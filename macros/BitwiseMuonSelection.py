import ROOT
ROOT.gSystem.Load('libMitAnaDataTree.so')
ROOT.gSystem.Load('libMitPhysicsMods.so')
ROOT.gSystem.Load('libMitTagAndProbeMods.so')
from MitAna.TreeMod.bambu import mithep, analysis

Mods=[]

hltMod = mithep.HLTMod()
hltMod.SetBitsName('HLTBits')
hltMod.SetTrigObjsName('SingleMuonTriggerObjects')
hltMod.AddTrigger('HLT_IsoMu20_v*')
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
  ("Mit2012_WMuId",           mithep.MuonTools.kMit2012_WMuId),
  ("Mit2012_ZMuId",           mithep.MuonTools.kMit2012_ZMuId),
  ("Mit2012_Tight",           mithep.MuonTools.kMit2012_Tight),
  ("Pog2012_CutBasedIDTight", mithep.MuonTools.kPog2012_CutBasedIdTight),
  ("Mit2012_Loose",           mithep.MuonTools.kMit2012_Loose),
  ("Mit2012_WWMuIdV1",        mithep.MuonTools.kMit2012_WWMuIdV1),
  ("Mit2012_WWMuIdV2",        mithep.MuonTools.kMit2012_WWMuIdV2),      
  ("Mit2012_WWMuIdV3",        mithep.MuonTools.kMit2012_WWMuIdV3),      
  ("Mit2012_WWMuIdV4",        mithep.MuonTools.kMit2012_WWMuIdV4),      
  ("Pog2015_Loose" ,          mithep.MuonTools.kPog2015_Loose),      
  ("Pog2015_Medium",          mithep.MuonTools.kPog2015_Medium),         
  ("Pog2015_Tight",           mithep.MuonTools.kPog2015_Tight),        
  ("NoId",                    mithep.MuonTools.kNoId),  
  ("MVAID_BDTG_IDIso",        mithep.MuonTools.kMVAID_BDTG_IDIso)
]
IsolationAlgos=[
  ("TrackCalo",                              mithep.MuonTools.kTrackCalo),
  ("TrackCaloCombined",                      mithep.MuonTools.kTrackCaloCombined),
  ("TrackCaloSliding",                       mithep.MuonTools.kTrackCaloSliding),                
  ("TrackCaloSlidingNoCorrection",           mithep.MuonTools.kTrackCaloSlidingNoCorrection),      
  ("CombinedRelativeConeAreaCorrected",      mithep.MuonTools.kCombinedRelativeConeAreaCorrected), 
  ("CombinedRelativeEffectiveAreaCorrected", mithep.MuonTools.kCombinedRelativeEffectiveAreaCorrected),
  ("PFIso",                                  mithep.MuonTools.kPFIso),                             
  ("PFRadialIso",                            mithep.MuonTools.kPFRadialIso),                       
  ("PFIsoBetaPUCorrected",                   mithep.MuonTools.kPFIsoBetaPUCorrected),              
  ("PFIsoBetaPUCorrectedTight",              mithep.MuonTools.kPFIsoBetaPUCorrectedTight),         
  ("PFIsoEffectiveAreaCorrected",            mithep.MuonTools.kPFIsoEffectiveAreaCorrected),       
  ("PFIsoNoL",                               mithep.MuonTools.kPFIsoNoL),                          
  ("NoIso",                                  mithep.MuonTools.kNoIso),                             
  ("MVAIso_BDTG_IDIso",                      mithep.MuonTools.kMVAIso_BDTG_IDIso),                 
  ("IsoRingsV0_BDTG_Iso",                    mithep.MuonTools.kIsoRingsV0_BDTG_Iso),               
  ("IsoDeltaR",                              mithep.MuonTools.kIsoDeltaR)
]
for algo in IdAlgos:
  muonWorker=mithep.MuonIdMod(algo[0],algo[0])
  muonWorker.SetIsFilterMode(False)
  muonWorker.SetPtMin(20.)
  muonWorker.SetEtaMax(2.4)
  muonWorker.SetIdType(algo[1])
  muonWorker.SetIsoType(mithep.MuonTools.kNoIso)
  muonWorker.SetInputName('Muons')
  muonWorker.SetOutputName(algo[0])
  muonWorker.SetPFNoPileupCandidatesName('pfNoPU') 
  muonWorker.SetPFPileupCandidatesName('pfPU')
  muonWorker.SetVertexName('PrimaryVertexes')
  muonWorker.SetNonIsolatedMuonsName('Muons')
  muonWorker.SetNonIsolatedElectronsName('Electrons')
  Mods.append(muonWorker)
for algo in IsolationAlgos:
  muonWorker=mithep.MuonIdMod(algo[0],algo[0])
  muonWorker.SetIsFilterMode(False)
  muonWorker.SetPtMin(20.)
  muonWorker.SetEtaMax(2.4)
  muonWorker.SetIdType(mithep.MuonTools.kNoId)
  muonWorker.SetIsoType(algo[1])
  muonWorker.SetInputName('Muons')
  muonWorker.SetOutputName(algo[0])
  muonWorker.SetPFNoPileupCandidatesName('pfNoPU') 
  muonWorker.SetPFPileupCandidatesName('pfPU')
  muonWorker.SetVertexName('PrimaryVertexes')
  muonWorker.SetNonIsolatedMuonsName('Muons')
  muonWorker.SetNonIsolatedElectronsName('Electrons')
  Mods.append(muonWorker)

BitwiseMuonNtuplesMod = mithep.BitwiseMuonNtuples('BitwiseMuonNtuples', 'Flat ntuples producer')
for algo in IdAlgos:
  BitwiseMuonNtuplesMod.AddIdFlag(algo[0],algo[1])
for algo in IsolationAlgos:
  BitwiseMuonNtuplesMod.AddIsoFlag(algo[0],algo[1])
Mods.append(BitwiseMuonNtuplesMod)

seq=Mods[0]
for mod in Mods[1:]:
  seq*=mod
analysis.setSequence(seq)
#analysis.setSequence(hltMod * goodPVMod * pfPUMod * BitwiseMuonNtuplesMod)

