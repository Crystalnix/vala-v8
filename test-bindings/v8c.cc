#define BUILDING_V8C
#include <v8.h>

#include "v8c.h"
#include "v8c-private.h"

template<typename T>
static V8Handle* handle_new (v8::Handle<T> handle, V8HandleType type) {
  V8Handle* self = (V8Handle*)malloc(sizeof(V8Handle));
  self.handle = new V8HandleWrap (handle);
  self.type = type;
  return self;
}

extern "C" {

  /* Handle */
  void* v8_handle_data(V8Handle* self) {
    return self->handle->data();
  }

  void v8_handle_free(V8Handle* self) {
    delete self.handle;
    free(self);
  }

  bool v8_handle_is_empty(V8Handle* self) {
    return self->handle->handle()->IsEmpty();
  }

  void v8_persistent_dispose(V8Persistent* self) {
    self->handle->handle()->Dispose();
  }

  V8CHandleScope* v8_handle_scope_new() {
    return new V8CHandleScope();
  }

  void v8_handle_scope_free(V8CHandleScope* hs) {
    delete hs;
  }

  V8Local* v8_script_compile(V8Handle* code) {
    return handle_new(v8::Script::Compile(code->handle->handle()),
		      V8HT_SCRIPT);
  }

  V8Local* v8_script_run(V8Script* self) {
    return handle_new(reinterpret_cast<v8::Script*>(self)->Run(),
		      V8HT_VALUE);
  }

  V8Handle* v8_string_new_utf8(const char* data, int length) {
    return handle_new(v8::String::New(data, length), V8HT_STRING);
  }

  V8StringUtf8Value* v8_string_utf8_value_new(V8Handle* handle) {
    return new v8::String::Utf8Value(handle->handle->handle());
  }

  int v8_string_utf8_value_length(V8StringUtf8Value* utf8) {
    return utf8->length();
  }

  char* v8_string_utf8_value_chars(V8StringUtf8Value* utf8) {
    return **utf8;
  }

  void v8_string_utf8_value_free(V8StringUtf8Value* utf8) {
    delete utf8;
  }

  V8Persistent* v8_context_new() {
    return handle_new(v8::Context::New(), V8HT_CONTEXT);
  }

  void v8_context_enter(V8Context* self) {
    reinterpret_cast<v8::Context*>(self)->Enter();
  }

  void v8_context_exit(V8Context* self) {
    reinterpret_cast<v8::Context*>(self)->Exit();
  }

}  // extern "C"
