//
//  ToolMenuHeader.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuHeader_hpp
#define ToolMenuHeader_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "UIButton.hpp"

class ToolMenu;
class ToolMenuHeader : public FCanvas {
public:
    ToolMenuHeader();
    virtual ~ToolMenuHeader();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            Notify(void *pSender, const char *pNotification);

    ToolMenu                                *mMenu;

    UIButton                                *mButtonClose;
    UIButton                                *mButtonMinimize;

    UIRoundedRect                           mMenuBackground;
};

#endif /* ToolMenuHeader_hpp */
