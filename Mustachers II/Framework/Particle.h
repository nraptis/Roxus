#include "FPoint.h"
#include "Color.h"
#include "Object.h"
#include "Buffer.h"


#ifndef PARTICLE_H
#define PARTICLE_H

class Sprite;
class Particle : public Object
{
public:
	Particle();
	virtual ~Particle();
	
	virtual void Update();
	virtual void Draw();
    
	Particle *Duplicate();
	
	Color mColor;
	Color mColorAdd;
	Color mColorDecay;
	
	float mRotation;
	float mRotationAdd;
	float mRotationDecay;
	
	float mScale;
	float mScaleAdd;
	float mScaleDecay;
	
	FPoint mPos;
	FPoint mVel;
	FPoint mVelAdd;
	FPoint mVelDecay;
	
	int mTimer;
	
	Sprite *mSprite;
};

#endif