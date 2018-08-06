//
//  WorldTransformContainer.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "WorldTransformContainer.hpp"
#include "GLApp.hpp"
#include "GameArena.hpp"

WorldTransformContainer::WorldTransformContainer() {
    mConsumesTouches = false;
    SetTransformAnchor(0.5f, 0.5f);
    mName = "path_editor";
    mPivotX = 0.0f;
    mPivotY = 0.0f;
}

WorldTransformContainer::~WorldTransformContainer() {

}

void WorldTransformContainer::Layout() {
    SetSize(gArenaWidth, gArenaHeight);
    SetPos(-mWidth2, -mHeight2);
}

void WorldTransformContainer::Update() {

}

void WorldTransformContainer::Draw() {
    
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


