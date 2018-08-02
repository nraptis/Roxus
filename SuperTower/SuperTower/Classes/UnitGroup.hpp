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
    
    Unit                            *mLeader;
    FList                           mUnitList;

    void                            Refresh();

    bool                            ContainsUnit(Unit *pUnit);

    
};

#endif
