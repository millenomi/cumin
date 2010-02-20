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

void CuAlloc(CuObjectKind* kind) {
	CuObjectBase* b = malloc(kind->CuObjectKindInfo->InstancesSize);
	b->CuObjectKind = kind;
	b->CuRetainCount = 0;
	if (kind->CuObjectKindInfo->Initialize)
		kind->CuObjectKindInfo->Initialize(b);
}

void CuRetain(CuObject* o) {
	CuGetObjectBase(o)->CuRetainCount++;
}

void CuRelease(CuObject* o) {
	if (CuGetObjectBase(o)->CuRetainCount > 1) {
		CuGetObjectBase(o)->CuRetainCount--;
	} else {
		CuGetObjectKindInfo(o)->Destroy(o);
		free(o);
	}
}
