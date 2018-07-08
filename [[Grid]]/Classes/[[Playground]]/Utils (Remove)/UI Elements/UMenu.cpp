//
//  UMenu.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UMenu.h"
#include "FApp.h"
#include "UMainCanvas.h"

UMenuRow::UMenuRow(int pGridWidth)
{
    mConsumesTouches = false;
    
    mToolMenu = 0;
    
    mMenuItemIsRow = true;
    mFixedHeight = false;
    
    mMenuItem = new UMenuItem *[pGridWidth];
    for(int i=0;i<pGridWidth;i++)mMenuItem[i]=0;
    
    mRowSize = pGridWidth;
    mRowCount = 0;
    mRowColCount = 0;
    
    mRowPane = 0;
    
    SetFrame(mX, mY, UTIL_MENU_DEFAULT_WIDTH, UTIL_MENU_ROW_HEIGHT);
}

UMenuRow::~UMenuRow()
{
    //Log("UMenuRow::~UMenuRow()\n");
    delete [] mMenuItem;
    mMenuItem = 0;
}


void UMenuRow::AddMenuItem(UMenuItem *pMenuItem)
{
    mMenuItem[mRowCount] = pMenuItem;
    AddSubview(pMenuItem);
    mRowColCount += pMenuItem->mMenuItemWidthSlots;
    
    if(pMenuItem->mMenuItemIsPane)
    {
        mRowPane = (UMenuPane *)pMenuItem;
    }
    
    mRowCount++;
}


void UMenuRow::Notify(void *pSender)
{
    if(mParent)
    {
        mParent->Notify(pSender);
    }
}

void UMenuRow::Notify(void *pSender, int pID, void *pObject)
{
    if(mParent)
    {
        if((pID == UTIL_ACTION_NODE_SELECT) || (pID == UTIL_ACTION_NEST_DEPTH))
        {
            EnumList(FView, aView, mSubviews)aView->Notify(pSender, pID, pObject);
        }
        else
        {
            mParent->Notify(pSender, pID, mParent);
            //mParent->Notify(pSender);
        }
        
        
        
        if(pID == UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS)
        {
            
        }
    }
}

//


//int                                         mRowCount;
//int                                         mRowColCount;

void UMenuRow::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    
    if(mRowColCount > 0)
    {
        float aSpacing = (mWidth - (UTIL_MENU_SPACING_H_SIDES * 2)) / ((float)mRowColCount);
        aSpacing -= ((float)UTIL_MENU_SPACING_H);
        
        float aX = UTIL_MENU_SPACING_H_SIDES;
        
        if(mRowCount == 1)
        {
            if(mMenuItem[0])
            {
                if((mMenuItem[0]->mMenuItemIsPane == true) || (mMenuItem[0]->mMenuItemIsRow == true))
                {
                    aSpacing = (mWidth) / ((float)mRowColCount);
                    aSpacing -= ((float)UTIL_MENU_SPACING_H);
                    
                    aX = 0.0f;
                }
            }
            
        }
        for(int i=0;i<mRowCount;i++)
        {
            float aWidth = ((float)mMenuItem[i]->mMenuItemWidthSlots) * aSpacing;
            mMenuItem[i]->SetMenuItemFrame(aX, 0.0f, aWidth, mHeight);
            aX += (aWidth + UTIL_MENU_SPACING_H);
        }
    }
}

UMenuPane::UMenuPane(const char *pTitle, bool pExpandable, bool pDetatchable) : UMenuPane()
{
    SetExpandable(pExpandable, pDetatchable);
    SetText(pTitle);
}

UMenuPane::UMenuPane() : UMenuItem()
{
    FView::SetFrame(mX, mY, UTIL_MENU_DEFAULT_WIDTH, UTIL_MENU_TOOLBAR_HEIGHT);
    
    mCollapseRectHeight = UTIL_MENU_PANE_HEADER_HEIGHT;
    
    mParentPane = 0;
    
    mNestDepth = 0;
    
    mButtonDetatch = 0;
    mButtonExpand = 0;
    
    mContainerContent = 0;
    mContainerContentEnqueued = 0;
    mContainerContentEnqueuedTimer = 0;
    
    mCollapseBarWidth = 0.0f;
    mCollapseBarWidthFixed = false;
    mCollapseBarFixedSide = 1;
    
    mIsToolMenu = false;
    mDisableDraw = false;
    
    mTextLabel = new ULabel();
    
    mExpandable = false;
    mExpanded = true;
    
    mMenuItemIsPane = true;
    
    mAllowMultipleExpandedSubpanes = false;
    
    mMenuItemWidthSlots = 4;
    
    
    //mRectOutline.SetColorTop(0.88f, 0.88f, 0.88f, 1.0f);
    //mRectOutline.SetColorBottom(1.0f, 1.0f, 1.0f, 1.0f);
    
    mRectOutline.SetColorBottom(0.06f, 0.06f, 0.06f, 4.0f);
    mRectOutline.SetColorTop(0.0f, 0.0f, 0.0f, 4.0f);
    
    
    mRectOutline.mCornerRadius = 10;
    mRectOutline.mCornerPointCount = 8;
    
    
    mRect.SetColorTop(0.75f, 0.75f, 0.75f);
    mRect.SetColorBottom(0.82f, 0.82f, 0.82f);
    mRect.mCornerRadius = 8;
    mRect.mCornerPointCount = 6;
    
    
    mRectBar.mCornerRadius = 8;
    mRectBar.mCornerPointCount = 6;
    
    //mRectBar[1].mCornerRadius = 5;
    //mRectBar[1].mCornerPointCount = 7;
    //mRectBar[1].mRoundBottom = false;
    
    
    //mRectBarShine[0].mCornerRadius = 5;
    //mRectBarShine[0].mCornerPointCount = 7;
    
    mRectBarShine.Copy(&mRectBar);
    
    mRectBarShine.SetColorTop(1.0f, 1.0f, 1.0f, 0.35f);
    mRectBarShine.SetColorBottom(1.0f, 1.0f, 1.0f, 0.0f);
    
    //.mCornerRadius = 5;
    //mRectBarShine[1].mCornerPointCount = 7;
    //mRectBarShine[1].mRoundBottom = false;
    
    
}

UMenuPane::~UMenuPane()
{
    
}

void UMenuPane::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    //mRect
    
    float aInset = 2.0f;
    
    float aRectX = aInset;
    float aRectY = aInset;
    float aRectWidth = mWidth - (aInset * 2);
    float aRectHeight = mCollapseRectHeight;
    
    
    if(mCollapseBarWidthFixed)
    {
        float aX = aInset;
        
        if(mCollapseBarFixedSide == 1)aX = mWidth - (mCollapseBarWidth + aInset);
        
        aRectX = aX;
        aRectY = aInset;
        aRectWidth = mCollapseBarWidth - (aInset * 2);
        aRectHeight = mCollapseRectHeight;
    }
    
    mRectBar.SetRect(aRectX, aRectY, aRectWidth, aRectHeight);
    mRectBar.mRefresh = true;
    
    //mRectBarShine[0].SetRect(aRectX, aRectY, aRectWidth, aRectHeight);
    //mRectBarShine[0].mRefresh = true;
    
    mRectBarShine.SetRect(aRectX + 2.0f, aRectY + 2.0f, aRectWidth - 2.0f, aRectHeight - 8.0f);
    mRectBarShine.mRefresh = true;
    
    
    mRectOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mRectOutline.mRefresh = true;
    
    mRect.SetRect(aInset, aInset, mWidth - (aInset * 2), mHeight - (aInset * 2));
    mRect.mRefresh = true;
    
    
    float aButtonWidth = 60.0f;
    float aButtonHeight = aRectHeight - 4.0f;
    
    float aButtonX = mWidth - (aButtonWidth + 6.0f);
    float aButtonY = 2.0f;
    
    if(mButtonExpand)
    {
        mButtonExpand->SetMenuItemFrame(aButtonX, aButtonY, aButtonWidth, aButtonHeight);
        aButtonX -= (aButtonWidth + 6.0f);
    }
    
    if(mButtonDetatch)
    {
        mButtonDetatch->SetMenuItemFrame(aButtonX, aButtonY, aButtonWidth, aButtonHeight);
        aButtonX -= (aButtonWidth + 6.0f);
    }
}

void UMenuPane::SetText(const char *pText)
{
    UMenuItem::SetText(pText);
    if(mTextLabel)
    {
        mTextLabel->SetText(pText);
    }
}

void UMenuPane::SetExpandable(bool pExpandable, bool pDetatchable)
{
    mExpandable = pExpandable;
    
    if(mIsToolMenu == false)
    {
        if(pExpandable == true)
        {
            if(mButtonExpand == 0)
            {
                mButtonExpand = new UButton("-");
                mButtonExpand->mListenerPane = this;
                AddSubview(mButtonExpand);
                mButtonExpand->StyleSetClear();
                mCollapseViews.Add(mButtonExpand);
            }
            else
            {
                BringSubviewToFront(mButtonExpand);
            }
        }
        
        if(pDetatchable == true)
        {
            if(mButtonDetatch == 0)
            {
                mButtonDetatch = new UButton("-[D]-");
                mButtonDetatch->mListenerPane = this;
                AddSubview(mButtonDetatch);
                mButtonDetatch->StyleSetClear();
                mCollapseViews.Add(mButtonDetatch);
            }
            else
            {
                BringSubviewToFront(mButtonDetatch);
            }
        }
    }
    
    SetMenuItemFrame(mX, mY, mWidth, mHeight);
}

void UMenuPane::Notify(void *pSender)
{
    if(mMenuPtr)
    {
        if(mMenuPtr != this)
        {
            //mMenuPtr->Notify(pSender);
        }
    }
    
    if(mParent)
    {
        mParent->Notify(pSender);
    }
}

void UMenuPane::Notify(void *pSender, int pID, void *pObject)
{
    if(pID == UTIL_ACTION_NODE_SELECT)
    {
        EnumList(FView, aView, mSubviews)aView->Notify(pSender, pID, pObject);
        SetSelectedNode((UNode *)pObject);
    }
    else if(pID == UTIL_ACTION_NEST_DEPTH)
    {
        int aDepth = (int)((long)pObject);
        SetNestDepth(aDepth);
        EnumList(FView, aView, mSubviews)aView->Notify(pSender, UTIL_ACTION_NEST_DEPTH, (void *)((long)(aDepth + 1)));
    }
    else
    {
        if(mParent)
        {
            if(pID == UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS)
            {
                mParent->Notify(pSender, UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS, mParent);
            }
            else
            {
                mParent->Notify(pSender, pID, pObject);
            }
        }
        if(mListenerView)
        {
            mListenerView->Notify(pSender, pID, pObject);
        }
    }
}

void UMenuPane::NotifyPane(void *pSender)
{
    if(pSender == mButtonDetatch)
    {
        gUtils->MenuDetatch(mMenuPtr, this);
    }
    
    if((pSender == mButtonExpand) && (mButtonExpand != 0))
    {
        
        if(mExpanded)
        {
            Collapse();
            mButtonExpand->SetText("+");
        }
        else
        {
            Expand();
            mButtonExpand->SetText("-");
        }
        
    }
    
}

void UMenuPane::NotifyPane(void *pSender, int pID, void *pObject)
{
    
}

void UMenuPane::SetSelectedNode(UNode *pNode)
{
    
}

void UMenuPane::SetNestDepth(int pDepth)
{
    mNestDepth = pDepth;
    
    //SetText(FString(pDepth).c());
    
    int aPaneSlot = (pDepth % 2);
    int aBarSlot = (pDepth % 4);
    
    if(aBarSlot < 0)aBarSlot = 3;
    
    if(aPaneSlot == 0)
    {
        mRect.SetColorTop(gUtils->mMenuStylePaneR[0], gUtils->mMenuStylePaneG[0], gUtils->mMenuStylePaneB[0], gUtils->mMenuStylePaneA[0]);
        mRect.SetColorBottom(gUtils->mMenuStylePaneR[1], gUtils->mMenuStylePaneG[1], gUtils->mMenuStylePaneB[1], gUtils->mMenuStylePaneA[1]);
        
    }
    else
    {
        mRect.SetColorTop(gUtils->mMenuStylePaneOddR[0], gUtils->mMenuStylePaneOddG[0], gUtils->mMenuStylePaneOddB[0], gUtils->mMenuStylePaneOddA[0]);
        mRect.SetColorBottom(gUtils->mMenuStylePaneOddR[1], gUtils->mMenuStylePaneOddG[1], gUtils->mMenuStylePaneOddB[1], gUtils->mMenuStylePaneOddA[1]);
    }
    
    mRectBar.SetColorTop(gUtils->mMenuStyleBarR[aBarSlot][0], gUtils->mMenuStyleBarG[aBarSlot][0], gUtils->mMenuStyleBarB[aBarSlot][0], gUtils->mMenuStyleBarA[aBarSlot][0]);
    mRectBar.SetColorBottom(gUtils->mMenuStyleBarR[aBarSlot][1], gUtils->mMenuStyleBarG[aBarSlot][1], gUtils->mMenuStyleBarB[aBarSlot][1], gUtils->mMenuStyleBarA[aBarSlot][1]);
    
    
    mRectBarShine.Copy(&mRectBar);
    
    mRectBarShine.SetColorTop(gUtils->mMenuStyleBarShineR[0], gUtils->mMenuStyleBarShineG[0], gUtils->mMenuStyleBarShineB[0], gUtils->mMenuStyleBarShineA[0]);
    mRectBarShine.SetColorBottom(gUtils->mMenuStyleBarShineR[1], gUtils->mMenuStyleBarShineG[1], gUtils->mMenuStyleBarShineB[1], gUtils->mMenuStyleBarShineA[1]);
    
    
    //}
    
    mRectBar.mRefresh = true;
    mRectBarShine.mRefresh = true;
}

void UMenuPane::LayoutSubviews()
{
    float aY = 0.0f;
    
    if(mIsToolMenu)
    {
        aY += mCollapseRectHeight;
    }
    else
    {
        if(mExpandable)
        {
            aY += mCollapseRectHeight;
        }
    }
    
    if(mExpanded == true)
    {
        
        if(mRowList.mCount <= 0)
        {
            aY += (UTIL_MENU_ROW_HEIGHT + UTIL_MENU_SPACING_V);
            
        }
        else
        {
            aY += UTIL_MENU_SPACING_V_TOP;//UTIL_MENU_SPACING_V;
            
            EnumList(UMenuRow, aRow, mRowList)
            {
                aRow->mMenuPtr = mMenuPtr;
                
                if(aRow->mRowPane)
                {
                    UMenuPane *aPane = ((UMenuPane *)(aRow->mMenuItem[0]));
                    if(aPane)
                    {
                        float aPaneSpacing = 3.0f + UTIL_MENU_SPACING_H_SIDES;
                        
                        aRow->SetMenuItemFrame(aPaneSpacing + UTIL_MENU_SPACING_H_SIDES, aY, mWidth - (aPaneSpacing), UTIL_MENU_ROW_HEIGHT);
                        aPane->LayoutSubviews();
                        aRow->SetMenuItemFrame(aPaneSpacing + UTIL_MENU_SPACING_H_SIDES, aY, mWidth - (aPaneSpacing), aPane->mHeight);
                    }
                }
                else
                {
                    if(aRow->mFixedHeight)
                    {
                        aRow->SetMenuItemFrame(0.0f, aY, mWidth, aRow->mHeight);
                    }
                    else
                        
                    {
                        aRow->SetMenuItemFrame(0.0f, aY, mWidth, UTIL_MENU_ROW_HEIGHT);
                    }
                }
                aY += (aRow->mHeight + UTIL_MENU_SPACING_V);
            }
            
            //aY -= UTIL_MENU_SPACING_V;
            aY += UTIL_MENU_SPACING_V_BOTTOM;
            
            
            
        }
    }
    
    //UMenuItem::
    SetMenuItemFrame(mX, mY, mWidth, aY);
}

void UMenuPane::AddMenuItems(UMenuItem *pMenuItem)
{
    if(pMenuItem)
    {
        pMenuItem->mMenuPtr = mMenuPtr;
        
        if(pMenuItem->mMenuItemIsPane)
        {
            ((UMenuPane *)pMenuItem)->mParentPane = this;
        }
        
        if(pMenuItem->mMenuItemWidthSlots < 1)pMenuItem->mMenuItemWidthSlots = 1;
        //if(pMenuItem->mMenuItemWidthSlots > mMenuItemWidthSlots)pMenuItem->mMenuItemWidthSlots = mMenuItemWidthSlots;
        
        
        UMenuRow *aRow = ((UMenuRow *)(mRowList.Last()));
        
        //bool aPane = false;
        
        if(aRow)
        {
            
            if(((aRow->mRowColCount + pMenuItem->mMenuItemWidthSlots) <= mMenuItemWidthSlots) && (aRow->mRowPane == 0))
            {
                aRow->AddMenuItem(pMenuItem);
            }
            else
            {
                aRow = 0;
            }
        }
        
        if(aRow == 0)
        {
            aRow = new UMenuRow(mMenuItemWidthSlots);
            
            if(pMenuItem->mMenuItemIsPane)
            {
                aRow->mRowPane = (UMenuPane *)pMenuItem;
            }
            
            aRow->AddMenuItem(pMenuItem);
            
            mRowList += aRow;
            
            AddSubview(aRow);
        }
    }
}

void UMenuPane::AddMenuItems(const char *pLabe1, UMenuItem *pMenuItem1, const char *pLabel2, UMenuItem *pMenuItem2)
{
    AddMenuItems(pLabe1, pMenuItem1);
    AddMenuItems(pLabel2, pMenuItem2);
}

void UMenuPane::AddMenuItems(const char *pLabel, UMenuItem *pMenuItem)
{
    ULabel *aLabel = new ULabel();
    aLabel->SetText(pLabel);
    AddMenuItems(aLabel, pMenuItem);
}

void UMenuPane::AddMenuItems(UMenuItem *pMenuItem1, UMenuItem *pMenuItem2, UMenuItem *pMenuItem3, UMenuItem *pMenuItem4)
{
    AddMenuItems(pMenuItem1);
    AddMenuItems(pMenuItem2);
    AddMenuItems(pMenuItem3);
    AddMenuItems(pMenuItem4);
}

void UMenuPane::AddMenuItems(UMenuItem *pMenuItem1, UMenuItem *pMenuItem2, UMenuItem *pMenuItem3)
{
    AddMenuItems(pMenuItem1);
    AddMenuItems(pMenuItem2);
    AddMenuItems(pMenuItem3);
}

void UMenuPane::AddMenuItems(UMenuItem *pMenuItem1, UMenuItem *pMenuItem2)
{
    AddMenuItems(pMenuItem1);
    AddMenuItems(pMenuItem2);
}


void UMenuPane::AddLine(UMenuItem *pItem1, UMenuItem *pItem2, UMenuItem *pItem3, UMenuItem *pItem4, UMenuItem *pItem5, UMenuItem *pItem6, UMenuItem *pItem7, UMenuItem *pItem8, UMenuItem *pItem9, UMenuItem *pItem10)
{
    
    FList aList;
    
    if(pItem1)aList.Add(pItem1);
    if(pItem2)aList.Add(pItem2);
    if(pItem3)aList.Add(pItem3);
    if(pItem4)aList.Add(pItem4);
    if(pItem5)aList.Add(pItem5);
    if(pItem6)aList.Add(pItem6);
    if(pItem7)aList.Add(pItem7);
    if(pItem8)aList.Add(pItem8);
    if(pItem9)aList.Add(pItem9);
    if(pItem10)aList.Add(pItem10);
    
    int aRowWidth = 0;
    
    EnumList(UMenuItem, aItem, aList)
    {
        aItem->mMenuPtr = mMenuPtr;
        
        if(aItem->mMenuItemWidthSlots <= 0)aItem->mMenuItemWidthSlots = 1;
        
        aRowWidth += aItem->mMenuItemWidthSlots;
        aItem->mMenuPtr = mMenuPtr;
        
        if(aItem->mMenuItemIsPane)
        {
            ((UMenuPane *)aItem)->mParentPane = this;
        }
    }
    
    if(aRowWidth > 0)
    {
        UMenuRow *aRow = new UMenuRow(aList.mCount);
        
        EnumList(UMenuItem, aItem, aList)
        {
            aRow->AddMenuItem(aItem);
        }
        mRowList += aRow;
        
        AddSubview(aRow);
    }
}

void UMenuPane::AddBlankLine(float pHeight)
{
    UMenuRow *aRow = new UMenuRow(1);
    
    //UMenuPane *aPlaceholder = new UMenuPane();
    //aPlaceholder->mMenuItemIsPane = true;
    //aRow->AddMenuItem(aPlaceholder);
    
    aRow->SetMenuItemFrame(0.0f, 0.0f, mWidth, pHeight);
    //aPlaceholder->SetMenuItemFrame(0.0f, 0.0f, mWidth, pHeight);
    
    aRow->mFixedHeight = true;
    mRowList += aRow;
    AddSubview(aRow);
}

void UMenuPane::AddBlankLine()
{
    UMenuRow *aRow = new UMenuRow(1);
    mRowList += aRow;
    AddSubview(aRow);
}

void UMenuPane::ReplaceMenuItems(UMenuPane *pNewContents)
{
    if(pNewContents)
    {
        mRowList.RemoveAll();
        
        EnumList(UMenuRow, aRow, pNewContents->mRowList)
        {
            mRowList.Add(aRow);
        }
        
        LayoutSubviews();
    }
}

void UMenuPane::SetContainerContents(UMenuPane *pPane)
{
    if((mContainerContentEnqueued == 0) && (mContainerContentEnqueuedTimer <= 0))//(pPane != 0))
    {
        if(mContainerContent != pPane)
        {
            EnumList(UMenuRow, aRow, mRowList)
            {
                aRow->RemoveFromParent();
            }
            
            mRowList.Clear();
            
            mContainerContentEnqueued = pPane;
            mContainerContentEnqueuedTimer = 2;
        }
    }
}

void UMenuPane::BaseUpdate()
{
    UMenuItem::BaseUpdate();
    
    if(mContainerContentEnqueuedTimer > 0)
    {
        mContainerContentEnqueuedTimer--;
        
        if(mContainerContentEnqueuedTimer <= 0)
        {
            mContainerContent = mContainerContentEnqueued;
            mContainerContentEnqueued = 0;
            
            mContainerContentEnqueuedTimer = 0;
            
            if(mContainerContent != 0)
            {
                EnumList(UMenuRow, aRow, mContainerContent->mRowList)
                {
                    mRowList.Add(aRow);
                    AddSubview(aRow);
                }
            }
            
            if(mParent)
            {
                mParent->Notify(this, UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS, mParent);
            }
            
            SetSelectedNode(gUtilsNode);
            EnumList(FView, aView, mSubviews)aView->Notify(this, UTIL_ACTION_NODE_SELECT, gUtilsNode);
        }
    }
}

void UMenuPane::Draw()
{
    Graphics::BlendSetAlpha();
    
    if(mDisableDraw == false)
    {
        
        if(mExpandable)
        {
            if(mExpanded)
            {
                mRectOutline.Draw();
                mRect.Draw();
                mRectBar.Draw();
            }
            else
            {
                mRectBar.Draw();
            }
        }
        else
        {
            mRect.Draw();
        }
        
        mRectBarShine.Draw();
        
        Graphics::SetColor();
        Graphics::BlendSetPremultiplied();
        
        float aFontWidth = gAppBase->mSysFontBold.Width(mText.c());
        
        gAppBase->mSysFontBold.Center(mText.c(), (aFontWidth * 0.8f * 0.5f) + 12.0f + mNestDepth * 6.0f, UTIL_MENU_PANE_HEADER_HEIGHT / 2 + 3.0f, 0.80f);
        Graphics::BlendSetAlpha();
    }
}

void UMenuPane::TouchUp(float pX, float pY, void *pData)
{
    if(mExpandable)
    {
        //if(mExpanded)Collapse();
        //else Expand();
    }
    
    if((mMenuPtr != 0) && (gUtils != 0))
    {
        gUtils->MenuSelect(mMenuPtr);
    }
}

void UMenuPane::SetCollapseBarWidth(float pWidth, int pSide)
{
    mCollapseBarWidth = pWidth;
    mCollapseBarWidthFixed = true;
    mCollapseBarFixedSide = pSide;
}

void UMenuPane::PaneExpanded(UMenuPane *pPane)
{
    if(mAllowMultipleExpandedSubpanes == false)
    {
        EnumList(UMenuRow, aRow, mRowList)
        {
            if(aRow->mRowPane)
            {
                UMenuPane *aPane = ((UMenuPane *)(aRow->mMenuItem[0]));
                if(aPane)
                {
                    if(aPane != pPane)
                    {
                        aPane->Collapse();
                    }
                }
            }
        }
    }
}

//This earthly life is only temporary.

void UMenuPane::Collapse()
{
    if(mExpanded == true)
    {
        mExpanded = false;
        
        EnumList(FView, aView, mSubviews)
        {
            if(mCollapseViews.Exists(aView) == false)
            {
                aView->mHidden = true;
                aView->mEnabled = false;
            }
        }
        
        LayoutSubviews();
        if(mParent)
        {
            mParent->Notify(this, UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS, mParent);
        }
        Notify(this, UTIL_ACTION_NODE_SELECT, gUtilsNode);
    }
}

void UMenuPane::Expand()
{
    if(mExpanded == false)
    {
        mExpanded = true;
        EnumList(FView, aView, mSubviews)
        {
            if(mCollapseViews.Exists(aView) == false){aView->mHidden = false;aView->mEnabled = true;}
        }
        if(mParentPane)mParentPane->PaneExpanded(this);
        LayoutSubviews();
        if(mParent)mParent->Notify(this, UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS, mParent);
        Notify(this, UTIL_ACTION_NODE_SELECT, gUtilsNode);
    }
}

UMenu::UMenu()
{
    mName = "UMenu";
    
    mMenuPtr = this;
    mIsToolMenu = true;
    
    mAllowMultipleExpandedSubpanes = true;
    
    mCollapseRectHeight = UTIL_MENU_TOOLBAR_HEIGHT;
    
    mToolbar = new UMenuToolbar();
    AddSubview(mToolbar);
    
    mToolbar->mToolMenu = this;
    //mSubviewStartOffsetY = UTIL_MENU_TOOLBAR_HEIGHT;
    
    //mToolbar->mToolMenu
    
    SetSize(UTIL_MENU_DEFAULT_WIDTH, UTIL_MENU_TOOLBAR_HEIGHT + UTIL_MENU_SPACING_V);
    
    mExpandedWidth = mWidth;
    mExpandedHeight = mHeight;
    
    mDragFrameMode = true;
    //mNotifyParent = true;
    
    mExpanded = true;
    mExpandable = true;
    
    mExpandedWidth = mWidth;
    mExpandedHeight = mHeight;
    
    mQuadBackground.SetColorTop(0.62f * 0.66f, 0.67f * 0.66f, 0.72f * 0.66f, 1.0f);
    mQuadBackground.SetColorBottom(0.64f * 0.66f, 0.69f * 0.66f, 0.78f * 0.66f, 1.0f);
    
    SetFrame(mX, mY, mWidth, mHeight);
}

UMenu::~UMenu()
{
    //if(gUtils)
    //{
    //    gUtils->KillMenu(this);
    //}
}

void UMenu::Update()
{
    /*
     if(mRefresh)
     {
     mRefresh = false;
     LayoutSubviews();
     }
     */
    
}

void UMenu::Draw()
{
    DrawBottom();
    
    //UMenuPane::Draw();
    
    DrawToolbar();
}

void UMenu::DrawBottom()
{
    
    mRectShadow.Draw();
    
    if(mExpanded)
    {
        mQuadBackground.Draw();
        
        mRectBorderLeft.Draw();
        mRectBorderRight.Draw();
        mRectBorderBottom.Draw();
    }
    else
    {
        //mRectToolbarCollapsed.Draw();
    }
}

void UMenu::DrawToolbar()
{
    
}

void UMenu::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    UMenuPane::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    float aDrawHeight = mHeight + 6;
    
    
    float aBorderSize = 2;
    float aBorderSideY = (UTIL_MENU_TOOLBAR_HEIGHT / 2);
    float aBorderSideHeight = (aDrawHeight - (aBorderSideY + aBorderSize));
    
    mRectBorderLeft.SetColorLeft(0.0f, 0.0f, 0.0f, 0.4f);
    mRectBorderLeft.SetColorRight(0.0f, 0.0f, 0.0f, 0.4f);
    
    mRectBorderRight.SetColorLeft(0.0f, 0.0f, 0.0f, 0.4f);
    mRectBorderRight.SetColorRight(0.0f, 0.0f, 0.0f, 0.4f);
    
    mRectBorderBottom.SetColorLeft(0.0f, 0.0f, 0.0f, 0.4f);
    mRectBorderBottom.SetColorRight(0.0f, 0.0f, 0.0f, 0.4f);
    
    
    mRectBorderLeft.SetRect(0.0f, aBorderSideY, aBorderSize, aBorderSideHeight);
    mRectBorderRight.SetRect(mWidth - aBorderSize, aBorderSideY, aBorderSize, aBorderSideHeight);
    mRectBorderBottom.SetRect(0.0f, aDrawHeight, mWidth, aBorderSize);
    mQuadBackground.SetRect(0.0f, aBorderSideY, mWidth, aBorderSideHeight);
    
    mToolbar->SetMenuItemFrame(0.0f, 0.0f, mWidth, mToolbar->mHeight);
    
    float aShadowOffX = -3.0f;
    float aShadowOffY = 7.0f;
    float aShadowSize = 6.0f;
    
    mRectShadow.SetRect(2.0f - aShadowSize + aShadowOffX, -3.0f - aShadowSize + aShadowOffY, mWidth + aShadowSize * 2.0f + 2.0f, mHeight + aShadowSize * 2.0f + 2.0f);
    mRectShadow.SetColorTop(0.0f, 0.0f, 0.05f, 0.14f);
    mRectShadow.SetColorBottom(0.0f, 0.0f, 0.05f, 0.14f);
    
    mRectShadow.mCornerPointCount = 8;
    mRectShadow.mCornerRadius = 8.0f;
    
    if(mExpanded)mRectShadow.mRoundBottom = false;
    else mRectShadow.mRoundBottom = true;
    
    mRectShadow.mRefresh = true;
}

void UMenu::TouchDown(float pX, float pY, void *pData)
{
    if((mMenuPtr != 0) && (gUtils != 0))gUtils->MenuSelect(this);
}

void UMenu::TouchUp(float pX, float pY, void *pData)
{
    
}

void UMenu::SetSelectedNode(UNode *pNode)
{
    
}

void UMenu::SetText(const char *pText)
{
    UMenuItem::SetText(pText);
    if(mToolbar)
    {
        mToolbar->SetText(pText);
    }
}

void UMenu::Notify(void *pSender, int pID, void *pObject)
{
    if(pID == UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS)
    {
        LayoutSubviews();
    }
    else
    {
        UMenuPane::Notify(pSender, pID, pObject);
    }
}

void UMenu::CloseMenu()
{
    if(gUtils)gUtils->MenuKill(this);
}

void UMenu::LayoutSubviews()
{
    if(mToolbar)mToolbar->SetText(FString(mText.c()).c());
    
    UMenuPane::LayoutSubviews();
    
    EnumList(FView, aView, mSubviews)aView->Notify(this, UTIL_ACTION_NEST_DEPTH, (void *)1);
    EnumList(FView, aView, mSubviews)aView->Notify(this, UTIL_ACTION_NODE_SELECT, gUtilsNode);
}

void UMenu::Collapse()
{
    if(mExpanded)
    {
        mExpanded = false;
        
        mExpandedWidth = mWidth;
        mExpandedHeight = mHeight;
        
        EnumList(FView, aView, mSubviews)
        {
            if(aView != mToolbar)
            {
                aView->mHidden = true;
                aView->mEnabled = false;
            }
        }
        
        LayoutSubviews();
        Notify(this, UTIL_ACTION_NODE_SELECT, gUtilsNode);
    }
}

void UMenu::Expand()
{
    if(mExpanded == false)
    {
        mExpanded = true;
        
        EnumList(FView, aView, mSubviews)
        {
            if(aView != mToolbar)
            {
                aView->mHidden = false;
                aView->mEnabled = true;
            }
        }
        
        LayoutSubviews();
        
        //SetSize(mExpandedWidth, mExpandedHeight);
        //virtual void                                SetSelectedNode(UNode *pNode);
        Notify(this, UTIL_ACTION_NODE_SELECT, gUtilsNode);
        
        //SetSelectedNode(gUtilsNode);
    }
}


void UMenu::DisableCloseButton()
{
    if(mToolbar)
    {
        mToolbar->DisableCloseButton();
    }
}



UMenuToolbar::UMenuToolbar()
{
    float aWidth = 300.0f;
    SetFrame(0.0f, 0.0f, aWidth, UTIL_MENU_TOOLBAR_HEIGHT);
    
    mName = "UMenuToolbar";
    mLabelTitle = 0;
    
    mToolMenu = 0;
    
    mConsumesTouches = false;
    
    mCloseButtonDisabled = false;
    
    
    mButtonCollapse = new UButton("-");
    mButtonCollapse->SetMenuItemFrame(5.0f, 3.0f, 66.0f, 38.0f);
    mButtonCollapse->StyleSetClose();
    AddSubview(mButtonCollapse);
    
    mButtonClose = new UButton("X");
    //mButtonClose->SetMenuItemFrame(mWidth - 80.0f, 5.0f, 70.0f, mButtonClose->mHeight);
    mButtonClose->StyleSetRed();
    mButtonClose->SetMenuItemFrame(101.0f, 3.0f, 66.0f, 38.0f);
    AddSubview(mButtonClose);
    
    
    
    
    mRectOutline.mCornerPointCount = 8;
    mRectOutline.mCornerRadius = 6.0f;
    mRectOutline.SetColorTop(0.22f, 0.22f, 0.22f, 1.0000f);
    mRectOutline.SetColorBottom(0.16f, 0.17f, 0.14f, 1.0000);
    
    
    mRectBack.mCornerPointCount = 8;
    mRectBack.mCornerRadius = 4.0f;
    mRectBack.SetColorTop(0.127f, 0.147f, 0.157f, 1.0000f);
    mRectBack.SetColorBottom(0.11909f, 0.12727f, 0.0991f, 1.0000f);
    
    mRectFront.mCornerPointCount = 8;
    mRectFront.mCornerRadius = 4.0f;
    mRectFront.SetColorTop(0.05f, 0.07f, 0.14f, 1.0000f);
    mRectFront.SetColorBottom(0.10f, 0.12f, 0.18f, 1.0000f);
    
    mRectShine.mCornerPointCount = 6;
    mRectShine.mCornerRadius = 4.0f;
    mRectShine.SetColorTop(1.0f, 1.0f, 1.0f, 0.4f);
    mRectShine.SetColorBottom(0.9f, 0.9f, 1.0f, 0.0f);
    
    //mRect.SetColorTop(0.75f, 0.75f, 0.75f);
    //mRect.SetColorBottom(0.67f, 0.67f, 0.67f);
    
    //mRect.mCornerRadius = 10.0f;
    //mRect.mCornerPointCount = 12;
    //mRect.mRoundBottom = false;
    
    mRectCollapsed.Copy(&mRectBack);
    mRectCollapsed.mRoundBottom = true;
    mRectCollapsed.SetRect(0.0f, 0.0f, (mButtonCollapse->mX * 2.0f) + mButtonCollapse->mWidth, mHeight);
    mRectCollapsed.ColorDarkenAll(0.14f);
    
}

UMenuToolbar::~UMenuToolbar()
{
    if(mButtonClose)
    {
        mButtonClose = 0;
    }
    
    if(mButtonCollapse)
    {
        mButtonCollapse=0;
    }
}

void UMenuToolbar::Draw()
{
    
    if(mToolMenu)
    {
        
        mRectOutline.Draw();
        mRectBack.Draw();
        
        if(mToolMenu->mExpanded)
        {
            
            mRectFront.Draw();
            
            
            //mRect.Draw();
        }
        else
        {
            mRectCollapsed.Draw();
        }
        
        mRectShine.Draw();
        
        Graphics::SetColor();
        Graphics::BlendSetPremultiplied();
        gAppBase->mSysFontBold.Center(mText.c(), mWidth2, mHeight2, 0.86f);
        Graphics::BlendSetAlpha();
    }
    Graphics::SetColor();
}

void UMenuToolbar::SetText(const char *pText)
{
    UMenuItem::SetText(pText);
}


void UMenuToolbar::SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight)
{
    
    UMenuItem::SetMenuItemFrame(pX, pY, pWidth, pHeight);
    
    if(mButtonCollapse)mButtonCollapse->SetMenuItemFrame(5.0f, 5.0f, mButtonCollapse->mWidth, mButtonCollapse->mHeight);
    if(mButtonClose)mButtonClose->SetMenuItemFrame(mWidth - 70.0f, 5.0f, mButtonClose->mWidth, mButtonClose->mHeight);
    
    
    mRectOutline.SetRect(-3.0f, -3.0f, mWidth + 6.0f, mHeight + 6.0f);
    mRectOutline.mRefresh = true;
    
    mRectBack.SetRect(-1, -1, mWidth + 2, mHeight + 2);
    mRectBack.mRefresh = true;
    
    mRectFront.SetRect(3.0f, 3.0f, mWidth - 6.0f, mHeight - 6.0f);
    mRectFront.mRefresh = true;
    
    
    mRectShine.SetRect(-1.0f, -1.0f, mWidth + 2.0f, mHeight + 2.0f);
    mRectShine.mRefresh = true;
    
    mRectCollapsed.SetRect(-1, -1, mWidth + 2, mHeight + 2);
    mRectCollapsed.mRefresh = true;
    
    if(mLabelTitle)
    {
        float aLeft = 0.0f;
        float aRight = mWidth;
        
        if(mButtonCollapse)aLeft = (mButtonCollapse->GetRight() + UTIL_MENU_SPACING_H);
        if(mButtonClose)aRight = (mButtonClose->mX - UTIL_MENU_SPACING_H);
        
        mLabelTitle->SetMenuItemFrame(aLeft, 0.0f, (aRight - aLeft), mHeight);
    }
}

void UMenuToolbar::TouchDown(float pX, float pY, void *pData)
{
    if(gUtils)gUtils->MenuSelect(mParent);
}


void UMenuToolbar::Collapse()
{
    if(mToolMenu)
    {
        mToolMenu->Collapse();
        
        if(mButtonCollapse)
        {
            mButtonCollapse->mText = "[+]";
        }
        
        if(mButtonClose)
        {
            //mButtonClose->mHidden = true;
            //mButtonClose->mEnabled = false;
        }
        
    }
}

void UMenuToolbar::Expand()
{
    if(mToolMenu)
    {
        mToolMenu->Expand();
        mButtonCollapse->mText = "[-]";
        
        //mRect.mRoundBottom = true;
        
        if(mButtonClose)
        {
            //mButtonClose->mHidden = false;
            //mButtonClose->mEnabled = true;
        }
    }
    
    
}

void UMenuToolbar::Notify(void *pSender, int pID, void *pObject)
{
    if(pID == UTIL_ACTION_NODE_SELECT)
    {
        SetSelectedNode((UNode *)pObject);
        EnumList(FView, aView, mSubviews)aView->Notify(pSender, pID, pObject);
    }
    
    
}

void UMenuToolbar::Notify(void *pSender)
{
    if(mToolMenu)
    {
        if(pSender == mButtonCollapse)
        {
            if(mToolMenu->mExpanded)
            {
                Collapse();
            }
            else
            {
                Expand();
            }
        }
        else if(pSender == mButtonClose)
        {
            mToolMenu->CloseMenu();
            //mToolMenu->Kill();
            
            mToolMenu = 0;
        }
    }
}

void UMenuToolbar::SetSelectedNode(UNode *pNode)
{
    
}

void UMenuToolbar::DisableCloseButton()
{
    if(mButtonClose)
    {
        mButtonClose->Kill();
        mButtonClose = 0;
    }
    mCloseButtonDisabled = true;
}

