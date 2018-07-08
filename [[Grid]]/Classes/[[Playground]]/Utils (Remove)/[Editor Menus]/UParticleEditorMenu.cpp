//
//  UParticleEditorMenu.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/22/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UParticleEditorMenu.h"
#include "UMainCanvas.h"
#include "core_includes.h"




UParticleEditorMenu1::UParticleEditorMenu1()
{
    SetText("Particles");
    SetFrame(mX, mY, 480.0f, mHeight);
    
    mDefaultsPane = new UParticleEditorDefaultsPane();
    mSpawnPane = new UParticleEditorSpawnPane();
    mScalePane = new UParticleEditoScalePane();
    mRotationPane = new UParticleEditorRotationPane();
    mSpeedPane = new UParticleEditorSpeedPane();
    
    AddLine(mDefaultsPane);
    AddLine(mSpawnPane);
    AddLine(mScalePane);
    AddLine(mRotationPane);
    AddLine(mSpeedPane);
    
    
    mDefaultsPane->Collapse();
    //mSpawnPane
    mScalePane->Collapse();
    mRotationPane->Collapse();
    mSpeedPane->Collapse();


    
    
    
    mOffsetPane = new UParticleEditorOffsetPane();
    mColorPane = new UParticleEditorColorPane();
    mDirectionalSpeedPane = new UParticleEditorDirectionalSpeedPane();
    mDelayPane = new UParticleEditorDelayPane();
    mFramePane = new UParticleEditorFramePane();
    
    
//    UMenuPane *aDopePane1 = new UMenuPane("DOPE-1", true);
//    mDefaultsPane->AddLine(aDopePane1);
//    
//    UMenuPane *aDopePane2 = new UMenuPane("DOPE-2", true);
//    aDopePane1->AddLine(aDopePane2);
//    
//    
//    UMenuPane *aDopePane11 = new UMenuPane("d11", true);
//    aDopePane1->AddLine(aDopePane11);
//    
//    UMenuPane *aDopePane12 = new UMenuPane("d11", true);
//    aDopePane1->AddLine(aDopePane12);
//    
//    
//    UMenuPane *aDopePane121 = new UMenuPane("d11", true);
//    aDopePane12->AddLine(aDopePane121);
//    
//    UMenuPane *aDopePane21 = new UMenuPane("d21", true);
//    aDopePane12->AddLine(aDopePane21);
//    
    
    
    
    
    AddLine(mOffsetPane);
    AddLine(mColorPane);
    AddLine(mDirectionalSpeedPane);
    AddLine(mDelayPane);
    AddLine(mFramePane);
    
    mOffsetPane->Collapse();
    mColorPane->Collapse();
    mDirectionalSpeedPane->Collapse();
    mDelayPane->Collapse();
    mFramePane->Collapse();
    
    
    mAllowMultipleExpandedSubpanes = false;
}

UParticleEditorMenu1::~UParticleEditorMenu1()
{
    
}

void UParticleEditorMenu1::Notify(void *pSender)
{
    
}

void UParticleEditorMenu1::SetSelectedNode(UNode *pNode)
{
    
}


/*
UParticleEditorMenu2::UParticleEditorMenu2()
{
    SetText("Particles 2");
    SetFrame(mX, mY, 420.0f, mHeight);
    
    
    
    mAllowMultipleExpandedSubpanes = false;
}

UParticleEditorMenu2::~UParticleEditorMenu2()
{
    
}

void UParticleEditorMenu2::Notify(void *pSender)
{
    
}

void UParticleEditorMenu2::SetSelectedNode(UNode *pNode)
{
    
}
*/



UParticleEditorColorPane::UParticleEditorColorPane()
{
    SetExpandable(true);
    SetText("Color");
    
    mColorPicker = new UColorPicker();
    mColorPicker->SetText("Start");
    mColorPicker->SetNormalRange();
    AddLine(mColorPicker);
    mColorPicker->Expand();
    
    
    //mColorPickerExtra = new UColorPicker();
    //mColorPickerExtra->SetText("Base-Extra");
    //mColorPickerExtra->SetExtraRange();
    //AddLine(mColorPickerExtra);
    
    
    mColorPickerRandom = new UColorPicker();
    mColorPickerRandom->SetText("Color Rand");
    mColorPickerRandom->SetRandomRange();
    AddLine(mColorPickerRandom);
    mColorPickerRandom->Collapse();
    
    mColorPickerSpeed = new UColorPicker();
    mColorPickerSpeed->SetText("ColorSpeed");
    mColorPickerSpeed->SetSpeedRange();
    AddLine(mColorPickerSpeed);
    mColorPickerSpeed->Collapse();
    
    
    mColorPickerSpeedRandom = new UColorPicker();
    mColorPickerSpeedRandom->SetText("Speed-Rand");
    mColorPickerSpeedRandom->SetSpeedRange();
    AddLine(mColorPickerSpeedRandom);
    mColorPickerSpeedRandom->Collapse();
    
}

UParticleEditorColorPane::~UParticleEditorColorPane()
{
    
}

void UParticleEditorColorPane::Notify(void *pSender)
{
    
}

void UParticleEditorColorPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mColorPicker->SetColor(&(pNode->mTemplate.mSpawnColor));
        mColorPickerRandom->SetColor(&(pNode->mTemplate.mSpawnColorRandom));
        mColorPickerSpeed->SetColor(&(pNode->mTemplate.mSpawnColorSpeed));
        mColorPickerSpeedRandom->SetColor(&(pNode->mTemplate.mSpawnColorSpeedRandom));
    }
    else
    {
        mColorPicker->SetColor(0);
        //mColorPickerExtra->SetColor(0);
        mColorPickerRandom->SetColor(0);
        mColorPickerSpeed->SetColor(0);
        mColorPickerSpeedRandom->SetColor(0);
    }
}



UParticleEditorSpawnPane::UParticleEditorSpawnPane()
{
    SetExpandable(true);
    SetText("Spawn");
    

    
    mInfoPane = new UMenuPane("Info", true, false);
    AddLine(mInfoPane);
    
    mInfoButtonSeedRandom = new UButton("Seed Random");
    mInfoLabelSeed = new ULabel("S = %d");
    mInfoPane->AddLine(mInfoButtonSeedRandom, mInfoLabelSeed);
    
    
    mPaneClusters = new UMenuPane("Clusters", true);
    AddLine(mPaneClusters);
    
    mStepperCount = new UStepper("Count");
    mPaneClusters->AddLine(mStepperCount);
    
    mStepperCountRandom = new UStepper("Rand");
    mPaneClusters->AddLine(mStepperCountRandom);
    
    mStepperStartDelayRandom = new UStepper("Stagger");
    mPaneClusters->AddLine(mStepperStartDelayRandom);
    
    
    mPaneWaves = new UMenuPane("Waves", true);
    AddLine(mPaneWaves);
    
    mStepperWaveCount = new UStepper("Count");
    mPaneWaves->AddLine(mStepperWaveCount);
    
    mStepperWaveCountRandom = new UStepper("Rand");
    mPaneWaves->AddLine(mStepperWaveCountRandom);
    
    mStepperWaveInterval = new UStepper("Intrvl");
    mPaneWaves->AddLine(mStepperWaveInterval);
    
    mStepperWaveIntervalRandom = new UStepper("Rand");
    mPaneWaves->AddLine(mStepperWaveIntervalRandom);
    
    mPaneWaves->Collapse();
}

UParticleEditorSpawnPane::~UParticleEditorSpawnPane()
{
    
}

void UParticleEditorSpawnPane::Notify(void *pSender)
{
    if(pSender == mInfoButtonSeedRandom)
    {
        if(gUtilsNode)
        {
            gUtilsNode->mTemplate.Seed();
        }
    }
    
    if(gUtils)
    {
        gUtils->SetSelectedNode();
    }
}

void UParticleEditorSpawnPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mStepperCount->SetTarget(&(pNode->mTemplate.mSpawnParticleCount));
        mStepperCountRandom->SetTarget(&(pNode->mTemplate.mSpawnParticleCountRandom));
        mStepperStartDelayRandom->SetTarget(&(pNode->mTemplate.mSpawnParticleStartDelayRandom));
        
        mStepperWaveCount->SetTarget(&(pNode->mTemplate.mSpawnWaveCount));
        mStepperWaveCountRandom->SetTarget(&(pNode->mTemplate.mSpawnWaveCountRandom));
        
        mStepperWaveInterval->SetTarget(&(pNode->mTemplate.mSpawnWaveInterval));
        mStepperWaveIntervalRandom->SetTarget(&(pNode->mTemplate.mSpawnWaveIntervalRandom));
        
        mInfoLabelSeed->SetText(FString(FString("Sd: ") + FString(pNode->mTemplate.mSeed)).c());
        
    }
    else
    {
        mStepperCount->SetTarget(0);
        mStepperCountRandom->SetTarget(0);
        mStepperStartDelayRandom->SetTarget(0);
        
        
        mStepperWaveCount->SetTarget(0);
        mStepperWaveCountRandom->SetTarget(0);
        
        mStepperWaveInterval->SetTarget(0);
        mStepperWaveIntervalRandom->SetTarget(0);
        
        mInfoLabelSeed->SetText("????");
        
    }
}


UParticleEditorDelayPane::UParticleEditorDelayPane()
{
    SetExpandable(true);
    SetText("Delayed Triggers");
    
    mSliderScale = new UExtendedSlider("Scale", -0.02, 0.02);
    AddLine(mSliderScale);
    
    mStepperScale = new UStepper("S-Tim", 0);
    AddLine(mStepperScale);
    
    mSliderAlpha = new UExtendedSlider("Alpha", -0.02, 0.02);
    AddLine(mSliderAlpha);
    
    mStepperAlpha = new UStepper("A-Tim", 0);
    AddLine(mStepperAlpha);
}

UParticleEditorDelayPane::~UParticleEditorDelayPane()
{
    
}

void UParticleEditorDelayPane::Notify(void *pSender)
{
    
}

void UParticleEditorDelayPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mStepperScale->SetTarget(&(pNode->mTemplate.mSpawnDelayScaleSpeedAddTime));
        mSliderScale->SetTarget(&(pNode->mTemplate.mSpawnDelayScaleSpeedAdd));
        
        mStepperAlpha->SetTarget(&(pNode->mTemplate.mSpawnDelayAlphaSpeedAddTime));
        mSliderAlpha->SetTarget(&(pNode->mTemplate.mSpawnDelayAlphaSpeedAdd));
    }
    else
    {
        mStepperScale->SetTarget(0);
        mSliderScale->SetTarget(0);
        
        mStepperAlpha->SetTarget(0);
        mSliderAlpha->SetTarget(0);
    }
}



UParticleEditorRotationPane::UParticleEditorRotationPane()
{
    SetExpandable(true);
    SetText("Rotation");
    
    mRotationSlider = new UExtendedSlider("Rot", 0, 360.0f);
    AddLine(mRotationSlider);
    
    mRotationSliderRandom = new UExtendedSlider("Rand", 0, 360.0f);
    AddLine(mRotationSliderRandom);
    
    mRotationSliderSpeed = new UExtendedSlider("Sp", 0.0f, 20.0f);
    AddLine(mRotationSliderSpeed);
    
    mRotationSliderSpeedRandom = new UExtendedSlider("Rand", 0.0f, 20.0f);
    AddLine(mRotationSliderSpeedRandom);
    
    
    mRotationSliderSpeedAccel = new UExtendedSlider("Sp-A", 0.85f, 1.0f);
    AddLine(mRotationSliderSpeedAccel);
    
    
    
    mRotationButtonRandomNegative = new UButton("Rnd Neg");
    mRotationButtonRandomNegative->StyleSetCheckBox();
    
    mRotationButtonRandomNegativeSpeed = new UButton("Rnd Neg Spd");
    mRotationButtonRandomNegativeSpeed->StyleSetCheckBox();
    
    AddLine(mRotationButtonRandomNegative, mRotationButtonRandomNegativeSpeed);
}

UParticleEditorRotationPane::~UParticleEditorRotationPane()
{
    
}

void UParticleEditorRotationPane::Notify(void *pSender)
{
    
}

void UParticleEditorRotationPane::SetSelectedNode(UNode *pNode)
{
    
    if(pNode)
    {
        mRotationSlider->SetTarget(&(gUtilsNode->mTemplate.mSpawnRotation));
        mRotationSliderRandom->SetTarget(&(gUtilsNode->mTemplate.mSpawnRotationRandom));
        mRotationSliderSpeed->SetTarget(&(gUtilsNode->mTemplate.mSpawnRotationSpeed));
        mRotationSliderSpeedRandom->SetTarget(&(gUtilsNode->mTemplate.mSpawnRotationSpeedRandom));
        mRotationSliderSpeedAccel->SetTarget(&(gUtilsNode->mTemplate.mSpawnRotationSpeedAccel));
        mRotationButtonRandomNegativeSpeed->SetTargetCheck(&(pNode->mTemplate.mSpawnRotationSpeedNegativeRandom));
    }
    else
    {
        mRotationSlider->SetTarget(0);
        mRotationSliderRandom->SetTarget(0);
        mRotationSliderSpeed->SetTarget(0);
        mRotationSliderSpeedRandom->SetTarget(0);
        mRotationSliderSpeedAccel->SetTarget(0);
        mRotationButtonRandomNegative->SetTargetCheck(0);
        mRotationButtonRandomNegativeSpeed->SetTargetCheck(0);
    }
}

UParticleEditoScalePane::UParticleEditoScalePane()
{
    SetExpandable(true);
    SetText("Scale");
    
    mPaneMain = new UMenuPane("Start", true);
    AddLine(mPaneMain);
    
    mSliderScale = new UExtendedSlider("Scale", 0.1f, 1.25f);
    mPaneMain->AddLine(mSliderScale);
    
    mSliderScaleRandom = new UExtendedSlider("Rand", 0.0f, 0.20f);
    mPaneMain->AddLine(mSliderScaleRandom);
    
    
    mPaneSpeed = new UMenuPane("Cumulative", true);
    AddLine(mPaneSpeed);
    
    mSliderSpeed = new UExtendedSlider("Speed", -0.1f, 0.1f);
    mPaneSpeed->AddLine(mSliderSpeed);
    
    mSliderSpeedRandom = new UExtendedSlider("Rand", 0.0f, 0.1f);
    mPaneSpeed->AddLine(mSliderSpeedRandom);
    
    mSliderSpeedAdd = new UExtendedSlider("Add", -0.02, 0.02);
    mPaneSpeed->AddLine(mSliderSpeedAdd);
    
    
    mSliderSpeedAccel = new UExtendedSlider("Accel", 0.95f, 1.05f);
    mPaneSpeed->AddLine(mSliderSpeedAccel);
    
    
    
    /*
     mPaneXY = new UMenuPane("XY Scale", true);
     AddLine(mPaneXY);
     
     mSliderScaleX = new UExtendedSlider("ScX:", 0.9f, 1.2f);
     mPaneXY->AddLine(mSliderScaleX);
     
     mSliderScaleY = new UExtendedSlider("ScY:", 0.9f, 1.2f);
     mPaneXY->AddLine(mSliderScaleY);
     
     
     
     
     
     
     
     */
    
}

UParticleEditoScalePane::~UParticleEditoScalePane()
{
    
}

void UParticleEditoScalePane::Notify(void *pSender)
{
    /*
    if(pSender == mScaleButtonReset)
    {
        if(gUtilsNode)
        {
            gUtilsNode->mTemplate.ResetSpawnScaleAll();
        }
    }
    */
    
}

void UParticleEditoScalePane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mSliderScale->SetTarget(&(pNode->mTemplate.mSpawnScale));
        mSliderScaleRandom->SetTarget(&(pNode->mTemplate.mSpawnScaleRandom));
        
        mSliderSpeed->SetTarget(&(pNode->mTemplate.mSpawnScaleSpeed));
        mSliderSpeedAccel->SetTarget(&(pNode->mTemplate.mSpawnScaleSpeedAccel));
        
        mSliderSpeedAdd->SetTarget(&(pNode->mTemplate.mSpawnScaleSpeedAdd));
        
    }
    else
    {
        mSliderScale->SetTarget(0);
        mSliderScaleRandom->SetTarget(0);
        
        mSliderSpeed->SetTarget(0);
        mSliderSpeedAccel->SetTarget(0);
        
        mSliderSpeedAdd->SetTarget(0);
    }
}


UParticleEditorSpeedPane::UParticleEditorSpeedPane()
{
    SetExpandable(true);
    SetText("Speeds");
    
    mPaneBase = new UMenuPane("Start", true);
    AddLine(mPaneBase);
    
    mSpeedSliderX = new UExtendedSlider("X", -20.0f, 20.0f);
    mPaneBase->AddLine(mSpeedSliderX);
    
    mSpeedSliderXRandom = new UExtendedSlider("Rand", -8.0f, 8.0f);
    mPaneBase->AddLine(mSpeedSliderXRandom);
    
    mSpeedSliderY = new UExtendedSlider("Y", -20.0f, 20.0f);
    mPaneBase->AddLine(mSpeedSliderY);
    
    mSpeedSliderYRandom = new UExtendedSlider("Rand", -8.0f, 8.0f);
    mPaneBase->AddLine(mSpeedSliderYRandom);
    
    
    
    mPaneAccel = new UMenuPane("Cumulative", true);
    AddLine(mPaneAccel);
    
    mSpeedSliderAccel = new UExtendedSlider("Accel", 0.84f, 1.0f);
    mPaneAccel->AddLine(mSpeedSliderAccel);
    
    
    mSpeedSliderGravityX = new UExtendedSlider("G-X", -0.2, 0.2);
    mPaneAccel->AddLine(mSpeedSliderGravityX);
    
    mSpeedSliderGravityY = new UExtendedSlider("G-Y:", 0.0f, 0.3);
    mPaneAccel->AddLine(mSpeedSliderGravityY);
    
    
    mSpeedSliderGravityYAdd = new UExtendedSlider("Add", 0.0f, 0.2f);
    mPaneAccel->AddLine(mSpeedSliderGravityYAdd);
    
    mPaneAccel->Collapse();
}

UParticleEditorSpeedPane::~UParticleEditorSpeedPane()
{
    
}

void UParticleEditorSpeedPane::Notify(void *pSender)
{
    
}

void UParticleEditorSpeedPane::SetSelectedNode(UNode *pNode)
{
    
    if(pNode)
    {
        
        mSpeedSliderX->SetTarget(&(pNode->mTemplate.mSpawnSpeedX));
        mSpeedSliderY->SetTarget(&(pNode->mTemplate.mSpawnSpeedY));
        
        mSpeedSliderXRandom->SetTarget(&(pNode->mTemplate.mSpawnSpeedXRandom));
        mSpeedSliderYRandom->SetTarget(&(pNode->mTemplate.mSpawnSpeedYRandom));
        
        mSpeedSliderAccel->SetTarget(&(pNode->mTemplate.mSpawnSpeedAccel));
        
        mSpeedSliderGravityY->SetTarget(&(pNode->mTemplate.mSpawnSpeedGravityY));
        mSpeedSliderGravityX->SetTarget(&(pNode->mTemplate.mSpawnSpeedGravityX));
        mSpeedSliderGravityYAdd->SetTarget(&(pNode->mTemplate.mSpawnSpeedGravityYAdd));
    }
    else
    {
        mSpeedSliderX->SetTarget(0);
        mSpeedSliderY->SetTarget(0);
        
        mSpeedSliderXRandom->SetTarget(0);
        mSpeedSliderYRandom->SetTarget(0);
        
        mSpeedSliderAccel->SetTarget(0);
        
        mSpeedSliderGravityX->SetTarget(0);
        mSpeedSliderGravityY->SetTarget(0);
        
        mSpeedSliderGravityYAdd->SetTarget(0);
    }
}

UParticleEditorFramePane::UParticleEditorFramePane()
{
    SetExpandable(true);
    SetText("Frame Rate");
    
    
    mSliderFrameSpeed = new UExtendedSlider("Frame", 0.5f, 1.3f);
    AddLine(mSliderFrameSpeed);
    
    mSliderFrameSpeedRandom = new UExtendedSlider("Rand", 0.0f, 0.25f);
    AddLine(mSliderFrameSpeedRandom);
    
    mButtonStartRandom = new UButton("R-Start");
    mButtonStartRandom->StyleSetCheckBox();
    
    mButtonLoop = new UButton("Loop");
    mButtonLoop->StyleSetCheckBox();
    AddLine(mButtonStartRandom, mButtonLoop);
}

UParticleEditorFramePane::~UParticleEditorFramePane()
{
    
}

void UParticleEditorFramePane::Notify(void *pSender)
{
    
}

void UParticleEditorFramePane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mSliderFrameSpeed->SetTarget(&(pNode->mTemplate.mSpawnFrameSpeed));
        mSliderFrameSpeedRandom->SetTarget(&(pNode->mTemplate.mSpawnFrameSpeedRandom));
        
        mButtonStartRandom->SetTargetCheck(&(pNode->mTemplate.mSpawnFrameStartRandom));
        mButtonLoop->SetTargetCheck(&(pNode->mTemplate.mSpawnFrameLoop));
    }
    else
    {
        mSliderFrameSpeed->SetTarget(0);
        mSliderFrameSpeedRandom->SetTarget(0);
        
        mButtonStartRandom->SetTargetCheck(0);
        mButtonLoop->SetTargetCheck(0);
        
    }
}


UParticleEditorOffsetPane::UParticleEditorOffsetPane()
{
    
    SetText("Offsets");
    SetExpandable(true);
    
    mSliderOffsetX = new UExtendedSlider("X", -100.0f, 100.0f);
    AddLine(mSliderOffsetX);
    
    mSliderOffsetXRandom = new UExtendedSlider("Rand", -100.0f, 100.0f);
    AddLine(mSliderOffsetXRandom);
    
    mSliderOffsetY = new UExtendedSlider("Y", -100.0f, 100.0f);
    AddLine(mSliderOffsetY);
    
    
    
    mSliderOffsetYRandom = new UExtendedSlider("Rand", -100.0f, 100.0f);
    AddLine(mSliderOffsetYRandom);
    
    
    
    mButtonSpawnFromParentGeometry = new UButton("Par Geom");
    mButtonSpawnFromParentGeometry->StyleSetCheckBox();
    
    mButtonSpawnFromParentLocation = new UButton("Par Loc");
    mButtonSpawnFromParentLocation->StyleSetCheckBox();
    
    AddLine(mButtonSpawnFromParentGeometry, mButtonSpawnFromParentLocation);
}



UParticleEditorOffsetPane::~UParticleEditorOffsetPane()
{
    
}

void UParticleEditorOffsetPane::Notify(void *pSender)
{
    
}

void UParticleEditorOffsetPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mSliderOffsetX->SetTarget(&(pNode->mTemplate.mSpawnOffsetX));
        mSliderOffsetY->SetTarget(&(pNode->mTemplate.mSpawnOffsetY));
        mSliderOffsetXRandom->SetTarget(&(pNode->mTemplate.mSpawnOffsetXRandom));
        mSliderOffsetYRandom->SetTarget(&(pNode->mTemplate.mSpawnOffsetYRandom));
    }
    else
    {
        mSliderOffsetX->SetTarget(0);
        mSliderOffsetY->SetTarget(0);
        mSliderOffsetXRandom->SetTarget(0);
        mSliderOffsetYRandom->SetTarget(0);
    }
}


UParticleEditorDefaultsPane::UParticleEditorDefaultsPane()
{
    SetText("Defaults");
    SetExpandable(true);
    
    
    mQuickResetPane = new UMenuPane("Quick Reset", true);
    AddLine(mQuickResetPane);
    
    mQuickResetButtonAll = new UButton("Reset All");
    mQuickRandom1 = new UButton("Rand-Mono");
    mQuickRandom2 = new UButton("Rand-Blast");
    mQuickRandom3 = new UButton("Rand-Blizz");
    mQuickResetPane->AddLine(mQuickResetButtonAll, mQuickRandom1, mQuickRandom2, mQuickRandom3);
    
    
    mQuickResetButtonAllOffsets = new UButton("R[XY]");
    mQuickResetButtonAllSpeeds = new UButton("R[Spd]");
    mQuickResetButtonAllRotations = new UButton("R[Rot]");
    mQuickResetButtonAllScales = new UButton("R[Scale]");
    mQuickResetButtonAllColors = new UButton("R[Col]");
    
    mQuickResetPane->AddLine(mQuickResetButtonAllOffsets,
            mQuickResetButtonAllSpeeds,
            mQuickResetButtonAllRotations,
            mQuickResetButtonAllScales,
            mQuickResetButtonAllColors);
    
    
    
    
    //mResetPane->Collapse();
}

UParticleEditorDefaultsPane::~UParticleEditorDefaultsPane()
{
    
}

void UParticleEditorDefaultsPane::Notify(void *pSender)
{
    if(gUtilsNode)
    {
        if(pSender == mQuickRandom3)
        {
            gUtilsNode->mTemplate.QuickBlizzard();
        }
        if(pSender == mQuickRandom2)
        {
            gUtilsNode->mTemplate.QuickBlast();
        }
        if(pSender == mQuickRandom1)
        {
            gUtilsNode->mTemplate.QuickSingleton();
        }
    
    if(pSender == mQuickResetButtonAll)
    {
        if(gUtilsNode)gUtilsNode->mTemplate.ResetSpawnAll();
        gUtils->SetSelectedNode();
    }
    if(pSender == mQuickResetButtonAllOffsets)
    {
        if(gUtilsNode)gUtilsNode->mTemplate.ResetSpawnPosition();
        gUtils->SetSelectedNode();
    }
    
    if(pSender == mQuickResetButtonAllSpeeds)
    {
        if(gUtilsNode)gUtilsNode->mTemplate.ResetSpawnSpeedAll();
        gUtils->SetSelectedNode();
    }
    
    if(pSender == mQuickResetButtonAllRotations)
    {
        if(gUtilsNode)gUtilsNode->mTemplate.ResetSpawnScaleAll();
        gUtils->SetSelectedNode();
    }
    if(pSender == mQuickResetButtonAllScales)
    {
        if(gUtilsNode)gUtilsNode->mTemplate.ResetSpawnRotationAll();
        gUtils->SetSelectedNode();
    }
    if(pSender == mQuickResetButtonAllColors)
    {
        if(gUtilsNode)gUtilsNode->mTemplate.ResetSpawnColorAll();
        gUtils->SetSelectedNode();
    }
    
    
        gUtils->TimelineReset();
    }
    
}

void UParticleEditorDefaultsPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        //mSliderFrameSpeed->SetTarget(&(pNode->mTemplate.mSpawnFrameSpeed));
        //mSliderFrameSpeedRandom->SetTarget(&(pNode->mTemplate.mSpawnFrameSpeedRandom));
        
        //mButtonStartRandom->SetTargetCheck(&(pNode->mTemplate.mSpawnFrameStartRandom));
        //mButtonLoop->SetTargetCheck(&(pNode->mTemplate.mSpawnFrameLoop));
    }
    else
    {
        //mSliderFrameSpeed->SetTarget(0);
        //mSliderFrameSpeedRandom->SetTarget(0);
        
        //mButtonStartRandom->SetTargetCheck(0);
    }
    
    
}

UParticleEditorDirectionalSpeedPane::UParticleEditorDirectionalSpeedPane()
{
    SetText("Directional Speed");
    SetExpandable(true);
    
    mSliderDirMagnitude = new UExtendedSlider("Mag", -8.0f, 24.0f);
    AddLine(mSliderDirMagnitude);
    
    mSliderDirMagnitudeRandom = new UExtendedSlider("Rand", 0.0f, 20.0f);
    AddLine(mSliderDirMagnitudeRandom);
    
    mSliderDirAngle = new UExtendedSlider("Angle", 0.0f, 30.0f);
    AddLine(mSliderDirAngle);
    
    mSliderDirAngleRandom = new UExtendedSlider("Rand", -360.0f, 360.0f);
    AddLine(mSliderDirAngleRandom);
    
    mSliderDirPush = new UExtendedSlider("Push", 0.0f, 80.0f);
    AddLine(mSliderDirPush);
    
    mSliderDirPushRandom = new UExtendedSlider("Rand", 0.0f, 120.0f);
    AddLine(mSliderDirPushRandom);
}

UParticleEditorDirectionalSpeedPane::~UParticleEditorDirectionalSpeedPane()
{
    
}

void UParticleEditorDirectionalSpeedPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mSliderDirMagnitude->SetTarget(&(pNode->mTemplate.mSpawnDirectionalMagnitude));
        mSliderDirMagnitudeRandom->SetTarget(&(pNode->mTemplate.mSpawnDirectionalMagnitudeRandom));
        
        mSliderDirAngle->SetTarget(&(pNode->mTemplate.mSpawnDirectionalAngle));
        mSliderDirAngleRandom->SetTarget(&(pNode->mTemplate.mSpawnDirectionalAngleRandom));
        
        mSliderDirPush->SetTarget(&(pNode->mTemplate.mSpawnDirectionalPush));
        mSliderDirPushRandom->SetTarget(&(pNode->mTemplate.mSpawnDirectionalPushRandom));
    }
    else
    {
        mSliderDirMagnitude->SetTarget(0);
        mSliderDirMagnitudeRandom->SetTarget(0);
        
        mSliderDirAngle->SetTarget(0);
        mSliderDirAngleRandom->SetTarget(0);
        
        mSliderDirPush->SetTarget(0);
        mSliderDirPushRandom->SetTarget(0);
    }
}


void UParticleEditorDirectionalSpeedPane::Notify(void *pSender)
{
    
}

