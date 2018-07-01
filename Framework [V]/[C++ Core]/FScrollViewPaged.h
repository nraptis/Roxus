#ifndef FRAMEWORK_SCROLL_VIEW_PAGED_H
#define FRAMEWORK_SCROLL_VIEW_PAGED_H

#include "FGestureView.h"
#include "FSpline.h"

class FScrollViewPaged : public FGestureView
{
public:
    
    FScrollViewPaged();
    virtual ~FScrollViewPaged();
    
    virtual void                            BaseUpdate();
    
    
    void                                    SetPageCountHorizontal(int pCount);
    void                                    SetPageCountVertical(int pCount);
    void                                    SetPageCount(int pCountHorizontal, int pCountVertical){SetPageCountHorizontal(pCountHorizontal);SetPageCountVertical(pCountVertical);}
    
    int                                     mScrollPageCountH;
    int                                     mScrollPageCountV;
    
    
    virtual void                            ScrollFinished();
    virtual void                            ScrollFinishedHorizontal(int pStartRow, int pEndRow);
    virtual void                            ScrollFinishedVertical(int pStartCol, int pEndCol);
    
    virtual void                            BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    
    virtual void                            PanBegin(float pX, float pY);
    virtual void                            Pan(float pX, float pY);
    virtual void                            PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);
    
    int                                     mScrollCurrentPageH;
    int                                     mScrollCurrentPageV;
    
    int                                     mScrollAnimationTimeTotal;
    int                                     mScrollAnimationTimer;
    
    bool                                    mScrollAnimating;
    
    float                                   mSpeedThresholdFlingTo;
    float                                   mSpeedThresholdNudgeBack;
    
    float                                   mScrollOffset[2];
    float                                   mScrollOffsetPanShift[2];
    float                                   mScrollOffsetPanStart[2];
    
    int                                     mAnimationDirection;
    int                                     mFinishAnimationDirection;
    
    bool                                    mFinishAnimation;
    
    float                                   mScrollAnimationPercent;
    float                                   mScrollAnimationPercentTarget;
    
    float                                   mScrollPanStartThreshold;
    float                                   mScrollPanSwitchDirectionThreshold;
    
    bool                                    mScrollPanning;
    bool                                    mScrollPanDirectionPicked;
    
    bool                                    mScrollHorizontal;
    
    
    bool                                    mScrollEnabledHorizontal;
    bool                                    mScrollEnabledVertical;
    
    
    
    //How the heck sauce do they do that bounce stuff on UIScrollView.. *sigh*
    
    float                                   ScrollGetBounceDragShift(float pAmount);
    
};

#endif /* defined(__FleetGL__FScrollViewPaged__) */
