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

  TLegend* legend = new TLegend(0.12,0.7,0.46,0.8);
   legend->SetHeader("Amplitude = HV^{p1}/p0"); // option "C" allows to center the header
   legend->AddEntry(f,TString::Format("p0 = %.3e", f->GetParameter(0)),"l");
   legend->AddEntry(f,TString::Format("p1 = %.3e",f->GetParameter(1)),"l");
   legend->SetLineColor(0);
   legend->Draw();
}
