#include "Canvas.h"
#include "Application.h"
#include "stdafx.h"

Canvas::Canvas()
{
	mRoot=false;
	mParent=0;
	
	mOffsetX=0;
	mOffsetY=0;
	
	mRegisterAllTouch=false;
	mRegisterAllRelease=false;
	mRegisterAllDrag=false;
	
	mIsButton=false;
	mIsButtonOver=false;
    
    mUpdateReceived=false;
	
	Size(0,0,gAppWidth,gAppHeight);
}

Canvas::~Canvas()
{
    gApp->mKillChildren -= this;
    gApp->mChildren -= this;
    
	//printf("Canvas Delete [%x]\n",this);
	//FreeList(Canvas, mChildren);
	
    if(gApp->mTarget==this)
	{
		gApp->mTarget=0;
	}
}

void Canvas::SetPos(float x, float y)
{
	mX=x;
	mY=y;
}

/*
void Canvas::DeleteCanvas(Canvas *pCanvas)
{
	if(mChildren.Exists(pCanvas))
	{
		RemoveChild(pCanvas);
		delete pCanvas;
	}
}
*/

bool Canvas::IsOver(int x, int y)
{
	return x >= 0 && y >= 0 && x <= mWidth && y<= mHeight;
}

Canvas *Canvas::GetTop(int x, int y, int &pTopX, int &pTopY)
{
	Canvas *aReturn=0;
	
	pTopX+=mX;
	pTopY+=mY;
	
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		aReturn=aCanvas->GetTop(x-aCanvas->mX,y-aCanvas->mY,pTopX,pTopY);
		if(aReturn)
		{
			return aReturn;
		}
	}
	if(IsOver(x,y))
	{
		aReturn=this;
	}
	else
	{
		pTopX-=mX;
		pTopY-=mY;
	}
	return aReturn;
}

void Canvas::BaseTouch(int x, int y)
{
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		if(aCanvas->IsOver(x-aCanvas->mX,y-aCanvas->mY))
		{
			aCanvas->BaseTouch(x-aCanvas->mX,y-aCanvas->mY);
			if(!mRegisterAllTouch)return;
		}
	}
	mMouseX=x;
	mMouseY=y;
	mMouseXf=(float)x;
	mMouseYf=(float)y;
	Touch(x,y);
}

void Canvas::BaseRelease(int x, int y)
{
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		if(aCanvas->IsOver(x-aCanvas->mX,y-aCanvas->mY))
		{
			aCanvas->BaseRelease(x-aCanvas->mX,y-aCanvas->mY);
			return;
		}
	}
	mMouseX=x;
	mMouseY=y;
	mMouseXf=(float)x;
	mMouseYf=(float)y;
	Release(x,y);
}

void Canvas::BaseDrag(int x, int y)
{
    
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		if(x>=aCanvas->mX&&x<=aCanvas->mX+aCanvas->mWidth&&
		   y>=aCanvas->mY&&y<=aCanvas->mY+aCanvas->mHeight)
		{
			aCanvas->BaseDrag(x-aCanvas->mX,y-aCanvas->mY);
			return;
		}
	}
    
	mMouseX=x;
	mMouseY=y;
	
    mMouseXf=(float)x;
	mMouseYf=(float)y;	
	
    Drag(x,y);
    
}

void Canvas::BaseUpdate()
{
    mUpdateReceived=true;
	Update();
	EnumList(Canvas, aCanvas, mChildren)aCanvas->BaseUpdate();
}

void Canvas::BaseDraw(float pTranslateX, float pTranslateY)
{
    if(mUpdateReceived)
    {
        //glPushMatrix();
        Translate(mX,mY);
        //Clip(mX+pTranslateX,mY+pTranslateY,mWidth,mHeight);
        Draw();
        EnumList(Canvas, aCanvas, mChildren)aCanvas->BaseDraw(pTranslateX+mX,pTranslateY+mY);
        Translate(-mX,-mY);
        //glPopMatrix();
    }
}

void Canvas::BaseDrawOver(float pTranslateX, float pTranslateY)
{
	//glPushMatrix();
	Translate(mX,mY);
	//Clip(mX+pTranslateX,mY+pTranslateY,mWidth,mHeight);
	DrawOver();
	EnumList(Canvas, aCanvas, mChildren)aCanvas->BaseDrawOver(pTranslateX+mX,pTranslateY+mY);
	Translate(-mX,-mY);
	//glPopMatrix();
}

void Canvas::Size(int x, int y, int pWidth, int pHeight)
{
	mX=x;
	mY=y;
	mWidth=pWidth;
	mHeight=pHeight;
}

void Canvas::Fill(Color pColor)
{
	SetColor(pColor);
	DrawRect(0,0,mWidth,mHeight);
}

bool Canvas::Exists(Canvas *pCanvas)
{
	if(pCanvas==this)return true;
	EnumList(Canvas,aCanvas,mChildren)
	{
		if(aCanvas->Exists(pCanvas))return true;
	}
	return false;
}

void Canvas::Kill()
{
	gApp->DeleteCanvas(this);
    if(mParent)
    {
        mParent->RemoveChild(this);
        mParent=0;
    }
    
    EnumList(Canvas, aChild, mChildren)
    {
        //aChild->mParent=0;
        //aChild->Kill();
    }
    
    mChildren.Clear();
}

void Canvas::GoInactive()
{
    EnumList(Canvas,aCanvas,mChildren)aCanvas->GoInactive();
}

void Canvas::GoActive()
{
    EnumList(Canvas,aCanvas,mChildren)aCanvas->GoActive();
}

void Canvas::AddSubcanvas(Canvas *pCanvas)
{
    if(pCanvas)
    {
    if(mChildren.Exists(pCanvas))
    {
        mChildren.MoveToFront(pCanvas);
    }
    else
    {
        mChildren+=pCanvas;pCanvas->mParent=this;
    }
    }
}

