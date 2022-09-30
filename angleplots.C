#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TGraph.h>

using namespace std;

void angleplots() {

    TString infile = "/home/rj/RadioScatter/outputfiles/voltage_time_angle.root";
    //    TString infile = "/home/rj/RadioScatter/doc/output_test_100MHz_10W_4ns.root";
    auto ff = TFile::Open(infile, "READ");
    auto tree = (TTree *) ff->Get("tree");

    auto *c1 = new TCanvas();


    float_t X, Y, Z, voltmin, voltmax, other_angle_degrees;
//    double Y;
//    double Z;
//    double voltmax;
//    double voltmin;
//    double_t other_angle_degrees;
    tree->SetBranchAddress("X", &X);
    tree->SetBranchAddress("Y", &Y);
    tree->SetBranchAddress("Z", &Z);
    tree->SetBranchAddress("voltmax", &voltmax);
    tree->SetBranchAddress("voltmin", &voltmin);
    tree->SetBranchAddress("other_angle_degrees", &other_angle_degrees);

    auto entries = tree->GetEntries();
    float_t voltmaxarray[entries], other_angle_degreesarray[entries];
//    c1->Divide(2, 1);
//    c1->cd(1)->SetGrid();
//    gPad->SetLeftMargin(.1);
//    gPad->SetBottomMargin(.1);


//    TH1F *hist = new TH1F("hist", "Histogram", 100, 0, 100);


    for(int i = 0; i < entries; i++) {
        tree->GetEntry(i);
        voltmaxarray[i] = voltmax;
        other_angle_degreesarray[i] = other_angle_degrees;
//        cout << i << " " << other_angle_degrees << " Degrees: " << endl;
//        hist->Fill(other_angle_degrees);

    }
//    ROOT::RDataFrame fr(“tree”, ”home/rj/RadioScatter/outputfiles/voltage_time_angle.root”);
//    fr.Foreach([&](float angle){cout << angle << “\n”; }{“other_angle_degrees”});”).
//    hist->Draw("*P");
//
//    c1->cd(2);
    auto *graph = new TGraph(entries, other_angle_degreesarray, voltmaxarray);
    graph->GetXaxis()->SetTitle("Angle (Degrees)");
    graph->GetYaxis()->SetTitle("Max Voltage");
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(2);
//    graph->GetXaxis()->SetLimits(-1,90);

    c1->SetWindowSize(3000, 1500);
    graph->Draw("*AP");

}
//TODO: create hybrid macro(s) of showerAxisAngles.C and angleplots.C that doesn't need to write to a new .ROOT file