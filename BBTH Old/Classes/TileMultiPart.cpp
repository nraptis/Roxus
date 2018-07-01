//
//  TileMultiPart.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/2/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "TileMultiPart.h"
#include "GLApp.h"

TileMultiPart::TileMultiPart(){
    mGridOffsetX = 0;
    mGridOffsetY = 0;
    
    mMultiParent = 0;
    
    mMultiTilePart = true;
}

TileMultiPart::~TileMultiPart(){
    
}

void TileMultiPart::DrawEffectsUnder(int pDepth)
{
    if(pDepth == 0){
        Graphics::SetColor(1.0f, 0.5f, 0.5f, 1.0f);
        gApp->mEffectParticleWarmSmall[gRand.Get(4)].Center(mX, mY);
        Graphics::SetColor();
    }
}

void TileMultiPart::DrawEffectsOver(int pDepth)
{
    
}
