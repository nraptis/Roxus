//
//  Unit.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "Unit.h"
#include "GameArena.h"

Unit::Unit()
{
    mApp = GAPP;
    mArena = gArena;
    
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    
    mTargetX = 0.0f;
    mTargetY = 0.0f;
    mTargetZ = 0.0f;
    
    mPathIndex = 0;
    
    mKill = 0;
    
    mFinalGridX = 0;
    mFinalGridY = 0;
    mFinalGridZ = 0;
    
    mGridX = -1;
    mGridY = -1;
    mGridZ = 1;
    
    mDrawZ = 0;
    
    mWalkSpeed = gRand.GetFloat(1.25f, 4.0f);//gRand.GetFloat(2.5f, 4.0f);
    
    mHPMax = 200;
    mHP = mHPMax;
    
    mWalking = false;
    
    mRotation = 0.0f;
    mRotationSpeed = 2.0f;
    
    mFrame = 0.0f;
}

Unit::~Unit()
{
    
    //printf("Delete Unit [%x]\n", this);
    
}

void Unit::Update()
{
    float aMaxFrame = (float)mApp->mRobot.mSequenceLength;
    
    mFrame += 0.48f;
    if(mFrame >= aMaxFrame)mFrame -= aMaxFrame;
    
    if(mWalking)
    {
        
        
        float aTargetRotation = FaceTarget(mTargetX, mTargetY, mX, mY);
        
        mRotation += DistanceBetweenAngles(mRotation, aTargetRotation) / 13.0f;
        
        float aDirX = Sin(180.0f - mRotation);
        float aDirY = Cos(180.0f - mRotation);
        
        mX += aDirX * mWalkSpeed;
        mY += aDirY * mWalkSpeed;
        
        
        float aDiffX = mTargetX - mX;
        float aDiffY = mTargetY - mY;
        
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        float aBumpDist = 30.0f;
        
        if(aDist < (aBumpDist * aBumpDist))
        {
            //Advance Up The Path... !

            /*
            mPathIndex++;
            if(mPathIndex >= mPath.mSmoothLength)
            {
                mWalking = false;
                mKill = 100;
            }
            else
            {
                
                mTargetX = mPath.mSmoothPathX[mPathIndex];
                mTargetY = mPath.mSmoothPathY[mPathIndex];
                mTargetZ = mPath.mSmoothPathZ[mPathIndex];
                
                mGridX = mPath.mSmoothPathGridX[mPathIndex];
                mGridY = mPath.mSmoothPathGridY[mPathIndex];
                mGridZ = mPath.mSmoothPathGridZ[mPathIndex];

                mDrawZ = mPath.mSmoothPathDrawZ[mPathIndex];
            }
            */
        }
        
        /*
        if(aDist > 0.2f)
        {
            aDist = sqrtf(aDist);
            
            aDiffX /= aDist;
            aDiffY /= aDist;
        }
        
        if(aDist < mWalkSpeed)
        {
            
            mGridX = mTargetGridX;
            mGridY = mTargetGridY;
            mGridZ = mTargetGridZ;
            
            mX = mTargetX;
            mY = mTargetY;
            
            mPathIndex++;
            if(mPathIndex >= mPath.mLength)
            {
                mWalking = false;
                mKill = 100;
            }
            else
            {
                WalkTo(mPath.mPathX[mPathIndex], mPath.mPathY[mPathIndex], mPath.mPathZ[mPathIndex]);
            }
            
            
        }
        else
        {
            mX += aDiffX * mWalkSpeed;
            mY += aDiffY * mWalkSpeed;
        }
        */
    }
    
}

void Unit::Draw()
{
    //mApp->mKnight.Center(mRotationIndex, mFrame, mX, mY - 40.0f);
    
    Graphics::SetColor();
    //mApp->mRobot.Draw(mX, mY, 180.0f - mRotation, mFrame, 0.6f, 0.0f);
    mApp->mRobot.Draw(mX, mY, 180.0f - mRotation, 0.0f, 0.6f, 0.0f);
    
    /*
    SetColor(0.5f);
    mApp->mUnitCircleSoft.Center(mX, mY);
    
    SetColor();
    mApp->mUnitCircleHard.Center(mX, mY);
    
    SetColor(1.0f, 0.0f, 0.0f);
    
    DrawLine(mX, mY, mX + Sin(180.0f - mRotation) * 25, mY + Cos(180.0f - mRotation) * 25);
    
    //DrawRect(mTargetX - 20, mTargetY - 20, 40, 40);
    
    //mTargetX, mTargetY
    */
}

void Unit::ComputePath()
{
    mPath.mStartX = mGridX;
    mPath.mStartY = mGridY;
    mPath.mStartZ = mGridZ;
    
    mPath.mEndX = mFinalGridX;
    mPath.mEndY = mFinalGridY;
    mPath.mEndZ = mFinalGridZ;
    
    //mPath.ComputePath();

    
    mPathIndex = 0;
}

void Unit::SetUp(GamePath *pPath)
{
    mGridX = pPath->mStartX;
    mGridY = pPath->mStartY;
    mGridZ = pPath->mStartZ;
    
    mFinalGridX = pPath->mEndX;
    mFinalGridY = pPath->mEndY;
    mFinalGridZ = pPath->mEndZ;
    
    mX = CX(mGridX, mGridZ);
    mY = CY(mGridY, mGridZ);
    
    ComputePath();

    /*
    if(mPath.mSmoothLength > 0)
    {
        mWalking = true;
        
        mX = mPath.mSmoothPathX[0];
        mY = mPath.mSmoothPathY[0];
        mZ = mPath.mSmoothPathZ[0];
        
        mDrawZ = mPath.mSmoothPathDrawZ[0];
        
        
        if(mZ > 1)mDrawZ = 2;
        else if(mZ > 0)mDrawZ = 1;
        else mDrawZ = 0;
        
        
        if(mPath.mSmoothLength > 1)
        {
            mPathIndex = 1;
            
            mTargetX = mPath.mSmoothPathX[mPathIndex];
            mTargetY = mPath.mSmoothPathY[mPathIndex];
            mTargetZ = mPath.mSmoothPathZ[mPathIndex];

            mDrawZ = mPath.mSmoothPathDrawZ[mPathIndex];
            
            
            mRotation = FaceTarget(mTargetX, mTargetY, mX, mY);
            
            
            
            
            
            
            
        }
        
        //WalkTo(mPath.mPathX[1], mPath.mPathY[1], mPath.mPathZ[1]);
    }
    else
    {
        mWalking = false;
    }
    */
    
}
