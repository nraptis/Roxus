//
//  Unit.h
//  Mustache
//
//  Created by Nick Raptis on 6/17/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef UNIT_HPP
#define UNIT_HPP

#include "GLApp.hpp"
#include "LevelPath.hpp"
#include "SmallGameObject.hpp"


class GameArena;
class AnimatedLevelPath;
class GameTile;
class UnitPath;

class Unit : public SmallGameObject {
public:

    Unit();
    virtual ~Unit();

    virtual void                        Update();
    virtual void                        Draw();

    int                                 mHP;
    int                                 mHPMax;

    bool                                mStartedWalking;
    
    float                               mWalkSpeed;
    bool                                mWalking;

    float                               mMovePercent;

    float                               mMoveStartX;
    float                               mMoveStartY;
    float                               mMoveStartZ;

    float                               mMoveEndX;
    float                               mMoveEndY;
    float                               mMoveEndZ;

    float                               mRotation;
    float                               mRotationSpeed;
    
    float                               mFrame;

    bool                                mLeader;

    ///////////////////////////////////////////////
    //                                           //
    //           Only Pathing Stuff              //
    //                                           //


    void                                PlaceOnGrid(PathNode *pStartNode, PathNode *pDestinationNode, GameTile *pDestinationTile, LevelPath *pPath);

    int                                 mDestinationGridX;
    int                                 mDestinationGridY;
    int                                 mDestinationGridZ;

    LevelPath                           *mTrackingPath;

    GameTile                            *mDestinationTile;

    PathNode                            *mStartNode;
    PathNode                            *mDestinationNode;

    UnitPath                            *mPath;

    int                                 mPathIndex;

    //                                           //
    //                                           //
    //                                           //
    ///////////////////////////////////////////////


    
};

#endif
