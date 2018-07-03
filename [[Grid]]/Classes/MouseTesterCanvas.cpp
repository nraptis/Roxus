//
//  MouseTesterCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "MouseTesterCanvas.hpp"


//
//  MouseTesterCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "MouseTesterCanvas.hpp"
#include "GLApp.h"

MouseTesterCanvas::MouseTesterCanvas() {
    
    mName = "MouseTesterCanvas";

    mClipsContent = false;
}

MouseTesterCanvas::~MouseTesterCanvas() {
    Log("Free(MouseTesterCanvas)\n");
}

void MouseTesterCanvas::Layout() {



}

void MouseTesterCanvas::Update() {

}

void MouseTesterCanvas::Draw() {

    float aFillRed = 0.33f;
    float aFillGreen = 0.33f;
    float aFillBlue = 0.33f;

    if (mMouseLeftDown) {
        aFillRed = 0.66f;
    }

    if (mMouseMiddleDown) {
        aFillGreen = 0.66f;
    }



    if (mMouseRightDown) {
        aFillBlue = 0.66f;
    }

    if (mMouseLeftDownInside) {
        aFillRed = 1.0f;
    }

    if (mMouseMiddleDownInside) {
        aFillGreen = 1.0f;
    }

    if (mMouseRightDownInside) {
        aFillBlue = 1.0f;
    }

    Graphics::SetColor(aFillRed, aFillGreen, aFillBlue, 1.0);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);

    Graphics::SetColor();
    Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 4.0f);

    if (mTouchDown) {
        Graphics::SetColor(0.44f, 0.44f, 0.44f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 22.0f);
        Graphics::SetColor(0.66f, 0.66f, 0.75f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 18.0f);
    } else {
        Graphics::SetColor(0.88f, 0.88f, 0.88f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 22.0f);
        Graphics::SetColor(0.33f, 0.33f, 0.89f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 18.0f);
    }
}

void MouseTesterCanvas::TouchDown(float pX, float pY, void *pData) {

}

void MouseTesterCanvas::TouchMove(float pX, float pY, void *pData) {

}

void MouseTesterCanvas::TouchUp(float pX, float pY, void *pData) {

}

void MouseTesterCanvas::TouchFlush() {
    
}


void MouseTesterCanvas::MouseDown(float pX, float pY, int pButton) {

}

void MouseTesterCanvas::MouseMove(float pX, float pY) {

}

void MouseTesterCanvas::MouseUp(float pX, float pY, int pButton) {

}

void MouseTesterCanvas::MouseWheel(int pDirection) {

}

void MouseTesterCanvas::KeyDown(int pKey) {

}

void MouseTesterCanvas::KeyUp(int pKey) {

}
