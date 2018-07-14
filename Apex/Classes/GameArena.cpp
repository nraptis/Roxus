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
    
    gTileWidth = 72.0f;
    gTileHeight = 72.0f;
    
    gTileWidth2 = gTileWidth * 0.5f;
    gTileHeight2 = gTileHeight * 0.5f;
    
    
    mCursorGridX = -1;
    mCursorGridY = -1;
    mCursorGridZ = -1;
    
    mGridWidthTotal = 0;
    mGridHeightTotal = 0;
    
    mGridWidthActive = 0;
    mGridHeightActive = 0;
    
    mGridBufferH = 0;
    mGridBufferV = 0;
    
    mTile = 0;
    mTowerAllowed = 0;
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mTileVisible[aDepth] = true;
        mTileOpacity[aDepth] = 1.0f;
    }
    
    Generate(10, 14, 4, 4);
    
    Load("test_level_1.xml");
}

GameArena::~GameArena() {
    gArena = 0;
    
}

void GameArena::Update() {
    
    /*
     for(int i=0;i<mGridWidth;i++)
     {
     for(int n=0;n<mGridHeight;n++)
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
     int aTargetX = aUnit->mGridX + aDirX;
     int aTargetY = aUnit->mGridY + aDirY;
     
     if(aTargetX >= 0 && aTargetY >= 0 && aTargetX < mGridWidth && aTargetY < mGridHeight)
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
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        
        
        //if(aDepth == 2)mApp->mLevelBackTunnel.Center(gArenaWidth2, gArenaHeight2);
        //if(aDepth == 1)mApp->mLevelBackFloor.Center(gArenaWidth2, gArenaHeight2);
        //if(aDepth == 0)mApp->mLevelBackBridge.Center(gArenaWidth2, gArenaHeight2);
        
        if (mTileVisible[aDepth]) {

            Graphics::SetColor();
            if (gApp->mDarkMode) {
                Graphics::SetColor(0.125f, 0.125f, 0.125f, mTileOpacity[aDepth]);
            } else {
                Graphics::SetColor(mTileOpacity[aDepth]);
            }
            
            for (int aX=0;aX<mGridWidthTotal;aX++) {
                for (int aY=0;aY<mGridHeightTotal;aY++) {
                    GameTile *aTile = mTile[aDepth][aX][aY];
                    if (aTile) {
                        aTile->Draw();
                    }
                }
            }
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
    
    EnumList (AnimatedGamePath, aPath, mPathList) {
        aPath->Draw();
    }
    
    
    /*
     for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
     
     Graphics::SetColorSwatch(aDepth, 0.15f);
     for (int aGridX=0;aGridX<mGridWidthTotal;aGridX++) {
     for (int aGridY=0;aGridY<mGridHeightTotal;aGridY++) {
     
     GameTile *aTile1 = mTile[aDepth][aGridX][aGridY];
     
     if (aTile1) {
     for (int i=0;i<aTile1->mPathConnectionCount;i++) {
     GameTile *aTile2 = aTile1->mPathConnection[i].mTile;
     //aTile2->mCenterX
     
     
     Graphics::DrawArrow(aTile1->mCenterX, aTile1->mCenterY, aTile2->mCenterX, aTile2->mCenterY);
     
     
     }
     
     }
     
     }
     }
     }
     */
    
    Graphics::SetColor(0.85f, 0.25f, 0.25f, 1.0f);
    Graphics::OutlineRect(mPivotX - 6.0f, mPivotY - 6.0f, 12.0f, 12.0f, 4.0f);
    Graphics::SetColor();
}

void GameArena::Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {
    SizeGrid(pWidth, pHeight, pGridBufferH, pGridBufferV);
    int aDepth = 1;
    for (int aX=0;aX<mGridWidthActive;aX++) {
        for (int aY=0;aY<mGridHeightActive;aY++) {
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV]=new GameTile();
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV]->SetUp(aX + mGridBufferH, aY + mGridBufferV, aDepth);
        }
    }
    for (int aX = 0;aX < mGridWidthActive;aX++) {
        for (int aY=0;aY<mGridHeightActive;aY++) {
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV] = new GameTile();
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV]->SetUp(aX + mGridBufferH, aY + mGridBufferV, aDepth);
        }
    }
    aDepth = 0;
    for (int aX = 0;aX < mGridWidthTotal;aX++) {
        for (int aY = 0;aY < mGridHeightTotal;aY++) {
            if (aX < mGridBufferH || aY < mGridBufferV || aX >= (mGridBufferH + mGridWidthActive) || aY >= (mGridBufferV + mGridHeightActive)) {
                mTile[aDepth][aX][aY] = new GameTile();
                mTile[aDepth][aX][aY]->SetUp(aX, aY, aDepth);
            }
        }
    }
}

void GameArena::DrawGridOverlay() {
    int aDrawIndex = 0;
    for (int aX = 0;aX < mGridWidthTotal;aX++) {
        for (int aY = 0;aY < mGridHeightTotal;aY++) {
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
        float aLeft = mCursorGridX * gTileWidth;
        float aTop = mCursorGridY * gTileHeight;
        Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.25f);
        Graphics::DrawRect(0.0f, aTop, gArenaWidth, gTileHeight);
        Graphics::DrawRect(aLeft, 0.0f, gTileWidth, gArenaHeight);
    }
}

void GameArena::SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {
    if (mTowerAllowed) {
        for (int i=0;i<mGridWidthTotal;i++)delete [] mTowerAllowed[i];
        delete [] mTowerAllowed;
    }
    if (mTile) {
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mGridWidthTotal;i++) { delete [] mTile[aDepth][i]; }
            delete [] mTile[aDepth];
        }
        delete [] mTile;
    }
    mGridBufferH = pGridBufferH;
    mGridBufferV = pGridBufferV;
    mGridWidthActive = pWidth;
    mGridHeightActive = pHeight;
    mGridWidthTotal = mGridWidthActive + mGridBufferH * 2;
    mGridHeightTotal = mGridHeightActive + mGridBufferV * 2;
    mTile = new GameTile***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mTile[aDepth] = new GameTile**[mGridWidthTotal];
        for (int aX=0;aX<mGridWidthTotal;aX++) {
            mTile[aDepth][aX] = new GameTile*[mGridHeightTotal];
            for (int aY=0;aY<mGridHeightTotal;aY++) {
                mTile[aDepth][aX][aY] = 0;
            }
        }
    }
    
    mTowerAllowed = new bool*[mGridWidthTotal];
    for (int aX=0;aX<mGridWidthTotal;aX++) {
        mTowerAllowed[aX] = new bool[mGridHeightTotal];
        for (int aY=0;aY<mGridHeightTotal;aY++) {
            mTowerAllowed[aX][aY] = true;
        }
    }
    
    gArenaWidth = mGridWidthTotal * gTileWidth;
    gArenaWidth2 = gArenaWidth * 0.5f;
    gArenaHeight = mGridHeightTotal * gTileHeight;
    gArenaHeight2 = gArenaHeight * 0.5f;

    gArenaActiveWidth = mGridWidthActive * gTileWidth;
    gArenaActiveWidth2 = gArenaActiveWidth * 0.5f;
    gArenaActiveHeight = mGridHeightActive * gTileHeight;
    gArenaActiveHeight2 = gArenaActiveHeight * 0.5f;
    gArenaActiveX = pGridBufferH * gTileWidth;
    gArenaActiveY = pGridBufferV * gTileHeight;
    
    ComputeAllowedPlacements();
}

void GameArena::ComputeAllowedPlacements() {
    int aMaxX = mGridBufferH + mGridWidthActive;
    int aMaxY = mGridBufferV + mGridHeightActive;
    GameTile *aTile = 0;
    for (int aX=0;aX<mGridWidthTotal;aX++) {
        for (int aY=0;aY<mGridHeightTotal;aY++) {
            mTowerAllowed[aX][aY] = false;
            if (aX >= mGridBufferH && aY >= mGridBufferV && aX < aMaxX && aY < aMaxY) {
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
    if (pGridX >= 0 && pGridX < mGridWidthTotal && pGridY >= 0 && pGridY < mGridHeightTotal && pGridZ >= 0 && pGridZ < GRID_DEPTH) {
        aResult = true;
    }
    return aResult;
}


bool GameArena::CanPlaceTower() {
    return CanPlaceTower(mCursorGridX, mCursorGridY, 1);
}

GameTile *GameArena::GetTile(int pGridX, int pGridY, int pGridZ) {
    GameTile *aResult = 0;
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mGridWidthTotal) && (pGridY < mGridHeightTotal) && (pGridZ < GRID_DEPTH)) {
        aResult = mTile[pGridZ][pGridX][pGridY];
    }
    
    return aResult;
}

void GameArena::GetGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ) {
    pGridX = -1;
    pGridY = -1;
    pGridZ = -1;
    int aGridX = -1;
    if (pX > 0) {
        aGridX = (int)(pX / gTileWidth);
        if (aGridX >= mGridWidthTotal) {
            aGridX = -1;
        }
    }
    if (aGridX != -1) {
        int aGridY = -1;
        GameTile *aTile = 0;
        int aLandGridY = (int)(pY / gTileHeight);
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
                        aTop = aCenterY - (gTileHeight2 + aEpsilon);
                        aBottom = aCenterY + (gTileHeight2 + aEpsilon);
                        if (pY >= aTop && pY <= aBottom) {
                            printf("Y = %f [T=%f  B=%f]\n", pY, aTop, aBottom);
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

    mPivotX = pX;
    mPivotY = pY;
    
    
    GetGridPos(pX, pY, aGridX, aGridY, aGridZ);
    printf("Grid[%d %d %d]\n", aGridX, aGridY, aGridZ);
    
    if (aGridX != -1 && aGridY != -1 && aGridZ != -1) {
        if (CanPlaceTower(aGridX, aGridY, aGridZ)) {
            
            Tower *aTower = GetTower(aGridX, aGridY, aGridZ);
            
            if(aTower == 0)
            {
                aTower = new Tower();
                aTower->SetUp(aGridX, aGridY, aGridZ);
                
                mTowerCollection.Add(aTower);
            }
            else
            {
                aTower->Kill();
            }
        }
    }
    
    //int aDepth = 1;
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mGridWidthTotal;aX++) {
            for (int aY=0;aY<mGridHeightTotal;aY++) {
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
     if(aTower->mGridX == pGridX && aTower->mGridY == pGridY)
     {
     aResult = aTower;
     }
     }
     */

    return aResult;
}

void GameArena::ComputePathConnections() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mGridWidthTotal;aX++) {
            for (int aY=0;aY<mGridHeightTotal;aY++) {
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
        for (int aX=0;aX<mGridWidthTotal;aX++) {
            for (int aY=0;aY<mGridHeightTotal;aY++) {
                GameTile *aTile = GetTile(aX, aY, aDepth);
                if (aTile) {
                    if (aTile->IsBlocked() == false) {
                        GameTile *aTileU = GetTile(aX, aY - 1, aDepth);
                        GameTile *aTileD = GetTile(aX, aY + 1, aDepth);
                        GameTile *aTileL = GetTile(aX - 1, aY, aDepth);
                        GameTile *aTileR = GetTile(aX + 1, aY, aDepth);
                        if (aTile->IsNormal()) {
                            if (aTileU) {
                                if(aTileU->IsNormal() || aTileU->mType == TILE_TYPE_RAMP_U) {
                                    aTile->ConnectTo(aTileU, PATH_COST_ADJ);
                                }
                            }
                            if (aTileD) {
                                if (aTileD->IsNormal() || aTileD->mType == TILE_TYPE_RAMP_D) {
                                    aTile->ConnectTo(aTileD, PATH_COST_ADJ);
                                }
                            }
                            if (aTileL) {
                                if(aTileL->IsNormal() || aTileL->mType == TILE_TYPE_RAMP_L) {
                                    aTile->ConnectTo(aTileL, PATH_COST_ADJ);
                                }
                            }
                            if (aTileR) {
                                if(aTileR->IsNormal() || aTileR->mType == TILE_TYPE_RAMP_R) {
                                    aTile->ConnectTo(aTileR, PATH_COST_ADJ);
                                }
                            }
                            GameTile *aTileUR = GetTile(aX + 1, aY - 1, aDepth);
                            GameTile *aTileUL = GetTile(aX - 1, aY - 1, aDepth);
                            GameTile *aTileDR = GetTile(aX + 1, aY + 1, aDepth);
                            GameTile *aTileDL = GetTile(aX - 1, aY + 1, aDepth);
                            if (aTileU != 0 && aTileL != 0 && aTileUL != 0) {
                                if (aTileU->IsNormal() && aTileL->IsNormal() && aTileUL->IsNormal()) {
                                    aTile->ConnectTo(aTileUL, PATH_COST_DIA);
                                }
                            }
                            if (aTileU != 0 && aTileR != 0 && aTileUR != 0) {
                                if (aTileU->IsNormal() && aTileR->IsNormal() && aTileUR->IsNormal()) {
                                    aTile->ConnectTo(aTileUR, PATH_COST_DIA);
                                }
                            }
                            if (aTileD != 0 && aTileL != 0 && aTileDL != 0) {
                                if (aTileD->IsNormal() && aTileL->IsNormal() && aTileDL->IsNormal()) {
                                    aTile->ConnectTo(aTileDL, PATH_COST_DIA);
                                }
                            }
                            if (aTileD != 0 && aTileR != 0 && aTileDR != 0) {
                                if (aTileD->IsNormal() && aTileR->IsNormal() && aTileDR->IsNormal()) {
                                    aTile->ConnectTo(aTileDR, PATH_COST_DIA);
                                }
                            }
                        }
                        GameTile *aLowerTileU = GetTile(aX, aY - 1, aDepth - 1);
                        GameTile *aLowerTileD = GetTile(aX, aY + 1, aDepth - 1);
                        GameTile *aLowerTileL = GetTile(aX - 1, aY, aDepth - 1);
                        GameTile *aLowerTileR = GetTile(aX + 1, aY, aDepth - 1);
                        if (aTile->mType == TILE_TYPE_RAMP_U) {
                            if (aLowerTileU) {
                                if (aLowerTileU->IsBlocked() == false) {
                                    aTile->ConnectTo(aLowerTileU, PATH_COST_RAMP);
                                    aLowerTileU->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            if (aTileD) {
                                if (aTileD->IsBlocked() == false) {
                                    aTile->ConnectTo(aTileD, PATH_COST_ADJ);
                                }
                            }
                        }
                        if (aTile->mType == TILE_TYPE_RAMP_D) {
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
                        if (aTile->mType == TILE_TYPE_RAMP_R) {
                            if (aLowerTileR) {
                                if (aLowerTileR->IsBlocked() == false) {
                                    aTile->ConnectTo(aLowerTileR, PATH_COST_RAMP);
                                    aLowerTileR->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            if (aTileL) {
                                if (aTileL->IsBlocked() == false) {
                                    aTile->ConnectTo(aTileL, PATH_COST_ADJ);
                                }
                            }
                        }
                        if (aTile->mType == TILE_TYPE_RAMP_L) {
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
}

void GameArena::Save(const char *pPath) {
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    aPath = (gDirDocuments + aPath);
    
    FXML aXML;
    
    FXMLTag *aArenaTag = new FXMLTag("game_arena");
    aXML.mRoot = aArenaTag;
    
    aArenaTag->AddParam("grid_width_active", FString(mGridWidthActive).c());
    aArenaTag->AddParam("grid_height_active", FString(mGridHeightActive).c());
    
    aArenaTag->AddParam("grid_buffer_h", FString(mGridBufferH).c());
    aArenaTag->AddParam("grid_buffer_v", FString(mGridBufferV).c());
    
    FXMLTag *aTileListTag = new FXMLTag("tile_list");
    *aArenaTag += aTileListTag;
    
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mGridWidthTotal;aX++) {
            for (int aY=0;aY<mGridHeightTotal;aY++) {
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
        mGridWidthActive = FString(aArenaTag->GetParamValue("grid_width_active")).ToInt();
        mGridHeightActive = FString(aArenaTag->GetParamValue("grid_height_active")).ToInt();
        mGridBufferH = FString(aArenaTag->GetParamValue("grid_buffer_h")).ToInt();
        mGridBufferV = FString(aArenaTag->GetParamValue("grid_buffer_v")).ToInt();
        if (mGridWidthTotal > 0 && mGridHeightTotal > 0) {
            SizeGrid(mGridWidthActive, mGridHeightActive, mGridBufferH, mGridBufferV);
            EnumTagsMatching (aArenaTag, aTileListTag, "tile_list") {
                EnumTags (aTileListTag, aTileTag) {
                    GameTile *aTile = new GameTile();
                    aTile->Load(aTileTag);
                    if (aTile->mGridX >= 0 && aTile->mGridY >= 0 && aTile->mGridZ >=0 && aTile->mGridX < mGridWidthTotal && aTile->mGridY < mGridHeightTotal && aTile->mGridZ < GRID_DEPTH) {
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
    
    printf("Grid Size [%d x %d] Active [%d x %d]\n", mGridWidthTotal, mGridHeightTotal, mGridWidthActive, mGridHeightTotal);
    
    ComputeAllowedPlacements();
    ComputePathConnections();
    
}

