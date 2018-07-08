//
//  GameArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "GameArena.h"
#include "Game.h"

GameArena::GameArena()
{
    mApp = GAPP;
    
    mGridWidth = 0;
    mGridHeight = 0;
    
    mArenaWidth = 100.0f;
    mArenaHeight = 100.0f;
    
    mTile = 0;
    
    Generate(10, 16);
    
    mTargetX = 0.0f;
    mTargetY = 0.0f;
    
    
    for(int i=0;i<5;i++)
    {
        Unit *aUnit = new Unit();
        
        aUnit->SetUp(gRand.Get(mGridWidth), gRand.Get(mGridHeight));
        
        mUnitList += aUnit;
        
    }
    
    
    Load("demo_arena.xml");
}

GameArena::~GameArena()
{
    
}

void GameArena::Update()
{
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
    
    
    
    
    EnumList(Tower, aTower, mTowerList)
    {
        aTower->Update();
    
        
        if(aTower->mCoolDownTime <= 0)
        {
            
        }
    
    }
    
    
    
    
    //mUnitKillList
    
}

void GameArena::Draw()
{
    SetColor();
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            if(mTile[i][n])
            {
                mTile[i][n]->Draw();
            }
        }
    }
    
    EnumList(Tower, aTower, mTowerList)
    {
        aTower->FacePoint(mTargetX, mTargetY);
    }
    
    EnumList(Tower, aTower, mTowerList)
    {
        aTower->Draw();
    }
    
    SetColor(0.0f, 1.0f, 0.25f);
    
    DrawRect(mTargetX - 13, mTargetY - 13, 25, 25);
    
    
    EnumList(Unit, aUnit, mUnitList)
    {
        aUnit->Draw();
    }
    
}

void GameArena::Generate(int pWidth, int pHeight)
{
    SizeGrid(pWidth, pHeight);
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            mTile[i][n] = new GameTile();
            mTile[i][n]->SetUp(0, i, n);
        }
    }
}

void GameArena::SizeGrid(int pWidth, int pHeight)
{
    if(mTile)
    {
        for(int i=0;i<mGridWidth;i++)delete [] mTile[i];
        delete [] mTile;
    }
    
    mGridWidth = pWidth;
    mGridHeight = pHeight;
    
    
    mTile = new GameTile**[mGridWidth];
    for(int i=0;i<mGridWidth;i++)
    {
        mTile[i] = new GameTile*[mGridHeight];
        for(int n=0;n<mGridHeight;n++)
        {
            mTile[i][n] = 0;
        }
    }
    
    mArenaWidth = pWidth * gTileWidth;
    mArenaHeight = pHeight * gTileHeight;
}

GameTile *GameArena::GetTile(int pGridX, int pGridY)
{
    GameTile *aReturn = 0;
    
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight))
    {
        aReturn = mTile[pGridX][pGridY];
    }
    
    return aReturn;
}

int GameArena::GetTouchGridX(float pX)
{
    int aReturn = -1;
    
    if(pX > 0)
    {
        pX /= gTileWidth;
        if(pX < mGridWidth)
        {
            aReturn = pX;
        }
    }
    
    return aReturn;
}

int GameArena::GetTouchGridY(float pY)
{
    int aReturn = -1;
    
    //pY -= (gBoardY - mVerticalOffset);// - gTileHeight / 2);
    
    if(pY > 0)
    {
        pY /= gTileHeight;
        if(pY < mGridHeight)
        {
            aReturn = pY;
        }
    }
    return aReturn;
}

void GameArena::Click(float pX, float pY)
{
    int aGridX = GetTouchGridX(pX);
    int aGridY = GetTouchGridY(pY);
    
    if((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGridWidth) && (aGridY < mGridHeight))
    {
        
        Tower *aTower = GetTower(aGridX, aGridY);
        
        if(aTower == 0)
        {
            if(mTowerList.mCount < 5)
            {
                aTower = new Tower();
                aTower->SetUp(aGridX, aGridY);
                
                mTowerList += aTower;
            }
            else
            {
                mTargetX = pX;
                mTargetY = pY;
            }
        }
        else
        {
            mTowerList -= aTower;
        }

        
    }
    
    /*
    printf("Grid[%d, %d]\n", aGridX, aGridY);
    GameTile *aTile = GetTile(aGridX, aGridY);
    if(aTile)
    {
        aTile->mType++;
        if(aTile->mType >= 4)aTile->mType = 0;
    }
    */
}

Tower *GameArena::GetTower(int pGridX, int pGridY)
{
    Tower *aReturn = 0;
    EnumList(Tower, aTower, mTowerList)
    {
        if(aTower->mGridX == pGridX && aTower->mGridY == pGridY)
        {
            aReturn = aTower;
        }
    }
    return aReturn;
}

void GameArena::Path(int pStartX, int pStartY, int pEndX, int pEndY)
{
    mPathSolver.Clear();
    
    int aHorizontalCost = 100;
    int aVerticalCost = 141;
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            GameTile *aTile = GetTile(i, n);
            
            if(aTile)
            {
                if(aTile->mTunnelU || aTile->mTunnelD || aTile->mTunnelR || aTile->mTunnelL)
                {
                    PathSolverNode *aNode = new PathSolverNode(i, n, 0);
                    mPathSolver.AddNode(aNode);
                }
                
                if(aTile->mBridgeU || aTile->mBridgeD || aTile->mBridgeR || aTile->mBridgeL)
                {
                    PathSolverNode *aNode = new PathSolverNode(i, n, 1);
                    mPathSolver.AddNode(aNode);
                }
            }
        }
    }
    
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            for(int aAddX=-1;aAddX<=1;aAddX++)
            {
                for(int aAddY=-1;aAddY<=1;aAddY++)
                {
                    if(aAddX != 0 || aAddY != 0)
                    {
                        if(TunnelConnected(i, n, i + aAddX, n + aAddY))
                        {
                            if(aAddX != 0 && aAddY != 0)
                            {
                                mPathSolver.Connect(i, n, 0, i + aAddX, n + aAddY, 0, aVerticalCost);
                            }
                            else
                            {
                                mPathSolver.Connect(i, n, 0, i + aAddX, n + aAddY, 0, aHorizontalCost);
                            }
                        }
                    }
                }
            }
        }
    }
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            for(int aAddX=-1;aAddX<=1;aAddX++)
            {
                for(int aAddY=-1;aAddY<=1;aAddY++)
                {
                    if(aAddX != 0 || aAddY != 0)
                    {
                        if(BridgeConnected(i, n, i + aAddX, n + aAddY))
                        {
                            if(aAddX != 0 && aAddY != 0)
                            {
                                mPathSolver.Connect(i, n, 1, i + aAddX, n + aAddY, 1, aVerticalCost);
                            }
                            else
                            {
                                mPathSolver.Connect(i, n, 1, i + aAddX, n + aAddY, 1, aHorizontalCost);
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            for(int aAddX=-1;aAddX<=1;aAddX++)
            {
                for(int aAddY=-1;aAddY<=1;aAddY++)
                {
                    if(aAddX != 0 || aAddY != 0)
                    {
                        if(RampConnectedDown(i, n, i + aAddX, n + aAddY))
                        {
                            mPathSolver.Connect(i, n, 1, i + aAddX, n + aAddY, 0, aVerticalCost);
                        }
                        if(RampConnectedUp(i, n, i + aAddX, n + aAddY))
                        {
                            mPathSolver.Connect(i, n, 0, i + aAddX, n + aAddY, 1, aVerticalCost);
                        }
                    }
                }
            }
        }
    }
    
    
    /*
    for(int i=0;i<mPathSolver.mNodeCount;i++)
    {
        
        int aCount = gRand.Get(7);
        
        
        for(int k=0;k<aCount;k++)
        {
            int aRand = gRand.Get(mPathSolver.mNodeCount);
            mPathSolver.mNode[i]->AddNode(mPathSolver.mNode[aRand], 0);
        }
    }
    */
    
}

bool GameArena::TunnelConnected(int pStartX, int pStartY, int pEndX, int pEndY)
{
    bool aReturn = false;
    
    GameTile *aStartTile = GetTile(pStartX, pStartY);
    GameTile *aEndTile = GetTile(pEndX, pEndY);
    
    if(aStartTile != 0 && aEndTile != 0)
    {
        
        GameTile *aTileUp = GetTile(pStartX, pStartY - 1);
        GameTile *aTileDown = GetTile(pStartX, pStartY + 1);
        GameTile *aTileLeft = GetTile(pStartX - 1, pStartY);
        GameTile *aTileRight = GetTile(pStartX + 1, pStartY);
        
        //Up
        if(pStartX == pEndX && pStartY == (pEndY + 1))
        {
            if(aStartTile->mTunnelU && aEndTile->mTunnelD)aReturn = true;
        }
        //Down
        if(pStartX == pEndX && pStartY == (pEndY - 1))
        {
            if(aStartTile->mTunnelD && aEndTile->mTunnelU)aReturn = true;
        }
        //Right
        if(pStartX == (pEndX - 1) && pStartY == pEndY)
        {
            if(aStartTile->mTunnelR && aEndTile->mTunnelL)aReturn = true;
        }
        //Left
        if(pStartX == (pEndX + 1) && pStartY == pEndY)
        {
            if(aStartTile->mTunnelL && aEndTile->mTunnelR)aReturn = true;
        }
        
        //Up, Left
        if(pStartX == (pEndX + 1) && pStartY == (pEndY + 1))
        {
            if(aTileUp != 0 && aTileLeft != 0)
            {
                if(aStartTile->mTunnelU && aStartTile->mTunnelL && aEndTile->mTunnelD && aEndTile->mTunnelR)
                {
                    if(aTileLeft->mTunnelR && aTileLeft->mTunnelU && aTileUp->mTunnelD && aTileUp->mTunnelL)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
        //Up, Right
        if(pStartX == (pEndX - 1) && pStartY == (pEndY + 1))
        {
            if(aTileUp != 0 && aTileRight != 0)
            {
                if(aStartTile->mTunnelU && aStartTile->mTunnelR && aEndTile->mTunnelD && aEndTile->mTunnelL)
                {
                    if(aTileRight->mTunnelL && aTileRight->mTunnelU && aTileUp->mTunnelD && aTileUp->mTunnelR)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
        //Down, Right
        
        if(pStartX == (pEndX - 1) && pStartY == (pEndY - 1))
        {
            if(aTileDown != 0 && aTileRight != 0)
            {
                if(aStartTile->mTunnelD && aStartTile->mTunnelR && aEndTile->mTunnelU && aEndTile->mTunnelL)
                {
                    if(aTileRight->mTunnelL && aTileRight->mTunnelD && aTileDown->mTunnelU && aTileDown->mTunnelR)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
        //Down, Left!
        if(pStartX == (pEndX + 1) && pStartY == (pEndY - 1))
        {
            if(aTileDown != 0 && aTileLeft != 0)
            {
                if(aStartTile->mTunnelD && aStartTile->mTunnelL && aEndTile->mTunnelU && aEndTile->mTunnelR)
                {
                    if(aTileLeft->mTunnelR && aTileLeft->mTunnelD && aTileDown->mTunnelU && aTileDown->mTunnelL)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
    }
    
    return aReturn;
}


bool GameArena::BridgeConnected(int pStartX, int pStartY, int pEndX, int pEndY)
{
    bool aReturn = false;
    
    GameTile *aStartTile = GetTile(pStartX, pStartY);
    GameTile *aEndTile = GetTile(pEndX, pEndY);
    
    if(aStartTile != 0 && aEndTile != 0)
    {
        
        GameTile *aTileUp = GetTile(pStartX, pStartY - 1);
        GameTile *aTileDown = GetTile(pStartX, pStartY + 1);
        GameTile *aTileLeft = GetTile(pStartX - 1, pStartY);
        GameTile *aTileRight = GetTile(pStartX + 1, pStartY);
        
        //Up
        if(pStartX == pEndX && pStartY == (pEndY + 1))
        {
            if(aStartTile->mBridgeU && aEndTile->mBridgeD)aReturn = true;
        }
        //Down
        if(pStartX == pEndX && pStartY == (pEndY - 1))
        {
            if(aStartTile->mBridgeD && aEndTile->mBridgeU)aReturn = true;
        }
        //Right
        if(pStartX == (pEndX - 1) && pStartY == pEndY)
        {
            if(aStartTile->mBridgeR && aEndTile->mBridgeL)aReturn = true;
        }
        //Left
        if(pStartX == (pEndX + 1) && pStartY == pEndY)
        {
            if(aStartTile->mBridgeL && aEndTile->mBridgeR)aReturn = true;
        }
        
        //Up, Left
        if(pStartX == (pEndX + 1) && pStartY == (pEndY + 1))
        {
            if(aTileUp != 0 && aTileLeft != 0)
            {
                if(aStartTile->mBridgeU && aStartTile->mBridgeL && aEndTile->mBridgeD && aEndTile->mBridgeR)
                {
                    if(aTileLeft->mBridgeR && aTileLeft->mBridgeU && aTileUp->mBridgeD && aTileUp->mBridgeL)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
        //Up, Right
        if(pStartX == (pEndX - 1) && pStartY == (pEndY + 1))
        {
            if(aTileUp != 0 && aTileRight != 0)
            {
                if(aStartTile->mBridgeU && aStartTile->mBridgeR && aEndTile->mBridgeD && aEndTile->mBridgeL)
                {
                    if(aTileRight->mBridgeL && aTileRight->mBridgeU && aTileUp->mBridgeD && aTileUp->mBridgeR)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
        //Down, Right
        
        if(pStartX == (pEndX - 1) && pStartY == (pEndY - 1))
        {
            if(aTileDown != 0 && aTileRight != 0)
            {
                if(aStartTile->mBridgeD && aStartTile->mBridgeR && aEndTile->mBridgeU && aEndTile->mBridgeL)
                {
                    if(aTileRight->mBridgeL && aTileRight->mBridgeD && aTileDown->mBridgeU && aTileDown->mBridgeR)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
        //Down, Left!
        if(pStartX == (pEndX + 1) && pStartY == (pEndY - 1))
        {
            if(aTileDown != 0 && aTileLeft != 0)
            {
                if(aStartTile->mBridgeD && aStartTile->mBridgeL && aEndTile->mBridgeU && aEndTile->mBridgeR)
                {
                    if(aTileLeft->mBridgeR && aTileLeft->mBridgeD && aTileDown->mBridgeU && aTileDown->mBridgeL)
                    {
                        aReturn = true;
                    }
                }
            }
        }
        
    }
    
    return aReturn;
}

bool GameArena::RampConnectedDown(int pStartX, int pStartY, int pEndX, int pEndY)
{
    bool aReturn = false;
    
    if(BridgeConnected(pStartX, pStartY, pEndX, pEndY))
    {
        
    }
    else if(TunnelConnected(pStartX, pStartY, pEndX, pEndY))
    {
        
    }
    else
    {
        GameTile *aStartTile = GetTile(pStartX, pStartY);
        GameTile *aEndTile = GetTile(pEndX, pEndY);
        
        if(aStartTile != 0 && aEndTile != 0)
        {
            //Up
            if(pStartX == pEndX && pStartY == (pEndY + 1))
            {
                if(aStartTile->mBridgeU && aEndTile->mTunnelD)aReturn = true;
            }
            //Down
            if(pStartX == pEndX && pStartY == (pEndY - 1))
            {
                if(aStartTile->mBridgeD && aEndTile->mTunnelU)aReturn = true;
            }
            //Right
            if(pStartX == (pEndX - 1) && pStartY == pEndY)
            {
                if(aStartTile->mBridgeR && aEndTile->mTunnelL)aReturn = true;
            }
            //Left
            if(pStartX == (pEndX + 1) && pStartY == pEndY)
            {
                if(aStartTile->mBridgeL && aEndTile->mTunnelR)aReturn = true;
            }
        }
    }
    
    return aReturn;
}

bool GameArena::RampConnectedUp(int pStartX, int pStartY, int pEndX, int pEndY)
{
    bool aReturn = false;
    
    if(BridgeConnected(pStartX, pStartY, pEndX, pEndY))
    {
        
    }
    else if(TunnelConnected(pStartX, pStartY, pEndX, pEndY))
    {
        
    }
    else
    {
        GameTile *aStartTile = GetTile(pStartX, pStartY);
        GameTile *aEndTile = GetTile(pEndX, pEndY);
        
        if(aStartTile != 0 && aEndTile != 0)
        {
            //Up
            if(pStartX == pEndX && pStartY == (pEndY + 1))
            {
                if(aStartTile->mTunnelU && aEndTile->mBridgeD)aReturn = true;
            }
            //Down
            if(pStartX == pEndX && pStartY == (pEndY - 1))
            {
                if(aStartTile->mTunnelD && aEndTile->mBridgeU)aReturn = true;
            }
            //Right
            if(pStartX == (pEndX - 1) && pStartY == pEndY)
            {
                if(aStartTile->mTunnelR && aEndTile->mBridgeL)aReturn = true;
            }
            //Left
            if(pStartX == (pEndX + 1) && pStartY == pEndY)
            {
                if(aStartTile->mTunnelL && aEndTile->mBridgeR)aReturn = true;
            }
        }
    }
    
    return aReturn;
}

void GameArena::Save(const char *pPath)
{
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    aPath = (gDocuments + aPath);
    
    XML aXML;
    
    XMLTag *aArenaTag = new XMLTag("game_arena");
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
    
    aXML.Print();
    aXML.Save(aPath.c());
    
}

void GameArena::Load(const char *pPath)
{
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    //aPath = (gDocuments + aPath);
    
    XML aXML;
    aXML.Load(aPath);
    
    
    
    
    XMLTag *aArenaTag = aXML.GetRoot();
    
    if(aArenaTag)
    {
        mGridWidth = FString(aArenaTag->GetParamValue("grid_width")).ToInt();
        mGridHeight = FString(aArenaTag->GetParamValue("grid_height")).ToInt();
        
        printf("Loaded Size(%d x %d)\n", mGridWidth, mGridHeight);
        
        if(mGridWidth > 0 && mGridHeight > 0)
        {
            SizeGrid(mGridWidth, mGridHeight);
            
            
            EnumTagsMatching(aArenaTag, aTileListTag, "tile_list")
            {
                EnumTags(aTileListTag, aTileTag)
                {
                    GameTile *aTile = new GameTile();
                    aTile->Load(aTileTag);
                    
                    
                    if(aTile->mGridX >= 0 && aTile->mGridY >= 0 && aTile->mGridX < mGridWidth && aTile->mGridY < mGridHeight)
                    {
                        mTile[aTile->mGridX][aTile->mGridY] = aTile;
                    }
                }
            }
        }
        
    }
    
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
    
}
