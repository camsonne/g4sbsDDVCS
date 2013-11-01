#include "G4SBSCalSD.hh"
#include "G4SBSCalHit.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4Box.hh"

G4SBSCalSD::G4SBSCalSD( G4String name, G4String colname )
  : G4VSensitiveDetector(name)
{
    collectionName.insert(colname);
}

G4SBSCalSD::~G4SBSCalSD()
{
}

void G4SBSCalSD::Initialize(G4HCofThisEvent*)
{
  hitCollection = new G4SBSCalHitsCollection(SensitiveDetectorName,collectionName[0]); 
}

G4bool G4SBSCalSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  double edep = aStep->GetTotalEnergyDeposit();
//  if( edep <= 0.5*GeV ) return false;

  // Only return primary electron hits
  /*int trid = aStep->GetTrack()->GetParentID();
    if( trid != 0 ) return false; */

  G4SBSCalHit* hit = new G4SBSCalHit();

  G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();

  G4TouchableHistory* hist = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  G4AffineTransform aTrans = hist->GetHistory()->GetTransform(hist->GetHistory()->GetDepth() );
  pos = aTrans.TransformPoint(pos);

  hit->SetPos(pos);
  hit->SetLabPos(aStep->GetPreStepPoint()->GetPosition());
//  hit->SetTime(aStep->GetPreStepPoint()->GetGlobalTime());
  hit->SetTime(aStep->GetPostStepPoint()->GetLocalTime());

  hit->SetTime(aStep->GetPostStepPoint()->GetLocalTime());

  //printf("Hit with E %g\n", edep/MeV);

  hit->SetEdep(edep);
  hit->SetPID(aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
  hit->SetMID(aStep->GetTrack()->GetParentID());

  /*
  printf("%f %f %f %f - dist %f beta %e momentum %f GeV\n", 
	  aStep->GetPreStepPoint()->GetLocalTime()/ns,
	  aStep->GetPostStepPoint()->GetLocalTime()/ns,
	  aStep->GetPreStepPoint()->GetGlobalTime()/ns,
	  aStep->GetPostStepPoint()->GetGlobalTime()/ns,
	  aStep->GetPreStepPoint()->GetPosition().mag()/m,
	  aStep->GetPreStepPoint()->GetPosition().mag()/aStep->GetPreStepPoint()->GetLocalTime()/(0.299792458*m/ns),
//aStep->GetTrack()->GetTotalEnergy()/GeV
	  edep/GeV
	  );
	  */

  hitCollection->insert( hit );

  return true;
}

void G4SBSCalSD::EndOfEvent(G4HCofThisEvent*HCE)
{
    G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    HCE->AddHitsCollection( HCID, hitCollection );
}

void G4SBSCalSD::clear()
{
} 

void G4SBSCalSD::DrawAll()
{
} 

void G4SBSCalSD::PrintAll()
{
} 
