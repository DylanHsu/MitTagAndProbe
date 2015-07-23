#ifndef MIT_TAGANDPROBE_MODS_BITWISE_MUON_NTUPLES_MOD_H
#define MIT_TAGANDPROBE_MODS_BITWISE_MUON_NTUPLES_MOD_H
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/MuonCol.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitPhysics/Utils/interface/MuonTools.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/VertexFwd.h" 
#include "TLorentzVector.h"
#include "TTree.h"
#include "TString.h"

namespace mithep {
  
  class BitwiseMuonNtuples : public BaseMod {
  public:
    BitwiseMuonNtuples(char const* name = "BitwiseMuonNtuples", char const* title = "Flat-tree ntuples producer");
    void SetAllMuonsName(char const* _name) { fAllMuonsName = _name; }
    void SetTriggerObjectsName(char const* _name) { fTriggerObjectsName = _name; }
    void SetPVName(const char *n)             { fPVName = n;                }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fAllMuonsName;
    TString fTriggerObjectsName;
    TString fPVName;  

    TTree* fNtuplesTree;
    TTree* fPropertiesTree;
    std::vector<MuonTools::EMuClassType> MuClassTypes {
      MuonTools::kAll,
      MuonTools::kGlobal,
      MuonTools::kGlobalorTracker,
      MuonTools::kGlobalTracker,
      MuonTools::kSta,
      MuonTools::kTrackerMuon,
      MuonTools::kCaloMuon,
      MuonTools::kTrackerBased,
      MuonTools::kGlobalOnly,
      MuonTools::kPFGlobalorTracker
    };
   
    std::vector<std::string> MuClassTypeNames {
      "All",
      "Global",
      "GlobalorTracker",
      "GlobalTracker",
      "Sta",
      "TrackerMuon",
      "CaloMuon",
      "TrackerBased",
      "GlobalOnly",
      "PFGlobalorTracker"
    };
    std::vector<MuonTools::EMuIdType> MuIdTypes {
      MuonTools::kWMuId,
      MuonTools::kZMuId,
      MuonTools::kTight,
      MuonTools::kMuonPOG2012CutBasedIdTight,
      MuonTools::kLoose,
      MuonTools::kWWMuIdV1,
      MuonTools::kWWMuIdV2,
      MuonTools::kWWMuIdV3,
      MuonTools::kWWMuIdV4,
      MuonTools::kNoId,
      MuonTools::kCustomId,
      MuonTools::kMVAID_BDTG_IDIso
    };

    std::vector<std::string> MuIdTypeNames {
      "WMuId",
      "ZMuId",
      "Tight",
      "MuonPOG2012CutBasedIdTight",
      "Loose",
      "WWMuIdV1",
      "WWMuIdV2",
      "WWMuIdV3",
      "WWMuIdV4",
      "NoId",
      "CustomId",
      "MVAID_BDTG_IDIso"
    };
 
    std::vector<MuonTools::EMuIsoType> MuIsoTypes {
      MuonTools::kTrackCalo,                         
      MuonTools::kTrackCaloCombined,                 
      MuonTools::kTrackCaloSliding,                  
      MuonTools::kTrackCaloSlidingNoCorrection,      
      MuonTools::kCombinedRelativeConeAreaCorrected, 
      MuonTools::kCombinedRelativeEffectiveAreaCorrected,
      MuonTools::kCustomIso,                         
      MuonTools::kPFIso,                             
      MuonTools::kPFRadialIso,                       
      MuonTools::kPFIsoBetaPUCorrected,              
      MuonTools::kPFIsoBetaPUCorrectedTight,         
      MuonTools::kPFIsoEffectiveAreaCorrected,       
      MuonTools::kPFIsoNoL,                          
      MuonTools::kNoIso,                             
      MuonTools::kMVAIso_BDTG_IDIso,                 
      MuonTools::kIsoRingsV0_BDTG_Iso,               
      MuonTools::kIsoDeltaR
    };
  
    std::vector<std::string> MuIsoTypeNames {
      "TrackCalo",                         
      "TrackCaloCombined",                   
      "TrackCaloSliding",                  
      "TrackCaloSlidingNoCorrection",      
      "CombinedRelativeConeAreaCorrected", 
      "CombinedRelativeEffectiveAreaCorrected",
      "CustomIso",                         
      "PFIso",                             
      "PFRadialIso",                       
      "PFIsoBetaPUCorrected",              
      "PFIsoBetaPUCorrectedTight",         
      "PFIsoEffectiveAreaCorrected",       
      "PFIsoNoL",                          
      "NoIso",                             
      "MVAIso_BDTG_IDIso",                 
      "IsoRingsV0_BDTG_Iso",               
      "IsoDeltaR"
    };

    //std::vector<std::array<Bool_t, sizeof(MuClassTypes)/sizeof(UInt_t) > > MuClassTypeBits;
    //std::vector<std::array<Bool_t, sizeof(MuIdTypes)/sizeof(UInt_t) > >    MuIdTypeBits;
    //std::vector<std::array<Bool_t, sizeof(MuIsoTypes)/sizeof(UInt_t) > >   MuIsoTypeBits;
    vector< vector<bool> > MuClassTypeBits_;
    vector< vector<bool> > MuIdTypeBits_;
    vector< vector<bool> > MuIsoTypeBits_;
    //Bool_t MuIdTypeBits[sizeof(MuIdTypes)/sizeof(UInt_t)];
    //Bool_t MuIsoTypeBits[sizeof(MuIsoTypes)/sizeof(UInt_t)];
    //unsigned int NClassTypes = sizeof(MuClassTypes)/sizeof(UInt_t);
    //unsigned int NIdTypes = sizeof(MuIdTypes)/sizeof(UInt_t);
    //unsigned int NIsoTypes = sizeof(MuIsoTypes)/sizeof(UInt_t);
    unsigned int NClassTypes = MuClassTypes.size();
    unsigned int NIdTypes    = MuIdTypes.size(); 
    unsigned int NIsoTypes   = MuIsoTypes.size();
    
    unsigned int runNum, lumiSec, evtNum; 
    unsigned int npv;                     
    std::vector<int> charge_;             
    std::vector<TLorentzVector*> fourMomentum_;        // tag, probe 4-vector
    ClassDef(BitwiseMuonNtuples, 0)
  };

}

#endif
