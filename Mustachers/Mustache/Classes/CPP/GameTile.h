//
//  GameTile.h
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_GameTile_h
#define Mustache_GameTile_h

#include "GLApp.h"
#include "XML.h"

class GameTile
{
public:
    
    GameTile();
    virtual ~GameTile();
    
    GLApp                               *mApp;
    
    void                                SetUp(int pType, int pGridX, int pGridY);
    void                                SetUp(int pGridX, int pGridY);
    
    virtual void                        Update();
    virtual void                        Draw();
    
    int                                 mGridX;
    int                                 mGridY;
    
    float                               mCenterX;
    float                               mCenterY;
    
    int                                 mType;
    
    bool                                mBlocked;
    
    bool                                mTunnelU;
    bool                                mTunnelD;
    bool                                mTunnelL;
    bool                                mTunnelR;
    
    bool                                mBridgeU;
    bool                                mBridgeD;
    bool                                mBridgeL;
    bool                                mBridgeR;
    
    XMLTag                              *Save();
    void                                Load(XMLTag *pTag);
    
};

#endif
