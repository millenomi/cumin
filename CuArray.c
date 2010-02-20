/*
 *  CuArray.c
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuArray.h"
#import <stdlib.h>
#include <string.h>

// ~ Kind & Instance layout (immutable) ~

typedef struct {
	CuObjectFields;
	CuObject** objects;
	size_t count;
} CuArrayActual;
#define CuArrayGetActual(x) ((CuArrayActual*)x)

static void CuArrayDestroy(CuArrayActual* a);

static CuObjectKindInfo CuArrayKindInfo = {
	sizeof(CuArrayActual),
	NULL,
	(CuFinalizer) &CuArrayDestroy
};
static CuObjectKind CuArrayKind = { &CuArrayKindInfo };


// ~ Constructor/Destructor (immutable) ~

static void CuArrayDestroy(CuArrayActual* me) {
	for (size_t i = 0; i < me->count; i++)
		CuRelease(me->objects[i]);
	free(me->objects);
}

CuArray* CuArrayCreate(CuObject** objects, size_t count) {
	CuArrayActual* me = CuAlloc(&CuArrayKind);
	
	if (count > 0) {
		me->objects = malloc(sizeof(CuObject*) * count);
		memcpy(me->objects, objects, count);
		for (size_t i = 0; i < count; i++)
			CuRetain(me->objects[i]);
	} else
		me->objects = NULL;
	
	me->count = count;
	return (CuArray*) me;
}

CuArray* CuArrayGetEmpty() {
	static CuArray* empty = NULL; if (!empty)
		empty = CuArrayCreate(NULL, 0);
	return empty;
}

CuArray* CuArrayCreateCopy(CuArray* a) {
	size_t count = CuArrayGetCount(a);
	CuObject** objects = alloca(sizeof(CuObject*) * count);
	CuArrayGetAllObjects(a, objects);
	return CuArrayCreate(objects, count);
}


// ~ Accessing ~

CuObject* CuArrayGetObjectAtIndex(CuArray* array, size_t index) {
	// TODO mutable
	return CuArrayGetActual(array)->objects[index];
}

size_t CuArrayGetCount(CuArray* array) {
	// TODO mutable
	return CuArrayGetActual(array)->count;
}


// ~ Mutation methods ~

// TODO
void CuArrayInsertObjectAtIndex(CuMutableArray* a, size_t index) {}
void CuArrayRemoveObjectAtIndex(CuMutableArray* a, size_t index) {}

void CuArrayAddObject(CuMutableArray* a, CuObject* o) {}
