//
//  EditorEditorGameArena.h
//  Mustache
//
//  Created by Nick Raptis on 6/21/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
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
    
    virtual void                                Update();
    virtual void                                Draw();
    
    void                                        SaveImage();
    
    virtual void                                Click(float pX, float pY);
    
    void                                        AddPath();
    void                                        DeleteCurrentPath();
    void                                        RemovePath(GamePath *pPath);
    AnimatedGamePath                            *mCurrentPath;


    void                                        DeleteTile(int pGridX, int pGridY, int pGridZ);
    

    //Editor only: this determines which grid position our fingers would land at
    //for a given depth...
    void                                        GetGridPosAtDepth(float pX, float pY, int pDepth, int &pGridX, int &pGridY);


    float                                       mGridOpacity;

    int                                         mTileDepth;
    int                                         mTileType;

    int                                         mEditorMode;

    bool                                        mPathStartMode;
    bool                                        mPathSelectMode;


};

extern EditorGameArena *gEditor;

#endif
