//
//  UCanvasPane.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UCanvasPane.h"
#include "UMainCanvas.h"

UCanvasPane::UCanvasPane()
{
    SetText("Canvas Pane!");


	mControlPane = new UMenuPane("Main Controls", true);
	AddLine(mControlPane);


	mControlButtonClear = new UButton("Clear");
	
	mControlButtonSave = new UButton("Save");
	mControlButtonSave->StyleSetGreen();
	mControlButtonLoad = new UButton("Load");
    
    mControlButtonDeleteSaved = new UButton("[NUKE]");
    

    mControlPane->AddLine(mControlButtonSave, mControlButtonLoad, mControlButtonClear, mControlButtonDeleteSaved);

    
    mControlButtonExport = new UButton("E[All]");
    mControlButtonExportOffsets = new UButton("Ex[Rel]");
    mControlButtonExportParticle = new UButton("Ex[Par]");
    mControlButtonExportPaths = new UButton("Ex[Pth]");
    
    mControlButtonExport->StyleSetDark();
    mControlButtonExportOffsets->StyleSetDark();
    mControlButtonExportParticle->StyleSetDark();
    mControlButtonExportPaths->StyleSetDark();
    
    
    
    
    
    mControlPane->AddLine(mControlButtonExport, mControlButtonExportOffsets, mControlButtonExportParticle, mControlButtonExportPaths);

   

    

	mCreatePane = new UMenuPane("Creation", true);
	AddLine(mCreatePane);

	mCreateButtonSprite = new UButton("[+]SPR");
	mCreateButtonSprite->StyleSetBlue();
	mCreateButtonSpriteSequence = new UButton("[+]SEQ");
	mCreateButtonSpriteSequence->StyleSetGreen();
	mCreateButtonParticle = new UButton("[+]PRT");
	mCreateButtonParticle->StyleSetBlue();
	mCreateButtonRect = new UButton("[+]BOX");
	mCreateButtonRect->StyleSetBlue();
	mCreatePane->AddLine(mCreateButtonSprite, mCreateButtonSpriteSequence, mCreateButtonParticle, mCreateButtonRect);
    
    mBackgroundPane = new UCanvasPaneBackground();
    AddLine(mBackgroundPane);
    mBackgroundPane->Collapse();
    
    
    
    mPathPane = new UMenuPane("Paths", true);
    AddLine(mPathPane);
    
    mPathSliderStartScale = new UExtendedSlider("Scale:", 0.2f, 2.0f);
    mPathPane->AddLine(mPathSliderStartScale);
    
    mPathButtonTransform = new UButton("Transform");
    mPathButtonTransform->StyleSetCheckBox();
    mPathPane->AddLine(mPathButtonTransform);
    
    
    
}

UCanvasPane::~UCanvasPane()
{
    
}


void UCanvasPane::Notify(void *pSender)
{
	if(pSender == mControlButtonClear)gUtilWS->Clear();
	if(pSender == mControlButtonExport)gUtils->Export();
	if(pSender == mControlButtonSave)gUtils->Save();
	if(pSender == mControlButtonLoad)gUtils->Load();
    
    //if(pSender == mControlButtonExportOffsets)gUtilWS->ExportOffsets();
    if(pSender == mControlButtonExportOffsets)gUtilWS->ExportRelChildren(0, 0, false);
    
    //
    
    if(pSender == mControlButtonExportParticle)gUtilWS->ExportParticleBasic();
    if(pSender == mControlButtonExportPaths)gUtilWS->ExportPaths();
    
    if(pSender == mControlButtonDeleteSaved)gUtils->DeleteSaved();
    
    
	if(pSender == mCreateButtonSprite)gUtilWS->CreateNodeSprite();
	if(pSender == mCreateButtonSpriteSequence)gUtilWS->CreateNodeSpriteSequence();
	if(pSender == mCreateButtonParticle)gUtilWS->CreateNodeParticles();
	if(pSender == mCreateButtonRect)gUtilWS->CreateNodeRectangle();
}

void UCanvasPane::SetSelectedNode(UNode *pNode)
{

}


UCanvasPaneBackground::UCanvasPaneBackground()
{
    SetText("Background");
    SetExpandable(true);
    
    
    
    mButtonLetterBoxEnable = new UButton("Letterbox");
    mButtonLetterBoxEnable->StyleSetCheckBox();
    
    mButtonLetterBoxFront = new UButton("LB Over");
    mButtonLetterBoxFront->StyleSetCheckBox();
    
    AddLine(mButtonLetterBoxEnable, mButtonLetterBoxFront);
    

    mColorPickerBackground = new UColorPicker();
    mColorPickerBackground->SetText("Background Color");
    mColorPickerBackground->Expand();
    AddLine(mColorPickerBackground);
    
    
    
    mButtonPickImage = new UButton("Pick Image");
    mButtonEnableColor = new UButton("Show CLR");
    mButtonEnableColor->StyleSetCheckBox();
    
    mButtonEnableImage = new UButton("Show IMG");
    mButtonEnableImage->StyleSetCheckBox();
    
    AddLine(mButtonPickImage, mButtonEnableColor, mButtonEnableImage);
    
    mSliderGlobalOpacity = new UExtendedSlider("World Alpha", 0.0f, 1.0f);
    AddLine(mSliderGlobalOpacity);
    
    mSliderBackOpacity = new UExtendedSlider("Back Alp", 0.0f, 0.6f);
    AddLine(mSliderBackOpacity);
}

UCanvasPaneBackground::~UCanvasPaneBackground()
{
    
}

void UCanvasPaneBackground::Notify(void *pSender)
{
    if(pSender == mButtonPickImage)
    {
        gUtils->BackgroundSpritePick();
    }
}

void UCanvasPaneBackground::SetSelectedNode(UNode *pNode)
{
    mColorPickerBackground->SetColor(&(gUtils->mBackgroundColor));
    
    mSliderGlobalOpacity->SetTarget(&(gUtils->mGlobalOpacity));
    mSliderBackOpacity->SetTarget(&(gUtils->mBackgroundOpacity));
    
    mButtonEnableColor->SetTargetCheck(&(gUtils->mBackgroundColorEnabled));
    mButtonEnableImage->SetTargetCheck(&(gUtils->mBackgroundImageEnabled));
    
    
    mButtonLetterBoxEnable->SetTargetCheck(&(gUtils->mBackgroundLetterBox));
    mButtonLetterBoxFront->SetTargetCheck(&(gUtils->mBackgroundLetterBoxOver));
}



