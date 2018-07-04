#include "MainApp.h"
#include "UMainCanvas.h"
#include "MapScreen.h"
#include "MainMenu.h"
#include "Game.h"
#include "MainMenuVolcano.h"
#include "MainMenuRock.h"

MainMenu::MainMenu()
{
    mName = "MainMenu";
    
    mRecievesConsumedTouches = true;
    
    mTitleContainer = 0;
    mButtonContainer = 0;
    
    mStego = 0;
    
#ifndef DISABLE_SOUNDS
    core_sound_musicCrossFade("music_main_menu.mp3", 80, true);
#endif
    
    mTopInterfaceFrame.mX = 0.0f;
    mTopInterfaceFrame.mY = 0.0f;
    mTopInterfaceFrame.mWidth = gVirtualDevWidth;
    mTopInterfaceFrame.mHeight = gVirtualDevHeight;
    
    if(mTopInterfaceFrame.mWidth < 280.0f)mTopInterfaceFrame.mWidth = 280.0f;
    if(mTopInterfaceFrame.mHeight < 200.0f)mTopInterfaceFrame.mHeight = 200.0f;
    
    
    SetStaticTransform(true);
    SetFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    
    

    
    mFloorX = 0.0f;
    mFloorY = 0.0f;
    mFloorCenterX = gVirtualDevWidth / 2.0f;
    mFloorCenterY = gVirtualDevHeight / 2.0f;
    
    mFloorWidth = 768.0f;
    mFloorHeight = 256.0f;
    
    mFloorScale = 1.0f;
    
    
    
    mSun = new MainMenuSun();
    
    
    MainMenuSceneItem *aItem = 0;
    
    
    aItem = new MainMenuRock(&(gApp->mTitleRock[0]));
    aItem->SetRelativePos(148.5f, 65.0f);
    mSceneItemListMiddle.Add(aItem);
    
    
    aItem = new MainMenuRock(&(gApp->mTitleRock[1]));
    aItem->SetRelativePos(188.0f, 96.5f);
    mSceneItemListMiddle.Add(aItem);
    
    
    
    
    aItem = new MainMenuSceneItem(&(gApp->mTitleMonolith[0]));
    aItem->SetRelativePos(182.0f, -179.0f - 20.0f);
    mSceneItemListBottom.Add(aItem);
    
    aItem = new MainMenuSceneItem(&(gApp->mTitleMonolith[1]));
    aItem->SetRelativePos(-71.5f, -136.5f - 20.0f);
    mSceneItemListBottom.Add(aItem);
    
    aItem = new MainMenuSceneItem(&(gApp->mTitleMonolith[2]));
    aItem->SetRelativePos(-218.5f, -168.5f - 20.0f);
    mSceneItemListBottom.Add(aItem);
    
    MainMenuVolcano *aVolcano1 = new MainMenuVolcano(&(gApp->mTitleVolcano[0]));
    aVolcano1->SetRelativePos(-219.0f, -134.0f);
    aVolcano1->SetMouthPos(-36.0f, -55.0f);
    aVolcano1->mSmokeBaseDriftSinSpeed = 3.0f;
    aVolcano1->mBaseMouthDir = -2.0f;
    aVolcano1->mBounceFactor = 1.0f;
    mSceneItemListBottom.Add(aVolcano1);
    
    MainMenuVolcano *aVolcano2 = new MainMenuVolcano(&(gApp->mTitleVolcano[1]));
    aVolcano2->SetRelativePos(262.0f, -209.0f);
    aVolcano2->SetMouthPos(-19.0f, -61.0f);
    aVolcano2->mSmokeBaseDriftSinSpeed = 3.0f;
    aVolcano2->mBaseMouthDir = 4.0f;
    aVolcano2->mBounceFactor = 0.5f;
    mSceneItemListBottom.Add(aVolcano2);
    
    
    MainMenuVolcano *aVolcano3 = new MainMenuVolcano(&(gApp->mTitleVolcano[2]));
    aVolcano3->SetRelativePos(-107.0f, -165.0f);
    aVolcano3->SetMouthPos(-3.0f, -50.0f);
    aVolcano3->mSmokeBaseDriftSinSpeed = 9.0f;
    aVolcano3->mBaseMouthDir = -7.0f;
    aVolcano3->mBounceFactor = 0.5f;
    mSceneItemListBottom.Add(aVolcano3);
    
    
    
    
    
    
    
    
    
    
    
    mButtonContainer = new FView();
    mButtonContainer->mName = "MM Button Container";
    mButtonContainer->mColor = FColor(0.5f, 1.0f, 0.8f, 0.2f);
    AddSubview(mButtonContainer);
    mButtonContainer->mParent = this;
    
    mButtonContainer->SetWidth(500.0f);
    mButtonContainer->SetHeight(260.0f);
    mButtonContainer->SetCenter(mWidth2, mHeight2 - 60.0f);
    mButtonContainer->mDrawManual = true;
    mButtonContainer->mNotifyParent = true;
    
    
    mTitleContainer = new FView();
    mTitleContainer->mName = "MM Title Container";
    mTitleContainer->mColor = FColor(0.66f, 0.77f, 0.44f, 0.2f);
    AddSubview(mTitleContainer);
    mTitleContainer->mParent = this;
    
    mTitleContainer->SetWidth(640.0f);
    mTitleContainer->SetHeight(260.0f);
    mTitleContainer->SetCenter(mWidth2, mHeight2);
    mTitleContainer->mDrawManual = true;
    
    
    //
    
    
    mButtonPlay = new MainMenuButton();
    mButtonLogIn = new MainMenuButton();
    mButtonStore = new MainMenuButton();
    
    mButtonContainer->AddSubview(mButtonPlay);
    mButtonContainer->AddSubview(mButtonLogIn);
    mButtonContainer->AddSubview(mButtonStore);
    
    mButtonPlay->SetSprites(&(gApp->mTitleButtonPlay[0]), &(gApp->mTitleButtonPlay[1]));
    mButtonPlay->AddLeavesLeft(136.0f);mButtonPlay->AddLeavesRight(136.0f);
    mButtonPlay->AddLetter(&(gApp->mTitleButtonTextPlay[0]), -61.5f, -4.5f);mButtonPlay->AddLetter(&(gApp->mTitleButtonTextPlay[1]), -23.0f, -4.5f);
    mButtonPlay->AddLetter(&(gApp->mTitleButtonTextPlay[2]), 17.5f, -4.5f);mButtonPlay->AddLetter(&(gApp->mTitleButtonTextPlay[3]), 60.5f, -4.5f);
    mButtonPlay->SetCenter(mButtonContainer->mWidth2, mButtonContainer->mHeight2 - 60.0f);
    
    mButtonStore->SetSprites(&(gApp->mTitleButtonStore[0]), &(gApp->mTitleButtonStore[1]));
    mButtonStore->AddLetter(&(gApp->mTitleButtonTextStore[0]), -60.5f, -2.5f);mButtonStore->AddLetter(&(gApp->mTitleButtonTextStore[1]), -37.5f, -2.5f);
    mButtonStore->AddLetter(&(gApp->mTitleButtonTextStore[2]), -12.5f, -2.5f);mButtonStore->AddLetter(&(gApp->mTitleButtonTextStore[3]), 13.0f, -2.5f);
    mButtonStore->SetCenter(mButtonPlay->GetCenterX() + 83.0f, mButtonPlay->GetCenterY() + 100.0f);
    mButtonStore->mLetterBounceScale = 0.5f;
    
    MainMenuButtonGem *aGem = new MainMenuButtonGem();
    aGem->mX = 58.0f;aGem->mY = -5.0f;
    mButtonStore->mGem = aGem;
    
    mButtonLogIn->SetSprites(&(gApp->mTitleButtonLogIn[0]), &(gApp->mTitleButtonLogIn[1]));
    mButtonLogIn->SetCenter(mButtonPlay->GetCenterX() - 106.0f, mButtonPlay->GetCenterY() + 100.0f);
    mButtonLogIn->AddLetter(&(gApp->mTitleButtonTextLogIn[0]), -49.0f, -4.5001f );mButtonLogIn->AddLetter(&(gApp->mTitleButtonTextLogIn[1]), -30.0f, -4.5001f );
    mButtonLogIn->AddLetter(&(gApp->mTitleButtonTextLogIn[2]), -9.0f, -4.5f );mButtonLogIn->AddLetter(&(gApp->mTitleButtonTextLogIn[3]), 8.0f, -4.5f );
    mButtonLogIn->AddLetter(&(gApp->mTitleButtonTextLogIn[1]), 27.0f, -4.4999f );mButtonLogIn->AddLetter(&(gApp->mTitleButtonTextLogIn[4]), 49.0f, -4.5f );
    mButtonLogIn->mLetterBounceScale = 0.5f;
    
    
    
    
    mDidClick = false;
    mDidClickTimer = 0;
    mDidClickActionIndex = 0;
    
    //mTitleTextRotationSin = 0.0f;
    //mTitleTextShiftSin = 0.0f;
    
    mTouch = 0;
    mLastClicked = 0;
    
    float aPitch = 0.8f;
    
    
    
    
    //Big
    mLetterOffsetBaseX[0] = -248.0f;mLetterOffsetBaseY[0] = -2.0f;
    mLetterOffsetBaseX[1] = -190.0f;mLetterOffsetBaseY[1] = 0.0f;
    mLetterOffsetBaseX[2] = -128.0f;mLetterOffsetBaseY[2] = 0.0f;
    //Bone
    mLetterOffsetBaseX[3] = -8.0f;mLetterOffsetBaseY[3] = 0.0f;
    mLetterOffsetBaseX[4] = 82.0f;mLetterOffsetBaseY[4] = 0.0f;
    mLetterOffsetBaseX[5] = 176.0f;mLetterOffsetBaseY[5] = 2.0f;
    mLetterOffsetBaseX[6] = 256.0f;mLetterOffsetBaseY[6] = 2.0f;
    
    aPitch = 0.8f;
    for(int i=0;i<7;i++)
    {
        MainMenuLetter *aLetter = new MainMenuLetter(&(gApp->mTitleTextLetterRow1[i]));
        aLetter->mSoundPitch = aPitch;
        mLetters+=aLetter;
        aPitch += 0.0725f;
    }
    
    //Treasure
    int aShift = 7;
    mLetterOffsetBaseX[aShift + 0] = -272.0f;mLetterOffsetBaseY[aShift + 0] = 0.0f;
    mLetterOffsetBaseX[aShift + 1] = -224.0f;mLetterOffsetBaseY[aShift + 1] = 2.0f;
    mLetterOffsetBaseX[aShift + 2] = -180.0f;mLetterOffsetBaseY[aShift + 2] = 2.0f;
    mLetterOffsetBaseX[aShift + 3] = -134.0f;mLetterOffsetBaseY[aShift + 3] = 2.0f;
    mLetterOffsetBaseX[aShift + 4] = -84.0f;mLetterOffsetBaseY[aShift + 4] = 0.0f;
    mLetterOffsetBaseX[aShift + 5] = -36.0f;mLetterOffsetBaseY[aShift + 5] = 2.0f;
    mLetterOffsetBaseX[aShift + 6] = 14.0f;mLetterOffsetBaseY[aShift + 6] = 4.0f;
    mLetterOffsetBaseX[aShift + 7] = 56.0f;mLetterOffsetBaseY[aShift + 7] = 2.0f;
    //Hunt
    mLetterOffsetBaseX[aShift + 8] = 126.0f;mLetterOffsetBaseY[aShift + 8] = 0.0f;
    mLetterOffsetBaseX[aShift + 9] = 176.0f;mLetterOffsetBaseY[aShift + 9] = 0.0f;
    mLetterOffsetBaseX[aShift + 10] = 228.0f;mLetterOffsetBaseY[aShift + 10] = 0.0f;
    mLetterOffsetBaseX[aShift + 11] = 276.0f;mLetterOffsetBaseY[aShift + 11] = 0.0f;
    
    
    mStego = new HeroStego();
    mStego->mX = mWidth2;
    mStego->mY = mHeight2;
    
    aPitch = 0.8f;
    for(int i=0;i<12;i++)
    {
        MainMenuLetterRow2 *aLetter = new MainMenuLetterRow2(&(gApp->mTitleTextLetterRow2[i]));
        aLetter->mSoundPitch = aPitch;
        mLetters+=aLetter;
        aPitch += 0.0725f;
    }
}

MainMenu::~MainMenu()
{
    FreeList(MainMenuLetter, mLetters);
    FreeList(MainMenuSceneItem, mSceneItemListBottom);
    FreeList(MainMenuSceneItem, mSceneItemListMiddle);
    FreeList(MainMenuSceneItem, mSceneItemListTop);
}

void MainMenu::PositionContent()
{
    SetFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    
    float aScaleTitle = 1.0f;
    float aScaleButtons = 1.0f;
    
    mTopInterfaceFrame.mHeight = (mHeight * 0.56f);
    mTopInterfaceFrame.mWidth = (mWidth);
    
    if((mWidth > 5.0f) && (mHeight > 5.0f))
    {
        float aMinScaleFactor = 0.78f;
        float aMaxScaleFactor = 1.36f;
        
        float aFactor = (mWidth / mHeight);
        
        if(aFactor > aMinScaleFactor)
        {
            float aPercent = (aFactor - aMinScaleFactor) / (aMaxScaleFactor - aMinScaleFactor);
            
            if(aPercent > 1.0f)
            {
                aPercent = 1.0f;
            }
            
            mTopInterfaceFrame.mHeight += (mHeight * 0.40f * aPercent);
            
        }
    }
    
    
    if(mTopInterfaceFrame.mWidth < 160.0f)mTopInterfaceFrame.mWidth = 160.0f;
    if(mTopInterfaceFrame.mHeight < 160.0f)mTopInterfaceFrame.mHeight = 160.0f;
    
    
    
    
    if((mHeight * 0.5f) > mTopInterfaceFrame.mHeight)mTopInterfaceFrame.mY = 4.0f + ((mHeight * 0.25f) - (mTopInterfaceFrame.mHeight * 0.5f));
    else mTopInterfaceFrame.mY = 4.0f;
    mTopInterfaceFrame.mX = mWidth2 - mTopInterfaceFrame.mWidth * 0.5f;
    
    //float aFitHeight = ;
    FRect aFitRect = mTopInterfaceFrame;
    aFitRect.mHeight = mTopInterfaceFrame.mHeight * 0.5f;
    
    mTopInterfaceTitleFrame = FRect::FitAspectFit(aFitRect, mTitleContainer->mWidth, mTitleContainer->mHeight, 8.0f, aScaleTitle);
    
    
    //aFitRect.mHeight = mTopInterfaceFrame.mHeight * 0.5f;
    mTopInterfaceButtonFrame = FRect::FitAspectFit(aFitRect, mButtonContainer->mWidth, mButtonContainer->mHeight, 0.0f, aScaleButtons);
    
    float aTopSpacingTotal = mTopInterfaceFrame.mHeight - (mTopInterfaceTitleFrame.mHeight + mTopInterfaceButtonFrame.mHeight);
    
    float aSpacingV = aTopSpacingTotal * 0.44f;
    
    mTopInterfaceTitleFrame.mX = mTopInterfaceFrame.mX + mTopInterfaceFrame.mWidth / 2.0f - mTopInterfaceTitleFrame.mWidth / 2.0f;
    mTopInterfaceTitleFrame.mY = mTopInterfaceFrame.mY + aSpacingV;
    
    
    mTopInterfaceButtonFrame.mX = mTopInterfaceFrame.mX + mTopInterfaceFrame.mWidth / 2.0f - mTopInterfaceButtonFrame.mWidth / 2.0f;
    mTopInterfaceButtonFrame.mY = mTopInterfaceTitleFrame.mY + mTopInterfaceTitleFrame.mHeight;// + aSpacingV;
    
    mTitleContainer->SetTransformScale(aScaleTitle);
    mTitleContainer->SetCenter(mTopInterfaceTitleFrame.CenterX(), mTopInterfaceTitleFrame.CenterY());
    
    mButtonContainer->SetTransformScale(aScaleButtons);
    mButtonContainer->SetCenter(mTopInterfaceButtonFrame.CenterX(), mTopInterfaceButtonFrame.CenterY());
    
    
    
    
    
    
    float aCenterX = mTitleContainer->mWidth2;
    float aCenterY = mTitleContainer->mHeight2;
    
    int aIndex = 0;
    
    EnumList(MainMenuLetter, aLetter, mLetters)
    {
        float aX = aCenterX + (mLetterOffsetBaseX[aIndex] * 1.0f);
        float aY = aCenterY + (mLetterOffsetBaseY[aIndex] * 1.0f) - 40.0f;
        
        if(aIndex >= 7)aY += 90.0f;
        
        aLetter->mX = aX;
        aLetter->mY = aY;
        
        aIndex++;
    }
    
    float aSandInset = 10.0f;
    
    mFloorScale = gApp->mTitleFloorDirt.ScaleFitH(mWidth, -aSandInset * 2.0f);
    mFloorWidth = gApp->mTitleFloorDirt.mWidth * mFloorScale;
    mFloorHeight = gApp->mTitleFloorDirt.mHeight * mFloorScale;
    
    mFloorX = (-aSandInset);
    mFloorY = mHeight - (mFloorHeight * 0.90f);
    
    mFloorCenterX = mFloorX + mFloorWidth / 2.0f;
    mFloorCenterY = mFloorY + mFloorHeight / 2.0f;
    
    EnumList(MainMenuSceneItem, aItem, mSceneItemListBottom)aItem->Place(mFloorCenterX, mFloorCenterY, mFloorScale);
    EnumList(MainMenuSceneItem, aItem, mSceneItemListMiddle)aItem->Place(mFloorCenterX, mFloorCenterY, mFloorScale);
    EnumList(MainMenuSceneItem, aItem, mSceneItemListTop)aItem->Place(mFloorCenterX, mFloorCenterY, mFloorScale);
    
    if(mStego)
    {
        mStego->mScale = mFloorScale;
        mStego->mX = mFloorCenterX - 147.0f * mFloorScale;
        mStego->mY = mFloorCenterY - 32.0f * mFloorScale;
    }
    
    
    if(mSun)
    {
        mSun->mX = mWidth * 0.125f;
        mSun->mY = mHeight * 0.03f;
        mSun->mScale = mFloorScale;
        
        float aSunHeight = mFloorScale * 300.0f;
        float aMinY = (aSunHeight * 0.25f);
        
        if(mSun->mY <= aMinY)mSun->mY = aMinY;
        
    }
}

void MainMenu::Update()
{
    if(mStego)mStego->Update();
    if(mSun)mSun->Update();
    
    /*
    if(mDidClick)
    {
        mDidClickTimer--;
        if(mDidClickTimer <= 0)
        {
            if(mDidClickActionIndex == 0)
            {
                if(gApp->TransitionInProgress() == false)
                {
                    gApp->TransitionTo(new Game(0), 0, new Transition());
                }
            }
            else if(mDidClickActionIndex == 1)
            {
                if(gApp->TransitionInProgress() == false)
                {
                    gApp->TransitionTo(new MapScreen(), 0, new Transition());
                }
            }
        }
    }
    */
    
    EnumList(MainMenuLetter, aLetter, mLetters)aLetter->Update();
    EnumList(MainMenuSceneItem, aItem, mSceneItemListBottom)aItem->Update();
    EnumList(MainMenuSceneItem, aItem, mSceneItemListMiddle)aItem->Update();
    EnumList(MainMenuSceneItem, aItem, mSceneItemListTop)aItem->Update();
}

void MainMenu::Draw()
{
    Graphics::SetColor();
    Graphics::DisableColorArray();
    
    gApp->mTitleBackgroundSky.DrawQuadRectOffset(0.0f, 0.0f, mWidth, mHeight, 2.0f);
    if(mSun)mSun->Draw();
    
    EnumList(MainMenuSceneItem, aItem, mSceneItemListBottom)aItem->Draw();
    
    gApp->mTitleFloorDirt.DrawQuad(mFloorX, mFloorY, mFloorX + mFloorWidth, mFloorY + mFloorHeight);
    
    EnumList(MainMenuSceneItem, aItem, mSceneItemListMiddle)aItem->Draw();
    EnumList(MainMenuSceneItem, aItem, mSceneItemListTop)aItem->Draw();
    
    
    if(mStego)
    {
        Graphics::SetColor();
        gApp->mHeroStegoShadow.Draw(mStego->mX + mStego->mScale * 22.0f, mStego->mY + (110.0f * mStego->mScale), mStego->mScale, 0.0f);
        mStego->Draw();
    }
    
    Graphics::SetColor();
    mTitleContainer->DrawManual();
    EnumList(MainMenuLetter, aLetter, mLetters)aLetter->Draw();
    
    Graphics::SetColor();
    mButtonContainer->DrawManual();
    
    if(gApp->mPopoverFade > 0)
    {
        Graphics::SetColor(0.0f, 0.0f, 0.0f, gApp->mPopoverFade * 0.6f);
        Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
        Graphics::SetColor();
    }
    
    if(mButtonContainer)
    {
        
    }
    
    
    DrawTransform();
}

void MainMenu::TouchDown(float pX, float pY, void *pData)
{
    mTouch = pData;
    
    MainMenuLetter *aClosest = 0;
    float aBestDist = (50.0f);
    if(gIsLargeScreen)aBestDist *= 2.0f;
    aBestDist = (aBestDist * aBestDist);
    
    float aLetterTouchX = pX;
    float aLetterTouchY = pY;
    ConvertPoint(aLetterTouchX, aLetterTouchY, this, mTitleContainer);
    
    EnumList(MainMenuLetter, aLetter, mLetters)
    {
        float aX = aLetter->mX;
        float aY = aLetter->mY;
        float aDiffX = aX - aLetterTouchX;
        float aDiffY = aY - aLetterTouchY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aDist < aBestDist)
        {
            aBestDist = aDist;
            aClosest = aLetter;
        }
    }
    
    if(aClosest)
    {
        mLastClicked = aClosest;
        aClosest->Bounce();
    }
    else mLastClicked = 0;
    
    TouchMove(pX, pY, pData);
}

void MainMenu::TouchUp(float pX, float pY, void *pData)
{
    if(mTouch == pData)mTouch = 0;
}

void MainMenu::TouchMove(float pX, float pY, void *pData)
{
    if(pData == mTouch)
    {
        MainMenuLetter *aClosest = 0;
        
        float aBestDist = (50.0f);
        if(gIsLargeScreen)aBestDist *= 2.0f;
        aBestDist = (aBestDist * aBestDist);
        
        float aLetterTouchX = pX;
        float aLetterTouchY = pY;
        ConvertPoint(aLetterTouchX, aLetterTouchY, this, mTitleContainer);
        
        EnumList(MainMenuLetter, aLetter, mLetters)
        {
            float aX = aLetter->mX;
            float aY = aLetter->mY;
            float aDiffX = aX - aLetterTouchX;
            float aDiffY = aY - aLetterTouchY;
            float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if(aDist < aBestDist)
            {
                aBestDist = aDist;
                aClosest = aLetter;
            }
        }
        
        if(aClosest)
        {
            if(aClosest != mLastClicked)
            {
                mLastClicked = aClosest;
                aClosest->Bounce();
            }
        }
        else
        {
            mLastClicked = 0;
        }
    }
}


void MainMenu::TouchFlush()
{
    mTouch = 0;
}

void MainMenu::Notify(void *pSender)
{
    
    if((mDidClick == false) && (gApp->mTransition == 0))
    {
        if(pSender == mButtonPlay)
        {
            if(gApp->TransitionInProgress() == false)
            {
                gApp->TransitionTo(new Game(0), 0, new Transition());
            }
            
            //mDidClick = true;
            //mDidClickTimer = 6;
            //mDidClickActionIndex = 0;
        }
        
    }
    
    if(pSender == &mButtonStore)
    {
        
    }
    
    //gApp->PopupStoreMenu();
    
}

MainMenuSun::MainMenuSun()
{
    mX = 0.0f;
    mY = 0.0f;
    
    mScale = 1.0f;
    
    mSin[0] = 0.0f;
    mSin[1] = 120.0f;
    mSin[2] = 220.0f;
    mSin[3] = 40.0f;
    
    
    mSinSpeed[0] = 4.0f;
    mSinSpeed[1] = 6.0f;
    mSinSpeed[2] = 1.25f;
    mSinSpeed[3] = 0.85f;
    
    
    
    
    mRot[0] = 150.0f;
    mRot[1] = 90.0f;
    mRot[2] = 300.0f;
    mRot[3] = 230.0f;
    
    mRotSpeed[0] = 0.085f;
    mRotSpeed[1] = -0.0325f;
    mRotSpeed[2] = 0.0225f;
    mRotSpeed[3] = -0.0425f;
    
}

MainMenuSun::~MainMenuSun()
{
    
}

void MainMenuSun::Update()
{
    for(int i=0;i<4;i++)
    {
        mSin[i] += mSinSpeed[i];
        if(mSin[i] >= 360.0f)mSin[i] -= 360.0f;
        
        mRot[i] += mRotSpeed[i];
        if(mRot[i] >= 360.0f)mRot[i] -= 360.0f;
        if(mRot[i] < 0.0f)mRot[i] += 360.0f;
        
    }
    
}

void MainMenuSun::Draw()
{
    Graphics::SetColor(0.8f);
    Graphics::BlendSetAdditive();
    
    
    gApp->mTitleSun.Draw(mX, mY, mScale * (0.96f + Sin(mSin[3]) * 0.025f), mRot[2] + Sin(mSin[0]) * 1.4f);
    
    Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.5f);
    gApp->mEffectLightSpinnerLarge[2].Draw(mX, mY, mScale * (1.17f + Sin(mSin[2]) * 0.025f), -Cos(mSin[0]) * 0.6f);
    
    Graphics::SetColor(1.0f, 0.5f, 0.0f, 0.6f);
    gApp->mEffectLightSpinnerLarge[1].Draw(mX, mY, mScale * (1.05f + Sin(mSin[0]) * 0.03f), mRot[0] + Sin(mSin[1]) * 1.0f);
    
    //Graphics::SetColor(1.0f, 0.8f, 0.65f, 0.6f);
    gApp->mEffectLightSpinnerLarge[0].Draw(mX, mY, mScale * (1.30f + Sin(mSin[3]) * 0.04f), mRot[1]);
    
    //gApp->mTitleSunMiddle.Draw(mX, mY, mScale * 1.2f, 0.0f);
    
    
    //Graphics::SetColor(0.8f);
    //Graphics::BlendSetAlpha();
    //gApp->mTitleSunMiddle.Draw(mX, mY, mScale, 0.0f);
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
}