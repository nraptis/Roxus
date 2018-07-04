//
//  RockHammer.h
//  Digplex
//
//  Created by Nick Raptis on 11/30/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__RockHammer__
#define __Digplex__RockHammer__

#include "ActionProcItem.h"

class RockHammer : public ActionProcItem
{
public:
    RockHammer();
    virtual ~RockHammer();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            DrawEffects();
    virtual void                            DrawFocus(float pX, float pY);
    
    virtual void                            StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    virtual void                            UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
};


#endif /* defined(__Digplex__RockHammer__) */
