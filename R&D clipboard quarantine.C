

auto evG=event->getGraph(rxindex, txindex);
TUtilRadioScatter::titles(evG, "", "Time [ns]", "V");
TUtilRadioScatter::style(evG, kBlack, 1, 1);
TUtilRadioScatter::xrange(evG, evG->GetX()[0], evG->GetX()[evG->GetN()-1]);
int bins = 32, overlap = 31;
auto spec=TUtilRadioScatter::FFT::spectrogram(evG, bins, overlap, bins*2, 2,   0,     0,    .2);

int NumFreqBins=spec->GetNbinsX();
int NumIntensBins=spec->GetNbinsY();
cout << NumIntensBins << endl;
double *points = new double[NumFreqBins];
double *itt = new double[NumIntensBins];

Float_t xmax = 1;
Float_t xmin = 0;
spec->Draw("colz");
int tempstuff;
// c1->Draw();
// for(int i = 1; i < NumFreqBins+1; ++i){
for(int j = 0; j <= NumIntensBins; ++j){
tempstuff = spec->GetBin(1,j);
points[j] = tempstuff;
itt[j] = j;
cout << "bin\(" << j <<  ") contents: " << tempstuff << endl;
}
// }

// c1->SetLogy(1);
const Int_t n = 70;
TGraph *grrrrreat = new TGraph(n,itt,points);
grrrrreat->SetMarkerColor(4);
// gr->SetMarkerStyle(2);
grrrrreat->SetMarkerStyle(20);
// grrrrreat->SetTitle("Triggered Event Peak Frequency vs Peak Power");
// grrrrreat->GetXaxis()->SetTitle("Peak Frequency (MHz)");
// grrrrreat->GetYaxis()->SetTitle("Peak Power (W)");
grrrrreat->Draw("AP");
c1->Update();
c1->GetFrame()->SetBorderSize(100);
c1->Modified();
c1->Draw();

// creates a float array called allfreqs of size num_freq_bins
// creates a float array called allpows of size num_intens_bins
// for(int entry = 0; entry < tree->GetEntries()-1; entry++){
//     for(int rx = 0; rx < event->nrx; rx++){
// //            cout << "event " << entry << " freq: " << freq_array[entry][rx] << "MHz, power: " << power_array[entry][rx] << endl;
//         allfreqs[count] = freq_array[entry][rx];
//         allpows[count]= power_array[entry][rx];
//         count++;
//     }
//