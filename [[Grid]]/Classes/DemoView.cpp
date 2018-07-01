//
//  DemoView.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/22/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "DemoView.hpp"
#include "GLApp.h"

DemoView::DemoView() {


    mDemoRotateEnabled = false;
    mDemoRotateState = 0;
    mDemoRotateTimer = gRand.Get(60);


    mDemoRotateDir = 1;
    mDemoRotateTarget = gRand.F(6.0f, 12.0f);
    mDemoRotateSpeed = gRand.F(0.35f, 2.0f);


    SetTransformAnchor(0.5f, 0.5f);
}

DemoView::~DemoView() {

}


void DemoView::BaseUpdate() {

    int aRand1 = gRand.Get(3);
    int aRand2 = gRand.Get(3);

    if (mDemoRotateEnabled) {

        if (mDemoRotateState == 0) {
            mDemoRotateTimer--;
            if (mDemoRotateTimer <= 0) {
                mDemoRotateTimer = 0;
                RotateStart();
            }
        } else if (mDemoRotateState == 1) {
            if (mDemoRotateDir > 0) {
                mDemoRotation += mDemoRotateSpeed;
                if (mDemoRotation > mDemoRotateTarget) {
                    mDemoRotation = mDemoRotateTarget;
                    RotateStop();
                }

            } else {
                mDemoRotation -= mDemoRotateSpeed;
                if (mDemoRotation < mDemoRotateTarget) {
                    mDemoRotation = mDemoRotateTarget;
                    RotateStop();
                }
            }
        } else {
            mDemoRotateTimer--;
            if (mDemoRotateTimer <= 0) {
                mDemoRotateTimer = 0;
                RotateStart();
            }
        }


        SetTransformRotation(mDemoRotation);
    }


    Update();
}

void DemoView::RotateStart() {

    mDemoRotateSpeed = gRand.F(0.125f, 0.5f);
    if (mDemoRotateDir > 0) {
        mDemoRotateDir = -1;
        mDemoRotateTarget = gRand.F(-12.0f, -6.0f);

        if (gRand.GetBool()) {
            mDemoRotateTarget = 0.0f;
        }


    } else {
        mDemoRotateDir = 1;
        mDemoRotateTarget = gRand.F(6.0f, 12.0f);

        if (gRand.GetBool()) {
            mDemoRotateTarget = 0.0f;
        }
    }

    mDemoRotateState = 1;

}

void DemoView::RotateStop() {

    int aRand1 = gRand.Get(2);
    int aRand2 = gRand.Get(3);


    if (fabsf(mDemoRotation) < 0.5f) {
        if (gRand.GetBool()) {
            mDemoRotateDir = 1;
        } else {
            mDemoRotateDir = -1;
        }
    }

    if (aRand1 == 0) {
        RotateStart();
    } else if (aRand1 == 1) {
        mDemoRotateState = 0;

        if (aRand2 == 0) {
            mDemoRotateTimer = gRand.Get(100);
        } else if (aRand2 == 1) {
            mDemoRotateTimer = gRand.Get(200) + gRand.Get(200) + 60;
        } else {
            mDemoRotateTimer = 0;
        }


    } else {
        mDemoRotateState = 2;

        if (aRand2 == 0) {
            mDemoRotateTimer = gRand.Get(100);
        } else if (aRand2 == 1) {
            mDemoRotateTimer = gRand.Get(100) + gRand.Get(100) + 50;
        } else {
            mDemoRotateTimer = 0;
        }
    }


}


void DemoView::BaseDraw() {
    Draw();
}

void DemoView::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData) {
    mTouchX = pX;
    mTouchY = pY;
    if (mController == &(gAppBase->mViewController)) {
        Log("BaseTouchDown[%s]\n", mName.c());
    }

    SetTransformAnchor(mTouchX / mWidth, mTouchY / mHeight);
    
    TouchDown(pX, pY, pData);
}

void DemoView::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData) {
    mTouchX = pX;
    mTouchY = pY;

    TouchMove(pX, pY, pData);
}

void DemoView::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData) {
    mTouchX = pX;
    mTouchY = pY;

    TouchUp(pX, pY, pData);
}

void DemoView::BaseTouchFlush() {
    TouchFlush();
}
