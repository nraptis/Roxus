//
//  UIButton.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIButton.hpp"
#include "GLApp.h"
#include "PGMainCanvas.hpp"

UIButton::UIButton() {
    mName = "UIButton";
    
    mConsumesTouches = true;
    
    mDrawCloseX = false;
    mDrawMinimize = false;
    mDrawMaximize = false;
    
    mButtonBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mButtonBackground.SetColorBottom(0.165f, 0.165f, 0.165f);
    mButtonBackground.mCornerRadius = 4.0f;

    mButtonOutline.SetColorTop(0.265f, 0.265f, 0.265f);
    mButtonOutline.SetColorBottom(0.225f, 0.225f, 0.225f);
    mButtonOutline.mCornerRadius = 4.0f;
    
    mButtonBackgroundDown.SetColorTop(0.165f, 0.165f, 0.165f);
    mButtonBackgroundDown.SetColorBottom(0.1825f, 0.1825f, 0.1825f);
    mButtonBackgroundDown.mCornerRadius = 4.0f;

    mButtonOutlineDown.SetColorTop(0.855f, 0.825f, 0.125f);
    mButtonOutlineDown.SetColorBottom(0.865f, 0.865f, 0.125f);
    mButtonOutlineDown.mCornerRadius = 4.0f;
}

UIButton::~UIButton() {
    
}

void UIButton::Layout() {
    mButtonBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mButtonBackgroundDown.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);

    mButtonOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mButtonOutlineDown.SetRect(0.0f, 0.0f, mWidth, mHeight);


    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;

}

void UIButton::Update() {

}

void UIButton::Draw() {

    if (mTouchDown) {
        mButtonOutlineDown.Draw();
        mButtonBackgroundDown.Draw();
    } else {
        mButtonOutline.Draw();
        mButtonBackground.Draw();
    }

    
    float aLineThickness = (int)(mHeight * 0.06f) + 1;
    if (mTouchDown) { Graphics::SetColor(0.88f, 0.88f, 0.88f); }
    else { Graphics::SetColor(1.0f, 1.0f, 1.0f); }

    
    if (mDrawCloseX) {
        float aGraphicInset = mWidth * 0.26f;
        Graphics::DrawLine(aGraphicInset, aGraphicInset, mWidth - aGraphicInset, mHeight - aGraphicInset, aLineThickness);
        Graphics::DrawLine(aGraphicInset, mHeight - aGraphicInset, mWidth - aGraphicInset, aGraphicInset, aLineThickness);
    }
    if (mDrawMinimize) {
        float aGraphicInset = mWidth * 0.26f;
        Graphics::DrawLine(aGraphicInset, mHeight2, mWidth - aGraphicInset, mHeight2, aLineThickness);
    }

    if (mDrawMaximize) {

        float aGraphicInset = mWidth * 0.26f;

        Graphics::OutlineRect(aGraphicInset, aGraphicInset, mWidth - (aGraphicInset * 2.0f), mHeight - (aGraphicInset * 2.0f), aLineThickness);
    }

    if (mText.mLength > 0) {
        Graphics::BlendSetPremultiplied();
        Graphics::BlendEnable();
        if (mTouchDown) { Graphics::SetColor(0.88f, 0.88f, 0.88f); }
        else { Graphics::SetColor(1.0f, 1.0f, 1.0f); }
        float aScale = gApp->mSysFont.ScaleForWidth(mText, mWidth, 6.0f);
        if (aScale > 1.0f) { aScale = 1.0f; }
        gApp->mSysFont.Center(mText, mWidth2, mHeight2, aScale);
        Graphics::BlendSetAlpha();
    }
}


void UIButton::TouchDown(float pX, float pY, void *pData) {
    FButton::TouchDown(pX, pY, pData);
}

void UIButton::TouchMove(float pX, float pY, void *pData) {
    FButton::TouchMove(pX, pY, pData);
}

void UIButton::TouchUp(float pX, float pY, void *pData) {
    FButton::TouchUp(pX, pY, pData);
}

void UIButton::TouchFlush() {
    FButton::TouchFlush();
}

void UIButton::SetTransparentBackground() {
    mButtonBackground.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mButtonOutline.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mButtonBackgroundDown.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mButtonOutlineDown.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);

    mButtonBackground.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}


