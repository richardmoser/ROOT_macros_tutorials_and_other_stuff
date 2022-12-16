 
void treetut()
{
    fstream file;
    file.open("data.txt", ios::in);
    double x, y, z;

    TFile *output = new TFile("data.root", "RECREATE");

    TTree *tree = new TTree("tree", "title");

    tree->Branch("x", &x, "x/D");
//    creates a branch on tree with name "x", associates it with variable x, and assigns x the type double
    tree->Branch("y", &y, "y/D");

    while(1){
        file >> x >> y >> z;
        cout << x << " " << y << " " << z << endl;

        if(file.eof()) break;

        tree->Fill();
//        reads each line from the data file and assigns x, y, and z to the numbers inside the file until it
//        reaches the end of the file
    }
    output->Write();
    output->Close();
    file.close();
}
