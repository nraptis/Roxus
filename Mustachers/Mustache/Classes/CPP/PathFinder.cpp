#include "GLApp.h"
#include "PathFinder.h"
#include <stdlib.h>

PathFinder::PathFinder(void)
{
    mGridWidth = 0;
    mGridHeight = 0;
    
    mPathLength = 0;
    
    mGrid = 0;
	mOpenList = 0;
	mTempList = 0;
	mOpenX = 0;
	mOpenY = 0;
	mParentXList = 0;
	mParentYList = 0;
	mTotCost = 0;
	mGCost = 0;
	mHCost = 0;
    
	mPathX = 0;
	mPathY = 0;
    
}

PathFinder::~PathFinder(void)
{
    
}

void PathFinder::Free()
{
    mGridWidth = 0;
    mGridHeight = 0;
    
    mPathLength = 0;
    
    mGrid = 0;
	mOpenList = 0;
	mTempList = 0;
	mOpenX = 0;
	mOpenY = 0;
	mParentXList = 0;
	mParentYList = 0;
	mTotCost = 0;
	mGCost = 0;
	mHCost = 0;

	mPathX = 0;
	mPathY = 0;
}

void PathFinder::Clear()
{
    for(int i=0;i<mGridWidth;i++)
	{
		for(int n=0;n<mGridHeight;n++)
		{
            mGrid[i][n]=false;
		}
	}
}

void PathFinder::Size(int pWidth, int pHeight)
{
    Free();
    
    mGridWidth = pWidth;
    mGridHeight = pHeight;
    
    printf("Sized To [%d x %d]\n", pWidth, pHeight);
    
    int aArea = mGridWidth*mGridHeight;
    
    mOpenList = new int[aArea];
	mOpenX = new int[aArea];
	mOpenY = new int[aArea];
    mTotCost = new int[aArea];
	mHCost = new int[aArea];
    mPathX = new int[aArea];
	mPathY = new int[aArea];
    
    mGrid = new bool*[mGridWidth];
    for(int i=0;i<mGridWidth;i++)mGrid[i] = new bool[mGridHeight];
    
    mTempList = new int*[mGridWidth];
	for(int i=0;i<mGridWidth;i++)mTempList[i] = new int[mGridHeight];
    
    mParentXList = new int*[mGridWidth];
	for(int i=0;i<mGridWidth;i++)mParentXList[i] = new int[mGridHeight];
    
    mParentYList = new int*[mGridWidth];
    for(int i=0;i<mGridWidth;i++)mParentYList[i] = new int[mGridHeight];
    
    mGCost = new int*[mGridWidth];
    for(int i=0;i<mGridWidth;i++)mGCost[i] = new int[mGridHeight];
    
    
	for(int i=0;i<mGridWidth;i++)
	{
		for(int n=0;n<mGridHeight;n++)
		{
            mGrid[i][n]=false;
		}
	}
}

bool PathFinder::FindPath(int pStartX, int pStartY, int pDestX, int pDestY)
{
    mPathLength = 0;
    
	bool aExists=false;
	bool aCrossesCorner=false;
    int mParentX=0;
	int mParentY=0;
	int aHoldOpen=0;
	int aTempListCount=0;
	int aAddedGCost=0;
	int aHoldGCost = 0;
	int aPathXTemp;
	int aPathX;
	int aPathY;
	int aTempOpen=0;
	int aX=0;
	int aY=0;
	int aOpenNode=0;
	int u=0;
	int v=0;

	int aXDist=pStartX-pDestX;
	int aYDist=pStartY-pDestY;
    
	if(aXDist == 0 && aYDist == 0)return false;

	for(int x=0;x<mGridWidth;x++)
	{
		for(int y=0;y<mGridHeight;y++)
		{
			mTempList[x][y] = 0;
		}
	}

	mGCost[pStartX][pStartY] = 0;
	aTempListCount = 1;
	mOpenList[1] = 1;
	mOpenX[1] = pStartX;
	mOpenY[1] = pStartY;

    while(true)
	{
		if(aTempListCount != 0)
		{
			mParentX = mOpenX[mOpenList[1]];
			mParentY = mOpenY[mOpenList[1]];
			mTempList[mParentX][mParentY] = 1;
			aTempListCount = aTempListCount - 1;
			mOpenList[1] = mOpenList[aTempListCount+1];
			v = 1;
			for(;;)
			{
				u = v;		
				if (2*u+1 <= aTempListCount)
				{
					if (mTotCost[mOpenList[u]] >= mTotCost[mOpenList[2*u]])
					{
						v = 2*u;
					}
					if (mTotCost[mOpenList[v]] >= mTotCost[mOpenList[2*u+1]])
					{
						v = 2*u+1;
					}
				}
				else
				{
					if(2*u <= aTempListCount)
					{	
						if (mTotCost[mOpenList[u]] >= mTotCost[mOpenList[2*u]])
						{
							v = 2*u;
						}
					}
				}

				if(u != v)
				{
					aHoldOpen = mOpenList[u];
					mOpenList[u] = mOpenList[v];
					mOpenList[v] = aHoldOpen;			
				}
				else 
				{
					break;
				}
			}
			for(aY = mParentY-1; aY <= mParentY+1; aY++)
			{
				for(aX = mParentX-1; aX <= mParentX+1; aX++)
				{
					if(aX != -1 && aY != -1 && aX != mGridWidth && aY != mGridHeight)
					{
						if(mTempList[aX][aY] < 2)
						{
							if(mGrid[aX][aY] != true)
							{
								aCrossesCorner = false;	
								if(aX == mParentX-1)
								{
									if(aY == mParentY-1)
									{
										if(mGrid[mParentX-1][mParentY] == true || mGrid[mParentX][mParentY-1] == true)
										{
											aCrossesCorner = true;
										}
									}
									else if(aY == mParentY+1)
									{
										if(mGrid[mParentX][mParentY+1] == true || mGrid[mParentX-1][mParentY] == true)
										{
											aCrossesCorner = true;
										}
									}
								}
								else if(aX == mParentX+1)
								{
									if(aY == mParentY-1)
									{
										if(mGrid[mParentX][mParentY-1] == true || mGrid[mParentX+1][mParentY] == true)
										{
											aCrossesCorner = true;
										}
									}
									else if(aY == mParentY+1)
									{
										if(mGrid[mParentX+1][mParentY] == true || mGrid[mParentX][mParentY+1] == true)
										{
											aCrossesCorner = true;
										}
									}
								}
								if(aCrossesCorner == false)
								{	
									if (mTempList[aX][aY] == false) 
									{
										aTempOpen = aTempOpen + 1;
										aOpenNode = aTempListCount+1;
										mOpenList[aOpenNode] = aTempOpen;
										mOpenX[aTempOpen] = aX;
										mOpenY[aTempOpen] = aY;

										if(abs(aX-mParentX) == 1 && abs(aY-mParentY) == 1)
										{
											aAddedGCost = DIAG_COST;
										}
										else
										{
											aAddedGCost = ADJ_COST;
										}

										//X Product?
										mGCost[aX][aY] = mGCost[mParentX][mParentY] + aAddedGCost;
										mHCost[mOpenList[aOpenNode]] = 10 * (abs(aX - pDestX) + abs(aY - pDestY))
										//+ abs(aXDist * (aY - pDestY) - aYDist * (aX - pDestX)) / 2
										//+ abs(aXDist * (aY - pDestY) - aYDist * (aX - pDestX))
										;
										mTotCost[mOpenList[aOpenNode]] = mGCost[aX][aY] + mHCost[mOpenList[aOpenNode]];
										mParentXList[aX][aY] = mParentX;
										mParentYList[aX][aY] = mParentY;

										//Reheapify!
										while(aOpenNode != 1)
										{
											if (mTotCost[mOpenList[aOpenNode]] <= mTotCost[mOpenList[aOpenNode/2]])
											{
												aHoldOpen = mOpenList[aOpenNode/2];
												mOpenList[aOpenNode/2] = mOpenList[aOpenNode];
												mOpenList[aOpenNode] = aHoldOpen;
												aOpenNode = aOpenNode/2;
											}
											else
											{
												break;
											}
										}
										aTempListCount = aTempListCount+1;
										mTempList[aX][aY] = true;
									}
									else
									{
										if(abs(aX-mParentX) == 1 && abs(aY-mParentY) == 1)
										{
											aAddedGCost = DIAG_COST;
										}
										else 
										{
											aAddedGCost = ADJ_COST;
										}
                                        
										aHoldGCost = mGCost[mParentX][mParentY] + aAddedGCost;

										if(aHoldGCost < mGCost[aX][aY])
										{
											mParentXList[aX][aY] = mParentX;
											mParentYList[aX][aY] = mParentY;
											mGCost[aX][aY] = aHoldGCost;

											for(int x = 1; x <= aTempListCount; x++)
											{
												if(mOpenX[mOpenList[x]] == aX && mOpenY[mOpenList[x]] == aY)
												{
													mTotCost[mOpenList[x]] = mGCost[aX][aY] + mHCost[mOpenList[x]];
													aOpenNode = x;
													//Reheapify open list!
													while(aOpenNode != 1)
													{
														if(mTotCost[mOpenList[aOpenNode]] < mTotCost[mOpenList[aOpenNode/2]])
														{
															aHoldOpen = mOpenList[aOpenNode/2];
															mOpenList[aOpenNode/2] = mOpenList[aOpenNode];
															mOpenList[aOpenNode] = aHoldOpen;
															aOpenNode /= 2;
														}
														else
														{
															break;
														}//14
													}//13
													break;
												}//12
											}//11
										}//10
									}//9
								}//8
							}//7
						}//6
					}//5
				}//4
			}//3
		}//2
		else
		{
			aExists = false;
			break;
		} 
		if(mTempList[pDestX][pDestY] > 0)
		{
			aExists = true;
			break;
		}
	}

	//The path exists! Now we walk backwards and store proper locations.
	if(aExists == true)
	{
		mPathLength = 0;
		aPathX = pDestX;
		aPathY = pDestY;

		do
		{
			aPathXTemp = mParentXList[aPathX][aPathY];	
			aPathY = mParentYList[aPathX][aPathY];
			aPathX = aPathXTemp;
			mPathLength++;
		}
		while(aPathX != pStartX || aPathY != pStartY);
        
		mPathX[0] = pStartX;
		mPathY[0] = pStartY;

		aPathX = pDestX;
		aPathY = pDestY;

		for(int i=mPathLength;i>0;i--)
		{
			mPathX[i] = aPathX;
			mPathY[i] = aPathY;

			aPathXTemp = mParentXList[aPathX][aPathY];		
			aPathY = mParentYList[aPathX][aPathY];
			aPathX = aPathXTemp;
		}
	}
	return aExists;
}