//
//  GameArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "GameArena.hpp"

GameArena *gArena = 0;
GameArena::GameArena() {
    gArena = this;
    
    
    gTileSize = 72.0f;
    gTileSize2 = gTileSize * 0.5f;
    gPathBendInset45 = (float)((int)gTileSize2 * 0.80f);
    gPathBendInset90 = (float)((int)gTileSize2 * 0.70f);
    
    mCursorGridX = -1;
    mCursorGridY = -1;
    mCursorGridZ = -1;
    
    mTileGridWidthTotal = 0;
    mTileGridHeightTotal = 0;
    
    mTileGridWidthActive = 0;
    mTileGridHeightActive = 0;
    
    mTileGridBufferH = 0;
    mTileGridBufferV = 0;
    
    mTile = 0;
    mTowerAllowed = 0;
    
    mWalkAllowed = 0;
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mTileVisible[aDepth] = true;
        mTileOpacity[aDepth] = 1.0f;
    }
    
    mUnitGrid = 0;
    mUnitGridBase = 0;
    
    mUnitGridWidth = 0;
    mUnitGridHeight = 0;
    
    //Generate(10, 14, 4, 4);
    
    //Expected result: The pathing "works" but ignores ramps and tunnels...
    //Actual result: Inconclusive / no pathing..?
    
    //Load("super_basic_hifi_path_test");
    
    //Load("test_level_1");
    
    //Load("test_level_1_mod");
    
    
    Load("map_with_long_path");
    
    
    //Load("ramps_test_01.xml");
    
    //Load("pathing_map_02_inverse.xml");
    //Load("45_degree_corners.xml");
    //Load("45_degree_corners_inverse.xml");
    
    //Load("crazy_ramps");
    //Load("crazy_ramps");
    
    //Load("many_wide_ramps");
    
    mTestNinjaRotation = 0.0f;
    mTestNinjaFrame = 0.0f;
    
    
    mUpdateEnabled = true;
    mUpdateSpeedIndex = 2;
    mUpdateTick = 0;
    mOneFrameUpdateEnqueued = false;
    
    
    
    //mTestMode = TEST_MODE_UNIT_GROUP_CREATE;
    mTestMode = TEST_MODE_NONE;
    mPreviousTestMode = mTestMode;
    
    mTestCreateGroup = 0;
    mTestSelectedGroup = 0;
    
    mTestGroupShowPath = true;
    mTestGroupShowAllPath = false;
    
    mTestUnitGridX = -1;
    mTestUnitGridY = -1;
}

GameArena::~GameArena() {
    gArena = 0;
}

void GameArena::Update() {
    
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

void GameArena::UpdateBody() {
    
    float aMaxFrame = (float)gApp->mNinja.mSequenceFrameCount;
    
    mTestNinjaFrame += 1.4125;
    if(mTestNinjaFrame >= aMaxFrame) { mTestNinjaFrame -= aMaxFrame; }
    
    if (mDeletedTileList.mCount > 0) {
        EnumList(GameTile, aTile, mDeletedTileList) {
            delete aTile;
        }
        mDeletedTileList.RemoveAll();
    }
    
    if (mDeletedNodeList.mCount > 0) {
        EnumList(PathNode, aNode, mDeletedNodeList) {
            delete aNode;
        }
        mDeletedNodeList.RemoveAll();
    }
    
    RefreshUnitGroups();
    
    EnumList(Unit, aUnit, mUnitList) { aUnit->Update(); }
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
        if (aGroup == mTestCreateGroup) {
            mTestCreateGroup = NULL;
        }
        if (aGroup == mTestSelectedGroup) {
            mTestSelectedGroup == NULL;
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

void GameArena::Draw() {
    Graphics::SetColor();
    
    EnumList (AnimatedLevelPath, aPath, mPathList) {
        aPath->DrawPrepare();
    }
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        if (mTileVisible[aDepth]) {
            Graphics::SetColor();
            if (gApp->mDarkMode) {
                Graphics::SetColor(0.125f, 0.125f, 0.125f, mTileOpacity[aDepth]);
            } else {
                Graphics::SetColor(mTileOpacity[aDepth]);
            }
            
            for (int aX=0;aX<mTileGridWidthTotal;aX++) {
                for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                    GameTile *aTile = mTile[aDepth][aX][aY];
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
    
    
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        
        if (gApp->mDarkMode) {
            Graphics::SetColorSwatch(aDepth, 0.075f);
        } else {
            Graphics::SetColorSwatch(aDepth, 0.5f);
        }
        
        for (int aGridX=0;aGridX<mTileGridWidthTotal;aGridX++) {
            for (int aGridY=0;aGridY<mTileGridHeightTotal;aGridY++) {
                GameTile *aTile1 = mTile[aDepth][aGridX][aGridY];
                if (aTile1) {
                    for (int i=0;i<aTile1->mPathConnectionCount;i++) {
                        //PathNode *aConnectedNode = aTile1->mPathConnection[i].mNode;
                        //Graphics::DrawArrow(aTile1->mCenterX, aTile1->mCenterY, aConnectedNode->mCenterX, aConnectedNode->mCenterY);
                    }
                }
            }
        }
        
        
        
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];
                for (int i=0;i<aNode->mPathConnectionCount;i++) {
                    PathNode *aConnectedNode = aNode->mPathConnection[i].mNode;
                    
                    if (aNode->mGridZ != aConnectedNode->mGridZ) {
                        
                        float aX1 = aNode->mCenterX;
                        float aY1 = aNode->mCenterY;
                        
                        float aX2 = aConnectedNode->mCenterX;
                        float aY2 = aConnectedNode->mCenterY;
                        
                        if ((aGridX % 2) == 1) {
                            aX1 -= 5.0f;
                        }
                        
                        if ((aGridY % 2) == 1) {
                            aY1 -= 5.0f;
                        }
                        
                        Graphics::DrawArrow(aX1, aY1, aX2, aY2, 4.0f, 0.5f);
                        
                    }
                }
            }
        }
    }
    
    
    //TODO: Start Grid Depth = 1
    /*
     for (int aDepth=1;aDepth<GRID_DEPTH;aDepth++) {
     for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
     for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
     PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];
     if (aNode->mBlocked == false) {
     Graphics::SetColor(0.95f, 0.95f, 0.95f, mTileOpacity[aDepth]);
     Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 3.0f);
     if (aDepth == 0) {
     Graphics::SetColor(1.0f, 0.75f, 0.25f, mTileOpacity[aDepth]);
     }
     if (aDepth == 1) {
     Graphics::SetColor(0.125f, 0.75f, 0.75f, mTileOpacity[aDepth]);
     }
     if (aDepth == 2) {
     Graphics::SetColor(0.855f, 0.125f, 0.85f, mTileOpacity[aDepth]);
     }
     if (aNode->mOccupied) {
     Graphics::SetColor(1.0f, 0.125f, 0.125f, mTileOpacity[aDepth]);
     }
     Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 1.5f);
     }
     }
     }
     }
     */
    
    
    
    //Graphics::SetColor();
    //gApp->mNinja.Center(mTestNinjaRotation, mTestNinjaFrame, 0.0f, 0.0f);
    
    Graphics::SetColor();
    mTestUnitPath.DrawMarkers();
    
    Graphics::SetColor(1.0f, 0.5f, 0.66f, 0.25f);
    Graphics::DrawPoint(mTestMouseX, mTestMouseY, 40.0f);
    
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
    
    DrawPathableNodes();
    
}

void GameArena::DrawPathableNodes() {
    
    ConfigureGridConnectionsForPlacement();
    
    if (gApp->mDarkMode == false) {
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
                for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                    PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];
                    LevelPath *aPath = GetPathForNode(aNode->mGridX, aNode->mGridY, aNode->mGridZ);
                    
                    if (aNode->mBlocked == false && aPath != NULL) {
                        if (aNode->mOccupied == false) {
                            Graphics::SetColor(0.95f, 0.95f, 0.95f, mTileOpacity[aDepth]);
                            Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 3.0f);
                            
                        } else {
                            Graphics::SetColor(0.025f, 0.025f, 0.025f, mTileOpacity[aDepth]);
                            Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 3.0f);
                            
                        }
                        
                        if (aDepth == 0) {
                            Graphics::SetColor(1.0f, 0.75f, 0.25f, mTileOpacity[aDepth]);
                        }
                        if (aDepth == 1) {
                            Graphics::SetColor(0.125f, 0.75f, 0.75f, mTileOpacity[aDepth]);
                        }
                        if (aDepth == 2) {
                            Graphics::SetColor(0.855f, 0.125f, 0.85f, mTileOpacity[aDepth]);
                        }
                        if (aNode->mOccupied) {
                            Graphics::SetColor(0.45f, 0.25f, 0.22f, mTileOpacity[aDepth]);
                        }
                        Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 1.5f);
                    }
                }
            }
        }
    }
    
}

void GameArena::DrawGridOverlay() {
    int aDrawIndex = 0;
    for (int aX = 0;aX < mTileGridWidthTotal;aX++) {
        for (int aY = 0;aY < mTileGridHeightTotal;aY++) {
            int aTopDepth = 0;
            for (int aDepth = 0;aDepth<GRID_DEPTH;aDepth++) {
                GameTile *aTile = GetTile(aX, aY, aDepth);
                if (aTile) { aTopDepth = aDepth; }
            }
            
            if (mTowerAllowed[aX][aY]) {
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

void GameArena::DrawGridSelection() {
    if ((mCursorGridX != -1) && (mCursorGridY != -1) && mCursorGridZ != -1) {
        float aLeft = mCursorGridX * gTileSize;
        float aTop = mCursorGridY * gTileSize;
        Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.25f);
        Graphics::DrawRect(0.0f, aTop, gArenaWidth, gTileSize);
        Graphics::DrawRect(aLeft, 0.0f, gTileSize, gArenaHeight);
    }
}

void GameArena::ResizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {
    
}

float GameArena::GetUnitGridX(int pGridX, int pGridY, int pGridZ) {
    float aResult = 0.0f;
    if (pGridX >= 0 && pGridX < mUnitGridWidth && pGridY >= 0 && pGridY < mUnitGridHeight && pGridZ >= 0 && pGridZ < GRID_DEPTH) {
        PathNode *aNode = mUnitGrid[pGridZ][pGridX][pGridY];
        aResult = aNode->mCenterX;
    }
    return aResult;
}

float GameArena::GetUnitGridY(int pGridX, int pGridY, int pGridZ) {
    float aResult = 0.0f;
    if (pGridX >= 0 && pGridX < mUnitGridWidth && pGridY >= 0 && pGridY < mUnitGridHeight && pGridZ >= 0 && pGridZ < GRID_DEPTH) {
        PathNode *aNode = mUnitGrid[pGridZ][pGridX][pGridY];
        aResult = aNode->mCenterY;
    }
    return aResult;
}

void GameArena::ComputeAllowedPlacements() {
    int aMaxX = mTileGridBufferH + mTileGridWidthActive;
    int aMaxY = mTileGridBufferV + mTileGridHeightActive;
    GameTile *aTile = 0;
    for (int aX=0;aX<mTileGridWidthTotal;aX++) {
        for (int aY=0;aY<mTileGridHeightTotal;aY++) {
            mTowerAllowed[aX][aY] = false;
            if (aX >= mTileGridBufferH && aY >= mTileGridBufferV && aX < aMaxX && aY < aMaxY) {
                aTile = mTile[MAIN_FLOOR][aX][aY];
                if (aTile) {
                    if (mTile[2][aX][aY] == 0) {
                        if (aTile->PlacementAllowed()) {
                            mTowerAllowed[aX][aY] = true;
                        }
                    }
                }
            }
        }
    }
}

void GameArena::RemoveTower(Tower *pTower) {
    if (pTower) {
        pTower->Kill();
        ComputePathConnections();
    }
}

void GameArena::RemoveTower(int pGridX, int pGridY, int pGridZ) {
    RemoveTower(GetTower(pGridX, pGridY, pGridZ));
}

void GameArena::DeleteTile(int pGridX, int pGridY, int pGridZ) {
    GameTile *aTile = GetTile(pGridX, pGridY, pGridZ);
    if (aTile) {
        mDeletedTileList += aTile;
        mTile[pGridZ][pGridX][pGridY] = 0;
    }
}

void GameArena::PlaceTower(Tower *pTower) {
    if (pTower) {
        mTowerCollection.Add(pTower);
        ComputePathConnections();
        
        //Update unit paths...
        
        //TODO:
        //mTowers.SortAscendingY();
        
        /*
         if(mTowerList.Exists(pTower) == false)
         {
         mTowerList += pTower;
         pTower->SetUp(mCursorGridX, mCursorGridY);
         
         
         
         ComputePathConnections();
         EnumList(Unit, aUnit, mUnitList)
         {
         aUnit->ComputePath();
         }
         }
         */
    }
}

bool GameArena::CanPlaceTower(int pGridX, int pGridY, int pGridZ) {
    bool aResult = false;
    if (pGridX >= 0 && pGridX < mTileGridWidthTotal && pGridY >= 0 && pGridY < mTileGridHeightTotal && pGridZ >= 0 && pGridZ < GRID_DEPTH) {
        aResult = true;
    }
    return aResult;
}

bool GameArena::CanPlaceTower() {
    return CanPlaceTower(mCursorGridX, mCursorGridY, 1);
}

GameTile *GameArena::GetTile(int pGridX, int pGridY, int pGridZ) {
    GameTile *aResult = 0;
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mTileGridWidthTotal) && (pGridY < mTileGridHeightTotal) && (pGridZ < GRID_DEPTH)) {
        aResult = mTile[pGridZ][pGridX][pGridY];
    }
    return aResult;
}

PathNode *GameArena::GetGridNode(int pGridX, int pGridY, int pGridZ) {
    PathNode *aResult = 0;
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mUnitGridWidth) && (pGridY < mUnitGridHeight) && (pGridZ < GRID_DEPTH)) {
        aResult = mUnitGrid[pGridZ][pGridX][pGridY];
    }
    return aResult;
}

void GameArena::GetGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ) {
    pGridX = -1;
    pGridY = -1;
    pGridZ = -1;
    int aGridX = -1;
    if (pX > 0) {
        aGridX = (int)(pX / gTileSize);
        if (aGridX >= mTileGridWidthTotal) {
            aGridX = -1;
        }
    }
    if (aGridX != -1) {
        int aGridY = -1;
        GameTile *aTile = 0;
        int aLandGridY = (int)(pY / gTileSize);
        float aCenterY = 0.0f;
        float aEpsilon = 0.01f;
        float aTop = 0.0f;
        float aBottom = 0.0f;
        for (int aDepth=GRID_DEPTH-1;aDepth>=0;aDepth--) {
            aGridY = aLandGridY - 1;
            for (int k=0;k<3;k++) {
                aTile = GetTile(aGridX, aGridY, aDepth);
                if (aTile != 0) {
                    if (aTile->IsRamp() == false) {
                        aCenterY = CY(aGridY, aDepth);
                        aTop = aCenterY - (gTileSize2 + aEpsilon);
                        aBottom = aCenterY + (gTileSize2 + aEpsilon);
                        if (pY >= aTop && pY <= aBottom) {
                            pGridX = aGridX;
                            pGridY = aGridY;
                            pGridZ = aDepth;
                            return;
                        }
                    }
                }
                aGridY += 1;
            }
        }
    }
}

void GameArena::GetEditorGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ) {
    pGridX = -1;
    pGridY = -1;
    pGridZ = -1;
    int aGridX = -1;
    if (pX > 0) {
        aGridX = (int)(pX / gTileSize);
        if (aGridX >= mTileGridWidthTotal) {
            aGridX = -1;
        }
    }
    
    if (aGridX != -1) {
        int aGridY = -1;
        GameTile *aTile = 0;
        int aLandGridY = (int)(pY / gTileSize);
        float aCenterY = 0.0f;
        float aEpsilon = 0.01f;
        float aTop = 0.0f;
        float aBottom = 0.0f;
        for (int aDepth=GRID_DEPTH-1;aDepth>=0;aDepth--) {
            aGridY = aLandGridY - 1;
            for (int k=0;k<3;k++) {
                aTile = GetTile(aGridX, aGridY, aDepth);
                if (aTile != 0) {
                    aCenterY = CY(aGridY, aDepth);
                    aTop = aCenterY - (gTileSize2 + aEpsilon);
                    aBottom = aCenterY + (gTileSize2 + aEpsilon);
                    if (pY >= aTop && pY <= aBottom) {
                        pGridX = aGridX;
                        pGridY = aGridY;
                        pGridZ = aDepth;
                        return;
                    }
                }
                aGridY += 1;
            }
        }
    }
}

void GameArena::GetEditorGridPosAtDepth(float pX, float pY, int pDepth, int &pGridX, int &pGridY) {
    pGridX = -1;
    pGridY = -1;
    if (pDepth >= 0 && pDepth < GRID_DEPTH) {
        int aGridX = -1;
        if (pX > 0) {
            aGridX = (int)(pX / gTileSize);
            if (aGridX >= mTileGridWidthTotal) {
                aGridX = -1;
            }
        }
        if (aGridX != -1) {
            int aGridY = -1;
            int aLandGridY = (int)(pY / gTileSize);
            float aCenterY = 0.0f;
            float aEpsilon = 0.01f;
            float aTop = 0.0f;
            float aBottom = 0.0f;
            aGridY = aLandGridY - 1;
            for (int k=0;k<3;k++) {
                aCenterY = CY(aGridY, pDepth);
                aTop = aCenterY - (gTileSize2 + aEpsilon);
                aBottom = aCenterY + (gTileSize2 + aEpsilon);
                if (pY >= aTop && pY <= aBottom) {
                    pGridX = aGridX;
                    pGridY = aGridY;
                    return;
                }
                aGridY += 1;
            }
        }
    }
}

LevelPath *GameArena::AttemptPathSelect(float pX, float pY) {
    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;
    GetEditorGridPos(pX, pY, aGridX, aGridY, aGridZ);
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
            GetEditorGridPosAtDepth(pX, pY, aDepth, aGridX, aGridY);
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

void GameArena::DumpLevelPathToTileList(LevelPath *pPath) {
    mTileList.RemoveAll();
    if (pPath) {
        GameTile *aStartTile = GetTile(pPath->mStartX, pPath->mStartY, pPath->mStartZ);
        if (aStartTile) {
            mTileList.Add(aStartTile);
        }
        int aCap = (pPath->mLength-1);
        for (int i=1;i<aCap;i++) {
            GameTile *aTile = GetTile(pPath->mPathX[i], pPath->mPathY[i], pPath->mPathZ[i]);
            if (aTile) {
                mTileList.Add(aTile);
            }
        }
        GameTile *aEndTile = GetTile(pPath->mEndX, pPath->mEndY, pPath->mEndZ);
        if (aEndTile) {
            mTileList.Add(aEndTile);
        }
    }
}

void GameArena::SpawnUnitsOnPath(FList *pUnitList, LevelPath *pPath, Unit *pLeader) {
    
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
    
    GameTile *aEndTile = GetEndTileForPath(pPath);
    if (aEndTile == NULL) {
        printf("Fatal Error: No end tile...\n");
        return;
    }
    
    PathNode *aEndNode = GetEndNodeForPath(pPath);
    if (aEndNode == NULL) {
        printf("Fatal Error: No end node...\n");
        return;
    }
    
    PathNode *aStartNode = GetStartNodeForPath(pPath);
    if (aStartNode == NULL) {
        printf("Fatal Error: No start node...\n");
        return;
    }
    
    printf("Spawning On Path [%s] From (%d %d %d) => (%d %d %d)\n", pPath->mName.c(),
           pPath->mStartX, pPath->mStartY, pPath->mStartZ,
           pPath->mEndX, pPath->mEndY, pPath->mEndZ);
    
    aStartNode->mOccupied = true;
    printf("Spawning At Node [%d %d %d]\n", aStartNode->mGridX, aStartNode->mGridY, aStartNode->mGridZ);
    
    if (pLeader != 0) {
        pUnitList->MoveToFirst(pLeader);
    }
    
    //Unit *aLeader = (Unit *)(pUnitList->First());
    UnitGroup *aGroup = new UnitGroup();
    EnumList(Unit, aUnit, *pUnitList) {
        aUnit->PlaceOnGrid(aStartNode, aEndNode, aEndTile, pPath);
        aGroup->AddUnit(aUnit);
        mUnitList.Add(aUnit);
    }
    mUnitGroupList.Add(aGroup);
    //mUnitGroupCollection.Add(aGroup);
    
    Deploy(aGroup);
}

GameTile *GameArena::GetEndTileForPath(LevelPath *pPath) {
    GameTile *aResult = NULL;
    if (pPath) {
        aResult = GetTile(pPath->mEndX, pPath->mEndY, pPath->mEndZ);
    }
    return aResult;
}

GameTile *GameArena::GetStartTileForPath(LevelPath *pPath) {
    GameTile *aResult = NULL;
    if (pPath) {
        aResult = GetTile(pPath->mStartX, pPath->mStartY, pPath->mStartZ);
    }
    return aResult;
}

PathNode *GameArena::GetEndNodeForPath(LevelPath *pPath) {
    PathNode *aResult = 0;
    GameTile *aEndTile = GetEndTileForPath(pPath);
    if (aEndTile) {
        aResult = GetEndNodeForTile(aEndTile);
    }
    return aResult;
}

PathNode *GameArena::GetEndNodeForTile(GameTile *pTile) {
    PathNode *aResult = 0;
    if (pTile) {
        int aStartGridX = pTile->mGridX * SUBDIVISIONS_PER_TILE;
        int aStartGridY = pTile->mGridY * SUBDIVISIONS_PER_TILE;
        int aGridZ = pTile->mGridZ;
        int aPrimeTargetX = aStartGridX + SUBDIVISIONS_PER_TILE / 2;
        int aPrimeTargetY = aStartGridY + SUBDIVISIONS_PER_TILE / 2;
        aResult = GetGridNode(aPrimeTargetX, aPrimeTargetY, aGridZ);
    }
    return aResult;
}

PathNode *GameArena::GetStartNodeForPath(LevelPath *pPath) {
    PathNode *aResult = 0;
    
    DumpLevelPathToTileList(pPath);
    
    GameTile *aStartTile = 0;
    PathNode *aNode = 0;
    
    int aTileIndex = 0;
    while (aTileIndex < mTileList.mCount - 1) {
        GameTile *aTile = (GameTile *)(mTileList.Fetch(aTileIndex));
        int aStartGridX = aTile->mGridX * SUBDIVISIONS_PER_TILE;
        int aStartGridY = aTile->mGridY * SUBDIVISIONS_PER_TILE;
        int aGridZ = aTile->mGridZ;
        for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
            int aGridX = aStartGridX + aOffsetX;
            for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                int aGridY = aStartGridY + aOffsetY;
                aNode = GetGridNode(aGridX, aGridY, aGridZ);
                if (aNode->IsBlocked() == false) {
                    aStartTile = aTile;
                    goto FOUND_START_TILE_SEARCHING_FOR_START_NODE;
                }
            }
        }
        aTileIndex += 1;
    }
    
FOUND_START_TILE_SEARCHING_FOR_START_NODE:
    
    if (aStartTile != 0) {
        int aStartGridX = aStartTile->mGridX * SUBDIVISIONS_PER_TILE;
        int aStartGridY = aStartTile->mGridY * SUBDIVISIONS_PER_TILE;
        int aGridZ = aStartTile->mGridZ;
        int aPrimeTargetX = aStartGridX + SUBDIVISIONS_PER_TILE / 2;
        int aPrimeTargetY = aStartGridY + SUBDIVISIONS_PER_TILE / 2;
        aNode = GetGridNode(aPrimeTargetX, aPrimeTargetY, aGridZ);
        if (!aNode->IsBlocked()) {
            aResult = aNode;
        }
        if (aResult == 0) {
            for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE&&aResult==NULL;aOffsetX++) {
                int aGridX = aStartGridX + aOffsetX;
                for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE&&aResult==NULL;aOffsetY++) {
                    int aGridY = aStartGridY + aOffsetY;
                    aNode = GetGridNode(aGridX, aGridY, aGridZ);
                    if (aNode->IsBlocked() == false) {
                        aResult = aNode;
                    }
                }
            }
        }
    }
    return aResult;
}

//Send the group along the way!!!
void GameArena::Deploy(UnitGroup *pGroup) {
    
    if (pGroup == NULL) {
        printf("Fatal Error: Null unit group...\n");
        return;
    }
    
    Unit *aLeader = pGroup->Leader();
    if (aLeader == NULL) {
        printf("Fatal Error: Null leader for unit group...\n");
        return;
    }
    
    PathNode *aEndNode = GetEndNodeForTile(aLeader->mDestinationTile);
    if (aEndNode == NULL) {
        printf("Fatal Error: Unable to find end node for unit's destination tile...\n");
        return;
    }
    
    if (pGroup->mUnitList.mCount <= 0) {
        printf("Fatal Error: Unit group with empty list...\n");
        return;
    }
    
    if (aLeader->mTrackingPath == NULL) {
        printf("Fatal Error: Unit leader has no tracking path...\n");
        return;
    }
    
    if (aLeader->mPath == NULL) {
        aLeader->mPath = new UnitPath();
    }
    
    pGroup->Refresh();
    
    ConfigureGridConnections(pGroup);
    
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
        printf("We got into a situation where our leader could not path to the end...");
        
        ConfigureGridConnectionsIgnoringUnits();
        aPath->ComputePath(this);
        
        if (aPath->mLength > 0) {
            printf("Path Correction => Ignoring units we are able to path...\n");
        } else {
            printf("Fatal Error: We are not able to DEPLAY group along any PATH...\n");
        }
        //In this case we sleep for a moment, then we try to path again...
    }
    
    
    int aLeaderGridX = aLeader->mGridX;
    int aLeaderGridY = aLeader->mGridY;
    int aLeaderGridZ = aLeader->mGridZ;
    
    //We need an additional step here to block the grid appropriately...
    
    //Like, we do not block a node until it's manhattan distance is < 2 from the blocking unit...
    
    
    
    
    
    //Assuming the LEVELPATH has already been computed...
    /// ...
    /// ...
    /// ...
    
    
    
    //mPath
    
    
    //...
    
}

bool GameArena::UnitGridPositionsAreAdjacent(int pGridX1, int pGridY1, int pGridZ1,
                                             int pGridX2, int pGridY2, int pGridZ2) {
    if (pGridX1 >= 0 && pGridX1 < mUnitGridWidth && pGridY1 >= 0 && pGridY1 < mUnitGridHeight && pGridZ1 >= 0 && pGridZ1 < GRID_DEPTH &&
        pGridX2 >= 0 && pGridX2 < mUnitGridWidth && pGridY2 >= 0 && pGridY2 < mUnitGridHeight && pGridZ2 >= 0 && pGridZ2 < GRID_DEPTH) {
        int aDiffX = pGridX2 - pGridX1;
        int aDiffY = pGridY2 - pGridY1;
        int aDiffZ = pGridZ2 - pGridZ1;
        
        //Same tile, not adjacent...
        if (aDiffX == 0 && aDiffY == 0 && aDiffZ == 0) { return false; }
        
        if (aDiffX >= -1 && aDiffX <= 1 &&
            aDiffY >= -1 && aDiffY <= 1 &&
            aDiffZ >= -1 && aDiffZ <= 1) {
            return true;
        }
        
        //Different vertical level, can only be straight moves..?
        //TODO: This causes us to freeze in some situations...
        //Problem: Path decided to switch directions at base of ramp.
        //        if (aDiffZ == 1) {
        //            if (aDiffX == 1 && aDiffY == 0) {
        //                return true;
        //            }
        //            if (aDiffX == 0 && aDiffY == 1) {
        //                return true;
        //            }
        //        }
    }
    return false;
}

//Our leader unit was asleep, and we just started walking. Make sure
//all the minnion follower units are in LEGAL positions, and figure out which
//ones are clumped up at start node versus not clumped up...
void GameArena::UnitDidStartWalkingFromIdle(Unit *pUnit) {
    
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
                    
                    if (UnitGridPositionsAreAdjacent(aPrevGridX, aPrevGridY, aPrevGridZ, aUnit->mGridX, aUnit->mGridY, aUnit->mGridZ)) {
                        
                        
                        
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
                    
                    for (int i=1;i<aGroup->mUnitList.mCount && aFirstNonAdjacentIndex == -1;i++) {
                        Unit *aUnit = (Unit *)(aGroup->mUnitList.mData[i]);
                        aUnit->mIsWalking = true;
                        aUnit->mDidStartWalking = true;
                    }
                    
                    
                } else {
                    
                    printf("aFirstNonAdjacentIndex = %d ...\n", aFirstNonAdjacentIndex);
                    
                    
                    
                    
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

void GameArena::UnitDidFinishWalkingStep(Unit *pUnit) {
    if (pUnit != NULL && pUnit->mGroup != NULL) {
        UnitGroup *aGroup = pUnit->mGroup;
        Unit *aLeader = aGroup->Leader();
        if (aGroup->Count() > 1 && aLeader == pUnit) {
            
            float aOvershootPercent = aLeader->mStepPercent;
            printf("Advancing [%lX] Prev[%d %d %d] Cur[%d %d %d]\n", (unsigned long)aLeader, aLeader->mPrevGridX, aLeader->mPrevGridY, aLeader->mPrevGridZ, aLeader->mGridX, aLeader->mGridY, aLeader->mGridZ);
            
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
        }
    }
}

void GameArena::SplitUnitGroups() {
    bool aReloop = true;
    do {
        aReloop = TrySplitUnitGroups();
    } while (aReloop);
}

bool GameArena::TrySplitUnitGroups() {
    
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
bool GameArena::TrySplitUnitGroup(UnitGroup *pGroup) {
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

void GameArena::HandOffPath(Unit *pFromUnit, Unit *pToUnit) {
    if ((pFromUnit != NULL) && (pToUnit != NULL) && (pFromUnit != pToUnit)) {
        pToUnit->AttemptCopyPathFromUnit(pFromUnit);
    }
}


void GameArena::KillAllInvalidUnitGroups() {
    
}

void GameArena::RemoveKilledUnitGroups() {
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (aGroup->mKill) {
            mKillUnitGroupList.Add(aGroup);
        }
    }
    EnumList(UnitGroup, aGroup, mKillUnitGroupList) {
        mUnitGroupList.Remove(aGroup);
    }
}

void GameArena::RefreshUnitGroups() {
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        aGroup->Refresh();
    }
}

void GameArena::Click(float pX, float pY) {
    
    if (mTestMode == TEST_MODE_NONE) {
        
        int aGridX = -1;
        int aGridY = -1;
        int aGridZ = -1;
        GetGridPos(pX, pY, aGridX, aGridY, aGridZ);
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
            for (int aX=0;aX<mTileGridWidthTotal;aX++) {
                for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                    GameTile *aTile = mTile[aDepth][aX][aY];
                    if (aTile) {
                        aTile->mBlocked = false;
                        if (GetTower(aX, aY, aDepth)) {
                            aTile->mBlocked = true;
                        }
                    }
                }
            }
        }
        ComputePathConnections();
        
    } else if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        
    } else if (mTestMode == TEST_MODE_UNIT_GROUP_SELECT) {
        
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

void GameArena::TestTouch(float pX, float pY, void *pData) {
    mTestMouseX = pX;
    mTestMouseY = pY;
    
    ConfigureGridConnectionsForPlacement();
    
    printf("Test Touch: %f %f\n", pX, pY);
    if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        
        PathNode *aNode = GetClosestNode(pX, pY, false, false, true);
        if (aNode) {
            LevelPath *aLevelPath = GetPathForNode(aNode->mGridX, aNode->mGridY, aNode->mGridZ);
            if (aLevelPath != NULL) {
                
                
                mTestCreateGroup = new UnitGroup();
                mUnitGroupList += mTestCreateGroup;
                
                Unit *aLeaderUnit = new Unit();
                mTestCreateGroup->AddUnit(aLeaderUnit);
                mUnitList += aLeaderUnit;
                
                PathNode *aEndNode = GetEndNodeForPath(aLevelPath);
                PathNode *aStartNode = aNode;
                GameTile *aEndTile = GetEndTileForPath(aLevelPath);
                
                aLeaderUnit->PlaceOnGrid(aStartNode, aEndNode, aEndTile, aLevelPath);
                aNode->mOccupied = true;
            }
        }
    }
    
    /*
     mPreviousTestMode = mTestMode;
     
     mTestCreateGroup = 0;
     mTestSelectedGroup = 0;
     
     mTestGroupShowPath = true;
     mTestGroupShowAllPath = false;
     */
    
}

void GameArena::TestDrag(float pX, float pY, void *pData) {
    mTestMouseX = pX;
    mTestMouseY = pY;
    
    ConfigureGridConnectionsForPlacement();
    
    if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        if (mTestCreateGroup != NULL) {
            Unit *aLastUnit = (Unit *)(mTestCreateGroup->mUnitList.Last());
            PathNode *aNode = GetClosestNode(pX, pY, false, false, true);
            if (aNode != NULL && aLastUnit != NULL) {
                LevelPath *aLevelPath = GetPathForNode(aNode->mGridX, aNode->mGridY, aNode->mGridZ);
                
                if (aLevelPath != NULL && UnitGridPositionsAreAdjacent(aLastUnit->mGridX, aLastUnit->mGridY, aLastUnit->mGridZ, aNode->mGridX, aNode->mGridY, aNode->mGridZ)) {
                    
                    Unit *aAddUnit = new Unit();
                    mTestCreateGroup->AddUnit(aAddUnit);
                    mUnitList += aAddUnit;
                    
                    PathNode *aEndNode = GetEndNodeForPath(aLevelPath);
                    PathNode *aStartNode = aNode;
                    GameTile *aEndTile = GetEndTileForPath(aLevelPath);
                    
                    aAddUnit->PlaceOnGrid(aStartNode, aEndNode, aEndTile, aLevelPath);
                    aNode->mOccupied = true;
                }
            }
        }
    }
}

void GameArena::TestRelease(float pX, float pY, void *pData) {
    
    if (mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        if (mTestCreateGroup != NULL) {
            if (mTestCreateGroup->mUnitList.mCount <= 0) {
                mTestCreateGroup->Kill();
            } else {
                Deploy(mTestCreateGroup);
            }
        }
    }
}

void GameArena::TestFlush() {
    
}


FRect GameArena::GetRectForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ) {
    float aNodeWidth = gTileSize / ((float)SUBDIVISIONS_PER_TILE);
    FRect aResult = FRect(0.0f, 0.0f, aNodeWidth, aNodeWidth);
    
    PathNode *aNode = GetGridNode(pUnitGridX, pUnitGridY, pUnitGridZ);
    if (aNode) {
        aResult.mX = aNode->mCenterX - aNodeWidth / 2.0f;
        aResult.mY = aNode->mCenterY - aNodeWidth / 2.0f;
    }
    
    return aResult;
}

GameTile *GetTopTileForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ);

//If there are multiple tiles for a particular node, we get all of the tiles
// (max of 2) for the given node...
void GameArena::GetAllTilesForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ, FList *pList) {
    if (pUnitGridX >= 0 && pUnitGridX < mUnitGridWidth && pUnitGridY >= 0 && pUnitGridY < mUnitGridHeight) {
        
        PathNode *aNode = GetGridNode(pUnitGridX, pUnitGridY, pUnitGridZ);
        
        //Basically... Ignore Z and scan through the whole pancake stack of tiles
        //on this position to see which ones contain the node
        
        if (aNode != NULL && pList != NULL) {
            
            int aTileGridX = pUnitGridX / SUBDIVISIONS_PER_TILE;
            int aTileGridY = pUnitGridY / SUBDIVISIONS_PER_TILE;
            for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
                
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                
                if (aTile != NULL) {
                    
                    bool aDidAddTile = false;
                    
                    for (int aGridX=0;aGridX<=SUBDIVISIONS_PER_TILE && aDidAddTile == false;aGridX++) {
                        for (int aGridY=0;aGridY<=SUBDIVISIONS_PER_TILE && aDidAddTile == false;aGridY++) {
                            
                            PathNode *aTileNode = aTile->mGrid[aGridX][aGridY];
                            if (aTileNode != NULL) {
                                
                                if (aTileNode == aNode) {
                                    aDidAddTile = true;
                                    pList->Add(aTile);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

LevelPath *GameArena::GetPathForGridPos(int pTileGridX, int pTileGridY, int pTileGridZ) {
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

LevelPath *GameArena::GetPathForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ) {
    LevelPath *aResult = NULL;
    
    FList aTileList;
    GetAllTilesForNode(pUnitGridX, pUnitGridY, pUnitGridZ, &aTileList);
    EnumList(GameTile, aTile, aTileList) {
        if (aResult == NULL) {
            aResult = GetPathForGridPos(aTile->mGridX, aTile->mGridY, aTile->mGridZ);
        }
    }
    
    return aResult;
}


GameTile *GameArena::GetTopTileForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ) {
    GameTile *aResult = 0;
    if (pUnitGridX >= 0 && pUnitGridX < mUnitGridWidth && pUnitGridY >= 0 && pUnitGridY < mUnitGridHeight && pUnitGridZ >= 0 && pUnitGridZ < GRID_DEPTH) {
        int aTileGridX = pUnitGridX / SUBDIVISIONS_PER_TILE;
        int aTileGridY = pUnitGridY / SUBDIVISIONS_PER_TILE;
        aResult = GetTile(aTileGridX, aTileGridY, pUnitGridZ);
    }
    return aResult;
}

//Get the closest valid node to a particular screen location....
//There is one rule always enforce - the node must be on a TILE...
PathNode *GameArena::GetClosestNode(float pX, float pY, bool pAllowBlocked, bool pAllowOccupied, bool pAllowRamps) {
    
    PathNode *aClosestNode = NULL;
    float aBestDist = 100.0f * 100.0f;
    
    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;
    
    GetEditorGridPos(pX, pY, aGridX, aGridY, aGridZ);
    GameTile *aTile = GetTile(aGridX, aGridY, aGridZ);
    
    if (aTile) {
        
        for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
            for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                PathNode *aNode = aTile->mGrid[aOffsetX][aOffsetY];
                if (aNode != NULL) {
                    
                    float aDiffX = aNode->mCenterX - pX;
                    float aDiffY = aNode->mCenterY - pY;
                    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
                    if (aDist < aBestDist) {
                        aClosestNode = aNode;
                        aBestDist = aDist;
                    }
                    
                }
            }
        }
    }
    
    
    if (aClosestNode != NULL && aTile != NULL) {
        if (pAllowRamps == true || aTile->IsRamp() == false) {
            
        } else {
            aClosestNode = NULL;
        }
    }
    
    
    if (aClosestNode != NULL && aTile != NULL) {
        if (pAllowBlocked == true || aClosestNode->mBlocked == false) {
            
        } else {
            aClosestNode = NULL;
        }
    }
    
    if (aClosestNode != NULL && aTile != NULL) {
        if (pAllowOccupied == true || aClosestNode->mOccupied == false) {
            
        } else {
            aClosestNode = NULL;
        }
    }
    
    
    
    
    //
    /*
     PathNode *aClosestNode = NULL;
     float aBestDist = 100.0f * 100.0f;
     for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
     for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
     for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
     GameTile *aTile = GetTopTileForNode(aGridX, aGridY, aDepth);
     PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];
     if (aTile != NULL && aNode != NULL) {
     if (pAllowRamps == false || aTile->IsRamp() == false) {
     if (pAllowBlocked == false || aNode->mBlocked == false) {
     if (pAllowOccupied == false || aNode->mOccupied == false) {
     float aDiffX = aNode->mCenterX - pX;
     float aDiffY = aNode->mCenterY - pY;
     float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
     if (aDist < aBestDist) {
     aClosestNode = aNode;
     aBestDist = aDist;
     }
     }
     }
     }
     }
     }
     }
     }
     */
    
    return aClosestNode;
}



void GameArena::RefreshGridCursor(float pX, float pY) {
    
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

Tower *GameArena::GetTower(int pGridX, int pGridY, int pGridZ) {
    Tower *aResult = 0;
    EnumList(Tower, aTower, mTowerCollection.mObjectList) {
        if (aTower->mKill == 0) {
            if (aTower->mGridX == pGridX && aTower->mGridY == pGridY && aTower->mGridZ == pGridZ) {
                aResult = aTower;
            }
        }
    }
    /*
     EnumList(Tower, aTower, mTowerList)
     {
     if(aTower->mTileGridX == pGridX && aTower->mTileGridY == pGridY)
     {
     aResult = aTower;
     }
     }
     */
    
    return aResult;
}

void GameArena::AddUnit(Unit *pUnit, LevelPath *pPath) {
    if (pUnit) {
        FList aUnitList;
        aUnitList.Add(pUnit);
        SpawnUnitsOnPath(&aUnitList, pPath);
    }
}

void GameArena::ComputePathConnections() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mTileGridWidthTotal;aX++) {
            for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                GameTile *aTile = mTile[aDepth][aX][aY];
                if (aTile) {
                    aTile->PathReset();
                }
            }
        }
    }
    
    EnumList(Tower, aTower, mTowerCollection.mObjectList) {
        if (aTower->mKill == 0) {
            GameTile *aTowerTile = GetTile(aTower->mGridX, aTower->mGridY, MAIN_FLOOR);
            if (aTowerTile) {
                aTowerTile->mOccupied = true;
            }
        }
    }
    
#define PATH_COST_ADJ 100
#define PATH_COST_DIA 141
#define PATH_COST_RAMP 100
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mTileGridWidthTotal;aX++) {
            for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                GameTile *aTile = GetTile(aX, aY, aDepth);
                if (aTile) {
                    if (aTile->IsBlocked() == false) {
                        
                        GameTile *aTileU = GetTile(aX, aY - 1, aDepth);
                        GameTile *aTileD = GetTile(aX, aY + 1, aDepth);
                        GameTile *aTileL = GetTile(aX - 1, aY, aDepth);
                        GameTile *aTileR = GetTile(aX + 1, aY, aDepth);
                        
                        if (aTile->IsNormal()) {
                            if (aTileU) {
                                if(aTileU->IsNormal() || aTileU->mTileType == TILE_TYPE_RAMP_U) {
                                    if (aTileU->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileU, PATH_COST_ADJ);
                                    }
                                }
                            }
                            
                            if (aTileD) {
                                if (aTileD->IsNormal() || aTileD->mTileType == TILE_TYPE_RAMP_D) {
                                    if (aTileD->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileD, PATH_COST_ADJ);
                                    }
                                }
                            }
                            if (aTileL) {
                                if(aTileL->IsNormal() || aTileL->mTileType == TILE_TYPE_RAMP_L) {
                                    if (aTileL->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileL, PATH_COST_ADJ);
                                    }
                                }
                            }
                            if (aTileR) {
                                if(aTileR->IsNormal() || aTileR->mTileType == TILE_TYPE_RAMP_R) {
                                    if (aTileR->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileR, PATH_COST_ADJ);
                                    }
                                }
                            }
                            
                            GameTile *aTileUR = GetTile(aX + 1, aY - 1, aDepth);
                            GameTile *aTileUL = GetTile(aX - 1, aY - 1, aDepth);
                            GameTile *aTileDR = GetTile(aX + 1, aY + 1, aDepth);
                            GameTile *aTileDL = GetTile(aX - 1, aY + 1, aDepth);
                            
                            if (aTileU != 0 && aTileL != 0 && aTileUL != 0) {
                                if (aTileU->IsNormal() && aTileL->IsNormal() && aTileUL->IsNormal()) {
                                    if (aTileU->IsBlocked() == false && aTileL->IsBlocked() == false && aTileUL->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileUL, PATH_COST_DIA);
                                    }
                                }
                            }
                            if (aTileU != 0 && aTileR != 0 && aTileUR != 0) {
                                if (aTileU->IsNormal() && aTileR->IsNormal() && aTileUR->IsNormal()) {
                                    if (aTileU->IsBlocked() == false && aTileR->IsBlocked() == false && aTileUR->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileUR, PATH_COST_DIA);
                                    }
                                }
                            }
                            if (aTileD != 0 && aTileL != 0 && aTileDL != 0) {
                                if (aTileD->IsNormal() && aTileL->IsNormal() && aTileDL->IsNormal()) {
                                    if (aTileD->IsBlocked() == false && aTileL->IsBlocked() == false && aTileDL->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileDL, PATH_COST_DIA);
                                    }
                                }
                            }
                            if (aTileD != 0 && aTileR != 0 && aTileDR != 0) {
                                if (aTileD->IsNormal() && aTileR->IsNormal() && aTileDR->IsNormal()) {
                                    if (aTileD->IsBlocked() == false && aTileR->IsBlocked() == false && aTileDR->IsBlocked() == false) {
                                        aTile->ConnectTo(aTileDR, PATH_COST_DIA);
                                    }
                                }
                            }
                        }
                        GameTile *aLowerTileU = GetTile(aX, aY - 1, aDepth - 1);
                        GameTile *aLowerTileD = GetTile(aX, aY + 1, aDepth - 1);
                        GameTile *aLowerTileL = GetTile(aX - 1, aY, aDepth - 1);
                        GameTile *aLowerTileR = GetTile(aX + 1, aY, aDepth - 1);
                        
                        if (aTile->mTileType == TILE_TYPE_RAMP_U) {
                            if (aLowerTileU) {
                                if (aLowerTileU->IsBlocked() == false) {
                                    aTile->ConnectTo(aLowerTileU, PATH_COST_RAMP);
                                    aLowerTileU->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            
                            //Special case, double ramp... (impractical, but necessary for completion...
                            if (aTileU) {
                                if (aTileU->IsBlocked() == false && aTileU->mTileType == TILE_TYPE_RAMP_D) {
                                    aTile->ConnectTo(aTileU, PATH_COST_RAMP);
                                    aTileU->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            if (aTileD) {
                                if (aTileD->IsBlocked() == false) {
                                    aTile->ConnectTo(aTileD, PATH_COST_ADJ);
                                }
                            }
                        }
                        
                        if (aTile->mTileType == TILE_TYPE_RAMP_D) {
                            if (aLowerTileD) {
                                if (aLowerTileD->IsBlocked() == false) {
                                    aTile->ConnectTo(aLowerTileD, PATH_COST_RAMP);
                                    aLowerTileD->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            if (aTileU) {
                                if (aTileU->IsBlocked() == false) {
                                    aTile->ConnectTo(aTileU, PATH_COST_ADJ);
                                }
                            }
                        }
                        if (aTile->mTileType == TILE_TYPE_RAMP_R) {
                            if (aLowerTileR) {
                                if (aLowerTileR->IsBlocked() == false) {
                                    aTile->ConnectTo(aLowerTileR, PATH_COST_RAMP);
                                    aLowerTileR->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            //Special case, double ramp... (impractical, but necessary for completion...
                            if (aTileR) {
                                if (aTileR->IsBlocked() == false && aTileR->mTileType == TILE_TYPE_RAMP_L) {
                                    aTile->ConnectTo(aTileR, PATH_COST_RAMP);
                                    aTileR->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            if (aTileL) {
                                if (aTileL->IsBlocked() == false) {
                                    aTile->ConnectTo(aTileL, PATH_COST_ADJ);
                                }
                            }
                        }
                        if (aTile->mTileType == TILE_TYPE_RAMP_L) {
                            if (aLowerTileL) {
                                if (aLowerTileL->IsBlocked() == false) {
                                    aTile->ConnectTo(aLowerTileL, PATH_COST_RAMP);
                                    aLowerTileL->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            if (aTileR) {
                                if (aTileR->IsBlocked() == false) {
                                    aTile->ConnectTo(aTileR, PATH_COST_ADJ);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    EnumList (AnimatedLevelPath, aPath, mPathList) {
        aPath->ComputePath(this);
    }
    
    ResetGridConnections();
    ComputeGridConnections();
}


void GameArena::ResetWalkAllowedGrid() {
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                mWalkAllowed[aDepth][aGridX][aGridY] = false;
            }
        }
    }
}

void GameArena::ResetGridConnections() {
    
    // Reset all subgrid path nodes.
    PathNode *aNode = 0;
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                aNode = mUnitGrid[aDepth][aGridX][aGridY];
                aNode->PathReset();
            }
        }
    }
    
    //  Make all "occupied" tiles entirely occuiped in subgrid.
    // (These are tiles where a tower lies)
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile != 0 && aTile->mOccupied == true) {
                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        int aGridX = aStartGridX + aOffsetX;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mUnitGrid[aDepth][aGridX][aGridY];
                            aNode->mOccupied = true;
                        }
                    }
                }
            }
        }
    }
}

void GameArena::ComputeGridConnections() {
    
    //Link up nodes insernally among tiles...
    
    // o o o o
    // |X|X|X|
    // o-o-o-o
    
    PathNode *aNode = 0;
    
    PathNode *aNodeU = 0;
    PathNode *aNodeR = 0;
    PathNode *aNodeD = 0;
    PathNode *aNodeL = 0;
    
    PathNode *aNodeUL = 0;
    PathNode *aNodeUR = 0;
    PathNode *aNodeDR = 0;
    PathNode *aNodeDL = 0;
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        int aGridX = aStartGridX + aOffsetX;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mUnitGrid[aDepth][aGridX][aGridY];
                            
                            if (aNode->IsBlocked()) { continue; }
                            
                            aNodeU = 0;
                            aNodeR = 0;
                            aNodeD = 0;
                            aNodeL = 0;
                            
                            aNodeUL = 0;
                            aNodeUR = 0;
                            aNodeDR = 0;
                            aNodeDL = 0;
                            
                            if (aOffsetY > 0) { aNodeU = mUnitGrid[aDepth][aGridX][aGridY-1]; }
                            if (aOffsetY < SUBDIVISIONS_PER_TILE) { aNodeD = mUnitGrid[aDepth][aGridX][aGridY+1]; }
                            if (aOffsetX > 0) {
                                aNodeL = mUnitGrid[aDepth][aGridX-1][aGridY];
                                if (aOffsetY > 0) { aNodeUL = mUnitGrid[aDepth][aGridX-1][aGridY-1]; }
                                if (aOffsetY < SUBDIVISIONS_PER_TILE) { aNodeDL = mUnitGrid[aDepth][aGridX-1][aGridY+1]; }
                            }
                            if (aOffsetX < SUBDIVISIONS_PER_TILE) {
                                aNodeR = mUnitGrid[aDepth][aGridX+1][aGridY];
                                if (aOffsetY > 0) { aNodeUR = mUnitGrid[aDepth][aGridX+1][aGridY-1]; }
                                if (aOffsetY < SUBDIVISIONS_PER_TILE) { aNodeDR = mUnitGrid[aDepth][aGridX+1][aGridY+1]; }
                            }
                            
                            if(aNodeU != 0 && aNodeU->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeU, PATH_COST_ADJ);
                            }
                            if(aNodeR != 0 && aNodeR->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeR, PATH_COST_ADJ);
                            }
                            if(aNodeD != 0 && aNodeD->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeD, PATH_COST_ADJ);
                            }
                            if(aNodeL != 0 && aNodeL->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeL, PATH_COST_ADJ);
                            }
                            if(aNodeUL != 0 && aNodeUL->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeUL, PATH_COST_DIA);
                            }
                            if(aNodeUR != 0 && aNodeUR->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeUR, PATH_COST_DIA);
                            }
                            if(aNodeDR != 0 && aNodeDR->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeDR, PATH_COST_DIA);
                            }
                            if(aNodeDL != 0 && aNodeDL->IsBlocked() == false) {
                                aNode->ConnectTo(aNodeDL, PATH_COST_DIA);
                            }
                        }
                    }
                }
            }
        }
    }
}

void GameArena::ConfigureGridConnections(UnitGroup *pGroup) {
    ResetGridConnections();
    if (pGroup) {
        EnumList(Unit, aUnit, mUnitList) {
            if (pGroup->ContainsUnit(aUnit) == false) {
                //TODO: Based on manhattan distance
                
                OccupyGridForUnit(aUnit);
            }
        }
    }
    
    Unit *aLeader = pGroup->Leader();
    PathNode *aNode = 0;
    
    //Make sure the destination tile is not occupied (it can't be occupied)
    GameTile *aDestinationTile = aLeader->mDestinationTile;
    if (aDestinationTile != NULL) {
        int aStartGridX = aDestinationTile->mGridX * SUBDIVISIONS_PER_TILE;
        int aStartGridY = aDestinationTile->mGridY * SUBDIVISIONS_PER_TILE;
        int aGridZ = aDestinationTile->mGridZ;
        for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
            int aGridX = aStartGridX + aOffsetX;
            for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                int aGridY = aStartGridY + aOffsetY;
                aNode = GetGridNode(aGridX, aGridY, aGridZ);
                aNode->mOccupied = false;
            }
        }
    }
    ComputeGridConnections();
}

void GameArena::ConfigureGridConnectionsForPlacement() {
    ResetGridConnections();
    EnumList(Unit, aUnit, mUnitList) {
        OccupyGridForUnit(aUnit, 0);
    }
    ComputeGridConnections();
}

void GameArena::ConfigureGridConnectionsIgnoringUnits() {
    ResetGridConnections();
    ComputeGridConnections();
}

void GameArena::OccupyGridForUnit(Unit *pUnit, int pLookAhead) {
    if (pUnit) {
        //If the unit is a leader unit, we consider the path...
        
        int aGridX = pUnit->mGridX;
        int aGridY = pUnit->mGridY;
        int aGridZ = pUnit->mGridZ;
        
        PathNode *aNode = GetGridNode(aGridX, aGridY, aGridZ);
        if (aNode) {
            aNode->mOccupied = true;
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
                        aNode = GetGridNode(aGridX, aGridY, aGridZ);
                        if (aNode) {
                            aNode->mOccupied = true;
                        }
                        aPathIndex++;
                        aLoops--;
                    }
                }
            }
        }
    }
}

bool GameArena::CanUnitWalkToAdjacentGridPosition(Unit *pUnit, int pGridX, int pGridY, int pGridZ) {
    if (pUnit) {
        ConfigureGridConnectionsForPlacement();
        int aGridX = pUnit->mGridX;
        int aGridY = pUnit->mGridY;
        int aGridZ = pUnit->mGridZ;
        if (UnitGridPositionsAreAdjacent(aGridX, aGridY, aGridZ, pGridX, pGridY, pGridZ)) {
            //Make sure grid position is unblocked and unoccupied.
            PathNode *aNode = GetGridNode(pGridX, pGridY, pGridZ);
            if (aNode) {
                if (aNode->IsBlocked() == false) {
                    return true;
                }
            }
        }
    }
    return false;
}


bool GameArena::IsLeaderUnit(Unit *pUnit) {
    bool aResult = false;
    EnumList(UnitGroup, aGroup, mUnitGroupList) {
        if (aGroup->mKill == 0 && aGroup->IsLeader(pUnit)) {
            return true;
        }
    }
    return aResult;
}


void GameArena::ComputeTestPath() {
    GameTile *aStartTile = 0;
    GameTile *aEndTile = 0;
    PathNode *aStartNode = 0;
    PathNode *aEndNode = 0;
    for (int aGridY=0;aGridY<mTileGridHeightTotal;aGridY++) {
        for (int aGridX=0;aGridX<mTileGridWidthTotal;aGridX++) {
            for (int aDepth=GRID_DEPTH-1;aDepth>=0;aDepth--) {
                GameTile *aTile = GetTile(aGridX, aGridY, aDepth);
                if (aTile) {
                    for (int aInnerX=0;aInnerX<=SUBDIVISIONS_PER_TILE;aInnerX++) {
                        for (int aInnerY=0;aInnerY<=SUBDIVISIONS_PER_TILE;aInnerY++) {
                            PathNode *aNode = aTile->mGrid[aInnerX][aInnerY];
                            if (aNode->IsBlocked() == false) {
                                aStartNode = aNode;
                                goto FOUND_X;
                            }
                        }
                    }
                }
            }
        }
    }
FOUND_X:
    
    for (int aGridY=(mTileGridHeightTotal-1);aGridY>=0;aGridY--) {
        for (int aGridX=(mTileGridWidthTotal-1);aGridX>=0;aGridX--) {
            for (int aDepth=GRID_DEPTH-1;aDepth>=0;aDepth--) {
                GameTile *aTile = GetTile(aGridX, aGridY, aDepth);
                if (aTile) {
                    for (int aInnerX=SUBDIVISIONS_PER_TILE;aInnerX>=0;aInnerX--) {
                        for (int aInnerY=SUBDIVISIONS_PER_TILE;aInnerY>=0;aInnerY--) {
                            PathNode *aNode = aTile->mGrid[aInnerX][aInnerY];
                            if (aNode->IsBlocked() == false) {
                                aEndNode = aNode;
                                goto FOUND_Y;
                            }
                        }
                    }
                }
            }
        }
    }
FOUND_Y:
    
    
    AnimatedLevelPath *aFirstPath = ((AnimatedLevelPath *)mPathList.Fetch(0));
    if (aFirstPath != 0) {
        GameTile *aStartTile = GetTile(aFirstPath->mStartX, aFirstPath->mStartY, aFirstPath->mStartZ);
        GameTile *aEndTile = GetTile(aFirstPath->mEndX, aFirstPath->mEndY, aFirstPath->mEndZ);
        
        if (aStartTile != 0 && aEndTile != 0) {
            aStartNode = 0;
            aEndNode = 0;
            
            for (int aGridX=0;aGridX<=SUBDIVISIONS_PER_TILE;aGridX++) {
                for (int aGridY=0;aGridY<=SUBDIVISIONS_PER_TILE;aGridY++) {
                    PathNode *aNode = aStartTile->mGrid[aGridX][aGridY];
                    if (aNode->mBlocked == false && aStartNode == 0) {
                        aStartNode = aNode;
                    }
                }
            }
            
            for (int aGridX=SUBDIVISIONS_PER_TILE;aGridX>=0;aGridX--) {
                for (int aGridY=SUBDIVISIONS_PER_TILE;aGridY>=0;aGridY--) {
                    PathNode *aNode = aEndTile->mGrid[aGridX][aGridY];
                    if (aNode->mBlocked == false && aEndNode == 0) {
                        aEndNode = aNode;
                    }
                }
            }
        }
    }
    
    if (aStartNode != 0 && aEndNode != 0) {
        mTestUnitPath.mStartX = aStartNode->mGridX;
        mTestUnitPath.mStartY = aStartNode->mGridY;
        mTestUnitPath.mStartZ = aStartNode->mGridZ;
        mTestUnitPath.mEndX = aEndNode->mGridX;
        mTestUnitPath.mEndY = aEndNode->mGridY;
        mTestUnitPath.mEndZ = aEndNode->mGridZ;
        mTestUnitPath.ComputePath(this);
    }
}


//This will assign nodes to tiles, compute node positions, and figure out which
//nodes are "blocked" by default...
void GameArena::RefreshUnitGridNodes() {
    PathNode *aNode = 0;
    //Step 1: UNBLOCK all of the grid nodes...
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                aNode = mUnitGridBase[aDepth][aGridX][aGridY];
                aNode->HardReset();
                aNode->mBlocked = true;
            }
        }
    }
    
    //Step 2: Using Unit Grid BASE, we generate Unit Grid, which will contain some
    //duplicates as per ramp connections to different levels...
    
    //  2.1: Reset all nodes to their base node...
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                aNode = mUnitGridBase[aDepth][aGridX][aGridY];
                aNode->mGridX = aGridX;
                aNode->mGridY = aGridY;
                aNode->mGridZ = aDepth;
                mUnitGrid[aDepth][aGridX][aGridY] = aNode;
            }
        }
    }
    
    //  2.2: Find all ramps and set the connecting connecting edge
    //  to the tile "below" (bridge ramp connects to floor tile, floor ramp connects to tunnel tile...)
    // (ONLY WHEN CONNECTION IS LEGAL) (e.g. a ramp leading into an opposite ramp does not connect to the floor below...)
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    
                    if (aTile->mTileType == TILE_TYPE_RAMP_U) {
                        GameTile *aTileU      = GetTile(aTileGridX, aTileGridY - 1, aDepth    );
                        GameTile *aTileBelowU = GetTile(aTileGridX, aTileGridY - 1, aDepth - 1);
                        
                        //Case 1: Tile U us a RAMP_DOWN... (Tile BELOW doesn't exist)
                        if (aTileU != 0 && aTileU->mTileType == TILE_TYPE_RAMP_D) {
                            //In this case, we don't reassign nodes...
                        } else if (aTileBelowU != 0) {
                            //Case 2: Tile BELOW U is EITHER (NORMAL or RAMP_UP) (AND there could be a bridge over or tunnel below...)
                            if (aTileBelowU->mTileType == TILE_TYPE_NORMAL || aTileBelowU->mTileType == TILE_TYPE_RAMP_U) {
                                //In this case, we connect the one row of nodes... We should theoretically be able to
                                //connect all of them, although a situation may arise where we need to leave out corners?
                                int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
                                int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                                int aOffsetX = 0;
                                int aOffsetY = 0;
                                while (aOffsetX <= SUBDIVISIONS_PER_TILE) {
                                    int aGridX = aStartGridX + aOffsetX;
                                    int aGridY = aStartGridY + aOffsetY;
                                    aNode = mUnitGridBase[aDepth-1][aGridX][aGridY];
                                    aNode->mGridZ = aDepth;
                                    mUnitGrid[aDepth][aGridX][aGridY] = aNode;
                                    aOffsetX++;
                                }
                            }
                        }
                    }
                    
                    if (aTile->mTileType == TILE_TYPE_RAMP_R) {
                        GameTile *aTileR      = GetTile(aTileGridX + 1, aTileGridY    , aDepth    );
                        GameTile *aTileBelowR = GetTile(aTileGridX + 1, aTileGridY    , aDepth - 1);
                        
                        //Case 1: Tile R us a RAMP_LEFT... (Tile BELOW doesn't exist)
                        if (aTileR != 0 && aTileR->mTileType == TILE_TYPE_RAMP_L) {
                            //In this case, we don't reassign nodes...
                        } else if (aTileBelowR != 0) {
                            //Case 2: Tile BELOW R is EITHER (NORMAL or RAMP_RIGHT) (AND there could be a bridge over or tunnel below...)
                            if (aTileBelowR->mTileType == TILE_TYPE_NORMAL || aTileBelowR->mTileType == TILE_TYPE_RAMP_R) {
                                //In this case, we connect the one row of nodes... We should theoretically be able to
                                //connect all of them, although a situation may arise where we need to leave out corners?
                                
                                int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
                                int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                                int aOffsetX = SUBDIVISIONS_PER_TILE;
                                int aOffsetY = 0;
                                while (aOffsetY <= SUBDIVISIONS_PER_TILE) {
                                    int aGridX = aStartGridX + aOffsetX;
                                    int aGridY = aStartGridY + aOffsetY;
                                    aNode = mUnitGridBase[aDepth-1][aGridX][aGridY];
                                    aNode->mGridZ = aDepth;
                                    mUnitGrid[aDepth][aGridX][aGridY] = aNode;
                                    aOffsetY++;
                                }
                            }
                        }
                    }
                    
                    
                    if (aTile->mTileType == TILE_TYPE_RAMP_D) {
                        GameTile *aTileD      = GetTile(aTileGridX    , aTileGridY + 1, aDepth    );
                        GameTile *aTileBelowD = GetTile(aTileGridX    , aTileGridY + 1, aDepth - 1);
                        
                        //Case 1: Tile D us a RAMP_UP... (Tile BELOW doesn't exist)
                        if (aTileD != 0 && aTileD->mTileType == TILE_TYPE_RAMP_U) {
                            //In this case, we don't reassign nodes...
                        } else if (aTileBelowD != 0) {
                            //Case 2: Tile BELOW D is EITHER (NORMAL or RAMP_DOWN) (AND there could be a bridge over or tunnel below...)
                            if (aTileBelowD->mTileType == TILE_TYPE_NORMAL || aTileBelowD->mTileType == TILE_TYPE_RAMP_D) {
                                //In this case, we connect the one row of nodes... We should theoretically be able to
                                //connect all of them, although a situation may arise where we need to leave out corners?
                                
                                int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
                                int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                                
                                int aOffsetX = 0;
                                int aOffsetY = SUBDIVISIONS_PER_TILE;
                                while (aOffsetX <= SUBDIVISIONS_PER_TILE) {
                                    int aGridX = aStartGridX + aOffsetX;
                                    int aGridY = aStartGridY + aOffsetY;
                                    aNode = mUnitGridBase[aDepth-1][aGridX][aGridY];
                                    aNode->mGridZ = aDepth;
                                    mUnitGrid[aDepth][aGridX][aGridY] = aNode;
                                    aOffsetX++;
                                }
                            }
                        }
                    }
                    
                    if (aTile->mTileType == TILE_TYPE_RAMP_L) {
                        GameTile *aTileL      = GetTile(aTileGridX - 1, aTileGridY    , aDepth    );
                        GameTile *aTileBelowL = GetTile(aTileGridX - 1, aTileGridY    , aDepth - 1);
                        
                        //Case 1: Tile L us a RAMP_RIGHT... (Tile BELOW doesn't exist)
                        if (aTileL != 0 && aTileL->mTileType == TILE_TYPE_RAMP_R) {
                            //In this case, we don't reassign nodes...
                        } else if (aTileBelowL != 0) {
                            //Case 2: Tile BELOW L is EITHER (NORMAL or RAMP_LEFT) (AND there could be a bridge over or tunnel below...)
                            if (aTileBelowL->mTileType == TILE_TYPE_NORMAL || aTileBelowL->mTileType == TILE_TYPE_RAMP_L) {
                                //In this case, we connect the one row of nodes... We should theoretically be able to
                                //connect all of them, although a situation may arise where we need to leave out corners?
                                
                                int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
                                int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                                int aOffsetX = 0;
                                int aOffsetY = 0;
                                while (aOffsetY <= SUBDIVISIONS_PER_TILE) {
                                    int aGridX = aStartGridX + aOffsetX;
                                    int aGridY = aStartGridY + aOffsetY;
                                    aNode = mUnitGridBase[aDepth-1][aGridX][aGridY];
                                    aNode->mGridZ = aDepth;
                                    mUnitGrid[aDepth][aGridX][aGridY] = aNode;
                                    aOffsetY++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    
    
    
    
    //Step 3: Assign nodes to their parent tiles
    //        Block off nodes which are on a null tile.
    //        Block off nodes which directly border a null tile
    //   Keep in mind, some nodes will be duplicated on several tiles.
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    //No need to reset grid, we will fill the whole grid right here..
                    //aTile->ResetGrid();
                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        int aGridX = aStartGridX + aOffsetX;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mUnitGrid[aDepth][aGridX][aGridY];
                            aTile->mGrid[aOffsetX][aOffsetY] = aNode;
                            aNode->mBlocked = false;
                        }
                    }
                } else {
                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        int aGridX = aStartGridX + aOffsetX;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mUnitGrid[aDepth][aGridX][aGridY];
                        }
                    }
                }
            }
        }
    }
    
    
    //Step 4: Give all path nodes a default location...
    // (After this step, "normal" tiles will not need to change...)
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                float aCenterX = CX(aTileGridX, aDepth);
                float aCenterY = CY(aTileGridY, aDepth);
                //By default, the locations will be...
                float aLeftX = aCenterX - gTileSize2;
                float aRightX = aCenterX + gTileSize2;
                float aTopY = aCenterY - gTileSize2;
                float aBottomY = aCenterY + gTileSize2;
                float aSpanH = aRightX - aLeftX;
                float aSpanV = aBottomY - aTopY;
                int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                    float aPercentX = ((float)aOffsetX) / ((float)SUBDIVISIONS_PER_TILE);
                    int aGridX = aStartGridX + aOffsetX;
                    for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                        float aPercentY = ((float)aOffsetY) / ((float)SUBDIVISIONS_PER_TILE);
                        int aGridY = aStartGridY + aOffsetY;
                        aNode = mUnitGrid[aDepth][aGridX][aGridY];
                        aNode->mCenterX = aLeftX + aSpanH * aPercentX;
                        aNode->mCenterY = aTopY + aSpanV * aPercentY;
                    }
                }
            }
        }
    }
    
    //Step 4: Consider nodes which are not blocked, assign their
    //actual map locations properly...
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                
                ////////////////
                ////////////////
                // ... \\ . . //
                // . . // . . //
                // ... \\ ... //
                // . . // . . //
                // . . \\ ... //
                ////////////////
                ////////////////
                
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    float aCenterX = CX(aTileGridX, aDepth);
                    float aCenterY = CY(aTileGridY, aDepth);
                    float aLeftX = aCenterX - gTileSize2;
                    float aRightX = aCenterX + gTileSize2;
                    float aLeftTopY = aCenterY - gTileSize2;
                    float aRightTopY = aCenterY - gTileSize2;
                    float aLeftBottomY = aCenterY + gTileSize2;
                    float aRightBottomY = aCenterY + gTileSize2;
                    
                    if (aTile->mTileType == TILE_TYPE_RAMP_U) {
                        aLeftTopY  = CY(aTileGridY - 1, aDepth - 1) + gTileSize2;
                        aRightTopY = aLeftTopY;
                    } else if (aTile->mTileType == TILE_TYPE_RAMP_R) {
                        aRightTopY    = CY(aTileGridY, aDepth - 1) - gTileSize2;
                        aRightBottomY = CY(aTileGridY, aDepth - 1) + gTileSize2;
                    } else if (aTile->mTileType == TILE_TYPE_RAMP_D) {
                        aLeftBottomY  = CY(aTileGridY + 1, aDepth - 1) - gTileSize2;
                        aRightBottomY = aLeftBottomY;
                    } else if (aTile->mTileType == TILE_TYPE_RAMP_L) {
                        aLeftTopY    = CY(aTileGridY, aDepth - 1) - gTileSize2;
                        aLeftBottomY = CY(aTileGridY, aDepth - 1) + gTileSize2;
                    }
                    
                    //Assuming our U, R, D, L values are set properly, this will
                    //interpolate the actual path node positions...
                    float aSpanH = aRightX - aLeftX;
                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        float aPercentX = ((float)aOffsetX) / ((float)SUBDIVISIONS_PER_TILE);
                        int aGridX = aStartGridX + aOffsetX;
                        float aTopY = aLeftTopY + (aRightTopY - aLeftTopY) * aPercentX;
                        float aBottomY = aLeftBottomY + (aRightBottomY - aLeftBottomY) * aPercentX;
                        float aSpanV = aBottomY - aTopY;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            float aPercentY = ((float)aOffsetY) / ((float)SUBDIVISIONS_PER_TILE);
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mUnitGrid[aDepth][aGridX][aGridY];
                            aNode->mCenterX = aLeftX + aSpanH * aPercentX;
                            aNode->mCenterY = aTopY + aSpanV * aPercentY;
                        }
                    }
                }
            }
        }
    }
    
    //Step 5: Now we go through the laboreous process of blocking all
    //the nodes which do not elegantly connect to their neighbors.
    //Essentially, a free floating tile would have all 4 edges blocked and
    //only the center "meat" nodes unblocked.
    
    // oooo oooo oooo    o
    // oxxx xxxx xxxo   oo
    // oxxx xxxx xxxo  oxo
    // oooo oooo oxxo oxxo
    //           oxxo xxo
    //           oxxx xo
    //           oxxx o
    //           oooo
    
    // oooo oooo oooo
    // oxxx xxxx xxxo
    // oxxx xxx* *xxo
    
    // oxxx xxx* *xxo
    // oxxx xxxx xxxo
    // oooo oxxx xxxo
    
    //      oxxx xxxo
    //      oxxx xxxo
    //      oxxx xxxo
    //      oooo oooo
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    GameTile *aTileU = GetTile(aTileGridX    , aTileGridY - 1, aDepth);
                    GameTile *aTileR = GetTile(aTileGridX + 1, aTileGridY    , aDepth);
                    GameTile *aTileD = GetTile(aTileGridX    , aTileGridY + 1, aDepth);
                    GameTile *aTileL = GetTile(aTileGridX - 1, aTileGridY    , aDepth);
                    GameTile *aTileUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth);
                    GameTile *aTileUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth);
                    GameTile *aTileDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth);
                    GameTile *aTileDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth);
                    GameTile *aTileAboveUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth + 1);
                    GameTile *aTileAboveUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth + 1);
                    GameTile *aTileAboveDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth + 1);
                    GameTile *aTileAboveDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth + 1);
                    GameTile *aTileBelowUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth - 1);
                    GameTile *aTileBelowUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth - 1);
                    GameTile *aTileBelowDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth - 1);
                    GameTile *aTileBelowDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth - 1);
                    GameTile *aTileAboveU = GetTile(aTileGridX    , aTileGridY - 1, aDepth + 1);
                    GameTile *aTileAboveR = GetTile(aTileGridX + 1, aTileGridY    , aDepth + 1);
                    GameTile *aTileAboveD = GetTile(aTileGridX    , aTileGridY + 1, aDepth + 1);
                    GameTile *aTileAboveL = GetTile(aTileGridX - 1, aTileGridY    , aDepth + 1);
                    GameTile *aTileBelowU = GetTile(aTileGridX    , aTileGridY - 1, aDepth - 1);
                    GameTile *aTileBelowR = GetTile(aTileGridX + 1, aTileGridY    , aDepth - 1);
                    GameTile *aTileBelowD = GetTile(aTileGridX    , aTileGridY + 1, aDepth - 1);
                    GameTile *aTileBelowL = GetTile(aTileGridX - 1, aTileGridY    , aDepth - 1);
                    bool aBlockAll = false;
                    bool aBlockU = true;
                    bool aBlockR = true;
                    bool aBlockD = true;
                    bool aBlockL = true;
                    bool aBlockUL = false;
                    bool aBlockUR = false;
                    bool aBlockDL = false;
                    bool aBlockDR = false;
                    if (aTile->mBlocked || aTile->mTileType == TILE_TYPE_BLOCKED) {
                        aBlockAll = true;
                    }
                    if (aTile->mTileType == TILE_TYPE_NORMAL) {
                        aBlockUL = true;
                        aBlockUR = true;
                        aBlockDL = true;
                        aBlockDR = true;
                        if (aTileL && aTileU && aTileUL) {
                            if (aTileUL->mTileType == TILE_TYPE_NORMAL &&
                                aTileU->mTileType == TILE_TYPE_NORMAL &&
                                aTileL->mTileType == TILE_TYPE_NORMAL &&
                                aTileUL->mBlocked == false &&
                                aTileU->mBlocked == false &&
                                aTileL->mBlocked == false) {
                                aBlockUL = false;
                            }
                            if (aTileU->mTileType == TILE_TYPE_NORMAL && aTileL->mTileType == TILE_TYPE_RAMP_R && aTileUL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockUL = false;
                            }
                            if (aTileU->mTileType == TILE_TYPE_NORMAL && aTileL->mTileType == TILE_TYPE_RAMP_L && aTileUL->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockUL = false;
                            }
                            if (aTileL->mTileType == TILE_TYPE_NORMAL && aTileU->mTileType == TILE_TYPE_RAMP_U && aTileUL->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockUL = false;
                            }
                            if (aTileL->mTileType == TILE_TYPE_NORMAL && aTileU->mTileType == TILE_TYPE_RAMP_D && aTileUL->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockUL = false;
                            }
                        }
                        if (aTileU && aTileAboveL && aTileAboveUL) {
                            if (aTileU->mTileType == TILE_TYPE_NORMAL && aTileAboveL->mTileType == TILE_TYPE_RAMP_R && aTileAboveUL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockUL = false;
                            }
                        }
                        if (aTileL && aTileAboveUL && aTileAboveU) {
                            if (aTileL->mTileType == TILE_TYPE_NORMAL && aTileAboveU->mTileType == TILE_TYPE_RAMP_D && aTileAboveUL->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockUL = false;
                            }
                        }
                        if (aTileR && aTileU && aTileUR) {
                            if (aTileUR->mTileType == TILE_TYPE_NORMAL &&
                                aTileU->mTileType == TILE_TYPE_NORMAL &&
                                aTileR->mTileType == TILE_TYPE_NORMAL &&
                                aTileUR->mBlocked == false &&
                                aTileU->mBlocked == false &&
                                aTileR->mBlocked == false) {
                                aBlockUR = false;
                            }
                            if (aTileU->mTileType == TILE_TYPE_NORMAL && aTileR->mTileType == TILE_TYPE_RAMP_L && aTileUR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockUR = false;
                            }
                            if (aTileU->mTileType == TILE_TYPE_NORMAL && aTileR->mTileType == TILE_TYPE_RAMP_R && aTileUR->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockUR = false;
                            }
                            if (aTileR->mTileType == TILE_TYPE_NORMAL && aTileU->mTileType == TILE_TYPE_RAMP_U && aTileUR->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockUR = false;
                            }
                            if (aTileR->mTileType == TILE_TYPE_NORMAL && aTileU->mTileType == TILE_TYPE_RAMP_D && aTileUR->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockUR = false;
                            }
                        }
                        if (aTileAboveR && aTileAboveUR && aTileU) {
                            if (aTileU->mTileType == TILE_TYPE_NORMAL && aTileAboveR->mTileType == TILE_TYPE_RAMP_L && aTileAboveUR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockUR = false;
                            }
                        }
                        if (aTileR && aTileAboveUR && aTileAboveU) {
                            if (aTileR->mTileType == TILE_TYPE_NORMAL && aTileAboveU->mTileType == TILE_TYPE_RAMP_D && aTileAboveUR->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockUR = false;
                            }
                        }
                        if (aTileL && aTileD && aTileDL) {
                            if (aTileDL->mTileType == TILE_TYPE_NORMAL &&
                                aTileD->mTileType == TILE_TYPE_NORMAL &&
                                aTileL->mTileType == TILE_TYPE_NORMAL &&
                                aTileDL->mBlocked == false &&
                                aTileD->mBlocked == false &&
                                aTileL->mBlocked == false) {
                                aBlockDL = false;
                            }
                            if (aTileD->mTileType == TILE_TYPE_NORMAL && aTileL->mTileType == TILE_TYPE_RAMP_R && aTileDL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockDL = false;
                            }
                            if (aTileD->mTileType == TILE_TYPE_NORMAL && aTileL->mTileType == TILE_TYPE_RAMP_L && aTileDL->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockDL = false;
                            }
                            if (aTileL->mTileType == TILE_TYPE_NORMAL && aTileD->mTileType == TILE_TYPE_RAMP_U && aTileDL->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockDL = false;
                            }
                            if (aTileL->mTileType == TILE_TYPE_NORMAL && aTileD->mTileType == TILE_TYPE_RAMP_D && aTileDL->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockDL = false;
                            }
                        }
                        if (aTileAboveL && aTileAboveDL && aTileD) {
                            if (aTileD->mTileType == TILE_TYPE_NORMAL && aTileAboveL->mTileType == TILE_TYPE_RAMP_R && aTileAboveDL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockDL = false;
                            }
                        }
                        if (aTileL && aTileAboveDL && aTileAboveD) {
                            if (aTileL->mTileType == TILE_TYPE_NORMAL && aTileAboveD->mTileType == TILE_TYPE_RAMP_U && aTileAboveDL->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockDL = false;
                            }
                        }
                        if (aTileR && aTileD && aTileDR) {
                            if (aTileDR->mTileType == TILE_TYPE_NORMAL &&
                                aTileD->mTileType == TILE_TYPE_NORMAL &&
                                aTileR->mTileType == TILE_TYPE_NORMAL &&
                                aTileDR->mBlocked == false &&
                                aTileD->mBlocked == false &&
                                aTileR->mBlocked == false) {
                                aBlockDR = false;
                            }
                            if (aTileD->mTileType == TILE_TYPE_NORMAL && aTileR->mTileType == TILE_TYPE_RAMP_L && aTileDR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockDR = false;
                            }
                            if (aTileD->mTileType == TILE_TYPE_NORMAL && aTileR->mTileType == TILE_TYPE_RAMP_R && aTileDR->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockDR = false;
                            }
                            if (aTileR->mTileType == TILE_TYPE_NORMAL && aTileD->mTileType == TILE_TYPE_RAMP_U && aTileDR->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockDR = false;
                            }
                            if (aTileR->mTileType == TILE_TYPE_NORMAL && aTileD->mTileType == TILE_TYPE_RAMP_D && aTileDR->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockDR = false;
                            }
                        }
                        if (aTileAboveR && aTileAboveDR && aTileD) {
                            if (aTileD->mTileType == TILE_TYPE_NORMAL && aTileAboveR->mTileType == TILE_TYPE_RAMP_L && aTileAboveDR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockDR = false;
                            }
                        }
                        if (aTileR && aTileAboveDR && aTileAboveD) {
                            if (aTileR->mTileType == TILE_TYPE_NORMAL && aTileAboveD->mTileType == TILE_TYPE_RAMP_U && aTileAboveDR->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockDR = false;
                            }
                        }
                        if (aTileR) {
                            if (aTileR->mBlocked == false &&
                                (aTileR->mTileType == TILE_TYPE_NORMAL || aTileR->mTileType == TILE_TYPE_RAMP_R)) {
                                aBlockR = false;
                            }
                        }
                        if (aTileAboveR) {
                            if (aTileAboveR->mBlocked == false && aTileAboveR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockR = false;
                            }
                        }
                        if (aTileL) {
                            if (aTileL->mBlocked == false &&
                                (aTileL->mTileType == TILE_TYPE_NORMAL || aTileL->mTileType == TILE_TYPE_RAMP_L)) {
                                aBlockL = false;
                            }
                        }
                        if (aTileAboveL) {
                            if (aTileAboveL->mBlocked == false && aTileAboveL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockL = false;
                            }
                        }
                        if (aTileU) {
                            if (aTileU->mBlocked == false &&
                                (aTileU->mTileType == TILE_TYPE_NORMAL || aTileU->mTileType == TILE_TYPE_RAMP_U)) {
                                aBlockU = false;
                            }
                        }
                        if (aTileAboveU) {
                            if (aTileAboveU->mBlocked == false && aTileAboveU->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockU = false;
                            }
                        }
                        if (aTileD) {
                            if (aTileD->mBlocked == false &&
                                (aTileD->mTileType == TILE_TYPE_NORMAL || aTileD->mTileType == TILE_TYPE_RAMP_D)) {
                                aBlockD = false;
                            }
                        }
                        if (aTileAboveD) {
                            if (aTileAboveD->mBlocked == false && aTileAboveD->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockD = false;
                            }
                        }
                    } else if (aTile->mTileType == TILE_TYPE_RAMP_U) {
                        if (aTileBelowU) {
                            if (aTileBelowU->mBlocked == false && (aTileBelowU->mTileType == TILE_TYPE_NORMAL || aTileBelowU->mTileType == TILE_TYPE_RAMP_U)) {
                                aBlockU = false;
                            }
                        }
                        if (aTileU) {
                            if (aTileU->mBlocked == false && aTileU->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockU = false;
                            }
                        }
                        if (aTileD) {
                            if (aTileD->mBlocked == false && (aTileD->mTileType == TILE_TYPE_NORMAL || aTileD->mTileType == TILE_TYPE_RAMP_D)) {
                                aBlockD = false;
                            }
                        }
                        if (aTileAboveD) {
                            if (aTileAboveD->mBlocked == false && (aTileAboveD->mTileType == TILE_TYPE_RAMP_U)) {
                                aBlockD = false;
                            }
                        }
                        if (aTileR != 0 && aTileR->mTileType == TILE_TYPE_RAMP_U) {
                            aBlockR = false;
                        }
                        if (aTileL != 0 && aTileL->mTileType == TILE_TYPE_RAMP_U) {
                            aBlockL = false;
                        }
                        if (aTileL != 0 && aTileBelowU && aTileBelowUL) {
                            if (aTileL->mTileType == TILE_TYPE_RAMP_U) {
                                if (aTileBelowU->mTileType != aTileBelowUL->mTileType) {
                                    aBlockUL = true;
                                }
                            }
                        }
                        if (aTileR != 0 && aTileBelowU && aTileBelowUR) {
                            if (aTileR->mTileType == TILE_TYPE_RAMP_U) {
                                if (aTileBelowU->mTileType != aTileBelowUR->mTileType) {
                                    aBlockUR = true;
                                }
                            }
                        }
                    } else if (aTile->mTileType == TILE_TYPE_RAMP_R) {
                        if (aTileBelowR) {
                            if (aTileBelowR->mBlocked == false && (aTileBelowR->mTileType == TILE_TYPE_NORMAL || aTileBelowR->mTileType == TILE_TYPE_RAMP_R)) {
                                aBlockR = false;
                            }
                        }
                        if (aTileR) {
                            if (aTileR->mBlocked == false && aTileR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockR = false;
                            }
                        }
                        if (aTileL) {
                            if (aTileL->mBlocked == false && (aTileL->mTileType == TILE_TYPE_NORMAL || aTileL->mTileType == TILE_TYPE_RAMP_L)) {
                                aBlockL = false;
                            }
                        }
                        if (aTileAboveL) {
                            if (aTileAboveL->mBlocked == false && (aTileAboveL->mTileType == TILE_TYPE_RAMP_R)) {
                                aBlockL = false;
                            }
                        }
                        if (aTileU != 0 && aTileU->mTileType == TILE_TYPE_RAMP_R) {
                            aBlockU = false;
                        }
                        if (aTileD != 0 && aTileD->mTileType == TILE_TYPE_RAMP_R) {
                            aBlockD = false;
                        }
                        if (aTileU != 0 && aTileBelowR && aTileBelowUR) {
                            if (aTileU->mTileType == TILE_TYPE_RAMP_R) {
                                if (aTileBelowR->mTileType != aTileBelowUR->mTileType) {
                                    aBlockUR = true;
                                }
                            }
                        }
                        if (aTileD != 0 && aTileBelowR && aTileBelowDR) {
                            if (aTileD->mTileType == TILE_TYPE_RAMP_R) {
                                if (aTileBelowR->mTileType != aTileBelowDR->mTileType) {
                                    aBlockDR = true;
                                }
                            }
                        }
                    } else if (aTile->mTileType == TILE_TYPE_RAMP_D) {
                        if (aTileBelowD) {
                            if (aTileBelowD->mBlocked == false && (aTileBelowD->mTileType == TILE_TYPE_NORMAL || aTileBelowD->mTileType == TILE_TYPE_RAMP_D)) {
                                aBlockD = false;
                            }
                        }
                        if (aTileD) {
                            if (aTileD->mBlocked == false && aTileD->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockD = false;
                            }
                        }
                        if (aTileU) {
                            if (aTileU->mBlocked == false && (aTileU->mTileType == TILE_TYPE_NORMAL || aTileU->mTileType == TILE_TYPE_RAMP_U)) {
                                aBlockU = false;
                            }
                        }
                        if (aTileAboveU) {
                            if (aTileAboveU->mBlocked == false && (aTileAboveU->mTileType == TILE_TYPE_RAMP_D)) {
                                aBlockU = false;
                            }
                        }
                        if (aTileR != 0 && aTileR->mTileType == TILE_TYPE_RAMP_D) {
                            aBlockR = false;
                        }
                        if (aTileL != 0 && aTileL->mTileType == TILE_TYPE_RAMP_D) {
                            aBlockL = false;
                        }
                        if (aTileR != 0 && aTileBelowD && aTileBelowDR) {
                            if (aTileR->mTileType == TILE_TYPE_RAMP_D) {
                                if (aTileBelowD->mTileType != aTileBelowDR->mTileType) {
                                    aBlockDR = true;
                                }
                            }
                        }
                        if (aTileL != 0 && aTileBelowD && aTileBelowDL) {
                            if (aTileL->mTileType == TILE_TYPE_RAMP_D) {
                                if (aTileBelowD->mTileType != aTileBelowDL->mTileType) {
                                    aBlockDL = true;
                                }
                            }
                        }
                    } else if (aTile->mTileType == TILE_TYPE_RAMP_L) {
                        if (aTileBelowL) {
                            if (aTileBelowL->mBlocked == false && (aTileBelowL->mTileType == TILE_TYPE_NORMAL || aTileBelowL->mTileType == TILE_TYPE_RAMP_L)) {
                                aBlockL = false;
                            }
                        }
                        if (aTileL) {
                            if (aTileL->mBlocked == false && aTileL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockL = false;
                            }
                        }
                        if (aTileR) {
                            if (aTileR->mBlocked == false && (aTileR->mTileType == TILE_TYPE_NORMAL || aTileR->mTileType == TILE_TYPE_RAMP_R)) {
                                aBlockR = false;
                            }
                        }
                        if (aTileAboveR) {
                            if (aTileAboveR->mBlocked == false && (aTileAboveR->mTileType == TILE_TYPE_RAMP_L)) {
                                aBlockR = false;
                            }
                        }
                        if (aTileU != 0 && aTileU->mTileType == TILE_TYPE_RAMP_L) {
                            aBlockU = false;
                        }
                        if (aTileD != 0 && aTileD->mTileType == TILE_TYPE_RAMP_L) {
                            aBlockD = false;
                        }
                        if (aTileU != 0 && aTileBelowL && aTileBelowUL) {
                            if (aTileU->mTileType == TILE_TYPE_RAMP_L) {
                                if (aTileBelowL->mTileType != aTileBelowUL->mTileType) {
                                    aBlockUL = true;
                                }
                            }
                        }
                        if (aTileD != 0 && aTileBelowL && aTileBelowDL) {
                            if (aTileD->mTileType == TILE_TYPE_RAMP_L) {
                                if (aTileBelowL->mTileType != aTileBelowDL->mTileType) {
                                    aBlockDL = true;
                                }
                            }
                        }
                    }
                    
                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        int aGridX = aStartGridX + aOffsetX;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mUnitGrid[aDepth][aGridX][aGridY];
                            if (aBlockAll) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetX == 0 && aBlockL) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetY == 0 && aBlockU) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetX == SUBDIVISIONS_PER_TILE && aBlockR) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetY == SUBDIVISIONS_PER_TILE && aBlockD) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetX == 0 && aOffsetY == 0 && aBlockUL) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetX == SUBDIVISIONS_PER_TILE && aOffsetY == 0 && aBlockUR) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetX == 0 && aOffsetY == SUBDIVISIONS_PER_TILE && aBlockDL) {
                                aNode->mBlocked = true;
                            }
                            if (aOffsetX == SUBDIVISIONS_PER_TILE && aOffsetY == SUBDIVISIONS_PER_TILE && aBlockDR) {
                                aNode->mBlocked = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void GameArena::UpdateOneFrame() {
    mOneFrameUpdateEnqueued = true;
    mUpdateEnabled = false;
}

void GameArena::ClearTiles(int pDepth) {
    if (mTile) {
        if (pDepth >= 0 && pDepth < GRID_DEPTH) {
            for (int aGridX=0;aGridX<mTileGridWidthTotal;aGridX++) {
                for (int aGridY=0;aGridY<mTileGridHeightTotal;aGridY++) {
                    DeleteTile(aGridX, aGridY, pDepth);
                }
            }
        }
        RefreshUnitGridNodes();
    }
}

void GameArena::ClearTiles() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        ClearTiles(aDepth);
    }
}

void GameArena::Flood(int pDepth) {
    if (pDepth >= 0 && pDepth < GRID_DEPTH) {
        ClearTiles(pDepth);
        for (int aGridX=0;aGridX<mTileGridWidthTotal;aGridX++) {
            for (int aGridY=0;aGridY<mTileGridHeightTotal;aGridY++) {
                //mTile[pDepth][
                GameTile *aTile = new GameTile();
                mTile[pDepth][aGridX][aGridY] = aTile;
                aTile->mTileType = TILE_TYPE_NORMAL;
                aTile->SetUp(aGridX, aGridY, pDepth);
            }
        }
        RefreshUnitGridNodes();
    }
}

void GameArena::IncreaseBuffer() {
    
}

void GameArena::DecreaseBuffer() {
    
}

void GameArena::IncreaseWidth() {
    
}

void GameArena::DecreaseWidth() {
    
}

void GameArena::IncreaseHeight() {
    
}

void GameArena::DecreaseHeight() {
    
}

void GameArena::Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {
    SizeGrid(pWidth, pHeight, pGridBufferH, pGridBufferV);
    int aDepth = 1;
    for (int aX=0;aX<mTileGridWidthActive;aX++) {
        for (int aY=0;aY<mTileGridHeightActive;aY++) {
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV] = new GameTile();
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV]->SetUp(aX + mTileGridBufferH, aY + mTileGridBufferV, aDepth);
        }
    }
    for (int aX = 0;aX < mTileGridWidthActive;aX++) {
        for (int aY=0;aY<mTileGridHeightActive;aY++) {
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV] = new GameTile();
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV]->SetUp(aX + mTileGridBufferH, aY + mTileGridBufferV, aDepth);
        }
    }
    aDepth = 0;
    for (int aX = 0;aX < mTileGridWidthTotal;aX++) {
        for (int aY = 0;aY < mTileGridHeightTotal;aY++) {
            if (aX < mTileGridBufferH || aY < mTileGridBufferV || aX >= (mTileGridBufferH + mTileGridWidthActive) || aY >= (mTileGridBufferV + mTileGridHeightActive)) {
                mTile[aDepth][aX][aY] = new GameTile();
                mTile[aDepth][aX][aY]->SetUp(aX, aY, aDepth);
            }
        }
    }
    ComputeAllowedPlacements();
    ComputePathConnections();
}

void GameArena::GenerateUnitGrid() {
    
    
    if (mTileGridWidthTotal <= 0 || mTileGridHeightTotal <= 0) { return; }
    
    //Step 1: Generate all path nodes, assign all to their respective parent.
    PathNode *aNode = 0;
    mUnitGridWidth = (mTileGridWidthTotal * SUBDIVISIONS_PER_TILE) + 1;
    mUnitGridHeight = (mTileGridHeightTotal * SUBDIVISIONS_PER_TILE) + 1;

    int aUnitGridCount = 0;
    mUnitGridBase = new PathNode***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mUnitGridBase[aDepth] = new PathNode**[mUnitGridWidth];
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            mUnitGridBase[aDepth][aGridX] = new PathNode*[mUnitGridHeight];
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                aUnitGridCount++;
                aNode = new PathNode();
                aNode->mGridX = aGridX;
                aNode->mGridY = aGridY;
                aNode->mGridZ = aDepth;
                mUnitGridBase[aDepth][aGridX][aGridY] = aNode;
            }
        }
    }
    printf("Unit Grid Count = [%d]\n", aUnitGridCount);
    
    mUnitGrid = new PathNode***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mUnitGrid[aDepth] = new PathNode**[mUnitGridWidth];
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            mUnitGrid[aDepth][aGridX] = new PathNode*[mUnitGridHeight];
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                mUnitGrid[aDepth][aGridX][aGridY] = mUnitGridBase[aDepth][aGridX][aGridY];
            }
        }
    }
    
    
    mWalkAllowed = new bool**[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mWalkAllowed[aDepth] = new bool*[mUnitGridWidth];
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            mWalkAllowed[aDepth][aGridX] = new bool[mUnitGridHeight];
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                mWalkAllowed[aDepth][aGridX][aGridY] = false;
            }
        }
    }
    
    RefreshUnitGridNodes();
    ComputePathConnections();
}

void GameArena::Clear() {
    if (mTowerAllowed) {
        for (int i=0;i<mTileGridWidthTotal;i++)delete [] mTowerAllowed[i];
        delete [] mTowerAllowed;
    }
    mTowerAllowed = 0;
    
    if (mTile) {
        
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mTileGridWidthTotal;i++) {
                for (int n=0;n<mTileGridHeightTotal;n++) {
                    DeleteTile(i, n, aDepth);
                }
            }
        }
        
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mTileGridWidthTotal;i++) {
                delete [] mTile[aDepth][i];
            }
            delete [] mTile[aDepth];
        }
        delete [] mTile;
    }
    mTile = 0;
    mTileGridWidthTotal = 0;
    mTileGridHeightTotal = 0;
    
    if (mUnitGridBase) {
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
                for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                    mDeletedNodeList += mUnitGridBase[aDepth][aGridX][aGridY];
                }
            }
        }
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mUnitGridWidth;i++) { delete [] mUnitGridBase[aDepth][i]; }
            delete [] mUnitGridBase[aDepth];
        }
        delete [] mUnitGridBase;
        mUnitGridBase = 0;
        
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mUnitGridWidth;i++) { delete [] mWalkAllowed[aDepth][i]; }
            delete [] mWalkAllowed[aDepth];
        }
        
        delete [] mWalkAllowed;
        mWalkAllowed = 0;
        
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mUnitGridWidth;i++) { delete [] mUnitGrid[aDepth][i]; }
            delete [] mUnitGrid[aDepth];
        }
        delete [] mUnitGrid;
        mUnitGrid = 0;
    }
    
    mUnitGridWidth = 0;
    mUnitGridHeight = 0;
}

void GameArena::SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {
    
    Clear();
    
    mTileGridBufferH = pGridBufferH;
    mTileGridBufferV = pGridBufferV;
    mTileGridWidthActive = pWidth;
    mTileGridHeightActive = pHeight;
    mTileGridWidthTotal = mTileGridWidthActive + mTileGridBufferH * 2;
    mTileGridHeightTotal = mTileGridHeightActive + mTileGridBufferV * 2;
    mTile = new GameTile***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mTile[aDepth] = new GameTile**[mTileGridWidthTotal];
        for (int aX=0;aX<mTileGridWidthTotal;aX++) {
            mTile[aDepth][aX] = new GameTile*[mTileGridHeightTotal];
            for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                mTile[aDepth][aX][aY] = 0;
            }
        }
    }
    
    mTowerAllowed = new bool*[mTileGridWidthTotal];
    for (int aX=0;aX<mTileGridWidthTotal;aX++) {
        mTowerAllowed[aX] = new bool[mTileGridHeightTotal];
        for (int aY=0;aY<mTileGridHeightTotal;aY++) {
            mTowerAllowed[aX][aY] = true;
        }
    }
    
    gArenaWidth = mTileGridWidthTotal * gTileSize;
    gArenaWidth2 = gArenaWidth * 0.5f;
    gArenaHeight = mTileGridHeightTotal * gTileSize;
    gArenaHeight2 = gArenaHeight * 0.5f;
    
    gArenaActiveWidth = mTileGridWidthActive * gTileSize;
    gArenaActiveWidth2 = gArenaActiveWidth * 0.5f;
    gArenaActiveHeight = mTileGridHeightActive * gTileSize;
    gArenaActiveHeight2 = gArenaActiveHeight * 0.5f;
    gArenaActiveX = pGridBufferH * gTileSize;
    gArenaActiveY = pGridBufferV * gTileSize;
    
    GenerateUnitGrid();
}

void GameArena::Save(const char *pPath) {
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    aPath = (gDirDocuments + aPath);
    
    FXML aXML;
    
    FXMLTag *aArenaTag = new FXMLTag("game_arena");
    aXML.mRoot = aArenaTag;
    
    aArenaTag->AddParam("grid_width_active", FString(mTileGridWidthActive).c());
    aArenaTag->AddParam("grid_height_active", FString(mTileGridHeightActive).c());
    
    aArenaTag->AddParam("grid_buffer_h", FString(mTileGridBufferH).c());
    aArenaTag->AddParam("grid_buffer_v", FString(mTileGridBufferV).c());
    
    FXMLTag *aTileListTag = new FXMLTag("tile_list");
    *aArenaTag += aTileListTag;
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mTileGridWidthTotal;aX++) {
            for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                if (mTile[aDepth][aX][aY]) {
                    *aTileListTag += mTile[aDepth][aX][aY]->Save();
                }
            }
        }
    }
    FXMLTag *aPathListTag = new FXMLTag("path_list");
    *aArenaTag += aPathListTag;
    EnumList (AnimatedLevelPath, aPath, mPathList) {
        *aPathListTag += aPath->Save();
    }
    
    aXML.Print();
    aXML.Save(aPath.c());
}

void GameArena::Load(const char *pPath) {
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    
    FXML aXML;
    aXML.Load(aPath);
    FreeList(AnimatedLevelPath, mPathList);
    FXMLTag *aArenaTag = aXML.GetRoot();
    if (aArenaTag) {
        int aTileGridWidthActive = FString(aArenaTag->GetParamValue("grid_width_active")).ToInt();
        int aTileGridHeightActive = FString(aArenaTag->GetParamValue("grid_height_active")).ToInt();
        int aTileGridBufferH = FString(aArenaTag->GetParamValue("grid_buffer_h")).ToInt();
        int aTileGridBufferV = FString(aArenaTag->GetParamValue("grid_buffer_v")).ToInt();
        int aTileGridWidthTotal = aTileGridWidthActive + aTileGridBufferH * 2;
        int aTileGridHeightTotal = aTileGridHeightActive + aTileGridBufferV * 2;
        if (aTileGridWidthTotal > 0 && aTileGridHeightTotal > 0) {
            SizeGrid(aTileGridWidthActive, aTileGridHeightActive, aTileGridBufferH, aTileGridBufferV);
            EnumTagsMatching (aArenaTag, aTileListTag, "tile_list") {
                EnumTags (aTileListTag, aTileTag) {
                    GameTile *aTile = new GameTile();
                    aTile->Load(aTileTag);
                    if (aTile->mGridX >= 0 && aTile->mGridY >= 0 && aTile->mGridZ >=0 && aTile->mGridX < mTileGridWidthTotal && aTile->mGridY < mTileGridHeightTotal && aTile->mGridZ < GRID_DEPTH) {
                        mTile[aTile->mGridZ][aTile->mGridX][aTile->mGridY] = aTile;
                    }
                }
            }
            
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
    }
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    if (aTile->mTileType == TILE_TYPE_BLOCKED) {
                        aTile->mBlocked = true;
                    }
                }
            }
        }
    }
    
    RefreshUnitGridNodes();
    ComputeAllowedPlacements();
    ComputePathConnections();
    
}


void GameArena::TestModeDidChange(int pPreviousMode, int pCurrentMode) {
    
}



