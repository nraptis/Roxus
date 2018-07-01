
#include "UImagePicker.h"
#include "UMainCanvas.h"
#include "core_includes.h"

UImagePickerScrollContent::UImagePickerScrollContent(float pX, float pY, float pWidth, float pHeight) : FGestureView()
{
    mName = "Image Picker Scroller";
    
    mMaxRows = 6;
    
    mDrawManual = true;
    mNotifyParent = true;
    
    SetFrame(pX, pY, pWidth, pHeight);
    
    mCellGrid = 0;
    
    mScrollSpeedX = 0.0f;
    mScrollSpeedY = 0.0f;
    
    mScrollOffsetX = 0.0f;
    mScrollOffsetY = 0.0f;
    
    mGridOffsetX = 0;
    mGridOffsetY = 0;
    
    mCellSpacingH = 2.0f;
    mCellSpacingV = 2.0f;
    
    mCellWidth = 60.0f;
    mCellHeight = 60.0f;
    
    mCellHeight = (pHeight / ((float)mMaxRows)) - (mCellSpacingV * (mMaxRows + 1));
    mCellWidth = (mCellHeight * 1.4f);
    
    mColCount = 0;
    mRowCount = 0;
    
    float aWidth = gAppWidth;
    float aProbeX = mCellSpacingH;
    
    int aScreenColCount = 0;
    
    while(aProbeX < aWidth)
    {
        aScreenColCount++;
        aProbeX += (mCellWidth + mCellSpacingH);
    }
    
    mScreenGridWidth = (aScreenColCount);// + 2);
    
    mCellGrid = 0;
    
    mColCount = 0;
    mRowCount = 1;
}

UImagePickerScrollContent::~UImagePickerScrollContent()
{
    for(int aCol=0;aCol<mColCount;aCol++)
    {
        delete [] mCellGrid[aCol];// = new UImagePickerScrollContentCell *[mRowCount];
    }
    delete [] mCellGrid;
    
    mCellGrid = 0;
    mColCount = 0;
    mRowCount = 0;
}

void UImagePickerScrollContent::Update()
{
    if(mScrollFlingSpeed > 0)
    {
        mScrollFlingSpeed *= 0.940f;
        mScrollFlingSpeed -= 0.1f;
        
        if(mScrollFlingSpeed <= 0)
        {
            mScrollFlingSpeed = 0;
        }
        
        mScrollOffsetX += mScrollFlingSpeed * mScrollSpeedX;
    }
    
    float aCellWidth = (mCellWidth + mCellSpacingH);
    
    UImageCell *aHold = 0;
    
    if((mColCount == 0) && (mRowCount == 1))
    {
        
    }
    
    if(mCellGrid != 0)
    {
        while (mScrollOffsetX >= aCellWidth)
        {
            mGridOffsetX++;
            if(mGridOffsetX >= mColCount)mGridOffsetX -= mColCount;
            
            mScrollOffsetX -= aCellWidth;
            
            for(int n = 0; n < mRowCount; n++)
            {
                aHold = mCellGrid[mColCount - 1][n];
                for(int i = (mColCount - 2); i >= 0; i--)
                {
                    mCellGrid[i + 1][n] = mCellGrid[i][n];
                }
                mCellGrid[0][n] = aHold;
            }
        }
        
        while (mScrollOffsetX <= 0.0f)
        {
            mGridOffsetX--;
            if(mGridOffsetX < 0)mGridOffsetX += mColCount;
            
            //aShifted = true;
            mScrollOffsetX += aCellWidth;
            
            for(int n = 0; n < mRowCount; n++)
            {
                aHold = mCellGrid[0][n];
                for(int i = 1; i < mColCount; i++)
                {
                    mCellGrid[i - 1][n] = mCellGrid[i][n];
                }
                mCellGrid[mColCount - 1][n] = aHold;
            }
        }
        
        int aIndex = 0;
        
        float aProbeX = mCellSpacingH;
        float aProbeY = mCellSpacingV;
        
        for(int aRow = 0; aRow < mRowCount; aRow++)
        {
            aProbeX = (mCellSpacingH - aCellWidth);
            
            for(int aCol = 0; aCol < mColCount; aCol++)
            {
                UImageCell *aCell = mCellGrid[aCol][aRow];
                
                if(aCell)
                {
                    aCell->SetFrame(aProbeX + mScrollOffsetX, aProbeY, mCellWidth, mCellHeight);
                    
                    if((aCell->mX >= (-mCellWidth)) && (aCell->mX < (mWidth)))
                    {
                        aCell->mHidden = false;
                        aCell->mEnabled = true;
                    }
                    else
                    {
                        aCell->mHidden = true;
                        aCell->mEnabled = false;
                    }
                }
                
                
                aProbeX += (mCellWidth + mCellSpacingH);
                aIndex++;
                
            }
            
            aProbeY += (mCellHeight + mCellSpacingV);
        }
    }
}

void UImagePickerScrollContent::Draw()
{
    
}

void UImagePickerScrollContent::AddCell(UImageCell *pCell)
{
    
    if(pCell)
    {
        //pCell->SetCellSize(mCellWidth, mCellHeight);
        
        //pCell->mBaseX = ((float)(mCellList.mCount)) * mCellWidth;
        float aPlaceX = ((float)(mCellList.mCount)) * mCellWidth;
        
        pCell->SetFrame(aPlaceX, 0.0f, mCellWidth, mCellHeight);
        mCellList += pCell;
        AddSubview(pCell);
        
        pCell->mConsumesTouches = false;
    }
    
}

void UImagePickerScrollContent::TouchDown(float pX, float pY, void *pData)
{
    mScrollFlingSpeed = 0.0f;
    
    mScrollSpeedX = 0.0f;
    mScrollSpeedY = 0.0f;
}

void UImagePickerScrollContent::PanBegin(float pX, float pY)
{
    mScrollOffsetX += pX;
    mScrollOffsetY += pY;
}


void UImagePickerScrollContent::Pan(float pX, float pY)
{
    mScrollOffsetX += pX;
    mScrollOffsetY += pY;
    
    
    EnumList(UImageCell, aCell, mCellList)
    {
        aCell->mTouchCanceled = true;
    }
    
}

void UImagePickerScrollContent::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY)
{
    float aSpeed = pSpeedX * pSpeedX + pSpeedY * pSpeedY;
    
    if(aSpeed > 0.1f)
    {
        aSpeed = sqrtf(aSpeed);
        pSpeedX /= aSpeed;
        pSpeedY /= aSpeed;
    }
    
    mScrollSpeedX = (pSpeedX);
    mScrollSpeedY = (pSpeedY);
    
    mScrollFlingSpeed = aSpeed;
    
    if(mScrollFlingSpeed > 50.0f)mScrollFlingSpeed = 50.0f;
    
    
    EnumList(UImageCell, aCell, mCellList)
    {
        aCell->mTouchCanceled = false;
    }
    
}

void UImagePickerScrollContent::LayoutSubviews()
{
    
    int aCount = mCellList.mCount;
    
    for(int aCol=0;aCol<mColCount;aCol++)
    {
        delete [] mCellGrid[aCol];// = new UImagePickerScrollContentCell *[mRowCount];
    }
    
    if(mScreenGridWidth < 5)mScreenGridWidth = 5;
    
    mCellGrid = 0;
    
    mColCount = 0;
    mRowCount = 1;
    
    if(aCount <= 0)
    {
        
    }
    else
    {
        if(aCount <= mScreenGridWidth)
        {
            mColCount = aCount;
        }
        else
        {
            int aScan = aCount;
            while(aScan > mScreenGridWidth)
            {
                aScan -= mScreenGridWidth;
                mRowCount++;
            }
            
            if(mRowCount > mMaxRows)
            {
                mRowCount = mMaxRows;
                mColCount = (aCount / mRowCount);
                if((aCount % mRowCount) != 0)mColCount++;
            }
            else
            {
                mColCount = mScreenGridWidth;
            }
        }
        
        
        mCellGrid = new UImageCell**[mColCount];
        for(int aCol=0;aCol<mColCount;aCol++)
        {
            mCellGrid[aCol] = new UImageCell*[mRowCount];
            for(int aRow=0;aRow<mRowCount;aRow++)
            {
                mCellGrid[aCol][aRow] = 0;
            }
        }
        
        int aIndex = 0;
        
        float aProbeX = mCellSpacingH;
        float aProbeY = mCellSpacingV;
        
        for(int aRow=0;aRow<mRowCount;aRow++)
        {
            aProbeX = mCellSpacingH;
            
            for(int aCol=0;aCol<mColCount;aCol++)
            {
                UImageCell *aCell = ((UImageCell *)(mCellList.Fetch(aIndex)));
                
                if(aCell)
                {
                    mCellGrid[aCol][aRow] = aCell;
                    
                    //aCell->mBaseX = aProbeX;
                    //aCell->mBaseY = aProbeY;
                }
                
                
                aProbeX += (mCellWidth + mCellSpacingH);
                aIndex++;
            }
            
            aProbeY += (mCellHeight + mCellSpacingV);
        }
    }
    
    SetHeight((((float)mRowCount) * (mCellHeight + mCellSpacingV)) + mCellSpacingV);
}

UImagePicker::UImagePicker(FView *pListener)
{
    
    float aX = gDeviceWidth2 / 3.0f;
    float aY = gDeviceHeight2 / 3.0f;
    
    float aWidth = gDeviceWidth2 + gDeviceWidth2 / 2.0f;
    float aHeight = gDeviceHeight2 + gDeviceHeight2 / 2.0f;
    
    //UImagePicker::UImagePicker(gAppWidth2 / 3.0f, gAppHeight2 / 3.0f, gAppWidth2 + gAppWidth2 / 2.0f, gAppHeight2 + gAppHeight2 / 2.0f);
    mName = "Image Picker";
    
    SetMenuItemFrame(aX, aY, aWidth, aHeight);
    SetText("Pick Image");
    
    //UMenu::SetUp(aX, aY, aWidth, "Image Picker!");
    //SetHeight(aHeight);
    
    //UMenu::SetUp(pX, pY, pWidth, pHeight);
    
    //mRectToolbar.mRoundBottom = false;
    //mRectBack.mCornerRadius = 6;
    
    mDragFrameMode = true;
    mClipsContent = true;
    
    //mListener = 0;
    
    
    //float aWidth = pWidth;
    
    
    mScrollContent = new UImagePickerScrollContent(0.0f, UTIL_MENU_TOOLBAR_HEIGHT, aWidth, (aHeight - UTIL_MENU_TOOLBAR_HEIGHT));
    AddSubview(mScrollContent);
    
    SetMenuItemFrame(aX, aY, aWidth, aHeight);
    
    //mQuadBackground.SetRect(0.0f, 0.0f, mWidth, mHeight);
    //mQuadBackground.SetColorTop(0.99f, 0.99f, 0.99f);
    //mQuadBackground.SetColorBottom(0.90f, 0.90f, 0.90f);
    
    
    mListener = pListener;
}

/*
 UImagePicker::UImagePicker(float pX, float pY, float pWidth, float pHeight)// : UMenu()
 {
 mName = "Image Picker";
 
 SetFrame(pX, pY, pWidth, pHeight);
 SetTitle("Pick Image");
 
 //UMenu::SetUp(pX, pY, pWidth, "Image Picker!");
 //SetHeight(pHeight);
 
 //UMenu::SetUp(pX, pY, pWidth, pHeight);
 
 //mRectToolbar.mRoundBottom = false;
 //mRectBack.mCornerRadius = 6;
 
 mDragFrameMode = true;
 mClipsContent = true;
 
 mListener = 0;
 
 float aWidth = pWidth;
 
 mScrollContent = new UImagePickerScrollContent(0.0f, UTIL_MENU_TOOLBAR_HEIGHT, aWidth, 160.0f);
 AddSubview(mScrollContent);
 
 SetFrame(pX, pY, pWidth, pHeight);
 
 //mQuadBackground.SetRect(0.0f, 0.0f, mWidth, mHeight);
 //mQuadBackground.SetColorTop(0.99f, 0.99f, 0.99f);
 //mQuadBackground.SetColorBottom(0.90f, 0.90f, 0.90f);
 }
 */

UImagePicker::~UImagePicker()
{
    
}

void UImagePicker::Update()
{
    if(mDidLayoutSubviews == false)
    {
        mDidLayoutSubviews = true;
        LayoutSubviews();
    }
}

void UImagePicker::Draw()
{
    if(mExpanded)
    {
        DrawBottom();
        
        if(mScrollContent)
        {
            mScrollContent->DrawManual();
            DrawTransform();
        }
        
        Graphics::SetColor();
        DrawToolbar();
    }
}

void UImagePicker::TouchDown(float pX, float pY, void *pData)
{
    
}

void UImagePicker::Notify(void *pSender, int pID, void *pObject)
{
    if((pObject != 0) && (pSender != 0))
    {
        
        bool aShift = (gKeyPressed[DIK_LSHIFT]);
        bool aCtrl = (gKeyPressed[DIK_LCONTROL]);
        
        
        FSprite *aSprite = ((FSprite *)pObject);
        FSpriteSequence *aSpriteSequence = ((FSpriteSequence *)pObject);
        
        UImageCell *aCell = (UImageCell *)pSender;
        
        if(pID == IMG_PICK_RESPONSE_SPRITE)
        {
            if(aSprite)
            {
                
                if(aShift)
                {
                    FString aName = aSprite->mFileName;
                    
                    Log("gUtils->BlockSprite(\"%s\");\n", aName.c());
                    return;
                }
                
                if(mListener)
                {
                    if(aCell->mDestroySprite)
                    {
                        FSprite *aClone = new FSprite();
                        aClone->Load(aSprite->mFileName);
                        aSprite = aClone;
                    }
                    
                    mListener->Notify(this, IMG_PICK_RESPONSE_SPRITE, aSprite);
                    
                    if(aCtrl == false)Kill();
                    
                    return;
                    
                }
            }
        }
        else if(pID == IMG_PICK_RESPONSE_SEQUENCE)
        {
            if(aSpriteSequence)
            {
                if(aShift)
                {
                    FString aName = aSpriteSequence->mFilePrefix;
                    
                    Log("gUtils->BlockSprite(\"%s\");\n", aName.c());
                    return;
                }
                
                if(mListener)
                {
                    mListener->Notify(this, IMG_PICK_RESPONSE_SEQUENCE, aSpriteSequence);
                    
                    if(aCtrl == false)Kill();
                    
                    return;
                }
            }
        }
    }
}

void UImagePicker::AddSprite(const char *pSpritePath)
{
    FSprite *aSprite = new FSprite();
    aSprite->Load(pSpritePath);
    UImageCell *aCell = new UImageCell(aSprite, true);
    aCell->SetUp(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
    mScrollContent->AddCell(aCell);
    mDidLayoutSubviews = false;
}

void UImagePicker::AddSprite(FSprite *pSprite)
{
    
    if(pSprite)
    {
        
        FString aPath = pSprite->mFileName.c();
        
        EnumList(FString, aString, gUtils->mBlockedSpriteList)
        {
            if(*aString == aPath)
            {
                return;
            }
        }
        
        
        UImageCell *aCell = new UImageCell(pSprite, false);
        aCell->SetUp(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
        mScrollContent->AddCell(aCell);
        mDidLayoutSubviews = false;
        
    }
}

void UImagePicker::AddSpriteSequence(FSpriteSequence *pSpriteSequence)
{
    if(pSpriteSequence)
    {
        FString aPath = pSpriteSequence->mFilePrefix.c();
        EnumList(FString, aString, gUtils->mBlockedSpriteList)
        {
            if(*aString == aPath)
            {
                return;
            }
        }
        
        UImageCellSequence *aCell = new UImageCellSequence(pSpriteSequence, false);
        aCell->SetUp(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
        mScrollContent->AddCell(aCell);
        mDidLayoutSubviews = false;
        
    }
}

void UImagePicker::LayoutSubviews()
{
    if(mScrollContent)
    {
        mScrollContent->LayoutSubviews();
        SetHeight(UTIL_MENU_TOOLBAR_HEIGHT + mScrollContent->mHeight);
    }
    
    //mQuadBackground.SetRect(0.0f, 0.0f, mWidth, mHeight);
}

void UImagePicker::FillWithAny()
{
    EnumList(FSprite, aSprite, gSpriteList)
    {
        AddSprite(aSprite);
    }
    
    EnumList(FSpriteSequence, aSequence, gSpriteSequenceList)
    {
        AddSpriteSequence(aSequence);
    }
}

void UImagePicker::FillWithImages()
{
    EnumList(FSprite, aSprite, gSpriteList)
    {
        AddSprite(aSprite);
    }
}

void UImagePicker::FillWithImageSequences()
{
    EnumList(FSpriteSequence, aSequence, gSpriteSequenceList)
    {
        AddSpriteSequence(aSequence);
    }
}

