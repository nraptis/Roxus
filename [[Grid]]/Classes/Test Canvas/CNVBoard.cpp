//
//  CNVBoard.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVBoard.hpp"
#include "GLApp.h"

CNVBoard::CNVBoard() {

    int aRand = gRand.Get(3);

    SetTransformAnchor(0.0f, 0.0f);
    
    if (aRand == 0) {
        //SetTransformAnchor(0.0f, 0.0f);
        //printf("CNVBoard::SetTransformAnchor(0.0f, 0.0f);\n");
    } else if (aRand == 1) {
        //SetTransformAnchor(0.5f, 0.5f);
        //printf("CNVBoard::SetTransformAnchor(0.5f, 0.5f);\n");
    } else {
        //SetTransformAnchor(1.0f, 1.0f);
        //printf("CNVBoard::SetTransformAnchor(1.0f, 1.0f);\n");
    }

    mSpriteRotation = gRand.Get(360);
    mClipEnabled = true;
    
    mSphereRotation1 = gRand.Get(360);
    mSphereRotation2 = gRand.Get(360);
    
    mTestAngle = gRand.Get(360);
    mSpriteEndAngle = gRand.Get(360);
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mGridWidth = 9;
    mGridHeight = 12;
    
    
    //mRotView1UT = new CNVMiniWindow();
    //mRotView1UT->mName = "mRotView1UT";
    //AddChild(mRotView1UT);
    
    mRotView1 = new CNVMiniWindow();
    mRotView1->mName = "ROTATION-VIEW-1";
    AddChild(mRotView1);
    mRotView1->SetTransformAnchor(0.0f, 0.0f);

    //mRotView2UT = new CNVMiniWindow();
    //mRotView2UT->mName = "mRotView2UT";
    //AddChild(mRotView2UT);
    
    mRotView2 = new CNVMiniWindow();
    mRotView2->mName = "ROTATION-VIEW-2";
    AddChild(mRotView2);
    mRotView2->SetTransformAnchor(0.0f, 0.0f);
    
    
    mName = "CNVBoard";


    mSnake.AddPoint(10.0f, 10.0f);


    

    //mParticleStream


    
}

CNVBoard::~CNVBoard() {
    Log("Free(CNVBoard)\n");
}

void CNVBoard::Layout() {

    Log("---Layout(CNVBoard) (%f %f %f %f)\n", mX, mY, mWidth, mHeight);
    float aTileWidth = gApp->mDarkTile.mWidth;
    float aTileHeight = gApp->mDarkTile.mHeight;
    if (aTileWidth > 20.0f && aTileHeight > 20.0f) {
        float aWidth = ((float)mGridWidth) * aTileWidth;
        float aHeight = ((float)mGridHeight) * aTileHeight;
        SetSize(aWidth, aHeight);
    }
    if (mRotView1) {
        mRotView1->SetFrame(100.0f, 256.0f, 200.0f, 256.0f);
        mRotView1->mColor = FColor(1.0f, 0.6f, 0.25f, 0.66f);
        mRotView1->SetTransformRotation(-44.0f);
    }
    if (mRotView2) {
        mRotView2->SetFrame((GetWidth() - 128) - 200, 256.0f, 128.0f, 256.0f);
        mRotView2->mColor = FColor(0.6f, 1.0f, 0.45f, 0.66f);
        mRotView2->SetTransformRotation(53.0f);
    }
}

void CNVBoard::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;

    float aSin = Sin(mTestAngle);
    
    SetTransformRotation(aSin * 5.0f);
    if (gRand.GetBool()) {

    } else {
        //SetTransformRotation(0.0f);
    }

    
    mSphereRotation1 += 0.25f;
    if (mSphereRotation1 >= 360.0f) mSphereRotation1 -= 360.0f;
    
    mSphereRotation2 += 3.0f;
    if (mSphereRotation2 >= 360.0f) mSphereRotation2 -= 360.0f;
    
    mTestAngle -= 0.5f;
    if (mTestAngle < -180.0f) { mTestAngle += 360.0f; }
    
    mSpriteEndAngle += 2.0f;
    if (mSpriteEndAngle > 360.0f) { mSpriteEndAngle -= 1080.0f;}
}

void CNVBoard::Draw() {
    FCanvas::Draw();
    //gApp->mCNVSprite.Draw(mWidth2, mHeight2, 2.0, mSpriteRotation, 1);
    gApp->mTestSprite.Draw(mWidth2, mHeight2, 2.0, mSpriteRotation);
    gApp->mBackgroundLarge.Center(mWidth2, mHeight2);


    Graphics::SetColor(0.66f, 0.66f, 0.66f, 0.75f);
    
    Graphics::OutlineRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f, 3.0f);
    
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.75f);
    Graphics::OutlineRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 2.0f);
    
    float aTileWidth = gApp->mDarkTile.mWidth;
    float aTileHeight = gApp->mDarkTile.mHeight;
    
    for (int i=0;i<mGridWidth;i++) {
        for (int n=0;n<mGridHeight;n++) {
            gApp->mDarkTile.Draw(aTileWidth * ((float)i), aTileHeight * ((float)n));
        }
    }
    
    gApp->mWallLeft.Draw(0.0f, 0.0f);
    gApp->mWallRight.Draw(mWidth - gApp->mWallRight.mWidth, 0.0f);
    
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

    Graphics::SetColor(1.0, 0.0f, 0.125f, 0.85f);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0],
                       mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1], 12.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1],
                       mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2], 12.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2],
                       mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3], 12.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3],
                       mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0], 12.0);
    
}

void CNVBoard::TouchDown(float pX, float pY, void *pData) {
    
}

void CNVBoard::TouchMove(float pX, float pY, void *pData) {
    
}

void CNVBoard::TouchUp(float pX, float pY, void *pData) {
    
}

void CNVBoard::TouchFlush() {
    
}



