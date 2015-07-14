import sys
import ROOT

ROOT.gSystem.Load('libRooFit.so')
ROOT.gSystem.Load('libMitTagAndProbeFitting.so')

source = ROOT.TFile.Open('hadded_histos_846fs_tnp_26-06-2015.root')
globalPassing = source.Get('h_global_mass_passing')
globalFailing = source.Get('h_global_mass_failing')
globalPassing.Rebin(4)
globalFailing.Rebin(4)

workspace = ROOT.RooWorkspace('workspace')

mass = workspace.factory('mass[60,120]')
arglist = ROOT.RooArgList(mass)
passingDataset = ROOT.RooDataHist("passingDataset", "passingDataset", arglist, globalPassing, 1.0)
failingDataset = ROOT.RooDataHist("failingDataset", "failingDataset", arglist, globalFailing, 1.0)

####################################################################################
# FITTING MODEL                                                                    #
# Background - Decaying exponential                                                #
# Signal - Convolution of Breit-Wigner with Crystal Ball shape. The Breit-Wigner   #
#          is fixed at the Z mass and width, and the Crystal Ball has four         #
#          floating parameters to account for detector effects.                    #
####################################################################################


failingBackground = workspace.factory('Exponential::failingBackground(mass, failing_c[-0.2,-10.,0.])')
failingBW = workspace.factory('BreitWigner::failingBW(mass, failing_mean[91.1876], failing_width[2.4952])')
failingCB = workspace.factory('CBShape::failingCB(mass, failing_x0[0], failing_sigma[0,3], failing_alpha[5,0,10], failing_n[7,0,10])')
failingSignal = workspace.factory('FCONV::failingSignal(mass, failingBW, failingCB)')
# Fit global failing distribution
modelFailing = workspace.factory('SUM::modelFailing(nsigfail[8e6, 0, 13e6] * failingSignal, nbkgfail[5e6, 0, 13e6] * failingBackground)')
modelFailing.fitTo(failingDataset)
failingFrame = mass.frame()
failingFrame.SetTitle("Tag and failing probe muon pairs")
failingFrame.SetXTitle("Invariant di-lepton mass [GeV / c^{2}]")
failingDataset.plotOn(failingFrame)
modelFailing.plotOn(failingFrame)
failingCanvas = ROOT.TCanvas("failingCanvas","failingCanvas")
failingCanvas.cd()
failingFrame.Draw()
failingCanvas.Print('globalFailing.png')

passingBackground = workspace.factory('Exponential::passingBackground(mass, c[-0.2,-10.,0.])')
passingBW = workspace.factory('BreitWigner::passingBW(mass, mean[91.1876], width[2.4952])')
passingCB = workspace.factory('CBShape::passingCB(mass, x0[0], sigma[0,3], alpha[5,0,10], n[7,0,10])')
passingSignal = workspace.factory('FCONV::passingSignal(mass, passingBW, passingCB)')
modelPassing = workspace.factory('SUM::modelPassing(nsigpass[10e6, 0, 13e6] * passingSignal, nbkgpass[3e6, 0, 13e6] * passingBackground)')
# Fit global passing distribution
modelPassing.fitTo(passingDataset)
passingFrame = mass.frame()
passingFrame.SetTitle("Tag and passing probe muon pairs")
passingFrame.SetXTitle("Invariant di-lepton mass [GeV / c^{2}]")
passingDataset.plotOn(passingFrame)
modelPassing.plotOn(passingFrame)
passingCanvas = ROOT.TCanvas("passingCanvas","passingCanvas")
passingCanvas.cd()
passingFrame.Draw()
passingCanvas.Print('globalPassing.png')

# Compute global efficiency using a TEfficiency
passingYield = ROOT.TH1F("passingYield","passingYield",1,60,120)
allYield = ROOT.TH1F("allYield","allYield",1,60,120)
passingYield.SetBinContent(1,workspace.arg('nsigpass').getVal())
passingYield.SetBinError(1,workspace.arg('nsigpass').getError())
allYield.SetBinContent(1,workspace.arg('nsigpass').getVal() + workspace.arg('nsigfail').getVal())
allYield.SetBinError(1,((workspace.arg('nsigpass').getError())**(2.) + (workspace.arg('nsigfail').getError())**(2.)) ** (0.5))

efficiency = ROOT.TEfficiency(passingYield, allYield)
print efficiency.GetEfficiency(1)
print efficiency.GetEfficiencyErrorLow(1)
print efficiency.GetEfficiencyErrorUp(1)

sys.stdin.readline()
