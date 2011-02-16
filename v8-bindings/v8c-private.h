#ifndef __V8C_PRIVATE_H__
#define __V8C_PRIVATE_H__

#include <stdlib.h>

class V8CHandleScope : public v8::HandleScope
{
public:
	V8CHandleScope() : v8::HandleScope() {}
		
	void* operator new(size_t size) { return malloc(size); }
	void operator delete(void* p, size_t size) { free(p); }
};

#endif  // #ifndef __V8C_PRIVATE_H__