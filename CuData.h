/*
 *  CuData.h
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CuObject.h"

typedef void CuData;

extern CuData* CuDataCreate(void* bytes, size_t size);
extern CuData* CuDataCreateNoCopy(void* bytes, size_t size);

extern const void* CuDataGetBytes(CuData* data);
extern size_t CuDataGetSize(CuData* data);
