//
//  ToolMenuSectionRow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuSectionRow.hpp"
#include "GLApp.h"

ToolMenuSectionRow::ToolMenuSectionRow() {
    mName = "ToolMenuSectionRow";

    mSectionBackground.SetColorTop(0.325f, 0.125f, 0.125f);
    mSectionBackground.SetColorBottom(0.365f, 0.135f, 0.085f);
    mSectionBackground.mCornerRadius = 4.0f;

    mSectionBackgroundOutline.SetColorTop(0.525f, 0.925f, 0.925f);
    mSectionBackgroundOutline.SetColorBottom(0.565f, 0.965f, 0.965f);
    mSectionBackgroundOutline.mCornerRadius = 5.0f;
}

ToolMenuSectionRow::~ToolMenuSectionRow() {

}

void ToolMenuSectionRow::Layout() {

    //float aHeaderHeight = 56.0f;
    //mHeader.SetFrame(1.0f, 1.0f, mWidth - 2.0f, aHeaderHeight);

    mSectionBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mSectionBackground.mRefresh = true;

    mSectionBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mSectionBackgroundOutline.mRefresh = true;
}

void ToolMenuSectionRow::Update() {

}

void ToolMenuSectionRow::Draw() {
    mSectionBackgroundOutline.Draw();
    mSectionBackground.Draw();
}

void ToolMenuSectionRow::Notify(void *pSender, const char *pNotification) {

}
