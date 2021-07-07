#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TRandom3.h>
#include <iostream>

#define NSEC 100
#define MEAN 5


void recombine(int num)
{
	TFile *inputFile = new TFile(TString("rawData_"+std::to_string(num)+".root"));
	TTree *input = (TTree*)inputFile->Get("T");

	TFile *output = new TFile(TString("rawDataOpt_"+std::to_string(num)+".root"), "RECREATE");
	TTree *outTree = new TTree("T", "T");

	Int_t StationID[1000000];
	Int_t nPart;
	Int_t EventID;

	input->SetBranchAddress("StationID", StationID);
	input->SetBranchAddress("nPart", &nPart);
	input->SetBranchAddress("EventID", &EventID);


	Int_t EventIDnew;
	Int_t nPhot[NSEC];
	Int_t nSec;

	outTree->Branch("EventID", &EventIDnew, "EventID/I");
	outTree->Branch("nSec", &nSec, "nSec/I");
	outTree->Branch("nPhot", nPhot, "nPhot[nSec]/I");


	Long_t nEntries = input->GetEntries();

	for (Long_t i = 0; i < nEntries; ++i) {
		input->GetEntry(i);
		for (Int_t k = 0; k < NSEC; ++k) nPhot[k] = 0;

		EventIDnew = EventID;
		nSec = NSEC;

		for (Long_t j = 0; j < nPart; ++j) {
			nPhot[StationID[j]] ++;
		}

		outTree->Fill();
	} 

	outTree->Write();
	output->Close();
}
	
