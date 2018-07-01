//
//  BoardAnimations.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__BoardAnimations__
#define ___015_Jeep_Arcon__BoardAnimations__

#include "FParticle.h"

class Board;
class GameTile;

class BoardAnimations
{
public:
    
    BoardAnimations(Board *pBoard);
    virtual ~BoardAnimations();
    
    Board                                           *mBoard;
    
    float                                           CenterX(int pGridX);
    float                                           CenterY(int pGridY);
    
    static FParticle                                *GenerateSparkle();
    static FParticle                                *GenerateSparkle(FSprite *pSprite);
    
    static FParticle                                *GenerateTwinkle();
    static FParticle                                *GenerateTwinkle(FSprite *pSprite, float pSpeed);
    
    
    
};


#endif /* defined(___015_Jeep_Arcon__BoardAnimations__) */
