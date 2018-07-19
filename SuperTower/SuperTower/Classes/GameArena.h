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
#include "AnimatedGamePath.hpp"
#include "Tower.h"
#include "TowerBullet.h"
#include "Unit.h"
#include "FXML.h"
#include "FObject.h"

#define GRID_DEPTH 3
#define SUBTILES_PER_TILE 5

#define MAIN_FLOOR 1



class GameArena {
public:
    GameArena();
    virtual ~GameArena();
    
    virtual void                                Update();
    virtual void                                Draw();

    TilePathFinder                              mPathFinder;

    //Our main "grid" of tiles...
    GameTile                                    ****mTile;



    //Whole world gets subtiles..
    //SUBTILES_PER_TILE
    GameTile                                    ****mSubtile;


    bool                                        **mTowerAllowed;
    void                                        ComputeAllowedPlacements();
    
    void                                        PlaceTower(Tower *pTower);
    bool                                        CanPlaceTower(int pGridX, int pGridY, int pGridZ);
    bool                                        CanPlaceTower();
    
    void                                        RemoveTower(Tower *pTower);
    void                                        RemoveTower(int pGridX, int pGridY, int pGridZ);

    void                                        DeleteTile(int pGridX, int pGridY, int pGridZ);
    void                                        DeleteSubtile(int pGridX, int pGridY, int pGridZ);
    FList                                       mDeletedTileList;

    bool                                        mTileVisible[GRID_DEPTH];
    float                                       mTileOpacity[GRID_DEPTH];
    
    int                                         mGridWidthTotal;
    int                                         mGridHeightTotal;
    
    int                                         mGridWidthActive;
    int                                         mGridHeightActive;
    
    int                                         mGridBufferH;
    int                                         mGridBufferV;

    int                                         mSubgridWidth;
    int                                         mSubgridHeight;
    
    int                                         mCursorGridX;
    int                                         mCursorGridY;
    int                                         mCursorGridZ;

    void                                        RefreshGridCursor(float pX, float pY);

    void                                        DrawGridOverlay();
    void                                        DrawGridSelection();
    
    virtual void                                Click(float pX, float pY);
    
    GameTile                                    *GetTile(int pGridX, int pGridY, int pGridZ);
    GameTile                                    *GetSubtile(int pGridX, int pGridY, int pGridZ);
    Tower                                       *GetTower(int pGridX, int pGridY, int pGridZ);

    void                                        ComputePathConnections();

    FList                                       mPathList;

    FObjectList                                 mTowerCollection;
    
    //Takes into consideration the actual tiles of the arena to determine exactly
    //which x, y, and z grid positions the user's finger has landed on...
    void                                        GetGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ);


    void                                        Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);
    void                                        SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);
    void                                        ResizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);

    //Assumptions: Grid is already sized and loaded
    void                                        GenerateSubtiles();

    void                                        Clear(int pDepth);
    void                                        Clear();

    void                                        Flood(int pDepth);
    void                                        IncreaseBuffer();
    void                                        DecreaseBuffer();
    void                                        IncreaseWidth();
    void                                        DecreaseWidth();
    void                                        IncreaseHeight();
    void                                        DecreaseHeight();

    void                                        Save(const char *pPath=0);
    void                                        Load(const char *pPath=0);
};

extern GameArena *gArena;

#endif
