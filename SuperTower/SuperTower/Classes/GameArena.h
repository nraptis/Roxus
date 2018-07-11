//
//  GameArena.h
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef GAME_ARENA_H
#define GAME_ARENA_H

#include "GLApp.h"
#include "GameTile.h"
#include "GamePath.h"
#include "Tower.h"
#include "TowerBullet.h"
#include "Unit.h"
#include "FXML.h"
#include "FObject.h"

#define GRID_DEPTH 3

#define MAIN_FLOOR 1

#define TILE_TYPE_NORMAL 0
#define TILE_TYPE_RAMP_U 1
#define TILE_TYPE_RAMP_D 2
#define TILE_TYPE_RAMP_L 3
#define TILE_TYPE_RAMP_R 4
#define TILE_TYPE_BLOCKED 5

class GameArena {
public:
    GameArena();
    virtual ~GameArena();
    
    GLApp                               *mApp;
    
    virtual void                        Update();
    virtual void                        Draw();

    TilePathFinder                      mPathFinder;

    GameTile                            ****mTile;
    
    bool                                **mTowerAllowed;
    void                                ComputeAllowedPlacements();
    
    void                                PlaceTower(Tower *pTower);
    bool                                CanPlaceTower(int pGridX, int pGridY);
    bool                                CanPlaceTower();
    
    void                                RemoveTower(Tower *pTower);
    void                                RemoveTower(int pGridX, int pGridY);

    bool                                mTileVisible[GRID_DEPTH];
    float                               mTileOpacity[GRID_DEPTH];
    
    int                                 mGridWidthTotal;
    int                                 mGridHeightTotal;
    
    int                                 mGridWidthActive;
    int                                 mGridHeightActive;
    
    int                                 mGridBufferH;
    int                                 mGridBufferV;
    
    int                                 mCursorGridX;
    int                                 mCursorGridY;
    void                                RefreshGridCursor(float pX, float pY);
    
    void                                DrawGridOverlay();
    void                                DrawGridSelection();
    
    virtual void                        Click(float pX, float pY);
    
    GameTile                            *GetTile(int pGridX, int pGridY, int pGridZ);
    Tower                               *GetTower(int pGridX, int pGridY);
    
    void                                ComputePathConnections();
    
    FList                                mPathList;
    //List                                mTowerList;

    FObjectList                         mTowerCollection;

    //GameObjectCollection                mTowers;

    int                                 GetGridX(float pX);
    int                                 GetGridY(float pY);

    void                                Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);
    void                                SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);

    void                                Save(const char *pPath=0);
    void                                Load(const char *pPath=0);
};

extern GameArena *gArena;

#endif
