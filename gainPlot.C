#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"

void gainPlot(const char *file = "test.txt")
{

  TString nameTxt(file);
  nameTxt.ReplaceAll(".txt","");
  TString SN = nameTxt;
  cout<< "SN: " << SN << endl;

  TF1 *f = new TF1("f", "TMath::Power(x/[0],[1])");
  f->SetParameters(1300,12);
  f->SetParLimits(0,100,10000);
  f->SetParLimits(1,1,100);
  f->SetLineColor(kRed);

  TGraphErrors *gr = new TGraphErrors(file);
  gr->SetTitle("Gain plot: "+SN);
  gr->Fit(f,"","",1300,2400);
  gr->SetMarkerStyle(kFullCircle);
  gr->GetXaxis()->SetTitle("HV (Volts)");
  gr->GetYaxis()->SetTitle("MIP mean amplitude (Volts)");

  TCanvas *c1 = new TCanvas("c1","canvas",1200, 800);
  c1-> SetLogy();
  gr->Draw("AP");
}
