//
//  FViewTransform.cpp
//  RaptisGame
//
//  Created by Nick Raptis on 3/13/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FViewTransform.h"
#include "core_includes.h"

FViewTransform::FViewTransform() {
    mX = 0.0f;
    mY = 0.0f;
    mScale = 1.0f;
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    mRotation = 0.0f;
    mAnchorX = 0.0f;
    mAnchorY = 0.0f;
    for(int i=0;i<4;i++) {
        mCornerX[i] = 0.0f;
        mCornerY[i] = 0.0f;
    }
}

FViewTransform::~FViewTransform() {
    
}

bool FViewTransform::ApplyAbsoluteTransformation(FViewTransform *pParentTransform, float pParentX, float pParentY, float pParentWidth, float pParentHeight, FViewTransform *pTransform, float pX, float pY, float pWidth, float pHeight) {
    bool aReturn = true;
    float aStartX = mX;
    float aStartY = mY;
    float aStartScale = mScale;
    float aStartScaleX = mScaleX;
    float aStartScaleY = mScaleY;
    float aStartRotation = mRotation;
    float aStartAnchorX = mAnchorX;
    float aStartAnchorY = mAnchorY;
    mAnchorX = pTransform->mAnchorX;
    mAnchorY = pTransform->mAnchorY;
    float aAnchorWidth = mAnchorX * pWidth;
    float aAnchorHeight = mAnchorY * pHeight;
    float aAnchorX = aAnchorWidth * pTransform->mScale * pTransform->mScaleX;
    float aAnchorY = aAnchorHeight * pTransform->mScale * pTransform->mScaleY;
    mRotation = pTransform->mRotation;
    mScale = pTransform->mScale;
    mScaleX = pTransform->mScaleX;
    mScaleY = pTransform->mScaleY;
    float aParentX = pParentTransform->mX;
    float aParentY = pParentTransform->mY;
    float aParentScaleX = pParentTransform->mScale * pParentTransform->mScaleX;
    float aParentScaleY = pParentTransform->mScale * pParentTransform->mScaleY;
    mScale *= pParentTransform->mScale;
    mScaleX *= pParentTransform->mScaleX;
    mScaleY *= pParentTransform->mScaleY;
    if((pParentTransform->mAnchorX != 0.0f) || (pParentTransform->mAnchorY != 0.0f)) {
        float aParentShiftX = pParentWidth * pParentTransform->mAnchorX * (aParentScaleX);
        float aParentShiftY = pParentHeight * pParentTransform->mAnchorY * (aParentScaleY);
        if(pParentTransform->mRotation != 0.0f) {
            float aDist = aParentShiftX * aParentShiftX + aParentShiftY * aParentShiftY;
            float aSwivel = 180.0f - FaceTarget(-aParentShiftX, -aParentShiftY);
            if(aDist > SQRT_EPSILON)aDist = sqrtf(aDist);
            aSwivel -= pParentTransform->mRotation;
            float aDirX = Sin(aSwivel);
            float aDirY = Cos(aSwivel);
            aParentShiftX = aDirX * aDist;
            aParentShiftY = aDirY * aDist;
        }
        aParentX -= aParentShiftX;
        aParentY -= aParentShiftY;
    }
    mX = ((pX + pTransform->mX + aAnchorX) * (aParentScaleX));
    mY = ((pY + pTransform->mY + aAnchorY) * (aParentScaleY));
    if(pParentTransform->mRotation != 0) {
        float aPivotRotation = FaceTarget(mX, mY);
        float aDist = mX * mX + mY * mY;
        if(aDist > SQRT_EPSILON)aDist = sqrtf(aDist);
        aPivotRotation += pParentTransform->mRotation;
        float aDirX = Sin(-aPivotRotation);
        float aDirY = Cos(-aPivotRotation);
        mX = aDirX * (aDist) + aParentX;
        mY = aDirY * (aDist) + aParentY;
    } else {
        mX += aParentX;
        mY += aParentY;
    }
    mRotation += pParentTransform->mRotation;
    float aScaleX = mScale * mScaleX;
    float aScaleY = mScale * mScaleY;
    float aWidth = pWidth * (aScaleX);
    float aHeight = pHeight * (aScaleY);
    float aCornerStartX = mX;
    float aCornerStartY = mY;
    if(mRotation != 0) {
        float aDirX = Sin(-mRotation);
        float aDirY = Cos(-mRotation);
        float aNormalX = (aDirY);
        float aNormalY = (-aDirX);
        float aHeightShiftX = (aHeight * aDirX);
        float aHeightShiftY = (aHeight * aDirY);
        float aWidthShiftX = (aWidth * aNormalX);
        float aWidthShiftY = (aWidth * aNormalY);
        aCornerStartX -= ((aWidthShiftX * mAnchorX + aHeightShiftX * mAnchorY));
        aCornerStartY -= ((aWidthShiftY * mAnchorX + aHeightShiftY * mAnchorY));
        mCornerX[0] = aCornerStartX;
        mCornerY[0] = aCornerStartY;
        mCornerX[1] = aCornerStartX + aHeightShiftX;
        mCornerY[1] = aCornerStartY + aHeightShiftY;
        mCornerX[2] = aCornerStartX + (aWidthShiftX + aHeightShiftX);
        mCornerY[2] = aCornerStartY + (aWidthShiftY + aHeightShiftY);
        mCornerX[3] = aCornerStartX + aWidthShiftX;
        mCornerY[3] = aCornerStartY + aWidthShiftY;
    } else {
        aCornerStartX -= aAnchorWidth * aScaleX;
        aCornerStartY -= aAnchorHeight * aScaleY;
        mCornerX[0] = aCornerStartX;
        mCornerY[0] = aCornerStartY;
        mCornerX[1] = aCornerStartX;
        mCornerY[1] = aCornerStartY + aHeight;
        mCornerX[2] = aCornerStartX + aWidth;
        mCornerY[2] = aCornerStartY + aHeight;
        mCornerX[3] = aCornerStartX + aWidth;
        mCornerY[3] = aCornerStartY;
    }
    if(aStartX != mX)aReturn = false;
    if(aStartY != mY)aReturn = false;
    if(aStartScale != mScale)aReturn = false;
    if(aStartScaleX != mScaleX)aReturn = false;
    if(aStartScaleY != mScaleY)aReturn = false;
    if(aStartRotation != mRotation)aReturn = false;
    if(aStartAnchorX != mAnchorX)aReturn = false;
    if(aStartAnchorY != mAnchorY)aReturn = false;
    return aReturn;
}

bool FViewTransform::ApplyAbsoluteTransformation(FViewTransform *pTransform, float pX, float pY, float pWidth, float pHeight) {
    bool aReturn = true;
    float aStartX = mX;
    float aStartY = mY;
    float aStartScale = mScale;
    float aStartScaleX = mScaleX;
    float aStartScaleY = mScaleY;
    float aStartRotation = mRotation;
    float aStartAnchorX = mAnchorX;
    float aStartAnchorY = mAnchorY;
    if (pTransform != 0) {
        mAnchorX = pTransform->mAnchorX;
        mAnchorY = pTransform->mAnchorY;
        mRotation = pTransform->mRotation;
        mScale = pTransform->mScale;
        mScaleX = pTransform->mScaleX;
        mScaleY = pTransform->mScaleY;
        float aAnchorWidth = mAnchorX * pWidth;
        float aAnchorHeight = mAnchorY * pHeight;
        float aAnchorX = aAnchorWidth * pTransform->mScale * pTransform->mScaleX;
        float aAnchorY = aAnchorHeight * pTransform->mScale * pTransform->mScaleY;
        mX = pX + pTransform->mX + aAnchorX;
        mY = pY + pTransform->mY + aAnchorY;
        float aScaleX = mScale * mScaleX;
        float aScaleY = mScale * mScaleY;
        float aWidth = pWidth * (aScaleX);
        float aHeight = pHeight * (aScaleY);
        float aCornerStartX = mX;
        float aCornerStartY = mY;
        if (mRotation != 0) {
            float aDirX = Sin(-mRotation);
            float aDirY = Cos(-mRotation);
            float aNormalX = (aDirY);
            float aNormalY = (-aDirX);
            float aHeightShiftX = (aHeight * aDirX);
            float aHeightShiftY = (aHeight * aDirY);
            float aWidthShiftX = (aWidth * aNormalX);
            float aWidthShiftY = (aWidth * aNormalY);
            aCornerStartX -= ((aWidthShiftX * mAnchorX + aHeightShiftX * mAnchorY));
            aCornerStartY -= ((aWidthShiftY * mAnchorX + aHeightShiftY * mAnchorY));
            mCornerX[0] = aCornerStartX;
            mCornerY[0] = aCornerStartY;
            mCornerX[1] = aCornerStartX + aHeightShiftX;
            mCornerY[1] = aCornerStartY + aHeightShiftY;
            mCornerX[2] = aCornerStartX + (aWidthShiftX + aHeightShiftX);
            mCornerY[2] = aCornerStartY + (aWidthShiftY + aHeightShiftY);
            mCornerX[3] = aCornerStartX + aWidthShiftX;
            mCornerY[3] = aCornerStartY + aWidthShiftY;
        } else {
            aCornerStartX -= aAnchorWidth * aScaleX;
            aCornerStartY -= aAnchorHeight * aScaleY;
            mCornerX[0] = aCornerStartX;
            mCornerY[0] = aCornerStartY;
            mCornerX[1] = aCornerStartX;
            mCornerY[1] = aCornerStartY + aHeight;
            mCornerX[2] = aCornerStartX + aWidth;
            mCornerY[2] = aCornerStartY + aHeight;
            mCornerX[3] = aCornerStartX + aWidth;
            mCornerY[3] = aCornerStartY;
        }
    }
    if(aStartX != mX)aReturn = false;
    if(aStartY != mY)aReturn = false;
    if(aStartScale != mScale)aReturn = false;
    if(aStartScaleX != mScaleX)aReturn = false;
    if(aStartScaleY != mScaleY)aReturn = false;
    if(aStartRotation != mRotation)aReturn = false;
    if(aStartAnchorX != mAnchorX)aReturn = false;
    if(aStartAnchorY != mAnchorY)aReturn = false;
    return aReturn;
}

bool FViewTransform::ContainsPoint(float pX, float pY) {
    bool aReturn = false;
    if(mRotation != 0) {
        for(int aStart=0,aEnd=3;aStart<4;aEnd=aStart++) {
            if((((mCornerY[aStart] <= pY) && (pY < mCornerY[aEnd]))||
                 ((mCornerY[aEnd] <= pY) && (pY < mCornerY[aStart])))&&
                (pX < (mCornerX[aEnd] - mCornerX[aStart]) * (pY - mCornerY[aStart])
                 / (mCornerY[aEnd] - mCornerY[aStart]) + mCornerX[aStart])) {
                aReturn = !aReturn;
            }
        }
    } else {
        aReturn = ((pX >= mCornerX[0]) && (pY >= mCornerY[0]) && (pX <= mCornerX[2]) && (pY <= mCornerY[2]));
    }
    return aReturn;
}

void FViewTransform::Untransform(float &pX, float &pY, float pWidth, float pHeight) {
    float aDiffX = (pX - (mAnchorX * pWidth)) * mScale * mScaleX;
    float aDiffY = (pY - (mAnchorY * pHeight)) * mScale * mScaleY;
    float aPivotRotation = FaceTarget(aDiffX, aDiffY) + mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if(aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
    }
    float aDirX = Sin(-aPivotRotation);
    float aDirY = Cos(-aPivotRotation);
    pX = aDirX * (aDist) + mX;
    pY = aDirY * (aDist) + mY;
}

void FViewTransform::Untransform(float &pX, float &pY) {
    float aDiffX = pX * mScale * mScaleX;
    float aDiffY = pY * mScale * mScaleY;
    float aPivotRotation = FaceTarget(aDiffX, aDiffY) + mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if(aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
    }
    float aDirX = Sin(-aPivotRotation);
    float aDirY = Cos(-aPivotRotation);
    pX = aDirX * (aDist) + mX;
    pY = aDirY * (aDist) + mY;
}

void FViewTransform::Transform(float &pX, float &pY) {
    float aX = pX;
    float aY = pY;
    float aDiffX = (aX - mX);
    float aDiffY = (aY - mY);
    float aRot = FaceTarget(aDiffX, aDiffY) - mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if(aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
    }
    float aDirX = Sin(-aRot);
    float aDirY = Cos(-aRot);
    pX = aDirX * (aDist / (mScale * mScaleX));
    pY = aDirY * (aDist / (mScale * mScaleY));
}

void FViewTransform::Transform(float &pX, float &pY, float pWidth, float pHeight) {
    float aX = pX;
    float aY = pY;
    float aDiffX = (aX - mX);
    float aDiffY = (aY - mY);
    float aRot = FaceTarget(aDiffX, aDiffY) - mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if(aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
    }
    float aDirX = Sin(-aRot);
    float aDirY = Cos(-aRot);
    pX = aDirX * (aDist / (mScale * mScaleX)) + mAnchorX * pWidth;
    pY = aDirY * (aDist / (mScale * mScaleY)) + mAnchorY * pHeight;
}
