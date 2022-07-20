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
Double_t fitnew(Double_t *x, Double_t *par){ 
  Double_t pi = TMath::Pi();
  Double_t volume = par[0];
  Double_t temp   = par[1];
  Double_t    q   = par[2];
  int g = 1;
  
  Double_t norm = g*volume/(2.0*2.0*2.0*pi*pi*pi);
  Double_t y = q-1.0;
  Double_t m =.136 ;
  Double_t mt = sqrt(m*m+x[0]*x[0]);         
  Double_t f1 = TMath::Power((1+ (y*mt/temp)),-q/y);
  Double_t f2 = norm*mt*f1;
  
  return f2;
}

void fitting(int x,int y){

  Double_t pi = TMath::Pi();
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

  TFile *hpt = TFile::Open("Pt_normalized_histograms.root");
  TH1F *h[10][10];
  TH1D *hCounter ;
  hCounter= (TH1D*)hpt->Get("hCounter");
  TVirtualFitter::SetMaxIterations(500000);

  TF1*fit1 =new TF1("fit1", fitnew ,.10,3.0,3);  // fit defining
      fit1->SetParameter(0, 1.1000e+06);             // seting parameters
      fit1->SetParameter(1, 1.0500e-01);
      fit1->SetParameter(2, 1.06500e+00);
      //fit1->SetParLimits(0,1.0000e+06,1.2200e+06);             // seting parameters
      //fit1->SetParLimits(1, 1.0000e-01,1.1000e-01);
      //fit1->SetParLimits(2, 1.0600e+00,1.07300e+00);
            char name[100];
            sprintf(name,"hPtNormBin%d",(x*10)+y);
            h[x][y] = (TH1F*)hpt->Get(name);
            double sum=0 ;
          //  for (int i=0 ;i <= h[x][y]->GetNbinsX();i++) { 
           /* for (int i= 4;i <= 5;i++) { 
            double temp= h[x][y]->GetBinContent(i+1);
            sum = sum + temp;
            }*/
            double temp1= h[x][y]->GetBinContent(1);
            double temp2= h[x][y]->GetBinContent(2);
            double temp3= h[x][y]->GetBinContent(3);
            double temp4= h[x][y]->GetBinContent(4);
            double temp5= h[x][y]->GetBinContent(5);
            double temp6= h[x][y]->GetBinContent(6);
            double temp7= h[x][y]->GetBinContent(7);
            double temp8= h[x][y]->GetBinContent(8);
            sum=temp1/(temp5);
            //h[x][y] = (TH1F*)hpt->Get("hPtNormBin0");
            cout<<"Histogram numbers"<<x<<"\t"<<y<<endl;
            h[x][y]->Fit("fit1","R");
            double V =fit1->GetParameter(0) ;
            double T =fit1->GetParameter(1) ;
            double Q =fit1->GetParameter(2) ;
            double r = (fit1->GetChisquare()/fit1->GetNDF());   // ChiSquare 
            cout<<"==="<<  r  <<endl;
                              // filling plot
 FILE *f3= fopen("temperature.txt","a");
 FILE *f4= fopen("non-extn.txt","a");
 FILE *f5= fopen("volume.txt","a");
 FILE *f6= fopen("number.txt","a");
 /*
TFile *file = new TFile("tsallisfit.root","Update");
   file->cd();
   h[x][y]->Write();  
  file->Close();*/
fprintf(f3,"%lf \n",T);
fprintf(f4,"%lf \n",Q);
fprintf(f5,"%lf \n",V);
fprintf(f6,"%lf \n",sum);


fclose(f3);   
fclose(f4);              
fclose(f5);  
fclose(f6);  


  
} 
