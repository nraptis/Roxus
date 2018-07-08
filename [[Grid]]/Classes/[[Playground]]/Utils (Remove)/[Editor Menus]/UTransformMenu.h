//
//  UTransformMenu.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef UTIL_TRANSFORM_MENU_H
#define UTIL_TRANSFORM_MENU_H

//#include "UMenu.h"

#include "UMenuStyleExtended.h"


class UTransformMenu : public UMenu
{
public:
    UTransformMenu();
    virtual ~UTransformMenu();
    
    
    virtual void                                Notify(void *pSender);
    virtual void                                SetSelectedNode(UNode *pNode);
    
	UMenuPane                                   *mControlPane;

	ULabel										*mInfoLabelTitleX;
	ULabel										*mInfoLabelX;

	ULabel										*mInfoLabelTitleY;
	ULabel										*mInfoLabelY;




	UMenuPane                                   *mCreatePane;

    
};

#endif /* defined(___015_Fleet_XP__UTransformMenu__) */
