import ROOT
ROOT.gSystem.Load('libMitAnaDataTree.so')
ROOT.gSystem.Load('libMitPhysicsMods.so')
ROOT.gSystem.Load('libMitTagAndProbeMods.so')
from MitAna.TreeMod.bambu import mithep, analysis

Mods=[]

hltMod = mithep.HLTMod()
hltMod.SetBitsName('HLTBits')
hltMod.SetTrigObjsName('SingleElectronTriggerObjects')
hltMod.AddTrigger('HLT_Ele23_WPLoose_Gsf_v*')
Mods.append(hltMod)

goodPVMod = mithep.GoodPVFilterMod()
goodPVMod.SetMinVertexNTracks(0)
goodPVMod.SetMinNDof(4)
goodPVMod.SetMaxAbsZ(24.0)
goodPVMod.SetMaxRho(2.0)
goodPVMod.SetIsMC(False)
goodPVMod.SetVertexesName('PrimaryVertexes')
Mods.append(goodPVMod)

pfPUMod = mithep.SeparatePileUpMod()
pfPUMod.SetPFNoPileUpName('pfNoPU')
pfPUMod.SetPFPileUpName('pfPU')
Mods.append(pfPUMod)

IdAlgos=[
  ("Tight",                                 mithep.ElectronTools.kTight),             
  ("Loose",                                 mithep.ElectronTools.kLoose),             
  #("Likelihood",                            mithep.ElectronTools.kLikelihood),        
  ("NoId",                                  mithep.ElectronTools.kNoId),              
  ("ZeeId",                                 mithep.ElectronTools.kZeeId),             
  ("VBTFWorkingPointFakeableId",            mithep.ElectronTools.kVBTFWorkingPointFakeableId),
  ("VBTFWorkingPoint95Id",                  mithep.ElectronTools.kVBTFWorkingPoint95Id),
  ("VBTFWorkingPoint90Id",                  mithep.ElectronTools.kVBTFWorkingPoint90Id),
  ("VBTFWorkingPoint85Id",                  mithep.ElectronTools.kVBTFWorkingPoint85Id),
  ("VBTFWorkingPoint80Id",                  mithep.ElectronTools.kVBTFWorkingPoint80Id),
  ("VBTFWorkingPointLowPtId",               mithep.ElectronTools.kVBTFWorkingPointLowPtId),
  ("VBTFWorkingPoint70Id",                  mithep.ElectronTools.kVBTFWorkingPoint70Id),
  #("MVAID_BDTG_NoIPInfo",                   mithep.ElectronTools.kMVAID_BDTG_NoIPInfo),
  #("MVAID_BDTG_WithIPInfo",                 mithep.ElectronTools.kMVAID_BDTG_WithIPInfo),
  #("MVAID_BDTG_IDIsoCombined",              mithep.ElectronTools.kMVAID_BDTG_IDIsoCombined),
  ("HggLeptonTagId",                        mithep.ElectronTools.kHggLeptonTagId),
  ("HggLeptonTagId2012",                    mithep.ElectronTools.kHggLeptonTagId2012),
  ("HggLeptonTagId2012HCP",                 mithep.ElectronTools.kHggLeptonTagId2012HCP),
  #("MVAID_BDTG_IDHWW2012TrigV0",            mithep.ElectronTools.kMVAID_BDTG_IDHWW2012TrigV0),
  #("MVAID_BDTG_IDIsoCombinedHWW2012TrigV4", mithep.ElectronTools.kMVAID_BDTG_IDIsoCombinedHWW2012TrigV4),
  ("Phys14Veto",                            mithep.ElectronTools.kPhys14Veto),
  ("Phys14Loose",                           mithep.ElectronTools.kPhys14Loose),
  ("Phys14Medium",                          mithep.ElectronTools.kPhys14Medium),
  ("Phys14Tight",                           mithep.ElectronTools.kPhys14Tight)
]
IsolationAlgos=[
  ("TrackCalo",	                           mithep.ElectronTools.kTrackCalo),	
  ("TrackJura",	                           mithep.ElectronTools.kTrackJura),	
  ("TrackJuraCombined",	                   mithep.ElectronTools.kTrackJuraCombined),	
  ("TrackJuraSliding",	                       mithep.ElectronTools.kTrackJuraSliding),	
  ("TrackJuraSlidingNoCorrection",            mithep.ElectronTools.kTrackJuraSlidingNoCorrection),
  ("CombinedRelativeConeAreaCorrected",       mithep.ElectronTools.kCombinedRelativeConeAreaCorrected),
  ("NoIso",	                               mithep.ElectronTools.kNoIso),	
  ("PFIso",	                               mithep.ElectronTools.kPFIso),	
  ("PFIsoRhoCorrected",                       mithep.ElectronTools.kPFIsoRhoCorrected),
  ("PFIsoNoL",	                               mithep.ElectronTools.kPFIsoNoL),	
  ("ZeeIso",	                               mithep.ElectronTools.kZeeIso),	
  ("VBTFWorkingPoint95IndividualIso",         mithep.ElectronTools.kVBTFWorkingPoint95IndividualIso),
  ("VBTFWorkingPoint90IndividualIso",         mithep.ElectronTools.kVBTFWorkingPoint90IndividualIso),
  ("VBTFWorkingPoint85IndividualIso",         mithep.ElectronTools.kVBTFWorkingPoint85IndividualIso),
  ("VBTFWorkingPoint80IndividualIso",         mithep.ElectronTools.kVBTFWorkingPoint80IndividualIso),
  ("VBTFWorkingPoint70IndividualIso",         mithep.ElectronTools.kVBTFWorkingPoint70IndividualIso),
  ("VBTFWorkingPoint95CombinedIso",           mithep.ElectronTools.kVBTFWorkingPoint95CombinedIso),
  ("VBTFWorkingPoint90CombinedIso",           mithep.ElectronTools.kVBTFWorkingPoint90CombinedIso),
  ("VBTFWorkingPoint85CombinedIso",           mithep.ElectronTools.kVBTFWorkingPoint85CombinedIso),
  ("VBTFWorkingPoint80CombinedIso",           mithep.ElectronTools.kVBTFWorkingPoint80CombinedIso),
  ("VBTFWorkingPoint70CombinedIso",           mithep.ElectronTools.kVBTFWorkingPoint70CombinedIso),
  ("MVAIso_BDTG_IDIsoCombined",               mithep.ElectronTools.kMVAIso_BDTG_IDIsoCombined),
  ("PFIso_HWW2012TrigV0",                     mithep.ElectronTools.kPFIso_HWW2012TrigV0),
  ("PFIso_HggLeptonTag2012",                  mithep.ElectronTools.kPFIso_HggLeptonTag2012),
  ("PFIso_HggLeptonTag2012HCP",               mithep.ElectronTools.kPFIso_HggLeptonTag2012HCP),
  ("MVAIso_BDTG_IDIsoCombinedHWW2012TrigV4",  mithep.ElectronTools.kMVAIso_BDTG_IDIsoCombinedHWW2012TrigV4),
  ("Phys14VetoIso",                           mithep.ElectronTools.kPhys14VetoIso),
  ("Phys14LooseIso",                          mithep.ElectronTools.kPhys14LooseIso),
  ("Phys14MediumIso",                         mithep.ElectronTools.kPhys14MediumIso),
  ("Phys14TightIso",                          mithep.ElectronTools.kPhys14TightIso)
]
for algo in IdAlgos:
  electronWorker=mithep.ElectronIdMod(algo[0],algo[0])
  electronWorker.SetIsFilterMode(False)
  electronWorker.SetPtMin(20.)
  electronWorker.SetEtaMax(2.4)
  electronWorker.SetIdType(algo[1])
  electronWorker.SetIsoType(mithep.MuonTools.kNoIso)
  electronWorker.SetInputName('Electrons')
  electronWorker.SetOutputName(algo[0])
  electronWorker.SetPFNoPileupCandidatesName('pfNoPU') 
  electronWorker.SetPFPileupCandidatesName('pfPU')
  electronWorker.SetVertexName('PrimaryVertexes')
  electronWorker.SetNonIsolatedMuonsName('Muons')
  electronWorker.SetNonIsolatedElectronsName('Electrons')
  Mods.append(electronWorker)
for algo in IsolationAlgos:
  electronWorker=mithep.ElectronIdMod(algo[0],algo[0])
  electronWorker.SetIsFilterMode(False)
  electronWorker.SetPtMin(20.)
  electronWorker.SetEtaMax(2.4)
  electronWorker.SetIdType(mithep.MuonTools.kNoId)
  electronWorker.SetIsoType(algo[1])
  electronWorker.SetInputName('Electrons')
  electronWorker.SetOutputName(algo[0])
  electronWorker.SetPFNoPileupCandidatesName('pfNoPU') 
  electronWorker.SetPFPileupCandidatesName('pfPU')
  electronWorker.SetVertexName('PrimaryVertexes')
  electronWorker.SetNonIsolatedMuonsName('Muons')
  electronWorker.SetNonIsolatedElectronsName('Electrons')
  Mods.append(electronWorker)

BitwiseElectronNtuplesMod = mithep.BitwiseElectronNtuples('BitwiseElectronNtuples', 'Flat ntuples producer')
for algo in IdAlgos:
  BitwiseElectronNtuplesMod.AddIdFlag(algo[0],algo[1])
for algo in IsolationAlgos:
  BitwiseElectronNtuplesMod.AddIsoFlag(algo[0],algo[1])
Mods.append(BitwiseElectronNtuplesMod)

seq=Mods[0]
for mod in Mods[1:]:
  seq*=mod
analysis.setSequence(seq)

