/*
 * L_Hit.cpp
 *
 *  Created on: Oct 3, 2018
 *      Author: vsevolod
 */

#include "L_Hit.h"

#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Square.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"

G4Allocator<L_Hit> L_HitAllocator;

L_Hit::L_Hit() :
    G4VHit()
{}

L_Hit::~L_Hit() {}

L_Hit::L_Hit(const L_Hit& right) :
    G4VHit()
{
    myData = right.myData;
}

const L_Hit& L_Hit::operator=(const L_Hit& right)
{
    myData = right.myData;
    return *this;
}

G4int L_Hit::operator==(const L_Hit& right) const
{
    return (this == &right) ? 1 : 0;
}

void L_Hit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager) {
        G4ThreeVector pos =
                G4ThreeVector(myData.X, myData.Y, myData.Z);
        G4Circle circle(pos);
        circle.SetScreenSize(4.);
        circle.SetFillStyle(G4Circle::filled);
        G4Color color(1., 0., 0.);
        G4VisAttributes att(color);
        circle.SetVisAttributes(att);
        pVVisManager->Draw(circle);
    }
}

void L_Hit::Print()
{
    /*
  G4cout << "Hit Print: "
     << " trackID: " << trackID
     << " energy: " << G4BestUnit(energy, "Energy")
     << " position: " << G4BestUnit(pos, "Length")
     << " time: " << G4BestUnit(time, "Time")
     << G4endl;
  */
}
