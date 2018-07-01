//
//  FCanvasAbsoluteTransform.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_CANVAS_TRANSFORM_H
#define FRAMEWORK_CANVAS_TRANSFORM_H

class FView;
class FCanvasTTTransform
{
public:
    FCanvasTTTransform();
    ~FCanvasTTTransform();

    float                                       mX;
    float                                       mY;

    float                                       mScale;

    float                                       mScaleX;
    float                                       mScaleY;

    float                                       mRotation;

    float                                       mAnchorX;
    float                                       mAnchorY;
};

class FCanvasAbsoluteTransform
{
public:
    FCanvasAbsoluteTransform();
    ~FCanvasAbsoluteTransform();

    void                                        Transform(float &pX, float &pY);
    void                                        Untransform(float &pX, float &pY);

    void                                        Transform(float &pX, float &pY, float pWidth, float pHeight);
    void                                        Untransform(float &pX, float &pY, float pWidth, float pHeight);

    bool                                        ApplyAbsoluteTransformation(FCanvasAbsoluteTransform *pParentTransform, float pParentX, float pParentY, float pParentWidth, float pParentHeight, FCanvasTTTransform *pTransform, float pX, float pY, float pWidth, float pHeight);

    bool                                        ApplyAbsoluteTransformation(FCanvasTTTransform *pTransform, float pX, float pY, float pWidth, float pHeight);

    bool                                        ContainsPoint(float pX, float pY);

    float                                       mX;
    float                                       mY;

    float                                       mScale;

    float                                       mScaleX;
    float                                       mScaleY;

    float                                       mRotation;

    float                                       mAnchorX;
    float                                       mAnchorY;

    float                                       mCornerX[4];
    float                                       mCornerY[4];
};

#endif
