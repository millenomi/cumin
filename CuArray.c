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

// pseudovtable
typedef struct {
	CuObjectKindInfoFields;
	CuObject* (*ObjectAtIndex)(CuArray* a, size_t index);
	size_t (*Count)(CuArray* a);
	void (*AllObjects)(CuArray* a, CuObject** objects);
} CuArrayObjectKind;


// Immutable impls
static CuObject* CuArrayImmutableGetObjectAtIndex(CuArray* a, size_t index);
static size_t CuArrayImmutableGetCount(CuArray* a);
static void CuArrayImmutableGetAllObjects(CuArray* a, CuObject** objects);

static CuArrayObjectKind CuArrayImmutableKind = {
	// Kind info
	"CuArray",
	sizeof(CuArrayActual),
	NULL,
	(CuFinalizer) &CuArrayDestroy,
	
	&CuArrayImmutableGetObjectAtIndex,
	&CuArrayImmutableGetCount,
	&CuArrayImmutableGetAllObjects,
};


// ~ Constructor/Destructor (immutable) ~

static void CuArrayDestroy(CuArrayActual* me) {
	for (size_t i = 0; i < me->Count; i++)
		CuRelease(me->Objects[i]);
	free(me->Objects);
}

CuArray* CuArrayMake(CuObject** objects, size_t count) {
	CuArrayActual* me = CuAlloc((CuObjectKindInfo*) &CuArrayImmutableKind);
	
	if (count > 0) {
		me->Objects = malloc(sizeof(CuObject*) * count);
		memcpy(me->Objects, objects, sizeof(CuObject*) * count);
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

static CuObject* CuArrayImmutableGetObjectAtIndex(CuArray* a, size_t index) {
	return CuArrayGetActual(a)->Objects[index];
}

static size_t CuArrayImmutableGetCount(CuArray* a) {
	return CuArrayGetActual(a)->Count;	
}

static void CuArrayImmutableGetAllObjects(CuArray* a, CuObject** objects) {
	memcpy(CuArrayGetActual(a)->Objects, objects, CuArrayGetActual(a)->Count);
}

CuObject* CuArrayGetObjectAtIndex(CuArray* array, size_t index) {
	return ((CuArrayObjectKind*) CuObjectGetKindInfo((CuObject*) array))->ObjectAtIndex(array, index);
}

size_t CuArrayGetCount(CuArray* array) {
	return ((CuArrayObjectKind*) CuObjectGetKindInfo((CuObject*) array))->Count(array);
}

void CuArrayGetAllObjects(CuArray* array, CuObject** objects) {
	((CuArrayObjectKind*) CuObjectGetKindInfo((CuObject*) array))->AllObjects(array, objects);
}


// ~ Mutation methods ~

//static CuObject* CuArrayMutableGetObjectAtIndex(CuArray* a, size_t index);
//static size_t CuArrayMutableGetCount(CuArray* a);
//static void CuArrayMutableGetAllObjects(CuArray* a, CuObject** objects);
//
//static CuArrayObjectKind CuArrayImmutableKind = {
//	&CuArrayKindInfo,
//	&CuArrayMutableGetObjectAtIndex,
//	&CuArrayMutableGetCount,
//	&CuArrayMutableGetAllObjects,
//};
//
//typedef struct {
//	CuObjectFields;
//	
//
//CuObject* CuArrayMutableGetObjectAtIndex(CuArray* a, size_t index);
//size_t CuArrayMutableGetCount(CuArray* a);
//void CuArrayMutableGetAllObjects(CuArray* a, CuObject** objects);



// TODO
void CuArrayInsertObjectAtIndex(CuMutableArray* a, size_t index) {}
void CuArrayRemoveObjectAtIndex(CuMutableArray* a, size_t index) {}

void CuArrayAddObject(CuMutableArray* a, CuObject* o) {}
