//
//  FRect.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/12/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_RECT_H
#define FRAMEWORK_RECT_H

#include "FVec2.h"

class FRect
{
public:
    
    FRect(float pX, float pY, float pWidth, float pHeight);
    FRect(float pWidth, float pHeight);
    FRect(const FRect &pRect){*this = pRect;}
    FRect();
    
    virtual ~FRect();
    
    inline FRect &operator = (const FRect &pRect){if(this!=&pRect){mX=pRect.mX;mY=pRect.mY;mWidth=pRect.mWidth;mHeight=pRect.mHeight;}return *this;}
    
    static FRect                    FitAspectFit(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder, float &pScale);
    static FRect                    FitAspectFill(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder, float &pScale);
    
    
    static FRect                    FitAspectFit(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder);
    static FRect                    FitAspectFill(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder);
    
    static float                    PinRight(FRect pFrame, FRect pRect, float pBorder);
    static float                    PinLeft(FRect pFrame, FRect pRect, float pBorder);
    static float                    PinCenterX(FRect pFrame, FRect pRect);
    
    static float                    PinTop(FRect pFrame, FRect pRect, float pBorder);
    static float                    PinBottom(FRect pFrame, FRect pRect, float pBorder);
    static float                    PinCenterY(FRect pFrame, FRect pRect);
    
    
    
    
    FVec2                           Center();
    
    float                           Left();
    float                           Right();
    float                           Top();
    float                           Bottom();
    
    //width only / height only as well..
    //static FRect                                        FitAspect(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder);
    
    
    bool                            Contains(float pX, float pY);
    inline bool                     ContainsPoint(float pX, float pY){return Contains(pX, pY);}
    
    
    
    bool                            Intersects(float pX, float pY, float pWidth, float pHeight);
    inline bool                     Intersects(FRect &pRect){return Intersects(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight);}
    
    
    float                           CenterX(){return mX + (mWidth * 0.5f);}
    float                           CenterY(){return mY + (mHeight * 0.5f);}
    
    
    
    float                           mX;
    float                           mY;
    
    float                           mWidth;
    float                           mHeight;
    
};

#endif /* defined(__CoreDemo__FRect__) */
