//
//  PGMainCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGMainCanvas.hpp"
#include "GLApp.h"


PGMainCanvas *gTool = 0;
PGMainCanvas::PGMainCanvas() {
    gTool = this;
    mName = "_Playground_";
    mClipEnabled = false;
    mBackQuad.Corner1SetColor(0.96f, 0.92f, 0.88f);
    mBackQuad.Corner2SetColor(0.98f, 0.95f, 0.99f);
    mBackQuad.Corner3SetColor(0.97f, 0.96f, 0.96f);
    mBackQuad.Corner4SetColor(0.95f, 0.97f, 0.94f);

    mToolMenu1 = new ToolMenu();
    mToolMenu1->SetFrame(20.0f, 20.0f, 300.0f, 220.0f);
    mToolMenu1->mName = "TM-1";
    AddChild(mToolMenu1);
    
    mMenuIndex = 10;

}

PGMainCanvas::~PGMainCanvas() {
    gTool = 0;
}

void PGMainCanvas::Layout() {
    SetFrame(6.0f, 6.0f, gDeviceWidth - 12.0f, gDeviceHeight - 12.0f);
    mBackQuad.SetRect(0.0f, 0.0f, mWidth, mHeight);
}

void PGMainCanvas::Update() {
    //SetContentSize(gApp->mBackgroundLarge.mWidth, gApp->mBackgroundLarge.mHeight);


}

void PGMainCanvas::Draw() {
    mBackQuad.Draw();
}

void PGMainCanvas::TouchDown(float pX, float pY, void *pData) {
    if (pX <= 20 && pY >= (mHeight - 20)) {
        EnumList(FCanvas, aCanvas, mChildren) {
            if(gRand.Get(10) > 4) {
                aCanvas->Kill();
            }
        }
    }
}

void PGMainCanvas::TouchMove(float pX, float pY, void *pData) {

}

void PGMainCanvas::TouchUp(float pX, float pY, void *pData) {

}

void PGMainCanvas::TouchFlush() {

}

void PGMainCanvas::MouseDown(float pX, float pY, int pButton) {

}

void PGMainCanvas::MouseMove(float pX, float pY) {

}

void PGMainCanvas::MouseUp(float pX, float pY, int pButton) {

}

void PGMainCanvas::MouseWheel(int pDirection) {

}

void PGMainCanvas::KeyDown(int pKey) {

}

void PGMainCanvas::KeyUp(int pKey) {

}

