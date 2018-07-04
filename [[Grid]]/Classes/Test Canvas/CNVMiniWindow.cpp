//
//  CNVMiniWindow.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/18/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVMiniWindow.hpp"
#include "GLApp.h"

CNVMiniWindow::CNVMiniWindow() {
    mSpriteRotation = gRand.Get(360);
    mClipEnabled = false;
    
    //mRecievesOutsideTouches = true;
    
    mSphereRotation1 = gRand.Get(360);
    mSphereRotation2 = gRand.Get(360);
    
    mTestAngle = gRand.Get(360);
    mSpriteEndAngle = gRand.Get(360);
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
}

CNVMiniWindow::~CNVMiniWindow() {
    
}

void CNVMiniWindow::Layout() {
    Log("---Layout(CNVMiniWindow)\n");
}

void CNVMiniWindow::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;
    
    mSphereRotation1 += 0.25f;
    if (mSphereRotation1 >= 360.0f) mSphereRotation1 -= 360.0f;
    
    mSphereRotation2 += 3.0f;
    if (mSphereRotation2 >= 360.0f) mSphereRotation2 -= 360.0f;
    
    mTestAngle -= 0.5f;
    if (mTestAngle < -180.0f) { mTestAngle += 360.0f; }
    
    mSpriteEndAngle += 2.0f;
    if (mSpriteEndAngle > 360.0f) { mSpriteEndAngle -= 1080.0f;}
}

void CNVMiniWindow::Draw() {
    FCanvas::Draw();

    Graphics::SetColor(1.0f, 0.66f, 0.66f, 0.75f);
    Graphics::OutlineRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f, 3.0f);
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.75f);
    Graphics::OutlineRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 2.0f);


    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);

        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }

    /*
    
    Graphics::ClipDisable();
    Graphics::ResetMatrixModelView();
    Graphics::ResetMatrixProjection();

    FMatrix aProj = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -1024.0f, 1024.0f);
    Graphics::SetMatrix(aProj);

    for (int i=0;i<4;i++) {
        Graphics::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 20.0f);
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 14.0f);
    }

    Graphics::SetColor(1.0f, 1.0f, 0.5f, 0.75f);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[0], mContainer->mTransformAbsolute.mCornerY[0],
                       mContainer->mTransformAbsolute.mCornerX[1], mContainer->mTransformAbsolute.mCornerY[1], 6.0);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[1], mContainer->mTransformAbsolute.mCornerY[1],
                       mContainer->mTransformAbsolute.mCornerX[2], mContainer->mTransformAbsolute.mCornerY[2], 6.0);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[2], mContainer->mTransformAbsolute.mCornerY[2],
                       mContainer->mTransformAbsolute.mCornerX[3], mContainer->mTransformAbsolute.mCornerY[3], 6.0);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[3], mContainer->mTransformAbsolute.mCornerY[3],
                       mContainer->mTransformAbsolute.mCornerX[0], mContainer->mTransformAbsolute.mCornerY[0], 6.0);

    */


    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 30.0f);
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 24.0f);
    }
    
}

void CNVMiniWindow::TouchDown(float pX, float pY, void *pData) {
    
}

void CNVMiniWindow::TouchMove(float pX, float pY, void *pData) {
    
}

void CNVMiniWindow::TouchUp(float pX, float pY, void *pData) {
    
}

void CNVMiniWindow::TouchFlush() {
    
}



