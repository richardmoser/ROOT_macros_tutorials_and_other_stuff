#include <iostream>
#include <TGraph.h>

using namespace std;

//defines a function which returns a TGraph
TGraph* makegraph(int t_window, TH2D *spec){
    int NumFreqBins = spec->GetNbinsX();
    int NumIntensBins = spec->GetNbinsY();
    int binmax = spec->GetMaximumBin(); // bin number of max intensity
    double *freqs = new double[NumFreqBins]; // array of frequencies
    double *ybin = new double[NumFreqBins]; // array of y bin numbers
    double_t iterator = 0; // iterator for the for loop
    int i = t_window - 390; // time bin number of the max intensity
    for(int j = 0; j < spec->GetNbinsY(); j++){
        if(j==0){freqs[j]=0;}
        else{freqs[j]=spec->GetBinContent(i,j);}
        ybin[j] = j*0.015625*1000; // y bin number x YBinWidth * 1000MHz/GHz
//     ybin[j] = j*.00625*1000; // y bin number x .2GHz/32bins * 1000MHz/GHz -- seems not correct
// TODO: verify scale factor
//        cout << 390+i << " " << ybin[j] << " " << freqs[j] << endl;
        iterator ++;
    }
    TGraph *gr = new TGraph(NumFreqBins, ybin, freqs);
    return gr;
}

void doit() {
    TString infile = "/home/rj/RadioScatter/doc/smallmultiscat_0MHz_10W_10ns.root";
    auto ff = TFile::Open(infile, "READ");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->Divide(2, 2);
    c1->SetWindowSize(2400, 2400);

    gPad->SetLeftMargin(.1);
    gPad->SetBottomMargin(.1);
    c1->cd(1);
    c1->cd(1)->SetLeftMargin(.15);
    c1->cd(1)->SetRightMargin(.2);
    c1->cd(2)->SetLeftMargin(.15);

    int rxindex = 0;
    int txindex = 0;
    int antenna = 0;
    int entry = 0;
    auto tree = (TTree *) ff->Get("tree");
    auto event = new RadioScatterEvent();
    tree->SetBranchAddress("event", &event);
    tree->GetEntry(29);

    auto evG = event->getGraph(rxindex, txindex);
    TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
    TUtilRadioScatter::style(evG, kBlack, 1, 1);
    TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN() - 1]);
    int bins = 32, overlap = 31;
    auto spec = TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins * 2, 2, 0, 0, .2);
    c1->SetLogy(0);
// evG->Draw();
    c1->cd(1);
    c1->cd(1)->SetLogy(0);
    spec->SetStats(0);
    spec->Draw("colz");

    int  time_window = 479;
    int i = time_window - 390;

    auto mg = new TMultiGraph();
    c1->cd(2)->SetLogy(1);
    int binmax = spec->GetMaximumBin()-390; // bin number of max intensity
    cout << "max bin number: " << binmax << "ns" << endl; // 390 is the time bin number of the first bin
    auto gr0 = makegraph(binmax, spec); gr0->SetMarkerStyle(20);
    auto gr1 = makegraph(binmax-2, spec); gr1->SetMarkerStyle(21);
    auto gr2 = makegraph(binmax+2, spec); gr2->SetMarkerStyle(22);
    auto gr3 = makegraph(binmax-4, spec); gr3->SetMarkerStyle(23);
    auto gr4 = makegraph(binmax+4, spec); gr4->SetMarkerStyle(24);
    auto gr5 = makegraph(binmax-6, spec); gr5->SetMarkerStyle(25);
    auto gr6 = makegraph(binmax+6, spec); gr6->SetMarkerStyle(26);
    gr1->GetYaxis()->SetRangeUser(1*pow(10,-16.5), 1*pow(10,-11));
    c1->cd(2);
    mg->Add(gr0, "ACP");
    mg->Add(gr1, "ACP");
    mg->Add(gr2, "ACP");
    mg->Add(gr3, "ACP");
    mg->Add(gr4, "ACP");
    mg->Add(gr5, "ACP");
    mg->Add(gr6, "ACP");
    mg->GetXaxis()->SetLimits(0,200);
    mg->GetXaxis()->SetTitle("Frequency (MHz)");
    mg->GetYaxis()->SetTitle("Power (WGHz^{-1} x 10^{-12})");
    mg->SetTitle(Form("Frequency vs Power at time %dns", 390+i));

    mg->Draw("A pmc plc");

    c1->cd(4);
    TLegend *leg = new TLegend(0.25, 0.6, 0.6, 1);
    leg->SetFillColor(0);
    leg->SetHeader("Frequency vs Power\n");
    leg->AddEntry(gr5, Form("%dns", binmax-6+390), "p");
    leg->AddEntry(gr3, Form("%dns", binmax-4+390), "p");
    leg->AddEntry(gr1, Form("%dns", binmax-2+390), "p");
    leg->AddEntry(gr0, Form("%dns", binmax+390), "p");
    leg->AddEntry(gr2, Form("%dns", binmax+2+390), "p");
    leg->AddEntry(gr4, Form("%dns", binmax+4+390), "p");
    leg->AddEntry(gr6, Form("%dns", binmax+6+390), "p");
    leg->Draw();

    c1->SaveAs("/home/rj/RadioScatter/outputfiles/powerfreq.png");

}