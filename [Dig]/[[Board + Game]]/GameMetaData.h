//
//  GameMetaData.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/11/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__GameMetaData__
#define __DigMMMac__GameMetaData__

#include <stdio.h>

class GameMetaData
{
public:
    GameMetaData();
    ~GameMetaData();
    
    int                                     mScore;
    
    int                                     mCurrency;
    int                                     mCurrencyGem1;
    int                                     mCurrencyGem2;
    int                                     mCurrencyGem3;
    
    
    int                                     mLevelCurrent;
    
    bool                                    mLevelUnlocked[512];
    
    int                                     mLevelStars[512];
    int                                     mLevelPlayCount[512];
    int                                     mLevelScore[512];
    
    int                                     mLevelUnlockedCount;
    
    
    
    void                                    Save();
    void                                    Save(const char *pFile);
    
    void                                    Load();
    void                                    Load(const char *pFile);
    
};

#endif /* defined(__DigMMMac__GameMetaData__) */
