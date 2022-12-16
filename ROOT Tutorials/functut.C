 
void functut()
{
    TF3 *func = new TF3("Function", "x + y", -10, 10, -10, 10, -10, 10);

    TCanvas *c1 = new TCanvas();
    c1->SetWindowSize(2000, 1000);

    func->Draw();
}

//run by the terminal command root tut1.C