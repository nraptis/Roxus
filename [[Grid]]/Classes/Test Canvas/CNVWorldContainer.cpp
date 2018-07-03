//
//  CNVWorldContainer.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVWorldContainer.hpp"
#include "GLApp.h"

CNVWorldContainer::CNVWorldContainer() {

    SetTransformAnchor(0.25f, 0.75f);
    
    mSpriteRotation = gRand.Get(360);
    
    mClipsContent = true;
    
    mWobbleRot = gRand.GetFloat(360.0f);
    
    mWorld1 = 0;
    mWorld2 = 0;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mWorld1 = new CNVWorld();
    AddChild(mWorld1);
    
    
    //mWorld2 = new CNVWorld();
    
    
    mName = "CNVWorldContainer";
    
}

CNVWorldContainer::~CNVWorldContainer() {
    Log("Free(CNVWorldContainer)\n");
}

void CNVWorldContainer::Layout() {
    Log("---Layout(CNVWorldContainer)\n");
    float aWidth = 1536.0f;
    float aHeight = 1536.0f;
    if (mWorld1) {
        aWidth = mWorld1->GetWidth();
        aHeight = mWorld1->GetHeight();
    }
    SetSize(aWidth, aHeight);
}

void CNVWorldContainer::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;
    mWobbleRot += 3.0f;
    if (mWobbleRot >= 360.0f) mWobbleRot -= 360.0f;
}

void CNVWorldContainer::Draw() {
    FCanvas::Draw();
    
    float aWidth = gApp->mTessPattern.mWidth;
    float aHeight = gApp->mTessPattern.mHeight;
    
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.125f);
    
    if(aWidth > 10.0f && aHeight > 10.0f) {
        for (float aX=0;aX<=mWidth;aX+=aWidth) {
            for (float aY=0;aY<=mHeight;aY+=aHeight) {
                gApp->mTessPattern.Draw(aX, aY);
            }
        }
    }
    
    Graphics::SetColor();
    
    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }



    Graphics::ClipDisable();
    Graphics::ResetMatrixModelView();
    Graphics::ResetMatrixProjection();
    //Graphics::Ortho2D(0, gDeviceWidth, gDeviceHeight, 0); //, -4096.0f, 4096.0f);

    FMatrix aProj = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -1024.0f, 1024.0f);
    Graphics::SetMatrix(aProj);



    for (int i=0;i<4;i++) {

        Graphics::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
        Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 20.0f);
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 14.0f);
    }

    Graphics::SetColor(0.75f, 0.85f, 0.05f, 0.85f);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0],
                       mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1], 5.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1],
                       mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2], 5.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2],
                       mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3], 5.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3],
                       mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0], 5.0);
}

void CNVWorldContainer::TouchDown(float pX, float pY, void *pData) {
    
}

void CNVWorldContainer::TouchMove(float pX, float pY, void *pData) {
    
}

void CNVWorldContainer::TouchUp(float pX, float pY, void *pData) {
    
}

void CNVWorldContainer::TouchFlush() {
    
}

