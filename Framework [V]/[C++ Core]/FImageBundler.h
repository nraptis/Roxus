/*
*  FImageBundler.h
*  Ninja
*
*  Created by Nick Raptis on 4/26/11.
*  Copyright 2011 Nick Raptis. All rights reserved.
*
*/

#ifndef IMAGE_BUNDLER_H
#define IMAGE_BUNDLER_H

#define IMAGE_BUNDLER_GROUP_SAME_SIZE 0x0001
#define IMAGE_BUNDLER_GROUP_TILES 0x0002

#define BUNDLE_IMG_PREFIX "BNDL_IMG_"
#define BUNDLE_DATA_PREFIX "BNDL_DAT_"


#include "FImage.h"
#include "FString.h"
#include "FList.h"

//TODO: Add width skips..

class FImageBundlerSaveNode
{
    
public:
	
	FImageBundlerSaveNode();
	~FImageBundlerSaveNode();
    
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
    
    bool                mPlaced;
    
    FImage              *mImageQuadrupleRez;
    FImage              *mImageDoubleRez;
	FImage				*mImage;
	FString				mName;
};


class FImageBundlerLoadNode
{
public:
    
	FImageBundlerLoadNode();
	~FImageBundlerLoadNode();
    
    FImageBundlerLoadNode           *Clone();
    
	int                             mX;
	int                             mY;
    
	int                             mWidth;
	int                             mHeight;
	
    int                             mOffsetX;
	int                             mOffsetY;
	
	int                             mOriginalWidth;
	int                             mOriginalHeight;
    
    float                           mSpriteLeft;
    float                           mSpriteRight;
    float                           mSpriteTop;
    float                           mSpriteBottom;
    
    float                           mSpriteUStart;
    float                           mSpriteUEnd;
    
    float                           mSpriteVStart;
    float                           mSpriteVEnd;
    
    float                           mSpriteWidth;
    float                           mSpriteHeight;
    
    bool                            mRotated;
    
	FString                         mName;
};

class FImageBundler
{
    
public:
	
	FImageBundler();
	~FImageBundler();
	
	void                            AddImage(FImage *pImage);
	void                            AddNode(FImageBundlerSaveNode *pNode);
	FImageBundlerLoadNode           *FetchNode(char *pName);
    
    
    void                            ExportChunksWithCropData();
    
    FList                           mSaveNodeList;
    FList                           mLoadNodeList;
	
	//The edge border only applies to the edges of the entire splat,
	//which ignore mBorder.
	int                             mEdgeBorder;
	
	//The number of border pixels between each tile on the splat,
	//except for edges, see above.
	int                             mBorder;
	
	
	//This is basically for edge bleeding fixers, like a duplicated
	//ring of pixels so opengl can blend tiles more sexy.
	int                             mInset;
    
    
    bool                            mDidLoad;
    
    bool                            mTileMode;
    int                             mTileBorderSize;
    
    bool                            mAutoBundle;
    bool                            mMultiRez;
    
    bool                            mLoadSequential;
    int                             mSequentialLoadIndex;
    
    int                             mSequenceStartIndex;
    int                             mSequenceEndIndex;
    
    bool                            mRotationEnabled;
    
    bool                            mModelMode;
    
    bool                            mSeamlessBorders;
	
    int                             mBundleWidth;
    int                             mBundleHeight;
    
    float                           mBundleScale;
    
    
	int                             mSplatArea;
    
    int                             mTextureWidth;
    int                             mTextureHeight;
    
    int                             mSpacingRadix;
	
	bool                            mSuccess;
    
    bool                            mScreenCenter;
	
	FImage                          mImage;
    
    void                            Clear();
	
	void                            Save(char *pName);
	inline void                     Save(const char *pName){Save((char*)pName);}
	inline void                     Save(FString pName){Save((char*)pName.c());}
    
	void                            Load(char *pName);
	inline void                     Load(const char *pName){Load((char*)pName);}
	inline void                     Load(FString pName){Load((char*)pName.c());}
    
    void                            Load(const char *pFileName, const char *pImageName);
    
    
    void                            LoadBundle(const char *pFileXML);
    
    
    void                            StartBundle(const char *pBundleName);
    void                            EndBundle();
    FString                         mBundleName;
    
    static bool                     SliceUpBundle(FImage *pImage, FList *pImageList, int pTolerance=3);
    static bool                     FindSequenceCrop(FList *pFileList, int &pCropX, int &pCropY, int &pCropWidth, int &pCropHeight);
    
    
	
};

extern FImageBundler gImageBundler;

#endif



