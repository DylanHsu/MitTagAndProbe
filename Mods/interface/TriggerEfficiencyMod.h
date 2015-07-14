#ifndef MITEXAMPLE_MODS_TRIGGEREFFICIENCYMOD_H
#define MITEXAMPLE_MODS_TRIGGEREFFICIENCYMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitAna/DataTree/interface/PhotonCol.h"
#include "MitAna/DataTree/interface/ElectronCol.h"
#include "MitAna/DataTree/interface/SuperClusterCol.h"

#include "TString.h"
#include "TH1D.h"

namespace mithep {
  
  class TriggerEfficiencyMod : public BaseMod {
  public:
    TriggerEfficiencyMod(char const* name = "TriggerEfficiencyMod", char const* title = "Trigger efficiency calculator");
    ~TriggerEfficiencyMod();

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fTriggerObjectsName;
    TString fPhotonsName;
    TString fElectronsName;
    TString fSuperClustersName;

    mithep::TriggerObjectArr const* fTriggerObjects;
    mithep::PhotonArr const* fPhotons;
    mithep::ElectronArr const* fElectrons;
    mithep::SuperClusterArr const* fSuperClusters;

    TH1D* hDenom;
    TH1D* hNumer;

    ClassDef(TriggerEfficiencyMod, 0)
  };

}

#endif
