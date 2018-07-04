//
//  Transition.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__Transition__
#define __CoreDemo__Transition__

#define TRANSITION_STATE_INITIAL 0
#define TRANSITION_STATE_ENTER 1
#define TRANSITION_STATE_SWAP 2
#define TRANSITION_STATE_EXIT 3

class Transition
{
public:
    
    Transition();
    virtual ~Transition();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                Kill(){if(mKill == 0){mKill=5;}}
    int                                 mKill;
    
    int                                 mTransitionState;
    
    int                                 mEnterTime;
    int                                 mSwapTime;
    int                                 mExitTime;
    
    int                                 mTimer;
    
    float                               mScale;
    
};

#endif
