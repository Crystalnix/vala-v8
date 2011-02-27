/* Copyright 2011 Crystalnix <thekondr@gmail.com>
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

/* To have the compiler help catch type errors, this file is #included by
   both the C++ implementation and the C user.  These typedefs make the
   function prototypes work on both sides.
*/

typedef void V8HandleWrap;

#ifdef __cplusplus
class V8CHandleScope;
template <class T> class V8CHandleWrap;
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

  typedef struct _V8Handle {
    void *handle;
    V8HandleType  type;
  } V8Handle;

  typedef V8Handle V8Local;
  typedef V8Handle V8Persistent;

  typedef void V8String;
  typedef void V8Script;
  typedef void V8Context;

  /* Handle */
  void*       v8_handle_data(V8Handle* self);
  void        v8_handle_free(V8Handle* self);
  bool        v8_handle_is_empty(V8Handle* self);

  /* Persistent */
  void        v8_persistent_dispose(V8Handle* self);

  /* HandleScope */
  V8HandleScope* v8_handle_scope_new();
  void           v8_handle_scope_free(V8HandleScope* hs);

  /* Script */
  V8Local* v8_script_compile(V8Handle* code);
  V8Local* v8_script_run(V8Script* self);

  V8Handle*    v8_string_new_utf8      (const char* data, int length);
 
  /* String::Utf8Value */
  V8StringUtf8Value* v8_string_utf8_value_new(V8Handle* handle);
  int     v8_string_utf8_value_length(V8StringUtf8Value* utf8);
  char*   v8_string_utf8_value_chars(V8StringUtf8Value* utf8);
  void    v8_string_utf8_value_free(V8StringUtf8Value* utf8);

  /* Context */
  V8Persistent* v8_context_new();
  void v8_context_dispose(V8Context* self);
  void v8_context_enter(V8Context* self);
  void v8_context_exit(V8Context* self);

#ifdef __cplusplus
}
#endif
