//
//  AnimatedGamePath.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/12/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef AnimatedGamePath_hpp
#define AnimatedGamePath_hpp

#include "GamePath.h"
#include "FDrawQuad.hpp"

class AnimatedGamePathSegment {
public:
    AnimatedGamePathSegment();
    ~AnimatedGamePathSegment();

    
};

class AnimatedGamePath : public GamePath {
public:
    AnimatedGamePath();
    virtual ~AnimatedGamePath();

    void                                Update();
    void                                Draw();

    void                                ResetQuads();
    void                                GenerateQuads();

    FDrawQuadSnake                      mSnake;
    //float
    
    


};

#endif /* AnimatedGamePath_hpp */
