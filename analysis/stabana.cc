#include "TH1D.h"
#include "TH2D.h"
#include "TChain.h"
#include <iostream>
#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include <vector>

#define nSec 24

// TH1D* getHist(TString);


using namespace std;

// TH1D getHist(TString);

#define NHIST 1

TRandom3 *rnd = new TRandom3(0);

Int_t NREBIN = nSec;
Int_t NMAX = 500;



Double_t eff[100] = {0.06, 0.15, 0.3, 0.4, 0.6, 0.6, 0.9, 1.2, 1.4, \
	1.8, 1.9, 2.2, 2.6, 2.9, 3.4, 3.575, 3.95, 4.5, 4.825, 5.7, 5.9, 6.35, \
	7, 7.4, 8.1, 8.4, 9.05, 10, 10.9, 11.5, 12.1, 12.75, 14, 15, 16.4, 17, \
	18.3, 20.2, 22, 24, 25.6, 26.875, 29.75, 33, 35.5, 37.2, 39.175, 42.85, \
	46, 50, 52, 53.625, 57.25, 60, 64.3, 66.2, 67.625, 70.75, 73.8, 75.6, 76.5, \
	78.35, 80.1, 82, 83.6, 84.2, 84.9, 86.3, 87.3, 88.5, 89.1, 89.35, 90.2, 91, \
	91.9, 92.3, 92.5, 93.1, 94, 94.2, 94.6, 94.875, 95.45, 96, 96.6, 96.8, 97, \
	97.4, 97.7, 98.2, 98.35, 98.5, 98.8, 99.1, 99.4, 99.5, 99.55, 99.7, 99.9, 100 };




Bool_t isFired(Int_t nPhot){

	Double_t dice = rnd->Uniform() * 100.;

	if (nPhot >= 35) return true;
	else return false;

}


void getHistSpectra(TString filename, Int_t flag, TH1D* htot, TH1D* hlayer1, TH1D* hlayer2, TH2D* hcorr)
{

	cout << filename << endl;

	TFile *file = new TFile(filename);
	TTree *theChain1 = (TTree*)file->Get("T");

	Int_t *nPhot = new Int_t[nSec*2];


	theChain1->SetBranchAddress("nPhot", nPhot);

	// TH1D *h1nColl = new TH1D("nColl1", "nColl1", 10, 0, 10);

	Long_t nEv1 = theChain1->GetEntries();

	
	////////// Loop 1 //////////
	for (Long_t j = 0; j <  nEv1; ++j) {
		theChain1->GetEntry(j);


		for (Int_t i = 0; i < nSec; ++i){
			if (flag == 0) {
				htot->Fill(nPhot[i]);
				htot->Fill(nPhot[i+nSec]);
				hlayer1->Fill(nPhot[i]);
				hlayer2->Fill(nPhot[i+nSec]);
				hcorr->Fill(nPhot[i], nPhot[i+nSec]);
			}
			if (flag == 1) {
				if (isFired(nPhot[i]) && isFired(nPhot[i+nSec])) {
					htot->Fill(nPhot[i]);
					htot->Fill(nPhot[i+nSec]);
					hlayer1->Fill(nPhot[i]);
					hlayer2->Fill(nPhot[i+nSec]);
					hcorr->Fill(nPhot[i], nPhot[i+nSec]);
				}
			}
		}

	}
	
	file->Close();
	
}



void getHist_AND(TString filename, TH1D* h1Hnum)
{

	cout << filename << endl;
	// TChain *theChain1 = new TChain("T");

	TFile *file = new TFile(filename);
	TTree *theChain1 = (TTree*)file->Get("T");
	// if (!theChain1) { std::
	// theChain1->Add(filename);


	Int_t nPart1;
	Int_t *nPhot = new Int_t[nSec*2];

	Int_t n_hodo = nSec;

	theChain1->SetBranchAddress("nPhot", nPhot);

	// TH1D *h1nColl = new TH1D("nColl1", "nColl1", 10, 0, 10);

	Long_t nEv1 = theChain1->GetEntries();

	
	////////// Loop 1 //////////
	for (Long_t j = 0; j <  nEv1; ++j) {
		theChain1->GetEntry(j);


		// Bool_t isChecked[nSec] = {false};
		

		const Int_t nRebin = NREBIN;
		// const Int_t nRebin = 100;


		for (Int_t i = 0; i < n_hodo/nRebin; ++i){
			Double_t numOfHits = 0;			

			for (Int_t j = 0; j < nRebin; ++j){
				bool fired = false;
				if (isFired(nPhot[nRebin*i+j]) && isFired(nPhot[n_hodo+nRebin*i+j])) {
					fired = true;
					// break;
				}
				if (fired) {
					numOfHits += 1;	
				}
			}

			h1Hnum->Fill( numOfHits );	
		}

	}
	
	file->Close();
	
}

void getHist_OR(TString filename, TH1D* h1Hnum)
{

	cout << filename << endl;
	// TChain *theChain1 = new TChain("T");

	TFile *file = new TFile(filename);
	TTree *theChain1 = (TTree*)file->Get("T");
	// if (!theChain1) { std::
	// theChain1->Add(filename);


	Int_t nPart1;
	Int_t *nPhot = new Int_t[nSec*2];

	Int_t n_hodo = nSec;

	theChain1->SetBranchAddress("nPhot", nPhot);

	Long_t nEv1 = theChain1->GetEntries();

	
	////////// Loop 1 //////////
	for (Long_t j = 0; j <  nEv1; ++j) {
		theChain1->GetEntry(j);

		const Int_t nRebin = NREBIN;

		for (Int_t i = 0; i < n_hodo/nRebin; ++i){
			Double_t numOfHits = 0;			

			for (Int_t j = 0; j < nRebin; ++j){
				bool fired = false;
				if (isFired(nPhot[nRebin*i+j]) || isFired(nPhot[n_hodo+nRebin*i+j])) {
					fired = true;
					// break;
				}
				if (fired) {
					numOfHits += 1;	
				}
			}

			h1Hnum->Fill( numOfHits );	
		}

	}
	
	file->Close();
	
}

void getHist_FIRST(TString filename, TH1D* h1Hnum)
{

	cout << filename << endl;
	// TChain *theChain1 = new TChain("T");

	TFile *file = new TFile(filename);
	TTree *theChain1 = (TTree*)file->Get("T");
	// if (!theChain1) { std::
	// theChain1->Add(filename);


	Double_t eff[100] = {0.06, 0.15, 0.3, 0.4, 0.6, 0.6, 0.9, 1.2, 1.4, \
		1.8, 1.9, 2.2, 2.6, 2.9, 3.4, 3.575, 3.95, 4.5, 4.825, 5.7, 5.9, 6.35, \
		7, 7.4, 8.1, 8.4, 9.05, 10, 10.9, 11.5, 12.1, 12.75, 14, 15, 16.4, 17, \
		18.3, 20.2, 22, 24, 25.6, 26.875, 29.75, 33, 35.5, 37.2, 39.175, 42.85, \
		46, 50, 52, 53.625, 57.25, 60, 64.3, 66.2, 67.625, 70.75, 73.8, 75.6, 76.5, \
		78.35, 80.1, 82, 83.6, 84.2, 84.9, 86.3, 87.3, 88.5, 89.1, 89.35, 90.2, 91, \
		91.9, 92.3, 92.5, 93.1, 94, 94.2, 94.6, 94.875, 95.45, 96, 96.6, 96.8, 97, \
		97.4, 97.7, 98.2, 98.35, 98.5, 98.8, 99.1, 99.4, 99.5, 99.55, 99.7, 99.9, 100 };


	Int_t nPart1;
	Int_t *nPhot = new Int_t[nSec*2];

	Int_t n_hodo = nSec;

	theChain1->SetBranchAddress("nPhot", nPhot);

	Long_t nEv1 = theChain1->GetEntries();

	
	////////// Loop 1 //////////
	for (Long_t j = 0; j <  nEv1; ++j) {
		theChain1->GetEntry(j);

		const Int_t nRebin = NREBIN;

		for (Int_t i = 0; i < n_hodo/nRebin; ++i){
			Double_t numOfHits = 0;			

			for (Int_t j = 0; j < nRebin; ++j){
				bool fired = false;
				if (isFired(nPhot[nRebin*i+j])) {
					fired = true;
					// break;
				}
				if (fired) {
					numOfHits += 1;	
				}
			}

			h1Hnum->Fill( numOfHits );	
		}

	}
	
	file->Close();
	
}




int main(int argc, char** argv){
	TString filename = "file8.root";



	if (argc == 2) NMAX = atoi(argv[1]); else
	if (argc == 3) {
		filename = TString(argv[1]);
		NMAX = atoi(argv[2]);
	} else
	if (argc == 4){
		filename = TString(argv[1]);
		NMAX = atoi(argv[2]);
		NREBIN = atoi(argv[3]);
	} else {
	cout<<" PLUME simulation data analysis SW: "<<endl
		<<"       [1] - input root file name               (default: \"" << filename << "\")   "<<endl
		<<"       [2] - max number of photons in spectra   (default:     500     )   "<<endl
		<<"       [3] - number of sectors in group         (default:      "<< nSec <<"     )"  <<endl
		<<"                                                                          "  <<endl
		<<" Recomended combinations: [2], [1][2], [1][2][3]"<< endl;
	return 0 ;
	} 

	

	TH1D *array[9];
	TH2D *array2[2];
	
	TFile *out = new TFile("histos.root","RECREATE");



	array[0]  = new TH1D(TString("total_raw"),TString("total_raw"), NMAX, 1, NMAX+1);
	array[1]  = new TH1D(TString("layer1_raw"),TString("layer1_raw"), NMAX, 1, NMAX+1);
	array[2]  = new TH1D(TString("layer2_raw"),TString("layer2_raw"), NMAX, 1, NMAX+1);
	array2[0] = new TH2D(TString("layers_corr_raw"),TString("layers_corr_raw"), NMAX, 1, NMAX+1,
																				NMAX, 1, NMAX+1);
 

	array[3] = new TH1D(TString("total_AND_th35"),TString("total_AND_th35"), NMAX, 1, NMAX+1);
	array[4] = new TH1D(TString("layer1_AND_th35"),TString("total_AND_th35"), NMAX, 1, NMAX+1);
	array[5] = new TH1D(TString("layer2_AND_th35"),TString("total_AND_th35"), NMAX, 1, NMAX+1);
	array2[1] = new TH2D(TString("layers_corr_AND_th35"),TString("layers_corr_AND_th35"), 	NMAX, 1, NMAX+1,
																							NMAX, 1, NMAX+1);



	getHistSpectra(filename, 0, array[0], array[1], array[2], array2[0]);
	getHistSpectra(filename, 1, array[3], array[4], array[5], array2[1]);

	array[0]->SetLineColor(kGreen);
	array[1]->SetLineColor(kRed);
	array[2]->SetLineColor(kBlue);


	array[3]->SetLineColor(kGreen);
	array[4]->SetLineColor(kRed);
	array[5]->SetLineColor(kBlue);



	array[6] = new TH1D(TString("HitNumber_AND"),TString("HitNumber_AND"), nSec, 0, nSec);
	array[7] = new TH1D(TString("HitNumber_OR"),TString("HitNumber_OR"), nSec, 0, nSec);
	array[8] = new TH1D(TString("HitNumber_FIRST"),TString("HitNumber_FIRST"), nSec, 0, nSec);



	getHist_AND(filename, array[6]);
	getHist_OR(filename, array[7]);
	getHist_FIRST(filename, array[8]);

	array[6]->SetLineColor(kBlue);
	array[7]->SetLineColor(kRed);
	array[8]->SetLineColor(kGreen);


	cout << "AND: \t" << array[0]->GetMean() << " \t+- \t" << array[0]->GetMeanError() << std::endl;
	cout << "OR: \t" << array[1]->GetMean() << " \t+- \t" << array[1]->GetMeanError() << std::endl;
	cout << "First: \t" << array[2]->GetMean() << " \t+- \t" << array[2]->GetMeanError() << std::endl;
	

	out->cd();

	for (auto hist : array){
		hist->Write();
	} 

	array2[0]->Write();
	array2[1]->Write();

	// delete htemp;

	
	return 0;
}
