//
//  FWindow.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/14/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "FWindow.hpp"
#include "core_graphics.h"

FWindow::FWindow() {
    mRoot.mWindow = this;
    mRoot.mParent = 0;
    mRoot.mName = "root";
    mRoot.mClipsContent = false;
    mRoot.mConsumesTouches = false;
    //mRoot.mRecievesConsumedTouches = false;
    //mRoot.mRecievesOutsideTouches = false;
    mRoot.mDeleteWhenParentIsDeleted = false;
}

FWindow::~FWindow() {

}

void FWindow::AddChild(FCanvas *pCanvas) {
    mRoot.AddChild(pCanvas);
}

void FWindow::AddChild(FCanvas &pCanvas) {
    pCanvas.mDeleteWhenParentIsDeleted = false;
    AddChild(&pCanvas);
}

void FWindow::PrintTempList(const char *pName) {

    printf("List[%s] => {", pName);

    for (int i=0;i<mTemp.mCount;i++) {
        FCanvas *aCanvas = ((FCanvas *)mTemp.mData[i]);
        printf("%s", aCanvas->mName.c());
        if (i < mTemp.mCount - 1) {
            printf(", ");
        }
    }
    printf("}\n\n");
}

void FWindow::Update() {
    while (!(mRealizeBucket.IsEmpty() && mLayoutBucket.IsEmpty())) {
        if (!mRealizeBucket.IsEmpty()) {
            mTemp.RemoveAll();
            mRealizeBucket.AddCanvasesToList(&mTemp);
            EnumList(FCanvas, aCanvas, mTemp) { RegisterTransformDidUpdate(aCanvas); }

            //Now we need to layout all the canvases and their children...
            mTemp.RemoveAll();
            mRealizeBucket.AddCanvasesAndChildrenRecursivelyToListAndRemoveAll(&mTemp);

            //We can remove all of these canvases from layout-bucket,
            //and frame-update-bucket.
            EnumList(FCanvas, aCanvas, mTemp) {
                aCanvas->mWindow = this;
                mLayoutBucket.Remove(aCanvas);
            }

            EnumList(FCanvas, aCanvas, mTemp) { aCanvas->BaseLayout(); }
        }

        //"Layout" everything from layout-bucket, and they all
        //need to update their transform...
        if (!mLayoutBucket.IsEmpty()) {
            mTemp.RemoveAll();
            mLayoutBucket.AddCanvasesToListAndRemoveAll(&mTemp);
            EnumList(FCanvas, aCanvas, mTemp) {
                RegisterTransformDidUpdate(aCanvas);
                aCanvas->BaseLayout();
            }
        }
    }

    if (!mTransformUpdateBucket.IsEmpty()) {
        mTemp.RemoveAll();
        mTransformUpdateBucket.AddCanvasesToListAndRemoveAll(&mTemp);
        EnumList(FCanvas, aCanvas, mTemp) {
            aCanvas->ComputeAbsoluteTransformation();
        }
    }

    mRoot.BaseUpdate();
}

void FWindow::Draw() {
    mRoot.BaseDraw();
}

bool FWindow::TouchDown(float pX, float pY, void *pData) {
    bool aConsumed = false;
    FCanvas *aCollider = mRoot.BaseTouchDown(pX, pY, pX, pY, pData, false, aConsumed);
    if (aCollider) {
        printf("Touch Landed: {{%s}} [C: %d]\n", aCollider->mName.c(), aCollider->mTouchCount);
        return aConsumed;
    }
    return false;
}

void FWindow::TouchMove(float pX, float pY, void *pData) {
    mRoot.BaseTouchMove(pX, pY, pX, pY, pData, false);
}

void FWindow::TouchUp(float pX, float pY, void *pData) {
    mRoot.BaseTouchUp(pX, pY, pX, pY, pData, false);
}

void FWindow::TouchFlush() {
    mRoot.BaseTouchFlush();
}

bool FWindow::MouseDown(float pX, float pY, int pButton) {
    return false;
}

bool FWindow::MouseMove(float pX, float pY) {
    return false;
}

void FWindow::MouseUp(float pX, float pY, int pButton) {

}

void FWindow::MouseWheel(int pDirection) {

}

void FWindow::KeyDown(int pKey) {

}

void FWindow::KeyUp(int pKey) {
    
}

void FWindow::SetDeviceSize(int pWidth, int pHeight) {
    mDeviceWidth = pWidth;
    mDeviceHeight = pHeight;
    RegisterTransformDidUpdate(&mRoot);
}

void FWindow::SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    if (mVirtualFrameX != pX || mVirtualFrameY != pY || mVirtualFrameWidth != pWidth || mVirtualFrameHeight != pHeight) {
        mVirtualFrameX = pX;
        mVirtualFrameY = pY;
        mVirtualFrameWidth = pWidth;
        mVirtualFrameHeight = pHeight;
        mRoot.SetFrame(pX, pY, pWidth, pHeight);
    }
}

void FWindow::RegisterRealize(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    if (!mRealizeBucket.Exists(pCanvas)) {
        if (!mRealizeBucket.ParentExists(pCanvas)) {
            mRealizeBucket.RemoveAllChildren(pCanvas);
            mRealizeBucket.Add(pCanvas);
        }
    }
}

void FWindow::RegisterChildrenDidUpdate(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    mLayoutBucket.Add(pCanvas);
}

/*
void FWindow::RegisterParentDidUpdate(FCanvas *pCanvas) {
    if (pCanvas == 0) return;

    //printf("\t---RegisterParentDidUpdate(%s)\n", pCanvas->mName.c());

    mLayoutBucket.Add(pCanvas);
    //mParentUpdateBucket.Add(pCanvas);
}
*/

//Transform updates must be recursive through children.
void FWindow::RegisterTransformDidUpdate(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    if (!mTransformUpdateBucket.Exists(pCanvas)) {
        if (!mTransformUpdateBucket.ParentExists(pCanvas)) {
            mTransformUpdateBucket.RemoveAllChildren(pCanvas);
            mTransformUpdateBucket.Add(pCanvas);
        }
    }
}

void FWindow::RegisterFrameDidUpdate(FCanvas *pCanvas) {
    if (pCanvas == 0) return;


    /*
    FCanvas *aCanvas = pCanvas;
    if (pCanvas->mParent) { aCanvas = pCanvas; }

    if (!mLayoutBucket.Exists(pCanvas)) {
        if (mLayoutBucket.ParentExists(pCanvas)) {
            //The canvas' parent is already going to have
            //frame update recursively.
        } else {
            mLayoutBucket.RemoveAllChildren(pCanvas);
            mLayoutBucket.Add(pCanvas);
        }
    }
    */



    //printf("\t---RegisterFrameDidUpdate(%s)\n", pCanvas->mName.c());
    
    mLayoutBucket.Add(pCanvas);

    //The parent's child has updated its frame...
    RegisterChildrenDidUpdate(pCanvas->mParent);

    //The children's parent has updated its frame..
    EnumList(FCanvas, aChild, pCanvas->mChildren) {
        mLayoutBucket.Add(aChild);
        //RegisterParentDidUpdate(aChild);
    }
    RegisterTransformDidUpdate(pCanvas);
}

void FWindow::RegisterKill(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    mKillBucket.Add(pCanvas);
}

void FWindow::RegisterDealloc(FCanvas *pCanvas) {
    mRealizeBucket.Remove(pCanvas);
    mLayoutBucket.Remove(pCanvas);
    mTransformUpdateBucket.Remove(pCanvas);
    mKillBucket.Remove(pCanvas);
}



