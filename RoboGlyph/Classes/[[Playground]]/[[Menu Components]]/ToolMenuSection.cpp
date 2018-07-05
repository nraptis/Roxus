//
//  ToolMenuSection.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuSection.hpp"
#include "GLApp.h"

ToolMenuSection::ToolMenuSection() {
    mName = "ToolMenuSection";

    mSectionDepth = 0;

    mSectionBackgroundOutline.mCornerRadius = 5.0f;
    mSectionBackground.mCornerRadius = 5.0f;

    mSectionBackground.SetColorTop(0.325f, 0.125f, 0.125f);
    mSectionBackground.SetColorBottom(0.365f, 0.135f, 0.085f);
    mSectionBackground.mCornerRadius = 5.0f;

    mSectionBackgroundOutline.SetColorTop(0.525f, 0.925f, 0.925f);
    mSectionBackgroundOutline.SetColorBottom(0.565f, 0.965f, 0.965f);
    mSectionBackgroundOutline.mCornerRadius = 5.0f;

    mLayoutBubbleUpDepth = 2;
}

ToolMenuSection::~ToolMenuSection() {

}

void ToolMenuSection::Layout() {
    if (mSectionDepth == 0) {
        mSectionBackground.ResetColor(0.28f, 0.28f, 0.28f);
        mSectionBackgroundOutline.ResetColor(0.36f, 0.36f, 0.36f);
    }
    if (mSectionDepth == 1) {
        mSectionBackground.ResetColor(0.34f, 0.35f, 0.36f);
        mSectionBackgroundOutline.ResetColor(0.386f, 0.40f, 0.40f);
    }
    if (mSectionDepth == 2) {
        mSectionBackground.ResetColor(0.15f, 0.14f, 0.15f);
        mSectionBackgroundOutline.ResetColor(0.24f, 0.26f, 0.24f);
    }
    if (mSectionDepth == 3) {
        mSectionBackground.ResetColor(0.24f, 0.24f, 0.24f);
        mSectionBackgroundOutline.ResetColor(0.28f, 0.28f, 0.28f);
    }

    mSectionBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mSectionBackgroundOutline.mRefresh = true;
}

void ToolMenuSection::Update() {

}

void ToolMenuSection::Draw() {
    mSectionBackgroundOutline.Draw();
    mSectionBackground.Draw();
}

void ToolMenuSection::Notify(void *pSender, const char *pNotification) {

}

void ToolMenuSection::SetTransparentBackground() {
    mSectionBackground.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackgroundOutline.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.mRefresh = true;
}
