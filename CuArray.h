/*
 *  CuArray.h
 *  Cumin
 *
 *  Created by ∞ on 20/02/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "CuObject.h"

#ifndef Cu__Array_h__
#define Cu__Array_h__ 1

typedef void CuMutableArray;
typedef const CuMutableArray CuArray;

extern CuArray* CuArrayMake(CuObject** objects, size_t count);
extern CuArray* CuArrayGetEmpty();
extern CuMutableArray* CuArrayCreateMutable(); // TODO
extern CuArray* CuArrayMakeCopy(CuArray* a);

extern CuObject* CuArrayGetObjectAtIndex(CuArray* a, size_t index);
extern size_t CuArrayGetCount(CuArray* a);
extern void CuArrayGetAllObjects(CuArray* a, CuObject** objects);

extern void CuArrayInsertObjectAtIndex(CuMutableArray* a, size_t index);
extern void CuArrayRemoveObjectAtIndex(CuMutableArray* a, size_t index);

extern void CuArrayAddObject(CuMutableArray* a, CuObject* o);

#endif