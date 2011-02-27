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

template <class T> class V8CHandleWrap
{
 public:
  inline V8CHandleWrap (const v8::Handle<T>& h) : handle_(h) {}

  inline v8::Handle<T>* handle () { return &handle_; }
  inline v8::Local<T>* local () { return reinterpret_cast<v8::Local<T>*>(&handle_); }
  inline v8::Persistent<T>* persistent () { return reinterpret_cast<v8::Persistent<T>*>(&handle_); }

  inline void* data () { return reinterpret_cast<void*>(*handle_); }

 private:
  v8::Handle<T> handle_;

  V8CHandleWrap ();
};

#endif  // #ifndef __V8C_PRIVATE_H__
