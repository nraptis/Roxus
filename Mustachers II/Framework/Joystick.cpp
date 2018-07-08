#include "Joystick.h"

#include "stdafx.h"

Joystick::Joystick()
{
    mData=0;
    mCancelTimer=0;
    
    mCancelTimer=0;
    mData=0;
    
    mDirX=0;
    mDirY=0;
    mLength=0;
    
    mLengthSquared=0;
    
    mX=0.0f;
    mY=0.0f;
    
    mDiffMultX=1.0f;
    mDiffMultY=1.0f;
    
    mPercentX=0.0f;
    mPercentY=0.0f;
    
    mRotation=0.0f;
    mRotationJoystick=0.0f;
    
    mMaxDragLength=60.0f;
    
    mRotateBack=false;
    
    mKnobMoves=true;
    mBackRotates=false;
    
    mSpriteBackground=0;
    mSpriteKnob=0;
    
    SetRadius(100);
    
    mRotationJoystickStart=0.0f;
    mRotationStart=0.0f;
}

Joystick::~Joystick()
{
    
}

void Joystick::Update()
{
    if(mData)
    {
        /*
        mCancelTimer--;
        if(mCancelTimer <= 0)
        {
            mCancelTimer=0;
            mData=0;
            mLength=0;
            mDirX=0;
            mDirY=0;
        }
        */
    }
    else
    {
        mCancelTimer=0;
    }
}

void Joystick::Draw()
{
    if(mRotateBack)
    {
        if(mSpriteBackground)mSpriteBackground->Draw(mX, mY, 1.0f, mRotationJoystick);
    }
    else
    {
        if(mSpriteBackground)mSpriteBackground->Draw(mX, mY, 1.0f, 0.0f);
    }
    
    
    
    if(mSpriteKnob)
    {
        if(mKnobMoves)
        {
            mSpriteKnob->Center(mX + mDirX * mLength, mY + mDirY * mLength);
        }
        else
        {
            mSpriteKnob->Center(mX, mY);
        }
    }
}

bool Joystick::IsClicked()
{
    
    if(mData)return true;
    
    else return false;
    
}

void Joystick::MultiTouch(int x, int y, void *pData)
{
    
    float aDiffX = (x - mX);
    float aDiffY = (y - mY);
    
    float aLengthSquared = aDiffX * aDiffX + aDiffY * aDiffY;
    
    if(aLengthSquared < mRadiusSquared)
    {
        bool aHit=false;
        
        if(mData)
        {
            if(aLengthSquared < mLengthSquared)
            {
                aHit=true;
            }
        }
        else
        {
            aHit=true;
        }
        
        if(aHit)
        {
            mData = pData;
            
            MultiDrag(x, y, pData);
            
            /*
            mLengthSquared = aLengthSquared;
            
            if(mLengthSquared > 1)
            {
                mLength = sqrtf(mLengthSquared);
                mDirX = aDiffX / mLength;
                mDirY = aDiffY / mLength;
            }
            else
            {
                mLengthSquared = 0;
                mLength = 0;
                mDirX = 0;
                mDirY = 0;
            }
            
            if(mLength > mMaxDragLength)mLength=mMaxDragLength;
            
            mCancelTimer = JOYSTICK_CANCEL_TIME;
            
            
            mRotationJoystickStart = mRotationJoystick;
            mRotationStart = mRotation;
            
            mPercentX = (mDirX * mLength) / mMaxDragLength;
            mPercentY = (mDirY * mLength) / mMaxDragLength;
            */
        }
    }
}

void Joystick::MultiRelease(int x, int y, void *pData)
{
    if(pData == mData)
    {
        mData=0;
        mCancelTimer=0;
        mLength = 0;
        mDirX = 0.0f;
        mDirY = 0.0f;
        mPercentX = 0.0f;
        mPercentY = 0.0f;
    }
}

void Joystick::MultiDrag(int x, int y, void *pData)
{
    if(pData == mData)
    {
        float aDiffX = (x - mX);
        float aDiffY = (y - mY);
        
        aDiffX *= mDiffMultX;
        aDiffY *= mDiffMultY;
        
        float aLengthSquared = aDiffX * aDiffX + aDiffY * aDiffY;
        
        mLengthSquared = aLengthSquared;
        
        if(mLengthSquared > 1)
        {
            mLength = sqrtf(mLengthSquared);
            
            mDirX = aDiffX / mLength;
            mDirY = aDiffY / mLength;
            
            mRotation = //180.0f -
            FaceTarget(mDirX, mDirY);
            
            mRotationJoystick = mRotationJoystickStart + (mRotation - mRotationStart);
        }
        else
        {
            mLengthSquared = 0;
            mLength = 0;
            mDirX = 0;
            mDirY = 0;
        }
        
        if(mLength > mMaxDragLength)
        {
            mLength=mMaxDragLength;
        }
        
        mPercentX = (mDirX * mLength) / mMaxDragLength;
        mPercentY = (mDirY * mLength) / mMaxDragLength;
        
    }
}

void Joystick::FlushMultiTouch()
{
    mData=0;
    
    mCancelTimer=0;
    mLength = 0;
    mDirX = 0;
    mDirY = 0;
    
    mPercentX = 0.0f;
    mPercentY = 0.0f;
}




