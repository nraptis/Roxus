//
//  UNode.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UMenuStyle.h"
#include "UMainCanvas.h"
#include "UPathMaker.h"
#include "UNode.h"
#include "FParticle.h"

UNode::UNode()
{
    mObject = new FMotionObject();
    
    //mPathAddPoly.mUnique = true;
    //mPathAddPointCloud.mUnique = true;
    
    //mListSelAddQueue.mUnique = true;
    
    mColorNode = false;
    mParticleSource = false;
    mSelectionTypeHasBeenSet = false;
    
    mSelectedKeyPath = 0;
    mSelectedKeyNode = 0;
    
    mParentVisited = false;
    
    mWorldX = 0.0f;
    mWorldY = 0.0f;
    
    mSeed = gRand.Get(1000000);
    mTemplate.mSeed = mSeed;
    
    mTrackingType = 0;
    
    mTrackingSideX = 1;
    mTrackingSideY = 1;
    
    mTrackingOffsetX = 0.0f;
    mTrackingOffsetY = 0.0f;
    
    mTrackingMatchTransform = false;
    mTrackingAdjustWorldPosition = false;
    
    
    mSpawnParentGeometry = true;
    mSpawnParentOrigin = true;
    
    
    mDidExport = false;
    mExportAddTarget = 0;
    
    mParent = 0;
    
    mBlendType = BLEND_TYPE_STANDARD;
    
    mParentOffsetMatch = 0;
    mParentRotationMatch = 0;
    mParentScaleMatch = 0;
    
    mSprite = 0;
    mSpriteSequence = 0;
    
    mFrame = 0.0f;
    
    mRefresh = true;
    
    mIsSelectable = true;
    mIsVisible = true;
    
    mAddTypePth = UTIL_PATH_TYPE_POLY;
    
    UNodeSelection *aSel = new UNodeSelection();
    aSel->SetRect(80.0f, 60.0f);
    mListSelAddQueue.Add(aSel);
    
    mSelected = false;
    mSelectedLink = false;
    mSelectedLinkTarget = false;
    
    mBlinkTimer = 0;
    
    mSelectedKeyPath = &(mMotionPath);
    mSelectedKeyNode = 0;
}

UNode::~UNode()
{
    EnumList(UNodeSelection, aSel, mListSel)gUtils->DeleteNodeSelection(aSel);
    mListSel.Clear();
    
    EnumList(UNodeSelection, aSel, mListSelDelete)gUtils->DeleteNodeSelection(aSel);
    mListSelDelete.Clear();
    
    EnumList(UNodeSelection, aSel, mListSelAddQueue)gUtils->DeleteNodeSelection(aSel);
    mListSelAddQueue.Clear();
    
    
    EnumList(FMotionPathTemplate, aPath, mPathAddPoly)gUtils->DeleteMotionPath(aPath);
    mPathAddPoly.Clear();
    
    EnumList(FMotionPathTemplate, aPath, mPathAddPointCloud)gUtils->DeleteMotionPath(aPath);
    mPathAddPointCloud.Clear();
    
    EnumList(FMotionPathTemplate, aPath, mPathDelete)gUtils->DeleteMotionPath(aPath);
    mPathDelete.Clear();
    
    //FreeList(FParticleContainer, mParticles);
    mParticles.Free();
    
}

void UNode::PrepareUpdate()
{
    if(mParent)
    {
        mTemplate.SetParent(&(mParent->mTemplate));
    }
    else
    {
        mTemplate.SetParent(0);
    }
    
    float aTrackX = mWorldX;//mObject->TrackX();
    float aTrackY = mWorldY;//mObject->TrackY();
    
    aTrackX = mWorldX;
    aTrackY = mWorldY;
    
    mTemplate.mSource.mX = aTrackX;
    mTemplate.mSource.mY = aTrackY;
    
    mTemplate.TimeTrialPrepareUpdate();
    
    if(mObject)
    {
        mObject->Update();
    }
}

void UNode::Update(int pTick, int pPreviousTick)
{
    mBlinkTimer++;
    if(mBlinkTimer >= 20)
    {
        mBlinkTimer = 0;
    }
    
    
    EnumList(FMotionPathTemplateNode, aNode, mMotionPath.mList)
    {
        
        if(aNode->mTrackScreen == true)
        {
            
            float aTrackX = 0.0f;
            float aTrackY = 0.0f;
            
            /*
            if(aNode->mTrackSideX == 0)aTrackX = 0.0f;
            else if(aNode->mTrackSideX == 1)aTrackX = gAppWidth2;
            else aTrackX = gAppWidth;
            
            if(aNode->mTrackSideY == 0)aTrackY = 0.0f;
            else if(aNode->mTrackSideY == 1)aTrackY = gAppHeight2;
            else aTrackY = gAppHeight;
            
            
            aTrackX += aNode->mTrackOffsetX;
            aTrackY += aNode->mTrackOffsetY;
            */
            
            aTrackX = mWorldX;
            aTrackY = mWorldY;
            
            
            aNode->mX = aTrackX;
            aNode->mY = aTrackY;
        }
        
        
    }
    
    if(mListSelDelete.mCount > 0)
    {
        EnumList(UNodeSelection, aSel, mListSelDelete)
        {
            mListSel.Remove(aSel);
            mListSelAddQueue.Remove(aSel);
        }
        mListSelDelete.RemoveAll();
    }
    
    if(mPathDelete.mCount > 0)
    {
        EnumList(FMotionPathTemplate, aPath, mPathDelete)
        {
            mTemplate.mSpawnSourcePolygonList.Remove(aPath);
            mTemplate.mSpawnSourcePointCloudList.Remove(aPath);
            
            if(aPath->mPathAbs)
            {
                delete aPath->mPathAbs;
                aPath->mPathAbs = 0;
            }
            
            delete aPath;
        }
        mPathDelete.RemoveAll();
    }
    
    if(mListSelAddQueue.mCount > 0)
    {
        EnumList(UNodeSelection, aSel, mListSel)mListSelDelete.Add(aSel);
        EnumList(UNodeSelection, aSel, mListSelAddQueue)
        {
            
            aSel->mNode = this;
            mListSel.Add(aSel);
        }
        mListSelAddQueue.Clear();
    }
    
    if(mPathAddPoly.mCount > 0)
    {
        EnumList(FMotionPathTemplate, aPath, mTemplate.mSpawnSourcePolygonList)mPathDelete.Add(aPath);
        mTemplate.mSpawnSourcePolygonList.Clear();
        EnumList(FMotionPathTemplate, aPath, mPathAddPoly)mTemplate.mSpawnSourcePolygonList.Add(aPath);
        
        mPathAddPoly.Clear();
        GenerateSelectionReference();
    }
    
    if(mPathAddPointCloud.mCount > 0)
    {
        EnumList(FMotionPathTemplate, aPath, mTemplate.mSpawnSourcePointCloudList)mPathDelete.Add(aPath);
        mTemplate.mSpawnSourcePointCloudList.Clear();
        
        EnumList(FMotionPathTemplate, aPath, mPathAddPointCloud)mTemplate.mSpawnSourcePointCloudList.Add(aPath);
        mPathAddPointCloud.Clear();
        
        GenerateSelectionReference();
    }
    
    
    
    
    if(mRefresh)
    {
        Generate();
        mRefresh = false;
    }
    
    
    mParticleSpawnList.RemoveAll();
    if(mParticleSource)
    {
        
        if(mParent)
        {
            mTemplate.mSpawnSourceParent = &(mParent->mTemplate);
        }
        
        float aDrawX = mWorldX;//mObject->TrackX();
        float aDrawY = mWorldY;//mObject->TrackY();
        
        aDrawX = mWorldX;
        aDrawY = mWorldY;
        
        /*
        EnumList(FParticleContainer, aContainer, mParticles)
        {
            FParticle *aParticle = aContainer->mParticle;
            
            if(mSpriteSequence != 0)
            {
                aParticle->mSprite = 0;
                aParticle->mSpriteSequence = mSpriteSequence;
            }
            else if(mSprite != 0)
            {
                aParticle->mSpriteSequence = 0;
                aParticle->mSprite = mSprite;
            }
            
            
            
        }
        */
        
        //mParticles.Update();
        //mTemplate.TimeTrialSetPos(mObject->TrackX(), mObject->TrackY());
        mTemplate.TimeTrialSetPos(aDrawX, aDrawY);
        mTemplate.TimeTrialUpdate(pTick);
        
    }
    else
    {
        if(mSpriteSequence)
        {
            float aFrameMax = mSpriteSequence->GetMaxFrame();
            if(aFrameMax >= 1.0f)
            {
                mFrame += mTemplate.mSpawnFrameSpeed;
                if(mFrame >= aFrameMax)mFrame -= aFrameMax;
            }
        }
    }
}

void UNode::Draw(float pGlobalOpacity)
{
    float aDrawX = mWorldX;//mObject->TrackX();
    float aDrawY = mWorldX;//mObject->TrackY();
    
    aDrawX = mWorldX;
    aDrawY = mWorldY;
    
    if(mParticleSource)
    {
        /*
        EnumList(FParticleContainer, aContainer, mParticles)
        {
            aContainer->mBlendType = mBlendType;
            
            float aAlphaHold = aContainer->mParticle->mAlpha;
            float aAlpha = aContainer->mParticle->mAlpha * pGlobalOpacity;
            
            aAlpha *= 0.25f;
            
            aContainer->mParticle->mAlpha = aAlpha;
            aContainer->Draw();
            aContainer->mParticle->mAlpha = aAlphaHold;
        }
        */
        
        //mTemplate.mSource.BlendTypeSet(mBlendType);
        Graphics::BlendSetType(mBlendType);
        mTemplate.TimeTrialDraw();
        Graphics::BlendSetAlpha();
    }
    else
    {
        float aScaleX = mObject->mScale * mObject->mScaleX;
        float aScaleY = mObject->mScale * mObject->mScaleY;
        float aRot = mObject->mRotation;
        
        float aR = mObject->mRed + mTemplate.mSpawnColorExtra.mRed;
        float aG = mObject->mGreen + mTemplate.mSpawnColorExtra.mGreen;
        float aB = mObject->mBlue + mTemplate.mSpawnColorExtra.mBlue;
        float aA = mObject->mAlpha + mTemplate.mSpawnColorExtra.mAlpha;
        
        if(mSpriteSequence)
        {
            mSprite = mSpriteSequence->GetSprite(mFrame);
        }
        
        Graphics::BlendSetType(mBlendType);
        Graphics::SetColor(aR, aG, aB, aA * pGlobalOpacity);
        
        if(mColorNode)
        {
            Graphics::DrawRect(aDrawX - mTemplate.mSpawnSourceWidth / 2.0f, aDrawY - mTemplate.mSpawnSourceHeight / 2.0f, mTemplate.mSpawnSourceWidth, mTemplate.mSpawnSourceHeight);
        }
        
        if(mSprite)
        {
            mSprite->DrawScaled(aDrawX, aDrawY, aScaleX, aScaleY, aRot);
            
            if(gUtils->mDrawDisableAll == false)
            {
                if(((aDrawX == mWorldX) && (aDrawY == mWorldY)) == false)
                {
                    Graphics::BlendSetAlpha();
                    //Graphics::SetColor(pGlobalOpacity * 0.25f);
                    Graphics::SetColor(1.0f);
                    
                    mSprite->DrawScaled(mWorldX, mWorldY, aScaleX, aScaleY, aRot);
                }
            }
        }
        
        Graphics::SetColor();
        Graphics::BlendSetAlpha();
    }
    
    if(mMotionPath.mList.mCount > 0)
    {
        Graphics::SetColor(0.5f);
        
        mMotionPathDraw.Clone(&mMotionPath);
        mMotionPathDraw.Transform(mWorldX, mWorldY, mObject->mScale * mObject->mScaleX, mObject->mScale * mObject->mScaleY, mObject->mRotation);
        
        //mMotionPathDraw.DrawPoints(10, -1);
        //mMotionPathDraw.DrawEdges(1);
        
        mMotionPathDraw.DrawNaturalSpline();
        Graphics::SetColor();
        
        mMotionPathDraw.DrawPoints(6.0f);
    }
    else
    {
        
    }
    
    
    if(mMotionPath.mList.mCount > 0)
    {
        mObject->Draw();
    }
    
}

void UNode::DrawOutline(float pGlobalOpacity)
{
    float aRed = 1.0f;
    float aGreen = 1.0f;
    float aBlue = 1.0f;
    float aAlpha = 1.0f;
    
    float aOutlineRed = 1.0f;
    float aOutlineGreen = 1.0f;
    float aOutlineBlue = 1.0f;
    float aOutlineAlpha = 0.0f;
    
    if(mParticleSource)
    {
        aGreen = 0.85f;
        aBlue = 0.85f;
        aRed = 0.125f;
    }
    else if(mSpriteSequence)
    {
        aRed = 0.45f;
        aGreen = 0.85f;
        aBlue = 0.55f;
    }
    else if(mSprite)
    {
        aRed = 0.35f;
        aGreen = 0.35f;
        aBlue = 0.35f;
    }
    
    if(mSelectedLinkTarget)
    {
        aOutlineRed = 1.0f;
        aOutlineGreen = 0.75f;
        aOutlineBlue = 0.0f;
        aOutlineAlpha = 1.0f;
    }
    else if(mSelectedLink)
    {
        aOutlineRed = 0.25f;
        aOutlineGreen = 0.25f;
        aOutlineBlue = 1.0f;
        aOutlineAlpha = 1.0f;
    }
    else if(mSelected)
    {
        aOutlineRed = 0.65f;
        aOutlineGreen = 1.0f;
        aOutlineBlue = 0.85f;
        aOutlineAlpha = 1.0f;
    }
    
    bool aOutline = true;
    
    Graphics::SetColor(aRed, aGreen, aBlue, aAlpha * pGlobalOpacity);
    
    float aOpacity = 0.85f;
    
    bool aSelected = false;
    bool aEdge = false;
    
    bool aSelLoop = false;
    bool aEdgLoop = false;
    
    for(int i=0;i<4;i++)
    {
        aSelLoop = false;
        aEdgLoop = false;
        
        if(i == 0)
        {
            aSelLoop = false;
            aEdgLoop = true;
        }
        if(i == 1)
        {
            aSelLoop = false;
            aEdgLoop = false;
        }
        if(i == 2)
        {
            aSelLoop = true;
            aEdgLoop = true;
        }
        if(i == 3)
        {
            aSelLoop = true;
            aEdgLoop = false;
        }
        
        EnumList(UNodeSelection, aNodeSel, mListSel)
        {
            aSelected = gUtilsNode==(aNodeSel->mNode);
            
            if(aSelected)
            {
                if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
                {
                    aNodeSel->DrawPoints(aSelected, false, aOpacity);
                    aNodeSel->DrawPoints(aSelected, true, aOpacity);
                }
                else
                {
                    aNodeSel->DrawEdges(aSelected,false,aOpacity);
                    aNodeSel->DrawEdges(aSelected,true,aOpacity);
                    aNodeSel->DrawPoints(aSelected, false, aOpacity);
                    aNodeSel->DrawPoints(aSelected, true, aOpacity);
                }
            }
            else
            {
                if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
                {
                    aNodeSel->DrawPoints(false, false, aOpacity);
                }
                else
                {
                    aNodeSel->DrawEdges(false,false,aOpacity);
                    aNodeSel->DrawPoints(false, false, aOpacity);
                }
            }
        }
    }
    
    
    
    if(aSelected)
    {
        Graphics::SetColor(1.0f, 0.2f, 0.2f, 1.0f);
        Graphics::OutlineRect(mWorldX - 20.0f, mWorldY - 20.0f, 40.0f, 40.0f, 2.0f);
        
        if(mBlinkTimer < 10)
        {
            Graphics::SetColor(0.2f, 0.8f, 0.8f, 1.0f);
            
            Graphics::DrawLine(mWorldX, mWorldY - 10.0f, mWorldX, mWorldY + 10.0f, 1.0f);
            Graphics::DrawLine(mWorldX - 10.0f, mWorldY, mWorldX + 10.0f, mWorldY, 1.0f);
        }
    }
    else
    {
        Graphics::SetColor(1.0f, 0.5f, 0.5f, 0.5f);
        Graphics::OutlineRect(mWorldX - 16.0f, mWorldY - 16.0f, 32.0f, 32.0f, 2.0f);
    }
    
    
    Graphics::SetColor();
}

void UNode::DrawLinkOutline(float pGlobalOpacity)
{
    if(mSelectedLink)
    {
        EnumList(UNodeSelection, aNodeSel, mListSel)
        {
            aNodeSel->DrawLinkStartMarkers((mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD), pGlobalOpacity);
        }
    }
    if(mSelectedLinkTarget)
    {
        EnumList(UNodeSelection, aNodeSel, mListSel)
        {
            aNodeSel->DrawLinkEndMarkers((mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD), pGlobalOpacity);
        }
    }
}

void UNode::TimelineReset()
{
    mTemplate.TimeTrialReset();
}

void UNode::ExportGenerateNames()
{
    FList aWordList;
    
    mExportTypeName = "FMotionObject";
    mExportName = "aObject";
    mExportSpriteName = "";
    
    if(mSpriteSequence)mExportSpriteName = mSpriteSequence->mFilePrefix;
    if(mExportSpriteName.mLength <= 0)if(mSprite)mExportSpriteName = mSprite->mFileName;
    if(mExportSpriteName.mLength > 0)
    {
        bool aLastWasLetter = false;
        bool aLastWasCap = false;
        bool aLastWasNumber = false;
        
        FString aString;
        
        
        for(int i = 0; i < mExportSpriteName.mLength; i++)
        {
            char aChar = mExportSpriteName.mData[i];
            
            bool aIsLetterLower = (aChar >= 'a') && (aChar <= 'z');
            bool aIsLetterUpper = (aChar >= 'A') && (aChar <= 'Z');
            bool aIsNumber = (aChar >= '0') && (aChar <= '9');
            bool aIsLetter = (aIsLetterLower || aIsLetterUpper);
            if(aIsLetter)
            {
                if((aLastWasLetter == false) || ((aLastWasCap == false) && (aIsLetterUpper == true)))
                {
                    if(aString.mLength > 0){ aWordList.Add(new FString(aString.c())); aString = ""; }
                    
                }
                aString += FString((char)(aChar));
                aLastWasLetter = true;
                aLastWasCap = (aIsLetterUpper);
                aLastWasNumber = false;
            }
            else if(aIsNumber)
            {
                aString += FString((char)(aChar));
                
                aLastWasNumber = true;
                aLastWasLetter = false;
                aLastWasCap = false;
            }
            else
            {
                if((aChar != '_') && (aChar != '\'') && (aChar > ' '))
                {
                    aString += FString((char)(aChar));
                }
                else
                {
                    if(aString.mLength > 0){ aWordList.Add(new FString(aString.c())); aString = ""; }
                }
                aLastWasNumber = false;
                aLastWasLetter = false;
                aLastWasCap = false;
            }
        }
        if(aString.mLength > 0){ aWordList.Add(new FString(aString.c())); aString = ""; }
    }
    
    if(aWordList.mCount <= 0)
    {
        if(mColorNode)aWordList.Add(new FString("Rect"));
        else if(mParticleSource)aWordList.Add(new FString("Source"));
    }
    aWordList.Add(new FString("Obj"));
    
    EnumList(FString, aString, aWordList)
    {
        aString->CapitolizeFirstLetter(true);
    }
    
    int aWordIndex = 0;
    
    EnumList(FString, aString, aWordList)aWordIndex++;
    
    mExportName = "a";
    mExportSpriteName = "gApp->mSprite";
    
    EnumList(FString, aString, aWordList)
    {
        mExportName += aString->c();
        mExportSpriteName += aString->c();
    }
    
    if(mParticleSource)mExportTypeName = "FMotionObjectParticleSource";
    else if(mColorNode)mExportTypeName = "FMotionObject";
    else mExportTypeName = "FMotionObject";
    
    FreeList(FString, aWordList);
}

FString	UNode::ExportPointList(const char *pName, FPointList *pPointList)
{
    FString aReturn = FString(pName);
    return aReturn;
}

FString	UNode::ExportMotionPath(const char *pName, FMotionPathTemplate *pPath)
{
    FString aReturn = FString(pName);
    return aReturn;
}

float UNode::GetTouchX()
{
    return mWorldX;
}

float UNode::GetTouchY()
{
    return mWorldY;
}

void UNode::WorldPosSet(float pX, float pY)
{
    mWorldX = pX;
    mWorldY = pY;
    
    WorldUpdateParent(this);
}

void UNode::WorldPosShift(float pX, float pY)
{
    WorldPosSet(mWorldX + pX, mWorldY + pY);
}

void UNode::WorldUpdateParent(UNode *pNode)
{
    if(pNode)
    {
        pNode->mParentVisited = true;
        EnumList(UNode, aNode, gUtilWS->mNodeList)
        {
            if((aNode != this) && (aNode->mParent == this) && (aNode->mParentVisited == false)
                && (aNode->mParticleSource == false)
                && (aNode->mTrackingType == NODE_TRACK_OBJ)
                && (aNode->mTrackingAdjustWorldPosition == true))
            {
                aNode->mWorldX = pNode->mWorldX + aNode->mTrackingOffsetX;
                aNode->mWorldY = pNode->mWorldY + aNode->mTrackingOffsetY;
                
                
                
                
            }
        }
    }
}

void UNode::SetParent(UNode *pParent, bool pComputeRelativeShift)
{
    if(pParent == this)pParent = 0;
    
    mParent = pParent;
    mTemplate.SetParent(0);
    
    if(mParent)
    {
        mTemplate.SetParent(&(mParent->mTemplate));
    }
}

void UNode::HeirarchyClear()
{
    mVisited = false;
    
    //mObject->mObjectListCount = 0;
}

void UNode::HeirarchyFind()
{
    /*
    if(mParent)
    {
        if(mParent->mObject->ObjectExists(mObject) == false)
        {
            mParent->mObject->ObjectAdd(mObject);
        }
    }
    */
}

bool UNode::TrackingFind(bool pForce)
{
    bool aReturn = true;
    
    mObject->mRed = mColor.mRed;
    mObject->mGreen = mColor.mGreen;
    mObject->mBlue = mColor.mBlue;
    mObject->mAlpha = mColor.mAlpha;
    

    /*
    if(mTrackingType == NODE_TRACK_OBJ)
    {
        //FMotionObjectModifierTrackingObject *aTracker = ((FMotionObjectModifierTrackingObject *)(mObject->mTrackObject));
        
        if(mParent != 0)
        {
            if(mParent->mVisited == true)
            {
                mObject->TrackTargetSetObject(mParent->mObject, mTrackingOffsetX, mTrackingOffsetY);
            }
            else
            {
                aReturn = false;
            }
        }
        else
        {
            aReturn = false;
        }
        if((aReturn == false) && (pForce == true))
        {
            mObject->TrackTargetSetPosition(mWorldX, mWorldY);
        }
    }
    else if(mTrackingType == NODE_TRACK_VIEW)
    {
        mObject->TrackTargetSetView(gUtils->mReferenceView, mTrackingSideX - 1, mTrackingSideY - 1, mTrackingOffsetX, mTrackingOffsetY);
        
    }
    else if(mTrackingType == NODE_TRACK_SCREEN)
    {
        mObject->TrackTargetSetScreen(mTrackingSideX - 1, mTrackingSideY - 1, mTrackingOffsetX, mTrackingOffsetY);
    }
    else
    {
        mObject->TrackTargetSetPosition(mWorldX, mWorldY);
    }
    
    if(aReturn == true)
    {
        mObject->ModifiersApplyUpdate();
    }
    */
    
    return aReturn;
}

bool UNode::Contains1(float pX, float pY, float &pDist)
{
    bool aReturn = false;
    
    if(mIsSelectable == true)
    {
    
    if(DistanceSquared(mWorldX, mWorldY, pX, pY) < (10.0f * 10.0f))
    {
        aReturn = true;
    }
    else
    {
        float aBestClosestPointDist = 20.0f * 20.0f;
        float aBestClosestEdgeDist = 20.0f * 20.0f;
        
        if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
        {
            aBestClosestEdgeDist = 40.0f * 40.0f;
            aBestClosestPointDist = 40.0f * 40.0f;
        }
        
        EnumList(UNodeSelection, aSel, mListSel)
        {
            float aClosestPointDist = 50.0f * 50.0f;
            float aClosestEdgeDist = 50.0f * 50.0f;
            
            aSel->mPoints.GetClosestIndex(pX, pY, aClosestPointDist);
            aSel->mPoints.GetClosestEdge(pX, pY, false, aClosestEdgeDist);
            
            if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
            {
                if(aClosestPointDist < aBestClosestPointDist)
                {
                    aBestClosestPointDist = aClosestPointDist;
                    aReturn = true;
                }
                
                if(aClosestEdgeDist < aBestClosestEdgeDist)
                {
                    aBestClosestEdgeDist = aClosestEdgeDist;
                }
            }
            else
            {
                if(aSel->mPoints.ContainsPoint(pX, pY))
                {
                    aReturn = true;
                }
            }
        }
    }
    }
    
    return aReturn;
}


bool UNode::Contains2(float pX, float pY, float &pDist)
{
    bool aReturn = false;
    
    if(mIsSelectable == true)
    {
    
    if(DistanceSquared(mWorldX, mWorldY, pX, pY) < (60.0f * 60.0f))
    {
        aReturn = true;
    }
    else
    {
        float aBestClosestPointDist = 50.0f * 50.0f;
        float aBestClosestEdgeDist = 50.0f * 50.0f;
        
        if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
        {
            aBestClosestEdgeDist = 40.0f * 40.0f;
            aBestClosestPointDist = 40.0f * 40.0f;
            
        }
        
        EnumList(UNodeSelection, aSel, mListSel)
        {
            float aClosestPointDist = 50.0f * 50.0f;
            float aClosestEdgeDist = 50.0f * 50.0f;
            
            aSel->mPoints.GetClosestIndex(pX, pY, aClosestPointDist);
            aSel->mPoints.GetClosestEdge(pX, pY, false, aClosestEdgeDist);
            
            if(aClosestPointDist < aBestClosestPointDist)
            {
                aBestClosestPointDist = aClosestPointDist;
                aReturn = true;
            }
            
            if(aClosestEdgeDist < aBestClosestEdgeDist)
            {
                aBestClosestEdgeDist = aClosestEdgeDist;
            }
            
            if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
            {
                
            }
            else
            {
                if(aSel->mPoints.ContainsPoint(pX, pY))
                {
                    aReturn = true;
                }
            }
        }
    }
        
    }
    return aReturn;
}

void UNode::SelectionPathAdd(FMotionPathTemplate *pPath, int pType)
{
    
    
    if(pPath)
    {
        EnumList(UNodeSelection, aSel, mListSelAddQueue)mListSelDelete.Add(aSel);
        EnumList(UNodeSelection, aSel, mListSel)mListSelDelete.Add(aSel);
        
        UNodeSelection *aSelAdd = new UNodeSelection();
        aSelAdd->SetPath(pPath->Clone(), this, pType);
        mListSelAddQueue.Add(aSelAdd);
    }
}

void UNode::SelectionPathAddList(FList *pList, int pType)
{
    
    if(pList)
    {
        if(pType == UTIL_PATH_TYPE_POLY)EnumList(FMotionPathTemplate, aPath, (*pList))mPathAddPoly.Add(aPath);
        if(pType == UTIL_PATH_TYPE_POINT_CLOUD)EnumList(FMotionPathTemplate, aPath, (*pList))mPathAddPointCloud.Add(aPath);
        mAddTypePth = pType;
    }
}

void UNode::SetPointsPoly(FList *pPathList)
{
    SelectionPathAddList(pPathList, UTIL_PATH_TYPE_POLY);
}

void UNode::SetPointsPointCloud(FList *pPathList)
{
    SelectionPathAddList(pPathList, UTIL_PATH_TYPE_POINT_CLOUD);
}

void UNode::GenerateSelectionReference()
{
    EnumList(UNodeSelection, aSel, mListSelAddQueue)mListSelDelete.Add(aSel);
    EnumList(UNodeSelection, aSel, mListSel)mListSelDelete.Add(aSel);
    
    if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_RECT)
    {
        UNodeSelection *aSel = new UNodeSelection();
        aSel->SetRect(mTemplate.mSpawnSourceWidth, mTemplate.mSpawnSourceHeight);
        mListSelAddQueue.Add(aSel);
    }
    
    if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_CIRCLE)
    {
        UNodeSelection *aSelAdd = new UNodeSelection();
        aSelAdd->SetCirc(mTemplate.mSpawnSourceRadius);
        mListSelAddQueue.Add(aSelAdd);
    }
    
    if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT)
    {
        UNodeSelection *aSelAdd = new UNodeSelection();
        aSelAdd->SetCirc(50.0f);
        mListSelAddQueue.Add(aSelAdd);
    }
    
    if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POLYGON)
    {
        GenerateSelectionReferencePoly();
    }
    
    if(mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)
    {
        GenerateSelectionReferencePointCloud();
    }
}

void UNode::GenerateSelectionReferencePoly()
{
    EnumList(UNodeSelection, aSel, mListSelAddQueue)mListSelDelete.Add(aSel);
    EnumList(UNodeSelection, aSel, mListSel)mListSelDelete.Add(aSel);
    
    EnumList(FMotionPathTemplate, aPath, mTemplate.mSpawnSourcePolygonList)
    {
        UNodeSelection *aSelAdd = new UNodeSelection();
        aSelAdd->SetPath(aPath->Clone(), this, SPAWN_SOURCE_POLYGON);
        mListSelAddQueue.Add(aSelAdd);
    }
}

void UNode::GenerateSelectionReferencePointCloud()
{
    EnumList(UNodeSelection, aSel, mListSelAddQueue)mListSelDelete.Add(aSel);
    EnumList(UNodeSelection, aSel, mListSel)mListSelDelete.Add(aSel);
    
    EnumList(FMotionPathTemplate, aPath, mTemplate.mSpawnSourcePointCloudList)
    {
        UNodeSelection *aSelAdd = new UNodeSelection();
        aSelAdd->SetPath(aPath->Clone(), this, SPAWN_SOURCE_POINT_CLOUD);
        mListSelAddQueue.Add(aSelAdd);
    }
}

void UNode::Generate()
{
    if((mSelectionTypeHasBeenSet == false) && ((mSprite != 0) || (mSpriteSequence != 0)))
    {
        if(mParticleSource)
        {
            mTemplate.SetSpawnSource(SPAWN_SOURCE_POINT);
            mTemplate.mSpawnSourceRadius = 46.0f;
        }
        else
        {
            float aWidth = 64.0f;
            float aHeight = 64.0f;
            
            if(mSpriteSequence)
            {
                aWidth = mSpriteSequence->mWidth;
                aHeight = mSpriteSequence->mHeight;
            }
            else if(mSprite)
            {
                aWidth = mSprite->mWidth;
                aHeight = mSprite->mHeight;
            }
            
            mTemplate.SetSpawnSource(SPAWN_SOURCE_RECT);
            mTemplate.mSpawnSourceWidth = aWidth;
            mTemplate.mSpawnSourceHeight = aHeight;
        }
        
        mSelectionTypeHasBeenSet = true;
        GenerateSelectionReference();
    }
}


FXMLTag	*UNode::SaveXML()
{
    
    
    
    FXMLTag *aTag = new FXMLTag("node");
    
    
    aTag->AddParamSafeFloat("world_x", mWorldX);
    aTag->AddParamSafeFloat("world_y", mWorldY);
    aTag->AddParamInt("parent_index", mParentSaveIndex);
    
    aTag->AddParamSafeFloat("object_rotation", mObject->mRotation);
    aTag->AddParamSafeFloat("object_scale", mObject->mScale);
    aTag->AddParamSafeFloat("object_scale_x", mObject->mScaleX);
    aTag->AddParamSafeFloat("object_scale_y", mObject->mScaleY);
    
    aTag->AddParamBool("is_particle_source", mParticleSource);
    aTag->AddParamBool("is_color_node", mColorNode);
    aTag->AddParamBool("is_selectable", mIsSelectable);
    aTag->AddParamBool("is_visible", mIsVisible);
    
    aTag->AddTagSafeColor("color", &mColor);
    aTag->AddParamInt("blend_type", mBlendType);
    
    FXMLTag *aTrackingTag = new FXMLTag("tracking");
    *aTag += aTrackingTag;
    aTrackingTag->AddParamInt("type", mTrackingType);
    aTrackingTag->AddParamInt("side_x", mTrackingSideX);
    aTrackingTag->AddParamInt("side_y", mTrackingSideY);
    aTrackingTag->AddParamSafeFloat("offset_x", mTrackingOffsetX);
    aTrackingTag->AddParamSafeFloat("offset_y", mTrackingOffsetY);
    aTrackingTag->AddParamBool("match_xform", mTrackingMatchTransform);
    aTrackingTag->AddParamBool("auto_adjust", mTrackingAdjustWorldPosition);
    
    
    FXMLTag *aMotionPathTag = mMotionPath.SaveXML("motion_path");
    FXMLTag *aMotionPathTagAbs = mMotionPath.GetPathAbs()->SaveXML("motion_path_abs");
    
    *aTag += aMotionPathTag;
    *aTag += aMotionPathTagAbs;
    mTemplate.mSpriteSequence = mSpriteSequence;
    mTemplate.mSprite = mSprite;
    *aTag += mTemplate.SaveXML();
    
    return aTag;
}

void UNode::LoadXML(FXMLTag *pTag)
{
    if(pTag)
    {
        mSelectionTypeHasBeenSet = true;
        
        
        mWorldX = pTag->GetParamSafeFloat("world_x", 0.0f);
        mWorldY = pTag->GetParamSafeFloat("world_y", 0.0f);
        
        
        mParentSaveIndex = pTag->GetParamInt("parent_index", -1);
        
        mObject->mRotation = pTag->GetParamSafeFloat("object_rotation", 0.0f);
        mObject->mScale = pTag->GetParamSafeFloat("object_scale", 1.0f);
        mObject->mScaleX = pTag->GetParamSafeFloat("object_scale_x", 1.0f);
        mObject->mScaleY = pTag->GetParamSafeFloat("object_scale_y", 1.0f);
        
        mParticleSource = pTag->GetParamBool("is_particle_source", false);
        mColorNode = pTag->GetParamBool("is_color_node", false);
        mIsSelectable = pTag->GetParamBool("is_selectable", true);
        mIsVisible = pTag->GetParamBool("is_visible", true);
        
        FColor aDefaultColor = FColor(1.0f, 1.0f, 1.0f, 1.0f);
        pTag->ReadTagSafeColor("color", &mColor, &aDefaultColor);
        
        
        mBlendType = pTag->GetParamInt("blend_type", BLEND_TYPE_STANDARD);
        
        
        
        
        EnumTagsMatching(pTag, aTrackingTag, "tracking")
        {
            mTrackingType = aTrackingTag->GetParamInt("type", 0);
            mTrackingSideX = aTrackingTag->GetParamInt("side_x", 1);
            mTrackingSideY = aTrackingTag->GetParamInt("side_y", 1);
            mTrackingOffsetX = aTrackingTag->GetParamSafeFloat("offset_x", 0.0f);
            mTrackingOffsetY = aTrackingTag->GetParamSafeFloat("offset_y", 0.0f);
            mTrackingMatchTransform = aTrackingTag->GetParamBool("match_xform", false);
            mTrackingAdjustWorldPosition = aTrackingTag->GetParamBool("auto_adjust", true);
        }
        
        EnumTagsMatching(pTag, aMotionPathTag, "motion_path")mMotionPath.LoadXML(aMotionPathTag);
        EnumTagsMatching(pTag, aMotionPathTagAbs, "motion_path_abs")
        {
            FMotionPathTemplate *aPathAbs = new FMotionPathTemplate();
            
            aPathAbs->LoadXML(aMotionPathTagAbs);
            
            if(mMotionPath.mPathAbs)
            {
                Log("????\n\n\n");
                delete mMotionPath.mPathAbs;
                mMotionPath.mPathAbs = 0;
            }
            mMotionPath.mPathAbs = aPathAbs;
        }
        
        
        
        EnumTagsMatching(pTag, aTag, "particle_template")
        {
            
            mTemplate.LoadXML(aTag);
            
            
            
            //mTemplate.mSpawnSourcePolygonList.Clear();
            //mTemplate.mSpawnSourcePointCloudList.Clear();
        }
        
        //SetPointsPoly(&aListPoly);
        //SetPointsPointCloud(&aListPoly);
        
        
        if(mTemplate.mSpriteSequence)SetSpriteSequence(mTemplate.mSpriteSequence);
        else if(mTemplate.mSprite)SetSprite(mTemplate.mSprite);
        
        GenerateSelectionReference();
        
    }
}

void UNode::Save(FFile *pFile)
{
    if(pFile)
    {
        
    }
}

void UNode::Load(FFile *pFile)
{
    if(pFile)
    {
        
    }
}



void UNode::SetSprite(FSprite *pSprite)
{
    if(mSpriteSequence)
    {
        mSpriteSequence = 0;
    }
    
    mSprite = pSprite;
    mTemplate.mSprite = pSprite;
    
    if(mSelectionTypeHasBeenSet == false)
    {
        Generate();
        mSelectionTypeHasBeenSet = true;
    }
    
    mRefresh = true;
}

void UNode::SetSpriteSequence(FSpriteSequence *pSpriteSequence)
{
    if(mSprite)
    {
        mSprite = 0;
    }
    
    mSpriteSequence = pSpriteSequence;
    mTemplate.mSpriteSequence = mSpriteSequence;
    
    if(mSelectionTypeHasBeenSet == false)
    {
        Generate();
        mSelectionTypeHasBeenSet = true;
    }
    
    mRefresh = true;
}

FMotionPathTemplate *UNode::MotionPickPath()
{
    FMotionPathTemplate *aPath = mSelectedKeyPath;
    
    if(aPath == 0)
    {
        aPath = &(mMotionPath);
        mSelectedKeyPath = aPath;
    }
    
    
    return aPath;
}


void UNode::MotionApply(int pTick)
{
    
    if(mMotionPath.mList.mCount != 0)
    {

     FMotionPathTemplateNode *aInterp = mMotionPath.Interpolate(pTick);
     
     if(aInterp)
     {
         mObject->mX = aInterp->mX;
         mObject->mY = aInterp->mY;
         
         //WorldPosSet(aInterp->mX, aInterp->mY);
         
         mObject->mRotation = aInterp->mRotation;
         
     }
     }
    
}

void UNode::MotionKeyMake(int pTime, int pPathIndex)
{
    /*
    FMotionPathTemplate *aPath = (FMotionPathTemplate *)(mKeyPathList.Fetch(pPathIndex));
    if(aPath)
    {
        FMotionPathTemplateNode *aNode = aPath->GetNodeForTime(pTime);
        
        aNode->mX = mWorldX;
        aNode->mY = mWorldY;
        
        aNode->mScale = mObject->mScale;
        aNode->mRotation = mObject->mRotation;
        
        aNode->mR = mObject->mRed;
        aNode->mG = mObject->mGreen;
        aNode->mB = mObject->mBlue;
        aNode->mA = mObject->mAlpha;
        
        mSelectedKeyPath = aPath;
        mSelectedKeyNode = aNode;
        
        int aIndex = 0;
        EnumList(FMotionPathTemplateNode, aNode, aPath->mList)
        {
            Log("KEY[%d]  ((%d)) = (%f, %f)  (%f %f %f)\n", aIndex, aNode->mTime, aNode->mX, aNode->mY, aNode->mR, aNode->mG, aNode->mA);
            aIndex++;
        }
    }
    */
}

void UNode::MotionKeySelectNext()
{
    
    if(mSelectedKeyPath == 0)
    {
        mSelectedKeyPath = &(mMotionPath);
        
        /*
        EnumList(FMotionPathTemplate, aPath, mKeyPathList)
        {
            if((aPath->mList.mCount > 0) && (mSelectedKeyPath == 0))
            {
                mSelectedKeyPath = aPath;
            }
        }
        */
    }
    
    if(mSelectedKeyPath)
    {
        int aIndex = mSelectedKeyPath->mList.Find(mSelectedKeyNode);
        aIndex++;
        if((aIndex < 0) || (aIndex >= (mSelectedKeyPath->mList.mCount)))
        {
            aIndex = 0;
        }
        mSelectedKeyNode = (FMotionPathTemplateNode *)(mSelectedKeyPath->mList.Fetch(aIndex));
    }
    else
    {
        mSelectedKeyNode = 0;
    }
    
    gUtils->SetSelectedNode(gUtilsNode);
}

void UNode::MotionKeySelectPrev()
{
    /*
    
    if(mSelectedKeyPath == 0)
    {
        EnumList(FMotionPathTemplate, aPath, mKeyPathList)
        {
            if((aPath->mList.mCount > 0) && (mSelectedKeyPath == 0))
            {
                mSelectedKeyPath = aPath;
            }
        }
    }
    if(mSelectedKeyPath)
    {
        int aIndex = mSelectedKeyPath->mList.Find(mSelectedKeyNode);
        aIndex--;
        if((aIndex < 0) || (aIndex >= (mSelectedKeyPath->mList.mCount)))
        {
            aIndex = (mSelectedKeyPath->mList.mCount - 1);
        }
        mSelectedKeyNode = (FMotionPathTemplateNode *)(mSelectedKeyPath->mList.Fetch(aIndex));
    }
    else
    {
        mSelectedKeyNode = 0;
    }
    gUtils->SetSelectedNode(gUtilsNode);
    */
    
  
    if(mSelectedKeyPath)
    {
        int aIndex = mSelectedKeyPath->mList.Find(mSelectedKeyNode);
        aIndex--;
        if((aIndex < 0) || (aIndex >= (mSelectedKeyPath->mList.mCount)))
        {
            aIndex = (mSelectedKeyPath->mList.mCount - 1);
        }
        mSelectedKeyNode = (FMotionPathTemplateNode *)(mSelectedKeyPath->mList.Fetch(aIndex));
    }
    else
    {
        mSelectedKeyNode = 0;
    }
    gUtils->SetSelectedNode(gUtilsNode);
    
}

void UNode::MotionKeyDeleteSelected()
{
    if((mSelectedKeyPath != 0) && (mSelectedKeyNode != 0))
    {
        int aIndex = mSelectedKeyPath->mList.Find(mSelectedKeyNode);
        
        mSelectedKeyNode = (FMotionPathTemplateNode *)(mSelectedKeyPath->mList.Fetch(aIndex));
        
        mSelectedKeyPath->mList.Remove(mSelectedKeyNode);
        mSelectedKeyNode = 0;
        
        if(aIndex >= (mSelectedKeyPath->mList.mCount))
        {
            aIndex = (mSelectedKeyPath->mList.mCount - 1);
        }
        
        mSelectedKeyNode = (FMotionPathTemplateNode *)(mSelectedKeyPath->mList.Fetch(aIndex));
        
        
        gUtils->SetSelectedNode(gUtilsNode);
    }
    else
    {
        MotionKeySelectNext();
    }

}

void UNode::MotionKeyDeleteAll()
{
    /*
    
    EnumList(FMotionPathTemplate, aPath, mKeyPathList)
    {
        aPath->Clear();
    }
    
    */
}


UNodeSelection::UNodeSelection()
{
    mNode = 0;
    mType = 0;
    mUseFill = 1;
    mUseEdge = 1;
    mUsePoint = 2;
}

UNodeSelection::~UNodeSelection()
{
    //Log("UNodeSelection::~UNodeSelection()\n");
    Clear();
}

void UNodeSelection::Clear()
{
    mPoints.Clear();
    mPointsOutline.Clear();
    mBasePoints.Clear();
    
    mBaseCornerNormals.Clear();
    mBaseNormalsRight.Clear();
    mBaseNormalsLeft.Clear();
}

void UNodeSelection::SetNode(UNode *pNode)
{
    mNode = pNode;
    
    if(mNode)UpdateTransform();
}



void UNodeSelection::UpdateTransform()
{
    mPoints.Clone(mBasePoints);
    if(mNode)
    {
        mPoints.Transform(mNode->mWorldX, mNode->mWorldY, mNode->mObject->mScale * mNode->mObject->mScaleX, mNode->mObject->mScale * mNode->mObject->mScaleY, mNode->mObject->mRotation);
    }
}


void UNodeSelection::DrawPoints(bool pSelected, bool pFill, float pOpacity)
{
    UpdateTransform();
    if(mPoints.mCount <= 0)return;
    
    
    if(pSelected)pOpacity += (1.0f - pOpacity) * 0.1f;
    FColor aColor = FColor(0.33f, 0.20f, 0.88f, pOpacity);
    
    if(pSelected == false)
    {
        aColor.mRed *= 0.78f;
        aColor.mGreen *= 0.9f;
        aColor.mBlue *= 0.8f;
    }
    if(pFill)
    {
        aColor.mGreen *= 0.5f;
        aColor.mRed = (1.0f - aColor.mRed) * 0.8f;
    }
    if(pSelected)
    {
        FColor aColorRot = FColor(aColor.mGreen, (1.0f - aColor.mBlue) * 0.7f + (1.0f - aColor.mRed) * 0.3f, aColor.mRed * 0.8f + (aColor.mBlue) * 0.2f, aColor.mAlpha);
        aColor = aColorRot;
    }
    
    Graphics::SetColor(aColor);
    for(int i=0;i<mPoints.mCount;i++)
    {
        float aX = mPoints.mX[i];
        float aY = mPoints.mY[i];
        
        if(pSelected)Graphics::DrawRect(aX - 3.0f, aY - 3.0f, 7.0f, 7.0f);
        Graphics::DrawRect(aX - 1.0f, aY - 1.0f, 3.0f, 3.0f);
        
        
    }
}

void UNodeSelection::DrawEdges(bool pSelected, bool pFill, float pOpacity)
{
    UpdateTransform();
    if(mPoints.mCount <= 0)return;
    
    float aX = 0.0f;float aY = 0.0f;
    float aLastX = mPoints.mX[mPoints.mCount-1];float aLastY = mPoints.mY[mPoints.mCount-1];
    
    if(pSelected)
    {
        pOpacity += (1.0f - pOpacity) * 0.1f;
    }
    
    FColor aColor = FColor(0.85f, 0.78f, 0.80f, pOpacity);
    
    if(pSelected == false)
    {
        aColor.mRed *= 0.78f;
        aColor.mGreen *= 0.9f;
        aColor.mBlue *= 0.8f;
    }
    
    if(pFill)
    {
        aColor.mGreen *= 0.5f;
        aColor.mRed = (1.0f - aColor.mRed) * 0.8f;
    }
    
    if(pSelected)
    {
        FColor aColorRot = FColor(aColor.mGreen, (1.0f - aColor.mBlue) * 0.7f + (1.0f - aColor.mRed) * 0.3f, aColor.mRed * 0.8f + (aColor.mBlue) * 0.2f, aColor.mAlpha);
        aColor = aColorRot;
    }
    
    float aWidth = 1.0f;
    if((pFill == false) && (pSelected == true))aWidth = 3.0f;
    
    Graphics::SetColor(aColor);
    for(int i=0;i<mPoints.mCount;i++)
    {
        aX = mPoints.mX[i];aY = mPoints.mY[i];
        Graphics::DrawLine(aLastX, aLastY, aX, aY, aWidth);
        aLastX = aX;aLastY = aY;
    }
}

void UNodeSelection::DrawEdgesOffset(bool pSelected, bool pFill, float pOpacity)
{
    
}

void UNodeSelection::DrawLinkStartMarkers(bool pPoints, float pOpacity)
{
    UpdateTransform();
    if(mPoints.mCount <= 0)return;
    
    float aX = 0.0f;float aY = 0.0f;
    float aLastX = mPoints.mX[mPoints.mCount-1];float aLastY = mPoints.mY[mPoints.mCount-1];
    
    
    if(pPoints == false)
    {
        Graphics::SetColor(0.99f, 0.99f, 0.99f, 1.0f);
        for(int i=0;i<mPoints.mCount;i++)
        {
            aX = mPoints.mX[i];aY = mPoints.mY[i];
            Graphics::DrawLine(aLastX, aLastY, aX, aY, 3);
            aLastX = aX;aLastY = aY;
        }
        
        Graphics::SetColor(0.8f, 0.33f, 0.22f, pOpacity);
        for(int i=0;i<mPoints.mCount;i++)
        {
            aX = mPoints.mX[i];aY = mPoints.mY[i];
            Graphics::DrawLine(aLastX, aLastY, aX, aY, 1);
            aLastX = aX;aLastY = aY;
        }
    }
    else
    {
        
        Graphics::SetColor(0.99f, 0.99f, 0.99f, 1.0f);
        for(int i=0;i<mPoints.mCount;i++)
        {
            Graphics::DrawPoint(mPoints.mX[i], mPoints.mY[i], 10.0f);
        }
        
        Graphics::SetColor(0.8f, 0.33f, 0.22f, pOpacity);
        for(int i=0;i<mPoints.mCount;i++)
        {
            Graphics::DrawPoint(mPoints.mX[i], mPoints.mY[i], 6.0f);
        }
    }
}

void UNodeSelection::DrawLinkEndMarkers(bool pPoints, float pOpacity)
{
    UpdateTransform();
    if(mPoints.mCount <= 0)return;
    float aX = 0.0f;float aY = 0.0f;
    float aLastX = mPoints.mX[mPoints.mCount-1];float aLastY = mPoints.mY[mPoints.mCount-1];
    if(pPoints == false)
    {
        Graphics::SetColor(0.99f, 0.99f, 0.99f, 1.0f);
        for(int i=0;i<mPoints.mCount;i++)
        {
            aX = mPoints.mX[i];aY = mPoints.mY[i];
            Graphics::DrawLine(aLastX, aLastY, aX, aY, 3);
            aLastX = aX;aLastY = aY;
        }
        
        Graphics::SetColor(0.33f, 0.8f, 0.22f, pOpacity);
        for(int i=0;i<mPoints.mCount;i++)
        {
            aX = mPoints.mX[i];aY = mPoints.mY[i];
            Graphics::DrawLine(aLastX, aLastY, aX, aY, 1);
            aLastX = aX;aLastY = aY;
        }
    }
    else
    {
        Graphics::SetColor(0.99f, 0.99f, 0.99f, 1.0f);
        for(int i=0;i<mPoints.mCount;i++)Graphics::DrawPoint(mPoints.mX[i], mPoints.mY[i], 10.0f);
        Graphics::SetColor(0.33f, 0.8f, 0.22f, pOpacity);
        for(int i=0;i<mPoints.mCount;i++)Graphics::DrawPoint(mPoints.mX[i], mPoints.mY[i], 6.0f);
    }
}

void UNodeSelection::SetPath(FMotionPathTemplate *pPath, UNode *pNode, int pType)
{
    Clear();
    
    
    //pRadius
    
    if(pNode)
    {
        if(pType == SPAWN_SOURCE_POLYGON)
        {
            
            mBasePoints.Clear();
            pPath->WritePointsToList(&mBasePoints);
            
            
            //EnumList(pNode->mTemplate.m , <#__NAME__#>, <#__LIST__#>)
            
        }
        if(pType == SPAWN_SOURCE_POINT_CLOUD)
        {
            mBasePoints.Clear();
            pPath->WritePointsToList(&mBasePoints);
            
        }
    }
    
    
}

void UNodeSelection::SetCirc(float pRadius)
{
    Clear();
    
    mBasePoints.GenerateCircle(pRadius);
}

void UNodeSelection::SetRect(float pWidth, float pHeight)
{
    Clear();
    
    mBasePoints.Clear();
    mBasePoints.Add(-(pWidth / 2.0f), - (pHeight / 2.0f));
    mBasePoints.Add( (pWidth / 2.0f), - (pHeight / 2.0f));
    mBasePoints.Add( (pWidth / 2.0f),   (pHeight / 2.0f));
    mBasePoints.Add(-(pWidth / 2.0f),   (pHeight / 2.0f));
}

/*
UNodeExportStat::UNodeExportStat(FString pStatName, FString pValue)
{
    mStatName = pStatName.c();
    mValueString = pValue.c();
}

UNodeExportStat::UNodeExportStat(FString pStatName, int pValue)
{
    mStatName = pStatName.c();
    mValueString = FString(pValue).c();
}

UNodeExportStat::UNodeExportStat(FString pStatName, float pValue)
{
    mStatName = pStatName.c();
    mValueString = FString(pValue, 5).c();
}



UNodeExportStat::UNodeExportStat(FString pVariableName, FString pStatName, FString pValue)
{
    mVariableName = pVariableName.c();
    mStatName = pStatName.c();
    mValueString = pValue.c();
}

UNodeExportStat::UNodeExportStat(FString pVariableName, FString pStatName, int pValue)
{
    mVariableName = pVariableName.c();
    mStatName = pStatName.c();
    mValueString = FString(pValue).c();
}

UNodeExportStat::UNodeExportStat(FString pVariableName, FString pStatName, float pValue)
{
    mVariableName = pVariableName.c();
    mStatName = pStatName.c();
    mValueString = FString(pValue, 5).c();
}

UNodeExportStat::UNodeExportStat()
{
    
}

UNodeExportStat::~UNodeExportStat()
{
    
}

FString	UNodeExportStat::Get()
{
    FString aReturn = "";
    
    
    aReturn += mStatName;
    aReturn += " = ";
    aReturn += mValueString;
    aReturn += ";\n";
    
    return aReturn;
    
}
*/


