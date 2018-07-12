//
//  GLApp.cpp
//  OptimizeRX
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
#include "Game.h"
#include "WorldContainer.hpp"

float gArenaWidth = 512.0f;
float gArenaWidth2 = 256.0f;
float gArenaHeight = 512.0f;
float gArenaHeight2 = 256.0f;
float gTileWidth = 46.0f;
float gTileHeight = 46.0f;

float gArenaActiveWidth = 512.0f;
float gArenaActiveWidth2 = 256.0f;
float gArenaActiveHeight = 512.0f;
float gArenaActiveHeight2 = 256.0f;
float gArenaActiveX = 0.0f;
float gArenaActiveY = 0.0f;

GLApp *gApp = 0;
GLApp::GLApp() {
    gApp = this;
    mWorld = 0;
}

GLApp::~GLApp() {
    
}

void GLApp::Update() {


}

void GLApp::Draw() {
    FDrawQuad aQuad;
    aQuad.SetColorBottom(0.84f, 0.86f, 0.92f);
    aQuad.SetColorTop(0.92f, 0.93f, 0.96f);
    aQuad.SetRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    aQuad.Draw();

    aQuad.SetColorLeft(0.64f, 0.46f, 0.78f, 0.08f);
    aQuad.SetColorRight(0.72f, 0.66f, 1.0f, 0.7f);
    //aQuad.SetRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    aQuad.Draw();

    Graphics::Clear(0.125f, 0.125f, 0.133f);
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.6);
    
    for (float aX = 0.0f;aX < gAppWidth;aX += 10.0) {
        for (float aY = 0.0f;aY < gAppHeight;aY += 10.0) {
            Graphics::DrawPoint(aX, aY, 2.0);
        }
    }
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

    
    //Util_ScreenFrame *aScreenFrameUtil = new Util_ScreenFrame();
    //mWindowTools.AddChild(aScreenFrameUtil);
}

float CX(int pGridX) {
    return (float)pGridX * gTileWidth + (gTileWidth / 2.0f);
}

float CY(int pGridY) {
    return (float)pGridY * gTileHeight + (gTileHeight / 2.0f);
}

float CX(int pGridX, int pGridZ) {
    float aReturn = CX(pGridX);

    //if(pGridZ == 0)aReturn -= 4.0f;
    //if(pGridZ == 2)aReturn += 4.0f;

    return aReturn;
}

float CY(int pGridY, int pGridZ)
{
    float aReturn = CY(pGridY);

    //if(pGridZ == 0)aReturn += 22.0f;
    //if(pGridZ == 2)aReturn -= 22.0f;

    if(pGridZ == 0)aReturn += gTileHeight * 0.6666f;
    if(pGridZ == 2)aReturn -= gTileHeight * 0.6666f;

    return aReturn;
}
