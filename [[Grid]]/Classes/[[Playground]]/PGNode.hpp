//
//  PGNode.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PGNode_hpp
#define PGNode_hpp

#include "FObject.h"

class PGNode : public FObject {
public:

    PGNode();
    virtual ~PGNode();
    
    virtual void                            Update();
    virtual void                            Draw();

};

#endif /* PGNode_hpp */
