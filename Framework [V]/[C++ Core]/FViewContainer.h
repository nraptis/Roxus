//
//  FViewContainer.h
//  RaptisGame
//
//  Created by Nick Raptis on 3/13/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_VIEW_CONTAINER_H
#define FRAMEWORK_VIEW_CONTAINER_H

#include "FViewTransform.h"
#include "FRect.h"
//#include "FViewAnimation.h"

#define VIEW_MAX_TOUCH_COUNT 5

//Umm, should really do this without a container... The hell is that..?

class FView;
class FViewContainer
{
public:
    
    FViewContainer(FView *pView);
    ~FViewContainer();
    
    void                                        Update();
    //void                                        Draw(int pLevel);
    void                                        Draw();
    
    void                                        DrawManualBegin();
    void                                        DrawManualEnd();
    
    void                                        DrawManualSubviews();
    
    //Theoretical Rule - If the touch didn't begin in a view, the touch
    //won't trickle down the move or up functions either..
    
    FViewContainer                              *TouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pClippedByParent, bool &pConsumed);
	void                                        TouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pClippedByParent);
    void                                        TouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pClippedByParent);
    void                                        TouchFlush();

	void										MouseWheel(int pDirection);
	void										KeyDown(int pKey);
	void										KeyUp(int pKey);
    
    void                                        MemoryWarning(bool pSevere);
    
    void                                        Inactive();
    void                                        Active();
    
    void                                        DrawTransform();
    
    FView                                       *mView;
    
    int                                         mKill;
    
    bool                                        mDidUpdate;
    bool                                        mDidDraw;
    
    bool                                        mDraggingFrame;
    
    void                                        *mDraggingFrameData;
    
    float                                       mDraggingFrameStartX;
    float                                       mDraggingFrameStartY;
    float                                       mDraggingFrameTouchStartX;
    float                                       mDraggingFrameTouchStartY;
    
    void                                        Refresh();
    void                                        RefreshTransformations();
    void                                        FlagReadyForRefresh();
    
    bool                                        mRefresh;
    bool                                        mRefreshTransformations;
    
    bool                                        ContainsPoint(float pX, float pY);
    
    void                                        TransformTouch(float &pX, float &pY);
    
    
    
    //void                                        MoveChildToFront(FViewContainer *pContainer);
    //void                                        MoveChildToBack(FViewContainer *pContainer);
    //void                                        MoveChildForward(FViewContainer *pContainer);
    //void                                        MoveChildBackward(FViewContainer *pContainer);
    //void                                        AddSubviewContainer(FViewContainer *pContainer);
    //void                                        RemoveChildContainer(FViewContainer *pContainer);
    
    //bool                                        ContainsChildContainer(FViewContainer *pContainer);
    
    //void                                        ChildZIndexChanged(FViewContainer *pChild);
    
    //FViewContainer                              **mChild;
    
    //int                                         mChildListCount;
    //int                                         mChildListSize;
    
    //bool                                        mChildListIsSorted;
    
    //void                                        KillModalViews();
    //void                                        FlagAllChildrenAsModal();
    
    void                                        SetTransformX(float pX);
    void                                        SetTransformY(float pY);
    void                                        SetTransformScale(float pScale);
    void                                        SetTransformScaleX(float pScaleX);
    void                                        SetTransformScaleY(float pScaleY);
    void                                        SetTransformRotation(float pRotation);
    void                                        SetTransformAnchorX(float pAnchorX);
    void                                        SetTransformAnchorY(float pAnchorY);
    
    void                                        SetFrameX(float pX);
    void                                        SetFrameY(float pY);
    void                                        SetFrameWidth(float pWidth);
    void                                        SetFrameHeight(float pHeight);
    
    FViewTransform                              mTransformAbsolute;
    FViewContainer                              *mParent;
    //int                                         mChildIndex;
    
    //bool                                        mRetainedByParent;
    
    void                                        SetStaticTransform(bool pIsStatic);
    bool                                        mStaticTransform;
    
    void                                        *mTouchData[VIEW_MAX_TOUCH_COUNT];
    bool                                        mTouchInside[VIEW_MAX_TOUCH_COUNT];
};

#endif






