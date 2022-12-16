 
void graphtut()
{
    double x[5] = {1, 2, 3, 4, 5};
    double y[5] = {1,4,9,16,25};

    TGraph *graph = new TGraph(5, x, y);
//  creates a graphy with five entries, x values from array x, and y values from array y

    TCanvas *c1 = new TCanvas();
//    creates new TCanvas named c1
    c1->SetWindowSize(2000, 1000);
//    sets the window size of the TCanvas

    graph->GetXaxis()->SetTitle("X-axis");
    graph->GetYaxis()->SetTitle("Y-axis");
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(2);
//    Sets various properties of the graph

    graph->Draw("ALP");






}

//run by the terminal command root tut1.C