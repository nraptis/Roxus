//
//  EditorGameArena.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "EditorGameArena.h"
#include "Game.h"

EditorGameArena *gEditor = 0;

EditorGameArena::EditorGameArena()
{
    gEditor = this;

    mTileType = EDITOR_TILE_TYPE_TUNNEL;
    
    mTileUp = false;
    mTileDown = false;
    mTileLeft = false;
    mTileRight = false;
    
    
    mPathStartX = 1;
    mPathStartY = 1;
    
    mPathEndX = 7;
    mPathEndY = 8;
    
    Path(mPathStartX, mPathStartY, mPathEndX, mPathEndY);
    
    
    
    
    
    mEditorMode = EDITOR_MODE_PATH;
    
    mPathStartMode = false;
    
    mBlockedOverlay.Load("editor_tile_blocked");
    
    
    
    mBridgeOverlayCross.Load("editor_tile_bridge_cross");
    
    mBridgeOverlay_H.Load("editor_tile_bridge_h");
    mBridgeOverlay_V.Load("editor_tile_bridge_v");
    
    mBridgeOverlayCorner_TR.Load("editor_tile_bridge_corner_tr");
    mBridgeOverlayCorner_TL.Load("editor_tile_bridge_corner_tl");
    mBridgeOverlayCorner_BL.Load("editor_tile_bridge_corner_bl");
    mBridgeOverlayCorner_BR.Load("editor_tile_bridge_corner_br");
    
    mBridgeOverlayT_U.Load("editor_tile_bridge_t_u");
    mBridgeOverlayT_D.Load("editor_tile_bridge_t_d");
    mBridgeOverlayT_L.Load("editor_tile_bridge_t_l");
    mBridgeOverlayT_R.Load("editor_tile_bridge_t_r");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    mTunnelOverlayCross.Load("editor_tile_tunnel_cross");
    
    mTunnelOverlay_H.Load("editor_tile_tunnel_h");
    mTunnelOverlay_V.Load("editor_tile_tunnel_v");
    
    mTunnelOverlayCorner_TR.Load("editor_tile_tunnel_corner_tr");
    mTunnelOverlayCorner_TL.Load("editor_tile_tunnel_corner_tl");
    mTunnelOverlayCorner_BL.Load("editor_tile_tunnel_corner_bl");
    mTunnelOverlayCorner_BR.Load("editor_tile_tunnel_corner_br");
    
    mTunnelOverlayT_U.Load("editor_tile_tunnel_t_u");
    mTunnelOverlayT_D.Load("editor_tile_tunnel_t_d");
    mTunnelOverlayT_L.Load("editor_tile_tunnel_t_l");
    mTunnelOverlayT_R.Load("editor_tile_tunnel_t_r");
    
}

EditorGameArena::~EditorGameArena()
{
    
}

void EditorGameArena::Update()
{
    
}

void EditorGameArena::Draw()
{
    GameArena::Draw();
    
    
    SetColor();
    
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            GameTile *aTile = mTile[i][n];
            if(aTile)
            {
                Sprite *aOverlay = 0;
                
                //U
                if(aTile->mTunnelU == true && aTile->mTunnelD == true && aTile->mTunnelR == true && aTile->mTunnelL == true)aOverlay = &mTunnelOverlayCross;
                
                else if(aTile->mTunnelU == true && aTile->mTunnelD == false && aTile->mTunnelR == true && aTile->mTunnelL == true)aOverlay = &mTunnelOverlayT_U;
                else if(aTile->mTunnelU == false && aTile->mTunnelD == true && aTile->mTunnelR == true && aTile->mTunnelL == true)aOverlay = &mTunnelOverlayT_D;
                else if(aTile->mTunnelU == true && aTile->mTunnelD == true && aTile->mTunnelR == false && aTile->mTunnelL == true)aOverlay = &mTunnelOverlayT_L;
                else if(aTile->mTunnelU == true && aTile->mTunnelD == true && aTile->mTunnelR == true && aTile->mTunnelL == false)aOverlay = &mTunnelOverlayT_R;
                
                else if(aTile->mTunnelU == true && aTile->mTunnelD == false && aTile->mTunnelR == true && aTile->mTunnelL == false)aOverlay = &mTunnelOverlayCorner_TR;
                else if(aTile->mTunnelU == false && aTile->mTunnelD == true && aTile->mTunnelR == true && aTile->mTunnelL == false)aOverlay = &mTunnelOverlayCorner_BR;
                else if(aTile->mTunnelU == true && aTile->mTunnelD == false && aTile->mTunnelR == false && aTile->mTunnelL == true)aOverlay = &mTunnelOverlayCorner_TL;
                else if(aTile->mTunnelU == false && aTile->mTunnelD == true && aTile->mTunnelR == false && aTile->mTunnelL == true)aOverlay = &mTunnelOverlayCorner_BL;
                
                else if(aTile->mTunnelU == false && aTile->mTunnelD == false && aTile->mTunnelR == true && aTile->mTunnelL == true)aOverlay = &mTunnelOverlay_H;
                else if(aTile->mTunnelU == true && aTile->mTunnelD == true && aTile->mTunnelR == false && aTile->mTunnelL == false)aOverlay = &mTunnelOverlay_V;
                
                if(aOverlay)aOverlay->Center(aTile->mCenterX, aTile->mCenterY);
                
            }
        }
    }
    
    SetColor(0.5f);
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            GameTile *aTile = mTile[i][n];
            if(aTile)
            {
                Sprite *aOverlay = 0;
                
                //U
                if(aTile->mBridgeU == true && aTile->mBridgeD == true && aTile->mBridgeR == true && aTile->mBridgeL == true)aOverlay = &mBridgeOverlayCross;
                
                else if(aTile->mBridgeU == true && aTile->mBridgeD == false && aTile->mBridgeR == true && aTile->mBridgeL == true)aOverlay = &mBridgeOverlayT_U;
                else if(aTile->mBridgeU == false && aTile->mBridgeD == true && aTile->mBridgeR == true && aTile->mBridgeL == true)aOverlay = &mBridgeOverlayT_D;
                else if(aTile->mBridgeU == true && aTile->mBridgeD == true && aTile->mBridgeR == false && aTile->mBridgeL == true)aOverlay = &mBridgeOverlayT_L;
                else if(aTile->mBridgeU == true && aTile->mBridgeD == true && aTile->mBridgeR == true && aTile->mBridgeL == false)aOverlay = &mBridgeOverlayT_R;
                
                else if(aTile->mBridgeU == true && aTile->mBridgeD == false && aTile->mBridgeR == true && aTile->mBridgeL == false)aOverlay = &mBridgeOverlayCorner_TR;
                else if(aTile->mBridgeU == false && aTile->mBridgeD == true && aTile->mBridgeR == true && aTile->mBridgeL == false)aOverlay = &mBridgeOverlayCorner_BR;
                else if(aTile->mBridgeU == true && aTile->mBridgeD == false && aTile->mBridgeR == false && aTile->mBridgeL == true)aOverlay = &mBridgeOverlayCorner_TL;
                else if(aTile->mBridgeU == false && aTile->mBridgeD == true && aTile->mBridgeR == false && aTile->mBridgeL == true)aOverlay = &mBridgeOverlayCorner_BL;
                
                else if(aTile->mBridgeU == false && aTile->mBridgeD == false && aTile->mBridgeR == true && aTile->mBridgeL == true)aOverlay = &mBridgeOverlay_H;
                else if(aTile->mBridgeU == true && aTile->mBridgeD == true && aTile->mBridgeR == false && aTile->mBridgeL == false)aOverlay = &mBridgeOverlay_V;
                
                
                if(aOverlay)aOverlay->Center(aTile->mCenterX, aTile->mCenterY);
                
                
            }
        }
    }
    
    mPathSolver.Draw();
    
    SetColor(1.0f, 0.15f, 0.15f);
    DrawRect(CX(mPathStartX) - 13, CY(mPathStartY) - 13, 25, 25);
    
    SetColor(0.15f, 0.15f, 1.0f);
    DrawRect(CX(mPathEndX) - 13, CY(mPathEndY) - 13, 25, 25);
    
}

void EditorGameArena::Click(float pX, float pY)
{
    
    
    int aGridX = GetTouchGridX(pX);
    int aGridY = GetTouchGridY(pY);
    
    if(mEditorMode == EDITOR_MODE_PATH)
    {
        if(mPathStartMode)
        {
            mPathStartX = aGridX;
            mPathStartY = aGridY;
        }
        else
        {
            mPathEndX = aGridX;
            mPathEndY = aGridY;
        }
    }
    else if(mEditorMode == EDITOR_MODE_TILES)
    {
        
        if((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGridWidth) && (aGridY < mGridHeight))
        {
            GameTile *aTile = GetTile(aGridX, aGridY);
            
            if(aTile)
            {
                if(mTileType == EDITOR_TILE_TYPE_TUNNEL)
                {
                    aTile->mBlocked = false;
                    
                    aTile->mTunnelU = mTileUp;
                    aTile->mTunnelD = mTileDown;
                    aTile->mTunnelR = mTileRight;
                    aTile->mTunnelL = mTileLeft;
                }
                if(mTileType == EDITOR_TILE_TYPE_BRIDGE)
                {
                    aTile->mBlocked = false;
                    
                    aTile->mBridgeU = mTileUp;
                    aTile->mBridgeD = mTileDown;
                    aTile->mBridgeR = mTileRight;
                    aTile->mBridgeL = mTileLeft;
                }
                if(mTileType == EDITOR_TILE_TYPE_BLANK)
                {
                    aTile->mBlocked = false;
                    
                    aTile->mBridgeU = false;
                    aTile->mBridgeD = false;
                    aTile->mBridgeR = false;
                    aTile->mBridgeL = false;
                    
                    aTile->mTunnelU = false;
                    aTile->mTunnelD = false;
                    aTile->mTunnelR = false;
                    aTile->mTunnelL = false;
                }
                if(mTileType == EDITOR_TILE_TYPE_BLOCK)
                {
                    aTile->mBlocked = true;
                    
                    aTile->mBridgeU = false;
                    aTile->mBridgeD = false;
                    aTile->mBridgeR = false;
                    aTile->mBridgeL = false;
                    
                    aTile->mTunnelU = false;
                    aTile->mTunnelD = false;
                    aTile->mTunnelR = false;
                    aTile->mTunnelL = false;
                }
            }
        }
        else
        {
            /*
             for(int i=0;i<mGridWidth;i++)
             {
             for(int n=0;n<mGridHeight;n++)
             {
             GameTile *aTile = mTile[i][n];
             if(aTile)
             {
             aTile->mBridgeU = false;
             aTile->mBridgeD = false;
             aTile->mBridgeL = false;
             aTile->mBridgeR = false;
             
             aTile->mTunnelU = gRand.Get(3) == 0 ? false : true;
             aTile->mTunnelD = gRand.Get(3) == 0 ? false : true;
             aTile->mTunnelL = gRand.Get(3) == 0 ? false : true;
             aTile->mTunnelR = gRand.Get(3) == 0 ? false : true;
             
             }
             }
             }
             */
        }
    }
    
    
    Path(mPathStartX, mPathStartY, mPathEndX, mPathEndY);
    
    /*
     printf("Grid[%d, %d]\n", aGridX, aGridY);
     GameTile *aTile = GetTile(aGridX, aGridY);
     if(aTile)
     {
     aTile->mType++;
     if(aTile->mType >= 4)aTile->mType = 0;
     }
     */
}
