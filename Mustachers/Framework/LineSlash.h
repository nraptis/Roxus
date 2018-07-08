//
//  LineSlash.h
//  DodgeDart
//
//  Created by Nick Raptis on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef LINE_SLASH_H
#define LINE_SLASH_H

class LineSlash
{
public:
    
    LineSlash();
    ~LineSlash();
    
    void                AddPoint(float x, float y);
    void                Solve();
    
    float               *mX;
    float               *mY;
    
    float               *mNormalX;
    float               *mNormalY;
    
    float               *mAngle;
    
    float               *mKinkX;
    float               *mKinkY;
    
    float               *mDist;
    
    float               mLength;
    
    int                 mCount;
    int                 mSize;
};

#endif
