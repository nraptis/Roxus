//
//  LevelPath.h
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef LEVEL_PATH_HPP
#define LEVEL_PATH_HPP

#include "GameTile.hpp"

//The most basic form of path, contains only grid data
//and computes most efficient path using modified A*
class GameArena;
class LevelPath {
public:
    
    LevelPath();
    ~LevelPath();
    
    virtual void                        ComputePath(GameArena *pArena);

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

    FString                             mName;

    FXMLTag                             *Save();
    void                                Load(FXMLTag *pTag);
};

#endif
