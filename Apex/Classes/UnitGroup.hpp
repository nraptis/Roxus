//
//  UnitGroupGroup.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/30/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef UNIT_GROUP_HPP
#define UNIT_GROUP_HPP

#include "FList.hpp"
#include "FObject.h"

class Unit;
class UnitGroup : public FObject {
public:

    UnitGroup();
    virtual ~UnitGroup();


    //Unit                            *mLeader;
    //New rule, Unit #0 is always the leader...
    Unit                            *Leader();
    bool                            IsLeader(Unit *pUnit);

    int                             Count();

    FList                           mUnitList;

    void                            Refresh();

    bool                            ContainsUnit(Unit *pUnit);

    void                            SetNeedsRepath();

    //Try to only call this when you are at or near the end of a
    //path segment, this will cancel all units from walking and snap
    //them into position...
    void                            Halt();


    //Assuming we are not yet deployed and want a ubiquitous speed...
    void                            SetDeploySpeed(float pSpeed);

    //mTestSingleGroupSpawnSpeed = 2.0f;
    //mTestDragGroupSpawnSpeed = 0.85f;


    void                            AddUnit(Unit *pUnit);
    bool                            RemoveUnit(Unit *pUnit);
    
    void                            DrawConnections(bool pSelected);

    
};

#endif
