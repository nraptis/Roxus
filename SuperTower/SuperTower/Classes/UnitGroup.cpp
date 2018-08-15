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

void UnitGroup::SetDeploySpeed(float pSpeed) {
    EnumList(Unit, aUnit, mUnitList) {
        aUnit->mWalkSpeed = pSpeed;
    }
}

void UnitGroup::DrawConnections(bool pSelected) {
    
    if (mUnitList.mCount <= 0) { return; }
    Unit *aPrev = (Unit *)(mUnitList.First());
    
    for (int i=1;i<mUnitList.mCount;i++) {
        Unit *aUnit = (Unit *)(mUnitList.mData[i]);
        
        float aPrevX = aPrev->mX;
        float aPrevY = aPrev->mY;
        
        float aX = aUnit->mX;
        float aY = aUnit->mY;
        
        if (pSelected) {
            Graphics::SetColor(1.0f, 1.0f, 0.66f, 0.85f);
        } else {
            Graphics::SetColor(0.55f, 0.55f, 0.55f, 0.85f);
        }
            
        Graphics::DrawLine(aPrevX, aPrevY, aX, aY, 3.0f);
        
        aPrev = aUnit;
    }
    
    for (int i=0;i<mUnitList.mCount;i++) {
        Unit *aUnit = (Unit *)(mUnitList.mData[i]);
        
        float aX = aUnit->mX;
        float aY = aUnit->mY;
        
        if (pSelected) {
            Graphics::SetColor(0.88f, 0.88f, 0.25f, 0.75f);
            Graphics::OutlineRect(aX - 7.0f, aY - 7.0f, 15.0f, 15.0f, 3.0f);
            
        } else {
            Graphics::SetColor(0.66f, 0.66f, 0.25f, 0.75f);
            Graphics::OutlineRect(aX - 4.0f, aY - 4.0f, 9.0f, 9.0f, 2.0f);
        }
        
    }
    
    
    
}


