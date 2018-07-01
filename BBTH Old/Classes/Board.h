//
//  Board.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/12/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include "FView.h"
#include "TileEgg.h"
#include "TileMulti.h"
#include "BoardUtilities.hpp"
#include "BoardActionLayer.h"
#include "BoardMatch.h"

#define SWAP_TIME 18
#define MATCH_TIME 33

class Board : public FView
{
public:
    
    Board();
    virtual ~Board();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            Notify(void *pSender);
    
    
    
    void                                    Load();
    
    //Only call this after load / board sizing is complete.
    void                                    Layout();
    
    
    int                                     GetTouchGridX(float pX);
    int                                     GetTouchGridY(float pY);
    float                                   GetTileCenterX(int pGridX);
    float                                   GetTileCenterY(int pGridY);
    
    
    
    Tile                                    *GetTile(int pGridX, int pGridY);
    Tile                                    *GetTile(int pGridX, int pGridY, int pTileType);
    TileEgg                                 *GetEgg(int pGridX, int pGridY){return (TileEgg *)GetTile(pGridX, pGridY, TILE_TYPE_EGG);}
    
    
    
    void                                    SizeGrid(int pGridWidth, int pGridHeight);
    void                                    FreeGrid();
    bool                                    OnGrid(int pGridX, int pGridY){return (pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight);}
    bool                                    Selectable(int pGridX, int pGridY);
    
    bool                                    ActionAllowed();
    
    
    void                                    DeleteTile(int pGridX, int pGridY);
    Tile                                    *RemoveTileFromGrid(int pGridX, int pGridY);
    void                                    PlaceTileOnGrid(Tile *pTile, int pGridX, int pGridY);
    
    Tile                                    ***mTile;
    int                                     mGridWidth;
    int                                     mGridHeight;
    
    int                                     mGridScreenTop;
    int                                     mGridScreenHeight;
    
    int                                     mGridDigZoneTop;
    int                                     mGridDigZoneHeight;
    
    
    int                                     *mDirtTop;
    
    int                                     *mMultiPartBottom;
    
    float                                   mOffsetX, mOffsetY;
    
    int                                     mTouchGridX, mTouchGridY;
    
    FList                                   mKillList;
    FList                                   mDeleteList;
    
    
    void                                    ActionRefresh();
    int                                     mActionTimer;
    
    void                                    DestroyDirtReset();
    void                                    DestroyDirt(int pGridX, int pGridY);
    void                                    DestroyDirtAdjustUndershoot();
    
    
    BoardActionLayer                        mDestroyDirtAdjacent;
    BoardActionLayer                        mDestroyDirt;
    
    
    
    bool                                    mSwap,mSwapReverse;
    //,mSwapBlock;
    int                                     mSwapTimer;
    
    Tile                                    *mSwapTile[2];
    int                                     mSwapTileGridX[2];
    int                                     mSwapTileGridY[2];
    
    float                                   mSwapDragStartX, mSwapDragStartY;
    void                                    *mSwapDragData;
    
    bool                                    mMatching;
    int                                     mMatchingTimer;
    
    bool                                    mToppleCheck;
    bool                                    mToppling;
    
    bool                                    Topple();
    bool                                    FillHoles();
    
    BoardActionLayer                        mFalling;
    BoardActionLayer                        mFresh;
    
    //Same as mMatching...
    //bool                                    mCascading;
    bool                                    mCascadeCheck;
    int                                     mCascadeComboCount;
    bool                                    Cascade();
    bool                                    CascadeAllowed();
    
    //equivalent to "matching" ...
    //bool                                    mCascading;
    
    bool                                    SwapTiles(int pGridX1, int pGridY1, int pGridX2, int pGridY2, bool pReverse);
    bool                                    SwapTilesAllowed(int pGridX1, int pGridY1, int pGridX2, int pGridY2);
    void                                    SwapTilesCancel();
    
    
    int                                     FindMoves();
    
    
    //Matches are only from swaps. Only vertical and horizontal.
    
    
    void                                    MatchesBegin(bool pFromSwap);
    void                                    MatchesComplete();
    
    void                                    MatchesReset();
    bool                                    MatchesFind(int pGridX, int pGridY);
    BoardMatch                              *DequeueMatch();
    BoardActionLayer                        mMatchType;
    BoardActionLayer                        mMatchCheckH;
    BoardActionLayer                        mMatchCheckV;
    FList                                   mMatchList;
    FList                                   mMatchQueue;
    
    int                                     mMatchTypeCount;
    
    //Clusters are HOR and VER groups that are triggered from items and stuff..
    
    
    
    
    BoardUtilities                          *mUtils;
    
    
};

extern Board *gBoard;

#endif



