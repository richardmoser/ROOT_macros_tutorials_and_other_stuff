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

void regularmacro(){

//    TString infile = "/home/rj/RadioScatter/doc/multiscat_0MHz_10W_10ns.root";
    TString infile = "/home/rj/RadioScatter/doc/multiscat_1MHz_10W_10ns.root";
    auto ff=TFile::Open(infile, "READ");
    TFile *outfile = new TFile("/home/rj/RadioScatter/outputfiles/voltage_time_angle.root", "RECREATE");
    TTree *outtree = new TTree("tree", "test label");

    int rxindex = 0;
    int txindex = 0;
    int antenna = 0;
    int entry = 0;
//    string draw;
    string draw = "y";
//    string draw = "n";

//    cout << "Draw graphics? (y/n) " << endl;
//    cin >> draw;
//    auto ff=TFile::Open(infile, "READ");
    auto tree=(TTree*)ff->Get("tree");
    auto event= new RadioScatterEvent();
    tree->SetBranchAddress("event", &event);
    TVector3 n(0,1,0);

    float_t X;
    float_t Y;
    float_t Z;
    float voltmax;
    float voltmin;
    float other_angle_degrees;
    double_t other_angle_rad;

    outtree->Branch("X", &X, "X/F");
    outtree->Branch("Y", &Y, "Y/F");
    outtree->Branch("Z", &Z, "Z/F");
    outtree->Branch("voltmin", &voltmin, "voltmin/F");
    outtree->Branch("voltmax", &voltmax, "voltmax/F");
    outtree->Branch("other_angle_degrees", &other_angle_degrees, "other_angle_degrees/F");
    cout

    double noise_flag = 0;
    cout << "enter a noise level (.00001 is a good start)" << endl;
//    noise_flag = 0.00001;

    cin >> noise_flag;
    for(int i = 0; i < tree->GetEntries(); ++i){
//    for(int i = 0; i < 1; ++i){
        tree->GetEntry(i);
        TVector3 shower_angle = event->direction + event->position;
        TVector3 shower_position = event->position;
        X = shower_position.X();
        Y = shower_position.Y();
        Z = shower_position.Z();
        other_angle_rad = asin(shower_angle.Dot(n) / (shower_angle.Mag() * n.Mag()));
        other_angle_degrees = (other_angle_rad * (180.0 / 3.141592653589793238463));

        TGraph *time_voltage = event->getGraph(rxindex, txindex);
        voltmax = time_voltage->GetHistogram()->GetMaximum();
        voltmin = time_voltage->GetHistogram()->GetMinimum();
        outtree->Fill();


        if (draw == "y" or draw == "Y") {
            auto canvas = new TCanvas("canvas", "t00");
            //            canvas->Divide(2, 2);
            //            commented for removal of pane 3&4, uncomment above and comment below for 4 pane TCanvas
            canvas->Divide(2, 2);
            canvas->SetWindowSize(1200, 1200);
            canvas->cd(1)->SetGrid();
            gPad->SetLeftMargin(.1);
            gPad->SetBottomMargin(.1);

            canvas->cd(1);
            TGraph *time_voltage = event->getGraph(rxindex, txindex);
//            TH1 *time_voltage = event->getSpectrum(0,rxindex);
            time_voltage->GetXaxis()->SetTitle("Time [ns]");
            time_voltage->GetYaxis()->SetTitle("V");
            time_voltage->Draw("al");
            canvas->cd(2);
            TPaveText *pt = new TPaveText(.05, .1, .95, .9);
            pt->AddText(Form("Max Voltage: %g", voltmax));
            pt->AddText(Form("Min Voltage: %g", voltmin));
            pt->AddText(Form("Position: (%g,%g,%g)", X, Y, X));
            pt->AddText(Form("Angle: %g Degrees", other_angle_degrees));
            //            pt->AddText(Form("Other Angle: %g Degrees", (180- (90 + other_angle_degrees))));

            pt->Draw(); // Uncomment to print to screen

            //            canvas->Print(charpath, "PNG"); // uncomment to save PDF to file

            //            uncommented to add pane 3 for GetHistogram

            //            canvas->cd(3);
            //            double tan_of_angle = tan(other_angle_degrees);
            //            TFormula *form1 = new TFormula("form1","abs(2 * x)");
            //            TF1 *sqroot = new TF1("sqroot",Form("%g * x", tan_of_angle),-10,10);
            //            sqroot->SetParameters(-10,10,1,20);
            //            sqroot->SetLineColor(4);
            //            sqroot->SetLineWidth(6);
            //            sqroot->Draw();
            //            TPaveLabel *lfunction = new TPaveLabel(5,39,9.8,46,"The sqroot function");
            //            lfunction->SetFillColor(41);
            //            lfunction->Draw();
            //            commented to remove pane 3 for a dual slide TCanvas
            //            outtree->Write();
//                          1           2           3                   4           5           6             7         8               9
//          plotEvent(int txindex, int rxindex, double noise_flag, int show_geom, int bins, int overlap, int logFlag, double ymin, double ymax){
            canvas->cd(3);
//            cout << "\033[1;32mnoise setting: " << noise_flag << endl;
            auto evG=event->getGraph(rxindex, txindex);
            if(noise_flag>0){
//                evG=TUtilRadioScatter::addNoise(evG, noise_flag);
                evG=TUtilRadioScatter::addNoise(evG, noise_flag);

            }
            TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
            TUtilRadioScatter::style(evG, kBlack, 1, 1);
            TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN()-1]);

            int bins = 64, overlap = 60;
//            int bins = 32, overlap = 30;
          //auto spec=TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins*2, 2, logFlag,ymin, ymax);
            auto spec=TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins*2);
            spec->Draw("colz");

            string path = "/home/rj/RadioScatter/outputfiles/";
            string filename = "event" + to_string(i) + ".png";
            string full_path = path + filename;
            const char *charpath = full_path.c_str();
            canvas->SaveAs(charpath);
//        auto rxdata = new vector<TLorentzVector>(event->rx);
//        double rxX = rxdata->X(0);
//        cout << rxdata << endl;
        }



        cout << "\033[1;31mMax Voltage:     \033[34m" << voltmax << "V" << endl;
        cout << "\033[1;31mMin Voltage:    \033[34m" << voltmin << "V" << endl;

        cout << "\033[1;31mPosition:        \033[0m" << "\033[1;34m(" << X << "m, " <<Y << "m, " << Z << "m)" << "\n";
        cout << "\033[1;31mAngle:           \033[034m" << other_angle_degrees << " Degrees" << endl;
//        cout << A << " " << 180 - (90 * A) << "\n";
//        I think Keith meant to type plus, per "Then the remaining angle is 180 - (90 + A)..."
        cout << "\033[1;31mOther Angle:     \033[034m" << 180 - (90 + other_angle_degrees)  << " Degrees\n\033[1;37m" << endl;
//        cout << "\033[1;31mTX Voltage:      " <<"\033[034m" << shower_voltage << endl;


    }
    cout << "\n";
    outfile->Write();
    outfile->Close();

}
