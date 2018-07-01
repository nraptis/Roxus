/*
 *   FImageBundler.cpp
 *   Ninja
 *
 *   Created by Nick Raptis on 4/26/11.
 *   Copyright 2011 Nick Raptis. All rights reserved.
 *
 */

#include "core_includes.h"
#include "FImageBundler.h"
#include "FXML.h"
#include "FFile.h"

FImageBundler gImageBundler;

FImageBundler::FImageBundler()
{
    mEdgeBorder=2;
    mBorder=2;
    mInset=0;
    
    mSpacingRadix = 16;
    
    mSequenceStartIndex = -1;
    mSequenceEndIndex = -1;
    
    mMultiRez=false;
    
    mAutoBundle=false;
    
    //mModelMode=false;
    mSeamlessBorders = false;
    
    mTextureWidth = 0;
    mTextureHeight = 0;
    
    mBundleWidth = 0;
    mBundleHeight = 0;
    
    mBundleScale = 1.0f;
    
    mSplatArea = 0;
    
    mTileBorderSize=2;
    mTileMode=false;
    
    mRotationEnabled=true;
    
    mSuccess=false;
    
    mDidLoad = false;
    
    mLoadSequential=true;
    mSequentialLoadIndex=0;
    
}

FImageBundler::~FImageBundler()
{
    Clear();
}

void FImageBundler::Clear()
{
    FreeList(FImageBundlerSaveNode,mSaveNodeList);
    FreeList(FImageBundlerLoadNode,mLoadNodeList);
    
    mSequentialLoadIndex = 0;
    
    mDidLoad = false;
    
    mBundleWidth = 0;
    mBundleHeight = 0;
    
    mTextureWidth = 0;
    mTextureHeight = 0;
    
    mSplatArea = 0;
    
    mSuccess = false;
    
    mImage.Kill();
    
}

void FImageBundler::AddImage(FImage *pImage)
{
    
    if(!pImage)return;
    if(pImage->mWidth<=0||pImage->mHeight<=0)return;
    
    FString aPath = pImage->mFileName;
    
    aPath.RemovePath();
    aPath.RemoveExtension();
    aPath.Replace("@2x", "");
    aPath.Replace("highrez", "");
    aPath.Replace("_hd", "");
    
    FImage aDoubleRez;
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gDirBundle + aPath + FString("_hd.png"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gDirBundle + aPath + FString("_hd.jpg"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gDirBundle + aPath + FString("_hd.jpeg"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gDirBundle + aPath + FString("_hd.PNG"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gDirBundle + aPath + FString("_hd.JPG"));
    if(aDoubleRez.mWidth==0)aDoubleRez.LoadDirect(gDirBundle + aPath + FString("_hd.JPEG"));
    if(aDoubleRez.mWidth > 0)
    {
        if(aDoubleRez.mWidth != (pImage->mWidth * 2))Log("***\nWIDTH MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), pImage->mWidth, aDoubleRez.mWidth);
        if(aDoubleRez.mHeight != (pImage->mHeight * 2))Log("***\nHEIGHT MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), pImage->mHeight, aDoubleRez.mHeight);
    }
    else
    {
        //Log("No High Rez Image For [%s]\n", aPath.c());
    }
    
    FImage aQuadrupleRez;
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gDirBundle + aPath + FString("_uhd.png"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gDirBundle + aPath + FString("_uhd.jpg"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gDirBundle + aPath + FString("_uhd.jpeg"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gDirBundle + aPath + FString("_uhd.PNG"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gDirBundle + aPath + FString("_uhd.JPG"));
    if(aQuadrupleRez.mWidth==0)aQuadrupleRez.LoadDirect(gDirBundle + aPath + FString("_uhd.JPEG"));
    if(aQuadrupleRez.mWidth > 0)
    {
        if(aQuadrupleRez.mWidth != (pImage->mWidth * 4))Log("***\nWIDTH MISMATCH (%s) Low[%d] Ultra[%d]\n***\n", aPath.c(), pImage->mWidth, aQuadrupleRez.mWidth);
        if(aQuadrupleRez.mHeight != (pImage->mHeight * 4))Log("***\nHEIGHT MISMATCH (%s) Low[%d] Ultra[%d]\n***\n", aPath.c(), pImage->mHeight, aQuadrupleRez.mHeight);
    }
    else
    {
        //Log("No High Rez Image For [%s]\n", aPath.c());
    }
    
    
    FImageBundlerSaveNode *aNode=new FImageBundlerSaveNode();
    AddNode(aNode);
    
    aNode->mName = aPath;
    
    aNode->mX=0;
    aNode->mY=0;
    
    aNode->mOriginalWidth=pImage->mWidth;
    aNode->mOriginalHeight=pImage->mHeight;
    
    if(mInset > 0)
    {
        
        //mInset);
        
        aNode->mImage = pImage->Clone();
        
        //if(mSeamlessBorders)aNode->mImage->BufferEdgesSeamless(mInset);
        //else aNode->mImage->BufferEdges(mInset);
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
            
            //if(mSeamlessBorders)aNode->mImageDoubleRez->BufferEdgesSeamless(mInset * 2);
            //else
            aNode->mImageDoubleRez->BufferEdges(mInset * 2);
            
            //FString aPrefix = FString("/Users/nraptis/Desktop/Exports/");
            //ExportPNGImage(aNode->mImageDoubleRez->mData, FString(aPrefix + aPath + FString("_border_lol_double.png")).c(), aNode->mImageDoubleRez->mWidth, aNode->mImageDoubleRez->mHeight);
            
            aDoubleRez.Kill();
        }
        
        if(aQuadrupleRez.mWidth > 0)
        {
            aNode->mImageQuadrupleRez = aQuadrupleRez.Clone();
            
            
            //if(mSeamlessBorders)aNode->mImageDoubleRez->BufferEdgesSeamless(mInset * 4);
            //else
            aNode->mImageQuadrupleRez->BufferEdges(mInset * 4);
            
            //ExportPNGImage(aNode->mImageQuadrupleRez->mData, FString(aPrefix + aPath + FString("_border_lol_quad.png")).c(), aNode->mImageQuadrupleRez->mWidth, aNode->mImageQuadrupleRez->mHeight);
            
            aQuadrupleRez.Kill();
        }
        
        //aNode->mIm
        
        //ExportPNGImage(aNode->mImage->mData, FString(aPrefix + aPath + FString("_border_lol.png")).c(), aNode->mImage->mWidth, aNode->mImage->mHeight);
        
        return;
    }
    
    //pImage->FixTileBorders(20);
    
    int aLeft, aRight, aTop, aBottom, aWidth, aHeight;
    pImage->GetEdges(aLeft,aRight,aTop,aBottom);
    
    
    if(mSeamlessBorders)
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
     aNewImage->mFileName=pImage->mFileName;
     aNewImage->mFileName.RemovePath(true);
     aNode->mImage=aNewImage;
     
     return;
     }
     }
     
     */
    
    
    FImage *aNewImage = 0;
    
    if(mSeamlessBorders)
    {
        aNewImage = pImage->Clone();
    }
    else
    {
        aNewImage = pImage->Crop(aLeft,aTop,aWidth,aHeight);
    }
    
    //aNewImage->mFileName=pImage->mFileName;
    
    //aNewImage->mFileName.RemovePath(true);
    aNode->mImage=aNewImage;
    
    if(aDoubleRez.mWidth > 0)aNode->mImageDoubleRez=aDoubleRez.Crop(aLeft*2, aTop*2, aWidth*2, aHeight*2);
    //else Log("No High Rez Image For [%s]\n", aNode->mName.c());
    
    if(aQuadrupleRez.mWidth > 0)aNode->mImageQuadrupleRez=aQuadrupleRez.Crop(aLeft*4, aTop*4, aWidth*4, aHeight*4);
    //else Log("No High Rez Image For [%s]\n", aNode->mName.c());
    
}

void FImageBundler::AddNode(FImageBundlerSaveNode *pNode)
{
    mSaveNodeList += pNode;
}


void FImageBundler::ExportChunksWithCropData()
{
    FXML aXML;
    
    FString aName;
    
    FXMLTag *aRootTag = new FXMLTag("image_crops");
    aXML.mRoot = aRootTag;
    
    FXMLTag *aCropListTag = new FXMLTag("crop_list");
    *aRootTag += aCropListTag;
    
    FString aPrefix;os_getTestDirectory(&aPrefix);
    
    EnumList(FImageBundlerSaveNode, aSaveNode, mSaveNodeList)
    {
        aName = aSaveNode->mName;
        
        FXMLTag *aCropTag = new FXMLTag("crop");
        *aCropListTag += aCropTag;
        
        aCropTag->AddParam("offset_x", FString(aSaveNode->mOffsetX).c());
        aCropTag->AddParam("offset_y", FString(aSaveNode->mOffsetY).c());
        aCropTag->AddParam("name", aName.c());
        
        
        
        FString aImagePath = FString(aPrefix + FString("bundle_") + FString(aName) + FString(".png")).c();
        
        
        //os_exportPNGImage(aSaveNode->mImage->mData, FString(FString("Exports/") + FString(aName) + FString("_cropped.png")).c(), aSaveNode->mImage->mWidth, aSaveNode->mImage->mHeight);
        os_exportPNGImage(aSaveNode->mImage->mData, aImagePath.c(), aSaveNode->mImage->mWidth, aSaveNode->mImage->mHeight);
        
        //aName
        
        
    }
    
    FString aPathXML = FString(aPrefix + FString("image_crop_data") + FString(aName) + FString(".xml")).c();
    
    aXML.Save(aPathXML.c());
    
}

void FImageBundler::Save(char *pName)
{
    if(mSaveNodeList.mCount <= 0)
    {
        Log("Skipping Bundle [%s] (0 Nodes!)\n", pName);
        return;
    }
    
    mSuccess=false;
    
    int aTryWidth[32];
    int aTryHeight[32];
    
    aTryWidth[0]=256;aTryHeight[0]=256;
    
    aTryWidth[1]=256;aTryHeight[1]=256;
    aTryWidth[2]=512;aTryHeight[2]=512;
    aTryWidth[3]=1024;aTryHeight[3]=512;
    aTryWidth[4]=1024;aTryHeight[4]=1024;
    aTryWidth[5]=2048;aTryHeight[5]=1024;
    aTryWidth[6]=2048;aTryHeight[6]=2048;
    
    FImageBundlerSaveNode *aNode, *aCheckNode;
    
    int aNodeCount=mSaveNodeList.mCount;
    FImageBundlerSaveNode **aArray = new FImageBundlerSaveNode*[mSaveNodeList.mCount+1];
    for(int i=0;i<aNodeCount;i++)
    {
        aArray[i]=(FImageBundlerSaveNode*)mSaveNodeList.Fetch(i);
    }
    
    int aLowRezCount=0;
    int aDoubleRezCount=0;
    int aQuadrupleRezCount=0;
    
    EnumList(FImageBundlerSaveNode, aSaveNode, mSaveNodeList)
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
    
    Log("\n***\nFound %d Images and %d High Rez\n***\n", aLowRezCount, aDoubleRezCount);
    
    for(int i=0;i<aNodeCount;i++)
    {
        aArray[i]=(FImageBundlerSaveNode*)mSaveNodeList.Fetch(i);
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
    
    FString aPrefix;os_getTestDirectory(&aPrefix);
    
    for(int aSplatSizeIndex=0;aSplatSizeIndex<7;aSplatSizeIndex++)
    {
        mBundleWidth = aTryWidth[aSplatSizeIndex];
        mBundleHeight = aTryHeight[aSplatSizeIndex];
        
        
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
                
                
                //mBundleWidth
                //mBundleHeight
                
                for(int aY=0;aNodePlaced==false && aY<=mBundleHeight-aNodeHeight;aY+=mSpacingRadix)
                {
                    
                    for(int aX=0;aNodePlaced==false && aX <= mBundleWidth - aNodeWidth;aX+=mSpacingRadix)
                    {
                        aEdgeIntersect = ((aX+aNodeWidth >(mBundleWidth-mEdgeBorder))
                                          || (aY+aNodeHeight>(mBundleHeight-mEdgeBorder))
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
        
        if(aNodeCount == 0)
        {
            mSuccess = false;
        }

        if(mSuccess)
        {
            mImage.Kill();
            mImage.MakeBlank(mBundleWidth, mBundleHeight);
            
            FImage aImageHigh;
            if(aDoubleRezCount > 0)aImageHigh.MakeBlank(mBundleWidth * 2, mBundleHeight * 2);
            
            FImage aImageUltra;
            if(aQuadrupleRezCount > 0)aImageUltra.MakeBlank(mBundleWidth * 4, mBundleHeight * 4);
            
            
            
            
            
            
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
            
            FXML aXML;
            FXMLTag *aRoot=new FXMLTag("image_bundle");
            aXML.mRoot=aRoot;
            
            FXMLTag *aNodeListTag = new FXMLTag("node_list");
            *aRoot += aNodeListTag;
            
            aRoot->AddParam("width", FString(mImage.mWidth).c());
            aRoot->AddParam("height", FString(mImage.mHeight).c());
            aRoot->AddParam("border", FString(mBorder).c());
            aRoot->AddParam("edge", FString(mEdgeBorder).c());
            
            aRoot->AddParam("sequence_start", FString(mSequenceStartIndex).c());
            aRoot->AddParam("sequence_end", FString(mSequenceEndIndex).c());
            
            
                            
            int aLoopIndex=0;
            
            
            EnumList(FImageBundlerSaveNode, aSaveNode, mSaveNodeList)
            {
                FXMLTag *aNodeTag = new FXMLTag("node");
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
            }
            
            
            FString aPath = FString(aPrefix + FString("") + FString(pName) + FString(".png")).c();
            os_exportPNGImage(mImage.mData, aPath.c(), mImage.mWidth, mImage.mHeight);

            
            aPath = FString(aPrefix + FString("") + FString(pName) + FString("_data.xml")).c();
            aXML.Save(aPath.c());
            
            //os_exportPNGImage(aImageUltra.mData, FString(FString(pName) + FString("_ipad@2x.png")).c(), aImageUltra.mWidth, aImageUltra.mHeight);
            return;
        }
    }
}

void FImageBundler::StartBundle(const char *pBundleName)
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

void FImageBundler::EndBundle()
{
    if(mAutoBundle)
    {
        if(mSaveNodeList.mCount > 0)
        {
            Save(mBundleName);
            Clear();
        }
    }
}


void FImageBundler::Load(const char *pFileName, const char *pImageName)
{
    Clear();
    
    mBundleName = FString(pImageName);
    mBundleName.RemoveExtension();
    
    LoadBundle(pFileName);
    
    if(mLoadNodeList.mCount > 0)
    {
        mDidLoad = true;
    }
    
    FTexture *aTexture = gTextureCache.GetTexture(pImageName);
    if(aTexture)
    {
        //int aTextureWidth = aTexture->mExpandedWidth;
        //int aTextureHeight = aTexture->mExpandedHeight;
        

        if((aTexture->mExpandedWidth > 0) && (aTexture->mExpandedHeight > 0))
        {
            
            if(mBundleWidth > 0)
            {
                mBundleScale = ((float)aTexture->mExpandedWidth) / ((float)mBundleWidth);
            }
            
        }
    }

    
    
}


void FImageBundler::LoadBundle(const char *pFileXML)
{
    FXML aXML;
    aXML.Load(pFileXML);
    
    FXMLTag *aRoot = aXML.GetRoot();
    
//#define BUNDLE_IMG_PREFIX "BNDL_IMG_"
//#define BUNDLE_DATA_PREFIX "BNDL_DAT_"
    
    //FString(BUNDLE_DATA_PREFIX) +
    //_data
    
    //if(aRoot == 0){aXML.Load(gDirBundle + FString("Bundles/") + mBundleName + FString(".xml"));aRoot = aXML.GetRoot();}
    //if(aRoot == 0){aXML.Load(gDirBundle + FString("[Bundles]/") + mBundleName + FString(".xml"));aRoot = aXML.GetRoot();}
    //if(aRoot == 0){aXML.Load(gDirBundle + FString("[[Bundles]]/") + mBundleName + FString(".xml"));aRoot = aXML.GetRoot();}
    
    if(gEnvironment == ENV_IPHONE)
    {
        if(aRoot == 0){aXML.Load(mBundleName + FString("_data.xml"));aRoot = aXML.GetRoot();}
        if(aRoot == 0){aXML.Load(gDirBundle + mBundleName + FString("_data.xml"));aRoot = aXML.GetRoot();}
        if(aRoot == 0){aXML.Load(gDirDocuments + mBundleName + FString("_data.xml"));aRoot = aXML.GetRoot();}
    }
    
    if(aRoot == 0){aXML.Load(gDirBundle + FString("Bundles/") + mBundleName + FString("_data.xml"));aRoot = aXML.GetRoot();}
    if(aRoot == 0){aXML.Load(gDirBundle + FString("[Bundles]/") + mBundleName + FString("_data.xml"));aRoot = aXML.GetRoot();}
    if(aRoot == 0){aXML.Load(gDirBundle + FString("[[Bundles]]/") + mBundleName + FString("_data.xml"));aRoot = aXML.GetRoot();}
    
    
    
    //if(aRoot == 0)Log("++++ FAILED TO LOAD BUNDLE [%s]\n\n", pFileXML);
    
    if(aRoot)
    {
        //aXML.Print();
        
        mBundleWidth = 0;
        mBundleHeight = 0;
        
        EnumParams(aRoot, aParam)
        {
            if(FString(aParam->mName) == "width")
            {
                mBundleWidth = FString(aParam->mValue).ToInt();
            }
            if(FString(aParam->mName) == "height")
            {
                mBundleHeight = FString(aParam->mValue).ToInt();
            }
        }

        EnumTags(aRoot, aNodeListTag)
        {
            EnumTags(aNodeListTag, aNodeTag)
            {
                
                FImageBundlerLoadNode *aNode = new FImageBundlerLoadNode();
                mLoadNodeList += aNode;
                
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
                }
                
                /*
                if(mSeamlessBorders)
                {
                    
                    float aStartX = aNode->mX - aNode->mOffsetX;
                    float aStartY = aNode->mY - aNode->mOffsetY;
                    
                    aNode->mSpriteUStart=(float)(aStartX) / (float)mBundleWidth;
                    aNode->mSpriteVStart=(float)(aStartY) / (float)mBundleHeight;
                    aNode->mSpriteUEnd  =(float)(aStartX + aNode->mOriginalWidth) / (float)mBundleWidth;
                    aNode->mSpriteVEnd  =(float)(aStartY + aNode->mOriginalHeight) / (float)mBundleHeight;
                }
                else
                {
                */
                    
                    aNode->mSpriteUStart=(float)(aNode->mX) / (float)mBundleWidth;
                    aNode->mSpriteVStart=(float)(aNode->mY) / (float)mBundleHeight;
                    aNode->mSpriteUEnd = (float)(aNode->mX + aNode->mWidth) / (float)mBundleWidth;
                    aNode->mSpriteVEnd = (float)(aNode->mY + aNode->mHeight) / (float)mBundleHeight;
                    
                //}
                
                aNode->mSpriteLeft = (float)aNode->mOffsetX - ((float)aNode->mOriginalWidth / 2.0f);
                aNode->mSpriteRight = aNode->mSpriteLeft + (float)aNode->mWidth;
                
                aNode->mSpriteTop = (float)aNode->mOffsetY - ((float)aNode->mOriginalHeight / 2.0f);
                aNode->mSpriteBottom = aNode->mSpriteTop + (float)aNode->mHeight;
                
                aNode->mSpriteWidth = (float)aNode->mOriginalWidth;
                aNode->mSpriteHeight = (float)aNode->mOriginalHeight;
            }
        }
    }
}

void FImageBundler::Load(char *pName)
{
    Clear();
    Load(pName, pName);
}


bool FImageBundler::SliceUpBundle(FImage *pImage, FList *pImageList, int pTolerance)
{
    bool aReturn = false;
    
    
    if((pImage != 0) && (pImageList != 0))
    {
        if((pImage->mExpandedWidth > 0) && (pImage->mExpandedHeight > 0))
        {
            
            
        }
    }
    
    
    int aWidth=pImage->mExpandedWidth ;//min(pOriginal.mWidth,pMask.mWidth);
    int aHeight=pImage->mExpandedHeight;//min(pOriginal.mHeight,pMask.mHeight);
    
    int aArea=aWidth*aHeight;
    
    char *aMaskLinear = new char[aArea];
    char **aMask = new char*[aHeight];
    
    
    
    char *aPtr=aMaskLinear;
    
    
    
    unsigned int *aWriteData=pImage->mData;
    for(int i=0;i<aArea;i++)
    {
        //if(((*aWriteData)&0xFF)==0)
        
        if(IMAGE_ALPHA(*aWriteData) <= 4)
        {
            aMaskLinear[i]=1;
            //aHopsBase[i] = ((char)pTolerance);
        }
        else
        {
            aMaskLinear[i]=0;
            //aHops[i] = 0;
            //aHopsBase[i] = 0;
        }
        
        aWriteData++;
    }
    
    for(int i=0;i<aHeight;i++)
    {
        aMask[i]=aPtr;
        aPtr+=aWidth;
    }
    
    
    //bool aExpand = true;
    //int
    
    
    
    //..
    //delete [] aHopsBase;
    //delete [] aHops;
    
    
    unsigned int **aData=new unsigned int*[aHeight];
    aWriteData = pImage->mData;
    for(int i=0;i<aHeight;i++)
    {
        aData[i]=aWriteData;
        aWriteData+=aWidth;
    }
    
    aArea=aWidth*aHeight;
    
    
    
    int aListCount=0;
    int aStackCount=0;
    int aLeft, aRight, aTop, aBottom;
    int aXOffset, aYOffset;
    int aNewImageWidth,aNewImageHeight;
    int aX=0;
    int aY=0;
    //unsigned int *aSource,*aDest;
    
    unsigned int **aNewData=new unsigned int *[aHeight];
    
    short *aXList=new short[aArea];
    short *aYList=new short[aArea];
    short *aXStack=new short[aArea];
    short *aYStack=new short[aArea];
    
    
    for(int x=0;x<aWidth;x++)
    {
        
        for(int y=0;y<aHeight;y++)
        {
            
            if(!aMask[y][x])
            {
                aXList[0]=x;
                aYList[0]=y;
                aXStack[0]=x;
                aYStack[0]=y;
                aListCount=0;
                aStackCount=1;
                while(aStackCount>0)
                {
                    aStackCount--;
                    aX=aXStack[aStackCount];
                    aY=aYStack[aStackCount];
                    if(!aMask[aY][aX])
                    {
                        aXList[aListCount]=aX;
                        aYList[aListCount]=aY;
                        aListCount++;
                        aMask[aY][aX]=1;
                        //top
                        if(aY>0)
                        {
                            if(!aMask[aY-1][aX])
                            {
                                aXStack[aStackCount]=aX;
                                aYStack[aStackCount]=aY-1;
                                aStackCount++;
                            }
                        }
                        //right
                        if(aX<aWidth-1)
                        {
                            if(!aMask[aY][aX+1])
                            {
                                aXStack[aStackCount]=aX+1;
                                aYStack[aStackCount]=aY;
                                aStackCount++;
                            }
                        }
                        //bottom
                        if(aY<aHeight-1)
                        {
                            if(!aMask[aY+1][aX])
                            {
                                aXStack[aStackCount]=aX;
                                aYStack[aStackCount]=aY+1;
                                aStackCount++;
                            }
                        }
                        //left
                        if(aX>0)
                        {
                            if(!aMask[aY][aX-1])
                            {
                                aXStack[aStackCount]=aX-1;
                                aYStack[aStackCount]=aY;
                                aStackCount++;
                            }
                        }
                    }
                }
                
                aLeft=x;
                aRight=x;
                aTop=y;
                aBottom=y;
                
                for(int i=0;i<aListCount;i++)if(aXList[i]<aLeft)aLeft=aXList[i];
                for(int i=0;i<aListCount;i++)if(aXList[i]>aRight)aRight=aXList[i];
                for(int i=0;i<aListCount;i++)if(aYList[i]<aTop)aTop=aYList[i];
                for(int i=0;i<aListCount;i++)if(aYList[i]>aBottom)aBottom=aYList[i];
                
                aRight++;
                aBottom++;
                
                
                //FImage *aImage
                
                FImage *aImage = new FImage();
                aNewImageWidth=aRight-aLeft;
                aNewImageHeight=aBottom-aTop;
                
                //mImageList+=aImage;
                
                pImageList->Add(aImage);
                
                
                
                //mPointList+=new Vector2((float)(aLeft-pBorder)+((float)aNewImageWidth)/2, (float)(aTop-pBorder)+((float)aNewImageHeight)/2);
                
                aImage->MakeBlank((aNewImageWidth),(aNewImageHeight));
                
                aWriteData=aImage->mData;
                for(int i=0;i<aNewImageHeight;i++)
                {
                    aNewData[i]=aWriteData;
                    aWriteData+=aNewImageWidth;
                }
                
                aXOffset = aLeft;
                aYOffset = aTop;
                
                for(int i=0;i<aListCount;i++)
                {
                    aX=aXList[i];
                    aY=aYList[i];
                    aNewData[aY-aYOffset][aX-aXOffset]=aData[aY][aX];
                    //aNewData[aX-aXOffset][aY-aYOffset]=aData[aX][aY];
                    
                }

                //os_exportPNGImage(aImage->mData, FString(FString("/Users/nraptis/Desktop/Exports/") + FString(FString("SLICE") + FString(pImageList->mCount)) + FString("_cropped.png")).c(), aImage->mExpandedWidth, aImage->mExpandedHeight);
                
                
                aImage->mOffsetX = aLeft;
                aImage->mOffsetY = aTop;
                
                //os_ex  (aImage->mData, <#const char *pFilePath#>, <#int pWidth#>, <#int pHeight#>)
                
                //if(pStroke)aImage->Stroke(0xFF000000,128,pStroke);
                
                //Sprite *aSprite=new Sprite();
                //aSprite->Load(aImage);
                //mSpriteList+=aSprite;
                
            }
        }
    }
    delete[]aNewData;
    delete[]aMaskLinear;
    delete[]aMask;
    delete[]aXList;
    delete[]aYList;
    delete[]aXStack;
    delete[]aYStack;
    delete[]aData;
    
    
    return aReturn;
}

bool FImageBundler::FindSequenceCrop(FList *pFileList, int &pCropX, int &pCropY, int &pCropWidth, int &pCropHeight)
{
    bool aReturn = false;
    
    pCropX = 0;
    pCropY = 0;
    pCropWidth = -1;
    pCropHeight = -1;
    

	int aSequenceWidth = -1;
	int aSequenceHeight = -1;
    
    int aMinInsetTop = -1;
    int aMinInsetRight = -1;
    int aMinInsetBottom = -1;
    int aMinInsetLeft = -1;
    
    if(pFileList)
    {
        //int aMaxImageWidth = 0;
        //int aMaxImageHeight = 0;
        
        
        
        //int aCharCount = 0;
        
        for(int aIndex=0;aIndex<(pFileList->mCount);aIndex++)
        {
            FString *aPath = (FString *)(pFileList->Fetch(aIndex));
            
            
            if(aPath)
            {
                FImage aImage;
                aImage.Load(aPath->c());
                
                if((aSequenceWidth == -1) && (aImage.mWidth > 0))
                {
                    aSequenceWidth = aImage.mWidth;
                    aSequenceHeight = aImage.mHeight;
                    
                }
                
                if(aImage.mWidth > 0)
                {
					if(aImage.IsBlank() == false)
					{
						if((aImage.mWidth != aSequenceWidth) || (aImage.mHeight != aSequenceHeight))
						{

							//Log("SEQUENCE ERROR [%d x %d] != [%d %d] (%s)\n", aImage.mWidth, aImage.mHeight, aSequenceWidth, aSequenceHeight, aPath->c());

							aImage.Kill();

							aReturn = false;

							break;
						}
						else
						{
							int aPaddingTop = -1;
							int aPaddingRight = -1;
							int aPaddingBottom = -1;
							int aPaddingLeft = -1;

							aImage.GetEdges(aPaddingLeft, aPaddingRight, aPaddingTop, aPaddingBottom);

							int aInsetTop = aPaddingTop;
							int aInsetRight = ((aImage.mWidth - aPaddingRight));
							int aInsetBottom = ((aImage.mHeight - aPaddingBottom));
							int aInsetLeft = aPaddingLeft;

							//Log("Ins[%d %d %d %d]\n", aInsetTop, aInsetRight, aInsetBottom, aInsetLeft);

							if(aMinInsetTop == -1)aMinInsetTop = aInsetTop;
							else if(aInsetTop < aMinInsetTop)aMinInsetTop = aInsetTop;

							if(aMinInsetRight == -1)aMinInsetRight = aInsetRight;
							else if(aInsetRight < aMinInsetRight)aMinInsetRight = aInsetRight;

							if(aMinInsetBottom == -1)aMinInsetBottom = aInsetBottom;
							else if(aInsetBottom < aMinInsetBottom)aMinInsetBottom = aInsetBottom;

							if(aMinInsetLeft == -1)aMinInsetLeft = aInsetLeft;
							else if(aInsetLeft < aMinInsetLeft)aMinInsetLeft = aInsetLeft;
						}
					}
                }
            }
        }
        
        //Log("Best Crop For The [%d x %d] Seq Is (%d %d %d %d)\n", aSequenceWidth, aSequenceHeight, aMinInsetLeft, aMinInsetTop, aMinInsetRight, aMinInsetBottom);
        
        
        if(aMinInsetRight < aMinInsetLeft)
        {
            aMinInsetLeft = aMinInsetRight;
        }
        
        if(aMinInsetLeft < aMinInsetRight)
        {
            aMinInsetRight = aMinInsetLeft;
        }
        
        if(aMinInsetTop < aMinInsetBottom)
        {
            aMinInsetBottom = aMinInsetTop;
        }
        
        if(aMinInsetBottom < aMinInsetTop)
        {
            aMinInsetTop = aMinInsetBottom;
        }
        
        //Log("2 - Best Crop For The [%d x %d] Seq Is (%d %d %d %d)\n", aSequenceWidth, aSequenceHeight, aMinInsetLeft, aMinInsetTop, aMinInsetRight, aMinInsetBottom);
    }

	pCropX = aMinInsetLeft;
	pCropY = aMinInsetTop;
	pCropWidth = aSequenceWidth - (aMinInsetRight + aMinInsetLeft);
	pCropHeight = aSequenceHeight - (aMinInsetTop + aMinInsetBottom);
    
    return aReturn;
}


FImageBundlerLoadNode *FImageBundler::FetchNode(char *pName)
{
    FImageBundlerLoadNode *aReturn=0;
    
    if(mLoadSequential && false)
    {
        if(mSequentialLoadIndex >= 0 && mSequentialLoadIndex < mLoadNodeList.mCount)
        {
            aReturn = ((FImageBundlerLoadNode*)mLoadNodeList.Fetch(mSequentialLoadIndex));
        }
        mSequentialLoadIndex++;
    }
    else
    {
        
        EnumList(FImageBundlerLoadNode, aNode, mLoadNodeList)
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

FImageBundlerLoadNode::FImageBundlerLoadNode()
{
    mX=0;
    mY=0;
    
    mWidth=0;
    mHeight=0;
    
    
    //mBundleWidth=0;
    //mBundleHeight=0;
    
    mOriginalWidth=0;
    mOriginalHeight=0;
    
    mOffsetX=0;
    mOffsetY=0;
    
    mRotated=false;
}

FImageBundlerLoadNode::~FImageBundlerLoadNode()
{
    
}


FImageBundlerLoadNode *FImageBundlerLoadNode::Clone()
{
    FImageBundlerLoadNode *aReturn = new FImageBundlerLoadNode();
    
    //aReturn->mBundleWidth = mBundleWidth;
    //aReturn->mBundleHeight = mBundleHeight;
    
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
    
    aReturn->mName=mName;
    
    return aReturn;
}



FImageBundlerSaveNode::FImageBundlerSaveNode()
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
    
    mRotated=false;
    mCanRotate=true;
}

FImageBundlerSaveNode::~FImageBundlerSaveNode()
{
    delete mImage;
    mImage=0;
}

void FImageBundlerSaveNode::Rotate()
{
    if(!mRotated)
    {
        mRotated=true;
        int aHold=mWidth;
        mWidth=mHeight;
        mHeight=aHold;
    }
}

void FImageBundlerSaveNode::Unrotate()
{
    if(mRotated)
    {
        mRotated=false;
        int aHold=mWidth;
        mWidth=mHeight;
        mHeight=aHold;
    }
}
