//
//  BoardContainer.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/11/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "BoardContainer.h"
#include "GLApp.h"
#include "Board.h"

BoardContainer::BoardContainer()
{
    mBoard = new Board();
    AddSubview(mBoard);
    
}

BoardContainer::~BoardContainer()
{
    
}


void BoardContainer::Layout(float pX, float pY, float pWidth, float pHeight)
{
    SetFrame(pX, pY, pWidth, pHeight);
    mBoard->Layout();
    
    
    float aFitWidth = ((float)mBoard->mGridWidth) * gTileWidth;
    float aFitHeight = ((float)mBoard->mGridScreenHeight) * gTileHeight;
    
    float aScaleX = pWidth / aFitWidth;
    float aScaleY = pHeight / aFitHeight;
    
    float aScale = aScaleX;
    if(aScaleY < aScaleX)aScale = aScaleY;
    
    mBoard->SetTransformScale(aScale);
    
    float aBoardWidth = aFitWidth * aScale;
    float aExtraSpacing = (pWidth - aBoardWidth) / 2.0f;
    
    mBoard->SetTransformTranslate(aExtraSpacing, 0.0f);
}

void BoardContainer::Notify(void *pSender)
{
    
}

void BoardContainer::Update()
{
    
}

void BoardContainer::Draw()
{
    //Graphics::SetColor(gRand.F(0.55f, 0.60f), 0.77f, 0.33f, 0.5f);
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    Graphics::SetColor();
    
}



