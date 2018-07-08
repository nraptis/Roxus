#include "TexSpline.h"
#include "Sprite.h"

TexSpline::TexSpline(void)
{
	mScale=1;
	mSprite=0;
	mOffset=0;
	mExpandAmount=0;
	mSpriteWidth=0;

	mNeedsRegenerate=false;
	mManualSpriteFit=false;
	mStretch=0;

	mManualInterval=false;
	mStart=0;
	mEnd=0;

	mList=0;
	mListSize=0;
	mListCount=0;

	mWidth=0;
	mWidthCount=0;
	mWidthSize=0;

	mTempList=0;
	mTempListCount=0;
	mTempListSize=0;

	mAngularThreshold=0.025f;
	mGranularity=-1.0f;
	
	mDrawCount=0;
}

TexSpline::~TexSpline(void)
{
	Clear();
	delete[]mList;
	delete[]mWidth;
	delete[]mTempList;

	mTempList=0;
	mWidth=0;
	mList=0;
}

float TexSpline::GetSpriteStretchFit(Sprite*theSprite,float theStartOffset,float theEndOffset)
{
	if(theSprite==0)theSprite=mSprite;
	if(mSprite==0)mSprite=theSprite;
	if(mChanged)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	float aReturn=1;
	if(theSprite&&mLength>0.25f&&mListCount>1)
	{
		if(theSprite->mHeight>0)
		{
			if(mScale>0.025f)
			{

				//TODO: FIGURE OUT HOW SCALE INFLUENCES THIS... GOD...

				float aEnd=theStartOffset+(mLength)*(mSprite->GetEndV()/(float)theSprite->mHeight);
				aReturn=(aEnd-fmodf(aEnd-theEndOffset,1.0f))-theStartOffset;
			}
			else
			{
				aReturn=0;
			}
		}
	}
	if(aReturn<1)aReturn=1;
	return aReturn;
}

float TexSpline::LengthToPos(float theLength)
{
	float aReturn=0;
	if(mChanged||mNeedsRegenerate)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	if(mListCount>1)
	{
		if(IsCircular())
		{
			theLength=fmod(theLength,mLength);
			if(theLength<0)theLength+=mLength;
		}
		if(theLength<0)theLength=0;
		if(theLength>mLength)theLength=mLength;
		int aStart=0;
		int aEnd=mListCount-1;
		int aMiddle;
		float *aListLen=mList+(mListSize)*4;
		float *aListPos=aListLen+mListSize;
		float aLength=theLength;
		while(aStart<=aEnd)
		{
			aMiddle=(aStart+aEnd)>>1;
			if(aListLen[aMiddle]>=aLength)aEnd=aMiddle-1;
			else aStart=aMiddle+1;
		}
		int aSlot=aSlot=aStart-1;
		if(aSlot<0)aSlot=0;
		aReturn=aListPos[aSlot+1];
		float aLenDiff=aListLen[aSlot+1]-aListLen[aSlot];
		if(aLenDiff>0.25f)
		{
			float aInterpolationPercent=1.0f-(aListLen[aSlot+1]-aLength)/aLenDiff;
			if(aInterpolationPercent<0)aInterpolationPercent=0;
			if(aInterpolationPercent>1)aInterpolationPercent=1;
			aReturn=aListPos[aSlot]+(aListPos[aSlot+1]-aListPos[aSlot])*aInterpolationPercent;
		}
	}
	return aReturn;
}

float TexSpline::PercentToPos(float thePercent)
{
	float aReturn=0;
	if(mChanged||mNeedsRegenerate)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	if(mListCount>1)
	{
		float aAdd=0;
		if(IsCircular())
		{
			aAdd=floorf(thePercent)*((float)mMax);
			thePercent=fmod(thePercent,1.0f);
			if(thePercent<0)thePercent+=1.0f;
		}
		if(thePercent<0)thePercent=0;
		if(thePercent>1)thePercent=1;
		int aStart=0;
		int aEnd=mListCount-1;
		int aMiddle;
		float *aListLen=mList+(mListSize)*4;
		float *aListPos=aListLen+mListSize;
		float aLength=thePercent*mLength;
		while(aStart<=aEnd)
		{
			aMiddle=(aStart+aEnd)>>1;
			if(aListLen[aMiddle]>=aLength)aEnd=aMiddle-1;
			else aStart=aMiddle+1;
		}
		int aSlot=aSlot=aStart-1;
		if(aSlot<0)aSlot=0;
		aReturn=aListPos[aSlot+1];
		float aLenDiff=aListLen[aSlot+1]-aListLen[aSlot];
		if(aLenDiff>0.25f)
		{
			float aInterpolationPercent=1.0f-(aListLen[aSlot+1]-aLength)/aLenDiff;
			if(aInterpolationPercent<0)aInterpolationPercent=0;
			if(aInterpolationPercent>1)aInterpolationPercent=1;
			aReturn=aListPos[aSlot]+(aListPos[aSlot+1]-aListPos[aSlot])*aInterpolationPercent;
		}
		aReturn+=aAdd;
	}
	return aReturn;
}

int TexSpline::GetAnchor(float thePos)
{
	if(mChanged||mNeedsRegenerate)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	int aReturn=0;
	if(mListCount>1)
	{

		int aStart=0;
		int aEnd=mListCount-1;
		int aMiddle;
		float *aListPos=mList+(mListSize)*5;
		while(aStart<=aEnd)
		{
			aMiddle=(aStart+aEnd)>>1;
			if(aListPos[aMiddle]>=thePos)aEnd=aMiddle-1;
			else aStart=aMiddle+1;
		}
		aReturn=aStart-1;
		if(aReturn<0)aReturn=0;
	}
	return aReturn;
}

float TexSpline::GetOffset(float pos)
{
	if(mChanged||mNeedsRegenerate)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	float aOffset=mOffset;
	if(mListCount>1&&mSprite&&mLength>0.25f)
	{
		float *aListLen=mList+(mListSize)*4;
		float *aListPos=mList+(mListSize)*5;
		float aMax=(float)mMax;
		if(IsClosed())
		{
			pos=fmodf(pos,aMax);
			if(pos<0)pos+=aMax;
		}
		if(pos<0)pos=0;
		if(pos>aMax)pos=aMax;
		int aSlot=GetAnchor(pos);
		float aDiff=aListPos[aSlot+1]-aListPos[aSlot];
		float aPercent=0;
		if(aDiff>0.0001f)aPercent=1.0f-((aListPos[aSlot+1]-pos)/aDiff);
		if(aPercent<0)aPercent=0;
		if(aPercent>1)aPercent=1;
		float aLength=aListLen[aSlot]+(aListLen[aSlot+1]-aListLen[aSlot])*aPercent;
		
		float aTU=mSprite->GetEndV();
		float aSpriteWidth=(float)mSprite->mHeight;
		if(aSpriteWidth<1)aSpriteWidth=1;
		
		float aMult;
		
		if(mManualSpriteFit)aMult=(aTU*mStretch)/mLength;
		else aMult=aTU/aSpriteWidth;
		if(mScale>0.025f)aMult/=mScale;
		else aMult=0;
		
		aOffset=mOffset + aLength * aMult;
	}
	return aOffset;
}

float TexSpline::GetSpriteStretchFit(Sprite *theSprite)
{
	if(theSprite==0)theSprite=mSprite;
	if(mSprite==0)mSprite=theSprite;
	if(mChanged||mNeedsRegenerate)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	float aReturn=1;
	if(theSprite&&mLength>0.25f&&theSprite->mHeight>0)aReturn=mLength/(float)theSprite->mHeight;
	return aReturn;
}

void TexSpline::SetWidth(float pos, float percent)
{
	if(percent>100)percent=100;
	if(percent<-100)percent=-100;
	mNeedsRegenerate=true;
	float *aPos=mWidth+mWidthSize;
	for(int i=0;i<mWidthCount;i++)
	{
		if(aPos[i]==pos)
		{
			mWidth[i]=percent;
			return;
		}
	}
	if(mWidthCount==mWidthSize)
	{
		mWidthSize=mWidthSize*2+1;
		float *aWidth=new float[mWidthSize*2];
		for(int i=0;i<mWidthCount;i++)aWidth[i]=mWidth[i];
		float *aNewPos=aWidth+mWidthSize;
		for(int i=0;i<mWidthCount;i++)aNewPos[i]=aPos[i];
		delete[]mWidth;
		mWidth=aWidth;
		aPos=aNewPos;
	}
	mWidth[mWidthCount]=percent;
	aPos[mWidthCount]=pos;
	mWidthCount++;
}

float TexSpline::Interpolate(float pos, int listID)
{
	if(mChanged||mNeedsRegenerate)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	float aReturn=0;
	if(listID>=0&&listID<=6&&mListCount>1)
	{
		if(mProperties&SPLINE_CLOSED)
		{
			pos=fmodf(pos,(float)mMax);
			if(pos<0)pos+=(float)mMax;
		}

		if(pos<0)pos=0;
		if(pos>(float)mMax)pos=(float)mMax;

		int aAnchor=GetAnchor(pos);
		float *aValue=mList+mListSize*listID;
		float *aListPos=mList+mListSize*5;
		float aPercent=1-(((aListPos[aAnchor+1]-pos)/(aListPos[aAnchor+1]-aListPos[aAnchor])));
		if(aPercent>1)aPercent=1;
		if(aPercent<0)aPercent=0;
		aReturn=aValue[aAnchor]+(aValue[aAnchor+1]-aValue[aAnchor])*aPercent;
	}
	return aReturn;
}

void TexSpline::Generate(Sprite *theSprite,bool isLinear,bool isCircular)
{
	mVertexCount=0;

	bool aChanged=(mChanged)||isLinear!=IsLinear()||isCircular!=IsClosed();
	if(aChanged)Spline::Solve(isLinear,isCircular);

	mChanged=false;
	mNeedsRegenerate=false;

	if(!mSprite)mSprite=theSprite;

	if(mPointCount<2||theSprite==0)return;
	if(theSprite->mWidth<=0||theSprite->mHeight<=0)return;

	float aSpriteWidth=(float)mSprite->mHeight;
	float aSpriteHeight=(float)mSprite->mWidth/2;

	mSpriteWidth=aSpriteHeight;

	float *aNewX,*aNewY,*aNewXNorm,*aNewYNorm,*aNewLen,*aNewPos;

	float aMax=(float)mMax;

	float *aHoldList=0;
	int aHoldListSize=0;

	if(mTempList)
	{
		aHoldListSize=mListSize;
		aHoldList=mList;
		mList=mTempList;
		mListSize=mTempListSize;
		mListCount=mTempListCount;
		mTempList=0;
	}

	if(mXCoef&&(aChanged||theSprite!=mSprite||mListCount==0))
	{
		int aLoops=0;
		mSprite=theSprite;
		mVertexCount=0;
		
		int aIndex=0;
		float aLastX=*mX,aLastY=*mY;
		//float aStripStartX=aLastX,aStripStartY=aLastY;
		float aPerpX=0,aPerpY=0,aLastPerpX=0,aLastPerpY=0;
		float aX,aY,aDiffX,aDiffY,aDist=0,aMid,aTemp,aPos;
		float aCount=(float)mMax,aSeek=0+SPLINE_SHORT_STEP,aMin=0;
		
		mListCount=0;
		
		if(mListSize<mMax*2+4)
		{
			mListSize=mMax*2+4;
			delete[]mList;
			mList=new float[mListSize*7];
		}

		float *aListX=mList;
		float *aListY=aListX+mListSize;
		float *aListXNorm=aListY+mListSize;
		float *aListYNorm=aListXNorm+mListSize;
		float *aListLen=aListYNorm+mListSize;
		float *aListPos=aListLen+mListSize;
		float *aListWidth=aListPos+mListSize;
		
		aListLen[0]=0;
		aListPos[0]=0;
		float aArc=0;
		float aTotalLength=0;
		if((mProperties&SPLINE_LINEAR)||(mPointCount==2&&
			
			//mProperties&SPLINE_MANUAL_TANGENTS

			//WE DO A MANUAL LINEAR CHECK...

			mXCoef[2]==0
			&&
			mXCoef[1]==0
			&&
			mYCoef[2]==0
			&&
			mYCoef[1]==0
			
			
			))
		{
			aLastX=mX[0];
			aLastY=mY[0];
			aX=mX[1];
			aY=mY[1];
			aDiffX=aX-aLastX;
			aDiffY=aY-aLastY;
			aArc=sqrtf(aDiffX*aDiffX+aDiffY*aDiffY);
			aTotalLength+=aArc;
			aPerpX=-aDiffY/aArc;
			aPerpY=aDiffX/aArc;
			aLastPerpX=aPerpX;
			aLastPerpY=aPerpY;
			aListPos[1]=1;
			aListLen[1]=aArc;

			aListX[0]=aLastX;
			aListY[0]=aLastY;
			aListXNorm[0]=aPerpX;
			aListYNorm[0]=aPerpY;

			aListX[1]=aX;
			aListY[1]=aY;
			aListXNorm[1]=aPerpX;
			aListYNorm[1]=aPerpY;
			
			mListCount=2;
			aLastX=aX;
			aLastY=aY;
			for(int i=2;i<mPointCount;i++)
			{
				aX=mX[i];
				aY=mY[i];
				aDiffX=aX-aLastX;
				aDiffY=aY-aLastY;
				aArc=sqrtf(aDiffX*aDiffX+aDiffY*aDiffY);
				aPerpX=-aDiffY/aArc;
				aPerpY=aDiffX/aArc;

				aListX[mListCount]=aLastX;
				aListY[mListCount]=aLastY;
				aListXNorm[mListCount]=aPerpX;
				aListYNorm[mListCount]=aPerpY;

				aListLen[mListCount]=aTotalLength;
				aListPos[mListCount]=(float)(i-1);
				aTotalLength+=aArc;
				mListCount++;
				
				aListX[mListCount]=aX;
				aListY[mListCount]=aY;
				aListXNorm[mListCount]=aPerpX;
				aListYNorm[mListCount]=aPerpY;
				
				aListLen[mListCount]=aTotalLength;
				aListPos[mListCount]=(float)(i);
				mListCount++;
				aLastX=aX;
				aLastY=aY;
			}
			if((mProperties&SPLINE_CLOSED)&&mListCount>2)
			{
				aX=mX[0];
				aY=mY[0];
				aDiffX=aX-aLastX;
				aDiffY=aY-aLastY;
				aArc=sqrtf(aDiffX*aDiffX+aDiffY*aDiffY);
				aPerpX=-aDiffY/aArc;
				aPerpY=aDiffX/aArc;

				aListX[mListCount]=aLastX;
				aListY[mListCount]=aLastY;
				aListXNorm[mListCount]=aPerpX;
				aListYNorm[mListCount]=aPerpY;

				aListLen[mListCount]=aTotalLength;
				aListPos[mListCount]=(float)(mPointCount-1);
				aTotalLength+=aArc;
				mListCount++;

				aListX[mListCount]=aX;
				aListY[mListCount]=aY;
				aListXNorm[mListCount]=aPerpX;
				aListYNorm[mListCount]=aPerpY;

				aListLen[mListCount]=aTotalLength;
				aListPos[mListCount]=(float)mPointCount;
				mListCount++;
				aLastX=aX;
				aLastY=aY;
			}
		}
		else
		{
			while(aSeek<aCount)
			{
				aIndex=(int)aSeek;
				aPos=aSeek-(float)aIndex;
				if(aIndex>=mMax)
				{
					aIndex=mMax-1;
					aPos=1;
				}
				aX=mX[aIndex];
				aY=mY[aIndex];
				aIndex=((aIndex<<1)+aIndex);
				aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
				aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
				aDiffX=aX-aLastX;
				aDiffY=aY-aLastY;
				aDist=aDiffX*aDiffX+aDiffY*aDiffY;
				while(aDist<1.0f&&aSeek<aCount)
				{
					aMin=aSeek;
					aSeek+=SPLINE_SHORT_STEP;
					aIndex=(int)aSeek;
					aPos=aSeek-(float)aIndex;
					if(aIndex>=mMax)
					{
						aIndex=mMax-1;
						aPos=1;
					}
					aX=mX[aIndex];
					aY=mY[aIndex];
					aIndex=((aIndex<<1)+aIndex);
					aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
					aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
					aDiffX=aX-aLastX;
					aDiffY=aY-aLastY;
					aDist=aDiffX*aDiffX+aDiffY*aDiffY;
					aLoops++;
				}
				aMid=(aSeek+aMin)*0.5f;
				while(fabsf(aMin-aSeek)>SPLINE_EPSILON)
				{
					aIndex=(int)aMid;
					aPos=aMid-(float)aIndex;
					if(aIndex>=mMax)
					{
						aIndex=mMax-1;
						aPos=1;
					}
					aX=mX[aIndex];
					aY=mY[aIndex];
					aIndex=((aIndex<<1)+aIndex);
					aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
					aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
					aDiffX=aX-aLastX;
					aDiffY=aY-aLastY;
					aDist=aDiffX*aDiffX+aDiffY*aDiffY;
					if(aDist<1.0f)aMin=aMid;
					else aSeek=aMid;
					aMid=(aSeek+aMin)*0.5f;
					aLoops++;
				}
				aLastPerpX=aX-aLastX;
				aLastPerpY=aY-aLastY;
				aLastX=aX;
				aLastY=aY;
				break;
			}
			if(fabsf(aLastPerpX)+fabsf(aLastPerpY)>0.5f)
			{
				mListCount=0;
				aArc=aDist;
				aTemp=aLastPerpX;
				aLastPerpX=-aLastPerpY;
				aLastPerpY=aTemp;
				
				aListX[mListCount]=aX;
				aListY[mListCount]=aY;
				aListXNorm[mListCount]=aLastPerpX;
				aListYNorm[mListCount]=aLastPerpY;
				
				mListCount++;
				while(aSeek<aCount)
				{
					aIndex=(int)aSeek;
					aPos=aSeek-(float)aIndex;
					if(aIndex>=mMax)
					{
						aIndex=mMax-1;
						aPos=1;
					}
					aX=mX[aIndex];
					aY=mY[aIndex];
					aIndex=((aIndex<<1)+aIndex);
					aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
					aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
					aDiffX=aX-aLastX;
					aDiffY=aY-aLastY;
					aDist=aDiffX*aDiffX+aDiffY*aDiffY;
					while(aDist<1.0f&&aSeek<aCount)
					{
						aLoops++;
						aMin=aSeek;
						aSeek+=SPLINE_SHORT_STEP;
						aIndex=(int)aSeek;
						aPos=aSeek-(float)aIndex;
						if(aIndex>=mMax)
						{
							aIndex=mMax-1;
							aPos=1;
						}
						aX=mX[aIndex];
						aY=mY[aIndex];
						aIndex=((aIndex<<1)+aIndex);
						aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
						aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
						aDiffX=aX-aLastX;
						aDiffY=aY-aLastY;
						aDist=aDiffX*aDiffX+aDiffY*aDiffY;
					}
					aMid=(aSeek+aMin)*0.5f;
					while(fabsf(aMin-aSeek)>SPLINE_EPSILON)
					{
						aIndex=(int)aMid;
						aPos=aMid-(float)aIndex;
						if(aIndex>=mMax)
						{
							aIndex=mMax-1;
							aPos=1;
						}
						aX=mX[aIndex];
						aY=mY[aIndex];
						aIndex=((aIndex<<1)+aIndex);
						aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
						aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
						aDiffX=aX-aLastX;
						aDiffY=aY-aLastY;
						aDist=aDiffX*aDiffX+aDiffY*aDiffY;
						if(aDist<1.0f)aMin=aMid;
						else aSeek=aMid;
						aMid=(aSeek+aMin)*0.5f;
						aLoops++;
					}
					aArc+=aDist;
					aPerpX=aX-aLastX;
					aPerpY=aY-aLastY;
					if((fabsf(aPerpX*aLastPerpX+aPerpY*aLastPerpY)>mAngularThreshold||(aArc>=mGranularity && mGranularity>=0))&&aDist>0.975f)
					{
						aLastPerpX=-aPerpY;
						aLastPerpY=aPerpX;
						if(mListCount==mListSize)
						{
							mListSize=mListSize*2+32;
							aNewX=new float[mListSize*7];//Account for our potential overflow at end...
							aNewY=aNewX+mListSize;
							aNewXNorm=aNewY+mListSize;
							aNewYNorm=aNewXNorm+mListSize;
							aNewLen=aNewYNorm+mListSize;
							aNewPos=aNewLen+mListSize;
							for(int i=0;i<mListCount;i++)aNewX[i]=aListX[i];
							for(int i=0;i<mListCount;i++)aNewY[i]=aListY[i];
							for(int i=0;i<mListCount;i++)aNewXNorm[i]=aListXNorm[i];
							for(int i=0;i<mListCount;i++)aNewYNorm[i]=aListYNorm[i];
							for(int i=0;i<mListCount;i++)aNewLen[i]=aListLen[i];
							for(int i=0;i<mListCount;i++)aNewPos[i]=aListPos[i];
							delete[]mList;
							mList=aNewX;
							aListX=aNewX;
							aListY=aNewY;
							aListXNorm=aNewXNorm;
							aListYNorm=aNewYNorm;
							aListLen=aNewLen;
							aListPos=aNewPos;
							aListWidth=aNewPos+mListSize;
						}
						aTotalLength+=aArc;
						aListX[mListCount]=aX;
						aListY[mListCount]=aY;
						aListXNorm[mListCount]=aLastPerpX;
						aListYNorm[mListCount]=aLastPerpY;
						aListLen[mListCount]=aTotalLength;
						aListPos[mListCount]=aMid;
						mListCount++;
						aArc=0;
					}
					aLastX=aX;
					aLastY=aY;
				}


				if(mListCount>=mListSize-2)
				{
					mListSize=mListSize+2;
					aNewX=new float[mListSize*7];//Account for our potential overflow at end...
					aNewY=aNewX+mListSize;
					aNewXNorm=aNewY+mListSize;
					aNewYNorm=aNewXNorm+mListSize;
					aNewLen=aNewYNorm+mListSize;
					aNewPos=aNewLen+mListSize;
					for(int i=0;i<mListCount;i++)aNewX[i]=aListX[i];
					for(int i=0;i<mListCount;i++)aNewY[i]=aListY[i];
					for(int i=0;i<mListCount;i++)aNewXNorm[i]=aListXNorm[i];
					for(int i=0;i<mListCount;i++)aNewYNorm[i]=aListYNorm[i];
					for(int i=0;i<mListCount;i++)aNewLen[i]=aListLen[i];
					for(int i=0;i<mListCount;i++)aNewPos[i]=aListPos[i];
					delete[]mList;
					mList=aNewX;
					aListX=aNewX;
					aListY=aNewY;
					aListXNorm=aNewXNorm;
					aListYNorm=aNewYNorm;
					aListLen=aNewLen;
					aListPos=aNewPos;
					aListWidth=aNewPos+mListSize;
				}


				aTotalLength+=aArc;
				aListX[mListCount]=aX;
				aListY[mListCount]=aY;
				aListXNorm[mListCount]=aLastPerpX;
				aListYNorm[mListCount]=aLastPerpY;
				aListLen[mListCount]=aTotalLength;
				aListPos[mListCount]=(float)mMax;
				mListCount++;
				if(mProperties&SPLINE_CLOSED)
				{
					aTotalLength++;
					aListX[mListCount]=aListX[0];
					aListY[mListCount]=aListY[0];
					aListXNorm[mListCount]=aListXNorm[0];
					aListYNorm[mListCount]=aListYNorm[0];
					aListLen[mListCount]=aTotalLength;
					aListPos[mListCount]=(float)mMax;
					aListPos[mListCount-1]=((float)mMax)-0.01f;
					mListCount++;
				}
			}
		}
		mLength=aTotalLength;
		for(int i=0;i<mListCount;i++)aListWidth[i]=1;
	}

	if(mListCount>1)
	{
		float *aListX=mList;
		float *aListY=aListX+mListSize;
		float *aListXNorm=aListY+mListSize;
		float *aListYNorm=aListXNorm+mListSize;
		float *aListLen=aListYNorm+mListSize;
		float *aListPos=aListLen+mListSize;
		float *aListWidth=aListPos+mListSize;

		if(mWidthCount>0)
		{
			float *aPos=mWidth+mWidthSize;
			int i,j;
			float aHoldWidth,aHoldPos;

			if(mProperties&SPLINE_CLOSED)
			{
				for(int i=0;i<mWidthCount;i++)
				{
					aPos[i]=fmodf(aPos[i],aMax);
					if(aPos[i]<0)aPos[i]+=aMax;
				}
			}

			for(i=1;i<mWidthCount;i++)
			{
				aHoldWidth=mWidth[i];
				aHoldPos=aPos[i];
				for(j=i-1;j>=0&&aPos[j]>aHoldPos;j--)
				{
					aPos[j+1]=aPos[j];
					mWidth[j+1]=mWidth[j];
				}
				mWidth[j+1]=aHoldWidth;
				aPos[j+1]=aHoldPos;
			}

			int aWidthIndex=0;

			float *aWidthPos=mWidth+mWidthSize;

			//Ok... first we skip past negative positions
			while(aWidthIndex<mWidthCount)
			{
				if(aWidthPos[aWidthIndex]>=0)break;
				aWidthIndex++;
			}

			int aFirstPositiveWidthPos=aWidthIndex;
			float aWidth;
			if(aWidthIndex==mWidthCount||mWidthCount==1)
			{
				aWidth=mWidth[mWidthCount-1];
				for(int i=0;i<mListCount;i++)
				{
					aListWidth[i]=aWidth;
				}
			}
			else if(aWidthPos[0]>=(float)mMax)
			{
				aWidth=mWidth[0];
				for(int i=0;i<mListCount;i++)
				{
					aListWidth[i]=aWidth;
				}
			}
			else
			{
				mTempList=mList;
				mTempListCount=mListCount;
				mTempListSize=mListSize;
				mListSize=mWidthCount+mListCount;
				if(mListSize<=aHoldListSize)
				{
					mListSize=aHoldListSize;
					mList=aHoldList;
				}
				else
				{
					delete[]aHoldList;
					mListSize+=100;
					mList=new float[mListSize*7];
				}
				aHoldList=0;
#define NULL_WIDTH (-100000000000000.0f)
				aNewX=mList;
				aNewY=aNewX+mListSize;
				aNewXNorm=aNewY+mListSize;
				aNewYNorm=aNewXNorm+mListSize;
				aNewLen=aNewYNorm+mListSize;
				aNewPos=aNewLen+mListSize;
				float *aNewWidth=aNewPos+mListSize;
				aNewX[0]=aListX[0];
				aNewY[0]=aListY[0];
				aNewXNorm[0]=aListXNorm[0];
				aNewYNorm[0]=aListYNorm[0];
				aNewLen[0]=aListLen[0];
				aNewPos[0]=aListPos[0];
				aNewWidth[0]=NULL_WIDTH;
				int aListIndex=1;
				int aNewListIndex=1;
				int aListIndexMinusOne;
				float aPercent,aDist;
				if(aWidthPos[aWidthIndex]==0)
				{
					aNewWidth[0]=mWidth[aWidthIndex];
					aWidthIndex++;
				}
				while(aWidthIndex<mWidthCount&&aListIndex<mListCount)
				{
					if(aListPos[aListIndex]>=aWidthPos[aWidthIndex])
					{
						aListIndexMinusOne=aListIndex-1;
						aDist=aListPos[aListIndex]-aListPos[aListIndexMinusOne];
						aPercent=1;
						if(aDist>SPLINE_EPSILON)aPercent=1-((aListPos[aListIndex]-aWidthPos[aWidthIndex])/aDist);
						if(aPercent<0)aPercent=0;
						if(aPercent>1)aPercent=1;
						aNewX[aNewListIndex]=aListX[aListIndexMinusOne]+(aListX[aListIndex]-aListX[aListIndexMinusOne])*aPercent;
						aNewY[aNewListIndex]=aListY[aListIndexMinusOne]+(aListY[aListIndex]-aListY[aListIndexMinusOne])*aPercent;
						aNewXNorm[aNewListIndex]=aListXNorm[aListIndexMinusOne]+(aListXNorm[aListIndex]-aListXNorm[aListIndexMinusOne])*aPercent;
						aNewYNorm[aNewListIndex]=aListYNorm[aListIndexMinusOne]+(aListYNorm[aListIndex]-aListYNorm[aListIndexMinusOne])*aPercent;
						aNewLen[aNewListIndex]=aListLen[aListIndexMinusOne]+(aListLen[aListIndex]-aListLen[aListIndexMinusOne])*aPercent;
						aNewPos[aNewListIndex]=aWidthPos[aWidthIndex];
						aNewWidth[aNewListIndex]=mWidth[aWidthIndex];
						if(aListPos[aListIndex]==aWidthPos[aWidthIndex])aListIndex++;
						aNewListIndex++;
						aWidthIndex++;
					}
					else
					{
						aNewX[aNewListIndex]=aListX[aListIndex];
						aNewY[aNewListIndex]=aListY[aListIndex];
						aNewXNorm[aNewListIndex]=aListXNorm[aListIndex];
						aNewYNorm[aNewListIndex]=aListYNorm[aListIndex];
						aNewLen[aNewListIndex]=aListLen[aListIndex];
						aNewPos[aNewListIndex]=aListPos[aListIndex];
						aNewWidth[aNewListIndex]=NULL_WIDTH;
						aNewListIndex++;
						aListIndex++;
					}
				}
				while(aListIndex<mListCount)
				{
					aNewX[aNewListIndex]=aListX[aListIndex];
					aNewY[aNewListIndex]=aListY[aListIndex];
					aNewXNorm[aNewListIndex]=aListXNorm[aListIndex];
					aNewYNorm[aNewListIndex]=aListYNorm[aListIndex];
					aNewLen[aNewListIndex]=aListLen[aListIndex];
					aNewPos[aNewListIndex]=aListPos[aListIndex];
					aNewWidth[aNewListIndex]=NULL_WIDTH;
					aNewListIndex++;
					aListIndex++;
				}
				aListX=aNewX;
				aListY=aNewY;
				aListXNorm=aNewXNorm;
				aListYNorm=aNewYNorm;
				aListLen=aNewLen;
				aListPos=aNewPos;
				aListWidth=aNewWidth;
				mListCount=aNewListIndex;
				if(mProperties&SPLINE_CLOSED)
				{
					aDist=aWidthPos[0]-aWidthPos[mWidthCount-1]+aMax;
					aPercent=((aWidthPos[0]-aListPos[0])/aDist);
					if(aPercent<0)aPercent=0;
					if(aPercent>1)aPercent=1;
					//if(aListWidth[0]==NULL_WIDTH)aListWidth[0]=mWidth[0]+(mWidth[mWidthCount-1]-mWidth[0])*aPercent;
					//if(aListWidth[mListCount-1]==NULL_WIDTH)aListWidth[mListCount-1]=mWidth[0]+(mWidth[mWidthCount-1]-mWidth[0])*aPercent;
					aWidth=mWidth[0]+(mWidth[mWidthCount-1]-mWidth[0])*aPercent;
					aListWidth[0]=aWidth;
					aListWidth[mListCount-1]=aWidth;
				}
				aListIndex=0;
				while(aListIndex<mListCount)
				{
					if(aListWidth[aListIndex]!=NULL_WIDTH)break;
					aListIndex++;
				}
				if(aListIndex<mListCount)
				{
					aWidth=aListWidth[aListIndex];
					aNewListIndex=aListIndex-1;
					if(aFirstPositiveWidthPos>0)
					{
						aDist=aListPos[aListIndex]-aWidthPos[aFirstPositiveWidthPos-1];
						if(aDist<SPLINE_EPSILON)aDist=SPLINE_EPSILON;
						while(aNewListIndex>=0)
						{
							aPercent=((aListPos[aNewListIndex]-aWidthPos[aFirstPositiveWidthPos-1])/aDist);
							if(aPercent<0)aPercent=0;
							if(aPercent>1)aPercent=1;
							aListWidth[aNewListIndex]=mWidth[aFirstPositiveWidthPos-1]+(aWidth-mWidth[aFirstPositiveWidthPos-1])*aPercent;
							aNewListIndex--;
						}
					}
					else
					{
						while(aNewListIndex>=0)
						{
							aListWidth[aNewListIndex]=aWidth;
							aNewListIndex--;
						}
					}
					int aPreviousIndex=aListIndex;
					do
					{
						while(aListIndex<mListCount)
						{
							if(aListWidth[aListIndex]!=NULL_WIDTH)break;
							aListIndex++;
						}
						if(aListIndex<mListCount)
						{
							if(aListIndex-aPreviousIndex>1)
							{
								aDist=aListPos[aListIndex]-aListPos[aPreviousIndex];
								if(aDist<SPLINE_EPSILON)aDist=SPLINE_EPSILON;
								for(int i=aPreviousIndex+1;i<aListIndex;i++)
								{
									aPercent=((aListPos[i]-aListPos[aPreviousIndex])/aDist);
									if(aPercent<0)aPercent=0;
									if(aPercent>1)aPercent=1;
									aListWidth[i]=aListWidth[aPreviousIndex]+(aListWidth[aListIndex]-aListWidth[aPreviousIndex])*aPercent;
								}
							}
							aPreviousIndex=aListIndex;
							aListIndex++;
						}
					}
					while(aListIndex<mListCount);
					if(aPreviousIndex<mListCount)
					{
						if(aWidthIndex<mWidthCount)
						{
							aDist=aWidthPos[aWidthIndex]-aListPos[aPreviousIndex];
							if(aDist<SPLINE_EPSILON)aDist=SPLINE_EPSILON;
							aListIndex=aPreviousIndex+1;
							while(aListIndex<mListCount)
							{
								aPercent=((aListPos[aListIndex]-aListPos[aPreviousIndex])/aDist);
								if(aPercent<0)aPercent=0;
								if(aPercent>1)aPercent=1;
								aListWidth[aListIndex]=aListWidth[aPreviousIndex]+(mWidth[aWidthIndex]-aListWidth[aPreviousIndex])*aPercent;
								aListIndex++;
							}
						}
						else
						{
							aWidth=aListWidth[aPreviousIndex];
							aPreviousIndex++;
							while(aPreviousIndex<mListCount)aListWidth[aPreviousIndex++]=aWidth;
						}
					}
				}
				else
				{
					aDist=aWidthPos[aFirstPositiveWidthPos]-aWidthPos[aFirstPositiveWidthPos-1];
					if(aDist<SPLINE_EPSILON)aDist=SPLINE_EPSILON;
					aNewListIndex=mListCount-1;
					aWidth=mWidth[aFirstPositiveWidthPos];
					while(aNewListIndex>=0)
					{
						aPercent=((aListPos[aNewListIndex]-aWidthPos[aFirstPositiveWidthPos-1])/aDist);
						if(aPercent<0)aPercent=0;
						if(aPercent>1)aPercent=1;
						aListWidth[aNewListIndex]=mWidth[aFirstPositiveWidthPos-1]+(aWidth-mWidth[aFirstPositiveWidthPos-1])*aPercent;
						aNewListIndex--;
					}
				}
			}
		}

		aSpriteHeight*=mScale;
		//aSpriteHeight+=mExpandAmount;

		float aTU=mSprite->GetEndV();
		float aTV=mSprite->GetEndU();
		
		float aU=mOffset;
		float aMult;

		if(mManualSpriteFit)aMult=(aTU*mStretch)/mLength;
		// Equivalent to SetStretchFactor(GetSpriteStretchFit(mSprite));
		else aMult=aTU/aSpriteWidth;
		if(mScale>0.025f)aMult/=mScale;
		else aMult=0;

		
		float aStart=0;
		float aEnd=aMax;
		if(mManualInterval)
		{
			aStart=mStart;
			aEnd=mEnd;
		}

		if(aStart<aEnd)
		{
			bool aLoopAround=false;
			if(IsClosed())
			{
				if((aEnd-aStart)>=aMax)
				{
					aStart=0;
					aEnd=aMax;
				}
				else
				{
					aStart=fmodf(aStart,aMax);
					aEnd=fmodf(aEnd,aMax);
					if(aStart<0)aStart+=aMax;
					if(aEnd<0)aEnd+=aMax;
					if(aEnd<aStart)
					{
						aLoopAround=true;
					}
				}
			}

			if(aStart<0)aStart=0;
			if(aStart>aMax)aStart=aMax;
			if(aEnd<0)aEnd=0;
			if(aEnd>aMax)aEnd=aMax;

			if(aStart!=aEnd)
			{
				mVBuffer.Clear();
				
				
				float aLength=mLength;
				if(aLength<1)aLength=1;

				int aEndIndex=GetAnchor(aEnd);
				int aStartIndex=GetAnchor(aStart);
				if(aLoopAround)
				{
					if(aStartIndex<aEndIndex)aStartIndex=aEndIndex;
				}
				else
				{
					if(aEndIndex<aStartIndex)aEndIndex=aStartIndex;
				}
				int aEndIndex1=aEndIndex+1;
				int aStartIndex1=aStartIndex+1;
				float aStartPercent=1-(((aListPos[aStartIndex1]-aStart)/(aListPos[aStartIndex1]-aListPos[aStartIndex])));
				float aEndPercent=1-(((aListPos[aEndIndex1]-aEnd)/(aListPos[aEndIndex1]-aListPos[aEndIndex])));
				if(aStartPercent<0)aStartPercent=0;
				if(aStartPercent>1)aStartPercent=1;
				if(aEndPercent<0)aEndPercent=0;
				if(aEndPercent>1)aEndPercent=1;
				float aStartX = aListX[aStartIndex]+(aListX[aStartIndex1]-aListX[aStartIndex])*aStartPercent;
				float aStartY = aListY[aStartIndex]+(aListY[aStartIndex1]-aListY[aStartIndex])*aStartPercent;
				float aStartWidth = aListWidth[aStartIndex]+(aListWidth[aStartIndex1]-aListWidth[aStartIndex])*aStartPercent;
				float aStartXNorm = aListXNorm[aStartIndex]+(aListXNorm[aStartIndex1]-aListXNorm[aStartIndex])*aStartPercent;
				float aStartYNorm = aListYNorm[aStartIndex]+(aListYNorm[aStartIndex1]-aListYNorm[aStartIndex])*aStartPercent;
				float aEndX = aListX[aEndIndex]+(aListX[aEndIndex1]-aListX[aEndIndex])*aEndPercent;
				float aEndY = aListY[aEndIndex]+(aListY[aEndIndex1]-aListY[aEndIndex])*aEndPercent;
				float aEndWidth = aListWidth[aEndIndex]+(aListWidth[aEndIndex1]-aListWidth[aEndIndex])*aEndPercent;
				float aEndXNorm = aListXNorm[aEndIndex]+(aListXNorm[aEndIndex1]-aListXNorm[aEndIndex])*aEndPercent;
				float aEndYNorm = aListYNorm[aEndIndex]+(aListYNorm[aEndIndex1]-aListYNorm[aEndIndex])*aEndPercent;
				aU=mOffset+(aListLen[aStartIndex]+(aListLen[aStartIndex1]-aListLen[aStartIndex])*aStartPercent)*aMult;
				
				mVBuffer.Add(aStartX+aStartXNorm*(aSpriteHeight*aStartWidth+mExpandAmount),aStartY+aStartYNorm*(aSpriteHeight*aStartWidth+mExpandAmount),0,aU);
				
				mVBuffer.Add(aStartX-aStartXNorm*(aSpriteHeight*aStartWidth+mExpandAmount),aStartY-aStartYNorm*(aSpriteHeight*aStartWidth+mExpandAmount),aTV,aU);
				
				mVertexCount=2;

				if(aEndIndex != aStartIndex)
				{
					aU=mOffset+aListLen[aStartIndex1]*aMult;
					
					mVBuffer.Add(aListX[aStartIndex1]+aListXNorm[aStartIndex1]*(aSpriteHeight*aListWidth[aStartIndex1]+mExpandAmount),aListY[aStartIndex1]+aListYNorm[aStartIndex1]*(aSpriteHeight*aListWidth[aStartIndex1]+mExpandAmount),0,aU);
					
					mVBuffer.Add(aListX[aStartIndex1]-aListXNorm[aStartIndex1]*(aSpriteHeight*aListWidth[aStartIndex1]+mExpandAmount),aListY[aStartIndex1]-aListYNorm[aStartIndex1]*(aSpriteHeight*aListWidth[aStartIndex1]+mExpandAmount),aTV,aU);
					
					mVertexCount=4;
					if(aLoopAround)
					{
						for(int i=aStartIndex+2;i<mListCount;i++)
						{
							aU=mOffset+aListLen[i]*aMult;
								 
							mVBuffer.Add(aListX[i]+aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aListY[i]+aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),0,aU);
										 
							mVBuffer.Add(aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aListY[i]-aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aTV,aU);
							mVertexCount+=2;
						}
						for(int i=0;i<=aEndIndex;i++)
						{
							aU=mOffset+aListLen[i]*aMult;
										 
							mVBuffer.Add(aListX[i]+aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aListY[i]+aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),0,aU);
							
							mVBuffer.Add(aListX[i]-aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aListY[i]-aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aTV, aU);
							
							mVertexCount+=2;
						}
					}
					else
					{
						for(int i=aStartIndex+2;i<=aEndIndex;i++)
						{
							aU=mOffset+aListLen[i]*aMult;
							
							mVBuffer.Add(aListX[i]+aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aListY[i]+aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),0,aU);
							
							mVBuffer.Add(aListX[i]-aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aListY[i]-aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount),aTV,aU);
										 
							mVertexCount+=2;
						}
					}
				}
				aU=mOffset+(aListLen[aEndIndex]+(aListLen[aEndIndex1]-aListLen[aEndIndex])*aEndPercent)*aMult;
				
				mVBuffer.Add(aEndX+aEndXNorm*(aSpriteHeight*aEndWidth+mExpandAmount),aEndY+aEndYNorm*(aSpriteHeight*aEndWidth+mExpandAmount),0,aU);
				
				mVertexCount+=2;
							 
				mVBuffer.Add(aEndX-aEndXNorm*(aSpriteHeight*aEndWidth+mExpandAmount),aEndY-aEndYNorm*(aSpriteHeight*aEndWidth+mExpandAmount),aTV,aU);
			}
			else
			{
				
				mVBuffer.Clear();
			}
		}
	}
	if(aHoldList)
	{
		delete[]aHoldList;
	}

	//gOut.Out("Final: mListCount=%d mVertexCount=%d", mListCount, mVertexCount);

}

void TexSpline::Draw(float x, float y)
{
	glPushMatrix();
	Translate(x,y);
	Draw();
	glPopMatrix();
}

void TexSpline::Draw()
{
	if(mNeedsRegenerate||mChanged)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	
	//glTexEnvf(GL_TEXTURE, GL TEXTURE WRAP S);
	if(mSprite)
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glEnable( GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,mSprite->mBindIndex);
		mVBuffer.Draw();
		glDisable( GL_TEXTURE_2D);
	}
}

void TexSpline::DrawControlPoints(Color theColor)
{
	SetColor(theColor);
	for(int i=0;i<mPointCount;i++)
	{
		DrawRect(mX[i]-3,mY[i]-3,7,7);
	}
}

void TexSpline::DrawAnchorPoints(Color theColor)
{
	if(mNeedsRegenerate||mChanged)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	if(mListCount>1&&mSprite)
	{
		float aSpriteHeight=mSpriteWidth*mScale;
		SetColor(theColor);
		float *aListX=mList;
		float *aListY=aListX+mListSize;
		float *aListXNorm=aListY+mListSize;
		float *aListYNorm=aListXNorm+mListSize;
		float *aListWidth=mList+mListSize*6;
		for(int i=0;i<mListCount;i++)
		{
			DrawRect(aListX[i]+aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount)-1,aListY[i]+aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount)-1,3,3);
			DrawRect(aListX[i]-aListXNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount)-1,aListY[i]-aListYNorm[i]*(aSpriteHeight*aListWidth[i]+mExpandAmount)-1,3,3);
			DrawRect(aListX[i]-1,aListY[i]-1,3,3);
		}
	}
}

void TexSpline::DrawMarkers(Color anchorPointColor, Color controlPointColor)
{
	DrawAnchorPoints(anchorPointColor);
	DrawControlPoints(controlPointColor);
}

void TexSpline::DrawTriangles()
{
	if(mNeedsRegenerate||mChanged)
	{
		mNeedsRegenerate=false;
		Generate(mSprite,IsLinear(),IsClosed());
	}
	
	//glTexEnvf(GL_TEXTURE, GL TEXTURE WRAP S);
	if(mSprite)
	{
		mVBuffer.DrawTriangles();
	}
}