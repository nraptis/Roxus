//
//  Transition.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef TRANSITION_H
#define TRANSITION_H

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
    float                               mGlobalScale;
    
    float                               mFade;
    float                               mBlur;
};

#endif
