#include <stdio.h>
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"


void readCSV_v1(const char *file = "Bottom/200mv/TimeFDDA-bottom-200mv.csv")
{
   // Simplified version of cernbuild.C.
   // This macro to read data from an ascii file and
   // create a root file with a TTree

   Int_t    bin;
   Float_t  ch[12];
   Bool_t PRINT = false;

   FILE *fp = fopen(file,"r");

   char line[80];

   Int_t counter = 0;
   Int_t binMax = 2047;
   Int_t binMin = -2048;
   Int_t hBining = binMax - binMin +1;

   TH1F *hx = new TH1F("hx", "h title", hBining, binMin, binMax);

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

      Float_t number = ch[0];
      hx->Fill(bin, number);

      if(ch[0]){
       Double_t error = 1./sqrt(number);
       hx->SetBinError(counter,error);
       cout << "bin:"<< bin <<  " "<< number << " "<< error << endl;
     }
     counter++;
   }


            TCanvas *c0 = new TCanvas("c0", "histo", 800,800);
            c0 -> SetLogy();
            hx->Draw("");


   fclose(fp);

}
