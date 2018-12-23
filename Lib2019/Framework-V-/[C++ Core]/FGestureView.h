//
//  CatImageCycler.h
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef CAT_GESTURE_VIEW_H
#define CAT_GESTURE_VIEW_H

#define MAX_GESTURE_TOUCHES 10


//#define MAX_GESTURE_TOUCH_RECORD_COUNT 5
#define MAX_GESTURE_TOUCH_RECORD_COUNT 8

#include "FView.h"
#include "FObject.h"

//In theory we could build it on this platform EXCEPT for the dang videos.. Hmm..

class FGestureTouch : public FObject
{
public:
    
    FGestureTouch();
    virtual ~FGestureTouch();
    
    
    
    void                        Reset(float pX, float pY, void *pData);
    void                        Move(float pX, float pY);
    
    float                       mHistoryMoveX[MAX_GESTURE_TOUCH_RECORD_COUNT];
    float                       mHistoryMoveY[MAX_GESTURE_TOUCH_RECORD_COUNT];
    int                         mHistoryMoveTime[MAX_GESTURE_TOUCH_RECORD_COUNT];
    int                         mHistoryMoveCount;
    
    float                       mX;
    float                       mY;
    
    float                       mStartX;
    float                       mStartY;
    
    float                       mMaxDistMoved;
    
    //Basically, if it is "resting" for too long, flush it out of the system.
    int                         mTimer;
    
    void                        *mData;
    
};

class FGestureView : public FView
{
public:
    
    FGestureView();
    virtual ~FGestureView();
    
    
    //Gesture Functions...
    virtual void                                    PanBegin(float pX, float pY);
    virtual void                                    Pan(float pX, float pY);
    virtual void                                    PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);
    
    virtual void                                    PinchBegin(float pScale);
    virtual void                                    Pinch(float pScale);
    virtual void                                    PinchEnd(float pScale);
    
    virtual void                                    TapSingle(float pX, float pY);
    virtual void                                    TapDouble(float pX, float pY);
    
    virtual void                                    RotateStart(float pRotation);
    virtual void                                    Rotate(float pRotation);
    virtual void                                    RotateEnd(float pRotation);
    
    virtual void                                    BaseUpdate();
    
    FGestureTouch                                   *mTouch[MAX_GESTURE_TOUCHES];
    int                                             mTouchCount;
    
    
    
    virtual void                                    BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
	virtual void                                    BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    virtual void                                    BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    virtual void                                    BaseTouchFlush();
    void                                            GestureComputeCenter();
    
    bool                                            mEnableGestures;
    
    
    bool                                            mEnablePanning;
    bool                                            mEnablePinching;
    bool                                            mEnableRotating;
    
    bool                                            mIsPanning;
    int                                             mGesturePanRequiredTouches;
    
    float                                           mGestureTouchCenterX;
    float                                           mGestureTouchCenterY;
    
    float                                           mGesturePanStartCenterX;
    float                                           mGesturePanStartCenterY;
    
    float                                           mGesturePanPreviousCenterX;
    float                                           mGesturePanPreviousCenterY;
    
    float                                           mGesturePanStartX;
    float                                           mGesturePanStartY;
    
    float                                           mGesturePanDistX;
    float                                           mGesturePanDistY;
    
    float                                           mGestureTranslateX;
    float                                           mGestureTranslateY;
    
    bool                                            mGestureTapQueued;
    int                                             mGestureTapLastTapTimer;
    int                                             mGestureTapLastTapCount;
    
    bool                                            mIsPinching;
    bool                                            mIsRotating;

    
    float                                           mGesturePinchX1;
    float                                           mGesturePinchY1;
    float                                           mGesturePinchX2;
    float                                           mGesturePinchY2;
    
    float                                           mGesturePinchStartDist;
    float                                           mGesturePinchScale;
    
    
    float                                           mGestureRotateStartAngle;
    float                                           mGestureRotateDegrees;
    
    void                                            ClearGestures(bool pEndActive);
    
    virtual void                                    Kill();
    
};


#endif /* defined(__FleetGL__CatImageCycler__) */
