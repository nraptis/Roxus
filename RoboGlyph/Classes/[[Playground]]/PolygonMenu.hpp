//
//  PolygonMenu.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PolygonMenu_hpp
#define PolygonMenu_hpp

#include "ToolMenu.hpp"
#include "UISlider.hpp"
#include "UISegment.hpp"


class PolygonMenu : public ToolMenu {
public:
    PolygonMenu();
    virtual ~PolygonMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    ToolMenuPanel                           *mPanel1;
    ToolMenuPanel                           *mPanel2;
    ToolMenuPanel                           *mPanel3;

    ToolMenuPanel                           *mSubPanel1;
    ToolMenuPanel                           *mSubPanel2;
    ToolMenuPanel                           *mSubPanel3;
    

    ToolMenuSection                         *mSection1;
    ToolMenuSection                         *mSection2;
    ToolMenuSection                         *mSection3;


    UISlider                                *mSlider1;
    UISlider                                *mSlider2;

    UISegment                               *mSegment1;
    UISegment                               *mSegment2;


};

#endif
