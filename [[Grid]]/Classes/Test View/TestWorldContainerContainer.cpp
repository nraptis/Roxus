//
//  TestWorldContainerContainerContainer.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/17/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TestWorldContainerContainer.hpp"
#include "GLApp.h"
#include "TestWorld.hpp"

TestWorldContainerContainer::TestWorldContainerContainer() {
    mSpriteRotation = gRand.Get(360);
    
    mWorldContainer = 0;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mWorldContainer = new TestWorldContainer();
    AddSubview(mWorldContainer);
    
    mName = "TestWorldContainer+Container [OUTER]";
    
}

TestWorldContainerContainer::~TestWorldContainerContainer() {
    Log("Free(TestWorldContainerContainer)\n");
}

void TestWorldContainerContainer::PositionContent() {
    
    //Log("---PositionContent(TestWorldContainerContainer_\n");

    SetFrame(5.0f, 5.0f, gAppWidth - 10.0f, gAppHeight - 10.0f);
    
    if (mContainer) {

        float aWidth = 1536.0f;
        float aHeight = 1536.0f;

        if (mWorldContainer->mWorld1) {

            aWidth = mWorldContainer->mWorld1->GetWidth();
            aHeight = mWorldContainer->mWorld1->GetHeight();
        }

        if (aWidth > 10.0 && aHeight > 10.0 && mWidth > 10.0 && mHeight > 10.0) {
            
            FRect aBounds = FRect(0.0f, 0.0f, mWidth, mHeight);

            float aScale = 1.0f;
            FRect aFit = FRect::FitAspectFit(aBounds, aHeight, aWidth, 5.0f, aScale);

            mWorldContainer->SetTransformScale(aScale);
            mWorldContainer->SetTransformX(aFit.mX);
            mWorldContainer->SetTransformY(aFit.mY);

            if (gRand.GetBool()) {
                //mWorldContainer->SetTransformRotation(-14.0f);
            } else {
                //mWorldContainer->SetTransformRotation(0.0f);
            }
        }
    }
}

void TestWorldContainerContainer::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;
    
}

void TestWorldContainerContainer::Draw() {
    FView::Draw();
    
    
    float aWidth = gApp->mTessPattern.mWidth;
    float aHeight = gApp->mTessPattern.mHeight;

    Graphics::BlendSetAdditive();
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.25f);
    gApp->mSillyMeme.DrawQuadRect(0.0f, 0.0f, GetWidth(), GetHeight());

    Graphics::BlendSetAlpha();


    /*
    if(aWidth > 10.0f && aHeight > 10.0f) {
        for (float aX=0;aX<=mWidth;aX+=aWidth) {
            for (float aY=0;aY<=mHeight;aY+=aHeight) {
                gApp->mTessPattern.Draw(aX, aY);
            }
        }
    }
    */
    
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

    Graphics::SetColor(1.0f, 0.25f, 0.75f, 0.75f);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[0],
                       mContainer->mTransformAbsolute.mCornerY[0],
                       mContainer->mTransformAbsolute.mCornerX[1],
                       mContainer->mTransformAbsolute.mCornerY[1], 6.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[1],
                       mContainer->mTransformAbsolute.mCornerY[1],
                       mContainer->mTransformAbsolute.mCornerX[2],
                       mContainer->mTransformAbsolute.mCornerY[2], 6.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[2],
                       mContainer->mTransformAbsolute.mCornerY[2],
                       mContainer->mTransformAbsolute.mCornerX[3],
                       mContainer->mTransformAbsolute.mCornerY[3], 6.0);

    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[3],
                       mContainer->mTransformAbsolute.mCornerY[3],
                       mContainer->mTransformAbsolute.mCornerX[0],
                       mContainer->mTransformAbsolute.mCornerY[0], 6.0);

}

void TestWorldContainerContainer::TouchDown(float pX, float pY, void *pData) {
    
}

void TestWorldContainerContainer::TouchMove(float pX, float pY, void *pData) {
    
}

void TestWorldContainerContainer::TouchUp(float pX, float pY, void *pData) {
    
}

void TestWorldContainerContainer::TouchFlush() {
    
}


