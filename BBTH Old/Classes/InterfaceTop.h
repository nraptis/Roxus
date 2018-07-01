//
//  InterfaceTop.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/12/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef InterfaceTop_h
#define InterfaceTop_h

#include "FView.h"

class InterfaceTop : public FView
{
public:
    
    InterfaceTop();
    virtual ~InterfaceTop();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    Layout(float pX, float pY, float pWidth, float pHeight);
};

#endif /* InterfaceTop_hpp */
