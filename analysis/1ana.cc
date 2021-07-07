{
	TChain *theChain1 = new TChain("T");
	theChain1->Add("dataNew5.root");
	//theChain1->Add("newData_1.root");

	theChain2 = new TChain("T");
	theChain2->Add("dataNew5+.root");
	//theChain2->Add("newData_1.root");

	TCanvas *c = new TCanvas();
	c->Divide(4,2);

	Int_t EventID1;
	Int_t nPart1;
	Int_t nColl1;
	Int_t TrackID1[100000];
	Int_t ParentID1[100000];
	Int_t StationID1[100000];
	Double_t X1[100000];
	Double_t Y1[100000];
	Double_t Z1[100000];
	Double_t Momentum1[100000];
	Double_t Px1[100000];
	Double_t Py1[100000];
	Double_t Pz1[100000];
	Double_t Time1[100000];
	Double_t PdgID1[100000];

	Int_t EventID2;
	Int_t nPart2;
	Int_t nColl2;
	Int_t TrackID2[100000];
	Int_t ParentID2[100000];
	Int_t StationID2[100000];
	Double_t X2[100000];
	Double_t Y2[100000];
	Double_t Z2[100000];
	Double_t Momentum2[100000];
	Double_t Px2[100000];
	Double_t Py2[100000];
	Double_t Pz2[100000];
	Double_t Time2[100000];
	Double_t PdgID2[100000];

	theChain1->SetBranchAddress("EventID", &EventID1);
	theChain1->SetBranchAddress("nPart", &nPart1);
	theChain1->SetBranchAddress("nColl", &nColl1);
	theChain1->SetBranchAddress("TrackID", TrackID1);
	theChain1->SetBranchAddress("ParentID", ParentID1);
	theChain1->SetBranchAddress("StationID", StationID1);
	theChain1->SetBranchAddress("X", X1);
	theChain1->SetBranchAddress("Y", Y1);
	theChain1->SetBranchAddress("Z", Z1);
	theChain1->SetBranchAddress("Momentum", Momentum1);
	theChain1->SetBranchAddress("Px", Px1);
	theChain1->SetBranchAddress("Py", Py1);
	theChain1->SetBranchAddress("Pz", Pz1);
	theChain1->SetBranchAddress("Time", Time1);
	theChain1->SetBranchAddress("PdgID", PdgID1);



	theChain2->SetBranchAddress("EventID", &EventID2);
	theChain2->SetBranchAddress("nPart", &nPart2);
	theChain2->SetBranchAddress("nColl", &nColl2);
	theChain2->SetBranchAddress("TrackID", TrackID2);
	theChain2->SetBranchAddress("ParentID", ParentID2);
	theChain2->SetBranchAddress("StationID", StationID2);
	theChain2->SetBranchAddress("X", X2);
	theChain2->SetBranchAddress("Y", Y2);
	theChain2->SetBranchAddress("Z", Z2);
	theChain2->SetBranchAddress("Momentum", Momentum2);
	theChain2->SetBranchAddress("Px", Px2);
	theChain2->SetBranchAddress("Py", Py2);
	theChain2->SetBranchAddress("Pz", Pz2);
	theChain2->SetBranchAddress("Time", Time2);
	theChain2->SetBranchAddress("PdgID", PdgID2);
	theChain2->GetEntries();


	TH1D *hTime = new TH1D("Time","Time", 10000, 7, 13);
	TH1D *hMom = new TH1D("Momentum","Momentum", 10000, 0, 10000);

	TH2D *hTimeAngle = new TH2D("Corr","Corr", 	1000, 0, 0.07,
												1000, 7.22, 7.3);

	TH2D *hTimeMom = new TH2D("Corr","Corr", 	1000, 0, 100,
												1000, 7.2, 7.4);

	TH2D *hAngleMom = new TH2D("Corr","Corr", 	1000, 0, 0.07,
												1000, 0, 100);


	#define nSec 110


	
	TH1D *h1Hnum = new TH1D("Hit Number","HitNumber", nSec, -0.5, nSec-0.5);
	h1Hnum->SetLineColor(kBlue);
	TH1D *h2Hnum = new TH1D("Hit Number","HitNumber", nSec, -0.5, nSec-0.5);
	h2Hnum->SetLineColor(kRed);

	TH1D *h1nColl = new TH1D("nColl1", "nColl1", 10, 0, 10);
	TH1D *h2nColl = new TH1D("nColl2", "nColl2", 10, 0, 10);
	// theChain1->Draw("nColl>>nColl1");
	// theChain2->Draw("nColl>>nColl2");


	Int_t nBin = 10;


	TH1D *h1Hnum1 = new TH1D("Hit Number","HitNumber (1)", nBin, -0.5, nBin-0.5);
	h1Hnum1->SetLineColor(kBlue);
	TH1D *h1Hnum2 = new TH1D("Hit Number","HitNumber (2)", nBin, -0.5, nBin-0.5);
	h1Hnum2->SetLineColor(kBlue);
	TH1D *h1Hnum3 = new TH1D("Hit Number","HitNumber (3)", nBin, -0.5, nBin-0.5);
	h1Hnum3->SetLineColor(kBlue);
	TH1D *h1Hnum4 = new TH1D("Hit Number","HitNumber (4)", nBin, -0.5, nBin-0.5);
	h1Hnum4->SetLineColor(kBlue);
	TH1D *h1Hnum5 = new TH1D("Hit Number","HitNumber (5)", nBin, -0.5, nBin-0.5);
	h1Hnum5->SetLineColor(kBlue);
	TH1D *h1Hnum6 = new TH1D("Hit Number","HitNumber (6)", nBin, -0.5, nBin-0.5);
	h1Hnum6->SetLineColor(kBlue);
	TH1D *h1Hnum7 = new TH1D("Hit Number","HitNumber (7)", nBin, -0.5, nBin-0.5);
	h1Hnum7->SetLineColor(kBlue);
	TH1D *h1Hnum8 = new TH1D("Hit Number","HitNumber (8)", nBin, -0.5, nBin-0.5);
	h1Hnum8->SetLineColor(kBlue);
	
	TH1D *h2Hnum1 = new TH1D("Hit Number","HitNumber (1)", nBin, -0.5, nBin-0.5);
	h2Hnum1->SetLineColor(kRed);
	TH1D *h2Hnum2 = new TH1D("Hit Number","HitNumber (2)", nBin, -0.5, nBin-0.5);
	h2Hnum2->SetLineColor(kRed);
	TH1D *h2Hnum3 = new TH1D("Hit Number","HitNumber (3)", nBin, -0.5, nBin-0.5);
	h2Hnum3->SetLineColor(kRed);
	TH1D *h2Hnum4 = new TH1D("Hit Number","HitNumber (4)", nBin, -0.5, nBin-0.5);
	h2Hnum4->SetLineColor(kRed);
	TH1D *h2Hnum5 = new TH1D("Hit Number","HitNumber (5)", nBin, -0.5, nBin-0.5);
	h2Hnum5->SetLineColor(kRed);
	TH1D *h2Hnum6 = new TH1D("Hit Number","HitNumber (6)", nBin, -0.5, nBin-0.5);
	h2Hnum6->SetLineColor(kRed);
	TH1D *h2Hnum7 = new TH1D("Hit Number","HitNumber (7)", nBin, -0.5, nBin-0.5);
	h2Hnum7->SetLineColor(kRed);
	TH1D *h2Hnum8 = new TH1D("Hit Number","HitNumber (8)", nBin, -0.5, nBin-0.5);
	h2Hnum8->SetLineColor(kRed);
	

	Long_t nEv1 = theChain1->GetEntries();
	Long_t nEv2 = theChain2->GetEntries();


	////////// Loop 1 //////////
	for (Long_t j = 0; j < min(nEv2, nEv1); ++j) {
		theChain1->GetEntry(j);
		h1nColl->Fill(nColl1);

		Int_t nPhot[nSec] = {0};
		Bool_t isChecked[nSec] = {false};

		for (Int_t i = 0; i < nPart1; ++i){
			if (StationID1[i] < 0) continue;
			if (isChecked[StationID1[i]]) continue;

			nPhot[StationID1[i]] ++;
			if (nPhot[StationID1[i]] > 20.){
				// h1Hnum->Fill(StationID[i]);
				isChecked[StationID1[i]] = true;
			}
		}

		Int_t numOfHits = 0;
		for (int i = 0; i < nSec; ++i)
			if (isChecked[i]) numOfHits++;
		
		h1Hnum->Fill(numOfHits);

		if (nColl1 == 1) h1Hnum1->Fill(numOfHits);
		else if (nColl1 == 2) h1Hnum2->Fill(numOfHits);
		else if (nColl1 == 3) h1Hnum3->Fill(numOfHits);
		else if (nColl1 == 4) h1Hnum4->Fill(numOfHits);
		else if (nColl1 == 5) h1Hnum5->Fill(numOfHits);
		else if (nColl1 == 6) h1Hnum6->Fill(numOfHits);
		else if (nColl1 == 7) h1Hnum7->Fill(numOfHits);
		else if (nColl1 == 8) h1Hnum8->Fill(numOfHits);
	}


	////////// Loop 2 //////////

	for (Long_t j = 0; j < min(nEv2, nEv1); ++j) {
		theChain2->GetEntry(j);
		h2nColl->Fill(nColl2);

		Int_t nPhot[nSec] = {0};
		Bool_t isChecked[nSec] = {false};

		for (Int_t i = 0; i < nPart2; ++i){
			if (StationID2[i] < 0) continue;
			if (isChecked[StationID2[i]]) continue;

			nPhot[StationID2[i]] ++;
			if (nPhot[StationID2[i]] > 20.){
				// h2Hnum->Fill(StationID[i]);
				isChecked[StationID2[i]] = true;
			}
		}

		Int_t numOfHits = 0;
		for (int i = 0; i < nSec; ++i)
			if (isChecked[i]) numOfHits++;

		h2Hnum->Fill(numOfHits);

		if (nColl2 == 1) h2Hnum1->Fill(numOfHits);
		else if (nColl2 == 2) h2Hnum2->Fill(numOfHits);
		else if (nColl2 == 3) h2Hnum3->Fill(numOfHits);
		else if (nColl2 == 4) h2Hnum4->Fill(numOfHits);
		else if (nColl2 == 5) h2Hnum5->Fill(numOfHits);
		else if (nColl2 == 6) h2Hnum6->Fill(numOfHits);
		else if (nColl2 == 7) h2Hnum7->Fill(numOfHits);
		else if (nColl2 == 8) h2Hnum8->Fill(numOfHits);
	}


	// h1Hnum1->Scale(1./h1nColl->GetBinContent(2));	
	// h1Hnum2->Scale(1./h1nColl->GetBinContent(3));	
	// h1Hnum3->Scale(1./h1nColl->GetBinContent(4));	
	// h1Hnum4->Scale(1./h1nColl->GetBinContent(5));	
	// h1Hnum5->Scale(1./h1nColl->GetBinContent(6));	
	// h1Hnum6->Scale(1./h1nColl->GetBinContent(7));	
	// h1Hnum7->Scale(1./h1nColl->GetBinContent(8));	
	// h1Hnum8->Scale(1./h1nColl->GetBinContent(9));

	// h2Hnum1->Scale(1./h2nColl->GetBinContent(2));	
	// h2Hnum2->Scale(1./h2nColl->GetBinContent(3));	
	// h2Hnum3->Scale(1./h2nColl->GetBinContent(4));	
	// h2Hnum4->Scale(1./h2nColl->GetBinContent(5));	
	// h2Hnum5->Scale(1./h2nColl->GetBinContent(6));	
	// h2Hnum6->Scale(1./h2nColl->GetBinContent(7));	
	// h2Hnum7->Scale(1./h2nColl->GetBinContent(8));	
	// h2Hnum8->Scale(1./h2nColl->GetBinContent(9));


	Double_t chi2 = 0;

	for (Int_t i = 1; i < 21; ++i){
		if (h1Hnum->GetBinContent(i) == 0) continue;
		chi2 +=	(h1Hnum->GetBinContent(i) - h2Hnum->GetBinContent(i))*
				(h1Hnum->GetBinContent(i) - h2Hnum->GetBinContent(i))
				/ (h1Hnum->GetBinError(i) *h1Hnum->GetBinError(i) +
					h2Hnum->GetBinError(i) *h2Hnum->GetBinError(i));
	}

	std::cout << "chi2 = " << chi2 << std::endl;

	h1Hnum->Draw("E1");
	h2Hnum->Draw("E1 SAME");

	// c->cd(1);
	// h1Hnum1->Draw("E1");
	// h2Hnum1->Draw("E1 SAME");
	// c->cd(2);
	// h1Hnum2->Draw("E1");
	// h2Hnum2->Draw("E1 SAME");
	// c->cd(3);
	// h1Hnum3->Draw("E1");
	// h2Hnum3->Draw("E1 SAME");
	// c->cd(4);
	// h1Hnum4->Draw("E1");
	// h2Hnum4->Draw("E1 SAME");
	// c->cd(5);
	// h1Hnum5->Draw("E1");
	// h2Hnum5->Draw("E1 SAME");
	// c->cd(6);
	// h2Hnum6->Draw("E1");
	// h1Hnum6->Draw("E1 SAME");
	// c->cd(7);
	// h2Hnum7->Draw("E1");
	// h1Hnum7->Draw("E1 SAME");
	// c->cd(8);
	// h2Hnum8->Draw("E1");
	// h1Hnum8->Draw("E1 SAME");

	// hTime->Draw();
	// hTimeAngle->Draw();
	// hMom->Draw();
	// hTimeMom->Draw();
	// hAngleMom->Draw();

}
