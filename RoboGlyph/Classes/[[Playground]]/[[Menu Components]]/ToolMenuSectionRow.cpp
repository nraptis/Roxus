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
    mConsumesTouches = false;
    mName = "row";
    SetHeight(ToolMenuSectionRow::RowHeight());
}

ToolMenuSectionRow::~ToolMenuSectionRow() {

}

float ToolMenuSectionRow::RowHeight() {
    return 52.0f;
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
