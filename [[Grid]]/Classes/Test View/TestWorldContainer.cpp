//
//  TestWorldContainer.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TestWorldContainer.hpp"
#include "GLApp.h"

TestWorldContainer::TestWorldContainer() {
    mSpriteRotation = gRand.Get(360);
    
    mClipsContent = true;
    
    mWobbleRot = gRand.GetFloat(360.0f);
    
    mWorld1 = 0;
    mWorld2 = 0;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mWorld1 = new TestWorld();
    AddSubview(mWorld1);
    
    
    //mWorld2 = new TestWorld();
    
    
    mName = "TestWorldContainer";
    
}

TestWorldContainer::~TestWorldContainer() {
    Log("Free(TestWorldContainer)\n");
}

void TestWorldContainer::PositionContent() {
    //Log("---PositionContent(TestWorldContainer)\n");
    float aWidth = 1536.0f;
    float aHeight = 1536.0f;
    if (mWorld1) {
        aWidth = mWorld1->GetWidth();
        aHeight = mWorld1->GetHeight();
    }
    SetSize(aWidth, aHeight);
}

void TestWorldContainer::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;
    mWobbleRot += 3.0f;
    if (mWobbleRot >= 360.0f) mWobbleRot -= 360.0f;
}

void TestWorldContainer::Draw() {
    FView::Draw();
    
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
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 20.0f);
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 14.0f);
    }

    Graphics::SetColor(0.75f, 0.85f, 0.05f, 0.85f);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[0],
                       mContainer->mTransformAbsolute.mCornerY[0],
                       mContainer->mTransformAbsolute.mCornerX[1],
                       mContainer->mTransformAbsolute.mCornerY[1], 5.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[1],
                       mContainer->mTransformAbsolute.mCornerY[1],
                       mContainer->mTransformAbsolute.mCornerX[2],
                       mContainer->mTransformAbsolute.mCornerY[2], 5.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[2],
                       mContainer->mTransformAbsolute.mCornerY[2],
                       mContainer->mTransformAbsolute.mCornerX[3],
                       mContainer->mTransformAbsolute.mCornerY[3], 5.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[3],
                       mContainer->mTransformAbsolute.mCornerY[3],
                       mContainer->mTransformAbsolute.mCornerX[0],
                       mContainer->mTransformAbsolute.mCornerY[0], 5.0);
}

void TestWorldContainer::TouchDown(float pX, float pY, void *pData) {
    
}

void TestWorldContainer::TouchMove(float pX, float pY, void *pData) {
    
}

void TestWorldContainer::TouchUp(float pX, float pY, void *pData) {
    
}

void TestWorldContainer::TouchFlush() {
    
}

