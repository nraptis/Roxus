//
//  TestWorld.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TestWorld.hpp"
#include "GLApp.h"

TestWorld::TestWorld() {
    
    mGame = 0;
    
    mLarge = false;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mGame = new TestGame();
    AddSubview(mGame);
    
    mName = "TestWorld";
    
}

TestWorld::~TestWorld() {
    Log("Free(TestWorld)\n");
}

void TestWorld::PositionContent() {
    //Log("---PositionContent(TestWorld)\n");
    if (gVirtualDevWidth > 600.0f && gVirtualDevHeight > 600.0f) {
        mLarge = true;
        SetSize(gApp->mBackgroundLarge);
    } else {
        mLarge = false;
        SetSize(gApp->mBackground);
    }
}

void TestWorld::Update() {
    
}

void TestWorld::Draw() {
    FView::Draw();

    
    Graphics::SetColor(1.0f, 0.22f, 0.22f, 0.75f);
    Graphics::DrawRect(-2.0f, -2.0f, mWidth + 4.0f, mHeight + 4.0f);
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.15f);

    if (mLarge) {
        gApp->mBackgroundLarge.Draw(0.0f, 0.0f);
    } else {
        gApp->mBackground.Draw(0.0f, 0.0f);
    }

    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }

    Graphics::SetColor();


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

    Graphics::SetColor(0.0f, 1.0f, 0.5f, 0.85f);

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

void TestWorld::TouchDown(float pX, float pY, void *pData) {
    
}

void TestWorld::TouchMove(float pX, float pY, void *pData) {
    
}

void TestWorld::TouchUp(float pX, float pY, void *pData) {
    
}

void TestWorld::TouchFlush() {
    
}


