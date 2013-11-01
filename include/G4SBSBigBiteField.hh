#ifndef G4SBSBigBiteField_hh
#define G4SBSBigBiteField_hh

#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4RotationMatrix.hh"

#define MAXPT 120


class G4SBSBigBiteField : public G4MagneticField {
    public:
	G4SBSBigBiteField(double, G4RotationMatrix *);
	~G4SBSBigBiteField();

	void GetFieldValue( const  double Point[3], double *Bfield ) const;

	void SetUseGeantino( G4bool b ){ fUseGeantino = b; }

	void SetOffset( double off ){ fZOffset = off; }
	void SetRM( G4RotationMatrix *rm ){ frm = rm; }

    private:
	char fFilename[255];

	int fN[3];
	double fMin[3], fMax[3];

	double fFieldVal[MAXPT][MAXPT][MAXPT][3];

	void ReadField();

	G4bool fUseGeantino;

	double fZOffset;
	G4RotationMatrix *frm;
};

#endif//G4SBSBigBiteField_hh
