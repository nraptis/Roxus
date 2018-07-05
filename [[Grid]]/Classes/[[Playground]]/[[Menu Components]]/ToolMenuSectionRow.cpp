//
//  ToolMenuSectionRow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuSectionRow.hpp"
#include "GLApp.h"

ToolMenuSectionRow::ToolMenuSectionRow() {
    mName = "ToolMenuSectionRow";
    
    SetHeight(52.0f);
}

ToolMenuSectionRow::~ToolMenuSectionRow() {

}

void ToolMenuSectionRow::Layout() {
    ToolMenuSection::Layout();
}

void ToolMenuSectionRow::Update() {

}

void ToolMenuSectionRow::Draw() {
    mSectionBackgroundOutline.Draw();
    mSectionBackground.Draw();
}

void ToolMenuSectionRow::Notify(void *pSender, const char *pNotification) {

}
