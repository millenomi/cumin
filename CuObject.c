/*
 *  CuObject.c
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuObject.h"
#include <stdlib.h>
#include <stdio.h>

void* CuAlloc(CuObjectKind* kind) {
	CuObjectBase* b = calloc(kind->CuObjectKindInfo->InstancesSize, 1);
	b->CuObjectKind = kind;
	b->CuRetainCount = 0;
	if (kind->CuObjectKindInfo->Initialize)
		kind->CuObjectKindInfo->Initialize(b);
	return b;
}

CuObject* CuRetain(CuObject* o) {
	CuGetObjectBase(o)->CuRetainCount++;
	return o;
}

void CuRelease(CuObject* o) {
	if (CuGetObjectBase(o)->CuRetainCount > 1) {
		CuGetObjectBase(o)->CuRetainCount--;
	} else {
		if (CuGetObjectKindInfo(o)->Destroy)
			CuGetObjectKindInfo(o)->Destroy(o);
		free(o);
	}
}

uint32_t CuObjectGetRetainCount(CuObject* o) {
	return CuGetObjectBase(o)->CuRetainCount;
}

void CuShow(CuObject* o) {
	fprintf(stderr, "<%s %p>", CuGetObjectKindInfo(o)->Name, o);
	fflush(stderr);
}
