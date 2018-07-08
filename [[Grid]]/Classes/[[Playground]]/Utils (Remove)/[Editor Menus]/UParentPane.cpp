//
//  UParentPane.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UMainCanvas.h"
#include "UParentPane.h"

UParentPane::UParentPane()
{
    
    SetText("Parent");
    SetExpandable(true);
    
    
    mRelationPane = new UMenuPane("Tracking Type", true);
    AddLine(mRelationPane);
    
    
    
    mRelationTypeSegment = new USegment(4);
    mRelationTypeSegment->SetTitles("Posi", "Screen", "View", "Object");
    mRelationPane->AddLine(mRelationTypeSegment);
    
    
    mRelationTypeSegmentX = new USegment(3);
    mRelationTypeSegmentX->SetTitles("Left", "Center", "Right");
    mRelationPane->AddLine(new ULabel("X-Trk"), mRelationTypeSegmentX);
    
    mRelationTypeSegmentY = new USegment(3);
    mRelationTypeSegmentY->SetTitles("Top", "Center", "Bottom");
    mRelationPane->AddLine(new ULabel("X-Trk"), mRelationTypeSegmentY);
    
    
    mButtonAdjustWorld = new UButton("Adjust");
    mButtonAdjustWorld->StyleSetCheckBox();
    
    mButtonMatchTransform = new UButton("MatchTra");
    mButtonMatchTransform->StyleSetCheckBox();
    
    mButtonResetOffset = new UButton("ResetOffset");
    
    mRelationPane->AddLine(mButtonAdjustWorld, mButtonMatchTransform, mButtonResetOffset);
    
    
    mOffsetSliderX = new UExtendedSlider("X-Off:", -600.0f, 600.0f);
    mRelationPane->AddLine(mOffsetSliderX);
    
    mOffsetSliderY = new UExtendedSlider("Y-Off:", -600.0f, 600.0f);
    mRelationPane->AddLine(mOffsetSliderY);
    
    
}


UParentPane::~UParentPane()
{
    
}


void UParentPane::Notify(void *pSender)
{
    if(pSender == mButtonResetOffset)
    {
        if(gUtilsNode)
        {
            gUtilsNode->mTrackingOffsetX = 0.0f;
            gUtilsNode->mTrackingOffsetY = 0.0f;
            
            
        }
    }
    
    
    gUtils->SetSelectedNode(gUtilsNode);
}

void UParentPane::SetSelectedNode(UNode *pNode)
{
    
    if(pNode)
    {
        
        mRelationTypeSegment->SetTarget(&(pNode->mTrackingType));
        
        mRelationTypeSegmentX->SetTarget(&(pNode->mTrackingSideX));
        mRelationTypeSegmentY->SetTarget(&(pNode->mTrackingSideY));
        
        mOffsetSliderX->SetTarget(&(pNode->mTrackingOffsetX));
        mOffsetSliderY->SetTarget(&(pNode->mTrackingOffsetY));
        
        
        mButtonAdjustWorld->SetTargetCheck(&(pNode->mTrackingAdjustWorldPosition));
        mButtonMatchTransform->SetTargetCheck(&(pNode->mTrackingMatchTransform));
        
        
    }
    else
    {
        
        mRelationTypeSegment->SetTarget(0);
        
        mRelationTypeSegmentX->SetTarget(0);
        mRelationTypeSegmentY->SetTarget(0);
        
        mOffsetSliderX->SetTarget(0);
        mOffsetSliderY->SetTarget(0);
        
        mButtonAdjustWorld->SetTargetCheck(0);
        mButtonMatchTransform->SetTargetCheck(0);
    }
}






