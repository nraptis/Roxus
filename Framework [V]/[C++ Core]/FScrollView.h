//
//  FScrollView.h
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef CAT_SCROLL_VIEW_H
#define CAT_SCROLL_VIEW_H

#include "FGestureView.h"

class FScrollView : public FGestureView
{
public:
    
    FScrollView();
    virtual ~FScrollView();
    
    //virtual void                            BaseParentFrameChanged(float pX, float pY, float pWidth, float pHeight);
    
    virtual void                            BaseUpdate();
    virtual void                            BaseDraw();
    virtual void                            BaseDrawOver();
    
    virtual void                            BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    //virtual void                            BaseTouchDown(float pX, float pY, void *pData);
    
    virtual void                            PanBegin(float pX, float pY);
    virtual void                            Pan(float pX, float pY);
    virtual void                            PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);
    
    void                                    SetContentSize(float pWidth, float pHeight);
    
    virtual void                            ScrollFinished();
    
    bool                                    PositionIsOutOfBoundsOver(float pValue, int pIndex);
    bool                                    PositionIsOutOfBoundsUnder(float pValue, int pIndex);
    
    //float                                   mNaturalFlingTo[2];
    
    float                                   mScrollUpdateFlingDecayMultiply;
    float                                   mScrollUpdateFlingDecaySubtract;
    
    float                                   mScrollOffset[2];
    
    float                                   mScrollTargetOffset[2];
    
    float                                   mScrollFlingSpeed;
    float                                   mScrollFlingDir[2];
    
    float                                   mScrollContentSizeWidth;
    float                                   mScrollContentSizeHeight;
    
    float                                   mScrollMinOffset[2];
    
    
    float                                   mScrollBounceBackStartOffset[2];
    float                                   mScrollBounceBackFinishOffset[2];
    float                                   mScrollBounceBackStartSpeed[2];
    float                                   mScrollBounceBackFinishSpeed[2];
    
    float                                   mScrollBounceBackAdjustmentPre[2];
    float                                   mScrollBounceBackAdjustmentPost[2];
    
    int                                     mScrollBounceBackTimeTotal[2];
    int                                     mScrollBounceBackTime[2];
    
    float                                   mScrollMaxDistance;
    
    float                                   mScrollActionScale;
    
    float                                   ScrollGetBounceDragShift(float pAmount);
    
    void                                    ScrollBounce(int pIndex);
    
    bool                                    ScrollIsAnimating();
    
    
    bool                                    mScrollHorizontalDisabledIfTooSmall;
    bool                                    mScrollVerticalDisabledIfTooSmall;
    
    
    bool                                    mScrollHorizontalEnabled;
    bool                                    mScrollVerticalEnabled;
    
    
    //How the heck sauce do they do that bounce stuff on UIScrollView.. *sigh*
    //float                                   mScrollMax
    
    
    
};

#endif /* defined(__FleetGL__FScrollView__) */
