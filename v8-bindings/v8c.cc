#define BUILDING_V8C
#include <v8.h>

#include "v8c.h"
#include "v8c-private.h"

template<typename T>
static V8Handle* unwrap_handle(v8::Handle<T> handle) {
  return *handle;
}

template<typename T>
static v8::Handle<T> wrap_handle(V8Handle* handle) {
  return v8::Handle<T>(reinterpret_cast<T*>(handle));
}

template<typename T>
static v8::Persistent<T> wrap_persistent_handle(V8Handle* handle) {
  return v8::Persistent<T>(reinterpret_cast<T*>(handle));
}

extern "C" {

bool v8_handle_is_empty(V8Handle* handle) {
  return wrap_handle<void>(handle).IsEmpty();
}

/* Persistent */
V8Handle*   v8_persistent_new(V8Handle* handle, V8HandleType handle_type) {
  V8Handle* res = NULL;
  switch (handle_type) {
  case V8HT_DATA:
    res = unwrap_handle(v8::Persistent<v8::Data>::New(wrap_handle<v8::Data>(handle)));
    break;
  case V8HT_SCRIPT:
    res = unwrap_handle(v8::Persistent<v8::Script>::New(wrap_handle<v8::Script>(handle)));
    break;
  case V8HT_MESSAGE:
    res = unwrap_handle(v8::Persistent<v8::Message>::New(wrap_handle<v8::Message>(handle)));
    break;
  case V8HT_STACK_TRACE:
    res = unwrap_handle(v8::Persistent<v8::StackTrace>::New(wrap_handle<v8::StackTrace>(handle)));
    break;
  case V8HT_STACK_FRAME:
    res = unwrap_handle(v8::Persistent<v8::StackFrame>::New(wrap_handle<v8::StackFrame>(handle)));
    break;
  case V8HT_VALUE:
    res = unwrap_handle(v8::Persistent<v8::Value>::New(wrap_handle<v8::Value>(handle)));
    break;
  case V8HT_PRIMITIVE:
    res = unwrap_handle(v8::Persistent<v8::Primitive>::New(wrap_handle<v8::Primitive>(handle)));
    break;
  case V8HT_BOOLEAN:
    res = unwrap_handle(v8::Persistent<v8::Boolean>::New(wrap_handle<v8::Boolean>(handle)));
    break;
  case V8HT_STRING:
    res = unwrap_handle(v8::Persistent<v8::String>::New(wrap_handle<v8::String>(handle)));
    break;
  case V8HT_NUMBER:
    res = unwrap_handle(v8::Persistent<v8::Number>::New(wrap_handle<v8::Number>(handle)));
    break;
  case V8HT_INTEGER:
    res = unwrap_handle(v8::Persistent<v8::Integer>::New(wrap_handle<v8::Integer>(handle)));
    break;
  case V8HT_INT32:
    res = unwrap_handle(v8::Persistent<v8::Int32>::New(wrap_handle<v8::Int32>(handle)));
    break;
  case V8HT_UINT32:
    res = unwrap_handle(v8::Persistent<v8::Uint32>::New(wrap_handle<v8::Uint32>(handle)));
    break;
  case V8HT_DATE:
    res = unwrap_handle(v8::Persistent<v8::Date>::New(wrap_handle<v8::Date>(handle)));
    break;
  case V8HT_REGEXP:
    res = unwrap_handle(v8::Persistent<v8::RegExp>::New(wrap_handle<v8::RegExp>(handle)));
    break;
  case V8HT_OBJECT:
    res = unwrap_handle(v8::Persistent<v8::Object>::New(wrap_handle<v8::Object>(handle)));
    break;
  case V8HT_ARRAY:
    res = unwrap_handle(v8::Persistent<v8::Array>::New(wrap_handle<v8::Array>(handle)));
    break;
  case V8HT_FUNCTION:
    res = unwrap_handle(v8::Persistent<v8::Function>::New(wrap_handle<v8::Function>(handle)));
    break;
  case V8HT_EXTERNAL:
    res = unwrap_handle(v8::Persistent<v8::External>::New(wrap_handle<v8::External>(handle)));
    break;
  case V8HT_TEMPLATE:
    res = unwrap_handle(v8::Persistent<v8::Template>::New(wrap_handle<v8::Template>(handle)));
    break;
  case V8HT_FUNCTION_TEMPLATE:
    res = unwrap_handle(v8::Persistent<v8::FunctionTemplate>::New(wrap_handle<v8::FunctionTemplate>(handle)));
    break;
  case V8HT_OBJECT_TEMPLATE:
    res = unwrap_handle(v8::Persistent<v8::ObjectTemplate>::New(wrap_handle<v8::ObjectTemplate>(handle)));
    break;
  case V8HT_SIGNATURE:
    res = unwrap_handle(v8::Persistent<v8::Signature>::New(wrap_handle<v8::Signature>(handle)));
    break;
  case V8HT_TYPE_SWITCH:
    res = unwrap_handle(v8::Persistent<v8::TypeSwitch>::New(wrap_handle<v8::TypeSwitch>(handle)));
    break;
  case V8HT_CONTEXT:
    res = unwrap_handle(v8::Persistent<v8::Context>::New(wrap_handle<v8::Context>(handle)));
    break;
  default:
    res = NULL;
    break;
  }
  
  return res;
}

void        v8_persistent_dispose(V8Handle* handle, V8HandleType handle_type) {
  switch (handle_type) {
  case V8HT_DATA:
    wrap_persistent_handle<v8::Data>(handle).Dispose();
    break;
  case V8HT_SCRIPT:
    wrap_persistent_handle<v8::Script>(handle).Dispose();
    break;
  case V8HT_MESSAGE:
    wrap_persistent_handle<v8::Message>(handle).Dispose();
    break;
  case V8HT_STACK_TRACE:
    wrap_persistent_handle<v8::StackTrace>(handle).Dispose();
    break;
  case V8HT_STACK_FRAME:
    wrap_persistent_handle<v8::StackFrame>(handle).Dispose();
    break;
  case V8HT_VALUE:
    wrap_persistent_handle<v8::Value>(handle).Dispose();
    break;
  case V8HT_PRIMITIVE:
    wrap_persistent_handle<v8::Primitive>(handle).Dispose();
    break;
  case V8HT_BOOLEAN:
    wrap_persistent_handle<v8::Boolean>(handle).Dispose();
    break;
  case V8HT_STRING:
    wrap_persistent_handle<v8::String>(handle).Dispose();
    break;
  case V8HT_NUMBER:
    wrap_persistent_handle<v8::Number>(handle).Dispose();
    break;
  case V8HT_INTEGER:
    wrap_persistent_handle<v8::Integer>(handle).Dispose();
    break;
  case V8HT_INT32:
    wrap_persistent_handle<v8::Int32>(handle).Dispose();
    break;
  case V8HT_UINT32:
    wrap_persistent_handle<v8::Uint32>(handle).Dispose();
    break;
  case V8HT_DATE:
    wrap_persistent_handle<v8::Date>(handle).Dispose();
    break;
  case V8HT_REGEXP:
    wrap_persistent_handle<v8::RegExp>(handle).Dispose();
    break;
  case V8HT_OBJECT:
    wrap_persistent_handle<v8::Object>(handle).Dispose();
    break;
  case V8HT_ARRAY:
    wrap_persistent_handle<v8::Array>(handle).Dispose();
    break;
  case V8HT_FUNCTION:
    wrap_persistent_handle<v8::Function>(handle).Dispose();
    break;
  case V8HT_EXTERNAL:
    wrap_persistent_handle<v8::External>(handle).Dispose();
    break;
  case V8HT_TEMPLATE:
    wrap_persistent_handle<v8::Template>(handle).Dispose();
    break;
  case V8HT_FUNCTION_TEMPLATE:
    wrap_persistent_handle<v8::FunctionTemplate>(handle).Dispose();
    break;
  case V8HT_OBJECT_TEMPLATE:
    wrap_persistent_handle<v8::ObjectTemplate>(handle).Dispose();
    break;
  case V8HT_SIGNATURE:
    wrap_persistent_handle<v8::Signature>(handle).Dispose();
    break;
  case V8HT_TYPE_SWITCH:
    wrap_persistent_handle<v8::TypeSwitch>(handle).Dispose();
    break;
  case V8HT_CONTEXT:
    wrap_persistent_handle<v8::Context>(handle).Dispose();
    break;
  default:
    break;
  }
}

V8CHandleScope* v8_handle_scope_new() {
  return new V8CHandleScope();
}

void v8_handle_scope_free(V8CHandleScope* hs) {
  delete hs;
}

V8Handle* v8_handle_scope_close(V8CHandleScope *self, V8Handle* value, V8HandleType handle_type) {
  V8Handle* res = (V8Handle*)0;
  
  switch (handle_type) {
  case V8HT_VALUE:
  default:
    res = unwrap_handle(self->Close(wrap_handle<v8::Value>(value)));
  }
  
  return res;
}

int v8_handle_scope_number_of_handles() {
  return v8::HandleScope::NumberOfHandles();
}

V8Handle* v8_script_compile(V8Handle* code) {
  return unwrap_handle(v8::Script::Compile(wrap_handle<v8::String>(code)));
}

V8Handle* v8_script_run(V8Handle* script) {
  return unwrap_handle(wrap_handle<v8::Script>(script)->Run());
}

/* Message */
V8Handle* v8_message_get(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Message>(self)->Get());
}

V8Handle* v8_message_get_source_line(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Message>(self)->GetSourceLine());  
}

V8Handle* v8_message_get_script_resource_name(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Message>(self)->GetScriptResourceName());  
}

V8Handle* v8_message_get_stack_trace(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Message>(self)->GetStackTrace());  
}

int      v8_message_get_line_number(V8Handle* self) {
  return wrap_handle<v8::Message>(self)->GetLineNumber();
}

int      v8_message_get_start_position(V8Handle* self) {
  return wrap_handle<v8::Message>(self)->GetStartPosition();
}

int      v8_message_get_end_position(V8Handle* self) {
  return wrap_handle<v8::Message>(self)->GetEndPosition();
}

int      v8_message_get_start_column(V8Handle* self) {
  return wrap_handle<v8::Message>(self)->GetStartColumn();
}

int      v8_message_get_end_column(V8Handle* self) {
  return wrap_handle<v8::Message>(self)->GetEndColumn();
}

/* StackTrace */
V8Handle* v8_stack_trace_get_frame(V8Handle* self, uint32_t index) {
    return unwrap_handle(wrap_handle<v8::StackTrace>(self)->GetFrame(index));
}

int      v8_stack_trace_get_frame_count(V8Handle* self) {
  return wrap_handle<v8::StackTrace>(self)->GetFrameCount();
}

/* StackFrame */
int      v8_stack_frame_get_line_number(V8Handle* self) {
  return wrap_handle<v8::StackFrame>(self)->GetLineNumber();
}

int      v8_stack_frame_get_column(V8Handle* self) {
  return wrap_handle<v8::StackFrame>(self)->GetColumn();
}

V8Handle* v8_stack_frame_get_script_name(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::StackFrame>(self)->GetScriptName());
}

V8Handle* v8_stack_frame_get_script_name_or_source_url(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::StackFrame>(self)->GetScriptNameOrSourceURL());
}

V8Handle* v8_stack_frame_get_function_name(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::StackFrame>(self)->GetFunctionName());
}

bool     v8_stack_frame_is_eval(V8Handle* self) {
  return wrap_handle<v8::StackFrame>(self)->IsEval();
}

bool     v8_stack_frame_is_constructor(V8Handle* self) {
  return wrap_handle<v8::StackFrame>(self)->IsConstructor();
}


/* Value */
bool v8_value_is_undefined  (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsUndefined();
}

bool v8_value_is_null       (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsNull();
}

bool v8_value_is_true       (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsTrue();
}

bool v8_value_is_false      (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsFalse();
}

bool v8_value_is_string     (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsString();
}

bool v8_value_is_function   (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsFunction();
}

bool v8_value_is_array      (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsArray();
}

bool v8_value_is_object     (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsObject();
}

bool v8_value_is_boolean    (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsBoolean();
}

bool v8_value_is_number     (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsNumber();  
}

bool v8_value_is_external   (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsExternal();
}

bool v8_value_is_int32      (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsInt32();
}

bool v8_value_is_uint32     (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsUint32();
}

bool v8_value_is_date       (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsDate();
}

bool v8_value_is_regexp     (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IsRegExp();
}

V8Handle* v8_value_to_boolean    (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToBoolean());
}

V8Handle* v8_value_to_number     (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToNumber());
}

V8Handle* v8_value_to_string     (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToString());
}

V8Handle* v8_value_to_detail_string (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToDetailString());
}

V8Handle* v8_value_to_object     (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToObject());
}

V8Handle* v8_value_to_integer    (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToInteger());
}

V8Handle* v8_value_to_uint32     (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToUint32());
}

V8Handle* v8_value_to_int32      (V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToInt32());
}

V8Handle* v8_value_to_external   (V8Handle* self) {
  return unwrap_handle(v8::Handle<v8::External>::Cast(wrap_handle<v8::Value>(self)));
}

V8Handle* v8_value_to_array_index(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Value>(self)->ToArrayIndex());
}

bool     v8_value_boolean_value (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->BooleanValue();
}

double   v8_value_number_value  (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->NumberValue();
}

int64_t  v8_value_integer_value (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->IntegerValue();
}

uint32_t v8_value_uint32_value  (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->Uint32Value();
}

int32_t  v8_value_int32_value   (V8Handle* self) {
  return wrap_handle<v8::Value>(self)->Int32Value();
}

void*    v8_value_voidp_value   (V8Handle* self) {
  return v8::Handle<v8::External>::Cast(wrap_handle<v8::Value>(self))->Value();
}

bool v8_value_equals(V8Handle* self, V8Handle* that) {
  return wrap_handle<v8::Value>(self)->Equals(wrap_handle<v8::Value>(that));
}

bool v8_value_strict_equals(V8Handle* self, V8Handle* that) {
  return wrap_handle<v8::Value>(self)->StrictEquals(wrap_handle<v8::Value>(that));
}

/* Boolean */
bool v8_boolean_value(V8Handle* self) {
  return wrap_handle<v8::Boolean>(self)->Value();
}

V8Handle* v8_boolean_new(bool value) {
  return unwrap_handle(v8::Boolean::New(value));
}

V8Handle* v8_string_new_utf8(const char* data, int length) {
  return unwrap_handle(v8::String::New(data, length));
}

int v8_string_length(V8Handle* h) {
  return wrap_handle<v8::String>(h)->Length();
}

int         v8_string_utf8_length   (V8Handle* self) {
  return wrap_handle<v8::String>(self)->Utf8Length();
}

V8Handle*    v8_string_empty         (void) {
  return unwrap_handle(v8::String::Empty());
}

bool        v8_string_is_external   (V8Handle* self) {
  return wrap_handle<v8::String>(self)->IsExternal();
}

bool        v8_string_is_external_ascii   (V8Handle* self) {
  return wrap_handle<v8::String>(self)->IsExternalAscii();
}

V8StringUtf8Value* v8_string_utf8_value_new(V8Handle* handle) {
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

/* String::AsciiValue */
V8StringAsciiValue*     v8_string_ascii_value_new(V8Handle* handle) {
  return new v8::String::AsciiValue(wrap_handle<v8::Value>(handle));
}

int     v8_string_ascii_value_length (V8StringAsciiValue* self) {
  return self->length();
}

char*   v8_string_ascii_value_chars  (V8StringAsciiValue* self) {
  return **self;
}

void    v8_string_ascii_value_free   (V8StringAsciiValue* self) {
  delete self;
}

/* String::Value (2-byte string) */
V8StringValue*     v8_string_value_new(V8Handle* handle) {
  return new v8::String::Value(wrap_handle<v8::Value>(handle));
}

int         v8_string_value_length (V8StringValue* self) {
  return self->length();
}

uint16_t*   v8_string_value_chars  (V8StringValue* self) {
  return **self;
}

void        v8_string_value_free   (V8StringValue* self) {
  delete self;
}

/* Number */
double v8_number_value(V8Handle* self) {
  return wrap_handle<v8::Number>(self)->Value(); 
}

V8Handle* v8_number_new(double value) {
  return unwrap_handle(v8::Number::New(value));
}

/* Integer */
V8Handle* v8_integer_new(int32_t value) {
  return unwrap_handle(v8::Integer::New(value));
}

V8Handle* v8_integer_new_from_unsigned(uint32_t value) {
  return unwrap_handle(v8::Integer::NewFromUnsigned(value));
}

int64_t v8_integer_value(V8Handle* self) {
  return wrap_handle<v8::Integer>(self)->Value(); 
}

/* Int32 */
int32_t v8_int32_value(V8Handle* self) {
  return wrap_handle<v8::Int32>(self)->Value(); 
}

/* Uint32 */
uint32_t v8_uint32_value(V8Handle* self) {
  return wrap_handle<v8::Uint32>(self)->Value(); 
}

/* Date */
V8Handle*    v8_date_new(double time) {
  return unwrap_handle(v8::Date::New(time));
}

double      v8_date_number_value(V8Handle* self) {
  return wrap_handle<v8::Date>(self)->NumberValue();
}

void        v8_date_time_configuration_change_notification(void) {
  v8::Date::DateTimeConfigurationChangeNotification();
}

/* Object */
V8Handle*   v8_object_new() {
  return unwrap_handle(v8::Object::New());
}

bool        v8_object_set_with_key(V8Handle *self, V8Handle* key, V8Handle* value) {
  return wrap_handle<v8::Object>(self)->Set(wrap_handle<v8::Value>(key),
                                            wrap_handle<v8::Value>(value));
}

bool        v8_object_set_with_index(V8Handle *self, uint32_t index, V8Handle* value) {
  return wrap_handle<v8::Object>(self)->Set(index,
                                            wrap_handle<v8::Value>(value));
}

V8Handle*   v8_object_get_with_key(V8Handle *self, V8Handle* key) {
  return unwrap_handle(wrap_handle<v8::Object>(self)->Get(wrap_handle<v8::Value>(key)));
}

/* External */
V8Handle*    v8_external_new(void *value) {
  return unwrap_handle(v8::External::New(value));
}

void*       v8_external_value(V8Handle* self) {
  return wrap_handle<v8::External>(self)->Value();  
}

/* Template */
void v8_template_set(V8Handle* tmpl, V8Handle* name, V8Handle* value) {
  wrap_handle<v8::Template>(tmpl)->Set(wrap_handle<v8::String>(name),
                                       wrap_handle<v8::Data>(value));
}

/* Arguments */
int v8_arguments_length(const V8Arguments* args) {
  return args->Length();
}

V8Handle* v8_arguments_get(const V8Arguments* args, int i) {
  return unwrap_handle((*args)[i]);
}

V8Handle* v8_arguments_callee(const V8Arguments* args) {
  return unwrap_handle(args->Callee());
}

V8Handle* v8_arguments_this(const V8Arguments* args) {
  return unwrap_handle(args->This());
}

V8Handle* v8_arguments_holder(const V8Arguments* args) {
  return unwrap_handle(args->Holder());
}

bool     v8_arguments_is_construct_call(const V8Arguments* args) {
  return args->IsConstructCall();
}

V8Handle* v8_arguments_data(const V8Arguments* args) {
  return unwrap_handle(args->Data());
}

/* FunctionTemplate */
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
  return wrap_handle<v8::Value>(callback_data->callback(&args));
}

V8Handle* v8_function_template_new(V8InvocationCallback callback) {
  return unwrap_handle(
      v8::FunctionTemplate::New((callback != NULL) ? v8_invocation_callback_no_data : 0,
				(callback != NULL) ? v8::External::New((void*)callback) : v8::Handle<v8::Value>()));
}

V8Handle* v8_function_template_new_with_data(V8InvocationCallbackData *callback_data) {
  return unwrap_handle(
      v8::FunctionTemplate::New(v8_invocation_callback_with_data,
				v8::External::New(callback_data)));
}

V8Handle* v8_function_template_get_function(V8Handle* self)
{
  return unwrap_handle(wrap_handle<v8::FunctionTemplate>(self)->GetFunction());
}

void v8_function_template_set_call_handler(V8Handle* self, V8InvocationCallback callback)
{
  wrap_handle<v8::FunctionTemplate>(self)->SetCallHandler(
    v8_invocation_callback_no_data,
    v8::External::New((void*)callback)
  );
}

V8Handle* v8_function_template_instance_template(V8Handle* self)
{
  return unwrap_handle(wrap_handle<v8::FunctionTemplate>(self)->InstanceTemplate());
}

void v8_function_template_inherit(V8Handle* self, V8Handle* parent)
{
  wrap_handle<v8::FunctionTemplate>(self)->Inherit(wrap_handle<v8::FunctionTemplate>(parent));
}

V8Handle* v8_function_template_prototype_template(V8Handle* self)
{
  return unwrap_handle(wrap_handle<v8::FunctionTemplate>(self)->PrototypeTemplate());
}

void v8_function_template_set_class_name(V8Handle* self, V8Handle* name)
{
  wrap_handle<v8::FunctionTemplate>(self)->SetClassName(wrap_handle<v8::String>(name));
}

void v8_function_template_set_hidden_prototype(V8Handle* self, bool value)
{
  wrap_handle<v8::FunctionTemplate>(self)->SetHiddenPrototype(value);
}

bool v8_function_template_has_instance(V8Handle* self, V8Handle* object)
{
  return wrap_handle<v8::FunctionTemplate>(self)->HasInstance(wrap_handle<v8::Value>(object));
}

V8Handle* v8_object_template_new() {
  return unwrap_handle(v8::ObjectTemplate::New());
}

V8Handle* v8_object_template_new_instance(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::ObjectTemplate>(self)->NewInstance());
}

/* getter / setter wrappers for object template */

v8::Handle<v8::Value> accessor_getter_callback(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(info.Data());
  V8AccessorData *accessor_data =
      reinterpret_cast<V8AccessorData*>(data->Value());
      
  return wrap_handle<v8::Value>(accessor_data->getter(unwrap_handle(property), &info));
}

void accessor_setter_callback(v8::Local<v8::String> property, v8::Local<v8::Value> value, 
                             const v8::AccessorInfo& info) 
{
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(info.Data());
  V8AccessorData *accessor_data =
      reinterpret_cast<V8AccessorData*>(data->Value());
  accessor_data->setter(unwrap_handle(property), unwrap_handle(value), &info);
}

v8::Handle<v8::Value> named_getter_callback(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(info.Data());
  V8NamedPropertyData *named_data =
      reinterpret_cast<V8NamedPropertyData*>(data->Value());
      
  return wrap_handle<v8::Value>(named_data->getter(unwrap_handle(property), &info));
}

v8::Handle<v8::Value> named_setter_callback(v8::Local<v8::String> property, v8::Local<v8::Value> value, 
                             const v8::AccessorInfo& info) 
{
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(info.Data());
  V8NamedPropertyData *named_data =
      reinterpret_cast<V8NamedPropertyData*>(data->Value());
  return wrap_handle<v8::Value>(named_data->setter(
                                  unwrap_handle(property), 
                                  unwrap_handle(value), 
                                  &info)
                                );
}

v8::Handle<v8::Value> indexed_getter_callback(uint32_t index, const v8::AccessorInfo& info) {
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(info.Data());
  V8IndexedPropertyData *indexed_data =
      reinterpret_cast<V8IndexedPropertyData*>(data->Value());
      
  return wrap_handle<v8::Value>(indexed_data->getter(index, &info));
}

v8::Handle<v8::Value> indexed_setter_callback(uint32_t index, v8::Local<v8::Value> value, 
                             const v8::AccessorInfo& info) 
{
  v8::Local<v8::External> data = v8::Local<v8::External>::Cast(info.Data());
  V8IndexedPropertyData *indexed_data =
      reinterpret_cast<V8IndexedPropertyData*>(data->Value());
  return wrap_handle<v8::Value>(indexed_data->setter(
                                  index, 
                                  unwrap_handle(value), 
                                  &info)
                                );
}

void v8_object_template_set_accessor(V8Handle* self, V8Handle* name, 
                                     V8AccessorData *accessor_data) {
  wrap_handle<v8::ObjectTemplate>(self)->SetAccessor(
      wrap_handle<v8::String>(name),
      accessor_getter_callback,
      (accessor_data->setter != NULL) ? accessor_setter_callback : 0,
      v8::External::New(accessor_data)      
  );
}

void v8_object_template_set_named_property_handler(V8Handle* self,
                                                   V8NamedPropertyData *named_property_data) {
   wrap_handle<v8::ObjectTemplate>(self)->SetNamedPropertyHandler(
       named_getter_callback,
       (named_property_data->setter != NULL) ? named_setter_callback : 0,
       0, 0, 0,
       v8::External::New(named_property_data)      
   );                                                  
}

void v8_object_template_set_indexed_property_handler(V8Handle* self,
                                                     V8IndexedPropertyData *indexed_property_data) {
   wrap_handle<v8::ObjectTemplate>(self)->SetIndexedPropertyHandler(
       indexed_getter_callback,
       (indexed_property_data->setter != NULL) ? indexed_setter_callback : 0,
       0, 0, 0,
       v8::External::New(indexed_property_data)      
   );
}
                                                     
void v8_object_template_set_call_as_function_handler(V8Handle* self, V8InvocationCallback callback) {
  wrap_handle<v8::ObjectTemplate>(self)->SetCallAsFunctionHandler(v8_invocation_callback_no_data,
		                                                              v8::External::New((void*)callback));
}

void v8_object_template_mark_as_undetectable(V8Handle* self) {
  wrap_handle<v8::ObjectTemplate>(self)->MarkAsUndetectable();
}

int v8_object_template_internal_field_count(V8Handle* self) {
  return wrap_handle<v8::ObjectTemplate>(self)->InternalFieldCount();
}

void v8_object_template_set_internal_field_count(V8Handle* self, int value) {
  wrap_handle<v8::ObjectTemplate>(self)->SetInternalFieldCount(value);
}

V8Handle* v8_undefined() {
  return unwrap_handle(v8::Undefined());
}

V8Handle* v8_null() {
  return unwrap_handle(v8::Null());
}

V8Handle* v8_true() {
  return unwrap_handle(v8::True());
}

V8Handle* v8_false() {
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

V8Handle* v8_try_catch_exception(V8TryCatch* try_catch) {
  return unwrap_handle(try_catch->Exception());
}

V8Handle* v8_try_catch_get_message(V8TryCatch* try_catch) {
  return unwrap_handle(try_catch->Message());
}

void v8_try_catch_reset(V8TryCatch* try_catch) {
  try_catch->Reset();
}

void v8_try_catch_set_verbose(V8TryCatch* try_catch, bool value) {
  try_catch->SetVerbose(value);
}

V8Handle* v8_context_new(V8ExtensionConfiguration extensions,
                        V8Handle* global_template) {
      
  return unwrap_handle(
      v8::Context::New(extensions,
                       wrap_handle<v8::ObjectTemplate>(global_template)));
}

void v8_context_dispose(V8Handle* context) {
    return wrap_persistent_handle<v8::Context>(context).Dispose();
}

void v8_context_enter(V8Handle* context) {
  wrap_handle<v8::Context>(context)->Enter();
}

void v8_context_exit(V8Handle* context) {
  wrap_handle<v8::Context>(context)->Exit();
}

V8Handle* v8_context_global(V8Handle* self) {
  return unwrap_handle(wrap_handle<v8::Context>(self)->Global());
}

V8Handle* v8_context_get_current() {
  return unwrap_handle(v8::Context::GetCurrent());
}

V8Handle* v8_exception_range_error      (V8Handle* message) {
  return unwrap_handle(v8::Exception::RangeError(wrap_handle<v8::String>(message)));
}

V8Handle* v8_exception_reference_error  (V8Handle* message) {
  return unwrap_handle(v8::Exception::ReferenceError(wrap_handle<v8::String>(message)));
}

V8Handle* v8_exception_syntax_error     (V8Handle* message) {
  return unwrap_handle(v8::Exception::SyntaxError(wrap_handle<v8::String>(message)));
}

V8Handle* v8_exception_type_error       (V8Handle* message) {
  return unwrap_handle(v8::Exception::TypeError(wrap_handle<v8::String>(message)));
}

V8Handle* v8_exception_error            (V8Handle* message) {
  return unwrap_handle(v8::Exception::Error(wrap_handle<v8::String>(message)));
}

V8Handle* v8_exception_throw            (V8Handle* exception) {
  return unwrap_handle(v8::ThrowException(wrap_handle<v8::Value>(exception)));
}

}  // extern "C"