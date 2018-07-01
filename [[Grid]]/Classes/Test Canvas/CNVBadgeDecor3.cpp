//
//  CNVBadgeDecor3Decor3.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVBadgeDecor3.hpp"
#include "GLApp.h"

CNVBadgeDecor3::CNVBadgeDecor3() {
    mClipsContent = true;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mName = "CNVBadgeDecor3";
}

CNVBadgeDecor3::~CNVBadgeDecor3() {
    Log("Free(CNVBadgeDecor3)\n");
}

void CNVBadgeDecor3::Layout() {

    Log("---Layout(~CNVBadgeDecor3)\n");
    
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

void CNVBadgeDecor3::Update() {
    
}

void CNVBadgeDecor3::Draw() {
    FCanvas::Draw();
    

    Graphics::SetColor();
    gApp->mTile3.DrawQuadRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }
}


