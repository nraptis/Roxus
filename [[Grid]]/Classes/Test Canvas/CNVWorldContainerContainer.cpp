//
//  CNVWorldContainerContainerContainer.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/17/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "CNVWorldContainerContainer.hpp"
#include "GLApp.h"
#include "CNVWorld.hpp"

CNVWorldContainerContainer::CNVWorldContainerContainer() {
    mSpriteRotation = gRand.Get(360);
    
    mWorldContainer = 0;
    
    mTouchMarkerColor1 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    mTouchMarkerColor2 = FColor(gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat(), gRand.GetFloat());
    
    mWorldContainer = new CNVWorldContainer();
    AddChild(mWorldContainer);
    
    mName = "CNVWorldContainer+Container [OUTER]";
    
}

CNVWorldContainerContainer::~CNVWorldContainerContainer() {
    Log("Free(CNVWorldContainerContainer)\n");
}

void CNVWorldContainerContainer::Layout() {
    
    Log("---Layout(CNVWorldContainerContainer_\n");

    SetFrame(20.0f, 20.0f, gAppWidth - 40.0f, gAppHeight - 40.0f);

    if (mWorldContainer) {
        float aWidth = 1536.0f;
        float aHeight = 1536.0f;

        if (mWorldContainer->mWorld1) {
            aWidth = mWorldContainer->mWorld1->GetWidth();
            aHeight = mWorldContainer->mWorld1->GetHeight();
        }

        if (aWidth > 10.0 && aHeight > 10.0 && mWidth > 10.0 && mHeight > 10.0) {
            
            FRect aBounds = FRect(0.0f, 0.0f, mWidth, mHeight);

            float aScale = 1.0f;
            FRect aFit = FRect::FitAspectFit(aBounds, aHeight, aWidth, 5.0f, aScale);

            mWorldContainer->SetTransformScale(aScale);
            mWorldContainer->SetTransformX(aFit.mX);
            mWorldContainer->SetTransformY(aFit.mY);

            if (gRand.GetBool()) {
                //mWorldContainer->SetTransformRotation(-14.0f);
            } else {
                //mWorldContainer->SetTransformRotation(0.0f);
            }
        }
    }
}

void CNVWorldContainerContainer::Update() {
    mSpriteRotation += 2.0;
    if (mSpriteRotation >= 360.0f) mSpriteRotation -= 360.0f;
    
}

void CNVWorldContainerContainer::Draw() {
    FCanvas::Draw();
    
    
    float aWidth = gApp->mTessPattern.mWidth;
    float aHeight = gApp->mTessPattern.mHeight;

    Graphics::BlendSetAdditive();
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.25f);
    gApp->mSillyMeme.DrawQuadRect(0.0f, 0.0f, GetWidth(), GetHeight());

    Graphics::BlendSetAlpha();


    /*
    if(aWidth > 10.0f && aHeight > 10.0f) {
        for (float aX=0;aX<=mWidth;aX+=aWidth) {
            for (float aY=0;aY<=mHeight;aY+=aHeight) {
                gApp->mTessPattern.Draw(aX, aY);
            }
        }
    }
    */
    
    Graphics::SetColor();
    
    if (mTouchX > 0.0f || mTouchY >= 0.0f) {
        Graphics::SetColor(mTouchMarkerColor1);
        Graphics::DrawPoint(mTouchX, mTouchY, 14.0f);
        Graphics::SetColor(mTouchMarkerColor2);
        Graphics::DrawPoint(mTouchX, mTouchY, 10.0f);
    }
    

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

    Graphics::SetColor(1.0f, 0.85f, 0.75f, 0.75f);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0],
                       mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1], 6.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[1],
                       mTransformAbsolute.mCornerY[1],
                       mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2], 6.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[2],
                       mTransformAbsolute.mCornerY[2],
                       mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3], 6.0);

    Graphics::DrawLine(mTransformAbsolute.mCornerX[3],
                       mTransformAbsolute.mCornerY[3],
                       mTransformAbsolute.mCornerX[0],
                       mTransformAbsolute.mCornerY[0], 6.0);

}

void CNVWorldContainerContainer::TouchDown(float pX, float pY, void *pData) {
    
}

void CNVWorldContainerContainer::TouchMove(float pX, float pY, void *pData) {
    
}

void CNVWorldContainerContainer::TouchUp(float pX, float pY, void *pData) {
    
}

void CNVWorldContainerContainer::TouchFlush() {
    
}


