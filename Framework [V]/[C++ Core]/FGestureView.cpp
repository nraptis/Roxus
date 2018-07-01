//
//  FGestureView.cpp
//  FleetGL
//
//  Created by Nick Raptis on 2/10/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FGestureView.h"
#include "core_includes.h"

FGestureTouch::FGestureTouch()
{
    Reset(0.0f, 0.0f, 0);
    mHistoryMoveCount = 0;
}

FGestureTouch::~FGestureTouch()
{
    
}

void FGestureTouch::Reset(float pX, float pY, void *pData)
{
    mX = pX;
    mY = pY;
    
    mStartX = pX;
    mStartY = pY;
    
    mMaxDistMoved = 0.0f;
    
    mTimer = 0;
    mData = pData;
    
    mHistoryMoveX[0] = pX;
    mHistoryMoveY[0] = pY;
    mHistoryMoveTime[0] = mTimer;
    
    mHistoryMoveCount = 1;
}

void FGestureTouch::Move(float pX, float pY)
{
    mX = pX;
    mY = pY;
    
    float aDiffX = (pX - mStartX);
    float aDiffY = (pY - mStartY);
    
    if(aDiffX < 0)aDiffX = (-aDiffX);
    if(aDiffY < 0)aDiffY = (-aDiffY);
    
    if(aDiffX > mMaxDistMoved)mMaxDistMoved = aDiffX;
    if(aDiffY > mMaxDistMoved)mMaxDistMoved = aDiffY;
    
    //mStartX = pX;
    //mStartY = pY;
    
    if(mHistoryMoveCount == MAX_GESTURE_TOUCH_RECORD_COUNT)
    {
        for(int i=1;i<MAX_GESTURE_TOUCH_RECORD_COUNT;i++)mHistoryMoveX[i - 1] = mHistoryMoveX[i];
        for(int i=1;i<MAX_GESTURE_TOUCH_RECORD_COUNT;i++)mHistoryMoveY[i - 1] = mHistoryMoveY[i];
        for(int i=1;i<MAX_GESTURE_TOUCH_RECORD_COUNT;i++)mHistoryMoveTime[i - 1] = mHistoryMoveTime[i];
        
        mHistoryMoveX[MAX_GESTURE_TOUCH_RECORD_COUNT - 1] = pX;
        mHistoryMoveY[MAX_GESTURE_TOUCH_RECORD_COUNT - 1] = pY;
        mHistoryMoveTime[MAX_GESTURE_TOUCH_RECORD_COUNT - 1] = mTimer;
    }
    else
    {
        mHistoryMoveX[mHistoryMoveCount] = pX;
        mHistoryMoveY[mHistoryMoveCount] = pY;
        mHistoryMoveTime[mHistoryMoveCount] = mTimer;
        
        mHistoryMoveCount++;
    }
}

FGestureView::FGestureView()
{
    mTouchCount = 0;
    
    mIsPanning = false;
    mIsPinching = false;
    mIsRotating = false;
    
    mEnableGestures = true;
    
    mEnablePanning = true;
    mEnablePinching = true;
    mEnableRotating = true;
    
    mGesturePanRequiredTouches = 1;
    
    mGesturePanStartX = 0.0f;
    mGesturePanStartY = 0.0f;
    
    mGesturePanStartCenterX = 0.0f;
    mGesturePanStartCenterY = 0.0f;
    
    mGestureTouchCenterX = 0;
    mGestureTouchCenterY = 0;
    
    mGesturePanDistX = 0.0f;
    mGesturePanDistY = 0.0f;
    
    mGesturePanPreviousCenterX = 0.0f;
    mGesturePanPreviousCenterY = 0.0f;
    
    mGestureTapLastTapTimer = 0;
    mGestureTapLastTapCount = 0;
    mGestureTapQueued = false;
    
    mGestureTranslateX = 0.0f;
    mGestureTranslateY = 0.0f;
    
    mGesturePinchX1 = 0.0f;
    mGesturePinchY1 = 0.0f;
    mGesturePinchX2 = 0.0f;
    mGesturePinchY2 = 0.0f;
    
    mGesturePinchStartDist = 0.0f;
    mGesturePinchScale = 1.0f;
    
    mGestureRotateStartAngle = 0.0f;
    
    for(int i=0;i<MAX_GESTURE_TOUCHES;i++)
    {
        mTouch[i] = new FGestureTouch();
    }
    
}

FGestureView::~FGestureView()
{
    
}

void FGestureView::BaseUpdate()
{
    FView::BaseUpdate();
    
    for(int i=0;i<mTouchCount;i++)
    {
        mTouch[i]->mTimer++;
    }
    
    if(mGestureTapQueued)
    {
        mGestureTapLastTapTimer++;
        if((mGestureTapLastTapTimer > 16) || (mEnableGestures == false))
        {
            mGestureTapQueued = false;
            mGestureTapLastTapTimer = 0;
            mGestureTapLastTapCount = 0;
        }
    }
}







void FGestureView::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData)
{
    FGestureTouch *aTouch = 0;
    
    if(mTouchCount < MAX_GESTURE_TOUCHES)
    {
        bool aExists = false;
        for(int i = 0; i < mTouchCount; i++)
        {
            if(mTouch[i]->mData == pData)
            {
                aTouch = mTouch[i];
            }
        }
        
        if(aTouch == 0)
        {
            aTouch = mTouch[mTouchCount];
            mTouchCount++;
        }
    }
    else
    {
        aTouch = mTouch[0];
        
        for(int i=1;i<MAX_GESTURE_TOUCHES;i++)
        {
            mTouch[i-1] = mTouch[i];
        }
        
        mTouch[MAX_GESTURE_TOUCHES - 1] = aTouch;
    }
    
    if(aTouch)
    {
        aTouch->Reset(pX, pY, pData);
        
        if(mEnableGestures)
        {
            GestureComputeCenter();
            
            if(mIsPanning && mEnablePanning)
            {
                mGesturePanStartCenterX = mGestureTouchCenterX;
                mGesturePanStartCenterY = mGestureTouchCenterY;
                
                mGesturePanPreviousCenterX = mGestureTouchCenterX;
                mGesturePanPreviousCenterY = mGestureTouchCenterY;
            }
            
            
        }
    }
    
    TouchDown(pX, pY, pData);
}

void FGestureView::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData)
{
    int aTouchIndex = -1;
    
    for(int i=0;i<mTouchCount;i++)
    {
        if(mTouch[i]->mData == pData)
        {
            aTouchIndex = i;
            break;
        }
    }
    
    if(aTouchIndex >= 0)
    {
        FGestureTouch *aMovedTouch = mTouch[aTouchIndex];
        aMovedTouch->Move(pX, pY);
        
        GestureComputeCenter();
        
        float aTriggerPanDistance = 10.0f;
        if((gDeviceWidth > 600.0f) || (gDeviceHeight > 600.0f))aTriggerPanDistance = 14.0f;
        
        float aTriggerPinchDistance = 1.0f;
        //if((gDeviceWidth > 600.0f) || (gDeviceHeight > 600.0f))aTriggerPinchDistance = 10.0f;
        
        float aPinchSize = 24.0f;
        
        
        if(mIsPanning == false)
        {
            
            
            if(mTouchCount >= mGesturePanRequiredTouches)
            {
                if(aMovedTouch->mMaxDistMoved > aTriggerPanDistance)
                {
                    mIsPanning = true;
                    
                    
                    mGesturePanDistX = (aMovedTouch->mX - aMovedTouch->mStartX);
                    mGesturePanDistY = (aMovedTouch->mY - aMovedTouch->mStartY);
                    
                    mGesturePanStartCenterX = mGestureTouchCenterX;
                    mGesturePanStartCenterY = mGestureTouchCenterY;
                    
                    mGesturePanPreviousCenterX = mGestureTouchCenterX;
                    mGesturePanPreviousCenterY = mGestureTouchCenterY;
                    
                    mGesturePanDistX = (mGestureTouchCenterX - mGesturePanStartCenterX);
                    mGesturePanDistY = (mGestureTouchCenterY - mGesturePanStartCenterY);
                    
                    //PanBegin(mGesturePanStartCenterX + mGesturePanDistX, mGesturePanStartCenterY + mGesturePanDistY);
                    PanBegin(0.0f, 0.0f);
                    
                    Pan(mGesturePanDistX, mGesturePanDistY);
                }
            }
        }
        else
        {
            mGesturePanDistX = (mGestureTouchCenterX - mGesturePanStartCenterX);
            mGesturePanDistY = (mGestureTouchCenterY - mGesturePanStartCenterY);
            
            Pan(mGesturePanDistX, mGesturePanDistY);
        }
        
        
        if(mIsPinching == false)
        {
            if((mTouchCount >= 2) && (mEnablePinching == true) && (mEnableGestures == true))
            {
                if(true)//aMovedTouch->mMaxDistMoved > aPinchSize)
                {
                    mGesturePinchStartDist = Distance(mTouch[0]->mStartX, mTouch[0]->mStartY, mTouch[1]->mStartX, mTouch[1]->mStartY);
                    mGesturePinchScale = 1.0f;
                    
                    if(mGesturePinchStartDist > aPinchSize)
                    {
                        mIsPinching = true;
                        float aDist = Distance(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);
                        
                        mGesturePinchScale = (aDist / mGesturePinchStartDist);
                        
                        PinchBegin(1.0f);
                        Pinch(mGesturePinchScale);
                    }
                    
                }
            }
        }
        else
        {
            if(mTouchCount >= 2)
            {
                
                if(mGesturePinchStartDist > aPinchSize)
                {
                    float aDist = Distance(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);
                    mGesturePinchScale = (aDist / mGesturePinchStartDist);
                    Pinch(mGesturePinchScale);
                }
            }
            else
            {
                PinchEnd(mGesturePinchScale);
                mIsPinching = false;
            }
        }
        
        
        
        
        if(mIsRotating == false)
        {
            if((mTouchCount >= 2) && (mEnableRotating == true) && (mEnableGestures == true))
            {
                if(aMovedTouch->mMaxDistMoved > aTriggerPinchDistance)
                {
                    
                    float aDist = Distance(mTouch[0]->mStartX, mTouch[0]->mStartY, mTouch[1]->mStartX, mTouch[1]->mStartY);
                    
                    
                    
                    if(aDist > 36.0f)
                    {
                        mIsRotating = true;
                        
                        mGestureRotateStartAngle = FaceTarget(mTouch[0]->mStartX, mTouch[0]->mStartY, mTouch[1]->mStartX, mTouch[1]->mStartY);
                        
                        float aAngle = FaceTarget(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);
                        
                        mGestureRotateDegrees = DistanceBetweenAngles(mGestureRotateStartAngle, aAngle);
                        
                        RotateStart(0.0f);
                        Rotate(mGestureRotateDegrees);
                        
                    }
                    
                }
            }
        }
        else
        {
            if(mTouchCount >= 2)
            {
                
                if(mGesturePinchStartDist > 36.0f)
                {
                    float aAngle = FaceTarget(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);
                    mGestureRotateDegrees = DistanceBetweenAngles(mGestureRotateStartAngle, aAngle);
                    
                    Rotate(mGestureRotateDegrees);
                }
            }
            else
            {
                RotateEnd(mGestureRotateDegrees);
                mIsRotating = false;
            }
        }
        
        
        
    }
    
    
    
    
    
    
    TouchMove(pX, pY, pData);
}

void FGestureView::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData)
{
    
    
    int aTouchIndex = -1;
    
    for(int i=0;i<mTouchCount;i++)
    {
        if(mTouch[i]->mData == pData)
        {
            aTouchIndex = i;
            break;
        }
    }
    
    if(aTouchIndex >= 0)
    {
        FGestureTouch *aReleasedTouch = mTouch[aTouchIndex];
        for(int i=aTouchIndex+1;i<mTouchCount;i++)mTouch[i-1] = mTouch[i];
        mTouch[mTouchCount - 1] = aReleasedTouch;
        
        mTouchCount--;
        
        GestureComputeCenter();
        
        
        if(mIsPinching)
        {
            PinchEnd(mGesturePinchScale);
            mIsPinching = false;
        }
        
        if(mIsRotating)
        {
            RotateEnd(mGestureRotateDegrees);
            mIsRotating = false;
        }
        
        
        if(mIsPanning)
        {
            if(mTouchCount == 0)
            {
                float aReleaseSpeedX = 0.0f;
                float aReleaseSpeedY = 0.0f;
                
                int aReleaseTime = (aReleasedTouch->mTimer - 6);
                int aReleaseConsiderCount = 0;
                
                for(int i=(aReleasedTouch->mHistoryMoveCount - 2);i >= 0;i--)
                {
                    if(aReleasedTouch->mHistoryMoveTime[i + 1] >= aReleaseTime)
                    {
                        int aTimeDiff = (aReleasedTouch->mHistoryMoveTime[i + 1] - aReleasedTouch->mHistoryMoveTime[i]);
                        
                        float aXDiff = (aReleasedTouch->mHistoryMoveX[i + 1] - aReleasedTouch->mHistoryMoveX[i]);
                        float aYDiff = (aReleasedTouch->mHistoryMoveY[i + 1] - aReleasedTouch->mHistoryMoveY[i]);
                        
                        aReleaseSpeedX += ((float)aTimeDiff) * aXDiff;
                        aReleaseSpeedY += ((float)aTimeDiff) * aYDiff;
                        
                        aReleaseConsiderCount++;
                    }
                }
                
                
                if(aReleaseConsiderCount > 0)
                {
                    aReleaseConsiderCount++;
                    
                    aReleaseSpeedX /= ((float)aReleaseConsiderCount);
                    aReleaseSpeedY /= ((float)aReleaseConsiderCount);
                }
                
                PanEnd(aReleasedTouch->mX, aReleasedTouch->mY, aReleaseSpeedX, aReleaseSpeedY);
                
                mIsPanning = false;
                
            }
            else
            {
                mGesturePanStartCenterX = mGestureTouchCenterX;
                mGesturePanStartCenterY = mGestureTouchCenterY;
                
                mGesturePanPreviousCenterX = mGestureTouchCenterX;
                mGesturePanPreviousCenterY = mGestureTouchCenterY;
            }
        }
        else
        {
            if(mTouchCount == 0)
            {
                if(aReleasedTouch->mTimer <= 12)
                {
                    mGestureTapLastTapCount++;
                    mGestureTapQueued = true;
                    
                    if(mGestureTapLastTapCount == 1)
                    {
                        mGestureTapLastTapTimer = 0;
                        TapSingle(aReleasedTouch->mX, aReleasedTouch->mY);
                    }
                    else if(mGestureTapLastTapCount == 2)
                    {
                        TapDouble(aReleasedTouch->mX, aReleasedTouch->mY);
                        mGestureTapLastTapCount = 0;
                    }
                }
                else
                {
                    mGestureTapLastTapTimer = 0;
                    mGestureTapLastTapCount = 0;
                    mGestureTapQueued = false;
                }
            }
            else
            {
                mGestureTapLastTapTimer = 0;
                mGestureTapLastTapCount = 0;
                mGestureTapQueued = false;
            }
        }
    }
    
    TouchUp(pX, pY, pData);
}

void FGestureView::BaseTouchFlush()
{
    FView::BaseTouchFlush();
    
    /*
     
     TouchFlush();
     EnumList(FView, aView, mSubviews)
     {
     aView->BaseTouchFlush();
     }
     
     */
    
    
}

void FGestureView::GestureComputeCenter()
{
    mGestureTouchCenterX = 0.0f;
    mGestureTouchCenterY = 0.0f;
    
    for(int i=0;i<mTouchCount;i++)
    {
        mGestureTouchCenterX += mTouch[i]->mX;
        mGestureTouchCenterY += mTouch[i]->mY;
    }
    
    mGestureTouchCenterX /= ((float)mTouchCount);
    mGestureTouchCenterY /= ((float)mTouchCount);
}

void FGestureView::PanBegin(float pX, float pY)
{
    
}

void FGestureView::Pan(float pX, float pY)
{
    
}

void FGestureView::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY)
{
    
}


void FGestureView::PinchBegin(float pScale)
{
    
}

void FGestureView::Pinch(float pScale)
{
    
}

void FGestureView::PinchEnd(float pScale)
{
    
}

void FGestureView::TapSingle(float pX, float pY)
{
    //Log("FGestureView::TapSingle(%f, %f)\n", pX, pY);
    
}

void FGestureView::TapDouble(float pX, float pY)
{
    //Log("FGestureView::TapDouble(%f, %f)\n", pX, pY);
}

void FGestureView::RotateStart(float pRotation)
{
    //Log("FGestureView::RotateStart(%f)\n", pRotation);
}

void FGestureView::Rotate(float pRotation)
{
    //Log("FGestureView::Rotate(%f)\n", pRotation);
    
}

void FGestureView::RotateEnd(float pRotation)
{
    //Log("FGestureView::RotateEnd(%f)\n", pRotation);

}

void FGestureView::Kill()
{
    ClearGestures(true);
    FView::Kill();
}

void FGestureView::ClearGestures(bool pEndActive)
{
    if(pEndActive)
    {
        if(mIsPanning)
        {
            mIsPanning = false;
            PanEnd(mGesturePanDistX, mGesturePanDistY, 0.0f, 0.0f);
        }
        
        if(mIsPinching)
        {
            mIsPinching = false;
            PinchEnd(mGesturePinchScale);
        }
    }
    else
    {
        mIsPanning = false;
        mIsPinching = false;
    }
}



