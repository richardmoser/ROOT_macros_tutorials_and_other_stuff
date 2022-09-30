#include <iostream>
#include <type_traits>

//void kmacro(TString infile, int rxindex, int txindex, int antenna=0, int entry=0){
void kmacro(){

//    TString infile = "/home/rj/RadioScatter/doc/output_test_0MHz_10W_3ns.root";
    TString infile = "/home/rj/RadioScatter/doc/output_big_scat_0MHz_10W_3ns.root";
    int rxindex = 0;
    int txindex = 0;
    int antenna = 0;
    int entry = 0;
        auto ff=TFile::Open(infile);
        auto tree=(TTree*)ff->Get("tree");

        auto event=new RadioScatterEvent();

        tree->SetBranchAddress("event", &event);
        tree->GetEntry(entry);
        auto shower_direction= event->direction;
        auto shower_position= event->position;

        cout << "shower position X: " << shower_position.X() << endl;
        cout << "shower position Y: " << shower_position.Y() << endl;
        cout << "shower position z: " << shower_position.Z() << endl;


        cout << "shower direction X: " << shower_direction.X() << endl;
        cout << "shower direction Y: " << shower_direction.Y() << endl;
        cout << "shower direction Z: " << shower_direction.Z() << endl;

        auto neathistogram = event->eventHist;

        TCanvas *c1 = new TCanvas();
    //    creates new TCanvas named c1
        c1->SetWindowSize(2000, 1000);
    //    sets the window size of the TCanvas
//
        neathistogram[0][0]->GetXaxis()->SetTitle("X-axis");
        neathistogram[0][0]->GetYaxis()->SetTitle("Y-axis");
        neathistogram[0][0]->SetMarkerStyle(4);
        neathistogram[0][0]->SetMarkerSize(2);
//
        cout << typeid(neathistogram).name() << endl;
        neathistogram[0][0]->Draw();



//        auto c1 = new TCanvas();
//        event->getGraph(rxindex, txindex)->Draw("A*");
//        c1->Print("/path/to/graph.pdf");



}
