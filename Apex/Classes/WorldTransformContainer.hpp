//
//  WorldTransformContainer.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef WorldTransformContainer_hpp
#define WorldTransformContainer_hpp

#include "FCanvas.hpp"

class WorldTransformContainer : public FCanvas {
public:
    WorldTransformContainer();
    virtual ~WorldTransformContainer();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);

    virtual void                            Notify(void *pSender, const char *pNotification);
    
    float                                   mPivotX;
    float                                   mPivotY;
    
    

};

#endif
