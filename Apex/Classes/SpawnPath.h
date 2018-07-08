//
//  SpawnPath.h
//  Mustache
//
//  Created by Nick Raptis on 6/27/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_SpawnPath_h
#define Mustache_SpawnPath_h

class SpawnPath
{
public:
    
    SpawnPath();
    virtual ~SpawnPath();
    
    int                             mStartX;
    int                             mStartY;
    
    int                             mEndX;
    int                             mEndY;
};


#endif
