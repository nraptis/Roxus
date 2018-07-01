//
//  TestBadge.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "TestBadge.hpp"
#include "GLApp.h"

TestBadge::TestBadge() {
    mClipsContent = true;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mName = "TestBadge";


    AddSubview(mDecor1);
    AddSubview(mDecor2);
    AddSubview(mDecor3);
    AddSubview(mDecor4);


    mLoopFrame = gApp->mSequenceSquare.GetMaxFrame();


    
}

TestBadge::~TestBadge() {
    Log("Free(TestBadge)\n");
}

void TestBadge::PositionContent() {

    //Log("---PositionContent(TestBadge)\n");

    SetSize(gApp->mSequenceSquare.mWidth, gApp->mSequenceSquare.mHeight);
}

void TestBadge::Update() {
    mLoopFrame = gApp->mSequenceSquare.LoopFrame(mLoopFrame, 0.33f);
}

void TestBadge::Draw() {
    FView::Draw();

    gApp->mDarkTile.Center(mWidth2, mHeight2);

    Graphics::SetColor(0.25f, 0.125f, 0.75f, 0.35f);
    Graphics::OutlineRectInside(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 3.0f);

    Graphics::SetColor();

    gApp->mSequenceSquare.Draw(mLoopFrame, mWidth2, mHeight2, 1.0f, 0.0f);

}

