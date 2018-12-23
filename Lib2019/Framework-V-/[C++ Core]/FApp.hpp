#ifndef FRAMEWORK_APP_H
#define FRAMEWORK_APP_H

#include "core_includes.h"
#include "FFont.hpp"


class PlatformOpenGLView;
//class UMainCanvas;

class FApp
{
public:

    FApp();
    virtual ~FApp();

protected:
    bool                                        mDidInitialize;
    
    bool                                        mDidUpdate;
    
public:
    
    virtual void                                Initialize() { }
    
    virtual void                                SetDeviceSize(float pWidth, float pHeight) { }
    
	virtual void                                SetVirtualFrame(float pX, float pY, float pWidth, float pHeight) { }
    
    virtual void                                Load() {}
    virtual void                                LoadComplete() {}

    virtual void                                Update(){}
    virtual void                                Draw(){}
    virtual void                                DrawOver(){}

    virtual void                                TouchDown(float pX, float pY, void *pData){}
    virtual void                                TouchMove(float pX, float pY, void *pData){}
    virtual void                                TouchUp(float pX, float pY, void *pData){}
    virtual void                                TouchFlush(){}
    virtual void                                MouseDown(float pX, float pY, int pButton);
    virtual void                                MouseMove(float pX, float pY);
    virtual void                                MouseUp(float pX, float pY, int pButton);
    virtual void                                MouseWheel(int pDirection);

    virtual void                                KeyDown(int pKey);
    virtual void                                KeyUp(int pKey);

    virtual void                                Inactive(){}
    virtual void                                Active(){}

    bool                                        mActive;

    virtual void                                MemoryWarning(bool pSevere) { }
    
    FWindow                                     mWindowMain;
    FWindow                                     mWindowModal;
    FWindow                                     mWindowTools;
    FWindow                                     *mSelectedInputWindow;
    
    int                                         mTimeSinceLastInteraction;
    
    FFont                                       mSysFont;
    FFont                                       mSysFontBold;
    
    float                                       mTouchX;
    float                                       mTouchY;

    FList                                       mImageLoadDirectoryList;
    FList                                       mImageLoadExtensionList;
    FList                                       mImageLoadSuffixList;
    FList                                       mImageLoadMutableSuffixList;

    void                                        ProcessMouseDown(float pX, float pY, int pButton);
    void                                        ProcessMouseMove(float pX, float pY);
    void                                        ProcessMouseUp(float pX, float pY, int pButton);
    void                                        ProcessMouseWheel(int pDir);
    void                                        ProcessTouchDown(float pX, float pY, void *pData);
    void                                        ProcessTouchMove(float pX, float pY, void *pData);
    void                                        ProcessTouchUp(float pX, float pY, void *pData);
    void                                        ProcessTouchFlush();
    void                                        ProcessKeyDown(int pKey);
    void                                        ProcessKeyUp(int pKey);

    void                                        BaseLoad();
    void                                        BaseUpdate();
    void                                        BaseDraw();
    void                                        BaseSetDeviceSize(float pWidth, float pHeight);
    void                                        BaseSetVirtualFrame(float pX, float pY, float pWidth, float pHeight);
    void                                        BaseInitialize();
    void                                        BaseLoadComplete();
    void                                        BaseActive();
    void                                        BaseInactive();
    void                                        BaseMemoryWarning(bool pSevere);
    void                                        BaseKeyDown(int pKey);
    void                                        BaseKeyUp(int pKey);
    void                                        BaseTouchDown(float pX, float pY, void *pData);
    void                                        BaseTouchMove(float pX, float pY, void *pData);
    void                                        BaseTouchUp(float pX, float pY, void *pData);
    void                                        BaseTouchCanceled(float pX, float pY, void *pData);
    void                                        BaseTouchDownDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseTouchMoveDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseTouchUpDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseTouchCanceledDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseMouseDown(float pX, float pY, int pButton);
    void                                        BaseMouseMove(float pX, float pY);
    void                                        BaseMouseUp(float pX, float pY, int pButton);
    void                                        BaseMouseWheel(int pDirection);
    
    
    void                                        MainRunLoop();
    
    
    void                                        BaseQuit();
    virtual void                                Quit();
    bool                                        ShouldQuit();
    bool                                        mQuit;
    
    
    
    
    
    void                                        FrameController();
    
    int                                         mSystemLock;
    void                                        SystemLock();
    void                                        SystemUnlock();
    void                                        SystemProcess();
    
    
    int                                         mThrottleLock;
    void                                        ThrottleLock();
    void                                        ThrottleUnlock();
    void                                        Throttle();
    void                                        ThrottleUpdate();
    void                                        ThrottleDraw();
    
    void                                        EnqueueInitialLoad();
    void                                        (*mLoadFunc)(void *pArgs);
    bool                                        mIsLoadEnqueued;
    bool                                        mIsLoading;
    bool                                        mIsLoadingComplete;
    
    bool                                        mTriggerLoadComplete;
    
    
    
    //void os_execute_on_main_thread(void (*pFunc)());
    
    
    //
    // Control stuff...
    //
    
    float                                       mUpdatesPerSecond;
    int                                         mUpdateMultiplier;
    
    int                                         mSkipDrawTick;
    
    void                                        RecoverTime();
    inline void                                 CatchUp() { RecoverTime(); }
    
    struct Frame
    {
        unsigned int                            mBaseUpdateTime;
        int                                     mCurrentUpdateNumber;
        bool                                    mBreakUpdate;
        float                                   mDesiredUpdate;
    }                                           mFrame;
    
    int                                         mFPS;
    
};

extern FApp *gAppBase;
extern PlatformOpenGLView *gOpenGLView;

#endif
