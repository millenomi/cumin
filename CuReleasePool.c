/*
 *  CuReleasePool.c
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CuReleasePool.h"
#include <stdint.h>
#include <stdbool.h>

enum {
	CuReleasePoolEntryPush,
	CuReleasePoolEntryReleaseLater,
};

typedef struct {
	uint8_t Type;
	CuObject* Object;
	void* NextEntry;
} CuReleasePoolEntry;

static CuReleasePoolEntry* CuReleasePoolEntriesListTop = NULL;

void CuReleasePoolPush() {
	CuReleasePoolEntry* e = malloc(sizeof(CuReleasePoolEntry));
	e->Type = CuReleasePoolEntryPush;
	e->NextEntry = CuReleasePoolEntriesListTop;
	
	CuReleasePoolEntriesListTop = e;
}

void CuReleasePoolPop() {
	CuReleasePoolEntry* entry = CuReleasePoolEntriesListTop;
	while (entry) {
		
		bool entryIsPush = (entry->Type == CuReleasePoolEntryPush);
		
		if (entry->Type == CuReleasePoolEntryReleaseLater)
			CuRelease(entry->Object);
		
		CuReleasePoolEntriesListTop = entry->NextEntry;
		free(entry);
		
		if (entryIsPush)
			break;

		entry = CuReleasePoolEntriesListTop;
	}
}

extern CuObject* CuReleaseLater(CuObject* o) {
	CuReleasePoolEntry* e = malloc(sizeof(CuReleasePoolEntry));
	e->Type = CuReleasePoolEntryReleaseLater;
	e->Object = o;
	e->NextEntry = CuReleasePoolEntriesListTop;
	
	CuReleasePoolEntriesListTop = e;	
	
	return o;
}

void _CuReleasePoolPopForScope(int* i) {
	CuReleasePoolPop();
}
