//
//  Unit.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "Unit.h"
#include "GameArena.h"
#include "AnimatedLevelPath.hpp"

Unit::Unit() {

    mTrackingPath = 0;

    mTargetX = 0.0f;
    mTargetY = 0.0f;
    mTargetZ = 0.0f;

    mPathIndex = 0;

    mKill = 0;

    mDestinationGridX = -1;
    mDestinationGridY = -1;
    mDestinationGridZ = -1;
    
    mDrawZ = 0;
    
    mWalkSpeed = gRand.GetFloat(1.25f, 4.0f);

    mHPMax = 200;
    mHP = mHPMax;
    
    mWalking = false;
    
    mRotation = 0.0f;
    mRotationSpeed = 2.0f;

    mFrame = 0.0f;
}

Unit::~Unit() {
    //printf("Delete Unit [%x]\n", this);
}

void Unit::Update() {
    float aMaxFrame = (float)gApp->mNinja.mSequenceFrameCount;

    mFrame += 0.48f;
    if (mFrame >= aMaxFrame) {
        mFrame -= aMaxFrame;
    }

    if (mWalking) {

        float aTargetRotation = FaceTarget(mTargetX, mTargetY, mX, mY);
        
        mRotation += DistanceBetweenAngles(mRotation, aTargetRotation) / 14.0f;


        //TODO: Position will be controlled by a smoothing track of some sort...

    }
}

void Unit::Draw() {
    Graphics::SetColor();
    gApp->mNinja.Draw(mRotation, mFrame, mX, mY, 1.0f, 0.0f);
}

//void Unit::PlaceOnGrid(PathNode *pNode, LevelPath *pPath) {

void Unit::PlaceOnGrid(PathNode *pStartNode, PathNode *pDestinationNode, LevelPath *pPath) {
    if (pStartNode != 0 && pDestinationNode != 0 && pPath != 0) {
        int aGridX = pStartNode->mGridX;
        int aGridY = pStartNode->mGridY;
        int aGridZ = pStartNode->mGridZ;

        mGridX = pStartNode->mGridX;
        mGridY = pStartNode->mGridY;
        mGridZ = pStartNode->mGridZ;

        mX = gArena->GetUnitGridX(aGridX, aGridY, aGridZ);
        mY = gArena->GetUnitGridY(aGridX, aGridY, aGridZ);



        //TODO: Our Destination should be the center node of the end tile..
        //mDestinationGridX = pPath->mEndX;
        //mDestinationGridY = pPath->mEndY;
        //mDestinationGridZ = pPath->mEndZ;


        mTrackingPath = pPath;
    }


    /*
    if (pNode) {
        PlaceOnGrid(pNode->mGridX, pNode->mGridY, pNode->mGridZ);
    } else {
        PlaceOnGrid(pNode->mGridX, pNode->mGridY, pNode->mGridZ);
    }
    */
}



