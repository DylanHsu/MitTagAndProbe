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
template class vector<TLorentzVector*>;

ClassImp(mithep::BitwiseElectronNtuples)

mithep::BitwiseElectronNtuples::BitwiseElectronNtuples(char const* _name/* = "mithep::BitwiseElectronNtuples"*/, char const* _title/* = "Flat-tree ntuples producer"*/) :
  BaseMod(_name, _title),
  fAllElectronsName(Names::gkElectronBrn),
  fTriggerObjectsName(mithep::Names::gkHltObjBrn),
  fPVName(Names::gkPVBeamSpotBrn)
{
}

void
mithep::BitwiseElectronNtuples::AddIdFlag(std::string name, mithep::ElectronTools::EElIdType IdType)
{
  ElIdTypeNames.push_back(name);
  ElIdTypes.push_back(IdType);
  NIdTypes++;
}
void
mithep::BitwiseElectronNtuples::AddIsoFlag(std::string name, mithep::ElectronTools::EElIsoType IsoType)
{
  ElIsoTypeNames.push_back(name);
  ElIsoTypes.push_back(IsoType);
  NIsoTypes++;
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
  
  // Arrays of NFArrBool with flags from object published by ElectronIdMod
  mithep::NFArrBool *IdFlags[NIdTypes];
  mithep::NFArrBool *IsoFlags[NIsoTypes];
  // Now get the published objects and fill these arrays
  for(unsigned int iType=0; iType != NIdTypes; iType++) {
    IdFlags[iType] = GetObject<mithep::NFArrBool>(ElIdTypeNames[iType].c_str());
  }
  for(unsigned int iType=0; iType != NIsoTypes; iType++) {
    IsoFlags[iType] = GetObject<mithep::NFArrBool>(ElIsoTypeNames[iType].c_str());
  }
  
  // Set Object-level variables 
  for (unsigned iP(0); iP != allElectrons->GetEntries(); ++iP) {  
    Electron const &electron(*allElectrons->At(iP));
    vector<bool> ElIdTypeBits(NIdTypes); 
    vector<bool> ElIsoTypeBits(NIsoTypes); 
    // Set bits for Electron id types
    for(unsigned int iType=0; iType != NIdTypes; iType++) {
      ElIdTypeBits[iType] = IdFlags[iType]->At(iP);
      if(ElIdTypeBits[iType]) fIdHisto->Fill(ElIdTypeNames[iType].c_str(), 1);
    }
    // Set bits for Electron isolation types
    for(unsigned int iType=0; iType != NIsoTypes; iType++) {
      ElIsoTypeBits[iType] = IsoFlags[iType]->At(iP);
      if(ElIsoTypeBits[iType]) fIsoHisto->Fill(ElIsoTypeNames[iType].c_str(), 1);
    }
    float charge = electron.Trk()->Charge();
    TLorentzVector *fourMomentum=new TLorentzVector(
      electron.Px(),
      electron.Py(),
      electron.Pz(),
      electron.E()
    );
    ElIdTypeBits_.push_back(ElIdTypeBits);
    ElIsoTypeBits_.push_back(ElIsoTypeBits);
    charge_.push_back(charge);
    fourMomentum_.push_back(fourMomentum);
    
  }
  fNtuplesTree->Fill();
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
  AddOutput(fPropertiesTree);
  fPropertiesTree->Fill();

  fNtuplesTree = new TTree("Events", "Big burlap sack o' electrons.");
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
 
  //histo outputs
  fIdHisto = new TH1F("Counts by Id","", 1, 0, 1);
  fIsoHisto= new TH1F("Counts by Iso","", 1, 0, 1);
  AddOutput(fNtuplesTree);
  AddOutput(fIdHisto);
  AddOutput(fIsoHisto);
}

void
mithep::BitwiseElectronNtuples::SlaveTerminate()
{
}


