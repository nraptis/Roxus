//
//  GLApp.cpp
//  OptimizeRX
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "core_app_shell.h"
#include "GLApp.h"
#include "Util_ScreenFrame.h"
#include "FCanvas.hpp"
#include "CNVWorldContainerContainer.hpp"
#include "PGMainCanvas.hpp"

GLApp *gApp = 0;
GLApp::GLApp() {
    gApp = this;
    
    mCanvasContainer = 0;

    mSpawnNewWorldTimer = 0;

    mFont1ScaleSin = 30.0f;
    mFont2ScaleSin = 30.0f + 180.0f;
    
    mLine1Point1 = FPoint(100, 100);
    mLine1Point2 = FPoint(200, 320);
    
    mLine2Point1 = FPoint(220, 100);
    mLine2Point2 = FPoint(120, 440);
    
    mSelectedPoint = 0;

    mAnimationSide = false;
}

GLApp::~GLApp() {
    
}

void GLApp::Update() {

    mFont1ScaleSin += 1.0f;
    if ( mFont1ScaleSin > 360.0f ) { mFont1ScaleSin -= 360.0f; }

    mFont2ScaleSin += 1.0f;
    if ( mFont2ScaleSin > 360.0f ) { mFont2ScaleSin -= 360.0f; }

    if (mSpawnNewWorldTimer > 0) {
        mSpawnNewWorldTimer -= 1;
        if (mSpawnNewWorldTimer == 0) {
            //mCanvasContainer = new CNVWorldContainerContainer();
            //mWindowMain.AddChild(mCanvasContainer);
            //mCanvasContainer->SetTransformAnchor(0.5f, 0.5f);

            mAnimation.mCanvas = 0;
        }
    }

    mAnimation.Update();

}

void GLApp::Draw() {

    FDrawQuad aQuad;
    aQuad.SetColorBottom(0.84f, 0.86f, 0.92f);
    aQuad.SetColorTop(0.92f, 0.93f, 0.96f);
    aQuad.SetRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    aQuad.Draw();

    aQuad.SetColorLeft(0.64f, 0.46f, 0.78f, 0.08f);
    aQuad.SetColorRight(0.72f, 0.66f, 1.0f, 0.7f);
    //aQuad.SetRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    aQuad.Draw();

    
    //Graphics::Clear(0.88f, 0.88f, 0.92f);
    Graphics::Clear(0.125f, 0.125f, 0.133f);


    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.6);
    
    for (float aX = 0.0f;aX < gAppWidth;aX += 10.0) {
        for (float aY = 0.0f;aY < gAppHeight;aY += 10.0) {
            Graphics::DrawPoint(aX, aY, 2.0);
        }
    }


    Graphics::SetColor(1.0, 1.0, 1.0);
    
    Graphics::DrawLine(mLine1Point1, mLine1Point2);
    Graphics::DrawLine(mLine2Point1, mLine2Point2);
    
    Graphics::SetColor(1.0, 0.0, 0.0);
    Graphics::DrawPoint(mLine1Point1.mX, mLine1Point1.mY, 6.0f);
    Graphics::DrawPoint(mLine1Point2.mX, mLine1Point2.mY, 6.0f);
    
    Graphics::SetColor(0.0, 1.0, 0.0);
    Graphics::DrawPoint(mLine2Point1.mX, mLine2Point1.mY, 6.0f);
    Graphics::DrawPoint(mLine2Point2.mX, mLine2Point2.mY, 6.0f);
    
    
    FPoint aCollide;
    if (SegmentSegmentIntersection(mLine1Point1, mLine1Point2, mLine2Point1, mLine2Point2, &aCollide)) {
        
        Graphics::SetColor(0.7, 0.6, 0.8);
        Graphics::DrawPoint(aCollide.mX, aCollide.mY, 10.0f);
        
        Graphics::SetColor(0.25, 0.25, 0.25);
        Graphics::DrawPoint(aCollide.mX, aCollide.mY, 6.0f);
    }




    /*
    Graphics::SetColor();
    gApp->mSysFont.Draw("Here is some sample TEXT 1234", 20.0f, 200.0f);
    Graphics::SetColor(0.6f, 0.1f, 0.1f, 0.6f);
    Graphics::DrawRect(20.0f, 200.0f, 500.0f, 2.0f);

    Graphics::SetColor();
    gApp->mSysFontBold.Draw("SAMPLE bold TEXT", 20.0f, 250.0f);
    Graphics::SetColor(0.1f, 0.6f, 0.1f, 0.6f);
    Graphics::DrawRect(20.0f, 250.0f, 500.0f, 2.0f);



    float aScale1 = Sin(mFont1ScaleSin) * 0.5f + 1.0f;
    float aScale2 = Sin(mFont2ScaleSin) * 0.5f + 1.0f;


    Graphics::SetColor();
    gApp->mSysFontBold.Center("+-(Centered)]][] B#0l.<>D Text", gAppWidth2, gAppHeight2, aScale1);
    Graphics::SetColor(0.6f, 0.1f, 0.1f, 0.6f);
    Graphics::DrawRect(0.0f, gAppHeight2 - 1.0f, 2000.0f, 2.0f);


    Graphics::SetColor();
    gApp->mSysFontBold.Center("[(Centered)] l2eGuL@r%% Text", gAppWidth2, gAppHeight2 + gAppHeight2 / 2.0f, aScale2);
    Graphics::SetColor(0.6f, 0.1f, 0.1f, 0.6f);
    Graphics::DrawRect(0.0f, gAppHeight2 + gAppHeight2 / 2.0f - 1.0f, 2000.0f, 2.0f);
    */


    /*
    Graphics::SetColor();
    gApp->mSysFont.Draw("Here is some sample TEXT 1234", 20.0f, 300.0f, 2.0);
    Graphics::SetColor(0.6f, 0.1f, 0.1f, 0.6f);
    Graphics::DrawRect(20.0f, 300.0f, 500.0f, 2.0f);
    
    Graphics::SetColor();
    gApp->mSysFontBold.Draw("Sample BOLD TExt#@$%%!!+-", 20.0f, 350.0f, 2.0f);
    Graphics::SetColor(0.1f, 0.6f, 0.1f, 0.6f);
    Graphics::DrawRect(20.0f, 350.0f, 500.0f, 2.0f);
    */


    /*
    Graphics::Go3D();
    
    
    Graphics::MatrixPerspective();
    Graphics::MatrixPush();
    
    
    Graphics::MatrixLookAt(-200.0f, 100.0f, 220.0f, 0.0f, 0.0f, 0.0f, 0, 0, -1.0f);
    Graphics::SetColor(1.0, 0.0f, 0.0f, 1.0f);
    Graphics::DrawSphere12(100.0f, 100.0f, 30.0f, 140.0f);
    
    Graphics::MatrixPop();
    Graphics::Go2D();
    */

}

bool IsBetween(float pValue, float pStart, float pEnd) {
    if (pStart < pEnd) {
        return (pValue >= pStart) && (pValue <= pEnd);
    } else {
        return (pValue >= pEnd) && (pValue <= pStart);
    }
}

bool GLApp::SegmentSegmentIntersection(FPoint l1p1, FPoint l1p2, FPoint l2p1, FPoint l2p2, FPoint *intersection) {
    float x1 = l1p1.mX, x2 = l1p2.mX, x3 = l2p1.mX, x4 = l2p2.mX;
    float y1 = l1p1.mY, y2 = l1p2.mY, y3 = l2p1.mY, y4 = l2p2.mY;
    
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return NULL;
    
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
    
    // Check if the x and y coordinates are within both lines
    if ( x < min(x1, x2) || x > max(x1, x2) ||
        x < min(x3, x4) || x > max(x3, x4) ) {
        return NULL;
    }
    if ( y < min(y1, y2) || y > max(y1, y2) ||
        y < min(y3, y4) || y > max(y3, y4) ) {
        return NULL;
    }

    intersection->mX = x;
    intersection->mY = y;
    
    return true;
    
    /*
    float aLine1DiffX = l1p2.mX - l1p1.mX;
    float aLine2DiffX = l2p2.mX - l2p1.mX;
    
    float aLine1DiffY = l1p2.mY - l1p1.mY;
    float aLine2DiffY = l2p2.mY - l2p1.mY;
    
    if (fabsf(aLine1DiffX) > SQRT_EPSILON && fabsf(aLine2DiffX) > SQRT_EPSILON) {
        
        //y = mx + b
        //y - b = mx
        //b = mx - y
        //x = (b - y) / m
        float aSlope1 = aLine1DiffY / aLine1DiffX;
        float aSlope2 = aLine2DiffY / aLine2DiffX;
        
        float aOffset1 = aSlope1 * l1p1.mX - l1p1.mY;
        float aOffset2 = aSlope2 * l2p1.mX - l2p1.mY;
        
        if (fabsf(aSlope1 - aSlope2) > SQRT_EPSILON) {
            
            
            //m1 * x + b1 = m2 * x + b2
            //m1 * x - m2 * x = (b2 - b1)
            //x * (m1 - m2) = (b2 - b1)
            
            
            float aHitX = (aOffset2 - aOffset1) / (aSlope1 - aSlope2);
            float aHitY = aSlope1 * aHitX + aOffset1;
            //float aHitX = (aOffset1 - aHitX) / aSlope1;
            
            printf("Collide: %f %f  Slope1 = %f  Slope2 = %f   B1 = %f   B2 = %f\n", aHitX, aHitY, aSlope1, aSlope2, aOffset1, aOffset2);
     
            intersection->mX = aHitX;
            intersection->mY = aHitY;
     
            return true;
        }
    }
    */


    return false;
}

void GLApp::Load() {
    mBackground.Load("1024x1024");
    mTestSprite.Load("widge");
    mTessPattern.Load("tess_1");
    mDarkTile.Load("tile_metal_7_buried_1.png");
    mBackgroundLarge.Load("2048x2048.BMP");
    
    mWallLeft.Load("wall_loop_left_1.gif");
    mWallRight.Load("wall_loop_right_1.png");
    
    mSillyMeme.Load("trap.jpg");

    mTest_800x600_1.Load("800x600_1");
    mTest_800x600_2.Load("800x600_2");
    mTest_Small_1.Load("sunny_field");

    mInterfaceBottom.Load("game_interface_bottom_back_colored");
    mInterfaceBottomGray.Load("game_interface_bottom_back_grey");

    mSequenceSquare.Load("effect_hilight_square_");
    mParticleStream.Load("particle_stream_");

    mSequencePlasmaBolt.Load("plasma_bolt_");
    mSequencePlasmaBoltGlow.Load("plasma_bolt_glow_");
    
    mSequenceSmokePuff.Load("smoke_puff_b_fast_");
    mSequenceTwinkle.Load("effect_twinkle_accent_loop_");
    mSequenceSparkBlast.Load("effect_sparkblast_");

    mTile1.Load("tile_back_1");
    mTile2.Load("tile_back_2");
    mTile3.Load("tile_back_3");
    mTile4.Load("tile_back_4");

    mInterfaceBottom.Load("game_interface_bottom_back_colored");
}

void GLApp::SetVirtualFrame(float pX, float pY, float pWidth, float pHeight) {

}

void GLApp::TouchDown(float pX, float pY, void *pData) {
    mSound.Play();
    UpdateRot(pX);
    
    mSelectedPoint = NULL;
    
    float aBestDist = 60.0f;
    
    FPoint aPoint = FPoint(pX, pY);
    
    float aDist = Distance(aPoint, mLine1Point1);
    if (aDist < aBestDist) {
        aBestDist = aDist;
        mSelectedPoint = &mLine1Point1;
        mSelectedPointStart = mLine1Point1;
    }
    
    aDist = Distance(aPoint, mLine1Point2);
    if (aDist < aBestDist) {
        aBestDist = aDist;
        mSelectedPoint = &mLine1Point2;
        mSelectedPointStart = mLine1Point2;
    }

    aDist = Distance(aPoint, mLine2Point1);
    if (aDist < aBestDist) {
        aBestDist = aDist;
        mSelectedPoint = &mLine2Point1;
        mSelectedPointStart = mLine2Point1;
    }
    
    aDist = Distance(aPoint, mLine2Point2);
    if (aDist < aBestDist) {
        aBestDist = aDist;
        mSelectedPoint = &mLine2Point2;
        mSelectedPointStart = mLine2Point2;
    }
    
    mSelectedTouchStart = aPoint;
    if (mCanvasContainer) {
        mAnimation.SetUp(mCanvasContainer);
        mAnimationSide = !mAnimationSide;
        if (mAnimationSide) {
            mAnimation.mTargetAnchorX=1.0f;
            mAnimation.mTargetAnchorY=1.0f;
            mAnimation.mTargetX=0.0f;
            mAnimation.mTargetY= 0.0f;
            mAnimation.mTargetRotation = 22.0f;
        } else {
            mAnimation.mTargetAnchorX=0.0f;
            mAnimation.mTargetAnchorY=1.0f;
            mAnimation.mTargetX = 0.0f;
            mAnimation.mTargetY = 0.0f;
            mAnimation.mTargetRotation = -22.0f;
        }
        mAnimation.Generate(ANIMATION_TYPE_OVERSHOOT, 200);
    }
}

void GLApp::TouchMove(float pX, float pY, void *pData) {
    UpdateRot(pX);
    if (mSelectedPoint != NULL) {
        float aDiffX = mSelectedTouchStart.mX - pX;
        float aDiffY = mSelectedTouchStart.mY - pY;
        mSelectedPoint->mX = mSelectedPointStart.mX - aDiffX;
        mSelectedPoint->mY = mSelectedPointStart.mY - aDiffY;
        int aX = mSelectedPoint->mX;
        int aModX = aX % 10;
        aX -= aModX;
        if (aModX >= 5) { aX += 10; }
        int aY = mSelectedPoint->mY;
        int aModY = aY % 10;
        aY -= aModY;
        if (aModY >= 5) { aY += 10; }
        mSelectedPoint->mX = aX;
        mSelectedPoint->mY = aY;
    }
}

void GLApp::UpdateRot(float pX) {
    
}

void GLApp::TouchUp(float pX, float pY, void *pData) {
    mSelectedPoint = NULL;
}

void GLApp::TouchFlush() {
    
}

void GLApp::MouseWheel(int pDirection) {

}

void GLApp::KeyDown(int pKey) {
    mWindowMain.RegisterRealize(&mWindowMain.mRoot);
    if (mCanvasContainer) {
        mCanvasContainer->Kill();
        mCanvasContainer = 0;
    }
    mSpawnNewWorldTimer = 20 + gRand.Get(20);
}

void GLApp::KeyUp(int pKey) {

}

void GLApp::SetDeviceSize(float pWidth, float pHeight) {
    FApp::SetDeviceSize(pWidth, pHeight);
}

void GLApp::LoadComplete() {

    //mCanvasContainer = new CNVWorldContainerContainer();
    //mWindowMain.AddChild(mCanvasContainer);
    //mCanvasContainer->SetTransformAnchor(0.25f, 0.5f);

    PGMainCanvas *aPlayground = new PGMainCanvas();
    mWindowTools.AddChild(aPlayground);

    //Util_ScreenFrame *aScreenFrameUtil = new Util_ScreenFrame();
    //mWindowTools.AddChild(aScreenFrameUtil);
    
}

