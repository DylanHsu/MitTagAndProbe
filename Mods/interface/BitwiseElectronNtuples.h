#ifndef MIT_TAGANDPROBE_MODS_BITWISE_ELECTRON_NTUPLES_MOD_H
#define MIT_TAGANDPROBE_MODS_BITWISE_ELECTRON_NTUPLES_MOD_H
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/ElectronCol.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitPhysics/Utils/interface/ElectronTools.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/VertexFwd.h" 
#include "TLorentzVector.h"
#include "TTree.h"
#include "TString.h"

namespace mithep {
  
  class BitwiseElectronNtuples : public BaseMod {
  public:
    BitwiseElectronNtuples(char const* name = "BitwiseElectronNtuples", char const* title = "Flat-tree ntuples producer");
    void SetAllElectronsName(char const* _name) { fAllElectronsName = _name; }
    void SetTriggerObjectsName(char const* _name) { fTriggerObjectsName = _name; }
    void SetPVName(const char *n)             { fPVName = n;                }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fAllElectronsName;
    TString fTriggerObjectsName;
    TString fPVName;  

    TTree* fNtuplesTree;
    TTree* fPropertiesTree;
    
    //std::vector<MuonTools::EMuClassType> MuClassTypes {
    //  MuonTools::kAll,
    //  MuonTools::kGlobal,
    //  MuonTools::kGlobalorTracker,
    //  MuonTools::kGlobalTracker,
    //  MuonTools::kSta,
    //  MuonTools::kTrackerMuon,
    //  MuonTools::kCaloMuon,
    //  MuonTools::kTrackerBased,
    //  MuonTools::kGlobalOnly,
    //  MuonTools::kPFGlobalorTracker
    //};
   
    //std::vector<std::string> MuClassTypeNames {
    //  "All",
    //  "Global",
    //  "GlobalorTracker",
    //  "GlobalTracker",
    //  "Sta",
    //  "TrackerMuon",
    //  "CaloMuon",
    //  "TrackerBased",
    //  "GlobalOnly",
    //  "PFGlobalorTracker"
    //};
    
    std::vector<ElectronTools::EElIdType> ElIdTypes {
      ElectronTools::kIdUndef = 0,
      ElectronTools::kTight,
      ElectronTools::kLoose,
      ElectronTools::kLikelihood,
      ElectronTools::kNoId,
      ElectronTools::kZeeId,
      ElectronTools::kCustomIdLoose,
      ElectronTools::kCustomIdTight,
      ElectronTools::kVBTFWorkingPointFakeableId,
      ElectronTools::kVBTFWorkingPoint95Id,
      ElectronTools::kVBTFWorkingPoint90Id,
      ElectronTools::kVBTFWorkingPoint85Id,
      ElectronTools::kVBTFWorkingPoint80Id,
      ElectronTools::kVBTFWorkingPointLowPtId,
      ElectronTools::kVBTFWorkingPoint70Id,
      ElectronTools::kMVAID_BDTG_NoIPInfo,
      ElectronTools::kMVAID_BDTG_WithIPInfo,
      ElectronTools::kMVAID_BDTG_IDIsoCombined,
      ElectronTools::kHggLeptonTagId,
      ElectronTools::kHggLeptonTagId2012,
      ElectronTools::kHggLeptonTagId2012HCP,
      ElectronTools::kMVAID_BDTG_IDHWW2012TrigV0,
      ElectronTools::kMVAID_BDTG_IDIsoCombinedHWW2012TrigV4,
      ElectronTools::kPhys14Veto,
      ElectronTools::kPhys14Loose,
      ElectronTools::kPhys14Medium,
      ElectronTools::kPhys14Tight
    };

    std::vector<std::string> ElIdTypeNames {
      "IdUndef",
      "Tight",
      "Loose",
      "Likelihood",
      "NoId",
      "ZeeId",
      "CustomIdLoose",
      "CustomIdTight",
      "VBTFWorkingPointFakeableId",
      "VBTFWorkingPoint95Id",
      "VBTFWorkingPoint90Id",
      "VBTFWorkingPoint85Id",
      "VBTFWorkingPoint80Id",
      "VBTFWorkingPointLowPtId",
      "VBTFWorkingPoint70Id",
      "MVAID_BDTG_NoIPInfo",
      "MVAID_BDTG_WithIPInfo",
      "MVAID_BDTG_IDIsoCombined",
      "HggLeptonTagId",
      "HggLeptonTagId2012",
      "HggLeptonTagId2012HCP",
      "MVAID_BDTG_IDHWW2012TrigV0",
      "MVAID_BDTG_IDIsoCombinedHWW2012TrigV4",
      "Phys14Veto",
      "Phys14Loose",
      "Phys14Medium",
      "Phys14Tight"
    };
 
    std::vector<ElectronTools::EElIsoType> ElIsoTypes {
      ElectronTools::kIsoUndef = 0,               
      ElectronTools::kTrackCalo,               
      ElectronTools::kTrackJura,
      ElectronTools::kTrackJuraCombined,
      ElectronTools::kTrackJuraSliding,
      ElectronTools::kTrackJuraSlidingNoCorrection,
      ElectronTools::kCombinedRelativeConeAreaCorrected,
      ElectronTools::kNoIso,
      ElectronTools::kPFIso, 
      ElectronTools::kPFIsoRhoCorrected, 
      ElectronTools::kPFIsoNoL,
      ElectronTools::kZeeIso,
      ElectronTools::kCustomIso,        
      ElectronTools::kVBTFWorkingPoint95IndividualIso,     
      ElectronTools::kVBTFWorkingPoint90IndividualIso,
      ElectronTools::kVBTFWorkingPoint85IndividualIso,
      ElectronTools::kVBTFWorkingPoint80IndividualIso,
      ElectronTools::kVBTFWorkingPoint70IndividualIso,
      ElectronTools::kVBTFWorkingPoint95CombinedIso,     
      ElectronTools::kVBTFWorkingPoint90CombinedIso,
      ElectronTools::kVBTFWorkingPoint85CombinedIso,
      ElectronTools::kVBTFWorkingPoint80CombinedIso,
      ElectronTools::kVBTFWorkingPoint70CombinedIso,
      ElectronTools::kMVAIso_BDTG_IDIsoCombined,               
      ElectronTools::kPFIso_HWW2012TrigV0,
      ElectronTools::kPFIso_HggLeptontag2012,
      ElectronTools::kPFIso_HggLeptonTag2012HCP,
      ElectronTools::kMVAIso_BDTG_IDIsoCombinedHWW2012TrigV4,
      ElectronTools::kPhys14VetoIso,
      ElectronTools::kPhys14LooseIso,
      ElectronTools::kPhys14MediumIso,
      ElectronTools::kPhys14TightIso
    };
  
    std::vector<std::string> ElIsoTypeNames {
      "IsoUndef",
      "TrackCalo",
      "TrackJura",
      "TrackJuraCombined",
      "TrackJuraSliding",
      "TrackJuraSlidingNoCorrection",
      "CombinedRelativeConeAreaCorrected",
      "NoIso",
      "PFIso",
      "PFIsoRhoCorrected",
      "PFIsoNoL",
      "ZeeIso",
      "CustomIso",
      "VBTFWorkingPoint95IndividualIso",
      "VBTFWorkingPoint90IndividualIso",
      "VBTFWorkingPoint85IndividualIso",
      "VBTFWorkingPoint80IndividualIso",
      "VBTFWorkingPoint70IndividualIso",
      "VBTFWorkingPoint95CombinedIso",
      "VBTFWorkingPoint90CombinedIso",
      "VBTFWorkingPoint85CombinedIso",
      "VBTFWorkingPoint80CombinedIso",
      "VBTFWorkingPoint70CombinedIso",
      "MVAIso_BDTG_IDIsoCombined",
      "PFIso_HWW2012TrigV0",
      "PFIso_HggLeptonTag2012",
      "PFIso_HggLeptonTag2012HCP",
      "MVAIso_BDTG_IDIsoCombinedHWW2012TrigV4",
      "Phys14VetoIso",
      "Phys14LooseIso",
      "Phys14MediumIso",
      "Phys14TightIso"
    };

    //std::vector<std::array<Bool_t, sizeof(MuClassTypes)/sizeof(UInt_t) > > MuClassTypeBits;
    //std::vector<std::array<Bool_t, sizeof(MuIdTypes)/sizeof(UInt_t) > >    MuIdTypeBits;
    //std::vector<std::array<Bool_t, sizeof(MuIsoTypes)/sizeof(UInt_t) > >   MuIsoTypeBits;
    //vector< vector<bool> > MuClassTypeBits_;
    //vector< vector<bool> > MuIdTypeBits_;
    //vector< vector<bool> > MuIsoTypeBits_;
    vector< vector<bool> > ElIdTypeBits_;
    vector< vector<bool> > ElIsoTypeBits_;
    //Bool_t MuIdTypeBits[sizeof(MuIdTypes)/sizeof(UInt_t)];
    //Bool_t MuIsoTypeBits[sizeof(MuIsoTypes)/sizeof(UInt_t)];
    //unsigned int NClassTypes = sizeof(MuClassTypes)/sizeof(UInt_t);
    //unsigned int NIdTypes = sizeof(MuIdTypes)/sizeof(UInt_t);
    //unsigned int NIsoTypes = sizeof(MuIsoTypes)/sizeof(UInt_t);
    //unsigned int NClassTypes = MuClassTypes.size();
    //unsigned int NIdTypes    = MuIdTypes.size(); 
    //unsigned int NIsoTypes   = MuIsoTypes.size();
    unsigned int NIdTypes = ElIdTypes.size();
    unsigned int NIsoTypes = ElIsoTypes.size();

    unsigned int runNum, lumiSec, evtNum; 
    unsigned int npv;                     
    std::vector<int> charge_;             
    std::vector<TLorentzVector*> fourMomentum_;        // tag, probe 4-vector
    ClassDef(BitwiseElectronNtuples, 0)
  };

}

#endif
