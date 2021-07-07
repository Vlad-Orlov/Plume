#include "TH1D.h"
#include "TChain.h"
#include <iostream>
#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include <vector>
#include "TLegend.h"

#define NHIST 20
#define NBINS 10

#define TOLERANCE 1e-8
#define MAX_ITER 50

using namespace std;

Double_t solve(Int_t, Double_t, Double_t);

int main(int argc, char *argv[])
{
	TFile *file = new TFile("histos-5-25.root");
	TH1D* array = new TH1D[NHIST];

	TH1D *recoBin[NBINS];

	for (Int_t i = 0; i < NBINS; ++i)
	{
		recoBin[i]= new TH1D(TString("reco")+to_string(i), " ", 200, 0, 3);
		recoBin[i]->SetLineColor(i+1);
		if (i == 9)
		  recoBin[i]->SetLineColor(40);

		recoBin[i]->SetAxisRange(0,20,"Y");

	}

	for (Int_t i = 0; i < NHIST; ++i){
		array[i] = *(TH1D*)file->Get( TString("Hit Number") + TString(std::to_string(i)));
	}


	TH1D *reco = new TH1D("reco", "reco", 100, 0, 5.);
	//	TH1D *reco0 = new TH1D("reco0", "reco0", 100, 0, 5.);

	for (Int_t histI = 0; histI < NHIST; ++histI)
	{
		Int_t nEntries = array[histI].GetEntries();
		Double_t p0 = array[histI].GetBinContent(1) / nEntries;
		// reco0->Fill(-TMath::Log(p0));
		recoBin[0]->Fill(-TMath::Log(p0));

		for (Int_t binJ = 1; binJ < NBINS; ++binJ)
		{
			Double_t binContent = array[histI].GetBinContent(binJ + 1);
			if (binContent == 0) continue;

			// reco->Fill(solve(binJ, binContent/nEntries, p0));
			recoBin[binJ]->Fill(solve(binJ, binContent/nEntries, p0));

		}
		
	}

	reco->SetLineColor(kBlue);
	//	reco0->SetLineColor(kRed);


	TApplication *app = new TApplication("name", &argc, argv);
	TCanvas *c = new TCanvas();

	// reco->Draw();
	// reco0->Draw("SAME");

	TLegend *legend = new TLegend();
	legend->SetHeader("Number of hits","C");

	recoBin[0]->Draw();
	legend->AddEntry(TString("reco")+to_string(0), 
			 TString(to_string(0)) + " nEntries ~ " + to_string((int)array[0].GetBinContent(0+1)) +
			 TString(" (sqrt = ") + to_string(TMath::Sqrt(array[0].GetBinContent(0+1))) + ")");


	for (int i = 1; i < NBINS; ++i)
	  {
	    recoBin[i]->Draw("SAME");
	    legend->AddEntry(TString("reco")+to_string(i), 
			     TString(to_string(i)) + " nEntries ~ " + to_string((int)array[0].GetBinContent(i+1)) +
			     TString(" (sqrt = ") + to_string(TMath::Sqrt(array[0].GetBinContent(i+1))) + ")");
	    
	  }
	
	legend->Draw();
	
	c->Show();
	app->Run();
	
	return 0;
}

Double_t solve(Int_t n, Double_t p, Double_t p0)
{
	Double_t coef[50] = {1.0000000000000000000, 1.4142135623730950488, 
		1.8171205928321396589, 2.2133638394006431848, 2.6051710846973518923,
		2.9937951655239089549, 3.3800151591412964499, 3.7643505995031286001, 
		4.1471662743969128805, 4.5287286881167647622, 4.9092387795843953590, 
		5.2888519941024478656, 5.6676911762517604347, 6.0458551714185018476, 
		6.4234247497797610972, 6.8004667982676424411, 7.1770373570247743956, 
		7.5531838641068058062, 7.9289468448651502701, 8.3043612037393433042, 
		8.6794572261328690841, 9.0542613653979386513, 9.4287968681752428600, 
		9.8030842765090768641, 10.177141834880184885, 10.550985823054150716, 
		10.924630830459004882, 11.298089984044201968, 11.671375138808850192, 
		12.044497038131643916, 12.417465449489871776, 12.790289279981639568, 
		13.162976675166152035, 13.535535104041503661, 13.907971432437271719, 
		14.280291986673251982, 14.652502608998593483, 15.024608706057010584, 
		15.396615291408378016, 15.768527022963257301, 16.140348236045913571, 
		16.512082972686357272, 16.883735007647618741, 17.255307871616730578, 
		17.626804871923534775, 17.998229111097910142, 18.369583503531317068, 
		18.740870790471075383, 19.112093553544240005, 19.483254226981281425};



    Double_t x = - TMath::Log(p0); 
    Double_t x_old;

    Int_t i = 0;  


    do {
        x_old = x;
        x = coef[n - 1] * TMath::Power(p, 1./n) * TMath::Exp(x/n); 
        i++;
    } while (fabs(x - x_old) / x > TOLERANCE && i < MAX_ITER);

    return x;

}
