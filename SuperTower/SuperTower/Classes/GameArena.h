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
#include "AnimatedLevelPath.hpp"
#include "UnitPath.hpp"
#include "Tower.h"
#include "TowerBullet.h"
#include "Unit.h"
#include "FXML.h"
#include "FObject.h"

#define GRID_DEPTH 3
//#define SUBTILES_PER_TILE 5


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

    //The grid that we use for pathfinding, etc - these are clones of the objects in mUnitGridBase...
    PathNode                                    ****mUnitGrid;
    PathNode                                    ****mUnitGridBase;

    int                                         mUnitGridWidth;
    int                                         mUnitGridHeight;

    bool                                        **mTowerAllowed;
    void                                        ComputeAllowedPlacements();
    
    void                                        PlaceTower(Tower *pTower);
    bool                                        CanPlaceTower(int pGridX, int pGridY, int pGridZ);
    bool                                        CanPlaceTower();
    
    void                                        RemoveTower(Tower *pTower);
    void                                        RemoveTower(int pGridX, int pGridY, int pGridZ);

    void                                        DeleteTile(int pGridX, int pGridY, int pGridZ);
    FList                                       mDeletedTileList;

    //For smaller grid, the nodes from GRID BASE (assumed we will be mapping
    //properly from unit grid base to unit grid) ... 
    FList                                       mDeletedNodeList;

    bool                                        mTileVisible[GRID_DEPTH];
    float                                       mTileOpacity[GRID_DEPTH];
    
    int                                         mTileGridWidthTotal;
    int                                         mTileGridHeightTotal;
    
    int                                         mTileGridWidthActive;
    int                                         mTileGridHeightActive;
    
    int                                         mTileGridBufferH;
    int                                         mTileGridBufferV;

    int                                         mCursorGridX;
    int                                         mCursorGridY;
    int                                         mCursorGridZ;

    float                                       GetUnitGridX(int pGridX, int pGridY, int pGridZ);
    float                                       GetUnitGridY(int pGridX, int pGridY, int pGridZ);

    void                                        RefreshGridCursor(float pX, float pY);

    void                                        DrawGridOverlay();
    void                                        DrawGridSelection();
    
    virtual void                                Click(float pX, float pY);
    
    GameTile                                    *GetTile(int pGridX, int pGridY, int pGridZ);
    PathNode                                    *GetGridNode(int pGridX, int pGridY, int pGridZ);
    Tower                                       *GetTower(int pGridX, int pGridY, int pGridZ);


    void                                        AddUnit(Unit *pUnit, LevelPath *pPath);
    void                                        AddUnit(Unit *pUnit);

    FObjectList                                 mUnitCollection;
    

    //Assumption: Grid nodes already exist.
    //If, for example, we change a tile or place a tower, we should REFRESH the nodes.
    //This will assign nodes to tiles, compute node positions, and figure out which
    //nodes are "blocked" by default...
    void                                        RefreshUnitGridNodes();
    void                                        ComputePathConnections();

    //Assumed that ComputePathConnections() was called...
    void                                        ComputeGridConnections();


    FList                                       mPathList;

    FObjectList                                 mTowerCollection;

    void                                        SpawnUnitsOnPath(FList *pUnitList, LevelPath *pPath);

    void                                        DumpLevelPathToTileList(LevelPath *pPath);
    FList                                       mTileList;
    
    LevelPath                                   *AttemptPathSelect(float pX, float pY);
    
    //Takes into consideration the actual tiles of the arena to determine exactly
    //which x, y, and z grid positions the user's finger has landed on...
    void                                        GetGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ);

    //Editor only: this determines which grid position our fingers would land at
    //for a given depth...
    void                                        GetEditorGridPosAtDepth(float pX, float pY, int pDepth, int &pGridX, int &pGridY);
    void                                        GetEditorGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ);


    void                                        Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);
    void                                        SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);
    void                                        ResizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);

    //Assumptions: Grid is already sized and loaded
    void                                        GenerateUnitGrid();

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

    float                                       mTestNinjaRotation;
    float                                       mTestNinjaFrame;
    
    UnitPath                                    mTestUnitPath;
    void                                        ComputeTestPath();

};

extern GameArena *gArena;

#endif
