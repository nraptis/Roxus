//
//  SpriteSequence.cpp
//  Mustache
//
//  Created by Nick Raptis on 9/9/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "SpriteSequence.h"

#include "FileSequence.h"


SpriteSequence::SpriteSequence()
{
    mSprite = 0;
    mSpriteCount = 0;
}

SpriteSequence::~SpriteSequence()
{
    Free();
}

void SpriteSequence::Free()
{
    delete [] mSprite;
    mSprite = 0;
    
    mSpriteCount = 0;
}

void SpriteSequence::Load(const char *pFilePrefix, int pStartIndex, int pEndIndex)
{
    mSpriteCount = (pEndIndex - pStartIndex) + 1;
    
    if(mSpriteCount <= 0)
    {
        mSpriteCount = 0;
        delete mSprite;
    }
    else
    {
        mSprite = new Sprite[mSpriteCount];
        
        FString aBasePath = FString(pFilePrefix);
        FString aNumberString;
        FString aFile;
        
        for(int aIndex=pStartIndex;aIndex<=pEndIndex;aIndex++)
        {
            for(int aLeadingZeroCount=0;aLeadingZeroCount<8;aLeadingZeroCount++)
            {
                if(mSprite[aIndex - pStartIndex].mWidth > 0)break;
                
                aNumberString = FString(aIndex);
                int aLengthDifference = aLeadingZeroCount - aNumberString.mLength;
                if(aLengthDifference > 0)aNumberString.Insert('0', aLengthDifference, 0);
                aFile.Write(aBasePath,0);
                aFile.Write(aNumberString,aBasePath.mLength);
                aFile.SetChar(aBasePath.mLength + aNumberString.mLength, 0);
                
                mSprite[aIndex - pStartIndex].Load(aFile.c());
            }
        }
    }
    
}

void SpriteSequence::Draw(float pX, float pY, float pFrame)
{
    int aFrame = (int)(pFrame + 0.5f);
    if(aFrame >= mSpriteCount)aFrame = (mSpriteCount - 1);
    if(aFrame < 0)aFrame = 0;
    
    if(mSpriteCount > 0)
    {
        mSprite[aFrame].Draw(pX, pY);
    }
}

void SpriteSequence::Draw(float pX, float pY, float pFrame, float pScale, float pSpriteRotation)
{
    int aFrame = (int)(pFrame + 0.5f);
    if(aFrame >= mSpriteCount)aFrame = (mSpriteCount - 1);
    if(aFrame < 0)aFrame = 0;
    
    if(mSpriteCount > 0)
    {
        mSprite[aFrame].Draw(pX, pY, pScale, pSpriteRotation);
    }
}

void SpriteSequence::Center(float pX, float pY, float pFrame)
{
    int aFrame = (int)(pFrame + 0.5f);
    if(aFrame >= mSpriteCount)aFrame = (mSpriteCount - 1);
    if(aFrame < 0)aFrame = 0;
    
    if(mSpriteCount > 0)
    {
        mSprite[aFrame].Center(pX, pY);
    }
}




