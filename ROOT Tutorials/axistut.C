 
void axistut()
{
        TCanvas *c1 = new TCanvas("c1","Examples of TGaxis",10,10,700,500);

        c1->Range(-10,-1,10,1);

        TGaxis *axis1 = new TGaxis(-4.5,-0.2,5.5,-0.2,-6,8,510,"");
        axis1->SetName("axis1");
        axis1->Draw();

        TGaxis *axis2 = new TGaxis(-4.5,0.2,5.5,0.2,0.001,10000,510,"G");
        axis2->SetName("axis2");
        axis2->Draw();

        TGaxis *axis3 = new TGaxis(-9,-0.8,-9,0.8,-8,8,50510,"");
        axis3->SetName("axis3");
        axis3->Draw();

        TGaxis *axis4 = new TGaxis(-7,-0.8,-7,0.8,1,10000,50510,"G");
        axis4->SetName("axis4");
        axis4->Draw();

        TGaxis *axis5 = new TGaxis(-4.5,-0.6,5.5,-0.6,1.2,1.32,80506,"-+");
        axis5->SetName("axis5");
        axis5->SetLabelSize(0.03);
        axis5->SetTextFont(72);
        axis5->SetLabelOffset(0.025);

        axis5->Draw();

        TGaxis *axis6 = new TGaxis(-4.5,0.6,5.5,0.6,100,900,50510,"-");
        axis6->SetName("axis6");
        axis6->Draw();

        TGaxis *axis7 = new TGaxis(8,-0.8,8,0.8,0,9000,50510,"+L");
        axis7->SetName("axis7");
        axis7->SetLabelOffset(0.01);
        axis7->Draw();

        //one can make axis going top->bottom. However because of a long standing
        //problem, the two x values should not be equal
        TGaxis *axis8 = new TGaxis(6.5,0.8,6.499,-0.8,0,90,50510,"-");
        axis8->SetName("axis8");
        axis8->Draw();
    }