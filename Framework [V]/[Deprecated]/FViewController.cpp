//
//  FViewController.cpp
//  RaptisGame
//
//  Created by Nick Raptis on 3/13/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "core_includes.h"

#include "FView.h"
#include "FViewContainer.h"
#include "FViewController.h"

FViewController::FViewController()
{
    mAppFitRefresh = true;
    
    mAppFitType = APP_FIT_MODE_NONE;
    
    mMain = false;
    
    mIsUpdating = false;
    mIsDrawing = false;
    mIsPerformingTouchAction = false;
    
    mAppFitDeviceOriginX = 0.0f;
    mAppFitDeviceOriginY = 0.0f;
    
    mAppFitDeviceWidth = 1024.0f;
    mAppFitDeviceHeight = 768.0f;
    
    mAppFitTargetWidth = 1024.0f;
    mAppFitTargetHeight = 768.0f;
    
    mAppWidth = 1024.0f;
    mAppHeight = 768.0f;
    
    mRoot.SetFrame(0.0f, 0.0f, mAppFitTargetWidth, mAppFitTargetHeight);
    //mRoot.GetContainer() = new FViewContainer(&mRoot);
    
    mRoot.mClipsContent = false;
    mRoot.mConsumesTouches = false;
    mRoot.mRecievesConsumedTouches = true;
    mRoot.mRecievesOutsideTouches = true;
    //mRoot.SetTransformRotation(5.0f);
    //mRoot.SetTransformScaleX(1.125f);
    //mRoot.SetTransformScaleY(0.75f);
    //mRoot.SetTransformScale(1.125f);
    
    mRoot.mName = "Root";
    
    mRefresh = true;
    
    mTouchConsumed = false;
    
    
    mViewStack = 0;
    mViewStackCount = 0;
    mViewStackSize = 0;
    mViewStackDeleted = 0;
    mViewStackRebuild = true;
}

FViewController::~FViewController()
{
    
}

void FViewController::DeviceSizeChanged(float pX, float pY, float pWidth, float pHeight)
{
    mAppFitDeviceOriginX = pX;
    mAppFitDeviceOriginY = pY;
    
    mAppFitDeviceWidth = pWidth;
    mAppFitDeviceHeight = pHeight;
    
    FitTypeSet(mAppFitType);
}

/*
 void FViewController::UpdateUtilsOnly()
 {
 if(mRefresh)Refresh();
 
 mIsUpdating = true;
 
 if(gUtils)
 {
 gUtils->GetContainer()->Update();
 }
 
 //mRoot.GetContainer()->Update();
 //if(mRootOverlay)mRootOverlay->GetContainer()->Update();
 
 mIsUpdating = false;
 if(mRefresh)Refresh();
 }
 */

void FViewController::Update()
{
    if(mRefresh)Refresh();
    
    mIsUpdating = true;
    
    mRoot.GetContainer()->Update();
    
    mIsUpdating = false;
    if(mRefresh)Refresh();
}

void FViewController::Draw()
{
    if(mRefresh)Refresh();
    mIsDrawing = true;
    
    mRoot.GetContainer()->Draw();
    
    mIsDrawing = false;
    if(mRefresh)Refresh();
}

bool FViewController::TouchDown(float pX, float pY, void *pData)
{
    bool aResult = false;
    
    mTouchConsumed = false;
    FViewContainer *aContainer = mRoot.GetContainer()->TouchDown(pX, pY, pX, pY, pData, false, mTouchConsumed);
    
    if(aContainer != 0)
    {
        if(aContainer != mRoot.GetContainer())
        {
            aResult = true;
        }
    }
    
    return aResult;
}

void FViewController::TouchMove(float pX, float pY, void *pData)
{
    mRoot.GetContainer()->TouchMove(pX, pY, pX, pY, pData, false);
}

void FViewController::TouchUp(float pX, float pY, void *pData)
{
    
    if(mRoot.GetContainer())
    {
        mRoot.GetContainer()->TouchUp(pX, pY, pX, pY, pData, false);
    }
}

void FViewController::TouchFlush()
{
    if(mRoot.GetContainer())
    {
        mRoot.GetContainer()->TouchFlush();
    }
}

void FViewController::MouseWheel(int pDirection)
{
    mRoot.GetContainer()->MouseWheel(pDirection);
}

void FViewController::KeyDown(int pKey)
{
    mRoot.GetContainer()->KeyDown(pKey);
}

void FViewController::KeyUp(int pKey)
{
    mRoot.GetContainer()->KeyUp(pKey);
}

/*
 
 void FViewController::OverlayTouchDown(float pX, float pY, void *pData)
 {
 if(mRootOverlay)
 {
 mRootOverlay->GetContainer()->TouchUp(pX, pY, pX, pY, pData, false);
 }
 }
 
 void FViewController::OverlayTouchMove(float pX, float pY, void *pData)
 {
 if(mRootOverlay)
 {
 mRootOverlay->GetContainer()->TouchMove(pX, pY, pX, pY, pData, false);
 }
 }
 
 void FViewController::OverlayTouchUp(float pX, float pY, void *pData)
 {
 if(mRootOverlay)
 {
 mRootOverlay->GetContainer()->TouchUp(pX, pY, pX, pY, pData, false);
 }
 }
 
 void FViewController::OverlayTouchFlush()
 {
 if(mRootOverlay)
 {
 mRootOverlay->GetContainer()->TouchFlush();
 }
 }
 
 */

void FViewController::Inactive()
{
    if(mRoot.GetContainer())
    {
        mRoot.GetContainer()->Inactive();
    }
}

void FViewController::Active()
{
    if(mRoot.GetContainer())
    {
        mRoot.GetContainer()->Active();
    }
}

void FViewController::MemoryWarning(bool pSevere)
{
    if(mRoot.GetContainer())
    {
        mRoot.GetContainer()->MemoryWarning(pSevere);
    }
}

bool FViewController::IsLocked()
{
    bool aResult = false;
    
    if(mIsUpdating)aResult = true;
    if(mIsDrawing)aResult = true;
    if(mIsPerformingTouchAction)aResult = true;
    
    return aResult;
}


void FViewController::ViewCreated(FView *pView)
{
    mViewStackRebuild = true;
}

void FViewController::ViewDestroyed(FView *pView)
{
    mViewStackRebuild = true;
}

void FViewController::ViewAdd(FView *pView)
{
    ViewAddToParent(pView, &(mRoot), false, false);
}

void FViewController::ViewAdd(FView &pView)
{
    ViewAddToParent(&pView, &(mRoot), true, false);
}


bool FViewController::ViewExists()
{
    bool aResult = false;
    if(mRoot.mSubviews.mCount > 0)aResult = true;
    return aResult;
}

bool FViewController::ViewExists(FView *pView)
{
    bool aResult = false;
    
    
    return aResult;
}

//void FViewController::ViewAdd(FView *pView, int pZIndex)
//{
//    ViewAddToParent(pView, &(mRoot), pZIndex, false, false, false);
//}

//void FViewController::ViewAdd(FView &pView, int pZIndex)
//{
//    ViewAddToParent(&pView, &(mRoot), pZIndex, true, false, false);
//}

void FViewController::ViewAdd(FView *pView, bool pRetainedByParent)
{
    ViewAddToParent(pView, &(mRoot), pRetainedByParent, false);
}

/*
 void FViewController::ModalViewAdd(FView *pView)
 {
 ViewAddToParent(pView, &(mRoot), false, true);
 }
 
 void FViewController::ModalViewAdd(FView &pView)
 {
 ViewAddToParent(&pView, &(mRoot), true, true);
 }
 
 void FViewController::ModalViewAddTop(FView *pView)
 {
 ViewAddToParent(pView, &(mRoot), false, true);
 }
 
 void FViewController::ModalViewAddTop(FView &pView)
 {
 ViewAddToParent(&pView, &(mRoot), true, true);
 }
 
 //void FViewController::ModalViewAdd(FView *pView, int pZIndex)
 //{
 //    ViewAddToParent(pView, &(mRoot), pZIndex, false, false, true);
 //}
 
 //void FViewController::ModalViewAdd(FView &pView, int pZIndex)
 //{
 //    ViewAddToParent(&pView, &(mRoot), pZIndex, true, false, true);
 //}
 
 bool FViewController::ModalViewExists()
 {
 return mRoot.ModalViewExists();
 }
 
 int FViewController::ModalViewCount()
 {
 return mRoot.ModalViewCount();
 }
 
 */

//void FViewController::ViewAddToParent(FView *pChild, FView *pParent, int pZIndex, bool pRetainedByParent, bool pGenerateZIndex, bool pIsModal)
void FViewController::ViewAddToParent(FView *pChild, FView *pParent, bool pRetainedByParent, bool pIsModal)
{
    if(pParent != 0)pParent->mController = this;
    if(pChild != 0)pChild->mController = this;
    
    if((pChild != 0) && (pParent != 0))
    {
        //if(pParent->GetContainer()->mModal)
        //{
        //    pChild->GetContainer()->mModal = true;
        //    pIsModal = true;
        
        ////pChild->GetContainer()->mModal = true;
        //}
        
        //TODO: If thre's already a parent, safely shuffle it all around.
        
        //if(pGenerateZIndex)
        //{
        //    pZIndex = pParent->GetContainer()->GenerateZIndex();
        //Log("[%s] Generated Z(%d) For [%s]\n", pParent->mName.c(), pZIndex, pChild->mName.c());
        //}
        
        //pChild->GetContainer()->mZIndex = pZIndex;
        //pChild->SetZIndex(pZIndex);
        
        //if(pIsModal)
        //{
        //    pChild->GetContainer()->mModal = true;
        //}
        
        
        if(pParent->mSubviews.Exists(pChild) == false)pParent->mSubviews.Add(pChild);
        pChild->mParentRetain = pRetainedByParent;
        
        
        if(pChild->mParent)
        {
            if(pChild->mParent == pParent)
            {
                //... Nice!
            }
            else
            {
                //TODO: Swap on next cycle..
                pChild->mParent = pParent;
            }
        }
        else
        {
            pChild->mParent = pParent;
        }
        
        
        FViewContainer *aContainer = pChild->GetContainer();
        if(aContainer)
        {
            aContainer->mParent = (pParent->GetContainer());
            
            if(IsLocked())
            {
                if(mQueueParentAdd.Exists(aContainer) == false)
                {
                    mQueueParentAdd.Add(aContainer);
                }
            }
            else
            {
                RealizeAddToParent(aContainer);
            }
            
            aContainer->mRefresh = true;
            mRefresh = true;
        }
    }
    
    ViewAddToParentCallback(pParent);
    
    mViewStackRebuild = true;
}

void FViewController::ViewAddToParentCallback(FView *pView)
{
    if(pView)
    {
        pView->mController = this;
        
        EnumList(FView, aView, pView->mSubviews)
        {
            ViewAddToParentCallback(aView);
        }
    }
}



//void FViewController::ViewRemoveFromParent(FView *pChild)
void FViewController::RemoveViewFromParent(FView *pView)
{
    if(pView)
    {
        FViewContainer *aContainer = pView->GetContainer();
        
        if(IsLocked() == false)
        {
            RealizeRemoveFromParent(aContainer);
        }
        else
        {
            if(mQueueParentRemove.Exists(aContainer) == false)
            {
                mQueueParentRemove.Add(aContainer);
                
            }
        }
        mRefresh = true;
    }
    mViewStackRebuild = true;
}

void FViewController::ViewKill(FView *pView)
{
    if(pView)
    {
        /*
         Log("Deleting View [%s]\n", pView->mName.c());
         
         for(int i=0;i<mViewStackCount;i++)
         {
         if(mViewStack[i] == pView)
         {
         Log("THE VIEW WAS IN THE STACK...\n\n");
         
         mViewStackDeleted[i] = true;
         
         }
         }
         */
        
        
        FViewContainer *aContainer = pView->GetContainer();
        
        
        if(aContainer->mKill <= 0)
        {
            aContainer->mKill = 3;
        }
        
        if(IsLocked() == false)// && (false))
        {
            RealizeKill(aContainer);
        }
        else
        {
            bool aExists = false;
            //mQueueKill.Exists(aContainer);
            
            FViewContainer *aCheck = aContainer;
            
            while((aExists == false) && (aCheck != 0))
            {
                aExists = mQueueKill.Exists(aContainer);
                aCheck = aCheck->mParent;
            }
            
            if(aExists == false)
            {
                //Flush Out All Children From Kill Queue...
                RemoveChildrenFromKillQueue(aContainer);
                mQueueKill.Add(aContainer);
            }
            else
            {
                Log("Deleting View[%s] - Parent Is Already Being Killed\n", pView->mName.c());
            }
        }
        mRefresh = true;
    }
    
    mViewStackRebuild = true;
    
}

void FViewController::RemoveChildrenFromKillQueue(FViewContainer *pContainer)
{
    if(pContainer)
    {
        FViewContainer *aChild = 0;
        
        for(int i = 0; i<pContainer->mView->mSubviews.mCount; i++)
        {
            FViewContainer *aCtr = ((FView *)(pContainer->mView->mSubviews.Fetch(i)))->GetContainer();
            if(mQueueKill.Exists(aCtr))
            {
                if(aCtr->mView)
                {
                    Log("Removing Child From Kill Queue[%s]\n", aChild->mView->mName.c());
                }
                
                mQueueKill.Remove(aCtr);
            }
            RemoveChildrenFromKillQueue(aCtr);
        }
    }
}

void FViewController::KillAllChildrenWithView(FViewContainer *pContainer)
{
    if(pContainer)
    {
        if(pContainer->mView)
        {
            for(int i = 0; i<pContainer->mView->mSubviews.mCount; i++)
            {
                FViewContainer *aCtr = ((FView *)(pContainer->mView->mSubviews.Fetch(i)))->GetContainer();
                KillAllChildrenWithView(aCtr);
            }
            
            if(pContainer->mView->mParentRetain == false)
            {
                delete pContainer->mView;
            }
        }
        
        pContainer->mView = 0;
        delete pContainer;
    }
}

void FViewController::KillAllViews()
{
    FList aList;
    EnumList(FView, aView, mRoot.mSubviews)
    {
        aList.Add(aView);
    }
    EnumList(FView, aView, aList)
    {
        aView->Kill();
    }
}

void FViewController::RealizeAddToParent(FViewContainer *pContainer)
{
    if(pContainer)
    {
        FViewContainer *aParent = pContainer->mParent;
        
        if((aParent == 0) && (pContainer->mView))
        {
            
            if(pContainer->mView->mParent)
            {
                aParent = pContainer->mView->mParent->GetContainer();
            }
        }
        
        if(aParent)
        {
            // aParent->AddSubviewContainer(pContainer);
        }
    }
    
    mViewStackRebuild = true;
}

void FViewController::RealizeRemoveFromParent(FViewContainer *pContainer)
{
    if(pContainer)
    {
        FView *aView = pContainer->mView;
        FView *aParent = pContainer->mView->mParent;
        
        if(aParent)
        {
            aView->mParent = 0;
            
            aParent->mSubviews.Remove(pContainer->mView);
            //aParent->GetContainer()->RemoveChildContainer(pContainer);
        }
    }
    
    mViewStackRebuild = true;
}

void FViewController::RealizeKill(FViewContainer *pContainer)
{
    if(pContainer)
    {
        if(pContainer->mView != 0)
        {
            //Log("RealizeKill(%s)\n", pContainer->mView->mName.c());
            if(pContainer->mView->mParent != 0)
            {
                pContainer->mView->mParent->mSubviews.Remove(pContainer->mView);
            }
        }
        KillAllChildrenWithView(pContainer);
    }
    mViewStackRebuild = true;
}

void FViewController::RebuildViewStack()
{
    if(mViewStackRebuild)
    {
        mViewStackRebuild = false;
        
        mViewStackCount = 0;
        RebuildViewStack(&mRoot, 1);
    }
}

void FViewController::RebuildViewStack(FView *pView, int pDepth)
{
    if(mViewStackCount == mViewStackSize)
    {
        mViewStackSize = (mViewStackCount + (mViewStackCount / 2) + 1);
        
        FView **aStack = new FView*[mViewStackSize];
        
        bool *aDeleted = new bool[mViewStackSize];
        
        for(int i=0;i<mViewStackCount;i++)
        {
            aStack[i] = mViewStack[i];
            aDeleted[i] = mViewStackDeleted[i];
        }
        
        for(int i=mViewStackCount;i<mViewStackSize;i++)
        {
            aDeleted[i] = false;
        }
        
        delete [] mViewStack;
        
        mViewStack = aStack;
        
        
        delete [] mViewStackDeleted;
        
        mViewStackDeleted = aDeleted;
    }
    
    if(pView)
    {
        mViewStack[mViewStackCount] = pView;
        mViewStackDeleted[mViewStackCount] = false;
        
        mViewStackCount++;
        
        EnumList(FView, aView, pView->mSubviews)
        {
            RebuildViewStack(aView, pDepth + 1);
        }
    }
}

void FViewController::SetNaturalSize(float pWidth, float pHeight)
{
    mAppFitTargetWidth = pWidth;
    mAppFitTargetHeight = pHeight;
    
    FitTypeSet(mAppFitType);
}

void FViewController::FitTypeSetWidth()
{
    FitTypeSet(APP_FIT_MODE_WIDTH);
}

void FViewController::FitTypeSetHeight()
{
    FitTypeSet(APP_FIT_MODE_HEIGHT);
}

void FViewController::FitTypeSetNone()
{
    FitTypeSet(APP_FIT_MODE_NONE);
}

void FViewController::FitTypeSet(int pType)
{
    mAppFitType = pType;
    
    if(IsLocked() == false)
    {
        RealizeFitType();
    }
    else
    {
        mAppFitRefresh = true;
        mRefresh = true;
    }
}

void FViewController::RealizeFitType() {
    if (mAppFitType == APP_FIT_MODE_WIDTH) {
        float aWidthScale = mAppFitDeviceWidth / mAppFitTargetWidth;
        mRoot.SetTransformScale(aWidthScale);
        gAdjustmentScale = (1 / mRoot.GetTransformScale());
        
        mAppWidth = mAppFitTargetWidth;
        mAppHeight = mAppFitDeviceHeight / mRoot.GetTransformScale();
        
        if(mMain)
        {
            gAppWidth = mAppWidth;
            gAppHeight = mAppHeight;
            
            gAppWidth2 = (gAppWidth / 2.0f);
            gAppHeight2 = (gAppHeight / 2.0f);
            
            Graphics::ClipSetAppFrame(mAppFitDeviceOriginX, mAppFitDeviceOriginY, gAppWidth, gAppHeight);
        }
        
        mRoot.SetTransformX(mAppFitDeviceOriginX);
        mRoot.SetTransformY(mAppFitDeviceOriginY);
        
        mRoot.SetFrame(0.0f, 0.0f, mAppWidth, mAppHeight);
    }
    else if(mAppFitType == APP_FIT_MODE_HEIGHT)
    {
        float aHeightScale = mAppFitDeviceHeight / mAppFitTargetHeight;
        mRoot.SetTransformScale(aHeightScale);
        gAdjustmentScale = (1 / mRoot.GetTransformScale());
        
        
        mAppWidth = mAppFitDeviceHeight / mRoot.GetTransformScale();
        mAppHeight = mAppFitTargetHeight;
        
        if(mMain)
        {
            gAppWidth = mAppWidth;
            gAppHeight = mAppHeight;
            
            gAppWidth2 = (gAppWidth / 2.0f);
            gAppHeight2 = (gAppHeight / 2.0f);
            
            Graphics::ClipSetAppFrame(mAppFitDeviceOriginX, mAppFitDeviceOriginY, gAppWidth, gAppHeight);
        }
        
        mRoot.SetTransformX(mAppFitDeviceOriginX);
        mRoot.SetTransformY(mAppFitDeviceOriginY);
        
        
        mRoot.SetFrame(0.0f, 0.0f, mAppWidth, mAppHeight);
    }
    else
    {
        mAppWidth = mAppFitDeviceWidth;
        mAppHeight = mAppFitDeviceHeight;
        
        if(mMain)
        {
            gAppWidth = mAppWidth;
            gAppHeight = mAppHeight;
            
            gAppWidth2 = (gAppWidth / 2.0f);
            gAppHeight2 = (gAppHeight / 2.0f);
            
            Graphics::ClipSetAppFrame(mAppFitDeviceOriginX, mAppFitDeviceOriginY, gAppWidth, gAppHeight);
        }
        
        mRoot.SetTransformX(mAppFitDeviceOriginX);
        mRoot.SetTransformY(mAppFitDeviceOriginY);
        
        
        
        
        
        mRoot.SetFrame(0.0f, 0.0f, mAppWidth, mAppHeight);
    }
    
    if(mRoot.GetContainer())
    {
        mRoot.GetContainer()->mRefresh = true;
    }
    
    mAppFitRefresh = false;

}

void FViewController::Refresh()
{
    mRefresh = false;
    
    if(mAppFitRefresh)
    {
        RealizeFitType();
    }
    
    int aRefreshLoops = 0;
    bool aLoop = true;
    
    while((aRefreshLoops < 300) && (aLoop == true))
    {
        aLoop = false;
        while(mQueueParentAdd.mCount > 0)
        {
            FViewContainer *aContainer = (FViewContainer *)mQueueParentAdd.Last();
            mQueueParentAdd.mCount--;
            RealizeAddToParent(aContainer);
            aLoop = true;
        }
        
        while(mQueueParentRemove.mCount > 0)
        {
            FViewContainer *aContainer = (FViewContainer *)mQueueParentRemove.Last();
            mQueueParentRemove.mCount--;
            RealizeRemoveFromParent(aContainer);
            aLoop = true;
        }
        
        while(mQueueKill.mCount > 0)
        {
            FViewContainer *aContainer = (FViewContainer *)mQueueKill.Last();
            mQueueKill.mCount--;
            RealizeKill(aContainer);
            aLoop = true;
        }
        
        if(RefreshAll(mRoot.GetContainer()))
        {
            aLoop = true;
        }
        aRefreshLoops++;
    }
    mRefresh = false;
}

bool FViewController::RefreshAll(FViewContainer *pContainer)
{
    bool aResult = false;
    
    if(pContainer)
    {
        pContainer->mRefresh = false;
        
        pContainer->Refresh();
        pContainer->RefreshTransformations();
        
        if(pContainer->mRefresh == true)
        {
            aResult = true;
        }
        
        for(int i = 0; i<pContainer->mView->mSubviews.mCount; i++)
        {
            FViewContainer *aCtr = ((FView *)(pContainer->mView->mSubviews.Fetch(i)))->GetContainer();
            
            if(RefreshAll(aCtr))
            {
                aResult = true;
            }
        }
    }
    
    return aResult;
}

bool FViewController::AnyViewRefreshed(FViewContainer *pContainer)
{
    bool aResult = false;
    
    if(pContainer)
    {
        if((pContainer->mRefreshTransformations == true) || (pContainer->mRefresh == true))
        {
            aResult = true;
        }
        
        for(int i = 0; i<pContainer->mView->mSubviews.mCount; i++)
        {
            FViewContainer *aCtr = ((FView *)(pContainer->mView->mSubviews.Fetch(i)))->GetContainer();
            if(AnyViewRefreshed(aCtr))
            {
                aResult = true;
            }
        }
    }
    
    if(mRefresh == true)
    {
        aResult = true;
    }
    
    return aResult;
}



