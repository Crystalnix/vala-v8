[CCode (cheader_filename = "v8c.h" cprefix="v8_")]
namespace v8 {
    [Compact]
    [CCode (cname = "V8Handle", cprefix = "v8_handle_")]
    public class Handle {
        public is_empty ();
    }
    
    [Compact]
    [CCode (cname = "V8HandleScope", cprefix = "v8_handle_scope_")]
    public class HandleScope {
        [CCode (cname = "v8_handle_scope_new")]
        public HandleScope ();
        public void free ();
        public Handle close (Handle value, HandleType handle_type);
        public static number_of_handles ();
    }
    
    [Compact]
    [CCode (cname = "V8Handle", cprefix = "v8_context_")]
    public class Context : Handle {
        [CCode (cname = "v8_context_new")]
        public Context (ExtensionConfiguration extensions, Handle global_template);
        public void dispose ();
        public void enter ();
        public void exit ();
        public Handle global();
    }
    
    [Compact]
    [CCode (cname = "V8Handle", cprefix = "v8_string_")]
    public class String : Handle {
        [CCode (cname = v8_string_new_utf8)]
        public String (string data, int length);
        
        [CCode (cname = "V8StringAsciiValue", cprefix = "v8_string_ascii_value_")]
        public class AsciiValue {
            [CCode (cname = "v8_string_ascii_value_new")]
            public AsciiValue (Handle handle);
            public int length();
            public int chars();
            public void free(); 
        }
    }
    
    [Compact]
    [CCode (cname = "V8Handle", cprefix = "v8_script_")]
    public class Script : Handle {
        public static Script compile (String source);
        public Handle run ();
    }
    
    [CCode (cname = "V8HandleType")]
    public enum HandleType {
        UNKNOWN,
        DATA,
        SCRIPT,
        MESSAGE,
        STACK_TRACE,
        STACK_FRAME,
        VALUE,
        PRIMITIVE,
        BOOLEAN,
        STRING,
        NUMBER,
        INTEGER,
        INT32,
        UINT32,
        DATE,
        REGEXP,
        OBJECT,
        ARRAY,
        FUNCTION,
        EXTERNAL,
        TEMPLATE,
        FUNCTION_TEMPLATE,
        OBJECT_TEMPLATE,
        SIGNATURE,
        TYPE_SWITCH,
        CONTEXT
    }
    
    [CCode (cname = "V8ExtensionConfiguration")]
    public class ExtensionConfiguration {}
}