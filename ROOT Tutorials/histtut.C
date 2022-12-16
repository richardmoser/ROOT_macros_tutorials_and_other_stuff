 
void histtut()
{
    TH1F *hist = new TH1F("hist", "Histogram", 100, 0, 100);
//    creates new TH1F named hist
//    TH1 *name_of_histogram = new TH1F(name, title, bins, start value, end value)

    hist->Fill(10);
//    Adds the value 10 to the histogram
    hist->Fill(20);

    hist->GetXaxis()->SetTitle("X-axis");
    hist->GetYaxis()->SetTitle("Y-axis");
//    Sets the title of the axes

    TCanvas *c1 = new TCanvas();
//     creates new TCanvas named c1
    c1->SetWindowSize(2000, 1000);
//    sets the window size of the TCanvas

    hist->Draw();
//    draws the histogram on the canvas
}

//run by the terminal command root tut1.C