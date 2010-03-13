
#ifndef Cu__CompilerTools_h__
#define Cu__CompilerTools_h__

// Compiler switch: CuCompilerDisableInline (if 0, all inline funcs are static instead).
#if CuCompilerDisableInline
#define CuInline
#else
#define CuInline inline
#endif

#if __GNUC__ >= 3
#define CuInlineFunction static inline
#define CuFunctionAttributeAlwaysInline __attribute__((always_inline))
#else
#define CuInlineFunction static CuInline
#define CuFunctionAttributeAlwaysInline
#endif


#if __GNUC__ >= 3
#define CuAttributeUnavailable __attribute__((unavailable))
#define CuAttributeDeprecated __attribute__((deprecated))
#else
#define CuAttributeUnavailable
#define CuAttributeDeprecated
#endif

#endif // #ifndef Cu__CompilerTools_h__
