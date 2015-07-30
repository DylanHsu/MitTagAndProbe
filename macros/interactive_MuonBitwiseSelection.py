import ROOT
import sys

ROOT.gSystem.Load('libMitAnaDataTree.so')
ROOT.gSystem.Load('libMitPhysicsMods.so')
ROOT.gSystem.Load('libMitTagAndProbeMods.so')

#from MitAna.TreeMod.bambu import mithep, analysis
mithep = ROOT.mithep
analysis = mithep.Analysis()
analysis.SetOutputName('ntuples.root')
catalog = mithep.Catalog('/home/cmsprod/catalog')
#dataset = catalog.FindDataset('t2mit/filefi/032', 'r12a-smu-j22-v1', '0000', 1)
dataset = catalog.FindDataset('t2mit/filefi/041', 'SingleMuon+Run2015B-PromptReco-v1+AOD', '0000', 1)
analysis.AddDataset(dataset)
analysis.SetProcessNEvents(10000)

hltMod = mithep.HLTMod()
hltMod.SetBitsName('HLTBits')
hltMod.SetTrigObjsName('SingleMuonTriggerObjects')
triggerList = open('muon_triggers_2012_dhsu.txt')
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

BitwiseMuonNtuplesMod = mithep.BitwiseMuonNtuples('BitwiseMuonNtuples', 'Flat ntuples producer')

analysis.AddSuperModule(hltMod)
hltMod.Add(goodPVMod)
goodPVMod.Add(pfPUMod)
pfPUMod.Add(BitwiseMuonNtuplesMod)

analysis.Run(False)
