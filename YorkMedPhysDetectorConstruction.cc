#include "YorkMedPhysDetectorConstruction.hh"
#include "YorkMedPhysPhantomSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal
G4GlobalMagFieldMessenger*
 YorkMedPhysDetectorConstruction::fMagFieldMessenger = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysDetectorConstruction::YorkMedPhysDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true),
   fNofLayers(-1),
   fStepLimit(NULL)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysDetectorConstruction::~YorkMedPhysDetectorConstruction()
{
  delete fStepLimit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* YorkMedPhysDetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysDetectorConstruction::DefineMaterials()
{
  // Define water using NIST definition
  G4NistManager* nist = G4NistManager::Instance();

  nist->FindOrBuildMaterial("G4_AIR");
  nist->FindOrBuildMaterial("G4_WATER");
  nist->FindOrBuildMaterial("G4_SKIN_ICRP");
  nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  nist->FindOrBuildMaterial("G4_B-100_BONE");
  nist->FindOrBuildMaterial("G4_KEVLAR");
  nist->FindOrBuildMaterial("G4_B");
  nist->FindOrBuildMaterial("G4_Al");
  nist->FindOrBuildMaterial("G4_Pb");
  nist->FindOrBuildMaterial("G4_Concrete");
  nist->FindOrBuildMaterial("G4_O");



  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* YorkMedPhysDetectorConstruction::DefineVolumes()
{
  G4double worldEdgeSize = 1.0*m;

  G4double phantomSizeX  = 30.*cm;
  G4double phantomSizeY  = 30.*cm;
  G4double phantomThickness = 50.*cm;

  // Get materials for each volume (world and phantom)
  G4Material* worldMaterial = G4Material::GetMaterial("G4_AIR");
  G4Material* phantomSkin = G4Material::GetMaterial("G4_SKIN_ICRP");
  G4Material* phantomTissue = G4Material::GetMaterial("G4_A-150_TISSUE");
  G4Material* phantomBone = G4Material::GetMaterial("G4_B-100_BONE");
  //G4Material* phantomShield = G4Material::GetMaterial("G4_KEVLAR");
  //G4Material* phantomShield = G4Material::GetMaterial("G4_Al");
  //G4Material* phantomShield = G4Material::GetMaterial("G4_B");
  G4Material* phantomShield = G4Material::GetMaterial("G4_Pb");
  //G4Material* phantomShield = G4Material::GetMaterial("G4_AIR");
  //G4Material* phantomShield = G4Material::GetMaterial("G4_WATER");
  //G4Material* phantomShield = G4Material::GetMaterial("G4_Concrete");
  //G4Material* phantomShield = G4Material::GetMaterial("G4_O");




  if (!worldMaterial || !phantomSkin)
  {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve shield materials already defined.";
    G4Exception("YorkMedPhysDetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

  //First thing to do is define experimental area: World volume
  // World
  G4VSolid* worldSolid
    = new G4Box("World",           // its name
                 worldEdgeSize/2, worldEdgeSize/2, worldEdgeSize/2); // its size

  G4LogicalVolume* worldLogVol
    = new G4LogicalVolume(
                 worldSolid,           // its solid
                 worldMaterial,  // its material
                 "World");         // its name

  G4VPhysicalVolume* worldPhysVol
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLogVol,          // its logical volume
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  // water
  //G4VSolid* waterSolid
  //  = new G4Box("water",     // its name
  //               phantomSizeX/2, phantomSizeY/2, phantomThickness/2); // its size

  //G4LogicalVolume* waterLogVol
//    = new G4LogicalVolume(
//                 phantomMaterial,  // its material
//                 "waterLV");   // its name

//  G4VPhysicalVolume* waterphysical=new G4PVPlacement(
  //               0,                // no rotation
    //             G4ThreeVector(),  // at (0,0,0)
    //             waterLogVol,          // its logical volume
      //           "water",    // its name
        //         worldLogVol,          // its mother  volume
          //       false,            // no boolean operation
            //     0,                // copy number
              //   fCheckOverlaps);  // checking overlaps

//second water target
//G4VSolid* water2solid = new G4Box("water2",10,10,10);
////G4VPhysicalVolume* water2physical = new G4PVPlacement(0,G4ThreeVector(40,0,0),water2logic,"water2",worldLogVol,false,0,fCheckOverlaps);

//the body - solid, logical, physical
G4VSolid* skinSolid = new G4Tubs("skin", //name
      28*cm, 30*cm, //inner r, outer r
      50*cm, //length: -50 <z< 50
      0, 2*M_PI*rad); //rotation about 2pi radians
G4VSolid* tissueSolid = new G4Tubs("tissue", 5*cm, 28*cm, 50*cm, 0, 2*M_PI*rad);
G4VSolid* boneSolid = new G4Tubs("bone", 0*cm, 5*cm, 50*cm, 0, 2*M_PI*rad);

G4LogicalVolume* skinLogVol = new G4LogicalVolume(skinSolid, phantomSkin, "skinLV");
G4LogicalVolume* tissueLogVol = new G4LogicalVolume(tissueSolid, phantomTissue, "tissueLV");
G4LogicalVolume* boneLogVol = new G4LogicalVolume(boneSolid, phantomBone, "boneLV");

G4VPhysicalVolume* skinphysical= new G4PVPlacement(0, G4ThreeVector(0,0,0), skinLogVol, "skin", worldLogVol, false, 0, fCheckOverlaps);
G4VPhysicalVolume* tissuephysical=new G4PVPlacement(0, G4ThreeVector(0,0,0), tissueLogVol, "tissue", worldLogVol, false, 0, fCheckOverlaps);
G4VPhysicalVolume* bonephysical=new G4PVPlacement(0, G4ThreeVector(0,0,0), boneLogVol, "bone", worldLogVol, false, 0, fCheckOverlaps);

//shield - solid, logical, physical
G4VSolid* shieldSolid = new G4Box("shield", 0.5*cm, 20.0*cm, 20.0*cm);
G4LogicalVolume* shieldLogVol = new G4LogicalVolume(shieldSolid, phantomShield, "shieldLV");
G4VPhysicalVolume* shieldphysical = new G4PVPlacement(0, G4ThreeVector(-35*cm,0,0), shieldLogVol, "shield", worldLogVol, false, 0, fCheckOverlaps);

  G4double maxStep = 0.1*mm;
  fStepLimit = new G4UserLimits(maxStep);
  boneLogVol->SetUserLimits(fStepLimit);
  tissueLogVol->SetUserLimits(fStepLimit);
  skinLogVol->SetUserLimits(fStepLimit);
  shieldLogVol->SetUserLimits(fStepLimit);


  // //
  // // print parameters
  // //
  G4cout
    << G4endl
    << "------------------------------------------------------------" << G4endl
    << "---> The subject is a cylinder of " << phantomSizeX/mm << " mm * "
    << phantomSizeY/mm << " mm * " << phantomThickness << " mm of "
    << phantomBone->GetName()
    << "------------------------------------------------------------" << G4endl;

  //
  // Visualization attributes
  //
  worldLogVol->SetVisAttributes (G4VisAttributes::GetInvisible());

  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1., 1., 1.));
  simpleBoxVisAtt->SetVisibility(true);
  boneLogVol->SetVisAttributes(simpleBoxVisAtt);
  tissueLogVol->SetVisAttributes(simpleBoxVisAtt);
  skinLogVol->SetVisAttributes(simpleBoxVisAtt);
  shieldLogVol->SetVisAttributes(simpleBoxVisAtt);


  //
  // Always return the physical World
  //
  return worldPhysVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysDetectorConstruction::ConstructSDandField()

{
  // Sensitive detectors
  //create for all materials
  YorkMedPhysPhantomSD* PhantomSD
    = new YorkMedPhysPhantomSD("PhantomSD", "PhantomHitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(PhantomSD);
  SetSensitiveDetector("boneLV", PhantomSD); //phantomLV no longer exists
  SetSensitiveDetector("tissueLV", PhantomSD);
  SetSensitiveDetector("skinLV", PhantomSD);
  SetSensitiveDetector("shieldLV", PhantomSD);

//  YorkMedPhysBoneSD* BoneSD = new YorkMedPhysBoneSD("BoneSD", "BoneHitsCollection", 1);
//  G4SDManager::GetSDMpointer()->AddNewDetector(BoneSD);
//  SetSensitiveDetector("boneLV", BoneSD);

//  YorkMedPhysPhantomSD* waterSD = new YorkMedPhysPhantomSD("waterSD","waterHitsCollection",1);
  //G4SDManager::GetSDMpointer()->AddNewDetector(waterSD);
//SetSensitiveDetector("water2logic",waterSD);

  //
  // Magnetic field
  //
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
