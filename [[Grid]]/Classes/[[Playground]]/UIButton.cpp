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


    mText = "ABC";


    mConsumesTouches = true;

    mButtonBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mButtonBackground.SetColorBottom(0.165f, 0.165f, 0.165f);
    mButtonBackground.mCornerRadius = 4.0f;

    mButtonOutline.SetColorTop(0.465f, 0.465f, 0.465f);
    mButtonOutline.SetColorBottom(0.625f, 0.625f, 0.625f);
    mButtonOutline.mCornerRadius = 6.0f;
    
    mButtonBackgroundDown.SetColorTop(0.35f, 0.35f, 0.65f);
    mButtonBackgroundDown.SetColorBottom(0.38f, 0.38f, 0.68f);
    mButtonBackgroundDown.mCornerRadius = 4.0f;

    mButtonOutlineDown.SetColorTop(0.825f, 0.825f, 0.425f);
    mButtonOutlineDown.SetColorBottom(0.865f, 0.865f, 0.865f);
    mButtonOutlineDown.mCornerRadius = 6.0f;
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
    if (true) {
        float aGraphicInset = mWidth * 0.26f;

        Graphics::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        Graphics::DrawLine(aGraphicInset, aGraphicInset, mWidth - aGraphicInset, mHeight - aGraphicInset, aLineThickness);
        Graphics::DrawLine(aGraphicInset, mHeight - aGraphicInset, mWidth - aGraphicInset, aGraphicInset, aLineThickness);
    }



    if (mText.mLength > 0) {

        float aScale = gApp->mSysFontBold.ScaleForWidth(mText, mWidth, 6.0f);
        if (aScale > 1.0f) { aScale = 1.0f; }

        gApp->mSysFontBold.LeftCenter(mText, mWidth2, mHeight2, aScale);
        


        //gApp->mSysFontBold.Right(mText, 0.0f, mHeight2, aScale);



//        gApp->mSysFontBold.Draw(mText.c(), 0.0f, mHeight2, 1.0f);
//
//        gApp->mSysFontBold.Draw(mText.c(), 0.0f, mHeight2, 0.5f);
//        float aWidth = gApp->mSysFontBold.Width(mText.c());
//
//        Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.66f);
//        Graphics::DrawRect(0.0f, mHeight - 5.0f, aWidth, 3.0f);


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



