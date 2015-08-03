#include "MitTagAndProbe/Mods/interface/BitwiseMuonNtuples.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitPhysics/Utils/interface/MuonTools.h"
#include "MitPhysics/Mods/interface/MuonIdMod.h"

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
  fPVName(Names::gkPVBeamSpotBrn)
{
}

void
mithep::BitwiseMuonNtuples::AddIdFlag(std::string name, mithep::MuonTools::EMuIdType IdType)
{
  MuIdTypeNames.push_back(name);
  MuIdTypes.push_back(IdType);
  NIdTypes++;
}
void
mithep::BitwiseMuonNtuples::AddIsoFlag(std::string name, mithep::MuonTools::EMuIsoType IsoType)
{
  MuIsoTypeNames.push_back(name);
  MuIsoTypes.push_back(IsoType);
  NIsoTypes++;
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
  
  // Array of NFArrBool with flags from object published by MuonIdMod
  mithep::NFArrBool *IdFlags[NIdTypes];
  mithep::NFArrBool *IsoFlags[NIsoTypes];
  // Now get the published objects and fill these arrays
  for(unsigned int iType=0; iType != NIdTypes; iType++) {
    IdFlags[iType] = GetObject<mithep::NFArrBool>(MuIdTypeNames[iType].c_str());
//    printf("%d entries in IdFlags\n",IdFlags[iType]->GetEntries());
  }
  for(unsigned int iType=0; iType != NIsoTypes; iType++) {
    IsoFlags[iType] = GetObject<mithep::NFArrBool>(MuIsoTypeNames[iType].c_str());
//    printf("%d entries in IsoFlags\n",IsoFlags[iType]->GetEntries());
  }
  
  // Set Object-level variables 
  for (unsigned iP(0); iP != allMuons->GetEntries(); ++iP) {  
    Muon const &muon(*allMuons->At(iP));
    vector<bool> MuIdTypeBits(NIdTypes); 
    vector<bool> MuIsoTypeBits(NIsoTypes); 
    // Set bits for Muon id types
    for(unsigned int iType=0; iType != NIdTypes; iType++) {
      //MuonTools::EMuIdType MuonIdType = MuIdTypes[iType];
      //if(MuonTools::PassId(&muon, MuonTools::EMuIdType(MuonIdType))) {
      //  MuIdTypeBits[iType]=true; 
      //} else {
      //  MuIdTypeBits[iType]=false; 
      //
      //printf("reading IdFlags at iP=%d\n",iP);
      MuIdTypeBits[iType] = IdFlags[iType]->At(iP);
      if(MuIdTypeBits[iType]) fIdHisto->Fill(MuIdTypeNames[iType].c_str(), 1);
    }
    // Set bits for Muon isolation types
    for(unsigned int iType=0; iType != NIsoTypes; iType++) {
      //MuonTools::EMuIsoType MuonIsoType = MuIsoTypes[iType];
      //if(MuonTools::PassIso(&muon, MuonTools::EMuIsoType(MuonIsoType))) {
      //  MuIsoTypeBits[iType]=true; 
      //} else {
      //  MuIsoTypeBits[iType]=false; 
      //}
      //printf("reading IsoFlags at iP=%d\n",iP);
      MuIsoTypeBits[iType] = IsoFlags[iType]->At(iP);
      if(MuIsoTypeBits[iType]) fIsoHisto->Fill(MuIsoTypeNames[iType].c_str(), 1);
    }
    float charge = muon.Trk()->Charge();
    TLorentzVector *fourMomentum=new TLorentzVector(
      muon.Px(),
      muon.Py(),
      muon.Pz(),
      muon.E()
    );
    MuIdTypeBits_.push_back(MuIdTypeBits);
    MuIsoTypeBits_.push_back(MuIsoTypeBits);
    charge_.push_back(charge);
    fourMomentum_.push_back(fourMomentum);
    
  }
  fNtuplesTree->Fill();
  MuIdTypeBits_.resize(0);
  MuIsoTypeBits_.resize(0);
  charge_.resize(0);
  fourMomentum_.resize(0);
}

void
mithep::BitwiseMuonNtuples::SlaveBegin()
{
  fPropertiesTree = new TTree("BitNames", "");
  fPropertiesTree->Branch("IdNames",    "vector<string>", &MuIdTypeNames);
  fPropertiesTree->Branch("IsoNames",   "vector<string>", &MuIsoTypeNames);
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
  fNtuplesTree->Branch("IdBits", "vector< vector<bool> >", &MuIdTypeBits_);
  fNtuplesTree->Branch("IsoBits", "vector< vector<bool> >", &MuIsoTypeBits_);
 
  //histo outputs
  fIdHisto = new TH1F("Counts by Id","", 1, 0, 1);
  fIsoHisto= new TH1F("Counts by Iso","", 1, 0, 1);
  AddOutput(fNtuplesTree);
  AddOutput(fIdHisto);
  AddOutput(fIsoHisto);
}

void
mithep::BitwiseMuonNtuples::SlaveTerminate()
{
}


