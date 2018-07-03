//
//  CNVBadge.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVBadge.hpp"
#include "GLApp.h"

CNVBadge::CNVBadge() {
    mClipsContent = true;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mName = "CNVBadge";


    AddChild(mDecor1);
    AddChild(mDecor2);
    AddChild(mDecor3);

    mDecor4 = new CNVBadgeDecor4();
    AddChild(mDecor4);

    mFrame = gApp->mSequenceSquare.GetMaxFrame();


    
}

CNVBadge::~CNVBadge() {
    Log("Free(CNVBadge)\n");
}

void CNVBadge::Layout() {

    Log("---Layout(CNVBadge)\n");

    SetSize(gApp->mSequenceSquare.mWidth, gApp->mSequenceSquare.mHeight);
}

void CNVBadge::Update() {

    mFrame = gApp->mSequenceSquare.LoopFrame(mFrame, 0.33f);





}

void CNVBadge::Draw() {
    FCanvas::Draw();

    gApp->mDarkTile.Center(mWidth2, mHeight2);

    Graphics::SetColor(0.25f, 0.125f, 0.75f, 0.35f);
    Graphics::OutlineRectInside(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f, 3.0f);

    Graphics::SetColor();

    gApp->mSequenceSquare.Draw(mFrame, mWidth2, mHeight2, 1.0f, 0.0f);

}

