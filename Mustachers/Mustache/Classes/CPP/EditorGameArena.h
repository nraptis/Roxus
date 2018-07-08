//
//  EditorEditorGameArena.h
//  Mustache
//
//  Created by Nick Raptis on 6/21/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef EDITOR_GAME_ARENA_H
#define EDITOR_GAME_ARENA_H

#include "GameArena.h"

#define EDITOR_MODE_TILES 0
#define EDITOR_MODE_PATH 1

#define EDITOR_TILE_TYPE_TUNNEL 0
#define EDITOR_TILE_TYPE_BRIDGE 1
#define EDITOR_TILE_TYPE_BLANK 2
#define EDITOR_TILE_TYPE_BLOCK 3

class EditorGameArena : public GameArena
{
public:
    
    EditorGameArena();
    virtual ~EditorGameArena();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    virtual void                        Click(float pX, float pY);
    
    int                                 mTileType;
    
    bool                                mTileUp;
    bool                                mTileDown;
    bool                                mTileLeft;
    bool                                mTileRight;
    
    
    
    int                                 mEditorMode;
    
    
    bool                                mPathStartMode;
    
    int                                 mPathStartX;
    int                                 mPathStartY;
    
    int                                 mPathEndX;
    int                                 mPathEndY;
    
    
    Sprite                              mBlockedOverlay;
    
    
    Sprite                              mBridgeOverlayCross;
    
    Sprite                              mBridgeOverlay_H;
    Sprite                              mBridgeOverlay_V;
    
    Sprite                              mBridgeOverlayCorner_TR;
    Sprite                              mBridgeOverlayCorner_TL;
    Sprite                              mBridgeOverlayCorner_BL;
    Sprite                              mBridgeOverlayCorner_BR;
    
    Sprite                              mBridgeOverlayT_U;
    Sprite                              mBridgeOverlayT_D;
    Sprite                              mBridgeOverlayT_L;
    Sprite                              mBridgeOverlayT_R;
    
    
    
    Sprite                              mTunnelOverlayCross;
    
    Sprite                              mTunnelOverlay_H;
    Sprite                              mTunnelOverlay_V;
    
    Sprite                              mTunnelOverlayCorner_TR;
    Sprite                              mTunnelOverlayCorner_TL;
    Sprite                              mTunnelOverlayCorner_BL;
    Sprite                              mTunnelOverlayCorner_BR;
    
    Sprite                              mTunnelOverlayT_U;
    Sprite                              mTunnelOverlayT_D;
    Sprite                              mTunnelOverlayT_L;
    Sprite                              mTunnelOverlayT_R;
    
    
};

extern EditorGameArena *gEditor;

#endif
