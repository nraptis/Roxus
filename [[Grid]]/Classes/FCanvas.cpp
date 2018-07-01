//
//  FCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "FCanvas.hpp"

FCanvas::FCanvas() {
    mX = 0.0f;
    mY = 0.0f;
    mWidth = 256.0f;
    mHeight = 256.0f;
    mWidth2 = 128.0;
    mHeight2 = 128.0;
    mKill = 0;
    mClipsContent = false;
    mDidUpdate = false;
    mConsumesTouches = true;
    mRecievesOutsideTouches = false;
    mRecievesConsumedTouches = false;
    mEnabled = true;
    mHidden = false;
    mDrawManual = false;
    mTouchDownInside = false;
    mMouseOver = false;
    mTouchDown = false;
    mDeleteWhenParentIsDeleted = true;
    mTouchCount = 0;
    mParent = 0;
    mColor.mRed = 1.0f;
    mColor.mGreen = 1.0f;
    mColor.mBlue = 1.0f;
    mColor.mAlpha = 0.0f;
    mTouchX = 0.0f;
    mTouchY = 0.0f;
    mWindow = 0;
}

FCanvas::~FCanvas() {
    if (mWindow) {
        FWindow *aWindow = mWindow;
        mWindow = 0;
        aWindow->RegisterDealloc(this);
    }
}

void FCanvas::Kill() {
    mKill = 10;
    if (mWindow) {
        mWindow->RegisterKill(this);
    } else {
        Log("\nKilling View Without Window?\n[%s]\n", mName.c());
        exit(0);
    }
}

void FCanvas::Layout() { printf("----Layout(%s)\n", mName.c()); }
void FCanvas::Update() { }
void FCanvas::Draw() {
    if (mColor.mAlpha != 0.0f) {
        Graphics::SetColor(mColor);
        Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
        Graphics::SetColor();
    }
}
void FCanvas::MouseDown(float pX, float pY, int pButton) { }
void FCanvas::MouseMove(float pX, float pY) { }
void FCanvas::MouseUp(float pX, float pY, int pButton) { }
void FCanvas::MouseWheel(int pDirection) { }
void FCanvas::TouchDown(float pX, float pY, void *pData) { }
void FCanvas::TouchMove(float pX, float pY, void *pData) { }
void FCanvas::TouchUp(float pX, float pY, void *pData) { }
void FCanvas::TouchFlush() { }
void FCanvas::KeyDown(int pKey) { }
void FCanvas::KeyUp(int pKey) { }



void FCanvas::DrawManual() {
    if (mDidUpdate == true && mHidden == false && mKill == 0) {
        DrawTransform();
        if (mClipsContent) {
            Graphics::ClipEnable();
            Graphics::Clip(0.0f, 0.0f, mWidth, mHeight);
        }
        Draw();
        EnumList(FCanvas, aCanvas, mChildren) { aCanvas->DrawManual(); }
        if (mClipsContent) { Graphics::ClipDisable(); }
    }
}

void FCanvas::DrawTransform() {
    FMatrix aOrtho = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -2048.0f, 2048.0f);
    Graphics::SetMatrixProjection(aOrtho);
    float aX = mTransformAbsolute.mX;
    float aY = mTransformAbsolute.mY;
    if (aX != 0.0f || aY != 0.0f) {
        Graphics::Translate(aX, aY, 0.0f);
    }
    float aRotation = mTransformAbsolute.mRotation;
    if (aRotation != 0.0f) {
        Graphics::Rotate(aRotation);
    }
    float aScaleX = mTransformAbsolute.mScale * mTransformAbsolute.mScaleX;
    float aScaleY = mTransformAbsolute.mScale * mTransformAbsolute.mScaleY;
    float aScale = mTransformAbsolute.mScale;
    if (aScaleX != 1.0f || aScaleY != 1.0f || aScale != 1.0f) {
        Graphics::Scale(aScaleX, aScaleY, aScale);
    }
    float aAnchorX = mTransformAbsolute.mAnchorX;
    float aAnchorY = mTransformAbsolute.mAnchorY;
    if ((aAnchorX != 0.0f) || (aAnchorY != 0.0f)) {
        Graphics::Translate(aAnchorX * (-mWidth), aAnchorY * (-mHeight));
    }
    Graphics::ResetMatrixModelView();
}

void FCanvas::AddChild(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    pCanvas->mParent = this;
    pCanvas->mWindow = mWindow;
    mChildren.Add(pCanvas);
    if (mWindow) {
        mWindow->RegisterRealize(pCanvas);
        mWindow->RegisterChildrenDidUpdate(this);
    }
}

void FCanvas::AddChild(FCanvas &pCanvas) {
    pCanvas.mDeleteWhenParentIsDeleted = false;
    AddChild(&pCanvas);
}

void FCanvas::BringChildToFront(FCanvas *pCanvas) {
    mChildren.MoveToLast(pCanvas);
    if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
}

void FCanvas::SendChildToBack(FCanvas *pCanvas) {
    mChildren.MoveToFirst(pCanvas);
    if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
}

void FCanvas::SendChildBackward(FCanvas *pCanvas) {
    mChildren.MoveObjectUp(pCanvas);
    if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
}

void FCanvas::BringChildForward(FCanvas *pCanvas) {
    mChildren.MoveObjectDown(pCanvas);
    if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
}

void FCanvas::PrintTransform() {
    Log(mName.c());

    Log("\nTRA");

    //Log(mName.c());

    Log(" - XY[%.2f %.2f] Sc[%.2f %.2f %.2f] R[%.2f] - Fr[%.2f,%.2f,%.2f,%.2f]\n", mTransform.mX, mTransform.mY, mTransform.mScale, mTransform.mScaleX, mTransform.mScaleY, mTransform.mRotation, mX, mY, mWidth, mHeight);

    Log("ABS - XY[%.2f %.2f] Sc[%.2f %.2f %.2f] R[%.3f]\n\n", mTransformAbsolute.mX, mTransformAbsolute.mY, mTransformAbsolute.mScale, mTransformAbsolute.mScaleX, mTransformAbsolute.mScaleY, mTransformAbsolute.mRotation);

    Log("Corners - 1[%.2f %.2f] 2[%.2f %.2f] 3[%.2f %.2f] 4[%.2f %.2f]\n\n",

        mTransformAbsolute.mCornerX[0],
        mTransformAbsolute.mCornerY[0],
        mTransformAbsolute.mCornerX[1],
        mTransformAbsolute.mCornerY[1],
        mTransformAbsolute.mCornerX[2],
        mTransformAbsolute.mCornerY[2],
        mTransformAbsolute.mCornerX[3],
        mTransformAbsolute.mCornerY[3]);



    Log("---\n");

    EnumList(FCanvas, aCanvas, mChildren) {
        aCanvas->PrintTransform();
    }

}

void FCanvas::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    SetX(pX);
    SetY(pY);
    SetWidth(pWidth);
    SetHeight(pHeight);
}

void FCanvas::SetX(float pX) {
    float aDifference = mX - pX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mX = pX;
        FrameDidUpdate();
    }
}

void FCanvas::SetY(float pY) {
    float aDifference = mY - pY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mY = pY;
        FrameDidUpdate();
    }
}

void FCanvas::SetWidth(float pWidth) {
    float aDifference = mWidth - pWidth;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mWidth = pWidth;
        mWidth2 = mWidth * 0.5f;
        FrameDidUpdate();
    }
}

void FCanvas::SetHeight(float pHeight) {
    float aDifference = mHeight - pHeight;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mHeight = pHeight;
        mHeight2 = mHeight * 0.5f;
        FrameDidUpdate();
    }
}

void FCanvas::SetTransformTranslate(float pX, float pY) {
    SetTransformX(pX);
    SetTransformY(pY);
}

void FCanvas::SetTransformX(float pX) {
    float aDifference = mTransform.mX - pX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mX = pX;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformY(float pY) {
    float aDifference = mTransform.mY - pY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mY = pY;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformScale(float pScale) {
    float aDifference = mTransform.mScale - pScale;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mScale = pScale;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformScale(float pScaleX, float pScaleY) {
    SetTransformScaleX(pScaleX);
    SetTransformScaleY(pScaleY);
}

void FCanvas::SetTransformScaleX(float pScaleX) {
    float aDifference = mTransform.mScaleX - pScaleX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mScaleX = pScaleX;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformScaleY(float pScaleY) {
    float aDifference = mTransform.mScaleY - pScaleY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mScaleY = pScaleY;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformRotation(float pRotation) {
    float aDifference = mTransform.mRotation - pRotation;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mRotation = pRotation;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformAnchor(float pAnchorX, float pAnchorY) {
    SetTransformAnchorX(pAnchorX);
    SetTransformAnchorY(pAnchorY);
}

void FCanvas::SetTransformAnchorX(float pAnchorX) {
    float aDifference = mTransform.mAnchorX - pAnchorX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mAnchorX = pAnchorX;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformAnchorY(float pAnchorY) {
    float aDifference = mTransform.mAnchorY - pAnchorY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mAnchorY = pAnchorY;
        TransformDidUpdate();
    }
}

void FCanvas::PrintFrame() {
    
}

void FCanvas::PrintAllChildrenTransforms() {

}

void FCanvas::ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    if (pFromCanvas) {
        pFromCanvas->mTransformAbsolute.Untransform(pX, pY, pFromCanvas->mWidth, pFromCanvas->mHeight);
    }
    if (pToCanvas) {
        pToCanvas->mTransformAbsolute.Transform(pX, pY, pToCanvas->mWidth, pToCanvas->mHeight);
    }
}

FPoint FCanvas::Convert(float pX, float pY, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    FPoint aResult;
    aResult.mX = pX; aResult.mY = pY;
    ConvertPoint(aResult.mX, aResult.mY, pFromCanvas, pToCanvas);
    return aResult;
}

float FCanvas::ConvertScale(float pScale, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    return 0.0f;
}

float FCanvas::ConvertRotation(float pDegrees, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    return 0.0f;
}

void FCanvas::DrawManualBegin() { }
void FCanvas::DrawManualEnd() { }
void FCanvas::DrawChildrenManual() { }

void FCanvas::TransformDidUpdate() {
    if (mWindow) {
        mWindow->RegisterTransformDidUpdate(this);
    }
}

void FCanvas::FrameDidUpdate() {
    if (mWindow) {
        mWindow->RegisterFrameDidUpdate(this);
    }
}

void FCanvas::ComputeAbsoluteTransformation() {
    if (mParent) {
        mTransformAbsolute.ApplyAbsoluteTransformation(&mParent->mTransformAbsolute, mParent->mX, mParent->mY, mParent->mWidth, mParent->mHeight, &mTransform, mX, mY, mWidth, mHeight);
    } else {
        mTransformAbsolute.ApplyAbsoluteTransformation(&mTransform, mX, mY, mWidth, mHeight);
    }
    EnumList(FCanvas, aCanvas, mChildren) {
        aCanvas->ComputeAbsoluteTransformation();
    }
}

void FCanvas::BaseLayout() { Layout(); }
void FCanvas::BaseUpdate() {
    mDidUpdate=true;
    Update();
    EnumList(FCanvas, aCanvas, mChildren) { aCanvas->BaseUpdate(); }
}

void FCanvas::BaseDraw() {
    if (mDidUpdate == true && mDrawManual == false && mHidden == false && mKill == 0) {
        DrawTransform();
        if (mClipsContent) {
            Graphics::ClipEnable();
            Graphics::Clip(0.0f, 0.0f, mWidth, mHeight);
        } else {
            Graphics::ClipDisable();
        }
        Draw();
        EnumList(FCanvas, aCanvas, mChildren) { aCanvas->BaseDraw(); }
        if (mClipsContent) { Graphics::ClipDisable(); }



        /*
        if (mTouchDownInside) {
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

        Graphics::SetColor(0.75f, 0.65f, 0.125f, 0.90f);

        Graphics::DrawLine(mTransformAbsolute.mCornerX[0],
                           mTransformAbsolute.mCornerY[0],
                           mTransformAbsolute.mCornerX[1],
                           mTransformAbsolute.mCornerY[1], 5.0);

        Graphics::DrawLine(mTransformAbsolute.mCornerX[1],
                           mTransformAbsolute.mCornerY[1],
                           mTransformAbsolute.mCornerX[2],
                           mTransformAbsolute.mCornerY[2], 5.0);

        Graphics::DrawLine(mTransformAbsolute.mCornerX[2],
                           mTransformAbsolute.mCornerY[2],
                           mTransformAbsolute.mCornerX[3],
                           mTransformAbsolute.mCornerY[3], 5.0);

        Graphics::DrawLine(mTransformAbsolute.mCornerX[3],
                           mTransformAbsolute.mCornerY[3],
                           mTransformAbsolute.mCornerX[0],
                           mTransformAbsolute.mCornerY[0], 5.0);



        }
        */
    }
}
void FCanvas::BaseMouseDown(float pX, float pY, float pOriginalX, float pOriginalY, int pButton) { mTouchX = pX; mTouchY = pY; MouseDown(pX, pY, pButton); }
void FCanvas::BaseMouseMove(float pX, float pY, float pOriginalX, float pOriginalY) { mTouchX = pX;mTouchY = pY;MouseMove(pX, pY); }
void FCanvas::BaseMouseUp(float pX, float pY, float pOriginalX, float pOriginalY, int pButton) { mTouchX = pX; mTouchY = pY; MouseUp(pX, pY, pButton); }
void FCanvas::BaseMouseWheel(int pDirection) { MouseWheel(pDirection); }

FCanvas *FCanvas::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed) {
    //mTouchX = pX; mTouchY = pY; TouchDown(pX, pY, pData);

    FCanvas *aResult = 0;
    FCanvas *aCollider = 0;

    if (mKill == 0 && mEnabled == true) {
        bool aContainsTouch = false;
        if ((pConsumed == true) && (mRecievesConsumedTouches == false)) {
            aContainsTouch = false;
        } else {
            if (pOutsideParent) {
                aContainsTouch = false;
            } else {
                aContainsTouch = mTransformAbsolute.ContainsPoint(pX, pY);
                if (aContainsTouch == false) {
                    pOutsideParent = true;
                }
            }
        }
        EnumListReverse(FCanvas, aChild, mChildren) {
            aCollider = aChild->BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent, pConsumed);
            if (aCollider) {
                if (aCollider->mConsumesTouches) {
                    pConsumed = true;
                    if(aResult == 0) {
                        aResult = aCollider;
                    }
                    if ((mRecievesOutsideTouches == false) && (mRecievesConsumedTouches == false)) {
                        aContainsTouch = false;
                    }
                }
            }
        }

        if ((mRecievesConsumedTouches == true) || (pConsumed == false)) {
            if ((aContainsTouch == true) || (mRecievesOutsideTouches == true)) {
                mTouchDown = true;
                if (mTouchCount < VIEW_MAX_TOUCH_COUNT) {
                    mTouchData[mTouchCount] = pData;
                    if (aContainsTouch == true) {
                        if (aResult == 0) {
                            aResult = this;
                        }
                        mTouchInside[mTouchCount] = true;
                        mTouchDownInside = true;
                    } else {
                        mTouchInside[mTouchCount] = false;
                        mTouchDown = true;
                        bool aAnyTouchesInside = false;
                        for (int i=0;i<mTouchCount;i++) {
                            if(mTouchInside[i] == true)aAnyTouchesInside = true;
                        }
                        mTouchDownInside = aAnyTouchesInside;
                    }

                    mTouchCount++;

                    mTouchX = pX;
                    mTouchY = pY;
                    mTransformAbsolute.Transform(mTouchX, mTouchY, mWidth, mHeight);
                    mTouchDown = true;
                    TouchDown(mTouchX, mTouchY, pData);
                }
            }
        }
    } else {
        BaseTouchFlush();
    }
    return aResult;
}

void FCanvas::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    if (mKill == 0 && mEnabled == true) {
        int aTouchIndex = -1;
        for (int i=0;i<mTouchCount;i++) {
            if (mTouchData[i] == pData) {
                aTouchIndex = i;
            }
        }
        bool aContainsTouch = false;
        if (pOutsideParent) {
            aContainsTouch = false;
        } else {
            aContainsTouch = mTransformAbsolute.ContainsPoint(pX, pY);
            if (aContainsTouch == false) {
                pOutsideParent = true;
            }
        }
        EnumListReverse (FCanvas, aChild, mChildren) {
            aChild->BaseTouchMove(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
        }
        if (aTouchIndex >= 0) {
            if (aContainsTouch) {
                mTouchInside[aTouchIndex] = true;
                mTouchDownInside = true;
            } else {
                mTouchInside[aTouchIndex] = false;
                bool aAnyTouchesInside = false;
                for (int i=0;i<mTouchCount;i++) {
                    if(mTouchInside[i] == true) { aAnyTouchesInside = true; }
                }
                mTouchDownInside = aAnyTouchesInside;
            }
            mTouchX = pX;
            mTouchY = pY;
            mTransformAbsolute.Transform(mTouchX, mTouchY, mWidth, mHeight);
            TouchMove(mTouchX, mTouchY, pData);
        }
    } else {
        BaseTouchFlush();
    }
}

void FCanvas::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    int aTouchIndex = -1;
    for (int i=0;i<mTouchCount;i++) {
        if (mTouchData[i] == pData) {
            aTouchIndex = i;
        }
    }
    if (aTouchIndex >= 0) {
        for (int i=aTouchIndex;i<(mTouchCount - 1);i++) {
            mTouchData[i] = mTouchData[i + 1];
            mTouchInside[i] = mTouchInside[i + 1];
        }
        mTouchCount--;
    }
    if (mKill == 0 && mEnabled == true) {
        bool aContainsTouch = false;
        if (pOutsideParent) {
            aContainsTouch = false;
        } else {
            aContainsTouch = mTransformAbsolute.ContainsPoint(pX, pY);
            if (aContainsTouch == false) {
                pOutsideParent = true;
            }
        }
        EnumListReverse (FCanvas, aChild, mChildren) {
            aChild->BaseTouchUp(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
        }
        if (mTouchCount <= 0) {
            mTouchDown = false;
            mTouchDownInside = false;
        } else {
            bool aAnyTouchesInside = false;
            for (int i=0;i<mTouchCount;i++) {
                if (mTouchInside[i] == true) { aAnyTouchesInside = true; }
            }
            mTouchDownInside = aAnyTouchesInside;
        }

        if(aTouchIndex >= 0) {
            mTouchX = pX;
            mTouchY = pY;
            mTransformAbsolute.Transform(mTouchX, mTouchY, mWidth, mHeight);
            TouchUp(mTouchX, mTouchY, pData);
        }
    } else {
        BaseTouchFlush();
    }
}

void FCanvas::BaseTouchFlush() {
    mTouchDown = false;
    mTouchDownInside = false;
    mTouchCount = 0;
    mMouseOver = false;
    TouchFlush();
    EnumList(FCanvas, aChild, mChildren) {
        aChild->BaseTouchFlush();
    }
}
void FCanvas::BaseKeyDown(int pKey) {
    KeyDown(pKey);
    EnumList(FCanvas, aChild, mChildren) {
        aChild->BaseKeyDown(pKey);
    }
}
void FCanvas::BaseKeyUp(int pKey) {
    KeyUp(pKey);
    EnumList(FCanvas, aChild, mChildren) {
        aChild->BaseKeyUp(pKey);
    }
}

/*



void FViewContainer::TouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent)
{

}

void FViewContainer::TouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent)
{


}

void FViewContainer::TouchFlush()
{
    for(int i = 0; i < mView->mSubviews.mCount; i++)
    {
        FViewContainer *aCtr = ((FView *)(mView->mSubviews.Fetch(i)))->GetContainer();

        aCtr->TouchFlush();
    }

    if(mView)
    {
        mView->mTouchDown = false;
        mView->mTouchDownInside = false;
        mView->mTouchCount = 0;
        mView->mMouseOver = false;
        mView->BaseTouchFlush();
    }
}


void FViewContainer::MouseWheel(int pDirection)
{
    for(int i = 0; i<mView->mSubviews.mCount; i++)
    {
        FViewContainer *aCtr = ((FView *)(mView->mSubviews.Fetch(i)))->GetContainer();
        aCtr->MouseWheel(pDirection);
    }
    if(mView)
    {
        mView->MouseWheel(pDirection);
    }
}

*/


/*


void FCanvas::DrawBorders() {
    Graphics::OutlineRect(1.0f, 1.0f, mWidth - 2.0f, mHeight - 2.0f, 1.0f);
}


void FCanvas::PrintTransform()
{
    Log(mName.c());
    
    Log("\nTRA");
    
    //Log(mName.c());
    
    Log(" - XY[%.2f %.2f] Sc[%.2f %.2f %.2f] R[%.2f] - Fr[%.2f,%.2f,%.2f,%.2f]\n", mTransform.mX, mTransform.mY, mTransform.mScale, mTransform.mScaleX, mTransform.mScaleY, mTransform.mRotation, mX, mY, mWidth, mHeight);
    
    Log("ABS - XY[%.2f %.2f] Sc[%.2f %.2f %.2f] R[%.3f]\n\n", GetAbsoluteTransformX(), GetAbsoluteTransformY(), GetAbsoluteTransformScale(), GetAbsoluteTransformScaleX(), GetAbsoluteTransformScaleY(), GetAbsoluteTransformRotation());
}

void FCanvas::PrintFrame()
{
    FString aName = mName;
    if(aName.mLength <= 0)aName = "Canvas";
    
    printf("%s Frame (%.2f, %.2f, %.2f, %.2f)\n", aName.c(), GetX(), GetY(), GetWidth(), GetHeight());
}

void FCanvas::PrintAllChildrenTransforms()
{
    
    FList aStack;
    FList aTemp;
    
    
    printf("-----%s-----\n", mName.c());
    
    aStack.Add(this);
    
    while(aStack.mCount > 0)
    {
        EnumList(FCanvas, aCanvas, aStack)
        {
            
            EnumList(FCanvas, aChildCanvas, aCanvas->mSubCanvass)
            {
                aTemp.Add(aChildCanvas);
            }
            aCanvas->PrintTransform();
            
        }
        
        aStack.Clear();
        
        EnumList(FCanvas, aCanvas, aTemp)
        {
            aStack.Add(aCanvas);
        }
        
        aTemp.Clear();
    }
    
    printf("-----------------\n");
    
}

void FCanvas::SetStaticTransform(bool pIsStatic)
{
    GetContainer()->SetStaticTransform(pIsStatic);
}

void FCanvas::SizeToFitChildren()
{
    SizeToFitChildren(0.0f, 0.0f);
}

void FCanvas::SizeToFitChildren(float pPaddingLeft, float pPaddingRight)
{
    SizeToFitChildren(pPaddingLeft, pPaddingRight, 0.0f, 0.0f);
}

void FCanvas::SizeToFitChildren(float pPaddingLeft, float pPaddingRight, float pPaddingTop, float pPaddingBottom)
{
    
    float aLeft = 0.0f;
    float aRight = 0.0f;
    float aTop = 0.0f;
    float aBottom = 0.0f;
    if(mSubCanvass.mCount > 0.0f) {
        EnumList(FCanvas, aCanvas, mSubCanvass) {
            float aCheckLeft = aCanvas->GetX();
            float aCheckRight = aCanvas->GetX() + aCanvas->GetWidth();
            float aCheckTop = aCanvas->GetY();
            float aCheckBottom = aCanvas->GetY() + aCanvas->GetHeight();
            
            if(aCheckLeft < aLeft)aLeft = aCheckLeft;
            if(aCheckRight > aRight)aRight = aCheckRight;
            if(aCheckTop < aTop)aTop = aCheckTop;
            if(aCheckBottom > aBottom)aBottom = aCheckBottom;
            
        }
        
        float aWidth = (aRight - aLeft) + (pPaddingLeft + pPaddingRight);
        float aHeight = (aBottom - aTop) + (pPaddingBottom + pPaddingTop);
        
        SetFrame(aLeft - pPaddingLeft, aTop - pPaddingTop, aWidth, aHeight);
    }
}

FVec2 FCanvas::Convert(float pX, float pY, FCanvas *pFromCanvas, FCanvas *pToCanvas)
{
    FVec2 aResult;
    aResult.mX = pX;
    aResult.mY = pY;
    
    ConvertPoint(aResult.mX, aResult.mY, pFromCanvas, pToCanvas);
    
    return aResult;
}

void FCanvas::ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    if(pFromCanvas)
    {
        pFromCanvas->GetContainer()->mTransformAbsolute.Untransform(pX, pY, pFromCanvas->GetWidth(), pFromCanvas->GetHeight());
    }
    
    if(pToCanvas)
    {
        pToCanvas->GetContainer()->mTransformAbsolute.Transform(pX, pY, pToCanvas->GetWidth(), pToCanvas->GetHeight());
    }
}

float FCanvas::ConvertScale(float pScale, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    float aResult = pScale;
    if(pFromCanvas)aResult /= pFromCanvas->GetContainer()->mTransformAbsolute.mScale;
    if(pToCanvas)aResult *= pToCanvas->GetContainer()->mTransformAbsolute.mScale;
    return aResult;
}

float FCanvas::ConvertRotation(float pDegrees, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    float aResult = pDegrees;
    if(pFromCanvas)aResult -= pFromCanvas->GetContainer()->mTransformAbsolute.mRotation;
    if(pToCanvas)aResult += pToCanvas->GetContainer()->mTransformAbsolute.mRotation;
    return aResult;
}
 
*/


