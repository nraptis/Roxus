#include "GLApp.h"
#include "Game.h"

Game *gGame;
TilePathFinder *gPathFinder;

float gArenaWidth = 512.0f;
float gArenaWidth2 = 256.0f;

float gArenaHeight = 512.0f;
float gArenaHeight2 = 256.0f;

GLApp::GLApp()
{
	gApp = this;
    
    mGame = 0;
    
    gPathFinder = new TilePathFinder();
}

GLApp::~GLApp()
{
    if(mGame)mGame->Kill();
    mGame=0;
}

void GLApp::Clean()
{
    if(mGame)mGame->Kill();
}

void GLApp::Load()
{
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
    
    mRobot.LoadSequential("robot_", 0, 24, 20);
    
    mLevelBackTunnel.Load("level_layer_bridge");
    mLevelBackFloor.Load("level_layer_floor");
    mLevelBackBridge.Load("level_layer_tunnel");
    
}

void GLApp::LoadComplete()
{
    
    //mEditor = new Editor();
    mGame = new Game();
    
    if(mGame)AddSubcanvas(mGame);
	LoadData();
    
    Application::LoadComplete();
    
    if(mMusicOn)
    {
        //PlayMusic("game_music.mp3");
    }
    
}

void GLApp::Update()
{
    
}

void GLApp::DrawOver()
{
    /*
    int aSpriteCount = 0;
    for(float x=0;x<1024;x+=10)
    {
        for(float y=0;y<768;y+=10)
        {
            mCheck.Center(x, y);
            aSpriteCount++;
        }
    }
    
    printf("Sprite Count = %d\n", aSpriteCount);
    */
    
}

void GLApp::Message(FString pMessage, FString pArguments)
{
    /*
    printf("==\n==\n{%s}\n==\n==\n", pMessage.c());
    
    if(pMessage == "gc_complete")
    {
        if(mGameCenterMenu)
        {
            mGameCenterMenu->Kill();
            mGameCenterMenu = 0;
        }
    }
    */
}

void GLApp::SaveData()
{
	Buffer aBuffer;
    aBuffer.WriteInt(12345);
    
	aBuffer.Save(FString(gDocuments + FString("saved.dat")).c());
	SaveStatic();
}

void GLApp::SaveStatic()
{
    Application::SaveStatic();
    mHSList.Save(gDocuments + "scores.dat");
}


void GLApp::LoadStatic()
{
	Application::LoadStatic();
	mHSList.Load(gDocuments + "scores.dat");
    SetMusicVolume(mMusicVolume);
}

void GLApp::LoadData()
{
	Buffer aBuffer;
    aBuffer.Load(gDocuments + FString("saved.dat"));
    //int aRead = aBuffer.ReadInt();
    
    
}

void GLApp::GoInactive()
{
    Application::GoInactive();
}

void GLApp::GoActive()
{
    Application::GoActive();
}

void GLApp::PauseForIAd()
{
	SaveStatic();
    mStopUpdates = true;
    mStopDraws = true;
    SetMusicVolume(0);
}

void GLApp::UnpauseForIAd()
{
	mStopUpdates = false;
    mStopDraws = false;
    SetMusicVolume(mMusicVolume);
}

void GLApp::SuccessfulPurchase(char* pId)
{
	Application::SuccessfulPurchase(pId);
    mPurchased = true;
    SaveStatic();
	//AchProgress("unlock");
}

void GLApp::FailPurchase(char* pId)
{
	Application::FailPurchase(pId);
}

void GLApp::CancelPurchase(char* pId)
{
	Application::CancelPurchase(pId);
}

void GLApp::AchProgress(const char *pAchievementName, int pCount)
{
    //Achievement *aAchievement = mAchievementManager.AddProgress(pAchievementName, pCount);
    //if(aAchievement)mRecentAchievementList += aAchievement;
}

void GLApp::AchProgressGroup(const char *pGroupName, int pCount)
{
    //mAchievementManager.AddProgressGroup(pGroupName, &mRecentAchievementList, pCount);
}



float CX(int pGridX)
{
    return (float)pGridX * gTileWidth + (gTileWidth / 2.0f);
}

float CY(int pGridY)
{
    return (float)pGridY * gTileHeight + (gTileHeight / 2.0f);
}

float CX(int pGridX, int pGridZ)
{
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
