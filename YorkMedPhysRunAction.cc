// $Id: YorkMedPhysRunAction.cc 100946 2016-11-03 11:28:08Z gcosmo $
//
/// \file YorkMedPhysRunAction.cc
/// \brief Implementation of the YorkMedPhysRunAction class

#include "YorkMedPhysRunAction.hh"
#include "YorkMedPhysAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysRunAction::YorkMedPhysRunAction()
 : G4UserRunAction()
{
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in YorkMedPhysAnalysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple

  // Creating histograms
  analysisManager->CreateH1("Edep_vs_z","Edep vs z; z(mm)", 500, 0., 50.*cm);
  analysisManager->CreateH1("Edep_vs_z_zoom10cm","Edep vs z; z(mm)", 100, 0., 10.*cm);
  analysisManager->CreateH1("Edep_vs_z_zoom20cm","Edep vs z; z(mm)", 100, 0., 20.*cm);
  analysisManager->CreateH1("Length","trackL in material; z(mm)", 500, 0., 0.5*m);
  //histograms for different materials
  analysisManager->CreateH1("Edep_vs_xy_bone","Edep bone; x(mm) y(mm)", 500, 0., 40*cm);
  analysisManager->CreateH1("Edep_vs_xy_tissue","Edep tissue; x(mm) y(mm)", 500, 0., 40*cm);
  analysisManager->CreateH1("Edep_vs_xy_skin","Edep skin; x(mm) y(mm)", 500, 0., 40*cm);
  analysisManager->CreateH1("Edep_vs_xy_shield","Edep shield; x(mm) y(mm)", 500, 0., 60*cm);


  // Creating ntuple
  //
  analysisManager->CreateNtuple("YorkMedPhys", "Edep spacial distribution");
  analysisManager->CreateNtupleDColumn("Edep"); //need to change to something different
  analysisManager->CreateNtupleDColumn("X");
  analysisManager->CreateNtupleDColumn("Y");
  analysisManager->CreateNtupleDColumn("Z");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysRunAction::~YorkMedPhysRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysRunAction::BeginOfRunAction(const G4Run*)
{
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "YorkMedPhys";
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysRunAction::EndOfRunAction(const G4Run*)
{
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//  if (analysisManager->GetH1(1))
  //{
    //G4cout << G4endl << " ----> print histograms statistic ";

    //if(isMaster)
     //G4cout << "for the entire run " << G4endl << G4endl;

    //else
     //G4cout << "for the local thread " << G4endl << G4endl;

    //G4cout << "Z-coordinate of energy depositions : mean = "
      // << G4BestUnit(analysisManager->GetH1(0)->mean(), "Length")
       //<< " rms = "
       //<< G4BestUnit(analysisManager->GetH1(0)->rms(),  "Length") << G4endl;

    //G4cout << "Track-length : mean = "
      //<< G4BestUnit(analysisManager->GetH1(3)->mean(), "Length")
      //<< " rms = "
      //<< G4BestUnit(analysisManager->GetH1(3)->rms(),  "Length") << G4endl;

  //}

  //save histograms & ntuple

  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
