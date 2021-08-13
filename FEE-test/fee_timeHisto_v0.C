#include <stdio.h>
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TString.h"


void fee_timeHisto_v0(const char *file = "Bottom/200mv/TimeFDDA-bottom-200mv.csv")
{
   // Simplified version of cernbuild.C.
   // This macro to read data from an ascii file and
   // create a root file with a TTree

   Int_t    bin;
   Int_t    counter=0;
   Float_t  ch[12];
   Bool_t PRINT = false;
   const Int_t NHISTO = 12;

   FILE *fp = fopen(file,"r");

   char line[80];

   Int_t binMax = 2047;
   Int_t binMin = -2048;
   Int_t hBining = binMax - binMin +1;


   TH1F *h[NHISTO];
    for (Int_t i = 0; i < NHISTO; i++) {
      h[i] = new TH1F(Form("h%d",i), Form("Ch%d Time; TDC time;Counts",i), hBining, binMin, binMax);
      h[i]->SetMarkerStyle(kOpenCircle);
      h[i]->SetMarkerColor(kBlue);
      h[i]->SetMarkerSize(0.5);
    }


   while (fgets(line,80,fp)) {
      sscanf(&line[0],"%i:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f",
      &bin,&ch[0],&ch[1],&ch[2],&ch[3],&ch[4],&ch[5],&ch[6],&ch[7],&ch[8],&ch[9],&ch[10],&ch[11]);

      if(PRINT)
      {
        cout<<" bin "<< bin ;
        cout << "\033[;32m"<< ": "<< ch[0]<<"\033[0m";
        cout << "\033[;31m"<< ": "<< ch[1]<<"\033[0m";
        cout << "\033[;32m"<< ": "<< ch[2]<<"\033[0m";
        cout << "\033[;31m"<< ": "<< ch[3]<<"\033[0m";
        cout << "\033[;32m"<< ": "<< ch[4]<<"\033[0m";
        cout << "\033[;31m"<< ": "<< ch[5]<<"\033[0m";
        cout << "\033[;32m"<< ": "<< ch[6]<<"\033[0m";
        cout << "\033[;31m"<< ": "<< ch[7]<<"\033[0m";
        cout << "\033[;32m"<< ": "<< ch[8]<<"\033[0m";
        cout << "\033[;31m"<< ": "<< ch[9]<<"\033[0m";
        cout << "\033[;32m"<< ": "<< ch[10]<<"\033[0m";
        cout << "\033[;31m"<< ": "<< ch[11]<<"\033[0m";
        cout << endl;
      }

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
  for (Int_t i = 0; i < NHISTO; i++) {
    cHisto->cd(i+1);
    cHisto->cd(i+1)->SetLogy();
    h[i]->Draw();
  }

   fclose(fp);

}
