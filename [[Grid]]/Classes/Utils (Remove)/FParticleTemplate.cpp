//
//  FParticleTemplate.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/8/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FParticleTemplate.h"
#include "FMotionPath.h"
#include "FParticle.h"

#include "core_graphics.h"
#include "core_includes.h"



FParticleTemplate::FParticleTemplate()
{
    //mSpawnSourcePolygonList.mUnique = true;
    //mSpawnSourcePointCloudList.mUnique = true;
    
    mSpawnSourceParent = 0;
    mSeed = 60;
    mRand = new FRandomizer();
    Seed();
    
    mTimeTrialX = 0.0f;
    mTimeTrialY = 0.0f;
    
    mSprite = 0;
    mSpriteSequence = 0;
    
    mSpawnFrameSpeed = 1.0f;
    mSpawnFrameSpeedRandom = 0.0f;
    mSpawnFrameLoop = true;
    mSpawnFrameStartRandom = false;
    
    mSpawnParticleCount = 1;
    mSpawnParticleCountRandom = 0;
    
    mSpawnWaveCount = 1;
    mSpawnWaveCountRandom = 0;
    
    mSpawnWaveInterval = 8;
    mSpawnWaveIntervalRandom = 0;
    
    mSpawnParticleStartDelayRandom = 0;
    
    
    
    
    mSpawnOffsetX = 0.0f;
    mSpawnOffsetY = 0.0f;
    mSpawnOffsetXRandom = 0.0f;
    mSpawnOffsetYRandom = 0.0f;
    
    mSpawnSourceType = SPAWN_SOURCE_POINT;
    
    
    mSpawnSourceRadius = 160.0f;
    mSpawnSourceWidth = 300.0f;
    mSpawnSourceHeight = 200.0f;
    
    
    
    
    
    mSpawnDirectionalAngle = 0.0f;
    mSpawnDirectionalAngleRandom = 0.0f;
    mSpawnDirectionalMagnitude = 0.0f;
    mSpawnDirectionalMagnitudeRandom = 0.0f;
    mSpawnDirectionalPush = 0.0f;
    mSpawnDirectionalPushRandom = 0.0f;
    
    
    
    
    
    
    mSpawnSpeedX = 0.0f;
    mSpawnSpeedXRandom = 0.0f;
    mSpawnSpeedY = 0.0f;
    mSpawnSpeedYRandom = 0.0f;
    mSpawnSpeedAccel = 1.0f;
    mSpawnSpeedGravityX = 0.0f;
    mSpawnSpeedGravityY = 0.0f;
    mSpawnSpeedGravityYAdd = 0.0f;
    
    
    
    
    mSpawnColor = FColor(1.0f, 1.0f, 1.0f, 1.0f);
    mSpawnColorExtra = FColor(0.0f, 0.0f, 0.0f, 0.01f);
    mSpawnColorRandom = FColor(0.0f, 0.0f, 0.0f, 0.0f);
    mSpawnColorSpeed = FColor(0.0f, 0.0f, 0.0f, 0.01f);
    mSpawnColorSpeedRandom = FColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    
    mSpawnDelayAlphaSpeedAddTime = 0;
    mSpawnDelayAlphaSpeedAdd = 0.0f;
    mSpawnDelayScaleSpeedAddTime = 0;
    mSpawnDelayScaleSpeedAdd = 0.0f;
    
    mSpawnScale = 1.0f;
    mSpawnScaleRandom = 0.0f;
    mSpawnScaleSpeed = 0.0f;
    mSpawnScaleSpeedAdd = 0.0f;
    mSpawnScaleSpeedRandom = 0.0f;
    mSpawnScaleSpeedAccel = 1.0f;
    
    mSpawnRotation = 0.0f;
    mSpawnRotationRandom = 0.0f;
    
    mSpawnRotationSpeed = 0.0f;
    mSpawnRotationSpeedRandom = 0.0f;
    mSpawnRotationSpeedAccel = 1.0f;
    mSpawnRotationSpeedNegativeRandom = false;
    
    Reset();
}

FParticleTemplate::~FParticleTemplate()
{
    Clear();
}

void FParticleTemplate::Reset()
{
    
    //mSimPulseTimer.SetTime(mSpawnPulseTime, mSpawnPulseTimeRandom);
    //mSimPulseTimer.SetSleep(0);
    //mSimPulseTimer.Reset();
}

void FParticleTemplate::Clear()
{
    FreeList(FMotionPathTemplate, mSpawnSourcePolygonList);
    FreeList(FMotionPathTemplate, mSpawnSourcePointCloudList);
}

void FParticleTemplate::TimeTrialReset()
{
    
}

void FParticleTemplate::TimeTrialPrepareUpdate()
{
    /*
    if(mSpawnSourceType == SPAWN_SOURCE_POLYGON)
    {
        mSpawnPointList.Reset();
        
        EnumList(FMotionPathTemplate, aPath, mSpawnSourcePolygonList)
        {
            FMotionPathTemplate *aPathAbs = aPath->GetPathAbs();
            
            EnumList(FMotionPathTemplateNode, aPathNode, aPathAbs->mList)
            {
                mSpawnPointList.Add(aPathNode->mX, aPathNode->mY);
            }
        }
        mSource.GeometrySetPolygon(&mSpawnPointList);
    }
    else if(mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
    {
        mSpawnPointList.Reset();
        EnumList(FMotionPathTemplate, aPath, mSpawnSourcePointCloudList)
        {
            FMotionPathTemplate *aPathAbs = aPath->GetPathAbs();
            
            EnumList(FMotionPathTemplateNode, aPathNode, aPathAbs->mList)
            {
                mSpawnPointList.Add(aPathNode->mX, aPathNode->mY);
            }
        }
        mSource.GeometrySetPointCloud(&mSpawnPointList);
    }
    else if(mSpawnSourceType == SPAWN_SOURCE_CIRCLE)
    {
        mSource.GeometrySetCircle(mSpawnSourceRadius);
    }
    else if(mSpawnSourceType == SPAWN_SOURCE_RECT)
    {
        mSource.GeometrySetRectangle(mSpawnSourceWidth, mSpawnSourceHeight);
    }
    else
    {
        mSource.GeometrySetUnknown();
    }
     
    */
}

void FParticleTemplate::TimeTrialUpdate(int pTime)
{
    mTimeTrialPreviousTick = mTimeTrialTick;
    mTimeTrialTick = pTime;
    
    mSource.mX = mTimeTrialX;
    mSource.mY = mTimeTrialY;
    
    
    //if(pTime == 0)
    //{
    
    mRand->Seed(mSeed);
    
    mSource.Reset();
    
    mSource.Spawn(mRand, mSpawnParticleCount, mSpawnParticleCountRandom,
                  mSpawnWaveCount, mSpawnWaveCountRandom, mSpawnWaveInterval, mSpawnWaveIntervalRandom,
                  mSpawnParticleStartDelayRandom);
    
    
    FMotionObject *aSource = &(mSource);
    if(mSpawnSourceParent != 0)aSource = &(mSpawnSourceParent->mSource);
    
    /*
    FMotionObjectModifierGeometry *aGeo = ((FMotionObjectModifierGeometry *)aSource->GeometryGetModifier());
    if(aGeo)
    {
        if(aGeo->mIndexType == MOT_GEO_TYPE_POLYGON)
        {
            FMotionObjectModifierGeometryPolygon *aNode = (FMotionObjectModifierGeometryPolygon *)aGeo;
            mSource.ApplySpawnSourcePolygon(mRand, &(aNode->mPointList));
        }
        else if(aGeo->mIndexType == MOT_GEO_TYPE_POINT_CLOUD)
        {
            FMotionObjectModifierGeometryPointCloud *aNode = (FMotionObjectModifierGeometryPointCloud*)aGeo;
            mSource.ApplySpawnSourcePointCloud(mRand, &(aNode->mPointList));
        }
        else if(aGeo->mIndexType == MOT_GEO_TYPE_CIRCLE)
        {
            FMotionObjectModifierGeometryCircle *aNode = (FMotionObjectModifierGeometryCircle *)aGeo;
            mSource.ApplySpawnSourceCircle(mRand, aNode->mRadius);
        }
        else if(aGeo->mIndexType == MOT_GEO_TYPE_RECT)
        {
            FMotionObjectModifierGeometryRectangle *aNode = (FMotionObjectModifierGeometryRectangle *)aGeo;
            mSource.ApplySpawnSourceRectangle(mRand, aNode->mWidth, aNode->mHeight);
        }
    }
    */
    
    
    
    mSource.ApplyColor(mRand, mSpawnColor.mRed + mSpawnColorExtra.mRed,
                       mSpawnColor.mGreen + mSpawnColorExtra.mGreen,
                       mSpawnColor.mBlue + mSpawnColorExtra.mBlue,
                       mSpawnColor.mAlpha + mSpawnColorExtra.mAlpha,
                       mSpawnColorRandom.mRed, mSpawnColorRandom.mGreen, mSpawnColorRandom.mBlue, mSpawnColorRandom.mAlpha);
    mSource.ApplyColorSpeed(mRand, mSpawnColorSpeed.mRed, mSpawnColorSpeed.mGreen, mSpawnColorSpeed.mBlue, mSpawnColorSpeed.mAlpha,
                            mSpawnColorSpeedRandom.mRed, mSpawnColorSpeedRandom.mGreen, mSpawnColorSpeedRandom.mBlue, mSpawnColorSpeedRandom.mAlpha);
    mSource.ApplyOffset(mRand, mSpawnOffsetX, mSpawnOffsetY, mSpawnOffsetXRandom, mSpawnOffsetYRandom);
    mSource.ApplyDirectionalSpeed(mRand, mSpawnDirectionalAngle, mSpawnDirectionalAngleRandom, mSpawnDirectionalMagnitude, mSpawnDirectionalMagnitudeRandom,
                                  mSpawnDirectionalPush, mSpawnDirectionalPushRandom);
    
    mSource.ApplySpeed(mRand, mSpawnSpeedX, mSpawnSpeedY, mSpawnSpeedXRandom, mSpawnSpeedYRandom, mSpawnSpeedAccel);
    
    mSource.ApplySpeedGravity(mSpawnSpeedGravityX, mSpawnSpeedGravityY, mSpawnSpeedGravityYAdd);
    
    mSource.ApplyRotation(mRand, mSpawnRotation, mSpawnRotationRandom,
                          mSpawnRotationSpeed, mSpawnRotationSpeedRandom, mSpawnRotationSpeedAccel, mSpawnRotationSpeedNegativeRandom);
    
    mSource.ApplyScale(mRand, mSpawnScale, mSpawnScaleRandom, mSpawnScaleSpeed, mSpawnScaleSpeedRandom, mSpawnScaleSpeedAdd, mSpawnScaleSpeedAccel);
    
    mSource.ApplyFrameRate(mRand, mSpawnFrameSpeed, mSpawnFrameSpeedRandom, mSpawnFrameLoop, mSpawnFrameStartRandom);
    
    mSource.ApplyDelayedAlphaSpeed(mSpawnDelayAlphaSpeedAddTime, mSpawnDelayAlphaSpeedAdd);
    mSource.ApplyDelayedScaleSpeed(mSpawnDelayScaleSpeedAddTime, mSpawnDelayScaleSpeedAdd);
    
    mSource.Finalize(aSource->mX, aSource->mY);
    
    
    
    //mSource.Update(pTime);
    
    
}

void FParticleTemplate::TimeTrialSetPos(float pX, float pY)
{
    mTimeTrialX = pX;
    mTimeTrialY = pY;
}

void FParticleTemplate::TimeTrialDraw()
{
    if(mSpriteSequence)
    {
        mSource.mSpriteSequence = mSpriteSequence;
        mSource.mSprite = 0;
    }
    else if(mSprite)
    {
        mSource.mSpriteSequence = 0;
        mSource.mSprite = mSprite;
    }
    mSource.Draw();
}

void FParticleTemplate::Seed(int pSeed)
{
    mSeed = pSeed;
    mRand->Seed(pSeed);
}

void FParticleTemplate::Seed()
{
    Seed(gRand.Get(2000));
}




void FParticleTemplate::SetSpawnSource(int pSourceType)
{
    mSpawnSourceType = pSourceType;
}

FString FParticleTemplate::ExportString(const char *pName)
{
    FString aReturn = "";
    FColor aColor = mSpawnColor;
    aColor += mSpawnColorExtra;
    
    FList aParamList;
    
    
    FString aSpawnString = FString("Spawn(&gRand, ") +
    FString(mSpawnParticleCount) + FString(", ") + FString(mSpawnParticleCountRandom) + FString(", ") +
    FString(mSpawnWaveCount) + FString(", ") + FString(mSpawnWaveCountRandom) + FString(", ") +
    FString(mSpawnWaveInterval) + FString(", ") + FString(mSpawnWaveIntervalRandom) + FString(", ") +
    FString(mSpawnParticleStartDelayRandom) + FString(");");
    
    aParamList += new FString(aSpawnString.c());
    aSpawnString.Free();
    
    
    
    

    
    
    if((mSpawnOffsetX != 0.0f) || (mSpawnOffsetY != 0.0f) || (mSpawnOffsetXRandom != 0.0f) || (mSpawnOffsetYRandom != 0.0f))
    {
        FString aBaseOffsetString = FString("ApplyOffset(&gRand, ") + FString(mSpawnOffsetX) + FString(", ") + FString(mSpawnOffsetY);
        aBaseOffsetString += FString(", ") + FString(mSpawnOffsetXRandom) + FString(", ") + FString(mSpawnOffsetYRandom);
        
        aBaseOffsetString += FString(");");
        aParamList += new FString(aBaseOffsetString.c());
    }
    
    if((aColor.mRed != 1.0f) || (aColor.mGreen != 1.0f) || (aColor.mBlue != 1.0f) || (aColor.mAlpha != 1.0f)
        || (mSpawnColorRandom.mRed != 0.0f) || (mSpawnColorRandom.mGreen != 0.0f) || (mSpawnColorRandom.mBlue != 0.0f) || (mSpawnColorRandom.mAlpha != 0.0f))
    {
        bool aExportRandom = ((mSpawnColorRandom.mRed != 0.0f) || (mSpawnColorRandom.mGreen != 0.0f) || (mSpawnColorRandom.mBlue != 0.0f) || (mSpawnColorRandom.mAlpha != 0.0f));
        
        FString aColorString = FString("ApplyColor(");
        if(aExportRandom)aColorString += "&gRand, ";
        aColorString += FString(aColor.mRed) + FString(", ") + FString(aColor.mGreen) + FString(", ") + FString(aColor.mBlue);
        aColorString += FString(FString(", ") + FString(aColor.mAlpha));
        
        if(aExportRandom)
        {
            aColorString += FString(", ") + FString(mSpawnColorRandom.mRed) + FString(", ") + FString(mSpawnColorRandom.mGreen) + FString(", ") + FString(mSpawnColorRandom.mBlue);
            aColorString += FString(", ") + FString(mSpawnColorRandom.mAlpha);
        }
        
        aColorString += FString(");");
        aParamList += new FString(aColorString.c());
    }
    
    if((mSpawnColorSpeedRandom.mRed != 0.0f) || (mSpawnColorSpeedRandom.mGreen != 0.0f) || (mSpawnColorSpeedRandom.mBlue != 0.0f) || (mSpawnColorSpeedRandom.mAlpha != 0.0f)
        || (mSpawnColorSpeed.mRed != 0.0f) || (mSpawnColorSpeed.mGreen != 0.0f) || (mSpawnColorSpeed.mBlue != 0.0f) || (mSpawnColorSpeed.mAlpha != 0.0f))
    {
        bool aExportRandom = ((mSpawnColorSpeedRandom.mRed != 0.0f) || (mSpawnColorSpeedRandom.mGreen != 0.0f) || (mSpawnColorSpeedRandom.mBlue != 0.0f) || (mSpawnColorSpeedRandom.mAlpha != 0.0f));
        
        
        FString aColorString = FString("ApplyColorSpeed(");
        
        
        if(aExportRandom)aColorString += "&gRand, ";
        aColorString += FString(mSpawnColorSpeed.mRed) + FString(", ") + FString(mSpawnColorSpeed.mGreen) + FString(", ") + FString(mSpawnColorSpeed.mBlue);
        
        
        aColorString += FString(", ") + FString(mSpawnColorSpeed.mAlpha);
        
        if(aExportRandom)
        {
            aColorString += FString(", ") + FString(mSpawnColorSpeedRandom.mRed) + FString(", ") + FString(mSpawnColorSpeedRandom.mGreen) + FString(", ") + FString(mSpawnColorSpeedRandom.mBlue);
            aColorString += FString(", ") + FString(mSpawnColorSpeedRandom.mAlpha);
        }
        
        aColorString += FString(");");
        aParamList += new FString(aColorString.c());
    }
    
    if((mSpawnScale != 1.0f) || (mSpawnScaleRandom != 0.0f) || (mSpawnScaleSpeed != 0.0f) || (mSpawnScaleSpeedAccel != 1.0f))
    {
        
        FString aScaleString = FString("ApplyScale(&gRand, ") + FString(mSpawnScale) + FString(", ") + FString(mSpawnScaleRandom) + FString(", ") +
        FString(mSpawnScaleSpeed) + FString(", ") + FString(mSpawnScaleSpeedRandom) + FString(", ") + FString(mSpawnScaleSpeedAdd) + FString(", ") + FString(mSpawnScaleSpeedAccel) + FString(");");
        
        aParamList += new FString(aScaleString.c());
    }
    
    
    if((mSpawnFrameSpeed != 1.0f) || (mSpawnFrameSpeedRandom != 0.0f) || (mSpawnFrameStartRandom == true) || (mSpawnFrameLoop == false))
    {
        FString aFrameString = FString("ApplyFrameRate(&gRand, ") + FString(mSpawnFrameSpeed) + FString(", ") + FString(mSpawnFrameSpeedRandom) + FString(", ") +
        FString(mSpawnFrameLoop) + FString(", ") + FString(mSpawnFrameStartRandom) + FString(");");
        aParamList += new FString(aFrameString.c());
    }
    
    if((mSpawnRotation != 0) || (mSpawnRotationRandom != 0.0f) || (mSpawnRotationRandom != 360.0f))
    {
        FString aRotString = FString("ApplyRotation(&gRand, ") + FString(mSpawnRotation) + FString(", ") + FString(mSpawnRotationRandom) + FString(", ") +
        FString(mSpawnRotationSpeed);
        aRotString += FString(", ") + FString(mSpawnRotationSpeedRandom) + FString(", ") + FString(mSpawnRotationSpeedAccel) + FString(", ") +
        FString(mSpawnRotationSpeedNegativeRandom) + FString(");");
        aParamList += new FString(aRotString.c());
    }
    
    if((mSpawnSpeedX != 0.0f) || (mSpawnSpeedY != 0.0f) || (mSpawnSpeedXRandom != 0.0f)
       || (mSpawnSpeedYRandom != 0.0f) || (mSpawnSpeedAccel != 1.0f))
    {
        bool aExportRandom = ((mSpawnSpeedXRandom != 0.0f) || (mSpawnSpeedYRandom != 0.0f));
        FString aSpeedString = FString("ApplySpeed(");
        if(aExportRandom)aSpeedString += "&gRand, ";
        aSpeedString += FString(mSpawnSpeedX) + FString(", ") + FString(mSpawnSpeedY);
        if(aExportRandom)
        {
            aSpeedString += FString(", ") + FString(mSpawnSpeedXRandom) + FString(", ") + FString(mSpawnSpeedYRandom);
        }
        aSpeedString += FString(", ") + FString(mSpawnSpeedAccel);
        aSpeedString += FString(");");
        aParamList += new FString(aSpeedString.c());
    }
    
    
    
    if((mSpawnSpeedGravityX != 0.0f) || (mSpawnSpeedGravityY != 0.0f) || (mSpawnSpeedGravityYAdd != 0.0f))
    {
        FString aGravityString = FString("ApplySpeedGravity(");
        if((mSpawnSpeedGravityX == 0.0f) && (mSpawnSpeedGravityYAdd == 0.0f))
        {
            aGravityString += FString(mSpawnSpeedGravityY);
        }
        else
        {
            aGravityString += FString(mSpawnSpeedGravityX) + FString(", ") + FString(mSpawnSpeedGravityY);
            if(mSpawnSpeedGravityYAdd != 0.0f)aGravityString += FString(", ") + FString(mSpawnSpeedGravityYAdd);
        }
        aGravityString += FString(");");
        aParamList += new FString(aGravityString.c());
    }
    
    
    
    if((mSpawnDirectionalMagnitude != 0.0f) || (mSpawnDirectionalMagnitudeRandom != 0.0f) || (mSpawnDirectionalPushRandom != 0.0f) || (mSpawnDirectionalPush != 0.0f) || (mSpawnDirectionalAngle != 0.0f) || (mSpawnDirectionalAngleRandom != 0.0f))
    {
        
        FString aDirSpeedString = FString("ApplyDirectionalSpeed(&gRand, ") + FString(mSpawnDirectionalAngle) + FString(", ") + FString(mSpawnDirectionalAngleRandom) + FString(", ") +
        FString(mSpawnDirectionalMagnitude) + FString(", ") + FString(mSpawnDirectionalMagnitudeRandom) +
        FString(", ") + FString(mSpawnDirectionalPush) + FString(", ") + FString(mSpawnDirectionalPushRandom) + FString(");");
        
        aParamList += new FString(aDirSpeedString.c());
    }
    
    
    if(mSpawnDelayAlphaSpeedAdd != 0.0f)
    {
        FString aDelayString = FString("ApplyDelayedAlphaSpeed(") + FString(mSpawnDelayAlphaSpeedAddTime) + FString(", ") + FString(mSpawnDelayAlphaSpeedAdd) + FString(");\n");
        aParamList += new FString(aDelayString.c());
    }
    
    if(mSpawnDelayScaleSpeedAdd != 0.0f)
    {
        FString aDelayString = FString("ApplyDelayedScaleSpeed(") + FString(mSpawnDelayScaleSpeedAddTime) + FString(", ") + FString(mSpawnDelayScaleSpeedAdd) + FString(");\n");
        aParamList += new FString(aDelayString.c());
    }
    
    FString aName = FString(pName);
    
    EnumList(FString, aString, aParamList)
    {
        if(aName.mLength > 0)
        {
            aReturn += FString(pName);
            aReturn += "->";
        }
        aReturn += aString->c();
        aReturn += "\n";
    }
    
    FreeList(FString, aParamList);
    return aReturn;
}


FXMLTag	*FParticleTemplate::SaveXML()
{
    FXMLTag *aTag = new FXMLTag("particle_template");
    FXMLTag *aMetaTag = new FXMLTag("meta");
    *aTag += aMetaTag;
    
    if(mSpriteSequence != 0)
    {
        aMetaTag->AddParam("sprite_sequence_path", FString(mSpriteSequence->mFilePrefix).c());
    }
    
    if(mSprite != 0)
    {
        aMetaTag->AddParam("sprite_path", FString(mSprite->mFileName).c());
    }
    
    
    FXMLTag *aSourceTag = new FXMLTag("source");
    *aTag += aSourceTag;
    aSourceTag->AddParamInt("type", mSpawnSourceType);
    aSourceTag->AddParamSafeFloat("rect_width", mSpawnSourceWidth);
    aSourceTag->AddParamSafeFloat("rect_height", mSpawnSourceHeight);
    aSourceTag->AddParamSafeFloat("radius", mSpawnSourceRadius);
    
    aSourceTag->AddParamInt("count", mSpawnParticleCount);
    aSourceTag->AddParamInt("count_r", mSpawnParticleCountRandom);
    aSourceTag->AddParamInt("wave_count", mSpawnWaveCount);
    aSourceTag->AddParamInt("wave_count_r", mSpawnWaveCountRandom);
    aSourceTag->AddParamInt("wave_interval", mSpawnWaveInterval);
    aSourceTag->AddParamInt("wave_interval_r", mSpawnWaveIntervalRandom);
    aSourceTag->AddParamInt("start_delay_r", mSpawnParticleStartDelayRandom);
    
    FXMLTag *aPosTag = new FXMLTag("position");
    *aTag += aPosTag;
    aPosTag->AddParamSafeFloat("offset_x", mSpawnOffsetX);
    aPosTag->AddParamSafeFloat("offset_y", mSpawnOffsetY);
    aPosTag->AddParamSafeFloat("offset_x_r", mSpawnOffsetXRandom);
    aPosTag->AddParamSafeFloat("offset_y_r", mSpawnOffsetYRandom);
    
    FXMLTag *aFrameTag = new FXMLTag("frames");
    *aTag += aFrameTag;
    aFrameTag->AddParamSafeFloat("frame_speed", mSpawnFrameSpeed);
    aFrameTag->AddParamSafeFloat("frame_speed_r", mSpawnFrameSpeedRandom);
    aFrameTag->AddParamBool("frame_start_random", mSpawnFrameStartRandom);
    aFrameTag->AddParamBool("frame_loop", mSpawnFrameLoop);
    
    FXMLTag *aScaleTag = new FXMLTag("scale");
    *aTag += aScaleTag;
    aScaleTag->AddParamSafeFloat("scale", mSpawnScale);
    aScaleTag->AddParamSafeFloat("scale_r", mSpawnScaleRandom);
    aScaleTag->AddParamSafeFloat("speed", mSpawnScaleSpeed);
    aScaleTag->AddParamSafeFloat("speed_add", mSpawnScaleSpeedAdd);
    aScaleTag->AddParamSafeFloat("speed_r", mSpawnScaleSpeedRandom);
    aScaleTag->AddParamSafeFloat("accel", mSpawnScaleSpeedAccel);
    
    
    FXMLTag *aRotationTag = new FXMLTag("rotation");
    *aTag += aRotationTag;
    aRotationTag->AddParamBool("speed_inv_r", mSpawnRotationSpeedNegativeRandom);
    aRotationTag->AddParamSafeFloat("rotation", mSpawnRotation);
    aRotationTag->AddParamSafeFloat("rotation_r", mSpawnRotationRandom);
    aRotationTag->AddParamSafeFloat("speed", mSpawnRotationSpeed);
    aRotationTag->AddParamSafeFloat("speed_r", mSpawnRotationSpeedRandom);
    aRotationTag->AddParamSafeFloat("accel", mSpawnRotationSpeedAccel);
    
    FXMLTag *aSpeedTag = new FXMLTag("speed");
    *aTag += aSpeedTag;
    aSpeedTag->AddParamSafeFloat("x", mSpawnSpeedX);
    aSpeedTag->AddParamSafeFloat("y", mSpawnSpeedY);
    aSpeedTag->AddParamSafeFloat("x_r", mSpawnSpeedXRandom);
    aSpeedTag->AddParamSafeFloat("y_r", mSpawnSpeedYRandom);
    aSpeedTag->AddParamSafeFloat("accel", mSpawnSpeedAccel);
    aSpeedTag->AddParamSafeFloat("gravity_x", mSpawnSpeedGravityX);
    aSpeedTag->AddParamSafeFloat("gravity_y", mSpawnSpeedGravityY);
    aSpeedTag->AddParamSafeFloat("gravity_y_add", mSpawnSpeedGravityYAdd);
    
    
    FXMLTag *aDirectionalSpeedTag = new FXMLTag("directional_speed");
    *aTag += aDirectionalSpeedTag;
    aDirectionalSpeedTag->AddParamSafeFloat("angle", mSpawnDirectionalAngle);
    aDirectionalSpeedTag->AddParamSafeFloat("angle_r", mSpawnDirectionalAngleRandom);
    aDirectionalSpeedTag->AddParamSafeFloat("magnitude", mSpawnDirectionalMagnitude);
    aDirectionalSpeedTag->AddParamSafeFloat("magnitude_r", mSpawnDirectionalMagnitudeRandom);
    aDirectionalSpeedTag->AddParamSafeFloat("push", mSpawnDirectionalPush);
    aDirectionalSpeedTag->AddParamSafeFloat("push_r", mSpawnDirectionalPushRandom);
    
    FXMLTag *aDelayTag = new FXMLTag("delayed_triggers");
    *aTag += aDelayTag;
    aDelayTag->AddParamInt("alpha_speed_add_time", mSpawnDelayAlphaSpeedAddTime);
    aDelayTag->AddParamSafeFloat("alpha_speed_add", mSpawnDelayAlphaSpeedAdd);
    aDelayTag->AddParamInt("scale_speed_add_time", mSpawnDelayScaleSpeedAddTime);
    aDelayTag->AddParamSafeFloat("scale_speed_add", mSpawnDelayScaleSpeedAdd);
    
    
    FXMLTag *aColorTag = new FXMLTag("colors");
    *aTag += aColorTag;
    aColorTag->AddTagSafeColor("base", &mSpawnColor);
    aColorTag->AddTagSafeColor("base_extra", &mSpawnColorExtra);
    aColorTag->AddTagSafeColor("base_r", &mSpawnColorRandom);
    aColorTag->AddTagSafeColor("speed", &mSpawnColorSpeed);
    aColorTag->AddTagSafeColor("speed_r", &mSpawnColorSpeedRandom);
    
    
    
    
    
    FXMLTag *aPolygonTag = new FXMLTag("polygons");
    *aTag += aPolygonTag;
    aPolygonTag->AddParamInt("count", mSpawnSourcePolygonList.mCount);
    for(int i = 0; i<mSpawnSourcePolygonList.mCount; i++)
    {
        FMotionPathTemplate *aPath = (FMotionPathTemplate*)(mSpawnSourcePolygonList.Fetch(i));
        FMotionPathTemplate *aPathAbs = aPath->GetPathAbs();
        FXMLTag *aGroupTag = new FXMLTag("group");
        *aPolygonTag += aGroupTag;
        *aGroupTag += aPath->SaveXML("relative");
        *aGroupTag += aPath->SaveXML("absolute");
    }
    
    
    FXMLTag *aPointCloudTag = new FXMLTag("point_clouds");
    *aTag += aPointCloudTag;
    aPointCloudTag->AddParamInt("count", mSpawnSourcePointCloudList.mCount);
    for(int i = 0; i<mSpawnSourcePointCloudList.mCount; i++)
    {
        FMotionPathTemplate *aPath = (FMotionPathTemplate*)(mSpawnSourcePointCloudList.Fetch(i));
        FMotionPathTemplate *aPathAbs = aPath->GetPathAbs();
        FXMLTag *aGroupTag = new FXMLTag("group");
        *aPointCloudTag += aGroupTag;
        *aGroupTag += aPath->SaveXML("relative");
        *aGroupTag += aPath->SaveXML("absolute");
    }
    return aTag;
}

void FParticleTemplate::LoadXML(FXMLTag *pTag)
{
    if(pTag)
    {
        FString aPathSequence;
        FString aPathSprite;
        
        EnumTagsMatching(pTag, aMetaTag, "meta")
        {
            aPathSprite = aMetaTag->GetParamValue("sprite_path");
            aPathSequence = aMetaTag->GetParamValue("sprite_sequence_path");
        }
        
        if(aPathSequence.mLength > 0)EnumList(FSpriteSequence, aSpriteSequence, gSpriteSequenceList)if(aSpriteSequence->mFilePrefix == aPathSequence)mSpriteSequence = aSpriteSequence;
        if(aPathSprite.mLength > 0)EnumList(FSprite, aSprite, gSpriteList)if(aSprite->mFileName == aPathSprite)mSprite = aSprite;
        
        
        EnumTagsMatching(pTag, aSourceTag, "source")
        {
            mSpawnSourceType = aSourceTag->GetParamInt("type", mSpawnSourceType);
            mSpawnSourceWidth = aSourceTag->GetParamSafeFloat("rect_width", mSpawnSourceWidth);
            mSpawnSourceHeight = aSourceTag->GetParamSafeFloat("rect_height", mSpawnSourceHeight);
            mSpawnSourceRadius = aSourceTag->GetParamSafeFloat("radius", mSpawnSourceRadius);
            
            mSpawnParticleCount = aSourceTag->GetParamInt("count", 1);
            mSpawnParticleCountRandom = aSourceTag->GetParamInt("count_r", 0);
            
            mSpawnWaveCount = aSourceTag->GetParamInt("wave_count", 1);
            mSpawnWaveCountRandom = aSourceTag->GetParamInt("wave_count_r", 0);
            
            mSpawnWaveInterval = aSourceTag->GetParamInt("wave_interval", 0);
            mSpawnWaveIntervalRandom = aSourceTag->GetParamInt("wave_interval_r", 0);
            
            mSpawnParticleStartDelayRandom = aSourceTag->GetParamInt("start_delay_r", 0);
        }
        
        
        EnumTagsMatching(pTag, aPosTag, "position")
        {
            mSpawnOffsetX = aPosTag->GetParamSafeFloat("offset_x", 0.0f);
            mSpawnOffsetY = aPosTag->GetParamSafeFloat("offset_y", 0.0f);
            mSpawnOffsetXRandom = aPosTag->GetParamSafeFloat("offset_x_r", 0.0f);
            mSpawnOffsetYRandom = aPosTag->GetParamSafeFloat("offset_y_r", 0.0f);
        }
        
        EnumTagsMatching(pTag, aFrameTag, "frames")
        {
            mSpawnFrameSpeed = aFrameTag->GetParamSafeFloat("frame_speed", 1.0f);
            mSpawnFrameSpeedRandom = aFrameTag->GetParamSafeFloat("frame_speed_r", 0.0f);
            mSpawnFrameStartRandom = aFrameTag->GetParamBool("frame_start_random", false);
            mSpawnFrameLoop = aFrameTag->GetParamBool("frame_loop", false);
        }
        
        EnumTagsMatching(pTag, aScaleTag, "scale")
        {
            mSpawnScale = aScaleTag->GetParamSafeFloat("scale", 1.0f);
            mSpawnScaleRandom = aScaleTag->GetParamSafeFloat("scale_r", 0.0f);
            mSpawnScaleSpeed = aScaleTag->GetParamSafeFloat("speed", 0.0f);
            mSpawnScaleSpeedAdd = aScaleTag->GetParamSafeFloat("speed_add", 0.0f);
            mSpawnScaleSpeedRandom = aScaleTag->GetParamSafeFloat("speed_r", 0.0f);
            mSpawnScaleSpeedAccel = aScaleTag->GetParamSafeFloat("accel", 1.0f);
            
            
            
        }
        
        EnumTagsMatching(pTag, aRotationTag, "rotation")
        {
            mSpawnRotationSpeedNegativeRandom = aRotationTag->GetParamBool("speed_inv_r", false);
            mSpawnRotation = aRotationTag->GetParamSafeFloat("rotation", 0.0f);
            mSpawnRotationRandom = aRotationTag->GetParamSafeFloat("rotation_r", 360.0f);
            mSpawnRotationSpeed = aRotationTag->GetParamSafeFloat("speed", 0.0f);
            mSpawnRotationSpeedRandom = aRotationTag->GetParamSafeFloat("speed_r", 0.0f);
            mSpawnRotationSpeedAccel = aRotationTag->GetParamSafeFloat("accel", 1.0f);
            //mSpawnRotationSpeedAccelAdd = aRotationTag->GetParamSafeFloat("accel_add", 0.0f);
        }
        
        EnumTagsMatching(pTag, aSpeedTag, "speed")
        {
            mSpawnSpeedX = aSpeedTag->GetParamSafeFloat("x", 0.0f);
            mSpawnSpeedY = aSpeedTag->GetParamSafeFloat("y", 0.0f);
            mSpawnSpeedXRandom = aSpeedTag->GetParamSafeFloat("x_r", 0.0f);
            mSpawnSpeedYRandom = aSpeedTag->GetParamSafeFloat("y_r", 0.0f);
            mSpawnSpeedAccel = aSpeedTag->GetParamSafeFloat("accel", 1.0f);
            
            //mSpawnSpeedAccelAdd = aSpeedTag->GetParamSafeFloat("accel_add", 0.0f);
            
            
            mSpawnSpeedGravityX = aSpeedTag->GetParamSafeFloat("gravity_x", 0.0f);
            mSpawnSpeedGravityY = aSpeedTag->GetParamSafeFloat("gravity_y", 0.0f);
            mSpawnSpeedGravityYAdd = aSpeedTag->GetParamSafeFloat("gravity_y_add", 0.0f);
        }
        
        EnumTagsMatching(pTag, aDirectionalSpeedTag, "directional_speed")
        {
            mSpawnDirectionalAngle = aDirectionalSpeedTag->GetParamSafeFloat("angle", 0.0f);
            mSpawnDirectionalAngleRandom = aDirectionalSpeedTag->GetParamSafeFloat("angle_r", 0.0f);
            mSpawnDirectionalMagnitude = aDirectionalSpeedTag->GetParamSafeFloat("magnitude", 0.0f);
            mSpawnDirectionalMagnitudeRandom = aDirectionalSpeedTag->GetParamSafeFloat("magnitude_r", 0.0f);
            mSpawnDirectionalPush = aDirectionalSpeedTag->GetParamSafeFloat("push", 0.0f);
            mSpawnDirectionalPushRandom = aDirectionalSpeedTag->GetParamSafeFloat("push_r", 0.0f);
            
        }
        
        
        EnumTagsMatching(pTag, aDelayTag, "delayed_triggers")
        {
            mSpawnDelayAlphaSpeedAddTime = aDelayTag->GetParamInt("alpha_speed_add_time", 0);
            mSpawnDelayAlphaSpeedAdd = aDelayTag->GetParamSafeFloat("alpha_speed_add", 0.0f);
            
            mSpawnDelayScaleSpeedAddTime = aDelayTag->GetParamInt("scale_speed_add_time", 0);
            mSpawnDelayScaleSpeedAdd = aDelayTag->GetParamSafeFloat("scale_speed_add", 0.0f);
        }
        
        
        EnumTagsMatching(pTag, aColorTag, "colors")
        {
            FColor aDefault = FColor(1.0f, 1.0f, 1.0f, 1.0f);
            aColorTag->ReadTagSafeColor("base", &mSpawnColor, &aDefault);
            aDefault = FColor(0.0f, 0.0f, 0.0f, 0.0f);
            aColorTag->ReadTagSafeColor("base_extra", &mSpawnColorExtra, &aDefault);
            aColorTag->ReadTagSafeColor("base_r", &mSpawnColorRandom, &aDefault);
            aColorTag->ReadTagSafeColor("speed", &mSpawnColorSpeed, &aDefault);
            aColorTag->ReadTagSafeColor("speed_r", &mSpawnColorSpeedRandom, &aDefault);
            
            //mSpawnAlphaSpeedAdd = aColorTag->GetParamSafeFloat("alpha_speed_add", 0.0f);
        }
        
        
        FList aLoadList;
        EnumTagsMatching(pTag, aPolygonTag, "polygons")
        {
            EnumTagsMatching(aPolygonTag, aGroupTag, "group")
            {
                FMotionPathTemplate *aPath = new FMotionPathTemplate();
                EnumTagsMatching(aGroupTag, aRelativeTag, "relative")aPath->LoadXML(aRelativeTag);
                
                FMotionPathTemplate *aPathAbs = new FMotionPathTemplate();
                EnumTagsMatching(aGroupTag, aAbsoluteTag, "absolute")aPathAbs->LoadXML(aAbsoluteTag);
                //mSpawnSourcePolygonListAbs.Add(aPathAbs);
                
                aPathAbs->mPathAbs = 0;
                aPath->mPathAbs = aPathAbs;
                
                mSpawnSourcePolygonList.Add(aPath);
            }
        }
        
        
        EnumTagsMatching(pTag, aPointCloudTag, "point_clouds")
        {
            EnumTagsMatching(aPointCloudTag, aGroupTag, "group")
            {
                FMotionPathTemplate *aPath = new FMotionPathTemplate();
                EnumTagsMatching(aGroupTag, aRelativeTag, "relative")aPath->LoadXML(aRelativeTag);
                
                FMotionPathTemplate *aPathAbs = new FMotionPathTemplate();
                EnumTagsMatching(aGroupTag, aAbsoluteTag, "absolute")aPathAbs->LoadXML(aAbsoluteTag);
                
                aPathAbs->mPathAbs = 0;
                aPath->mPathAbs = aPathAbs;
                
                mSpawnSourcePointCloudList.Add(aPath);
            }
        }
    }
}


void FParticleTemplate::SetParent(FParticleTemplate *pParent)
{
    mSpawnSourceParent = pParent;
    
    /*
    if(mSpawnSourceParent)
    {
        mSource.mParent = &(mSpawnSourceParent->mSource);
    }
    else
    {
        mSource.mParent = 0;
    }
    */
}

void FParticleTemplate::Clone(FParticleTemplate *pParticleTemplate)
{
    Reset();
    if(pParticleTemplate)
    {
        FXMLTag *aInfo = pParticleTemplate->SaveXML();
        LoadXML(aInfo);
        delete aInfo;
    }
}

void FParticleTemplate::ResetSpawnAll()
{
    ResetSpawnPosition();
    ResetSpawnRotationAll();
    ResetSpawnScaleAll();
    ResetSpawnSpeedAll();
    ResetSpawnColorAll();
    ResetSpawnDelayedTriggers();
}

void FParticleTemplate::ResetSpawnPosition()
{
    mSpawnOffsetX = 0.0f;
    mSpawnOffsetY = 0.0f;
    mSpawnOffsetXRandom = 0.0f;
    mSpawnOffsetYRandom = 0.0f;
}

void FParticleTemplate::ResetSpawnSpeedAll()
{
    ResetSpawnSpeedBase();
    ResetSpawnSpeedDirectional();
}

void FParticleTemplate::ResetSpawnSpeedBase()
{
    mSpawnSpeedX = 0.0f;
    mSpawnSpeedXRandom = 0.0f;
    mSpawnSpeedY = 0.0f;
    mSpawnSpeedYRandom = 0.0f;
    mSpawnSpeedAccel = 1.0f;
    mSpawnSpeedGravityX = 0.0f;
    mSpawnSpeedGravityY = 0.0f;
    mSpawnSpeedGravityYAdd = 0.0f;
}

void FParticleTemplate::ResetSpawnSpeedDirectional()
{
    mSpawnDirectionalAngle = 0.0f;
    mSpawnDirectionalAngleRandom = 0.0f;
    mSpawnDirectionalMagnitude = 0.0f;
    mSpawnDirectionalMagnitudeRandom = 0.0f;
    mSpawnDirectionalPush = 0.0f;
    mSpawnDirectionalPushRandom = 0.0f;
}

void FParticleTemplate::ResetSpawnColorAll()
{
    ResetSpawnColorBase();
    ResetSpawnColorRandom();
    ResetSpawnColorSpeed();
    
}

void FParticleTemplate::ResetSpawnColorBase()
{
    mSpawnColor.mRed = 1.0f;
    mSpawnColor.mGreen = 1.0f;
    mSpawnColor.mBlue = 1.0f;
    mSpawnColor.mAlpha = 1.0f;
    mSpawnColorExtra.mRed = 0.0f;
    mSpawnColorExtra.mGreen = 0.0f;
    mSpawnColorExtra.mBlue = 0.0f;
    mSpawnColorExtra.mAlpha = 0.0f;
}

void FParticleTemplate::ResetSpawnColorRandom()
{
    mSpawnColorRandom.mRed = 0.0f;
    mSpawnColorRandom.mGreen = 0.0f;
    mSpawnColorRandom.mBlue = 0.0f;
    mSpawnColorRandom.mAlpha = 0.0f;
}

void FParticleTemplate::ResetSpawnColorSpeed()
{
    mSpawnColorSpeed.mRed = 0.0f;
    mSpawnColorSpeed.mGreen = 0.0f;
    mSpawnColorSpeed.mBlue = 0.0f;
    mSpawnColorSpeed.mAlpha = 0.0f;
    
    mSpawnColorSpeedRandom.mRed = 0.0f;
    mSpawnColorSpeedRandom.mGreen = 0.0f;
    mSpawnColorSpeedRandom.mBlue = 0.0f;
    mSpawnColorSpeedRandom.mAlpha = 0.0f;
}

void FParticleTemplate::ResetSpawnScaleAll()
{
    ResetSpawnScaleBase();
    ResetSpawnScaleSpeed();
}

void FParticleTemplate::ResetSpawnScaleBase()
{
    mSpawnScale = 1.0f;
    mSpawnScaleRandom = 0.0f;
}

void FParticleTemplate::ResetSpawnScaleSpeed()
{
    mSpawnScaleSpeed = 0.0f;
    mSpawnScaleSpeedAdd = 0.0f;
    mSpawnScaleSpeedRandom = 0.0f;
    mSpawnScaleSpeedAccel = 1.0f;
}

void FParticleTemplate::ResetSpawnRotationAll()
{
    ResetSpawnRotationBase();
    ResetSpawnRotationSpeed();
}

void FParticleTemplate::ResetSpawnRotationBase()
{
    mSpawnRotation = 0.0f;
    mSpawnRotationRandom = 0.0f;
}

void FParticleTemplate::ResetSpawnRotationSpeed()
{
    mSpawnRotationSpeed = 0.0f;
    mSpawnRotationSpeedRandom = 0.0f;
    mSpawnRotationSpeedAccel = 1.0f;
    mSpawnRotationSpeedNegativeRandom = false;
}


void FParticleTemplate::ResetSpawnDelayedTriggers()
{
    mSpawnDelayAlphaSpeedAddTime = 0;
    mSpawnDelayAlphaSpeedAdd = 0.0f;
    
    mSpawnDelayScaleSpeedAddTime = 0;
    mSpawnDelayScaleSpeedAdd = 0.0f;
}



void FParticleTemplate::QuickSingleton()
{
    QuickBlast();
    
    
    mSpawnOffsetX = 0.0f;
    mSpawnOffsetY = 0.0f;
    mSpawnOffsetXRandom = 0.0f;
    mSpawnOffsetYRandom = 0.0f;
    
    mSpawnParticleCount = 1;
    mSpawnParticleCountRandom = 0;
    mSpawnWaveCount = 1;
    mSpawnWaveCountRandom = 0;
    mSpawnWaveInterval = 8;
    mSpawnWaveIntervalRandom = 0;
    mSpawnParticleStartDelayRandom = 0;
}

void FParticleTemplate::QuickBlast()
{
    mSeed = gRand.Get(580000);
    
    if(gRand.Get(2) == 0)
    {
        float aSpeedSpan = 4.0f + gRand.GetFloat(6);
        
        mSpawnSpeedX = -(aSpeedSpan / 2.0f);
        mSpawnSpeedY = -(aSpeedSpan / 2.0f);
        mSpawnSpeedXRandom = aSpeedSpan;
        mSpawnSpeedYRandom = aSpeedSpan;
    }
    else
    {
        mSpawnSpeedX = 0.0f;
        mSpawnSpeedY = 0.0f;
        mSpawnSpeedXRandom = 0.0f;
        mSpawnSpeedYRandom = 0.0f;
    }
    
    if(gRand.Get(3) != 1)mSpawnSpeedAccel = 1.0f;
    else mSpawnSpeedAccel = gRand.F(0.8f, 1.0f);
    
    if(gRand.Get(3) != 1)mSpawnSpeedGravityX = 0.0f;
    else mSpawnSpeedGravityX = gRand.F(-0.03f, 0.03f);
    
    if(gRand.Get(3) != 1)mSpawnSpeedGravityX = 0.0f;
    else mSpawnSpeedGravityX = gRand.F(-0.08f, 0.08f);
    
    if(gRand.Get(2) == 0)mSpawnSpeedGravityY = gRand.GetFloat(0.0f, 0.1f);
    else if(gRand.Get(3) != 1)mSpawnSpeedGravityY = 0.0f;
    else mSpawnSpeedGravityY = gRand.F(-0.03f, 0.03f);
    
    if(gRand.Get(4) != 1)mSpawnSpeedGravityYAdd = 0.0f;
    else mSpawnSpeedGravityYAdd = gRand.F(-0.015f, 0.015f);
    
    
    
    if(gRand.Get(4) == 2)
    {
        mSpawnOffsetX = 0.0f;
        mSpawnOffsetY = 0.0f;
        mSpawnOffsetXRandom = 0.0f;
        mSpawnOffsetYRandom = 0.0f;
    }
    else
    {
        
        float aSpanX = 10.0f;
        float aSpanY = 10.0f;
        
        if(gRand.Get(3) == 1)
        {
            aSpanX = gRand.GetFloat(6.0f) + 4.0f;
            aSpanY = gRand.GetFloat(6.0f) + 4.0f;
            
        }
        else
        {
            if(gRand.Get(3) == 1)
            {
                aSpanX = gRand.GetFloat(12.0f) + 28.0f;
                aSpanY = gRand.GetFloat(12.0f) + 28.0f;
            }
            else
            {
                aSpanX = gRand.GetFloat(2.0f) + 2.0f;
                aSpanY = gRand.GetFloat(2.0f) + 2.0f;
            }
        }
        
        mSpawnOffsetX = -(aSpanX / 2.0f);
        mSpawnOffsetY = -(aSpanY / 2.0f);
        mSpawnOffsetXRandom = aSpanX;
        mSpawnOffsetYRandom = aSpanY;
        
    }
    
    
    mSpawnParticleCount = gRand.Get(12) + 4;
    mSpawnParticleCountRandom = gRand.Get(4) + 2;
    mSpawnWaveCount = 1;
    mSpawnWaveCountRandom = 0;
    mSpawnWaveInterval = 8;
    mSpawnWaveIntervalRandom = 0;
    mSpawnParticleStartDelayRandom = gRand.Get(4);
    
    if(gRand.Get(3) == 1)
    {
        mSpawnWaveCount += gRand.Get(6);
        mSpawnWaveCountRandom += gRand.Get(3);
        
        mSpawnWaveInterval = gRand.Get(16) + 8;
        mSpawnWaveIntervalRandom = gRand.Get(4) + 2;
    }
    
    if(gRand.Get(3) == 1)
    {
        mSpawnParticleCount += gRand.Get(20) + 16;
        mSpawnParticleCountRandom += gRand.Get(6) + 6;
    }
    
    
    
    if(gRand.Get(3) == 1)
    {
        mSpawnColor = FColor(1.0f, 1.0f, 1.0f, 1.0f);
        mSpawnColorExtra = FColor(0.0f, 0.0f, 0.0f, 0.0f);
        
        mSpawnColorRandom = FColor(0.0f, 0.0f, 0.0f, 0.0f);
        
        
        mSpawnColorSpeed = FColor(0.0f, 0.0f, 0.0f, 0.0f);
        mSpawnColorSpeedRandom = FColor(0.006f, 0.006f, 0.006f, 0.006f);
    }
    
    if(gRand.Get(3) == 1)
    {
        mSpawnColorSpeed = FColor(0.006f, 0.006f, 0.006f, 0.006f);
        mSpawnColorSpeedRandom = FColor(0.02f, 0.02f, 0.02f, 0.02f);
    }
    
    RandomRotAll(0);
}

void FParticleTemplate::QuickBlizzard()
{
    QuickBlast();
    
}


void FParticleTemplate::RandomRotAll(int pLevel)
{
    RandomRotBase(pLevel);
    RandomRotSpeed(pLevel);
    
    mSpawnRotation = 0.0f;
    mSpawnRotationRandom = 0.0f;
}


void FParticleTemplate::RandomRotBase(int pLevel)
{
    ResetSpawnRotationBase();
    
    int aRand1 = gRand.Get(3);int aRand2 = gRand.Get(3);int aRand3 = gRand.Get(3);
    
    if(aRand1 == 1)mSpawnRotation = gRand.GetFloat(360.0f);
    else if(aRand1 == 0)mSpawnRotation = gRand.GetFloat(-20.0f, 20.0f);
    else mSpawnRotation = gRand.GetFloat(-2.0f, 2.0f);
    
    if(aRand2 == 1)mSpawnRotation += gRand.GetFloat(85.0f, 95.0f);
    else if(aRand2 == 0)mSpawnRotation += gRand.GetFloat(178.0f, 182.0f);
    
    if(aRand3 == 1)mSpawnRotationRandom = 360.0f;
    else if(aRand3 == 2)mSpawnRotationRandom = gRand.GetFloat(5.0f);
    else mSpawnRotationRandom = gRand.GetFloat(0.0f, 360.0f);
}

void FParticleTemplate::RandomRotSpeed(int pLevel)
{
    ResetSpawnRotationSpeed();
    
    int aRand1 = gRand.Get(3);int aRand2 = gRand.Get(3);int aRand3 = gRand.Get(3);
    
    mSpawnRotationSpeedNegativeRandom = gRand.GetBool();
    
    if(aRand1 == 1)mSpawnRotationSpeed = gRand.GetFloat(0.0f, 0.4f);
    else mSpawnRotationSpeed = gRand.GetFloat(0.0f, 3.0f);
    
    if(aRand2 == 1)mSpawnRotationSpeedRandom = gRand.GetFloat(0.0f, 0.2f);
    else mSpawnRotationSpeedRandom = gRand.GetFloat(0.0f, 2.25f);
    
    if(aRand3 == 1)mSpawnRotationSpeedAccel = gRand.GetFloat(0.92f, 1.0f);
    else if(aRand3 == 2)mSpawnRotationSpeedAccel = gRand.GetFloat(0.85f, 1.1f);
    else mSpawnRotationSpeedAccel = gRand.GetFloat(0.98f, 1.01f);
    
}
