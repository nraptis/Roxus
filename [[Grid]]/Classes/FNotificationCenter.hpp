//
//  FNotificationCenter.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FNotificationCenter_hpp
#define FNotificationCenter_hpp

#include "FHashMap.hpp"
#include "FHashTable.hpp"
#include "FCanvas.hpp"
#include "FNotificationTable.hpp"
#include "FNotificationReceiverMap.hpp"

class FCanvas;
class FNotificationCenter {
public:
    FNotificationCenter();
    ~FNotificationCenter();
    
    void                            Register(FCanvas *pMenu, FCanvas *pButton, const char *pNotification);

    void                            Unregister(FCanvas *pMenu, FCanvas *pButton, const char *pNotification);
    void                            Unregister(FCanvas *pMenu);

    void                            Post(FCanvas *pButton, const char *pNotification);
    
    void                            Print();

protected:

    //"Forward" map...
    FNotificationTable              mSendTable;

    //"Backward" map...
    FNotificationReceiverMap        mRegisterTable;

    //Used for processing...
    FList                           mNodeList;
    FList                           mPostList;
};

#endif

