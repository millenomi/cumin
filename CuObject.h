/*
 *  CuObject.h
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>

typedef void CuObject;

typedef void (*CuInitializer)(void* o);
typedef void (*CuFinalizer)(void* o);

typedef struct CuObjectKindInfo {
	size_t InstancesSize;
	CuInitializer Initialize;
	CuFinalizer Destroy;
} CuObjectKindInfo;

typedef struct CuObjectKind {
	CuObjectKindInfo* CuObjectKindInfo;
} CuObjectKind;


#define CuObjectFields \
	CuObjectKind* CuObjectKind; \
	uint32_t CuRetainCount


typedef struct CuObjectBase {
	CuObjectFields;
} CuObjectBase;

#define CuGetObjectBase(a) ((CuObjectBase*)a)
#define CuGetObjectKind(a) (CuGetObjectBase(a)->CuObjectKind)
#define CuGetObjectKindInfo(a) (CuGetObjectBase(a)->CuObjectKind->CuObjectKindInfo)

extern void* CuAlloc(CuObjectKind* kind);

extern void CuRetain(CuObject* o);
extern void CuRelease(CuObject* o);

extern uint32_t CuObjectGetRetainCount(CuObject* o);
