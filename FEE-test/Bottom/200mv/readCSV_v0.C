#include <stdio.h>
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"


void readCSV_v0()
{
   // Simplified version of cernbuild.C.
   // This macro to read data from an ascii file and
   // create a root file with a TTree

   Int_t    bin;
   Float_t  ch[12];

   FILE *fp = fopen("test.csv","r");

   TFile *hfile = hfile = TFile::Open("test.root","RECREATE");

   TTree *tree = new TTree("T","CERN 1988 staff data");
   tree->Branch("bin",&bin,"bin/F");
   tree->Branch("Ch01T",&ch[0]);
   tree->Branch("Ch02T",&ch[1],"Ch02T/F");
   tree->Branch("Ch03T",&ch[2],"Ch03T/F");
   tree->Branch("Ch04T",&ch[3],"Ch04T/F");
   tree->Branch("Ch05T",&ch[4],"Ch05T/F");
   tree->Branch("Ch06T",&ch[5],"Ch06T/F");
   tree->Branch("Ch07T",&ch[6],"Ch07T/F");
   tree->Branch("Ch08T",&ch[7],"Ch08T/F");
   tree->Branch("Ch09T",&ch[8],"Ch09T/F");
   tree->Branch("Ch10T",&ch[9],"Ch10T/F");
   tree->Branch("Ch11T",&ch[10],"Ch11T/F");
   tree->Branch("Ch12T",&ch[11],"Ch12T/F");

   char line[80];

   TH1F *hx = new TH1F("hx", "h title", 2000, -2000, 2000);

   while (fgets(line,80,fp)) {
      sscanf(&line[0],"%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f",
      &bin,&ch[0],&ch[1],&ch[2],&ch[3],&ch[4],&ch[5],&ch[6],&ch[7],&ch[8],&ch[9],&ch[10],&ch[11]);
      tree->Fill();

      cout << "bin "<< bin ;
      cout << "\033[;32m"<< ": "<< ch[0]<<"\033[0m";
      cout << "\033[;31m"<< ": "<< ch[1]<<"\033[0m";
      cout << endl;
      Float_t number = ch[0];
      hx->Fill(bin,number);
   }
   tree->Print();
   tree->Write();

    TGraph *gr = new TGraph();

   Int_t entries = tree->GetEntries();
   cout << "Entries: " << entries << endl;
   Int_t k = 0;

   for (Int_t i = 950; i < 1050; i++) {
     tree->GetEntry(i);
     /*
     cout << "Entry["<<i<<"] "<< bin;
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
     */
     //hx->Fill(k,ch[0]); // ?
     gr->SetPoint(k,i,ch[0]);
     k++;
   }

      TCanvas *c1 = new TCanvas("c1", "histo", 800,800);
      gr->Draw("AL*");

            TCanvas *c0 = new TCanvas("c0", "histo", 800,800);
            c0 -> SetLogy();
            hx->Draw("");


   fclose(fp);
   delete hfile;

}
