//
//  LevelCompleteTextLetter.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/13/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__LevelCompleteTextLetter__
#define __DigMMMac__LevelCompleteTextLetter__

#include "FSprite.h"

class LevelCompleteTextLetter// : public Object
{
public:
    
    LevelCompleteTextLetter();
    virtual ~LevelCompleteTextLetter();
    
    virtual void                    Update();
    
    void                            Draw(FSprite *pSprite, float pX, float pY, float pScale);
    virtual void                    Draw(float pX, float pY, float pScale);
    virtual void                    DrawShadow(float pX, float pY, float pScale);
    virtual void                    DrawStroke(float pX, float pY, float pScale);
    
    
    
    FSprite                         *mSprite;
    FSprite                         *mSpriteShadow;
    
    float                           mX;
    float                           mY;
    
    
    void                            Bounce();
    float                           mBounceAmount;
    int                             mBounceTimer;
    float                           mBounceSin;
    float                           mBounceSinSpeed;
    float                           mBounceScale;
    
    
    
    int                             mSkewDir;
    float                           mSkewFactor;
    float                           mBaseX;
    float                           mBaseY;
    
    
    float                           mExtraScale;
    float                           mExtraX;
    float                           mExtraY;
    
    float                           mCurrentOffsetX;
    float                           mCurrentOffsetY;
    float                           mCurrentOffsetRotation;
    
    float                           mExtraRotation;
    
    
    float                           mFade;
    float                           mExtraFade;
    
    
    float                           mExtraShadowScale;
    
    
    
    float                           mArc;
    
    
};

#endif /* defined(__DigMMMac__LevelCompleteTextLetter__) */
