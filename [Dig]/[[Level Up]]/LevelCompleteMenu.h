//
//  LevelCompleteMenu.h
//  CrossBone
//
//  Created by Nick Raptis on 7/24/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#ifndef __CrossBone__LevelCompleteMenu__
#define __CrossBone__LevelCompleteMenu__


#include "MenuButton.h"
#include "FVec2.h"

class LevelCompleteMenu : public FView
{
public:
    
    LevelCompleteMenu(bool pDidWin);
    virtual ~LevelCompleteMenu();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    //virtual void                            ButtonClick(FButton *pButton);
    virtual void                            Notify(void *pSender);
    
    MenuButton                              *mButtonDone;
    
    bool                                    mStarAnimation;
    int                                     mStarAnimationTimer;
    bool                                    mStarEarned[3];
    bool                                    mStarEarnedDisplay[3];
    
    FVec2                                   mStarPos[3];
    
    float                                   mStarShake[3];
    
    int                                     mStarAnimationIndex;
    
    bool                                    mDidWin;
    
};

#endif

/* defined(__CrossBone__LevelCompleteMenu__) */
