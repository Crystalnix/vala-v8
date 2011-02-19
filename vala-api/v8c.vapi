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

	public static Handle undefined ();

	[Compact]
	public class HandleScope {
		public HandleScope ();
		public void free ();
	}

	[Compact]
	public class StringUtf8Value {
		public StringUtf8Value (Handle handle);
		public int length ();
		public unowned string chars ();
		public void free ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Template : Handle {

	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class FunctionTemplate : Template {
		public FunctionTemplate (InvocationCallback call_back);
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class ObjectTemplate : Template {
		public ObjectTemplate ();
		[CCode (cname = "v8_template_set")]
		public void template_set (Handle name, Handle value);
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Context : Handle {
		public Context (ExtensionConfiguration? extensions, Handle global_template);
		public void dispose ();
		public void enter ();
		public void exit ();
	}

	[Compact]
	[CCode (cname = "V8Handle")]
	public class Script : Handle {
		public static Script compile (Handle source);
		public Handle run ();
	}

	public static Handle string_new_utf8 (string data, int length);

	public class Arguments {
		public int length ();
		[CCode (cname = "v8_arguments_get")]
		public Handle get_i (int i);
	}

	[CCode (has_target = false)]
	public delegate Handle InvocationCallback (Arguments args);

	public class ExtensionConfiguration {}
}
