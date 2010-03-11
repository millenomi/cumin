//
//  CuObjectTests.m
//  Cumin
//
//  Created by ∞ on 20/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "CuObjectTests.h"

typedef struct {
	CuObjectFields;
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
	CuObjectKindInfo kind = {
		"CuTestKind",
		sizeof(CuTestObject),
		(CuInitializer) &CuTestObjectInitialize,
		(CuFinalizer) &CuTestObjectDestroy
	};
	
	CuTestObject* o = CuAlloc(&kind);
	STAssertTrue(o->initCalled, @"Init called");
	STAssertTrue(o->destroyCalled == NULL, @"No destroy variable set");
	STAssertTrue(CuObjectGetRetainCount(o) == 1, @"Just-alloc'd objects have a retain count of 1.");
	
	BOOL destroyCalled = NO;
	o->destroyCalled = &destroyCalled;
	
	CuRetain(o);
	CuRelease(o);
	STAssertFalse(destroyCalled, @"Destroy wasn't called");
	CuRelease(o);
	STAssertTrue(destroyCalled, @"Destroy was called");
}

- (void) testStuffBehavesCorrectlyInTheFaceOfMultipleRetainsAndReleases;
{
	CuReleasePoolPush();
	
	char* test = "This is a test actually!";
	CuData* testData = CuDataMake(test, strlen(test) + 1);
	CuRetain(testData);
	CuRetain(testData);
	
	CuObject* object[] = { testData };
	(void) CuArrayMake(object, 1);

	CuRelease(testData);

	CuReleasePoolPop();
	
	CuRelease(testData);
}

@end
