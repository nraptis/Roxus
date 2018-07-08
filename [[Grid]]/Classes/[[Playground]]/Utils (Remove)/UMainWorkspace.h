//
//  UMainCanvas.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef UTILS_MAIN_WORKSPACE_H
#define UTILS_MAIN_WORKSPACE_H

#define UTIL_WS_MODE_SELECT_AND_DRAG 0
#define UTIL_WS_MODE_TRANSFORM 1
#define UTIL_WS_MODE_PAN 2
#define UTIL_WS_MODE_LINK 3
#define UTIL_WS_MODE_SET_CURSOR 4

#include "UNode.h"
#include "UMenu.h"
#include "FSprite.h"
#include "FSpriteSequence.h"
#include "FSpline.h"
#include "UMainToolbar.h"
#include "FFile.h"
//#include "FLinePath.h"
#include "FMotionPath.h"
#include "FMotionObject.h"

class UPathMaker;

class UMainWorkspace : public FView
{
public:
    
	UMainWorkspace();
	virtual ~UMainWorkspace();

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


	void									FindHeirarchy();
	void									FindTracking(UNode *pNode);

	//mObject



	float                                   mSelectCursorX;
	float                                   mSelectCursorY;

	void                                    SetMode(int pMode);
	int                                     mMode;
    int                                     mModeNext;

	void									Clear();


	void									CreateNodeSprite();
	void									CreateNodeSpriteSequence();
	void									CreateNodeParticles();
	void									CreateNodeRectangle();

	void									EditNodeSprite();
	void									EditNodeSpriteSequence();


	FList									mMotionObjects;


	void                                    AddNode();
	void                                    AddSpriteNode(FSprite *pSprite);
	void                                    AddSequenceNode(FSpriteSequence *pSpriteSequence);
	void                                    AddNode(UNode *pNode);
	FList                                   mNodeList;

	void									DeleteNode(UNode *pNode);
	FList									mListDelete;

	void                                    FindSelectableNodes();
	FList                                   mNodeListSelectable;
	FList									mListAdd;
	
	bool                                    mDrawNodes;

	

	virtual void                            SetSelectedNode(UNode *pNode);
	virtual void                            SetSelectedNode();

	void                                    Deselect();

	void                                    SelectionGetParent();
	void                                    SelectionMoveUp();
	void                                    SelectionMoveDown();
	void                                    SelectionMoveFront();
	void                                    SelectionMoveBack();

	void                                    SelectionPickNext();
	void                                    SelectionPickPrevious();


	void                                    SelectionImageNext();
	void                                    SelectionImagePrev();

	void                                    SelectionParentPickNext();
	void                                    SelectionParentPickPrevious();

	void                                    SelectionClone();
	void                                    SelectionShift(float pX, float pY);

	void									SelectionDelete();

	


	

	


	bool                                    mDragging;
	void                                    *mDragData;

	UNode                                   *GetTouchNode(float pX, float pY, UNode *pIgnoreNode);

	

	float                                   mDraggingCornerStartRotation;
	float                                   mDraggingCornerStartRotationFromPoint;

	float                                   mDragImageStartX;
	float                                   mDragImageStartY;
	float                                   mDragTouchStartX;
	float                                   mDragTouchStartY;

	UNode                                   *mLinkStartNode;
	UNode                                   *mLinkTargetNode;

	float                                   mDragTransformStartScale;
	float                                   mDragTransformStartRotation;

	void									SetTime(int pTime);

	void                                    Save(FFile *pFile);
	void                                    Load(FFile *pFile);


	float									mWallLeft;
	float									mWallRight;
	float									mWallTop;
	float									mWallBottom;



    void									Export();
    FString									Export(UNode *pNode);

    FString									ExportPassDeclarations(UNode *pNode);
    FString									ExportPassInfo(UNode *pNode);
    FString									ExportPassParticleData(UNode *pNode);
    FString									ExportPassLinkWorld(UNode *pNode);
    FString									ExportPassLinkParents(UNode *pNode);
    FString									ExportPassLinkTracking(UNode *pNode);
    FString									ExportPassFinalize(UNode *pNode);
    
    
    void									ExportReset();
	int										ExportPrepare(UNode *pNode, int pIndex);
    FString                                 ExportApplyActions(UNode *pNode, FList *pList);
    
    void									ExportSetUp(UNode *pNode);
    FList                                   mExportList;
    
    
    void									ExportOffsets();
    FString									ExportOffsets(UNode *pNode);
    
    void									ExportParticleBasic();
    FString									ExportParticleBasic(UNode *pNode);
    
    void									ExportPaths();
    FString									ExportPaths(UNode *pNode);
    
    
    
    void                                    ExportRel(int pSideX, int pSideY, bool pUntransform);
    void                                    ExportRelChildren(int pSideX, int pSideY, bool pUntransform);
    
    
    
};

//class UMainCanvasCont

extern UMainWorkspace *gUtilWS;

#endif






