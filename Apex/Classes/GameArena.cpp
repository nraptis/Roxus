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

    mGrid = 0;
    mGridWidth = 0;
    mGridHeight = 0;

    Generate(10, 14, 4, 4);

    //Load("test_level_1.xml");

    //Load("ramps_test_01.xml");

    //Load("pathing_map_02_inverse.xml");
    //Load("45_degree_corners.xml");
    //Load("45_degree_corners_inverse.xml");

    //Load("crazy_ramps");

    //Load("complex_ramping");

    Load("many_wide_ramps");

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
    
    mTowerCollection.Update();

    EnumList (AnimatedGamePath, aPath, mPathList) {
        aPath->Update();
    }
}

void GameArena::Draw() {
    Graphics::SetColor();


    EnumList (AnimatedGamePath, aPath, mPathList) {
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

        EnumList (AnimatedGamePath, aPath, mPathList) {
            aPath->Draw(aDepth);
        }

        EnumList(Tower, aTower, mTowerCollection.mObjectList) {
            if (aTower->mKill == 0 && aTower->mGridZ == aDepth) {
                aTower->Draw();
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
        for (int aGridX=0;aGridX<mGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mGridHeight;aGridY++) {
                PathNode *aNode = mGrid[aDepth][aGridX][aGridY];

                if (aNode->mBlocked == false) {
                    Graphics::SetColor(0.95f, 0.95f, 0.95f, 1.0f);
                    Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 3.0f);

                    Graphics::SetColor(0.0f, 0.125f, 0.125f, 1.0f);
                    Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 2.25f);


                    if (aDepth == 0) {
                        Graphics::SetColor(1.0f, 0.75f, 0.25f);
                    }
                    if (aDepth == 1) {
                        Graphics::SetColor(0.125f, 0.75f, 0.75f);
                    }
                    if (aDepth == 2) {
                        Graphics::SetColor(0.855f, 0.125f, 0.85f);
                    }

                    Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 1.5f);


                }
            }
        }
    }

    Graphics::SetColor();
    gApp->mNinja.Center(mTestNinjaRotation, mTestNinjaFrame, 0.0f, 0.0f);
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

void GameArena::DeleteGridNode(int pGridX, int pGridY, int pGridZ) {
    PathNode *aNode = GetGridNode(pGridX, pGridY, pGridZ);
    if (aNode) {
        mDeletedNodeList += aNode;
        mGrid[pGridZ][pGridX][pGridY] = 0;
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
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight) && (pGridZ < GRID_DEPTH)) {
        aResult = mGrid[pGridZ][pGridX][pGridY];
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

void GameArena::Click(float pX, float pY) {
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
    
    //EnumList (Unit, aUnit, mUnitList) {
    //    aUnit->ComputePath();
    //}
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
    
    EnumList (AnimatedGamePath, aPath, mPathList) {
        aPath->ComputePath(this);
    }

    ComputeGridConnections();
}

void GameArena::ComputeGridConnections() {


}

//This will assign nodes to tiles, compute node positions, and figure out which
//nodes are "blocked" by default...
void GameArena::RefreshUnitGridNodes() {

    PathNode *aNode = 0;
    //Step 1: UNBLOCK all of the grid nodes...
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mGridHeight;aGridY++) {
                aNode = mGrid[aDepth][aGridX][aGridY];
                aNode->Reset();
                aNode->mBlocked = true;
            }
        }
    }



    //Step 2: Assign nodes to their parent tiles
    //        Block off nodes which are on a null tile.
    //        Block off nodes which directly border a null tile
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
                            aNode = mGrid[aDepth][aGridX][aGridY];
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
                            aNode = mGrid[aDepth][aGridX][aGridY];

                        }
                    }
                }
            }
        }
    }


    //Step 3: Give all path nodes a default location...
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
                        aNode = mGrid[aDepth][aGridX][aGridY];
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
                            aNode = mGrid[aDepth][aGridX][aGridY];
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
        //for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
        for (int aTileGridX=(mTileGridWidthTotal-1);aTileGridX>=0;aTileGridX--) {
            int aStartGridX = aTileGridX * SUBDIVISIONS_PER_TILE;
            //for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
            for (int aTileGridY=(mTileGridHeightTotal-1);aTileGridY>=0;aTileGridY--) {

                GameTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    GameTile *aTileU = GetTile(aTileGridX    , aTileGridY - 1, aDepth);
                    GameTile *aTileR = GetTile(aTileGridX + 1, aTileGridY    , aDepth);
                    GameTile *aTileD = GetTile(aTileGridX    , aTileGridY + 1, aDepth);
                    GameTile *aTileL = GetTile(aTileGridX - 1, aTileGridY    , aDepth);

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
                        GameTile *aTileUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth);
                        GameTile *aTileUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth);
                        GameTile *aTileDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth);
                        GameTile *aTileDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth);

                        GameTile *aTileAboveUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth + 1);
                        GameTile *aTileAboveUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth + 1);
                        GameTile *aTileAboveDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth + 1);
                        GameTile *aTileAboveDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth + 1);

                        //GameTile *aTileBelowUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth - 1);
                        //GameTile *aTileBelowUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth - 1);
                        //GameTile *aTileBelowDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth - 1);
                        //GameTile *aTileBelowDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth - 1);

                        aBlockUL = true;
                        if (aTileL && aTileU && aTileUL) {
                            if (aTileUL->mTileType == TILE_TYPE_NORMAL &&
                                aTileU->mTileType == TILE_TYPE_NORMAL &&
                                aTileL->mTileType == TILE_TYPE_NORMAL &&
                                aTileUL->mBlocked == false &&
                                aTileU->mBlocked == false &&
                                aTileL->mBlocked == false) {
                                aBlockUL = false;
                            }
                        }
                        if (aTileL && aTileUL) {
                            if (aTileL->mTileType == TILE_TYPE_RAMP_R && aTileUL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockUL = false;
                            }
                            if (aTileL->mTileType == TILE_TYPE_RAMP_L && aTileUL->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockUL = false;
                            }
                        }
                        if (aTileU && aTileUL) {
                            if (aTileU->mTileType == TILE_TYPE_RAMP_U && aTileUL->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockUL = false;
                            }
                            if (aTileU->mTileType == TILE_TYPE_RAMP_D && aTileUL->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockUL = false;
                            }
                        }
                        if (aTileAboveL && aTileAboveUL) {
                            if (aTileAboveL->mTileType == TILE_TYPE_RAMP_L && aTileAboveUL->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockUL = false;
                            }
                        }



                        aBlockUR = true;
                        if (aTileR && aTileU && aTileUR) {
                            if (aTileUR->mTileType == TILE_TYPE_NORMAL &&
                                aTileU->mTileType == TILE_TYPE_NORMAL &&
                                aTileR->mTileType == TILE_TYPE_NORMAL &&
                                aTileUR->mBlocked == false &&
                                aTileU->mBlocked == false &&
                                aTileR->mBlocked == false) {
                                aBlockUR = false;
                            }
                        }
                        if (aTileR && aTileUR) {
                            if (aTileR->mTileType == TILE_TYPE_RAMP_L && aTileUR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockUR = false;
                            }
                            if (aTileR->mTileType == TILE_TYPE_RAMP_R && aTileUR->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockUR = false;
                            }
                        }
                        if (aTileU && aTileUR) {
                            if (aTileU->mTileType == TILE_TYPE_RAMP_U && aTileUR->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockUR = false;
                            }
                            if (aTileU->mTileType == TILE_TYPE_RAMP_D && aTileUR->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockUR = false;
                            }
                        }
                        if (aTileAboveR && aTileAboveUR) {
                            if (aTileAboveR->mTileType == TILE_TYPE_RAMP_R && aTileAboveUR->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockUR = false;
                            }
                        }


                        aBlockDL = true;
                        if (aTileL && aTileD && aTileDL) {
                            if (aTileDL->mTileType == TILE_TYPE_NORMAL &&
                                aTileD->mTileType == TILE_TYPE_NORMAL &&
                                aTileL->mTileType == TILE_TYPE_NORMAL &&
                                aTileDL->mBlocked == false &&
                                aTileD->mBlocked == false &&
                                aTileL->mBlocked == false) {
                                aBlockDL = false;
                            }
                        }
                        if (aTileL && aTileDL) {
                            if (aTileL->mTileType == TILE_TYPE_RAMP_R && aTileDL->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockDL = false;
                            }
                            if (aTileL->mTileType == TILE_TYPE_RAMP_L && aTileDL->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockDL = false;
                            }
                        }
                        if (aTileD && aTileDL) {
                            if (aTileD->mTileType == TILE_TYPE_RAMP_U && aTileDL->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockDL = false;
                            }
                            if (aTileD->mTileType == TILE_TYPE_RAMP_D && aTileDL->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockDL = false;
                            }
                        }
                        if (aTileAboveL && aTileAboveDL) {
                            if (aTileAboveL->mTileType == TILE_TYPE_RAMP_L && aTileAboveDL->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockDL = false;
                            }
                        }


                        aBlockDR = true;
                        if (aTileR && aTileD && aTileDR) {
                            if (aTileDR->mTileType == TILE_TYPE_NORMAL &&
                                aTileD->mTileType == TILE_TYPE_NORMAL &&
                                aTileR->mTileType == TILE_TYPE_NORMAL &&
                                aTileDR->mBlocked == false &&
                                aTileD->mBlocked == false &&
                                aTileR->mBlocked == false) {
                                aBlockDR = false;
                            }
                        }

                        if (aTileR && aTileDR) {
                            if (aTileR->mTileType == TILE_TYPE_RAMP_L && aTileDR->mTileType == TILE_TYPE_RAMP_L) {
                                aBlockDR = false;
                            }
                            if (aTileR->mTileType == TILE_TYPE_RAMP_R && aTileDR->mTileType == TILE_TYPE_RAMP_R) {
                                aBlockDR = false;
                            }
                        }
                        if (aTileD && aTileDR) {
                            if (aTileD->mTileType == TILE_TYPE_RAMP_U && aTileDR->mTileType == TILE_TYPE_RAMP_U) {
                                aBlockDR = false;
                            }
                            if (aTileD->mTileType == TILE_TYPE_RAMP_D && aTileDR->mTileType == TILE_TYPE_RAMP_D) {
                                aBlockDR = false;
                            }
                        }
                        if (aTileAboveR && aTileAboveDR) {
                            if (aTileAboveR->mTileType == TILE_TYPE_RAMP_R && aTileAboveDR->mTileType == TILE_TYPE_RAMP_R) {
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
                    }

                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        int aGridX = aStartGridX + aOffsetX;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mGrid[aDepth][aGridX][aGridY];
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
    GenerateUnitGrid();
    ComputePathConnections();
}

void GameArena::GenerateUnitGrid() {
    if (mGrid) {
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int aGridX=0;aGridX<mGridWidth;aGridX++) {
                for (int aGridY=0;aGridY<mGridHeight;aGridY++) {
                    DeleteGridNode(aGridX, aGridY, aDepth);
                }
            }
        }
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mGridWidth;i++) { delete [] mGrid[aDepth][i]; }
            delete [] mGrid[aDepth];
        }
        delete [] mGrid;
        mGrid = 0;
    }

    mGridWidth = 0;
    mGridHeight = 0;

    if (mTileGridWidthTotal <= 0 || mTileGridHeightTotal <= 0) { return; }

    mGridWidth = (mTileGridWidthTotal * SUBDIVISIONS_PER_TILE) + 1;
    mGridHeight = (mTileGridHeightTotal * SUBDIVISIONS_PER_TILE) + 1;
    mGrid = new PathNode***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mGrid[aDepth] = new PathNode**[mGridWidth];
        for (int aGridX=0;aGridX<mGridWidth;aGridX++) {
            mGrid[aDepth][aGridX] = new PathNode*[mGridHeight];
            for (int aGridY=0;aGridY<mGridHeight;aGridY++) {
                mGrid[aDepth][aGridX][aGridY] = new PathNode();
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

    ComputeAllowedPlacements();
    ComputePathConnections();
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
    EnumList (AnimatedGamePath, aPath, mPathList) {
        *aPathListTag += aPath->Save();
    }
    
    aXML.Print();
    aXML.Save(aPath.c());
}

void GameArena::Load(const char *pPath)
{
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    //aPath = (gDocuments + aPath);


    FXML aXML;
    aXML.Load(aPath);

    FreeList(AnimatedGamePath, mPathList);

    FXMLTag *aArenaTag = aXML.GetRoot();
    if (aArenaTag) {
        mTileGridWidthActive = FString(aArenaTag->GetParamValue("grid_width_active")).ToInt();
        mTileGridHeightActive = FString(aArenaTag->GetParamValue("grid_height_active")).ToInt();
        mTileGridBufferH = FString(aArenaTag->GetParamValue("grid_buffer_h")).ToInt();
        mTileGridBufferV = FString(aArenaTag->GetParamValue("grid_buffer_v")).ToInt();
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
                    AnimatedGamePath *aPath = new AnimatedGamePath();
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

    printf("Grid Size [%d x %d] Active [%d x %d]\n", mTileGridWidthTotal, mTileGridHeightTotal, mTileGridWidthActive, mTileGridHeightTotal);

    GenerateUnitGrid();
    RefreshUnitGridNodes();
    
    ComputeAllowedPlacements();
    ComputePathConnections();
}

