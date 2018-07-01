#ifndef FRAMEWORK_NEW_VIEW_H
#define FRAMEWORK_NEW_VIEW_H

#include "FList.h"
#include "FRect.h"
#include "FColor.h"
#include "FString.h"
#include "FAnimation.h"
#include "FViewContainer.h"
#include "FViewTransform.h"
#include "FSprite.h"

#define VIEW_ANIMATION_NULL (-1)
#define VIEW_ANIMATION_IN 1
#define VIEW_ANIMATION_OUT 2
#define VIEW_ANIMATION_TRANSITION_IN 3
#define VIEW_ANIMATION_TRANSITION_OUT 4

enum
{
    VIEW_TYPE_VIEW=0,
    VIEW_TYPE_BUTTON=1,
    VIEW_TYPE_IMAGE_VIEW,
    VIEW_TYPE_GESTURE_VIEW,
    VIEW_TYPE_SCROLL_VIEW,
    VIEW_TYPE_SCROLL_VIEW_PAGED
};

class FViewController;
class FView
{
public:
    FView();
    virtual ~FView();
    
    virtual void                            BasePositionContent();
    virtual void                            PositionContent();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            Notify(void *pSender);
    virtual void                            Notify(void *pSender, int pID, void *pObject);
    
	virtual void							MouseWheel(int pDirection);
	virtual void							KeyDown(int pKey);
	virtual void							KeyUp(int pKey);
    
    void                                    DrawManualBegin();
    void                                    DrawManualEnd();
    void                                    DrawManualSubviews();
    
    void                                    SetListener(FView *pView){mListenerView = pView;}
    FView                                   *mListenerView;
    
    bool                                    mNotifyParent;
    
    void                                    DrawBorders();
    
    virtual void                            BaseUpdate();
    virtual void                            BaseDraw();
    
    virtual void                            BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
	virtual void                            BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    virtual void                            BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
	virtual void                            BaseTouchFlush();
    
    inline FViewContainer                   *GetContainer(){return mContainer;}
    
    float                                   mTouchX;
    float                                   mTouchY;
    
    void                                    SizeToFitChildren();
    void                                    SizeToFitChildren(float pPaddingLeft, float pPaddingRight);
    void                                    SizeToFitChildren(float pPaddingLeft, float pPaddingRight, float pPaddingTop, float pPaddingBottom);
    
    virtual bool                            ShouldReceieveTouch(FView *pTopView, bool pInside);
    
    void                                    DrawManual();
    bool                                    mDrawManual;
    
    void                                    DrawTransform();
    
    void                                    AddSubview(FView *pView);
    void                                    AddSubview(FView &pView);
    
    void                                    RemoveFromParent();
    
    void                                    BringSubviewToFront(FView *pView);
    inline void                             BringSubviewToFront(FView &pView){BringSubviewToFront(&pView);}
    
    void                                    SendSubviewToBack(FView *pView);
    inline void                             SendSubviewToBack(FView &pView){SendSubviewToBack(&pView);}
    
    void                                    SendSubviewBackward(FView *pView);
    inline void                             SendSubviewBackward(FView &pView){SendSubviewBackward(&pView);}
    
    void                                    BringSubviewForward(FView *pView);
    inline void                             BringSubviewForward(FView &pView){BringSubviewForward(&pView);}
    
    FString                                 mName;
    FViewContainer                          *mContainer;
    FViewController                         *mController;
    
    int                                     mViewID;
    
    float                                   mX;
    float                                   mY;
    
    float                                   mWidth;
    float                                   mHeight;
    float                                   mWidth2;
    float                                   mHeight2;
    
    bool                                    mClipsContent;
    
    bool                                    mHidden;
    bool                                    mEnabled;
    
    bool                                    mConsumesTouches;
    bool                                    mRecievesOutsideTouches;
    bool                                    mRecievesConsumedTouches;
    
    bool                                    mTouchDownInside;
    bool                                    mTouchDown;
    
    int                                     mTouchCount;
    
    bool                                    mMouseOver;
    bool                                    mTouchCanceled;
    
    bool                                    mDragFrameMode;
    
    bool                                    ContainsPoint(float pX, float pY);
    
    void                                    Kill();
    
    FViewTransform                          mTransform;
    FColor                                  mColor;
    
    int                                     mViewType;
    
    virtual void                            SetFrame(float pX, float pY, float pWidth, float pHeight);
    inline void                             SetFrame(FRect pRect){SetFrame(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight);}
    inline void                             SetFrame(float pWidth, float pHeight){SetFrame(0.0f, 0.0f, pWidth, pHeight);}
    
    
    inline void                             SetSize(float pWidth, float pHeight){SetFrame(GetX(), GetY(), pWidth, pHeight);}
    inline void                             SetSize(float pSize){SetSize(pSize, pSize);}
    inline void                             SetSize(FSprite *pSprite){if(pSprite)SetSize(pSprite->mWidth, pSprite->mHeight);}
    inline void                             SetSize(FSprite &pSprite){SetSize(&pSprite);}
    
    void                                    SetCenter(float pCenterX, float pCenterY);
    void                                    SetCenter();
    
    FRect                                   GetFrame(){return FRect(mX, mY, mWidth, mHeight);}
    
    void                                    SetFrameCenter(float pX, float pY);
    void                                    SetFrameTopLeft(float pX, float pY);
    void                                    SetFrameTopRight(float pX, float pY);
    
    void                                    SetFrameBottomLeft(float pX, float pY);
    void                                    SetFrameBottomRight(float pX, float pY);
    
    void                                    SetPos(float pX, float pY){SetFrameTopLeft(pX, pY);}
    
    void                                    PrintFrame();
    void                                    PrintTransform();
    
    void                                    PrintAllChildrenTransforms();
    
    void                                    SetTransformTranslate(float pX, float pY);
    
    void                                    SetTransformX(float pX);
    void                                    SetTransformY(float pX);
    
    void                                    SetTransformScale(float pScale);
    void                                    SetTransformScale(float pScaleX, float pScaleY);
    
    void                                    SetTransformScaleX(float pScaleX);
    void                                    SetTransformScaleY(float pScaleY);
    
    void                                    SetTransformRotation(float pRotation);
    
    void                                    SetTransformAnchorX(float pAnchorX);
    void                                    SetTransformAnchorY(float pAnchorY);
    void                                    SetTransformAnchor(float pAnchorX, float pAnchorY);
    
    float                                   GetTransformX(){return mTransform.mX;}
    float                                   GetTransformY(){return mTransform.mY;}
    
    float                                   GetTransformScale(){return mTransform.mScale;}
    
    float                                   GetTransformScaleX(){return mTransform.mScaleX;}
    float                                   GetTransformScaleY(){return mTransform.mScaleY;}
    
    float                                   GetTransformRotation(){return mTransform.mRotation;}
    
    float                                   GetTransformAnchorX(){return mTransform.mAnchorX;}
    float                                   GetTransformAnchorY(){return mTransform.mAnchorY;}
    
    static void                             ConvertPoint(float &pX, float &pY, FView *pFromView, FView *pToView);
    void                                    ConvertPoint(float &pX, float &pY, FView *pFromView){ConvertPoint(pX, pY, pFromView, this);}
    void                                    ConvertPoint(float &pX, float &pY, FView &pFromView){ConvertPoint(pX, pY, &pFromView, this);}
    static void                             ConvertPoint(float &pX, float &pY, FView &pFromView, FView &pToView){ConvertPoint(pX, pY, &pFromView, &pToView);}
    static void                             ConvertPoint(float &pX, float &pY, FView *pFromView, FView &pToView){ConvertPoint(pX, pY, pFromView, &pToView);}
    static void                             ConvertPoint(float &pX, float &pY, FView &pFromView, FView *pToView){ConvertPoint(pX, pY, &pFromView, pToView);}
    
    static FVec2                            Convert(float pX, float pY, FView *pFromView, FView *pToView);
    FVec2                                   Convert(float pX, float pY, FView *pFromView){return Convert(pX, pY, pFromView, this);}
    FVec2                                   Convert(float pX, float pY, FView &pFromView){return Convert(pX, pY, &pFromView, this);}
    static FVec2                            Convert(float pX, float pY, FView &pFromView, FView &pToView){return Convert(pX, pY, &pFromView, &pToView);}
    static FVec2                            Convert(float pX, float pY, FView *pFromView, FView &pToView){return Convert(pX, pY, pFromView, &pToView);}
    static FVec2                            Convert(float pX, float pY, FView &pFromView, FView *pToView){return Convert(pX, pY, &pFromView, pToView);}
    
    static float                            ConvertScale(float pScale, FView *pFromView, FView *pToView);
    float                                   ConvertScale(float pScale, FView *pFromView){return ConvertScale(pScale, pFromView, this);}
    float                                   ConvertScale(float pScale, FView &pFromView){return ConvertScale(pScale, &pFromView, this);}
    static float                            ConvertScale(float pScale, FView &pFromView, FView &pToView){return ConvertScale(pScale, &pFromView, &pToView);}
    static float                            ConvertScale(float pScale, FView *pFromView, FView &pToView){return ConvertScale(pScale, pFromView, &pToView);}
    static float                            ConvertScale(float pScale, FView &pFromView, FView *pToView){return ConvertScale(pScale, &pFromView, pToView);}
    
    static float                            ConvertRotation(float pDegrees, FView *pFromView, FView *pToView);
    float                                   ConvertRotation(float pDegrees, FView *pFromView){return ConvertRotation(pDegrees, pFromView, this);}
    float                                   ConvertRotation(float pDegrees, FView &pFromView){return ConvertRotation(pDegrees, &pFromView, this);}
    static float                            ConvertRotation(float pDegrees, FView &pFromView, FView &pToView){return ConvertRotation(pDegrees, &pFromView, &pToView);}
    static float                            ConvertRotation(float pDegrees, FView *pFromView, FView &pToView){return ConvertRotation(pDegrees, pFromView, &pToView);}
    static float                            ConvertRotation(float pDegrees, FView &pFromView, FView *pToView){return ConvertRotation(pDegrees, &pFromView, pToView);}
    
    float                                   GetAbsoluteTransformX();
    float                                   GetAbsoluteTransformY();
    
    float                                   GetAbsoluteTransformScale();
    
    float                                   GetAbsoluteTransformScaleX();
    float                                   GetAbsoluteTransformScaleY();
    
    float                                   GetAbsoluteTransformRotation();
    
	void                                    SetStaticTransform(bool pIsStatic);
    
    float                                   GetX(){float aReturn = mX;return aReturn;}
    float                                   GetY(){float aReturn = mY;return aReturn;}
    float                                   GetLeft(){return GetX();}
    float                                   GetTop(){return GetY();}
    float                                   GetWidth(){float aReturn = mWidth;return aReturn;}
    float                                   GetHeight(){float aReturn = mHeight;return aReturn;}
    float                                   GetWidth2(){return mWidth2;}
    float                                   GetHeight2(){return mHeight2;}
    
    float                                   GetCenterX(){return mX + mWidth2;}
    float                                   GetCenterY(){return mY + mHeight2;}
    float                                   GetRight(){return GetX() + GetWidth();}
    float                                   GetBottom(){return GetY() + GetHeight();}
    FVec2                                   GetCenter(){FVec2 aReturn;aReturn.mX=GetCenterX();aReturn.mY=GetCenterY();return aReturn;}
    
    
    void                                    SetX(float pX);
    void                                    SetY(float pY);
    void                                    SetWidth(float pWidth);
    void                                    SetHeight(float pHeight);
    
    FView                                   *mParent;
    bool                                    mParentRetain;
    
    FList                                   mSubviews;
    
    //void                                    LayoutSetParent(float pPaddingUp, float pPaddingDown, float pPaddingRight, float pPaddingLeft);
    //void                                    LayoutSetParent(float pPaddingUp, float pPaddingDown){LayoutSetParent();}
    //void                                    LayoutSetParent();
    
    
    /*
    void                                    AnimationCommit(int pTickCount=43);
    
    
    bool                                    IsAnimating();
    bool                                    IsAnimatingIn();
    bool                                    IsAnimatingOut();
    
    float                                   GetAnimationPercent();
    
    
    virtual void                            AnimateIn();
    virtual void                            AnimateOut(bool pKillAfter);
    
    //void                                    AnimationBegin();
    virtual void                            AnimationComplete(FViewAnimation *pAnimation, int pID){}
    virtual void                            AnimationUpdate(FViewAnimation *pAnimation, int pID, float pPercent){}
    
    void                                    AnimationSetCurve(int pAnimationCurve);
    
    
    void                                    AnimationSetDirectionIn();
    void                                    AnimationSetDirectionOut();
    void                                    AnimationSetDirectionArbitrary();
    
    
    
    
    void                                    AnimationSetID(int pID);
    int                                     AnimationGetID();
    void                                    AnimationSetKillAfter(bool pKillAfter);
    void                                    AnimationSetDelay(int pDelayTicks);
    
    
    void                                    AnimationSetAnchorX(float pStartAnchorX, float pTargetAnchorX);
    void                                    AnimationSetAnchorX(float pTargetAnchorX);
    void                                    AnimationSetAnchorXFrom(float pStartAnchorX);
    
    void                                    AnimationSetAnchorY(float pStartAnchorY, float pTargetAnchorY);
    void                                    AnimationSetAnchorY(float pTargetAnchorY);
    void                                    AnimationSetAnchorYFrom(float pStartAnchorY);
    
    void                                    AnimationSetRotation(float pStartRotation, float pTargetRotation);
    void                                    AnimationSetRotation(float pTargetRotation);
    void                                    AnimationSetRotationFrom(float pStartRotation);
    
    void                                    AnimationSetScale(float pStartScale, float pTargetScale);
    void                                    AnimationSetScale(float pTargetScale);
    void                                    AnimationSetScaleFrom(float pStartScale);
    
    void                                    AnimationSetScaleX(float pStartScaleX, float pTargetScaleX);
    void                                    AnimationSetScaleX(float pTargetScaleX);
    void                                    AnimationSetScaleXFrom(float pStartScaleX);
    
    void                                    AnimationSetScaleY(float pStartScaleY, float pTargetScaleY);
    void                                    AnimationSetScaleY(float pTargetScaleY);
    void                                    AnimationSetScaleYFrom(float pStartScaleY);
    
    void                                    AnimationSetX(float pStartX, float pTargetX);
    void                                    AnimationSetX(float pTargetX);
    void                                    AnimationSetXFrom(float pStartX);
    
    void                                    AnimationSetY(float pStartY, float pTargetY);
    void                                    AnimationSetY(float pTargetY);
    void                                    AnimationSetYFrom(float pStartY);
    */
    
    
    
    /*
    
    /////////////////////////////
    //
    //      Smooth Group
    //
    //Smooth Slow-Downs
#define ANIMATION_TYPE_EASE_OUT_SIN 1
#define ANIMATION_TYPE_EASE_OUT_IN_SIN 2
#define ANIMATION_TYPE_EASE_IN_CURVE 3
    
    //Smooth Speed-Ups
#define ANIMATION_TYPE_EASE_IN_SIN 4
#define ANIMATION_TYPE_EASE_IN_OUT_SIN 5
#define ANIMATION_TYPE_EASE_OUT_CURVE 6
    
    //Smooth Stuck, ZOOM, Stuck..
#define ANIMATION_TYPE_EASE_IN_OUT_EXPO 7
#define EASE_IN_OUT_QUART 8
#define EASE_OUT_IN_QUART 9
    //
    /////////////////////////////
    
    
    /////////////////////////////
    //
    //      Slow Down Group
    //
    //Slowing Down..
#define ANIMATION_TYPE_EASE_OUT_CIRC 10
#define ANIMATION_EASE_OUT_ELASTIC 11
#define ANIMATION_TYPE_EASE_OUT_BACK 12
#define ANIMATION_TYPE_OVERSHOOT (ANIMATION_TYPE_EASE_OUT_BACK)
#define ANIMATION_TYPE_OVERSHOOT_MORE 13
#define ANIMATION_TYPE_BOUNCE 14
#define ANIMATION_TYPE_BOUNCE_MORE 15
#define ANIMATION_TYPE_EASE_OUT_QUART 16 //Really fast, then GLUE
#define ANIMATION_TYPE_EASE_OUT_EXPO 17
    //
    /////////////////////////////
    
    
    /////////////////////////////
    //
    //      Speed Up Group
    //
    //Speeding Up.. (Slow, then FAST)
#define ANIMATION_TYPE_EASE_IN_CIRC 20
#define ANIMATION_TYPE_EASE_IN_OUT_CIRC 21
#define ANIMATION_TYPE_EASE_IN_EXPO 22
#define ANIMATION_TYPE_EASE_IN_QUART 23 //Sticky like tar, then ZEWWWWWWW!!!
    
    */
    
    
    
};

#endif
