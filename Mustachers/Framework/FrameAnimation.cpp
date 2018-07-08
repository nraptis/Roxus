//
//  FrameAnimation.cpp
//  Wrangler
//
//  Created by Nick Raptis on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "FrameAnimation.h"


FrameAnimation::FrameAnimation()
{
    mOffsetX=0;
    mOffsetY=0;
}

FrameAnimation::~FrameAnimation()
{
    Clear();
}

void FrameAnimation::Clear()
{
    FreeList(Sprite, mSpriteList);
}

Sprite *FrameAnimation::GetSprite(float pFrame)
{
    return (Sprite*)(mSpriteList.FetchBest(pFrame));
}

void FrameAnimation::Load(const char *pFilePrefix, int pStartIndex)
{
    Clear();
    
    bool aFoundAny = false;
    int aLeadingZeroCount = 0;
    int aLengthDifference;
    
    
    FString aBasePath = FString(pFilePrefix);
    FString aNumberString;
    FString aFile;
    
    Sprite *aSprite = new Sprite();
    
    while((aLeadingZeroCount < 20) && (aFoundAny == false))
    {
        aNumberString = FString(pStartIndex);
        aLengthDifference = aLeadingZeroCount - aNumberString.mLength;
        if(aLengthDifference > 0)aNumberString.Insert('0', aLengthDifference, 0);
        aFile.Write(aBasePath,0);
        aFile.Write(aNumberString,aBasePath.mLength);
        
        
        aSprite->Load(aFile);
        
        if(aSprite->mWidth > 0)
        {
            aFoundAny = true;
            mSpriteList += aSprite;
            aSprite = new Sprite();
            
            int aIndex = pStartIndex+1;
            bool aSuccess = true;
            
            while(aSuccess == true)
            {
                aNumberString = FString(aIndex);
                aLengthDifference = aLeadingZeroCount - aNumberString.mLength;
                if(aLengthDifference > 0)aNumberString.Insert('0', aLengthDifference, 0);
                aFile.Write(aBasePath,0);
                aFile.Write(aNumberString,aBasePath.mLength);
                
                aSprite->Load(aFile);
                if(aSprite->mWidth > 0)
                {
                    mSpriteList += aSprite;
                    aSprite = new Sprite();
                }
                else
                {
                    aSuccess=false;
                }
                
                aIndex++;
            }   
        }
        aLeadingZeroCount++;
    }
    
    delete aSprite;
}

void FrameAnimation::Load(const char *pFilePrefix, int pStartIndex, int pEndIndex, int pLeadingZeros)
{
    Clear();
 
    /*
    int aStartIndex=pStartIndex;
    int aEndIndex=pEndIndex;
    
    if(aSize >= 0)
    {
        
        
        
        
        FString aBasePath = FString(pFilePrefix);
        FString aNumberString;// = FString(i);
        //String aExtention = FString(".") + FString(pType);
        FString aFile;
        
        for(int i=pStartIndex;i<=pEndIndex;i++)
        {
            aNumberString = FString(((int)i));
            int aLengthDifference = pLeadingZeros - aNumberString.mLength;
            if(aLengthDifference > 0)aNumberString.Insert('0', aLengthDifference, 0);
            aFile.Write(aBasePath,0);
            aFile.Write(aNumberString,aBasePath.mLength);
            //aFile.Write(aExtention,aBasePath.mLength + aNumberString.mLength);
            
            mSprite[mCount].Load(aFile);
            
            if(mSprite[mCount].mWidth > 0)
            {
                mCount++;
            }
        }
    }
    */
}










FrameRef::FrameRef(FrameAnimation *pFrameAnimation)
{
    mFrameAnimation = pFrameAnimation;
    
    mCount = mFrameAnimation->mSpriteList.mCount;
    mMax = (float)mCount;
    
    mFrame = 0;
    
    mSpeed = 0.33f;
    
    mPlayOnce = false;
    mCompleted = false;
}

FrameRef::~FrameRef()
{
    
}

void FrameRef::Update()
{
    mFrame += mSpeed;
    if(mSpeed > 0)
    {
        if(mPlayOnce)
        {
            if(mFrame >= mMax)
            {
                mFrame = mMax;
                mCompleted=true;
            }
        }
        else
        {
            if(mFrame >= mMax)
            {
                mFrame -= mMax;
            }
        }
    }
    else
    {
        if(mPlayOnce)
        {
            if(mFrame < 0)
            {
                mFrame=0;
                mCompleted=true;
            }
        }
        else
        {
            if(mFrame < 0)mFrame += mMax;
        }
    }
}

void FrameRef::Draw(float x, float y, float pScale, float pRotationDegrees, int pFacing)
{
    Sprite *aSprite = mFrameAnimation->GetSprite(mFrame);
    
    if(aSprite)
    {
    float aScaleX = 1.0f;
    float aScaleY = 1.0f;
    float aScaleZ = 1.0f;
    
    if(pFacing < 0)aScaleX = -1.0f;
    
    
    Graphics::MatrixPush();
    
    Graphics::Translate(x, y);
    Graphics::Scale(aScaleX, aScaleY, aScaleZ);
    
    Graphics::Translate(mFrameAnimation->mOffsetX, mFrameAnimation->mOffsetY);
    Graphics::RotateZ(pRotationDegrees);
    
    gGraphics.DrawSprite(aSprite->mTextureVertex, aSprite->mTextureCoord, aSprite->mBindIndex);
    
    Graphics::MatrixPop();
    }
}

void FrameRef::PlayOnce()
{
    mCompleted=false;
    mPlayOnce=true;
    Start();
    
}

void FrameRef::Start()
{
    mFrame=0;
}