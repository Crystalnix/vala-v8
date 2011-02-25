using namespace v8;
using namespace GI;

public class Importer {
  private Importer() {}
  
  public static init(ObjectTemplate global) {
    HandleScope hs = new HandleScope();
    
    imports = new Persistent(new ObjectTemplate(), HandleType.OBJECT_TEMPLATE);
    NamedPropertyData imports_npd = { Importer.imports_get_property, null };
    imports.set_named_property_handler(imports_npd);
    
    imports_gi = new Persistent(new ObjectTemplate(), HandleType.OBJECT_TEMPLATE);
    NamedPropertyData imports_gi_npd = { Importer.imports_gi_get_property, null }
    imports_gi.set_named_property_handler(imports_gi_npd);
    
    imports_gi_versions = new Persistent(new v8.Object(), HandleType.OBJECT);
    
    gi_hash = new HashTable<string, Handle>();
    
    global.set(new String("imports", -1), imports.new_instance());
  }
  
  private static Handle imports_get_property(Handle property, AccessorInfo info) {
    String.Utf8Value prop_str = new String.Utf8Value(property);
    if (!strcmp(prop_str.chars(), "gi"))
      return imports_gi;
    if (!strcmp(prop_str.chars(), "searchPath"))
      return NULL;
    if (!strcmp(prop_str.chars(), "toString"))
      return NULL;
  }
  
  private static Handle imports_gi_get_property(Handle property, AccessorInfo info) {
    String.Utf8Value prop_str = new String.Utf8Value(property);
    if (!strcmp(prop_str.chars(), "versions"))
      return imports_gi_versions;
    if (!strcmp(prop_str.chars(), "toString"))
      return NULL;
    if (!strcmp(prop_str.chars(), "valueOf")
      return NULL;
      
    Value ret;
    TryCatch tc = new TryCatch();
    ret = imports_gi_do_namespace(prop_str.chars());
    /*if (ret.is_empty()) {
      String.Utf8Value msg = new String.Utf8Value(tc.exception());
      stderr.printf("Unable to import namespace: %s\n", msg.chars());
    }
    */
    
    return ret;
  }
  
  private static Value imports_gi_do_namespace(unowned string namespace) {
    v8.Object namespace_obj;
    HandleScope hs = new HandleScope();
    
    if (namespace_obj = gi_hash.lookup(namespace)) {
      /* TODO: log */
      return namespace_obj;
    }
    
    String version = imports_gi_get_version(namespace);
    String.Utf8Value version_v = new String.Utf8Value(version);

    try {
      Repository.require(null, namespace, version, 0);
      uint n = Repository.get_n_infos(null, namespace);
    
      BaseInfo info;
      for (int i = 0; i < n; i++) {
        InfoType info_type;
        info = Repository.get_info(null, namespace, i);
        info_type = info.get_type();
        /*switch (info_type) {
          case InfoType.FUNCTION:
            FunctionInfo func_info = (FunctionInfo) info;
            stdout.printf("%s\n", func_info.get_symbol());
            break;
          case InfoType.OBJECT:
            ObjectInfo obj_info = (ObjectInfo) info;
            stdout.printf("%s\n", obj_info.get_type_name());
            break;
          case InfoType.ENUM:
          case InfoType.FLAGS:
            EnumInfo enum_info = (EnumInfo) info;
          
          default:
            break;
        }*/
        stdout.printf("%s\n", info.get_name());
      }
    
    } catch (Error e) {
      stderr.printf("Error: %s\n", e.message);
      return v8.undefined();
    }
    
    return v8.null();
  }
  
  private static String imports_gi_get_version(unowned string namespace) {
    HandleScope hs = new HandleScope();
    Value ret = imports_gi_versions.get_with_key(new String(namespace, -1));
    return hs.close(ret, HandleType.VALUE);
  }
  
  private static ObjectTemplate imports;
  private static ObjectTemplate imports_gi;
  private static v8.Object imports_gi_versions;
  private static HashTable<string, Handle> gi_hash;
}