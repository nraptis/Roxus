//
//  BoardActionLayer.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/15/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef BOARD_ACTION_LAYER_H
#define BOARD_ACTION_LAYER_H

class BoardActionLayer
{
public:
    
    BoardActionLayer();
    virtual ~BoardActionLayer();
    
    void                                    Free();
    
    void                                    Make(int pGridWidth, int pGridHeight);
    void                                    Make(int pGridWidth, int pGridHeight, int pID);
    
    void                                    Resize(int pGridWidth, int pGridHeight);
    
    void                                    Flood(int pValue);
    void                                    Set(int pGridX, int pGridY, int pValue);
    int                                     Get(int pGridX, int pGridY);
    
    void                                    Stamp(int pGridX, int pGridY, BoardActionLayer *pLayer);
    
    bool                                    OnGrid(int pGridX, int pGridY){return (pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight);}
    
    ////////////////////////////////////////
    ////      Match Prediction Crap
    ////     (Assumes valid types > 0)
    
    bool                                    SwapAllowed(int pGridX1, int pGridY1, int pGridX2, int pGridY2);
    void                                    Swap(int pGridX1, int pGridY1, int pGridX2, int pGridY2);
    
    bool                                    MatchExists(int pGridX, int pGridY);
    bool                                    MatchExistsH(int pGridX, int pGridY);
    bool                                    MatchExistsV(int pGridX, int pGridY);
    
    ////
    ////////////////////////////////////////
    
    short                                   **mData;
    short                                   *mDataBase;
    
    int                                     mWidth;
    int                                     mHeight;
    
    int                                     mDefaultValue;
};

#endif
