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

    mPinCanvas1 = new FCanvas();
    AddChild(mPinCanvas1);
    mPinCanvas1->mColor = FColor(0.5f, 0.5f, 1.0f, 0.75f);

    mPinCanvas2 = new FCanvas();
    AddChild(mPinCanvas2);
    mPinCanvas2->mColor = FColor(1.0f, 1.0f, 1.0f, 0.75f);
}

WorldTransformContainer::~WorldTransformContainer() {

}

void WorldTransformContainer::Layout() {

    //SetSize(aImageWidth + aImageWidth, aImageHeight);
    SetSize(1024.0f, 512.0f);

    mPinCanvas1->SetX(50.0f);
    mPinCanvas1->SetY(50.0f);
    mPinCanvas1->SetWidth(512.0f);
    mPinCanvas1->SetHeight(256.0f);
    mPinCanvas1->SetTransformAnchor(1.0f, 1.0f);
    mPinCanvas1->SetTransformRotation(-22.0f);

    mPinCanvas2->SetX(1024.0f - (300 + 60.0f));
    mPinCanvas2->SetY(512.0f - (100 + 60.0f));
    mPinCanvas2->SetWidth(300.0f);
    mPinCanvas2->SetHeight(100.0f);
    mPinCanvas2->SetTransformAnchor(0.0f, 0.0f);
    mPinCanvas2->SetTransformRotation(22.0f);

}

void WorldTransformContainer::Update() {

    
}

void WorldTransformContainer::Draw() {

    Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.75f);
    //gApp->m1024x1024.Draw(0.0f, 0.0f);

    gApp->m1024x1024.DrawQuadRect(0.0f, 0.0f, 512.0f, 512.0f);
    gApp->m1024x1024.DrawQuadRect(512.0f, 0.0f, 512.0f, 512.0f);


    //gApp->m1024x1024.Draw(gApp->m1024x1024.mWidth, 0.0f);

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


