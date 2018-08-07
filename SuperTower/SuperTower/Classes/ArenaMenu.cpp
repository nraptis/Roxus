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
    
    mFrameRow = new ToolMenuSectionRow();
    AddSection(mFrameRow);

    mPlayCheckBox = new UICheckBox();
    mPlayCheckBox->SetText("Updates Enabled");
    mPlayCheckBox->SetTarget(&gArena->mUpdateEnabled);



    mFrameRow->AddCheckBox(mPlayCheckBox);

    mOneFrameButton = new UIButton();
    mOneFrameButton->SetText(">");
    mFrameRow->AddButton(mOneFrameButton);

    mSpeedSegment = new UISegment(5);
    mSpeedSegment->SetTarget(&gArena->mUpdateSpeedIndex);
    mSpeedSegment->SetTitles("XSlo", "Slo", "Norm", "Fas", "XFas");
    AddSection(mSpeedSegment);

    DeactivateCloseButton();
}

ArenaMenu::~ArenaMenu() {

}

void ArenaMenu::Layout() {
    ToolMenu::Layout();

}


void ArenaMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {

        if (pSender == mOneFrameButton) {
            gArena->UpdateOneFrame();
        }

    }

    //

    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;

    }
}







