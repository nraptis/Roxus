/*
 *
 *  Achievement.h
 *  Darts
 *
 *  Created by Nick Raptis on 11/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include "Buffer.h"
#include "List.h"

class Achievement
{
public:
    
    Achievement(const char *pName, int pProgressMax);
    Achievement();
    
    virtual ~Achievement();
    
    void                SetUp(const char *pName, int pProgressMax=1);
    
    //mName is also used as identifier for GameCenter or OpenFeint...
    FString				mName;
	
	virtual void		Load(Buffer *pBuffer);
	virtual void		Save(Buffer *pBuffer);
	
	virtual void		ResetProgress();
	virtual bool		AddProgress(int pProgress=1);
	
	void				Print();
	
	//Is it posted to Game Center / OpenFeint yet?
	bool				mPosted;
	
	//Once mProgress = mProgressMax, we are complete. Great for stuff like "do 5,000 of X."
	int					mProgress;
	int					mProgressMax;
	
	int					mProgressSaved;
	
	//Is the achievement complete?? Well... IS IT?
	bool				mComplete;
	bool				mCompletedThisUpdate;
	
	//Used exclusively for achievement manager...
	bool				mAutoResetsOnLevelUp;
	bool				mAutoResetsOnGameOver;
    
	bool				mAutoResetsOnAction;
	int					mAutoResetsActionId;
};

class AchievementGroup
{
public:
    
    AchievementGroup(const char *pGroupName);
    virtual ~AchievementGroup();
    
    void                    Add(const char *pAchievementName, int pProgressMax=1);
    void                    AddProgress(List *pBubbleList, int pProgress=1);
    
    FString                 mGroupName;
    
    List                    mAchievementList;
};

class AchievementManager
{
public:
    
	AchievementManager();
	virtual ~AchievementManager();
    
	void					LevelUp();
	void					GameOver();
	void					PerformAction(int pAction);
	
	void					Reset();
    
    void                    Add(const char *pAchievementName, int pProgressMax=1);
    void                    Add(const char *pAchievementName, const char *pGroupName, int pProgressMax=1);
    
	bool					Exists(FString pName);
    
    void                    GetAllAchievements(List *pList);
    
    void                    Synchronize(const char *pAchievementName, int pProgress);
    void                    Synchronize(Achievement *pAchievement, int pProgress);
    
    
    
    Achievement				*GetAchievement(const char *pName);
    Achievement				*GetAchievement(char *pName);
	Achievement				*GetAchievement(FString pName);
    
    void                    AddProgressGroup(const char *pGroupName, List *pBubbleList, int pProgress=1);
    Achievement				*AddProgress(const char *pAchievementName, int pProgress=1);
    
	void					Print();
	
	virtual void			Load();
	virtual void			Save();
    
    List                    mAchievementList;
    List                    mAchievementGroupList;
};


#endif