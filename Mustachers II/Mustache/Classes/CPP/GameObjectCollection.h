//
//  GameObjectCollection.h
//  Mustache
//
//  Created by Nick Raptis on 9/17/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_GameObjectCollection_h
#define Mustache_GameObjectCollection_h

#include "GameObject.h"

class GameObjectCollection
{
public:
    
    GameObjectCollection();
    ~GameObjectCollection();
    
    
    virtual void                        Update();
    virtual void                        Draw();
    
    
    void                                AddObject(GameObject *pGameObject);
    
    GameObject                          **mList;
    int                                 mCount;
    int                                 mSize;
    
    void                                SortAscendingY();
    
};

#endif
