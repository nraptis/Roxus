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
    printf("WorldGestureContainer::Layout()\n\n");
    if (mParent) {
        SetFrame(0.0f, 0.0f, mParent->mWidth, mParent->mHeight);
        FRect aBounds = FRect(0.0f, 0.0f, mWidth, mHeight);
        mWorldPinchStartTouchCenterX = mWidth2;
        mWorldPinchStartTouchCenterY = mHeight2;
        mWorldPinchTouchCenterX = mWidth2;
        mWorldPinchTouchCenterY = mHeight2;
        if (mWorldTransform) {
            float aWorldWidth = mWorldTransform->mWidth;
            float aWorldHeight = mWorldTransform->mHeight;
            float aWorldScale = 1.0f;
            FRect aFit = FRect::FitAspectFit(aBounds, aWorldWidth, aWorldHeight, 10.0f, aWorldScale);
            mWorldScale = aWorldScale;
            mWorldOffsetX = mWidth2;
            mWorldOffsetY = mHeight2;
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

        //if (mIsPinching) {

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

            //We force our transformation to compute once...
            ComputeAbsoluteTransformation();


            //aArenaStartX -= aShiftX;
            //aArenaStartY -= aShiftY;


            ConvertPoint(aArenaStartX, aArenaStartY, this, mWorldTransform);

            //mWorldPinchStartArenaX = aArenaStartX;
            //mWorldPinchStartArenaY = aArenaStartY;

            //mWorldPinchStartTouchCenterX -= aShiftX;
            //mWorldPinchStartTouchCenterY -= aShiftY;

  //      }


}

void WorldGestureContainer::Draw() {
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

}

void WorldGestureContainer::TouchDown(float pX, float pY, void *pData) {

    if (mWorldTransform) {
        //float aX = pX;
        //float aY = pY;
        //mWorldPinchStartTouchCenterX = pX;
        //mWorldPinchStartTouchCenterY = pY;
        //mWorldTransform->ConvertPoint(aX, aY, this);
        //mWorldTransform->mPivotX = aX;
        //mWorldTransform->mPivotY = aY;

        //PinchBegin(1.0f);
        
    }

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

    printf("***PanBegin(%f, %f)\n", pX, pY);

    //mWorldOffsetX = 0.0f;
    //mWorldOffsetY = 0.0f;

    // = mWorldOffsetX;
    //mWorldPanStartOffsetY = mWorldOffsetY;

    //mWorldScale = 0.75f;
    //mWorldPinchStartScale = mWorldScale;

    if (mIsPinching == false) {
        mWorldPinchStartTouchCenterX = 0.0f;
        mWorldPinchStartTouchCenterY = 0.0f;
        mWorldPinchTouchCenterX = 0.0f;
        mWorldPinchTouchCenterY = 0.0f;
        mWorldPinchStartArenaX = 0.0f;
        mWorldPinchStartArenaY = 0.0f;
        mWorldTransform->ConvertPoint(mWorldPinchStartArenaX, mWorldPinchStartArenaY, this);
    }

}

void WorldGestureContainer::Pan(float pX, float pY) {
    mWorldOffsetX = mWorldPanStartOffsetX + mGesturePanDistX;
    mWorldOffsetY = mWorldPanStartOffsetY + mGesturePanDistY;

    mWorldPinchTouchCenterX = mWorldPinchStartTouchCenterX + mGesturePanDistX;
    mWorldPinchTouchCenterY = mWorldPinchStartTouchCenterY + mGesturePanDistY;

    printf("Pan(%f, %f)\n", mGesturePanDistX, mGesturePanDistY);
}

void WorldGestureContainer::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {
    printf("***PanEnd(%f, %f)\n", mGesturePanDistX, mGesturePanDistY);



    
}

void WorldGestureContainer::PinchBegin(float pScale) {
    mWorldPinchStartScale = mWorldScale;
    printf("***PinchBegin(%f)\n", mWorldPinchStartScale);

    //Kludge, normally we wouldn't set these here...
    //mTouch[0]->mX = mWorldPinchStartTouchCenterX;
    //mTouch[0]->mY = mWorldPinchStartTouchCenterY;
    //mTouch[1]->mX = mWorldPinchStartTouchCenterX;
    //mTouch[1]->mY = mWorldPinchStartTouchCenterY;

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

    printf("Pinch(%f)\n", pScale);
}

void WorldGestureContainer::PinchEnd(float pScale) {
    printf("***PinchEnd(%f)\n", pScale);


    /*
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

    //Where we were in the arena, converted with the current transformation...
    ConvertPoint(aArenaStartX, aArenaStartY, mWorldTransform, this);

    //Where we are on THIS minus where we were on THIS...
    mWorldOffsetX += (aTouchCenterX - aArenaStartX);
    mWorldOffsetY += (aTouchCenterY - aArenaStartY);

    mWorldTransform->SetTransformX(mWorldOffsetX);
    mWorldTransform->SetTransformY(mWorldOffsetY);

    //We force our transformation to compute once...
    ComputeAbsoluteTransformation();

    */

}

void WorldGestureContainer::TapDouble(float pX, float pY) {

}

void WorldGestureContainer::RotateStart(float pRotation) {

}

void WorldGestureContainer::Rotate(float pRotation) {

}

void WorldGestureContainer::RotateEnd(float pRotation) {

}

//float WorldGestureContainer::UntransformX(float pX) {
//    float aResult = pX;
//    if (mWorldTransform) {
//        aResult = mWidth2 + (aResult - mWorldTransform->mWidth2) * mWorldScale;
//    }
//    return aResult;
//    //return mCenterX + (pX - gArenaWidth2) * mZoomScale;
//}
//
//float WorldGestureContainer::UntransformY(float pY) {
//    float aResult = pY;
//    if (mWorldTransform) {
//        aResult = mHeight2 + (aResult - mWorldTransform->mHeight2) * mWorldScale;
//    }
//    return aResult;
//}
//
//float WorldGestureContainer::TransformX(float pX) {
//    float aResult = pX;
//    if (mWorldTransform) {
//        aResult = mWorldTransform->mWidth2 + (aResult - mWidth2) / mWorldScale;
//    }
//    return aResult;
//}
//
//float WorldGestureContainer::TransformY(float pY) {
//
//
//
//    return gArenaHeight2 + (pY - mCenterY) / mZoomScale;
//}


