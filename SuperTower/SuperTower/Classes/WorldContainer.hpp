//
//  WorldContainer.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/9/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef WorldContainer_hpp
#define WorldContainer_hpp

#include "FCanvas.hpp"
#include "WorldGestureContainer.hpp"
#include "WorldTransformContainer.hpp"
#include "MapArena.hpp"
#include "EditorMapArena.hpp"

class WorldMenu;
class TimelineMenu;
class EditorMainMenu;
class ArenaMenu;
class WorldContainer : public FCanvas {
public:
    WorldContainer();
    virtual ~WorldContainer();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);

    virtual void                            Notify(void *pSender, const char *pNotification);

    WorldGestureContainer                   *mGestureContainer;
    WorldTransformContainer                 *mTransformContainer;
    
    MapArena                               *mArena;

    TimelineMenu                            *mTimelineMenu;
    WorldMenu                               *mTestMenu;

    ArenaMenu                               *mArenaMenu;


    EditorMainMenu                          *mEditorMenu;

};

extern WorldContainer *gWorldContainer;


#endif

