
#include "UNodeEditorMenu.h"
#include "UImagePicker.h"
#include "UNodeEditorMenu.h"
#include "UMainCanvas.h"
#include "UMainToolbar.h"
#include "UMainCanvas.h"
#include "UPathMaker.h"
#include "UNode.h"
#include "FMotionObject.h"

UNodeEditorMenu::UNodeEditorMenu() : UMenu()
{
    mMenuItemWidthSlots = 4;
    SetText("Nodes");
    
    mColorPane = new UNodeEditorColorPane();
    AddLine(mColorPane);
    
    mTransformPane = new UNodeEditorTransformPane();
    AddLine(mTransformPane);
    mTransformPane->Collapse();
    
    
    mSourcePane = new UNodeEditorSourcePane();
    AddLine(mSourcePane);
    mSourcePane->Collapse();
    
    mSelPane = new UNodeEditorSelectionPane();
    AddLine(mSelPane);
    mSelPane->Collapse();
    
    
    
    
    
    
    
    /*
     mRectTest1 = new URectEditorPane(&(gUtils->mSetupRect[0]));
     AddLine(mRectTest1);
     mRectTest1->Collapse();
     
     mRectTest2 = new URectEditorPane(&(gUtils->mSetupRect[1]));
     AddLine(mRectTest2);
     mRectTest2->Collapse();
     
     mRectTest3 = new URectEditorPane(&(gUtils->mSetupRect[2]));
     AddLine(mRectTest3);
     mRectTest3->Collapse();
     */
    
    //FVec2 aBestPlace = gUtils->GoodMenuPlacement(mWidth, mHeight);
    //SetMenuItemFrame(aBestPlace.mX, aBestPlace.mY, mWidth, mHeight);
    LayoutSubviews();
    
}

UNodeEditorMenu::~UNodeEditorMenu()
{
    
}

void UNodeEditorMenu::Notify(void *pSender)
{
    //UMenu::UMenuPane::Notify(pSender);
    
    
    //UMenu                                     Notify(pSender);
    //UMenuPane                                 *mControlPane;
    //USegment                                  *mControlSegmentMode;
    //UButton                                   *mControlButtonCreateNodeSprite;
    //UButton                                   *mControlButtonCreateNodeSpriteSequence;
    //UButton                                   *mControlButtonCreateNodeParticleSource;
    //UButton                                   *mControlButtonCreateNodeColor;
    
    
    
}

void UNodeEditorMenu::SetSelectedNode(UNode *pNode)
{
    
}



UNodeEditorSourcePane::UNodeEditorSourcePane()
{
    SetText("Source");
    SetExpandable(true);
    
    mSegmentType = new USegment(5);
    mSegmentType->SetTitles("[Point]", "[Rect]", "[Circ]", "[Poly]", "[Points]");
    AddLine(mSegmentType);
    
    
    mButtonIsBox = new UButton("[Box]");
    mButtonIsBox->StyleSetCheckBox();
    
    mButtonIsParticleSource = new UButton("[Particle]");
    mButtonIsParticleSource->StyleSetCheckBox();
    
    AddLine(mButtonIsParticleSource, mButtonIsBox, new UMenuItem(), new UMenuItem());
    
    
    
    mButtonEditMotionPath = new UButton("[MOVEM]");
    mButtonEditPoly = new UButton("[POLY]");
    mButtonEditPointCloud = new UButton("[PNT]");
    
    AddLine(new UMenuItem(), mButtonEditMotionPath, mButtonEditPoly, mButtonEditPointCloud);
    
    mSourceWidth = new UExtendedSlider("W:", 18.0f, 800.0f);
    AddLine(mSourceWidth);
    
    mSourceHeight = new UExtendedSlider("H:", 18.0f, 800.0f);
    AddLine(mSourceHeight);
    
    mSourceRadius = new UExtendedSlider("R:", 0.0f, 400.0f);
    AddLine(mSourceRadius);
    
    
}

UNodeEditorSourcePane::~UNodeEditorSourcePane()
{
    
}



void UNodeEditorSourcePane::Notify(void *pSender)
{
    if(pSender == mButtonEditPoly)
    {
        if(gUtilsNode)
        {
            gUtilsNode->mTemplate.SetSpawnSource(SPAWN_SOURCE_POLYGON);
            gUtils->SetSelectedNode();
            gUtils->PathCreate(UTIL_PATH_TYPE_POLY);
        }
        
        
    }
    
    if(pSender == mButtonEditPointCloud)
    {
        if(gUtilsNode)
        {
            gUtilsNode->mTemplate.SetSpawnSource(SPAWN_SOURCE_POINT_CLOUD);
            gUtils->SetSelectedNode();
            gUtils->PathCreate(UTIL_PATH_TYPE_POINT_CLOUD);
        }
        
    }
    
    if(pSender == mButtonEditMotionPath)
    {
        if(gUtilsNode)
        {
            gUtils->SetSelectedNode();
            gUtils->PathCreate(UTIL_PATH_TYPE_MOVEMENT);
        }
    }
    
    if((pSender == mSegmentType) || (pSender == mSourceRadius) || (pSender == mSourceWidth) || (pSender == mSourceHeight))
    {
        if(gUtilsNode)
        {
            gUtilsNode->mTemplate.SetSpawnSource(mSegmentType->mSelectedIndex);
            gUtilsNode->GenerateSelectionReference();
        }
        gUtils->SetSelectedNode();
        
    }
}

void UNodeEditorSourcePane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mSegmentType->SetTarget(&(pNode->mTemplate.mSpawnSourceType));
        mSourceWidth->SetTarget(&(pNode->mTemplate.mSpawnSourceWidth));
        mSourceHeight->SetTarget(&(pNode->mTemplate.mSpawnSourceHeight));
        mSourceRadius->SetTarget(&(pNode->mTemplate.mSpawnSourceRadius));
        
        mButtonIsParticleSource->SetTargetCheck(&(pNode->mParticleSource));
        mButtonIsBox->SetTargetCheck(&(pNode->mColorNode));
    }
    else
    {
        mSegmentType->SetTarget(0);
        mSourceWidth->SetTarget(0);
        mSourceHeight->SetTarget(0);
        mSourceRadius->SetTarget(0);
        
        mButtonIsParticleSource->SetTargetCheck(0);
        mButtonIsBox->SetTargetCheck(0);
    }
}

UNodeEditorColorPane::UNodeEditorColorPane()
{
    SetText("Blending");
    SetExpandable(true);
    
    
    
    mSegmentBlend = new USegment(5);
    mSegmentBlend->SetTitles("B[Norm]", "B[Add]", "B[Pre]", "B[Sub]", "B[G1]", "B[G2]");
    AddLine(mSegmentBlend);
    
    
    
    mColorButtonReset = new UButton("Reset");
    mColorButtonRandom = new UButton("Random");
    mColorButtonInvert = new UButton("Invert");
    mColorButtonRotate = new UButton("Rotate");
    
    AddLine(mColorButtonReset, mColorButtonRandom, mColorButtonReset, mColorButtonInvert, mColorButtonRotate);
    
    
    
    mColorPicker = new UColorPicker();
    mColorPicker->SetText("Base Color");
    AddLine(mColorPicker);
    
}

UNodeEditorColorPane::~UNodeEditorColorPane()
{
    
    
}

void UNodeEditorColorPane::Notify(void *pSender)
{
    if(gUtilsNode)
    {
        float aR = gUtilsNode->mColor.mRed;
        float aG = gUtilsNode->mColor.mGreen;
        float aB = gUtilsNode->mColor.mBlue;
        float aA = gUtilsNode->mColor.mAlpha;
        
        
        
        if(pSender == mColorButtonReset)
        {
            aR = 1.0f; aG = 1.0f; aB = 1.0f; aA = 1.0f;
        }
        if(pSender == mColorButtonRandom)
        {
            aR = gRand.GetFloat(0.0f, 1.0f); aG = gRand.GetFloat(0.0f, 1.0f); aB = gRand.GetFloat(0.0f, 1.0f);
        }
        
        if(pSender == mColorButtonInvert)
        {
            aR = (1.0f - aR);
            aG = (1.0f - aG);
            aB = (1.0f - aB);
            
        }
        
        if(pSender == mColorButtonRotate)
        {
            float aHoldR = aR;
            float aHoldG = aG;
            float aHoldB = aB;
            
            aR = aHoldB;
            aG = aHoldR;
            aB = aHoldG;
        }
        
        gUtilsNode->mColor.mRed = aR;
        gUtilsNode->mColor.mGreen = aG;
        gUtilsNode->mColor.mBlue = aB;
        gUtilsNode->mColor.mAlpha = aA;
        
        
        gUtils->SetSelectedNode();
    }
    
}

void UNodeEditorColorPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mColorPicker->SetColor(&(pNode->mColor));
        mSegmentBlend->SetTarget(&(pNode->mBlendType));
    }
    else
    {
        mColorPicker->SetColor(0);
        mSegmentBlend->SetTarget(0);
    }
}






UNodeEditorTransformPane::UNodeEditorTransformPane()
{
    SetText("Transform");
    SetExpandable(true);
    
    mResetButtonScale = new UButton("Scale");
    
    mResetButtonRotation = new UButton("Rotation");
    
    AddLine(new ULabel("Reset:"), mResetButtonRotation, mResetButtonScale);
    
    mSliderScale = new UExtendedSlider("Scale", 0.2f, 1.6f);
    AddLine(mSliderScale);
    
    mSliderRotation = new UExtendedSlider("Rot", -360.0f, 360.0f);
    AddLine(mSliderRotation);
}

UNodeEditorTransformPane::~UNodeEditorTransformPane()
{
    
}

void UNodeEditorTransformPane::Notify(void *pSender)
{
    if(gUtilsNode)
    {
        if(pSender == mResetButtonScale)
        {
            gUtilsNode->mObject->mScale = 1.0f;
            gUtils->SetSelectedNode();
        }
        
        if(pSender == mResetButtonRotation)
        {
            gUtilsNode->mObject->mRotation = 0.0f;
            gUtils->SetSelectedNode();
        }
    }
}

void UNodeEditorTransformPane::SetSelectedNode(UNode *pNode)
{
    if(pNode)
    {
        mSliderScale->SetTarget(&(pNode->mObject->mScale));
        mSliderRotation->SetTarget(&(pNode->mObject->mRotation));
        
    }
    else
    {
        mSliderScale->SetTarget(0);
        mSliderRotation->SetTarget(0);
        
    }
}




UNodeEditorSelectionPane::UNodeEditorSelectionPane()
{
    SetText("Selection");
    SetExpandable(true);
    
    
    mButtonEditSprite = new UButton("[IMG]");
    mButtonEditSequence = new UButton("[SEQ]");
    mButtonClone = new UButton("Clone!");
    
    AddLine(mButtonEditSprite, mButtonEditSequence, mButtonClone);
    
    
    mButtonSelectNone = new UButton("Sel[ ]");
    mButtonSelectParent = new UButton("Sel[ P ]");
    mButtonSelectNext = new UButton("S[->]");
    mButtonSelectPrev = new UButton("S[<-]");
    AddLine(mButtonSelectNone, mButtonSelectParent, mButtonSelectPrev, mButtonSelectNext);
    
    mButtonSendFront = new UButton("M[First]");
    mButtonSendForward = new UButton("M[Fwd]");
    mButtonSendBackwards = new UButton("M[Bck]");
    mButtonSendBack = new UButton("M[Last]");
    AddLine(mButtonSendBack, mButtonSendBackwards, mButtonSendForward, mButtonSendFront);
}

UNodeEditorSelectionPane::~UNodeEditorSelectionPane()
{
    
}

void UNodeEditorSelectionPane::Notify(void *pSender)
{
    if(pSender == mButtonEditSprite)
    {
        gUtilWS->EditNodeSprite();
    }
    
    if(pSender == mButtonEditSequence)
    {
        gUtilWS->EditNodeSpriteSequence();
    }
    
    if(pSender == mButtonClone)
    {
        gUtilWS->SelectionClone();
    }
    
    
    if(pSender == mButtonSendForward)gUtilWS->SelectionMoveUp();
    if(pSender == mButtonSendBackwards)gUtilWS->SelectionMoveDown();
    
    
    if(pSender == mButtonSendBack)gUtilWS->SelectionMoveBack();
    if(pSender == mButtonSendFront)gUtilWS->SelectionMoveFront();
    
    
    if(pSender == mButtonSelectNext)gUtilWS->SelectionPickNext();
    if(pSender == mButtonSelectPrev)gUtilWS->SelectionPickPrevious();
    
    
}

void UNodeEditorSelectionPane::SetSelectedNode(UNode *pNode)
{
    
}




URectEditorPane::URectEditorPane(URoundedRect *pRect) : UMenuPane()
{
    SetText("Rect");
    SetExpandable(true);
    
    mRect = pRect;
    
    mColorTop = FColor(pRect->mVertex[0].mR, pRect->mVertex[0].mG, pRect->mVertex[0].mB, pRect->mVertex[0].mA);
    mColorBottom = FColor(pRect->mVertex[2].mR, pRect->mVertex[2].mG, pRect->mVertex[2].mB, pRect->mVertex[2].mA);
    
    
    mColorPickerTop = new UColorPicker();
    mColorPickerTop->SetText("Col-Top");
    mColorPickerTop->SetColor(&mColorTop);
    AddLine(mColorPickerTop);
    
    mColorPickerBottom = new UColorPicker();
    mColorPickerBottom->SetText("Col-Bot");
    mColorPickerBottom->SetColor(&mColorBottom);
    AddLine(mColorPickerBottom);
    
    
    mButtonPrint = new UButton("Print!");
    AddLine(mButtonPrint);
    
    
    mSliderCornerRadius = new UExtendedSlider("Corner Radius", 2.0f, 16.0f);
    mSliderCornerRadius->SetTarget(&(pRect->mCornerRadius));
    AddLine(mSliderCornerRadius);
    
    mStepperPoints = new UStepper("Points", 0);
    mStepperPoints->SetTarget(&(pRect->mCornerPointCount));
    AddLine(mStepperPoints);
    
}

URectEditorPane::~URectEditorPane()
{
    
}

void URectEditorPane::Notify(void *pSender)
{
    mRect->SetColorTop(mColorTop);
    mRect->SetColorBottom(mColorBottom);
    
    if(pSender == mButtonPrint)
    {
        Log("mRect.mCornerPointCount = %d;\n", mRect->mCornerPointCount);
        Log("mRect.mCornerRadius = %f;\n", mRect->mCornerRadius);
        Log("mRect.SetColorTop(%.4f, %.4f, %.4f, %.4f);\n", mRect->mVertex[0].mR, mRect->mVertex[0].mG, mRect->mVertex[0].mB, mRect->mVertex[0].mA);
        Log("mRect.SetColorBottom(%.4f, %.4f, %.4f, %.4f);\n", mRect->mVertex[2].mR, mRect->mVertex[2].mG, mRect->mVertex[2].mB, mRect->mVertex[2].mA);
        
        
    }
    
}







