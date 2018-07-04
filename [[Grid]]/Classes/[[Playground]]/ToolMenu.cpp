//
//  ToolMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenu.hpp"
//
//  ToolMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "ToolMenu.hpp"
#include "GLApp.h"

ToolMenu::ToolMenu() {
    mName = "ToolMenu";
    mClipEnabled = false;
    mClipDisabled = true;

    mMenuBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mMenuBackground.SetColorBottom(0.165f, 0.135f, 0.085f);
    mMenuBackground.mCornerRadius = 8.0f;

    mMenuBackgroundOutline.SetColorTop(0.925f, 0.925f, 0.925f);
    mMenuBackgroundOutline.SetColorBottom(0.965f, 0.965f, 0.965f);
    mMenuBackgroundOutline.mCornerRadius = 8.0f;

    mMenuBackgroundShadow.SetColorTop(0.021f, 0.021f, 0.021f, 0.25f);
    mMenuBackgroundShadow.SetColorBottom(0.025f, 0.025f, 0.025f, 0.25f);
    mMenuBackgroundShadow.mCornerRadius = 8.0f;


    AddChild(mContent);
    AddChild(mHeader);
}

ToolMenu::~ToolMenu() {
    
}

void ToolMenu::Layout() {

    float aHeaderHeight = 56.0f;


    mContent.SetFrame(2.0f, aHeaderHeight + 2.0f, mWidth - 4.0f, mHeight - (aHeaderHeight + 4.0f));
    //mContentScroller.SetContentSize(mContent.mWidth, mContent.mHeight);


    mHeader.SetFrame(1.0f, 1.0f, mWidth - 2.0f, aHeaderHeight);

    mMenuBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mMenuBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mMenuBackgroundShadow.SetRect(-2.0f, -2.0f, mWidth + 4.0f, mHeight + 4.0f);

    mMenuBackground.mRefresh = true;
    mMenuBackgroundOutline.mRefresh = true;
    mMenuBackgroundShadow.mRefresh = true;
}

void ToolMenu::Update() {
    
}

void ToolMenu::Draw() {
    mMenuBackgroundShadow.Draw();
    mMenuBackgroundOutline.Draw();
    mMenuBackground.Draw();
}

void ToolMenu::TouchDown(float pX, float pY, void *pData) {
    if (mParent) {
        mParent->BringChildToFront(this);
    }
}

void ToolMenu::TouchMove(float pX, float pY, void *pData) {

}

void ToolMenu::TouchUp(float pX, float pY, void *pData) {

}

void ToolMenu::TouchFlush() {

}

void ToolMenu::Notify(void *pSender, const char *pNotification) {
    Kill();
}








