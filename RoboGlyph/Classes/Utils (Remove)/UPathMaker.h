//
//  UUPathMaker.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/23/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UUPathMaker__
#define ___015_Fleet_XP__UUPathMaker__

#include "FView.h"
#include "UMenu.h"
#include "UMenuStyleExtended.h"

#include "FMotionPath.h"

#include "FSpline.h"
#include "FView.h"
#include "FButton.h"
#include "FSlider.hpp"
#include "FDrawQuad.h"
#include "FModelData.h"

#define GKMTV_MODE_CREATE_POINTS 0
#define GKMTV_MODE_SELECT_POINTS 1
#define GKMTV_MODE_SELECT_TANGENTS 2
#define GKMTV_MODE_MAKE_TRIANGLES 3
#define GKMTV_MODE_CENTER 4

class UPathMaker;
class UPathMakerSymmetryPane : public UMenuPane
{
public:
	UPathMakerSymmetryPane();
	virtual ~UPathMakerSymmetryPane();

	void                                            SetPathMaker(UPathMaker *pPathMaker);
	UPathMaker                                      *mPathMaker;

	virtual void                                    Notify(void *pSender);
};


class UPathMakerMenu : public UMenu
{
public:
    UPathMakerMenu();
    virtual ~UPathMakerMenu();
    
    void                                            SetPathMaker(UPathMaker *pPathMaker);
    UPathMaker                                      *mPathMaker;
    
    virtual void                                    Notify(void *pSender);
    virtual void                                    CloseMenu();
    
    
    void                                            Refresh();

	UPathMakerSymmetryPane							*mSymmetryPane;
    
    UMenuPane                                       *mPathPane;
    
    USegment                                        *mPathSegmentMode;
    
    UButton                                         *mPathButtonCreateNew;
    UButton                                         *mPathButtonPrint;
    
    UButton                                         *mPathButtonTriangleDeleteLast;
    UButton                                         *mPathButtonTriangleDeleteAll;
    
    
    UButton                                         *mPathButtonDelete;
    UButton                                         *mPathButtonDeleteAll;
    
    UButton                                         *mPathSelectButtonLock;
    UButton                                         *mPathSelectButtonNext;
    UButton                                         *mPathSelectButtonPrev;
    
    
    UMenuPane                                       *mPointPane;
    
    UButton                                         *mPointShiftButtonL;
    UButton                                         *mPointShiftButtonR;
    UButton                                         *mPointShiftButtonU;
    UButton                                         *mPointShiftButtonD;
    
    UButton                                         *mPointSelectButtonNext;
    UButton                                         *mPointSelectButtonPrev;
    UButton                                         *mPointSelectButtonClear;
    UButton                                         *mPointSelectButtonDelete;
    UButton                                         *mPointSelectButtonInsert;
    
    UButton                                         *mButtonAllowDragPoints;
    UButton                                         *mButtonAllowDragTangents;
    UButton                                         *mButtonCircular;
    UButton                                         *mButtonTangentsLockDirection;
    
    
    
    UMenuPane                                       *mPaneLook;
    
    UColorPicker                                    *mColorPickerBackground;
    UExtendedSlider                                 *mSliderOpacity;
    
    UButton                                         *mButtonDrawPoints;
    UButton                                         *mButtonDrawLines;
    //UButton                                         *mButtonDrawTangents;
    UButton                                         *mButtonDrawReference;
    
    
    
    UButton                                         *mButtonPointAddAfter;
    UButton                                         *mButtonPointRemove;
    
    
    
};

class UPathMaker : public FView
{
public:
    UPathMaker();
    virtual ~UPathMaker();

    void                                            SetUp(UNode *pNode, int pPathType);

    int                                             mPathType;
    
    UPathMakerMenu                                  *mPathMakerMenu;
    
    virtual void                                    Update();
    virtual void                                    Draw();
    
    
    virtual void                                    TouchDown(float pX, float pY, void *pData);
    virtual void                                    TouchMove(float pX, float pY, void *pData);
    virtual void                                    TouchUp(float pX, float pY, void *pData);
    virtual void                                    TouchFlush();
    
	virtual void									MouseWheel(int pDirection);
	virtual void									KeyDown(int pKey);
	
    void                                            SetMode(int pMode);
    int                                             mMode;
    
    
    int                                             mDragMode;
	int												mStartMode;

    int                                             mSelectedPointIndex;
    int                                             mSelectedTanSide;
    
    bool                                            mDragging;
    void                                            *mDragData;
    
    float                                           mDragTouchStartX;
    float                                           mDragTouchStartY;
    
    float                                           mDragNodeStartX;
    float                                           mDragNodeStartY;
    
    float                                           mDragTranslateShiftX;
    float                                           mDragTranslateShiftY;
    
    
    bool                                            mAllowDragPoint;
    bool                                            mAllowDragTan;
    bool                                            mTanLockDir;
    
	bool                                            mDrawCenter;
	bool                                            mDrawPoints;
    bool                                            mDrawEdges;
    bool                                            mDrawEdgesClosed;
    //bool                                            mDrawTangents;
    
    bool                                            mDrawReference;
    bool                                            mDrawNumbers;
    
    
    
    bool                                            mCreateNewPath;


    FMotionPathTemplate                             *mSelectedPath;
    FMotionPathTemplate                             *mSelectedPathLockTarget;


    void                                            PathSelectionDragLockToggle();
    void                                            PathSelectionClear();
    void                                            PathSelectionNext();
	void                                            PathSelectionPrev();
	void                                            PathSelectionShift(float pMoveX, float pMoveY);
    void                                            PathDeleteSelected();
    void                                            PathDeleteAll();
    
    void                                            PointSelectionNext();
    void                                            PointSelectionPrev();
    void                                            PointSelectionClear();
    void                                            PointSelectionDelete();
    void                                            PointSelectionInsert();
	void                                            PointSelectionShift(float pMoveX, float pMoveY);
    void                                            PointSelectionTrianglesDeleteLast();
    void                                            PointSelectionTrianglesDeleteAll();
    
    
    void                                            Print();
    
    
    
    
    FList                                           mPathList;
    
    void                                            FindSelectablePaths();
    FList                                           mSelectablePathList;
    
    bool                                            IsSelectable(FMotionPathTemplate *pPath);
    bool                                            IsSelected(FMotionPathTemplate *pPath);
    
    
    float                                           mTranX;
    float                                           mTranY;
    
    float                                           mTranScale;
    
    float                                           mTranScaleX;
    float                                           mTranScaleY;
    float                                           mTranRotation;
    
    
    void                                            TransformRead(UNode *pNode);
    void                                            GetAbsolutePaths(FList *pList);
    
    
    void                                            SymmetrySlice(bool pHor, bool pSide);
    void                                            SymmetryApply();
    
    
    bool                                            mSymmetryEnabled;
    bool                                            mSymmetryHorizontal;
    bool                                            mSymmetrySide;
    
    float                                           mSymmetryCenterX;
    float                                           mSymmetryCenterY;
    
    //float                                           mSymmetryRotation;
    
    //FMotionPathTemplate                             mSymmetrySlicePath1;
    //FMotionPathTemplate                             mSymmetrySlicePath2;
    
    FPointList                                      mSymmetryEdgeList1;
    FPointList                                      mSymmetryEdgeList2;
    
    FPointList                                      mSymmetryEdgeListMirror1;
    FPointList                                      mSymmetryEdgeListMirror2;
    
    //FMotionPathTemplate                             mSymmetryMirrorPath;
    
    FSprite                                         *mSprite;
    FSpriteSequence                                 *mSpriteSequence;
    
    float                                           mSpriteSequenceFrame;
    bool                                            mSpriteSequenceFrameUpdate;
    
    FColor                                          mBackgroundColor;
    float                                           mOpacity;
    
    
    UNode                                           *mNode;
    
    
    
    FPointList                                      mTrianglePointList;
    int                                             mTriangleSelectionStep;
    int                                             mTriangleSelectionIndex1;
    int                                             mTriangleSelectionIndex2;
    int                                             mTriangleSelectionIndex3;
    
    
    
    
    
    
};

#endif /* defined(___015_Fleet_XP__UUPathMaker__) */
