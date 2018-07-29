//
//  GameTile.h
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef GAME_TILE_HPP
#define GAME_TILE_HPP

#define SUBDIVISIONS_PER_TILE 2

#define TILE_TYPE_NORMAL 0
#define TILE_TYPE_RAMP_U 1
#define TILE_TYPE_RAMP_D 2
#define TILE_TYPE_RAMP_L 3
#define TILE_TYPE_RAMP_R 4
#define TILE_TYPE_BLOCKED 5

#include "GLApp.h"
#include "FXML.h"
#include "PathNode.hpp"

class GameTile : public PathNode {
public:
    
    GameTile();
    virtual ~GameTile();

    void                                SetUp(int pGridX, int pGridY, int pGridZ);

    void                                ResetGrid();

    //void                                ConnectCentralGridNodes();


    virtual void                        Update();
    virtual void                        Draw();
    
    virtual bool                        IsBlocked();


    bool                                IsNormal();
    bool                                IsRamp();

    bool                                mDisabled;

    int                                 mTileType;
    
    bool                                PlacementAllowed();
    
    FXMLTag                             *Save();
    void                                Load(FXMLTag *pTag);

    // -------------
    // | 1 | 2 | 3 |
    // | 1 | 2 | 3 |
    // | 1 | 2 | 3 |
    // -------------

    //Basically, with 3 subdivisions, since the tile "contains" both
    //"edges" for top and bottom.

    PathNode                            *mGrid[SUBDIVISIONS_PER_TILE + 1][SUBDIVISIONS_PER_TILE + 1];

    float                               mTop;
    float                               mRight;
    float                               mBottom;
    float                               mLeft;

};

#endif
