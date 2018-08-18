//
//  MapArena.h
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

//TODO:
// Unit Grid Node connections need to take into consideration
//"funny" corners when drawing up the nodes that we can legally
//walk to...

#ifndef GAME_ARENA_H
#define GAME_ARENA_H

#define TEST_MODE_NONE 0
#define TEST_MODE_UNIT_GROUP_CREATE 1
#define TEST_MODE_UNIT_GROUP_SELECT 2
#define TEST_MODE_UNIT_SELECT 3
#define TEST_MODE_ITEM_CREATE 4
#define TEST_MODE_ITEM_SELECT 5
#define TEST_MODE_UNIT_SPAWN 6

#define DISJOINT_UNIT_BLOCKER_DISTANCE_THRESHOLD 4

#include "GLApp.hpp"
#include "MapTile.hpp"
#include "AnimatedLevelPath.hpp"
#include "UnitPath.hpp"
#include "NodePathFinder.hpp"
#include "Tower.hpp"
#include "TowerBullet.h"
#include "Unit.hpp"
#include "UnitGroup.hpp"
#include "FXML.h"
#include "FObject.h"

#define MAIN_FLOOR 1

//TODO: The end node for each path is never blocked...

class MapGrid;
class MapArena {
public:
    MapArena();
    virtual ~MapArena();

    virtual void                                Update();
    virtual void                                Draw();

    void                                        UpdateBody();

    NodePathFinder                              mTilePathFinder;
    NodePathFinder                              mUnitPathFinder;

    bool                                        mUpdateEnabled;
    int                                         mUpdateSpeedIndex;
    int                                         mUpdateTick;

    void                                        UpdateOneFrame();
    bool                                        mOneFrameUpdateEnqueued;

    MapGrid                                     *mGrid;

    LevelPath                                   *GetPathForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ);
    LevelPath                                   *GetPathForGridPos(int pTileGridX, int pTileGridY, int pTileGridZ);

    void                                        PlaceTower(Tower *pTower);
    bool                                        CanPlaceTower(int pGridX, int pGridY, int pGridZ);

    void                                        RemoveTower(Tower *pTower);
    void                                        RemoveTower(int pGridX, int pGridY, int pGridZ);

    //Assumption: The group is not null, the leader is not null, there is at least one item in the unit list...
    bool                                        Deploy(UnitGroup *pGroup);

    int                                         mCursorGridX;
    int                                         mCursorGridY;
    int                                         mCursorGridZ;

    void                                        RefreshGridCursor(float pX, float pY);

    void                                        DrawGridOverlay();
    void                                        DrawGridSelection();
    void                                        DrawLevelPathCosts();
    void                                        DrawUnitGridPosText();
    void                                        DrawRampConnections();
    void                                        DrawSelectedGroupPath();

    virtual void                                Click(float pX, float pY);

    void                                        TestTouch(float pX, float pY, void *pData);
    void                                        TestDrag(float pX, float pY, void *pData);
    void                                        TestRelease(float pX, float pY, void *pData);
    void                                        TestFlush();

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
    
    
    //Our leader unit was asleep, and we just started walking. Make sure
    //all the minnion follower units are in LEGAL positions, and figure out which
    //ones are clumped up at start node versus not clumped up...
    void                                        UnitDidStartWalkingFromIdle(Unit *pUnit);
    
    

    FList                                       mUnitList;

    FList                                       mUnitGroupList;

    FList                                       mProcessUnitGroupList;

    FList                                       mProcessUnitList;




    FList                                       mAddUnitGroupList;
    
    FList                                       mKillUnitGroupList;
    FList                                       mKillUnitList;

    FList                                       mDeleteUnitGroupList;
    FList                                       mDeleteUnitList;
    
    //UnitGroup

    

    

    //We will set the occupied state of the path nodes based on a particular unit group
    //and have the other groups block tiles depending on their proximity to *this* group...
    //... Keep in mind that the group could be separated from its target path or on the
    //target path...
    void                                        ConfigureGridConnectionsForLeaderDeploy(UnitGroup *pGroup);

    //Or... we might want to do it without any unit group in consideration...
    //For placement, we don't consider the look-ahead, only the current position...
    void                                        ConfigureGridConnectionsForPlacement();
    void                                        ConfigureGridConnectionsIgnoringUnits();
    
    void                                        OccupyGridForUnit(Unit *pUnit, int pLookAhead=2);

    //This is somewhat expensive on a per-unit basis because we will need to refresh the whole adjacency grid...
    bool                                        CanUnitWalkToAdjacentGridPosition(Unit *pUnit, int pGridX, int pGridY, int pGridZ);
    
    
    //Scan through all unit groups and see if this unit is leading any of them...
    bool                                        IsLeaderUnit(Unit *pUnit);

    FList                                       mPathList;

    FObjectList                                 mTowerCollection;

    void                                        SpawnUnitsOnPath(FList *pUnitList, LevelPath *pPath, Unit *pLeader=0);
    

    LevelPath                                   *AttemptPathSelect(float pX, float pY);


    void                                        Save(const char *pPath=0);
    void                                        Load(const char *pPath=0);

    void                                        DeleteSelectedUnit();
    void                                        DeleteSelectedGroup();
    void                                        SplitGroupOnSelectedUnit();

    //#define TEST_MODE_NONE 0
    //#define TEST_MODE_UNIT_GROUP_CREATE 1

    int                                         mTestMode;
    int                                         mPreviousTestMode;
    void                                        TestModeDidChange(int pPreviousMode, int pCurrentMode);


    bool                                        mTestDrawAllNodes;
    bool                                        mTestDrawOccupiedNodes;
    bool                                        mTestDrawOccupiedTiles;
    bool                                        mTestDrawAllConnections;
    bool                                        mTestDrawRampConnections;
    bool                                        mTestDrawSelectedGroupPath;

    float                                       mTestSingleGroupSpawnSpeed;
    float                                       mTestDragGroupSpawnSpeed;

    int                                         mTestDragGroupSpawnTrailerIndex;

    UnitGroup                                   *mTestSelectedGroup;
    Unit                                        *mTestSelectedUnit;
    
    bool                                        mTestGroupShowPath;
    bool                                        mTestGroupShowAllPath;
    
    int                                         mTestUnitGridX;
    int                                         mTestUnitGridY;
    
    float                                       mTestMouseX;
    float                                       mTestMouseY;
    
    //TEST_MODE_UNIT_GROUP_CREATE
};

extern MapArena *gArena;

#endif
