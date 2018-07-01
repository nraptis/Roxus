//
//  TempView.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/14/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TempView.hpp"
#include "GLApp.h"

TempView::TempView() {
    mSpriteRotation = gRand.Get(360);
    mClipsContent = true;
    
    mSphereRotation1 = gRand.Get(360);
    mSphereRotation2 = gRand.Get(360);
    
    mSpriteStartAngle = gRand.Get(360);
    mSpriteEndAngle = gRand.Get(360);
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
}

TempView::~TempView() {
    
}

void TempView::PositionContent() {
    
}

void TempView::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;
    
    mSphereRotation1 += 0.25f;
    if (mSphereRotation1 >= 360.0f) mSphereRotation1 -= 360.0f;
    
    mSphereRotation2 += 3.0f;
    if (mSphereRotation2 >= 360.0f) mSphereRotation2 -= 360.0f;
    
    mSpriteStartAngle -= 0.5f;
    if (mSpriteStartAngle < -180.0f) { mSpriteStartAngle += 360.0f; }
    
    mSpriteEndAngle += 2.0f;
    if (mSpriteEndAngle > 360.0f) { mSpriteEndAngle -= 1080.0f;}
}

void TempView::Draw() {
    FView::Draw();
    //gApp->mTestSprite.Draw(mWidth2, mHeight2, 2.0, mSpriteRotation, 1);
    gApp->mTestSprite.Draw(mWidth2, mHeight2, 2.0, mSpriteRotation);
    gApp->mBackground.Center(mWidth2, mHeight2);
    
    Graphics::SetColor(0.66f, 0.66f, 0.66f, 0.75f);
    
    Graphics::OutlineRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f, 3.0f);
    
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.75f);
    Graphics::OutlineRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 2.0f);
    
    
    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }
    
    
    
}

void TempView::TouchDown(float pX, float pY, void *pData) {
    
}

void TempView::TouchMove(float pX, float pY, void *pData) {
    
}

void TempView::TouchUp(float pX, float pY, void *pData) {
    
}

void TempView::TouchFlush() {
    
}

