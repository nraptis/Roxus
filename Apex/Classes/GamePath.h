//
//  GamePath.h
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_GamePath_h
#define Mustache_GamePath_h

#include "TilePathFinder.h"
#include "GameTile.h"

#define PATH_DIRECTION_NULL 0
#define PATH_DIRECTION_UP 1
#define PATH_DIRECTION_DOWN 2
#define PATH_DIRECTION_LEFT 3
#define PATH_DIRECTION_RIGHT 4
#define PATH_DIRECTION_UPLEFT 5
#define PATH_DIRECTION_UPRIGHT 6
#define PATH_DIRECTION_DOWNLEFT 7
#define PATH_DIRECTION_DOWNRIGHT 8


class GameArena;

class GamePath
{
public:
    
    GamePath();
    ~GamePath();
    
    void                                Update();
    void                                Draw();
    
    GameArena                           *mArena;
    
    void                                ComputePath();
    void                                ComputeSmoothPath();
    
    void                                AddSmooth(float pX, float pY, float pZ, int pGridX, int pGridY, int pGridZ);
    
    int                                 mStartX;
    int                                 mStartY;
    int                                 mStartZ;
    
    int                                 mEndX;
    int                                 mEndY;
    int                                 mEndZ;
    
    int                                 mLength;
    int                                 mSize;
    
    int                                 *mPathX;
    int                                 *mPathY;
    int                                 *mPathZ;
    
    
    
    
    float                               *mSmoothPathX;
    float                               *mSmoothPathY;
    float                               *mSmoothPathZ;
    
    int                                 *mSmoothPathGridX;
    int                                 *mSmoothPathGridY;
    int                                 *mSmoothPathGridZ;
    
    int                                 *mSmoothPathDrawZ;
    
    int                                 mSmoothLength;
    int                                 mSmoothSize;
    
    FXMLTag                             *Save();
    void                                Load(FXMLTag *pTag);
};

#endif
