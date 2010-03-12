/*
 *  CuNumber.c
 *  Cumin
 *
 *  Created by ∞ on 12/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuNumber.h"

typedef struct {
	CuObjectFields;
	
	bool IsInteger;
	uint64_t Integer;
	long double Double;
} CuNumberInternals;
#define CuN(x) ((CuNumberInternals*)(x))

static CuObjectKind CuNumberKind = {
	"CuNumber",
	sizeof(CuNumberInternals),
	NULL
};

CuNumber* CuNumberMakeFromInteger(uint64_t integerNumber) {
	CuNumber* n = CuAlloc(&CuNumberKind);
	CuN(n)->IsInteger = true;
	CuN(n)->Integer = integerNumber;
	return CuReleaseLater(n);
}

CuNumber* CuNumberMakeFromDouble(long double doubleNumber) {
	CuNumber* n = CuAlloc(&CuNumberKind);
	CuN(n)->IsInteger = false;
	CuN(n)->Double = doubleNumber;
	return CuReleaseLater(n);	
}

uint64_t CuNumberGetInteger(CuNumber* n) {
	if (CuN(n)->IsInteger)
		return CuN(n)->Integer;
	else
		return (uint64_t) CuN(n)->Double;
}

long double CuNumberGetDouble(CuNumber* n) {
	if (!CuN(n)->IsInteger)
		return (long double) CuN(n)->Integer;
	else
		return CuN(n)->Double;	
}
