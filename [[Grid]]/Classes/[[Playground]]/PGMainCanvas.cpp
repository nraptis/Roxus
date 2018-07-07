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

    SetBackgroundDark();

    mMainToolbar = new PGMainToolbar();
    AddChild(mMainToolbar);

    mToolMenu1 = new ToolMenu();
    mToolMenu1->SetFrame(20.0f, 20.0f, 300.0f, 220.0f);
    mToolMenu1->mName = "TM-1";
    AddChild(mToolMenu1);


    mToolMenu2 = new ToolMenu();
    mToolMenu2->SetFrame(20.0f, 300.0f, 300.0f, 220.0f);
    mToolMenu2->mName = "TM-1";
    mToolMenu2->Collapse();
    AddChild(mToolMenu2);

    mToolMenu3 = new ToolMenu();
    mToolMenu3->SetFrame(20.0f, 300.0f, 300.0f, 220.0f);
    mToolMenu3->mName = "TM-1";
    mToolMenu3->Collapse();
    AddChild(mToolMenu3);




    PolygonMenu *aPolyMenu = new PolygonMenu();
    aPolyMenu->SetFrame(500.0f, 270.0f, 340.0f, 290.0f);
    aPolyMenu->Collapse();
    AddChild(aPolyMenu);



    mPolyMenu = new PolygonMenu();
    mPolyMenu->SetFrame(200.0f, 180.0f, 340.0f, 290.0f);
    AddChild(mPolyMenu);

    mMenuIndex = 10;


    BringChildToFront(mMainToolbar);

}

PGMainCanvas::~PGMainCanvas() {
    gTool = 0;
}

void PGMainCanvas::Layout() {
    SetFrame(1.0f, 1.0f, gDeviceWidth - 2.0f, gDeviceHeight - 2.0f);
    mBackQuad.SetRect(0.0f, 0.0f, mWidth, mHeight);
}

void PGMainCanvas::Update() {

    BringChildToFront(mMainToolbar);

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
    BringChildToFront(mMainToolbar);
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

void PGMainCanvas::SetBackgroundDark() {
    mBackQuad.Corner2SetColor(0.06f, 0.02f, 0.03f);
    mBackQuad.Corner4SetColor(0.08f, 0.05f, 0.09f);
    mBackQuad.Corner3SetColor(0.07f, 0.06f, 0.06f);
    mBackQuad.Corner1SetColor(0.05f, 0.07f, 0.04f);
}

void PGMainCanvas::SetBackgroundGray() {
    mBackQuad.Corner1SetColor(0.48f, 0.45f, 0.49f);
    mBackQuad.Corner3SetColor(0.46f, 0.47f, 0.48f);
    mBackQuad.Corner4SetColor(0.47f, 0.46f, 0.46f);
    mBackQuad.Corner2SetColor(0.45f, 0.47f, 0.44f);
}

void PGMainCanvas::SetBackgroundLight() {
    mBackQuad.Corner1SetColor(0.96f, 0.92f, 0.88f);
    mBackQuad.Corner2SetColor(0.98f, 0.95f, 0.99f);
    mBackQuad.Corner3SetColor(0.97f, 0.96f, 0.96f);
    mBackQuad.Corner4SetColor(0.95f, 0.97f, 0.94f);
}
