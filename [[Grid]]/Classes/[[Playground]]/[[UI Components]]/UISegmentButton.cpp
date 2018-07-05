//
//  UISegmentButton.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UISegmentButton.hpp"
#include "GLApp.h"
#include "PGMainCanvas.hpp"

UISegmentButton::UISegmentButton() {
    mName = "UISegmentButton";

    mSelected = false;
    SetSelected(mSelected);
}

UISegmentButton::~UISegmentButton() {

}

void UISegmentButton::Layout() {
    mButtonBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mButtonBackgroundDown.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);

    mButtonOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mButtonOutlineDown.SetRect(0.0f, 0.0f, mWidth, mHeight);

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

void UISegmentButton::StyleSetLeft() {
    mButtonBackground.mRoundLeft = true;
    mButtonBackground.mRoundRight = false;

    mButtonBackgroundDown.mRoundLeft = true;
    mButtonBackgroundDown.mRoundRight = false;

    mButtonOutline.mRoundLeft = true;
    mButtonOutline.mRoundRight = false;

    mButtonOutlineDown.mRoundLeft = true;
    mButtonOutlineDown.mRoundRight = false;

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

void UISegmentButton::StyleSetMiddle() {
    mButtonBackground.mRoundLeft = false;
    mButtonBackground.mRoundRight = false;

    mButtonBackgroundDown.mRoundLeft = false;
    mButtonBackgroundDown.mRoundRight = false;

    mButtonOutline.mRoundLeft = false;
    mButtonOutline.mRoundRight = false;

    mButtonOutlineDown.mRoundLeft = false;
    mButtonOutlineDown.mRoundRight = false;

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

void UISegmentButton::StyleSetRight() {
    mButtonBackground.mRoundLeft = false;
    mButtonBackground.mRoundRight = true;

    mButtonBackgroundDown.mRoundLeft = false;
    mButtonBackgroundDown.mRoundRight = true;

    mButtonOutline.mRoundLeft = false;
    mButtonOutline.mRoundRight = true;

    mButtonOutlineDown.mRoundLeft = false;
    mButtonOutlineDown.mRoundRight = true;

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

void UISegmentButton::SetSelected(bool pState) {
    mSelected = pState;

    if (mSelected) {

        mButtonBackground.SetColorTop(0.05f, 0.05f, 0.35f);
        mButtonBackground.SetColorBottom(0.07f, 0.07f, 0.37f);
        mButtonOutline.SetColorTop(0.78f, 0.78f, 0.78f);
        mButtonOutline.SetColorBottom(0.75f, 0.75f, 0.75f);

        //mButtonBackgroundDown.SetColorTop(0.165f, 0.165f, 0.165f);
        //mButtonBackgroundDown.SetColorBottom(0.1825f, 0.1825f, 0.1825f);
        //mButtonOutlineDown.SetColorTop(0.855f, 0.825f, 0.125f);
        //mButtonOutlineDown.SetColorBottom(0.865f, 0.865f, 0.125f);

        
    } else {
        mButtonBackground.SetColorTop(0.167f, 0.167f, 0.167f);
        mButtonBackground.SetColorBottom(0.175f, 0.175f, 0.175f);
        mButtonOutline.SetColorTop(0.375, 0.375, 0.373);
        mButtonOutline.SetColorBottom(0.366f, 0.366f, 0.366f);
    }
}

