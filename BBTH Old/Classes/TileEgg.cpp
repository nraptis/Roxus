//
//  TileEgg.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/13/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "TileEgg.h"
#include "GLApp.h"

TileEgg::TileEgg()
{
    mType = TILE_TYPE_EGG;
    mMatchType = gRand.Get(5);

    
    
    mMatchAnimationFade = 0.0f;
    mMatchAnimationOuterFrame = 0.0f;
    mMatchAnimationInnerFrame = 0.0f;
    
    mMatchShakeX = 0.0f;
    mMatchShakeY = 0.0f;
}

TileEgg::~TileEgg()
{
    
}

void TileEgg::Update()
{
    Tile::Update();
    
    if(mMatched)
    {
        mMatchAnimationInnerFrame = gApp->mSequenceEffectTileBurn[1].LoopFrame(mMatchAnimationInnerFrame, 0.72f);
        mMatchAnimationOuterFrame = gApp->mSequenceEffectTileBurn[0].LoopFrame(mMatchAnimationOuterFrame, 0.58f);
    }
    
}

void TileEgg::Draw()
{
    gApp->mTileMatchableWhole[mMatchType].Center(mX, mY);
    
    if(mSelected){
        gApp->mTileMatchableFrontSelected[mMatchType].Center(mX, mY);
    }
}

void TileEgg::DrawEffectsUnder(int pDepth)
{
    if(mMatched)
    {
        if(pDepth == 0){
            float aScale = 1.35f;
            gApp->mSequenceEffectTileBurn[1].Draw(mMatchAnimationInnerFrame, mX, mY, aScale, 0.0f);
        }
        if(pDepth == 1){
            float aScale = 1.10f;
            gApp->mSequenceEffectTileBurn[0].Draw(mMatchAnimationOuterFrame, mX, mY, aScale, 0.0f);
        }
    }
}

void TileEgg::DrawEffectsOver(int pDepth)
{
    Tile::DrawEffectsOver(pDepth);
    
    //gApp->mEffectLaserBurn.Draw(mX - 10, mY, 0.25f, 200.0f);
    
}

void TileEgg::SetUp(int pGridX, int pGridY, int pMatchType)
{
    Tile::SetUp(pGridX, pGridY);
    mMatchType = pMatchType;
}

void TileEgg::Select()
{
    mSelected = true;
}

void TileEgg::Deselect()
{
    mSelected = false;
}

void TileEgg::Matched()
{
    Tile::Matched();
    //mMatched = true;
    mMatchAnimationFade = 0.0f;
    mMatchAnimationOuterFrame = 0.0f;
    mMatchAnimationInnerFrame = 0.0f;
}






