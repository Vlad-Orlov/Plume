/*
 * L_PrimaryGeneratorAction.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: vsevolod
 */

#include "L_PrimaryGeneratorAction.h"


L_PrimaryGeneratorAction::L_PrimaryGeneratorAction() {
    iEv = 0;


    //    G4cout << "Start creating primary generator" << G4endl;

    // Pythia seed is generated from system time
    Int_t pythiaSeed = time(NULL)%10000000;

    // Getting number of event to be run in order to give Pythia
    // an information how many event to generate
    G4RunManager *runManager = G4RunManager::GetRunManager();
    G4int evToGen = runManager->GetNumberOfEventsToBeProcessed();

    // Reading configuration file, setting number of events and seed
    // pythia.readFile("PythiaSettings.cmnd");
    // pythia.readString("Main:numberOfEvents = " + std::to_string(evToGen));
    // pythia.readString("Random:seed = " + std::to_string(pythiaSeed));

    // Starting up the pythia instance
    // pythia.init();


    //    G4cout << "Primary generator created" << G4endl;
}

L_PrimaryGeneratorAction::~L_PrimaryGeneratorAction() {

}

void L_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {


    //    G4cout << "Generate primaries" << G4endl;

    //    G4LogicalVolume* worldLV
    //            = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

    // If current event is inapropriate trying another time
//    if (!pythia.next()) GeneratePrimaries(anEvent);

    // filling up class variables with event data from pythia
//    GetEvent(PythiaEvent);


    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("pi-");
    G4double m = particle->GetPDGMass();
    G4ThreeVector dir = G4ThreeVector(0.,0.,-1.);

    G4double momentum = 500 * GeV;
    G4double Ekin = (TMath::Sqrt(momentum*momentum + m*m) - m);

    _particleGun->SetParticleDefinition(particle);
    _particleGun->SetParticleMomentumDirection(dir);
    _particleGun->SetParticleEnergy(Ekin);
    _particleGun->SetParticleTime(0);
    _particleGun->SetParticlePosition(G4ThreeVector(0.,0.,5.*cm));

    _particleGun->GeneratePrimaryVertex(anEvent);

    // generating all primaries from event
    //    for (G4int pId = 0; pId < nParticles; ++pId){
    //        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    //        G4ParticleDefinition* particle = particleTable->FindParticle(pdgID[pId]);
    //        G4double m = particle->GetPDGMass();

    //        G4ThreeVector dir = G4ThreeVector(pX[pId],pY[pId],pZ[pId]);

    //        G4double momentum = TMath::Sqrt(pX[pId]*pX[pId] + pY[pId]*pY[pId] + pZ[pId]*pZ[pId]);
    //        G4double Ekin = (TMath::Sqrt(momentum*momentum + m*m) - m);

    //        _particleGun->SetParticleDefinition(particle);
    //        _particleGun->SetParticleMomentumDirection(dir);
    //        _particleGun->SetParticleEnergy(Ekin);
    //        _particleGun->SetParticleTime(T[pId]);

    //        _particleGun->SetParticlePosition(G4ThreeVector(X[pId], Y[pId], Z[pId]));


    //        // Cut off low-momentum particles (< 20 MeV)
    //        if (momentum < 20.) continue; //////////////////////// Momentum cut ////////////////////////////

    //        _particleGun->GeneratePrimaryVertex(anEvent);

    //			G4cout << "Particle name = " << particle->GetParticleName() << G4endl;
    //}


    //    G4cout << "Primaries generated" << G4endl;
}


// Method for getting an information from pythia into the class variables to pass
// into the particle gun
// bool L_PrimaryGeneratorAction::GetEvent(Pythia8::Event event) {
//     G4int particleID = 0;

//     // in terms of pythia:
//     // 0        - total values
//     // 1 and 2  - initial protons colliding
//     // so starting from 4th (id = 3) particle
//     for (G4int i = 3; i < event.size(); ++i){
//         if (!event[i].isFinal()) continue;


//         G4double vertexX = G4RandGauss::shoot(LConst::VertexX, LConst::VertexSigmaX);
//         G4double vertexY = G4RandGauss::shoot(LConst::VertexY, LConst::VertexSigmaY);
//         G4double vertexZ = G4RandGauss::shoot(LConst::VertexZ, LConst::VertexSigmaZ);

//         pdgID[particleID] = event[i].id();

//         X[particleID] = event[i].xProd()*mm + vertexX;
//         Y[particleID] = event[i].yProd()*mm + vertexY;
//         Z[particleID] = event[i].zProd()*mm + vertexZ;

//         pX[particleID] = event[i].px()*GeV;
//         pY[particleID] = event[i].py()*GeV;
//         pZ[particleID] = event[i].pz()*GeV;
//         T[particleID] = event[i].tProd()*mm / c_light;
//         particleID ++;
//     }
//     nParticles = particleID;
// }
