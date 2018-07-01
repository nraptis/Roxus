#include "FParticleSource.h"
#include "FApp.h"
#include "FParticle.h"

FParticleSource::FParticleSource(FSpriteSequence *pSpriteSequence) : FParticleSource()
{
    mSpriteSequence = pSpriteSequence;
}

FParticleSource::FParticleSource(FSprite *pSprite) : FParticleSource()
{
    SetSprite(pSprite);
}

FParticleSource::FParticleSource()
{
    mSpriteSequence = 0;
    mBlendType = 0;
}

FParticleSource::~FParticleSource()
{

}



void FParticleSource::Update()
{
	FMotionObject::Update();
    
	mParticles.Update();
}

void FParticleSource::Draw()
{
	FMotionObject::Draw();
    
	if(mBlendType != 0)
	{
		Graphics::BlendSetType(mBlendType);
		mParticles.Draw();
		Graphics::BlendSetAlpha();
	}
	else
	{
		mParticles.Draw();
	}
	Graphics::SetColor();
}

void FParticleSource::Clear()
{

}


void FParticleSource::Reset()
{
	//FMotionObject::Reset();
    
	if(true)
	{
		mParticles.KillAll();

	}
}




void FParticleSource::Finalize(float pX, float pY)
{
	mX = pX;
	mY = pY;
	Finalize();
}

void FParticleSource::Finalize()
{
	mParticles.ClearRecentlyAdded();

	EnumList(FParticle, aParticle, mParticles)
	{

		aParticle->mX += mX;
		aParticle->mY += mY;

	}
}


void FParticleSource::Spawn(FRandomizer *pRand, int pParticleCount, int pParticleCountRandom,
                                                  int pWaveCount, int pWaveCountRandom,
                                                  int pWaveInterval, int pWaveIntervalRandom,
                                                  int pParticleStartDelayRandom)
{
    int aSpawnWaveCount = pWaveCount;
    if(aSpawnWaveCount <= 0)aSpawnWaveCount = 1;
    
    if(pWaveCountRandom != 0.0f)aSpawnWaveCount += pRand->Get(pWaveCountRandom);
    
    int aWaveTime = 0;
    int aSpawnParticleCount = 0;
    
    FParticle *aParticle = 0;
    
    for(int aSpawnWaveIndex = 0; aSpawnWaveIndex < aSpawnWaveCount; aSpawnWaveIndex++)
    {
        aSpawnParticleCount = pParticleCount;
        if(pParticleCountRandom != 0)aSpawnParticleCount += pRand->Get(pParticleCountRandom);
        
        for(int aParticleIndex = 0; aParticleIndex < aSpawnParticleCount; aParticleIndex++)
        {
            aParticle = new FParticle();
            mParticles.Add(aParticle);
            
            if(mSpriteSequence)aParticle->SetSpriteSequence(mSpriteSequence);
            if(mSprite)aParticle->SetSprite(mSprite);
            
            if(pParticleStartDelayRandom)aParticle->mTimerDelay = (aWaveTime + pRand->Get(pParticleStartDelayRandom));
            else aParticle->mTimerDelay = aWaveTime;
        }
        
        aWaveTime += pWaveInterval;
        if(pWaveIntervalRandom != 0.0f)aWaveTime += pRand->Get(pWaveIntervalRandom);
    }
    mParticles.ClearRecentlyAdded();
}

void FParticleSource::Spawn(FRandomizer *pRand, int pParticleCount, int pParticleCountRandom)
{
    FParticle *aParticle = 0;

    int aCount = pParticleCount;
    if(aCount <= 0)aCount = 1;
    
    if(pParticleCountRandom != 0)aCount += pRand->Get(pParticleCountRandom);
        
        for(int aParticleIndex = 0; aParticleIndex < aCount; aParticleIndex++)
        {
            aParticle = new FParticle();
            mParticles.Add(aParticle);
            
            if(mSpriteSequence)aParticle->SetSpriteSequence(mSpriteSequence);
            if(mSprite)aParticle->SetSprite(mSprite);
            
        }
    
    mParticles.ClearRecentlyAdded();
}

void FParticleSource::Spawn(int pParticleCount)
{
    FParticle *aParticle = 0;
    int aCount = pParticleCount;
    for(int aParticleIndex = 0; aParticleIndex < aCount; aParticleIndex++)
    {
        aParticle = new FParticle();
        mParticles.Add(aParticle);
        if(mSpriteSequence)aParticle->SetSpriteSequence(mSpriteSequence);
        if(mSprite)aParticle->SetSprite(mSprite);
    }
    mParticles.ClearRecentlyAdded();
}


/*
void FParticleSource::Spawn(FRandomizer *pRand, int pStartTime,
	int pParticleCount, int pParticleCountRandom,
	int pSpawnWaveCount,
	int pSpawnWaveDelay, int pSpawnWaveDelayRandom,
	int pParticleSpawnDelayRandom)
{
	int aSpawnWaveCount = pSpawnWaveCount;
	//if(pSpawnWaveCountRandom)pSpawnWaveCount += pRand->Get(pSpawnWaveCountRandom);

	int aSpawnWaveTime = pStartTime;
	//if(pStartTimeRandom)aSpawnWaveTime += pRand->Get(pStartTimeRandom);

	int aSpawnParticleCount = 0;

	FParticle *aParticle = 0;

	for(int aSpawnWaveIndex = 0; aSpawnWaveIndex < pSpawnWaveCount; aSpawnWaveIndex++)
	{
		aSpawnParticleCount = pParticleCount;
		if(pParticleCountRandom != 0)aSpawnParticleCount += pRand->Get(pParticleCountRandom);

		for(int aParticleIndex = 0; aParticleIndex < aSpawnParticleCount; aParticleIndex++)
		{
			aParticle = new FParticle();
			mParticles.Add(aParticle);

			if(mSpriteSequence)aParticle->SetSpriteSequence(mSpriteSequence);
			if(mSprite)aParticle->SetSprite(mSprite);

			if(pParticleSpawnDelayRandom)aParticle->SetDelay(aSpawnWaveTime + pRand->Get(pParticleSpawnDelayRandom));
			else aParticle->SetDelay(aSpawnWaveTime);
				
		}

		aSpawnWaveTime += pSpawnWaveDelay;
		if(pSpawnWaveDelayRandom)aSpawnWaveTime += pRand->Get(pSpawnWaveDelayRandom);
	}

	mParticles.ClearRecentlyAdded();
}
*/


void FParticleSource::ApplySpawnSourcePoint()
{
    
}

void FParticleSource::ApplySpawnSourceRectangle(FRandomizer *pRand, float pWidth, float pHeight)
{
	float aWidth2 = pWidth / 2.0f;
	float aHeight2 = pHeight / 2.0f;

	EnumList(FParticle, aParticle, mParticles)
	{
		aParticle->mX += pRand->GetFloat(-aWidth2, aWidth2);
		aParticle->mY += pRand->GetFloat(-aHeight2, aHeight2);
	}
}

void FParticleSource::ApplySpawnSourceCircle(FRandomizer *pRand, float pRadius)
{
	float aAngle = 0.0f;

	EnumList(FParticle, aParticle, mParticles)
	{
		aAngle = pRand->GetFloat(360.0f);
		aParticle->mX += pRadius * Sin(aAngle);
		aParticle->mY -= pRadius * Cos(aAngle);
	}
}

void FParticleSource::ApplySpawnSourcePolygon(FRandomizer *pRand, FPointList *pPointList)
{

	if(pPointList)
	{
		if(pPointList->mCount > 1)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				int aIndex1 = pRand->Get(pPointList->mCount);
				int aIndex2 = aIndex1 + 1;
				if(aIndex2 >= pPointList->mCount)aIndex2 = 0.0f;

				float aX1 = pPointList->mX[aIndex1];
				float aY1 = pPointList->mY[aIndex1];

				float aX2 = pPointList->mX[aIndex2];
				float aY2 = pPointList->mY[aIndex2];

				float aPercent = pRand->GetFloat();

				aParticle->mX += (aX1 + (aX2 - aX1) * aPercent);
				aParticle->mY += (aY1 + (aY2 - aY1) * aPercent);

			}
		}
		else if(pPointList->mCount == 1)
		{
			float aX = pPointList->mX[0];
			float aY = pPointList->mY[0];
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mX += aX;
				aParticle->mY -= aY;
			}
		}
	}
}

void FParticleSource::ApplySpawnSourcePointCloud(FRandomizer *pRand, FPointList *pPointList)
{
	if(pPointList)
	{
		if(pPointList->mCount >= 1)
		{
			int aIndex = 0;

			EnumList(FParticle, aParticle, mParticles)
			{
				float aX = pPointList->mX[aIndex];
				float aY = pPointList->mY[aIndex];

				aParticle->mX += aX;
				aParticle->mY += aY;

				aIndex++;
				if(aIndex >= pPointList->mCount)aIndex = 0;
			}
		}
		else if(pPointList->mCount == 1)
		{
			float aX = pPointList->mX[0];
			float aY = pPointList->mY[0];
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mX += aX;
				aParticle->mY -= aY;
			}
		}
	}
}


void FParticleSource::ApplyOffset(float pOffsetX, float pOffsetY, float pOffsetXRandom, float pOffsetYRandom)
{
    ApplyOffset(&gRand, pOffsetX, pOffsetY, pOffsetXRandom, pOffsetYRandom);
}

void FParticleSource::ApplyOffset(FRandomizer *pRand, float pOffsetX, float pOffsetY, float pOffsetXRandom, float pOffsetYRandom)
{
	if(pOffsetXRandom != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mX += pOffsetX + pRand->GetFloat(pOffsetXRandom);
	else EnumList(FParticle, aParticle, mParticles)aParticle->mX += pOffsetX;

	if(pOffsetYRandom != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mY += pOffsetY + pRand->GetFloat(pOffsetYRandom);
	else EnumList(FParticle, aParticle, mParticles)aParticle->mY += pOffsetY;
}

void FParticleSource::ApplyOffset(float pOffsetX, float pOffsetY)
{
	if((pOffsetX != 0.0f) || (pOffsetY != 0.0f))
	{
		EnumList(FParticle, aParticle, mParticles)
		{
			aParticle->mX += pOffsetX;
			aParticle->mY += pOffsetY;
		}
	}
}





void FParticleSource::ApplySpeed(float pSpeedX, float pSpeedY, float pSpeedAccel)
{
    if((pSpeedX != 0.0f) || (pSpeedY != 0.0f))
    {
        EnumList(FParticle, aParticle, mParticles)
        {
            aParticle->mXSpeed += pSpeedX;
            aParticle->mYSpeed += pSpeedY;
        }
    }
    ApplySpeedAccel(pSpeedAccel);
}

void FParticleSource::ApplySpeed(FRandomizer *pRand, float pSpeedX, float pSpeedY, float pSpeedXRandom, float pSpeedYRandom, float pSpeedAccel)
{
    if(pSpeedXRandom != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)aParticle->mXSpeed += pSpeedX + pRand->GetFloat(pSpeedXRandom);
    }
    else if(pSpeedX != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)aParticle->mXSpeed += pSpeedX;
    }
    
    if(pSpeedYRandom != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)aParticle->mYSpeed += pSpeedY + pRand->GetFloat(pSpeedYRandom);
    }
    else if(pSpeedY != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)aParticle->mYSpeed += pSpeedY;
    }
    
    ApplySpeedAccel(pSpeedAccel);
}




void FParticleSource::ApplySpeedGravity(float pGravityX, float pGravityY, float pGravityYAdd)
{
    ApplySpeedGravity(pGravityX, pGravityY);
    
    if(pGravityYAdd != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)
        {
            aParticle->mGravityYAdd += pGravityYAdd;
        }
    }
}

void FParticleSource::ApplySpeedGravity(float pGravityX, float pGravityY)
{
    if((pGravityX != 0.0f) || (pGravityY != 0.0f))
    {
        EnumList(FParticle, aParticle, mParticles)
        {
            aParticle->mGravityX += pGravityX;
            aParticle->mGravityY += pGravityY;
        }
    }
}

void FParticleSource::ApplySpeedGravity(float pGravityY)
{
    if(pGravityY != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)
        {
            aParticle->mGravityY += pGravityY;
        }
    }
}

void FParticleSource::ApplySpeedAccel(float pSpeedAccel)
{
	if(pSpeedAccel != 1.0f)
	{
		EnumList(FParticle, aParticle, mParticles)
		{
			aParticle->mSpeedAccel = pSpeedAccel;
		}
	}
}





void FParticleSource::ApplyDirectionalSpeed(FRandomizer *pRand, float pAngle, float pAngleRandom, float pMagnitude, float pMagnitudeRandom, float pPushAxis, float pPushAxisRandom)
{
	float aAngle = 0.0f;
	float aMagnitude = 0.0f;
	float aPush = 0.0f;

	float aDirX = 0.0f;
	float aDirY = 0.0f;
	EnumList(FParticle, aParticle, mParticles)
	{
		aAngle = pAngle;// +
		if(pAngleRandom != 0.0f)aAngle += pRand->GetFloat(pAngleRandom);

		aPush = pPushAxis;
		if(pPushAxisRandom != 0.0f)aPush += pRand->GetFloat(pPushAxisRandom);

		aMagnitude = pMagnitude;
		if(pMagnitudeRandom != 0.0f)aMagnitude += pRand->GetFloat(pMagnitudeRandom);


		aDirX = Sin(aAngle);
		aDirY = -Cos(aAngle);

		if(aMagnitude != 0.0f)
		{
			aParticle->mXSpeed += aDirX * aMagnitude;
			aParticle->mYSpeed += aDirY * aMagnitude;
		}
		if(aPush != 0.0f)
		{
			aParticle->mX += aDirX * aPush;
			aParticle->mY += aDirY * aPush;
		}

	}
}



void FParticleSource::ApplyColor(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pAlpha, float pRedRand, float pGreenRand, float pBlueRand, float pAlphaRand)
{
	if(pRedRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mRed = (pRed + pRand->GetFloat(pRedRand));
	}
	else if(pRed != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mRed = pRed;
	}


	if(pGreenRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mGreen = (pGreen + pRand->GetFloat(pGreenRand));
	}
	else if(pGreen != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mGreen = pGreen;
	}


	if(pBlueRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mBlue = (pBlue + pRand->GetFloat(pBlueRand));
	}
	else if(pBlue != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mBlue = pBlue;
	}


	if(pAlphaRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mAlpha = (pAlpha + pRand->GetFloat(pAlphaRand));
	}
	else if(pAlpha != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mAlpha = pAlpha;
	}
}

void FParticleSource::ApplyColor(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pRedRand, float pGreenRand, float pBlueRand)
{
	ApplyColor(pRand, pRed, pGreen, pBlue, 0.0f, pRedRand, pGreenRand, pBlueRand, 0.0f);
}

void FParticleSource::ApplyColor(float pRed, float pGreen, float pBlue, float pAlpha)
{
	if(pRed != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mRed = pRed;
	if(pGreen != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mGreen = pGreen;
	if(pBlue != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mBlue = pBlue;
	if(pAlpha != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mAlpha = pAlpha;
}

void FParticleSource::ApplyColor(float pRed, float pGreen, float pBlue)
{
	ApplyColor(pRed, pGreen, pBlue, 0.0f);
}

void FParticleSource::ApplyColorSpeed(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pAlpha, float pRedRand, float pGreenRand, float pBlueRand, float pAlphaRand)
{
	if(pRedRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mRedSpeed = (pRed + pRand->GetFloat(pRedRand));
	}
	else if(pRed != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mRedSpeed = pRed;
	}
	if(pGreenRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mGreenSpeed = (pGreen + pRand->GetFloat(pGreenRand));
	}
	else if(pGreen != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mGreenSpeed = pGreen;
	}
	if(pBlueRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mBlueSpeed = (pBlue + pRand->GetFloat(pBlueRand));
	}
	else if(pBlue != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mBlueSpeed = pBlue;
	}
	if(pAlphaRand != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mAlphaSpeed = (pAlpha + pRand->GetFloat(pAlphaRand));
	}
	else if(pAlpha != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mAlphaSpeed = pAlpha;
	}
}

void FParticleSource::ApplyColorSpeed(FRandomizer *pRand, float pRed, float pGreen, float pBlue, float pRedRand, float pGreenRand, float pBlueRand)
{
	ApplyColorSpeed(pRand, pRed, pGreen, pBlue, 0.0f, pRedRand, pGreenRand, pBlueRand, 0.0f);
}

void FParticleSource::ApplyColorSpeed(float pRed, float pGreen, float pBlue, float pAlpha)
{
	if(pRed != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mRedSpeed = pRed;
	if(pGreen != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mGreenSpeed = pGreen;
	if(pBlue != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mBlueSpeed = pBlue;
	if(pAlpha != 0.0f)EnumList(FParticle, aParticle, mParticles)aParticle->mAlphaSpeed = pAlpha;
}

void FParticleSource::ApplyColorSpeed(float pRed, float pGreen, float pBlue)
{
	ApplyColorSpeed(pRed, pGreen, pBlue, 0.0f);
}


void FParticleSource::ApplyRotation(FRandomizer *pRand, float pRotation, float pRotationRandom, float pRotationSpeed, float pRotationSpeedRandom, float pRotationSpeedAccel, bool pRotationSpeedRandomNegative)
{
	ApplyRotation(pRand, pRotation, pRotationRandom);
	ApplyRotationSpeed(pRand, pRotationSpeed, pRotationSpeedRandom, pRotationSpeedAccel, pRotationSpeedRandomNegative);
}

void FParticleSource::ApplyRotation(FRandomizer *pRand, float pRotation, float pRotationRandom)
{
		if(pRotationRandom != 0.0f)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mRotation += (pRotation + pRand->GetFloat(pRotationRandom));
			}
		}
		else if(pRotation != 0.0f)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mRotation += pRotation;
			}
		}
}

void FParticleSource::ApplyRotationSpeed(FRandomizer *pRand, float pRotationSpeed, float pRotationSpeedRandom,
	float pRotationSpeedAccel, bool pRotationSpeedRandomNegative)
{
	float aSpeed = 0.0f;
	if(pRotationSpeedRandomNegative)
	{
		if(pRotationSpeedRandom != 0.0f)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aSpeed = pRotationSpeed + pRand->GetFloat(pRotationSpeedRandom);
				if(pRand->GetBool())aSpeed = (-aSpeed);
				aParticle->mRotationSpeed += aSpeed;
			}
		}
		else
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aSpeed = pRotationSpeed;
				if(pRand->GetBool())aSpeed = (-aSpeed);
				aParticle->mRotationSpeed += aSpeed;
			}
		}
	}
	else
	{
		if(pRotationSpeedRandom != 0.0f)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aSpeed = pRotationSpeed + pRand->GetFloat(pRotationSpeedRandom);
				aParticle->mRotationSpeed += aSpeed;
			}
		}
		else if(pRotationSpeed != 0.0f)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mRotationSpeed += pRotationSpeed;
			}
		}
		
	}
	if(pRotationSpeedAccel != 1.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mRotationAccel = pRotationSpeedAccel;
	}
}



void FParticleSource::ApplyScale(FRandomizer *pRand, float pScale, float pScaleRandom,
	float pScaleSpeed, float pScaleSpeedRandom, float pScaleSpeedAdd, float pScaleSpeedAccel)
{
	ApplyScale(pRand, pScale, pScaleRandom);
	ApplyScaleSpeed(pRand, pScaleSpeed, pScaleSpeedRandom, pScaleSpeedAdd, pScaleSpeedAccel);
}

void FParticleSource::ApplyScale(FRandomizer *pRand, float pScale, float pScaleRandom)
{
	float aScale = 0.0f;

		if(pScaleRandom != 0.0f)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aScale = pScale + pRand->GetFloat(pScaleRandom);
				aParticle->mScale = aScale;
			}
		}
		else
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mScale = pScale;
			}
		}
}
										


void FParticleSource::ApplyScaleSpeed(FRandomizer *pRand, float pScaleSpeed, float pScaleSpeedRandom, float pScaleSpeedAdd, float pScaleSpeedAccel)
{
	float aSpeed = 0.0f;
	
		if(pScaleSpeedRandom != 0.0f)
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aSpeed = pScaleSpeed + pRand->GetFloat(pScaleSpeedRandom);
				aParticle->mScaleSpeed += aSpeed;
			}
		}
		else
		{
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mScaleSpeed += pScaleSpeed;
			}
		}

		if((pScaleSpeedAccel != 1.0f) || (pScaleSpeedAdd != 0.0f))
	{
			EnumList(FParticle, aParticle, mParticles)
			{
				aParticle->mScaleSpeedAdd += pScaleSpeedAdd;
				aParticle->mScaleAccel = pScaleSpeedAccel;
			}
	}
}


void FParticleSource::ApplyFrameRate(FRandomizer *pRand, float pFrameSpeed, float pFrameSpeedRandom, bool pFrameLoop, bool pFrameStartRandom)
{
	if(pFrameSpeedRandom != 0.0f)
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mFrameSpeed = pFrameSpeed + pRand->GetFloat(pFrameSpeedRandom);
	}
	else
	{
		EnumList(FParticle, aParticle, mParticles)aParticle->mFrameSpeed = pFrameSpeed;
	}
	EnumList(FParticle, aParticle, mParticles)
	{
		aParticle->mFrameLoop = pFrameLoop;
	}

	if((pFrameStartRandom == true) && (mSpriteSequence != 0))
	{
		float aMaxFrame = mSpriteSequence->GetMaxFrame();
		EnumList(FParticle, aParticle, mParticles)
		{
			aParticle->mFrame += pRand->GetFloat(aMaxFrame);
		}
	}
}


void FParticleSource::ApplyDelayedAlphaSpeed(int pTime, float pSpeedAdd)
{
    if(pSpeedAdd != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)
        {
            aParticle->mDelayAlphaSpeedAddTime = pTime;
            aParticle->mDelayAlphaSpeedAdd = pSpeedAdd;
        }
    }
}

void FParticleSource::ApplyDelayedScaleSpeed(int pTime, float pSpeedAdd)
{
    if(pSpeedAdd != 0.0f)
    {
        EnumList(FParticle, aParticle, mParticles)
        {
            aParticle->mDelayScaleSpeedAddTime = pTime;
            aParticle->mDelayScaleSpeedAdd = pSpeedAdd;
            
        }
    }
}


