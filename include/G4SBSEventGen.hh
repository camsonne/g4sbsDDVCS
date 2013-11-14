#ifndef G4SBSEVENTGEN_HH
#define G4SBSEVENTGEN_HH

#include "globals.hh"
#include "sbstypes.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/RandGauss.h"
#include "G4SBSIO.hh"
#include "G4String.hh"

#define MAXMOMPT 1000 // N points for targets momentum distribution interpolations

class G4SBSEventGen {
public:
  G4SBSEventGen();
  ~G4SBSEventGen();
  
  double GetBeamE(){ return fBeamE; }
  G4ThreeVector GetBeamP(){ return fBeamP; }
  
  G4ThreeVector GetV(){ return fVert; }
  
  double GetElectronE(){ return fElectronE; }
  double GetNucleonE(){ return fNucleonE; }
  G4ThreeVector GetElectronP(){ return fElectronP; }
  G4ThreeVector GetNucleonP(){ return fNucleonP; }
  G4LorentzVector GetQP(){return fQP;}
  G4LorentzVector GetQM(){return fQM;}
  Nucl_t GetNucleonType(){ return fNuclType; }
  Nucl_t GetFinalNucleon(){ return fFinalNucl; }
  
  void GenerateEvent();
  
	ev_t GetEventData();
  
  void SetNevents(int n){fNevt = n;}
  void SetBeamCur(double c){fBeamCur = c;}
  void SetBeamE(double c){fBeamE= c; fBeamP = G4ThreeVector(0.0, 0.0, c); }
  void SetRunTime(double t){fRunTime = t;}
  
	void SetKine(Kine_t t ){fKineType = t;}
	Kine_t GetKine(){return fKineType;}

	void SetTarget(Targ_t t ){fTargType = t;}
	void SetTargLen(double len){fTargLen = len;}
	void SetTargDen(double den){fTargDen = den;}

	void SetRasterX(double v){fRasterX = v;}
	void SetRasterY(double v){fRasterY = v;}

	void SetThMin(double v){fThMin = v;}
	void SetThMax(double v){fThMax = v;}
	void SetPhMin(double v){fPhMin = v;}
	void SetPhMax(double v){fPhMax = v;}
        void SetPairE(double v){fPairE = v;}
        void SetQprime2(double v){fQPrime2 = v;}
        void SetPairPart(G4String v){fPairPart = v;}
        void SetPairCAngle(double v){fPairCAngle = v;}
        void SetPairRotAngle(double v){fPairRotAngle = v;}
        void SetPairPhiAngle(double v){fPairPhiAngle = v;}
        G4String GetPairPart(){return fPairPart;}
        double GetPairCAngle(){return fPairCAngle;}
        double GetPairPhiAngle(){return fPairPhiAngle;}
  double GetPairRotAngle(){return fPairRotAngle;}

	void SetHCALDist(double v){ fHCALdist = v;}

	double GetHcalDist(){ return fHCALdist; }
  //	double GetBeamE(){ return fBeamE; }
  	double GetPairE(){ return fPairE; }
	double GetToFres(){ return fToFres; }
  void GeneratePair();
  void GeneratePairAcc();
    private:
  double fElectronE, fNucleonE, fBeamE, fPairE, fPairCAngle,fPairPhiAngle,fPairRotAngle;
       
	G4ThreeVector fElectronP, fNucleonP, fBeamP, fVert;
        G4LorentzVector fQM,fQP;
  double fWeight, fQ2, fW2, fxbj, fSigma, fAperp, fApar,fQPrime2;
        G4String fPairPart; 
	double fBeamCur;
	double fRunTime;
	int    fNevt;
	double Wfact;

	Nucl_t fNuclType, fFinalNucl;
	Targ_t fTargType;
	Kine_t fKineType;

	double fThMin, fThMax, fPhMin, fPhMax;
	double fTargLen, fRasterX, fRasterY, fTargDen;
	double fPmisspar, fPmissperp, fPmissparSm;
	double fHCALdist, fToFres;

	G4LorentzVector GetInitialNucl( Targ_t, Nucl_t );

	void GenerateElastic( Nucl_t, G4LorentzVector, G4LorentzVector );
	void GenerateInelastic( Nucl_t, G4LorentzVector, G4LorentzVector );
	void GenerateDIS( Nucl_t, G4LorentzVector, G4LorentzVector );
	void GenerateFlat( Nucl_t, G4LorentzVector, G4LorentzVector );
  void GeneratePairSym( double_t theta, double phi, double Qprime2, G4LorentzVector & Qm, G4LorentzVector &Qp);
  void GeneratePair( double_t theta, double phi, double E);
  void GenerateDDVCS( Nucl_t, G4LorentzVector, G4LorentzVector);
	void GenerateBeam( Nucl_t, G4LorentzVector, G4LorentzVector );

	double deutpdist( double );
	double he3pdist( Nucl_t, double );

	void LoadTargetData();
};

#endif//G4SBSEVENTGEN_HH
