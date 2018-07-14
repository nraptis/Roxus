//
//  GameTile.h
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_GameTile_h
#define Mustache_GameTile_h

#include "GLApp.h"
#include "FXML.h"

class GameTile;

//Theoretically, there should not be any more than
//8 connections per tile, unless your map is configured
//illegally, in which case there's a problem anyway...
#define TILE_CONNECTION_COUNT 8

class GameTileConnection {
public:
    
    GameTileConnection();
    ~GameTileConnection();
    
    void                        Reset();
    
    GameTile                    *mTile;
    
    GameTileConnection          *mParent;
    
    //This is the cost to hop to this node from its parent..
    int                         mCost;
    
    //A* Costs, these are updated / replaced on each search..
    int                         mCostG;
    int                         mCostH;
    int                         mCostTotal;
};

class GameTile
{
public:
    
    GameTile();
    virtual ~GameTile();
    
    void                                SetUp(int pGridX, int pGridY, int pGridZ);
    
    virtual void                        Update();
    virtual void                        Draw();
    
    virtual void                        DrawConnections();
    
    bool                                IsBlocked();
    bool                                IsNormal();
    bool                                IsRamp();
    
    bool                                mBlocked;
    bool                                mOccupied;
    
    int                                 mGridX;
    int                                 mGridY;
    int                                 mGridZ;
    
    float                               mCenterX;
    float                               mCenterY;
    
    int                                 mType;
    
    GameTileConnection                  mPathConnection[TILE_CONNECTION_COUNT];
    int                                 mPathConnectionCount;
    
    void                                PathReset();
    void                                ConnectTo(GameTile *pTile, int pCost);
    
    bool                                PlacementAllowed();
    
    FXMLTag                             *Save();
    void                                Load(FXMLTag *pTag);
    
};

#endif
