//
//  Game.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/11/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "FView.h"

#include "Board.h"
#include "BoardContainer.h"
#include "InterfaceTop.h"
#include "InterfaceBottom.h"

class Game : public FView
{
public:
    
    Game();
    virtual ~Game();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    
    virtual void                            Notify(void *pSender);
    
    void                                    Layout(float pX, float pY, float pWidth, float pHeight);
    
    Board                                   *mBoard;
    BoardContainer                          *mBoardContainer;
    InterfaceTop                            *mInterfaceTop;
    InterfaceBottom                         *mInterfaceBottom;
    
};

extern Game *gGame;

#endif /* Game_hpp */
