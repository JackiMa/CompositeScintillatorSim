// --- Lab 27 CERN ---

#include "MyMaterials.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"

using namespace CLHEP;

MyMaterials::MyMaterials()
{
}

MyMaterials::~MyMaterials()
{
}

G4Material *MyMaterials::Boron()
// Boron Sputtering Target 1000035066-technical-data.pdf
{
  G4double a, z, density;
  G4int nelements;
  G4Element *B = new G4Element("Boron", "B", z = 5., a = 10.810 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Material *mat = new G4Material("Boron", density = 2.355 * g / cm3, nelements = 2);
  mat->AddElement(B, 99.5 * perCent);
  mat->AddElement(C, 0.5 * perCent);
  return mat;
}
G4Material *MyMaterials::TantalumFoil()
// Tantalum Foil, property data from 1000042754-technical-data.pdf
{
  G4double a, z, density;
  G4int nelements;
  G4Element *Ta = new G4Element("Tantalum", "Ta", z = 73, a = 180.9479 * g / mole);
  G4Material *mat = new G4Material("TantalumFoil", density = 16.6 * g / cm3, nelements = 1);
  mat->AddElement(Ta, 100 * perCent);
  return mat;
}

G4Material *MyMaterials::Graphite()
// Graphite, property data from https://poco.entegris.com/content/dam/poco/resources/reference-materials/brochures/brochure-graphite-properties-and-characteristics-11043.pdf
{
  G4double a, z, density;
  G4int nelements;
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Material *mat = new G4Material("Graphite", density = 2.26 * g / cm3, nelements = 1);
  mat->AddElement(C, 100 * perCent);
  return mat;
}

G4Material *MyMaterials::PEEK()
{
  G4double a, z, density;
  G4int nelements;
  G4Element *H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
  G4Material *mat = new G4Material("PEEK", density = 1.32 * g / cm3, nelements = 3);
  mat->AddElement(H, 12);
  mat->AddElement(C, 19);
  mat->AddElement(O, 3);
  return mat;
}

G4Material *MyMaterials::Air()
{
  G4double a, z, density;
  G4int nelements;

  G4Element *N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);

  G4Material *mat = new G4Material("Air", density = 1.29 * mg / cm3, nelements = 2);
  mat->AddElement(N, 70. * perCent);
  mat->AddElement(O, 30. * perCent);

  std::vector<G4double> PhotonEnergy_RI =
      {0.1000 * eV, 1.0000 * eV, 1.0121 * eV, 1.0332 * eV,
       1.0552 * eV, 1.0781 * eV, 1.1021 * eV, 1.1271 * eV,
       1.1533 * eV, 1.1808 * eV, 1.2096 * eV, 1.2398 * eV,
       1.2716 * eV, 1.3051 * eV, 1.3404 * eV, 1.3776 * eV,
       1.4170 * eV, 1.4586 * eV, 1.5028 * eV, 1.5498 * eV,
       1.5998 * eV, 1.6531 * eV, 1.7101 * eV, 1.7712 * eV,
       1.8368 * eV, 1.9074 * eV, 1.9837 * eV, 2.0664 * eV,
       2.1562 * eV, 2.2543 * eV, 2.3616 * eV, 2.4797 * eV,
       2.6102 * eV, 2.7552 * eV, 2.9173 * eV, 3.0996 * eV,
       3.3062 * eV, 3.5424 * eV, 3.8149 * eV, 4.1328 * eV,
       4.5085 * eV, 4.9594 * eV};

  std::vector<G4double> RefractiveIndex =
      {1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::AirKiller()
{
  G4double a, z, density;
  G4int nelements;

  G4Element *N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);

  G4Material *mat = new G4Material("AirKiller", density = 1.29 * mg / cm3, nelements = 2);
  mat->AddElement(N, 70. * perCent);
  mat->AddElement(O, 30. * perCent);

  std::vector<G4double> PhotonEnergy_RI =
      {0.1000 * eV, 1.0000 * eV, 1.0121 * eV, 1.0332 * eV,
       1.0552 * eV, 1.0781 * eV, 1.1021 * eV, 1.1271 * eV,
       1.1533 * eV, 1.1808 * eV, 1.2096 * eV, 1.2398 * eV,
       1.2716 * eV, 1.3051 * eV, 1.3404 * eV, 1.3776 * eV,
       1.4170 * eV, 1.4586 * eV, 1.5028 * eV, 1.5498 * eV,
       1.5998 * eV, 1.6531 * eV, 1.7101 * eV, 1.7712 * eV,
       1.8368 * eV, 1.9074 * eV, 1.9837 * eV, 2.0664 * eV,
       2.1562 * eV, 2.2543 * eV, 2.3616 * eV, 2.4797 * eV,
       2.6102 * eV, 2.7552 * eV, 2.9173 * eV, 3.0996 * eV,
       3.3062 * eV, 3.5424 * eV, 3.8149 * eV, 4.1328 * eV,
       4.5085 * eV, 4.9594 * eV};

  std::vector<G4double> RefractiveIndex =
      {1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003, 1.0003, 1.0003,
       1.0003, 1.0003};

  std::vector<G4double> PhotonEnergy_ABS = PhotonEnergy_RI;

  std::vector<G4double> Absorption =
      {1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm, 1e-6 * mm, 1e-6 * mm,
       1e-6 * mm, 1e-6 * mm};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::Water()
{
  G4double a, z, density;
  G4int nelements;

  G4Element *H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);

  G4Material *mat = new G4Material("Water", density = 1.0 * g / cm3, nelements = 2);
  mat->AddElement(H, 2);
  mat->AddElement(O, 1);

  const G4int nEntries = 33;
  G4double PhotonEnergy[nEntries] =
      {0.100 * eV, 2.034 * eV, 2.068 * eV, 2.103 * eV,
       2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV,
       2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV,
       2.481 * eV, 2.532 * eV, 2.585 * eV, 2.640 * eV,
       2.697 * eV, 2.757 * eV, 2.820 * eV, 2.885 * eV,
       2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV,
       3.265 * eV, 3.353 * eV, 3.446 * eV, 3.545 * eV,
       3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV,
       4.136 * eV};
  G4double RefractiveIndex[nEntries] =
      {1.3435, 1.3435, 1.3440, 1.3445,
       1.3450, 1.3455, 1.3460, 1.3465,
       1.3470, 1.3475, 1.3480, 1.3485,
       1.3492, 1.3500, 1.3505, 1.3510,
       1.3518, 1.3522, 1.3530, 1.3535,
       1.3540, 1.3545, 1.3550, 1.3555,
       1.3560, 1.3568, 1.3572, 1.3580,
       1.3585, 1.3590, 1.3595, 1.3600,
       1.3608};
  G4double Absorption[nEntries] =
      {3.448 * m, 3.448 * m, 4.082 * m, 6.329 * m,
       9.174 * m, 12.346 * m, 13.889 * m, 15.152 * m,
       17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m,
       35.714 * m, 45.455 * m, 47.619 * m, 52.632 * m,
       52.632 * m, 55.556 * m, 52.632 * m, 52.632 * m,
       47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m,
       33.333 * m, 30.000 * m, 28.500 * m, 27.000 * m,
       24.500 * m, 22.000 * m, 19.500 * m, 17.500 * m,
       14.500 * m};
  G4double FastComponent[nEntries] =
      {1.00, 1.00, 1.00, 1.00,
       1.00, 1.00, 1.00, 1.00,
       1.00, 1.00, 1.00, 1.00,
       1.00, 1.00, 1.00, 1.00,
       1.00, 1.00, 1.00, 1.00,
       1.00, 1.00, 1.00, 1.00,
       1.00, 1.00, 1.00, 1.00,
       1.00, 1.00, 1.00, 1.00,
       1.00};
  G4double SlowComponent[nEntries] =
      {0.01, 0.01, 1.00, 2.00,
       3.00, 4.00, 5.00, 6.00,
       7.00, 8.00, 9.00, 8.00,
       7.00, 6.00, 4.00, 3.00,
       2.00, 1.00, 0.01, 1.00,
       2.00, 3.00, 4.00, 5.00,
       6.00, 7.00, 8.00, 9.00,
       8.00, 7.00, 6.00, 5.00,
       4.00};

  double lightyield = 50;
  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy, Absorption, nEntries);
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy, FastComponent, nEntries);
  myMPT->AddProperty("SCINTILLATIONCOMPONENT2", PhotonEnergy, SlowComponent, nEntries);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 1.0);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1. * ns);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 10. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 0.8);
  myMPT->AddConstProperty("SCINTILLATIONYIELD2", 0.2);
  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::Vacuum()
{
  G4double a, z, density;
  G4int nelements;

  G4Element *N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);

  G4Material *mat = new G4Material("Vacuum", density = 0.001 * mg / cm3, nelements = 2);
  mat->AddElement(N, 70. * perCent);
  mat->AddElement(O, 30. * perCent);

  const G4int nEntries = 3;
  G4double PhotonEnergy[nEntries] =
      {0.0001 * eV, 1.00 * eV, 100.00 * eV};
  G4double RefractiveIndex[nEntries] =
      {1.00, 1.00, 1.00};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::Silicon()
{
  G4double a, z, density;

  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);

  G4Material *mat = new G4Material("Silicon", density = 2.33 * g / cm3, 1);
  mat->AddElement(Si, 1);

  const G4int nEntries = 4;
  G4double PhotonEnergy[nEntries] =
      {0.0001 * eV, 1.0 * eV, 1.84 * eV, 6.26 * eV};
  G4double RefractiveIndex[nEntries] =
      {4.0, 4.0, 4.0, 4.0};
  G4double Absorption[nEntries] =
      {0.1 * mm, 0.1 * mm, 0.1 * mm, 0.1 * mm};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy, Absorption, nEntries);

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::Tyvek()
{
  //--------------------------------------------------
  //  Polyethylene
  //--------------------------------------------------
  G4double a, z, density;

  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Element *H = new G4Element("Hydrogenum", "H", z = 1., a = 1.008 * g / mole);

  G4Material *mat = new G4Material("Tyvek", density = 1.200 * g / cm3, 2);
  mat->AddElement(C, 2);
  mat->AddElement(H, 4);

  return mat;
}

G4Material *MyMaterials::Pethylene(double scaleFactor)
{
  //--------------------------------------------------
  //  Polyethylene
  //--------------------------------------------------
  G4double a, z, density;

  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Element *H = new G4Element("Hydrogenum", "H", z = 1., a = 1.008 * g / mole);

  G4Material *mat = new G4Material("Pethylene", density = 1.200 * g / cm3, 2);
  mat->AddElement(C, 2);
  mat->AddElement(H, 4);

  //
  // ------------ Generate & Add Material Properties Table ------------
  //

  G4double photonEnergy[] =                                    // scale in  nm
      {2.00 * eV, 2.03 * eV, 2.06 * eV, 2.09 * eV, 2.12 * eV,  // 620, 611, 602, 593, 585
       2.15 * eV, 2.18 * eV, 2.21 * eV, 2.24 * eV, 2.27 * eV,  // 576, 569, 561, 553, 546
       2.30 * eV, 2.33 * eV, 2.36 * eV, 2.39 * eV, 2.42 * eV,  // 539, 532, 525, 518, 512
       2.45 * eV, 2.48 * eV, 2.51 * eV, 2.54 * eV, 2.57 * eV,  // 506, 500, 494, 488, 482
       2.60 * eV, 2.63 * eV, 2.66 * eV, 2.69 * eV, 2.72 * eV,  // 476, 471, 466, 461, 456
       2.75 * eV, 2.78 * eV, 2.81 * eV, 2.84 * eV, 2.87 * eV,  // 450, 446, 441, 436, 432
       2.90 * eV, 2.93 * eV, 2.96 * eV, 2.99 * eV, 3.02 * eV,  // 427, 423, 419, 414, 410
       3.05 * eV, 3.08 * eV, 3.11 * eV, 3.14 * eV, 3.17 * eV,  // 406, 402, 398, 394, 391
       3.20 * eV, 3.23 * eV, 3.26 * eV, 3.29 * eV, 3.32 * eV,  // 387, 384, 380, 376, 373
       3.35 * eV, 3.38 * eV, 3.41 * eV, 3.44 * eV, 3.47 * eV}; // 370, 366, 363, 360, 357

  const G4int nEntries = sizeof(photonEnergy) / sizeof(G4double);

  G4double refractiveIndexClad1[] =
      {1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
       1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
       1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
       1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
       1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49};

  assert(sizeof(refractiveIndexClad1) == sizeof(photonEnergy));

  G4double absClad[] =
      {43.76 * m, 47.06 * m, 50.37 * m, 53.72 * m, 56.73 * m, 59.99 * m, 62.57 * m, 62.52 * m, 62.01 * m, 61.54 * m,
       60.98 * m, 60.50 * m, 59.99 * m, 59.60 * m, 59.56 * m, 58.44 * m, 57.50 * m, 53.51 * m, 50.24 * m, 48.95 * m,
       48.74 * m, 49.38 * m, 48.78 * m, 41.40 * m, 45.69 * m, 43.41 * m, 42.08 * m, 40.45 * m, 38.73 * m, 37.49 * m,
       35.47 * m, 33.67 * m, 32.12 * m, 30.62 * m, 29.50 * m, 28.51 * m, 27.53 * m, 24.82 * m, 20.35 * m, 16.79 * m, // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       13.91 * m, 12.41 * m, 10.61 * m, 6.74 * m, 3.82 * m, 1.25 * m, 0.82 * m, 0.43 * m, 0.13 * m, 0.13 * m};       // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(absClad) == sizeof(photonEnergy));

  for (int i = 0; i < nEntries; i++)
  {
    absClad[i] = absClad[i] * scaleFactor;
  }

  // Add entries into properties table
  G4MaterialPropertiesTable *mptClad1 = new G4MaterialPropertiesTable();
  mptClad1->AddProperty("RINDEX", photonEnergy, refractiveIndexClad1, nEntries);
  mptClad1->AddProperty("ABSLENGTH", photonEnergy, absClad, nEntries);

  mat->SetMaterialPropertiesTable(mptClad1);

  return mat;
}

G4Material *MyMaterials::Shashlik_Polystyrene() // NOT USED, polystyrene in SHASHLIK modules is "Polystyrene" function in this file
{
  //--------------------------------------------------
  //  Polystyrene
  //--------------------------------------------------

  G4double a, z;
  G4Element *H = new G4Element("Hydrogen", "H", z = 1., a = 1.01 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);

  G4Material *mat = new G4Material("Shashlik_Polystyrene", 1.050 * g / cm3, 2); // AMCRYS producer
  mat->AddElement(C, 8);
  mat->AddElement(H, 8);

  //
  // ------------ Generate & Add Material Properties Table ------------
  //

  G4double photonEnergy[] =                                    // scale in  nm
      {2.00 * eV, 2.03 * eV, 2.06 * eV, 2.09 * eV, 2.12 * eV,  // 620, 611, 602, 593, 585
       2.15 * eV, 2.18 * eV, 2.21 * eV, 2.24 * eV, 2.27 * eV,  // 576, 569, 561, 553, 546
       2.30 * eV, 2.33 * eV, 2.36 * eV, 2.39 * eV, 2.42 * eV,  // 539, 532, 525, 518, 512
       2.45 * eV, 2.48 * eV, 2.51 * eV, 2.54 * eV, 2.57 * eV,  // 506, 500, 494, 488, 482
       2.60 * eV, 2.63 * eV, 2.66 * eV, 2.69 * eV, 2.72 * eV,  // 476, 471, 466, 461, 456
       2.75 * eV, 2.78 * eV, 2.81 * eV, 2.84 * eV, 2.87 * eV,  // 450, 446, 441, 436, 432
       2.90 * eV, 2.93 * eV, 2.96 * eV, 2.99 * eV, 3.02 * eV,  // 427, 423, 419, 414, 410
       3.05 * eV, 3.08 * eV, 3.11 * eV, 3.14 * eV, 3.17 * eV,  // 406, 402, 398, 394, 391
       3.20 * eV, 3.23 * eV, 3.26 * eV, 3.29 * eV, 3.32 * eV,  // 387, 384, 380, 376, 373
       3.35 * eV, 3.38 * eV, 3.41 * eV, 3.44 * eV, 3.47 * eV}; // 370, 366, 363, 360, 357

  const G4int nEntries = sizeof(photonEnergy) / sizeof(G4double);

  G4double refractiveIndexPS[] =
      {1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
       1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
       1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
       1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
       1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58};

  assert(sizeof(refractiveIndexPS) == sizeof(photonEnergy));

  // absorption spectra for PS + pTP + POPOP. Original spectra defined up to 700 nm
  //  Reference page 7 of : https://indico.cern.ch/event/143675/contributions/164201/attachments/132452/187976/pahlka_near_detector_workshop.pdf
  G4double absPS[] =
      {4.56 * m, 4.18 * m, 4.29 * m, 4.53 * m, 4.58 * m, 4.57 * m, 4.55 * m, 4.55 * m, 4.55 * m, 4.54 * m,  // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       4.52 * m, 4.43 * m, 4.47 * m, 4.46 * m, 4.39 * m, 4.32 * m, 4.23 * m, 4.13 * m, 4.06 * m, 3.97 * m,  // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       3.82 * m, 3.74 * m, 3.64 * m, 3.54 * m, 3.44 * m, 3.29 * m, 3.21 * m, 3.09 * m, 2.97 * m, 2.86 * m,  // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       2.58 * m, 2.02 * m, 1.21 * m, 0.31 * m, 0.09 * m, 0.04 * m, 1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm,  // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm, 1.0 * mm}; // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(absPS) == sizeof(photonEnergy));

  G4double scintilFast[] =
      {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000,  // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       0.000, 0.000, 0.000, 0.025, 0.038, 0.053, 0.072, 0.010, 0.012, 0.016,  // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       0.201, 0.251, 0.323, 0.400, 0.463, 0.530, 0.593, 0.800, 0.948, 0.995,  // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       0.969, 0.900, 0.800, 0.629, 0.500, 0.361, 0.259, 0.186, 0.139, 0.115,  // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       0.093, 0.079, 0.066, 0.051, 0.043, 0.037, 0.033, 0.030, 0.028, 0.028}; // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(scintilFast) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable *mptPolystyrene = new G4MaterialPropertiesTable();
  mptPolystyrene->AddProperty("RINDEX", photonEnergy, refractiveIndexPS, nEntries);
  mptPolystyrene->AddProperty("ABSLENGTH", photonEnergy, absPS, nEntries);
  mptPolystyrene->AddProperty("FASTCOMPONENT", photonEnergy, scintilFast, nEntries);
  mptPolystyrene->AddConstProperty("SCINTILLATIONYIELD", 10000 / MeV); // reduced 1/10 to compensate crystal efficiency
  mptPolystyrene->AddConstProperty("RESOLUTIONSCALE", 1.0);
  mptPolystyrene->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2. * ns); // was 10 ns

  mat->SetMaterialPropertiesTable(mptPolystyrene);

  // Set the Birks Constant for the Polystyrene scintillator
  mat->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
  return mat;
}

G4Material *MyMaterials::PMMA()
{
  //--------------------------------------------------
  // WLSfiber PMMA
  //--------------------------------------------------
  G4double a, z, density;

  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Element *H = new G4Element("Hydrogenum", "H", z = 1., a = 1.008 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("PMMA", density = 1.190 * g / cm3, 3);
  mat->AddElement(C, 5);
  mat->AddElement(H, 8);
  mat->AddElement(O, 2);

  //
  // ------------ Generate & Add Material Properties Table ------------
  //

  G4double photonEnergy[] =                                    // scale in  nm
      {2.00 * eV, 2.03 * eV, 2.06 * eV, 2.09 * eV, 2.12 * eV,  // 620, 611, 602, 593, 585
       2.15 * eV, 2.18 * eV, 2.21 * eV, 2.24 * eV, 2.27 * eV,  // 576, 569, 561, 553, 546
       2.30 * eV, 2.33 * eV, 2.36 * eV, 2.39 * eV, 2.42 * eV,  // 539, 532, 525, 518, 512
       2.45 * eV, 2.48 * eV, 2.51 * eV, 2.54 * eV, 2.57 * eV,  // 506, 500, 494, 488, 482
       2.60 * eV, 2.63 * eV, 2.66 * eV, 2.69 * eV, 2.72 * eV,  // 476, 471, 466, 461, 456
       2.75 * eV, 2.78 * eV, 2.81 * eV, 2.84 * eV, 2.87 * eV,  // 450, 446, 441, 436, 432
       2.90 * eV, 2.93 * eV, 2.96 * eV, 2.99 * eV, 3.02 * eV,  // 427, 423, 419, 414, 410
       3.05 * eV, 3.08 * eV, 3.11 * eV, 3.14 * eV, 3.17 * eV,  // 406, 402, 398, 394, 391
       3.20 * eV, 3.23 * eV, 3.26 * eV, 3.29 * eV, 3.32 * eV,  // 387, 384, 380, 376, 373
       3.35 * eV, 3.38 * eV, 3.41 * eV, 3.44 * eV, 3.47 * eV}; // 370, 366, 363, 360, 357

  const G4int nEntries = sizeof(photonEnergy) / sizeof(G4double);

  G4double refractiveIndexWLSfiber[] =
      {1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60};

  assert(sizeof(refractiveIndexWLSfiber) == sizeof(photonEnergy));

  G4double absWLSfiber[] =
      {18.53 * m, 7.80 * m, 8.65 * m, 16.44 * m, 17.72 * m, 16.65 * m, 15.05 * m, 14.29 * m, 13.41 * m, 12.31 * m, // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       10.30 * m, 8.21 * m, 8.34 * m, 7.23 * m, 5.64 * m, 3.54 * m, 2.04 * m, 1.02 * m, 0.16 * m, 1. * mm,         // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm};                  // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(absWLSfiber) == sizeof(photonEnergy));

  G4double emissionFib[] =
      {0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.08, 0.13, 0.18, 0.22,  // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       0.27, 0.31, 0.45, 0.62, 0.74, 0.76, 0.71, 0.69, 0.81, 0.95,  // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       0.99, 0.72, 0.43, 0.20, 0.09, 0.01, 0.01, 0.00, 0.00, 0.00,  // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,  // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}; // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(emissionFib) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable *mptWLSfiber = new G4MaterialPropertiesTable();
  mptWLSfiber->AddProperty("RINDEX", photonEnergy, refractiveIndexWLSfiber, nEntries);
  mptWLSfiber->AddProperty("ABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSCOMPONENT", photonEnergy, emissionFib, nEntries);
  mptWLSfiber->AddConstProperty("WLSTIMECONSTANT", 10 * ns); // !SK: time shift
                                                             //  mptWLSfiber->AddConstProperty("WLSFASTTIMECONSTANT", 10.*ns); // was 10 ns

  mat->SetMaterialPropertiesTable(mptWLSfiber);

  return mat;
}

G4Material *MyMaterials::PMMA_Y11(double scaleFactor)
{
  //--------------------------------------------------
  // WLSfiber PMMA
  //--------------------------------------------------
  G4double a, z, density;

  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Element *H = new G4Element("Hydrogenum", "H", z = 1., a = 1.008 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("PMMA_Y11", density = 1.190 * g / cm3, 3);
  mat->AddElement(C, 5);
  mat->AddElement(H, 8);
  mat->AddElement(O, 2);

  //
  // ------------ Generate & Add Material Properties Table ------------
  //

  G4double photonEnergy[] =                                    // scale in  nm
      {2.00 * eV, 2.03 * eV, 2.06 * eV, 2.09 * eV, 2.12 * eV,  // 620, 611, 602, 593, 585
       2.15 * eV, 2.18 * eV, 2.21 * eV, 2.24 * eV, 2.27 * eV,  // 576, 569, 561, 553, 546
       2.30 * eV, 2.33 * eV, 2.36 * eV, 2.39 * eV, 2.42 * eV,  // 539, 532, 525, 518, 512
       2.45 * eV, 2.48 * eV, 2.51 * eV, 2.54 * eV, 2.57 * eV,  // 506, 500, 494, 488, 482
       2.60 * eV, 2.63 * eV, 2.66 * eV, 2.69 * eV, 2.72 * eV,  // 476, 471, 466, 461, 456
       2.75 * eV, 2.78 * eV, 2.81 * eV, 2.84 * eV, 2.87 * eV,  // 450, 446, 441, 436, 432
       2.90 * eV, 2.93 * eV, 2.96 * eV, 2.99 * eV, 3.02 * eV,  // 427, 423, 419, 414, 410
       3.05 * eV, 3.08 * eV, 3.11 * eV, 3.14 * eV, 3.17 * eV,  // 406, 402, 398, 394, 391
       3.20 * eV, 3.23 * eV, 3.26 * eV, 3.29 * eV, 3.32 * eV,  // 387, 384, 380, 376, 373
       3.35 * eV, 3.38 * eV, 3.41 * eV, 3.44 * eV, 3.47 * eV}; // 370, 366, 363, 360, 357

  const G4int nEntries = sizeof(photonEnergy) / sizeof(G4double);

  G4double refractiveIndexWLSfiber[] =
      {1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60};

  assert(sizeof(refractiveIndexWLSfiber) == sizeof(photonEnergy));

  G4double absWLSfiber[] =
      {18.53 * m, 7.80 * m, 8.65 * m, 16.44 * m, 17.72 * m, 16.65 * m, 15.05 * m, 14.29 * m, 13.41 * m, 12.31 * m, // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       10.30 * m, 8.21 * m, 8.34 * m, 7.23 * m, 5.64 * m, 3.54 * m, 2.04 * m, 1.02 * m, 0.16 * m, 1. * mm,         // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm};                  // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(absWLSfiber) == sizeof(photonEnergy));

  for (int i = 0; i < nEntries; i++)
  {
    absWLSfiber[i] = absWLSfiber[i] * scaleFactor;
  }

  G4double emissionFib[] =
      {0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.08, 0.13, 0.18, 0.22,  // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       0.27, 0.31, 0.45, 0.62, 0.74, 0.76, 0.71, 0.69, 0.81, 0.95,  // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       0.99, 0.72, 0.43, 0.20, 0.09, 0.01, 0.01, 0.00, 0.00, 0.00,  // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,  // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}; // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(emissionFib) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable *mptWLSfiber = new G4MaterialPropertiesTable();
  mptWLSfiber->AddProperty("RINDEX", photonEnergy, refractiveIndexWLSfiber, nEntries);
  mptWLSfiber->AddProperty("ABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSCOMPONENT", photonEnergy, emissionFib, nEntries);
  mptWLSfiber->AddConstProperty("WLSTIMECONSTANT", 7 * ns); // !SK: time shift
                                                            //  mptWLSfiber->AddConstProperty("WLSFASTTIMECONSTANT", 10.*ns); // was 10 ns

  mat->SetMaterialPropertiesTable(mptWLSfiber);

  return mat;
}

G4Material *MyMaterials::PMMA_YS2(double scaleFactor)
{
  //--------------------------------------------------
  // WLSfiber PMMA
  //--------------------------------------------------
  G4double a, z, density;

  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Element *H = new G4Element("Hydrogenum", "H", z = 1., a = 1.008 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("PMMA_YS2", density = 1.190 * g / cm3, 3);
  mat->AddElement(C, 5);
  mat->AddElement(H, 8);
  mat->AddElement(O, 2);

  //
  // ------------ Generate & Add Material Properties Table ------------
  //

  G4double photonEnergy[] =                                    // scale in  nm
      {2.00 * eV, 2.03 * eV, 2.06 * eV, 2.09 * eV, 2.12 * eV,  // 620, 611, 602, 593, 585
       2.15 * eV, 2.18 * eV, 2.21 * eV, 2.24 * eV, 2.27 * eV,  // 576, 569, 561, 553, 546
       2.30 * eV, 2.33 * eV, 2.36 * eV, 2.39 * eV, 2.42 * eV,  // 539, 532, 525, 518, 512
       2.45 * eV, 2.48 * eV, 2.51 * eV, 2.54 * eV, 2.57 * eV,  // 506, 500, 494, 488, 482
       2.60 * eV, 2.63 * eV, 2.66 * eV, 2.69 * eV, 2.72 * eV,  // 476, 471, 466, 461, 456
       2.75 * eV, 2.78 * eV, 2.81 * eV, 2.84 * eV, 2.87 * eV,  // 450, 446, 441, 436, 432
       2.90 * eV, 2.93 * eV, 2.96 * eV, 2.99 * eV, 3.02 * eV,  // 427, 423, 419, 414, 410
       3.05 * eV, 3.08 * eV, 3.11 * eV, 3.14 * eV, 3.17 * eV,  // 406, 402, 398, 394, 391
       3.20 * eV, 3.23 * eV, 3.26 * eV, 3.29 * eV, 3.32 * eV,  // 387, 384, 380, 376, 373
       3.35 * eV, 3.38 * eV, 3.41 * eV, 3.44 * eV, 3.47 * eV}; // 370, 366, 363, 360, 357

  const G4int nEntries = sizeof(photonEnergy) / sizeof(G4double);

  G4double refractiveIndexWLSfiber[] =
      {1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60};

  assert(sizeof(refractiveIndexWLSfiber) == sizeof(photonEnergy));

  G4double absWLSfiber[] =
      {18.53 * m, 7.80 * m, 8.65 * m, 16.44 * m, 17.72 * m, 16.65 * m, 15.05 * m, 14.29 * m, 13.41 * m, 12.31 * m, // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       10.30 * m, 8.21 * m, 8.34 * m, 7.23 * m, 5.64 * m, 3.54 * m, 2.04 * m, 1.02 * m, 0.16 * m, 1. * mm,         // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm};                  // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(absWLSfiber) == sizeof(photonEnergy));

  for (int i = 0; i < nEntries; i++)
  {
    absWLSfiber[i] = absWLSfiber[i] * scaleFactor;
  }

  G4double emissionFib[] =
      {0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.08, 0.13, 0.18, 0.22,  // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       0.27, 0.31, 0.45, 0.62, 0.74, 0.76, 0.71, 0.69, 0.81, 0.95,  // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       0.99, 0.72, 0.43, 0.20, 0.09, 0.01, 0.01, 0.00, 0.00, 0.00,  // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,  // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}; // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(emissionFib) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable *mptWLSfiber = new G4MaterialPropertiesTable();
  mptWLSfiber->AddProperty("RINDEX", photonEnergy, refractiveIndexWLSfiber, nEntries);
  mptWLSfiber->AddProperty("ABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSCOMPONENT", photonEnergy, emissionFib, nEntries);
  mptWLSfiber->AddConstProperty("WLSTIMECONSTANT", 2.5 * ns); // !SK: time shift
                                                              //  mptWLSfiber->AddConstProperty("WLSFASTTIMECONSTANT", 10.*ns); // was 10 ns

  mat->SetMaterialPropertiesTable(mptWLSfiber);

  return mat;
}

G4Material *MyMaterials::PMMA_YS4(double scaleFactor)
{
  //--------------------------------------------------
  // WLSfiber PMMA
  //--------------------------------------------------
  G4double a, z, density;

  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  G4Element *H = new G4Element("Hydrogenum", "H", z = 1., a = 1.008 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("PMMA_YS4", density = 1.190 * g / cm3, 3);
  mat->AddElement(C, 5);
  mat->AddElement(H, 8);
  mat->AddElement(O, 2);

  //
  // ------------ Generate & Add Material Properties Table ------------
  //

  G4double photonEnergy[] =                                    // scale in  nm
      {2.00 * eV, 2.03 * eV, 2.06 * eV, 2.09 * eV, 2.12 * eV,  // 620, 611, 602, 593, 585
       2.15 * eV, 2.18 * eV, 2.21 * eV, 2.24 * eV, 2.27 * eV,  // 576, 569, 561, 553, 546
       2.30 * eV, 2.33 * eV, 2.36 * eV, 2.39 * eV, 2.42 * eV,  // 539, 532, 525, 518, 512
       2.45 * eV, 2.48 * eV, 2.51 * eV, 2.54 * eV, 2.57 * eV,  // 506, 500, 494, 488, 482
       2.60 * eV, 2.63 * eV, 2.66 * eV, 2.69 * eV, 2.72 * eV,  // 476, 471, 466, 461, 456
       2.75 * eV, 2.78 * eV, 2.81 * eV, 2.84 * eV, 2.87 * eV,  // 450, 446, 441, 436, 432
       2.90 * eV, 2.93 * eV, 2.96 * eV, 2.99 * eV, 3.02 * eV,  // 427, 423, 419, 414, 410
       3.05 * eV, 3.08 * eV, 3.11 * eV, 3.14 * eV, 3.17 * eV,  // 406, 402, 398, 394, 391
       3.20 * eV, 3.23 * eV, 3.26 * eV, 3.29 * eV, 3.32 * eV,  // 387, 384, 380, 376, 373
       3.35 * eV, 3.38 * eV, 3.41 * eV, 3.44 * eV, 3.47 * eV}; // 370, 366, 363, 360, 357

  const G4int nEntries = sizeof(photonEnergy) / sizeof(G4double);

  G4double refractiveIndexWLSfiber[] =
      {1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
       1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60};

  assert(sizeof(refractiveIndexWLSfiber) == sizeof(photonEnergy));

  G4double absWLSfiber[] =
      {18.53 * m, 7.80 * m, 8.65 * m, 16.44 * m, 17.72 * m, 16.65 * m, 15.05 * m, 14.29 * m, 13.41 * m, 12.31 * m, // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       10.30 * m, 8.21 * m, 8.34 * m, 7.23 * m, 5.64 * m, 3.54 * m, 2.04 * m, 1.02 * m, 0.16 * m, 1. * mm,         // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,                   // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm};                  // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(absWLSfiber) == sizeof(photonEnergy));

  for (int i = 0; i < nEntries; i++)
  {
    absWLSfiber[i] = absWLSfiber[i] * scaleFactor;
  }

  G4double emissionFib[] =
      {0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.08, 0.13, 0.18, 0.22,  // 620, 611, 602, 593, 585, 576, 569, 561, 553, 546
       0.27, 0.31, 0.45, 0.62, 0.74, 0.76, 0.71, 0.69, 0.81, 0.95,  // 539, 532, 525, 518, 512, 506, 500, 494, 488, 482
       0.99, 0.72, 0.43, 0.20, 0.09, 0.01, 0.01, 0.00, 0.00, 0.00,  // 476, 471, 466, 461, 456, 450, 446, 441, 436, 432
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,  // 427, 423, 419, 414, 410, 406, 402, 398, 394, 391
       0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}; // 387, 384, 380, 376, 373, 370, 366, 363, 360, 357

  assert(sizeof(emissionFib) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable *mptWLSfiber = new G4MaterialPropertiesTable();
  mptWLSfiber->AddProperty("RINDEX", photonEnergy, refractiveIndexWLSfiber, nEntries);
  mptWLSfiber->AddProperty("ABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSABSLENGTH", photonEnergy, absWLSfiber, nEntries);
  mptWLSfiber->AddProperty("WLSCOMPONENT", photonEnergy, emissionFib, nEntries);
  mptWLSfiber->AddConstProperty("WLSTIMECONSTANT", 1.1 * ns); // !SK: time shift
                                                              //  mptWLSfiber->AddConstProperty("WLSFASTTIMECONSTANT", 10.*ns); // was 10 ns

  mat->SetMaterialPropertiesTable(mptWLSfiber);

  return mat;
}

G4Material *MyMaterials::Quartz()
{
  G4double a, z, density;

  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("Quartz", density = 2.2 * g / cm3, 2);
  mat->AddElement(Si, 1);
  mat->AddElement(O, 2);

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 2.0 * eV, 2.5 * eV, 3.0 * eV,
       3.5 * eV, 4.0 * eV, 4.5 * eV, 5.0 * eV,
       5.5 * eV, 6.0 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.53, 1.54, 1.55, 1.56,
       1.56, 1.57, 1.59, 1.60,
       1.62, 1.64, 1.65};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV};
  std::vector<G4double> Absorption =
      {138. * mm, 138. * mm, 138. * mm, 138. * mm};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

// Epoxy resin for LAPPD PCB material
// To be fixed with more accurate description from INCOM
G4Material *MyMaterials::Epoxy()
{
  G4double a, z, density;

  G4Element *H = new G4Element("Hydrogenum", "H", z = 1., a = 1.008 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("Epoxy", density = 1.2 * g / cm3, 2);
  mat->AddElement(H, 2);
  mat->AddElement(O, 2);

  return mat;
}

// average material to simulate the effect of gap between sections, given by insertion of lappd
// weight LAPPD with frame and PCB = 2.087 kg
// dimensions 21x21x2.7=1191cm3
// so density 1.75*g/cm3
G4Material *MyMaterials::LAPPD_Average()
{
  G4double a, z, density;

  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("LAPPD_Average", density = 1.75 * g / cm3, 2); // same composition as quartz, but less dense
                                                                                  // To be adjusted with full implementation of LAPPD
  mat->AddElement(Si, 1);
  mat->AddElement(O, 2);

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 2.0 * eV, 2.5 * eV, 3.0 * eV,
       3.5 * eV, 4.0 * eV, 4.5 * eV, 5.0 * eV,
       5.5 * eV, 6.0 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.53, 1.54, 1.55, 1.56,
       1.56, 1.57, 1.59, 1.60,
       1.62, 1.64, 1.65};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV};
  std::vector<G4double> Absorption =
      {138. * mm, 138. * mm, 138. * mm, 138. * mm};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::LAPPD_Window()
{
  G4double a, z, density;

  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("LAPPD_Window", density = 2.2 * g / cm3, 2); // same composition as quartz
                                                                                // To be adjusted with full implementation of LAPPD
  mat->AddElement(Si, 1);
  mat->AddElement(O, 2);

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 2.0 * eV, 2.5 * eV, 3.0 * eV,
       3.5 * eV, 4.0 * eV, 4.5 * eV, 5.0 * eV,
       5.5 * eV, 6.0 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.53, 1.54, 1.55, 1.56,
       1.56, 1.57, 1.59, 1.60,
       1.62, 1.64, 1.65};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV};
  std::vector<G4double> Absorption =
      {138. * mm, 138. * mm, 138. * mm, 138. * mm};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

// Average material for the MCP of LAPPD
// Material is Borosilicate, but density must be scaled in order to
// take into account the open area due to pores.
G4Material *MyMaterials::LAPPD_MCP()
{
  G4double a, z, density;

  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.085 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.000 * g / mole);
  G4Element *B = new G4Element("Boron", "B", z = 5., a = 10.810 * g / mole);
  G4Element *Na = new G4Element("Sodium", "Na", z = 11., a = 22.990 * g / mole);
  G4Element *Al = new G4Element("Aluminium", "Al", z = 13., a = 26.980 * g / mole);
  G4Element *K = new G4Element("Potassium", "K", z = 19., a = 39.098 * g / mole);

  G4Material *mat = new G4Material("LAPPD_MCP", density = 2.2 * g / cm3, 6); // Need to adjust density to take into account pores
  mat->AddElement(Si, 0.3618);
  mat->AddElement(O, 0.5368);
  mat->AddElement(B, 0.04469);
  mat->AddElement(Na, 0.014623);
  mat->AddElement(Al, 0.01716);
  mat->AddElement(K, 0.024869);

  return mat;
}

// Material for backplane of plastic of the LAPPD
// For now composed of Quartz + Epoxy resin
// Taken from http://www.physi.uni-heidelberg.de/~adler/TRD/TRDunterlagen/RadiatonLength/tgc2.htm
// where usual FS4 material is described
// To be updated with more detailed informations from INCOM
G4Material *MyMaterials::LAPPD_PCB()
{
  G4double density;

  G4Material *mat = new G4Material("LAPPD_PCB", density = 1.86 * g / cm3, 2);
  mat->AddMaterial(Quartz(), 0.528);
  mat->AddMaterial(Epoxy(), 0.472);

  return mat;
}

G4Material *MyMaterials::SiO2_Ce(double user_lightyield, double scaleFactor, double user_birks)
{
  G4double a, z, density;
    
  double standard_light_yield = 1800.0;
  double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("SiO2Ce", density = 2.65 * g / cm3, 2);
  mat->AddElement(Si, 1);
  mat->AddElement(O, 2);

  std::vector<G4double> PhotonEnergy_RI =
      {0.1000 * eV, 1.0000 * eV, 1.0121 * eV, 1.0332 * eV,
       1.0552 * eV, 1.0781 * eV, 1.1021 * eV, 1.1271 * eV,
       1.1533 * eV, 1.1808 * eV, 1.2096 * eV, 1.2398 * eV,
       1.2716 * eV, 1.3051 * eV, 1.3404 * eV, 1.3776 * eV,
       1.4170 * eV, 1.4586 * eV, 1.5028 * eV, 1.5498 * eV,
       1.5998 * eV, 1.6531 * eV, 1.7101 * eV, 1.7712 * eV,
       1.8368 * eV, 1.9074 * eV, 1.9837 * eV, 2.0664 * eV,
       2.1562 * eV, 2.2543 * eV, 2.3616 * eV, 2.4797 * eV,
       2.6102 * eV, 2.7552 * eV, 2.9173 * eV, 3.0996 * eV,
       3.3062 * eV, 3.5424 * eV, 3.8149 * eV, 4.1328 * eV,
       4.5085 * eV, 4.9594 * eV};

  std::vector<G4double> RefractiveIndex =
      {1.4476, 1.4476, 1.4478, 1.4481,
       1.4483, 1.4486, 1.4489, 1.4492,
       1.4495, 1.4498, 1.4501, 1.4504,
       1.4507, 1.4511, 1.4514, 1.4518,
       1.4521, 1.4525, 1.4529, 1.4533,
       1.4538, 1.4542, 1.4547, 1.4553,
       1.4559, 1.4565, 1.4572, 1.4580,
       1.4589, 1.4599, 1.4610, 1.4623,
       1.4638, 1.4656, 1.4676, 1.4701,
       1.4731, 1.4769, 1.4816, 1.4878,
       1.4960, 1.5074};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV};
  std::vector<G4double> Absorption =
      {138. * mm, 138. * mm, 138. * mm, 138. * mm};

  std::vector<G4double> PhotonEnergy_FAST = {1.8 * eV, 1.90 * eV, 2.7 * eV, 2.88 * eV, 4.08 * eV};
  std::vector<G4double> FastComponent = {0.00, 1.00, 2.0, 1.0, 0.00};

  for (auto& value : Absorption)
  {
      value *= scaleFactor;
  }
  double birks = (user_birks < 0) ? 0 : user_birks; 
  
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 8.5);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 55. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

  mat->SetMaterialPropertiesTable(mt);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks*mm/MeV);
  return mat;
}

G4Material *MyMaterials::YAG_Ce(double user_lightyield, double scaleFactor, double user_birks)
{
  double standard_light_yield = 33200.0;
  double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }

  G4double a, z, density;

  G4Element *Y = new G4Element("Silicon", "Y", z = 39., a = 88.01 * g / mole);
  G4Element *Al = new G4Element("Aluminium", "Al", z = 13., a = 26.98 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("YAG_Ce", density = 4.6 * g / cm3, 3);
  mat->AddElement(Y, 3);
  mat->AddElement(Al, 5);
  mat->AddElement(O, 12);

  // fixed index of refraction
  std::vector<G4double> PhotonEnergy_RI = {0.1 * eV, 1.0 * eV, 2.26 * eV, 2.55 * eV, 2.84 * eV, 3.06 * eV,
                                           3.4 * eV, 4.1 * eV};
  std::vector<G4double> RefractiveIndex = {1.84, 1.84, 1.84, 1.84, 1.84, 1.84, 1.84,
                                           1.84};

  // G4double Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm };

  // intrinsic absorption spectrum

  std::vector<G4double> PhotonEnergy_ABS =
      {4.42857 * eV, 4.35088 * eV, 4.27586 * eV, 4.20339 * eV, 4.13333 * eV, 4.06557 * eV, 4 * eV, 3.93651 * eV,
       3.875 * eV,
       3.81538 * eV, 3.75758 * eV, 3.70149 * eV, 3.64706 * eV, 3.5942 * eV, 3.54286 * eV, 3.49296 * eV, 3.44444 * eV,
       3.39726 * eV, 3.35135 * eV, 3.30667 * eV, 3.26316 * eV, 3.22078 * eV, 3.17949 * eV, 3.13924 * eV, 3.1 * eV,
       3.06173 * eV,
       3.02439 * eV, 2.98795 * eV, 2.95238 * eV, 2.91765 * eV, 2.88372 * eV, 2.85057 * eV, 2.81818 * eV, 2.78652 * eV,
       2.75556 * eV, 2.72527 * eV, 2.69565 * eV, 2.66667 * eV, 2.6383 * eV, 2.61053 * eV, 2.58333 * eV, 2.5567 * eV,
       2.53061 * eV, 2.50505 * eV, 2.48 * eV, 2.45545 * eV, 2.43137 * eV, 2.40777 * eV, 2.38462 * eV, 2.3619 * eV,
       2.33962 * eV, 2.31776 * eV, 2.2963 * eV, 2.27523 * eV, 2.25455 * eV, 2.23423 * eV, 2.21429 * eV, 2.19469 * eV,
       2.17544 * eV, 2.15652 * eV, 2.13793 * eV, 2.11966 * eV, 2.10169 * eV, 2.08403 * eV, 2.06667 * eV, 2.04959 * eV,
       2.03279 * eV, 2.01626 * eV, 2 * eV, 1.984 * eV, 1.96825 * eV, 1.95276 * eV, 1.9375 * eV, 1.92248 * eV, 1.90769 * eV,
       1.89313 * eV, 1.87879 * eV, 1.86466 * eV, 1.85075 * eV, 1.83704 * eV, 1.82353 * eV, 1.81022 * eV, 1.7971 * eV,
       1.78417 * eV};

  std::vector<G4double> Absorption =
      {12.7389 * mm, 7.96854 * mm, 9.79472 * mm, 11.3642 * mm, 13.9544 * mm, 14.078 * mm, 9.48293 * mm, 4.60862 * mm,
       0.45205 * mm, 0.14906 * mm, 0.09215 * mm, 0.05898 * mm, 0.09349 * mm, 0.09448 * mm, 4.00614 * mm, 14.055 * mm,
       59.4712 * mm, 177.765 * mm, 322.779 * mm, 407.883 * mm, 423.384 * mm, 250.626 * mm, 107.986 * mm, 40.2593 * mm,
       16.1867 * mm, 7.08721 * mm, 3.3827 * mm, 1.85802 * mm, 0.42111 * mm, 0.348 * mm, 0.36044 * mm, 0.37582 * mm,
       0.39199 * mm, 0.33268 * mm, 0.27998 * mm, 0.33348 * mm, 0.21815 * mm, 0.28273 * mm, 0.37124 * mm, 0.4064 * mm,
       1.09597 * mm, 1.45447 * mm, 2.03141 * mm, 3.62354 * mm, 6.92578 * mm, 13.9067 * mm, 29.0131 * mm, 60.2374 * mm,
       129.476 * mm, 226.564 * mm, 553.51 * mm, 516.632 * mm, 600. * mm, 700. * mm, 800. * mm, 900. * mm,
       1000. * mm, 1000. * mm, 1000. * mm, 1000.2 * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm,
       1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm,
       1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm,
       1000. * mm, 1000. * mm, 1000. * mm, 1000. * mm};

  // scaleFactor = 1.0;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }
  // emission spectrum

  std::vector<G4double> PhotonEnergy_FAST =
      {2.72827 * eV, 2.71335 * eV, 2.69859 * eV, 2.68398 * eV, 2.66954 * eV, 2.65525 * eV, 2.64111 * eV, 2.62712 * eV,
       2.61328 * eV, 2.59958 * eV,
       2.58603 * eV, 2.57261 * eV, 2.55934 * eV, 2.5462 * eV, 2.5332 * eV, 2.52033 * eV, 2.50758 * eV, 2.49497 * eV,
       2.48248 * eV, 2.47012 * eV,
       2.45788 * eV, 2.44576 * eV, 2.43376 * eV, 2.42188 * eV, 2.41011 * eV, 2.39845 * eV, 2.38691 * eV, 2.37548 * eV,
       2.36416 * eV, 2.35294 * eV,
       2.34183 * eV, 2.33083 * eV, 2.31993 * eV, 2.30912 * eV, 2.29842 * eV, 2.28782 * eV, 2.27732 * eV, 2.26691 * eV,
       2.2566 * eV, 2.24638 * eV,
       2.23625 * eV, 2.22621 * eV, 2.21626 * eV, 2.20641 * eV, 2.19663 * eV, 2.18695 * eV, 2.17735 * eV, 2.16783 * eV,
       2.1584 * eV, 2.14905 * eV,
       2.13978 * eV, 2.13058 * eV, 2.12147 * eV, 2.11244 * eV, 2.10348 * eV, 2.09459 * eV, 2.08579 * eV, 2.07705 * eV,
       2.06839 * eV, 2.0598 * eV,
       2.05128 * eV, 2.04283 * eV, 2.03445 * eV, 2.02614 * eV, 2.0179 * eV, 2.00972 * eV, 2.00161 * eV, 1.99357 * eV,
       1.98559 * eV, 1.97767 * eV,
       1.96982 * eV, 1.96203 * eV, 1.95429 * eV, 1.94662 * eV, 1.93901 * eV, 1.93146 * eV, 1.92397 * eV, 1.91654 * eV,
       1.90916 * eV, 1.90184 * eV,
       1.89458 * eV, 1.88737 * eV, 1.88021 * eV, 1.87311 * eV, 1.86606 * eV, 1.85907 * eV, 1.85213 * eV, 1.84524 * eV,
       1.8384 * eV, 1.83161 * eV,
       1.82487 * eV, 1.81818 * eV, 1.81154 * eV, 1.80495 * eV, 1.7984 * eV, 1.79191 * eV, 1.78546 * eV, 1.77905 * eV,
       1.77269 * eV, 1.76638 * eV,
       1.76011 * eV, 1.75389 * eV, 1.74771 * eV, 1.74157 * eV, 1.73548 * eV, 1.72943 * eV, 1.72342 * eV, 1.71745 * eV,
       1.71153 * eV, 1.70564 * eV,
       1.69979 * eV, 1.69399 * eV, 1.68822 * eV, 1.6825 * eV, 1.67681 * eV, 1.67116 * eV, 1.66555 * eV, 1.65997 * eV,
       1.65444 * eV, 1.64894 * eV,
       1.64347 * eV, 1.63804 * eV, 1.63265 * eV, 1.6273 * eV, 1.62198 * eV, 1.61669 * eV, 1.61144 * eV, 1.60622 * eV,
       1.60103 * eV, 1.59588 * eV,
       1.59076 * eV, 1.58568 * eV, 1.58062 * eV, 1.5756 * eV, 1.57061 * eV, 1.56566 * eV, 1.56073 * eV};

  std::vector<G4double> FastComponent =
      {0.017312, 0.0096453, 0.00790803, 0.00810917, 0.0088267, 0.0100443, 0.0119759, 0.013618, 0.0158952,
       0.0205216, 0.0276587,
       0.0355978, 0.047533, 0.063484, 0.0846373, 0.110553, 0.142739, 0.179262, 0.220629, 0.265465,
       0.316428, 0.373613, 0.435236,
       0.503049, 0.573143, 0.645777, 0.716553, 0.781489, 0.830571, 0.868259, 0.892522, 0.905547, 0.90921,
       0.904013, 0.894359,
       0.879165, 0.863961, 0.848755, 0.832279, 0.814811, 0.796789, 0.781315, 0.763563, 0.741355,
       0.724224, 0.705468, 0.687985,
       0.668306, 0.65034, 0.62812, 0.608418, 0.588743, 0.569351, 0.545681, 0.521421, 0.500633, 0.47682,
       0.455015, 0.432658,
       0.408202, 0.385464, 0.363256, 0.341688, 0.321938, 0.302229, 0.283179, 0.264294, 0.244777,
       0.227309, 0.208308, 0.193561,
       0.178659, 0.163398, 0.14938, 0.137934, 0.126634, 0.116962, 0.106936, 0.0974455, 0.0876783,
       0.0803322, 0.073087, 0.0664133,
       0.0601629, 0.0542353, 0.0497304, 0.0440716, 0.0397871, 0.035986, 0.0335943, 0.0305447, 0.027748,
       0.0251957, 0.0232941,
       0.0210163, 0.0181465, 0.0167443, 0.014946, 0.0138611, 0.0129008, 0.0123556, 0.0118624, 0.011176,
       0.0102985, 0.00944158,
       0.00946978, 0.00862405, 0.00771896, 0.00694318, 0.00643815, 0.00590943, 0.00537023, 0.00446022,
       0.00436113, 0.0043437,
       0.00408437, 0.00385623, 0.0032281, 0.00318978, 0.00319752, 0.00311753, 0.00256044, 0.00262745,
       0.00253195, 0.00259158,
       0.00233708, 0.00213198, 0.00234155, 0.0024483, 0.00209324, 0.0018311, 0.00175891, 0.00183815,
       0.00192849, 0.00163606,
       0.00136759, 0.00170809};

  // reverse std::vector<G4double> PhotonEnergy_FAST 
  std::reverse(PhotonEnergy_FAST.begin(), PhotonEnergy_FAST.end());
  std::reverse(FastComponent.begin(), FastComponent.end());


  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 4.8);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 90. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

  mat->SetMaterialPropertiesTable(mt);
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}

G4Material *MyMaterials::Brass()
{
  G4double density, a, z;

  G4Element *Cu = new G4Element("Copper", "Cu", z = 29., a = 63.546 * g / mole);
  G4Element *Zn = new G4Element("Zinc", "Zn", z = 30., a = 65.409 * g / mole);

  G4Material *mat = new G4Material("Brass", density = 8.73 * g / cm3, 2);
  mat->AddElement(Cu, 0.75);
  mat->AddElement(Zn, 0.25);

  return mat;
}

G4Material *MyMaterials::StainlessSteel()
{
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  return mat;
}

G4Material *MyMaterials::Copper()
{
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *mat = nist->FindOrBuildMaterial("G4_Cu");
  return mat;
}

G4Material *MyMaterials::Aluminium()
{
  G4NistManager *man = G4NistManager::Instance();
  G4Element *Al = man->FindOrBuildElement("Al");

  G4Material *mat = new G4Material("Aluminium", 2.700 * g / cm3, 1);
  mat->AddElement(Al, 100. * perCent);

  return mat;
}

G4Material *MyMaterials::Iron()
{
  G4NistManager *man = G4NistManager::Instance();
  G4Element *Fe = man->FindOrBuildElement("Fe");

  G4Material *mat = new G4Material("Iron", 7.874 * g / cm3, 1);
  mat->AddElement(Fe, 100. * perCent);

  return mat;
}

G4Material *MyMaterials::Lead()
{
  G4double density;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *Pb = man->FindOrBuildElement("Pb");

  G4Material *mat = new G4Material("Lead", density = 11.35 * g / cm3, 1);
  mat->AddElement(Pb, 100. * perCent);

  return mat;
}

// Pb 84% - Sb 12% - 4% Sn - density 10 g/cm3
G4Material *MyMaterials::GarthTypographicAlloy()
{
  G4double density;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *Pb = man->FindOrBuildElement("Pb");
  G4Element *Sb = man->FindOrBuildElement("Sb");
  G4Element *Sn = man->FindOrBuildElement("Sn");
  G4Material *mat = new G4Material("GarthTypographicAlloy", density = 10.00 * g / cm3, 3);
  mat->AddElement(Pb, 84. * perCent);
  mat->AddElement(Sb, 12. * perCent);
  mat->AddElement(Sn, 4. * perCent);
  return mat;
}

G4Material *MyMaterials::Cu()
{
  G4double density;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *Cu = man->FindOrBuildElement("Cu");

  G4Material *mat = new G4Material("Cu", density = 8.96 * g / cm3, 1);
  mat->AddElement(Cu, 100. * perCent);

  return mat;
}

G4Material *MyMaterials::CuAir()
{
  G4double density;

  G4int nelements;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *Cu = man->FindOrBuildElement("Cu");
  G4Element *O = man->FindOrBuildElement("O");
  G4Element *N = man->FindOrBuildElement("N");
  // G4double rho_Cu = 8.96;
  // G4double rho_N = 0.125;
  // G4double rho_O = 0.147;
  // // G4double rhoCA = rho_Cu*0.1 + rho_O*0.25 + rho_N*0.65;
  G4Material *mat = new G4Material("CuAir", density = 1.5 * g / cm3, nelements = 3);

  mat->AddElement(Cu, 10. * perCent);
  mat->AddElement(N, 65. * perCent);
  mat->AddElement(O, 25. * perCent);

  return mat;
}

G4Material *MyMaterials::Tungsten()
{
  G4double density;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *W = man->FindOrBuildElement("W");
  G4Element *Ni = man->FindOrBuildElement("Ni");
  G4Element *Cu = man->FindOrBuildElement("Cu");

  G4Material *mat = new G4Material("Tungsten", density = 17. * g / cm3, 3);
  mat->AddElement(W, 90. * perCent);
  mat->AddElement(Ni, 5. * perCent);
  mat->AddElement(Cu, 5. * perCent);

  return mat;
}

G4Material *MyMaterials::TungstenLight()
{
  G4double density;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *W = man->FindOrBuildElement("W");
  G4Material *mat = new G4Material("PureTungsten", density = 15.9 * g / cm3, 1);
  mat->AddElement(W, 1);
  return mat;
}

G4Material *MyMaterials::PVC()
{
  G4double density;
  G4int nelements;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *C = man->FindOrBuildElement("C");
  G4Element *H = man->FindOrBuildElement("H");
  G4Element *Cl = man->FindOrBuildElement("Cl");

  G4Material *mat = new G4Material("PVC", density = 1.4 * g / cm3, nelements = 3);
  mat->AddElement(C, 2);
  mat->AddElement(H, 3);
  mat->AddElement(Cl, 1);

  // 随便设置的
  std::vector<G4double> PhotonEnergy_RI = {2 * eV, 6 * eV};
  std::vector<G4double> RefractiveIndex = {1.35, 1.38};

  std::vector<G4double> ABS_Energy = {1.0 * eV,  6 * eV};
  std::vector<G4double> ABS_LENGTH = {0.1 * mm, 0.1 * mm}; 

  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", ABS_Energy, ABS_LENGTH);
  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::CopperTungstenAlloy(const G4double &WFrac)
{
  G4NistManager *man = G4NistManager::Instance();
  G4Element *W = man->FindOrBuildElement("W");
  G4Element *Cu = man->FindOrBuildElement("Cu");

  // G4double rho_Cu = 8.96;
  // G4double rho_W = 19.25;
  // G4double rho = (1.-WFrac)*rho_Cu + WFrac*rho_W;
  G4double rho = 15.0;
  G4Material *mat = new G4Material("CopperTungstenAlloy", rho * g / cm3, 2);
  mat->AddElement(Cu, 1. - WFrac);
  mat->AddElement(W, WFrac);

  return mat;
}

G4Material *MyMaterials::OpticalGrease()
{
  G4double a, z, density;
  G4Element *H = new G4Element("Hydrogen", "H", z = 1., a = 1.01 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);

  G4Material *mat = new G4Material("Grease", density = 1.0 * g / cm3, 3);
  mat->AddElement(C, 1);
  mat->AddElement(H, 1);
  mat->AddElement(O, 1);

  const G4int nEntries = 35;
  G4double PhotonEnergy[nEntries] =
      {0.0001 * eV, 1.000 * eV, 2.034 * eV, 2.068 * eV,
       2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
       2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV,
       2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV,
       2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
       2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV,
       3.181 * eV, 3.265 * eV, 3.353 * eV, 3.446 * eV,
       3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
       4.002 * eV, 4.136 * eV, 6.260 * eV};
  G4double RefractiveIndex[nEntries] =
      {1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50};

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  // myMPT->AddProperty("ABSLENGTH", PhotonEnergy, Absorption,      nEntries);

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::DSB_Ce(double user_lightyield, double scaleFactor, double user_birks) // Nanostructured glass ceramics scintillator DSB:Ce
{
  G4double a, z, density;
  G4Element *DSB_glass = new G4Element("DSB_glass", "DSB", z = 51, a = 124.00 * g / mole);

  G4Material *mat = new G4Material("DSB", density = 4 * g / cm3, 1);
  mat->AddElement(DSB_glass, 1);

  double standard_light_yield = 1800.0;
  double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  // large band between 470 (2.64 eV) and 630 nm (1.97 eV) (mean 535 nm, 2.32)

  std::vector<G4double> PhotonEnergy_FAST = {1.8 * eV, 1.90 * eV, 2.7 * eV, 2.88 * eV, 4.08 * eV};
  std::vector<G4double> FastComponent = {0.00, 1.00, 2.0, 1.0, 0.00};

  std::vector<G4double> PhotonEnergy_RI =
      {0.1000 * eV, 1.0000 * eV, 1.0121 * eV, 1.0332 * eV,
       1.0552 * eV, 1.0781 * eV, 1.1021 * eV, 1.1271 * eV,
       1.1533 * eV, 1.1808 * eV, 1.2096 * eV, 1.2398 * eV,
       1.2716 * eV, 1.3051 * eV, 1.3404 * eV, 1.3776 * eV,
       1.4170 * eV, 1.4586 * eV, 1.5028 * eV, 1.5498 * eV,
       1.5998 * eV, 1.6531 * eV, 1.7101 * eV, 1.7712 * eV,
       1.8368 * eV, 1.9074 * eV, 1.9837 * eV, 2.0664 * eV,
       2.1562 * eV, 2.2543 * eV, 2.3616 * eV, 2.4797 * eV,
       2.6102 * eV, 2.7552 * eV, 2.9173 * eV, 3.0996 * eV,
       3.3062 * eV, 3.5424 * eV, 3.8149 * eV, 4.1328 * eV,
       4.5085 * eV, 4.9594 * eV};

  std::vector<G4double> RefractiveIndex =
      {1.4476, 1.4476, 1.4478, 1.4481,
       1.4483, 1.4486, 1.4489, 1.4492,
       1.4495, 1.4498, 1.4501, 1.4504,
       1.4507, 1.4511, 1.4514, 1.4518,
       1.4521, 1.4525, 1.4529, 1.4533,
       1.4538, 1.4542, 1.4547, 1.4553,
       1.4559, 1.4565, 1.4572, 1.4580,
       1.4589, 1.4599, 1.4610, 1.4623,
       1.4638, 1.4656, 1.4676, 1.4701,
       1.4731, 1.4769, 1.4816, 1.4878,
       1.4960, 1.5074};

  std::vector<G4double> ABS_Energy = {1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV};
  std::vector<G4double> ABS_LENGTH = {500. * mm, 500. * mm, 500. * mm, 500. * mm}; // 138 original

  for (auto& value : ABS_LENGTH)
  {
      value *= scaleFactor;
  }
  double birks = (user_birks < 0) ? 0 : user_birks; 

  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", ABS_Energy, ABS_LENGTH);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 8.5);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 50. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

  mat->SetMaterialPropertiesTable(mt);

    // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks*mm/MeV);
  return mat;
}

G4Material *MyMaterials::LuAG_Ce(double user_lightyield, double scaleFactor, double user_birks) // Lutetium Aluminum Garnet - Ce-doped
{
  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Lu = new G4Element("Lutetium", "Lu", z = 71., a = 174.97 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("LuAG_Ce", density = 6.7 * g / cm3, 3);
  mat->AddElement(Lu, 3);
  mat->AddElement(Al, 12);
  mat->AddElement(O, 5);

  double standard_light_yield = 15000.0;
  double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  std::vector<G4double> PhotonEnergy_FAST =
      {1.82487 * eV, 1.82622 * eV, 1.82756 * eV, 1.82891 * eV, 1.83026 * eV, 1.83161 * eV, 1.83296 * eV, 1.83432 * eV, 1.83568 * eV, 1.83704 * eV,
       1.8384 * eV, 1.83976 * eV, 1.84113 * eV, 1.8425 * eV, 1.84387 * eV, 1.84524 * eV, 1.84661 * eV, 1.84799 * eV, 1.84937 * eV, 1.85075 * eV,
       1.85213 * eV, 1.85351 * eV, 1.8549 * eV, 1.85629 * eV, 1.85768 * eV, 1.85907 * eV, 1.86047 * eV, 1.86186 * eV, 1.86326 * eV, 1.86466 * eV,
       1.86606 * eV, 1.86747 * eV, 1.86888 * eV, 1.87029 * eV, 1.8717 * eV, 1.87311 * eV, 1.87453 * eV, 1.87595 * eV, 1.87737 * eV, 1.87879 * eV,
       1.88021 * eV, 1.88164 * eV, 1.88307 * eV, 1.8845 * eV, 1.88593 * eV, 1.88737 * eV, 1.8888 * eV, 1.89024 * eV, 1.89169 * eV, 1.89313 * eV,
       1.89458 * eV, 1.89602 * eV, 1.89748 * eV, 1.89893 * eV, 1.90038 * eV, 1.90184 * eV, 1.9033 * eV, 1.90476 * eV, 1.90623 * eV, 1.90769 * eV,
       1.90916 * eV, 1.91063 * eV, 1.9121 * eV, 1.91358 * eV, 1.91506 * eV, 1.91654 * eV, 1.91802 * eV, 1.9195 * eV, 1.92099 * eV, 1.92248 * eV,
       1.92397 * eV, 1.92547 * eV, 1.92696 * eV, 1.92846 * eV, 1.92996 * eV, 1.93146 * eV, 1.93297 * eV, 1.93448 * eV, 1.93599 * eV, 1.9375 * eV,
       1.93901 * eV, 1.94053 * eV, 1.94205 * eV, 1.94357 * eV, 1.9451 * eV, 1.94662 * eV, 1.94815 * eV, 1.94969 * eV, 1.95122 * eV, 1.95276 * eV,
       1.95429 * eV, 1.95584 * eV, 1.95738 * eV, 1.95893 * eV, 1.96047 * eV, 1.96203 * eV, 1.96358 * eV, 1.96513 * eV, 1.96669 * eV, 1.96825 * eV,
       1.96982 * eV, 1.97138 * eV, 1.97295 * eV, 1.97452 * eV, 1.9761 * eV, 1.97767 * eV, 1.97925 * eV, 1.98083 * eV, 1.98241 * eV, 1.984 * eV,
       1.98559 * eV, 1.98718 * eV, 1.98877 * eV, 1.99037 * eV, 1.99197 * eV, 1.99357 * eV, 1.99517 * eV, 1.99678 * eV, 1.99839 * eV, 2 * eV,
       2.00161 * eV, 2.00323 * eV, 2.00485 * eV, 2.00647 * eV, 2.0081 * eV, 2.00972 * eV, 2.01135 * eV, 2.01299 * eV, 2.01462 * eV, 2.01626 * eV,
       2.0179 * eV, 2.01954 * eV, 2.02119 * eV, 2.02284 * eV, 2.02449 * eV, 2.02614 * eV, 2.0278 * eV, 2.02946 * eV, 2.03112 * eV, 2.03279 * eV,
       2.03445 * eV, 2.03612 * eV, 2.0378 * eV, 2.03947 * eV, 2.04115 * eV, 2.04283 * eV, 2.04452 * eV, 2.0462 * eV, 2.04789 * eV, 2.04959 * eV,
       2.05128 * eV, 2.05298 * eV, 2.05468 * eV, 2.05638 * eV, 2.05809 * eV, 2.0598 * eV, 2.06151 * eV, 2.06323 * eV, 2.06495 * eV, 2.06667 * eV,
       2.06839 * eV, 2.07012 * eV, 2.07185 * eV, 2.07358 * eV, 2.07531 * eV, 2.07705 * eV, 2.07879 * eV, 2.08054 * eV, 2.08228 * eV, 2.08403 * eV,
       2.08579 * eV, 2.08754 * eV, 2.0893 * eV, 2.09106 * eV, 2.09283 * eV, 2.09459 * eV, 2.09637 * eV, 2.09814 * eV, 2.09992 * eV, 2.10169 * eV,
       2.10348 * eV, 2.10526 * eV, 2.10705 * eV, 2.10884 * eV, 2.11064 * eV, 2.11244 * eV, 2.11424 * eV, 2.11604 * eV, 2.11785 * eV, 2.11966 * eV,
       2.12147 * eV, 2.12329 * eV, 2.12511 * eV, 2.12693 * eV, 2.12876 * eV, 2.13058 * eV, 2.13242 * eV, 2.13425 * eV, 2.13609 * eV, 2.13793 * eV,
       2.13978 * eV, 2.14162 * eV, 2.14347 * eV, 2.14533 * eV, 2.14719 * eV, 2.14905 * eV, 2.15091 * eV, 2.15278 * eV, 2.15465 * eV, 2.15652 * eV,
       2.1584 * eV, 2.16028 * eV, 2.16216 * eV, 2.16405 * eV, 2.16594 * eV, 2.16783 * eV, 2.16973 * eV, 2.17163 * eV, 2.17353 * eV, 2.17544 * eV,
       2.17735 * eV, 2.17926 * eV, 2.18118 * eV, 2.1831 * eV, 2.18502 * eV, 2.18695 * eV, 2.18888 * eV, 2.19081 * eV, 2.19275 * eV, 2.19469 * eV,
       2.19663 * eV, 2.19858 * eV, 2.20053 * eV, 2.20249 * eV, 2.20444 * eV, 2.20641 * eV, 2.20837 * eV, 2.21034 * eV, 2.21231 * eV, 2.21429 * eV,
       2.21626 * eV, 2.21825 * eV, 2.22023 * eV, 2.22222 * eV, 2.22422 * eV, 2.22621 * eV, 2.22821 * eV, 2.23022 * eV, 2.23222 * eV, 2.23423 * eV,
       2.23625 * eV, 2.23827 * eV, 2.24029 * eV, 2.24231 * eV, 2.24434 * eV, 2.24638 * eV, 2.24841 * eV, 2.25045 * eV, 2.2525 * eV, 2.25455 * eV,
       2.2566 * eV, 2.25865 * eV, 2.26071 * eV, 2.26277 * eV, 2.26484 * eV, 2.26691 * eV, 2.26898 * eV, 2.27106 * eV, 2.27314 * eV, 2.27523 * eV,
       2.27732 * eV, 2.27941 * eV, 2.28151 * eV, 2.28361 * eV, 2.28571 * eV, 2.28782 * eV, 2.28994 * eV, 2.29205 * eV, 2.29417 * eV, 2.2963 * eV,
       2.29842 * eV, 2.30056 * eV, 2.30269 * eV, 2.30483 * eV, 2.30698 * eV, 2.30912 * eV, 2.31128 * eV, 2.31343 * eV, 2.31559 * eV, 2.31776 * eV,
       2.31993 * eV, 2.3221 * eV, 2.32427 * eV, 2.32645 * eV, 2.32864 * eV, 2.33083 * eV, 2.33302 * eV, 2.33522 * eV, 2.33742 * eV, 2.33962 * eV,
       2.34183 * eV, 2.34405 * eV, 2.34626 * eV, 2.34848 * eV, 2.35071 * eV, 2.35294 * eV, 2.35518 * eV, 2.35741 * eV, 2.35966 * eV, 2.3619 * eV,
       2.36416 * eV, 2.36641 * eV, 2.36867 * eV, 2.37094 * eV, 2.37321 * eV, 2.37548 * eV, 2.37776 * eV, 2.38004 * eV, 2.38232 * eV, 2.38462 * eV,
       2.38691 * eV, 2.38921 * eV, 2.39151 * eV, 2.39382 * eV, 2.39614 * eV, 2.39845 * eV, 2.40077 * eV, 2.4031 * eV, 2.40543 * eV, 2.40777 * eV,
       2.41011 * eV, 2.41245 * eV, 2.4148 * eV, 2.41715 * eV, 2.41951 * eV, 2.42188 * eV, 2.42424 * eV, 2.42661 * eV, 2.42899 * eV, 2.43137 * eV,
       2.43376 * eV, 2.43615 * eV, 2.43854 * eV, 2.44094 * eV, 2.44335 * eV, 2.44576 * eV, 2.44817 * eV, 2.45059 * eV, 2.45302 * eV, 2.45545 * eV,
       2.45788 * eV, 2.46032 * eV, 2.46276 * eV, 2.46521 * eV, 2.46766 * eV, 2.47012 * eV, 2.47258 * eV, 2.47505 * eV, 2.47752 * eV, 2.48 * eV,
       2.48248 * eV, 2.48497 * eV, 2.48746 * eV, 2.48996 * eV, 2.49246 * eV, 2.49497 * eV, 2.49748 * eV, 2.5 * eV, 2.50252 * eV, 2.50505 * eV,
       2.50758 * eV, 2.51012 * eV, 2.51266 * eV, 2.51521 * eV, 2.51777 * eV, 2.52033 * eV, 2.52289 * eV, 2.52546 * eV, 2.52803 * eV, 2.53061 * eV,
       2.5332 * eV, 2.53579 * eV, 2.53838 * eV, 2.54098 * eV, 2.54359 * eV, 2.5462 * eV, 2.54882 * eV, 2.55144 * eV, 2.55407 * eV, 2.5567 * eV,
       2.55934 * eV, 2.56198 * eV, 2.56463 * eV, 2.56729 * eV, 2.56995 * eV, 2.57261 * eV, 2.57529 * eV, 2.57796 * eV, 2.58065 * eV, 2.58333 * eV,
       2.58603 * eV, 2.58873 * eV, 2.59143 * eV, 2.59414 * eV, 2.59686 * eV, 2.59958 * eV, 2.60231 * eV, 2.60504 * eV, 2.60778 * eV, 2.61053 * eV,
       2.61328 * eV, 2.61603 * eV, 2.6188 * eV, 2.62156 * eV, 2.62434 * eV, 2.62712 * eV, 2.6299 * eV, 2.6327 * eV, 2.63549 * eV, 2.6383 * eV,
       2.64111 * eV, 2.64392 * eV, 2.64674 * eV, 2.64957 * eV, 2.65241 * eV, 2.65525 * eV, 2.65809 * eV, 2.66094 * eV, 2.6638 * eV, 2.66667 * eV,
       2.66954 * eV, 2.67241 * eV, 2.6753 * eV, 2.67819 * eV, 2.68108 * eV, 2.68398 * eV, 2.68689 * eV, 2.6898 * eV, 2.69273 * eV, 2.69565 * eV,
       2.69859 * eV, 2.70153 * eV, 2.70447 * eV, 2.70742 * eV, 2.71038 * eV, 2.71335 * eV, 2.71632 * eV, 2.7193 * eV, 2.72228 * eV, 2.72527 * eV,
       2.72827 * eV, 2.73128 * eV, 2.73429 * eV, 2.73731 * eV, 2.74033 * eV, 2.74336 * eV, 2.7464 * eV, 2.74945 * eV};
  std::vector<G4double> FastComponent =
      {5.81332e-05, 6.44431e-05, 5.14981e-05, 5.53578e-05, 7.63256e-05, 7.53282e-05, 7.58269e-05, 8.97693e-05, 7.76917e-05, 7.38103e-05,
       7.78435e-05, 7.09481e-05, 7.49162e-05, 8.77528e-05, 8.86852e-05, 9.01596e-05, 7.3355e-05, 8.61916e-05, 8.31125e-05, 9.63177e-05,
       9.64045e-05, 8.96609e-05, 0.000118934, 0.000122446, 0.000112017, 8.10092e-05, 9.10487e-05, 9.54287e-05, 0.000102975, 0.000102996,
       0.00010833, 9.44529e-05, 9.82259e-05, 0.000117372, 0.000121601, 0.00011206, 0.000123183, 0.000126371, 0.000114987, 0.000121687,
       0.00011065, 0.000131879, 0.000124766, 0.000119606, 0.000146146, 0.000145279, 0.000141441, 0.000148553, 0.000156012, 0.000149746,
       0.000163168, 0.000161043, 0.000174898, 0.000182661, 0.000175918, 0.000175939, 0.000171169, 0.000159807, 0.0001726, 0.000178866,
       0.000175028, 0.000190836, 0.000208768, 0.000179539, 0.000198165, 0.000197644, 0.000199509, 0.000202545, 0.000218005, 0.000208031,
       0.000212584, 0.000219848, 0.000234961, 0.000249945, 0.000232078, 0.000224814, 0.000229476, 0.000248232, 0.000290948, 0.000269568,
       0.000289062, 0.000288346, 0.000276572, 0.000287999, 0.000306235, 0.000306452, 0.000293724, 0.000325186, 0.000335356, 0.000332277,
       0.000323885, 0.000335464, 0.000335724, 0.000372413, 0.000366406, 0.000352919, 0.000341297, 0.000400384, 0.00038796, 0.000373518,
       0.000396785, 0.000419986, 0.00042712, 0.000413654, 0.000429158, 0.000443621, 0.000482629, 0.000489546, 0.00047736, 0.000457151,
       0.000534973, 0.000505028, 0.000518277, 0.000507934, 0.000520879, 0.000552884, 0.00054859, 0.00057396, 0.000561015, 0.000557329,
       0.000603645, 0.000608111, 0.000628646, 0.000624894, 0.000634196, 0.000647055, 0.000670148, 0.000680122, 0.000679211, 0.000696731,
       0.000703887, 0.000728888, 0.000708722, 0.000749509, 0.000780863, 0.000772819, 0.000771908, 0.000782294, 0.000797256, 0.000792767,
       0.000837197, 0.00086081, 0.000856668, 0.000894267, 0.000905629, 0.000906323, 0.00097068, 0.00095175, 0.000955696, 0.000969986,
       0.000980069, 0.00103508, 0.00108445, 0.00109566, 0.00108985, 0.00108554, 0.00116115, 0.00116232, 0.00123272, 0.00118337,
       0.0012059, 0.00121104, 0.00122034, 0.00134806, 0.00132759, 0.00131655, 0.00134255, 0.0014004, 0.00139422, 0.00140613,
       0.00148002, 0.00146782, 0.00151511, 0.00152601, 0.00156979, 0.00156765, 0.00161945, 0.00161797, 0.00164276, 0.00167585,
       0.00163298, 0.00169692, 0.00173064, 0.00185434, 0.0018602, 0.00183116, 0.00184591, 0.00187262, 0.00185005, 0.00187863,
       0.00193908, 0.00196593, 0.00204381, 0.00207335, 0.00214098, 0.00216439, 0.00214946, 0.00215717, 0.00218378, 0.00220102,
       0.00226733, 0.00225952, 0.00232741, 0.0023407, 0.00237913, 0.0023986, 0.00246035, 0.00246658, 0.00256504, 0.00255051,
       0.00260585, 0.00261381, 0.00263094, 0.00263575, 0.00272168, 0.00272411, 0.00270891, 0.00276706, 0.00281004, 0.00290874,
       0.00298958, 0.00287925, 0.00292917, 0.00294574, 0.00308388, 0.00300632, 0.00300664, 0.00304351, 0.00310511, 0.00314704,
       0.00307382, 0.0031967, 0.00324223, 0.0032804, 0.00328582, 0.00328493, 0.00322873, 0.00335108, 0.00344131, 0.00348589,
       0.00347806, 0.00350257, 0.00354257, 0.00361777, 0.00364609, 0.00357236, 0.00361374, 0.0036504, 0.00367545, 0.00370214,
       0.00372157, 0.00380769, 0.00386073, 0.00378243, 0.0038225, 0.00388172, 0.00388896, 0.0039206, 0.00382433, 0.0039355,
       0.00394595, 0.00403936, 0.00412466, 0.00398097, 0.00412995, 0.00410556, 0.00412607, 0.00409762, 0.00417612, 0.00419223,
       0.00418902, 0.00420858, 0.00418737, 0.00438864, 0.00428859, 0.00424058, 0.00428341, 0.00434349, 0.00426255, 0.00425739,
       0.00426099, 0.00435654, 0.00430615, 0.0043434, 0.00436442, 0.00443317, 0.00453702, 0.00458465, 0.00451718, 0.00454829,
       0.004526, 0.00444941, 0.00459784, 0.00461657, 0.00464116, 0.00463936, 0.00462128, 0.00464869, 0.00472074, 0.00464255,
       0.00463531, 0.00464357, 0.00472312, 0.00471226, 0.00472876, 0.00475929, 0.00477558, 0.00477493, 0.00476745, 0.00480513,
       0.00488634, 0.00489984, 0.00491695, 0.0049675, 0.00488809, 0.00492643, 0.0048836, 0.00497446, 0.00506449, 0.00503294,
       0.00507216, 0.00511015, 0.00528854, 0.00508509, 0.00508214, 0.00515293, 0.00521213, 0.00535207, 0.00521807, 0.00530294,
       0.00523004, 0.00531701, 0.00543113, 0.00540544, 0.00534221, 0.00529414, 0.00536786, 0.00530663, 0.00540221, 0.0054366,
       0.00546841, 0.00534307, 0.0053802, 0.00543647, 0.00542493, 0.00540019, 0.0054354, 0.00542636, 0.00540218, 0.00539761,
       0.00546834, 0.00538748, 0.0054119, 0.00524333, 0.0052661, 0.00528475, 0.00527178, 0.00527688, 0.00527451, 0.0051803,
       0.00532525, 0.00516377, 0.00502179, 0.00498588, 0.00493792, 0.00504124, 0.00497812, 0.00480997, 0.00484698, 0.00475996,
       0.00467631, 0.0046375, 0.00452982, 0.00445893, 0.00443842, 0.00431203, 0.004365, 0.00422527, 0.00416564, 0.00407752,
       0.00394289, 0.00401572, 0.00385061, 0.00368295, 0.00359867, 0.00356532, 0.00350603, 0.00343337, 0.00328738, 0.00314308,
       0.00308744, 0.00307742, 0.00298919, 0.00291293, 0.00276594, 0.00274861, 0.00263172, 0.00244029, 0.00243841, 0.0023837,
       0.00222602, 0.00220015, 0.00206933, 0.0019725, 0.00198421, 0.00188412, 0.00176243, 0.00169384, 0.00163604, 0.00154739,
       0.00148061, 0.00135909, 0.00128767, 0.00121056, 0.00116466, 0.00113142, 0.00102363, 0.000933341, 0.000903136, 0.00086764,
       0.000834096, 0.000722275, 0.000704733, 0.000665919, 0.000615007, 0.00057151, 0.000541261, 0.000484668, 0.000465868, 0.000435923,
       0.000406347, 0.000362091, 0.000334272, 0.000302766, 0.000280562, 0.000268874, 0.000248102, 0.000231557, 0.0002133, 0.0001981,
       0.000193611, 0.000166442, 0.000154017, 0.000139056, 0.0001301, 0.00011928, 0.000122511, 0.000106704, 8.5411e-05, 8.49339e-05,
       8.20717e-05, 6.96905e-05, 6.09304e-05, 5.20402e-05, 5.76345e-05, 5.77646e-05, 4.39089e-05, 6.16243e-05};

  std::vector<G4double> PhotonEnergy_RI =
      {0.1000 * eV, 1.0000 * eV, 1.0121 * eV, 1.0332 * eV,
       1.0552 * eV, 1.0781 * eV, 1.1021 * eV, 1.1271 * eV,
       1.1533 * eV, 1.1808 * eV, 1.2096 * eV, 1.2398 * eV,
       1.2716 * eV, 1.3051 * eV, 1.3404 * eV, 1.3776 * eV,
       1.4170 * eV, 1.4586 * eV, 1.5028 * eV, 1.5498 * eV,
       1.5998 * eV, 1.6531 * eV, 1.7101 * eV, 1.7712 * eV,
       1.8368 * eV, 1.9074 * eV, 1.9837 * eV, 2.0664 * eV,
       2.1562 * eV, 2.2543 * eV, 2.3616 * eV, 2.4797 * eV,
       2.6102 * eV, 2.7552 * eV, 2.9173 * eV, 3.0996 * eV,
       3.3062 * eV, 3.5424 * eV, 3.8149 * eV, 4.1328 * eV,
       4.5085 * eV, 4.9594 * eV};

  std::vector<G4double> RefractiveIndex =
      {1.8212, 1.8212, 1.8215, 1.8219,
       1.8223, 1.8227, 1.8231, 1.8236,
       1.8240, 1.8245, 1.8250, 1.8255,
       1.8261, 1.8266, 1.8272, 1.8279,
       1.8285, 1.8293, 1.8300, 1.8308,
       1.8317, 1.8327, 1.8338, 1.8349,
       1.8362, 1.8376, 1.8392, 1.8410,
       1.8430, 1.8453, 1.8479, 1.8509,
       1.8545, 1.8587, 1.8637, 1.8699,
       1.8774, 1.8869, 1.8991, 1.9152,
       1.9374, 1.9694};
  // G4double Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm };

  std::vector<G4double> PhotonEnergy_ABS =
      {1.78417 * eV, 1.7971 * eV, 1.81022 * eV, 1.82353 * eV, 1.83704 * eV, 1.85075 * eV, 1.86466 * eV, 1.87879 * eV, 1.89313 * eV, 1.90769 * eV,
       1.92248 * eV, 1.9375 * eV, 1.95276 * eV, 1.96825 * eV, 1.984 * eV, 2 * eV, 2.01626 * eV, 2.03279 * eV, 2.04959 * eV, 2.06667 * eV,
       2.08403 * eV, 2.10169 * eV, 2.11966 * eV, 2.13793 * eV, 2.15652 * eV, 2.17544 * eV, 2.19469 * eV, 2.21429 * eV, 2.23423 * eV, 2.25455 * eV,
       2.27523 * eV, 2.2963 * eV, 2.31776 * eV, 2.33962 * eV, 2.3619 * eV, 2.38462 * eV, 2.40777 * eV, 2.43137 * eV, 2.45545 * eV, 2.48 * eV,
       2.50505 * eV, 2.53061 * eV, 2.5567 * eV, 2.58333 * eV, 2.61053 * eV, 2.6383 * eV, 2.66667 * eV, 2.69565 * eV, 2.72527 * eV, 2.75556 * eV,
       2.78652 * eV, 2.81818 * eV, 2.85057 * eV, 2.88372 * eV, 2.91765 * eV, 2.95238 * eV, 2.98795 * eV, 3.02439 * eV, 3.06173 * eV, 3.1 * eV,
       3.13924 * eV, 3.17949 * eV, 3.22078 * eV, 3.26316 * eV, 3.30667 * eV, 3.35135 * eV, 3.39726 * eV, 3.44444 * eV, 3.49296 * eV, 3.54286 * eV,
       3.5942 * eV, 3.64706 * eV, 3.70149 * eV, 3.75758 * eV, 3.81538 * eV, 3.875 * eV, 3.93651 * eV, 4 * eV, 4.06557 * eV, 4.13333 * eV,
       4.20339 * eV, 4.27586 * eV, 4.35088 * eV, 4.42857 * eV, 4.50909 * eV, 4.59259 * eV, 4.67925 * eV, 4.76923 * eV, 4.86275 * eV};
  std::vector<G4double> Absorption =
      {1.66482 * m, 1.0584 * m, 1.90233 * m, 0.958758 * m, 1.16913 * m, 1.05368 * m, 0.881739 * m, 2.74593 * m, 0.969113 * m, 1.30342 * m,
       1.11065 * m, 1.14053 * m, 0.926481 * m, 0.835474 * m, 0.814388 * m, 0.702776 * m, 1.01264 * m, 0.749002 * m, 0.691299 * m, 0.791851 * m,
       0.708582 * m, 0.609636 * m, 0.625308 * m, 0.59058 * m, 0.522642 * m, 0.599727 * m, 0.595345 * m, 0.594927 * m, 0.574464 * m, 0.541271 * m,
       0.531547 * m, 0.581632 * m, 0.57251 * m, 0.560577 * m, 0.493902 * m, 0.422165 * m, 0.354962 * m, 0.255139 * m, 0.151762 * m, 0.0827965 * m,
       0.0409174 * m, 0.02007 * m, 0.0100463 * m, 0.00588694 * m, 0.00636339 * m, 0.0084497 * m, 0.0224574 * m, 0.0509883 * m, 0.262914 * m, 0.0571499 * m,
       0.0830375 * m, 0.378696 * m, 0.0528428 * m, 0.0661874 * m, 0.0930821 * m, 0.0672707 * m, 0.0152385 * m, 0.00676752 * m, 0.00538106 * m, 0.00799596 * m,
       0.0177025 * m, 0.0411282 * m, 0.0919861 * m, 0.149875 * m, 0.132761 * m, 0.068419 * m, 0.0246548 * m, 0.00922619 * m, 0.00902168 * m, 0.0264256 * m,
       0.0839517 * m, 0.0796384 * m, 0.0552649 * m, 0.0197203 * m, 0.00872616 * m, 0.00764327 * m, 0.0153009 * m, 0.0299903 * m, 0.0403526 * m, 0.0377371 * m,
       0.0322887 * m, 0.0251734 * m, 0.0194992 * m, 0.0145645 * m, 0.0112908 * m, 0.0100775 * m, 0.0112081 * m, 0.0158907 * m, 0.019793 * m};

  // for now, using the LSO scintillation properties
  const G4int nEntries_SCY = 12;
  G4double ElectronEnergy_SCY[nEntries_SCY] =
      {0.000 * MeV, 0.015 * MeV, 0.020 * MeV, 0.030 * MeV,
       0.040 * MeV, 0.060 * MeV, 0.080 * MeV, 0.090 * MeV,
       0.105 * MeV, 0.300 * MeV, 0.500 * MeV, 1.000 * MeV};
  G4double ScintilYield[nEntries_SCY] =
      {0.10, 0.46, 0.60, 0.68,
       0.74, 0.80, 0.82, 0.84,
       0.87, 0.96, 0.98, 1.00};
  for (int i = 0; i < nEntries_SCY; i++)
    ScintilYield[i] = 15000.0 * MeV * ScintilYield[i] * ElectronEnergy_SCY[i];

  for (auto& value : Absorption)
  {
      value *= scaleFactor;
  }
  double birks = (user_birks < 0) ? 0 : user_birks; 

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_RI,   Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  // myMPT->AddProperty("ELECTRONSCINTILLATIONYIELD", ElectronEnergy_SCY, ScintilYield, nEntries_SCY);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 8.5);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 60. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

  mat->SetMaterialPropertiesTable(myMPT);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks*mm/MeV);
  return mat;
}

G4Material *MyMaterials::LuAG_Pr(double user_lightyield, double scaleFactor, double user_birks) // Lutetium Aluminum Garnet -
{
  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Lu = new G4Element("Lutetium", "Lu", z = 71., a = 174.97 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("LuAG_Pr", density = 6.7 * g / cm3, 3);
  mat->AddElement(Lu, 3);
  mat->AddElement(Al, 12);
  mat->AddElement(O, 5);

  double standard_light_yield = 7000.0;
  double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  //  2 bands at 290nm (4.28eV) and 350nm (3.54eV) about 50% of the light in each.
  std::vector<G4double> PhotonEnergy_FAST =
      {1.00 * eV, 3.40 * eV, 3.50 * eV, 3.60 * eV,
       3.90 * eV, 3.91 * eV, 4.07 * eV, 4.08 * eV};
  std::vector<G4double> FastComponent =
      {0.00, 0.00, 1.00, 0.00,
       0.00, 1.00, 0.00, 0.00};

  std::vector<G4double> PhotonEnergy_RI =
      {0.1000 * eV, 1.0000 * eV, 1.0121 * eV, 1.0332 * eV,
       1.0552 * eV, 1.0781 * eV, 1.1021 * eV, 1.1271 * eV,
       1.1533 * eV, 1.1808 * eV, 1.2096 * eV, 1.2398 * eV,
       1.2716 * eV, 1.3051 * eV, 1.3404 * eV, 1.3776 * eV,
       1.4170 * eV, 1.4586 * eV, 1.5028 * eV, 1.5498 * eV,
       1.5998 * eV, 1.6531 * eV, 1.7101 * eV, 1.7712 * eV,
       1.8368 * eV, 1.9074 * eV, 1.9837 * eV, 2.0664 * eV,
       2.1562 * eV, 2.2543 * eV, 2.3616 * eV, 2.4797 * eV,
       2.6102 * eV, 2.7552 * eV, 2.9173 * eV, 3.0996 * eV,
       3.3062 * eV, 3.5424 * eV, 3.8149 * eV, 4.1328 * eV,
       4.5085 * eV, 4.9594 * eV};

  std::vector<G4double> RefractiveIndex =
      {1.8212, 1.8212, 1.8215, 1.8219,
       1.8223, 1.8227, 1.8231, 1.8236,
       1.8240, 1.8245, 1.8250, 1.8255,
       1.8261, 1.8266, 1.8272, 1.8279,
       1.8285, 1.8293, 1.8300, 1.8308,
       1.8317, 1.8327, 1.8338, 1.8349,
       1.8362, 1.8376, 1.8392, 1.8410,
       1.8430, 1.8453, 1.8479, 1.8509,
       1.8545, 1.8587, 1.8637, 1.8699,
       1.8774, 1.8869, 1.8991, 1.9152,
       1.9374, 1.9694};
  // G4double Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.0 * eV, 1.84 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {138. * mm, 138. * mm, 138. * mm};

  for (auto& value : Absorption)
  {
      value *= scaleFactor;
  }
  double birks = (user_birks < 0) ? 0 : user_birks; 

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_RI,   Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 6.4);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

  mat->SetMaterialPropertiesTable(myMPT);
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks*mm/MeV);
  return mat;
}

G4Material *MyMaterials::NaI_Tl(double user_lightyield, double scaleFactor, double user_birks)
{
  double lightyield = (user_lightyield == -1) ? 38000 : user_lightyield;
  // Birks' constant is used to describe the non-linear light yield effect in scintillator materials
  double birks = (user_birks < 0) ? 0 : user_birks;

  G4double a, z, density;
  G4Element *Na = new G4Element("Sodium", "Na", z = 11., a = 22.99 * g / mole);
  G4Element *I = new G4Element("Iodine", "I", z = 53., a = 126.9 * g / mole);

  G4Material *mat = new G4Material("NaI_Tl", density = 3.67 * g / cm3, 2, kStateSolid);
  mat->AddElement(Na, 1);
  mat->AddElement(I, 1);

  std::vector<G4double> PhotonEnergy_FAST =
      {1.77169 * eV, 1.77266 * eV, 1.77558 * eV, 1.77851 * eV, 1.78145 * eV, 1.78539 * eV, 1.79033 * eV, 1.7963 * eV, 1.80231 * eV, 1.80836 * eV,
       1.81445 * eV, 1.82058 * eV, 1.82882 * eV, 1.83401 * eV, 1.84553 * eV, 1.85293 * eV, 1.86147 * eV, 1.869 * eV, 1.87769 * eV, 1.89308 * eV,
       1.90536 * eV, 1.92007 * eV, 1.93039 * eV, 1.94901 * eV, 1.95846 * eV, 1.9668 * eV, 1.97884 * eV, 1.99102 * eV, 2.00088 * eV, 2.01209 * eV,
       2.02596 * eV, 2.03617 * eV, 2.04519 * eV, 2.0569 * eV, 2.06611 * eV, 2.0794 * eV, 2.09151 * eV, 2.10239 * eV, 2.112 * eV, 2.1231 * eV,
       2.13431 * eV, 2.14565 * eV, 2.15566 * eV, 2.16868 * eV, 2.18038 * eV, 2.19519 * eV, 2.21171 * eV, 2.2193 * eV, 2.23619 * eV, 2.23464 * eV,
       2.24395 * eV, 2.25806 * eV, 2.27234 * eV, 2.28358 * eV, 2.29493 * eV, 2.30475 * eV, 2.31631 * eV, 2.32463 * eV, 2.33134 * eV, 2.33809 * eV,
       2.34487 * eV, 2.35856 * eV, 2.36719 * eV, 2.37939 * eV, 2.38642 * eV, 2.40238 * eV, 2.41134 * eV, 2.424 * eV, 2.43312 * eV, 2.44047 * eV,
       2.44786 * eV, 2.46278 * eV, 2.47788 * eV, 2.48741 * eV, 2.49317 * eV, 2.49702 * eV, 2.50282 * eV, 2.50865 * eV, 2.5145 * eV, 2.52038 * eV,
       2.52432 * eV, 2.53223 * eV, 2.5362 * eV, 2.54619 * eV, 2.55424 * eV, 2.56031 * eV, 2.56437 * eV, 2.57049 * eV, 2.57663 * eV, 2.58487 * eV,
       2.59317 * eV, 2.59734 * eV, 2.60571 * eV, 2.61414 * eV, 2.61414 * eV, 2.61837 * eV, 2.62262 * eV, 2.62475 * eV, 2.62902 * eV, 2.63331 * eV,
       2.63545 * eV, 2.63976 * eV, 2.64191 * eV, 2.64841 * eV, 2.65493 * eV, 2.6593 * eV, 2.66149 * eV, 2.66588 * eV, 2.67914 * eV, 2.67914 * eV,
       2.68136 * eV, 2.68136 * eV, 2.68359 * eV, 2.68805 * eV, 2.68805 * eV, 2.68805 * eV, 2.69477 * eV, 2.69477 * eV, 2.69702 * eV, 2.70153 * eV,
       2.70605 * eV, 2.71286 * eV, 2.71742 * eV, 2.71971 * eV, 2.722 * eV, 2.722 * eV, 2.72429 * eV, 2.72889 * eV, 2.72889 * eV, 2.73351 * eV,
       2.73814 * eV, 2.74279 * eV, 2.74512 * eV, 2.74979 * eV, 2.75213 * eV, 2.75447 * eV, 2.75917 * eV, 2.75682 * eV, 2.76389 * eV, 2.76626 * eV,
       2.76389 * eV, 2.76626 * eV, 2.77338 * eV, 2.77576 * eV, 2.78533 * eV, 2.79255 * eV, 2.79738 * eV, 2.80223 * eV, 2.80466 * eV, 2.80709 * eV,
       2.80953 * eV, 2.80953 * eV, 2.81934 * eV, 2.8218 * eV, 2.82673 * eV, 2.83168 * eV, 2.84164 * eV, 2.84916 * eV, 2.85419 * eV, 2.8643 * eV,
       2.86684 * eV, 2.87449 * eV, 2.87705 * eV, 2.87961 * eV, 2.88475 * eV, 2.88733 * eV, 2.8925 * eV, 2.89509 * eV, 2.90028 * eV, 2.90549 * eV,
       2.90811 * eV, 2.91073 * eV, 2.91335 * eV, 2.91335 * eV, 2.91335 * eV, 2.91861 * eV, 2.92125 * eV, 2.92125 * eV, 2.92389 * eV, 2.92654 * eV,
       2.92654 * eV, 2.92919 * eV, 2.92919 * eV, 2.93185 * eV, 2.93451 * eV, 2.93717 * eV, 2.93985 * eV, 2.94252 * eV, 2.9452 * eV, 2.94789 * eV,
       2.94789 * eV, 2.94789 * eV, 2.95058 * eV, 2.95868 * eV, 2.96411 * eV, 2.96955 * eV, 2.97228 * eV, 2.97228 * eV, 2.96955 * eV, 2.97228 * eV,
       2.97502 * eV, 2.97776 * eV, 2.97502 * eV, 2.9805 * eV, 2.9805 * eV, 2.9805 * eV, 2.98601 * eV, 2.99154 * eV, 2.99431 * eV, 2.99431 * eV,
       2.99708 * eV, 2.99431 * eV, 2.99708 * eV, 3.00544 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.01385 * eV, 3.0223 * eV,
       3.02797 * eV, 3.03081 * eV, 3.02797 * eV, 3.03365 * eV, 3.03081 * eV, 3.03081 * eV, 3.0365 * eV, 3.03935 * eV, 3.04221 * eV, 3.04795 * eV,
       3.04795 * eV, 3.05083 * eV, 3.05371 * eV, 3.05949 * eV, 3.06239 * eV, 3.06529 * eV, 3.0682 * eV, 3.06529 * eV, 3.07112 * eV, 3.0682 * eV,
       3.07696 * eV, 3.08283 * eV, 3.0976 * eV, 3.09464 * eV, 3.09464 * eV, 3.10653 * eV, 3.11252 * eV, 3.11852 * eV, 3.12757 * eV, 3.13668 * eV,
       3.14583 * eV, 3.15813 * eV, 3.16741 * eV, 3.17675 * eV, 3.20828 * eV, 3.23719 * eV, 3.26664 * eV, 3.28656 * eV, 3.31351 * eV, 3.34783 * eV,
       3.38287 * eV};
  std::vector<G4double> FastComponent =
      {0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
       0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
       0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
       0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
       0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
       0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
       0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
       0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
       0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
       0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
       1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
       1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
       1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
       1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
       1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
       2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
       2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
       1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
       1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
       1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
       1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
       1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
       0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
       0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
       0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
       0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
       0.011691};

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 1.84 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.82, 1.82, 1.82};
  // std::vector<G4double> Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.00 * eV, 2.82 * eV, 2.88 * eV, 2.95 * eV, 3.02 * eV, 3.10 * eV, 3.18 * eV, 3.26 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {438. * mm, 438. * mm, 413. * mm, 375. * mm, 263. * mm, 87.5 * mm, 11.5 * mm, 1.0 * mm, 1.0 * mm};
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_ABS,  Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 10);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1);

  mat->SetMaterialPropertiesTable(myMPT);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}
G4Material *MyMaterials::CsI_Tl(double user_lightyield, double scaleFactor, double user_birks)
{
  double lightyield = (user_lightyield == -1) ? 60000 : user_lightyield;
  // Birks' constant is used to describe the non-linear light yield effect in scintillator materials
  double birks = (user_birks < 0) ? 0 : user_birks;

  G4double a, z, density;
  G4Element *Cs = new G4Element("Caesium", "Cs", z = 55., a = 132.91 * g / mole);
  G4Element *I = new G4Element("Iodine", "I", z = 53., a = 126.9 * g / mole);

  G4Material *mat = new G4Material("CsI_Tl", density = 4.51 * g / cm3, 2, kStateSolid);
  mat->AddElement(Cs, 1);
  mat->AddElement(I, 1);

  std::vector<G4double> PhotonEnergy_FAST =
      {1.77169 * eV, 1.77266 * eV, 1.77558 * eV, 1.77851 * eV, 1.78145 * eV, 1.78539 * eV, 1.79033 * eV, 1.7963 * eV, 1.80231 * eV, 1.80836 * eV,
       1.81445 * eV, 1.82058 * eV, 1.82882 * eV, 1.83401 * eV, 1.84553 * eV, 1.85293 * eV, 1.86147 * eV, 1.869 * eV, 1.87769 * eV, 1.89308 * eV,
       1.90536 * eV, 1.92007 * eV, 1.93039 * eV, 1.94901 * eV, 1.95846 * eV, 1.9668 * eV, 1.97884 * eV, 1.99102 * eV, 2.00088 * eV, 2.01209 * eV,
       2.02596 * eV, 2.03617 * eV, 2.04519 * eV, 2.0569 * eV, 2.06611 * eV, 2.0794 * eV, 2.09151 * eV, 2.10239 * eV, 2.112 * eV, 2.1231 * eV,
       2.13431 * eV, 2.14565 * eV, 2.15566 * eV, 2.16868 * eV, 2.18038 * eV, 2.19519 * eV, 2.21171 * eV, 2.2193 * eV, 2.23619 * eV, 2.23464 * eV,
       2.24395 * eV, 2.25806 * eV, 2.27234 * eV, 2.28358 * eV, 2.29493 * eV, 2.30475 * eV, 2.31631 * eV, 2.32463 * eV, 2.33134 * eV, 2.33809 * eV,
       2.34487 * eV, 2.35856 * eV, 2.36719 * eV, 2.37939 * eV, 2.38642 * eV, 2.40238 * eV, 2.41134 * eV, 2.424 * eV, 2.43312 * eV, 2.44047 * eV,
       2.44786 * eV, 2.46278 * eV, 2.47788 * eV, 2.48741 * eV, 2.49317 * eV, 2.49702 * eV, 2.50282 * eV, 2.50865 * eV, 2.5145 * eV, 2.52038 * eV,
       2.52432 * eV, 2.53223 * eV, 2.5362 * eV, 2.54619 * eV, 2.55424 * eV, 2.56031 * eV, 2.56437 * eV, 2.57049 * eV, 2.57663 * eV, 2.58487 * eV,
       2.59317 * eV, 2.59734 * eV, 2.60571 * eV, 2.61414 * eV, 2.61414 * eV, 2.61837 * eV, 2.62262 * eV, 2.62475 * eV, 2.62902 * eV, 2.63331 * eV,
       2.63545 * eV, 2.63976 * eV, 2.64191 * eV, 2.64841 * eV, 2.65493 * eV, 2.6593 * eV, 2.66149 * eV, 2.66588 * eV, 2.67914 * eV, 2.67914 * eV,
       2.68136 * eV, 2.68136 * eV, 2.68359 * eV, 2.68805 * eV, 2.68805 * eV, 2.68805 * eV, 2.69477 * eV, 2.69477 * eV, 2.69702 * eV, 2.70153 * eV,
       2.70605 * eV, 2.71286 * eV, 2.71742 * eV, 2.71971 * eV, 2.722 * eV, 2.722 * eV, 2.72429 * eV, 2.72889 * eV, 2.72889 * eV, 2.73351 * eV,
       2.73814 * eV, 2.74279 * eV, 2.74512 * eV, 2.74979 * eV, 2.75213 * eV, 2.75447 * eV, 2.75917 * eV, 2.75682 * eV, 2.76389 * eV, 2.76626 * eV,
       2.76389 * eV, 2.76626 * eV, 2.77338 * eV, 2.77576 * eV, 2.78533 * eV, 2.79255 * eV, 2.79738 * eV, 2.80223 * eV, 2.80466 * eV, 2.80709 * eV,
       2.80953 * eV, 2.80953 * eV, 2.81934 * eV, 2.8218 * eV, 2.82673 * eV, 2.83168 * eV, 2.84164 * eV, 2.84916 * eV, 2.85419 * eV, 2.8643 * eV,
       2.86684 * eV, 2.87449 * eV, 2.87705 * eV, 2.87961 * eV, 2.88475 * eV, 2.88733 * eV, 2.8925 * eV, 2.89509 * eV, 2.90028 * eV, 2.90549 * eV,
       2.90811 * eV, 2.91073 * eV, 2.91335 * eV, 2.91335 * eV, 2.91335 * eV, 2.91861 * eV, 2.92125 * eV, 2.92125 * eV, 2.92389 * eV, 2.92654 * eV,
       2.92654 * eV, 2.92919 * eV, 2.92919 * eV, 2.93185 * eV, 2.93451 * eV, 2.93717 * eV, 2.93985 * eV, 2.94252 * eV, 2.9452 * eV, 2.94789 * eV,
       2.94789 * eV, 2.94789 * eV, 2.95058 * eV, 2.95868 * eV, 2.96411 * eV, 2.96955 * eV, 2.97228 * eV, 2.97228 * eV, 2.96955 * eV, 2.97228 * eV,
       2.97502 * eV, 2.97776 * eV, 2.97502 * eV, 2.9805 * eV, 2.9805 * eV, 2.9805 * eV, 2.98601 * eV, 2.99154 * eV, 2.99431 * eV, 2.99431 * eV,
       2.99708 * eV, 2.99431 * eV, 2.99708 * eV, 3.00544 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.01385 * eV, 3.0223 * eV,
       3.02797 * eV, 3.03081 * eV, 3.02797 * eV, 3.03365 * eV, 3.03081 * eV, 3.03081 * eV, 3.0365 * eV, 3.03935 * eV, 3.04221 * eV, 3.04795 * eV,
       3.04795 * eV, 3.05083 * eV, 3.05371 * eV, 3.05949 * eV, 3.06239 * eV, 3.06529 * eV, 3.0682 * eV, 3.06529 * eV, 3.07112 * eV, 3.0682 * eV,
       3.07696 * eV, 3.08283 * eV, 3.0976 * eV, 3.09464 * eV, 3.09464 * eV, 3.10653 * eV, 3.11252 * eV, 3.11852 * eV, 3.12757 * eV, 3.13668 * eV,
       3.14583 * eV, 3.15813 * eV, 3.16741 * eV, 3.17675 * eV, 3.20828 * eV, 3.23719 * eV, 3.26664 * eV, 3.28656 * eV, 3.31351 * eV, 3.34783 * eV,
       3.38287 * eV};
  std::vector<G4double> FastComponent =
      {0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
       0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
       0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
       0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
       0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
       0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
       0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
       0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
       0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
       0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
       1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
       1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
       1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
       1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
       1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
       2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
       2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
       1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
       1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
       1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
       1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
       1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
       0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
       0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
       0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
       0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
       0.011691};

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 1.84 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.82, 1.82, 1.82};
  // std::vector<G4double> Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.00 * eV, 2.82 * eV, 2.88 * eV, 2.95 * eV, 3.02 * eV, 3.10 * eV, 3.18 * eV, 3.26 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {438. * mm, 438. * mm, 413. * mm, 375. * mm, 263. * mm, 87.5 * mm, 11.5 * mm, 1.0 * mm, 1.0 * mm};
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_ABS,  Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 10);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1000. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1);

  mat->SetMaterialPropertiesTable(myMPT);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}
G4Material *MyMaterials::CsI(double user_lightyield, double scaleFactor, double user_birks)
{
  double lightyield = (user_lightyield == -1) ? 1500 : user_lightyield;
  // Birks' constant is used to describe the non-linear light yield effect in scintillator materials
  double birks = (user_birks < 0) ? 0 : user_birks;

  G4double a, z, density;
  G4Element *Cs = new G4Element("Caesium", "Cs", z = 55., a = 132.91 * g / mole);
  G4Element *I = new G4Element("Iodine", "I", z = 53., a = 126.9 * g / mole);

  G4Material *mat = new G4Material("CsI", density = 4.51 * g / cm3, 2, kStateSolid);
  mat->AddElement(Cs, 1);
  mat->AddElement(I, 1);

  std::vector<G4double> PhotonEnergy_FAST =
      {1.77169 * eV, 1.77266 * eV, 1.77558 * eV, 1.77851 * eV, 1.78145 * eV, 1.78539 * eV, 1.79033 * eV, 1.7963 * eV, 1.80231 * eV, 1.80836 * eV,
       1.81445 * eV, 1.82058 * eV, 1.82882 * eV, 1.83401 * eV, 1.84553 * eV, 1.85293 * eV, 1.86147 * eV, 1.869 * eV, 1.87769 * eV, 1.89308 * eV,
       1.90536 * eV, 1.92007 * eV, 1.93039 * eV, 1.94901 * eV, 1.95846 * eV, 1.9668 * eV, 1.97884 * eV, 1.99102 * eV, 2.00088 * eV, 2.01209 * eV,
       2.02596 * eV, 2.03617 * eV, 2.04519 * eV, 2.0569 * eV, 2.06611 * eV, 2.0794 * eV, 2.09151 * eV, 2.10239 * eV, 2.112 * eV, 2.1231 * eV,
       2.13431 * eV, 2.14565 * eV, 2.15566 * eV, 2.16868 * eV, 2.18038 * eV, 2.19519 * eV, 2.21171 * eV, 2.2193 * eV, 2.23619 * eV, 2.23464 * eV,
       2.24395 * eV, 2.25806 * eV, 2.27234 * eV, 2.28358 * eV, 2.29493 * eV, 2.30475 * eV, 2.31631 * eV, 2.32463 * eV, 2.33134 * eV, 2.33809 * eV,
       2.34487 * eV, 2.35856 * eV, 2.36719 * eV, 2.37939 * eV, 2.38642 * eV, 2.40238 * eV, 2.41134 * eV, 2.424 * eV, 2.43312 * eV, 2.44047 * eV,
       2.44786 * eV, 2.46278 * eV, 2.47788 * eV, 2.48741 * eV, 2.49317 * eV, 2.49702 * eV, 2.50282 * eV, 2.50865 * eV, 2.5145 * eV, 2.52038 * eV,
       2.52432 * eV, 2.53223 * eV, 2.5362 * eV, 2.54619 * eV, 2.55424 * eV, 2.56031 * eV, 2.56437 * eV, 2.57049 * eV, 2.57663 * eV, 2.58487 * eV,
       2.59317 * eV, 2.59734 * eV, 2.60571 * eV, 2.61414 * eV, 2.61414 * eV, 2.61837 * eV, 2.62262 * eV, 2.62475 * eV, 2.62902 * eV, 2.63331 * eV,
       2.63545 * eV, 2.63976 * eV, 2.64191 * eV, 2.64841 * eV, 2.65493 * eV, 2.6593 * eV, 2.66149 * eV, 2.66588 * eV, 2.67914 * eV, 2.67914 * eV,
       2.68136 * eV, 2.68136 * eV, 2.68359 * eV, 2.68805 * eV, 2.68805 * eV, 2.68805 * eV, 2.69477 * eV, 2.69477 * eV, 2.69702 * eV, 2.70153 * eV,
       2.70605 * eV, 2.71286 * eV, 2.71742 * eV, 2.71971 * eV, 2.722 * eV, 2.722 * eV, 2.72429 * eV, 2.72889 * eV, 2.72889 * eV, 2.73351 * eV,
       2.73814 * eV, 2.74279 * eV, 2.74512 * eV, 2.74979 * eV, 2.75213 * eV, 2.75447 * eV, 2.75917 * eV, 2.75682 * eV, 2.76389 * eV, 2.76626 * eV,
       2.76389 * eV, 2.76626 * eV, 2.77338 * eV, 2.77576 * eV, 2.78533 * eV, 2.79255 * eV, 2.79738 * eV, 2.80223 * eV, 2.80466 * eV, 2.80709 * eV,
       2.80953 * eV, 2.80953 * eV, 2.81934 * eV, 2.8218 * eV, 2.82673 * eV, 2.83168 * eV, 2.84164 * eV, 2.84916 * eV, 2.85419 * eV, 2.8643 * eV,
       2.86684 * eV, 2.87449 * eV, 2.87705 * eV, 2.87961 * eV, 2.88475 * eV, 2.88733 * eV, 2.8925 * eV, 2.89509 * eV, 2.90028 * eV, 2.90549 * eV,
       2.90811 * eV, 2.91073 * eV, 2.91335 * eV, 2.91335 * eV, 2.91335 * eV, 2.91861 * eV, 2.92125 * eV, 2.92125 * eV, 2.92389 * eV, 2.92654 * eV,
       2.92654 * eV, 2.92919 * eV, 2.92919 * eV, 2.93185 * eV, 2.93451 * eV, 2.93717 * eV, 2.93985 * eV, 2.94252 * eV, 2.9452 * eV, 2.94789 * eV,
       2.94789 * eV, 2.94789 * eV, 2.95058 * eV, 2.95868 * eV, 2.96411 * eV, 2.96955 * eV, 2.97228 * eV, 2.97228 * eV, 2.96955 * eV, 2.97228 * eV,
       2.97502 * eV, 2.97776 * eV, 2.97502 * eV, 2.9805 * eV, 2.9805 * eV, 2.9805 * eV, 2.98601 * eV, 2.99154 * eV, 2.99431 * eV, 2.99431 * eV,
       2.99708 * eV, 2.99431 * eV, 2.99708 * eV, 3.00544 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.01385 * eV, 3.0223 * eV,
       3.02797 * eV, 3.03081 * eV, 3.02797 * eV, 3.03365 * eV, 3.03081 * eV, 3.03081 * eV, 3.0365 * eV, 3.03935 * eV, 3.04221 * eV, 3.04795 * eV,
       3.04795 * eV, 3.05083 * eV, 3.05371 * eV, 3.05949 * eV, 3.06239 * eV, 3.06529 * eV, 3.0682 * eV, 3.06529 * eV, 3.07112 * eV, 3.0682 * eV,
       3.07696 * eV, 3.08283 * eV, 3.0976 * eV, 3.09464 * eV, 3.09464 * eV, 3.10653 * eV, 3.11252 * eV, 3.11852 * eV, 3.12757 * eV, 3.13668 * eV,
       3.14583 * eV, 3.15813 * eV, 3.16741 * eV, 3.17675 * eV, 3.20828 * eV, 3.23719 * eV, 3.26664 * eV, 3.28656 * eV, 3.31351 * eV, 3.34783 * eV,
       3.38287 * eV};
  std::vector<G4double> FastComponent =
      {0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
       0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
       0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
       0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
       0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
       0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
       0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
       0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
       0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
       0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
       1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
       1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
       1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
       1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
       1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
       2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
       2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
       1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
       1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
       1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
       1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
       1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
       0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
       0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
       0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
       0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
       0.011691};

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 1.84 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.82, 1.82, 1.82};
  // std::vector<G4double> Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.00 * eV, 2.82 * eV, 2.88 * eV, 2.95 * eV, 3.02 * eV, 3.10 * eV, 3.18 * eV, 3.26 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {438. * mm, 438. * mm, 413. * mm, 375. * mm, 263. * mm, 87.5 * mm, 11.5 * mm, 1.0 * mm, 1.0 * mm};
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_ABS,  Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 10);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 10. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1);

  mat->SetMaterialPropertiesTable(myMPT);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}

G4Material *MyMaterials::BaF2(double user_lightyield, double scaleFactor, double user_birks)
{
  double lightyield = (user_lightyield == -1) ? 12000 : user_lightyield;
  // Birks' constant is used to describe the non-linear light yield effect in scintillator materials
  double birks = (user_birks < 0) ? 0 : user_birks;

  G4double a, z, density;
  G4Element *Ba = new G4Element("Barium", "Ba", z = 56., a = 137.33 * g / mole);
  G4Element *F = new G4Element("Fluorine", "F", z = 9., a = 18.998 * g / mole);

  G4Material *mat = new G4Material("BaF2", density = 4.89 * g / cm3, 2, kStateSolid);
  mat->AddElement(Ba, 1);
  mat->AddElement(F, 2);

  std::vector<G4double> PhotonEnergy_FAST =
      {1.77169 * eV, 1.77266 * eV, 1.77558 * eV, 1.77851 * eV, 1.78145 * eV, 1.78539 * eV, 1.79033 * eV, 1.7963 * eV, 1.80231 * eV, 1.80836 * eV,
       1.81445 * eV, 1.82058 * eV, 1.82882 * eV, 1.83401 * eV, 1.84553 * eV, 1.85293 * eV, 1.86147 * eV, 1.869 * eV, 1.87769 * eV, 1.89308 * eV,
       1.90536 * eV, 1.92007 * eV, 1.93039 * eV, 1.94901 * eV, 1.95846 * eV, 1.9668 * eV, 1.97884 * eV, 1.99102 * eV, 2.00088 * eV, 2.01209 * eV,
       2.02596 * eV, 2.03617 * eV, 2.04519 * eV, 2.0569 * eV, 2.06611 * eV, 2.0794 * eV, 2.09151 * eV, 2.10239 * eV, 2.112 * eV, 2.1231 * eV,
       2.13431 * eV, 2.14565 * eV, 2.15566 * eV, 2.16868 * eV, 2.18038 * eV, 2.19519 * eV, 2.21171 * eV, 2.2193 * eV, 2.23619 * eV, 2.23464 * eV,
       2.24395 * eV, 2.25806 * eV, 2.27234 * eV, 2.28358 * eV, 2.29493 * eV, 2.30475 * eV, 2.31631 * eV, 2.32463 * eV, 2.33134 * eV, 2.33809 * eV,
       2.34487 * eV, 2.35856 * eV, 2.36719 * eV, 2.37939 * eV, 2.38642 * eV, 2.40238 * eV, 2.41134 * eV, 2.424 * eV, 2.43312 * eV, 2.44047 * eV,
       2.44786 * eV, 2.46278 * eV, 2.47788 * eV, 2.48741 * eV, 2.49317 * eV, 2.49702 * eV, 2.50282 * eV, 2.50865 * eV, 2.5145 * eV, 2.52038 * eV,
       2.52432 * eV, 2.53223 * eV, 2.5362 * eV, 2.54619 * eV, 2.55424 * eV, 2.56031 * eV, 2.56437 * eV, 2.57049 * eV, 2.57663 * eV, 2.58487 * eV,
       2.59317 * eV, 2.59734 * eV, 2.60571 * eV, 2.61414 * eV, 2.61414 * eV, 2.61837 * eV, 2.62262 * eV, 2.62475 * eV, 2.62902 * eV, 2.63331 * eV,
       2.63545 * eV, 2.63976 * eV, 2.64191 * eV, 2.64841 * eV, 2.65493 * eV, 2.6593 * eV, 2.66149 * eV, 2.66588 * eV, 2.67914 * eV, 2.67914 * eV,
       2.68136 * eV, 2.68136 * eV, 2.68359 * eV, 2.68805 * eV, 2.68805 * eV, 2.68805 * eV, 2.69477 * eV, 2.69477 * eV, 2.69702 * eV, 2.70153 * eV,
       2.70605 * eV, 2.71286 * eV, 2.71742 * eV, 2.71971 * eV, 2.722 * eV, 2.722 * eV, 2.72429 * eV, 2.72889 * eV, 2.72889 * eV, 2.73351 * eV,
       2.73814 * eV, 2.74279 * eV, 2.74512 * eV, 2.74979 * eV, 2.75213 * eV, 2.75447 * eV, 2.75917 * eV, 2.75682 * eV, 2.76389 * eV, 2.76626 * eV,
       2.76389 * eV, 2.76626 * eV, 2.77338 * eV, 2.77576 * eV, 2.78533 * eV, 2.79255 * eV, 2.79738 * eV, 2.80223 * eV, 2.80466 * eV, 2.80709 * eV,
       2.80953 * eV, 2.80953 * eV, 2.81934 * eV, 2.8218 * eV, 2.82673 * eV, 2.83168 * eV, 2.84164 * eV, 2.84916 * eV, 2.85419 * eV, 2.8643 * eV,
       2.86684 * eV, 2.87449 * eV, 2.87705 * eV, 2.87961 * eV, 2.88475 * eV, 2.88733 * eV, 2.8925 * eV, 2.89509 * eV, 2.90028 * eV, 2.90549 * eV,
       2.90811 * eV, 2.91073 * eV, 2.91335 * eV, 2.91335 * eV, 2.91335 * eV, 2.91861 * eV, 2.92125 * eV, 2.92125 * eV, 2.92389 * eV, 2.92654 * eV,
       2.92654 * eV, 2.92919 * eV, 2.92919 * eV, 2.93185 * eV, 2.93451 * eV, 2.93717 * eV, 2.93985 * eV, 2.94252 * eV, 2.9452 * eV, 2.94789 * eV,
       2.94789 * eV, 2.94789 * eV, 2.95058 * eV, 2.95868 * eV, 2.96411 * eV, 2.96955 * eV, 2.97228 * eV, 2.97228 * eV, 2.96955 * eV, 2.97228 * eV,
       2.97502 * eV, 2.97776 * eV, 2.97502 * eV, 2.9805 * eV, 2.9805 * eV, 2.9805 * eV, 2.98601 * eV, 2.99154 * eV, 2.99431 * eV, 2.99431 * eV,
       2.99708 * eV, 2.99431 * eV, 2.99708 * eV, 3.00544 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.01385 * eV, 3.0223 * eV,
       3.02797 * eV, 3.03081 * eV, 3.02797 * eV, 3.03365 * eV, 3.03081 * eV, 3.03081 * eV, 3.0365 * eV, 3.03935 * eV, 3.04221 * eV, 3.04795 * eV,
       3.04795 * eV, 3.05083 * eV, 3.05371 * eV, 3.05949 * eV, 3.06239 * eV, 3.06529 * eV, 3.0682 * eV, 3.06529 * eV, 3.07112 * eV, 3.0682 * eV,
       3.07696 * eV, 3.08283 * eV, 3.0976 * eV, 3.09464 * eV, 3.09464 * eV, 3.10653 * eV, 3.11252 * eV, 3.11852 * eV, 3.12757 * eV, 3.13668 * eV,
       3.14583 * eV, 3.15813 * eV, 3.16741 * eV, 3.17675 * eV, 3.20828 * eV, 3.23719 * eV, 3.26664 * eV, 3.28656 * eV, 3.31351 * eV, 3.34783 * eV,
       3.38287 * eV};
  std::vector<G4double> FastComponent =
      {0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
       0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
       0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
       0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
       0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
       0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
       0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
       0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
       0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
       0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
       1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
       1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
       1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
       1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
       1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
       2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
       2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
       1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
       1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
       1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
       1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
       1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
       0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
       0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
       0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
       0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
       0.011691};

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 1.84 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.82, 1.82, 1.82};
  // std::vector<G4double> Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.00 * eV, 2.82 * eV, 2.88 * eV, 2.95 * eV, 3.02 * eV, 3.10 * eV, 3.18 * eV, 3.26 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {438. * mm, 438. * mm, 413. * mm, 375. * mm, 263. * mm, 87.5 * mm, 11.5 * mm, 1.0 * mm, 1.0 * mm};
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_ABS,  Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 3.4);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 0.9 * ns);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 650. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 0.5);
  myMPT->AddConstProperty("SCINTILLATIONYIELD2", 0.5);

  mat->SetMaterialPropertiesTable(myMPT);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}

G4Material *MyMaterials::LYSO(double user_lightyield, double scaleFactor, double user_birks)
{
  double lightyield = (user_lightyield == -1) ? 40000 : user_lightyield;
  // Birks' constant is used to describe the non-linear light yield effect in scintillator materials
  double birks = (user_birks < 0) ? 0 : user_birks;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Lu = new G4Element("Lutetium", "Lu", z = 71., a = 174.97 * g / mole);
  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);

  G4Material *mat = new G4Material("LYSO", density = 7.1 * g / cm3, 3, kStateSolid);
  mat->AddElement(Lu, 2);
  mat->AddElement(Si, 1);
  mat->AddElement(O, 5);

  std::vector<G4double> PhotonEnergy_FAST =
      {1.77169 * eV, 1.77266 * eV, 1.77558 * eV, 1.77851 * eV, 1.78145 * eV, 1.78539 * eV, 1.79033 * eV, 1.7963 * eV, 1.80231 * eV, 1.80836 * eV,
       1.81445 * eV, 1.82058 * eV, 1.82882 * eV, 1.83401 * eV, 1.84553 * eV, 1.85293 * eV, 1.86147 * eV, 1.869 * eV, 1.87769 * eV, 1.89308 * eV,
       1.90536 * eV, 1.92007 * eV, 1.93039 * eV, 1.94901 * eV, 1.95846 * eV, 1.9668 * eV, 1.97884 * eV, 1.99102 * eV, 2.00088 * eV, 2.01209 * eV,
       2.02596 * eV, 2.03617 * eV, 2.04519 * eV, 2.0569 * eV, 2.06611 * eV, 2.0794 * eV, 2.09151 * eV, 2.10239 * eV, 2.112 * eV, 2.1231 * eV,
       2.13431 * eV, 2.14565 * eV, 2.15566 * eV, 2.16868 * eV, 2.18038 * eV, 2.19519 * eV, 2.21171 * eV, 2.2193 * eV, 2.23619 * eV, 2.23464 * eV,
       2.24395 * eV, 2.25806 * eV, 2.27234 * eV, 2.28358 * eV, 2.29493 * eV, 2.30475 * eV, 2.31631 * eV, 2.32463 * eV, 2.33134 * eV, 2.33809 * eV,
       2.34487 * eV, 2.35856 * eV, 2.36719 * eV, 2.37939 * eV, 2.38642 * eV, 2.40238 * eV, 2.41134 * eV, 2.424 * eV, 2.43312 * eV, 2.44047 * eV,
       2.44786 * eV, 2.46278 * eV, 2.47788 * eV, 2.48741 * eV, 2.49317 * eV, 2.49702 * eV, 2.50282 * eV, 2.50865 * eV, 2.5145 * eV, 2.52038 * eV,
       2.52432 * eV, 2.53223 * eV, 2.5362 * eV, 2.54619 * eV, 2.55424 * eV, 2.56031 * eV, 2.56437 * eV, 2.57049 * eV, 2.57663 * eV, 2.58487 * eV,
       2.59317 * eV, 2.59734 * eV, 2.60571 * eV, 2.61414 * eV, 2.61414 * eV, 2.61837 * eV, 2.62262 * eV, 2.62475 * eV, 2.62902 * eV, 2.63331 * eV,
       2.63545 * eV, 2.63976 * eV, 2.64191 * eV, 2.64841 * eV, 2.65493 * eV, 2.6593 * eV, 2.66149 * eV, 2.66588 * eV, 2.67914 * eV, 2.67914 * eV,
       2.68136 * eV, 2.68136 * eV, 2.68359 * eV, 2.68805 * eV, 2.68805 * eV, 2.68805 * eV, 2.69477 * eV, 2.69477 * eV, 2.69702 * eV, 2.70153 * eV,
       2.70605 * eV, 2.71286 * eV, 2.71742 * eV, 2.71971 * eV, 2.722 * eV, 2.722 * eV, 2.72429 * eV, 2.72889 * eV, 2.72889 * eV, 2.73351 * eV,
       2.73814 * eV, 2.74279 * eV, 2.74512 * eV, 2.74979 * eV, 2.75213 * eV, 2.75447 * eV, 2.75917 * eV, 2.75682 * eV, 2.76389 * eV, 2.76626 * eV,
       2.76389 * eV, 2.76626 * eV, 2.77338 * eV, 2.77576 * eV, 2.78533 * eV, 2.79255 * eV, 2.79738 * eV, 2.80223 * eV, 2.80466 * eV, 2.80709 * eV,
       2.80953 * eV, 2.80953 * eV, 2.81934 * eV, 2.8218 * eV, 2.82673 * eV, 2.83168 * eV, 2.84164 * eV, 2.84916 * eV, 2.85419 * eV, 2.8643 * eV,
       2.86684 * eV, 2.87449 * eV, 2.87705 * eV, 2.87961 * eV, 2.88475 * eV, 2.88733 * eV, 2.8925 * eV, 2.89509 * eV, 2.90028 * eV, 2.90549 * eV,
       2.90811 * eV, 2.91073 * eV, 2.91335 * eV, 2.91335 * eV, 2.91335 * eV, 2.91861 * eV, 2.92125 * eV, 2.92125 * eV, 2.92389 * eV, 2.92654 * eV,
       2.92654 * eV, 2.92919 * eV, 2.92919 * eV, 2.93185 * eV, 2.93451 * eV, 2.93717 * eV, 2.93985 * eV, 2.94252 * eV, 2.9452 * eV, 2.94789 * eV,
       2.94789 * eV, 2.94789 * eV, 2.95058 * eV, 2.95868 * eV, 2.96411 * eV, 2.96955 * eV, 2.97228 * eV, 2.97228 * eV, 2.96955 * eV, 2.97228 * eV,
       2.97502 * eV, 2.97776 * eV, 2.97502 * eV, 2.9805 * eV, 2.9805 * eV, 2.9805 * eV, 2.98601 * eV, 2.99154 * eV, 2.99431 * eV, 2.99431 * eV,
       2.99708 * eV, 2.99431 * eV, 2.99708 * eV, 3.00544 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.01385 * eV, 3.0223 * eV,
       3.02797 * eV, 3.03081 * eV, 3.02797 * eV, 3.03365 * eV, 3.03081 * eV, 3.03081 * eV, 3.0365 * eV, 3.03935 * eV, 3.04221 * eV, 3.04795 * eV,
       3.04795 * eV, 3.05083 * eV, 3.05371 * eV, 3.05949 * eV, 3.06239 * eV, 3.06529 * eV, 3.0682 * eV, 3.06529 * eV, 3.07112 * eV, 3.0682 * eV,
       3.07696 * eV, 3.08283 * eV, 3.0976 * eV, 3.09464 * eV, 3.09464 * eV, 3.10653 * eV, 3.11252 * eV, 3.11852 * eV, 3.12757 * eV, 3.13668 * eV,
       3.14583 * eV, 3.15813 * eV, 3.16741 * eV, 3.17675 * eV, 3.20828 * eV, 3.23719 * eV, 3.26664 * eV, 3.28656 * eV, 3.31351 * eV, 3.34783 * eV,
       3.38287 * eV};
  std::vector<G4double> FastComponent =
      {0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
       0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
       0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
       0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
       0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
       0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
       0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
       0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
       0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
       0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
       1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
       1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
       1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
       1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
       1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
       2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
       2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
       1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
       1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
       1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
       1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
       1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
       0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
       0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
       0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
       0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
       0.011691};

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 1.84 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.82, 1.82, 1.82};
  // std::vector<G4double> Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.00 * eV, 2.82 * eV, 2.88 * eV, 2.95 * eV, 3.02 * eV, 3.10 * eV, 3.18 * eV, 3.26 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {438. * mm, 438. * mm, 413. * mm, 375. * mm, 263. * mm, 87.5 * mm, 11.5 * mm, 1.0 * mm, 1.0 * mm};
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_ABS,  Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 3.4);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 40. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1);

  mat->SetMaterialPropertiesTable(myMPT);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}


G4Material *MyMaterials::YSO(double user_lightyield, double scaleFactor, double user_birks)
{
  double lightyield = (user_lightyield == -1) ? 30000 : user_lightyield;
  // Birks' constant is used to describe the non-linear light yield effect in scintillator materials
  double birks = (user_birks < 0) ? 0 : user_birks;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Y = new G4Element("Yttrium", "Y", z = 39., a = 88.9 * g / mole);
  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);

  G4Material *mat = new G4Material("YSO", density = 4.4 * g / cm3, 3, kStateSolid);
  mat->AddElement(Y, 2);
  mat->AddElement(Si, 1);
  mat->AddElement(O, 5);

  std::vector<G4double> PhotonEnergy_FAST =
      {1.77169 * eV, 1.77266 * eV, 1.77558 * eV, 1.77851 * eV, 1.78145 * eV, 1.78539 * eV, 1.79033 * eV, 1.7963 * eV, 1.80231 * eV, 1.80836 * eV,
       1.81445 * eV, 1.82058 * eV, 1.82882 * eV, 1.83401 * eV, 1.84553 * eV, 1.85293 * eV, 1.86147 * eV, 1.869 * eV, 1.87769 * eV, 1.89308 * eV,
       1.90536 * eV, 1.92007 * eV, 1.93039 * eV, 1.94901 * eV, 1.95846 * eV, 1.9668 * eV, 1.97884 * eV, 1.99102 * eV, 2.00088 * eV, 2.01209 * eV,
       2.02596 * eV, 2.03617 * eV, 2.04519 * eV, 2.0569 * eV, 2.06611 * eV, 2.0794 * eV, 2.09151 * eV, 2.10239 * eV, 2.112 * eV, 2.1231 * eV,
       2.13431 * eV, 2.14565 * eV, 2.15566 * eV, 2.16868 * eV, 2.18038 * eV, 2.19519 * eV, 2.21171 * eV, 2.2193 * eV, 2.23619 * eV, 2.23464 * eV,
       2.24395 * eV, 2.25806 * eV, 2.27234 * eV, 2.28358 * eV, 2.29493 * eV, 2.30475 * eV, 2.31631 * eV, 2.32463 * eV, 2.33134 * eV, 2.33809 * eV,
       2.34487 * eV, 2.35856 * eV, 2.36719 * eV, 2.37939 * eV, 2.38642 * eV, 2.40238 * eV, 2.41134 * eV, 2.424 * eV, 2.43312 * eV, 2.44047 * eV,
       2.44786 * eV, 2.46278 * eV, 2.47788 * eV, 2.48741 * eV, 2.49317 * eV, 2.49702 * eV, 2.50282 * eV, 2.50865 * eV, 2.5145 * eV, 2.52038 * eV,
       2.52432 * eV, 2.53223 * eV, 2.5362 * eV, 2.54619 * eV, 2.55424 * eV, 2.56031 * eV, 2.56437 * eV, 2.57049 * eV, 2.57663 * eV, 2.58487 * eV,
       2.59317 * eV, 2.59734 * eV, 2.60571 * eV, 2.61414 * eV, 2.61414 * eV, 2.61837 * eV, 2.62262 * eV, 2.62475 * eV, 2.62902 * eV, 2.63331 * eV,
       2.63545 * eV, 2.63976 * eV, 2.64191 * eV, 2.64841 * eV, 2.65493 * eV, 2.6593 * eV, 2.66149 * eV, 2.66588 * eV, 2.67914 * eV, 2.67914 * eV,
       2.68136 * eV, 2.68136 * eV, 2.68359 * eV, 2.68805 * eV, 2.68805 * eV, 2.68805 * eV, 2.69477 * eV, 2.69477 * eV, 2.69702 * eV, 2.70153 * eV,
       2.70605 * eV, 2.71286 * eV, 2.71742 * eV, 2.71971 * eV, 2.722 * eV, 2.722 * eV, 2.72429 * eV, 2.72889 * eV, 2.72889 * eV, 2.73351 * eV,
       2.73814 * eV, 2.74279 * eV, 2.74512 * eV, 2.74979 * eV, 2.75213 * eV, 2.75447 * eV, 2.75917 * eV, 2.75682 * eV, 2.76389 * eV, 2.76626 * eV,
       2.76389 * eV, 2.76626 * eV, 2.77338 * eV, 2.77576 * eV, 2.78533 * eV, 2.79255 * eV, 2.79738 * eV, 2.80223 * eV, 2.80466 * eV, 2.80709 * eV,
       2.80953 * eV, 2.80953 * eV, 2.81934 * eV, 2.8218 * eV, 2.82673 * eV, 2.83168 * eV, 2.84164 * eV, 2.84916 * eV, 2.85419 * eV, 2.8643 * eV,
       2.86684 * eV, 2.87449 * eV, 2.87705 * eV, 2.87961 * eV, 2.88475 * eV, 2.88733 * eV, 2.8925 * eV, 2.89509 * eV, 2.90028 * eV, 2.90549 * eV,
       2.90811 * eV, 2.91073 * eV, 2.91335 * eV, 2.91335 * eV, 2.91335 * eV, 2.91861 * eV, 2.92125 * eV, 2.92125 * eV, 2.92389 * eV, 2.92654 * eV,
       2.92654 * eV, 2.92919 * eV, 2.92919 * eV, 2.93185 * eV, 2.93451 * eV, 2.93717 * eV, 2.93985 * eV, 2.94252 * eV, 2.9452 * eV, 2.94789 * eV,
       2.94789 * eV, 2.94789 * eV, 2.95058 * eV, 2.95868 * eV, 2.96411 * eV, 2.96955 * eV, 2.97228 * eV, 2.97228 * eV, 2.96955 * eV, 2.97228 * eV,
       2.97502 * eV, 2.97776 * eV, 2.97502 * eV, 2.9805 * eV, 2.9805 * eV, 2.9805 * eV, 2.98601 * eV, 2.99154 * eV, 2.99431 * eV, 2.99431 * eV,
       2.99708 * eV, 2.99431 * eV, 2.99708 * eV, 3.00544 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.01385 * eV, 3.0223 * eV,
       3.02797 * eV, 3.03081 * eV, 3.02797 * eV, 3.03365 * eV, 3.03081 * eV, 3.03081 * eV, 3.0365 * eV, 3.03935 * eV, 3.04221 * eV, 3.04795 * eV,
       3.04795 * eV, 3.05083 * eV, 3.05371 * eV, 3.05949 * eV, 3.06239 * eV, 3.06529 * eV, 3.0682 * eV, 3.06529 * eV, 3.07112 * eV, 3.0682 * eV,
       3.07696 * eV, 3.08283 * eV, 3.0976 * eV, 3.09464 * eV, 3.09464 * eV, 3.10653 * eV, 3.11252 * eV, 3.11852 * eV, 3.12757 * eV, 3.13668 * eV,
       3.14583 * eV, 3.15813 * eV, 3.16741 * eV, 3.17675 * eV, 3.20828 * eV, 3.23719 * eV, 3.26664 * eV, 3.28656 * eV, 3.31351 * eV, 3.34783 * eV,
       3.38287 * eV};
  std::vector<G4double> FastComponent =
      {0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
       0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
       0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
       0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
       0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
       0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
       0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
       0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
       0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
       0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
       1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
       1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
       1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
       1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
       1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
       2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
       2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
       1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
       1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
       1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
       1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
       1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
       0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
       0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
       0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
       0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
       0.011691};

  std::vector<G4double> PhotonEnergy_RI =
      {1.0 * eV, 1.84 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.82, 1.82, 1.82};
  // std::vector<G4double> Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.00 * eV, 2.82 * eV, 2.88 * eV, 2.95 * eV, 3.02 * eV, 3.10 * eV, 3.18 * eV, 3.26 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {438. * mm, 438. * mm, 413. * mm, 375. * mm, 263. * mm, 87.5 * mm, 11.5 * mm, 1.0 * mm, 1.0 * mm};
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_ABS,  Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 3.4);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 60. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1);

  mat->SetMaterialPropertiesTable(myMPT);

  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}


G4Material *MyMaterials::LSO(double user_lightyield, double scaleFactor, double user_birks)
// !! Is this light yield correct?
{
  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Lu = new G4Element("Lutetium", "Lu", z = 71., a = 174.97 * g / mole);
  G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.09 * g / mole);

  G4Material *mat = new G4Material("LSO", density = 7.4 * g / cm3, 3);
  mat->AddElement(Lu, 2);
  mat->AddElement(Si, 1);
  mat->AddElement(O, 5);

  double standard_light_yield = 30000;
  double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  std::vector<G4double> PhotonEnergy_FAST =
      {1.83966 * eV, 1.84948 * eV, 1.86274 * eV, 1.87507 * eV, 1.88413 * eV, 1.90369 * eV, 1.91187 * eV, 1.92129 * eV, 1.92962 * eV, 1.93922 * eV,
       1.95258 * eV, 1.96365 * eV, 1.97986 * eV, 1.99124 * eV, 2.00533 * eV, 2.02618 * eV, 2.04747 * eV, 2.06101 * eV, 2.07472 * eV, 2.09424 * eV,
       2.11269 * eV, 2.12565 * eV, 2.14466 * eV, 2.16251 * eV, 2.17914 * eV, 2.19602 * eV, 2.21317 * eV, 2.22422 * eV, 2.24021 * eV, 2.25479 * eV,
       2.26462 * eV, 2.27785 * eV, 2.29462 * eV, 2.30821 * eV, 2.32024 * eV, 2.33588 * eV, 2.34643 * eV, 2.35529 * eV, 2.37322 * eV, 2.38594 * eV,
       2.3896 * eV, 2.39879 * eV, 2.40805 * eV, 2.41365 * eV, 2.4268 * eV, 2.44009 * eV, 2.45161 * eV, 2.46518 * eV, 2.47693 * eV, 2.48483 * eV,
       2.49477 * eV, 2.50479 * eV, 2.51692 * eV, 2.53123 * eV, 2.5457 * eV, 2.54986 * eV, 2.55613 * eV, 2.56033 * eV, 2.56665 * eV, 2.58796 * eV,
       2.59658 * eV, 2.60091 * eV, 2.60309 * eV, 2.60744 * eV, 2.614 * eV, 2.62059 * eV, 2.62943 * eV, 2.6361 * eV, 2.64057 * eV, 2.64729 * eV,
       2.65632 * eV, 2.66085 * eV, 2.6654 * eV, 2.66997 * eV, 2.67684 * eV, 2.67684 * eV, 2.68839 * eV, 2.69303 * eV, 2.70237 * eV, 2.70471 * eV,
       2.71177 * eV, 2.72124 * eV, 2.72362 * eV, 2.73077 * eV, 2.73077 * eV, 2.73317 * eV, 2.73797 * eV, 2.74279 * eV, 2.74762 * eV, 2.7549 * eV,
       2.7549 * eV, 2.75978 * eV, 2.75978 * eV, 2.76468 * eV, 2.76713 * eV, 2.77205 * eV, 2.77699 * eV, 2.77699 * eV, 2.77947 * eV, 2.78941 * eV,
       2.79692 * eV, 2.80195 * eV, 2.80699 * eV, 2.8146 * eV, 2.81714 * eV, 2.8248 * eV, 2.8325 * eV, 2.83507 * eV, 2.85063 * eV, 2.85847 * eV,
       2.86635 * eV, 2.86899 * eV, 2.87428 * eV, 2.87959 * eV, 2.88225 * eV, 2.89027 * eV, 2.89295 * eV, 2.89833 * eV, 2.90103 * eV, 2.90915 * eV,
       2.91186 * eV, 2.91731 * eV, 2.92278 * eV, 2.92278 * eV, 2.92553 * eV, 2.93103 * eV, 2.93103 * eV, 2.93103 * eV, 2.94487 * eV, 2.94487 * eV,
       2.94766 * eV, 2.95324 * eV, 2.95604 * eV, 2.95885 * eV, 2.95604 * eV, 2.96166 * eV, 2.96447 * eV, 2.97012 * eV, 2.96166 * eV, 2.97295 * eV,
       2.98434 * eV, 2.98434 * eV, 2.98148 * eV, 2.98434 * eV, 2.99006 * eV, 2.9872 * eV, 2.99006 * eV, 2.9872 * eV, 2.99006 * eV, 2.99869 * eV,
       3.00447 * eV, 3.00737 * eV, 3.0161 * eV, 3.01902 * eV, 3.0161 * eV, 3.0161 * eV, 3.01318 * eV, 3.01318 * eV, 3.02194 * eV, 3.02781 * eV,
       3.03666 * eV, 3.03666 * eV, 3.03666 * eV, 3.04556 * eV, 3.05152 * eV, 3.05152 * eV, 3.05451 * eV, 3.05451 * eV, 3.05451 * eV, 3.06051 * eV,
       3.05751 * eV, 3.07258 * eV, 3.07258 * eV, 3.07561 * eV, 3.08169 * eV, 3.09085 * eV, 3.08779 * eV, 3.09085 * eV, 3.09699 * eV, 3.10935 * eV,
       3.10625 * eV, 3.1218 * eV, 3.12807 * eV, 3.13121 * eV, 3.14067 * eV, 3.15657 * eV, 3.16941 * eV, 3.19213 * eV, 3.21849 * eV, 3.24529 * eV,
       3.27255 * eV, 3.28981 * eV};
  std::vector<G4double> FastComponent =
      {0.0121475, 0.0121475, 0.0151844, 0.0151844, 0.0151844, 0.0182213, 0.0182213, 0.0182213, 0.024295, 0.024295,
       0.0212581, 0.0212581, 0.0303688, 0.0303688, 0.0303688, 0.0425163, 0.0516269, 0.0607375, 0.0698482, 0.072885,
       0.0850325, 0.0941432, 0.106291, 0.127549, 0.130586, 0.142733, 0.163991, 0.179176, 0.19436, 0.212581,
       0.224729, 0.239913, 0.252061, 0.273319, 0.297614, 0.318872, 0.34013, 0.355315, 0.376573, 0.38872,
       0.413015, 0.4282, 0.440347, 0.458568, 0.47679, 0.507158, 0.531453, 0.567896, 0.595228, 0.628633,
       0.652928, 0.68026, 0.71974, 0.759219, 0.77744, 0.813883, 0.835141, 0.859436, 0.886768, 0.920174,
       0.956616, 0.990022, 1.00521, 1.01735, 1.04165, 1.06898, 1.09328, 1.11757, 1.15098, 1.17223,
       1.2026, 1.23297, 1.26334, 1.29067, 1.32104, 1.37874, 1.40304, 1.43341, 1.46074, 1.49414,
       1.52451, 1.56095, 1.60043, 1.63991, 1.67028, 1.69761, 1.72191, 1.7462, 1.77354, 1.81605,
       1.84946, 1.88286, 1.88286, 1.88894, 1.9102, 1.94056, 1.98308, 2.00434, 2.03167, 2.07419,
       2.10759, 2.13189, 2.15315, 2.16833, 2.17744, 2.19566, 2.20781, 2.20781, 2.21996, 2.21692,
       2.20477, 2.18959, 2.16833, 2.14403, 2.11367, 2.08026, 2.04685, 2.01649, 1.98308, 1.94056,
       1.90716, 1.87679, 1.84642, 1.80998, 1.77354, 1.73406, 1.70369, 1.66421, 1.60651, 1.53362,
       1.5154, 1.49111, 1.46985, 1.44252, 1.4243, 1.39696, 1.36356, 1.318, 1.26941, 1.21171,
       1.16616, 1.13275, 1.09935, 1.12972, 1.11453, 1.08416, 1.05683, 1.02343, 0.993059, 0.956616,
       0.929284, 0.895879, 0.87462, 0.835141, 0.801735, 0.77744, 0.747072, 0.704555, 0.67115, 0.640781,
       0.595228, 0.570933, 0.540564, 0.510195, 0.473753, 0.443384, 0.419089, 0.394794, 0.373536, 0.34013,
       0.318872, 0.276356, 0.252061, 0.203471, 0.185249, 0.163991, 0.142733, 0.127549, 0.112364, 0.0911063,
       0.072885, 0.0577007, 0.0425163, 0.0303688, 0.024295, 0.00911063, 0.00607375, 0.00607375, 0.00303688, 0.00303688,
       0.00911063, 0.00911063};

  std::vector<G4double> PhotonEnergy_RI =
      {0.0001 * eV, 1.0 * eV, 1.84 * eV, 6.26 * eV};
  std::vector<G4double> RefractiveIndex =
      {1.82, 1.82, 1.82, 1.82};
  // G4double Rayleigh[nEntries_RI] =
  //   { 138.*mm, 138.*mm, 138.*mm};

  std::vector<G4double> PhotonEnergy_ABS =
      {0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV};
  std::vector<G4double> Absorption =
      {1 * mm, 138. * mm, 138. * mm, 138. * mm};

  const G4int nEntries_SCY = 12;
  G4double ElectronEnergy_SCY[nEntries_SCY] =
      {0.000 * MeV, 0.015 * MeV, 0.020 * MeV, 0.030 * MeV,
       0.040 * MeV, 0.060 * MeV, 0.080 * MeV, 0.090 * MeV,
       0.105 * MeV, 0.300 * MeV, 0.500 * MeV, 1.000 * MeV};
  G4double ScintilYield[nEntries_SCY] =
      {0.10, 0.46, 0.60, 0.68,
       0.74, 0.80, 0.82, 0.84,
       0.87, 0.96, 0.98, 1.00};
  for (int i = 0; i < nEntries_SCY; i++)
    ScintilYield[i] = lightyield * MeV * ScintilYield[i] * ElectronEnergy_SCY[i];

  for (auto& value : Absorption)
  {
      value *= scaleFactor;
  }
  double birks = (user_birks < 0) ? 0 : user_birks; 

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  // myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_RI,   Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddProperty("ELECTRONSCINTILLATIONYIELD", ElectronEnergy_SCY, ScintilYield, nEntries_SCY);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 3.2);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 40. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

  mat->SetMaterialPropertiesTable(myMPT);
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks*mm/MeV);
  return mat;
}
G4Material *MyMaterials::PWO(double user_lightyield, double scaleFactor, double user_birks)
{
  G4double a, z, density;
  G4Element *Pb = new G4Element("Lead", "Pb", z = 82., a = 207.21 * g / mole);
  G4Element *W = new G4Element("Tungsten", "W", z = 74., a = 183.85 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("PWO", density = 8.28 * g / cm3, 3);
  mat->AddElement(Pb, 1);
  mat->AddElement(W, 1);
  mat->AddElement(O, 4);

  // !! is this lightyield true?
  double lightyield = (user_lightyield == -1) ? 100 : user_lightyield;

  // birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double birks = (user_birks < 0) ? 0 : user_birks;

  std::vector<G4double> PhotonEnergy_FAST =
      {1.7712 * eV, 1.77374 * eV, 1.77628 * eV, 1.77883 * eV, 1.78138 * eV, 1.78395 * eV, 1.78652 * eV, 1.78909 * eV, 1.79168 * eV, 1.79427 * eV,
       1.79687 * eV, 1.79948 * eV, 1.8021 * eV, 1.80472 * eV, 1.80735 * eV, 1.80999 * eV, 1.81263 * eV, 1.81529 * eV, 1.81795 * eV, 1.82062 * eV,
       1.8233 * eV, 1.82598 * eV, 1.82868 * eV, 1.83138 * eV, 1.83409 * eV, 1.8368 * eV, 1.83953 * eV, 1.84226 * eV, 1.845 * eV, 1.84775 * eV,
       1.85051 * eV, 1.85328 * eV, 1.85605 * eV, 1.85883 * eV, 1.86162 * eV, 1.86442 * eV, 1.86723 * eV, 1.87005 * eV, 1.87287 * eV, 1.87571 * eV,
       1.87855 * eV, 1.8814 * eV, 1.88426 * eV, 1.88713 * eV, 1.89 * eV, 1.89289 * eV, 1.89578 * eV, 1.89869 * eV, 1.9016 * eV, 1.90452 * eV,
       1.90745 * eV, 1.91039 * eV, 1.91334 * eV, 1.91629 * eV, 1.91926 * eV, 1.92224 * eV, 1.92522 * eV, 1.92821 * eV, 1.93122 * eV, 1.93423 * eV,
       1.93725 * eV, 1.94028 * eV, 1.94333 * eV, 1.94638 * eV, 1.94944 * eV, 1.95251 * eV, 1.95559 * eV, 1.95868 * eV, 1.96178 * eV, 1.96488 * eV,
       1.968 * eV, 1.97113 * eV, 1.97427 * eV, 1.97742 * eV, 1.98058 * eV, 1.98375 * eV, 1.98693 * eV, 1.99012 * eV, 1.99331 * eV, 1.99652 * eV,
       1.99974 * eV, 2.00298 * eV, 2.00622 * eV, 2.00947 * eV, 2.01273 * eV, 2.016 * eV, 2.01929 * eV, 2.02258 * eV, 2.02589 * eV, 2.0292 * eV,
       2.03253 * eV, 2.03587 * eV, 2.03921 * eV, 2.04257 * eV, 2.04594 * eV, 2.04933 * eV, 2.05272 * eV, 2.05612 * eV, 2.05954 * eV, 2.06296 * eV,
       2.0664 * eV, 2.06985 * eV, 2.07331 * eV, 2.07679 * eV, 2.08027 * eV, 2.08377 * eV, 2.08728 * eV, 2.0908 * eV, 2.09433 * eV, 2.09787 * eV,
       2.10143 * eV, 2.10499 * eV, 2.10857 * eV, 2.11217 * eV, 2.11577 * eV, 2.11939 * eV, 2.12302 * eV, 2.12666 * eV, 2.13031 * eV, 2.13398 * eV,
       2.13766 * eV, 2.14135 * eV, 2.14506 * eV, 2.14877 * eV, 2.1525 * eV, 2.15625 * eV, 2.16 * eV, 2.16377 * eV, 2.16756 * eV, 2.17135 * eV,
       2.17516 * eV, 2.17898 * eV, 2.18282 * eV, 2.18667 * eV, 2.19053 * eV, 2.19441 * eV, 2.1983 * eV, 2.20221 * eV, 2.20612 * eV, 2.21006 * eV,
       2.214 * eV, 2.21796 * eV, 2.22194 * eV, 2.22593 * eV, 2.22993 * eV, 2.23395 * eV, 2.23798 * eV, 2.24203 * eV, 2.24609 * eV, 2.25017 * eV,
       2.25426 * eV, 2.25836 * eV, 2.26249 * eV, 2.26662 * eV, 2.27077 * eV, 2.27494 * eV, 2.27912 * eV, 2.28332 * eV, 2.28753 * eV, 2.29176 * eV,
       2.296 * eV, 2.30026 * eV, 2.30454 * eV, 2.30883 * eV, 2.31314 * eV, 2.31746 * eV, 2.3218 * eV, 2.32616 * eV, 2.33053 * eV, 2.33492 * eV,
       2.33932 * eV, 2.34375 * eV, 2.34819 * eV, 2.35264 * eV, 2.35711 * eV, 2.3616 * eV, 2.36611 * eV, 2.37063 * eV, 2.37518 * eV, 2.37973 * eV,
       2.38431 * eV, 2.38891 * eV, 2.39352 * eV, 2.39815 * eV, 2.40279 * eV, 2.40746 * eV, 2.41214 * eV, 2.41685 * eV, 2.42157 * eV, 2.42631 * eV,
       2.43106 * eV, 2.43584 * eV, 2.44063 * eV, 2.44545 * eV, 2.45028 * eV, 2.45513 * eV, 2.46 * eV, 2.46489 * eV, 2.4698 * eV, 2.47473 * eV,
       2.47968 * eV, 2.48465 * eV, 2.48964 * eV, 2.49465 * eV, 2.49968 * eV, 2.50473 * eV, 2.5098 * eV, 2.51489 * eV, 2.52 * eV, 2.52514 * eV,
       2.53029 * eV, 2.53546 * eV, 2.54066 * eV, 2.54588 * eV, 2.55111 * eV, 2.55637 * eV, 2.56166 * eV, 2.56696 * eV, 2.57229 * eV, 2.57763 * eV,
       2.583 * eV, 2.5884 * eV, 2.59381 * eV, 2.59925 * eV, 2.60471 * eV, 2.61019 * eV, 2.6157 * eV, 2.62123 * eV, 2.62678 * eV, 2.63236 * eV,
       2.63796 * eV, 2.64359 * eV, 2.64923 * eV, 2.65491 * eV, 2.6606 * eV, 2.66633 * eV, 2.67207 * eV, 2.67784 * eV, 2.68364 * eV, 2.68946 * eV,
       2.69531 * eV, 2.70118 * eV, 2.70708 * eV, 2.713 * eV, 2.71895 * eV, 2.72493 * eV, 2.73093 * eV, 2.73696 * eV, 2.74301 * eV, 2.7491 * eV,
       2.7552 * eV, 2.76134 * eV, 2.7675 * eV, 2.7737 * eV, 2.77991 * eV, 2.78616 * eV, 2.79244 * eV, 2.79874 * eV, 2.80507 * eV, 2.81143 * eV,
       2.81782 * eV, 2.82424 * eV, 2.83069 * eV, 2.83717 * eV, 2.84367 * eV, 2.85021 * eV, 2.85678 * eV, 2.86338 * eV, 2.87 * eV, 2.87666 * eV,
       2.88335 * eV, 2.89007 * eV, 2.89683 * eV, 2.90361 * eV, 2.91043 * eV, 2.91727 * eV, 2.92416 * eV, 2.93107 * eV, 2.93801 * eV, 2.94499 * eV,
       2.952 * eV, 2.95905 * eV, 2.96613 * eV, 2.97324 * eV, 2.98039 * eV, 2.98757 * eV, 2.99479 * eV, 3.00204 * eV, 3.00932 * eV, 3.01665 * eV,
       3.024 * eV, 3.0314 * eV, 3.03883 * eV, 3.04629 * eV, 3.0538 * eV, 3.06134 * eV, 3.06892 * eV, 3.07653 * eV, 3.08418 * eV, 3.09187 * eV,
       3.0996 * eV, 3.10737 * eV, 3.11518 * eV, 3.12303 * eV, 3.13091 * eV, 3.13884 * eV, 3.14681 * eV, 3.15481 * eV, 3.16286 * eV, 3.17095 * eV,
       3.17908 * eV, 3.18725 * eV, 3.19547 * eV, 3.20373 * eV, 3.21203 * eV, 3.22037 * eV, 3.22875 * eV, 3.23719 * eV, 3.24566 * eV, 3.25418 * eV,
       3.26274 * eV, 3.27135 * eV, 3.28 * eV, 3.28871 * eV, 3.29745 * eV, 3.30624 * eV, 3.31509 * eV, 3.32397 * eV, 3.33291 * eV, 3.34189 * eV,
       3.35092 * eV, 3.36001 * eV, 3.36914 * eV, 3.37832 * eV, 3.38755 * eV, 3.39683 * eV, 3.40616 * eV, 3.41554 * eV, 3.42498 * eV, 3.43447 * eV,
       3.44401 * eV, 3.4536 * eV, 3.46325 * eV, 3.47295 * eV, 3.4827 * eV, 3.49251 * eV, 3.50238 * eV, 3.5123 * eV, 3.52228 * eV, 3.53231 * eV,
       3.54241 * eV, 3.55256 * eV, 3.56276 * eV, 3.57303 * eV, 3.58336 * eV, 3.59374 * eV, 3.60419 * eV, 3.6147 * eV, 3.62527 * eV, 3.6359 * eV,
       3.64659 * eV, 3.65735 * eV, 3.66817 * eV, 3.67906 * eV, 3.69001 * eV, 3.70102 * eV, 3.7121 * eV, 3.72325 * eV, 3.73446 * eV, 3.74575 * eV,
       3.7571 * eV, 3.76852 * eV, 3.78001 * eV, 3.79157 * eV, 3.8032 * eV, 3.8149 * eV, 3.82667 * eV, 3.83852 * eV, 3.85044 * eV, 3.86244 * eV,
       3.87451 * eV, 3.88665 * eV, 3.89887 * eV, 3.91117 * eV, 3.92355 * eV, 3.93601 * eV, 3.94854 * eV, 3.96116 * eV, 3.97385 * eV, 3.98663 * eV,
       3.99949 * eV, 4.01243 * eV, 4.02546 * eV, 4.03857 * eV, 4.05177 * eV, 4.06506 * eV, 4.07843 * eV, 4.09189 * eV, 4.10544 * eV, 4.11908 * eV,
       4.13281 * eV, 4.14663 * eV, 4.16054 * eV, 4.17455 * eV, 4.18865 * eV, 4.20285 * eV, 4.21715 * eV, 4.23154 * eV, 4.24603 * eV, 4.26062 * eV,
       4.27532 * eV, 4.29011 * eV, 4.30501 * eV, 4.32001 * eV, 4.33511 * eV, 4.35032 * eV, 4.36564 * eV, 4.38107 * eV, 4.3966 * eV, 4.41225 * eV,
       4.42801 * eV, 4.44388 * eV, 4.45986 * eV, 4.47596 * eV, 4.49218 * eV, 4.50852 * eV, 4.52497 * eV, 4.54155 * eV, 4.55824 * eV, 4.57506 * eV,
       4.59201 * eV, 4.60908 * eV, 4.62628 * eV, 4.6436 * eV, 4.66106 * eV, 4.67865 * eV, 4.69637 * eV, 4.71423 * eV, 4.73222 * eV, 4.75035 * eV,
       4.76862 * eV, 4.78703 * eV, 4.80559 * eV, 4.82429 * eV, 4.84313 * eV, 4.86212 * eV, 4.88127 * eV, 4.90056 * eV, 4.92001 * eV, 4.93961 * eV,
       4.95937 * eV, 4.97928 * eV, 4.99936 * eV, 5.0196 * eV, 5.04001 * eV, 5.06058 * eV, 5.08132 * eV, 5.10223 * eV, 5.12331 * eV, 5.14457 * eV,
       5.16601 * eV, 5.18762 * eV, 5.20942 * eV, 5.2314 * eV, 5.25357 * eV, 5.27592 * eV, 5.29847 * eV, 5.32121 * eV, 5.34415 * eV, 5.36728 * eV,
       5.39062 * eV, 5.41416 * eV, 5.4379 * eV, 5.46186 * eV, 5.48603 * eV, 5.51041 * eV, 5.53501 * eV, 5.55983 * eV, 5.58487 * eV, 5.61014 * eV,
       5.63564 * eV, 5.66138 * eV, 5.68735 * eV, 5.71356 * eV, 5.74001 * eV, 5.76671 * eV, 5.79365 * eV, 5.82085 * eV, 5.84831 * eV, 5.87603 * eV,
       5.90401 * eV, 5.93226 * eV, 5.96078 * eV, 5.98957 * eV, 6.01865 * eV, 6.04801 * eV, 6.07766 * eV, 6.1076 * eV, 6.13783 * eV, 6.16837 * eV,
       6.19921 * eV};
  std::vector<G4double> FastComponent =
      {5.48303e-45, 1.10277e-44, 2.21239e-44, 4.42745e-44, 8.83811e-44, 1.75987e-43, 3.49554e-43, 6.92569e-43, 1.36876e-42, 2.69838e-42,
       5.30634e-42, 1.04088e-41, 2.03667e-41, 3.97517e-41, 7.73935e-41, 1.50303e-40, 2.91169e-40, 5.62647e-40, 1.08453e-39, 2.08527e-39,
       3.99941e-39, 7.65147e-39, 1.46018e-38, 2.77962e-38, 5.27808e-38, 9.99728e-38, 1.88887e-37, 3.55988e-37, 6.69243e-37, 1.25501e-36,
       2.3476e-36, 4.38041e-36, 8.15305e-36, 1.5137e-35, 2.80333e-35, 5.17872e-35, 9.543e-35, 1.75413e-34, 3.21627e-34, 5.88244e-34,
       1.07319e-33, 1.95304e-33, 3.54535e-33, 6.4198e-33, 1.15957e-32, 2.08924e-32, 3.75486e-32, 6.73153e-32, 1.20378e-31, 2.14731e-31,
       3.82083e-31, 6.78163e-31, 1.20067e-30, 2.12046e-30, 3.7355e-30, 6.56421e-30, 1.15062e-29, 2.01183e-29, 3.50888e-29, 6.10463e-29,
       1.05941e-28, 1.83393e-28, 3.16677e-28, 5.45461e-28, 9.37186e-28, 1.60621e-27, 2.74595e-27, 4.68271e-27, 7.96556e-27, 1.3516e-26,
       2.28769e-26, 3.86241e-26, 6.50481e-26, 1.09276e-25, 1.83117e-25, 3.06089e-25, 5.10365e-25, 8.48845e-25, 1.40828e-24, 2.33059e-24,
       3.8473e-24, 6.3352e-24, 1.04059e-23, 1.70495e-23, 2.7865e-23, 4.54277e-23, 7.38748e-23, 1.19836e-22, 1.93906e-22, 3.12974e-22,
       5.03897e-22, 8.09261e-22, 1.29643e-21, 2.07169e-21, 3.30229e-21, 5.25072e-21, 8.32794e-21, 1.31756e-20, 2.0793e-20, 3.27324e-20,
       5.13989e-20, 8.05088e-20, 1.2579e-19, 1.96049e-19, 3.04788e-19, 4.72655e-19, 7.31148e-19, 1.12819e-18, 1.73648e-18, 2.66608e-18,
       4.08312e-18, 6.2377e-18, 9.50541e-18, 1.44488e-17, 2.19082e-17, 3.31357e-17, 4.99919e-17, 7.52346e-17, 1.1294e-16, 1.6912e-16,
       2.52614e-16, 3.76384e-16, 5.59398e-16, 8.29324e-16, 1.22643e-15, 1.80915e-15, 2.66207e-15, 3.90734e-15, 5.72078e-15, 8.35496e-15,
       1.21716e-14, 1.76875e-14, 2.56388e-14, 3.70718e-14, 5.34692e-14, 7.69269e-14, 1.10399e-13, 1.58041e-13, 2.25677e-13, 3.21454e-13,
       4.56736e-13, 6.4733e-13, 9.15166e-13, 1.29059e-12, 1.81548e-12, 2.54747e-12, 3.56566e-12, 4.97836e-12, 6.9334e-12, 9.63209e-12,
       1.33478e-11, 1.84507e-11, 2.54407e-11, 3.49913e-11, 4.80072e-11, 6.57001e-11, 8.96892e-11, 1.22132e-10, 1.65894e-10, 2.24775e-10,
       3.03794e-10, 4.09567e-10, 5.50788e-10, 7.38854e-10, 9.8866e-10, 1.31962e-09, 1.75698e-09, 2.33344e-09, 3.09131e-09, 4.0851e-09,
       5.38488e-09, 7.0805e-09, 9.28681e-09, 1.21502e-08, 1.58567e-08, 2.06424e-08, 2.68052e-08, 3.4721e-08, 4.48622e-08, 5.78206e-08,
       7.4336e-08, 9.533e-08, 1.21948e-07, 1.55609e-07, 1.98065e-07, 2.51475e-07, 3.18491e-07, 4.02359e-07, 5.07043e-07, 6.37367e-07,
       7.99187e-07, 9.9959e-07, 1.24712e-06, 1.55207e-06, 1.92676e-06, 2.38593e-06, 2.94715e-06, 3.6313e-06, 4.46308e-06, 5.4717e-06,
       6.69151e-06, 8.16282e-06, 9.93277e-06, 1.20563e-05, 1.45973e-05, 1.76298e-05, 2.1239e-05, 2.55232e-05, 3.05951e-05, 3.65832e-05,
       4.36341e-05, 5.19141e-05, 6.1611e-05, 7.29365e-05, 8.61284e-05, 0.0001015, 0.0001192, 0.0001397, 0.0001633, 0.0001905,
       0.0002216, 0.0002571, 0.0002976, 0.0003436, 0.0003958, 0.0004547, 0.000521, 0.0005956, 0.0006791, 0.0007725,
       0.0008764, 0.0009919, 0.0011197, 0.0012609, 0.0014164, 0.001587, 0.0017737, 0.0019775, 0.0021992, 0.0024396,
       0.0026995, 0.0029797, 0.0032808, 0.0036032, 0.0039475, 0.0043139, 0.0047025, 0.0051132, 0.005546, 0.0060005,
       0.0064759, 0.0069715, 0.0074864, 0.0080192, 0.0085684, 0.0091325, 0.0097093, 0.0102968, 0.0108926, 0.0114941,
       0.0120985, 0.012703, 0.0133043, 0.0138992, 0.0144846, 0.0150569, 0.0156127, 0.0161486, 0.0166612, 0.0171472,
       0.0176033, 0.0180263, 0.0184135, 0.018762, 0.0190694, 0.0193334, 0.0195521, 0.019724, 0.0198476, 0.0199222,
       0.0199471, 0.0199222, 0.0198476, 0.019724, 0.0195521, 0.0193334, 0.0190694, 0.018762, 0.0184135, 0.0180263,
       0.0176033, 0.0171472, 0.0166612, 0.0161486, 0.0156127, 0.0150569, 0.0144846, 0.0138992, 0.0133043, 0.012703,
       0.0120985, 0.0114941, 0.0108926, 0.0102968, 0.0097093, 0.0091325, 0.0085684, 0.0080192, 0.0074864, 0.0069715,
       0.0064759, 0.0060005, 0.005546, 0.0051132, 0.0047025, 0.0043139, 0.0039475, 0.0036032, 0.0032808, 0.0029797,
       0.0026995, 0.0024396, 0.0021992, 0.0019775, 0.0017737, 0.001587, 0.0014164, 0.0012609, 0.0011197, 0.0009919,
       0.0008764, 0.0007725, 0.0006791, 0.0005956, 0.000521, 0.0004547, 0.0003958, 0.0003436, 0.0002976, 0.0002571,
       0.0002216, 0.0001905, 0.0001633, 0.0001397, 0.0001192, 0.0001015, 8.61284e-05, 7.29365e-05, 6.1611e-05, 5.19141e-05,
       4.36341e-05, 3.65832e-05, 3.05951e-05, 2.55232e-05, 2.1239e-05, 1.76298e-05, 1.45973e-05, 1.20563e-05, 9.93277e-06, 8.16282e-06,
       6.69151e-06, 5.4717e-06, 4.46308e-06, 3.6313e-06, 2.94715e-06, 2.38593e-06, 1.92676e-06, 1.55207e-06, 1.24712e-06, 9.9959e-07,
       7.99187e-07, 6.37367e-07, 5.07043e-07, 4.02359e-07, 3.18491e-07, 2.51475e-07, 1.98065e-07, 1.55609e-07, 1.21948e-07, 9.533e-08,
       7.4336e-08, 5.78206e-08, 4.48622e-08, 3.4721e-08, 2.68052e-08, 2.06424e-08, 1.58567e-08, 1.21502e-08, 9.28681e-09, 7.0805e-09,
       5.38488e-09, 4.0851e-09, 3.09131e-09, 2.33344e-09, 1.75698e-09, 1.31962e-09, 9.8866e-10, 7.38854e-10, 5.50788e-10, 4.09567e-10,
       3.03794e-10, 2.24775e-10, 1.65894e-10, 1.22132e-10, 8.96892e-11, 6.57001e-11, 4.80072e-11, 3.49913e-11, 2.54407e-11, 1.84507e-11,
       1.33478e-11, 9.63209e-12, 6.9334e-12, 4.97836e-12, 3.56566e-12, 2.54747e-12, 1.81548e-12, 1.29059e-12, 9.15166e-13, 6.4733e-13,
       4.56736e-13, 3.21454e-13, 2.25677e-13, 1.58041e-13, 1.10399e-13, 7.69269e-14, 5.34692e-14, 3.70718e-14, 2.56388e-14, 1.76875e-14,
       1.21716e-14, 8.35496e-15, 5.72078e-15, 3.90734e-15, 2.66207e-15, 1.80915e-15, 1.22643e-15, 8.29324e-16, 5.59398e-16, 3.76384e-16,
       2.52614e-16, 1.6912e-16, 1.1294e-16, 7.52346e-17, 4.99919e-17, 3.31357e-17, 2.19082e-17, 1.44488e-17, 9.50541e-18, 6.2377e-18,
       4.08312e-18, 2.66608e-18, 1.73648e-18, 1.12819e-18, 7.31148e-19, 4.72655e-19, 3.04788e-19, 1.96049e-19, 1.2579e-19, 8.05088e-20,
       5.13989e-20, 3.27324e-20, 2.0793e-20, 1.31756e-20, 8.32794e-21, 5.25072e-21, 3.30229e-21, 2.07169e-21, 1.29643e-21, 8.09261e-22,
       5.03897e-22, 3.12974e-22, 1.93906e-22, 1.19836e-22, 7.38748e-23, 4.54277e-23, 2.7865e-23, 1.70495e-23, 1.04059e-23, 6.3352e-24,
       3.8473e-24, 2.33059e-24, 1.40828e-24, 8.48845e-25, 5.10365e-25, 3.06089e-25, 1.83117e-25, 1.09276e-25, 6.50481e-26, 3.86241e-26,
       2.28769e-26, 1.3516e-26, 7.96556e-27, 4.68271e-27, 2.74595e-27, 1.60621e-27, 9.37186e-28, 5.45461e-28, 3.16677e-28, 1.83393e-28,
       1.05941e-28};

  G4double PbWO_indexZero = 1.5861;
  G4double PbWO_nVec[1] = {1.1062};
  G4double PbWO_lVec[1] = {270.63};
  int sizeVect = sizeof(PbWO_nVec) / sizeof(*PbWO_nVec);

  std::vector<G4double> PhotonEnergy_RI =
      {0.0001 * eV, 1.0 * eV, 1.84 * eV, 2.952 * eV, 4.08 * eV};
  std::vector<G4double> RefractiveIndex =
      {CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[0])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[1])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[2])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[3])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[4]))};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.25237 * eV, 1.26514 * eV, 1.27819 * eV, 1.2915 * eV, 1.3051 * eV, 1.31898 * eV, 1.33316 * eV, 1.34765 * eV, 1.36246 * eV, 1.3776 * eV,
       1.39308 * eV, 1.40891 * eV, 1.42511 * eV, 1.44168 * eV, 1.45864 * eV, 1.476 * eV, 1.49379 * eV, 1.512 * eV, 1.53067 * eV, 1.5498 * eV,
       1.56942 * eV, 1.58954 * eV, 1.61018 * eV, 1.63137 * eV, 1.65312 * eV, 1.67546 * eV, 1.69841 * eV, 1.722 * eV, 1.74626 * eV, 1.7712 * eV,
       1.79687 * eV, 1.8233 * eV, 1.85051 * eV, 1.87855 * eV, 1.90745 * eV, 1.93725 * eV, 1.968 * eV, 1.99974 * eV, 2.03253 * eV, 2.0664 * eV,
       2.10143 * eV, 2.13766 * eV, 2.17516 * eV, 2.214 * eV, 2.25426 * eV, 2.296 * eV, 2.33932 * eV, 2.38431 * eV, 2.43106 * eV, 2.47968 * eV,
       2.53029 * eV, 2.583 * eV, 2.63796 * eV, 2.69531 * eV, 2.7552 * eV, 2.81782 * eV, 2.88335 * eV, 2.952 * eV, 3.024 * eV, 3.0996 * eV,
       3.17908 * eV, 3.26274 * eV, 3.35092 * eV, 3.44401 * eV, 3.54241 * eV, 3.64659 * eV, 3.7571 * eV, 3.87451 * eV, 3.99949 * eV, 4.13281 * eV};
  std::vector<G4double> Absorption =
      {3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm,
       3105 * mm, 2745 * mm, 2460 * mm, 2230 * mm, 2039 * mm, 1877 * mm, 1859 * mm, 1826 * mm, 1764 * mm, 1760 * mm,
       1664 * mm, 1585 * mm, 1471 * mm, 1376 * mm, 1272 * mm, 1187 * mm, 1114 * mm, 1046 * mm, 993.2 * mm, 942.9 * mm,
       898.8 * mm, 856.9 * mm, 821.7 * mm, 794.2 * mm, 767.7 * mm, 746.5 * mm, 725.6 * mm, 710.7 * mm, 695.3 * mm, 686.2 * mm,
       674.8 * mm, 663.5 * mm, 648.3 * mm, 633.4 * mm, 622.3 * mm, 607.8 * mm, 590.9 * mm, 568.9 * mm, 541.4 * mm, 502.9 * mm,
       467 * mm, 430.2 * mm, 390.1 * mm, 345.3 * mm, 298.9 * mm, 256.7 * mm, 219.8 * mm, 185.4 * mm, 150.9 * mm, 116.4 * mm,
       84.8 * mm, 59.4 * mm, 41.1 * mm, 27.5 * mm, 24.2 * mm, 24.2 * mm, 24.3 * mm, 24.3 * mm, 24.4 * mm, 24.6 * mm};

  // scaleFactor = 1.0;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 3.2);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 40. * ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1);

  mat->SetMaterialPropertiesTable(myMPT);
  // Set the Birks Constant for the Polystyrene scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}

G4Material *MyMaterials::CWO(double user_lightyield, double scaleFactor, double user_birks)
{
  G4double a, z, density;
  G4Element *Cd = new G4Element("Cadmium", "Cd", z = 48., a = 112.4 * g / mole);
  G4Element *W = new G4Element("Tungsten", "W", z = 74., a = 183.85 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  G4Material *mat = new G4Material("CWO", density = 7.9 * g / cm3, 3);
  mat->AddElement(Cd, 1);
  mat->AddElement(W, 1);
  mat->AddElement(O, 4);

  // !! is this lightyield true?
  double lightyield = (user_lightyield == -1) ? 13000 : user_lightyield;

  // birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double birks = (user_birks < 0) ? 0 : user_birks;

  std::vector<G4double> PhotonEnergy_FAST =
      {1.7712 * eV, 1.77374 * eV, 1.77628 * eV, 1.77883 * eV, 1.78138 * eV, 1.78395 * eV, 1.78652 * eV, 1.78909 * eV, 1.79168 * eV, 1.79427 * eV,
       1.79687 * eV, 1.79948 * eV, 1.8021 * eV, 1.80472 * eV, 1.80735 * eV, 1.80999 * eV, 1.81263 * eV, 1.81529 * eV, 1.81795 * eV, 1.82062 * eV,
       1.8233 * eV, 1.82598 * eV, 1.82868 * eV, 1.83138 * eV, 1.83409 * eV, 1.8368 * eV, 1.83953 * eV, 1.84226 * eV, 1.845 * eV, 1.84775 * eV,
       1.85051 * eV, 1.85328 * eV, 1.85605 * eV, 1.85883 * eV, 1.86162 * eV, 1.86442 * eV, 1.86723 * eV, 1.87005 * eV, 1.87287 * eV, 1.87571 * eV,
       1.87855 * eV, 1.8814 * eV, 1.88426 * eV, 1.88713 * eV, 1.89 * eV, 1.89289 * eV, 1.89578 * eV, 1.89869 * eV, 1.9016 * eV, 1.90452 * eV,
       1.90745 * eV, 1.91039 * eV, 1.91334 * eV, 1.91629 * eV, 1.91926 * eV, 1.92224 * eV, 1.92522 * eV, 1.92821 * eV, 1.93122 * eV, 1.93423 * eV,
       1.93725 * eV, 1.94028 * eV, 1.94333 * eV, 1.94638 * eV, 1.94944 * eV, 1.95251 * eV, 1.95559 * eV, 1.95868 * eV, 1.96178 * eV, 1.96488 * eV,
       1.968 * eV, 1.97113 * eV, 1.97427 * eV, 1.97742 * eV, 1.98058 * eV, 1.98375 * eV, 1.98693 * eV, 1.99012 * eV, 1.99331 * eV, 1.99652 * eV,
       1.99974 * eV, 2.00298 * eV, 2.00622 * eV, 2.00947 * eV, 2.01273 * eV, 2.016 * eV, 2.01929 * eV, 2.02258 * eV, 2.02589 * eV, 2.0292 * eV,
       2.03253 * eV, 2.03587 * eV, 2.03921 * eV, 2.04257 * eV, 2.04594 * eV, 2.04933 * eV, 2.05272 * eV, 2.05612 * eV, 2.05954 * eV, 2.06296 * eV,
       2.0664 * eV, 2.06985 * eV, 2.07331 * eV, 2.07679 * eV, 2.08027 * eV, 2.08377 * eV, 2.08728 * eV, 2.0908 * eV, 2.09433 * eV, 2.09787 * eV,
       2.10143 * eV, 2.10499 * eV, 2.10857 * eV, 2.11217 * eV, 2.11577 * eV, 2.11939 * eV, 2.12302 * eV, 2.12666 * eV, 2.13031 * eV, 2.13398 * eV,
       2.13766 * eV, 2.14135 * eV, 2.14506 * eV, 2.14877 * eV, 2.1525 * eV, 2.15625 * eV, 2.16 * eV, 2.16377 * eV, 2.16756 * eV, 2.17135 * eV,
       2.17516 * eV, 2.17898 * eV, 2.18282 * eV, 2.18667 * eV, 2.19053 * eV, 2.19441 * eV, 2.1983 * eV, 2.20221 * eV, 2.20612 * eV, 2.21006 * eV,
       2.214 * eV, 2.21796 * eV, 2.22194 * eV, 2.22593 * eV, 2.22993 * eV, 2.23395 * eV, 2.23798 * eV, 2.24203 * eV, 2.24609 * eV, 2.25017 * eV,
       2.25426 * eV, 2.25836 * eV, 2.26249 * eV, 2.26662 * eV, 2.27077 * eV, 2.27494 * eV, 2.27912 * eV, 2.28332 * eV, 2.28753 * eV, 2.29176 * eV,
       2.296 * eV, 2.30026 * eV, 2.30454 * eV, 2.30883 * eV, 2.31314 * eV, 2.31746 * eV, 2.3218 * eV, 2.32616 * eV, 2.33053 * eV, 2.33492 * eV,
       2.33932 * eV, 2.34375 * eV, 2.34819 * eV, 2.35264 * eV, 2.35711 * eV, 2.3616 * eV, 2.36611 * eV, 2.37063 * eV, 2.37518 * eV, 2.37973 * eV,
       2.38431 * eV, 2.38891 * eV, 2.39352 * eV, 2.39815 * eV, 2.40279 * eV, 2.40746 * eV, 2.41214 * eV, 2.41685 * eV, 2.42157 * eV, 2.42631 * eV,
       2.43106 * eV, 2.43584 * eV, 2.44063 * eV, 2.44545 * eV, 2.45028 * eV, 2.45513 * eV, 2.46 * eV, 2.46489 * eV, 2.4698 * eV, 2.47473 * eV,
       2.47968 * eV, 2.48465 * eV, 2.48964 * eV, 2.49465 * eV, 2.49968 * eV, 2.50473 * eV, 2.5098 * eV, 2.51489 * eV, 2.52 * eV, 2.52514 * eV,
       2.53029 * eV, 2.53546 * eV, 2.54066 * eV, 2.54588 * eV, 2.55111 * eV, 2.55637 * eV, 2.56166 * eV, 2.56696 * eV, 2.57229 * eV, 2.57763 * eV,
       2.583 * eV, 2.5884 * eV, 2.59381 * eV, 2.59925 * eV, 2.60471 * eV, 2.61019 * eV, 2.6157 * eV, 2.62123 * eV, 2.62678 * eV, 2.63236 * eV,
       2.63796 * eV, 2.64359 * eV, 2.64923 * eV, 2.65491 * eV, 2.6606 * eV, 2.66633 * eV, 2.67207 * eV, 2.67784 * eV, 2.68364 * eV, 2.68946 * eV,
       2.69531 * eV, 2.70118 * eV, 2.70708 * eV, 2.713 * eV, 2.71895 * eV, 2.72493 * eV, 2.73093 * eV, 2.73696 * eV, 2.74301 * eV, 2.7491 * eV,
       2.7552 * eV, 2.76134 * eV, 2.7675 * eV, 2.7737 * eV, 2.77991 * eV, 2.78616 * eV, 2.79244 * eV, 2.79874 * eV, 2.80507 * eV, 2.81143 * eV,
       2.81782 * eV, 2.82424 * eV, 2.83069 * eV, 2.83717 * eV, 2.84367 * eV, 2.85021 * eV, 2.85678 * eV, 2.86338 * eV, 2.87 * eV, 2.87666 * eV,
       2.88335 * eV, 2.89007 * eV, 2.89683 * eV, 2.90361 * eV, 2.91043 * eV, 2.91727 * eV, 2.92416 * eV, 2.93107 * eV, 2.93801 * eV, 2.94499 * eV,
       2.952 * eV, 2.95905 * eV, 2.96613 * eV, 2.97324 * eV, 2.98039 * eV, 2.98757 * eV, 2.99479 * eV, 3.00204 * eV, 3.00932 * eV, 3.01665 * eV,
       3.024 * eV, 3.0314 * eV, 3.03883 * eV, 3.04629 * eV, 3.0538 * eV, 3.06134 * eV, 3.06892 * eV, 3.07653 * eV, 3.08418 * eV, 3.09187 * eV,
       3.0996 * eV, 3.10737 * eV, 3.11518 * eV, 3.12303 * eV, 3.13091 * eV, 3.13884 * eV, 3.14681 * eV, 3.15481 * eV, 3.16286 * eV, 3.17095 * eV,
       3.17908 * eV, 3.18725 * eV, 3.19547 * eV, 3.20373 * eV, 3.21203 * eV, 3.22037 * eV, 3.22875 * eV, 3.23719 * eV, 3.24566 * eV, 3.25418 * eV,
       3.26274 * eV, 3.27135 * eV, 3.28 * eV, 3.28871 * eV, 3.29745 * eV, 3.30624 * eV, 3.31509 * eV, 3.32397 * eV, 3.33291 * eV, 3.34189 * eV,
       3.35092 * eV, 3.36001 * eV, 3.36914 * eV, 3.37832 * eV, 3.38755 * eV, 3.39683 * eV, 3.40616 * eV, 3.41554 * eV, 3.42498 * eV, 3.43447 * eV,
       3.44401 * eV, 3.4536 * eV, 3.46325 * eV, 3.47295 * eV, 3.4827 * eV, 3.49251 * eV, 3.50238 * eV, 3.5123 * eV, 3.52228 * eV, 3.53231 * eV,
       3.54241 * eV, 3.55256 * eV, 3.56276 * eV, 3.57303 * eV, 3.58336 * eV, 3.59374 * eV, 3.60419 * eV, 3.6147 * eV, 3.62527 * eV, 3.6359 * eV,
       3.64659 * eV, 3.65735 * eV, 3.66817 * eV, 3.67906 * eV, 3.69001 * eV, 3.70102 * eV, 3.7121 * eV, 3.72325 * eV, 3.73446 * eV, 3.74575 * eV,
       3.7571 * eV, 3.76852 * eV, 3.78001 * eV, 3.79157 * eV, 3.8032 * eV, 3.8149 * eV, 3.82667 * eV, 3.83852 * eV, 3.85044 * eV, 3.86244 * eV,
       3.87451 * eV, 3.88665 * eV, 3.89887 * eV, 3.91117 * eV, 3.92355 * eV, 3.93601 * eV, 3.94854 * eV, 3.96116 * eV, 3.97385 * eV, 3.98663 * eV,
       3.99949 * eV, 4.01243 * eV, 4.02546 * eV, 4.03857 * eV, 4.05177 * eV, 4.06506 * eV, 4.07843 * eV, 4.09189 * eV, 4.10544 * eV, 4.11908 * eV,
       4.13281 * eV, 4.14663 * eV, 4.16054 * eV, 4.17455 * eV, 4.18865 * eV, 4.20285 * eV, 4.21715 * eV, 4.23154 * eV, 4.24603 * eV, 4.26062 * eV,
       4.27532 * eV, 4.29011 * eV, 4.30501 * eV, 4.32001 * eV, 4.33511 * eV, 4.35032 * eV, 4.36564 * eV, 4.38107 * eV, 4.3966 * eV, 4.41225 * eV,
       4.42801 * eV, 4.44388 * eV, 4.45986 * eV, 4.47596 * eV, 4.49218 * eV, 4.50852 * eV, 4.52497 * eV, 4.54155 * eV, 4.55824 * eV, 4.57506 * eV,
       4.59201 * eV, 4.60908 * eV, 4.62628 * eV, 4.6436 * eV, 4.66106 * eV, 4.67865 * eV, 4.69637 * eV, 4.71423 * eV, 4.73222 * eV, 4.75035 * eV,
       4.76862 * eV, 4.78703 * eV, 4.80559 * eV, 4.82429 * eV, 4.84313 * eV, 4.86212 * eV, 4.88127 * eV, 4.90056 * eV, 4.92001 * eV, 4.93961 * eV,
       4.95937 * eV, 4.97928 * eV, 4.99936 * eV, 5.0196 * eV, 5.04001 * eV, 5.06058 * eV, 5.08132 * eV, 5.10223 * eV, 5.12331 * eV, 5.14457 * eV,
       5.16601 * eV, 5.18762 * eV, 5.20942 * eV, 5.2314 * eV, 5.25357 * eV, 5.27592 * eV, 5.29847 * eV, 5.32121 * eV, 5.34415 * eV, 5.36728 * eV,
       5.39062 * eV, 5.41416 * eV, 5.4379 * eV, 5.46186 * eV, 5.48603 * eV, 5.51041 * eV, 5.53501 * eV, 5.55983 * eV, 5.58487 * eV, 5.61014 * eV,
       5.63564 * eV, 5.66138 * eV, 5.68735 * eV, 5.71356 * eV, 5.74001 * eV, 5.76671 * eV, 5.79365 * eV, 5.82085 * eV, 5.84831 * eV, 5.87603 * eV,
       5.90401 * eV, 5.93226 * eV, 5.96078 * eV, 5.98957 * eV, 6.01865 * eV, 6.04801 * eV, 6.07766 * eV, 6.1076 * eV, 6.13783 * eV, 6.16837 * eV,
       6.19921 * eV};
  std::vector<G4double> FastComponent =
      {5.48303e-45, 1.10277e-44, 2.21239e-44, 4.42745e-44, 8.83811e-44, 1.75987e-43, 3.49554e-43, 6.92569e-43, 1.36876e-42, 2.69838e-42,
       5.30634e-42, 1.04088e-41, 2.03667e-41, 3.97517e-41, 7.73935e-41, 1.50303e-40, 2.91169e-40, 5.62647e-40, 1.08453e-39, 2.08527e-39,
       3.99941e-39, 7.65147e-39, 1.46018e-38, 2.77962e-38, 5.27808e-38, 9.99728e-38, 1.88887e-37, 3.55988e-37, 6.69243e-37, 1.25501e-36,
       2.3476e-36, 4.38041e-36, 8.15305e-36, 1.5137e-35, 2.80333e-35, 5.17872e-35, 9.543e-35, 1.75413e-34, 3.21627e-34, 5.88244e-34,
       1.07319e-33, 1.95304e-33, 3.54535e-33, 6.4198e-33, 1.15957e-32, 2.08924e-32, 3.75486e-32, 6.73153e-32, 1.20378e-31, 2.14731e-31,
       3.82083e-31, 6.78163e-31, 1.20067e-30, 2.12046e-30, 3.7355e-30, 6.56421e-30, 1.15062e-29, 2.01183e-29, 3.50888e-29, 6.10463e-29,
       1.05941e-28, 1.83393e-28, 3.16677e-28, 5.45461e-28, 9.37186e-28, 1.60621e-27, 2.74595e-27, 4.68271e-27, 7.96556e-27, 1.3516e-26,
       2.28769e-26, 3.86241e-26, 6.50481e-26, 1.09276e-25, 1.83117e-25, 3.06089e-25, 5.10365e-25, 8.48845e-25, 1.40828e-24, 2.33059e-24,
       3.8473e-24, 6.3352e-24, 1.04059e-23, 1.70495e-23, 2.7865e-23, 4.54277e-23, 7.38748e-23, 1.19836e-22, 1.93906e-22, 3.12974e-22,
       5.03897e-22, 8.09261e-22, 1.29643e-21, 2.07169e-21, 3.30229e-21, 5.25072e-21, 8.32794e-21, 1.31756e-20, 2.0793e-20, 3.27324e-20,
       5.13989e-20, 8.05088e-20, 1.2579e-19, 1.96049e-19, 3.04788e-19, 4.72655e-19, 7.31148e-19, 1.12819e-18, 1.73648e-18, 2.66608e-18,
       4.08312e-18, 6.2377e-18, 9.50541e-18, 1.44488e-17, 2.19082e-17, 3.31357e-17, 4.99919e-17, 7.52346e-17, 1.1294e-16, 1.6912e-16,
       2.52614e-16, 3.76384e-16, 5.59398e-16, 8.29324e-16, 1.22643e-15, 1.80915e-15, 2.66207e-15, 3.90734e-15, 5.72078e-15, 8.35496e-15,
       1.21716e-14, 1.76875e-14, 2.56388e-14, 3.70718e-14, 5.34692e-14, 7.69269e-14, 1.10399e-13, 1.58041e-13, 2.25677e-13, 3.21454e-13,
       4.56736e-13, 6.4733e-13, 9.15166e-13, 1.29059e-12, 1.81548e-12, 2.54747e-12, 3.56566e-12, 4.97836e-12, 6.9334e-12, 9.63209e-12,
       1.33478e-11, 1.84507e-11, 2.54407e-11, 3.49913e-11, 4.80072e-11, 6.57001e-11, 8.96892e-11, 1.22132e-10, 1.65894e-10, 2.24775e-10,
       3.03794e-10, 4.09567e-10, 5.50788e-10, 7.38854e-10, 9.8866e-10, 1.31962e-09, 1.75698e-09, 2.33344e-09, 3.09131e-09, 4.0851e-09,
       5.38488e-09, 7.0805e-09, 9.28681e-09, 1.21502e-08, 1.58567e-08, 2.06424e-08, 2.68052e-08, 3.4721e-08, 4.48622e-08, 5.78206e-08,
       7.4336e-08, 9.533e-08, 1.21948e-07, 1.55609e-07, 1.98065e-07, 2.51475e-07, 3.18491e-07, 4.02359e-07, 5.07043e-07, 6.37367e-07,
       7.99187e-07, 9.9959e-07, 1.24712e-06, 1.55207e-06, 1.92676e-06, 2.38593e-06, 2.94715e-06, 3.6313e-06, 4.46308e-06, 5.4717e-06,
       6.69151e-06, 8.16282e-06, 9.93277e-06, 1.20563e-05, 1.45973e-05, 1.76298e-05, 2.1239e-05, 2.55232e-05, 3.05951e-05, 3.65832e-05,
       4.36341e-05, 5.19141e-05, 6.1611e-05, 7.29365e-05, 8.61284e-05, 0.0001015, 0.0001192, 0.0001397, 0.0001633, 0.0001905,
       0.0002216, 0.0002571, 0.0002976, 0.0003436, 0.0003958, 0.0004547, 0.000521, 0.0005956, 0.0006791, 0.0007725,
       0.0008764, 0.0009919, 0.0011197, 0.0012609, 0.0014164, 0.001587, 0.0017737, 0.0019775, 0.0021992, 0.0024396,
       0.0026995, 0.0029797, 0.0032808, 0.0036032, 0.0039475, 0.0043139, 0.0047025, 0.0051132, 0.005546, 0.0060005,
       0.0064759, 0.0069715, 0.0074864, 0.0080192, 0.0085684, 0.0091325, 0.0097093, 0.0102968, 0.0108926, 0.0114941,
       0.0120985, 0.012703, 0.0133043, 0.0138992, 0.0144846, 0.0150569, 0.0156127, 0.0161486, 0.0166612, 0.0171472,
       0.0176033, 0.0180263, 0.0184135, 0.018762, 0.0190694, 0.0193334, 0.0195521, 0.019724, 0.0198476, 0.0199222,
       0.0199471, 0.0199222, 0.0198476, 0.019724, 0.0195521, 0.0193334, 0.0190694, 0.018762, 0.0184135, 0.0180263,
       0.0176033, 0.0171472, 0.0166612, 0.0161486, 0.0156127, 0.0150569, 0.0144846, 0.0138992, 0.0133043, 0.012703,
       0.0120985, 0.0114941, 0.0108926, 0.0102968, 0.0097093, 0.0091325, 0.0085684, 0.0080192, 0.0074864, 0.0069715,
       0.0064759, 0.0060005, 0.005546, 0.0051132, 0.0047025, 0.0043139, 0.0039475, 0.0036032, 0.0032808, 0.0029797,
       0.0026995, 0.0024396, 0.0021992, 0.0019775, 0.0017737, 0.001587, 0.0014164, 0.0012609, 0.0011197, 0.0009919,
       0.0008764, 0.0007725, 0.0006791, 0.0005956, 0.000521, 0.0004547, 0.0003958, 0.0003436, 0.0002976, 0.0002571,
       0.0002216, 0.0001905, 0.0001633, 0.0001397, 0.0001192, 0.0001015, 8.61284e-05, 7.29365e-05, 6.1611e-05, 5.19141e-05,
       4.36341e-05, 3.65832e-05, 3.05951e-05, 2.55232e-05, 2.1239e-05, 1.76298e-05, 1.45973e-05, 1.20563e-05, 9.93277e-06, 8.16282e-06,
       6.69151e-06, 5.4717e-06, 4.46308e-06, 3.6313e-06, 2.94715e-06, 2.38593e-06, 1.92676e-06, 1.55207e-06, 1.24712e-06, 9.9959e-07,
       7.99187e-07, 6.37367e-07, 5.07043e-07, 4.02359e-07, 3.18491e-07, 2.51475e-07, 1.98065e-07, 1.55609e-07, 1.21948e-07, 9.533e-08,
       7.4336e-08, 5.78206e-08, 4.48622e-08, 3.4721e-08, 2.68052e-08, 2.06424e-08, 1.58567e-08, 1.21502e-08, 9.28681e-09, 7.0805e-09,
       5.38488e-09, 4.0851e-09, 3.09131e-09, 2.33344e-09, 1.75698e-09, 1.31962e-09, 9.8866e-10, 7.38854e-10, 5.50788e-10, 4.09567e-10,
       3.03794e-10, 2.24775e-10, 1.65894e-10, 1.22132e-10, 8.96892e-11, 6.57001e-11, 4.80072e-11, 3.49913e-11, 2.54407e-11, 1.84507e-11,
       1.33478e-11, 9.63209e-12, 6.9334e-12, 4.97836e-12, 3.56566e-12, 2.54747e-12, 1.81548e-12, 1.29059e-12, 9.15166e-13, 6.4733e-13,
       4.56736e-13, 3.21454e-13, 2.25677e-13, 1.58041e-13, 1.10399e-13, 7.69269e-14, 5.34692e-14, 3.70718e-14, 2.56388e-14, 1.76875e-14,
       1.21716e-14, 8.35496e-15, 5.72078e-15, 3.90734e-15, 2.66207e-15, 1.80915e-15, 1.22643e-15, 8.29324e-16, 5.59398e-16, 3.76384e-16,
       2.52614e-16, 1.6912e-16, 1.1294e-16, 7.52346e-17, 4.99919e-17, 3.31357e-17, 2.19082e-17, 1.44488e-17, 9.50541e-18, 6.2377e-18,
       4.08312e-18, 2.66608e-18, 1.73648e-18, 1.12819e-18, 7.31148e-19, 4.72655e-19, 3.04788e-19, 1.96049e-19, 1.2579e-19, 8.05088e-20,
       5.13989e-20, 3.27324e-20, 2.0793e-20, 1.31756e-20, 8.32794e-21, 5.25072e-21, 3.30229e-21, 2.07169e-21, 1.29643e-21, 8.09261e-22,
       5.03897e-22, 3.12974e-22, 1.93906e-22, 1.19836e-22, 7.38748e-23, 4.54277e-23, 2.7865e-23, 1.70495e-23, 1.04059e-23, 6.3352e-24,
       3.8473e-24, 2.33059e-24, 1.40828e-24, 8.48845e-25, 5.10365e-25, 3.06089e-25, 1.83117e-25, 1.09276e-25, 6.50481e-26, 3.86241e-26,
       2.28769e-26, 1.3516e-26, 7.96556e-27, 4.68271e-27, 2.74595e-27, 1.60621e-27, 9.37186e-28, 5.45461e-28, 3.16677e-28, 1.83393e-28,
       1.05941e-28};

  G4double PbWO_indexZero = 1.5861;
  G4double PbWO_nVec[1] = {1.1062};
  G4double PbWO_lVec[1] = {270.63};
  int sizeVect = sizeof(PbWO_nVec) / sizeof(*PbWO_nVec);

  std::vector<G4double> PhotonEnergy_RI =
      {0.0001 * eV, 1.0 * eV, 1.84 * eV, 2.952 * eV, 4.08 * eV};
  std::vector<G4double> RefractiveIndex =
      {CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[0])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[1])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[2])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[3])),
       CalculateSellmeier(sizeVect, PbWO_indexZero, PbWO_nVec, PbWO_lVec, fromEvToNm(PhotonEnergy_RI[4]))};

  std::vector<G4double> PhotonEnergy_ABS =
      {1.25237 * eV, 1.26514 * eV, 1.27819 * eV, 1.2915 * eV, 1.3051 * eV, 1.31898 * eV, 1.33316 * eV, 1.34765 * eV, 1.36246 * eV, 1.3776 * eV,
       1.39308 * eV, 1.40891 * eV, 1.42511 * eV, 1.44168 * eV, 1.45864 * eV, 1.476 * eV, 1.49379 * eV, 1.512 * eV, 1.53067 * eV, 1.5498 * eV,
       1.56942 * eV, 1.58954 * eV, 1.61018 * eV, 1.63137 * eV, 1.65312 * eV, 1.67546 * eV, 1.69841 * eV, 1.722 * eV, 1.74626 * eV, 1.7712 * eV,
       1.79687 * eV, 1.8233 * eV, 1.85051 * eV, 1.87855 * eV, 1.90745 * eV, 1.93725 * eV, 1.968 * eV, 1.99974 * eV, 2.03253 * eV, 2.0664 * eV,
       2.10143 * eV, 2.13766 * eV, 2.17516 * eV, 2.214 * eV, 2.25426 * eV, 2.296 * eV, 2.33932 * eV, 2.38431 * eV, 2.43106 * eV, 2.47968 * eV,
       2.53029 * eV, 2.583 * eV, 2.63796 * eV, 2.69531 * eV, 2.7552 * eV, 2.81782 * eV, 2.88335 * eV, 2.952 * eV, 3.024 * eV, 3.0996 * eV,
       3.17908 * eV, 3.26274 * eV, 3.35092 * eV, 3.44401 * eV, 3.54241 * eV, 3.64659 * eV, 3.7571 * eV, 3.87451 * eV, 3.99949 * eV, 4.13281 * eV};
  std::vector<G4double> Absorption =
      {3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm,
       3105 * mm, 2745 * mm, 2460 * mm, 2230 * mm, 2039 * mm, 1877 * mm, 1859 * mm, 1826 * mm, 1764 * mm, 1760 * mm,
       1664 * mm, 1585 * mm, 1471 * mm, 1376 * mm, 1272 * mm, 1187 * mm, 1114 * mm, 1046 * mm, 993.2 * mm, 942.9 * mm,
       898.8 * mm, 856.9 * mm, 821.7 * mm, 794.2 * mm, 767.7 * mm, 746.5 * mm, 725.6 * mm, 710.7 * mm, 695.3 * mm, 686.2 * mm,
       674.8 * mm, 663.5 * mm, 648.3 * mm, 633.4 * mm, 622.3 * mm, 607.8 * mm, 590.9 * mm, 568.9 * mm, 541.4 * mm, 502.9 * mm,
       467 * mm, 430.2 * mm, 390.1 * mm, 345.3 * mm, 298.9 * mm, 256.7 * mm, 219.8 * mm, 185.4 * mm, 150.9 * mm, 116.4 * mm,
       84.8 * mm, 59.4 * mm, 41.1 * mm, 27.5 * mm, 24.2 * mm, 24.2 * mm, 24.3 * mm, 24.3 * mm, 24.4 * mm, 24.6 * mm};

  // scaleFactor = 1.0;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);
  myMPT->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 3.2);
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 12700* ns);
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 1);

  mat->SetMaterialPropertiesTable(myMPT);
  // Set the Birks Constant for the Polystyrene scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  return mat;
}

G4Material *MyMaterials::BGO(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{
  // ########################################################
  // BGO的衰减长度似乎比较小？根据透射率进行计算得到的
  // ########

  double standard_light_yield = 8000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Ge = new G4Element("Germanium", "Ge", z = 32., a = 72.64 * g / mole);
  G4Element *Bi = new G4Element("Bismuth", "Bi", z = 83., a = 208.98 * g / mole);

  G4Material *mat = new G4Material("BGO", density = 7.13 * g / cm3, 3);
  mat->AddElement(Bi, 2);
  mat->AddElement(Ge, 1);
  mat->AddElement(O, 5);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  // --- Refractive Index
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_ABS = {
      1.55369 * eV, 1.55759 * eV, 1.56151 * eV, 1.56546 * eV, 1.56942 * eV, 1.57340 * eV, 1.57741 * eV, 1.58143 * eV,
      1.58548 * eV, 1.58954 * eV, 1.59363 * eV, 1.59773 * eV, 1.60186 * eV, 1.60601 * eV, 1.61018 * eV, 1.61438 * eV,
      1.61859 * eV, 1.62283 * eV, 1.62709 * eV, 1.63137 * eV, 1.63568 * eV, 1.64000 * eV, 1.64435 * eV, 1.64873 * eV,
      1.65312 * eV, 1.65754 * eV, 1.66199 * eV, 1.66645 * eV, 1.67095 * eV, 1.67546 * eV, 1.68000 * eV, 1.68457 * eV,
      1.68916 * eV, 1.69377 * eV, 1.69841 * eV, 1.70308 * eV, 1.70777 * eV, 1.71249 * eV, 1.71723 * eV, 1.72200 * eV,
      1.72680 * eV, 1.73162 * eV, 1.73647 * eV, 1.74135 * eV, 1.74626 * eV, 1.75119 * eV, 1.75615 * eV, 1.76114 * eV,
      1.76616 * eV, 1.77120 * eV, 1.77628 * eV, 1.78138 * eV, 1.78652 * eV, 1.79168 * eV, 1.79687 * eV, 1.80210 * eV,
      1.80735 * eV, 1.81263 * eV, 1.81795 * eV, 1.82330 * eV, 1.82868 * eV, 1.83409 * eV, 1.83953 * eV, 1.84500 * eV,
      1.85051 * eV, 1.85605 * eV, 1.86162 * eV, 1.86723 * eV, 1.87287 * eV, 1.87855 * eV, 1.88426 * eV, 1.89000 * eV,
      1.89578 * eV, 1.90160 * eV, 1.90745 * eV, 1.91334 * eV, 1.91926 * eV, 1.92522 * eV, 1.93122 * eV, 1.93725 * eV,
      1.94333 * eV, 1.94944 * eV, 1.95559 * eV, 1.96178 * eV, 1.96800 * eV, 1.97427 * eV, 1.98058 * eV, 1.98693 * eV,
      1.99332 * eV, 1.99975 * eV, 2.00622 * eV, 2.01273 * eV, 2.01929 * eV, 2.02589 * eV, 2.03253 * eV, 2.03921 * eV,
      2.04594 * eV, 2.05272 * eV, 2.05954 * eV, 2.06640 * eV, 2.07331 * eV, 2.08027 * eV, 2.08728 * eV, 2.09433 * eV,
      2.10143 * eV, 2.10857 * eV, 2.11577 * eV, 2.12302 * eV, 2.13031 * eV, 2.13766 * eV, 2.14506 * eV, 2.15250 * eV,
      2.16000 * eV, 2.16756 * eV, 2.17516 * eV, 2.18282 * eV, 2.19053 * eV, 2.19830 * eV, 2.20612 * eV, 2.21400 * eV,
      2.22194 * eV, 2.22993 * eV, 2.23798 * eV, 2.24609 * eV, 2.25426 * eV, 2.26249 * eV, 2.27077 * eV, 2.27912 * eV,
      2.28753 * eV, 2.29600 * eV, 2.30454 * eV, 2.31314 * eV, 2.32180 * eV, 2.33053 * eV, 2.33932 * eV, 2.34819 * eV,
      2.35711 * eV, 2.36611 * eV, 2.37518 * eV, 2.38431 * eV, 2.39352 * eV, 2.40279 * eV, 2.41214 * eV, 2.42157 * eV,
      2.43106 * eV, 2.44063 * eV, 2.45028 * eV, 2.46000 * eV, 2.46980 * eV, 2.47968 * eV, 2.48964 * eV, 2.49968 * eV,
      2.50980 * eV, 2.52000 * eV, 2.53029 * eV, 2.54066 * eV, 2.55112 * eV, 2.56166 * eV, 2.57229 * eV, 2.58300 * eV,
      2.59381 * eV, 2.60471 * eV, 2.61570 * eV, 2.62678 * eV, 2.63796 * eV, 2.64924 * eV, 2.66061 * eV, 2.67207 * eV,
      2.68364 * eV, 2.69531 * eV, 2.70708 * eV, 2.71895 * eV, 2.73093 * eV, 2.74301 * eV, 2.75520 * eV, 2.76750 * eV,
      2.77991 * eV, 2.79244 * eV, 2.80507 * eV, 2.81782 * eV, 2.83069 * eV, 2.84367 * eV, 2.85678 * eV, 2.87000 * eV,
      2.88335 * eV, 2.89683 * eV, 2.91043 * eV, 2.92416 * eV, 2.93801 * eV, 2.95200 * eV, 2.96613 * eV, 2.98039 * eV,
      2.99479 * eV, 3.00933 * eV, 3.02400 * eV, 3.03883 * eV, 3.05380 * eV, 3.06892 * eV, 3.08418 * eV, 3.09960 * eV,
      3.11518 * eV, 3.13091 * eV, 3.14681 * eV, 3.16286 * eV, 3.17908 * eV, 3.19547 * eV, 3.21203 * eV, 3.22876 * eV,
      3.24566 * eV, 3.26274 * eV, 3.28001 * eV, 3.29745 * eV, 3.31509 * eV, 3.33291 * eV, 3.35092 * eV, 3.36914 * eV,
      3.38755 * eV, 3.40616 * eV, 3.42498 * eV, 3.44401 * eV, 3.46325 * eV, 3.48270 * eV, 3.50238 * eV, 3.52228 * eV,
      3.54241 * eV, 3.56276 * eV, 3.58336 * eV, 3.60419 * eV, 3.62527 * eV, 3.64659 * eV, 3.66817 * eV, 3.69001 * eV,
      3.71210 * eV, 3.73446 * eV, 3.75710 * eV, 3.78001 * eV, 3.80320 * eV, 3.82667 * eV, 3.85044 * eV, 3.87451 * eV,
      3.89887 * eV, 3.92355 * eV, 3.94854 * eV, 3.97385 * eV, 3.99949 * eV, 4.02546 * eV, 4.05177 * eV, 4.07843 * eV,
      4.10544 * eV, 4.13281 * eV, 4.16054 * eV, 4.18866 * eV, 4.21715 * eV, 4.24603 * eV, 4.27532 * eV, 4.30501 * eV,
      4.33511 * eV, 4.36564 * eV, 4.39660 * eV, 4.42801 * eV, 4.45986 * eV, 4.49218 * eV, 4.52497 * eV, 4.55824 * eV,
      4.59201 * eV, 4.62628 * eV, 4.66106 * eV, 4.69637 * eV, 4.73222 * eV, 4.76862 * eV, 4.80559 * eV, 4.84313 * eV,
      4.88127 * eV, 4.92001 * eV, 4.95937 * eV, 4.99936 * eV, 5.04001 * eV, 5.08132 * eV, 5.12331 * eV, 5.16601 * eV,
      5.20942 * eV, 5.25357 * eV, 5.29847 * eV, 5.34415 * eV, 5.39062 * eV, 5.43790 * eV, 5.48603 * eV, 5.53501 * eV,
      5.58487 * eV, 5.63565 * eV};

  std::vector<G4double> RefractiveIndex = {
      2.11651, 2.11655, 2.11658, 2.11661, 2.11664, 2.11667, 2.11670, 2.11673,
      2.11676, 2.11679, 2.11685, 2.11691, 2.11697, 2.11704, 2.11710, 2.11716,
      2.11722, 2.11728, 2.11734, 2.11740, 2.11747, 2.11753, 2.11759, 2.11765,
      2.11771, 2.11777, 2.11783, 2.11790, 2.11796, 2.11802, 2.11808, 2.11814,
      2.11821, 2.11828, 2.11834, 2.11842, 2.11849, 2.11858, 2.11866, 2.11876,
      2.11885, 2.11896, 2.11906, 2.11918, 2.11930, 2.11941, 2.11952, 2.11963,
      2.11974, 2.11985, 2.11996, 2.12008, 2.12022, 2.12037, 2.12053, 2.12069,
      2.12085, 2.12102, 2.12118, 2.12134, 2.12151, 2.12169, 2.12187, 2.12205,
      2.12224, 2.12242, 2.12262, 2.12282, 2.12302, 2.12322, 2.12343, 2.12363,
      2.12383, 2.12402, 2.12421, 2.12440, 2.12460, 2.12480, 2.12500, 2.12520,
      2.12541, 2.12562, 2.12582, 2.12603, 2.12624, 2.12646, 2.12670, 2.12695,
      2.12723, 2.12752, 2.12781, 2.12812, 2.12843, 2.12874, 2.12906, 2.12938,
      2.12971, 2.13005, 2.13040, 2.13075, 2.13111, 2.13149, 2.13187, 2.13227,
      2.13268, 2.13309, 2.13348, 2.13387, 2.13425, 2.13462, 2.13498, 2.13533,
      2.13567, 2.13600, 2.13632, 2.13664, 2.13697, 2.13731, 2.13765, 2.13800,
      2.13833, 2.13865, 2.13895, 2.13924, 2.13951, 2.13979, 2.14006, 2.14034,
      2.14063, 2.14091, 2.14121, 2.14152, 2.14183, 2.14216, 2.14250, 2.14284,
      2.14318, 2.14352, 2.14387, 2.14421, 2.14457, 2.14495, 2.14535, 2.14577,
      2.14620, 2.14665, 2.14713, 2.14763, 2.14815, 2.14869, 2.14923, 2.14977,
      2.15030, 2.15084, 2.15137, 2.15189, 2.15240, 2.15290, 2.15339, 2.15388,
      2.15435, 2.15481, 2.15526, 2.15570, 2.15613, 2.15655, 2.15695, 2.15734,
      2.15771, 2.15808, 2.15845, 2.15884, 2.15923, 2.15963, 2.16005, 2.16048,
      2.16092, 2.16138, 2.16186, 2.16235, 2.16289, 2.16346, 2.16408, 2.16474,
      2.16544, 2.16610, 2.16671, 2.16727, 2.16778, 2.16824, 2.16868, 2.16911,
      2.16951, 2.16990, 2.17027, 2.17060, 2.17088, 2.17111, 2.17128, 2.17141,
      2.17152, 2.17163, 2.17172, 2.17181, 2.17188, 2.17208, 2.17242, 2.17290,
      2.17352, 2.17428, 2.17514, 2.17612, 2.17719, 2.17838, 2.17965, 2.18081,
      2.18186, 2.18280, 2.18364, 2.18439, 2.18520, 2.18606, 2.18696, 2.18792,
      2.18892, 2.18973, 2.19035, 2.19077, 2.19099, 2.19102, 2.19107, 2.19115,
      2.19126, 2.19138, 2.19156, 2.19197, 2.19260, 2.19347, 2.19457, 2.19588,
      2.19722, 2.19860, 2.20001, 2.20145, 2.20294, 2.20452, 2.20621, 2.20800,
      2.20988, 2.21186, 2.21385, 2.21587, 2.21791, 2.21997, 2.22206, 2.22424,
      2.22650, 2.22885, 2.23129, 2.23386, 2.23667, 2.23972, 2.24300, 2.24653,
      2.25032, 2.25461, 2.25938, 2.26466, 2.27043, 2.27672, 2.28351, 2.29079,
      2.29856, 2.30682, 2.31561, 2.32505, 2.33515, 2.34591, 2.35733, 2.36918,
      2.37438, 2.37976, 2.38533, 2.39113, 2.39717, 2.40335, 2.40968, 2.41622,
      2.42302, 2.43010};

  std::vector<G4double> Absorption = {
      306.74520 * mm, 297.26304 * mm, 290.52204 * mm, 284.99272 * mm, 272.89041 * mm, 270.66131 * mm, 264.47562 * mm, 257.31102 * mm,
      252.48876 * mm, 249.45741 * mm, 247.09458 * mm, 246.69876 * mm, 234.90033 * mm, 232.86958 * mm, 235.03736 * mm, 233.86249 * mm,
      235.36066 * mm, 233.57979 * mm, 221.95655 * mm, 220.51788 * mm, 222.22112 * mm, 222.31698 * mm, 223.04992 * mm, 221.75579 * mm,
      227.32457 * mm, 228.99676 * mm, 231.11938 * mm, 236.37542 * mm, 233.56182 * mm, 234.21647 * mm, 233.91697 * mm, 228.47044 * mm,
      232.53553 * mm, 236.83727 * mm, 233.66821 * mm, 228.07102 * mm, 228.66511 * mm, 229.45889 * mm, 230.96608 * mm, 233.09428 * mm,
      228.94979 * mm, 229.12428 * mm, 227.60343 * mm, 228.14848 * mm, 227.62583 * mm, 223.96638 * mm, 221.73550 * mm, 221.25256 * mm,
      225.39774 * mm, 227.11056 * mm, 223.91316 * mm, 223.14576 * mm, 224.91443 * mm, 223.37265 * mm, 222.98195 * mm, 221.64733 * mm,
      218.18684 * mm, 217.36715 * mm, 217.76647 * mm, 220.08596 * mm, 222.83736 * mm, 223.03916 * mm, 223.82862 * mm, 225.12500 * mm,
      223.77222 * mm, 225.35214 * mm, 225.79560 * mm, 225.17460 * mm, 224.89636 * mm, 224.22765 * mm, 227.36401 * mm, 227.06886 * mm,
      225.22577 * mm, 225.28883 * mm, 224.64827 * mm, 228.13158 * mm, 229.75219 * mm, 229.40527 * mm, 228.57382 * mm, 223.26183 * mm,
      221.58433 * mm, 218.99092 * mm, 219.80581 * mm, 219.38763 * mm, 219.24013 * mm, 219.83911 * mm, 222.37302 * mm, 221.30438 * mm,
      223.34679 * mm, 221.88384 * mm, 223.28193 * mm, 225.33299 * mm, 224.53774 * mm, 225.95846 * mm, 228.71197 * mm, 228.26246 * mm,
      230.20063 * mm, 230.27808 * mm, 229.40795 * mm, 230.89960 * mm, 234.11836 * mm, 238.50325 * mm, 236.47017 * mm, 235.55875 * mm,
      237.38855 * mm, 237.19088 * mm, 236.80252 * mm, 239.02870 * mm, 238.61373 * mm, 239.66362 * mm, 237.46288 * mm, 233.57478 * mm,
      231.78612 * mm, 229.85821 * mm, 226.09495 * mm, 223.93386 * mm, 222.50989 * mm, 221.17167 * mm, 220.70901 * mm, 220.24326 * mm,
      219.25381 * mm, 217.71796 * mm, 217.88208 * mm, 218.12089 * mm, 216.02682 * mm, 214.92506 * mm, 214.27965 * mm, 211.44163 * mm,
      211.19528 * mm, 211.45955 * mm, 210.69372 * mm, 211.63709 * mm, 213.28735 * mm, 214.99630 * mm, 218.14153 * mm, 218.37770 * mm,
      216.20659 * mm, 216.05007 * mm, 215.12700 * mm, 213.81471 * mm, 211.26890 * mm, 208.59716 * mm, 207.52558 * mm, 206.83781 * mm,
      206.42373 * mm, 206.31117 * mm, 205.22807 * mm, 205.84232 * mm, 204.69697 * mm, 203.84137 * mm, 203.50375 * mm, 202.98864 * mm,
      202.34676 * mm, 200.82931 * mm, 198.93044 * mm, 198.21928 * mm, 199.93524 * mm, 202.51304 * mm, 203.87612 * mm, 203.08280 * mm,
      202.93795 * mm, 204.13753 * mm, 203.50950 * mm, 201.36620 * mm, 199.64205 * mm, 199.34975 * mm, 199.92542 * mm, 199.64198 * mm,
      199.79423 * mm, 199.38061 * mm, 199.02498 * mm, 197.12878 * mm, 194.90449 * mm, 193.52524 * mm, 192.40217 * mm, 192.30384 * mm,
      190.57158 * mm, 186.92882 * mm, 183.83365 * mm, 183.45025 * mm, 184.13688 * mm, 183.43123 * mm, 183.04898 * mm, 183.65744 * mm,
      183.31420 * mm, 181.18274 * mm, 179.53682 * mm, 178.29473 * mm, 177.34256 * mm, 177.13345 * mm, 176.21290 * mm, 176.59952 * mm,
      177.36243 * mm, 176.55166 * mm, 175.25735 * mm, 174.11657 * mm, 173.10860 * mm, 173.44854 * mm, 173.97557 * mm, 173.66964 * mm,
      174.78966 * mm, 177.28488 * mm, 178.42534 * mm, 178.26669 * mm, 179.61778 * mm, 177.40607 * mm, 174.43904 * mm, 172.76975 * mm,
      169.45612 * mm, 167.52894 * mm, 166.48115 * mm, 164.45587 * mm, 161.59323 * mm, 157.76382 * mm, 154.33437 * mm, 150.62754 * mm,
      146.37615 * mm, 140.86672 * mm, 136.05165 * mm, 131.25236 * mm, 125.09009 * mm, 119.42212 * mm, 114.40955 * mm, 109.56437 * mm,
      103.62241 * mm, 99.47601 * mm, 95.65570 * mm, 91.05247 * mm, 86.34451 * mm, 81.15177 * mm, 76.28774 * mm, 71.53227 * mm,
      66.67082 * mm, 61.47413 * mm, 55.77604 * mm, 49.88733 * mm, 44.39200 * mm, 39.63207 * mm, 35.49639 * mm, 31.89803 * mm,
      28.76796 * mm, 25.96727 * mm, 23.50224 * mm, 21.32173 * mm, 19.41965 * mm, 17.64399 * mm, 15.96829 * mm, 14.43310 * mm,
      13.02828 * mm, 11.69468 * mm, 10.37163 * mm, 9.07409 * mm, 7.78320 * mm, 6.54818 * mm, 5.35505 * mm, 4.28463 * mm,
      3.49850 * mm, 3.19350 * mm, 3.16486 * mm, 3.16557 * mm, 3.16632 * mm, 3.17301 * mm, 3.18604 * mm, 3.19832 * mm,
      3.20107 * mm, 3.20502 * mm, 3.21023 * mm, 3.21657 * mm, 3.22321 * mm, 3.22939 * mm, 3.23994 * mm, 3.24913 * mm,
      3.25533 * mm, 3.26512 * mm, 3.27466 * mm, 3.28228 * mm, 3.29095 * mm, 3.30257 * mm, 3.31313 * mm, 3.32324 * mm,
      3.32888 * mm, 3.33319 * mm, 3.33589 * mm, 3.33680 * mm, 3.34071 * mm, 3.34632 * mm, 3.35282 * mm, 3.35704 * mm,
      3.36292 * mm, 3.36783 * mm};
  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  // BGO的实测值，<0的部分用0代替
  std::vector<G4double> PhotonEnergy = {
      1.549802e+00 * eV, 1.553687e+00 * eV, 1.557590e+00 * eV, 1.561514e+00 * eV, 1.565457e+00 * eV, 1.569420e+00 * eV, 1.573403e+00 * eV, 1.577407e+00 * eV, 1.581431e+00 * eV, 1.585476e+00 * eV, 1.589541e+00 * eV, 1.593627e+00 * eV, 1.597734e+00 * eV, 1.601863e+00 * eV, 1.606013e+00 * eV, 1.610184e+00 * eV, 1.614378e+00 * eV, 1.618593e+00 * eV, 1.622830e+00 * eV, 1.627089e+00 * eV, 1.631371e+00 * eV, 1.635675e+00 * eV, 1.640003e+00 * eV, 1.644353e+00 * eV, 1.648726e+00 * eV, 1.653123e+00 * eV, 1.657543e+00 * eV, 1.661987e+00 * eV, 1.666454e+00 * eV, 1.670946e+00 * eV, 1.675462e+00 * eV, 1.680003e+00 * eV, 1.684568e+00 * eV, 1.689158e+00 * eV, 1.693773e+00 * eV, 1.698414e+00 * eV, 1.703080e+00 * eV, 1.707771e+00 * eV, 1.712489e+00 * eV, 1.717233e+00 * eV, 1.722003e+00 * eV, 1.726799e+00 * eV, 1.731623e+00 * eV, 1.736473e+00 * eV, 1.741351e+00 * eV, 1.746256e+00 * eV, 1.751189e+00 * eV, 1.756150e+00 * eV, 1.761139e+00 * eV, 1.766157e+00 * eV, 1.771203e+00 * eV, 1.776278e+00 * eV, 1.781382e+00 * eV, 1.786516e+00 * eV, 1.791679e+00 * eV, 1.796872e+00 * eV, 1.802096e+00 * eV, 1.807350e+00 * eV, 1.812634e+00 * eV, 1.817950e+00 * eV, 1.823297e+00 * eV, 1.828675e+00 * eV, 1.834086e+00 * eV, 1.839528e+00 * eV, 1.845003e+00 * eV, 1.850510e+00 * eV, 1.856051e+00 * eV, 1.861625e+00 * eV, 1.867232e+00 * eV, 1.872873e+00 * eV, 1.878548e+00 * eV, 1.884258e+00 * eV, 1.890003e+00 * eV, 1.895783e+00 * eV, 1.901598e+00 * eV, 1.907449e+00 * eV, 1.913336e+00 * eV, 1.919260e+00 * eV, 1.925220e+00 * eV, 1.931218e+00 * eV, 1.937253e+00 * eV, 1.943326e+00 * eV, 1.949437e+00 * eV, 1.955587e+00 * eV, 1.961775e+00 * eV, 1.968003e+00 * eV, 1.974271e+00 * eV, 1.980578e+00 * eV, 1.986926e+00 * eV, 1.993315e+00 * eV, 1.999745e+00 * eV, 2.006217e+00 * eV, 2.012730e+00 * eV, 2.019287e+00 * eV, 2.025886e+00 * eV, 2.032528e+00 * eV, 2.039214e+00 * eV, 2.045944e+00 * eV, 2.052718e+00 * eV, 2.059538e+00 * eV, 2.066403e+00 * eV, 2.073314e+00 * eV, 2.080272e+00 * eV, 2.087276e+00 * eV, 2.094328e+00 * eV, 2.101427e+00 * eV, 2.108575e+00 * eV, 2.115771e+00 * eV, 2.123017e+00 * eV, 2.130313e+00 * eV, 2.137659e+00 * eV, 2.145055e+00 * eV, 2.152503e+00 * eV, 2.160003e+00 * eV, 2.167556e+00 * eV, 2.175161e+00 * eV, 2.182820e+00 * eV, 2.190533e+00 * eV, 2.198301e+00 * eV, 2.206124e+00 * eV, 2.214003e+00 * eV, 2.221939e+00 * eV, 2.229932e+00 * eV, 2.237982e+00 * eV, 2.246090e+00 * eV, 2.254258e+00 * eV, 2.262485e+00 * eV, 2.270773e+00 * eV, 2.279121e+00 * eV, 2.287531e+00 * eV, 2.296004e+00 * eV, 2.304539e+00 * eV, 2.313138e+00 * eV, 2.321801e+00 * eV, 2.330530e+00 * eV, 2.339324e+00 * eV, 2.348185e+00 * eV, 2.357114e+00 * eV, 2.366111e+00 * eV, 2.375176e+00 * eV, 2.384311e+00 * eV, 2.393517e+00 * eV, 2.402794e+00 * eV, 2.412144e+00 * eV, 2.421566e+00 * eV, 2.431063e+00 * eV, 2.440634e+00 * eV, 2.450280e+00 * eV, 2.460004e+00 * eV, 2.469805e+00 * eV, 2.479684e+00 * eV, 2.489642e+00 * eV, 2.499681e+00 * eV, 2.509801e+00 * eV, 2.520004e+00 * eV, 2.530290e+00 * eV, 2.540660e+00 * eV, 2.551115e+00 * eV, 2.561657e+00 * eV, 2.572286e+00 * eV, 2.583004e+00 * eV, 2.593812e+00 * eV, 2.604710e+00 * eV, 2.615700e+00 * eV, 2.626784e+00 * eV, 2.637962e+00 * eV, 2.649235e+00 * eV, 2.660605e+00 * eV, 2.672073e+00 * eV, 2.683641e+00 * eV, 2.695309e+00 * eV, 2.707078e+00 * eV, 2.718952e+00 * eV, 2.730929e+00 * eV, 2.743013e+00 * eV, 2.755204e+00 * eV, 2.767504e+00 * eV, 2.779915e+00 * eV, 2.792437e+00 * eV, 2.805072e+00 * eV, 2.817823e+00 * eV, 2.830689e+00 * eV, 2.843674e+00 * eV, 2.856779e+00 * eV, 2.870004e+00 * eV, 2.883353e+00 * eV, 2.896827e+00 * eV, 2.910427e+00 * eV, 2.924155e+00 * eV, 2.938014e+00 * eV, 2.952005e+00 * eV, 2.966129e+00 * eV, 2.980389e+00 * eV, 2.994787e+00 * eV, 3.009325e+00 * eV, 3.024005e+00 * eV, 3.038828e+00 * eV, 3.053798e+00 * eV, 3.068916e+00 * eV, 3.084184e+00 * eV, 3.099605e+00 * eV, 3.115181e+00 * eV, 3.130914e+00 * eV, 3.146807e+00 * eV, 3.162862e+00 * eV, 3.179082e+00 * eV, 3.195469e+00 * eV, 3.212026e+00 * eV, 3.228755e+00 * eV, 3.245660e+00 * eV, 3.262742e+00 * eV, 3.280005e+00 * eV, 3.297452e+00 * eV, 3.315085e+00 * eV, 3.332908e+00 * eV, 3.350924e+00 * eV, 3.369136e+00 * eV, 3.387546e+00 * eV, 3.406159e+00 * eV, 3.424978e+00 * eV, 3.444005e+00 * eV, 3.463246e+00 * eV, 3.482702e+00 * eV, 3.502378e+00 * eV, 3.522278e+00 * eV, 3.542406e+00 * eV, 3.562764e+00 * eV, 3.583358e+00 * eV, 3.604192e+00 * eV, 3.625269e+00 * eV, 3.646594e+00 * eV, 3.668171e+00 * eV, 3.690006e+00 * eV, 3.712102e+00 * eV, 3.734464e+00 * eV, 3.757097e+00 * eV, 3.780006e+00 * eV, 3.803196e+00 * eV, 3.826673e+00 * eV, 3.850441e+00 * eV, 3.874506e+00 * eV, 3.898874e+00 * eV, 3.923550e+00 * eV, 3.948541e+00 * eV, 3.973852e+00 * eV, 3.999490e+00 * eV, 4.025461e+00 * eV, 4.051771e+00 * eV, 4.078427e+00 * eV, 4.105437e+00 * eV, 4.132806e+00 * eV};
  std::vector<G4double> COMPONENT = {
      1.795417e-04, 1.786151e-04, 1.901804e-04, 1.959447e-04, 2.001024e-04, 1.938566e-04, 1.961014e-04, 1.973287e-04, 2.087365e-04, 2.135325e-04, 2.192456e-04, 2.239214e-04, 2.215911e-04, 2.238145e-04, 2.237850e-04, 2.362284e-04, 2.438981e-04, 2.533980e-04, 2.566182e-04, 2.669541e-04, 2.745797e-04, 2.809080e-04, 2.850937e-04, 2.848920e-04, 2.943054e-04, 3.048122e-04, 3.196230e-04, 3.276818e-04, 3.351533e-04, 3.426957e-04, 3.511393e-04, 3.597513e-04, 3.739922e-04, 3.929031e-04, 4.042121e-04, 4.137157e-04, 4.227772e-04, 4.318461e-04, 4.404130e-04, 4.473946e-04, 4.624595e-04, 4.788674e-04, 4.931498e-04, 5.057651e-04, 5.236445e-04, 5.405128e-04, 5.537482e-04, 5.776754e-04, 6.009607e-04, 6.233158e-04, 6.389449e-04, 6.604322e-04, 6.801802e-04, 7.075546e-04, 7.278614e-04, 7.531377e-04, 7.790073e-04, 8.056500e-04, 8.228047e-04, 8.395150e-04, 8.592031e-04, 8.790582e-04, 9.013892e-04, 9.168929e-04, 9.459438e-04, 9.663072e-04, 9.964794e-04, 1.013899e-03, 1.047115e-03, 1.080429e-03, 1.116525e-03, 1.148477e-03, 1.184400e-03, 1.222023e-03, 1.250968e-03, 1.285432e-03, 1.319211e-03, 1.365481e-03, 1.403968e-03, 1.447824e-03, 1.495020e-03, 1.535997e-03, 1.577212e-03, 1.621277e-03, 1.669679e-03, 1.717932e-03, 1.766111e-03, 1.809391e-03, 1.859019e-03, 1.908667e-03, 1.958150e-03, 2.014780e-03, 2.068389e-03, 2.123111e-03, 2.174689e-03, 2.231942e-03, 2.286806e-03, 2.346232e-03, 2.400674e-03, 2.457963e-03, 2.517205e-03, 2.577904e-03, 2.641994e-03, 2.708524e-03, 2.774745e-03, 2.839390e-03, 2.902948e-03, 2.973889e-03, 3.041142e-03, 3.106289e-03, 3.171224e-03, 3.240158e-03, 3.306128e-03, 3.372595e-03, 3.438896e-03, 3.502954e-03, 3.568342e-03, 3.623061e-03, 3.691103e-03, 3.768035e-03, 3.829572e-03, 3.893561e-03, 3.959160e-03, 4.024525e-03, 4.096949e-03, 4.167950e-03, 4.235691e-03, 4.305421e-03, 4.372176e-03, 4.437749e-03, 4.504159e-03, 4.567637e-03, 4.630747e-03, 4.689614e-03, 4.745544e-03, 4.793665e-03, 4.850540e-03, 4.901355e-03, 4.953146e-03, 4.991928e-03, 5.037749e-03, 5.081095e-03, 5.128247e-03, 5.164043e-03, 5.197396e-03, 5.228879e-03, 5.259975e-03, 5.283603e-03, 5.304831e-03, 5.326737e-03, 5.342228e-03, 5.355112e-03, 5.354667e-03, 5.357832e-03, 5.350387e-03, 5.347919e-03, 5.331669e-03, 5.320124e-03, 5.293058e-03, 5.266065e-03, 5.229341e-03, 5.184701e-03, 5.144456e-03, 5.093333e-03, 5.047792e-03, 4.993973e-03, 4.934075e-03, 4.866365e-03, 4.802718e-03, 4.733542e-03, 4.666464e-03, 4.588775e-03, 4.500717e-03, 4.414503e-03, 4.311856e-03, 4.211021e-03, 4.105716e-03, 3.999065e-03, 3.882535e-03, 3.761954e-03, 3.641364e-03, 3.530016e-03, 3.415101e-03, 3.298307e-03, 3.180346e-03, 3.058957e-03, 2.936859e-03, 2.813679e-03, 2.695057e-03, 2.575859e-03, 2.456212e-03, 2.333532e-03, 2.208627e-03, 2.086335e-03, 1.973344e-03, 1.859214e-03, 1.749932e-03, 1.650817e-03, 1.547272e-03, 1.446062e-03, 1.346114e-03, 1.251149e-03, 1.160678e-03, 1.076721e-03, 9.953578e-04, 9.160842e-04, 8.438969e-04, 7.661572e-04, 6.985366e-04, 6.335932e-04, 5.753021e-04, 5.190099e-04, 4.675408e-04, 4.157514e-04, 3.694176e-04, 3.282556e-04, 2.864811e-04, 2.514278e-04, 2.209945e-04, 1.936450e-04, 1.680835e-04, 1.452957e-04, 1.253437e-04, 1.090975e-04, 9.346363e-05, 8.046524e-05, 7.040124e-05, 6.168383e-05, 5.291980e-05, 4.524337e-05, 3.885235e-05, 3.342269e-05, 2.863639e-05, 2.517911e-05, 2.101129e-05, 1.781728e-05, 1.454224e-05, 1.086912e-05, 8.358240e-06, 6.380853e-06, 5.330650e-06, 3.443922e-06, 2.250523e-06, 6.845511e-07, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};

  // 具体参数含义见：https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html#id13
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_ABS, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  // mt->AddProperty("RAYLEIGH",      Rayleigh_energy,  Rayleigh_length,     Rayleigh_points);

  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy, COMPONENT);
  mt->AddProperty("SCINTILLATIONCOMPONENT2", PhotonEnergy, COMPONENT);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 300. * ns);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 300. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 0.56);
  mt->AddConstProperty("SCINTILLATIONYIELD2", 0.44);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 16); // 我的理解是6662keV的能量分辨率？

  mat->SetMaterialPropertiesTable(mt);

  return mat;
}


G4Material *MyMaterials::GOS(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{

  double standard_light_yield = 28000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *Gd = new G4Element("Gadolinium", "Gd", z = 64., a = 157.25 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *S = new G4Element("Bismuth", "S", z = 16, a = 32.06 * g / mole);

  G4Material *mat = new G4Material("GOS", density = 7.3 * g / cm3, 3);
  mat->AddElement(Gd, 2);
  mat->AddElement(O, 2);
  mat->AddElement(S, 1);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  // --- Refractive Index
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_ABS = {
      1.55369 * eV, 1.55759 * eV, 1.56151 * eV, 1.56546 * eV, 1.56942 * eV, 1.57340 * eV, 1.57741 * eV, 1.58143 * eV,
      1.58548 * eV, 1.58954 * eV, 1.59363 * eV, 1.59773 * eV, 1.60186 * eV, 1.60601 * eV, 1.61018 * eV, 1.61438 * eV,
      1.61859 * eV, 1.62283 * eV, 1.62709 * eV, 1.63137 * eV, 1.63568 * eV, 1.64000 * eV, 1.64435 * eV, 1.64873 * eV,
      1.65312 * eV, 1.65754 * eV, 1.66199 * eV, 1.66645 * eV, 1.67095 * eV, 1.67546 * eV, 1.68000 * eV, 1.68457 * eV,
      1.68916 * eV, 1.69377 * eV, 1.69841 * eV, 1.70308 * eV, 1.70777 * eV, 1.71249 * eV, 1.71723 * eV, 1.72200 * eV,
      1.72680 * eV, 1.73162 * eV, 1.73647 * eV, 1.74135 * eV, 1.74626 * eV, 1.75119 * eV, 1.75615 * eV, 1.76114 * eV,
      1.76616 * eV, 1.77120 * eV, 1.77628 * eV, 1.78138 * eV, 1.78652 * eV, 1.79168 * eV, 1.79687 * eV, 1.80210 * eV,
      1.80735 * eV, 1.81263 * eV, 1.81795 * eV, 1.82330 * eV, 1.82868 * eV, 1.83409 * eV, 1.83953 * eV, 1.84500 * eV,
      1.85051 * eV, 1.85605 * eV, 1.86162 * eV, 1.86723 * eV, 1.87287 * eV, 1.87855 * eV, 1.88426 * eV, 1.89000 * eV,
      1.89578 * eV, 1.90160 * eV, 1.90745 * eV, 1.91334 * eV, 1.91926 * eV, 1.92522 * eV, 1.93122 * eV, 1.93725 * eV,
      1.94333 * eV, 1.94944 * eV, 1.95559 * eV, 1.96178 * eV, 1.96800 * eV, 1.97427 * eV, 1.98058 * eV, 1.98693 * eV,
      1.99332 * eV, 1.99975 * eV, 2.00622 * eV, 2.01273 * eV, 2.01929 * eV, 2.02589 * eV, 2.03253 * eV, 2.03921 * eV,
      2.04594 * eV, 2.05272 * eV, 2.05954 * eV, 2.06640 * eV, 2.07331 * eV, 2.08027 * eV, 2.08728 * eV, 2.09433 * eV,
      2.10143 * eV, 2.10857 * eV, 2.11577 * eV, 2.12302 * eV, 2.13031 * eV, 2.13766 * eV, 2.14506 * eV, 2.15250 * eV,
      2.16000 * eV, 2.16756 * eV, 2.17516 * eV, 2.18282 * eV, 2.19053 * eV, 2.19830 * eV, 2.20612 * eV, 2.21400 * eV,
      2.22194 * eV, 2.22993 * eV, 2.23798 * eV, 2.24609 * eV, 2.25426 * eV, 2.26249 * eV, 2.27077 * eV, 2.27912 * eV,
      2.28753 * eV, 2.29600 * eV, 2.30454 * eV, 2.31314 * eV, 2.32180 * eV, 2.33053 * eV, 2.33932 * eV, 2.34819 * eV,
      2.35711 * eV, 2.36611 * eV, 2.37518 * eV, 2.38431 * eV, 2.39352 * eV, 2.40279 * eV, 2.41214 * eV, 2.42157 * eV,
      2.43106 * eV, 2.44063 * eV, 2.45028 * eV, 2.46000 * eV, 2.46980 * eV, 2.47968 * eV, 2.48964 * eV, 2.49968 * eV,
      2.50980 * eV, 2.52000 * eV, 2.53029 * eV, 2.54066 * eV, 2.55112 * eV, 2.56166 * eV, 2.57229 * eV, 2.58300 * eV,
      2.59381 * eV, 2.60471 * eV, 2.61570 * eV, 2.62678 * eV, 2.63796 * eV, 2.64924 * eV, 2.66061 * eV, 2.67207 * eV,
      2.68364 * eV, 2.69531 * eV, 2.70708 * eV, 2.71895 * eV, 2.73093 * eV, 2.74301 * eV, 2.75520 * eV, 2.76750 * eV,
      2.77991 * eV, 2.79244 * eV, 2.80507 * eV, 2.81782 * eV, 2.83069 * eV, 2.84367 * eV, 2.85678 * eV, 2.87000 * eV,
      2.88335 * eV, 2.89683 * eV, 2.91043 * eV, 2.92416 * eV, 2.93801 * eV, 2.95200 * eV, 2.96613 * eV, 2.98039 * eV,
      2.99479 * eV, 3.00933 * eV, 3.02400 * eV, 3.03883 * eV, 3.05380 * eV, 3.06892 * eV, 3.08418 * eV, 3.09960 * eV,
      3.11518 * eV, 3.13091 * eV, 3.14681 * eV, 3.16286 * eV, 3.17908 * eV, 3.19547 * eV, 3.21203 * eV, 3.22876 * eV,
      3.24566 * eV, 3.26274 * eV, 3.28001 * eV, 3.29745 * eV, 3.31509 * eV, 3.33291 * eV, 3.35092 * eV, 3.36914 * eV,
      3.38755 * eV, 3.40616 * eV, 3.42498 * eV, 3.44401 * eV, 3.46325 * eV, 3.48270 * eV, 3.50238 * eV, 3.52228 * eV,
      3.54241 * eV, 3.56276 * eV, 3.58336 * eV, 3.60419 * eV, 3.62527 * eV, 3.64659 * eV, 3.66817 * eV, 3.69001 * eV,
      3.71210 * eV, 3.73446 * eV, 3.75710 * eV, 3.78001 * eV, 3.80320 * eV, 3.82667 * eV, 3.85044 * eV, 3.87451 * eV,
      3.89887 * eV, 3.92355 * eV, 3.94854 * eV, 3.97385 * eV, 3.99949 * eV, 4.02546 * eV, 4.05177 * eV, 4.07843 * eV,
      4.10544 * eV, 4.13281 * eV, 4.16054 * eV, 4.18866 * eV, 4.21715 * eV, 4.24603 * eV, 4.27532 * eV, 4.30501 * eV,
      4.33511 * eV, 4.36564 * eV, 4.39660 * eV, 4.42801 * eV, 4.45986 * eV, 4.49218 * eV, 4.52497 * eV, 4.55824 * eV,
      4.59201 * eV, 4.62628 * eV, 4.66106 * eV, 4.69637 * eV, 4.73222 * eV, 4.76862 * eV, 4.80559 * eV, 4.84313 * eV,
      4.88127 * eV, 4.92001 * eV, 4.95937 * eV, 4.99936 * eV, 5.04001 * eV, 5.08132 * eV, 5.12331 * eV, 5.16601 * eV,
      5.20942 * eV, 5.25357 * eV, 5.29847 * eV, 5.34415 * eV, 5.39062 * eV, 5.43790 * eV, 5.48603 * eV, 5.53501 * eV,
      5.58487 * eV, 5.63565 * eV};

  std::vector<G4double> RefractiveIndex = {
      2.11651, 2.11655, 2.11658, 2.11661, 2.11664, 2.11667, 2.11670, 2.11673,
      2.11676, 2.11679, 2.11685, 2.11691, 2.11697, 2.11704, 2.11710, 2.11716,
      2.11722, 2.11728, 2.11734, 2.11740, 2.11747, 2.11753, 2.11759, 2.11765,
      2.11771, 2.11777, 2.11783, 2.11790, 2.11796, 2.11802, 2.11808, 2.11814,
      2.11821, 2.11828, 2.11834, 2.11842, 2.11849, 2.11858, 2.11866, 2.11876,
      2.11885, 2.11896, 2.11906, 2.11918, 2.11930, 2.11941, 2.11952, 2.11963,
      2.11974, 2.11985, 2.11996, 2.12008, 2.12022, 2.12037, 2.12053, 2.12069,
      2.12085, 2.12102, 2.12118, 2.12134, 2.12151, 2.12169, 2.12187, 2.12205,
      2.12224, 2.12242, 2.12262, 2.12282, 2.12302, 2.12322, 2.12343, 2.12363,
      2.12383, 2.12402, 2.12421, 2.12440, 2.12460, 2.12480, 2.12500, 2.12520,
      2.12541, 2.12562, 2.12582, 2.12603, 2.12624, 2.12646, 2.12670, 2.12695,
      2.12723, 2.12752, 2.12781, 2.12812, 2.12843, 2.12874, 2.12906, 2.12938,
      2.12971, 2.13005, 2.13040, 2.13075, 2.13111, 2.13149, 2.13187, 2.13227,
      2.13268, 2.13309, 2.13348, 2.13387, 2.13425, 2.13462, 2.13498, 2.13533,
      2.13567, 2.13600, 2.13632, 2.13664, 2.13697, 2.13731, 2.13765, 2.13800,
      2.13833, 2.13865, 2.13895, 2.13924, 2.13951, 2.13979, 2.14006, 2.14034,
      2.14063, 2.14091, 2.14121, 2.14152, 2.14183, 2.14216, 2.14250, 2.14284,
      2.14318, 2.14352, 2.14387, 2.14421, 2.14457, 2.14495, 2.14535, 2.14577,
      2.14620, 2.14665, 2.14713, 2.14763, 2.14815, 2.14869, 2.14923, 2.14977,
      2.15030, 2.15084, 2.15137, 2.15189, 2.15240, 2.15290, 2.15339, 2.15388,
      2.15435, 2.15481, 2.15526, 2.15570, 2.15613, 2.15655, 2.15695, 2.15734,
      2.15771, 2.15808, 2.15845, 2.15884, 2.15923, 2.15963, 2.16005, 2.16048,
      2.16092, 2.16138, 2.16186, 2.16235, 2.16289, 2.16346, 2.16408, 2.16474,
      2.16544, 2.16610, 2.16671, 2.16727, 2.16778, 2.16824, 2.16868, 2.16911,
      2.16951, 2.16990, 2.17027, 2.17060, 2.17088, 2.17111, 2.17128, 2.17141,
      2.17152, 2.17163, 2.17172, 2.17181, 2.17188, 2.17208, 2.17242, 2.17290,
      2.17352, 2.17428, 2.17514, 2.17612, 2.17719, 2.17838, 2.17965, 2.18081,
      2.18186, 2.18280, 2.18364, 2.18439, 2.18520, 2.18606, 2.18696, 2.18792,
      2.18892, 2.18973, 2.19035, 2.19077, 2.19099, 2.19102, 2.19107, 2.19115,
      2.19126, 2.19138, 2.19156, 2.19197, 2.19260, 2.19347, 2.19457, 2.19588,
      2.19722, 2.19860, 2.20001, 2.20145, 2.20294, 2.20452, 2.20621, 2.20800,
      2.20988, 2.21186, 2.21385, 2.21587, 2.21791, 2.21997, 2.22206, 2.22424,
      2.22650, 2.22885, 2.23129, 2.23386, 2.23667, 2.23972, 2.24300, 2.24653,
      2.25032, 2.25461, 2.25938, 2.26466, 2.27043, 2.27672, 2.28351, 2.29079,
      2.29856, 2.30682, 2.31561, 2.32505, 2.33515, 2.34591, 2.35733, 2.36918,
      2.37438, 2.37976, 2.38533, 2.39113, 2.39717, 2.40335, 2.40968, 2.41622,
      2.42302, 2.43010};

  std::vector<G4double> Absorption = {
      306.74520 * mm, 297.26304 * mm, 290.52204 * mm, 284.99272 * mm, 272.89041 * mm, 270.66131 * mm, 264.47562 * mm, 257.31102 * mm,
      252.48876 * mm, 249.45741 * mm, 247.09458 * mm, 246.69876 * mm, 234.90033 * mm, 232.86958 * mm, 235.03736 * mm, 233.86249 * mm,
      235.36066 * mm, 233.57979 * mm, 221.95655 * mm, 220.51788 * mm, 222.22112 * mm, 222.31698 * mm, 223.04992 * mm, 221.75579 * mm,
      227.32457 * mm, 228.99676 * mm, 231.11938 * mm, 236.37542 * mm, 233.56182 * mm, 234.21647 * mm, 233.91697 * mm, 228.47044 * mm,
      232.53553 * mm, 236.83727 * mm, 233.66821 * mm, 228.07102 * mm, 228.66511 * mm, 229.45889 * mm, 230.96608 * mm, 233.09428 * mm,
      228.94979 * mm, 229.12428 * mm, 227.60343 * mm, 228.14848 * mm, 227.62583 * mm, 223.96638 * mm, 221.73550 * mm, 221.25256 * mm,
      225.39774 * mm, 227.11056 * mm, 223.91316 * mm, 223.14576 * mm, 224.91443 * mm, 223.37265 * mm, 222.98195 * mm, 221.64733 * mm,
      218.18684 * mm, 217.36715 * mm, 217.76647 * mm, 220.08596 * mm, 222.83736 * mm, 223.03916 * mm, 223.82862 * mm, 225.12500 * mm,
      223.77222 * mm, 225.35214 * mm, 225.79560 * mm, 225.17460 * mm, 224.89636 * mm, 224.22765 * mm, 227.36401 * mm, 227.06886 * mm,
      225.22577 * mm, 225.28883 * mm, 224.64827 * mm, 228.13158 * mm, 229.75219 * mm, 229.40527 * mm, 228.57382 * mm, 223.26183 * mm,
      221.58433 * mm, 218.99092 * mm, 219.80581 * mm, 219.38763 * mm, 219.24013 * mm, 219.83911 * mm, 222.37302 * mm, 221.30438 * mm,
      223.34679 * mm, 221.88384 * mm, 223.28193 * mm, 225.33299 * mm, 224.53774 * mm, 225.95846 * mm, 228.71197 * mm, 228.26246 * mm,
      230.20063 * mm, 230.27808 * mm, 229.40795 * mm, 230.89960 * mm, 234.11836 * mm, 238.50325 * mm, 236.47017 * mm, 235.55875 * mm,
      237.38855 * mm, 237.19088 * mm, 236.80252 * mm, 239.02870 * mm, 238.61373 * mm, 239.66362 * mm, 237.46288 * mm, 233.57478 * mm,
      231.78612 * mm, 229.85821 * mm, 226.09495 * mm, 223.93386 * mm, 222.50989 * mm, 221.17167 * mm, 220.70901 * mm, 220.24326 * mm,
      219.25381 * mm, 217.71796 * mm, 217.88208 * mm, 218.12089 * mm, 216.02682 * mm, 214.92506 * mm, 214.27965 * mm, 211.44163 * mm,
      211.19528 * mm, 211.45955 * mm, 210.69372 * mm, 211.63709 * mm, 213.28735 * mm, 214.99630 * mm, 218.14153 * mm, 218.37770 * mm,
      216.20659 * mm, 216.05007 * mm, 215.12700 * mm, 213.81471 * mm, 211.26890 * mm, 208.59716 * mm, 207.52558 * mm, 206.83781 * mm,
      206.42373 * mm, 206.31117 * mm, 205.22807 * mm, 205.84232 * mm, 204.69697 * mm, 203.84137 * mm, 203.50375 * mm, 202.98864 * mm,
      202.34676 * mm, 200.82931 * mm, 198.93044 * mm, 198.21928 * mm, 199.93524 * mm, 202.51304 * mm, 203.87612 * mm, 203.08280 * mm,
      202.93795 * mm, 204.13753 * mm, 203.50950 * mm, 201.36620 * mm, 199.64205 * mm, 199.34975 * mm, 199.92542 * mm, 199.64198 * mm,
      199.79423 * mm, 199.38061 * mm, 199.02498 * mm, 197.12878 * mm, 194.90449 * mm, 193.52524 * mm, 192.40217 * mm, 192.30384 * mm,
      190.57158 * mm, 186.92882 * mm, 183.83365 * mm, 183.45025 * mm, 184.13688 * mm, 183.43123 * mm, 183.04898 * mm, 183.65744 * mm,
      183.31420 * mm, 181.18274 * mm, 179.53682 * mm, 178.29473 * mm, 177.34256 * mm, 177.13345 * mm, 176.21290 * mm, 176.59952 * mm,
      177.36243 * mm, 176.55166 * mm, 175.25735 * mm, 174.11657 * mm, 173.10860 * mm, 173.44854 * mm, 173.97557 * mm, 173.66964 * mm,
      174.78966 * mm, 177.28488 * mm, 178.42534 * mm, 178.26669 * mm, 179.61778 * mm, 177.40607 * mm, 174.43904 * mm, 172.76975 * mm,
      169.45612 * mm, 167.52894 * mm, 166.48115 * mm, 164.45587 * mm, 161.59323 * mm, 157.76382 * mm, 154.33437 * mm, 150.62754 * mm,
      146.37615 * mm, 140.86672 * mm, 136.05165 * mm, 131.25236 * mm, 125.09009 * mm, 119.42212 * mm, 114.40955 * mm, 109.56437 * mm,
      103.62241 * mm, 99.47601 * mm, 95.65570 * mm, 91.05247 * mm, 86.34451 * mm, 81.15177 * mm, 76.28774 * mm, 71.53227 * mm,
      66.67082 * mm, 61.47413 * mm, 55.77604 * mm, 49.88733 * mm, 44.39200 * mm, 39.63207 * mm, 35.49639 * mm, 31.89803 * mm,
      28.76796 * mm, 25.96727 * mm, 23.50224 * mm, 21.32173 * mm, 19.41965 * mm, 17.64399 * mm, 15.96829 * mm, 14.43310 * mm,
      13.02828 * mm, 11.69468 * mm, 10.37163 * mm, 9.07409 * mm, 7.78320 * mm, 6.54818 * mm, 5.35505 * mm, 4.28463 * mm,
      3.49850 * mm, 3.19350 * mm, 3.16486 * mm, 3.16557 * mm, 3.16632 * mm, 3.17301 * mm, 3.18604 * mm, 3.19832 * mm,
      3.20107 * mm, 3.20502 * mm, 3.21023 * mm, 3.21657 * mm, 3.22321 * mm, 3.22939 * mm, 3.23994 * mm, 3.24913 * mm,
      3.25533 * mm, 3.26512 * mm, 3.27466 * mm, 3.28228 * mm, 3.29095 * mm, 3.30257 * mm, 3.31313 * mm, 3.32324 * mm,
      3.32888 * mm, 3.33319 * mm, 3.33589 * mm, 3.33680 * mm, 3.34071 * mm, 3.34632 * mm, 3.35282 * mm, 3.35704 * mm,
      3.36292 * mm, 3.36783 * mm};
  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  // BGO的实测值，<0的部分用0代替
  std::vector<G4double> PhotonEnergy = {
      1.549802e+00 * eV, 1.553687e+00 * eV, 1.557590e+00 * eV, 1.561514e+00 * eV, 1.565457e+00 * eV, 1.569420e+00 * eV, 1.573403e+00 * eV, 1.577407e+00 * eV, 1.581431e+00 * eV, 1.585476e+00 * eV, 1.589541e+00 * eV, 1.593627e+00 * eV, 1.597734e+00 * eV, 1.601863e+00 * eV, 1.606013e+00 * eV, 1.610184e+00 * eV, 1.614378e+00 * eV, 1.618593e+00 * eV, 1.622830e+00 * eV, 1.627089e+00 * eV, 1.631371e+00 * eV, 1.635675e+00 * eV, 1.640003e+00 * eV, 1.644353e+00 * eV, 1.648726e+00 * eV, 1.653123e+00 * eV, 1.657543e+00 * eV, 1.661987e+00 * eV, 1.666454e+00 * eV, 1.670946e+00 * eV, 1.675462e+00 * eV, 1.680003e+00 * eV, 1.684568e+00 * eV, 1.689158e+00 * eV, 1.693773e+00 * eV, 1.698414e+00 * eV, 1.703080e+00 * eV, 1.707771e+00 * eV, 1.712489e+00 * eV, 1.717233e+00 * eV, 1.722003e+00 * eV, 1.726799e+00 * eV, 1.731623e+00 * eV, 1.736473e+00 * eV, 1.741351e+00 * eV, 1.746256e+00 * eV, 1.751189e+00 * eV, 1.756150e+00 * eV, 1.761139e+00 * eV, 1.766157e+00 * eV, 1.771203e+00 * eV, 1.776278e+00 * eV, 1.781382e+00 * eV, 1.786516e+00 * eV, 1.791679e+00 * eV, 1.796872e+00 * eV, 1.802096e+00 * eV, 1.807350e+00 * eV, 1.812634e+00 * eV, 1.817950e+00 * eV, 1.823297e+00 * eV, 1.828675e+00 * eV, 1.834086e+00 * eV, 1.839528e+00 * eV, 1.845003e+00 * eV, 1.850510e+00 * eV, 1.856051e+00 * eV, 1.861625e+00 * eV, 1.867232e+00 * eV, 1.872873e+00 * eV, 1.878548e+00 * eV, 1.884258e+00 * eV, 1.890003e+00 * eV, 1.895783e+00 * eV, 1.901598e+00 * eV, 1.907449e+00 * eV, 1.913336e+00 * eV, 1.919260e+00 * eV, 1.925220e+00 * eV, 1.931218e+00 * eV, 1.937253e+00 * eV, 1.943326e+00 * eV, 1.949437e+00 * eV, 1.955587e+00 * eV, 1.961775e+00 * eV, 1.968003e+00 * eV, 1.974271e+00 * eV, 1.980578e+00 * eV, 1.986926e+00 * eV, 1.993315e+00 * eV, 1.999745e+00 * eV, 2.006217e+00 * eV, 2.012730e+00 * eV, 2.019287e+00 * eV, 2.025886e+00 * eV, 2.032528e+00 * eV, 2.039214e+00 * eV, 2.045944e+00 * eV, 2.052718e+00 * eV, 2.059538e+00 * eV, 2.066403e+00 * eV, 2.073314e+00 * eV, 2.080272e+00 * eV, 2.087276e+00 * eV, 2.094328e+00 * eV, 2.101427e+00 * eV, 2.108575e+00 * eV, 2.115771e+00 * eV, 2.123017e+00 * eV, 2.130313e+00 * eV, 2.137659e+00 * eV, 2.145055e+00 * eV, 2.152503e+00 * eV, 2.160003e+00 * eV, 2.167556e+00 * eV, 2.175161e+00 * eV, 2.182820e+00 * eV, 2.190533e+00 * eV, 2.198301e+00 * eV, 2.206124e+00 * eV, 2.214003e+00 * eV, 2.221939e+00 * eV, 2.229932e+00 * eV, 2.237982e+00 * eV, 2.246090e+00 * eV, 2.254258e+00 * eV, 2.262485e+00 * eV, 2.270773e+00 * eV, 2.279121e+00 * eV, 2.287531e+00 * eV, 2.296004e+00 * eV, 2.304539e+00 * eV, 2.313138e+00 * eV, 2.321801e+00 * eV, 2.330530e+00 * eV, 2.339324e+00 * eV, 2.348185e+00 * eV, 2.357114e+00 * eV, 2.366111e+00 * eV, 2.375176e+00 * eV, 2.384311e+00 * eV, 2.393517e+00 * eV, 2.402794e+00 * eV, 2.412144e+00 * eV, 2.421566e+00 * eV, 2.431063e+00 * eV, 2.440634e+00 * eV, 2.450280e+00 * eV, 2.460004e+00 * eV, 2.469805e+00 * eV, 2.479684e+00 * eV, 2.489642e+00 * eV, 2.499681e+00 * eV, 2.509801e+00 * eV, 2.520004e+00 * eV, 2.530290e+00 * eV, 2.540660e+00 * eV, 2.551115e+00 * eV, 2.561657e+00 * eV, 2.572286e+00 * eV, 2.583004e+00 * eV, 2.593812e+00 * eV, 2.604710e+00 * eV, 2.615700e+00 * eV, 2.626784e+00 * eV, 2.637962e+00 * eV, 2.649235e+00 * eV, 2.660605e+00 * eV, 2.672073e+00 * eV, 2.683641e+00 * eV, 2.695309e+00 * eV, 2.707078e+00 * eV, 2.718952e+00 * eV, 2.730929e+00 * eV, 2.743013e+00 * eV, 2.755204e+00 * eV, 2.767504e+00 * eV, 2.779915e+00 * eV, 2.792437e+00 * eV, 2.805072e+00 * eV, 2.817823e+00 * eV, 2.830689e+00 * eV, 2.843674e+00 * eV, 2.856779e+00 * eV, 2.870004e+00 * eV, 2.883353e+00 * eV, 2.896827e+00 * eV, 2.910427e+00 * eV, 2.924155e+00 * eV, 2.938014e+00 * eV, 2.952005e+00 * eV, 2.966129e+00 * eV, 2.980389e+00 * eV, 2.994787e+00 * eV, 3.009325e+00 * eV, 3.024005e+00 * eV, 3.038828e+00 * eV, 3.053798e+00 * eV, 3.068916e+00 * eV, 3.084184e+00 * eV, 3.099605e+00 * eV, 3.115181e+00 * eV, 3.130914e+00 * eV, 3.146807e+00 * eV, 3.162862e+00 * eV, 3.179082e+00 * eV, 3.195469e+00 * eV, 3.212026e+00 * eV, 3.228755e+00 * eV, 3.245660e+00 * eV, 3.262742e+00 * eV, 3.280005e+00 * eV, 3.297452e+00 * eV, 3.315085e+00 * eV, 3.332908e+00 * eV, 3.350924e+00 * eV, 3.369136e+00 * eV, 3.387546e+00 * eV, 3.406159e+00 * eV, 3.424978e+00 * eV, 3.444005e+00 * eV, 3.463246e+00 * eV, 3.482702e+00 * eV, 3.502378e+00 * eV, 3.522278e+00 * eV, 3.542406e+00 * eV, 3.562764e+00 * eV, 3.583358e+00 * eV, 3.604192e+00 * eV, 3.625269e+00 * eV, 3.646594e+00 * eV, 3.668171e+00 * eV, 3.690006e+00 * eV, 3.712102e+00 * eV, 3.734464e+00 * eV, 3.757097e+00 * eV, 3.780006e+00 * eV, 3.803196e+00 * eV, 3.826673e+00 * eV, 3.850441e+00 * eV, 3.874506e+00 * eV, 3.898874e+00 * eV, 3.923550e+00 * eV, 3.948541e+00 * eV, 3.973852e+00 * eV, 3.999490e+00 * eV, 4.025461e+00 * eV, 4.051771e+00 * eV, 4.078427e+00 * eV, 4.105437e+00 * eV, 4.132806e+00 * eV};
  std::vector<G4double> COMPONENT = {
      1.795417e-04, 1.786151e-04, 1.901804e-04, 1.959447e-04, 2.001024e-04, 1.938566e-04, 1.961014e-04, 1.973287e-04, 2.087365e-04, 2.135325e-04, 2.192456e-04, 2.239214e-04, 2.215911e-04, 2.238145e-04, 2.237850e-04, 2.362284e-04, 2.438981e-04, 2.533980e-04, 2.566182e-04, 2.669541e-04, 2.745797e-04, 2.809080e-04, 2.850937e-04, 2.848920e-04, 2.943054e-04, 3.048122e-04, 3.196230e-04, 3.276818e-04, 3.351533e-04, 3.426957e-04, 3.511393e-04, 3.597513e-04, 3.739922e-04, 3.929031e-04, 4.042121e-04, 4.137157e-04, 4.227772e-04, 4.318461e-04, 4.404130e-04, 4.473946e-04, 4.624595e-04, 4.788674e-04, 4.931498e-04, 5.057651e-04, 5.236445e-04, 5.405128e-04, 5.537482e-04, 5.776754e-04, 6.009607e-04, 6.233158e-04, 6.389449e-04, 6.604322e-04, 6.801802e-04, 7.075546e-04, 7.278614e-04, 7.531377e-04, 7.790073e-04, 8.056500e-04, 8.228047e-04, 8.395150e-04, 8.592031e-04, 8.790582e-04, 9.013892e-04, 9.168929e-04, 9.459438e-04, 9.663072e-04, 9.964794e-04, 1.013899e-03, 1.047115e-03, 1.080429e-03, 1.116525e-03, 1.148477e-03, 1.184400e-03, 1.222023e-03, 1.250968e-03, 1.285432e-03, 1.319211e-03, 1.365481e-03, 1.403968e-03, 1.447824e-03, 1.495020e-03, 1.535997e-03, 1.577212e-03, 1.621277e-03, 1.669679e-03, 1.717932e-03, 1.766111e-03, 1.809391e-03, 1.859019e-03, 1.908667e-03, 1.958150e-03, 2.014780e-03, 2.068389e-03, 2.123111e-03, 2.174689e-03, 2.231942e-03, 2.286806e-03, 2.346232e-03, 2.400674e-03, 2.457963e-03, 2.517205e-03, 2.577904e-03, 2.641994e-03, 2.708524e-03, 2.774745e-03, 2.839390e-03, 2.902948e-03, 2.973889e-03, 3.041142e-03, 3.106289e-03, 3.171224e-03, 3.240158e-03, 3.306128e-03, 3.372595e-03, 3.438896e-03, 3.502954e-03, 3.568342e-03, 3.623061e-03, 3.691103e-03, 3.768035e-03, 3.829572e-03, 3.893561e-03, 3.959160e-03, 4.024525e-03, 4.096949e-03, 4.167950e-03, 4.235691e-03, 4.305421e-03, 4.372176e-03, 4.437749e-03, 4.504159e-03, 4.567637e-03, 4.630747e-03, 4.689614e-03, 4.745544e-03, 4.793665e-03, 4.850540e-03, 4.901355e-03, 4.953146e-03, 4.991928e-03, 5.037749e-03, 5.081095e-03, 5.128247e-03, 5.164043e-03, 5.197396e-03, 5.228879e-03, 5.259975e-03, 5.283603e-03, 5.304831e-03, 5.326737e-03, 5.342228e-03, 5.355112e-03, 5.354667e-03, 5.357832e-03, 5.350387e-03, 5.347919e-03, 5.331669e-03, 5.320124e-03, 5.293058e-03, 5.266065e-03, 5.229341e-03, 5.184701e-03, 5.144456e-03, 5.093333e-03, 5.047792e-03, 4.993973e-03, 4.934075e-03, 4.866365e-03, 4.802718e-03, 4.733542e-03, 4.666464e-03, 4.588775e-03, 4.500717e-03, 4.414503e-03, 4.311856e-03, 4.211021e-03, 4.105716e-03, 3.999065e-03, 3.882535e-03, 3.761954e-03, 3.641364e-03, 3.530016e-03, 3.415101e-03, 3.298307e-03, 3.180346e-03, 3.058957e-03, 2.936859e-03, 2.813679e-03, 2.695057e-03, 2.575859e-03, 2.456212e-03, 2.333532e-03, 2.208627e-03, 2.086335e-03, 1.973344e-03, 1.859214e-03, 1.749932e-03, 1.650817e-03, 1.547272e-03, 1.446062e-03, 1.346114e-03, 1.251149e-03, 1.160678e-03, 1.076721e-03, 9.953578e-04, 9.160842e-04, 8.438969e-04, 7.661572e-04, 6.985366e-04, 6.335932e-04, 5.753021e-04, 5.190099e-04, 4.675408e-04, 4.157514e-04, 3.694176e-04, 3.282556e-04, 2.864811e-04, 2.514278e-04, 2.209945e-04, 1.936450e-04, 1.680835e-04, 1.452957e-04, 1.253437e-04, 1.090975e-04, 9.346363e-05, 8.046524e-05, 7.040124e-05, 6.168383e-05, 5.291980e-05, 4.524337e-05, 3.885235e-05, 3.342269e-05, 2.863639e-05, 2.517911e-05, 2.101129e-05, 1.781728e-05, 1.454224e-05, 1.086912e-05, 8.358240e-06, 6.380853e-06, 5.330650e-06, 3.443922e-06, 2.250523e-06, 6.845511e-07, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};

  // 具体参数含义见：https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/physicsProcess.html#id13
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_ABS, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  // mt->AddProperty("RAYLEIGH",      Rayleigh_energy,  Rayleigh_length,     Rayleigh_points);

  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy, COMPONENT);
  mt->AddProperty("SCINTILLATIONCOMPONENT2", PhotonEnergy, COMPONENT);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3000. * ns);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 3000. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 0.56);
  mt->AddConstProperty("SCINTILLATIONYIELD2", 0.44);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 16); // 我的理解是6662keV的能量分辨率？

  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::GAGG_Ce_Mg(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{
  // ########################################################
  // ### GAGG:Ce:Mg in a more complete fashion.
  // ### - Index of refraction taken from:
  // ###         Kozlova NS, Buzanov OA, Kasimova VM, Kozlova AP, Zabelina EV (2018) Optical characteristics of single crystal Gd3Al2Ga3O12 : Ce. Modern Electronic Materials 4(1): 7–12. https://doi.org/10.3897/j.moem.4.1.33240
  // ### - Emission measured in Lab 27, CERN.                                                                         L. Martinazzoli                   (2020)
  // ### - Absorption calculated measuring transmission of different ILM GAGG:Ce (not codoped!) in Lab 27, CERN.      N. Kratochwil, L. Martinazzoli    (2019)
  // ########

double standard_light_yield = 40000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Ga = new G4Element("Gallium", "Ga", z = 31., a = 69.723 * g / mole);
  G4Element *Gd = new G4Element("Gadolinio", "Gd", z = 64., a = 157.25 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("GAGG_Ce_Mg", density = 6.63 * g / cm3, 4);
  mat->AddElement(Ga, 3);
  mat->AddElement(Gd, 3);
  mat->AddElement(Al, 2);
  mat->AddElement(O, 12);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);

  // --- Refractive Index
  // 适应geant4.11的新特性，使用vector来描述
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_RI = {1.23984 * eV,
                                           1.72271 * eV, 1.74623 * eV, 1.77132 * eV, 1.79807 * eV, 1.82468 * eV, 1.85209 * eV, 1.87931 * eV, 1.90734 * eV, 1.93840 * eV, 1.96824 * eV, 2.00017 * eV, 2.03315 * eV, 2.06599 * eV,
                                           2.10633 * eV, 2.13762 * eV, 2.17670 * eV, 2.21440 * eV, 2.25637 * eV, 2.29690 * eV, 2.34050 * eV, 2.38578 * eV, 2.42943 * eV, 2.53093 * eV, 2.58203 * eV, 2.63926 * eV, 2.69489 * eV,
                                           2.75950 * eV, 2.88396 * eV, 2.95302 * eV, 3.02545 * eV, 3.09601 * eV, 3.18161 * eV, 3.26590 * eV, 3.35473 * eV, 3.44161 * eV, 3.54034 * eV, 3.64512 * eV, 3.75608 * eV, 3.87418 * eV,
                                           3.99973 * eV, 4.13371 * eV, 4.27696 * eV, 4.43064 * eV, 4.59557 * eV, 4.76007 * eV, 4.95065 * eV, 5.15688 * eV, 5.38078 * eV, 5.62461 * eV};

  std::vector<G4double> RefractiveIndex = {1.8646638,
                                           1.87226, 1.87263, 1.87336, 1.87409, 1.87409, 1.87555, 1.87628, 1.87737, 1.87774, 1.87883, 1.87993, 1.88102, 1.88285, 1.88467,
                                           1.88613, 1.88832, 1.88942, 1.89015, 1.89234, 1.89307, 1.89453, 1.89599, 1.90073, 1.90401, 1.90547, 1.90693, 1.90839, 1.91277,
                                           1.91569, 1.92080, 1.91861, 1.91934, 1.91788, 1.92226, 1.93175, 1.94197, 1.93102, 1.93978, 1.93248, 1.94489, 1.95438, 1.96606,
                                           1.96752, 1.98212, 1.99818, 2.03102, 2.07628, 2.13394, 2.20912};

  // --- Intrinsic absorption spectrum
  //    Highest and Lowest energies are arbitrarily set.
  std::vector<G4double> PhotonEnergy_ABS =
      {1.49849 * eV, 1.50943 * eV, 1.52054 * eV, 1.53181 * eV, 1.54325 * eV, 1.55486 * eV, 1.56665 * eV, 1.57861 * eV, 1.59076 * eV,
       1.6031 * eV, 1.61564 * eV, 1.62837 * eV, 1.6413 * eV, 1.65444 * eV, 1.66779 * eV, 1.68136 * eV, 1.69515 * eV, 1.70917 * eV,
       1.72342 * eV, 1.73791 * eV, 1.75265 * eV, 1.76764 * eV, 1.78289 * eV, 1.7984 * eV, 1.81419 * eV, 1.83026 * eV, 1.84661 * eV,
       1.86326 * eV, 1.88021 * eV, 1.89748 * eV, 1.91506 * eV, 1.93297 * eV, 1.95122 * eV, 1.96982 * eV, 1.98877 * eV, 2.0081 * eV,
       2.0278 * eV, 2.04789 * eV, 2.06839 * eV, 2.0893 * eV, 2.11064 * eV, 2.13242 * eV, 2.15465 * eV, 2.17735 * eV, 2.20053 * eV,
       2.22422 * eV, 2.23022 * eV, 2.24231 * eV, 2.25455 * eV, 2.26691 * eV, 2.27941 * eV, 2.29205 * eV, 2.30483 * eV, 2.31776 * eV,
       2.33083 * eV, 2.34405 * eV, 2.35741 * eV, 2.37094 * eV, 2.38462 * eV, 2.39845 * eV, 2.41245 * eV, 2.42661 * eV, 2.44094 * eV,
       2.45545 * eV, 2.47012 * eV, 2.48497 * eV, 2.5 * eV, 2.51521 * eV, 2.53061 * eV, 2.5462 * eV, 2.56198 * eV, 2.57796 * eV,
       2.59414 * eV, 2.61053 * eV, 2.62712 * eV, 2.64392 * eV, 2.66094 * eV, 2.67819 * eV, 2.71335 * eV, 2.73128 * eV, 2.74945 * eV,
       2.76786 * eV, 2.78652 * eV, 2.80543 * eV, 2.8246 * eV, 2.84404 * eV, 2.86374 * eV, 2.88372 * eV, 2.90398 * eV, 2.92453 * eV,
       2.94537 * eV, 2.96651 * eV, 2.98795 * eV, 3.00971 * eV, 3.03178 * eV, 3.05419 * eV, 3.07692 * eV, 3.1 * eV, 3.12343 * eV,
       3.14721 * eV, 3.17136 * eV, 3.19588 * eV, 3.22078 * eV, 3.24607 * eV, 3.27177 * eV, 3.29787 * eV, 3.3244 * eV, 3.35135 * eV,
       3.37875 * eV, 3.40659 * eV, 3.4349 * eV, 3.46369 * eV, 3.49296 * eV, 3.52273 * eV, 3.58382 * eV, 3.61516 * eV, 3.67953 * eV,
       3.71257 * eV, 3.78049 * eV, 3.92405 * eV, 3.96166 * eV, 4 * eV, 4.03909 * eV, 4.07895 * eV, 4.1196 * eV, 4.16107 * eV,
       4.20339 * eV, 4.24658 * eV, 4.29066 * eV, 4.33566 * eV, 4.38163 * eV, 4.42857 * eV, 4.47653 * eV, 4.52555 * eV, 4.62687 * eV,
       4.67925 * eV, 4.78764 * eV, 4.96 * eV, 5.62461 * eV};

  std::vector<G4double> Absorption =
      {955.954000 * mm, 668.943000 * mm, 614.032000 * mm, 467.353000 * mm, 559.162000 * mm, 579.555000 * mm, 650.626000 * mm, 535.162000 * mm, 524.755000 * mm,
       540.255000 * mm, 600.531000 * mm, 519.526000 * mm, 526.569000 * mm, 516.447000 * mm, 502.306000 * mm, 518.467000 * mm, 522.762000 * mm, 503.951000 * mm,
       537.711000 * mm, 520.839000 * mm, 553.001000 * mm, 488.909000 * mm, 521.548000 * mm, 471.766000 * mm, 450.077000 * mm, 404.852000 * mm, 441.221000 * mm,
       440.960000 * mm, 411.248000 * mm, 380.195000 * mm, 399.852000 * mm, 380.692000 * mm, 372.110000 * mm, 362.841000 * mm, 370.628000 * mm, 355.130000 * mm,
       371.095000 * mm, 389.190000 * mm, 390.557000 * mm, 376.662000 * mm, 394.540000 * mm, 419.485000 * mm, 423.900000 * mm, 424.207000 * mm, 459.364000 * mm,
       432.117000 * mm, 450.723000 * mm, 444.802000 * mm, 451.629000 * mm, 415.643000 * mm, 458.704000 * mm, 473.048000 * mm, 388.097000 * mm, 445.714000 * mm,
       356.658000 * mm, 362.018000 * mm, 323.960000 * mm, 249.410000 * mm, 222.770000 * mm, 173.466000 * mm, 126.428000 * mm, 94.944500 * mm, 64.388500 * mm,
       45.198300 * mm, 30.697900 * mm, 20.705400 * mm, 14.095600 * mm, 9.563980 * mm, 6.555540 * mm, 4.590660 * mm, 3.251770 * mm, 2.439640 * mm, 1.899230 * mm,
       1.561530 * mm, 1.644290 * mm, 1.454600 * mm, 1.344050 * mm, 1.392430 * mm, 1.474630 * mm, 1.365870 * mm, 1.418190 * mm, 1.449410 * mm, 1.429420 * mm, 1.588940 * mm,
       1.456210 * mm, 1.313570 * mm, 1.626080 * mm, 1.611680 * mm, 1.429990 * mm, 1.472460 * mm, 1.501370 * mm, 1.565330 * mm, 1.556520 * mm, 1.413260 * mm, 1.651750 * mm,
       1.532130 * mm, 1.908330 * mm, 2.906480 * mm, 4.388340 * mm, 6.664950 * mm, 9.720680 * mm, 12.470900 * mm, 13.226400 * mm, 11.510300 * mm, 8.747250 * mm, 6.425540 * mm,
       4.638230 * mm, 3.356940 * mm, 2.389330 * mm, 1.730910 * mm, 1.621300 * mm, 1.349290 * mm, 1.371340 * mm, 1.454750 * mm, 1.353480 * mm, 1.092090 * mm, 1.486040 * mm,
       1.375890 * mm, 1.153950 * mm, 1.623740 * mm, 1.443300 * mm, 1.605000 * mm, 1.705960 * mm, 1.510680 * mm, 1.525980 * mm, 1.586010 * mm, 1.616290 * mm, 1.489230 * mm,
       1.483450 * mm, 1.411050 * mm, 1.685210 * mm, 1.409220 * mm, 1.232600 * mm, 1.707510 * mm, 1.382160 * mm, 1.322320 * mm, 1.441060 * mm, 1.478580 * mm, 0 * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  //      Taken straight outta the spectrophotometer.
  //      Hope this doesn't kill the performance.      O.o'
  std::vector<G4double> FAST_Energy = {1.425287 * eV, 1.426107 * eV, 1.426928 * eV, 1.427749 * eV, 1.428571 * eV, 1.429395 * eV, 1.430219 * eV, 1.431044 * eV, 1.431871 * eV, 1.432698 * eV, 1.433526 * eV, 1.434355 * eV,
                                       1.435185 * eV, 1.436016 * eV, 1.436848 * eV, 1.437681 * eV, 1.438515 * eV, 1.439350 * eV, 1.440186 * eV, 1.441023 * eV, 1.441860 * eV, 1.442699 * eV, 1.443539 * eV, 1.444380 * eV, 1.445221 * eV, 1.446064 * eV, 1.446908 * eV, 1.447752 * eV,
                                       1.448598 * eV, 1.449445 * eV, 1.450292 * eV, 1.451141 * eV, 1.451991 * eV, 1.452841 * eV, 1.453693 * eV, 1.454545 * eV, 1.455399 * eV, 1.456254 * eV, 1.457109 * eV, 1.457966 * eV, 1.458824 * eV, 1.459682 * eV, 1.460542 * eV, 1.461402 * eV,
                                       1.462264 * eV, 1.463127 * eV, 1.463991 * eV, 1.464855 * eV, 1.465721 * eV, 1.466588 * eV, 1.467456 * eV, 1.468324 * eV, 1.469194 * eV, 1.470065 * eV, 1.470937 * eV, 1.471810 * eV, 1.472684 * eV, 1.473559 * eV, 1.474435 * eV, 1.475312 * eV,
                                       1.476190 * eV, 1.477070 * eV, 1.477950 * eV, 1.478831 * eV, 1.479714 * eV, 1.480597 * eV, 1.481481 * eV, 1.482367 * eV, 1.483254 * eV, 1.484141 * eV, 1.485030 * eV, 1.485920 * eV, 1.486811 * eV, 1.487702 * eV, 1.488595 * eV, 1.489489 * eV,
                                       1.490385 * eV, 1.491281 * eV, 1.492178 * eV, 1.493076 * eV, 1.493976 * eV, 1.494876 * eV, 1.495778 * eV, 1.496681 * eV, 1.497585 * eV, 1.498489 * eV, 1.499395 * eV, 1.500302 * eV, 1.501211 * eV, 1.502120 * eV, 1.503030 * eV, 1.503942 * eV,
                                       1.504854 * eV, 1.505768 * eV, 1.506683 * eV, 1.507599 * eV, 1.508516 * eV, 1.509434 * eV, 1.510353 * eV, 1.511274 * eV, 1.512195 * eV, 1.513118 * eV, 1.514042 * eV, 1.514966 * eV, 1.515892 * eV, 1.516820 * eV, 1.517748 * eV, 1.518677 * eV,
                                       1.519608 * eV, 1.520540 * eV, 1.521472 * eV, 1.522406 * eV, 1.523342 * eV, 1.524278 * eV, 1.525215 * eV, 1.526154 * eV, 1.527094 * eV, 1.528035 * eV, 1.528977 * eV, 1.529920 * eV, 1.530864 * eV, 1.531810 * eV, 1.532756 * eV, 1.533704 * eV,
                                       1.534653 * eV, 1.535604 * eV, 1.536555 * eV, 1.537508 * eV, 1.538462 * eV, 1.539417 * eV, 1.540373 * eV, 1.541330 * eV, 1.542289 * eV, 1.543248 * eV, 1.544209 * eV, 1.545171 * eV, 1.546135 * eV, 1.547099 * eV, 1.548065 * eV, 1.549032 * eV,
                                       1.550000 * eV, 1.550969 * eV, 1.551940 * eV, 1.552912 * eV, 1.553885 * eV, 1.554859 * eV, 1.555834 * eV, 1.556811 * eV, 1.557789 * eV, 1.558768 * eV, 1.559748 * eV, 1.560730 * eV, 1.561713 * eV, 1.562697 * eV, 1.563682 * eV, 1.564669 * eV,
                                       1.565657 * eV, 1.566646 * eV, 1.567636 * eV, 1.568627 * eV, 1.569620 * eV, 1.570614 * eV, 1.571610 * eV, 1.572606 * eV, 1.573604 * eV, 1.574603 * eV, 1.575604 * eV, 1.576605 * eV, 1.577608 * eV, 1.578612 * eV, 1.579618 * eV, 1.580625 * eV, 1.581633 * eV, 1.582642 * eV, 1.583653 * eV, 1.584665 * eV, 1.585678 * eV, 1.586692 * eV, 1.587708 * eV,
                                       1.588725 * eV, 1.589744 * eV, 1.590763 * eV, 1.591784 * eV, 1.592807 * eV, 1.593830 * eV, 1.594855 * eV, 1.595882 * eV, 1.596909 * eV, 1.597938 * eV, 1.598968 * eV, 1.600000 * eV, 1.601033 * eV, 1.602067 * eV, 1.603103 * eV, 1.604140 * eV, 1.605178 * eV, 1.606218 * eV, 1.607259 * eV, 1.608301 * eV, 1.609345 * eV, 1.610390 * eV, 1.611436 * eV,
                                       1.612484 * eV, 1.613533 * eV, 1.614583 * eV, 1.615635 * eV, 1.616688 * eV, 1.617743 * eV, 1.618799 * eV, 1.619856 * eV, 1.620915 * eV, 1.621975 * eV, 1.623037 * eV, 1.624100 * eV, 1.625164 * eV, 1.626230 * eV, 1.627297 * eV, 1.628365 * eV, 1.629435 * eV, 1.630506 * eV, 1.631579 * eV, 1.632653 * eV, 1.633729 * eV, 1.634806 * eV, 1.635884 * eV,
                                       1.636964 * eV, 1.638045 * eV, 1.639128 * eV, 1.640212 * eV, 1.641297 * eV, 1.642384 * eV, 1.643472 * eV, 1.644562 * eV, 1.645654 * eV, 1.646746 * eV, 1.647841 * eV, 1.648936 * eV, 1.650033 * eV, 1.651132 * eV, 1.652232 * eV, 1.653333 * eV, 1.654436 * eV, 1.655541 * eV, 1.656647 * eV, 1.657754 * eV, 1.658863 * eV, 1.659973 * eV, 1.661085 * eV,
                                       1.662198 * eV, 1.663313 * eV, 1.664430 * eV, 1.665547 * eV, 1.666667 * eV, 1.667787 * eV, 1.668910 * eV, 1.670034 * eV, 1.671159 * eV, 1.672286 * eV, 1.673414 * eV, 1.674544 * eV, 1.675676 * eV, 1.676809 * eV, 1.677943 * eV, 1.679079 * eV, 1.680217 * eV, 1.681356 * eV, 1.682497 * eV, 1.683639 * eV, 1.684783 * eV, 1.685928 * eV, 1.687075 * eV,
                                       1.688223 * eV, 1.689373 * eV, 1.690525 * eV, 1.691678 * eV, 1.692833 * eV, 1.693989 * eV, 1.695147 * eV, 1.696306 * eV, 1.697467 * eV, 1.698630 * eV, 1.699794 * eV, 1.700960 * eV, 1.702128 * eV, 1.703297 * eV, 1.704467 * eV, 1.705640 * eV, 1.706813 * eV, 1.707989 * eV, 1.709166 * eV, 1.710345 * eV, 1.711525 * eV, 1.712707 * eV, 1.713891 * eV,
                                       1.715076 * eV, 1.716263 * eV, 1.717452 * eV, 1.718642 * eV, 1.719834 * eV, 1.721027 * eV, 1.722222 * eV, 1.723419 * eV, 1.724618 * eV, 1.725818 * eV, 1.727019 * eV, 1.728223 * eV, 1.729428 * eV, 1.730635 * eV, 1.731844 * eV, 1.733054 * eV, 1.734266 * eV, 1.735479 * eV, 1.736695 * eV, 1.737912 * eV, 1.739130 * eV, 1.740351 * eV, 1.741573 * eV,
                                       1.742797 * eV, 1.744023 * eV, 1.745250 * eV, 1.746479 * eV, 1.747710 * eV, 1.748942 * eV, 1.750176 * eV, 1.751412 * eV, 1.752650 * eV, 1.753890 * eV, 1.755131 * eV, 1.756374 * eV, 1.757619 * eV, 1.758865 * eV, 1.760114 * eV, 1.761364 * eV, 1.762615 * eV, 1.763869 * eV, 1.765125 * eV, 1.766382 * eV, 1.767641 * eV, 1.768902 * eV, 1.770164 * eV,
                                       1.771429 * eV, 1.772695 * eV, 1.773963 * eV, 1.775233 * eV, 1.776504 * eV, 1.777778 * eV, 1.779053 * eV, 1.780330 * eV, 1.781609 * eV, 1.782890 * eV, 1.784173 * eV, 1.785457 * eV, 1.786744 * eV, 1.788032 * eV, 1.789322 * eV, 1.790614 * eV, 1.791908 * eV, 1.793203 * eV, 1.794501 * eV,
                                       1.795800 * eV, 1.797101 * eV, 1.798405 * eV, 1.799710 * eV, 1.801017 * eV, 1.802326 * eV, 1.803636 * eV, 1.804949 * eV, 1.806264 * eV, 1.807580 * eV, 1.808899 * eV, 1.810219 * eV, 1.811541 * eV, 1.812865 * eV, 1.814192 * eV, 1.815520 * eV, 1.816850 * eV, 1.818182 * eV, 1.819516 * eV, 1.820852 * eV, 1.822190 * eV, 1.823529 * eV, 1.824871 * eV,
                                       1.826215 * eV, 1.827561 * eV, 1.828909 * eV, 1.830258 * eV, 1.831610 * eV, 1.832964 * eV, 1.834320 * eV, 1.835677 * eV, 1.837037 * eV, 1.838399 * eV, 1.839763 * eV, 1.841128 * eV, 1.842496 * eV, 1.843866 * eV, 1.845238 * eV, 1.846612 * eV, 1.847988 * eV, 1.849366 * eV, 1.850746 * eV, 1.852128 * eV, 1.853513 * eV, 1.854899 * eV, 1.856287 * eV,
                                       1.857678 * eV, 1.859070 * eV, 1.860465 * eV, 1.861862 * eV, 1.863261 * eV, 1.864662 * eV, 1.866065 * eV, 1.867470 * eV, 1.868877 * eV, 1.870287 * eV, 1.871698 * eV, 1.873112 * eV, 1.874528 * eV, 1.875946 * eV, 1.877366 * eV, 1.878788 * eV, 1.880212 * eV, 1.881639 * eV, 1.883068 * eV, 1.884498 * eV, 1.885932 * eV, 1.887367 * eV, 1.888804 * eV,
                                       1.890244 * eV, 1.891686 * eV, 1.893130 * eV, 1.894576 * eV, 1.896024 * eV, 1.897475 * eV, 1.898928 * eV, 1.900383 * eV, 1.901840 * eV, 1.903300 * eV, 1.904762 * eV, 1.906226 * eV, 1.907692 * eV, 1.909161 * eV, 1.910632 * eV, 1.912105 * eV, 1.913580 * eV, 1.915058 * eV, 1.916538 * eV, 1.918020 * eV, 1.919505 * eV, 1.920991 * eV, 1.922481 * eV,
                                       1.923972 * eV, 1.925466 * eV, 1.926962 * eV, 1.928460 * eV, 1.929961 * eV, 1.931464 * eV, 1.932970 * eV, 1.934477 * eV, 1.935988 * eV, 1.937500 * eV, 1.939015 * eV, 1.940532 * eV, 1.942052 * eV, 1.943574 * eV, 1.945098 * eV, 1.946625 * eV, 1.948154 * eV, 1.949686 * eV, 1.951220 * eV, 1.952756 * eV, 1.954295 * eV, 1.955836 * eV, 1.957380 * eV,
                                       1.958926 * eV, 1.960474 * eV, 1.962025 * eV, 1.963579 * eV, 1.965135 * eV, 1.966693 * eV, 1.968254 * eV, 1.969817 * eV, 1.971383 * eV, 1.972951 * eV, 1.974522 * eV, 1.976096 * eV, 1.977671 * eV, 1.979250 * eV, 1.980831 * eV, 1.982414 * eV, 1.984000 * eV, 1.985588 * eV, 1.987179 * eV, 1.988773 * eV, 1.990369 * eV, 1.991968 * eV, 1.993569 * eV,
                                       1.995173 * eV, 1.996779 * eV, 1.998388 * eV, 2.000000 * eV, 2.001614 * eV, 2.003231 * eV, 2.004850 * eV, 2.006472 * eV, 2.008097 * eV, 2.009724 * eV, 2.011354 * eV, 2.012987 * eV, 2.014622 * eV, 2.016260 * eV, 2.017901 * eV, 2.019544 * eV, 2.021190 * eV, 2.022838 * eV, 2.024490 * eV, 2.026144 * eV, 2.027800 * eV, 2.029460 * eV, 2.031122 * eV,
                                       2.032787 * eV, 2.034454 * eV, 2.036125 * eV, 2.037798 * eV, 2.039474 * eV, 2.041152 * eV, 2.042834 * eV, 2.044518 * eV, 2.046205 * eV, 2.047894 * eV, 2.049587 * eV, 2.051282 * eV, 2.052980 * eV, 2.054681 * eV, 2.056385 * eV, 2.058091 * eV, 2.059801 * eV, 2.061513 * eV, 2.063228 * eV, 2.064946 * eV, 2.066667 * eV, 2.068390 * eV, 2.070117 * eV,
                                       2.071846 * eV, 2.073579 * eV, 2.075314 * eV, 2.077052 * eV, 2.078793 * eV, 2.080537 * eV, 2.082284 * eV, 2.084034 * eV, 2.085786 * eV, 2.087542 * eV, 2.089301 * eV, 2.091062 * eV, 2.092827 * eV, 2.094595 * eV, 2.096365 * eV, 2.098139 * eV, 2.099915 * eV, 2.101695 * eV, 2.103478 * eV,
                                       2.105263 * eV, 2.107052 * eV, 2.108844 * eV, 2.110638 * eV, 2.112436 * eV, 2.114237 * eV, 2.116041 * eV, 2.117848 * eV, 2.119658 * eV, 2.121471 * eV, 2.123288 * eV, 2.125107 * eV, 2.126930 * eV, 2.128755 * eV, 2.130584 * eV, 2.132416 * eV, 2.134251 * eV, 2.136090 * eV, 2.137931 * eV, 2.139776 * eV, 2.141623 * eV, 2.143475 * eV, 2.145329 * eV,
                                       2.147186 * eV, 2.149047 * eV, 2.150911 * eV, 2.152778 * eV, 2.154648 * eV, 2.156522 * eV, 2.158399 * eV, 2.160279 * eV, 2.162162 * eV, 2.164049 * eV, 2.165939 * eV, 2.167832 * eV, 2.169729 * eV, 2.171629 * eV, 2.173532 * eV, 2.175439 * eV, 2.177349 * eV, 2.179262 * eV, 2.181179 * eV, 2.183099 * eV, 2.185022 * eV, 2.186949 * eV, 2.188879 * eV,
                                       2.190813 * eV, 2.192750 * eV, 2.194690 * eV, 2.196634 * eV, 2.198582 * eV, 2.200532 * eV, 2.202487 * eV, 2.204444 * eV, 2.206406 * eV, 2.208370 * eV, 2.210339 * eV, 2.212310 * eV, 2.214286 * eV, 2.216265 * eV, 2.218247 * eV, 2.220233 * eV, 2.222222 * eV, 2.224215 * eV, 2.226212 * eV, 2.228212 * eV, 2.230216 * eV, 2.232223 * eV, 2.234234 * eV,
                                       2.236249 * eV, 2.238267 * eV, 2.240289 * eV, 2.242315 * eV, 2.244344 * eV, 2.246377 * eV, 2.248413 * eV, 2.250454 * eV, 2.252498 * eV, 2.254545 * eV, 2.256597 * eV, 2.258652 * eV, 2.260711 * eV, 2.262774 * eV, 2.264840 * eV, 2.266910 * eV, 2.268984 * eV, 2.271062 * eV, 2.273144 * eV, 2.275229 * eV, 2.277319 * eV, 2.279412 * eV, 2.281509 * eV,
                                       2.283610 * eV, 2.285714 * eV, 2.287823 * eV, 2.289935 * eV, 2.292052 * eV, 2.294172 * eV, 2.296296 * eV, 2.298424 * eV, 2.300557 * eV, 2.302693 * eV, 2.304833 * eV, 2.306977 * eV, 2.309125 * eV, 2.311277 * eV, 2.313433 * eV, 2.315593 * eV, 2.317757 * eV, 2.319925 * eV, 2.322097 * eV, 2.324274 * eV, 2.326454 * eV, 2.328638 * eV, 2.330827 * eV,
                                       2.333020 * eV, 2.335217 * eV, 2.337418 * eV, 2.339623 * eV, 2.341832 * eV, 2.344045 * eV, 2.346263 * eV, 2.348485 * eV, 2.350711 * eV, 2.352941 * eV, 2.355176 * eV, 2.357414 * eV, 2.359657 * eV, 2.361905 * eV, 2.364156 * eV, 2.366412 * eV, 2.368672 * eV, 2.370937 * eV, 2.373206 * eV, 2.375479 * eV, 2.377756 * eV, 2.380038 * eV, 2.382325 * eV,
                                       2.384615 * eV, 2.386910 * eV, 2.389210 * eV, 2.391514 * eV, 2.393822 * eV, 2.396135 * eV, 2.398453 * eV, 2.400774 * eV, 2.403101 * eV, 2.405432 * eV, 2.407767 * eV, 2.410107 * eV, 2.412451 * eV, 2.414800 * eV, 2.417154 * eV, 2.419512 * eV, 2.421875 * eV, 2.424242 * eV, 2.426614 * eV, 2.428991 * eV, 2.431373 * eV, 2.433759 * eV, 2.436149 * eV,
                                       2.438545 * eV, 2.440945 * eV, 2.443350 * eV, 2.445759 * eV, 2.448174 * eV, 2.450593 * eV, 2.453017 * eV, 2.455446 * eV, 2.457879 * eV, 2.460317 * eV, 2.462761 * eV, 2.465209 * eV, 2.467662 * eV, 2.470120 * eV, 2.472582 * eV, 2.475050 * eV, 2.477522 * eV, 2.480000 * eV, 2.482482 * eV, 2.484970 * eV, 2.487462 * eV, 2.489960 * eV, 2.492462 * eV,
                                       2.494970 * eV, 2.497482 * eV, 2.500000 * eV, 2.502523 * eV, 2.505051 * eV, 2.507583 * eV, 2.510121 * eV, 2.512665 * eV, 2.515213 * eV, 2.517766 * eV, 2.520325 * eV, 2.522889 * eV, 2.525458 * eV, 2.528033 * eV, 2.530612 * eV, 2.533197 * eV, 2.535787 * eV, 2.538383 * eV, 2.540984 * eV,
                                       2.543590 * eV, 2.546201 * eV, 2.548818 * eV, 2.551440 * eV, 2.554068 * eV, 2.556701 * eV, 2.559340 * eV, 2.561983 * eV, 2.564633 * eV, 2.567288 * eV, 2.569948 * eV, 2.572614 * eV, 2.575286 * eV, 2.577963 * eV, 2.580645 * eV, 2.583333 * eV, 2.586027 * eV, 2.588727 * eV, 2.591432 * eV, 2.594142 * eV, 2.596859 * eV, 2.599581 * eV, 2.602308 * eV};

  std::vector<G4double> FAST_COMPONENT = {0.160333, 0.172055, 0.180528, 0.185841, 0.188323, 0.188954, 0.186772, 0.182738, 0.178573, 0.175773, 0.174867, 0.173955, 0.172557, 0.171364, 0.170930, 0.170360, 0.168857, 0.167288, 0.165351, 0.163923, 0.162677, 0.161678, 0.161048, 0.160843, 0.160919, 0.160517, 0.160686, 0.160464,
                                          0.159976, 0.159308, 0.158286, 0.157136, 0.155732, 0.154752, 0.154047, 0.153539, 0.153576, 0.154763, 0.156705, 0.158406, 0.159616, 0.159562, 0.158966, 0.157962, 0.155876, 0.153398, 0.152418, 0.152958, 0.154043, 0.155506, 0.156696, 0.158246, 0.159557, 0.160035, 0.159984, 0.160655,
                                          0.161680, 0.162683, 0.163751, 0.164225, 0.164384, 0.163716, 0.162927, 0.161685, 0.161064, 0.161583, 0.163290, 0.166036, 0.169015, 0.172248, 0.174792, 0.177343, 0.178371, 0.179139, 0.179470, 0.179794, 0.180614, 0.181098, 0.181929, 0.182751, 0.184452, 0.184796, 0.185040, 0.185164,
                                          0.185262, 0.185692, 0.185288, 0.185155, 0.185544, 0.186761, 0.186675, 0.186026, 0.185206, 0.184357, 0.184081, 0.182930, 0.180970, 0.179324, 0.178990, 0.178807, 0.178816, 0.179548, 0.180189, 0.181705, 0.183860, 0.185555, 0.186864, 0.187659, 0.186991, 0.185885, 0.184938, 0.182451,
                                          0.179253, 0.176828, 0.175065, 0.174352, 0.174345, 0.174170, 0.174635, 0.176360, 0.177780, 0.178376, 0.179079, 0.179967, 0.180717, 0.181527, 0.182005, 0.182501, 0.182777, 0.182598, 0.181987, 0.181748, 0.181893, 0.182113, 0.182613, 0.182965, 0.183928, 0.184883, 0.185172, 0.185290,
                                          0.185926, 0.187299, 0.189183, 0.192071, 0.194687, 0.197445, 0.200288, 0.202261, 0.203751, 0.204776, 0.205879, 0.207200, 0.209689, 0.212624, 0.215543, 0.218708, 0.221917, 0.225334, 0.228164, 0.231296, 0.234249, 0.238200, 0.242831, 0.246744, 0.249958, 0.252404, 0.254520, 0.255287,
                                          0.255467, 0.255138, 0.255251, 0.256250, 0.257098, 0.258633, 0.260698, 0.263629, 0.266652, 0.269514, 0.271993, 0.274103, 0.275915, 0.276758, 0.277352, 0.277538, 0.277770, 0.278430, 0.279565, 0.280986, 0.282494, 0.284023, 0.284981, 0.285279, 0.285089, 0.284264, 0.283283, 0.282408,
                                          0.281352, 0.280817, 0.280748, 0.280999, 0.281389, 0.282203, 0.283156, 0.284094, 0.284769, 0.284727, 0.285041, 0.285578, 0.286377, 0.286919, 0.287022, 0.287172, 0.287323, 0.286838, 0.286101, 0.285711, 0.285562, 0.286258, 0.287810, 0.289147, 0.290564, 0.291878, 0.292197, 0.291950,
                                          0.291027, 0.289650, 0.288632, 0.288382, 0.288782, 0.289809, 0.290986, 0.292057, 0.293552, 0.294994, 0.296213, 0.297359, 0.298379, 0.299725, 0.301065, 0.301758,
                                          0.302152, 0.302418, 0.302455, 0.302965, 0.303988, 0.305269, 0.307792, 0.311004, 0.314233, 0.317157, 0.319612, 0.321208, 0.322833, 0.323933, 0.324668, 0.325648, 0.326384, 0.327127, 0.327983, 0.329782, 0.331478, 0.334153, 0.337734, 0.342331, 0.347829, 0.353863, 0.359909, 0.365554,
                                          0.371182, 0.375309, 0.378078, 0.380650, 0.383559, 0.386661, 0.391209, 0.396554, 0.403391, 0.412262, 0.421569, 0.430263, 0.438646, 0.446296, 0.452533, 0.459093, 0.464611, 0.470111, 0.475587, 0.480986, 0.486321, 0.492086, 0.497950, 0.503656, 0.510915, 0.518411, 0.525585, 0.531775,
                                          0.537243, 0.541844, 0.545787, 0.548832, 0.551114, 0.554734, 0.560204, 0.566683, 0.574083, 0.582899, 0.591700, 0.599719, 0.606075, 0.610675, 0.613892, 0.616678, 0.619201, 0.621949, 0.626338, 0.631770, 0.637622, 0.643314, 0.648892, 0.654411, 0.659824, 0.665181, 0.670375, 0.676088,
                                          0.683226, 0.690607, 0.698531, 0.708160, 0.718258, 0.728716, 0.739570, 0.751581, 0.763034, 0.775454, 0.786540, 0.797086, 0.808549, 0.820140, 0.831665, 0.843176, 0.856263, 0.868398, 0.881225, 0.892920, 0.904357, 0.915893, 0.928096, 0.939263, 0.948868, 0.959247, 0.969073, 0.979514,
                                          0.991217, 1.006180, 1.022176, 1.040957, 1.060646, 1.080315, 1.099629, 1.117168, 1.132367, 1.143713, 1.154007, 1.162971, 1.172804, 1.183047, 1.193364, 1.204806, 1.218254, 1.233768, 1.249340, 1.264735, 1.280843, 1.298822, 1.316305, 1.333060, 1.349401, 1.365012, 1.381080, 1.398043,
                                          1.414998, 1.433156, 1.453538, 1.475149, 1.497840, 1.522714, 1.549153, 1.575589, 1.602703, 1.629766, 1.657771, 1.686157, 1.713829, 1.740740, 1.768848, 1.797099, 1.826433, 1.856914, 1.887414, 1.920113, 1.952943, 1.984931, 2.016673, 2.048364, 2.080761, 2.114546, 2.150983, 2.187603,
                                          2.227391, 2.267608, 2.308318, 2.349979, 2.391574, 2.432560, 2.473686, 2.517020, 2.560338, 2.606682, 2.652806, 2.697589, 2.740990, 2.782212, 2.822549, 2.863372, 2.906545, 2.951182, 2.999788, 3.049974, 3.101279, 3.150571, 3.197309, 3.241397, 3.282194, 3.319780, 3.355298, 3.394046,
                                          3.434711, 3.481092, 3.529849, 3.581205, 3.636162, 3.692668, 3.749120, 3.806017, 3.865440, 3.920449, 3.976139, 4.028575, 4.079399, 4.129317, 4.178763, 4.227938, 4.276508, 4.328505, 4.377710, 4.431798, 4.485211, 4.542401, 4.602420, 4.665596, 4.733517, 4.805294, 4.881597, 4.955312,
                                          5.031172, 5.103682, 5.172749, 5.236611, 5.298137, 5.359899, 5.419967, 5.482172, 5.543176, 5.605148, 5.670492, 5.740138, 5.814321, 5.895414, 5.981730, 6.071641, 6.164834, 6.256723, 6.343300, 6.426013, 6.507092, 6.584824, 6.664619, 6.745062, 6.824841, 6.905505, 6.987358, 7.068448,
                                          7.145806, 7.223107, 7.299318, 7.382849, 7.469975, 7.558261, 7.648318, 7.739405, 7.832896, 7.927704, 8.024399, 8.117990, 8.213648, 8.309669, 8.403208, 8.491036, 8.573814, 8.653141, 8.732364, 8.812956, 8.896425, 8.982942, 9.074628, 9.172558, 9.271829, 9.373102, 9.471807, 9.568671, 9.664489, 9.764401, 9.862431, 9.961527,
                                          10.062514, 10.162395, 10.267956, 10.377316, 10.486914, 10.593941, 10.704643, 10.812764, 10.922728, 11.031806, 11.136382, 11.240701, 11.348914, 11.457710, 11.560809, 11.666111, 11.769687, 11.873744, 11.982856, 12.091494, 12.195096, 12.306485, 12.424388, 12.538396, 12.649503,
                                          12.755230, 12.852457, 12.955026, 13.057408, 13.151514, 13.249479, 13.360196, 13.475367, 13.590405, 13.703543, 13.809648, 13.920157, 14.030500, 14.136132, 14.234845, 14.337392, 14.440752, 14.542470, 14.643342, 14.742330, 14.837359, 14.933357, 15.030482, 15.121741, 15.217645,
                                          15.311870, 15.403404, 15.499368, 15.605598, 15.711020, 15.818623, 15.928037, 16.034052, 16.143130, 16.247351, 16.339258, 16.425389, 16.516449, 16.606260, 16.696443, 16.790204, 16.882196, 16.980250, 17.080543, 17.177801, 17.265764, 17.349557, 17.429280, 17.505393, 17.582362,
                                          17.656297, 17.732708, 17.816212, 17.908350, 18.003255, 18.095199, 18.181472, 18.269397, 18.354728, 18.434323, 18.510606, 18.596313, 18.693102, 18.802602, 18.911997, 19.015629, 19.124369, 19.229364, 19.323701, 19.402913, 19.483465, 19.560596, 19.641053, 19.718309, 19.792413,
                                          19.869586, 19.949725, 20.026719, 20.095968, 20.171002, 20.255738, 20.345770, 20.434825, 20.524169, 20.604079, 20.677508, 20.741404, 20.794106, 20.843678, 20.898596, 20.953907, 21.011152, 21.081034, 21.153868, 21.230743, 21.305027, 21.372700, 21.432274, 21.489282, 21.538526,
                                          21.580936, 21.626996, 21.670602, 21.712001, 21.748164, 21.781695, 21.812616, 21.837206, 21.857631, 21.878914, 21.906131, 21.934830, 21.957913, 21.976860, 21.991334, 22.003585, 22.005043, 21.998509, 21.990289, 21.987864, 21.988827, 21.987035, 21.980584, 21.963873, 21.947645,
                                          21.926436, 21.896811, 21.859359, 21.814038, 21.758221,
                                          21.698002, 21.635145, 21.566074, 21.493923, 21.423607, 21.353887, 21.278387, 21.189528, 21.081072, 20.957433, 20.818778, 20.670547, 20.513037, 20.350933, 20.191659, 20.036380, 19.873308, 19.701685, 19.519604, 19.329683, 19.135690, 18.936732, 18.729052, 18.519217, 18.310576,
                                          18.094135, 17.867046, 17.627899, 17.378721, 17.118091, 16.853280, 16.576317, 16.292254, 16.011360, 15.733297, 15.457866, 15.182900, 14.905330, 14.621737, 14.337595, 14.046097, 13.746192, 13.443646, 13.141727, 12.844686, 12.550631, 12.257647, 11.962531, 11.666829, 11.369029,
                                          11.064639, 10.758183, 10.449219, 10.146628,
                                          9.845579, 9.550573, 9.256683, 8.963058, 8.669924, 8.372660, 8.075375, 7.777387, 7.485712, 7.198002, 6.920792, 6.650151, 6.388837, 6.131463, 5.875763, 5.623275, 5.370905, 5.120390, 4.872820, 4.632578, 4.396777, 4.168619, 3.945906, 3.727595, 3.515392, 3.310932, 3.113700, 2.926979,
                                          2.751590, 2.588683, 2.439079, 2.300711, 2.169602, 2.044509, 1.925282, 1.810431, 1.701355, 1.600311, 1.508377, 1.428058, 1.361947, 1.306719, 1.260604, 1.221590, 1.187067, 1.155297, 1.125212, 1.094388, 1.064629, 1.039276, 1.018386, 1.002130, 0.991032, 0.985420, 0.984140};

G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  // mt->AddProperty("RAYLEIGH",      Rayleigh_energy,  Rayleigh_length,     Rayleigh_points);

  mt->AddProperty("SCINTILLATIONCOMPONENT1", FAST_Energy, FAST_COMPONENT);
  mt->AddProperty("SCINTILLATIONCOMPONENT2", FAST_Energy, FAST_COMPONENT);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 59. * ns);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 180. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 0.56);
  mt->AddConstProperty("SCINTILLATIONYIELD2", 0.44);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 4.8);

  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::GAGG_ILM(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{
  // ########################################################
  // ### GAGG:Ce:Mg in a more complete fashion.
  // ### - Index of refraction taken from:
  // ###         Kozlova NS, Buzanov OA, Kasimova VM, Kozlova AP, Zabelina EV (2018) Optical characteristics of single crystal Gd3Al2Ga3O12 : Ce. Modern Electronic Materials 4(1): 7–12. https://doi.org/10.3897/j.moem.4.1.33240
  // ### - Emission measured in Lab 27, CERN.                                                                         L. Martinazzoli                   (2020)
  // ### - Absorption calculated measuring transmission of different ILM GAGG:Ce (not codoped!) in Lab 27, CERN.      N. Kratochwil, L. Martinazzoli    (2019)
  // ########

  double standard_light_yield = 30000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Ga = new G4Element("Gallium", "Ga", z = 31., a = 69.723 * g / mole);
  G4Element *Gd = new G4Element("Gadolinio", "Gd", z = 64., a = 157.25 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("GAGG_ILM", density = 6.63 * g / cm3, 4);
  mat->AddElement(Ga, 3);
  mat->AddElement(Gd, 3);
  mat->AddElement(Al, 2);
  mat->AddElement(O, 12);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);
  //--------//

  // --- Refractive Index
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_RI = {1.23984 * eV,
                                           1.72271 * eV, 1.74623 * eV, 1.77132 * eV, 1.79807 * eV, 1.82468 * eV, 1.85209 * eV, 1.87931 * eV, 1.90734 * eV, 1.93840 * eV, 1.96824 * eV, 2.00017 * eV, 2.03315 * eV, 2.06599 * eV,
                                           2.10633 * eV, 2.13762 * eV, 2.17670 * eV, 2.21440 * eV, 2.25637 * eV, 2.29690 * eV, 2.34050 * eV, 2.38578 * eV, 2.42943 * eV, 2.53093 * eV, 2.58203 * eV, 2.63926 * eV, 2.69489 * eV,
                                           2.75950 * eV, 2.88396 * eV, 2.95302 * eV, 3.02545 * eV, 3.09601 * eV, 3.18161 * eV, 3.26590 * eV, 3.35473 * eV, 3.44161 * eV, 3.54034 * eV, 3.64512 * eV, 3.75608 * eV, 3.87418 * eV,
                                           3.99973 * eV, 4.13371 * eV, 4.27696 * eV, 4.43064 * eV, 4.59557 * eV, 4.76007 * eV, 4.95065 * eV, 5.15688 * eV, 5.38078 * eV, 5.62461 * eV};

  std::vector<G4double> RefractiveIndex = {1.8646638,
                                           1.87226, 1.87263, 1.87336, 1.87409, 1.87409, 1.87555, 1.87628, 1.87737, 1.87774, 1.87883, 1.87993, 1.88102, 1.88285, 1.88467,
                                           1.88613, 1.88832, 1.88942, 1.89015, 1.89234, 1.89307, 1.89453, 1.89599, 1.90073, 1.90401, 1.90547, 1.90693, 1.90839, 1.91277,
                                           1.91569, 1.92080, 1.91861, 1.91934, 1.91788, 1.92226, 1.93175, 1.94197, 1.93102, 1.93978, 1.93248, 1.94489, 1.95438, 1.96606,
                                           1.96752, 1.98212, 1.99818, 2.03102, 2.07628, 2.13394, 2.20912};

  // --- Intrinsic absorption spectrum
  //    Highest and Lowest energies are arbitrarily set.

  std::vector<G4double> PhotonEnergy_ABS =
      {1.49849 * eV, 1.50943 * eV, 1.52054 * eV, 1.53181 * eV, 1.54325 * eV, 1.55486 * eV, 1.56665 * eV, 1.57861 * eV, 1.59076 * eV,
       1.6031 * eV, 1.61564 * eV, 1.62837 * eV, 1.6413 * eV, 1.65444 * eV, 1.66779 * eV, 1.68136 * eV, 1.69515 * eV, 1.70917 * eV,
       1.72342 * eV, 1.73791 * eV, 1.75265 * eV, 1.76764 * eV, 1.78289 * eV, 1.7984 * eV, 1.81419 * eV, 1.83026 * eV, 1.84661 * eV,
       1.86326 * eV, 1.88021 * eV, 1.89748 * eV, 1.91506 * eV, 1.93297 * eV, 1.95122 * eV, 1.96982 * eV, 1.98877 * eV, 2.0081 * eV,
       2.0278 * eV, 2.04789 * eV, 2.06839 * eV, 2.0893 * eV, 2.11064 * eV, 2.13242 * eV, 2.15465 * eV, 2.17735 * eV, 2.20053 * eV,
       2.22422 * eV, 2.23022 * eV, 2.24231 * eV, 2.25455 * eV, 2.26691 * eV, 2.27941 * eV, 2.29205 * eV, 2.30483 * eV, 2.31776 * eV,
       2.33083 * eV, 2.34405 * eV, 2.35741 * eV, 2.37094 * eV, 2.38462 * eV, 2.39845 * eV, 2.41245 * eV, 2.42661 * eV, 2.44094 * eV,
       2.45545 * eV, 2.47012 * eV, 2.48497 * eV, 2.5 * eV, 2.51521 * eV, 2.53061 * eV, 2.5462 * eV, 2.56198 * eV, 2.57796 * eV,
       2.59414 * eV, 2.61053 * eV, 2.62712 * eV, 2.64392 * eV, 2.66094 * eV, 2.67819 * eV, 2.71335 * eV, 2.73128 * eV, 2.74945 * eV,
       2.76786 * eV, 2.78652 * eV, 2.80543 * eV, 2.8246 * eV, 2.84404 * eV, 2.86374 * eV, 2.88372 * eV, 2.90398 * eV, 2.92453 * eV,
       2.94537 * eV, 2.96651 * eV, 2.98795 * eV, 3.00971 * eV, 3.03178 * eV, 3.05419 * eV, 3.07692 * eV, 3.1 * eV, 3.12343 * eV,
       3.14721 * eV, 3.17136 * eV, 3.19588 * eV, 3.22078 * eV, 3.24607 * eV, 3.27177 * eV, 3.29787 * eV, 3.3244 * eV, 3.35135 * eV,
       3.37875 * eV, 3.40659 * eV, 3.4349 * eV, 3.46369 * eV, 3.49296 * eV, 3.52273 * eV, 3.58382 * eV, 3.61516 * eV, 3.67953 * eV,
       3.71257 * eV, 3.78049 * eV, 3.92405 * eV, 3.96166 * eV, 4 * eV, 4.03909 * eV, 4.07895 * eV, 4.1196 * eV, 4.16107 * eV,
       4.20339 * eV, 4.24658 * eV, 4.29066 * eV, 4.33566 * eV, 4.38163 * eV, 4.42857 * eV, 4.47653 * eV, 4.52555 * eV, 4.62687 * eV,
       4.67925 * eV, 4.78764 * eV, 4.96 * eV, 5.62461 * eV};

  std::vector<G4double> Absorption =
      {955.954000 * mm, 668.943000 * mm, 614.032000 * mm, 467.353000 * mm, 559.162000 * mm, 579.555000 * mm, 650.626000 * mm, 535.162000 * mm, 524.755000 * mm,
       540.255000 * mm, 600.531000 * mm, 519.526000 * mm, 526.569000 * mm, 516.447000 * mm, 502.306000 * mm, 518.467000 * mm, 522.762000 * mm, 503.951000 * mm,
       537.711000 * mm, 520.839000 * mm, 553.001000 * mm, 488.909000 * mm, 521.548000 * mm, 471.766000 * mm, 450.077000 * mm, 404.852000 * mm, 441.221000 * mm,
       440.960000 * mm, 411.248000 * mm, 380.195000 * mm, 399.852000 * mm, 380.692000 * mm, 372.110000 * mm, 362.841000 * mm, 370.628000 * mm, 355.130000 * mm,
       371.095000 * mm, 389.190000 * mm, 390.557000 * mm, 376.662000 * mm, 394.540000 * mm, 419.485000 * mm, 423.900000 * mm, 424.207000 * mm, 459.364000 * mm,
       432.117000 * mm, 450.723000 * mm, 444.802000 * mm, 451.629000 * mm, 415.643000 * mm, 458.704000 * mm, 473.048000 * mm, 388.097000 * mm, 445.714000 * mm,
       356.658000 * mm, 362.018000 * mm, 323.960000 * mm, 249.410000 * mm, 222.770000 * mm, 173.466000 * mm, 126.428000 * mm, 94.944500 * mm, 64.388500 * mm,
       45.198300 * mm, 30.697900 * mm, 20.705400 * mm, 14.095600 * mm, 9.563980 * mm, 6.555540 * mm, 4.590660 * mm, 3.251770 * mm, 2.439640 * mm, 1.899230 * mm,
       1.561530 * mm, 1.644290 * mm, 1.454600 * mm, 1.344050 * mm, 1.392430 * mm, 1.474630 * mm, 1.365870 * mm, 1.418190 * mm, 1.449410 * mm, 1.429420 * mm, 1.588940 * mm,
       1.456210 * mm, 1.313570 * mm, 1.626080 * mm, 1.611680 * mm, 1.429990 * mm, 1.472460 * mm, 1.501370 * mm, 1.565330 * mm, 1.556520 * mm, 1.413260 * mm, 1.651750 * mm,
       1.532130 * mm, 1.908330 * mm, 2.906480 * mm, 4.388340 * mm, 6.664950 * mm, 9.720680 * mm, 12.470900 * mm, 13.226400 * mm, 11.510300 * mm, 8.747250 * mm, 6.425540 * mm,
       4.638230 * mm, 3.356940 * mm, 2.389330 * mm, 1.730910 * mm, 1.621300 * mm, 1.349290 * mm, 1.371340 * mm, 1.454750 * mm, 1.353480 * mm, 1.092090 * mm, 1.486040 * mm,
       1.375890 * mm, 1.153950 * mm, 1.623740 * mm, 1.443300 * mm, 1.605000 * mm, 1.705960 * mm, 1.510680 * mm, 1.525980 * mm, 1.586010 * mm, 1.616290 * mm, 1.489230 * mm,
       1.483450 * mm, 1.411050 * mm, 1.685210 * mm, 1.409220 * mm, 1.232600 * mm, 1.707510 * mm, 1.382160 * mm, 1.322320 * mm, 1.441060 * mm, 1.478580 * mm, 0 * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  //      Taken straight outta the spectrophotometer.
  //      Hope this doesn't kill the performance.      O.o'

  std::vector<G4double> PhotonEnergy_FAST = {1.425287 * eV, 1.426107 * eV, 1.426928 * eV, 1.427749 * eV, 1.428571 * eV, 1.429395 * eV, 1.430219 * eV, 1.431044 * eV, 1.431871 * eV, 1.432698 * eV, 1.433526 * eV, 1.434355 * eV,
                                             1.435185 * eV, 1.436016 * eV, 1.436848 * eV, 1.437681 * eV, 1.438515 * eV, 1.439350 * eV, 1.440186 * eV, 1.441023 * eV, 1.441860 * eV, 1.442699 * eV, 1.443539 * eV, 1.444380 * eV, 1.445221 * eV, 1.446064 * eV, 1.446908 * eV, 1.447752 * eV,
                                             1.448598 * eV, 1.449445 * eV, 1.450292 * eV, 1.451141 * eV, 1.451991 * eV, 1.452841 * eV, 1.453693 * eV, 1.454545 * eV, 1.455399 * eV, 1.456254 * eV, 1.457109 * eV, 1.457966 * eV, 1.458824 * eV, 1.459682 * eV, 1.460542 * eV, 1.461402 * eV,
                                             1.462264 * eV, 1.463127 * eV, 1.463991 * eV, 1.464855 * eV, 1.465721 * eV, 1.466588 * eV, 1.467456 * eV, 1.468324 * eV, 1.469194 * eV, 1.470065 * eV, 1.470937 * eV, 1.471810 * eV, 1.472684 * eV, 1.473559 * eV, 1.474435 * eV, 1.475312 * eV,
                                             1.476190 * eV, 1.477070 * eV, 1.477950 * eV, 1.478831 * eV, 1.479714 * eV, 1.480597 * eV, 1.481481 * eV, 1.482367 * eV, 1.483254 * eV, 1.484141 * eV, 1.485030 * eV, 1.485920 * eV, 1.486811 * eV, 1.487702 * eV, 1.488595 * eV, 1.489489 * eV,
                                             1.490385 * eV, 1.491281 * eV, 1.492178 * eV, 1.493076 * eV, 1.493976 * eV, 1.494876 * eV, 1.495778 * eV, 1.496681 * eV, 1.497585 * eV, 1.498489 * eV, 1.499395 * eV, 1.500302 * eV, 1.501211 * eV, 1.502120 * eV, 1.503030 * eV, 1.503942 * eV,
                                             1.504854 * eV, 1.505768 * eV, 1.506683 * eV, 1.507599 * eV, 1.508516 * eV, 1.509434 * eV, 1.510353 * eV, 1.511274 * eV, 1.512195 * eV, 1.513118 * eV, 1.514042 * eV, 1.514966 * eV, 1.515892 * eV, 1.516820 * eV, 1.517748 * eV, 1.518677 * eV,
                                             1.519608 * eV, 1.520540 * eV, 1.521472 * eV, 1.522406 * eV, 1.523342 * eV, 1.524278 * eV, 1.525215 * eV, 1.526154 * eV, 1.527094 * eV, 1.528035 * eV, 1.528977 * eV, 1.529920 * eV, 1.530864 * eV, 1.531810 * eV, 1.532756 * eV, 1.533704 * eV,
                                             1.534653 * eV, 1.535604 * eV, 1.536555 * eV, 1.537508 * eV, 1.538462 * eV, 1.539417 * eV, 1.540373 * eV, 1.541330 * eV, 1.542289 * eV, 1.543248 * eV, 1.544209 * eV, 1.545171 * eV, 1.546135 * eV, 1.547099 * eV, 1.548065 * eV, 1.549032 * eV,
                                             1.550000 * eV, 1.550969 * eV, 1.551940 * eV, 1.552912 * eV, 1.553885 * eV, 1.554859 * eV, 1.555834 * eV, 1.556811 * eV, 1.557789 * eV, 1.558768 * eV, 1.559748 * eV, 1.560730 * eV, 1.561713 * eV, 1.562697 * eV, 1.563682 * eV, 1.564669 * eV,
                                             1.565657 * eV, 1.566646 * eV, 1.567636 * eV, 1.568627 * eV, 1.569620 * eV, 1.570614 * eV, 1.571610 * eV, 1.572606 * eV, 1.573604 * eV, 1.574603 * eV, 1.575604 * eV, 1.576605 * eV, 1.577608 * eV, 1.578612 * eV, 1.579618 * eV, 1.580625 * eV, 1.581633 * eV, 1.582642 * eV, 1.583653 * eV, 1.584665 * eV, 1.585678 * eV, 1.586692 * eV, 1.587708 * eV,
                                             1.588725 * eV, 1.589744 * eV, 1.590763 * eV, 1.591784 * eV, 1.592807 * eV, 1.593830 * eV, 1.594855 * eV, 1.595882 * eV, 1.596909 * eV, 1.597938 * eV, 1.598968 * eV, 1.600000 * eV, 1.601033 * eV, 1.602067 * eV, 1.603103 * eV, 1.604140 * eV, 1.605178 * eV, 1.606218 * eV, 1.607259 * eV, 1.608301 * eV, 1.609345 * eV, 1.610390 * eV, 1.611436 * eV,
                                             1.612484 * eV, 1.613533 * eV, 1.614583 * eV, 1.615635 * eV, 1.616688 * eV, 1.617743 * eV, 1.618799 * eV, 1.619856 * eV, 1.620915 * eV, 1.621975 * eV, 1.623037 * eV, 1.624100 * eV, 1.625164 * eV, 1.626230 * eV, 1.627297 * eV, 1.628365 * eV, 1.629435 * eV, 1.630506 * eV, 1.631579 * eV, 1.632653 * eV, 1.633729 * eV, 1.634806 * eV, 1.635884 * eV,
                                             1.636964 * eV, 1.638045 * eV, 1.639128 * eV, 1.640212 * eV, 1.641297 * eV, 1.642384 * eV, 1.643472 * eV, 1.644562 * eV, 1.645654 * eV, 1.646746 * eV, 1.647841 * eV, 1.648936 * eV, 1.650033 * eV, 1.651132 * eV, 1.652232 * eV, 1.653333 * eV, 1.654436 * eV, 1.655541 * eV, 1.656647 * eV, 1.657754 * eV, 1.658863 * eV, 1.659973 * eV, 1.661085 * eV,
                                             1.662198 * eV, 1.663313 * eV, 1.664430 * eV, 1.665547 * eV, 1.666667 * eV, 1.667787 * eV, 1.668910 * eV, 1.670034 * eV, 1.671159 * eV, 1.672286 * eV, 1.673414 * eV, 1.674544 * eV, 1.675676 * eV, 1.676809 * eV, 1.677943 * eV, 1.679079 * eV, 1.680217 * eV, 1.681356 * eV, 1.682497 * eV, 1.683639 * eV, 1.684783 * eV, 1.685928 * eV, 1.687075 * eV,
                                             1.688223 * eV, 1.689373 * eV, 1.690525 * eV, 1.691678 * eV, 1.692833 * eV, 1.693989 * eV, 1.695147 * eV, 1.696306 * eV, 1.697467 * eV, 1.698630 * eV, 1.699794 * eV, 1.700960 * eV, 1.702128 * eV, 1.703297 * eV, 1.704467 * eV, 1.705640 * eV, 1.706813 * eV, 1.707989 * eV, 1.709166 * eV, 1.710345 * eV, 1.711525 * eV, 1.712707 * eV, 1.713891 * eV,
                                             1.715076 * eV, 1.716263 * eV, 1.717452 * eV, 1.718642 * eV, 1.719834 * eV, 1.721027 * eV, 1.722222 * eV, 1.723419 * eV, 1.724618 * eV, 1.725818 * eV, 1.727019 * eV, 1.728223 * eV, 1.729428 * eV, 1.730635 * eV, 1.731844 * eV, 1.733054 * eV, 1.734266 * eV, 1.735479 * eV, 1.736695 * eV, 1.737912 * eV, 1.739130 * eV, 1.740351 * eV, 1.741573 * eV,
                                             1.742797 * eV, 1.744023 * eV, 1.745250 * eV, 1.746479 * eV, 1.747710 * eV, 1.748942 * eV, 1.750176 * eV, 1.751412 * eV, 1.752650 * eV, 1.753890 * eV, 1.755131 * eV, 1.756374 * eV, 1.757619 * eV, 1.758865 * eV, 1.760114 * eV, 1.761364 * eV, 1.762615 * eV, 1.763869 * eV, 1.765125 * eV, 1.766382 * eV, 1.767641 * eV, 1.768902 * eV, 1.770164 * eV,
                                             1.771429 * eV, 1.772695 * eV, 1.773963 * eV, 1.775233 * eV, 1.776504 * eV, 1.777778 * eV, 1.779053 * eV, 1.780330 * eV, 1.781609 * eV, 1.782890 * eV, 1.784173 * eV, 1.785457 * eV, 1.786744 * eV, 1.788032 * eV, 1.789322 * eV, 1.790614 * eV, 1.791908 * eV, 1.793203 * eV, 1.794501 * eV,
                                             1.795800 * eV, 1.797101 * eV, 1.798405 * eV, 1.799710 * eV, 1.801017 * eV, 1.802326 * eV, 1.803636 * eV, 1.804949 * eV, 1.806264 * eV, 1.807580 * eV, 1.808899 * eV, 1.810219 * eV, 1.811541 * eV, 1.812865 * eV, 1.814192 * eV, 1.815520 * eV, 1.816850 * eV, 1.818182 * eV, 1.819516 * eV, 1.820852 * eV, 1.822190 * eV, 1.823529 * eV, 1.824871 * eV,
                                             1.826215 * eV, 1.827561 * eV, 1.828909 * eV, 1.830258 * eV, 1.831610 * eV, 1.832964 * eV, 1.834320 * eV, 1.835677 * eV, 1.837037 * eV, 1.838399 * eV, 1.839763 * eV, 1.841128 * eV, 1.842496 * eV, 1.843866 * eV, 1.845238 * eV, 1.846612 * eV, 1.847988 * eV, 1.849366 * eV, 1.850746 * eV, 1.852128 * eV, 1.853513 * eV, 1.854899 * eV, 1.856287 * eV,
                                             1.857678 * eV, 1.859070 * eV, 1.860465 * eV, 1.861862 * eV, 1.863261 * eV, 1.864662 * eV, 1.866065 * eV, 1.867470 * eV, 1.868877 * eV, 1.870287 * eV, 1.871698 * eV, 1.873112 * eV, 1.874528 * eV, 1.875946 * eV, 1.877366 * eV, 1.878788 * eV, 1.880212 * eV, 1.881639 * eV, 1.883068 * eV, 1.884498 * eV, 1.885932 * eV, 1.887367 * eV, 1.888804 * eV,
                                             1.890244 * eV, 1.891686 * eV, 1.893130 * eV, 1.894576 * eV, 1.896024 * eV, 1.897475 * eV, 1.898928 * eV, 1.900383 * eV, 1.901840 * eV, 1.903300 * eV, 1.904762 * eV, 1.906226 * eV, 1.907692 * eV, 1.909161 * eV, 1.910632 * eV, 1.912105 * eV, 1.913580 * eV, 1.915058 * eV, 1.916538 * eV, 1.918020 * eV, 1.919505 * eV, 1.920991 * eV, 1.922481 * eV,
                                             1.923972 * eV, 1.925466 * eV, 1.926962 * eV, 1.928460 * eV, 1.929961 * eV, 1.931464 * eV, 1.932970 * eV, 1.934477 * eV, 1.935988 * eV, 1.937500 * eV, 1.939015 * eV, 1.940532 * eV, 1.942052 * eV, 1.943574 * eV, 1.945098 * eV, 1.946625 * eV, 1.948154 * eV, 1.949686 * eV, 1.951220 * eV, 1.952756 * eV, 1.954295 * eV, 1.955836 * eV, 1.957380 * eV,
                                             1.958926 * eV, 1.960474 * eV, 1.962025 * eV, 1.963579 * eV, 1.965135 * eV, 1.966693 * eV, 1.968254 * eV, 1.969817 * eV, 1.971383 * eV, 1.972951 * eV, 1.974522 * eV, 1.976096 * eV, 1.977671 * eV, 1.979250 * eV, 1.980831 * eV, 1.982414 * eV, 1.984000 * eV, 1.985588 * eV, 1.987179 * eV, 1.988773 * eV, 1.990369 * eV, 1.991968 * eV, 1.993569 * eV,
                                             1.995173 * eV, 1.996779 * eV, 1.998388 * eV, 2.000000 * eV, 2.001614 * eV, 2.003231 * eV, 2.004850 * eV, 2.006472 * eV, 2.008097 * eV, 2.009724 * eV, 2.011354 * eV, 2.012987 * eV, 2.014622 * eV, 2.016260 * eV, 2.017901 * eV, 2.019544 * eV, 2.021190 * eV, 2.022838 * eV, 2.024490 * eV, 2.026144 * eV, 2.027800 * eV, 2.029460 * eV, 2.031122 * eV,
                                             2.032787 * eV, 2.034454 * eV, 2.036125 * eV, 2.037798 * eV, 2.039474 * eV, 2.041152 * eV, 2.042834 * eV, 2.044518 * eV, 2.046205 * eV, 2.047894 * eV, 2.049587 * eV, 2.051282 * eV, 2.052980 * eV, 2.054681 * eV, 2.056385 * eV, 2.058091 * eV, 2.059801 * eV, 2.061513 * eV, 2.063228 * eV, 2.064946 * eV, 2.066667 * eV, 2.068390 * eV, 2.070117 * eV,
                                             2.071846 * eV, 2.073579 * eV, 2.075314 * eV, 2.077052 * eV, 2.078793 * eV, 2.080537 * eV, 2.082284 * eV, 2.084034 * eV, 2.085786 * eV, 2.087542 * eV, 2.089301 * eV, 2.091062 * eV, 2.092827 * eV, 2.094595 * eV, 2.096365 * eV, 2.098139 * eV, 2.099915 * eV, 2.101695 * eV, 2.103478 * eV,
                                             2.105263 * eV, 2.107052 * eV, 2.108844 * eV, 2.110638 * eV, 2.112436 * eV, 2.114237 * eV, 2.116041 * eV, 2.117848 * eV, 2.119658 * eV, 2.121471 * eV, 2.123288 * eV, 2.125107 * eV, 2.126930 * eV, 2.128755 * eV, 2.130584 * eV, 2.132416 * eV, 2.134251 * eV, 2.136090 * eV, 2.137931 * eV, 2.139776 * eV, 2.141623 * eV, 2.143475 * eV, 2.145329 * eV,
                                             2.147186 * eV, 2.149047 * eV, 2.150911 * eV, 2.152778 * eV, 2.154648 * eV, 2.156522 * eV, 2.158399 * eV, 2.160279 * eV, 2.162162 * eV, 2.164049 * eV, 2.165939 * eV, 2.167832 * eV, 2.169729 * eV, 2.171629 * eV, 2.173532 * eV, 2.175439 * eV, 2.177349 * eV, 2.179262 * eV, 2.181179 * eV, 2.183099 * eV, 2.185022 * eV, 2.186949 * eV, 2.188879 * eV,
                                             2.190813 * eV, 2.192750 * eV, 2.194690 * eV, 2.196634 * eV, 2.198582 * eV, 2.200532 * eV, 2.202487 * eV, 2.204444 * eV, 2.206406 * eV, 2.208370 * eV, 2.210339 * eV, 2.212310 * eV, 2.214286 * eV, 2.216265 * eV, 2.218247 * eV, 2.220233 * eV, 2.222222 * eV, 2.224215 * eV, 2.226212 * eV, 2.228212 * eV, 2.230216 * eV, 2.232223 * eV, 2.234234 * eV,
                                             2.236249 * eV, 2.238267 * eV, 2.240289 * eV, 2.242315 * eV, 2.244344 * eV, 2.246377 * eV, 2.248413 * eV, 2.250454 * eV, 2.252498 * eV, 2.254545 * eV, 2.256597 * eV, 2.258652 * eV, 2.260711 * eV, 2.262774 * eV, 2.264840 * eV, 2.266910 * eV, 2.268984 * eV, 2.271062 * eV, 2.273144 * eV, 2.275229 * eV, 2.277319 * eV, 2.279412 * eV, 2.281509 * eV,
                                             2.283610 * eV, 2.285714 * eV, 2.287823 * eV, 2.289935 * eV, 2.292052 * eV, 2.294172 * eV, 2.296296 * eV, 2.298424 * eV, 2.300557 * eV, 2.302693 * eV, 2.304833 * eV, 2.306977 * eV, 2.309125 * eV, 2.311277 * eV, 2.313433 * eV, 2.315593 * eV, 2.317757 * eV, 2.319925 * eV, 2.322097 * eV, 2.324274 * eV, 2.326454 * eV, 2.328638 * eV, 2.330827 * eV,
                                             2.333020 * eV, 2.335217 * eV, 2.337418 * eV, 2.339623 * eV, 2.341832 * eV, 2.344045 * eV, 2.346263 * eV, 2.348485 * eV, 2.350711 * eV, 2.352941 * eV, 2.355176 * eV, 2.357414 * eV, 2.359657 * eV, 2.361905 * eV, 2.364156 * eV, 2.366412 * eV, 2.368672 * eV, 2.370937 * eV, 2.373206 * eV, 2.375479 * eV, 2.377756 * eV, 2.380038 * eV, 2.382325 * eV,
                                             2.384615 * eV, 2.386910 * eV, 2.389210 * eV, 2.391514 * eV, 2.393822 * eV, 2.396135 * eV, 2.398453 * eV, 2.400774 * eV, 2.403101 * eV, 2.405432 * eV, 2.407767 * eV, 2.410107 * eV, 2.412451 * eV, 2.414800 * eV, 2.417154 * eV, 2.419512 * eV, 2.421875 * eV, 2.424242 * eV, 2.426614 * eV, 2.428991 * eV, 2.431373 * eV, 2.433759 * eV, 2.436149 * eV,
                                             2.438545 * eV, 2.440945 * eV, 2.443350 * eV, 2.445759 * eV, 2.448174 * eV, 2.450593 * eV, 2.453017 * eV, 2.455446 * eV, 2.457879 * eV, 2.460317 * eV, 2.462761 * eV, 2.465209 * eV, 2.467662 * eV, 2.470120 * eV, 2.472582 * eV, 2.475050 * eV, 2.477522 * eV, 2.480000 * eV, 2.482482 * eV, 2.484970 * eV, 2.487462 * eV, 2.489960 * eV, 2.492462 * eV,
                                             2.494970 * eV, 2.497482 * eV, 2.500000 * eV, 2.502523 * eV, 2.505051 * eV, 2.507583 * eV, 2.510121 * eV, 2.512665 * eV, 2.515213 * eV, 2.517766 * eV, 2.520325 * eV, 2.522889 * eV, 2.525458 * eV, 2.528033 * eV, 2.530612 * eV, 2.533197 * eV, 2.535787 * eV, 2.538383 * eV, 2.540984 * eV,
                                             2.543590 * eV, 2.546201 * eV, 2.548818 * eV, 2.551440 * eV, 2.554068 * eV, 2.556701 * eV, 2.559340 * eV, 2.561983 * eV, 2.564633 * eV, 2.567288 * eV, 2.569948 * eV, 2.572614 * eV, 2.575286 * eV, 2.577963 * eV, 2.580645 * eV, 2.583333 * eV, 2.586027 * eV, 2.588727 * eV, 2.591432 * eV, 2.594142 * eV, 2.596859 * eV, 2.599581 * eV, 2.602308 * eV};

  std::vector<G4double> FastComponent =
      {
          0.160333, 0.172055, 0.180528, 0.185841, 0.188323, 0.188954, 0.186772, 0.182738, 0.178573, 0.175773, 0.174867, 0.173955, 0.172557, 0.171364, 0.170930, 0.170360, 0.168857, 0.167288, 0.165351, 0.163923, 0.162677, 0.161678, 0.161048, 0.160843, 0.160919, 0.160517, 0.160686, 0.160464,
          0.159976, 0.159308, 0.158286, 0.157136, 0.155732, 0.154752, 0.154047, 0.153539, 0.153576, 0.154763, 0.156705, 0.158406, 0.159616, 0.159562, 0.158966, 0.157962, 0.155876, 0.153398, 0.152418, 0.152958, 0.154043, 0.155506, 0.156696, 0.158246, 0.159557, 0.160035, 0.159984, 0.160655,
          0.161680, 0.162683, 0.163751, 0.164225, 0.164384, 0.163716, 0.162927, 0.161685, 0.161064, 0.161583, 0.163290, 0.166036, 0.169015, 0.172248, 0.174792, 0.177343, 0.178371, 0.179139, 0.179470, 0.179794, 0.180614, 0.181098, 0.181929, 0.182751, 0.184452, 0.184796, 0.185040, 0.185164,
          0.185262, 0.185692, 0.185288, 0.185155, 0.185544, 0.186761, 0.186675, 0.186026, 0.185206, 0.184357, 0.184081, 0.182930, 0.180970, 0.179324, 0.178990, 0.178807, 0.178816, 0.179548, 0.180189, 0.181705, 0.183860, 0.185555, 0.186864, 0.187659, 0.186991, 0.185885, 0.184938, 0.182451,
          0.179253, 0.176828, 0.175065, 0.174352, 0.174345, 0.174170, 0.174635, 0.176360, 0.177780, 0.178376, 0.179079, 0.179967, 0.180717, 0.181527, 0.182005, 0.182501, 0.182777, 0.182598, 0.181987, 0.181748, 0.181893, 0.182113, 0.182613, 0.182965, 0.183928, 0.184883, 0.185172, 0.185290,
          0.185926, 0.187299, 0.189183, 0.192071, 0.194687, 0.197445, 0.200288, 0.202261, 0.203751, 0.204776, 0.205879, 0.207200, 0.209689, 0.212624, 0.215543, 0.218708, 0.221917, 0.225334, 0.228164, 0.231296, 0.234249, 0.238200, 0.242831, 0.246744, 0.249958, 0.252404, 0.254520, 0.255287,
          0.255467, 0.255138, 0.255251, 0.256250, 0.257098, 0.258633, 0.260698, 0.263629, 0.266652, 0.269514, 0.271993, 0.274103, 0.275915, 0.276758, 0.277352, 0.277538, 0.277770, 0.278430, 0.279565, 0.280986, 0.282494, 0.284023, 0.284981, 0.285279, 0.285089, 0.284264, 0.283283, 0.282408,
          0.281352, 0.280817, 0.280748, 0.280999, 0.281389, 0.282203, 0.283156, 0.284094, 0.284769, 0.284727, 0.285041, 0.285578, 0.286377, 0.286919, 0.287022, 0.287172, 0.287323, 0.286838, 0.286101, 0.285711, 0.285562, 0.286258, 0.287810, 0.289147, 0.290564, 0.291878, 0.292197, 0.291950,
          0.291027, 0.289650, 0.288632, 0.288382, 0.288782, 0.289809, 0.290986, 0.292057, 0.293552, 0.294994, 0.296213, 0.297359, 0.298379, 0.299725, 0.301065, 0.301758,
          0.302152, 0.302418, 0.302455, 0.302965, 0.303988, 0.305269, 0.307792, 0.311004, 0.314233, 0.317157, 0.319612, 0.321208, 0.322833, 0.323933, 0.324668, 0.325648, 0.326384, 0.327127, 0.327983, 0.329782, 0.331478, 0.334153, 0.337734, 0.342331, 0.347829, 0.353863, 0.359909, 0.365554,
          0.371182, 0.375309, 0.378078, 0.380650, 0.383559, 0.386661, 0.391209, 0.396554, 0.403391, 0.412262, 0.421569, 0.430263, 0.438646, 0.446296, 0.452533, 0.459093, 0.464611, 0.470111, 0.475587, 0.480986, 0.486321, 0.492086, 0.497950, 0.503656, 0.510915, 0.518411, 0.525585, 0.531775,
          0.537243, 0.541844, 0.545787, 0.548832, 0.551114, 0.554734, 0.560204, 0.566683, 0.574083, 0.582899, 0.591700, 0.599719, 0.606075, 0.610675, 0.613892, 0.616678, 0.619201, 0.621949, 0.626338, 0.631770, 0.637622, 0.643314, 0.648892, 0.654411, 0.659824, 0.665181, 0.670375, 0.676088,
          0.683226, 0.690607, 0.698531, 0.708160, 0.718258, 0.728716, 0.739570, 0.751581, 0.763034, 0.775454, 0.786540, 0.797086, 0.808549, 0.820140, 0.831665, 0.843176, 0.856263, 0.868398, 0.881225, 0.892920, 0.904357, 0.915893, 0.928096, 0.939263, 0.948868, 0.959247, 0.969073, 0.979514,
          0.991217, 1.006180, 1.022176, 1.040957, 1.060646, 1.080315, 1.099629, 1.117168, 1.132367, 1.143713, 1.154007, 1.162971, 1.172804, 1.183047, 1.193364, 1.204806, 1.218254, 1.233768, 1.249340, 1.264735, 1.280843, 1.298822, 1.316305, 1.333060, 1.349401, 1.365012, 1.381080, 1.398043,
          1.414998, 1.433156, 1.453538, 1.475149, 1.497840, 1.522714, 1.549153, 1.575589, 1.602703, 1.629766, 1.657771, 1.686157, 1.713829, 1.740740, 1.768848, 1.797099, 1.826433, 1.856914, 1.887414, 1.920113, 1.952943, 1.984931, 2.016673, 2.048364, 2.080761, 2.114546, 2.150983, 2.187603,
          2.227391, 2.267608, 2.308318, 2.349979, 2.391574, 2.432560, 2.473686, 2.517020, 2.560338, 2.606682, 2.652806, 2.697589, 2.740990, 2.782212, 2.822549, 2.863372, 2.906545, 2.951182, 2.999788, 3.049974, 3.101279, 3.150571, 3.197309, 3.241397, 3.282194, 3.319780, 3.355298, 3.394046,
          3.434711, 3.481092, 3.529849, 3.581205, 3.636162, 3.692668, 3.749120, 3.806017, 3.865440, 3.920449, 3.976139, 4.028575, 4.079399, 4.129317, 4.178763, 4.227938, 4.276508, 4.328505, 4.377710, 4.431798, 4.485211, 4.542401, 4.602420, 4.665596, 4.733517, 4.805294, 4.881597, 4.955312,
          5.031172, 5.103682, 5.172749, 5.236611, 5.298137, 5.359899, 5.419967, 5.482172, 5.543176, 5.605148, 5.670492, 5.740138, 5.814321, 5.895414, 5.981730, 6.071641, 6.164834, 6.256723, 6.343300, 6.426013, 6.507092, 6.584824, 6.664619, 6.745062, 6.824841, 6.905505, 6.987358, 7.068448,
          7.145806, 7.223107, 7.299318, 7.382849, 7.469975, 7.558261, 7.648318, 7.739405, 7.832896, 7.927704, 8.024399, 8.117990, 8.213648, 8.309669, 8.403208, 8.491036, 8.573814, 8.653141, 8.732364, 8.812956, 8.896425, 8.982942, 9.074628, 9.172558, 9.271829, 9.373102, 9.471807, 9.568671, 9.664489, 9.764401, 9.862431, 9.961527,
          10.062514, 10.162395, 10.267956, 10.377316, 10.486914, 10.593941, 10.704643, 10.812764, 10.922728, 11.031806, 11.136382, 11.240701, 11.348914, 11.457710, 11.560809, 11.666111, 11.769687, 11.873744, 11.982856, 12.091494, 12.195096, 12.306485, 12.424388, 12.538396, 12.649503,
          12.755230, 12.852457, 12.955026, 13.057408, 13.151514, 13.249479, 13.360196, 13.475367, 13.590405, 13.703543, 13.809648, 13.920157, 14.030500, 14.136132, 14.234845, 14.337392, 14.440752, 14.542470, 14.643342, 14.742330, 14.837359, 14.933357, 15.030482, 15.121741, 15.217645,
          15.311870, 15.403404, 15.499368, 15.605598, 15.711020, 15.818623, 15.928037, 16.034052, 16.143130, 16.247351, 16.339258, 16.425389, 16.516449, 16.606260, 16.696443, 16.790204, 16.882196, 16.980250, 17.080543, 17.177801, 17.265764, 17.349557, 17.429280, 17.505393, 17.582362,
          17.656297, 17.732708, 17.816212, 17.908350, 18.003255, 18.095199, 18.181472, 18.269397, 18.354728, 18.434323, 18.510606, 18.596313, 18.693102, 18.802602, 18.911997, 19.015629, 19.124369, 19.229364, 19.323701, 19.402913, 19.483465, 19.560596, 19.641053, 19.718309, 19.792413,
          19.869586, 19.949725, 20.026719, 20.095968, 20.171002, 20.255738, 20.345770, 20.434825, 20.524169, 20.604079, 20.677508, 20.741404, 20.794106, 20.843678, 20.898596, 20.953907, 21.011152, 21.081034, 21.153868, 21.230743, 21.305027, 21.372700, 21.432274, 21.489282, 21.538526,
          21.580936, 21.626996, 21.670602, 21.712001, 21.748164, 21.781695, 21.812616, 21.837206, 21.857631, 21.878914, 21.906131, 21.934830, 21.957913, 21.976860, 21.991334, 22.003585, 22.005043, 21.998509, 21.990289, 21.987864, 21.988827, 21.987035, 21.980584, 21.963873, 21.947645,
          21.926436, 21.896811, 21.859359, 21.814038, 21.758221,
          21.698002, 21.635145, 21.566074, 21.493923, 21.423607, 21.353887, 21.278387, 21.189528, 21.081072, 20.957433, 20.818778, 20.670547, 20.513037, 20.350933, 20.191659, 20.036380, 19.873308, 19.701685, 19.519604, 19.329683, 19.135690, 18.936732, 18.729052, 18.519217, 18.310576,
          18.094135, 17.867046, 17.627899, 17.378721, 17.118091, 16.853280, 16.576317, 16.292254, 16.011360, 15.733297, 15.457866, 15.182900, 14.905330, 14.621737, 14.337595, 14.046097, 13.746192, 13.443646, 13.141727, 12.844686, 12.550631, 12.257647, 11.962531, 11.666829, 11.369029,
          11.064639, 10.758183, 10.449219, 10.146628,
          9.845579, 9.550573, 9.256683, 8.963058, 8.669924, 8.372660, 8.075375, 7.777387, 7.485712, 7.198002, 6.920792, 6.650151, 6.388837, 6.131463, 5.875763, 5.623275, 5.370905, 5.120390, 4.872820, 4.632578, 4.396777, 4.168619, 3.945906, 3.727595, 3.515392, 3.310932, 3.113700, 2.926979,
          2.751590, 2.588683, 2.439079, 2.300711, 2.169602, 2.044509, 1.925282, 1.810431, 1.701355, 1.600311, 1.508377, 1.428058, 1.361947, 1.306719, 1.260604, 1.221590, 1.187067, 1.155297, 1.125212, 1.094388, 1.064629, 1.039276, 1.018386, 1.002130, 0.991032, 0.985420, 0.984140};

  // RAYLEIGH
  // const G4int Rayleigh_points = ;
  // G4double Rayleigh_energy[] = ;
  // G4double Rayleigh_length[] = ;

  //** scintillation and optical properties **//
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  // mt->AddProperty("RAYLEIGH",      Rayleigh_energy,  Rayleigh_length,     Rayleigh_points);
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 4.8);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 40. * ns);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 130. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 0.6); // Ratio between fast component and total light yield. Ignore the documentation.


  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::GAGG_very_fast(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{
  // ########################################################
  // ### GAGG:Ce:Mg in a more complete fashion.
  // ### - Index of refraction taken from:
  // ###         Kozlova NS, Buzanov OA, Kasimova VM, Kozlova AP, Zabelina EV (2018) Optical characteristics of single crystal Gd3Al2Ga3O12 : Ce. Modern Electronic Materials 4(1): 7–12. https://doi.org/10.3897/j.moem.4.1.33240
  // ### - Emission measured in Lab 27, CERN.                                                                         L. Martinazzoli                   (2020)
  // ### - Absorption calculated measuring transmission of different ILM GAGG:Ce (not codoped!) in Lab 27, CERN.      N. Kratochwil, L. Martinazzoli    (2019)
  // ########

  double standard_light_yield = 40000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Ga = new G4Element("Gallium", "Ga", z = 31., a = 69.723 * g / mole);
  G4Element *Gd = new G4Element("Gadolinio", "Gd", z = 64., a = 157.25 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("GAGG_very_fast", density = 6.63 * g / cm3, 4);
  mat->AddElement(Ga, 3);
  mat->AddElement(Gd, 3);
  mat->AddElement(Al, 2);
  mat->AddElement(O, 12);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);
  //--------//

  // --- Refractive Index
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_RI = {1.23984 * eV,
                                           1.72271 * eV, 1.74623 * eV, 1.77132 * eV, 1.79807 * eV, 1.82468 * eV, 1.85209 * eV, 1.87931 * eV, 1.90734 * eV, 1.93840 * eV, 1.96824 * eV, 2.00017 * eV, 2.03315 * eV, 2.06599 * eV,
                                           2.10633 * eV, 2.13762 * eV, 2.17670 * eV, 2.21440 * eV, 2.25637 * eV, 2.29690 * eV, 2.34050 * eV, 2.38578 * eV, 2.42943 * eV, 2.53093 * eV, 2.58203 * eV, 2.63926 * eV, 2.69489 * eV,
                                           2.75950 * eV, 2.88396 * eV, 2.95302 * eV, 3.02545 * eV, 3.09601 * eV, 3.18161 * eV, 3.26590 * eV, 3.35473 * eV, 3.44161 * eV, 3.54034 * eV, 3.64512 * eV, 3.75608 * eV, 3.87418 * eV,
                                           3.99973 * eV, 4.13371 * eV, 4.27696 * eV, 4.43064 * eV, 4.59557 * eV, 4.76007 * eV, 4.95065 * eV, 5.15688 * eV, 5.38078 * eV, 5.62461 * eV};

  std::vector<G4double> RefractiveIndex = {1.8646638,
                                           1.87226, 1.87263, 1.87336, 1.87409, 1.87409, 1.87555, 1.87628, 1.87737, 1.87774, 1.87883, 1.87993, 1.88102, 1.88285, 1.88467,
                                           1.88613, 1.88832, 1.88942, 1.89015, 1.89234, 1.89307, 1.89453, 1.89599, 1.90073, 1.90401, 1.90547, 1.90693, 1.90839, 1.91277,
                                           1.91569, 1.92080, 1.91861, 1.91934, 1.91788, 1.92226, 1.93175, 1.94197, 1.93102, 1.93978, 1.93248, 1.94489, 1.95438, 1.96606,
                                           1.96752, 1.98212, 1.99818, 2.03102, 2.07628, 2.13394, 2.20912};

  // --- Intrinsic absorption spectrum
  //    Highest and Lowest energies are arbitrarily set.

  std::vector<G4double> PhotonEnergy_ABS =
      {1.49849 * eV, 1.50943 * eV, 1.52054 * eV, 1.53181 * eV, 1.54325 * eV, 1.55486 * eV, 1.56665 * eV, 1.57861 * eV, 1.59076 * eV,
       1.6031 * eV, 1.61564 * eV, 1.62837 * eV, 1.6413 * eV, 1.65444 * eV, 1.66779 * eV, 1.68136 * eV, 1.69515 * eV, 1.70917 * eV,
       1.72342 * eV, 1.73791 * eV, 1.75265 * eV, 1.76764 * eV, 1.78289 * eV, 1.7984 * eV, 1.81419 * eV, 1.83026 * eV, 1.84661 * eV,
       1.86326 * eV, 1.88021 * eV, 1.89748 * eV, 1.91506 * eV, 1.93297 * eV, 1.95122 * eV, 1.96982 * eV, 1.98877 * eV, 2.0081 * eV,
       2.0278 * eV, 2.04789 * eV, 2.06839 * eV, 2.0893 * eV, 2.11064 * eV, 2.13242 * eV, 2.15465 * eV, 2.17735 * eV, 2.20053 * eV,
       2.22422 * eV, 2.23022 * eV, 2.24231 * eV, 2.25455 * eV, 2.26691 * eV, 2.27941 * eV, 2.29205 * eV, 2.30483 * eV, 2.31776 * eV,
       2.33083 * eV, 2.34405 * eV, 2.35741 * eV, 2.37094 * eV, 2.38462 * eV, 2.39845 * eV, 2.41245 * eV, 2.42661 * eV, 2.44094 * eV,
       2.45545 * eV, 2.47012 * eV, 2.48497 * eV, 2.5 * eV, 2.51521 * eV, 2.53061 * eV, 2.5462 * eV, 2.56198 * eV, 2.57796 * eV,
       2.59414 * eV, 2.61053 * eV, 2.62712 * eV, 2.64392 * eV, 2.66094 * eV, 2.67819 * eV, 2.71335 * eV, 2.73128 * eV, 2.74945 * eV,
       2.76786 * eV, 2.78652 * eV, 2.80543 * eV, 2.8246 * eV, 2.84404 * eV, 2.86374 * eV, 2.88372 * eV, 2.90398 * eV, 2.92453 * eV,
       2.94537 * eV, 2.96651 * eV, 2.98795 * eV, 3.00971 * eV, 3.03178 * eV, 3.05419 * eV, 3.07692 * eV, 3.1 * eV, 3.12343 * eV,
       3.14721 * eV, 3.17136 * eV, 3.19588 * eV, 3.22078 * eV, 3.24607 * eV, 3.27177 * eV, 3.29787 * eV, 3.3244 * eV, 3.35135 * eV,
       3.37875 * eV, 3.40659 * eV, 3.4349 * eV, 3.46369 * eV, 3.49296 * eV, 3.52273 * eV, 3.58382 * eV, 3.61516 * eV, 3.67953 * eV,
       3.71257 * eV, 3.78049 * eV, 3.92405 * eV, 3.96166 * eV, 4 * eV, 4.03909 * eV, 4.07895 * eV, 4.1196 * eV, 4.16107 * eV,
       4.20339 * eV, 4.24658 * eV, 4.29066 * eV, 4.33566 * eV, 4.38163 * eV, 4.42857 * eV, 4.47653 * eV, 4.52555 * eV, 4.62687 * eV,
       4.67925 * eV, 4.78764 * eV, 4.96 * eV, 5.62461 * eV};

  std::vector<G4double> Absorption =
      {955.954000 * mm, 668.943000 * mm, 614.032000 * mm, 467.353000 * mm, 559.162000 * mm, 579.555000 * mm, 650.626000 * mm, 535.162000 * mm, 524.755000 * mm,
       540.255000 * mm, 600.531000 * mm, 519.526000 * mm, 526.569000 * mm, 516.447000 * mm, 502.306000 * mm, 518.467000 * mm, 522.762000 * mm, 503.951000 * mm,
       537.711000 * mm, 520.839000 * mm, 553.001000 * mm, 488.909000 * mm, 521.548000 * mm, 471.766000 * mm, 450.077000 * mm, 404.852000 * mm, 441.221000 * mm,
       440.960000 * mm, 411.248000 * mm, 380.195000 * mm, 399.852000 * mm, 380.692000 * mm, 372.110000 * mm, 362.841000 * mm, 370.628000 * mm, 355.130000 * mm,
       371.095000 * mm, 389.190000 * mm, 390.557000 * mm, 376.662000 * mm, 394.540000 * mm, 419.485000 * mm, 423.900000 * mm, 424.207000 * mm, 459.364000 * mm,
       432.117000 * mm, 450.723000 * mm, 444.802000 * mm, 451.629000 * mm, 415.643000 * mm, 458.704000 * mm, 473.048000 * mm, 388.097000 * mm, 445.714000 * mm,
       356.658000 * mm, 362.018000 * mm, 323.960000 * mm, 249.410000 * mm, 222.770000 * mm, 173.466000 * mm, 126.428000 * mm, 94.944500 * mm, 64.388500 * mm,
       45.198300 * mm, 30.697900 * mm, 20.705400 * mm, 14.095600 * mm, 9.563980 * mm, 6.555540 * mm, 4.590660 * mm, 3.251770 * mm, 2.439640 * mm, 1.899230 * mm,
       1.561530 * mm, 1.644290 * mm, 1.454600 * mm, 1.344050 * mm, 1.392430 * mm, 1.474630 * mm, 1.365870 * mm, 1.418190 * mm, 1.449410 * mm, 1.429420 * mm, 1.588940 * mm,
       1.456210 * mm, 1.313570 * mm, 1.626080 * mm, 1.611680 * mm, 1.429990 * mm, 1.472460 * mm, 1.501370 * mm, 1.565330 * mm, 1.556520 * mm, 1.413260 * mm, 1.651750 * mm,
       1.532130 * mm, 1.908330 * mm, 2.906480 * mm, 4.388340 * mm, 6.664950 * mm, 9.720680 * mm, 12.470900 * mm, 13.226400 * mm, 11.510300 * mm, 8.747250 * mm, 6.425540 * mm,
       4.638230 * mm, 3.356940 * mm, 2.389330 * mm, 1.730910 * mm, 1.621300 * mm, 1.349290 * mm, 1.371340 * mm, 1.454750 * mm, 1.353480 * mm, 1.092090 * mm, 1.486040 * mm,
       1.375890 * mm, 1.153950 * mm, 1.623740 * mm, 1.443300 * mm, 1.605000 * mm, 1.705960 * mm, 1.510680 * mm, 1.525980 * mm, 1.586010 * mm, 1.616290 * mm, 1.489230 * mm,
       1.483450 * mm, 1.411050 * mm, 1.685210 * mm, 1.409220 * mm, 1.232600 * mm, 1.707510 * mm, 1.382160 * mm, 1.322320 * mm, 1.441060 * mm, 1.478580 * mm, 0 * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  //      Taken straight outta the spectrophotometer.
  //      Hope this doesn't kill the performance.      O.o'

  std::vector<G4double> PhotonEnergy_FAST = {1.425287 * eV, 1.426107 * eV, 1.426928 * eV, 1.427749 * eV, 1.428571 * eV, 1.429395 * eV, 1.430219 * eV, 1.431044 * eV, 1.431871 * eV, 1.432698 * eV, 1.433526 * eV, 1.434355 * eV,
                                             1.435185 * eV, 1.436016 * eV, 1.436848 * eV, 1.437681 * eV, 1.438515 * eV, 1.439350 * eV, 1.440186 * eV, 1.441023 * eV, 1.441860 * eV, 1.442699 * eV, 1.443539 * eV, 1.444380 * eV, 1.445221 * eV, 1.446064 * eV, 1.446908 * eV, 1.447752 * eV,
                                             1.448598 * eV, 1.449445 * eV, 1.450292 * eV, 1.451141 * eV, 1.451991 * eV, 1.452841 * eV, 1.453693 * eV, 1.454545 * eV, 1.455399 * eV, 1.456254 * eV, 1.457109 * eV, 1.457966 * eV, 1.458824 * eV, 1.459682 * eV, 1.460542 * eV, 1.461402 * eV,
                                             1.462264 * eV, 1.463127 * eV, 1.463991 * eV, 1.464855 * eV, 1.465721 * eV, 1.466588 * eV, 1.467456 * eV, 1.468324 * eV, 1.469194 * eV, 1.470065 * eV, 1.470937 * eV, 1.471810 * eV, 1.472684 * eV, 1.473559 * eV, 1.474435 * eV, 1.475312 * eV,
                                             1.476190 * eV, 1.477070 * eV, 1.477950 * eV, 1.478831 * eV, 1.479714 * eV, 1.480597 * eV, 1.481481 * eV, 1.482367 * eV, 1.483254 * eV, 1.484141 * eV, 1.485030 * eV, 1.485920 * eV, 1.486811 * eV, 1.487702 * eV, 1.488595 * eV, 1.489489 * eV,
                                             1.490385 * eV, 1.491281 * eV, 1.492178 * eV, 1.493076 * eV, 1.493976 * eV, 1.494876 * eV, 1.495778 * eV, 1.496681 * eV, 1.497585 * eV, 1.498489 * eV, 1.499395 * eV, 1.500302 * eV, 1.501211 * eV, 1.502120 * eV, 1.503030 * eV, 1.503942 * eV,
                                             1.504854 * eV, 1.505768 * eV, 1.506683 * eV, 1.507599 * eV, 1.508516 * eV, 1.509434 * eV, 1.510353 * eV, 1.511274 * eV, 1.512195 * eV, 1.513118 * eV, 1.514042 * eV, 1.514966 * eV, 1.515892 * eV, 1.516820 * eV, 1.517748 * eV, 1.518677 * eV,
                                             1.519608 * eV, 1.520540 * eV, 1.521472 * eV, 1.522406 * eV, 1.523342 * eV, 1.524278 * eV, 1.525215 * eV, 1.526154 * eV, 1.527094 * eV, 1.528035 * eV, 1.528977 * eV, 1.529920 * eV, 1.530864 * eV, 1.531810 * eV, 1.532756 * eV, 1.533704 * eV,
                                             1.534653 * eV, 1.535604 * eV, 1.536555 * eV, 1.537508 * eV, 1.538462 * eV, 1.539417 * eV, 1.540373 * eV, 1.541330 * eV, 1.542289 * eV, 1.543248 * eV, 1.544209 * eV, 1.545171 * eV, 1.546135 * eV, 1.547099 * eV, 1.548065 * eV, 1.549032 * eV,
                                             1.550000 * eV, 1.550969 * eV, 1.551940 * eV, 1.552912 * eV, 1.553885 * eV, 1.554859 * eV, 1.555834 * eV, 1.556811 * eV, 1.557789 * eV, 1.558768 * eV, 1.559748 * eV, 1.560730 * eV, 1.561713 * eV, 1.562697 * eV, 1.563682 * eV, 1.564669 * eV,
                                             1.565657 * eV, 1.566646 * eV, 1.567636 * eV, 1.568627 * eV, 1.569620 * eV, 1.570614 * eV, 1.571610 * eV, 1.572606 * eV, 1.573604 * eV, 1.574603 * eV, 1.575604 * eV, 1.576605 * eV, 1.577608 * eV, 1.578612 * eV, 1.579618 * eV, 1.580625 * eV, 1.581633 * eV, 1.582642 * eV, 1.583653 * eV, 1.584665 * eV, 1.585678 * eV, 1.586692 * eV, 1.587708 * eV,
                                             1.588725 * eV, 1.589744 * eV, 1.590763 * eV, 1.591784 * eV, 1.592807 * eV, 1.593830 * eV, 1.594855 * eV, 1.595882 * eV, 1.596909 * eV, 1.597938 * eV, 1.598968 * eV, 1.600000 * eV, 1.601033 * eV, 1.602067 * eV, 1.603103 * eV, 1.604140 * eV, 1.605178 * eV, 1.606218 * eV, 1.607259 * eV, 1.608301 * eV, 1.609345 * eV, 1.610390 * eV, 1.611436 * eV,
                                             1.612484 * eV, 1.613533 * eV, 1.614583 * eV, 1.615635 * eV, 1.616688 * eV, 1.617743 * eV, 1.618799 * eV, 1.619856 * eV, 1.620915 * eV, 1.621975 * eV, 1.623037 * eV, 1.624100 * eV, 1.625164 * eV, 1.626230 * eV, 1.627297 * eV, 1.628365 * eV, 1.629435 * eV, 1.630506 * eV, 1.631579 * eV, 1.632653 * eV, 1.633729 * eV, 1.634806 * eV, 1.635884 * eV,
                                             1.636964 * eV, 1.638045 * eV, 1.639128 * eV, 1.640212 * eV, 1.641297 * eV, 1.642384 * eV, 1.643472 * eV, 1.644562 * eV, 1.645654 * eV, 1.646746 * eV, 1.647841 * eV, 1.648936 * eV, 1.650033 * eV, 1.651132 * eV, 1.652232 * eV, 1.653333 * eV, 1.654436 * eV, 1.655541 * eV, 1.656647 * eV, 1.657754 * eV, 1.658863 * eV, 1.659973 * eV, 1.661085 * eV,
                                             1.662198 * eV, 1.663313 * eV, 1.664430 * eV, 1.665547 * eV, 1.666667 * eV, 1.667787 * eV, 1.668910 * eV, 1.670034 * eV, 1.671159 * eV, 1.672286 * eV, 1.673414 * eV, 1.674544 * eV, 1.675676 * eV, 1.676809 * eV, 1.677943 * eV, 1.679079 * eV, 1.680217 * eV, 1.681356 * eV, 1.682497 * eV, 1.683639 * eV, 1.684783 * eV, 1.685928 * eV, 1.687075 * eV,
                                             1.688223 * eV, 1.689373 * eV, 1.690525 * eV, 1.691678 * eV, 1.692833 * eV, 1.693989 * eV, 1.695147 * eV, 1.696306 * eV, 1.697467 * eV, 1.698630 * eV, 1.699794 * eV, 1.700960 * eV, 1.702128 * eV, 1.703297 * eV, 1.704467 * eV, 1.705640 * eV, 1.706813 * eV, 1.707989 * eV, 1.709166 * eV, 1.710345 * eV, 1.711525 * eV, 1.712707 * eV, 1.713891 * eV,
                                             1.715076 * eV, 1.716263 * eV, 1.717452 * eV, 1.718642 * eV, 1.719834 * eV, 1.721027 * eV, 1.722222 * eV, 1.723419 * eV, 1.724618 * eV, 1.725818 * eV, 1.727019 * eV, 1.728223 * eV, 1.729428 * eV, 1.730635 * eV, 1.731844 * eV, 1.733054 * eV, 1.734266 * eV, 1.735479 * eV, 1.736695 * eV, 1.737912 * eV, 1.739130 * eV, 1.740351 * eV, 1.741573 * eV,
                                             1.742797 * eV, 1.744023 * eV, 1.745250 * eV, 1.746479 * eV, 1.747710 * eV, 1.748942 * eV, 1.750176 * eV, 1.751412 * eV, 1.752650 * eV, 1.753890 * eV, 1.755131 * eV, 1.756374 * eV, 1.757619 * eV, 1.758865 * eV, 1.760114 * eV, 1.761364 * eV, 1.762615 * eV, 1.763869 * eV, 1.765125 * eV, 1.766382 * eV, 1.767641 * eV, 1.768902 * eV, 1.770164 * eV,
                                             1.771429 * eV, 1.772695 * eV, 1.773963 * eV, 1.775233 * eV, 1.776504 * eV, 1.777778 * eV, 1.779053 * eV, 1.780330 * eV, 1.781609 * eV, 1.782890 * eV, 1.784173 * eV, 1.785457 * eV, 1.786744 * eV, 1.788032 * eV, 1.789322 * eV, 1.790614 * eV, 1.791908 * eV, 1.793203 * eV, 1.794501 * eV,
                                             1.795800 * eV, 1.797101 * eV, 1.798405 * eV, 1.799710 * eV, 1.801017 * eV, 1.802326 * eV, 1.803636 * eV, 1.804949 * eV, 1.806264 * eV, 1.807580 * eV, 1.808899 * eV, 1.810219 * eV, 1.811541 * eV, 1.812865 * eV, 1.814192 * eV, 1.815520 * eV, 1.816850 * eV, 1.818182 * eV, 1.819516 * eV, 1.820852 * eV, 1.822190 * eV, 1.823529 * eV, 1.824871 * eV,
                                             1.826215 * eV, 1.827561 * eV, 1.828909 * eV, 1.830258 * eV, 1.831610 * eV, 1.832964 * eV, 1.834320 * eV, 1.835677 * eV, 1.837037 * eV, 1.838399 * eV, 1.839763 * eV, 1.841128 * eV, 1.842496 * eV, 1.843866 * eV, 1.845238 * eV, 1.846612 * eV, 1.847988 * eV, 1.849366 * eV, 1.850746 * eV, 1.852128 * eV, 1.853513 * eV, 1.854899 * eV, 1.856287 * eV,
                                             1.857678 * eV, 1.859070 * eV, 1.860465 * eV, 1.861862 * eV, 1.863261 * eV, 1.864662 * eV, 1.866065 * eV, 1.867470 * eV, 1.868877 * eV, 1.870287 * eV, 1.871698 * eV, 1.873112 * eV, 1.874528 * eV, 1.875946 * eV, 1.877366 * eV, 1.878788 * eV, 1.880212 * eV, 1.881639 * eV, 1.883068 * eV, 1.884498 * eV, 1.885932 * eV, 1.887367 * eV, 1.888804 * eV,
                                             1.890244 * eV, 1.891686 * eV, 1.893130 * eV, 1.894576 * eV, 1.896024 * eV, 1.897475 * eV, 1.898928 * eV, 1.900383 * eV, 1.901840 * eV, 1.903300 * eV, 1.904762 * eV, 1.906226 * eV, 1.907692 * eV, 1.909161 * eV, 1.910632 * eV, 1.912105 * eV, 1.913580 * eV, 1.915058 * eV, 1.916538 * eV, 1.918020 * eV, 1.919505 * eV, 1.920991 * eV, 1.922481 * eV,
                                             1.923972 * eV, 1.925466 * eV, 1.926962 * eV, 1.928460 * eV, 1.929961 * eV, 1.931464 * eV, 1.932970 * eV, 1.934477 * eV, 1.935988 * eV, 1.937500 * eV, 1.939015 * eV, 1.940532 * eV, 1.942052 * eV, 1.943574 * eV, 1.945098 * eV, 1.946625 * eV, 1.948154 * eV, 1.949686 * eV, 1.951220 * eV, 1.952756 * eV, 1.954295 * eV, 1.955836 * eV, 1.957380 * eV,
                                             1.958926 * eV, 1.960474 * eV, 1.962025 * eV, 1.963579 * eV, 1.965135 * eV, 1.966693 * eV, 1.968254 * eV, 1.969817 * eV, 1.971383 * eV, 1.972951 * eV, 1.974522 * eV, 1.976096 * eV, 1.977671 * eV, 1.979250 * eV, 1.980831 * eV, 1.982414 * eV, 1.984000 * eV, 1.985588 * eV, 1.987179 * eV, 1.988773 * eV, 1.990369 * eV, 1.991968 * eV, 1.993569 * eV,
                                             1.995173 * eV, 1.996779 * eV, 1.998388 * eV, 2.000000 * eV, 2.001614 * eV, 2.003231 * eV, 2.004850 * eV, 2.006472 * eV, 2.008097 * eV, 2.009724 * eV, 2.011354 * eV, 2.012987 * eV, 2.014622 * eV, 2.016260 * eV, 2.017901 * eV, 2.019544 * eV, 2.021190 * eV, 2.022838 * eV, 2.024490 * eV, 2.026144 * eV, 2.027800 * eV, 2.029460 * eV, 2.031122 * eV,
                                             2.032787 * eV, 2.034454 * eV, 2.036125 * eV, 2.037798 * eV, 2.039474 * eV, 2.041152 * eV, 2.042834 * eV, 2.044518 * eV, 2.046205 * eV, 2.047894 * eV, 2.049587 * eV, 2.051282 * eV, 2.052980 * eV, 2.054681 * eV, 2.056385 * eV, 2.058091 * eV, 2.059801 * eV, 2.061513 * eV, 2.063228 * eV, 2.064946 * eV, 2.066667 * eV, 2.068390 * eV, 2.070117 * eV,
                                             2.071846 * eV, 2.073579 * eV, 2.075314 * eV, 2.077052 * eV, 2.078793 * eV, 2.080537 * eV, 2.082284 * eV, 2.084034 * eV, 2.085786 * eV, 2.087542 * eV, 2.089301 * eV, 2.091062 * eV, 2.092827 * eV, 2.094595 * eV, 2.096365 * eV, 2.098139 * eV, 2.099915 * eV, 2.101695 * eV, 2.103478 * eV,
                                             2.105263 * eV, 2.107052 * eV, 2.108844 * eV, 2.110638 * eV, 2.112436 * eV, 2.114237 * eV, 2.116041 * eV, 2.117848 * eV, 2.119658 * eV, 2.121471 * eV, 2.123288 * eV, 2.125107 * eV, 2.126930 * eV, 2.128755 * eV, 2.130584 * eV, 2.132416 * eV, 2.134251 * eV, 2.136090 * eV, 2.137931 * eV, 2.139776 * eV, 2.141623 * eV, 2.143475 * eV, 2.145329 * eV,
                                             2.147186 * eV, 2.149047 * eV, 2.150911 * eV, 2.152778 * eV, 2.154648 * eV, 2.156522 * eV, 2.158399 * eV, 2.160279 * eV, 2.162162 * eV, 2.164049 * eV, 2.165939 * eV, 2.167832 * eV, 2.169729 * eV, 2.171629 * eV, 2.173532 * eV, 2.175439 * eV, 2.177349 * eV, 2.179262 * eV, 2.181179 * eV, 2.183099 * eV, 2.185022 * eV, 2.186949 * eV, 2.188879 * eV,
                                             2.190813 * eV, 2.192750 * eV, 2.194690 * eV, 2.196634 * eV, 2.198582 * eV, 2.200532 * eV, 2.202487 * eV, 2.204444 * eV, 2.206406 * eV, 2.208370 * eV, 2.210339 * eV, 2.212310 * eV, 2.214286 * eV, 2.216265 * eV, 2.218247 * eV, 2.220233 * eV, 2.222222 * eV, 2.224215 * eV, 2.226212 * eV, 2.228212 * eV, 2.230216 * eV, 2.232223 * eV, 2.234234 * eV,
                                             2.236249 * eV, 2.238267 * eV, 2.240289 * eV, 2.242315 * eV, 2.244344 * eV, 2.246377 * eV, 2.248413 * eV, 2.250454 * eV, 2.252498 * eV, 2.254545 * eV, 2.256597 * eV, 2.258652 * eV, 2.260711 * eV, 2.262774 * eV, 2.264840 * eV, 2.266910 * eV, 2.268984 * eV, 2.271062 * eV, 2.273144 * eV, 2.275229 * eV, 2.277319 * eV, 2.279412 * eV, 2.281509 * eV,
                                             2.283610 * eV, 2.285714 * eV, 2.287823 * eV, 2.289935 * eV, 2.292052 * eV, 2.294172 * eV, 2.296296 * eV, 2.298424 * eV, 2.300557 * eV, 2.302693 * eV, 2.304833 * eV, 2.306977 * eV, 2.309125 * eV, 2.311277 * eV, 2.313433 * eV, 2.315593 * eV, 2.317757 * eV, 2.319925 * eV, 2.322097 * eV, 2.324274 * eV, 2.326454 * eV, 2.328638 * eV, 2.330827 * eV,
                                             2.333020 * eV, 2.335217 * eV, 2.337418 * eV, 2.339623 * eV, 2.341832 * eV, 2.344045 * eV, 2.346263 * eV, 2.348485 * eV, 2.350711 * eV, 2.352941 * eV, 2.355176 * eV, 2.357414 * eV, 2.359657 * eV, 2.361905 * eV, 2.364156 * eV, 2.366412 * eV, 2.368672 * eV, 2.370937 * eV, 2.373206 * eV, 2.375479 * eV, 2.377756 * eV, 2.380038 * eV, 2.382325 * eV,
                                             2.384615 * eV, 2.386910 * eV, 2.389210 * eV, 2.391514 * eV, 2.393822 * eV, 2.396135 * eV, 2.398453 * eV, 2.400774 * eV, 2.403101 * eV, 2.405432 * eV, 2.407767 * eV, 2.410107 * eV, 2.412451 * eV, 2.414800 * eV, 2.417154 * eV, 2.419512 * eV, 2.421875 * eV, 2.424242 * eV, 2.426614 * eV, 2.428991 * eV, 2.431373 * eV, 2.433759 * eV, 2.436149 * eV,
                                             2.438545 * eV, 2.440945 * eV, 2.443350 * eV, 2.445759 * eV, 2.448174 * eV, 2.450593 * eV, 2.453017 * eV, 2.455446 * eV, 2.457879 * eV, 2.460317 * eV, 2.462761 * eV, 2.465209 * eV, 2.467662 * eV, 2.470120 * eV, 2.472582 * eV, 2.475050 * eV, 2.477522 * eV, 2.480000 * eV, 2.482482 * eV, 2.484970 * eV, 2.487462 * eV, 2.489960 * eV, 2.492462 * eV,
                                             2.494970 * eV, 2.497482 * eV, 2.500000 * eV, 2.502523 * eV, 2.505051 * eV, 2.507583 * eV, 2.510121 * eV, 2.512665 * eV, 2.515213 * eV, 2.517766 * eV, 2.520325 * eV, 2.522889 * eV, 2.525458 * eV, 2.528033 * eV, 2.530612 * eV, 2.533197 * eV, 2.535787 * eV, 2.538383 * eV, 2.540984 * eV,
                                             2.543590 * eV, 2.546201 * eV, 2.548818 * eV, 2.551440 * eV, 2.554068 * eV, 2.556701 * eV, 2.559340 * eV, 2.561983 * eV, 2.564633 * eV, 2.567288 * eV, 2.569948 * eV, 2.572614 * eV, 2.575286 * eV, 2.577963 * eV, 2.580645 * eV, 2.583333 * eV, 2.586027 * eV, 2.588727 * eV, 2.591432 * eV, 2.594142 * eV, 2.596859 * eV, 2.599581 * eV, 2.602308 * eV};

  std::vector<G4double> FastComponent =
      {
          0.160333, 0.172055, 0.180528, 0.185841, 0.188323, 0.188954, 0.186772, 0.182738, 0.178573, 0.175773, 0.174867, 0.173955, 0.172557, 0.171364, 0.170930, 0.170360, 0.168857, 0.167288, 0.165351, 0.163923, 0.162677, 0.161678, 0.161048, 0.160843, 0.160919, 0.160517, 0.160686, 0.160464,
          0.159976, 0.159308, 0.158286, 0.157136, 0.155732, 0.154752, 0.154047, 0.153539, 0.153576, 0.154763, 0.156705, 0.158406, 0.159616, 0.159562, 0.158966, 0.157962, 0.155876, 0.153398, 0.152418, 0.152958, 0.154043, 0.155506, 0.156696, 0.158246, 0.159557, 0.160035, 0.159984, 0.160655,
          0.161680, 0.162683, 0.163751, 0.164225, 0.164384, 0.163716, 0.162927, 0.161685, 0.161064, 0.161583, 0.163290, 0.166036, 0.169015, 0.172248, 0.174792, 0.177343, 0.178371, 0.179139, 0.179470, 0.179794, 0.180614, 0.181098, 0.181929, 0.182751, 0.184452, 0.184796, 0.185040, 0.185164,
          0.185262, 0.185692, 0.185288, 0.185155, 0.185544, 0.186761, 0.186675, 0.186026, 0.185206, 0.184357, 0.184081, 0.182930, 0.180970, 0.179324, 0.178990, 0.178807, 0.178816, 0.179548, 0.180189, 0.181705, 0.183860, 0.185555, 0.186864, 0.187659, 0.186991, 0.185885, 0.184938, 0.182451,
          0.179253, 0.176828, 0.175065, 0.174352, 0.174345, 0.174170, 0.174635, 0.176360, 0.177780, 0.178376, 0.179079, 0.179967, 0.180717, 0.181527, 0.182005, 0.182501, 0.182777, 0.182598, 0.181987, 0.181748, 0.181893, 0.182113, 0.182613, 0.182965, 0.183928, 0.184883, 0.185172, 0.185290,
          0.185926, 0.187299, 0.189183, 0.192071, 0.194687, 0.197445, 0.200288, 0.202261, 0.203751, 0.204776, 0.205879, 0.207200, 0.209689, 0.212624, 0.215543, 0.218708, 0.221917, 0.225334, 0.228164, 0.231296, 0.234249, 0.238200, 0.242831, 0.246744, 0.249958, 0.252404, 0.254520, 0.255287,
          0.255467, 0.255138, 0.255251, 0.256250, 0.257098, 0.258633, 0.260698, 0.263629, 0.266652, 0.269514, 0.271993, 0.274103, 0.275915, 0.276758, 0.277352, 0.277538, 0.277770, 0.278430, 0.279565, 0.280986, 0.282494, 0.284023, 0.284981, 0.285279, 0.285089, 0.284264, 0.283283, 0.282408,
          0.281352, 0.280817, 0.280748, 0.280999, 0.281389, 0.282203, 0.283156, 0.284094, 0.284769, 0.284727, 0.285041, 0.285578, 0.286377, 0.286919, 0.287022, 0.287172, 0.287323, 0.286838, 0.286101, 0.285711, 0.285562, 0.286258, 0.287810, 0.289147, 0.290564, 0.291878, 0.292197, 0.291950,
          0.291027, 0.289650, 0.288632, 0.288382, 0.288782, 0.289809, 0.290986, 0.292057, 0.293552, 0.294994, 0.296213, 0.297359, 0.298379, 0.299725, 0.301065, 0.301758,
          0.302152, 0.302418, 0.302455, 0.302965, 0.303988, 0.305269, 0.307792, 0.311004, 0.314233, 0.317157, 0.319612, 0.321208, 0.322833, 0.323933, 0.324668, 0.325648, 0.326384, 0.327127, 0.327983, 0.329782, 0.331478, 0.334153, 0.337734, 0.342331, 0.347829, 0.353863, 0.359909, 0.365554,
          0.371182, 0.375309, 0.378078, 0.380650, 0.383559, 0.386661, 0.391209, 0.396554, 0.403391, 0.412262, 0.421569, 0.430263, 0.438646, 0.446296, 0.452533, 0.459093, 0.464611, 0.470111, 0.475587, 0.480986, 0.486321, 0.492086, 0.497950, 0.503656, 0.510915, 0.518411, 0.525585, 0.531775,
          0.537243, 0.541844, 0.545787, 0.548832, 0.551114, 0.554734, 0.560204, 0.566683, 0.574083, 0.582899, 0.591700, 0.599719, 0.606075, 0.610675, 0.613892, 0.616678, 0.619201, 0.621949, 0.626338, 0.631770, 0.637622, 0.643314, 0.648892, 0.654411, 0.659824, 0.665181, 0.670375, 0.676088,
          0.683226, 0.690607, 0.698531, 0.708160, 0.718258, 0.728716, 0.739570, 0.751581, 0.763034, 0.775454, 0.786540, 0.797086, 0.808549, 0.820140, 0.831665, 0.843176, 0.856263, 0.868398, 0.881225, 0.892920, 0.904357, 0.915893, 0.928096, 0.939263, 0.948868, 0.959247, 0.969073, 0.979514,
          0.991217, 1.006180, 1.022176, 1.040957, 1.060646, 1.080315, 1.099629, 1.117168, 1.132367, 1.143713, 1.154007, 1.162971, 1.172804, 1.183047, 1.193364, 1.204806, 1.218254, 1.233768, 1.249340, 1.264735, 1.280843, 1.298822, 1.316305, 1.333060, 1.349401, 1.365012, 1.381080, 1.398043,
          1.414998, 1.433156, 1.453538, 1.475149, 1.497840, 1.522714, 1.549153, 1.575589, 1.602703, 1.629766, 1.657771, 1.686157, 1.713829, 1.740740, 1.768848, 1.797099, 1.826433, 1.856914, 1.887414, 1.920113, 1.952943, 1.984931, 2.016673, 2.048364, 2.080761, 2.114546, 2.150983, 2.187603,
          2.227391, 2.267608, 2.308318, 2.349979, 2.391574, 2.432560, 2.473686, 2.517020, 2.560338, 2.606682, 2.652806, 2.697589, 2.740990, 2.782212, 2.822549, 2.863372, 2.906545, 2.951182, 2.999788, 3.049974, 3.101279, 3.150571, 3.197309, 3.241397, 3.282194, 3.319780, 3.355298, 3.394046,
          3.434711, 3.481092, 3.529849, 3.581205, 3.636162, 3.692668, 3.749120, 3.806017, 3.865440, 3.920449, 3.976139, 4.028575, 4.079399, 4.129317, 4.178763, 4.227938, 4.276508, 4.328505, 4.377710, 4.431798, 4.485211, 4.542401, 4.602420, 4.665596, 4.733517, 4.805294, 4.881597, 4.955312,
          5.031172, 5.103682, 5.172749, 5.236611, 5.298137, 5.359899, 5.419967, 5.482172, 5.543176, 5.605148, 5.670492, 5.740138, 5.814321, 5.895414, 5.981730, 6.071641, 6.164834, 6.256723, 6.343300, 6.426013, 6.507092, 6.584824, 6.664619, 6.745062, 6.824841, 6.905505, 6.987358, 7.068448,
          7.145806, 7.223107, 7.299318, 7.382849, 7.469975, 7.558261, 7.648318, 7.739405, 7.832896, 7.927704, 8.024399, 8.117990, 8.213648, 8.309669, 8.403208, 8.491036, 8.573814, 8.653141, 8.732364, 8.812956, 8.896425, 8.982942, 9.074628, 9.172558, 9.271829, 9.373102, 9.471807, 9.568671, 9.664489, 9.764401, 9.862431, 9.961527,
          10.062514, 10.162395, 10.267956, 10.377316, 10.486914, 10.593941, 10.704643, 10.812764, 10.922728, 11.031806, 11.136382, 11.240701, 11.348914, 11.457710, 11.560809, 11.666111, 11.769687, 11.873744, 11.982856, 12.091494, 12.195096, 12.306485, 12.424388, 12.538396, 12.649503,
          12.755230, 12.852457, 12.955026, 13.057408, 13.151514, 13.249479, 13.360196, 13.475367, 13.590405, 13.703543, 13.809648, 13.920157, 14.030500, 14.136132, 14.234845, 14.337392, 14.440752, 14.542470, 14.643342, 14.742330, 14.837359, 14.933357, 15.030482, 15.121741, 15.217645,
          15.311870, 15.403404, 15.499368, 15.605598, 15.711020, 15.818623, 15.928037, 16.034052, 16.143130, 16.247351, 16.339258, 16.425389, 16.516449, 16.606260, 16.696443, 16.790204, 16.882196, 16.980250, 17.080543, 17.177801, 17.265764, 17.349557, 17.429280, 17.505393, 17.582362,
          17.656297, 17.732708, 17.816212, 17.908350, 18.003255, 18.095199, 18.181472, 18.269397, 18.354728, 18.434323, 18.510606, 18.596313, 18.693102, 18.802602, 18.911997, 19.015629, 19.124369, 19.229364, 19.323701, 19.402913, 19.483465, 19.560596, 19.641053, 19.718309, 19.792413,
          19.869586, 19.949725, 20.026719, 20.095968, 20.171002, 20.255738, 20.345770, 20.434825, 20.524169, 20.604079, 20.677508, 20.741404, 20.794106, 20.843678, 20.898596, 20.953907, 21.011152, 21.081034, 21.153868, 21.230743, 21.305027, 21.372700, 21.432274, 21.489282, 21.538526,
          21.580936, 21.626996, 21.670602, 21.712001, 21.748164, 21.781695, 21.812616, 21.837206, 21.857631, 21.878914, 21.906131, 21.934830, 21.957913, 21.976860, 21.991334, 22.003585, 22.005043, 21.998509, 21.990289, 21.987864, 21.988827, 21.987035, 21.980584, 21.963873, 21.947645,
          21.926436, 21.896811, 21.859359, 21.814038, 21.758221,
          21.698002, 21.635145, 21.566074, 21.493923, 21.423607, 21.353887, 21.278387, 21.189528, 21.081072, 20.957433, 20.818778, 20.670547, 20.513037, 20.350933, 20.191659, 20.036380, 19.873308, 19.701685, 19.519604, 19.329683, 19.135690, 18.936732, 18.729052, 18.519217, 18.310576,
          18.094135, 17.867046, 17.627899, 17.378721, 17.118091, 16.853280, 16.576317, 16.292254, 16.011360, 15.733297, 15.457866, 15.182900, 14.905330, 14.621737, 14.337595, 14.046097, 13.746192, 13.443646, 13.141727, 12.844686, 12.550631, 12.257647, 11.962531, 11.666829, 11.369029,
          11.064639, 10.758183, 10.449219, 10.146628,
          9.845579, 9.550573, 9.256683, 8.963058, 8.669924, 8.372660, 8.075375, 7.777387, 7.485712, 7.198002, 6.920792, 6.650151, 6.388837, 6.131463, 5.875763, 5.623275, 5.370905, 5.120390, 4.872820, 4.632578, 4.396777, 4.168619, 3.945906, 3.727595, 3.515392, 3.310932, 3.113700, 2.926979,
          2.751590, 2.588683, 2.439079, 2.300711, 2.169602, 2.044509, 1.925282, 1.810431, 1.701355, 1.600311, 1.508377, 1.428058, 1.361947, 1.306719, 1.260604, 1.221590, 1.187067, 1.155297, 1.125212, 1.094388, 1.064629, 1.039276, 1.018386, 1.002130, 0.991032, 0.985420, 0.984140};

  //** scintillation and optical properties **//
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 4.8);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 35. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0); // Ratio between fast component and total light yield. Ignore the documentation.


  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::GYAGG(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{
  // ########################################################
  // ### GAGG:Ce:Mg in a more complete fashion.
  // ### - Index of refraction taken from:
  // ###         Kozlova NS, Buzanov OA, Kasimova VM, Kozlova AP, Zabelina EV (2018) Optical characteristics of single crystal Gd3Al2Ga3O12 : Ce. Modern Electronic Materials 4(1): 7–12. https://doi.org/10.3897/j.moem.4.1.33240
  // ### - Emission measured in Lab 27, CERN.                                                                         L. Martinazzoli                   (2020)
  // ### - Absorption calculated measuring transmission of different ILM GAGG:Ce (not codoped!) in Lab 27, CERN.      N. Kratochwil, L. Martinazzoli    (2019)
  // ########

  double standard_light_yield = 40000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Ga = new G4Element("Gallium", "Ga", z = 31., a = 69.723 * g / mole);
  G4Element *Gd = new G4Element("Gadolinio", "Gd", z = 64., a = 157.25 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("GYAGG", density = 6.63 * g / cm3, 4);
  mat->AddElement(Ga, 3);
  mat->AddElement(Gd, 3);
  mat->AddElement(Al, 2);
  mat->AddElement(O, 12);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);
  //--------//

  // --- Refractive Index
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_RI = {1.23984 * eV,
                                           1.72271 * eV, 1.74623 * eV, 1.77132 * eV, 1.79807 * eV, 1.82468 * eV, 1.85209 * eV, 1.87931 * eV, 1.90734 * eV, 1.93840 * eV, 1.96824 * eV, 2.00017 * eV, 2.03315 * eV, 2.06599 * eV,
                                           2.10633 * eV, 2.13762 * eV, 2.17670 * eV, 2.21440 * eV, 2.25637 * eV, 2.29690 * eV, 2.34050 * eV, 2.38578 * eV, 2.42943 * eV, 2.53093 * eV, 2.58203 * eV, 2.63926 * eV, 2.69489 * eV,
                                           2.75950 * eV, 2.88396 * eV, 2.95302 * eV, 3.02545 * eV, 3.09601 * eV, 3.18161 * eV, 3.26590 * eV, 3.35473 * eV, 3.44161 * eV, 3.54034 * eV, 3.64512 * eV, 3.75608 * eV, 3.87418 * eV,
                                           3.99973 * eV, 4.13371 * eV, 4.27696 * eV, 4.43064 * eV, 4.59557 * eV, 4.76007 * eV, 4.95065 * eV, 5.15688 * eV, 5.38078 * eV, 5.62461 * eV};

  std::vector<G4double> RefractiveIndex = {1.8646638,
                                           1.87226, 1.87263, 1.87336, 1.87409, 1.87409, 1.87555, 1.87628, 1.87737, 1.87774, 1.87883, 1.87993, 1.88102, 1.88285, 1.88467,
                                           1.88613, 1.88832, 1.88942, 1.89015, 1.89234, 1.89307, 1.89453, 1.89599, 1.90073, 1.90401, 1.90547, 1.90693, 1.90839, 1.91277,
                                           1.91569, 1.92080, 1.91861, 1.91934, 1.91788, 1.92226, 1.93175, 1.94197, 1.93102, 1.93978, 1.93248, 1.94489, 1.95438, 1.96606,
                                           1.96752, 1.98212, 1.99818, 2.03102, 2.07628, 2.13394, 2.20912};

  // --- Intrinsic absorption spectrum
  //    Highest and Lowest energies are arbitrarily set.

  std::vector<G4double> PhotonEnergy_ABS =
      {1.49849 * eV, 1.50943 * eV, 1.52054 * eV, 1.53181 * eV, 1.54325 * eV, 1.55486 * eV, 1.56665 * eV, 1.57861 * eV, 1.59076 * eV,
       1.6031 * eV, 1.61564 * eV, 1.62837 * eV, 1.6413 * eV, 1.65444 * eV, 1.66779 * eV, 1.68136 * eV, 1.69515 * eV, 1.70917 * eV,
       1.72342 * eV, 1.73791 * eV, 1.75265 * eV, 1.76764 * eV, 1.78289 * eV, 1.7984 * eV, 1.81419 * eV, 1.83026 * eV, 1.84661 * eV,
       1.86326 * eV, 1.88021 * eV, 1.89748 * eV, 1.91506 * eV, 1.93297 * eV, 1.95122 * eV, 1.96982 * eV, 1.98877 * eV, 2.0081 * eV,
       2.0278 * eV, 2.04789 * eV, 2.06839 * eV, 2.0893 * eV, 2.11064 * eV, 2.13242 * eV, 2.15465 * eV, 2.17735 * eV, 2.20053 * eV,
       2.22422 * eV, 2.23022 * eV, 2.24231 * eV, 2.25455 * eV, 2.26691 * eV, 2.27941 * eV, 2.29205 * eV, 2.30483 * eV, 2.31776 * eV,
       2.33083 * eV, 2.34405 * eV, 2.35741 * eV, 2.37094 * eV, 2.38462 * eV, 2.39845 * eV, 2.41245 * eV, 2.42661 * eV, 2.44094 * eV,
       2.45545 * eV, 2.47012 * eV, 2.48497 * eV, 2.5 * eV, 2.51521 * eV, 2.53061 * eV, 2.5462 * eV, 2.56198 * eV, 2.57796 * eV,
       2.59414 * eV, 2.61053 * eV, 2.62712 * eV, 2.64392 * eV, 2.66094 * eV, 2.67819 * eV, 2.71335 * eV, 2.73128 * eV, 2.74945 * eV,
       2.76786 * eV, 2.78652 * eV, 2.80543 * eV, 2.8246 * eV, 2.84404 * eV, 2.86374 * eV, 2.88372 * eV, 2.90398 * eV, 2.92453 * eV,
       2.94537 * eV, 2.96651 * eV, 2.98795 * eV, 3.00971 * eV, 3.03178 * eV, 3.05419 * eV, 3.07692 * eV, 3.1 * eV, 3.12343 * eV,
       3.14721 * eV, 3.17136 * eV, 3.19588 * eV, 3.22078 * eV, 3.24607 * eV, 3.27177 * eV, 3.29787 * eV, 3.3244 * eV, 3.35135 * eV,
       3.37875 * eV, 3.40659 * eV, 3.4349 * eV, 3.46369 * eV, 3.49296 * eV, 3.52273 * eV, 3.58382 * eV, 3.61516 * eV, 3.67953 * eV,
       3.71257 * eV, 3.78049 * eV, 3.92405 * eV, 3.96166 * eV, 4 * eV, 4.03909 * eV, 4.07895 * eV, 4.1196 * eV, 4.16107 * eV,
       4.20339 * eV, 4.24658 * eV, 4.29066 * eV, 4.33566 * eV, 4.38163 * eV, 4.42857 * eV, 4.47653 * eV, 4.52555 * eV, 4.62687 * eV,
       4.67925 * eV, 4.78764 * eV, 4.96 * eV, 5.62461 * eV};

  std::vector<G4double> Absorption =
      {955.954000 * mm, 668.943000 * mm, 614.032000 * mm, 467.353000 * mm, 559.162000 * mm, 579.555000 * mm, 650.626000 * mm, 535.162000 * mm, 524.755000 * mm,
       540.255000 * mm, 600.531000 * mm, 519.526000 * mm, 526.569000 * mm, 516.447000 * mm, 502.306000 * mm, 518.467000 * mm, 522.762000 * mm, 503.951000 * mm,
       537.711000 * mm, 520.839000 * mm, 553.001000 * mm, 488.909000 * mm, 521.548000 * mm, 471.766000 * mm, 450.077000 * mm, 404.852000 * mm, 441.221000 * mm,
       440.960000 * mm, 411.248000 * mm, 380.195000 * mm, 399.852000 * mm, 380.692000 * mm, 372.110000 * mm, 362.841000 * mm, 370.628000 * mm, 355.130000 * mm,
       371.095000 * mm, 389.190000 * mm, 390.557000 * mm, 376.662000 * mm, 394.540000 * mm, 419.485000 * mm, 423.900000 * mm, 424.207000 * mm, 459.364000 * mm,
       432.117000 * mm, 450.723000 * mm, 444.802000 * mm, 451.629000 * mm, 415.643000 * mm, 458.704000 * mm, 473.048000 * mm, 388.097000 * mm, 445.714000 * mm,
       356.658000 * mm, 362.018000 * mm, 323.960000 * mm, 249.410000 * mm, 222.770000 * mm, 173.466000 * mm, 126.428000 * mm, 94.944500 * mm, 64.388500 * mm,
       45.198300 * mm, 30.697900 * mm, 20.705400 * mm, 14.095600 * mm, 9.563980 * mm, 6.555540 * mm, 4.590660 * mm, 3.251770 * mm, 2.439640 * mm, 1.899230 * mm,
       1.561530 * mm, 1.644290 * mm, 1.454600 * mm, 1.344050 * mm, 1.392430 * mm, 1.474630 * mm, 1.365870 * mm, 1.418190 * mm, 1.449410 * mm, 1.429420 * mm, 1.588940 * mm,
       1.456210 * mm, 1.313570 * mm, 1.626080 * mm, 1.611680 * mm, 1.429990 * mm, 1.472460 * mm, 1.501370 * mm, 1.565330 * mm, 1.556520 * mm, 1.413260 * mm, 1.651750 * mm,
       1.532130 * mm, 1.908330 * mm, 2.906480 * mm, 4.388340 * mm, 6.664950 * mm, 9.720680 * mm, 12.470900 * mm, 13.226400 * mm, 11.510300 * mm, 8.747250 * mm, 6.425540 * mm,
       4.638230 * mm, 3.356940 * mm, 2.389330 * mm, 1.730910 * mm, 1.621300 * mm, 1.349290 * mm, 1.371340 * mm, 1.454750 * mm, 1.353480 * mm, 1.092090 * mm, 1.486040 * mm,
       1.375890 * mm, 1.153950 * mm, 1.623740 * mm, 1.443300 * mm, 1.605000 * mm, 1.705960 * mm, 1.510680 * mm, 1.525980 * mm, 1.586010 * mm, 1.616290 * mm, 1.489230 * mm,
       1.483450 * mm, 1.411050 * mm, 1.685210 * mm, 1.409220 * mm, 1.232600 * mm, 1.707510 * mm, 1.382160 * mm, 1.322320 * mm, 1.441060 * mm, 1.478580 * mm, 0 * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  //      Taken straight outta the spectrophotometer.
  //      Hope this doesn't kill the performance.      O.o'

  std::vector<G4double> PhotonEnergy_FAST = {1.425287 * eV, 1.426107 * eV, 1.426928 * eV, 1.427749 * eV, 1.428571 * eV, 1.429395 * eV, 1.430219 * eV, 1.431044 * eV, 1.431871 * eV, 1.432698 * eV, 1.433526 * eV, 1.434355 * eV,
                                             1.435185 * eV, 1.436016 * eV, 1.436848 * eV, 1.437681 * eV, 1.438515 * eV, 1.439350 * eV, 1.440186 * eV, 1.441023 * eV, 1.441860 * eV, 1.442699 * eV, 1.443539 * eV, 1.444380 * eV, 1.445221 * eV, 1.446064 * eV, 1.446908 * eV, 1.447752 * eV,
                                             1.448598 * eV, 1.449445 * eV, 1.450292 * eV, 1.451141 * eV, 1.451991 * eV, 1.452841 * eV, 1.453693 * eV, 1.454545 * eV, 1.455399 * eV, 1.456254 * eV, 1.457109 * eV, 1.457966 * eV, 1.458824 * eV, 1.459682 * eV, 1.460542 * eV, 1.461402 * eV,
                                             1.462264 * eV, 1.463127 * eV, 1.463991 * eV, 1.464855 * eV, 1.465721 * eV, 1.466588 * eV, 1.467456 * eV, 1.468324 * eV, 1.469194 * eV, 1.470065 * eV, 1.470937 * eV, 1.471810 * eV, 1.472684 * eV, 1.473559 * eV, 1.474435 * eV, 1.475312 * eV,
                                             1.476190 * eV, 1.477070 * eV, 1.477950 * eV, 1.478831 * eV, 1.479714 * eV, 1.480597 * eV, 1.481481 * eV, 1.482367 * eV, 1.483254 * eV, 1.484141 * eV, 1.485030 * eV, 1.485920 * eV, 1.486811 * eV, 1.487702 * eV, 1.488595 * eV, 1.489489 * eV,
                                             1.490385 * eV, 1.491281 * eV, 1.492178 * eV, 1.493076 * eV, 1.493976 * eV, 1.494876 * eV, 1.495778 * eV, 1.496681 * eV, 1.497585 * eV, 1.498489 * eV, 1.499395 * eV, 1.500302 * eV, 1.501211 * eV, 1.502120 * eV, 1.503030 * eV, 1.503942 * eV,
                                             1.504854 * eV, 1.505768 * eV, 1.506683 * eV, 1.507599 * eV, 1.508516 * eV, 1.509434 * eV, 1.510353 * eV, 1.511274 * eV, 1.512195 * eV, 1.513118 * eV, 1.514042 * eV, 1.514966 * eV, 1.515892 * eV, 1.516820 * eV, 1.517748 * eV, 1.518677 * eV,
                                             1.519608 * eV, 1.520540 * eV, 1.521472 * eV, 1.522406 * eV, 1.523342 * eV, 1.524278 * eV, 1.525215 * eV, 1.526154 * eV, 1.527094 * eV, 1.528035 * eV, 1.528977 * eV, 1.529920 * eV, 1.530864 * eV, 1.531810 * eV, 1.532756 * eV, 1.533704 * eV,
                                             1.534653 * eV, 1.535604 * eV, 1.536555 * eV, 1.537508 * eV, 1.538462 * eV, 1.539417 * eV, 1.540373 * eV, 1.541330 * eV, 1.542289 * eV, 1.543248 * eV, 1.544209 * eV, 1.545171 * eV, 1.546135 * eV, 1.547099 * eV, 1.548065 * eV, 1.549032 * eV,
                                             1.550000 * eV, 1.550969 * eV, 1.551940 * eV, 1.552912 * eV, 1.553885 * eV, 1.554859 * eV, 1.555834 * eV, 1.556811 * eV, 1.557789 * eV, 1.558768 * eV, 1.559748 * eV, 1.560730 * eV, 1.561713 * eV, 1.562697 * eV, 1.563682 * eV, 1.564669 * eV,
                                             1.565657 * eV, 1.566646 * eV, 1.567636 * eV, 1.568627 * eV, 1.569620 * eV, 1.570614 * eV, 1.571610 * eV, 1.572606 * eV, 1.573604 * eV, 1.574603 * eV, 1.575604 * eV, 1.576605 * eV, 1.577608 * eV, 1.578612 * eV, 1.579618 * eV, 1.580625 * eV, 1.581633 * eV, 1.582642 * eV, 1.583653 * eV, 1.584665 * eV, 1.585678 * eV, 1.586692 * eV, 1.587708 * eV,
                                             1.588725 * eV, 1.589744 * eV, 1.590763 * eV, 1.591784 * eV, 1.592807 * eV, 1.593830 * eV, 1.594855 * eV, 1.595882 * eV, 1.596909 * eV, 1.597938 * eV, 1.598968 * eV, 1.600000 * eV, 1.601033 * eV, 1.602067 * eV, 1.603103 * eV, 1.604140 * eV, 1.605178 * eV, 1.606218 * eV, 1.607259 * eV, 1.608301 * eV, 1.609345 * eV, 1.610390 * eV, 1.611436 * eV,
                                             1.612484 * eV, 1.613533 * eV, 1.614583 * eV, 1.615635 * eV, 1.616688 * eV, 1.617743 * eV, 1.618799 * eV, 1.619856 * eV, 1.620915 * eV, 1.621975 * eV, 1.623037 * eV, 1.624100 * eV, 1.625164 * eV, 1.626230 * eV, 1.627297 * eV, 1.628365 * eV, 1.629435 * eV, 1.630506 * eV, 1.631579 * eV, 1.632653 * eV, 1.633729 * eV, 1.634806 * eV, 1.635884 * eV,
                                             1.636964 * eV, 1.638045 * eV, 1.639128 * eV, 1.640212 * eV, 1.641297 * eV, 1.642384 * eV, 1.643472 * eV, 1.644562 * eV, 1.645654 * eV, 1.646746 * eV, 1.647841 * eV, 1.648936 * eV, 1.650033 * eV, 1.651132 * eV, 1.652232 * eV, 1.653333 * eV, 1.654436 * eV, 1.655541 * eV, 1.656647 * eV, 1.657754 * eV, 1.658863 * eV, 1.659973 * eV, 1.661085 * eV,
                                             1.662198 * eV, 1.663313 * eV, 1.664430 * eV, 1.665547 * eV, 1.666667 * eV, 1.667787 * eV, 1.668910 * eV, 1.670034 * eV, 1.671159 * eV, 1.672286 * eV, 1.673414 * eV, 1.674544 * eV, 1.675676 * eV, 1.676809 * eV, 1.677943 * eV, 1.679079 * eV, 1.680217 * eV, 1.681356 * eV, 1.682497 * eV, 1.683639 * eV, 1.684783 * eV, 1.685928 * eV, 1.687075 * eV,
                                             1.688223 * eV, 1.689373 * eV, 1.690525 * eV, 1.691678 * eV, 1.692833 * eV, 1.693989 * eV, 1.695147 * eV, 1.696306 * eV, 1.697467 * eV, 1.698630 * eV, 1.699794 * eV, 1.700960 * eV, 1.702128 * eV, 1.703297 * eV, 1.704467 * eV, 1.705640 * eV, 1.706813 * eV, 1.707989 * eV, 1.709166 * eV, 1.710345 * eV, 1.711525 * eV, 1.712707 * eV, 1.713891 * eV,
                                             1.715076 * eV, 1.716263 * eV, 1.717452 * eV, 1.718642 * eV, 1.719834 * eV, 1.721027 * eV, 1.722222 * eV, 1.723419 * eV, 1.724618 * eV, 1.725818 * eV, 1.727019 * eV, 1.728223 * eV, 1.729428 * eV, 1.730635 * eV, 1.731844 * eV, 1.733054 * eV, 1.734266 * eV, 1.735479 * eV, 1.736695 * eV, 1.737912 * eV, 1.739130 * eV, 1.740351 * eV, 1.741573 * eV,
                                             1.742797 * eV, 1.744023 * eV, 1.745250 * eV, 1.746479 * eV, 1.747710 * eV, 1.748942 * eV, 1.750176 * eV, 1.751412 * eV, 1.752650 * eV, 1.753890 * eV, 1.755131 * eV, 1.756374 * eV, 1.757619 * eV, 1.758865 * eV, 1.760114 * eV, 1.761364 * eV, 1.762615 * eV, 1.763869 * eV, 1.765125 * eV, 1.766382 * eV, 1.767641 * eV, 1.768902 * eV, 1.770164 * eV,
                                             1.771429 * eV, 1.772695 * eV, 1.773963 * eV, 1.775233 * eV, 1.776504 * eV, 1.777778 * eV, 1.779053 * eV, 1.780330 * eV, 1.781609 * eV, 1.782890 * eV, 1.784173 * eV, 1.785457 * eV, 1.786744 * eV, 1.788032 * eV, 1.789322 * eV, 1.790614 * eV, 1.791908 * eV, 1.793203 * eV, 1.794501 * eV,
                                             1.795800 * eV, 1.797101 * eV, 1.798405 * eV, 1.799710 * eV, 1.801017 * eV, 1.802326 * eV, 1.803636 * eV, 1.804949 * eV, 1.806264 * eV, 1.807580 * eV, 1.808899 * eV, 1.810219 * eV, 1.811541 * eV, 1.812865 * eV, 1.814192 * eV, 1.815520 * eV, 1.816850 * eV, 1.818182 * eV, 1.819516 * eV, 1.820852 * eV, 1.822190 * eV, 1.823529 * eV, 1.824871 * eV,
                                             1.826215 * eV, 1.827561 * eV, 1.828909 * eV, 1.830258 * eV, 1.831610 * eV, 1.832964 * eV, 1.834320 * eV, 1.835677 * eV, 1.837037 * eV, 1.838399 * eV, 1.839763 * eV, 1.841128 * eV, 1.842496 * eV, 1.843866 * eV, 1.845238 * eV, 1.846612 * eV, 1.847988 * eV, 1.849366 * eV, 1.850746 * eV, 1.852128 * eV, 1.853513 * eV, 1.854899 * eV, 1.856287 * eV,
                                             1.857678 * eV, 1.859070 * eV, 1.860465 * eV, 1.861862 * eV, 1.863261 * eV, 1.864662 * eV, 1.866065 * eV, 1.867470 * eV, 1.868877 * eV, 1.870287 * eV, 1.871698 * eV, 1.873112 * eV, 1.874528 * eV, 1.875946 * eV, 1.877366 * eV, 1.878788 * eV, 1.880212 * eV, 1.881639 * eV, 1.883068 * eV, 1.884498 * eV, 1.885932 * eV, 1.887367 * eV, 1.888804 * eV,
                                             1.890244 * eV, 1.891686 * eV, 1.893130 * eV, 1.894576 * eV, 1.896024 * eV, 1.897475 * eV, 1.898928 * eV, 1.900383 * eV, 1.901840 * eV, 1.903300 * eV, 1.904762 * eV, 1.906226 * eV, 1.907692 * eV, 1.909161 * eV, 1.910632 * eV, 1.912105 * eV, 1.913580 * eV, 1.915058 * eV, 1.916538 * eV, 1.918020 * eV, 1.919505 * eV, 1.920991 * eV, 1.922481 * eV,
                                             1.923972 * eV, 1.925466 * eV, 1.926962 * eV, 1.928460 * eV, 1.929961 * eV, 1.931464 * eV, 1.932970 * eV, 1.934477 * eV, 1.935988 * eV, 1.937500 * eV, 1.939015 * eV, 1.940532 * eV, 1.942052 * eV, 1.943574 * eV, 1.945098 * eV, 1.946625 * eV, 1.948154 * eV, 1.949686 * eV, 1.951220 * eV, 1.952756 * eV, 1.954295 * eV, 1.955836 * eV, 1.957380 * eV,
                                             1.958926 * eV, 1.960474 * eV, 1.962025 * eV, 1.963579 * eV, 1.965135 * eV, 1.966693 * eV, 1.968254 * eV, 1.969817 * eV, 1.971383 * eV, 1.972951 * eV, 1.974522 * eV, 1.976096 * eV, 1.977671 * eV, 1.979250 * eV, 1.980831 * eV, 1.982414 * eV, 1.984000 * eV, 1.985588 * eV, 1.987179 * eV, 1.988773 * eV, 1.990369 * eV, 1.991968 * eV, 1.993569 * eV,
                                             1.995173 * eV, 1.996779 * eV, 1.998388 * eV, 2.000000 * eV, 2.001614 * eV, 2.003231 * eV, 2.004850 * eV, 2.006472 * eV, 2.008097 * eV, 2.009724 * eV, 2.011354 * eV, 2.012987 * eV, 2.014622 * eV, 2.016260 * eV, 2.017901 * eV, 2.019544 * eV, 2.021190 * eV, 2.022838 * eV, 2.024490 * eV, 2.026144 * eV, 2.027800 * eV, 2.029460 * eV, 2.031122 * eV,
                                             2.032787 * eV, 2.034454 * eV, 2.036125 * eV, 2.037798 * eV, 2.039474 * eV, 2.041152 * eV, 2.042834 * eV, 2.044518 * eV, 2.046205 * eV, 2.047894 * eV, 2.049587 * eV, 2.051282 * eV, 2.052980 * eV, 2.054681 * eV, 2.056385 * eV, 2.058091 * eV, 2.059801 * eV, 2.061513 * eV, 2.063228 * eV, 2.064946 * eV, 2.066667 * eV, 2.068390 * eV, 2.070117 * eV,
                                             2.071846 * eV, 2.073579 * eV, 2.075314 * eV, 2.077052 * eV, 2.078793 * eV, 2.080537 * eV, 2.082284 * eV, 2.084034 * eV, 2.085786 * eV, 2.087542 * eV, 2.089301 * eV, 2.091062 * eV, 2.092827 * eV, 2.094595 * eV, 2.096365 * eV, 2.098139 * eV, 2.099915 * eV, 2.101695 * eV, 2.103478 * eV,
                                             2.105263 * eV, 2.107052 * eV, 2.108844 * eV, 2.110638 * eV, 2.112436 * eV, 2.114237 * eV, 2.116041 * eV, 2.117848 * eV, 2.119658 * eV, 2.121471 * eV, 2.123288 * eV, 2.125107 * eV, 2.126930 * eV, 2.128755 * eV, 2.130584 * eV, 2.132416 * eV, 2.134251 * eV, 2.136090 * eV, 2.137931 * eV, 2.139776 * eV, 2.141623 * eV, 2.143475 * eV, 2.145329 * eV,
                                             2.147186 * eV, 2.149047 * eV, 2.150911 * eV, 2.152778 * eV, 2.154648 * eV, 2.156522 * eV, 2.158399 * eV, 2.160279 * eV, 2.162162 * eV, 2.164049 * eV, 2.165939 * eV, 2.167832 * eV, 2.169729 * eV, 2.171629 * eV, 2.173532 * eV, 2.175439 * eV, 2.177349 * eV, 2.179262 * eV, 2.181179 * eV, 2.183099 * eV, 2.185022 * eV, 2.186949 * eV, 2.188879 * eV,
                                             2.190813 * eV, 2.192750 * eV, 2.194690 * eV, 2.196634 * eV, 2.198582 * eV, 2.200532 * eV, 2.202487 * eV, 2.204444 * eV, 2.206406 * eV, 2.208370 * eV, 2.210339 * eV, 2.212310 * eV, 2.214286 * eV, 2.216265 * eV, 2.218247 * eV, 2.220233 * eV, 2.222222 * eV, 2.224215 * eV, 2.226212 * eV, 2.228212 * eV, 2.230216 * eV, 2.232223 * eV, 2.234234 * eV,
                                             2.236249 * eV, 2.238267 * eV, 2.240289 * eV, 2.242315 * eV, 2.244344 * eV, 2.246377 * eV, 2.248413 * eV, 2.250454 * eV, 2.252498 * eV, 2.254545 * eV, 2.256597 * eV, 2.258652 * eV, 2.260711 * eV, 2.262774 * eV, 2.264840 * eV, 2.266910 * eV, 2.268984 * eV, 2.271062 * eV, 2.273144 * eV, 2.275229 * eV, 2.277319 * eV, 2.279412 * eV, 2.281509 * eV,
                                             2.283610 * eV, 2.285714 * eV, 2.287823 * eV, 2.289935 * eV, 2.292052 * eV, 2.294172 * eV, 2.296296 * eV, 2.298424 * eV, 2.300557 * eV, 2.302693 * eV, 2.304833 * eV, 2.306977 * eV, 2.309125 * eV, 2.311277 * eV, 2.313433 * eV, 2.315593 * eV, 2.317757 * eV, 2.319925 * eV, 2.322097 * eV, 2.324274 * eV, 2.326454 * eV, 2.328638 * eV, 2.330827 * eV,
                                             2.333020 * eV, 2.335217 * eV, 2.337418 * eV, 2.339623 * eV, 2.341832 * eV, 2.344045 * eV, 2.346263 * eV, 2.348485 * eV, 2.350711 * eV, 2.352941 * eV, 2.355176 * eV, 2.357414 * eV, 2.359657 * eV, 2.361905 * eV, 2.364156 * eV, 2.366412 * eV, 2.368672 * eV, 2.370937 * eV, 2.373206 * eV, 2.375479 * eV, 2.377756 * eV, 2.380038 * eV, 2.382325 * eV,
                                             2.384615 * eV, 2.386910 * eV, 2.389210 * eV, 2.391514 * eV, 2.393822 * eV, 2.396135 * eV, 2.398453 * eV, 2.400774 * eV, 2.403101 * eV, 2.405432 * eV, 2.407767 * eV, 2.410107 * eV, 2.412451 * eV, 2.414800 * eV, 2.417154 * eV, 2.419512 * eV, 2.421875 * eV, 2.424242 * eV, 2.426614 * eV, 2.428991 * eV, 2.431373 * eV, 2.433759 * eV, 2.436149 * eV,
                                             2.438545 * eV, 2.440945 * eV, 2.443350 * eV, 2.445759 * eV, 2.448174 * eV, 2.450593 * eV, 2.453017 * eV, 2.455446 * eV, 2.457879 * eV, 2.460317 * eV, 2.462761 * eV, 2.465209 * eV, 2.467662 * eV, 2.470120 * eV, 2.472582 * eV, 2.475050 * eV, 2.477522 * eV, 2.480000 * eV, 2.482482 * eV, 2.484970 * eV, 2.487462 * eV, 2.489960 * eV, 2.492462 * eV,
                                             2.494970 * eV, 2.497482 * eV, 2.500000 * eV, 2.502523 * eV, 2.505051 * eV, 2.507583 * eV, 2.510121 * eV, 2.512665 * eV, 2.515213 * eV, 2.517766 * eV, 2.520325 * eV, 2.522889 * eV, 2.525458 * eV, 2.528033 * eV, 2.530612 * eV, 2.533197 * eV, 2.535787 * eV, 2.538383 * eV, 2.540984 * eV,
                                             2.543590 * eV, 2.546201 * eV, 2.548818 * eV, 2.551440 * eV, 2.554068 * eV, 2.556701 * eV, 2.559340 * eV, 2.561983 * eV, 2.564633 * eV, 2.567288 * eV, 2.569948 * eV, 2.572614 * eV, 2.575286 * eV, 2.577963 * eV, 2.580645 * eV, 2.583333 * eV, 2.586027 * eV, 2.588727 * eV, 2.591432 * eV, 2.594142 * eV, 2.596859 * eV, 2.599581 * eV, 2.602308 * eV};

  std::vector<G4double> FastComponent =
      {
          0.160333, 0.172055, 0.180528, 0.185841, 0.188323, 0.188954, 0.186772, 0.182738, 0.178573, 0.175773, 0.174867, 0.173955, 0.172557, 0.171364, 0.170930, 0.170360, 0.168857, 0.167288, 0.165351, 0.163923, 0.162677, 0.161678, 0.161048, 0.160843, 0.160919, 0.160517, 0.160686, 0.160464,
          0.159976, 0.159308, 0.158286, 0.157136, 0.155732, 0.154752, 0.154047, 0.153539, 0.153576, 0.154763, 0.156705, 0.158406, 0.159616, 0.159562, 0.158966, 0.157962, 0.155876, 0.153398, 0.152418, 0.152958, 0.154043, 0.155506, 0.156696, 0.158246, 0.159557, 0.160035, 0.159984, 0.160655,
          0.161680, 0.162683, 0.163751, 0.164225, 0.164384, 0.163716, 0.162927, 0.161685, 0.161064, 0.161583, 0.163290, 0.166036, 0.169015, 0.172248, 0.174792, 0.177343, 0.178371, 0.179139, 0.179470, 0.179794, 0.180614, 0.181098, 0.181929, 0.182751, 0.184452, 0.184796, 0.185040, 0.185164,
          0.185262, 0.185692, 0.185288, 0.185155, 0.185544, 0.186761, 0.186675, 0.186026, 0.185206, 0.184357, 0.184081, 0.182930, 0.180970, 0.179324, 0.178990, 0.178807, 0.178816, 0.179548, 0.180189, 0.181705, 0.183860, 0.185555, 0.186864, 0.187659, 0.186991, 0.185885, 0.184938, 0.182451,
          0.179253, 0.176828, 0.175065, 0.174352, 0.174345, 0.174170, 0.174635, 0.176360, 0.177780, 0.178376, 0.179079, 0.179967, 0.180717, 0.181527, 0.182005, 0.182501, 0.182777, 0.182598, 0.181987, 0.181748, 0.181893, 0.182113, 0.182613, 0.182965, 0.183928, 0.184883, 0.185172, 0.185290,
          0.185926, 0.187299, 0.189183, 0.192071, 0.194687, 0.197445, 0.200288, 0.202261, 0.203751, 0.204776, 0.205879, 0.207200, 0.209689, 0.212624, 0.215543, 0.218708, 0.221917, 0.225334, 0.228164, 0.231296, 0.234249, 0.238200, 0.242831, 0.246744, 0.249958, 0.252404, 0.254520, 0.255287,
          0.255467, 0.255138, 0.255251, 0.256250, 0.257098, 0.258633, 0.260698, 0.263629, 0.266652, 0.269514, 0.271993, 0.274103, 0.275915, 0.276758, 0.277352, 0.277538, 0.277770, 0.278430, 0.279565, 0.280986, 0.282494, 0.284023, 0.284981, 0.285279, 0.285089, 0.284264, 0.283283, 0.282408,
          0.281352, 0.280817, 0.280748, 0.280999, 0.281389, 0.282203, 0.283156, 0.284094, 0.284769, 0.284727, 0.285041, 0.285578, 0.286377, 0.286919, 0.287022, 0.287172, 0.287323, 0.286838, 0.286101, 0.285711, 0.285562, 0.286258, 0.287810, 0.289147, 0.290564, 0.291878, 0.292197, 0.291950,
          0.291027, 0.289650, 0.288632, 0.288382, 0.288782, 0.289809, 0.290986, 0.292057, 0.293552, 0.294994, 0.296213, 0.297359, 0.298379, 0.299725, 0.301065, 0.301758,
          0.302152, 0.302418, 0.302455, 0.302965, 0.303988, 0.305269, 0.307792, 0.311004, 0.314233, 0.317157, 0.319612, 0.321208, 0.322833, 0.323933, 0.324668, 0.325648, 0.326384, 0.327127, 0.327983, 0.329782, 0.331478, 0.334153, 0.337734, 0.342331, 0.347829, 0.353863, 0.359909, 0.365554,
          0.371182, 0.375309, 0.378078, 0.380650, 0.383559, 0.386661, 0.391209, 0.396554, 0.403391, 0.412262, 0.421569, 0.430263, 0.438646, 0.446296, 0.452533, 0.459093, 0.464611, 0.470111, 0.475587, 0.480986, 0.486321, 0.492086, 0.497950, 0.503656, 0.510915, 0.518411, 0.525585, 0.531775,
          0.537243, 0.541844, 0.545787, 0.548832, 0.551114, 0.554734, 0.560204, 0.566683, 0.574083, 0.582899, 0.591700, 0.599719, 0.606075, 0.610675, 0.613892, 0.616678, 0.619201, 0.621949, 0.626338, 0.631770, 0.637622, 0.643314, 0.648892, 0.654411, 0.659824, 0.665181, 0.670375, 0.676088,
          0.683226, 0.690607, 0.698531, 0.708160, 0.718258, 0.728716, 0.739570, 0.751581, 0.763034, 0.775454, 0.786540, 0.797086, 0.808549, 0.820140, 0.831665, 0.843176, 0.856263, 0.868398, 0.881225, 0.892920, 0.904357, 0.915893, 0.928096, 0.939263, 0.948868, 0.959247, 0.969073, 0.979514,
          0.991217, 1.006180, 1.022176, 1.040957, 1.060646, 1.080315, 1.099629, 1.117168, 1.132367, 1.143713, 1.154007, 1.162971, 1.172804, 1.183047, 1.193364, 1.204806, 1.218254, 1.233768, 1.249340, 1.264735, 1.280843, 1.298822, 1.316305, 1.333060, 1.349401, 1.365012, 1.381080, 1.398043,
          1.414998, 1.433156, 1.453538, 1.475149, 1.497840, 1.522714, 1.549153, 1.575589, 1.602703, 1.629766, 1.657771, 1.686157, 1.713829, 1.740740, 1.768848, 1.797099, 1.826433, 1.856914, 1.887414, 1.920113, 1.952943, 1.984931, 2.016673, 2.048364, 2.080761, 2.114546, 2.150983, 2.187603,
          2.227391, 2.267608, 2.308318, 2.349979, 2.391574, 2.432560, 2.473686, 2.517020, 2.560338, 2.606682, 2.652806, 2.697589, 2.740990, 2.782212, 2.822549, 2.863372, 2.906545, 2.951182, 2.999788, 3.049974, 3.101279, 3.150571, 3.197309, 3.241397, 3.282194, 3.319780, 3.355298, 3.394046,
          3.434711, 3.481092, 3.529849, 3.581205, 3.636162, 3.692668, 3.749120, 3.806017, 3.865440, 3.920449, 3.976139, 4.028575, 4.079399, 4.129317, 4.178763, 4.227938, 4.276508, 4.328505, 4.377710, 4.431798, 4.485211, 4.542401, 4.602420, 4.665596, 4.733517, 4.805294, 4.881597, 4.955312,
          5.031172, 5.103682, 5.172749, 5.236611, 5.298137, 5.359899, 5.419967, 5.482172, 5.543176, 5.605148, 5.670492, 5.740138, 5.814321, 5.895414, 5.981730, 6.071641, 6.164834, 6.256723, 6.343300, 6.426013, 6.507092, 6.584824, 6.664619, 6.745062, 6.824841, 6.905505, 6.987358, 7.068448,
          7.145806, 7.223107, 7.299318, 7.382849, 7.469975, 7.558261, 7.648318, 7.739405, 7.832896, 7.927704, 8.024399, 8.117990, 8.213648, 8.309669, 8.403208, 8.491036, 8.573814, 8.653141, 8.732364, 8.812956, 8.896425, 8.982942, 9.074628, 9.172558, 9.271829, 9.373102, 9.471807, 9.568671, 9.664489, 9.764401, 9.862431, 9.961527,
          10.062514, 10.162395, 10.267956, 10.377316, 10.486914, 10.593941, 10.704643, 10.812764, 10.922728, 11.031806, 11.136382, 11.240701, 11.348914, 11.457710, 11.560809, 11.666111, 11.769687, 11.873744, 11.982856, 12.091494, 12.195096, 12.306485, 12.424388, 12.538396, 12.649503,
          12.755230, 12.852457, 12.955026, 13.057408, 13.151514, 13.249479, 13.360196, 13.475367, 13.590405, 13.703543, 13.809648, 13.920157, 14.030500, 14.136132, 14.234845, 14.337392, 14.440752, 14.542470, 14.643342, 14.742330, 14.837359, 14.933357, 15.030482, 15.121741, 15.217645,
          15.311870, 15.403404, 15.499368, 15.605598, 15.711020, 15.818623, 15.928037, 16.034052, 16.143130, 16.247351, 16.339258, 16.425389, 16.516449, 16.606260, 16.696443, 16.790204, 16.882196, 16.980250, 17.080543, 17.177801, 17.265764, 17.349557, 17.429280, 17.505393, 17.582362,
          17.656297, 17.732708, 17.816212, 17.908350, 18.003255, 18.095199, 18.181472, 18.269397, 18.354728, 18.434323, 18.510606, 18.596313, 18.693102, 18.802602, 18.911997, 19.015629, 19.124369, 19.229364, 19.323701, 19.402913, 19.483465, 19.560596, 19.641053, 19.718309, 19.792413,
          19.869586, 19.949725, 20.026719, 20.095968, 20.171002, 20.255738, 20.345770, 20.434825, 20.524169, 20.604079, 20.677508, 20.741404, 20.794106, 20.843678, 20.898596, 20.953907, 21.011152, 21.081034, 21.153868, 21.230743, 21.305027, 21.372700, 21.432274, 21.489282, 21.538526,
          21.580936, 21.626996, 21.670602, 21.712001, 21.748164, 21.781695, 21.812616, 21.837206, 21.857631, 21.878914, 21.906131, 21.934830, 21.957913, 21.976860, 21.991334, 22.003585, 22.005043, 21.998509, 21.990289, 21.987864, 21.988827, 21.987035, 21.980584, 21.963873, 21.947645,
          21.926436, 21.896811, 21.859359, 21.814038, 21.758221,
          21.698002, 21.635145, 21.566074, 21.493923, 21.423607, 21.353887, 21.278387, 21.189528, 21.081072, 20.957433, 20.818778, 20.670547, 20.513037, 20.350933, 20.191659, 20.036380, 19.873308, 19.701685, 19.519604, 19.329683, 19.135690, 18.936732, 18.729052, 18.519217, 18.310576,
          18.094135, 17.867046, 17.627899, 17.378721, 17.118091, 16.853280, 16.576317, 16.292254, 16.011360, 15.733297, 15.457866, 15.182900, 14.905330, 14.621737, 14.337595, 14.046097, 13.746192, 13.443646, 13.141727, 12.844686, 12.550631, 12.257647, 11.962531, 11.666829, 11.369029,
          11.064639, 10.758183, 10.449219, 10.146628,
          9.845579, 9.550573, 9.256683, 8.963058, 8.669924, 8.372660, 8.075375, 7.777387, 7.485712, 7.198002, 6.920792, 6.650151, 6.388837, 6.131463, 5.875763, 5.623275, 5.370905, 5.120390, 4.872820, 4.632578, 4.396777, 4.168619, 3.945906, 3.727595, 3.515392, 3.310932, 3.113700, 2.926979,
          2.751590, 2.588683, 2.439079, 2.300711, 2.169602, 2.044509, 1.925282, 1.810431, 1.701355, 1.600311, 1.508377, 1.428058, 1.361947, 1.306719, 1.260604, 1.221590, 1.187067, 1.155297, 1.125212, 1.094388, 1.064629, 1.039276, 1.018386, 1.002130, 0.991032, 0.985420, 0.984140};

  //** scintillation and optical properties **//
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 4.8);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 36. * ns);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 97. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 0.80); // Ratio between fast component and total light yield. Ignore the documentation.
  mt->AddConstProperty("SCINTILLATIONYIELD2", 0.20); // Ratio between fast component and total light yield. Ignore the documentation.


  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::GFAG(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{
  // ########################################################
  // ### GAGG:Ce:Mg in a more complete fashion.
  // ### - Index of refraction taken from:
  // ###         Kozlova NS, Buzanov OA, Kasimova VM, Kozlova AP, Zabelina EV (2018) Optical characteristics of single crystal Gd3Al2Ga3O12 : Ce. Modern Electronic Materials 4(1): 7–12. https://doi.org/10.3897/j.moem.4.1.33240
  // ### - Emission measured in Lab 27, CERN.                                                                         L. Martinazzoli                   (2020)
  // ### - Absorption calculated measuring transmission of different ILM GAGG:Ce (not codoped!) in Lab 27, CERN.      N. Kratochwil, L. Martinazzoli    (2019)
  // ########

  double standard_light_yield = 35000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Ga = new G4Element("Gallium", "Ga", z = 31., a = 69.723 * g / mole);
  G4Element *Gd = new G4Element("Gadolinio", "Gd", z = 64., a = 157.25 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("GFAG", density = 6.63 * g / cm3, 4);
  mat->AddElement(Ga, 3);
  mat->AddElement(Gd, 3);
  mat->AddElement(Al, 2);
  mat->AddElement(O, 12);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);
  //--------//

  // --- Refractive Index
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_RI = {1.23984 * eV,
                                           1.72271 * eV, 1.74623 * eV, 1.77132 * eV, 1.79807 * eV, 1.82468 * eV, 1.85209 * eV, 1.87931 * eV, 1.90734 * eV, 1.93840 * eV, 1.96824 * eV, 2.00017 * eV, 2.03315 * eV, 2.06599 * eV,
                                           2.10633 * eV, 2.13762 * eV, 2.17670 * eV, 2.21440 * eV, 2.25637 * eV, 2.29690 * eV, 2.34050 * eV, 2.38578 * eV, 2.42943 * eV, 2.53093 * eV, 2.58203 * eV, 2.63926 * eV, 2.69489 * eV,
                                           2.75950 * eV, 2.88396 * eV, 2.95302 * eV, 3.02545 * eV, 3.09601 * eV, 3.18161 * eV, 3.26590 * eV, 3.35473 * eV, 3.44161 * eV, 3.54034 * eV, 3.64512 * eV, 3.75608 * eV, 3.87418 * eV,
                                           3.99973 * eV, 4.13371 * eV, 4.27696 * eV, 4.43064 * eV, 4.59557 * eV, 4.76007 * eV, 4.95065 * eV, 5.15688 * eV, 5.38078 * eV, 5.62461 * eV};

  std::vector<G4double> RefractiveIndex = {1.8646638,
                                           1.87226, 1.87263, 1.87336, 1.87409, 1.87409, 1.87555, 1.87628, 1.87737, 1.87774, 1.87883, 1.87993, 1.88102, 1.88285, 1.88467,
                                           1.88613, 1.88832, 1.88942, 1.89015, 1.89234, 1.89307, 1.89453, 1.89599, 1.90073, 1.90401, 1.90547, 1.90693, 1.90839, 1.91277,
                                           1.91569, 1.92080, 1.91861, 1.91934, 1.91788, 1.92226, 1.93175, 1.94197, 1.93102, 1.93978, 1.93248, 1.94489, 1.95438, 1.96606,
                                           1.96752, 1.98212, 1.99818, 2.03102, 2.07628, 2.13394, 2.20912};

  // --- Intrinsic absorption spectrum
  //    Highest and Lowest energies are arbitrarily set.

  std::vector<G4double> PhotonEnergy_ABS =
      {1.49849 * eV, 1.50943 * eV, 1.52054 * eV, 1.53181 * eV, 1.54325 * eV, 1.55486 * eV, 1.56665 * eV, 1.57861 * eV, 1.59076 * eV,
       1.6031 * eV, 1.61564 * eV, 1.62837 * eV, 1.6413 * eV, 1.65444 * eV, 1.66779 * eV, 1.68136 * eV, 1.69515 * eV, 1.70917 * eV,
       1.72342 * eV, 1.73791 * eV, 1.75265 * eV, 1.76764 * eV, 1.78289 * eV, 1.7984 * eV, 1.81419 * eV, 1.83026 * eV, 1.84661 * eV,
       1.86326 * eV, 1.88021 * eV, 1.89748 * eV, 1.91506 * eV, 1.93297 * eV, 1.95122 * eV, 1.96982 * eV, 1.98877 * eV, 2.0081 * eV,
       2.0278 * eV, 2.04789 * eV, 2.06839 * eV, 2.0893 * eV, 2.11064 * eV, 2.13242 * eV, 2.15465 * eV, 2.17735 * eV, 2.20053 * eV,
       2.22422 * eV, 2.23022 * eV, 2.24231 * eV, 2.25455 * eV, 2.26691 * eV, 2.27941 * eV, 2.29205 * eV, 2.30483 * eV, 2.31776 * eV,
       2.33083 * eV, 2.34405 * eV, 2.35741 * eV, 2.37094 * eV, 2.38462 * eV, 2.39845 * eV, 2.41245 * eV, 2.42661 * eV, 2.44094 * eV,
       2.45545 * eV, 2.47012 * eV, 2.48497 * eV, 2.5 * eV, 2.51521 * eV, 2.53061 * eV, 2.5462 * eV, 2.56198 * eV, 2.57796 * eV,
       2.59414 * eV, 2.61053 * eV, 2.62712 * eV, 2.64392 * eV, 2.66094 * eV, 2.67819 * eV, 2.71335 * eV, 2.73128 * eV, 2.74945 * eV,
       2.76786 * eV, 2.78652 * eV, 2.80543 * eV, 2.8246 * eV, 2.84404 * eV, 2.86374 * eV, 2.88372 * eV, 2.90398 * eV, 2.92453 * eV,
       2.94537 * eV, 2.96651 * eV, 2.98795 * eV, 3.00971 * eV, 3.03178 * eV, 3.05419 * eV, 3.07692 * eV, 3.1 * eV, 3.12343 * eV,
       3.14721 * eV, 3.17136 * eV, 3.19588 * eV, 3.22078 * eV, 3.24607 * eV, 3.27177 * eV, 3.29787 * eV, 3.3244 * eV, 3.35135 * eV,
       3.37875 * eV, 3.40659 * eV, 3.4349 * eV, 3.46369 * eV, 3.49296 * eV, 3.52273 * eV, 3.58382 * eV, 3.61516 * eV, 3.67953 * eV,
       3.71257 * eV, 3.78049 * eV, 3.92405 * eV, 3.96166 * eV, 4 * eV, 4.03909 * eV, 4.07895 * eV, 4.1196 * eV, 4.16107 * eV,
       4.20339 * eV, 4.24658 * eV, 4.29066 * eV, 4.33566 * eV, 4.38163 * eV, 4.42857 * eV, 4.47653 * eV, 4.52555 * eV, 4.62687 * eV,
       4.67925 * eV, 4.78764 * eV, 4.96 * eV, 5.62461 * eV};

  std::vector<G4double> Absorption =
      {955.954000 * mm, 668.943000 * mm, 614.032000 * mm, 467.353000 * mm, 559.162000 * mm, 579.555000 * mm, 650.626000 * mm, 535.162000 * mm, 524.755000 * mm,
       540.255000 * mm, 600.531000 * mm, 519.526000 * mm, 526.569000 * mm, 516.447000 * mm, 502.306000 * mm, 518.467000 * mm, 522.762000 * mm, 503.951000 * mm,
       537.711000 * mm, 520.839000 * mm, 553.001000 * mm, 488.909000 * mm, 521.548000 * mm, 471.766000 * mm, 450.077000 * mm, 404.852000 * mm, 441.221000 * mm,
       440.960000 * mm, 411.248000 * mm, 380.195000 * mm, 399.852000 * mm, 380.692000 * mm, 372.110000 * mm, 362.841000 * mm, 370.628000 * mm, 355.130000 * mm,
       371.095000 * mm, 389.190000 * mm, 390.557000 * mm, 376.662000 * mm, 394.540000 * mm, 419.485000 * mm, 423.900000 * mm, 424.207000 * mm, 459.364000 * mm,
       432.117000 * mm, 450.723000 * mm, 444.802000 * mm, 451.629000 * mm, 415.643000 * mm, 458.704000 * mm, 473.048000 * mm, 388.097000 * mm, 445.714000 * mm,
       356.658000 * mm, 362.018000 * mm, 323.960000 * mm, 249.410000 * mm, 222.770000 * mm, 173.466000 * mm, 126.428000 * mm, 94.944500 * mm, 64.388500 * mm,
       45.198300 * mm, 30.697900 * mm, 20.705400 * mm, 14.095600 * mm, 9.563980 * mm, 6.555540 * mm, 4.590660 * mm, 3.251770 * mm, 2.439640 * mm, 1.899230 * mm,
       1.561530 * mm, 1.644290 * mm, 1.454600 * mm, 1.344050 * mm, 1.392430 * mm, 1.474630 * mm, 1.365870 * mm, 1.418190 * mm, 1.449410 * mm, 1.429420 * mm, 1.588940 * mm,
       1.456210 * mm, 1.313570 * mm, 1.626080 * mm, 1.611680 * mm, 1.429990 * mm, 1.472460 * mm, 1.501370 * mm, 1.565330 * mm, 1.556520 * mm, 1.413260 * mm, 1.651750 * mm,
       1.532130 * mm, 1.908330 * mm, 2.906480 * mm, 4.388340 * mm, 6.664950 * mm, 9.720680 * mm, 12.470900 * mm, 13.226400 * mm, 11.510300 * mm, 8.747250 * mm, 6.425540 * mm,
       4.638230 * mm, 3.356940 * mm, 2.389330 * mm, 1.730910 * mm, 1.621300 * mm, 1.349290 * mm, 1.371340 * mm, 1.454750 * mm, 1.353480 * mm, 1.092090 * mm, 1.486040 * mm,
       1.375890 * mm, 1.153950 * mm, 1.623740 * mm, 1.443300 * mm, 1.605000 * mm, 1.705960 * mm, 1.510680 * mm, 1.525980 * mm, 1.586010 * mm, 1.616290 * mm, 1.489230 * mm,
       1.483450 * mm, 1.411050 * mm, 1.685210 * mm, 1.409220 * mm, 1.232600 * mm, 1.707510 * mm, 1.382160 * mm, 1.322320 * mm, 1.441060 * mm, 1.478580 * mm, 0 * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  //      Taken straight outta the spectrophotometer.
  //      Hope this doesn't kill the performance.      O.o'

  std::vector<G4double> PhotonEnergy_FAST = {1.425287 * eV, 1.426107 * eV, 1.426928 * eV, 1.427749 * eV, 1.428571 * eV, 1.429395 * eV, 1.430219 * eV, 1.431044 * eV, 1.431871 * eV, 1.432698 * eV, 1.433526 * eV, 1.434355 * eV,
                                             1.435185 * eV, 1.436016 * eV, 1.436848 * eV, 1.437681 * eV, 1.438515 * eV, 1.439350 * eV, 1.440186 * eV, 1.441023 * eV, 1.441860 * eV, 1.442699 * eV, 1.443539 * eV, 1.444380 * eV, 1.445221 * eV, 1.446064 * eV, 1.446908 * eV, 1.447752 * eV,
                                             1.448598 * eV, 1.449445 * eV, 1.450292 * eV, 1.451141 * eV, 1.451991 * eV, 1.452841 * eV, 1.453693 * eV, 1.454545 * eV, 1.455399 * eV, 1.456254 * eV, 1.457109 * eV, 1.457966 * eV, 1.458824 * eV, 1.459682 * eV, 1.460542 * eV, 1.461402 * eV,
                                             1.462264 * eV, 1.463127 * eV, 1.463991 * eV, 1.464855 * eV, 1.465721 * eV, 1.466588 * eV, 1.467456 * eV, 1.468324 * eV, 1.469194 * eV, 1.470065 * eV, 1.470937 * eV, 1.471810 * eV, 1.472684 * eV, 1.473559 * eV, 1.474435 * eV, 1.475312 * eV,
                                             1.476190 * eV, 1.477070 * eV, 1.477950 * eV, 1.478831 * eV, 1.479714 * eV, 1.480597 * eV, 1.481481 * eV, 1.482367 * eV, 1.483254 * eV, 1.484141 * eV, 1.485030 * eV, 1.485920 * eV, 1.486811 * eV, 1.487702 * eV, 1.488595 * eV, 1.489489 * eV,
                                             1.490385 * eV, 1.491281 * eV, 1.492178 * eV, 1.493076 * eV, 1.493976 * eV, 1.494876 * eV, 1.495778 * eV, 1.496681 * eV, 1.497585 * eV, 1.498489 * eV, 1.499395 * eV, 1.500302 * eV, 1.501211 * eV, 1.502120 * eV, 1.503030 * eV, 1.503942 * eV,
                                             1.504854 * eV, 1.505768 * eV, 1.506683 * eV, 1.507599 * eV, 1.508516 * eV, 1.509434 * eV, 1.510353 * eV, 1.511274 * eV, 1.512195 * eV, 1.513118 * eV, 1.514042 * eV, 1.514966 * eV, 1.515892 * eV, 1.516820 * eV, 1.517748 * eV, 1.518677 * eV,
                                             1.519608 * eV, 1.520540 * eV, 1.521472 * eV, 1.522406 * eV, 1.523342 * eV, 1.524278 * eV, 1.525215 * eV, 1.526154 * eV, 1.527094 * eV, 1.528035 * eV, 1.528977 * eV, 1.529920 * eV, 1.530864 * eV, 1.531810 * eV, 1.532756 * eV, 1.533704 * eV,
                                             1.534653 * eV, 1.535604 * eV, 1.536555 * eV, 1.537508 * eV, 1.538462 * eV, 1.539417 * eV, 1.540373 * eV, 1.541330 * eV, 1.542289 * eV, 1.543248 * eV, 1.544209 * eV, 1.545171 * eV, 1.546135 * eV, 1.547099 * eV, 1.548065 * eV, 1.549032 * eV,
                                             1.550000 * eV, 1.550969 * eV, 1.551940 * eV, 1.552912 * eV, 1.553885 * eV, 1.554859 * eV, 1.555834 * eV, 1.556811 * eV, 1.557789 * eV, 1.558768 * eV, 1.559748 * eV, 1.560730 * eV, 1.561713 * eV, 1.562697 * eV, 1.563682 * eV, 1.564669 * eV,
                                             1.565657 * eV, 1.566646 * eV, 1.567636 * eV, 1.568627 * eV, 1.569620 * eV, 1.570614 * eV, 1.571610 * eV, 1.572606 * eV, 1.573604 * eV, 1.574603 * eV, 1.575604 * eV, 1.576605 * eV, 1.577608 * eV, 1.578612 * eV, 1.579618 * eV, 1.580625 * eV, 1.581633 * eV, 1.582642 * eV, 1.583653 * eV, 1.584665 * eV, 1.585678 * eV, 1.586692 * eV, 1.587708 * eV,
                                             1.588725 * eV, 1.589744 * eV, 1.590763 * eV, 1.591784 * eV, 1.592807 * eV, 1.593830 * eV, 1.594855 * eV, 1.595882 * eV, 1.596909 * eV, 1.597938 * eV, 1.598968 * eV, 1.600000 * eV, 1.601033 * eV, 1.602067 * eV, 1.603103 * eV, 1.604140 * eV, 1.605178 * eV, 1.606218 * eV, 1.607259 * eV, 1.608301 * eV, 1.609345 * eV, 1.610390 * eV, 1.611436 * eV,
                                             1.612484 * eV, 1.613533 * eV, 1.614583 * eV, 1.615635 * eV, 1.616688 * eV, 1.617743 * eV, 1.618799 * eV, 1.619856 * eV, 1.620915 * eV, 1.621975 * eV, 1.623037 * eV, 1.624100 * eV, 1.625164 * eV, 1.626230 * eV, 1.627297 * eV, 1.628365 * eV, 1.629435 * eV, 1.630506 * eV, 1.631579 * eV, 1.632653 * eV, 1.633729 * eV, 1.634806 * eV, 1.635884 * eV,
                                             1.636964 * eV, 1.638045 * eV, 1.639128 * eV, 1.640212 * eV, 1.641297 * eV, 1.642384 * eV, 1.643472 * eV, 1.644562 * eV, 1.645654 * eV, 1.646746 * eV, 1.647841 * eV, 1.648936 * eV, 1.650033 * eV, 1.651132 * eV, 1.652232 * eV, 1.653333 * eV, 1.654436 * eV, 1.655541 * eV, 1.656647 * eV, 1.657754 * eV, 1.658863 * eV, 1.659973 * eV, 1.661085 * eV,
                                             1.662198 * eV, 1.663313 * eV, 1.664430 * eV, 1.665547 * eV, 1.666667 * eV, 1.667787 * eV, 1.668910 * eV, 1.670034 * eV, 1.671159 * eV, 1.672286 * eV, 1.673414 * eV, 1.674544 * eV, 1.675676 * eV, 1.676809 * eV, 1.677943 * eV, 1.679079 * eV, 1.680217 * eV, 1.681356 * eV, 1.682497 * eV, 1.683639 * eV, 1.684783 * eV, 1.685928 * eV, 1.687075 * eV,
                                             1.688223 * eV, 1.689373 * eV, 1.690525 * eV, 1.691678 * eV, 1.692833 * eV, 1.693989 * eV, 1.695147 * eV, 1.696306 * eV, 1.697467 * eV, 1.698630 * eV, 1.699794 * eV, 1.700960 * eV, 1.702128 * eV, 1.703297 * eV, 1.704467 * eV, 1.705640 * eV, 1.706813 * eV, 1.707989 * eV, 1.709166 * eV, 1.710345 * eV, 1.711525 * eV, 1.712707 * eV, 1.713891 * eV,
                                             1.715076 * eV, 1.716263 * eV, 1.717452 * eV, 1.718642 * eV, 1.719834 * eV, 1.721027 * eV, 1.722222 * eV, 1.723419 * eV, 1.724618 * eV, 1.725818 * eV, 1.727019 * eV, 1.728223 * eV, 1.729428 * eV, 1.730635 * eV, 1.731844 * eV, 1.733054 * eV, 1.734266 * eV, 1.735479 * eV, 1.736695 * eV, 1.737912 * eV, 1.739130 * eV, 1.740351 * eV, 1.741573 * eV,
                                             1.742797 * eV, 1.744023 * eV, 1.745250 * eV, 1.746479 * eV, 1.747710 * eV, 1.748942 * eV, 1.750176 * eV, 1.751412 * eV, 1.752650 * eV, 1.753890 * eV, 1.755131 * eV, 1.756374 * eV, 1.757619 * eV, 1.758865 * eV, 1.760114 * eV, 1.761364 * eV, 1.762615 * eV, 1.763869 * eV, 1.765125 * eV, 1.766382 * eV, 1.767641 * eV, 1.768902 * eV, 1.770164 * eV,
                                             1.771429 * eV, 1.772695 * eV, 1.773963 * eV, 1.775233 * eV, 1.776504 * eV, 1.777778 * eV, 1.779053 * eV, 1.780330 * eV, 1.781609 * eV, 1.782890 * eV, 1.784173 * eV, 1.785457 * eV, 1.786744 * eV, 1.788032 * eV, 1.789322 * eV, 1.790614 * eV, 1.791908 * eV, 1.793203 * eV, 1.794501 * eV,
                                             1.795800 * eV, 1.797101 * eV, 1.798405 * eV, 1.799710 * eV, 1.801017 * eV, 1.802326 * eV, 1.803636 * eV, 1.804949 * eV, 1.806264 * eV, 1.807580 * eV, 1.808899 * eV, 1.810219 * eV, 1.811541 * eV, 1.812865 * eV, 1.814192 * eV, 1.815520 * eV, 1.816850 * eV, 1.818182 * eV, 1.819516 * eV, 1.820852 * eV, 1.822190 * eV, 1.823529 * eV, 1.824871 * eV,
                                             1.826215 * eV, 1.827561 * eV, 1.828909 * eV, 1.830258 * eV, 1.831610 * eV, 1.832964 * eV, 1.834320 * eV, 1.835677 * eV, 1.837037 * eV, 1.838399 * eV, 1.839763 * eV, 1.841128 * eV, 1.842496 * eV, 1.843866 * eV, 1.845238 * eV, 1.846612 * eV, 1.847988 * eV, 1.849366 * eV, 1.850746 * eV, 1.852128 * eV, 1.853513 * eV, 1.854899 * eV, 1.856287 * eV,
                                             1.857678 * eV, 1.859070 * eV, 1.860465 * eV, 1.861862 * eV, 1.863261 * eV, 1.864662 * eV, 1.866065 * eV, 1.867470 * eV, 1.868877 * eV, 1.870287 * eV, 1.871698 * eV, 1.873112 * eV, 1.874528 * eV, 1.875946 * eV, 1.877366 * eV, 1.878788 * eV, 1.880212 * eV, 1.881639 * eV, 1.883068 * eV, 1.884498 * eV, 1.885932 * eV, 1.887367 * eV, 1.888804 * eV,
                                             1.890244 * eV, 1.891686 * eV, 1.893130 * eV, 1.894576 * eV, 1.896024 * eV, 1.897475 * eV, 1.898928 * eV, 1.900383 * eV, 1.901840 * eV, 1.903300 * eV, 1.904762 * eV, 1.906226 * eV, 1.907692 * eV, 1.909161 * eV, 1.910632 * eV, 1.912105 * eV, 1.913580 * eV, 1.915058 * eV, 1.916538 * eV, 1.918020 * eV, 1.919505 * eV, 1.920991 * eV, 1.922481 * eV,
                                             1.923972 * eV, 1.925466 * eV, 1.926962 * eV, 1.928460 * eV, 1.929961 * eV, 1.931464 * eV, 1.932970 * eV, 1.934477 * eV, 1.935988 * eV, 1.937500 * eV, 1.939015 * eV, 1.940532 * eV, 1.942052 * eV, 1.943574 * eV, 1.945098 * eV, 1.946625 * eV, 1.948154 * eV, 1.949686 * eV, 1.951220 * eV, 1.952756 * eV, 1.954295 * eV, 1.955836 * eV, 1.957380 * eV,
                                             1.958926 * eV, 1.960474 * eV, 1.962025 * eV, 1.963579 * eV, 1.965135 * eV, 1.966693 * eV, 1.968254 * eV, 1.969817 * eV, 1.971383 * eV, 1.972951 * eV, 1.974522 * eV, 1.976096 * eV, 1.977671 * eV, 1.979250 * eV, 1.980831 * eV, 1.982414 * eV, 1.984000 * eV, 1.985588 * eV, 1.987179 * eV, 1.988773 * eV, 1.990369 * eV, 1.991968 * eV, 1.993569 * eV,
                                             1.995173 * eV, 1.996779 * eV, 1.998388 * eV, 2.000000 * eV, 2.001614 * eV, 2.003231 * eV, 2.004850 * eV, 2.006472 * eV, 2.008097 * eV, 2.009724 * eV, 2.011354 * eV, 2.012987 * eV, 2.014622 * eV, 2.016260 * eV, 2.017901 * eV, 2.019544 * eV, 2.021190 * eV, 2.022838 * eV, 2.024490 * eV, 2.026144 * eV, 2.027800 * eV, 2.029460 * eV, 2.031122 * eV,
                                             2.032787 * eV, 2.034454 * eV, 2.036125 * eV, 2.037798 * eV, 2.039474 * eV, 2.041152 * eV, 2.042834 * eV, 2.044518 * eV, 2.046205 * eV, 2.047894 * eV, 2.049587 * eV, 2.051282 * eV, 2.052980 * eV, 2.054681 * eV, 2.056385 * eV, 2.058091 * eV, 2.059801 * eV, 2.061513 * eV, 2.063228 * eV, 2.064946 * eV, 2.066667 * eV, 2.068390 * eV, 2.070117 * eV,
                                             2.071846 * eV, 2.073579 * eV, 2.075314 * eV, 2.077052 * eV, 2.078793 * eV, 2.080537 * eV, 2.082284 * eV, 2.084034 * eV, 2.085786 * eV, 2.087542 * eV, 2.089301 * eV, 2.091062 * eV, 2.092827 * eV, 2.094595 * eV, 2.096365 * eV, 2.098139 * eV, 2.099915 * eV, 2.101695 * eV, 2.103478 * eV,
                                             2.105263 * eV, 2.107052 * eV, 2.108844 * eV, 2.110638 * eV, 2.112436 * eV, 2.114237 * eV, 2.116041 * eV, 2.117848 * eV, 2.119658 * eV, 2.121471 * eV, 2.123288 * eV, 2.125107 * eV, 2.126930 * eV, 2.128755 * eV, 2.130584 * eV, 2.132416 * eV, 2.134251 * eV, 2.136090 * eV, 2.137931 * eV, 2.139776 * eV, 2.141623 * eV, 2.143475 * eV, 2.145329 * eV,
                                             2.147186 * eV, 2.149047 * eV, 2.150911 * eV, 2.152778 * eV, 2.154648 * eV, 2.156522 * eV, 2.158399 * eV, 2.160279 * eV, 2.162162 * eV, 2.164049 * eV, 2.165939 * eV, 2.167832 * eV, 2.169729 * eV, 2.171629 * eV, 2.173532 * eV, 2.175439 * eV, 2.177349 * eV, 2.179262 * eV, 2.181179 * eV, 2.183099 * eV, 2.185022 * eV, 2.186949 * eV, 2.188879 * eV,
                                             2.190813 * eV, 2.192750 * eV, 2.194690 * eV, 2.196634 * eV, 2.198582 * eV, 2.200532 * eV, 2.202487 * eV, 2.204444 * eV, 2.206406 * eV, 2.208370 * eV, 2.210339 * eV, 2.212310 * eV, 2.214286 * eV, 2.216265 * eV, 2.218247 * eV, 2.220233 * eV, 2.222222 * eV, 2.224215 * eV, 2.226212 * eV, 2.228212 * eV, 2.230216 * eV, 2.232223 * eV, 2.234234 * eV,
                                             2.236249 * eV, 2.238267 * eV, 2.240289 * eV, 2.242315 * eV, 2.244344 * eV, 2.246377 * eV, 2.248413 * eV, 2.250454 * eV, 2.252498 * eV, 2.254545 * eV, 2.256597 * eV, 2.258652 * eV, 2.260711 * eV, 2.262774 * eV, 2.264840 * eV, 2.266910 * eV, 2.268984 * eV, 2.271062 * eV, 2.273144 * eV, 2.275229 * eV, 2.277319 * eV, 2.279412 * eV, 2.281509 * eV,
                                             2.283610 * eV, 2.285714 * eV, 2.287823 * eV, 2.289935 * eV, 2.292052 * eV, 2.294172 * eV, 2.296296 * eV, 2.298424 * eV, 2.300557 * eV, 2.302693 * eV, 2.304833 * eV, 2.306977 * eV, 2.309125 * eV, 2.311277 * eV, 2.313433 * eV, 2.315593 * eV, 2.317757 * eV, 2.319925 * eV, 2.322097 * eV, 2.324274 * eV, 2.326454 * eV, 2.328638 * eV, 2.330827 * eV,
                                             2.333020 * eV, 2.335217 * eV, 2.337418 * eV, 2.339623 * eV, 2.341832 * eV, 2.344045 * eV, 2.346263 * eV, 2.348485 * eV, 2.350711 * eV, 2.352941 * eV, 2.355176 * eV, 2.357414 * eV, 2.359657 * eV, 2.361905 * eV, 2.364156 * eV, 2.366412 * eV, 2.368672 * eV, 2.370937 * eV, 2.373206 * eV, 2.375479 * eV, 2.377756 * eV, 2.380038 * eV, 2.382325 * eV,
                                             2.384615 * eV, 2.386910 * eV, 2.389210 * eV, 2.391514 * eV, 2.393822 * eV, 2.396135 * eV, 2.398453 * eV, 2.400774 * eV, 2.403101 * eV, 2.405432 * eV, 2.407767 * eV, 2.410107 * eV, 2.412451 * eV, 2.414800 * eV, 2.417154 * eV, 2.419512 * eV, 2.421875 * eV, 2.424242 * eV, 2.426614 * eV, 2.428991 * eV, 2.431373 * eV, 2.433759 * eV, 2.436149 * eV,
                                             2.438545 * eV, 2.440945 * eV, 2.443350 * eV, 2.445759 * eV, 2.448174 * eV, 2.450593 * eV, 2.453017 * eV, 2.455446 * eV, 2.457879 * eV, 2.460317 * eV, 2.462761 * eV, 2.465209 * eV, 2.467662 * eV, 2.470120 * eV, 2.472582 * eV, 2.475050 * eV, 2.477522 * eV, 2.480000 * eV, 2.482482 * eV, 2.484970 * eV, 2.487462 * eV, 2.489960 * eV, 2.492462 * eV,
                                             2.494970 * eV, 2.497482 * eV, 2.500000 * eV, 2.502523 * eV, 2.505051 * eV, 2.507583 * eV, 2.510121 * eV, 2.512665 * eV, 2.515213 * eV, 2.517766 * eV, 2.520325 * eV, 2.522889 * eV, 2.525458 * eV, 2.528033 * eV, 2.530612 * eV, 2.533197 * eV, 2.535787 * eV, 2.538383 * eV, 2.540984 * eV,
                                             2.543590 * eV, 2.546201 * eV, 2.548818 * eV, 2.551440 * eV, 2.554068 * eV, 2.556701 * eV, 2.559340 * eV, 2.561983 * eV, 2.564633 * eV, 2.567288 * eV, 2.569948 * eV, 2.572614 * eV, 2.575286 * eV, 2.577963 * eV, 2.580645 * eV, 2.583333 * eV, 2.586027 * eV, 2.588727 * eV, 2.591432 * eV, 2.594142 * eV, 2.596859 * eV, 2.599581 * eV, 2.602308 * eV};

  std::vector<G4double> FastComponent =
      {
          0.160333, 0.172055, 0.180528, 0.185841, 0.188323, 0.188954, 0.186772, 0.182738, 0.178573, 0.175773, 0.174867, 0.173955, 0.172557, 0.171364, 0.170930, 0.170360, 0.168857, 0.167288, 0.165351, 0.163923, 0.162677, 0.161678, 0.161048, 0.160843, 0.160919, 0.160517, 0.160686, 0.160464,
          0.159976, 0.159308, 0.158286, 0.157136, 0.155732, 0.154752, 0.154047, 0.153539, 0.153576, 0.154763, 0.156705, 0.158406, 0.159616, 0.159562, 0.158966, 0.157962, 0.155876, 0.153398, 0.152418, 0.152958, 0.154043, 0.155506, 0.156696, 0.158246, 0.159557, 0.160035, 0.159984, 0.160655,
          0.161680, 0.162683, 0.163751, 0.164225, 0.164384, 0.163716, 0.162927, 0.161685, 0.161064, 0.161583, 0.163290, 0.166036, 0.169015, 0.172248, 0.174792, 0.177343, 0.178371, 0.179139, 0.179470, 0.179794, 0.180614, 0.181098, 0.181929, 0.182751, 0.184452, 0.184796, 0.185040, 0.185164,
          0.185262, 0.185692, 0.185288, 0.185155, 0.185544, 0.186761, 0.186675, 0.186026, 0.185206, 0.184357, 0.184081, 0.182930, 0.180970, 0.179324, 0.178990, 0.178807, 0.178816, 0.179548, 0.180189, 0.181705, 0.183860, 0.185555, 0.186864, 0.187659, 0.186991, 0.185885, 0.184938, 0.182451,
          0.179253, 0.176828, 0.175065, 0.174352, 0.174345, 0.174170, 0.174635, 0.176360, 0.177780, 0.178376, 0.179079, 0.179967, 0.180717, 0.181527, 0.182005, 0.182501, 0.182777, 0.182598, 0.181987, 0.181748, 0.181893, 0.182113, 0.182613, 0.182965, 0.183928, 0.184883, 0.185172, 0.185290,
          0.185926, 0.187299, 0.189183, 0.192071, 0.194687, 0.197445, 0.200288, 0.202261, 0.203751, 0.204776, 0.205879, 0.207200, 0.209689, 0.212624, 0.215543, 0.218708, 0.221917, 0.225334, 0.228164, 0.231296, 0.234249, 0.238200, 0.242831, 0.246744, 0.249958, 0.252404, 0.254520, 0.255287,
          0.255467, 0.255138, 0.255251, 0.256250, 0.257098, 0.258633, 0.260698, 0.263629, 0.266652, 0.269514, 0.271993, 0.274103, 0.275915, 0.276758, 0.277352, 0.277538, 0.277770, 0.278430, 0.279565, 0.280986, 0.282494, 0.284023, 0.284981, 0.285279, 0.285089, 0.284264, 0.283283, 0.282408,
          0.281352, 0.280817, 0.280748, 0.280999, 0.281389, 0.282203, 0.283156, 0.284094, 0.284769, 0.284727, 0.285041, 0.285578, 0.286377, 0.286919, 0.287022, 0.287172, 0.287323, 0.286838, 0.286101, 0.285711, 0.285562, 0.286258, 0.287810, 0.289147, 0.290564, 0.291878, 0.292197, 0.291950,
          0.291027, 0.289650, 0.288632, 0.288382, 0.288782, 0.289809, 0.290986, 0.292057, 0.293552, 0.294994, 0.296213, 0.297359, 0.298379, 0.299725, 0.301065, 0.301758,
          0.302152, 0.302418, 0.302455, 0.302965, 0.303988, 0.305269, 0.307792, 0.311004, 0.314233, 0.317157, 0.319612, 0.321208, 0.322833, 0.323933, 0.324668, 0.325648, 0.326384, 0.327127, 0.327983, 0.329782, 0.331478, 0.334153, 0.337734, 0.342331, 0.347829, 0.353863, 0.359909, 0.365554,
          0.371182, 0.375309, 0.378078, 0.380650, 0.383559, 0.386661, 0.391209, 0.396554, 0.403391, 0.412262, 0.421569, 0.430263, 0.438646, 0.446296, 0.452533, 0.459093, 0.464611, 0.470111, 0.475587, 0.480986, 0.486321, 0.492086, 0.497950, 0.503656, 0.510915, 0.518411, 0.525585, 0.531775,
          0.537243, 0.541844, 0.545787, 0.548832, 0.551114, 0.554734, 0.560204, 0.566683, 0.574083, 0.582899, 0.591700, 0.599719, 0.606075, 0.610675, 0.613892, 0.616678, 0.619201, 0.621949, 0.626338, 0.631770, 0.637622, 0.643314, 0.648892, 0.654411, 0.659824, 0.665181, 0.670375, 0.676088,
          0.683226, 0.690607, 0.698531, 0.708160, 0.718258, 0.728716, 0.739570, 0.751581, 0.763034, 0.775454, 0.786540, 0.797086, 0.808549, 0.820140, 0.831665, 0.843176, 0.856263, 0.868398, 0.881225, 0.892920, 0.904357, 0.915893, 0.928096, 0.939263, 0.948868, 0.959247, 0.969073, 0.979514,
          0.991217, 1.006180, 1.022176, 1.040957, 1.060646, 1.080315, 1.099629, 1.117168, 1.132367, 1.143713, 1.154007, 1.162971, 1.172804, 1.183047, 1.193364, 1.204806, 1.218254, 1.233768, 1.249340, 1.264735, 1.280843, 1.298822, 1.316305, 1.333060, 1.349401, 1.365012, 1.381080, 1.398043,
          1.414998, 1.433156, 1.453538, 1.475149, 1.497840, 1.522714, 1.549153, 1.575589, 1.602703, 1.629766, 1.657771, 1.686157, 1.713829, 1.740740, 1.768848, 1.797099, 1.826433, 1.856914, 1.887414, 1.920113, 1.952943, 1.984931, 2.016673, 2.048364, 2.080761, 2.114546, 2.150983, 2.187603,
          2.227391, 2.267608, 2.308318, 2.349979, 2.391574, 2.432560, 2.473686, 2.517020, 2.560338, 2.606682, 2.652806, 2.697589, 2.740990, 2.782212, 2.822549, 2.863372, 2.906545, 2.951182, 2.999788, 3.049974, 3.101279, 3.150571, 3.197309, 3.241397, 3.282194, 3.319780, 3.355298, 3.394046,
          3.434711, 3.481092, 3.529849, 3.581205, 3.636162, 3.692668, 3.749120, 3.806017, 3.865440, 3.920449, 3.976139, 4.028575, 4.079399, 4.129317, 4.178763, 4.227938, 4.276508, 4.328505, 4.377710, 4.431798, 4.485211, 4.542401, 4.602420, 4.665596, 4.733517, 4.805294, 4.881597, 4.955312,
          5.031172, 5.103682, 5.172749, 5.236611, 5.298137, 5.359899, 5.419967, 5.482172, 5.543176, 5.605148, 5.670492, 5.740138, 5.814321, 5.895414, 5.981730, 6.071641, 6.164834, 6.256723, 6.343300, 6.426013, 6.507092, 6.584824, 6.664619, 6.745062, 6.824841, 6.905505, 6.987358, 7.068448,
          7.145806, 7.223107, 7.299318, 7.382849, 7.469975, 7.558261, 7.648318, 7.739405, 7.832896, 7.927704, 8.024399, 8.117990, 8.213648, 8.309669, 8.403208, 8.491036, 8.573814, 8.653141, 8.732364, 8.812956, 8.896425, 8.982942, 9.074628, 9.172558, 9.271829, 9.373102, 9.471807, 9.568671, 9.664489, 9.764401, 9.862431, 9.961527,
          10.062514, 10.162395, 10.267956, 10.377316, 10.486914, 10.593941, 10.704643, 10.812764, 10.922728, 11.031806, 11.136382, 11.240701, 11.348914, 11.457710, 11.560809, 11.666111, 11.769687, 11.873744, 11.982856, 12.091494, 12.195096, 12.306485, 12.424388, 12.538396, 12.649503,
          12.755230, 12.852457, 12.955026, 13.057408, 13.151514, 13.249479, 13.360196, 13.475367, 13.590405, 13.703543, 13.809648, 13.920157, 14.030500, 14.136132, 14.234845, 14.337392, 14.440752, 14.542470, 14.643342, 14.742330, 14.837359, 14.933357, 15.030482, 15.121741, 15.217645,
          15.311870, 15.403404, 15.499368, 15.605598, 15.711020, 15.818623, 15.928037, 16.034052, 16.143130, 16.247351, 16.339258, 16.425389, 16.516449, 16.606260, 16.696443, 16.790204, 16.882196, 16.980250, 17.080543, 17.177801, 17.265764, 17.349557, 17.429280, 17.505393, 17.582362,
          17.656297, 17.732708, 17.816212, 17.908350, 18.003255, 18.095199, 18.181472, 18.269397, 18.354728, 18.434323, 18.510606, 18.596313, 18.693102, 18.802602, 18.911997, 19.015629, 19.124369, 19.229364, 19.323701, 19.402913, 19.483465, 19.560596, 19.641053, 19.718309, 19.792413,
          19.869586, 19.949725, 20.026719, 20.095968, 20.171002, 20.255738, 20.345770, 20.434825, 20.524169, 20.604079, 20.677508, 20.741404, 20.794106, 20.843678, 20.898596, 20.953907, 21.011152, 21.081034, 21.153868, 21.230743, 21.305027, 21.372700, 21.432274, 21.489282, 21.538526,
          21.580936, 21.626996, 21.670602, 21.712001, 21.748164, 21.781695, 21.812616, 21.837206, 21.857631, 21.878914, 21.906131, 21.934830, 21.957913, 21.976860, 21.991334, 22.003585, 22.005043, 21.998509, 21.990289, 21.987864, 21.988827, 21.987035, 21.980584, 21.963873, 21.947645,
          21.926436, 21.896811, 21.859359, 21.814038, 21.758221,
          21.698002, 21.635145, 21.566074, 21.493923, 21.423607, 21.353887, 21.278387, 21.189528, 21.081072, 20.957433, 20.818778, 20.670547, 20.513037, 20.350933, 20.191659, 20.036380, 19.873308, 19.701685, 19.519604, 19.329683, 19.135690, 18.936732, 18.729052, 18.519217, 18.310576,
          18.094135, 17.867046, 17.627899, 17.378721, 17.118091, 16.853280, 16.576317, 16.292254, 16.011360, 15.733297, 15.457866, 15.182900, 14.905330, 14.621737, 14.337595, 14.046097, 13.746192, 13.443646, 13.141727, 12.844686, 12.550631, 12.257647, 11.962531, 11.666829, 11.369029,
          11.064639, 10.758183, 10.449219, 10.146628,
          9.845579, 9.550573, 9.256683, 8.963058, 8.669924, 8.372660, 8.075375, 7.777387, 7.485712, 7.198002, 6.920792, 6.650151, 6.388837, 6.131463, 5.875763, 5.623275, 5.370905, 5.120390, 4.872820, 4.632578, 4.396777, 4.168619, 3.945906, 3.727595, 3.515392, 3.310932, 3.113700, 2.926979,
          2.751590, 2.588683, 2.439079, 2.300711, 2.169602, 2.044509, 1.925282, 1.810431, 1.701355, 1.600311, 1.508377, 1.428058, 1.361947, 1.306719, 1.260604, 1.221590, 1.187067, 1.155297, 1.125212, 1.094388, 1.064629, 1.039276, 1.018386, 1.002130, 0.991032, 0.985420, 0.984140};

  //** scintillation and optical properties **//
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 4.8);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 42. * ns);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 156. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 0.65); // Ratio between fast component and total light yield. Ignore the documentation.
  mt->AddConstProperty("SCINTILLATIONYIELD2", 0.35); // Ratio between fast component and total light yield. Ignore the documentation.

  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::GAGG_slow(double user_lightyield, double scaleFactor, double user_birks) // Gadolinium Gallium Aluminum Garnet
{
  // ########################################################
  // ### GAGG:Ce:Mg in a more complete fashion.
  // ### - Index of refraction taken from:
  // ###         Kozlova NS, Buzanov OA, Kasimova VM, Kozlova AP, Zabelina EV (2018) Optical characteristics of single crystal Gd3Al2Ga3O12 : Ce. Modern Electronic Materials 4(1): 7–12. https://doi.org/10.3897/j.moem.4.1.33240
  // ### - Emission measured in Lab 27, CERN.                                                                         L. Martinazzoli                   (2020)
  // ### - Absorption calculated measuring transmission of different ILM GAGG:Ce (not codoped!) in Lab 27, CERN.      N. Kratochwil, L. Martinazzoli    (2019)
  // ########

  double standard_light_yield = 40000.0;
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *Ga = new G4Element("Gallium", "Ga", z = 31., a = 69.723 * g / mole);
  G4Element *Gd = new G4Element("Gadolinio", "Gd", z = 64., a = 157.25 * g / mole);
  G4Element *Al = new G4Element("Aluminum", "Al", z = 13., a = 26.98 * g / mole);

  G4Material *mat = new G4Material("GAGG_slow", density = 6.63 * g / cm3, 4);
  mat->AddElement(Ga, 3);
  mat->AddElement(Gd, 3);
  mat->AddElement(Al, 2);
  mat->AddElement(O, 12);

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);
  //--------//

  // --- Refractive Index
  //      The first point (1.23984 eV) is added artificially to extend the RI above 700 nm.
  std::vector<G4double> PhotonEnergy_RI = {1.23984 * eV,
                                           1.72271 * eV, 1.74623 * eV, 1.77132 * eV, 1.79807 * eV, 1.82468 * eV, 1.85209 * eV, 1.87931 * eV, 1.90734 * eV, 1.93840 * eV, 1.96824 * eV, 2.00017 * eV, 2.03315 * eV, 2.06599 * eV,
                                           2.10633 * eV, 2.13762 * eV, 2.17670 * eV, 2.21440 * eV, 2.25637 * eV, 2.29690 * eV, 2.34050 * eV, 2.38578 * eV, 2.42943 * eV, 2.53093 * eV, 2.58203 * eV, 2.63926 * eV, 2.69489 * eV,
                                           2.75950 * eV, 2.88396 * eV, 2.95302 * eV, 3.02545 * eV, 3.09601 * eV, 3.18161 * eV, 3.26590 * eV, 3.35473 * eV, 3.44161 * eV, 3.54034 * eV, 3.64512 * eV, 3.75608 * eV, 3.87418 * eV,
                                           3.99973 * eV, 4.13371 * eV, 4.27696 * eV, 4.43064 * eV, 4.59557 * eV, 4.76007 * eV, 4.95065 * eV, 5.15688 * eV, 5.38078 * eV, 5.62461 * eV};

  std::vector<G4double> RefractiveIndex = {1.8646638,
                                           1.87226, 1.87263, 1.87336, 1.87409, 1.87409, 1.87555, 1.87628, 1.87737, 1.87774, 1.87883, 1.87993, 1.88102, 1.88285, 1.88467,
                                           1.88613, 1.88832, 1.88942, 1.89015, 1.89234, 1.89307, 1.89453, 1.89599, 1.90073, 1.90401, 1.90547, 1.90693, 1.90839, 1.91277,
                                           1.91569, 1.92080, 1.91861, 1.91934, 1.91788, 1.92226, 1.93175, 1.94197, 1.93102, 1.93978, 1.93248, 1.94489, 1.95438, 1.96606,
                                           1.96752, 1.98212, 1.99818, 2.03102, 2.07628, 2.13394, 2.20912};

  // --- Intrinsic absorption spectrum
  //    Highest and Lowest energies are arbitrarily set.

  std::vector<G4double> PhotonEnergy_ABS =
      {1.49849 * eV, 1.50943 * eV, 1.52054 * eV, 1.53181 * eV, 1.54325 * eV, 1.55486 * eV, 1.56665 * eV, 1.57861 * eV, 1.59076 * eV,
       1.6031 * eV, 1.61564 * eV, 1.62837 * eV, 1.6413 * eV, 1.65444 * eV, 1.66779 * eV, 1.68136 * eV, 1.69515 * eV, 1.70917 * eV,
       1.72342 * eV, 1.73791 * eV, 1.75265 * eV, 1.76764 * eV, 1.78289 * eV, 1.7984 * eV, 1.81419 * eV, 1.83026 * eV, 1.84661 * eV,
       1.86326 * eV, 1.88021 * eV, 1.89748 * eV, 1.91506 * eV, 1.93297 * eV, 1.95122 * eV, 1.96982 * eV, 1.98877 * eV, 2.0081 * eV,
       2.0278 * eV, 2.04789 * eV, 2.06839 * eV, 2.0893 * eV, 2.11064 * eV, 2.13242 * eV, 2.15465 * eV, 2.17735 * eV, 2.20053 * eV,
       2.22422 * eV, 2.23022 * eV, 2.24231 * eV, 2.25455 * eV, 2.26691 * eV, 2.27941 * eV, 2.29205 * eV, 2.30483 * eV, 2.31776 * eV,
       2.33083 * eV, 2.34405 * eV, 2.35741 * eV, 2.37094 * eV, 2.38462 * eV, 2.39845 * eV, 2.41245 * eV, 2.42661 * eV, 2.44094 * eV,
       2.45545 * eV, 2.47012 * eV, 2.48497 * eV, 2.5 * eV, 2.51521 * eV, 2.53061 * eV, 2.5462 * eV, 2.56198 * eV, 2.57796 * eV,
       2.59414 * eV, 2.61053 * eV, 2.62712 * eV, 2.64392 * eV, 2.66094 * eV, 2.67819 * eV, 2.71335 * eV, 2.73128 * eV, 2.74945 * eV,
       2.76786 * eV, 2.78652 * eV, 2.80543 * eV, 2.8246 * eV, 2.84404 * eV, 2.86374 * eV, 2.88372 * eV, 2.90398 * eV, 2.92453 * eV,
       2.94537 * eV, 2.96651 * eV, 2.98795 * eV, 3.00971 * eV, 3.03178 * eV, 3.05419 * eV, 3.07692 * eV, 3.1 * eV, 3.12343 * eV,
       3.14721 * eV, 3.17136 * eV, 3.19588 * eV, 3.22078 * eV, 3.24607 * eV, 3.27177 * eV, 3.29787 * eV, 3.3244 * eV, 3.35135 * eV,
       3.37875 * eV, 3.40659 * eV, 3.4349 * eV, 3.46369 * eV, 3.49296 * eV, 3.52273 * eV, 3.58382 * eV, 3.61516 * eV, 3.67953 * eV,
       3.71257 * eV, 3.78049 * eV, 3.92405 * eV, 3.96166 * eV, 4 * eV, 4.03909 * eV, 4.07895 * eV, 4.1196 * eV, 4.16107 * eV,
       4.20339 * eV, 4.24658 * eV, 4.29066 * eV, 4.33566 * eV, 4.38163 * eV, 4.42857 * eV, 4.47653 * eV, 4.52555 * eV, 4.62687 * eV,
       4.67925 * eV, 4.78764 * eV, 4.96 * eV, 5.62461 * eV};

  std::vector<G4double> Absorption =
      {955.954000 * mm, 668.943000 * mm, 614.032000 * mm, 467.353000 * mm, 559.162000 * mm, 579.555000 * mm, 650.626000 * mm, 535.162000 * mm, 524.755000 * mm,
       540.255000 * mm, 600.531000 * mm, 519.526000 * mm, 526.569000 * mm, 516.447000 * mm, 502.306000 * mm, 518.467000 * mm, 522.762000 * mm, 503.951000 * mm,
       537.711000 * mm, 520.839000 * mm, 553.001000 * mm, 488.909000 * mm, 521.548000 * mm, 471.766000 * mm, 450.077000 * mm, 404.852000 * mm, 441.221000 * mm,
       440.960000 * mm, 411.248000 * mm, 380.195000 * mm, 399.852000 * mm, 380.692000 * mm, 372.110000 * mm, 362.841000 * mm, 370.628000 * mm, 355.130000 * mm,
       371.095000 * mm, 389.190000 * mm, 390.557000 * mm, 376.662000 * mm, 394.540000 * mm, 419.485000 * mm, 423.900000 * mm, 424.207000 * mm, 459.364000 * mm,
       432.117000 * mm, 450.723000 * mm, 444.802000 * mm, 451.629000 * mm, 415.643000 * mm, 458.704000 * mm, 473.048000 * mm, 388.097000 * mm, 445.714000 * mm,
       356.658000 * mm, 362.018000 * mm, 323.960000 * mm, 249.410000 * mm, 222.770000 * mm, 173.466000 * mm, 126.428000 * mm, 94.944500 * mm, 64.388500 * mm,
       45.198300 * mm, 30.697900 * mm, 20.705400 * mm, 14.095600 * mm, 9.563980 * mm, 6.555540 * mm, 4.590660 * mm, 3.251770 * mm, 2.439640 * mm, 1.899230 * mm,
       1.561530 * mm, 1.644290 * mm, 1.454600 * mm, 1.344050 * mm, 1.392430 * mm, 1.474630 * mm, 1.365870 * mm, 1.418190 * mm, 1.449410 * mm, 1.429420 * mm, 1.588940 * mm,
       1.456210 * mm, 1.313570 * mm, 1.626080 * mm, 1.611680 * mm, 1.429990 * mm, 1.472460 * mm, 1.501370 * mm, 1.565330 * mm, 1.556520 * mm, 1.413260 * mm, 1.651750 * mm,
       1.532130 * mm, 1.908330 * mm, 2.906480 * mm, 4.388340 * mm, 6.664950 * mm, 9.720680 * mm, 12.470900 * mm, 13.226400 * mm, 11.510300 * mm, 8.747250 * mm, 6.425540 * mm,
       4.638230 * mm, 3.356940 * mm, 2.389330 * mm, 1.730910 * mm, 1.621300 * mm, 1.349290 * mm, 1.371340 * mm, 1.454750 * mm, 1.353480 * mm, 1.092090 * mm, 1.486040 * mm,
       1.375890 * mm, 1.153950 * mm, 1.623740 * mm, 1.443300 * mm, 1.605000 * mm, 1.705960 * mm, 1.510680 * mm, 1.525980 * mm, 1.586010 * mm, 1.616290 * mm, 1.489230 * mm,
       1.483450 * mm, 1.411050 * mm, 1.685210 * mm, 1.409220 * mm, 1.232600 * mm, 1.707510 * mm, 1.382160 * mm, 1.322320 * mm, 1.441060 * mm, 1.478580 * mm, 0 * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  // --- Emission Spectrum
  //      Taken straight outta the spectrophotometer.
  //      Hope this doesn't kill the performance.      O.o'

  std::vector<G4double> PhotonEnergy_FAST = {1.425287 * eV, 1.426107 * eV, 1.426928 * eV, 1.427749 * eV, 1.428571 * eV, 1.429395 * eV, 1.430219 * eV, 1.431044 * eV, 1.431871 * eV, 1.432698 * eV, 1.433526 * eV, 1.434355 * eV,
                                             1.435185 * eV, 1.436016 * eV, 1.436848 * eV, 1.437681 * eV, 1.438515 * eV, 1.439350 * eV, 1.440186 * eV, 1.441023 * eV, 1.441860 * eV, 1.442699 * eV, 1.443539 * eV, 1.444380 * eV, 1.445221 * eV, 1.446064 * eV, 1.446908 * eV, 1.447752 * eV,
                                             1.448598 * eV, 1.449445 * eV, 1.450292 * eV, 1.451141 * eV, 1.451991 * eV, 1.452841 * eV, 1.453693 * eV, 1.454545 * eV, 1.455399 * eV, 1.456254 * eV, 1.457109 * eV, 1.457966 * eV, 1.458824 * eV, 1.459682 * eV, 1.460542 * eV, 1.461402 * eV,
                                             1.462264 * eV, 1.463127 * eV, 1.463991 * eV, 1.464855 * eV, 1.465721 * eV, 1.466588 * eV, 1.467456 * eV, 1.468324 * eV, 1.469194 * eV, 1.470065 * eV, 1.470937 * eV, 1.471810 * eV, 1.472684 * eV, 1.473559 * eV, 1.474435 * eV, 1.475312 * eV,
                                             1.476190 * eV, 1.477070 * eV, 1.477950 * eV, 1.478831 * eV, 1.479714 * eV, 1.480597 * eV, 1.481481 * eV, 1.482367 * eV, 1.483254 * eV, 1.484141 * eV, 1.485030 * eV, 1.485920 * eV, 1.486811 * eV, 1.487702 * eV, 1.488595 * eV, 1.489489 * eV,
                                             1.490385 * eV, 1.491281 * eV, 1.492178 * eV, 1.493076 * eV, 1.493976 * eV, 1.494876 * eV, 1.495778 * eV, 1.496681 * eV, 1.497585 * eV, 1.498489 * eV, 1.499395 * eV, 1.500302 * eV, 1.501211 * eV, 1.502120 * eV, 1.503030 * eV, 1.503942 * eV,
                                             1.504854 * eV, 1.505768 * eV, 1.506683 * eV, 1.507599 * eV, 1.508516 * eV, 1.509434 * eV, 1.510353 * eV, 1.511274 * eV, 1.512195 * eV, 1.513118 * eV, 1.514042 * eV, 1.514966 * eV, 1.515892 * eV, 1.516820 * eV, 1.517748 * eV, 1.518677 * eV,
                                             1.519608 * eV, 1.520540 * eV, 1.521472 * eV, 1.522406 * eV, 1.523342 * eV, 1.524278 * eV, 1.525215 * eV, 1.526154 * eV, 1.527094 * eV, 1.528035 * eV, 1.528977 * eV, 1.529920 * eV, 1.530864 * eV, 1.531810 * eV, 1.532756 * eV, 1.533704 * eV,
                                             1.534653 * eV, 1.535604 * eV, 1.536555 * eV, 1.537508 * eV, 1.538462 * eV, 1.539417 * eV, 1.540373 * eV, 1.541330 * eV, 1.542289 * eV, 1.543248 * eV, 1.544209 * eV, 1.545171 * eV, 1.546135 * eV, 1.547099 * eV, 1.548065 * eV, 1.549032 * eV,
                                             1.550000 * eV, 1.550969 * eV, 1.551940 * eV, 1.552912 * eV, 1.553885 * eV, 1.554859 * eV, 1.555834 * eV, 1.556811 * eV, 1.557789 * eV, 1.558768 * eV, 1.559748 * eV, 1.560730 * eV, 1.561713 * eV, 1.562697 * eV, 1.563682 * eV, 1.564669 * eV,
                                             1.565657 * eV, 1.566646 * eV, 1.567636 * eV, 1.568627 * eV, 1.569620 * eV, 1.570614 * eV, 1.571610 * eV, 1.572606 * eV, 1.573604 * eV, 1.574603 * eV, 1.575604 * eV, 1.576605 * eV, 1.577608 * eV, 1.578612 * eV, 1.579618 * eV, 1.580625 * eV, 1.581633 * eV, 1.582642 * eV, 1.583653 * eV, 1.584665 * eV, 1.585678 * eV, 1.586692 * eV, 1.587708 * eV,
                                             1.588725 * eV, 1.589744 * eV, 1.590763 * eV, 1.591784 * eV, 1.592807 * eV, 1.593830 * eV, 1.594855 * eV, 1.595882 * eV, 1.596909 * eV, 1.597938 * eV, 1.598968 * eV, 1.600000 * eV, 1.601033 * eV, 1.602067 * eV, 1.603103 * eV, 1.604140 * eV, 1.605178 * eV, 1.606218 * eV, 1.607259 * eV, 1.608301 * eV, 1.609345 * eV, 1.610390 * eV, 1.611436 * eV,
                                             1.612484 * eV, 1.613533 * eV, 1.614583 * eV, 1.615635 * eV, 1.616688 * eV, 1.617743 * eV, 1.618799 * eV, 1.619856 * eV, 1.620915 * eV, 1.621975 * eV, 1.623037 * eV, 1.624100 * eV, 1.625164 * eV, 1.626230 * eV, 1.627297 * eV, 1.628365 * eV, 1.629435 * eV, 1.630506 * eV, 1.631579 * eV, 1.632653 * eV, 1.633729 * eV, 1.634806 * eV, 1.635884 * eV,
                                             1.636964 * eV, 1.638045 * eV, 1.639128 * eV, 1.640212 * eV, 1.641297 * eV, 1.642384 * eV, 1.643472 * eV, 1.644562 * eV, 1.645654 * eV, 1.646746 * eV, 1.647841 * eV, 1.648936 * eV, 1.650033 * eV, 1.651132 * eV, 1.652232 * eV, 1.653333 * eV, 1.654436 * eV, 1.655541 * eV, 1.656647 * eV, 1.657754 * eV, 1.658863 * eV, 1.659973 * eV, 1.661085 * eV,
                                             1.662198 * eV, 1.663313 * eV, 1.664430 * eV, 1.665547 * eV, 1.666667 * eV, 1.667787 * eV, 1.668910 * eV, 1.670034 * eV, 1.671159 * eV, 1.672286 * eV, 1.673414 * eV, 1.674544 * eV, 1.675676 * eV, 1.676809 * eV, 1.677943 * eV, 1.679079 * eV, 1.680217 * eV, 1.681356 * eV, 1.682497 * eV, 1.683639 * eV, 1.684783 * eV, 1.685928 * eV, 1.687075 * eV,
                                             1.688223 * eV, 1.689373 * eV, 1.690525 * eV, 1.691678 * eV, 1.692833 * eV, 1.693989 * eV, 1.695147 * eV, 1.696306 * eV, 1.697467 * eV, 1.698630 * eV, 1.699794 * eV, 1.700960 * eV, 1.702128 * eV, 1.703297 * eV, 1.704467 * eV, 1.705640 * eV, 1.706813 * eV, 1.707989 * eV, 1.709166 * eV, 1.710345 * eV, 1.711525 * eV, 1.712707 * eV, 1.713891 * eV,
                                             1.715076 * eV, 1.716263 * eV, 1.717452 * eV, 1.718642 * eV, 1.719834 * eV, 1.721027 * eV, 1.722222 * eV, 1.723419 * eV, 1.724618 * eV, 1.725818 * eV, 1.727019 * eV, 1.728223 * eV, 1.729428 * eV, 1.730635 * eV, 1.731844 * eV, 1.733054 * eV, 1.734266 * eV, 1.735479 * eV, 1.736695 * eV, 1.737912 * eV, 1.739130 * eV, 1.740351 * eV, 1.741573 * eV,
                                             1.742797 * eV, 1.744023 * eV, 1.745250 * eV, 1.746479 * eV, 1.747710 * eV, 1.748942 * eV, 1.750176 * eV, 1.751412 * eV, 1.752650 * eV, 1.753890 * eV, 1.755131 * eV, 1.756374 * eV, 1.757619 * eV, 1.758865 * eV, 1.760114 * eV, 1.761364 * eV, 1.762615 * eV, 1.763869 * eV, 1.765125 * eV, 1.766382 * eV, 1.767641 * eV, 1.768902 * eV, 1.770164 * eV,
                                             1.771429 * eV, 1.772695 * eV, 1.773963 * eV, 1.775233 * eV, 1.776504 * eV, 1.777778 * eV, 1.779053 * eV, 1.780330 * eV, 1.781609 * eV, 1.782890 * eV, 1.784173 * eV, 1.785457 * eV, 1.786744 * eV, 1.788032 * eV, 1.789322 * eV, 1.790614 * eV, 1.791908 * eV, 1.793203 * eV, 1.794501 * eV,
                                             1.795800 * eV, 1.797101 * eV, 1.798405 * eV, 1.799710 * eV, 1.801017 * eV, 1.802326 * eV, 1.803636 * eV, 1.804949 * eV, 1.806264 * eV, 1.807580 * eV, 1.808899 * eV, 1.810219 * eV, 1.811541 * eV, 1.812865 * eV, 1.814192 * eV, 1.815520 * eV, 1.816850 * eV, 1.818182 * eV, 1.819516 * eV, 1.820852 * eV, 1.822190 * eV, 1.823529 * eV, 1.824871 * eV,
                                             1.826215 * eV, 1.827561 * eV, 1.828909 * eV, 1.830258 * eV, 1.831610 * eV, 1.832964 * eV, 1.834320 * eV, 1.835677 * eV, 1.837037 * eV, 1.838399 * eV, 1.839763 * eV, 1.841128 * eV, 1.842496 * eV, 1.843866 * eV, 1.845238 * eV, 1.846612 * eV, 1.847988 * eV, 1.849366 * eV, 1.850746 * eV, 1.852128 * eV, 1.853513 * eV, 1.854899 * eV, 1.856287 * eV,
                                             1.857678 * eV, 1.859070 * eV, 1.860465 * eV, 1.861862 * eV, 1.863261 * eV, 1.864662 * eV, 1.866065 * eV, 1.867470 * eV, 1.868877 * eV, 1.870287 * eV, 1.871698 * eV, 1.873112 * eV, 1.874528 * eV, 1.875946 * eV, 1.877366 * eV, 1.878788 * eV, 1.880212 * eV, 1.881639 * eV, 1.883068 * eV, 1.884498 * eV, 1.885932 * eV, 1.887367 * eV, 1.888804 * eV,
                                             1.890244 * eV, 1.891686 * eV, 1.893130 * eV, 1.894576 * eV, 1.896024 * eV, 1.897475 * eV, 1.898928 * eV, 1.900383 * eV, 1.901840 * eV, 1.903300 * eV, 1.904762 * eV, 1.906226 * eV, 1.907692 * eV, 1.909161 * eV, 1.910632 * eV, 1.912105 * eV, 1.913580 * eV, 1.915058 * eV, 1.916538 * eV, 1.918020 * eV, 1.919505 * eV, 1.920991 * eV, 1.922481 * eV,
                                             1.923972 * eV, 1.925466 * eV, 1.926962 * eV, 1.928460 * eV, 1.929961 * eV, 1.931464 * eV, 1.932970 * eV, 1.934477 * eV, 1.935988 * eV, 1.937500 * eV, 1.939015 * eV, 1.940532 * eV, 1.942052 * eV, 1.943574 * eV, 1.945098 * eV, 1.946625 * eV, 1.948154 * eV, 1.949686 * eV, 1.951220 * eV, 1.952756 * eV, 1.954295 * eV, 1.955836 * eV, 1.957380 * eV,
                                             1.958926 * eV, 1.960474 * eV, 1.962025 * eV, 1.963579 * eV, 1.965135 * eV, 1.966693 * eV, 1.968254 * eV, 1.969817 * eV, 1.971383 * eV, 1.972951 * eV, 1.974522 * eV, 1.976096 * eV, 1.977671 * eV, 1.979250 * eV, 1.980831 * eV, 1.982414 * eV, 1.984000 * eV, 1.985588 * eV, 1.987179 * eV, 1.988773 * eV, 1.990369 * eV, 1.991968 * eV, 1.993569 * eV,
                                             1.995173 * eV, 1.996779 * eV, 1.998388 * eV, 2.000000 * eV, 2.001614 * eV, 2.003231 * eV, 2.004850 * eV, 2.006472 * eV, 2.008097 * eV, 2.009724 * eV, 2.011354 * eV, 2.012987 * eV, 2.014622 * eV, 2.016260 * eV, 2.017901 * eV, 2.019544 * eV, 2.021190 * eV, 2.022838 * eV, 2.024490 * eV, 2.026144 * eV, 2.027800 * eV, 2.029460 * eV, 2.031122 * eV,
                                             2.032787 * eV, 2.034454 * eV, 2.036125 * eV, 2.037798 * eV, 2.039474 * eV, 2.041152 * eV, 2.042834 * eV, 2.044518 * eV, 2.046205 * eV, 2.047894 * eV, 2.049587 * eV, 2.051282 * eV, 2.052980 * eV, 2.054681 * eV, 2.056385 * eV, 2.058091 * eV, 2.059801 * eV, 2.061513 * eV, 2.063228 * eV, 2.064946 * eV, 2.066667 * eV, 2.068390 * eV, 2.070117 * eV,
                                             2.071846 * eV, 2.073579 * eV, 2.075314 * eV, 2.077052 * eV, 2.078793 * eV, 2.080537 * eV, 2.082284 * eV, 2.084034 * eV, 2.085786 * eV, 2.087542 * eV, 2.089301 * eV, 2.091062 * eV, 2.092827 * eV, 2.094595 * eV, 2.096365 * eV, 2.098139 * eV, 2.099915 * eV, 2.101695 * eV, 2.103478 * eV,
                                             2.105263 * eV, 2.107052 * eV, 2.108844 * eV, 2.110638 * eV, 2.112436 * eV, 2.114237 * eV, 2.116041 * eV, 2.117848 * eV, 2.119658 * eV, 2.121471 * eV, 2.123288 * eV, 2.125107 * eV, 2.126930 * eV, 2.128755 * eV, 2.130584 * eV, 2.132416 * eV, 2.134251 * eV, 2.136090 * eV, 2.137931 * eV, 2.139776 * eV, 2.141623 * eV, 2.143475 * eV, 2.145329 * eV,
                                             2.147186 * eV, 2.149047 * eV, 2.150911 * eV, 2.152778 * eV, 2.154648 * eV, 2.156522 * eV, 2.158399 * eV, 2.160279 * eV, 2.162162 * eV, 2.164049 * eV, 2.165939 * eV, 2.167832 * eV, 2.169729 * eV, 2.171629 * eV, 2.173532 * eV, 2.175439 * eV, 2.177349 * eV, 2.179262 * eV, 2.181179 * eV, 2.183099 * eV, 2.185022 * eV, 2.186949 * eV, 2.188879 * eV,
                                             2.190813 * eV, 2.192750 * eV, 2.194690 * eV, 2.196634 * eV, 2.198582 * eV, 2.200532 * eV, 2.202487 * eV, 2.204444 * eV, 2.206406 * eV, 2.208370 * eV, 2.210339 * eV, 2.212310 * eV, 2.214286 * eV, 2.216265 * eV, 2.218247 * eV, 2.220233 * eV, 2.222222 * eV, 2.224215 * eV, 2.226212 * eV, 2.228212 * eV, 2.230216 * eV, 2.232223 * eV, 2.234234 * eV,
                                             2.236249 * eV, 2.238267 * eV, 2.240289 * eV, 2.242315 * eV, 2.244344 * eV, 2.246377 * eV, 2.248413 * eV, 2.250454 * eV, 2.252498 * eV, 2.254545 * eV, 2.256597 * eV, 2.258652 * eV, 2.260711 * eV, 2.262774 * eV, 2.264840 * eV, 2.266910 * eV, 2.268984 * eV, 2.271062 * eV, 2.273144 * eV, 2.275229 * eV, 2.277319 * eV, 2.279412 * eV, 2.281509 * eV,
                                             2.283610 * eV, 2.285714 * eV, 2.287823 * eV, 2.289935 * eV, 2.292052 * eV, 2.294172 * eV, 2.296296 * eV, 2.298424 * eV, 2.300557 * eV, 2.302693 * eV, 2.304833 * eV, 2.306977 * eV, 2.309125 * eV, 2.311277 * eV, 2.313433 * eV, 2.315593 * eV, 2.317757 * eV, 2.319925 * eV, 2.322097 * eV, 2.324274 * eV, 2.326454 * eV, 2.328638 * eV, 2.330827 * eV,
                                             2.333020 * eV, 2.335217 * eV, 2.337418 * eV, 2.339623 * eV, 2.341832 * eV, 2.344045 * eV, 2.346263 * eV, 2.348485 * eV, 2.350711 * eV, 2.352941 * eV, 2.355176 * eV, 2.357414 * eV, 2.359657 * eV, 2.361905 * eV, 2.364156 * eV, 2.366412 * eV, 2.368672 * eV, 2.370937 * eV, 2.373206 * eV, 2.375479 * eV, 2.377756 * eV, 2.380038 * eV, 2.382325 * eV,
                                             2.384615 * eV, 2.386910 * eV, 2.389210 * eV, 2.391514 * eV, 2.393822 * eV, 2.396135 * eV, 2.398453 * eV, 2.400774 * eV, 2.403101 * eV, 2.405432 * eV, 2.407767 * eV, 2.410107 * eV, 2.412451 * eV, 2.414800 * eV, 2.417154 * eV, 2.419512 * eV, 2.421875 * eV, 2.424242 * eV, 2.426614 * eV, 2.428991 * eV, 2.431373 * eV, 2.433759 * eV, 2.436149 * eV,
                                             2.438545 * eV, 2.440945 * eV, 2.443350 * eV, 2.445759 * eV, 2.448174 * eV, 2.450593 * eV, 2.453017 * eV, 2.455446 * eV, 2.457879 * eV, 2.460317 * eV, 2.462761 * eV, 2.465209 * eV, 2.467662 * eV, 2.470120 * eV, 2.472582 * eV, 2.475050 * eV, 2.477522 * eV, 2.480000 * eV, 2.482482 * eV, 2.484970 * eV, 2.487462 * eV, 2.489960 * eV, 2.492462 * eV,
                                             2.494970 * eV, 2.497482 * eV, 2.500000 * eV, 2.502523 * eV, 2.505051 * eV, 2.507583 * eV, 2.510121 * eV, 2.512665 * eV, 2.515213 * eV, 2.517766 * eV, 2.520325 * eV, 2.522889 * eV, 2.525458 * eV, 2.528033 * eV, 2.530612 * eV, 2.533197 * eV, 2.535787 * eV, 2.538383 * eV, 2.540984 * eV,
                                             2.543590 * eV, 2.546201 * eV, 2.548818 * eV, 2.551440 * eV, 2.554068 * eV, 2.556701 * eV, 2.559340 * eV, 2.561983 * eV, 2.564633 * eV, 2.567288 * eV, 2.569948 * eV, 2.572614 * eV, 2.575286 * eV, 2.577963 * eV, 2.580645 * eV, 2.583333 * eV, 2.586027 * eV, 2.588727 * eV, 2.591432 * eV, 2.594142 * eV, 2.596859 * eV, 2.599581 * eV, 2.602308 * eV};

  std::vector<G4double> FastComponent =
      {
          0.160333, 0.172055, 0.180528, 0.185841, 0.188323, 0.188954, 0.186772, 0.182738, 0.178573, 0.175773, 0.174867, 0.173955, 0.172557, 0.171364, 0.170930, 0.170360, 0.168857, 0.167288, 0.165351, 0.163923, 0.162677, 0.161678, 0.161048, 0.160843, 0.160919, 0.160517, 0.160686, 0.160464,
          0.159976, 0.159308, 0.158286, 0.157136, 0.155732, 0.154752, 0.154047, 0.153539, 0.153576, 0.154763, 0.156705, 0.158406, 0.159616, 0.159562, 0.158966, 0.157962, 0.155876, 0.153398, 0.152418, 0.152958, 0.154043, 0.155506, 0.156696, 0.158246, 0.159557, 0.160035, 0.159984, 0.160655,
          0.161680, 0.162683, 0.163751, 0.164225, 0.164384, 0.163716, 0.162927, 0.161685, 0.161064, 0.161583, 0.163290, 0.166036, 0.169015, 0.172248, 0.174792, 0.177343, 0.178371, 0.179139, 0.179470, 0.179794, 0.180614, 0.181098, 0.181929, 0.182751, 0.184452, 0.184796, 0.185040, 0.185164,
          0.185262, 0.185692, 0.185288, 0.185155, 0.185544, 0.186761, 0.186675, 0.186026, 0.185206, 0.184357, 0.184081, 0.182930, 0.180970, 0.179324, 0.178990, 0.178807, 0.178816, 0.179548, 0.180189, 0.181705, 0.183860, 0.185555, 0.186864, 0.187659, 0.186991, 0.185885, 0.184938, 0.182451,
          0.179253, 0.176828, 0.175065, 0.174352, 0.174345, 0.174170, 0.174635, 0.176360, 0.177780, 0.178376, 0.179079, 0.179967, 0.180717, 0.181527, 0.182005, 0.182501, 0.182777, 0.182598, 0.181987, 0.181748, 0.181893, 0.182113, 0.182613, 0.182965, 0.183928, 0.184883, 0.185172, 0.185290,
          0.185926, 0.187299, 0.189183, 0.192071, 0.194687, 0.197445, 0.200288, 0.202261, 0.203751, 0.204776, 0.205879, 0.207200, 0.209689, 0.212624, 0.215543, 0.218708, 0.221917, 0.225334, 0.228164, 0.231296, 0.234249, 0.238200, 0.242831, 0.246744, 0.249958, 0.252404, 0.254520, 0.255287,
          0.255467, 0.255138, 0.255251, 0.256250, 0.257098, 0.258633, 0.260698, 0.263629, 0.266652, 0.269514, 0.271993, 0.274103, 0.275915, 0.276758, 0.277352, 0.277538, 0.277770, 0.278430, 0.279565, 0.280986, 0.282494, 0.284023, 0.284981, 0.285279, 0.285089, 0.284264, 0.283283, 0.282408,
          0.281352, 0.280817, 0.280748, 0.280999, 0.281389, 0.282203, 0.283156, 0.284094, 0.284769, 0.284727, 0.285041, 0.285578, 0.286377, 0.286919, 0.287022, 0.287172, 0.287323, 0.286838, 0.286101, 0.285711, 0.285562, 0.286258, 0.287810, 0.289147, 0.290564, 0.291878, 0.292197, 0.291950,
          0.291027, 0.289650, 0.288632, 0.288382, 0.288782, 0.289809, 0.290986, 0.292057, 0.293552, 0.294994, 0.296213, 0.297359, 0.298379, 0.299725, 0.301065, 0.301758,
          0.302152, 0.302418, 0.302455, 0.302965, 0.303988, 0.305269, 0.307792, 0.311004, 0.314233, 0.317157, 0.319612, 0.321208, 0.322833, 0.323933, 0.324668, 0.325648, 0.326384, 0.327127, 0.327983, 0.329782, 0.331478, 0.334153, 0.337734, 0.342331, 0.347829, 0.353863, 0.359909, 0.365554,
          0.371182, 0.375309, 0.378078, 0.380650, 0.383559, 0.386661, 0.391209, 0.396554, 0.403391, 0.412262, 0.421569, 0.430263, 0.438646, 0.446296, 0.452533, 0.459093, 0.464611, 0.470111, 0.475587, 0.480986, 0.486321, 0.492086, 0.497950, 0.503656, 0.510915, 0.518411, 0.525585, 0.531775,
          0.537243, 0.541844, 0.545787, 0.548832, 0.551114, 0.554734, 0.560204, 0.566683, 0.574083, 0.582899, 0.591700, 0.599719, 0.606075, 0.610675, 0.613892, 0.616678, 0.619201, 0.621949, 0.626338, 0.631770, 0.637622, 0.643314, 0.648892, 0.654411, 0.659824, 0.665181, 0.670375, 0.676088,
          0.683226, 0.690607, 0.698531, 0.708160, 0.718258, 0.728716, 0.739570, 0.751581, 0.763034, 0.775454, 0.786540, 0.797086, 0.808549, 0.820140, 0.831665, 0.843176, 0.856263, 0.868398, 0.881225, 0.892920, 0.904357, 0.915893, 0.928096, 0.939263, 0.948868, 0.959247, 0.969073, 0.979514,
          0.991217, 1.006180, 1.022176, 1.040957, 1.060646, 1.080315, 1.099629, 1.117168, 1.132367, 1.143713, 1.154007, 1.162971, 1.172804, 1.183047, 1.193364, 1.204806, 1.218254, 1.233768, 1.249340, 1.264735, 1.280843, 1.298822, 1.316305, 1.333060, 1.349401, 1.365012, 1.381080, 1.398043,
          1.414998, 1.433156, 1.453538, 1.475149, 1.497840, 1.522714, 1.549153, 1.575589, 1.602703, 1.629766, 1.657771, 1.686157, 1.713829, 1.740740, 1.768848, 1.797099, 1.826433, 1.856914, 1.887414, 1.920113, 1.952943, 1.984931, 2.016673, 2.048364, 2.080761, 2.114546, 2.150983, 2.187603,
          2.227391, 2.267608, 2.308318, 2.349979, 2.391574, 2.432560, 2.473686, 2.517020, 2.560338, 2.606682, 2.652806, 2.697589, 2.740990, 2.782212, 2.822549, 2.863372, 2.906545, 2.951182, 2.999788, 3.049974, 3.101279, 3.150571, 3.197309, 3.241397, 3.282194, 3.319780, 3.355298, 3.394046,
          3.434711, 3.481092, 3.529849, 3.581205, 3.636162, 3.692668, 3.749120, 3.806017, 3.865440, 3.920449, 3.976139, 4.028575, 4.079399, 4.129317, 4.178763, 4.227938, 4.276508, 4.328505, 4.377710, 4.431798, 4.485211, 4.542401, 4.602420, 4.665596, 4.733517, 4.805294, 4.881597, 4.955312,
          5.031172, 5.103682, 5.172749, 5.236611, 5.298137, 5.359899, 5.419967, 5.482172, 5.543176, 5.605148, 5.670492, 5.740138, 5.814321, 5.895414, 5.981730, 6.071641, 6.164834, 6.256723, 6.343300, 6.426013, 6.507092, 6.584824, 6.664619, 6.745062, 6.824841, 6.905505, 6.987358, 7.068448,
          7.145806, 7.223107, 7.299318, 7.382849, 7.469975, 7.558261, 7.648318, 7.739405, 7.832896, 7.927704, 8.024399, 8.117990, 8.213648, 8.309669, 8.403208, 8.491036, 8.573814, 8.653141, 8.732364, 8.812956, 8.896425, 8.982942, 9.074628, 9.172558, 9.271829, 9.373102, 9.471807, 9.568671, 9.664489, 9.764401, 9.862431, 9.961527,
          10.062514, 10.162395, 10.267956, 10.377316, 10.486914, 10.593941, 10.704643, 10.812764, 10.922728, 11.031806, 11.136382, 11.240701, 11.348914, 11.457710, 11.560809, 11.666111, 11.769687, 11.873744, 11.982856, 12.091494, 12.195096, 12.306485, 12.424388, 12.538396, 12.649503,
          12.755230, 12.852457, 12.955026, 13.057408, 13.151514, 13.249479, 13.360196, 13.475367, 13.590405, 13.703543, 13.809648, 13.920157, 14.030500, 14.136132, 14.234845, 14.337392, 14.440752, 14.542470, 14.643342, 14.742330, 14.837359, 14.933357, 15.030482, 15.121741, 15.217645,
          15.311870, 15.403404, 15.499368, 15.605598, 15.711020, 15.818623, 15.928037, 16.034052, 16.143130, 16.247351, 16.339258, 16.425389, 16.516449, 16.606260, 16.696443, 16.790204, 16.882196, 16.980250, 17.080543, 17.177801, 17.265764, 17.349557, 17.429280, 17.505393, 17.582362,
          17.656297, 17.732708, 17.816212, 17.908350, 18.003255, 18.095199, 18.181472, 18.269397, 18.354728, 18.434323, 18.510606, 18.596313, 18.693102, 18.802602, 18.911997, 19.015629, 19.124369, 19.229364, 19.323701, 19.402913, 19.483465, 19.560596, 19.641053, 19.718309, 19.792413,
          19.869586, 19.949725, 20.026719, 20.095968, 20.171002, 20.255738, 20.345770, 20.434825, 20.524169, 20.604079, 20.677508, 20.741404, 20.794106, 20.843678, 20.898596, 20.953907, 21.011152, 21.081034, 21.153868, 21.230743, 21.305027, 21.372700, 21.432274, 21.489282, 21.538526,
          21.580936, 21.626996, 21.670602, 21.712001, 21.748164, 21.781695, 21.812616, 21.837206, 21.857631, 21.878914, 21.906131, 21.934830, 21.957913, 21.976860, 21.991334, 22.003585, 22.005043, 21.998509, 21.990289, 21.987864, 21.988827, 21.987035, 21.980584, 21.963873, 21.947645,
          21.926436, 21.896811, 21.859359, 21.814038, 21.758221,
          21.698002, 21.635145, 21.566074, 21.493923, 21.423607, 21.353887, 21.278387, 21.189528, 21.081072, 20.957433, 20.818778, 20.670547, 20.513037, 20.350933, 20.191659, 20.036380, 19.873308, 19.701685, 19.519604, 19.329683, 19.135690, 18.936732, 18.729052, 18.519217, 18.310576,
          18.094135, 17.867046, 17.627899, 17.378721, 17.118091, 16.853280, 16.576317, 16.292254, 16.011360, 15.733297, 15.457866, 15.182900, 14.905330, 14.621737, 14.337595, 14.046097, 13.746192, 13.443646, 13.141727, 12.844686, 12.550631, 12.257647, 11.962531, 11.666829, 11.369029,
          11.064639, 10.758183, 10.449219, 10.146628,
          9.845579, 9.550573, 9.256683, 8.963058, 8.669924, 8.372660, 8.075375, 7.777387, 7.485712, 7.198002, 6.920792, 6.650151, 6.388837, 6.131463, 5.875763, 5.623275, 5.370905, 5.120390, 4.872820, 4.632578, 4.396777, 4.168619, 3.945906, 3.727595, 3.515392, 3.310932, 3.113700, 2.926979,
          2.751590, 2.588683, 2.439079, 2.300711, 2.169602, 2.044509, 1.925282, 1.810431, 1.701355, 1.600311, 1.508377, 1.428058, 1.361947, 1.306719, 1.260604, 1.221590, 1.187067, 1.155297, 1.125212, 1.094388, 1.064629, 1.039276, 1.018386, 1.002130, 0.991032, 0.985420, 0.984140};

  //** scintillation and optical properties **//
  G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
  mt->AddProperty("RINDEX", PhotonEnergy_RI, RefractiveIndex);
  mt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  mt->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  mt->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  mt->AddConstProperty("RESOLUTIONSCALE", 4.8);
  mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 150. * ns);
  mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0); // Ratio between fast component and total light yield. Ignore the documentation.

  mat->SetMaterialPropertiesTable(mt);

  return mat;
}

G4Material *MyMaterials::ESR_Vikuiti()
{
  G4double density;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *C = man->FindOrBuildElement("C");
  G4Element *F = man->FindOrBuildElement("F");
  // G4Element* C = new G4Element("Carbon"  , "C", z=6., a=12.01*g/mole);
  // G4Element* F = new G4Element("Fluorine", "F", z=9., a= 18.99*g/mole);
  G4Material *mat = new G4Material("ESR_Vikuiti", density = 1.29 * g / cm3, 2);
  mat->AddElement(C, 2);
  mat->AddElement(F, 4);

  return mat;
}

// outer cladding of the clear fibers: Fluorinated Polymer (FP)  !!! not yet implemeted, waiting for Kuraray answer on the precise material composition
G4Material *MyMaterials::FlurPoly(double scaleFactor)
{
  G4double a, z, density;
  G4Element *H = new G4Element("Hydrogen", "H", z = 1., a = 1.01 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);

  G4Material *mat = new G4Material("FlurPoly", density = 1.43 * g / cm3, 2);
  mat->AddElement(C, 5);
  mat->AddElement(H, 8);

  const G4int nEntries = 35;
  G4double PhotonEnergy[nEntries] =
      {0.0001 * eV, 1.000 * eV, 2.034 * eV, 2.068 * eV,
       2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
       2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV,
       2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV,
       2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
       2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV,
       3.181 * eV, 3.265 * eV, 3.353 * eV, 3.446 * eV,
       3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
       4.002 * eV, 4.136 * eV, 6.260 * eV};
  G4double RefractiveIndex[nEntries] =
      {1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42, 1.42,
       1.42, 1.42, 1.42};

  // FOR THE MOMENT, SAME AS POLYSTYRENE - need to find proper values

  std::vector<G4double> PhotonEnergy_ABS =
      {0.1 * eV, 1. * eV, 2. * eV, 3. * eV, 4. * eV, 5 * eV, 6. * eV, 10. * eV};
  std::vector<G4double> Absorption =
      // Nuclear Instruments and Methods in Physics Research A 555 (2005) 125–131. No Energy dependecy ref.
      {1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  if (scaleFactor > 0)
  {
    myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  }

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

// intermediate cladding of the clear fibers: Polystyrene (PS)
G4Material *MyMaterials::Polystyrene(double user_lightyield, double scaleFactor, double user_birks)
{

  double standard_light_yield = 9744; // 56 % of Anthracene (17,400 photons/MeV). !!! : to be tuned depending on the spedific product,
                                      // fluctuates depending on specific composition.
  
double lightyield = (user_lightyield == -1) ? standard_light_yield : user_lightyield;

  G4double a, z, density;
  G4Element *H = new G4Element("Hydrogen", "H", z = 1., a = 1.01 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);

  G4Material *mat = new G4Material("Polystyrene", density = 1.06 * g / cm3, 2); // AMCRYS producer
  mat->AddElement(C, 8);
  mat->AddElement(H, 8);
  // double lightyield = 9744; // 56 % of Anthracene (17,400 photons/MeV). !!! : to be tuned depending on the spedific product,
  // fluctuates depending on specific composition.

  //--------//
  // BIRKS  //
  //--------//
  // standard_birks = 0. means birks law will not be used.
  // Modify if the value is known for this material
  double standard_birks = 0.126;
  double birks;
  if (user_birks < 0)
  {
    birks = standard_birks;
  }
  else
  {
    birks = user_birks;
  }
  // Set the Birks Constant for the scintillator
  mat->GetIonisation()->SetBirksConstant(birks * mm / MeV);
  //--------//

  const G4int nEntries = 19;
  G4double PhotonEnergy[nEntries] =
      {0.1 * eV, 1.207 * eV, 1.300 * eV, 1.409 * eV, 1.504 * eV,
       1.599 * eV, 1.708 * eV, 1.799 * eV, 1.901 * eV,
       1.995 * eV, 2.099 * eV, 2.191 * eV, 2.290 * eV,
       2.399 * eV, 2.519 * eV, 2.617 * eV, 2.723 * eV,
       2.838 * eV, 10. * eV};
  G4double RefractiveIndex[nEntries] =
      {1.572, 1.572, 1.574, 1.576, 1.577,
       1.579, 1.581, 1.584, 1.586,
       1.588, 1.591, 1.594, 1.597,
       1.601, 1.605, 1.608, 1.612, 1.616,
       1.616};

  std::vector<G4double> PhotonEnergy_ABS =
      {0.1 * eV, 1. * eV, 2. * eV, 3. * eV, 4. * eV, 5 * eV, 6. * eV, 10. * eV};
  std::vector<G4double> Absorption =
      // Nuclear Instruments and Methods in Physics Research A 555 (2005) 125–131. No Energy dependecy ref.
      {1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  std::vector<G4double> PhotonEnergy_FAST = {3.44749667700487 * eV,
                                             3.35099052540913 * eV, 3.30543755310110 * eV, 3.26384228187919 * eV, 3.22194616977226 * eV, 3.17981201471189 * eV,
                                             3.13750000000000 * eV, 3.09876543209877 * eV, 3.06459235919653 * eV, 3.02174757281553 * eV, 2.98694817658349 * eV, 2.95294117647059 * eV,
                                             2.91860465116279 * eV, 2.88398813936249 * eV, 2.85122755588128 * eV, 2.81716147719044 * eV, 2.78489620615605 * eV, 2.75238769013088 * eV,
                                             2.72539404553415 * eV, 2.69518531347419 * eV, 2.66655243317341 * eV, 2.63762711864407 * eV, 2.60844787127053 * eV, 2.58076285240464 * eV,
                                             2.55449770190414 * eV, 2.53122966818478 * eV, 2.50434502735758 * eV, 2.47960484384959 * eV, 2.45534869043862 * eV, 2.43080287410184 * eV,
                                             2.40897832817337 * eV, 2.38461538461538 * eV, 2.36145675265554 * eV, 2.33944678292243 * eV, 2.31853396901073 * eV, 2.29663518299882 * eV,
                                             2.27781030444965 * eV, 2.25340283811179 * eV};
  // Synthesis and characterization of polystyrene scintillators and their application in positron emission tomography L-2. Kaplon 2017
  std::vector<G4double> FastComponent = {0.0286475400174451,
                                         0.0484224836354779, 0.134739542814934, 0.216124063902182, 0.292085307684450, 0.364102564102564, 0.423300093511555, 0.451924059187314, //
                                         0.438139355791823, 0.407595652891393, 0.373102461947084, 0.342554044178316, 0.321868345159795, 0.279980276134122, 0.223298521888776,
                                         0.193738654848063, 0.162698712055133, 0.135111231602191, 0.118861044971986, 0.100641614999568, 0.0834075925096459, 0.0691329357127703,
                                         0.0543659680803414, 0.0474877609876077, 0.0420880580243130, 0.0386583842146209, 0.0332602528741053, 0.0288467432046960, 0.0273918134169437,
                                         0.0249514761466954, 0.0225087814422783, 0.0200692299834194, 0.0205874725948280, 0.0191325428070755, 0.0196492137957047, 0.0196743597601704,
                                         0.0172308792443638, 0.0172599542657772};
  
  // reverse std::vector<G4double> PhotonEnergy_FAST 
  std::reverse(PhotonEnergy_FAST.begin(), PhotonEnergy_FAST.end());
  std::reverse(FastComponent.begin(), FastComponent.end());


  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);

  myMPT->AddProperty("SCINTILLATIONCOMPONENT1", PhotonEnergy_FAST, FastComponent);

  myMPT->AddConstProperty("SCINTILLATIONYIELD", lightyield / MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE", 4.); // !!! we need to estimate this parameter from measurements and sims !!!
  // Transactions of the Korean Nuclear Society Autumn Meeting Yeosu, Korea, October 25-26, 2018
  // +   Proceedings of the SPIE, Volume 9968, id. 996803 7 pp. (2016).
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2. * ns); // Synthesis and characterization of polystyrene scintillators and their application in positron emission tomography L-2. Kaplon 2017. Matches AMSYS producer
  myMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 7. * ns); // some report a small fraction of slower tail .. to be checked.
  myMPT->AddConstProperty("SCINTILLATIONYIELD1", 0.95);
  myMPT->AddConstProperty("SCINTILLATIONYIELD2", 0.05);


  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4Material *MyMaterials::PLEX(double scaleFactor)
{
  G4double a, z, density;
  G4Element *H = new G4Element("Hydrogen", "H", z = 1., a = 1.01 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);

  G4Material *mat = new G4Material("PLEX", density = 1.19 * g / cm3, 3);
  mat->AddElement(C, 5);
  mat->AddElement(H, 8);
  mat->AddElement(O, 2);

  const G4int nEntries = 35;
  G4double PhotonEnergy[nEntries] =
      {0.0001 * eV, 1.000 * eV, 2.034 * eV, 2.068 * eV,
       2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
       2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV,
       2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV,
       2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
       2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV,
       3.181 * eV, 3.265 * eV, 3.353 * eV, 3.446 * eV,
       3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
       4.002 * eV, 4.136 * eV, 6.260 * eV};
  G4double RefractiveIndex[nEntries] =
      {1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50, 1.50,
       1.50, 1.50, 1.50};

  // FOR THE MOMENT, SAME AS POLYSTYRENE - need to find proper values

  std::vector<G4double> PhotonEnergy_ABS =
      {0.1 * eV, 1. * eV, 2. * eV, 3. * eV, 4. * eV, 5 * eV, 6. * eV, 10. * eV};
  std::vector<G4double> Absorption =
      // Nuclear Instruments and Methods in Physics Research A 555 (2005) 125–131. No Energy dependecy ref.
      {1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm, 1900. * mm};

  // G4cout << " ------------> Scaling ABS by " << scaleFactor << G4endl;
  for (auto &value : Absorption)
  {
    value *= scaleFactor;
  }

  G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  if (scaleFactor > 0)
  {
    myMPT->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption);
  }

  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}

G4MaterialPropertiesTable *MyMaterials::ESR(double esrTransmittance)
{
  G4MaterialPropertiesTable *ESR_surf = new G4MaterialPropertiesTable();

  // ESR
  //  实部折射指数（REALRINDEX）和虚部折射指数（IMAGINARYRINDEX）：定义了光在材料中传播时折射指数的变化，这影响光在材料中的吸收和反射。
  //  透射率（TRANSMITTANCE）：根据esrTransmittance的值，可以是固定的或根据能量动态定义的透射率，用于模拟光通过ESR材料的部分透射。
  const G4int NUMvikuiti = 29;
  G4double vikuiti_energy_im[NUMvikuiti] = {1.25 * eV, 1.31 * eV, 1.34 * eV, 1.38 * eV, 1.42 * eV, 1.46 * eV, 1.51 * eV, 1.60 * eV, 1.66 * eV, 1.75 * eV, 1.80 * eV, 1.90 * eV, 1.95 * eV, 2.05 * eV, 2.10 * eV, 2.20 * eV, 2.26 * eV, 2.35 * eV, 2.45 * eV, 2.51 * eV, 2.71 * eV, 2.81 * eV, 3.01 * eV, 3.21 * eV, 3.41 * eV, 3.55 * eV, 3.71 * eV, 3.91 * eV, 4.14 * eV};

  // we specify the imaginary index WITHOUT dividing by 1.47 because in this matrix
  // esr is in air contact with everything, so n1=1
  G4double vikuiti_RIndex_im[NUMvikuiti] = {9.49, 8.88, 8.49, 8.30, 8.18, 8.22, 8.31, 8.60, 8.62, 8.39, 8.21, 7.82, 7.65, 7.31, 7.15, 6.85, 6.69, 6.42, 6.15, 6.03, 5.58, 5.38, 5.02, 4.71, 4.43, 4.24, 4.06, 3.84, 3.61};
  G4double vikuiti_energy_re[NUMvikuiti] = {1.24 * eV, 1.27 * eV, 1.31 * eV, 1.34 * eV, 1.38 * eV, 1.42 * eV, 1.46 * eV, 1.51 * eV, 1.55 * eV, 1.60 * eV, 1.66 * eV, 1.71 * eV, 1.77 * eV, 1.84 * eV, 1.91 * eV, 1.99 * eV, 2.07 * eV, 2.16 * eV, 2.26 * eV, 2.37 * eV, 2.48 * eV, 2.62 * eV, 2.76 * eV, 2.92 * eV, 3.11 * eV, 3.31 * eV, 3.55 * eV, 3.82 * eV, 4.14 * eV};

  G4double vikuiti_RIndex_re[NUMvikuiti] = {0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.1, 0.6, 1.2, 0.4, 0.23, 0.17, 0.26, 1.3, 0.24, 0.11, 0.19, 0.24, 0.25, 0.87, 0.595, 0.18, 0.178, 0.6, 8.0, 8.0, 8.0, 8.0};
  const G4int NUMu = 2;
  G4double pp[NUMu] = {2.038 * eV, 4.144 * eV};

  // double esrTransmittance = 0.02;
  G4double FixedTransmittance_surf[NUMu] = {esrTransmittance, esrTransmittance};

  G4double esrTransmittance_energy[] = {2.7008152174 * eV, 2.7304945055 * eV, 2.7608333333 * eV, 2.7918539326 * eV, 2.8235795455 * eV, 2.8560344828 * eV, 2.889244186 * eV, 2.9232352941 * eV, 2.9580357143 * eV, 2.9936746988 * eV, 3.0301829268 * eV, 3.0675925926 * eV, 3.1059375 * eV, 3.1452531646 * eV, 3.1855769231 * eV, 3.2269480519 * eV, 3.2694078947 * eV};
  G4double esrTransmittance_values[] = {0.0024, 0.0025, 0.002, 0.0024, 0.0015, 0.0011, 0.0011, 0.0011, 0.0009, 0.0007, 0.001, 0.0016, 0.005, 0.0164, 0.0303, 0.0365, 0.0389};
  const G4int numEsrTrans = sizeof(esrTransmittance_energy) / sizeof(G4double);
  assert(sizeof(esrTransmittance_energy) == sizeof(esrTransmittance_values));

  ESR_surf->AddProperty("REALRINDEX", vikuiti_energy_re, vikuiti_RIndex_re, NUMvikuiti);
  ESR_surf->AddProperty("IMAGINARYRINDEX", vikuiti_energy_im, vikuiti_RIndex_im, NUMvikuiti);
  if (esrTransmittance == -1)
  {
    ESR_surf->AddProperty("TRANSMITTANCE", esrTransmittance_energy, esrTransmittance_values, numEsrTrans);
  }
  else
  {
    ESR_surf->AddProperty("TRANSMITTANCE", pp, FixedTransmittance_surf, NUMu);
  }

  return ESR_surf;
}

//--------------------------//
// TEFLON                   //
//--------------------------//
G4MaterialPropertiesTable *MyMaterials::Teflon()
{
  G4MaterialPropertiesTable *Teflon_surf = new G4MaterialPropertiesTable();

  // surf roughness
  const G4int Np = 2;
  G4double Energy[Np] = {0 * eV, 6 * eV};
  // set all to 0, so it's lambertian
  G4double SpecularLobeVector[Np] = {0, 0};
  G4double SpecularspikeVector[Np] = {0, 0};
  G4double BackscatterVector[Np] = {0, 0};
  G4double reflectivity[Np] = {0.98, 0.98};        // 98% reflectivity
  G4double TransmittanceVector[Np] = {0.02, 0.02}; // 2% transmittance
  Teflon_surf->AddProperty("SPECULARLOBECONSTANT", Energy, SpecularLobeVector, Np);
  Teflon_surf->AddProperty("SPECULARSPIKECONSTANT", Energy, SpecularspikeVector, Np);
  Teflon_surf->AddProperty("BACKSCATTERCONSTANT", Energy, BackscatterVector, Np);
  Teflon_surf->AddProperty("TRANSMITTANCE", Energy, TransmittanceVector, Np);
  Teflon_surf->AddProperty("REFLECTIVITY", Energy, reflectivity, Np);

  return Teflon_surf;
}

//--------------------------//
// TiO2                   //
//--------------------------//
G4MaterialPropertiesTable *MyMaterials::TiO2()
{
  G4MaterialPropertiesTable *TiO2_surf = new G4MaterialPropertiesTable();

  // surf roughness
  const G4int Np = 2;
  G4double Energy[Np] = {0 * eV, 6 * eV};
  // set all to 0, so it's lambertian
  G4double SpecularLobeVector[Np] = {0, 0};
  G4double SpecularspikeVector[Np] = {0, 0};
  G4double BackscatterVector[Np] = {0, 0};
  G4double reflectivity[Np] = {0.9, 0.9};
  G4double TransmittanceVector[Np] = {0.02, 0.02}; // 2% transmittance
  TiO2_surf->AddProperty("SPECULARLOBECONSTANT", Energy, SpecularLobeVector, Np);
  TiO2_surf->AddProperty("SPECULARSPIKECONSTANT", Energy, SpecularspikeVector, Np);
  TiO2_surf->AddProperty("BACKSCATTERCONSTANT", Energy, BackscatterVector, Np);
  TiO2_surf->AddProperty("TRANSMITTANCE", Energy, TransmittanceVector, Np);
  TiO2_surf->AddProperty("REFLECTIVITY", Energy, reflectivity, Np);

  return TiO2_surf;
}
//--------------------------//

G4MaterialPropertiesTable *MyMaterials::ABS_SURF(G4double Reflectivity, G4double specularLobe, G4double specularSpike, G4double backScatter)
{
  // ABS（丙烯腈-丁二烯-苯乙烯共聚物）是一种常见的塑料材料
  // 这段代码定义了一个具有可配置光学属性的ABS材料表面
  G4MaterialPropertiesTable *surfPT = new G4MaterialPropertiesTable();
  const G4int Np = 2;

  G4double Energy[Np] = {0 * eV, 6 * eV};
  G4double SpecularLobeVector[Np] = {specularLobe, specularLobe};
  G4double SpecularspikeVector[Np] = {specularSpike, specularSpike};
  G4double BackscatterVector[Np] = {backScatter, backScatter};
  G4double ReflectivityVector[Np] = {Reflectivity, Reflectivity};
  surfPT->AddProperty("SPECULARLOBECONSTANT", Energy, SpecularLobeVector, Np);
  surfPT->AddProperty("SPECULARSPIKECONSTANT", Energy, SpecularspikeVector, Np);
  surfPT->AddProperty("BACKSCATTERCONSTANT", Energy, BackscatterVector, Np);

  if (Reflectivity != -1)
  {
    surfPT->AddProperty("REFLECTIVITY", Energy, ReflectivityVector, Np);
  }

  G4double index_energy[] = {0.5009458867 * eV, 0.7514186785 * eV, 1.0018917733 * eV, 1.2523642116 * eV, 1.502838266 * eV, 1.7533109568 * eV, 2.0037835466 * eV, 2.2542560354 * eV, 2.5047284232 * eV, 2.7552001544 * eV, 3.0056728957 * eV, 3.2561469501 * eV, 3.5066169642 * eV, 3.7570888469 * eV, 4.0075735579 * eV};
  G4double reIndex_value[] = {1.2049, 2.4636, 4.3505, 2.1933, 1.1957, 0.8969, 0.933, 1.3296, 2.0777, 2.2457, 1.6556, 1.2611, 1.327, 2.0193, 1.8008};
  G4double imIndex_value[] = {24.3542, 14.8056, 13.142, 11.8617, 9.6069, 7.8089, 6.3712, 5.2379, 4.782, 5.1471, 5.1025, 4.516, 3.806, 3.578, 4.3314};
  const G4int NUMindex = sizeof(index_energy) / sizeof(G4double);
  assert(sizeof(index_energy) == sizeof(reIndex_value));
  assert(sizeof(index_energy) == sizeof(imIndex_value));
  surfPT->AddProperty("REALRINDEX", reIndex_value, index_energy, NUMindex);
  surfPT->AddProperty("IMAGINARYRINDEX", imIndex_value, index_energy, NUMindex);

  return surfPT;
}

G4MaterialPropertiesTable *MyMaterials::crystal_depo_SURF()
{
  G4MaterialPropertiesTable *crystalReal_surf = new G4MaterialPropertiesTable();
  const G4int Ndepo = 2;
  G4double depoEnergy[Ndepo] = {0 * eV, 6 * eV};
  G4double specularlobeRealVector[Ndepo] = {1, 1};
  G4double specularspikeRealVector[Ndepo] = {0, 0};
  G4double backscatterRealVector[Ndepo] = {0, 0};

  // 镜面反射（SPECULARLOBECONSTANT）：指的是光在遇到材料表面时以相同的角度反射，常见于平滑、光滑的表面。
  // 尖峰反射（SPECULARSPIKECONSTANT）：通常发生在具有特定微结构的表面上，例如光纤内壁，这种反射有助于光沿原有路径传播。
  // 反向散射（BACKSCATTERCONSTANT）：描述光在与材料表面相互作用后向后散射的情况，这在某些传感器和探测器应用中需要被考虑。
  // **镜面反射分量（SPECULARLOBECONSTANT）**设为 {1, 1}，意味着在所有给定的能量点上，镜面反射分量是最大的，即所有的反射都是镜面反射。
  // **尖峰反射分量（SPECULARSPIKECONSTANT）**设为 {0, 0}，表示没有尖峰反射发生。
  // **反向散射分量（BACKSCATTERCONSTANT）**也设为 {0, 0}，表示没有反向散射。
  crystalReal_surf->AddProperty("SPECULARLOBECONSTANT", depoEnergy, specularlobeRealVector, Ndepo);
  crystalReal_surf->AddProperty("SPECULARSPIKECONSTANT", depoEnergy, specularspikeRealVector, Ndepo);
  crystalReal_surf->AddProperty("BACKSCATTERCONSTANT", depoEnergy, backscatterRealVector, Ndepo);
  return crystalReal_surf;
}

G4MaterialPropertiesTable *MyMaterials::clear_fiber_optical()
{
  G4MaterialPropertiesTable *clear_optical = new G4MaterialPropertiesTable();
  const G4int Ndepo = 2;
  G4double depoEnergy[Ndepo] = {0 * eV, 6 * eV};
  G4double specularlobeRealVector[Ndepo] = {0, 0};
  G4double specularspikeRealVector[Ndepo] = {1, 1};
  G4double backscatterRealVector[Ndepo] = {0, 0};
  clear_optical->AddProperty("SPECULARLOBECONSTANT", depoEnergy, specularlobeRealVector, Ndepo);
  clear_optical->AddProperty("SPECULARSPIKECONSTANT", depoEnergy, specularspikeRealVector, Ndepo);
  clear_optical->AddProperty("BACKSCATTERCONSTANT", depoEnergy, backscatterRealVector, Ndepo);
  return clear_optical;
}

// ------------- Surfaces --------------
// Teflon，TiO2
// 晶体到空气层，晶体到Teflon，晶体到crystal入射窗，晶体到硅脂，硅脂到入射窗
//
G4OpticalSurface *MyMaterials::surf_Teflon()
{
  // Teflon surface
  G4OpticalSurface *surf_teflon = new G4OpticalSurface("surf_teflon");
  surf_teflon->SetType(dielectric_dielectric); // Teflon视为非金属
  surf_teflon->SetFinish(groundfrontpainted);  // 漫反射表面处理
  surf_teflon->SetModel(unified);              // 使用统一模型
  surf_teflon->SetMaterialPropertiesTable(MyMaterials::Teflon());
  // surf_teflon->SetSigmaAlpha(); // 表面粗糙度的贡献，与测得的Ra不完全一样，这里暂时忽略不管。据SpaCal的模拟来看并不关键

  return surf_teflon;
}
G4OpticalSurface *MyMaterials::surf_TiO2()
{
  // TiO2 coating surface
  G4OpticalSurface *surf_TiO2 = new G4OpticalSurface("surf_TiO2");
  surf_TiO2->SetType(dielectric_dielectric); // Teflon视为非金属
  surf_TiO2->SetFinish(groundfrontpainted);  // 漫反射表面处理
  surf_TiO2->SetModel(unified);              // 使用统一模型
  surf_TiO2->SetMaterialPropertiesTable(MyMaterials::TiO2());
  // surf_TiO2->SetSigmaAlpha(); // 表面粗糙度的贡献

  return surf_TiO2;
}
G4OpticalSurface *MyMaterials::surf_GapToClearCrystal()
{
  // Crystal to Air gap
  G4OpticalSurface *surf_GapToClearCrystal = new G4OpticalSurface("surf_GapToClearCrystal");
  surf_GapToClearCrystal->SetType(dielectric_dielectric);
  surf_GapToClearCrystal->SetFinish(polished);
  surf_GapToClearCrystal->SetModel(unified);
  surf_GapToClearCrystal->SetMaterialPropertiesTable(MyMaterials::clear_fiber_optical());

  return surf_GapToClearCrystal;
}

G4OpticalSurface *MyMaterials::surf_GlassToPhotocathode()
{
  // crystal入射窗到光阴极表面的反射率
  G4OpticalSurface *surf_GlassToPhotocathode = new G4OpticalSurface("surf_GapToClearCrystal");
  surf_GlassToPhotocathode->SetType(dielectric_metal);
  surf_GlassToPhotocathode->SetFinish(polished);
  surf_GlassToPhotocathode->SetModel(unified);

  const G4int num = 2;
  G4double reflectivity[num] = {0.095, 0.095};       // 30% 的反射率
  G4double photonEnergy[num] = {1.2 * eV, 5.7 * eV}; // 光子能量范围
  G4double TransmittanceVector[num] = {0.905, 0.905};

  G4MaterialPropertiesTable *Photocat_mpt = new G4MaterialPropertiesTable();
  Photocat_mpt->AddProperty("REFLECTIVITY", photonEnergy, reflectivity, num);
  Photocat_mpt->AddProperty("TRANSMITTANCE", photonEnergy, TransmittanceVector, num);

  surf_GlassToPhotocathode->SetMaterialPropertiesTable(Photocat_mpt);

  return surf_GlassToPhotocathode;
}

G4double MyMaterials::CalculateSellmeier(int size, G4double indexZero, G4double *nVec, G4double *lVec, G4double wavelength)
{
  /*------http://gentitfx.fr/SLitrani/code/SLitraniCode/TLitSellmeier.html----*/

  double partial = indexZero * indexZero;
  double sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += nVec[i] * nVec[i] / (1 - lVec[i] * lVec[i] / (wavelength * wavelength));
  }

  partial += sum;
  partial += 1;

  // G4cout << "Wavelength: " << wavelength << " -> rifr. index: " << sqrt(partial) << G4endl;

  return sqrt(partial);
}

G4double MyMaterials::fromEvToNm(G4double energy)
{
  return 1239.84187 / energy;
}

G4double MyMaterials::fromNmToEv(G4double wavelength)
{
  return 1239.84187 / wavelength;
}
