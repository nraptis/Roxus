#include "Particle.h"
#include "Application.h"
#include "Sprite.h"

Particle::Particle()
{
	mColor=Color(1,1,1,1);
	mColorAdd=Color(0,0,0,0);
	mColorDecay=Color(1,1,1,1);
	
	mRotation=0;
	mRotationAdd=0;
	mRotationDecay=1;
	
	mScale=1;
	mScaleAdd=0;
	mScaleDecay=1;
	
	mPos=FPoint(0,0);
	mVel=FPoint(0,0);
	mVelAdd=FPoint(0,0);
	mVelDecay=FPoint(1,1);
	
	mTimer=0;
	
	mSprite=0;
	
	mName="Particle";
}

Particle::~Particle()
{
	
}

void Particle::Update()
{
	mColor+=mColorAdd;
	mColorAdd*=mColorDecay;
	
	mRotation+=mRotationAdd;
	mRotation*=mRotationDecay;
	
	mRotation+=mRotationAdd;
	mRotationAdd*=mRotationDecay;
	
	mScale+=mScaleAdd;
	mScaleAdd*=mScaleDecay;
	
	mPos+=mVel;
	mVel+=mVelAdd;
	mVel*=mVelDecay;
	
	if(mPos.mX>gAppWidth+300||mPos.mX<-300||mPos.mY>gAppHeight+300||mPos.mY<-300)
	{
		mKill=true;
	}
	if(mScale<=0||mColor.mAlpha<=0)
	{
		mKill=true;
	}
	if(mTimer>0)
	{
		if(--mTimer==0)
        {
            mKill=true;
        }
	}
}

void Particle::Draw()
{
	if(mSprite)
	{
		SetColor(mColor);
		mSprite->Draw(mPos.mX,mPos.mY,mScale,mRotation);
	}
}

Particle *Particle::Duplicate()
{
	
	
	Particle *aParticle = new Particle();
	aParticle->mColor=mColor;
	aParticle->mColorAdd=mColorAdd;
	aParticle->mColorDecay=mColorDecay;
	
	aParticle->mRotation=mRotation;
	aParticle->mRotationAdd=mRotationAdd;
	aParticle->mRotationDecay=mRotationDecay;
	
	aParticle->mScale=mScale;
	aParticle->mScaleAdd=mScaleAdd;
	aParticle->mScaleDecay=mScaleDecay;
	
	aParticle->mPos=mPos;
	aParticle->mVel=mVel;
	aParticle->mVelAdd=mVelAdd;
	aParticle->mVelDecay=mVelDecay;
	
	aParticle->mTimer=mTimer;
	aParticle->mSprite=mSprite;
	
	aParticle->mName=mName;
	
	return aParticle;
}



