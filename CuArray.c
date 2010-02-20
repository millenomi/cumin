/*
 *  CuArray.c
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuArray.h"

typedef struct {
	CuObjectKind* kind;
	void* objects;
	size_t count;
} CuArrayActual;
#define CuArrayGetActual(x) ((CuArrayActual*)x)

const CuObjectKindInfo CuArrayKindInfo = {
	sizeof(CuArrayActual),
	(void*)0,
	&CuArrayDestroy
};
const CuObjectKind CuArrayKind = { &CuArrayKindInfo };


CuArray* CuArrayCreate(CuObject** objects, size_t count) {
	CuArrayActual* me = CuAlloc(&CuArrayKind);
	
	if (count > 0) {
		me->objects = malloc(sizeof(CuObject*) * count);
		memcpy(me->objects, objects, count);
	} else
		me->objects = NULL;
	
	me->count = count;
	return (CuArray*) me;
}

extern CuArray* CuArrayGetEmpty() {
	static CuArray* empty = NULL; if (!empty)
		empty = CuArrayCreate(NULL, 0);
	return empty;
}

extern CuMutableArray* CuArrayCreateMutable() {
	return NULL; // TODO
}

CuArray* CuArrayCreateCopy(CuArray* a) {
	// TODO
	return NULL;
}

CuObject* CuArrayGetObjectAtIndex(CuArray* a, size_t index) {
	// TODO mutable	
	return CuArrayGetActual(a)->objects[index];
}

size_t CuArrayGetCount(CuArray* a) {
	// TODO mutable
s	return CuArrayGetActual(a)->count;
}

// TODO
void CuArrayInsertObjectAtIndex(CuMutableArray* a, size_t index) {}
void CuArrayRemoveObjectAtIndex(CuMutableArray* a, size_t index) {}

void CuArrayAddObject(CuMutableArray* a, CuObject* o) {}
