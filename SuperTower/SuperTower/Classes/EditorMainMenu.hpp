//
//  EditorMainMenu.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/13/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef EditorMainMenu_hpp
#define EditorMainMenu_hpp

#include "ToolMenu.hpp"
#include "FPoint.h"

class WorldContainer;
class EditorGameArena;
class EditorMainMenu : public ToolMenu {
public:
    EditorMainMenu();
    virtual ~EditorMainMenu();

    virtual void                            Update();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    UISegment                               *mMainSegment;

    ToolMenuPanel                           *mPanelWorldTransform;
    ToolMenuSectionRow                      *mRowTransformButtons;
    UIButton                                *mButtonResetTransform;
    UISlider                                *mSliderZoom;
    UISlider                                *mSliderPanRotation;

    ToolMenuPanel                           *mPanelPaths;
    //UISegment                               *mSegmentPathStart;
    ToolMenuSectionRow                      *mRowPathMode;
    UICheckBox                              *mCheckBoxPathStart;
    UICheckBox                              *mCheckBoxPathSelect;

    ToolMenuSectionRow                      *mRowPathButtons;
    UIButton                                *mButtonAddPath;
    UIButton                                *mButtonDeletePath;

    ToolMenuPanel                           *mPanelTiles;
    UISegment                               *mSegmentTileDepth;

    ToolMenuSectionRow                      *mRowBasicTiles;
    UICheckBox                              *mCheckBoxTile;
    UICheckBox                              *mCheckBoxTileObstacle;

    ToolMenuSectionRow                      *mRowRampTiles;
    UICheckBox                              *mCheckBoxTileRampL;
    UICheckBox                              *mCheckBoxTileRampR;
    UICheckBox                              *mCheckBoxTileRampU;
    UICheckBox                              *mCheckBoxTileRampD;

};

#endif /* EditorMainMenu_hpp */
