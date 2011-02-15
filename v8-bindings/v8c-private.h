#ifndef __V8C_PRIVATE_H__
#define __V8C_PRIVATE_H__

#include <stdlib.h>

typedef struct _V8InvocationCallbackData V8InvocationCallbackData;

class V8CHandleScope : public v8::HandleScope
{
public:
	V8CHandleScope() : v8::HandleScope() {}
		
	void* operator new(size_t size) { return malloc(size); }
	void operator delete(void* p, size_t size) { free(p); }
};

/*
class V8CFunctionTemplate : public v8::FunctionTemplate
{
public:
	static v8::Local<FunctionTemplate> NewWithOptions(
	    v8::InvocationCallback callback = 0,
	    v8::Handle<v8::Value> data = v8::Handle<v8::Value>(),
	    v8::Handle<v8::Signature> signature = v8::Handle<v8::Signature>(),
	    V8InvocationCallbackData *deleteAfterUsing);
	~V8CFunctionTemplate()
	void SetCallHandler(v8::InvocationCallback callback,
                        v8::Handle<v8::Value> data = v8::Handle<v8::Value>());
    void Set
private:
	V8CFunctionTemplate() : v8::FunctionTemplate() {}
};
*/
#endif  // #ifndef __V8C_PRIVATE_H__