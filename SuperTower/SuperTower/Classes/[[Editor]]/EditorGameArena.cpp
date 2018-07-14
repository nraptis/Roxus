//
//  EditorGameArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "EditorGameArena.hpp"

EditorGameArena *gEditor = 0;
EditorGameArena::EditorGameArena() {
    gEditor = this;
    mTileDepth = 1;
    mTileType = TILE_TYPE_NORMAL;
    mEditorMode = EDITOR_MODE_TILES;
    mPathStartMode = false;
    mPathSelectMode = false;

    mCurrentPath = 0;

}

EditorGameArena::~EditorGameArena() {
    if (gEditor == this) {
        gEditor = 0;
    }
}

void EditorGameArena::Update() {
    EnumList(AnimatedGamePath, aPath, mPathList) {
        aPath->Update();
    }
}

void EditorGameArena::Draw() {
    GameArena::Draw();
    EnumList(AnimatedGamePath, aPath, mPathList) {
        aPath->Draw();
    }


    for (int aGridX = 0;aGridX < mGridWidthTotal;aGridX++) {
        for (int aGridY = 0;aGridY < mGridHeightTotal;aGridY++) {

            if (GetTile(aGridX, aGridY, mTileDepth) == 0) {
                float aCenterX = CX(aGridX, mTileType);
                float aCenterY = CY(aGridY, mTileType);
                float aLeft = aCenterX - gTileWidth2;
                float aRight = aCenterX + gTileWidth2;
                float aTop = aCenterY - gTileHeight2;
                float aBottom = aCenterY + gTileHeight2;
                float aWidth = aRight - aLeft;
                float aHeight = aBottom - aTop;
                Graphics::SetColor(1.0f, 1.0f, 0.5f, 0.75f);
                Graphics::OutlineRectInside(aLeft + 1.0f, aTop - 1.0f, aWidth - 2.0f, aHeight - 2.0f, 2.0f);
            }




        }
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
     for (int i=0;i<mPathSolver.mClosedListCount;i++) {
     PathSolverNeighbor *aNeighbor = mPathSolver.mClosedList[i];
     float aRectSize = 20.0f;
     float aX = CX(aNeighbor->mNode->mGridX);
     float aY = CY(aNeighbor->mNode->mGridY);

     DrawRect(aX - aRectSize / 2.0f, aY - aRectSize / 2.0f, aRectSize, aRectSize);
     }
     
     SetColor(0.0f, 1.0f, 0.0f, 0.7f);
     for (int i=0;i<mPathSolver.mOpenListCount;i++) {
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

void EditorGameArena::AddPath() {
    AnimatedGamePath *aPath = new AnimatedGamePath();
    aPath->mStartX = mGridBufferH;
    aPath->mStartY = mGridBufferV + gRand.Get(mGridHeightActive);
    aPath->mStartZ = 1;
    aPath->mEndX = mGridBufferH + mGridHeightActive - 1;
    aPath->mStartY = mGridBufferV + gRand.Get(mGridHeightActive);
    aPath->mStartZ = 1;
    mPathList += aPath;
    mCurrentPath = aPath;
    aPath->ComputePath(this);
}

void EditorGameArena::RemovePath(GamePath *pPath)
{
    if(pPath == mCurrentPath)mCurrentPath = 0;
    mPathList -= pPath;
    delete pPath;
}

void EditorGameArena::Click(float pX, float pY) {

    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;

    GetGridPos(pX, pY, aGridX, aGridY, aGridZ);
    
    if (mEditorMode == EDITOR_MODE_PATH) {
        if (aGridX != -1 && aGridY != -1 && aGridZ != -1) {
            if (mPathSelectMode) {
                mCurrentPath = 0;
                EnumList(AnimatedGamePath, aPath, mPathList) {
                    if (aPath->mStartX == aGridX && aPath->mStartY == aGridY && aPath->mStartZ == aGridZ) {
                        mCurrentPath = aPath;
                    }
                    if (aPath->mEndX == aGridX && aPath->mEndY == aGridY && aPath->mEndZ == aGridZ) {
                        mCurrentPath = aPath;
                    }
                }

                if (mCurrentPath == 0) {
                    EnumList(AnimatedGamePath, aPath, mPathList) {
                        for (int i=0;i<aPath->mLength;i++) {
                            int aPathGridX = aPath->mPathX[i];
                            int aPathGridY = aPath->mPathY[i];
                            int aPathGridZ = aPath->mPathZ[i];
                            if (aPathGridX == aGridX && aPathGridY == aGridY && aPathGridZ == aGridZ) {
                                mCurrentPath = aPath;
                            }
                        }
                    }
                }
            } else {
                //Try to select current path.
                //mCurrentPath
                if (mCurrentPath) {
                    if (mPathStartMode) {
                        mCurrentPath->mStartX = aGridX;
                        mCurrentPath->mStartY = aGridY;
                        mCurrentPath->mStartZ = aGridZ;
                    } else {
                        mCurrentPath->mEndX = aGridX;
                        mCurrentPath->mEndY = aGridY;
                        mCurrentPath->mEndZ = aGridZ;
                    }
                }
            }
        }
    } else if(mEditorMode == EDITOR_MODE_TILES) {
        GetGridPosAtDepth(pX, pY, mTileDepth, aGridX, aGridY);
        printf("Click [%d,%d] Depth[%d]\n", aGridX, aGridY, mTileDepth);
        if ((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGridWidthTotal) && (aGridY < mGridHeightTotal)) {
            if (GetTile(aGridX, aGridY, mTileDepth) == 0) {
                //If we are a bridge or tunnel, delete at depth == 1
                if (aGridZ == 0 || aGridZ == 2) {
                    DeleteTile(aGridX, aGridY, 1);
                    //If we are at depth == 1, delete bridge and tunnel
                } else {
                    DeleteTile(aGridX, aGridY, 0);
                    DeleteTile(aGridX, aGridY, 2);
                }
                GameTile *aTile = new GameTile();
                aTile->SetUp(aGridX, aGridY, mTileDepth);
                aTile->mType = mTileType;
                mTile[mTileDepth][aGridX][aGridY] = aTile;
            } else {
                DeleteTile(aGridX, aGridY, aGridZ);
            }
        }
    }
    ComputePathConnections();
    EnumList (AnimatedGamePath, aPath, mPathList) {
        aPath->ComputePath(this);
    }
}

void EditorGameArena::GetGridPosAtDepth(float pX, float pY, int pDepth, int &pGridX, int &pGridY) {
    pGridX = -1;
    pGridY = -1;
    if (pDepth >= 0 && pDepth < GRID_DEPTH) {
        int aGridX = -1;
        if (pX > 0) {
            aGridX = (int)(pX / gTileWidth);
            if (aGridX >= mGridWidthTotal) {
                aGridX = -1;
            }
        }
        if (aGridX != -1) {
            int aGridY = -1;
            int aLandGridY = (int)(pY / gTileHeight);
            float aCenterY = 0.0f;
            float aEpsilon = 0.01f;
            float aTop = 0.0f;
            float aBottom = 0.0f;
            aGridY = aLandGridY - 1;
            for (int k=0;k<3;k++) {
                aCenterY = CY(aGridY, pDepth);
                aTop = aCenterY - (gTileHeight2 + aEpsilon);
                aBottom = aCenterY + (gTileHeight2 + aEpsilon);
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

void EditorGameArena::DeleteTile(int pGridX, int pGridY, int pGridZ) {
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mGridWidthTotal) && (pGridY < mGridHeightTotal) && (pGridZ < GRID_DEPTH)) {
        delete mTile[pGridZ][pGridX][pGridY];
        mTile[pGridZ][pGridX][pGridY] = 0;
    }
}

void EditorGameArena::SaveImage() {
    int aTileWidth = 144;
    int aTileHeight = 144;
    
    int aImageWidth = mGridWidthTotal * aTileWidth;
    int aImageHeight = mGridHeightTotal * aTileHeight;
    
    printf("Saving Image!! (%d x %d)\n", aImageWidth, aImageHeight);

    FImage aImageTunnel;
    FImage aImageFloor;
    FImage aImageBridge;

    FImage aImageFloorRampU;
    FImage aImageFloorRampD;
    FImage aImageFloorRampL;
    FImage aImageFloorRampR;

    FImage aImageBridgeRampU;
    FImage aImageBridgeRampD;
    FImage aImageBridgeRampL;
    FImage aImageBridgeRampR;

    FImage aImageBlocker;

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

    FImage aSaveImage;
    aSaveImage.MakeBlank(aImageWidth, aImageHeight);

    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aY=0;aY<mGridHeightTotal;aY++) {
            for (int aX=0;aX<mGridWidthTotal;aX++) {
                GameTile *aTile = mTile[aDepth][aX][aY];
                if (aTile) {
                    FImage *aTileImage = 0;
                    FImage *aSpecialImage = 0;
                    if (aTile->mGridZ == 0) {
                        aTileImage = &aImageTunnel;
                    }
                    if (aTile->mGridZ == 1) {
                        aTileImage = &aImageFloor;
                        if(aTile->mType == TILE_TYPE_RAMP_U)aSpecialImage = &aImageFloorRampU;
                        if(aTile->mType == TILE_TYPE_RAMP_D)aSpecialImage = &aImageFloorRampD;
                        if(aTile->mType == TILE_TYPE_RAMP_L)aSpecialImage = &aImageFloorRampL;
                        if(aTile->mType == TILE_TYPE_RAMP_R)aSpecialImage = &aImageFloorRampR;
                        if(aTile->mType == TILE_TYPE_BLOCKED)aSpecialImage = &aImageBlocker;
                    }
                    if (aTile->mGridZ == 2) {
                        aTileImage = &aImageBridge;
                        if(aTile->mType == TILE_TYPE_RAMP_U)aSpecialImage = &aImageBridgeRampU;
                        if(aTile->mType == TILE_TYPE_RAMP_D)aSpecialImage = &aImageBridgeRampD;
                        if(aTile->mType == TILE_TYPE_RAMP_L)aSpecialImage = &aImageBridgeRampL;
                        if(aTile->mType == TILE_TYPE_RAMP_R)aSpecialImage = &aImageBridgeRampR;
                    }

                    int aStampX = aTile->mGridX * aTileWidth - aStampShiftX;
                    int aStampY = aTile->mGridY * aTileHeight - aStampShiftY;
                    if (aSpecialImage) {
                        aSaveImage.StampBlend(aSpecialImage, aStampX, aStampY);
                    } else if(aTileImage) {
                        aSaveImage.StampBlend(aTileImage, aStampX, aStampY);
                    }
                }
            }
        }
    }

    os_exportPNGImage(aSaveImage.mData, gDirExport.c(), aSaveImage.mWidth, aSaveImage.mHeight);
    //ExportToPhotoLibrary(aSaveImage.mData, aSaveImage.mWidth, aSaveImage.mHeight);

}





