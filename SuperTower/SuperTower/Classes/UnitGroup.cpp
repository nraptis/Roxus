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

Unit *UnitGroup::Leader() {
    return (Unit *)mUnitList.First();
}

bool UnitGroup::IsLeader(Unit *pUnit) {
    bool aResult = false;
    if (pUnit != NULL && Leader() == pUnit) {
        aResult = true;
    }
    return aResult;
}


void UnitGroup::Refresh() {
    for (int aIndex = 0;aIndex<mUnitList.mCount;aIndex++) {
        Unit *aUnit = (Unit *)(mUnitList.mData[aIndex]);
        if (aIndex == 0) {
            aUnit->mIsLeader = true;
        } else {
            aUnit->mIsLeader = false;
        }
    }
}

int UnitGroup::Count() {
    return mUnitList.mCount;
}

bool UnitGroup::ContainsUnit(Unit *pUnit) {
    return mUnitList.Exists(pUnit);
}

void UnitGroup::AddUnit(Unit *pUnit) {

    if (pUnit != NULL) {

    if (mUnitList.Exists(pUnit) == false) {
        mUnitList.Add(pUnit);
        Refresh();
    }
        pUnit->mGroup = this;
    }
}

bool UnitGroup::RemoveUnit(Unit *pUnit) {
    bool aResult = false;
    if (mUnitList.Exists(pUnit)) {
        mUnitList.Remove(pUnit);
        aResult = true;
    }
    Refresh();
    return aResult;
}
