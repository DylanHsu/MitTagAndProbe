import ROOT
import sys

ROOT.gSystem.Load('libMitAnaDataTree.so')
ROOT.gSystem.Load('libMitPhysicsMods.so')
ROOT.gSystem.Load('libMitTagAndProbeMods.so')

from MitAna.TreeMod.bambu import mithep, analysis

hltMod = mithep.HLTMod()
hltMod.SetBitsName('HLTBits')
hltMod.SetTrigObjsName('SingleElectronTriggerObjects')
triggerList = open('electron_triggers_2012.txt')
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

tagElectronIdMod = mithep.ElectronIdMod()
tagElectronIdMod.SetPtMin(25.)
tagElectronIdMod.SetEtaMax(2.4)
tagElectronIdMod.SetIdType(mithep.ElectronTools.kTight)
tagElectronIdMod.SetIsoType(mithep.ElectronTools.kNoIso)
tagElectronIdMod.SetApplyD0Cut(True)
tagElectronIdMod.SetApplyDZCut(True)
tagElectronIdMod.SetWhichVertex(0)
tagElectronIdMod.SetInputName('Electrons')
tagElectronIdMod.SetOutputName('TightElectrons')
tagElectronIdMod.SetPFNoPileupCandidatesName('pfNoPU')
tagElectronIdMod.SetPFPileupCandidatesName('pfPU')

probeElectronIdMod = mithep.ElectronIdMod()
probeElectronIdMod.SetPtMin(25.)
probeElectronIdMod.SetEtaMax(2.4)
probeElectronIdMod.SetIdType(mithep.ElectronTools.kLoose)
probeElectronIdMod.SetIsoType(mithep.ElectronTools.kNoIso)
probeElectronIdMod.SetApplyD0Cut(False)
probeElectronIdMod.SetApplyDZCut(False)
probeElectronIdMod.SetOutputName('LooseElectrons')
probeElectronIdMod.SetPFNoPileupCandidatesName('pfNoPU')
probeElectronIdMod.SetPFPileupCandidatesName('pfPU')

ntuplesMod = mithep.ElectronNtuples('ElectronNtuples', 'Flat ntuples producer')
ntuplesMod.SetTagElectronsName('TightElectrons')
ntuplesMod.SetProbeElectronsName('LooseElectrons')
ntuplesMod.SetTriggerObjectsName('SingleElectronTriggerObjects')

analysis.setSequence(hltMod * goodPVMod * pfPUMod * tagElectronIdMod * probeElectronIdMod * ntuplesMod)
