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
#include "ToolMenuSection.hpp"
#include "UIElement.hpp"

class UIButton;
class UILabel;
class UISlider;
class UISegment;

class ToolMenuSectionRow : public ToolMenuSection {
public:
    ToolMenuSectionRow();
    virtual ~ToolMenuSectionRow();

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Layout();

    static float                            RowHeight();

    virtual void                            Notify(void *pSender, const char *pNotification);
};

#endif /* ToolMenuSectionRow_hpp */
