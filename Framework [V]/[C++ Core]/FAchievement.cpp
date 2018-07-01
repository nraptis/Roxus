/*
 *  FAchievement.cpp
 *  Darts
 *
 *  Created by Nick Raptis on 11/30/10.
 *  Copyright 2010 Nick Raptis. All rights reserved.
 *
 */

#include "FApp.h"
#include "FAchievement.h"
#include "core_includes.h"

FAchievement::FAchievement(const char *pName, int pProgressMax)
{
    SetUp(pName, pProgressMax);
}

FAchievement::FAchievement()
{
    SetUp((const char *)0, 1);
}

void FAchievement::SetUp(const char *pName, int pProgressMax)
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

FAchievement::~FAchievement()
{
    
}

void FAchievement::ResetProgress()
{
	mProgress = 0;
	mProgressSaved = 0;
}

void FAchievement::Load(FFile *pFFile)
{
	if(pFFile)
	{
		mProgress=pFFile->ReadInt();
		mProgressMax=pFFile->ReadInt();
		mAutoResetsActionId=pFFile->ReadInt();
		mProgressSaved=pFFile->ReadInt();
		
		mComplete=pFFile->ReadBool();
		mCompletedThisUpdate=pFFile->ReadBool();
		mPosted=pFFile->ReadBool();
		mAutoResetsOnLevelUp=pFFile->ReadBool();
		mAutoResetsOnGameOver=pFFile->ReadBool();
		mAutoResetsOnAction=pFFile->ReadBool();
        
        mName=pFFile->ReadString();
	}
}

void FAchievement::Print()
{
	Log("%s: complete: %d (%d/%d) posted: %d\n", mName.c(), mComplete, mProgress, mProgressMax, mPosted);
}

void FAchievement::Save(FFile *pFFile)
{
	if(pFFile)
	{
		pFFile->WriteInt(mProgress);
		pFFile->WriteInt(mProgressMax);
		pFFile->WriteInt(mAutoResetsActionId);
		pFFile->WriteInt(mProgressSaved);
		
		pFFile->WriteBool(mComplete);
		pFFile->WriteBool(mCompletedThisUpdate);
		pFFile->WriteBool(mPosted);
		pFFile->WriteBool(mAutoResetsOnLevelUp);
		pFFile->WriteBool(mAutoResetsOnGameOver);
		pFFile->WriteBool(mAutoResetsOnAction);
        
        pFFile->WriteString(mName);
	}
}

bool FAchievement::AddProgress(int pProgress)
{
	if(mProgress<mProgressMax)
	{
		mProgress+=pProgress;
		if(mProgress>mProgressMax)mProgress=mProgressMax;
		if(mProgress<0)mProgress=0;
		if(mProgress==mProgressMax)
		{
			if(gAppBase)
			{
				//gApp->DisplayFAchievement(this);
                
                
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


FAchievementGroup::FAchievementGroup(const char *pGroupName)
{
    mGroupName = pGroupName;
}

FAchievementGroup::~FAchievementGroup()
{
    
}

void FAchievementGroup::AddProgress(FList *pBubbleList, int pProgress)
{
    EnumList(FAchievement, aFAchievement, mFAchievementList)
    {
        if(aFAchievement->AddProgress(pProgress))
        {
            //Log("FAchievement Complete [%s]\n\n", aFAchievement->mName.c());
            
            if(pBubbleList)
            {
                pBubbleList->Add(aFAchievement);
            }
            
        }
    }
}

void FAchievementGroup::Add(const char *pFAchievementName, int pProgressMax)
{
    FAchievement *aFAchievement = 0;
    EnumList(FAchievement, aCheck, mFAchievementList)
    {
        if(aCheck->mName == pFAchievementName)
        {
            aFAchievement = aCheck;
        }
    }
    if(aFAchievement == 0)
    {
        aFAchievement = new FAchievement(pFAchievementName, pProgressMax);
        mFAchievementList += aFAchievement;
    }
    else
    {
        aFAchievement->mProgressMax = pProgressMax;
    }
}

/////////////////////////
/////////////////////////
/////////////////////////


FAchievementController::FAchievementController()
{
    
}

FAchievementController::~FAchievementController()
{
    Reset();
}

void FAchievementController::LevelUp()
{
	
}

void FAchievementController::GameOver()
{
	
}

void FAchievementController::PerformAction(int pAction)
{
	
}


FAchievement *FAchievementController::GetFAchievement(const char *pName)
{
    FAchievement *aReturn=0;
    
    EnumList(FAchievement, aFAchievement, mFAchievementList)
    {
        if(aFAchievement->mName == pName)
        {
            aReturn = aFAchievement;
        }
    }
    
    if(aReturn == 0)
    {
        EnumList(FAchievementGroup, aGroup, mFAchievementGroupList)
        {
            EnumList(FAchievement, aFAchievement, aGroup->mFAchievementList)
            {
                if(aFAchievement->mName == pName)
                {
                    aReturn = aFAchievement;
                }
            }
        }
    }
    
	return aReturn;
}

FAchievement *FAchievementController::GetFAchievement(char *pName)
{
    return GetFAchievement((const char*)pName);
}

FAchievement *FAchievementController::GetFAchievement(FString pName)
{
    return GetFAchievement((const char*)pName.c());
}

void FAchievementController::AddProgressGroup(const char *pGroupName, FList *pBubbleList, int pProgress)
{
    EnumList(FAchievementGroup, aGroup, mFAchievementGroupList)
    {
        if(aGroup->mGroupName == pGroupName)
        {
            aGroup->AddProgress(pBubbleList, pProgress);
        }
    }
}

FAchievement *FAchievementController::AddProgress(const char *pFAchievementName, int pProgress)
{
	FAchievement *aFAchievement = GetFAchievement(pFAchievementName);
	if(aFAchievement)
	{
		if(aFAchievement->AddProgress(pProgress))
		{
			return aFAchievement;
		}
	}
	return 0;
}

void FAchievementController::Add(const char *pFAchievementName, int pProgressMax)
{
    FAchievement *aFAchievement = 0;
    EnumList(FAchievement, aCheck, mFAchievementList)
    {
        if(aCheck->mName == pFAchievementName)
        {
            aFAchievement = aCheck;
        }
    }
    if(aFAchievement == 0)
    {
        aFAchievement = new FAchievement(pFAchievementName, pProgressMax);
        mFAchievementList += aFAchievement;
    }
    else
    {
        aFAchievement->mProgressMax = pProgressMax;
    }
}

void FAchievementController::Add(const char *pFAchievementName, const char *pGroupName, int pProgressMax)
{
    FAchievementGroup *aGroup = 0;
    EnumList(FAchievementGroup, aCheckGroup, mFAchievementGroupList)
    {
        if(aCheckGroup->mGroupName == pGroupName)aGroup = aCheckGroup;
    }
    if(aGroup == 0)
    {
        aGroup = new FAchievementGroup(pGroupName);
        mFAchievementGroupList += aGroup;
    }
    aGroup->Add(pFAchievementName, pProgressMax);
}

void FAchievementController::GetAllFAchievements(FList *pList)
{
    
    EnumList(FAchievementGroup, aGroup, mFAchievementGroupList)
    {
        EnumList(FAchievement, aFAchievement, aGroup->mFAchievementList)
        {
            pList->Add(aFAchievement);
        }
    }
    
    EnumList(FAchievement, aFAchievement, mFAchievementList)
    {
        pList->Add(aFAchievement);
    }
    
}


bool FAchievementController::Exists(FString pName)
{
    return GetFAchievement(pName) != 0;
}

void FAchievementController::Reset()
{
    
}

void FAchievementController::Load()
{
	FFile aFile;
	aFile.Load(FString("achievements.dat"));
	
	int aFAchievementCount=aFile.ReadInt();
	
    for(int i=0;i<aFAchievementCount;i++)
	{
		FAchievement *aFAchievement = new FAchievement();
		aFAchievement->Load(&aFile);
        Synchronize(aFAchievement->mName.c(), aFAchievement->mProgress);
        delete aFAchievement;
	}
    
    int aFAchievementGroupCount=aFile.ReadInt();
    for(int k=0;k<aFAchievementGroupCount;k++)
	{
        aFAchievementCount=aFile.ReadInt();
        for(int i=0;i<aFAchievementCount;i++)
        {
            FAchievement *aFAchievement = new FAchievement();
            aFAchievement->Load(&aFile);
            Synchronize(aFAchievement->mName.c(), aFAchievement->mProgress);
            delete aFAchievement;
        }
	}
    
}

void FAchievementController::Save()
{
    
    FFile aFile;
    
    aFile.WriteInt(mFAchievementList.mCount);
    EnumList(FAchievement, aFAchievement, mFAchievementList)
    {
        aFAchievement->Save(&aFile);
    }
    
    aFile.WriteInt(mFAchievementGroupList.mCount);
    EnumList(FAchievementGroup, aGroup, mFAchievementGroupList)
    {
        aFile.WriteInt(aGroup->mFAchievementList.mCount);
        EnumList(FAchievement, aFAchievement, aGroup->mFAchievementList)
        {
            aFAchievement->Save(&aFile);
        }
    }
    
	aFile.Save(gDirDocuments + FString("achievements.dat"));
    
}

void FAchievementController::Synchronize(const char *pFAchievementName, int pProgress)
{
    EnumList(FAchievement, aFAchievement, mFAchievementList)
    {
        if(aFAchievement->mName == pFAchievementName)
        {
            Synchronize(aFAchievement, pProgress);
        }
    }
    
    EnumList(FAchievementGroup, aGroup, mFAchievementGroupList)
    {
        EnumList(FAchievement, aFAchievement, aGroup->mFAchievementList)
        {
            if(aFAchievement->mName == pFAchievementName)
            {
                Synchronize(aFAchievement, pProgress);
            }
        }
    }
    
}

void FAchievementController::Synchronize(FAchievement *pFAchievement, int pProgress)
{
    if(pFAchievement)
    {
        if(pFAchievement->mProgress < pProgress)
        {
            pFAchievement->mProgress = pProgress;
            if(pFAchievement->mProgress > pFAchievement->mProgressMax)
            {
                pFAchievement->mProgress = pFAchievement->mProgressMax;
            }
        }
    }
}


void FAchievementController::Print()
{
	Log("\n\n[--FAchievement List--]\n");
    
    
    Log("\n[Ungrouped]\n{\n");
    EnumList(FAchievement, aFAchievement, mFAchievementList)
    {
        Log("\t");
        aFAchievement->Print();
    }
    Log("}\n");
    
    EnumList(FAchievementGroup, aGroup, mFAchievementGroupList)
    {
        Log("\n[Group %s]\n{\n", aGroup->mGroupName.c());
        
        EnumList(FAchievement, aFAchievement, aGroup->mFAchievementList)
        {
            Log("\t");
            aFAchievement->Print();
        }
        
        Log("}\n");
    }
    

    /*
    for(int i=0;i<mListSize;i++)
    {
        if(mList[i])
        {
            Log("AchList[%d] = %s\n", i, mList[i]->mName.c());
        }
        else
        {
            Log("AchList[%d] = {NULL}\n", i);
        }
    }
    
	Log("[--------------------]\n");
    Log("FAchievement Count: %d]\n", mFAchievementCount);
    
    for(int i=0;i<mFAchievementHashTableSize;i++)
    {
        if(mFAchievementHashTable[i])
        {
            Log("AchHash[%d] = {", i);
            
            FAchievement *aHashed = mFAchievementHashTable[i];
            
            while(aHashed)
            {
                Log("%s", aHashed->mName.c());
                
                if(aHashed->mHashNeighbor)
                {
                    Log(", ");
                }
                
                if(aHashed->mHashNeighbor == aHashed)
                {
                    Log("@@@   WHAT????\n");
                    Log("@@@   WHAT????\n");
                    Log("@@@   WHAT????\n");
                    Log("@@@   WHAT????\n");
                }
                
                aHashed=aHashed->mHashNeighbor;
            }
            
            Log("}\n");
            
        }
        else
        {
            Log("AchHash[%d] = {NULL}\n", i);
        }
    }
    */
}

