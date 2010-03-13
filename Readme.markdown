# Cumin

Cumin is a small library providing base services often used in apps. The goal is:

* Take the best parts of Apple's Core Foundation and Objective-C. Object-orientation, but lightweight.

* Pure C.

* As portable as possible. Portable means that it works and it makes little or no assumptions on what it has to work with! Ideally, the whole thing would require just some half-decent libc subset and maybe pthreads.

* Able to integrate smoothly into whatever run loop or event delivery structure it finds itself in.

* Be buildable with:
	
		gcc -shared -o libCumin.dylib *.c
		
	and nothing else. In fact, be buildable with the least amount of customization needed on the build process ever, and a small and well-known list of dependencies that do not require building or require only minimal effort.
	
## THE (Cumin) RULES

Cumin takes an approach similar to Core Foundation and Cocoa by having memory management rules that apply to the whole framework. These are more similar to Cocoa's than Core Foundation's (see [THE (original) RULES](http://developer.apple.com/mac/library/documentation/Cocoa/Conceptual/MemoryMgmt/Articles/mmRules.html) for more information).

Cumin's RULES are as follows:

* Objects returned by CuAlloc() and CuRetain() MUST be balanced by a CuRelease() or CuReleaseLater().

* Objects returned by ANY OTHER FUNCTION must NOT be released, and are only valid until this function returns (and can be returned), or until a release pool is popped via CuReleasePoolPop(). To keep such an object around past these boundaries, you must retain it with a CuRetain() call.

Please note that unlike Core Foundation, 'Create' and 'Copy' do not have a particular meaning. Additionally, unlike Objective-C, 'new' has no particular meaning. If a function with that word in its name returns an object, it must be retained to be kept past this function.

Finally: all Cumin functions **require** a release pool (Cumin's version of Cocoa's autorelease pools) in place before calling. All callbacks coming from Cumin code can expect that there will be one alraedy in place; however, all functions called from other sources **must** push a release pool on the stack and pop it when finished as follows:

	void MyFunctionCalledFromElsewhere() {
		CuReleasePoolPush();
		/* do absurdly fun stuff here */
		CuReleasePoolPop();
	}

If you're using GCC, you can automatically push a pool and pop it at end of the current scope (`{ ... }`) by placing `CuReleasePoolScope()` at the point where you would use `…Push()`:

	void MyFunctionCalledFromElsewhere() {
		CuReleasePoolScope();
		/* do absurdly fun stuff here */
		/* no need to pop */
	}

## Threading

Cumin is thread-unsafe, main-thread-only at the moment.
