#include "TROOT.h"
#include <TFile.h>
#include <TChain.h>


void mergeMT(int nThr, int nFile)
{

	TChain *inputChain = new TChain("T");
	for (Int_t i = 1; i <= nThr; ++i){
		for (Int_t j = 1; j <= nFile; ++j){
			inputChain->Add(TString("data_"+std::to_string(i)+std::to_string(j)+".root"));
			/* code */
		}
	}

	inputChain->Merge("data.root");

	// TFile *output = new TFile(TString("dataNew.root"), "UPDATE");

	// TTree *tree = inputChain;
	// tree->Write();
	// output->Close();
}

