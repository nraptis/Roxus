//
//  PolygonMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PolygonMenu.hpp"


//
//  PolygonMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PolygonMenu.hpp"
//
//  PolygonMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "PolygonMenu.hpp"
#include "GLApp.h"

PolygonMenu::PolygonMenu() {
    mName = "PolygonMenu";

    SetTitle("Polygon Editor");
    SetScrollMode(true);

    mPanel1 = new ToolMenuPanel();
    mPanel1->SetFrame(10, 20, 300, 70.0f);
    AddSection(mPanel1);

    mPanel2 = new ToolMenuPanel();
    mPanel2->SetFrame(-20, -100, 120, 110.0f);
    AddSection(mPanel2);

    mPanel3 = new ToolMenuPanel();
    mPanel3->SetFrame(-100, -120, 3000, 100);
    AddSection(mPanel3);

    mSection1 = new ToolMenuSection();
    mSection1->SetFrame(30.0f, 80.0f, 220.0f, 220.0f);
    AddSection(mSection1);

    mSection2 = new ToolMenuSection();
    mSection2->SetFrame(30.0f, 80.0f, 220.0f, 90.0f);
    AddSection(mSection2);

    mSection3 = new ToolMenuSection();
    mSection3->SetFrame(30.0f, 80.0f, 220.0f, 280.0f);
    AddSection(mSection3);




    

}

PolygonMenu::~PolygonMenu() {

}

void PolygonMenu::Layout() {
    ToolMenu::Layout();

}


void PolygonMenu::Notify(void *pSender, const char *pNotification) {

}







