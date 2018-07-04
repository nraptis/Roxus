//
//  EditorBoard.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__EditorBoard__
#define __CoreDemo__EditorBoard__

#include "Board.h"

#define ED_M_PAN 0
#define ED_M_TILES 1
#define ED_M_DEPTH 2

#define ED_T_M_NORMAL 0
#define ED_T_M_POWERUP 1
#define ED_T_M_TREASURE 2
#define ED_T_M_DIRT 3
#define ED_T_M_ROCK 4
#define ED_T_M_RELIC 5
#define ED_T_M_COLORED_ROCK 6
#define ED_T_M_METAL 7
#define ED_T_M_ENERGY 8
#define ED_T_M_HARD_ROCK 9
#define ED_T_M_ACCESSORY 10

#define ED_T_M_ERASER 20

class EditorBoard : public Board
{
public:
    
    EditorBoard();
    virtual ~EditorBoard();
    
    virtual void                        Update();
    virtual void                        Draw();
    virtual void                        DrawOver();
    
    
    virtual void                        TouchDown(float pX, float pY, void *pData);
	virtual void                        TouchUp(float pX, float pY, void *pData);
    virtual void                        TouchMove(float pX, float pY, void *pData);
    
    //Base editor mode...
    int                                 mMode;
    
    int                                 mModeTile;
    
    //-1 = Random!
    int                                 mTileType;
    
    int                                 mAccessoryType;
    
    float                               mDragScale;
    float                               mDragStartOffset;
    float                               mDragStartMouseY;
    bool                                mDragging;
    bool                                mSideDragging;
    
    void                                ComputeReachability();
    
    void                                PlaceTile(int pGridX, int pGridY);
    int                                 mLastSetTileX;
    int                                 mLastSetTileY;
    
    int                                 mEditorStarDepthIndex;
    
    
    //virtual void                        SetTile(int pGridX, int pGridY, GameTile *pTile);
    
    void                                EditorDeleteTile(int pGridX, int pGridY);
    FList                               mEditorDeletedTileList;
    
    void                                GenerateLevel(int pInitialDepth, int pSpacing);
    
    void                                EditorClear();
    void                                EditorClearToDirt();
    void                                EditorFillWithDirt();
    
    
    
    virtual void                        Save(const char *pPath);
    virtual void                        Load(const char *pPath);
    
    FString                             mCurrentFile;
    FList                               mSavedFileList;
    
    
    
    
    
};

extern EditorBoard *gEditor;


#endif
