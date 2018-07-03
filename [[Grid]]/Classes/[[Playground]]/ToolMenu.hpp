//
//  ToolMenu.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenu_hpp
#define ToolMenu_hpp

#include "DragableCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "ToolMenuHeader.hpp"
#include "UIButton.hpp"

class ToolMenu : public DragableCanvas {
public:
    ToolMenu();
    virtual ~ToolMenu();

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Layout();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            Notify(void *pSender, const char *pNotification);

    ToolMenuHeader                          mHeader;


    UIRoundedRect                           mMenuBackground;
    UIRoundedRect                           mMenuBackgroundOutline;
    UIRoundedRect                           mMenuBackgroundShadow;
};

#endif /* ToolMenu_hpp */
