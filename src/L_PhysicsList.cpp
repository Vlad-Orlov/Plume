#include "L_PhysicsList.h"


// Physics list constructor inherited from QGSP_BERT
L_PhysicsList::L_PhysicsList() : QGSP_BERT()
{
    theCerenkovProcess = 0;
    defaultCutValue = 1.0*mm;
    SetVerboseLevel(0);

    G4cout << "Physics list constructor" << G4endl;
}

L_PhysicsList::~L_PhysicsList()
{
    delete theCerenkovProcess;
}

void L_PhysicsList::ConstructParticle()
{
    //  Constructing HEP particles from base physics list
    //  and adding OpticalPhoton to them

    QGSP_BERT::ConstructParticle();
    G4OpticalPhoton::OpticalPhotonDefinition();
}


void L_PhysicsList::ConstructProcess()
{
    //  Constructing processes from base physics list and adding
    //  Cherenkov process and optical processes

    QGSP_BERT::ConstructProcess();
    ConstructOp();
}
//void SetCuts();


void L_PhysicsList::ConstructOp()
{


    G4ParticleTable::G4PTblDicIterator *theParticleIterator = GetParticleIterator();

    G4cout<<" 000 "<<G4endl;

    // Optical Photon Processes
    theCerenkovProcess = new G4Cerenkov("Cerenkov");

    G4cout<<" 111 "<<G4endl;

    SetVerbose(0);

    theCerenkovProcess->SetMaxNumPhotonsPerStep(300);
    theCerenkovProcess->SetTrackSecondariesFirst(true);
    G4cout<<" 111 "<<G4endl;

    theParticleIterator->reset();
    while( (*theParticleIterator)() ) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        if (theCerenkovProcess->IsApplicable(*particle)) {
            G4cout << "Add Cerenkov process to " << particleName << G4endl;
            pmanager->AddProcess(theCerenkovProcess);
            pmanager->SetProcessOrdering(theCerenkovProcess, idxPostStep);
        }
        if (particleName == "opticalphoton") {
            G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
            pmanager->AddDiscreteProcess(new G4OpAbsorption());
            pmanager->AddDiscreteProcess(new G4OpRayleigh());
            pmanager->AddDiscreteProcess(new G4OpBoundaryProcess());
        }
    }


    G4cout << "Optics constructed" << G4endl;
}


void L_PhysicsList::SetVerbose(G4int verbose)
{
    theCerenkovProcess->SetVerboseLevel(verbose);

}

