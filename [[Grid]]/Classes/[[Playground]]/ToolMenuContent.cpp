//
//  ToolMenuContent.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//
//
//  ToolMenuContent.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuContent.hpp"


//
//  ToolMenuContent.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "ToolMenuContent.hpp"
#include "GLApp.h"

ToolMenuContent::ToolMenuContent() {
    mConsumesTouches = false;
    mClipDisabled = false;

    mName = "ToolMenuContent";

    /*
    mB1.SetFrame(-10.0f, -10.0f, 120.0f, 66.0f);
    AddChild(mB1);

    mB2.SetFrame(40.0f, 100.0f, 660.0f, 100.0f);
    AddChild(mB2);

    mB3.SetFrame(170.0f, 260.0f, 180.0f, 100.0f);
    AddChild(mB3);

    mB4.SetFrame(170, 330.0f, 260.0f, 680.0f);
    AddChild(mB4);
    */

}

ToolMenuContent::~ToolMenuContent() {
    Log("Free(ToolMenuContent)\n");
}

void ToolMenuContent::Layout() {
    
}

void ToolMenuContent::Update() {

}

void ToolMenuContent::Draw() {
    
}

void ToolMenuContent::TouchDown(float pX, float pY, void *pData) {

}

void ToolMenuContent::TouchMove(float pX, float pY, void *pData) {

}

void ToolMenuContent::TouchUp(float pX, float pY, void *pData) {

}

void ToolMenuContent::TouchFlush() {

}


void ToolMenuContent::MouseDown(float pX, float pY, int pButton) {

}

void ToolMenuContent::MouseMove(float pX, float pY) {

}

void ToolMenuContent::MouseUp(float pX, float pY, int pButton) {

}

void ToolMenuContent::MouseWheel(int pDirection) {

}

void ToolMenuContent::KeyDown(int pKey) {

}

void ToolMenuContent::KeyUp(int pKey) {

}

