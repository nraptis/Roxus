//
//  TestBadgeDecor3Decor3.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TestBadgeDecor3.hpp"
#include "GLApp.h"

TestBadgeDecor3::TestBadgeDecor3() {
    mClipsContent = true;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mName = "TestBadgeDecor3";
}

TestBadgeDecor3::~TestBadgeDecor3() {
    Log("Free(TestBadgeDecor3)\n");
}

void TestBadgeDecor3::PositionContent() {

    //Log("---PositionContent(~TestBadgeDecor3)\n");
    
    if (mParent) {
        float aParentWidth = mParent->GetWidth();
        float aParentHeight = mParent->GetHeight();
        if (aParentWidth > 10.0f && aParentHeight > 10.0f) {
            float aWidth = aParentWidth * 0.33f;
            float aHeight = aParentHeight * 0.33f;
            SetFrame(0.0f, aParentHeight - aHeight, aWidth, aHeight);

            SetTransformAnchor(0.5f, 0.5f);
            int aRand = gRand.Get(4);
            if (aRand == 0) {
                SetTransformRotation(0.0f);
            } else if (aRand == 0) {
                SetTransformRotation(90.0f);
            } else if (aRand == 0) {
                SetTransformRotation(180.0f);
            } else {
                SetTransformRotation(270.0f);
            }


        }
    }
}

void TestBadgeDecor3::Update() {
    
}

void TestBadgeDecor3::Draw() {
    FView::Draw();
    

    Graphics::SetColor();
    gApp->mTile3.DrawQuadRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }
}


