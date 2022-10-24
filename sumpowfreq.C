#include <iostream>
#include <TGraph.h>

using namespace std;

//defines a function which returns a TGraph
TGraph* makegraph(int t_window, TH2D *spec){
    int NumFreqBins = spec->GetNbinsX();
    int NumIntensBins = spec->GetNbinsY();
    int binmax = spec->GetMaximumBin(); // bin number of max intensity
    double *pows = new double[NumFreqBins]; // array of frequencies
    double *ybin = new double[NumFreqBins]; // array of y bin numbers
    double_t iterator = 0; // iterator for the for loop
    int i = t_window - 390; // time bin number of the max intensity
    for(int j = 0; j < spec->GetNbinsY(); j++){
        if(j==0){pows[j]=0;}
        else{pows[j]=spec->GetBinContent(i,j);}
        ybin[j] = j*0.015625*1000; // y bin number x YBinWidth * 1000MHz/GHz
        iterator ++;
    }
    TGraph *gr = new TGraph(NumFreqBins, ybin, pows);
    return gr;
}

//defines a function which returns pows
double* power_generator(TH2D *spec, double *pows_in){
    int NumFreqBins = spec->GetNbinsX();
    int NumIntensBins = spec->GetNbinsY();
    int binmax = spec->GetMaximumBin(); // bin number of max intensity
    double *pows = new double[NumFreqBins]; // array of frequencies
    double *retpows = new double[NumFreqBins]; // array of frequencies
    double *ybin = new double[NumFreqBins]; // array of y bin numbers
    double_t iterator = 0; // iterator for the for loop
//    int i = binmax - 390; // time bin number of the max intensity
    int i = 460 - 390;
    for(int j = 0; j < 32; j++){
        if(j==0){pows[j]=0;}
//        else{pows[j]=spec->GetBinContent(i,j) + pows_in[j];
            else{pows[j]=spec->GetBinContent(i,j);
        }
        ybin[j] = j*0.015625*1000; // y bin number x YBinWidth * 1000MHz/GHz
        iterator ++;
    }
    // loop over each entry in pows, add the value of pows_in, then return pows
    for (int k = 0; k < NumFreqBins; k++){
        retpows[k] = pows[k] + 1*pows_in[k];
//        cout << "pows[" << k << "] = " << pows[k] << " retpows[" << k << "] = " << retpows[k] << endl;
    }
    return retpows;



}

void doit() {
    TString infile = "/home/rj/RadioScatter/doc/smallmultiscat_0MHz_10W_10ns.root";
//    TString infile = "/home/rj/RadioScatter/doc/multiscat_0MHz_10W_10ns.root";

    auto ff = TFile::Open(infile, "READ");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->Divide(2, 2);
//    c1->SetWindowSize(1200, 1200);
    c1->SetWindowSize(1200, 800);
    gPad->SetLeftMargin(.1);
    gPad->SetBottomMargin(0);
    c1->cd(1);
    c1->cd(1)->SetLeftMargin(.15);
    c1->cd(1)->SetRightMargin(.2);
    c1->cd(2)->SetLeftMargin(.15);
    c1->cd(3)->SetLeftMargin(.15);
    c1->cd(3)->SetRightMargin(.2);
    c1->cd(4)->SetLeftMargin(.15);

    int rxindex = 0;
    int txindex = 0;
    int antenna = 0;
    int entry = 0;
    auto tree = (TTree *) ff->Get("tree");
    auto event = new RadioScatterEvent();
    tree->SetBranchAddress("event", &event);

    int entries = tree->GetEntries();
    tree->GetEntry(entry); // get the first entry
    auto evG = event->getGraph(rxindex, txindex); // generates graph evG
    TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
    TUtilRadioScatter::style(evG, kBlack, 1, 1);
    TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN() - 1]);
    int bins = 32, overlap = 31;
    auto spec = TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins * 2, 2, 0, 0, .2); // generates spectrogram spec
    c1->SetLogy(0); // set y axis to linear
    c1->cd(1); //moves to canvas 1, upper left
    c1->cd(1)->SetLogy(0); // set y axis to linear
    spec->SetStats(0); // removes stats box
    spec->Draw("colz"); // draws spectrogram to canvas 1 upper left

    int  time_window = 479; // time window of interest

    auto mg = new TMultiGraph(); // creates a multigraph
    c1->cd(2)->SetLogy(1); // set y axis to logarithmic

    int NumFreqBins=spec->GetNbinsX();
    int NumTimeBins=spec->GetNbinsY();
    double *pows = new double[NumFreqBins];
    double *ybin = new double[NumFreqBins];
    double_t iterator = 0;
    int binmax = spec->GetMaximumBin(); // bin number of max intensity
    cout << "binmax = " << binmax << endl;
    cout << "NumFreqBins = " << NumFreqBins << endl;
    cout << "NumTimeBins = " << NumTimeBins << endl;

    int i=460 - 390;
    for(int j = 0; j < spec->GetNbinsY(); j++){
        if(j==0){
            pows[j]=0;
        }
        else{
            pows[j]=spec->GetBinContent(i,j);
        }
        ybin[j] = j*.00625*1000; // y bin number x .2GHz/32bins * 1000MHz/GHz
        iterator ++;
    }
    TGraph *gr = new TGraph(NumFreqBins, ybin, pows);
    gr->GetYaxis()->SetRangeUser(1*pow(10,-18), 1*pow(10,-15));
    gr->GetYaxis()->SetLimits(1*pow(10,-18), 1*pow(10,-15));
    gr->SetMarkerColor(4);
    gr->SetMarkerSize(.5);
    gr->SetMarkerStyle(21);
    gr->GetXaxis()->SetLimits(0,200);
    gr->SetTitle(Form("Frequency vs Power at time %dns", 390+i));
    gr->GetXaxis()->SetTitle("");
    gr->GetYaxis()->SetTitle("WGHz^{-1}");
    double *newpows = new double[NumFreqBins];
    for (int k = 0; k < entries -1; k++){
        tree->GetEntry(k); // get the first entry
        auto evG = event->getGraph(rxindex, txindex); // generates graph evG
        TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
        TUtilRadioScatter::style(evG, kBlack, 1, 1);
        TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN() - 1]);
        int bins = 32, overlap = 31;
        auto spec2 = TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins * 2, 2, 0, 0, .2); // generates spectrogram spec
        newpows = power_generator(spec2, pows);
//
//        auto canvas = new TCanvas("canvas", "t00");
//        spec->Draw("colz");
//        string path = "/home/rj/RadioScatter/outputfiles/";
//        string filename = "spec_event_" + to_string(k) + ".png";
//        string full_path = path + filename;
//        const char *charpath = full_path.c_str();
//        canvas->SaveAs(charpath);
    }


    c1->cd(2);
    mg->Add(gr, "ACP");

    mg->GetXaxis()->SetLimits(0,200);
    mg->GetXaxis()->SetTitle("Frequency (MHz)");
    mg->GetYaxis()->SetTitle("Power (WGHz^{-1} x 10^{-12})");
    mg->SetTitle(Form("Frequency vs Power at time %dns on ", 390+i));

//    mg->Draw("ACP");
    gr->Draw("ACP");

//    newpows[31] = 1*pow(10,-15);


    c1->cd(4);
    c1->cd(4)->SetLogy(1);
    TGraph *gr1 = new TGraph(NumFreqBins, ybin, newpows);
//    gr1->GetYaxis()->SetRangeUser(1*pow(10,-18), 1*pow(10,-15));
    gr1->GetYaxis()->SetLimits(1*pow(10,-18), 1*pow(10,-15));
    gr1->SetMarkerColor(4);
    gr1->SetMarkerSize(.5);
    gr1->SetMarkerStyle(21);
    gr1->GetXaxis()->SetLimits(0,200);
    gr1->SetTitle("Frequency vs Power summed over all events");
    gr1->GetXaxis()->SetTitle("");
    gr1->GetYaxis()->SetTitle("WGHz^{-1}");
    gr1->Draw("ACP");
    cout << gr1->GetMaximum() << endl;


//    TLegend *leg = new TLegend(0.25, 0.6, 0.6, 1);
//    leg->SetFillColor(0);
//    leg->SetHeader("Frequency vs Power\n");
//    leg->AddEntry(gr5, Form("%dns", binmax-6), "p");
//    leg->AddEntry(gr3, Form("%dns", binmax-4), "p");
//    leg->AddEntry(gr1, Form("%dns", binmax-2), "p");
//    leg->AddEntry(gr0, Form("%dns", binmax), "p");
//    leg->AddEntry(gr2, Form("%dns", binmax+2), "p");
//    leg->AddEntry(gr4, Form("%dns", binmax+4), "p");
//    leg->AddEntry(gr6, Form("%dns", binmax+6), "p");
//    leg->Draw();


//    c1->SaveAs("/home/rj/RadioScatter/outputfiles/sumpowfreq.png");

}