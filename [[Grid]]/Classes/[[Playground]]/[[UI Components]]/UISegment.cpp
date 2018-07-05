//
//  UISegment.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UISegment.hpp"

USegment::USegment(int pSegmentCount) {
    mTarget = 0;
    mSelectedIndex = -1;

    mSegmentCount = 0;
    SetSegmentCount(pSegmentCount);
}

USegment::~USegment() {
    delete [] mButton;
    mButton = 0;
}

void USegment::Layout() {
    ToolMenuSectionRow::Layout();

    float aTotalWidth = mWidth;
    float aX = 0.0f;
    float aItemWidth = aTotalWidth;

    if (mSegmentCount == 1) {

    } else {
        aItemWidth /= ((float)mSegmentCount);
    }
    for (int i=0;i<mSegmentCount;i++) {
        UISegmentButton *aButton = mButton[i];
        aButton->SetFrame(aX, 0.0f, aItemWidth, mHeight);
        aX += (aItemWidth);
    }
}

void USegment::SetSegmentCount(int pSegmentCount) {
    for (int i=0;i<mSegmentCount;i++) {
        mButton[i]->Kill();
        mButton[i] = 0;
    }
    delete [] mButton;
    mButton = 0;
    if (pSegmentCount <= 0) {
        mSegmentCount = 0;
        return;
    }
    mSegmentCount = pSegmentCount;
    mButton = new UISegmentButton*[mSegmentCount];
    for (int i=0;i<mSegmentCount;i++) {
        UISegmentButton *aButton = new UISegmentButton();
        mButton[i] = aButton;
        AddChild(aButton);
        if (i == 0) {
            if (pSegmentCount <= 1) {
                aButton->StyleSetMiddle();
            } else {
                aButton->StyleSetLeft();
            }
            aButton->SetSelected(true);
        } else if (i == (pSegmentCount - 1)) {
            aButton->StyleSetMiddle();
        } else {
            aButton->StyleSetRight();
        }
        gNotify.Register(this, aButton, "button_click");
    }
}

void USegment::SetTitle(int pSegment, const char *pText) {
    if ((pSegment >= 0) && (pSegment < mSegmentCount)) {
        mButton[pSegment]->SetText(pText);
    }
}

void USegment::SetTitles(const char *pTitle1, const char *pTitle2, const char *pTitle3, const char *pTitle4, const char *pTitle5, const char *pTitle6) {
    SetTitle(0, pTitle1);
    SetTitle(1, pTitle2);
    SetTitle(2, pTitle3);
    SetTitle(3, pTitle4);
    SetTitle(4, pTitle5);
    SetTitle(5, pTitle6);
}

void USegment::SetTarget(int *pTarget) {
    mTarget = pTarget;
    if (mTarget) {
        int aIndex = (*pTarget);
        if((aIndex >= 0) && (aIndex < mSegmentCount)) {
            mSelectedIndex = aIndex;
            for(int i=0;i<mSegmentCount;i++)mButton[i]->SetSelected(false);
            mButton[mSelectedIndex]->SetSelected(true);
        }
    }
}

void USegment::Notify(void *pSender, const char *pNotification) {

    if (FString("button_click") == pNotification) {

    for (int aCheckIndex=0;aCheckIndex<mSegmentCount;aCheckIndex++) {
        if (pSender == mButton[aCheckIndex]) {
            mSelectedIndex = aCheckIndex;

            for(int i=0;i<mSegmentCount;i++)mButton[i]->SetSelected(false);
            mButton[mSelectedIndex]->SetSelected(true);
            if (mTarget) {
                *mTarget = mSelectedIndex;
            }
        }
    }
    }

    if(mParent)
    {
        //mParent->Notify(this);

    }
}


