//
//  ToolMenuHeader.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuHeader.hpp"
#include "ToolMenu.hpp"
#include "PGMainCanvas.hpp"
#include "ToolMenu.hpp"

#include "UIImagePicker.hpp"


ToolMenuHeader::ToolMenuHeader() {
    mMenu = 0;

    mName = "ToolMenuHeader";

    mConsumesTouches = false;

    mMenuBackground.SetColorTop(0.325f, 0.325f, 0.325f);
    mMenuBackground.SetColorBottom(0.365f, 0.365f, 0.345f);
    mMenuBackground.mCornerRadius = 6.0f;
    mMenuBackground.mRoundBottom = false;

    mButtonClose = new UIButton();
    mButtonClose->mName = "Close Button";
    mButtonClose->mDrawCloseX = true;
    AddChild(mButtonClose);
    
    mButtonMinimize = new UIButton();
    mButtonMinimize->mName = "Minimize Button";
    mButtonMinimize->mDrawMinimize = true;
    AddChild(mButtonMinimize);
    
    gNotify.Register(this, mButtonClose, "click");
    gNotify.Register(this, mButtonMinimize, "click");
}

ToolMenuHeader::~ToolMenuHeader() {
    
}

void ToolMenuHeader::Layout() {
    float aButtonPadding = 4.0f;
    float aButtonSize = mHeight - aButtonPadding * 2.0f;
    mButtonMinimize->SetFrame(aButtonPadding, aButtonPadding, aButtonSize, aButtonSize);
    mButtonClose->SetFrame(mWidth - (aButtonPadding + aButtonSize), aButtonPadding, aButtonSize, aButtonSize);
    mMenuBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mMenuBackground.mRefresh = true;
}

void ToolMenuHeader::Update() {

}

void ToolMenuHeader::Draw() {

    FCanvas::Draw();


    //mMenuBackgroundShadow.Draw();
    //mMenuBackgroundOutline.Draw();
    mMenuBackground.Draw();

}

void ToolMenuHeader::TouchDown(float pX, float pY, void *pData) {

}

void ToolMenuHeader::TouchMove(float pX, float pY, void *pData) {

}

void ToolMenuHeader::TouchUp(float pX, float pY, void *pData) {

}

void ToolMenuHeader::TouchFlush() {

}

void ToolMenuHeader::Notify(void *pSender, const char *pNotification) {
    printf("Header Notify: [%s][%s]\n", ((FCanvas *)pSender)->mName.c(), pNotification);
    
    if (pSender == mButtonClose) {
        printf("Close Button...\n");
        mParent->Notify(pSender, pNotification);
    }

    if (FString(pNotification) == "click") {
    if (pSender == mButtonMinimize) {

        UIImagePicker *aImagePicker = new UIImagePicker();
        gTool->AddChild(aImagePicker);
        aImagePicker->FillWithAny();


        printf("Minimize Button...\n");

        /*
        for(int i=0;i<200;i++) {
        ToolMenu *aToolMenu = new ToolMenu();
        aToolMenu->SetFrame(gRand.Get(200), gRand.Get(200), 100 + gRand.Get(200), 100 + gRand.Get(200));

        gTool->mMenuIndex+=1;
        aToolMenu->mName = FString("TOOL") + FString(gTool->mMenuIndex);
        gTool->AddChild(aToolMenu);
        
        gNotify.Register(this, aToolMenu, "what");
         */

        }
    }

}



