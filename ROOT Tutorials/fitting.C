/*
    Author: Richard Moser
    Date: 05Jun24
    Description: This program reads in data from an array and fits the data to a polynomial of degree 1-5. The data is
    then plotted on a graph with the fits.
    Data Source: https://www.kaggle.com/datasets/starbucks/starbucks-menu
    Requirements: ROOT (https://root.cern.ch/)
    Instructions to run:
        1: Open your terminal
        2: Navigate to the directory containing this file
        3: source /path/to/root/bin/thisroot.sh if you have not already done so in the .bashrc file
        4: either type root and then .x fitting.C or type root -l fitting.C
*/


void fitting()
{

    double x[242] = {0.0, 0.0, 0.0, 2.0, 20.0, 20.0, 20.0, 30.0, 30.0, 30.0, 40.0, 40.0, 40.0, 50.0, 50.0, 50.0, 15.0, 15.0,
                15.0, 25.0, 25.0, 25.0, 35.0, 35.0, 35.0, 45.0, 45.0, 45.0, 20.0, 20.0, 20.0, 30.0, 30.0, 30.0, 35.0,
                35.0, 35.0, 50.0, 45.0, 45.0, 0.0, 2.0, 2.0, 2.0, 15.0, 15.0, 10.0, 20.0, 20.0, 20.0, 25.0, 25.0, 25.0,
                30.0, 30.0, 35.0, 0.0, 0.0, 20.0, 30.0, 35.0, 50.0, 15.0, 15.0, 15.0, 25.0, 25.0, 25.0, 35.0, 30.0,
                35.0, 40.0, 40.0, 40.0, 25.0, 25.0, 25.0, 35.0, 35.0, 35.0, 45.0, 45.0, 45.0, 60.0, 60.0, 60.0, 20.0,
                20.0, 20.0, 30.0, 30.0, 30.0, 40.0, 40.0, 40.0, 50.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 10.0, 10.0, 10.0, 20.0, 20.0, 20.0, 25.0, 25.0, 25.0, 35.0, 30.0, 30.0, 20.0, 20.0, 20.0, 35.0,
                35.0, 35.0, 45.0, 45.0, 45.0, 60.0, 50.0, 60.0, 10.0, 10.0, 10.0, 20.0, 15.0, 20.0, 25.0, 25.0, 25.0,
                30.0, 30.0, 30.0, 10.0, 10.0, 10.0, 20.0, 15.0, 20.0, 25.0, 25.0, 25.0, 30.0, 30.0, 30.0, 0.0, 0.0, 0.0,
                6.0, 6.0, 6.0, 8.0, 8.0, 8.0, 10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 20.0, 20.0, 10.0,
                10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 8.0, 10.0, 10.0, 10.0, 10.0, 20.0, 15.0, 20.0, 10.0, 8.0, 10.0,
                10.0, 10.0, 10.0, 15.0, 15.0, 20.0, 10.0, 8.0, 10.0, 10.0, 10.0, 10.0, 15.0, 15.0, 20.0, 10.0, 8.0,
                10.0, 10.0, 10.0, 10.0, 20.0, 15.0, 20.0, 10.0, 10.0, 15.0, 8.0, 10.0, 15.0, 8.0, 10.0, 15.0, 10.0,
                10.0, 15.0, 10.0, 10.0, 10.0, 15.0, 15.0, 15.0, 20.0, 20.0, 20.0, 10.0, 10.0, 10.0, 15.0 };
    double y[242] = {0.3, 0.5, 1.0, 1.0, 6.0, 6.0, 5.0, 10.0, 10.0, 8.0, 13.0, 12.0, 10.0, 16.0, 16.0, 13.0, 7.0, 6.0,
                6.0, 10.0, 10.0, 9.0, 13.0, 13.0, 11.0, 17.0, 17.0, 14.0, 6.0, 6.0, 5.0, 9.0, 9.0, 7.0, 12.0, 12.0, 9.0,
                15.0, 15.0, 12.0, 0.4, 1.0, 1.0, 1.0, 5.0, 5.0, 3.0, 6.0, 6.0, 5.0, 8.0, 8.0, 7.0, 10.0, 10.0, 9.0,
                0.4, 1.0, 6.0, 9.0, 12.0, 15.0, 6.0, 5.0, 4.0, 8.0, 8.0, 7.0, 11.0, 10.0, 9.0, 13.0, 13.0, 11.0, 7.0,
                7.0, 6.0, 12.0, 11.0, 10.0, 15.0, 15.0, 13.0, 19.0, 19.0, 16.0, 7.0, 7.0, 6.0, 11.0, 10.0, 9.0, 14.0,
                14.0, 12.0, 18.0, 17.0, 15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.0, 4.0, 3.0, 6.0, 6.0, 5.0, 8.0,
                8.0, 6.0, 10.0, 10.0, 8.0, 7.0, 7.0, 6.0, 11.0, 10.0, 9.0, 14.0, 14.0, 11.0, 18.0, 17.0, 14.0, 4.0, 3.0,
                3.0, 5.0, 5.0, 4.0, 7.0, 7.0, 6.0, 9.0, 9.0, 7.0, 4.0, 3.0, 3.0, 5.0, 5.0, 4.0, 7.0, 7.0, 6.0, 9.0, 9.0,
                7.0, 0.2, 0.3, 0.4, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 4.0, 3.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 20.0,
                20.0, 19.0, 16.0, 16.0, 15.0, 16.0, 16.0, 16.0, 3.0, 3.0, 2.0, 4.0, 3.0, 3.0, 6.0, 5.0, 5.0, 3.0, 3.0,
                3.0, 4.0, 4.0, 4.0, 7.0, 6.0, 6.0, 3.0, 3.0, 2.0, 4.0, 3.0, 3.0, 5.0, 5.0, 5.0, 4.0, 4.0, 3.0, 5.0, 5.0,
                4.0, 7.0, 7.0, 6.0, 3.0, 3.0, 5.0, 3.0, 4.0, 6.0, 3.0, 3.0, 5.0, 4.0, 5.0, 7.0, 3.0, 3.0, 3.0, 4.0, 4.0,
                3.0, 6.0, 6.0, 5.0, 4.0, 3.0, 3.0, 5.0 };
    // initializes the x and y arrays with the data from the Starbucks menu
    // x is the calcium % daily value and y is the protein in grams

    TGraph *graph = new TGraph(242, x, y);
    //  creates a graph with 242 entries, x values from array x, and y values from array y

    TCanvas *c1 = new TCanvas();
    //    creates new TCanvas named c1
    c1->SetWindowSize(2000, 1000);
    //    sets the window size of the TCanvas

    graph->SetTitle("Starbucks Drink Nutrition Comparison");
    // sets the title fo the graph to "Starbucks Drink Nutrition"

    graph->GetXaxis()->SetTitle("Calcium (% DV)");
    graph->GetYaxis()->SetTitle("Protein (g)");
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(2);

    graph->Fit("pol1", "+");
    graph->Fit("pol2", "+");
    graph->Fit("pol3", "+");
    graph->Fit("pol4", "+");
    graph->Fit("pol5", "+");
    // fits the graph with a polynomial of degree 1-5

    graph->GetFunction("pol1")->SetLineColor(kBlue);
    // sets pol1 fit line color to blue
    graph->GetFunction("pol2")->SetLineColor(kRed);
    // sets pol2 fit line color to red
    graph->GetFunction("pol3")->SetLineColor(kGreen);
    // sets pol3 fit line color to green
    graph->GetFunction("pol4")->SetLineColor(kYellow);
    // sets pol4 fit line color to yellow
    graph->GetFunction("pol5")->SetLineColor(kBlack);
    // sets pol5 fit line color to black

    graph->Draw("AP");
    // draws the graph to the canvas

}

