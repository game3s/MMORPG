
#include "MyWrap.h"
#include "plugin.h"
#include "MyEventDelegate.h"
#include "MyMethod.h"

#include <string>
#include <fstream>

using namespace std;

//后期加上共享不用每次都建
LxScriptEventDelegate* sharedScriptEventDelegate=NULL;

inline Local<Context> LxScriptEventDelegate::context() const
{
	return PersistentToLocal(isolate, context_);
}

LxScriptEventDelegate::LxScriptEventDelegate(v8::Local<v8::Context> ctx,std::string txtScript)
	:context_(ctx->GetIsolate(), ctx)
{
	v8::Isolate::Scope isolate_scope(isolate);
	v8::HandleScope handle_scope(isolate);

	v8::Context::Scope context_scope(ctx);
	
#if(1)

	Local<v8::String> source = v8::String::NewFromUtf8(isolate, txtScript.c_str(),
			v8::NewStringType::kNormal).ToLocalChecked();

	v8::Local<v8::Script> script = v8::Script::Compile(ctx, source).ToLocalChecked();
	script->Run();


//	v_script = &Persistent<Script>(ctx->GetIsolate(), script);
//	script->Run(ctx).ToLocalChecked();
//	v_script = v8::Script::Compile(ctx, source);

#else
	PtrMyJavaScript->ScriptDoString(txtScript.c_str());

	//Local<Object> _myGlobal = ctx->Global()->Clone();
#endif


}

LxScriptEventDelegate::~LxScriptEventDelegate()
{
	//v_script->Reset();
	context_.Reset();
}

void LxScriptEventDelegate::OnCreate(IxObject * sender)
{
	if (sender->script.empty()) return;
	sender->Retain();
	//throw std::logic_error("The method or operation is not implemented.");

	//调用脚本中的函数
	//sender->script

	string strObj = MsObjPtr(sender);

	/*
	
	function obj_event(strPtr,nEvent,u64,i64) {
	return "Jimmy";
	}
	
	*/
	//Handle<Value> args[4];
	// Call the JS function
	//Handle<Value> js_result = CallJSFunction(global, "JSrepeat", args, 4);
	//String::AsciiValue ascii2(js_result);
	//printf("JSrepeat() returned: %s\n", ascii2);

	//PtrMyJavaScript->ScriptDoString(sender->script.c_str());

	v8::Isolate::Scope isolate_scope(isolate);
	v8::HandleScope handle_scope(isolate);
	//v8::Local<v8::Context> ctx = PtrMyJavaScript->context();// context();
	v8::Local<v8::Context> ctx =  context();
	v8::Context::Scope context_scope(ctx);

	try {
		
		//Local<Script> script = PersistentToLocal<Script>(isolate, *v_script);
		//Local<Script> script = PersistentToLocal(isolate, *v_script);
		
		//Local<Script> script= v_script.ToLocalChecked();
		//script->Run(ctx);
	

		Handle<Value>* args=new Handle<Value>[4];
		AddStringToArguments(strObj, args, 0);
		AddIntToArguments(0, args, 1);
		AddIntToArguments(0, args, 2);
		AddIntToArguments(0, args, 3);

		//Local<Context> ctx = PtrMyJavaScript->context();
		Handle<Value> js_result = CallJSFunction(ctx->Global(), "obj_event", args, 4);
		delete[] args;
	}
	catch (...) {
		GxLOG_ERROR("调用对象脚本事件函数失败");
	}
	sender->Release();
}

void LxScriptEventDelegate::OnTimer(IxObject * sender, int _nId, uint32 _diff)
{
	//throw std::logic_error("The method or operation is not implemented.");
	if (sender->script.empty()) return;

	//throw std::logic_error("The method or operation is not implemented.");

	//调用脚本中的函数
	//sender->script
	sender->Retain();
	string strObj = MsObjPtr(sender);

	/*

	function obj_event(strPtr,nEvent,u64,i64) {
	return "Jimmy";
	}

	*/
	//Handle<Value> args[4];
	// Call the JS function
	//Handle<Value> js_result = CallJSFunction(global, "JSrepeat", args, 4);
	//String::AsciiValue ascii2(js_result);
	//printf("JSrepeat() returned: %s\n", ascii2);

	//PtrMyJavaScript->ScriptDoString(sender->script.c_str());

	//v8::Isolate::Scope isolate_scope(isolate);
	//v8::HandleScope handle_scope(isolate);

	//v8::Local<v8::Context> ctx = PtrMyJavaScript->context();
	//v8::Context::Scope context_scope(ctx);
	//	v8::Local<v8::Context> ctx =context();

	v8::Isolate::Scope isolate_scope(isolate);
	v8::HandleScope handle_scope(isolate);

	v8::Local<v8::Context> ctx = context();
	v8::Context::Scope context_scope(ctx);

	try {
		
//		Local<Script> script = v_script.ToLocalChecked();
//		script->Run(ctx);

#if(1)	
		//v8::Local<v8::String> source =
		//	v8::String::NewFromUtf8(isolate, sender->script.c_str(),
		//		v8::NewStringType::kInternalized)
		//	.ToLocalChecked();
#else
		v8::Local<v8::String> source =
			v8::String::NewFromUtf8(isolate, "xlog(\"hhhhhhhaaaaaaaa.\");",
				v8::NewStringType::kNormal)
			.ToLocalChecked();
#endif

		// Compile the source code.
		//v8::Local<v8::Script> script = v_script.ToLocalChecked();
		//Persistent<Script> sc1(isolate,script);//这是对的

		// Run the script to get the result.
		//v8::Local<v8::Value> result = script->Run(ctx).ToLocalChecked();


		Handle<Value>* args = new Handle<Value>[4];
		AddStringToArguments(strObj, args, 0);
		AddIntToArguments(21, args, 1);
		AddIntToArguments(_nId, args, 2);
		AddIntToArguments(_diff, args, 3);
		

		//Local<Context> ctx = PtrMyJavaScript->context();
		Handle<Value> js_result = CallJSFunction(ctx->Global(), "obj_event", args, 3);
		delete[] args;
	}
	catch (...) {
		GxLOG_ERROR("调用对象脚本事件函数失败");
	}
	sender->Release();
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
int FileContent(std::string fname, std::vector<uint8>& result)
{
	//	std::string str;
#if(1)
	std::ifstream inf(fname.c_str());
	if (!inf.good()) return -1;

	inf.seekg(0, std::ifstream::end);
	size_t l = inf.tellg();
	inf.seekg(0, std::ifstream::beg);
	result.resize(l);
	inf.read((char*)&result[0], l);
	inf.close();
	return 0;
#else
	std::ifstream is(fname.c_str(), std::ifstream::binary);
	if (is) {
		// get length of file:
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		char * buffer = new char[length];

		std::cout << "Reading " << length << " characters... ";
		// read data as a block:
		is.read(buffer, length);

		if (is)
			std::cout << "all characters read successfully.";
		else
			std::cout << "error: only " << is.gcount() << " could be read";
		is.close();

		// ...buffer contains the entire file...
		result.resize(length);
		memcpy(&result[0], buffer, length);
		delete[] buffer;
	}
	return 0;
#endif

}

static int k = 0; //临时

int ObjectEventHandler(IxObject* _sender, int _nEvent, uint64_t _p0, int64_t _p1, const void* arg)
{
	if (_nEvent == EX_CREATE)
	{
		//先临时直接加上去
		std::vector<uint8> sct;
		FileContent("Resource\\script\\character.js",sct);
		if(k>0) FileContent("Resource\\script\\npc202.js", sct);
		k++;

		if (sct.size()) {
			_sender->script.clear();
			_sender->script.append((char*)&sct[0], sct.size());
		}

#if(0)
//		v8::Isolate::Scope isolate_scope(isolate);
//		v8::HandleScope handle_scope(isolate);
//		v8::Local<v8::Context> ctx = Context::New(isolate);
		Local<Context> ctx = PtrMyJavaScript->context();
//		LxMyJavaScript::Init(ctx);
#else

		v8::Isolate::Scope isolate_scope(isolate);
		v8::HandleScope handle_scope(isolate);
		
		v8::Local<v8::Context> ctx = v8::Context::New(isolate);
		v8::Context::Scope context_scope(ctx);

		Handle<v8::Object> global = ctx->Global();
		LxMyJavaScript::MY_SET_METHOD(global, "xlog", MyPrintLine);
		LxMyJavaScript::MY_SET_METHOD(global, "xobj_attrib_set", GxObjAttribSet);
		LxMyJavaScript::MY_SET_METHOD(global, "xobj_timer_create", GxTimerCreate);
		LxMyJavaScript::MY_SET_METHOD(global, "xobj_timer_kill", GxTimerKill);
		LxMyJavaScript::MY_SET_METHOD(global, "XByteBuffer", LxByteBufferWriter::Constructor);
		LxMyJavaScript::MY_SET_METHOD(global, "xnet_send", GxSendToClient);
#endif

		LxScriptEventDelegate* sed = new LxScriptEventDelegate(ctx, _sender->script);
		game_engine->AttribSetMethod(_sender, "LxScriptEventDelegate", sed);
		_sender->AddEventDelegate(sed);
		sed->OnCreate(_sender);
		LxScriptEventDelegate* sed1 = (LxScriptEventDelegate*)game_engine->AttribMethod(_sender, "LxScriptEventDelegate");
		return 0;
	}

	if (_nEvent == EX_CHAR_EXIT_SCENE)
	{
		LxScriptEventDelegate* sed = (LxScriptEventDelegate*)game_engine->AttribMethod(_sender, "LxScriptEventDelegate");
		if (sed) {
			//_sender->RemoveEventDelegate(&sharedScriptEventDelegate);
			_sender->RemoveEventDelegate(sed);
			delete sed;
		}
		return 0;
	}

	return 0;
}
