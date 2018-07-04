//
//  CNVFooter.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/22/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVFooter.hpp"
#include "GLApp.h"

CNVFooter::CNVFooter() {

    mBadgeLeft = 0;
    mBadgeRight = 0;

    mInsetLeft = 66.0f;
    mInsetRight = 100.0f;
    mInsetBottom = 40.0f;

    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());

    mBadgeLeft = new CNVBadge();
    AddChild(mBadgeLeft);

    mBadgeRight = new CNVBadge();
    AddChild(mBadgeRight);

    mName = "CNVFooter";
}

CNVFooter::~CNVFooter() {
    Log("Free(CNVFooter)\n");
}

void CNVFooter::Layout() {

    Log("---Layout(CNVFooter)\n");

    SetSize(gApp->mInterfaceBottom.mWidth, gApp->mInterfaceBottom.mHeight + mInsetBottom);

    if (mParent) {
        float aParentWidth = mParent->mWidth;
        float aParentHeight = mParent->mHeight;
        if (aParentWidth > 24.0f && aParentHeight > 24.0f && mWidth > 24.0f && mHeight > 24.0f) {
            FRect aBounds = FRect(0.0f, 0.0f, aParentWidth, aParentHeight);

            float aScale = 1.0f;
            //FRect aFit = FRect::FitAspectFit(aBounds, aWidth, aHeight, 12.0f, aScale);
            float aBorderSize = 8.0f;
            FRect aFit = FRect::FitAspectFit(aBounds, mWidth, mHeight, aBorderSize, aScale);

            SetTransformScale(aScale);
            SetX(aFit.mX);
            SetY(aParentHeight - (mHeight * aScale + aBorderSize));
        }
    }

    if (mBadgeLeft) {

        float aBadgeWidth = mBadgeLeft->mWidth;
        float aBadgeHeight = mBadgeLeft->mHeight;
        float aBadgeScale = 1.0f;

        FRect aBadgeContainer = FRect(mInsetLeft, 0.0f, (GetWidth() - (mInsetLeft + mInsetRight)) / 2.0f, GetHeight() - mInsetBottom);

        FRect aFit = FRect::FitAspectFit(aBadgeContainer, aBadgeWidth, aBadgeHeight, 2.0f, aBadgeScale);

        mBadgeLeft->SetTransformScaleX(aBadgeScale);
        mBadgeLeft->SetTransformScaleY(aBadgeScale);
        mBadgeLeft->SetTransformTranslate(mInsetLeft, 2.0f);
    }

    if (mBadgeRight) {
        float aBadgeWidth = mBadgeRight->mWidth;
        float aBadgeHeight = mBadgeRight->mHeight;
        float aBadgeScale = 1.0f;
        FRect aBadgeContainer = FRect(mInsetLeft, 0.0f, (GetWidth() - (mInsetLeft + mInsetRight)) / 2.0f, GetHeight() - mInsetBottom);
        FRect aFit = FRect::FitAspectFit(aBadgeContainer, aBadgeWidth, aBadgeHeight, 2.0f, aBadgeScale);
        mBadgeRight->SetTransformScaleX(aBadgeScale);
        mBadgeRight->SetTransformScaleY(aBadgeScale);
        mBadgeRight->SetTransformTranslate(GetWidth() - (mInsetRight + mBadgeRight->GetWidth() * mBadgeRight->GetTransformScaleX()), 2.0f);
    }
}

void CNVFooter::Update() {

}

void CNVFooter::Draw() {
    FCanvas::Draw();
    //gApp->mCNVSprite.Draw(mWidth2, mHeight2, 2.0, mSpriteRotation, 1);

    Graphics::SetColor(0.66f, 0.66f, 0.66f, 0.75f);

    Graphics::OutlineRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f, 3.0f);

    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.75f);
    Graphics::OutlineRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 2.0f);

    Graphics::SetColor();

    gApp->mInterfaceBottom.Draw(0.0f, 0.0f);





    FRect aLeftRect = FRect(0.0f, 0.0f, mInsetLeft, GetHeight());
    FRect aRightRect = FRect(GetWidth() - mInsetRight, 0.0f, mInsetRight, GetHeight());
    FRect aBottomRect = FRect(mInsetLeft, GetHeight() - mInsetBottom, GetWidth() - (mInsetRight + mInsetLeft), mInsetBottom);

    Graphics::SetColor(1.0f, 0.125f, 0.35f, 0.15f);
    Graphics::DrawRect(aLeftRect);

    Graphics::SetColor(0.66f, 0.74f, 0.15f, 0.15f);
    Graphics::DrawRect(aRightRect);

    Graphics::SetColor(0.066f, 1.0f, 0.35f, 0.15f);
    Graphics::DrawRect(aBottomRect);

    Graphics::SetColor(0.76f, 0.125f, 0.056f, 0.85f);
    Graphics::OutlineRect(aLeftRect, 2.0f);

    Graphics::SetColor(0.76f, 0.125f, 0.76f, 0.85f);
    Graphics::OutlineRect(aRightRect, 2.0f);

    Graphics::SetColor(0.0f, 0.76f, 0.056f, 0.85f);
    Graphics::OutlineRect(aBottomRect, 2.0f);
    
    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }

    Graphics::SetColor();

}

void CNVFooter::TouchDown(float pX, float pY, void *pData) {

}

void CNVFooter::TouchMove(float pX, float pY, void *pData) {

}

void CNVFooter::TouchUp(float pX, float pY, void *pData) {

}

void CNVFooter::TouchFlush() {

}



