/*
 *  CuString.c
 *  Cumin
 *
 *  Created by ∞ on 13/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuString.h"

#include <string.h>

typedef struct {
	CuObjectFields;
	CuChar* Characters;
	size_t Length;
} CuStringInternals;
#define CuS(x) ((CuStringInternals*)(x))

static void CuStringDestroy(CuString* s);

static CuObjectKind CuStringKind = {
	"CuString",
	sizeof(CuStringInternals),
	&CuStringDestroy,
};

CuString* CuStringMakeWithCharacters(CuChar* chars, size_t count) {
	CuStringInternals* s = CuAlloc(&CuStringKind);
	s->Characters = count > 0? malloc(count * sizeof(CuChar)) : NULL;
	if (count > 0)
		memcpy(s->Characters, chars, count);
	s->Length = count;
	
	return CuReleaseLater(s);
}

static CuString* CuStringMakeWithASCIIBytes(const uint8_t* chars, size_t count);
static CuString* CuStringMakeWithISOLatin1Bytes(const uint8_t* chars, size_t count);

CuString* CuStringMakeWithBytes(const uint8_t* chars, size_t count, CuEncoding encoding) {
	switch (encoding) {
		case CuEncodingASCII:
			return CuStringMakeWithASCIIBytes(chars, count);
			
		case CuEncodingISOLatin1:
			return CuStringMakeWithISOLatin1Bytes(chars, count);
			
		default:
			assert(false);
			return NULL;
	}
}

CuString* CuStringMakeWithCString(const uint8_t* chars, CuEncoding encoding) {
	return CuStringMakeWithBytes(chars, strlen((const char*) chars), encoding);
}

CuString* CuStringMakeWithData(CuData* data, CuEncoding encoding) {
	return CuStringMakeWithBytes(CuDataGetBytes(data), CuDataGetSize(data), encoding);
}

static CuString* CuStringMakeWithISOLatin1Bytes(const uint8_t* chars, size_t count) {
	// We're lucky all ISO Latin 1 characters are valid Unicode code points with the same semantics :)
	
	CuChar* c = alloca(count);

	size_t i; for (i = 0; i < count; i++) {
		c[i] = (CuChar) chars[i];
	}
	
	return CuStringMakeWithCharacters(c, count);
}

static CuString* CuStringMakeWithASCIIBytes(const uint8_t* chars, size_t count) {
	// Same as above, but returns NULL for bytes above 127.
	
	CuChar* c = alloca(count);
	
	size_t i; for (i = 0; i < count; i++) {
		if (chars[i] > 127)
			return NULL;
		c[i] = (CuChar) chars[i];
	}
	
	return CuStringMakeWithCharacters(c, count);
}

static void CuStringDestroy(CuString* s) {
	if (CuS(s)->Characters)
		free(CuS(s)->Characters);
}

// ~ 

uint8_t CuStringGetLength(CuString* string) {
	return CuS(string)->Length;
}

// Supports CuRangeEntireContent().
void CuStringGetCharactersInRange(CuString* string, CuChar* chars, CuRange r) {
	if (CuRangeEquals(r, CuRangeEntireContent())) {
		r.Position = 0;
		r.Length = CuS(string)->Length;
	}
	
	// YAY POINTER ARITHMETICS
	memcpy(chars, CuS(string)->Characters + r.Position, r.Length);
}

// Returns CuNotFound if not found.
size_t CuStringSearchForSubstring(CuString* string, CuString* substring) {
	// TODO
	return CuNotFound;
}
