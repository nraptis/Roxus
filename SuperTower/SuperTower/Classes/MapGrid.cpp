//
//  MapGrid.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "MapGrid.hpp"
#include "MapArena.hpp"
#include "Tower.hpp"

MapGrid *gGrid = NULL;

MapGrid::MapGrid() {
    gGrid = this;

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
    mTileOpacity[2] = 0.75f;

    mUnitGrid = NULL;
    mUnitGridBase = NULL;
    mWalkAllowed = NULL;

    mUnitGridWidth = 0;
    mUnitGridHeight = 0;

}

MapGrid::~MapGrid() {

}

void MapGrid::Update() {

    if (mDeletedTileList.mCount > 0) {
        EnumList(MapTile, aTile, mDeletedTileList) {
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
}

void MapGrid::DrawAllNodes() {
    if (gApp->mDarkMode) return;
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];
                if (aNode->mBlocked == false) {
                    Graphics::SetColor(0.025f, 0.025f, 0.025f, mTileOpacity[aDepth]);
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
                    if (aNode->mOccupiedByUnit) {
                        Graphics::SetColor(0.45f, 0.25f, 0.22f, mTileOpacity[aDepth]);
                    }
                    Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 1.5f);
                }
            }
        }
    }
    Graphics::SetColor();
}

void MapGrid::DrawOccupiedNodes() {
    float aShift = gTileSize2 / ((float)SUBDIVISIONS_PER_TILE);
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                PathNode *aNode = mUnitGrid[aDepth][aGridX][aGridY];


                float aRed = 0.0f;
                float aGreen = 0.0f;
                float aBlue = 0.0f;

                if (aNode->mBlocked == false) {
                if (aNode->mOccupiedByItem || aNode->mOccupiedByUnit || aNode->mOccupiedByTower) {

                    if (aNode->mOccupiedByItem) {
                        aBlue = 0.75f;
                    }

                    if (aNode->mOccupiedByTower) {
                        aRed = 0.75f;
                    }

                    if (aNode->mOccupiedByUnit) {
                        aGreen = 0.75f;
                    }

                    Graphics::SetColor(aRed, aGreen, aBlue, 0.85f);

                        float aCX = aNode->mCenterX;
                        float aCY = aNode->mCenterY;
                        Graphics::DrawLine(aCX - aShift, aCY - aShift, aCX + aShift, aCY + aShift);
                        Graphics::DrawLine(aCX + aShift, aCY - aShift, aCX - aShift, aCY + aShift);
                    }
                }
            }
        }
    }

}

void MapGrid::DrawOccupiedTiles() {
    if (gApp->mDarkMode) { return; }
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {

        if (aDepth == 0)Graphics::SetColor(0.065f, 0.65f, 0.065f, 0.85f);
        if (aDepth == 1)Graphics::SetColor(0.65f, 0.065f, 0.065f, 0.85f);
        if (aDepth == 2)Graphics::SetColor(0.65f, 0.65f, 0.065f, 0.85f);


        for (int aGridX=0;aGridX<mTileGridWidthTotal;aGridX++) {
            for (int aGridY=0;aGridY<mTileGridHeightTotal;aGridY++) {
                MapTile *aTile1 = mTile[aDepth][aGridX][aGridY];
                if (aTile1) {
                    if (aTile1->mOccupiedByTower) {
                        Graphics::DrawLine(aTile1->mCenterX - gTileSize2, aTile1->mCenterY - gTileSize2, aTile1->mCenterX + gTileSize2, aTile1->mCenterY + gTileSize2, 2.0);

                        Graphics::DrawLine(aTile1->mCenterX + gTileSize2, aTile1->mCenterY - gTileSize2, aTile1->mCenterX - gTileSize2, aTile1->mCenterY + gTileSize2, 2.0);
                    }

                    for (int i=0;i<aTile1->mPathConnectionCount;i++) {
                        //PathNode *aConnectedNode = aTile1->mPathConnection[i].mNode;
                        //Graphics::DrawArrow(aTile1->mCenterX, aTile1->mCenterY, aConnectedNode->mCenterX, aConnectedNode->mCenterY);
                    }
                }
            }
        }
    }
    Graphics::SetColor();
}

void MapGrid::DrawAllConnections() {
    if (gApp->mDarkMode) { return; }
    Graphics::SetColor(0.75f, 0.125f, 0.125f, 0.85f);

    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
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
                        Graphics::DrawArrow(aX1, aY1, aX2, aY2, 4.0f, 0.5f);
                    }
                }
            }
        }
    }
    Graphics::SetColor();
}

void MapGrid::DrawLevelPathConnections() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        if (gApp->mDarkMode) {
            Graphics::SetColorSwatch(aDepth, 0.075f);
        } else {
            Graphics::SetColorSwatch(aDepth, 0.5f);
        }
        for (int aGridX=0;aGridX<mTileGridWidthTotal;aGridX++) {
            for (int aGridY=0;aGridY<mTileGridHeightTotal;aGridY++) {
                MapTile *aTile1 = mTile[aDepth][aGridX][aGridY];
                if (aTile1) {
                    for (int i=0;i<aTile1->mPathConnectionCount;i++) {
                        PathNode *aConnectedNode = aTile1->mPathConnection[i].mNode;
                        Graphics::DrawArrow(aTile1->mCenterX, aTile1->mCenterY, aConnectedNode->mCenterX, aConnectedNode->mCenterY);
                    }
                }
            }
        }
    }
}

void MapGrid::SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {

    ClearGrid();

    mTileGridBufferH = pGridBufferH;
    mTileGridBufferV = pGridBufferV;
    mTileGridWidthActive = pWidth;
    mTileGridHeightActive = pHeight;
    mTileGridWidthTotal = mTileGridWidthActive + mTileGridBufferH * 2;
    mTileGridHeightTotal = mTileGridHeightActive + mTileGridBufferV * 2;
    mTile = new MapTile***[GRID_DEPTH];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mTile[aDepth] = new MapTile**[mTileGridWidthTotal];
        for (int aX=0;aX<mTileGridWidthTotal;aX++) {
            mTile[aDepth][aX] = new MapTile*[mTileGridHeightTotal];
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

    //mTilePathFinder.SetLookupTableSize(mTileGridWidthTotal, mTileGridHeightTotal, GRID_DEPTH);

    GenerateUnitGrid();
}

void MapGrid::ClearGrid() {
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


    //mWalkAllowed = new bool**[]


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
        mUnitGridBase = NULL;


        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int i=0;i<mUnitGridWidth;i++) { delete [] mWalkAllowed[aDepth][i]; }
            delete [] mWalkAllowed[aDepth];
        }
        delete [] mWalkAllowed;
        mWalkAllowed = NULL;


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

void MapGrid::Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV) {
    SizeGrid(pWidth, pHeight, pGridBufferH, pGridBufferV);
    int aDepth = 1;
    for (int aX=0;aX<mTileGridWidthActive;aX++) {
        for (int aY=0;aY<mTileGridHeightActive;aY++) {
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV] = new MapTile();
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV]->SetUp(aX + mTileGridBufferH, aY + mTileGridBufferV, aDepth);
        }
    }
    for (int aX = 0;aX < mTileGridWidthActive;aX++) {
        for (int aY=0;aY<mTileGridHeightActive;aY++) {
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV] = new MapTile();
            mTile[aDepth][aX + mTileGridBufferH][aY + mTileGridBufferV]->SetUp(aX + mTileGridBufferH, aY + mTileGridBufferV, aDepth);
        }
    }
    aDepth = 0;
    for (int aX = 0;aX < mTileGridWidthTotal;aX++) {
        for (int aY = 0;aY < mTileGridHeightTotal;aY++) {
            if (aX < mTileGridBufferH || aY < mTileGridBufferV || aX >= (mTileGridBufferH + mTileGridWidthActive) || aY >= (mTileGridBufferV + mTileGridHeightActive)) {
                mTile[aDepth][aX][aY] = new MapTile();
                mTile[aDepth][aX][aY]->SetUp(aX, aY, aDepth);
            }
        }
    }
    ComputeTowerAllowedPlacements();
    ComputePathConnections();
}

void MapGrid::GenerateUnitGrid() {


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

    printf("Tile Grid = [%d x %d x %x]\n", GRID_DEPTH, mTileGridWidthTotal, mTileGridHeightTotal);
    printf("Unit Grid = [%d x %d x %x]\n", GRID_DEPTH, mUnitGridWidth, mUnitGridHeight);

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

    mWalkAllowed = new bool**[mUnitGridWidth];
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        mWalkAllowed[aDepth] = new bool*[mUnitGridWidth];
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            mWalkAllowed[aDepth][aGridX] = new bool[mUnitGridHeight];
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                mWalkAllowed[aDepth][aGridX][aGridY] = NULL;
            }
        }
    }

    RefreshUnitGridNodes();
    ComputePathConnections();
}

void MapGrid::ClearWalkableChunk(int pGridX, int pGridY, int pGridZ, int pRingSize) {

    float aStartX = pGridX - pRingSize;
    float aStartY = pGridY - pRingSize;
    float aEndX = pGridX + (pRingSize + 1);
    float aEndY = pGridY + (pRingSize + 1);

    if (aStartX < 0) { aStartX = 0; }

    if (aStartY < 0) { aStartY = 0; }

    if (aEndX > mUnitGridWidth) {
        aEndX = mUnitGridWidth;
    }

    if (aEndY > mUnitGridHeight) {
        aEndY = mUnitGridHeight;
    }

    PathNode *aNode = NULL;
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {

                aNode = mUnitGrid[aDepth][aGridX][aGridY];
                //if (aNode->mOccupied)



                mWalkAllowed[aDepth][aGridX][aGridY] = false;
            }
        }
    }

}

void MapGrid::ClearTiles(int pDepth) {
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

void MapGrid::ClearTiles() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        ClearTiles(aDepth);
    }
}

void MapGrid::Flood(int pDepth) {
    if (pDepth >= 0 && pDepth < GRID_DEPTH) {
        ClearTiles(pDepth);
        for (int aGridX=0;aGridX<mTileGridWidthTotal;aGridX++) {
            for (int aGridY=0;aGridY<mTileGridHeightTotal;aGridY++) {
                //mTile[pDepth][
                MapTile *aTile = new MapTile();
                mTile[pDepth][aGridX][aGridY] = aTile;
                aTile->mTileType = TILE_TYPE_NORMAL;
                aTile->SetUp(aGridX, aGridY, pDepth);
            }
        }
        RefreshUnitGridNodes();
    }
}

void MapGrid::IncreaseBuffer() {

}

void MapGrid::DecreaseBuffer() {

}

void MapGrid::IncreaseWidth() {

}

void MapGrid::DecreaseWidth() {

}

void MapGrid::IncreaseHeight() {

}

void MapGrid::DecreaseHeight() {

}

//Get the closest valid node to a particular screen location....
//There is one rule always enforce - the node must be on a TILE...
PathNode *MapGrid::GetClosestNode(float pX, float pY, bool pAllowBlocked, bool pAllowOccupied, bool pAllowRamps) {

    PathNode *aClosestNode = NULL;
    float aBestDist = 100.0f * 100.0f;
    int aGridX = -1;
    int aGridY = -1;
    int aGridZ = -1;

    GetEditorGridPos(pX, pY, aGridX, aGridY, aGridZ);
    MapTile *aTile = GetTile(aGridX, aGridY, aGridZ);

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
        if (pAllowOccupied == true || (aClosestNode->mOccupiedByTower == false && aClosestNode->mOccupiedByItem == false && aClosestNode->mOccupiedByUnit == false)) {

        } else {
            aClosestNode = NULL;
        }
    }
    return aClosestNode;
}

void MapGrid::GetGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ) {
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
        MapTile *aTile = 0;
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

void MapGrid::GetEditorGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ) {
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
        MapTile *aTile = 0;
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

void MapGrid::GetEditorGridPosAtDepth(float pX, float pY, int pDepth, int &pGridX, int &pGridY) {
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



//This will assign nodes to tiles, compute node positions, and figure out which
//nodes are "blocked" by default...
void MapGrid::RefreshUnitGridNodes() {
    PathNode *aNode = 0;
    //Step 1: UNBLOCK all of the grid nodes...
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aGridX=0;aGridX<mUnitGridWidth;aGridX++) {
            for (int aGridY=0;aGridY<mUnitGridHeight;aGridY++) {
                aNode = mUnitGridBase[aDepth][aGridX][aGridY];
                aNode->HardReset();
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
                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {

                    if (aTile->mTileType == TILE_TYPE_RAMP_U) {
                        MapTile *aTileU      = GetTile(aTileGridX, aTileGridY - 1, aDepth    );
                        MapTile *aTileBelowU = GetTile(aTileGridX, aTileGridY - 1, aDepth - 1);

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
                        MapTile *aTileR      = GetTile(aTileGridX + 1, aTileGridY    , aDepth    );
                        MapTile *aTileBelowR = GetTile(aTileGridX + 1, aTileGridY    , aDepth - 1);

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
                        MapTile *aTileD      = GetTile(aTileGridX    , aTileGridY + 1, aDepth    );
                        MapTile *aTileBelowD = GetTile(aTileGridX    , aTileGridY + 1, aDepth - 1);

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
                        MapTile *aTileL      = GetTile(aTileGridX - 1, aTileGridY    , aDepth    );
                        MapTile *aTileBelowL = GetTile(aTileGridX - 1, aTileGridY    , aDepth - 1);

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
                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
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

                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
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
                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    MapTile *aTileU = GetTile(aTileGridX    , aTileGridY - 1, aDepth);
                    MapTile *aTileR = GetTile(aTileGridX + 1, aTileGridY    , aDepth);
                    MapTile *aTileD = GetTile(aTileGridX    , aTileGridY + 1, aDepth);
                    MapTile *aTileL = GetTile(aTileGridX - 1, aTileGridY    , aDepth);
                    MapTile *aTileUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth);
                    MapTile *aTileUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth);
                    MapTile *aTileDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth);
                    MapTile *aTileDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth);
                    MapTile *aTileAboveUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth + 1);
                    MapTile *aTileAboveUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth + 1);
                    MapTile *aTileAboveDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth + 1);
                    MapTile *aTileAboveDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth + 1);
                    MapTile *aTileBelowUL = GetTile(aTileGridX - 1, aTileGridY - 1, aDepth - 1);
                    MapTile *aTileBelowUR = GetTile(aTileGridX + 1, aTileGridY - 1, aDepth - 1);
                    MapTile *aTileBelowDL = GetTile(aTileGridX - 1, aTileGridY + 1, aDepth - 1);
                    MapTile *aTileBelowDR = GetTile(aTileGridX + 1, aTileGridY + 1, aDepth - 1);
                    MapTile *aTileAboveU = GetTile(aTileGridX    , aTileGridY - 1, aDepth + 1);
                    MapTile *aTileAboveR = GetTile(aTileGridX + 1, aTileGridY    , aDepth + 1);
                    MapTile *aTileAboveD = GetTile(aTileGridX    , aTileGridY + 1, aDepth + 1);
                    MapTile *aTileAboveL = GetTile(aTileGridX - 1, aTileGridY    , aDepth + 1);
                    MapTile *aTileBelowU = GetTile(aTileGridX    , aTileGridY - 1, aDepth - 1);
                    MapTile *aTileBelowR = GetTile(aTileGridX + 1, aTileGridY    , aDepth - 1);
                    MapTile *aTileBelowD = GetTile(aTileGridX    , aTileGridY + 1, aDepth - 1);
                    MapTile *aTileBelowL = GetTile(aTileGridX - 1, aTileGridY    , aDepth - 1);
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

void MapGrid::ComputePathConnections() {
    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mTileGridWidthTotal;aX++) {
            for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                MapTile *aTile = mTile[aDepth][aX][aY];
                if (aTile) {
                    aTile->PathReset();
                }
            }
        }
    }


    EnumList(Tower, aTower, gArena->mTowerCollection.mObjectList) {
        if (aTower->mKill == 0) {
            MapTile *aTowerTile = GetTile(aTower->mGridX, aTower->mGridY, MAIN_FLOOR);
            if (aTowerTile) {
                aTowerTile->mOccupiedByTower = true;
            }
        }
    }

#define PATH_COST_ADJ 100
#define PATH_COST_DIA 141
#define PATH_COST_RAMP 100

    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aX=0;aX<mTileGridWidthTotal;aX++) {
            for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                MapTile *aTile = GetTile(aX, aY, aDepth);
                if (aTile) {
                    if (aTile->IsBlocked() == false) {
                        MapTile *aTileU = GetTile(aX, aY - 1, aDepth);
                        MapTile *aTileD = GetTile(aX, aY + 1, aDepth);
                        MapTile *aTileL = GetTile(aX - 1, aY, aDepth);
                        MapTile *aTileR = GetTile(aX + 1, aY, aDepth);
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

                            MapTile *aTileUR = GetTile(aX + 1, aY - 1, aDepth);
                            MapTile *aTileUL = GetTile(aX - 1, aY - 1, aDepth);
                            MapTile *aTileDR = GetTile(aX + 1, aY + 1, aDepth);
                            MapTile *aTileDL = GetTile(aX - 1, aY + 1, aDepth);

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
                        MapTile *aLowerTileU = GetTile(aX, aY - 1, aDepth - 1);
                        MapTile *aLowerTileD = GetTile(aX, aY + 1, aDepth - 1);
                        MapTile *aLowerTileL = GetTile(aX - 1, aY, aDepth - 1);
                        MapTile *aLowerTileR = GetTile(aX + 1, aY, aDepth - 1);

                        if (aTile->mTileType == TILE_TYPE_RAMP_U) {
                            if (aLowerTileU) {
                                if (aLowerTileU->IsBlocked() == false) {
                                    aTile->ConnectTo(aLowerTileU, PATH_COST_RAMP);
                                    aLowerTileU->ConnectTo(aTile, PATH_COST_RAMP);
                                }
                            }

                            //Special case, double ramp... (impractical, but necessary for completion)...
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

    EnumList (AnimatedLevelPath, aPath, gArena->mPathList) {
        aPath->ComputePath(gArena);
    }

    ResetGridConnections();
    ComputeGridConnections();
}


void MapGrid::ResetGridConnections() {

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
                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile != 0 && aTile->mOccupiedByTower == true) {
                    int aStartGridY = aTileGridY * SUBDIVISIONS_PER_TILE;
                    for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
                        int aGridX = aStartGridX + aOffsetX;
                        for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                            int aGridY = aStartGridY + aOffsetY;
                            aNode = mUnitGrid[aDepth][aGridX][aGridY];
                            aNode->mOccupiedByTower = true;
                        }
                    }
                }
            }
        }
    }
}

void MapGrid::ComputeGridConnections() {

    //Link up nodes internally among tiles...

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
                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
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
                                if (aNodeU != NULL && aNodeL != NULL) {
                                    if (aNodeU->IsBlocked() == false && aNodeL->IsBlocked() == false) {
                                        aNode->ConnectTo(aNodeUL, PATH_COST_DIA);
                                    }
                                }
                            }

                            if(aNodeUR != 0 && aNodeUR->IsBlocked() == false) {
                                if (aNodeU != NULL && aNodeR != NULL) {
                                    if (aNodeU->IsBlocked() == false && aNodeR->IsBlocked() == false) {
                                        aNode->ConnectTo(aNodeUR, PATH_COST_DIA);
                                    }
                                }
                            }

                            if(aNodeDR != 0 && aNodeDR->IsBlocked() == false) {
                                if (aNodeD != NULL && aNodeR != NULL) {
                                    if (aNodeD->IsBlocked() == false && aNodeR->IsBlocked() == false) {
                                        aNode->ConnectTo(aNodeDR, PATH_COST_DIA);
                                    }
                                }
                            }

                            if(aNodeDL != 0 && aNodeDL->IsBlocked() == false) {
                                if (aNodeD != NULL && aNodeL != NULL) {
                                    if (aNodeD->IsBlocked() == false && aNodeL->IsBlocked() == false) {
                                        aNode->ConnectTo(aNodeDL, PATH_COST_DIA);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

PathNode *MapGrid::GetGridNode(int pGridX, int pGridY, int pGridZ) {
    PathNode *aResult = 0;
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mUnitGridWidth) && (pGridY < mUnitGridHeight) && (pGridZ < GRID_DEPTH)) {
        aResult = mUnitGrid[pGridZ][pGridX][pGridY];
    }
    return aResult;
}

float MapGrid::GetUnitGridX(int pGridX, int pGridY, int pGridZ) {
    float aResult = 0.0f;
    if (pGridX >= 0 && pGridX < mUnitGridWidth && pGridY >= 0 && pGridY < mUnitGridHeight && pGridZ >= 0 && pGridZ < GRID_DEPTH) {
        PathNode *aNode = mUnitGrid[pGridZ][pGridX][pGridY];
        aResult = aNode->mCenterX;
    }
    return aResult;
}

float MapGrid::GetUnitGridY(int pGridX, int pGridY, int pGridZ) {
    float aResult = 0.0f;
    if (pGridX >= 0 && pGridX < mUnitGridWidth && pGridY >= 0 && pGridY < mUnitGridHeight && pGridZ >= 0 && pGridZ < GRID_DEPTH) {
        PathNode *aNode = mUnitGrid[pGridZ][pGridX][pGridY];
        aResult = aNode->mCenterY;
    }
    return aResult;
}

bool MapGrid::UnitGridPositionsAreAdjacent(int pGridX1, int pGridY1, int pGridZ1, int pGridX2, int pGridY2, int pGridZ2) {
    if (pGridX1 >= 0 && pGridX1 < mUnitGridWidth && pGridY1 >= 0 && pGridY1 < mUnitGridHeight && pGridZ1 >= 0 && pGridZ1 < GRID_DEPTH &&
        pGridX2 >= 0 && pGridX2 < mUnitGridWidth && pGridY2 >= 0 && pGridY2 < mUnitGridHeight && pGridZ2 >= 0 && pGridZ2 < GRID_DEPTH) {
        int aDiffX = pGridX2 - pGridX1;
        int aDiffY = pGridY2 - pGridY1;
        int aDiffZ = pGridZ2 - pGridZ1;
        if (aDiffX >= -1 && aDiffX <= 1 &&
            aDiffY >= -1 && aDiffY <= 1 &&
            aDiffZ >= -1 && aDiffZ <= 1) {
            return true;
        }
    }
    return false;
}

bool MapGrid::UnitGridPositionsAreAdjacentAndNotEqual(int pGridX1, int pGridY1, int pGridZ1, int pGridX2, int pGridY2, int pGridZ2) {
    if (UnitGridPositionsAreAdjacent(pGridX1, pGridY1, pGridZ1, pGridX2, pGridY2, pGridZ2)) {
        int aDiffX = pGridX2 - pGridX1;
        int aDiffY = pGridY2 - pGridY1;
        int aDiffZ = pGridZ2 - pGridZ1;
        if (aDiffX == 0 && aDiffY == 0 && aDiffZ == 0) { return false; }
        return true;
    }
    return false;
}

FRect MapGrid::GetRectForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ) {
    float aNodeWidth = gTileSize / ((float)SUBDIVISIONS_PER_TILE);
    FRect aResult = FRect(0.0f, 0.0f, aNodeWidth, aNodeWidth);
    PathNode *aNode = GetGridNode(pUnitGridX, pUnitGridY, pUnitGridZ);
    if (aNode) {
        aResult.mX = aNode->mCenterX - aNodeWidth / 2.0f;
        aResult.mY = aNode->mCenterY - aNodeWidth / 2.0f;
    }
    return aResult;
}

MapTile *MapGrid::GetTile(int pGridX, int pGridY, int pGridZ) {
    MapTile *aResult = 0;
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridZ >= 0) && (pGridX < mTileGridWidthTotal) && (pGridY < mTileGridHeightTotal) && (pGridZ < GRID_DEPTH)) {
        aResult = mTile[pGridZ][pGridX][pGridY];
    }
    return aResult;
}

void MapGrid::DeleteTile(int pGridX, int pGridY, int pGridZ) {
    MapTile *aTile = GetTile(pGridX, pGridY, pGridZ);
    if (aTile != NULL) {
        mDeletedTileList += aTile;
        mTile[pGridZ][pGridX][pGridY] = 0;
    }
}

bool MapGrid::IsNodeOnTile(PathNode *pNode, MapTile *pTile) {
    if (pNode != NULL && pTile != NULL) {
        for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
            for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                if (pTile->mGrid[aOffsetX][aOffsetY] == pNode) {
                    return true;
                }
            }
        }
    }
    return false;
}

PathNode *MapGrid::GetEndNodeForTile(MapTile *pTile) {
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

//If there are multiple tiles for a particular node, we get all of the tiles
// (max of 2) for the given node...
void MapGrid::GetAllTilesForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ, FList *pList) {
    if (pUnitGridX >= 0 && pUnitGridX < mUnitGridWidth && pUnitGridY >= 0 && pUnitGridY < mUnitGridHeight) {
        PathNode *aNode = GetGridNode(pUnitGridX, pUnitGridY, pUnitGridZ);
        //Basically... Ignore Z and scan through the whole pancake stack of tiles
        //on this position to see which ones contain the node
        if (aNode != NULL && pList != NULL) {
            int aTileGridX = pUnitGridX / SUBDIVISIONS_PER_TILE;
            int aTileGridY = pUnitGridY / SUBDIVISIONS_PER_TILE;
            for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
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

//Used when we deploy a group, so that there are not collisions on the end-tile...
void MapGrid::UnblockAllNodesForTile(MapTile *pTile) {
    if (pTile != NULL) {
        PathNode *aNode = 0;
        int aStartGridX = pTile->mGridX * SUBDIVISIONS_PER_TILE;
        int aStartGridY = pTile->mGridY * SUBDIVISIONS_PER_TILE;
        int aGridZ = pTile->mGridZ;
        for (int aOffsetX=0;aOffsetX<=SUBDIVISIONS_PER_TILE;aOffsetX++) {
            int aGridX = aStartGridX + aOffsetX;
            for (int aOffsetY=0;aOffsetY<=SUBDIVISIONS_PER_TILE;aOffsetY++) {
                int aGridY = aStartGridY + aOffsetY;
                aNode = GetGridNode(aGridX, aGridY, aGridZ);
                if (aNode != NULL) {
                    aNode->Unblock();
                }
            }
        }
    }
}

PathNode *MapGrid::GetEndNodeForPath(LevelPath *pPath) {
    PathNode *aResult = 0;
    MapTile *aEndTile = GetEndTileForPath(pPath);
    if (aEndTile) {
        aResult = GetEndNodeForTile(aEndTile);
    }
    return aResult;
}

PathNode *MapGrid::GetStartNodeForPath(LevelPath *pPath) {
    PathNode *aResult = 0;

    DumpLevelPathToTileList(pPath);

    MapTile *aStartTile = 0;
    PathNode *aNode = 0;

    int aTileIndex = 0;
    while (aTileIndex < mTileList.mCount - 1) {
        MapTile *aTile = (MapTile *)(mTileList.Fetch(aTileIndex));
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

void MapGrid::DumpLevelPathToTileList(LevelPath *pPath) {
    mTileList.RemoveAll();
    if (pPath) {
        MapTile *aStartTile = GetTile(pPath->mStartX, pPath->mStartY, pPath->mStartZ);
        if (aStartTile) {
            mTileList.Add(aStartTile);
        }
        int aCap = (pPath->mLength-1);
        for (int i=1;i<aCap;i++) {
            MapTile *aTile = GetTile(pPath->mPathX[i], pPath->mPathY[i], pPath->mPathZ[i]);
            if (aTile) {
                mTileList.Add(aTile);
            }
        }
        MapTile *aEndTile = GetTile(pPath->mEndX, pPath->mEndY, pPath->mEndZ);
        if (aEndTile) {
            mTileList.Add(aEndTile);
        }
    }
}

MapTile *MapGrid::GetEndTileForPath(LevelPath *pPath) {
    MapTile *aResult = NULL;
    if (pPath) {
        aResult = GetTile(pPath->mEndX, pPath->mEndY, pPath->mEndZ);
    }
    return aResult;
}

MapTile *MapGrid::GetStartTileForPath(LevelPath *pPath) {
    MapTile *aResult = NULL;
    if (pPath) {
        aResult = GetTile(pPath->mStartX, pPath->mStartY, pPath->mStartZ);
    }
    return aResult;
}

void MapGrid::ComputeTowerAllowedPlacements() {
    int aMaxX = mTileGridBufferH + mTileGridWidthActive;
    int aMaxY = mTileGridBufferV + mTileGridHeightActive;
    MapTile *aTile = 0;
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

void MapGrid::Save(FXMLTag *pTag) {
    if (pTag != NULL) {
        pTag->AddParam("grid_width_active", FString(mTileGridWidthActive).c());
        pTag->AddParam("grid_height_active", FString(mTileGridHeightActive).c());
        pTag->AddParam("grid_buffer_h", FString(mTileGridBufferH).c());
        pTag->AddParam("grid_buffer_v", FString(mTileGridBufferV).c());

        FXMLTag *aTileListTag = new FXMLTag("tile_list");
        *pTag += aTileListTag;

        for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
            for (int aX=0;aX<mTileGridWidthTotal;aX++) {
                for (int aY=0;aY<mTileGridHeightTotal;aY++) {
                    if (mTile[aDepth][aX][aY]) {
                        *aTileListTag += mTile[aDepth][aX][aY]->Save();
                    }
                }
            }
        }
    }
}

void MapGrid::Load(FXMLTag *pTag) {
    if (pTag != NULL) {
        int aTileGridWidthActive = FString(pTag->GetParamValue("grid_width_active")).ToInt();
        int aTileGridHeightActive = FString(pTag->GetParamValue("grid_height_active")).ToInt();
        int aTileGridBufferH = FString(pTag->GetParamValue("grid_buffer_h")).ToInt();
        int aTileGridBufferV = FString(pTag->GetParamValue("grid_buffer_v")).ToInt();
        int aTileGridWidthTotal = aTileGridWidthActive + aTileGridBufferH * 2;
        int aTileGridHeightTotal = aTileGridHeightActive + aTileGridBufferV * 2;
        if (aTileGridWidthTotal > 0 && aTileGridHeightTotal > 0) {
            SizeGrid(aTileGridWidthActive, aTileGridHeightActive, aTileGridBufferH, aTileGridBufferV);
            EnumTagsMatching (pTag, aTileListTag, "tile_list") {
                EnumTags (aTileListTag, aTileTag) {
                    MapTile *aTile = new MapTile();
                    aTile->Load(aTileTag);
                    if (aTile->mGridX >= 0 && aTile->mGridY >= 0 && aTile->mGridZ >=0 && aTile->mGridX < mTileGridWidthTotal && aTile->mGridY < mTileGridHeightTotal && aTile->mGridZ < GRID_DEPTH) {
                        mTile[aTile->mGridZ][aTile->mGridX][aTile->mGridY] = aTile;
                    }
                }
            }

            /*
             int aPathIndex = 1;
             EnumTagsMatching (pTag, aPathListTag, "path_list") {
             EnumTags (aPathListTag, aPathTag) {
             AnimatedLevelPath *aPath = new AnimatedLevelPath();
             aPath->Load(aPathTag);
             mPathList += aPath;

             aPath->mName = FString("level_path_") + FString(aPathIndex);
             aPathIndex += 1;
             }
             }
             */
            
        }
    }

    for (int aDepth=0;aDepth<GRID_DEPTH;aDepth++) {
        for (int aTileGridX=0;aTileGridX<mTileGridWidthTotal;aTileGridX++) {
            for (int aTileGridY=0;aTileGridY<mTileGridHeightTotal;aTileGridY++) {
                MapTile *aTile = GetTile(aTileGridX, aTileGridY, aDepth);
                if (aTile) {
                    if (aTile->mTileType == TILE_TYPE_BLOCKED) {
                        aTile->mBlocked = true;
                    }
                }
            }
        }
    }

    

}

