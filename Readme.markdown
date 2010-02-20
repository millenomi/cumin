# Cumin

Cumin is a small library providing base services often used in apps. The goal is:

* Take the best parts of Apple's Core Foundation and Objective-C. Object-orientation, but lightweight.

* Pure C.

* As portable as possible. Portable means that it works and it makes little or no assumptions on what it has to work with! Ideally, the whole thing would require just some half-decent libc subset and maybe pthreads.

* Able to integrate smoothly into whatever run loop or event delivery structure it finds itself in.

* Be buildable with:
	
		gcc -shared -o libCumin.dylib *.c
		
	and nothing else. In fact, be buildable with the least amount of customization needed on the build process ever, and a small and well-known list of dependencies that do not require building or require only minimal effort.
	