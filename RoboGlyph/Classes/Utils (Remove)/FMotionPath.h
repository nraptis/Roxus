//
//  FMotionPath.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/23/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__FMotionPathTemplate__
#define ___015_Fleet_XP__FMotionPathTemplate__

#include "FObject.h"
#include "FPointList.h"
#include "FModelData.h"
#include "FList.h"
#include "FSpline.h"
#include "FXML.h"

class FFile;
class FMotionPathTemplateNode
{
public:
    FMotionPathTemplateNode();
    
    int                             mTime;
    int                             mTimeSleep;
    
    float                           mX;
    float                           mY;
    
    int                             mAnimationFunction;
    
    float                           mRotation;
    
    float                           mScale;
    
    float                           mTanInX;
    float                           mTanInY;
    bool                            mTanInAuto;
    
    float                           mTanOutX;
    float                           mTanOutY;
    bool                            mTanOutAuto;
    
    float                           mR;
    float                           mG;
    float                           mB;
    float                           mA;
    
    bool                            mTrackScreen;
    
    int                             mTrackSideX;
    int                             mTrackSideY;
    
    float                           mTrackOffsetX;
    float                           mTrackOffsetY;
};

class FMotionPathTemplate : public FObject
{
public:
    FMotionPathTemplate();
    virtual ~FMotionPathTemplate();
    
    
    
    virtual void                    Update();
    virtual void                    Draw();
    
    void                            DrawTriangles();
    
    void                            DrawEdges(float pSize);
    void                            DrawPoints(float pSize, int pSelectedPoint = -1);
    
    void                            DrawPointsSelected(float pSize, int pSelectedPoint = -1);
    void                            DrawPointsUnselected(float pSize, int pSelectedPoint = -1);
    
    void                            DrawTangents(float pSize, int pSelectedPoint = -1, int pSelectedTangent = -1);
    void                            DrawTangentsSelected(float pSize, int pSelectedPoint = -1, int pSelectedTangent = -1);
    void                            DrawTangentsUnselected(float pSize, int pSelectedPoint = -1, int pSelectedTangent = -1);

	void							DrawNaturalSpline();
    
    void                            Save(FFile *pFile);
    void                            Load(FFile *pFile);
    
	FXMLTag							*SaveXML(const char *pName);
	void							LoadXML(FXMLTag *pTag);

    
	FIndexList						mTriangleData;
	FPointList						mTriangleDataXY;
	FDrawNodeList					mTriangleDataDraw;

	FSpline							mTestSpline;


	FMotionPathTemplateNode			*Get(int pIndex);
    
	FMotionPathTemplate             *GetPathAbs();
    void                            SetPathAbs(FMotionPathTemplate *pPathAbs);
	FMotionPathTemplate             *mPathAbs;
    
    
    void                            Clone(FMotionPathTemplate *pPath);
    FMotionPathTemplate             *Clone(){FMotionPathTemplate *aClone = new FMotionPathTemplate();aClone->Clone(this);return aClone;};
    
	int	                            Count();
	void                            Clear();
    //void                            Reset();

    
    void                            AddPoint(float pX, float pY);
    void                            AddEdge(float pX1, float pY1, float pX2, float pY2);
    
    void                            SetPoint(int pIndex, float pX, float pY);
    void                            SetAbsoluteTanIn(int pIndex, float pX, float pY);
    void                            SetAbsoluteTanOut(int pIndex, float pX, float pY);
    void                            SetAbsoluteTan(int pIndex, int pSide, float pX, float pY);
    
    //void                            Size(int pSize);
    //inline void                     SetSize(int pSize){Size(pSize);}
    
    float                           GetPointX(int pIndex);
    float                           GetPointY(int pIndex);
    
    float                           GetAbsoluteTanInX(int pIndex);
    float                           GetAbsoluteTanInY(int pIndex);
    
    float                           GetAbsoluteTanOutX(int pIndex);
    float                           GetAbsoluteTanOutY(int pIndex);
    
    float                           GetAbsoluteTanX(int pIndex, int pSide);
    float                           GetAbsoluteTanY(int pIndex, int pSide);
    
    int                             GetClosestPointIndex(float pX, float pY, float &pDist);
    
    int                             GetClosestTanInIndex(float pX, float pY, float &pDist);
    int                             GetClosestTanOutIndex(float pX, float pY, float &pDist);
    
    int                             GetClosestTanIndex(float pX, float pY, float &pDist);
    int                             GetClosestTanSide(float pX, float pY);
    
    
    int                             GetNextIndex(int pIndex);
    int                             GetPrevIndex(int pIndex);
    
    int                             NodeDelete(int pIndex);
    
	int                             NodeInsert(FMotionPathTemplateNode *pNode, int pIndex);
    int                             NodeInsert(int pIndex);
    
	void                            NodeBlend(FMotionPathTemplateNode *pNode1, FMotionPathTemplateNode *pNode2, FMotionPathTemplateNode *pResult, float pPercent);
    

	FMotionPathTemplateNode			*GetNodeForTime(int pTime);

	FMotionPathTemplateNode			*Interpolate(int pTime);
	FMotionPathTemplateNode			*mInterpResult;
	FMotionPathTemplateNode			*mInterpLHS;
	FMotionPathTemplateNode			*mInterpRHS;
	float							mInterpPercent;

    
    
    FString                         ExportKeySequence(const char *pName);
    

	FList							mList;

    //FMotionPathTemplateNode         *mNode;
    //int                             mCount;
    //int                             mSize;
    
    bool                            mCircular;
    
    
    void                            Transform(float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    void                            Untransform(float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    
    void                            ReadPointsFromList(FPointList *pPointList);
    void                            WritePointsToList(FPointList *pPointList);
    FPointList                      *GetPointList();
    
    //void                            WriteTanIn(FPointList *pPointList);
    //void                            WriteTanOut(FPointList *pPointList);
    
    
    int                             mSelectedAllignTimer;
};


#endif /* defined(___015_Fleet_XP__FMotionPathTemplate__) */
