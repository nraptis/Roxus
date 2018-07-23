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

    mGridOpacity = 0.0125f;


}

EditorGameArena::~EditorGameArena() {
    if (gEditor == this) {
        gEditor = 0;
    }
}

void EditorGameArena::Update() {
    
    if (mEditorMode == EDITOR_MODE_TILES) {
        if (mTileDepth == 0) {
            if (mTileType == TILE_TYPE_RAMP_U || mTileType == TILE_TYPE_RAMP_R || mTileType == TILE_TYPE_RAMP_D || mTileType == TILE_TYPE_RAMP_L) {
                mTileType = TILE_TYPE_NORMAL;
            }
        }
    }

    EnumList(AnimatedLevelPath, aPath, mPathList) {
        aPath->mEditorMode = true;//(mEditorMode == EDITOR_MODE_PATH);
        aPath->mSelected = (aPath == mCurrentPath);
        aPath->Update();
    }
}

void EditorGameArena::Draw() {
    GameArena::Draw();
    EnumList(AnimatedLevelPath, aPath, mPathList) {
        aPath->DrawEditorMarkers();
    }

    if (mEditorMode == EDITOR_MODE_TILES) {
        for (int aGridX = 0;aGridX < mTileGridWidthTotal;aGridX++) {
            for (int aGridY = 0;aGridY < mTileGridHeightTotal;aGridY++) {
                if (GetTile(aGridX, aGridY, mTileDepth) == 0) {
                    float aCenterX = CX(aGridX, mTileDepth);
                    float aCenterY = CY(aGridY, mTileDepth);
                    float aLeft = aCenterX - gTileSize2;
                    float aRight = aCenterX + gTileSize2;
                    float aTop = aCenterY - gTileSize2;
                    float aBottom = aCenterY + gTileSize2;
                    float aWidth = aRight - aLeft;
                    float aHeight = aBottom - aTop;
                    Graphics::SetColor(1.0f, 1.0f, 0.0f, mGridOpacity);
                    Graphics::OutlineRectInside(aLeft + 1.0f, aTop - 1.0f, aWidth - 2.0f, aHeight - 2.0f, 2.0f);

                    Graphics::SetColor(1.0f, 0.25f, 0.25f, mGridOpacity);
                    Graphics::OutlineRectInside(aCenterX - 2.0f, aCenterY - 2.0f, 5.0f, 5.0f, 1.0f);

                    Graphics::SetColor(0.125f, 0.25f, 0.65f, mGridOpacity);
                    Graphics::DrawPoint(aCenterX, aCenterY, 3.0f);

                }
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
    AnimatedLevelPath *aPath = new AnimatedLevelPath();
    aPath->mStartX = mTileGridBufferH;
    aPath->mStartY = mTileGridBufferV + gRand.Get(mTileGridHeightActive);
    aPath->mStartZ = 1;
    aPath->mEndX = mTileGridBufferH + mTileGridHeightActive - 1;
    aPath->mStartY = mTileGridBufferV + gRand.Get(mTileGridHeightActive);
    aPath->mStartZ = 1;
    mPathList += aPath;
    mCurrentPath = aPath;
    aPath->ComputePath(this);
}

void EditorGameArena::DeleteCurrentPath() {
    RemovePath(mCurrentPath);
}

void EditorGameArena::RemovePath(AnimatedLevelPath *pPath) {
    if (pPath) {
        mPathList.Remove(pPath);
        //delete pPath;
        if(pPath == mCurrentPath)mCurrentPath = 0;
    }
}

void EditorGameArena::Click(float pX, float pY) {
    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;
    GetEditorGridPos(pX, pY, aGridX, aGridY, aGridZ);

    if (aGridX == -1 || aGridY == -1 || aGridZ == -1) {
        GetGridPosAtDepth(pX, pY, mTileDepth, aGridX, aGridY);
        aGridZ = mTileDepth;
    }



    if (mEditorMode == EDITOR_MODE_PATH) {
        if (mPathSelectMode || mCurrentPath == 0) {
            AttemptPathSelect(pX, pY);
        } else {
            if (aGridX != -1 && aGridY != -1 && mCurrentPath != 0) {
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
    } else if(mEditorMode == EDITOR_MODE_TILES) {
        GetGridPosAtDepth(pX, pY, mTileDepth, aGridX, aGridY);
        printf("Click [%d,%d] Depth[%d]\n", aGridX, aGridY, mTileDepth);
        if ((aGridX >= 0) && (aGridY >= 0) && (aGridX < mTileGridWidthTotal) && (aGridY < mTileGridHeightTotal)) {
            GameTile *aTile = GetTile(aGridX, aGridY, mTileDepth);
            if (aTile) {
                if (aTile->mTileType == mTileType) {
                    DeleteTile(aGridX, aGridY, mTileDepth);
                } else {
                    aTile->mTileType = mTileType;
                }
            } else {
                aTile = new GameTile();
                aTile->SetUp(aGridX, aGridY, mTileDepth);
                aTile->mTileType = mTileType;
                mTile[mTileDepth][aGridX][aGridY] = aTile;
            }
            RefreshUnitGridNodes();
        }
    }
    ComputePathConnections();
    EnumList (AnimatedLevelPath, aPath, mPathList) {
        aPath->ComputePath(this);
    }
}

void EditorGameArena::AttemptPathSelect(float pX, float pY) {
    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;
    GetEditorGridPos(pX, pY, aGridX, aGridY, aGridZ);
    mCurrentPath = 0;
    if (aGridX != -1 && aGridY != -1 && aGridZ != -1) {
        EnumList(AnimatedLevelPath, aPath, mPathList) {
            if (aPath->mStartX == aGridX && aPath->mStartY == aGridY && aPath->mStartZ == aGridZ) {
                mCurrentPath = aPath;
            }
            if (aPath->mEndX == aGridX && aPath->mEndY == aGridY && aPath->mEndZ == aGridZ) {
                mCurrentPath = aPath;
            }
        }
        if (mCurrentPath == 0) {
            EnumList(AnimatedLevelPath, aPath, mPathList) {
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
    }


    if (mCurrentPath == 0) {


        mCurrentPath = 0;
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            GetGridPosAtDepth(pX, pY, aDepth, aGridX, aGridY);

            EnumList(AnimatedLevelPath, aPath, mPathList) {
                if (aPath->mStartX == aGridX && aPath->mStartY == aGridY && aPath->mStartZ == aDepth) {
                    mCurrentPath = aPath;
                }
                if (aPath->mEndX == aGridX && aPath->mEndY == aGridY && aPath->mEndZ == aDepth) {
                    mCurrentPath = aPath;
                }
            }
            if (mCurrentPath == 0) {
                EnumList(AnimatedLevelPath, aPath, mPathList) {
                    for (int i=0;i<aPath->mLength;i++) {
                        int aPathGridX = aPath->mPathX[i];
                        int aPathGridY = aPath->mPathY[i];
                        int aPathGridZ = aPath->mPathZ[i];
                        if (aPathGridX == aGridX && aPathGridY == aGridY && aPathGridZ == aDepth) {
                            mCurrentPath = aPath;
                        }
                    }
                }
            }
        }
    }

}

void EditorGameArena::GetGridPosAtDepth(float pX, float pY, int pDepth, int &pGridX, int &pGridY) {
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

void EditorGameArena::GetEditorGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ) {
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

void EditorGameArena::DeleteTile(int pGridX, int pGridY, int pGridZ) {
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mTileGridWidthTotal) && (pGridY < mTileGridHeightTotal) && (pGridZ < GRID_DEPTH)) {
        delete mTile[pGridZ][pGridX][pGridY];
        mTile[pGridZ][pGridX][pGridY] = 0;
    }
}




void EditorGameArena::ExportMap() {
    FString aPath = "recent_map_data.xml";
    Save(aPath.c());
}

void EditorGameArena::ExportImage() {
    int aTileWidth = 144;
    int aTileHeight = 144;
    int aImageWidth = mTileGridWidthTotal * aTileWidth;
    int aImageHeight = mTileGridHeightTotal * aTileHeight;
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

    for (int aIter=0;aIter<2;aIter++) {
        if (aIter == 1) {
            aImageTunnel.SubtractAlpha(64);
            aImageFloor.SubtractAlpha(64);
            aImageBridge.SubtractAlpha(64);
            aImageFloorRampU.SubtractAlpha(64);
            aImageFloorRampD.SubtractAlpha(64);
            aImageFloorRampL.SubtractAlpha(64);
            aImageFloorRampR.SubtractAlpha(64);
            aImageBridgeRampU.SubtractAlpha(64);
            aImageBridgeRampD.SubtractAlpha(64);
            aImageBridgeRampL.SubtractAlpha(64);
            aImageBridgeRampR.SubtractAlpha(64);
            aImageBlocker.SubtractAlpha(64);
        }
        int aStampShiftX = (aImageFloor.mWidth - aTileWidth) / 2;
        int aStampShiftY = (aImageFloor.mHeight - aTileHeight) / 2;
        int aStampShiftCenterUp = -96;
        int aStampShiftCenterDown = 96;

        FImage aSaveImage;
        aSaveImage.Make(aImageWidth, aImageHeight, 0xFFFFFFFF);
        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                for (int aX=0;aX<mTileGridWidthTotal;aX++) {
                    GameTile *aTile = mTile[aDepth][aX][aY];
                    if (aTile) {
                        FImage *aTileImage = 0;
                        FImage *aSpecialImage = 0;
                        if (aTile->mGridZ == 0) {
                            aTileImage = &aImageTunnel;
                        }
                        if (aTile->mTileType == TILE_TYPE_BLOCKED) {
                            aSpecialImage = &aImageBlocker;
                        }
                        if (aTile->mGridZ == 1) {
                            aTileImage = &aImageFloor;
                            if(aTile->mTileType == TILE_TYPE_RAMP_U)aSpecialImage = &aImageFloorRampU;
                            if(aTile->mTileType == TILE_TYPE_RAMP_D)aSpecialImage = &aImageFloorRampD;
                            if(aTile->mTileType == TILE_TYPE_RAMP_L)aSpecialImage = &aImageFloorRampL;
                            if(aTile->mTileType == TILE_TYPE_RAMP_R)aSpecialImage = &aImageFloorRampR;
                        }
                        if (aTile->mGridZ == 2) {
                            aTileImage = &aImageBridge;
                            if(aTile->mTileType == TILE_TYPE_RAMP_U)aSpecialImage = &aImageBridgeRampU;
                            if(aTile->mTileType == TILE_TYPE_RAMP_D)aSpecialImage = &aImageBridgeRampD;
                            if(aTile->mTileType == TILE_TYPE_RAMP_L)aSpecialImage = &aImageBridgeRampL;
                            if(aTile->mTileType == TILE_TYPE_RAMP_R)aSpecialImage = &aImageBridgeRampR;
                        }
                        int aStampX = aTile->mGridX * aTileWidth - aStampShiftX;
                        int aStampY = aTile->mGridY * aTileHeight - aStampShiftY;
                        if (aTile->mTileType == TILE_TYPE_BLOCKED) {
                            if (aTile->mGridZ == 0) aStampY += aStampShiftCenterDown;
                            if (aTile->mGridZ == 2) aStampY += aStampShiftCenterUp;
                        }
                        if (aSpecialImage) {
                            aSaveImage.StampBlend(aSpecialImage, aStampX, aStampY);
                        } else if(aTileImage) {
                            aSaveImage.StampBlend(aTileImage, aStampX, aStampY);
                        }
                    }
                }
            }
        }
        FString aPath = gDirExport + "recent_map.png";
        if (aIter == 1) {
            aPath = gDirExport + "recent_map_xparent.png";
        }
        os_exportPNGImage(aSaveImage.mData, aPath.c(), aSaveImage.mWidth, aSaveImage.mHeight);
    }
}

