//
//  Game.h
//  GoldDigger
//
//  Created by Nick Raptis on 1/23/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#ifndef GoldDigger_Game_h
#define GoldDigger_Game_h

#include "GLApp.h"

#include "GameArena.h"
#include "EditorGameArena.h"

extern float gTileWidth;
extern float gTileHeight;

class Game : public Canvas
{
public:
    
    Game();
    virtual ~Game();
    
    GLApp                               *mApp;
    
    GameArena                           *mArena;
    
    virtual void                        Update();
    virtual void                        Draw();
    
    virtual void                        GoInactive();
    virtual void                        GoActive();
    
    virtual void                        Notify(void *pData);
    
    virtual void                        MultiTouch(int x, int y, void *pData);
	virtual void                        MultiRelease(int x, int y, void *pData);
    virtual void                        MultiDrag(int x, int y, void *pData);
    virtual void                        FlushMultiTouch();
    
    float                               TransformX(float pX);
    float                               TransformY(float pY);
    
    
    float                               mCenterX;
    float                               mCenterY;
    
    float                               mZoomScale;
};

#endif
