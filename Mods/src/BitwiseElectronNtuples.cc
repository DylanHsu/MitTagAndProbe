#include "MitTagAndProbe/Mods/interface/BitwiseElectronNtuples.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitPhysics/Utils/interface/ElectronTools.h"

#include "TVector2.h"
#include "TLorentzVector.h"
#include <vector>
#include <cstring>

template class vector< vector<bool> >;
//template class vector<string>;
//template class vector<int>;
template class vector<TLorentzVector*>;

ClassImp(mithep::BitwiseElectronNtuples)

mithep::BitwiseElectronNtuples::BitwiseElectronNtuples(char const* _name/* = "mithep::BitwiseElectronNtuples"*/, char const* _title/* = "Flat-tree ntuples producer"*/) :
  BaseMod(_name, _title),
  fAllElectronsName(Names::gkElectronBrn),
  fTriggerObjectsName(mithep::Names::gkHltObjBrn),
  fPVName(Names::gkPVBeamSpotBrn),
{
}

void
mithep::BitwiseElectronNtuples::Process()
{
  mithep::ElectronCol* allElectrons = GetObject<mithep::ElectronCol>(fAllElectronsName);
  mithep::VertexCol* Vertices = GetObject<mithep::VertexCol>(fPVName);

  if (!allElectrons) {
    std::cerr << "Could not find electrons in this event." << std::endl;
    return;
  }

  // Set Event-level variables
  npv=Vertices->GetEntries();
  evtNum = GetEventHeader()->EvtNum();
  runNum = GetEventHeader()->RunNum();
  lumiSec = GetEventHeader()->LumiSec();

  // Set Object-level variables 
  
  for (unsigned iP(0); iP != allElectrons->GetEntries(); ++iP) {  
    Electron const &electron(*allElectrons->At(iP));
    vector<bool> ElIdTypeBits(NIdTypes); 
    vector<bool> ElIsoTypeBits(NIsoTypes); 
    // Set bits for Muon class types
    //for(unsigned int iType=0; iType != NClassTypes; iType++) {
    //  MuonTools::EMuClassType MuonClassType = MuClassTypes[iType];
    //  if(MuonTools::PassClass(&muon, MuonTools::EMuClassType(MuonClassType))) {
    //    MuClassTypeBits[iType]=true; 
    //  } else {
    //    MuClassTypeBits[iType]=false; 
    //  }
    //}
    // Set bits for Electron id types
    for(unsigned int iType=0; iType != NIdTypes; iType++) {
      ElectronTools::EElIdType ElectronIdType = ElIdTypes[iType];
      if(ElectronTools::PassId(&electron, ElectronTools::EElIdType(ElectronIdType))) {
        ElIdTypeBits[iType]=true; 
      } else {
        ElIdTypeBits[iType]=false; 
      }
    }
    // Set bits for Electron isolation types
    for(unsigned int iType=0; iType != NIsoTypes; iType++) {
      ElectronTools::EElIsoType ElectronIsoType = ElIsoTypes[iType];
      if(ElectronTools::PassIso(&electron, ElectronTools::EElIsoType(ElectronIsoType))) {
        ElIsoTypeBits[iType]=true; 
      } else {
        ElIsoTypeBits[iType]=false; 
      }
    }
    float charge = electron.Trk()->Charge();
    TLorentzVector *fourMomentum=new TLorentzVector(
      Electron.Px(),
      Electron.Py(),
      Electron.Pz(),
      Electron.E()
    );
    ElIdTypeBits_.push_back(ElIdTypeBits);
    ElIsoTypeBits_.push_back(ElIsoTypeBits);
    charge_.push_back(charge);
    fourMomentum_.push_back(fourMomentum);
    
  }
  fNtuplesTree->Fill();
  ElClassTypeBits_.resize(0);
  ElIdTypeBits_.resize(0);
  ElIsoTypeBits_.resize(0);
  charge_.resize(0);
  fourMomentum_.resize(0);
}

void
mithep::BitwiseElectronNtuples::SlaveBegin()
{
  fPropertiesTree = new TTree("BitNames", "");
  fPropertiesTree->Branch("IdNames",    "vector<string>", &ElIdTypeNames);
  fPropertiesTree->Branch("IsoNames",   "vector<string>", &ElIsoTypeNames);
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
  fNtuplesTree->Branch("IdBits", "vector< vector<bool> >", &ElIdTypeBits_);
  fNtuplesTree->Branch("IsoBits", "vector< vector<bool> >", &ElIsoTypeBits_);
  
  //fNtuplesTree->SetBranchAddress("muonCharge",     &charge_);
  //fNtuplesTree->SetBranchAddress("muon4Momentum",     &fourMomentum_);
  //fNtuplesTree->SetBranchAddress("muonClassBits",  &MuClassTypeBits_);
  //fNtuplesTree->SetBranchAddress("muonIdBits",   &MuIdTypeBits_);
  //fNtuplesTree->SetBranchAddress("muonIsoBits", &MuIsoTypeBits_);
  
  AddOutput(fNtuplesTree);
}

void
mithep::BitwiseElectronNtuples::SlaveTerminate()
{
}


