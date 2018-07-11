//
//  WorldContainer.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "WorldContainer.hpp"
#include "GLApp.h"
#include "WorldMenu.hpp"

WorldContainer *gWorldContainer = 0;
WorldContainer::WorldContainer() {

    mGestureContainer = 0;
    mTransformContainer = 0;
    mArena = 0;

    gWorldContainer = this;
    mName = "path_editor";

    mGestureContainer = new WorldGestureContainer();
    AddChild(mGestureContainer);

    mTransformContainer = new WorldTransformContainer();
    mTransformContainer->Layout();
    mGestureContainer->AddChild(mTransformContainer);
    mGestureContainer->mWorldTransform = mTransformContainer;

    mTestMenu = new WorldMenu(this);
    AddChild(mTestMenu);

}

WorldContainer::~WorldContainer() {
    
    gWorldContainer = 0;

    if (mGestureContainer) {
        mGestureContainer = 0;
    }

}

void WorldContainer::Layout() {
    if (mParent) {
        SetFrame(2.0f, 2.0f, mParent->mWidth - 4.0f, mParent->mHeight - 4.0f);
    }
}

void WorldContainer::Update() {

}

void WorldContainer::Draw() {
    Graphics::SetColor(0.66f, 0.66f, 0.025f, 0.85f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);

    Graphics::SetColor(1.0f, 0.95f, 0.125f, 0.85f);
    Graphics::OutlineRectInside(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 10.0f);
    
    Graphics::SetColor();
}

void WorldContainer::TouchDown(float pX, float pY, void *pData) {

}

void WorldContainer::TouchMove(float pX, float pY, void *pData) {

}

void WorldContainer::TouchUp(float pX, float pY, void *pData) {

}

void WorldContainer::TouchFlush() {

}

void WorldContainer::KeyDown(int pKey) {

}

void WorldContainer::KeyUp(int pKey) {

}

void WorldContainer::Notify(void *pSender, const char *pNotification) {

}


