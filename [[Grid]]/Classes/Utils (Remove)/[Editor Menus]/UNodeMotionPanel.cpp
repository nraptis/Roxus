//
//  UNodeMotionPanel.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UNodeMotionPanel.h"


//
//  UNodeMotionPanel.cpp
//  Digplex
//
//  Created by Nicholas Raptis on 1/10/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "UMainCanvas.h"
#include "UNodeMotionPanel.h"

UNodeMotionPanel::UNodeMotionPanel()
{
    
    SetText("Chrysler Dawgs");
    
    
    mQuadPane = new UMenuPane("Quads", true);
    AddMenuItems(mQuadPane);
    
    
    mQuadButtonPrint = new UButton("PRINT THAT QUAD");
    mQuadPane->AddLine(mQuadButtonPrint);
    
    
    mQuadSliderShiftLeftX = new UExtendedSlider("Skew-LX", -0.4f, 0.4f);
    mQuadPane->AddLine(mQuadButtonPrint);
    
    mQuadSliderShiftLeftY = new UExtendedSlider("Skew-LY", -0.4f, 0.4f);
    mQuadPane->AddLine(mQuadButtonPrint);
    
    mQuadSliderShiftRightX = new UExtendedSlider("Skew-RX", -0.4f, 0.4f);
    mQuadPane->AddLine(mQuadSliderShiftRightX);
    
    mQuadSliderShiftRightY = new UExtendedSlider("Skew-RY", -0.4f, 0.4f);
    mQuadPane->AddLine(mQuadSliderShiftRightY);
    
    
    /*
     mQuadSliderShiftLeftX;
     mQuadSliderShiftLeftY;
     
     mQuadSliderShiftRightX;
     mQuadSliderShiftRightY;
     
     mTestQuad1LeftSkewX;
     mTestQuad1LeftSkewY;
     
     mTestQuad1RightSkewX;
     mTestQuad1RightSkewY;
     */
    
    mQuadSliderRotation1 = new UExtendedSlider("Rot-1", -180.0f, 180.0f);
    mQuadPane->AddLine(mQuadSliderRotation1);
    
    mQuadSliderRotation2 = new UExtendedSlider("Rot-2", -0.2f, 0.2f);
    mQuadPane->AddLine(mQuadSliderRotation2);
    
    
    
    //mQuadSliderRotation1;
    //mQuadSliderRotation2;
}


UNodeMotionPanel::~UNodeMotionPanel()
{
    
}


void UNodeMotionPanel::Notify(void *pSender)
{
    
    /*
     if(pSender == mTransformPositionButtonShiftL)gUtils->SelectionShift(-1.0f, 0.0f);
     if(pSender == mTransformPositionButtonShiftR)gUtils->SelectionShift(1.0f, 0.0f);
     if(pSender == mTransformPositionButtonShiftU)gUtils->SelectionShift(0.0f, -1.0f);
     if(pSender == mTransformPositionButtonShiftD)gUtils->SelectionShift(0.0f, 1.0f);
     
     if(pSender == mTransformPositionSegmentParent)
     {
     if(gUtilsNode)
     {
     gUtilsNode->ParentRefresh();
     
     }
     
     
     //gUtils->RefreshSubs(gUtilsNode, true);
     }
     */
    
}

void UNodeMotionPanel::SetSelectedNode(UNode *pNode)
{
    
    
    
    //mQuadSliderShiftLeftX = new UExtendedSlider("Skew-LX", -0.4f, 0.4f);
    //mQuadSliderShiftLeftY = new UExtendedSlider("Skew-LY", -0.4f, 0.4f);
    //mQuadSliderShiftRightX = new UExtendedSlider("Skew-LX", -0.4f, 0.4f);
    //mQuadSliderShiftRightY = new UExtendedSlider("Skew-LY", -0.4f, 0.4f);
    
    
    
    
    
    
    
    
    
    
    /*
     if(pNode)
     {
     mTransformPositionSegmentParent->SetTarget(&(pNode->mParentMode));
     
     mLookTransformColorPicker->SetColor(&(pNode->mTemplate.mSpawnColor));
     mLookTransformSliderRotation->SetTarget(&(pNode->mObject->mRotation));
     mLookTransformSliderScale->SetTarget(&(pNode->mObject->mScale));
     mLookTransformSliderScaleX->SetTarget(&(pNode->mObject->mScaleX));
     mLookTransformSliderScaleY->SetTarget(&(pNode->mObject->mScaleY));
     mLookTransformSegmentBlend->SetTarget(&(pNode->mTemplate.mSpawnBlendType));
     }
     else
     {
     mTransformPositionSegmentParent->SetTarget(0);
     
     mLookTransformColorPicker->SetColor(0);
     mLookTransformSliderRotation->SetTarget(0);
     mLookTransformSliderScale->SetTarget(0);
     mLookTransformSliderScaleX->SetTarget(0);
     mLookTransformSliderScaleY->SetTarget(0);
     mLookTransformSegmentBlend->SetTarget(0);
     }
     
     
     mQuadSliderShiftX1 = new UExtendedSlider("ShiftxX", 0.0f, 50.0f);
     mQuadPane->AddLine(mQuadSliderShiftX1);
     
     mQuadSliderShiftY1 = new UExtendedSlider("Shift-Y", 0.0f, 50.0f);
     mQuadPane->AddLine(mQuadSliderShiftY1);
     
     mQuadSliderRotation1 = new UExtendedSlider("Rotation", -180.0f, 180.0f);
     mQuadPane->AddLine(mQuadSliderRotation1);
     */
    
}






