//
//  ToolMenuSectionRow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuSectionRow_hpp
#define ToolMenuSectionRow_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"

class ToolMenuSectionRow : public FCanvas {
public:
    ToolMenuSectionRow();
    virtual ~ToolMenuSectionRow();

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Layout();

    virtual void                            Notify(void *pSender, const char *pNotification);

    UIRoundedRect                           mSectionBackgroundOutline;
    UIRoundedRect                           mSectionBackground;
};

#endif /* ToolMenuSectionRow_hpp */
