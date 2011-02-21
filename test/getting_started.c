#include "../v8-bindings/v8c.h"

#include <stdio.h>

static void print_value(V8Handle *v) {
  V8StringUtf8Value* utf8 = v8_string_utf8_value_new(v);
  printf("%s", v8_string_utf8_value_chars(utf8));
  v8_string_utf8_value_free(utf8);
}

// A callback from JavaScript to print concisely.
static V8Handle* print_cb(const V8Arguments* args) {
  int i, length = v8_arguments_length(args);
  for (i = 0; i < length; ++i) {
    if (i > 0)
      printf(" ");
    print_value(v8_arguments_get(args, i));
  }
  printf("\n");
  return v8_undefined();
}

int main(int argc, char *argv[])
{
  V8Handle *context, *source, *script, *result, *global, *print;
  V8HandleScope *handle_scope;
  V8StringUtf8Value* utf8_value;
  
  handle_scope = v8_handle_scope_new();

	print = v8_function_template_new(print_cb);
	global = v8_object_template_new();
	v8_template_set(global, v8_string_new_utf8("print", -1), print);  

  context = v8_context_new(NULL, global);
  v8_context_enter(context);
  
  source = v8_string_new_utf8("print(1); 'Hello' + ', World!'", -1);
  
  script = v8_script_compile(source);
  
  result = v8_script_run(script);
  
  v8_context_dispose(context);
  
  utf8_value = v8_string_utf8_value_new(result);
  printf("%s\n", v8_string_utf8_value_chars(utf8_value));
  v8_string_utf8_value_free(utf8_value);
  
  v8_handle_scope_free(handle_scope);
  
  return 0;
}