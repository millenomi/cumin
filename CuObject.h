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

typedef void CuObject;

typedef struct CuObjectKindInfo {
	size_t InstancesSize;
	void (*Initialize)(void* o);
	void (*Destroy)(void* o);
} CuObjectKindInfo;

typedef struct CuObjectKind {
	CuObjectKindInfo* CuObjectKindInfo;
} CuObjectKind;

typedef struct CuObjectBase {
	CuObjectKind* CuObjectKind;
	uint32_t CuRetainCount;
} CuObjectBase;

#define CuGetObjectBase(a) ((CuObjectBase*)a)
#define CuGetObjectKind(a) (CuGetObjectBase(a)->CuObjectKind)
#define CuGetObjectKindInfo(a) (CuGetObjectBase(a)->CuObjectKind->CuObjectKindInfo)

extern void CuAlloc(CuObjectKind* kind);

extern void CuRetain(CuObject* o);
extern void CuRelease(CuObject* o);
