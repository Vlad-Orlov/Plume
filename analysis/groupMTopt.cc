#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TRandom3.h>
#include <iostream>

#define NSEC 100
#define MEAN 8


void groupMTopt(int num)
{
	TFile *inputFile = new TFile(TString("rawData_"+std::to_string(num)+".root"));
	TTree *input = (TTree*)inputFile->Get("T");

	TFile *output = new TFile(TString("newData_"+std::to_string(num)+".root"), "UPDATE");
	TTree *outTree = new TTree("T", "T");

	Int_t nPhot[NSEC];

	input->SetBranchAddress("nPhot", nPhot);


	Int_t EventIDnew;
	Int_t nPhotNew[NSEC];
	Int_t nSec;
	Int_t nColl;

	outTree->Branch("EventID", &EventIDnew, "EventID/I");
	outTree->Branch("nSec", &nSec, "nSec/I");
	outTree->Branch("nColl", &nColl, "nColl/I");
	outTree->Branch("nPhot", nPhotNew, "nPhot[nSec]/I");

	std::vector<Int_t> vnEvToGroup(0);
	Int_t nFinalEvents;

	TRandom3 *rGen = new TRandom3(0);

	Long_t nEntries = input->GetEntries();

	for (Int_t i = 0; i < nEntries;) {
		Int_t randVal = rGen->Poisson(MEAN);
		if (i+randVal >= nEntries) break;
		vnEvToGroup.push_back(randVal);
		i += randVal;
	} 

	Int_t entryID = 0;

	nFinalEvents = vnEvToGroup.size();

	for (Int_t i = 0; i < nFinalEvents; ++i){
		for (Int_t k = 0; k < NSEC; ++k) nPhotNew[k] = 0;
		nColl = vnEvToGroup[i];
		EventIDnew = i;
		nSec = NSEC;


		for (Int_t j = 0; j < nColl; ++j){
			input->GetEntry(entryID);

			for (Int_t k = 0; k < NSEC; ++k) { nPhotNew[k] += nPhot[k]; }

			entryID++;
		}
		outTree->Fill();
	}
	outTree->Write();
	output->Close();
}
	
