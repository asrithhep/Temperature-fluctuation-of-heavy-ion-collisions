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

void normalization(){
Double_t pi = TMath::Pi();

  
  const Int_t eta_Nbins = 10;
  Double_t eta_Edges[eta_Nbins+1]={-.5,-.4,-.3,-.2,-.1,0,.1,.2,.3,.4,.5};
  TH1D* eta__ = new TH1D("heta", "heta",eta_Nbins,eta_Edges);
   TFile *hpt = TFile::Open("Pt-histograms.root");
   TH1F *h1[10][10];
   TH1D *eta[36];
   TH1D *phi[36];
   hpt->ls();
   TH1D *hCounter ;
   hCounter= (TH1D*)hpt->Get("hCounter");
   Double_t event_N= hCounter->GetBinContent(3);
   
   TH2D* heta = (TH2D*)hpt->Get("heta_pt");
   TH2D* hphi = (TH2D*)hpt->Get("hphi_pt");
   TH1D* eta_ = (TH1D*)hpt->Get("heta");
   TH1D* phi_ = (TH1D*)hpt->Get("hphi");
   
/*   for  (int i =0; i<34; i++){
        for  (int j =0; j<10; j++){ 
              eta[i]= (TH1D*)eta_->Clone("eta");
              phi[i]= (TH1D*)phi_->Clone("phi");
              eta[i]->Reset();
              phi[i]->Reset();
              double x= heta->GetBinContent(j,i);
              double y= hphi->GetBinContent(j,i);
              eta[i]->SetBinContent(j,x);
              phi[i]->SetBinContent(j,y);
              eta[i]->Scale((1.0/event_N));  
              phi[i]->Scale((1.0/event_N));
        }
   }         
 */             


        for  (int j =0; j<10; j++){ 
              eta[1]= (TH1D*)eta_->Clone("eta");
              eta[1]->Reset();
              double x= heta->GetBinContent(j,1);
              eta__->SetBinContent(j,1);
              
            double y= eta__->GetBinContent(j);
             eta__->Scale((1.0/event_N));    
              cout << y <<endl;
        }
   
 
  TFile *file = new TFile("Pt_normalized_histograms.root","recreate");
  file->cd();   
  hCounter->Write();
  

             // bin width normalization  
                for (int i=0 ;i <= 10;i++) {          //average pt scaling
                eta[1]= (TH1D*)eta_->Clone("eta");
                //eta[1]->Reset();
                    double x= heta->GetBinContent(i,1);
                    eta[1]->SetBinContent(i,x);
                   }


  /*
  

      for (int k=0;k<10;k++){
           for (int l=0;l<10 ; l++){  
                TH1F* h = (TH1F*)hpt->Get(Form("hPtBin%d",(k*10)+l));
                h1[k][l] = (TH1F*)h->Clone("temp");
		h1[k][l]->Reset();
		h1[k][l]->SetName(Form("hPtNormBin%d",(k*10)+l));
		h1[k][l]->GetYaxis()->SetTitle(
                  "#frac{1}{2#pi N}#frac{d^{3}N}{p_{T}dp_{T}d#eta d#phi} (GeV/c)^{-2}");
               

                // normalization
                
                Double_t delta_phi = 0.6283;                               //-3.1415 to -3.1415 phi divided to 10 bin
                h->Scale((1.0/delta_phi));                                // phi normalization
                
                Double_t delta_eta = 0.1;                                  //-0.5 to 0.5 eta divided to 10 bin
                h->Scale((1.0/delta_eta));                                // eta normalization
                
                Double_t event_N= hCounter->GetBinContent(3);	    //event number normalization
                h->Scale((1.0/event_N));           
                h->Scale((1.0/(2.0*pi)));                                // 2pi costant normalization
                
                //h[k][l]->Scale(1.0,"width");                           // bin width normalization  
                for (int i=0 ;i <= h1[k][l]->GetNbinsX();i++) {          //average pt scaling
                    Double_t c = h->GetBinCenter(i+1);
                    Double_t w = h->GetBinWidth(i+1);
                    Double_t pt= h->GetBinContent(i+1);
                    double x= heta->GetBinContent(i,1);
                    h1[k][l]->SetBinContent(i+1,(pt/(w*c)));
                    eta__->SetBinContent(i,x);
                   }

  
  h1[k][l]->Write();
               }

          }
*/
  file->Close();
 eta[1]-> Draw();

//cout << event_N <<"-"<<  x<< endl;
     } 
