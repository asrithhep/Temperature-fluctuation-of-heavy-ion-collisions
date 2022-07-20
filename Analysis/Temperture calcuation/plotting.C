#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include <stdio.h>
#include <cstring>
#include "TLatex.h"


void plotting(){
  Double_t pi = TMath::Pi();
  TH2D* plot = new TH2D("histogram", "temperature in eta-phi phase space",
			10, -.5,.5 , 10, -3.14,3.14);
        plot->SetTitle("");
        plot->GetYaxis()->SetTitle("#phi (azimuthal angle)"); 
   	plot->GetXaxis()->CenterTitle();
   	plot->GetXaxis()->SetNdivisions(5);
        plot->GetXaxis()->SetTitle("#eta (rapidity)"); 
   	plot->GetYaxis()->CenterTitle();
        plot->GetYaxis()->SetNdivisions(5);
        plot->GetZaxis()->SetTitle("Temperature in GeV");
        plot->GetZaxis()->CenterTitle(); 
        plot->GetZaxis()->SetNdivisions(10);
        plot->GetYaxis()->SetTitleOffset(.8);
        plot->GetXaxis()->SetTitleOffset(1.);
        plot->GetZaxis()->SetTitleOffset(1.);
        plot->GetYaxis()->SetTitleSize(.045);
        plot->GetXaxis()->SetTitleSize(.045);
        
    TH2D* plot1 = new TH2D("histogram1", "number in eta-phi phase space",
			10, -.5,.5 , 10, -3.14,3.14);
        plot1->SetTitle("Temperature fluctuation perbin(GeV )");
        plot1->GetYaxis()->SetTitle("#phi (azimuthal angle)"); 
   	plot1->GetXaxis()->CenterTitle();
   	plot1->GetXaxis()->SetNdivisions(5);
        plot1->GetXaxis()->SetTitle("#eta (rapidity)"); 
   	plot1->GetYaxis()->CenterTitle();
        plot1->GetYaxis()->SetNdivisions(5);
        plot1->GetZaxis()->SetTitle("temperature in MeV");
        plot1->GetZaxis()->CenterTitle(); 
        plot1->GetZaxis()->SetNdivisions(10);
        plot1->GetYaxis()->SetTitleSize(.035);
        plot1->GetXaxis()->SetTitleSize(.045);

    float a;
    vector<double>sig;
    ifstream myfile;
    myfile.open("temp_det.txt");
    while(myfile >> a){
    sig.push_back(a);}
    myfile.close();
double sum=0;
for (int i =0 ;i< 100 ;i++){
     sum =sum+sig[i];
     }
double avg= sum /100     ;    



    for (int k=0;k<10;k++){
         for (int l=0;l<10 ; l++){
              cout <<sig[(10*k)+l]<< endl;
              plot->SetBinContent(k+1, l+1,sig[(10*l)+k]);
         }
    }
    /*
   TCanvas * c1 = new TCanvas("c1","c1",1000,10,10000,1000);
     c1->SetGrid();
      c1->Divide(2,1);
       c1->cd(1);
      

  

  plot->Draw("SURF3");

c1->cd(2);
plot1->Draw("SURF3");
*/
  gStyle->SetOptStat(0);
  TCanvas * c3 = new TCanvas();
    plot->Draw("COL Text");
}





