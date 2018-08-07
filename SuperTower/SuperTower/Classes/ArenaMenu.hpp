//
//  ArenaMenu.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/7/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef ARENA_MENU_HPP
#define ARENA_MENU_HPP

#include "ToolMenu.hpp"
#include "FPoint.h"

class WorldContainer;
class ArenaMenu : public ToolMenu {
public:
    ArenaMenu();
    virtual ~ArenaMenu();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    ToolMenuSectionRow                      *mFrameRow;
    UICheckBox                              *mPlayCheckBox;
    UIButton                                *mOneFrameButton;

    UISegment                               *mSpeedSegment;

};

#endif
