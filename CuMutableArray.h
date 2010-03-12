/*
 *  CuMutableArray.h
 *  Cumin
 *
 *  Created by ∞ on 12/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import "CuObject.h"
#import "CuArray.h"

typedef CuArray CuMutableArray;

// You can use all methods that take a CuArray on CuMutableArray.

extern CuMutableArray* CuArrayMakeMutable();
extern CuMutableArray* CuArrayMakeMutableCopy(CuArray* a);

extern void CuArrayAddObject(CuMutableArray* a, CuObject* o);
extern void CuArrayInsertObjectAtIndex(CuMutableArray* a, CuObject* o, size_t index);
extern void CuArrayRemoveObjectAtIndex(CuMutableArray* a, size_t index);

