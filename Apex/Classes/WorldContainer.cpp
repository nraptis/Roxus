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
    mTestMenu = 0;
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

    //mTestMenu = new WorldMenu(this);
    //AddChild(mTestMenu);

    mArena = new GameArena();
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
    if (mArena != 0) {
        mArena->Update();
    }
}

void WorldContainer::Draw() {

    FDrawQuad aQuad;
    aQuad.SetColorBottom(0.04f, 0.06f, 0.03f);
    aQuad.SetColorTop(0.02f, 0.02f, 0.05f);
    aQuad.SetRect(0.0f, 0.0f, mWidth, mHeight);
    aQuad.Draw();
    aQuad.SetColorLeft(0.04f, 0.03f, 0.02f, 0.25f);
    aQuad.SetColorRight(0.02f, 0.06f, 0.05f, 0.25f);
    aQuad.Draw();


    Graphics::SetColor(0.08f, 0.08f, 0.08f, 0.08f);
    Graphics::OutlineRectInside(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 10.0f);
    
    Graphics::SetColor();


    //mArena
    if (mTransformContainer != 0 && mArena != 0) {
        mTransformContainer->DrawTransform();
        mArena->Draw();
    }
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


