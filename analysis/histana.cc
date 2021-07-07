{

	#define NHIST 20
	#define NBINS 30
	#define MAXCHI2 25

	std::cout << "start \n";
	TFile *file1 = new TFile("histos-pdf-5-25.root");
	TH1D* array1 = new TH1D[NHIST];

	TFile *file2 = new TFile("histos-pdf-5.root");
	TH1D* array2 = new TH1D[NHIST];

	// TH1D *hist = (TH1D*)file->Get("Hit Number1");
	// hist->Draw();

	for (Int_t i = 1; i <= NHIST; ++i){
	  file1->cd();
	  array1[i-1] = *(TH1D*)file1->Get( TString("Hit Number") + TString(std::to_string(i-1)));
	  file2->cd();
	  array2[i-1] = *(TH1D*)file2->Get( TString("Hit Number") + TString(std::to_string(i-1)));
	}

	TH1D* average1 = new TH1D("average1","average1", NBINS, 0 - 0.5, NBINS - 0.5);
	TH1D* average2 = new TH1D("average2","average2", NBINS, 0 - 0.5, NBINS - 0.5);


	for (Int_t binI = 1; binI <= NBINS; ++binI) {
		Double_t av = 0.;
		Double_t err = 0.;
		for (Int_t histJ = 0; histJ < NHIST; ++histJ)
		{
			av += array1[histJ].GetBinContent(binI);
			err += array1[histJ].GetBinError(binI)*array1[histJ].GetBinError(binI);
		}
		av /= NHIST;
		err = TMath::Sqrt( err/NHIST/(NHIST - 1) );
		average1->SetBinContent(binI, av);
		average1->SetBinError(binI, err);
	}

	for (Int_t binI = 1; binI <= NBINS; ++binI) {
		Double_t av = 0.;
		Double_t err = 0.;
		for (Int_t histJ = 0; histJ < NHIST; ++histJ)
		{
			av += array2[histJ].GetBinContent(binI);
			err += array2[histJ].GetBinError(binI)*array1[histJ].GetBinError(binI);
		}
		av /= NHIST;
		err = TMath::Sqrt( err/NHIST/(NHIST - 1) );
		average2->SetBinContent(binI, av);
		average2->SetBinError(binI, err);
	}

	//average->Draw();

	TH1D *hChi2 = new TH1D("chi2","chi2", 30, 0, 30);


	
	for (Int_t histJ = 0; histJ < NHIST; ++histJ){
	Double_t ndf = 0;
	Double_t chi2 = 0;
	
	for (Int_t binK = 1; binK <= NBINS; ++binK){
	  Double_t binContentI = average1->GetBinContent(binK);
	  Double_t binErrorI = average1->GetBinError(binK);
	  Double_t binContentJ = average2->GetBinContent(binK);
	  Double_t binErrorJ = average2->GetBinError(binK);
	  //Double_t binContentJ = array2[histJ].GetBinContent(binK);
	  //Double_t binErrorJ = array2[histJ].GetBinError(binK);
	  
	  if (binErrorI == 0 && binErrorJ == 0) continue;
	  //if (binErrorI * binErrorJ == 0) continue;
	  

	  //std::cout << binContentI << " " << binContentJ << std::endl;

	  chi2 += (binContentI - binContentJ)*(binContentI - binContentJ) / 
	    (binErrorI*binErrorI + binErrorJ*binErrorJ);
	  
	  ++ndf;
	}
	hChi2->Fill(chi2/ndf);
	
	std::cout << "Chi2 = " << chi2 << std::endl;
	//hChi2->Fill(chi2/ndf);

	} 
	
	hChi2->Draw();
	

}
