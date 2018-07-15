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
#include "FPointList.h"

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

    void                                Add45DegreeBend(float pStartX, float pStartY,
                                                        float pCenterX, float pCenterY,
                                                        float pEndX, float pEndY);

    FPointList                          mGeneratePointList;


    FDrawQuadSnake                      mSnake;
    //float


    bool                                mSelected;
    bool                                mEditorMode;
    


};

#endif /* AnimatedGamePath_hpp */
