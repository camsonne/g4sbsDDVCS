
#ifndef G4SBSPrimaryGeneratorAction_h
#define G4SBSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4String.hh"

class G4ParticleGun;
class G4Event;
class G4SBSEventGen;
class G4SBSIO;
class G4String;

class G4SBSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    G4SBSPrimaryGeneratorAction();
    ~G4SBSPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);
    G4ParticleGun* GetParticleGun();
    void SetIO( G4SBSIO *io ){ fIO = io; }
  void SetPairPart ( G4String part ) {fPairPart=part; }
     G4SBSEventGen *GetEvGen(){ return sbsgen; }

    void SetUseGeantino(bool b){ fUseGeantino = b; }

  private:
    G4ParticleGun* particleGun;
    G4SBSEventGen* sbsgen;

    G4SBSIO *fIO;
  G4String fPairPart;
    bool fUseGeantino;
};

#endif


