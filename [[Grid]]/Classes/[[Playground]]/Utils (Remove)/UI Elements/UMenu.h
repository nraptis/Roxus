//
//  UMenu.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UMenu__
#define ___015_Fleet_XP__UMenu__

#include "FView.h"
#include "UMenuStyle.h"
#include "FDrawQuad.h"

class UMenu;
class UMenuPane;
class UMenuRow : public UMenuItem
{
public:
    
    UMenuRow(int pGridWidth);
    virtual ~UMenuRow();
    
    UMenuItem                                   **mMenuItem;
    UMenuPane                                   *mRowPane;
    
	bool                                        mFixedHeight;
    
    void                                        AddMenuItem(UMenuItem *pMenuItem);
    
    virtual void                                Notify(void *pSender);
    virtual void                                Notify(void *pSender, int pID, void *pObject);
    
    int                                         mRowSize;
    int                                         mRowCount;
    int                                         mRowColCount;
    
    UMenu                                       *mToolMenu;
    
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
};

class UMenuPane : public UMenuItem
{
public:
    
    UMenuPane(const char *pTitle, bool pExpandable, bool pDetatchable=false);
    UMenuPane();
    virtual ~UMenuPane();
    
    virtual void                                SetText(const char *pText);
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    inline void                                 SetMenuItemFrame(){SetMenuItemFrame(mX, mY, mWidth, mHeight);}
    inline void                                 SetMenuItemWidth(float pWidth){SetMenuItemFrame(mX, mY, pWidth, mHeight);}
    inline void                                 SetMenuItemHeight(float pHeight){SetMenuItemFrame(mX, mY, mWidth, pHeight);}
    
    virtual void                                BaseUpdate();
    virtual void                                Draw();
    
    virtual void                                AddMenuItems(UMenuItem *pMenuItem);
    virtual void                                AddMenuItems(const char *pLabe1, UMenuItem *pMenuItem1, const char *pLabel2, UMenuItem *pMenuItem2);
    virtual void                                AddMenuItems(const char *pLabel, UMenuItem *pMenuItem);
    virtual void                                AddMenuItems(UMenuItem *pMenuItem1, UMenuItem *pMenuItem2, UMenuItem *pMenuItem3, UMenuItem *pMenuItem4);
    virtual void                                AddMenuItems(UMenuItem *pMenuItem1, UMenuItem *pMenuItem2, UMenuItem *pMenuItem3);
    virtual void                                AddMenuItems(UMenuItem *pMenuItem1, UMenuItem *pMenuItem2);
	virtual void                                AddLine(UMenuItem *pItem1, UMenuItem *pItem2 = 0, UMenuItem *pItem3 = 0, UMenuItem *pItem4 = 0, UMenuItem *pItem5 = 0, UMenuItem *pItem6 = 0, UMenuItem *pItem7 = 0, UMenuItem *pItem8 = 0, UMenuItem *pItem9 = 0, UMenuItem *pItem10 = 0);
	
    virtual void                                AddBlankLine(float pHeight);
	virtual void                                AddBlankLine();
    
    
    
    UButton                                     *mButtonDetatch;
    UButton                                     *mButtonExpand;
    
    void                                        ReplaceMenuItems(UMenuPane *pNewContents);
    void                                        SetContainerContents(UMenuPane *pPane);
    
    UMenuPane                                   *mContainerContentEnqueued;
    UMenuPane                                   *mContainerContent;
    
    int                                         mContainerContentEnqueuedTimer;
    
    virtual void                                SetExpandable(bool pExpandable, bool pDetatchable=false);
    
    virtual void                                Notify(void *pSender);
    virtual void                                Notify(void *pSender, int pID, void *pObject);
    
    void                                        NotifyPane(void *pSender);
    void                                        NotifyPane(void *pSender, int pID, void *pObject);
    
    
    
    virtual void                                LayoutSubviews();
    virtual void                                SetSelectedNode(UNode *pNode);
    
    virtual void                                SetNestDepth(int pDepth);
    int                                         mNestDepth;
    
    void                                        PaneExpanded(UMenuPane *pPane);
    
    virtual void                                TouchUp(float pX, float pY, void *pData);
    
    virtual void                                Collapse();
    virtual void                                Expand();
    
    FList                                       mCollapseViews;
    
    
    void                                        SetCollapseBarWidth(float pWidth, int pSide);
    float                                       mCollapseBarWidth;
    bool                                        mCollapseBarWidthFixed;
    int                                         mCollapseBarFixedSide;
    
    
    bool                                        mAllowMultipleExpandedSubpanes;
    
    bool                                        mIsToolMenu;
    
    float                                       mCollapseRectHeight;
    
    UMenu                                       *mToolMenu;
    
    UMenuPane                                   *mParentPane;
    
    FList                                       mRowList;
    
    URoundedRect                                mRect;
    URoundedRect                                mRectOutline;
    
    URoundedRect                                mRectBar;
    URoundedRect                                mRectBarShine;
    
	bool										mDisableDraw;
    
    ULabel                                      *mTextLabel;
    
    bool                                        mExpandable;
    bool                                        mExpanded;
};

//class UMenuSwappable


//class UMenu;
class UMenu;
class UMenuToolbar : public UMenuItem//FView
{
public:
    //UMenuToolbar(UMenu *pMenu);
    
    UMenuToolbar();
    
    virtual ~UMenuToolbar();
    
    virtual void                                Draw();
    virtual void                                SetText(const char *pText);
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                TouchDown(float pX, float pY, void *pData);
    
    virtual void                                Notify(void *pSender);
    virtual void                                Notify(void *pSender, int pID, void *pObject);
    virtual void                                SetSelectedNode(UNode *pNode);
    //virtual void								SetTitle(const char *pTitle);
    
    virtual void                                Collapse();
    virtual void                                Expand();
    
    UButton                                     *mButtonClose;
    UButton                                     *mButtonCollapse;
    
    void                                        DisableCloseButton();
    bool                                        mCloseButtonDisabled;
    
    ULabel                                      *mLabelTitle;
    
	URoundedRect                                mRectOutline;
	URoundedRect                                mRectBack;
	URoundedRect                                mRectFront;
    URoundedRect                                mRectShine;

    URoundedRect                                mRectCollapsed;
    
    FString                                     mTitle;
    
    //UMenu                                       *mMenu;
    UMenu                                       *mToolMenu;
};

class UMenu : public UMenuPane
{
public:
    UMenu();
    virtual ~UMenu();
    
    
    virtual void                                Update();
    virtual void                                Draw();
    void										DrawBottom();
    void										DrawToolbar();
    
    virtual void                                SetText(const char *pText);
    virtual void                                SetMenuItemFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                TouchDown(float pX, float pY, void *pData);
    virtual void                                TouchUp(float pX, float pY, void *pData);
    
    //virtual void                                Notify(void *pSender);
    virtual void                                Notify(void *pSender, int pID, void *pObject);
    virtual void                                SetSelectedNode(UNode *pNode);
    virtual void                                CloseMenu();
    
    virtual void                                LayoutSubviews();
    
    virtual void                                Collapse();
    virtual void                                Expand();
    
    UMenuToolbar                                *mToolbar;
    
    
    void                                        DisableCloseButton();
    
    
    FDrawQuad                                       mRectBorderLeft;
    FDrawQuad                                       mRectBorderRight;
    FDrawQuad                                       mRectBorderBottom;
    FDrawQuad                                       mQuadBackground;
    
    URoundedRect                                mRectShadow;
    
    float                                       mExpandedWidth;
    float                                       mExpandedHeight;
    
    bool                                        mRefresh;
    
};

#endif /* defined(___015_Fleet_XP__UMenu__) */
