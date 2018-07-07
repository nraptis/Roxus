//
//  PGPathEditor.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PGPathEditor_hpp
#define PGPathEditor_hpp

#include "FCanvas.hpp"
#include "ToolMenu.hpp"
#include "FPointList.h"

class PGPathEditor : public FCanvas {
public:
    PGPathEditor();
    virtual ~PGPathEditor();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);


    FPointList                              mPointList;

    
};

#endif
