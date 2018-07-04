//
//  GameStoreScreen.h
//  Digplex
//
//  Created by Nick Raptis on 11/26/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__GameStoreScreen__
#define __Digplex__GameStoreScreen__

#include "FView.h"
#include "FScrollView.h"
#include "MenuButton.h"

class GameStoreScreenCell : public FView
{
public:
    GameStoreScreenCell();
    virtual ~GameStoreScreenCell();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Notify(void *pSender);
};

class GameStoreScreen : public FView
{
public:
    
    GameStoreScreen();
    virtual ~GameStoreScreen();
    
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            Notify(void *pSender);
    
    FView                                   mViewTop;
    
    FScrollView                             mScrollViewContent;
    
    FView                                   mViewBottom;
    
    MenuButton                              mButtonClose;
    MenuButton                              mButtonZone;
    
};

#endif /* defined(__Digplex__GameStoreScreen__) */
