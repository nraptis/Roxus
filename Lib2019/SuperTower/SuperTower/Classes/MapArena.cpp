//
//  MapArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "MapArena.hpp"
#include "MapGrid.hpp"

MapArena *gArena = 0;
MapArena::MapArena() {
    gArena = this;

    mGrid = NULL;

    gTileSize = 72.0f;
    gTileSize2 = gTileSize * 0.5f;
    gPathBendInset45 = (float)((int)gTileSize2 * 0.80f);
    gPathBendInset90 = (float)((int)gTileSize2 * 0.70f);
    
    mCursorGridX = -1;
    mCursorGridY = -1;
    mCursorGridZ = -1;

    mGrid = new MapGrid();

    //Generate(10, 14, 4, 4);
    
    //Expected result: The pathing "works" but ignores ramps and tunnels...
    //Actual result: Inconclusive / no pathing..?

    //Load("super_basic_hifi_path_test");

    //Load("test_level_1");

    Load("test_level_1_mod");

    //Load("map_with_long_path");
    //Load("ramps_test_01.xml");
    
    //Load("pathing_map_02_inverse.xml");
    //Load("45_degree_corners.xml");
    //Load("45_degree_corners_inverse.xml");
    
    //Load("crazy_ramps");
    //Load("crazy_ramps");
    
    //Load("many_wide_ramps");

    mUpdateEnabled = true;
    mUpdateSpeedIndex = 2;
    mUpdateTick = 0;
    mOneFrameUpdateEnqueued = false;

    mTestSelectedUnit = NULL;

    //mTestMode = TEST_MODE_UNIT_GROUP_CREATE;
    mTestMode = TEST_MODE_NONE;
    mPreviousTestMode = mTestMode;

    mTestSelectedGroup = NULL;

    mTestGroupShowPath = true;
    mTestGroupShowAllPath = false;

    mTestSingleGroupSpawnSpeed = 2.0f;
    mTestDragGroupSpawnSpeed = 0.85f;

    mTestDrawAllNodes = false;
    mTestDrawOccupiedNodes = false;
    mTestDrawOccupiedTiles = false;
    mTestDrawAllConnections = false;
    mTestDrawRampConnections = false;
    mTestDrawSelectedGroupPath = true;

    mTestDragGroupSpawnTrailerIndex = 0;

    mTestUnitGridX = -1;
    mTestUnitGridY = -1;
}

MapArena::~MapArena() {
    
}

void MapArena::Update() {

    gGrid->Update();

    if (mTestMode != mPreviousTestMode) {
        TestModeDidChange(mPreviousTestMode, mTestMode);
        mPreviousTestMode = mTestMode;
    }
    
    if (mOneFrameUpdateEnqueued) {
        mUpdateEnabled = false;
        mOneFrameUpdateEnqueued = false;
        UpdateBody();
    } else if(mUpdateEnabled == false) {
        return;
    } else {
        mUpdateTick += 1;
        if (mUpdateSpeedIndex == 0) {
            //Extra Slow...
            if (mUpdateTick >= 25) {
                UpdateBody();
                mUpdateTick = 0;
            }
        }
        
        if (mUpdateSpeedIndex == 1) {
            //Slow...
            if (mUpdateTick >= 5) {
                UpdateBody();
                mUpdateTick = 0;
            }
        }
        
        if (mUpdateSpeedIndex == 2) {
            //Normal Speed
            UpdateBody();
            mUpdateTick = 0;
        }
        
        if (mUpdateSpeedIndex == 3) {
            //Fast Speed
            for (int i=0;i<2;i++) {
                UpdateBody();
            }
            mUpdateTick = 0;
        }
        
        if (mUpdateSpeedIndex == 4) {
            //Extra Fast Speed
            for (int i=0;i<10;i++) {
                UpdateBody();
            }
            mUpdateTick = 0;
        }
    }
}

void MapArena::UpdateBody() {

    
    RefreshUnitGroups();

    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit->mGroup == NULL) {
            printf("Fata Error: Ungrouped unit...\n");
        }
        if (aUnit->mGroup->mUnitList.mCount <= 0) {
            printf("Fata Error: Unit has an empty group, illegal assignment...\n");
        }
    }

    //An important step, here we want to take any unit which is not
    //sleeping and does not have a path / or is not walking, and then
    //we want to do 2 iterations of attempting to re-path, which includes
    //a first step that involves trying a path with near-by units not
    //blocking out path, and then one more iteration where we try to
    //do a path ignoring all other units. Groups that have had too many
    //consecutive failed pathing attempts can be broken apart such that each
    //unit is a group of its own.

    UnitGroup *aBreakApartGroup = NULL;
    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit->mIsLeader == true &&
            aUnit->mIsWalking == false &&
            aUnit->mIsSleeping == false &&
            aUnit->mIsFrozen == false) {

            //TODO: Deploy checks if we are able to walk to the next
            //desired location, otherwise returns false...
            if (Deploy(aUnit->mGroup)) {
                aUnit->mConsecutivePathingFailures = 0;
                printf("Successfully Re-Deployed[%lX]\n", (unsigned long)aUnit);
            } else {
                aUnit->mConsecutivePathingFailures += 1;
                if (aUnit->mConsecutivePathingFailures > 4) {
                    if (aUnit->mGroup != NULL && aUnit->mGroup->Count() > 1) {
                        aBreakApartGroup = aUnit->mGroup;
                    }
                }
                printf("Failed @ Re-Deployed[%lX] (Failures = %d)\n", (unsigned long)aUnit, aUnit->mConsecutivePathingFailures);
                aUnit->Sleep(60);
            }
        }
    }

    if (aBreakApartGroup != NULL) {
        printf("Breaking Apart Group [%lX] (%d Units)\n", (unsigned long)aBreakApartGroup, aBreakApartGroup->Count());

        mProcessUnitList.RemoveAll();

        int aInsertionIndex = mUnitGroupList.Find(aBreakApartGroup);
        EnumListReverse(Unit, aUnit, aBreakApartGroup->mUnitList) {
            aUnit->Halt();
            UnitGroup *aNewGroup = new UnitGroup();
            aNewGroup->AddUnit(aUnit);
            mUnitGroupList.Insert(aNewGroup, aInsertionIndex);
            mProcessUnitList.Add(aUnit);
        }
        aBreakApartGroup->Kill();
        EnumListReverse(Unit, aUnit, mProcessUnitList) {
            Deploy(aUnit->mGroup);
        }
    }

    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit->mIsLeader) { aUnit->Update(); }
    }

    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit->mIsLeader == false) { aUnit->Update(); }
    }

    mTowerCollection.Update();
    EnumList (AnimatedLevelPath, aPath, mPathList) { aPath->Update(); }
    
    //TODO: Handing off the path to the next unit in the group...
    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit->mDidReachEndOfPath) {
            //Todo: Poof animation..
            aUnit->Kill();
        }
    }
    RefreshUnitGroups();
    
    //TODO: Update bullets.
    //REQUIRE: no units can be killed on this update after THIS point...
    SplitUnitGroups();
    KillAllInvalidUnitGroups();
    
    ///////////////////////////////////////////
    ////                                   ////
    ////      Remove killed units..        ////
    
    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit->mKill) {
            //When the unit is killed, saely remove from all groups...
            EnumList(UnitGroup, aGroup, mUnitGroupList) {
                aGroup->RemoveUnit(aUnit);
            }
            mKillUnitList.Add(aUnit);
        }
    }

    mDeleteUnitList.RemoveAll();

    EnumList(Unit, aUnit, mKillUnitList) {
        if (aUnit == mTestSelectedUnit) {
            mTestSelectedUnit = NULL;
        }
        mUnitList.Remove(aUnit);
        aUnit->mKill--;
        if (aUnit->mKill <= 0) {
            mDeleteUnitList.Add(aUnit);
        }
    }
    EnumList(Unit, aUnit, mDeleteUnitList) {
        mKillUnitList.Remove(aUnit);
        delete aUnit;
    }
    
    ////                                   ////
    ////                                   ////
    ///////////////////////////////////////////
    
    
    ///////////////////////////////////////////
    ////                                   ////
    ////     Remove killed groups..        ////
    
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        //Group became empty, kill it...
        if (aGroup->mUnitList.mCount <= 0) {
            aGroup->Kill();
        }
        if (aGroup->mKill) {
            mKillUnitGroupList.Add(aGroup);
        }
    }

    mDeleteUnitGroupList.RemoveAll();
    EnumList(UnitGroup, aGroup, mKillUnitGroupList) {
        if (aGroup == mTestSelectedGroup) {
            mTestSelectedGroup = NULL;
        }
        mUnitGroupList.Remove(aGroup);
        aGroup->mKill--;
        if (aGroup->mKill <= 0) {
            mDeleteUnitGroupList.Add(aGroup);
        }
    }
    
    EnumList(UnitGroup, aGroup, mDeleteUnitGroupList) {
        mKillUnitGroupList.Remove(aGroup);
        delete aGroup;
    }

    ////                                   ////
    ////                                   ////
    ///////////////////////////////////////////
}

void MapArena::Draw() {
    Graphics::SetColor();
    
    

    EnumList (AnimatedLevelPath, aPath, mPathList) {
        aPath->DrawPrepare();
    }

    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        
        if (mGrid->mTileVisible[aDepth]) {
            Graphics::SetColor();
            if (gApp->mDarkMode) {
                Graphics::SetColor(0.125f, 0.125f, 0.125f, mGrid->mTileOpacity[aDepth]);
            } else {
                Graphics::SetColor(mGrid->mTileOpacity[aDepth]);
            }
            
            for (int aX=0;aX<mGrid->mTileGridWidthTotal;aX++) {
                for (int aY=0;aY<mGrid->mTileGridHeightTotal;aY++) {
                    MapTile *aTile = mGrid->mTile[aDepth][aX][aY];
                    if (aTile) { aTile->Draw(); }
                }
            }
        }
         
        
        
        
        EnumList (AnimatedLevelPath, aPath, mPathList) {
            aPath->Draw(aDepth);
        }
        
        EnumList(Tower, aTower, mTowerCollection.mObjectList) {
            if (aTower->mKill == 0 && aTower->mGridZ == aDepth) {
                aTower->Draw();
            }
        }

        EnumList(Unit, aUnit, mUnitList) {
            if (aUnit->mKill == 0 && aUnit->mGridZ == aDepth) {
                aUnit->Draw();
            }
        }
        

        //DrawUnitGridPosText();

        if (aDepth == 1) {

            //EnumList(Tower, aTower, mTowerList)
            //{
            //    aTower->Draw();
            //}
            
            //mTowerCollection.Draw();
            
            //TODO: Fix this
            /*
             if (gGame->mTowerPickerMenu.mCurrentTower) {
             if (mCursorGridX != -1 && mCursorGridY != -1 && mCursorGridZ != -1) {
             gGame->mTowerPickerMenu.mCurrentTower->SetUp(mCursorGridX, mCursorGridY, mCursorGridZ);
             gGame->mTowerPickerMenu.mCurrentTower->Draw();
             }
             }
             */
        }
    }
    
    Graphics::SetColor();
    
    
    

    //DrawLevelPathConnections();

    //Graphics::SetColor();
    //gApp->mNinja.Center(mTestNinjaRotation, mTestNinjaFrame, 0.0f, 0.0f);
    
    //Graphics::SetColor();
    //mTestUnitPath.DrawMarkers();

    
    //Graphics::SetColor(1.0f, 0.5f, 0.66f, 0.25f);
    //Graphics::DrawPoint(mTestMouseX, mTestMouseY, 40.0f);

    
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (aGroup != mTestSelectedGroup) {
            aGroup->DrawConnections(false);
        }
    }
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (aGroup == mTestSelectedGroup) {
            aGroup->DrawConnections(true);
        }
    }
    
    //DrawPathableNodes();
    //DrawLevelPathCosts();

    Graphics::SetColor();

    if (mTestDrawAllNodes) { mGrid->DrawAllNodes(); }
    if (mTestDrawAllConnections) { mGrid->DrawAllConnections(); }
    if (mTestDrawOccupiedNodes) { mGrid->DrawOccupiedNodes(); }
    if (mTestDrawOccupiedTiles) { mGrid->DrawOccupiedTiles(); }
    if (mTestDrawRampConnections) { mGrid->DrawAllConnections(); }

    if (mTestDrawSelectedGroupPath) {
        DrawSelectedGroupPath();
    }

    if (mTestSelectedGroup) {
        EnumListReverse(Unit, aUnit, mTestSelectedGroup->mUnitList) {
            float aSelectionSize = 14.0f;
            float aSelectionWidth = 2.0f;
            if (aUnit == mTestSelectedGroup->Leader()) {
                aSelectionSize = 18.0f;
                aSelectionWidth = 3.0f;

                Graphics::SetColor(0.67f, 0.25f, 0.25f, 0.85f);
                if (gApp->mDarkMode) {
                    Graphics::SetColor(0.67f, 0.25f, 0.25f, 0.15f);
                }

            } else {
                Graphics::SetColor(0.2f, 0.22f, 0.65f, 0.85f);
                if (gApp->mDarkMode) {
                    Graphics::SetColor(0.2f, 0.22f, 0.65f, 0.15f);
                }
            }
            Graphics::OutlineRect(aUnit->mX - aSelectionSize / 2.0f, aUnit->mY - aSelectionSize / 2.0f, aSelectionSize, aSelectionSize, aSelectionWidth);
        }
    }

    int aGroupIndex = 0;

    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (gApp->mDarkMode) {
            Graphics::SetColorSwatch(aGroupIndex, 0.06f);
        } else {
            Graphics::SetColorSwatch(aGroupIndex, 0.325f);
        }
        EnumList(Unit, aUnit, aGroup->mUnitList) {
            float aX = aUnit->mX;
            float aY = aUnit->mY;
            Graphics::OutlineRectInside(aX - 9.0f, aY - 11.0f, 18.0f, 22.0f, 6.0f);
        }
        aGroupIndex++;
    }

    if (mTestSelectedUnit != NULL) {
        float aX = mTestSelectedUnit->mX;
        float aY = mTestSelectedUnit->mY;
        if (gApp->mDarkMode) {
            Graphics::SetColor(0.66f, 0.66f, 0.125f, 0.10f);
        } else {
            Graphics::SetColor(0.66f, 0.66f, 0.125f, 0.55f);
        }
        Graphics::OutlineRectInside(aX - 15.0f, aY - 25.0f, 31.0f, 51.0f, 5.0f);
        Graphics::SetColor();
    }
}

void MapArena::DrawUnitGridPosText() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        int aShiftIndex = 0;
        int aDidEncounterUnwalking = 0;
        EnumList(Unit, aUnit, mUnitList) {
            if (aUnit->mKill == 0 && aUnit->mGridZ == aDepth) {
                if (aUnit->mDidStartWalking == false) {
                    aDidEncounterUnwalking++;
                }
                if (aDidEncounterUnwalking <= 1) {
                    if (aShiftIndex == 0)
                        aUnit->DrawGridPosInfo(-20);
                    if (aShiftIndex == 1)
                        aUnit->DrawGridPosInfo(0);
                    if (aShiftIndex == 2)
                        aUnit->DrawGridPosInfo(20);
                    aShiftIndex++;
                    if (aShiftIndex >= 3) {
                        aShiftIndex = 0;
                    }
                }
            }
        }
    }
}

void MapArena::DrawRampConnections() {

}

void MapArena::DrawSelectedGroupPath() {
    if (mTestSelectedGroup) {
        Unit *aLeader = mTestSelectedGroup->Leader();
        if (aLeader != NULL && aLeader->mPath != NULL) {
            aLeader->mPath->DrawMarkers();
        }
    }
}

void MapArena::DrawLevelPathCosts() {
    for (int a=0;a<mTilePathFinder.mOpenListCount;a++) {
        PathNodeConnection *aOpenCon = mTilePathFinder.mOpenListData[a];
        int aGridX = aOpenCon->mNode->mGridX;
        int aGridY = aOpenCon->mNode->mGridY;
        int aGridZ = aOpenCon->mNode->mGridZ;
        MapTile *aTile = mGrid->GetTile(aGridX, aGridY, aGridZ);
        if (aTile) {
            Graphics::SetColor(0.15f);
            gApp->mUnitCircleSoft.Center(aTile->mCenterX, aTile->mCenterY);
        }
    }

    for (int a=0;a<mTilePathFinder.mClosedListTableSize;a++) {
        PathNodeConnection *aClosedCon = mTilePathFinder.mClosedListTableData[a];
        while (aClosedCon != NULL) {
            int aGridX = aClosedCon->mNode->mGridX;
            int aGridY = aClosedCon->mNode->mGridY;
            int aGridZ = aClosedCon->mNode->mGridZ;
            MapTile *aTile = mGrid->GetTile(aGridX, aGridY, aGridZ);
            if (aTile) {
                Graphics::SetColor(0.15f);
                gApp->mUnitCircleHard.Center(aTile->mCenterX, aTile->mCenterY);
            }
            aClosedCon = aClosedCon->mClosedHashTableNext;
        }
    }
}

void MapArena::DrawGridOverlay() {
    int aDrawIndex = 0;
    for (int aX = 0;aX < mGrid->mTileGridWidthTotal;aX++) {
        for (int aY = 0;aY < mGrid->mTileGridHeightTotal;aY++) {
            int aTopDepth = 0;
            for (int aDepth = 0;aDepth<GRID_DEPTH;aDepth++) {
                MapTile *aTile = mGrid->GetTile(aX, aY, aDepth);
                if (aTile) { aTopDepth = aDepth; }
            }
            if (mGrid->mTowerAllowed[aX][aY]) {
                float aCenterX = CX(aX, aTopDepth);
                float aCenterY = CY(aY, aTopDepth);
                if(aX & 1)aDrawIndex = 0;
                else aDrawIndex = 1;
                if(aY & 1)aDrawIndex = !aDrawIndex;
                gApp->mGridOverlay[aDrawIndex].Center(aCenterX, aCenterY);
            }
        }
    }
}

void MapArena::DrawGridSelection() {
    if ((mCursorGridX != -1) && (mCursorGridY != -1) && mCursorGridZ != -1) {
        float aLeft = mCursorGridX * gTileSize;
        float aTop = mCursorGridY * gTileSize;
        Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.25f);
        Graphics::DrawRect(0.0f, aTop, gArenaWidth, gTileSize);
        Graphics::DrawRect(aLeft, 0.0f, gTileSize, gArenaHeight);
    }
}

void MapArena::RemoveTower(Tower *pTower) {
    if (pTower) {
        pTower->Kill();
        mGrid->ComputePathConnections();
    }
}

void MapArena::RemoveTower(int pGridX, int pGridY, int pGridZ) {
    RemoveTower(GetTower(pGridX, pGridY, pGridZ));
}

void MapArena::PlaceTower(Tower *pTower) {
    if (pTower) {
        mTowerCollection.Add(pTower);
        mGrid->ComputePathConnections();
    }
}

bool MapArena::CanPlaceTower(int pGridX, int pGridY, int pGridZ) {
    bool aResult = false;
    MapTile *aTile = mGrid->GetTile(pGridX, pGridY, pGridZ);
    if (aTile != NULL) {
        if (mGrid->mTowerAllowed[pGridX][pGridY]) {
            aResult = true;
        }
    }
    return aResult;
}

LevelPath *MapArena::AttemptPathSelect(float pX, float pY) {
    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;
    mGrid->GetEditorGridPos(pX, pY, aGridX, aGridY, aGridZ);
    LevelPath *aSelectedPath = 0;
    if (aGridX != -1 && aGridY != -1 && aGridZ != -1) {
        EnumList(LevelPath, aPath, mPathList) {
            if (aPath->mStartX == aGridX && aPath->mStartY == aGridY && aPath->mStartZ == aGridZ) {
                aSelectedPath = aPath;
            }
            if (aPath->mEndX == aGridX && aPath->mEndY == aGridY && aPath->mEndZ == aGridZ) {
                aSelectedPath = aPath;
            }
        }
        if (aSelectedPath == 0) {
            EnumList(LevelPath, aPath, mPathList) {
                for (int i=0;i<aPath->mLength;i++) {
                    int aPathGridX = aPath->mPathX[i];
                    int aPathGridY = aPath->mPathY[i];
                    int aPathGridZ = aPath->mPathZ[i];
                    if (aPathGridX == aGridX && aPathGridY == aGridY && aPathGridZ == aGridZ) {
                        aSelectedPath = aPath;
                    }
                }
            }
        }
    }
    if (aSelectedPath == 0) {
        aSelectedPath = 0;
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            mGrid->GetEditorGridPosAtDepth(pX, pY, aDepth, aGridX, aGridY);
            EnumList(LevelPath, aPath, mPathList) {
                if (aPath->mStartX == aGridX && aPath->mStartY == aGridY && aPath->mStartZ == aDepth) {
                    aSelectedPath = aPath;
                }
                if (aPath->mEndX == aGridX && aPath->mEndY == aGridY && aPath->mEndZ == aDepth) {
                    aSelectedPath = aPath;
                }
            }
            if (aSelectedPath == 0) {
                EnumList(LevelPath, aPath, mPathList) {
                    for (int i=0;i<aPath->mLength;i++) {
                        int aPathGridX = aPath->mPathX[i];
                        int aPathGridY = aPath->mPathY[i];
                        int aPathGridZ = aPath->mPathZ[i];
                        if (aPathGridX == aGridX && aPathGridY == aGridY && aPathGridZ == aDepth) {
                            aSelectedPath = aPath;
                        }
                    }
                }
            }
        }
    }
    return aSelectedPath;
}



void MapArena::SpawnUnitsOnPath(FList *pUnitList, LevelPath *pPath, Unit *pLeader) {
    
    ConfigureGridConnectionsForPlacement();
    
    if (pPath == NULL) {
        printf("Fatal Error: Spawning units on Null path...\n");
        return;
    }
    
    if (pUnitList == NULL) {
        printf("Null unit list...\n");
        return;
    }
    
    if (pUnitList->mCount <= 0) {
        printf("Empty unit list...\n");
        return;
    }
    
    MapTile *aEndTile = mGrid->GetEndTileForPath(pPath);
    if (aEndTile == NULL) {
        printf("Fatal Error: No end tile...\n");
        return;
    }
    
    PathNode *aEndNode = mGrid->GetEndNodeForPath(pPath);
    if (aEndNode == NULL) {
        printf("Fatal Error: No end node...\n");
        return;
    }
    
    PathNode *aStartNode = mGrid->GetStartNodeForPath(pPath);
    if (aStartNode == NULL) {
        printf("Fatal Error: No start node...\n");
        return;
    }
    
    printf("Spawning On Path [%s] From (%d %d %d) => (%d %d %d)\n", pPath->mName.c(),
           pPath->mStartX, pPath->mStartY, pPath->mStartZ,
           pPath->mEndX, pPath->mEndY, pPath->mEndZ);
    
    aStartNode->mOccupiedByUnit = true;
    printf("Spawning At Node [%d %d %d]\n", aStartNode->mGridX, aStartNode->mGridY, aStartNode->mGridZ);
    
    if (pLeader != 0) {
        pUnitList->MoveToFirst(pLeader);
    }

    UnitGroup *aGroup = new UnitGroup();
    EnumList(Unit, aUnit, *pUnitList) {
        aUnit->PlaceOnGrid(aStartNode, aEndNode, aEndTile, pPath);
        aGroup->AddUnit(aUnit);
        mUnitList.Add(aUnit);
    }

    aGroup->SetDeploySpeed(mTestSingleGroupSpawnSpeed);

    mUnitGroupList.Add(aGroup);

    Deploy(aGroup);
}

//Send the group along the way!!!
bool MapArena::Deploy(UnitGroup *pGroup) {

    if (pGroup == NULL) {
        printf("Fatal Error: Null unit group...\n");
        return false;
    }
    
    Unit *aLeader = pGroup->Leader();
    if (aLeader == NULL) {
        printf("Fatal Error: Null leader for unit group...\n");
        return false;
    }
    
    PathNode *aEndNode = mGrid->GetEndNodeForTile(aLeader->mDestinationTile);
    if (aEndNode == NULL) {
        printf("Fatal Error: Unable to find end node for unit's destination tile...\n");
        return false;
    }
    
    if (pGroup->mUnitList.mCount <= 0) {
        printf("Fatal Error: Unit group with empty list...\n");
        return false;
    }
    
    if (aLeader->mTrackingPath == NULL) {
        printf("Fatal Error: Unit leader has no tracking path...\n");
        return false;
    }
    
    if (aLeader->mPath == NULL) {
        aLeader->mPath = new UnitPath();
    }
    
    pGroup->Refresh();
    
    ConfigureGridConnectionsForLeaderDeploy(pGroup);

    UnitPath *aPath = aLeader->mPath;

    //Assumption: The unit's position is the tile that we are walking TO...
    // .. May have delayed reaction, e.g. finish walking to tile and then start this new path...

    int aStartX = aLeader->mGridX, aStartY = aLeader->mGridY, aStartZ = aLeader->mGridZ;
    int aEndX = aEndNode->mGridX, aEndY = aEndNode->mGridY, aEndZ = aEndNode->mGridZ;
    
    aPath->mStartX = aStartX;aPath->mStartY = aStartY;aPath->mStartZ = aStartZ;
    aPath->mEndX = aEndX;aPath->mEndY = aEndY;aPath->mEndZ = aEndZ;
    
    aPath->ComputePath(this);
    aLeader->mPathIndex = 0;

    if (aPath->mLength <= 0) {
        ConfigureGridConnectionsIgnoringUnits();
        aPath->ComputePath(this);
    }
    
    if (aPath->mLength > 0) {
        if (aPath->mLength == 1) {
            return true;
        } else {
            if (CanUnitWalkToAdjacentGridPosition(aLeader, aPath->mPathX[1], aPath->mPathY[1], aPath->mPathZ[1])) {
                aLeader->Flash(40, 3);
                return true;
            } else {
                return false;
            }
        }
    }

    return false;

}

//Our leader unit was asleep, and we just started walking. Make sure
//all the minnion follower units are in LEGAL positions, and figure out which
//ones are clumped up at start node versus not clumped up...
void MapArena::UnitDidStartWalkingFromIdle(Unit *pUnit) {
    if (pUnit != NULL && pUnit->mGroup != NULL) {
        UnitGroup *aGroup = pUnit->mGroup;
        Unit *aLeader = aGroup->Leader();
        if (aGroup->Count() > 1 && aLeader == pUnit) {
            
            int aLeaderPrevX = aLeader->mPrevGridX;
            int aLeaderPrevY = aLeader->mPrevGridY;
            int aLeaderPrevZ = aLeader->mPrevGridZ;
            
            Unit *aSecondUnit = (Unit *)(aGroup->mUnitList.Fetch(1));
            if (aSecondUnit->mGridX == aLeaderPrevX
                && aSecondUnit->mGridY == aLeaderPrevY
                && aSecondUnit->mGridZ == aLeaderPrevZ) {
                //This is the class of unit group with a clumping trail...
                
                for (int i=1;i<aGroup->mUnitList.mCount;i++) {
                    Unit *aUnit = (Unit *)(aGroup->mUnitList.mData[i]);
                    aUnit->mDidStartWalking = false;
                    aUnit->mIsWalking = false;
                    aUnit->mGridX = aLeaderPrevX;
                    aUnit->mGridY = aLeaderPrevY;
                    aUnit->mGridZ = aLeaderPrevZ;
                }
            } else {
                //This is the class of unit group with at least partial
                //previous arrangement along path...
                
                int aFirstNonAdjacentIndex = -1;
                Unit *aPrevUnit = aLeader;
                
                //The leader will be one tick ahead of the "expected" pos because
                //he has already started the walk and is assumed to be on the next
                //path tile...
                int aPrevGridX = aLeader->mPrevGridX;
                int aPrevGridY = aLeader->mPrevGridY;
                int aPrevGridZ = aLeader->mPrevGridZ;
                
                for (int i=1;i<aGroup->mUnitList.mCount && aFirstNonAdjacentIndex == -1;i++) {
                    Unit *aUnit = (Unit *)(aGroup->mUnitList.mData[i]);

                    if (mGrid->UnitGridPositionsAreAdjacentAndNotEqual(aPrevGridX, aPrevGridY, aPrevGridZ, aUnit->mGridX, aUnit->mGridY, aUnit->mGridZ)) {

                        aUnit->mPrevGridX = aPrevGridX;
                        aUnit->mPrevGridY = aPrevGridY;
                        aUnit->mPrevGridZ = aPrevGridZ;

                        aPrevGridX = aUnit->mGridX;
                        aPrevGridY = aUnit->mGridY;
                        aPrevGridZ = aUnit->mGridZ;
                        
                        aPrevUnit = aUnit;
                        
                    } else {
                        aFirstNonAdjacentIndex = i;
                    }
                }

                //This is the most common case - we have a "placed" group in a uniform string..
                if (aFirstNonAdjacentIndex == -1) {
                    printf("Expected Case 2!\n");
                    for (int i=1;i<aGroup->mUnitList.mCount;i++) {
                        Unit *aUnit = (Unit *)(aGroup->mUnitList.mData[i]);
                        aUnit->mIsWalking = true;
                        aUnit->mDidStartWalking = true;
                    }
                } else {
                    printf("aFirstNonAdjacentIndex = %d ...\n", aFirstNonAdjacentIndex);
                    for (int i=1;i<aFirstNonAdjacentIndex;i++) {
                        Unit *aUnit = (Unit *)(aGroup->mUnitList.mData[i]);
                        aUnit->mIsWalking = true;
                        aUnit->mDidStartWalking = true;
                    }
                }
                UnitDidFinishWalkingStep(aLeader);
            }

            float aOvershootPercent = aLeader->mStepPercent;
            printf("Starting Walk... [%lX] Prev[%d %d %d] Cur[%d %d %d]\n", (unsigned long)aLeader, aLeader->mPrevGridX, aLeader->mPrevGridY, aLeader->mPrevGridZ, aLeader->mGridX, aLeader->mGridY, aLeader->mGridZ);

            //Rule 1: Anything not on the leader's position, but adjacent to the
            //previously iterated unit is considered to have started walking and
            //to be walking.
            
            //Rule 2: Once we find 2 units in a row that are on the same position, the second
            //of such units and ALL trailing units are considered to have not started walking,
            
            //Rule 3: Once we find a unit which is not adjacent to the previous unit's position,
            //that unit and all trailing units snap to the PREVIOUS unit's position...

            //Here we know the unit is the leader AND at index 0...
            //Therefore we can "reverse bubble" the previous positions
            //to the other units following leader unit...
            
            /*
             Unit *aPrevUnit = aLeader;
             
             bool aDidEncounterNonMovingUnit = false;
             for (int i=1;i<aGroup->mUnitList.mCount && aDidEncounterNonMovingUnit==false;i++) {
             Unit *aUnit = (Unit *)(aGroup->mUnitList[i]);
             if (aUnit->mDidStartWalking == false) {
             aDidEncounterNonMovingUnit = true;
             } else {
             //SNAP unit into position, prepare to follow leader...
             if (aUnit->mDidStartWalking) {
             aUnit->ForceCompleteCurrentWalkPathSegment();
             }
             
             aUnit->mPrevGridX = aUnit->mGridX;
             aUnit->mPrevGridY = aUnit->mGridY;
             aUnit->mPrevGridZ = aUnit->mGridZ;
             }
             aPrevUnit = aUnit;
             }
             
             int aGridX = aLeader->mPrevGridX;
             int aGridY = aLeader->mPrevGridY;
             int aGridZ = aLeader->mPrevGridZ;
             
             //It's possible that one of the middle segments becomes blocked as
             //we are walking along.
             int aBlockedIndex = -1;
             //Unit *aPrevUnit = aLeader;
             
             bool aDidSendNonMovingUnitAlongPath = false;
             for (int i=1;i<aGroup->mUnitList.mCount && aBlockedIndex == -1 && aDidSendNonMovingUnitAlongPath == false;i++) {
             Unit *aUnit = (Unit *)(aGroup->mUnitList[i]);
             if (CanUnitWalkToAdjacentGridPosition(aUnit, aGridX, aGridY, aGridZ)) {
             if (aUnit->mDidStartWalking == false) {
             aDidSendNonMovingUnitAlongPath = true;
             }
             aUnit->FollowToNextPathSegment(aGridX, aGridY, aGridZ, aOvershootPercent);
             } else {
             aBlockedIndex = i;
             }
             
             aGridX = aUnit->mPrevGridX;
             aGridY = aUnit->mPrevGridY;
             aGridZ = aUnit->mPrevGridZ;
             
             }
             
             if (aBlockedIndex != -1) {
             //Separate everything out from the block index on backwards.
             }
             */
        }
    }
}

void MapArena::UnitDidFinishWalkingStep(Unit *pUnit) {
    if (pUnit != NULL && pUnit->mGroup != NULL) {
        UnitGroup *aGroup = pUnit->mGroup;
        Unit *aLeader = aGroup->Leader();
        if (aGroup->Count() > 1 && aLeader == pUnit) {
            
            float aOvershootPercent = aLeader->mStepPercent;
            //printf("Advancing [%lX] Prev[%d %d %d] Cur[%d %d %d]\n", (unsigned long)aLeader, aLeader->mPrevGridX, aLeader->mPrevGridY, aLeader->mPrevGridZ, aLeader->mGridX, aLeader->mGridY, aLeader->mGridZ);

            
            //Here we know the unit is the leader AND at index 0...
            //Therefore we can "reverse bubble" the previous positions
            //to the other units following leader unit...
            
            Unit *aPrevUnit = aLeader;
            
            bool aDidEncounterNonMovingUnit = false;
            for (int i=1;i<aGroup->mUnitList.mCount && aDidEncounterNonMovingUnit==false;i++) {
                Unit *aUnit = (Unit *)(aGroup->mUnitList[i]);
                if (aUnit->mDidStartWalking == false) {
                    aDidEncounterNonMovingUnit = true;
                } else {
                    //SNAP unit into position, prepare to follow leader...
                    if (aUnit->mDidStartWalking) {
                        aUnit->ForceCompleteCurrentWalkPathSegment();
                    }
                    
                    aUnit->mPrevGridX = aUnit->mGridX;
                    aUnit->mPrevGridY = aUnit->mGridY;
                    aUnit->mPrevGridZ = aUnit->mGridZ;
                }
                aPrevUnit = aUnit;
            }

            int aGridX = aLeader->mPrevGridX;
            int aGridY = aLeader->mPrevGridY;
            int aGridZ = aLeader->mPrevGridZ;
            
            //It's possible that one of the middle segments becomes blocked as
            //we are walking along.
            int aSplitIndex = -1;
            //Unit *aPrevUnit = aLeader;
            
            bool aDidSendNonMovingUnitAlongPath = false;
            bool aDidEncounterNonWalkingUnit = false;

            for (int i=1;i<aGroup->mUnitList.mCount && aSplitIndex == -1 && aDidSendNonMovingUnitAlongPath == false;i++) {
                Unit *aUnit = (Unit *)(aGroup->mUnitList[i]);
                if (CanUnitWalkToAdjacentGridPosition(aUnit, aGridX, aGridY, aGridZ)) {
                    if (aUnit->mDidStartWalking == false) {
                        aDidSendNonMovingUnitAlongPath = true;
                    }
                    aUnit->FollowToNextPathSegment(aGridX, aGridY, aGridZ, aOvershootPercent);
                } else {
                    if (aUnit->mDidStartWalking == false) {
                        aDidEncounterNonWalkingUnit = true;
                    }

                    //If we reached the bunch at the end of the chain,
                    //then we do not split the group..
                    if (aDidEncounterNonWalkingUnit == false) {
                        aSplitIndex = i;
                    }
                }
                aGridX = aUnit->mPrevGridX;
                aGridY = aUnit->mPrevGridY;
                aGridZ = aUnit->mPrevGridZ;
            }
            
            if (aSplitIndex != -1) {

                //Separate everything out from the block index on backwards.
                if (aSplitIndex == 0) {
                    printf("Fatal Error: We are supposing that block index is somewhere in the middle for group split..\n");
                    return;
                }

                //Theory: this is a safe time to split this group because...
                //we can only get here from the unit list updating, not
                //while we are doing an iteration through groups..

                //So we split the group into two here and reset the "sleep" timers
                //on new leader units, re-path (second group only...) ... ... .. ...

                //Also, try to keep the units from the original group in their group
                //and do not disrupt fluid motion, split group 2 and insert directly
                //after the original group...

                //UnitGroup *aGroup1 = new UnitGroup();
                //for (int i=0;i<aBlockedIndex;i++) {
                //    aGroup1->AddUnit((Unit *)(aGroup->mUnitList.mData[i]));
                //}
                //mUnitGroupList.Add(aGroup1);

                //mUnitGroupList.RemoveAllAfter()

                UnitGroup *aNewGroup = new UnitGroup();
                for (int i=aSplitIndex;i<aGroup->mUnitList.mCount;i++) {
                    aNewGroup->AddUnit((Unit *)(aGroup->mUnitList.mData[i]));
                }

                //mUnitGroupList.Add(aNewGroup);

                int aPreCount = aGroup->mUnitList.mCount;

                aGroup->mUnitList.RemoveAllAtOrAfter(aSplitIndex);

                int aInsertionIndex = mUnitGroupList.Find(aGroup);
                mUnitGroupList.Insert(aNewGroup, aInsertionIndex);

                printf("Blockers Forces Group Split PC[%d] -- G[%d] NG[%d]\n\n", aPreCount, aGroup->mUnitList.mCount, aNewGroup->mUnitList.mCount);
            }
        }
    }
}

void MapArena::SplitUnitGroups() {
    bool aReloop = true;
    do {
        aReloop = TrySplitUnitGroups();
    } while (aReloop);
}

bool MapArena::TrySplitUnitGroups() {
    
    bool aResult = false;
    int aUnitGroupCountBefore = mUnitGroupList.mCount;
    
    mAddUnitGroupList.RemoveAll();
    mProcessUnitGroupList.RemoveAll();
    
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (aGroup->mKill == 0) {
            mProcessUnitGroupList.Add(aGroup);
        }
    }
    
    EnumList(UnitGroup, aGroup, mProcessUnitGroupList) {
        if (TrySplitUnitGroup(aGroup)) {
            aResult = true;
        }
    }
    
    EnumList(UnitGroup, aGroup, mAddUnitGroupList) {
        mUnitGroupList.Add(aGroup);
    }
    mAddUnitGroupList.RemoveAll();
    
    KillAllInvalidUnitGroups();
    RemoveKilledUnitGroups();
    
    if (aResult == true) {
        printf("Unit Groups Split Before: %d Groups, After: %d Groups\n", aUnitGroupCountBefore, mUnitGroupList.mCount);
    }
    
    
    
    return aResult;
}

//We only want to perform one split each time we encounter this method...
//new groups get added to mAddUnitGroupList, defunct groups get killed (not deleted)
bool MapArena::TrySplitUnitGroup(UnitGroup *pGroup) {
    if (pGroup == NULL) return false;
    if (pGroup->mUnitList.mCount <= 1) return false;
    Unit *aLeader = pGroup->Leader();
    Unit *aUnit = NULL;
    int aSplitIndex = -1;
    for (int aIndex=0;aIndex<pGroup->mUnitList.mCount;aIndex++) {
        aUnit = (Unit *)(pGroup->mUnitList.mData[aIndex]);
        if (aUnit->ShouldResignLeadership()) {
            aSplitIndex = aIndex;
        }
    }
    
    if (aSplitIndex != -1) {
        if ((aSplitIndex + 1) < pGroup->mUnitList.mCount) {
            UnitGroup *aGroup = new UnitGroup();
            mAddUnitGroupList.Add(aGroup);
            for (int aIndex=aSplitIndex+1;aIndex<pGroup->mUnitList.mCount;aIndex++) {
                aUnit = (Unit *)(pGroup->mUnitList.mData[aIndex]);
                aGroup->AddUnit(aUnit);
            }
            Unit *aNewLeader = aGroup->Leader();
            HandOffPath(aLeader, aNewLeader);
        }
        
        if (true) {
            UnitGroup *aGroup = new UnitGroup();
            mAddUnitGroupList.Add(aGroup);
            aUnit = (Unit *)(pGroup->mUnitList.mData[aSplitIndex]);
            aGroup->AddUnit(aUnit);
            HandOffPath(aLeader, aUnit);
        }
        
        if (aSplitIndex > 0) {
            UnitGroup *aGroup = new UnitGroup();
            mAddUnitGroupList.Add(aGroup);
            for (int aIndex=aSplitIndex;aIndex<aSplitIndex;aIndex++) {
                aUnit = (Unit *)(pGroup->mUnitList.mData[aIndex]);
                aGroup->AddUnit(aUnit);
            }
            Unit *aNewLeader = aGroup->Leader();
            HandOffPath(aLeader, aNewLeader);
        }
        
        pGroup->Kill();
        pGroup->mUnitList.RemoveAll();
        
        return true;
    }
    
    //We could have SEVERAL slowed units, in a row, which would stay in a group together...
    //Basically...
    
    /*
     //If a unit has fallen to a slower speed and is in the middle of the group, split the group accordingly...
     /// [f][f][s][f]
     /// => 3 new groups...
     EnumList(UnitGroup, aGroup, mUnitGroupList) {
     if (aGroup->mKill == false) {
     }
     }
     
     //If a Leader unit should resign leadership, add the leader to a new group and re-organize accordingly
     EnumList(UnitGroup, aGroup, mUnitGroupCollection.mObjectList) {
     Unit *aLeader = aGroup->mLeader;
     if (aGroup->mKill == false && aLeader != 0) {
     if (aLeader->ShouldResignLeadership()) {
     //
     }
     }
     }
     */
    
    return false;
}

void MapArena::HandOffPath(Unit *pFromUnit, Unit *pToUnit) {
    if ((pFromUnit != NULL) && (pToUnit != NULL) && (pFromUnit != pToUnit)) {
        pToUnit->AttemptCopyPathFromUnit(pFromUnit);
    }
}


void MapArena::KillAllInvalidUnitGroups() {
    
}

void MapArena::RemoveKilledUnitGroups() {
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (aGroup->mKill) {
            mKillUnitGroupList.Add(aGroup);
        }
    }
    EnumList(UnitGroup, aGroup, mKillUnitGroupList) {
        mUnitGroupList.Remove(aGroup);
    }
}

void MapArena::RefreshUnitGroups() {
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        aGroup->Refresh();
    }
}




void MapArena::DeleteSelectedUnit() {

}

void MapArena::DeleteSelectedGroup() {

}

void MapArena::SplitGroupOnSelectedUnit() {

}


void MapArena::Click(float pX, float pY) {

    Unit *aPickedUnit = NULL;
    float aBestDistance = 90.0f * 90.0f;
    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit->mKill == false) {
            float aDist = Distance(pX, pY, aUnit->mX, aUnit->mY);
            if (aDist < aBestDistance) {
                aBestDistance = aDist;
                aPickedUnit = aUnit;
            }
        }
    }

    if (mTestMode == TEST_MODE_NONE) {
        
        int aGridX = -1;
        int aGridY = -1;
        int aGridZ = -1;
        mGrid->GetGridPos(pX, pY, aGridX, aGridY, aGridZ);
        if (aGridX != -1 && aGridY != -1 && aGridZ != -1) {
            if (CanPlaceTower(aGridX, aGridY, aGridZ)) {
                Tower *aTower = GetTower(aGridX, aGridY, aGridZ);
                if (aTower == 0) {
                    aTower = new Tower();
                    aTower->SetUp(aGridX, aGridY, aGridZ);
                    mTowerCollection.Add(aTower);
                } else {
                    aTower->Kill();
                }
            }
        }
        
        //int aDepth = 1;
        
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int aX=0;aX<mGrid->mTileGridWidthTotal;aX++) {
                for (int aY=0;aY<mGrid->mTileGridHeightTotal;aY++) {
                    MapTile *aTile = mGrid->GetTile(aGridX, aGridY, aDepth);
                    if (aTile) {
                        aTile->mBlocked = false;
                        if (GetTower(aX, aY, aDepth)) {
                            aTile->mBlocked = true;
                        }
                    }
                }
            }
        }
        mGrid->ComputePathConnections();
    } else if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        
    } else if (mTestMode == TEST_MODE_UNIT_GROUP_SELECT) {
        mTestSelectedGroup = NULL;
        if (aPickedUnit) {
            mTestSelectedGroup = aPickedUnit->mGroup;
        }
    } else if (mTestMode == TEST_MODE_UNIT_SELECT) {
        mTestSelectedUnit = NULL;
        if (aPickedUnit) {
            mTestSelectedUnit = aPickedUnit;
        }

    } else if (mTestMode == TEST_MODE_ITEM_CREATE) {
        
    } else if (mTestMode == TEST_MODE_ITEM_SELECT) {
        
    } else if (mTestMode == TEST_MODE_UNIT_SPAWN) {
        
        if (true) { //Unit Tests
            LevelPath *aSelectedPath = AttemptPathSelect(pX, pY);
            if (aSelectedPath) {
                //Spawn some test units.
                int aSpawnCount = 2;
                FList aUnitList;
                for (int aUnitIndex=0;aUnitIndex<aSpawnCount;aUnitIndex++) {
                    Unit *aUnit = new Unit();
                    aUnit->mWalkSpeed = 1.5f;
                    aUnitList.Add(aUnit);
                }
                
                printf("Selected Path: {%s}\n", aSelectedPath->mName.c());
                
                SpawnUnitsOnPath(&aUnitList, aSelectedPath);
            }
        }
    } //TEST_MODE_UNIT_SPAWN
    
    
    
}

void MapArena::TestTouch(float pX, float pY, void *pData) {
    mTestMouseX = pX;
    mTestMouseY = pY;
    
    ConfigureGridConnectionsForPlacement();
    
    printf("Test Touch: %f %f\n", pX, pY);
    if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        
        PathNode *aNode = mGrid->GetClosestNode(pX, pY, false, false, true);
        if (aNode) {
            LevelPath *aLevelPath = GetPathForNode(aNode->mGridX, aNode->mGridY, aNode->mGridZ);
            if (aLevelPath != NULL) {

                mTestSelectedGroup = new UnitGroup();
                mUnitGroupList += mTestSelectedGroup;

                Unit *aLeaderUnit = new Unit();
                mTestSelectedGroup->AddUnit(aLeaderUnit);
                mUnitList += aLeaderUnit;

                aLeaderUnit->mIsFrozen = true;

                PathNode *aEndNode = mGrid->GetEndNodeForPath(aLevelPath);
                PathNode *aStartNode = aNode;
                MapTile *aEndTile = mGrid->GetEndTileForPath(aLevelPath);
                
                aLeaderUnit->PlaceOnGrid(aStartNode, aEndNode, aEndTile, aLevelPath);
                aNode->mOccupiedByUnit = true;
            }
        }
    }
}

void MapArena::TestDrag(float pX, float pY, void *pData) {
    mTestMouseX = pX;
    mTestMouseY = pY;
    
    ConfigureGridConnectionsForPlacement();
    
    if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        if (mTestSelectedGroup != NULL) {
            Unit *aLastUnit = (Unit *)(mTestSelectedGroup->mUnitList.Last());
            PathNode *aNode = mGrid->GetClosestNode(pX, pY, false, false, true);
            if (aNode != NULL && aLastUnit != NULL) {
                LevelPath *aLevelPath = GetPathForNode(aNode->mGridX, aNode->mGridY, aNode->mGridZ);

                if (aLevelPath != NULL && mGrid->UnitGridPositionsAreAdjacent(aLastUnit->mGridX, aLastUnit->mGridY, aLastUnit->mGridZ, aNode->mGridX, aNode->mGridY, aNode->mGridZ)) {

                    Unit *aAddUnit = new Unit();
                    aAddUnit->mIsFrozen = true;

                    mTestSelectedGroup->AddUnit(aAddUnit);
                    mUnitList += aAddUnit;

                    PathNode *aEndNode = mGrid->GetEndNodeForPath(aLevelPath);
                    PathNode *aStartNode = aNode;
                    MapTile *aEndTile = mGrid->GetEndTileForPath(aLevelPath);
                    
                    aAddUnit->PlaceOnGrid(aStartNode, aEndNode, aEndTile, aLevelPath);
                    aNode->mOccupiedByUnit = true;
                }
            }
        }
    }
}

void MapArena::TestRelease(float pX, float pY, void *pData) {
    if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        if (mTestSelectedGroup != NULL) {
            if (mTestSelectedGroup->mUnitList.mCount <= 0) {
                mTestSelectedGroup->Kill();
            } else {

                int aExtraSpawn = 0;
                if (mTestDragGroupSpawnTrailerIndex == 1) { aExtraSpawn = 1; }
                if (mTestDragGroupSpawnTrailerIndex == 2) { aExtraSpawn = 3; }
                if (mTestDragGroupSpawnTrailerIndex == 3) { aExtraSpawn = 5; }
                if (mTestDragGroupSpawnTrailerIndex == 4) { aExtraSpawn = 10; }
                
                printf("Spawning an extra %d units at end...\n", aExtraSpawn);

                Unit *aLastUnit = ((Unit *)mTestSelectedGroup->mUnitList.Last());
                PathNode *aNode = mGrid->GetGridNode(aLastUnit->mGridX, aLastUnit->mGridY, aLastUnit->mGridZ);
                if (aNode != NULL && aLastUnit != NULL) {
                    LevelPath *aLevelPath = GetPathForNode(aNode->mGridX, aNode->mGridY, aNode->mGridZ);
                    PathNode *aEndNode = aLastUnit->mDestinationNode;

                    if (aLevelPath != NULL && aEndNode != NULL) {
                        for (int i=0;i<aExtraSpawn;i++) {
                            Unit *aAddUnit = new Unit();
                            mTestSelectedGroup->AddUnit(aAddUnit);
                            mUnitList += aAddUnit;

                            PathNode *aStartNode = aNode;
                            MapTile *aEndTile = mGrid->GetEndTileForPath(aLevelPath);

                            aAddUnit->PlaceOnGrid(aStartNode, aEndNode, aEndTile, aLevelPath);
                            aNode->mOccupiedByUnit = true;
                        }
                    }
                }

                EnumList(Unit, aUnit, mTestSelectedGroup->mUnitList) {
                    aUnit->mIsFrozen = false;
                }

                //Speed...
                mTestSelectedGroup->SetDeploySpeed(mTestDragGroupSpawnSpeed);
                Deploy(mTestSelectedGroup);

            }
        }
    }
}

void MapArena::TestFlush() {
    //Swirl and swirl and down the toilet the waste goes.

}





LevelPath *MapArena::GetPathForGridPos(int pTileGridX, int pTileGridY, int pTileGridZ) {
    LevelPath *aResult = NULL;
    EnumList(AnimatedLevelPath, aPath, mPathList) {
        for (int i=0;i<aPath->mLength;i++) {
            int aGridX = aPath->mPathX[i];
            int aGridY = aPath->mPathY[i];
            int aGridZ = aPath->mPathZ[i];
            if (aGridX == pTileGridX && aGridY == pTileGridY && aGridZ == pTileGridZ) {
                aResult = aPath;
            }
        }
    }
    return aResult;
}

LevelPath *MapArena::GetPathForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ) {
    LevelPath *aResult = NULL;
    FList aTileList;
    mGrid->GetAllTilesForNode(pUnitGridX, pUnitGridY, pUnitGridZ, &aTileList);
    EnumList(MapTile, aTile, aTileList) {
        if (aResult == NULL) {
            aResult = GetPathForGridPos(aTile->mGridX, aTile->mGridY, aTile->mGridZ);
        }
    }
    return aResult;
}






void MapArena::RefreshGridCursor(float pX, float pY) {
    
    /*
     mCursorGridX = GetGridX(pX);
     mCursorGridY = GetGridY(pY);
     mCursorGridZ
     
     //If one if out of bounds, they both are!
     if ((mCursorGridX == -1) || (mCursorGridY == -1)) {
     mCursorGridX = -1;
     mCursorGridY = -1;
     }
     */
    
}

Tower *MapArena::GetTower(int pGridX, int pGridY, int pGridZ) {
    Tower *aResult = 0;
    EnumList(Tower, aTower, mTowerCollection.mObjectList) {
        if (aTower->mKill == 0) {
            if (aTower->mGridX == pGridX && aTower->mGridY == pGridY && aTower->mGridZ == pGridZ) {
                aResult = aTower;
            }
        }
    }
    return aResult;
}

void MapArena::AddUnit(Unit *pUnit, LevelPath *pPath) {
    if (pUnit) {
        FList aUnitList;
        aUnitList.Add(pUnit);
        SpawnUnitsOnPath(&aUnitList, pPath);
    }
}

void MapArena::ConfigureGridConnectionsForLeaderDeploy(UnitGroup *pGroup) {
    mGrid->ResetGridConnections();
    if (pGroup != NULL && pGroup->mKill == 0) {

        Unit *aLeader = pGroup->Leader();
        if (aLeader != NULL) {
            mGrid->UnblockAllNodesForTile(aLeader->mDestinationTile);

            int aGridX = 0;
            int aGridY = 0;
            int aDiffX = 0;
            int aDiffY = 0;
            int aLeaderGridX = aLeader->mGridX;
            int aLeaderGridY = aLeader->mGridY;

            EnumList(Unit, aUnit, mUnitList) {
                if (pGroup->ContainsUnit(aUnit) == false) {
                    aGridX = aUnit->mGridX;
                    aGridY = aUnit->mGridY;
                    aDiffX = aGridX - aLeaderGridX;
                    if (aDiffX < 0) { aDiffX = -aDiffX; }
                    aDiffY = aGridY - aLeaderGridY;
                    if (aDiffY < 0) { aDiffY = -aDiffY; }

                    //We only block the grid with close units...
                    if (aDiffX < DISJOINT_UNIT_BLOCKER_DISTANCE_THRESHOLD &&
                        aDiffY < DISJOINT_UNIT_BLOCKER_DISTANCE_THRESHOLD) {
                        OccupyGridForUnit(aUnit);
                    }
                }
            }


            PathNode *aNode = 0;

            //Make sure the destination tile is not occupied (it can't be occupied)
            MapTile *aDestinationTile = aLeader->mDestinationTile;
            if (aDestinationTile != NULL) {
                int aStartGridX = aDestinationTile->mGridX * SUBDIVISIONS_PER_TILE;
                int aStartGridY = aDestinationTile->mGridY * SUBDIVISIONS_PER_TILE;
                int aGridZ = aDestinationTile->mGridZ;
                for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                    int aGridX = aStartGridX + aOffsetX;
                    for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                        int aGridY = aStartGridY + aOffsetY;
                        aNode = mGrid->GetGridNode(aGridX, aGridY, aGridZ);
                        aNode->mOccupiedByUnit = false;
                        aNode->mOccupiedByTower = false;
                        aNode->mOccupiedByItem = false;
                    }
                }
            }
        }
    }
    mGrid->ComputeGridConnections();
}

void MapArena::ConfigureGridConnectionsForPlacement() {
    mGrid->ResetGridConnections();
    EnumList(Unit, aUnit, mUnitList) {
        OccupyGridForUnit(aUnit, 0);
    }
    mGrid->ComputeGridConnections();
}

void MapArena::ConfigureGridConnectionsIgnoringUnits() {
    mGrid->ResetGridConnections();
    mGrid->ComputeGridConnections();
}

void MapArena::OccupyGridForUnit(Unit *pUnit, int pLookAhead) {
    if (pUnit) {
        //If the unit is a leader unit, we consider the path...

        int aGridX = pUnit->mGridX;
        int aGridY = pUnit->mGridY;
        int aGridZ = pUnit->mGridZ;
        
        PathNode *aNode = mGrid->GetGridNode(aGridX, aGridY, aGridZ);
        if (aNode) {
            aNode->mOccupiedByUnit = true;
        }
        if (IsLeaderUnit(pUnit)) {
            UnitPath *aPath = pUnit->mPath;
            if (aPath != NULL && aPath->mLength > 0) {
                int aPathIndex = pUnit->GetCurrentPathIndex();
                if (aPathIndex != -1) {
                    aPathIndex += 1;
                    int aLoops = pLookAhead;
                    while (aLoops > 0 && aPathIndex < aPath->mLength) {
                        aGridX = aPath->mPathX[aPathIndex];
                        aGridY = aPath->mPathY[aPathIndex];
                        aGridZ = aPath->mPathZ[aPathIndex];
                        aNode = mGrid->GetGridNode(aGridX, aGridY, aGridZ);
                        if (aNode) {
                            aNode->mOccupiedByUnit = true;
                        }
                        aPathIndex++;
                        aLoops--;
                    }
                }
            }
        }
    }
}

bool MapArena::CanUnitWalkToAdjacentGridPosition(Unit *pUnit, int pGridX, int pGridY, int pGridZ) {
    if (pUnit) {

        //TODO: Just for leader unit, the units in our group do not block us..?
        ConfigureGridConnectionsForPlacement();

        int aGridX = pUnit->mGridX;
        int aGridY = pUnit->mGridY;
        int aGridZ = pUnit->mGridZ;
        if (mGrid->UnitGridPositionsAreAdjacent(aGridX, aGridY, aGridZ, pGridX, pGridY, pGridZ)) {

            PathNode *aNode = mGrid->GetGridNode(pGridX, pGridY, pGridZ);
            MapTile *aEndTile = pUnit->mDestinationTile;

            if (aEndTile ==  NULL) {
                printf("Fatal Error: End tile can't be null for any unit...\n");
            }

            if (mGrid->IsNodeOnTile(aNode, aEndTile)) {
                return true;
            }

            int aDiffX = pGridX - aGridX;
            if (aDiffX < 0) { aDiffX = -aDiffX; }

            int aDiffY = pGridY - aGridY;
            if (aDiffY < 0) { aDiffY = -aDiffY; }

            //We are walking diagonal on a flat plane.
            if ((pGridZ == aGridZ) && (aDiffX == 1) && (aDiffY == 1)) {

                //We must consider whether or not the 2
                //corner nodes are blocked...

                PathNode *aCornerNode1 = mGrid->GetGridNode(pGridX, aGridY, aGridZ);
                PathNode *aCornerNode2 = mGrid->GetGridNode(aGridX, pGridY, aGridZ);

                //TODO: Resolve the corner clipping situation.
                //Speculation: We should only allow corner nodes to be blocked
                //from units that are outside of the unit in consideration's grp.

                if (aCornerNode1 != NULL && aCornerNode2 != NULL) {
                    if (aCornerNode1->IsBlocked() == true && aCornerNode2->IsBlocked() == true) {
                        printf("Failing adjacent transfer because of CORNER blockers...\n");
                        return false;
                    }
                }


                //if (aCornerNode1 != NULL) {
                //    if (aCornerNode1->IsBlocked() == true) {
                //        printf("Corner Clipping Case 1...\n");
                //        bool aIsUnitFromOutOfGroupOnNode = false;
                        //return false;
                //    }
                //}

                if (aCornerNode2 != NULL) {
                    if (aCornerNode2->IsBlocked() == true) {
                        printf("Corner Clipping Case 2...\n");
                        //return false;
                    }
                }

                /*
                 // [p0] [b0]
                 // [b1] [p1]
                 if (aGridX < pGridX && aGridY < pGridY) {
                 aCornerNode1 = GetGridNode(pGridX, aGridY, aGridZ);
                 aCornerNode2 = GetGridNode(aGridX, pGridY, aGridZ);
                 }

                 // [b0] [p1]
                 // [p0] [b1]
                 else if (aGridX < pGridX && aGridY > pGridY) {
                 aCornerNode1 = GetGridNode(aGridX, pGridY, aGridZ);
                 aCornerNode2 = GetGridNode(pGridX, aGridY, aGridZ);
                 }

                 // [p1] [b0]
                 // [b1] [p0]
                 else if (aGridX > pGridX && aGridY > pGridY) {
                 aCornerNode1 = GetGridNode(aGridX, pGridY, aGridZ);
                 aCornerNode2 = GetGridNode(pGridX, aGridY, aGridZ);
                 }

                 // [b0] [p0]
                 // [p1] [b1]
                 else {//if (aGridX < pGridX && aGridY > pGridY) {
                 aCornerNode1 = GetGridNode(aGridX, pGridY, aGridZ);
                 aCornerNode2 = GetGridNode(pGridX, aGridY, aGridZ);
                 }
                 */
            }


            //Make sure grid position is unblocked and unoccupied.

            if (aNode) {
                if (aNode->IsBlocked() == false) {
                    return true;
                }
            }
        }
    }
    return false;
}


bool MapArena::IsLeaderUnit(Unit *pUnit) {
    bool aResult = false;
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (aGroup->mKill == 0 && aGroup->IsLeader(pUnit)) {
            return true;
        }
    }
    return aResult;
}

void MapArena::UpdateOneFrame() {
    mOneFrameUpdateEnqueued = true;
    mUpdateEnabled = false;
}

void MapArena::Save(const char *pPath) {
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    aPath = (gDirDocuments + aPath);
    
    FXML aXML;
    
    FXMLTag *aArenaTag = new FXMLTag("game_arena");
    aXML.mRoot = aArenaTag;

    mGrid->Save(aArenaTag);

    FXMLTag *aPathListTag = new FXMLTag("path_list");
    *aArenaTag += aPathListTag;
    EnumList (AnimatedLevelPath, aPath, mPathList) {
        *aPathListTag += aPath->Save();
    }

    aXML.Print();
    aXML.Save(aPath.c());
}

void MapArena::Load(const char *pPath) {
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    
    FXML aXML;
    aXML.Load(aPath);
    FreeList(AnimatedLevelPath, mPathList);
    FXMLTag *aArenaTag = aXML.GetRoot();
    
    mGrid->Load(aArenaTag);

    if (aArenaTag) {
        int aPathIndex = 1;
        EnumTagsMatching (aArenaTag, aPathListTag, "path_list") {
            EnumTags (aPathListTag, aPathTag) {
                AnimatedLevelPath *aPath = new AnimatedLevelPath();
                aPath->Load(aPathTag);
                mPathList += aPath;

                aPath->mName = FString("level_path_") + FString(aPathIndex);
                aPathIndex += 1;
            }
        }
    }

    mGrid->RefreshUnitGridNodes();
    mGrid->ComputeTowerAllowedPlacements();
    mGrid->ComputePathConnections();
    
}

void MapArena::TestModeDidChange(int pPreviousMode, int pCurrentMode) {
    
}



