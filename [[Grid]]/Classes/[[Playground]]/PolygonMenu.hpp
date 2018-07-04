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


class PolygonMenu : public ToolMenu {
public:
    PolygonMenu();
    virtual ~PolygonMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    ToolMenuPanel                           *mPanel1;
    ToolMenuPanel                           *mPanel2;
    ToolMenuPanel                           *mPanel3;

    ToolMenuSection                         *mSection1;
    ToolMenuSection                         *mSection2;
    ToolMenuSection                         *mSection3;



};

#endif
