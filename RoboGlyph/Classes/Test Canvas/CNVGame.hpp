//
//  CNVGame.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVGame_hpp
#define CNVGame_hpp

#include "FCanvas.hpp"
#include "CNVBoard.hpp"
#include "CNVHeader.hpp"
#include "CNVFooter.hpp"

class CNVGame : public FCanvas {
public:
    CNVGame();
    virtual ~CNVGame();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
    
    CNVBoard                               *mBoard;

    CNVHeader                              mHeader;
    CNVFooter                              mFooter;
    
};

#endif /* CNVGame_hpp */
