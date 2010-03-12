/*
 *  CuNumber.h
 *  Cumin
 *
 *  Created by ∞ on 12/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuObject.h"
#include <stdint.h>

#ifndef Cu__Number_h__
#define Cu__Number_h__

typedef CuObject CuNumber;

CuNumber* CuNumberMakeFromInteger(uint64_t integerNumber);
CuNumber* CuNumberMakeFromDouble(long double doubleNumber);

uint64_t CuNumberGetInteger(CuNumber* n);
long double CuNumberGetDouble(CuNumber* n);

#endif // Cu__Number_h__