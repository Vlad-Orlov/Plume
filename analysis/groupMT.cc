#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TRandom3.h>
#include <iostream>

void groupMT(int num)
{
	std::cout << "Hi!\n";
	Double_t MEAN = 5.25;

	TFile *inputFile = new TFile(TString("data_"+std::to_string(num)+".root"));
	TTree *input = (TTree*)inputFile->Get("T");

	TFile *output = new TFile(TString("dataNew_"+std::to_string(num)+".root"), "UPDATE");

	TTree *outTree = new TTree("T", "T");

	Int_t EventID;
	Int_t nPart;
	Int_t TrackID[100000];
	Int_t ParentID[100000];
	Int_t StationID[100000];
	Double_t X[100000];
	Double_t Y[100000];
	Double_t Z[100000];
	Double_t Momentum[100000];
	Double_t Px[100000];
	Double_t Py[100000];
	Double_t Pz[100000];
	Double_t Time[100000];
	Int_t PdgID[100000];

	input->SetBranchAddress("EventID", &EventID);
	input->SetBranchAddress("nPart", &nPart);
	input->SetBranchAddress("TrackID", TrackID);
	input->SetBranchAddress("ParentID", ParentID);
	input->SetBranchAddress("StationID", StationID);
	input->SetBranchAddress("X", X);
	input->SetBranchAddress("Y", Y);
	input->SetBranchAddress("Z", Z);
	input->SetBranchAddress("Momentum", Momentum);
	input->SetBranchAddress("Px", Px);
	input->SetBranchAddress("Py", Py);
	input->SetBranchAddress("Pz", Pz);
	input->SetBranchAddress("Time", Time);
	input->SetBranchAddress("PdgID", PdgID);



	Int_t EventIDNew;
	Int_t nColl;
	Int_t nPartNew;


	std::vector<Int_t> vTrackIDNew(0);
	std::vector<Int_t> vParentIDNew(0);
	std::vector<Int_t> vStationIDNew(0);
	std::vector<Double_t> vXNew(0);
	std::vector<Double_t> vYNew(0);
	std::vector<Double_t> vZNew(0);
	std::vector<Double_t> vMomentumNew(0);
	std::vector<Double_t> vPxNew(0);
	std::vector<Double_t> vPyNew(0);
	std::vector<Double_t> vPzNew(0);
	std::vector<Double_t> vTimeNew(0);
	std::vector<Int_t> vPdgIDNew(0);


	outTree->Branch("EventID", &EventIDNew, "EventID/I");
	outTree->Branch("nColl", &nColl, "nColl/I");
	outTree->Branch("nPart", &nPartNew, "nPart/I");

	Int_t *TrackIDNew = vTrackIDNew.data();
	Int_t *ParentIDNew = vParentIDNew.data();
	Int_t *StationIDNew = vStationIDNew.data();
	Double_t *XNew = vXNew.data();
	Double_t *YNew = vYNew.data();
	Double_t *ZNew = vZNew.data();
	Double_t *MomentumNew = vMomentumNew.data();
	Double_t *PxNew = vPxNew.data();
	Double_t *PyNew = vPyNew.data();
	Double_t *PzNew = vPzNew.data();
	Double_t *TimeNew = vTimeNew.data();
	Int_t *PdgIDNew = vPdgIDNew.data();

	
	outTree->Branch("TrackID", TrackIDNew, "TrackID[nPart]/I");
	outTree->Branch("ParentID", ParentIDNew, "ParentID[nPart]/I");
	outTree->Branch("StationID", StationIDNew, "StationID[nPart]/I");
	outTree->Branch("X", XNew, "X[nPart]/D");
	outTree->Branch("Y", YNew, "Y[nPart]/D");
	outTree->Branch("Z", ZNew, "Z[nPart]/D");
	outTree->Branch("Momentum", MomentumNew, "Momentum[nPart]/D");
	outTree->Branch("Px", PxNew, "Px[nPart]/D");
	outTree->Branch("Py", PyNew, "Py[nPart]/D");
	outTree->Branch("Pz", PzNew, "Pz[nPart]/D");
	outTree->Branch("Time", TimeNew, "Time[nPart]/D");
	outTree->Branch("PdgID", PdgIDNew, "PdgID[nPart]/I");

	

	std::vector<Int_t> vnEvToGroup(0);
	Int_t nFinalEvents;
	Int_t *nEvToGroup = vnEvToGroup.data();



	nFinalEvents = 0;

	// Int_t i = 0;

	TRandom3 *rGen = new TRandom3(0);
	// std::cout << "hi\n";


	Long_t nEntries = input->GetEntries();

	for (Int_t i = 0; i < nEntries;) {
		Int_t randVal = rGen->Poisson(MEAN);
		if (i+randVal >= nEntries) break;
		vnEvToGroup.push_back(randVal);
		i += randVal;

	} 
	// std::cout << "hi\n";

	nFinalEvents = vnEvToGroup.size();
	nEvToGroup = vnEvToGroup.data();

	Int_t entryID = 0;
	
	for (Int_t i = 0; i < nFinalEvents; ++i){			// Loop for final events
		// std::cout << nEvToGroup[i] << std::endl;
		nPartNew = 0;
		EventIDNew = i;
		nColl = nEvToGroup[i];

		vTrackIDNew = std::vector<Int_t>(0);;
		vParentIDNew = std::vector<Int_t>(0);;
		vStationIDNew = std::vector<Int_t>(0);;
		vXNew = std::vector<Double_t>(0);;
		vYNew = std::vector<Double_t>(0);;
		vZNew = std::vector<Double_t>(0);;
		vMomentumNew = std::vector<Double_t>(0);;
		vPxNew = std::vector<Double_t>(0);;
		vPyNew = std::vector<Double_t>(0);;
		vPzNew = std::vector<Double_t>(0);;
		vTimeNew = std::vector<Double_t>(0);;
		vPdgIDNew = std::vector<Int_t>(0);;


		for (Int_t j = 0; j < nEvToGroup[i]; ++j){	// Loop for init events to group
			// std::cout << entryID << std::endl;
			input->GetEntry(entryID);
			nPartNew += nPart;
			


			for (Int_t k = 0; k < nPart; ++k) {	// Loop for particles inside event
				vTrackIDNew.push_back(TrackID[k]);
				vParentIDNew.push_back(ParentID[k]);
				vStationIDNew.push_back(StationID[k]);
				vXNew.push_back(X[k]);
				vYNew.push_back(Y[k]);
				vZNew.push_back(Z[k]);
				vMomentumNew.push_back(Momentum[k]);
				vPxNew.push_back(Px[k]);
				vPyNew.push_back(Py[k]);
				vPzNew.push_back(Pz[k]);
				vTimeNew.push_back(Time[k]);
				vPdgIDNew.push_back(PdgID[k]);


			}

			entryID++;
		}

		TrackIDNew = vTrackIDNew.data();
		ParentIDNew = vParentIDNew.data();
		StationIDNew = vStationIDNew.data();
		XNew = vXNew.data();
		YNew = vYNew.data();
		ZNew = vZNew.data();
		MomentumNew = vMomentumNew.data();
		PxNew = vPxNew.data();
		PyNew = vPyNew.data();
		PzNew = vPzNew.data();
		TimeNew = vTimeNew.data();
		PdgIDNew = vPdgIDNew.data();
		
		outTree->SetBranchAddress("TrackID", TrackIDNew);
		outTree->SetBranchAddress("ParentID", ParentIDNew);
		outTree->SetBranchAddress("StationID", StationIDNew);
		outTree->SetBranchAddress("X", XNew);
		outTree->SetBranchAddress("Y", YNew);
		outTree->SetBranchAddress("Z", ZNew);
		outTree->SetBranchAddress("Momentum", MomentumNew);
		outTree->SetBranchAddress("Px", PxNew);
		outTree->SetBranchAddress("Py", PyNew);
		outTree->SetBranchAddress("Pz", PzNew);
		outTree->SetBranchAddress("Time", TimeNew);
		outTree->SetBranchAddress("PdgID", PdgIDNew);


		outTree->Fill();


	}




	outTree->Write();
	output->Close();
	// input->Close();

}
