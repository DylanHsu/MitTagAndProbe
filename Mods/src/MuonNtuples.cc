#include "MitTagAndProbe/Mods/interface/MuonNtuples.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/Names.h"

#include "TVector2.h"
#include "TLorentzVector.h"
#include <vector>
#include <cstring>

ClassImp(mithep::MuonNtuples)

mithep::MuonNtuples::MuonNtuples(char const* _name/* = "mithep::MuonNtuples"*/, char const* _title/* = "Flat-tree ntuples producer"*/) :
  BaseMod(_name, _title),
  fTagMuonsName("TagMuons"),
  fProbeMuonsName("ProbeMuons"),
  fAllMuonsName(Names::gkMuonBrn),
  fTriggerObjectsName(mithep::Names::gkHltObjBrn),
  fTriggerMatchName(""),
  fPVName(Names::gkPVBeamSpotBrn)
//fTagMuons(0),
// fProbeMuons(0),
//fAllMuons(0),
//fVertices(0)
{
}

void
mithep::MuonNtuples::Process()
{
  mithep::MuonCol* tagMuons = GetObject<mithep::MuonCol>(fTagMuonsName);
  mithep::MuonCol* probeMuons = GetObject<mithep::MuonCol>(fProbeMuonsName);
  mithep::MuonCol* allMuons = GetObject<mithep::MuonCol>(fAllMuonsName);
  mithep::VertexCol* Vertices = GetObject<mithep::VertexCol>(fPVName);

  if (!tagMuons || !probeMuons || !allMuons) {
    std::cerr << "Could not find muons in this event." << std::endl;
    return;
  }
  //printf("%d tag muons, %d probe muons, %d all muons, %d vertices\n",tagMuons->GetEntries(), probeMuons->GetEntries(), allMuons->GetEntries(), Vertices->GetEntries());

  bool doTriggerMatch(fTriggerMatchName.Length() != 0);
  //bool doTriggerMatch=0;
  // Make vector of trigger objects and fill it
  std::vector<TriggerObject const*> matchObjects;
  if (doTriggerMatch) {
    mithep::TriggerObjectCol* fTriggerObjects = GetObject<mithep::TriggerObjectCol>(fTriggerObjectsName);
    //LoadEventObject(fTriggerObjectsName, fTriggerObjects);

    if (!fTriggerObjects) {
      std::cerr << "Could not find trigger objects in the event." << std::endl;
      return;
    } 

    for (unsigned iO(0); iO != fTriggerObjects->GetEntries(); ++iO) {
      TriggerObject const& to(*fTriggerObjects->At(iO));

      //if (std::strcmp(to.ModuleName(), fTriggerMatchName) == 0)
        matchObjects.push_back(&to);
    }

    if (matchObjects.size() == 0) {
      //printf("matchObjects.size() == 0, continuing\n");
      return;
    }
  }
  // Make tags vector, this sectino also includes the trigger matching
  std::vector<Muon const*> tags;
  
  for (unsigned iT(0); iT != tagMuons->GetEntries(); ++iT) {
    Muon const& inMu(*tagMuons->At(iT));

    // TRIGGER MATCHING
    if (doTriggerMatch) {
      unsigned iM(0);
      for (; iM != matchObjects.size(); ++iM) {
        double dEta(matchObjects[iM]->Eta() - inMu.Eta());
        double dPhi(TVector2::Phi_mpi_pi(matchObjects[iM]->Phi() - inMu.Phi()));

        if (dEta * dEta + dPhi * dPhi < 0.15 * 0.15)
          break;
      }
      if (iT == matchObjects.size()) {
        //printf("iT == matchObjects.size(), continuing\n");
        continue;
      }
    }
    // END TRIGGER MATCHING
    // apply more cuts to tag
    tags.push_back(&inMu);
  }

  // Make probe vector
  std::vector<Muon const*> probes;
  for (unsigned iP(0); iP != probeMuons->GetEntries(); ++iP) {
    Muon const& inMu(*probeMuons->At(iP));
    // apply some additional cuts to probe
    probes.push_back(&inMu);
  }
  
  // Make failing probes vector
  std::vector<Muon const*> failing_probes;
  for (unsigned iA(0); iA != allMuons->GetEntries(); ++iA) {
    Muon const& anyMu(*allMuons->At(iA));
    bool passed_probe=false;
    for (unsigned iP(0); iP != probeMuons->GetEntries(); ++iP) {
      Muon const& probeMu(*probeMuons->At(iP));
      if(probeMu.Trk() == anyMu.Trk()) {
        passed_probe=true;
        break;
      }
    }
    if(passed_probe) {
      //printf("Passed probe, continuing\n"); 
      continue;
    }
    failing_probes.push_back(&anyMu);
  }
  
  // Make vector of all muons
  std::vector<Muon const*> all_muons;
  for (unsigned iP(0); iP != allMuons->GetEntries(); ++iP) {
    Muon const& inMu(*allMuons->At(iP));
    all_muons.push_back(&inMu);
  }

  //fPassingEvent.clear();
  //fAllEvent.clear();

  // Record number of good PV
  // std::cout << fVertices->GetEntries()  << " vertices\n";
  // Make pairs of tag & passing probe
  npv=Vertices->GetEntries();
  scale1fb=1.;
  npu=0;
  evtNum = GetEventHeader()->EvtNum();
  runNum = GetEventHeader()->RunNum();
  lumiSec = GetEventHeader()->LumiSec();

  //printf("tags vector has %lu entries, probes vector has %lu entries\n",tags.size(),probes.size());
  
  for (Muon const* tag : tags) {
    for (Muon const* probe : probes) { 
      // candidates overlap in supercluster -> a same EG object
      if (tag->Trk() == probe->Trk() )
        continue;
      qtag = tag->Trk()->Charge();
      qprobe = probe->Trk()->Charge();
      if ( round(qtag + qprobe)!=0 ) continue;
      tagTLV=new TLorentzVector(
        tag->Px(),
        tag->Py(),
        tag->Pz(),
        tag->E()
      );
      probeTLV=new TLorentzVector(
        probe->Px(),
        probe->Py(),
        probe->Pz(),
        probe->E()
      );
      TLorentzVector dimuon_system_TLV = *probeTLV + *tagTLV;
      mass = dimuon_system_TLV.M();
      pass = 1;
      printf("Filling fNtuplesTree (runNum=%d, lumiSec=%d, evtNum=%d, pass=%d, mass=%f)\n",runNum,lumiSec,evtNum,pass,mass);
      fNtuplesTree->Fill();
    }
    
    for (Muon const* failing_probe : failing_probes) { 
      if (tag->Trk() == failing_probe->Trk() )
        continue;
      qtag = tag->Trk()->Charge();
      qprobe = failing_probe->Trk()->Charge();
      if ( round(qtag + qprobe)!=0 ) continue;
      tagTLV=new TLorentzVector(
        tag->Px(),
        tag->Py(),
        tag->Pz(),
        tag->E()
      );
      probeTLV=new TLorentzVector(
        failing_probe->Px(),
        failing_probe->Py(),
        failing_probe->Pz(),
        failing_probe->E()
      );
      TLorentzVector dimuon_system_TLV = *probeTLV + *tagTLV;
      mass = dimuon_system_TLV.M();
      pass = 0;
      printf("Filling fNtuplesTree (runNum=%d, lumiSec=%d, evtNum=%d, pass=%d, mass=%f)\n",runNum,lumiSec,evtNum,pass,mass);
      fNtuplesTree->Fill();

    }
  }
}

void
mithep::MuonNtuples::SlaveBegin()
{
  fNtuplesTree = new TTree("Events", "Tag and probe events with 2 muons for Kevin's script");
  
  fNtuplesTree->Branch("runNum",   &runNum,   "runNum/i"   );  
  fNtuplesTree->Branch("lumiSec",  &lumiSec,  "lumiSec/i"  );  
  fNtuplesTree->Branch("evtNum",   &evtNum,   "evtNum/i"   );  
  fNtuplesTree->Branch("npv",      &npv,      "npv/i"      );  
  fNtuplesTree->Branch("pass",     &pass,     "pass/i"     );  
  fNtuplesTree->Branch("npu",      &npu,      "npu/F"      );  
  fNtuplesTree->Branch("scale1fb", &scale1fb, "scale1fb/F" );
  fNtuplesTree->Branch("mass",     &mass,     "mass/F"     );  
  fNtuplesTree->Branch("qtag",     &qtag,     "qtag/I"     );  
  fNtuplesTree->Branch("qprobe",   &qprobe,   "qprobe/I"   );  
  // Need to make the TLorentzVector branches differently
  fNtuplesTree->Branch("tag",   "TLorentzVector", &tagTLV   );  
  fNtuplesTree->Branch("probe", "TLorentzVector", &probeTLV );         
  
  fNtuplesTree->SetBranchAddress("runNum",   &runNum);
  fNtuplesTree->SetBranchAddress("lumiSec",  &lumiSec);
  fNtuplesTree->SetBranchAddress("evtNum",   &evtNum);
  fNtuplesTree->SetBranchAddress("npv",      &npv);
  fNtuplesTree->SetBranchAddress("pass",     &pass);
  fNtuplesTree->SetBranchAddress("npu",      &npu);
  fNtuplesTree->SetBranchAddress("scale1fb", &scale1fb);
  fNtuplesTree->SetBranchAddress("mass",     &mass);
  fNtuplesTree->SetBranchAddress("qtag",     &qtag);
  fNtuplesTree->SetBranchAddress("qprobe",   &qprobe);
  fNtuplesTree->SetBranchAddress("tag",      &tagTLV);
  fNtuplesTree->SetBranchAddress("probe",    &probeTLV);
  
  AddOutput(fNtuplesTree);
}

void
mithep::MuonNtuples::SlaveTerminate()
{
}


