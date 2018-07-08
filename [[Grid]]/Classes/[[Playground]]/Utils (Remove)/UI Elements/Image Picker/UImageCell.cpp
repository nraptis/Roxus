//
//  UImageCell.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/13/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UImageCell.h"
#include "UImagePicker.h"

UImageCell::UImageCell()
{
    mName = "Image Cell (Blank)";
    
    mDestroySprite = false;
    mSprite = 0;
    
}

UImageCell::UImageCell(FSprite *pSprite, bool pDestroy)
{
    mName = "Image Cell (Sprite)";
    
    mDestroySprite = pDestroy;
    mSprite = pSprite;
}

UImageCell::UImageCell(const char *pPath)
{
    mName = "Image Cell (Sprite File)";
    
    mSprite = new FSprite();
    mSprite->Load(pPath);
    mDestroySprite = true;
}

UImageCell::~UImageCell()
{
    if(mDestroySprite == true)
    {
        if(mSprite != 0)
        {
            delete mSprite;
            mSprite = 0;
        }
    }
}

void UImageCell::SetUp(float pWidth, float pHeight)
{
    SetUp(mX, mY, mWidth, mHeight);
}

void UImageCell::SetUp(float pX, float pY, float pWidth, float pHeight)
{
    SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    mSpriteQuad.SetQuad(0.0f, 0.0f, pWidth, 0.0f, 0.0f, pHeight, pWidth, pHeight);
    
    if(mSprite)
    {
        mSpriteQuad.SetTextureAspectFit(mSprite);
    }
}

void UImageCell::Update()
{
    UMenuItem::Update();
}

void UImageCell::Draw()
{
	Graphics::SetColor();
    if(mSprite)
    {
        mSpriteQuad.Draw(mSprite);
    }
    
    if(mTouchDownInside && (mTouchCanceled == false))
    {
        Graphics::SetColor(1.0f, 0.15f, 0.15f, 0.75f);
        
    }
    else Graphics::SetColor(0.85f, 0.85f, 0.85f, 0.75f);
    
    Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 2);
    Graphics::SetColor();
}

void UImageCell::TouchUp(float pX, float pY, void *pData)
{
    if((mTouchCanceled == false) && (mParent != 0))
    {
        mParent->Notify(this, IMG_PICK_RESPONSE_SPRITE, mSprite);
    }
    
}

UImageCellSequence::UImageCellSequence()
{
    mSequence = 0;
    
    mFrame = 0;
    mFrameMax = 1.0f;
}

UImageCellSequence::UImageCellSequence(FSpriteSequence *pSequence, bool pDestroy)
{
    mSequence = pSequence;
    
    if(mSequence)
    {
        mFrameMax = mSequence->GetMaxFrame();
        mDestroySprite = pDestroy;
    }
    
    mFrame = 0;
    mFrameMax = 1.0f;
}

UImageCellSequence::~UImageCellSequence()
{
    if(mDestroySprite)
    {
        if(mSequence != 0)
        {
            delete mSequence;
        }
        mSequence = 0;
    }
}

void UImageCellSequence::SetUp(float pWidth, float pHeight)
{
    SetUp(mX, mY, pWidth, pHeight);
}

void UImageCellSequence::SetUp(float pX, float pY, float pWidth, float pHeight)
{
    if(mSequence)
    {
        mSprite = mSequence->Get(mFrame);
        mFrameMax = mSequence->GetMaxFrame();
    }
    UImageCell::SetUp(pX, pY, pWidth, pHeight);
    if(mSequence)mSprite = 0;
}

void UImageCellSequence::Update()
{
    UImageCell::Update();
    
    if(mSequence)
    {
        mFrameMax = mSequence->GetMaxFrame();
        mFrame += 0.15f;
        if(mFrame >= mFrameMax)mFrame -= mFrameMax;
    }
}

void UImageCellSequence::Draw()
{
    if(mSequence)
    {
        FSprite *aSprite = mSequence->GetSprite(mFrame);
        SetUp(mX, mY, mWidth, mHeight);
        mSprite = aSprite;
    }
    
    UImageCell::Draw();
    
    mSprite = 0;
}

void UImageCellSequence::TouchUp(float pX, float pY, void *pData)
{
    if((mTouchCanceled == false) && (mParent != 0))
    {
        mParent->Notify(this, IMG_PICK_RESPONSE_SEQUENCE, mSequence);
    }
}

