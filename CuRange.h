
#include <sys/types.h>
#include <stdint.h>
#include <CuCompilerTools.h>
#include <assert.h>
#include <stdbool.h>

#ifndef Cu__Range_h__
#define Cu__Range_h__

#define CuNotFound SIZE_MAX

typedef struct {
	size_t Position;
	size_t Length;
} CuRange;

CuInlineFunction CuRange CuMakeRange(size_t position, size_t length) CuFunctionAttributeAlwaysInline;
CuInlineFunction CuRange CuMakeRangeBetweenIndexes(size_t from, size_t to) CuFunctionAttributeAlwaysInline;
CuInlineFunction bool CuRangeEquals(CuRange a, CuRange b) CuFunctionAttributeAlwaysInline;

CuInlineFunction CuRange CuMakeRange(size_t position, size_t length) {
	CuRange r;
	r.Position = position; r.Length = length;
	return r;
}

CuInlineFunction CuRange CuMakeRangeBetweenIndexes(size_t from, size_t to) {
	assert(from <= to);
	
	CuRange r;
	r.Position = from; r.Length = to - from;
	return r;
}

CuInlineFunction bool CuRangeEquals(CuRange a, CuRange b) {
	return a.Position == b.Position && a.Length == b.Length;
}


#define CuRangeNotFound() (CuMakeRange(CuNotFound, CuNotFound))

// Some functions can accept this as a parameter to mean "use entire contents of something". ONLY functions that explicitly say they support it can use it. Never returned.
#define CuRangeEntireContent() (CuMakeRange(0, SIZE_MAX))

#endif // #ifndef Cu__Range_h__
