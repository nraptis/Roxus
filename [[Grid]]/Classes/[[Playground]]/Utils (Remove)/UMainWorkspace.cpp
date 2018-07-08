//
//  UMainWorkspace.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "UMainWorkspace.h"
#include "UMainCanvas.h"
#include "UImagePicker.h"
#include "UPathMaker.h"
#include "core_includes.h"
#include "FList.h"
#include "FXML.h"

UMainWorkspace *gUtilWS = 0;

UMainWorkspace::UMainWorkspace()
{
	gUtilWS = this;
	mName = "Util Workspace";

	SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
	SetStaticTransform(true);

	mMode = UTIL_WS_MODE_SELECT_AND_DRAG;
    mModeNext = -1;

	mLinkStartNode = 0;
	mLinkTargetNode = 0;


	mDrawNodes = true;


	mSelectCursorX = gAppWidth2;
	mSelectCursorY = gAppHeight2;



	mDragging = false;
	mDragData = 0;

	mDragImageStartX = 0.0f;
	mDragImageStartY = 0.0f;

	mDragTouchStartX = 0.0f;
	mDragTouchStartY = 0.0f;

	gUtilsNode = 0;

	mDragTransformStartScale = 1.0f;
	mDragTransformStartRotation = 0.0f;


	mWallLeft = 0.0f;
	mWallRight = 1024.0f;
	mWallTop = 30.0f;
	mWallBottom = 500.0f;

}

UMainWorkspace::~UMainWorkspace()
{

}

void UMainWorkspace::Update()
{

	EnumList(FMotionObject, aObject, mMotionObjects)
	{
		aObject->Update();
	}

    if(mModeNext != -1)
    {
        SetMode(mModeNext);
        mModeNext = -1;
    }


	UNode *aScanNode = 0;

	if(mListDelete.mCount > 0)
	{
		if(gUtilsNode)if(mListDelete.Exists(gUtilsNode))gUtilsNode = 0;

		while (mListDelete.mCount > 0)
		{
			aScanNode = (UNode *)(mListDelete.Last());

			EnumList(UNode, aNode, mNodeList)if(aNode->mParent == aScanNode)aNode->mParent = 0;
			EnumList(UNode, aNode, mListAdd)if(aNode->mParent == aScanNode)aNode->mParent = 0;

			mNodeList.Remove(aScanNode);
			mNodeListSelectable.Remove(aScanNode);
			mListAdd.Remove(aScanNode);

			delete aScanNode;
			mListDelete.mCount--;
		}

		SetSelectedNode(gUtilsNode);
	}

	while (mListAdd.mCount > 0)
	{
		aScanNode = (UNode *)(mListAdd.Last());

		mNodeList.Add(aScanNode);

		//if(gUtilsNode == 0)
		//{
			gUtilsNode = aScanNode;
			SetSelectedNode(aScanNode);
		//}

		aScanNode->MotionApply(gUtils->mTimelineTick);

		mListAdd.mCount--;
	}

	EnumList(UNode, aNode, mNodeList)
	{
		aNode->PrepareUpdate();
	}
	EnumList(UNode, aNode, mNodeList)
	{
		aNode->mParentVisited = false;
		aNode->Update(gUtils->mTimelineTick, gUtils->mTimelineTickPrev);
	}
}

void UMainWorkspace::Draw()
{
	FindHeirarchy();

	Graphics::SetColor();

	if(mDrawNodes)
	{

		if(mMode == UTIL_WS_MODE_LINK)
		{
			EnumList(UNode, aNode, mNodeList)
			{
				aNode->mSelectedLink = false;
				aNode->mSelectedLinkTarget = false;
				if(aNode == mLinkStartNode)aNode->mSelectedLink = true;
				if(aNode == mLinkTargetNode)aNode->mSelectedLinkTarget = true;
			}
		}

		//mDragLinkStartNode

		EnumList(UNode, aNode, mNodeList)
		{
			aNode->mSelected = false;
            if(aNode->mIsVisible == true)aNode->Draw(gUtils->mGlobalOpacity);
            if(aNode == gUtilsNode)aNode->mSelected = true;
        }
	}

	Graphics::SetColor();
	Graphics::BlendSetAlpha();

	if((mDrawNodes == true) && (gUtils->mDrawDisableAll == false))
	{
		EnumList(UNode, aNode, mNodeList)
		{
			aNode->DrawOutline(gUtils->mGlobalOpacity);
		}

		if(mMode == UTIL_WS_MODE_LINK)
		{
			EnumList(UNode, aNode, mNodeList)
			{
				aNode->DrawLinkOutline(gUtils->mGlobalOpacity);
			}
		}
	}



	if(gUtils->mDrawDisableAll == false)
	{

		if(mMode == UTIL_WS_MODE_LINK)
		{
			Graphics::SetColor(0.95f, 0.45f, 0.45f);
			Graphics::BlendSetAlpha();

			UNode *aParentNode = 0;
			EnumList(UNode, aNode, mNodeList)
			{
				aParentNode = aNode->mParent;
				if(aParentNode)Graphics::DrawArrow(aNode->GetTouchX(), aNode->GetTouchY(), aParentNode->GetTouchX(), aParentNode->GetTouchY(), 24.0f, 2.0f);
			}
			Graphics::SetColor(0.25f, 0.10f, 0.05f);
			EnumList(UNode, aNode, mNodeList)
			{
				aParentNode = aNode->mParent;
				if(aParentNode)Graphics::DrawArrow(aNode->GetTouchX(), aNode->GetTouchY(), aParentNode->GetTouchX(), aParentNode->GetTouchY(), 22.0f, 1.0f);
			}
		}
	}

	Graphics::SetColor();
	Graphics::BlendSetAlpha();

	if(mMode == UTIL_WS_MODE_SET_CURSOR)
	{
		Graphics::SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		Graphics::DrawRect(mSelectCursorX - 2, mSelectCursorY - 8, 5.0f, 17.0f);
		Graphics::DrawRect(mSelectCursorX - 10, mSelectCursorY - 2, 21.0f, 5.0f);
		Graphics::SetColor(0.4f, 1.0f, 0.4f, 1.0f);
		Graphics::DrawRect(mSelectCursorX - 1.5f, mSelectCursorY - 6, 3.0f, 13.0f); Graphics::DrawRect(mSelectCursorX - 8, mSelectCursorY - 1.5f, 17.0f, 3.0f);
	}


	DrawTransform();

	//Graphics::SetColor(1.0f, 0.0f, 0.3f);
	//Graphics::OutlineRect(mWallLeft, mWallTop, (mWallRight - mWallLeft), (mWallBottom - mWallTop), 8);
    
    //mm_bottom_sand

	Graphics::SetColor();
	EnumList(FMotionObject, aObject, mMotionObjects)aObject->Draw();



	Graphics::SetColor();

}

void UMainWorkspace::TouchDown(float pX, float pY, void *pData)
{
	if(gUtils->WorkspaceHasFocus() == false)return;

	UNode *aPreviouslySelectedNode = gUtilsNode;
	UNode *aClicked = GetTouchNode(pX, pY, 0);

	if(mMode == UTIL_WS_MODE_LINK)
	{
		mLinkStartNode = aClicked;
		mLinkTargetNode = 0;
		gUtilsNode = aClicked;
	}

	if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)// || (mMode == UTIL_WS_MODE_DRAG))
	{
		EnumList(UNode, aEditSprite, mNodeList)
		{
			//aEditSprite->mSelected = false;
			//aEditSprite->mSelectedCurrently = false;

		}

		mDragging = false;
		if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)
		{
			if(aClicked)// || aClickedRotation)
			{
				gUtilsNode = aClicked;

				mDragData = pData;

				mDragging = true;

				mDragImageStartX = gUtilsNode->GetTouchX();
				mDragImageStartY = gUtilsNode->GetTouchY();

				mDragTouchStartX = pX;
				mDragTouchStartY = pY;
			}
			else
			{
				gUtilsNode = 0;
			}
		}
	}


	if(mMode == UTIL_WS_MODE_TRANSFORM)
	{
		if(aClicked)
		{
			gUtilsNode = aClicked;

			mDragData = pData;
			mDragging = true;

			//mTransformStartCenterX = 0.0f;
			//mTransformStartCenterY = 0.0f;

			mDragTransformStartScale = gUtilsNode->mObject->mScale;
			mDragTransformStartRotation = gUtilsNode->mObject->mRotation;


			mDragImageStartX = gUtilsNode->GetTouchX();
			mDragImageStartY = gUtilsNode->GetTouchY();

			mDragTouchStartX = pX;
			mDragTouchStartY = pY;
		}
		else
		{
			gUtilsNode = 0;
		}
	}


	if(mMode == UTIL_WS_MODE_PAN)
	{

	}


	if(mMode == UTIL_WS_MODE_SET_CURSOR)
	{
		mSelectCursorX = pX;
		mSelectCursorY = pY;

	}


	TouchMove(pX, pY, pData);



	if(gUtilsNode != aPreviouslySelectedNode)
	{
		SetSelectedNode(gUtilsNode);
	}
}

void UMainWorkspace::TouchMove(float pX, float pY, void *pData)
{
	if(gUtils->WorkspaceHasFocus() == false)return;

	if(mMode == UTIL_WS_MODE_LINK)
	{
		if(mLinkStartNode)
		{
			mLinkTargetNode = GetTouchNode(pX, pY, mLinkStartNode);
		}
	}


	if(mMode == UTIL_WS_MODE_SET_CURSOR)
	{
		mSelectCursorX = pX;
		mSelectCursorY = pY;
	}


	if(mMode == UTIL_WS_MODE_TRANSFORM)
	{
		if((gUtilsNode != 0) && (mDragging == true) && (pData == mDragData))
		{
			float aDiffX = mDragTouchStartX - mDragImageStartX;
			float aDiffY = mDragTouchStartY - mDragImageStartY;

			float aDist = aDiffX * aDiffX + aDiffY * aDiffY;

			if(aDist >= 0.25f)
			{
				aDist = sqrtf(aDist);
				aDiffX /= aDist;
				aDiffY /= aDist;

				float aOriginalDist = aDist;
				float aOriginalRotation = FaceTarget(aDiffX, aDiffY);


				aDiffX = pX - mDragImageStartX;
				aDiffY = pY - mDragImageStartY;

				aDist = aDiffX * aDiffX + aDiffY * aDiffY;

				if(aDist >= 0.5f)
				{
					aDist = sqrtf(aDist);

					aDiffX /= aDist;
					aDiffY /= aDist;

					float aNewDist = aDist;
					float aNewRotation = FaceTarget(aDiffX, aDiffY);

					float aDistFactor = (aNewDist / aOriginalDist);
					float aRotationDiff = DistanceBetweenAngles(aOriginalRotation, aNewRotation);

					gUtilsNode->mObject->mRotation = mDragTransformStartRotation + aRotationDiff;
					gUtilsNode->mObject->mScale = mDragTransformStartScale * aDistFactor;

					gUtilsNode->mRefresh = true;
				}
			}
		}
	}


	if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)// || (mMode == UTIL_WS_MODE_DRAG))
	{
		if((gUtilsNode != 0) && (mDragging == true) && (pData == mDragData))
		{
			if(gKeyPressed[DIK_LSHIFT] || gKeyPressed[DIK_RSHIFT])
			{
				if(fabsf(mDragTouchStartX - pX) > fabsf(mDragTouchStartY - pY))
				{
					gUtilsNode->WorldPosSet(mDragImageStartX - (mDragTouchStartX - pX), mDragImageStartY);
					gUtilsNode->mRefresh = true;
				}
				else
				{
					gUtilsNode->WorldPosSet(mDragImageStartX, mDragImageStartY - (mDragTouchStartY - pY));
					gUtilsNode->mRefresh = true;
				}
			}
			else
			{
				gUtilsNode->WorldPosSet(mDragImageStartX - (mDragTouchStartX - pX), mDragImageStartY - (mDragTouchStartY - pY));
				gUtilsNode->mRefresh = true;
			}

			
		}
	}
}

void UMainWorkspace::TouchUp(float pX, float pY, void *pData)
{
	if(gUtils->WorkspaceHasFocus() == false)return;

	if(mDragging && (gUtilsNode != 0))
	{
		//gUtilsNode->MotionKeyMake(mTimelineTick);
	}

	if(mMode == UTIL_WS_MODE_LINK)
	{
		if(mLinkStartNode != 0)
		{
			if(mLinkTargetNode != 0)
			{
				if(mLinkStartNode->mParent == mLinkTargetNode)
				{
					mLinkStartNode->mParent = 0;
				}
				else
				{
					if(mLinkTargetNode->mParent == mLinkStartNode)
					{
						mLinkTargetNode->SetParent(0);
					}

					float aOriginalWorldX = mLinkStartNode->mWorldX;
					float aOriginalWorldY = mLinkStartNode->mWorldY;


					mLinkStartNode->SetParent(mLinkTargetNode);

					//if((mLinkStartNode->mTrackingAdjustWorldPosition) && (mLinkStartNode->mParticleSource == false))
					//{
						mLinkStartNode->mTrackingType = NODE_TRACK_OBJ;

						mLinkStartNode->mTrackingOffsetX = (aOriginalWorldX - mLinkTargetNode->mWorldX);
						mLinkStartNode->mTrackingOffsetY = (aOriginalWorldY - mLinkTargetNode->mWorldY);
					//}
				}
			}
			else
			{
                
                
                
				mLinkStartNode->SetParent(0);
                if(mLinkStartNode->mTrackingType == NODE_TRACK_OBJ)
                {
                    mLinkStartNode->mTrackingType = NODE_TRACK_POINT;
                }
			}
		}
	}

	mDragging = false;
	mLinkStartNode = 0;
	mLinkTargetNode = 0;

	gUtils->SetSelectedNode(gUtilsNode);
}

void UMainWorkspace::TouchFlush()
{

}

void UMainWorkspace::MouseWheel(int pDirection)
{
	if(gUtils->WorkspaceHasFocus() == false)return;

	bool aShift = (gKeyPressed[DIK_LSHIFT]);
	bool aCtrl = (gKeyPressed[DIK_LCONTROL]);

	if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)
	{
		if((aShift == false) && (aCtrl == false))
		{
			if(pDirection > 0)SelectionImageNext();
			else SelectionImagePrev();

			
		}
		else if((aShift == true) && (aCtrl == false))
		{
			if(pDirection > 0)SelectionPickNext();
			else SelectionPickPrevious();
		}
		else if((aShift == false) && (aCtrl == true))
		{
			if(gUtilsNode)
			{
				if(pDirection > 0)gUtilsNode->mObject->mScale += 0.01f;
				else gUtilsNode->mObject->mScale -= 0.01f;
				SetSelectedNode();
			}
		}
		else if((aShift == true) && (aCtrl == true))
		{
			if(gUtilsNode)
			{
				if(pDirection > 0)gUtilsNode->mObject->mRotation += 1.0f;
				else gUtilsNode->mObject->mRotation -= 1.0f;
				SetSelectedNode();
			}
		}
	}

	if(mMode == UTIL_WS_MODE_LINK)
	{
		if(pDirection > 0)SelectionParentPickNext();
		else SelectionParentPickPrevious();
	}
}

void UMainWorkspace::KeyDown(int pKey)
{
	if(gUtils->WorkspaceHasFocus() == false)return;

	bool aUp = (pKey == DIK_UP);
	bool aDown = (pKey == DIK_DOWN);
	bool aLeft = (pKey == DIK_LEFT);
	bool aRight = (pKey == DIK_RIGHT);


	bool aArrow = (aUp || aDown || aLeft || aRight);
	bool aShift = (gKeyPressed[DIK_LSHIFT]);
    bool aCtrl = (gKeyPressed[DIK_LCONTROL]);
    bool aAlt = (gKeyPressed[DIK_LALT]);
    
    

	if(aArrow)
	{
		if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)
		{
			if((aShift == false) && (aCtrl == false) && (aAlt == false))
			{
				if(aUp)SelectionShift(0.0f, -1.0f);
				if(aDown)SelectionShift(0.0f, 1.0f);
				if(aRight)SelectionShift(1.0f, 0.0f);
				if(aLeft)SelectionShift(-1.0f, 0.0f);

			}
			else if((aShift == true) && (aCtrl == false) && (aAlt == false))
			{
				if(aUp)SelectionShift(0.0f, -10.0f);
				if(aDown)SelectionShift(0.0f, 10.0f);
				if(aRight)SelectionShift(10.0f, 0.0f);
				if(aLeft)SelectionShift(-10.0f, 0.0f);
			}
            else if((aShift == true) && (aCtrl == true) && (aAlt == false))
            {
                if(aRight)SelectionMoveUp();
                if(aLeft)SelectionMoveDown();
            }
			else if((aShift == false) && (aCtrl == false) && (aAlt == true))
			{
				if(aRight)SelectionImageNext();
				if(aLeft)SelectionImagePrev();
                if(aUp)SelectionMoveUp();
                if(aDown)SelectionMoveDown();
			}
            else if((aShift == false) && (aCtrl == true) && (aAlt == false))
            {
                if(aUp)SelectionPickNext();
                if(aDown)SelectionPickPrevious();
            }
		}
        else if(mMode == UTIL_WS_MODE_LINK)
        {
            if((aShift == false) && (aCtrl == false) && (aAlt == false))
            {
                if(aUp)SelectionPickNext();
                if(aDown)SelectionPickPrevious();
                if(aRight)SelectionParentPickNext();
                if(aLeft)SelectionParentPickPrevious();
            }
        }
	}

	if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)
	{
		if(pKey == DIK_DELETE)
		{
			SelectionDelete();
		}
	}

	if(pKey == DIK_F1){ SetMode(UTIL_WS_MODE_SELECT_AND_DRAG);}
	if(pKey == DIK_F2){ SetMode(UTIL_WS_MODE_TRANSFORM);}
	if(pKey == DIK_F3){ SetMode(UTIL_WS_MODE_PAN);}
	if(pKey == DIK_F4){ SetMode(UTIL_WS_MODE_LINK);}
	if(pKey == DIK_F5){ SetMode(UTIL_WS_MODE_SET_CURSOR);}

    
    if(gUtils != 0)
    {
        
        if(pKey == DIK_A)
        {
            SelectionPickNext();
        }
        if(pKey == DIK_B)
        {
            if((aShift == false) && (aCtrl == false) && (aAlt == false)){if(gUtilsNode){gUtilsNode->mBlendType++;if(gUtilsNode->mBlendType > 5)gUtilsNode->mBlendType = 0;}}
            else if(aShift){if(gUtilsNode != 0)gUtilsNode->mBlendType = 0;}
            else{}
        }
        if(pKey == DIK_C)
        {
            if(aShift)SelectionClone();
        }
        if(pKey == DIK_E)
        {
            if((aShift == false) && (aCtrl == false) && (aAlt == false))Export();
            else if((aShift == false) && (aCtrl == true) && (aAlt == false))ExportOffsets();
            else if((aShift == false) && (aCtrl == false) && (aAlt == true))ExportParticleBasic();
        }
        if(pKey == DIK_L)
        {
            if((aShift == false) && (aCtrl == false) && (aAlt == false))
            {
                if(gUtilsNode != 0)
                {
                if(gUtilsNode->mTemplate.mSpawnSourceType == SPAWN_SOURCE_POLYGON)gUtils->PathCreate(UTIL_PATH_TYPE_POLY);
                else if(gUtilsNode->mTemplate.mSpawnSourceType == SPAWN_SOURCE_POINT_CLOUD)gUtils->PathCreate(UTIL_PATH_TYPE_POINT_CLOUD);
                else
                {
                    gUtilsNode->mTemplate.SetSpawnSource(SPAWN_SOURCE_POLYGON);
                    gUtils->PathCreate(UTIL_PATH_TYPE_POLY);
                }
                }
            }
            else if((aShift == false) && (aCtrl == false) && (aAlt == true))gUtils->Load();
            else if((aShift == false) && (aCtrl == false) && (aAlt == true)){}
        }
        if(pKey == DIK_M)
        {
            if(gUtilsNode)gUtils->PathCreate(UTIL_PATH_TYPE_MOVEMENT);
        }
        if(pKey == DIK_N)
        {
            if(gUtilsNode)
            {
                gUtilsNode->ExportGenerateNames();
                Log("Node Name ( %s );\n", gUtilsNode->mExportName.c());
            }
            CreateNodeSpriteSequence();
        }
        
        if(pKey == DIK_P)
        {
            CreateNodeParticles();
        }
        
        if(pKey == DIK_R)
        {
            CreateNodeRectangle();
        }
        
        if(pKey == DIK_S)
        {
            if((aShift == false) && (aCtrl == false) && (aAlt == false))CreateNodeSprite();
            else if((aShift == false) && (aCtrl == true) && (aAlt == false))gUtils->Save();
            else if((aShift == false) && (aCtrl == false) && (aAlt == true)){if(gUtilsNode != 0){if(gUtilsNode->mSpriteSequence != 0)EditNodeSpriteSequence();else EditNodeSprite();}}
        }
        
        if(pKey == DIK_Q)
        {
            if(aAlt == true){if(gUtilsNode != 0){EditNodeSpriteSequence();}}
            else CreateNodeSpriteSequence();
        }
        
        if(pKey == DIK_T)
        {
            if((aShift == false) && (aCtrl == false) && (aAlt == false))gUtils->mTimelineEnabled = !(gUtils->mTimelineEnabled);
            else if(aCtrl)SelectionMoveFront();
        }
        
        if(pKey == DIK_U)
        {
            gUtils->mUpdatesAllowed = !(gUtils->mUpdatesAllowed);
        }
        
        if(pKey == DIK_V)
        {
            if(gUtilsNode)gUtilsNode->mIsVisible = !(gUtilsNode->mIsVisible);
        }
        
        if(pKey == DIK_W)
        {
            if((aShift == true) && (aCtrl == false) && (aAlt == false)){}
            else if((aShift == false) && (aCtrl == false) && (aAlt == false)){gUtils->DeleteSaved();}
        }
        
        if(pKey == DIK_X)
        {
            if(aShift || aAlt)Clear();
        }
    }
    
	SetSelectedNode();
}

void UMainWorkspace::KeyUp(int pKey)
{

}

void UMainWorkspace::Notify(void *pSender)
{

}

void UMainWorkspace::Notify(void *pSender, int pID, void *pObject)
{

}

void UMainWorkspace::SetMode(int pMode)
{
    if(mModeNext == -1)
    {
        mModeNext = pMode;
        return;
    }
    
	mMode = pMode;

	mLinkStartNode = 0;
	mLinkTargetNode = 0;

	if(mMode == UTIL_WS_MODE_PAN)
	{
		gUtils->PanStart();

	}
	else
	{
		gUtils->PanEnd();

	}

	if(mMode == UTIL_WS_MODE_LINK)
	{

	}

	if(mMode == UTIL_WS_MODE_SELECT_AND_DRAG)
	{

	}
	else if(mMode == UTIL_WS_MODE_PAN)
	{

		

		//ShowOverlayPan();

		//UMainWorkspacePanOverlay *aOverlayPan = new UMainWorkspacePanOverlay();
		//AddOverlay(aOverlayPan);

		//SetOverlayView(aPanOverlay);
	}
    
    gUtils->mToolbar->mSegmentMode->SetTarget(&(mMode));
    //gUtils->mToolbar->Notify();
}

void UMainWorkspace::SetSelectedNode(UNode *pNode)
{
	gUtils->SetSelectedNode(pNode);
	/*
	gUtilsNode = pNode;
	EnumList(FView, aView, mSubviews)
	{
		aView->Notify(this, UTIL_ACTION_NODE_SELECT, pNode);
	}
	*/
}

void UMainWorkspace::SetSelectedNode()
{
	SetSelectedNode(gUtilsNode);
}

void UMainWorkspace::FindSelectableNodes()
{
	mNodeListSelectable.Clear();

	EnumList(UNode, aNode, mNodeList)
	{
		mNodeListSelectable.Add(aNode);
	}
}

UNode *UMainWorkspace::GetTouchNode(float pX, float pY, UNode *pIgnoreNode)
{
	UNode *aResult = 0;
	UNode *aCenterNode = 0;

	FindSelectableNodes();

	float aBestCenterDist = (8.0f * 8.0f);

	EnumListReverse(UNode, aNode, mNodeListSelectable)
	{
		if(aNode != pIgnoreNode)
		{
			if(aResult == 0)
			{
				float aCheckDist = 0.0f;

				if(aNode->Contains1(pX, pY, aCheckDist))
				{
					aResult = aNode;
				}
			}
		}
	}

	EnumListReverse(UNode, aNode, mNodeListSelectable)
	{
		if(aNode != pIgnoreNode)
		{
			if(aResult == 0)
			{
				float aCheckDist = 0.0f;
				if(aNode->Contains2(pX, pY, aCheckDist))
				{
					aResult = aNode;
				}
			}
		}
	}

	return aResult;

}


void UMainWorkspace::CreateNodeSprite()
{
    UImagePicker *aPicker = new UImagePicker(this);
    aPicker->FillWithImages();
    aPicker->mListener = gUtils;
    gUtils->mImagePickType = 1;
    gUtils->AddSubview(aPicker);
    gUtils->mImagePickerUpdatesCurrentNode = false;
}

void UMainWorkspace::CreateNodeSpriteSequence()
{
	UImagePicker *aPicker = new UImagePicker(this);
	aPicker->FillWithImageSequences();
	aPicker->mListener = gUtils;
	gUtils->mImagePickType = 2;
	gUtils->AddSubview(aPicker);
	gUtils->mImagePickerUpdatesCurrentNode = false;
}

void UMainWorkspace::CreateNodeParticles()
{
	UImagePicker *aPicker = new UImagePicker(this);
	aPicker->FillWithAny();
	aPicker->mListener = gUtils;
	gUtils->mImagePickType = 3;
	gUtils->AddSubview(aPicker);
	gUtils->mImagePickerUpdatesCurrentNode = false;
}

void UMainWorkspace::CreateNodeRectangle()
{
	gUtils->mImagePickType = 4;
	gUtilWS->AddNode();
}

void UMainWorkspace::EditNodeSprite()
{
	UImagePicker *aPicker = new UImagePicker(this);
	aPicker->FillWithImages();
	aPicker->mListener = gUtils;
	gUtils->mImagePickType = 0;
	gUtils->AddSubview(aPicker);
	gUtils->mImagePickerUpdatesCurrentNode = true;
}

void UMainWorkspace::EditNodeSpriteSequence()
{
	UImagePicker *aPicker = new UImagePicker(this);
	aPicker->FillWithImageSequences();
	aPicker->mListener = gUtils;
	gUtils->mImagePickType = 0;
	gUtils->AddSubview(aPicker);
	gUtils->mImagePickerUpdatesCurrentNode = true;
}


void UMainWorkspace::AddNode()
{
	Deselect();
	UNode *aNode = new UNode();
	if(gUtils->mImagePickType == 4)aNode->mColorNode = true;
	AddNode(aNode);
}


void UMainWorkspace::AddSpriteNode(FSprite *pSprite)
{
	Deselect();


	if((gUtils->mImagePickType == 1) || (gUtils->mImagePickType == 2) || (gUtils->mImagePickType == 3))
	{
		UNode *aNode = new UNode();
		if(gUtils->mImagePickType == 3)aNode->mParticleSource = true;
		aNode->SetSprite(pSprite);
		AddNode(aNode);

		/*
		FMotionObject *aObj = new FMotionObject();
		mMotionObjects.Add(aObj);

		aObj->mSprite = pSprite;

		aObj->mX = gRand.Get(400) + 300;
		aObj->mY = gRand.Get(200) + 200;


		FMotionObjectFlow *aFlowX = new FMotionObjectFlow(&(aObj->mX));
		aObj->FlowAdd(aFlowX);

		FMotionObjectFlowKey *aKey0 = new FMotionObjectFlowKey(260);
		aKey0->mAnimationFunction = 8;


		FMotionObjectFlowKey *aKey1 = new FMotionObjectFlowKey(700.0f);
		aKey1->mAnimationFunction = 15;


		FMotionObjectFlowKey *aKey2 = new FMotionObjectFlowKey(400.0f);

		aFlowX->Add(aKey0, 0);
		aFlowX->Add(aKey1, 40);
		aFlowX->Add(aKey2, 120);



		FMotionObjectFlow *aFlowY = new FMotionObjectFlow(&(aObj->mY));
		aObj->FlowAdd(aFlowY);

		aKey0 = new FMotionObjectFlowKey(400);
		aKey0->mAnimationFunction = 5;


		aKey1 = new FMotionObjectFlowKey(600.0f);
		aKey1->mAnimationFunction = 12;

		aKey2 = new FMotionObjectFlowKey(380.0f);
		aFlowY->Add(aKey0, 20);
		aFlowY->Add(aKey1, 60);
		aFlowY->Add(aKey2, 150);

		*/

		



	}
}

void UMainWorkspace::AddSequenceNode(FSpriteSequence *pSpriteSequence)
{
	Deselect();
	if((gUtils->mImagePickType == 1) || (gUtils->mImagePickType == 2) || (gUtils->mImagePickType == 3))
	{
		UNode *aNode = new UNode();
		if(gUtils->mImagePickType == 3)aNode->mParticleSource = true;
		aNode->SetSpriteSequence(pSpriteSequence);
		AddNode(aNode);
	}
}

void UMainWorkspace::AddNode(UNode *pNode)
{
	if(pNode)
	{
		pNode->mWorldX = mWidth2;
		pNode->mWorldY = mHeight2;

		if(pNode->mTemplate.mSpawnSourceType == SPAWN_SOURCE_RECT)
		{
			pNode->mWorldX = mWidth2 - pNode->mTemplate.mSpawnSourceWidth / 2.0f;
			pNode->mWorldY = mHeight2 - pNode->mTemplate.mSpawnSourceHeight / 2.0f;
		}

		if(pNode->mParticleSource == true)pNode->mTrackingAdjustWorldPosition = false;
		if(pNode->mColorNode == true)pNode->mTrackingAdjustWorldPosition = false;
        
        if(gUtils->mReferenceView)
        {
            FVec2 aPos = FView::Convert(gUtils->mReferenceView->mWidth2, gUtils->mReferenceView->mHeight2, gUtils->mReferenceView, this);
            pNode->mWorldX = aPos.mX;
            pNode->mWorldY = aPos.mY;
        }
        
		mListAdd.Add(pNode);
	}
}

void UMainWorkspace::DeleteNode(UNode *pNode)
{
	if(pNode)
	{
		if(mListDelete.Exists(pNode) == false)
		{
			mListDelete.Add(pNode);
		}
		else

		{
			Log("SAY WHAT??\n");
			return;
		}



		EnumList(UNode, aNode, mNodeList)
		{
			if(aNode->mParent == pNode)
			{
				aNode->SetParent(0);
				//aNode->mParent = 0;
			}
		}

		//pNode->mParent = 0;
		pNode->SetParent(0);

	}
}

void UMainWorkspace::FindHeirarchy()
{
	EnumList(UNode, aNode, mNodeList)
	{
		aNode->mVisited = false;
		aNode->HeirarchyClear();
	}
	EnumList(UNode, aNode, mNodeList)
	{
		aNode->HeirarchyFind();
	}


	bool aLoop = true;

	while (aLoop == true)
	{
		aLoop = false;

		EnumList(UNode, aNode, mNodeList)
		{
			if(aNode->mVisited == false)
			{
				if(aNode->TrackingFind(false) == true)
				{
					aNode->mVisited = true;
					aLoop = true;
				}
			}
			
		}

	}

	EnumList(UNode, aNode, mNodeList)
	{
		if(aNode->mVisited == false)
		{
			aNode->TrackingFind(true);
		}
	}


	//mVisited



}

void UMainWorkspace::FindTracking(UNode *pNode)
{
	if(pNode)
	{
		if(pNode->mVisited == false)
		{

		}
	}
}


void UMainWorkspace::SelectionGetParent()
{
	if(gUtilsNode)
	{
		if(gUtilsNode->mParent)
		{
			SetSelectedNode(gUtilsNode->mParent);
		}
	}
}

void UMainWorkspace::SelectionMoveUp()
{
	mNodeList.MoveObjectUp(gUtilsNode);
}

void UMainWorkspace::SelectionMoveDown()
{
	mNodeList.MoveObjectDown(gUtilsNode);
}

void UMainWorkspace::SelectionMoveFront()
{
	mNodeList.MoveToLast(gUtilsNode);
}

void UMainWorkspace::SelectionMoveBack()
{
	mNodeList.MoveToFirst(gUtilsNode);
}

void UMainWorkspace::SelectionPickNext()
{
	FindSelectableNodes();

	int aIndex = mNodeListSelectable.Find(gUtilsNode);

	if((gUtilsNode == 0) || (aIndex == -1))
	{
		gUtilsNode = (UNode *)(mNodeListSelectable.FetchRandom());
	}
	else
	{
		if(mNodeListSelectable.mCount > 1)
		{

			aIndex--;
			if(aIndex < 0)(aIndex = mNodeListSelectable.mCount - 1);

			gUtilsNode = (UNode *)(mNodeListSelectable.Fetch(aIndex));
		}
	}
	SetSelectedNode(gUtilsNode);
}

void UMainWorkspace::SelectionPickPrevious()
{
	FindSelectableNodes();

	int aIndex = mNodeListSelectable.Find(gUtilsNode);

	if((gUtilsNode == 0) || (aIndex == -1))
	{
		gUtilsNode = (UNode *)(mNodeListSelectable.FetchRandom());
	}
	else
	{
		if(mNodeListSelectable.mCount > 1)
		{
			int aIndex = mNodeListSelectable.Find(gUtilsNode);
			aIndex++;
			if(aIndex >= mNodeListSelectable.mCount)(aIndex = 0);

			gUtilsNode = (UNode *)(mNodeListSelectable.Fetch(aIndex));
		}
	}
	SetSelectedNode(gUtilsNode);
}

void UMainWorkspace::SelectionImageNext()
{
	if(gUtilsNode)
	{
		if((gUtilsNode->mSpriteSequence) && (gSpriteSequenceList.mCount > 0))
		{
			int aFind = gSpriteSequenceList.Find(gUtilsNode->mSpriteSequence);
			aFind++;
			if((aFind < 0) || (aFind >= gSpriteSequenceList.mCount))aFind = 0;
			gUtilsNode->mSpriteSequence = (FSpriteSequence *)(gSpriteSequenceList.Fetch(aFind));
		}
		else if((gUtilsNode->mSprite) && (gSpriteList.mCount > 0))
		{
			int aFind = gSpriteList.Find(gUtilsNode->mSprite);
			aFind++;
			if((aFind < 0) || (aFind >= gSpriteList.mCount))aFind = 0;
			gUtilsNode->mSprite = (FSprite *)(gSpriteList.Fetch(aFind));
		}
	}
}

void UMainWorkspace::SelectionImagePrev()
{
	if(gUtilsNode)
	{
		if((gUtilsNode->mSpriteSequence) && (gSpriteSequenceList.mCount > 0))
		{
			int aFind = gSpriteSequenceList.Find(gUtilsNode->mSpriteSequence);
			aFind--;
			if((aFind < 0) || (aFind >= gSpriteSequenceList.mCount))aFind = (gSpriteSequenceList.mCount - 1);
			gUtilsNode->mSpriteSequence = (FSpriteSequence *)(gSpriteSequenceList.Fetch(aFind));
		}
		else if((gUtilsNode->mSprite) && (gSpriteList.mCount > 0))
		{
			int aFind = gSpriteList.Find(gUtilsNode->mSprite);
			aFind--;
			if((aFind < 0) || (aFind >= gSpriteList.mCount))aFind = (gSpriteList.mCount - 1);
			gUtilsNode->mSprite = (FSprite *)(gSpriteList.Fetch(aFind));
		}
	}
}

void UMainWorkspace::SelectionParentPickNext()
{
	if(gUtilsNode)
	{
		if(mNodeList.mCount >= 1)
		{
			if(gUtilsNode->mParent)
			{
				int aIndex = mNodeList.Find(gUtilsNode->mParent);
				aIndex++;

				if(((UNode *)mNodeList.Fetch(aIndex)) == gUtilsNode)
				{
					aIndex++;
				}

				gUtilsNode->SetParent(((UNode *)mNodeList.Fetch(aIndex)));
			}
			else
			{
				if(((UNode *)mNodeList.Fetch(0)) == gUtilsNode)
				{
					gUtilsNode->SetParent(((UNode *)mNodeList.Fetch(1)));
				}
				else
				{
					gUtilsNode->SetParent(((UNode *)mNodeList.Fetch(0)));
				}
			}
		}
	}
	SetSelectedNode(gUtilsNode);
}

void UMainWorkspace::SelectionParentPickPrevious()
{
	if(gUtilsNode)
	{
		if(mNodeList.mCount >= 1)
		{
			if(gUtilsNode->mParent)
			{
				int aIndex = mNodeList.Find(gUtilsNode->mParent);
				aIndex--;

				if(((UNode *)mNodeList.Fetch(aIndex)) == gUtilsNode)
				{
					aIndex--;
				}

				gUtilsNode->SetParent(((UNode *)mNodeList.Fetch(aIndex)));
			}
			else
			{
				if(((UNode *)mNodeList.Fetch(mNodeList.mCount - 1)) == gUtilsNode)
				{
					gUtilsNode->SetParent(((UNode *)mNodeList.Fetch(mNodeList.mCount - 2)));
				}
				else
				{
					gUtilsNode->SetParent(((UNode *)mNodeList.Fetch(mNodeList.mCount - 1)));
				}
			}
		}
	}
	SetSelectedNode(gUtilsNode);
}


void UMainWorkspace::SelectionClone()
{
	if(gUtilsNode)
	{

		FXMLTag *aTag = gUtilsNode->SaveXML();


		//FFile aFile;
		//gUtilsNode->Save(&aFile);
		UNode *aNode = new UNode();
		
		aNode->LoadXML(aTag);
		aNode->SetParent(gUtilsNode->mParent);

		

		float aWorldX = aNode->mWorldX;
		float aWorldY = aNode->mWorldY;

		SetSelectedNode(0);
		AddNode(aNode);

		aNode->WorldPosSet(aWorldX - 40, aWorldY + 40);


		delete aTag;
	}
}

void UMainWorkspace::SelectionShift(float pX, float pY)
{
	if(gUtilsNode)
	{
        
        
		if(gUtilsNode->mTrackingType != NODE_TRACK_POINT)// && (gUtilsNode->mParent))
		{
			gUtilsNode->mTrackingOffsetX += pX;
			gUtilsNode->mTrackingOffsetY += pY;

			if(gUtilsNode->mTrackingAdjustWorldPosition)
			{
				gUtilsNode->WorldPosShift(pX, pY);
				//gUtilsNode->ShiftWorldX(pX);
				//gUtilsNode->ShiftWorldY(pY);
			}


		}
		else
		{
			gUtilsNode->WorldPosShift(pX, pY);

			//gUtilsNode->ShiftWorldX(pX);
			//gUtilsNode->ShiftWorldY(pY);
		}

		
	}
	EnumList(UNode, aNode, mNodeList)
	{

	}
}




void UMainWorkspace::SelectionDelete()
{
	if(gUtilsNode)
	{
		DeleteNode(gUtilsNode);
		gUtilsNode = 0;
	}
	SetSelectedNode(gUtilsNode);
}






void UMainWorkspace::Deselect()
{
	gUtilsNode = 0;
	mDragging = false;
	SetSelectedNode(gUtilsNode);
}


void UMainWorkspace::SetTime(int pTime)
{

	bool aCancel = false;

	EnumList(UNode, aNode, mNodeList)
	{
		aCancel = false;

		if(mDragging)
		{
			if(gUtilsNode == aNode)
			{
				aCancel = true;
			}
		}

		if(aCancel == false)aNode->MotionApply(pTime);
	}
}

void UMainWorkspace::Clear()
{
	FList aList;
	EnumList(UNode, aNode, mNodeList)
	{
		aList.Add(aNode);
		aNode->mParent = 0;
	}

	while (aList.mCount > 0)
	{
		UNode *aDelete = ((UNode *)aList.Last());
		if(aDelete)
		{
			DeleteNode(aDelete);
		}
		aList.mCount--;
	}

	Deselect();
	SetSelectedNode(0);
}

void UMainWorkspace::Save(FFile *pFile)
{
	FindHeirarchy();

	EnumList(UNode, aNode, mNodeList)
	{
		aNode->mParentSaveIndex = mNodeList.Find(aNode->mParent);
	}

	pFile->WriteInt(mNodeList.mCount);

	int aNodeIndex = 0;
	EnumList(UNode, aNode, mNodeList)
	{
		FString aNodePath = gDirDocuments + FString("node_data_") + FString(aNodeIndex) + FString(".xml");
		FXMLTag *aTag = aNode->SaveXML();
		FXML aXML;
		aXML.mRoot = aTag;
		aXML.Save(aNodePath);
		aNodeIndex++;
	}
}

void UMainWorkspace::Load(FFile *pFile)
{
	Clear();

	int aCount = pFile->ReadInt();
    for(int i = 0; i<1; i++) //TODO:
	{
		UNode *aNode = new UNode();
		FString aNodePath = gDirDocuments + FString("node_data_") + FString(i) + FString(".xml");
		FXML aXML;
		aXML.Load(aNodePath);
		aNode->LoadXML(aXML.mRoot);
		mListAdd.Add(aNode);
	}

	for(int i = 0; i<aCount; i++)
	{
		UNode *aNode = (UNode *)mListAdd.Fetch(i);
		if(aNode)
		{
			UNode *aParentNode = (UNode *)mListAdd.Fetch(aNode->mParentSaveIndex);
			aNode->SetParent(aParentNode);
		}
	}

	mListAdd.Reverse();
}


void UMainWorkspace::ExportOffsets()
{
    FString aExport = ExportOffsets(gUtilsNode);
    if(aExport.mLength > 0)Log("\n\n\n%s\n\n\n", aExport.c());
}

FString	UMainWorkspace::ExportOffsets(UNode *pNode)
{
    FString aExport = "";
    if(pNode)
    {
        ExportSetUp(pNode);
        
        int aLastExportDepth = -1;
        
        
        
        EnumList(UNode, aNode, mExportList)
        {
            
            
            FString aOffsetString = "";
            
            FString aOffsetStringX = "";
            FString aOffsetStringY = "";
            
            FString aComment = "";
            
            
            //aExport += FString("( ") + FString(aNode->mTrackingOffsetX) + FString(", ") + FString(FString(aNode->mTrackingOffsetY)) + FString(" ); //") + aNode->mExportName;
            
            aComment += FString("\t\t//[") + aNode->mExportName + FString("] (");

            
            
            if(aNode->mTrackingType == NODE_TRACK_OBJ)
            {
                aOffsetStringX = "mP->mX + ";
                aOffsetStringY = "mP->mY + ";
            }
            if(aNode->mTrackingType == NODE_TRACK_SCREEN)
            {
                aOffsetStringX = "gAppWidth2";
                aOffsetStringY = "gAppHeight2";
                
                aComment += " (Screen ";
                if((aNode->mTrackingSideY == 1) && (aNode->mTrackingSideX == 1))
                {
                    aComment += "Center";
                }
                else
                {
                    if(aNode->mTrackingSideY == 1)
                    {
                        aComment += "Center";
                    }
                    if(aNode->mTrackingSideY == 0)
                    {
                        aComment += "Top";
                        aOffsetStringY = "0.0f";
                    }
                    if(aNode->mTrackingSideY == 2)
                    {
                        
                        aComment += "Bottom";
                        aOffsetStringY = "gAppHeight";
                    }
                    
                    aComment += " ";
                    
                    if(aNode->mTrackingSideX == 1)
                    {
                        aComment += "Center";
                    }
                    if(aNode->mTrackingSideX == 0)
                    {
                        aComment += "Left";
                        aOffsetStringX = "0.0f";
                    }
                    if(aNode->mTrackingSideX == 2)
                    {
                        aComment += "Right";
                        aOffsetStringX = "gAppWidth";
                    }
                }
                
                aOffsetStringX += " + ";
                aOffsetStringY += " + ";
                
                
                aComment += ")";
            }
            
            
            
            aOffsetStringX += FString(aNode->mTrackingOffsetX);
            aOffsetStringY += FString(aNode->mTrackingOffsetY);
            
            aOffsetString = FString("( ") + aOffsetStringX + FString(", ") + aOffsetStringY + FString(" );");
            
            aExport += aOffsetString;
            aExport += aComment;
            
            
            //aExport += FString("( ") + FString(aNode->mTrackingOffsetX) + FString(", ") + FString(FString(aNode->mTrackingOffsetY)) + FString(" ); //") + aNode->mExportName;
            
            
            if(aNode->mExportDepth == aLastExportDepth)
            {
                aExport += "\n";
            }
            else
            {
                aExport += "______\n___\n";
            }
        }
        
    }
    return aExport;
}

void UMainWorkspace::ExportRel(int pSideX, int pSideY, bool pUntransform)
{
    
}

void UMainWorkspace::ExportRelChildren(int pSideX, int pSideY, bool pUntransform)
{
    Log("ExportRelChildren(!\n");
    
    if(gUtilsNode)
    {
        ExportSetUp(gUtilsNode);
        
        
        float aCenterX = gUtilsNode->mWorldX;
        float aCenterY = gUtilsNode->mWorldY;
        
        
        EnumList(UNode, aNode, mNodeList)
        {
            
            
            
            if(aNode->mParent == gUtilsNode)
            {
            
            
            FString aOffsetString = "";
            
            FString aOffsetStringX = "";
            FString aOffsetStringY = "";
            
           
                
            
                
                float aDX = aNode->mWorldX - aCenterX;
                float aDY = aNode->mWorldY - aCenterY;
                
                
                
            
            

            
            
            aOffsetStringX += FString(aDX);
            aOffsetStringY += FString(aDY);
            
            aOffsetString = FString("( ") + aOffsetStringX + FString(", ") + aOffsetStringY + FString(" );");
            
                
                Log("%s\n", aOffsetString.c());
                

        }
        
            
        }
        
    }
}


void UMainWorkspace::ExportParticleBasic()
{
    FString aExport = ExportParticleBasic(gUtilsNode);
    if(aExport.mLength > 0)Log("\n\n\n%s\n\n\n", aExport.c());
}

FString	UMainWorkspace::ExportParticleBasic(UNode *pNode)
{
    ExportReset();
    FString aExport = "";
    if(pNode)
    {
        
        
    }
    return aExport;
}

void UMainWorkspace::ExportPaths()
{
    FString aExport = ExportPaths(gUtilsNode);
    if(aExport.mLength > 0)Log("\n\n\n%s\n\n\n", aExport.c());
}

FString	UMainWorkspace::ExportPaths(UNode *pNode)
{
    ExportReset();
    FString aExport = "";
    if(pNode)
    {
        aExport += pNode->mMotionPath.ExportKeySequence("aPiggyPath");
        
    }
    return aExport;
}


void UMainWorkspace::Export()
{
    FString aExport = Export(gUtilsNode);
    Log("\n\n\n%s\n\n\n", aExport.c());
}

void UMainWorkspace::ExportSetUp(UNode *pNode)
{
    ExportReset();
    FString aExport = "";
    if(pNode)
    {
        pNode->mExportDepth = 0;
        ExportPrepare(pNode, 1);
        
        
        for(int aOuter=0;aOuter<mNodeList.mCount;aOuter++)
        {
            UNode *aNodeOuter = ((UNode *)(mNodeList.Fetch(aOuter)));
            
            int aIndex = 2;
            
            if(aNodeOuter->mExportNameIndex == 0)
            {
                for(int aInner=(aOuter + 1);aInner<mNodeList.mCount;aInner++)
                {
                    UNode *aNodeInner = ((UNode *)(mNodeList.Fetch(aInner)));
                    
                    if(aNodeInner->mExportName == aNodeOuter->mExportName)
                    {
                        aNodeInner->mExportNameIndex = aIndex;
                        
                        aNodeInner->mExportName += FString("_");
                        aNodeInner->mExportName += FString(aIndex);
                        
                        aIndex++;
                    }
                }
            }
        }
        
        UNode *aBestExportNode = 0;
        
        bool aLoop = true;
        
        while(aLoop)
        {
            aLoop = false;
            aBestExportNode = 0;
            
            
            EnumList(UNode, aNode, mNodeList)
            {
                if(aNode->mExportDepth != -1)
                {
                    if(aBestExportNode == 0)
                    {
                        aBestExportNode = aNode;
                    }
                    else
                    {
                        if(aNode->mExportDepth < aBestExportNode->mExportDepth)
                        {
                            aBestExportNode = aNode;
                        }
                    }
                }
            }
            
            if(aBestExportNode)
            {
                aLoop = true;
                aBestExportNode->mExportDepth = -1;
                mExportList += aBestExportNode;
            }
        }
    }
}

FString	UMainWorkspace::Export(UNode *pNode)
{
    ExportReset();
	FString aExport = "";
	if(pNode)
    {
        ExportSetUp(pNode);
    
        
        FList aListBlocks;
        FList aListBlockNames;
        
        
        aExport = "";
        EnumList(UNode, aNode, mExportList)aExport.Append(ExportPassDeclarations(aNode).c());
        if(aExport.mLength > 0)
        {
            aListBlocks += new FString(aExport);
            aListBlockNames += new FString("Declarations");
        }
        
        
        aExport = "";
        EnumList(UNode, aNode, mExportList)aExport.Append(ExportPassLinkWorld(aNode).c());
        if(aExport.mLength > 0)
        {
            aListBlocks += new FString(aExport);
            aListBlockNames += new FString("Link - Environment");
        }
        
        aExport = "";
        EnumList(UNode, aNode, mExportList)aExport.Append(ExportPassLinkParents(aNode).c());
        if(aExport.mLength > 0)
        {
            aListBlocks += new FString(aExport);
            aListBlockNames += new FString("Link - Parents");
        }
        
        aExport = "";
        EnumList(UNode, aNode, mExportList)aExport.Append(ExportPassLinkTracking(aNode).c());
        if(aExport.mLength > 0)
        {
            aListBlocks += new FString(aExport);
            aListBlockNames += new FString("Link - Tracking");
        }
        
        
        aExport = "";
        EnumList(UNode, aNode, mExportList)aExport.Append(ExportPassInfo(aNode).c());
        if(aExport.mLength > 0)
        {
            aListBlocks += new FString(aExport);
            aListBlockNames += new FString("Basic Info");
        }
        
        
        aExport = "";
        EnumList(UNode, aNode, mExportList)aExport.Append(ExportPassParticleData(aNode).c());
        if(aExport.mLength > 0)
        {
            aListBlocks += new FString(aExport);
            aListBlockNames += new FString("Particle Data");
        }
        
        
        
        
        
        aExport = "";
        EnumList(UNode, aNode, mExportList)aExport.Append(ExportPassFinalize(aNode).c());
        if(aExport.mLength > 0)
        {
            aListBlocks += new FString(aExport);
            aListBlockNames += new FString("Finalize...");
        }
        
        
        
        
        
        //aExport += FString("//");
        
        bool aLastWasNamed = false;
        aExport = "";
        for(int i=0;(i<aListBlocks.mCount) && (i<aListBlockNames.mCount);i++)
        {
            FString *aStringBlock = (FString *)(aListBlocks.Fetch(i));
            FString *aStringName = (FString *)(aListBlockNames.Fetch(i));
            
            
            if(aStringBlock->mLength > 0)
            {
                while(aStringName->mLength < 30)
                {
                    aStringName->Append(' ');
                }
                
                if(aStringName->mLength > 0)
                {
                    if(aLastWasNamed)
                    {
                        aExport += FString("//\n");
                    }
                    aExport += FString("//    ") + FString(aStringName->c());
                    aExport += FString("//\n");
                    
                    aExport += FString(aStringBlock->c());
                    
                    
                    aLastWasNamed = true;
                }
                else
                {
                    aExport += FString(aStringBlock->c());
                    aLastWasNamed = false;
                }
                
            }
            
            
            
        }
        
        if(aLastWasNamed)
        {
            aExport += FString("//\n////////////");
        }
        
        aExport += FString("\n");
        
        
        FreeList(FString, aListBlocks);
        FreeList(FString, aListBlockNames);
        
        

	}


	return aExport;
}


void UMainWorkspace::ExportReset()
{
    mExportList.Clear();
    EnumList(UNode, aNode, mNodeList)
    {
        aNode->mDidExport = false;
        aNode->mExportSubnodes.Clear();
        aNode->mExportDepth = -1;
        aNode->mExportAddTarget = 0;
        aNode->mExportNameIndex = 0;
    }
}

FString	UMainWorkspace::ExportPassDeclarations(UNode *pNode)
{
    FString aResult = "";
    
    
    if(pNode)
    {
    aResult += FString(pNode->mExportTypeName.c()) + FString(" *") + FString(pNode->mExportName.c()) + FString(" = new ") + FString(pNode->mExportTypeName.c())
    + FString("(");
    
    if(pNode->mSpriteSequence)
    {
        aResult += FString("&(gApp->") + FString(pNode->mSpriteSequence->mFilePrefix.c()) + FString("));\n");
    }
    else if(pNode->mSprite)
    {
        aResult += FString("&(gApp->") + FString(pNode->mSprite->mFileName.c()) + FString("));\n");
    }
    else
    {
        aResult += FString(");\n");
    }
    
    }
    
    
    return aResult;
}



FString	UMainWorkspace::ExportPassInfo(UNode *pNode)
{
	FString aResult = "";FString aString="";FList aList;
	if(pNode)
	{
        if(pNode->mParticleSource == false)
        {
            if((pNode->mColor.mRed != 1.0f) || (pNode->mColor.mGreen != 1.0f) || (pNode->mColor.mBlue != 1.0f) || (pNode->mColor.mAlpha != 1.0f) || (mColor.mRed != -222.0f))
            {
                aString = "ColorSet(";
                
                if((pNode->mColor.mRed != 1.0f) || (pNode->mColor.mGreen != 1.0f) || (pNode->mColor.mBlue != 1.0f))
                {
                    
                    aString += FString(pNode->mColor.mRed) + FString(", ");
                    aString += FString(pNode->mColor.mGreen) + FString(", ");
                    aString += FString(pNode->mColor.mBlue);
                    
                    if(mColor.mAlpha != 1.0f)
                    {
                        aString += FString(", ") + FString(pNode->mColor.mAlpha);
                    }
                }
                else
                {
                    aString += FString(pNode->mColor.mAlpha);
                }
                
                
                
                
                
                
                aString += FString(")");
                
                aList += new FString(aString);
            }
        }
        
        if(pNode->mObject->mRotation != 0.0f)
        {
            aString = FString("RotationSet(") + FString(pNode->mObject->mRotation) + FString(")");
            aList += new FString(aString);
        }
        
        if(pNode->mObject->mScale != 1.0f)
        {
            aString = FString("ScaleSet(") + FString(pNode->mObject->mScale) + FString(");");
            aList += new FString(aString);
        }
        
        
        
        
        if(pNode->mBlendType != BLEND_TYPE_STANDARD)
        {
            aString = "SetBlendType(";
            if(pNode->mBlendType == BLEND_TYPE_STANDARD)aString = "BlendTypeSetDefault()";
            else if(pNode->mBlendType == BLEND_TYPE_ADDITIVE)aString = "BlendTypeSetAdditive()";
            else if(pNode->mBlendType == BLEND_TYPE_PREMULTIPLIED)aString = "BlendTypeSetPremultiplied()";
            else aString = FString("BlendTypeSet(") + FString(pNode->mBlendType) + FString(");");
            aList += new FString(aString);
            
        }

        
        
        
        
        if(pNode->mBlendType != BLEND_TYPE_STANDARD)
        {
            aString = "SetBlendType(";
            if(pNode->mBlendType == BLEND_TYPE_STANDARD)aString = "BlendTypeSetDefault()";
            else if(pNode->mBlendType == BLEND_TYPE_ADDITIVE)aString = "BlendTypeSetAdditive()";
            else if(pNode->mBlendType == BLEND_TYPE_PREMULTIPLIED)aString = "BlendTypeSetPremultiplied()";
            else aString = FString("BlendTypeSet(") + FString(pNode->mBlendType) + FString(");");
            aList += new FString(aString);
            
        }


        /*
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
        
        
        if(pNode->mBlendType != BLEND_TYPE_STANDARD)
		{
            aString = "SetBlendType(";
            if(pNode->mBlendType == BLEND_TYPE_STANDARD)aString = "BlendTypeSetDefault()";
            else if(pNode->mBlendType == BLEND_TYPE_ADDITIVE)aString = "BlendTypeSetAdditive()";
            else if(pNode->mBlendType == BLEND_TYPE_PREMULTIPLIED)aString = "BlendTypeSetPremultiplied()";
            else aString = FString("BlendTypeSet(") + FString(pNode->mBlendType) + FString(");");
            aList += new FString(aString);
            
		}
        */
        
        
        aResult += ExportApplyActions(pNode, &aList);
	}

	return aResult;
}

FString	UMainWorkspace::ExportPassParticleData(UNode *pNode)
{
    FString aResult = "";
    if(pNode)
    {
        if(pNode->mParticleSource)
        {
            aResult += FString(pNode->mTemplate.ExportString(pNode->mExportName.c()));
            aResult += "\n";
        }
    }
    return aResult;
}




FString	UMainWorkspace::ExportPassLinkWorld(UNode *pNode)
{
    FString aResult = "";
    if(pNode)
    {
        if(pNode->mExportAddTarget == 0)
        {
            aResult += FString("mAnimations.Add(") + FString(pNode->mExportName) + FString(");");
        }
    }
    return aResult;
}

FString	UMainWorkspace::ExportPassLinkParents(UNode *pNode)
{
    FString aResult = "";
    if(pNode)
    {
        if(pNode->mExportAddTarget != 0)
        {
            aResult += FString(pNode->mExportAddTarget->mExportName) + FString("->ObjectAdd");
            bool aUnder = false;
            int aIndexAdd = mNodeList.Find(pNode->mExportAddTarget);
            int aIndex = mNodeList.Find(pNode);
            if(aIndex < aIndexAdd)aUnder = true;
            if(aUnder)aResult += "Under";
            aResult += FString("(") + FString(pNode->mExportName) + FString(");\n");
        }
    }
    return aResult;
}


FString	UMainWorkspace::ExportPassLinkTracking(UNode *pNode)
{
    FString aResult = "";
    
    FList aList;
    FString aString = "";
    
    if(pNode)
    {
        FString aOffsetString = "";
        
        if((pNode->mTrackingOffsetX != 0.0f) || (pNode->mTrackingOffsetY != 0.0f))
        {
            aOffsetString += FString(pNode->mTrackingOffsetX) + FString(", ") + FString(FString(pNode->mTrackingOffsetY));
        }
        
        
        
        
        if((pNode->mParent != 0) && (pNode->mTrackingType == NODE_TRACK_OBJ))
        {
            if((gRand.GetBool()) && (pNode->mExportAddTarget == pNode->mParent))
            {
                aString = FString("TrackTargetSetParent(");
            }
            else
            {
                aString = FString("TrackTargetSetObject(") + FString(pNode->mParent->mExportName) + FString(", ");
            }
            
            aString += aOffsetString + FString(")");
            aList += new FString(aString);
        }
        else if(pNode->mTrackingType == NODE_TRACK_SCREEN)
        {
            aString = FString("TrackTargetSetScreen(") + FString(pNode->mTrackingSideX) + FString(", ") + FString(FString(pNode->mTrackingSideY));
            
            if((pNode->mTrackingOffsetX != 0.0f) || (pNode->mTrackingOffsetY != 0.0f))
            {
                aString += FString(", ") + FString(pNode->mTrackingOffsetX) + FString(", ") + FString(FString(pNode->mTrackingOffsetY));
            }
            aString += FString(");");
            aList += new FString(aString);
        }
    }
    
    aResult += ExportApplyActions(pNode, &aList);
    return aResult;
}


FString	UMainWorkspace::ExportPassFinalize(UNode *pNode)
{
    FString aResult = "";FString aString="";FList aList;
    if(pNode)
    {
        if(pNode->mExportAddTarget == 0)
        {
            //aResult += FString("Finalize(");
            //+ FString(pNode->mExportName) +//
            //aResult += FString(");");
            
        }
        
        aList += new FString("Finalize(pX, pY)");
    }
    aResult += ExportApplyActions(pNode, &aList);
    return aResult;
}

int UMainWorkspace::ExportPrepare(UNode *pNode, int pIndex)
{
	int aResult = pIndex;
	if(pNode != 0)
	{
		if(pNode->mDidExport == false)
		{
			pNode->mExportIndex = aResult;
			aResult++;

			int aTabs = pNode->mExportDepth;

			while (aTabs >= 0)
			{
				aTabs--;
			}

			pNode->ExportGenerateNames();
			pNode->mDidExport = true;

            
            if(pNode->mParent)
            {
                pNode->mExportAddTarget = pNode->mParent;
            }
            else
            {
                pNode->mExportAddTarget = 0;
                
            }
            //mExportAddTarget
            
            
            
            
			FList aNext;

			EnumList(UNode, aNode, mNodeList)
			{
				if((aNode->mDidExport == false) && (aNode->mParent == pNode))
				{
					if(aNode->mExportDepth == -1)
					{
						//aNode->mExportParentName = pNode->ExportGetName();
						pNode->mExportSubnodes.Add(aNode);
						aNode->mExportDepth = pNode->mExportDepth + 1;
						aNext.Add(aNode);
					}
				}
			}

			EnumList(UNode, aNode, aNext)
			{
				aResult = ExportPrepare(aNode, aResult);
			}

			aNext.Clear();
		}
	}

	return aResult;
}



FString	UMainWorkspace::ExportApplyActions(UNode *pNode, FList *pList)
{
    FString aResult = "";
    FString aName = "mUnknown";
    
    if(pNode)aName = pNode->mExportName;
    
    if(pList)
    {
        EnumList(FString, aString, *pList)
        {
            aResult += aName;
            aResult += "->";
            
            FString aActionString = aString->c();
            if(aActionString.EndsWith(";") == false)aActionString += ";";
            if(aActionString.EndsWith("\n") == false)aActionString += "\n";
            
            aResult += FString(aActionString);
        }
    }
    
    FreeList(FString, (*pList));
    return aResult;
}

/*
FString	UNode::ExportString()
{
	FString aResult = "";
	FString aName = ExportGetName();



	FString aType = "Node";




	FString aVariableType = FString("FMotionObject");
	FString aVariableName = FString("m") + FString(mExportName.c());

	if(pNode->mParticleSource)
	{
		aType = "Particle";

	}


	aResult = aVariableType + FString(" *") + aVariableName + FString(" = new ") + aVariableType + FString("();\n");




	FList aStats;



	aStats += new UNodeExportStat("mRotation", mObject->mRotation);

	//aStats += new UNodeExportStat("mColor", mTemplate.mSpawnColor);


	EnumList(UNodeExportStat, aStat, aStats)
	{
		aResult += FString(aStat->Get()).c();
		delete aStat;
	}
	aStats.Clear();


	aResult += ExportColorString("mColor", mTemplate.mSpawnColor);




	return aResult;
}
*/


