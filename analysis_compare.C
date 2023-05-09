void SetLeafAddress(TTree* ntuple, const char* name, void* address);


void analysis_compare(string filename1="YorkMedPhys.root", string filename2="YorkMedPhys.root"){


        //Create your histogram (100 bins between 0.0cm and 50.0cm)
    TH1F *histo_example1 = new TH1F("histo_example1", "Histo example Edep@Z; Z (cm) ; E_{dep}", 100, 0.0, 50.0);
    TH1F *histo_example_Z1 = new TH1F("histo_example_Z1","Histo example Z; Z (cm) ; N",100, 0.0, 50.0);
    TH1F *histo_example_Zcut1 = new TH1F("histo_example_Zcut1","Histo example Z (X^{2}+Y^{2} < 1 mm); Z(cm); N", 100, 0.0, 50.0);
    TH2F *histo_radius_Z1=new TH2F("histo_radius_Z1","File 1: Distance from beamline (r) vs Phantom depth (Z); Z (cm); r (cm);",100, 0, 50, 200, 0, 5);

    TH1F *histo_example2 = new TH1F("histo_example2", "Histo example Edep@Z; Z (cm) ; E_{dep}", 100, 0.0, 50.0);
    TH1F *histo_example_Z2 = new TH1F("histo_example_Z2","Histo example Z; Z (cm) ; N",100, 0.0, 50.0);
    TH1F *histo_example_Zcut2 = new TH1F("histo_example_Zcut2","Histo example Z (X^{2}+Y^{2} < 1 mm); Z(cm); N", 100, 0.0, 50.0);
    TH2F *histo_radius_Z2=new TH2F("histo_radius_Z2","File 2: Distance from beamline (r) vs Phantom depth (Z); Z (cm); r (cm);",100, 0, 50, 200, 0, 5);
        //YOU CAN CREATE YOUR HISTOGRAMS HERE
        TH2F *bone_histo1 = new TH2F("bone_histo1", "bone Edep vs XY; X (cm) Y(cm); E_{dep}", 800, -8.0, 8.0, 800, -8.0, 8.0);
        TH2F *tissue_histo1 = new TH2F("tissue_histo1", "tissue Edep vs XY; X (cm); Y(cm); E_{dep}", 800, -30.0, 30.0, 800, -30.0, 30.0);
        TH2F *skin_histo1 = new TH2F("skin_histo1", "skin Edep vs XY; X (cm); Y(cm); E_{dep}", 800, -35.0, 35.0, 800, -35.0, 35.0);
        TH2F *shield_histo1 = new TH2F("shield_histo1", "shield Edep vs XY; X (cm); Y(cm); E_{dep}", 800, -40.0, 40.0, 800, -40.0, 40.0);

        //Reading the input file
    TFile *file_input1 = TFile::Open(filename1.c_str());
    TFile *file_input2 = TFile::Open(filename2.c_str());
        //Reading the data (in TTree format
    TTree *YorkMedPhys1 =(TTree *) file_input1->Get("YorkMedPhys;1");
    TTree *YorkMedPhys2 =(TTree *) file_input2->Get("YorkMedPhys;1");
    bool rowWise = true;
    TBranch* eventBranch1 = YorkMedPhys1->FindBranch("row_wise_branch");
    TBranch* eventBranch2 = YorkMedPhys2->FindBranch("row_wise_branch");


    //FOR TREE 1
    if (! eventBranch1) rowWise = false;
        //Setting up your variables that you want to read from the data
    double Edep;
    double X;
    double Y;
    double Z;
        // Connect these variables to the one in the TTree data
    if (!rowWise){
        YorkMedPhys1->SetBranchAddress("Edep", &Edep);
        YorkMedPhys1->SetBranchAddress("X", &X);
        YorkMedPhys1->SetBranchAddress("Y", &Y);
        YorkMedPhys1->SetBranchAddress("Z", &Z); // positions are recorded in mm
    }
    else{
        SetLeafAddress(YorkMedPhys1, "Edep", &Edep);
        SetLeafAddress(YorkMedPhys1, "X", &X);
        SetLeafAddress(YorkMedPhys1, "Y", &Y);
        SetLeafAddress(YorkMedPhys1, "Z", &Z);
    }


        // See how many entries (collections of E_abs,X,Y,Z) are written in the data
        // file (each particle beam throw into the phantom can deposit energy multiple
        // times at multiple steps inside the phantom, through the particle itself or
        // with its shower of particles created)
    int entries = YorkMedPhys1->GetEntries();







        // loop through all the entries in the data file
    for (int i = 0; i < entries; i++){
            // Read the single entry inside the data file (Now all the variables are
            // linked to the values at this entry
        YorkMedPhys1->GetEntry(i);

            // (Z is in mm!! we want it in cm)each value of Z is put into the histograms:
            // This will give how many times there was an energy deposited in each range
            // defined by this bin in the histogram
        histo_example_Z1->Fill(Z/10);
        bone_histo1->Fill(X/10, Y/10);
        tissue_histo1->Fill(X/10, Y/10);
        skin_histo1->Fill(X/10, Y/10);
        shield_histo1->Fill(X/10, Y/10);

            // same as before, but now each entry is weighted with the energy deposited
            // at that moment. At the end this  will five the full energy deposited in

            // We can make a cut on the data (NB variables in mm)
        if ((X*X + Y*Y) < 1){
                // (Z is in mm!! we want it in cm)each value of Z is put into the
                // histograms: This will give how many times there was an energy deposited
                // in each range defined by this bin in the histogram
            histo_example_Zcut1->Fill(Z/10);
        }
        //FILL YOUR HISTOGRAMS HERE


    }


    if (!eventBranch2) rowWise = false;
        //Setting up your variables that you want to read from the data
        // Connect these variables to the one in the TTree data
    if (!rowWise){
        YorkMedPhys2->SetBranchAddress("Edep", &Edep);
        YorkMedPhys2->SetBranchAddress("X", &X);
        YorkMedPhys2->SetBranchAddress("Y", &Y);
        YorkMedPhys2->SetBranchAddress("Z", &Z); // positions are recorded in mm
    }
    else{
        SetLeafAddress(YorkMedPhys2, "Edep", &Edep);
        SetLeafAddress(YorkMedPhys2, "X", &X);
        SetLeafAddress(YorkMedPhys2, "Y", &Y);
        SetLeafAddress(YorkMedPhys2, "Z", &Z);
    }
    entries = YorkMedPhys2->GetEntries();
        // loop through all the entries in the data file
    for (int i = 0; i < entries; i++){
            // Read the single entry inside the data file (Now all the variables are
            // linked to the values at this entry
        YorkMedPhys2->GetEntry(i);
        //fill the histograms here
        // each bin in Z.
    histo_example1->Fill(Z/10, Edep);
    //bone_histo1->Fill(X/10, Y/10, Edep);
    //tissue_histo1->Fill(X/10, Y/10, Edep);
    //skin_histo1->Fill(X/10, Y/10, Edep);
    //shield_histo1->Fill(X/10, Y/10, Edep);
    double r=TMath::Sqrt(X*X+Y*Y);
    histo_radius_Z1->Fill(Z/10, r/10, Edep);
            // (Z is in mm!! we want it in cm)each value of Z is put into the histograms:
            // This will give how many times there was an energy deposited in each range
            // defined by this bin in the histogram
        histo_example_Z2->Fill(Z/10);
        bone_histo1->Fill(X/10, Y/10);
        tissue_histo1->Fill(X/10, Y/10);
        skin_histo1->Fill(X/10, Y/10);
        shield_histo1->Fill(X/10, Y/10);

            // same as before, but now each entry is weighted with the energy deposited
            // at that moment. At the end this  will five the full energy deposited in
            // each bin in Z.
        histo_example2->Fill(Z/10, Edep);
        double r=TMath::Sqrt(X*X+Y*Y);
        histo_radius_Z2->Fill(Z/10, r/10, Edep);
        bone_histo1->Fill(X/10, Y/10, Edep);
        tissue_histo1->Fill(X/10, Y/10, Edep);
        skin_histo1->Fill(X/10, Y/10, Edep);
        shield_histo1->Fill(X/10, Y/10, Edep);
            // We can make a cut on the data (NB variables in mm)
        if ((X*X + Y*Y) < 1){
                // (Z is in mm!! we want it in cm)each value of Z is put into the
                // histograms: This will give how many times there was an energy deposited
                // in each range defined by this bin in the histogram
            histo_example_Zcut2->Fill(Z/10);
        }
            //FILL YOUR HISTOGRAMS HERE
    }





















    histo_example_Z1->SetLineColor(kRed); // change the color of the histogram to red
    histo_example_Z2->SetLineColor(kBlue); // change the color of the histogram to
    int max1=(histo_example_Z1->GetMaximum()>histo_example_Z2->GetMaximum())?histo_example_Z1->GetMaximum() :
    histo_example_Z2->GetMaximum();

    histo_example1->SetLineColor(kRed); // change the color of the histogram to red
    histo_example2->SetLineColor(kBlue); // change the color of the histogram to
    int max=(histo_example1->GetMaximum()>histo_example2->GetMaximum())?histo_example1->GetMaximum() :
    histo_example2->GetMaximum();



        // now the looop through all the entries is finished
    gStyle->SetOptStat(0);
        // Create a Canvas where to plot the histogram created
    TCanvas *C1 = new TCanvas ("C1","Histograms", 1200, 600);
    C1->Divide(2,2);
    C1->cd(1);
    histo_example_Z1->SetMaximum(max1+500);
    histo_example_Z1->SetMinimum(0);
    histo_example_Z1->Draw();
    histo_example_Z2->Draw("SAME");

    C1->cd(2);
    histo_example1->SetMaximum(max+500);
    histo_example1->SetMinimum(0);
    histo_example1->Draw();
    histo_example2->Draw("SAME");


    C1->cd(3);
    gPad->SetLogz();
    histo_radius_Z1->Draw("colz");

    C1->cd(4);
    gPad->SetLogz();
    histo_radius_Z2->Draw("colz");

//    C1->Print("Z_picture_comparison.jpeg");

        // we can also write the results in an output file
    TFile *file_output = new TFile("analysis_compare_output.root","RECREATE");
    histo_example_Z1->Write();
    histo_example_Zcut1->Write();
    histo_example1->Write();
    histo_example_Z2->Write();
    histo_example_Zcut2->Write();
    histo_example2->Write();
    file_output->Close();
}






void SetLeafAddress(TTree* ntuple, const char* name, void* address){
    TLeaf* leaf = ntuple->FindLeaf(name);
    if (!leaf){
        std::cerr << "Error in <SetLeafAddress>: unknown leaf --> " << name
        << std::endl;
        return;
    }
    leaf->SetAddress(address);
}
