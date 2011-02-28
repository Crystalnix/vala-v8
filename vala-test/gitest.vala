using v8;

unowned String read_file(string fname) {
  string tmp;
  size_t length;
  
  try {
    GLib.FileUtils.get_contents(fname, out tmp, out length);
  }
  catch (FileError fe) {
     stderr.printf("Error: %s\n", fe.message);
  }
  
  return String.new(tmp, (int)length);
}

int main (string[] args) 
{
  if (args.length < 2) {
    stderr.printf("No source file specified.\n");
    return 1;
  }
  
  set_flags_from_command_line(ref args, false);
    
	HandleScope handle_scope = new HandleScope();

	unowned ObjectTemplate global = ObjectTemplate.new ();
  
  Importer.init(global);
  
  unowned Context context = Context.new (null, global);
	context.enter ();

	unowned String source = read_file(args[1]);

	unowned Script script = Script.compile (source);

	unowned v8.Value result = script.run ();

  context.exit ();
	context.dispose ();
	
	return 0;
}