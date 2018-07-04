
#include "HeroStego.h"
#include "MainApp.h"

HeroStego::HeroStego()
{
    SetSize(&(gApp->mHeroStegoMockup));
    
    mPartBody = new WiggleBoyPart(&(gApp->mHeroStegoBody), -17.5f, 5.5f);
    
    mPartSpike1 = new WiggleBoyPart(&(gApp->mHeroStegoSpike[0]), mPartBody, 20.5f, -96.0f);
    mPartSpike2 = new WiggleBoyPart(&(gApp->mHeroStegoSpike[1]), mPartBody, 65.5f, -89.5f);
    mPartSpike3 = new WiggleBoyPart(&(gApp->mHeroStegoSpike[2]), mPartBody, 99.5f, -53.5f);
    
    mPartFootFront1 = new WiggleBoyPart(&(gApp->mHeroStegoFootFront[0]), 18.0f, 82.0f);
    mPartBelly = new WiggleBoyPart(&(gApp->mHeroStegoBelly), mPartBody, 3.0f, 33.0f);
    
    
    mPartFootFront2 = new WiggleBoyPart(&(gApp->mHeroStegoFootFront[1]), -32.0f, 70.5f);
    
    
    
    mPartTail = new WiggleBoyPart(&(gApp->mHeroStegoTail), mPartBody, 98.5f, 13.0f);
    
    mPartHeadNub = new WiggleBoyPart(&(gApp->mHeroStegoHeadNub), mPartBody, -2.0f, -17.0f);
    mPartHead = new WiggleBoyPart(&(gApp->mHeroStegoHead), mPartHeadNub, -25.0f, 28.0f);
    
    mPartEye = new WiggleBoyPart(&(gApp->mHeroStegoEye), mPartHead, 0.0f, -30.0f);
    mPartNostril = new WiggleBoyPart(&(gApp->mHeroStegoNostril), mPartHead, -44.0f, 35.0f);
    
    mPartTailSpike1 = new WiggleBoyPart(&(gApp->mHeroStegoTailSpike[0]), mPartTail, 33.5f, -1.0f);
    mPartTailSpike2 = new WiggleBoyPart(&(gApp->mHeroStegoTailSpike[1]), mPartTail, 48.5f, 11.0f);
    mPartTailSpike3 = new WiggleBoyPart(&(gApp->mHeroStegoTailSpike[2]), mPartTail, 45.5f, 3.0f);
    mPartTailSpike4 = new WiggleBoyPart(&(gApp->mHeroStegoTailSpike[3]), mPartTail, 64.5f, 14.0f);
    
    
    
    //mPartList.Add(mPartReference);
    
    mPartList.Add(mPartTailSpike1);
    mPartList.Add(mPartTailSpike2);
    
    mPartList.Add(mPartTail);
    
    mPartList.Add(mPartTailSpike4);
    mPartList.Add(mPartTailSpike3);
    
    
    
    mPartList.Add(mPartSpike3);
    
    mPartList.Add(mPartBody);
    mPartList.Add(mPartBelly);
    
    mPartList.Add(mPartFootFront2);
    mPartList.Add(mPartFootFront1);
    
    mPartList.Add(mPartSpike2);
    mPartList.Add(mPartSpike1);
    

    mPartList.Add(mPartHeadNub);
    mPartList.Add(mPartHead);
    
    mPartList.Add(mPartEye);
    mPartList.Add(mPartNostril);
    
    

    
    mAnimSwaySpikeWobbler1.SetTime(42, 8);
    mAnimSwaySpikeWobbler2.SetTime(42, 8);
    mAnimSwaySpikeWobbler3.SetTime(42, 8);
    
    
    mAnimSwaySpikeWobbler1.SetInterval(-1.3f, 0.75f);
    mAnimSwaySpikeWobbler2.SetInterval(-0.45f, 1.2f);
    mAnimSwaySpikeWobbler3.SetInterval(-0.85f, 1.1f);
    
    
    mAnimTailSpikeTimer.SetTime(30, 45);
    mAnimTailSpikeCount = 0;
    mAnimTailSpikeMode = 0;
    
    
    mAnimNoseTimer.SetTime(40, 32);
    mAnimNoseStepper.SetTimes(22, 13, 14);
    mAnimNoseCount = 0;
    mAnimNoseMode = 0;
    
    
    
    mAnimCraneNeckTimer.SetTime(40, 100);
    mAnimCraneNeckStepper.SetTimes(20, 6, 32);
    mAnimCraneNeckStepper.SetValues(0.0f, 1.0f, 1.0f, 0.0f);
    mAnimCraneNeckCount = 0;
    mAnimCraneNeckMode = 0;
    
    
    
    mAnimSpikeTimer.SetTime(50, 70);
    mAnimSpikeStepper.SetTimes(14, 4, 28);
    mAnimSpikeStepper.SetValues(0.0f, 1.35f, 1.2f, 0.0f);
    mAnimSpikeCount = 0;
    mAnimSpikeMode = 0;
    
    
    
    mAnimTailWagTimer.SetTime(8, 18);
    mAnimTailWagWobbler.SetInterval(-4.2f, 0.85f);
    mAnimTailWagWobbler.SetTime(28, 9);
    mAnimTailWagCount = 0;
    mAnimTailWagMode = 0;
    
    
    
    

    

    mAnimBounceTimer.SetTime(40, 120);
    mAnimBounceTimer.Randomize();
    
    mAnimBounceStepper.SetTimes(16, 16, 22);
    mAnimBounceStepper.SetValues(0.0f, 1.0f, 1.0f, 0.0f);
    
    mAnimBounceCount = 0;
    mAnimBounceMode = 0;
    
    
    
}

HeroStego::~HeroStego()
{
    
}

void HeroStego::Update()
{

    //mPartTail->mRotation -= 0.5f;
    //if(mPartTail->mRotation < -20)mPartTail->mRotation = 20.0f;
    
    //mPartBody->mRotation = Sin(mTestSin3) * 6.0f - 40.0f;
    
    
    
    //mX -= (aDiffX / 400.0f);
    //mY -= (aDiffY / 400.0f);
    
    WiggleBoy::Update();
    
    if(mAnimBounceMode == 0)
    {
        if(mAnimBounceTimer.Tick())
        {
            mAnimBounceStepper.Reset();
            mAnimBounceTimer.Reset();
            mAnimBounceMode = 1;
            mAnimBounceCount = 1 + gRand.Get(2);
        }
    }
    else
    {
        mAnimBounceStepper.Update();
        float aBounce = mAnimBounceStepper.V() * 8.0f * mScale;
        
        if(mAnimBounceStepper.IsFinished())
        {
            mAnimBounceCount--;
            if(mAnimBounceCount <= 0)
            {
                mAnimBounceCount = 0;
                mAnimBounceMode = 0;
            }
            else
            {
                mAnimBounceStepper.Reset();
            }
        }
        
        mPartBody->mCornerOffsetY[0] = (aBounce * 1.6f);
        mPartBody->mCornerOffsetY[1] = (aBounce * 1.6f);
        
        
        mPartSpike1->mOffsetY = aBounce * 0.3f;
        mPartSpike2->mOffsetY = aBounce * 0.4f;
        mPartSpike3->mOffsetY = aBounce * 0.34f;
        
        mPartHeadNub->mRotation = (aBounce * 0.4f);
        mPartHeadNub->mOffsetY = (-aBounce * 0.3f);
        
        mPartFootFront1->mCornerOffsetX[2] = (-aBounce * 0.3f);
        mPartFootFront1->mCornerOffsetY[1] = (aBounce * 0.4f);
        mPartFootFront1->mCornerOffsetY[0] = (aBounce * 0.6f);
        
        mPartFootFront2->mRotation = (aBounce * 0.2f);
    
        mPartFootFront2->mCornerOffsetX[2] = aBounce * 0.2f;
    }

    
    
    
    if(mAnimSpikeMode == 0)
    {
        if(mAnimSpikeTimer.Tick())
        {
            mAnimSpikeStepper.Reset();
            mAnimSpikeTimer.Reset();
            mAnimSpikeMode = 1;
            mAnimSpikeCount = 1;
            
            if(gRand.Get(7) == 4)mAnimSpikeCount += gRand.Get(2);
        }
    }
    else
    {
        
        mAnimSpikeStepper.Update();
        float aAmount = mAnimSpikeStepper.V() * 4.0f * mScale;
        
        if(mAnimSpikeStepper.IsFinished())
        {
            mAnimSpikeCount--;
            if(mAnimSpikeCount <= 0)
            {
                mAnimSpikeCount = 0;
                mAnimSpikeMode = 0;
            }
            else
            {
                mAnimSpikeStepper.Reset();
            }
        }
        
        
        mPartSpike1->mRotation = aAmount;
        mPartSpike2->mRotation = -(aAmount * 0.3f);
        mPartSpike3->mRotation = aAmount;
    }
    

    mAnimSwaySpikeWobbler1.Update();
    mAnimSwaySpikeWobbler2.Update();
    mAnimSwaySpikeWobbler3.Update();
    
    float aSpikeSway1 = mAnimSwaySpikeWobbler1.V() * 0.75f;
    float aSpikeSway2 = mAnimSwaySpikeWobbler2.V() * 0.62f;
    float aSpikeSway3 = mAnimSwaySpikeWobbler3.V() * 0.89f;
    
    mPartSpike1->mPivotOffsetX = aSpikeSway1 * mScale;
    mPartSpike2->mPivotOffsetX = aSpikeSway2 * mScale;
    mPartSpike3->mPivotOffsetX = aSpikeSway3 * mScale;
    
    
    
    
    if(mAnimTailWagMode == 0)
    {
        if(mAnimTailWagTimer.Tick())
        {
            mAnimTailWagWobbler.Reset();
            mAnimTailWagTimer.Reset();
            mAnimTailWagMode = 1;
            mAnimTailWagCount = 1 + gRand.Get(2);
            if(gRand.GetBool())
            {
                mAnimTailWagCount = 1;
            }
        }
    }
    else
    {
        mAnimTailWagWobbler.Update();
        float aAmount = mAnimTailWagWobbler.V() * mScale;
        
        if(mAnimTailWagWobbler.mDidLoop)
        {
            mAnimTailWagCount--;
            if(mAnimTailWagCount <= 0)
            {
                mAnimTailWagCount = 0;
                mAnimTailWagMode = 0;
            }
            else
            {
                mAnimTailWagWobbler.Reset();
            }
        }
        
        mPartTail->mRotation = aAmount;
        mPartTail->mOffsetX = aAmount * 0.4f;
        mPartTail->mOffsetY = (aAmount * 1.15f);
    }
    
    
    
    
    
    
    
    
    
    
    if(mAnimTailSpikeMode == 0)
    {
        if(mAnimTailSpikeTimer.Tick())
        {
            
            mAnimTailSpikeStepper.Reset();
            mAnimTailSpikeTimer.Reset();
            mAnimTailSpikeMode = 1;
            mAnimTailSpikeCount = 1 + gRand.Get(2);
            if(gRand.GetBool())
            {
                mAnimTailSpikeCount = 1;
            }
        }
    }
    else
    {
        
        mAnimTailSpikeStepper.Update();
        float aAmount = mAnimTailSpikeStepper.V() * 5.0f;//mScale * 2.0f;
        
        if(mAnimTailSpikeStepper.IsFinished())
        {
            mAnimTailSpikeCount--;
            if(mAnimTailSpikeCount <= 0)
            {
                mAnimTailSpikeCount = 0;
                mAnimTailSpikeMode = 0;
            }
            else
            {
                mAnimTailSpikeStepper.Reset();
            }
        }
        
        mPartTailSpike1->mRotation = -aAmount * 4.0f;
        mPartTailSpike2->mRotation = aAmount * 3.25f;
        mPartTailSpike3->mRotation = -aAmount * 3.0f;
        mPartTailSpike4->mRotation = aAmount * 4.15f;
    }

    
    
    if(mAnimNoseMode == 0)
    {
        if(mAnimNoseTimer.Tick())
        {
            
            mAnimNoseStepper.Reset();
            mAnimNoseTimer.Reset();
            mAnimNoseMode = 1;
            mAnimNoseCount = 1 + gRand.Get(2);
            if(gRand.GetBool())
            {
                mAnimNoseCount = 1;
            }
        }
    }
    else
    {
        
        mAnimNoseStepper.Update();
        float aAmount = mAnimNoseStepper.V() * mScale * 5.0f;
        
        if(mAnimNoseStepper.IsFinished())
        {
            mAnimNoseCount--;
            if(mAnimNoseCount <= 0)
            {
                mAnimNoseCount = 0;
                mAnimNoseMode = 0;
            }
            else
            {
                mAnimNoseStepper.Reset();
            }
        }
        
        mPartHead->mCornerOffsetX[0] = (aAmount * 0.5f);
        mPartHead->mCornerOffsetY[0] = (aAmount * 1.1f);
        
        mPartHead->mCornerOffsetX[1] = (aAmount * 1.25f);
        mPartHead->mCornerOffsetY[1] = (-aAmount * 0.35f);
        
        mPartHead->mCornerOffsetX[2] = (aAmount * 2.20f);
        mPartHead->mCornerOffsetY[2] = (-aAmount * 0.75f);
        
        
        mPartHead->mCornerOffsetX[3] = (aAmount * 0.85f);
        mPartHead->mCornerOffsetY[3] = (-aAmount * 0.35f);
        
        mPartHead->mOffsetX = (-aAmount * 1.4f);
        mPartHead->mOffsetY = (aAmount * 1.0f);
        
        
        mPartHead->mScale = 1.0f + (aAmount * 0.002f);

        mPartNostril->mRotation = (-aAmount * 0.4f);
        mPartNostril->mOffsetX = (-aAmount * 0.4f);
        mPartNostril->mOffsetY = (-aAmount * 0.3f);
        
        
        mPartBelly->mCornerOffsetX[3] = -aAmount * 0.1f;
        mPartBelly->mCornerOffsetY[2] = aAmount * 1.15f;
    }
    
    
    
    
    
    
    if(mAnimCraneNeckMode == 0)
    {
        if(mAnimCraneNeckTimer.Tick())
        {
            
            mAnimCraneNeckStepper.Reset();
            mAnimCraneNeckTimer.Reset();
            mAnimCraneNeckMode = 1;
            mAnimCraneNeckCount = 1 + gRand.Get(2);
            if(gRand.GetBool())
            {
                mAnimCraneNeckCount = 1;
            }
        }
    }
    else
    {
        mAnimCraneNeckStepper.Update();
        float aAmount = mAnimCraneNeckStepper.V() * mScale;
        
        if(mAnimCraneNeckStepper.IsFinished())
        {
            mAnimCraneNeckCount--;
            if(mAnimCraneNeckCount <= 0)
            {
                mAnimCraneNeckCount = 0;
                mAnimCraneNeckMode = 0;
            }
            else
            {
                mAnimCraneNeckStepper.Reset();
            }
        }
        
        mPartHeadNub->mOffsetX = aAmount * 9.0f;
    }
}
