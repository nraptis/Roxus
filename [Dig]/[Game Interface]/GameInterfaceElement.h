//
//  GameInterfaceElement.h
//  Digplex
//
//  Created by Nick Raptis on 9/19/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__GameInterfaceElement__
#define __Digplex__GameInterfaceElement__

#include "FView.h"
#include "FButton.h"

class GameInterfaceElement : public FView
{
public:
    GameInterfaceElement();
    virtual ~GameInterfaceElement();
    
    void                                    SetSprite(FSprite *pSprite, bool pAutoSize=true);
    void                                    SetSpriteShadow(FSprite *pSprite, bool pAutoSize=true);
    
    
    virtual void                            Draw();
    virtual void                            DrawShadow();
    virtual void                            DrawOverlay();
    
    FSprite                                 *mSprite;
    FSprite                                 *mSpriteShadow;
};


class GameInterfaceContainer : public FView
{
public:
    GameInterfaceContainer();
    
    virtual void                            Draw();
    virtual void                            DrawShadow();
    virtual void                            DrawOverlay();
};



//GameInterfaceElement

#endif /* defined(__Digplex__GameInterfaceElement__) */
