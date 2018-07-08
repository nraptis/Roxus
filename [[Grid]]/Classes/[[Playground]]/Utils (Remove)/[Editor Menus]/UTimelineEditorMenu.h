//
//  UTimelineEditorMenu.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/22/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UTimelineEditorMenu__
#define ___015_Fleet_XP__UTimelineEditorMenu__

#include "UMenu.h"
#include "UMenuStyle.h"
#include "UMenuStyleExtended.h"
#include "FMotionPath.h"

class UMainCanvas;

class UTimelineKeyFramePicker : public FView
{
public:
	UTimelineKeyFramePicker();
	virtual ~UTimelineKeyFramePicker();

	virtual void                            Update();
	virtual void                            Draw();

	virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchMove(float pX, float pY, void *pData);
	virtual void                            TouchUp(float pX, float pY, void *pData);
	virtual void                            TouchFlush();

	virtual void                            Notify(void *pSender);
	virtual void                            Refresh(UNode *pNode);
    
	void									*mDragData;
	float									mDragStartFrameX;
	float									mDragStartTouchX;

};

class UTimelineEditorSelectedKeyPane : public UMenuPane
{
public:
    UTimelineEditorSelectedKeyPane();
    virtual ~UTimelineEditorSelectedKeyPane();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    
    
    UExtendedSlider                         *mSliderRotation;
    
    
    
    
    
    UButton                                 *mButtonTrackScreen;
    UButton                                 *mButtonRead;
    
    
    USegment                                *mRelationTypeSegmentX;
    USegment                                *mRelationTypeSegmentY;
    UExtendedSlider                         *mSliderTrackOffX;
    UExtendedSlider                         *mSliderTrackOffY;

};



class UTimelineEditorKeyFramePane : public UMenuPane
{
public:
	UTimelineEditorKeyFramePane();
	virtual ~UTimelineEditorKeyFramePane();
    
	virtual void                            Notify(void *pSender);
	virtual void                            SetSelectedNode(UNode *pNode);
    virtual void							Refresh();
    
    UButton                                 *mButtonExport;
    
	UButton									*mButtonDelete;
	UButton									*mButtonDeleteAll;

	UButton									*mButtonKeySelectNext;
	UButton									*mButtonKeySelectPrev;

	UButton									*mButtonCreate1;
	UButton									*mButtonCreate2;
	UButton									*mButtonCreate3;

	UStepper								*mStepperType;
	ULabel									*mLabelType;
    
    
    
};

class UTimelineEditorControlPane : public UMenuPane
{
public:
	UTimelineEditorControlPane();
	virtual ~UTimelineEditorControlPane();

	UButton										*mButtonPlay;

	UButton										*mButtonNextFrame;
	UButton										*mButtonPrevFrame;
	UButton										*mButtonSelectedFrame;

	UButton										*mButtonFastForward;
	UButton										*mButtonSlowMotion;

	UButton										*mButtonLoopSetStart;
	UButton										*mButtonLoopSetEnd;
    
    UButton										*mButtonSpan50;
    UButton										*mButtonSpan100;
    UButton										*mButtonSpan200;
    UButton										*mButtonSpan400;

	virtual void                                Refresh();
	virtual void                                Notify(void *pSender);
};

class UTimelineEditorMenu : public UMenu
{
public:
    UTimelineEditorMenu();
    virtual ~UTimelineEditorMenu();
    
	virtual void								Update();
	virtual void								Draw();

	virtual void								TouchDown(float pX, float pY, void *pData);
	virtual void								TouchMove(float pX, float pY, void *pData);
	virtual void								TouchUp(float pX, float pY, void *pData);
	virtual void								TouchFlush();


	virtual void								Notify(void *pSender);
	virtual void								SetSelectedNode(UNode *pNode);

	void										RefreshThumb();
    
	UTimelineEditorControlPane					*mControlPane;

	UTimelineKeyFramePicker						*mKeyPicker;

	UTimelineEditorKeyFramePane					*mKeyFramePane;


	FRect										mTimelineRect;

	FRect										mThumbRect;


	float										mThumbWidth;
	FRect										mTimelineBarRect;



	void										*mDragData;
	float										mDragThumbX;
	float										mDragStartTouchX;

	URoundedRect								mDrawThumbRectOutline;
	URoundedRect								mDrawThumbRectBottom;
	URoundedRect								mDrawThumbRectFront;


	URoundedRect								mDrawBarRectBottom;
	URoundedRect								mDrawBarRectFront;

	URoundedRect								mDrawEdgeRectBottom;
	URoundedRect								mDrawEdgeRectFront;



    //UMenuPane                               *mTimelinePane;
    
    //UMenuPane                               *mPane1;
    //UButton                                 *mPane1Button;
    
    //UMenuPane                               *mSubPane1;
    //UButton                                 *mPane1Button1;
    //UButton                                 *mPane1Button2;
    
    //UMenuPane                               *mSubPane2;
    //UExtendedSlider                         *mPane2Slider1;
    
    //UMenuPane                               *mSubPane3;
    //UExtendedSlider                         *mPane3Slider1;
    //UExtendedSlider                         *mPane3Slider2;
    //UExtendedSlider                         *mPane3Slider3;
    
    
    UTimelineEditorSelectedKeyPane              *mSelKeyPane;
};




#endif /* defined(___015_Fleet_XP__UTimelineEditorMenu__) */
