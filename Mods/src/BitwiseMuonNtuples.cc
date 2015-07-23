#include "MitTagAndProbe/Mods/interface/BitwiseMuonNtuples.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitPhysics/Utils/interface/MuonTools.h"

#include "TVector2.h"
#include "TLorentzVector.h"
#include <vector>
#include <cstring>

template class vector< vector<bool> >;
//template class vector<string>;
//template class vector<int>;
template class vector<TLorentzVector*>;

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
    vector<bool> MuClassTypeBits(NClassTypes); 
    vector<bool> MuIdTypeBits(NIdTypes); 
    vector<bool> MuIsoTypeBits(NIsoTypes); 
    // Set bits for Muon class types
    for(unsigned int iType=0; iType != NClassTypes; iType++) {
      MuonTools::EMuClassType MuonClassType = MuClassTypes[iType];
      if(MuonTools::PassClass(&muon, MuonTools::EMuClassType(MuonClassType))) {
        MuClassTypeBits[iType]=true; 
      } else {
        MuClassTypeBits[iType]=false; 
      }
    }
    // Set bits for Muon id types
    for(unsigned int iType=0; iType != NIdTypes; iType++) {
      MuonTools::EMuIdType MuonIdType = MuIdTypes[iType];
      if(MuonTools::PassId(&muon, MuonTools::EMuIdType(MuonIdType))) {
        MuIdTypeBits[iType]=true; 
      } else {
        MuIdTypeBits[iType]=false; 
      }
    }
    // Set bits for Muon isolation types
    for(unsigned int iType=0; iType != NIsoTypes; iType++) {
      MuonTools::EMuIsoType MuonIsoType = MuIsoTypes[iType];
      if(MuonTools::PassIso(&muon, MuonTools::EMuIsoType(MuonIsoType))) {
        MuIsoTypeBits[iType]=true; 
      } else {
        MuIsoTypeBits[iType]=false; 
      }
    }
    float charge = muon.Trk()->Charge();
    TLorentzVector *fourMomentum=new TLorentzVector(
      muon.Px(),
      muon.Py(),
      muon.Pz(),
      muon.E()
    );
    MuClassTypeBits_.push_back(MuClassTypeBits);
    MuIdTypeBits_.push_back(MuIdTypeBits);
    MuIsoTypeBits_.push_back(MuIsoTypeBits);
    charge_.push_back(charge);
    fourMomentum_.push_back(fourMomentum);
    
  }
  fNtuplesTree->Fill();
  MuClassTypeBits_.resize(0);
  MuIdTypeBits_.resize(0);
  MuIsoTypeBits_.resize(0);
  charge_.resize(0);
  fourMomentum_.resize(0);
}

void
mithep::BitwiseMuonNtuples::SlaveBegin()
{
  fPropertiesTree = new TTree("BitNames", "");
  fPropertiesTree->Branch("ClassNames", "vector<string>", &MuClassTypeNames);
  fPropertiesTree->Branch("IdNames",    "vector<string>", &MuIdTypeNames);
  fPropertiesTree->Branch("IsoNames",   "vector<string>", &MuIsoTypeNames);
  //fPropertiesTree->SetBranchAddress("muonClassNames", &MuClassTypeNames);
  //fPropertiesTree->SetBranchAddress("muonIdNames",    &MuIdTypeNames);
  //fPropertiesTree->SetBranchAddress("muonIsoNames",   &MuIsoTypeNames);
  AddOutput(fPropertiesTree);
  fPropertiesTree->Fill();

  fNtuplesTree = new TTree("Events", "Big burlap sack o' muons.");
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
  fNtuplesTree->Branch("charge", "vector<int>", &charge_);  
  fNtuplesTree->Branch("fourMomentum", "vector<TLorentzVector*>", &fourMomentum_ );         
  fNtuplesTree->Branch("ClassBits", "vector< vector<bool> >", &MuClassTypeBits_);
  fNtuplesTree->Branch("IdBits", "vector< vector<bool> >", &MuIdTypeBits_);
  fNtuplesTree->Branch("IsoBits", "vector< vector<bool> >", &MuIsoTypeBits_);
  
  //fNtuplesTree->SetBranchAddress("muonCharge",     &charge_);
  //fNtuplesTree->SetBranchAddress("muon4Momentum",     &fourMomentum_);
  //fNtuplesTree->SetBranchAddress("muonClassBits",  &MuClassTypeBits_);
  //fNtuplesTree->SetBranchAddress("muonIdBits",   &MuIdTypeBits_);
  //fNtuplesTree->SetBranchAddress("muonIsoBits", &MuIsoTypeBits_);
  
  AddOutput(fNtuplesTree);
}

void
mithep::BitwiseMuonNtuples::SlaveTerminate()
{
}


