/*
*   ImageBundler.cpp
*   Ninja
*
*   Created by Nick Raptis on 4/26/11.
*   Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "ImageBundler.h"
#include "Application.h"
#include "XML.h"

ImageBundler::ImageBundler()
{
	mEdgeBorder=2;
	mBorder=2;
	mInset=0;
    
    mMultiRez=false;
    
    mAutoBundle=false;
    
    mModelMode=false;
	
	mSplatWidth=0;
	mSplatHeight=0;
	mSplatArea=0;
    
    mTileBorderSize=2;
    mTileMode=false;
    
    mRotationEnabled=true;
	
	mSuccess=false;
    
    mLoadSequential=true;
    mSequentialLoadIndex=0;
    
}

ImageBundler::~ImageBundler()
{
	if(gApp)
    {
        if(gApp->mImageBundle == this)
        {
            gApp->mImageBundle=0;
        }
    }
    Clear();
}

void ImageBundler::Clear()
{
    FreeList(ImageBundlerSaveNode,mSaveNodeList);
    FreeList(ImageBundlerLoadNode,mLoadNodeList);
    
    mSequentialLoadIndex=0;
	
	mSplatWidth=0;
	mSplatHeight=0;
	mSplatArea=0;
	
	mSuccess=false;
	
	mImage.Kill();
    
}

void ImageBundler::AddImage(Image *pImage)
{
    
	if(!pImage)return;
	if(pImage->mWidth<=0||pImage->mHeight<=0)return;
    
    
    FString aPath = pImage->mPath;
    
    
    aPath.RemovePath(true);
    aPath.Replace("@2x", "");
    aPath.Replace("highrez", "");
    aPath.Replace("_hd", "");
    
    
    
    Image aDoubleRez;
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gSandbox + aPath + FString("_hd.png"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gSandbox + aPath + FString("_hd.jpg"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gSandbox + aPath + FString("_hd.jpeg"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gSandbox + aPath + FString("_hd.PNG"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gSandbox + aPath + FString("_hd.JPG"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gSandbox + aPath + FString("_hd.JPEG"));
    if(aDoubleRez.mWidth > 0)
    {
        if(aDoubleRez.mWidth != (pImage->mWidth * 2))printf("***\nWIDTH MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), pImage->mWidth, aDoubleRez.mWidth);
        if(aDoubleRez.mHeight != (pImage->mHeight * 2))printf("***\nHEIGHT MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), pImage->mHeight, aDoubleRez.mHeight);
    }
    else printf("No High Rez Image For [%s]\n", aPath.c());
    
    Image aQuadrupleRez;
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gSandbox + aPath + FString("_uhd.png"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gSandbox + aPath + FString("_uhd.jpg"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gSandbox + aPath + FString("_uhd.jpeg"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gSandbox + aPath + FString("_uhd.PNG"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gSandbox + aPath + FString("_uhd.JPG"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gSandbox + aPath + FString("_uhd.JPEG"));
    if(aQuadrupleRez.mWidth > 0)
    {
        if(aQuadrupleRez.mWidth != (pImage->mWidth * 4))printf("***\nWIDTH MISMATCH (%s) Low[%d] Ultra[%d]\n***\n", aPath.c(), pImage->mWidth, aQuadrupleRez.mWidth);
        if(aQuadrupleRez.mHeight != (pImage->mHeight * 4))printf("***\nHEIGHT MISMATCH (%s) Low[%d] Ultra[%d]\n***\n", aPath.c(), pImage->mHeight, aQuadrupleRez.mHeight);
    }
    else printf("No High Rez Image For [%s]\n", aPath.c());
    
    
    ImageBundlerSaveNode *aNode=new ImageBundlerSaveNode();
    AddNode(aNode);
    
    aNode->mName = aPath;
    
    aNode->mX=0;
	aNode->mY=0;
    
    aNode->mOriginalWidth=pImage->mWidth;
    aNode->mOriginalHeight=pImage->mHeight;
    
    aNode->mScreenCenter=mScreenCenter;
    
    
    if(mInset > 0)
    {
        
        //mInset);
        
        aNode->mImage = pImage->Clone();
        aNode->mImage->BufferEdges(mInset);
        aNode->mInset = mInset;
        
        aNode->mOffsetX = 0;
        aNode->mOffsetY = 0;
        
        aNode->mWidth = (aNode->mImage->mWidth);
        aNode->mHeight = (aNode->mImage->mHeight);
        
        aNode->mArea=aNode->mWidth*aNode->mHeight;
        
        //ExportPNGImage(pImage, , , )
        
        if(aDoubleRez.mWidth > 0)
        {
            aNode->mImageDoubleRez = aDoubleRez.Clone();
            aNode->mImageDoubleRez->BufferEdges(mInset * 2);
            
            //FString aPrefix = FString("/Users/nraptis/Desktop/Exports/");
            //ExportPNGImage(aNode->mImageDoubleRez->mData, FString(aPrefix + aPath + FString("_border_lol_double.png")).c(), aNode->mImageDoubleRez->mWidth, aNode->mImageDoubleRez->mHeight);
            
            aDoubleRez.Kill();
        }
        
        if(aQuadrupleRez.mWidth > 0)
        {
            aNode->mImageQuadrupleRez = aQuadrupleRez.Clone();
            aNode->mImageQuadrupleRez->BufferEdges(mInset * 4);
            
            //FString aPrefix = FString("/Users/nraptis/Desktop/Exports/");
            //ExportPNGImage(aNode->mImageQuadrupleRez->mData, FString(aPrefix + aPath + FString("_border_lol_quad.png")).c(), aNode->mImageQuadrupleRez->mWidth, aNode->mImageQuadrupleRez->mHeight);
            
            aQuadrupleRez.Kill();
        }
        
        //aNode->mIm
        
        //FString aPrefix = FString("/Users/nraptis/Desktop/Exports/");
        //ExportPNGImage(aNode->mImage->mData, FString(aPrefix + aPath + FString("_border_lol.png")).c(), aNode->mImage->mWidth, aNode->mImage->mHeight);
        
        return;
    }
    
    //pImage->FixTileBorders(20);
    
	int aLeft, aRight, aTop, aBottom, aWidth, aHeight;
	pImage->GetEdges(aLeft,aRight,aTop,aBottom);
    
    
    if(mModelMode)
    {
        
        aWidth = pImage->mWidth;
        aHeight = pImage->mHeight;
        
        aLeft = 0;
        aRight = (aWidth - 1);
        
        aTop = 0;
        aBottom = (aHeight - 1);
     
    }
    
    //int aStartLeft = aLeft;
    //int aStartRight = aRight;
    //int aStartTop = aTop;
    //int aStartBottom = aBottom;
    
    //int aStartWidth = (aStartRight - aStartLeft) + 1;
    //int aStartHeight = (aStartBottom - aStartTop) + 1;
    
    //aLeft -= mInset;
    //aTop -= mInset;
    
    //aRight += mInset;
    //aBottom += mInset;
    
    aWidth = aRight - aLeft + 1;
	aHeight = aBottom - aTop + 1;
    
    
    aNode->mWidth = aWidth;
	aNode->mHeight = aHeight;
    aNode->mArea=aNode->mWidth*aNode->mHeight;
    
	aNode->mOffsetX = aLeft;
	aNode->mOffsetY = aTop;
    
    /*
    if(mCurrentGroup)
    {
        mCurrentGroup->AddNode(aNode);
        
        if(mCurrentGroup->mGroupType == IMAGE_BUNDLER_GROUP_SAME_SIZE)
        {
            Image *aNewImage=new Image();
            aNewImage->MakeBlank(pImage->mWidth,pImage->mHeight);
            aNewImage->Stamp(pImage);
            aNewImage->mPath=pImage->mPath;
            aNewImage->mPath.RemovePath(true);
            aNode->mImage=aNewImage;
            
            return;
        }
    }
    
    */
    
    
    Image *aNewImage = 0;
    
    if(mModelMode)
    {
        aNewImage = pImage->Clone();
    }
    else
    {
        aNewImage = pImage->Crop(aLeft,aTop,aWidth,aHeight);
    }
    
    aNewImage->mPath=pImage->mPath;
    aNewImage->mPath.RemovePath(true);
    aNode->mImage=aNewImage;
    
    if(aDoubleRez.mWidth > 0)aNode->mImageDoubleRez=aDoubleRez.Crop(aLeft*2, aTop*2, aWidth*2, aHeight*2);
    else printf("No High Rez Image For [%s]\n", aNode->mName.c());
    
    if(aQuadrupleRez.mWidth > 0)aNode->mImageQuadrupleRez=aQuadrupleRez.Crop(aLeft*4, aTop*4, aWidth*4, aHeight*4);
    else printf("No High Rez Image For [%s]\n", aNode->mName.c());
}

void ImageBundler::AddNode(ImageBundlerSaveNode *pNode)
{
    mSaveNodeList += pNode;
}


void ImageBundler::ExportChunksWithCropData()
{
    XML aXML;
    
    FString aName;
    
    XMLTag *aRootTag = new XMLTag("image_crops");
    aXML.mRoot = aRootTag;
    
    XMLTag *aCropListTag = new XMLTag("crop_list");
    *aRootTag += aCropListTag;
    
    EnumList(ImageBundlerSaveNode, aSaveNode, mSaveNodeList)
    {
        aName = aSaveNode->mName;
        
        XMLTag *aCropTag = new XMLTag("crop");
        *aCropListTag += aCropTag;
        
        aCropTag->AddParam("offset_x", FString(aSaveNode->mOffsetX).c());
        aCropTag->AddParam("offset_y", FString(aSaveNode->mOffsetY).c());
        aCropTag->AddParam("name", aName.c());
        
        
        ExportPNGImage(aSaveNode->mImage->mData, FString(FString("Exports/") + FString(aName) + FString("_cropped.png")).c(), aSaveNode->mImage->mWidth, aSaveNode->mImage->mHeight);
        
    }
    
    aXML.Save( FString(FString("image_crop_data") + FString(".xml")));
    
}

void ImageBundler::Save(char *pName)
{
	mSuccess=false;
    
	int aTryWidth[32];
	int aTryHeight[32];
    
	aTryWidth[0]=256;aTryHeight[0]=256;
    
	aTryWidth[1]=512;aTryHeight[1]=256;
	aTryWidth[2]=256;aTryHeight[2]=512;
	aTryWidth[3]=512;aTryHeight[3]=512;
	
    
	aTryWidth[4]=1024;aTryHeight[4]=512;
	aTryWidth[5]=512;aTryHeight[5]=1024;
	aTryWidth[6]=1024;aTryHeight[6]=1024;
	
    
	aTryWidth[7]=2048;aTryHeight[7]=1024;
	aTryWidth[8]=1024;aTryHeight[8]=2048;
	aTryWidth[9]=2048;aTryHeight[9]=2048;
    
    
	aTryWidth[10]=4096;aTryHeight[10]=2048;
	aTryWidth[11]=2048;aTryHeight[11]=4096;
	aTryWidth[12]=4096;aTryHeight[12]=4096;
    
	ImageBundlerSaveNode *aNode, *aCheckNode;
    
    int aNodeCount=mSaveNodeList.mCount;
    ImageBundlerSaveNode **aArray = new ImageBundlerSaveNode*[mSaveNodeList.mCount+1];
    for(int i=0;i<aNodeCount;i++)
	{
        aArray[i]=(ImageBundlerSaveNode*)mSaveNodeList.Fetch(i);
	}
    
    int aLowRezCount=0;
    int aDoubleRezCount=0;
    int aQuadrupleRezCount=0;
    
    EnumList(ImageBundlerSaveNode, aSaveNode, mSaveNodeList)
    {
        aLowRezCount++;
        if(aSaveNode->mImageDoubleRez)
        {
            aDoubleRezCount++;
        }
        if(aSaveNode->mImageQuadrupleRez)
        {
            aQuadrupleRezCount++;
        }
        aSaveNode->mArea=aSaveNode->mWidth*aSaveNode->mHeight;
    }
    
    printf("\n***\nFound %d Images and %d High Rez\n***\n", aLowRezCount, aDoubleRezCount);
    
	for(int i=0;i<aNodeCount;i++)
	{
        aArray[i]=(ImageBundlerSaveNode*)mSaveNodeList.Fetch(i);
        aArray[i]->mArea=aArray[i]->mWidth*aArray[i]->mHeight;
	}
	
	
	//Sort By Area
	int aStart, aCheck;
	for(aStart=1; aStart<aNodeCount;aStart++)
	{
		aNode=aArray[aStart];
		aCheck=aStart-1;
		
		while(aCheck>=0 && aArray[aCheck]->mArea < aNode->mArea)
		{
			aArray[aCheck+1]=aArray[aCheck];
			aCheck--;
		}
		aArray[aCheck+1]=aNode;
	}
    
	int aNodeWidth, aNodeHeight;
	
	bool aNodePlaced;
	bool aIntersects;
    bool aCanRotate;
    bool aEdgeIntersect;
	
	for(int aSplatSizeIndex=0;aSplatSizeIndex<13;aSplatSizeIndex++)
	{
		mSplatWidth = aTryWidth[aSplatSizeIndex];
		mSplatHeight = aTryHeight[aSplatSizeIndex];
        
		printf("Trying Bundle [%d %d]\n", mSplatWidth, mSplatHeight);
        
        for(int i=0;i<aNodeCount;i++)
		{
			aArray[i]->mPlaced=false;
            aArray[i]->Unrotate();
        }
        
		for(int i=0;i<aNodeCount;i++)
		{
			aNode=aArray[i];
			aNodePlaced=false;
            
            for(int q=0;q<2&&(aNodePlaced==false);q++)
            {
                
                
                
                aNodeWidth=aNode->mWidth;
                aNodeHeight=aNode->mHeight;
                
                for(int aY=0;aNodePlaced==false && aY<=mSplatHeight-aNodeHeight;aY++)
                {
                    for(int aX=0;aNodePlaced==false && aX<=mSplatWidth-aNodeWidth;aX++)
                    {
                        aEdgeIntersect = ((aX+aNodeWidth >(mSplatWidth-mEdgeBorder))
                                          || (aY+aNodeHeight>(mSplatHeight-mEdgeBorder))
                                          || (aX<mEdgeBorder)
                                          || (aY<mEdgeBorder));
                        
                        if(aEdgeIntersect==false)
                        {
                            aIntersects=false;
                            for(int aCheckIndex=i-1;aCheckIndex>=0;aCheckIndex--)
                            {
                                aCheckNode = aArray[aCheckIndex];
                                
                                if(!((aX+aNodeWidth<=(aCheckNode->mX-mBorder))
                                     || (aY+aNodeHeight<=(aCheckNode->mY-mBorder))
                                     || (aX>=(aCheckNode->mX+aCheckNode->mWidth+mBorder))
                                     || (aY>=(aCheckNode->mY+aCheckNode->mHeight+mBorder))))
                                {
                                    aIntersects=true;
                                }
                            }
                            if(aIntersects == false)
                            {                        
                                aNode->mX=aX;
                                aNode->mY=aY;
                                aNodePlaced=true;
                            }
                        }
                    }
                }
            }
			if(aNodePlaced==false)
			{
				break;
			}
            else
            {
                aNode->mPlaced=true;
            }
		}
		
		mSuccess=true;
        
        int aHitCount=0;
        for(int i=0;i<aNodeCount;i++)
		{
            if(aArray[i]->mPlaced == false)
            {
                mSuccess = false;
            }
            else
            {
                aHitCount++;
            }
        }
        
        printf("Placed %d of %d nodes!\n", aHitCount, aNodeCount);
        
		if(mSuccess)
		{
			mImage.Kill();
            mImage.MakeBlank(mSplatWidth, mSplatHeight);
            
            Image aImageHigh;
            
            if(aDoubleRezCount > 0)
            {
                //aImageHigh.MakeBlank(mSplatWidth*2, mSplatHeight*2);
                //aImageHigh.Make(mSplatWidth*2, mSplatHeight*2,IMAGE_RGBA(0x00, 0xFF, 0x80, 0xFF));
                aImageHigh.MakeBlank(mSplatWidth*2, mSplatHeight*2);
            }
            
            
            Image aImageUltra;
            if(aQuadrupleRezCount > 0)
            {
                //aImageHigh.MakeBlank(mSplatWidth*2, mSplatHeight*2);
                //aImageHigh.Make(mSplatWidth*2, mSplatHeight*2,IMAGE_RGBA(0x00, 0xFF, 0x80, 0xFF));
                aImageUltra.MakeBlank(mSplatWidth*4, mSplatHeight*4);
            }
            
            
            
           

			
			for(int i=0;i<aNodeCount;i++)
			{
                aNode = aArray[i];
                if(aArray[i]->mRotated)
                {
                    aArray[i]->mImage->RotateLeft();
                    mImage.Stamp(aNode->mImage,aNode->mX,aNode->mY);
                    aNode->mImage->RotateRight();
                    
                    if(aNode->mImageDoubleRez)
                    {
                        aArray[i]->mImageDoubleRez->RotateLeft();
                        aImageHigh.Stamp(aNode->mImageDoubleRez,aNode->mX*2,aNode->mY*2);
                        aNode->mImageDoubleRez->RotateRight();
                    }
                    if(aNode->mImageQuadrupleRez)
                    {
                        aArray[i]->mImageQuadrupleRez->RotateLeft();
                        aImageUltra.Stamp(aNode->mImageQuadrupleRez,aNode->mX*4,aNode->mY*4);
                        aNode->mImageQuadrupleRez->RotateRight();
                    }
                }
                else
                {
                    mImage.Stamp(aNode->mImage,aNode->mX,aNode->mY);
                    if(aNode->mImageDoubleRez)
                    {
                        aImageHigh.Stamp(aNode->mImageDoubleRez, aNode->mX*2, aNode->mY*2);
                    }
                    if(aNode->mImageQuadrupleRez)
                    {
                        aImageUltra.Stamp(aNode->mImageQuadrupleRez, aNode->mX*4, aNode->mY*4);
                    }
                }
			}
            
            XML aXML;
            XMLTag *aRoot=new XMLTag("image_bundle");
            aXML.mRoot=aRoot;
            
            XMLTag *aNodeListTag=new XMLTag("node_list");
            *aRoot += aNodeListTag;
            
            aRoot->AddParam("width", FString(mImage.mWidth).c());
            aRoot->AddParam("height", FString(mImage.mHeight).c());
            aRoot->AddParam("border", FString(mBorder).c());
            aRoot->AddParam("edge", FString(mEdgeBorder).c());
            
            int aLoopIndex=0;
            
            printf("\n\n\n********SAVE NODE COUNT: %d\n\n\n", mSaveNodeList.mCount);
            
            printf("\n\n ---- Save Node Count: %d\n---\n\n----\n\n\n", mSaveNodeList.mCount);
            
			EnumList(ImageBundlerSaveNode, aSaveNode, mSaveNodeList)
            {
                XMLTag *aNodeTag=new XMLTag("node");
                *aNodeListTag += aNodeTag;
                
                aNodeTag->AddTag("name", aSaveNode->mName.c());
                
                aNodeTag->AddTag("inset", FString(aSaveNode->mInset).c());
                
                //aRoot->AddParam("inset", FString(aNode->mInset).c());
                
                aNodeTag->AddTag("image_width", FString(aSaveNode->mOriginalWidth).c());
                aNodeTag->AddTag("image_height", FString(aSaveNode->mOriginalHeight).c());
                
                aNodeTag->AddTag("offset_x", FString(aSaveNode->mOffsetX).c());
                aNodeTag->AddTag("offset_y", FString(aSaveNode->mOffsetY).c());
                
                aNodeTag->AddTag("rect_x", FString(aSaveNode->mX + aSaveNode->mInset).c());
                aNodeTag->AddTag("rect_y", FString(aSaveNode->mY + aSaveNode->mInset).c());
                
                aNodeTag->AddTag("rect_width", FString(aSaveNode->mWidth - (aSaveNode->mInset * 2)).c());
                aNodeTag->AddTag("rect_height", FString(aSaveNode->mHeight - (aSaveNode->mInset * 2)).c());
                
                if(aSaveNode->mRotated)aNodeTag->AddTag("rotated", "true");
                
                if(aSaveNode->mScreenCenter)aNodeTag->AddTag("screen_center", "true");
                
                
			}
            
            aXML.Save(FString(FString(pName) + FString(".xml")));
            
            ExportPNGImage(aImageUltra.mData, FString(FString(pName) + FString("_ipad@2x.png")).c(), aImageUltra.mWidth, aImageUltra.mHeight);
			ExportPNGImage(aImageHigh.mData, FString(FString(pName) + FString("@2x.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(aImageHigh.mData, FString(FString(pName) + FString("_ipad.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(mImage.mData, FString(FString(pName) + FString(".png")).c(), mImage.mWidth, mImage.mHeight);
            
            FString aPrefix = FString("/Users/nraptis/Desktop/Exports/");
            
            aXML.Save(FString(aPrefix + FString(pName) + FString(".xml")));
            ExportPNGImage(aImageUltra.mData, FString(aPrefix + FString(pName) + FString("_ipad@2x.png")).c(), aImageUltra.mWidth, aImageUltra.mHeight);
			ExportPNGImage(aImageHigh.mData, FString(aPrefix + FString(pName) + FString("@2x.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(aImageHigh.mData, FString(aPrefix + FString(pName) + FString("_ipad.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(mImage.mData, FString(aPrefix + FString(pName) + FString(".png")).c(), mImage.mWidth, mImage.mHeight);
            
            
            
            /*
            mImage.WhiteToAlpha()
            
            ExportPNGImage(aImageUltra.mData, FString(FString(pName) + FString("_ipad@2x.png")).c(), aImageUltra.mWidth, aImageUltra.mHeight);
			ExportPNGImage(aImageHigh.mData, FString(FString(pName) + FString("@2x.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(aImageHigh.mData, FString(FString(pName) + FString("_ipad.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(mImage.mData, FString(FString(pName) + FString(".png")).c(), mImage.mWidth, mImage.mHeight);
            
            
            ExportPNGImage(aImageUltra.mData, FString(aPrefix + FString(pName) + FString("_ipad@2x.png")).c(), aImageUltra.mWidth, aImageUltra.mHeight);
			ExportPNGImage(aImageHigh.mData, FString(aPrefix + FString(pName) + FString("@2x.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(aImageHigh.mData, FString(aPrefix + FString(pName) + FString("_ipad.png")).c(), aImageHigh.mWidth, aImageHigh.mHeight);
            ExportPNGImage(mImage.mData, FString(aPrefix + FString(pName) + FString(".png")).c(), mImage.mWidth, mImage.mHeight);
            */
            
            
			return;
		}
	}
}

void ImageBundler::StartBundle(const char *pBundleName)
{
    if(mAutoBundle)
    {
        if(mSaveNodeList.mCount > 0)
        {
            Save(mBundleName);
            Clear();
        }
        mBundleName = pBundleName;
    }
    else
    {
        Load(pBundleName);
    }
}

void ImageBundler::EndBundle()
{
    if(mAutoBundle)
    {
        if(mSaveNodeList.mCount > 0)
        {
            Save(mBundleName);
            Clear();
        }
    }
    mAutoBundle = false;
}

void ImageBundler::Load(char *pName)
{
    Clear();
    
    bool aHoldRetinaResize = gSpriteIgnoreRetina;
    gSpriteIgnoreRetina = true;
    
    if(gIsIpad)
    {
        //mImage.Load(FString(pName) + FString("@2x"));
    }
    if(mImage.mWidth <= 0)
    {
        mImage.Load(pName);
    }
    
    gSpriteIgnoreRetina = aHoldRetinaResize;
    
    XML aXML;
    aXML.Load(FString(pName) + FString(".xml"));
    //aXML.Print();
    XMLTag *aRoot = aXML.GetRoot();
    
    if(aRoot)
    {
        int aSplatWidth=0;
        int aSplatHeight=0;
        
        EnumParams(aRoot, aParam)
        {
            if(FString(aParam->mName) == "width")
            {
                aSplatWidth = FString(aParam->mValue).ToInt();
            }
            if(FString(aParam->mName) == "height")
            {
                aSplatHeight = FString(aParam->mValue).ToInt();
            }
        }
        
        bool aIsRetina= (mImage.mWidth == (aSplatWidth / 2));
        
        //printf("Retina Splat: [%d]\n", aIsRetina);
        //printf("Image Bundler Expected [%d %d] For Image [%d %d]\n", aSplatWidth, aSplatHeight, mImage.mWidth, mImage.mHeight);
        
        EnumTags(aRoot, aNodeListTag)
        {
            EnumTags(aNodeListTag, aNodeTag)
            {
                
                ImageBundlerLoadNode *aNode = new ImageBundlerLoadNode();
                mLoadNodeList += aNode;
                
                aNode->mBundleWidth = mImage.mWidth;
                aNode->mBundleHeight = mImage.mHeight;
                
                EnumTags(aNodeTag,aNodeSubtag)
                {
                    if(FString(aNodeSubtag->mName) == "name")
                    {
                        aNode->mName = aNodeSubtag->mValue;
                    }
                    if(FString(aNodeSubtag->mName) == "image_width")
                    {
                        aNode->mOriginalWidth = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "image_height")
                    {
                        aNode->mOriginalHeight = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "offset_x")
                    {
                        aNode->mOffsetX = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "offset_y")
                    {
                        aNode->mOffsetY = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "rect_x")
                    {
                        aNode->mX = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "rect_y")
                    {
                        aNode->mY = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "rect_width")
                    {
                        aNode->mWidth = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "rect_height")
                    {
                        aNode->mHeight = FString(aNodeSubtag->mValue).ToInt();
                    }
                    if(FString(aNodeSubtag->mName) == "rotated")
                    {
                        aNode->mRotated = FString(aNodeSubtag->mValue).ToBool();
                    }
                    if(FString(aNodeSubtag->mName) == "screen_center")
                    {
                        aNode->mScreenCenter = FString(aNodeSubtag->mValue).ToBool();
                    }
                    
                    
                    
                }
                
                
                //printf("Chunk[%s] Rct(%d,%d,%d,%d) Off(%d,%d) Ori(%d,%d) Rot(%d)\n", aNode->mName.c(), aNode->mX, aNode->mY, aNode->mWidth, aNode->mHeight, aNode->mOffsetX, aNode->mOffsetY, aNode->mOriginalWidth, aNode->mOriginalHeight, (int)(aNode->mRotated));
                
                
                if(aNode->mScreenCenter)
                {
                    int aWidth = aNode->mWidth;
                }
                
                
                if(mModelMode)
                {
                    
                    /*
                     aNode->mSpriteUStart=(float)((aNode->mX - aNode->mOffsetX)) / (float)aSplatWidth;
                     aNode->mSpriteVStart=(float)((aNode->mY - aNode->mOffsetY)) / (float)aSplatHeight;
                     aNode->mSpriteUEnd  =(float)((aNode->mX - aNode->mOffsetX) + aNode->mOriginalWidth) / (float)aSplatWidth;
                     aNode->mSpriteVEnd  =(float)((aNode->mY - aNode->mOffsetY) + aNode->mOriginalHeight) / (float)aSplatHeight;
                     */
                    
                    float aStartX = aNode->mX - aNode->mOffsetX;
                    float aStartY = aNode->mY - aNode->mOffsetY;
                    
                    aNode->mSpriteUStart=(float)(aStartX) / (float)aSplatWidth;
                    aNode->mSpriteVStart=(float)(aStartY) / (float)aSplatHeight;
                    aNode->mSpriteUEnd  =(float)(aStartX + aNode->mOriginalWidth) / (float)aSplatWidth;
                    aNode->mSpriteVEnd  =(float)(aStartY + aNode->mOriginalHeight) / (float)aSplatHeight;
                }
                else
                {
                    
                    aNode->mSpriteUStart=(float)(aNode->mX) / (float)aSplatWidth;
                    aNode->mSpriteVStart=(float)(aNode->mY) / (float)aSplatHeight;
                    aNode->mSpriteUEnd  =(float)(aNode->mX + aNode->mWidth) / (float)aSplatWidth;
                    aNode->mSpriteVEnd  =(float)(aNode->mY + aNode->mHeight) / (float)aSplatHeight;
                    
                }
                
                /*
                
                aLeft = -(aWidth / 2.0f) + (float)aNode->mOffsetX;
                aTop = -(aHeight / 2.0f) + (float)aNode->mOffsetY;
                
                aRight = aLeft + (float)aNode->mWidth;
                aBottom = aTop + (float)aNode->mHeight;
                
                */
                
                aNode->mSpriteLeft = (float)aNode->mOffsetX - ((float)aNode->mOriginalWidth / 2.0f);
                aNode->mSpriteRight = aNode->mSpriteLeft + (float)aNode->mWidth;
                
                aNode->mSpriteTop = (float)aNode->mOffsetY - ((float)aNode->mOriginalHeight / 2.0f);
                aNode->mSpriteBottom = aNode->mSpriteTop + (float)aNode->mHeight;
                
                aNode->mSpriteWidth = (float)aNode->mOriginalWidth;
                aNode->mSpriteHeight = (float)aNode->mOriginalHeight;
                
                //if(mMultiRez)
                //{
                
                if(gIsIpad)
                {
                    aNode->mSpriteHeight *= 2.0f;
                    aNode->mSpriteWidth *= 2.0f;
                    
                    aNode->mSpriteLeft *= 2.0f;
                    aNode->mSpriteRight *= 2.0f;
                    
                    aNode->mSpriteTop *= 2.0f;
                    aNode->mSpriteBottom *= 2.0f;
                }
                
                //}
                
//                if(aIsRetina)
//                {
//                    aNode->mSpriteHeight /= 2.0f;
//                    aNode->mSpriteWidth /= 2.0f;
//                    
//                    aNode->mSpriteLeft /= 2.0f;
//                    aNode->mSpriteRight /= 2.0f;
//                    
//                    aNode->mSpriteTop /= 2.0f;
//                    aNode->mSpriteBottom /= 2.0f;
//                }
            }
        }
    }
    
	gApp->mImageBundle = this;
    
    if(mLoadNodeList.mCount==0)
    {
        int mNodeCount=0;
        
        FString aSplatString = FString(pName) + FString(".splat");
        
        Buffer aBuffer;
        aBuffer.Load(aSplatString.c());
        
        char aWrite[1024];
        int aWriteIndex=0;
        
        char *aPtr = (char*)aBuffer.mData;
        char *aCap = &(((char*)aBuffer.mData)[aBuffer.mLength]);
        
        
        int aNumber[32];
        int aRunningSum=0;
        int aNumberIndex=0;
        
        
        while(aPtr < aCap)
        {
            while(*aPtr!='\"' && aPtr<aCap)aPtr++;
            if(aPtr<aCap)
            {
                aPtr++;
                aWriteIndex=0;
                
                while(*aPtr!='\"')
                {
                    aWrite[aWriteIndex]=*aPtr;
                    aWriteIndex++;
                    aPtr++;
                }
                
                aWrite[aWriteIndex]=0;
                
                aPtr++;
                
                aNumberIndex=0;
                
                while(aNumberIndex < 9)
                {
                    aRunningSum=0;
                    
                    while(aPtr < aCap && (!(*aPtr>='0'&&*aPtr<='9')))
                    {
                        aPtr++;
                    }
                    
                    while(aPtr < aCap && (*aPtr>='0'&&*aPtr<='9'))
                    {
                        aRunningSum*=10;
                        aRunningSum += (int)((unsigned char)(*aPtr - '0'));
                        aPtr++;
                    }
                    
                    aNumber[aNumberIndex]=aRunningSum;
                    aNumberIndex++;
                }
                
                
                ImageBundlerLoadNode *aNode = new ImageBundlerLoadNode();
                
                aNode->mBundleWidth = mImage.mWidth;
                aNode->mBundleHeight = mImage.mHeight;
                
                aNode->mName = aWrite;
                
                aNode->mX = aNumber[0];
                aNode->mY = aNumber[1];
                aNode->mWidth = aNumber[2];
                aNode->mHeight = aNumber[3];
                
                aNode->mOffsetX = aNumber[4];
                aNode->mOffsetY = aNumber[5];
                
                aNode->mOriginalWidth = aNumber[6];
                aNode->mOriginalHeight = aNumber[7];
                
                aNode->mRotated=(bool)aNumber[8];
                
                
                
                aNode->mSpriteUStart=(float)(aNode->mX) / (float)mImage.mWidth;
                aNode->mSpriteVStart=(float)(aNode->mY) / (float)mImage.mHeight;
                aNode->mSpriteUEnd  =(float)(aNode->mX + aNode->mWidth) / (float)mImage.mWidth;
                aNode->mSpriteVEnd  =(float)(aNode->mY + aNode->mHeight) / (float)mImage.mHeight;
                
                /*
                 aLeft = -(aWidth / 2.0f) + (float)aNode->mOffsetX;
                 aTop = -(aHeight / 2.0f) + (float)aNode->mOffsetY;
                 
                 
                 aRight = aLeft + (float)aNode->mWidth;
                 aBottom = aTop + (float)aNode->mHeight;
                 */
                
                
                aNode->mSpriteLeft = (float)aNode->mOffsetX - ((float)aNode->mOriginalWidth / 2.0f);
                aNode->mSpriteRight = aNode->mSpriteLeft + (float)aNode->mWidth;
                
                aNode->mSpriteTop = (float)aNode->mOffsetY - ((float)aNode->mOriginalHeight / 2.0f);
                aNode->mSpriteBottom = aNode->mSpriteTop + (float)aNode->mHeight;
                
                aNode->mSpriteWidth = (float)aNode->mOriginalWidth;
                aNode->mSpriteHeight = (float)aNode->mOriginalHeight;
                
                mLoadNodeList += aNode;
            }
            aPtr++;
        }
        if(gApp)
        {
            gApp->mImageBundle = this;
        }
    }
}

ImageBundlerLoadNode *ImageBundler::FetchNode(char *pName)
{
	ImageBundlerLoadNode *aReturn=0;
    
    if(mLoadSequential && false)
    {
        if(mSequentialLoadIndex >= 0 && mSequentialLoadIndex < mLoadNodeList.mCount)
        {
            aReturn = ((ImageBundlerLoadNode*)mLoadNodeList.Fetch(mSequentialLoadIndex));
        }
        mSequentialLoadIndex++;
    }
    else
    {
        
        EnumList(ImageBundlerLoadNode, aNode, mLoadNodeList)
        {
            if(aNode->mName == pName)
            {
                aReturn = aNode;
                break;
            }
        }
    }
	return aReturn;
}

ImageBundlerLoadNode::ImageBundlerLoadNode()
{
    mX=0;
	mY=0;
    
	mWidth=0;
	mHeight=0;
    
    mBundleWidth=0;
    mBundleHeight=0;
    
	mOriginalWidth=0;
	mOriginalHeight=0;
	
	mOffsetX=0;
	mOffsetY=0;
    
    mScreenCenter=false;
	
    mRotated=false;
}

ImageBundlerLoadNode::~ImageBundlerLoadNode()
{
    
}


ImageBundlerLoadNode *ImageBundlerLoadNode::Clone()
{
    ImageBundlerLoadNode *aReturn = new ImageBundlerLoadNode();
    
    aReturn->mBundleWidth = mBundleWidth;
    aReturn->mBundleHeight = mBundleHeight;
    
    aReturn->mX=mX;
    aReturn->mY=mY;
    
    aReturn->mWidth=mWidth;
    aReturn->mHeight=mHeight;
    
    aReturn->mOffsetX=mOffsetX;
    aReturn->mOffsetY=mOffsetY;
    
    aReturn->mOriginalWidth=mOriginalWidth;
    aReturn->mOriginalHeight=mOriginalHeight;
    
    
    aReturn->mSpriteLeft=mSpriteLeft;
    aReturn->mSpriteRight=mSpriteRight;
    aReturn->mSpriteTop=mSpriteTop;
    aReturn->mSpriteBottom=mSpriteBottom;
    
    aReturn->mSpriteUStart=mSpriteUStart;
    aReturn->mSpriteUEnd=mSpriteUEnd;
    
    aReturn->mSpriteVStart=mSpriteVStart;
    aReturn->mSpriteVEnd=mSpriteVEnd;
    
    aReturn->mSpriteWidth=mSpriteWidth;
    aReturn->mSpriteHeight=mSpriteHeight;
    
    aReturn->mRotated=mRotated;
    
    aReturn->mScreenCenter=mScreenCenter;
    
    aReturn->mName=mName;
    
    return aReturn;
}



ImageBundlerSaveNode::ImageBundlerSaveNode()
{
	mX=0;
	mY=0;
	
	mWidth=0;
	mHeight=0;
	
	
	mOriginalWidth=0;
	mOriginalHeight=0;
	
	mOffsetX=0;
	mOffsetY=0;
	
	mArea=0;
    
    mInset=0;
	
	mImage=0;
    mImageQuadrupleRez=0;
    mImageDoubleRez=0;
    
    mScreenCenter=false;
	
    mRotated=false;
    mCanRotate=true;
}

ImageBundlerSaveNode::~ImageBundlerSaveNode()
{
	delete mImage;
	mImage=0;
}

void ImageBundlerSaveNode::Rotate()
{
    if(!mRotated)
    {
        mRotated=true;
        int aHold=mWidth;
        mWidth=mHeight;
        mHeight=aHold;
    }
}

void ImageBundlerSaveNode::Unrotate()
{
    if(mRotated)
    {
        mRotated=false;
        int aHold=mWidth;
        mWidth=mHeight;
        mHeight=aHold;
    }
}
