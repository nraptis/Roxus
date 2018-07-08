//
//  UTransformMenu.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UTransformMenu.h"
#include "UMainCanvas.h"

UTransformMenu::UTransformMenu()
{
	SetWidth(500.0f);
    SetText("Transforms");


	mControlPane = new UMenuPane("Main Controls", true);
	AddLine(mControlPane);

	mCreatePane = new UMenuPane("Creation", true);
	AddLine(mCreatePane);


	mInfoLabelTitleX = new ULabel("X: ");
	mInfoLabelX = new ULabel("001122");

	mInfoLabelTitleY = new ULabel("Y: ");
	mInfoLabelY = new ULabel("134435");

	AddLine(mInfoLabelTitleX, mInfoLabelX, mInfoLabelTitleY, mInfoLabelY);

}

UTransformMenu::~UTransformMenu()
{
    
}


void UTransformMenu::Notify(void *pSender)
{
    
}

void UTransformMenu::SetSelectedNode(UNode *pNode)
{

}






