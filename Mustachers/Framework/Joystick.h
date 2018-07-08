//
//  Joystick.h
//  Starfox
//
//  Created by Nick Raptis on 5/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sprite.h"

#define JOYSTICK_CANCEL_TIME 1000

class Joystick
{
public:
    
    Joystick();
    ~Joystick();
    
    virtual void                Update();
    virtual void                Draw();
    
    bool                        IsClicked();
    
    int                         mCancelTimer;
    void                        *mData;
    
    bool                        mRotateBack;
    
    bool                        mKnobMoves;
    bool                        mBackRotates;
    
    float                       mX, mY;
    
    float                       mDiffMultX;
    float                       mDiffMultY;
    
    float                       mDirX, mDirY, mLength;
    float                       mPercentX;
    float                       mPercentY;
    
    float                       mRotation;
    float                       mRotationJoystick;
    
    
    float                       mRotationJoystickStart;
    float                       mRotationStart;
    
    float                       mLengthSquared;
    
    float                       mRadius;
    float                       mRadiusSquared;
    
    float                       mMaxDragLength;
    
    void                        SetRadius(float pRadius){mRadius=pRadius;mRadiusSquared=mRadius*mRadius;}
    
    virtual void                MultiTouch(int x, int y, void *pData);
	virtual void                MultiRelease(int x, int y, void *pData);
    virtual void                MultiDrag(int x, int y, void *pData);
    virtual void                FlushMultiTouch();
    
    Sprite                      *mSpriteBackground;
    Sprite                      *mSpriteKnob;
    
};