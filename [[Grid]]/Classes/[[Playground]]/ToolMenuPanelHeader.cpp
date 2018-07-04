//
//  ToolMenuPanelHeader.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuPanelHeader.hpp"
#include "ToolMenu.hpp"
#include "PGMainCanvas.hpp"
#include "ToolMenuPanel.hpp"

ToolMenuPanelHeader::ToolMenuPanelHeader() {
    mPanel = 0;
    mName = "ToolMenuPanelHeader";
    mConsumesTouches = false;
    mLabelTitle.mAlignment = 0;
    mLabelTitle.mBold = true;
    mLabelTitle.mShrink = true;
    mLabelTitle.mScale = 1.0f;
    mLabelTitle.SetTransparentBackground();
    AddChild(mLabelTitle);
    mMenuBackground.SetColorTop(0.325f, 0.325f, 0.665f);
    mMenuBackground.SetColorBottom(0.365f, 0.365f, 0.665f);
    mMenuBackground.mCornerRadius = 4.0f;
    mMenuBackground.mRoundBottom = false;

    mButtonClose.SetTransparentBackground();
    mButtonClose.mName = "Close Button";
    mButtonClose.mDrawCloseX = true;
    AddChild(mButtonClose);

    mButtonMinimize.SetTransparentBackground();
    mButtonMinimize.mName = "Minimize Button";
    mButtonMinimize.mDrawMinimize = true;
    AddChild(mButtonMinimize);

    gNotify.Register(this, &mButtonClose, "click");
    gNotify.Register(this, &mButtonMinimize, "click");
}

ToolMenuPanelHeader::~ToolMenuPanelHeader() {

}

void ToolMenuPanelHeader::Layout() {
    float aButtonPadding = 4.0f;
    float aButtonSize = mHeight - aButtonPadding * 2.0f;
    mButtonClose.SetFrame(aButtonPadding, aButtonPadding, aButtonSize, aButtonSize);
    mButtonMinimize.SetFrame(mWidth - (aButtonPadding + aButtonSize), aButtonPadding, aButtonSize, aButtonSize);
    float aLabelLeft = mButtonClose.GetRight() + 2.0f;
    float aLabelRight = mButtonMinimize.GetLeft() - 2.0f;
    mLabelTitle.SetFrame(aLabelLeft, 2.0f, aLabelRight - aLabelLeft, mHeight - 4.0f);
    mMenuBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mMenuBackground.mRefresh = true;
}

void ToolMenuPanelHeader::Update() {

}

void ToolMenuPanelHeader::Draw() {
    FCanvas::Draw();
    mMenuBackground.Draw();
}

void ToolMenuPanelHeader::Notify(void *pSender, const char *pNotification) {
    printf("Header Notify: [%s][%s]\n", ((FCanvas *)pSender)->mName.c(), pNotification);
    if (FString(pNotification) == "click") {
        if (pSender == &mButtonClose) {

        }
        if (pSender == &mButtonMinimize) {
            if (mPanel) {
                if (mPanel->mExpanded) {
                    mPanel->Collapse();
                } else {
                    mPanel->Expand();
                }
            }
        }
    }
}

void ToolMenuPanelHeader::SetExpandedLayout() {
    mButtonMinimize.mDrawMaximize = false;
    mButtonMinimize.mDrawMinimize = true;
}

void ToolMenuPanelHeader::SetCollapsedLayout() {
    mButtonMinimize.mDrawMaximize = true;
    mButtonMinimize.mDrawMinimize = false;
}



