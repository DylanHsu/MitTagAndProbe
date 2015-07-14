#include "MitTagAndProbe/Mods/interface/ElectronNtuples.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/Names.h"

#include "TVector2.h"
#include "TLorentzVector.h"
#include <vector>
#include <cstring>

ClassImp(mithep::ElectronNtuples)

mithep::ElectronNtuples::ElectronNtuples(char const* _name/* = "mithep::ElectronNtuples"*/, char const* _title/* = "Flat-tree ntuples producer"*/) :
  BaseMod(_name, _title),
  fTagElectronsName("TagElectrons"),
  fProbeElectronsName("ProbeElectrons"),
  fAllElectronsName(Names::gkElectronBrn),
  fTriggerObjectsName(mithep::Names::gkHltObjBrn),
  fTriggerMatchName(""),
  fPVName(Names::gkPVBeamSpotBrn)
{
}

void
mithep::ElectronNtuples::Process()
{
  mithep::ElectronCol* tagElectrons = GetObject<mithep::ElectronCol>(fTagElectronsName);
  mithep::ElectronCol* probeElectrons = GetObject<mithep::ElectronCol>(fProbeElectronsName);
  mithep::ElectronCol* allElectrons = GetObject<mithep::ElectronCol>(fAllElectronsName);
  mithep::VertexCol* Vertices = GetObject<mithep::VertexCol>(fPVName);

  if (!tagElectrons || !probeElectrons || !allElectrons) {
    std::cerr << "Could not find electrons in this event." << std::endl;
    return;
  }

  bool doTriggerMatch(fTriggerMatchName.Length() != 0);

  // Make vector of trigger objects and fill it
  std::vector<TriggerObject const*> matchObjects;
  if (doTriggerMatch) {
    mithep::TriggerObjectCol* fTriggerObjects = GetObject<mithep::TriggerObjectCol>(fTriggerObjectsName);

    if (!fTriggerObjects) {
      std::cerr << "Could not find trigger objects in the event." << std::endl;
      return;
    } 

    for (unsigned iO(0); iO != fTriggerObjects->GetEntries(); ++iO) {
      TriggerObject const& to(*fTriggerObjects->At(iO));

      if (std::strcmp(to.ModuleName(), fTriggerMatchName) == 0)
        matchObjects.push_back(&to);
    }

    if (matchObjects.size() == 0)
      return;
  }
  // Make tags vector, this sectino also includes the trigger matching
  std::vector<Electron const*> tags;
  
  for (unsigned iT(0); iT != tagElectrons->GetEntries(); ++iT) {
    Electron const& inEle(*tagElectrons->At(iT));

    // TRIGGER MATCHING
    if (doTriggerMatch) {
      unsigned iM(0);
      for (; iM != matchObjects.size(); ++iM) {
        double dEta(matchObjects[iM]->Eta() - inEle.Eta());
        double dPhi(TVector2::Phi_mpi_pi(matchObjects[iM]->Phi() - inEle.Phi()));

        if (dEta * dEta + dPhi * dPhi < 0.15 * 0.15)
          break;
      }
      if (iT == matchObjects.size())
        continue;
    }
    // END TRIGGER MATCHING
    // apply more cuts to tag
    tags.push_back(&inEle);
  }

  // Make probe vector
  std::vector<Electron const*> probes;
  for (unsigned iP(0); iP != probeElectrons->GetEntries(); ++iP) {
    Electron const& inEle(*probeElectrons->At(iP));
    // apply some additional cuts to probe
    probes.push_back(&inEle);
  }
  
  // Make failing probes vector
  std::vector<Electron const*> failing_probes;
  for (unsigned iA(0); iA != allElectrons->GetEntries(); ++iA) {
    Electron const& anyEle(*allElectrons->At(iA));
    bool passed_probe=false;
    for (unsigned iP(0); iP != probeElectrons->GetEntries(); ++iP) {
      Electron const& probeEle(*probeElectrons->At(iP));
      if(probeEle.Trk() == anyEle.Trk()) {
        passed_probe=true;
        break;
      }
    }
    if(passed_probe) continue;
    failing_probes.push_back(&anyEle);
  }
  
  // Make vector of all muons
  std::vector<Electron const*> all_muons;
  for (unsigned iP(0); iP != allElectrons->GetEntries(); ++iP) {
    Electron const& inEle(*allElectrons->At(iP));
    all_muons.push_back(&inEle);
  }

  // Record number of good PV
  // std::cout << fVertices->GetEntries()  << " vertices\n";
  // Make pairs of tag & passing probe
  npv=Vertices->GetEntries();
  scale1fb=1.;
  npu=0;
  evtNum = GetEventHeader()->EvtNum();
  runNum = GetEventHeader()->RunNum();
  lumiSec = GetEventHeader()->LumiSec();

  for (Electron const* tag : tags) {
    for (Electron const* probe : probes) { 
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
      fNtuplesTree->Fill();
    }
    
    for (Electron const* failing_probe : failing_probes) { 
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
      fNtuplesTree->Fill();

    }
  }
}

void
mithep::ElectronNtuples::SlaveBegin()
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
mithep::ElectronNtuples::SlaveTerminate()
{
}


