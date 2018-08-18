//
//  UnitPath.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/22/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "UnitPath.hpp"
#include "MapArena.hpp"
#include "FSpline.h"

UnitPath::UnitPath() {
    mStartX = -1;mStartY = -1;mStartZ = -1;
    mEndX = -1;mEndY = -1;mEndZ = -1;
    mLength = 0;
    mSize = 0;
    mPathX = 0;mPathY = 0;mPathZ = 0;
}

UnitPath::~UnitPath() {
    delete [] mPathX;
    mPathX = 0;
    mPathY = 0;
    mPathZ = 0;
    mLength = 0;
    mSize = 0;
}

void UnitPath::ComputePath(MapArena *pArena) {
    PathNode *aStartNode = pArena->GetGridNode(mStartX, mStartY, mStartZ);
    PathNode *aEndNode = pArena->GetGridNode(mEndX, mEndY, mEndZ);


    gArena->mUnitPathFinder.FindPath(aStartNode, aEndNode);
    PathNodeConnection *aConnection = gArena->mUnitPathFinder.mPathEnd;
    if (aConnection) {
        mLength = 0;
        while (aConnection) {
            aConnection = aConnection->mPathParent;
            mLength++;
        }
        if (mLength >= mSize) {
            delete [] mPathX;
            mSize = mLength + (mLength / 2) + 1;
            mPathX = new int[mSize * 3];
            mPathY = mPathX + mSize;
            mPathZ = mPathY + mSize;
        }
        int aIndex = mLength - 1;
        aConnection = gArena->mUnitPathFinder.mPathEnd;
        while (aConnection) {
            mPathX[aIndex] = aConnection->mNode->mGridX;
            mPathY[aIndex] = aConnection->mNode->mGridY;
            mPathZ[aIndex] = aConnection->mNode->mGridZ;

            aConnection = aConnection->mPathParent;
            aIndex--;
        }
    } else {
        mLength = 0;
    }
}

void UnitPath::DrawMarkers() {
    if (mLength >= 2) {
        int aStartDirX = mPathX[1] - mPathX[0];
        int aStartDirY = mPathY[1] - mPathY[0];
        int aPrevGridX = mPathX[0] - aStartDirX;
        int aPrevGridY = mPathY[0] - aStartDirY;
        int aPrevGridZ = mPathZ[0];
        int aGridX = 0;
        int aGridY = 0;
        int aGridZ = 0;
        for (int i=0;i<mLength;i++) {
            aGridX = mPathX[i];
            aGridY = mPathY[i];
            aGridZ = mPathZ[i];

            float aPreviousCenterX = gArena->GetUnitGridX(aPrevGridX, aPrevGridY, aPrevGridZ);
            float aPreviousCenterY = gArena->GetUnitGridY(aPrevGridX, aPrevGridY, aPrevGridZ);
            
            float aCenterX = gArena->GetUnitGridX(aGridX, aGridY, aGridZ);
            float aCenterY = gArena->GetUnitGridY(aGridX, aGridY, aGridZ);

            Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.75f);
            Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 2.0f);
            Graphics::SetColor(0.95f, 0.95f, 0.45f, 1.0f);
            Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 1.0f);

            aPrevGridX = aGridX;
            aPrevGridY = aGridY;
            aPrevGridZ = aGridZ;
        }

        for (int i=0;i<mLength;i++) {
            aGridX = mPathX[i];
            aGridY = mPathY[i];
            aGridZ = mPathZ[i];
            float aCenterX = gArena->GetUnitGridX(aGridX, aGridY, aGridZ);
            float aCenterY = gArena->GetUnitGridY(aGridX, aGridY, aGridZ);
            if (gApp->mDarkMode) {
                Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.125f);
            } else {
                Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.625f);
            }
            Graphics::DrawPoint(aCenterX, aCenterY, 5.0f);
            if (gApp->mDarkMode) {
                Graphics::SetColor(0.25f, 0.85f, 0.25f, 0.125f);
            } else {
                Graphics::SetColor(0.25f, 0.85f, 0.25f, 0.625f);
            }
            Graphics::DrawPoint(aCenterX, aCenterY, 3.0f);
        }
    }

    float aX1 = gArena->GetUnitGridX(mStartX, mStartY, mStartZ);
    float aY1 = gArena->GetUnitGridY(mStartX, mStartY, mStartZ);
    float aX2 = gArena->GetUnitGridX(mEndX, mEndY, mEndZ);
    float aY2 = gArena->GetUnitGridY(mEndX, mEndY, mEndZ);

    if (mLength < 2) {
        if (gApp->mDarkMode) {
            Graphics::SetColor(0.75f, 0.75f, 0.125f, 0.15f);
        } else {
            Graphics::SetColor(0.75f, 0.75f, 0.125f, 0.75f);
        }
        Graphics::DrawLine(aX1, aY1, aX2, aY2, 8.0f);
    }

    if (gApp->mDarkMode) {
        Graphics::SetColor(0.125f, 0.125f, 0.125f, 0.25f);
    } else {
        Graphics::SetColor();
    }

    Graphics::SetColor(0.25f);

    gApp->mUnitCircleHard.Center(aX1, aY1);
    gApp->mUnitCircleHard.Center(aX2, aY2);

    Graphics::SetColor();
    
}

void UnitPath::Reset() {
    mStartX = -1;mStartY = -1;mStartZ = -1;
    mEndX = -1;mEndY = -1;mEndZ = -1;
    mLength = 0;
}

void UnitPath::CloneFrom(UnitPath *pPath) {
    Reset();
    if (pPath) {
        if (pPath->mLength > mSize) {
            delete [] mPathX;
            mSize = pPath->mLength;
            mPathX = new int[mSize * 3];
            mPathY = mPathX + mSize;
            mPathZ = mPathY + mSize;
        }
        mLength = pPath->mLength;
        for (int i=0;i<mLength;i++) {
            mPathX[i] = pPath->mPathX[i];
            mPathY[i] = pPath->mPathY[i];
            mPathZ[i] = pPath->mPathZ[i];
        }
        mStartX = pPath->mStartX;mStartY = pPath->mStartY;mStartZ = pPath->mStartZ;
        mEndX = pPath->mEndX;mEndY = pPath->mEndY;mEndZ = pPath->mEndZ;
    }
}

int UnitPath::GetIndexOfGridPosition(int pGridX, int pGridY, int pGridZ) {
    int aResult = -1;
    for (int i=0;i<mLength;i++) {
        if (mPathX[i] == pGridX &&
            mPathY[i] == pGridY &&
            mPathZ[i] == pGridZ) {
            aResult = i;
            break;
        }
    }
    return aResult;
}
