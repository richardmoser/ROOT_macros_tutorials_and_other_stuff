/*
This macro loads up the default plotting macro, sets the canvas size, and saves it

 */
#include<iostream>
#include<unistd.h>
#include<stdio.h>
using namespace std;

float antennas;
float events;
string filepath = "\"/home/rj/RadioScatter/doc/output_test_0MHz_10W_10ns.root\"";
string filename;
string continueyn;
string fileyn;

void start() {
    cout << "How many events? " << endl;
    cin >> events;

    cout << "How many receiver antennas? " << endl;
    cin >> antennas;

    if((antennas * events) > 200) {
        cout << events << " events * " << antennas << " antennas = " << (antennas * events) << " Interactions. ";
        cout << "saving greater than 200 interactions in one macro run is not recommended. PC failure is likely.";
        cout << "Do you wish to continue?" << endl;
        cin >> continueyn;
        if(continueyn != "y"){
            abort();
        }
    } //actual failure was seen at around 212 interactions but 850 files were in the folder...

    cout << "Is your ROOT file output_big_scat_0MHz_10W_3ns.root in the doc folder? (y/n) " << endl;
    cin >> fileyn;

    if(fileyn == "y" or fileyn == "Y" or fileyn == "yes"){
        filepath = "'/home/rj/RadioScatter/doc/output_big_scat_0MHz_10W_3ns.root'";
    }
    else{
        cout << "Drag and drop ROOT file here" << endl;
        cin >> filepath;
    }

    filepath = filepath.substr(1, filepath.size() - 2);
    string filepath2 = filepath;
    const char *str = filepath2.c_str();

    filename = filepath.erase(0, filepath.rfind("output"));
    string almostfancyfilename = filename.erase(filename.size() -5, filename.size());
    const char *fancyfilename = almostfancyfilename.c_str();

    cout << "filepath2: " << filepath2 << endl;
    cout << "fancy filename: " << fancyfilename << endl;
    cout << "str: " << str << endl;

    double progress = 0.0;
    for (int i = 0; i < antennas; i++) {
        for(int j = 0; j < events; j++) {
            gROOT->ProcessLine(Form("dsmacroworking(\"%s\", %i, %i)", str, j, i));
            gROOT->ProcessLine("plotEvent->SetCanvasSize(3000, 1000)");
            gROOT->ProcessLine(Form("plotEvent->SaveAs(\"/home/rj/Desktop/RS Stuff/bulk grabs/%s_Event%i_RX%i.png\")",
                                    fancyfilename, j, i));
            gROOT->ProcessLine(Form("plotEvent->SaveAs(\"/home/rj/Desktop/RS Stuff/bulk grabs/%s_Event%i_RX%i.C\")",
                                    fancyfilename, j, i));
            unsigned int microsecond = 1000000;
            usleep(.00 * microsecond); //sleeps for .1 seconds

            int barWidth = 70;
            cout << "\033[33m\n[";
            int pos = barWidth * progress;
            for (int i = 0; i < barWidth; ++i) {
                if (i < pos) cout << "\033[33m=";
                else if (i == pos) cout << "\033[33m>";
                else cout << " ";
            }
            cout << " " << int(progress * 100.0) << " %\r\n  \x1b[0m" << endl;
            cout.flush();
            progress += 1/(events * antennas); // replace with antennas and events
        }
    }
}