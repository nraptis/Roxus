//
//  GameArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "GameArena.h"
#include "Game.h"

GameArena *gArena;

GameArena::GameArena()
{
    gArena = this;
    mApp = GAPP;
    
    mCursorGridX = -1;
    mCursorGridY = -1;
    
    mGridWidthTotal = 0;
    mGridHeightTotal = 0;
    
    mGridWidthActive = 0;
    mGridHeightActive = 0;
    
    mGridBufferH = 0;
    mGridBufferV = 0;
    
    mTile = 0;
    mTowerAllowed = 0;
    
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        mTileVisible[aDepth] = true;
        mTileOpacity[aDepth] = 1.0f;
    }
    
    Generate(10, 14, 4, 4);
    
    /*
    
    for(int i=0;i<5;i++)
    {
        Unit *aUnit = new Unit();
        aUnit->SetUp(gRand.Get(mGridWidth), gRand.Get(mGridHeight));
        mUnitList += aUnit;
    }
    
    */
    
    //Load("test_level_pathing_1.xml");
    
    Load("test_level_1.xml");
    
    mTempUnitSpawnTimer1 = 0;
    mTempUnitSpawnTime1 = gRand.Get(40) + 60;
    
    mTempUnitSpawnTimer2 = 0;
    mTempUnitSpawnTime2 = gRand.Get(40) + 60;
    
}

GameArena::~GameArena()
{
    
}

void GameArena::Update()
{
    
    
    if(mPathList.mCount > 0)
    {
        mTempUnitSpawnTimer1++;
        if(mTempUnitSpawnTimer1 >= mTempUnitSpawnTime1)
        {
            mTempUnitSpawnTimer1 = 0;
            mTempUnitSpawnTime1 = gRand.Get(100) + 50;
            
            Unit *aUnit = new Unit();
            aUnit->SetUp((GamePath*)mPathList.Fetch(0));
            mUnitList += aUnit;
        }
    }
    
    if(mPathList.mCount > 1)
    {
        mTempUnitSpawnTimer2++;
        if(mTempUnitSpawnTimer2 >= mTempUnitSpawnTime2)
        {
            mTempUnitSpawnTimer2 = 0;
            mTempUnitSpawnTime2 = gRand.Get(100) + 50;
            
            Unit *aUnit = new Unit();
            aUnit->SetUp((GamePath*)mPathList.Fetch(1));
            mUnitList += aUnit;
        }
    }
    
    
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
    
    mUnitListKillThisUpdate.mCount = 0;
    
    EnumList(Unit, aUnit, mUnitList)
    {
        aUnit->Update();
        
        if(aUnit->mKill)
        {
            mUnitListKillThisUpdate += aUnit;
        }
    }
    
    EnumList(Unit, aUnit, mUnitListKillThisUpdate)
    {
        mUnitList -= aUnit;
        mUnitListKill += aUnit;
    }
    
    mUnitListDelete.mCount = 0;
    EnumList(Unit, aUnit, mUnitListKill)
    {
        aUnit->mKill--;
        if(aUnit->mKill <= 0)
        {
            mUnitListDelete += aUnit;
        }
    }
    
    EnumList(Unit, aUnit, mUnitListDelete)
    {
        mUnitListKill -= aUnit;
        delete aUnit;
    }
    
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
    
    mTowers.Update();
    
    EnumList(GamePath, aPath, mPathList)
    {
        aPath->Update();
    }
    
}

void GameArena::Draw()
{
    Graphics::SetColor();
    
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        
        //if(aDepth == 2)mApp->mLevelBackTunnel.Center(gArenaWidth2, gArenaHeight2);
        //if(aDepth == 1)mApp->mLevelBackFloor.Center(gArenaWidth2, gArenaHeight2);
        //if(aDepth == 0)mApp->mLevelBackBridge.Center(gArenaWidth2, gArenaHeight2);
        
        
        if(mTileVisible[aDepth])
        {
            Graphics::SetColor(mTileOpacity[aDepth]);
            for(int aX=0;aX<mGridWidthTotal;aX++)
            {
                for(int aY=0;aY<mGridHeightTotal;aY++)
                {
                    GameTile *aTile = mTile[aDepth][aX][aY];
                    if(aTile)
                    {
                        aTile->Draw();
                    }
                }
            }
        }
        
        
        EnumList(Unit, aUnit, mUnitList)
        {
            if(aUnit->mDrawZ == aDepth)
            {
                aUnit->Draw();
            }
        }
        
        if(aDepth == 1)
        {
            //EnumList(Tower, aTower, mTowerList)
            //{
            //    aTower->Draw();
            //}
            
            mTowers.Draw();
            
            if(gGame->mTowerPickerMenu.mCurrentTower)
            {
                if(mCursorGridX != -1 && mCursorGridY != -1)
                {
                    gGame->mTowerPickerMenu.mCurrentTower->SetUp(mCursorGridX, mCursorGridY);
                    gGame->mTowerPickerMenu.mCurrentTower->Draw();
                }
            }
        }
    }
    
    Graphics::SetColor();
    
    EnumList(GamePath, aPath, mPathList)
    {
        aPath->Draw();
    }
}

void GameArena::Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV)
{
    SizeGrid(pWidth, pHeight, pGridBufferH, pGridBufferV);
    
    int aDepth = 1;
    for(int aX=0;aX<mGridWidthActive;aX++)
    {
        for(int aY=0;aY<mGridHeightActive;aY++)
        {
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV]=new GameTile();
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV]->SetUp(aX + mGridBufferH, aY + mGridBufferV, aDepth);
        }
    }
    
    for(int aX=0;aX<mGridWidthActive;aX++)
    {
        for(int aY=0;aY<mGridHeightActive;aY++)
        {
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV]=new GameTile();
            mTile[aDepth][aX + mGridBufferH][aY + mGridBufferV]->SetUp(aX + mGridBufferH, aY + mGridBufferV, aDepth);
        }
    }
    
    aDepth = 0;
    
    for(int aX=0;aX<mGridWidthTotal;aX++)
    {
        for(int aY=0;aY<mGridHeightTotal;aY++)
        {
            if(aX < mGridBufferH || aY < mGridBufferV || aX >= (mGridBufferH + mGridWidthActive) || aY >= (mGridBufferV + mGridHeightActive))
            {
                mTile[aDepth][aX][aY]=new GameTile();
                mTile[aDepth][aX][aY]->SetUp(aX, aY, aDepth);
            }
        }
    }
}

void GameArena::DrawGridOverlay()
{
    int aDrawIndex = 0;
    for(int aX=0;aX<mGridWidthTotal;aX++)
    {
        for(int aY=0;aY<mGridHeightTotal;aY++)
        {
            if(mTowerAllowed[aX][aY])
            {
                float aCenterX = CX(aX);
                float aCenterY = CY(aY);
                
                if(aX & 1)aDrawIndex = 0;
                else aDrawIndex = 1;
                
                if(aY & 1)aDrawIndex = !aDrawIndex;
                
                mApp->mGridOverlay[aDrawIndex].Center(aCenterX, aCenterY);
            }
        }
    }
}

void GameArena::DrawGridSelection()
{
    
    if((mCursorGridX != -1) && (mCursorGridY != -1))
    {
        float aLeft = mCursorGridX * gTileWidth;
        float aTop = mCursorGridY * gTileHeight;

        Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.25f);
        
        Graphics::DrawRect(0.0f, aTop, gArenaWidth, gTileHeight);
        Graphics::DrawRect(aLeft, 0.0f, gTileWidth, gArenaHeight);
    }
    
}

void GameArena::SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV)
{
    if(mTowerAllowed)
    {
        for(int i=0;i<mGridWidthTotal;i++)delete [] mTowerAllowed[i];
        delete [] mTowerAllowed;
        
    }
    
    if(mTile)
    {
        for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
        {
            for(int i=0;i<mGridWidthTotal;i++)delete [] mTile[aDepth][i];
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
    
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        mTile[aDepth] = new GameTile**[mGridWidthTotal];
        for(int aX=0;aX<mGridWidthTotal;aX++)
        {
            mTile[aDepth][aX] = new GameTile*[mGridHeightTotal];
            for(int aY=0;aY<mGridHeightTotal;aY++)
            {
                mTile[aDepth][aX][aY] = 0;
            }
        }
    }
    
    mTowerAllowed = new bool*[mGridWidthTotal];
    for(int aX=0;aX<mGridWidthTotal;aX++)
    {
        mTowerAllowed[aX] = new bool[mGridHeightTotal];
        for(int aY=0;aY<mGridHeightTotal;aY++)
        {
            mTowerAllowed[aX][aY] = true;
        }
    }
    
    gArenaWidth = mGridWidthTotal * gTileWidth;
    gArenaWidth2 = gArenaWidth / 2.0f;
    
    gArenaHeight = mGridHeightTotal * gTileHeight;
    gArenaHeight2 = gArenaHeight / 2.0f;
    
    ComputeAllowedPlacements();
}

void GameArena::ComputeAllowedPlacements()
{
    int aMaxX = mGridBufferH + mGridWidthActive;
    int aMaxY = mGridBufferV + mGridHeightActive;
    
    GameTile *aTile = 0;
    
    for(int aX=0;aX<mGridWidthTotal;aX++)
    {
        for(int aY=0;aY<mGridHeightTotal;aY++)
        {
            mTowerAllowed[aX][aY] = false;
            
            if(aX >= mGridBufferH && aY >= mGridBufferV && aX < aMaxX && aY < aMaxY)
            {
                aTile = mTile[MAIN_FLOOR][aX][aY];
                if(aTile)
                {
                    if(mTile[2][aX][aY] == 0)
                    {
                        if(aTile->PlacementAllowed())
                        {
                            mTowerAllowed[aX][aY] = true;
                        }
                    }
                }
            }
        }
    }
}

void GameArena::RemoveTower(Tower *pTower)
{
    if(pTower)
    {
        pTower->Kill();
        
        //mTowerList -= pTower;
        
        ComputePathConnections();
        EnumList(Unit, aUnit, mUnitList)
        {
            aUnit->ComputePath();
        }
    }
}

void GameArena::RemoveTower(int pGridX, int pGridY)
{
    RemoveTower(GetTower(pGridX, pGridY));
}

void GameArena::PlaceTower(Tower *pTower)
{
    if(pTower)
    {
        mTowers.AddObject(pTower);
        
        ComputePathConnections();
        EnumList(Unit, aUnit, mUnitList)
        {
            aUnit->ComputePath();
        }
        
        mTowers.SortAscendingY();
        
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

bool GameArena::CanPlaceTower(int pGridX, int pGridY)
{
    bool aReturn = false;
    
    if(pGridX >= 0 && pGridX < mGridWidthTotal && pGridY >= 0 && pGridY < mGridHeightTotal)
    {
        aReturn = true;
    }
    
    return aReturn;
}

bool GameArena::CanPlaceTower()
{
    return CanPlaceTower(mCursorGridX, mCursorGridY);
}

GameTile *GameArena::GetTile(int pGridX, int pGridY, int pGridZ)
{
    GameTile *aReturn = 0;
    
    if((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mGridWidthTotal) && (pGridY < mGridHeightTotal) && (pGridZ < GRID_DEPTH))
    {
        aReturn = mTile[pGridZ][pGridX][pGridY];
    }
    
    return aReturn;
}

int GameArena::GetGridX(float pX)
{
    int aReturn = -1;
    
    if(pX > 0)
    {
        pX /= gTileWidth;
        if(pX < mGridWidthTotal)
        {
            aReturn = pX;
        }
    }
    
    return aReturn;
}

int GameArena::GetGridY(float pY)
{
    int aReturn = -1;
    
    //pY -= (gBoardY - mVerticalOffset);// - gTileHeight / 2);
    
    if(pY > 0)
    {
        pY /= gTileHeight;
        if(pY < mGridHeightTotal)
        {
            aReturn = pY;
        }
    }
    return aReturn;
}

void GameArena::Click(float pX, float pY)
{
    int aGridX = GetGridX(pX);
    int aGridY = GetGridY(pY);
    
    if((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGridWidthTotal) && (aGridY < mGridHeightTotal))
    {
        if(CanPlaceTower(aGridX, aGridY))
        {
            
            /*
            Tower *aTower = GetTower(aGridX, aGridY);
            
            if(aTower == 0)
            {
                aTower = new Tower();
                aTower->SetUp(aGridX, aGridY);
                
                mTowerList += aTower;
            }
            else
            {
                mTowerList -= aTower;
            }
            */
            
        }
    }
    
    int aDepth = 1;
    
    for(int aX=0;aX<mGridWidthTotal;aX++)
    {
        for(int aY=0;aY<mGridHeightTotal;aY++)
        {
            GameTile *aTile = mTile[aDepth][aX][aY];
            if(aTile)
            {
                aTile->mBlocked = false;
                if(GetTower(aX, aY))
                {
                    aTile->mBlocked = true;
                }
            }
        }
    }
    
    ComputePathConnections();
    
    EnumList(Unit, aUnit, mUnitList)
    {
        aUnit->ComputePath();
    }
}

void GameArena::RefreshGridCursor(float pX, float pY)
{
    mCursorGridX = GetGridX(pX);
    mCursorGridY = GetGridY(pY);
    
    //If one if out of bounds, they both are!
    if((mCursorGridX == -1) || (mCursorGridY == -1))
    {
        mCursorGridX = -1;
        mCursorGridY = -1;
    }
}

Tower *GameArena::GetTower(int pGridX, int pGridY)
{
    Tower *aReturn = 0;
    
    for(int i=0;i<mTowers.mCount;i++)
    {
        Tower *aTower = (Tower *)mTowers.mList[i];
        
        if(aTower->mKill == 0)
        {
            if(aTower->mGridX == pGridX && aTower->mGridY == pGridY)
            {
                aReturn = aTower;
            }
        }
        
    }
    
    /*
    EnumList(Tower, aTower, mTowerList)
    {
        if(aTower->mGridX == pGridX && aTower->mGridY == pGridY)
        {
            aReturn = aTower;
        }
    }
    */
    
    return aReturn;
}

void GameArena::ComputePathConnections()
{
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        for(int aX=0;aX<mGridWidthTotal;aX++)
        {
            for(int aY=0;aY<mGridHeightTotal;aY++)
            {
                GameTile *aTile = mTile[aDepth][aX][aY];
                if(aTile)
                {
                    aTile->PathReset();
                }
            }
        }
    }
    
    
    
    for(int i=0;i<mTowers.mCount;i++)
    {
        Tower *aTower = (Tower *)mTowers.mList[i];
        
        GameTile *aTowerTile = GetTile(aTower->mGridX, aTower->mGridY, MAIN_FLOOR);
        if(aTowerTile)
        {
            aTowerTile->mOccupied = true;
        }
        
    }
    
    /*
    EnumList(Tower, aTower, mTowerList)
    {
        GameTile *aTowerTile = GetTile(aTower->mGridX, aTower->mGridY, MAIN_FLOOR);
        if(aTowerTile)
        {
            aTowerTile->mOccupied = true;
        }
    }
    */
    
#define PATH_COST_ADJ 100
#define PATH_COST_DIA 141
#define PATH_COST_RAMP 100
    
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        for(int aX=0;aX<mGridWidthTotal;aX++)
        {
            for(int aY=0;aY<mGridHeightTotal;aY++)
            {
                GameTile *aTile = GetTile(aX, aY, aDepth);
                if(aTile)
                {
                    if(aTile->IsBlocked() == false)
                    {
                        GameTile *aTileU = GetTile(aX, aY - 1, aDepth);
                        GameTile *aTileD = GetTile(aX, aY + 1, aDepth);
                        GameTile *aTileL = GetTile(aX - 1, aY, aDepth);
                        GameTile *aTileR = GetTile(aX + 1, aY, aDepth);
                        
                        if(aTile->IsNormal())
                        {
                            if(aTileU)
                            {
                                if(aTileU->IsNormal() || aTileU->mType == TILE_TYPE_RAMP_U)aTile->ConnectTo(aTileU, PATH_COST_ADJ);
                            }
                            
                            if(aTileD)
                            {
                                if(aTileD->IsNormal() || aTileD->mType == TILE_TYPE_RAMP_D)aTile->ConnectTo(aTileD, PATH_COST_ADJ);
                            }
                            
                            if(aTileL)
                            {
                                if(aTileL->IsNormal() || aTileL->mType == TILE_TYPE_RAMP_L)aTile->ConnectTo(aTileL, PATH_COST_ADJ);
                            }
                            
                            if(aTileR)
                            {
                                if(aTileR->IsNormal() || aTileR->mType == TILE_TYPE_RAMP_R)aTile->ConnectTo(aTileR, PATH_COST_ADJ);
                            }
                            
                            GameTile *aTileUR = GetTile(aX + 1, aY - 1, aDepth);
                            GameTile *aTileUL = GetTile(aX - 1, aY - 1, aDepth);
                            GameTile *aTileDR = GetTile(aX + 1, aY + 1, aDepth);
                            GameTile *aTileDL = GetTile(aX - 1, aY + 1, aDepth);
                            
                            if(aTileU != 0 && aTileL != 0 && aTileUL != 0)
                            {
                                if(aTileU->IsNormal() && aTileL->IsNormal() && aTileUL->IsNormal())
                                {
                                    aTile->ConnectTo(aTileUL, PATH_COST_DIA);
                                }
                            }
                            
                            if(aTileU != 0 && aTileR != 0 && aTileUR != 0)
                            {
                                if(aTileU->IsNormal() && aTileR->IsNormal() && aTileUR->IsNormal())
                                {
                                    aTile->ConnectTo(aTileUR, PATH_COST_DIA);
                                }
                            }
                            
                            if(aTileD != 0 && aTileL != 0 && aTileDL != 0)
                            {
                                if(aTileD->IsNormal() && aTileL->IsNormal() && aTileDL->IsNormal())
                                {
                                    aTile->ConnectTo(aTileDL, PATH_COST_DIA);
                                }
                            }
                            
                            if(aTileD != 0 && aTileR != 0 && aTileDR != 0)
                            {
                                if(aTileD->IsNormal() && aTileR->IsNormal() && aTileDR->IsNormal())
                                {
                                    aTile->ConnectTo(aTileDR, PATH_COST_DIA);
                                }
                            }
                        }
                        
                        GameTile *aLowerTileU = GetTile(aX, aY - 1, aDepth - 1);
                        GameTile *aLowerTileD = GetTile(aX, aY + 1, aDepth - 1);
                        GameTile *aLowerTileL = GetTile(aX - 1, aY, aDepth - 1);
                        GameTile *aLowerTileR = GetTile(aX + 1, aY, aDepth - 1);
                        
                        if(aTile->mType == TILE_TYPE_RAMP_U)
                        {
                            if(aLowerTileU)
                            {
                                if(aLowerTileU->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aLowerTileU, PATH_COST_RAMP);
                                    aLowerTileU->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            
                            if(aTileD)
                            {
                                if(aTileD->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aTileD, PATH_COST_ADJ);
                                }
                            }
                        }
                        
                        
                        if(aTile->mType == TILE_TYPE_RAMP_D)
                        {
                            if(aLowerTileD)
                            {
                                if(aLowerTileD->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aLowerTileD, PATH_COST_RAMP);
                                    aLowerTileD->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            if(aTileU)
                            {
                                if(aTileU->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aTileU, PATH_COST_ADJ);
                                }
                            }
                        }
                        
                        if(aTile->mType == TILE_TYPE_RAMP_R)
                        {
                            if(aLowerTileR)
                            {
                                if(aLowerTileR->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aLowerTileR, PATH_COST_RAMP);
                                    aLowerTileR->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            
                            if(aTileL)
                            {
                                if(aTileL->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aTileL, PATH_COST_ADJ);
                                }
                            }
                        }
                        
                        if(aTile->mType == TILE_TYPE_RAMP_L)
                        {
                            if(aLowerTileL)
                            {
                                if(aLowerTileL->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aLowerTileL, PATH_COST_RAMP);
                                    aLowerTileL->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }
                            
                            if(aTileR)
                            {
                                if(aTileR->IsBlocked() == false)
                                {
                                    aTile->ConnectTo(aTileR, PATH_COST_ADJ);
                                }
                            }
                        } 
                    }
                }
            }
        }
    }
    
    EnumList(GamePath, aPath, mPathList)
    {
        aPath->ComputePath();
    }
}

void GameArena::Save(const char *pPath)
{
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
    
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        for(int aX=0;aX<mGridWidthTotal;aX++)
        {
            for(int aY=0;aY<mGridHeightTotal;aY++)
            {
                if(mTile[aDepth][aX][aY])
                {
                    *aTileListTag += mTile[aDepth][aX][aY]->Save();
                }
            }
        }
    }
    
    
    FXMLTag *aPathListTag = new FXMLTag("path_list");
    *aArenaTag += aPathListTag;
    
    EnumList(GamePath, aPath, mPathList)
    {
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
    
    
    FreeList(GamePath, mPathList);
    
    
    FXMLTag *aArenaTag = aXML.GetRoot();
    
    if(aArenaTag)
    {
        mGridWidthActive = FString(aArenaTag->GetParamValue("grid_width_active")).ToInt();
        mGridHeightActive = FString(aArenaTag->GetParamValue("grid_height_active")).ToInt();
        
        
        mGridBufferH = FString(aArenaTag->GetParamValue("grid_buffer_h")).ToInt();
        mGridBufferV = FString(aArenaTag->GetParamValue("grid_buffer_v")).ToInt();
        
        if(mGridWidthTotal > 0 && mGridHeightTotal > 0)
        {
            SizeGrid(mGridWidthActive, mGridHeightActive, mGridBufferH, mGridBufferV);
            
            EnumTagsMatching(aArenaTag, aTileListTag, "tile_list")
            {
                EnumTags(aTileListTag, aTileTag)
                {
                    GameTile *aTile = new GameTile();
                    aTile->Load(aTileTag);
                    
                    if(aTile->mGridX >= 0 && aTile->mGridY >= 0 && aTile->mGridZ >=0 && aTile->mGridX < mGridWidthTotal && aTile->mGridY < mGridHeightTotal && aTile->mGridZ < GRID_DEPTH)
                    {
                        mTile[aTile->mGridZ][aTile->mGridX][aTile->mGridY] = aTile;
                    }
                }
            }
            
            
            EnumTagsMatching(aArenaTag, aPathListTag, "path_list")
            {
                EnumTags(aPathListTag, aPathTag)
                {
                    GamePath *aPath = new GamePath();
                    aPath->Load(aPathTag);
                    mPathList += aPath;
                }
            }
        }
    }
    
    printf("Grid Size [%d x %d] Active [%d x %d]\n", mGridWidthTotal, mGridHeightTotal, mGridWidthActive, mGridHeightTotal);
    
    ComputeAllowedPlacements();
    
    //mTowerAllowed[aX][aY]
    
    /*
    aXML.mRoot = aArenaTag;
    
    
    aArenaTag->AddParam("grid_width", FString(mGridWidth).c());
    aArenaTag->AddParam("grid_height", FString(mGridHeight).c());
    
    
    XMLTag *aTileListTag = new XMLTag("tile_list");
    *aArenaTag += aTileListTag;
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            if(mTile[i][n])
            {
                *aTileListTag += mTile[i][n]->Save();
            }
        }
    }
    */
    ComputePathConnections();
}


/*
#define THRESHHOLD 10
void Sort::AwesomeSort(int *data, int start, int end)
{
	if(start < end)
	{
		if(end - start <= THRESHHOLD)
		{
			for (int i = start + 1; i <= end; i++)
			{
				int next = data[i];
				int j = i;
				while ((j > start) && (data[j-1] > next))
				{
					data[j] = data[j-1];
					j = j - 1;
				}
				data[j] = next;
			}
			return;
		}
		int i = start;
		int j = end;
		int partition = data[(start+end)/2];
		do
		{
			while (data[i]<partition) i++;
			while (data[j]>partition) j--;
			if (i<=j)
			{
				swap(data[i], data[j]);
				i++; j--;
			}
		} while (i<=j);
		AwesomeSort(data, start, j);
		AwesomeSort(data, i, end);
	}
}
*/

