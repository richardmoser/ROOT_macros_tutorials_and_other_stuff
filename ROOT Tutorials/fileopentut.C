 
void fileopentut()
{
    TFile *file = new TFile("tutorial_TFile.root", "READ");

    TH1F *hist = (TH1F*)file->Get("hist");

    TCanvas *c1 = new TCanvas();

    c1->SetWindowSize(2000, 1000);

    hist->Draw();

}
