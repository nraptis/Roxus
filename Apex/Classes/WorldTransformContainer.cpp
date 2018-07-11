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

    mConsumesTouches = false;
    SetTransformAnchor(0.5f, 0.5f);
    mName = "path_editor";

    mPinCanvas1 = new FCanvas();
    AddChild(mPinCanvas1);
    mPinCanvas1->mColor = FColor(0.5f, 0.5f, 1.0f, 0.75f);
    mPinCanvas1->mConsumesTouches = false;

    mPinCanvas2 = new FCanvas();
    AddChild(mPinCanvas2);
    mPinCanvas2->mColor = FColor(1.0f, 1.0f, 1.0f, 0.75f);
    mPinCanvas2->mConsumesTouches = false;

    mPivotX = 0.0f;
    mPivotY = 0.0f;
}

WorldTransformContainer::~WorldTransformContainer() {

}

void WorldTransformContainer::Layout() {

    //SetSize(aImageWidth + aImageWidth, aImageHeight);
    SetSize(1024.0f, 512.0f);
    SetPos(-mWidth2, -mHeight2);

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

    Graphics::SetColor(0.66f, 0.66f, 0.66f, 1.0f);
    Graphics::DrawRect(0.0f, mPivotY - 4.0f, mWidth, 8.0f);
    Graphics::DrawRect(mPivotX - 4.0f, 0.0f, 8.0f, mHeight);

    Graphics::SetColor(0.25f, 0.25f, 0.95f, 1.0f);
    Graphics::DrawRect(0.0f, mPivotY - 2.0f, mWidth, 4.0f);
    Graphics::DrawRect(mPivotX - 2.0f, 0.0f, 4.0f, mHeight);

    Graphics::SetColor(1.0f, 0.85f, 0.0f, 1.0f);
    Graphics::OutlineRect(mPivotX - 10.0f, mPivotY - 10.0f, 20.0f, 20.0f, 4.0f);

    Graphics::SetColor(0.25f, 0.25f, 0.25f, 1.0f);
    Graphics::OutlineRect(mPivotX - 6.0f, mPivotY - 6.0f, 12.0f, 12.0f, 4.0f);

    Graphics::SetColor();
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


