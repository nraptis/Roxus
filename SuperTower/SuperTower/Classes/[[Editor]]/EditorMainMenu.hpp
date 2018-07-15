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

    void                                    RefreshActiveMenus();


    UISegment                               *mMainSegment;

    ToolMenuPanel                           *mPanelMainControls;
    ToolMenuSectionRow                      *mRowMainMenu;
    UIButton                                *mButtonSave;
    UIButton                                *mButtonExport;

    ToolMenuSectionRow                      *mRowClear;
    UIButton                                *mButtonClearTunnels;
    UIButton                                *mButtonClearTiles;
    UIButton                                *mButtonClearBridges;

    ToolMenuSectionRow                      *mRowFlood;
    UIButton                                *mButtonFloodTunnels;
    UIButton                                *mButtonFloodTiles;
    UIButton                                *mButtonFloodBridges;

    ToolMenuSectionRow                      *mRowGridSize;
    UIButton                                *mButtonWidthAdd;
    UIButton                                *mButtonWidthSubtract;
    UIButton                                *mButtonHeightAdd;
    UIButton                                *mButtonHeightSubtract;

    ToolMenuSectionRow                      *mRowGridBuffer;
    UIButton                                *mButtonBufferAdd;
    UIButton                                *mButtonBufferSubtract;
    

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

    UISlider                                *mSliderTunnelOpacity;
    UISlider                                *mSliderTileOpacity;
    UISlider                                *mSliderBridgeOpacity;


    UISlider                                *mSliderTileGridOpacity;





};

#endif /* EditorMainMenu_hpp */
