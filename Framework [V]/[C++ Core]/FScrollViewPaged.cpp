//
//  FScrollViewPaged.cpp
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FScrollViewPaged.h"
#include "core_includes.h"

FScrollViewPaged::FScrollViewPaged()
{
    mClipsContent = false;
    mRecievesConsumedTouches = true;
    
    mName = "Paged Scroll View";
    
    mScrollPanStartThreshold = 14.0f;
    mScrollPanSwitchDirectionThreshold = 32.0f;
    
    mScrollPanning = false;
    mScrollHorizontal = false;
    
    mScrollEnabledHorizontal = true;
    mScrollEnabledVertical = true;
    
    mScrollCurrentPageH = 0;
    mScrollCurrentPageV = 0;
    
    mScrollAnimating = false;
    mScrollPanDirectionPicked = false;
    
    mScrollAnimationTimeTotal = 0;
    mScrollAnimationTimer = 0;
    
    mSpeedThresholdFlingTo = 20.0f;
    mSpeedThresholdNudgeBack = 6.0f;
    
    mScrollPageCountH = 1;
    mScrollPageCountV = 1;
    
    if((gDeviceWidth < 700) || (gDeviceHeight < 500))
    {
        mSpeedThresholdFlingTo *= 0.85f;
        mSpeedThresholdNudgeBack *= 0.85f;
    }

    for(int i=0;i<2;i++)
    {
        mScrollOffset[i] = 0.0f;
        mScrollOffsetPanShift[i] = 0.0f;
        mScrollOffsetPanStart[i] = 0.0f;
    }

    mAnimationDirection = 0;
    mFinishAnimationDirection = 0;
    mFinishAnimation = false;
    mScrollAnimationPercent = 0.0f;
    mScrollAnimationPercentTarget = 0.0f;
}

FScrollViewPaged::~FScrollViewPaged()
{
    
}

void FScrollViewPaged::SetPageCountHorizontal(int pCount)
{
    mScrollPageCountH = pCount;
}

void FScrollViewPaged::SetPageCountVertical(int pCount)
{
    mScrollPageCountV = pCount;
}


void FScrollViewPaged::BaseUpdate()
{
    FGestureView::BaseUpdate();
    
    if(mScrollAnimating)
    {
        if(mFinishAnimation)
        {
            mScrollAnimationPercent = 0.0f;
            mScrollAnimating = false;
            
            int aDir = mFinishAnimationDirection;
            
            int aPreviousPageH = mScrollCurrentPageH;
            int aPreviousPageV = mScrollCurrentPageV;
            
            if(mScrollHorizontal)
            {
                
                mScrollCurrentPageH += aDir;
                
                mScrollOffset[0] = ((float)(-mScrollCurrentPageH)) * mWidth;
            }
            else
            {
                mScrollCurrentPageV += aDir;
                
                mScrollOffset[1] = ((float)(-mScrollCurrentPageV)) * mHeight;
            }
            
            ScrollFinished();
            
            if(mScrollHorizontal)ScrollFinishedHorizontal(aPreviousPageH, mScrollCurrentPageH);
            else ScrollFinishedVertical(aPreviousPageV, mScrollCurrentPageV);
        }
        else
        {
            mFinishAnimationDirection = 0;
            
            if(mAnimationDirection == 1)
            {
                if(mScrollAnimationPercentTarget > mScrollAnimationPercent)mScrollAnimationPercent += (mScrollAnimationPercentTarget - mScrollAnimationPercent) / 16.0f;
                mScrollAnimationPercent += 0.025f;
                if(mScrollAnimationPercent >= mScrollAnimationPercentTarget)
                {
                    mScrollAnimationPercent = mScrollAnimationPercentTarget;
                    mFinishAnimation = true;
                    if(mScrollAnimationPercentTarget > (0.5f))mFinishAnimationDirection = -1;
                }
            }
            else
            {
                if(mScrollAnimationPercent > mScrollAnimationPercentTarget)mScrollAnimationPercent -= (mScrollAnimationPercent - mScrollAnimationPercentTarget) / 16.0f;
                mScrollAnimationPercent -= 0.025f;
                
                if(mScrollAnimationPercent <= mScrollAnimationPercentTarget)
                {
                    mScrollAnimationPercent = mScrollAnimationPercentTarget;
                    mFinishAnimation = true;
                    if(mScrollAnimationPercentTarget < (-0.5f))mFinishAnimationDirection = 1;
                }
            }
            
            if(mScrollHorizontal)
            {
                float aScrollBaseStartOffset = ((float)(-mScrollCurrentPageH)) * mWidth;
                mScrollOffset[0] = aScrollBaseStartOffset + mScrollAnimationPercent * mWidth;
            }
            else
            {
                float aScrollBaseStartOffset = ((float)(-mScrollCurrentPageV)) * mHeight;
                mScrollOffset[1] = aScrollBaseStartOffset + mScrollAnimationPercent * mHeight;
            }
        }
    }
    
    EnumList(FView, aView, mSubviews)
    {
        aView->SetTransformTranslate(mScrollOffset[0], mScrollOffset[1]);
    }
    
}

void FScrollViewPaged::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData)
{
    //mScrollFlingSpeed = 0.0f;
    
    //mScrollBounceBackTimeTotal[0] = 0;
    //mScrollBounceBackTime[0] = 0;
    
    //mScrollBounceBackTimeTotal[1] = 0;
    //mScrollBounceBackTime[1] = 0;
    
    FGestureView::BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData);
}

void FScrollViewPaged::PanBegin(float pX, float pY)
{
    //Log("Pan Begin! [%.2f, %.2f] (%d)\n", pX, pY, mScrollAnimating);
    
    if(mScrollAnimating)
    {
        mScrollPanning = false;
    }
    else
    {
        mAnimationDirection = 0;
        mFinishAnimation = false;
        mScrollAnimationPercent = 0.0f;
        mScrollAnimationPercentTarget = 0.0f;
        
        mScrollPanDirectionPicked = false;
        mScrollPanning = true;
        
        for(int i=0;i<2;i++)
        {
            mScrollOffsetPanStart[i] = mScrollOffset[i];
            mScrollOffsetPanShift[i] = 0.0f;
        }
    }
}

void FScrollViewPaged::Pan(float pX, float pY)
{
    if(mScrollPanning)
    {
        mScrollOffsetPanShift[0] += pX;
        mScrollOffsetPanShift[1] += pY;
        
        float aManhattanDistanceX = fabsf(mScrollOffsetPanShift[0]);
        float aManhattanDistanceY = fabsf(mScrollOffsetPanShift[1]);
        
        float aMaximumManhattanDistance = aManhattanDistanceX;
        
        if(mScrollEnabledVertical)
        {
            if(mScrollEnabledHorizontal)
            {
                if(aManhattanDistanceY > aMaximumManhattanDistance)aMaximumManhattanDistance = aManhattanDistanceY;
            }
            else
            {
                aMaximumManhattanDistance = aManhattanDistanceY;
            }
        }
        
        if(aMaximumManhattanDistance < mScrollPanSwitchDirectionThreshold)
        {
            if(mScrollPanDirectionPicked == false)
            {
                if((aManhattanDistanceX > aManhattanDistanceY) || (mScrollEnabledVertical == false))
                {
                    if(mScrollEnabledHorizontal)
                    {
                    if(aManhattanDistanceX > mScrollPanStartThreshold)
                    {
                        //Log("Picked X!\n");
                        
                        mScrollPanDirectionPicked = true;
                        mScrollHorizontal = true;
                    }
                    }
                }
                else
                {
                    if(mScrollEnabledVertical)
                    {
                    if(aManhattanDistanceY > mScrollPanStartThreshold)
                    {
                        //Log("Picked Y!\n");
                        
                        mScrollPanDirectionPicked = true;
                        mScrollHorizontal = false;
                    }
                    }
                }
            }
        }
        
        if(mScrollPanDirectionPicked)
        {
            bool aEdge = false;
            
            if(mScrollHorizontal)
            {
                if(mScrollOffsetPanShift[0] > 0.0f)
                {
                    if(mScrollCurrentPageH <= 0)aEdge = true;
                }
                else
                {
                    if(mScrollCurrentPageH >= (mScrollPageCountH - 1))aEdge = true;
                }
                
                float aOffset = mScrollOffsetPanShift[0];
                if(aEdge)aOffset = ScrollGetBounceDragShift(aOffset);
                
                mScrollOffset[0] = (mScrollOffsetPanStart[0] + aOffset);
                mScrollOffset[1] = mScrollOffsetPanStart[1];
                
                mScrollAnimationPercent = (aOffset / mWidth);
            }
            else
            {
                if(mScrollOffsetPanShift[1] > 0.0f)
                {
                    if(mScrollCurrentPageV <= 0)aEdge = true;
                }
                else
                {
                    if(mScrollCurrentPageV >= (mScrollPageCountV - 1))aEdge = true;
                }
                
                float aOffset = mScrollOffsetPanShift[1];
                if(aEdge)aOffset = ScrollGetBounceDragShift(aOffset);
                
                mScrollOffset[0] = mScrollOffsetPanStart[0];
                mScrollOffset[1] = (mScrollOffsetPanStart[1] + aOffset);
                mScrollAnimationPercent = (aOffset / mHeight);
            }
        }
    }
    else
    {
        //PanBegin(pX, pY);
    }
}

void FScrollViewPaged::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY)
{
    if(pSpeedX > 80)pSpeedX = 80.0f;
    if(pSpeedX < -80)pSpeedX = -80.0f;
    if(pSpeedY > 80)pSpeedY = 80.0f;
    if(pSpeedY < -80)pSpeedY = -80.0f;
    
    if(mScrollPanning)
    {
        mScrollPanning = false;
        
        float aVelocity = pSpeedY;
        if(mScrollHorizontal)aVelocity = pSpeedX;
        
        float aMinimumScrollPercent = 0.25f;
        
        mAnimationDirection = -1;
        mFinishAnimation = false;
        
        if(fabsf(aVelocity) >= mSpeedThresholdFlingTo)
        {
            if(aVelocity >= 0)
            {
                mAnimationDirection = 1;
                if(mScrollAnimationPercent < 0)mScrollAnimationPercentTarget = 0.0f;
                else mScrollAnimationPercentTarget = 1.0f;
            }
            else
            {
                mAnimationDirection = -1;
                if(mScrollAnimationPercent > 0)mScrollAnimationPercentTarget = 0.0f;
                else mScrollAnimationPercentTarget = -1.0f;
            }
        }
        else
        {
            if(mScrollAnimationPercent >= 0)
            {
                if(mScrollAnimationPercent > aMinimumScrollPercent)
                {
                    mAnimationDirection = 1;
                    mScrollAnimationPercentTarget = 1.0f;
                }
                else
                {
                    mScrollAnimationPercentTarget = 0.0f;
                }
            }
            else
            {
                if(mScrollAnimationPercent < (-aMinimumScrollPercent))
                {
                    mAnimationDirection = -1;
                    mScrollAnimationPercentTarget = -1.0f;
                }
                else
                {
                    mAnimationDirection = 1;
                    mScrollAnimationPercentTarget = 0.0f;
                }
            }
        }
        
        if(mAnimationDirection < 0)
        {
            if(mScrollHorizontal)
            {
                //if(CanScrollRight() == false)
                if(mScrollCurrentPageH >= (mScrollPageCountH - 1))
                {
                    if(mScrollAnimationPercent <= 0)
                    {
                        mAnimationDirection = 1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
            else
            {
                //if(CanScrollDown() == false)
                if(mScrollCurrentPageV >= (mScrollPageCountV - 1))
                {
                    if(mScrollAnimationPercent <= 0)
                    {
                        mAnimationDirection = 1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
        }
        else
        {
            if(mScrollHorizontal)
            {
                //if(CanScrollLeft() == false)
                if(mScrollCurrentPageH <= 0)
                {
                    if(mScrollAnimationPercent >= 0)
                    {
                        mAnimationDirection = -1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
            else
            {
                if(mScrollCurrentPageV <= 0)
                {
                    if(mScrollAnimationPercent >= 0)
                    {
                        mAnimationDirection = -1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
        }
        
        mScrollAnimating = true;
    }
}

void FScrollViewPaged::ScrollFinished()
{
    Log("FScrollViewPaged::ScrollFinished()\n");
}

void FScrollViewPaged::ScrollFinishedHorizontal(int pStartRow, int pEndRow)
{
    
}

void FScrollViewPaged::ScrollFinishedVertical(int pStartCol, int pEndCol)
{
    
}

float FScrollViewPaged::ScrollGetBounceDragShift(float pAmount)
{
    float aResult = pAmount;
    
    float aMaxShift = ((gDeviceWidth * 0.25f)) / GetAbsoluteTransformScale();
    float aMaxDrag = ((gDeviceWidth * 0.75f)) / GetAbsoluteTransformScale();
    
    bool aNegative = (pAmount < 0.0f);
    
    if(aNegative)pAmount = (-pAmount);
    if(pAmount >= aMaxDrag)
    {
        aResult = aMaxShift;
    }
    else
    {
        float aPercent = (pAmount / aMaxDrag);
        float aRads = (3.1415926535897932384626433832795028841968f / 2.0f) * aPercent;
        aResult = sin(aRads) * aMaxShift;
    }
    
    if(aNegative)aResult = (-aResult);
    
    return aResult;
}
