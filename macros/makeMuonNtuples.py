import ROOT

ROOT.gSystem.Load('libMitAnaDataTree.so')
ROOT.gSystem.Load('libMitPhysicsMods.so')
ROOT.gSystem.Load('libMitTagAndProbeMods.so')

from MitAna.TreeMod.bambu import mithep, analysis

hltMod = mithep.HLTMod()
hltMod.SetBitsName('HLTBits')
hltMod.SetTrigObjsName('SingleMuonTriggerObjects')
triggerList = open('muon_triggers_2012.txt')
for line in triggerList:
    hltMod.AddTrigger(line.strip())

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
tagMuonIdMod.SetPtMin(25.)
tagMuonIdMod.SetEtaMax(2.4)
tagMuonIdMod.SetIdType(mithep.MuonTools.kMuonPOG2012CutBasedIdTight)
tagMuonIdMod.SetIsoType(mithep.MuonTools.kPFIsoBetaPUCorrectedTight)
tagMuonIdMod.SetApplyD0Cut(True)
tagMuonIdMod.SetApplyDZCut(True)
tagMuonIdMod.SetWhichVertex(0)
tagMuonIdMod.SetInputName('Muons')
tagMuonIdMod.SetOutputName('TightMuons')
tagMuonIdMod.SetPFNoPileupCandidatesName('pfNoPU')
tagMuonIdMod.SetPFPileupCandidatesName('pfPU')

probeMuonIdMod = mithep.MuonIdMod()
probeMuonIdMod.SetPtMin(25.)
probeMuonIdMod.SetEtaMax(2.4)
probeMuonIdMod.SetIdType(mithep.MuonTools.kMuonPOG2012CutBasedIdTight)
probeMuonIdMod.SetIsoType(mithep.MuonTools.kPFIsoBetaPUCorrectedTight)
probeMuonIdMod.SetApplyD0Cut(False)
probeMuonIdMod.SetApplyDZCut(False)
probeMuonIdMod.SetOutputName('LooseMuons')
probeMuonIdMod.SetPFNoPileupCandidatesName('pfNoPU')
probeMuonIdMod.SetPFPileupCandidatesName('pfPU')

ntuplesMod = mithep.MuonNtuples('MuonNtuples', 'Flat ntuples producer')
ntuplesMod.SetTagMuonsName('TightMuons')
ntuplesMod.SetProbeMuonsName('LooseMuons')
ntuplesMod.SetTriggerObjectsName('SingleMuonTriggerObjects')

analysis.setSequence(hltMod * goodPVMod * pfPUMod * tagMuonIdMod * probeMuonIdMod * ntuplesMod)
