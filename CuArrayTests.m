//
//  CuArrayTests.m
//  Cumin
//
//  Created by ∞ on 12/03/10.
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import "CuArrayTests.h"


@implementation CuArrayTests

- (void) testMutableArray;
{
	CuReleasePoolScope();
	
	CuMutableArray* m = CuArrayMakeMutable();
	CuArrayAddObject(m, CuNumberMakeFromInteger(12));
	CuArrayAddObject(m, CuNumberMakeFromInteger(34));
	CuArrayAddObject(m, CuNumberMakeFromInteger(567));
	
	STAssertTrue(CuArrayGetCount(m) == 3, @"Three items in the array");
	
	CuArrayInsertObjectAtIndex(m, CuNumberMakeFromInteger(888), 1);
	STAssertTrue(CuArrayGetCount(m) == 4, @"Four items in the array");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(m, 0)) == 12, @"The right item was returned");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(m, 1)) == 888, @"The right item was returned");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(m, 2)) == 34, @"The right item was returned");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(m, 3)) == 567, @"The right item was returned");

	CuArrayRemoveObjectAtIndex(m, 2);
	STAssertTrue(CuArrayGetCount(m) == 3, @"Three items in the array");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(m, 0)) == 12, @"The right item was returned");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(m, 1)) == 888, @"The right item was returned");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(m, 2)) == 567, @"The right item was returned");
	
	CuArray* im = CuArrayMakeCopy(m);
	STAssertTrue(CuArrayGetCount(im) == 3, @"Three items in the array");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(im, 0)) == 12, @"The right item was returned");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(im, 1)) == 888, @"The right item was returned");
	STAssertTrue(CuNumberGetInteger(CuArrayGetObjectAtIndex(im, 2)) == 567, @"The right item was returned");	
}

@end
