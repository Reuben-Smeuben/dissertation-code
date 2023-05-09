#include "YorkMedPhysPhantomSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPhantomSD::YorkMedPhysPhantomSD(
                            const G4String& name,
                            const G4String& hitsCollectionName,
                            G4int nofCells)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr),
   fNofCells(nofCells)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPhantomSD::~YorkMedPhysPhantomSD()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysPhantomSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection
    = new YorkMedPhysPhantomHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);

  // Create hits
  // fNofCells for cells + one more for total sums
  for (G4int i = 0; i < fNofCells + 1; i++)
  {
    fHitsCollection->insert(new YorkMedPhysPhantomHit());
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool YorkMedPhysPhantomSD::ProcessHits(G4Step* step,
                                     G4TouchableHistory*)
{
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  if (0.0 < edep)
  {
    G4ThreeVector p1 = step->GetPreStepPoint()->GetPosition();
    G4ThreeVector p2 = step->GetPostStepPoint()->GetPosition();

    G4double x1 = p1.x();
    G4double y1 = p1.y();
    G4double z1 = p1.z();

    G4double x2 = p2.x();
    G4double y2 = p2.y();
    G4double z2 = p2.z();

    G4double x0 = 0.5*(x1 + x2);
    G4double y0 = 0.5*(y1 + y2);
    G4double z0 = 0.5*(z1 + z2);

    analysisManager->FillH1(0, z0 + 0.*cm, edep);
    analysisManager->FillH1(1, z0 + 0.*cm, edep);
    analysisManager->FillH1(2, z0 + 0.*cm, edep);
    analysisManager->FillNtupleDColumn(0, edep/MeV);
    analysisManager->FillNtupleDColumn(1, x0);
    analysisManager->FillNtupleDColumn(2, y0);
    analysisManager->FillNtupleDColumn(3, z0 + 0.*cm);
    analysisManager->AddNtupleRow();
  }

  // step length
  G4double stepLength = 0.;

  if (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
  {
    stepLength = step->GetStepLength();
  }

  if (edep == 0. && stepLength == 0.) return false;

  const G4VTouchable* touchable = (step->GetPreStepPoint()->GetTouchable());

  // Get calorimeter cell id
  G4int layerNumber = touchable->GetReplicaNumber(1);

  // Get hit accounting data for this cell
  YorkMedPhysPhantomHit* hit = (*fHitsCollection)[layerNumber];

  if (!hit)
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hit " << layerNumber;
    G4Exception("YorkMedPhysPhantomSD::ProcessHits()",
      "MyCode0004", FatalException, msg);
  }

  // Get hit for total accounting
  YorkMedPhysPhantomHit* hitTotal =
   (*fHitsCollection)[fHitsCollection->entries() - 1];

  // Add values
  hit->Add(edep, stepLength);
  hitTotal->Add(edep, stepLength);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysPhantomSD::EndOfEvent(G4HCofThisEvent*)
{
  if (verboseLevel > 1)
  {
     G4int nofHits = fHitsCollection->entries();

     G4cout
       << G4endl
       << "-------->In this event there are " << nofHits
       << " hits in the phantom: " << G4endl;
     for (G4int i = 0; i < nofHits; i++) (*fHitsCollection)[i]->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
