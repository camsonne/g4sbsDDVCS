#include <TLorentzVector.h>
#include <TRandom.h>

#ifndef _TDDVCSGEN_
#define _TDDVCSGEN_
class TDDVCSGen : public TObject
{

 public:
  TDDVCSGen();
  ~TDDVCSGen();
  void  GenerateDDVCS();
  void GenerateDDVCSFlat();
  TLorentzVector SetFourVect ( Double_t E, Double_t kx, Double_t  ky, Double_t kz ){TLorentzVector v(kx,ky,kz,E);return v;};
  TLorentzVector SetBeam();
  TLorentzVector SetScattered();
  void GenerateEvent();
  void GenerateScattered();
  void GenerateQ2();
  TLorentzVector Q(){fq = fk-fkp; return fq;};
  TLorentzVector Delta(){fDelta =(fq2 - fq1)*0.5; return fDelta;}
  TLorentzVector P(){fp = (fpi+fpf)*0.5; return fp;};
   Double_t Xi(){return fXi;};
   Double_t Eta(){return fEta;};
  Double_t Q2() {return fQ2;}
  Double_t xbj(){return fxbj; };
  void Compute();
 protected:
  TLorentzVector fk,fkp,fpi,fpf,fp,fq1,fq2,fq,fL1,fL2,fDelta;
  Double_t fDThetaE,fDPhiE,fDPE;
  Double_t fDThetaQ2,fDPhiQ2;
  Double_t fQ2,fxbj,fEta,fXi;
  ClassDef (TDDVCSGen,1);
}
;
#endif
