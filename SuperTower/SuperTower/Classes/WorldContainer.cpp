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
#include "EditorMainMenu.hpp"

WorldContainer *gWorldContainer = 0;
WorldContainer::WorldContainer() {
    gWorldContainer = this;

    mTestMenu = 0;
    mGestureContainer = 0;
    mTransformContainer = 0;
    mArena = 0;
    
    mName = "world_container";

    mGestureContainer = new WorldGestureContainer();
    AddChild(mGestureContainer);

    mTransformContainer = new WorldTransformContainer();
    mTransformContainer->Layout();
    mGestureContainer->AddChild(mTransformContainer);
    mGestureContainer->mWorldTransform = mTransformContainer;

    //mTestMenu = new WorldMenu(this);
    //AddChild(mTestMenu);

    if (gEditorMode) {
        gEditor = new EditorGameArena();
        mArena = gEditor;
        mEditorMenu = new EditorMainMenu();
        AddChild(mEditorMenu);
    } else {
        mArena = new GameArena();
    }
}

WorldContainer::~WorldContainer() {
    if (gWorldContainer == this) {
        gWorldContainer = 0;
    }
    if (mGestureContainer) {
        mGestureContainer = 0;
    }
}

void WorldContainer::Layout() {
    if (mParent) {
        SetFrame(0.0f, 0.0f, mParent->mWidth, mParent->mHeight);
        if (mDidUpdate == false) {
            float aWidth = mWidth - 64.0f;
            float aHeight = mHeight - 64.0f;
            if (aWidth > 420.0f) { aWidth = 420.0f; }
            if (640.0f > 640.0f) { aHeight = 640.0f; }
            if (mEditorMenu->mExpanded) {
                mEditorMenu->SetFrame(32.0f, 32.0f, aWidth, aHeight);
            } else {
                mEditorMenu->SetFrame(32.0f, 32.0f, aWidth, mEditorMenu->GetHeight());
            }
        }
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
