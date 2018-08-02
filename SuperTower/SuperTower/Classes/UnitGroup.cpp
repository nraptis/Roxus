//
//  UnitGroupGroup.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/30/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "GLApp.hpp"
#include "UnitGroup.hpp"
#include "Unit.hpp"

UnitGroup::UnitGroup() {

}

UnitGroup::~UnitGroup() {
    
}

void UnitGroup::Refresh() {
    EnumList(Unit, aUnit, mUnitList) {
        if (aUnit == mLeader) {
            aUnit->mLeader = true;
        } else {
            aUnit->mLeader = false;
        }
    }
}

bool UnitGroup::ContainsUnit(Unit *pUnit) {
    return mUnitList.Exists(pUnit);
}

