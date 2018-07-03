//
//  UMenuStyle.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UMenuStyle.h"
#include "FApp.h"
#include "UNode.h"
#include "UMainCanvas.h"
#include "UMenu.h"

UMenuItem::UMenuItem()
{
    mMenuRow = 0;
    mMenuPtr = 0;
    
    mMenuItemWidthSlots = 1;
    mMenuItemHeightSlots = 1;
    
    mMenuItemIsPane = false;
    mMenuItemIsRow = false;
    
    //FView::
    SetFrame(0.0f, 0.0f, 64.0f, UTIL_MENU_ROW_HEIGHT);
}

UMenuItem::~UMenuItem()
{
    
}

void UMenuItem::SetText(const char *pText)
{
    mText = pText;
}

void UMenuItem::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    FView::SetFrame(pX, pY, pWidth, pHeight);
}


void UMenuItem::BubbleUpLayoutMessage()
{
    if(mParent)
    {
        //UTIL_ACTION_LAYOUT_SUBVIEWS
        Notify(this, UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS, mParent);
    }
}

//virtual void                                Update();

URoundedRect::URoundedRect()
{
    SetRect(0.0f, 0.0f, 44.0f, 44.0f);
    mCornerRadius = 12;mCornerPointCount = 12;
    mRoundBottom = true;mRoundRight = true;mRoundLeft = true;mSquare = false;
    SetColorTop(0.9575f, 0.96f, 0.9589f);
    SetColorBottom(0.875f, 0.0f, 0.0f);
    mRefresh = true;
}

URoundedRect::~URoundedRect()
{
    
}

void URoundedRect::Generate()
{
    float *aDirX = new float[mCornerPointCount];
    float *aDirY = new float[mCornerPointCount];
    
    for(int i=0;i<mCornerPointCount;i++)
    {
        float aPercent = ((float)(i + 1)) / (mCornerPointCount + 2);
        float aAngle = 0.0f + (0.0f - 90.0f) * aPercent;
        
        aDirX[i] = Sin(aAngle) * mCornerRadius;
        aDirY[i] = -Cos(aAngle) * mCornerRadius;
    }
    
    mNodeList.Reset();
    int aWriteIndex = 0;
    
    float aStartX = X1();
    float aStartY = Y1();
    float aEndX = X4();
    float aEndY = Y4();
    
    if (mSquare) {
        mNodeList.SetXY(aWriteIndex++, aStartX, aStartY);
        mNodeList.SetXY(aWriteIndex++, aEndX, aStartY);
        mNodeList.SetXY(aWriteIndex++, aStartX, aEndY);
        mNodeList.SetXY(aWriteIndex++, aEndX, aEndY);
    } else {
        mNodeList.SetXY(aWriteIndex++, aStartX + mCornerRadius, aStartY);
        mNodeList.SetXY(aWriteIndex++, aEndX - mCornerRadius, aStartY);
        for(int i=0;i<mCornerPointCount;i++)
        {
            float aDX = aDirX[i];
            float aDY = aDirY[i];
            
            if(mRoundLeft)
            {
                mNodeList.SetXY(aWriteIndex++, (aStartX + mCornerRadius) + aDX, (aStartY + mCornerRadius) + aDY);
            }
            else
            {
                mNodeList.SetXY(aWriteIndex++, aStartX, (aStartY + mCornerRadius) + aDY);
            }
            
            if(mRoundRight)
            {
                mNodeList.SetXY(aWriteIndex++, (aEndX - mCornerRadius) - aDX, (aStartY + mCornerRadius) + aDY);
            }
            else
            {
                mNodeList.SetXY(aWriteIndex++, aEndX, (aStartY + mCornerRadius) + aDY);
            }
        }
        
        mNodeList.SetXY(aWriteIndex++, aStartX, aStartY + mCornerRadius);
        mNodeList.SetXY(aWriteIndex++, aEndX, aStartY + mCornerRadius);
        
        if(mRoundBottom == true)
        {
            mNodeList.SetXY(aWriteIndex++, aStartX, aEndY - mCornerRadius);
            mNodeList.SetXY(aWriteIndex++, aEndX, aEndY - mCornerRadius);
            
            for(int i=(mCornerPointCount-1);i>=0;i--)
            {
                float aDX = aDirX[i];
                float aDY = aDirY[i];
                
                if(mRoundLeft)mNodeList.SetXY(aWriteIndex++, (aStartX + mCornerRadius) + aDX, (aEndY - mCornerRadius) - aDY);
                else mNodeList.SetXY(aWriteIndex++, aStartX, (aEndY - mCornerRadius) - aDY);
                
                if(mRoundRight)mNodeList.SetXY(aWriteIndex++, (aEndX - mCornerRadius) - aDX, (aEndY - mCornerRadius) - aDY);
                else mNodeList.SetXY(aWriteIndex++, aEndX, (aEndY - mCornerRadius) - aDY);
            }
            
            mNodeList.SetXY(aWriteIndex++, aStartX + mCornerRadius, aEndY);
            mNodeList.SetXY(aWriteIndex++, aEndX - mCornerRadius, aEndY);
        }
        else
        {
            mNodeList.SetXY(aWriteIndex++, aStartX, aEndY);
            mNodeList.SetXY(aWriteIndex++, aEndX, aEndY);
        }
    }
    
    delete [] aDirX;
    delete [] aDirY;
    
    float aHeight = (aEndY - aStartY);
    
    for(int i=0;i<mNodeList.mCountNodes;i++)
    {
        float aPercent = (mNodeList.GetY(i) - aStartY) / aHeight;
        mNodeList.SetRGBA(i, mVertex[0].mR + (mVertex[3].mR - mVertex[0].mR) * aPercent, mVertex[0].mG + (mVertex[3].mG - mVertex[0].mG) * aPercent, mVertex[0].mB + (mVertex[3].mB - mVertex[0].mB) * aPercent, mVertex[0].mA + (mVertex[3].mA - mVertex[0].mA) * aPercent);
    }
}

void URoundedRect::Draw()
{
    if(mRefresh)
    {
        Generate();
        mRefresh = false;
    }
    
    mNodeList.DrawTriStrips();
    
}

void URoundedRect::Draw(float pOffsetX, float pOffsetY)
{
    Graphics::MatrixPush();
    Graphics::Translate(pOffsetX, pOffsetY);
    Draw();
    Graphics::MatrixPop();
}

void URoundedRect::Copy(URoundedRect *pRect, bool pIgnoreColor)
{
    if(pRect)
    {
        FDrawQuad::CopyXYZ(pRect);
        FDrawQuad::CopyUVW(pRect);
        
        if(pIgnoreColor == false)
        {
            FDrawQuad::CopyRGBA(pRect);
        }
        
        mCornerRadius = pRect->mCornerRadius;
        mCornerPointCount = pRect->mCornerPointCount;
        
        mRoundBottom = pRect->mRoundBottom;
        mRoundRight = pRect->mRoundRight;
        mRoundLeft = pRect->mRoundLeft;
        mSquare = pRect->mSquare;
    }
}

UButton::UButton(FSprite *pSprite) : UButton()
{
    mSprite = pSprite;
    
}

UButton::UButton(const char *pText) : UButton()
{
    mText = FString(pText).c();
}

UButton::UButton()
{
    mText = "Button";
    
    mSprite = 0;
    
    mRefresh = true;
    mChecked = false;
    mCheckBox = false;
    mDrawCheck = false;
    
    mTargetCheck = 0;
    
    mListenerPane = 0;
    
    
    mManualDownStateColor = false;
    
    mRectBack.mCornerRadius = 12;
    mRectBack.mCornerPointCount = 12;
    
    mRectFront.mCornerRadius = 8;
    mRectFront.mCornerPointCount = 8;
    
    mRectBack.SetColorTop(0.25f, 0.24f, 0.25f, 1.0f);
    mRectBack.SetColorBottom(0.39f, 0.39f, 0.39f, 1.0f);
    
    mRectFront.SetColorTop(0.435f, 0.433f, 0.43125f);
    mRectFront.SetColorBottom(0.35f, 0.34f, 0.35f, 1.0f);
    
    mRectCheckOutline.mCornerRadius = 6;
    mRectCheckOutline.mCornerPointCount = 6;
    
    mRectCheck.mCornerRadius = 4;
    mRectCheck.mCornerPointCount = 6;
    
    mRectCheckDown.mCornerRadius = 4;
    mRectCheckDown.mCornerPointCount = 6;
    
    
    mRectCheckOutline.SetColorTop(0.15f, 0.15f, 0.15f);
    mRectCheckOutline.SetColorBottom(0.08f, 0.12f, 0.15f);
    
    
    mRectCheck.SetColorTop(0.15f, 0.05f, 0.16f, 1.0f);
    mRectCheck.SetColorBottom(0.30f, 0.28f, 0.33f, 1.0f);
    
    mRectCheckDown.SetColorTop(0.14f, 0.92f, 0.20f, 1.0f);
    mRectCheckDown.SetColorBottom(0.10f, 0.80f, 0.13f, 1.0f);
    
    
}

UButton::~UButton()
{

}

void UButton::Draw()
{
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    if(mRefresh)
    {
        Generate();
        mRefresh = false;
    }
    
    bool aDown = false;
    
    if(mCheckBox)
    {
        if(mTouchDownInside || mChecked)
        {
            aDown = true;
        }
    }
    else
    {
        if(mTouchDownInside)
        {
            aDown = true;
        }
    }
    
    if(aDown)
    {
        mRectBackDown.Draw();
        mRectFrontDown.Draw();
    }
    else
    {
        mRectBack.Draw();
        mRectFront.Draw();
    }
    
    if(mCheckBox && mDrawCheck)
    {
        mRectCheckOutline.Draw();
        if(mChecked)mRectCheckDown.Draw();
        else mRectCheck.Draw();
    }
    
    //Graphics::BlendSetPremultiplied();
    Graphics::SetColor();
    
    
    float aCheckWidth = 42.0f;
    float aTextWidth = (mWidth - 4.0f);
    
    
    if(mDrawCheck)
    {
        aTextWidth -= aCheckWidth;
    }
    else
    {
        
    }
    
    if(aTextWidth < 24)aTextWidth = 24.0f;
    
    float aScale = 0.75f;
    
    float aWidthBase =  gAppBase->mSysFontBold.Width(mText.c());
    if((aWidthBase > mWidth) && (mWidth > 1.0f) && (aWidthBase > 1.0f))
    {
        aScale = (aTextWidth / aWidthBase);
    }
    
    if(aScale > 0.75f)aScale = 0.75f;
    aTextWidth *= aScale;
    
    
    
    
    if(mDrawCheck)
    {
        gAppBase->mSysFontBold.Center(mText.c(), mWidth - (aCheckWidth + aTextWidth * 0.5f), mHeight2, aScale);
    }
    else
    {
        gAppBase->mSysFontBold.Center(mText.c(), mWidth2, mHeight2, aScale);
    }

    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    if(mSprite)
    {
        if((mWidth > 1.0f) && (mHeight > 1.0f) && (mSprite->mWidth > 1.0f) && (mSprite->mHeight > 1.0f))
        {
            float aScaleW = mSprite->mWidth / mWidth;
            float aScaleH = mSprite->mHeight / mHeight;
            
            float aScale = aScaleW;
            if(aScaleH < aScale)aScale = aScaleH;
            if(aScale > 1.0f)aScale = 1.0f;
            
            mSprite->Draw(mWidth2, mHeight2, aScale, 0.0f);
            
        }
    }
}

void UButton::TouchUp(float pX, float pY, void *pData)
{
    if(mTouchCanceled == false)
    {
        
        if(mCheckBox)
        {
            mChecked = !mChecked;
            
            if(mTargetCheck)
            {
                *mTargetCheck = mChecked;
            }
        }
        
        if(mParent)
        {
            mParent->Notify(this);
            mParent->Notify(this, 1, 0);
        }
        
        if(mListenerPane)
        {
            mListenerPane->NotifyPane(this);
            mListenerPane->NotifyPane(this, 1, 0);
            //mListenerPane
        }
        
    }
}

void UButton::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    mRectBack.SetRect(0.0f, 0.0f, pWidth, pHeight);
    mRectBack.mRefresh = true;
    
    
    mRectFront.SetRect(0.0f + 3.0f, 0.0f + 3.0f, pWidth - 6.0f, pHeight - 6.0f);
    mRectFront.mRefresh = true;
    
    
    mRectBackDown.SetRect(0.0f, 0.0f, pWidth, pHeight);
    mRectBackDown.mRefresh = true;
    
    mRectFrontDown.SetRect(4.0f, 4.0f, pWidth - 8.0f, pHeight - 8.0f);
    mRectFrontDown.mRefresh = true;
    
    
    float aCheckX = mWidth - 28.0f;
    float aCheckY = 7.0f;
    
    float aCheckW = 22.0f;
    float aCheckH = mHeight - 15.0f;
    
    mRectCheckOutline.SetRect(aCheckX, aCheckY, aCheckW, aCheckH);
    mRectCheckOutline.mRefresh = true;
    
    aCheckX += 2;
    aCheckY += 2;
    aCheckW -= 4;
    aCheckH -= 4;
    
    mRectCheck.SetRect(aCheckX, aCheckY, aCheckW, aCheckH);
    mRectCheck.mRefresh = true;
    
    mRectCheckDown.SetRect(aCheckX, aCheckY, aCheckW, aCheckH);
    mRectCheckDown.mRefresh = true;
}




void UButton::StyleSetClear()
{
	mRectBack.SetColorTop(FColor(1.0f, 1.9f, 1.0f, 0.06f));
	mRectBack.SetColorBottom(FColor(1.0f, 0.96f, 1.0f, 0.02f));

	mRectFront.SetColorBottom(FColor(0.7f, 1.0f, 1.0f, 0.01f));
	mRectFront.SetColorTop(FColor(1.0f, 1.0f, 1.0f, 0.06f));

	mRectBackDown.SetColorTop(FColor(0x4bbaf4));
	mRectBackDown.SetColorBottom(FColor(0x081d6f));

	mRectFrontDown.SetColorTop(FColor(0x0b53c0));
	mRectFrontDown.SetColorBottom(FColor(0x1c64e7));

	mDrawCheck = false;
	mRefresh = true;
	mManualDownStateColor = true;
}


void UButton::StyleSetSegment()
{
    mRectBack.SetColorTop(0.22f, 0.22f, 0.32f);
    mRectBack.SetColorBottom(0.16f, 0.16f, 0.24f);
    
    mRectFront.SetColorBottom(0.14f, 0.14f, 0.32f);
    mRectFront.SetColorTop(0.18f, 0.18f, 0.28f);
    
    mRectBackDown.SetColorTop(FColor(0x4bbaf4));
    mRectBackDown.SetColorBottom(FColor(0x081d6f));
    
    mRectFrontDown.SetColorTop(FColor(0x0b53c0));
    mRectFrontDown.SetColorBottom(FColor(0x1c64e7));
    
    mDrawCheck = false;
    mRefresh = true;
    mManualDownStateColor = true;
}



void UButton::StyleSetSegmentLeft()
{
    mRectBack.mRoundRight = false;
    mRectFront.mRoundRight = false;
    StyleSetSegment();
    
}

void UButton::StyleSetSegmentMiddle()
{
    mRectBack.mSquare = true;
    mRectFront.mSquare = true;
    StyleSetSegment();
}

void UButton::StyleSetSegmentRight()
{
    mRectBack.mRoundLeft = false;
    mRectFront.mRoundLeft = false;
    StyleSetSegment();
}

void UButton::StyleSetClose()
{
    mRectBack.SetColorTop(0.36f, 0.36f, 0.36f, 1.0f);
    mRectBack.SetColorBottom(0.0f, 0.06f, 0.02f, 1.0f);
    
    mRectFront.SetColorTop(0.22f, 0.20f, 0.24f, 1.0f);
    mRectFront.SetColorBottom(0.24f, 0.25f, 0.29f, 1.0f);

	//mRefresh = true;
}

void UButton::StyleSetGreen()
{
	mRectBack.SetColorTop(0.01f, 0.45f, 0.04f);
	mRectBack.SetColorBottom(0.0f, 0.65f, 0.02f);

	mRectFront.SetColorTop(0.0f, 0.65f, 0.02f);
	mRectFront.SetColorBottom(0.01f, 0.56f, 0.0f);

	mRefresh = true;
}

void UButton::StyleSetBlue()
{
    mRectBack.SetColorTop(0.04f, 0.01f, 0.45f);
    mRectBack.SetColorBottom(0.0f, 0.02f, 0.65f);
    
    mRectFront.SetColorTop(0.1f, 0.02f, 0.65f);
    mRectFront.SetColorBottom(0.04f, 0.02f, 0.56f);
    
    mRefresh = true;
}

void UButton::StyleSetDark()
{
    
    mRectBack.SetColorTop(0.15f, 0.19f, 0.21f, 1.0f);
    mRectBack.SetColorBottom(0.30f, 0.28f, 0.30f, 1.0f);
    
    mRectFront.SetColorTop(0.335f, 0.333f, 0.33125f);
    mRectFront.SetColorBottom(0.25f, 0.24f, 0.25f, 1.0f);
    
    
    
    
    
}

void UButton::StyleSetOrange()
{
    mRectBack.SetColorTop(0.9000f, 0.6673f, 0.2182f, 1.0000f);
    mRectBack.SetColorBottom(0.9600f, 0.4091f, 0.1091f, 1.0000f);
    
    mRectFront.SetColorTop(1.000f, 0.5091f, 0.2091f, 1.0000f);
    mRectFront.SetColorBottom(0.9600f, 0.5673f, 0.0182f, 1.0000f);
}

void UButton::StyleSetRed()
{
    mRectBack.SetColorTop(0.45f, 0.01f, 0.04f);
    mRectBack.SetColorBottom(0.65f, 0.0f, 0.02f);
    
    mRectFront.SetColorTop(0.65f, 0.0f, 0.02f);
    mRectFront.SetColorBottom(0.56f, 0.01f, 0.0f);
}

void UButton::StyleSetYellow()
{
    mRectBack.SetColorTop(0.95f, 0.1f, 0.06f);
    mRectBack.SetColorBottom(0.80f, 0.87f, 0.04f);
    
    mRectFront.SetColorTop(0.92f, 0.80f, 0.03f);
    mRectFront.SetColorBottom(0.87f, 0.87f, 0.1f);
}




void UButton::StyleSetCheckBox()
{
    mRectBack.SetColorTop(0.46f, 0.46f, 0.46f, 1.0f);
    mRectBack.SetColorBottom(0.52f, 0.48f, 0.52f, 1.02f);
    
    mRectFront.SetColorTop(0.44f, 0.44f, 0.44f, 1.0f);
    mRectFront.SetColorBottom(0.35f, 0.35f, 0.35f, 1.0f);
    
    
    mDrawCheck = true;
    
    mRectBackDown.SetColorTop(0.42f, 0.42f, 0.42f, 1.0f);
    mRectBackDown.SetColorBottom(0.475f, 0.475f, 0.475f, 1.0f);
    
    mRectFrontDown.SetColorTop(0.74f, 0.64f, 0.64f, 1.0f);
    mRectFrontDown.SetColorBottom(0.55f, 0.545f, 0.4885f, 1.0f);
    
    
    
    mCheckBox = true;
    
    mRefresh = true;
    mManualDownStateColor = true;
    
    mRefresh = true;
}

void UButton::SetTargetCheck(bool *pTargetCheck)
{
    mTargetCheck = pTargetCheck;
    if(mTargetCheck)
    {
        mChecked = (*mTargetCheck);
    }
}

void UButton::Generate()
{
    mRectBackDown.Copy(&mRectBack, mManualDownStateColor);
    mRectBackDown.ColorLightenAll(0.1f);
    mRectBackDown.mRefresh = true;
    
    mRectFrontDown.Copy(&mRectFront, mManualDownStateColor);
    mRectFrontDown.ColorFlipV();
    mRectFrontDown.ColorDarkenAll(0.05f);
    mRectFrontDown.mRefresh = true;
}

ULabel::ULabel(const char *pText)
{
    mText = pText;
    
    mFont = &(gAppBase->mSysFont);
    
    mBold = false;
    
    
    mAutoScale = true;
    mScale = 0.72f;
    
    mConsumesTouches = false;
    
    mAlign = 0;
    mAlignPadding = 2;
    
    mTextWidth = 0.0f;
}

ULabel::ULabel()
{
    mText = "Label";
    
    mFont = &(gAppBase->mSysFontBold);
    
    mBold = false;
    
    
    mAutoScale = true;
    mScale = 0.75f;
    
    
    mConsumesTouches = false;
    
    mAlign = 0;
    mAlignPadding = 2;
    
    mTextWidth = 0.0f;
    
}

ULabel::~ULabel()
{
    
}

void ULabel::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    
    
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    SetText(FString(mText.c()).c());
    
    
    
}

void ULabel::Draw()
{
    //Graphics::BlendSetAlpha();
    //Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.2f);
    //Graphics::DrawRect(2, 2, mWidth - 4, mHeight - 4);
    
    
    
    //Graphics::BlendSetPremultiplied();
    Graphics::SetColor();
    
    if(mAlign == -1)mFont->Center(mText.c(), mTextWidth / 2.0f + (float)mAlignPadding, mHeight2, mScale);
    else if(mAlign == 0)mFont->Center(mText.c(), mWidth2, mHeight2);
    else mFont->Center(mText.c(), mWidth - (mTextWidth / 2.0f + (float)mAlignPadding), mHeight2, mScale);
    
    Graphics::BlendSetAlpha();
    
    
    //Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 1);
}

void ULabel::SetText(const char *pText)
{
    //if(mBold)mFont = &(gAppBase->mSysFontBold);
    //else mFont = &(gAppBase->mSysFont);
    
    UMenuItem::SetText(pText);
    
    //mFont = &(gAppBase->mSysFont);
    
    mText = FString(pText).c();
    
    
    if(mAutoScale)
    {
        float aWidthBase = mFont->Width(mText.c());
        
        if((aWidthBase > mWidth) && (mWidth > 1.0f))
        {
            mScale = (mWidth / aWidthBase);
        }
        
    }
    
    if(mScale > 0.75f)mScale = 0.75f;
    
    mTextWidth = mFont->Width(pText, mScale);
}

void ULabel::AlignLeft()
{
    mAlign = -1;
}

void ULabel::AlignCenter()
{
    mAlign = 0;
}

void ULabel::AlignRight()
{
    mAlign = 1;
}

ULabelStat::ULabelStat(const char *pTitle, float pTitleSpacing, int pGridSlotCount) : ULabelStat()
{
    mTitleSpacing = pTitleSpacing;
    
    mMenuItemWidthSlots = pGridSlotCount;
    
    mTitleSpacing = pTitleSpacing;
    
    SetText(pTitle);
}

ULabelStat::ULabelStat()
{
    mTitleSpacing = 0;
    
    SetFrame(0.0f, 0.0f, 100.0f, UTIL_MENU_ROW_HEIGHT);
    
    mTitleSpacing = 0;
    
    mFont = &(gAppBase->mSysFont);
    mTargetInt = 0;
    mTargetFloat = 0;
    
    mValueText = "-";
    mTitleText = "???";
}

ULabelStat::~ULabelStat()
{
    
}

void ULabelStat::Draw()
{
    //Graphics::BlendSetPremultiplied();
    Graphics::SetColor();
    
    float aFontHeight = mFont->mPointSize;
    float aY = mHeight2 - (aFontHeight / 2.0f);
    
    mFont->Draw(mTitleText.c(), 2.0f, aY);
    mFont->Draw(mValueText.c(), mTitleSpacing, aY);
    
    Graphics::BlendSetAlpha();
}

void ULabelStat::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
}

void ULabelStat::SetText(const char *pText)
{
    UMenuItem::SetText(pText);
}

void ULabelStat::SetValueText(const char *pText)
{
    mValueText = FString(pText).c();
}

void ULabelStat::SetTargetFloat(float *pTarget)
{
    mTargetFloat = pTarget;
    
    if(mTargetFloat)
    {
        FString aFloatString;
        
        if((*pTarget) >= 10.0f)
        {
            aFloatString = FString(*pTarget, 2);
        }
        else
        {
            aFloatString = FString(*pTarget, 4);
        }
        SetValueText(aFloatString.c());
    }
    else
    {
        SetValueText("-");
    }
}

void ULabelStat::SetTargetInt(int *pTarget)
{
    mTargetInt = pTarget;
    
    if(mTargetInt)
    {
        FString aIntString = FString((int)(*pTarget)).c();
        SetValueText(aIntString.c());
    }
    else
    {
        SetValueText("-");
    }
}



USegment::USegment(int pSegmentCount)
{
    mMenuItemWidthSlots = pSegmentCount;
    
    mTarget = 0;
    mSelectedIndex = -1;
    mSegmentCount = pSegmentCount;
    mButton = new UButton*[mSegmentCount];
    
    for(int i=0;i<mSegmentCount;i++)
    {
        UButton *aButton = new UButton();
        mButton[i] = aButton;
        AddSubview(aButton);
        
        if(i == 0)
        {
            if(pSegmentCount <= 1)
            {
                aButton->StyleSetSegment();
            }
            else
            {
                aButton->StyleSetSegmentLeft();
            }
            
            aButton->mChecked = true;
            
        }
        else if(i == (pSegmentCount - 1))
        {
            aButton->StyleSetSegmentRight();
        }
        else
        {
            aButton->StyleSetSegmentMiddle();
        }
    }
}

//USegment::USegment(float pX, float pY, float pWidth, int pSegmentCount) : USegment(pSegmentCount)
//{
//    SetUp(pX, pY, pWidth);
//}

void USegment::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    float aTotalWidth = mWidth;
    float aX = 0.0f;
    float aItemWidth = aTotalWidth;
    
    if(mSegmentCount == 1)
    {
        
    }
    else
    {
        aItemWidth /= ((float)mSegmentCount);
    }
    
    for(int i=0;i<mSegmentCount;i++)
    {
        UButton *aButton = mButton[i];
        aButton->SetMenuItemFrame(aX, 0.0f, aItemWidth, mHeight);
        aButton->mCheckBox = true;
        aX += (aItemWidth);
    }
    
}

USegment::~USegment()
{
    delete [] mButton;
    mButton = 0;
}

void USegment::SetTitle(int pSegment, const char *pText)
{
    if((pSegment >= 0) && (pSegment < mSegmentCount))
    {
        mButton[pSegment]->SetText(pText);
    }
}

void USegment::SetTitles(const char *pTitle1, const char *pTitle2, const char *pTitle3, const char *pTitle4, const char *pTitle5, const char *pTitle6)
{
    SetTitle(0, pTitle1);
    SetTitle(1, pTitle2);
    SetTitle(2, pTitle3);
    SetTitle(3, pTitle4);
    SetTitle(4, pTitle5);
    SetTitle(5, pTitle6);
}

void USegment::SetTarget(int *pTarget)
{
    mTarget = pTarget;
    if(mTarget)
    {
        int aIndex = (*pTarget);
        
        if((aIndex >= 0) && (aIndex < mSegmentCount))
        {
            mSelectedIndex = aIndex;
            
            for(int i=0;i<mSegmentCount;i++)mButton[i]->mChecked = false;
            mButton[mSelectedIndex]->mChecked = true;
        }
    }
}

void USegment::Notify(void *pSender)
{
    for(int aCheckIndex=0;aCheckIndex<mSegmentCount;aCheckIndex++)
    {
        if(pSender == mButton[aCheckIndex])
        {
            mSelectedIndex = aCheckIndex;
            
            for(int i=0;i<mSegmentCount;i++)mButton[i]->mChecked = false;
            mButton[mSelectedIndex]->mChecked = true;
            
            if(mTarget)
            {
                *mTarget = mSelectedIndex;
            }
        }
    }
    
    if(mParent)
    {
        mParent->Notify(this);
    }
}

USlider::USlider()
{
    
    mPreviousDrawMin = -1;
    mPreviousDrawMax = -1;
    
    mValue = 0.0f;
    mTargetValue = 0;
    
    mBarHeight = 10.0f;
    
    mMenuItemWidthSlots = 3;
    
    mBaseSlider = new FSlider();
    mBaseSlider->SetFrame(0.0f, 0.0f, mWidth, mHeight);
    mBaseSlider->SetThumb(0.0f, 0.0f, 40.0f, mHeight);
    mBaseSlider->mDrawManual = true;
    AddSubview(mBaseSlider);
    
    
    FRect aRectBar = FRect(6.0f, mHeight / 2.0f - mBarHeight / 2.0f, mWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(0.0f, 0.0f, mBaseSlider->mThumbWidth, mBaseSlider->mThumbHeight);
    
    mRectBar.mCornerRadius = 5.0f;
    mRectBar.mCornerPointCount = 6;
    
    mRectBar.SetColorTop(0.12f, 0.14f, 0.19f);
    mRectBar.SetColorBottom(0.05f, 0.02f, 0.06f);
    mRectBar.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);
    
    mRectThumb.mCornerRadius = 10.0f;
    mRectThumb.mCornerPointCount = 12;
    //mRectThumb.SetColorTop(1.0f, 0.45f, 0.1f);
    //mRectThumb.SetColorBottom(0.96f, 0.55f, 0.10f);
    mRectThumb.SetColorTop(0.6f, 0.63f, 0.66f);
    mRectThumb.SetColorBottom(0.54f, 0.55f, 0.60f);
    
    
    mRectThumb.SetRect(0.0f, 0.0f, mBaseSlider->mThumbWidth, mBaseSlider->mThumbHeight);
    
    
    mRectBarShine.Copy(&mRectBar);// SetRect(7.0f, mHeight / 2.0f - mBarHeightInner / 2.0f, mWidth - 14, mBarHeightInner);
    mRectBarShine.SetColorTop(1.0f, 1.0f, 1.0f, 0.25f);
    mRectBarShine.SetColorBottom(1.0f, 0.95f, 0.9f, 0.0f);
    
    
    mRectThumbShine.Copy(&mRectThumb);
    mRectThumbShine.SetColorTop(1.0f, 1.0f, 1.0f, 0.40f);
    mRectThumbShine.SetColorBottom(1.0f, 1.0f, 1.0f, 0.0f);
}

USlider::~USlider()
{
    
}

void USlider::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    mBaseSlider->SetFrame(0.0f, 0.0f, mWidth, mHeight);
    
    mBaseSlider->mThumbHeight = mHeight;
    
    
    FRect aRectBar = FRect(6.0f, mHeight / 2.0f - mBarHeight / 2.0f, mWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(0.0f, 0.0f, mBaseSlider->mThumbWidth, mBaseSlider->mThumbHeight);
    
    mRectBar.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);
    mRectBarShine.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);
    
    mRectThumb.SetRect(0.0f, 0.0f, mBaseSlider->mThumbWidth, mBaseSlider->mThumbHeight);
    mRectThumbShine.SetRect(0.0f, 0.0f, mBaseSlider->mThumbWidth, mBaseSlider->mThumbHeight);
    
    mRectBar.mRefresh = true;
    mRectBarShine.mRefresh = true;
    mRectThumb.mRefresh = true;
    mRectThumbShine.mRefresh = true;
    
    mBaseSlider->SetValue(mValue);
    
    
}

void USlider::Draw()
{
    mRectBar.Draw();
    mRectBarShine.Draw();
    
    mRectThumb.Draw(mBaseSlider->mThumbX, 0.0f);
    mRectThumbShine.Draw(mBaseSlider->mThumbX, 0.0f);
    
    
    bool aUpdateText = false;
    
    if(mBaseSlider)
    {
        if(mBaseSlider->mMin != mPreviousDrawMin)
        {
            mPreviousDrawMin = mBaseSlider->mMin;
            aUpdateText = true;
        }
        
        if(mBaseSlider->mMax != mPreviousDrawMax)
        {
            mPreviousDrawMax = mBaseSlider->mMax;
            aUpdateText = true;
        }
    }
    
    if(mBaseSlider)
    {
        if(aUpdateText || true)
        {
            int aDecimals = 1;
            
            float aRange = mBaseSlider->mMax - mBaseSlider->mMin;
            
            if(aRange <= 2.0f)
            {
                aDecimals = 2;
                
                if(aRange < 0.5f)
                {
                    aDecimals = 4;
                }
                
            }
            
            /*
            FString aSliderText = FString(mBaseSlider->mMin, aDecimals) + FString(" - ") + FString(mBaseSlider->mMax, aDecimals);
            float aSliderTextWidth = gAppBase->mSysFont.Width(aSliderText.c());
            
            float aX = (mBaseSlider->mThumbX + (mBaseSlider->mThumbWidth / 2.0f));
            aX -= (aSliderTextWidth / 2.0f);
            
            if(aX < 0.0f)aX = 0.0f;
            if(aX > (mBaseSlider->mWidth - aSliderTextWidth))aX = (mBaseSlider->mWidth - aSliderTextWidth);
            
            float aY = mHeight2 - 8.0f;
            
			Graphics::SetColor(0.7f);
            gAppBase->mSysFont.Center(aSliderText.c(), mWidth2, aY, 0.75f);
            */
            
			Graphics::SetColor();
            
            
            //aUpdateText
            
        }
    }
    
    //mAllowMultipleExpandedSubpanes
    
    
    //mAllowMultipleExpandedSubpanes
    
    
    //OutlineRect(mBaseSlider->mX, mBaseSlider->mY, mBaseSlider->mWidth, mBaseSlider->mHeight, 2.0f);
    
    //gAppBase->mSysFont24.Center(mText.c(), mWidth2, mHeight2);
}

void USlider::SetValue(float *pTargetValue)
{
    mTargetValue = pTargetValue;
    if(mTargetValue)
    {
        mBaseSlider->ForceValue(*mTargetValue);
        mValue = mBaseSlider->GetValue();
    }
    else
    {
        if((mValue < mBaseSlider->mMin) || (mValue > mBaseSlider->mMax))
        {
            mValue = mBaseSlider->mMin;
            mBaseSlider->ForceValue(mValue);
        }
    }
}

float USlider::GetValue()
{
    return mBaseSlider->GetValue();
}


void USlider::Notify(void *pSender)
{
    if((pSender == mBaseSlider) && (mBaseSlider != 0))
    {
        mValue = mBaseSlider->mValue;
        
        if(mTargetValue)
        {
            *mTargetValue = mValue;
        }
        
        if(mParent)
        {
            mParent->Notify(this);
        }
    }
}

















