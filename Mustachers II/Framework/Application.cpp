#include "Application.h"
#include "Include.h"
#include "OCInlets.h"

int gAppWidth=320.0f;
int gAppHeight=480.0f;
float gAppWidth2=((float)gAppWidth/2.0f);
float gAppHeight2=((float)gAppHeight/2.0f);
float gGlobalScale=1.0f;
bool gIsIpad=false;
bool gDoubleRez=false;


float gTestSlide1=0.35f;
float gTestSlide2=0.25f;
float gTestSlide3=0.15f;

int gTestIndex1=0;
int gTestIndex2=0;
int gTestIndex3=0;

bool gTestFlag1=false;
bool gTestFlag2=false;
bool gTestFlag3=false;

ImageBundler gImageBundler;

Application *gApp;
Randomizer gRand;
FString gSandbox;
FString gDocuments;

Application::Application()
{
	char aPath[1024];
    
	mPurchased = false;
    mLoadComplete = false;
    mSnapPicture = false;
    mActive = true;
    
#ifdef DISABLE_BULLSHIT
    mPurchased = true;
#endif
    
	mImageBundle=0;
    
	mStopUpdates=0;
	mStopDraws=0;
    
	mPendingHTTPPosts=0;
    
	mAdHeight=0;
    
	GetBundleDirectory(aPath);
	gSandbox=aPath;
	gSandbox+='/';
	
    
	GetDocumentsDirectory(aPath);
	gDocuments=aPath;
	gDocuments+='/';
	
	
	mBindList=0;
	mBindCountList=0;
	mBindListSize=0;
	mBindListCount=0;
	
    
    mMouseX=gAppWidth/2;
	mMouseY=gAppHeight/2;
	
    
	mTarget=0;
	mTargetX=0;
	mTargetY=0;
    
	mOrientation=0;
	mPreviousOrientation=0;
    
	mAudioInitialized=false;
    
	mMusicVolume=1.0f;
	mSoundVolume=1.0f;
	mMusicOn=true;
	mOptionsMusicOn=true;
	mSoundOn=true;
	mOptionsSoundOn=true;
	mMusicOverride=false;
	
	mLoadStarted=0;
	mLoadComplete=0;
    
#ifndef DISABLE_OPEN_AL
    
	InitializeAudio();
    
#endif
    
    mMultiTouchData=0;
    mMultiTouchX=0;
    mMultiTouchY=0;
    mMultiTouchCount=0;
    mMultiTouchSize=0;
    mMultiTouchTimer=0;
    
    mDrawing=false;
    
}

Application::~Application()
{
	PurgeAllTextures();
	FlushMultiTouch();
	
	//printf("Application DECON\n");
    
    
	/*
	for(int i=0;i<mBindListSize;i++)
	{
		if(mBindList[i]>0)
		{
			glDeleteTextures(1,(GLuint*)(&(mBindList[i])));
		}
	}
	
	delete[]mBindList;
	mBindList=0;
	mBindListSize=0;
    */
    
    
}

void Application::InitializeAudio()
{
	if(mAudioInitialized)return;
	mAudioInitialized=true;
	
	mDevice=alcOpenDevice(NULL) ;
    
    if(mDevice)
    {
        mContext=alcCreateContext(mDevice, NULL);
        alcMakeContextCurrent(mContext);
        
        ALfloat ListenerPos[]={0.0, 0.0, 0.0};
        ALfloat ListenerVel[]={0.0, 0.0, 0.0};
        ALfloat ListenerOri[]={0.0, 0.0, 0.0,  0.0, 1.0, 0.0};
        
        alListenerfv(AL_POSITION,ListenerPos);
        alListenerfv(AL_VELOCITY,ListenerVel);
        alListenerfv(AL_ORIENTATION,ListenerOri);
    }
}



void Application::BaseDraw()
{
	mDrawing=true;
	if(!mStopDraws && mLoadComplete)
	{
	
		/*
		if(mLoadStarted==0)
		{
			mLoadStarted=1;		
			pthread_attr_t  aAttr;
			pthread_t aPosixThreadID;
			assert(!pthread_attr_init(&aAttr));
			assert(!pthread_attr_setdetachstate(&aAttr, PTHREAD_CREATE_DETACHED));
			pthread_create(&aPosixThreadID, &aAttr, &LoadController, this);
			assert(!pthread_attr_destroy(&aAttr));
		}
		 */
		
		//ClearBuffer();
		Draw();
		EnumList(Canvas,aCanvas,mChildren)aCanvas->BaseDraw(0,0);
		DrawOver();
		EnumList(Canvas,aCanvas,mChildren)aCanvas->BaseDrawOver(0,0);
		DrawTop();
		//if(mLoadProgressTicks>0)DrawLoading();
		//glBindTexture(GL_TEXTURE_2D,-1);
	}
    mDrawing=false;
}


void Application::BaseTouch(int x, int y)
{
	mTarget=0;
	mTargetX=0;
	mTargetY=0;
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		mTarget=aCanvas->GetTop(x-aCanvas->mX,y-aCanvas->mY,mTargetX,mTargetY);
		if(mTarget)
		{
			mTarget->Touch(x-mTargetX,y-mTargetY);
			return;
		}
	}
	
	/*
	Canvas *aCurrent=0;
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		aCurrent=aCanvas->GetTop(x-aCanvas->mX,y-aCanvas->mY);
		if(aCurrent)
		{
			if(mTarget!=0 && mTarget != aCurrent)
			{
				mTarget->Release(-1000,-1000);
			}
			mTarget=aCurrent;
			break;
		}
	}
	
	
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		if(x>=aCanvas->mX&&x<=aCanvas->mX+aCanvas->mWidth&&
		   y>=aCanvas->mY&&y<=aCanvas->mY+aCanvas->mHeight)
		{
			aCanvas->BaseTouch(x-aCanvas->mX,y-aCanvas->mY);
			return;
		}
	}
	 */
	
	Touch(x,y);
}

void Application::BaseRelease(int x, int y)
{
	if(mTarget)
	{
		mTarget->Release(x-mTargetX,y-mTargetY);
		return;
	}
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		if(x>=aCanvas->mX&&x<=aCanvas->mX+aCanvas->mWidth&&
		   y>=aCanvas->mY&&y<=aCanvas->mY+aCanvas->mHeight)
		{
			aCanvas->BaseRelease(x-aCanvas->mX,y-aCanvas->mY);
			return;
		}
	}
	Release(x,y);
}

void Application::BaseDrag(int x, int y)
{
	if(mTarget)
	{
		mTarget->Drag(x-mTargetX,y-mTargetY);
		return;
	}
	/*
	Canvas *aCurrent=0;
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		aCurrent=aCanvas->GetTop(x-aCanvas->mX,y-aCanvas->mY);
		if(aCurrent)
		{
			if(mTarget!=0 && mTarget != aCurrent)
			{
				bool aLive=false;
				
				EnumList(Canvas,aCheck,mChildren)
				{
					if(aCheck->Exists(mTarget))aLive=true;
				}
				
				if(aLive)
				{
				mTarget->Release(-1000,-1000);
				}
				else
				{
					//printf("HORRIBLE FUCK UP :( :( :(\n");
				}
			}
			mTarget=aCurrent;
			break;
		}
	}
	*/
	
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		if(x>=aCanvas->mX&&x<=aCanvas->mX+aCanvas->mWidth&&
		   y>=aCanvas->mY&&y<=aCanvas->mY+aCanvas->mHeight)
		{
			aCanvas->BaseDrag(x-aCanvas->mX,y-aCanvas->mY);
			return;
		}
	}
	
	
	Drag(x,y);
}

void Application::BaseUpdate()
{
    for(int i=0;i<mMultiTouchCount;i++)
    {
        mMultiTouchTimer[i]--;
        if(mMultiTouchTimer[i] <= 0)
        {
            BaseMultiRelease(mMultiTouchX[i], mMultiTouchY[i], mMultiTouchData[i]);
            break;
        }
    }
	
	if(!mStopUpdates && mLoadComplete)
	{
		Update();
		EnumList(Canvas,aCanvas,mChildren)aCanvas->BaseUpdate();
	}
    
    Canvas *aDeleteCanvas = 0;
    EnumList(Canvas, aCanvas, mKillChildren)
    {
        aCanvas->mKill--;
        if(aCanvas->mKill <= 0)
        {
            aDeleteCanvas = aCanvas;
            break;
        }
    }
    
    if(aDeleteCanvas)
    {
        //printf("Deleting Canvas[%x] (Count = %d)\n", aDeleteCanvas, mKillChildren.mCount);
        
        mKillChildren -= aDeleteCanvas;
        delete aDeleteCanvas;
    }
    
}

//Note: This will crash the app.
void Application::PurgeAllTextures()
{
	PrintBindList();
    
	for(int i=0;i<mBindListCount;i++)
    {
        Graphics::UnbindTexture(mBindList[i]);
    }
	
	delete[]mBindList;
	mBindList=0;
	
	delete[]mBindCountList;
	mBindCountList=0;
	
	mBindListSize=0;
	mBindListCount=0;
}

void Application::PrintBindList()
{
	printf("BindList[Count=%d Size=%d]={\n", mBindListCount, mBindListSize);
	for(int i=0;i<mBindListCount;i++)
	{
		printf("[c:%d i:%d]", mBindCountList[i], mBindList[i]);
		if(i < mBindListCount - 1)printf(", ");
	}
	//printf("\n};\n", mBindListCount, mBindListSize);
}

void Application::AddBind(int pIndex)
{
	for(int i=0;i<mBindListCount;i++)
	{
		if(mBindList[i] == pIndex)
		{
			mBindCountList[i]++;
			return;
		}
	}
	
	if(mBindListCount == mBindListSize)
	{
		mBindListSize = mBindListSize + mBindListSize / 2 + 1;
		int *aNewBindList = new int[mBindListSize];
		for(int i=0;i<mBindListCount;i++)
		{
			aNewBindList[i]=mBindList[i];
		}
		delete[]mBindList;
		mBindList=aNewBindList;
		
		int *aNewBindCountList = new int[mBindListSize];
		for(int i=0;i<mBindListCount;i++)
		{
			aNewBindCountList[i]=mBindCountList[i];
		}
		delete[]mBindCountList;
		mBindCountList=aNewBindCountList;
		
	}
    
	mBindList[mBindListCount] = pIndex;
	mBindCountList[mBindListCount] = 1;
	mBindListCount++;
}

void Application::RemoveBind(int pIndex)
{
	//printf("RemoveBind(%d/%d)\n", pIndex, mBindListSize);
	
	
	int aSlot=-1;
	
	for(int i=0;i<mBindListCount;i++)
	{
		if(mBindList[i] == pIndex)
		{
			aSlot=i;
			break;
		}
	}
	
	if(aSlot != -1)
	{
		mBindCountList[aSlot]--;
		
		if(mBindCountList[aSlot] <= 0)
		{
            Graphics::UnbindTexture(pIndex);
            
			int aCap=mBindListCount-1;
			
			for(int i=aSlot;i<aCap;i++)
			{
				mBindList[i]=mBindList[i+1];
				mBindCountList[i]=mBindCountList[i+1];
			}
			mBindListCount--;
			
			/*
			if(mBindListCount < mBindListSize / 4)
			{
				if(mBindListCount == 0)
				{
					delete[]mBindList;
					delete[]mBindCountList;
					
					mBindList=0;
					mBindCountList=0;
					
					mBindListCount=0;
					mBindListSize=0;
				}
				else
				{
					mBindListSize = mBindListSize / 2;
					int *aNewBindList = new int[mBindListSize];
					for(int i=0;i<mBindListCount;i++)
					{
						aNewBindList[i]=mBindList[i];
					}
					delete[]mBindList;
					mBindList=aNewBindList;
					
					int *aNewBindCountList = new int[mBindListSize];
					for(int i=0;i<mBindListCount;i++)
					{
						aNewBindCountList[i]=mBindCountList[i];
					}
					delete[]mBindCountList;
					mBindCountList=aNewBindCountList;
				}
			}
             */
		}
	}
}





void Application::BaseMultiTouch(int x, int y, void *pData)
{
    if(mMultiTouchCount==mMultiTouchSize)
    {
        mMultiTouchSize=mMultiTouchSize+mMultiTouchSize/1+1;
        
        void **aNewData=new void*[mMultiTouchSize];
        for(int i=0;i<mMultiTouchCount;i++)
        {
            aNewData[i]=mMultiTouchData[i];
        }
        delete[]mMultiTouchData;
        mMultiTouchData=aNewData;
		
        int *aNewX=new int[mMultiTouchSize];
        for(int i=0;i<mMultiTouchCount;i++)
        {
            aNewX[i]=mMultiTouchX[i];
        }
        
        delete[]mMultiTouchX;
        mMultiTouchX=aNewX;
        
        int *aNewY=new int[mMultiTouchSize];
        for(int i=0;i<mMultiTouchCount;i++)
        {
            aNewY[i]=mMultiTouchY[i];
        }
        delete[]mMultiTouchY;
        mMultiTouchY=aNewY;
        
        int *aNewTimer=new int[mMultiTouchSize];
        for(int i=0;i<mMultiTouchCount;i++)
        {
            aNewTimer[i]=mMultiTouchTimer[i];
        }
        delete[]mMultiTouchTimer;
        
        mMultiTouchTimer=aNewTimer;
    }
    
    mMultiTouchData[mMultiTouchCount]=pData;
    mMultiTouchX[mMultiTouchCount]=x;
    mMultiTouchY[mMultiTouchCount]=y;
    mMultiTouchTimer[mMultiTouchCount]=MULTI_TOUCH_AUTOFLUSH_TIMER;
    
    mMultiTouchCount++;
    
	MultiTouch(x, y, pData);
	
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		aCanvas->MultiTouch(x-aCanvas->mX,y-aCanvas->mY,pData);
	}
}
void Application::BaseMultiRelease(int x, int y, void *pData)
{
	MultiRelease(x, y, pData);
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		aCanvas->MultiRelease(x-aCanvas->mX,y-aCanvas->mY,pData);
	}
	
    int aIndex=-1;
    
    for(int i=0;i<mMultiTouchCount;i++)
    {
        if(mMultiTouchData[i] == pData)
        {
            aIndex=i;
        }
    }
    
    if(aIndex>=0)
    {
        for(int i=aIndex+1;i<mMultiTouchCount;i++)
        {
            mMultiTouchData[i-1]=mMultiTouchData[i];
            mMultiTouchX[i-1]=mMultiTouchX[i];
            mMultiTouchY[i-1]=mMultiTouchY[i];
            mMultiTouchTimer[i-1]=mMultiTouchTimer[i];
        }
        mMultiTouchCount--;
    }
}
void Application::BaseMultiDrag(int x, int y, void *pData)
{
    for(int i=0;i<mMultiTouchCount;i++)
    {
        if(mMultiTouchData[i] == pData)
        {
            mMultiTouchX[i]=x;
            mMultiTouchY[i]=y;
            mMultiTouchTimer[i]=MULTI_TOUCH_AUTOFLUSH_TIMER;
        }
    }
	
	MultiDrag(x, y, pData);
	
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		aCanvas->MultiDrag(x-aCanvas->mX,y-aCanvas->mY,pData);
	}
}

void Application::BaseFlushMultiTouch()
{
    delete [] mMultiTouchX;
    delete [] mMultiTouchY;
    delete [] mMultiTouchData;
    
    mMultiTouchData=0;
    mMultiTouchX=0;
    mMultiTouchY=0;
    mMultiTouchCount=0;
    mMultiTouchSize=0;
	
	FlushMultiTouch();
	
	EnumListReverse(Canvas,aCanvas,mChildren)
	{
		aCanvas->FlushMultiTouch();
	}
}

float Application::MultiTouchCenterX()
{
	float aReturn=0;
	if(mMultiTouchCount > 0)
	{
		for(int i=0;i<mMultiTouchCount;i++)aReturn += mMultiTouchX[i];
		aReturn /= ((float)mMultiTouchCount);
	}
	return aReturn;
}

float Application::MultiTouchCenterY()
{
	float aReturn=0;
	if(mMultiTouchCount > 0)
	{
		for(int i=0;i<mMultiTouchCount;i++)aReturn += mMultiTouchY[i];
		aReturn /= ((float)mMultiTouchCount);
	}
	return aReturn;
}

float Application::MultiTouchDist()
{
	float aReturn=0;
	float aDiffX, aDiffY, aDist;
	if(mMultiTouchCount > 0)
	{
		for(int aStart=0,aEnd=mMultiTouchCount-1;aStart<mMultiTouchCount;aEnd=aStart++)
		{
			aDiffX = mMultiTouchX[aEnd]-mMultiTouchX[aStart];
			aDiffY = mMultiTouchY[aEnd]-mMultiTouchY[aStart];
			
			aDist = aDiffX * aDiffX + aDiffY * aDiffY;
			
			if(aDist > 0.25f)aDist = sqrtf(aDist);
			else aDist = 0;
			
			
			aReturn += aDist;
		}
		
		aReturn /= ((float)mMultiTouchCount);
		
		
	}
	return aReturn;
}

void Application::AddSubcanvas(Canvas *pCanvas)
{
	if(pCanvas)
	{
		pCanvas->mRoot=true;
		
		mChildren+=pCanvas;
	}
}

void Application::RemoveChild(Canvas *pCanvas)
{
	mChildren-=pCanvas;
}

void Application::DeleteCanvas(Canvas *pCanvas)
{
    if(pCanvas)
    {
        pCanvas->mKill = 25;
        RemoveChild(pCanvas);
        if(mKillChildren.Exists(pCanvas) == false)
        {
            mKillChildren.Add(pCanvas);
        }
    }
}

void Application::LoadStatic()
{
    
	Buffer aStaticBuffer;
	
    aStaticBuffer.Load("static.dat");
	
    if(aStaticBuffer.ReadInt()==54321)
	{
		mPendingHTTPPosts=aStaticBuffer.ReadInt();
		mMusicVolume=aStaticBuffer.ReadFloat();
		mSoundVolume=aStaticBuffer.ReadFloat();
		mSoundOn=aStaticBuffer.ReadBool();
		mMusicOn=aStaticBuffer.ReadBool();
		mPurchased=aStaticBuffer.ReadBool();
	}
    
#ifdef DISABLE_BULLSHIT
    mPurchased = true;
#endif
    
	mAchievementManager.Load();
	
    mPurchaseManager.Load();
    
}

void Application::SaveStatic()
{
	Buffer aStaticBuffer;
    
    aStaticBuffer.WriteInt(54321);
    
	aStaticBuffer.WriteInt(mPendingHTTPPosts);
	aStaticBuffer.WriteFloat(mMusicVolume);
	aStaticBuffer.WriteFloat(mSoundVolume);
	aStaticBuffer.WriteBool(mSoundOn);
	aStaticBuffer.WriteBool(mMusicOn);
	aStaticBuffer.WriteBool(mPurchased);
    
	aStaticBuffer.Save(gDocuments + "static.dat");
	
	mAchievementManager.Save();
	mPurchaseManager.Save();
}

void Application::SuccessfulPurchase(char* pId)
{
	//printf("Successful Payment: %s\n", pId);
}

void Application::FailPurchase(char* pId)
{
	//printf("Failed Payment: %s\n", pId);
}

void Application::CancelPurchase(char* pId)
{
	//printf("Cancel Payment: %s\n", pId);
}

void Application::FailHTTP(char *pURL)
{
	//printf("Application::FailHTTP(%s)\n", pURL);
}

void Application::SuccessfulHTTP(char *pURL)
{
	//printf("Application::SuccessfulHTTP(%s)\n", pURL);
}


void Application::DisplayAchievement(Achievement *pAchievement)
{
	//if(mRecentAchievements.mCount <= 25)
	mRecentAchievements += pAchievement;
}



/*
void Application::SetOrientation(int pOrientation)
{
	//printf("Set Orientation To: %d\n", pOrientation);
	
	if(mOrientation!=0)mPreviousOrientation=mOrientation;
	
	if(mOrientation==0)
	{
		if(pOrientation!=0)
		{
			mOrientation=pOrientation;
		}
	}
	else
	{
		if(pOrientation!=0)
		{
			mOrientation=pOrientation;
		}
	}
	
	if(mPreviousOrientation!=0 && mOrientation !=0 && mOrientation != mPreviousOrientation)OrientationChanged();
}
 */



void Application::LoadSpriteSequence(Sprite *pSpriteArray, const char *pBasePath, int pStartIndex, int pEndIndex, int pLeadingZeros)
{
	FString aBasePath = FString(pBasePath);
	FString aNumberString;// = FString(i);
	//String aExtention = FString(".") + FString(pType);
	FString aFile;
	int aIndex=0;
	for(int i=pStartIndex;i<=pEndIndex;i++)
	{
		aNumberString = FString(((int)i));
		int aLengthDifference = pLeadingZeros - aNumberString.mLength;
		if(aLengthDifference > 0)aNumberString.Insert('0', aLengthDifference, 0);
		aFile.Write(aBasePath,0);
		aFile.Write(aNumberString,aBasePath.mLength);
		//aFile.Write(aExtention,aBasePath.mLength + aNumberString.mLength);
		pSpriteArray[aIndex].Load(aFile.c());
		aIndex++;
	}
}



void Application::LoadImageSequence(Image *pImageArray, const char *pBasePath, int pStartIndex, int pEndIndex, int pLeadingZeros)
{
	FString aBasePath = FString(pBasePath);
	FString aNumberString;// = FString(i);
	
    //String aExtention = FString(".") + FString(pType);
    
	FString aFile;
	
	int aIndex=0;
	for(int i=pStartIndex;i<=pEndIndex;i++)
	{
		aNumberString = FString(i);
		int aLengthDifference = pLeadingZeros - aNumberString.mLength;
		if(aLengthDifference > 0)aNumberString.Insert('0', aLengthDifference, 0);
		aFile.Write(aBasePath,0);
		aFile.Write(aNumberString,aBasePath.mLength);
		//aFile.Write(aExtention,aBasePath.mLength + aNumberString.mLength);
		pImageArray[aIndex].Load(aFile.c());
		aIndex++;
	}
}

void Application::GoInactive()
{
    printf("\n[[Inactive]]\n");
    mActive=false;
    EnumList(Canvas,aCanvas,mChildren)aCanvas->GoInactive();
    FlushMultiTouch();
}

void Application::GoActive()
{
    printf("\n[[Active]]\n");
    mActive=true;
    EnumList(Canvas,aCanvas,mChildren)aCanvas->GoActive();
}
