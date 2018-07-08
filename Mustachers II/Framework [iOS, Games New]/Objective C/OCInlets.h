#ifndef OCINLETS_H
#define OCINLETS_H

#include "FString.h"

unsigned long SystemTime();
FString SystemTimeString();

//unsigned int *LoadImage(char *pFile,int &pWidth, int &pHeight);
unsigned int *LoadImage(char *pFile,int &pWidth, int &pHeight, float &pScale);


unsigned int *LoadSound(char *theFilename, int *theDataSize, int *theDataFormat, int* theSampleRate);
void RootDeleteFile(char *pPath);
void ExportPNGImage(unsigned int *pData, char *pPath, int pWidth, int pHeight);
void ExportJPEGImage(unsigned int *pData, char *pPath, int pWidth, int pHeight, float pQuality=0.95f);
void ExportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight);
void GetDocumentsDirectory(char *pPath);
void GetBundleDirectory(char *pPath);
bool IsIPodMusicPlaying();
bool OpenURL( const char* utf8url );
void ShowAlert(const char *pTitle,const char *pText,const char *pButton="OK");
void OpenItunesURL(FString pURL);
void OpenURL(FString pURL);
void PlayMusic(FString pFile);
void SetMusicVolume(float pVolume);
void ShowControl();
void HideControl();
bool IsDevicePlayingMusic();
void SwitchToDeviceMusic();
void SwitchToAppMusic();

bool StoreIsConnecting();
bool StoreIsRequesting();
bool StoreIsPaying();

bool StoreDidSucceed();
bool StoreDidFail();
bool StoreDidCancel();

void StoreReset();

void StoreBuy(const char *pItem);
void StoreRestore();


void GameCenterConnect();

void GameCenterShowAchievements();
void GameCenterShowLeaderboard(FString pName);

bool GameCenterIsConnecting();
bool GameCenterIsConnected();
bool GameCenterDidFail();

bool GameCenterModeLeaderboard();
bool GameCenterModeAchievements();

bool GameCenterIsShowingLeaderboard();
bool GameCenterIsShowingAchievements();
bool GameCenterIsShowing();

void GameCenterSubmitScore(int pScore, const char *pLeaderboard);
void GameCenterSubmitScore(int pScore, char *pLeaderboard);
void GameCenterSubmitScore(int pScore, FString pLeaderboard);

void GameCenterUpdateAchievement(const char *pAchievement, float pPercent);
void GameCenterUpdateAchievement(char *pAchievement, float pPercent);
void GameCenterUpdateAchievement(FString pAchievement, float pPercent);

void GameCenterSyncAll();

#endif












