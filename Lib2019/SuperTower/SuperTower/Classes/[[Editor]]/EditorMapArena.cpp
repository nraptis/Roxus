//
//  EditorMapArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "EditorMapArena.hpp"
#include "MapGrid.hpp"

EditorMapArena *gEditor = 0;
EditorMapArena::EditorMapArena() {
    gEditor = this;
    mTileDepth = 1;
    mTileType = TILE_TYPE_NORMAL;
    mEditorMode = EDITOR_MODE_TILES;
    mPathStartMode = false;
    mPathSelectMode = false;

    mCurrentPath = 0;

    mGridOpacity = 0.0125f;


}

EditorMapArena::~EditorMapArena() {
    if (gEditor == this) {
        gEditor = 0;
    }
}

void EditorMapArena::Update() {
    
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

void EditorMapArena::Draw() {
    MapArena::Draw();
    EnumList(AnimatedLevelPath, aPath, mPathList) {
        aPath->DrawEditorMarkers();
    }

    if (mEditorMode == EDITOR_MODE_TILES) {
        for (int aGridX = 0;aGridX < mGrid->mTileGridWidthTotal;aGridX++) {
            for (int aGridY = 0;aGridY < mGrid->mTileGridHeightTotal;aGridY++) {
                if (mGrid->GetTile(aGridX, aGridY, mTileDepth) == 0) {
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
     MapTile *aTile = mTile[aDepth][aX][aY];
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

void EditorMapArena::AddPath() {
    AnimatedLevelPath *aPath = new AnimatedLevelPath();
    aPath->mStartX = mGrid->mTileGridBufferH;
    aPath->mStartY = mGrid->mTileGridBufferV + gRand.Get(mGrid->mTileGridHeightActive);
    aPath->mStartZ = 1;
    aPath->mEndX = mGrid->mTileGridBufferH + mGrid->mTileGridHeightActive - 1;
    aPath->mStartY = mGrid->mTileGridBufferV + gRand.Get(mGrid->mTileGridHeightActive);
    aPath->mStartZ = 1;
    mPathList += aPath;
    mCurrentPath = aPath;
    aPath->ComputePath(this);
}

void EditorMapArena::DeleteCurrentPath() {
    RemovePath(mCurrentPath);
}

void EditorMapArena::RemovePath(LevelPath *pPath) {
    if (pPath) {
        mPathList.Remove(pPath);
        //delete pPath;
        if(pPath == mCurrentPath)mCurrentPath = 0;
    }
}

void EditorMapArena::Click(float pX, float pY) {
    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;
    mGrid->GetEditorGridPos(pX, pY, aGridX, aGridY, aGridZ);

    if (aGridX == -1 || aGridY == -1 || aGridZ == -1) {
        mGrid->GetEditorGridPosAtDepth(pX, pY, mTileDepth, aGridX, aGridY);
        aGridZ = mTileDepth;
    }



    if (mEditorMode == EDITOR_MODE_PATH) {
        if (mPathSelectMode || mCurrentPath == 0) {
            mCurrentPath = AttemptPathSelect(pX, pY);
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
        mGrid->GetEditorGridPosAtDepth(pX, pY, mTileDepth, aGridX, aGridY);
        printf("Click [%d,%d] Depth[%d]\n", aGridX, aGridY, mTileDepth);
        if ((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGrid->mTileGridWidthTotal) && (aGridY < mGrid->mTileGridHeightTotal)) {
            MapTile *aTile = mGrid->GetTile(aGridX, aGridY, mTileDepth);
            if (aTile) {
                if (aTile->mTileType == mTileType) {
                    DeleteTile(aGridX, aGridY, mTileDepth);
                } else {
                    aTile->mTileType = mTileType;
                }
            } else {
                aTile = new MapTile();
                aTile->SetUp(aGridX, aGridY, mTileDepth);
                aTile->mTileType = mTileType;
                mGrid->mTile[mTileDepth][aGridX][aGridY] = aTile;
            }
            mGrid->RefreshUnitGridNodes();
        }
    }
    mGrid->ComputePathConnections();
    EnumList (AnimatedLevelPath, aPath, mPathList) {
        aPath->ComputePath(this);
    }
}

void EditorMapArena::DeleteTile(int pGridX, int pGridY, int pGridZ) {
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mGrid->mTileGridWidthTotal) && (pGridY < mGrid->mTileGridHeightTotal) && (pGridZ < GRID_DEPTH)) {


        mGrid->DeleteTile(pGridX, pGridY, pGridZ);


        //delete mGrid->mTile[pGridZ][pGridX][pGridY];
        //mGrid->mTile[pGridZ][pGridX][pGridY] = 0;
    }
}

void EditorMapArena::ExportMap() {
    FString aPath = "recent_map_data.xml";
    Save(aPath.c());
}

void EditorMapArena::ExportImage() {
    int aTileWidth = 144;
    int aTileHeight = 144;
    int aImageWidth = mGrid->mTileGridWidthTotal * aTileWidth;
    int aImageHeight = mGrid->mTileGridHeightTotal * aTileHeight;
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
            for (int aY=0;aY<mGrid->mTileGridHeightTotal;aY++) {
                for (int aX=0;aX<mGrid->mTileGridWidthTotal;aX++) {
                    MapTile *aTile = mGrid->mTile[aDepth][aX][aY];
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

