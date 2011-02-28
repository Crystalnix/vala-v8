/* Copyright 2011 Crystalnix <thekondr@gmail.com>, <vgachkaylo@gmail.com>
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

[CCode (cprefix = "V8", cheader_filename = "v8c.h")]
namespace v8
{
	[Compact]
	[CCode (free_function = "")]
	public class Handle {
		public bool is_empty ();
	}
	
    [Compact]
    [CCode (cname = "V8Handle")]
    public class Local : Handle {
        public static unowned Local new(Handle that, HandleType type);
    }
    
    [Compact]
    [CCode (cname = "V8Handle")]
    public class Persistent : Handle {
        public static unowned Persistent new(Handle that, HandleType type);
        public void dispose(HandleType type);
    }

	[CCode (cprefix = "V8HT_", has_type_id = false)]
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

	[Compact]
	public class HandleScope {
		public HandleScope ();
		public unowned Handle close (Handle value, HandleType handle_type);
		public static int number_of_handles ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Script : Handle {
		public static unowned Script compile (Handle source);
		public unowned v8.Value run ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Message : Handle {
		public unowned Handle get ();
		public unowned Handle get_source_line ();
		public unowned Handle get_script_resource_name ();
		public unowned Handle get_stack_trace ();
		public int get_line_number ();
		public int get_start_position ();
		public int get_end_position ();
		public int get_start_column ();
		public int get_end_column ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class StackTrace : Handle {
		public unowned Handle get_frame (uint32 index);
		public unowned Handle get_frame_count ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class StackFrame : Handle {
		public int get_line_number ();
		public int get_column ();
		public unowned Handle get_script_name ();
		public Handle get_script_name_or_source_url ();
		public Handle get_function_name ();
		public bool is_eval ();
		public bool is_constructor ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Value : Handle {
		public bool is_undefined ();
		public bool is_null ();
		public bool is_true ();
		public bool is_false ();
		public bool is_string ();
		public bool is_function ();
		public bool is_array ();
		public bool is_object ();
		public bool is_boolean ();
		public bool is_number ();
		public bool is_external ();
		public bool is_int32 ();
		public bool is_uint32 ();
		public bool is_date ();
		public bool is_regexp ();

		public unowned Handle to_boolean ();
		public unowned Handle to_number ();
		public unowned Handle to_string ();
		public unowned Handle to_detail_string ();
		public unowned Handle to_object ();
		public unowned Handle to_integer ();
		public unowned Handle to_uint32 ();
		public unowned Handle to_int32 ();

		public unowned Handle to_external ();

		public unowned Handle to_array_index ();

		public bool boolean_value ();
		public double number_value ();
		public int64 integer_value ();
		public uint32 uint32_value ();
		public int32 int32_value ();

		/* FIXME: Is it works? */
		public void* voidp_value ();

		public bool equals (Handle that);
		public bool strict_equals (Handle that);
	}

    [Compact]
    [CCode (cname = "V8Handle")]
    public class Primitive : v8.Value {}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Boolean : v8.Value {
		public static unowned Boolean new (bool value);
		public bool value ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class String : v8.Value {
		[CCode (cname = "v8_string_new_utf8")]
		public static unowned String new (string data, int length);
		public static unowned Handle empty ();
		public int length ();
		public int utf8_length ();
		public bool is_external ();
		public bool is_external_ascii ();

		[Compact]
		[CCode (cname = "V8Handle")]
		public class AsciiValue {
			public AsciiValue (Handle handle);
			public int length ();
			public unowned string chars ();
		}

		[Compact]
		[CCode (cname = "V8Handle")]
		public class Utf8Value {
			public Utf8Value (Handle handle);
			public int length ();
			public unowned string chars ();
		}

		[Compact]
		[CCode (cname = "V8Handle")]
		public class Value {
			public Value (Handle handle);
			public int length ();
			/* FIXME: ptr to uint16? */
			public unowned uint16 chars ();
		}
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Number : v8.Value {
		public static unowned Number new (double value);
		public double value ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Integer : Number {
		public static unowned Integer new (int32 value);
		public Integer.from_unsigned (uint32 value);
		public int64 value ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Int32 : Integer {
		public int32 value ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Uint32 : Integer {
		public uint32 value ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Date : v8.Value {
		public static unowned Date new (double time);
		public double number_value ();
		public static void time_configuration_change_notification ();
	}

    [Compact]
    [CCode (cname = "V8Handle")]
    public class Object : v8.Value {
        public static unowned Object new ();
        public bool set_with_key (Value key, Value value);
        public bool set_with_index (uint32 index, Value value);
        public unowned Value get_with_key (Value key);
    }
    
	/* FIXME: is void ptr works? */
	[Compact]
	[CCode (cname = "V8Handle")]
	public class External : v8.Value {
		public static unowned External new (void *value);
		public void* value ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Template : Handle {
		public void set (Handle name, Handle value);
	}

	[Compact]
	public struct Arguments {
		public int length ();
		public unowned Handle get (int i);
		public unowned Handle callee ();
		public unowned Handle this ();
		public unowned Handle holder ();
		public bool is_construct_call ();
		public unowned Handle data ();
	}

	[CCode (has_target = false)]
	public delegate unowned Handle InvocationCallback (Arguments args);

	public struct InvocationCallbackData {
		public InvocationCallback callback;
		public void *data;
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class FunctionTemplate : Template {
		public static unowned FunctionTemplate new (InvocationCallback callback);
		public static unowned FunctionTemplate new_with_data (InvocationCallbackData callbackData);
		public unowned Handle get_function ();
		public void set_call_handler (InvocationCallback callback);
		public unowned Handle instance_template ();
		public void inherit (Handle parent);
		public unowned Handle prototype_template ();
		public void set_class_name (Handle name);
		public void set_hidden_prototype (bool value);
		public bool has_instance (Handle object);
	}

	[Compact]
	public class AccessorInfo {}

	[CCode (has_target = false)]
	public delegate unowned Handle AccessorGetter (Handle property, AccessorInfo info);

	[CCode (has_target = false)]
	public delegate void AccessorSetter (Handle property, Handle value, AccessorInfo info);

	[CCode (has_target = false)]
	public delegate unowned Handle NamedPropertyGetter (Handle property, AccessorInfo info);

	[CCode (has_target = false)]
	public delegate unowned Handle NamedPropertySetter (Handle property, Handle value, AccessorInfo info);

	[CCode (has_target = false)]
	public delegate unowned Handle IndexedPropertyGetter (uint32 index, AccessorInfo info);

	[CCode (has_target = false)]
	public delegate unowned Handle IndexedPropertySetter (uint32 index, Handle value, AccessorInfo info);

	public struct AccessorData {
		public AccessorGetter getter;
		public AccessorSetter setter;
	}

	public struct NamedPropertyData {
		public NamedPropertyGetter getter;
		public NamedPropertySetter setter;
	}

	public struct IndexedPropertyData {
		public IndexedPropertyGetter getter;
		public IndexedPropertySetter setter;
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class ObjectTemplate : Template {
		public static unowned ObjectTemplate new ();
		public unowned Handle new_instance ();
		public void set_accessor (Handle name, AccessorData accessor_data);
		public void set_named_property_handler (NamedPropertyData named_property_data);
		public void set_indexed_property_handler (IndexedPropertyData indexed_property_data);
		public void set_call_as_function_handler (InvocationCallback callback);
		public void mark_as_undetectable ();
		public int internal_field_count ();
		public void set_internal_field_count (int value);
	}

	public static unowned Primitive undefined ();
	public static unowned Primitive null ();
	public static unowned Boolean true ();
	public static unowned Boolean false ();

	public static void set_flags_from_command_line ([CCode (array_length_pos = 0.9)] ref unowned string[] argv, bool remove_flags);

	[Compact]
	public class TryCatch {
		public TryCatch ();
		public bool has_caught ();
		public unowned Handle exception ();
		public unowned Handle get_message ();
		public void reset ();
		public void set_verbose (bool value);
	}

	[Compact]
	public class ExtensionConfiguration {}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Context : Handle {
		public static unowned Context new (ExtensionConfiguration? extensions, Handle global_template);
		public void dispose ();
		public void enter ();
		public void exit ();
		public unowned Handle global();
		public static unowned Context get_current();
	}
	
	[Compact]
	[CCode (cname = "V8Handle")]
	public class Exception : Handle {
	    public static unowned Handle range_error (String message);
	    public static unowned Handle reference_error (String message);
	    public static unowned Handle syntax_error (String message);
	    public static unowned Handle type_error (String message);
	    public static unowned Handle error (String message);
	    
	    public unowned Handle throw ();
	}
}
