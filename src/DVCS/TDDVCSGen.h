#include <TLorentzVector.h>
#include <TLorentzRotation.h>
#include <TRandom3.h>
#include <TString.h>
#include <iostream>
#ifndef _TDDVCSGEN_
#define _TDDVCSGEN_




/*
Root Vector3 angle :
phi angle betweeb x and y in XY plane
theta angle between Z and Y ( equal to pi/2 to be in XY plane ) 
beam along y axis usually
z anti gravity
 */

using namespace std;

/* class T3DArrow : public TPolyLine3D */
/* { */
/*  public: */
/*   T3DArrow(); */
/*   ~T3DArrow(); */
/*   void Draw(); */
/*   void SetBegin(Double_t x,Double_t y,Double_t z); */
/*   void SetEnd(Double_t x,Double_t y,Double_t z); */

/* } */
/* ; */
class TGenPart:public TRandom3
{
 public:
 TGenPart(TLorentzVector * lv):TRandom3()
    {
      fLorVect=lv;
      fThMin=-10;
      fThMax=10;
      fPhMin=-10;
      fPhMax=10;
      fEMin=0;
      fEMax=11;
      fMass=0;
    }
 TGenPart():TRandom3()
    {
      fLorVect=0;
      fThMin=25;
      fThMax=35;
      fPhMin=-10;
      fPhMax=10;
      fEMin=0;
      fEMax=11;
      fMass=0;
    }
~TGenPart()
  {

  }
 void Generate();
 void Generate(Double_t Emin,Double_t Emax);
 void GenerateDir(TVector3 dir);

  Double_t SetThMin(Double_t v) 
  {
    fThMin=v;
  }
  Double_t SetThMax(Double_t v) {
    fThMax=v;
  }
  Double_t SetPhiMin(Double_t v) {
    fPhMin=v;
  }
  Double_t SetPhiMax(Double_t v) {
    fPhMax=v;
  }
  Double_t SetEMin(Double_t v) {
    fEMin=v;
  }
  Double_t SetEMax(Double_t v) {
    fEMax=v;
  }

   Double_t SetMass(Double_t v) {
    fMass=v;
  }
   void Print();
   protected:
   Double_t fThMin,fThMax,fPhMin,fPhMax,fEMin,fEMax;// Degrees
   Double_t fMass;// GeV
  TLorentzVector * fLorVect;
  ClassDef(TGenPart,1)
};

class TDDVCSGen : public TObject
{

 public:
  TDDVCSGen();
  ~TDDVCSGen();
  void  GenerateDDVCS();
  void GenerateDDVCSFlat();
  TLorentzVector SetFourVect ( Double_t E, Double_t kx, Double_t  ky, Double_t kz ){TLorentzVector v(kx,ky,kz,E);return v;};
  TLorentzVector SetBeam(TLorentzVector & v );
  TLorentzVector SetScattered(TLorentzVector & v);
  TLorentzVector SetBeam(Double_t px,Double_t py,Double_t pz,Double_t E );
  TLorentzVector SetBeam(Double_t E );
  TLorentzVector SetScattered(Double_t px,Double_t py,Double_t pz,Double_t E );
  void GenerateEvent();
  void GenerateScattered();
  void GenerateQ2();
  TLorentzVector Q1(){fq1 = fk-fkp; return fq1;};
  TLorentzVector Q(){fq = (fq1+fq2)*0.5; return fq;};
  TLorentzVector Delta(){fDelta =(fq2 - fq1); return fDelta;}
  TLorentzVector Deltap(){fDelta =fpi -fpf; return fDelta;}
  TLorentzVector P(){fp = (fpi+fpf); return fp;};
   Double_t Xi(){return fXi;};
   Double_t Eta(){return fEta;};
  Double_t Q2() {return fQ2;}
  Double_t xbj(){return fxbj; };
  Double_t t(){return Delta().Mag2(); };
  void Compute();
  void Print();
  TString Lund();
  protected:
  TLorentzVector fk,fkp,fpi,fpf,fp,fq1,fq2,fq,fL1,fL2,fL1CM,fL2CM,fDelta;
  TGenPart  * fGkp, * fGq2, * fGL1;
  Double_t fDThetaE,fDPhiE,fDPE;
  Double_t fDThetaQ2,fDPhiQ2;
  Double_t fQ2,fxbj,fEta,fXi;
  Double_t fAngle;
  Double_t fMTarg;
  ClassDef (TDDVCSGen,1);
}
;
#endif

 TString Lund(TLorentzVector * v)
 {
   //return momentum in text Lund Format
   TString output="";
   output+= v->Px();
   output+=" ";
   output+= v->Py();
   output+=" ";
   output+= v->Pz();
   output+=" ";
   output+= v->E();
   output+=" ";
   return output;
 }
