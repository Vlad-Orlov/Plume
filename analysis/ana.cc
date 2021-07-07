{
	TChain *theChain = new TChain("T");
	theChain->Add("data.root");
	// theChain->Add("iii5_4.root");
	TCanvas *c = new TCanvas("plots","plots", 1500,800);

	c->Divide(2,1);


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
	Double_t PdgID[100000];

	theChain->SetBranchAddress("EventID", &EventID);
	theChain->SetBranchAddress("nPart", &nPart);
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

	Int_t nBinXIn, nBinYIn, nBinXOut, nBinYOut;
	Double_t xMinIn, xMaxIn, yMinIn, yMaxIn;
	Double_t xMinOut, xMaxOut, yMinOut, yMaxOut;

	nBinXOut = 10; nBinYOut = 10;
	nBinXIn= 10; nBinYIn = 10;

	xMinIn = -30; xMaxIn = 30;
	yMinIn = -30; yMaxIn = 30;

	xMinOut = -100; xMaxOut = 100;
	yMinOut = -100; yMaxOut = 100;

	// Double_t Rmin = 10.;
	// Double_t Rmax = 30.;
	Double_t Rmin = 31.;
	Double_t Rmax = 200.;



	TH2D StationMap[2];
	StationMap[0] =  TH2D("FarthestOut", "FarthestOut", 
		nBinXOut, xMinOut, xMaxOut,
		nBinYOut, yMinOut, yMaxOut);
	StationMap[1] =  TH2D("FarthestIn", "FarthestIn", 
		nBinXIn, xMinIn, xMaxIn,
		nBinYIn, yMinIn, yMaxIn);


	TH2D CountMap[2];
	CountMap[0] =  TH2D("FarthestOut1", "FarthestOut1", 
		nBinXOut, xMinOut, xMaxOut,
		nBinYOut, yMinOut, yMaxOut);
	CountMap[1] =  TH2D("FarthestIn1", "FarthestIn1", 
		nBinXIn, xMinIn, xMaxIn,
		nBinYIn, yMinIn, yMaxIn);



	Double_t nNoPartIn = 0;
	Double_t nNoPartOut = 0;

	Long_t nEv = theChain->GetEntries();

	for (Long_t j = 0; j < nEv; ++j) {
		theChain->GetEntry(j);

		TH2D TempMap[2];
		TempMap[0] =  TH2D("FarthestOut2", "FarthestOut2", 
			nBinXOut, xMinOut, xMaxOut,
			nBinYOut, yMinOut, yMaxOut);
		TempMap[1] =  TH2D("FarthestIn2", "FarthestIn2", 
			nBinXIn, xMinIn, xMaxIn,
			nBinYIn, yMinIn, yMaxIn);


		bool noPartIn = true;
		bool noPartOut = true;


		for (Int_t i = 0; i < nPart; ++i){
			// if (X[i] < 8. && X[i] > -8 && Y[i] < 8. && Y[i] > -8) continue;
			if (StationID[i] ==  1){ 
				StationMap[0].Fill(X[i],Y[i]);
				TempMap[0].Fill(X[i],Y[i]);
			}
			if (StationID[i] == -1){
				StationMap[1].Fill(X[i],Y[i]);
				TempMap[1].Fill(X[i],Y[i]);
			}

			Double_t R = TMath::Sqrt(X[i]*X[i] + Y[i]*Y[i]);

			if (R < Rmax && R > Rmin) noPartIn = false;
			if (R > Rmax && 
				X[i] > -100 && X[i] < 100 &&
				Y[i] > -100 && Y[i] < 100) noPartOut = false;
		}

		if (noPartIn) nNoPartIn++; 
		if (noPartOut) nNoPartOut++;

		for (Int_t xI = 1; xI <= nBinXOut; ++xI){
			for (Int_t yI = 1; yI <= nBinYOut; ++yI){
				if (TempMap[0].GetBinContent(xI,yI) == 0) 
					CountMap[0].SetBinContent(xI,yI,
						CountMap[0].GetBinContent(xI,yI) + 1);
		}}

		for (Int_t xI = 1; xI <= nBinXIn; ++xI){
			for (Int_t yI = 1; yI <= nBinYIn; ++yI){
				if (TempMap[1].GetBinContent(xI,yI) == 0) 
					CountMap[1].SetBinContent(xI,yI,
						CountMap[1].GetBinContent(xI,yI) + 1);
		}}
		TempMap[0].Reset(); TempMap[1].Reset();


	}

	std::cout << "No signal inside " << nNoPartIn/nEv << " of events\n";
	std::cout << "No signal outside " << nNoPartOut/nEv << " of events\n";




	// for (Int_t xI = 0; xI <= nBinXOut; ++xI){
	// 	for (Int_t yI = 0; yI <= nBinYOut; ++yI){
	// 		Double_t BinVal = StationMap[0].GetBinContent(xI,yI) / nEv;
	// 		BinVal = round(BinVal * 10.)/10.;
	// 		StationMap[0].SetBinContent(xI, yI, BinVal);
	// }}

	// for (Int_t xI = 0; xI <= nBinXIn; ++xI){
	// 	for (Int_t yI = 0; yI <= nBinYIn; ++yI){
	// 		Double_t BinVal = StationMap[1].GetBinContent(xI,yI) / nEv;
	// 		BinVal = round(BinVal * 10.)/10.;
	// 		StationMap[1].SetBinContent(xI, yI, BinVal);
	// }}

	for (Int_t xI = 1; xI <= nBinXOut; ++xI){
		for (Int_t yI = 1; yI <= nBinYOut; ++yI){
			Double_t BinVal = CountMap[0].GetBinContent(xI,yI) / nEv ;
			BinVal = round(BinVal * 1000.)/1000.;
			CountMap[0].SetBinContent(xI, yI, BinVal);
	}}

	for (Int_t xI = 1; xI <= nBinXIn; ++xI){
		for (Int_t yI = 1; yI <= nBinYIn; ++yI){
			Double_t BinVal = CountMap[1].GetBinContent(xI,yI) / nEv ;
			BinVal = round(BinVal * 1000.)/1000.;
			CountMap[1].SetBinContent(xI, yI, BinVal);
	}}




	for (Int_t i = 0; i < 2; ++i){
		StationMap[i].SetOption("COL TEXT");
		c->cd(i+1);
		StationMap[i].Draw();
	}

	// for (Int_t i = 0; i < 2; ++i){
	// 	CountMap[i].SetOption("COL TEXT");
	// 	c->cd(i+1);
	// 	CountMap[i].Draw();
	// }



}