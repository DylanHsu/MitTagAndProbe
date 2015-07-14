import sys
import ROOT
import os

ROOT.gSystem.Load('libRooFit.so')
ROOT.gSystem.Load('libMitTagAndProbeFitting.so')

source = ROOT.TFile.Open('hadded_histos_846fs_tnp_26-06-2015.root')
massPtPassing = source.Get('h_mass_pt_passing')
massPtFailing = source.Get('h_mass_pt_failing')
massEtaPassing = source.Get('h_mass_eta_passing')
massEtaFailing = source.Get('h_mass_eta_failing')
massPvPassing = source.Get('h_mass_pv_passing')
massPvFailing = source.Get('h_mass_pv_failing')

################################
# EFFICIENCY AS FUNCTION OF PT #
################################

#n_ptbins = 10
#d_pt = 10

#massPtPassing.RebinY(int(massPtPassing.GetYaxis().GetNbins() * d_pt / massPtPassing.GetYaxis().GetXmax()))
#massPtFailing.RebinY(int(massPtFailing.GetYaxis().GetNbins() * d_pt / massPtFailing.GetYaxis().GetXmax()))

#pt_0 = massPtPassing.FindFirstBinAbove(19.9,2)

#ptPassYield = ROOT.TH1F("ptPassYield", "ptPassYield",n_ptbins,60,120)
#ptAllYield = ROOT.TH1F("ptAllYield", "ptAllYield",n_ptbins,60,120)

#for nbin in range(pt_0, pt_0 + n_ptbins * d_pt):
#    workspace = ROOT.RooWorkspace('workspace')
#    mass = workspace.factory('mass[60,120]')
#    argList = ROOT.RooArgList(mass)

#    massPassing = ROOT.TH1D(massPtPassing.ProjectionX("massPassing",nbin,nbin,"o"))
#    massFailing = ROOT.TH1D(massPtFailing.ProjectionX("massFailing",nbin,nbin,"o"))
#    
#    ptPassingDataset = ROOT.RooDataHist("ptPassingDataset", "ptPassingDataset", argList, massPassing, 1.0)
#    ptFailingDataset = ROOT.RooDataHist("ptFailingDataset", "ptFailingDataset", argList, massFailing, 1.0)
#
#    ptPassingBackground = workspace.factory('Exponential::ptPassingBackground(mass, pt_passing_c[-0.2,-10.,0.])')
#    ptPassingBW = workspace.factory('BreitWigner::ptPassingBW(mass, pt_passing_mean[91.1876], pt_passing_width[2.4952])')
#    ptPassingCB = workspace.factory('CBShape::ptPassingCB(mass, pt_passing_x0[0], pt_passing_sigma[0,3], pt_passing_alpha[5,0,10], pt_passing_n[7,0,10])')
#    ptPassingSignal = workspace.factory('FCONV::ptPassingSignal(mass, ptPassingBW, ptPassingCB)')
#    ptModelPassing = workspace.factory('SUM::ptModelPassing(pt_nsigpass[10e6, 0, 13e6] * ptPassingSignal, pt_nbkgpass[3e6, 0, 13e6] * ptPassingBackground)')
#
#    ptFailingBackground = workspace.factory('Exponential::ptFailingBackground(mass, pt_failing_c[-0.2,-10.,0.])')
#    ptFailingBW = workspace.factory('BreitWigner::ptFailingBW(mass, pt_failing_mean[91.1876], pt_failing_width[2.4952])')
#    ptFailingCB = workspace.factory('CBShape::ptFailingCB(mass, pt_failing_x0[0], pt_failing_sigma[0,3], pt_failing_alpha[5,0,10], pt_failing_n[7,0,10])')
#    ptFailingSignal = workspace.factory('FCONV::ptFailingSignal(mass, ptFailingBW, ptFailingCB)')
#    ptModelFailing = workspace.factory('SUM::ptModelFailing(pt_nsigfail[8e6, 0, 13e6] * ptFailingSignal, pt_nbkgfail[5e6, 0, 13e6] * ptFailingBackground)')
#
#    ptModelPassing.fitTo(ptPassingDataset)
#    ptModelFailing.fitTo(ptFailingDataset)
#    ptPassYield.SetBinContent(nbin, workspace.arg('pt_nsigpass').getVal())
#    ptPassYield.SetBinError(nbin, workspace.arg('pt_nsigpass').getError())
#    ptAllYield.SetBinContent(nbin, workspace.arg('pt_nsigpass').getVal() + workspace.arg('pt_nsigfail').getVal())
#    ptAllYield.SetBinError(nbin, ( (workspace.arg('pt_nsigpass').getError()) ** (2.) + (workspace.arg('pt_nsigfail').getError()) ** (2.) ) ** (0.5))
#
#    ptPassFrame = mass.frame()
#    ptPassingDataset.plotOn(ptPassFrame)
#    ptModelPassing.plotOn(ptPassFrame)
#    #ptPassCanvas = ROOT.TCanvas("ptPassCanvas", "ptPassCanvas")
#    #ptPassCanvas.cd()
#    #ptPassFrame.Draw()
#
#    ptFailFrame = mass.frame()
#    ptFailingDataset.plotOn(ptFailFrame)
#    ptModelFailing.plotOn(ptFailFrame)
    #ptFailCanvas = ROOT.TCanvas("ptFailCanvas", "ptFailCanvas")
    #ptFailCanvas.cd()
    #ptFailFrame.Draw()

    #wait = input("")

#pt_efficiency = ROOT.TEfficiency(ptPassYield, ptAllYield)
#
#efficiencyPt = ROOT.TH1F("efficiencyPt", "efficiencyPt",n_ptbins,60,120)
#efficiencyPt.SetTitle("Efficiency as function of p_{T}")
#efficiencyPt.SetXTitle("Invariant di-lepton mass [GeV / c^{2}]")
#
#for bin in range(1, n_ptbins):
#    efficiencyPt.SetBinContent(bin, pt_efficiency.GetEfficiency(bin))
#    efficiencyPt.SetBinError(bin, pt_efficiency.GetEfficiencyErrorLow(bin))
#
#ptEfficiencyCanvas = ROOT.TCanvas("ptEfficiencyCanvas", "ptEfficiencyCanvas")
#ptEfficiencyCanvas.cd()
#efficiencyPt.Draw()
#ptEfficiencyCanas.Print('ptEfficiency.png')

#################################
# EFFICIENCY AS FUNCTION OF ETA #
#################################

# This rebinning gives 10 bins of width 1 in the range [-2.5, 2.5]
massEtaPassing.RebinY(50)
massEtaFailing.RebinY(50)

etaPassYield = ROOT.TH1F("etaPassYield", "etaPassYield", 10, -2.5, 2.5)
etaAllYield = ROOT.TH1F("etaAllYield", "etaAllYield", 10, -2.5, 2.5)
etaPassChiSquare = ROOT.TH1F("etaPassChiSquare", "etaPassChiSquare", 10, -2.5, 2.5)
etaFailChiSquare = ROOT.TH1F("etaFailChiSquare", "etaFailChiSquare", 10, -2.5, 2.5)

for bin in range(1, 11):
    workspace = ROOT.RooWorkspace('workpace')
    mass = workspace.factory('mass[60,120]')
    argList = ROOT.RooArgList(mass)

    massPassing = ROOT.TH1D(massEtaPassing.ProjectionX("massPassing",bin,bin,"o"))
    massFailing = ROOT.TH1D(massEtaFailing.ProjectionX("massFailing",bin,bin,"o"))
    passEntries = workspace.factory('passEntries[' + str(massPassing.GetEntries()) + ']')
    failEntries = workspace.factory('failEntries[' + str(massFailing.GetEntries()) + ']')

    etaPassingDataset = ROOT.RooDataHist("etaPassingDataset", "etaPassingDataset", argList, massPassing, 1.0)
    etaFailingDataset = ROOT.RooDataHist("etaFailingDataset", "etaFailingDataset", argList, massFailing, 1.0)

    etaPassingBackground = workspace.factory('Exponential::etaPassingBackground(mass, eta_passing_c[-0.05,-10,0.])')
    etaPassingBW = workspace.factory('BreitWigner::etaPassingBW(mass, eta_passing_mean[91.1876], eta_passing_width[2.4952])')
    etaPassingCB = workspace.factory('CBShape::etaPassingCB(mass, eta_passing_x0[0], eta_passing_sigma[0,3], eta_passing_alpha[1.7,0,10], eta_passing_n[1.7,0,10])')
    etaPassingSignal = workspace.factory('FCONV::etaPassingSignal(mass, etaPassingBW, etaPassingCB)')
    etaModelPassing = workspace.factory('SUM::etaModelPassing(eta_nsigpass['+str(0.8*passEntries.getVal())+', 0, '+str(passEntries.getVal())+'] * etaPassingSignal, eta_nbkgpass['+str(0.2*passEntries.getVal())+', 0, '+str(passEntries.getVal())+'] * etaPassingBackground)')

    etaFailingBackground = workspace.factory('Exponential::etaFailingBackground(mass, eta_failing_c[-0.05,-10.,0.])')
    etaFailingBW = workspace.factory('BreitWigner::etaFailingBW(mass, eta_failing_mean[91.1876], eta_failing_width[2.4952])')
    etaFailingCB = workspace.factory('CBShape::etaFailingCB(mass, eta_failing_x0[0], eta_failing_sigma[0,3], eta_failing_alpha[1.7,0,10], eta_failing_n[1.7,0,10])')
    etaFailingSignal = workspace.factory('FCONV::etaFailingSignal(mass, etaFailingBW, etaFailingCB)')
    etaModelFailing = workspace.factory('SUM::etaModelFailing(eta_nsigfail['+str(0.6*failEntries.getVal()) + ', 0, '+str(failEntries.getVal())+'] * etaFailingSignal, eta_nbkgfail['+str(0.4*failEntries.getVal())+', 0, '+str(failEntries.getVal())+'] * etaFailingBackground)')

    etaModelPassing.fitTo(etaPassingDataset)
    etaModelFailing.fitTo(etaFailingDataset)
    etaPassYield.SetBinContent(bin, workspace.arg('eta_nsigpass').getVal())
    etaPassYield.SetBinError(bin, workspace.arg('eta_nsigpass').getError())
    etaAllYield.SetBinContent(bin, workspace.arg('eta_nsigpass').getVal() + workspace.arg('eta_nsigfail').getVal())
    etaAllYield.SetBinError(bin, ((workspace.arg('eta_nsigpass').getError())**(2.) + (workspace.arg('eta_nsigfail').getError())**(2.))**(0.5))

    etaPassFrame = mass.frame()
    etaPassingDataset.plotOn(etaPassFrame)
    etaModelPassing.plotOn(etaPassFrame)
    #etaPassCanvas = ROOT.TCanvas("etaPassCanvas", "etaPassCanvas")
    #etaPassCanvas.cd()
    #etaPassFrame.Draw()
    etaPassChiSquare.SetBinContent(bin, etaPassFrame.chiSquare(6))

    etaFailFrame = mass.frame()
    etaFailingDataset.plotOn(etaFailFrame)
    etaModelFailing.plotOn(etaFailFrame)
    #etaFailCanvas = ROOT.TCanvas("etaFailCanvas", "etaFailCanvas")
    #etaFailCanvas.cd()
    #etaFailFrame.Draw()
    etaFailChiSquare.SetBinContent(bin, etaFailFrame.chiSquare(6))

    #wait = input("")

eta_efficiency = ROOT.TEfficiency(etaPassYield, etaAllYield)

efficiencyEta = ROOT.TH1F("efficiencyEta", "efficiencyEta", 10, -2.5, 2.5)
efficiencyEta.SetTitle("Efficiency as function of Eta")
efficiencyEta.SetXTitle("Eta")
ROOT.gStyle.SetOptStat(0)

for bin in range(1, 11):
    print eta_efficiency.GetEfficiency(bin)
    efficiencyEta.SetBinContent(bin, eta_efficiency.GetEfficiency(bin))
    efficiencyEta.SetBinError(bin, eta_efficiency.GetEfficiencyErrorLow(bin))

etaEfficiencyCanvas = ROOT.TCanvas("etaEfficiencyCanvas", "etaEfficiencyCanvas")
etaEfficiencyCanvas.cd()
efficiencyEta.Draw()
etaEfficiencyCanvas.Print('etaEfficiency.png')

etaChiSquareCanvas = ROOT.TCanvas("etaChiSquareCanvas", "etaChiSquareCanvas")
etaChiSquareCanvas.cd()
etaPassChiSquare.SetLineColor(4)
etaFailChiSquare.SetLineColor(2)
etaPassChiSquare.Draw()
etaFailChiSquare.Draw('same')
etaChiSquareCanvas.Print('etaChiSquare.png')

################################
# EFFICIENCY AS FUNCTION OF PV #
################################

# This rebinning gives 20 bins of width 5 in the range [0, 100]
massPvPassing.RebinY(50)
massPvFailing.RebinY(50)

pvPassYield = ROOT.TH1F("pvPassYield", "pvPassYield", 8, 0, 40)
pvAllYield = ROOT.TH1F("pvAllYield", "pvAllYield", 8, 0, 40)
pvPassChiSquare = ROOT.TH1F("pvPassChiSquare", "pvPassChiSquare", 8, 0, 40)
pvFailChiSquare = ROOT.TH1F("pvFailChiSquare", "pvFailChiSquare", 8, 0, 40)

for bin in range(1, 9):
    workspace = ROOT.RooWorkspace('workpace')
    mass = workspace.factory('mass[60,120]')
    argList = ROOT.RooArgList(mass)

    massPassing = ROOT.TH1D(massPvPassing.ProjectionX("massPassing",bin,bin,"o"))
    massFailing = ROOT.TH1D(massPvFailing.ProjectionX("massFailing",bin,bin,"o"))
    passEntries = workspace.factory('passEntries[' + str(massPassing.GetEntries()) + ']')
    failEntries = workspace.factory('failEntries[' + str(massFailing.GetEntries()) + ']')


    pvPassingDataset = ROOT.RooDataHist("pvPassingDataset", "pvPassingDataset", argList, massPassing, 1.0)
    pvFailingDataset = ROOT.RooDataHist("pvFailingDataset", "pvFailingDataset", argList, massFailing, 1.0)

    pvPassingBackground = workspace.factory('Exponential::pvPassingBackground(mass, pv_passing_c[-0.2,-10,0.])')
    pvPassingBW = workspace.factory('BreitWigner::pvPassingBW(mass, pv_passing_mean[91.1876], pv_passing_width[2.4952])')
    pvPassingCB = workspace.factory('CBShape::pvPassingCB(mass, pv_passing_x0[0], pv_passing_sigma[0,3], pv_passing_alpha[1.7,0,10], pv_passing_n[1.7,0,10])')
    pvPassingSignal = workspace.factory('FCONV::pvPassingSignal(mass, pvPassingBW, pvPassingCB)')
    pvModelPassing = workspace.factory('SUM::pvModelPassing(pv_nsigpass['+str(0.8*passEntries.getVal())+', 0, '+str(passEntries.getVal())+'] * pvPassingSignal, pv_nbkgpass['+str(0.2*passEntries.getVal())+', 0, '+str(passEntries.getVal())+'] * pvPassingBackground)')

    pvFailingBackground = workspace.factory('Exponential::pvFailingBackground(mass, pv_failing_c[-0.2,-10.,0.])')
    pvFailingBW = workspace.factory('BreitWigner::pvFailingBW(mass, pv_failing_mean[91.1876], pv_failing_width[2.4952])')
    pvFailingCB = workspace.factory('CBShape::pvFailingCB(mass, pv_failing_x0[0], pv_failing_sigma[0,3], pv_failing_alpha[1.7,0,10], pv_failing_n[1.7,0,10])')
    pvFailingSignal = workspace.factory('FCONV::pvFailingSignal(mass, pvFailingBW, pvFailingCB)')
    pvModelFailing = workspace.factory('SUM::pvModelFailing(pv_nsigfail['+str(0.5*failEntries.getVal())+', 0, '+str(failEntries.getVal())+'] * pvFailingSignal, pv_nbkgfail['+str(0.5*failEntries.getVal())+', 0, '+str(failEntries.getVal())+'] * pvFailingBackground)')

    pvModelPassing.fitTo(pvPassingDataset)
    pvModelFailing.fitTo(pvFailingDataset)
    pvPassYield.SetBinContent(bin, workspace.arg('pv_nsigpass').getVal())
    pvPassYield.SetBinError(bin, workspace.arg('pv_nsigpass').getError())
    pvAllYield.SetBinContent(bin, workspace.arg('pv_nsigpass').getVal() + workspace.arg('pv_nsigfail').getVal())
    pvAllYield.SetBinError(bin, ((workspace.arg('pv_nsigpass').getError()) ** (2.) + (workspace.arg('pv_nsigfail').getError()) ** (2.) ) ** (0.5))

    pvPassFrame = mass.frame()
    pvPassingDataset.plotOn(pvPassFrame)
    pvModelPassing.plotOn(pvPassFrame)
    #pvPassCanvas = ROOT.TCanvas("pvPassCanvas", "pvPassCanvas")
    #pvPassCanvas.cd()
    #pvPassFrame.Draw()
    #passChiSquare = pvPassFrame.chiSquare()
    pvPassChiSquare.SetBinContent(bin, pvPassFrame.chiSquare(6))

    pvFailFrame = mass.frame()
    pvFailingDataset.plotOn(pvFailFrame)
    pvModelFailing.plotOn(pvFailFrame)
    #pvFailCanvas = ROOT.TCanvas("pvFailCanvas", "pvFailCanvas")
    #pvFailCanvas.cd()
    #pvFailFrame.Draw()
    #failChiSquare = pvFailFrame.chiSquare()
    pvFailChiSquare.SetBinContent(bin, pvFailFrame.chiSquare(6))

    #wait = input("")

pv_efficiency = ROOT.TEfficiency(pvPassYield, pvAllYield)

efficiencyPv = ROOT.TH1F("efficiencyPv", "efficiencyPv", 8, 0, 40)
efficiencyPv.SetTitle("Efficiency as function of PV")
efficiencyPv.SetXTitle("Number of primary vertices")
ROOT.gStyle.SetOptStat(0)

for bin in range(1, 9):
    efficiencyPv.SetBinContent(bin, pv_efficiency.GetEfficiency(bin))
    efficiencyPv.SetBinError(bin, pv_efficiency.GetEfficiencyErrorLow(bin))

pvEfficiencyCanvas = ROOT.TCanvas("pvEfficiencyCanvas", "pvEfficiencyCanvas")
pvEfficiencyCanvas.cd()
efficiencyPv.Draw()
pvEfficiencyCanvas.Print('pvEfficiency.png')

pvChiSquareCanvas = ROOT.TCanvas("pvChiSquareCanvas", "pvChiSquareCanvas")
pvChiSquareCanvas.cd()
pvPassChiSquare.SetLineColor(4)
pvFailChiSquare.SetLineColor(2)
pvPassChiSquare.Draw()
pvFailChiSquare.Draw('same')
pvChiSquareCanvas.Print('pvChiSquare.png')

sys.stdin.readline()
