//
//  GLApp.cpp
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "core_app_shell.h"
#include "GLApp.hpp"
#include "Util_ScreenFrame.h"
#include "FCanvas.hpp"
#include "PGMainCanvas.hpp"
#include "WorldContainer.hpp"
#include "PriorityQueue.hpp"

#include "TilePathFinderHeapOld.hpp"
#include "TilePathFinderHeap.hpp"


float gArenaWidth = 512.0f;
float gArenaWidth2 = 256.0f;
float gArenaHeight = 512.0f;
float gArenaHeight2 = 256.0f;

float gTileSize = 50.0f;
float gTileSize2 = 25.0f;
float gPathBendInset45 = 20.0f;
float gPathBendInset90 = 20.0f;

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
    //mDarkMode = false;
    mDarkMode = false;


    TilePathFinderHeapOld aHeapOld;
    TilePathFinderHeap aHeap;

    for (int i=0;i<500;i++) {

        PathNodeConnection *aCon = new PathNodeConnection();
        aCon->mCostTotal = gRand.Get(-2000, 2000);

        aHeapOld.Add(aCon);
        aHeap.Add(aCon);
    }


    int aPopIter = 0;
    for (int i=50;i<500;i+=3) {

        PathNodeConnection *aPop1 = aHeapOld.Pop();
        PathNodeConnection *aPop2 = aHeap.Pop();
        if (aPop1->mCostTotal != aPop2->mCostTotal) {
            printf("1.0 [%d] - Mismatch [%d] vs [%d]\n", aPopIter, aPop1->mCostTotal, aPop2->mCostTotal);
        }
        aPopIter += 1;
    }


    for (int i=0;i<200;i++) {
        PathNodeConnection *aCon = new PathNodeConnection();
        aCon->mCostTotal = gRand.Get(-5000, 5000);
        aHeapOld.Add(aCon);
        aHeap.Add(aCon);
    }

    /*
    aPopIter = 0;
    for (int i=3;i<500;i+=3) {

        PathNodeConnection *aPop1 = aHeapOld.Pop();
        PathNodeConnection *aPop2 = aHeap.Pop();
        if (aPop1->mCostTotal != aPop2->mCostTotal) {
            printf("2.0 [%d] - Mismatch [%d] vs [%d]\n", aPopIter, aPop1->mCostTotal, aPop2->mCostTotal);
        }

        aPopIter += 1;
    }
    */


    aHeapOld.Reset();
    aHeap.Reset();

    for (int i=0;i<1110;i++) {

        PathNodeConnection *aCon = new PathNodeConnection();
        aCon->mCostTotal = gRand.Get(-2000, 2000);

        aHeapOld.Add(aCon);
        aHeap.Add(aCon);
    }

    aHeapOld.Reset();
    aHeap.Reset();


    for (int i=0;i<111;i++) {

        PathNodeConnection *aCon = new PathNodeConnection();
        aCon->mCostTotal = gRand.Get(-2000, 2000);

        aHeapOld.Add(aCon);
        aHeap.Add(aCon);
    }

    aHeapOld.Reset();
    aHeap.Reset();

    //exit(0);

//#include "TilePathFinderHeapOld.hpp"
//#include "TilePathFinderHeap.hpp"


    
    /*
    PriorityQueue aQueue;
    void *aObj1 = (void *)0xDEADBEE0;
    void *aObj2 = (void *)0xDEADBEE1;
    void *aObj3 = (void *)0xDEADBEE2;
    void *aObj4 = (void *)0xDEADBEE3;
    void *aObj5 = (void *)0xDEADBEE4;
    void *aObj6 = (void *)0xDEADBEE5;
    void *aObj7 = (void *)0xBEEADD01;
    void *aObj8 = (void *)0xBEEADD02;
    void *aObj9 = (void *)0xBEEADD03;
    void *aObj10 = (void *)0xBEEADD04;
    
    
    for (int q=0;q<256;q++) {
    
    
    aQueue.Enqueue(aObj1, 4);
    aQueue.Enqueue(aObj2, 5);
    aQueue.Enqueue(aObj3, 2);
    aQueue.Enqueue(aObj4, 7);
    aQueue.Enqueue(aObj5, 10);
    aQueue.Enqueue(aObj6, -1);
        
    for (int i=0;i<3;i++) {
        void *aObj = aQueue.Dequeue();
        printf("Deq1[%d] = %lX\n", i, aObj);
        
    }
    
    aQueue.Enqueue(aObj7, 4);
    aQueue.Enqueue(aObj8, 5);
    aQueue.Enqueue(aObj9, 2);
    aQueue.Enqueue(aObj10, 7);
    
    for (int i=0;i<10;i++) {
        void *aObj = aQueue.Dequeue();
        printf("Deq2[%d] = %lX\n", i, aObj);
        
    }
        
        int aCap1 = gRand.Get(1000);
        int aCap2 = gRand.Get(1000);
        
        for (int i=0;i<aCap1;i++) {
            aQueue.Enqueue((void *)gRand.Get(1000), gRand.Get(20));
        }
        
        for (int i=0;i<aCap2;i++) {
            void *aObj = aQueue.Dequeue();
            printf("Dequeue[%lX]\n", aObj);
        }
        
        
        
        
    }
    
    
    exit(0);
    */
     
    
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

    //glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

    gImageBundler.StartBundle("tower_basic_off");
    mTowerBasicOff.Load("tower_basic_off_", 0, 23);

    gImageBundler.StartBundle("tower_basic_on");
    mTowerBasicOn.Load("tower_basic_on_", 0, 23);
    gImageBundler.EndBundle();

    //mRobot.LoadSequential("robot_", 0, 24, 20);

    mLevelBackTunnel.Load("level_layer_bridge");
    mLevelBackFloor.Load("level_layer_floor");
    mLevelBackBridge.Load("level_layer_tunnel");

    //glEnable(GL_TEXTURE_GEN_S);
    //glEnable(GL_TEXTURE_GEN_T);

    m1024x1024.Load("1024x1024");
    m2048x2048.Load("2048x2048");


    mTile1.Load("tile_whole_1");
    mTile2.Load("tile_whole_2");
    mTile3.Load("tile_whole_3");
    mTile4.Load("tile_whole_4");
    
    mPathArrow.Load("path_cycle_arrow");
    

    //AppShellSetSpriteFrameScale(1.0f);
    //We can't change this on the fly...
    //AppShellSetImageFileScale(3);


    gImageBundler.StartBundle("ninja_run_1");
    mNinja.LoadSection("ninja_rot_", 0, 1, 2, "_", 300, 340);
    gImageBundler.StartBundle("ninja_run_2");
    mNinja.LoadSection("ninja_rot_", 2, 3, 2, "_", 300, 340);
    gImageBundler.StartBundle("ninja_run_3");
    mNinja.LoadSection("ninja_rot_", 4, 5, 2, "_", 300, 340);
    gImageBundler.StartBundle("ninja_run_4");
    mNinja.LoadSection("ninja_rot_", 6, 7, 2, "_", 300, 340);
    gImageBundler.StartBundle("ninja_run_5");
    mNinja.LoadSection("ninja_rot_", 8, 9, 2, "_", 300, 340);
    gImageBundler.StartBundle("ninja_run_6");
    mNinja.LoadSection("ninja_rot_", 10, 11, 2, "_", 300, 340);
    gImageBundler.StartBundle("ninja_run_7");
    mNinja.LoadSection("ninja_rot_", 12, 13, 2, "_", 300, 340);
    gImageBundler.StartBundle("ninja_run_8");
    mNinja.LoadSection("ninja_rot_", 14, 15, 2, "_", 300, 340);
    gImageBundler.EndBundle();

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
    float aResult = (float)pGridX * gTileSize + gTileSize2;
    return aResult;
}

float CY(int pGridY, int pGridZ) {
    float aResult = (float)pGridY * gTileSize + gTileSize2;
    aResult += SZ(pGridZ);
    return aResult;
}

float SZ(int pGridZ) {
    float aResult = 0.0f;
    if(pGridZ == 0)aResult += gTileSize * 0.65f;
    if(pGridZ == 2)aResult -= gTileSize * 0.65f;
    return aResult;
}



