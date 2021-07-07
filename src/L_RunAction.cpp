/*
 * L_RunAction.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#include "L_RunAction.h"


L_RunAction::L_RunAction() {
    //	_outputFileName = "data.root";
    timer = new G4Timer();


    G4cout << "Run action constructor" << G4endl;
}

L_RunAction::~L_RunAction() {
    delete tree;
    delete hfile;
}

void L_RunAction::BeginOfRunAction(const G4Run* run)
{

    G4cout << "BeginOfRunAction" << G4endl;

    timer->Start();

    // Histogramming

    hfile = new TFile(_outputFileName, "RECREATE", "LHCb Luminometer Simulation Data", 1);

    G4cout << "Output file created" << G4endl;
    if (hfile->IsZombie()) exit(-1);
    tree = new TTree("T", "LHCb Luminometer Data Tree");
    //	tree->SetAutoSave(1000000);

    // Create new event
    TTree::SetBranchStyle(0);

    // Branches filled for each EVENT

    // Event ID
    tree->Branch("EventID",  &_EventID,  "EventID/I");
    // Number of sectors (constant every event, just for array length)
    tree->Branch("nSec", &_nSec, "nSec/I");
    // Number of photons detected in each sector
    tree->Branch("nPhot", _nPhot, "nPhot[nSec]/I");

    // Branches filled for each HIT (commented due to "optimization")


    G4cout << "BeginOfRunAction end" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void L_RunAction::EndOfRunAction(const G4Run* )
{
    //	hfile = tree->GetCurrentFile();

    G4cout << "End of run action" << G4endl;
    tree->Write();
    hfile->Write();
    tree->Print();
    timer->Stop();
    hfile->Close();

    G4cout << "Time: " << *timer << G4endl;

}
