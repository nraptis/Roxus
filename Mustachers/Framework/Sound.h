/*
 *  Sound.h
 *  Drillheads
 *
 *  Created by Nick Raptis on 11/29/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#ifndef SOUND_H
#define SOUND_H

#include "openal/al.h"
#include "OpenAL/alc.h"

#include "List.h"
#include "FString.h"

class SoundInstance
{
public:
	SoundInstance(ALuint pIndex);
	virtual ~SoundInstance();
	SoundInstance(const SoundInstance&);
	SoundInstance& operator= (const SoundInstance&);
	
	void					Play(float pVolume=1.0f);
	void					Loop(float pVolume=1.0f);
	void					Stop();
	void					SetVolume(float pVolume=1.0f);
	bool					IsPlaying();
	
	void					SetPitch(float pAdjustment);
	void					SetPitchManual(float pPitch);
	void					SetPitch();
	
	int						GetPosition();
	void					Pause(bool pState);
	
	void					Destroy();
	
public:
	ALuint					mIndex;
	float					mVolume;
	
	int						mPause;
	bool					mSavedPlaying;
	
	bool					mIsLooping;
	
	
	//alGetSourcef
	
	
	
	void					GetSourceProperty(unsigned int pFlag, float *pBuffer);
	
};

class Sound
{
public:
	Sound(void);
	virtual ~Sound(void);
	
public:
	void					LoadCAF(FString pFilename, int pDuplicates=8);
	void					Load(FString pFilename, int pDuplicates=8);//{LoadCAF(gSandbox + pFilename,pDuplicates);}
	
	
	void					Play(float pVolume=1.0f);
	void					PlayPitched(float pPitch, float pVolume=1.0f);
	void					StopAll();
	void					Clean();
	
	bool					IsPlaying();
	
	
	void					GetSourceProperty(unsigned int pFlag);
	
	
	float					GetGain();
	
	float					GetMaxGain();
	float					GetMinGain();
	float					GetRollOff();
	float					GetByteOffset();
	
	
	/*
	AL_GAIN                 ALfloat
	* Min Gain                          AL_MIN_GAIN             ALfloat
	* Max Gain                          AL_MAX_GAIN             ALfloat
	* Position                          AL_POSITION             ALfloat[3]
	* Velocity                          AL_VELOCITY             ALfloat[3]
	* Direction                         AL_DIRECTION            ALfloat[3]
	* Head Relative Mode                AL_SOURCE_RELATIVE      ALint (AL_TRUE or AL_FALSE)
	* Reference Distance                AL_REFERENCE_DISTANCE   ALfloat
	* Max Distance                      AL_MAX_DISTANCE         ALfloat
	* RollOff Factor                    AL_ROLLOFF_FACTOR       ALfloat
	* Inner Angle                       AL_CONE_INNER_ANGLE     ALint or ALfloat
	* Outer Angle                       AL_CONE_OUTER_ANGLE     ALint or ALfloat
	* Cone Outer Gain                   AL_CONE_OUTER_GAIN      ALint or ALfloat
	* Pitch                             AL_PITCH                ALfloat
	* Looping                           AL_LOOPING              ALint (AL_TRUE or AL_FALSE)
	* MS Offset                         AL_MSEC_OFFSET          ALint or ALfloat
	* Byte Offset                       AL_BYTE_OFFSET          ALint or ALfloat
	* Sample Offset                     AL_SAMPLE_OFFSET        ALint or ALfloat
	* Attached Buffer                   AL_BUFFER               ALint
	* State (Query only)                AL_SOURCE_STATE         ALint
	* Buffers Queued (Query only)       AL_BUFFERS_QUEUED       ALint
	* Buffers Processed (Query only)    AL_BUFFERS_PROCESSED    ALint
	*/
	
	
	int						mInstanceCount;
	ALuint					*mSoundData;
	ALuint					*mInstanceID;
	
	
	float					*mSourceBuffer;
	
	int						mOriginalFrequency;

	void					SetPitch(float pMultiplier);
	
	List					mBufferList;
};

#endif