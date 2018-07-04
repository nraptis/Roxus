//
//  TileChainLink.cpp
//  CrossBone
//
//  Created by Nick Raptis on 5/23/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#include "core_includes.h"
#include "TileChainLink.h"
#include "MainApp.h"

TileChainLink::TileChainLink(int pStartIndex, int pEndIndex)
{
    mStartX = 0.0f;
    mStartY = 0.0f;
    
    mEndX = 0.0f;
    mEndY = 0.0f;
    
    mDirX = 1.0f;
    mDirY = 0.0f;
    
    mNormX = 0.0f;
    mNormY = -1.0f;
    
    mKnotCount = 0;
    
    mKnotControlX = 0;
    mKnotControlY = 0;
    
    mKnotShiftDirX = 0;
    mKnotShiftDirY = 0;
    
    mKnotShiftMagnitude = 0;
    
    mKnotSin = 0;
    mKnotSinSpeed = 0;
    
    mPhasing = false;
    mPhasePercent = 1.0f;
    
    mStartIndex = pStartIndex;
    mEndIndex = pEndIndex;
    
}

TileChainLink::~TileChainLink()
{
    
    mStartX = 0.0f;
    mStartY = 0.0f;
    
    mEndX = 0.0f;
    mEndY = 0.0f;
    
    mDirX = 1.0f;
    mDirY = 0.0f;
    
    mNormX = 0.0f;
    mNormY = -1.0f;
    
    mKnotCount = 0;
    
    
    delete [] mKnotControlX;
    
    mKnotControlX = 0;
    mKnotControlY = 0;
    
    mKnotSin = 0;
    mKnotSinSpeed = 0;
    
    mKnotShiftDirX = 0;
    mKnotShiftDirY = 0;
    
    mKnotShiftMagnitude = 0;
    
}

void TileChainLink::Update()
{
    
    for(int i=0;i<mKnotCount;i++)
    {
        mKnotSin[i] = LoopAngle(mKnotSin[i], mKnotSinSpeed[i]);
    }
    
    if(mPhasing)
    {
        mPhasePercent -= 0.125f;
        
        if(mPhasePercent <= 0.0f)
        {
            mPhasePercent = 0.0f;
            mPhasing = false;
            
            Kill();
        }
    }
}

void TileChainLink::Draw()
{
    
    /*
    for(int i=0;i<mKnotCount;i++)
    {
        
        
        
        float aX = mKnotControlX[i];
        float aY = mKnotControlY[i];
        
        
        float aSin = Sin(mKnotSin[i]);
        
        float aDirX = mKnotShiftDirX[i];
        float aDirY = mKnotShiftDirY[i];
        
        float aMag = mKnotShiftMagnitude[i];
        
        aX += aDirX * aSin * aMag;
        aY += aDirY * aSin * aMag;
        
        mSpline.SetPoint(i, aX, aY);
        
        
        //mStreamSpline.SetPoint(i, aX, aY);
        //mStreamSpline.AddPoint(aX, aY);
        
        
        
        //Graphics::DrawPoint(aX, aY, 6.0f);
        
        //
        //        float aPercent = ((float)i) / ((float)(mKnotCount - 1));
        //
        //         = mStartX + aSpanX * aPercent;
        //        mKnotControlY[i] = mStartY + aSpanY * aPercent;
        //
        //        mKnotSin[i] = gRand.GetFloat(((float)i) * 360.0f);
        //        mKnotSinSpeed[i] = 5.0f + gRand.GetFloat(3.25f);
        //
        //        mKnotShiftMagnitude[i] = 3.0f + gRand.GetFloat(6.0f);
        //
        //        mKnotShiftDirX[i] = mNormX;
        //        mKnotShiftDirY[i] = mNormY;
        //
        
        
        
    }
    */
    
    Graphics::SetColor(0.0f, 1.0f, 0.34f, mPhasePercent);
    
    if(mPhasing == false)
    {
        Graphics::SetColor();
        
        if((mStartX == mEndX) || (mStartY == mEndY))
        {
            Graphics::DrawLine(mStartX, mStartY, mEndX, mEndY, 6.0f);
        }
        else
        {
            Graphics::DrawLine(mStartX, mStartY, mEndX, mEndY, 5.0f);
        }
    }
    
    Graphics::SetColor(mPhasePercent);
    
    for(float i=0;i<mSpline.Max();i+=0.01f)
    {
        //Graphics::DrawPoint(mSpline.GetX(i), mSpline.GetY(i));
    }
    
}

void TileChainLink::SetUp(float pStartX, float pStartY, float pEndX, float pEndY)
{
    mStartX = pStartX;
    mStartY = pStartY;
    
    mEndX = pEndX;
    mEndY = pEndY;
    
    float aSpanX = mEndX - mStartX;
    float aSpanY = mEndY - mStartY;
    
    mDirX = aSpanX;
    mDirY = aSpanY;
    
    float aDist = mDirX * mDirX + mDirY * mDirY;
    
    if(aDist > 0.1f)
    {
        aDist = (float)sqrtf(aDist);
        
        mDirX /= aDist;
        mDirY /= aDist;
    }
    else
    {
        mDirX = 0.0f;
        mDirY = 1.0f;
    }
    
    mNormX = ( mDirY);
    mNormY = (-mDirX);
    
    
    
    
    mKnotCount = 5;
    
    mKnotControlX = new float[mKnotCount * 8];
    mKnotControlY = &(mKnotControlX[mKnotCount]);
    
    mKnotSin = &(mKnotControlY[mKnotCount]);
    mKnotSinSpeed = &(mKnotSin[mKnotCount]);
    
    
    mKnotShiftDirX = &(mKnotSin[mKnotCount]);
    mKnotShiftDirY = &(mKnotShiftDirX[mKnotCount]);
    
    mKnotShiftMagnitude = &(mKnotShiftDirY[mKnotCount]);
    
    for(int i=0;i<mKnotCount;i++)
    {
        float aPercent = ((float)i) / ((float)(mKnotCount - 1));
        
        mKnotControlX[i] = mStartX + aSpanX * aPercent;
        mKnotControlY[i] = mStartY + aSpanY * aPercent;
        
        mKnotSin[i] = gRand.GetFloat(((float)i) * 360.0f);
        mKnotSinSpeed[i] = 15.0f + gRand.GetFloat(3.25f);
        
        mKnotShiftMagnitude[i] = 16.0f + gRand.GetFloat(6.0f);
        //mKnotShiftMagnitude[i] = 2.0f;
        
        mKnotShiftDirX[i] = mNormX;
        mKnotShiftDirY[i] = mNormY;
        
        mSpline.Add(mKnotControlX[i], mKnotControlY[i]);
        
        //mStreamSpline.Add(mKnotControlX[i], mKnotControlY[i]);
        
    }
    
    //mStreamSpline.SetSprite(&(gApp->mGameTileRock));
    
    //mStreamSpline.SetSprite(&(gApp->mEffectChainSplineTexture));
    
    //mStreamSpline.SetWidth(0.0f, 0.5f);
    //mStreamSpline.SetWidth(1.25f, 0.25f);
    //mStreamSpline.SetWidth(3.0f, 0.5f);
    
}


void TileChainLink::PhaseOut()
{
    if(mPhasing == false)
    {
        mPhasing = true;
    }
}



