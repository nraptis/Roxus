//
//  WorldGestureContainer.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef WorldGestureContainer_hpp
#define WorldGestureContainer_hpp

#include "FGestureCanvas.hpp"

class WorldTransformContainer;
class WorldGestureContainer : public FGestureCanvas {
public:
    WorldGestureContainer();
    virtual ~WorldGestureContainer();
    
    virtual void                                    Update();
    virtual void                                    Draw();

    virtual void                                    Layout();

    virtual void                                    TouchDown(float pX, float pY, void *pData);
    virtual void                                    TouchMove(float pX, float pY, void *pData);
    virtual void                                    TouchUp(float pX, float pY, void *pData);
    virtual void                                    TouchFlush();

    virtual void                                    KeyDown(int pKey);
    virtual void                                    KeyUp(int pKey);

    virtual void                                    Notify(void *pSender, const char *pNotification);

    virtual void                                    PanBegin(float pX, float pY);
    virtual void                                    Pan(float pX, float pY);
    virtual void                                    PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);

    virtual void                                    PinchBegin(float pScale);
    virtual void                                    Pinch(float pScale);
    virtual void                                    PinchEnd(float pScale);
    
    virtual void                                    TapDouble(float pX, float pY);

    virtual void                                    RotateStart(float pRotation);
    virtual void                                    Rotate(float pRotation);
    virtual void                                    RotateEnd(float pRotation);

    WorldTransformContainer                         *mWorldTransform;


    float                                           mWorldOffsetX;
    float                                           mWorldOffsetY;

    float                                           mWorldPanStartOffsetX;
    float                                           mWorldPanStartOffsetY;

    float                                           mWorldScale;
    float                                           mWorldPinchStartScale;



    float                                           mWorldRotation;


};

#endif
