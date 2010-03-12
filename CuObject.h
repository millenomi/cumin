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

// ---------------------------------
// Kind and object types.

typedef void CuObject;

typedef void (*CuFinalizer)(void* o);

#define CuObjectKindInfoFields \
	char* Name; \
	size_t InstancesSize; \
	CuFinalizer Finalize

typedef struct {
	CuObjectKindInfoFields;
} CuObjectKind;


#define CuObjectFields \
	CuObjectKind* CuObjectKind; \
	uint32_t CuRetainCount

typedef struct CuObjectBase {
	CuObjectFields;
} CuObjectBase;

// ---------------------------------
// Accessors to retrieve object info and kinds

static inline CuObjectBase* CuObjectGetBase(CuObject* object) {
	return (CuObjectBase*) object;
}

static inline CuObjectKind* CuObjectGetKindInfo(CuObject* o) {
	return CuObjectGetBase(o)->CuObjectKind;
}

static inline uint32_t CuObjectGetRetainCount(CuObject* o) {
	return CuObjectGetBase(o)->CuRetainCount;
}

// ---------------------------------
// Polymorphic function for all objects.

// Allocates an object. The object returned has been retained
// and will need to be released later.
extern void* CuAlloc(CuObjectKind* kind);

// Keeps an object around by raising its retain count.
// Needs to be balanced by a CuRelease.
extern CuObject* CuRetain(CuObject* o);

// Reduces an object's retain count, balancing a CuRetain or
// CuAlloc.
extern void CuRelease(CuObject* o);

// Reduces an object's retain count later for some amount of
// later. (See CuReleasePoolPop().)
extern CuObject* CuReleaseLater(CuObject* o);

// Prints a short description of the object. TODO
extern void CuShow(CuObject* o);


#include "CuReleasePool.h"

#endif
