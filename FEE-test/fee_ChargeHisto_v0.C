#include <stdio.h>
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TString.h"
#include "THStack.h"


void fee_ChargeHisto_v0(const char *file = "Bottom/200mv/AmpFDDA-botton-200mv.csv")
{

   Int_t    bin;
   Int_t    counter=0;
   Bool_t PRINT = true;
   Int_t NHISTO = 24;
   Float_t  ch[24];

   FILE *fp = fopen(file,"r");

   char line[200];

   Int_t binMax = 4096;
   Int_t binMin = -256;
   Int_t hBining = binMax - binMin +1;


   TH1F *h[NHISTO];
    for (Int_t i = 0; i < NHISTO; i++) {
      h[i] = new TH1F(Form("h%d",i), Form("Ch%d Charge;ADC charge;Counts",i), hBining, binMin, binMax);
    }

    THStack *hs[NHISTO];
    for (Int_t i = 0; i < 12; i++) {
      hs[i] = new THStack(Form("hs%d",i),Form("Ch%d;ADC Charge;Counts",i));
    }

//bin:C01A0:C01A1:C02A0:C02A1:C03A0:C03A1:C04A0:C04A1:C05A0:C05A1:C06A0:C06A1:C07A0:C07A1:C08A0:C08A1:C09A0:C09A1:C10A0:C10A1:C11A0:C11A1:C12A0:C12A1

   while (fgets(line,200,fp)) {
      sscanf(&line[0],"%i:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f",
      &bin,&ch[0],&ch[1],&ch[2],&ch[3],&ch[4],&ch[5],&ch[6],&ch[7],&ch[8],&ch[9],&ch[10],&ch[11],
    &ch[12],&ch[13],&ch[14],&ch[15],&ch[16],&ch[17],&ch[18],&ch[19],&ch[20],&ch[21],&ch[22],&ch[23]);


      for (Int_t i = 0; i < NHISTO; i++) {
        h[i]->Fill(bin,ch[i]);
        if(ch[i]){
           Double_t error = 1./sqrt(ch[i]);
           h[i]->SetBinError(counter,error);
         }
      }
      counter++;
   }


  TCanvas *cHisto = new TCanvas("cHisto", "FEE time", 1200,900);
  cHisto->Divide(4,3);

  TCanvas *cHisto2 = new TCanvas("cHisto2", "FEE time", 1200,900);
  cHisto2->Divide(4,3);

  Int_t nHisto = 0;
  for (Int_t i = 0; i < 12; i++) {
    cHisto->cd(i+1);
    cHisto->cd(i+1)->SetLogy();
    h[nHisto]->SetMarkerStyle(kOpenCircle);
    h[nHisto]->SetMarkerColor(kBlue);
    h[nHisto]->SetMarkerSize(0.5);
    h[nHisto]->Draw("SAME");

    h[nHisto+1]->SetMarkerStyle(kFullCircle);
    h[nHisto+1]->SetMarkerColor(kRed);
    h[nHisto+1]->SetMarkerSize(0.5);
    h[nHisto+1]->Draw("SAME");


    cHisto2->cd(i+1);
    //cHisto2->cd(i+1)->SetLogy();
    hs[i]->Add(h[nHisto]);
    hs[i]->Add(h[nHisto+1]);
    //hs[i]->Draw("nostack");
    hs[i]->Draw("");

    nHisto+=2;


  }


   fclose(fp);

}
