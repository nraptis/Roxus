//
//  TestBoard.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TestBoard.hpp"
#include "GLApp.h"

TestBoard::TestBoard() {
    mSpriteRotation = gRand.Get(360);
    mClipsContent = true;
    
    mSphereRotation1 = gRand.Get(360);
    mSphereRotation2 = gRand.Get(360);
    
    mSpriteStartAngle = gRand.Get(360);
    mSpriteEndAngle = gRand.Get(360);
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mGridWidth = 9;
    mGridHeight = 12;
    
    
    //mRotView1UT = new TestMiniWindow();
    //mRotView1UT->mName = "mRotView1UT";
    //AddSubview(mRotView1UT);
    
    mRotView1 = new TestMiniWindow();
    mRotView1->mName = "ROTATION-VIEW-1";
    AddSubview(mRotView1);
    
    //mRotView2UT = new TestMiniWindow();
    //mRotView2UT->mName = "mRotView2UT";
    //AddSubview(mRotView2UT);
    
    mRotView2 = new TestMiniWindow();
    mRotView2->mName = "ROTATION-VIEW-2";
    AddSubview(mRotView2);
    
    mName = "TestBoard";


    mSnake.AddPoint(10.0f, 10.0f);


    

    //mParticleStream


    
}

TestBoard::~TestBoard() {
    Log("Free(TestBoard)\n");
}

void TestBoard::PositionContent() {
    //Log("---PositionContent(TestBoard)\n");
    
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
        mRotView1->SetTransformRotation(-35.0f);
        
        //mRotView1UT->SetFrame(100.0f, 256.0f, 200.0f, 256.0f);
        //mRotView1UT->mColor = FColor(1.0f * 0.8f, 0.6f * 0.8f, 0.25f * 0.8f, 0.66f);
    }
    
    if (mRotView2) {
        
        mRotView2->SetFrame((GetWidth() - 128) - 200, 256.0f, 128.0f, 256.0f);
        mRotView2->mColor = FColor(0.6f, 1.0f, 0.45f, 0.66f);
        mRotView2->SetTransformRotation(35.0f);
        
        //mRotView2UT->SetFrame((GetWidth() - 128) - 200, 256.0f, 128.0f, 256.0f);
        //mRotView2UT->mColor = FColor(0.6f * 0.8f, 1.0f * 0.8f, 0.45f * 0.8f, 0.66f);
    }
    
}

void TestBoard::Update() {
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

void TestBoard::Draw() {
    FView::Draw();
    //gApp->mTestSprite.Draw(mWidth2, mHeight2, 2.0, mSpriteRotation, 1);
    gApp->mTestSprite.Draw(mWidth2, mHeight2, 2.0, mSpriteRotation);
    gApp->mBackground.Center(mWidth2, mHeight2);
    
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
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 20.0f);
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 14.0f);
    }

    Graphics::SetColor(1.0, 0.0f, 0.125f, 0.85f);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[0],
                       mContainer->mTransformAbsolute.mCornerY[0],
                       mContainer->mTransformAbsolute.mCornerX[1],
                       mContainer->mTransformAbsolute.mCornerY[1], 12.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[1],
                       mContainer->mTransformAbsolute.mCornerY[1],
                       mContainer->mTransformAbsolute.mCornerX[2],
                       mContainer->mTransformAbsolute.mCornerY[2], 12.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[2],
                       mContainer->mTransformAbsolute.mCornerY[2],
                       mContainer->mTransformAbsolute.mCornerX[3],
                       mContainer->mTransformAbsolute.mCornerY[3], 12.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[3],
                       mContainer->mTransformAbsolute.mCornerY[3],
                       mContainer->mTransformAbsolute.mCornerX[0],
                       mContainer->mTransformAbsolute.mCornerY[0], 12.0);
    
}

void TestBoard::TouchDown(float pX, float pY, void *pData) {
    
}

void TestBoard::TouchMove(float pX, float pY, void *pData) {
    
}

void TestBoard::TouchUp(float pX, float pY, void *pData) {
    
}

void TestBoard::TouchFlush() {
    
}



