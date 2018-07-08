#include "UPathMaker.h"
#include "UMainCanvas.h"
#include "FApp.h"
#include "FLine.h"


UPathMaker::UPathMaker()
{
    mNode = gUtilsNode;
    TransformRead(mNode);
    
    SetStaticTransform(true);
    
    //SetTransformScale(gUtilWS->GetAbsoluteTransformScale());
    //SetTransformX(gUtilWS->GetAbsoluteTransformX());
    //SetTransformY(gUtilWS->GetAbsoluteTransformY());
    
    
    SetFrame(0.0f, 0.0f, gDeviceWidth - 50, gDeviceHeight - 50);
    
    
    //SetSize(gUtils->mWidth, gUtils->mHeight);
    
    mMode = GKMTV_MODE_CREATE_POINTS;
    mPathType = UTIL_PATH_TYPE_MOVEMENT;
    mStartMode = UTIL_PATH_TYPE_POLY;
    
    
    mDragTranslateShiftX = 0.0f;
    mDragTranslateShiftY = 0.0f;
    
    mBackgroundColor = FColor(0.08f, 0.45f, 0.65f, 0.25f);
    
    mSelectedPath = 0;
    mSelectedPathLockTarget = 0;
    
    
    mDrawCenter = true;
    mDrawEdges = true;
    mDrawEdgesClosed = false;
    mDrawPoints = true;
    mDrawReference = true;
    mDrawNumbers = false;
    
    mSymmetryEnabled = false;
    mSymmetryHorizontal = false;
    mSymmetrySide = false;
    
    
    
    mSymmetryCenterX = mTranX;
    mSymmetryCenterY = mTranY;
    
    
    mSprite = 0;
    mSpriteSequence = 0;
    mSpriteSequenceFrame = 0.0f;
    mSpriteSequenceFrameUpdate = true;
    
    mOpacity = 0.75f;
    
    mTanLockDir = false;
    
    mAllowDragPoint = true;
    mAllowDragTan = true;
    
    mSprite = 0;
    
    mSelectedPointIndex = -1;
    mSelectedTanSide = 0;
    
    mDragTouchStartX = 0;
    mDragTouchStartY = 0;
    
    
    
    
    mDragMode = -1;
    
    mDragging = false;
    mDragData = 0;
    
    mDragTouchStartX = 0.0f;
    mDragTouchStartY = 0.0f;
    
    mDragNodeStartX = 0.0f;
    mDragNodeStartY = 0.0f;
    
    mCreateNewPath = true;
    
    mPathMakerMenu = new UPathMakerMenu();
    AddSubview(mPathMakerMenu);
    
    mPathMakerMenu->SetPathMaker(this);
    
    mPathMakerMenu->LayoutSubviews();
    
    mPathMakerMenu->SetPos(60.0f, 80.0f);
    
    mPathMakerMenu->Expand();
    
    mPathMakerMenu->Refresh();
    
}

UPathMaker::~UPathMaker()
{
    EnumList(FMotionPathTemplate, aPath, mPathList)
    {
        if(aPath->mList.mCount <= 0)
        {
            gUtils->DeleteMotionPath(aPath);
        }
    }
    
    FList aPathOut;
    GetAbsolutePaths(&aPathOut);
    gUtils->PathSelect(&aPathOut, mPathType);
}

void UPathMaker::SetUp(UNode *pNode, int pPathType)
{
    mPathType = pPathType;
    TransformRead(pNode);
    
    if(pNode)
    {
        if(pNode->mSpriteSequence)
        {
            mSpriteSequence = pNode->mSpriteSequence;
        }
        else if(pNode->mSprite)
        {
            mSprite = pNode->mSprite;
        }
        
        if((pPathType == UTIL_PATH_TYPE_POINT_CLOUD) || (pPathType == UTIL_PATH_TYPE_POLY))
        {
            FList *aNodePathList = &(pNode->mTemplate.mSpawnSourcePolygonList);
            if(pPathType == UTIL_PATH_TYPE_POINT_CLOUD) aNodePathList = &(pNode->mTemplate.mSpawnSourcePointCloudList);
            
            if(aNodePathList != 0)
            {
                for(int i=0;i<aNodePathList->mCount;i++)
                {
                    FMotionPathTemplate *aExPath = (FMotionPathTemplate *)(aNodePathList->Fetch(i));
                    
                    if(aExPath != 0)
                    {
                        FMotionPathTemplate *aExPathAbs = aExPath->GetPathAbs();
                        
                        aExPathAbs = aExPathAbs->Clone();
                        aExPath = aExPath->Clone();
                        
                        float aSX = mTranScale * mTranScaleX;
                        float aSY = mTranScale * mTranScaleY;
                        
                        aExPath->Transform(mTranX, mTranY, aSX, aSY, mTranRotation);
                        aExPath->mPathAbs = 0;
                        
                        aExPath->mPathAbs = aExPathAbs;
                        
                        mPathList.Add(aExPath);
                    }
                }
            }
        }
        else
        {
            
            //mMotionPath
            
            
            FMotionPathTemplate *aExPath = pNode->mMotionPath.Clone();
            FMotionPathTemplate *aExPathAbs = pNode->mMotionPath.GetPathAbs()->Clone();
            
            float aSX = mTranScale * mTranScaleX;
            float aSY = mTranScale * mTranScaleY;
            
            
            aExPath->Transform(mTranX, mTranY, aSX, aSY, mTranRotation);
            aExPath->mPathAbs = 0;
            
            aExPath->mPathAbs = aExPathAbs;
            
            mPathList.Add(aExPath);
        }
    }
    
    if(pPathType == UTIL_PATH_TYPE_POINT_CLOUD)
    {
        mStartMode = UTIL_PATH_TYPE_POINT_CLOUD;
        mDrawEdges = false;
        mDrawEdgesClosed = false;
    }
    
    if(pPathType == UTIL_PATH_TYPE_POLY)
    {
        mStartMode = UTIL_PATH_TYPE_POLY;
        mDrawEdges = true;
        mDrawEdgesClosed = true;
    }
    
    
    bool aExists = false;
    EnumList(FMotionPathTemplate, aPath, mPathList)
    {
        if(aPath->mList.mCount > 0)
        {
            aExists = true;
        }
    }
    
    if(aExists)
    {
        mMode = GKMTV_MODE_SELECT_POINTS;
        mCreateNewPath = false;
    }
    else
    {
        mMode = GKMTV_MODE_CREATE_POINTS;
        mCreateNewPath = true;
    }
}


void UPathMaker::Update()
{
    if(mSpriteSequenceFrameUpdate)
    {
        if(mSpriteSequence)
        {
            mSpriteSequenceFrame += 0.5f;
            
            //if(mSpriteSequenceFrame >= mSpriteSequence->)
        }
    }
    
    EnumList(FMotionPathTemplate, aPath, mPathList)
    {
        aPath->Update();
    }
    
}

void UPathMaker::Draw()
{
    Graphics::SetColor(mBackgroundColor);
    
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    Graphics::SetColor();
    
    Graphics::Translate(mDragTranslateShiftX, mDragTranslateShiftY, 0.0f);
    Graphics::SetColor(mOpacity);
    
    float aSX = mTranScale * mTranScaleX;
    float aSY = mTranScale * mTranScaleY;
    
    
    if(mSpriteSequence)
    {
        mSpriteSequence->DrawScaled(mSpriteSequenceFrame, mTranX, mTranY, aSX, aSY, mTranRotation);
    }
    else if(mSprite)
    {
        mSprite->DrawScaled(mTranX, mTranY, aSX, aSY, mTranRotation);
    }
    
    float aOpacity = mOpacity;
    EnumList(FMotionPathTemplate, aPath, mPathList)
    {
        if((mSymmetryEnabled == false) || (aPath != mSelectedPath))
        {
            
            aOpacity = mOpacity;
            
            bool aIsSelected = IsSelected(aPath);
            bool aIsSelectable = IsSelectable(aPath);
            
            int aSelectedPointIndex = mSelectedPointIndex;
            int aSelectedTanIndex = mSelectedPointIndex;
            
            if(aIsSelected)
            {
                Graphics::SetColor(0.2, 0.9f, 0.05f, 0.25f);
                aPath->DrawTriangles();
                Graphics::SetColor();
                
                if(mDragMode == GKMTV_MODE_SELECT_TANGENTS)aSelectedPointIndex = -1;
                else if((mDragMode == GKMTV_MODE_CREATE_POINTS) || (mDragMode == GKMTV_MODE_SELECT_POINTS))aSelectedTanIndex = -1;
            }
            else
            {
                Graphics::SetColor(0.5f, 0.9f, 0.05f, 0.70f);
                aPath->DrawTriangles();
                Graphics::SetColor();
                
                aOpacity *= 0.6f;
                
                if(aIsSelectable == false)
                {
                    aOpacity *= 0.4f;
                }
                
                aSelectedPointIndex = -1;
                aSelectedTanIndex = -1;
            }
            
            if(mDrawEdges)
            {
                if(aIsSelected)
                {
                    
                    Graphics::SetColor(1.0f, 0.3f, 0.3f, aOpacity);
                    aPath->DrawEdges(2);
                    
                    
                    Graphics::SetColor(0.2f, 0.5f, 0.6f, aOpacity + (1 - aOpacity) * 0.5f);
                    aPath->DrawEdges(1);
                }
                else
                {
                    Graphics::SetColor(0.33f, 0.33f, 0.33f, aOpacity);
                    aPath->DrawEdges(1);
                }
            }
            
            
            if(mDrawPoints)
            {
                if(aIsSelected)
                {
                    Graphics::SetColor(0.0f, 0.4f, 0.7f, 1.0f);
                    aPath->DrawPointsUnselected(8.0f, aSelectedPointIndex);
                    
                    Graphics::SetColor(0.7f, 0.6f, 0.2f, aOpacity);
                    aPath->DrawPointsUnselected(5.0f, aSelectedPointIndex);
                    aPath->DrawPointsSelected(5.0f, aSelectedPointIndex);
                }
                else
                {
                    Graphics::SetColor(0.55f, 0.55f, 0.55f, aOpacity);
                    aPath->DrawPointsUnselected(6.0f, -1);
                    
                    Graphics::SetColor(0.55f, 0.55f, 0.55f, aOpacity);
                    aPath->DrawPointsUnselected(4.0f, -1);
                }
            }
            
            if(mMode == GKMTV_MODE_SELECT_TANGENTS)
            {
                Graphics::SetColor(0.72f, 0.11f, 1.0f, 0.85f * aOpacity);
                aPath->DrawTangentsUnselected(2.0f, aSelectedTanIndex, mSelectedTanSide);
                Graphics::SetColor(0.25f, 0.11f, 1.0f, 0.85f * aOpacity);
                aPath->DrawTangentsSelected(2.0f * 1.35f, aSelectedTanIndex, mSelectedTanSide);
            }
            
            
            
            
            if(mDrawNumbers)
            {
                Graphics::BlendSetPremultiplied();
                Graphics::SetColor(1.0f, 1.0f, 0.8f, 0.9f * aOpacity);
                
                for(int i=0;i<aPath->mList.mCount;i++)
                {
                    
                    
                    gAppBase->mSysFont.Center(FString(i + 1).c(), aPath->GetPointX(i), aPath->GetPointY(i) - 40.0f);
                }
                
                Graphics::BlendSetAlpha();
                
            }
            
        }
    }
    
    
    
    if(mSymmetryEnabled)
    {
        if(mDrawReference)
        {
            Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.6f * mOpacity);
            
            Graphics::DrawPoint(mSymmetryCenterX, mSymmetryCenterY, 8.0f);
            
            if(mSymmetryHorizontal)
            {
                Graphics::DrawLine(mSymmetryCenterX - 10.0f, mSymmetryCenterY, mSymmetryCenterX + 20.0f, mSymmetryCenterY);
                Graphics::DrawLine(mSymmetryCenterX, mSymmetryCenterY - 500.0f, mSymmetryCenterX, mSymmetryCenterY + 500.0f);
                
            }
        }
        
        if(mSelectedPath)
        {
            SymmetrySlice(mSymmetryHorizontal, mSymmetrySide);
            
        }
    }
    
    
    if(mMode == GKMTV_MODE_MAKE_TRIANGLES)
    {
        if(mSelectedPath)
        {
            float aX[3];
            float aY[3];
            
            if(mTriangleSelectionIndex1 != -1)
            {
                
                aX[0] = mSelectedPath->GetPointX(mTriangleSelectionIndex1);
                aY[0] = mSelectedPath->GetPointY(mTriangleSelectionIndex1);
                
                
                
                if(mTriangleSelectionIndex2 != -1)
                {
                    aX[1] = mSelectedPath->GetPointX(mTriangleSelectionIndex2);
                    aY[1] = mSelectedPath->GetPointY(mTriangleSelectionIndex2);
                    
                    
                    Graphics::SetColor(1.0f, 0.2f, 0.2f, 1.0f);
                    Graphics::DrawLine(aX[0], aY[0], aX[1], aY[1], 2.0f);
                    
                    if(mTriangleSelectionIndex3 != -1)
                    {
                        
                        aX[2] = mSelectedPath->GetPointX(mTriangleSelectionIndex3);
                        aY[2] = mSelectedPath->GetPointY(mTriangleSelectionIndex3);
                        
                        
                        Graphics::DrawLine(aX[1], aY[1], aX[2], aY[2], 2.0f);
                        Graphics::DrawLine(aX[0], aY[0], aX[2], aY[2], 2.0f);
                        
                        
                        Graphics::SetColor(0.0f, 1.0f, 0.6f, 1.0f);
                        Graphics::DrawPoint(aX[2], aY[2], 6.0f);
                        
                        Graphics::SetColor(1.0f, 1.0f, 0.6f, 1.0f);
                        Graphics::DrawPoint(aX[2], aY[2], 4.0f);
                        
                        
                    }
                    
                    
                    Graphics::SetColor(0.0f, 1.0f, 0.6f, 1.0f);
                    Graphics::DrawPoint(aX[1], aY[1], 6.0f);
                    
                    Graphics::SetColor(1.0f, 1.0f, 0.6f, 1.0f);
                    Graphics::DrawPoint(aX[1], aY[1], 4.0f);
                    
                }
                
                
                Graphics::SetColor(0.0f, 1.0f, 0.6f, 1.0f);
                Graphics::DrawPoint(aX[0], aY[0], 6.0f);
                
                Graphics::SetColor(1.0f, 1.0f, 0.6f, 1.0f);
                Graphics::DrawPoint(aX[0], aY[0], 4.0f);
            }
        }
    }
    
    if(mDrawCenter)
    {
        Graphics::SetColor(1.0f, 0.6f, 0.6f);
        Graphics::DrawLine(mTranX, mTranY - 200, mTranX, mTranY + 200, 2);
        Graphics::DrawLine(mTranX - 50, mTranY, mTranX + 50, mTranY, 2);
        Graphics::SetColor();
    }
    
    
    /*
    if(mSelectedPath)
    {
        if(mSelectedPath->mList.mCount > 1)
        {
            int aStartIndex = 0;
            int aEndIndex = mSelectedPath->mList.mCount - 1;
            
            while(aStartIndex < mSelectedPath->mList.mCount)
            {
                FMotionPathTemplateNode *aNodeStart = (FMotionPathTemplateNode *)(mSelectedPath->mList.Fetch(aStartIndex));
                FMotionPathTemplateNode *aNodeEnd = (FMotionPathTemplateNode *)(mSelectedPath->mList.Fetch(aEndIndex));
                
                float aDirX1 = aNodeStart->mTanOutX;
                float aDirY1 = aNodeStart->mTanOutY;
                
                float aDirX2 = aNodeEnd->mTanInX;
                float aDirY2 = aNodeEnd->mTanInY;
                
                float aX1 = aNodeStart->mX;
                float aY1 = aNodeStart->mY;
                
                float aX2 = aNodeEnd->mX;
                float aY2 = aNodeEnd->mY;
                
                float aAX = aDirX1;
                float aAY = aDirY1;
                
                float aBX = 3 * (aX2 - aX1) - 2 * aDirX1 + aDirX2;
                float aBY = 3 * (aY2 - aY1) - 2 * aDirY1 + aDirY2;
                
                float aCX = 2 * (aX1 - aX2) + aDirX1 - aDirX2;
                float aCY = 2 * (aY1 - aY2) + aDirY1 - aDirY2;
                
                for(float aPercent = 0.0f;aPercent<=1.0f;aPercent+=0.0125f)
                {
                    float aPercent2 = aPercent  * aPercent;
                    float aPercent3 = aPercent2 * aPercent;
                    
                    float aX = aX1 + aPercent * aAX + aPercent2 * aBX + aPercent3 * aCX;
                    float aY = aY1 + aPercent * aAY + aPercent2 * aBY + aPercent3 * aCY;
                    
                    Graphics::DrawRect(aX - 2.0f, aY - 2.0f, 5.0f, 5.0f);
                }
                
                aEndIndex = aStartIndex;
                aStartIndex++;
                
            }
        }
    }
    */
    
    
    Graphics::SetColor();
    Graphics::Translate(-mDragTranslateShiftX, -mDragTranslateShiftY, 0.0f);
}

void UPathMaker::TouchDown(float pX, float pY, void *pData)
{
    bool aShift = (gKeyPressed[DIK_LSHIFT]);
    bool aCtrl = (gKeyPressed[DIK_LCONTROL]);
    
    if((aShift == true) && (aCtrl == false))
    {
        mMode = GKMTV_MODE_CREATE_POINTS;
        mCreateNewPath = true;
    }
    
    if((aShift == false) && (aCtrl == true))mMode = GKMTV_MODE_SELECT_POINTS;
    
    FindSelectablePaths();
    
    FMotionPathTemplate *aPreviousSelection = mSelectedPath;
    
    mDragTranslateShiftX = 0.0f;
    mDragTranslateShiftY = 0.0f;
    
    mSelectedPointIndex = -1;
    mDragging = false;
    mDragData = 0;
    mDragMode = -1;
    
    if(mMode == GKMTV_MODE_CREATE_POINTS)
    {
        if(mCreateNewPath == true)
        {
            PathSelectionClear();
            mSelectablePathList.Clear();
            
            mCreateNewPath = false;
            
            mSelectedPath = new FMotionPathTemplate();
            mSelectablePathList.Add(mSelectedPath);
            mPathList.Add(mSelectedPath);
            
        }
        else
        {
            if(mSelectedPath)
            {
                if(mSelectablePathList.Exists(mSelectedPath) == false)
                {
                    mSelectedPath = 0;
                }
            }
            
            if(mSelectedPath == 0)
            {
                if(mSelectablePathList.mCount > 0)
                {
                    mSelectedPath = (FMotionPathTemplate *)(mSelectablePathList.Last());
                    
                }
                else
                {
                    mSelectedPath = new FMotionPathTemplate();
                    mSelectablePathList.Add(mSelectedPath);
                    mPathList.Add(mSelectedPath);
                }
            }
            
            //SelectAnyPath();
        }
        
        mSelectedPath->AddPoint(pX, pY);
        mSelectedPointIndex = (mSelectedPath->Count() - 1);
        
        mDragging = false;
        mDragData = 0;
        
        mDragTouchStartX = 0.0f;
        mDragTouchStartY = 0.0f;
        
        mDragNodeStartX = 0.0f;
        mDragNodeStartY = 0.0f;
        
        //return;
    }
    
    
    
    int aClosestPoint = -1;
    float aClosestPointDist = 70.0f * 70.0f;
    
    int aClosestTan = -1;
    int aClosestTanSide = 0;
    
    float aClosestTanDist = 50.0f * 50.0f;
    
    FMotionPathTemplate *aClosestPointPath = 0;
    FMotionPathTemplate *aClosestTanPath = 0;
    
    EnumList(FMotionPathTemplate, aPath, mSelectablePathList)
    {
        
        float aCheckClosestPointDist = aClosestPointDist;
        int aCheckClosestPoint = aPath->GetClosestPointIndex(pX, pY, aCheckClosestPointDist);
        
        if(aCheckClosestPointDist <= aClosestPointDist)
        {
            aClosestPoint = aCheckClosestPoint;
            aClosestPointDist = aCheckClosestPointDist;
            aClosestPointPath = aPath;
        }
        
        float aCheckClosestTanDist = aClosestTanDist;
        int aCheckClosestTan = aPath->GetClosestTanIndex(pX, pY, aCheckClosestTanDist);
        int aCheckClosestTanSide = aPath->GetClosestTanSide(pX, pY);
        //if(aPath)
        
        if(aCheckClosestTanDist <= aClosestTanDist)
        {
            aClosestTan = aCheckClosestTan;
            aClosestTanDist = aCheckClosestTanDist;
            aClosestTanPath = aPath;
            aClosestTanSide = aCheckClosestTanSide;
        }
        
    }
    
    if((mMode == GKMTV_MODE_CREATE_POINTS) || (mMode == GKMTV_MODE_SELECT_POINTS))
    {
        
        if(aClosestPointPath)
        {
            mSelectedPath = aClosestPointPath;
            mSelectedPointIndex = aClosestPoint;
            
            if((mSelectedPointIndex != -1) && (mAllowDragPoint == true) && (mSelectedPath != 0))
            {
                mDragMode = GKMTV_MODE_SELECT_POINTS;
                
                mDragging = true;
                mDragData = pData;
                
                mDragTouchStartX = pX;
                mDragTouchStartY = pY;
                
                mDragNodeStartX = mSelectedPath->GetPointX(mSelectedPointIndex);
                mDragNodeStartY = mSelectedPath->GetPointY(mSelectedPointIndex);
            }
            
        }
    }
    
    if(mMode == GKMTV_MODE_SELECT_TANGENTS)
    {
        if(aClosestTanPath)
        {
            mSelectedPath = aClosestTanPath;
            mSelectedPointIndex = aClosestTan;
            mSelectedTanSide = aClosestTanSide;
            
            if((mSelectedPointIndex != -1) && (mAllowDragTan == true) && (mSelectedPath != 0))
            {
                mDragMode = GKMTV_MODE_SELECT_TANGENTS;
                
                mDragging = true;
                mDragData = pData;
                
                mDragTouchStartX = pX;
                mDragTouchStartY = pY;
                
                mDragNodeStartX = mSelectedPath->GetAbsoluteTanX(mSelectedPointIndex, mSelectedTanSide);
                mDragNodeStartY = mSelectedPath->GetAbsoluteTanY(mSelectedPointIndex, mSelectedTanSide);
                
            }
        }
    }
    
    if(mMode == GKMTV_MODE_MAKE_TRIANGLES)
    {
        if(mTriangleSelectionStep == 0)
        {
            mSelectedPath = aClosestPointPath;
            mTriangleSelectionIndex1 = aClosestPoint;
            mTrianglePointList.mCount = 0;
            
            if(mSelectedPath)
            {
                mDragging = true;
                mDragData = pData;
                
                mTriangleSelectionStep = 1;
                mSelectedPath->WritePointsToList(&mTrianglePointList);
                
                
            }
            else
            {
                mTriangleSelectionStep = 0;
            }
            
        }
        else
        {
            if(mSelectedPath)
            {
                
                mDragging = true;
                mDragData = pData;
            }
        }
        
    }
    
    if(mMode == GKMTV_MODE_CENTER)
    {
        mDragTranslateShiftX = 0.0f;
        mDragTranslateShiftY = 0.0f;
        
        mDragMode = GKMTV_MODE_CENTER;
        
        mDragging = true;
        mDragData = pData;
        
        mDragTouchStartX = pX;
        mDragTouchStartY = pY;
        
        //mDragNodeStartX = mPath.GetAbsoluteTanInX(mSelectedPointIndex);
        //mDragNodeStartY = mPath.GetAbsoluteTanInY(mSelectedPointIndex);
        
        mDragNodeStartX = GetTransformX();
        mDragNodeStartY = GetTransformY();
    }
    
    if(mSelectedPath)
    {
        if(mSelectedPath != aPreviousSelection)
        {
            mSelectedPathLockTarget = 0;
        }
    }
    else
    {
        mSelectedPathLockTarget = 0;
    }
    
    
    TouchMove(pX, pY, pData);
    
    mPathMakerMenu->Refresh();
}

void UPathMaker::TouchMove(float pX, float pY, void *pData)
{
    float aDiffX = mDragTouchStartX - pX;
    float aDiffY = mDragTouchStartY - pY;
    
    float aX = mDragNodeStartX - aDiffX;
    float aY = mDragNodeStartY - aDiffY;
    
    if((mDragging == true) && (mDragData == pData) && (mSelectedPath != 0))
    {
        if(mDragMode == GKMTV_MODE_SELECT_POINTS)
        {
            mSelectedPath->SetPoint(mSelectedPointIndex, aX, aY);
        }
        if(mDragMode == GKMTV_MODE_SELECT_TANGENTS)
        {
            mSelectedPath->SetAbsoluteTan(mSelectedPointIndex, mSelectedTanSide, aX, aY);
        }
    }
    
    
    
    if((mMode == GKMTV_MODE_MAKE_TRIANGLES) && (mDragging == true) && (mDragData == pData) && (mSelectedPath != 0))
    {
        float aBestDist = 60.0f;
        if(mTriangleSelectionStep == 1)
        {
            mTriangleSelectionIndex2 = mTrianglePointList.GetClosestIndex(pX, pY, aBestDist);
            
            if((aBestDist >= (10.0f * 10.0f)) || (mTriangleSelectionIndex2 == mTriangleSelectionIndex1))
            {
                mTriangleSelectionIndex2 = -1;
            }
            
        }
        if(mTriangleSelectionStep == 2)
        {
            mTriangleSelectionIndex3 = mTrianglePointList.GetClosestIndex(pX, pY, aBestDist);
            
            if((aBestDist >= (10.0f * 10.0f)) || (mTriangleSelectionIndex3 == mTriangleSelectionIndex2) || (mTriangleSelectionIndex3 == mTriangleSelectionIndex1))
            {
                mTriangleSelectionIndex3 = -1;
            }
            
        }
    }
    
    if((mDragging == true) && (mDragData == pData))
    {
        if(mDragMode == GKMTV_MODE_CENTER)
        {
            mDragTranslateShiftX = -(aDiffX);
            mDragTranslateShiftY = -(aDiffY);
        }
    }
}

void UPathMaker::TouchUp(float pX, float pY, void *pData)
{
    if((mDragging == true) && (mDragData == pData))
    {
        if(mDragMode == GKMTV_MODE_CENTER)
        {
            TouchMove(pX, pY, pData);
            SetTransformTranslate(mDragNodeStartX + mDragTranslateShiftX, mDragNodeStartY + mDragTranslateShiftY);
            mDragTranslateShiftX = 0.0f;
            mDragTranslateShiftY = 0.0f;
        }
    }
    
    if((mMode == GKMTV_MODE_MAKE_TRIANGLES) && (mDragging == true) && (mDragData == pData) && (mSelectedPath != 0))
    {
        
        if(mTriangleSelectionStep == 1)
        {
            if(mTriangleSelectionIndex2 != -1)
            {
                mTriangleSelectionStep = 2;
                
            }
        }
        else if(mTriangleSelectionStep == 2)
        {
            if(mTriangleSelectionIndex3 != -1)
            {
                mSelectedPath->mTriangleData.Add(mTriangleSelectionIndex1);
                mSelectedPath->mTriangleData.Add(mTriangleSelectionIndex2);
                mSelectedPath->mTriangleData.Add(mTriangleSelectionIndex3);
                
                mTriangleSelectionStep = 0;
                mTriangleSelectionIndex1 = -1;
                mTriangleSelectionIndex2 = -1;
                mTriangleSelectionIndex3 = -1;
            }
        }
    }
    
    
    mDragging = false;
    mDragData = 0;
    
    mPathMakerMenu->Refresh();
}

void UPathMaker::TouchFlush()
{
    
}

void UPathMaker::MouseWheel(int pDirection)
{
    bool aShift = (gKeyPressed[DIK_LSHIFT]);
    bool aCtrl = (gKeyPressed[DIK_LCONTROL]);
    
    if(true)
    {
        if((aShift == false) && (aCtrl == false))
        {
            if(pDirection > 0)PointSelectionNext();
            else PointSelectionPrev();
        }
        else if((aShift == false) && (aCtrl == true))
        {
            if(pDirection > 0)PathSelectionNext();
            else PathSelectionPrev();
        }
    }
}

void UPathMaker::KeyDown(int pKey)
{
    bool aUp = (pKey == DIK_UP);
    bool aDown = (pKey == DIK_DOWN);
    bool aLeft = (pKey == DIK_LEFT);
    bool aRight = (pKey == DIK_RIGHT);
    
    
    bool aArrow = (aUp || aDown || aLeft || aRight);
    bool aShift = (gKeyPressed[DIK_LSHIFT]);
    bool aCtrl = (gKeyPressed[DIK_LCONTROL]);
    
    if(aArrow)
    {
        if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)
        {
            if((aShift == false) && (aCtrl == false))
            {
                if(aUp)PointSelectionShift(0.0f, -1.0f);
                if(aDown)PointSelectionShift(0.0f, 1.0f);
                if(aRight)PointSelectionShift(1.0f, 0.0f);
                if(aLeft)PointSelectionShift(-1.0f, 0.0f);
                
            }
            else if((aShift == true) && (aCtrl == false))
            {
                if(aUp)PointSelectionShift(0.0f, -10.0f);
                if(aDown)PointSelectionShift(0.0f, 10.0f);
                if(aRight)PointSelectionShift(10.0f, 0.0f);
                if(aLeft)PointSelectionShift(-10.0f, 0.0f);
            }
            else if((aShift == false) && (aCtrl == true))
            {
                if(aUp)PathSelectionShift(0.0f, -1.0f);
                if(aDown)PathSelectionShift(0.0f, 1.0f);
                if(aRight)PathSelectionShift(1.0f, 0.0f);
                if(aLeft)PathSelectionShift(-1.0f, 0.0f);
            }
            else if((aShift == true) && (aCtrl == true))
            {
                if(aUp)PathSelectionShift(0.0f, -10.0f);
                if(aDown)PathSelectionShift(0.0f, 10.0f);
                if(aRight)PathSelectionShift(10.0f, 0.0f);
                if(aLeft)PathSelectionShift(-10.0f, 0.0f);
            }
        }
    }
    
    if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)
    {
        if(pKey == DIK_DELETE)
        {
            if((aShift == false) && (aCtrl == false))
            {
                PointSelectionDelete();
            }
            else if((aShift == false) && (aCtrl == true))
            {
                PathDeleteSelected();
            }
        }
    }
    
    if(pKey == DIK_S)
    {
        if(mSymmetryEnabled == false)
        {
            mSymmetryEnabled = true;
        }
        else
        {
            mSymmetryEnabled = false;
            
            if(aCtrl == false)
            {
                SymmetryApply();
            }
        }
    }
    
    if(pKey == DIK_H)mSymmetryHorizontal = !mSymmetryHorizontal;
    
    if(pKey == DIK_T)
    {
        
    }
    
    
    if(aCtrl)
    {
        
    }
    
    
    //EditNodeSprite(
    
    //
    mPathMakerMenu->Refresh();
}


void UPathMaker::SetMode(int pMode)
{
    mMode = pMode;
    
    if(mMode == GKMTV_MODE_MAKE_TRIANGLES)
    {
        mTriangleSelectionStep = 0;
        
        mTriangleSelectionIndex1 = -1;
        mTriangleSelectionIndex2 = -1;
        mTriangleSelectionIndex3 = -1;
        
    }
    
    
    
    
}

void UPathMaker::SymmetrySlice(bool pHor, bool pSide)
{
    
    
    if(mSelectedPath)
    {
        
        
        float aSymPlaneX1 = mSymmetryCenterX;
        float aSymPlaneY1 = mSymmetryCenterY;
        
        float aSymPlaneX2 = aSymPlaneX1;
        float aSymPlaneY2 = aSymPlaneY1;
        
        if(mSymmetryHorizontal)
        {
            aSymPlaneX1 -= 400.0f;
            aSymPlaneX2 += 400.0f;
            
        }
        else
        {
            aSymPlaneY1 -= 400.0f;
            aSymPlaneY2 += 400.0f;
        }
        
        //float aSymPlaneDirX =  Sin(mSymmetryRotation);
        //float aSymPlaneDirY = 1.0f;
        
        //float aSymPlaneX2 = aSymPlaneX1 + aSymPlaneDirX * 150.0f;
        //float aSymPlaneY2 = aSymPlaneY1 + aSymPlaneDirY * 150.0f;
        
        
        FPointList aPoints;
        mSelectedPath->WritePointsToList(&aPoints);
        
        aPoints.DrawPoints();
        
        FPointList aEdgeList1;
        FPointList aEdgeList2;
        
        aPoints.GenerateEdgeLists(&aEdgeList1, &aEdgeList2, false);
        aPoints.GetSymmetryFromEdges(&aEdgeList1, &aEdgeList2, false, aSymPlaneX1, aSymPlaneY1, aSymPlaneX2 - aSymPlaneX1, aSymPlaneY2 - aSymPlaneY1);
        
        mSymmetryEdgeList1.Reset();
        mSymmetryEdgeList2.Reset();
        
        mSymmetryEdgeListMirror1.Reset();
        mSymmetryEdgeListMirror2.Reset();
        
        for(int i=0;i<aEdgeList1.mCount;i++)
        {
            float aX1 = aEdgeList1.mX[i];
            float aY1 = aEdgeList1.mY[i];
            
            float aX2 = aEdgeList2.mX[i];
            float aY2 = aEdgeList2.mY[i];
            
            mSymmetryEdgeList1.Add(aX1, aY1);
            mSymmetryEdgeList2.Add(aX2, aY2);
            
            if(mSymmetryHorizontal)
            {
                aY1 = aSymPlaneY1 - (aY1 - aSymPlaneY1);
                aY2 = aSymPlaneY2 - (aY2 - aSymPlaneY1);
            }
            else
                
            {
                aX1 = aSymPlaneX1 - (aX1 - aSymPlaneX1);
                aX2 = aSymPlaneX2 - (aX2 - aSymPlaneX1);
            }
            
            mSymmetryEdgeListMirror1.Add(aX1, aY1);
            mSymmetryEdgeListMirror2.Add(aX2, aY2);
        }
        
        
        mSymmetryEdgeListMirror1.Reverse();
        mSymmetryEdgeListMirror2.Reverse();
        
        
        //aSymList.GetSymmetryFromEdges(&aSymEdgeList1, &aSymEdgeList2, true, aSymPlaneX1, aSymPlaneY1, aSymPlaneDirX, aSymPlaneDirY);
        
        Graphics::SetColor(0.25f, 0.75f, 0.6f, 0.85f);
        aPoints.DrawEdgeLists(&mSymmetryEdgeList1, &mSymmetryEdgeList2, 0, 2);
        aPoints.DrawEdgeLists(&mSymmetryEdgeListMirror1, &mSymmetryEdgeListMirror2, 0, 2);
        
        
        Graphics::SetColor(0.85f, 0.55f, 0.9f, 0.6f);
        aPoints.DrawEdgeLists(&mSymmetryEdgeList1, &mSymmetryEdgeList2, 1, 2);
        aPoints.DrawEdgeLists(&mSymmetryEdgeListMirror1, &mSymmetryEdgeListMirror2, 1, 2);
        //aSymList.DrawEdgeLists(&aSymEdgeList1, &aSymEdgeList2, 1, 2);
        
    }
}

void UPathMaker::SymmetryApply()
{
    SymmetrySlice(mSymmetryHorizontal, mSymmetrySide);
    
    if(mSelectedPath)
    {
        mSelectedPath->Clear();
        
        
        for(int i=0;i<mSymmetryEdgeList1.mCount;i++)
        {
            
            //mSymmetryEdgeList1
            
            float aX1 = mSymmetryEdgeList1.mX[i];
            float aY1 = mSymmetryEdgeList1.mY[i];
            
            float aX2 = mSymmetryEdgeList2.mX[i];
            float aY2 = mSymmetryEdgeList2.mY[i];
            
            mSelectedPath->AddEdge(aX1, aY1, aX2, aY2);
            
        }
        
        for(int i=0;i<mSymmetryEdgeListMirror1.mCount;i++)
        {
            
            //mSymmetryEdgeList1
            
            float aX1 = mSymmetryEdgeListMirror1.mX[i];
            float aY1 = mSymmetryEdgeListMirror1.mY[i];
            
            float aX2 = mSymmetryEdgeListMirror2.mX[i];
            float aY2 = mSymmetryEdgeListMirror2.mY[i];
            
            mSelectedPath->AddEdge(aX1, aY1, aX2, aY2);
            
        }
        
    }
}

void UPathMaker::PathSelectionDragLockToggle()
{
    if(mSelectedPath)
    {
        if(mPathList.Exists(mSelectedPath) == false)
        {
            //mSelectedPath = 0;
            PathSelectionClear();
        }
        else
        {
            if(mSelectedPathLockTarget == mSelectedPath)
            {
                mSelectedPathLockTarget = 0;
            }
            else
            {
                mSelectedPathLockTarget = mSelectedPath;
            }
        }
    }
    else
    {
        mSelectedPathLockTarget = 0;
    }
    
    FindSelectablePaths();
    mPathMakerMenu->Refresh();
}

void UPathMaker::PointSelectionTrianglesDeleteLast()
{
    if(mSelectedPath)
    {
        if(mSelectedPath->mTriangleData.mCount > 2)
        {
            mSelectedPath->mTriangleData.mCount -= 3;
            
            mTriangleSelectionIndex1 = -1;
            mTriangleSelectionIndex2 = -1;
            mTriangleSelectionIndex3 = -1;
            mTriangleSelectionStep = 0;
        }
    }
}

void UPathMaker::PointSelectionTrianglesDeleteAll()
{
    if(mSelectedPath)
    {
        mSelectedPath->mTriangleData.mCount = 0;
        
        mTriangleSelectionIndex1 = -1;
        mTriangleSelectionIndex2 = -1;
        mTriangleSelectionIndex3 = -1;
        mTriangleSelectionStep = 0;
    }
}

void UPathMaker::Print()
{
    
    FList aListAbs;
    GetAbsolutePaths(&aListAbs);
    
    
    FPointList aPointList;
    EnumList(FMotionPathTemplate, aPath, aListAbs)
    {
        
        aPath->WritePointsToList(&aPointList);
        
        FString aString = aPointList.GetPrintString("aPointList");
        Log("%s\n", aString.c());
        
        
        
        aString = aPath->mTriangleData.GetPrintString("aIndexList");
        Log("%s\n", aString.c());
        
        //delete aPathAbs;
    }
}

void UPathMaker::GetAbsolutePaths(FList *pList)
{
    float aAdjustX = mTranX;
    float aAdjustY = mTranY;
    float aAdjustSX = (mTranScale * mTranScaleX);
    float aAdjustSY = (mTranScale * mTranScaleY);
    float aAdjustRot = mTranRotation;
    
    EnumList(FMotionPathTemplate, aPath, mPathList)
    {
        if(aPath->mList.mCount > 0)
        {
            FMotionPathTemplate *aPathAbs = aPath->Clone();
            
            aPathAbs->Untransform(aAdjustX, aAdjustY, aAdjustSX, aAdjustSY, aAdjustRot);
            
            delete aPath->mPathAbs;
            
            aPath->mPathAbs = aPathAbs;
            
            pList->Add(aPathAbs);
        }
    }
}


void UPathMaker::PathSelectionClear()
{
    mSelectedPath = 0;
    mSelectedPathLockTarget = 0;
    mDragMode = -1;
    mDragging = false;
    mDragData = 0;
}

void UPathMaker::PathSelectionNext()
{
    int aIndex = mPathList.Find(mSelectedPath);
    if(aIndex != -1)
    {
        aIndex++;
        if(aIndex >= mPathList.mCount)aIndex = 0;
        mSelectedPath = ((FMotionPathTemplate *)mPathList.Fetch(aIndex));
    }
    else
    {
        mSelectedPath = ((FMotionPathTemplate *)mPathList.Last());
    }
    mSelectedPathLockTarget = 0;
    FindSelectablePaths();
    mPathMakerMenu->Refresh();
}

void UPathMaker::PathSelectionPrev()
{
    int aIndex = mPathList.Find(mSelectedPath);
    if(aIndex != -1)
    {
        aIndex--;
        if(aIndex < 0)aIndex = (mPathList.mCount - 1);
        mSelectedPath = ((FMotionPathTemplate *)mPathList.Fetch(aIndex));
    }
    else
    {
        mSelectedPath = ((FMotionPathTemplate *)mPathList.First());
    }
    mSelectedPathLockTarget = 0;
    FindSelectablePaths();
    mPathMakerMenu->Refresh();
}

void UPathMaker::PathSelectionShift(float pMoveX, float pMoveY)
{
    if(mSelectedPath)
    {
        for(int i = 0; i < mSelectedPath->mList.mCount; i++)
        {
            float aX = mSelectedPath->GetPointX(mSelectedPointIndex);
            float aY = mSelectedPath->GetPointY(mSelectedPointIndex);
            
            aX += pMoveX;
            aY += pMoveY;
            
            mSelectedPath->SetPoint(mSelectedPointIndex, aX, aY);
            
        }
    }
}

void UPathMaker::PathDeleteSelected()
{
    //int aSelectionIndex = mPathList.Find(mSelectedPath);
    
    if(mSelectedPath)
    {
        mSelectedPathLockTarget = 0;
        mPathList.Remove(mSelectedPath);
    }
    else
    {
        
    }
    mSelectedPath = 0;
    PathSelectionClear();
    PathSelectionNext();
    mPathMakerMenu->Refresh();
}

void UPathMaker::PathDeleteAll()
{
    PathSelectionClear();
    mPathList.RemoveAll();
    mPathMakerMenu->Refresh();
}


void UPathMaker::PointSelectionNext()
{
    mSelectedPathLockTarget = 0;
    if(mSelectedPath)mSelectedPointIndex = mSelectedPath->GetNextIndex(mSelectedPointIndex);
    else{PathSelectionClear();PathSelectionNext();}
    mPathMakerMenu->Refresh();
}

void UPathMaker::PointSelectionPrev()
{
    mSelectedPathLockTarget = 0;
    if(mSelectedPath)mSelectedPointIndex = mSelectedPath->GetPrevIndex(mSelectedPointIndex);
    else{PathSelectionClear();PathSelectionPrev();}
    mPathMakerMenu->Refresh();
}

void UPathMaker::PointSelectionClear()
{
    mSelectedPointIndex=-1;
    mPathMakerMenu->Refresh();
}

void UPathMaker::PointSelectionDelete()
{
    
    //mSymmetryRotation
    
    if(mSelectedPath)
    {
        mSelectedPointIndex = mSelectedPath->NodeDelete(mSelectedPointIndex);
        if(mSelectedPath->Count() <= 0)PathDeleteSelected();
    }
    else
    {
        PathSelectionClear();
        PathSelectionPrev();
    }
    mPathMakerMenu->Refresh();
}

void UPathMaker::PointSelectionInsert()
{
    if(mSelectedPath)
    {
        mSelectedPointIndex = mSelectedPath->NodeInsert(mSelectedPointIndex);
    }
    else
    {
        PathSelectionPrev();
    }
}

void UPathMaker::PointSelectionShift(float pMoveX, float pMoveY)
{
    if(mSelectedPath)
    {
        float aX = mSelectedPath->GetPointX(mSelectedPointIndex);
        float aY = mSelectedPath->GetPointY(mSelectedPointIndex);
        
        aX += pMoveX;
        aY += pMoveY;
        
        mSelectedPath->SetPoint(mSelectedPointIndex, aX, aY);
    }
}




void UPathMaker::FindSelectablePaths()
{
    mSelectablePathList.Clear();
    
    if((mSelectedPath != 0) && (mSelectedPathLockTarget != 0))
    {
        EnumList(FMotionPathTemplate, aPath, mPathList)
        {
            if(aPath == mSelectedPathLockTarget)
            {
                mSelectablePathList.Add(aPath);
            }
        }
    }
    else
    {
        mSelectedPathLockTarget = 0;
        
        EnumList(FMotionPathTemplate, aPath, mPathList)
        {
            mSelectablePathList.Add(aPath);
        }
    }
    
    mPathMakerMenu->Refresh();
}

bool UPathMaker::IsSelectable(FMotionPathTemplate *pPath)
{
    bool aResult = false;
    
    if(pPath)
    {
        if(mSelectedPathLockTarget != 0)
        {
            if(pPath == mSelectedPathLockTarget)aResult = true;
            else aResult = false;
        }
        else
        {
            aResult = true;
        }
    }
    
    return aResult;
}

bool UPathMaker::IsSelected(FMotionPathTemplate *pPath)
{
    bool aResult = false;
    
    if(pPath)
    {
        if(mSelectedPath != 0)
        {
            if(pPath == mSelectedPath)aResult = true;
            else aResult = false;
        }
        else
        {
            aResult = false;
        }
    }
    
    return aResult;
}


void UPathMaker::TransformRead(UNode *pNode)
{
    if(pNode)
    {
        mTranX = pNode->mWorldX;
        mTranY = pNode->mWorldY;
        mTranScale = pNode->mObject->mScale;
        mTranScaleX = pNode->mObject->mScaleX;
        mTranScaleY = pNode->mObject->mScaleY;
        mTranRotation = pNode->mObject->mRotation;
    }
    else
    {
        mTranX = gAppWidth2 + gAppWidth2 * 0.4f;
        mTranY = gAppHeight2 - 80.0f;
        mTranScale = 1.0f;
        mTranScaleX = 1.0f;
        mTranScaleY = 1.0f;
        mTranRotation = 0.0f;
    }
    
    if(gUtils)
    {
        mTranScale *= gUtils->mPathEditScale;
        
        
        mTranX = (gUtils->mEdgeLeft + gUtils->mEdgeRight) / 2.0f;
        mTranY = (gUtils->mEdgeTop + gUtils->mEdgeBottom) / 2.0f;
    }
    
    mSymmetryCenterX = mTranX;
    mSymmetryCenterY = mTranY;
    
}


UPathMakerMenu::UPathMakerMenu()// : UMenu()
{
    mPathMaker = 0;
    
    SetText("Motion Path");
    
    
    
    
    
    
    
    
    mSymmetryPane = new UPathMakerSymmetryPane();
    AddLine(mSymmetryPane);
    
    
    
    
    
    mPathPane = new UMenuPane("Path Segments", true);
    AddLine(mPathPane);
    
    
    mPathSegmentMode = new USegment(4);
    mPathSegmentMode->SetTitles("+", "[Pnt]", "[Tan]", "[TRIS]");
    mPathPane->AddLine(mPathSegmentMode);
    
    
    mPathButtonCreateNew = new UButton("Create");
    mPathButtonCreateNew->StyleSetCheckBox();
    
    mPathButtonPrint = new UButton("Print!");
    mPathPane->AddLine(mPathButtonCreateNew, mPathButtonPrint);
    
    mPathButtonDelete = new UButton("Path-D");
    mPathButtonDeleteAll = new UButton("P-D-All");
    mPathButtonTriangleDeleteLast = new UButton("Tri-D-L");
    mPathButtonTriangleDeleteAll = new UButton("Tri-D-A");
    
    
    mPathPane->AddLine(mPathButtonDeleteAll, mPathButtonDelete, mPathButtonTriangleDeleteAll, mPathButtonTriangleDeleteLast);
    
    
    mPathSelectButtonLock = new UButton("Sel-Lock");
    mPathSelectButtonLock->StyleSetCheckBox();
    
    mPathSelectButtonNext = new UButton("Sel-Next");
    mPathSelectButtonPrev = new UButton("Sel-Prev");
    
    mPathPane->AddLine(mPathSelectButtonLock, mPathSelectButtonNext, mPathSelectButtonPrev);
    
    
    //mPaneMain = new UMenuPane("Main", true);
    //AddMenuItems(mPaneMain);
    
    //mSegmentMode = new USegment(5);
    //mPaneMain->AddLine(mSegmentMode);
    //mSegmentMode->SetTitles("+", "[Pnt]", "[Tan]", "[Ref]", "[SYM]", "[AA]");
    
    
    
    mButtonCircular = new UButton("CIRC");
    mButtonCircular->StyleSetCheckBox();
    
    mButtonTangentsLockDirection = new UButton("TAN-LOCK");
    mButtonTangentsLockDirection->StyleSetCheckBox();
    
    mButtonAllowDragPoints = new UButton("Drag-P");
    mButtonAllowDragPoints->StyleSetCheckBox();
    
    mButtonAllowDragTangents = new UButton("Drag-T");
    mButtonAllowDragTangents->StyleSetCheckBox();
    
    
    mPathPane->AddLine(mButtonCircular, mButtonTangentsLockDirection, mButtonAllowDragPoints, mButtonAllowDragTangents);
    
    
    
    
    mPointPane = new UMenuPane("Points", true);
    AddLine(mPointPane);
    
    
    mPointShiftButtonL = new UButton("ShiftL");
    mPointShiftButtonR = new UButton("ShiftR");
    mPointShiftButtonU = new UButton("ShiftU");
    mPointShiftButtonD = new UButton("ShiftD");
    
    mPointPane->AddLine(mPointShiftButtonL, mPointShiftButtonR, mPointShiftButtonU, mPointShiftButtonD);
    
    
    mPointSelectButtonInsert = new UButton("INS");
    mPointSelectButtonDelete = new UButton("DEL");
    
    mPointPane->AddLine(mPointSelectButtonInsert, mPointSelectButtonDelete);
    
    mPointSelectButtonNext = new UButton("P->");
    mPointSelectButtonPrev = new UButton("<-P");
    mPointSelectButtonClear = new UButton("[  ]");
    
    mPointPane->AddLine(mPointSelectButtonNext, mPointSelectButtonPrev, mPointSelectButtonClear);
    mPointPane->Collapse();
    
    
    
    mPaneLook = new UMenuPane("Background Underlay", true);
    AddMenuItems(mPaneLook);
    
    mButtonDrawPoints = new UButton("Pnt");
    mButtonDrawPoints->StyleSetCheckBox();
    
    mButtonDrawLines = new UButton("Lin");
    mButtonDrawLines->StyleSetCheckBox();
    
    mButtonDrawReference = new UButton("Ref");
    mButtonDrawReference->StyleSetCheckBox();
    
    mPaneLook->AddLine(mButtonDrawPoints, mButtonDrawLines, mButtonDrawReference);
    
    
    mColorPickerBackground = new UColorPicker();
    mColorPickerBackground->SetText("Canvas Color");
    mPaneLook->AddLine(mColorPickerBackground);
    
    
    mSliderOpacity = new UExtendedSlider("Opac", 0.0f, 1.0f);
    mPaneLook->AddLine(mSliderOpacity);
    
    
    mPaneLook->Collapse();
    
}

UPathMakerMenu::~UPathMakerMenu()
{
    
}

void UPathMakerMenu::SetPathMaker(UPathMaker *pPathMaker)
{
    mPathMaker = pPathMaker;
    
    if(mSymmetryPane)mSymmetryPane->SetPathMaker(pPathMaker);
    
    mPathSegmentMode->SetTarget(&(mPathMaker->mMode));
    mPathButtonCreateNew->SetTargetCheck(&(mPathMaker->mCreateNewPath));
    
    //WHWHWHHWHWH
    //mPathButtonLockSelection->SetTargetCheck(&(mPathMaker->mDrawPoints));
    
    mButtonAllowDragPoints->SetTargetCheck(&(mPathMaker->mAllowDragPoint));
    mButtonAllowDragTangents->SetTargetCheck(&(mPathMaker->mAllowDragTan));
    
    mButtonTangentsLockDirection->SetTargetCheck(&(mPathMaker->mTanLockDir));
    //mButtonCircular->SetTargetCheck(&(mPathMaker->mDrawEdgesClosed));
    
    
    mSliderOpacity->SetTarget(&(mPathMaker->mOpacity));
    mColorPickerBackground->SetColor(&(mPathMaker->mBackgroundColor));
    
    mButtonDrawPoints->SetTargetCheck(&(mPathMaker->mDrawPoints));
    mButtonDrawLines->SetTargetCheck(&(mPathMaker->mDrawEdges));
    //mButtonDrawTangents->SetTargetCheck(&(mPathMaker->mDrawTangents));
    mButtonDrawReference->SetTargetCheck(&(mPathMaker->mDrawReference));
    
    
    Refresh();
}

void UPathMakerMenu::Refresh()
{
    FMotionPathTemplate *aSelectedPath = 0;
    FMotionPathTemplate *aSelectedLockPath = 0;
    
    if(mPathMaker)
    {
        aSelectedPath = mPathMaker->mSelectedPath;
        aSelectedLockPath = mPathMaker->mSelectedPathLockTarget;
    }
    
    
    mPathButtonCreateNew->SetTargetCheck(&(mPathMaker->mCreateNewPath));
    
    mPathSegmentMode->SetTarget(&(mPathMaker->mMode));
    
    if(aSelectedPath)
    {
        mButtonCircular->SetTargetCheck(&(aSelectedPath->mCircular));
    }
    else
    {
        mButtonCircular->SetTargetCheck(0);
    }
    
    if(aSelectedLockPath)
    {
        mPathSelectButtonLock->mChecked = true;
    }
    else
    {
        mPathSelectButtonLock->mChecked = false;
    }
    
    //mPathSelectButtonLock = new UButton("LCK");
    //mPathSelectButtonLock->StyleSetCheckBox();
    
    
    
    
    
    
}

void UPathMakerMenu::Notify(void *pSender)
{
    
    if(pSender == mPathButtonCreateNew)
    {
        //mPathMaker->mCreateNewPath = !(mPathMaker->mCreateNewPath);
        //mPathMaker->mSelectedPath = 0;
        
        if(mPathMaker->mCreateNewPath)
        {
            mPathMaker->mMode = GKMTV_MODE_CREATE_POINTS;
        }
    }
    else
    {
        mPathMaker->mCreateNewPath = false;
    }
    
    
    if(pSender == mPathSegmentMode)mPathMaker->SetMode(mPathSegmentMode->mSelectedIndex);
    
    if(pSender == mPathButtonPrint)mPathMaker->Print();
    
    if(pSender == mPathSelectButtonLock)mPathMaker->PathSelectionDragLockToggle();
    
    if(pSender == mPathSelectButtonNext)mPathMaker->PathSelectionPrev();
    if(pSender == mPathSelectButtonPrev)mPathMaker->PathSelectionNext();
    
    if(pSender == mPathButtonDelete)mPathMaker->PathDeleteSelected();
    if(pSender == mPathButtonDeleteAll)mPathMaker->PathDeleteAll();
    
    
    if(pSender == mPointShiftButtonL)mPathMaker->PointSelectionShift(-1.0f,  0.0f);
    if(pSender == mPointShiftButtonR)mPathMaker->PointSelectionShift( 1.0f,  0.0f);
    if(pSender == mPointShiftButtonU)mPathMaker->PointSelectionShift( 0.0f, -1.0f);
    if(pSender == mPointShiftButtonD)mPathMaker->PointSelectionShift( 0.0f,  1.0f);
    
    
    if(pSender == mPointSelectButtonDelete)mPathMaker->PointSelectionDelete();
    if(pSender == mPointSelectButtonInsert)mPathMaker->PointSelectionInsert();
    if(pSender == mPointSelectButtonNext)mPathMaker->PointSelectionNext();
    if(pSender == mPointSelectButtonPrev)mPathMaker->PointSelectionPrev();
    if(pSender == mPointSelectButtonClear)mPathMaker->PointSelectionClear();

    if(pSender == mPathButtonTriangleDeleteLast)mPathMaker->PointSelectionTrianglesDeleteLast();
    if(pSender == mPathButtonTriangleDeleteAll)mPathMaker->PointSelectionTrianglesDeleteAll();
    
    Refresh();
}

void UPathMakerMenu::CloseMenu()
{
    gUtils->KillOverlay();
}


UPathMakerSymmetryPane::UPathMakerSymmetryPane()
{
    
}

UPathMakerSymmetryPane::~UPathMakerSymmetryPane()
{
    
}

void UPathMakerSymmetryPane::SetPathMaker(UPathMaker *pPathMaker)
{
    mPathMaker = pPathMaker;
    
}


void UPathMakerSymmetryPane::Notify(void *pSender)
{
    
    
}



