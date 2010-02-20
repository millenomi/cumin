/*
 *  CuData.c
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CuData.h"
#include <string.h>
#include <stdlib.h>

// ~ Layout ~

struct CuData {
	CuObjectFields;
	void* Bytes;
	size_t Size;
	bool OwnsBuffer;
};

#define CuDataGetFields(o) ((struct CuData*)o)

// Kind
static void CuDataFinalize(struct CuData* d);

static CuObjectKindInfo CuDataKindInfo = {
	sizeof(struct CuData),
	NULL,
	(CuFinalizer) &CuDataFinalize
};

static CuObjectKind CuDataKind = { &CuDataKindInfo };


// ~ Init/Finalize ~

CuData* CuDataCreate(void* bytes, size_t size) {
	struct CuData* c = CuAlloc(&CuDataKind);
	c->Bytes = malloc(size);
	memcpy(c->Bytes, bytes, size);
	c->Size = size;
	c->OwnsBuffer = true;
	
	return (CuData*) c;
}

CuData* CuDataCreateNoCopy(void* bytes, size_t size) {
	struct CuData* c = CuAlloc(&CuDataKind);
	c->Bytes = bytes;
	c->Size = size;
	c->OwnsBuffer = false;
	
	return (CuData*) c;	
}

static void CuDataFinalize(struct CuData* c) {
	if (c->OwnsBuffer)
		free(c->Bytes);
}

const void* CuDataGetBytes(CuData* data) {
	return CuDataGetFields(data)->Bytes;
}

size_t CuDataGetSize(CuData* data) {
	return CuDataGetFields(data)->Size;
}
