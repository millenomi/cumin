/*
 *  CuData.h
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CuObject.h"

#ifndef Cu__Data_h__
#define Cu__Data_h__

typedef void CuData;

extern CuData* CuDataMake(const void* bytes, size_t size);
extern CuData* CuDataMakeNoCopy(const void* bytes, size_t size);

extern const void* CuDataGetBytes(CuData* data);
extern size_t CuDataGetSize(CuData* data);

#endif