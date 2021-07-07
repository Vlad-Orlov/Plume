{

	#define NBINS 100
	#define MAXCHI2 25

	TCanvas *c = new TCanvas("plot", "plot", 0, 0, 1920,1080);


	TString filename1, filename2, filename3; 
	TString outname;


	filename1 = "8";
	// filename1 = "heavyIon";


	// filename2 = "vfar_5";
	filename2 = "8-08";

	// filename3 = "init_be";

	TFile *file1 = new TFile("far/" + filename1+"/histos.root");
	TH1D* hist1 = (TH1D*)file1->Get( TString("HitNumber0"));

	TFile *file2 = new TFile("far/"+ filename2+"/histos.root");	
	file2->cd();
	TH1D* hist2 = (TH1D*)file2->Get( TString("HitNumber0"));

	// TFile *file3 = new TFile(filename3+"/histos.root");	
	// file3->cd();
	// TH1D* hist3 = (TH1D*)file3->Get( TString("HitNumber0"));



	// outname = filename1 + "_vs_" + filename2 + ".png";
	outname = filename1 + "_vs_" + filename2 + "_vs_" + filename3 + ".png";

	std::cout << "_____ " << outname << " _____\n"; 



	std::cout << "Hist1: " << file1->GetName() << std::endl;
	std::cout << "Hist2: " << file2->GetName() << std::endl;

	Int_t ndf = 0;
	Double_t chi2 = 0;


	// hist1->Scale(hist2->GetEntries()/hist1->GetEntries());

	// hist1->Scale(1./hist1->GetEntries());
	// hist2->Scale(1./hist2->GetEntries());
	// hist3->Scale(1./hist3->GetEntries());

	// hist1->Scale(1e6/hist1->GetEntries());
	hist2->Scale(hist1->GetEntries()/hist2->GetEntries());

	std::cout << "nEntries: " << hist1->GetEntries() << std::endl; 


	hist2->SetLineColor(kRed);
	// hist3->SetLineColor(kBlack);

	// hist2->Draw("SAME E1");

	// hist1->Fit("f1", "N" , "E0", 0, NBINS);
	// hist2->Fit("f2", "N", "",0, NBINS);

	hist2->GetXaxis()->SetRangeUser(0,80);

	hist2->Draw("E1");
	hist1->Draw("SAME E1");
	// hist3->Draw("SAME E1");

	// poisson->Draw();

	// poisson->Draw("SAME");

	// hist1->Draw("SAME E1");

	TGraph *gChi2 = new TGraph();
	gChi2->SetMarkerStyle(kFullSquare);
	gChi2->SetMarkerSize(1);


	// poisson->Draw("SAME");

	std::cout << "Nhits\t"<< filename1<<"\t"<< filename2 <<"\tChi2\n";

	for (Int_t binK = 1; binK <= NBINS; ++binK){
		Double_t binContentI = round(hist1->GetBinContent(binK));
		Double_t binErrorI = hist1->GetBinError(binK);


		Double_t binContentJ = hist2->GetBinContent(binK);
		Double_t binErrorJ = hist2->GetBinError(binK);

		// Double_t binContentJ = poisson->Eval(binK-1);
		// Double_t binErrorJ = TMath::Sqrt(poisson->Eval(binK));
		// Double_t binErrorJ = 0;


		if (binContentI == 0 && binContentJ == 0) continue;
		//if (binErrorI * binErrorJ == 0) continue;

		Double_t chi2Local = 	(binContentI - binContentJ)*(binContentI - binContentJ) / 
								(binErrorI*binErrorI + binErrorJ*binErrorJ);
		
		Double_t difLocal = 	(binContentI - binContentJ) / 
								TMath::Sqrt((binErrorI*binErrorI + binErrorJ*binErrorJ));
		chi2 += abs(chi2Local);

		std::cout << binK-1 << "\t" << binContentI << "("<< binErrorI << ")\t\t"
									<< binContentJ << "(" << binErrorJ << ")\t\t"
									<< chi2Local << std::endl; 

		// gChi2->SetPoint(gChi2->GetN(), binK-1, difLocal);

		++ndf;
	}
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Total chi2:\t\t\t\t" << chi2 << std::endl;
	std::cout << "Total chi2/nBin:\t\t\t" << chi2/ndf << std::endl;


	// hist1->GetYaxis()->SetLog();


	// gChi2->Draw("ap");
	// gChi2->GetYaxis()->SetRangeUser(-50, 50);


	gStyle->SetOptStat(0);
	gStyle->SetOptFit();

	TLegend *l = new TLegend(0.6,0.75,0.9,0.9);
	l->SetHeader("6 cm rectangle, 1 cm from beampipe (beryllium)", "c");
	l->AddEntry(hist1, "mean = 8","l");
	l->AddEntry(hist2, "mean = 8.08","l");
	// l->AddEntry(hist3, "6 cm trapeze, 1 cm from beampipe (beryllium)","l");

	l->Draw();
	// gPad->SetLogy();
	gPad->Modified();

	c->SaveAs(outname);


	gROOT->Close();
}
