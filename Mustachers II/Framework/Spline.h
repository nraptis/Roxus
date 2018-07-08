#pragma once
#include "stdafx.h"
#include <math.h>

#define SPLINE_LINEAR 0x001
#define SPLINE_CLOSED 0x002
#define SPLINE_MANUAL_TANGENTS 0x004


//For the Chrysler Apps...

#ifdef CHRYSLER_APP
	#define SPLINE_EPSILON 0.0000025f
	#define SPLINE_SHORT_STEP 0.0025f
#else
	#define SPLINE_EPSILON 0.0001f
	#define SPLINE_SHORT_STEP 0.01f
#endif



class Buffer;

class Spline
{
public:
	Spline(void);
	virtual ~Spline(void);
    
    void                    Clone(Spline *pSpline);

	//Add points to the spline.
	void					Add(float x,float y);
	inline void				Add(float x,int y){Add(x,(float)y);}
	inline void				Add(int x,float y){Add((float)x,y);}
	inline void				Add(int x,int y){Add((float)x,(float)y);}
	inline void				AddPoint(float x,float y){Add(x,y);}
	inline void				AddPoint(float x,int y){Add(x,(float)y);}
	inline void				AddPoint(int x,float y){Add((float)x,y);}
	inline void				AddPoint(int x,int y){Add((float)x,(float)y);}
	inline void				Add(double x, double y){Add((float)x,(float)y);}
	//Framework specific.
	inline void				Add(FPoint p){Add(p.mX,p.mY);}
	inline void				AddPoint(FPoint p){Add(p.mX,p.mY);}
	inline void				operator+=(FPoint theFPoint){Add(theFPoint);}
	//-

	//Manually set the tangent of the spline at a given index.
	//(Do this before solving the spline - a smooth curve will
	//be generated that is 'tugged' in the direction of the tangent
	//by the magnitude of the tangent).
	//Note: The spline also uses more memory once this has been called.
	void					SetTangent(int theIndex,float xtan,float ytan);
	inline void				SetTangent(int theIndex,int xtan,int ytan){SetTangent(theIndex,(float)xtan,(float)ytan);}
	inline void				SetTangent(int theIndex,float xtan,int ytan){SetTangent(theIndex,xtan,(float)ytan);}
	inline void				SetTangent(int theIndex,int xtan,float ytan){SetTangent(theIndex,(float)xtan,ytan);}
	//Framework specific
	inline void				SetTangent(int theIndex,FPoint tan){SetTangent(theIndex,tan.mX,tan.mY);}
	//
	
	//Maybe we wanna add a point AND set a tangent for it!
	inline void				Add(float x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	
    
    ////
    //
	//Framework specific
    //
    ////
    
	inline void				Add(FPoint p, FPoint tan){Add(p.mX,p.mY,tan.mX,tan.mY);}
	inline void				Add(FPoint p, float tanx, float tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(FPoint p, int tanx, float tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(FPoint p, float tanx, int tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(FPoint p, int tanx, int tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(float x, float y, FPoint tan){Add(x,y,tan.mX,tan.mY);}
	inline void				Add(int x, float y, FPoint tan){Add(x,y,tan.mX,tan.mY);}
	inline void				Add(float x, int y, FPoint tan){Add(x,y,tan.mX,tan.mY);}
	inline void				Add(int x, int y, FPoint tan){Add(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(FPoint p, FPoint tan){AddPoint(p.mX,p.mY,tan.mX,tan.mY);}
	inline void				AddPoint(FPoint p, float tanx, float tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(FPoint p, int tanx, float tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(FPoint p, float tanx, int tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(FPoint p, int tanx, int tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(float x, float y, FPoint tan){AddPoint(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(int x, float y, FPoint tan){AddPoint(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(float x, int y, FPoint tan){AddPoint(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(int x, int y, FPoint tan){AddPoint(x,y,tan.mX,tan.mY);}
	//

	//Spline Editor functions!
	//
	//
	//Add a point at a given index. (later points
	//automatically pushed back)
	void					Insert(int theIndex,float x, float y);
	inline void				Insert(int theIndex,float x, int y){Insert(theIndex,x,(float)y);}
	inline void				Insert(int theIndex,int x, float y){Insert(theIndex,(float)x,y);}
	inline void				Insert(int theIndex,int x, int y){Insert(theIndex,(float)x,(float)y);}
	inline void				InsertPoint(int theIndex,float x, float y){Insert(theIndex,x,y);}
	inline void				InsertPoint(int theIndex,float x, int y){Insert(theIndex,x,(float)y);}
	inline void				InsertPoint(int theIndex,int x, float y){Insert(theIndex,(float)x,y);}
	inline void				InsertPoint(int theIndex,int x, int y){Insert(theIndex,(float)x,(float)y);}

	//Framework specific
	inline void				Insert(int theIndex,FPoint p){Insert(theIndex,p.mX,p.mY);}
	inline void				InsertPoint(int theIndex,FPoint p){Insert(theIndex,p.mX,p.mY);}
	//

	//Change the position of a point already on the spline.
	void					SetPoint(int theIndex,float x, float y);
	inline void				SetPoint(int theIndex,float x, int y){SetPoint(theIndex,x,(float)y);}
	inline void				SetPoint(int theIndex,int x, float y){SetPoint(theIndex,(float)x,y);}
	inline void				SetPoint(int theIndex,int x, int y){SetPoint(theIndex,(float)x,(float)y);}

	inline void				MovePoint(int theIndex,float x, float y){SetPoint(theIndex,x,y);}
	inline void				MovePoint(int theIndex,float x, int y){SetPoint(theIndex,x,(float)y);}
	inline void				MovePoint(int theIndex,int x, float y){SetPoint(theIndex,(float)x,y);}
	inline void				MovePoint(int theIndex,int x, int y){SetPoint(theIndex,(float)x,(float)y);}

	//Framework specific
	inline void				SetPoint(int theIndex,FPoint p){SetPoint(theIndex,p.mX,p.mY);}
	inline void				MovePoint(int theIndex,FPoint p){SetPoint(theIndex,p.mX,p.mY);}
	//


	//DON'T USE THIS UNLESS YOU KNOW WHAT YOU'RE DOING
	void					SetCoefs(int theIndex, float xa, float xb, float xc, float ya, float yb, float yc);
	inline void				SetCoefs(int theIndex, double xa, double xb, double xc, double ya, double yb, double yc){SetCoefs(theIndex,(float)xa,(float)xb,(float)xc,(float)ya,(float)yb,(float)yc);}


	void					InvertH(float theCenter=400);


	void					Translate(float theXDistance, float theYDistance);
	inline void				Translate(FPoint theDistance){Translate(theDistance.mX,theDistance.mY);}


	//Removes the point/tangent at a given index.
	void					Delete(int theIndex);
    
	//
	//End editor functions!

	//Change the number of points the spline can hold.
	//If you Size() the spline the the number of points you will add
	//before you add them, it will be faster.
	//You can also remove end-points by shrinking the size.
	void					Size(int size);


	//file contents as argument! (must be null terminated)
	void					ImportData(char *theData);

	//Destroy the spline and free up memory.
	void					Clear();

	//Solve() or CalculateSpline() will generate the actual spline.
	//This should be called after all of the points are added and
	//all of the manual tangents are set!
	//
	//Circular means that the spline will be closed (The last point will be
	//connected to the first point by a smooth curve)
	//
	virtual void			Solve(bool linear=false,bool circular=false);
	//
	//***
	//Everything beyond this point should only be used
	//after Solve() or CalculateSpline() have been called!
	//***
	//
    
	//Fetch a point along the spline. [Min() to Max()] AKA [0 to mPointCount-1]
	//Get(2.5) will yield the point interpolated half-way
	//between the 2nd and 3rd points that were added.
	void					Get(float pos,float &x,float &y);
	void					Get(int pos,float &x,float &y);
	float					GetX(float pos);//{float aX,aY;Get(pos,aX,aY);return aX;}
	float					GetY(float pos);//{float aX,aY;Get(pos,aX,aY);return aY;}
	//Framework specific.
	inline FPoint			Get(float pos){FPoint aReturn;Get(pos,aReturn.mX,aReturn.mY);return aReturn;}
	inline FPoint			Get(int pos){FPoint aReturn;Get(pos,aReturn.mX,aReturn.mY);return aReturn;}
	inline void				GetPoint(float pos,float &x,float &y){Get(pos,x,y);}
	inline void				GetPoint(int pos,float &x,float &y){Get(pos,x,y);}
	inline FPoint			GetPoint(float pos){FPoint aReturn;Get(pos,aReturn.mX,aReturn.mY);return aReturn;}
	inline FPoint			GetPoint(int pos){FPoint aReturn;Get(pos,aReturn.mX,aReturn.mY);return aReturn;}
	inline FPoint			operator[](float theSlot){return Get(theSlot);}
	inline FPoint			operator[](int theSlot){return Get(theSlot);}
	//

	//Find the closest position (or point) on the spline to a given point.
	//(This isn't extremely fast)
	float					GetClosestPosition(float x, float y, float &pDist);
	inline float			GetClosestPosition(float x, float y){float aDist;return GetClosestPosition(x,y,aDist);}
	inline float			GetClosestPosition(float x, int y){return GetClosestPosition((float)x,(float)y);}
	inline float			GetClosestPosition(int x, float y){return GetClosestPosition((float)x,y);}
	inline float			GetClosestPosition(int x, int y){return GetClosestPosition(x,(float)y);}
	
	//Framework specific.
	inline float			GetClosestPosition(FPoint theFPoint){return GetClosestPosition(theFPoint.mX,theFPoint.mY);}
	inline FPoint			GetClosestPoint(FPoint theFPoint){return GetClosestPoint(theFPoint.mX,theFPoint.mY);}
	
	inline FPoint			GetClosestPoint(FPoint theFPoint, float &pDist){return Get(GetClosestPosition(theFPoint.mX,theFPoint.mY,pDist));}
	
	inline FPoint			GetClosestPoint(float x, float y){return Get(GetClosestPosition(x,y));}
	inline FPoint			GetClosestPoint(int x, int y){return GetClosestPoint((float)x,(float)y);}
	//

	int						GetClosestControlIndex(float x, float y, float &dist);

	//Get the tangent of the spline at a given position.
	void					Tan(float pos,float &x,float &y);
	void					Tan(int pos,float &x,float &y);
	//Framework specific.
	inline FPoint			Tan(int pos){FPoint aReturn;Tan(pos,aReturn.mX,aReturn.mY);return aReturn;}
	inline FPoint			Tan(float pos){FPoint aReturn;Tan(pos,aReturn.mX,aReturn.mY);return aReturn;}
	//

	//Get the length of the spline between two points
	//(end==-1 will seek to the end of the spline)
	//float					GetLength(float start=0,float end=-1);

	//Get the angle of the slope of the spline at a given position.
	float					Rot(float pos);
	inline float			Rotation(float pos){return Rot(pos);}

	//Steps along the spline by a given linear distance. Returns false when you pass
	//the end of the spline.
	bool					GetNextFPoint(float &x, float &y, float &t,float theDistance=1.0f);
	bool					GetNextFPointSloppy(float &x, float &y, float &t,float theDistance=1.0f);

	//The maximum and minimum positions of the spline.
	//for(float i=Min();i<=Max();i+=0.1f){}
	inline float			Max(){if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);return (float)mMax;}
	inline float			Min(){return 0.0f;}
	
    
    int						mMax;

	bool					mChanged;
    
    float                   GetLength(float pStart,float pEnd);
    
	

	//Info about the spline's last calculation.
	inline bool				IsClosed(){return (mProperties&SPLINE_CLOSED)!=0;}
	inline bool				IsCircular(){return IsClosed();}
	inline bool				IsLinear(){return (mProperties&SPLINE_LINEAR)!=0;}
	inline bool				IsUsingManualTangents(){return (mProperties&SPLINE_MANUAL_TANGENTS)!=0;}

	void					SetClosed(bool theState){mProperties&=(~SPLINE_CLOSED);if(theState)mProperties|=SPLINE_CLOSED;}
	void					SetLinear(bool theState){mProperties&=(~SPLINE_LINEAR);if(theState)mProperties|=SPLINE_LINEAR;}

	//Points that were added to the spline, stored as arrays of floats!
	float					*mX;
	float					*mY;
    //Number of points that were added to the spline.
	int						mPointCount;
	inline int				PointCount(){return mPointCount;}
    
    
    void                    Save(Buffer *pBuffer);
    void                    Load(Buffer *pBuffer);
    
    
    

	//Internal affairs.
//protected:
	void					Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theTemp,float*theCoef,bool linear,bool circular);
	void					Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theCoef,bool linear,bool circular);
	int						mSize;
	float					*mXCoef;
	float					*mYCoef;
	float					*mTangent;
	float					mLength;
	unsigned int			mProperties;
    
};