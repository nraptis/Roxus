//
//  GameArena.h
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef GAME_ARENA_H
#define GAME_ARENA_H

#define TEST_MODE_NONE 0
#define TEST_MODE_UNIT_GROUP_CREATE 1


#include "GLApp.hpp"
#include "GameTile.hpp"
#include "AnimatedLevelPath.hpp"
#include "UnitPath.hpp"
#include "Tower.hpp"
#include "TowerBullet.h"
#include "Unit.hpp"
#include "UnitGroup.hpp"
#include "FXML.h"
#include "FObject.h"
#include "GameArenaHelper.hpp"

#define GRID_DEPTH 3
//#define SUBTILES_PER_TILE 5


#define MAIN_FLOOR 1

//TODO: The end node for each path is never blocked...

class GameArena {
public:
    GameArena();
    virtual ~GameArena();
    
    virtual void                                Update();


    virtual void                                Draw();

    void                                        UpdateBody();

    void                                        Clear();

    GameArenaHelper                             mHelper;


    bool                                        mUpdateEnabled;
    int                                         mUpdateSpeedIndex;
    int                                         mUpdateTick;

    void                                        UpdateOneFrame();
    bool                                        mOneFrameUpdateEnqueued;
    



    TilePathFinder                              mPathFinder;
    
    //Our main "grid" of tiles...
    GameTile                                    ****mTile;

    //The grid that we use for pathfinding, etc - these are clones of the objects in mUnitGridBase...
    PathNode                                    ****mUnitGrid;
    PathNode                                    ****mUnitGridBase;

    int                                         mUnitGridWidth;
    int                                         mUnitGridHeight;

    //This is for walking allowance when taking a single step...
    bool                                        ***mWalkAllowed;
    void                                        ResetWalkAllowedGrid();

    //...There can only be one tower at ANY level along the grid, assumed top level...
    //TODO: Make special grid locations election function for TOWERS which select the top
    //available colliding tile with click position...
    bool                                        **mTowerAllowed;
    void                                        ComputeAllowedPlacements();
    
    void                                        PlaceTower(Tower *pTower);
    bool                                        CanPlaceTower(int pGridX, int pGridY, int pGridZ);
    bool                                        CanPlaceTower();
    
    void                                        RemoveTower(Tower *pTower);
    void                                        RemoveTower(int pGridX, int pGridY, int pGridZ);

    void                                        DeleteTile(int pGridX, int pGridY, int pGridZ);
    FList                                       mDeletedTileList;

    bool                                        UnitGridPositionsAreAdjacent(int pGridX1, int pGridY1, int pGridZ1, int pGridX2, int pGridY2, int pGridZ2);

    //Assumption: The group is not null, the leader is not null, there is at least one item in the unit list...
    void                                        Deploy(UnitGroup *pGroup);

    //For smaller grid, the nodes from GRID BASE (assumed we will be mapping
    //properly from unit grid base to unit grid) ... co
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

    void                                        TestTouch(float pX, float pY, void *pData);
    void                                        TestDrag(float pX, float pY, void *pData);
    void                                        TestRelease(float pX, float pY, void *pData);
    void                                        TestFlush();




    GameTile                                    *GetTile(int pGridX, int pGridY, int pGridZ);

    PathNode                                    *GetGridNode(int pGridX, int pGridY, int pGridZ);

    PathNode                                    *GetEndNodeForPath(LevelPath *pPath);
    PathNode                                    *GetEndNodeForTile(GameTile *pTile);

    GameTile                                    *GetEndTileForPath(LevelPath *pPath);
    GameTile                                    *GetStartTileForPath(LevelPath *pPath);

    PathNode                                    *GetStartNodeForPath(LevelPath *pPath);
    
    //This is on the TILE GRID
    Tower                                       *GetTower(int pGridX, int pGridY, int pGridZ);

    void                                        SplitUnitGroups();
    bool                                        TrySplitUnitGroups();
    bool                                        TrySplitUnitGroup(UnitGroup *pGroup);

    void                                        KillAllInvalidUnitGroups();

    //Quickie spawn function for a singleton unit.
    void                                        AddUnit(Unit *pUnit, LevelPath *pPath);

    //This only concerns itself with killed units in the main list, not
    //processed and killed units from the previous heartbeat...

    void                                        RemoveKilledUnitGroups();

    void                                        RefreshUnitGroups();

    void                                        HandOffPath(Unit *pFromUnit, Unit *pToUnit);

    //Okay, by the time we get to here, we are guaranteed to have
    //a previous grid location and current grid location...
    void                                        UnitDidFinishWalkingStep(Unit *pUnit);

    FList                                       mUnitList;

    FList                                       mUnitGroupList;

    FList                                       mProcessUnitGroupList;



    FList                                       mAddUnitGroupList;
    
    FList                                       mKillUnitGroupList;
    FList                                       mKillUnitList;

    FList                                       mDeleteUnitGroupList;
    FList                                       mDeleteUnitList;
    
    //UnitGroup

    //Assumption: Grid nodes already exist.
    //If, for example, we change a tile or place a tower, we should REFRESH the nodes.
    //This will assign nodes to tiles, compute node positions, and figure out which
    //nodes are "blocked" by default...
    void                                        RefreshUnitGridNodes();
    void                                        ComputePathConnections();

    //Basically un-occupy all tiles and reset our connections...
    //Then, re-occupy all nodes covered by tower tiles, and anything that
    //is not a moving unit...
    void                                        ResetGridConnections();

    //Assumed that ComputePathConnections() was called...
    //Assumed that we have OCCUPIED the desired tiles that will
    //be occupied for this twist of the pepper dispenser.
    void                                        ComputeGridConnections();

    //We will set the occupied state of the path nodes based on a particular unit group
    //and have the other groups block tiles depending on their proximity to *this* group...
    //... Keep in mind that the group could be separated from its target path or on the
    //target path...
    void                                        ConfigureGridConnections(UnitGroup *pGroup);
    //Or... we might want to do it without any unit group in consideration...
    //For placement, we don't consider the look-ahead, only the current position...
    void                                        ConfigureGridConnectionsForPlacement();
    
    void                                        OccupyGridForUnit(Unit *pUnit, int pLookAhead=2);

    //This is somewhat expensive on a per-unit basis because we will need to refresh the whole adjacency grid...
    bool                                        CanUnitWalkToAdjacentGridPosition(Unit *pUnit, int pGridX, int pGridY, int pGridZ);
    
    //Scan through all unit groups and see if this unit is leading any of them...
    bool                                        IsLeaderUnit(Unit *pUnit);

    FList                                       mPathList;

    FObjectList                                 mTowerCollection;

    void                                        SpawnUnitsOnPath(FList *pUnitList, LevelPath *pPath, Unit *pLeader=0);
    
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

    void                                        ClearTiles(int pDepth);
    void                                        ClearTiles();

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



    //#define TEST_MODE_NONE 0
    //#define TEST_MODE_UNIT_GROUP_CREATE 1

    int                                         mTestMode;
    int                                         mPreviousTestMode;
    void                                        TestModeDidChange(int pPreviousMode, int pCurrentMode);






};

extern GameArena *gArena;

#endif
