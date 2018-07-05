//
//  ToolMenuPanelPanelPanel.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuPanel.hpp"
#include "GLApp.h"

ToolMenuPanel::ToolMenuPanel() {
    mName = "ToolMenuPanel";
    mExpanded = true;
    AddChild(mContent);
    mHeader.mPanel = this;
    AddChild(mHeader);
}

ToolMenuPanel::~ToolMenuPanel() {

}

void ToolMenuPanel::Layout() {

    mHeader.SetSectionDepth(mSectionDepth);

    ToolMenuSection::Layout();
    float aHeaderHeight = 44.0f;
    float aContentWidth = mWidth - 4.0f;
    float aContentHeight = 6.0f;
    EnumList(ToolMenuSection, aSection, mSectionList) {
        aSection->SetFrame(3.0f, aContentHeight, aContentWidth - 6.0f, aSection->mHeight);
        aContentHeight += aSection->mHeight + 6.0f;
    }
    if (aContentHeight < 44.0f) { aContentHeight = 44.0f; }
    mContent.SetFrame(2.0f, aHeaderHeight + 2.0f, aContentWidth, aContentHeight);
    mHeader.SetFrame(1.0f, 1.0f, mWidth - 2.0f, aHeaderHeight);

    if (mExpanded) {
        SetHeight(aContentHeight + 46.0f);
    } else {
        SetHeight(46.0f);
    }
}

void ToolMenuPanel::Notify(void *pSender, const char *pNotification) {

}

void ToolMenuPanel::SetTitle(const char *pText) {
    mHeader.mLabelTitle.mText = pText;
}

void ToolMenuPanel::AddSection(ToolMenuSection *pSection) {
    mSectionList.Add(pSection);
    mContent.AddChild(pSection);
}


void ToolMenuPanel::Expand() {
    float aContentHeight = 0.0f;
    EnumList(ToolMenuSection, aSection, mSectionList) {
        aContentHeight += aSection->mHeight;
    }
    if (aContentHeight < 32.0f) { aContentHeight = 32.0f; }
    mExpanded = true;
    mContent.mEnabled = true;
    mContent.mHidden = false;
    mHeader.SetExpandedLayout();
    SetHeight(aContentHeight + 46.0f);
}

void ToolMenuPanel::Collapse() {
    mExpanded = false;
    mContent.mEnabled = false;
    mContent.mHidden = true;
    mHeader.SetCollapsedLayout();
    SetHeight(46.0f);
}








