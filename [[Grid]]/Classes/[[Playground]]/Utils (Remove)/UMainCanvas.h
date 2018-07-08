//
//  UMainCanvas.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UMainCanvas__
#define ___015_Fleet_XP__UMainCanvas__



#define UTIL_PATH_TYPE_MOVEMENT 0
#define UTIL_PATH_TYPE_POINT_CLOUD 1
#define UTIL_PATH_TYPE_POLY 2

#define UTIL_ACTION_NODE_SELECT 9
#define UTIL_ACTION_LAYOUT_SUBVIEWS 11
#define UTIL_ACTION_PARENT_LAYOUT_SUBVIEWS 12
#define UTIL_ACTION_NEST_DEPTH 13

#define UTIL_NODE_PARENT_FIXED 0
#define UTIL_NODE_PARENT_RELATIVE 1

#define UTIL_SELECTION_TYPE_NODE 0
#define UTIL_SELECTION_TYPE_SLIDER 1

#include "FSprite.h"
#include "FSpriteSequence.h"
#include "FSpline.h"
#include "FFile.h"

#include "FMotionPath.h"
#include "FMotionKeySequence.h"

#include "UNodeMotionPanel.h"
#include "UMainWorkspace.h"
#include "UNode.h"
#include "UMenu.h"
#include "UMainToolbar.h"
#include "UNodeEditorMenu.h"
#include "UTimelineEditorMenu.h"
#include "UParticleEditorMenu.h"




class UMainCanvasPanOverlay;
class UPathMaker;
class UParentPane;
class UCanvasPane;
class UTransformMenu;

class UMainCanvas : public FView
{
public:
    
    UMainCanvas();
    virtual ~UMainCanvas();
    
	virtual void                            PositionContent();

	virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
	virtual void                            TouchFlush();


	virtual void							MouseWheel(int pDirection);
	virtual void							KeyDown(int pKey);
	virtual void							KeyUp(int pKey);

    
    virtual void                            Notify(void *pSender);
    virtual void                            Notify(void *pSender, int pID, void *pObject);

    virtual void                            Expand();
    virtual void                            Collapse();
    bool                                    mIsExpanded;
    
	//FView									*mWorkspaceContainer;

    UMainToolbar                            *mToolbar;
    
	virtual void                            SetSelectedNode(UNode *pNode);
	virtual void                            SetSelectedNode();

    
    void                                    MenuAdd(UMenu *pMenu);
    void                                    MenuKill(FView *pMenu);
    void                                    MenuDetatch(UMenu *pMenu, UMenuPane *pMenuPane);
    
    FVec2                                   MenuGoodPlacement(float pWidth, float pHeight);
    void                                    MenuSelect(FView *pSelectedMenu);
    
    
    
    
    void                                    AddOverlay(FView *pView);
    void                                    KillOverlay();
    FView                                   *mOverlayView;
    
    void                                    Export();
    void                                    ExportSelected();
    void                                    Save();
    void                                    Load();
    void                                    DeleteSaved();
    
    void                                    SaveLayout();
    void                                    LoadLayout();

	void									BlockSprite(const char *pSprite);
	FList									mBlockedSpriteList;

	FList									mMotionPathDeleteList;
	int										mMotionPathDeleteListTimer;
	void									DeleteMotionPath(FMotionPathTemplate *pPath);

	FList									mNodeSelDeleteList;
	int										mNodeSelDeleteListTimer;
	void									DeleteNodeSelection(UNodeSelection *pSel);
    
	void									WorkspaceDisable();
	void									WorkspaceEnable();
	bool									WorkspaceHasFocus();
    
	void									SetReferenceView(FView *pView);
	FView									*mReferenceView;
    
	void									PanStart();
	void									PanEnd();

	bool									mPanning;
	float                                   mPanWindowStartX;
	float                                   mPanWindowStartY;
	float                                   mPanTouchStartX;
	float                                   mPanTouchStartY;
	void                                    *mPanDragData;
    
    UNodeEditorMenu                         *mNodeMenu;
	UTimelineEditorMenu                     *mTimelineMenu;
    UParticleEditorMenu1                    *mParticleMenu;
    UNodeMotionPanel                        *mMotionMenu;
	UParentPane								*mParentPane;
	UCanvasPane								*mCanvasPane;
	UTransformMenu							*mTransformMenu;
    
    
    FList                                   mMenuList;
    
    int                                     mMarkerDisplayType;
    
    void                                    SpawnNodeMenu();
    void                                    SpawnTimelineMenu();
    void                                    SpawnParticleMenu();
    void                                    SpawnTimeline();
	void                                    SpawnMotionMenu();
	void                                    SpawnCanvasMenu();
	void                                    SpawnParentMenu();
	void                                    SpawnTransformMenu();


	int										mImagePickType;

    
    bool                                    mDrawDisableAll;
    
    //
    
    void                                    PathCreate(int pPathType);
    void                                    PathSelect(FList *pPathList, int pPathType);
    
    
    float                                   mPathEditScale;
    bool                                    mPathTransformStart;
    
    
    bool                                    mFirstUpdate;
    
    void                                    BackgroundSpritePick();
    void                                    BackgroundDrawLetterBox();
    
    FColor                                  mBackgroundColor;
    bool                                    mBackgroundColorEnabled;
    bool                                    mBackgroundImageEnabled;
    bool                                    mBackgroundLetterBox;
    bool                                    mBackgroundLetterBoxOver;
    
    float                                   mEdgeLeft;
    float                                   mEdgeRight;
    float                                   mEdgeTop;
    float                                   mEdgeBottom;
    
    //FRect                                   mBackgroundLetterBoxRect;
    
    //mButtonEnableLetterBox
    
    float                                   mBackgroundOpacity;
    FSprite                                 *mBackgroundSprite;
    
    
    
    float                                   mGlobalOpacity;
    
    bool                                    mUpdatesAllowed;
    bool                                    mUpdateOnce;
    
    bool                                    mImagePickerUpdatesCurrentNode;
    bool                                    mImagePickerUpdatesBackground;
    
    float                                   mScreenResizeCornerX[4];
    float                                   mScreenResizeCornerY[4];
    float                                   mScreenResizeCornerDragStartX[4];
    float                                   mScreenResizeCornerDragStartY[4];
    
    
    
    
    float                                   mMenuStylePaneR[2];
    float                                   mMenuStylePaneG[2];
    float                                   mMenuStylePaneB[2];
    float                                   mMenuStylePaneA[2];
    
    float                                   mMenuStylePaneOddR[2];
    float                                   mMenuStylePaneOddG[2];
    float                                   mMenuStylePaneOddB[2];
    float                                   mMenuStylePaneOddA[2];
    
    float                                   mMenuStylePaneBorderR[2];
    float                                   mMenuStylePaneBorderG[2];
    float                                   mMenuStylePaneBorderB[2];
    float                                   mMenuStylePaneBorderA[2];
    
    float                                   mMenuStyleBarR[4][2];
    float                                   mMenuStyleBarG[4][2];
    float                                   mMenuStyleBarB[4][2];
    float                                   mMenuStyleBarA[4][2];
    
    float                                   mMenuStyleBarShineR[2];
    float                                   mMenuStyleBarShineG[2];
    float                                   mMenuStyleBarShineB[2];
    float                                   mMenuStyleBarShineA[2];
    
    
    
	void                                    ComputeResizeRect();
	float                                   mResizeLeft;
	float                                   mResizeTop;
	float                                   mResizeRight;
	float                                   mResizeBottom;
	float                                   mResizeWidth;
	float                                   mResizeHeight;


	float									mResizeDragCornerX;
	float									mResizeDragCornerY;
	int                                     mResizeCornerIndex;
    
	int										mLoadFrame;
	float									mLoadFrameX;
	float									mLoadFrameY;
	float									mLoadFrameWidth;
	float									mLoadFrameHeight;

    
    
	bool                                    mTimelineEnabled;
	bool									mTimelineFastForward;
	bool									mTimelineSlowMotion;
    
    
	int                                     mTimelineTick;
	int                                     mTimelineTickPrev;
    int                                     mTimelineTickMax;
	int										mTimelineSlowMotionTick;
	int                                     mTimelineLoopStartTick;
	int                                     mTimelineLoopEndTick;
    
    
	void									TimelineApply();
    void                                    TimelineSetMax(int pMax);
	void                                    TimelineSet(int pPos);
	void                                    TimelineNextFrame();
	void                                    TimelinePrevFrame();
    void                                    TimelineReset();
    



};





extern UMainCanvas *gUtils;
extern UNode *gUtilsNode;

#endif






