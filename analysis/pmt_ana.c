#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"

void ana(int flag){
	gROOT->Reset();

	TFile* f_al = new TFile("histos.root");

	TH1D* h_and = (TH1D*)f_al->Get("HitNumber_AND");
	TH1D* h_or = (TH1D*)f_al->Get("HitNumber_OR");
	TH1D* h_first = (TH1D*)f_al->Get("HitNumber_FIRST");

	h_and->SetLineColor(kBlue);
	h_or->SetLineColor(kRed);
	h_first->SetLineColor(kMagenta);

	h_and->Scale(1./h_and->GetEntries());
	h_or->Scale(1./h_or->GetEntries());
	h_first->Scale(1./h_first->GetEntries());

	Double_t occ_and = h_and->GetBinContent(2);
	Double_t occ_or = h_or->GetBinContent(2) ;
	Double_t occ_first = h_first->GetBinContent(2);

	TCanvas *c = new TCanvas("c","c",1920,1080);

	h_and->Draw();
	h_or->Draw("SAME");
	h_first->Draw("SAME");

	TLegend *l = new TLegend(0.65,0.75,0.9,0.9);
	// l->SetHeader("20 sectors, 6 cm from BP", "c");

	if (flag == 0){
		l->AddEntry(h_and, TString("AND (" + std::to_string(occ_and) + ")" ) );
		l->AddEntry(h_or, TString("OR (" + std::to_string(occ_or) + ")"));
		l->AddEntry(h_first, TString("First layer only (" + std::to_string(occ_first) + ")") );
		l->Draw();
	}


	// TLegend *l = new TLegend(0.65,0.75,0.9,0.9);
	// l->SetHeader("20 sectors, 6 cm from BP", "c");
	

	if (flag == 1){
		l->AddEntry(h_and, "AND" );
		l->AddEntry(h_or, "OR");
		l->AddEntry(h_first, "First layer only");
		l->Draw();
	}

	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	c->SaveAs("comparison.png");

}


