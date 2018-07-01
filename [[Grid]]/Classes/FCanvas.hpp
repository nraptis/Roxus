//
//  FCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_CANVAS_HPP
#define FRAMEWORK_CANVAS_HPP

#define CANVAS_TRACKED_TOUCH_COUNT 6

#include "FList.h"
#include "FRect.h"
#include "FColor.h"
#include "FString.h"
#include "FSprite.h"
#include "FPoint.h"
#include "FCanvasAbsoluteTransform.hpp"

class FWindow;
class FCanvas {

    friend class FWindow;

public:
    
    FCanvas();
    
    virtual ~FCanvas();

    virtual void                            Layout();
    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            MouseDown(float pX, float pY, int pButton);
    virtual void                            MouseMove(float pX, float pY);
    virtual void                            MouseUp(float pX, float pY, int pButton);
    virtual void                            MouseWheel(int pDirection);

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);

    void                                    AddChild(FCanvas *pCanvas);
    void                                    AddChild(FCanvas &pCanvas);
    void                                    Kill();

    void                                    DrawManualBegin();
    void                                    DrawManualEnd();
    void                                    DrawChildrenManual();
    
    float                                   mTouchX;
    float                                   mTouchY;
    
    void                                    DrawManual();
    bool                                    mDrawManual;
    
    void                                    DrawTransform();

    
    FString                                 mName;
    
    FCanvasTransform                        mTransform;
    FCanvasAbsoluteTransform                mTransformAbsolute;
    
    FColor                                  mColor;
    
    //FRect                                   mFrame;
    float                                   mX;
    float                                   mY;
    float                                   mWidth;
    float                                   mHeight;
    float                                   mWidth2;
    float                                   mHeight2;

    FWindow                                 *mWindow;
    FCanvas                                 *mParent;
    
    FList                                   mChildren;
    
    bool                                    mClipsContent;


    bool                                    mHidden;
    bool                                    mEnabled;
    
    bool                                    mConsumesTouches;
    bool                                    mRecievesOutsideTouches;
    bool                                    mRecievesConsumedTouches;

    bool                                    mMouseOver;
    bool                                    mTouchDownInside;
    bool                                    mTouchDown;
    int                                     mTouchCount;

    void                                    BringChildToFront(FCanvas *pCanvas);
    inline void                             BringChildToFront(FCanvas &pCanvas){BringChildToFront(&pCanvas);}
    void                                    SendChildToBack(FCanvas *pCanvas);
    inline void                             SendChildToBack(FCanvas &pCanvas){SendChildToBack(&pCanvas);}
    void                                    SendChildBackward(FCanvas *pCanvas);
    inline void                             SendChildBackward(FCanvas &pCanvas){SendChildBackward(&pCanvas);}
    void                                    BringChildForward(FCanvas *pCanvas);
    inline void                             BringChildForward(FCanvas &pCanvas){BringChildForward(&pCanvas);}
    
    virtual void                            SetFrame(float pX, float pY, float pWidth, float pHeight);
    inline void                             SetFrame(FRect pRect){SetFrame(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight);}
    
    inline void                             SetSize(float pWidth, float pHeight) { SetFrame(GetX(), GetY(), pWidth, pHeight); }
    inline void                             SetSize(FSprite *pSprite){ if (pSprite) SetSize(pSprite->mWidth, pSprite->mHeight); }
    inline void                             SetSize(FSprite &pSprite) { SetSize(&pSprite); }

    void                                    PrintFrame();
    void                                    PrintTransform();
    void                                    PrintAllChildrenTransforms();
    
    void                                    SetX(float pX);
    void                                    SetY(float pY);
    void                                    SetWidth(float pWidth);
    void                                    SetHeight(float pHeight);

    float                                   GetX() { float aResult = mX;return aResult; }
    float                                   GetY() { float aResult = mY;return aResult; }
    float                                   GetLeft() { return GetX(); }
    float                                   GetTop() { return GetY(); }
    float                                   GetWidth() { float aResult = mWidth;return aResult; }
    float                                   GetHeight(){ float aResult = mHeight;return aResult; }
    float                                   GetWidth2(){ float aResult = mWidth2;return aResult; }
    float                                   GetHeight2(){ float aResult = mHeight2;return aResult; }
    float                                   GetCenterX(){ return GetWidth2(); }
    float                                   GetCenterY(){ return GetHeight2(); }
    float                                   GetRight(){ float aResult = mWidth;return aResult; }
    float                                   GetBottom(){ float aResult = mHeight;return aResult; }
    FVec2                                   GetCenter() { FVec2 aResult;aResult.mX=GetCenterX();aResult.mY=GetCenterY();return aResult; }

    void                                    SetTransformTranslate(float pX, float pY);
    void                                    SetTransformX(float pX);
    void                                    SetTransformY(float pY);
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
    
    static void                             ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    void                                    ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas) { ConvertPoint(pX, pY, pFromCanvas, this); }
    void                                    ConvertPoint(float &pX, float &pY, FCanvas &pFromCanvas) { ConvertPoint(pX, pY, &pFromCanvas, this); }
    static void                             ConvertPoint(float &pX, float &pY, FCanvas &pFromCanvas, FCanvas &pToCanvas) { ConvertPoint(pX, pY, &pFromCanvas, &pToCanvas); }
    static void                             ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas, FCanvas &pToCanvas) { ConvertPoint(pX, pY, pFromCanvas, &pToCanvas); }
    static void                             ConvertPoint(float &pX, float &pY, FCanvas &pFromCanvas, FCanvas *pToCanvas) { ConvertPoint(pX, pY, &pFromCanvas, pToCanvas); }
    
    static FPoint                           Convert(float pX, float pY, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    static FPoint                           Convert(float pX, float pY, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return Convert(pX, pY, &pFromCanvas, &pToCanvas); }
    static FPoint                           Convert(float pX, float pY, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return Convert(pX, pY, pFromCanvas, &pToCanvas); }
    static FPoint                           Convert(float pX, float pY, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return Convert(pX, pY, &pFromCanvas, pToCanvas); }
    
    static FPoint                           Convert(FPoint pPos, FCanvas *pFromCanvas, FCanvas *pToCanvas) { return Convert(pPos.mX, pPos.mY, pFromCanvas, pToCanvas); }
    static FPoint                           Convert(FPoint pPos, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return Convert(pPos, &pFromCanvas, &pToCanvas); }
    static FPoint                           Convert(FPoint pPos, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return Convert(pPos.mX, pPos.mY, pFromCanvas, &pToCanvas); }
    static FPoint                           Convert(FPoint pPos, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return Convert(pPos.mX, pPos.mY, &pFromCanvas, pToCanvas); }
    
    static float                            ConvertScale(float pScale, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    static float                            ConvertScale(float pScale, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return ConvertScale(pScale, &pFromCanvas, &pToCanvas); }
    static float                            ConvertScale(float pScale, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return ConvertScale(pScale, pFromCanvas, &pToCanvas); }
    static float                            ConvertScale(float pScale, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return ConvertScale(pScale, &pFromCanvas, pToCanvas); }
    
    static float                            ConvertRotation(float pDegrees, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    static float                            ConvertRotation(float pDegrees, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return ConvertRotation(pDegrees, &pFromCanvas, &pToCanvas); }
    static float                            ConvertRotation(float pDegrees, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return ConvertRotation(pDegrees, pFromCanvas, &pToCanvas); }
    static float                            ConvertRotation(float pDegrees, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return ConvertRotation(pDegrees, &pFromCanvas, pToCanvas); }


private:

    void                                    *mTouchData[CANVAS_TRACKED_TOUCH_COUNT];
    bool                                    mTouchInside[CANVAS_TRACKED_TOUCH_COUNT];

    void                                    ComputeAbsoluteTransformation();

    int                                     mKill;

    bool                                    mDeleteWhenParentIsDeleted;

    bool                                    mDidUpdate;
    
    //When the children update, we need to re-layout
    //void                                    ChildrenDidUpdate();
    //bool                                    mChildrenDidUpdate;

    //When the children update, we need to re-layout
    //void                                    ParentDidUpdate();
    //bool                                    mParentDidUpdate;

    //When the transform updates, we do not need to re-layout the
    //parent or children.
    void                                    TransformDidUpdate();

    //When the frame updates, we need to re-layout the parent and children.
    void                                    FrameDidUpdate();

    //When our children change, we need to re-layout.
    //void                                    ChildredDidUpdate();
    //bool                                    mChildredDidUpdate;

    virtual void                            BaseLayout();
    virtual void                            BaseUpdate();
    virtual void                            BaseDraw();


    /*
    FViewContainer                              *TouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed);
    void                                        TouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    void                                        TouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    */



    virtual FCanvas                         *BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed);
    virtual void                            BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                            BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                            BaseTouchFlush();

    virtual void                            BaseMouseDown(float pX, float pY, float pOriginalX, float pOriginalY, int pButton);
    virtual void                            BaseMouseMove(float pX, float pY, float pOriginalX, float pOriginalY);
    virtual void                            BaseMouseUp(float pX, float pY, float pOriginalX, float pOriginalY, int pButton);
    virtual void                            BaseMouseWheel(int pDirection);

    virtual void                            BaseKeyDown(int pKey);
    virtual void                            BaseKeyUp(int pKey);


};

#endif /* FCanvas_hpp */
