//
//  PGMainToolbar.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGMainToolbar.hpp"
#include "GLApp.h"


PGMainToolbar::PGMainToolbar() {
    mName = "PGMainToolbar";
    mClipEnabled = false;
    mClipDisabled = true;
    mExpanded = true;
    mExpandedWidth = 0.0f;

    mContent.mConsumesTouches = false;

    mToolbarBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mToolbarBackground.SetColorBottom(0.165f, 0.135f, 0.085f);
    mToolbarBackground.mCornerRadius = 8.0f;

    mToolbarBackgroundOutline.SetColorTop(0.925f, 0.925f, 0.925f);
    mToolbarBackgroundOutline.SetColorBottom(0.965f, 0.965f, 0.965f);
    mToolbarBackgroundOutline.mCornerRadius = 8.0f;

    mToolbarBackgroundShadow.SetColorTop(0.021f, 0.021f, 0.021f, 0.25f);
    mToolbarBackgroundShadow.SetColorBottom(0.025f, 0.025f, 0.025f, 0.25f);
    mToolbarBackgroundShadow.mCornerRadius = 8.0f;

    AddChild(mContent);

    AddRow(&mMainRow);
    AddRow(&mRow1);
    AddRow(&mRow2);

    float aRowHeight = ToolMenuSectionRow::RowHeight();
    mButtonMinimize.SetFrame(2.0f, 2.0f, aRowHeight * 1.5f - 4.0f, aRowHeight - 4.0f);
    mButtonMinimize.mDrawMaximize = true;
    AddChild(mButtonMinimize);

    gNotify.Register(this, &mButtonMinimize, "button_click");

    mSizeMinWidth = 500.0f;
    mSizeMinHeight = aRowHeight + 4.0f;

    SetWidth(mSizeMinWidth + 200.0f);
}

PGMainToolbar::~PGMainToolbar() {

}

void PGMainToolbar::Layout() {

    float aContentWidth = mWidth - 4.0f;
    float aContentHeight = 0.0f;
    int aRowIndex = 0;
    float aInset = 2.0f;
    float aRowHeight = ToolMenuSectionRow::RowHeight();
    EnumList(ToolMenuSectionRow, aRow, mRowList) {
        if (aRowIndex == 0) {
            float aTopContentWidth = aContentWidth - (mButtonMinimize.GetRight() + aInset * 2.0f);
            aRow->SetFrame(mButtonMinimize.GetRight() + aInset, aInset, aTopContentWidth, aRowHeight);
        } else {
            aRow->SetFrame(aInset, aContentHeight + aInset, aContentWidth - (aInset * 2.0f), aRowHeight);
        }
        aContentHeight += aRow->mHeight + 2.0f;
        aRowIndex++;
    }
    mContent.SetFrame(2.0f, 2.0f, aContentWidth, mHeight - 4.0f);
    mToolbarBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mToolbarBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mToolbarBackgroundShadow.SetRect(-2.0f, -2.0f, mWidth + 4.0f, mHeight + 4.0f);
    mToolbarBackground.mRefresh = true;
    mToolbarBackgroundOutline.mRefresh = true;
    mToolbarBackgroundShadow.mRefresh = true;

    if (mExpanded) {
        SetHeight(aContentHeight + 4.0f);
    } else {

        SetHeight(aRowHeight + 4.0f);
    }
}

void PGMainToolbar::Update() {

}

void PGMainToolbar::Draw() {
    mToolbarBackgroundShadow.Draw();
    mToolbarBackgroundOutline.Draw();
    mToolbarBackground.Draw();
}

void PGMainToolbar::TouchDown(float pX, float pY, void *pData) {
    if (mParent) {
        mParent->BringChildToFront(this);
    }
}

void PGMainToolbar::TouchMove(float pX, float pY, void *pData) {

}

void PGMainToolbar::TouchUp(float pX, float pY, void *pData) {

}

void PGMainToolbar::TouchFlush() {

}

void PGMainToolbar::Notify(void *pSender, const char *pNotification) {

    if (FString(pNotification) == "button_click") {
        if (pSender == &mButtonMinimize) {
                if (mExpanded) {
                    Collapse();
                } else {
                    Expand();
                }
        }
    }
}

void PGMainToolbar::AddRow(ToolMenuSectionRow *pRow) {
    mRowList.Add(pRow);
    mContent.AddChild(pRow);
}

void PGMainToolbar::Expand() {
    mExpanded = true;
    mResizeDragAllowed = true;
    float aContentHeight = 0.0f;
    EnumList(ToolMenuSectionRow, aRow, mRowList) {
        aContentHeight += aRow->mHeight + 2.0f;
    }
    mContent.mEnabled = true;
    mContent.mHidden = false;
    SetExpandedLayout();
    SetHeight(aContentHeight + 4.0f);
    SetWidth(mExpandedWidth);
}

void PGMainToolbar::Collapse() {
    mExpandedWidth = mWidth;
    mExpanded = false;
    mResizeDragAllowed = false;
    mContent.mEnabled = false;
    mContent.mHidden = true;
    float aRowHeight = ToolMenuSectionRow::RowHeight();
    SetHeight(aRowHeight + 4.0f);
    SetWidth(200.0f);
    SetCollapsedLayout();
}

void PGMainToolbar::SetExpandedLayout() {
    mButtonMinimize.mDrawMaximize = false;
    mButtonMinimize.mDrawMinimize = true;
}

void PGMainToolbar::SetCollapsedLayout() {
    mButtonMinimize.mDrawMaximize = true;
    mButtonMinimize.mDrawMinimize = false;
}






