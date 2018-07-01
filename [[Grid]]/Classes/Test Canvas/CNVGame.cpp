//
//  CNVGame.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVGame.hpp"
#include "GLApp.h"

CNVGame::CNVGame() {
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());

    mBoard = 0;


    mBoard = new CNVBoard();
    AddChild(mBoard);


    mName = "CNVGame";

    AddChild(mHeader);
    AddChild(mFooter);
}

CNVGame::~CNVGame() {
    Log("Free(CNVGame)\n");
}

void CNVGame::Layout() {
    Log("---Layout(CNVGame)\n");

    if (mParent) {
        float aParentWidth = mParent->mWidth;
        float aParentHeight = mParent->mHeight;

        if (aParentWidth > 10.0 && aParentHeight > 10.0) {

            float aWidth = aParentWidth * 0.45f;
            float aHeight = aParentHeight * 0.66f;

            float aBoardScale = 1.0f;

            if (mBoard) {
                if (mBoard->mWidth > 20.0f && mBoard->mHeight > 20.0f && mHeader.mWidth > 20.0f && mHeader.mHeight > 20.0f && mFooter.mWidth > 20.0f && mFooter.mHeight > 20.0f) {

                    float aHeaderHeight = mHeader.mHeight * mHeader.GetTransformScale() * mHeader.GetTransformScaleY();
                    float aFooterHeight = mFooter.mHeight * mFooter.GetTransformScale() * mFooter.GetTransformScaleY();

                    float aBoardHeight = mBoard->mHeight;
                    float aBoardWidth = mBoard->mWidth;

                    if (aBoardWidth > aWidth) {

                        FRect aBounds = FRect(0.0f, 0.0f, aWidth, 100000.0f);

                        FRect aFit = FRect::FitAspectFit(aBounds, aBoardWidth, aBoardHeight, 8.0f, aBoardScale);
                        mBoard->SetTransformScale(aBoardScale);
                        
                        aBoardHeight *= aBoardScale;
                        aBoardWidth *= aBoardScale;
                    } else {
                        mBoard->SetTransformScale(1.0f);
                    }

                    aHeight = aHeaderHeight + aFooterHeight + aBoardHeight;
                    mBoard->SetTransformX(aWidth / 2.0f - aBoardWidth / 2.0f);

                    mBoard->SetTransformY(aHeaderHeight);
                }
            }

            SetFrame(0.0f, 0.0f, aWidth, aHeight);



            FRect aBounds = FRect(0.0f, 0.0f, aParentWidth, aParentHeight);

            float aScale = 1.0f;
            FRect aFit = FRect::FitAspectFit(aBounds, aWidth, aHeight, 8.0f, aScale);

            SetTransformScale(aScale);
            SetTransformX(aFit.mX);
            SetTransformY(aFit.mY);
        }

        if (aParentWidth > 24.0f && aParentHeight > 24.0f && mWidth > 24.0f && mHeight > 24.0f) {

        }
    }

    if (mParent) {

    }
}

void CNVGame::Update() {

}

void CNVGame::Draw() {

    FCanvas::Draw();

    Graphics::SetColor(0.66f, 0.66f, 0.66f, 0.25f);
    Graphics::BlendSetSubtract();

    gApp->mTest_800x600_1.DrawQuadRect(0.0f, 0.0f, mWidth, mHeight);

    Graphics::BlendSetAlpha();



    Graphics::ClipDisable();
    Graphics::ResetMatrixModelView();
    Graphics::ResetMatrixProjection();
    //Graphics::Ortho2D(0, gDeviceWidth, gDeviceHeight, 0); //, -4096.0f, 4096.0f);

    FMatrix aProj = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -1024.0f, 1024.0f);
    Graphics::SetMatrix(aProj);



    for (int i=0;i<4;i++) {

        Graphics::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
        Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 20.0f);
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 14.0f);
    }

    Graphics::SetColor(0.0f, 0.0f, 1.0f, 0.85f);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0],
                       mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1], 12.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1],
                       mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2], 12.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2],
                       mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3], 12.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3],
                       mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0], 12.0);
}

void CNVGame::TouchDown(float pX, float pY, void *pData) {
    
}

void CNVGame::TouchMove(float pX, float pY, void *pData) {
    
}

void CNVGame::TouchUp(float pX, float pY, void *pData) {
    
}

void CNVGame::TouchFlush() {
    
}



