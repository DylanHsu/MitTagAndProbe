import ROOT

ROOT.gSystem.Load('libMitAnaDataTree.so')
ROOT.gSystem.Load('libMitPhysicsMods.so')
ROOT.gSystem.Load('libMitTagAndProbeMods.so')

from MitAna.TreeMod.bambu import mithep, analysis

hltMod = mithep.HLTMod()
hltMod.SetBitsName('HLTBits')
hltMod.SetTrigObjsName('SingleMuonTriggerObjects')
hltMod.AddTrigger("HLT_IsoMu27_v*")
#triggerList = open('muon_triggers_2012.txt')
#for line in triggerList:
#    hltMod.AddTrigger(line.strip())

goodPVMod = mithep.GoodPVFilterMod()
goodPVMod.SetMinVertexNTracks(0)
goodPVMod.SetMinNDof(4)
goodPVMod.SetMaxAbsZ(24.0)
goodPVMod.SetMaxRho(2.0)
goodPVMod.SetIsMC(False)
goodPVMod.SetVertexesName('PrimaryVertexes')

pfPUMod = mithep.SeparatePileUpMod()
pfPUMod.SetPFNoPileUpName('pfNoPU')
pfPUMod.SetPFPileUpName('pfPU')

tagMuonIdMod = mithep.MuonIdMod()
#tagMuonIdMod.SetPtMin(25.)
#tagMuonIdMod.SetEtaMax(2.4)
tagMuonIdMod.SetIdType(mithep.MuonTools.kPog2015_Tight)
tagMuonIdMod.SetIsoType(mithep.MuonTools.kPFIsoBetaPUCorrectedTight)
tagMuonIdMod.SetApplyD0Cut(True)
tagMuonIdMod.SetApplyDZCut(True)
tagMuonIdMod.SetWhichVertex(0)
tagMuonIdMod.SetInputName('Muons')
tagMuonIdMod.SetOutputName('TagMuons')
tagMuonIdMod.SetPFNoPileupCandidatesName('pfNoPU')
tagMuonIdMod.SetPFPileupCandidatesName('pfPU')

passingProbeMuonIdMod = mithep.MuonIdMod()
#passingProbeMuonIdMod.SetPtMin(25.)
#passingProbeMuonIdMod.SetEtaMax(2.4)
passingProbeMuonIdMod.SetIdType(mithep.MuonTools.kPog2015_Tight)
passingProbeMuonIdMod.SetIsoType(mithep.MuonTools.kPFIsoBetaPUCorrectedTight)
passingProbeMuonIdMod.SetApplyD0Cut(True)
passingProbeMuonIdMod.SetApplyDZCut(True)
passingProbeMuonIdMod.SetWhichVertex(0)
passingProbeMuonIdMod.SetInputName('Muons')
passingProbeMuonIdMod.SetOutputName('PassingProbeMuons')
passingProbeMuonIdMod.SetPFNoPileupCandidatesName('pfNoPU')
passingProbeMuonIdMod.SetPFPileupCandidatesName('pfPU')


probeMuonIdMod = mithep.MuonIdMod()
#probeMuonIdMod.SetPtMin(25.)
#probeMuonIdMod.SetEtaMax(2.4)
probeMuonIdMod.SetIdType(mithep.MuonTools.kPog2015_Loose)
probeMuonIdMod.SetIsoType(mithep.MuonTools.kPFIsoBetaPUCorrectedTight)
probeMuonIdMod.SetApplyD0Cut(False)
probeMuonIdMod.SetApplyDZCut(False)
probeMuonIdMod.SetInputName('Muons')
probeMuonIdMod.SetOutputName('ProbeMuons')
probeMuonIdMod.SetPFNoPileupCandidatesName('pfNoPU')
probeMuonIdMod.SetPFPileupCandidatesName('pfPU')

ntuplesMod = mithep.MuonNtuples('MuonNtuples', 'Flat ntuples producer')
ntuplesMod.SetTagMuonsName('TagMuons')
ntuplesMod.SetPassingProbeMuonsName('PassingProbeMuons')
ntuplesMod.SetProbeMuonsName('ProbeMuons')
ntuplesMod.SetTriggerObjectsName('SingleMuonTriggerObjects')

analysis.setSequence(hltMod * goodPVMod * pfPUMod * tagMuonIdMod * passingProbeMuonIdMod * probeMuonIdMod * ntuplesMod)
