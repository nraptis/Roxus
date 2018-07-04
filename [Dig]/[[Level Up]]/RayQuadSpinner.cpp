//
//  RayQuadSpinner.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/15/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "RayQuadSpinner.h"


RayQuadSpinnerSpoke::RayQuadSpinnerSpoke()
{
    //mQuadBase
    //mQuad
}


void RayQuadSpinnerSpoke::Transform(float pX, float pY, float pScale, float pRotation, float pAlpha)
{
    
    
}

void RayQuadSpinnerSpoke::Draw()
{
    //mBaseQuadList
}





RayQuadSpinner::RayQuadSpinner()
{
    mGenerate = true;
    
    mSpokeCount = 0;
}

RayQuadSpinner::~RayQuadSpinner()
{
    
}

void RayQuadSpinner::Update()
{
    if(mGenerate)Generate();
    
}

void RayQuadSpinner::Draw()
{
    if(mGenerate)Generate();
    
    Graphics::DrawRect(mX - 20, mY - 20, 44, 44);
    
    FDrawQuad aQuad;
    aQuad.SetColorBottom(1.0f, 0.0f, 0.5f, 0.7f);
    aQuad.SetColorTop(1.0f, 1.0f, 0.6f, 0.15f);
    
    aQuad.SetRect(mX, mY, 40, 200);
    aQuad.Draw();
    
}

void RayQuadSpinner::Transform(float pX, float pY, float pScale, float pRotation, float pAlpha)
{
    mX = pX;
    mY = pY;
    
    mScale = pScale;
    mRotation = pRotation;
    
    mAlpha = pAlpha;
    
    if(mGenerate)Generate();
    
}

void RayQuadSpinner::SetSpokeCount(int pCount)
{
    mSpokeCount = pCount;
    mGenerate = true;
}

void RayQuadSpinner::SetColorInner(FColor pColorInner)
{
    mGenerate = true;
    mColorInner = pColorInner;
}


void RayQuadSpinner::SetColorOuter(FColor pColorOuter)
{
    mGenerate = true;
    mColorOuter = pColorOuter;
}

void RayQuadSpinner::SetRayDist(float pRayDist)
{
    mGenerate = true;
    mRayDist = pRayDist;
}

void RayQuadSpinner::SetRayLength(float pRayLength)
{
    mGenerate = true;
    mRayLength = pRayLength;
}

void RayQuadSpinner::SetRayWidthInner(float pWidth)
{
    mGenerate = true;
    mRayWidthInner = pWidth;
}

void RayQuadSpinner::SetRayWidthOuter(float pWidth)
{
    mGenerate = true;
    mRayWidthOuter = pWidth;
}

void RayQuadSpinner::SetRayWidth(float pWidthInner, float pWidthOuter)
{
    mGenerate = true;
    SetRayWidthInner(pWidthInner);
    SetRayWidthOuter(pWidthOuter);
}


void RayQuadSpinner::Generate()
{
    mGenerate = false;
}



