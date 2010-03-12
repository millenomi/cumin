/*
 *  CuMutableArray.c
 *  Cumin
 *
 *  Created by ∞ on 12/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuMutableArray.h"
#include <assert.h>
#include "CuArray_Private.h"

static void CuMutableArrayDestroy(CuObject* o);

static CuObject* CuMutableArrayGetObjectAtIndex(CuArray* a, size_t index);
static size_t CuMutableArrayGetCount(CuArray* a);
static void CuMutableArrayGetAllObjects(CuArray* a, CuObject** objects);


typedef struct {
	CuObject* Object;
	void* Next;
} CuMutableArrayLink;

typedef struct {
	CuObjectFields;
	size_t Count;
	CuMutableArrayLink* FirstLink;
	CuMutableArrayLink* LastLink;
} CuMutableArrayInternals;
#define CuMA(x) ((CuMutableArrayInternals*)(x))

static CuArrayObjectKind CuMutableArrayKind = {
	"CuMutableArray",
	sizeof(CuMutableArrayInternals),
	&CuMutableArrayDestroy,
	
	&CuMutableArrayGetObjectAtIndex,
	&CuMutableArrayGetCount,
	&CuMutableArrayGetAllObjects
};

// ~ Creating ~

extern CuMutableArray* CuArrayMakeMutable() {
	return CuReleaseLater(CuAlloc((CuObjectKind*)&CuMutableArrayKind));
}

extern CuMutableArray* CuArrayMakeMutableCopy(CuArray* a) {
	CuMutableArray* self = CuArrayMakeMutable();
	
	size_t count = CuArrayGetCount(a);
	CuObject** objects = alloca(count * sizeof(CuObject*));
	CuArrayGetAllObjects(a, objects);
	
	int i; for (i = 0; i < count; i++)
		CuArrayAddObject(self, objects[i]);
	
	return self;
}


// ~ Adding and removing ~

void CuArrayAddObject(CuMutableArray* a, CuObject* o) {
	CuMutableArrayLink* link = malloc(sizeof(CuMutableArrayLink));
	link->Object = CuRetain(o);
	link->Next = NULL;
	
	if (!CuMA(a)->FirstLink) {
		CuMA(a)->FirstLink = link;
		CuMA(a)->LastLink = link;
	} else {
		assert(CuMA(a)->LastLink != NULL);
		CuMA(a)->LastLink->Next = link;
		CuMA(a)->LastLink = link;
	}
	
	CuMA(a)->Count++;
}

static CuMutableArrayLink* CuMutableArrayLinkAtIndex(CuMutableArray* a, size_t index) {
	assert(index < CuMA(a)->Count);
	
	CuMutableArrayLink* link = CuMA(a)->FirstLink;
	while (index != 0) {
		link = link->Next;
		index--;
	}
	
	return link;
}

void CuArrayInsertObjectAtIndex(CuMutableArray* a, CuObject* o, size_t index) {
	bool mustUpdateCount = true;
	if (CuMA(a)->Count == index) {
		CuArrayAddObject(a, o);
		mustUpdateCount = false;
	} else if (index == 0) {
		CuMutableArrayLink* link = malloc(sizeof(CuMutableArrayLink));
		link->Object = CuRetain(o);
		link->Next = CuMA(a)->FirstLink;
		
		CuMA(a)->FirstLink = link;
	} else {
		CuMutableArrayLink* previousLink = CuMutableArrayLinkAtIndex(a, index - 1);
		
		CuMutableArrayLink* link = malloc(sizeof(CuMutableArrayLink));
		link->Object = CuRetain(o);
		link->Next = previousLink->Next;
		
		previousLink->Next = link;
	}
	
	if (mustUpdateCount)
		CuMA(a)->Count++;
}

void CuArrayRemoveObjectAtIndex(CuMutableArray* a, size_t index) {
	if (index == 0) {
		CuMutableArrayLink* link = CuMA(a)->FirstLink;
		CuMA(a)->FirstLink = link->Next;
		
		if (link == CuMA(a)->LastLink)
			CuMA(a)->LastLink = NULL;
		
		free(link);
	} else {
		CuMutableArrayLink* previousLink = CuMutableArrayLinkAtIndex(a, index - 1);
		CuMutableArrayLink* link = previousLink->Next;
		previousLink->Next = link->Next;
		
		if (link == CuMA(a)->LastLink)
			CuMA(a)->LastLink = NULL;
		
		free(link);
	}
	
	CuMA(a)->Count--;
}


// ~ Pseudovtable Impls ~

static CuObject* CuMutableArrayGetObjectAtIndex(CuArray* a, size_t index) {
	return CuMutableArrayLinkAtIndex(a, index)->Object;
}

static size_t CuMutableArrayGetCount(CuArray* a) {
	return CuMA(a)->Count;
}

static void CuMutableArrayGetAllObjects(CuArray* a, CuObject** objects) {
	CuMutableArrayLink* link = CuMA(a)->FirstLink;
	size_t index = 0;
	while (link) {
		objects[index] = link->Object;
		index++;
		link = link->Next;
	}
}

static void CuMutableArrayDestroy(CuObject* o) {
	CuMutableArrayLink* link = CuMA(o)->FirstLink;
	while (link) {
		CuRelease(link->Object);
		
		CuMutableArrayLink* toBeFreed = link;
		link = link->Next;
		
		free(toBeFreed);
	}
}
