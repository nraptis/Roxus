//
//  UISlider.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UISlider.hpp"

UISlider::UISlider() {
    mPreviousDrawMin = -1;
    mPreviousDrawMax = -1;

    mValue = 0.0f;
    mTargetValue = 0;

    mBarHeight = 10.0f;

    mLabelTitle.mScale = 0.6f;
    mLabelTitle.mAlignment = 1;

    mLabelValue.mScale = 0.6f;
    mLabelValue.mAlignment = -1;

    mLabelTitleWidth = 80.0f;
    mLabelValueWidth = 60.0f;

    mLabelTitle.SetTransparentBackground();
    mLabelValue.SetTransparentBackground();

    AddChild(mLabelTitle);
    AddChild(mLabelValue);

    mLabelTitle.SetText("My Value:");
    
    mBaseSlider.SetFrame(0.0f, 0.0f, mWidth, mHeight);
    mBaseSlider.SetThumb(0.0f, 0.0f, 40.0f, mHeight);
    mBaseSlider.mDrawManual = true;
    AddChild(mBaseSlider);

    gNotify.Register(this, &mBaseSlider, "slider_update");

    FRect aRectBar = FRect(6.0f, mHeight / 2.0f - mBarHeight / 2.0f, mWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(0.0f, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);

    mRectBar.mCornerRadius = 5.0f;
    mRectBar.mCornerPointCount = 6;

    mRectBar.SetColorTop(0.22f, 0.22f, 0.22f);
    mRectBar.SetColorBottom(0.19f, 0.19f, 0.22f);
    mRectBar.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);

    mRectThumb.mCornerRadius = 12.0f;
    mRectThumb.mCornerPointCount = 10;

    mRectThumb.SetColorTop(0.2157f, 0.353f, 0.7647059f);
    mRectThumb.SetColorBottom(0.231f, 0.373f, 0.7847059f);
    mRectThumb.SetRect(0.0f, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);
}

UISlider::~UISlider()
{

}

void UISlider::Layout() {

    ToolMenuSectionRow::Layout();



    mLabelTitle.SetFrame(2.0f, 2.0f, mLabelTitleWidth, mHeight - 4.0f);
    mLabelValue.SetFrame(mWidth - (mLabelValueWidth + 2.0f), 2.0f, mLabelValueWidth, mHeight - 4.0f);

    float aSliderLeft = mLabelTitle.GetRight() + 2.0f;
    float aSliderRight = mLabelValue.GetLeft() - 2.0f;
    float aSliderWidth = (aSliderRight - aSliderLeft);


    mBaseSlider.SetFrame(aSliderLeft, 0.0f, aSliderWidth, mHeight);
    mBaseSlider.mThumbHeight = mHeight;

    FRect aRectBar = FRect(aSliderLeft + 6.0f, mHeight / 2.0f - mBarHeight / 2.0f, aSliderWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(aSliderLeft + 2.0f, 10.0f, mBaseSlider.mThumbWidth - 4.0f, mBaseSlider.mThumbHeight - 20.0f);

    mRectBar.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);

    mRectThumb.SetRect(aSliderLeft, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);

    mRectBar.mRefresh = true;
    mRectThumb.mRefresh = true;

    mBaseSlider.SetValue(mValue);
}

void UISlider::Draw() {
    mRectBar.Draw();
    mRectThumb.Draw(mBaseSlider.mThumbX, 0.0f);

    bool aUpdateText = false;
    if (mBaseSlider.mMin != mPreviousDrawMin) {
        mPreviousDrawMin = mBaseSlider.mMin;
        aUpdateText = true;
    }

    if (mBaseSlider.mMax != mPreviousDrawMax) {
        mPreviousDrawMax = mBaseSlider.mMax;
        aUpdateText = true;
    }


    if(aUpdateText || true)
    {
        int aDecimals = 1;

        float aRange = mBaseSlider.mMax - mBaseSlider.mMin;

        if(aRange <= 2.0f)
        {
            aDecimals = 2;

            if(aRange < 0.5f)
            {
                aDecimals = 4;
            }

        }

        mLabelValue.mText = FString(mBaseSlider.mValue, 3.0f);
        Graphics::SetColor();
    }
}

void UISlider::SetValue(float *pTargetValue) {
    mTargetValue = pTargetValue;
    if (mTargetValue) {
        mBaseSlider.ForceValue(*mTargetValue);
        mValue = mBaseSlider.GetValue();
    } else {
        if ((mValue < mBaseSlider.mMin) || (mValue > mBaseSlider.mMax)) {
            mValue = mBaseSlider.mMin;
            mBaseSlider.ForceValue(mValue);
        }
    }
}

float UISlider::GetValue() {
    return mBaseSlider.GetValue();
}

void UISlider::Notify(void *pSender, const char *pNotification) {
    if (FString("slider_update") == pNotification) {
        if (pSender == &mBaseSlider) {

            mValue = mBaseSlider.mValue;
            if (mTargetValue) {
                *mTargetValue = mValue;
            }

            gNotify.Post(this, "slider_update");
        }
    }
}
