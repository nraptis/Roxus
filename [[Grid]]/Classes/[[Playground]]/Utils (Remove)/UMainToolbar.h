//
//  UMainToolbar.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/13/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UMainToolbar__
#define ___015_Fleet_XP__UMainToolbar__

#include "FView.h"
#include "UMenuStyle.h"

class UMainCanvas;
class UMenuPane;
class UMainToolbar : public FView
{
public:
    
    UMainToolbar();
    virtual ~UMainToolbar();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            Notify(void *pSender);
    virtual void                            Notify(void *pSender, int pID, void *pObject);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    virtual void                            Expand();
    virtual void                            Collapse();
    
    bool                                    mIsExpanded;
    
    float                                   mExpandWidth;
    float                                   mExpandHeight;
    
    //void                                    AddButton(UButton *pButton);
    //void                                    AddButton(int pRow, int pCol, UButton *pButton);
    
    URoundedRect                            mRect1;
    URoundedRect                            mRect2;
    
    UButton                                 *mButtonCollapse;
    
    UButton                                 *mButtonToggleOutlines;
    
    UButton                                 *mButtonToggleUpdates;
    UButton                                 *mButtonTogglePassTouches;
    
    
    UButton                                 *mButtonNextFrame;
    
    UButton                                 *mButtonNodeEditor;
	UButton                                 *mButtonMotionEditor;
    
    UButton                                 *mButtonTimelineEditor;
	UButton                                 *mButtonParticleEditor;

	UButton                                 *mButtonParentPanel;
	UButton                                 *mButtonCanvasPanel;
	UButton                                 *mButtonTransform;
    
    //UButton                                 *mButtonGrid[32][32];
    //int                                     mMaxRowCount;

	USegment								*mSegmentMode;

	UMenuPane								*mPaneTop;
	UMenuPane								*mPaneLower;


	//UMenuRow								*mRow1;
	//UMenuRow								*mRow2;


    
    int                                     mInsertRow;
    
    float                                   mInsertY;
    float                                   mInsertX;
};

extern UMainToolbar *gUtilToolbar;

#endif



