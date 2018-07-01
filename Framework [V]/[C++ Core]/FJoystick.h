//
//  FJoystick.h
//  Starfox
//
//  Created by Nick Raptis on 5/23/11.
//  Copyright 2011 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_JOYSTICK_H
#define FRAMEWORK_JOYSTICK_H

#include "FSprite.h"
#include "FView.h"

#define FJoystick_CANCEL_TIME 1000

class FJoystick : public FView
{
public:
    
    FJoystick();
    ~FJoystick();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    
    bool                                    IsClicked();
    
    int                                     mCancelTimer;
    void                                    *mData;
    
    bool                                    mRotateBack;
    
    bool                                    mKnobMoves;
    bool                                    mBackRotates;
    
    float                                   mX, mY;
    
    float                                   mDiffMultX;
    float                                   mDiffMultY;
    
    float                                   mDirX, mDirY, mLength;
    float                                   mPercentX;
    float                                   mPercentY;
    
    float                                   mRotation;
    float                                   mRotationFJoystick;
    
    
    float                                   mRotationFJoystickStart;
    float                                   mRotationStart;
    
    float                                   mLengthSquared;
    
    float                                   mRadius;
    float                                   mRadiusSquared;
    
    float                                   mMaxDragLength;
    
    void                                    SetRadius(float pRadius){mRadius=pRadius;mRadiusSquared=mRadius*mRadius;}
    
    //virtual void                            MultiTouch(int x, int y, void *pData);
	//virtual void                            MultiRelease(int x, int y, void *pData);
    //virtual void                            MultiDrag(int x, int y, void *pData);
    //virtual void                            FlushMultiTouch();
    
    FSprite                                 *mSpriteBackground;
    FSprite                                 *mSpriteKnob;
    
};

#endif
