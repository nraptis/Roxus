//
//  GameInterfaceBottom.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__GameInterfaceBottom__
#define __CoreDemo__GameInterfaceBottom__

#include "MainApp.h"
#include "GameInterfaceTop.h"
#include "ItemBlaster.h"
#include "ItemBuzzDrill.h"
#include "RockHammer.h"

class GameInterfaceBottom : public FView
{
public:
    
    GameInterfaceBottom();
    virtual ~GameInterfaceBottom();
    
    void                                    SetUp(float pY, float pHeight);
    
    virtual void                            Update();
    virtual void                            Draw();
    
    ItemBlaster                             *mBlaster;
    ItemBuzzDrill                           *mBuzzDrill;
    RockHammer                              *mRockHammer1;
    RockHammer                              *mRockHammer2;
    
    //GameInterfaceProgressbar                mProgressBar1;
    //GameInterfaceProgressbar                mProgressBar2;
    
    FView                                   mContentLeft;
    FView                                   mContentRight;
};

#endif /* defined(__CoreDemo__GameInterfaceBottom__) */
