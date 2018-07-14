//
//  EditorMainMenu.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/13/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "EditorMainMenu.hpp"
#include "WorldContainer.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.h"
#include "EditorGameArena.hpp"

EditorMainMenu::EditorMainMenu() : ToolMenu() {
    mName = "EditorMainMenu";



    mPanelWorldTransform = 0;

    SetTitle("Map Editor");
    SetScrollMode(true);

    
    WorldGestureContainer *aGesture = gWorldContainer->mGestureContainer;



    mMainSegment = new UISegment();
    mMainSegment->SetSegmentCount(2);
    mMainSegment->SetTitles("Paths", "Tiles");
    mMainSegment->SetTarget(&gEditor->mEditorMode);
    AddSection(mMainSegment);
    gNotify.Register(this, mMainSegment, "segment");



    mPanelWorldTransform = new ToolMenuPanel();
    mPanelWorldTransform->SetTitle("World Transform");
    AddSection(mPanelWorldTransform);


    mRowTransformButtons = new ToolMenuSectionRow();
    mPanelWorldTransform->AddSection(mRowTransformButtons);

    mButtonResetTransform = new UIButton();
    mButtonResetTransform->SetText("Reset Transform");
    mRowTransformButtons->AddButton(mButtonResetTransform);
    gNotify.Register(this, mButtonResetTransform, "button_click");

    mSliderZoom = new UISlider();
    mSliderZoom->SetText("Zoom:");
    mSliderZoom->SetValue(&aGesture->mWorldScale);
    mSliderZoom->SetRange(0.125f, 2.25f);
    mPanelWorldTransform->AddSection(mSliderZoom);
    
    mSliderPanRotation = new UISlider();
    mSliderPanRotation->SetText("Rotation:");
    mSliderPanRotation->SetValue(&aGesture->mWorldRotation);
    mSliderPanRotation->SetRange(-180.0f, 180.0f);
    mPanelWorldTransform->AddSection(mSliderPanRotation);

    mSliderPanRotation = new UISlider();
    mSliderPanRotation->SetText("Rotation:");
    mSliderPanRotation->SetValue(&aGesture->mWorldRotation);
    mSliderPanRotation->SetRange(-180.0f, 180.0f);
    mPanelWorldTransform->AddSection(mSliderPanRotation);
    mPanelWorldTransform->Collapse();




    mPanelPaths = new ToolMenuPanel();
    mPanelPaths->SetTitle("Spawn Paths");
    AddSection(mPanelPaths);



    mRowPathMode = new ToolMenuSectionRow();
    mPanelPaths->AddSection(mRowPathMode);


    mCheckBoxPathStart = new UICheckBox();
    mCheckBoxPathStart->SetText("Path Start");
    mCheckBoxPathStart->SetTarget(&gEditor->mPathStartMode);
    mRowPathMode->AddCheckBox(mCheckBoxPathStart);

    
    mCheckBoxPathSelect = new UICheckBox();
    mCheckBoxPathSelect->SetText("Path Select");
    mCheckBoxPathSelect->SetTarget(&gEditor->mPathSelectMode);
    mRowPathMode->AddCheckBox(mCheckBoxPathSelect);



    mRowPathButtons = new ToolMenuSectionRow();
    mPanelPaths->AddSection(mRowPathButtons);

    mButtonAddPath = new UIButton();
    mButtonAddPath->SetText("Add Path");
    mRowPathButtons->AddButton(mButtonAddPath);

    mButtonDeletePath = new UIButton();
    mButtonDeletePath->SetText("Delete Path");
    mRowPathButtons->AddButton(mButtonDeletePath);

    mPanelPaths->Collapse();









    mPanelTiles = new ToolMenuPanel();
    mPanelTiles->SetTitle("Tiles");
    AddSection(mPanelTiles);

    mSegmentTileDepth = new UISegment(3);
    mSegmentTileDepth->SetTitles("Tunnel", "Floor", "Bridge");
    mSegmentTileDepth->SetTarget(&gEditor->mTileDepth);
    mPanelTiles->AddSection(mSegmentTileDepth);

    mRowBasicTiles = new ToolMenuSectionRow();
    mPanelTiles->AddSection(mRowBasicTiles);

    mButtonAddPath = new UIButton();
    mButtonAddPath->SetText("Add Path");
    mRowBasicTiles->AddButton(mButtonAddPath);

    mButtonDeletePath = new UIButton();
    mButtonDeletePath->SetText("Delete Path");
    mRowBasicTiles->AddButton(mButtonDeletePath);

    mRowBasicTiles = new ToolMenuSectionRow();
    mPanelTiles->AddSection(mRowBasicTiles);

    mCheckBoxTile = new UICheckBox();
    mCheckBoxTile->SetText("Tile");
    gNotify.Register(this, mCheckBoxTile, "checkbox");
    mRowBasicTiles->AddCheckBox(mCheckBoxTile);

    mCheckBoxTileObstacle = new UICheckBox();
    mCheckBoxTileObstacle->SetText("Rock");
    gNotify.Register(this, mCheckBoxTileObstacle, "checkbox");
    mRowBasicTiles->AddCheckBox(mCheckBoxTileObstacle);

    mRowRampTiles = new ToolMenuSectionRow();
    mPanelTiles->AddSection(mRowRampTiles);

    mCheckBoxTileRampL = new UICheckBox();
    mCheckBoxTileRampL->SetText("R-L");
    gNotify.Register(this, mCheckBoxTileRampL, "checkbox");
    mRowRampTiles->AddCheckBox(mCheckBoxTileRampL);

    mCheckBoxTileRampR = new UICheckBox();
    mCheckBoxTileRampR->SetText("R-R");
    gNotify.Register(this, mCheckBoxTileRampR, "checkbox");
    mRowRampTiles->AddCheckBox(mCheckBoxTileRampR);

    mCheckBoxTileRampU = new UICheckBox();
    mCheckBoxTileRampU->SetText("R-U");
    gNotify.Register(this, mCheckBoxTileRampU, "checkbox");
    mRowRampTiles->AddCheckBox(mCheckBoxTileRampU);

    mCheckBoxTileRampD = new UICheckBox();
    mCheckBoxTileRampD->SetText("R-D");
    gNotify.Register(this, mCheckBoxTileRampD, "checkbox");
    mRowRampTiles->AddCheckBox(mCheckBoxTileRampD);




}

EditorMainMenu::~EditorMainMenu() {

}

void EditorMainMenu::Layout() {
    ToolMenu::Layout();

}

void EditorMainMenu::Update() {

    mCheckBoxTile->SetChecked(gEditor->mTileType == TILE_TYPE_NORMAL);

    mCheckBoxTileObstacle->SetChecked(gEditor->mTileType == TILE_TYPE_BLOCKED);

    mCheckBoxTileRampU->SetChecked(gEditor->mTileType == TILE_TYPE_RAMP_U);
    mCheckBoxTileRampR->SetChecked(gEditor->mTileType == TILE_TYPE_RAMP_R);
    mCheckBoxTileRampD->SetChecked(gEditor->mTileType == TILE_TYPE_RAMP_D);
    mCheckBoxTileRampL->SetChecked(gEditor->mTileType == TILE_TYPE_RAMP_L);
    
}

void EditorMainMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "pick_image") {
        UIImagePicker *aImagePicker = (UIImagePicker *)pSender;

    }

    if (FString(pNotification) == "button_click") {
        if (pSender == mButtonResetTransform) {
            gWorldContainer->BaseLayout();
            gWorldContainer->mGestureContainer->BaseLayout();
        }
    }

    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        if (aSegment == mMainSegment) {
            printf("Main Segment Index: %d\n", aSegment->mSelectedIndex);
        }
    }

    if (FString(pNotification) == "checkbox") {

        printf("CHECKBOX TOGGLE!!\n");

        UICheckBox *aCheckBox = (UICheckBox *)pSender;

        if (aCheckBox == mCheckBoxTile        ) { gEditor->mTileType = TILE_TYPE_NORMAL; }
        if (aCheckBox == mCheckBoxTileObstacle) { gEditor->mTileType = TILE_TYPE_BLOCKED; }

        if (aCheckBox == mCheckBoxTileRampU)    { gEditor->mTileType = TILE_TYPE_RAMP_U; }
        if (aCheckBox == mCheckBoxTileRampR)    { gEditor->mTileType = TILE_TYPE_RAMP_R; }
        if (aCheckBox == mCheckBoxTileRampD)    { gEditor->mTileType = TILE_TYPE_RAMP_D; }
        if (aCheckBox == mCheckBoxTileRampL)    { gEditor->mTileType = TILE_TYPE_RAMP_L; }
    }

}












