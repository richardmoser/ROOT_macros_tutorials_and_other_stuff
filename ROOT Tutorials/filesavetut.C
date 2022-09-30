 
void filesavetut()
{
    TFile *file = new TFile("tutorial_TFile.root", "RECREATE");
//    creates a new root file in the RECREATE mode

    TH1F *hist = new TH1F("hist", "Histogram", 100, 0, 100);
    hist->Fill(10);
    hist->Fill(20);
    hist->GetXaxis()->SetTitle("X-axis");
    hist->GetYaxis()->SetTitle("Y-axis");

    file->Write();
//    writes everything from the TFile's creation to now to the file
    file->Close();
//    closes the TFile.
}

//run by the terminal command root tut1.C