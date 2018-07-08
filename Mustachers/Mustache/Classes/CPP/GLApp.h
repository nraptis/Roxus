#pragma once

#define GAME_TEST_MODE 1
#undef GAME_TEST_MODE

#define GAPP ((GLApp*)gApp)


#define TOWER_FRAMES 16

#include "Application.h"
#include "HSList.h"


class Game;

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
    
    Sprite                                  mTile;
    
    
    
    
    
    Sprite                                  mUnit;
    
    Sprite                                  mTower[TOWER_FRAMES];
    
    virtual void                            AchProgress(const char *pAchievementName, int pCount=1);
    virtual void                            AchProgressGroup(const char *pGroupName, int pCount=1);

};

float CX(int pGridX);
float CY(int pGridY);

extern Game *gGame;







