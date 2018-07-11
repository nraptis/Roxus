//
//  CNVWorld.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVWorld.hpp"
#include "GLApp.h"

CNVWorld::CNVWorld() {
    
    mGame = 0;
    
    mLarge = false;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());

    SetTransformAnchor(0.66f, 0.66f);
    
    mGame = new CNVGame();
    AddChild(mGame);

    mName = "CNVWorld";
}

CNVWorld::~CNVWorld() {
    Log("Free(CNVWorld)\n");
}

void CNVWorld::Layout() {
    Log("---Layout(CNVWorld)\n");
    if (gVirtualDevWidth > 600.0f && gVirtualDevHeight > 600.0f) {
        mLarge = true;
        SetSize(gApp->mBackgroundLarge);
    } else {
        mLarge = false;
        SetSize(gApp->mBackground);
    }
}

void CNVWorld::Update() {
    
}

void CNVWorld::Draw() {
    FCanvas::Draw();

    
    Graphics::SetColor(1.0f, 0.22f, 0.22f, 0.44f);
    Graphics::DrawRect(-2.0f, -2.0f, mWidth + 4.0f, mHeight + 4.0f);
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.55f);

    Graphics::SetColor();
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
        Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 20.0f);
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 14.0f);
    }

    Graphics::SetColor(0.0f, 1.0f, 0.5f, 0.85f);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0],
                       mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1], 1.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1],
                       mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2], 1.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2],
                       mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3], 1.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3],
                       mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0], 1.0);
}

void CNVWorld::TouchDown(float pX, float pY, void *pData) {
    
}

void CNVWorld::TouchMove(float pX, float pY, void *pData) {
    
}

void CNVWorld::TouchUp(float pX, float pY, void *pData) {
    
}

void CNVWorld::TouchFlush() {
    
}


