//
//  FViewController.h
//  RaptisGame
//
//  Created by Nick Raptis on 3/13/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_VIEW_MANAGER_H
#define FRAMEWORK_VIEW_MANAGER_H

#define APP_FIT_MODE_NONE 0
#define APP_FIT_MODE_WIDTH 1
#define APP_FIT_MODE_HEIGHT 2

#include "FView.h"
#include "FHashTable.hpp"
#include "FList.h"

class FView;
class FViewContainer;

class FViewController
{
public:
    
    FViewController();
    ~FViewController();
    
    void                                    DeviceSizeChanged(float pX, float pY, float pWidth, float pHeight);
    
    void                                    Update();
	void                                    Draw();
    
    bool                                    TouchDown(float pX, float pY, void *pData);
    void                                    TouchMove(float pX, float pY, void *pData);
    void                                    TouchUp(float pX, float pY, void *pData);
    void                                    TouchFlush();

	void									MouseWheel(int pDirection);
	void									KeyDown(int pKey);
	void									KeyUp(int pKey);
    
    void                                    Inactive();
    void                                    Active();
    
    void                                    MemoryWarning(bool pSevere);
    
    void                                    RealizeAddToParent(FViewContainer *pContainer);
    void                                    RealizeRemoveFromParent(FViewContainer *pContainer);
    void                                    RealizeKill(FViewContainer *pContainer);
    
    void                                    RemoveChildrenFromKillQueue(FViewContainer *pContainer);
    void                                    KillAllChildrenWithView(FViewContainer *pContainer);
    //void                                    KillAllModalViews();
    void                                    KillAllViews();
    
    
    void                                    ViewCreated(FView *pView);
    void                                    ViewDestroyed(FView *pView);
    
    void                                    ViewAdd(FView *pView);
    void                                    ViewAdd(FView &pView);
    
    bool                                    ViewExists();
    bool                                    ViewExists(FView *pView);
    
    
    //void                                    ModalViewAdd(FView *pView);
    //void                                    ModalViewAdd(FView &pView);
    //void                                    ModalViewAddTop(FView *pView);
    //void                                    ModalViewAddTop(FView &pView);
    //bool                                    ModalViewExists();
    //int                                     ModalViewCount();
    //FView                                   *GetTopModalView();
    
    void                                    ViewAdd(FView *pView, bool pRetainedByParent);
    void                                    ViewAddToParent(FView *pChild, FView *pParent, bool pRetainedByParent, bool pIsModal);
    
    void                                    ViewAddToParentCallback(FView *pView);
    
    
    
    //void                                    ViewRemoveFromParent(FView *pChild);
    
    
    void                                    RemoveViewFromParent(FView *pView);
    
    //void                                    BringSubviewToFront(FView *pView);
    //void                                    SendSubviewToBack(FView *pView);
    
    //void                                    SendSubviewBackward(FView *pView);
    //void                                    BringSubviewForward(FView *pView);
    
    
    void                                    ViewKill(FView *pView);
    
    void                                    Refresh();
    bool                                    RefreshAll(FViewContainer *pContainer);
    
    bool                                    AnyViewRefreshed(FViewContainer *pContainer);
    bool                                    mRefresh;
    
    FView                                   mRoot;
    
    FList                                   mQueueParentAdd;
    FList                                   mQueueParentRemove;
    FList                                   mQueueKill;

    //FList                                   mQueueMoveFront;
    //FList                                   mQueueMoveBack;
    //FList                                   mQueueMoveForward;
    //FList                                   mQueueMoveBackward;

    FList                                   mDelete;
    
    
    
    void                                    RebuildViewStack();
    void                                    RebuildViewStack(FView *pView, int pDepth);
    
    FView                                   **mViewStack;
    bool                                    *mViewStackDeleted;
    bool                                    mViewStackRebuild;
    int                                     mViewStackCount;
    int                                     mViewStackSize;
    
    
    bool                                    mIsUpdating;
    bool                                    mIsDrawing;
    bool                                    mIsPerformingTouchAction;
    
    bool                                    IsLocked();
    
    bool                                    mTouchConsumed;
    
    
    
    
    //This stuff is basically for, like..
    void                                    SetNaturalSize(float pWidth, float pHeight);
    
    void                                    FitTypeSetWidth();
    void                                    FitTypeSetHeight();
    void                                    FitTypeSetNone();
    void                                    FitTypeSet(int pType);
    void                                    RealizeFitType();
    
    bool                                    mAppFitRefresh;
    
    int                                     mAppFitType;
    
    float                                   mAppFitDeviceOriginX;
    float                                   mAppFitDeviceOriginY;
    
    float                                   mAppFitDeviceWidth;
    float                                   mAppFitDeviceHeight;
    
    float                                   mAppFitTargetWidth;
    float                                   mAppFitTargetHeight;
    
    
    bool                                    mMain;
    float                                   mAppWidth;
    float                                   mAppHeight;

};

#endif
