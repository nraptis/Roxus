//
//  SelectionHalo.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/21/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__SelectionHalo__
#define ___015_Jeep_Arcon__SelectionHalo__

#include "FObject.h"

//Eh, so this is a "new" idea. So, it will probably look bad..

class SelectionHalo : public FObject
{
public:
    
    SelectionHalo();
    virtual ~SelectionHalo();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    
};


#endif /* defined(___015_Jeep_Arcon__SelectionHalo__) */
