
int glob_to_x(TH2* hist, int global){
    int x_bins = hist->GetNbinsX();
    int temp = global % (x_bins + 2);
    // x bin value is global % the total number of x bins (GetNbinsX doesn't count either buffer bin)
    return temp;
}

int glob_to_y(TH2* hist, int global){
    int x_bins = hist->GetNbinsX();
    int temp = global / (x_bins + 2);
    // x bin value is global % the total number of x bins (GetNbinsX doesn't count either buffer bin)
    return temp;
}
double* power_generator(TH2D *spec, double *pows_in, double_t loop_i){
    int NumFreqBins = spec->GetNbinsX();
    int NumIntensBins = spec->GetNbinsY();
    int binmax = spec->GetMaximumBin(); // bin number of max intensity
    int xmax = glob_to_x(spec, binmax); // x bin number of max intensity
    double *pows2 = new double[NumFreqBins]; // array of frequencies
    double *retpows = new double[NumFreqBins]; // array of frequencies
    double *ybin = new double[NumFreqBins]; // array of y bin numbers
    double_t iterator = 0; // iterator for the for loop
//    int i = binmax - 390; // time bin number of the max intensity
//    int i = 460 - 390;
    int i = xmax;
    for(int j = 0; j < spec->GetNbinsY(); j++){
        if(j==0){
            pows2[j]=0;
        }
        else{
            pows2[j]=spec->GetBinContent(i,j);
        }
//        ybin[j] = j*.00625*1000*2.5; // y bin number x .2GHz/32bins * 1000MHz/GHz * 2.5 to account for overlap
        ybin[j] = j*.0625*1000*2.5; // y bin number x .2GHz/32bins * 1000MHz/GHz * 2.5 to account for overlap

        iterator ++;
    }
    // loop over each entry in pows, add the value of pows_in, then return pows
    for (int k = 0; k < NumFreqBins; k++){
        retpows[k] = pows2[k] + 1*pows_in[k];
//        cout << "pows[" << k << "] = " << pows[k] << " retpows[" << k << "] = " << retpows[k] << endl;
    }
    int intk = loop_i;
    spec->GetYaxis()->SetRangeUser(0, 5);
//    spec->GetZaxis()->SetRangeUser(5*pow(10,-17),1*pow(10,-14));
    spec->SetStats(0); // removes stats box

//    auto c2 = new TCanvas("c2", "c2", 800, 600);
//    spec->Draw("colz");
//    string path = "/home/rj/RadioScatter/outputfiles/";
//    string filename = "spec_wide_" + to_string(intk) + ".png";
//    string full_path = path + filename;
//    const char *charpath = full_path.c_str();
//    c2->SaveAs(charpath);
//
//    TH2D *spec2 = (TH2D*)spec->Clone();
//    auto c3 = new TCanvas("c2", "c2", 800, 600);
//    spec2->GetYaxis()->SetRangeUser(0, 1);
//    spec2->Draw("colz");
//    string path2 = "/home/rj/RadioScatter/outputfiles/";
//    string filename2 = "spec_narrow_" + to_string(intk) + ".png";
//    string full_path2 = path + filename2;
//    const char *charpath2 = full_path2.c_str();
//    c3->SaveAs(charpath2);

    return retpows;
}


void doit(){
    TString infile = "/home/rj/RadioScatter/outputfiles/multiscat_0GHz_10W_10ns.root";

    auto ff = TFile::Open(infile, "READ");

    int rxindex = 0;
    int txindex = 0;
    int antenna = 0;
    int entry = 0;
    auto tree=(TTree*)ff->Get("tree");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->Divide(3, 2);
    //    c1->SetWindowSize(1200, 1200);
    c1->SetWindowSize(2000, 1000);
    gPad->SetLeftMargin(.1);
    gPad->SetBottomMargin(0);
    c1->cd(1);
//    c1->cd(1)->SetLeftMargin(.15);
//    c1->cd(1)->SetRightMargin(.2);
//    c1->cd(2)->SetLeftMargin(.15);
//    c1->cd(3)->SetLeftMargin(.15);
//    c1->cd(3)->SetRightMargin(.2);
//    c1->cd(4)->SetLeftMargin(.15);

    auto event = new RadioScatterEvent();
    tree->SetBranchAddress("event", &event);

    int entries = tree->GetEntries();
    tree->GetEntry(entry); // get the first entry
    auto evG = event->getGraph(rxindex, txindex); // generates graph evG
    TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
    TUtilRadioScatter::style(evG, kBlack, 1, 1);
    TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN() - 1]);
    int bins = 32, overlap = 31;
//    int bins = 64, overlap = 62;

    auto spec = TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins * 2, 2, 0, 0, .2); // generates spectrogram spec
    c1->SetLogy(0); // set y axis to linear
    c1->cd(1); //moves to canvas 1, upper left
    c1->cd(1)->SetLogy(0); // set y axis to linear
    spec->GetYaxis()->SetRangeUser(0, 0.5);
    c1->cd(1)->SetLogz(1); // set z axis to log
//    spec->GetZaxis()->SetRangeUser(5*pow(10,-12),1*pow(10,-10));
//    spec->GetZaxis()->SetRangeUser(5*pow(10,-17),1*pow(10,-14));
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

    int spec_start_time; // time at which the spectrogram "spec" starts
    if(fmod(evG->GetX()[0], 1) >=.5){ // C++ rounds down for all numbers, so
        spec_start_time = evG->GetX()[0] + 1; // if the decimal is >= .5, add 1 to the integer part
    }
    else{
        spec_start_time = evG->GetX()[0]; // otherwise, just use the integer part
    }

    int binmax = spec->GetMaximumBin(); // bin number of max intensity
    int xmax = glob_to_x(spec, binmax); // x bin number of max intensity
    cout << spec->GetNbinsX() << " " << spec->GetNbinsY() << endl;
    cout << "max, global bin number = " << binmax << endl;
    cout << "max, x bin number = " << xmax << endl;
    cout << "start time = " << spec_start_time << endl;
    cout << "max time = " << spec_start_time + xmax << endl;
    cout << "NumFreqBins = " << NumFreqBins << endl;
    cout << "NumTimeBins = " << NumTimeBins << endl;

    int i = xmax;
    for(int j = 0; j < spec->GetNbinsY(); j++){
        if(j==0){
            pows[j]=0;
        }
        else{
            pows[j]=spec->GetBinContent(i,j);
        }
        ybin[j] = j*.0625*1000*2.5; // y bin number x .2GHz/32bins * 1000MHz/GHz * 2.5 to account for overlap
        iterator ++;
    }

        cout << spec->GetNbinsY()*.00625*1 << endl;

    TGraph *gr = new TGraph(NumFreqBins, ybin, pows);
//    gr->GetYaxis()->SetRangeUser(1*pow(10,-18), 1*pow(10,-8));
    gr->GetYaxis()->SetRangeUser(1*pow(10,-18), 5*pow(10,-9));
//    gr->GetYaxis()->SetLimits(1*pow(10,-18), 1*pow(10,-15));
    gr->SetMarkerColor(4);
    gr->SetMarkerSize(.5);
    gr->SetMarkerStyle(21);
//    gr->GetXaxis()->SetLimits(0,200);
    gr->GetXaxis()->SetLimits(0,5000);
    gr->SetTitle(Form("Frequency vs asdfasdf Power at time %dns", (i + spec_start_time))); // set title of graph with the time of maximum intensity
    gr->GetXaxis()->SetTitle("Frequency (MHz)");
    gr->GetYaxis()->SetTitle("Power WGHz^{-1}");
    double *newpows = new double[NumFreqBins];

    // vvv
    for(int j = 0; j < spec->GetNbinsY(); j++){
        newpows[j]=0;
    }
    iterator ++;

    for (int k = 0; k < entries -1; k++){
        tree->GetEntry(k); // get the first entry
        auto evG = event->getGraph(rxindex, txindex); // generates graph evG
        TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
        TUtilRadioScatter::style(evG, kBlack, 1, 1);
        TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN() - 1]);
        int bins = 32, overlap = 31;
        auto spec2 = TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins * 2, 2, 0, 0, .2); // generates spectrogram spec
        newpows = power_generator(spec2, newpows, k);
//        cout << k << endl;
    }

    c1->cd(2);
    mg->Add(gr, "ACP");

    mg->GetXaxis()->SetLimits(0,200);
    mg->GetXaxis()->SetTitle("Frequency (MHz)");
    mg->GetYaxis()->SetTitle("Power (WGHz^{-1} x 10^{-12})");
    mg->SetTitle(Form("Frequency vs Power at time %dns on ", 390+i));

    //    mg->Draw("ACP");
    gr->Draw("ACP");

    c1->cd(4);
    c1->cd(4)->SetLogy(1);
    TGraph *gr1 = new TGraph(NumFreqBins, ybin, newpows);
    gr1->GetYaxis()->SetRangeUser(1*pow(10,-18), 1*pow(10,-12));
    // gr1->GetYaxis()->SetLimits(1*pow(10,-18), 1*pow(10,-15));
    gr1->GetXaxis()->SetRangeUser(0,500);
    gr1->GetXaxis()->SetLimits(0,500);
    gr1->SetMarkerColor(4);
    gr1->SetMarkerSize(.5);
    gr1->SetMarkerStyle(21);
    // gr1->GetXaxis()->SetLimits(0,200);
    gr1->SetTitle("Frequency vs Power summed over all events");
    gr1->GetXaxis()->SetTitle("");
    gr1->GetYaxis()->SetTitle("WGHz^{-1}");
    gr1->Draw("ACP");
    cout << gr1->GetMaximum() << endl;

    // spec->GetZaxis()->SetRangeUser(1*pow(10,-18), 1*pow(10,-15));
    // spec->Draw("colz"); // draws spectrogram to canvas 1 upper left


    c1->Draw();



    //    c1->SaveAs("/home/rj/RadioScatter/outputfiles/sumpowfreq.png");

}