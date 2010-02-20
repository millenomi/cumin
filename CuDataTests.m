//
//  CuDataTests.m
//  Cumin
//
//  Created by ∞ on 20/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "CuDataTests.h"
#import "CuReleasePool.h"

@implementation CuDataTests

- (void) testCreation;
{ // CuWaitForDebugger(go);
	CuReleasePoolScope();
	
	NSData* cocoaData = [@"This is just a test" dataUsingEncoding:NSUTF8StringEncoding];
	CuData* cuminData = CuDataMake((void*)[cocoaData bytes], [cocoaData length]);
	
	STAssertTrue(CuDataGetBytes(cuminData) != NULL, @"Data has a backing store");
	STAssertEquals(CuDataGetSize(cuminData), [cocoaData length], @"Data is of the right length");
	STAssertTrue([cocoaData bytes] != CuDataGetBytes(cuminData), @"Data was copied");
	
	NSData* cocoaData2 = [NSData dataWithBytes:CuDataGetBytes(cuminData) length:CuDataGetSize(cuminData)];
	STAssertEqualObjects(cocoaData, cocoaData2, @"Data was copied accurately");
	
	cuminData = CuDataMakeNoCopy((void*)[cocoaData bytes], [cocoaData length]);
	
	STAssertTrue(CuDataGetBytes(cuminData) != NULL, @"Data has a backing store");
	STAssertEquals(CuDataGetSize(cuminData), [cocoaData length], @"Data is of the right length");
	STAssertEquals([cocoaData bytes], CuDataGetBytes(cuminData), @"Data was NOT copied");
	
	STAssertEqualObjects(cocoaData, cocoaData2, @"Original buffer wasn't clobbered by release");
}

@end
