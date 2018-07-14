//
//  GLApp.cpp
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "core_app_shell.h"
#include "GLApp.h"
#include "Util_ScreenFrame.h"
#include "FCanvas.hpp"
#include "PGMainCanvas.hpp"
#include "WorldContainer.hpp"

float gArenaWidth = 512.0f;
float gArenaWidth2 = 256.0f;
float gArenaHeight = 512.0f;
float gArenaHeight2 = 256.0f;
float gTileWidth = 46.0f;
float gTileHeight = 46.0f;
float gTileWidth2 = 46.0f;
float gTileHeight2 = 46.0f;

float gArenaActiveWidth = 512.0f;
float gArenaActiveWidth2 = 256.0f;
float gArenaActiveHeight = 512.0f;
float gArenaActiveHeight2 = 256.0f;
float gArenaActiveX = 0.0f;
float gArenaActiveY = 0.0f;

bool gEditorMode = false;

GLApp *gApp = 0;
GLApp::GLApp() {
    gApp = this;
    mWorld = 0;

    //TODO: Twiddle
    mDarkMode = false;
    //mDarkMode = true;

    //gEnableEditor = false;
    gEditorMode = true;
    
}

GLApp::~GLApp() {
    
}

void GLApp::Update() {
    
}

void GLApp::Draw() {
    
}


void GLApp::SetVirtualFrame(float pX, float pY, float pWidth, float pHeight) {

}

void GLApp::TouchDown(float pX, float pY, void *pData) {

}

void GLApp::TouchMove(float pX, float pY, void *pData) {

}

void GLApp::TouchUp(float pX, float pY, void *pData) {

}

void GLApp::TouchFlush() {
    
}

void GLApp::MouseWheel(int pDirection) {

}

void GLApp::KeyDown(int pKey) {

}

void GLApp::KeyUp(int pKey) {

}

void GLApp::SetDeviceSize(float pWidth, float pHeight) {

}

void GLApp::Load() {
    //?!
    AppShellSetSpriteFrameScale(0.5f);
    
    mTileTunnel.Load("tile_tunnel");
    mTileFloor.Load("tile_floor");
    mTileBridge.Load("tile_bridge");

    mBridgeRampU.Load("bridge_ramp_u");
    mBridgeRampD.Load("bridge_ramp_d");
    mBridgeRampL.Load("bridge_ramp_l");
    mBridgeRampR.Load("bridge_ramp_r");

    mFloorRampU.Load("floor_ramp_u");
    mFloorRampD.Load("floor_ramp_d");
    mFloorRampL.Load("floor_ramp_l");
    mFloorRampR.Load("floor_ramp_r");

    mBlocker.Load("blocker");

    mUnitCircleSoft.Load("unit_circle_soft");
    mUnitCircleHard.Load("unit_circle_hard");

    mTowerMenuButtonBack[0].Load("tower_menu_cell");
    mTowerMenuButtonBack[1].Load("tower_menu_cell_selected");

    mTowerMenuButtonPrice8.Load("tower_menu_cell_price_8");
    mTowerMenuButtonPrice20.Load("tower_menu_cell_price_20");
    mTowerMenuButtonPrice45.Load("tower_menu_cell_price_45");
    mTowerMenuButtonPrice65.Load("tower_menu_cell_price_65");
    mTowerMenuButtonPrice75.Load("tower_menu_cell_price_75");
    mTowerMenuButtonPrice100.Load("tower_menu_cell_price_100");
    mTowerMenuButtonPrice125.Load("tower_menu_cell_price_125");

    mTowerDetailMenuButtonInfo.Load("tower_detail_menu_button_info");
    mTowerDetailMenuButtonSell.Load("tower_detail_menu_button_sell");
    mTowerDetailMenuButtonUpgrade.Load("tower_detail_menu_button_upgrade");

    mGridOverlay[0].Load("grid_overlay_1");
    mGridOverlay[1].Load("grid_overlay_2");

    mTowerBasicOff.Load("tower_basic_off_", 0, 23);
    mTowerBasicOn.Load("tower_basic_on_", 0, 23);

    //mRobot.LoadSequential("robot_", 0, 24, 20);

    mLevelBackTunnel.Load("level_layer_bridge");
    mLevelBackFloor.Load("level_layer_floor");
    mLevelBackBridge.Load("level_layer_tunnel");

    printf("Bundle: %s\n", gDirBundle.c());
    printf("Documents: %s\n", gDirDocuments.c());

    m1024x1024.Load("1024x1024");
    m2048x2048.Load("2048x2048");
}

void GLApp::LoadComplete() {
    //PGMainCanvas *aPlayground = new PGMainCanvas();
    //mWindowTools.AddChild(aPlayground);

    //mGame = new Game();
    //mWindowMain.AddChild(mGame);

    
    mWorld = new WorldContainer();
    mWindowMain.AddChild(mWorld);


    //gEditor = new

    
    //Util_ScreenFrame *aScreenFrameUtil = new Util_ScreenFrame();
    //mWindowTools.AddChild(aScreenFrameUtil);
}

float CX(int pGridX, int pGridZ) {
    float aResult = (float)pGridX * gTileWidth + gTileWidth2;
    return aResult;
}

float CY(int pGridY, int pGridZ) {
    float aResult = (float)pGridY * gTileHeight + gTileHeight2;
    if(pGridZ == 0)aResult += gTileHeight * 0.65f;
    if(pGridZ == 2)aResult -= gTileHeight * 0.65f;
    return aResult;
}
