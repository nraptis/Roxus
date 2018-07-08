#pragma once

#define GAME_TEST_MODE 1
#undef GAME_TEST_MODE

#define GAPP ((GLApp*)gApp)


#define TOWER_FRAMES 24

#include "Application.h"
#include "HSList.h"
#include "SpriteSequence.h"
#include "SpriteSequenceNested.h"

class Game;
class TilePathFinder;

class GLApp : public Application
{
public:
	
    GLApp();
	virtual ~GLApp();
    
    Game                                    *mGame;
    
    virtual void                            GoInactive();
    virtual void                            GoActive();
    
    virtual void                            Update();
    
    virtual void                            DrawOver();
    
    virtual void                            Clean();
	virtual void                            Load();

	virtual void                            LoadComplete();
    
    virtual void                            Message(FString pMessage, FString pArguments);
    
	virtual void                            SuccessfulPurchase(char* pId);
	virtual void                            FailPurchase(char* pId);
	virtual void                            CancelPurchase(char* pId);
    
    virtual void                            SaveData();
	virtual void                            LoadData();
	virtual void                            LoadStatic();
	virtual void                            SaveStatic();
	
	virtual void                            PauseForIAd();
	virtual void                            UnpauseForIAd();
    
    Sprite                                  mTileTunnel;
    Sprite                                  mTileFloor;
    Sprite                                  mTileBridge;
    
    Sprite                                  mBridgeRampU;
    Sprite                                  mBridgeRampD;
    Sprite                                  mBridgeRampL;
    Sprite                                  mBridgeRampR;
    
    Sprite                                  mFloorRampU;
    Sprite                                  mFloorRampD;
    Sprite                                  mFloorRampL;
    Sprite                                  mFloorRampR;
    
    Sprite                                  mBlocker;
    
    Sprite                                  mUnitCircleSoft;
    Sprite                                  mUnitCircleHard;
    
    SpriteSequence                          mTowerBasicOff;
    SpriteSequence                          mTowerBasicOn;
    
    SpriteSequenceNested                    mRobot;
    
    Sprite                                  mTowerMenuButtonBack[2];
    Sprite                                  mTowerMenuButtonPrice8;
    Sprite                                  mTowerMenuButtonPrice20;
    Sprite                                  mTowerMenuButtonPrice45;
    Sprite                                  mTowerMenuButtonPrice65;
    Sprite                                  mTowerMenuButtonPrice75;
    Sprite                                  mTowerMenuButtonPrice100;
    Sprite                                  mTowerMenuButtonPrice125;
    
    
    Sprite                                  mTowerDetailMenuButtonInfo;
    Sprite                                  mTowerDetailMenuButtonSell;
    Sprite                                  mTowerDetailMenuButtonUpgrade;
    
    Sprite                                  mGridOverlay[2];
    
    
    virtual void                            AchProgress(const char *pAchievementName, int pCount=1);
    virtual void                            AchProgressGroup(const char *pGroupName, int pCount=1);
    
    
    Sprite                                  mLevelBackTunnel;
    Sprite                                  mLevelBackFloor;
    Sprite                                  mLevelBackBridge;
    
    
    Sprite mCheck;
    
};

float CX(int pGridX);
float CY(int pGridY);

float CX(int pGridX, int pGridZ);
float CY(int pGridY, int pGridZ);


extern Game *gGame;
extern TilePathFinder *gPathFinder;

extern float gArenaWidth;
extern float gArenaWidth2;

extern float gArenaHeight;
extern float gArenaHeight2;






