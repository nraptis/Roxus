//
//  TimelineMenu.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/5/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef TIMELINE_MENU_HPP
#define TIMELINE_MENU_HPP

#include "ToolMenu.hpp"
#include "FPoint.h"


class WorldContainer;
class TimelineMenu : public ToolMenu {
public:
    TimelineMenu();
    virtual ~TimelineMenu();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);


    ToolMenuSectionRow                      *mFrameRow;
    UICheckBox                              *mPlayCheckBox;
    UIButton                                *mOneFrameButton;

    UISegment                               *mSpeedSegment;

};

#endif
