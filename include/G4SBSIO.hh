#ifndef G4SBSIO_H
#define G4SBSIO_H

#include "TROOT.h"
#include "TLorentzVector.h"
#include "TObject.h"
#include "G4Run.hh"
#include "G4LorentzVector.hh"

class TFile;
class TTree;

#define MAXHITDATA 10000

typedef struct {
    Double_t thbb, thhcal, dbb, dhcal, Ebeam;
} gen_t;


typedef struct {
    Double_t count, rate, solang, sigma, W2, xbj, Q2, th, ph;
    Double_t Aperp, Apar;
    Double_t vx, vy, vz;
    Double_t ep, np;
    Double_t epx, epy, epz;
    Double_t npx, npy, npz;
    Double_t nth, nph;
    Double_t pmperp, pmpar, pmparsm;
    Int_t nucl, fnucl;
} ev_t;

typedef struct {
    Double_t x, y, xp, yp;
    Double_t tx, ty, txp, typ;
    Int_t hcal, bb, gemtr;
    Double_t hcx, hcy, bcx, bcy;
    Double_t hct, hctex;
    Double_t hclx, hcly, hclz, hcdang;
} tr_t;

typedef struct {
    Int_t ndata;
	Int_t gid[MAXHITDATA];
  	Int_t e[MAXHITDATA];
  	Int_t pid[MAXHITDATA];
	Double_t x[MAXHITDATA], y[MAXHITDATA], z[MAXHITDATA];
	Double_t dx[MAXHITDATA], dy[MAXHITDATA];
	Double_t tx[MAXHITDATA], ty[MAXHITDATA];
	Double_t txp[MAXHITDATA], typ[MAXHITDATA];
} hit_t;

typedef struct {
  Int_t hcndata, bcndata;
  Double_t bcx[MAXHITDATA], bcy[MAXHITDATA], bce[MAXHITDATA];
  Double_t hcx[MAXHITDATA], hcy[MAXHITDATA], hce[MAXHITDATA];
  Int_t hctrid[MAXHITDATA], hcmid[MAXHITDATA], hcpid[MAXHITDATA];
  Int_t bctrid[MAXHITDATA], bcmid[MAXHITDATA], bcpid[MAXHITDATA];
  Double_t etot;
} cal_t;

class G4SBSIO {
    public:
	G4SBSIO();
	~G4SBSIO();

	void SetFilename(const char *fn){strcpy(fFilename, fn);}
	void SetTrackData(tr_t td){ trdata = td; }
	void SetCalData(cal_t cd){ caldata = cd; }
  	void SetCal2Data(cal_t cd){ cal2data = cd; }
	void SetEventData(ev_t ed){ evdata = ed; }
	void SetHitData(hit_t ht){ hitdata = ht; }
        void SetPairM(G4LorentzVector qm)
  {  
      
    pairMgen.SetPx(qm.px());
      pairMgen.SetPy(qm.py());
      pairMgen.SetPz(qm.pz());
      pairMgen.SetE(qm.e());
      }
    void SetPairP(G4LorentzVector qm)
  {  
      
    pairPgen.SetPx(qm.px());
      pairPgen.SetPy(qm.py());
      pairPgen.SetPz(qm.pz());
      pairPgen.SetE(qm.e());
      }
	void FillTree();
	void WriteTree();

	void SetBeamE(double E){ gendata.Ebeam = E/GeV; }
	void SetBigBiteTheta(double th){ gendata.thbb = th; }
	void SetBigBiteDist(double d){ gendata.dbb = d/m; }
	void SetHcalTheta(double th){ gendata.thhcal = th; }
	void SetHcalDist(double d){ gendata.dhcal = d/m; }

	ev_t GetEventData(){ return evdata; }

	void InitializeTree();
    private:
	TFile *fFile;
	TTree *fTree;
        TLorentzVector pairPgen, pairMgen;
	ev_t evdata;
	gen_t gendata;
	tr_t trdata;
	cal_t caldata;
  	cal_t cal2data;
	hit_t hitdata;
  TLorentzVector fQm,fQp;
	char fFilename[255];

};

#endif//G4SBSIO_H
