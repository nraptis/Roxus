//
//  PGPathEditor.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGPathEditor.hpp"


PGPathEditor::PGPathEditor() {
    mName = "path_editor";


    mPointList.Add(100.0f, 100.0f);
    mPointList.Add(300.0f, 100.0f);
    mPointList.Add(400.0f, 500.0f);


}

PGPathEditor::~PGPathEditor() {

}

void PGPathEditor::Layout() {
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);

}

void PGPathEditor::Update() {

}

void PGPathEditor::Draw() {


}

void PGPathEditor::TouchDown(float pX, float pY, void *pData) {
    if (pX <= 20 && pY >= (mHeight - 20)) {
        EnumList(FCanvas, aCanvas, mChildren) {
            if(gRand.Get(10) > 4) {
                aCanvas->Kill();
            }
        }
    }

}

void PGPathEditor::TouchMove(float pX, float pY, void *pData) {

}

void PGPathEditor::TouchUp(float pX, float pY, void *pData) {

}

void PGPathEditor::TouchFlush() {

}

void PGPathEditor::KeyDown(int pKey) {

}

void PGPathEditor::KeyUp(int pKey) {

}

