/*
 *  CuReleasePool.h
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef Cu__ReleasePool_h__
#define Cu__ReleasePool_h__

#include "CuObject.h"

extern void CuReleasePoolPush();
extern void CuReleasePoolPop();

extern CuObject* CuReleaseLater(CuObject* o);

#define CuReleasePoolScope() \
	int CuReleasePoolScope##__LINE__ __attribute__((cleanup(_CuReleasePoolPopForScope))) = 0; CuReleasePoolPush()
extern void _CuReleasePoolPopForScope(int* i);

#endif