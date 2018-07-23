//
//  UnitPath.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/22/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "UnitPath.hpp"
#include "GameArena.h"
#include "FSpline.h"

UnitPath::UnitPath() {
    mStartX = 0;
    mStartY = 0;
    mStartZ = 1;
    mEndX = 0;
    mEndY = 0;
    mEndZ = 1;
    mLength = 0;
    mSize = 0;
    mPathX = 0;
    mPathY = 0;
    mPathZ = 0;
}

UnitPath::~UnitPath() {
    delete [] mPathX;
    mPathX = 0;
    mPathY = 0;
    mPathZ = 0;
    mLength = 0;
    mSize = 0;
}

void UnitPath::ComputePath(GameArena *pArena) {

    PathNode *aStartNode = pArena->GetGridNode(mStartX, mStartY, mStartZ);
    PathNode *aEndNode = pArena->GetGridNode(mEndX, mEndY, mEndZ);
    mPathFinder.FindPath(aStartNode, aEndNode);
    PathNodeConnection *aConnection = mPathFinder.mPathEnd;
    if (aConnection) {
        mLength = 0;
        while (aConnection) {
            aConnection = aConnection->mParent;
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
        aConnection = mPathFinder.mPathEnd;
        while (aConnection) {
            mPathX[aIndex] = aConnection->mNode->mGridX;
            mPathY[aIndex] = aConnection->mNode->mGridY;
            mPathZ[aIndex] = aConnection->mNode->mGridZ;
            aConnection = aConnection->mParent;
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
            float aCenterY = gArena->GetUnitGridY(aGridY, aGridY, aGridZ);

                Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.15f);
                Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 2.0f);
                Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.1f);
                Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 1.0f);

            aPrevGridX = aGridX;
            aPrevGridY = aGridY;
            aPrevGridZ = aGridZ;
        }
    }

    float aX1 = gArena->GetUnitGridX(mStartX, mStartY, mStartZ);
    float aY1 = gArena->GetUnitGridY(mStartX, mStartY, mStartZ);
    float aX2 = gArena->GetUnitGridX(mEndX, mEndY, mEndZ);
    float aY2 = gArena->GetUnitGridY(mEndX, mEndY, mEndZ);

    if (mLength < 2) {
        Graphics::SetColor(0.75f, 0.75f, 0.125f, 0.75f);
        Graphics::DrawLine(aX1, aY1, aX2, aY2, 8.0f);
    }

    if (gApp->mDarkMode) {
        Graphics::SetColor(0.125f, 0.125f, 0.125f, 0.25f);
    } else {
        Graphics::SetColor();
    }

    gApp->mUnitCircleHard.Center(aX1, aY1);
    gApp->mUnitCircleHard.Center(aX2, aY2);

}

