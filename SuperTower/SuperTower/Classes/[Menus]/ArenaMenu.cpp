//
//  ArenaMenu.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/7/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "ArenaMenu.hpp"
#include "WorldContainer.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"

ArenaMenu::ArenaMenu() : ToolMenu() {
    mName = "ArenaMenu";

    SetTitle("Arena Stuff");
    SetScrollMode(true);




    mTestModeSegment = new UISegment(7);
    mTestModeSegment->SetTitles("None", "GRP-C", "GRP-S", "UNI-S", "A", "A");
    mTestModeSegment->SetTitle(6, "Spawn");
    mTestModeSegment->SetTarget(&gArena->mTestMode);
    gNotify.Register(this, mTestModeSegment, "segment");
    AddSection(mTestModeSegment);

    mMarkerDrawingPanel = new ToolMenuPanel();
    mMarkerDrawingPanel->SetTitle("Drawing Markers");
    AddSection(mMarkerDrawingPanel);

    mMarkerDrawingRow1 = new ToolMenuSectionRow();
    mMarkerDrawingPanel->AddSection(mMarkerDrawingRow1);

    mDrawAllNodesCheckBox = new UICheckBox();
    mDrawAllNodesCheckBox->SetText("All Nodes");
    mDrawAllNodesCheckBox->SetTarget(&gArena->mTestDrawAllNodes);
    mMarkerDrawingRow1->AddCheckBox(mDrawAllNodesCheckBox);

    mDrawOccupiedNodesCheckBox = new UICheckBox();
    mDrawOccupiedNodesCheckBox->SetText("Occ Nodes");
    mDrawOccupiedNodesCheckBox->SetTarget(&gArena->mTestDrawOccupiedNodes);
    mMarkerDrawingRow1->AddCheckBox(mDrawOccupiedNodesCheckBox);

    mMarkerDrawingRow2 = new ToolMenuSectionRow();
    mMarkerDrawingPanel->AddSection(mMarkerDrawingRow2);

    mDrawAllConnectionsCheckBox = new UICheckBox();
    mDrawAllConnectionsCheckBox->SetText("All Cons");
    mDrawAllConnectionsCheckBox->SetTarget(&gArena->mTestDrawAllConnections);
    mMarkerDrawingRow2->AddCheckBox(mDrawAllConnectionsCheckBox);

    mDrawRampConnectionsCheckBox = new UICheckBox();
    mDrawRampConnectionsCheckBox->SetText("Ramp Cons");
    mDrawRampConnectionsCheckBox->SetTarget(&gArena->mTestDrawRampConnections);
    mMarkerDrawingRow2->AddCheckBox(mDrawRampConnectionsCheckBox);




    mMarkerDrawingRow3 = new ToolMenuSectionRow();
    mMarkerDrawingPanel->AddSection(mMarkerDrawingRow3);

    mDrawSelectedGroupPathCheckBox = new UICheckBox();
    mDrawSelectedGroupPathCheckBox->SetText("S-G Path");
    mDrawSelectedGroupPathCheckBox->SetTarget(&gArena->mTestDrawSelectedGroupPath);
    mMarkerDrawingRow3->AddCheckBox(mDrawSelectedGroupPathCheckBox);

    mDrawOccupiedTilesCheckBox = new UICheckBox();
    mDrawOccupiedTilesCheckBox->SetText("Occ Tiles");
    mDrawOccupiedTilesCheckBox->SetTarget(&gArena->mTestDrawOccupiedTiles);
    mMarkerDrawingRow3->AddCheckBox(mDrawOccupiedTilesCheckBox);






    mUnitGroupDragCreationPanel = new ToolMenuPanel();
    mUnitGroupDragCreationPanel->SetTitle("Drag Group Creation");
    AddSection(mUnitGroupDragCreationPanel);

    mUnitGroupDragSpawnSpeedSlider = new UISlider();
    mUnitGroupDragSpawnSpeedSlider->SetValue(&gArena->mTestDragGroupSpawnSpeed);
    mUnitGroupDragCreationPanel->AddSection(mUnitGroupDragSpawnSpeedSlider);

    mUnitGroupDragSpawnTrailerCountSegment = new UISegment(5);
    mUnitGroupDragSpawnTrailerCountSegment->SetTitles("0", "1", "3", "5", "10");
    mUnitGroupDragSpawnTrailerCountSegment->SetTarget(&gArena->mTestDragGroupSpawnTrailerIndex);
    mUnitGroupDragCreationPanel->AddSection(mUnitGroupDragSpawnTrailerCountSegment);



    mUnitGroupSingleCreationPanel = new ToolMenuPanel();
    mUnitGroupSingleCreationPanel->SetTitle("Single Spawn Creation");
    AddSection(mUnitGroupSingleCreationPanel);

    mUnitGroupSingleSpawnSpeedSlider = new UISlider();
    mUnitGroupSingleSpawnSpeedSlider->SetValue(&gArena->mTestSingleGroupSpawnSpeed);
    mUnitGroupSingleCreationPanel->AddSection(mUnitGroupSingleSpawnSpeedSlider);

    DeactivateCloseButton();

    RefreshTestMode();
    
}

ArenaMenu::~ArenaMenu() {

}

void ArenaMenu::Layout() {
    ToolMenu::Layout();

}


void ArenaMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {

        if (pSender == mUnitGroupSelectionReverseButton) {
            //gArena->UpdateOneFrame();
            
        }
        
        if (pSender == mUnitGroupSelectionDeleteButton) {
            //gArena->UpdateOneFrame();
            
        }
        
        if (pSender == mUnitGroupSelectionRepath) {
            //gArena->UpdateOneFrame();
            
        }
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        if (aSegment == mTestModeSegment) {
            RefreshTestMode();
        }
    }
}

void ArenaMenu::RefreshTestMode() {

    if (gArena->mTestMode == TEST_MODE_NONE) {
        mMarkerDrawingPanel->Activate();
        mMarkerDrawingPanel->Expand();
    } else {
        mMarkerDrawingPanel->Deactivate();
    }

    if (gArena->mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
        mUnitGroupDragCreationPanel->Activate();
        mUnitGroupDragCreationPanel->Expand();
    } else {
        mUnitGroupDragCreationPanel->Deactivate();
    }

    if (gArena->mTestMode == TEST_MODE_UNIT_GROUP_SELECT) {

    }

    if (gArena->mTestMode == TEST_MODE_ITEM_CREATE) {

    }

    if (gArena->mTestMode == TEST_MODE_ITEM_SELECT) {

    }

    if (gArena->mTestMode == TEST_MODE_UNIT_SPAWN) {
        mUnitGroupSingleCreationPanel->Activate();
        mUnitGroupSingleCreationPanel->Expand();
    } else {
        mUnitGroupSingleCreationPanel->Deactivate();
    }
}





