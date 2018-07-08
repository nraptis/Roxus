//
//  FMotionPathTemplate.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/23/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "FMotionPath.h"
#include "FFile.h"
#include "core_graphics.h"
#include "core_includes.h"

#include "FAnimation.h"
#include "FSpline.h"
#include "FMath.h"

FMotionPathTemplateNode::FMotionPathTemplateNode()
{
    mTime = 0;
    mTimeSleep = 5;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mAnimationFunction = ANIMATION_TYPE_AUTOMATIC;
    
    mRotation = 0.0f;
    
    mScale = 1.0f;
    
    mTanInX = -50.0f;
    mTanInY = 10.0f;
    mTanInAuto = true;
    
    mTanOutX = 60.0f;
    mTanOutY = -40.0f;
    mTanOutAuto = true;
    
    mR = 1.0f;
    mG = 1.0f;
    mB = 1.0f;
    mA = 1.0f;

    mTrackScreen = false;
    mTrackSideX = 1;
    mTrackSideY = 1;
    mTrackOffsetX = 0.0f;
    mTrackOffsetY = 0.0f;
}

FMotionPathTemplate::FMotionPathTemplate()
{
	mInterpResult = 0;
	mInterpLHS = 0;
	mInterpRHS = 0;
	mInterpPercent = 0.0f;

	
	mPathAbs = 0;
    
    mCircular = false;
    
    mSelectedAllignTimer = 0;
}

FMotionPathTemplate::~FMotionPathTemplate()
{
    Clear();
}


void FMotionPathTemplate::Update()
{
    mSelectedAllignTimer++;
    if(mSelectedAllignTimer >= 40)mSelectedAllignTimer = 0;
}

void FMotionPathTemplate::Draw()
{
    if(mList.mCount > 0)
    {
		Graphics::SetColor(0.15f, 0.15f, 0.15f, 1.0f);
        DrawEdges(3.0f);
        
		Graphics::SetColor(0.65f, 0.65f, 0.65f, 1.0f);
        DrawEdges(1.0f);
        
		Graphics::SetColor(0.15f, 0.65f, 0.15f, 1.0f);
        DrawPoints(8.0f);
        
		Graphics::SetColor(0.45f, 1.0f, 0.45f, 1.0f);
		DrawPoints(4.0f);
    }
    
	Graphics::SetColor();
}


int FMotionPathTemplate::Count()
{
	return mList.mCount;
}

void FMotionPathTemplate::DrawTriangles()
{
		if((mTriangleData.mCount > 0) && (mList.mCount > 0))
		{
			mTriangleDataXY.Reset();
			mTriangleDataDraw.Reset();

			float aX = 0.0f;
			float aY = 0.0f;

			for(int i = 0; i < mList.mCount; i++)
			{

				aX = Get(i)->mX;
				aY = Get(i)->mY;

				//mTriangleDataXY.Add(aX, aY);

				mTriangleDataDraw.SetXY(i, aX, aY);

			}

			for(int i = 0; i < (mTriangleData.mCount - 2); i += 3)
			{
				int aIndex1 = mTriangleData.Get(i + 0);
				int aIndex2 = mTriangleData.Get(i + 1);
				int aIndex3 = mTriangleData.Get(i + 2);


				if(((aIndex1 >= 0) && (aIndex1 < mList.mCount)) && ((aIndex2 >= 0) && (aIndex2 < mList.mCount)) && ((aIndex3 >= 0) && (aIndex3 < mList.mCount)))
				{
					float aX1 = Get(aIndex1)->mX;
					float aY1 = Get(aIndex1)->mY;

					float aX2 = Get(aIndex2)->mX;
					float aY2 = Get(aIndex2)->mY;

					float aX3 = Get(aIndex3)->mX;
					float aY3 = Get(aIndex3)->mY;

					Graphics::SetColor(0.15f, 0.15f, 0.15f, 0.66f);
					Graphics::DrawTriangle2D(aX1, aY1, aX2, aY2, aX3, aY3);
				}
			}
		}
}

void FMotionPathTemplate::DrawEdges(float pSize)
{
    if(mList.mCount > 1)
    {
        if(mCircular)
        {
            float aX = 0.0f;
            float aY = 0.0f;
			float aLastX = Get(mList.mCount - 1)->mX;
			float aLastY = Get(mList.mCount - 1)->mY;
            
            for(int i=0;i< mList.mCount;i++)
            {
                aX = Get(i)->mX;
                aY = Get(i)->mY;
                
				Graphics::DrawLine(aLastX, aLastY, aX, aY, pSize);
                
                aLastX = aX;
                aLastY = aY;
            }
        }
        else
        {
            float aX = 0.0f;
            float aY = 0.0f;
            float aLastX = Get(0)->mX;
            float aLastY = Get(0)->mY;
            
            for(int i=1;i< mList.mCount;i++)
            {
                aX = Get(i)->mX;
                aY = Get(i)->mY;
                
				Graphics::DrawLine(aLastX, aLastY, aX, aY, pSize);
                
                aLastX = aX;
                aLastY = aY;
            }
        }
    }
    
}

void FMotionPathTemplate::DrawPoints(float pSize, int pSelectedPoint)
{
    DrawPointsUnselected(pSize, pSelectedPoint);
    DrawPointsSelected(pSize * 2.0f, pSelectedPoint);
}

void FMotionPathTemplate::DrawPointsSelected(float pSize, int pSelectedPoint)
{
    
    if((pSelectedPoint >= 0) && (pSelectedPoint < Count()))
    {
		float aX = Get(pSelectedPoint)->mX;
		float aY = Get(pSelectedPoint)->mY;
        
        float aSelX = aX;
        float aSelY = aY;
        
		Graphics::SetColor(1.0f, 0.15f, 0.15f, 0.5f);
        Graphics::OutlineRect(aSelX - pSize, aSelY - pSize, pSize * 2, pSize * 2, 4);
        
		Graphics::SetColor(0.15f, 0.65f, 0.65f, 0.5f);
        Graphics::OutlineRect(aSelX - pSize, aSelY - pSize, pSize * 2, pSize * 2, 2);
        
        
        float aEpsilon = (0.4f);
        
        if(mSelectedAllignTimer >= 0 && mSelectedAllignTimer <= 60)
        {
            bool aBump = false;
            
			for(int i = 0; i<mList.mCount; i++)
            {
				if(i != pSelectedPoint)
				{
					aX = Get(i)->mX;
					aY = Get(i)->mY;


					float aDist = (aX - aSelX);
					if(aDist < 0.0f)aDist = -aDist;

					if(aDist <= aEpsilon)
					{
						aBump = true;

						Graphics::SetColor(1.0f, 0.45f, 0.45f, 0.5f);
						Graphics::DrawLine(aX - 16.0f, aY, aX + 16.0f, aY, 3);
					}
				}
            }
            
            if(aBump)
            {
				Graphics::SetColor(1.0f, 0.2f, 0.4f, 0.5f);
                Graphics::DrawLine(aSelX - 16.0f, aSelY, aSelX + 16.0f, aSelY, 2);
            }
        }
        
        if(mSelectedAllignTimer >= 0 && mSelectedAllignTimer <= 100)
        {
            bool aBump = false;
            
			for(int i = 0; i<mList.mCount; i++)
            {
				if(pSelectedPoint != i)
				{
					aX = Get(i)->mX;
					aY = Get(i)->mY;

					float aDist = (aY - aSelY);
					if(aDist < 0.0f)aDist = -aDist;

					if(aDist <= aEpsilon)
					{
						aBump = true;

						Graphics::SetColor(1.0f, 0.45f, 0.45f, 0.5f);
						Graphics::DrawLine(aX, aY - 16.0f, aX, aY + 10.0f, 3);
					}
				}
            }
            
            if(aBump)
            {
				Graphics::SetColor(1.0f, 0.2f, 0.4f, 0.5f);
                Graphics::DrawLine(aSelX, aSelY - 16.0f, aSelX, aSelY + 16.0f, 2);
            }
        }
        
        
        //Graphics::DrawPoint(Get(pSelectedPoint)->mX, Get(pSelectedPoint)->mY, pSize);
    }
}

void FMotionPathTemplate::DrawPointsUnselected(float pSize, int pSelectedPoint)
{
	for(int i = 0; i<mList.mCount; i++)
    {
        if(i != pSelectedPoint)
        {
            Graphics::DrawPoint(Get(i)->mX, Get(i)->mY, pSize);
        }
    }
}

void FMotionPathTemplate::DrawTangents(float pSize, int pSelectedPoint, int pSelectedTangent)
{
    DrawTangentsUnselected(pSize, pSelectedPoint, pSelectedTangent);
    DrawTangentsSelected(pSize * 2.0f, pSelectedPoint, pSelectedTangent);
}

void FMotionPathTemplate::DrawTangentsSelected(float pSize, int pSelectedPoint, int pSelectedTangent)
{
    
	if((pSelectedPoint >= 0) && (pSelectedPoint < mList.mCount))
    {
        float aX1 = 0.0f;
        float aY1 = 0.0f;
        
        float aX2 = 0.0f;
        float aY2 = 0.0f;
        
        
		aX1 = Get(pSelectedPoint)->mX;
        aY1 = Get(pSelectedPoint)->mY;
        
        if(pSelectedTangent <= 0)
        {
            aX2 = aX1 + Get(pSelectedPoint)->mTanInX;
            aY2 = aY1 + Get(pSelectedPoint)->mTanInY;
        }
        else
        {
            aX2 = aX1 + Get(pSelectedPoint)->mTanOutX;
            aY2 = aY1 + Get(pSelectedPoint)->mTanOutY;
        }
        Graphics::DrawLine(aX1, aY1, aX2, aY2, 2.0f);
        
        //Graphics::DrawPoint(aX2, aY2, pSize);
        
        Graphics::DrawPoint(aX2, aY2, pSize);
    }
    
}

void FMotionPathTemplate::DrawTangentsUnselected(float pSize, int pSelectedPoint, int pSelectedTangent)
{
    
    /*
    
    FSpline aSpline;
    for(int i=0;i< mList.mCount;i++)
    {
        aSpline.Add(Get(i)->mX, Get(i)->mY);
    }
    
    aSpline.SetClosed(true);
    
    for(int i=0;i<aSpline.mPointCount;i++)
    {
        
        float aRot = aSpline.Rot(((float)i));// + 80.0f;
        
        //FVec2 aTan = aSpline.Tan(i);
        
		if(i < mList.mCount)
        {
			Get(i)->mTanInX = Sin(aRot) * 17.0f; //aTan.mX * 0.3f;
            Get(i)->mTanInY = -Cos(aRot) * 17.0f; //aTan.mY * 0.3f;
     
            Get(i)->mTanOutX =  Sin(aRot + 160.0f) * 14.0f; //-aTan.mX * 0.3f;
            Get(i)->mTanOutY = -Cos(aRot + 160.0f) * 14.0f;//-aTan.mY * 0.3f;
        }
    }
    
    */
    
    
    
    float aX1 = 0.0f;
    float aY1 = 0.0f;
    
    float aX2 = 0.0f;
    float aY2 = 0.0f;
    
    for(int i=0;i< mList.mCount;i++)
    {
        aX1 = Get(i)->mX;
        aY1 = Get(i)->mY;
        
        if((pSelectedPoint != i) || (pSelectedTangent > 0))
        {
            aX2 = aX1 + Get(i)->mTanInX;
            aY2 = aY1 + Get(i)->mTanInY;
            
            Graphics::DrawLine(aX1, aY1, aX2, aY2, 2.0f);
            Graphics::DrawPoint(aX2, aY2, pSize);
            
        }
        
        if((pSelectedPoint != i) || (pSelectedTangent <= 0))
        {
            aX2 = aX1 + Get(i)->mTanOutX;
            aY2 = aY1 + Get(i)->mTanOutY;
            
            Graphics::DrawLine(aX1, aY1, aX2, aY2, 2.0f);
            Graphics::DrawPoint(aX2, aY2, pSize);
        }
    }
}

void FMotionPathTemplate::DrawNaturalSpline()
{
	if(mList.mCount > 0)
	{
		mTestSpline.Clear();

		EnumList(FMotionPathTemplateNode, aNode, mList)
		{
			mTestSpline.Add(aNode->mX, aNode->mY);
		}

		float aLastX = 0.0f;
		float aLastY = 0.0f;

		mTestSpline.Get(0.0f, aLastX, aLastY);

		float aX = aLastX;
		float aY = aLastY;

		for(float aPos = 0.05f; aPos <= mTestSpline.Max(); aPos += 0.05f)
		{
			mTestSpline.Get(aPos, aX, aY);

			Graphics::DrawPoint(mTestSpline.GetX(aPos), mTestSpline.GetY(aPos), 4);

			Graphics::DrawLine(aLastX, aLastY, aX, aY);

			aLastX = aX;
			aLastY = aY;

		}
	}
}


void FMotionPathTemplate::Clear()
{
	mTriangleData.Clear();

	FreeList(FMotionPathTemplateNode, mList);



    //delete [] mNode;
    
    //mCount=0;
    //mSize=0;
    
   // mNode=0;
}

FMotionPathTemplateNode *FMotionPathTemplate::Get(int pIndex)
{
	FMotionPathTemplateNode *aResult = 0;

	if(pIndex < 0)
	{
		aResult = 0;
	}
	else if(pIndex < mList.mCount)
	{
		aResult = (FMotionPathTemplateNode *)(mList.Fetch(pIndex));
	}
	else

	{
			for(int i = mList.mCount; i <= (pIndex + 1); i++)
		{
			AddPoint(0.0f, 0.0f);
		}

		return (FMotionPathTemplateNode *)(mList.Last());
	}

    return aResult;
}


void FMotionPathTemplate::AddPoint(float pX, float pY)
{

	FMotionPathTemplateNode *aNode = new FMotionPathTemplateNode();
	aNode->mX = pX;
	aNode->mY = pY;
	mList.Add(aNode);

}

void FMotionPathTemplate::AddEdge(float pX1, float pY1, float pX2, float pY2)
{
    if(mList.mCount == 0)
    {
        AddPoint(pX1, pY1);
        AddPoint(pX2, pY2);
    }
    else
    {
		float aFirstX = Get(0)->mX;
        float aFirstY = Get(0)->mY;
        
        
		float aLastX = Get(mList.mCount - 1)->mX;
		float aLastY = Get(mList.mCount - 1)->mY;
        
        //float aDi
        
        float aD1_1 = DistanceSquared(pX1, pY1, aLastX, aLastY);
        float aD1_2 = DistanceSquared(pX1, pY1, aFirstX, aFirstY);
        
        float aD2_1 = DistanceSquared(pX2, pY2, aLastX, aLastY);
        float aD2_2 = DistanceSquared(pX2, pY2, aFirstX, aFirstY);
        
        if((aD1_1 >= 1.0f) && (aD1_2 >= 1.0f))
        {
            AddPoint(pX1, pY1);
        }
        
        if((aD2_1 >= 1.0f) && (aD2_2 >= 1.0f))
        {
            AddPoint(pX2, pY2);
        }
        
    }
    
}

void FMotionPathTemplate::SetPoint(int pIndex, float pX, float pY)
{
    if(pIndex >= 0)
    {
		Get(pIndex)->mX = pX;
        Get(pIndex)->mY = pY;
    }
}

void FMotionPathTemplate::SetAbsoluteTanIn(int pIndex, float pX, float pY)
{
    if(pIndex >= 0)
    {
        FMotionPathTemplateNode *aNode = Get(pIndex);
        
        if(aNode)
        {
            float aDiffX = pX - aNode->mX;
            float aDiffY = pY - aNode->mY;
        
            aNode->mTanInX = aDiffX;
            aNode->mTanInY = aDiffY;
        
            Log("Set Tan In (%f, %f)\n", aNode->mTanInX, aNode->mTanInY);
        }
    }
}

FMotionPathTemplate *FMotionPathTemplate::GetPathAbs()
{
    if(mPathAbs == 0)
    {
        mPathAbs = new FMotionPathTemplate();
        mPathAbs->Clone(this);
    }
    
    return mPathAbs;
}

void FMotionPathTemplate::SetPathAbs(FMotionPathTemplate *pPathAbs)
{
    if(mPathAbs)
    {
        if(mPathAbs == pPathAbs)
        {
            return;
        }
    }
    
    if(pPathAbs != 0)
    {
        mPathAbs = pPathAbs->Clone();
    }
    
    if(mPathAbs == 0)
    {
        mPathAbs = new FMotionPathTemplate();
        mPathAbs->Clone(this);
    }
}



void FMotionPathTemplate::SetAbsoluteTanOut(int pIndex, float pX, float pY)
{
    if(pIndex >= 0)
    {
        Get(pIndex)->mTanOutX = (pX - Get(pIndex)->mX);
        Get(pIndex)->mTanOutY = (pY - Get(pIndex)->mY);
    }
}

void FMotionPathTemplate::SetAbsoluteTan(int pIndex, int pSide, float pX, float pY)
{
    
    Log("Set Absolute Tan(%d, %d, %f, %f)\n", pIndex, pSide, pX, pY);
    
    if(pSide <= 0)SetAbsoluteTanIn(pIndex, pX, pY);
    else SetAbsoluteTanOut(pIndex, pX, pY);
}


/*
void FMotionPathTemplate::Size(int pSize)
{
    if(pSize != mSize)
    {
        if(pSize <= 0)
        {
            Clear();
        }
        else
        {
			if(mList.mCount >= pSize)mCount = pSize;

            FMotionPathTemplateNode *aNew = new FMotionPathTemplateNode[pSize];
            
            for(int i=0;i< mList.mCount;i++)aNew[i] = mNode[i];
            
            delete[]mNode;
            
            mNode = aNew;
            mSize = pSize;

            
        }
    }
}*/


int FMotionPathTemplate::GetClosestPointIndex(float pX, float pY, float &pDist)
{
    int aResult = -1;
    
    if(mList.mCount > 0)
    {
        aResult = 0;
        
        float aDiffX = Get(0)->mX - pX;
        float aDiffY = Get(0)->mY - pY;
        
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        pDist = aDist;
        
        for(int i=1;i< mList.mCount;i++)
        {
            aDiffX = Get(i)->mX - pX;
            aDiffY = Get(i)->mY - pY;
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if(aDist < pDist)
            {
                pDist = aDist;
                aResult = i;
            }
        }
    }
    
    return aResult;
}

int FMotionPathTemplate::GetClosestTanInIndex(float pX, float pY, float &pDist)
{
    int aResult = -1;
    if(mList.mCount > 0)
    {
        float aX = Get(0)->mX + Get(0)->mTanInX;
        float aY = Get(0)->mY + Get(0)->mTanInY;
        float aDiffX = aX - pX;
        float aDiffY = aY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        aResult = 0;
        pDist = aDist;
        for(int i=1;i< mList.mCount;i++)
        {
            aX = Get(i)->mX + Get(i)->mTanInX;
            aY = Get(i)->mY + Get(i)->mTanInY;
            aDiffX = aX - pX;
            aDiffY = aY - pY;
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if(aDist < pDist)
            {
                pDist = aDist;
                aResult = i;
            }
        }
    }
    return aResult;
}

int FMotionPathTemplate::GetClosestTanOutIndex(float pX, float pY, float &pDist)
{
    int aResult = -1;
    if(mList.mCount > 0)
    {
        float aX = Get(0)->mX + Get(0)->mTanOutX;
        float aY = Get(0)->mY + Get(0)->mTanOutY;
        float aDiffX = aX - pX;
        float aDiffY = aY - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        aResult = 0;
        pDist = aDist;
        for(int i=1;i< mList.mCount;i++)
        {
            aX = Get(i)->mX + Get(i)->mTanOutX;
            aY = Get(i)->mY + Get(i)->mTanOutY;
            aDiffX = aX - pX;
            aDiffY = aY - pY;
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if(aDist < pDist)
            {
                pDist = aDist;
                aResult = i;
            }
        }
    }
    return aResult;
}

int FMotionPathTemplate::GetClosestTanIndex(float pX, float pY, float &pDist)
{
    int aResult = -1;
    
    float aDistIn = pDist;
    float aDistOut = pDist;
    
    int aIndexIn = GetClosestTanInIndex(pX, pY, aDistIn);
    int aIndexOut = GetClosestTanOutIndex(pX, pY, aDistOut);
    
    if(aDistOut < aDistIn)
    {
        aResult = aIndexOut;
        pDist = aDistOut;
    }
    else
    {
        aResult = aIndexIn;
        pDist = aDistIn;
    }
    
    return aResult;
}

int FMotionPathTemplate::GetClosestTanSide(float pX, float pY)
{
    int aResult = 0;
    
    float aDistIn = 512.0f * 512.0f;
    float aDistOut = aDistIn;
    
    //int aIndexIn = GetClosestTanInIndex(pX, pY, aDistIn);
    //int aIndexOut = GetClosestTanOutIndex(pX, pY, aDistOut);
    
    if(aDistOut < aDistIn)
    {
        aResult = 1;
    }
    
    return aResult;
}

void FMotionPathTemplate::Clone(FMotionPathTemplate *pPath)
{
    if(pPath)
    {
		FXMLTag *aTag = pPath->SaveXML("tag");

		LoadXML(aTag);

		delete aTag;


        //FFile aFile;
        //pPath->Save(&aFile);
        //Load(&aFile);
    }
}

FXMLTag	*FMotionPathTemplate::SaveXML(const char *pName)
{
	FXMLTag *aTag = new FXMLTag(pName);


	aTag->AddParamInt("count", mList.mCount);
	aTag->AddParamBool("circular", mCircular);



	FXMLTag *aNodeListTag = new FXMLTag("path_node_list");
	*aTag += aNodeListTag;


	EnumList(FMotionPathTemplateNode, aNode, mList)
	{
		FXMLTag *aNodeTag = new FXMLTag("path_node");
		*aNodeListTag += aNodeTag;


		aNodeTag->AddParamSafeFloat("x", aNode->mX);
		aNodeTag->AddParamSafeFloat("y", aNode->mY);

		aNodeTag->AddParamSafeFloat("tan_in_x", aNode->mTanInX);
		aNodeTag->AddParamSafeFloat("tan_in_y", aNode->mTanInY);

		aNodeTag->AddParamSafeFloat("tan_out_x", aNode->mTanOutX);
		aNodeTag->AddParamSafeFloat("tan_out_y", aNode->mTanOutY);

		aNodeTag->AddParamBool("tan_in_auto", aNode->mTanInAuto);
		aNodeTag->AddParamBool("tan_out_auto", aNode->mTanOutAuto);
        
        
        
        aNodeTag->AddParamSafeFloat("rotation", aNode->mRotation);
        
        
        
        aNodeTag->AddParamBool("track_screen", aNode->mTrackScreen);
        
        aNodeTag->AddParamSafeFloat("track_off_x", aNode->mTrackOffsetX);
        aNodeTag->AddParamSafeFloat("track_off_y", aNode->mTrackOffsetY);
        
        aNodeTag->AddParamInt("tan_out_x", aNode->mTrackSideX);
        aNodeTag->AddParamInt("tan_out_x", aNode->mTrackSideY);
        
        aNodeTag->AddParamInt("track_side_x", aNode->mTanOutX);
        aNodeTag->AddParamInt("track_side_y", aNode->mTanOutX);
        
        aNodeTag->AddParamInt("time", aNode->mTime);
        aNodeTag->AddParamInt("time_sleep", aNode->mTimeSleep);
	}


	FXMLTag *aTriListTag = new FXMLTag("path_triangle_list");
	*aTag += aTriListTag;

	for(int i = 0; i < (mTriangleData.mCount - 2); i+=3)
	{
		//int aTriangleData = mTriangleData.mIndex[i];

		FXMLTag *aTriangleTag = new FXMLTag("triangle");
		*aTriListTag += aTriangleTag;

		int aIndex1 = mTriangleData.Get(i + 0);
		int aIndex2 = mTriangleData.Get(i + 1);
		int aIndex3 = mTriangleData.Get(i + 2);

		aTriangleTag->AddParamInt("i1", aIndex1);
		aTriangleTag->AddParamInt("i2", aIndex2);
		aTriangleTag->AddParamInt("i3", aIndex3);
	}

	return aTag;
}

void FMotionPathTemplate::LoadXML(FXMLTag *pTag)
{
	Clear();

	if(pTag)
	{

		//int aCount = pTag->GetParamInt("count", 0);
		mCircular = pTag->GetParamInt("circular", false);



		EnumTagsMatching(pTag, aNodeListTag, "path_node_list")
		{



			EnumTagsMatching(aNodeListTag, aNodeTag, "path_node")
			{
				FMotionPathTemplateNode *aNode = new FMotionPathTemplateNode();
				mList.Add(aNode);

				aNode->mX = aNodeTag->GetParamSafeFloat("x", 0.0f);
				aNode->mY = aNodeTag->GetParamSafeFloat("y", 0.0f);
				aNode->mTanInX = aNodeTag->GetParamSafeFloat("tan_in_x", 0.0f);
				aNode->mTanInY = aNodeTag->GetParamSafeFloat("tan_in_y", 0.0f);
				aNode->mTanOutX = aNodeTag->GetParamSafeFloat("tan_out_x", 0.0f);
                aNode->mTanOutY = aNodeTag->GetParamSafeFloat("tan_out_y", 0.0f);
                
                
               
                

				aNode->mTanInAuto = aNodeTag->GetParamBool("tan_in_auto", 0.0f);
				aNode->mTanOutAuto = aNodeTag->GetParamBool("tan_out_auto", 0.0f);
                
                 aNode->mRotation = aNodeTag->GetParamSafeFloat("rotation", 0.0f);
                
                aNode->mTrackScreen = aNodeTag->GetParamInt("track_screen", false);
                
                aNode->mTrackOffsetX = aNodeTag->GetParamSafeFloat("track_off_x", 0.0f);
                aNode->mTrackOffsetY = aNodeTag->GetParamSafeFloat("track_off_y", 0.0f);
                
                
                aNode->mTrackSideX = aNodeTag->GetParamSafeFloat("track_side_x", 0.0f);
                aNode->mTrackSideY = aNodeTag->GetParamSafeFloat("track_side_y", 0.0f);
                
                
                aNode->mTime = aNodeTag->GetParamInt("time", 0);
                aNode->mTimeSleep = aNodeTag->GetParamInt("time_sleep", 0);
                
			}

		}

		EnumTagsMatching(pTag, aTriListTag, "path_triangle_list")
		{



			EnumTagsMatching(aTriListTag, aTriangleTag, "triangle")
			{

				int aIndex1 = aTriangleTag->GetParamInt("i1", -1);
				int aIndex2 = aTriangleTag->GetParamInt("i2", -1);
				int aIndex3 = aTriangleTag->GetParamInt("i3", -1);


				if((aIndex1 != -1) && (aIndex2 != -1) && (aIndex3 != -1))
				{
					mTriangleData.Add(aIndex1);
					mTriangleData.Add(aIndex2);
					mTriangleData.Add(aIndex3);

				}
			}
		}
	}
}

void FMotionPathTemplate::Save(FFile *pFile)
{

	//FRegFile aReg;
	//Save(&aReg);
	//aReg.Save(pFile);


}

void FMotionPathTemplate::Load(FFile *pFile)
{
	//Clear();
	//FRegFile aReg;
	//aReg.Load(pFile);
	//Load(&aReg);
}

float FMotionPathTemplate::GetPointX(int pIndex)
{
    float aResult = 0.0f;
    if((pIndex >= 0) && (pIndex < mList.mCount))aResult = Get(pIndex)->mX;
    return aResult;
}

float FMotionPathTemplate::GetPointY(int pIndex)
{
    float aResult = 0.0f;
    if((pIndex >= 0) && (pIndex < mList.mCount))aResult = Get(pIndex)->mY;
    return aResult;
}

float FMotionPathTemplate::GetAbsoluteTanInX(int pIndex)
{
    float aResult = 0.0f;
    if((pIndex >= 0) && (pIndex < mList.mCount))aResult = Get(pIndex)->mX + Get(pIndex)->mTanInX;
    return aResult;
}

float FMotionPathTemplate::GetAbsoluteTanInY(int pIndex)
{
    float aResult = 0.0f;
    if((pIndex >= 0) && (pIndex < mList.mCount))aResult = Get(pIndex)->mY + Get(pIndex)->mTanInY;
    return aResult;
}

float FMotionPathTemplate::GetAbsoluteTanOutX(int pIndex)
{
    float aResult = 0.0f;
    if((pIndex >= 0) && (pIndex < mList.mCount))aResult = Get(pIndex)->mX + Get(pIndex)->mTanOutX;
    return aResult;
}

float FMotionPathTemplate::GetAbsoluteTanOutY(int pIndex)
{
    float aResult = 0.0f;
    if((pIndex >= 0) && (pIndex < mList.mCount))aResult = Get(pIndex)->mY + Get(pIndex)->mTanOutY;
    return aResult;
}

float FMotionPathTemplate::GetAbsoluteTanX(int pIndex, int pSide)
{
    if(pSide <= 0)return GetAbsoluteTanInX(pIndex);
    else return GetAbsoluteTanOutX(pIndex);
}

float FMotionPathTemplate::GetAbsoluteTanY(int pIndex, int pSide)
{
    if(pSide <= 0)return GetAbsoluteTanInY(pIndex);
    else return GetAbsoluteTanOutY(pIndex);
}


int FMotionPathTemplate::GetNextIndex(int pIndex)
{
    int aResult = 0;
    if(mList.mCount > 0)
    {
        aResult = (pIndex + 1);
        if(aResult >= mList.mCount)aResult = 0;
        else if(aResult < 0) aResult = (mList.mCount - 1);
    }
    return aResult;
}

int FMotionPathTemplate::GetPrevIndex(int pIndex)
{
    int aResult = 0;
    if(mList.mCount > 0)
    {
        aResult = (pIndex - 1);
        if(aResult < 0) aResult = (mList.mCount - 1);
        else if(aResult >= mList.mCount)aResult = 0;
    }
    return aResult;
}

int FMotionPathTemplate::NodeDelete(int pIndex)
{
    int aResult = pIndex;
    
    if((pIndex >= 0) && (pIndex < mList.mCount))
    {
		FMotionPathTemplateNode *aNode = Get(pIndex);
		
		//DELETE
		mList.Remove(aNode);
    }
    
    if(mList.mCount > 0)
    {
        
        if(aResult < 0)
        {
            aResult = (mList.mCount - 1);
        }
        else if(aResult >= mList.mCount)
        {
            aResult = 0;
        }
    }
    
    return aResult;
}

FMotionPathTemplateNode	*FMotionPathTemplate::GetNodeForTime(int pTime)
{
	FMotionPathTemplateNode *aResult = 0;


	EnumList(FMotionPathTemplateNode, aNode, mList)
	{
		if(aNode->mTime == pTime)
		{
			aResult = aNode;
		}
	}

	if(aResult == 0)
	{
		aResult = new FMotionPathTemplateNode();
		aResult->mTime = pTime;
		mList.Add(aResult);
	}

	return aResult;
}

FMotionPathTemplateNode	*FMotionPathTemplate::Interpolate(int pTime)
{
	if(mInterpResult == 0)mInterpResult = new FMotionPathTemplateNode();

	int aBestRHS = -1;
	int aBestLHS = -1;


	int aDist = 0;

	mInterpLHS = 0;
	mInterpRHS = 0;

	mInterpPercent = 0.5f;


	EnumList(FMotionPathTemplateNode, aNode, mList)
	{
		if(aNode->mTime <= pTime)
		{
			aDist = (pTime - aNode->mTime);

			if((aDist < aBestLHS) || (aBestLHS == -1))
			{
				aBestLHS = aDist;
				mInterpLHS = aNode;
			}

		}

		if(aNode->mTime > pTime)
		{
			aDist = (aNode->mTime - pTime);

			if((aDist < aBestRHS) || (aBestRHS == -1))
			{
				aBestRHS = aDist;
				mInterpRHS = aNode;
			}

		}
	}


	if((mInterpLHS != 0) && (mInterpRHS != 0))
	{
		int aSpan = (mInterpRHS->mTime - mInterpLHS->mTime);

		mInterpPercent = ((float)(pTime - mInterpLHS->mTime)) / ((float)aSpan);


		//Log("Left[%d] %d Right[%d] (%d) (%f%%)\n", mInterpLHS->mTime, pTime, mInterpRHS->mTime, aSpan, mInterpPercent);


		float aPercent = (mInterpPercent);

		aPercent = FAnimation::ApplyFunction(mInterpLHS->mAnimationFunction, aPercent);

		//mInterpPercent

		mInterpResult->mX = (mInterpLHS->mX + (mInterpRHS->mX - mInterpLHS->mX) * aPercent);
		mInterpResult->mY = (mInterpLHS->mY + (mInterpRHS->mY - mInterpLHS->mY) * aPercent);


		mInterpResult->mRotation = (mInterpLHS->mRotation + (mInterpRHS->mRotation - mInterpLHS->mRotation) * aPercent);

		mInterpResult->mScale = (mInterpLHS->mScale + (mInterpRHS->mScale - mInterpLHS->mScale) * aPercent);


		mInterpResult->mR = (mInterpLHS->mR + (mInterpRHS->mR - mInterpLHS->mR) * aPercent);
		mInterpResult->mG = (mInterpLHS->mG + (mInterpRHS->mG - mInterpLHS->mG) * aPercent);
		mInterpResult->mB = (mInterpLHS->mB + (mInterpRHS->mB - mInterpLHS->mB) * aPercent);
		mInterpResult->mA = (mInterpLHS->mA + (mInterpRHS->mA - mInterpLHS->mA) * aPercent);


		//mInterpPercent = 1.0f;

	}
	else
	{
		FMotionPathTemplateNode *aEdge = 0;
		if(mInterpRHS != 0)aEdge = mInterpRHS;
		if(mInterpLHS != 0)aEdge = mInterpLHS;

		if(aEdge)
		{
			mInterpResult->mX = aEdge->mX;
			mInterpResult->mY = aEdge->mY;

			mInterpResult->mRotation = aEdge->mRotation;

			mInterpResult->mScale = aEdge->mScale;

			mInterpResult->mR = aEdge->mR;
			mInterpResult->mG = aEdge->mG;
			mInterpResult->mB = aEdge->mB;
			mInterpResult->mA = aEdge->mA;


		}
		
		mInterpPercent = 1.0f;
	}
	
	
	return mInterpResult;
}




int FMotionPathTemplate::NodeInsert(FMotionPathTemplateNode *pNode, int pIndex)
{
	int aResult = pIndex;

	mList.Insert(pNode, pIndex);
	/*
    int aResult = 0;
    if(mList.mCount <= 0)
    {
        if(mSize <= 0)Size(1);
        mNode[0] = pNode;
        mList.mCount = 1;
    }
    else if(mList.mCount == 1)
    {
        if(mSize <= 1)Size(2);
        mList.mCount = 2;
        
        if(pIndex <= 0)
        {
            mNode[1] = mNode[0];
            mNode[0] = pNode;
            aResult = 0;
        }
        else
        {
            mNode[1] = pNode;
            aResult = 1;
        }
    }
    else
    {
        if((mList.mCount + 1) >= (mSize))
        {
            Size(mList.mCount + (mList.mCount / 2) + 1);
        }
        
        if(pIndex < 0)pIndex = 0;
        if(pIndex > mList.mCount)pIndex = mList.mCount;
        
        
        //int aFloor = (pIndex + 1);
        int aFloor = pIndex;// + 1;
        
        for(int i=mCount;i>=aFloor;i--)
        {
            mNode[i] = mNode[i - 1];
            
        }
        
        mNode[pIndex] = pNode;
        aResult = pIndex;
        
        mList.mCount++;
    }
    //if()
	*/
    return aResult;
}

int FMotionPathTemplate::NodeInsert(int pIndex)
{
    int aResult = 0;
    
	FMotionPathTemplateNode *aNode = new FMotionPathTemplateNode();
	aNode->mX = 255.0f;
	aNode->mY = 255.0f;
    
	return NodeInsert(aNode, pIndex);
	
	/*
    if((pIndex >= -1) && (pIndex <= mList.mCount))
    {
        if(mList.mCount <= 0)
        {
            //AddPoint(256, 256);
			NodeInsert(aNode, 0);
        }
        else if(mList.mCount == 1)
        {
            aNode = mNode[0];
            aNode.mY += 33.0f;
            
            aResult = NodeInsert(aNode, pIndex);
        }
        else
        {
            int aInd1 = 0;
            int aInd2 = 1;
            
            
            int aInsertIndex = pIndex;
            
            if((pIndex < 0) || (pIndex >= (mList.mCount - 1)))
            {
                //aInd2 = (mList.mCount - 1);
                //aInd1 = 0;
                
                aInd1 = (mList.mCount - 1);
                aInd2 = 0;
                
                
                aInsertIndex = mList.mCount;
                
                
            }
            
            else //if(pIndex == 0)
            {
                aInd1 = pIndex;
                aInd2 = (pIndex + 1);
                aInsertIndex = aInd2;
            }
            
            
			NodeBlend(&(Get(aInd1), Get(aInd2), &(aNode), 0.25f);
            
            aResult = NodeInsert(aNode, aInsertIndex);// aInsertIndex);
            
        }
    }
    return aResult;
	*/
}

void FMotionPathTemplate::NodeBlend(FMotionPathTemplateNode *pNode1, FMotionPathTemplateNode *pNode2, FMotionPathTemplateNode *pResult, float pPercent)
{
    if((pNode1 != 0) && (pNode2 != 0) && (pResult != 0))
    {
        //pResult->mX = pNode2->mX + (pNode1->mX - pNode2->mX) * pPercent;
        //pResult->mY = pNode2->mY + (pNode1->mY - pNode2->mY) * pPercent;
        
        pResult->mX = pNode1->mX + (pNode2->mX - pNode1->mX) * pPercent;
        pResult->mY = pNode1->mY + (pNode2->mY - pNode1->mY) * pPercent;
        
        
        
    }
}

FPointList *FMotionPathTemplate::GetPointList()
{
    FPointList *aList = new FPointList();
    WritePointsToList(aList);
    return aList;
}

void FMotionPathTemplate::ReadPointsFromList(FPointList *pPointList)
{
    if(pPointList)
    {
        for(int i=0;i< mList.mCount;i++)
        {
            Get(i)->mX = pPointList->mX[i];
            Get(i)->mY = pPointList->mY[i];
        }
    }
}
void FMotionPathTemplate::WritePointsToList(FPointList *pPointList)
{
    if(pPointList)
    {
        if(pPointList->mSize < mList.mCount)pPointList->SetSize(mList.mCount);
        pPointList->Reset();
        for(int i=0;i< mList.mCount;i++)
        {
            pPointList->Add(Get(i)->mX, Get(i)->mY);
        }
    }
}




void FMotionPathTemplate::Transform(float pX, float pY, float pScaleX, float pScaleY, float pRotation)
{
    FPointList aListPos;
    WritePointsToList(&aListPos);
    aListPos.Transform(pX, pY, pScaleX, pScaleY, pRotation);
    ReadPointsFromList(&aListPos);
}

void FMotionPathTemplate::Untransform(float pX, float pY, float pScaleX, float pScaleY, float pRotation)
{
    FPointList aListPos;
    WritePointsToList(&aListPos);
    aListPos.Untransform(pX, pY, pScaleX, pScaleY, pRotation);
    ReadPointsFromList(&aListPos);
}



FString FMotionPathTemplate::ExportKeySequence(const char *pName)
{
    FString aExport = "";
    
    FString aNameXY = pName;
    if(aNameXY.mLength <= 0)aNameXY = "aSeqPos";
    else aNameXY += "Pos";
    
    aExport = FString("FMotionKeySequence *") + aNameXY + FString(" = new FMotionKeySequence();\n");
    
    EnumList(FMotionPathTemplateNode, aNode, mList)
    {
        FString aStringX = FString(aNode->mX);
        FString aStringY = FString(aNode->mY);
        
        if(aNode->mTrackScreen == true)
        {
            aStringX = "";
            aStringY = "";
            
            if(aNode->mTrackSideX == 0)aStringX += "0.0f";
            else if(aNode->mTrackSideX == 1)aStringX += "gAppWidth2";
            else aStringX += "gAppWidth";
            
            if(aNode->mTrackSideY == 0)aStringY += "0.0";
            else if(aNode->mTrackSideY == 1)aStringY += "gAppHeight2";
            else aStringY += "gAppHeight";
            
            if(aNode->mTrackOffsetX != 0.0f)aStringX += FString(" + ") + FString(aNode->mTrackOffsetX);
            if(aNode->mTrackOffsetY != 0.0f)aStringY += FString(" + ") + FString(aNode->mTrackOffsetY);
        }
        
        aExport += aNameXY;
        
        aExport += FString("->Add(") + aStringX + FString(", ") + aStringY + FString(", ") + FString(aNode->mTime);
        
        if(aNode->mAnimationFunction != 3453453)
        {
            aExport += FString(", ") + FString(aNode->mAnimationFunction);
        }
        
        aExport += FString(");\n");
    }
    return aExport;
}
