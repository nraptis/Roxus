#ifndef ___015_Fleet_XP__FViewAnimation__
#define ___015_Fleet_XP__FViewAnimation__

class FView;

class FViewAnimation {
public:
    FViewAnimation();
    FViewAnimation(FView *pView);
    
    virtual ~FViewAnimation();
    
    bool                            Update();
    void                            SetUp(FView *pView);
    
    void                            Generate(int pFunction, int pTicks);
    void                            GenerateIn(int pTicks);
    void                            GenerateOut(int pTicks);
    void                            GenerateSmooth(int pTicks);
    
    void                            Finish();
    float                           Percent();
    
    int                             mID;
    
    float                           mStartX;
    float                           mTargetX;
    
    float                           mStartY;
    float                           mTargetY;
    
    float                           mStartScale;
    float                           mTargetScale;
    
    float                           mStartScaleX;
    float                           mTargetScaleX;
    
    float                           mStartScaleY;
    float                           mTargetScaleY;
    
    float                           mStartRotation;
    float                           mTargetRotation;
    
    int                             mTimerTick;
    int                             mTime;
    
    float                           *mPercent;
    FView                           *mView;
};

#endif

