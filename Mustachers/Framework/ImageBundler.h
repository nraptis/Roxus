/*
*  ImageBundler.h
*  Ninja
*
*  Created by Nick Raptis on 4/26/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#ifndef IMAGE_BUNDLER_H
#define IMAGE_BUNDLER_H

#define IMAGE_BUNDLER_GROUP_SAME_SIZE 0x0001
#define IMAGE_BUNDLER_GROUP_TILES 0x0002

#include "Image.h"
#include "FString.h"
#include "List.h"

class ImageBundlerSaveNode
{
    
public:
	
	ImageBundlerSaveNode();
	~ImageBundlerSaveNode();
    
    void                Rotate();
    void                Unrotate();
    
	int					mX;
	int					mY;
	
	int					mWidth;
	int					mHeight;
	
    int					mOffsetX;
	int					mOffsetY;
	
	int					mOriginalWidth;
	int					mOriginalHeight;
    
	int					mArea;
    
    int                 mInset;
    
    bool                mRotated;
    bool                mCanRotate;
    bool                mScreenCenter;
    
    bool                mPlaced;
    
    Image               *mImageQuadrupleRez;
    Image               *mImageDoubleRez;
	Image				*mImage;
	FString				mName;
};


class ImageBundlerLoadNode
{
public:
    
	ImageBundlerLoadNode();
	~ImageBundlerLoadNode();
    
    ImageBundlerLoadNode        *Clone();
    
	int                         mX;
	int                         mY;
	
    int                         mBundleWidth;
	int                         mBundleHeight;
    
	int                         mWidth;
	int                         mHeight;
	
    int                         mOffsetX;
	int                         mOffsetY;
	
	int                         mOriginalWidth;
	int                         mOriginalHeight;
    
    
    float                       mSpriteLeft;
    float                       mSpriteRight;
    float                       mSpriteTop;
    float                       mSpriteBottom;
    
    float                       mSpriteUStart;
    float                       mSpriteUEnd;
    
    float                       mSpriteVStart;
    float                       mSpriteVEnd;
    
    float                       mSpriteWidth;
    float                       mSpriteHeight;
    
    bool                        mRotated;
    
    bool                        mScreenCenter;
    
	FString                     mName;
};

class ImageBundler
{
    
public:
	
	ImageBundler();
	~ImageBundler();
	
	void						AddImage(Image *pImage);
	void						AddNode(ImageBundlerSaveNode *pNode);
	ImageBundlerLoadNode        *FetchNode(char *pName);
    
    
    void                        ExportChunksWithCropData();
    
    List                        mSaveNodeList;
    List                        mLoadNodeList;
	
	//The edge border only applies to the edges of the entire splat,
	//which ignore mBorder.
	int							mEdgeBorder;
	
	//The number of border pixels between each tile on the splat,
	//except for edges, see above.
	int							mBorder;
	
	
	//This is basically for edge bleeding fixers, like a duplicated
	//ring of pixels so opengl can blend tiles more sexy.
	int							mInset;
    
    
    bool                        mTileMode;
    int                         mTileBorderSize;    
    
    bool                        mAutoBundle;
    bool                        mMultiRez;
    
    bool                        mLoadSequential;
    int                         mSequentialLoadIndex;
    
    bool                        mRotationEnabled;
    
    bool                        mModelMode;
	
	int							mSplatWidth;
	int							mSplatHeight;
	int							mSplatArea;
	
	bool						mSuccess;
    
    bool                        mScreenCenter;
	
	Image						mImage;
    
    void                        Clear();
	
	void						Save(char *pName);
	inline void					Save(const char *pName){Save((char*)pName);}
	inline void					Save(FString pName){Save((char*)pName.c());}
	
	void						Load(char *pName);
	inline void					Load(const char *pName){Load((char*)pName);}
	inline void					Load(FString pName){Load((char*)pName.c());}
    
    void                        StartBundle(const char *pBundleName);
    void                        EndBundle();
    FString                     mBundleName;
	
};


#endif



