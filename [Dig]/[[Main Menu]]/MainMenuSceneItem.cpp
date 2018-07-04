//
//  MainMenuSceneItem.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/3/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "MainMenuSceneItem.h"
#include "MainApp.h"

MainMenuSceneItem::MainMenuSceneItem(FSprite *pSprite)
{
    mRelativeX = 0.0f;
    mRelativeY = 0.0f;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mScale = 1.0f;
    
    mSprite = pSprite;
}

MainMenuSceneItem::~MainMenuSceneItem()
{
    
}

void MainMenuSceneItem::Update()
{
    
}

void MainMenuSceneItem::Draw()
{
    
    
    if(mSprite)
    {
        Graphics::SetColor(0.66f);
        mSprite->Draw(mX, mY, mScale, 0.0f);
    }
    
    EnumList(MainMenuSceneItem, aItem, mItemList)
    {
        aItem->Draw();
    }
}

void MainMenuSceneItem::AddItem(MainMenuSceneItem *pItem)
{
    mItemList.Add(pItem);
}

void MainMenuSceneItem::SetRelativePos(float pX, float pY)
{
    mRelativeX = pX;
    mRelativeY = pY;
    
}

void MainMenuSceneItem::Place(float pCenterX, float pCenterY, float pScale)
{
    mScale = pScale;
    
    mX = pCenterX + mRelativeX * mScale;
    mY = pCenterY + mRelativeY * mScale;
    
    float aWidth = 128.0f;
    float aHeight = 128.0f;
    
    if(mSprite)
    {
        aWidth = mSprite->mWidth;
        aHeight = mSprite->mHeight;
    }
    

    
    EnumList(MainMenuSceneItem, aItem, mItemList)
    {
        aItem->Place(mX, mY, mScale);
    }
}

/*
void MainMenuRockCrystal::Twinkle()
{
    FParticle *aTwinkle = new FParticle(gApp->mEffectTwinkle[gRand.Get(2)]);
    
    aTwinkle->SetPos(gRand.F(-80.0f, 80.0f), gRand.F(-80.0f, 80.0f));
    aTwinkle->SetRotation(-20.0f);
    aTwinkle->SetScale(0.05f);
    aTwinkle->mScaleSpeed = 0.20f + gRand.GetFloat(0.02f);
    aTwinkle->mScaleSpeedAdd = -0.0125f;
    aTwinkle->mRotationSpeed = gRand.GetFloat(0.5f) + 1.5f;
    
    mTwinkleList.Add(aTwinkle);
}
*/

//MainMenuRockCrystal();
//virtual ~MainMenuRockCrystal();
//virtual void                            Update();
