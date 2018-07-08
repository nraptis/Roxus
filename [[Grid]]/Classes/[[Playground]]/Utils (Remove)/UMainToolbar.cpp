//
//  UMainToolbar.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/13/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UMainToolbar.h"
#include "UMainCanvas.h"
#include "UMenu.h"
#include "UImagePicker.h"
#include "core_includes.h"
#include "FApp.h"

UMainToolbar *gUtilToolbar = 0;

UMainToolbar::UMainToolbar()
{
    SetStaticTransform(true);
    
    gUtilToolbar = this;
    
    mInsertX = 0;
    mInsertY = 0;
    
    mExpandWidth = mWidth;
    mExpandHeight = mHeight;
    
    mIsExpanded = true;
    mDragFrameMode = true;
    
    
    float aPaneHeight = 30.0f;
    
    float aWidth = gUtils->mWidth;
    if(aWidth > 700.0f)aWidth = 700.0f;
    float aWidthButtons = (aWidth - 120.0f);
    
    
    float aHeight = (aPaneHeight + aPaneHeight + 4.0f);
    
    SetFrame(20.0f, 0.0f, aWidth, aHeight);
    

	mPaneTop = new UMenuPane();
	AddSubview(mPaneTop);

	mPaneLower = new UMenuPane();
	AddSubview(mPaneLower);




    
    //mMaxRowCount = 9;
    
    
    
    
    mRect1.SetRect(0.0f, 0.0f, aHeight, mHeight);
    mRect1.mCornerRadius = 10.0f;
    
    mRect1.SetColorTop(0.06f, 0.10f, 0.32f, 0.4f);
    mRect1.SetColorBottom(0.14f, 0.16f, 0.2f, 0.4f);
    
    mRect2.SetRect(2.0f, 2.0f, mWidth - 4.0f, aHeight - 4.0f);
    mRect2.mCornerRadius = 8.0f;
    mRect2.SetColorTop(0.07f, 0.15f, 0.20f, 0.2f);
    mRect2.SetColorBottom(0.03f, 0.07f, 0.15f, 0.6f);
    

    mButtonCollapse = new UButton("+");
    
    
    mButtonNodeEditor = new UButton("(Node)");
    mButtonTimelineEditor = new UButton("(Time)");
	mButtonMotionEditor = new UButton("(Move)");
    mButtonParticleEditor = new UButton("(Part)");
	mButtonParentPanel = new UButton("(Parent)");
	mButtonCanvasPanel = new UButton("(World)");
	mButtonTransform = new UButton("(XFrm)");

	//  mButtonMotionEditor, mButtonParticleEditor
	mPaneTop->AddLine(mButtonCollapse, mButtonCanvasPanel, mButtonNodeEditor, mButtonMotionEditor, mButtonParticleEditor, mButtonParentPanel, mButtonTimelineEditor, mButtonTransform);
	

	if(gEnvironment == ENV_WIN32)mPaneTop->SetMenuItemFrame(40.0f, 3.0f, (mWidth - 60.0f), aPaneHeight);
	else mPaneTop->SetMenuItemFrame(40.0f, 2.0f, aWidthButtons, aPaneHeight);
	
	mPaneTop->mDisableDraw = true;
	mPaneTop->LayoutSubviews();
    
	mSegmentMode = new USegment(4);
	mSegmentMode->SetTitles("[Pick]", "[XFrm]", "[Pan]", "[Lnk]", "Cur");
	mSegmentMode->SetTarget(&(gUtilWS->mMode));

    
	mButtonToggleOutlines = new UButton("Lines");
	mButtonToggleOutlines->mChecked = true;
	mButtonToggleOutlines->StyleSetCheckBox();
	//AddButton(mButtonToggleOutlines);

    mButtonToggleUpdates = new UButton("Update");
    mButtonToggleUpdates->mCheckBox = true;
    mButtonToggleUpdates->mChecked = true;
    mButtonToggleUpdates->StyleSetCheckBox();
    
    mButtonTogglePassTouches = new UButton("Touch");
    mButtonTogglePassTouches->mCheckBox = true;
    mButtonTogglePassTouches->StyleSetCheckBox();
    mButtonTogglePassTouches->SetTargetCheck(&(gUtils->mConsumesTouches));

    //mButtonTogglePassTouches
    
    

	mButtonNextFrame = new UButton("Frame[>]");
	//AddButton(mButtonNextFrame);


	mPaneLower->AddLine(mButtonToggleUpdates, mButtonNextFrame, mSegmentMode, mButtonToggleOutlines, mButtonTogglePassTouches);

    mButtonToggleUpdates->SetMenuItemFrame(mButtonToggleUpdates->mX, mButtonToggleUpdates->mY, mButtonToggleUpdates->mWidth, aPaneHeight);
    mSegmentMode->SetMenuItemFrame(mSegmentMode->mX, mSegmentMode->mY, mSegmentMode->mWidth, aPaneHeight);
    
    
    //mButtonToggleUpdates, mButtonNextFrame, mSegmentMode, mButtonToggleOutlines, mButtonTogglePassTouches
    

	mPaneLower->SetMenuItemFrame(mPaneTop->mX, mPaneTop->mY + mPaneTop->mHeight - 4.0f, mPaneTop->mWidth, mPaneTop->mHeight);
	mPaneLower->LayoutSubviews();
	mPaneLower->mDisableDraw = true;
    

	


}

UMainToolbar::~UMainToolbar()
{
    
}

void UMainToolbar::Update()
{
    
}

void UMainToolbar::Draw()
{
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    mRect1.Draw();
    mRect2.Draw();
}

void UMainToolbar::TouchDown(float pX, float pY, void *pData)
{
    
}

void UMainToolbar::TouchMove(float pX, float pY, void *pData)
{
    
}

void UMainToolbar::TouchUp(float pX, float pY, void *pData)
{
    
}

void UMainToolbar::TouchFlush()
{
    
}

void UMainToolbar::Notify(void *pSender)
{

	if(pSender == mSegmentMode)
	{

		gUtilWS->SetMode(mSegmentMode->mSelectedIndex);
		
	}

    if(pSender == mButtonCollapse)
    {
        if(gUtils->mIsExpanded)gUtils->Collapse();
        else gUtils->Expand();
    }
    
    if(pSender == mButtonNodeEditor)
    {
        
    }

    
    if(pSender == mButtonToggleUpdates)
    {
        if(mButtonToggleUpdates->mChecked)gUtils->mUpdatesAllowed = true;
        else gUtils->mUpdatesAllowed = false;
    }
    
    if(pSender == mButtonToggleOutlines)
    {
        gUtils->mDrawDisableAll = (!(gUtils->mDrawDisableAll));
    }
    
    if(pSender == mButtonNextFrame)
    {
        if(mButtonToggleUpdates)mButtonToggleUpdates->mChecked = false;
        gUtils->mUpdatesAllowed = false;
        gUtils->mUpdateOnce = true;
    }
    
    if(pSender == mButtonNodeEditor)
    {
        //gUtils->SpawnNodePlacementMenu();
    }

	if(pSender == mButtonMotionEditor)
	{
		gUtils->SpawnMotionMenu();
	}
    
    if(pSender == mButtonParticleEditor)
    {
        gUtils->SpawnParticleMenu();
    }
    
    if(pSender == mButtonTimelineEditor)
    {
        gUtils->SpawnTimelineMenu();
    }
    
	if(pSender == mButtonNodeEditor)
	{
		gUtils->SpawnNodeMenu();
	}

	if(pSender == mButtonTransform)
	{
		gUtils->SpawnTransformMenu();
	}

	if(pSender == mButtonCanvasPanel)
	{
		gUtils->SpawnCanvasMenu();
	}
    
	if(pSender == mButtonParentPanel)
	{
		gUtils->SpawnParentMenu();
	}

}

void UMainToolbar::Notify(void *pSender, int pID, void *pObject)
{
    /*
    if(pObject != 0)
    {
        if(pID == IMG_PICK_RESPONSE_SPRITE)
        {
            FSprite *aSprite = ((FSprite *)pObject);
            if(aSprite)
            {
                if(gUtils->mImagePickerUpdatesCurrentNode)
                {
                    if(gUtilsNode)
                    {
                        gUtilsNode->SetSprite(aSprite);
                        gUtils->mImagePickerUpdatesCurrentNode = false;
                    }
					else
					{
						gUtilWS->AddSpriteNode(aSprite);
					}
                }
                else
                {
					gUtilWS->AddSpriteNode(aSprite);
                }
            }
        }
        else if(pID == IMG_PICK_RESPONSE_SEQUENCE)
        {
            FSpriteSequence *aSequence = ((FSpriteSequence *)pObject);
            
            if(aSequence)
            {
                FSprite *aSprite = aSequence->Get();
                
                if(aSprite)
                {
                    if(gUtils->mImagePickerUpdatesCurrentNode)
                    {
                        if(gUtilsNode)
                        {
                            gUtilsNode->SetSpriteSequence(aSequence);
                            gUtils->mImagePickerUpdatesCurrentNode = false;
                        }
						else
						{
							gUtilWS->AddSequenceNode(aSequence);
						}
                    }
                    else
                    {
						gUtilWS->AddSequenceNode(aSequence);
                    }
                }
            }
        }
    }
    */
}

void UMainToolbar::SetSelectedNode(UNode *pNode)
{
    
}

void UMainToolbar::Expand()
{
    if(mIsExpanded == false)
    {
        SetFrame(mX, mY, mExpandWidth, mExpandHeight);
        
        mButtonCollapse->mText = "-";

		/*
        EnumList(FView, aView, mSubviews)
        {
            if(aView != mButtonCollapse)
            {
                aView->mHidden = false;
                aView->mEnabled = true;
            }
        }
		*/

        mIsExpanded = true;
        
        mRect1.SetRect(0.0f, 0.0f, mWidth, mHeight);
        mRect1.mRefresh = true;
        mRect2.SetRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f);
        mRect2.mRefresh = true;
    }
}

void UMainToolbar::Collapse()
{
    if(mIsExpanded == true)
    {
        mExpandWidth = mWidth;
        mExpandHeight = mHeight;
        
        mButtonCollapse->mText = "+";
        
		/*
		EnumList(FView, aView, mPaneTop->mSubviews)
		{
			if(aView != mButtonCollapse)
			{
				aView->mHidden = true;
				aView->mEnabled = false;
			}
		}

		
        EnumList(FView, aView, mSubviews)
        {
			if(aView != mPaneTop)
            {
                aView->mHidden = true;
                aView->mEnabled = false;
            }
        }
        
        SetFrame(mX, mY, UTIL_MENU_SPACING_H_SIDES + mButtonCollapse->mWidth + 48.0f, UTIL_MENU_SPACING_V_TOP + mButtonCollapse->mHeight + UTIL_MENU_SPACING_V_BOTTOM);
        */
        
		mIsExpanded = false;

        mRect1.SetRect(0.0f, 0.0f, mWidth, mHeight);
        mRect1.mRefresh = true;
        mRect2.SetRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f);
        mRect2.mRefresh = true;
    }
}

/*
void UMainToolbar::AddButton(UButton *pButton)
{
    pButton->SetHeight(UTIL_MENU_TOOLBAR_HEIGHT - 6.0f);
    AddButton(mInsertX, mInsertY, pButton);
    mInsertX++;
    if(mInsertX >= mMaxRowCount)
    {
        mInsertX = 0;
        mInsertY++;
    }
}

void UMainToolbar::AddButton(int pCol, int pRow, UButton *pButton)
{
    if(pButton)
    {
        AddSubview(pButton);
        mButtonGrid[pRow][pCol] = pButton;
        
        float aSize = ((mWidth - UTIL_MENU_SPACING_H_SIDES * 2) / ((float)mMaxRowCount));
        
        float aX = UTIL_MENU_SPACING_H_SIDES + aSize * pCol;
        float aY = UTIL_MENU_SPACING_V_TOP + (UTIL_MENU_SPACING_V + UTIL_MENU_ROW_HEIGHT) * pRow;
        float aWidth = (aSize - UTIL_MENU_SPACING_H);
        float aHeight = pButton->mHeight;
        
        pButton->SetMenuItemFrame(aX, aY, aWidth, aHeight);
        
        //pButton->SetUp(UTIL_MENU_SPACING_H_SIDES + aSize * pCol, UTIL_MENU_SPACING_V_TOP + (UTIL_MENU_SPACING_V + UTIL_MENU_ROW_HEIGHT) * pRow, (aSize - UTIL_MENU_SPACING_H), pButton->mText.c());
        
        
        
        float aMaxY = pButton->mY + pButton->mHeight + UTIL_MENU_SPACING_V_BOTTOM;
        if(aMaxY >= mHeight)
        {
            SetFrame(0.0f, 0.0f, mWidth, aMaxY);
            mRect1.SetRect(0.0f, 0.0f, mWidth, mHeight);
            mRect1.mRefresh = true;
            
            mRect2.SetRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f);
            mRect2.mRefresh = true;
        }
    }
}

*/


