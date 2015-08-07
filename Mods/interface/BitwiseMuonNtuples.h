#ifndef MIT_TAGANDPROBE_MODS_BITWISE_MUON_NTUPLES_MOD_H
#define MIT_TAGANDPROBE_MODS_BITWISE_MUON_NTUPLES_MOD_H
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/MuonCol.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitPhysics/Utils/interface/MuonTools.h"
#include "MitPhysics/Mods/interface/MuonIdMod.h"
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
    void AddIdFlag(std::string name, MuonTools::EMuIdType IdType);
    void AddIsoFlag(std::string name, MuonTools::EMuIsoType IsoType);
  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fAllMuonsName;
    TString fTriggerObjectsName;
    TString fPVName;  
    TTree* fNtuplesTree;
    TTree* fPropertiesTree;
    TH1F* fIdHisto, *fIsoHisto;
    
    vector<std::string> MuIdTypeNames;
    vector<std::string> MuIsoTypeNames;
    vector<MuonTools::EMuIdType> MuIdTypes;
    vector<MuonTools::EMuIsoType> MuIsoTypes;
    vector< vector<bool> > MuIdTypeBits_;
    vector< vector<bool> > MuIsoTypeBits_;
    vector<bool> MuMCMatch_;
    unsigned int NIdTypes    = 0; 
    unsigned int NIsoTypes   = 0;
    
    unsigned int runNum, lumiSec, evtNum; 
    unsigned int npv;                     
    std::vector<int> charge_;             
    std::vector<TLorentzVector*> fourMomentum_;
    ClassDef(BitwiseMuonNtuples, 0)
  };

}

#endif
