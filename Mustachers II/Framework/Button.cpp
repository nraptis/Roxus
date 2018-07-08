#include "Button.h"
#include "Image.h"
#include "Sprite.h"
#include "Font.h"
#include "Application.h"


ButtonLayer::ButtonLayer()
{
    mSprite[0] = 0;
    mSprite[1] = 0;
    mSprite[2] = 0;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
}

ButtonLayer::~ButtonLayer()
{
    mSprite[0] = 0;
    mSprite[1] = 0;
    mSprite[2] = 0;
}



Button::Button()
{
    
	mImage = 0;
    
	mSpriteCount = 0;
	mListener = 0;
	
    mData = 0;
    
    mDrawOver = 0;
	mPressed = 0;
	mOver = 0;
	mClicked = 0;
    
    mWidth = 0.0f;
    mHeight = 0.0f;
    
	mSprite[0]=0;
	mSprite[1]=0;
	mSprite[2]=0;
    
    mMultiTouch=false;
	
	mIsButton=true;
	mIsButtonOver=true;
	
    mTriggerOnDown=false;
    
	mDisableSound=false;
    
    mCheckBox=false;
    mCheckBoxState=false;
    
    mDrawManual=false;
	
	mOverSprite=0;
    
	mClickSound=0;
    
    //ButtonLayer
    
    
    mDragMode = false;
    
    mDragModeClicked = false;
    
    mDragModeMouseX = 0.0f;
    mDragModeMouseY = 0.0f;
    
    mDragModeOffseX = 0.0f;
    mDragModeOffseY = 0.0f;
    
    mDragModeTimer = 0;
}

Button::~Button()
{
	mSprite[0]=0;
	mSprite[1]=0;
	mSprite[2]=0;
    
    FreeList(ButtonLayer , mLayerList);
}

void Button::Setup(int x, int y, int pWidth, int pHeight, Canvas *pListener)
{
    mX=x;
	mY=y;
    
    mWidth=pWidth;
    mHeight=pHeight;
    
    if(pListener)
    {
        pListener->AddSubcanvas(this);
        AddListener(pListener);
    }
}

void Button::Setup(int x, int y, Sprite *pSpriteArray, int pSpriteCount, Canvas *pListener)
{
	mSpriteCount=pSpriteCount;
    
	for(int i=0;i<mSpriteCount;i++)
	{
		mSprite[i]=&(pSpriteArray[i]);
	}
    Setup(x, y, mSprite[0]->mWidth, mSprite[0]->mHeight, pListener);
}

void Button::Setup(int x, int y, Sprite *pSprite, Canvas *pListener)
{
    
    mSpriteCount=1;
    
    mSprite[0]=pSprite;
    
    Setup(x, y, pSprite->mWidth, pSprite->mHeight, pListener);
}

void Button::Setup(int x, int y, Sprite *pSprite)
{
    
    mSpriteCount=1;
    mSprite[0]=pSprite;
    
    
    Setup(x, y, pSprite->mWidth, pSprite->mHeight);
}

void Button::SetUpTopLeft(float pX, float pY, Canvas *pListener, bool pAutoSize)
{
    float aWidth = mWidth;
    float aHeight = mHeight;
    
    if(pAutoSize)
    {
        for(int i=0;i<3;i++)
        {
            if(mSprite[i])
            {
                if(mSprite[i]->mWidth > aWidth)aWidth = mSprite[i]->mWidth;
                if(mSprite[i]->mHeight > aHeight)aHeight = mSprite[i]->mHeight;
            }
        }
        
        EnumList(ButtonLayer, aLayer, mLayerList)
        {
            for(int i=0;i<3;i++)
            {
                if(aLayer->mSprite[i])
                {
                    if(aLayer->mSprite[i]->mWidth > aWidth)aWidth = aLayer->mSprite[i]->mWidth;
                    if(aLayer->mSprite[i]->mHeight > aHeight)aHeight = aLayer->mSprite[i]->mHeight;
                }
            }
        }
        
    }
    
    
    
    //float aX = (pX - (aWidth / 2.0f));
    //float aY = (pY - (aHeight / 2.0f));
    
    Setup(pX, pY, aWidth, aHeight, pListener);
    
}

void Button::SetUpCentered(float pX, float pY, Canvas *pListener, bool pAutoSize)
{
    float aWidth = mWidth;
    float aHeight = mHeight;
    
    if(pAutoSize)
    {
        for(int i=0;i<3;i++)
        {
            if(mSprite[i])
            {
                if(mSprite[i]->mWidth > aWidth)aWidth = mSprite[i]->mWidth;
                if(mSprite[i]->mHeight > aHeight)aHeight = mSprite[i]->mHeight;
            }
        }
        
        EnumList(ButtonLayer, aLayer, mLayerList)
        {
            for(int i=0;i<3;i++)
            {
                if(aLayer->mSprite[i])
                {
                    if(aLayer->mSprite[i]->mWidth > aWidth)aWidth = aLayer->mSprite[i]->mWidth;
                    if(aLayer->mSprite[i]->mHeight > aHeight)aHeight = aLayer->mSprite[i]->mHeight;
                }
            }
        }
        
    }
    
    
    
    float aX = (pX - (aWidth / 2.0f));
    float aY = (pY - (aHeight / 2.0f));
    
    Setup(aX, aY, aWidth, aHeight, pListener);
    
}


void Button::AddLayer(Sprite *pSprite1, Sprite *pSprite2, Sprite *pSprite3)
{
    ButtonLayer *aLayer = new ButtonLayer();
    
    aLayer->mSprite[0] = pSprite1;
    aLayer->mSprite[1] = pSprite2;
    aLayer->mSprite[2] = pSprite3;
    
    mLayerList += aLayer;
}

void Button::AddLayer(Sprite &pSprite1, Sprite &pSprite2, Sprite &pSprite3)
{
    AddLayer(&(pSprite1), &(pSprite2), &(pSprite3));
}

void Button::AddLayer(Sprite &pSprite1, Sprite &pSprite2)
{
    AddLayer(&(pSprite1),&(pSprite2),0);
}

void Button::AddLayer(Sprite &pSprite1)
{
    AddLayer(&(pSprite1),0,0);
}

bool Button::IsOver(int x, int y)
{
    
	bool aReturn = false;
    
	if(x >= 0 && y >= 0 && x <= mWidth && y<= mHeight)
	{
		if(mImage)
		{
			if(mImage->GetAlpha(x,y)>16)
			{
				aReturn=true;
			}
		}
		else
		{
			aReturn=true;
		}
	}
	return aReturn;
}

void Button::Touch(int x, int y)
{
    if(mMultiTouch)return;
    
	mPressed=false;
	mClicked=false;
	
	if(IsOver(x,y))
	{
        
        if(mDragMode)
        {
            mDragMode = false;
            
            mDragModeClicked = true;
            
            mDragModeTimer=0;
            
            mDragModeMouseX=x;
            mDragModeMouseY=y;
            
            mDragModeOffseX=mX;
            mDragModeOffseY=mY;
            
        }
        
        else
        
        {
            mPressed=true;
            mClicked=true;
            if(mDisableSound==false)
            {
                if(mClickSound)mClickSound->Play();
                else gApp->mSoundGlobalButtonClick.Play();
            }
            
            if((mTriggerOnDown == true) && (mListener != 0))
            {
                mListener->Notify(this);
            }
        } 
	}
    
	Drag(x,y);
}

void Button::Release(int x, int y)
{
    if(mMultiTouch)return;
    
#ifdef BUTTON_SETUP
    
    printf("Button Position [%d %d]\n", (int)mX, (int)mY);
    
#endif
    
	if(mPressed)
	{
        
		mClicked=0;
		mPressed=0;
        
		if(IsOver(x,y))
		{
            
#ifdef BUTTON_SETUP
            if(mDragTimer > 6)return;
#endif
            
            if(mCheckBox)
            {
                mCheckBoxState=!mCheckBoxState;
            }
            
            if((mTriggerOnDown == false) && (mListener != 0))
            {
                mListener->Notify(this);
            }
		}
		//for(int i=0;i<mListenerListCount;i++)mListener[i]->Notify(this);
	}
	else
	{
		mClicked=0;
		mPressed=0;
	}
}

void Button::Drag(int x, int y)
{
    if(mMultiTouch)return;
    
	mPressed=false;
	
	if(mClicked)
	{
        
		mPressed=IsOver(x,y);
        
        
        
        if(mDragMode)
        {
            if(mDragModeClicked)
            {
                mX = mDragModeOffseX - (mDragModeMouseX - x);
                mY = mDragModeOffseY - (mDragModeMouseY - y);
            }
        }
	}
    
	/*
    
	mPressed=false;
	if(mClicked)
	{
	if(mImage)
	{
		if(mImage->GetAlpha(x,y)>16)
		{
			mPressed=true;
		}
	}
	else
	{
		mPressed=true;
	}
	}
    
    */
}


void Button::MultiTouch(int x, int y, void *pData)
{
    if(mMultiTouch == false)return;
    
	if(IsOver(x - mX, y - mY))
	{
        mData = pData;
        
        mPressed=true;
        mClicked=true;
        
        if(mDisableSound==false)
        {
            if(mClickSound)mClickSound->Play();
            else gApp->mSoundGlobalButtonClick.Play();
        }
        
        if((mTriggerOnDown == true) && (mListener != 0))
        {
            mListener->Notify(this);
        }
	}
    else
    {
        if(mData == 0)
        {
            mPressed = false;
            mClicked = false;
        }
    }
    
	Canvas::MultiDrag(x, y, pData);
    
    //mData
}

void Button::MultiRelease(int x, int y, void *pData)
{
    if(mMultiTouch == false)return;
    
    if(pData == mData)
    {
        if(mPressed)
        {
            
            mClicked=0;
            mPressed=0;
            
            if(IsOver(x - mX, y - mY))
            {
                if(mCheckBox)
                {
                    mCheckBoxState=!mCheckBoxState;
                }
                if((mTriggerOnDown == false) && (mListener != 0))
                {
                    mListener->Notify(this);
                }
            }
        }
        else
        {
            mClicked=0;
            mPressed=0;
        }
        mData = 0;
    }
}

void Button::MultiDrag(int x, int y, void *pData)
{
    if(mMultiTouch == false)return;
    
    if(pData == mData)
    {
        mPressed=false;
        if(mClicked)
        {
            mPressed=IsOver(x - mX, y - mY);
            if(mDragMode)
            {
                if(mDragModeClicked)
                {
                    mX = mDragModeOffseX - (mDragModeMouseX - x);
                    mY = mDragModeOffseY - (mDragModeMouseY - y);
                }
            }
        }
    }
}

void Button::FlushMultiTouch()
{
    if(mMultiTouch == false)return;
    
    mData = 0;
    mClicked = false;
    mPressed = false;
}

void Button::BaseDraw(float pTranslateX, float pTranslateY)
{
    
    if(mUpdateReceived)
    {
        
        //glPushMatrix();
        
        Translate(mX,mY);
        
        //Clip(mX+pTranslateX,mY+pTranslateY,mWidth,mHeight);
        
        if(!mDrawManual && !mDrawOver)Draw();
        
        EnumList(Canvas, aCanvas, mChildren)aCanvas->BaseDraw(pTranslateX+mX,pTranslateY+mY);
        
        Translate(-mX,-mY);
        
        //glPopMatrix();
        
    }
    
}

void Button::BaseDrawOver(float pTranslateX, float pTranslateY)
{
	//glPushMatrix();
	Translate(mX,mY);
	//Clip(mX+pTranslateX,mY+pTranslateY,mWidth,mHeight);
	if(!mDrawManual && mDrawOver)Draw();
	EnumList(Canvas, aCanvas, mChildren)aCanvas->BaseDrawOver(pTranslateX+mX,pTranslateY+mY);
	Translate(-mX,-mY);
	//glPopMatrix();
}

void Button::DrawUntransformed()
{
    bool aPressed = mPressed;
    
    if(mCheckBox)
    {
        aPressed = mCheckBoxState;
    }
    
	if(aPressed)
	{
		if(mSpriteCount==1)
		{
            if(mSprite[0])mSprite[0]->Draw(0,0);
		}
		else if(mSpriteCount==2)
		{
			if(mSprite[1])mSprite[1]->Draw(0,0);
		}
		else
		{
			if(mSprite[2])mSprite[2]->Draw(0,0);
            else if(mSprite[1])mSprite[1]->Draw(0,0);
		}
	}
	/*else if(mOver)
     {
     if(mSpriteCount==3)
     {
     mSprite[1]->Draw(0,0);
     }
     else
     {
     mSprite[0]->Draw(0,0);
     }
     }
     */
	else
	{
        if(mSprite[0])mSprite[0]->Draw();
	}
    
    EnumList(ButtonLayer, aLayer, mLayerList)
    {
        Sprite *aSprite = aLayer->mSprite[0];
        
        if(mPressed)
        {
            if(aLayer->mSprite[1])
            {
                aSprite = aLayer->mSprite[1];
            }
        }
        if(aSprite)
        {
            aSprite->Draw();
        }
    }
    
	if(mOverSprite)
	{
		mOverSprite->Draw();
	}
}

void Button::Draw()
{
    
    
    //mDragModeOffseX = false;
    //mDragModeOffseY = true;
    
    //mDragModeTimer=0;
    
    //mDragModeMouseX=x;
    //mDragModeMouseY=y;
    
    //mDragModeOffseX=mX;
    //mDragModeOffseY=mY;
    
    
    
	if(mDrawOver)return;
    
    if(mDrawManual)Translate(mX,mY);
    
#ifdef BUTTON_SETUP
    mDragTimer++;
    if(mClicked)SetColor(1,1,1,0.5f);
#endif
    
    bool aPressed = mPressed;
    
    if(mCheckBox)
    {
        aPressed = mCheckBoxState;
    }
    
	if(aPressed)
	{
		if(mSpriteCount<=1)
		{
            SetColor(0.85f,0.85f,0.85f,1.0f);
            if(mSprite[0])mSprite[0]->Draw(0,0);
            SetColor();
		}
		else if(mSpriteCount==2)
		{
			if(mSprite[1])mSprite[1]->Draw(0,0);
		}
		else
		{
			if(mSprite[2])mSprite[2]->Draw(0,0);
            else if(mSprite[1])mSprite[1]->Draw(0,0);
		}
	}
	/*else if(mOver)
	{
		if(mSpriteCount==3)
		{
			mSprite[1]->Draw(0,0);
		}
		else
		{
			mSprite[0]->Draw(0,0);
		}
	}
    */
	else
	{
        if(mSprite[0])
        {
            //printf("DrawSpriteSize[%f %f]\n", mSprite[0]->mWidth, mSprite[0]->mHeight);
            mSprite[0]->Draw(0,0);
        }
	}
    
    EnumList(ButtonLayer, aLayer, mLayerList)
    {
        Sprite *aSprite = aLayer->mSprite[0];
        
        if(mPressed)
        {
            if(aLayer->mSprite[1])
            {
                aSprite = aLayer->mSprite[1];
            }
        }
        if(aSprite)
        {
            aSprite->Draw(aLayer->mOffsetX, aLayer->mOffsetY);
        }
    }
    
    
	if(mOverSprite)
	{
		mOverSprite->Center(mWidth/2,mHeight/2);
	}
    
    
    if(mDragMode)
    {
    
    SetColor(0,0,0,0.25f);
    DrawRect(0,0,mWidth,mHeight);
    
    SetColor(1,1,1,0.25f);
    OutlineRect(0,0,mWidth,mHeight,6);
        
    }
    
    if(mDrawManual)Translate(-mX,-mY);
}


void Button::SetDimensions(float pWidth, float pHeight)
{
	mWidth=pWidth;
	mHeight=pHeight;
}

void Button::AddListener(Canvas *pCanvas)
{
	mListener=pCanvas;
}



