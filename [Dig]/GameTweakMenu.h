//
//  GameTweakMenu.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/13/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__GameTweakMenu__
#define __DigMMMac__GameTweakMenu__

#include "UMenu.h"

class GameTweakMenu : public UMenu
{
public:
    GameTweakMenu();
    virtual ~GameTweakMenu();
    
    
    virtual void                            Notify(void *pSender);
    
    UButton                                 *mButtonReset;
    UButton                                 *mButtonLevelUp;
    
    UButton                                 *mButtonMainMenu;
    UButton                                 *mButtonGame;
    
    int                                     mGimpTimer;
};

#endif /* defined(__DigMMMac__GameTweakMenu__) */
