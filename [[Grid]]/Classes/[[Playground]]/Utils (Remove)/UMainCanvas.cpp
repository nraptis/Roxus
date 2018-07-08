//
//  UMainCanvas.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UPathMaker.h"
#include "UMainCanvasOverlays.h"
#include "UMainCanvas.h"
#include "core_includes.h"
#include "core_app_shell.h"
#include "FList.h"
#include "UParentPane.h"
#include "UCanvasPane.h"
#include "UTransformMenu.h"
#include "UImagePicker.h"
#include "FApp.h"

UMainCanvas *gUtils = 0;
UNode *gUtilsNode = 0;

bool gUtilsHideAllMarkers = false;
bool gUtilsHideExtendedMarkers = false;

UMainCanvas::UMainCanvas()
{
    gUtils = this;
    gUtilsNode = 0;
    
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    SetStaticTransform(true);
    mConsumesTouches = false;
    
    
    gUtilWS = new UMainWorkspace();
    gUtilWS->mDrawManual = true;
    gUtilWS->mRecievesOutsideTouches = true;
    gUtilWS->SetMode(UTIL_WS_MODE_SELECT_AND_DRAG);
    AddSubview(gUtilWS);
    
    mLoadFrame = 0;
    mLoadFrameX = 0.0f;
    mLoadFrameY = 0.0f;
    mLoadFrameWidth = 0.0f;
    mLoadFrameHeight = 0.0f;
    
    mPanning = false;
    mPanDragData = 0;
    mPanWindowStartX = 0.0f;
    mPanWindowStartY = 0.0f;
    mPanTouchStartX = 0.0f;
    mPanTouchStartY = 0.0f;
    
    mBackgroundLetterBox = true;
    mBackgroundLetterBoxOver = false;
    
    mPathEditScale = 2.0f;
    
    
    mImagePickType = 0;
    mImagePickerUpdatesCurrentNode = false;
    
    
    
    mScreenResizeCornerX[0] = gVirtualDevX;
    mScreenResizeCornerY[0] = gVirtualDevY;
    mScreenResizeCornerX[1] = gVirtualDevX;
    mScreenResizeCornerY[1] = gVirtualDevY + gVirtualDevHeight;
    mScreenResizeCornerX[2] = gVirtualDevX + gVirtualDevWidth;
    mScreenResizeCornerY[2] = gVirtualDevY;
    mScreenResizeCornerX[3] = gVirtualDevX + gVirtualDevWidth;
    mScreenResizeCornerY[3] = gVirtualDevY + gVirtualDevHeight;
    
    
    mMenuStylePaneR[0] = 0.15f;mMenuStylePaneG[0] = 0.14f;mMenuStylePaneB[0] = 0.25f;mMenuStylePaneA[0] = 1.0f;
    mMenuStylePaneR[1] = 0.12f;mMenuStylePaneG[1] = 0.19f;mMenuStylePaneB[1] = 0.15f;mMenuStylePaneA[1] = 1.0f;
    
    mMenuStylePaneOddR[0] = 0.36f;mMenuStylePaneOddG[0] = 0.42f;mMenuStylePaneOddB[0] = 0.39f;mMenuStylePaneOddA[0] = 1.0f;
    mMenuStylePaneOddR[1] = 0.32f;mMenuStylePaneOddG[1] = 0.35f;mMenuStylePaneOddB[1] = 0.34f;mMenuStylePaneOddA[1] = 1.0f;
    
    mMenuStylePaneBorderR[0] = 0.86f;mMenuStylePaneBorderG[0] = 0.79f;mMenuStylePaneBorderB[0] = 0.82f;mMenuStylePaneBorderA[0] = 1.0f;
    mMenuStylePaneBorderR[1] = 0.82f;mMenuStylePaneBorderG[1] = 0.72f;mMenuStylePaneBorderB[1] = 0.76f;mMenuStylePaneBorderA[1] = 1.0f;
    
    
    mMenuStyleBarR[0][0] = 0.10f;mMenuStyleBarG[0][0] = 0.10f;mMenuStyleBarB[0][0] = 0.17f;mMenuStyleBarA[0][0] = 1.0f;
    mMenuStyleBarR[1][0] = 0.07f;mMenuStyleBarG[1][0] = 0.12f;mMenuStyleBarB[1][0] = 0.13f;mMenuStyleBarA[1][0] = 1.0f;
    mMenuStyleBarR[2][0] = 0.13f;mMenuStyleBarG[2][0] = 0.14f;mMenuStyleBarB[2][0] = 0.26f;mMenuStyleBarA[2][0] = 1.0f;
    mMenuStyleBarR[3][0] = 0.07f;mMenuStyleBarG[3][0] = 0.10f;mMenuStyleBarB[3][0] = 0.22f;mMenuStyleBarA[3][0] = 1.0f;
    
    for(int i=0;i<4;i++)
    {
        mMenuStyleBarR[i][1] = mMenuStyleBarB[i][0] * 0.88f;
        mMenuStyleBarG[i][1] = mMenuStyleBarG[i][0] * 0.88f;
        mMenuStyleBarB[i][1] = mMenuStyleBarR[i][0] * 0.88f;
        mMenuStyleBarA[i][1] = 1.0f;
    }
    
    mMenuStyleBarShineR[0] = 1.0f;mMenuStyleBarShineG[0] = 1.0f;mMenuStyleBarShineB[0] = 1.0f;mMenuStyleBarShineA[0] = 0.30f;
    mMenuStyleBarShineR[1] = 1.0f;mMenuStyleBarShineG[1] = 1.0f;mMenuStyleBarShineB[1] = 1.0f;mMenuStyleBarShineA[1] = 0.0f;
    
    
    mImagePickerUpdatesBackground = false;
    
    
    mName = "UMainCanvas";
    
    mNodeMenu = 0;
    mTimelineMenu = 0;
    mParticleMenu = 0;
    
    mMotionMenu = 0;
    mParentPane = 0;
    mCanvasPane = 0;
    mTransformMenu = 0;
    
    mOverlayView = 0;
    
    mMarkerDisplayType = 0;
    
    
    mReferenceView = 0;
    
    
    
    mToolbar = new UMainToolbar();
    AddSubview(mToolbar);
    
    mUpdatesAllowed = true;
    mUpdateOnce = false;
    
    
    
    mPathEditScale = 2.0f;
    mPathTransformStart = true;
    
    
    mDrawDisableAll = false;
    
    
    mBackgroundOpacity = 0.6f;
    mBackgroundColor = FColor(0.2f, 0.0f, 0.16f, 0.4f);
    mBackgroundColorEnabled = false;
    mBackgroundImageEnabled = false;
    mBackgroundSprite = 0;
    
    
    
    mGlobalOpacity = 1.0f;
    
    mFirstUpdate = true;
    
    mIsExpanded = true;
    
    mMotionPathDeleteListTimer = 0;
    mNodeSelDeleteListTimer = 0;
    
    
    mTimelineEnabled = true;
    
    mTimelineTick = 0;
    mTimelineTickPrev = -1;
    mTimelineTickMax = 100;
    
    mTimelineFastForward = false;
    mTimelineSlowMotion = false;
    mTimelineSlowMotionTick = 0;
    
    mTimelineLoopStartTick = 0;
    mTimelineLoopEndTick = mTimelineTickMax;
    
    
    //SpawnNodeMenu();
    //SpawnParticleMenu();
    //SpawnParticleMenu2();
    
    //SpawnParentMenu();
    //SpawnCanvasMenu();
    //SpawnTimeline();
    
    //SpawnMotionMenu();
    //SpawnNodePlacementMenu();
    
    
    Collapse();
    Expand();
    
    mToolbar->Collapse();
    mToolbar->Expand();
    
    SetSelectedNode(gUtilsNode);
}

UMainCanvas::~UMainCanvas()
{
    Log("UMainCanvas::~UMainCanvas()\n\n");
    Save();
}

void UMainCanvas::PositionContent()
{
    if(mPanning == false)
    {
        mScreenResizeCornerX[0] = gVirtualDevX;
        mScreenResizeCornerY[0] = gVirtualDevY;
        
        mScreenResizeCornerX[1] = gVirtualDevX;
        mScreenResizeCornerY[1] = gVirtualDevY + gVirtualDevHeight;
        
        mScreenResizeCornerX[2] = gVirtualDevX + gVirtualDevWidth;
        mScreenResizeCornerY[2] = gVirtualDevY;
        
        mScreenResizeCornerX[3] = gVirtualDevX + gVirtualDevWidth;
        mScreenResizeCornerY[3] = gVirtualDevY + gVirtualDevHeight;
    }
}

void UMainCanvas::Update()
{
    if(mFirstUpdate)
    {
        mFirstUpdate = false;
        Load();
        
        SetSelectedNode(gUtilsNode);
    }
    
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    if(mLoadFrame > 0)
    {
        mLoadFrame--;
        if(mLoadFrame <= 0)
        {
            mLoadFrame = 0;
            //AppShellSetVirtualFrame(mLoadFrameX, mLoadFrameY, mLoadFrameWidth, mLoadFrameHeight);
            //PositionContent();
            
            mTimelineEnabled = true;
        }
    }
    
    
    
    if(mMarkerDisplayType == 0)
    {
        gUtilsHideAllMarkers = false;
        gUtilsHideExtendedMarkers = false;
    }
    if(mMarkerDisplayType == 1)
    {
        gUtilsHideAllMarkers = false;
        gUtilsHideExtendedMarkers = true;
    }
    if(mMarkerDisplayType == 2)
    {
        gUtilsHideAllMarkers = true;
        gUtilsHideExtendedMarkers = true;
    }
    
    
    if(gUtilWS)
    {
        gUtilWS->mConsumesTouches = mConsumesTouches;
    }
    if(mOverlayView)
    {
        mOverlayView->mConsumesTouches = mConsumesTouches;
    }
    
    
    mTimelineTickPrev = mTimelineTick;
    if(mTimelineEnabled == true)
    {
        if(mTimelineSlowMotion)
        {
            mTimelineSlowMotionTick++;
            if(mTimelineSlowMotionTick >= 10)
            {
                mTimelineSlowMotionTick = 0;
                mTimelineTick++;
                if(mTimelineTick > mTimelineLoopEndTick)mTimelineTick = mTimelineLoopStartTick;
                TimelineApply();
                
            }
        }
        else if(mTimelineFastForward)
        {
            mTimelineTick += 5;
            if(mTimelineTick > mTimelineLoopEndTick)mTimelineTick = mTimelineLoopStartTick;
            TimelineApply();
        }
        else
        {
            mTimelineTick++;
            if(mTimelineTick > mTimelineLoopEndTick)mTimelineTick = mTimelineLoopStartTick;
            TimelineApply();
        }
        
        
        
        
        
        
        
    }
    
    
    
}

void UMainCanvas::Draw()
{
    
    
    
    if(mNodeSelDeleteList.mCount > 0)
    {
        mNodeSelDeleteListTimer--;
        if(mNodeSelDeleteListTimer <= 0)
        {
            while (mNodeSelDeleteList.mCount > 0)
            {
                UNodeSelection *aSel = (UNodeSelection *)(mNodeSelDeleteList.Last());
                
                delete aSel;
                
                mNodeSelDeleteList.mCount--;
            }
        }
    }
    
    
    if(mMotionPathDeleteList.mCount > 0)
    {
        mMotionPathDeleteListTimer--;
        if(mMotionPathDeleteListTimer <= 0)
        {
            while (mMotionPathDeleteList.mCount > 0)
            {
                FMotionPathTemplate *aPath = (FMotionPathTemplate *)(mMotionPathDeleteList.Last());
                
                delete aPath;
                mMotionPathDeleteList.mCount--;
            }
        }
    }
    
    

    mEdgeLeft = gVirtualDevX;
    mEdgeTop = gVirtualDevY;
    mEdgeRight = gVirtualDevX + gVirtualDevWidth;
    mEdgeBottom = gVirtualDevY + gVirtualDevHeight;
    if(mReferenceView)
    {
        FVec2 aTL = FView::Convert(0.0f, 0.0f, mReferenceView, this);
        FVec2 aBR = FView::Convert(mReferenceView->mWidth, mReferenceView->mHeight, mReferenceView, this);
        mEdgeLeft = aTL.mX;
        mEdgeTop = aTL.mY;
        mEdgeRight = aBR.mX;
        mEdgeBottom = aBR.mY;
    }
    
    
    
    Graphics::BlendSetAlpha();
    
    
    
    if(mIsExpanded)
    {
    if((mBackgroundImageEnabled == true) && (mBackgroundSprite != 0))
    {
        float aX = gDeviceWidth2;
        float aY = gDeviceHeight2;
        
        if(mReferenceView)
        {
            FVec2 aPos = FView::Convert(mReferenceView->mWidth2, mReferenceView->mHeight2, mReferenceView, this);
            
            aX = aPos.mX;
            aY = aPos.mY;
        
        }
        
        Graphics::SetColor(mBackgroundColor.mRed, mBackgroundColor.mGreen, mBackgroundColor.mBlue, mGlobalOpacity * mBackgroundOpacity);
        mBackgroundSprite->Center(aX, aY);
    }
    
    
    if((mBackgroundColorEnabled == true) && (mBackgroundColor.mAlpha > 0.0f))
    {
        Graphics::SetColor(mBackgroundColor.mRed, mBackgroundColor.mGreen, mBackgroundColor.mBlue, mBackgroundColor.mAlpha * mBackgroundOpacity * mGlobalOpacity);
        Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    }
    
    Graphics::SetColor();
    
    if((mBackgroundLetterBox == true) && (mBackgroundLetterBoxOver == false))BackgroundDrawLetterBox();
        
    }
    
    //Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.1f);
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    //Graphics::SetColor();
    
    gUtilWS->DrawManual();
    
    DrawTransform();
    
    Graphics::SetColor();
    if(mPanning)
    {
        for(int i = 0; i < 4; i++)
        {
            float aX = mScreenResizeCornerX[i];
            float aY = mScreenResizeCornerY[i];
            
            Graphics::SetColor();
            Graphics::DrawRect(aX - 4, aY - 4, 12, 12);
            
            Graphics::SetColor(0.4f, 0.4f, 0.4f);
            Graphics::DrawRect(aX - 4, aY - 4, 8, 8);
            
        }
        
        Graphics::SetColor();
    }
    
    
    if((mBackgroundLetterBox == true) && (mBackgroundLetterBoxOver == true))BackgroundDrawLetterBox();
    

    Graphics::SetColor();
}




void UMainCanvas::TouchDown(float pX, float pY, void *pData)
{
    if(mPanning)
    {
        mPanDragData = pData;
        
        mPanTouchStartX = pX;
        mPanTouchStartY = pY;
        
        mPanWindowStartX = gVirtualDevX;
        mPanWindowStartY = gVirtualDevY;
        
        float aMinDist = 45.0f;
        if(gDeviceWidth < 600.0f)aMinDist = 24.0f;
        
        mResizeCornerIndex = -1;
        
        for(int i = 0; i<4; i++)
        {
            
            mScreenResizeCornerDragStartX[i] = mScreenResizeCornerX[i];
            mScreenResizeCornerDragStartY[i] = mScreenResizeCornerY[i];
            
            float aX = mScreenResizeCornerX[i];
            float aY = mScreenResizeCornerY[i];
            
            float aDist = Distance(pX, pY, aX, aY);
            
            if(aDist < aMinDist)
            {
                mResizeCornerIndex = i;
                
                mResizeDragCornerX = aX;
                mResizeDragCornerY = aY;
            }
        }
    }
}

void UMainCanvas::TouchMove(float pX, float pY, void *pData)
{
    if(mPanning)
    {
        if(mPanDragData == pData)
        {
            
            if((mResizeCornerIndex >= 0) && (mResizeCornerIndex < 4))
            {
                float aX = mResizeDragCornerX + (pX - mPanTouchStartX);
                float aY = mResizeDragCornerY + (pY - mPanTouchStartY);
                
                mScreenResizeCornerX[mResizeCornerIndex] = aX;
                mScreenResizeCornerY[mResizeCornerIndex] = aY;
                
                if(mResizeCornerIndex == 0){mScreenResizeCornerX[1] = aX;mScreenResizeCornerY[2] = aY;}
                if(mResizeCornerIndex == 1){mScreenResizeCornerX[0] = aX;mScreenResizeCornerY[3] = aY;}
                if(mResizeCornerIndex == 2){mScreenResizeCornerX[3] = aX;mScreenResizeCornerY[0] = aY;}
                if(mResizeCornerIndex == 3){mScreenResizeCornerX[2] = aX;mScreenResizeCornerY[1] = aY;}
                
                ComputeResizeRect();
                
                AppShellSetVirtualFrame(mResizeLeft, mResizeTop, mResizeWidth, mResizeHeight);
            }
            else
            {
                float aDeltaX = pX - mPanTouchStartX;
                float aDeltaY = pY - mPanTouchStartY;
                
                float aX = mPanWindowStartX + (aDeltaX);
                float aY = mPanWindowStartY + (aDeltaY);
                
                for(int i=0;i<4;i++)
                {
                    mScreenResizeCornerX[i] = (mScreenResizeCornerDragStartX[i] + aDeltaX);
                    mScreenResizeCornerY[i] = (mScreenResizeCornerDragStartY[i] + aDeltaY);
                }
                
                AppShellSetVirtualFrame(aX, aY, gVirtualDevWidth, gVirtualDevHeight);
                
                PositionContent();
            }
        }
    }
}

void UMainCanvas::TouchUp(float pX, float pY, void *pData)
{
    mPanDragData = 0;
}

void UMainCanvas::TouchFlush()
{
    mPanDragData = 0;
}

void UMainCanvas::SetSelectedNode(UNode *pNode)
{
    gUtilsNode = pNode;
    
    gUtilWS->FindHeirarchy();
    
    EnumList(FView, aView, mSubviews)
    {
        aView->Notify(this, UTIL_ACTION_NODE_SELECT, pNode);
    }
    //gUtilWS->SetSelectedNode(pNode);
}

void UMainCanvas::SetSelectedNode()
{
    SetSelectedNode(gUtilsNode);
}

void UMainCanvas::Notify(void *pSender, int pID, void *pObject)
{
    if(pObject != 0)
    {
        if(pID == IMG_PICK_RESPONSE_SPRITE)
        {
            FSprite *aSprite = ((FSprite *)pObject);
            if(aSprite)
            {
                if(mImagePickerUpdatesBackground)
                {
                    mBackgroundSprite = aSprite;
                }
                else
                {
                if(gUtils->mImagePickerUpdatesCurrentNode)
                {
                    if(gUtilsNode)
                    {
                        gUtilsNode->SetSprite(aSprite);
                        gUtils->mImagePickerUpdatesCurrentNode = false;
                    }
                    else
                    {
                        gUtilWS->AddSpriteNode(aSprite);
                    }
                }
                else
                {
                    gUtilWS->AddSpriteNode(aSprite);
                }
                }
            }
            
            
            mImagePickerUpdatesBackground = false;
        }
        else if(pID == IMG_PICK_RESPONSE_SEQUENCE)
        {
            FSpriteSequence *aSequence = ((FSpriteSequence *)pObject);
            
            if(aSequence)
            {
                FSprite *aSprite = aSequence->Get();
                
                if(aSprite)
                {
                    if(gUtils->mImagePickerUpdatesCurrentNode)
                    {
                        if(gUtilsNode)
                        {
                            gUtilsNode->SetSpriteSequence(aSequence);
                            gUtils->mImagePickerUpdatesCurrentNode = false;
                        }
                        else
                        {
                            gUtilWS->AddSequenceNode(aSequence);
                        }
                    }
                    else
                    {
                        gUtilWS->AddSequenceNode(aSequence);
                    }
                }
            }
            
            
            mImagePickerUpdatesBackground = false;
        }
    }
}

void UMainCanvas::Notify(void *pSender)
{
    
}

FVec2 UMainCanvas::MenuGoodPlacement(float pWidth, float pHeight)
{
    FList aPosList;
    
    float aMinX = 8.0f;
    float aMinY = mToolbar->mHeight + 8.0f;
    float aMaxX = mWidth - (pWidth + 16.0f);
    float aMaxY = (mHeight - mToolbar->mHeight);
    
    FVec2 aResult = FVec2(aMinX + gRand.GetFloat(aMaxX - aMinX), aMinY + gRand.GetFloat(aMaxY - aMinY));
    
    for(int n=0;n<20;n++)
    {
        float aPercentN = ((float)n) / (19.0f);
        float aCheckY = aMinY + (aMaxY - aMinY) * aPercentN;
        
        for(int i=0;i<20;i++)
        {
            float aPercentI = ((float)i) / (19.0f);
            float aCheckX = aMinX + (aMaxX - aMinX) * aPercentI;
            aPosList += new FVec2(aCheckX, aCheckY);
        }
    }
    
    FRect aRect;
    FRect aViewRect;
    
    aRect.mWidth = pWidth;
    aRect.mHeight = pHeight;
    
    bool aFound = false;
    
    for(int i=0;((i<4) && (aFound==false));i++)
    {
        EnumList(FVec2, aPos, aPosList)
        {
            if(aFound == false)
            {
                aRect.mX = aPos->mX;
                aRect.mY = aPos->mY;
                bool aCollides = false;
                EnumList(FView, aView, mSubviews)
                {
                    aViewRect.mX = aView->mX;
                    aViewRect.mY = aView->mY;
                    aViewRect.mWidth = aView->mWidth;
                    //aViewRect.mHeight = aView->mHeight;
                    aViewRect.mHeight = 80.0f;
                    
                    if(aViewRect.Intersects(aRect) == true)
                    {
                        aCollides = true;
                        break;
                    }
                }
                
                if((aCollides == false) && (aFound == false))
                {
                    aResult.mX = aPos->mX;
                    aResult.mY = aPos->mY;
                    
                    aFound = true;
                    
                    break;
                }
                
            }
        }
        
        pHeight *= 2;
        pHeight /= 3;
    }
    
    FreeList(FVec2, aPosList);
    return aResult;
}

void UMainCanvas::MenuAdd(UMenu *pMenu)
{
    if(pMenu)
    {
        mMenuList += pMenu;
        
        pMenu->SetMenuItemFrame(100.0f, 160.0f, pMenu->mWidth, pMenu->mHeight);
        pMenu->LayoutSubviews();
        
        FVec2 aBestPlace = gUtils->MenuGoodPlacement(pMenu->mWidth, pMenu->mHeight);
        pMenu->SetMenuItemFrame(aBestPlace.mX, aBestPlace.mY, pMenu->mWidth, pMenu->mHeight);
        
        if(mSubviews.Exists(pMenu) == false)AddSubview(pMenu);
        
        SetSelectedNode(gUtilsNode);
    }
}

void UMainCanvas::MenuSelect(FView *pSelectedMenu)
{
    if(pSelectedMenu)
    {
        if(mSubviews.Exists(pSelectedMenu))
        {
            SetSelectedNode();
            if(pSelectedMenu->mParent)
            {
                pSelectedMenu->mParent->BringSubviewToFront(pSelectedMenu);
            }
        }
    }
}

void UMainCanvas::MenuDetatch(UMenu *pMenu, UMenuPane *pMenuPane)
{
    
}

void UMainCanvas::MenuKill(FView *pMenu)
{
    mMenuList -= pMenu;
    if(pMenu == mParticleMenu)mParticleMenu = 0;
    if(pMenu == mTimelineMenu)mTimelineMenu = 0;
    if(pMenu == mNodeMenu)mNodeMenu = 0;
    if(pMenu == mMotionMenu)mMotionMenu = 0;
    if(pMenu == mParentPane)mParentPane = 0;
    if(pMenu == mCanvasPane)mCanvasPane = 0;
    
    if(pMenu)
    {
        pMenu->Kill();
    }
    
}

void UMainCanvas::AddOverlay(FView *pView)
{
    if(mOverlayView)KillOverlay();
    
    if(pView)
    {
        mOverlayView = pView;
        EnumList(FView, aView, mSubviews)
        {
            if((aView != mToolbar) && (aView != mOverlayView))
            {
                aView->mHidden = true;
                aView->mEnabled = false;
            }
        }
        
        if(mController)
        {
            mController->ViewAdd(mOverlayView);
        }
        //gViewController.ViewAdd(mOverlayView);
    }
}

void UMainCanvas::KillOverlay()
{
    EnumList(FView, aView, mSubviews)
    {
        if((aView != mToolbar) && (aView != mOverlayView))
        {
            aView->mHidden = false;
            aView->mEnabled = true;
        }
    }
    
    if(mOverlayView)
    {
        mOverlayView->Kill();
        mOverlayView = 0;
    }
    
    gUtilWS->mDrawNodes = true;
    
}



void UMainCanvas::Export()
{
    ExportSelected();
}

void UMainCanvas::ExportSelected()
{
    if(gUtilsNode)
    {
        gUtilWS->Export();
    }
}

void UMainCanvas::Save()
{
    SaveLayout();
    
    FFile aFile;
    
    aFile.WriteFloat(gVirtualDevX);
    aFile.WriteFloat(gVirtualDevY);
    aFile.WriteFloat(gVirtualDevWidth);
    aFile.WriteFloat(gVirtualDevHeight);
    
    
    aFile.WriteBool(mTimelineEnabled);
    aFile.WriteBool(mTimelineFastForward);
    aFile.WriteBool(mTimelineSlowMotion);
    
    aFile.WriteInt(mTimelineTick);
    aFile.WriteInt(mTimelineTickMax);
    aFile.WriteInt(mTimelineSlowMotionTick);
    aFile.WriteInt(mTimelineLoopStartTick);
    aFile.WriteInt(mTimelineLoopEndTick);
    
    FString aBackSpritePath = "";
    if(mBackgroundSprite)
    {
        aBackSpritePath = mBackgroundSprite->mFileName;
    }
    aFile.WriteString(aBackSpritePath);
    
    aFile.WriteFloat(mGlobalOpacity);
    aFile.WriteFloat(mBackgroundOpacity);
    
    aFile.WriteColor(mBackgroundColor);
    
    aFile.WriteBool(mBackgroundColorEnabled);
    aFile.WriteBool(mBackgroundImageEnabled);
    aFile.WriteBool(mBackgroundLetterBox);
    aFile.WriteBool(mBackgroundLetterBoxOver);
    
    gUtilWS->Save(&aFile);
    
    aFile.Save(gDirDocuments + FString("configgy.dat"));
}

void UMainCanvas::Load()
{
    LoadLayout();
    
    if(gUtilWS->mListAdd.mCount > 0)
    {
        return;
    }
    
    FFile aFile;
    aFile.Load(gDirDocuments + FString("configgy.dat"));
    
    
    mLoadFrame = 4;
    if(aFile.mLength <= 4)
    {
        mLoadFrame = 0;
        return;
    }
    
    mLoadFrameX = aFile.ReadFloat();
    mLoadFrameY = aFile.ReadFloat();
    mLoadFrameWidth = aFile.ReadFloat();
    mLoadFrameHeight = aFile.ReadFloat();
    
    mTimelineEnabled = aFile.ReadBool();
    mTimelineFastForward = aFile.ReadBool();
    mTimelineSlowMotion = aFile.ReadBool();
    
    mTimelineTick = aFile.ReadInt();
    mTimelineTickMax = aFile.ReadInt();
    mTimelineSlowMotionTick = aFile.ReadInt();
    mTimelineLoopStartTick = aFile.ReadInt();
    mTimelineLoopEndTick = aFile.ReadInt();
    
    
    
    FString aBackSpritePath = aFile.ReadString();
    mBackgroundSprite = 0;
    if(aBackSpritePath.mLength > 0)
    {
        EnumList(FSprite, aSprite, gSpriteList)
        {
            if(aSprite->mFileName == aBackSpritePath)
            {
                mBackgroundSprite = aSprite;
            }
        }
    }
        
    
    mGlobalOpacity = aFile.ReadFloat();
    mBackgroundOpacity = aFile.ReadFloat();
    
    
    mBackgroundColor = aFile.ReadColor();
    
    mBackgroundColorEnabled = aFile.ReadBool();
    mBackgroundImageEnabled = aFile.ReadBool();
    mBackgroundLetterBox = aFile.ReadBool();
    mBackgroundLetterBoxOver = aFile.ReadBool();
    
    

    
    gUtilWS->Load(&aFile); 
}

void UMainCanvas::DeleteSaved()
{
    gUtilWS->Clear();
    FFile aFile;
    aFile.WriteInt(0);
    aFile.Save(gDirDocuments + FString("configgy.dat"));
}

void UMainCanvas::SaveLayout()
{
    FXML aLayoutXML;
    FXMLTag *aLayoutTag = new FXMLTag("layout_info");
    aLayoutXML.mRoot = aLayoutTag;
    
    FXMLTag *aMenuListTag = new FXMLTag("menu_list");
    *aLayoutTag += aMenuListTag;
    
    EnumList(UMenu, aMenu, mMenuList)
    {
        FString aMenuID = "Unknown";
        FXMLTag *aMenuTag = new FXMLTag("menu_info");
        
        *aMenuListTag += aMenuTag;
        
        if(aMenu == mNodeMenu)aMenuID = "node_main";
        if(aMenu == mTimelineMenu)aMenuID = "timeline";
        if(aMenu == mParticleMenu)aMenuID = "particles";
        if(aMenu == mMotionMenu)aMenuID = "motion";
        if(aMenu == mParentPane)aMenuID = "parent";
        if(aMenu == mCanvasPane)aMenuID = "canvas";
        if(aMenu == mTransformMenu)aMenuID = "xform";
        
        aMenuTag->AddParam("id", aMenuID.c());
        aMenuTag->AddParamFloat("x", aMenu->mX);
        aMenuTag->AddParamFloat("y", aMenu->mY);
        aMenuTag->AddParamFloat("width", aMenu->mWidth);
        aMenuTag->AddParamFloat("height", aMenu->mHeight);
        aMenuTag->AddParamBool("expanded", aMenu->mExpanded);
        
    }
    
    if(gDeviceWidth >= 1580)aLayoutXML.Save(gDirDocuments + FString("layout_huge.xml"));
    else if(gDeviceWidth >= 800)aLayoutXML.Save(gDirDocuments + FString("layout_medium.xml"));
    else aLayoutXML.Save(gDirDocuments + FString("layout_small.xml"));
    
}



void UMainCanvas::LoadLayout()
{
    FXML aLayoutXML;
    if(gDeviceWidth >= 1580)aLayoutXML.Load(gDirDocuments + FString("layout_huge.xml"));
    else if(gDeviceWidth >= 800)aLayoutXML.Load(gDirDocuments + FString("layout_medium.xml"));
    else aLayoutXML.Load(gDirDocuments + FString("layout_small.xml"));
    
    if(aLayoutXML.mRoot)
    {
        EnumTagsMatching(aLayoutXML.mRoot, aMenuListTag, "menu_list")
        {
            EnumTagsMatching(aMenuListTag, aMenuTag, "menu_info")
            {
                FString aMenuID = aMenuTag->GetParamValue("id");
                
                float aX = aMenuTag->GetParamFloat("x", 0.0f);
                float aY = aMenuTag->GetParamFloat("y", 0.0f);
                float aWidth = aMenuTag->GetParamFloat("width", 0.0f);
                float aHeight = aMenuTag->GetParamFloat("height", 0.0f);
                bool aExpanded = aMenuTag->GetParamBool("expanded", true);
                
                if((aWidth > 10.0f) && (aWidth < 2000.0f) && (aHeight > 10.0f) && (aHeight < 2000.0f))
                {
                    UMenu *aMenu = 0;
                    
                    if(aMenuID == "node_main"){SpawnNodeMenu();aMenu = mNodeMenu;}
                    if(aMenuID == "timeline"){SpawnTimelineMenu();aMenu = mTimelineMenu;}
                    if(aMenuID == "particles"){SpawnParticleMenu();aMenu = mParticleMenu;}
                    if(aMenuID == "motion"){SpawnMotionMenu();aMenu = mMotionMenu;}
                    if(aMenuID == "parent"){SpawnParentMenu();aMenu = mParentPane;}
                    if(aMenuID == "canvas"){SpawnCanvasMenu();aMenu = mCanvasPane;}
                    if(aMenuID == "xform"){SpawnTransformMenu();aMenu = mTransformMenu;}
                    
                    if(aMenu)
                    {
                        aMenu->SetMenuItemFrame(aX, aY, aWidth, aHeight);
                        aMenu->LayoutSubviews();
                        if(aExpanded)
                        {
                            aMenu->Expand();
                        }
                        else
                        {
                            aMenu->Collapse();
                        }
                        aMenu->LayoutSubviews();
                    }
                }
            }
        }
        
    }
}


void UMainCanvas::PathCreate(int pPathType)
{
    mPathEditScale = 1.4f;
    //mPathTransformStart
    
    if(mReferenceView)mPathEditScale = mReferenceView->GetAbsoluteTransformScale();
    
    
    mPathEditScale = 1.0f;
    
    
    UPathMaker *aPathMaker = new UPathMaker();
    aPathMaker->SetUp(gUtilsNode, pPathType);
    gUtilWS->mDrawNodes = false;
    AddOverlay(aPathMaker);
}

//void UMainCanvas::PathSelect(UPathMakerMenu *pPathMaker, FMotionPathTemplate *pPath, int pPathType)
//void UMainCanvas::PathSelect(FMotionPathTemplate *pPathAbsolute, FMotionPathTemplate *pPath, int pPathType)
//void UMainCanvas::PathSelect(FList *pPathListAbsolute, FList *pPathList, int pPathType)

void UMainCanvas::PathSelect(FList *pPathList, int pPathType)
{
    if(gUtilsNode == 0)
    {
        gUtilWS->AddNode();
        
        if(gUtilsNode)
        {
            if(pPathType == UTIL_PATH_TYPE_POINT_CLOUD)gUtilsNode->mTemplate.SetSpawnSource(SPAWN_SOURCE_POINT_CLOUD);
            if(pPathType == UTIL_PATH_TYPE_POLY)gUtilsNode->mTemplate.SetSpawnSource(SPAWN_SOURCE_POLYGON);
        }
    }
    
    if(pPathList != 0)
    {
        if(pPathType == UTIL_PATH_TYPE_POINT_CLOUD)
        {
            if(gUtilsNode)
            {
                gUtilsNode->mTemplate.SetSpawnSource(SPAWN_SOURCE_POINT_CLOUD);
                gUtilsNode->SetPointsPointCloud(pPathList);
            }
        }
        
        else if(pPathType == UTIL_PATH_TYPE_POLY)
        {
            
            if(gUtilsNode)
            {
                gUtilsNode->mTemplate.SetSpawnSource(SPAWN_SOURCE_POLYGON);
                gUtilsNode->SetPointsPoly(pPathList);
            }
        }
        else
        {
            EnumList(FMotionPathTemplate, aPath, *pPathList)
            {
                gUtilsNode->mMotionPath.Clone(aPath);
                gUtilsNode->mMotionPath.GetPathAbs()->Clone(aPath->GetPathAbs());
                
                delete aPath->mPathAbs;
                aPath->mPathAbs = 0;
                
                delete aPath;
            }
            
        }
        SetSelectedNode(gUtilsNode);
    }
}

void UMainCanvas::SpawnNodeMenu()
{
    if(mNodeMenu == 0)
    {
        mNodeMenu = new UNodeEditorMenu();
        MenuAdd(mNodeMenu);
    }
    else BringSubviewToFront(mNodeMenu);
}


void UMainCanvas::SpawnCanvasMenu()
{
    if(mCanvasPane == 0)
    {
        mCanvasPane = new UCanvasPane();
        MenuAdd(mCanvasPane);
    }
    else BringSubviewForward(mCanvasPane);
}

void UMainCanvas::SpawnParentMenu()
{
    if(mParentPane == 0)
    {
        mParentPane = new UParentPane();
        MenuAdd(mParentPane);
    }
    else BringSubviewForward(mParentPane);
}

void UMainCanvas::SpawnTimelineMenu()
{
    if(mTimelineMenu == 0)
    {
        mTimelineMenu = new UTimelineEditorMenu();
        MenuAdd(mTimelineMenu);
    }
    else BringSubviewToFront(mTimelineMenu);
}

void UMainCanvas::SpawnTransformMenu()
{
    if(mTransformMenu == 0)
    {
        mTransformMenu = new UTransformMenu();
        MenuAdd(mTransformMenu);
    }
    else BringSubviewToFront(mTransformMenu);
}

void UMainCanvas::SpawnParticleMenu()
{
    if(mParticleMenu == 0)
    {
        mParticleMenu = new UParticleEditorMenu1();
        MenuAdd(mParticleMenu);
    }
    else BringSubviewToFront(mParticleMenu);
}


void UMainCanvas::SpawnTimeline()
{
    if(mTimelineMenu == 0)
    {
        mTimelineMenu = new UTimelineEditorMenu();
        MenuAdd(mTimelineMenu);
    }
    else BringSubviewToFront(mTimelineMenu);
}

void UMainCanvas::SpawnMotionMenu()
{
    if(mMotionMenu == 0)
    {
        mMotionMenu = new UNodeMotionPanel();
        MenuAdd(mMotionMenu);
    }
    else BringSubviewToFront(mMotionMenu);
}


void UMainCanvas::DeleteNodeSelection(UNodeSelection *pSel)
{
    if(pSel)
    {
        if(mNodeSelDeleteList.Exists(pSel) == false)mNodeSelDeleteList.Add(pSel);
        mNodeSelDeleteListTimer = 4;
    }
}

void UMainCanvas::DeleteMotionPath(FMotionPathTemplate *pPath)
{
    if(pPath)
    {
        if(mMotionPathDeleteList.Exists(pPath) == false)mMotionPathDeleteList.Add(pPath);
        if(pPath->mPathAbs)
        {
            FMotionPathTemplate *aAbsPath = pPath->mPathAbs;
            pPath->mPathAbs = 0;
            DeleteMotionPath(aAbsPath);
        }
        
        mMotionPathDeleteListTimer = 4;
    }
    
}








void UMainCanvas::Expand()
{
    if(mIsExpanded == false)
    {
        mConsumesTouches = true;
        mToolbar->Expand();
        EnumList(FView, aView, mSubviews)
        {
            if(aView != mToolbar)
            {
                aView->mHidden = false;
                aView->mEnabled = true;
            }
        }
        mIsExpanded = true;
    }
}


void UMainCanvas::Collapse()
{
    if(mIsExpanded)
    {
        mConsumesTouches = false;
        mToolbar->Collapse();
        EnumList(FView, aView, mSubviews)
        {
            if(aView != mToolbar)
            {
                aView->mHidden = true;
                aView->mEnabled = false;
            }
        }
        mIsExpanded = false;
    }
}













void UMainCanvas::MouseWheel(int pDirection)
{
    //Log("CvMW(%d)", pDirection);
    
    if(mOverlayView != 0)return;
    
    bool aShift = (gKeyPressed[DIK_LSHIFT]);
    bool aCtrl = (gKeyPressed[DIK_LCONTROL]);
    
    
    
    
    
    
}

void UMainCanvas::KeyDown(int pKey)
{
    //Log("CvKD(%d)", pKey);
    
    if(mOverlayView != 0)return;
    
    
    
    
}

void UMainCanvas::KeyUp(int pKey)
{
    //Log("CvKU(%d)", pKey);
    
}



void UMainCanvas::PanStart()
{
    mPanning = true;
    mPanDragData = 0;
    WorkspaceDisable();
}

void UMainCanvas::PanEnd()
{
    mPanning = false;
    mPanDragData = 0;
    WorkspaceEnable();
}

void UMainCanvas::ComputeResizeRect()
{
    
    for(int i = 0; i<4; i++)
    {
        if(mScreenResizeCornerX[i] < 0.0f)mScreenResizeCornerX[i] = 0.0f;
        if(mScreenResizeCornerX[i] > gDeviceWidth)mScreenResizeCornerX[i] = gDeviceWidth;
        
        if(mScreenResizeCornerY[i] < 0.0f)mScreenResizeCornerY[i] = 0.0f;
        if(mScreenResizeCornerY[i] > gDeviceHeight)mScreenResizeCornerY[i] = gDeviceHeight;
    }
    
    mResizeLeft = mScreenResizeCornerX[0];
    mResizeTop = mScreenResizeCornerY[0];
    
    mResizeRight = mScreenResizeCornerX[3];
    mResizeBottom = mScreenResizeCornerY[3];
    
    for(int i = 0; i<4; i++)
    {
        int aX = mScreenResizeCornerX[i];
        int aY = mScreenResizeCornerY[i];
        
        if(aX < mResizeLeft)mResizeLeft = aX;
        if(aX > mResizeRight)mResizeRight = aX;
        
        if(aY < mResizeTop)mResizeTop = aY;
        if(aY > mResizeBottom)mResizeBottom = aY;
    }
    
    mResizeWidth = mResizeRight - mResizeLeft;
    mResizeHeight = mResizeBottom - mResizeTop;
    
    //BaseDeviceSizeChanged(mResizeLeft, mResizeTop, mResizeWidth, mResizeHeight);
    
    
}


void UMainCanvas::TimelineReset()
{
    mTimelineTick = mTimelineLoopStartTick;
    TimelineSet(mTimelineTick);
    TimelineApply();
}

void UMainCanvas::TimelineApply()
{
    gUtilWS->SetTime(mTimelineTick);
}

void UMainCanvas::TimelineSetMax(int pMax)
{
    mTimelineTickMax = pMax;
    mTimelineLoopEndTick = pMax;
    TimelineReset();
    TimelineSet(mTimelineTick);
    TimelineApply();
}

void UMainCanvas::TimelineSet(int pPos)
{
    mTimelineTick = pPos;
    if(mTimelineTick < 0)mTimelineTick = 0;
    if(mTimelineTick > mTimelineTickMax)mTimelineTick = mTimelineTickMax;
    TimelineApply();
    
    if(mTimelineMenu)mTimelineMenu->RefreshThumb();
}


void UMainCanvas::TimelineNextFrame()
{
    mTimelineEnabled = false;
    
    mTimelineTick++;
    if(mTimelineTick > mTimelineTickMax)mTimelineTick = 0;
    
    TimelineSet(mTimelineTick);
    TimelineApply();
    
}

void UMainCanvas::TimelinePrevFrame()
{
    mTimelineEnabled = false;
    mTimelineTick--;
    if(mTimelineTick < 0)mTimelineTick = mTimelineTickMax;
    
    TimelineSet(mTimelineTick);
    TimelineApply();
}


void UMainCanvas::WorkspaceDisable()
{
    gUtilWS->mEnabled = false;
    
}

void UMainCanvas::WorkspaceEnable()
{
    gUtilWS->mEnabled = true;
}


bool UMainCanvas::WorkspaceHasFocus()
{
    bool aResult = true;
    
    if(mOverlayView != 0)aResult = false;
    //if(mIsExpanded == false)aResult = false;
    
    return aResult;
}


void UMainCanvas::BlockSprite(const char *pSprite)
{
    
    FString aString = pSprite;
    
    if(aString.mLength > 0)
    {
        EnumList(FString, aCheck, mBlockedSpriteList)
        {
            if(aString == FString(aCheck->c()))
            {
                return;
            }
        }
        
        mBlockedSpriteList += new FString(pSprite);
        
    }
}

void UMainCanvas::SetReferenceView(FView *pView)
{
    mReferenceView = pView;
    if(mReferenceView != 0)
    {
        FViewTransform *aTransform = &(mReferenceView->GetContainer()->mTransformAbsolute);
        //mReferenceViewQuad.Corner1SetPos(aTransform->mCornerX[0], aTransform->mCornerY[0]);
        //mReferenceViewQuad.Corner2SetPos(aTransform->mCornerX[1], aTransform->mCornerY[1]);
        //mReferenceViewQuad.Corner3SetPos(aTransform->mCornerX[2], aTransform->mCornerY[2]);
        //mReferenceViewQuad.Corner4SetPos(aTransform->mCornerX[3], aTransform->mCornerY[3]);
        
        gUtilWS->SetTransformScale(aTransform->mScale);
        gUtilWS->SetTransformX(gVirtualDevX + pView->mX);
        gUtilWS->SetTransformY(gVirtualDevY + pView->mY);
        
        gUtilWS->mWallLeft = 0.0f;
        gUtilWS->mWallRight = (pView->mWidth);
        gUtilWS->mWallTop = 0.0f;
        gUtilWS->mWallBottom = (pView->mHeight);
    }
}


void UMainCanvas::BackgroundDrawLetterBox()
{
    if(mBackgroundLetterBoxOver == false)Graphics::SetColor(0.04f, 0.02f, 0.10f, 0.5f);
    else Graphics::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
    Graphics::DrawRect(mEdgeRight, 0.0f, (mWidth - mEdgeRight), mHeight);
    Graphics::DrawRect(0.0f, 0.0f, mEdgeLeft, mHeight);
    Graphics::DrawRect(mEdgeLeft, 0.0f, (mEdgeRight - mEdgeLeft), mEdgeTop);
    Graphics::DrawRect(mEdgeLeft, mEdgeBottom, (mEdgeRight - mEdgeLeft), (mHeight - mEdgeBottom));
    Graphics::SetColor(0.1f, 0.1f, 0.1f, 0.25f);
    Graphics::OutlineRect(mEdgeLeft, mEdgeTop, mEdgeRight - mEdgeLeft, mEdgeBottom - mEdgeTop, 4.0f);
    Graphics::SetColor();
}

void UMainCanvas::BackgroundSpritePick()
{
    UImagePicker *aPicker = new UImagePicker(this);
    aPicker->FillWithImages();
    aPicker->mListener = this;
    mImagePickType = 1;
    AddSubview(aPicker);
    mImagePickerUpdatesCurrentNode = false;
    mImagePickerUpdatesBackground = true;
}

