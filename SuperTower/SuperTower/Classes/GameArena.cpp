//
//  GameArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "GameArena.h"

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

    Load("test_level_1.xml");
    //Load("super_basic_hifi_path_test");


    //Load("ramps_test_01.xml");

    //Load("pathing_map_02_inverse.xml");
    //Load("45_degree_corners.xml");
    //Load("45_degree_corners_inverse.xml");

    //Load("crazy_ramps");
    //Load("crazy_ramps");

    //Load("many_wide_ramps");

    mTestNinjaRotation = 0.0f;
    mTestNinjaFrame = 0.0f;
}

GameArena::~GameArena() {
    gArena = 0;
    
}

void GameArena::Update() {

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

    /*
     for(int i=0;i<mTileGridWidth;i++)
     {
     for(int n=0;n<mTileGridHeight;n++)
     {
     if(mTile[i][n])
     {
     mTile[i][n]->Update();
     }
     }
     }
     */
    
    /*
     
     EnumList(Unit, aUnit, mUnitList)
     {
     aUnit->Update();
     
     if(aUnit->mWalking == false)
     {
     if(gRand.Get(40) == 22)
     {
     //mWalking
     
     bool aFail = true;
     
     
     while(aFail)
     {
     int aDirX = gRand.Get(3) - 1;
     int aDirY = gRand.Get(3) - 1;
     
     if(aDirX != 0 || aDirY != 0)
     {
     int aTargetX = aUnit->mTileGridX + aDirX;
     int aTargetY = aUnit->mTileGridY + aDirY;
     
     if(aTargetX >= 0 && aTargetY >= 0 && aTargetX < mTileGridWidth && aTargetY < mTileGridHeight)
     {
     
     aUnit->WalkTo(aTargetX, aTargetY);
     aFail = false;
     }
     }
     }
     }
     }
     }
     
     */
    
    /*
     EnumList(Tower, aTower, mTowerList)
     {
     aTower->Update();
     
     if(aTower->mCoolDownTime <= 0)
     {
     
     }
     }
     */

    mUnitCollection.Update();

    mTowerCollection.Update();

    EnumList (AnimatedLevelPath, aPath, mPathList) {
        aPath->Update();
    }
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

        EnumList(Unit, aUnit, mUnitCollection.mObjectList) {
            if (aUnit->mKill == 0 && aUnit->mGridZ == aDepth) {
                aUnit->Draw();
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
                        PathNode *aConnectedNode = aTile1->mPathConnection[i].mNode;
                        //Graphics::DrawArrow(aTile1->mCenterX, aTile1->mCenterY, aConnectedNode->mCenterX, aConnectedNode->mCenterY);
                    }
                }
            }
        }


        /*
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];
                for (int i=0;i<aNode->mPathConnectionCount;i++) {
                    PathNode *aConnectedNode = aNode->mPathConnection[i].mNode;

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
        */
    }
         

    int aSwatchIndex = 0;

    /*

     for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
     for (int aX=0;aX<mTileGridWidthTotal;aX++) {
     for (int aY=0;aY<mTileGridHeightTotal;aY++) {
     GameTile *aTile = mTile[aDepth][aX][aY];
     if (aTile) {
     Graphics::SetColorSwatch(aSwatchIndex, 0.35f);
     for (int i=0;i<=SUBDIVISIONS_PER_TILE;i++) {
     for (int n=0;n<=SUBDIVISIONS_PER_TILE;n++) {
     PathNode *aNode = aTile->mGrid[i][n];
     if (aNode) {
     Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 2.0f);
     }
     }
     }
     aSwatchIndex++;
     }
     }
     }
     }
     */

    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];

                if (aNode->mBlocked == false) {
                    Graphics::SetColor(0.95f, 0.95f, 0.95f, mTileOpacity[aDepth]);
                    Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 3.0f);

                    Graphics::SetColor(0.0f, 0.125f, 0.125f, mTileOpacity[aDepth]);
                    Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 2.25f);

                    if (aDepth == 0) {
                        Graphics::SetColor(1.0f, 0.75f, 0.25f, mTileOpacity[aDepth]);
                    }
                    if (aDepth == 1) {
                        Graphics::SetColor(0.125f, 0.75f, 0.75f, mTileOpacity[aDepth]);
                    }
                    if (aDepth == 2) {
                        Graphics::SetColor(0.855f, 0.125f, 0.85f, mTileOpacity[aDepth]);
                    }

                    Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 1.5f);
                }
            }
        }
    }

    //Graphics::SetColor();
    //gApp->mNinja.Center(mTestNinjaRotation, mTestNinjaFrame, 0.0f, 0.0f);

    Graphics::SetColor();
    mTestUnitPath.DrawMarkers();
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
        
        //Update unit paths...
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
    if (pPath) {
        GameTile *aStartTile = GetTile(pPath->mStartX, pPath->mStartY, pPath->mStartZ);
        if (aStartTile) {
            mTileList.Add(aStartTile);
        }
        int aCap = (pPath->mLength-1);
        for (int i=1;i<aCap;i++) {
            int aGridX = pPath->mPathX[i];
            int aGridY = pPath->mPathY[i];
            int aGridZ = pPath->mPathZ[i];
            GameTile *aTile = GetTile(aGridX, aGridY, aGridZ);
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

void GameArena::SpawnUnitsOnPath(FList *pUnitList, LevelPath *pPath) {

    //We may not be able to spawn ALL units on the
    //first tile, so we will try a few if necessary...
    DumpLevelPathToTileList(pPath);

    PathNode *aNode = 0;
    PathNode *aEndNode = 0;
    int aTileIndex = pPath->mLength - 1;

    while (aEndNode == 0 && aTileIndex >= 0) {
        GameTile *aTile = (GameTile *)(mTileList[aTileIndex]);
        int aStartGridX = aTile->mGridX * SUBDIVISIONS_PER_TILE;
        int aStartGridY = aTile->mGridY * SUBDIVISIONS_PER_TILE;
        int aGridZ = aTile->mGridZ;

        int aPrimeTargetX = aStartGridX + SUBDIVISIONS_PER_TILE / 2;
        int aPrimeTargetY = aStartGridY + SUBDIVISIONS_PER_TILE / 2;

        aNode = GetGridNode(aPrimeTargetX, aPrimeTargetY, aGridZ);
        if (aNode->IsBlocked() == false) {
            printf("CHOOSING END NODE: EXPECTED\n");
            aEndNode = aNode;
        }
        for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE && aEndNode==0;aOffsetX++) {
            int aGridX = aStartGridX + aOffsetX;
            for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE && aEndNode==0;aOffsetY++) {
                int aGridY = aStartGridY + aOffsetY;
                aNode = GetGridNode(aGridX, aGridY, aGridZ);
                if (aNode->IsBlocked() == false) {
                    printf("CHOOSING END NODE: ODDBALL\n");
                    aEndNode = aNode;
                }
            }
        }

        aTileIndex--;
    }


    aNode = 0;
    aTileIndex = 0;
    bool aPlacedUnit = false;
    for (int aUnitIndex=0;aUnitIndex<pUnitList->mCount;aUnitIndex++) {
        Unit *aUnit = (Unit *)(pUnitList->Fetch(aUnitIndex));
        aPlacedUnit = false;

        //TODO: Verify this works when we spawn like 20 units near top of ramp (all 4 dirs)
        while (aPlacedUnit == false && aTileIndex < mTileList.mCount) {

            //Note: The edge node rows/cols might be from a different level,
            //but we have duplicated connecting rows/cols
            GameTile *aTile = (GameTile *)(mTileList[aTileIndex]);

            int aStartGridX = aTile->mGridX * SUBDIVISIONS_PER_TILE;
            int aStartGridY = aTile->mGridY * SUBDIVISIONS_PER_TILE;
            int aGridZ = aTile->mGridZ;

            for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE && aPlacedUnit==false;aOffsetX++) {
                int aGridX = aStartGridX + aOffsetX;
                for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE && aPlacedUnit==false;aOffsetY++) {
                    int aGridY = aStartGridY + aOffsetY;

                    aNode = GetGridNode(aGridX, aGridY, aGridZ);

                    if (aNode->IsBlocked() == false) {

                        aUnit->PlaceOnGrid(aNode, aEndNode, pPath);

                        AddUnit(aUnit);

                        aNode->mOccupied = true;
                        aPlacedUnit = true;
                    }

                    //aNode = mUnitGrid[aDepth][aGridX][aGridY];
                    //aNode->mOccupied = true;
                }
            }

            if (aPlacedUnit == false) {
                aTileIndex++;
            }
        }

        //aUnitIndex
    }


    EnumList(GameTile, aTile, mTileList) {


    }



}

void GameArena::Click(float pX, float pY) {
    //Test mode stuff..
    if (true) { //Unit Tests
        LevelPath *aSelectedPath = AttemptPathSelect(pX, pY);
        if (aSelectedPath) {
            //Spawn some test units.
            int aSpawnCount = 3 + gRand.Get(8);
            FList aUnitList;
            for (int aUnitIndex=0;aUnitIndex<aSpawnCount;aUnitIndex++) {
                Unit *aUnit = new Unit();
                aUnit->mWalkSpeed = 2.25f;
                aUnitList.Add(aUnit);
            }
            SpawnUnitsOnPath(&aUnitList, aSelectedPath);
        }
        return;
    }


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

void GameArena::AddUnit(Unit *pUnit) {
    if (pUnit) {
        mUnitCollection.Add(pUnit);
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

    ComputeGridConnections();
}

void GameArena::ComputeGridConnections() {

    //1.) Reset all subgrid path nodes.
    PathNode *aNode = 0;
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                aNode = mUnitGrid[aDepth][aGridX][aGridY];
                aNode->PathReset();
            }
        }
    }

    //2.) Make all "occupied" tiles entirely occuiped in subgrid.
    //    (These are tiles where a tower lies)
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

    //3.) ... Link up nodes insernally among tiles...

    // o o o o
    // |X|X|X|
    // o-o-o-o

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
    ComputeTestPath();
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

void GameArena::Clear(int pDepth) {
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

void GameArena::Clear() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        Clear(aDepth);
    }
}

void GameArena::Flood(int pDepth) {
    if (pDepth >= 0 && pDepth < GRID_DEPTH) {
        Clear(pDepth);
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
    GenerateUnitGrid();
    ComputePathConnections();
}

void GameArena::GenerateUnitGrid() {
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
            for (int i=0;i<mUnitGridWidth;i++) { delete [] mUnitGrid[aDepth][i]; }
            delete [] mUnitGrid[aDepth];
        }
        delete [] mUnitGrid;
        mUnitGrid = 0;
    }

    mUnitGridWidth = 0;
    mUnitGridHeight = 0;

    if (mTileGridWidthTotal <= 0 || mTileGridHeightTotal <= 0) { return; }

    //Step 1: Generate all path nodes, assign all to their respective parent.
    PathNode *aNode = 0;
    mUnitGridWidth = (mTileGridWidthTotal * SUBDIVISIONS_PER_TILE) + 1;
    mUnitGridHeight = (mTileGridHeightTotal * SUBDIVISIONS_PER_TILE) + 1;

    mUnitGridBase = new PathNode***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mUnitGridBase[aDepth] = new PathNode**[mUnitGridWidth];
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            mUnitGridBase[aDepth][aGridX] = new PathNode*[mUnitGridHeight];
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                aNode = new PathNode();
                aNode->mGridX = aGridX;
                aNode->mGridY = aGridY;
                aNode->mGridZ = aDepth;
                mUnitGridBase[aDepth][aGridX][aGridY] = aNode;
            }
        }
    }

    mUnitGrid = new PathNode***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mUnitGrid[aDepth] = new PathNode**[mUnitGridWidth];
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            mUnitGrid[aDepth][aGridX] = new PathNode*[mUnitGridHeight];
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                mUnitGrid[aDepth][aGridX][aGridY] = 0;
            }
        }
    }

    RefreshUnitGridNodes();
    ComputePathConnections();
}

void GameArena::SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {
    if (mTowerAllowed) {
        for (int i=0;i<mTileGridWidthTotal;i++)delete [] mTowerAllowed[i];
        delete [] mTowerAllowed;
    }
    if (mTile) {
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mTileGridWidthTotal;i++) {
                for (int n=0;n<mTileGridHeightTotal;n++) {
                    DeleteTile(i, n, aDepth);
                }
            }
        }
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mTileGridWidthTotal;i++) { delete [] mTile[aDepth][i]; }
            delete [] mTile[aDepth];
        }
        delete [] mTile;
    }

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

void GameArena::Load(const char *pPath)
{
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";

    FXML aXML;
    aXML.Load(aPath);
    FreeList(AnimatedLevelPath, mPathList);
    FXMLTag *aArenaTag = aXML.GetRoot();
    if (aArenaTag) {
        mTileGridWidthActive = FString(aArenaTag->GetParamValue("grid_width_active")).ToInt();
        mTileGridHeightActive = FString(aArenaTag->GetParamValue("grid_height_active")).ToInt();
        mTileGridBufferH = FString(aArenaTag->GetParamValue("grid_buffer_h")).ToInt();
        mTileGridBufferV = FString(aArenaTag->GetParamValue("grid_buffer_v")).ToInt();
        mTileGridWidthTotal = mTileGridWidthActive + mTileGridBufferH * 2;
        mTileGridHeightTotal = mTileGridHeightActive + mTileGridBufferV * 2;
        if (mTileGridWidthTotal > 0 && mTileGridHeightTotal > 0) {
            SizeGrid(mTileGridWidthActive, mTileGridHeightActive, mTileGridBufferH, mTileGridBufferV);
            EnumTagsMatching (aArenaTag, aTileListTag, "tile_list") {
                EnumTags (aTileListTag, aTileTag) {
                    GameTile *aTile = new GameTile();
                    aTile->Load(aTileTag);
                    if (aTile->mGridX >= 0 && aTile->mGridY >= 0 && aTile->mGridZ >=0 && aTile->mGridX < mTileGridWidthTotal && aTile->mGridY < mTileGridHeightTotal && aTile->mGridZ < GRID_DEPTH) {
                        mTile[aTile->mGridZ][aTile->mGridX][aTile->mGridY] = aTile;
                    }
                }
            }
            
            EnumTagsMatching (aArenaTag, aPathListTag, "path_list") {
                EnumTags (aPathListTag, aPathTag) {
                    AnimatedLevelPath *aPath = new AnimatedLevelPath();
                    aPath->Load(aPathTag);
                    mPathList += aPath;
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
    
    GenerateUnitGrid();
    ComputeAllowedPlacements();
    ComputePathConnections();
}

