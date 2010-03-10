/*
 *  CuObject.h
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Cu__Object_h__
#define Cu__Object_h__ 1

typedef void CuObject;

typedef void (*CuInitializer)(void* o);
typedef void (*CuFinalizer)(void* o);

typedef struct CuObjectKindInfo {
	char* Name; // must remain valid as long as this struct does.
	size_t InstancesSize;
	CuInitializer Initialize;
	CuFinalizer Destroy;
} CuObjectKindInfo;


#define CuObjectKindFields \
	CuObjectKindInfo* CuObjectKindInfo


typedef struct CuObjectKind {
	CuObjectKindFields;
} CuObjectKind;


#define CuObjectFields \
	CuObjectKind* CuObjectKind; \
	uint32_t CuRetainCount


typedef struct CuObjectBase {
	CuObjectFields;
} CuObjectBase;

#define CuObjectGetBase(a) ((CuObjectBase*)a)
#define CuObjectGetKind(a) (CuObjectGetBase(a)->CuObjectKind)

static inline CuObjectKindInfo* CuObjectGetKindInfo(CuObject* o) {
	return CuObjectGetBase(o)->CuObjectKind->CuObjectKindInfo;
}

extern void* CuAlloc(CuObjectKind* kind);

extern CuObject* CuRetain(CuObject* o);
extern void CuRelease(CuObject* o);

extern uint32_t CuObjectGetRetainCount(CuObject* o);

extern void CuShow(CuObject* o);

#include "CuReleasePool.h"

#endif
