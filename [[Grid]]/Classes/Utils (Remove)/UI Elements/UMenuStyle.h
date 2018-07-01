//
//  UMenuStyle.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UMenuStyle__
#define ___015_Fleet_XP__UMenuStyle__

#define UTIL_MENU_ROW_HEIGHT 38.0f

#define UTIL_MENU_SPACING_H 6.0f
#define UTIL_MENU_SPACING_V 3.0f

#define UTIL_MENU_SPACING_H_SIDES 4.0f

#define UTIL_MENU_SPACING_V_TOP 2.0f
#define UTIL_MENU_SPACING_V_BOTTOM 2.0f

#define UTIL_MENU_PANE_HEADER_HEIGHT 36.0f
#define UTIL_MENU_DEFAULT_WIDTH ((gDeviceWidth >= 1580) ? (400.0f) : (340.0f))
#define UTIL_MENU_TOOLBAR_HEIGHT 42.0f

#include "FPrimitive.h"
#include "FColor.h"
#include "FView.h"
#include "FDrawQuad.h"
#include "FSlider.h"

class UNode;
class UMenuRow;
class UMenuPane;
class UButton;
class FFont;
class UMenu;

class UMenuItem : public FView
{
public:
    
    UMenuItem();
    virtual ~UMenuItem();
    
    
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    
    virtual void                                SetText(const char *pText);
    FString                                     mText;
    
    void                                        BubbleUpLayoutMessage();
    
    UMenuRow                                    *mMenuRow;
    UMenu                                       *mMenuPtr;
    
    int                                         mMenuItemWidthSlots;
    int                                         mMenuItemHeightSlots;
    
	bool                                        mMenuItemIsPane;
    bool                                        mMenuItemIsRow;
};

class URoundedRect : public FDrawQuad
{
public:
    URoundedRect();
    virtual ~URoundedRect();
    
	virtual void                                Draw();
	virtual void                                Draw(float pOffsetX, float pOffsetY);
    
	virtual void                                Copy(URoundedRect *pRect, bool pIgnoreColor = false);
    
    float                                       mCornerRadius;
    
    int                                         mCornerPointCount;
    
    bool                                        mRoundBottom;
    bool                                        mRoundRight;
    bool                                        mRoundLeft;
    
    bool                                        mSquare;
    
    bool                                        mRefresh;
    
    void                                        Generate();
    
    FDrawNodeList                               mNodeList;
    
};

class UButton : public UMenuItem
{
public:
    
    UButton(FSprite *pSprite);
    UButton(const char *pText);
    UButton();
    virtual ~UButton();
    
    //virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    
	//virtual void								SetUp(float pX, float pY);
	//virtual void                                SetUp(float pX, float pY, float pWidth);
	//virtual void								SetUp(float pX, float pY, float pWidth, const char *pTitle);
    
    //virtual void								SetTitle(const char *pText);

    void                                        StyleSetSegment();
    void                                        StyleSetSegmentLeft();
    void                                        StyleSetSegmentMiddle();
    void                                        StyleSetSegmentRight();
    void                                        StyleSetClose();
	void                                        StyleSetGreen();
	void                                        StyleSetBlue();
	void                                        StyleSetClear();

    void                                        StyleSetDark();
    void                                        StyleSetOrange();
    void                                        StyleSetRed();
    void                                        StyleSetYellow();
    
    void                                        StyleSetCheckBox();
    
	virtual void                                Draw();
    virtual void                                TouchUp(float pX, float pY, void *pData);
    
	//FString                                     mText;
    
    FSprite                                     *mSprite;

    URoundedRect                                mRectBack;
    URoundedRect                                mRectBackDown;
    URoundedRect                                mRectFront;
    URoundedRect                                mRectFrontDown;
    
    
    URoundedRect                                mRectCheckOutline;
    URoundedRect                                mRectCheck;
    URoundedRect                                mRectCheckDown;
    
    
    UMenuPane                                   *mListenerPane;
    
    void                                        SetTargetCheck(bool *pTargetCheck);
    bool                                        *mTargetCheck;
    
    bool                                        mCheckBox;
    bool                                        mChecked;
    bool                                        mDrawCheck;
    
    
    bool                                        mRefresh;
    bool                                        mManualDownStateColor;

    void                                        Generate();
};

class USegment : public UMenuItem
{
public:
    USegment(int pSegmentCount);
    USegment(float pX, float pY, float pWidth, int pSegmentCount);
    virtual ~USegment();
    
    //virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    
    virtual void                                Notify(void *pSender);
    
    
    //void                                        SetUp(float pX, float pY, float pWidth);
    void                                        SetTitle(int pSegment, const char *pTitle);
    void                                        SetTitles(const char *pTitle1, const char *pTitle2=0, const char *pTitle3=0, const char *pTitle4=0, const char *pTitle5=0, const char *pTitle6=0);
    
    virtual void                                SetTarget(int *pTarget);
    int                                         *mTarget;
    
    UButton                                     **mButton;
    
    int                                         mSegmentCount;
    int                                         mSelectedIndex;
};

class USlider : public UMenuItem// FSlider //UMenuItem
{
public:
    USlider();
    virtual ~USlider();
    
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                Notify(void *pSender);
    
    //void                                        SetUp(float pX, float pY, float pWidth, const char *pText);
    
    float                                       GetValue();
    void                                        SetValue(float *pTargetValue);
    float                                       *mTargetValue;
    float                                       mValue;
    
    FSlider                                     *mBaseSlider;
    float                                       mBarHeight;
    float                                       mBarHeightInner;
    
    URoundedRect                                mRectBar;
    URoundedRect                                mRectBarShine;
    
    URoundedRect                                mRectThumb;
    URoundedRect                                mRectThumbShine;
    
    virtual void                                Draw();
    
    float                                       mPreviousDrawMin;
    float                                       mPreviousDrawMax;
    
};


class ULabel : public UMenuItem
{
public:
    ULabel(const char *pText);
    ULabel();
    virtual ~ULabel();
    
    virtual void                                Draw();
    
    
    
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                SetText(const char *pText);
    
    float                                       mTextWidth;
    
    FFont                                       *mFont;
    
    bool                                        mBold;
    
    bool                                        mAutoScale;
    float                                       mScale;
    
    
    int                                         mAlign;
    int                                         mAlignPadding;
    
    void                                        AlignLeft();
    void                                        AlignCenter();
    void                                        AlignRight();
};

class ULabelStat : public UMenuItem
{
public:
    ULabelStat(const char *pTitle, float pTitleSpacing, int pGridSlotCount=1);
    ULabelStat();
    virtual ~ULabelStat();
    
    virtual void                                Draw();
    
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    //virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight);
    
    //virtual void                                SetTitle(const char *pText);
    //virtual void                                SetTitle(char *pText){SetTitle((const char *)pText);}
    //virtual void                                SetTitle(FString pText){SetTitle(((const char *)pText.c()));}
    
    virtual void                                SetText(const char *pText);
    
    virtual void                                SetValueText(const char *pText);
    virtual void                                SetValueText(char *pText){SetValueText((const char *)pText);}
    virtual void                                SetValueText(FString pText){SetValueText(((const char *)pText.c()));}
    
    virtual void                                SetTargetFloat(float *pTarget);
    float                                       *mTargetFloat;
    
    virtual void                                SetTargetInt(int *pTarget);
    int                                         *mTargetInt;
    
    float                                       mTitleSpacing;
    
    FString                                     mTitleText;
    FString                                     mValueText;
    
    FFont                                       *mFont;
    
};







#endif


