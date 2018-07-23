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
#include "GameTile.h"

//Paths that units use, operates on higher fidelity grid...
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

