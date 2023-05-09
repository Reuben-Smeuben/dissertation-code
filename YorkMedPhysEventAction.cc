// $Id: YorkMedPhysEventAction.cc 100946 2016-11-03 11:28:08Z gcosmo $
//
/// \file YorkMedPhysEventAction.cc
/// \brief Implementation of the YorkMedPhysEventAction class

#include "YorkMedPhysEventAction.hh"
#include "YorkMedPhysPhantomSD.hh"
#include "YorkMedPhysPhantomHit.hh"
#include "YorkMedPhysAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysEventAction::YorkMedPhysEventAction()
 : G4UserEventAction(),
   fPhantomHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysEventAction::~YorkMedPhysEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPhantomHitsCollection*
YorkMedPhysEventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
  YorkMedPhysPhantomHitsCollection* hitsCollection
    = static_cast<YorkMedPhysPhantomHitsCollection*>
    (event->GetHCofThisEvent()->GetHC(hcID));

//  if (!hitsCollection)
//  {
//    G4ExceptionDescription msg;
//    msg << "Cannot access hitsCollection ID " << hcID;
//    G4Exception("YorkMedPhysEventAction::GetHitsCollection()",
//      "MyCode0003", FatalException, msg);
//  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysEventAction::PrintEventStatistics(G4double phantomEdep,
 G4double phantomTrackLength) const
{
  // print event statistics
  //G4cout
  //   << "   Energy deposited in the phantom = "
  //   << std::setw(7) << G4BestUnit(phantomEdep, "Energy")
//     << "       Track length of the primary particle = "
//     << std::setw(7) << G4BestUnit(phantomTrackLength, "Length")
//     << G4endl;
}

void YorkMedPhysEventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysEventAction::EndOfEventAction(const G4Event* event)
{
  // Get hits collections IDs (only once)
  if (fPhantomHCID == -1)
  {
    fPhantomHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("PhantomHitsCollection");
  }

  // Get hits collections
  YorkMedPhysPhantomHitsCollection* phantomHC =
   GetHitsCollection(fPhantomHCID, event);

  // Get hit with total values
  YorkMedPhysPhantomHit* phantomHit = (*phantomHC)[phantomHC->entries()-1];

  // Print per event (modulo n)
  //
  G4int eventID = event->GetEventID();
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();

  if ((printModulo > 0) && (eventID % printModulo == 0))
  {
  //  G4cout << "---> End of event: " << eventID << G4endl;

  //  PrintEventStatistics(phantomHit->GetEdep(), phantomHit->GetTrackLength());
  }

  // Fill histograms, ntuple
  //

  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  // analysisManager->FillH1(0, phantomHit->GetEdep());
//  analysisManager->FillH1(3, phantomHit->GetTrackLength());

  // // fill ntuple
  // analysisManager->FillNtupleDColumn(0, phantomHit->GetEdep());
  // analysisManager->FillNtupleDColumn(2, phantomHit->GetTrackLength());
  // analysisManager->AddNtupleRow();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
