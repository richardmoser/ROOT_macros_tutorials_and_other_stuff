#include <iostream>
#include <string>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TVector3.h>
#include <TGraph.h>
#include <TPaveText.h>
using namespace std;
//cycles through events. If detected, adds to a power vs frequency plot
void plotmacro(){

//    TString infile = "/home/rj/RadioScatter/doc/smallmultiscat_0MHz_10W_10ns.root";
//    TString infile = "/home/rj/RadioScatter/doc/multiscat_1MHz_10W_10ns.root";
    TString infile = "/home/rj/RadioScatter/doc/smallmultiscat_0MHz_10W_10ns.root";
    auto ff=TFile::Open(infile, "READ");
//    TFile *outfile = new TFile("/home/rj/RadioScatter/outputfiles/voltage_time_angle.root", "RECREATE");
//    TTree *outtree = new TTree("tree", "test label");
    int rxindex = 0;
    int txindex = 0;
    int antenna = 0;
    int entry = 0;
    auto tree=(TTree*)ff->Get("tree");
    auto event= new RadioScatterEvent();
    tree->SetBranchAddress("event", &event);
    TVector3 n(0,1,0);
    // Shuffled loops way (good for macros)
    int entries = tree->GetEntries();
    int rxs = event->nrx;
    // TODO: make array sizes dynamic
    float **power_array = new float*[entries];
    for(int i = 0; i < entries; ++i){
        power_array[i] = new float[rxs];
    }
    //make a 2d array of size (entries, rxs)
    float **freq_array = new float*[entries];
    for(int i = 0; i < entries; ++i){
        freq_array[i] = new float[rxs];
    }

// auto *freqs = new double[entries][rxs];
    auto *freqs = new double[30][3];
    auto *pows = new double[30][3];
    double frq;
    double pow;
    double thresh = 20e-6;
    cout << "Trigger threshold is: " << thresh << "\n" << endl;
    for(int k = 0; k < tree->GetEntries(); k++){
        tree->GetEntry(k);
        int trig=0,num=0;
        for(int i=0;i<event->ntx;i++){
            for(int j=0;j<event->nrx;j++){
                trig=event->peakV(i,j)>=thresh?1:0;
                if(trig==1){
                    num++;
                    // Meat goes here
                    frq = event->peakFreq(0,j);
                    pow = event->peakPowerW(0,j);
                    freq_array[k][j]=frq;
                    power_array[k][j]=pow;
                 cout << "Event " << k << " triggered on RX " << j << " at " << event->peakV(0,j) << "V ";
                 cout << "with peak frequency " << freq_array[k][j] << "MHz and power "<< pow << "W" << endl;
                }
                else{
                    freq_array[k][j] = 0;
                }
                if(num>=event->nrx){

                }
            }
        }
    }
    double *allfreqs = new double[90];
    double *allpows = new double[90];
    int count = 0;
    for(int entry = 0; entry < tree->GetEntries()-1; entry++){
        for(int rx = 0; rx < event->nrx; rx++){
//            cout << "event " << entry << " freq: " << freq_array[entry][rx] << "MHz, power: " << power_array[entry][rx] << endl;
            allfreqs[count] = freq_array[entry][rx];
            allpows[count]= power_array[entry][rx];
            count++;
        }
    }

    TCanvas *c1 = new TCanvas("c1","TFrqVPow",200,10,1200,1000);
//    c1->SetGrid();
    c1->SetLogy(1);
    const Int_t num = entries * rxs;
    TGraph *gr = new TGraph(num,allfreqs,allpows);
    gr->SetMarkerColor(4);
// gr->SetMarkerStyle(2);
    gr->SetMarkerStyle(20);
    gr->SetTitle("Triggered Event Peak Frequency vs Peak Power");
    gr->GetXaxis()->SetTitle("Peak Frequency (GHz)");
    gr->GetYaxis()->SetTitle("Peak Power (W)");
    gr->Draw("AP");
    c1->Update();
    c1->GetFrame()->SetBorderSize(100);
    c1->Modified();
    c1->Draw();
    c1->SaveAs("/home/rj/new/TriggeredPeakFrequencyVsPower.png");
//
//    auto canvas = new TCanvas("canvas", "t00");
//    //            canvas->Divide(2, 2);
//    //            commented for removal of pane 3&4, uncomment above and comment below for 4 pane TCanvas
//    canvas->Divide(2, 2);
//    canvas->SetWindowSize(1200, 1200);
//    canvas->cd(1)->SetGrid();
//    gPad->SetLeftMargin(.1);
//    gPad->SetBottomMargin(.1);
//
//    canvas->cd(1);
//    TGraph *time_voltage = event->getGraph(rxindex, txindex);
////            TH1 *time_voltage = event->getSpectrum(0,rxindex);
//    time_voltage->GetXaxis()->SetTitle("Time [ns]");
//    time_voltage->GetYaxis()->SetTitle("V");
//    time_voltage->Draw("al");
//    canvas->cd(2);
//    TPaveText *pt = new TPaveText(.05, .1, .95, .9);
//    pt->AddText(Form("Max Voltage: %g", voltmax));
//    pt->AddText(Form("Min Voltage: %g", voltmin));
//    pt->AddText(Form("Position: (%g,%g,%g)", X, Y, X));
//    pt->AddText(Form("Angle: %g Degrees", other_angle_degrees));
//    //            pt->AddText(Form("Other Angle: %g Degrees", (180- (90 + other_angle_degrees))));
//
//    pt->Draw(); // Uncomment to print to screen
//
//    //            canvas->Print(charpath, "PNG"); // uncomment to save PDF to file
//
//    //            uncommented to add pane 3 for GetHistogram
//
//    //            canvas->cd(3);
//    //            double tan_of_angle = tan(other_angle_degrees);
//    //            TFormula *form1 = new TFormula("form1","abs(2 * x)");
//    //            TF1 *sqroot = new TF1("sqroot",Form("%g * x", tan_of_angle),-10,10);
//    //            sqroot->SetParameters(-10,10,1,20);
//    //            sqroot->SetLineColor(4);
//    //            sqroot->SetLineWidth(6);
//    //            sqroot->Draw();
//    //            TPaveLabel *lfunction = new TPaveLabel(5,39,9.8,46,"The sqroot function");
//    //            lfunction->SetFillColor(41);
//    //            lfunction->Draw();
//    //            commented to remove pane 3 for a dual slide TCanvas
//    //            outtree->Write();
////                          1           2           3                   4           5           6             7         8               9
////          plotEvent(int txindex, int rxindex, double noise_flag, int show_geom, int bins, int overlap, int logFlag, double ymin, double ymax){
//    canvas->cd(3);
////            cout << "\033[1;32mnoise setting: " << noise_flag << endl;
//    auto evG=event->getGraph(rxindex, txindex);
//    if(noise_flag>0){
////                evG=TUtilRadioScatter::addNoise(evG, noise_flag);
//        evG=TUtilRadioScatter::addNoise(evG, noise_flag);
//
//    }
//    TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
//    TUtilRadioScatter::style(evG, kBlack, 1, 1);
//    TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN()-1]);
//
////            int bins = 16, overlap = 14;
//    int bins = 32, overlap = 31;
//  //auto spec=TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins*2, 2, logFlag,ymin, ymax);
//    auto spec=TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins*2, 2,   0,     0,    .2);
//    Float_t xmax = 1;
//    Float_t xmin = 0;
////            spec->GetXaxis()->SetRange(0,3000);
//    spec->Draw("colz");
//
//    string path = "/home/rj/RadioScatter/outputfiles/";
//    string filename = "event" + to_string(i) + ".png";
//    string full_path = path + filename;
//    const char *charpath = full_path.c_str();
//    canvas->SaveAs(charpath);
}
