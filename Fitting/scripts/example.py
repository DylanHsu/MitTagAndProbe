import sys
import ROOT

ROOT.gSystem.Load('libRooFit.so')
ROOT.gSystem.Load('libMitTagAndProbeFitting.so')

RooFit = ROOT.RooFit
mithep = ROOT.mithep

source = ROOT.TFile.Open(sys.argv[1])
tree = source.Get('HLTMod/GoodPVFilterMod/MuonIDMod/MuonIDMod/NtuplesMod/events') 

workspace = ROOT.RooWorkspace('workspace')

mass = workspace.factory('mass[0., 200.]')
argset = ROOT.RooArgSet(mass)
dataset = mithep.FittingUtils.createDataSet(tree, argset, "dataset", "T&P dataset")

background = workspace.factory('Exponential::background(mass, c[-0.2,-10.,0.])')
signal = workspace.factory('BreitWigner::signal(mass, m0[91,70,120], w[0.1,0.,40.])')
pdf = workspace.factory('SUM::pdf(nsig[1,0,1000] * signal, nbkg[0,0,1000] * background)')

pdf.fitTo(dataset)

frame = mass.frame()
dataset.plotOn(frame)
pdf.plotOn(frame)

frame.Draw()

sys.stdin.readline() # let the script hang around
