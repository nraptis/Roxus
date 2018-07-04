//
//  GameMetaData.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/11/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "GameMetaData.h"


GameMetaData::GameMetaData()
{
    mScore = 0;
    
    mCurrency = 0;
    
    mCurrencyGem1 = 0;
    mCurrencyGem2 = 0;
    mCurrencyGem3 = 0;
    
    mLevelCurrent = 0;
    mLevelUnlockedCount = 0;
    
    for(int i=0;i<512;i++)
    {
        mLevelUnlocked[i] = 0;
        mLevelStars[i] = 0;
        mLevelPlayCount[i] = 0;
        mLevelScore[i] = 0;
    }
    
}

GameMetaData::~GameMetaData()
{
    
}

void GameMetaData::Save()
{
    
}

void GameMetaData::Save(const char *pFile)
{
    
}

void GameMetaData::Load()
{
    
}

void GameMetaData::Load(const char *pFile)
{
    
}




