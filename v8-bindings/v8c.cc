#define BUILDING_V8C
#include <v8.h>

#include "v8c.h"
#include "v8c-private.h"

template<typename T>
static V8Handle unwrap_handle(v8::Handle<T> handle) {
  return *handle;
}

template<typename T>
static v8::Handle<T> wrap_handle(V8Handle handle) {
  return v8::Handle<T>(reinterpret_cast<T*>(handle));
}

template<typename T>
static v8::Persistent<T> wrap_persistent_handle(V8Handle handle) {
  return v8::Persistent<T>(reinterpret_cast<T*>(handle));
}

extern "C" {

bool v8_handle_is_empty(V8Handle handle) {
  return wrap_handle<void>(handle).IsEmpty();
}

V8CHandleScope* v8_handle_scope_new() {
  return new V8CHandleScope();
}

void v8_handle_scope_free(V8CHandleScope* hs) {
  delete hs;
}

V8Handle v8_script_compile(V8Handle code) {
  return unwrap_handle(v8::Script::Compile(wrap_handle<v8::String>(code)));
}

V8Handle v8_script_run(V8Handle script) {
  return unwrap_handle(wrap_handle<v8::Script>(script)->Run());
}

V8Handle v8_string_new_utf8(const char* data, int length) {
  return unwrap_handle(v8::String::New(data, length));
}

int v8_string_length(V8Handle h) {
  return wrap_handle<v8::String>(h)->Length();
}

V8StringUtf8Value* v8_string_utf8_value_new(V8Handle handle) {
  return new v8::String::Utf8Value(wrap_handle<v8::Value>(handle));
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

void v8_template_set(V8Handle tmpl, V8Handle name, V8Handle value) {
  wrap_handle<v8::Template>(tmpl)->Set(wrap_handle<v8::String>(name),
                                       wrap_handle<v8::Data>(value));
}

int v8_arguments_length(const V8Arguments* args) {
  return args->Length();
}

V8Handle v8_arguments_get(const V8Arguments* args, int i) {
  return unwrap_handle((*args)[i]);
}

static v8::Handle<v8::Value> v8_invocation_callback_no_data(const v8::Arguments& args) {
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(args.Data());
  V8InvocationCallback callback =
      reinterpret_cast<V8InvocationCallback>(data->Value());
  return wrap_handle<v8::Value>(callback(&args));
}

static v8::Handle<v8::Value> v8_invocation_callback_with_data(const v8::Arguments& args) {
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(args.Data());
  V8InvocationCallbackData* callback_data =
      static_cast<V8InvocationCallbackData*>(data->Value());
  return wrap_handle<v8::Value>(callback_data->callback(&args, callback_data->data));
}

V8Handle v8_function_template_new(V8InvocationCallback callback) {
  return unwrap_handle(
      v8::FunctionTemplate::New(v8_invocation_callback_no_data,
				v8::External::New((void*)callback)));
}

V8Handle v8_function_template_new_with_data(V8InvocationCallbackData *callback_data) {
  return unwrap_handle(
      v8::FunctionTemplate::New(v8_invocation_callback_with_data,
				v8::External::New(callback_data)));
}

V8Handle v8_function_template_get_function(V8Handle self)
{
  return unwrap_handle(wrap_handle<v8::FunctionTemplate>(self)->GetFunction());
}

void v8_function_template_set_call_handler(V8Handle self, V8InvocationCallback callback)
{
  wrap_handle<v8::FunctionTemplate>(self)->SetCallHandler(
    v8_invocation_callback_no_data,
    v8::External::New((void*)callback)
  );
}

V8Handle v8_function_template_instance_template(V8Handle self)
{
  return unwrap_handle(wrap_handle<v8::FunctionTemplate>(self)->InstanceTemplate());
}

void v8_function_template_inherit(V8Handle self, V8Handle parent)
{
  wrap_handle<v8::FunctionTemplate>(self)->Inherit(wrap_handle<v8::FunctionTemplate>(parent));
}

V8Handle v8_function_template_prototype_template(V8Handle self)
{
  return unwrap_handle(wrap_handle<v8::FunctionTemplate>(self)->PrototypeTemplate());
}

void v8_function_template_set_class_name(V8Handle self, V8Handle name)
{
  wrap_handle<v8::FunctionTemplate>(self)->SetClassName(wrap_handle<v8::String>(name));
}

void v8_function_template_set_hidden_prototype(bool value)
{
  wrap_handle<v8::FunctionTemplate>(self)->SetHiddenPrototype(value);
}

bool v8_function_template_has_instance(V8Handle self, V8Handle object)
{
  return wrap_handle<v8::FunctionTemplate>(self)->HasInstance(wrap_handle<v8::Value>(object));
}

V8Handle v8_object_template_new() {
  return unwrap_handle(v8::ObjectTemplate::New());
}

V8Handle v8_undefined() {
  return unwrap_handle(v8::Undefined());
}

V8Handle v8_null() {
  return unwrap_handle(v8::Null());
}

V8Handle v8_true() {
  return unwrap_handle(v8::True());
}

V8Handle v8_false() {
  return unwrap_handle(v8::False());
}

void v8_set_flags_from_command_line(int* argc, char** argv,
                                    bool remove_flags) {
  v8::V8::SetFlagsFromCommandLine(argc, argv, remove_flags);
}

V8TryCatch* v8_try_catch_new() {
  return new V8TryCatch;
}

void v8_try_catch_free(V8TryCatch* try_catch) {
  delete try_catch;
}

bool v8_try_catch_has_caught(V8TryCatch* try_catch) {
  return try_catch->HasCaught();
}

V8Handle v8_try_catch_exception(V8TryCatch* try_catch) {
  return unwrap_handle(try_catch->Exception());
}

V8Handle v8_try_catch_get_message(V8TryCatch* try_catch) {
  return unwrap_handle(try_catch->Message());
}

void v8_try_catch_reset(V8TryCatch* try_catch) {
  try_catch->Reset();
}

void v8_try_catch_set_verbose(V8TryCatch* try_catch, bool value) {
  try_catch->SetVerbose(value);
}

V8Handle v8_context_new(V8ExtensionConfiguration extensions,
                        V8Handle global_template) {
      
  return unwrap_handle(
      v8::Context::New(extensions,
                       wrap_handle<v8::ObjectTemplate>(global_template)));
}

void v8_context_free(V8Handle context) {
    return wrap_persistent_handle<v8::Context>(context).Dispose();
}

void v8_context_enter(V8Handle context) {
  wrap_handle<v8::Context>(context)->Enter();
}

void v8_context_exit(V8Handle context) {
  wrap_handle<v8::Context>(context)->Exit();
}

}  // extern "C"