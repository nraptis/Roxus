/*
 *  Utils.h
 *  Fly Swatter
 *
 *  Created by Nick Raptis on 12/27/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "stdafx.h"
#include "Font.h"

#ifndef UTILS_H
#define UTILS_H

FString Chop(FString pString, Font *pFont, int pWidth);
FString TicksToTime(int pTicks, int pUpdatesPerSecond=60);
FString RandomString(int pLength);

#endif