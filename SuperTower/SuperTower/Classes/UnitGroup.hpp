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


    FList                           mUnitList;

    void                            Refresh();

    bool                            ContainsUnit(Unit *pUnit);

    bool                            RemoveUnit(Unit *pUnit);


    
};

#endif
