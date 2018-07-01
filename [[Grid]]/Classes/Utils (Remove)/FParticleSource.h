//
//  FMotionObject.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/27/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef FFMO_PSPSPS_H
#define FFMO_PSPSPS_H

#include "FSpriteSequence.h"
#include "FSprite.h"

#include "FObject.h"
#include "FRandomizer.h"
#include "FPointList.h"

#include "FMotionObject.h"
#include "FList.h"

class FParticle;
class FParticleSource : public FMotionObject
{
public:

	FParticleSource(FSpriteSequence *pSpriteSequence);
	FParticleSource(FSprite *pSprite);
	FParticleSource();
	virtual ~FParticleSource();

    
	virtual void								Update();
	virtual void                                Draw();

	void										Clear();
	void										Reset();

    
	FObjectList									mParticles;

    FSpriteSequence                             *mSpriteSequence;
	
    int                                         mBlendType;
    
    void										Spawn(FRandomizer *pRand,
                                                      int pParticleCount, int pParticleCountRandom,
                                                      int pWaveCount, int pWaveCountRandom,
                                                      int pWaveInterval, int pWaveIntervalRandom,
                                                      int pParticleStartDelayRandom);
    void										Spawn(FRandomizer *pRand, int pParticleCount, int pParticleCountRandom);
    void										Spawn(int pParticleCount);
    
    
	//void										ApplySpawnSourceBehavior(bool pFromParent, bool pFromParentSource, bool pEdgesOnly, bool pEvenSpread, bool pForceAll);

	void										Finalize(float pX, float pY);
	void										Finalize();
    
    void                                        ApplySpawnSourcePoint();
	void										ApplySpawnSourceRectangle(FRandomizer *pRand, float pWidth, float pHeight);
	void										ApplySpawnSourceCircle(FRandomizer *pRand, float pRadius);
	void										ApplySpawnSourcePolygon(FRandomizer *pRand, FPointList *pPointList);
	void										ApplySpawnSourcePointCloud(FRandomizer *pRand, FPointList *pPointList);


	void										ApplyOffset(FRandomizer *pRand, float pOffsetX, float pOffsetY, float pOffsetXRandom, float pOffsetYRandom);
    inline void                                 ApplyOffset(float pOffsetX, float pOffsetY, float pOffsetXRandom, float pOffsetYRandom);
    
	void										ApplyOffset(float pOffsetX, float pOffsetY);


	void										ApplyDirectionalSpeed(FRandomizer *pRand, float pAngle, float pAngleRandom, float pMagnitude, float pMagnitudeRandom, float pPushAxis, float pPushAxisRandom);
    //inline void                                 ApplyDirectionalSpeed(FRandomizer *pRand, float pAngle, float pAngleRandom, float pMagnitude, float pMagnitudeRandom, float pPushAxis, float pPushAxisRandom){ApplyDirectionalSpeed(&gRand, pAngle, pAngleRandom, pMagnitude, pMagnitudeRandom, pPushAxis, pPushAxisRandom);}


    void										ApplySpeed(float pSpeedX, float pSpeedY, float pSpeedAccel);
    
	void										ApplySpeed(FRandomizer *pRand, float pSpeedX, float pSpeedY, float pSpeedXRandom, float pSpeedYRandom, float pSpeedAccel);

	void										ApplySpeedGravity(float pGravityX, float pGravityY, float pGravityYAdd);
    void										ApplySpeedGravity(float pGravityX, float pGravityY);
    void										ApplySpeedGravity(float pGravityY);
    
	void										ApplySpeedAccel(float pSpeedAccel);


	void										ApplyRotation(FRandomizer *pRand, float pRotation, float pRotationRandom, float pRotationSpeed, float pRotationSpeedRandom, float pRotationSpeedAccel, bool pRotationSpeedRandomNegative);
    
	void										ApplyRotation(FRandomizer *pRand, float pRotation, float pRotationRandom);
	void										ApplyRotationSpeed(FRandomizer *pRand, float pRotationSpeed, float pRotationSpeedRandom, float pRotationSpeedAccel, bool pRotationSpeedRandomNegative);
    
	void										ApplyScale(FRandomizer *pRand, float pScale, float pScaleRandom,
		float pScaleSpeed, float pScaleSpeedRandom, float pScaleSpeedAdd, float pScaleSpeedAccel);
	void										ApplyScale(FRandomizer *pRand, float pScale, float pScaleRandom);
	void										ApplyScaleSpeed(FRandomizer *pRand, float pScaleSpeed, float pScaleSpeedRandom, float pScaleSpeedAdd, float pScaleSpeedAccel);



	void										ApplyColor(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pAlpha, float pRedRand, float pGreenRand, float pBlueRand, float pAlphaRand);
	void										ApplyColor(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pRedRand, float pGreenRand, float pBlueRand);
	void										ApplyColor(float pRed, float pGreen, float pBlue, float pAlpha);
	void										ApplyColor(float pRed, float pGreen, float pBlue);

	void										ApplyColorSpeed(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pAlpha, float pRedRand, float pGreenRand, float pBlueRand, float pAlphaRand);
	void										ApplyColorSpeed(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pRedRand, float pGreenRand, float pBlueRand);
	void										ApplyColorSpeed(float pRed, float pGreen, float pBlue, float pAlpha);
	void										ApplyColorSpeed(float pRed, float pGreen, float pBlue);


	void										ApplyFrameRate(FRandomizer *pRand, float pFrameSpeed, float pFrameSpeedRandom, bool pFrameLoop, bool pFrameStartRandom);

    void										ApplyDelayedAlphaSpeed(int pTime, float pSpeedAdd);
    void										ApplyDelayedScaleSpeed(int pTime, float pSpeedAdd);
    
    
};

#endif 





