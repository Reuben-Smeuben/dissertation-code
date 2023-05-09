void SetLeafAddress(TTree* ntuple, const char* name, void* address);
void analysis(string filename="YorkMedPhys.root"){
        //Reading the input file
    TFile *file_input = TFile::Open(filename.c_str());
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
    TH1F *histo_example = new TH1F("histo_example", "Histo example Edep@Z; Z (cm) ; E_{dep}", 100, 0.0, 50.0);
    TH1F *histo_example_Z = new TH1F("histo_example_Z","Histo example Z; Z (cm) ; N",100, 0.0, 50.0);
    TH1F *histo_example_Zcut = new TH1F("histo_example_Zcut","Histo example Z (X^{2}+Y^{2} < 1 mm); Z(cm); N", 100, 0.0, 50.0);
    TH2F *histo_radius_Z=new TH2F("histo_radius_Z","Distance from beamline (r) vs Phantom depth (Z); Z (cm); r (cm);",100, 0, 50, 200, 0, 5);
        //YOU CAN CREATE YOUR HISTOGRAMS HERE
    
    
    
    
    
    
    
    
        // loop through all the entries in the data file
    for (int i = 0; i < entries; i++){
            // Read the single entry inside the data file (Now all the variables are
            // linked to the values at this entry
        YorkMedPhys->GetEntry(i);
        
            // (Z is in mm!! we want it in cm)each value of Z is put into the histograms:
            // This will give how many times there was an energy deposited in each range
            // defined by this bin in the histogram
        histo_example_Z->Fill(Z/10);
        
            // same as before, but now each entry is weighted with the energy deposited
            // at that moment. At the end this  will five the full energy deposited in
            // each bin in Z.
        histo_example->Fill(Z/10, Edep);
        double r=TMath::Sqrt(X*X+Y*Y);
        histo_radius_Z->Fill(Z/10, r/10, Edep);
            // We can make a cut on the data (NB variables in mm)
        if ((X*X + Y*Y) < 1){
                // (Z is in mm!! we want it in cm)each value of Z is put into the
                // histograms: This will give how many times there was an energy deposited
                // in each range defined by this bin in the histogram
            histo_example_Zcut->Fill(Z/10);
        }
        //FILL YOUR HISTOGRAMS HERE
        
        
    }
        // now the looop through all the entries is finished
    gStyle->SetOptStat(0);
        // Create a Canvas where to plot the histogram created
    TCanvas *C1 = new TCanvas ("C1","Histograms", 1200, 600);
    histo_example_Z->Draw(); // Draw the histogram
                             // Create a picture (just click on it in order to see it (or download it if
                             // you want to keep it)
    C1->Print("Z_picture.jpeg");
    histo_example_Zcut->Draw(); // Draw the histogram
                                // Create a picture (just click on it in order to see it (or download it if
                                // you want to keep it)
    C1->Print("Z_picture_CUT.jpeg");
    histo_example->Draw(); // Draw the histogram
                           // Create a picture (just click on it in order to see it (or download it if
                           // you want to keep it)
    C1->Print("Z_Edep_picture.jpeg");
    
        // we can also draw them together
    histo_example_Z->SetLineColor(2); // change the color of the histogram to red
    histo_example_Z->SetTitle("Histo example Z (N_{events} RED) (E_{dep} BLUE); Z (cm);");
    int max=(histo_example_Z->GetMaximum()>histo_example->GetMaximum())?histo_example_Z->GetMaximum() :
    histo_example->GetMaximum();
    C1->Clear();
        //C1=new TCanvas ("C1","Histograms", 1200, 600);
    C1->Divide(2,1);
    C1->cd(1);
    histo_example_Z->SetMaximum(max+500);
    histo_example_Z->SetMinimum(0);
    
    histo_example_Z->Draw();
    
    histo_example->Draw("SAME");
    C1->cd(2);
    gPad->SetLogz();
    histo_radius_Z->Draw("colz");
    
    
    C1->Print("Z_picture_comparison.jpeg");
    
        // we can also write the results in an output file
    TFile *file_output = new TFile("analysis_output.root","RECREATE");
    histo_example_Z->Write();
    histo_example_Zcut->Write();
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
