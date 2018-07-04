//
//  GameMenu.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__GameMenu__
#define __CoreDemo__GameMenu__

//#include "MenuModal.h"
#include "FView.h"
#include "MenuButton.h"

class GameMenu : public FView
{
public:
    
    GameMenu();
    virtual ~GameMenu();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Notify(void *pSender);
    virtual void                            AnimationComplete(FViewAnimation *pAnimation, int pID);
    
    //virtual void                            ButtonClick(FButton *pButton);
    
    MenuButton                              mButtonClose;
    MenuButton                              mButtonOptions;
    MenuButton                              mButtonMainMenu;
    MenuButton                              mButtonStore;
    
};

#endif
