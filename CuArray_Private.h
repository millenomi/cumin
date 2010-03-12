
#include "CuArray.h"

// pseudovtable
typedef struct {
	CuObjectKindInfoFields;
	CuObject* (*ObjectAtIndex)(CuArray* a, size_t index);
	size_t (*Count)(CuArray* a);
	void (*AllObjects)(CuArray* a, CuObject** objects);
} CuArrayObjectKind;
