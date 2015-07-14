import ROOT

ROOT.gSystem.Load('libMitAnaTreeMod.so')
ROOT.gSystem.Load('libMitTagAndProbeMods.so')

mithep = ROOT.mithep

analysis = mithep.Analysis()
analysis.SetOutputName('EOverP.root')
analysis.SetUseHLT(False)

analysis.AddFile('/mnt/hadoop/cms/store/user/paus/filefi/032/s12-zll-ptz70-100-v7c/00134196-AC39-E211-A04C-00261894387C.root')
analysis.SetProcessNEvents(2)

eoverP = mithep.EOverPMod('EOverP', 'E/P')
analysis.AddSuperModule(eoverP)

analysis.Run(False)
