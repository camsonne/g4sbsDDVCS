//#include "TDDVCSGen.C"

 TFile * out = new TFile("out.root","RECREATE");
  TTree * tree = new TTree("T","Generated events",99);

void TestKin()
{
  gROOT->ProcessLine(".L TDDVCSGen.C+");
  TVector3 ekp;
  // ekp.SetXYZ(1.32*sin(30/180.*TMath::Pi()),1.32*cos(30/180.*TMath::Pi()),0);
  ekp.SetMagThetaPhi(1.32,TMath::Pi()/2,(90-30)/180.*TMath::Pi());
  // ekp.RotateX(90/180.*TMath::Pi());
  TDDVCSGen *a = new TDDVCSGen();
  TLorentzVector Fkp;
  Fkp.SetVectM(ekp,0);
  // a.SetBeam(0,11,0,11);
  a->SetBeam(11);
  a->SetScattered(Fkp);
  a->Compute();
  cout<<a->Q2()<<" "<<a->xbj()<<endl;
  cout<<4*1.32*11*sin(15/180.*TMath::Pi())*sin(15/180.*TMath::Pi())<<" "<<4*1.32*11*sin(15/180.*TMath::Pi())*sin(15/180.*TMath::Pi())/(2*0.938*(11-1.32))<<endl;
  a->GenerateDDVCS();
  a->Print();
  tree->Branch("ddvcs",a,32000,99);
  for ( int i = 0 ; i< 10000 ; i++)
    {
       a->GenerateDDVCS();
       tree->Fill();
       if (i%1000==0) cout<<i<<endl;
    }
  tree->Write("T");
  // out->Close();
}
