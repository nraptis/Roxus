#pragma once

#include <math.h>

#define		DIAG_COST 14
#define		ADJ_COST 10

class PathFinder
{
public:
	PathFinder();
	~PathFinder();
    
    void                                    Free();
    void                                    Clear();
    void                                    Size(int pWidth, int pHeight);
	bool                                    FindPath(int pStartX, int pStartY, int pDestX, int pDestY);
    
	bool                                    **mGrid;
	int                                     *mOpenList;
	int                                     **mTempList;
	int                                     *mOpenX;
	int                                     *mOpenY;
	int                                     **mParentXList;
	int                                     **mParentYList;
	int                                     *mTotCost;
	int                                     **mGCost;
	int                                     *mHCost;
	
	int                                     mPathLength;
    
    int                                     mGridWidth;
    int                                     mGridHeight;
    
	int                                     *mPathX;
	int                                     *mPathY;
};
