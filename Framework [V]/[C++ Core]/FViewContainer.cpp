//
//  FViewContainer.cpp
//  RaptisGame
//
//  Created by Nick Raptis on 3/13/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FViewContainer.h"
#include "FView.h"
#include "FViewController.h"
#include "FAnimation.h"
#include "FApp.h"

#include "core_includes.h"


FViewContainer::FViewContainer(FView *pView)
{
    mView = pView;
    
    //mZIndex = 0;
    
    mKill = 0;
    
    //mModal = false;
    
    mStaticTransform = false;
    
    mParent = 0;
    //mChildIndex = -1;
    
    //mChild = 0;
    //mChildListCount = 0;
    //mChildListSize = 0;
    //mChildListIsSorted = true;
    
    //mViewAnimation = 0;
    
    mRefresh = true;
    mRefreshTransformations = false;
    
    mDidUpdate = false;
    mDidDraw = false;
    
    for(int i=0;i<VIEW_MAX_TOUCH_COUNT;i++)
    {
        mTouchData[i] = 0;
        mTouchInside[i] = false;
        
    }
}

FViewContainer::~FViewContainer()
{
    
}

void FViewContainer::Update()
{
    //if(mView)
    //{
    
    /*
     if(mViewAnimation)
     {
     bool aFinished = false;
     float aAnimationPercent = 0.0f;
     
     mViewAnimation->mTimerTick++;
     if(mViewAnimation->mTime > 0)
     {
     
     aAnimationPercent = mViewAnimation->mPercent[mViewAnimation->mTimerTick];;
     
     //aAnimationPercent = ((float)mViewAnimation->mTimerTick) / ((float)mViewAnimation->mTime);
     
     //aAnimationPercent = FAnimation::EaseInSine(aAnimationPercent);
     //aAnimationPercent = FAnimation::EaseOutQuint(aAnimationPercent);
     
     //aAnimationPercent = FAnimation::EaseInOutSine(aAnimationPercent);
     
     if(mViewAnimation->mTimerTick >= mViewAnimation->mTime)
     {
     aFinished = true;
     }
     }
     else
     {
     aFinished = true;
     }
     
     if(aFinished)
     {
     bool aKillAfter = mViewAnimation->mKillAfter;
     
     SetTransformX(mViewAnimation->mTargetX);
     SetTransformY(mViewAnimation->mTargetY);
     SetTransformScale(mViewAnimation->mTargetScale);
     SetTransformScaleX(mViewAnimation->mTargetScaleX);
     SetTransformScaleY(mViewAnimation->mTargetScaleY);
     SetTransformRotation(mViewAnimation->mTargetRotation);
     SetTransformAnchorX(mViewAnimation->mTargetAnchorX);
     SetTransformAnchorY(mViewAnimation->mTargetAnchorY);
     
     
     if(mView)
     {
     mView->AnimationComplete(mViewAnimation, mViewAnimation->mID);
     }
     
     
     delete mViewAnimation;
     mViewAnimation = 0;
     
     if(aKillAfter)
     {
     Log("Animation Auto-Kill [%s]\n\n", mView->mName.c());
     
     mView->Kill();
     
     return;
     }
     }
     else
     {
     SetTransformX(mViewAnimation->mStartX + (mViewAnimation->mTargetX - mViewAnimation->mStartX) * aAnimationPercent);
     SetTransformY(mViewAnimation->mStartY + (mViewAnimation->mTargetY - mViewAnimation->mStartY) * aAnimationPercent);
     
     
     
     SetTransformScale(mViewAnimation->mStartScale + (mViewAnimation->mTargetScale - mViewAnimation->mStartScale) * aAnimationPercent);
     SetTransformScaleX(mViewAnimation->mStartScaleX + (mViewAnimation->mTargetScaleX - mViewAnimation->mStartScaleX) * aAnimationPercent);
     SetTransformScaleY(mViewAnimation->mStartScaleY + (mViewAnimation->mTargetScaleY - mViewAnimation->mStartScaleY) * aAnimationPercent);
     
     SetTransformRotation(mViewAnimation->mStartRotation + (mViewAnimation->mTargetRotation - mViewAnimation->mStartRotation) * aAnimationPercent);
     
     SetTransformAnchorX(mViewAnimation->mStartAnchorX + (mViewAnimation->mTargetAnchorX - mViewAnimation->mStartAnchorX) * aAnimationPercent);
     SetTransformAnchorY(mViewAnimation->mStartAnchorY + (mViewAnimation->mTargetAnchorY - mViewAnimation->mStartAnchorY) * aAnimationPercent);
     }
     }
     */
    
    mView->BaseUpdate();
    mDidUpdate = true;
    //}
    
    
    for(int i=0;i<mView->mSubviews.mCount;i++)
    {
        ((FView *)(mView->mSubviews.Fetch(i)))->GetContainer()->Update();
    }
    
}

//void FViewContainer::Draw(int pLevel)
void FViewContainer::Draw()
{
    if(mDidUpdate)
    {
        mDidDraw = true;
        
        //if(mView)
        //{
        if(mView->mHidden == false)
        {
            DrawTransform();
            
            if(mView->mClipsContent)
            {
                Graphics::ClipEnable();
                Graphics::Clip(0.0f, 0.0f, mView->mWidth, mView->mHeight);
            } else {
                Graphics::ClipDisable();
            }
            
            //if(pLevel == 0)mView->BaseDraw();
            
            mView->BaseDraw();
            
            //for(int aModalIndex=0;aModalIndex<2;aModalIndex++)
            //{
            //bool aModalCheck = false;
            //if(aModalIndex == 1)aModalCheck = true;
            
            for(int i = 0; i<mView->mSubviews.mCount; i++)
            {
                FView *aSub = ((FView *)(mView->mSubviews.Fetch(i)));
                FViewContainer *aCtr = aSub->GetContainer();
                
                //if(aCtr->IsModal() == aModalCheck)
                //{
                if(aSub->mDrawManual == false)
                {
                    //aCtr->Draw(pLevel);
                    aCtr->Draw();
                    
                }
                //}
            }
            //}
            
            if(mView->mClipsContent)
            {
                Graphics::ClipDisable();
            }
        }
    }
    //}
}

void FViewContainer::DrawManualBegin()
{
    if((mDidUpdate == true) && (mView != 0))
    {
        DrawTransform();
        
        if(mView->mClipsContent)
        {
            Graphics::ClipEnable();
            Graphics::Clip(0.0f, 0.0f, mView->mWidth, mView->mHeight);
        }
        
        
        
        
    }
}

void FViewContainer::DrawManualEnd()
{
    if((mDidUpdate == true) && (mView != 0))
    {
        if(mView->mClipsContent)
        {
            Graphics::ClipDisable();
        }
        
        mDidDraw = true;
    }
}

void FViewContainer::DrawManualSubviews()
{
    if((mDidUpdate == true) && (mView != 0))
    {
        //for(int aModalIndex=0;aModalIndex<2;aModalIndex++)
        //{
        //bool aModalCheck = false;
        //if(aModalIndex == 1)aModalCheck = true;
        
        for(int i = 0; i<mView->mSubviews.mCount; i++)
        {
            FView *aSub = ((FView *)(mView->mSubviews.Fetch(i)));
            FViewContainer *aCtr = aSub->GetContainer();
            
            
            if(aSub->mDrawManual == false)
            {
                //aCtr->Draw(0);
                aCtr->Draw();
                
            }
            
            
        }
        //}
    }
}

FViewContainer *FViewContainer::TouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pClippedByParent, bool &pConsumed)
{
    FViewContainer *aReturn = 0;
    FViewContainer *aCollideContainer = 0;
    
    
    if(mView->mEnabled)
    {
        
        bool aContainsTouch = false;// mTransformAbsolute.ContainsPoint(pX, pY);
        
        if((pConsumed == true) && (mView->mRecievesConsumedTouches == false))
        {
            aContainsTouch = false;
        }
        else
        {
            aContainsTouch = false;
            
            if(pClippedByParent)
            {
                aContainsTouch = false;
            }
            else
            {
                aContainsTouch = mTransformAbsolute.ContainsPoint(pX, pY);
                if(aContainsTouch == false)
                {
                    if(mView->mClipsContent)
                    {
                        pClippedByParent = true;
                    }
                }
            }
        }
        
        
        //for(int aModalIndex=0;aModalIndex<2;aModalIndex++)
        //{
        //bool aModalCheck = true;
        //if(aModalIndex == 1)aModalCheck = false;
        
        for(int i=(mView->mSubviews.mCount - 1);i>=0;i--)
        {
            FView *aSub = ((FView *)(mView->mSubviews.Fetch(i)));
            FViewContainer *aCtr = aSub->GetContainer();
            
            //if(aCtr->IsModal() == aModalCheck)
            //{
            aCollideContainer = aCtr->TouchDown(pX, pY, pOriginalX, pOriginalY, pData, pClippedByParent, pConsumed);
            
            if(aCollideContainer != 0)
            {
                if(mView->ShouldReceieveTouch(aCollideContainer->mView, aContainsTouch) == false)
                {
                    aContainsTouch = false;
                }
                
                if(aCollideContainer->mView)
                {
                    if(aCollideContainer->mView->mConsumesTouches)
                    {
                        pConsumed = true;
                        
                        if(aReturn == 0)
                        {
                            aReturn = aCollideContainer;
                        }
                        
                        if((mView->mRecievesOutsideTouches == false) && (mView->mRecievesConsumedTouches == false))
                        {
                            aContainsTouch = false;
                        }
                    }
                }
            }
        }
        //}
        //}
        
        if((mView->mRecievesConsumedTouches == true) || (pConsumed == false))
        {
            if((aContainsTouch == true) || (mView->mRecievesOutsideTouches == true))
            {
                if(aContainsTouch)
                {
                    mView->mTouchDownInside = true;
                }
                
                mView->mTouchDown = true;
                
                if(mView->mTouchCount < VIEW_MAX_TOUCH_COUNT)
                {
                    mTouchData[mView->mTouchCount] = pData;
                    
                    if(aContainsTouch == true)
                    {
                        if(aReturn == 0)
                        {
                            aReturn = this;
                        }
                        
                        mTouchInside[mView->mTouchCount] = true;
                        mView->mTouchDownInside = true;
                    }
                    else
                    {
                        mTouchInside[mView->mTouchCount] = false;
                        
                        mView->mTouchDown = true;
                        
                        bool aAnyTouchesInside = false;
                        for(int i=0;i<mView->mTouchCount;i++)
                        {
                            if(mTouchInside[i] == true)aAnyTouchesInside = true;
                        }
                        
                        if(aAnyTouchesInside)mView->mTouchDownInside = true;
                        else mView->mTouchDownInside = false;
                    }
                    
                    mView->mTouchCount++;
                    
                    float aX = pX;
                    float aY = pY;
                    
                    TransformTouch(aX, aY);
                    
                    mView->mTouchDown = true;
                    mView->BaseTouchDown(aX, aY, pX, pY, pData);
                    
                    if(mView->mDragFrameMode)
                    {
                        mDraggingFrame = true;
                        mDraggingFrameData = pData;
                        
                        mDraggingFrameStartX = mView->mX;
                        mDraggingFrameStartY = mView->mY;
                        
                        mDraggingFrameTouchStartX = pOriginalX;
                        mDraggingFrameTouchStartY = pOriginalY;
                    }
                }
            }
        }
    }
    else
    {
        if(mView->mEnabled)
        {
            TouchFlush();
        }
    }
    
    return aReturn;
}

void FViewContainer::TouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pClippedByParent)
{
    if(mView->mEnabled)
    {
        
        int aTouchIndex = -1;
        
        for(int i=0;i<mView->mTouchCount;i++)
        {
            if(mTouchData[i] == pData)
            {
                aTouchIndex = i;
            }
        }
        
        bool aContainsTouch = false;
        
        if(pClippedByParent)
        {
            aContainsTouch = false;
        }
        else
        {
            aContainsTouch = mTransformAbsolute.ContainsPoint(pX, pY);
            if(aContainsTouch == false)
            {
                if(mView->mClipsContent)
                {
                    pClippedByParent = true;
                }
            }
        }
        
        for(int i = (mView->mSubviews.mCount - 1); i >= 0; i--)
        {
            FView *aSub = ((FView *)(mView->mSubviews.Fetch(i)));
            FViewContainer *aCtr = aSub->GetContainer();
            
            aCtr->TouchMove(pX, pY, pOriginalX, pOriginalY, pData, pClippedByParent);
        }
        
        if(aTouchIndex >= 0)
        {
            if(aContainsTouch)
            {
                mTouchInside[aTouchIndex] = true;
                mView->mTouchDownInside = true;
            }
            else
            {
                mTouchInside[aTouchIndex] = false;
                
                bool aAnyTouchesInside = false;
                for(int i=0;i<mView->mTouchCount;i++)
                {
                    if(mTouchInside[i] == true)aAnyTouchesInside = true;
                }
                if(aAnyTouchesInside)
                {
                    mView->mTouchDownInside = true;
                }
                else
                {
                    mView->mTouchDownInside = false;
                }
            }
            
            float aX = pX;
            float aY = pY;
            
            TransformTouch(aX, aY);
            mView->BaseTouchMove(aX, aY, pX, pY, pData);
            
            
            
            if((mView->mDragFrameMode) && (mDraggingFrameData == pData))
            {
                float aDiffX = (mDraggingFrameTouchStartX - pOriginalX);
                float aDiffY = (mDraggingFrameTouchStartY - pOriginalY);
                
                float aTargetX = (mDraggingFrameStartX - aDiffX);
                float aTargetY = (mDraggingFrameStartY - aDiffY);
                
                if(aTargetX < 0)aTargetX = 0;
                if(aTargetY < 0)aTargetY = 0;
                
                SetFrameX(aTargetX);
                SetFrameY(aTargetY);
            }
        }
    }
    else
    {
        if(mView->mEnabled)
        {
            TouchFlush();
        }
    }
}

void FViewContainer::TouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pClippedByParent)
{
    int aTouchIndex = -1;
    
    for(int i=0;i<mView->mTouchCount;i++)
    {
        if(mTouchData[i] == pData)
        {
            aTouchIndex = i;
        }
    }
    
    if(aTouchIndex >= 0)
    {
        for(int i=aTouchIndex;i<(mView->mTouchCount - 1);i++)
        {
            mTouchData[i] = mTouchData[i + 1];
            mTouchInside[i] = mTouchInside[i + 1];
        }
        
        mView->mTouchCount--;
    }
    
    if(mView->mEnabled)
    {
        bool aContainsTouch = false;
        
        if(pClippedByParent)
        {
            aContainsTouch = false;
        }
        else
        {
            aContainsTouch = mTransformAbsolute.ContainsPoint(pX, pY);
            if(aContainsTouch == false)
            {
                if(mView->mClipsContent)
                {
                    pClippedByParent = true;
                }
            }
        }
        
        for(int i = (mView->mSubviews.mCount - 1); i >= 0; i--)
        {
            FView *aSub = ((FView *)(mView->mSubviews.Fetch(i)));
            FViewContainer *aCtr = aSub->GetContainer();
            aCtr->TouchUp(pX, pY, pOriginalX, pOriginalY, pData, pClippedByParent);
        }
        
        if(aContainsTouch)
        {
            mView->mMouseOver = true;
        }
        else
        {
            mView->mMouseOver = false;
        }
        
        if(mView->mTouchCount <= 0)
        {
            mView->mTouchDown = false;
            mView->mTouchDownInside = false;
        }
        else
        {
            bool aAnyTouchesInside = false;
            for(int i=0;i<mView->mTouchCount;i++)
            {
                if(mTouchInside[i] == true)aAnyTouchesInside = true;
            }
            if(aAnyTouchesInside)
            {
                mView->mTouchDownInside = true;
            }
            else
            {
                mView->mTouchDownInside = false;
            }
        }
        
        if(aTouchIndex >= 0)
        {
            float aX = pX;
            float aY = pY;
            
            TransformTouch(aX, aY);
            mView->BaseTouchUp(aX, aY, pX, pY, pData);
            
        }
    }
    else
    {
        if(mView->mEnabled)
        {
            TouchFlush();
        }
    }
    
    if(mDraggingFrame == true)
    {
        mDraggingFrame = false;
        mDraggingFrameData = 0;
        
        mDraggingFrameStartX = 0.0f;
        mDraggingFrameStartY = 0.0f;
        
        mDraggingFrameTouchStartX = 0.0f;
        mDraggingFrameTouchStartY = 0.0f;
    }
    
}

void FViewContainer::TouchFlush()
{
    for(int i = 0; i < mView->mSubviews.mCount; i++)
    {
        FViewContainer *aCtr = ((FView *)(mView->mSubviews.Fetch(i)))->GetContainer();
        
        aCtr->TouchFlush();
    }
    
    if(mView)
    {
        mView->mTouchDown = false;
        mView->mTouchDownInside = false;
        mView->mTouchCount = 0;
        mView->mMouseOver = false;
        mView->BaseTouchFlush();
    }
}

void FViewContainer::MouseWheel(int pDirection)
{
    for(int i = 0; i<mView->mSubviews.mCount; i++)
    {
        FViewContainer *aCtr = ((FView *)(mView->mSubviews.Fetch(i)))->GetContainer();
        aCtr->MouseWheel(pDirection);
    }
    if(mView)
    {
        mView->MouseWheel(pDirection);
    }
}

void FViewContainer::KeyDown(int pKey)
{
    for(int i = 0; i<mView->mSubviews.mCount; i++)
    {
        FViewContainer *aCtr = ((FView *)(mView->mSubviews.Fetch(i)))->GetContainer();
        aCtr->KeyDown(pKey);
    }
    if(mView)
    {
        mView->KeyDown(pKey);
    }
}

void FViewContainer::KeyUp(int pKey)
{
    for(int i = 0; i<mView->mSubviews.mCount; i++)
    {
        FViewContainer *aCtr = ((FView *)(mView->mSubviews.Fetch(i)))->GetContainer();
        aCtr->KeyUp(pKey);
    }
    if(mView)
    {
        mView->KeyUp(pKey);
    }
}

void FViewContainer::MemoryWarning(bool pSevere)
{
    
}

void FViewContainer::Inactive()
{
    
    //mView->Inactive();
}

void FViewContainer::Active() {
    
}

void FViewContainer::DrawTransform() {

    /*
    FMatrix aOrtho = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -2048.0f, 2048.0f);
    Graphics::SetMatrixProjection(aOrtho);

    float aX = mTransformAbsolute.mX;
    float aY = mTransformAbsolute.mY;
    if (aX != 0.0f || aY != 0.0f) {
        Graphics::Translate(aX, aY, 0.0f);
    }

    float aRotation = mTransformAbsolute.mRotation;
    if (aRotation != 0.0f) {
        Graphics::Rotate(aRotation);
    }
    
    float aScaleX = mTransformAbsolute.mScale * mTransformAbsolute.mScaleX;
    float aScaleY = mTransformAbsolute.mScale * mTransformAbsolute.mScaleY;
    float aScale = mTransformAbsolute.mScale;
    if (aScaleX != 1.0f || aScaleY != 1.0f || aScale != 1.0f) {
        Graphics::Scale(aScaleX, aScaleY, aScale);
    }

    float aAnchorX = mTransformAbsolute.mAnchorX;
    float aAnchorY = mTransformAbsolute.mAnchorY;
    if ((aAnchorX != 0.0f) || (aAnchorY != 0.0f)) {
        Graphics::Translate(aAnchorX * (-mView->mWidth), aAnchorY * (-mView->mHeight));
    }
    Graphics::ResetMatrixModelView();
*/


    Graphics::MatrixGoProjection();
    Graphics::MatrixLoadIdentity();
    Graphics::Ortho2D(0, gDeviceWidth, gDeviceHeight, 0);
    Graphics::MatrixGoModelView();
    Graphics::MatrixLoadIdentity();

    Graphics::Translate(mTransformAbsolute.mX, mTransformAbsolute.mY, 0.0f);
    Graphics::Rotate(mTransformAbsolute.mRotation);

    Graphics::Scale(mTransformAbsolute.mScale * mTransformAbsolute.mScaleX, mTransformAbsolute.mScale * mTransformAbsolute.mScaleY, mTransformAbsolute.mScale);

    if((mTransformAbsolute.mAnchorX != 0.0f) || (mTransformAbsolute.mAnchorY != 0.0f))
    {
        Graphics::Translate(mTransformAbsolute.mAnchorX * (-mView->mWidth), mTransformAbsolute.mAnchorY * (-mView->mHeight));
    }
    
}

bool FViewContainer::ContainsPoint(float pX, float pY)
{
    return mTransformAbsolute.ContainsPoint(pX, pY);
}

/*
 bool FViewContainer::IsModal()
 {
 bool aReturn = mModal;
 return aReturn;
 }
 
 void FViewContainer::KillModalViews()
 {
 
 
 //#ifdef UTILS_MODE
 
 
 if((mModal == true) && (mView != 0))
 {
 mView->Kill();
 }
 else
 {
 for(int i = 0; i<mView->mSubviews.mCount; i++)
 {
 FView *aSub = ((FView *)(mView->mSubviews.Fetch(i)));
 
 FViewContainer *aCtr = aSub->GetContainer();
 aCtr->KillModalViews();
 
 
 }
 }
 }
 
 
 
 void FViewContainer::FlagAllChildrenAsModal()
 {
 for(int i = 0; i<mView->mSubviews.mCount; i++)
 {
 FView *aSub = ((FView *)(mView->mSubviews.Fetch(i)));
 FViewContainer *aCtr = aSub->GetContainer();
 
 aCtr->mModal = true;
 
 if(aCtr->mView)
 {
 aCtr->mModal = true;
 }
 }
 }
 */

/*
 void FViewContainer::AnimationSetDelay(int pDelayTicks)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mDelay = pDelayTicks;
 }
 
 void FViewContainer::AnimationSetID(int pID)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mID = pID;
 }
 
 int FViewContainer::AnimationGetID()
 {
 int aReturn = VIEW_ANIMATION_NULL;
 if(mViewAnimation != 0)aReturn = mViewAnimation->mID;
 return aReturn;
 }
 
 void FViewContainer::AnimationSetKillAfter(bool pKillAfter)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mKillAfter = pKillAfter;
 }
 
 void FViewContainer::AnimationSetTime(int pTimeTicks)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTime = pTimeTicks;
 }
 
 void FViewContainer::AnimationSetCurve(int pAnimationCurve)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mCurveType = pAnimationCurve;
 }
 
 void FViewContainer::AnimationSetDirectionIn()
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mAnimatingOut = false;
 mViewAnimation->mAnimatingIn = true;
 }
 
 void FViewContainer::AnimationSetDirectionOut()
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mAnimatingOut = true;
 mViewAnimation->mAnimatingIn = false;
 
 }
 
 void FViewContainer::AnimationSetDirectionArbitrary()
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mAnimatingOut = false;
 mViewAnimation->mAnimatingIn = false;
 }
 
 void FViewContainer::AnimationSetAnchorX(float pStartAnchorX, float pTargetAnchorX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartAnchorX = pStartAnchorX;
 mViewAnimation->mTargetAnchorX = pTargetAnchorX;
 }
 
 void FViewContainer::AnimationSetAnchorX(float pTargetAnchorX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetAnchorX = pTargetAnchorX;
 }
 
 void FViewContainer::AnimationSetAnchorXFrom(float pStartAnchorX)
 {
 mViewAnimation->mStartAnchorX = pStartAnchorX;
 if(mView)mViewAnimation->mTargetAnchorX = mView->mTransform.mAnchorX;
 }
 
 void FViewContainer::AnimationSetAnchorY(float pStartAnchorY, float pTargetAnchorY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartAnchorY = pStartAnchorY;
 mViewAnimation->mTargetAnchorY = pTargetAnchorY;
 }
 
 void FViewContainer::AnimationSetAnchorY(float pTargetAnchorY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetAnchorY = pTargetAnchorY;
 }
 
 void FViewContainer::AnimationSetAnchorYFrom(float pStartAnchorY)
 {
 mViewAnimation->mStartAnchorY = pStartAnchorY;
 if(mView)mViewAnimation->mTargetAnchorY = mView->mTransform.mAnchorY;
 }
 
 void FViewContainer::AnimationSetRotation(float pTargetRotation)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetRotation = pTargetRotation;
 }
 
 void FViewContainer::AnimationSetRotation(float pStartRotation, float pTargetRotation)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartRotation = pStartRotation;
 mViewAnimation->mTargetRotation = pTargetRotation;
 }
 
 void FViewContainer::AnimationSetRotationFrom(float pStartRotation)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartRotation = pStartRotation;
 if(mView)mViewAnimation->mTargetRotation = mView->mTransform.mRotation;
 }
 
 
 
 void FViewContainer::AnimationSetScale(float pTargetScale)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetScale = pTargetScale;
 }
 
 void FViewContainer::AnimationSetScale(float pStartScale, float pTargetScale)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartScale = pStartScale;
 mViewAnimation->mTargetScale = pTargetScale;
 }
 
 void FViewContainer::AnimationSetScaleFrom(float pStartScale)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartScale = pStartScale;
 if(mView)mViewAnimation->mTargetScale = mView->mTransform.mScale;
 }
 
 void FViewContainer::AnimationSetScaleX(float pTargetScaleX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetScaleX = pTargetScaleX;
 }
 
 void FViewContainer::AnimationSetScaleX(float pStartScaleX, float pTargetScaleX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartScaleX = pStartScaleX;
 mViewAnimation->mTargetScaleX = pTargetScaleX;
 }
 
 void FViewContainer::AnimationSetScaleXFrom(float pStartScaleX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartScaleX = pStartScaleX;
 if(mView)mViewAnimation->mTargetScaleX = mView->mTransform.mScaleX;
 }
 
 void FViewContainer::AnimationSetScaleY(float pTargetScaleY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetScaleY = pTargetScaleY;
 }
 
 void FViewContainer::AnimationSetScaleY(float pStartScaleY, float pTargetScaleY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartScaleX = pStartScaleY;
 mViewAnimation->mTargetScaleX = pTargetScaleY;
 }
 
 void FViewContainer::AnimationSetScaleYFrom(float pStartScaleY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartScaleY = pStartScaleY;
 if(mView)mViewAnimation->mTargetScaleY = mView->mTransform.mScaleY;
 }
 
 void FViewContainer::AnimationSetX(float pTargetX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetX = pTargetX;
 }
 
 void FViewContainer::AnimationSetX(float pStartX, float pTargetX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartX = pStartX;
 mViewAnimation->mTargetX = pTargetX;
 }
 
 void FViewContainer::AnimationSetXFrom(float pStartX)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartX = pStartX;
 mViewAnimation->mTargetX = mView->mTransform.mX;
 }
 
 void FViewContainer::AnimationSetY(float pTargetY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mTargetY = pTargetY;
 }
 
 void FViewContainer::AnimationSetY(float pStartY, float pTargetY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartY = pStartY;
 mViewAnimation->mTargetY = pTargetY;
 }
 
 void FViewContainer::AnimationSetYFrom(float pStartY)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 mViewAnimation->mStartY = pStartY;
 if(mView)mViewAnimation->mTargetY = mView->mTransform.mY;
 }
 
 void FViewContainer::AnimationCommit(int pTickCount)
 {
 if(mViewAnimation == 0)mViewAnimation = new FViewAnimation(mView);
 
 //mViewAnimation->mTimerTick = 0;
 //mViewAnimation->mTime = pTickCount;
 
 mViewAnimation->Generate(pTickCount);
 
 }
 */

void FViewContainer::SetTransformX(float pX)
{
    if(mView->mTransform.mX != pX)
    {
        mView->mTransform.mX = pX;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetTransformY(float pY)
{
    if(mView->mTransform.mY != pY)
    {
        mView->mTransform.mY = pY;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetTransformScale(float pScale)
{
    if(mView->mTransform.mScale != pScale)
    {
        mView->mTransform.mScale = pScale;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetTransformScaleX(float pScaleX)
{
    if(mView->mTransform.mScaleX != pScaleX)
    {
        mView->mTransform.mScaleX = pScaleX;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetTransformScaleY(float pScaleY)
{
    if(mView->mTransform.mScaleY != pScaleY)
    {
        mView->mTransform.mScaleY = pScaleY;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetTransformRotation(float pRotation)
{
    if(mView->mTransform.mRotation != pRotation)
    {
        mView->mTransform.mRotation = pRotation;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetTransformAnchorX(float pAnchorX)
{
    if(mView->mTransform.mAnchorX != pAnchorX)
    {
        mView->mTransform.mAnchorX = pAnchorX;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetTransformAnchorY(float pAnchorY)
{
    if(mView->mTransform.mAnchorY != pAnchorY)
    {
        mView->mTransform.mAnchorY = pAnchorY;
        FlagReadyForRefresh();
    }
}


void FViewContainer::SetFrameX(float pX)
{
    if(mView->mX != pX)
    {
        mView->mX = pX;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetFrameY(float pY)
{
    if(mView->mY != pY)
    {
        mView->mY = pY;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetFrameWidth(float pWidth)
{
    if(mView->mWidth != pWidth)
    {
        mView->mWidth = pWidth;
        FlagReadyForRefresh();
    }
}

void FViewContainer::SetFrameHeight(float pHeight) {
    if (mView->mHeight != pHeight) {
        mView->mHeight = pHeight;
        FlagReadyForRefresh();
    }
}

void FViewContainer::FlagReadyForRefresh() {
    mRefresh = true;
    if (mView->mController) {
        mView->mController->mRefresh = true;
    }
}

void FViewContainer::SetStaticTransform(bool pIsStatic) {
    mStaticTransform = pIsStatic;
    FlagReadyForRefresh();
}

void FViewContainer::Refresh() {
    mRefresh = false;
    if(mView) {
        mView->BasePositionContent();
    }
}

void FViewContainer::RefreshTransformations() {
    if (mStaticTransform) {
        if (mTransformAbsolute.ApplyAbsoluteTransformation(&(mView->mTransform), mView->mX, mView->mY, mView->mWidth, mView->mHeight) == false) {
            mRefresh = true;
        }
    } else {
        if (mParent) {
            FView *aParentView = mParent->mView;
            if(mTransformAbsolute.ApplyAbsoluteTransformation(&(mParent->mTransformAbsolute), aParentView->mX, aParentView->mY, aParentView->mWidth, aParentView->mHeight, &(mView->mTransform), mView->mX, mView->mY, mView->mWidth, mView->mHeight) == false) {
                mRefresh = true;
            }
        } else {
            if (mTransformAbsolute.ApplyAbsoluteTransformation(&(mView->mTransform), mView->mX, mView->mY, mView->mWidth, mView->mHeight) == false) {
                mRefresh = true;
            }
        }
    }
}

void FViewContainer::TransformTouch(float &pX, float &pY) {
    if (mView) {
        mTransformAbsolute.Transform(pX, pY, mView->GetWidth(), mView->GetHeight());
    } else {
        mTransformAbsolute.Transform(pX, pY);
    }
}






