# Cumin

Cumin is a small library providing base services often used in apps. The goal is:

* Take the best parts of Apple's Core Foundation and Objective-C. Object-orientation, but lightweight.

* Pure C.

* As portable as possible. Portable means that it works and it makes little or no assumptions on what it has to work with! Ideally, the whole thing would require just some half-decent libc subset and maybe pthreads.

* Be buildable with:
	
		gcc -shared -o libCumin.dylib *.c
		
	and nothing else.
	