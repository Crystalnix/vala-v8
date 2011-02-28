using v8;

static void print_value (Handle v) {
  String.Utf8Value utf8 = new String.Utf8Value (v);
  stdout.printf (utf8.chars ());
}

// A callback from JavaScript to print concisely.
static Handle print_cb (Arguments args) {
  int i, length = args.length ();
  for (i = 0; i < length; ++i) {
    if (i > 0)
      stdout.printf (" ");
    print_value (args.get(i));
  }
  stdout.printf ("\n");
  return undefined ();
}

int main (string[] args)
{
	HandleScope handle_scope;
	String.Utf8Value utf8_value;

	handle_scope = new HandleScope ();

	var print = new FunctionTemplate (print_cb);
	var global = new ObjectTemplate ();
	global.set (new String ("print", -1), print);

	var context = Context.new (null, global);
	context.enter ();

	var source = new String ("print(1); 'Hello' + ', World!'", -1);

	var script = Script.compile (source);

	var result = script.run ();

    context.exit ();
	context.dispose ();
	
	utf8_value = new String.Utf8Value (result);
	stdout.printf ("%s\n", utf8_value.chars ());
	
	return 0;
}
