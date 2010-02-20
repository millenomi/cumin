//
//  CuObjectTests.m
//  Cumin
//
//  Created by ∞ on 20/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "CuObjectTests.h"

typedef struct {
	CuObjectKind* kind;
	BOOL initCalled;
	BOOL* destroyCalled;
} CuTestObject;

static void CuTestObjectInitialize(CuTestObject* o) {
	o->initCalled = YES;
	o->destroyCalled = NULL;
}

static void CuTestObjectDestroy(CuTestObject* o) {
	*(o->destroyCalled) = YES;
}

@implementation CuObjectTests

- (void) testAlloc;
{	
	CuObjectKindInfo info = {
		sizeof(CuTestObject),
		(CuInitializer) &CuTestObjectInitialize,
		(CuFinalizer) &CuTestObjectDestroy
	};
	
	CuObjectKind kind = { &info };
	
	CuTestObject* o = CuAlloc(&kind);
	STAssertTrue(o->initCalled, @"Init called");
	STAssertTrue(o->destroyCalled == NULL, @"No destroy variable set");
	
	BOOL destroyCalled = NO;
	o->destroyCalled = &destroyCalled;
	
	CuRetain(o);
	CuRelease(o);
	STAssertFalse(destroyCalled, @"Destroy wasn't called");
	CuRelease(o);
	STAssertTrue(destroyCalled, @"Destroy was called");
}

@end
