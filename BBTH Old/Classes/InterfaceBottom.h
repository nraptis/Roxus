//
//  InterfaceBottom.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/12/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef InterfaceBottom_h
#define InterfaceBottom_h

#include "FView.h"

class InterfaceBottom : public FView
{
public:
    
    InterfaceBottom();
    virtual ~InterfaceBottom();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    Layout(float pX, float pY, float pWidth, float pHeight);
};

#endif /* InterfaceBottom_hpp */
