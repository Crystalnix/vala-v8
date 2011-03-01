using v8;
using GI;

public class Importer {
  private Importer() {}
  
  public static void init(v8.Object global) {
    HandleScope hs = new HandleScope();
    
    unowned ObjectTemplate imports_t;
    unowned ObjectTemplate imports_gi_t;
    
    imports_t = (ObjectTemplate)Persistent.new(ObjectTemplate.new(), HandleType.OBJECT_TEMPLATE);
    imports_npd = { Importer.imports_get_property, null };
    imports_t.set_named_property_handler(ref imports_npd);
    imports = (v8.Object)Persistent.new(imports_t.new_instance(), HandleType.OBJECT);
    
    imports_gi_t = (ObjectTemplate)Persistent.new(ObjectTemplate.new(), HandleType.OBJECT_TEMPLATE);
    imports_gi_npd = { Importer.imports_gi_get_property, null };
    imports_gi_t.set_named_property_handler(ref imports_gi_npd);
    imports_gi = (v8.Object)Persistent.new(imports_gi_t.new_instance(), HandleType.OBJECT);
    
    imports_gi_versions = (v8.Object)Persistent.new(v8.Object.new(), HandleType.OBJECT);
      
    gi_hash = new HashTable<string, Handle>(str_hash, str_equal);
    
    global.set_with_key(String.new("imports", -1), imports);
  }
  
  private static unowned Handle imports_get_property(Handle property, AccessorInfo info) {
    String.Utf8Value prop_str = new String.Utf8Value(property);
    if (strcmp(prop_str.chars(), "gi") == 0)
      return imports_gi;
    if (strcmp(prop_str.chars(), "searchPath") == 0)
      return v8.null();
    if (strcmp(prop_str.chars(), "toString") == 0)
      return v8.null();
    return v8.null();
  }
  
  private static unowned Handle imports_gi_get_property(Handle property, AccessorInfo info) {
    String.Utf8Value prop_str = new String.Utf8Value(property);
    if (strcmp(prop_str.chars(), "versions") == 0)
      return imports_gi_versions;
    if (strcmp(prop_str.chars(), "toString") == 0)
      return v8.null();
    if (strcmp(prop_str.chars(), "valueOf") == 0)
      return v8.null();
      
    unowned v8.Value ret;
    ret = imports_gi_do_namespace(prop_str.chars());
    /*if (ret.is_empty()) {
      String.Utf8Value msg = new String.Utf8Value(tc.exception());
      stderr.printf("Unable to import namespace: %s\n", msg.chars());
    }
    */
    
    return ret;
  }
  
  private static unowned v8.Value imports_gi_do_namespace(string namespace) {
    unowned v8.Object namespace_obj;
    HandleScope hs = new HandleScope();
    
    namespace_obj = (v8.Object)gi_hash.lookup(namespace);
    if (namespace_obj != null) {
      /* TODO: log */
      return namespace_obj;
    }
    
    unowned String version = imports_gi_get_version(namespace);
    String.Utf8Value version_v = new String.Utf8Value(version);

    try {
      Repository.require(null, namespace, version_v.chars(), 0);
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
  
  private static unowned String imports_gi_get_version(string namespace) {
    HandleScope hs = new HandleScope();
    unowned v8.Value ret = imports_gi_versions.get_with_key(String.new(namespace, -1));
    return (String)hs.close(ret, HandleType.VALUE);
  }
  
  private static NamedPropertyData imports_npd;
  private static NamedPropertyData imports_gi_npd;
  private static unowned v8.Object imports;
  private static unowned ObjectTemplate imports_t;
  private static unowned v8.Object imports_gi;
  private static unowned ObjectTemplate imports_gi_t;
  private static unowned v8.Object imports_gi_versions;
  private static HashTable<string, Handle> gi_hash;
}