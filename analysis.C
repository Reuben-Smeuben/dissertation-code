void SetLeafAddress(TTree* ntuple, const char* name, void* address);
void analysis(string filename="YorkMedPhys.root"){
        //Reading the input file
    TFile *file_input = TFile::Open(filename.c_str());
    ifstream outfile;

    outfile.open("profile.txt");
    double myx, myy, rndm, alpha;
    TH1F *E_profile = new TH1F("E_profile", "Energy profile of electrons; energy (MeV); counts", 300, 0, 100.0);
      while (!outfile.eof()){
        outfile >> myx >> myy >> rndm >> alpha;
  //      cout<<myy<<endl;
        //fill 1D histo in this loop
        E_profile->Fill(myy);
      }
        //Reading the data (in TTree format
    TTree *YorkMedPhys =(TTree *) file_input->Get("YorkMedPhys;1");
    bool rowWise = true;
    TBranch* eventBranch = YorkMedPhys->FindBranch("row_wise_branch");

    if (! eventBranch) rowWise = false;

        //Setting up your variables that you want to read from the data
    double Edep;
    double X;
    double Y;
    double Z;

        // Connect these variables to the one in the TTree data
    if (!rowWise){
        YorkMedPhys->SetBranchAddress("Edep", &Edep);
        YorkMedPhys->SetBranchAddress("X", &X);
        YorkMedPhys->SetBranchAddress("Y", &Y);
        YorkMedPhys->SetBranchAddress("Z", &Z); // positions are recorded in mm
    }
    else{
        SetLeafAddress(YorkMedPhys, "Edep", &Edep);
        SetLeafAddress(YorkMedPhys, "X", &X);
        SetLeafAddress(YorkMedPhys, "Y", &Y);
        SetLeafAddress(YorkMedPhys, "Z", &Z);
    }

        // See how many entries (collections of E_abs,X,Y,Z) are written in the data
        // file (each particle beam throw into the phantom can deposit energy multiple
        // times at multiple steps inside the phantom, through the particle itself or
        // with its shower of particles created)
    int entries = YorkMedPhys->GetEntries();

        //Create your histogram (100 bins between 0.0cm and 50.0cm)
    TH1F *histo_example = new TH1F("histo_example", "Histo example Edep@X; X (cm) ; E_{dep}", 500, -40.0, 40.0);
    TH1F *histo_example_X = new TH1F("histo_example_X","Histo example X; X (cm) ; N",500, -40.0, 40.0);
    TH1F *histo_example_Xcut = new TH1F("histo_example_Xcut","Histo example X (X^{2}+Y^{2} < 1 mm); Z(cm); N", 100, 0.0, 50.0);
    TH2F *histo_radius_X=new TH2F("histo_radius_X","Distance from beamline (r) vs Phantom depth (X); X (cm); r (cm);",200, -40.0, 40, 200, 0.0, 31.0);
        //YOU CAN CREATE YOUR HISTOGRAMS HERE
        TH2F *bone_histo1 = new TH2F("bone_histo1", "bone Edep vs XY; X (cm) Y(cm); E_{dep}", 1100, -40.0, 40.0, 1100, -40.0, 40.0);
        TH2F *tissue_histo1 = new TH2F("tissue_histo1", "tissue Edep vs XY; X (cm); Y(cm); E_{dep}", 1100, -40.0, 40.0, 1100, -40.0, 40.0);
        TH2F *skin_histo1 = new TH2F("skin_histo1", "skin Edep vs XY; X (cm); Y(cm); E_{dep}", 1100, -40.0, 40.0, 1100, -40.0, 40.0);
        TH2F *shield_histo1 = new TH2F("shield_histo1", "shield Edep vs XY; X (cm); Y(cm); E_{dep}", 600, -38.0, -32.0, 600, -5.0, 5.0);
        TH2F *total_histo1 = new TH2F("total_histo1", "total Edep vs XY; X (cm); Y(cm); E_{dep}", 1100, -40.0, 40.0, 1100, -40.0, 40.0);
        TH1F *Edep_r = new TH1F("Edep_vs_r","Edep vs r; r (cm) ; E_{dep}", 400, 0.0, 40.0);







        // loop through all the entries in the data file
    for (int i = 0; i < entries; i++){

            // Read the single entry inside the data file (Now all the variables are
            // linked to the values at this entry
        YorkMedPhys->GetEntry(i);
        double r=TMath::Sqrt(X*X+Y*Y);

        histo_example->Fill(X/10, Edep*10);
        Edep_r->Fill(r/10, Edep);
          if (r<50.0)
        bone_histo1->Fill(X/10, Y/10, Edep);
          if (r>50.0 && r<280.0)
        tissue_histo1->Fill(X/10, Y/10, Edep);
          if (r>280.0 && r<300.0)
        skin_histo1->Fill(X/10, Y/10, Edep);
          if (X<-300.0 && X>-400.0) //in mm?
        shield_histo1->Fill(X/10, Y/10, Edep);
        total_histo1->Fill(X/10, Y/10, Edep);
            // (Z is in mm!! we want it in cm)each value of Z is put into the histograms:
            // This will give how many times there was an energy deposited in each range
            // defined by this bin in the histogram
        histo_example_X->Fill(X/10);
        Edep_r->Fill(r/10);
            // same as before, but now each entry is weighted with the energy deposited
            // at that moment. At the end this  will five the full energy deposited in
            // each bin in Z.
        histo_example->Fill(X/10, Edep*10);
      //  double r=TMath::Sqrt(X*X+Y*Y);
        histo_radius_X->Fill(X/10, r/10, Edep);
            // We can make a cut on the data (NB variables in mm)
        if ((X*X + Y*Y) < 1){
                // (Z is in mm!! we want it in cm)each value of Z is put into the
                // histograms: This will give how many times there was an energy deposited
                // in each range defined by this bin in the histogram
            histo_example_Xcut->Fill(Z/10);
        }
        //FILL YOUR HISTOGRAMS HERE


    }
        // now the looop through all the entries is finished
    gStyle->SetOptStat(0);
        // Create a Canvas where to plot the histogram created
    TCanvas *C1 = new TCanvas ("C1","Histograms", 1200, 600);
    histo_example_X->Draw(); // Draw the histogram
                             // Create a picture (just click on it in order to see it (or download it if
                             // you want to keep it)
    C1->Print("X_picture.jpeg");
    histo_example_Xcut->Draw(); // Draw the histogram
                                // Create a picture (just click on it in order to see it (or download it if
                                // you want to keep it)
    C1->Print("X_picture_CUT.jpeg");
    histo_example->Draw(); // Draw the histogram
                           // Create a picture (just click on it in order to see it (or download it if
                           // you want to keep it)
    C1->Print("X_Edep_picture.jpeg");

        // we can also draw them together
    histo_example_X->SetLineColor(2); // change the color of the histogram to red
    histo_example_X->SetTitle("Histo example X (N_{events} RED) (E_{dep} BLUE); X (cm);");
    int max=(histo_example_X->GetMaximum()>histo_example->GetMaximum())?histo_example_X->GetMaximum() :
    histo_example->GetMaximum();
    C1->Clear();
        //C1=new TCanvas ("C1","Histograms", 1200, 600);
    C1->Divide(2,1);
    C1->cd(1);
    histo_example_X->SetMaximum(max+500);
    histo_example_X->SetMinimum(0);

    histo_example_X->Draw();

    histo_example->Draw("SAME");
    C1->cd(2);
    gPad->SetLogz();
    histo_radius_X->Draw("colz");


    C1->Print("X_picture_comparison.jpeg");

        // we can also write the results in an output file
    TFile *file_output = new TFile("analysis_output.root","RECREATE");
    histo_example_X->Write();
    histo_example_Xcut->Write();
    histo_example->Write();
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
