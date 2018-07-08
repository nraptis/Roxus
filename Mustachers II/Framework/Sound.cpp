/*
 *  Sound.cpp
 *  Drillheads
 *
 *  Created by Nick Raptis on 11/29/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "Sound.h"
#include "stdafx.h"
#include "Application.h"

SoundInstance::SoundInstance(ALuint pIndex)
{
	mIndex=pIndex;
	//gAudio.mSoundInstanceList+=this;
	mVolume=1.0f;
	mSavedPlaying=false;
	mIsLooping=false;
	mPause=0;
	
	
}

SoundInstance::~SoundInstance()
{
	//if (!gAudio.mDestroyed) gAudio.mSoundInstanceList-=this;
}

void SoundInstance::SetPitch()
{
	alSourcef(mIndex,AL_PITCH,1.0f);
}

void SoundInstance::SetPitch(float pMultiplier)
{
	alSourcef(mIndex,AL_PITCH,pMultiplier);
}

void SoundInstance::SetPitchManual(float pPitch)
{
	alSourcef(mIndex,AL_PITCH,pPitch);
}


void SoundInstance::Play(float pVolume)
{
	if(!gApp->mSoundOn)return;
	SetVolume(pVolume*gApp->mSoundVolume);
	alSourcei(mIndex,AL_LOOPING,false);	
	alSourcePlay(mIndex);
	mIsLooping=false;
}

void SoundInstance::Pause(bool pState)
{
	if(pState)mPause++;
    if(mPause > 0)mPause--;
    else mPause = 0;
    
	if(mPause)
	{
		if(mPause==1 && pState)
		{
			mSavedPlaying=IsPlaying();
			alSourcePause(mIndex);
		}
	}
	else
	{
		if(mSavedPlaying)
		{
			alSourcePlay(mIndex);
			mSavedPlaying=false;
		}
	}
}


void SoundInstance::Loop(float pVolume)
{
	SetVolume(pVolume);
	alSourcei(mIndex,AL_LOOPING,true);	
	alSourcePlay(mIndex);
	mIsLooping=true;
}

void SoundInstance::SetVolume(float pVolume)
{
	mVolume=pVolume;
	alSourcef(mIndex, AL_GAIN,mVolume*
			  1
			  //gAudio.mSoundVolume
	);
}

void SoundInstance::Stop()
{
	alSourceStop(mIndex);
}

bool SoundInstance::IsPlaying()
{
	ALint aResult;
	alGetSourcei(mIndex,AL_SOURCE_STATE,&aResult) ;
	return (aResult==AL_PLAYING);
}

int SoundInstance::GetPosition()
{
	return 0;
}

void SoundInstance::Destroy()
{
	
}

void SoundInstance::GetSourceProperty(unsigned int pFlag, float *pBuffer)
{
	alGetSourcef(mIndex, pFlag, pBuffer);
}

Sound::Sound(void)
{
	//mBufferListEnum=mBufferList.GetEnumerator(PtrToUlong(__FILE__),__COUNTER__);
	mSoundData=NULL;
	mInstanceCount=1;
	
	
	mSourceBuffer=new float[16];
}

Sound::~Sound(void)
{
	delete[]mSourceBuffer;
	mSourceBuffer=0;
	
	Clean();
}

void Sound::Clean()
{
	FreeList(SoundInstance,mBufferList);
	mBufferList.Clear();
	if(mSoundData)
	{
		alDeleteBuffers(mInstanceCount,mSoundData);
		delete[]mSoundData;
		delete[]mInstanceID;
	}
	
}

void Sound::Play(float pVolume)
{
	PlayPitched(1,pVolume);
}

bool Sound::IsPlaying()
{
	EnumList(SoundInstance,aInstance,mBufferList)
	{
        if(aInstance->IsPlaying())
		{
            return true;
        }
    }
    return false;
    
}

void Sound::PlayPitched(float pPitch, float pVolume)
{
	SoundInstance *aSoundInstance=0;//(SoundInstance*)mBufferList.Next(mBufferListEnum);
	EnumList(SoundInstance,aInstance,mBufferList)
	{
		if(!aInstance->IsPlaying())
		{
			aSoundInstance=aInstance;
			break;
		}
	}
	if (aSoundInstance) 
	{
		aSoundInstance->SetPitch(pPitch);
		aSoundInstance->Play(pVolume);
	}
}

void Sound::GetSourceProperty(unsigned int pFlag)
{
	
	EnumList(SoundInstance,aInstance,mBufferList)
	{
		if(aInstance->IsPlaying())
		{
			aInstance->GetSourceProperty(pFlag, mSourceBuffer);
			break;
		}
	}
}



float Sound::GetGain()
{
	if(mSoundData)
	{
		GetSourceProperty(AL_GAIN);
		return mSoundData[0];
	}
	return 0;
	
}


float Sound::GetByteOffset()
{
	if(mSoundData)
	{
		GetSourceProperty(AL_BYTE_OFFSET);
		return mSoundData[0];
	}
	return 0;
}

void Sound::StopAll()
{
	EnumList(SoundInstance,aSoundInstance,mBufferList)aSoundInstance->Stop();
}

void Sound::SetPitch(float pAdjustment)
{
	EnumList(SoundInstance,aSoundInstance,mBufferList)aSoundInstance->SetPitch(pAdjustment);
}


void Sound::Load(FString pFilename, int pDuplicates)
{
	LoadCAF(gSandbox + pFilename,pDuplicates);
}

void Sound::LoadCAF(FString pFilename, int pDuplicates)
{
	//pFilename=ClassifyFile(pFilename.c());
	
	int aLoadDataSize;
	int aLoadDataFormat;
	int aLoadSampleRate;
	
	ALsizei aDataSize;
	ALenum aDataFormat;
	ALsizei aSampleRate;
	
	void *aData=LoadSound((pFilename).c(),&aLoadDataSize,&aLoadDataFormat,&aLoadSampleRate);
	if(aData)
	{
		
		aDataSize=aLoadDataSize;
		aDataFormat=(aLoadDataFormat>1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		aSampleRate=aLoadSampleRate;
		
		mSoundData=new ALuint(aDataSize);
		alGenBuffers(1,mSoundData);
		if (alGetError()!=AL_NO_ERROR)
		{
			printf("Could not load CAF (alGenBuffers Failed): %s\n",pFilename.c());
			return;
		}
		
		alBufferData(mSoundData[0],aDataFormat,aData,aDataSize,aSampleRate);	
		if (alGetError()!=AL_NO_ERROR)
		{
			printf("Could not load CAF (alBufferData Failed): %s\n",pFilename.c());
			return;
		}
		
		mOriginalFrequency=aSampleRate;
		mInstanceID=new ALuint[pDuplicates];
		alGenSources(pDuplicates,mInstanceID);
		
		if (alGetError()!=AL_NO_ERROR)
		{
			printf("Could not load CAF (alGenSources Failed): %s\n",pFilename.c());
			return;
		}
		
		for (int aCount=0;aCount<pDuplicates;aCount++)
		{
			alSourcei(mInstanceID[aCount],AL_BUFFER,mSoundData[0]);
			
			SoundInstance *aSoundInstance=new SoundInstance(mInstanceID[aCount]);
			mBufferList+=aSoundInstance;
		}
		
		free(aData);
	}
	return;
}