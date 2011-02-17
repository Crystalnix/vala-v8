/* Copyright 2007-2008 the V8 project authors. 
   Copyright 2011 Crystalnix <vgachkaylo@crystalnix.com>, <thekondr@gmail.com>
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

       * Redistributions of source code must retain the above copyright
         notice, this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above
         copyright notice, this list of conditions and the following
         disclaimer in the documentation and/or other materials provided
         with the distribution.
       * Neither the name of Google Inc. nor the names of its
         contributors may be used to endorse or promote products derived
         from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* v8c -- v8 API for using v8 from C (and other languages that can bind against
   C). */

/* NOTE: This file tries to follow include/v8.h directly.  The
   function order should match the order there, and that file should contain
   all the documentation.
*/

#include <stdint.h>

/* v8::Handle has a lot of nice type-checking and wrapping and unwrapping,
   but in the C world all we get is a pointer.
   Internally, V8Handle is the pointer held by a v8::Handle.
*/
typedef void* V8Handle;

typedef enum _V8HandleType {
    V8HT_UNKNOWN = 0,
    V8HT_DATA,
    V8HT_SCRIPT,
    V8HT_MESSAGE,
    V8HT_STACK_TRACE,
    V8HT_STACK_FRAME,
    V8HT_VALUE,
    V8HT_PRIMITIVE,
    V8HT_BOOLEAN,
    V8HT_STRING,
    V8HT_NUMBER,
    V8HT_INTEGER,
    V8HT_INT32,
    V8HT_UINT32,
    V8HT_DATE,
    V8HT_REGEXP,
    V8HT_OBJECT,
    V8HT_ARRAY,
    V8HT_FUNCTION,
    V8HT_EXTERNAL,
    V8HT_TEMPLATE,
    V8HT_FUNCTION_TEMPLATE,
    V8HT_OBJECT_TEMPLATE,
    V8HT_SIGNATURE,
    V8HT_TYPE_SWITCH,
    V8HT_CONTEXT    
} V8HandleType;

/* To have the compiler help catch type errors, this file is #included by
   both the C++ implementation and the C user.  These typedefs make the
   function prototypes work on both sides.
 */
#ifdef __cplusplus
class V8CHandleScope;
extern "C" {
typedef V8CHandleScope          V8HandleScope;
typedef v8::Arguments           V8Arguments;
typedef v8::AccessorInfo        V8AccessorInfo;
typedef v8::ExtensionConfiguration* V8ExtensionConfiguration;
typedef v8::String::Utf8Value   V8StringUtf8Value;
typedef v8::String::AsciiValue  V8StringAsciiValue;
typedef v8::String::Value       V8StringValue;
typedef v8::TryCatch            V8TryCatch;
#else  /* Compiling on the C side. */
typedef int bool;
typedef struct _V8HandleScope   V8HandleScope;
typedef struct _V8Arguments     V8Arguments;
typedef struct _V8AccessorInfo  V8AccessorInfo;
typedef void*                   V8ExtensionConfiguration;
typedef void                    V8StringUtf8Value;
typedef void                    V8StringAsciiValue;
typedef void                    V8StringValue;
typedef struct _V8TryCatch      V8TryCatch;
#endif

/* Handle */
bool        v8_handle_is_empty(V8Handle handle);

/* HandleScope */
V8HandleScope* v8_handle_scope_new();
void           v8_handle_scope_free(V8HandleScope* hs);
V8Handle       v8_handle_scope_close(V8HandleScope *self, V8Handle value, V8HandleType handle_type);
int            v8_handle_scope_number_of_handles();

/* Script */
V8Handle v8_script_compile(V8Handle source);
V8Handle v8_script_run(V8Handle script);

/* Message */
V8Handle v8_message_get(V8Handle self);
V8Handle v8_message_get_source_line(V8Handle self);
V8Handle v8_message_get_script_resource_name(V8Handle self);
V8Handle v8_message_get_stack_trace(V8Handle self);
int      v8_message_get_line_number(V8Handle self);
int      v8_message_get_start_position(V8Handle self);
int      v8_message_get_end_position(V8Handle self);
int      v8_message_get_start_column(V8Handle self);
int      v8_message_get_end_column(V8Handle self);

/* StackTrace */
V8Handle v8_stack_trace_get_frame(V8Handle self, uint32_t index);
int      v8_stack_trace_get_frame_count(V8Handle self);

/* StackFrame */
int      v8_stack_frame_get_line_number(V8Handle self);
int      v8_stack_frame_get_column(V8Handle self);
V8Handle v8_stack_frame_get_script_name(V8Handle self);
V8Handle v8_stack_frame_get_script_name_or_source_url(V8Handle self);
V8Handle v8_stack_frame_get_function_name(V8Handle self);
bool     v8_stack_frame_is_eval(V8Handle self);
bool     v8_stack_frame_is_constructor(V8Handle self);

/* Value */
bool v8_value_is_undefined  (V8Handle self);
bool v8_value_is_null       (V8Handle self);
bool v8_value_is_true       (V8Handle self);
bool v8_value_is_false      (V8Handle self);
bool v8_value_is_string     (V8Handle self);
bool v8_value_is_function   (V8Handle self);
bool v8_value_is_array      (V8Handle self);
bool v8_value_is_object     (V8Handle self);
bool v8_value_is_boolean    (V8Handle self);
bool v8_value_is_number     (V8Handle self);
bool v8_value_is_external   (V8Handle self);
bool v8_value_is_int32      (V8Handle self);
bool v8_value_is_uint32     (V8Handle self);
bool v8_value_is_date       (V8Handle self);
bool v8_value_is_regexp     (V8Handle self);

V8Handle v8_value_to_boolean    (V8Handle self);
V8Handle v8_value_to_number     (V8Handle self);
V8Handle v8_value_to_string     (V8Handle self);
V8Handle v8_value_to_detail_string (V8Handle self);
V8Handle v8_value_to_object     (V8Handle self);
V8Handle v8_value_to_integer    (V8Handle self);
V8Handle v8_value_to_uint32     (V8Handle self);
V8Handle v8_value_to_int32      (V8Handle self);

V8Handle v8_value_to_external   (V8Handle self);

V8Handle v8_value_to_array_index(V8Handle self);

bool     v8_value_boolean_value (V8Handle self);
double   v8_value_number_value  (V8Handle self);
int64_t  v8_value_integer_value (V8Handle self);
uint32_t v8_value_uint32_value  (V8Handle self);
int32_t  v8_value_int32_value   (V8Handle self);

void*    v8_value_voidp_value   (V8Handle self);

bool v8_value_equals(V8Handle self, V8Handle that);
bool v8_value_strict_equals(V8Handle self, V8Handle that);

/* Boolean */
bool v8_boolean_value(V8Handle self);
V8Handle v8_boolean_new(bool value);

/* String */
V8Handle    v8_string_new_utf8      (const char* data, int length);
int         v8_string_length        (V8Handle self);
int         v8_string_utf8_length   (V8Handle self);
V8Handle    v8_string_empty         (void);
bool        v8_string_is_external   (V8Handle self);
bool        v8_string_is_external_ascii   (V8Handle self);

/* String::Utf8Value */
V8StringUtf8Value* v8_string_utf8_value_new(V8Handle handle);
int     v8_string_utf8_value_length(V8StringUtf8Value* utf8);
char*   v8_string_utf8_value_chars(V8StringUtf8Value* utf8);
void    v8_string_utf8_value_free(V8StringUtf8Value* utf8);

/* String::AsciiValue */
V8StringAsciiValue*     v8_string_ascii_value_new(V8Handle handle);
int     v8_string_ascii_value_length (V8StringAsciiValue* self);
char*   v8_string_ascii_value_chars  (V8StringAsciiValue* self);
void    v8_string_ascii_value_free   (V8StringAsciiValue* self);

/* String::Value (2-byte string) */
V8StringValue*     v8_string_value_new(V8Handle handle);
int         v8_string_value_length (V8StringValue* self);
uint16_t*   v8_string_value_chars  (V8StringValue* self);
void        v8_string_value_free   (V8StringValue* self);

/* Number */
double v8_number_value(V8Handle self);
V8Handle v8_number_new(double value);

/* Integer */
V8Handle v8_integer_new(int32_t value);
V8Handle v8_integer_new_from_unsigned(uint32_t value);
int64_t v8_integer_value(V8Handle self);

/* Int32 */
int32_t v8_int32_value(V8Handle self);

/* Uint32 */
uint32_t v8_uint32_value(V8Handle self);

/* Date */
V8Handle    v8_date_new(double time);
double      v8_date_number_value(V8Handle self);
void        v8_date_time_configuration_change_notification(void);

/* External */
V8Handle    v8_external_new(void *value);
void*       v8_external_value(V8Handle self);

/* Template */
void v8_template_set(V8Handle tmpl, V8Handle name, V8Handle value);

/* Arguments */
int v8_arguments_length(const V8Arguments* args);
V8Handle v8_arguments_get(const V8Arguments* args, int i);

/* FunctionTemplate */
/* V8 lets you add a "data" value to a function template, but v8c uses
   it internally.  We could still provide extra-data-like
   functionality if needed, though. */
typedef V8Handle (*V8InvocationCallback)(const V8Arguments*);
typedef struct _V8InvocationCallbackData {
  V8InvocationCallback callback;
  void *data;
} V8InvocationCallbackData;

V8Handle v8_function_template_new(V8InvocationCallback callback);
/* v8_function_template_new_with_data(): */
/* Creates JavaScript callback with custom data passed to the C callback function */
/* callbackData pointer must be valid until function template handle is disposed */
V8Handle v8_function_template_new_with_data(V8InvocationCallbackData *callbackData);
V8Handle v8_function_template_get_function(V8Handle self);
void v8_function_template_set_call_handler(V8Handle self, V8InvocationCallback callback);
V8Handle v8_function_template_instance_template(V8Handle self);
void v8_function_template_inherit(V8Handle self, V8Handle parent);
V8Handle v8_function_template_prototype_template(V8Handle self);
void v8_function_template_set_class_name(V8Handle self, V8Handle name);
void v8_function_template_set_hidden_prototype(V8Handle self, bool value);
bool v8_function_template_has_instance(V8Handle self, V8Handle object);

/* ObjectTemplate */
typedef V8Handle    (*V8AccessorGetter)(V8Handle, const V8AccessorInfo*);
typedef void        (*V8AccessorSetter)(V8Handle, V8Handle, const V8AccessorInfo*);
typedef V8AccessorGetter V8NamedPropertyGetter; 
typedef V8Handle    (*V8NamedPropertySetter)(V8Handle, V8Handle, const V8AccessorInfo*);
typedef V8Handle    (*V8IndexedPropertyGetter)(uint32_t, const V8AccessorInfo*);
typedef V8Handle    (*V8IndexedPropertySetter)(uint32_t, V8Handle, const V8AccessorInfo*);

typedef struct _V8AccessorData {
    V8AccessorGetter getter;
    V8AccessorSetter setter;
} V8AccessorData;

typedef struct _V8NamedPropertyData {
    V8NamedPropertyGetter getter;
    V8NamedPropertySetter setter;
} V8NamedPropertyData;

typedef struct _V8IndexedPropertyData {
    V8IndexedPropertyGetter getter;
    V8IndexedPropertySetter setter;
} V8IndexedPropertyData;

V8Handle v8_object_template_new();
V8Handle v8_object_template_new_instance(V8Handle self);
void v8_object_template_set_accessor(V8Handle self, V8Handle name, 
                                     V8AccessorData *accessor_data);
void v8_object_template_set_named_property_handler(V8Handle self,
                                                   V8NamedPropertyData *named_property_data);
void v8_object_template_set_indexed_property_handler(V8Handle self,
                                                     V8IndexedPropertyData *indexed_property_data);
void v8_object_template_set_call_as_function_handler(V8Handle self, V8InvocationCallback callback);
void v8_object_template_mark_as_undetectable(V8Handle self);
int v8_object_template_internal_field_count(V8Handle self);
void v8_object_template_set_internal_field_count(V8Handle self, int value);

/* Special static values */
V8Handle v8_undefined();
V8Handle v8_null();
V8Handle v8_true();
V8Handle v8_false();

/* V8 (class containing static functions) */
void v8_set_flags_from_command_line(int* argc, char** argv,
                                    bool remove_flags);

/* TryCatch */
V8TryCatch* v8_try_catch_new();
void v8_try_catch_free(V8TryCatch* try_catch);
bool v8_try_catch_has_caught(V8TryCatch* try_catch);
V8Handle v8_try_catch_exception(V8TryCatch* try_catch);
V8Handle v8_try_catch_get_message(V8TryCatch* try_catch);
void v8_try_catch_reset(V8TryCatch* try_catch);
void v8_try_catch_set_verbose(V8TryCatch* try_catch, bool value);

/* Context */
V8Handle v8_context_new(V8ExtensionConfiguration extensions,
                        V8Handle global_template);
void v8_context_free(V8Handle context);
void v8_context_enter(V8Handle context);
void v8_context_exit(V8Handle context);

#ifdef __cplusplus
}
#endif