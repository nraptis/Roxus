//
//  PGMainCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGMainCanvas.hpp"
#include "GLApp.h"

PGMainCanvas::PGMainCanvas() {
    
    mName = "PGMainCanvas";

    mClipsContent = false;

    mBackQuad.Corner1SetColor(0.76f, 0.62f, 0.76f);
    mBackQuad.Corner2SetColor(0.86f, 0.66f, 0.76f);
    mBackQuad.Corner3SetColor(0.47f, 0.86f, 0.56f);
    mBackQuad.Corner4SetColor(0.75f, 0.66f, 0.76f);


    mDragCanvas1 = new DragableCanvas();
    mDragCanvas1->mName = "DR-1";
    mDragCanvas1->mColor = FColor(1.0f, 0.77, 0.9);
    AddChild(mDragCanvas1);
    mDragCanvas1->SetFrame(40.0f, 20.0f, 270.0f, 200.0f);



    /*
    mDragCanvas2 = new DragableCanvas();
    mDragCanvas2->mName = "DR-2";
    mDragCanvas2->mColor = FColor(0.0f, 1.0f, 0.45);
    AddChild(mDragCanvas2);
    mDragCanvas2->SetFrame(50.0f, 260.0f, 80.0f, 300.0f);


    mDragCanvas3 = new DragableCanvas();
    mDragCanvas3->mName = "DR-3";
    mDragCanvas3->mColor = FColor(0.26, 0.0f, 1.0f);
    AddChild(mDragCanvas3);
    mDragCanvas3->SetFrame(150.0f, 380.0f, 200.0f, 160.0f);
     */

}

PGMainCanvas::~PGMainCanvas() {
    Log("Free(PGMainCanvas)\n");

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
