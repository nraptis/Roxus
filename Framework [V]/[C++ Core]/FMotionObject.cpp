//
//  FMotionObject.cpp
//  2015 Gnome Launcher
//
//  Created by Nicholas Raptis on 12/27/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FMotionObject.h"
#include "FApp.h"
#include "core_includes.h"

FMotionObject::FMotionObject(FSprite *pSprite)
{
    BaseInitialize();
    mWidth = 0;
    mHeight = 0;
    SetSprite(pSprite);
	mSprite = pSprite;
}

FMotionObject::FMotionObject()
{
    BaseInitialize();
}

FMotionObject::~FMotionObject()
{
    
}

void FMotionObject::BaseInitialize()
{
    //mKeySEQ = 0;
    
    
    
    mSprite = 0;
    //mSpriteSequence = 0;
    
    //mParent = 0;
    //mParentOver = false;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mWidth = 0.0f;
    mHeight = 0.0f;
    
    mScale = 1.0f;
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    
    mRotation = 0.0f;
    
    mRed = 1.0f;
    mGreen = 1.0f;
    mBlue = 1.0f;
    mAlpha = 1.0f;
    
    
    //mMod = 0;
    //mModCount = 0;
    //mModSize = 0;
    
    //mObject = 0;
    //mObjectListCount = 0;
    //mObjectListSize = 0;
    
    //mFlow = 0;
    //mFlowListSize = 0;
    //mFlowListCount = 0;
    
    //mTime = -1;
    //mTimeMax = 400;
}

void FMotionObject::Update()
{
    /*
    if(mKeySEQ)
    {
        mKeySEQ->SetTarget(&mX, &mY);
        mKeySEQ->Update();
    }
    
	mTime++;
	if(mTime >= mTimeMax)
	{
		mTime = 0;
	}
    
    ModifiersApplyUpdate();
    for(int i=0;i<mObjectListCount;i++)
    {
        mObject[i]->Update();
    }
    */
}

void FMotionObject::Draw()
{
    /*
    ModifiersApplyDraw();
    
    for(int i=0;i<mObjectListCount;i++)
    {
        if(mObject[i]->mParentOver == true)
        {
            mObject[i]->Draw();
        }
    }
    */
    
	if(mSprite)
	{
        Graphics::SetColor(mRed, mGreen, mBlue, mAlpha);
		mSprite->DrawScaled(mX, mY, mScale * mScaleX, mScale * mScaleY, mRotation);
        Graphics::SetColor();
	}
    
    
    /*
	gAppBase->mSysFontBold.Center(FString(mTime).c(), mX, mY);
    
    for(int i=0;i<mObjectListCount;i++)
    {
        if(mObject[i]->mParentOver == false)
        {
            mObject[i]->Draw();
        }
    }
    */
    
}


void FMotionObject::SetSprite(FSprite *pSprite)
{
    mSprite = pSprite;
    
    if(mSprite != 0)
    {
        if(mSprite->mWidth > mWidth)mWidth = mSprite->mWidth;
        if(mSprite->mHeight > mHeight)mHeight = mSprite->mHeight;
    }
}

void FMotionObject::SetSize(float pWidth, float pHeight)
{
    mWidth = pWidth;
    mHeight = pHeight;
}

/*
void FMotionObject::Clear()
{
    //Clear();
    
    for(int i = 0; i < mModCount; i++)delete mMod[i];
    delete[] mMod;
    mMod = 0; mModSize = 0; mModCount = 0;
    
    //for(int i = 0; i < mFlowListCount; i++)delete mFlow[i];
    //delete[] mFlow;
    //mFlow = 0; mFlowListSize = 0; mFlowListCount = 0;
    

	for(int i = 0; i < mObjectListCount; i++)delete mObject[i];
	delete[] mObject;
	mObject = 0; mObjectListCount = 0; mObjectListSize = 0;
}

void FMotionObject::Reset()
{
	mTime = 0;
}

void FMotionObject::ModifiersApply(int pIndexCategory)
{
    for(int i=0;i<mModCount;i++)
    {
        if((mMod[i]->mIndexCategory == pIndexCategory) && (mMod[i]->Alive()))
        {
            mMod[i]->Apply(this);
        }
    }
}

void FMotionObject::ModifiersApplyInit()
{
    
}

void FMotionObject::ModifiersApplyUpdate()
{
    //ModifiersApply(MOT_CATG_UPDATE);
}

void FMotionObject::ModifiersApplyDraw()
{
    ModifiersApply(MOT_CATG_DRAW);
}

void FMotionObject::ModifierAdd(FMotionObjectModifier *pModifier)
{
    bool aPlaced = false;
    int aCategory = pModifier->mIndexCategory;
    for(int i=0;((i<mModCount) && (aPlaced == true));i++)
    {
        if((mMod[i]->mIndexCategory == aCategory) && (mMod[i]->Alive()))
        {
            aPlaced = true;
            FMotionObjectModifierBucket *aBucket = 0;
            if(mMod[i]->mIndexType == MOT_TYPE_BUCKET)
            {
                aBucket = (FMotionObjectModifierBucket *)(mMod[i]);
            }
            else
            {
                aBucket = new FMotionObjectModifierBucket();
                aBucket->mIndexCategory = aCategory;
                aBucket->Add(mMod[i]);
                mMod[i] = aBucket;
            }
            
            aBucket->Add(pModifier);
        }
    }
    
    if(aPlaced == false)
    {
        if(mModCount >= mModSize)
        {
            mModSize = (mModCount + mModCount / 2 + 1);
            FMotionObjectModifier **aNew = new FMotionObjectModifier*[mModSize];
            for(int i = 0; i < mModCount; i++)aNew[i] = mMod[i];
            delete[] mMod;
            mMod = aNew;
        }
        mMod[mModCount++] = pModifier;
    }
}

void FMotionObject::ModifierDelete(int pIndexCategory, FMotionObjectModifier *pModifier)
{
    
}

void FMotionObject::ModifierDelete(FMotionObjectModifier *pModifier)
{
    Log("Deleting Mod[%x]\n", pModifier);
}

void FMotionObject::ModifierRemove(FMotionObjectModifier *pModifier)
{
    int aSlot = -1;
    
    for(int i = 0; ((i < mModCount) && (aSlot == -1)); i++)
    {
        if(mMod[i] == pModifier)
        {
            aSlot = i;
        }
    }
    
    if(aSlot != -1)
    {
        ModifierRemoveAt(aSlot);
    }
}

void FMotionObject::ModifierRemoveAt(int pSlot)
{
    if((pSlot >= 0) && (pSlot < mModCount))
    {
        for(int i=(pSlot + 1);i<mModCount;i++)mMod[i-1] = mMod[i];
        mModCount--;
    }
}
*/


/*

FMotionObjectModifier *FMotionObject::ModifierReplace(FMotionObjectModifier *pOriginalModifier, FMotionObjectModifier *pNewModifier)
{
    FMotionObjectModifier *aResult = 0;
    
    
    return aResult;
}
 
*/


/*
void FMotionObject::ModifierReplaceUnique(int pIndexCategory, int pIndexGroup, FMotionObjectModifier *pModifier)
{
    FMotionObjectModifier *aModReplace = 0;
    FMotionObjectModifierBucket *aBucket = 0;
    
    int aFindIndex = 0;
    
    for(int i=0;i<mModCount;i++)
    {
        if((mMod[i]->mIndexCategory == pIndexCategory) && (mMod[i]->Alive()))
        {
            if(mMod[i]->mIndexType == MOT_TYPE_BUCKET)
            {
                aBucket = (FMotionObjectModifierBucket *)(mMod[i]);
                aFindIndex = aBucket->FindFromGroup(pIndexGroup);
                
                if(aFindIndex != -1)
                {
                    aModReplace = aBucket->Replace(pModifier, aFindIndex);
                    ModifierDelete(aModReplace);
                }
                else
                {
                    aBucket->Add(pModifier);
                }
                
                return;
            }
            
            if(mMod[i]->mIndexGroup == pIndexGroup)
            {
                if(mMod[i] != pModifier)
                {
                    if(pModifier)
                    {
                        ModifierDelete(mMod[i]);
                        mMod[i] = pModifier;
                    }
                    else
                    {
                        ModifierRemoveAt(i);
                        ModifierDelete(mMod[i]);
                        
                    }
                    return;
                }
            }
        }
    }
    
    ModifierAdd(pModifier);
}

FMotionObjectModifier *FMotionObject::ModifierGet(int pIndexCategory, int pIndexGroup)
{
    FMotionObjectModifier *aResult = 0;
    for(int i=0;((i<mModCount) && (aResult == 0));i++)
    {
        if((mMod[i]->mIndexCategory == pIndexCategory) && (mMod[i]->Alive()))
        {
            if(mMod[i]->mIndexGroup == pIndexGroup)
            {
                aResult = mMod[i];
            }
            else if(mMod[i]->mIndexType == MOT_TYPE_BUCKET)
            {
                aResult = ((FMotionObjectModifierBucket *)(mMod[i]))->GetFromGroup(pIndexGroup);
            }
        }
    }
    
    return aResult;
}

void FMotionObject::ObjectAdd(FMotionObject *pObject)
{
	if(mObjectListCount >= mObjectListSize)
	{
		mObjectListSize = (mObjectListSize + mObjectListSize / 2 + 1);
		FMotionObject **aNew = new FMotionObject*[mObjectListSize];
		for(int i = 0; i < mObjectListCount; i++)aNew[i] = mObject[i];
		delete[] mObject;
		mObject = aNew;
	}
    pObject->mParent = this;
	mObject[mObjectListCount++] = pObject;
}

void FMotionObject::ObjectAddUnder(FMotionObject *pObject)
{
    ObjectAdd(pObject);
    pObject->mParentOver = true;
}

void FMotionObject::ObjectAddOver(FMotionObject *pObject)
{
    ObjectAdd(pObject);
    pObject->mParentOver = false;
}

int FMotionObject::ObjectFind(FMotionObject *pObject)
{
	int aIndex = -1;
	for(int i = 0; ((i < mObjectListCount) && (aIndex == -1)); i++)
	{
		if(mObject[i] == pObject)aIndex = i;
	}
	return aIndex;
}

bool FMotionObject::ObjectExists(FMotionObject *pObject)
{
	return ObjectFind(pObject) != -1;
}

void FMotionObject::Finalize()
{
    ModifiersApplyInit();
    mTime = -1;
    ModifiersApplyUpdate();
    for(int i=0;i<mObjectListCount;i++)
    {
        mObject[i]->Finalize();
    }
}

void FMotionObject::Finalize(float pX, float pY)
{
    mX = pX;
    mY = pY;
    Finalize();
}

FMotionObjectModifierTracking *FMotionObject::TrackGetModifier()
{
    return (FMotionObjectModifierTracking *)ModifierGet(FMotionObjectModifierTracking::Cat(), MOT_GROUP_TRACK);
}

void FMotionObject::TrackTargetSetPosition(float pX, float pY)
{
    FMotionObjectModifierTracking *aModTrack = TrackGetModifier();
    FMotionObjectModifierTracking *aMod = 0;
    if(aModTrack)
    {
        if(aModTrack->mIndexType == MOT_TRACK_TYPE_UNKNOWN)aMod = aModTrack;
    }
    
    if(aMod == 0)aMod = new FMotionObjectModifierTracking();
    aMod->mOffsetX = pX;
    aMod->mOffsetY = pY;
    if(aModTrack != aMod)ModifierReplaceUnique(FMotionObjectModifierTracking::Cat(), MOT_GROUP_TRACK, aMod);
}

void FMotionObject::TrackTargetSetObject(FMotionObject *pObject, float pOffsetX, float pOffsetY)
{
    FMotionObjectModifierTracking *aModTrack = TrackGetModifier();
    FMotionObjectModifierTrackingObject *aMod = 0;
    if(aModTrack)
    {
        if(aModTrack->mIndexType == MOT_TRACK_TYPE_OBJECT)aMod = ((FMotionObjectModifierTrackingObject *)aModTrack);
    }
    
    if(aMod == 0)aMod = new FMotionObjectModifierTrackingObject();
    aMod->mOffsetX = pOffsetX;
    aMod->mOffsetY = pOffsetY;
    aMod->mObject = pObject;
    
    if(aModTrack != aMod)ModifierReplaceUnique(FMotionObjectModifierTracking::Cat(), MOT_GROUP_TRACK, aMod);
}

void FMotionObject::TrackTargetSetObject(FMotionObject *pObject)
{
    float aOffsetX = 0.0f;float aOffsetY = 0.0f;
    TrackGetOxxset(aOffsetX, aOffsetY);
    TrackTargetSetObject(pObject, aOffsetX, aOffsetY);
}

void FMotionObject::TrackTargetSetScreen(int pScreenSideX, int pScreenSideY, float pOffsetX, float pOffsetY)
{
    FMotionObjectModifierTracking *aModTrack = TrackGetModifier();
    FMotionObjectModifierTrackingScreen *aMod = 0;
    if(aModTrack)
    {
        if(aModTrack->mIndexType == MOT_TRACK_TYPE_SCREEN)aMod = ((FMotionObjectModifierTrackingScreen *)aModTrack);
    }
    if(aMod == 0)aMod = new FMotionObjectModifierTrackingScreen();
    aMod->mOffsetX = pOffsetX;
    aMod->mOffsetY = pOffsetY;
    aMod->mScreenTrackSideX = pScreenSideX;
    aMod->mScreenTrackSideY = pScreenSideY;
    if(aModTrack != aMod)ModifierReplaceUnique(FMotionObjectModifierTracking::Cat(), MOT_GROUP_TRACK, aMod);
}

void FMotionObject::TrackTargetSetScreen(int pScreenSideX, int pScreenSideY)
{
    float aOffsetX = 0.0f;float aOffsetY = 0.0f;
    TrackGetOxxset(aOffsetX, aOffsetY);
    TrackTargetSetScreen(pScreenSideX, pScreenSideY, aOffsetX, aOffsetY);
}


void FMotionObject::TrackTargetSetView(FView *pView, int pViewSideX, int pViewSideY, float pOffsetX, float pOffsetY)
{
    FMotionObjectModifierTracking *aModTrack = TrackGetModifier();
    FMotionObjectModifierTrackingView *aMod = 0;
    if(aModTrack)
    {
        if(aModTrack->mIndexType == MOT_TRACK_TYPE_VIEW)aMod = ((FMotionObjectModifierTrackingView *)aModTrack);
    }
    if(aMod == 0)aMod = new FMotionObjectModifierTrackingView();
    aMod->mOffsetX = pOffsetX;
    aMod->mOffsetY = pOffsetY;
    aMod->mViewTrackSideX = pViewSideX;
    aMod->mViewTrackSideY = pViewSideY;
    aMod->mView = pView;
    if(aModTrack != aMod)ModifierReplaceUnique(FMotionObjectModifierTracking::Cat(), MOT_GROUP_TRACK, aMod);

}

float FMotionObject::TrackX()
{
    float aX = mX;float aY = mY;
    //TrackGetPos(aX, aY);
    return aX;
}

float FMotionObject::TrackY()
{
    float aX = mX;float aY = mY;
    //TrackGetPos(aX, aY);
    return aY;
}

void FMotionObject::TrackGetPos(float &pX, float &pY)
{
    FMotionObjectModifierTracking *aModTrack = TrackGetModifier();
    
    pX = mX;
    pY = mY;
    
    if(aModTrack)
    {
        pX = aModTrack->mTrackX;
        pY = aModTrack->mTrackY;
        
    }
}

void FMotionObject::TrackGetOxxset(float &pX, float &pY)
{
    FMotionObjectModifierTracking *aModTrack = TrackGetModifier();
    
    pX = 0.0f;
    pY = 0.0f;
    
    if(aModTrack)
    {
        pX = aModTrack->mOffsetX;
        pY = aModTrack->mOffsetY;
    }
}

void FMotionObject::BlendTypeSet(int pBlendType)
{
    mBlendType = pBlendType;
}

void FMotionObject::ColorSet(float pRed, float pGreen, float pBlue, float pAlpha)
{
    mRed = pRed;
    mGreen = pGreen;
    mBlue = pBlue;
    mAlpha = pAlpha;
}

void FMotionObject::ColorSet(float pRed, float pGreen, float pBlue)
{
    mRed = pRed;
    mGreen = pGreen;
    mBlue = pBlue;
}

void FMotionObject::ColorSet(float pAlpha)
{
    mAlpha = pAlpha;
}

void FMotionObject::ScaleSet(float pScale)
{
    mScale = pScale;
}

void FMotionObject::RotationSet(float pRotation)
{
    mRotation = pRotation;
}









FMotionObjectFlowKey::FMotionObjectFlowKey(float pValue) : FMotionObjectFlowKey()
{
	mValue = pValue;
}

FMotionObjectFlowKey::FMotionObjectFlowKey()
{
	mAnimationFunction = 0;
	mValue = 0;
}

FMotionObjectFlowKey::~FMotionObjectFlowKey()
{

	//Clear();
}



FMotionObjectModifierGeometry *FMotionObject::GeometryGetModifier()
{
    return (FMotionObjectModifierGeometry *)ModifierGet(FMotionObjectModifierGeometry::Cat(), MOT_GROUP_GEOMETRY);
}

void FMotionObject::GeometrySetPoint()
{
    GeometrySetUnknown();
}
                                     
void FMotionObject::GeometrySetRectangle(float pWidth, float pHeight)
{
    FMotionObjectModifierGeometry *aModGeo = GeometryGetModifier();
    FMotionObjectModifierGeometryRectangle *aMod = 0;
    if(aModGeo)
    {
        if(aModGeo->mIndexType == MOT_GEO_TYPE_RECT)aMod = ((FMotionObjectModifierGeometryRectangle *)aModGeo);
    }
    if(aMod == 0)aMod = new FMotionObjectModifierGeometryRectangle();
    aMod->mWidth = pWidth;
    aMod->mHeight = pHeight;
    
    if(aModGeo != aMod)ModifierReplaceUnique(FMotionObjectModifierGeometry::Cat(), MOT_GROUP_GEOMETRY, aMod);

}

void FMotionObject::GeometrySetCircle(float pRadius)
{
 
	FMotionObjectModifierGeometry *aGeoNode = ((FMotionObjectModifierGeometry *)GeometryNodeGet());
	FMotionObjectModifierGeometryCircle *aNode = 0;
	if(aGeoNode)
	{
		if(aGeoNode->mGeometryType == SPAWN_SOURCE_CIRCLE)aNode = ((FMotionObjectModifierGeometryCircle *)aGeoNode);
	}

	if(aNode == 0)
	{
		if(aGeoNode)NodeDelete(aGeoNode);
		aNode = new FMotionObjectModifierGeometryCircle();
		NodeAdd(aNode);
	}
	aNode->mRadius = pRadius;
 
}

void FMotionObject::GeometrySetPointCloud(FPointList *pPointList)
{
    FMotionObjectModifierGeometry *aModGeo = GeometryGetModifier();
    FMotionObjectModifierGeometryPointCloud *aMod = 0;
    if(aModGeo)
    {
        if(aModGeo->mIndexType == MOT_GEO_TYPE_POINT_CLOUD)aMod = ((FMotionObjectModifierGeometryPointCloud *)aModGeo);
    }
    if(aMod == 0)aMod = new FMotionObjectModifierGeometryPointCloud();
    aMod->SetPoints(pPointList);
    if(aModGeo != aMod)ModifierReplaceUnique(FMotionObjectModifierGeometry::Cat(), MOT_GROUP_GEOMETRY, aMod);
}


void FMotionObject::GeometrySetPolygon(FPointList *pPointList)
{
 
	FMotionObjectModifierGeometry *aGeoNode = ((FMotionObjectModifierGeometry *)GeometryNodeGet());
	FMotionObjectModifierGeometryPolygon *aNode = 0;
	if(aGeoNode)
	{
		if(aGeoNode->mGeometryType == SPAWN_SOURCE_POLYGON)aNode = ((FMotionObjectModifierGeometryPolygon *)aGeoNode);
	}
	if(aNode == 0)
	{
		if(aGeoNode)NodeDelete(aGeoNode);
		aNode = new FMotionObjectModifierGeometryPolygon();
		NodeAdd(aNode);
	}
	aNode->SetPoints(pPointList);
 
}

void FMotionObject::GeometrySetUnknown()
{
 
	FMotionObjectModifierGeometry *aGeoNode = ((FMotionObjectModifierGeometry *)GeometryNodeGet());
	FMotionObjectModifierGeometry *aNode = 0;

	if(aGeoNode)
	{
		if((aGeoNode->mGeometryType == SPAWN_SOURCE_UNKNOWN) || (aGeoNode->mGeometryType == SPAWN_SOURCE_POINT))
		{
			aNode = aGeoNode;
		}
	}
	if(aNode == 0)
	{
		if(aGeoNode)NodeDelete(aGeoNode);
		aNode = new FMotionObjectModifierGeometry();
		NodeAdd(aNode);
	}
 
}


FString FMotionObject::ExportGeometry(const char *pName)
{
    
    FString aResult = "";
    

    if(mSpawnSourceType == SPAWN_SOURCE_POINT)
    {
        FString aSpawnString = FString("ApplySpawnSourcePoint();");
        aParamList += new FString(aSpawnString);
    }
    
    if(mSpawnSourceType == SPAWN_SOURCE_RECT)
    {
        FString aSpawnString = FString("GeometrySetRectangle(") + FString(mSpawnSourceWidth) + FString(", ") + FString(mSpawnSourceHeight) + FString(");");
        aParamList += new FString(aSpawnString);
    }
    
    if(mSpawnSourceType == SPAWN_SOURCE_CIRCLE)
    {
        FString aSpawnString = FString("ApplySpawnSourceCircle(") + FString(mSpawnSourceRadius) + FString(");");
        aParamList += new FString(aSpawnString);
    }
    
    if(mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
    {
        for(int i = 0; i<mSpawnSourcePointCloudList.mCount; i++)
        {
            FMotionPathTemplate *aPath = (FMotionPathTemplate*)(mSpawnSourcePointCloudList.Fetch(i));
            FMotionPathTemplate *aPathAbs = aPath->GetPathAbs();
            if(aPathAbs->mList.mCount > 0)
            {
                FPointList aPointList;aPathAbs->WritePointsToList(&aPointList);
                FString aPointListName = FString(pName) + FString("Points") + FString((int)(i + 1));
                aResult += FString("FPointList ") + aPointListName + FString(";\n");
                aResult += aPointList.GetPrintString(aPointListName.c());
                FString aSpawnString = FString("ApplySpawnSourcePointCloud(&gRand, &") + aPointListName + FString(");");
                aParamList += new FString(aSpawnString);
            }
        }
    }
    if(mSpawnSourceType == SPAWN_SOURCE_POLYGON)
    {
        for(int i = 0; i<mSpawnSourcePolygonList.mCount; i++)
        {
            FMotionPathTemplate *aPath = (FMotionPathTemplate*)(mSpawnSourcePolygonList.Fetch(i));
            FMotionPathTemplate *aPathAbs = aPath->GetPathAbs();
            if(aPathAbs->mList.mCount > 0)
            {
                FPointList aPointList;aPathAbs->WritePointsToList(&aPointList);
                FString aPointListName = FString(pName) + FString("Poly") + FString((int)(i + 1));
                aResult += FString("FPointList ") + aPointListName + FString(";\n");
                aResult += aPointList.GetPrintString(aPointListName.c());
                FString aSpawnString = FString("ApplySpawnSourcePolygon(&gRand, &") + aPointListName + FString(");");
                aParamList += new FString(aSpawnString);
            }
        }
    }
    
    FString aName = FString(pName);
    
    EnumList(FString, aString, aParamList)
    {
        if(aName.mLength > 0)
        {
            aResult += FString(pName);
            aResult += "->";
        }
        aResult += aString->c();
        aResult += "\n";
    }
    
    FreeList(FString, aParamList);
     

    
    return aResult;
}
 

*/










