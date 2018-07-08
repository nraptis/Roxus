//
//  GamePath.cpp
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "GamePath.h"
#include "GameArena.h"
#include "Spline.h"

GamePath::GamePath()
{
    mArena = gArena;
    
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
    
    
    mSmoothPathX = 0;
    mSmoothPathY = 0;
    mSmoothPathZ = 0;
    
    mSmoothPathGridX = 0;
    mSmoothPathGridY = 0;
    mSmoothPathGridZ = 0;
    
    mSmoothPathDrawZ = 0;
    
    mSmoothLength = 0;
    mSmoothSize = 0;
}

GamePath::~GamePath()
{
    delete [] mPathX;
    
    mPathX = 0;
    mPathY = 0;
    mPathZ = 0;
    
    mLength = 0;
    mSize = 0;
    
    delete [] mSmoothPathX;
    mSmoothPathX = 0;
    mSmoothPathY = 0;
    mSmoothPathZ = 0;
    
    delete [] mSmoothPathGridX;
    mSmoothPathGridX = 0;
    mSmoothPathGridY = 0;
    mSmoothPathGridZ = 0;
    mSmoothPathDrawZ = 0;
    
    mSmoothLength = 0;
    mSmoothSize = 0;
    
}


void GamePath::Update()
{
    //ComputePath();
}

void GamePath::Draw()
{
    for(int i=0;i<mLength;i++)
    {
        
        /*
        float aPercent = (float)i / ((float)(mLength - 1));
        
        SetColor(aPercent, 0.0f, 0.25f);
        //SetColor(0.0f, 0.0f, 0.0f);
        
        float aX = CX(mPathX[i], mPathZ[i]);
        float aY = CX(mPathY[i], mPathZ[i]);
        
        DrawRect(aX - 3, aY - 3, 7.0f, 7.0f);
        */
        
    }
    
    for(int i=0;i<mSmoothLength;i++)
    {
        //SetColor(0.65f, 0.0f, 0.05f, 1.0f);
        
        float aX = mSmoothPathX[i];
        float aY = mSmoothPathY[i];
        
        if(mSmoothPathDrawZ[i] == 0)SetColor(1.0f, 0.0f, 0.5f);
        if(mSmoothPathDrawZ[i] == 1)SetColor(0.0f, 1.0f, 0.5f);
        if(mSmoothPathDrawZ[i] == 2)SetColor(0.15f, 0.25f, 1.0f);
        
        DrawRect(aX - 2, aY - 2, 5.0f, 5.0f);
    }
    
    
    /*
    Spline aSpline;
    
    for(int i=0;i<mLength;i++)
    {
        float aPercent = (float)i / ((float)(mLength - 1));
        
        SetColor(aPercent, 0.0f, 0.25f);
        
        GameTile *aTile = mArena->GetTile(mPathX[i], mPathY[i], mPathZ[i]);
        
        if(aTile)
        {
            aSpline.AddPoint(aTile->mCenterX, aTile->mCenterY);
            
            //DrawRect(aTile->mCenterX - 11, aTile->mCenterY - 11, 23.0f, 23.0f);
        }
    }
    
    SetColor();
    for(float aPos=0.0f;aPos<=aSpline.Max();aPos+=0.025f)
    {
        float aX = aSpline.GetX(aPos);
        float aY = aSpline.GetY(aPos);
        
        DrawRect(aX - 2, aY - 2, 5, 5);
    }
    
    
    
    
    int aPathX, aPathY, aPathZ;
    int aPrevPathX, aPrevPathY, aPrevPathZ;
    int aNextPathX, aNextPathY, aNextPathZ;
    int aLength1 = (mLength - 1);
    
    //int aPreviousDirection = PATH_DIRECTION_NULL;
    
    int aDirX, aDirY;
    int aPrevDirX, aPrevDirY;
    bool aPrevWasKink = false;
    
    aSpline.Clear();
    
    if(mLength > 1)
    {
        aSpline.Add(CX(mPathX[0], mPathZ[0]), CY(mPathY[0], mPathZ[0]));
        
        aPrevPathX = mPathX[0];
        aPrevPathY = mPathY[0];
        aPrevPathZ = mPathZ[0];
        
        aPathX = mPathX[1];
        aPathY = mPathY[1];
        aPathZ = mPathZ[1];
        
        
        //aDirX = aPathX - aPrevPathX;
        //aDirY = aPathY - aPrevPathY;
        
        aPrevDirX = aPathX - aPrevPathX;
        aPrevDirY = aPathY - aPrevPathY;
        
        //aNextPathX = mPathX[2];
        //aNextPathY = mPathY[2];
        //aNextPathZ = mPathZ[2];
        
        for(int i=1;i<aLength1;i++)
        {
            
            aNextPathX = mPathX[i + 1];
            aNextPathY = mPathY[i + 1];
            aNextPathZ = mPathZ[i + 1];
            
            aDirX = aNextPathX - aPathX;
            aDirY = aNextPathY - aPathY;
            
            float aX = CX(aPathX, aPathZ);
            float aY = CX(aPathY, aPathZ);
            
            if(aDirX == aPrevDirX && aDirY == aPrevDirY)
            {
                SetColor(1.0f, 0.0f, 0.0f);
                DrawRect(aX - 11, aY - 11, 23.0f, 23.0f);
                
                aSpline.Add(aX, aY);
                
                aPrevWasKink = false;
            }
            else
            {
                
                
                if(aPrevWasKink == false)
                {
                    float aPrevX = CX(aPrevPathX, aPrevPathZ);
                    float aPrevY = CY(aPrevPathY, aPrevPathZ);
                    
                    float aX1 = (aPrevX + aX) * 0.5f;
                    float aY1 = (aPrevY + aY) * 0.5f;
                    
                    SetColor(0.0f, 1.0f, 0.0f, 0.5f);
                    DrawRect(aX1 - 8, aY1 - 8, 17.0f, 17.0f);
                    
                    aSpline.Add(aX1, aY1);
                }
                
                
                
                
                
                float aNextX = CX(aNextPathX, aNextPathZ);
                float aNextY = CY(aNextPathY, aNextPathZ);
                
                
                float aX2 = (aNextX + aX) * 0.5f;
                float aY2 = (aNextY + aY) * 0.5f;
                
                SetColor(0.0f, 0.0f, 1.0f, 0.5f);
                DrawRect(aX2 - 8, aY2 - 8, 17.0f, 17.0f);
                
                aSpline.Add(aX2, aY2);
                
                aPrevWasKink = true;
            }
            
            aPrevDirX = aDirX;aPrevDirY = aDirY;
            aPrevPathX = aPathX;aPrevPathY = aPathY;aPrevPathZ = aPathZ;
            aPathX = aNextPathX;aPathY = aNextPathY;aPathZ = aNextPathZ;
        }
        
        aSpline.Add(CX(mPathX[mLength - 1], mPathZ[mLength - 1]), CY(mPathY[mLength - 1], mPathZ[mLength - 1]));
        
    }
    
    SetColor(0.0f, 0.0f, 0.0f);
    for(float aPos=0.0f;aPos<=aSpline.Max();aPos+=0.025f)
    {
        float aX = aSpline.GetX(aPos);
        float aY = aSpline.GetY(aPos);
        
        DrawRect(aX - 1, aY - 1, 3, 3);
    }
    */

}

void GamePath::ComputePath()
{
    GameTile *aStartTile = mArena->GetTile(mStartX, mStartY, mStartZ);
    GameTile *aEndTile = mArena->GetTile(mEndX, mEndY, mEndZ);
    
    gPathFinder->FindPath(aStartTile, aEndTile);
    GameTileConnection *aConnection = gPathFinder->mPathEnd;
    
    if(aConnection)
    {
        mLength = 0;
        
        while(aConnection)
        {
            aConnection = aConnection->mParent;
            mLength++;
        }
        
        if(mLength >= mSize)
        {
            delete [] mPathX;
            
            mSize = mLength + (mLength / 2) + 1;
            
            mPathX = new int[mSize * 3];
            mPathY = mPathX + mSize;
            mPathZ = mPathY + mSize;
        }
        
        int aIndex = mLength - 1;
        aConnection = gPathFinder->mPathEnd;
        while(aConnection)
        {
            mPathX[aIndex] = aConnection->mTile->mGridX;
            mPathY[aIndex] = aConnection->mTile->mGridY;
            mPathZ[aIndex] = aConnection->mTile->mGridZ;
            
            aConnection = aConnection->mParent;
            aIndex--;
        }
    }
    else
    {
        mLength = 0;
    }
    
    ComputeSmoothPath();
}

void GamePath::ComputeSmoothPath()
{
    mSmoothLength = 0;
    
    if(mLength > 2)
    {
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
        
        for(int i=1;i<aLength1;i++)
        {
            
            aNextPathX = mPathX[i + 1];
            aNextPathY = mPathY[i + 1];
            aNextPathZ = mPathZ[i + 1];
            
            aNextX = CX(aNextPathX, aNextPathZ);
            aNextY = CY(aNextPathY, aNextPathZ);
            aNextZ = (float)aNextPathZ;
            
            aDirX = aNextPathX - aPathX;
            aDirY = aNextPathY - aPathY;
            
            if(aDirX == aPrevDirX && aDirY == aPrevDirY)
            {
                AddSmooth(aX, aY, aZ, aPathX, aPathY, aPathZ);
                
                aPrevWasKink = false;
            }
            else
            {
                if(aPrevWasKink == false)
                {
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
        
    }
    else
    {
        for(int i=0;i<mLength;i++)
        {
            AddSmooth(CX(mPathX[i], mPathZ[i]), CY(mPathY[i], mPathZ[i]), (float)mPathZ[i], mPathX[i], mPathY[i], mPathZ[i]);
        }
    }
    
    
    int aPreviousGridZ = -1;
    int aCurrentGridZ = 0;
    for(int i=0;i<mSmoothLength;i++)
    {
        aCurrentGridZ = mSmoothPathGridZ[i];
        
        if(aCurrentGridZ < aPreviousGridZ)mSmoothPathDrawZ[i] = aPreviousGridZ;
        else mSmoothPathDrawZ[i] = aCurrentGridZ;
        
        aPreviousGridZ = aCurrentGridZ;
    }
    
}

void GamePath::AddSmooth(float pX, float pY, float pZ, int pGridX, int pGridY, int pGridZ)
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


XMLTag *GamePath::Save()
{
    XMLTag *aTag = new XMLTag("path");
    
    aTag->AddParam("start_x", FString(mStartX).c());
    aTag->AddParam("start_y", FString(mStartY).c());
    aTag->AddParam("start_z", FString(mStartZ).c());
    
    aTag->AddParam("end_x", FString(mEndX).c());
    aTag->AddParam("end_y", FString(mEndY).c());
    aTag->AddParam("end_z", FString(mEndZ).c());
    
    return aTag;
}

void GamePath::Load(XMLTag *pTag)
{
    if(pTag)
    {
        mStartX = FString(pTag->GetParamValue("start_x")).ToInt();
        mStartY = FString(pTag->GetParamValue("start_y")).ToInt();
        mStartZ = FString(pTag->GetParamValue("start_z")).ToInt();
        
        mEndX = FString(pTag->GetParamValue("end_x")).ToInt();
        mEndY = FString(pTag->GetParamValue("end_y")).ToInt();
        mEndZ = FString(pTag->GetParamValue("end_z")).ToInt();
    }
}
