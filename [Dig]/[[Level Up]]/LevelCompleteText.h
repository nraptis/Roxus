//
//  LevelCompleteText.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/13/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__LevelCompleteText__
#define __DigMMMac__LevelCompleteText__

#include "FObject.h"
#include "LevelCompleteTextLetter.h"

class LevelCompleteText
{
public:
    LevelCompleteText();
    virtual ~LevelCompleteText();
    
    void                                Update();
    
    void                                Draw(bool pShadow);
    void                                Draw();
    void                                DrawShadow();
    
    void                                SetUpTimeUp();
    void                                SetUpWin();
    void                                SetUpLetters();
    
    
    float                               mX;
    float                               mY;
    
    float                               mOffsetX;
    float                               mOffsetY;
    
    float                               mScale;
    float                               mRotation;
    
    void                                AddLetter(FSprite *pSpriteShadow, FSprite *pSprite, float pX, float pY);
    void                                LetterBounce();
    bool                                mLetterBounce;
    int                                 mLetterBounceIndex;
    int                                 mLetterBounceTimer;
    float                               mLetterBounceScale;
    FList                               mLetters;
    
    
    
    float                               mWidth;
    float                               mHeight;
    
    

    
    
    bool                                mEnterAnimation;
    float                               mEnterAnimationPercent;
    void                                EnterAnimationStart();
    void                                EnterAnimationUpdate(float pPercent);
    void                                EnterAnimationFinish();
    
    
    float                               mSwaySin;
    
    
};




#endif /* defined(__DigMMMac__LevelCompleteText__) */
