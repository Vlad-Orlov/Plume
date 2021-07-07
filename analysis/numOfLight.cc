{
	// TFile *file = new TFile("../../pc_instr/Lumi/results_str/dc_vc_5/results/newDataMerged.root");
	TFile *file = new TFile("data_abs_double.root");
	TTree *tree = (TTree*)file->Get("T");

	Int_t nBin = 2000;

	Int_t StationID[1000000];
	Int_t nPart;

	tree->SetBranchAddress("StationID", StationID);
	tree->SetBranchAddress("nPart", &nPart);

	Long_t nEn = tree->GetEntries();




	std::vector<TH1D> h(100, TH1D("nPhot", "nPhot", nBin, 0, nBin-1));
	
	TH1D* h1 = new TH1D("nPhot", "nPhot", nBin, 0, nBin-1);


	for (Long_t i = 0; i < nEn; ++i) {
		tree->GetEntry(i);
		std::vector<Int_t> N (100,0);

		for (Int_t j = 0; j < nPart; ++j){
			N[StationID[j]-1] = N[StationID[j]-1] + 1;
		}

		// if (N[32] != 0) h1->Fill(N[32]);

		for (Int_t j = 0; j < 100; ++j){
			if (N[j] != 0) h[j].Fill(N[j]);
			// h[j]->Fill(N[j]);
		}
	}

	for (Int_t j = 1; j <= nBin; ++j) {
		Int_t binContent = 0;
		for (Int_t i = 0; i < 100; ++i)
			binContent += h[i].GetBinContent(j);
		h1->SetBinContent(j, binContent);
	}

	// h[5].Draw();
	// h[74].SetLineColor(kRed);
	// h[74].Draw("Same")
	h1->Draw();
}
