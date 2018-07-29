//
//  Unit.h
//  Mustache
//
//  Created by Nick Raptis on 6/17/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_Unit_h
#define Mustache_Unit_h

#include "GLApp.h"
#include "LevelPath.hpp"
#include "SmallGameObject.hpp"


class GameArena;
class AnimatedLevelPath;

class Unit : public SmallGameObject {
public:

    Unit();
    virtual ~Unit();

    virtual void                        Update();
    virtual void                        Draw();

    int                                 mHP;
    int                                 mHPMax;

    float                               mTargetX;
    float                               mTargetY;
    float                               mTargetZ;
    
    float                               mWalkSpeed;
    
    bool                                mWalking;
    
    float                               mRotation;
    float                               mRotationSpeed;
    
    float                               mFrame;



    /*
    float                               mX;
    float                               mY;
    float                               mZ;

    int                                 mDrawZ;

    int                                 mGridX;
    int                                 mGridY;
    int                                 mGridZ;

    //void                                SetUp(int pGridX, int pGridY);
    void                                SetUp(int pGridX, int pGridY, int pGridZ);
    */





    ///////////////////////////////////////////////
    //                                           //
    //           Only Pathing Stuff              //
    //                                           //


    void                                PlaceOnGrid(PathNode *pStartNode, PathNode *pDestinationNode, LevelPath *pPath);

    int                                 mDestinationGridX;
    int                                 mDestinationGridY;
    int                                 mDestinationGridZ;

    LevelPath                           *mTrackingPath;

    int                                 mPathIndex;


    
};

#endif
