#include <iostream>
#include <TGraph.h>

using namespace std;

void doit() {
    // creates the data for the histogram
    auto c1 = TUtilRadioScatter::canvas();
    vector<double_t> x;
    vector<double_t> y;
    vector<double_t> z;
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 25; ++j){
            x.push_back(i);
            y.push_back(j);
            z.push_back(gRandom->Integer(10));
        }
    }
    //initialize a new TH2D histogram with 25 entries in x and y, and a range of 0 to 5 in both x and y
    TH2D *h2 = new TH2D("h2","h2",5,0,5,5,0,5);
    //fill the histogram with the values in x,y,z
    h2->FillN(x.size(),&x[0],&y[0],&z[0]);
    gStyle->SetOptStat(0);
    h2->SetBarOffset(0.2);
    h2->Draw("TEXT colz");
    c1->Draw();

    //fills three vectors x,y,z. X and y are filled sequentially in loops. z is filled with random numbers
    vector<vector<double_t>> hist; //creates a vector of vectors of doubles called hist to fill the histogram
    for(int i = 0; i < 6; ++i){ //loops over number of row bins ()
        vector<double_t> row;
        for(int j = 0; j < 6; ++j){ //loops over number of column bins
            row.push_back(h2->GetBinContent(i,j)); //fills the row vector with the bin contents of the histogram
        }
        hist.push_back(row); //fills the hist vector with the row vector
    }
    //print the 2d vector
    for(int i = 0; i < 6; ++i){ //loops over number of row bins
        for(int j = 0; j < 6; ++j){ //loops over number of column bins
            // print the value at row i, column j with text
            if(i != 0 & j !=0){ //skips the first row and column (ROOT's overflow bins)
                cout << "row: " << i << ", col: " << j << ", value: " << hist[i][j] << endl;
            }

//            cout << hist[i][j] << " ";
        }
        cout << endl;
    }
}