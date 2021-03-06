#include "MitTagAndProbe/Mods/interface/EOverPMod.h"
#include "MitTagAndProbe/Mods/interface/MuonNtuples.h"
#include "MitTagAndProbe/Mods/interface/ElectronNtuples.h"
#include "MitTagAndProbe/Mods/interface/BitwiseMuonNtuples.h"
#include "MitTagAndProbe/Mods/interface/BitwiseElectronNtuples.h"
#include "MitTagAndProbe/Mods/interface/TriggerEfficiencyMod.h"
#include <vector>
#include "TLorentzVector.h"

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::EOverPMod+;
#pragma link C++ class mithep::MuonNtuples+;
#pragma link C++ class mithep::BitwiseMuonNtuples+;
#pragma link C++ class mithep::BitwiseElectronNtuples+;
#pragma link C++ class mithep::ElectronNtuples+;
#pragma link C++ class mithep::TriggerEfficiencyMod+;
#pragma link C++ class vector< vector<bool> >+;
#pragma link C++ class vector< TLorentzVector* >+;

#endif
