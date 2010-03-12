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
	CuObjectBase* b = calloc(kind->InstancesSize, 1);
	b->CuObjectKind = kind;
	b->CuRetainCount = 1;
	return b;
}

CuObject* CuRetain(CuObject* o) {
	fprintf(stderr, "Retaining object: "); CuShow(o); fprintf(stderr, "\n");
	CuObjectGetBase(o)->CuRetainCount++;
	fprintf(stderr, "Retain count of object: "); CuShow(o); fprintf(stderr, "is %d. \n", (int) CuObjectGetBase(o)->CuRetainCount);
	return o;
}

void CuRelease(CuObject* o) {
	fprintf(stderr, "Releasing object: "); CuShow(o); fprintf(stderr, "\n");
	if (CuObjectGetBase(o)->CuRetainCount > 1) {
		CuObjectGetBase(o)->CuRetainCount--;
	} else {
		fprintf(stderr, "Destroying object: ");
		CuShow(o);
		fprintf(stderr, "\n");
		
		if (CuObjectGetKindInfo(o)->Finalize)
			CuObjectGetKindInfo(o)->Finalize(o);
		free(o);
	}
}

void CuShow(CuObject* o) {
	fprintf(stderr, "<%s %p>", CuObjectGetKindInfo(o)->Name, o);
	fflush(stderr);
}

