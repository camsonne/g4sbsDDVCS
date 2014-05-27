 void pl3() {
      TCanvas *c1 = new TCanvas("c1");
      TView *view = TView::CreateView(1);
      view->SetRange(0,0,0,2,2,2);
      const Int_t n = 100;
      TPolyLine3D *l = new TPolyLine3D(n);
      for (Int_t i=0;i<n;i++) {
         Double_t x = 2*gRandom->Rndm();
         Double_t y = 2*gRandom->Rndm();
         Double_t z = 2*gRandom->Rndm();
         l->SetPoint(i,x,y,z);
      }
      l->Draw();
   }
