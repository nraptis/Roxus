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
    mMainSegment->SetTitles("Tiles", "Paths");
    mMainSegment->SetTarget(&gEditor->mEditorMode);
    AddSection(mMainSegment);
    gNotify.Register(this, mMainSegment, "segment");

    mPanelMainControls = new ToolMenuPanel();
    mPanelMainControls->SetTitle("Main Controls");
    AddSection(mPanelMainControls);

    mRowMainMenu = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowMainMenu);

    mButtonSave = new UIButton();
    mButtonSave->SetText("Save");
    mRowMainMenu->AddButton(mButtonSave);
    gNotify.Register(this, mButtonSave, "button_click");

    mButtonExport = new UIButton();
    mButtonExport->SetText("Export");
    mRowMainMenu->AddButton(mButtonExport);
    gNotify.Register(this, mButtonExport, "button_click");







    mRowClear = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowClear);
    
    mButtonClearTunnels = new UIButton();
    mButtonClearTunnels->SetText("Clear Tunnels");
    mRowClear->AddButton(mButtonClearTunnels);
    gNotify.Register(this, mButtonClearTunnels, "button_click");

    mButtonClearTiles = new UIButton();
    mButtonClearTiles->SetText("Clear (Norm)");
    mRowClear->AddButton(mButtonClearTiles);
    gNotify.Register(this, mButtonClearTiles, "button_click");

    mButtonClearBridges = new UIButton();
    mButtonClearBridges->SetText("Clear Bridges");
    mRowClear->AddButton(mButtonClearBridges);
    gNotify.Register(this, mButtonClearBridges, "button_click");


    mRowFlood = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowFlood);

    mButtonFloodTunnels = new UIButton();
    mButtonFloodTunnels->SetText("Fill Tunnels");
    mRowFlood->AddButton(mButtonFloodTunnels);
    gNotify.Register(this, mButtonFloodTunnels, "button_click");

    mButtonFloodTiles = new UIButton();
    mButtonFloodTiles->SetText("Fill (Norm)");
    mRowFlood->AddButton(mButtonFloodTiles);
    gNotify.Register(this, mButtonFloodTiles, "button_click");

    mButtonFloodBridges = new UIButton();
    mButtonFloodBridges->SetText("Fill Bridges");
    mRowFlood->AddButton(mButtonFloodBridges);
    gNotify.Register(this, mButtonFloodBridges, "button_click");




    mRowGridSize = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowGridSize);

    mButtonWidthAdd = new UIButton();
    mButtonWidthAdd->SetText("W(+)P");
    mRowGridSize->AddButton(mButtonWidthAdd);
    gNotify.Register(this, mButtonWidthAdd, "button_click");

    mButtonWidthSubtract = new UIButton();
    mButtonWidthSubtract->SetText("W(-)M");
    mRowGridSize->AddButton(mButtonWidthSubtract);
    gNotify.Register(this, mButtonWidthSubtract, "button_click");

    mButtonHeightAdd = new UIButton();
    mButtonHeightAdd->SetText("H(+)P");
    mRowGridSize->AddButton(mButtonHeightAdd);
    gNotify.Register(this, mButtonHeightAdd, "button_click");

    mButtonHeightSubtract = new UIButton();
    mButtonHeightSubtract->SetText("H(-)M");
    mRowGridSize->AddButton(mButtonHeightSubtract);
    gNotify.Register(this, mButtonHeightSubtract, "button_click");

    mRowGridBuffer = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowGridBuffer);

    mButtonBufferAdd = new UIButton();
    mButtonBufferAdd->SetText("Buffer (+) A");
    mRowGridBuffer->AddButton(mButtonBufferAdd);
    gNotify.Register(this, mButtonBufferAdd, "button_click");

    mButtonBufferSubtract = new UIButton();
    mButtonBufferSubtract->SetText("Buffer (-) M");
    mRowGridBuffer->AddButton(mButtonBufferSubtract);
    gNotify.Register(this, mButtonBufferSubtract, "button_click");


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
    mSliderZoom->SetRange(0.125f, 16.0f);
    mPanelWorldTransform->AddSection(mSliderZoom);
    
    mSliderPanRotation = new UISlider();
    mSliderPanRotation->SetText("Rotation:");
    mSliderPanRotation->SetValue(&aGesture->mWorldRotation);
    mSliderPanRotation->SetRange(-45.0f, 45.0f);
    mPanelWorldTransform->AddSection(mSliderPanRotation);

    //TOO: Twiddle...
    //mPanelWorldTransform->Deactivate();




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
    gNotify.Register(this, mButtonAddPath, "button_click");
    mRowPathButtons->AddButton(mButtonAddPath);

    mButtonDeletePath = new UIButton();
    mButtonDeletePath->SetText("Delete Path");
    gNotify.Register(this, mButtonDeletePath, "button_click");
    mRowPathButtons->AddButton(mButtonDeletePath);










    mPanelTiles = new ToolMenuPanel();
    mPanelTiles->SetTitle("Tiles");
    AddSection(mPanelTiles);

    mSegmentTileDepth = new UISegment(3);
    mSegmentTileDepth->SetTitles("Tunnel", "Floor", "Bridge");
    mSegmentTileDepth->SetTarget(&gEditor->mTileDepth);
    mPanelTiles->AddSection(mSegmentTileDepth);



    mSliderTileGridOpacity = new UISlider();
    mSliderTileGridOpacity->SetText("Grid Lines:");
    mSliderTileGridOpacity->SetValue(&gEditor->mGridOpacity);
    mPanelTiles->AddSection(mSliderTileGridOpacity);

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





    mSliderTunnelOpacity = new UISlider();
    mSliderTunnelOpacity->SetText("Tunnels:");
    mSliderTunnelOpacity->SetValue(&gEditor->mTileOpacity[0]);
    mPanelTiles->AddSection(mSliderTunnelOpacity);

    mSliderTileOpacity = new UISlider();
    mSliderTileOpacity->SetText("Tiles:");
    mSliderTileOpacity->SetValue(&gEditor->mTileOpacity[1]);
    mPanelTiles->AddSection(mSliderTileOpacity);

    mSliderBridgeOpacity = new UISlider();
    mSliderBridgeOpacity->SetText("Bridges:");
    mSliderBridgeOpacity->SetValue(&gEditor->mTileOpacity[2]);
    mPanelTiles->AddSection(mSliderBridgeOpacity);
    

    RefreshActiveMenus();
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

        if (pSender == mButtonClearTunnels) { gEditor->Clear(0); }
        if (pSender == mButtonClearTiles) { gEditor->Clear(1); }
        if (pSender == mButtonClearBridges) { gEditor->Clear(2); }

        if (pSender == mButtonFloodTunnels) { gEditor->Flood(0); }
        if (pSender == mButtonFloodTiles) { gEditor->Flood(1); }
        if (pSender == mButtonFloodBridges) { gEditor->Flood(2); }
        
        if (pSender == mButtonAddPath) { gEditor->AddPath(); }

        if (pSender == mButtonDeletePath) { gEditor->DeleteCurrentPath(); }
        if (pSender == mButtonExport) { gEditor->ExportImage(); }
        if (pSender == mButtonSave) { gEditor->ExportMap(); }

    }

    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        if (aSegment == mMainSegment) {
            printf("Main Segment Index: %d\n", aSegment->mSelectedIndex);
            RefreshActiveMenus();
        }
    }

    if (FString(pNotification) == "checkbox") {

        printf("CHECKBOX TOGGLE!!\n");

        UICheckBox *aCheckBox = (UICheckBox *)pSender;
        if (aCheckBox == mCheckBoxTile) { gEditor->mTileType = TILE_TYPE_NORMAL; }
        if (aCheckBox == mCheckBoxTileObstacle) { gEditor->mTileType = TILE_TYPE_BLOCKED; }
        if (aCheckBox == mCheckBoxTileRampU) { gEditor->mTileType = TILE_TYPE_RAMP_U; }
        if (aCheckBox == mCheckBoxTileRampR) { gEditor->mTileType = TILE_TYPE_RAMP_R; }
        if (aCheckBox == mCheckBoxTileRampD) { gEditor->mTileType = TILE_TYPE_RAMP_D; }
        if (aCheckBox == mCheckBoxTileRampL) { gEditor->mTileType = TILE_TYPE_RAMP_L; }
    }

}

void EditorMainMenu::RefreshActiveMenus() {
    if (gEditor->mEditorMode == EDITOR_MODE_PATH) {
        mPanelTiles->Deactivate();
        mPanelPaths->Activate();
        mPanelPaths->Expand();
    }
    if (gEditor->mEditorMode == EDITOR_MODE_TILES) {
        mPanelPaths->Deactivate();
        mPanelTiles->Activate();
        mPanelTiles->Expand();
    }
}







