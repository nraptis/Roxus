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
#include "FScrollCanvas.hpp"
#include "ToolMenuContent.hpp"
#include "ToolMenuSection.hpp"
#include "ToolMenuPanel.hpp"

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

    //Step 1
    void                                    SetTitle(const char *pText);

    //Step 2
    void                                    SetScrollMode(bool pScroll);

    //Step 3
    void                                    AddSection(ToolMenuSection *pSection);


    void                                    Expand();
    void                                    Collapse();
    bool                                    mExpanded;
    float                                   mExpandedHeight;


    ToolMenuHeader                          mHeader;

    //Use either flat content or scroll content...
    ToolMenuContent                         mContent;
    FScrollCanvas                           mScrollContent;


    FList                                   mSectionList;

    bool                                    mScrollMode;

    UIRoundedRect                           mMenuBackground;
    UIRoundedRect                           mMenuBackgroundOutline;
    UIRoundedRect                           mMenuBackgroundShadow;
};

#endif /* ToolMenu_hpp */
