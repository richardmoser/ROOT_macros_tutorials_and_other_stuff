/*
This macro loads up the default plotting macro, sets the canvas size, and saves it

 */
#include<iostream>
using namespace std;

int antenna;
int event;
string filename1 = "\"/home/rj/RadioScatter/doc/output_test_0MHz_10W_10ns.root\"";

void start(){
    cout << "How many events? " << endl;
    cin >> event;

    cout << "How many antennas? " << endl;
    cin >> antenna;

    cout << "Drag and drop ROOT file here" << endl;
    cin >> filename1;
    filename1 = filename1.substr(1, filename1.size() - 2);

    const char *str = filename1.c_str();
    cout << str << endl;

    gROOT->ProcessLine(Form("dsmacroworking(\"%s\", %i, %i)", str, antenna, event));
    gROOT->ProcessLine("plotEvent->SetCanvasSize(3000, 1000)");
    gROOT->ProcessLine("plotEvent->SaveAs(\" test.pdf\")");

  
  
  }
