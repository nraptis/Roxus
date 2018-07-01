//
//  UParticleEditorMenu.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/22/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UParticleEditorMenu__
#define ___015_Fleet_XP__UParticleEditorMenu__

#include "UMenuStyle.h"
#include "UMenuStyleExtended.h"
#include "UNode.h"

class UParticleEditorDefaultsPane : public UMenuPane
{
public:

	UParticleEditorDefaultsPane();
	virtual ~UParticleEditorDefaultsPane();

	virtual void                            Notify(void *pSender);
	virtual void                            SetSelectedNode(UNode *pNode);


	UMenuPane                               *mQuickResetPane;

	

	UButton									*mQuickRandom1;
	UButton									*mQuickRandom2;
    UButton									*mQuickRandom3;

    UButton                                 *mQuickResetButtonAll;
	UButton									*mQuickResetButtonAllOffsets;
	UButton									*mQuickResetButtonAllSpeeds;
	UButton									*mQuickResetButtonAllRotations;
	UButton									*mQuickResetButtonAllScales;
	UButton									*mQuickResetButtonAllColors;
	

	/*
	UMenuPane                               *mResetPane;
	UButton									*mResetButtonAll;
	UButton									*mResetButtonPos;
	UButton									*mResetButtonSpeed;
	UButton									*mResetButtonScale;
	UButton									*mResetButtonRotation;
	UButton									*mResetButtonColor;
	*/

};


class UParticleEditorOffsetPane : public UMenuPane
{
public:
	UParticleEditorOffsetPane();
	virtual ~UParticleEditorOffsetPane();

	virtual void                            Notify(void *pSender);
	virtual void                            SetSelectedNode(UNode *pNode);

	UExtendedSlider							*mSliderOffsetX;
	UExtendedSlider							*mSliderOffsetY;
	UExtendedSlider							*mSliderOffsetXRandom;
	UExtendedSlider							*mSliderOffsetYRandom;

	UButton									*mButtonSpawnFromParentGeometry;
	UButton									*mButtonSpawnFromParentLocation;

};


class UParticleEditorFramePane : public UMenuPane
{
public:
    UParticleEditorFramePane();
    virtual ~UParticleEditorFramePane();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    UExtendedSlider							*mSliderFrameSpeed;
    UExtendedSlider							*mSliderFrameSpeedRandom;
    
    UButton									*mButtonStartRandom;
    UButton									*mButtonLoop;
    
};


class UParticleEditorDelayPane : public UMenuPane
{
public:
    UParticleEditorDelayPane();
    virtual ~UParticleEditorDelayPane();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    UStepper                                *mStepperScale;
    UExtendedSlider							*mSliderScale;
    
    UStepper                                *mStepperAlpha;
    UExtendedSlider							*mSliderAlpha;
};


class UParticleEditorSpeedPane : public UMenuPane
{
public:
	UParticleEditorSpeedPane();
	virtual ~UParticleEditorSpeedPane();

	virtual void                            Notify(void *pSender);
	virtual void                            SetSelectedNode(UNode *pNode);

	UMenuPane								*mPaneBase;
	UExtendedSlider							*mSpeedSliderX;
	UExtendedSlider							*mSpeedSliderY;
	UExtendedSlider							*mSpeedSliderXRandom;
	UExtendedSlider							*mSpeedSliderYRandom;


	UMenuPane								*mPaneAccel;
	UExtendedSlider							*mSpeedSliderAccel;
	
	UExtendedSlider							*mSpeedSliderGravityX;
	UExtendedSlider							*mSpeedSliderGravityY;

	UExtendedSlider							*mSpeedSliderGravityYAdd;
};

class UParticleEditorDirectionalSpeedPane : public UMenuPane
{
public:
	UParticleEditorDirectionalSpeedPane();
	virtual ~UParticleEditorDirectionalSpeedPane();

	virtual void                            Notify(void *pSender);
	virtual void                            SetSelectedNode(UNode *pNode);

	UExtendedSlider							*mSliderDirMagnitude;
	UExtendedSlider							*mSliderDirMagnitudeRandom;

	UExtendedSlider							*mSliderDirAngle;
	UExtendedSlider							*mSliderDirAngleRandom;

	UExtendedSlider							*mSliderDirPush;
	UExtendedSlider							*mSliderDirPushRandom;
};

class UParticleEditorSpawnPane : public UMenuPane
{
public:
	UParticleEditorSpawnPane();
	virtual ~UParticleEditorSpawnPane();
    
	virtual void                                Notify(void *pSender);
	virtual void                                SetSelectedNode(UNode *pNode);
    
    UMenuPane                                   *mInfoPane;
    UButton                                     *mInfoButtonSeedRandom;
    ULabel                                      *mInfoLabelSeed;
    
    
    UMenuPane                                   *mPaneClusters;
	UStepper                                    *mStepperCount;
	UStepper                                    *mStepperCountRandom;
	UStepper                                    *mStepperStartDelayRandom;
    
    
    UMenuPane                                   *mPaneWaves;
    UStepper                                    *mStepperWaveCount;
    UStepper                                    *mStepperWaveCountRandom;
	UStepper                                    *mStepperWaveInterval;
	UStepper                                    *mStepperWaveIntervalRandom;
    

    
    int                                         mSpawnParticleCount;
    int                                         mSpawnParticleCountRandom;
    
    int                                         mSpawnWaveCount;
    int                                         mSpawnWaveCountRandom;
    
    int                                         mSpawnWaveInterval;
    int                                         mSpawnWaveIntervalRandom;
    
    int                                         mSpawnParticleStartDelayRandom;
    
    
};

class UParticleEditorColorPane : public UMenuPane
{
public:
    UParticleEditorColorPane();
    virtual ~UParticleEditorColorPane();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    UColorPicker                            *mColorPicker;
    UColorPicker                            *mColorPickerExtra;
    UColorPicker                            *mColorPickerRandom;
    UColorPicker                            *mColorPickerSpeed;
    UColorPicker                            *mColorPickerSpeedRandom;
};

class UParticleEditoScalePane : public UMenuPane
{
public:
    UParticleEditoScalePane();
    virtual ~UParticleEditoScalePane();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    
    UMenuPane                               *mPaneMain;
    
    UExtendedSlider                         *mSliderScale;
    UExtendedSlider                         *mSliderScaleRandom;
    
    UMenuPane                               *mPaneXY;
    UExtendedSlider                         *mSliderScaleX;
    UExtendedSlider                         *mSliderScaleY;
    
    UMenuPane                               *mPaneSpeed;
    
    UExtendedSlider                         *mSliderSpeed;
    UExtendedSlider                         *mSliderSpeedRandom;
    UExtendedSlider                         *mSliderSpeedAdd;
    UExtendedSlider                         *mSliderSpeedAccel;
    
    
};

class UParticleEditorRotationPane : public UMenuPane
{
public:
    UParticleEditorRotationPane();
    virtual ~UParticleEditorRotationPane();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
	UButton                                 *mRotationButtonRandomNegative;
	UButton                                 *mRotationButtonRandomNegativeSpeed;

    UExtendedSlider                         *mRotationSlider;
    UExtendedSlider                         *mRotationSliderRandom;
    
    UExtendedSlider                         *mRotationSliderSpeed;
    UExtendedSlider                         *mRotationSliderSpeedRandom;
    UExtendedSlider                         *mRotationSliderSpeedAccel;
    
};

class UParticleEditorMenu1 : public UMenu
{
public:
    
    UParticleEditorMenu1();
    virtual ~UParticleEditorMenu1();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    UParticleEditorDefaultsPane				*mDefaultsPane;
    UParticleEditorSpawnPane				*mSpawnPane;
    UParticleEditoScalePane                 *mScalePane;
    UParticleEditorRotationPane             *mRotationPane;
    UParticleEditorSpeedPane				*mSpeedPane;
    
    
    
    
    UParticleEditorOffsetPane				*mOffsetPane;
    UParticleEditorColorPane                *mColorPane;
    UParticleEditorDirectionalSpeedPane     *mDirectionalSpeedPane;
    UParticleEditorDelayPane                *mDelayPane;
    UParticleEditorFramePane				*mFramePane;
    
    
    
    
    
    
};


/*
class UParticleEditorMenu2 : public UMenu
{
public:
    
    UParticleEditorMenu2();
    virtual ~UParticleEditorMenu2();
    
    virtual void                            Notify(void *pSender);
    virtual void                            SetSelectedNode(UNode *pNode);
    
    
    
};

*/



#endif /* defined(___015_Fleet_XP__UParticleEditorMenu__) */
