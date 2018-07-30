//
//  UnitPath.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/22/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef UNIT_PATH_HPP
#define UNIT_PATH_HPP

#include "TilePathFinder.h"
#include "GameTile.hpp"

//Rule: U can't place any tower iff
// 1.) It blocks a "level path" from reaching its destination.
// 2.) It prevents any unit from reaching its destination...
// -------
// C.) As a result of rules 1 and 2, it is possible for a unit to be "cut off"
// from the "level path" is was originally following.


//Some observations which we must handle:
//1.) The "unit path" can stray somewhat far from the "level path" especially
//when going around gnarly diagonals and funky corners..
//2.) The unit path cannot be permenantly attached to the level path because it
//is possible to "cut off" a unit (See C)
//3.) It is also possible for a "cut off" unit to wander back onto the "level path"
//as it wanders in "free mode"

class GameArena;
class UnitPath {
public:
    UnitPath();
    ~UnitPath();

    TilePathFinder                      mPathFinder;

    void                                DrawMarkers();

    void                                ComputePath(GameArena *pArena);

    int                                 mStartX;
    int                                 mStartY;
    int                                 mStartZ;

    int                                 mEndX;
    int                                 mEndY;
    int                                 mEndZ;

    int                                 mLength;
    int                                 mSize;

    int                                 *mPathX;
    int                                 *mPathY;
    int                                 *mPathZ;
};

#endif

