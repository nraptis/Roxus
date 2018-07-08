//
//  UMenuStyleExtended.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/27/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UMenuStyleExtended.h"
#include "FApp.h"
#include "UNode.h"

UColorPicker::UColorPicker()// : UMenuPane("Color", true)
{
	SetText("Pick Color");
    //SetFrame(0.0f, 0.0f, UTIL_MENU_DEFAULT_WIDTH, UTIL_MENU_ROW_HEIGHT);
    SetExpandable(true);
    
    mColor = 0;
    
    mMenuItemWidthSlots = 4;
    
    mAllowMultipleExpandedSubpanes = true;
    
    //SetWidthSlots(1);
    
    //mButtonExpand = 0;
    //mExpandedSwatches = 0;
    
    //SetTitle("Color..");
    
    
    mSliderRed = new UExtendedSlider("R:", 0.0f, 1.0f);
    //mSliderRed->SetTitle("Red:");
    
    mSliderGreen = new UExtendedSlider("G:", 0.0f, 1.0f);
    //mSliderGreen->SetTitle("Green");
    
    mSliderBlue = new UExtendedSlider("B:", 0.0f, 1.0f);
    //mSliderBlue->SetTitle("Blue:");
    
    mSliderAlpha = new UExtendedSlider("A:", 0.0f, 1.0f);
    //mSliderAlpha->SetTitle("Alpha:");
    
    AddMenuItems(mSliderRed);
    AddMenuItems(mSliderGreen);
    AddMenuItems(mSliderBlue);
    AddMenuItems(mSliderAlpha);
    
    Collapse();
}

UColorPicker::~UColorPicker()
{
    //mButtonExpand = 0;
    
}

void UColorPicker::SetNormalRange()
{
    mSliderRed->SetMinMax(0.0f, 1.0f);
    mSliderGreen->SetMinMax(0.0f, 1.0f);
    mSliderBlue->SetMinMax(0.0f, 1.0f);
    mSliderAlpha->SetMinMax(0.15f, 1.5f);
    
}

void UColorPicker::SetExtraRange()
{
    mSliderRed->SetMinMax(0.0f, 1.5f);
    mSliderGreen->SetMinMax(0.0f, 1.5f);
    mSliderBlue->SetMinMax(0.0f, 1.5f);
    mSliderAlpha->SetMinMax(0.0f, 1.5f);
}

void UColorPicker::SetRandomRange()
{
    mSliderRed->SetMinMax(0.0f, 0.75f);
    mSliderGreen->SetMinMax(0.0f, 0.75f);
    mSliderBlue->SetMinMax(0.0f, 0.75f);
    mSliderAlpha->SetMinMax(0.0f, 0.75f);
}

void UColorPicker::SetSpeedRange()
{
    mSliderRed->SetMinMax(0.0f, 0.03f);
    mSliderGreen->SetMinMax(0.0f, 0.03f);
    mSliderBlue->SetMinMax(0.0f, 0.03f);
    mSliderAlpha->SetMinMax(0.0f, 0.03f);
}

void UColorPicker::Notify(void *pSender, int pID, void *pObject)
{
    UMenuPane::Notify(pSender, pID, pObject);
    /*
    if(pID == UTIL_ACTION_NODE_SELECT)
    {
        SetSelectedNode((UNode *)pObject);
        EnumList(FView, aView, mSubviews)aView->Notify(pSender, pID, pObject);
    }
    */
}

void UColorPicker::SetColor(FColor *pColor)
{
    mColor = pColor;
    
    if(mColor)
    {
        mSliderRed->SetTarget(&(mColor->mRed));
        mSliderGreen->SetTarget(&(mColor->mGreen));
        mSliderBlue->SetTarget(&(mColor->mBlue));
        mSliderAlpha->SetTarget(&(mColor->mAlpha));
    }
    else
    {
        mSliderRed->SetTarget(0);
        mSliderGreen->SetTarget(0);
        mSliderBlue->SetTarget(0);
        mSliderAlpha->SetTarget(0);
    }
}

void UColorPicker::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
    }
    else
    {
        
    }
}

void UColorPicker::Notify(void *pSender)
{
    UMenuPane::Notify(pSender);
    
    
    /*
    if(mButtonExpand == pSender)
    {
        if(mExpandedSwatches == 0)
        {
            float aSliderHeight = (UTIL_MENU_ROW_HEIGHT + 4.0f);
            
            mExpandedSwatches = new FView();
            //mExpandedSwatches->SetListener(this);
            
            
            if(mParent)mParent->AddSubview(mExpandedSwatches);
            else AddSubview(mExpandedSwatches);
            
            mSliderRed = new UExtendedSlider();
            mSliderRed->SetUp(0.0f, 0.0f, "Red");
            mSliderRed->SetListener(this);
            //mSliderRed->SetUp(0.0f, 0.0f, mExpandedSwatches->mWidth, "Red");
            mExpandedSwatches->AddSubview(mSliderRed);
            
            
            mSliderGreen = new UExtendedSlider();
            mSliderGreen->SetUp(0.0f, aSliderHeight, "Green");
            mSliderGreen->SetListener(this);
            //mSliderGreen->SetUp(0.0f, aSliderHeight, mExpandedSwatches->mWidth, "Green");
            mExpandedSwatches->AddSubview(mSliderGreen);
            
            mSliderBlue = new UExtendedSlider();
            mSliderBlue->SetUp(0.0f, aSliderHeight * 2.0f, "Blue");
            mSliderBlue->SetListener(this);
            mExpandedSwatches->AddSubview(mSliderBlue);
            
            mSliderAlpha = new UExtendedSlider();
            mSliderAlpha->SetUp(0.0f, aSliderHeight * 3.0f, "Alpha");
            mSliderAlpha->SetListener(this);
            mExpandedSwatches->AddSubview(mSliderAlpha);
            
            mExpandedSwatches->SetFrame(mX + mWidth / 2.0f, mY, mSliderRed->mWidth, aSliderHeight * 4);
            
            SetColor(mColor);
            //SetSelectedNode(gUtilsNode);
        }
        else
        {
            mSliderAlpha->Kill();
            mSliderBlue->Kill();
            mSliderGreen->Kill();
            mSliderRed->Kill();
            mExpandedSwatches->Kill();
            
            mSliderAlpha = 0;
            mSliderBlue = 0;
            mSliderGreen = 0;
            mSliderRed = 0;
            mExpandedSwatches = 0;
        }
    }
    */
}

UExtendedSlider::UExtendedSlider(const char *pText, float pMin, float pMax) : UExtendedSlider()
{
    SetMinMax(pMin, pMax);
    
    SetTextLabel(pText);
}

UExtendedSlider::UExtendedSlider()// : UMenuPane("slider", true)
{
    mTarget = 0;
    mMenuItemWidthSlots = 6;
    
    
    mCollapseRectHeight = UTIL_MENU_ROW_HEIGHT;
    
    SetCollapseBarWidth(30.0f, 1);
    
    mSlider = new USlider();
	AddSubview(mSlider);
    mCollapseViews.Add(mSlider);
    
    mLabelTitle = new ULabel();
    mLabelTitle->mBold = true;
    mLabelTitle->mAlign = 1;
    mLabelTitle->mAlignPadding = 2;
    AddSubview(mLabelTitle);
    mCollapseViews.Add(mLabelTitle);
    
    mLabelValue = new ULabel();
    mLabelValue->mAlign = -1;
    mLabelValue->mAlignPadding = 2;
    AddSubview(mLabelValue);
	mCollapseViews.Add(mLabelValue);
    
    
    
    mControlPane = new UMenuPane();
    
    AddMenuItems(mControlPane);
    
    
    mButtonDisplayMinMax = new UButton("M/M");
    mButtonDisplayMinMax->StyleSetCheckBox();
    mButtonDisplayMinMax->mCheckBox = true;
    mButtonDisplayMinMax->mChecked = false;
    
    mButtonSetZero = new UButton("0");
    mButtonSetOne = new UButton("1");
    mButtonSetHalf = new UButton(".5");
    
    mControlPane->AddLine(mButtonDisplayMinMax, mButtonSetZero, mButtonSetHalf, mButtonSetOne);
    
    
    
    
    mButtonMinAdd1 = new UButton("Lo+");
    mButtonMinSub1 = new UButton("Lo-");
    
    mButtonMaxAdd1 = new UButton("Hi+");
    mButtonMaxSub1 = new UButton("Hi-");
    
    mButtonRangeShrink = new UButton("[--]");
    
    mControlPane->AddLine(mButtonMinAdd1, mButtonMinSub1, mButtonMaxAdd1, mButtonMaxSub1, mButtonRangeShrink);
    
    
    
    
    //SetFrame(0.0f, 0.0f, UTIL_MENU_DEFAULT_WIDTH, UTIL_MENU_ROW_HEIGHT);
    
    
    //mMenuItemWidthSlots = 4;
    
    
    
	mButtonExtraSetZero = new UButton("");
	mButtonExtraSetZero->StyleSetClear();
	AddSubview(mButtonExtraSetZero);
	mCollapseViews.Add(mButtonExtraSetZero);



	mButtonExtraSetOne = new UButton("");
	mButtonExtraSetOne->StyleSetClear();
	AddSubview(mButtonExtraSetOne);
	mCollapseViews.Add(mButtonExtraSetOne);
    
	SetExpandable(true, false);
    
    Collapse();
}

UExtendedSlider::~UExtendedSlider()
{
    
}

void UExtendedSlider::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuPane::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    
    float aWorkArea = mWidth;
    float aWorkRight = mWidth - 2.0f;
    float aWorkLeft = 2.0f;
    
    if(mCollapseBarWidthFixed)
    {
        aWorkArea -= (mCollapseBarWidth + 4.0f);
        aWorkRight = mWidth - (mCollapseBarWidth);
    }
    
    float aTitleWidth = 0.0f;
    if(mLabelTitle)
    {
        aTitleWidth = aWorkArea / 6.0f;
        if(aTitleWidth < 32)aTitleWidth = 32;
        
        
    }
    
    float aValueLabelWidth = 0.0f;
    if(mLabelValue)
    {
        aValueLabelWidth = (aWorkArea / 6.0f);
        if(aValueLabelWidth < 32.0f)aValueLabelWidth = 32.0f;
    }
    
    if(aTitleWidth > 0.0f)
    {
        aWorkArea -= 8.0f;
        aWorkArea -= aTitleWidth;
    }
    
    if(aValueLabelWidth > 0.0f)
    {
        aWorkArea -= 8.0f;
        aWorkArea -= aValueLabelWidth;
    }
    
    if(mLabelValue)
    {
        mLabelValue->SetMenuItemFrame(aWorkRight - aValueLabelWidth, 0.0f, aValueLabelWidth, mCollapseRectHeight);
        UpdateText();
        
        aWorkRight -= aValueLabelWidth;
    }
    
    if(mLabelTitle)
    {
		mLabelTitle->UMenuItem::SetMenuItemFrame(aWorkLeft, 0.0f, aTitleWidth, mCollapseRectHeight);


		if(mButtonExtraSetZero)
		{
			mButtonExtraSetZero->SetMenuItemFrame(aWorkLeft, 0.0f, aTitleWidth / 2.0f, mCollapseRectHeight);

		}

		if(mButtonExtraSetOne)
		{
			mButtonExtraSetOne->SetMenuItemFrame(aWorkLeft + aTitleWidth / 2.0f, 3.0f, aTitleWidth / 2.0f, mCollapseRectHeight - 6);
		}


        //mLabelTitle->SetText(mTextLabelString.c());
        UpdateText();
        
        aWorkLeft += aTitleWidth;
    }
    
    
    //AddSubview(mLabelTitle);
    //AddSubview(mLabelValue);
    
    
    
    if(mSlider)
    {
        aWorkArea = (aWorkRight - aWorkLeft);
        
        mSlider->SetMenuItemFrame(aWorkLeft, 0.0f, aWorkArea, mCollapseRectHeight);
    }
    
    //FView::SetFrame(pX, pY, pWidth, pHeight);
    //SetUp();
}

void UExtendedSlider::Notify(void *pSender)
{
    FView::Notify(pSender);
    
    if((pSender == mSlider) && (mSlider != 0))
    {
        if(mTarget)
        {
            *mTarget = (mSlider->mValue);
        }
        
        UpdateText();
        
        if(mParent)
        {
            mParent->Notify(this);
        }
        
        if(mListenerView)
        {
            mListenerView->Notify(this);
        }
        
    }
    else
    {
        if(pSender == mButtonMinAdd1)
        {
            //mSlider->mBaseSlider->AttemptGrowMin(0.25f);
        }
        if(pSender == mButtonMinSub1)
        {
            //mSlider->mBaseSlider->AttemptShrinkMin(0.25f);
        }
        if(pSender == mButtonMaxAdd1)
        {
            //mSlider->mBaseSlider->AttemptGrowMax(0.25f);
        }
        if(pSender == mButtonMaxSub1)
        {
            //mSlider->mBaseSlider->AttemptShrinkMax(0.1f);
        }
        if(pSender == mButtonRangeShrink)
        {
            //mSlider->mBaseSlider->AttemptShrinkRange(0.25f);
        }
        
        if(pSender == mButtonDisplayMinMax)
        {
            
        }
        
		if((pSender == mButtonSetZero) || (pSender == mButtonExtraSetZero))
        {
            mSlider->mBaseSlider->ForceValue(0.0f);
        }
        if(pSender == mButtonSetHalf)
        {
            mSlider->mBaseSlider->ForceValue(0.5f);
        }
		if((pSender == mButtonSetOne) || (pSender == mButtonExtraSetOne))
        {
            mSlider->mBaseSlider->ForceValue(1.0f);
        }
        
        mSlider->Notify(mSlider->mBaseSlider);
    }
    
    UpdateText();
    
}

void UExtendedSlider::SetTextLabel(const char *pText)
{
    mTextLabelString = pText;
    
    UpdateText();
}

void UExtendedSlider::SetTextValue(const char *pText)
{
    mTextValueString = pText;
    
    UpdateText();
}

void UExtendedSlider::SetMinMax(float pMin, float pMax)
{
    if(mSlider)
    {
        mSlider->mBaseSlider->SetMin(pMin);
        mSlider->mBaseSlider->SetMax(pMax);
        UpdateText();
    }
}

void UExtendedSlider::UpdateText()
{
    int aDecimalCount = 1;
    
    
    
    
    bool aDisplayMinMax = false;
    if(mButtonDisplayMinMax)
    {
        aDisplayMinMax = mButtonDisplayMinMax->mChecked;
    }
    
    if((mSlider->mBaseSlider->mMax - mSlider->mBaseSlider->mMin) < 10.0f)
    {
        aDecimalCount = 2;
        
        if((mSlider->mBaseSlider->mMax - mSlider->mBaseSlider->mMin) < 0.2f)
        {
            aDecimalCount = 3;
        }
    }
    
    
    if(mSlider)
    {
        mTextMin = FString(mSlider->mBaseSlider->mMin, aDecimalCount);
        mTextMax = FString(mSlider->mBaseSlider->mMax, aDecimalCount);
        
        mTextValueString = FString(mSlider->mValue, aDecimalCount);
    }
    
    if(aDisplayMinMax)
    {
        if(mLabelValue)
        {
            mLabelValue->SetText(FString(mTextMin).c());
        }
        
        if(mTarget)
        {
            mLabelTitle->SetText(FString(mTextMax.c()).c());
        }
    }
    else
    {
        if(mLabelValue)
        {
            mLabelValue->SetText(mTextValueString.c());
        }
        
        if(mLabelTitle)
        {
            mLabelTitle->SetText(mTextLabelString.c());
        }
    }
}

void UExtendedSlider::SetTarget(float *pTarget)
{
    mTarget = pTarget;
    
    if(mSlider)
    {
        mSlider->SetValue(mTarget);
    }
    
    UpdateText();
}

void UExtendedSlider::Update()
{
    UMenuPane::Update();
}

void UExtendedSlider::Draw()
{
    UMenuPane::Draw();
}


UStepper::UStepper(const char *pTitle, int pStartValue) : UStepper()
{
    mValue = pStartValue;
    
    SetTitleText(pTitle);
    SetValueText(pStartValue);
}

UStepper::UStepper()
{
    mMenuItemWidthSlots = 6;
    
    mRectBack.mCornerPointCount = 6;
    mRectBack.mCornerRadius = 5;
    
    mRectBackShading.mCornerRadius = 5;
    mRectBackShading.mCornerPointCount = 6;
    
    mRectBack.SetColorTop(1.0f, 1.0f, 1.0f, 0.08f);
    mRectBack.SetColorBottom(0.8f, 0.8f, 1.0f, 0.15f);
    
    mRectBackShading.SetColorTop(1.0f, 1.0f, 0.9f, 0.3f);
    mRectBackShading.SetColorBottom(1.0f, 0.9f, 1.0f, 0.0f);
    
    
    
    SetHeight(UTIL_MENU_ROW_HEIGHT);
    
    //mCollapseRectHeight = UTIL_MENU_ROW_HEIGHT;
    //mCollapseRectHeight = UTIL_MENU_PANE_HEADER_HEIGHT;
    
    //SetCollapseBarWidth(40.0f, 1);
    //SetExpandable(true);
    
    mLabelValue = new ULabel();
    mLabelValue->mAlignPadding = 2;
    mLabelValue->mAlign = 0;
    AddSubview(mLabelValue);
    
    mLabelTitle = new ULabel();
    mLabelTitle->mAlign = 1;
    mLabelTitle->mAlignPadding = 2;
    AddSubview(mLabelTitle);
    
    mButtonZero = new UButton("0");
    AddSubview(mButtonZero);
    
	mButtonM10 = new UButton("--");

	AddSubview(mButtonM10);

		mButtonM = new UButton("-");
		AddSubview(mButtonM);

    mButtonAmount = new UButton("1");
    AddSubview(mButtonAmount);
    
    
	mButtonP = new UButton("+");
	AddSubview(mButtonP);

	mButtonP10 = new UButton("++");
	AddSubview(mButtonP10);
    
    
    mTarget = 0;
    mValue = 0;//...
    
    mButtonTimer[0] = 0;
    mButtonTimer[1] = 0;
    
}

UStepper::~UStepper()
{
    
}

void UStepper::Update()
{
    //UMenuPane::Update();
    
    int aThresh1 = 25;
    int aThresh2 = 40;
    
    int aMod1 = 5;
    int aMod2 = 1;
    
    
    if(mButtonM)
    {
        if(mButtonM->mTouchDownInside)
        {
            mButtonTimer[0]++;
            
            if(mButtonTimer[0] >= aThresh2)
            {
                if((mButtonTimer[0] % aMod2) == 0)
                {
                    Notify(mButtonM);
                }
            }
            else if(mButtonTimer[0] >= aThresh1)
            {
                if((mButtonTimer[0] % aMod1) == 0)
                {
                    Notify(mButtonM);
                }
            }
        }
        else
        {
            mButtonTimer[0] = 0;
        }
    }
    
    if(mButtonP)
    {
        if(mButtonP->mTouchDownInside)
        {
            mButtonTimer[1]++;
            
            if(mButtonTimer[1] >= aThresh2)
            {
                if((mButtonTimer[1] % aMod2) == 0)
                {
                    Notify(mButtonP);
                }
            }
            else if(mButtonTimer[1] >= aThresh1)
            {
                if((mButtonTimer[1] % aMod1) == 0)
                {
                    Notify(mButtonP);
                }
            }
        }
        else
        {
            mButtonTimer[1] = 0;
        }
    }
}

void UStepper::Draw()
{
    //UMenuPane::Draw();
    mRectBack.Draw();
    mRectBackShading.Draw();
    
    
}

void UStepper::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    mRectBack.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mRectBack.mRefresh = true;
    
    mRectBackShading.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mRectBackShading.mRefresh = true;
    
    
    float aWidth = mWidth - 6.0f;
    
    float aX = 3.0f;
    float aTitleWidth = aWidth / 4.0f;
    if(aTitleWidth < 110.0f)aTitleWidth = 110.0f;
    
    if(mLabelTitle)
    {
        mLabelTitle->SetMenuItemFrame(aX, 0.0f, aTitleWidth, mHeight);
        
        aX += (aTitleWidth + 2);
        aWidth -= (aTitleWidth + 2);
    }
    
    float aValueWidth = aWidth / 4.0f;
    if(aValueWidth < 28)aValueWidth = 28;
    
    if(mLabelValue)
    {
        //mLabelValue->SetMenuItemFrame(aX, 0.0f, aValueWidth, mHeight);
        //aX += (aValueWidth + 2);
        aWidth -= (aValueWidth + 2);
    }
    
    float aButtonWidth = 24.0f;
    float aButtonSpacing = 2.0f;
    float aButtonInset = 2.0f;
    
    if(aWidth > 80.0f)
    {
        aButtonWidth = (aWidth / 7.0f);
    }
    float aButtonHop = aButtonWidth;
    
    aButtonWidth -= aButtonSpacing;
    
    
    mButtonZero->SetMenuItemFrame(aX, aButtonInset, aButtonWidth, mHeight - (aButtonInset * 2));
    aX += aButtonHop;
    
    
    if(mLabelValue)
    {
        mLabelValue->SetMenuItemFrame(aX, 0.0f, aValueWidth, mHeight);
        aX += (aValueWidth + 2);
    }

	

		mButtonM10->SetMenuItemFrame(aX, aButtonInset, aButtonWidth, mHeight - (aButtonInset * 2));
	aX += aButtonHop;
    
		mButtonM->SetMenuItemFrame(aX, aButtonInset, aButtonWidth, mHeight - (aButtonInset * 2));
	aX += aButtonHop;
    
    mButtonAmount->SetMenuItemFrame(aX, aButtonInset, aButtonWidth, mHeight - (aButtonInset * 2));
    aX += aButtonHop;
    
    
	mButtonP->SetMenuItemFrame(aX, aButtonInset, aButtonWidth, mHeight - (aButtonInset * 2));
	aX += aButtonHop;
    

	mButtonP10->SetMenuItemFrame(aX, aButtonInset, aButtonWidth, mHeight - (aButtonInset * 2));
	aX += aButtonHop;

	
    
    
    
    
    //aX
    
    
    
    
    
    mTarget = 0;
    
}

void UStepper::SetTitleText(const char *pTitleText)
{
    if(mLabelTitle)
    {
        mLabelTitle->SetText(pTitleText);
    }
}

void UStepper::SetValueText(int pValue)
{
    if(mLabelValue)
    {
        mLabelValue->SetText(FString(pValue).c());
    }
}

void UStepper::ModifyValue(int pAmount)
{
    if(mTarget)
    {
    }
    else
    {
    }
}

void UStepper::Notify(void *pSender)
{
    int aAmount = 1;
    
	if(pSender == mButtonM10)
	{
        mValue -= aAmount * 10;
		if(mTarget)*mTarget = mValue;
		SetValueText(mValue);
	}

    if(pSender == mButtonM)
    {
        mValue -= aAmount;
        if(mTarget)*mTarget = mValue;
        SetValueText(mValue);
    }
    if(pSender == mButtonP)
    {
		mValue += aAmount;
		if(mTarget)*mTarget = mValue;
		SetValueText(mValue);
    }
	if(pSender == mButtonP10)
	{
		mValue += aAmount * 10;
		if(mTarget)*mTarget = mValue;
		SetValueText(mValue);
	}
    
    if(pSender == mButtonZero)
    {
        mValue = 0;
        if(mTarget)*mTarget = mValue;
        SetValueText(mValue);
    }
    
	if(mParent)mParent->Notify(this);
}

void UStepper::SetTarget(int *pTarget)
{
    mTarget = pTarget;
    if(mTarget)
    {
        mValue = *mTarget;
        if(mLabelValue)
        {
            mLabelValue->SetText(FString(((int)*mTarget)).c());
        }
    }
}

void UStepper::SetValue(int pValue)
{
    mValue = pValue;
    if(mTarget)
    {
        *mTarget = pValue;
    }
}


//int                                         *mTarget;






