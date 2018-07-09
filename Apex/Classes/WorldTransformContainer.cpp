//
//  WorldTransformContainer.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "WorldTransformContainer.hpp"
#include "GLApp.h"

WorldTransformContainer::WorldTransformContainer() {
    SetTransformAnchor(1.0f, 1.0f);
    mName = "path_editor";

}

WorldTransformContainer::~WorldTransformContainer() {

}

void WorldTransformContainer::Layout() {

    float aImageWidth = gApp->m1024x1024.mWidth;
    float aImageHeight = gApp->m1024x1024.mHeight;

    SetSize(aImageWidth + aImageWidth, aImageHeight);
}

void WorldTransformContainer::Update() {

    
}

void WorldTransformContainer::Draw() {

    Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.75f);
    gApp->m1024x1024.Draw(0.0f, 0.0f);
    gApp->m1024x1024.Draw(gApp->m1024x1024.mWidth, 0.0f);

    Graphics::SetColor(0.45f, 0.35f, 0.95f, 0.65f);
    Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 12.0f);
}

void WorldTransformContainer::TouchDown(float pX, float pY, void *pData) {

}

void WorldTransformContainer::TouchMove(float pX, float pY, void *pData) {

}

void WorldTransformContainer::TouchUp(float pX, float pY, void *pData) {

}

void WorldTransformContainer::TouchFlush() {

}

void WorldTransformContainer::KeyDown(int pKey) {

}

void WorldTransformContainer::KeyUp(int pKey) {

}

void WorldTransformContainer::Notify(void *pSender, const char *pNotification) {

}


