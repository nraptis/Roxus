//
//  BoardContainer.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/13/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef BoardContainer_hpp
#define BoardContainer_hpp

#include "FView.h"

class Board;
class BoardContainer : public FView
{
public:
    
    BoardContainer();
    virtual ~BoardContainer();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Notify(void *pSender);
    
    void                                    Layout(float pX, float pY, float pWidth, float pHeight);
    
    Board                                   *mBoard;
};


//BoardContainer

#endif /* BoardContainer_hpp */
