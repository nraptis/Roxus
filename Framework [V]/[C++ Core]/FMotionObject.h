//
//  FMotionObject.h
//  2015 Gnome Launcher
//
//  Created by Nicholas Raptis on 12/27/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef ___015_Fleet_XP__FMotionObject__
#define ___015_Fleet_XP__FMotionObject__

#define SPAWN_SOURCE_UNKNOWN -1
#define SPAWN_SOURCE_POINT 0
#define SPAWN_SOURCE_RECT 1
#define SPAWN_SOURCE_CIRCLE 2
#define SPAWN_SOURCE_POLYGON 3
#define SPAWN_SOURCE_POINT_CLOUD 4

#define MOT_NODE_TYPE_TRACKING 3
#define MOT_NODE_TYPE_UNKNOWN 0
#define MOT_NODE_TYPE_GEOMETRY 4
#define MOT_NODE_TYPE_SPAWN_BEHAVIOR 6

#include "FObject.h"
#include "FSprite.h"
#include "FSpriteSequence.h"
#include "FPointList.h"
#include "FDrawQuad.hpp"

class FMotionObject : public FObject
{
public:
    
	//FMotionObject(FSpriteSequence *pSpriteSequence);
	FMotionObject(FSprite *pSprite);
	FMotionObject();
    virtual ~FMotionObject();

	//virtual void							Update(int pTime);
	virtual void							Update();
	virtual void							Draw();
    
    float									mX;
	float									mY;
    
    float									mRotation;
    
	float									mScale;
    float									mScaleX;
    float									mScaleY;
    
	float									mRed;
	float									mGreen;
	float									mBlue;
	float									mAlpha;
    
	FSprite									*mSprite;
    void                                    SetSprite(FSprite *pSprite);
    void                                    SetSprite(FSprite &pSprite){SetSprite(&pSprite);}
    
    void                                    SetSize(float pWidth, float pHeight);
    float                                   mWidth;
    float                                   mHeight;
    
protected:
    
    void                                    BaseInitialize();
    
};

#endif





