//
//  Animation.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "TextBubble.h"
#include "MainApp.h"

TextBubble::TextBubble()
{
    mX = 0.0f;
    mY = 0.0f;
    
    mWidth = 0.0f;
    mHeight = 0.0f;
    
    mColor = FColor(1.0f, 1.0f, 1.0f, 1.30f);
    
    mYSpeed = -0.65f;
    
    mScale = 0.025f;
    mScaleSpeed = 0.2f;
    
    for(int i=0;i<32;i++)
    {
        mTextX[i] = 0.0f;
        
        mDrawX[i] = 0.0f;
        mDrawY[i] = 0.0f;
        
    }
    
    mMode = 0;
    mModeTimer = 0;
    
    mFont = 0;
}

TextBubble::~TextBubble()
{
    
}

void TextBubble::Update()
{
    mY += mYSpeed;
    
    if(mMode == 0)
    {
        mScale += mScaleSpeed;
        mScaleSpeed -= 0.0225f;
        
        if(mScaleSpeed < 0)
        {
            
            if(mScale <= 1.0f)
            {
                mScale = 1.0f;
                mMode = 1;
                mModeTimer = 40;
            }
            
            if(mScale <= 0.85f)
            {
                //mScale = 0.85f;
                //mMode = 1;
                //mModeTimer = 60;
            }
        }
    }
    else if(mMode == 1)
    {
        mModeTimer--;
        if(mModeTimer <= 0)
        {
            mMode = 2;
            mModeTimer = 0;
        }
    }
    else
    {
        mScale -= 0.05f;
        mColor.mAlpha -= 0.065f;
        
        if(mScale <= 0.0f)
        {
            Kill();
        }
        
        //mColor.mAlpha -= 0.040f;
        if(mColor.mAlpha <= 0.0f)
        {
            Kill();
        }
    }
}

void TextBubble::Draw()
{
    Graphics::SetColor(mColor);
    
    
    
    int aCharIndex = 0;
    
    
    for(int i=0;i<mText.mLength;i++)
    {
        mDrawX[i] = mX + mScale * mTextX[i];
        mDrawY[i] = mY;
    }
    
    for(int i=0;i<mText.mLength;i++)
    {
        aCharIndex = (int)(mText.mData[i]);
        if((aCharIndex >= 0) && (aCharIndex < 256))
        {
            gApp->mFontMainDisplayStroke.mCharacterSprite[aCharIndex].Draw(mDrawX[i], mDrawY[i], mScale * 0.65f, 0.0f);
        }
    }
    
    
    for(int i=0;i<mText.mLength;i++)
    {
        aCharIndex = (int)(mText.mData[i]);
        if((aCharIndex >= 0) && (aCharIndex < 256))
        {
            gApp->mFontMainDisplayMiddle.mCharacterSprite[aCharIndex].Draw(mDrawX[i], mDrawY[i], mScale * 0.65f, 0.0f);
        }
    }
    
    
    for(int i=0;i<mText.mLength;i++)
    {
        aCharIndex = (int)(mText.mData[i]);
        if((aCharIndex >= 0) && (aCharIndex < 256))
        {
            gApp->mFontMainDisplayFront.mCharacterSprite[aCharIndex].Draw(mDrawX[i], mDrawY[i], mScale * 0.65f, 0.0f);
        }
    }
    
    
    
    
    /*
    
    if(mFont != 0 && mText.mLength > 0)
    {
        //mFont->Center(mText, mX, mY, mScale);
    }
    
    for(int i=0;i<mText.mLength;i++)
    {
        Graphics::SetColorSwatch(i, 0.25f);
    
        Graphics::DrawPoint(mTextX[i] + mX, mY, 14.0f);
        Graphics::DrawLine(mTextX[i] + mX, mY - 64.0f, mX, mY);
    
    }
    
    */
    
    
    Graphics::SetColor();
}

void TextBubble::SetUp(FFont *pFont, FString pText, float pX, float pY)
{
    mText = pText.c();
    mFont = pFont;
    
    if(mFont)
    {
        mWidth = mFont->PlotWidthCentered(pText.c(), mTextX);
        //mWidth = mFont->Width(mText.c());
        mHeight = mFont->mPointSize;
        
        for(int i=0;i<pText.mLength;i++)
        {
            mTextX[i] *= 0.65f;
            
            //printf("Font[%d] X[[%f]]\n", i, mTextX[i]);
        }
        
    }
    
    mX = pX;
    mY = pY;
}


