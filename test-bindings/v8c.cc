#define BUILDING_V8C
#include <v8.h>

#include "v8c.h"
#include "v8c-private.h"

#define V8HANDLE_CASE(type,templ,fun,res) case type: res = reinterpret_cast<V8CHandleWrap<templ>*>(self->handle)->fun; break;

#define V8HANDLE_CALL(self,fun,res) do {				\
    switch (self->type) {						\
      V8HANDLE_CASE(V8HT_DATA,v8::Data,fun,res);			\
      V8HANDLE_CASE(V8HT_SCRIPT,v8::Script,fun,res);			\
      V8HANDLE_CASE(V8HT_MESSAGE,v8::Message,fun,res);			\
      V8HANDLE_CASE(V8HT_STACK_TRACE,v8::StackTrace,fun,res);		\
      V8HANDLE_CASE(V8HT_STACK_FRAME,v8::StackFrame,fun,res);		\
      V8HANDLE_CASE(V8HT_VALUE,v8::Value,fun,res);			\
      V8HANDLE_CASE(V8HT_PRIMITIVE,v8::Primitive,fun,res);		\
      V8HANDLE_CASE(V8HT_BOOLEAN,v8::Boolean,fun,res);			\
      V8HANDLE_CASE(V8HT_STRING,v8::String,fun,res);			\
      V8HANDLE_CASE(V8HT_NUMBER,v8::Number,fun,res);			\
      V8HANDLE_CASE(V8HT_INTEGER,v8::Integer,fun,res);			\
      V8HANDLE_CASE(V8HT_INT32,v8::Int32,fun,res);			\
      V8HANDLE_CASE(V8HT_UINT32,v8::Uint32,fun,res);			\
      V8HANDLE_CASE(V8HT_DATE,v8::Date,fun,res);			\
      V8HANDLE_CASE(V8HT_REGEXP,v8::RegExp,fun,res);			\
      V8HANDLE_CASE(V8HT_OBJECT,v8::Object,fun,res);			\
      V8HANDLE_CASE(V8HT_ARRAY,v8::Array,fun,res);			\
      V8HANDLE_CASE(V8HT_FUNCTION,v8::Function,fun,res);		\
      V8HANDLE_CASE(V8HT_EXTERNAL,v8::External,fun,res);		\
      V8HANDLE_CASE(V8HT_TEMPLATE,v8::Template,fun,res);		\
      V8HANDLE_CASE(V8HT_FUNCTION_TEMPLATE,v8::FunctionTemplate,fun,res); \
      V8HANDLE_CASE(V8HT_OBJECT_TEMPLATE,v8::ObjectTemplate,fun,res);	\
      V8HANDLE_CASE(V8HT_SIGNATURE,v8::Signature,fun,res);		\
      V8HANDLE_CASE(V8HT_TYPE_SWITCH,v8::TypeSwitch,fun,res);		\
      V8HANDLE_CASE(V8HT_CONTEXT,v8::Context,fun,res);			\
    }} while (false);

#define V8HANDLE_VCASE(type,templ,fun) case type: reinterpret_cast<V8CHandleWrap<templ>*>(self->handle)->fun; break;

#define V8HANDLE_VCALL(self,fun) do {				\
    switch (self->type) {						\
      V8HANDLE_VCASE(V8HT_DATA,v8::Data,fun);			\
      V8HANDLE_VCASE(V8HT_SCRIPT,v8::Script,fun);			\
      V8HANDLE_VCASE(V8HT_MESSAGE,v8::Message,fun);			\
      V8HANDLE_VCASE(V8HT_STACK_TRACE,v8::StackTrace,fun);		\
      V8HANDLE_VCASE(V8HT_STACK_FRAME,v8::StackFrame,fun);		\
      V8HANDLE_VCASE(V8HT_VALUE,v8::Value,fun);			\
      V8HANDLE_VCASE(V8HT_PRIMITIVE,v8::Primitive,fun);		\
      V8HANDLE_VCASE(V8HT_BOOLEAN,v8::Boolean,fun);			\
      V8HANDLE_VCASE(V8HT_STRING,v8::String,fun);			\
      V8HANDLE_VCASE(V8HT_NUMBER,v8::Number,fun);			\
      V8HANDLE_VCASE(V8HT_INTEGER,v8::Integer,fun);			\
      V8HANDLE_VCASE(V8HT_INT32,v8::Int32,fun);			\
      V8HANDLE_VCASE(V8HT_UINT32,v8::Uint32,fun);			\
      V8HANDLE_VCASE(V8HT_DATE,v8::Date,fun);			\
      V8HANDLE_VCASE(V8HT_REGEXP,v8::RegExp,fun);			\
      V8HANDLE_VCASE(V8HT_OBJECT,v8::Object,fun);			\
      V8HANDLE_VCASE(V8HT_ARRAY,v8::Array,fun);			\
      V8HANDLE_VCASE(V8HT_FUNCTION,v8::Function,fun);		\
      V8HANDLE_VCASE(V8HT_EXTERNAL,v8::External,fun);		\
      V8HANDLE_VCASE(V8HT_TEMPLATE,v8::Template,fun);		\
      V8HANDLE_VCASE(V8HT_FUNCTION_TEMPLATE,v8::FunctionTemplate,fun); \
      V8HANDLE_VCASE(V8HT_OBJECT_TEMPLATE,v8::ObjectTemplate,fun);	\
      V8HANDLE_VCASE(V8HT_SIGNATURE,v8::Signature,fun);		\
      V8HANDLE_VCASE(V8HT_TYPE_SWITCH,v8::TypeSwitch,fun);		\
      V8HANDLE_VCASE(V8HT_CONTEXT,v8::Context,fun);			\
    }} while (false);

#define V8HANDLE_DCASE(type,templ) case type: delete reinterpret_cast<V8CHandleWrap<templ>*>(self->handle); break;

#define V8HANDLE_DCALL(self) do {				\
    switch (self->type) {						\
      V8HANDLE_DCASE(V8HT_DATA,v8::Data);			\
      V8HANDLE_DCASE(V8HT_SCRIPT,v8::Script);			\
      V8HANDLE_DCASE(V8HT_MESSAGE,v8::Message);			\
      V8HANDLE_DCASE(V8HT_STACK_TRACE,v8::StackTrace);		\
      V8HANDLE_DCASE(V8HT_STACK_FRAME,v8::StackFrame);		\
      V8HANDLE_DCASE(V8HT_VALUE,v8::Value);			\
      V8HANDLE_DCASE(V8HT_PRIMITIVE,v8::Primitive);		\
      V8HANDLE_DCASE(V8HT_BOOLEAN,v8::Boolean);			\
      V8HANDLE_DCASE(V8HT_STRING,v8::String);			\
      V8HANDLE_DCASE(V8HT_NUMBER,v8::Number);			\
      V8HANDLE_DCASE(V8HT_INTEGER,v8::Integer);			\
      V8HANDLE_DCASE(V8HT_INT32,v8::Int32);			\
      V8HANDLE_DCASE(V8HT_UINT32,v8::Uint32);			\
      V8HANDLE_DCASE(V8HT_DATE,v8::Date);			\
      V8HANDLE_DCASE(V8HT_REGEXP,v8::RegExp);			\
      V8HANDLE_DCASE(V8HT_OBJECT,v8::Object);			\
      V8HANDLE_DCASE(V8HT_ARRAY,v8::Array);			\
      V8HANDLE_DCASE(V8HT_FUNCTION,v8::Function);		\
      V8HANDLE_DCASE(V8HT_EXTERNAL,v8::External);		\
      V8HANDLE_DCASE(V8HT_TEMPLATE,v8::Template);		\
      V8HANDLE_DCASE(V8HT_FUNCTION_TEMPLATE,v8::FunctionTemplate); \
      V8HANDLE_DCASE(V8HT_OBJECT_TEMPLATE,v8::ObjectTemplate);	\
      V8HANDLE_DCASE(V8HT_SIGNATURE,v8::Signature);		\
      V8HANDLE_DCASE(V8HT_TYPE_SWITCH,v8::TypeSwitch);		\
      V8HANDLE_DCASE(V8HT_CONTEXT,v8::Context);			\
    }} while (false);

template<typename T>
static V8Handle* handle_new (v8::Handle<T> handle, V8HandleType type) {
  V8Handle* self = (V8Handle*)malloc(sizeof(V8Handle));
  self->handle = reinterpret_cast<void*>(new V8CHandleWrap<T> (handle));
  self->type = type;
  return self;
}

extern "C" {

  /* Handle */
  void* v8_handle_data(V8Handle* self) {
    void * res = NULL;
    V8HANDLE_CALL (self, data(), res);
    return res;
  }

  void v8_handle_free(V8Handle* self) {
    V8HANDLE_DCALL (self);
    free(self);
  }

  bool v8_handle_is_empty(V8Handle* self) {
    bool res;
    V8HANDLE_CALL(self, handle()->IsEmpty(), res);
    return res;
  }

  void v8_persistent_dispose(V8Persistent* self) {
    V8HANDLE_VCALL (self, persistent()->Dispose());
  }

  V8CHandleScope* v8_handle_scope_new() {
    return new V8CHandleScope();
  }

  void v8_handle_scope_free(V8CHandleScope* hs) {
    delete hs;
  }

  V8Local* v8_script_compile(V8Handle* code) {
    return handle_new<v8::Script>(v8::Script::Compile(*reinterpret_cast<V8CHandleWrap<v8::String>*>(code->handle)->handle()), V8HT_SCRIPT);
  }

  V8Local* v8_script_run(V8Script* self) {
    return handle_new<v8::Value>(reinterpret_cast<v8::Script*>(self)->Run(),
		      V8HT_VALUE);
  }

  V8Handle* v8_string_new_utf8(const char* data, int length) {
    return handle_new<v8::String>(v8::String::New(data, length), V8HT_STRING);
  }

  V8StringUtf8Value* v8_string_utf8_value_new(V8Handle* handle) {
    return new v8::String::Utf8Value(*reinterpret_cast<V8CHandleWrap<v8::Value>*>(handle->handle)->handle());
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
    return handle_new<v8::Context>(v8::Context::New(), V8HT_CONTEXT);
  }

  void v8_context_enter(V8Context* self) {
    reinterpret_cast<v8::Context*>(self)->Enter();
  }

  void v8_context_exit(V8Context* self) {
    reinterpret_cast<v8::Context*>(self)->Exit();
  }

}  // extern "C"
