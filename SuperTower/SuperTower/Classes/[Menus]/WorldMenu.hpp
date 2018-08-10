//
//  WorldMenu.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef WorldMenu_hpp
#define WorldMenu_hpp

#include "ToolMenu.hpp"
#include "FPoint.h"

class WorldContainer;
class WorldMenu : public ToolMenu {
public:
    WorldMenu(WorldContainer *pWorld);
    virtual ~WorldMenu();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    WorldContainer                          *mWorld;

    UISlider                                *mSliderZoom;
    UISlider                                *mSliderPanRotation;

    UISlider                                *mSliderTestRotation;

};

#endif
