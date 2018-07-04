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

    mClipsContent = false;

    mBackQuad.Corner1SetColor(0.96f, 0.92f, 0.88f);
    mBackQuad.Corner2SetColor(0.98f, 0.95f, 0.99f);
    mBackQuad.Corner3SetColor(0.97f, 0.96f, 0.96f);
    mBackQuad.Corner4SetColor(0.95f, 0.97f, 0.94f);
    
    //mDragCanvas1 = new DragableCanvas();
    //mDragCanvas1->mName = "DR-1";
    //mDragCanvas1->mColor = FColor(1.0f, 0.77, 0.9);
    //AddChild(mDragCanvas1);
    //mDragCanvas1->SetFrame(40.0f, 20.0f, 270.0f, 200.0f);


    mToolMenu1 = new ToolMenu();
    mToolMenu1->SetFrame(100.0f, 20.0f, 300.0f, 220.0f);
    mToolMenu1->mName = "TM-1";
    AddChild(mToolMenu1);

    mToolMenu2 = new ToolMenu();
    mToolMenu2->SetFrame(10.0f, 300.0f, 400.0f, 280.0f);
    mToolMenu2->mName = "TM-2";
    AddChild(mToolMenu2);

    mToolMenu3 = new ToolMenu();
    mToolMenu3->SetFrame(300.0f, 510.0f, 200.0f, 340.0f);
    mToolMenu3->mName = "TM-3";
    AddChild(mToolMenu3);

    
    mMenuIndex = 10;
    

    //gNotify.Register(this, mToolMenu1, "f1");
    //gNotify.Register(this, mToolMenu2, "f1");
    //gNotify.Register(this, mToolMenu3, "f1");


    /*
    gNotify.Print();

    gNotify.Post(mToolMenu1, "f1");

    gNotify.Unregister(this, mToolMenu1, "f1");

    gNotify.Print();
     */

    
}

PGMainCanvas::~PGMainCanvas() {
    gTool = 0;
}

void PGMainCanvas::Layout() {
    SetFrame(6.0f, 6.0f, gDeviceWidth - 12.0f, gDeviceHeight - 12.0f);
    mBackQuad.SetRect(0.0f, 0.0f, mWidth, mHeight);
}

void PGMainCanvas::Update() {

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
