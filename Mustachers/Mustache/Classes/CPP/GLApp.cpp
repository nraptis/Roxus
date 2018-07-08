#include "GLApp.h"

#include "Game.h"

Game *gGame;

GLApp::GLApp()
{
    
	gApp = this;
    
    mGame = 0;
    
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
    mTile.Load("tile");
    
    mUnit.Load("unit");
    
    for(int i=0;i<TOWER_FRAMES;i++)
    {
        int aIndex = i;
        FString aString;
        if(aIndex >= 10)aString = FString("demo_tower_00") + FString((aIndex));
        else aString = FString("demo_tower_000") + FString((aIndex));
        mTower[i].Load(aString.c());
    }

    
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
