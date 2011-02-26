#include "v8c.h"

int main(int argc, char* argv[]) {

  // Create a stack-allocated handle scope.
  V8HandleScope* handle_scope = v8_handle_scope_new ();

  V8Persistent* context = v8_context_new ();
  
  // Enter the created context for compiling and
  // running the hello world script. 
  v8_context_enter (v8_handle_data (context));

  // Create a string containing the JavaScript source code.
  V8Handle* source = v8_string_new_utf8 ("'Hello' + ', World!'");

  // Compile the source code.
  V8Handle* script = v8_script_compile (source);
  
  // Run the script to get the result.
  V8Handle* result = v8_script_run (v8_handle_data (script));
  
  // Dispose the persistent context.
  v8_persistent_dispose (context);

  // Convert the result to an ASCII string and print it.
  V8StringUtf8Value* utf = v8_string_utf8_value_new (result);
  printf ("%s\n", v8_string_utf8_value_chars (utf));
  v8_string_utf8_value_free (utf);

  v8_context_exit (v8_handle_data (context));

  v8_handle_free (result);
  v8_handle_free (script);
  v8_handle_free (source);
  v8_handle_free (context);
  v8_handle_scope_free (handle_scope);
  return 0;
}
