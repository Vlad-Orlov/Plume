/*
 * L_Hit.h
 *
 *  Created on: Oct 3, 2018
 *      Author: vsevolod
 */

#pragma once

#include <G4VHit.hh>
//G4
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//my
#include "HitDataStructure.hh"

class L_Hit: public G4VHit {
public:
    L_Hit();
    virtual ~L_Hit();

    L_Hit(const L_Hit&);
    const L_Hit& operator=(const L_Hit&);
    G4int operator==(const L_Hit&) const;

	inline void* operator new(size_t);
	inline void  operator delete(void*);

	void Draw();
	void Print();

public:

	HitData myData;

private:

};

typedef G4THitsCollection<L_Hit> L_HitsCollection;

extern G4Allocator<L_Hit> L_HitAllocator;

inline void* L_Hit::operator new(size_t)
{
	void *aHit;
    aHit = (void *) L_HitAllocator.MallocSingle();
	return aHit;
}

inline void L_Hit::operator delete(void *aHit)
{
    L_HitAllocator.FreeSingle((L_Hit*) aHit);
}
