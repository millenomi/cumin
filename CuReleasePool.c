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
#include <stdio.h>

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

void _CuReleasePoolDebugDump();
void _CuReleasePoolDebugDumpEntry(CuReleasePoolEntry* entry);

void CuReleasePoolPush() {
	CuReleasePoolEntry* e = malloc(sizeof(CuReleasePoolEntry));
	e->Type = CuReleasePoolEntryPush;
	e->NextEntry = CuReleasePoolEntriesListTop;
	
	CuReleasePoolEntriesListTop = e;
}

void CuReleasePoolPop() {
	CuReleasePoolEntry* entry = CuReleasePoolEntriesListTop;
	while (entry) {
		if (entry->Type == CuReleasePoolEntryPush)
			break;

		_CuReleasePoolDebugDumpEntry(entry);
		
		CuRelease(entry->Object);
		CuReleasePoolEntry* self = entry;
		entry = entry->NextEntry;
		free(self);
	}
	CuReleasePoolEntriesListTop = entry;
}

void _CuReleasePoolDebugDump() {
	CuReleasePoolEntry* entry = CuReleasePoolEntriesListTop;
	while (entry) {
		_CuReleasePoolDebugDumpEntry(entry);
		entry = entry->NextEntry;
	}
	fprintf(stderr, "\n");
}

void _CuReleasePoolDebugDumpEntry(CuReleasePoolEntry* entry) {
	fprintf(stderr, "Entry (%p): ", entry);
	switch (entry->Type) {
		case CuReleasePoolEntryPush:
			fprintf(stderr, "PUSH.");
			break;
			
		case CuReleasePoolEntryReleaseLater: {
			fprintf(stderr, "RELEASE LATER for ");
			CuShow(entry->Object);
		}
			break;
			
		default:
			break;
	}
	fprintf(stderr, "\n");	
}

extern CuObject* CuReleaseLater(CuObject* o) {
	CuReleasePoolEntry* e = malloc(sizeof(CuReleasePoolEntry));
	e->Type = CuReleasePoolEntryReleaseLater;
	e->Object = o;
	e->NextEntry = CuReleasePoolEntriesListTop;
	
	CuReleasePoolEntriesListTop = e;	

	_CuReleasePoolDebugDump();
	
	return o;
}

void _CuReleasePoolPopForScope(int* i) {
	CuReleasePoolPop();
}
