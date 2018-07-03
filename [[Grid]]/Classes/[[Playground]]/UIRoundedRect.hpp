//
//  UIRoundedRect.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIRoundedRect_hpp
#define UIRoundedRect_hpp

#include "FDrawQuad.h"

class UIRoundedRect : public FDrawQuad
{
public:
    UIRoundedRect();
    virtual ~UIRoundedRect();

    virtual void                                Draw();
    virtual void                                Draw(float pOffsetX, float pOffsetY);
    virtual void                                Copy(UIRoundedRect *pRect, bool pIgnoreColor = false);

    float                                       mCornerRadius;
    int                                         mCornerPointCount;
    bool                                        mRoundBottom;
    bool                                        mRoundRight;
    bool                                        mRoundLeft;
    bool                                        mSquare;
    bool                                        mRefresh;

    void                                        Generate();

    FDrawNodeList                               mNodeList;
};

#endif /* UIRoundedRect_hpp */
