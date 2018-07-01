//
//  UParentPane.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UParentPane__
#define ___015_Fleet_XP__UParentPane__

//#include "UMenu.h"

#include "UMenuStyleExtended.h"

class UParentPane : public UMenu
{
public:
    UParentPane();
    virtual ~UParentPane();

    virtual void                                Notify(void *pSender);
    virtual void                                SetSelectedNode(UNode *pNode);

	UMenuPane                                   *mRelationPane;

	USegment									*mRelationTypeSegment;

	UMenuPane                                   *mRelationXPane;
	UMenuPane                                   *mRelationYPane;

	USegment									*mRelationTypeSegmentX;
	USegment									*mRelationTypeSegmentY;

	UButton										*mButtonAdjustWorld;
	UButton										*mButtonMatchTransform;
	UButton										*mButtonResetOffset;


	UExtendedSlider								*mOffsetSliderX;
	UExtendedSlider								*mOffsetSliderY;


	//USegment									*mRelationBehaviorTypeSegment;





    
};

#endif /* defined(___015_Fleet_XP__UParentPane__) */
