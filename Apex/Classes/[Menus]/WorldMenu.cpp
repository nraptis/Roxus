//
//  WorldMenu.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "WorldMenu.hpp"
#include "WorldContainer.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"

WorldMenu::WorldMenu(WorldContainer *pWorld) : ToolMenu() {
    mName = "WorldMenu";

    mWorld = pWorld;

    SetTitle("World Editor");
    SetScrollMode(true);
    
    WorldGestureContainer *aGesture = mWorld->mGestureContainer;

    mSliderZoom = new UISlider();
    mSliderZoom->SetText("Zoom:");
    mSliderZoom->SetValue(&aGesture->mWorldScale);
    mSliderZoom->SetRange(0.125f, 20.0f);
    AddSection(mSliderZoom);
    
    mSliderPanRotation = new UISlider();
    mSliderPanRotation->SetText("Rotation:");
    mSliderPanRotation->SetValue(&aGesture->mWorldRotation);
    mSliderPanRotation->SetRange(-180.0f, 180.0f);
    AddSection(mSliderPanRotation);

    mSliderTestRotation = new UISlider();
    mSliderTestRotation->SetText("Rotation:");
    //mSliderTestRotation->SetValue(&gArena->mTestNinjaRotation);

    mSliderTestRotation->SetRange(0.0f, 360.0f);
    AddSection(mSliderTestRotation);

    DeactivateCloseButton();
}

WorldMenu::~WorldMenu() {

}

void WorldMenu::Layout() {
    ToolMenu::Layout();

}


void WorldMenu::Notify(void *pSender, const char *pNotification) {

    if (FString(pNotification) == "pick_image") {
        UIImagePicker *aImagePicker = (UIImagePicker *)pSender;
        
    }

    if (FString(pNotification) == "button_click") {

    }

    //

    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;

    }
}







