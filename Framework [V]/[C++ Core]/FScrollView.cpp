//
//  FScrollView.cpp
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FScrollView.h"
#include "core_includes.h"

FScrollView::FScrollView()
{
    mRecievesConsumedTouches = true;
    mClipsContent = true;
    
    mName = "Scroll View";
    
    mScrollActionScale = 1.0f;
    
    mScrollUpdateFlingDecayMultiply = 0.940f;
    mScrollUpdateFlingDecaySubtract = 0.10f;
    
    mScrollMaxDistance = 240.0f;
    
    mScrollHorizontalEnabled = true;
    mScrollVerticalEnabled = true;
    
    mScrollHorizontalDisabledIfTooSmall = true;
    mScrollVerticalDisabledIfTooSmall = true;
    
    for(int i=0;i<2;i++)
    {
        mScrollOffset[i] = 0.0f;
        
        mScrollTargetOffset[0] = 0.0f;
        
        mScrollFlingSpeed = 0.0f;
        mScrollFlingDir[i] = 0.0f;
        mScrollFlingDir[i] = 0.0f;
        
        mScrollContentSizeWidth = 0.0f;
        mScrollContentSizeHeight = 0.0f;
        
        mScrollMinOffset[i] = 0.0f;
        
        mScrollBounceBackStartOffset[i] = 0.0f;
        mScrollBounceBackFinishOffset[i] = 0.0f;
        mScrollBounceBackStartSpeed[i] = 0.0f;
        mScrollBounceBackFinishSpeed[i] = 0.0f;
        
        mScrollBounceBackTimeTotal[i] = 0;
        mScrollBounceBackTime[i] = 0;
        
        
        mScrollBounceBackAdjustmentPre[i] = 0.0f;
        mScrollBounceBackAdjustmentPost[i] = 0.0f;
    }
    
}

FScrollView::~FScrollView()
{
    
}

void FScrollView::BaseUpdate()
{
    
    FGestureView::BaseUpdate();
    
    if(GetTransformScale() > 0.01f)
    {
        
        mScrollActionScale = (1.0f / GetTransformScale());
        
    }
    
    bool aAnimatingBefore = ScrollIsAnimating();
    
    /*
    
    for(int i=0;i<2;i++)
    {
        if(mScrollMinOffset[i] >= 0)
        {
            mScrollOffset[i] = 0.0f;
            
            mScrollTargetOffset[0] = 0.0f;
            
            mScrollFlingSpeed = 0.0f;
            mScrollFlingDir[i] = 0.0f;
            mScrollFlingDir[i] = 0.0f;
            
            mScrollBounceBackStartOffset[i] = 0.0f;
            mScrollBounceBackFinishOffset[i] = 0.0f;
            mScrollBounceBackStartSpeed[i] = 0.0f;
            mScrollBounceBackFinishSpeed[i] = 0.0f;
            
            mScrollBounceBackTimeTotal[i] = 0;
            mScrollBounceBackTime[i] = 0;
            
            mScrollBounceBackAdjustmentPre[i] = 0.0f;
            mScrollBounceBackAdjustmentPost[i] = 0.0f;
        }
    }
     
    */
    
    for(int i=0;i<2;i++)
    {
        if(mScrollBounceBackTimeTotal[i] > 0)
        {
            mScrollBounceBackTime[i]++;
            
            if(mScrollBounceBackTime[i] >= mScrollBounceBackTimeTotal[i])
            {
                mScrollBounceBackTimeTotal[i] = 0.0f;
                
                mScrollOffset[i] = (mScrollBounceBackFinishOffset[i] + mScrollBounceBackAdjustmentPost[i]);
                
                float aMoveX = mScrollFlingDir[0] * mScrollFlingSpeed;
                float aMoveY = mScrollFlingDir[1] * mScrollFlingSpeed;
                
                if(i == 0)
                {
                    aMoveX = mScrollBounceBackFinishSpeed[i];
                }
                else
                {
                    aMoveY = mScrollBounceBackFinishSpeed[i];
                }
                
                float aLength = aMoveX * aMoveX + aMoveY * aMoveY;
                
                if(aLength > 0.25f)
                {
                    aLength = sqrtf(aLength);
                    
                    aMoveX /= aLength;
                    aMoveY /= aLength;
                    
                    mScrollFlingDir[0] = aMoveX;
                    mScrollFlingDir[1] = aMoveY;
                    
                    mScrollFlingSpeed = aLength;
                }
                else
                {
                    mScrollFlingDir[i] = 0.0f;
                }
                
            }
            else
            {
                float aPercent = ((float)mScrollBounceBackTime[i]) / ((float)mScrollBounceBackTimeTotal[i]);
                float aPercentInv = 1.0f - aPercent;
                
                int aMagicTickNumber = 10;
                
                float aAdjustmentPercentPre = ((float)mScrollBounceBackTime[i]) / ((float)aMagicTickNumber);
                
                float aAdjustmentPercentPost = ((float)(mScrollBounceBackTimeTotal[i] - mScrollBounceBackTime[i])) / ((float)aMagicTickNumber);
                
                if((aAdjustmentPercentPost >= 0) && (aAdjustmentPercentPost <= 1.0f))
                {
                    mScrollBounceBackAdjustmentPost[i] += aAdjustmentPercentPost * mScrollBounceBackFinishSpeed[i];
                }
                
                aAdjustmentPercentPre = (1 - aAdjustmentPercentPre);
                
                if(aAdjustmentPercentPre >= 0.0f)
                {
                    mScrollBounceBackAdjustmentPre[i] += mScrollBounceBackStartSpeed[i] * aAdjustmentPercentPre;
                }
                
                float aOffset = mScrollBounceBackStartOffset[i] + (mScrollBounceBackFinishOffset[i] - mScrollBounceBackStartOffset[i]) * aPercent;
                
                aOffset += mScrollBounceBackAdjustmentPre[i] * aPercentInv;
                aOffset += mScrollBounceBackAdjustmentPost[i] * aPercent;
                
                mScrollOffset[i] = aOffset;
            }
        }
        else if(mScrollFlingSpeed > 0)
        {
            float aMove = mScrollFlingDir[i] * mScrollFlingSpeed;
            
            mScrollOffset[i] += aMove;
            mScrollTargetOffset[i] = mScrollOffset[i];
            
            if(PositionIsOutOfBoundsOver(mScrollOffset[i], i))
            {
                ScrollBounce(i);
            }
            else if(PositionIsOutOfBoundsUnder(mScrollOffset[i], i))
            {
                ScrollBounce(i);
            }
        }
    }
    
    if(mScrollFlingSpeed > 0)
    {
        mScrollFlingSpeed *= mScrollUpdateFlingDecayMultiply;
        mScrollFlingSpeed -= mScrollUpdateFlingDecaySubtract;
    
        if(mScrollFlingSpeed < 0.0f)mScrollFlingSpeed = 0.0f;
    }
    
    
    bool aAnimatingAfter = ScrollIsAnimating();
    
    if((aAnimatingBefore == true) && (aAnimatingAfter == false))
    {
        ScrollFinished();
        this->ScrollFinished();
    }
    
    
    
    float aTranslateX = mScrollOffset[0];
    float aTranslateY = mScrollOffset[1];
    
    if(mScrollHorizontalEnabled == false)aTranslateX = 0.0f;
    if(mScrollVerticalEnabled == false)aTranslateY = 0.0f;
    
    EnumList(FView, aView, mSubviews)
    {
        
        //mScrollVerticalEnabled
        
        
        
        
        
        
        aView->SetTransformTranslate(aTranslateX, aTranslateY);
        
        
        //mScrollHorizontalDisabledIfTooSmall = true;
        //mScrollVerticalDisabledIfTooSmall = true;
        
        
        /*
        aView-
        aView->BaseParentTransformChanged(mAbsoluteOriginX, mAbsoluteOriginY, mAbsoluteScale);
        aView->SetTransform(mScrollOffset[0], mScrollOffset[1], 1.0f);
        
        if(aView->mKill == 0)
        {
            aView->BaseDraw();
        }
         
        */
        
    }
    
    
}


void FScrollView::BaseDraw()
{
    
    Draw();
    

    
    /*
    //ComputeAbsoluteTransformations();
    
    Graphics::ClipEnable();
    Graphics::Clip(mAbsoluteOriginX, mAbsoluteOriginY, mAbsoluteWidth, mAbsoluteHeight);
    
    BaseDrawTransform();
    Draw();
    
    Graphics::SetColor();
    
    
    EnumList(FView, aView, mSubviews)
    {
        aView->BaseParentTransformChanged(mAbsoluteOriginX, mAbsoluteOriginY, mAbsoluteScale);
        aView->SetTransform(mScrollOffset[0], mScrollOffset[1], 1.0f);
        
        if(aView->mKill == 0)
        {
            aView->BaseDraw();
        }
    }
    
    Graphics::ClipDisable();
    
    
    */
    
    
    
    /*
    Graphics::SetColor(0.75f, 0.45f, 0.15f, 0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    //BaseDrawTransform();
    
    
    Graphics::SetColor(1.0f, 0.5f, 0.0f);
    for(int i=0;i<mTouchCount;i++)
    {
        float aHistoryCount = ((float)(mTouch[i]->mHistoryMoveCount + 1));
        
        for(int k=0;k<mTouch[i]->mHistoryMoveCount;k++)
        {
            float aPercent = ((float)k) / aHistoryCount;
            
            Graphics::DrawPoint(mTouch[i]->mHistoryMoveX[k], mTouch[i]->mHistoryMoveY[k], 5 + aPercent * 25);
        }
    }
    
    Graphics::SetColor(1.0f, 0.0f, 1.0f, 0.85f);
    for(int i=0;i<mTouchCount;i++)
    {
        Graphics::DrawPoint(mTouch[i]->mX, mTouch[i]->mY, 40);
    }
    
    Graphics::SetColor();
    */
    
}

void FScrollView::BaseDrawOver()
{
    //DrawOver();
    
    Graphics::SetColor(1.0f, 0.25f, 0.77f, 0.5f);
    Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 5.0f);
    
}

//void FScrollView::BaseTouchDown(float pX, float pY, void *pData)

void FScrollView::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData)
{
    mScrollFlingSpeed = 0.0f;
    
    mScrollBounceBackTimeTotal[0] = 0;
    mScrollBounceBackTime[0] = 0;
    
    mScrollBounceBackTimeTotal[1] = 0;
    mScrollBounceBackTime[1] = 0;
    
    FGestureView::BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData);
}

void FScrollView::PanBegin(float pX, float pY)
{
    
    mScrollTargetOffset[0] = mScrollOffset[0];
    mScrollTargetOffset[1] = mScrollOffset[1];
    
}

void FScrollView::Pan(float pX, float pY)
{
    mScrollFlingSpeed = 0;
    
    mScrollTargetOffset[0] += pX;// * mScrollActionScale;
    mScrollTargetOffset[1] += pY;// * mScrollActionScale;
    
    //Split all this functionality into a separate function, which is also called on release -
    
    for(int i=0;i<2;i++)
    {
        
    mScrollOffset[i] = mScrollTargetOffset[i];
    
    if(mScrollTargetOffset[i] < mScrollMinOffset[i])
    {
        float aShift = (mScrollMinOffset[i] - mScrollTargetOffset[i]);
        mScrollOffset[i] = (mScrollMinOffset[i] - ScrollGetBounceDragShift(aShift));
        
        //mScrollOffsetX = mScrollMinOffsetX;
    }
    if(mScrollTargetOffset[i] > 0.0f)
    {
        float aShift = mScrollTargetOffset[i];
        mScrollOffset[i] = ScrollGetBounceDragShift(aShift);
    }
        
    }
}

void FScrollView::ScrollFinished()
{
    //Log("FScrollView::ScrollFinished()\n");
    
}

bool FScrollView::ScrollIsAnimating()
{
    bool aReturn = false;
    
    if(mScrollFlingSpeed > 0)aReturn = true;
    
    for(int i=0;i<2;i++)
    {
        if(mScrollBounceBackTimeTotal[i] > 0)aReturn = true;
    }
    
    return aReturn;
}

void FScrollView::ScrollBounce(int pIndex)
{
    float aStickSpeedThreshold = 40.0f;
    
    mScrollBounceBackAdjustmentPre[pIndex] = 0.0f;
    mScrollBounceBackAdjustmentPost[pIndex] = 0.0f;
    
    mScrollBounceBackStartOffset[pIndex] = mScrollOffset[pIndex];
    
    mScrollBounceBackTime[pIndex] = 0;
    mScrollBounceBackTimeTotal[pIndex] = (8 + (mScrollFlingSpeed / 3.0f));
    
    
    
    bool aBouncesAway = false;
    
    float aSpeed = mScrollFlingSpeed * mScrollFlingDir[pIndex];
    
    mScrollBounceBackStartSpeed[pIndex] = aSpeed;
    
    if(fabsf(aSpeed) >= aStickSpeedThreshold)aBouncesAway = true;
    
    
    //if(mScrollOffsetX <=
    
    
    int aBounceDir = 0;
    
    if(mScrollOffset[pIndex] >= 0)
    {
        aBounceDir = -1;
        
        mScrollBounceBackFinishOffset[pIndex] = 0.0f;
        
        if(aSpeed < 0)
        {
            int aExtra = (int)(-(aSpeed / 4));
            if(aExtra > 20)aExtra = 20;
            mScrollBounceBackTimeTotal[pIndex] += aExtra;
            
        }
    }
    else
    {
        aBounceDir = 1;
        
        mScrollBounceBackFinishOffset[pIndex] = mScrollMinOffset[pIndex];
        
        //if(mScrollOffset[pIndex] <= (mScrollMinOffset[pIndex] - aStickDistanceThreshold))
        //{
        //    aBouncesAway = true;
        //}
        
        if(aSpeed > 0)
        {
            int aExtra = (int)(aSpeed / 4);
            if(aExtra > 20)aExtra = 20;
            mScrollBounceBackTimeTotal[pIndex] += aExtra;
            
        }
        
        
    }
    
    
    mScrollBounceBackFinishSpeed[pIndex] = 0.0f;
    
    if(aBouncesAway)
    {
        float aBounceAwaySpeed = ((float)mScrollBounceBackTimeTotal[pIndex]) / 3.0f;
        
        if(aBounceDir == -1)aBounceAwaySpeed = (-aBounceAwaySpeed);
        
        //if(aBounceAwaySpeed < 5.0f)aBounceAwaySpeed = 5.0f;
        
        mScrollBounceBackFinishSpeed[pIndex] = aBounceAwaySpeed;
    }
    
    //Log("BounceX Dir[%d] T[%d] Tar[%f]\n", aBounceDir, mScrollBounceBackTimeTotal[0], mScrollBounceBackFinishOffset[0] );
    
}

void FScrollView::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY)
{
    float aSpeed = pSpeedX * pSpeedX + pSpeedY * pSpeedY;
    
    if(aSpeed > 0.1f)
    {
        
        aSpeed = sqrtf(aSpeed);
        
        pSpeedX /= aSpeed;
        pSpeedY /= aSpeed;
    }
    
    mScrollFlingDir[0] = (pSpeedX);
    mScrollFlingDir[1] = (pSpeedY);
    
    mScrollFlingSpeed = aSpeed;
    
    if(mScrollFlingSpeed > 50.0f)
    {
        mScrollFlingSpeed = 50.0f;
    }
    
    
    float aDestination[2];
    
    //mNaturalFlingTo[0] = mScrollOffset[0];
    //mNaturalFlingTo[1] = mScrollOffset[1];
    
    aDestination[0] = mScrollOffset[0];
    aDestination[1] = mScrollOffset[1];
    
    
    float aFlingSpeed = mScrollFlingSpeed;
    
    int aLoops = 0;
    
    
    while(aFlingSpeed > 0.0f)
    {
        aLoops++;
        
        float aMoveX = mScrollFlingDir[0] * aFlingSpeed;
        float aMoveY = mScrollFlingDir[1] * aFlingSpeed;
        
        aDestination[0] += aMoveX;
        aDestination[1] += aMoveY;
        
        aFlingSpeed *= mScrollUpdateFlingDecayMultiply;
        aFlingSpeed -= mScrollUpdateFlingDecaySubtract;
    }
    
    //Log("Fling Will Go [%d Loops] To [%f %f]\n", aLoops, mNaturalFlingTo[0], mNaturalFlingTo[1]);
    
    
    
    for(int i=0;i<2;i++)
    {
        bool aBounce = false;
        
        if(PositionIsOutOfBoundsOver(mScrollOffset[i], i))
        {
            if(PositionIsOutOfBoundsOver(aDestination[i], i))
            {
                
                aBounce = true;
            }
        }
        
        if(PositionIsOutOfBoundsUnder(mScrollOffset[i], i))
        {
            if(PositionIsOutOfBoundsUnder(aDestination[i], i))
            {
                aBounce = true;
            }
        }
        
        if(aBounce)
        {
            ScrollBounce(i);
        }
    }
    
    
    /*
    
    mScrollBounceBackStartOffsetX = 0.0f;
    mScrollBounceBackStartOffsetY = 0.0f;
    
    mScrollBounceBackStartSpeedX = 0.0f;
    mScrollBounceBackStartSpeedY = 0.0f;
    
    mScrollBounceBackTimeTotal = 0.0f;
    mScrollBounceBackTime = 0.0f;
    
    */
    
    
    
}

void FScrollView::SetContentSize(float pWidth, float pHeight)
{
    mScrollContentSizeWidth = pWidth;
    mScrollContentSizeHeight = pHeight;
    
    if(mScrollContentSizeWidth > mWidth)
    {
        mScrollMinOffset[0] = (mWidth - mScrollContentSizeWidth);
    }
    else
    {
        mScrollMinOffset[0] = 0.0f;
    }
    
    
    
    if(mScrollContentSizeHeight > mHeight)
    {
        mScrollMinOffset[1] = (mHeight - mScrollContentSizeHeight);
    }
    else
    {
        mScrollMinOffset[1] = 0.0f;
    }
    
}

/*
void FScrollView::ComputeAbsoluteTransformations()
{
    
    mAbsoluteScale = mParentTransformScale * mTransformScale;
    
    mAbsoluteOriginX = ((mX + mTransformTranslateX) * mParentTransformScale + mParentTransformTranslateX);
    mAbsoluteOriginY = ((mY + mTransformTranslateY) * mParentTransformScale + mParentTransformTranslateY);
    
    mAbsoluteWidth = mWidth * mAbsoluteScale;
    mAbsoluteHeight = mHeight * mAbsoluteScale;
    
    mScrollAbsoluteScale = mAbsoluteScale;
    
    mScrollAbsoluteOriginX = ((mX + mScrollOffsetX) * mParentTransformScale + mParentTransformTranslateX) + mTransformTranslateX;
    mScrollAbsoluteOriginY = ((mY + mScrollOffsetY) * mParentTransformScale + mParentTransformTranslateY) + mTransformTranslateY;
    
    mScrollAbsoluteWidth = 100.0f;
    mScrollAbsoluteHeight = 100.0f;
    
}

*/



float FScrollView::ScrollGetBounceDragShift(float pAmount)
{
    float aReturn = pAmount;
    
    float aMaxShift = mScrollMaxDistance;
    float aMaxDrag = (gDeviceWidth * 0.75f);
    
    bool aNegative = (pAmount < 0.0f);
    
    if(aNegative)
    {
        pAmount = (-pAmount);
    }
    
    if(pAmount >= aMaxDrag)
    {
        aReturn = aMaxShift;
    }
    else
    {
        float aPercent = (pAmount / aMaxDrag);
        
        float aRads = (3.1415926535897932384626433832795028841968f / 2.0f) * aPercent;
        aReturn = sin(aRads) * aMaxShift;
    }
    
    if(aNegative)aReturn = (-aReturn);
    
    return aReturn;
}

bool FScrollView::PositionIsOutOfBoundsOver(float pValue, int pIndex)
{
    return (pValue > 0.0f);
}

bool FScrollView::PositionIsOutOfBoundsUnder(float pValue, int pIndex)
{
    return (pValue < mScrollMinOffset[pIndex]);
}
