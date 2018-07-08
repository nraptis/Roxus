#ifndef APPLICATION_H
#define APPLICATION_H



#include "stdafx.h"
#include "List.h"
#include "Image.h"
#include "Buffer.h"
#include "FString.h"
#include "Sprite.h"
#include "Font.h"
#include "Model.h"
#include "ImageBundler.h"
#include "Achievement.h"
#include "Purchase.h"
#include "HSList.h"

#include "ImageBundler.h"
extern ImageBundler gImageBundler;

//#include "al.h"

#include <AudioToolbox/AudioToolbox.h>
#include <QuartzCore/QuartzCore.h>
#include <CoreFoundation/CoreFoundation.h>

#include "openal/al.h"
#include "OpenAL/alc.h"

#define GS (gGlobalScale)

#define MULTI_TOUCH_AUTOFLUSH_TIMER 128



class Application
{
public:
    
	Application();
	virtual                 ~Application();

	virtual void            Initialize(){}
	virtual void            Load(){}
	virtual void            LoadComplete(){mLoadComplete=1;}
    
    virtual void            GoInactive();
    virtual void            GoActive();
	
	virtual void            Freeze(){}
	virtual void            Unfreeze(){}
	
	virtual void            SaveData(){}
	virtual void            LoadData(){}
    
	virtual void            LoadStatic();
	virtual void            SaveStatic();
	
	virtual void            Clean(){}
    
    virtual void            Message(char *pMessage, char *pArguments){Message(FString(pMessage), FString(pArguments));}
    virtual void            Message(char *pMessage){Message(FString(pMessage), FString(""));}
    
    virtual void            Message(const char *pMessage){Message(FString(pMessage), FString(""));}
    virtual void            Message(const char *pMessage, const char *pArguments){Message(FString(pMessage), FString(pArguments));}
    
    virtual void            Message(FString pMessage){Message(pMessage, FString(""));}
    
    //Override This...
	virtual void            Message(FString pMessage, FString pArguments){}
    
	virtual void            SuccessfulPurchase(char* pId);
	virtual void            FailPurchase(char* pId);
	virtual void            CancelPurchase(char* pId);
	
	virtual void            FailHTTP(char *pURL);
	virtual void            SuccessfulHTTP(char *pURL);
	int                     mPendingHTTPPosts;
	
	void                    DisplayAchievement(Achievement *pAchievement);
	List                    mRecentAchievements;
	
	void                    LoadImageSequence(Image *pImageArray, const char *pBasePath, int pStartIndex, int pEndIndex, int pLeadingZeros=4);
	void                    LoadSpriteSequence(Sprite *pSpriteArray, const char *pBasePath, int pStartIndex, int pEndIndex, int pLeadingZeros=4);
	
	void                    BaseTouch(int x, int y);
	void                    BaseRelease(int x, int y);
	void                    BaseDrag(int x, int y);
	
	void                    BaseMultiTouch(int x, int y, void *pData);
	void                    BaseMultiRelease(int x, int y, void *pData);
    void                    BaseMultiDrag(int x, int y, void *pData);
    void                    BaseFlushMultiTouch();
    
	virtual void            Touch(int x, int y){}
	virtual void            Release(int x, int y){}
	virtual void            Drag(int x, int y){}
    
    void                    AddSprite(Sprite *pSprite);
    void                    RemoveSprite(Sprite *pSprite);
    
    virtual void            MultiTouch(int x, int y, void *pData){}
	virtual void            MultiRelease(int x, int y, void *pData){}
    virtual void            MultiDrag(int x, int y, void *pData){}
	
	float                   MultiTouchCenterX();
	float                   MultiTouchCenterY();
	
	float                   MultiTouchDist();
	
    virtual void            FlushMultiTouch(){}
    
    bool                    mSnapPicture;
	
	virtual void            Accelerometer(float x, float y, float z, bool pReverse){};
	
	void                    BaseDraw();
	void                    BaseUpdate();
	
	void                    DeleteCanvas(Canvas *pCanvas);
	void                    SetOrientation(int pOrientation);
	
	virtual void            Update(){}
	virtual void            Draw(){}
	virtual void            DrawOver(){}
	virtual void            DrawTop(){}
	virtual void            DrawLoading(){}
    
    
    bool                    mActive;
    
    bool                    mDrawing;
    
    void                    **mMultiTouchData;
    int                     *mMultiTouchX;
    int                     *mMultiTouchY;
    int                     *mMultiTouchTimer;
    
    int                     mMultiTouchCount;
    int                     mMultiTouchSize;
	
    
	virtual void            UpdateAdHeight(int pHeight){mAdHeight=pHeight;}
	
	int                     *mBindList;
	int                     *mBindCountList;
	int                     mBindListSize;
	int                     mBindListCount;
	
	void                    AddBind(int pIndex);
	void                    RemoveBind(int pIndex);
	void                    PrintBindList();
	
    HSList                  mHSList;
	
	int                     mMouseX, mMouseY;
    
	void                    PurgeAllTextures();
	
	void                    AddSubcanvas(Canvas *pCanvas);
	void                    RemoveChild(Canvas *pCanvas);
    
	void                    operator+=(Canvas *pCanvas){AddSubcanvas(pCanvas);}
	void                    operator-=(Canvas *pCanvas){RemoveChild(pCanvas);}
	
    List                    mChildren;
    List                    mKillChildren;
    
	
	//Splat                 *mCurrentSplat;
	ImageBundler            *mImageBundle;
	
	Canvas                  *mTarget;
	int                     mTargetX,mTargetY;
	
	int                     mOrientation,mPreviousOrientation;
	
	int                     mLoadStarted;
	int                     mLoadComplete;
	
	int                     mAdHeight;
	
	ALCcontext              *mContext;
	ALCdevice               *mDevice;
	
	bool                    mPurchased;
	
	float                   mMusicVolume;
	float                   mSoundVolume;
	bool                    mMusicOn;
	bool                    mOptionsMusicOn;
	bool                    mSoundOn;
	bool                    mOptionsSoundOn;
	bool                    mMusicOverride;
	bool                    mStopUpdates;
	bool                    mStopDraws;
    
	void                    InitializeAudio();
	bool                    mAudioInitialized;
	
	Sound                   mSoundGlobalButtonClick;
	
	AchievementManager      mAchievementManager;
	PurchaseManager         mPurchaseManager;
	
};

extern int gAppWidth;
extern int gAppHeight;
extern float gAppWidth2;
extern float gAppHeight2;
extern float gGlobalScale;

extern bool gIsIpad;
extern bool gDoubleRez;

extern float gTestSlide1;
extern float gTestSlide2;
extern float gTestSlide3;

extern int gTestIndex1;
extern int gTestIndex2;
extern int gTestIndex3;

extern bool gTestFlag1;
extern bool gTestFlag2;
extern bool gTestFlag3;

#endif