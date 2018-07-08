//
//  UTimelineEditorMenu.cpp
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/22/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UTimelineEditorMenu.h"
#include "UMainCanvas.h"
#include "FApp.h"
#include "core_includes.h"


UTimelineKeyFramePicker::UTimelineKeyFramePicker()
{
    mDragData = 0;
    
    mDragStartFrameX = 0.0f;
    mDragStartTouchX = 0.0f;
    
    //mRecievesConsumedTouches = true;
    mRecievesOutsideTouches = true;
    
    
    
    
}

UTimelineKeyFramePicker::~UTimelineKeyFramePicker()
{
    
}

void UTimelineKeyFramePicker::Update()
{
    
}

void UTimelineKeyFramePicker::Draw()
{
    Graphics::SetColor(0.2f, 0.6f, 0.2f, 0.5f);
    Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 3.0f);
    
    
    FMotionPathTemplate *aPath = 0;
    if(gUtilsNode)
    {
        aPath = gUtilsNode->MotionPickPath();
    }
    
    if(aPath)
    {
        FRect aRect;
        
        EnumList(FMotionPathTemplateNode, aNode, aPath->mList)
        {
            float aPercent = ((float)(aNode->mTime)) / ((float)(gUtils->mTimelineTickMax));
            
            aRect.mX = aPercent * mWidth - 6.0f;
            aRect.mY = 8.0f;
            aRect.mWidth = 16.0f;aRect.mHeight = 44.0f;
            
            bool aSelected = ((gUtilsNode->mSelectedKeyPath == aPath) && (gUtilsNode->mSelectedKeyNode == aNode));
            
            
            if(aNode->mTime == gUtils->mTimelineTick)Graphics::SetColor(1.0f, 1.0f, 0.0f);
            else Graphics::SetColor(0.7f, 0.7f, 0.7f);
            
            Graphics::DrawRect(aRect.mX - 2, aRect.mY - 2, aRect.mWidth + 4, aRect.mHeight + 4);
            
            if(aSelected)Graphics::SetColor(0.4f, 1.0f, 0.0f);
            else Graphics::SetColor(0.13f, 0.25f, 0.4f);
            
            Graphics::DrawRect(aRect.mX, aRect.mY, aRect.mWidth, aRect.mHeight);
        }
    }
    

    
}

void UTimelineKeyFramePicker::TouchDown(float pX, float pY, void *pData)
{
    
    mDragData = 0;
    
    mDragStartFrameX = 0.0f;
    mDragStartTouchX = 0.0f;
    
    
    
    mDragData = 0;
    
    mDragStartFrameX = 0.0f;
    mDragStartTouchX = 0.0f;
    
    FMotionPathTemplate *aPath = 0;
    if(gUtilsNode)
    {
        aPath = gUtilsNode->MotionPickPath();
    }
    
    if(aPath)
    {
        FRect aRect;
        
        float aBestDist = 50.0f * 50.0f;
        
        EnumList(FMotionPathTemplateNode, aNode, aPath->mList)
        {
            float aPercent = ((float)(aNode->mTime)) / ((float)(gUtils->mTimelineTickMax));
            
            aRect.mX = aPercent * mWidth - 6.0f;
            aRect.mY = 8.0f;
            aRect.mWidth = 13.0f;aRect.mHeight = 36.0f;
            float aCenterX = aRect.mX + aRect.mWidth / 2.0f;
            float aCenterY = aRect.mY + aRect.mHeight / 2.0f;
            
            
            float aDist = DistanceSquared(aCenterX, aCenterY, pX, pY);
            
            
            
            if(aDist < aBestDist)
            {
                aBestDist = aDist;
                
                mDragData = pData;
                mDragStartFrameX = aRect.mX;
                mDragStartTouchX = pX;
                
                gUtilsNode->mSelectedKeyPath = aPath;
                gUtilsNode->mSelectedKeyNode = aNode;
                
                
            }
        }
    }


    /*
    if(gUtilsNode)
    {
        float aBestDist = 50.0f * 50.0f;
     
        FRect aRect;
        for(int aKeyPathIndex = 0; aKeyPathIndex < gUtilsNode->mKeyPathList.mCount; aKeyPathIndex++)
        {
            FMotionPathTemplate *aPath = ((FMotionPathTemplate *)(gUtilsNode->mKeyPathList.Fetch(aKeyPathIndex)));
            EnumList(FMotionPathTemplateNode, aNode, aPath->mList)
            {
                float aPercent = ((float)(aNode->mTime)) / ((float)(gUtils->mTimelineTickMax));
                
                aRect.mX = aPercent * mWidth - 6.0f;
                aRect.mY = 4.0f + ((float)aKeyPathIndex) * 46.0f;
                aRect.mWidth = 13.0f; aRect.mHeight = 36.0f;
                
                float aCenterX = aRect.mX + aRect.mWidth / 2.0f;
                float aCenterY = aRect.mY + aRect.mHeight / 2.0f;
                
                
                float aDist = DistanceSquared(aCenterX, aCenterY, pX, pY);
                
                
                
                if(aDist < aBestDist)
                {
                    aBestDist = aDist;
                    
                    mDragData = pData;
                    mDragStartFrameX = aRect.mX;
                    mDragStartTouchX = pX;
                    
                    gUtilsNode->mSelectedKeyPath = aPath;
                    gUtilsNode->mSelectedKeyNode = aNode;
                    
                    gUtils->SetSelectedNode(gUtilsNode);
                    
                }
            }
        }
    }
    
    */
    
    
    gUtils->SetSelectedNode(gUtilsNode);
}

void UTimelineKeyFramePicker::TouchMove(float pX, float pY, void *pData)
{
    if(pData == mDragData)
    {
        if(gUtilsNode)
        {
            FMotionPathTemplateNode *aNode = gUtilsNode->mSelectedKeyNode;
            
            if(aNode)
            {
                float aRectX = mDragStartFrameX + (pX - mDragStartTouchX);
                
                
                float aPercent = (aRectX) / ((float)(mWidth));
                
                int aTick = (int)(aPercent * ((float)(gUtils->mTimelineTickMax)) + 0.5f);
                
                if(aTick < 0)aTick = 0;
                if(aTick >(gUtils->mTimelineTickMax))
                {
                    aTick = gUtils->mTimelineTickMax;
                }
                
                if(aNode->mTime != aTick)
                {
                    aNode->mTime = aTick;
                    gUtils->SetSelectedNode(gUtilsNode);
                    gUtils->TimelineApply();
                }
            }
        }
    }
}

void UTimelineKeyFramePicker::TouchUp(float pX, float pY, void *pData)
{
    gUtils->SetSelectedNode(gUtilsNode);
    mDragData = 0;
}

void UTimelineKeyFramePicker::TouchFlush()
{
    
}

void UTimelineKeyFramePicker::Notify(void *pSender)
{
    
}

void UTimelineKeyFramePicker::Refresh(UNode *pNode)
{
    
}


UTimelineEditorMenu::UTimelineEditorMenu()
{
    SetText("Timeline");
    
    if(gDeviceWidth >= 1580)SetFrame(400, 200, 720.0f, 200);
    else SetFrame(400, 200, 540.0f, 200);
    
    AddBlankLine(140.0f);
    //AddBlankLine(100.0f);
    //AddBlankLine(100.0f);
    
    
    //mTimePane = new UMenuPane();
    //mTimePane->mMenuItemResizable = true;
    //mTimePane->SetExpandable(false);
    //mTimePane->SetMenuItemFrame(0.0f, 0.0f, 300.0f, 200.0f);
    //AddLine(mTimePane);
    
    
    mKeyPicker = new UTimelineKeyFramePicker();
    AddSubview(mKeyPicker);
    
    
    
    
    mControlPane = new UTimelineEditorControlPane();
    AddLine(mControlPane);
    mControlPane->Collapse();
    
    
    
    
    mKeyFramePane = new UTimelineEditorKeyFramePane();
    AddLine(mKeyFramePane);
    mKeyFramePane->Collapse();
    
    
    mSelKeyPane = new UTimelineEditorSelectedKeyPane();
    AddLine(mSelKeyPane);
    mSelKeyPane->Collapse();
    
    
    
    //LayoutSubviews();
    
    mThumbWidth = 60.0f;
    
    mTimelineRect = FRect(6.0f, 58.0f, mWidth - 12.0f, 66.0f);
    
    mKeyPicker->SetFrame(mTimelineRect.mX + (mThumbWidth / 2.0f), 126.0f, (mTimelineRect.mWidth - mThumbWidth), 90.0f);
    
    RefreshThumb();
    
    mDrawThumbRectOutline.SetRect(-2, -2, mThumbRect.mWidth + 4, mThumbRect.mHeight + 4);
    mDrawThumbRectOutline.mCornerPointCount = 12;
    mDrawThumbRectOutline.mCornerRadius = 12.0f;
    mDrawThumbRectOutline.SetColorTop(0.5909, 0.2091, 0.0000, 1.0000);
    mDrawThumbRectOutline.SetColorBottom(0.8273, 0.0909, 0.0727, 1.0000);
    mDrawThumbRectOutline.mRefresh = true;
    
    mDrawThumbRectBottom.SetRect(0.0f, 0.0f, mThumbRect.mWidth, mThumbRect.mHeight);
    mDrawThumbRectBottom.mCornerPointCount = 12;
    mDrawThumbRectBottom.mCornerRadius = 8.0f;
    mDrawThumbRectBottom.SetColorTop(0.8727f, 0.1909f, 0.0000f, 1.0000f);
    mDrawThumbRectBottom.SetColorBottom(1.0000f, 0.7182f, 0.0000f, 1.0000f);
    mDrawThumbRectBottom.mRefresh = true;
    
    mDrawThumbRectFront.SetRect(6.0f, 6.0f, mThumbRect.mWidth - 12.0f, mThumbRect.mHeight - 12.0f);
    mDrawThumbRectFront.mCornerPointCount = 12;
    mDrawThumbRectFront.mCornerRadius = 6.0f;
    mDrawThumbRectFront.SetColorTop(1.0000f, 0.9273f, 0.5182f, 1.0000f);
    mDrawThumbRectFront.SetColorBottom(1.0000f, 0.2091f, 0.0091f, 1.0000f);
    mDrawThumbRectFront.mRefresh = true;
    
    
    
    mDrawBarRectBottom.SetRect(0.0f, mTimelineRect.mHeight / 2.0f - 10.0f, mTimelineRect.mWidth, 20.0f);
    mDrawBarRectBottom.mCornerPointCount = 6;
    mDrawBarRectBottom.mCornerRadius = 6.0f;
    mDrawBarRectBottom.mRefresh = true;
    mDrawBarRectBottom.SetColorTop(0.4f, 0.4f, 0.4f);
    mDrawBarRectBottom.SetColorBottom(0.25f, 0.25f, 0.25f);
    
    
    mDragData = 0;
    mDragThumbX = 0.0f;
    mDragStartTouchX = 0.0f;
    
    SetMenuItemFrame(mX, mY, mWidth, mHeight);
    
    LayoutSubviews();
}

UTimelineEditorMenu::~UTimelineEditorMenu()
{
    
    
}


void UTimelineEditorMenu::Update()
{
    UMenu::Update();
}

void UTimelineEditorMenu::Draw()
{
    UMenu::Draw();
    
    if(gUtils->mTimelineEnabled)
    {
        RefreshThumb();
    }
    
    if(mExpanded == true)
    {
        
        Graphics::SetColor();
        
        mDrawBarRectBottom.Draw(mTimelineRect.mX, mTimelineRect.mY);
        
        mDrawThumbRectOutline.Draw(mThumbRect.mX, mThumbRect.mY);
        mDrawThumbRectBottom.Draw(mThumbRect.mX, mThumbRect.mY);
        mDrawThumbRectFront.Draw(mThumbRect.mX, mThumbRect.mY);
        
        gAppBase->mSysFontBold.Center(FString(gUtils->mTimelineTick), mThumbRect.Center().mX, mThumbRect.Center().mY);
    }
}

void UTimelineEditorMenu::TouchDown(float pX, float pY, void *pData)
{
    mDragData = 0;
    
    if(mKeyPicker->mDragData != 0)
    {
        mDragFrameMode = false;
        return;
    }
    
    if(mThumbRect.ContainsPoint(pX, pY))
    {
        mDragFrameMode = false;
        
        gUtils->mTimelineEnabled = false;
        
        mDragData = pData;
        
        mDragThumbX = mThumbRect.mX;
        mDragStartTouchX = pX;
        
        mControlPane->Refresh();
    }
    else
    {
        mDragFrameMode = true;
    }
    
    
    
    
    
}

void UTimelineEditorMenu::TouchMove(float pX, float pY, void *pData)
{
    if(mKeyPicker->mDragData != 0)
    {
        mDragFrameMode = false;
        return;
    }
    
    if(pData == mDragData)
    {
        float aActiveWidth = (mTimelineRect.mWidth - mThumbWidth);
        float aMinX = mTimelineRect.mX;
        float aMaxX = mTimelineRect.mX + aActiveWidth;
        
        
        mThumbRect.mX = mDragThumbX + (pX - mDragStartTouchX);
        if(mThumbRect.mX < aMinX)mThumbRect.mX = aMinX;
        if(mThumbRect.mX > aMaxX)mThumbRect.mX = aMaxX;
        
        float aPercent = (mThumbRect.mX - aMinX) / (aActiveWidth);
        
        
        int aTick = (int)(aPercent * ((float)(gUtils->mTimelineTickMax)) + 0.5f);
        
        gUtils->TimelineSet(aTick);
        
        //mValue = (mCursorX - aBorderLeft) / (aBorderRight - aBorderLeft);
        
    }
}

void UTimelineEditorMenu::TouchUp(float pX, float pY, void *pData)
{
    mDragData = 0;
    mDragFrameMode = true;
}

void UTimelineEditorMenu::TouchFlush()
{
    mDragData = 0;
    mDragFrameMode = true;
}


void UTimelineEditorMenu::Notify(void *pSender)
{
    
}

void UTimelineEditorMenu::SetSelectedNode(UNode *pNode)
{
    
}

void UTimelineEditorMenu::RefreshThumb()
{
    if(gUtils->mTimelineTickMax < 1)gUtils->mTimelineTickMax = 1;
    float aPercent = (float)(gUtils->mTimelineTick) / (float)(gUtils->mTimelineTickMax);
    float aThumbX = (mTimelineRect.mWidth - mThumbWidth) * aPercent;
    mThumbRect = FRect(mTimelineRect.mX + aThumbX, mTimelineRect.mY, mThumbWidth, mTimelineRect.mHeight);
}









UTimelineEditorControlPane::UTimelineEditorControlPane()
{
    SetText("Timeline Controls");
    SetExpandable(true);
    
    mButtonPlay = new UButton("Play");
    mButtonPlay->StyleSetCheckBox();
    mButtonPlay->mChecked = (!gUtils->mTimelineEnabled);
    mButtonPlay->mMenuItemWidthSlots = 2;
    
    
    
    mButtonFastForward = new UButton("Fast Mo");
    mButtonFastForward->StyleSetCheckBox();
    
    mButtonSlowMotion = new UButton("Slow Mo");
    mButtonSlowMotion->StyleSetCheckBox();
    
    
    mButtonLoopSetStart = new UButton("Set Start");
    mButtonLoopSetEnd = new UButton("Set End");
    
    
    AddLine(mButtonSlowMotion, mButtonFastForward, mButtonPlay, mButtonLoopSetStart, mButtonLoopSetEnd);
    
    
    mButtonSpan50 = new UButton("D-50");
    mButtonSpan100 = new UButton("D-100");
    mButtonSpan200 = new UButton("D-200");
    mButtonSpan400 = new UButton("D-400");
    
    
    mButtonNextFrame = new UButton("Frame ++");
    mButtonPrevFrame = new UButton("Frame --");
    mButtonSelectedFrame = new UButton("Frame - Sel");
    
    AddLine(mButtonSpan50, mButtonSpan100, mButtonSpan200, mButtonSpan400, mButtonPrevFrame, mButtonNextFrame, mButtonSelectedFrame);
    
    
    Refresh();
    
    mButtonPlay->SetTargetCheck(&(gUtils->mTimelineEnabled));
    
    mButtonFastForward->SetTargetCheck(&(gUtils->mTimelineFastForward));
    mButtonSlowMotion->SetTargetCheck(&(gUtils->mTimelineSlowMotion));
    
    
}



UTimelineEditorControlPane::~UTimelineEditorControlPane()
{
    
}

void UTimelineEditorControlPane::Refresh()
{
    if(mButtonPlay->mChecked != gUtils->mTimelineEnabled)
    {
        mButtonPlay->mChecked = gUtils->mTimelineEnabled;
        
        if(gUtils->mTimelineEnabled)mButtonPlay->SetText("[Pause]");
        else mButtonPlay->SetText("[Play]");
        
    }
    
    
    
    
    
    
    //mTimelineFastForward = false;
    //mTimelineSlowMotion = false;
    //mTimelineSlowMotionTick = 0;
    
}

void UTimelineEditorControlPane::Notify(void *pSender)
{
    if(pSender == mButtonPlay)
    {
        
    }
    
    if(pSender == mButtonSpan50){if(gUtils)gUtils->TimelineSetMax(50);}
    if(pSender == mButtonSpan100){if(gUtils)gUtils->TimelineSetMax(100);}
    if(pSender == mButtonSpan200){if(gUtils)gUtils->TimelineSetMax(200);}
    if(pSender == mButtonSpan400){if(gUtils)gUtils->TimelineSetMax(400);}
    
    if(pSender == mButtonNextFrame)gUtils->TimelineNextFrame();
    if(pSender == mButtonPrevFrame)gUtils->TimelinePrevFrame();
    
    if(pSender == mButtonLoopSetStart)gUtils->mTimelineLoopStartTick = gUtils->mTimelineTick;
    if(pSender == mButtonLoopSetEnd)gUtils->mTimelineLoopEndTick = gUtils->mTimelineTick;
    
    if(pSender == mButtonSelectedFrame)
    {
        if(gUtilsNode)
        {
            if(gUtilsNode->mSelectedKeyNode)
            {
                gUtils->mTimelineEnabled = false;
                gUtils->mTimelineTick = gUtilsNode->mSelectedKeyNode->mTime;
            }
        }
    }
    
    Refresh();
}




UTimelineEditorKeyFramePane::UTimelineEditorKeyFramePane()
{
    SetText("Keyframes");
    SetExpandable(true);
    
    mButtonDeleteAll = new UButton("Clear All");
    mButtonDelete = new UButton("Delete Selected");
    
    mButtonKeySelectNext = new UButton("Sel - Next");
    mButtonKeySelectPrev = new UButton("Sel - Prev");
    
    AddLine(mButtonDeleteAll, mButtonDelete, mButtonKeySelectPrev, mButtonKeySelectNext);
    
    mButtonCreate1 = new UButton("Key XY");;
    mButtonCreate2 = new UButton("Key TRAN");
    mButtonCreate3 = new UButton("Key - CLR");
    
    AddLine(mButtonCreate1, mButtonCreate2, mButtonCreate3);
    
    mStepperType = new UStepper("Type", 1);
    
    mLabelType = new ULabel("A Label");
    mLabelType->mMenuItemWidthSlots = 5;
    
    AddLine(mStepperType, mLabelType);
    
    
    
    
    
}

UTimelineEditorKeyFramePane::~UTimelineEditorKeyFramePane()
{
    
}

void UTimelineEditorKeyFramePane::Notify(void *pSender)
{
    if(gUtilsNode)
    {
        if(pSender == mButtonCreate1)gUtilsNode->MotionKeyMake(gUtils->mTimelineTick, 0);
        if(pSender == mButtonCreate2)gUtilsNode->MotionKeyMake(gUtils->mTimelineTick, 1);
        if(pSender == mButtonCreate3)gUtilsNode->MotionKeyMake(gUtils->mTimelineTick, 2);
        
        
        if(pSender == mButtonKeySelectNext)gUtilsNode->MotionKeySelectNext();
        if(pSender == mButtonKeySelectPrev)gUtilsNode->MotionKeySelectPrev();
        
        
        if(pSender == mButtonDelete)gUtilsNode->MotionKeyDeleteSelected();
        if(pSender == mButtonDeleteAll)gUtilsNode->MotionKeyDeleteAll();
        
        
        
        gUtils->SetSelectedNode(gUtilsNode);
    }
}

void UTimelineEditorKeyFramePane::SetSelectedNode(UNode *pNode)
{
    
    if(pNode)
    {
        if((pNode->mSelectedKeyPath) && (pNode->mSelectedKeyNode))
        {
            int aFunction = pNode->mSelectedKeyNode->mAnimationFunction;
            mStepperType->SetTarget(&(pNode->mSelectedKeyNode->mAnimationFunction));
            mLabelType->SetText(FAnimation::GetFunctionNameExtended(aFunction).c());
            
        }
        else
            
        {
            mLabelType->SetText("---");
            
        }
        
        int aIndex = 0;
        
        /*
        EnumList(FMotionPathTemplate, aPath, pNode->mKeyPathList)
        {
            if(aIndex == 0)
            {
                //mStepperType1->SetTarget(aPath->m);
                
            }
            
            aIndex++;
        }
        */
        
        //mStepperType1->SetTarget(0);
        //mStepperType2->SetTarget(0);
        //mStepperType3->SetTarget(0);
    }
    else
    {
        mStepperType->SetTarget(0);
        
        mLabelType->SetText("---");
        
        //mStepperType2->SetTarget(0);
        //mStepperType3->SetTarget(0);
        
    }
    
}

void UTimelineEditorKeyFramePane::Refresh()
{
    
}



UTimelineEditorSelectedKeyPane::UTimelineEditorSelectedKeyPane()
{
    SetText("Selected Key");
    SetExpandable(true);
    
    mSliderRotation = new UExtendedSlider("Rot:", 0.0f, 360.0f);
    AddLine(mSliderRotation);
    
    mSliderTrackOffX = new UExtendedSlider("X-Off:", -360.0f, 360.0f);
    AddLine(mSliderTrackOffX);
    
    
    mSliderTrackOffY = new UExtendedSlider("Y-Off:", -360.0f, 360.0f);
    AddLine(mSliderTrackOffY);
    
    
    mButtonRead = new UButton("ReadTo");
    
    mButtonTrackScreen = new UButton("Track Screen");
    mButtonTrackScreen->StyleSetCheckBox();
    AddLine(mButtonRead, mButtonTrackScreen);
    
    mRelationTypeSegmentX = new USegment(3);
    mRelationTypeSegmentX->SetTitles("Left", "Center", "Right");
    AddLine(new ULabel("X-Trk"), mRelationTypeSegmentX);
    
    mRelationTypeSegmentY = new USegment(3);
    mRelationTypeSegmentY->SetTitles("Top", "Center", "Bottom");
    AddLine(new ULabel("Y-Trk"), mRelationTypeSegmentY);
}

UTimelineEditorSelectedKeyPane::~UTimelineEditorSelectedKeyPane()
{
    
}

void UTimelineEditorSelectedKeyPane::Notify(void *pSender)
{
    FMotionPathTemplateNode *aKey = 0;
    
    if(gUtilsNode)
    {
        if(gUtilsNode->mSelectedKeyNode)
        {
            aKey = gUtilsNode->mSelectedKeyNode;
        }
    }
    
    if(pSender == mButtonRead)
    {
        if(aKey && gUtilsNode)
        {
            aKey->mX = gUtilsNode->mWorldX;
            aKey->mY = gUtilsNode->mWorldY;
            
            aKey->mRotation = gUtilsNode->mObject->mRotation;
        }
        
        
    }
}

void UTimelineEditorSelectedKeyPane::SetSelectedNode(UNode *pNode)
{
    FMotionPathTemplateNode *aKey = 0;
    
    if(pNode)
    {
        if(pNode->mSelectedKeyNode)
        {
            aKey = pNode->mSelectedKeyNode;
        }
    }
    
    if(aKey)
    {
        mSliderRotation->SetTarget(&(aKey->mRotation));
        
        mButtonTrackScreen->SetTargetCheck(&(aKey->mTrackScreen));
        
        mRelationTypeSegmentX->SetTarget(&(aKey->mTrackSideX));
        mRelationTypeSegmentY->SetTarget(&(aKey->mTrackSideY));
        
        mSliderTrackOffX->SetTarget(&(aKey->mTrackOffsetX));
        mSliderTrackOffY->SetTarget(&(aKey->mTrackOffsetY));
    }
    else
    {
        mSliderRotation->SetTarget(0);
        
        mButtonTrackScreen->SetTargetCheck(0);
        
        mRelationTypeSegmentX->SetTarget(0);
        mRelationTypeSegmentY->SetTarget(0);
        
        mSliderTrackOffX->SetTarget(0);
        mSliderTrackOffY->SetTarget(0);
    }
}



