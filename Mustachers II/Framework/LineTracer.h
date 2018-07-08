//
//  LineTracer.h
//  Jiggle
//
//  Created by Nick Raptis on 9/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "stdafx.h"
#include "VertexBuffer.h"

class LineTracer
{
public:
    
    LineTracer();
    ~LineTracer();
    
    void                Clear();
    void                AddPoint(float pX, float pY);
    void                Draw();
    
    void                Calculate();
    
    void				Add(float pX, float pY);
    
    
    float               mWidth;
    
    
    float				*mX;
    float				*mY;
    
    
    //float				*mCornerX;
    //float				*mCornerY;
    
    int					mCount;
    int					mSize;
    
    
    bool				mChanged;
    bool                mCircular;
    
    VertexBuffer        mBuffer;
    VertexBuffer        mBufferFill;
    
};