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
	CuObject** Objects;
	size_t Count;
} CuArrayActual;
#define CuArrayGetActual(x) ((CuArrayActual*)x)

static void CuArrayDestroy(CuArrayActual* a);

static CuObjectKindInfo CuArrayKindInfo = {
	"CuArray",
	sizeof(CuArrayActual),
	NULL,
	(CuFinalizer) &CuArrayDestroy
};
static CuObjectKind CuArrayKind = { &CuArrayKindInfo };


// ~ Constructor/Destructor (immutable) ~

static void CuArrayDestroy(CuArrayActual* me) {
	for (size_t i = 0; i < me->Count; i++)
		CuRelease(me->Objects[i]);
	free(me->Objects);
}

CuArray* CuArrayMake(CuObject** objects, size_t count) {
	CuArrayActual* me = CuAlloc(&CuArrayKind);
	
	if (count > 0) {
		me->Objects = malloc(sizeof(CuObject*) * count);
		memcpy(me->Objects, objects, count);
		for (size_t i = 0; i < count; i++)
			CuRetain(me->Objects[i]);
	} else
		me->Objects = NULL;
	
	me->Count = count;
	return CuReleaseLater(me);
}

CuArray* CuArrayGetEmpty() {
	static CuArray* empty = NULL; if (!empty)
		empty = CuArrayMake(NULL, 0);
	return empty;
}

CuArray* CuArrayMakeCopy(CuArray* a) {
	size_t count = CuArrayGetCount(a);
	CuObject** objects = alloca(sizeof(CuObject*) * count);
	CuArrayGetAllObjects(a, objects);
	return CuArrayMake(objects, count);
}


// ~ Accessing ~

CuObject* CuArrayGetObjectAtIndex(CuArray* array, size_t index) {
	// TODO mutable
	return CuArrayGetActual(array)->Objects[index];
}

size_t CuArrayGetCount(CuArray* array) {
	// TODO mutable
	return CuArrayGetActual(array)->Count;
}

void CuArrayGetAllObjects(CuArray* a, CuObject** objects) {
	// TODO mutable
	memcpy(CuArrayGetActual(a)->Objects, objects, CuArrayGetActual(a)->Count);
}


// ~ Mutation methods ~

// TODO
void CuArrayInsertObjectAtIndex(CuMutableArray* a, size_t index) {}
void CuArrayRemoveObjectAtIndex(CuMutableArray* a, size_t index) {}

void CuArrayAddObject(CuMutableArray* a, CuObject* o) {}
