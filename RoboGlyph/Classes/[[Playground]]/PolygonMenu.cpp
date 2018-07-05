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
    mPanel1->SetTitle("Point Editor");
    mPanel1->SetFrame(10, 20, 300, 70.0f);
    AddSection(mPanel1);

    UISlider *aSlider = new UISlider();
    mPanel1->AddSection(aSlider);

    UISegment *aSegment = new UISegment(5);
    mPanel1->AddSection(aSegment);


    mPanel2 = new ToolMenuPanel();
    mPanel2->SetTitle("Tangent Editor");
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





    mSubPanel1 = new ToolMenuPanel();
    mSubPanel1->SetTitle("+[]ASDF.,|");
    mSubPanel1->SetFrame(10, 20, 300, 70.0f);
    mPanel1->AddSection(mSubPanel1);

    ToolMenuPanel *mSubSub1 = new ToolMenuPanel();
    mSubSub1->SetTitle("+[]ASDF.,|");
    mSubSub1->SetFrame(10, 20, 300, 70.0f);
    mSubPanel1->AddSection(mSubSub1);


    ToolMenuPanel *mSubSub2 = new ToolMenuPanel();
    mSubSub2->SetTitle("+[]ASDF.,|");
    mSubSub2->SetFrame(10, 20, 300, 70.0f);
    mSubPanel1->AddSection(mSubSub2);

    ToolMenuPanel *mSubSubSub1 = new ToolMenuPanel();
    mSubSubSub1->SetTitle("+[]ASDF.,|");
    mSubSubSub1->SetFrame(10, 20, 300, 70.0f);
    mSubSub2->AddSection(mSubSubSub1);


    mSubPanel2 = new ToolMenuPanel();
    mSubPanel2->SetTitle("Amazing??");
    mSubPanel2->SetFrame(10, 20, 300, 70.0f);
    mPanel1->AddSection(mSubPanel2);



    mSubPanel1 = new ToolMenuPanel();
    mSubPanel1->SetTitle("Amazing journey through junkyard");
    mSubPanel1->SetFrame(10, 20, 300, 70.0f);
    mPanel2->AddSection(mSubPanel1);

    mSubPanel2 = new ToolMenuPanel();
    mSubPanel2->SetTitle("Amazing journey");
    mSubPanel2->SetFrame(10, 20, 300, 70.0f);
    mPanel2->AddSection(mSubPanel2);

    mSubPanel1 = new ToolMenuPanel();
    mSubPanel1->SetTitle("journey through junkyard");
    mSubPanel1->SetFrame(10, 20, 300, 70.0f);
    mPanel2->AddSection(mSubPanel1);




    

}

PolygonMenu::~PolygonMenu() {

}

void PolygonMenu::Layout() {
    ToolMenu::Layout();

}


void PolygonMenu::Notify(void *pSender, const char *pNotification) {

}







