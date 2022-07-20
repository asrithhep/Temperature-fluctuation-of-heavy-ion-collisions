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
  [23, 24, 57, 59, 60, 65, 71, 75, 78, 80, 99]
  TH2D* plot = new TH2D("histogram", "temperature in eta-phi phase space",
			10, -.5,.5 , 10, -3.14,3.14);
        plot->SetTitle("Temperature fluctuation perbin(GeV )");
        plot->GetYaxis()->SetTitle("#phi(azimuthal angle)"); 
   	plot->GetXaxis()->CenterTitle();
   	plot->GetXaxis()->SetNdivisions(5);
        plot->GetXaxis()->SetTitle("#eta(rapidity)"); 
   	plot->GetYaxis()->CenterTitle();
        plot->GetYaxis()->SetNdivisions(5);
        plot->GetZaxis()->SetTitle("temperature in MeV");
        plot->GetZaxis()->CenterTitle(); 
        plot->GetZaxis()->SetNdivisions(10);
        
    TH2D* plot1 = new TH2D("histogram1", "number in eta-phi phase space",
			10, -.5,.5 , 10, -3.14,3.14);
        plot1->SetTitle("Temperature fluctuation perbin(GeV )");
        plot1->GetYaxis()->SetTitle("#phi(azimuthal angle)"); 
   	plot1->GetXaxis()->CenterTitle();
   	plot1->GetXaxis()->SetNdivisions(5);
        plot1->GetXaxis()->SetTitle("#eta(rapidity)"); 
   	plot1->GetYaxis()->CenterTitle();
        plot1->GetYaxis()->SetNdivisions(5);
        plot1->GetZaxis()->SetTitle("temperature in MeV");
        plot1->GetZaxis()->CenterTitle(); 
        plot1->GetZaxis()->SetNdivisions(10);

    float a;
    float b;
    vector<double>sig;
    vector<double>sig1;
    ifstream myfile;
    ifstream myfile1;
    myfile.open("temperature.txt");
    myfile1.open("temperature1.txt");
    while(myfile >> a){
    sig.push_back(a);}
    while(myfile1 >> b){
    sig1.push_back(b);}
    myfile.close();
    myfile1.close();
double sum=0;
for (int i =0 ;i< 100 ;i++){
     sum =sum+sig[i];
     }
double avg= sum /100     ;    



    for (int k=0;k<10;k++){
         for (int l=0;l<10 ; l++){
              plot->SetBinContent(k+1, l+1,sig[(10*k)+l]);
              plot1->SetBinContent(k+1, l+1,sig[(10*k)+l]/sig1[(10*k)+l]);
         }
    }
   TCanvas * c1 = new TCanvas("c1","c1",1000,10,10000,1000);
     c1->SetGrid();
      c1->Divide(2,1);
       c1->cd(1);
       
  //TCanvas * c3 = new TCanvas();
  gStyle->SetOptStat(0);
  plot->Draw("SURF3");

c1->cd(2);
plot1->Draw("SURF3");
}





