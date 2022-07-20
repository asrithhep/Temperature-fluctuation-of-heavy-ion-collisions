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


void pt(){
  
  
  Double_t pi = TMath::Pi();

  ifstream in_stream;
  in_stream.open("chain.txt");
  
  if(in_stream.fail()) {    
    cout << "Input file opening failed" << endl;
  }
  char inFile[1000];
  
  TChain *chain = new TChain("tree1");// opening tree
  
  while(in_stream >> inFile){
    chain->Add(inFile);
  }  
  
  Int_t kTr = 600000;
  Int_t kTr1 = chain->GetEntries();
  
  TBranch *b_fNtrack; 
  TBranch *b_feta;
  TBranch *b_fphi;
  TBranch *b_fPt;
 
  Int_t fNtrack;
  Float_t fPt[kTr];
  Float_t feta[kTr];
  Float_t fphi[kTr];
  chain->SetBranchAddress("fNtrack",&fNtrack, &b_fNtrack); 
  chain->SetBranchAddress("fPt", fPt, &b_fPt);
  chain->SetBranchAddress("feta", feta, &b_feta);
  chain->SetBranchAddress("fphi", fphi, &b_fphi );

  //variables
  Double_t pt,eta,phi;
  
  
  

  
  const Int_t eta_Nbins = 10;
  Double_t eta_Edges[eta_Nbins+1]={-.5,-.4,-.3,-.2,-.1,0,.1,.2,.3,.4,.5};
  
  
  const Int_t phi_Nbins = 10;
  Double_t phi_Edges[phi_Nbins+1]={ 
    -3.1415 ,-2.5132 ,-1.8849 ,-1.2566 ,-.6283 ,0 ,0.6283, 1.2566, 1.8849, 2.5132,3.1415};
  
  // histogram initialising 
  TH1F *h[10][10];
  
  for (int k=0;k<10;k++){
    for (int l=0;l<10 ; l++){
      h[k][l] =new TH1F(Form("hPtBin%d",(k*10)+l),
                        Form(" %2.2f < #eta < %2.2f and %3.2f < #phi < %3.2f ",
			     eta_Edges[k],eta_Edges[k+1],phi_Edges[l],phi_Edges[l+1]),36,.1,3.0);

      h[k][l]->GetXaxis()->SetTitle("p_{T} (GeV/c)"); 
      h[k][l]->GetYaxis()->SetTitle("count");
      h[k][l]->GetXaxis()->CenterTitle();
      h[k][l]->GetYaxis()->CenterTitle();
      h[k][l]->SetTickLength(0.02,"x"); 
      h[k][l]->SetTickLength(0.02,"y"); 
      h[k][l]->SetTitleOffset(1.30,"y");  
      h[k][l]->SetTitleOffset(1.1,"x");
      h[k][l]->SetMarkerStyle(2);
      h[k][l]->SetMarkerColor(kRed);  
      h[k][l]->SetMarkerSize(2.6);
    }
  }
  


  TH1D *heta= new TH1D("heta","eta_bin", eta_Nbins,eta_Edges);
  TH1D *hphi=new TH1D("hphi","phi_bin",phi_Nbins,phi_Edges);

  TH1D *hCounter = new TH1D("hCounter", "", 100,0.5, 100.5);
  
  // finding pt,eta , phi for all particle
  
  for(Int_t i = 0; i < kTr1;i++){
    chain->GetEntry(i);
    for(Int_t j = 0;j < fNtrack; j++){
     
      pt =fPt[j];                         // Pt calculating
eta=feta[j]; 
phi =fphi[j]; 
      if (pt < 0.1 || pt > 3.0) continue;
       
      // binning and filling 
      
      int ieta=(heta->FindBin(eta));
      int iphi=(hphi->FindBin(phi));
      if (ieta < 1 || ieta > 10 ) continue;
      if (iphi<1 || iphi >10 ) continue;

      hCounter->Fill(11);

      hCounter->Fill(21+2*ieta);

      hCounter->Fill(51+2*iphi);
      

      
      h[ieta-1][iphi-1]->Fill(pt); // histogram filling
    }                                                                // particle loop closing
  }                                                                     // event loop closing

  //saving histogram to root file
  
  TFile *file = new TFile("Pt-histograms1.root","recreate");
  file->cd();
  hCounter->Write();
  for (int k=0;k<10;k++){
    for (int l=0;l<10 ; l++){ 
        h[k][l]->Write();
    }
  }
  
  file->Close();
  
}                                                                         //closing the document

