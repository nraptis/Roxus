//
//  os_core_sound.cpp
//  RaptisGame
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "os_core_sound.h"
#include "os_core_outlets.h"
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreFoundation/CoreFoundation.h>
#import "OSMusicPlayer.h"
#include "os_core_outlets.h"
#include "core_includes.h"
#include "openal/al.h"
#include "OpenAL/alc.h"
#import "FSound.h"

OSMusicPlayer *gMusicPlayer;

int musicFadeOutTick;
int musicFadeOutTickMax;
bool musicFadeOut;

int musicFadeInTick;
int musicFadeInTickMax;
bool musicFadeIn;

float musicVolume;

bool musicLoop;
bool musicFadeLoop;


FSoundInstanceMac::FSoundInstanceMac()
{
    
}

FSoundInstanceMac::~FSoundInstanceMac()
{
    
}

//unsigned int                    mIndexOpenAL;



FSoundDataMac::FSoundDataMac()
{
    mInstanceID = 0;
    mData = 0;
    mSourceBuffer = new float[16];
    
}

FSoundDataMac::~FSoundDataMac()
{
    mData = 0;
    mInstanceID = 0;
    
    if(mSourceBuffer)
    {
        delete [] mSourceBuffer;
        mSourceBuffer = 0;
    }
}

ALCcontext *gAudioContext = 0;
ALCdevice *gAudioDevice = 0;

void core_sound_initialize()
{
    gAudioDevice = alcOpenDevice(NULL);
    
    if(gAudioDevice)
    {
        //AVAudioSession *session = [AVAudioSession sharedInstance];
        //[session setCategory:AVAudioSessionCategoryPlayback error:nil];
        //OSStatus propertySetError = 0;
        //UInt32 allowMixing = true;
        //propertySetError = AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryMixWithOthers, sizeof (allowMixing),&allowMixing);
        
        
        gAudioContext = alcCreateContext(gAudioDevice, NULL);
        alcMakeContextCurrent(gAudioContext);
        
        ALfloat ListenerPos[]={0.0, 0.0, 0.0};
        ALfloat ListenerVel[]={0.0, 0.0, 0.0};
        ALfloat ListenerOri[]={0.0, 0.0, 0.0,  0.0, 1.0, 0.0};
        
        alListenerfv(AL_POSITION,ListenerPos);
        alListenerfv(AL_VELOCITY,ListenerVel);
        alListenerfv(AL_ORIENTATION,ListenerOri);
    }
    
    gMusicPlayer = [[OSMusicPlayer alloc] init];
}




void *sound_load_ios(const char *theFilename, int *theDataSize, int *theDataFormat, int* theSampleRate)
{
    //return 0;
    
    NSString *aPath=[NSString stringWithUTF8String: theFilename];
    NSURL *aUrl=[NSURL fileURLWithPath:aPath];
    
    CFURLRef						aFileURL=(__bridge CFURLRef)aUrl;
    OSStatus						aResult = noErr;
    SInt64							aFileLengthInFrames = 0;
    AudioStreamBasicDescription		aFileFormat;
    UInt32							aPropertySize = sizeof(aFileFormat);
    ExtAudioFileRef					aExtRef = NULL;
    unsigned int*					aData = NULL;
    AudioStreamBasicDescription		aOutputFormat;
    
    for(;;)
    {
        aResult = ExtAudioFileOpenURL(aFileURL, &aExtRef);
        if(aResult)
        {
            //Log("AudioToBits: ExtAudioFileOpenURL FAILED, Error = %ld\n", aResult);
            //	break;
        }
        
        aResult=ExtAudioFileGetProperty(aExtRef, kExtAudioFileProperty_FileDataFormat, &aPropertySize, &aFileFormat);
        
        if(aResult)
        {
            break;
        }
        
        if(aFileFormat.mChannelsPerFrame>2)
        {
            //Log("MyGetOpenALAudioData - Unsupported Format, channel count is greater than stereo\n");
            break;
        }
        
        
        aOutputFormat.mSampleRate=aFileFormat.mSampleRate;
        aOutputFormat.mChannelsPerFrame=aFileFormat.mChannelsPerFrame;
        
        
        aOutputFormat.mFormatID=kAudioFormatLinearPCM;
        aOutputFormat.mBytesPerPacket=2*aOutputFormat.mChannelsPerFrame;
        aOutputFormat.mFramesPerPacket=1;
        aOutputFormat.mBytesPerFrame=2*aOutputFormat.mChannelsPerFrame;
        aOutputFormat.mBitsPerChannel=16;
        aOutputFormat.mFormatFlags=kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
        
        aResult=ExtAudioFileSetProperty(aExtRef, kExtAudioFileProperty_ClientDataFormat,sizeof(aOutputFormat),&aOutputFormat);
        if(aResult)
        {
            //Log("AudioToBits: ExtAudioFileSetProperty(kExtAudioFileProperty_ClientDataFormat) FAILED, Error = %ld\n",aResult);
            break;
        }
        
        aPropertySize=sizeof(aFileLengthInFrames);
        aResult=ExtAudioFileGetProperty(aExtRef, kExtAudioFileProperty_FileLengthFrames, &aPropertySize, &aFileLengthInFrames);
        if(aResult)
        {
            //Log("AudioToBits: ExtAudioFileGetProperty(kExtAudioFileProperty_FileLengthFrames) FAILED, Error = %ld\n",aResult);
            break;
        }
        
        unsigned int aDataSize = (unsigned int)(aFileLengthInFrames*aOutputFormat.mBytesPerFrame);
        
        aData = (unsigned int*)malloc(aDataSize);
        
        if(aData)
        {
            AudioBufferList		aDataBuffer;
            aDataBuffer.mNumberBuffers = 1;
            aDataBuffer.mBuffers[0].mDataByteSize=aDataSize;
            aDataBuffer.mBuffers[0].mNumberChannels=aOutputFormat.mChannelsPerFrame;
            aDataBuffer.mBuffers[0].mData=aData;
            
            aResult=ExtAudioFileRead(aExtRef, (UInt32*)&aFileLengthInFrames, &aDataBuffer);
            if(aResult==noErr)
            {
                *theDataSize = (int)aDataSize;
                *theDataFormat = aOutputFormat.mChannelsPerFrame;//(aOutputFormat.mChannelsPerFrame>1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
                *theSampleRate = (int)aOutputFormat.mSampleRate;
            }
            else
            {
                free(aData);
                aData=NULL;
                //Log("AudioToBits: ExtAudioFileRead FAILED, Error = %ld\n",aResult); break;
            }
        }
        break;
    }
    
    if(aExtRef)
    {
        ExtAudioFileDispose(aExtRef);
    }
    
    return aData;
}

bool core_sound_load(FSound *pSound, const char *pFileName, int pInstanceCount)
{
    bool aResult = false;
    
    if((pSound != 0) && (pFileName != 0))
    {
        if(pSound->mSoundData != 0)
        {
            FSoundDataMac *aSoundData = ((FSoundDataMac *)pSound->mSoundData);
            
            if(os_fileExists(pFileName))
            {
                
                int aLoadDataSize;
                int aLoadDataFormat;
                int aLoadSampleRate;
                
                ALsizei aDataSize;
                ALenum aDataFormat;
                ALsizei aSampleRate;
                
                void *aData = sound_load_ios(pFileName,&aLoadDataSize,&aLoadDataFormat,&aLoadSampleRate);
                
                if(aData)
                {
                    aDataSize=aLoadDataSize;
                    aDataFormat=(aLoadDataFormat>1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
                    aSampleRate=aLoadSampleRate;
                    
                    aSoundData->mData = new ALuint(aDataSize);
                    
                    bool aFail = false;
                    
                    alGenBuffers(1, aSoundData->mData);
                    
                    if(alGetError()!=AL_NO_ERROR)
                    {
                        Log("Could not load Sound (alGenBuffers Failed): %s\n", pFileName);
                        
                        aFail = true;
                    }
                    
                    if(aFail == false)
                    {
                        alBufferData(aSoundData->mData[0],aDataFormat,aData,aDataSize,aSampleRate);
                        
                        if(alGetError()!=AL_NO_ERROR)
                        {
                            Log("Could not load Sound (alBufferData Failed): %s\n", pFileName);
                            
                            aFail = true;
                        }
                    }
                    
                    
                    if(aFail == false)
                    {
                        aSoundData->mInstanceID = new ALuint[pInstanceCount];
                        alGenSources(pInstanceCount, aSoundData->mInstanceID);
                        
                        if(alGetError() != AL_NO_ERROR)
                        {
                            aFail = true;
                            Log("Could not load Sound (%x alGenSources Failed): %s\n", alGetError(), pFileName);
                        }
                    }
                    
                    if(aFail == false)
                    {
                        for(int aCount=0;aCount<pInstanceCount;aCount++)
                        {
                            alSourcei(aSoundData->mInstanceID[aCount],AL_BUFFER,aSoundData->mData[0]);
                            
                            FSoundInstanceMac *aInstance = new FSoundInstanceMac();// (aSoundData->mInstanceID[aCount]);
                            aInstance->mIndexOpenAL = aSoundData->mInstanceID[aCount];
                            aInstance->mDidLoad = true;
                            pSound->mInstances+=aInstance;
                        }
                    }
                    
                    if(aData)
                    {
                        free(aData);
                    }
                    
                    if(aFail == false)
                    {
                        aResult = true;
                    }
                    
                }
            }
        }
    }
    
    return aResult;
}

void core_sound_play(FSound *pSound)
{
    core_sound_play(pSound, 1.0f);
}

void core_sound_play(FSound *pSound, float pVolume)
{
    if(pSound)
    {
        FSoundInstanceMac *aAvailable = 0;
        
        EnumList(FSoundInstanceMac, aInstance, pSound->mInstances)
        {
            if(aInstance->mDidLoad == true)
            {
                if(core_sound_instance_isPlaying(aInstance) == false)
                {
                    aAvailable = aInstance;
                    break;
                }
            }
        }
        
        if(aAvailable)
        {
            if(aAvailable->mDidLoad)
            {
                aAvailable->ResetPitch();
                aAvailable->Play(pVolume);
            }
        }
    }
}

void core_sound_playPitched(FSound *pSound, float pPitch, float pVolume)
{
    if(pSound)
    {
        FSoundInstanceMac *aAvailable = 0;
        
        EnumList(FSoundInstanceMac, aInstance, pSound->mInstances)
        {
            if(aInstance->mDidLoad)
            {
                if(core_sound_instance_isPlaying(aInstance) == false)
                {
                    aAvailable=aInstance;
                    break;
                }
            }
        }
        
        if(aAvailable)
        {
            aAvailable->SetPitch(pPitch);
            aAvailable->Play(pVolume);
        }
    }
}

void core_sound_stop(FSound *pSound)
{
    if(pSound)
    {
        EnumList(FSoundInstanceMac, aInstance, pSound->mInstances)
        {
            aInstance->Stop();
        }
    }
}

void core_sound_clear(FSound *pSound)
{
    if(pSound)
    {
        FSoundDataMac *aSoundData = ((FSoundDataMac *)pSound->mSoundData);
        
        if(aSoundData)
        {
            alDeleteBuffers(pSound->mInstances.mCount, aSoundData->mData);
            
            delete [] aSoundData->mData;
            delete [] aSoundData->mInstanceID;
            
            aSoundData->mData = 0;
            aSoundData->mInstanceID = 0;
        }
    }
}

bool core_sound_isPlaying(FSound *pSound)
{
    bool aResult = false;
    
    if(pSound)
    {
        EnumList(FSoundInstanceMac, aInstance, pSound->mInstances)
        {
            if(core_sound_instance_isPlaying(aInstance))
            {
                aResult = true;
                break;
            }
        }
    }
    
    return aResult;
}

bool core_sound_didLoad(FSound *pSound)
{
    bool aResult = false;
    
    if(pSound)
    {
        
        EnumList(FSoundInstanceMac, aInstance, pSound->mInstances)
        {
            if(aInstance->mDidLoad == true)
            {
                aResult = true;
            }
        }
    }
    
    return aResult;
}

void core_sound_setVolume(float pVolume)
{
    gVolumeSound = pVolume;
}

float core_sound_getVolume()
{
    return gVolumeSound;
}









void core_sound_instance_resetPitch(FSoundInstance *pInstance)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)alSourcef(aInstance->mIndexOpenAL,AL_PITCH,1.0f);
}

void core_sound_instance_setPitch(FSoundInstance *pInstance, float pPitch)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)alSourcef(aInstance->mIndexOpenAL, AL_PITCH, pPitch);
}

void core_sound_instance_setVolume(FSoundInstance *pInstance, float pVolume)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)alSourcef(aInstance->mIndexOpenAL, AL_GAIN, pVolume);
}

void core_sound_instance_play(FSoundInstance *pInstance, float pVolume)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)
    {
        core_sound_instance_setVolume(pInstance, pVolume);
        alSourcei(aInstance->mIndexOpenAL,AL_LOOPING,false);
        alSourcePlay(aInstance->mIndexOpenAL);
        pInstance->mIsLooping = false;
    }
}

void core_sound_instance_pause(FSoundInstance *pInstance)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)
    {
        if(pInstance->mIsPaused == false)
        {
            pInstance->mIsPaused = true;
            alSourcePause(aInstance->mIndexOpenAL);
        }
    }
}

void core_sound_instance_unpause(FSoundInstance *pInstance)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)
    {
        if(pInstance->mIsPaused == true)
        {
            pInstance->mIsPaused = false;
            alSourcePlay(aInstance->mIndexOpenAL);
        }
    }
}


void core_sound_instance_loop(FSoundInstance *pInstance, float pVolume)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)
    {
        core_sound_instance_setVolume(pInstance, pVolume);
        alSourcei(aInstance->mIndexOpenAL, AL_LOOPING, true);
        alSourcePlay(aInstance->mIndexOpenAL);
    }
    
}

void core_sound_instance_stop(FSoundInstance *pInstance)
{
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)
    {
        alSourceStop(aInstance->mIndexOpenAL);
    }
}

bool core_sound_instance_isPlaying(FSoundInstance *pInstance)
{
    ALint aResult = 0;
    
    FSoundInstanceMac *aInstance = (FSoundInstanceMac *)pInstance;
    if(aInstance)
    {
        alGetSourcei(aInstance->mIndexOpenAL, AL_SOURCE_STATE, &aResult);
    }
    
    return (aResult==AL_PLAYING);
}

void core_sound_instance_destroy(FSoundInstance *pInstance)
{
    
}

void core_sound_musicPlay(const char *pFilePath, bool pLoop)
{
    bool aDidFind = false;
    
    const char *aResourcePath = gRes.GetResourcePathMusic(pFilePath);
    while((aResourcePath != 0) && (aDidFind == false))//(mWidth <= 0) && (mHeight <= 0))
    {
        if(os_fileExists(aResourcePath))aDidFind = true;
        else aResourcePath = gRes.GetNextResourcePath();
    }
    
    if(aDidFind == true)
    {
        [gMusicPlayer musicPlay:[NSString stringWithUTF8String:aResourcePath] withLoop:pLoop];
    }
    
    
}

void core_sound_musicCrossFade(const char *pFilePath, int pDurationTicks, bool pLoop)
{
    bool aDidFind = false;
    
    const char *aResourcePath = gRes.GetResourcePathMusic(pFilePath);
    while((aResourcePath != 0) && (aDidFind == false))//(mWidth <= 0) && (mHeight <= 0))
    {
        if(os_fileExists(aResourcePath))aDidFind = true;
        else aResourcePath = gRes.GetNextResourcePath();
    }
    
    if(aDidFind == true)
    {
        [gMusicPlayer musicCrossFadeWithPath:[NSString stringWithUTF8String:aResourcePath] withDurationTicks:pDurationTicks withLoop:pLoop];
    }
}

void core_sound_musicFadeOut(int pDurationTicks)
{
    [gMusicPlayer musicFadeOutWithDurationTicks:pDurationTicks];
}

void core_sound_musicStop()
{
    [gMusicPlayer musicStop];
}

bool core_sound_musicIsPlaying()
{
    bool aResult = false;
    
    aResult = [gMusicPlayer musicIsPlaying];
    
    return aResult;
}

void core_sound_musicSetVolume(float pVolume)
{
    gVolumeMusic = pVolume;
}

float core_sound_musicGetVolume()
{
    return gVolumeMusic;
}



void core_sound_musicResume()
{
    
}

void core_sound_musicPause()
{
    
}


void core_sound_stopAll()
{
    core_sound_stopAllEffects();
    core_sound_musicPause();
}

void core_sound_stopAllEffects()
{
    
}

FSoundData *core_sound_spawn_data()
{
    return new FSoundDataMac();
}

void core_sound_unloadEffects()
{
    
}

void core_sound_reloadEffects()
{
    
}

void core_sound_update()
{
    [gMusicPlayer updateFade];
}

void core_sound_active()
{
    
}

void core_sound_inactive()
{
    
}
