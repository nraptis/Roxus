//
//  DemoView.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/22/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef DemoView_hpp
#define DemoView_hpp

#include "FView.h"

class DemoView : public FView {
public:
    DemoView();
    virtual ~DemoView();

    virtual void                            BaseUpdate();
    virtual void                            BaseDraw();

    virtual void                            BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    virtual void                            BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    virtual void                            BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    virtual void                            BaseTouchFlush();

    float                                   mDemoRotation;


    bool                                    mDemoRotateEnabled;
    int                                     mDemoRotateState;
    int                                     mDemoRotateDir;
    float                                   mDemoRotateTarget;
    float                                   mDemoRotateSpeed;
    int                                     mDemoRotateTimer;
    void                                    RotateStart();
    void                                    RotateStop();
    




};

#endif /* DemoView_hpp */
