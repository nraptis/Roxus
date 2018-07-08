//
//  UNode.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UNode__
#define ___015_Fleet_XP__UNode__

#include "FObject.h"
#include "FDrawQuad.h"
#include "FParticle.h"
#include "FParticleTemplate.h"
#include "FFile.h"
#include "FPointList.h"
#include "FMotionPath.h"
#include "FMotionObject.h"

#define NODE_TRACK_POINT 0
#define NODE_TRACK_SCREEN 1
#define NODE_TRACK_VIEW 2
#define NODE_TRACK_OBJ 3

class UNode
{
public:
    
    UNode();
    virtual ~UNode();
    


	void							PrepareUpdate();
	void							Update(int pTick, int pPreviousTick);


    void							Draw(float pGlobalOpacity);
    void							DrawOutline(float pGlobalOpacity);
    void							DrawLinkOutline(float pGlobalOpacity);
    


	void							TimelineReset();

    void							Generate();
    
    bool                            mRefresh;
    bool                            mSelectionTypeHasBeenSet;
    
    bool                            Contains1(float pX, float pY, float &pDist);
    bool                            Contains2(float pX, float pY, float &pDist);
    
	void							ExportGenerateNames();

	FMotionPathTemplate				mMotionPath;
	FMotionPathTemplate				mMotionPathDraw;


	int								mSeed;

	FMotionObject					*mObject;
	void							HeirarchyClear();
	void							HeirarchyFind();
	bool							mVisited;

	bool							TrackingFind(bool pForce);


	FColor							mColor;

	FString							mExportTypeName;
	FString							mExportName;
	FString							mExportSpriteName;
	int								mExportIndex;


	static FString					ExportPointList(const char *pName, FPointList *pPointList);
	static FString					ExportMotionPath(const char *pName, FMotionPathTemplate *pPath);

	bool							mDidExport;
	FList							mExportSubnodes;
	int								mExportDepth;
    int								mExportNameIndex;
    UNode                           *mExportAddTarget;
    

	void							Save(FFile *pFile);
	void							Load(FFile *pFile);

	FXMLTag							*SaveXML();
	void							LoadXML(FXMLTag *pTag);


	int								mBlendType;

    
    FParticleTemplate               mTemplate;
    
	//FMotionPathTemplate				*mKeyPath1;
	//FMotionPathTemplate				*mKeyPath2;
	//FMotionPathTemplate				*mKeyPath3;
	//FList							mKeyPathList;
    
    
    
    FMotionPathTemplate             *MotionPickPath();
    
	void							MotionApply(int pTick);
	void							MotionKeyMake(int pTime, int pPathIndex);

	void							MotionKeySelectNext();
	void							MotionKeySelectPrev();
	void							MotionKeyDeleteSelected();
	void							MotionKeyDeleteAll();
    
	FMotionPathTemplate				*mSelectedKeyPath;
	FMotionPathTemplateNode			*mSelectedKeyNode;


	float                           GetTouchX();
	float                           GetTouchY();
    
    void                            GenerateSelectionReference();
    void                            GenerateSelectionReferencePoly();
    void                            GenerateSelectionReferencePointCloud();
    
    void                            SetPointsPoly(FList *pPathList);
    void                            SetPointsPointCloud(FList *pPathList);
    
    void                            SelectionPathAdd(FMotionPathTemplate *pPath, int pType);
    void                            SelectionPathAddList(FList *pList, int pType);
    
    FList                           mListSel;
    FList                           mListSelDelete;
    FList                           mListSelAddQueue;

	FList                           mPathAddPoly;
	FList                           mPathAddPointCloud;
    FList                           mPathDelete;
    
    int                             mAddTypePth;
    
    FPointList                      mSelectionPointsOffsetNormals;
    FPointList                      mSelectionPointsOffset;
    
	//void							SetWorldX(float pX);
	//void							SetWorldY(float pY);

	//void							ShiftWorldX(float pX);
	//void							ShiftWorldY(float pY);

	void							WorldPosSet(float pX, float pY);
	void							WorldPosShift(float pX, float pY);
    void							WorldUpdateParent(UNode *pNode);
    
    
	float							mWorldX;
	float							mWorldY;


	//void							ComputeTrackPos();
	//float							mTrackX;
	//float							mTrackY;
	//bool							mTrackComputed;


    //float                           mRelativeX;
    //float                           mRelativeY;

    
    bool                            mParticleSource;
    bool                            mColorNode;

	bool							mIsSelectable;
	bool							mIsVisible;

    //float                           mOpacity;
    
    
    
	FObjectList                     mParticles;
    FList                           mParticleSpawnList;
    

	void							SetParent(UNode *pParent, bool pComputeRelativeShift = false);
    UNode                           *mParent;
	int								mParentSaveIndex;
	bool							mParentVisited;


	int								mTrackingType;

	int								mTrackingSideX;
	int								mTrackingSideY;

	float							mTrackingOffsetX;
	float							mTrackingOffsetY;

	bool							mTrackingAdjustWorldPosition;
	bool							mTrackingMatchTransform;
    
    
    
    
    bool                            mSpawnParentGeometry;
    bool                            mSpawnParentOrigin;
    
    
    int                             mParentOffsetMatch;
    int                             mParentRotationMatch;
    int                             mParentScaleMatch;
    
    FSprite                         *mSprite;
    FSpriteSequence                 *mSpriteSequence;
    
    void                            SetSprite(FSprite *pSprite);
    void                            SetSpriteSequence(FSpriteSequence *pSpriteSequence);
    
	float                           mFrame;
    
    bool                            mSelected;
    bool                            mSelectedLink;
    bool                            mSelectedLinkTarget;

    int                             mBlinkTimer;
    
};

class UNodeSelection
{
public:
    
    UNodeSelection();
    virtual ~UNodeSelection();
    
    
    void                            Draw(bool pSelected, bool pFill, float pOpacity);
    void                            DrawPoints(bool pSelected, bool pFill, float pOpacity);
    
    void                            DrawEdges(bool pSelected, bool pFill, float pOpacity);
    void                            DrawEdgesOffset(bool pSelected, bool pFill, float pOpacity);
    
    void                            DrawLinkStartMarkers(bool pPoints, float pOpacity);
    void                            DrawLinkEndMarkers(bool pPoints, float pOpacity);
    
    void                            Clear();
    
    void                            SetNode(UNode *pNode);
    void                            SetPath(FMotionPathTemplate *pPath, UNode *pNode, int pType);
    void                            SetCirc(float pRadius);
    void                            SetRect(float pWidth, float pHeight);
    
    
    
    void                            UpdateTransform();
    
    UNode                           *mNode;
    
    FPointList                      mPoints;
    FPointList                      mPointsOutline;
    FPointList                      mBasePoints;
    FPointList                      mBaseCornerNormals;
    FPointList                      mBaseNormalsRight;
    FPointList                      mBaseNormalsLeft;
    
    int                             mType;
    
    int                             mUseFill;
    int                             mUseEdge;
    int                             mUsePoint;

};

/*
class UNodeExportStat
{
public:


	UNodeExportStat(FString pVariableName, FString pStatName, FString pValue);
	UNodeExportStat(FString pVariableName, FString pStatName, int pValue);
	UNodeExportStat(FString pVariableName, FString pStatName, float pValue);
	UNodeExportStat(FString pStatName, FString pValue);
	UNodeExportStat(FString pStatName, int pValue);
	UNodeExportStat(FString pStatName, float pValue);
	UNodeExportStat();
	virtual ~UNodeExportStat();

	FString								Get();

	FString								mVariableName;
	FString								mStatName;
	FString								mValueString;


};
*/

/*
class UNodeSprite : public UNode
{
public:
    UNodeSprite();
    virtual ~UNodeSprite();
    
    virtual void                    Update();
    //virtual void                    Draw();
    virtual void                    Draw(float pGlobalOpacity);
    
    virtual void                    Generate();
    
    virtual void                    Save(FFile *pFile);
    virtual void                    Load(FFile *pFile);
    
    
    
    //FSpriteSequence
    //
};

class UNodeParticleEmitter : public UNodeSprite
{
public:
    UNodeParticleEmitter();
    virtual ~UNodeParticleEmitter();
    
    
    virtual void                    Update();
    //virtual void                    Draw();
    virtual void                    Draw(float pGlobalOpacity);
    
    virtual void                    Generate();
    
    
    
};
*/

#endif /* defined(___015_Fleet_XP__UNode__) */
