#include "TGraph.h"
#include "TCanvas.h"
#include "TH1.h"

void plotHisto_MultiFit(const char * file = "run-2/1800v/F8--FDD_1--00003.txt")
{
   TGraph *plot = new TGraph(file,"%lg %lg");
   Int_t n = plot->GetN();
   Double_t min = plot->GetPointX(0);
   Double_t max = plot->GetPointX(n-1);

   cout<< "Entries= " << n << endl;
   cout<< "Min = " << min << endl;
   cout<< "Max = " << max << endl;

   TH1F *h1 = new TH1F("h1", "h1 title", n, min, max);

   Int_t nPoints = plot->GetN(); // number of points in your TGraph
   for(int i=0; i < nPoints; ++i) {
      double x,y;
      plot->GetPoint(i, x, y);
      h1->Fill(x,y); // ?
      if(y!=0)
      h1->SetBinError(i,1./sqrt(y));
   }
   h1->Rebin(4);


       Double_t par[11];
       TF1 *g1    = new TF1("g1","gaus",0,0.015);
       TF1 *g2    = new TF1("g2","expo",0.015,0.05);
       TF1 *g3    = new TF1("g3","gaus",0.05,0.14);
       TF1 *totalFit = new TF1("total","gaus(0)+expo(3)+gaus(5)",0,0.15);
       totalFit->SetLineColor(kOrange-2);

       h1->Fit(g1,"R");
       h1->Fit(g2,"R+");
       h1->Fit(g3,"R+");
       g1->GetParameters(&par[0]);
       g2->GetParameters(&par[3]);
       g3->GetParameters(&par[5]);

       totalFit->SetParameters(par);
       totalFit->SetLineStyle(9);
       h1->Fit(totalFit,"R+");

      TCanvas *c1 = new TCanvas("c1","plot", 800, 800);
      plot->Draw("AL*");

      TCanvas *c2 = new TCanvas("c2","histo", 800, 800);
      c2 -> SetLogy();
      h1->Draw("");
}
