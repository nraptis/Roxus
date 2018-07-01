//#include "app_global.h"
#include "core_includes.h"
#include "FView.h"
#include "FButton.h"
#include "FApp.h"
#include "FViewAnimation.h"

FView::FView()
{
    mClipsContent = false;
    mConsumesTouches = true;
    mRecievesOutsideTouches = false;
    mRecievesConsumedTouches = false;
    
    mViewType = VIEW_TYPE_VIEW;
    
    mEnabled = true;
    mHidden = false;
    
    mListenerView = 0;
    
    mDrawManual = false;
    
    mDragFrameMode = false;
    
    mTouchDownInside = false;
    mMouseOver = false;
    mTouchDown = false;
    mTouchCount = 0;
    mTouchCanceled = false;
    
    mNotifyParent = false;
    
    mViewID = VIEW_TYPE_VIEW;
    
    mName = "View";
    mParent = 0;
    mParentRetain = false;
    
    mColor.mRed = 1.0f;
    mColor.mGreen = 1.0f;
    mColor.mBlue = 1.0f;
    mColor.mAlpha = 0.0f;
    
    mTouchX = 0.0f;
    mTouchY = 0.0f;
    
    mController = 0;
    mContainer = new FViewContainer(this);
    
    SetFrame(0.0f, 0.0f, 0.0f, 0.0f);
}

FView::~FView()
{
    if(mController)
    {
        mController->ViewDestroyed(this);
    }
    
    //Log("View Deleted[%s]\n", mName.c());
    //gViewController.ViewDestroyed(this);
}

void FView::BasePositionContent()
{
    PositionContent();
}

void FView::PositionContent()
{
    
}

void FView::BaseUpdate()
{
    Update();
}

void FView::BaseDraw()
{
    //if(mBackgroundSprite)
    //{
    //    mBackgroundSprite->Center(GetCenterX(), GetCenterY());
    //}
    
    Draw();
    
}

void FView::Update() {
    
}

void FView::Draw() {
    if (mColor.mAlpha != 0.0f) {
        Graphics::SetColor(mColor);
        Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
        Graphics::SetColor();
        
    }
    
    //Graphics::SetColor(0.0f, 0.0f, 0.0f);
    //Graphics::OutlineRect(mTouchX - 10.0f, mTouchY - 10.0f, 21.0f, 21.0f, 6.0f);
    
    /*
    
    if(mTouchDownInside)Graphics::SetColor(mColor.mRed, mColor.mGreen, mColor.mBlue, 0.75f);
    else if(mTouchDown)Graphics::SetColor(mColor.mRed, mColor.mGreen, mColor.mBlue, 0.5f);
    else Graphics::SetColor(mColor.mRed, mColor.mGreen, mColor.mBlue, 0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);

    Graphics::SetColor(mColor.mRed, mColor.mGreen, mColor.mBlue);
    Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 3.0f);

    Graphics::SetColor(0.0f, 0.0f, 0.0f);
    Graphics::OutlineRect(mTouchX - 10.0f, mTouchY - 10.0f, 21.0f, 21.0f, 6.0f);

    Graphics::SetColor();
    */
    
    
    /*
    if(mName == "cont")
    {
        Graphics::SetColor(0.15f, 0.0f, 0.875f, 0.75f);
        Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 7.22f);
        
        //Graphics::SetColor();
        //Graphics::OutlineRect(mTouchX - 10.0f, mTouchY - 10.0f, 21.0f, 21.0f, 6.0f);
        
        Graphics::SetColor();
    }
    
    else if(mName == "pc")
    {
        Graphics::SetColor(0.15f, 0.85f, 0.05f, 0.66);
        Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 8.9f);
        
        //Graphics::SetColor();
        //Graphics::OutlineRect(mTouchX - 10.0f, mTouchY - 10.0f, 21.0f, 21.0f, 6.0f);
        
        Graphics::SetColor();
    }
    */

    /*
    Graphics::ClipDisable();
    Graphics::ResetMatrixModelView();
    Graphics::ResetMatrixProjection();

    FMatrix aProj = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -1024.0f, 1024.0f);
    Graphics::SetMatrix(aProj);

    for (int i=0;i<4;i++) {
        Graphics::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 20.0f);
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(mContainer->mTransformAbsolute.mCornerX[i], mContainer->mTransformAbsolute.mCornerY[i], 14.0f);
    }

    Graphics::SetColor(1.0f, 1.0f, 0.5f, 0.75f);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[0], mContainer->mTransformAbsolute.mCornerY[0],
                       mContainer->mTransformAbsolute.mCornerX[1], mContainer->mTransformAbsolute.mCornerY[1], 6.0);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[1], mContainer->mTransformAbsolute.mCornerY[1],
                       mContainer->mTransformAbsolute.mCornerX[2], mContainer->mTransformAbsolute.mCornerY[2], 6.0);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[2], mContainer->mTransformAbsolute.mCornerY[2],
                       mContainer->mTransformAbsolute.mCornerX[3], mContainer->mTransformAbsolute.mCornerY[3], 6.0);
    Graphics::DrawLine(mContainer->mTransformAbsolute.mCornerX[3], mContainer->mTransformAbsolute.mCornerY[3],
                       mContainer->mTransformAbsolute.mCornerX[0], mContainer->mTransformAbsolute.mCornerY[0], 6.0);
    */

}

void FView::DrawManual()
{
    //GetContainer()->Draw(0);
    GetContainer()->Draw();
}

void FView::DrawManualBegin()
{
    GetContainer()->DrawManualBegin();
}

void FView::DrawManualEnd() {
    GetContainer()->DrawManualEnd();
}

void FView::DrawManualSubviews() {
    GetContainer()->DrawManualSubviews();
}

void FView::DrawBorders() {
    Graphics::OutlineRect(1.0f, 1.0f, mWidth - 2.0f, mHeight - 2.0f, 1.0f);
}

void FView::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData) {
    mTouchX = pX;
    mTouchY = pY;
    if (mController == &(gAppBase->mViewController)) {
        Log("BaseTouchDown[%s]\n", mName.c());
    }

    TouchDown(pX, pY, pData);
}

void FView::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData)
{
    mTouchX = pX;
    mTouchY = pY;
    
    TouchMove(pX, pY, pData);
}

void FView::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData)
{
    mTouchX = pX;
    mTouchY = pY;
    
    TouchUp(pX, pY, pData);
}

void FView::BaseTouchFlush()
{
    TouchFlush();
}



/*
FViewContainer *FView::GetContainer()
{
    //if(mContainer == 0)
    //{
    //    mContainer = new FViewContainer(this);
    //}
    
    return mContainer;
}
*/

void FView::TouchDown(float pX, float pY, void *pData)
{
    
}

void FView::TouchMove(float pX, float pY, void *pData)
{
    
}

void FView::TouchUp(float pX, float pY, void *pData)
{
    
}

void FView::TouchFlush()
{
    
}

void FView::MouseWheel(int pDirection)
{

}

void FView::KeyDown(int pKey)
{

}

void FView::KeyUp(int pKey)
{

}

void FView::Notify(void *pSender)
{
    if((mNotifyParent == true) && (mParent != 0))
    {
        mParent->Notify(pSender);
    }
    
    if(mListenerView)
    {
        mListenerView->Notify(pSender);
    }
    
}

void FView::Notify(void *pSender, int pID, void *pObject)
{
    if((mNotifyParent == true) && (mParent != 0))
    {
        mParent->Notify(pSender, pID, pObject);
    }
    
    if(mListenerView)
    {
        mListenerView->Notify(pSender, pID, pObject);
    }
}

bool FView::ShouldReceieveTouch(FView *pTopView, bool pInside)
{
    bool aResult = true;
    
    if(pTopView)
    {
        
        //Log("[%s] Base => [%s] Should Receive Touch[%d] = (%d)\n", mName.c(), pTopView->mName.c(), pInside, aResult);
        
    }
    
    return aResult;
}

void FView::DrawTransform()
{
    GetContainer()->DrawTransform();
}

/*
void FView::AddSubview(FView *pView, int pZIndex)
{
    //if(mSubviews.Exists(pView) == false)mSubviews.Add(pView);
    gViewController.ViewAddToParent(pView, this, pZIndex, false, false, false);
    
    if(pView)
    {
        if(pView->IsModalView())
        {
            
        }
    }
}

void FView::AddSubview(FView &pView, int pZIndex)
{
    //if(mSubviews.Exists(&pView) == false)mSubviews.Add(&pView);
    gViewController.ViewAddToParent(&pView, this, pZIndex, true, false, false);
}
*/

void FView::AddSubview(FView *pView)
{
    pView->mParentRetain = false;
    
    if(mController)
    {
        mController->ViewAddToParent(pView, this, false, false);
    }
    else
    {
        pView->mParent = this;
        pView->GetContainer()->mParent = GetContainer();
        if(mSubviews.Exists(pView) == false)mSubviews.Add(pView);
        pView->GetContainer()->mRefresh = true;
        GetContainer()->mRefresh = true;
    }
}

void FView::AddSubview(FView &pView)
{
    pView.mParentRetain = true;
    
    if(mController)
    {
        mController->ViewAddToParent(&pView, this, true, false);
    }
    else
    {
        pView.mParent = this;
        pView.GetContainer()->mParent = GetContainer();
        if(mSubviews.Exists((&pView)) == false)mSubviews.Add((&pView));
        pView.GetContainer()->mRefresh = true;
        GetContainer()->mRefresh = true;
    }
}

/*
void FView::AddModalChild(FView *pView, int pZIndex)
{
    if(pView)
    {
        gViewController.ViewAddToParent(pView, this, pZIndex, false, false, true);
    }
}

void FView::AddModalChild(FView &pView, int pZIndex)
{
    if(&pView)
    {
        gViewController.ViewAddToParent(&pView, this, pZIndex, true, false, true);
    }
}


void FView::AddModalChild(FView *pView)
{
    if((pView != 0) && (mController != 0))
    {
        mController->ViewAddToParent(pView, this, false, true);
    }
}

void FView::AddModalChild(FView &pView)
{
    if((&pView != 0) && (mController != 0))
    {
        mController->ViewAddToParent(&pView, this, true, true);
    }
}
 */

void FView::RemoveFromParent()
{
    if(mController != 0)
    {
        mController->RemoveViewFromParent(this);
    }
    //gViewController.RemoveViewFromParent(this);
    //mParent = 0;
}

void FView::BringSubviewToFront(FView *pView)
{
   // gViewController.BringSubviewToFront(pView);
    mSubviews.MoveToLast(pView);
}


void FView::SendSubviewToBack(FView *pView)
{
    //gViewController.SendSubviewToBack(pView);
    mSubviews.MoveToFirst(pView);
}

void FView::SendSubviewBackward(FView *pView)
{
	mSubviews.MoveObjectUp(pView);
}

void FView::BringSubviewForward(FView *pView)
{
	mSubviews.MoveObjectDown(pView);
}


bool FView::ContainsPoint(float pX, float pY)
{
    if (mName == "ROTATION-VIEW-2") {
        printf("ROT VIEW:::\n");
    }
    if (GetContainer()->ContainsPoint(pX, pY)) {
    
        printf("HITS: %s\n", mName.c());
        
        return true;
    } else {
        printf("MISSES: %s\n", mName.c());
        
    }
    return false;
}

void FView::Kill()
{
    if(mController)
    {
        mController->ViewKill(this);
    }
    //gViewController.ViewKill(this);
}

void FView::PrintTransform()
{
    Log(mName.c());
    
    Log("\nTRA");
    
    //Log(mName.c());
    
    Log(" - XY[%.2f %.2f] Sc[%.2f %.2f %.2f] R[%.2f] - Fr[%.2f,%.2f,%.2f,%.2f]\n", mTransform.mX, mTransform.mY, mTransform.mScale, mTransform.mScaleX, mTransform.mScaleY, mTransform.mRotation, mX, mY, mWidth, mHeight);
    
    Log("ABS - XY[%.2f %.2f] Sc[%.2f %.2f %.2f] R[%.3f]\n\n", GetAbsoluteTransformX(), GetAbsoluteTransformY(), GetAbsoluteTransformScale(), GetAbsoluteTransformScaleX(), GetAbsoluteTransformScaleY(), GetAbsoluteTransformRotation());
    
    
    
}

void FView::PrintFrame()
{
    FString aName = mName;
    if(aName.mLength <= 0)aName = "View";
    
    printf("%s Frame (%.2f, %.2f, %.2f, %.2f)\n", aName.c(), GetX(), GetY(), GetWidth(), GetHeight());
}

void FView::PrintAllChildrenTransforms()
{
    
    FList aStack;
    FList aTemp;
    
    
    printf("-----%s-----\n", mName.c());
    
    aStack.Add(this);
    
    while(aStack.mCount > 0)
    {
        EnumList(FView, aView, aStack)
        {
            
            EnumList(FView, aSubview, aView->mSubviews)
            {
                aTemp.Add(aSubview);
            }
            aView->PrintTransform();
            
        }
        
        aStack.Clear();
        
        EnumList(FView, aView, aTemp)
        {
            aStack.Add(aView);
        }
        
        aTemp.Clear();
    }
    
    printf("-----------------\n");
    
}

void FView::SetTransformTranslate(float pX, float pY)
{
    SetTransformX(pX);
    SetTransformY(pY);
}

void FView::SetTransformX(float pX)
{
    GetContainer()->SetTransformX(pX);
    mTransform.mX = pX;
}

void FView::SetTransformY(float pY)
{
    GetContainer()->SetTransformY(pY);
    mTransform.mY = pY;
}

void FView::SetTransformScale(float pScale)
{
    GetContainer()->SetTransformScale(pScale);
    mTransform.mScale = pScale;
}

void FView::SetTransformScale(float pScaleX, float pScaleY)
{
    SetTransformScaleX(pScaleX);
    SetTransformScaleY(pScaleY);
}

void FView::SetTransformScaleX(float pScaleX)
{
    GetContainer()->SetTransformScaleX(pScaleX);
    mTransform.mScaleX = pScaleX;
}

void FView::SetTransformScaleY(float pScaleY)
{
    GetContainer()->SetTransformScaleY(pScaleY);
    mTransform.mScaleY = pScaleY;
}

void FView::SetTransformRotation(float pRotation)
{
    GetContainer()->SetTransformRotation(pRotation);
    mTransform.mRotation = pRotation;
}

void FView::SetTransformAnchorX(float pAnchorX)
{
    GetContainer()->SetTransformAnchorX(pAnchorX);
    mTransform.mAnchorX = pAnchorX;
}

void FView::SetTransformAnchorY(float pAnchorY)
{
    GetContainer()->SetTransformAnchorY(pAnchorY);
    mTransform.mAnchorY = pAnchorY;
}

void FView::SetTransformAnchor(float pAnchorX, float pAnchorY)
{
    SetTransformAnchorX(pAnchorX);
    SetTransformAnchorY(pAnchorY);
}

void FView::SetX(float pX)
{
    pX = ((int)pX);
    
    GetContainer()->SetFrameX(pX);
    mX = pX;
    //mX = pX;
}

void FView::SetY(float pY)
{
    pY = ((int)pY);
    
    GetContainer()->SetFrameY(pY);
    mY = pY;
}

void FView::SetWidth(float pWidth)
{
    pWidth = (int)(pWidth + 0.5f);
    
    GetContainer()->SetFrameWidth(pWidth);
    mWidth = pWidth;
    mWidth2 = (mWidth / 2.0f);
    //mWidth = pWidth;
}

void FView::SetHeight(float pHeight)
{
    pHeight = (int)(pHeight + 0.5f);
    
    GetContainer()->SetFrameHeight(pHeight);
    mHeight = pHeight;
    mHeight2 = (mHeight / 2.0f);
    //mHeight = pHeight;
}

void FView::SetStaticTransform(bool pIsStatic)
{
    GetContainer()->SetStaticTransform(pIsStatic);
}
//mStaticTransform

//void FView::SetZIndex(int pZIndex)
//{
//    GetContainer()->SetZIndex(pZIndex);
//}

//int FView::GetZIndex()
//{
//    return GetContainer()->mZIndex;
//}

void FView::SizeToFitChildren()
{
    SizeToFitChildren(0.0f, 0.0f);
}

void FView::SizeToFitChildren(float pPaddingLeft, float pPaddingRight)
{
    SizeToFitChildren(pPaddingLeft, pPaddingRight, 0.0f, 0.0f);
}

void FView::SizeToFitChildren(float pPaddingLeft, float pPaddingRight, float pPaddingTop, float pPaddingBottom)
{
    
    float aLeft = 0.0f;
    float aRight = 0.0f;
    float aTop = 0.0f;
    float aBottom = 0.0f;
    if(mSubviews.mCount > 0.0f) {
        EnumList(FView, aView, mSubviews) {
            float aCheckLeft = aView->GetX();
            float aCheckRight = aView->GetX() + aView->GetWidth();
            float aCheckTop = aView->GetY();
            float aCheckBottom = aView->GetY() + aView->GetHeight();
            
            if(aCheckLeft < aLeft)aLeft = aCheckLeft;
            if(aCheckRight > aRight)aRight = aCheckRight;
            if(aCheckTop < aTop)aTop = aCheckTop;
            if(aCheckBottom > aBottom)aBottom = aCheckBottom;
            
        }
        
        float aWidth = (aRight - aLeft) + (pPaddingLeft + pPaddingRight);
        float aHeight = (aBottom - aTop) + (pPaddingBottom + pPaddingTop);
        
        SetFrame(aLeft - pPaddingLeft, aTop - pPaddingTop, aWidth, aHeight);
    }
}

/*
bool FView::ModalViewExists()
{
    return ModalViewCount() > 0;
}

int FView::ModalViewCount()
{
    int aResult = 0;
    
    EnumList(FView, aView, mSubviews)
    {
        if((aView->GetContainer()->mKill == 0) && (aView->GetContainer()->mModal == true))
        {
            aResult++;
        }
    }
    
    return aResult;
}

FView *FView::ModalViewGetNext()
{
    return ModalViewGetNextExcluding(0);
}

FView *FView::ModalViewGetNextExcluding(FView *pExclude)
{
    FView *aResult = 0;
    
    EnumListReverse(FView, aView, mSubviews)
    {
        if((aView->GetContainer()->mKill == 0) && (aView->GetContainer()->mModal == true) && (aResult == 0) && (aView != pExclude))
        {
            aResult = aView;
        }
    }
    
    return aResult;
}
*/

void FView::SetFrame(float pX, float pY, float pWidth, float pHeight)
{
    SetX(pX);
    SetY(pY);
    SetWidth(pWidth);
    SetHeight(pHeight);
}

void FView::SetFrameCenter(float pX, float pY)
{
    SetFrame(pX - mWidth / 2.0f, pY - mHeight / 2.0f, mWidth, mHeight);
}

void FView::SetFrameTopLeft(float pX, float pY)
{
    SetFrame(pX, pY, mWidth, mHeight);
}

void FView::SetFrameTopRight(float pX, float pY)
{
    SetFrame(pX - mWidth, pY, mWidth, mHeight);
}

void FView::SetFrameBottomLeft(float pX, float pY)
{
    SetFrame(pX, pY - mHeight, mWidth, mHeight);
}

void FView::SetFrameBottomRight(float pX, float pY)
{
    SetFrame(pX - mWidth, pY - mHeight, mWidth, mHeight);
}

void FView::SetCenter(float pCenterX, float pCenterY)
{
    SetFrame(pCenterX - mWidth2 * mTransform.mScale * mTransform.mScaleX, pCenterY - mHeight2 * mTransform.mScale * mTransform.mScaleY, mWidth, mHeight);
}

void FView::SetCenter()
{
    if(mParent)
    {
        SetCenter(mParent->GetWidth2(), mParent->GetHeight2());
    }
    else
    {
        if(mController)
        {
            SetCenter(mController->mRoot.GetWidth2(), mController->mRoot.GetHeight2());
        }
    }
}

float FView::GetAbsoluteTransformX()
{
    return GetContainer()->mTransformAbsolute.mX;
}

float FView::GetAbsoluteTransformY()
{
    return GetContainer()->mTransformAbsolute.mY;
}

float FView::GetAbsoluteTransformScale()
{
    return GetContainer()->mTransformAbsolute.mScale;
}

float FView::GetAbsoluteTransformScaleX()
{
    return GetContainer()->mTransformAbsolute.mScaleX;
}

float FView::GetAbsoluteTransformScaleY()
{
    return GetContainer()->mTransformAbsolute.mScaleY;
}

float FView::GetAbsoluteTransformRotation()
{
    return GetContainer()->mTransformAbsolute.mRotation;
}

FVec2 FView::Convert(float pX, float pY, FView *pFromView, FView *pToView)
{
    FVec2 aResult;
    aResult.mX = pX;
    aResult.mY = pY;
    
    ConvertPoint(aResult.mX, aResult.mY, pFromView, pToView);
    
    return aResult;
}

void FView::ConvertPoint(float &pX, float &pY, FView *pFromView, FView *pToView) {
    if(pFromView)
    {
        pFromView->GetContainer()->mTransformAbsolute.Untransform(pX, pY, pFromView->GetWidth(), pFromView->GetHeight());
    }
    
    if(pToView)
    {
        pToView->GetContainer()->mTransformAbsolute.Transform(pX, pY, pToView->GetWidth(), pToView->GetHeight());
    }
}

float FView::ConvertScale(float pScale, FView *pFromView, FView *pToView) {
    float aResult = pScale;
    if(pFromView)aResult /= pFromView->GetContainer()->mTransformAbsolute.mScale;
    if(pToView)aResult *= pToView->GetContainer()->mTransformAbsolute.mScale;
    return aResult;
}

float FView::ConvertRotation(float pDegrees, FView *pFromView, FView *pToView) {
    float aResult = pDegrees;
    if(pFromView)aResult -= pFromView->GetContainer()->mTransformAbsolute.mRotation;
    if(pToView)aResult += pToView->GetContainer()->mTransformAbsolute.mRotation;
    return aResult;
}
