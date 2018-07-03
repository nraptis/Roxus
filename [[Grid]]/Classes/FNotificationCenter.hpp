//
//  FNotificationCenter.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FNotificationCenter_hpp
#define FNotificationCenter_hpp

#include "FList.h"
#include "FString.h"
#include "FHashMap.hpp"
#include "FNotificationBucket.hpp"
#include "FHashTable.hpp"
#include "FCanvas.hpp"

class FCanvas;
class FNotificationCenter {
public:
    
    FNotificationCenter();
    virtual ~FNotificationCenter();

    void                            Register(FCanvas *pReciever, const char *pNotification);
    void                            Unregister(FCanvas *pReciever, const char *pNotification);
    void                            Unregister(FCanvas *pReciever);

    void                            Post(FCanvas *pSender, const char *pNotification);
    void                            Post(const char *pNotification);

    void                            Print();

protected:
    FHashTable                      mSendMap;
    FNotificationBucket             mNotifyBucket;

    FList                           mNodeList;
};

#endif

