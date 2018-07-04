//
//  MainMenuSceneItem.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/3/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__MainMenuSceneItem__
#define __DigMMMac__MainMenuSceneItem__

#include "FObject.h"
#include "FSprite.h"
#include "FParticle.h"

class MainMenuSceneItem
{
public:
    
    MainMenuSceneItem(FSprite *pSprite);
    virtual ~MainMenuSceneItem();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            AddItem(MainMenuSceneItem *pItem);
    
    virtual void                            SetRelativePos(float pX, float pY);
    virtual void                            Place(float pCenterX, float pCenterY, float pScale);
    
    float                                   mRelativeX;
    float                                   mRelativeY;
    
    float                                   mX;
    float                                   mY;
    
    float                                   mScale;
    
    FSprite                                 *mSprite;
    
    FList                                   mItemList;
};

#endif /* defined(__DigMMMac__MainMenuSceneItem__) */
