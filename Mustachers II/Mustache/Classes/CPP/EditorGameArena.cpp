//
//  EditorGameArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "EditorGameArena.h"
#include "Game.h"

EditorGameArena *gEditor = 0;

EditorGameArena::EditorGameArena()
{
    gEditor = this;
    
    mTileDepth = 1;
    mTileType = TILE_TYPE_NORMAL;
    
    mEditorMode = EDITOR_MODE_TILES;
    
    mPathStartMode = false;
}

EditorGameArena::~EditorGameArena()
{
    
}

void EditorGameArena::Update()
{
    EnumList(GamePath, aPath, mPathList)
    {
        aPath->Update();
    }
}

void EditorGameArena::Draw()
{
    GameArena::Draw();
    
    
    EnumList(GamePath, aPath, mPathList)
    {
        aPath->Draw();
    }
    
    /*
    SetColor();
    
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        SetColorSwatch(aDepth);
        for(int aX=0;aX<mGridWidth;aX++)
        {
            for(int aY=0;aY<mGridHeight;aY++)
            {
                GameTile *aTile = mTile[aDepth][aX][aY];
                if(aTile)
                {
                    aTile->DrawConnections();
                }
            }
        }
    }
    */
    
    
    /*
    SetColor(1.0f, 0.0f, 0.0f, 0.8f);
    
    for(int i=0;i<mPathSolver.mClosedListCount;i++)
    {
        PathSolverNeighbor *aNeighbor = mPathSolver.mClosedList[i];
        
        float aRectSize = 20.0f;
        float aX = CX(aNeighbor->mNode->mGridX);
        float aY = CY(aNeighbor->mNode->mGridY);
        
        DrawRect(aX - aRectSize / 2.0f, aY - aRectSize / 2.0f, aRectSize, aRectSize);
    }
    
    
    
    
    

    
    SetColor(0.0f, 1.0f, 0.0f, 0.7f);
    
    for(int i=0;i<mPathSolver.mOpenListCount;i++)
    {
        PathSolverNeighbor *aNeighbor = mPathSolver.mOpenList[i];
        
        float aRectSize = 15.0f;
        float aX = CX(aNeighbor->mNode->mGridX);
        float aY = CY(aNeighbor->mNode->mGridY);
        
        DrawRect(aX - aRectSize / 2.0f, aY - aRectSize / 2.0f, aRectSize, aRectSize);
    }
    
    
    
    
    
    
    
    PathSolverNeighbor *aPath = mPathSolver.mPathEnd;
    while(aPath)
    {
        if(aPath->mNode->mGridZ == 0)SetColor(1.0f, 1.0f, 1.0f);
        else SetColor(0.9f, 0.9f, 0.9f);
        
        DrawRect(CX(aPath->mNode->mGridX) - 9, CY(aPath->mNode->mGridY), 19.0f, 19.0f);
        
        aPath = aPath->mParent;
    }
    */
}

void EditorGameArena::AddPath()
{
    GamePath *aPath = new GamePath();
    
    aPath->mStartX = mGridBufferH;
    aPath->mStartY = mGridBufferV + gRand.Get(mGridHeightActive);
    aPath->mStartZ = 1;
    
    aPath->mEndX = mGridBufferH + mGridHeightActive - 1;
    aPath->mStartY = mGridBufferV + gRand.Get(mGridHeightActive);
    aPath->mStartZ = 1;
    
    mPathList += aPath;
    mCurrentPath = aPath;
    
    aPath->ComputePath();
}

void EditorGameArena::RemovePath(GamePath *pPath)
{
    if(pPath == mCurrentPath)mCurrentPath = 0;
    mPathList -= pPath;
    delete pPath;
}


void EditorGameArena::Click(float pX, float pY)
{
    
    int aGridX = GetGridX(pX);
    int aGridY = GetGridY(pY);
    
    if(mEditorMode == EDITOR_MODE_PATH)
    {
        if(mCurrentPath)
        {
            if(mPathStartMode)
            {
                mCurrentPath->mStartX = aGridX;
                mCurrentPath->mStartY = aGridY;
            }
            else
            {
                mCurrentPath->mEndX = aGridX;
                mCurrentPath->mEndY = aGridY;
            }
        }
    }
    else if(mEditorMode == EDITOR_MODE_TILES)
    {
        
        if((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGridWidthTotal) && (aGridY < mGridHeightTotal))
        {
            GameTile *aTile = GetTile(aGridX, aGridY, mTileDepth);
            
            if(aTile == 0)
            {
                aTile = new GameTile();
                aTile->SetUp(aGridX, aGridY, mTileDepth);
                aTile->mType = mTileType;
                mTile[mTileDepth][aGridX][aGridY] = aTile;
            }
            else
            {
                if(mTileType == TILE_TYPE_NORMAL)
                {
                    mTile[mTileDepth][aGridX][aGridY] = 0;
                    delete aTile;
                }
                else
                {
                    if(aTile->mType == mTileType)
                    {
                        aTile->mType = TILE_TYPE_NORMAL;
                    }
                    else
                    {
                        aTile->mType = mTileType;
                    }
                }
            }
        }
        else
        {
            
        }
    }
    
    ComputePathConnections();
    
    EnumList(GamePath, aPath, mPathList)
    {
        
        
        aPath->ComputePath();
    }
}

void EditorGameArena::SaveImage()
{
    int aTileWidth = 144;
    int aTileHeight = 144;
    
    int aImageWidth = mGridWidthTotal * aTileWidth;
    int aImageHeight = mGridHeightTotal * aTileHeight;
    
    printf("Saving Image!! (%d x %d)\n", aImageWidth, aImageHeight);
    
    
    Image aImageTunnel;
    Image aImageFloor;
    Image aImageBridge;
    
    Image aImageFloorRampU;
    Image aImageFloorRampD;
    Image aImageFloorRampL;
    Image aImageFloorRampR;
    
    Image aImageBridgeRampU;
    Image aImageBridgeRampD;
    Image aImageBridgeRampL;
    Image aImageBridgeRampR;
    
    Image aImageBlocker;
    
    
    
    aImageTunnel.Load("tile_tunnel.png");
    aImageFloor.Load("tile_floor.png");
    aImageBridge.Load("tile_bridge.png");
    
    aImageFloorRampU.Load("floor_ramp_u.png");
    aImageFloorRampD.Load("floor_ramp_d.png");
    aImageFloorRampL.Load("floor_ramp_l.png");
    aImageFloorRampR.Load("floor_ramp_r.png");
    
    aImageBridgeRampU.Load("bridge_ramp_u.png");
    aImageBridgeRampD.Load("bridge_ramp_d.png");
    aImageBridgeRampL.Load("bridge_ramp_l.png");
    aImageBridgeRampR.Load("bridge_ramp_r.png");
    
    aImageBlocker.Load("blocker.png");
    
    
    
    int aStampShiftX = (aImageFloor.mWidth - aTileWidth) / 2;
    int aStampShiftY = (aImageFloor.mHeight - aTileHeight) / 2;
    
    
    Image aSaveImage;
    aSaveImage.MakeBlank(aImageWidth, aImageHeight);
    
    
    
    
    for(int aDepth=0;aDepth<GRID_DEPTH;aDepth++)
    {
        
        for(int aY=0;aY<mGridHeightTotal;aY++)
        {
            for(int aX=0;aX<mGridWidthTotal;aX++)
            {
                
                GameTile *aTile = mTile[aDepth][aX][aY];
                if(aTile)
                {
                    Image *aTileImage = 0;
                    Image *aSpecialImage = 0;

                    
                    
                    
                    if(aTile->mGridZ == 0)
                    {
                        aTileImage = &aImageTunnel;
                    }
                    if(aTile->mGridZ == 1)
                    {
                        aTileImage = &aImageFloor;
                        
                        if(aTile->mType == TILE_TYPE_RAMP_U)aSpecialImage = &aImageFloorRampU;
                        if(aTile->mType == TILE_TYPE_RAMP_D)aSpecialImage = &aImageFloorRampD;
                        if(aTile->mType == TILE_TYPE_RAMP_L)aSpecialImage = &aImageFloorRampL;
                        if(aTile->mType == TILE_TYPE_RAMP_R)aSpecialImage = &aImageFloorRampR;
                        
                        if(aTile->mType == TILE_TYPE_BLOCKED)aSpecialImage = &aImageBlocker;
                        
                    }
                    if(aTile->mGridZ == 2)
                    {
                        aTileImage = &aImageBridge;
                        
                        if(aTile->mType == TILE_TYPE_RAMP_U)aSpecialImage = &aImageBridgeRampU;
                        if(aTile->mType == TILE_TYPE_RAMP_D)aSpecialImage = &aImageBridgeRampD;
                        if(aTile->mType == TILE_TYPE_RAMP_L)aSpecialImage = &aImageBridgeRampL;
                        if(aTile->mType == TILE_TYPE_RAMP_R)aSpecialImage = &aImageBridgeRampR;
                    }
                    
                    int aStampX = aTile->mGridX * aTileWidth - aStampShiftX;
                    int aStampY = aTile->mGridY * aTileHeight - aStampShiftY;
                    
                    if(aSpecialImage)
                    {
                        aSaveImage.StampBlend(aSpecialImage, aStampX, aStampY);
                    }
                    else if(aTileImage)
                    {
                        aSaveImage.StampBlend(aTileImage, aStampX, aStampY);
                    }
                    
                    //
                }
            }
        }
    }
    
    ExportToPhotoLibrary(aSaveImage.mData, aSaveImage.mWidth, aSaveImage.mHeight);
}





