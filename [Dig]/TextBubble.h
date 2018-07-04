//
//  TextBubble.h
//  CoreDemo
//
//  Created by Nick Raptis on 11/9/13.
//  Copyright (c) 2013 Union AdWorks Inc. All rights reserved.
//

#ifndef __CoreDemo__TextBubble__
#define __CoreDemo__TextBubble__


#include "FObject.h"
#include "FFont.h"
#include "FColor.h"

class TextBubble : public FObject
{
public:
    
    TextBubble();
    virtual ~TextBubble();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    SetUp(FFont *pFont, FString pText, float pX, float pY);
    
    float                                   mX;
    float                                   mY;
    
    float                                   mWidth;
    float                                   mHeight;
    
    
    float                                   mTextX[32];
    
    
    float                                   mDrawX[32];
    float                                   mDrawY[32];
    
    
    float                                   mYSpeed;
    
    float                                   mScale;
    float                                   mScaleSpeed;
    
    int                                     mMode;
    int                                     mModeTimer;
    
    FColor                                  mColor;
    
    FFont                                   *mFont;
    
    FString                                 mText;
    
};


#endif /* defined(__CoreDemo__TextBubble__) */
