//
//  UMenuStyleExtended.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/27/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UMenuStyleExtended__
#define ___015_Fleet_XP__UMenuStyleExtended__

#include "UMenu.h"

class UExtendedSlider;
class UColorPicker : public UMenuPane// UMenuItemExpandable// UButton
{
public:
    UColorPicker();
    virtual ~UColorPicker();
    
    //virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight);
    
    
    void                                        SetNormalRange();
    void                                        SetExtraRange();
    void                                        SetRandomRange();
    void                                        SetSpeedRange();
    
    
    
    //virtual void								SetUp();
    //virtual void								SetUp(float pX, float pY);
    //virtual void                                SetUp(float pX, float pY, float pWidth);
    //virtual void								SetUp(float pX, float pY, float pWidth, const char *pTitle);
    
    virtual void                                Notify(void *pSender);
    virtual void                                Notify(void *pSender, int pID, void *pObject);
    virtual void                                SetSelectedNode(UNode *pNode);
    
    //FView                                       *mExpandedSwatches;
    //UButton                                     *mButtonExpand;
    
    
    void                                        SetColor(FColor *pColor);
    FColor                                      *mColor;
    
    
    UExtendedSlider                             *mSliderRed;
    UExtendedSlider                             *mSliderGreen;
    UExtendedSlider                             *mSliderBlue;
    UExtendedSlider                             *mSliderAlpha;
};

class UExtendedSlider : public UMenuPane
{
public:
    
    UExtendedSlider(const char *pText, float pMin, float pMax);
    UExtendedSlider();
    virtual ~UExtendedSlider();
    
    virtual void                                SetTextLabel(const char *pText);
    virtual void                                SetTextValue(const char *pText);
    
    FString                                     mTextLabelString;
    FString                                     mTextValueString;
    
    FString                                     mTextMin;
    FString                                     mTextMax;
    
    ULabel                                      *mLabelTitle;
    ULabel                                      *mLabelValue;
    
    USlider                                     *mSlider;
    
    FString                                     mTitle;
    
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void								SetMinMax(float pMin, float pMax);
    
    UMenuPane                                   *mControlPane;
    
    
    UButton                                     *mButtonMinAdd1;
    UButton                                     *mButtonMinSub1;
    
    UButton                                     *mButtonMaxAdd1;
    UButton                                     *mButtonMaxSub1;
    
    UButton                                     *mButtonRangeShrink;
    
    UButton                                     *mButtonDisplayMinMax;
	UButton                                     *mButtonSetZero;
	UButton                                     *mButtonSetOne;
    UButton                                     *mButtonSetHalf;
    UButton                                     *mButtonSetRandom;

	UButton                                     *mButtonExtraSetZero;
	UButton                                     *mButtonExtraSetOne;
    
    virtual void                                SetTarget(float *pTarget);
    float                                       *mTarget;
    
    virtual void                                Notify(void *pSender);
    
    virtual void                                UpdateText();
    
    virtual void                                Update();
    virtual void                                Draw();
};

class UStepper : public UMenuItem
{
public:
    
    UStepper(const char *pTitle, int pStartValue=0);
    UStepper();
    virtual ~UStepper();
    
    virtual void                                Update();
    virtual void                                Draw();
    
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    //virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                Notify(void *pSender);
    
    ULabel                                      *mLabelValue;
    ULabel                                      *mLabelTitle;
    
    void                                        SetTitleText(const char *pTitleText);
    void                                        SetValueText(int pValue);
    
    URoundedRect                                mRectBack;
    URoundedRect                                mRectBackShading;
    
    
    UButton                                     *mButtonZero;
    
	UButton                                     *mButtonM10;
	UButton                                     *mButtonM;
    UButton                                     *mButtonAmount;
	UButton                                     *mButtonP;
	UButton                                     *mButtonP10;
    
    int                                         mButtonTimer[2];
    
    
    
    void                                        ModifyValue(int pAmount);
    
    
    virtual void                                SetTarget(int *pTarget);
    virtual void                                SetValue(int pValue);
    
    int                                         *mTarget;
    int                                         mValue;
    
};

#endif /* defined(___015_Fleet_XP__UMenuStyleExtended__) */
