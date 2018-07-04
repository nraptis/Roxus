//
//  BoardUtilities.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__BoardUtilities__
#define ___015_Jeep_Arcon__BoardUtilities__

class Board;
class GameTile;

class BoardUtilities
{
public:
    
    BoardUtilities();
    virtual ~BoardUtilities();
    
    void                                    DrawDirt(int *pDirtTop, int pColumnCount, int pStartY, int pEndY);
    
    void                                    DrawDirtSide(int pGridX, int pGridY, bool pRight, bool pTop);
    void                                    DrawDirtCorner(int pGridX, int pGridY, bool pRight);
    void                                    DrawDirtTop(int pGridX, int pGridY, bool pRight, bool pEdge);
    
    
    bool                                    TileRendersAsDirt(int pGridX, int pGridY);
    
    //void                                    DrawDirtSide(int pGridX, int pGridY, int *pDirtTop, int pColumnCount);
    //void                                    DrawDirtTop(int pGridX, int pGridY, int *pDirtTop, int pColumnCount);
    
    
    
    Board                              *mBoard;
    
    float                                   CenterX(int pGridX);
    float                                   CenterY(int pGridY);
    
    
    void                                    Save(const char *pPath);
    void                                    Load(const char *pPath);
};


#endif /* defined(___015_Jeep_Arcon__BoardUtilities__) */
