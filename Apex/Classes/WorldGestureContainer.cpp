//
//  WorldGestureContainer.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "WorldGestureContainer.hpp"
#include "WorldTransformContainer.hpp"
#include "GLApp.h"

WorldGestureContainer::WorldGestureContainer() {
    mName = "path_editor";
    mWorldTransform = 0;

    mWorldOffsetX = 0.0f;
    mWorldOffsetY = 0.0f;

    mWorldPanStartOffsetX = mWorldOffsetX;
    mWorldPanStartOffsetY = mWorldOffsetY;

    mWorldScale = 0.75f;
    mWorldPinchStartScale = mWorldScale;

    SetTransformScaleX(0.25f);
    SetTransformAnchor(1.0f, 0.5f);
    SetTransformRotation(10.0f);

}

WorldGestureContainer::~WorldGestureContainer() {

}

void WorldGestureContainer::Layout() {

    if (mWorldTransform) {
        SetFrame(0.0f, 0.0f, mWorldTransform->mWidth, mWorldTransform->mHeight);

    }
    if (mParent) {
        //SetFrame(0.0f, 0.0f, mParent->mWidth, mParent->mHeight);
    }
}

void WorldGestureContainer::Update() {

    if (mWorldTransform) {
        mWorldTransform->SetTransformX(mWorldOffsetX);
        mWorldTransform->SetTransformY(mWorldOffsetY);

        mWorldTransform->SetTransformScale(mWorldScale);
        //mWorldTransform->SetTransformScaleY(mWorldScale);

        mWorldTransform->SetTransformRotation(mWorldRotation);
    }
}

void WorldGestureContainer::Draw() {
    Graphics::SetColor(1.0f, 0.66f, 0.66f, 0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);

    Graphics::SetColor();
}

void WorldGestureContainer::TouchDown(float pX, float pY, void *pData) {

}

void WorldGestureContainer::TouchMove(float pX, float pY, void *pData) {

}

void WorldGestureContainer::TouchUp(float pX, float pY, void *pData) {

}

void WorldGestureContainer::TouchFlush() {

}

void WorldGestureContainer::KeyDown(int pKey) {

}

void WorldGestureContainer::KeyUp(int pKey) {

}

void WorldGestureContainer::Notify(void *pSender, const char *pNotification) {

}




void WorldGestureContainer::PanBegin(float pX, float pY) {

    mWorldPanStartOffsetX = mWorldOffsetX;
    mWorldPanStartOffsetY = mWorldOffsetY;


    //mWorldOffsetX = 0.0f;
    //mWorldOffsetY = 0.0f;

    // = mWorldOffsetX;
    //mWorldPanStartOffsetY = mWorldOffsetY;

    //mWorldScale = 0.75f;
    //mWorldPinchStartScale = mWorldScale;


}

void WorldGestureContainer::Pan(float pX, float pY) {

    mWorldOffsetX = mWorldPanStartOffsetX + mGesturePanDistX;
    mWorldOffsetY = mWorldPanStartOffsetY + mGesturePanDistY;

    


}

void WorldGestureContainer::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {

}

void WorldGestureContainer::PinchBegin(float pScale) {

}

void WorldGestureContainer::Pinch(float pScale) {

}

void WorldGestureContainer::PinchEnd(float pScale) {

}

void WorldGestureContainer::TapDouble(float pX, float pY) {

}

void WorldGestureContainer::RotateStart(float pRotation) {

}

void WorldGestureContainer::Rotate(float pRotation) {

}

void WorldGestureContainer::RotateEnd(float pRotation) {

}
