{
	TChain *theChain = new TChain("T");
	theChain->Add("dataNew.root");
	// theChain->Add("iii5_4.root");
	// TCanvas *c = new TCanvas("plots","plots", 1500,800);

	// c->Divide(2,1);

	Int_t EventID;
	Int_t nPart;
	Int_t nColl;
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
	Double_t PdgID[100000];

	theChain->SetBranchAddress("EventID", &EventID);
	theChain->SetBranchAddress("nPart", &nPart);
	theChain->SetBranchAddress("nColl", &nColl);
	theChain->SetBranchAddress("TrackID", TrackID);
	theChain->SetBranchAddress("ParentID", ParentID);
	theChain->SetBranchAddress("StationID", StationID);
	theChain->SetBranchAddress("X", X);
	theChain->SetBranchAddress("Y", Y);
	theChain->SetBranchAddress("Z", Z);
	theChain->SetBranchAddress("Momentum", Momentum);
	theChain->SetBranchAddress("Px", Px);
	theChain->SetBranchAddress("Py", Py);
	theChain->SetBranchAddress("Pz", Pz);
	theChain->SetBranchAddress("Time", Time);
	theChain->SetBranchAddress("PdgID", PdgID);

	Double_t nNoPartIn = 0;
	Double_t nNoPartOut = 0;

	Long_t nEv = theChain->GetEntries();

	for (Long_t j = 0; j < nEv; ++j) {
		theChain->GetEntry(j);

		Bool_t noPartIn = true;
		Bool_t noPartOut = true;

		// std::cout << "N coll: " << nColl << std::endl;

		for (Int_t i = 0; i < nPart; ++i){
			if (StationID[i] < 0) noPartIn = false;
			if (StationID[i] > 0) noPartOut = false;
		}

		// std::cout << nPart << std::endl;

		if (noPartIn) nNoPartIn++;
		if (noPartOut) nNoPartOut++;
	}

	nNoPartIn /= nEv;
	nNoPartOut /= nEv;

	Double_t meanIn = - log(nNoPartIn);
	Double_t meanOut = - log(nNoPartOut);

	// T->Draw("StationID", "nColl == 1");

	std::cout << "Number of events: " << nEv << std::endl;
	std::cout <<"Mean inside " << meanIn << std::endl;
	std::cout <<"Mean outside " << meanOut << std::endl;

}
