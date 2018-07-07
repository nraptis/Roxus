//
//  ToolMenuSection.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuSection.hpp"
#include "GLApp.h"
#include "ToolMenu.hpp"

ToolMenuSection::ToolMenuSection() {
    mName = "ToolMenuSection";
    mConsumesTouches = false;

    mSectionDepth = 0;

    mSectionBackgroundOutline.mCornerRadius = 5.0f;
    mSectionBackground.mCornerRadius = 5.0f;

    mSectionBackground.SetColorTop(0.325f, 0.125f, 0.125f);
    mSectionBackground.SetColorBottom(0.365f, 0.135f, 0.085f);
    mSectionBackground.mCornerRadius = 5.0f;

    mSectionBackgroundOutline.SetColorTop(0.525f, 0.925f, 0.925f);
    mSectionBackgroundOutline.SetColorBottom(0.565f, 0.965f, 0.965f);
    mSectionBackgroundOutline.mCornerRadius = 5.0f;

    mMenu = 0;

    mLayoutBubbleUpDepth = 2;
}

ToolMenuSection::~ToolMenuSection() {

}

void ToolMenuSection::Layout() {
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
    if (mMenu) {
        mMenu->Notify(pSender, pNotification);
    }

}

void ToolMenuSection::SetTransparentBackground() {
    mSectionBackground.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackgroundOutline.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.mRefresh = true;
}
