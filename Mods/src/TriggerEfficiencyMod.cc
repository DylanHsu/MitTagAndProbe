#include "MitTagAndProbe/Mods/interface/TriggerEfficiencyMod.h"

#include "MitAna/DataTree/interface/Names.h"

#include "TVector2.h"

#include <iostream>
#include <cstring>

ClassImp(mithep::TriggerEfficiencyMod)

namespace mithep {

  TriggerEfficiencyMod::TriggerEfficiencyMod(char const* name, char const* title) :
    BaseMod(name, title),
    fTriggerObjectsName(TString::Format("%sArr", Names::gkHltObjBrn)),
    fPhotonsName(Names::gkPhotonBrn),
    fElectronsName(Names::gkElectronBrn),
    fSuperClustersName("SuperClusters"),
    fTriggerObjects(0),
    fPhotons(0),
    fElectrons(0),
    fSuperClusters(0),
    hDenom(0),
    hNumer(0)
  {
  }

  TriggerEfficiencyMod::~TriggerEfficiencyMod()
  {
  }

  void
  TriggerEfficiencyMod::Process()
  {
    std::vector<TriggerObject const*> singleEG25;
    for (unsigned iO(0); iO != fTriggerObjects->GetEntries(); ++iO) {
      TriggerObject const& to(*fTriggerObjects->At(iO));

      if (std::strcmp(to.ModuleName(), "hltL1sL1SingleEG25") == 0)
        singleEG25.push_back(&to);
    }

    if (singleEG25.size() == 0)
      return;

    LoadBranch(fPhotonsName);
    LoadBranch(fElectronsName);
    LoadBranch(fSuperClustersName);

    std::vector<SuperCluster const*> probes;

    for (unsigned iP(0); iP != fPhotons->GetEntries(); ++iP) {
      Photon const& photon(*fPhotons->At(iP));

      if (photon.HadOverEmTow() > 0. || photon.R9() < 0.9 ||
          photon.PFChargedHadronIso() > 5. || photon.PFNeutralHadronIso() > 10. ||
          photon.PFPhotonIso() > 10.)
        continue;

      probes.push_back(photon.SCluster());

      // for (unsigned iCand(0); iCand != fPhotons->GetEntries(); ++iCand) {
      //   if (iCand == iP)
      //     continue;

      //   Photon const& tagCand(*fPhotons->At(iCand));
      //   SuperCluster const* sc(tagCand.SCluster());
      //   if (!sc) {
      //     std::cerr << "Photon with no SC: " << iCand << std::endl;
      //     continue;
      //   }

      //   unsigned iE(0);
      //   for (; iE != fElectrons->GetEntries(); ++iE) {
      //     Electron const& electron(*fElectrons->At(iE));
      //     if (electron.SCluster() != sc)
      //       continue;

      //     if (electron.PassTightID() < 0.5)
      //       sc = 0;
      //   }
      //   if (iE == fElectrons->GetEntries() || !sc)
      //     continue;

      //   double mass((tagCand.Mom() + photon.Mom()).M());

      //   if (mass > 81. && mass < 101.) {
      //     probes.push_back(photon.SCluster());
      //     break;
      //   }
      // }
    }

    for (SuperCluster const* probe : probes) {
      hDenom->Fill(probe->Et());
      for (TriggerObject const* to : singleEG25) {
        double dEta(to->Eta() - probe->Eta());
        double dPhi(TVector2::Phi_mpi_pi(to->Phi() - probe->Phi()));
        if (std::sqrt(dEta * dEta + dPhi * dPhi) < 0.3) {
          hNumer->Fill(probe->Et());
          break;
        }
      }
    }
  }

  void
  TriggerEfficiencyMod::SlaveBegin()
  {
    AddTH1(hDenom, "denom", "Denominator", 40, 0., 80.);
    AddTH1(hNumer, "numer", "Numerator", 40, 0., 80.);
    
    ReqBranch(fPhotonsName, fPhotons);
    ReqBranch(fElectronsName, fElectrons);
    ReqBranch(fSuperClustersName, fSuperClusters);

    fTriggerObjects = static_cast<mithep::TriggerObjectArr const*>(FindPublicObj(fTriggerObjectsName));
  }

  void
  TriggerEfficiencyMod::SlaveTerminate()
  {
  }

}
