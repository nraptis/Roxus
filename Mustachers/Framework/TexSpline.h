#pragma once

#include "stdafx.h"
#include "Spline.h"
#include "VertexBuffer.h"

#define ONLY_DRAW_100 1
#undef ONLY_DRAW_100

/********************************
/////////////////////////////////
//------------Notes------------//
/////////////////////////////////

A sprite must be given to the TexSpline at some point. As long
as one is passed as a parameter to any method, it will be stored.
(Recommended to just do SetSprite() Or manual Generate() at some point)

You shouldn't ever call Solve() on a TexSpline. (Won't do anything different if you do)

As a general rule, don't call any Get functions before all your
points and tangents are set.
********************************/

class TexSpline : public Spline
{
public:
	TexSpline(void);
	virtual ~TexSpline(void);

	//The TexSpline will only be generated (and thus draw)
	//between the start and end positions specified here.
	inline void				SetInterval(float theStartPos,float theEndPos){mStart=theStartPos;mEnd=theEndPos;mManualInterval=true;mNeedsRegenerate=true;}
	inline void				SetInterval(){AutomateInterval();}

	//Only use Generate() on TexSpline, not Solve()
	void					Solve(bool linear=false,bool circular=false){Spline::Solve(linear,circular);mChanged=true;mNeedsRegenerate=true;}

	//Sets up the TexSpline to be drawn. This will
	//automatically get called, so don't bother.
	void					Generate(Sprite *theSprite,bool isLinear=false,bool isCircular=false);

	inline void				Regenerate(){Generate(mSprite,IsLinear(),IsClosed());}

	//Sets the number of times that a sprite will repeat.
	//Usually used with GetSpriteStretchFit().
	inline void				SetStretch(float theFactor=1){mStretch=theFactor;mManualSpriteFit=true;mNeedsRegenerate=true;}
	inline void				SetRepeats(float theRepeatCount=1){SetStretch(theRepeatCount);}

	//The number of repeats required to draw
	//our sprite to scale along the spline.
	float					GetSpriteStretchFit(Sprite*theSprite=0);

	//The number of repeats to fit the sprite as closely as possible
	//to scale while starting and ending at the given ofsets.
	//(Train tracks meet up with eachother)
	//(Circular spline start/end match up GetSpriteStretchFit(mSprite,0,0));
	float					GetSpriteStretchFit(Sprite*theSprite,float theStartOffset,float theEndOffset);

	//[Needs Comment]
	void					SetWidth(float pos, float percent);
	void					Flatten(){mWidthCount=0;mNeedsRegenerate=true;}	

	//If we're using intervals, this lets us start
	//drawing from the beginning of our interval.
	//(Vines in Mario)
	inline void				SetStartOffset(float theStartPos, float theStartOffset=0){mOffset=0;SetOffset(theStartOffset-GetOffset(theStartPos));mNeedsRegenerate=true;}

	//Determines how smoothly the spline will curve.
	//0:	 maximally smooth.
	//0.025: recommended number (default value).
	//0.1:   slightly blocky, improved performance.
	//0.5:   extremely blocky.
	//1.0:   only start and end points will be used.
	inline void				SetAngularThreshold(float theThreshold=0.025f){mAngularThreshold=theThreshold;mNeedsRegenerate=true;}

	//The sprite that will be drawn along our spline.
	//You must call this if you don't call any other
	//methods that take a sprite as an argument.
	inline void				SetSprite(Sprite *theSprite){mSprite=theSprite;mNeedsRegenerate=true;}

	//The texture coordinate that the sprite will start drawing at.
	//[0-1] (Wraps around outside of this range)
	inline void				SetOffset(float theOffset){mOffset=fmodf(theOffset,1);if(mOffset<0)mOffset+=1;mNeedsRegenerate=true;}

	//If you have called SetInterval or SetStretchFactor, you may
	//revert back to automatic calculations with these functions.
	inline void				AutomateStretchFactor(){mManualSpriteFit=false;mNeedsRegenerate=true;}
	inline void				AutomateInterval(){mManualInterval=false;mNeedsRegenerate=true;}

	//[Needs Comment]
	inline void				Scale(float scale){mScale=scale;mNeedsRegenerate=true;}

	//Get the draw offset at a given position.
	float					GetOffset(float pos=0);

	//Convert a percent [0-1] to a position along the spline.
	//This is useful to move at a constant/controlled speed.
	float					PercentToPos(float thePercent);

	inline void				SetGranularity(float theGranularity=10){mGranularity=theGranularity;mNeedsRegenerate=true;}

	//Draws a sprite along the spline.
	virtual void			Draw();
	virtual void			Draw(float x, float y);

	//Draws control points and anchor points.
	//(Control points green, anchor points red)
	void					DrawMarkers(Color anchorPointColor=Color(1,0,0), Color controlPointColor=Color(0,1,0));
	
	void					DrawTriangles();

	void					DrawControlPoints(Color theColor=Color(0,1,0,1));
	void					DrawAnchorPoints(Color theColor=Color(1,0,0,1));

	//[Needs Comment]
	inline void				Expand(float theWidth){mExpandAmount=theWidth;mNeedsRegenerate=true;}
	inline void				Widen(float theWidth){Expand(theWidth);}

	//0 = x
	//1 = y
	//2 = xnorm
	//3 = ynorm
	//4 = dist 
	//5 = pos
	//6 = height
	float					Interpolate(float pos, int listID);

	float					*GetListX(){return mList;}
	float					*GetListY(){return mList+mListSize;}
	float					*GetListXNorm(){return mList+mListSize*2;}
	float					*GetListYNorm(){return mList+mListSize*3;}
	float					*GetListDist(){return mList+mListSize*4;}
	float					*GetListPos(){return mList+mListSize*5;}
	float					*GetListHeight(){return mList+mListSize*6;}
	
	float					LengthToPos(float theLength);
	inline float			DistanceToPos(float theLength){return LengthToPos(theLength);}

	inline float			PosToLength(float thePos){return Interpolate(thePos,4);}
	inline float			PosToDistance(float thePos){return PosToLength(thePos);}


	//Technically all this stuff should be protected.

	Sprite					*mSprite;
	
	float					mSpriteWidth;
	
	bool					mManualInterval;
	float					mStart;
	float					mEnd;

	float					mScale;

	bool					mManualSpriteFit;
	float					mStretch;

	bool					mNeedsRegenerate;

	float					mAngularThreshold;
	float					mGranularity;

	float					mOffset;
	
	int						GetAnchor(float thePos);

	float					*mList;
	int						mListSize;
	int						mListCount;

	float					*mTempList;
	int						mTempListSize;
	int						mTempListCount;

	float					*mWidth;
	int						mWidthCount;
	int						mWidthSize;

	float					mExpandAmount;

	VertexBuffer			mVBuffer;
	int						mVertexCount;
	int						mDrawCount;
};
