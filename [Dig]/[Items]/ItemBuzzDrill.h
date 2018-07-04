//
//  ItemBuzzDrill.h
//  Digplex
//
//  Created by Nick Raptis on 12/5/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__ItemBuzzDrill__
#define __Digplex__ItemBuzzDrill__

#include "ActionProcItem.h"
#include "FParticle.h"
#include "FObject.h"

class ItemBuzzDrill : public ActionProcItem
{
public:
    ItemBuzzDrill();
    virtual ~ItemBuzzDrill();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            DrawEffects();
    virtual void                            DrawFocus(float pX, float pY);
    
    virtual void                            StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    virtual void                            UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
};

#endif /* defined(__Digplex__ItemBuzzDrill__) */
