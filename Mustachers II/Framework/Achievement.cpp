/*
 *  Achievement.cpp
 *  Darts
 *
 *  Created by Nick Raptis on 11/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Achievement.h"
#include "stdafx.h"
#include "Application.h"

Achievement::Achievement(const char *pName, int pProgressMax)
{
    SetUp(pName, pProgressMax);
}

Achievement::Achievement()
{
    SetUp((const char *)0, 1);
}

void Achievement::SetUp(const char *pName, int pProgressMax)
{
    mName = pName;
    
    mProgressMax = pProgressMax;
    
	mCompletedThisUpdate = false;
	mAutoResetsOnLevelUp = false;
	mAutoResetsOnGameOver = false;
	mAutoResetsOnAction = false;
	
	mAutoResetsActionId = -1;
	mProgress = 0;
	mProgressSaved = 0;
	
	mPosted = false;
	mComplete = false;
    
	mName = pName;
	mProgress = 0;
	mProgressMax = pProgressMax;
}

Achievement::~Achievement()
{
    
}

void Achievement::ResetProgress()
{
	mProgress = 0;
	mProgressSaved = 0;
}

void Achievement::Load(Buffer *pBuffer)
{
	if(pBuffer)
	{
		mProgress=pBuffer->ReadInt();
		mProgressMax=pBuffer->ReadInt();
		mAutoResetsActionId=pBuffer->ReadInt();
		mProgressSaved=pBuffer->ReadInt();
		
		mComplete=pBuffer->ReadBool();
		mCompletedThisUpdate=pBuffer->ReadBool();
		mPosted=pBuffer->ReadBool();
		mAutoResetsOnLevelUp=pBuffer->ReadBool();
		mAutoResetsOnGameOver=pBuffer->ReadBool();
		mAutoResetsOnAction=pBuffer->ReadBool();
        
        mName=pBuffer->ReadString();
	}
}

void Achievement::Print()
{
	printf("%s: complete: %d (%d/%d) posted: %d\n", mName.c(), mComplete, mProgress, mProgressMax, mPosted);
}

void Achievement::Save(Buffer *pBuffer)
{
	if(pBuffer)
	{
		pBuffer->WriteInt(mProgress);
		pBuffer->WriteInt(mProgressMax);
		pBuffer->WriteInt(mAutoResetsActionId);
		pBuffer->WriteInt(mProgressSaved);
		
		pBuffer->WriteBool(mComplete);
		pBuffer->WriteBool(mCompletedThisUpdate);
		pBuffer->WriteBool(mPosted);
		pBuffer->WriteBool(mAutoResetsOnLevelUp);
		pBuffer->WriteBool(mAutoResetsOnGameOver);
		pBuffer->WriteBool(mAutoResetsOnAction);
        
        pBuffer->WriteString(mName);
	}
}

bool Achievement::AddProgress(int pProgress)
{
	if(mProgress<mProgressMax)
	{
		mProgress+=pProgress;
		if(mProgress>mProgressMax)mProgress=mProgressMax;
		if(mProgress<0)mProgress=0;
		if(mProgress==mProgressMax)
		{
			if(gApp)
			{
				gApp->DisplayAchievement(this);
			}
			mComplete=true;
			return true;
		}
	}
	else
	{
		mProgress=mProgressMax;
	}
	
	return false;
}

/////////////////////////
/////////////////////////
/////////////////////////


AchievementGroup::AchievementGroup(const char *pGroupName)
{
    mGroupName = pGroupName;
}

AchievementGroup::~AchievementGroup()
{
    
}

void AchievementGroup::AddProgress(List *pBubbleList, int pProgress)
{
    EnumList(Achievement, aAchievement, mAchievementList)
    {
        if(aAchievement->AddProgress(pProgress))
        {
            //printf("Achievement Complete [%s]\n\n", aAchievement->mName.c());
            
            if(pBubbleList)
            {
                pBubbleList->Add(aAchievement);
            }
            
        }
    }
}

void AchievementGroup::Add(const char *pAchievementName, int pProgressMax)
{
    Achievement *aAchievement = 0;
    EnumList(Achievement, aCheck, mAchievementList)
    {
        if(aCheck->mName == pAchievementName)
        {
            aAchievement = aCheck;
        }
    }
    if(aAchievement == 0)
    {
        aAchievement = new Achievement(pAchievementName, pProgressMax);
        mAchievementList += aAchievement;
    }
    else
    {
        aAchievement->mProgressMax = pProgressMax;
    }
}

/////////////////////////
/////////////////////////
/////////////////////////


AchievementManager::AchievementManager()
{
    
}

AchievementManager::~AchievementManager()
{
    Reset();
}

void AchievementManager::LevelUp()
{
	
}

void AchievementManager::GameOver()
{
	
}

void AchievementManager::PerformAction(int pAction)
{
	
}


Achievement *AchievementManager::GetAchievement(const char *pName)
{
    Achievement *aReturn=0;
    
    EnumList(Achievement, aAchievement, mAchievementList)
    {
        if(aAchievement->mName == pName)
        {
            aReturn = aAchievement;
        }
    }
    
    if(aReturn == 0)
    {
        EnumList(AchievementGroup, aGroup, mAchievementGroupList)
        {
            EnumList(Achievement, aAchievement, aGroup->mAchievementList)
            {
                if(aAchievement->mName == pName)
                {
                    aReturn = aAchievement;
                }
            }
        }
    }
    
	return aReturn;
}

Achievement *AchievementManager::GetAchievement(char *pName)
{
    return GetAchievement((const char*)pName);
}

Achievement *AchievementManager::GetAchievement(FString pName)
{
    return GetAchievement((const char*)pName.c());
}

void AchievementManager::AddProgressGroup(const char *pGroupName, List *pBubbleList, int pProgress)
{
    EnumList(AchievementGroup, aGroup, mAchievementGroupList)
    {
        if(aGroup->mGroupName == pGroupName)
        {
            aGroup->AddProgress(pBubbleList, pProgress);
        }
    }
}

Achievement *AchievementManager::AddProgress(const char *pAchievementName, int pProgress)
{
	Achievement *aAchievement = GetAchievement(pAchievementName);
	if(aAchievement)
	{
		if(aAchievement->AddProgress(pProgress))
		{
			return aAchievement;
		}
	}
	return 0;
}

void AchievementManager::Add(const char *pAchievementName, int pProgressMax)
{
    Achievement *aAchievement = 0;
    EnumList(Achievement, aCheck, mAchievementList)
    {
        if(aCheck->mName == pAchievementName)
        {
            aAchievement = aCheck;
        }
    }
    if(aAchievement == 0)
    {
        aAchievement = new Achievement(pAchievementName, pProgressMax);
        mAchievementList += aAchievement;
    }
    else
    {
        aAchievement->mProgressMax = pProgressMax;
    }
}

void AchievementManager::Add(const char *pAchievementName, const char *pGroupName, int pProgressMax)
{
    AchievementGroup *aGroup = 0;
    EnumList(AchievementGroup, aCheckGroup, mAchievementGroupList)
    {
        if(aCheckGroup->mGroupName == pGroupName)aGroup = aCheckGroup;
    }
    if(aGroup == 0)
    {
        aGroup = new AchievementGroup(pGroupName);
        mAchievementGroupList += aGroup;
    }
    aGroup->Add(pAchievementName, pProgressMax);
}

void AchievementManager::GetAllAchievements(List *pList)
{
    
    EnumList(AchievementGroup, aGroup, mAchievementGroupList)
    {
        EnumList(Achievement, aAchievement, aGroup->mAchievementList)
        {
            pList->Add(aAchievement);
        }
    }
    
    EnumList(Achievement, aAchievement, mAchievementList)
    {
        pList->Add(aAchievement);
    }
    
}


bool AchievementManager::Exists(FString pName)
{
    return GetAchievement(pName) != 0;
}

void AchievementManager::Reset()
{
    
}

void AchievementManager::Load()
{
	Buffer aBuffer;
	aBuffer.Load(FString("achievements.dat"));
	
	int aAchievementCount=aBuffer.ReadInt();
	
    for(int i=0;i<aAchievementCount;i++)
	{
		Achievement *aAchievement = new Achievement();
		aAchievement->Load(&aBuffer);
        Synchronize(aAchievement->mName.c(), aAchievement->mProgress);
        delete aAchievement;
	}
    
    int aAchievementGroupCount=aBuffer.ReadInt();
    for(int k=0;k<aAchievementGroupCount;k++)
	{
        aAchievementCount=aBuffer.ReadInt();
        for(int i=0;i<aAchievementCount;i++)
        {
            Achievement *aAchievement = new Achievement();
            aAchievement->Load(&aBuffer);
            Synchronize(aAchievement->mName.c(), aAchievement->mProgress);
            delete aAchievement;
        }
	}
    
}

void AchievementManager::Save()
{
    
    Buffer aBuffer;
    
    aBuffer.WriteInt(mAchievementList.mCount);
    EnumList(Achievement, aAchievement, mAchievementList)
    {
        aAchievement->Save(&aBuffer);
    }
    
    aBuffer.WriteInt(mAchievementGroupList.mCount);
    EnumList(AchievementGroup, aGroup, mAchievementGroupList)
    {
        aBuffer.WriteInt(aGroup->mAchievementList.mCount);
        EnumList(Achievement, aAchievement, aGroup->mAchievementList)
        {
            aAchievement->Save(&aBuffer);
        }
    }
    
	aBuffer.Save(gDocuments + FString("achievements.dat"));
    
}

void AchievementManager::Synchronize(const char *pAchievementName, int pProgress)
{
    EnumList(Achievement, aAchievement, mAchievementList)
    {
        if(aAchievement->mName == pAchievementName)
        {
            Synchronize(aAchievement, pProgress);
        }
    }
    
    EnumList(AchievementGroup, aGroup, mAchievementGroupList)
    {
        EnumList(Achievement, aAchievement, aGroup->mAchievementList)
        {
            if(aAchievement->mName == pAchievementName)
            {
                Synchronize(aAchievement, pProgress);
            }
        }
    }
    
}

void AchievementManager::Synchronize(Achievement *pAchievement, int pProgress)
{
    if(pAchievement)
    {
        if(pAchievement->mProgress < pProgress)
        {
            pAchievement->mProgress = pProgress;
            if(pAchievement->mProgress > pAchievement->mProgressMax)
            {
                pAchievement->mProgress = pAchievement->mProgressMax;
            }
        }
    }
}


void AchievementManager::Print()
{
	printf("\n\n[--Achievement List--]\n");
    
    
    printf("\n[Ungrouped]\n{\n");
    EnumList(Achievement, aAchievement, mAchievementList)
    {
        printf("\t");
        aAchievement->Print();
    }
    printf("}\n");
    
    EnumList(AchievementGroup, aGroup, mAchievementGroupList)
    {
        printf("\n[Group %s]\n{\n", aGroup->mGroupName.c());
        
        EnumList(Achievement, aAchievement, aGroup->mAchievementList)
        {
            printf("\t");
            aAchievement->Print();
        }
        
        printf("}\n");
    }
    

    /*
    for(int i=0;i<mListSize;i++)
    {
        if(mList[i])
        {
            printf("AchList[%d] = %s\n", i, mList[i]->mName.c());
        }
        else
        {
            printf("AchList[%d] = {NULL}\n", i);
        }
    }
    
	printf("[--------------------]\n");
    printf("Achievement Count: %d]\n", mAchievementCount);
    
    for(int i=0;i<mAchievementHashTableSize;i++)
    {
        if(mAchievementHashTable[i])
        {
            printf("AchHash[%d] = {", i);
            
            Achievement *aHashed = mAchievementHashTable[i];
            
            while(aHashed)
            {
                printf("%s", aHashed->mName.c());
                
                if(aHashed->mHashNeighbor)
                {
                    printf(", ");
                }
                
                if(aHashed->mHashNeighbor == aHashed)
                {
                    printf("@@@   WHAT????\n");
                    printf("@@@   WHAT????\n");
                    printf("@@@   WHAT????\n");
                    printf("@@@   WHAT????\n");
                }
                
                aHashed=aHashed->mHashNeighbor;
            }
            
            printf("}\n");
            
        }
        else
        {
            printf("AchHash[%d] = {NULL}\n", i);
        }
    }
    */
}

