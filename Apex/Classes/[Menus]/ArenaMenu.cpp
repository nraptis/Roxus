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
    
    
    
    mTestModeSegment = new UISegment(6);
    mTestModeSegment->SetTitles("None", "UG-Cr", "UG-Sel", "ITM-Cr", "ITM-Sel");
    mTestModeSegment->SetTarget(&gArena->mTestMode);
    AddSection(mTestModeSegment);

    
    
    mUnitGroupCreationPanel = new ToolMenuPanel();
    mUnitGroupCreationPanel->SetTitle("Unit Group Creation");
    AddSection(mUnitGroupCreationPanel);
    
    
    //mUnitGroupCreationPanel
    //mUnitGroupSelectionPanel
    
    //mItemCreationPanel;
    //mItemSelectionPanel;
    
    //UISegment                               *;
    //ToolMenuPanel                           *mUnitGroupCreationPanel;
    //UISlider                                *mUnitGroupSpawnSpeedSlider;
    
    
    /*
    //ToolMenuPanel                           *mItemCreationPanel;
    
    ToolMenuPanel                           *mUnitGroupSelectionPanel;
     UIButton                                *mUnitGroupSelectionReverseButton;
     UIButton                                *mUnitGroupSelectionDeleteButton;
     UIButton                                *mUnitGroupSelectionRepath;
    UICheckBox                              *mUnitGroupSelectionShowAllPathsCheckBox;
    UICheckBox                              *mUnitGroupSelectionShowPathCheckBox;
    UICheckBox                              *mUnitGroupSelectionShowMarkersCheckBox;
    UICheckBox                              *mUnitGroupSelectionFreezeCheckBox;
    
    
    ToolMenuPanel                           *mItemSelectionPanel;
    UIButton                                *mItemSelectionDeleteButton;
    */
    
    

    DeactivateCloseButton();
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
    
    //if (FString(pNotification) == "segment") {
    //    UISegment *aSegment = (UISegment *)pSender;
    //}
}







