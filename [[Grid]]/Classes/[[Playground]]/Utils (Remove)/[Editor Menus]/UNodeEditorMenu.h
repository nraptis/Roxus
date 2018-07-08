//
//  UNodeEditorMenu.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/19/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UNodeEditorMenu__
#define ___015_Fleet_XP__UNodeEditorMenu__

//#include "UMenu.h"
#include "UMenuStyleExtended.h"
#include "UMenuStyle.h"


class URectEditorPane : public UMenuPane
{
public:
	URectEditorPane(URoundedRect *pRect);
	virtual ~URectEditorPane();

	virtual void                                Notify(void *pSender);

	URoundedRect								*mRect;

	UColorPicker								*mColorPickerTop;
	UColorPicker								*mColorPickerBottom;
    
	UExtendedSlider								*mSliderCornerRadius;
	UStepper									*mStepperPoints;

	UButton										*mButtonPrint;

	FColor										mColorTop;
	FColor										mColorBottom;
};

class UNodeEditorColorPane : public UMenuPane
{
public:
	UNodeEditorColorPane();
	virtual ~UNodeEditorColorPane();

	virtual void                                Notify(void *pSender);
	virtual void                                SetSelectedNode(UNode *pNode);

	USegment                                    *mSegmentBlend;

	UButton										*mColorButtonReset;
	UButton										*mColorButtonRandom;
	UButton										*mColorButtonInvert;
	UButton										*mColorButtonRotate;

	UColorPicker								*mColorPicker;
};


class UNodeEditorTransformPane : public UMenuPane
{
public:
	UNodeEditorTransformPane();
	virtual ~UNodeEditorTransformPane();

	virtual void                                Notify(void *pSender);
	virtual void                                SetSelectedNode(UNode *pNode);

	UButton										*mResetButtonScale;
	UButton										*mResetButtonRotation;

	UExtendedSlider								*mSliderScale;
	UExtendedSlider								*mSliderRotation;
	UExtendedSlider								*mSliderFrameRate;



};

class UNodeEditorSourcePane : public UMenuPane
{
public:
	UNodeEditorSourcePane();
	virtual ~UNodeEditorSourcePane();

	virtual void                                Notify(void *pSender);
	virtual void                                SetSelectedNode(UNode *pNode);

	USegment                                    *mSegmentType;

	UButton                                     *mButtonTrackParent;
	UButton                                     *mButtonTrackParentOffset;

	UButton                                     *mButtonEditPoly;
	UButton                                     *mButtonEditPointCloud;
	UButton                                     *mButtonEditMotionPath;


	UButton                                     *mButtonIsBox;
	UButton                                     *mButtonIsParticleSource;


	UExtendedSlider                             *mSourceWidth;
	UExtendedSlider                             *mSourceHeight;
	UExtendedSlider                             *mSourceRadius;
};

class UNodeEditorSelectionPane : public UMenuPane
{
public:
    UNodeEditorSelectionPane();
    virtual ~UNodeEditorSelectionPane();
    
    virtual void                                Notify(void *pSender);
    virtual void                                SetSelectedNode(UNode *pNode);
    
    UButton                                     *mButtonEditSprite;
	UButton                                     *mButtonEditSequence;
	UButton                                     *mButtonClone;



	UButton                                     *mButtonSelectNone;
	UButton                                     *mButtonSelectParent;
	UButton                                     *mButtonSelectNext;
	UButton                                     *mButtonSelectPrev;

	UButton                                     *mButtonSendForward;
	UButton                                     *mButtonSendBackwards;
	UButton                                     *mButtonSendFront;
	UButton                                     *mButtonSendBack;
};




class UMainCanvas;
class UNodeEditorMenu : public UMenu
{
public:
    UNodeEditorMenu();
    virtual ~UNodeEditorMenu();

    virtual void                                Notify(void *pSender);
    virtual void                                SetSelectedNode(UNode *pNode);

	UNodeEditorColorPane						*mColorPane;
	UNodeEditorTransformPane					*mTransformPane;



	//UMenuPane                                   *mControlsMainPane;
    

    
    //UMenuPane                                   *mSelectionPane;
    
	//UButton                                 *mButtonClear;
    //UButton                                 *mButtonClone;
    //UButton                                 *mButtonDelete;
    
    
    
    

    UNodeEditorSourcePane                       *mSourcePane;
    
    UNodeEditorSelectionPane                    *mSelPane;
    
    //USegment                                    *mSourceSegmentType;
    //UExtendedSlider                             *mSourceWidth;
    //UExtendedSlider                             *mSourceHeight;
    //UExtendedSlider                             *mSourceRadius;
    
    //UButton                                     *mSourceEditImage;
    //UButton                                     *mSourceEditPathPoly;
    //UButton                                     *mSourceEditPathPointCloud;
    
    
    
};

/*

class UNodeMenuNodePlacement : public UMenu
{
public:
    UNodeMenuNodePlacement();
    virtual ~UNodeMenuNodePlacement();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    USegment                                *mSegmentBlendMode;
    
    UButton                                 *mButtonSelectNext;
    UButton                                 *mButtonSelectPrev;
    
    
    UButton                                 *mButtonSendForward;
    UButton                                 *mButtonSendBackwards;
    
    
    FView                                   *mViewNodeStats;
    
    
    UButton                                 *mButtonScale;
    UButton                                 *mButtonRotation;
    
    
    UColorPicker                            *mColorPicker;
    
    
    USlider                                 *mSliderRotation;
    USlider                                 *mSliderScale;
};

*/



#endif








