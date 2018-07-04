//
//  MainMenuRock.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/9/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__MainMenuRock__
#define __DigMMMac__MainMenuRock__

#include "MainMenuSceneItem.h"

class MainMenuRock : public MainMenuSceneItem
{
public:
    
    MainMenuRock(FSprite *pSprite);
    virtual ~MainMenuRock();
    
    virtual void                            Update();
    virtual void                            Draw();
    
};

class MainMenuRockGrass : public MainMenuSceneItem
{
public:
    
    MainMenuRockGrass(FSprite *pSprite);
    virtual ~MainMenuRockGrass();
    
    virtual void                            Update();
    virtual void                            Draw();
    
};

#endif /* defined(__DigMMMac__MainMenuRock__) */
