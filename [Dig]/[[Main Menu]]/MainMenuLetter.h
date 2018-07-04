//
//  MainMenuLetter.h
//  Gnomes
//
//  Created by Nick Raptis on 3/28/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#ifndef Gnomes_MainMenuLetter_h
#define Gnomes_MainMenuLetter_h

#include "MainApp.h"

class MainMenuLetter// : public Object
{
public:
    
    MainMenuLetter(FSprite *pSprite);
    virtual ~MainMenuLetter();
    
    virtual void                    Update();
    virtual void                    Draw();
    
    FSprite                         *mSprite;
    
    FSound                          *mSound;
    float                           mSoundPitch;
    
    float                           mX;
    float                           mY;
    
    
    
    virtual void                    Bounce();
    
    float                           mRotSin;
    float                           mRotSinSpeed;
    float                           mRotAmount;
    
    float                           mBounceSin;
    float                           mBounceAmount;
};

class MainMenuLetterRow2 : public MainMenuLetter
{
public:
    
    MainMenuLetterRow2(FSprite *pSprite);
    virtual ~MainMenuLetterRow2();
    
    virtual void                    Bounce();
};

#endif
