/*
 *  FSlider.cpp
 *  Fly Swatter
 *
 *  Created by Nick Raptis on 12/31/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "FSlider.h"
#include "core_graphics.h"
#include "core_includes.h"

FSlider::FSlider()
{
    mMin = 0.0f;
    mMax = 1.0f;
    
    mThumbX = 0.0f;
    mThumbY = 0.0f;
    mThumbWidth = 40.0f;
    mThumbHeight = 40.0f;
    
    
    mClickData = 0;
    
    mClickStartThumbX = 0.0f;
    mClickStartThumbY = 0.0f;
    
    mClickStartTouchX = 0.0f;
    mClickStartTouchY = 0.0f;
    
    mThumbBufferLeft = 5.0f;
    mThumbBufferRight = 5.0f;
    
    mValue = 0.0f;
    mPercent = 0.0f;
}

FSlider::~FSlider()
{
    
}

void FSlider::TouchDown(float pX, float pY, void *pData)
{
    
    
    mClickData = pData;
    
    mClickStartThumbX = mThumbX;
    mClickStartThumbY = mThumbY;
    
    mClickStartTouchX = pX;
    mClickStartTouchY = pY;
    
}

void FSlider::TouchMove(float pX, float pY, void *pData)
{
    if(mClickData == pData)
    {
        float aDeltaX = mClickStartTouchX - pX;
        //float aDeltaY = mClickStartTouchY - pY;
        
        mThumbX = mClickStartThumbX - aDeltaX;
        
        float aBorderRight = GetWidth() - (mThumbWidth + mThumbBufferRight);
        float aBorderLeft = mThumbBufferLeft;
        
        if(mThumbX < aBorderLeft)mThumbX = aBorderLeft;
        if(mThumbX > aBorderRight)mThumbX = aBorderRight;
        
        mPercent = (mThumbX - aBorderLeft) / (aBorderRight - aBorderLeft);
        mValue = mMin + (mMax - mMin) * mPercent;
        
        if(mParent)
        {
            mParent->Notify(this);
        }
    }
    
}

void FSlider::TouchUp(float pX, float pY, void *pData)
{
    if(mClickData == pData)
    {
        mClickData = 0;
        
        float aDeltaX = mClickStartTouchX - pX;
        //float aDeltaY = mClickStartTouchY - pY;
        
        mThumbX = mClickStartThumbX - aDeltaX;
        
        
        float aBorderRight = GetWidth() - (mThumbWidth + mThumbBufferRight);
        float aBorderLeft = mThumbBufferLeft;
        
        if(mThumbX < aBorderLeft)mThumbX = aBorderLeft;
        if(mThumbX > aBorderRight)mThumbX = aBorderRight;
        
        mPercent = (mThumbX - aBorderLeft) / (aBorderRight - aBorderLeft);
        mValue = mMin + (mMax - mMin) * mPercent;
        
        if(mParent)
        {
            mParent->Notify(this);
        }
    }
}

void FSlider::TouchFlush()
{
    
}

void FSlider::SetMin(float pMin)
{
    mMin = pMin;
}

void FSlider::SetMax(float pMax)
{
    mMax = pMax;
}

void FSlider::SetRange(float pMin, float pMax)
{
    SetMin(pMin);
    SetMax(pMax);
}

float FSlider::GetValue()
{
    return mValue;
}

float FSlider::GetRotationValue()
{
    return GetValue() * 360.0f;
}

void FSlider::SetRotationValue(float pDegrees)
{
    float aValue = pDegrees;
    
    if((aValue < -1000) || (aValue > 860))
    {
        aValue = fmodf(aValue, 360.0f);
    }
    
    while (aValue < 0)aValue += 360.0f;
    while (aValue >= 360.0f)aValue -= 360.0f;
    
    float aPercent = aValue / 360.0f;
    
    if(aPercent < 0.0f)aPercent = 0.0f;
    if(aPercent > 1.0f)aPercent = 1.0f;
    
    SetValue(aPercent);
    
}

void FSlider::SetValue(float pValue)
{
    mValue = pValue;
    
    //if(pValue < mMin)pValue = mMin;
    //if(pValue > mMax)pValue = mMax;
    
    //mMin = 0.0f;
    //mMax = 1.0f;
    
    float aValueRange = (mMax - mMin);
    
    mPercent = 1.0f;
    
    if(aValueRange > 0.01f)
    {
        mPercent = (pValue - mMin) / aValueRange;
    }
    else
    {
        
    }
    
    if(mPercent < 0.0f)mPercent = 0.0f;
    if(mPercent > 1.0f)mPercent = 1.0f;
    
    float aBorderRight = GetWidth() - (mThumbWidth + mThumbBufferRight);
    float aBorderLeft = mThumbBufferLeft;
    
    if(mThumbX < aBorderLeft)mThumbX = aBorderLeft;
    if(mThumbX > aBorderRight)mThumbX = aBorderRight;
    
    float aBorderWidth = (aBorderRight - aBorderLeft);
    
    
    //mPercent
    
    //(mThumbX - aBorderLeft) / (aBorderRight - aBorderLeft);
    
    
    //if(pValue<0)pValue=0.0f;
    //if(pValue>1)pValue=1.0f;
    
    if(aBorderRight > 0)
    {
        mThumbX=aBorderLeft+(int)((float)(aBorderRight-aBorderLeft)*mPercent);
    }
}

void FSlider::ForceValue(float pValue)
{
    float aRange = (mMax - mMin);
    if(aRange <= 0.001f)
    {
        mMax = mMin + 0.001f;
        aRange = (mMax - mMin);
    }
    
    if(pValue < mMin)
    {
        mMin = (pValue - aRange * 0.1f);
    }
    if(pValue > mMax)
    {
        mMax = (pValue + aRange * 0.1f);
    }
    
    SetValue(pValue);
}

void FSlider::AttemptGrowMin(float pPercent)
{
    float aRange = mMax - mMin;
    
    mMin += aRange * pPercent;
    if(mMin > mValue)mMin = mValue;
    
    ForceValue(mValue);
}

void FSlider::AttemptShrinkMin(float pPercent)
{
    float aRange = mMax - mMin;
    
    mMin -= aRange * pPercent;
    if(mMin > mValue)mMin = mValue;
    
    ForceValue(mValue);
}

void FSlider::AttemptGrowMax(float pPercent)
{
    float aRange = mMax - mMin;
    
    mMax += aRange * pPercent;
    if(mMax < mValue)mMax = mValue;
    
    ForceValue(mValue);
}

void FSlider::AttemptShrinkMax(float pPercent)
{
    float aRange = mMax - mMin;
    
    mMax -= aRange * pPercent;
    if(mMax < mValue)mMax = mValue;
    
    ForceValue(mValue);
}

void FSlider::AttemptGrowRange(float pPercent)
{
    float aRange = mMax - mMin;
    
    float aRangeLo = (mValue - mMin);
    float aRangeHi = (aRange - aRangeLo);
    
    mMax += aRangeHi * pPercent;
    mMin -= aRangeLo * pPercent;
    
    ForceValue(mValue);
    
}

void FSlider::AttemptShrinkRange(float pPercent)
{
    float aRange = mMax - mMin;
    
    float aRangeLo = (mValue - mMin);
    float aRangeHi = (aRange - aRangeLo);
    
    mMax -= aRangeHi * pPercent;
    mMin += aRangeLo * pPercent;
    
    ForceValue(mValue);
}


void FSlider::SetThumb(float pX, float pY, float pWidth, float pHeight)
{
    mThumbX = pX;
    mThumbY = pY;
    
    mThumbWidth = pWidth;
    mThumbHeight = pHeight;
    
    SetValue(mValue);
}

void FSlider::Draw()
{
    
    Graphics::SetColor(0.75f, 0.75f, 0.75f, 1.0f);
    Graphics::OutlineRect(mThumbX, mThumbY, mThumbWidth, mThumbHeight, 8.0f);
    
    Graphics::SetColor(0.5f, 0.5f, 0.5f, 1.0f);
    Graphics::DrawRect(mThumbX + 2.0f, mThumbY + 2.0f, mThumbWidth - 4.0f, mThumbHeight - 4.0f);
    
    Graphics::SetColor();
}

