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

void synthetic_data_generator(int x){






TFile *f = new TFile(Form("/home/dataa/Tsallis1/anomaly/1/%d/Sythetic_dat.root",x) , "RECREATE" );
TTree *tree2 = new TTree( "tree2" ,"simple tree");
Float_t fPt[600000],feta[600000],fphi[600000];
int fNtrack;
tree2->Branch("fNtrack",&fNtrack,"fNtrack/I");
tree2->Branch("fPt",fPt,"fPt[fNtrack]/F");
tree2->Branch("feta",feta,"feta[fNtrack]/F");
tree2->Branch("fphi",fphi,"fphi[fNtrack]/F");

vector<double>k[3];
for(unsigned int i =(x*100) ;i< ((x+1)*100); i++){
k[0].clear();
k[1].clear();
k[2].clear();
//502450
for(Int_t j = 0;j < 2000; j++){
TRandom m;
m.SetSeed (11*2000*i+j);

TF1 *f1 = new TF1("f1","(1*7.62214e+06/(2.0*2.0*2.0*TMath::Pi()*TMath::Pi()*TMath::Pi()))*sqrt( (.139*.139)+(x *x) )*TMath::Power((1+ ((1.06629e+00-1)*sqrt( (.139*.139)+(x *x) )/1.1052e-01 )),-1.06629e+00/(1.06629e+00-1))",0.0,5.0);
gRandom->SetSeed(2000*i+j);
double pt = f1->GetRandom();
double eta= m.Uniform(-.3,-.2);
double phi= m.Uniform( 2.5132,3.1415);
//cout <<pt <<"-"<<phi<<"-"<< eta << endl;
k[0].push_back(pt);
k[1].push_back(eta);
k[2].push_back(phi);

}
fNtrack =2000;
for(unsigned int  a =0 ;a < k[0].size(); a++){  fPt[a] = k[0][a];   }
for(unsigned int  a =0 ;a < k[1].size(); a++){  feta[a] = k[1][a];   }
for(unsigned int  a =0 ;a < k[2].size(); a++){  fphi[a] = k[2][a];   }


 

tree2->Fill();
}




f->Write();
f->Close();

cout << "end" << endl;

}




