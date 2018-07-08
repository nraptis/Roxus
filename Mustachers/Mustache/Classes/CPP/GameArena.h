//
//  GameArena.h
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef GAME_ARENA_H
#define GAME_ARENA_H

#include "GLApp.h"
#include "PathSolver.h"
#include "GameTile.h"
#include "Tower.h"
#include "TowerBullet.h"
#include "Unit.h"
#include "XML.h"

#define GAME_TILE_LAYER_COUNT 4

class GameArena
{
public:
    
    GameArena();
    virtual ~GameArena();
    
    GLApp                               *mApp;
    
    virtual void                        Update();
    virtual void                        Draw();

    GameTile                            ***mTile;
    
    float                               mArenaWidth;
    float                               mArenaHeight;

    int                                 mGridWidth;
    int                                 mGridHeight;
    
    virtual void                        Click(float pX, float pY);
    
    GameTile                            *GetTile(int pGridX, int pGridY);
    Tower                               *GetTower(int pGridX, int pGridY);
    
    PathSolver                          mPathSolver;
    
    void                                Path(int pStartX, int pStartY, int pEndX, int pEndY);
    
    bool                                TunnelConnected(int pStartX, int pStartY, int pEndX, int pEndY);
    bool                                BridgeConnected(int pStartX, int pStartY, int pEndX, int pEndY);
    bool                                RampConnectedDown(int pStartX, int pStartY, int pEndX, int pEndY);
    bool                                RampConnectedUp(int pStartX, int pStartY, int pEndX, int pEndY);
    
    
    List                                mTowerList;
    
    List                                mUnitList;
    List                                mUnitKillList;
    
    int                                 GetTouchGridX(float pX);
    int                                 GetTouchGridY(float pY);

    void                                Generate(int pWidth, int pHeight);
    void                                SizeGrid(int pWidth, int pHeight);
    
    float                               mTargetX;
    float                               mTargetY;
    
    void                                Save(const char *pPath=0);
    void                                Load(const char *pPath=0);
    
};

#endif
