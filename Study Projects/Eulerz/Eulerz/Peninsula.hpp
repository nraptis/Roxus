//
//  Peninsula.hpp
//  Eulerz
//
//  Created by Raptis, Nicholas on 5/24/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef Peninsula_hpp
#define Peninsula_hpp

#include <stdio.h>

class Peninsula {
public:
    Peninsula();
    ~Peninsula();
    
    int            connectedLandMassCount() {
        return 1;
    }
    
    void            doPeninsularThings();
    
};

#endif /* Peninsula_hpp */
