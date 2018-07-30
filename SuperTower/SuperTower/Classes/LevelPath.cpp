//
//  LevelPath.cpp
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "LevelPath.hpp"
#include "GameArena.hpp"
#include "FSpline.h"

LevelPath::LevelPath() {
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

LevelPath::~LevelPath() {
    delete [] mPathX;
    mPathX = 0;
    mPathY = 0;
    mPathZ = 0;
    mLength = 0;
    mSize = 0;
}

void LevelPath::ComputePath(GameArena *pArena) {
    GameTile *aStartTile = pArena->GetTile(mStartX, mStartY, mStartZ);
    GameTile *aEndTile = pArena->GetTile(mEndX, mEndY, mEndZ);
    mPathFinder.FindPath(aStartTile, aEndTile);
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

/*
void LevelPath::ComputeSmoothPath() {
    mSmoothLength = 0;
    if (mLength > 2) {
        int aPathX, aPathY, aPathZ;
        int aPrevPathX, aPrevPathY, aPrevPathZ;
        int aNextPathX, aNextPathY, aNextPathZ;
        int aLength1 = (mLength - 1);
        
        int aDirX, aDirY;
        int aPrevDirX, aPrevDirY;
        bool aPrevWasKink = false;
        
        aPrevPathX = mPathX[0];
        aPrevPathY = mPathY[0];
        aPrevPathZ = mPathZ[0];
        
        aPathX = mPathX[1];
        aPathY = mPathY[1];
        aPathZ = mPathZ[1];
        
        float aPrevX = CX(aPrevPathX, aPrevPathZ);
        float aPrevY = CY(aPrevPathY, aPrevPathZ);
        float aPrevZ = (float)aPrevPathZ;
        
        float aX = CX(aPathX, aPathZ);
        float aY = CX(aPathY, aPathZ);
        float aZ = (float)aPathZ;
        
        float aNextX = 0.0f;
        float aNextY = 0.0f;
        float aNextZ = 0.0f;
        
        float aInterpX = 0.0f;
        float aInterpY = 0.0f;
        float aInterpZ = 0.0f;
        
        aPrevDirX = aPathX - aPrevPathX;
        aPrevDirY = aPathY - aPrevPathY;

        AddSmooth(aPrevX, aPrevY, aPrevZ, aPrevPathX, aPrevPathY, aPrevPathZ);

        for (int i=1;i<aLength1;i++) {
            aNextPathX = mPathX[i + 1];
            aNextPathY = mPathY[i + 1];
            aNextPathZ = mPathZ[i + 1];
            
            aNextX = CX(aNextPathX, aNextPathZ);
            aNextY = CY(aNextPathY, aNextPathZ);
            aNextZ = (float)aNextPathZ;
            aDirX = aNextPathX - aPathX;
            aDirY = aNextPathY - aPathY;
            if (aDirX == aPrevDirX && aDirY == aPrevDirY) {
                AddSmooth(aX, aY, aZ, aPathX, aPathY, aPathZ);
                aPrevWasKink = false;
            } else {
                if (aPrevWasKink == false) {
                    aInterpX = (aPrevX + aX) * 0.5f;
                    aInterpY = (aPrevY + aY) * 0.5f;
                    aInterpZ = (aPrevZ + aZ) * 0.5f;
                    AddSmooth(aInterpX, aInterpY, aInterpZ, aPrevPathX, aPrevPathY, aPrevPathZ);
                }
                
                aInterpX = (aNextX + aX) * 0.5f;
                aInterpY = (aNextY + aY) * 0.5f;
                aInterpZ = (aNextZ + aZ) * 0.5f;
                
                AddSmooth(aInterpX, aInterpY, aInterpZ, aNextPathX, aNextPathY, aNextPathZ);
                
                aPrevWasKink = true;
            }
            
            aPrevX = aX;aPrevY = aY;aPrevZ = aZ;
            aX = aNextX;aY = aNextY;aZ = aNextZ;
            
            aPrevDirX = aDirX;aPrevDirY = aDirY;
            aPrevPathX = aPathX;aPrevPathY = aPathY;aPrevPathZ = aPathZ;
            aPathX = aNextPathX;aPathY = aNextPathY;aPathZ = aNextPathZ;
        }
        
        AddSmooth(aNextX, aNextY, aNextZ, aNextPathX, aNextPathY, aNextPathZ);
        
    } else {
        for (int i=0;i<mLength;i++) {
            AddSmooth(CX(mPathX[i], mPathZ[i]), CY(mPathY[i], mPathZ[i]), (float)mPathZ[i], mPathX[i], mPathY[i], mPathZ[i]);
        }
    }
    
    
    int aPreviousGridZ = -1;
    int aCurrentGridZ = 0;
    for (int i=0;i<mSmoothLength;i++) {
        aCurrentGridZ = mSmoothPathGridZ[i];
        
        if(aCurrentGridZ < aPreviousGridZ)mSmoothPathDrawZ[i] = aPreviousGridZ;
        else mSmoothPathDrawZ[i] = aCurrentGridZ;
        
        aPreviousGridZ = aCurrentGridZ;
    }
}

void LevelPath::AddSmooth(float pX, float pY, float pZ, int pGridX, int pGridY, int pGridZ)
{
    
    //printf("Adding Smootj [%d %d %d] [%.2f %.2f %.2f]\n", pGridX, pGridY, pGridZ, pX, pY, pZ);
    
    if(mSmoothLength >= mSmoothSize)
    {
        mSmoothSize = mSmoothLength + (mSmoothLength / 2) + 1;
        
        float *aSmoothPathX = new float[mSmoothSize * 3];
        float *aSmoothPathY = aSmoothPathX + mSmoothSize;
        float *aSmoothPathZ = aSmoothPathY + mSmoothSize;
        
        for(int i=0;i<mSmoothLength;i++)aSmoothPathX[i]=mSmoothPathX[i];
        for(int i=0;i<mSmoothLength;i++)aSmoothPathY[i]=mSmoothPathY[i];
        for(int i=0;i<mSmoothLength;i++)aSmoothPathZ[i]=mSmoothPathZ[i];
        
        delete [] mSmoothPathX;
        
        mSmoothPathX = aSmoothPathX;
        mSmoothPathY = aSmoothPathY;
        mSmoothPathZ = aSmoothPathZ;
        
        
        
        
        
        int *aSmoothGridX = new int[mSmoothSize * 4];
        int *aSmoothGridY = aSmoothGridX + mSmoothSize;
        int *aSmoothGridZ = aSmoothGridY + mSmoothSize;
        int *aSmoothDrawZ = aSmoothGridZ + mSmoothSize;
        
        
        for(int i=0;i<mSmoothLength;i++)aSmoothGridX[i]=mSmoothPathGridX[i];
        for(int i=0;i<mSmoothLength;i++)aSmoothGridY[i]=mSmoothPathGridY[i];
        for(int i=0;i<mSmoothLength;i++)aSmoothGridZ[i]=mSmoothPathGridZ[i];
        for(int i=0;i<mSmoothLength;i++)aSmoothDrawZ[i]=mSmoothPathDrawZ[i];
        
        delete [] mSmoothPathGridX;
        
        mSmoothPathGridX = aSmoothGridX;
        mSmoothPathGridY = aSmoothGridY;
        mSmoothPathGridZ = aSmoothGridZ;
        mSmoothPathDrawZ = aSmoothDrawZ;
    }
    
    mSmoothPathX[mSmoothLength] = pX;
    mSmoothPathY[mSmoothLength] = pY;
    mSmoothPathZ[mSmoothLength] = pZ;
    
    mSmoothPathGridX[mSmoothLength] = pGridX;
    mSmoothPathGridY[mSmoothLength] = pGridY;
    mSmoothPathGridZ[mSmoothLength] = pGridZ;
    mSmoothPathDrawZ[mSmoothLength] = pGridZ;
    
    mSmoothLength++;
    
}
*/


FXMLTag *LevelPath::Save() {
    FXMLTag *aTag = new FXMLTag("path");
    aTag->AddParam("start_x", FString(mStartX).c());
    aTag->AddParam("start_y", FString(mStartY).c());
    aTag->AddParam("start_z", FString(mStartZ).c());
    aTag->AddParam("end_x", FString(mEndX).c());
    aTag->AddParam("end_y", FString(mEndY).c());
    aTag->AddParam("end_z", FString(mEndZ).c());
    return aTag;
}

void LevelPath::Load(FXMLTag *pTag) {
    if (pTag) {
        mStartX = FString(pTag->GetParamValue("start_x")).ToInt();
        mStartY = FString(pTag->GetParamValue("start_y")).ToInt();
        mStartZ = FString(pTag->GetParamValue("start_z")).ToInt();
        mEndX = FString(pTag->GetParamValue("end_x")).ToInt();
        mEndY = FString(pTag->GetParamValue("end_y")).ToInt();
        mEndZ = FString(pTag->GetParamValue("end_z")).ToInt();
    }
}
