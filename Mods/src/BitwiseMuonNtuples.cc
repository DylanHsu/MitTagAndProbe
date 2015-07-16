#include "MitTagAndProbe/Mods/interface/BitwiseMuonNtuples.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitPhysics/Utils/interface/MuonTools.h"

#include "TVector2.h"
#include "TLorentzVector.h"
#include <vector>
#include <cstring>

ClassImp(mithep::BitwiseMuonNtuples)

mithep::BitwiseMuonNtuples::BitwiseMuonNtuples(char const* _name/* = "mithep::BitwiseMuonNtuples"*/, char const* _title/* = "Flat-tree ntuples producer"*/) :
  BaseMod(_name, _title),
  fAllMuonsName(Names::gkMuonBrn),
  fTriggerObjectsName(mithep::Names::gkHltObjBrn),
  fPVName(Names::gkPVBeamSpotBrn),
  MuClassTypes {
  }
{
}

void
mithep::BitwiseMuonNtuples::Process()
{
  mithep::MuonCol* allMuons = GetObject<mithep::MuonCol>(fAllMuonsName);
  mithep::VertexCol* Vertices = GetObject<mithep::VertexCol>(fPVName);

  if (!allMuons) {
    std::cerr << "Could not find muons in this event." << std::endl;
    return;
  }

  // Set Event-level variables
  npv=Vertices->GetEntries();
  evtNum = GetEventHeader()->EvtNum();
  runNum = GetEventHeader()->RunNum();
  lumiSec = GetEventHeader()->LumiSec();

  // Set Object-level variables 
  
  for (unsigned iP(0); iP != allMuons->GetEntries(); ++iP) {  
    Muon const &muon(*allMuons->At(iP));
    
    // Set bits for Muon class types
    for(unsigned int iType=0; iType != NClassTypes; iType++) {
      MuonTools::EMuClassType MuonClassType = MuClassTypes[iType];
      if(MuonTools::PassClass(&muon, MuonTools::EMuClassType(MuonClassType))) {
        MuClassTypeBits[iType]=1; 
      } else {
        MuClassTypeBits[iType]=0; 
      }
    }
    // Set bits for Muon id types
    for(unsigned int iType=0; iType != NIdTypes; iType++) {
      MuonTools::EMuIdType MuonIdType = MuIdTypes[iType];
      if(MuonTools::PassId(&muon, MuonTools::EMuIdType(MuonIdType))) {
        MuIdTypeBits[iType]=1; 
      } else {
        MuIdTypeBits[iType]=0; 
      }
    }
    // Set bits for Muon isolation types
    for(unsigned int iType=0; iType != NIsoTypes; iType++) {
      MuonTools::EMuIsoType MuonIsoType = MuIsoTypes[iType];
      if(MuonTools::PassIso(&muon, MuonTools::EMuIsoType(MuonIsoType))) {
        MuIsoTypeBits[iType]=1; 
      } else {
        MuIsoTypeBits[iType]=0; 
      }
    }
    charge = muon.Trk()->Charge();
    fourMomentum=new TLorentzVector(
      muon.Px(),
      muon.Py(),
      muon.Pz(),
      muon.E()
    );
    fNtuplesTree->Fill();
    
  }
}

void
mithep::BitwiseMuonNtuples::SlaveBegin()
{
  fNtuplesTree = new TTree("Muons", "Big burlap sack o' muons.");

  // Event-level branches
  fNtuplesTree->Branch("runNum",   &runNum,   "runNum/i"   );  
  fNtuplesTree->Branch("lumiSec",  &lumiSec,  "lumiSec/i"  );  
  fNtuplesTree->Branch("evtNum",   &evtNum,   "evtNum/i"   );  
  fNtuplesTree->Branch("npv",      &npv,      "npv/i"      );  
  fNtuplesTree->SetBranchAddress("runNum",   &runNum);
  fNtuplesTree->SetBranchAddress("lumiSec",  &lumiSec);
  fNtuplesTree->SetBranchAddress("evtNum",   &evtNum);
  fNtuplesTree->SetBranchAddress("npv",      &npv);
  
  // Object-level branches
  //fNtuplesTree->Branch("pass",     &pass,     "pass/i"     );  
  fNtuplesTree->Branch("mass",     &mass,     "mass/F"     );  
  fNtuplesTree->Branch("charge",     &charge,     "charge/I"     );  
  fNtuplesTree->Branch("fourMomentum", "TLorentzVector", &fourMomentum );         
  fNtuplesTree->SetBranchAddress("mass",     &mass);
  fNtuplesTree->SetBranchAddress("charge",     &charge);
  fNtuplesTree->SetBranchAddress("fourMomentum",     &fourMomentum);
  for(unsigned int iType=0; iType != NClassTypes; iType++) {
    std::string typeSpecifier= MuClassTypeNames[iType] + "/i";
    fNtuplesTree->Branch(MuClassTypeNames[iType].c_str(), std::addressof(MuClassTypeBits[iType]), typeSpecifier.c_str());
    fNtuplesTree->SetBranchAddress(MuClassTypeNames[iType].c_str(), std::addressof(MuClassTypeBits[iType]));
  }
  for(unsigned int iType=0; iType != NIdTypes; iType++) {
    std::string typeSpecifier= MuIdTypeNames[iType] + "/i";
    fNtuplesTree->Branch(MuIdTypeNames[iType].c_str(), std::addressof(MuIdTypeBits[iType]), typeSpecifier.c_str());
    fNtuplesTree->SetBranchAddress(MuIdTypeNames[iType].c_str(), std::addressof(MuIdTypeBits[iType]));
  }
  for(unsigned int iType=0; iType != NIsoTypes; iType++) {
    std::string typeSpecifier= MuIsoTypeNames[iType] + "/i";
    fNtuplesTree->Branch(MuIsoTypeNames[iType].c_str(), std::addressof(MuIsoTypeBits[iType]), typeSpecifier.c_str());
    fNtuplesTree->SetBranchAddress(MuIsoTypeNames[iType].c_str(), std::addressof(MuIsoTypeBits[iType]));
  }
  AddOutput(fNtuplesTree);
}

void
mithep::BitwiseMuonNtuples::SlaveTerminate()
{
}


