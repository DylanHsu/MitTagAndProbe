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
    MuonTools::EMuClassType MuClassTypes[10]={
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
   
    std::string MuClassTypeNames[10] = {
      "MuonClass_All",
      "MuonClass_Global",
      "MuonClass_GlobalorTracker",
      "MuonClass_GlobalTracker",
      "MuonClass_Sta",
      "MuonClass_TrackerMuon",
      "MuonClass_CaloMuon",
      "MuonClass_TrackerBased",
      "MuonClass_GlobalOnly",
      "MuonClass_PFGlobalorTracker"
    };
    MuonTools::EMuIdType MuIdTypes[12] = {
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

    std::string MuIdTypeNames[12]= {
      "MuonId_WMuId",
      "MuonId_ZMuId",
      "MuonId_Tight",
      "MuonId_MuonPOG2012CutBasedIdTight",
      "MuonId_Loose",
      "MuonId_WWMuIdV1",
      "MuonId_WWMuIdV2",
      "MuonId_WWMuIdV3",
      "MuonId_WWMuIdV4",
      "MuonId_NoId",
      "MuonId_CustomId",
      "MuonId_MVAID_BDTG_IDIso"
    };
 
    MuonTools::EMuIsoType MuIsoTypes[17] = {
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
  
    std::string MuIsoTypeNames[17] = {
      "MuonIso_TrackCalo",                         
      "MuonIso_TrackCaloCombined",                   
      "MuonIso_TrackCaloSliding",                  
      "MuonIso_TrackCaloSlidingNoCorrection",      
      "MuonIso_CombinedRelativeConeAreaCorrected", 
      "MuonIso_CombinedRelativeEffectiveAreaCorrected",
      "MuonIso_CustomIso",                         
      "MuonIso_PFIso",                             
      "MuonIso_PFRadialIso",                       
      "MuonIso_PFIsoBetaPUCorrected",              
      "MuonIso_PFIsoBetaPUCorrectedTight",         
      "MuonIso_PFIsoEffectiveAreaCorrected",       
      "MuonIso_PFIsoNoL",                          
      "MuonIso_NoIso",                             
      "MuonIso_MVAIso_BDTG_IDIso",                 
      "MuonIso_IsoRingsV0_BDTG_Iso",               
      "MuonIso_IsoDeltaR"
    };

    unsigned int MuClassTypeBits[sizeof(MuClassTypes)/sizeof(UInt_t)];
    unsigned int MuIdTypeBits[sizeof(MuIdTypes)/sizeof(UInt_t)];
    unsigned int MuIsoTypeBits[sizeof(MuIsoTypes)/sizeof(UInt_t)];
    unsigned int NClassTypes = sizeof(MuClassTypes)/sizeof(UInt_t);
    unsigned int NIdTypes = sizeof(MuIdTypes)/sizeof(UInt_t);
    unsigned int NIsoTypes = sizeof(MuIsoTypes)/sizeof(UInt_t);
    
    unsigned int runNum, lumiSec, evtNum;   // event ID
    unsigned int npv;                       // number of primary vertices
    unsigned int pass;                      // whether probe passes requirements
    int          charge;              // tag, probe charge
    float mass;
    TLorentzVector *fourMomentum=0;        // tag, probe 4-vector
    ClassDef(BitwiseMuonNtuples, 0)
  };

}

#endif
