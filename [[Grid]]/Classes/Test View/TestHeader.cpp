//
//  TestHeader.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TestHeader.hpp"
#include "GLApp.h"

TestHeader::TestHeader() {
    mSpriteRotation = gRand.Get(360);
    mClipsContent = true;

    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());

    mInsetLeft = 100.0f;
    mInsetRight = 40.0f;
    mInsetTop = 55.0f;

    mName = "TestHeader";
}

TestHeader::~TestHeader() {
    Log("Free(TestHeader)\n");
}

void TestHeader::PositionContent() {

    //Log("---PositionContent(TestHeader)\n");

    SetSize(1436.0f, gApp->mInterfaceBottomGray.mHeight + mInsetTop);

    if (mParent) {
        float aParentWidth = mParent->mWidth;
        float aParentHeight = mParent->mHeight;
        if (aParentWidth > 24.0f && aParentHeight > 24.0f && mWidth > 24.0f && mHeight > 24.0f) {
            FRect aBounds = FRect(0.0f, 0.0f, aParentWidth, aParentHeight);
            
            float aScale = 1.0f;
            //FRect aFit = FRect::FitAspectFit(aBounds, aWidth, aHeight, 12.0f, aScale);
            float aBorderSize = 12.0f;

            FRect aFit = FRect::FitAspectFit(aBounds, mWidth, mHeight, aBorderSize, aScale);
            
            SetTransformScaleX(aScale);
            SetTransformScaleY(aScale);

            SetTransformX(aBorderSize);
            SetTransformY(aBorderSize);

        }
    }

    //mInterfaceBottom.Load("game_interface_bottom_back_colored");
    //mInterfaceBottomGray.Load("game_interface_bottom_back_grey");

}

void TestHeader::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;

}

void TestHeader::Draw() {
    FView::Draw();

    FRect aLeftRect = FRect(0.0f, 0.0f, mInsetLeft, GetHeight());
    FRect aRightRect = FRect(GetWidth() - mInsetRight, 0.0f, mInsetRight, GetHeight());
    FRect aTopRect = FRect(mInsetLeft, 0.0f, GetWidth() - (mInsetRight + mInsetLeft), mInsetTop);

    gApp->mBackground.DrawQuadRect(0.0f, 0.0f, GetWidth(), GetHeight());




    float aImageWidth = gApp->mInterfaceBottomGray.mWidth;
    float aImageHeight = gApp->mInterfaceBottomGray.mHeight;

    float aImageWidth2 = aImageWidth / 2.0f;
    float aImageHeight2 = aImageHeight / 2.0f;

    Graphics::SetColor();
    gApp->mInterfaceBottomGray.Draw(mWidth2, mHeight - aImageHeight2, 1.0f, 180.0f, -1);


    Graphics::SetColor(1.0f, 0.66f, 0.85f, 0.75f);
    Graphics::BlendSetGhost1();



    gApp->mInterfaceBottomGray.Draw(mWidth2 - aImageWidth, mHeight - aImageHeight2, 1.0f, 180.0f, -1);
    gApp->mInterfaceBottomGray.Draw(mWidth2 + aImageWidth, mHeight - aImageHeight2, 1.0f, 180.0f, -1);





    Graphics::BlendSetAlpha();




    Graphics::SetColor(1.0f, 0.125f, 0.35f, 0.15f);
    Graphics::DrawRect(aLeftRect);

    Graphics::SetColor(0.66f, 0.74f, 0.15f, 0.15f);
    Graphics::DrawRect(aRightRect);

    Graphics::SetColor(0.066f, 1.0f, 0.35f, 0.15f);
    Graphics::DrawRect(aTopRect);

    Graphics::SetColor(0.76f, 0.125f, 0.056f, 0.85f);
    Graphics::OutlineRect(aLeftRect, 2.0f);

    Graphics::SetColor(0.76f, 0.125f, 0.76f, 0.85f);
    Graphics::OutlineRect(aRightRect, 2.0f);

    Graphics::SetColor(0.0f, 0.76f, 0.056f, 0.85f);
    Graphics::OutlineRect(aTopRect, 2.0f);





    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }
    
}

void TestHeader::TouchDown(float pX, float pY, void *pData) {
    
}

void TestHeader::TouchMove(float pX, float pY, void *pData) {
    
}

void TestHeader::TouchUp(float pX, float pY, void *pData) {
    
}

void TestHeader::TouchFlush() {
    
}



