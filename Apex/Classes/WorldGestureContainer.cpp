//
//  WorldGestureContainer.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "WorldGestureContainer.hpp"
#include "WorldTransformContainer.hpp"
#include "WorldContainer.hpp"
#include "GameArena.h"
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

    mWorldRotation = 0.0f;

    mWorldPinchStartTouchCenterX = 0.0f;
    mWorldPinchStartTouchCenterY = 0.0f;
    mWorldPinchTouchCenterX = 0.0f;
    mWorldPinchTouchCenterY = 0.0f;

    mWorldPinchStartArenaX = 0.0f;
    mWorldPinchStartArenaY = 0.0f;
}

WorldGestureContainer::~WorldGestureContainer() {

}

void WorldGestureContainer::Layout() {
    if (mParent) {
        SetFrame(0.0f, 0.0f, mParent->mWidth, mParent->mHeight);
        FRect aBounds = FRect(0.0f, 0.0f, mWidth, mHeight);
        mWorldRotation = 0.0f;
        mWorldPinchStartTouchCenterX = mWidth2;
        mWorldPinchStartTouchCenterY = mHeight2;
        mWorldPinchTouchCenterX = mWidth2;
        mWorldPinchTouchCenterY = mHeight2;
        if (mWorldTransform) {
            float aWorldWidth = gArenaActiveWidth;
            float aWorldHeight = gArenaActiveHeight;
            float aWorldScale = 1.0f;
            FRect aFit = FRect::FitAspectFit(aBounds, aWorldWidth, aWorldHeight, 10.0f, aWorldScale);
            mWorldScale = aWorldScale;
            mWorldOffsetX = mWidth2 + gArenaActiveX * aWorldScale;
            mWorldOffsetY = mHeight2 + gArenaActiveY * aWorldScale;
            mWorldPinchStartArenaX = mWorldTransform->mWidth2;
            mWorldPinchStartArenaY = mWorldTransform->mHeight2;
        }
    }
}

void WorldGestureContainer::Update() {

    mWorldTransform->SetTransformX(mWorldOffsetX);
    mWorldTransform->SetTransformY(mWorldOffsetY);
    mWorldTransform->SetTransformScale(mWorldScale);
    mWorldTransform->SetTransformRotation(mWorldRotation);


    //if ((gEnvironment != ENV_WIN32 && gEnvironment != ENV_MAC) || (mIsPanning == false)) {
    //We force our transformation to compute once, then our "arena touch point"
    //becomes correct and we can see how much our other transforms have displaced
    //the total arena from the center of where our touches landed...
    //TODO: Only need to do this if something changed...
    ComputeAbsoluteTransformation();

    //Now our offset discrepency will be computed correctly...
    float aArenaStartX = mWorldPinchStartArenaX;
    float aArenaStartY = mWorldPinchStartArenaY;
    float aTouchCenterX = mWorldPinchTouchCenterX;
    float aTouchCenterY = mWorldPinchTouchCenterY;
    ConvertPoint(aArenaStartX, aArenaStartY, mWorldTransform, this);


    float aShiftX = aTouchCenterX - aArenaStartX;
    float aShiftY = aTouchCenterY - aArenaStartY;

    //Where we are on THIS minus where we were on THIS...
    mWorldOffsetX += aShiftX;
    mWorldOffsetY += aShiftY;

    mWorldTransform->SetTransformX(mWorldOffsetX);
    mWorldTransform->SetTransformY(mWorldOffsetY);

    ComputeAbsoluteTransformation();
    ConvertPoint(aArenaStartX, aArenaStartY, this, mWorldTransform);

    //}

}

void WorldGestureContainer::Draw() {
    
    /*
     Graphics::SetColor(1.0f, 0.66f, 0.66f, 0.25f);
     Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
     Graphics::SetColor();

     float aColorCycle1 = 0.0f;
     float aColorCycle2 = 0.0f;

     for (float aY = 0.0f;aY<=mHeight;aY += 4.0f) {
     Graphics::SetColor(0.25f, aColorCycle1 * 0.25f, (1.0f - aColorCycle2) * 0.25f, 0.65f);
     Graphics::DrawRect(0.0f, aY, mWidth, 2.0f);

     aColorCycle1 += 0.1f;
     if (aColorCycle1 > 1.0f) {
     aColorCycle1 -= 1.0f;
     }

     aColorCycle2 += 0.05f;
     if (aColorCycle2 > 1.0f) {
     aColorCycle2 -= 1.0f;
     }
     }
     
     */

}

void WorldGestureContainer::TouchDown(float pX, float pY, void *pData) {

    if (gEnvironment == ENV_WIN32 || gEnvironment == ENV_MAC) {
        if (mTouchCount > 0) {
            //mMouseZoomCenterX = mTouch[0]->mX;
            //mMouseZoomCenterY = mTouch[0]->mY;

            mWorldPinchStartTouchCenterX = mTouch[0]->mX;
            mWorldPinchStartTouchCenterY = mTouch[0]->mY;
            mWorldPinchTouchCenterX = mWorldPinchStartTouchCenterX;
            mWorldPinchTouchCenterY = mWorldPinchStartTouchCenterY;

            mWorldPinchStartArenaX = mWorldPinchTouchCenterX;
            mWorldPinchStartArenaY = mWorldPinchTouchCenterY;
            mWorldTransform->ConvertPoint(mWorldPinchStartArenaX, mWorldPinchStartArenaY, this);
        }
    }
}

void WorldGestureContainer::TouchMove(float pX, float pY, void *pData) {

}

void WorldGestureContainer::TouchUp(float pX, float pY, void *pData) {

}

void WorldGestureContainer::TouchFlush() {

}

void WorldGestureContainer::MouseWheel(int pDirection) {
    printf("WorldGestureContainer::MouseWheel(%d)\n", pDirection);
    if (pDirection > 0) {
        mWorldScale = mWorldScale * 1.05f;
    } else {
        mWorldScale = mWorldScale * 0.95f;
    }
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

    if (mIsPinching == false && mTouchCount > 0) {
            mWorldPinchStartTouchCenterX = mTouch[0]->mX;
            mWorldPinchStartTouchCenterY = mTouch[0]->mY;
            mWorldPinchTouchCenterX = mWorldPinchStartTouchCenterX;
            mWorldPinchTouchCenterY = mWorldPinchStartTouchCenterY;
            mWorldPinchStartArenaX = mWorldPinchTouchCenterX;
            mWorldPinchStartArenaY = mWorldPinchTouchCenterY;
            mWorldTransform->ConvertPoint(mWorldPinchStartArenaX, mWorldPinchStartArenaY, this);
    }
}

void WorldGestureContainer::Pan(float pX, float pY) {
    mWorldOffsetX = mWorldPanStartOffsetX + mGesturePanDistX;
    mWorldOffsetY = mWorldPanStartOffsetY + mGesturePanDistY;

    mWorldPinchTouchCenterX = mWorldPinchStartTouchCenterX + mGesturePanDistX;
    mWorldPinchTouchCenterY = mWorldPinchStartTouchCenterY + mGesturePanDistY;
}

void WorldGestureContainer::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {

}

void WorldGestureContainer::PinchBegin(float pScale) {
    mWorldPinchStartScale = mWorldScale;
    if (gEnvironment == ENV_MAC || gEnvironment == ENV_WIN32) {
        printf("***FATAL ERROR*** [Pinching on Computer]\n");
    }

    mWorldPinchStartTouchCenterX = (mTouch[0]->mX + mTouch[1]->mX) * 0.5f;
    mWorldPinchStartTouchCenterY = (mTouch[0]->mY + mTouch[1]->mY) * 0.5f;

    mWorldPinchTouchCenterX = mWorldPinchStartTouchCenterX;
    mWorldPinchTouchCenterY = mWorldPinchStartTouchCenterY;

    mWorldPinchStartArenaX = mWorldPinchStartTouchCenterX;
    mWorldPinchStartArenaY = mWorldPinchStartTouchCenterY;
    mWorldTransform->ConvertPoint(mWorldPinchStartArenaX, mWorldPinchStartArenaY, this);
}

void WorldGestureContainer::Pinch(float pScale) {
    //mWorldPinchStartScale = mWorldScale;
    mWorldScale = mWorldPinchStartScale * pScale;
}

void WorldGestureContainer::PinchEnd(float pScale) {

}

void WorldGestureContainer::TapSingle(float pX, float pY) {
    float aX = pX;
    float aY = pY;
    mWorldTransform->ConvertPoint(aX, aY, this);
    gArena->Click(aX, aY);
}

void WorldGestureContainer::TapDouble(float pX, float pY) {

}

void WorldGestureContainer::RotateStart(float pRotation) {

}

void WorldGestureContainer::Rotate(float pRotation) {

}

void WorldGestureContainer::RotateEnd(float pRotation) {

}

