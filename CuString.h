/*
 *  CuString.h
 *  Cumin
 *
 *  Created by ∞ on 13/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include <stdint.h>
#include "CuObject.h"
#include "CuRange.h"
#include "CuData.h"

#ifndef Cu__String_h__
#define Cu__String_h__

typedef CuObject CuString;
typedef uint16_t CuChar; // TODO

enum {
	CuEncodingASCII,
	CuEncodingISOLatin1,
	// CuEncodingUTF8,
};
typedef uint32_t CuEncoding;

extern CuString* CuStringMakeWithCharacters(CuChar* chars, size_t count);

// do NOT have a terminating NULL byte at the end of chars. Use ...WithCString instead in that case.
extern CuString* CuStringMakeWithBytes(const uint8_t* chars, size_t count, CuEncoding encoding);
extern CuString* CuStringMakeWithCString(const uint8_t* chars, CuEncoding encoding);

extern CuString* CuStringMakeWithData(CuData* data, CuEncoding encoding);

extern uint8_t CuStringGetLength(CuString* string);

// Supports CuRangeEntireContent().
extern void CuStringGetCharactersInRange(CuString* string, CuChar* chars, CuRange r);

// Returns CuNotFound if not found.
extern size_t CuStringSearchForSubstring(CuString* string, CuString* substring);

#endif // #ifndef Cu__String_h__
