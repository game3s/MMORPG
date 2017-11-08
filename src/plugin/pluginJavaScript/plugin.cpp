
#include "plugin.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
//#include <fstream>

#include "Opcodes.h"
#include "ByteBuffer.h"
#include "GxEngine.h"

#include "include/libplatform/libplatform.h"
#include "include/v8.h"
//#include "include/libplatform/libplatform-export.h"

//#include "util-inl.h"

#include "default-platform.h"

#include "MyWrap.h"
#include "MyMethod.h"

extern GxEngine* game_engine;

LxMyJavaScript* PtrMyJavaScript =NULL;

v8::Isolate* isolate = NULL;



v8::Platform* app_platform = NULL;

using namespace v8;


void LxV8Init()
{
	const char* proc_file_name = game_engine->GetExecuteFilename();
	v8::V8::InitializeICUDefaultLocation(proc_file_name);
	v8::V8::InitializeExternalStartupData(proc_file_name);
	
	app_platform = v8::platform::CreateDefaultPlatform();
	v8::V8::InitializePlatform(app_platform);
	v8::V8::Initialize();

	// Create a new Isolate and make it the current one.
	v8::Isolate::CreateParams create_params;
	//create_params.array_buffer_allocator = &allocator;
	create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
	isolate = v8::Isolate::New(create_params);

	if (isolate == NULL)
	{
		GxLOG_ERROR("javascript error!");
		exit(0);
	}


	//注册函数
	//Handle<ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
	//global->Set(v8::String::NewFromUtf8(isolate, "xlog"), v8::FunctionTemplate::New(isolate, MyPrintLine));

	//v8::Local<v8::Context> context=v8::Context::New(isolate);
	//v8::Persistent<v8::Context> pc = context;

	//v8::Local<v8::Context> context = v8::Context::New(isolate);
	//PtrMyJavaScript = new LxMyJavaScript(context);
	//PtrMyJavaScript->Init();

}



void LxV8Free()
{
	if(isolate) isolate->Dispose();
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
	if(app_platform) delete app_platform;

	isolate = NULL;
	app_platform = NULL;

}


void AddStringToArguments(std::string str, Handle<Value>* argList, unsigned int argPos) 
{
	argList[argPos] = String::NewFromUtf8(isolate,str.c_str());
}

void AddNumberToArguments(double num, Handle<Value>* argList, unsigned int argPos)
{
	argList[argPos] = v8::Number::New(isolate,num);
}

void AddIntToArguments(int num, Handle<Value>* argList, unsigned int argPos)
{
	argList[argPos] = v8::Int32::New(isolate, num);
}

void AddInt64ToArguments(int64 num, Handle<Value>* argList, unsigned int argPos)
{
	argList[argPos] = v8::Integer::New(isolate, num);
}

//void AddBooleanToArguments(bool value, Handle<Value> argList[], unsigned int argPos) 
//{
//	argList[argPos] = v8::Boolean::New(value);
//}

Handle<v8::Value> CallJSFunction(Handle<v8::Object> global, std::string funcName, Handle<Value>* argList, unsigned int argCount)
{
	// Create value for the return of the JS function
	Handle<Value> js_result;
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	// Grab JS function out of file
	Handle<v8::Value> value = global->Get(String::NewFromUtf8(isolate, funcName.c_str()));
	// Cast value to v8::Function
	Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
	// Call function with all set values
	js_result = func->Call(global, argCount, argList);
	// Return value from function
	return js_result;
}

void MyScriptRegister(const char* name,
	v8::FunctionCallback callback)
{
	assert(name);

	v8::Isolate::Scope isolate_scope(isolate);
	v8::HandleScope handle_scope(isolate);
	v8::Local<v8::Context> ctx = PtrMyJavaScript->context();
	v8::Context::Scope context_scope(ctx);
	

	//LxMyJavaScript::MY_SET_METHOD(ctx->Global(), "ByteBuffer", LxByteBufferWriter::Constructor);
	LxMyJavaScript::MY_SET_METHOD(ctx->Global(), name, callback);

}


void MyScriptHelloWorld()
{
	if (isolate)
	{

		v8::Isolate::Scope isolate_scope(isolate);
		v8::HandleScope handle_scope(isolate);
		v8::Local<v8::Context> context = v8::Context::New(isolate);
		v8::Context::Scope context_scope(context);


		if (PtrMyJavaScript == NULL) {
			HandleScope handle_scope(isolate);
			v8::Local<v8::Context> context = Context::New(isolate);
			Context::Scope context_scope(context);
			PtrMyJavaScript = new LxMyJavaScript(context);
			LxMyJavaScript::Init(context);
		}

		// Create a string containing the JavaScript source code.
		v8::Local<v8::String> source =
			v8::String::NewFromUtf8(isolate, "'JavaScript:  Hello' + ', World!'",
				v8::NewStringType::kNormal)
			.ToLocalChecked();

		// Compile the source code.
		v8::Local<v8::Script> script =
			v8::Script::Compile(context, source).ToLocalChecked();

		// Run the script to get the result.
		v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

		// Convert the result to an UTF8 string and print it.
		//v8::String::Utf8Value utf8(isolate, result);
		//printf("%s\n", *utf8);
		v8::String::Utf8Value utf8(result);
		//printf("%s\n", *utf8);
		GxLOG_WARNING("%s\n", *utf8);
	}
}


void* MsObjPtr(const char* strAddr)
{
	if (strAddr==NULL) return NULL;
	uint64_t p = std::strtoull(strAddr, NULL, 10);
	return (void*)(p);
}

std::string MsObjPtr(void* p)
{
	char buf[256];
	memset(buf, 0, 256);
	snprintf(buf, 256, "%llu", (uint64_t)p);
	return std::string(buf);
}


v8::Handle<String> ReadFile(const char* name)
{
	//Open the file
	FILE* file;
	fopen_s(&file, name, "rb");

	//If there is no file, return an empty string
	if (file == NULL) return v8::Handle<v8::String>();

	//Set the pointer to the end of the file
	fseek(file, 0, SEEK_END);

	//Get the size of file
	int size = ftell(file);

	//Rewind the pointer to the beginning of the stream
	rewind(file);

	//Set up and read into the buffer
	char* chars = new char[size + 1];
	chars[size] = '\0';
	for (int i = 0; i < size;)
	{
		int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
		i += read;
	}

	//Close file
	fclose(file);

	std::string str;
	str.append(chars, size);
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::Handle<v8::String> result = v8::String::NewFromUtf8(isolate, str.c_str());
	delete[] chars;
	return result;
}



//LxMyJavaScript* LxMyJavaScript::Instance()
//{
//	if (PtrMyJavaScript == NULL) {
//		//Local<Context> ctx = v8::Context::New(isolate);
//		v8::Local<v8::Context> context = v8::Context::New(isolate);
//		PtrMyJavaScript = new LxMyJavaScript(context);
//	}
//	return PtrMyJavaScript;
//}


/*

#include <v8.h> 
 
using namespace v8; 
 
int main(int argc, char *argv[]) { 
    // 创建一个句柄作用域 ( 在栈上 ) 
    HandleScope handle_scope; 
 
    // 创建一个新的上下文对象
    Persistent<Context> context = Context::New(); 
 
    // 进入上一步创建的上下文，用于编译执行 helloworld 
    Context::Scope context_scope(context); 
 
    // 创建一个字符串对象，值为'Hello, Wrold!', 字符串对象被 JS 引擎
    // 求值后，结果为'Hello, World!'
    Handle<String> source = String::New("'Hello' + ', World!'"); 
 
    // 编译字符串对象为脚本对象
    Handle<Script> script = Script::Compile(source); 
 
    // 执行脚本，获取结果
    Handle <Value> result = script->Run(); 
 
    // 释放上下文资源
    context.Dispose(); 
 
    // 转换结果为字符串
    String::AsciiValue ascii(result); 
 
    printf("%s\n", *ascii); 
 
    return 0; 
}

*/

LxMyJavaScript::LxMyJavaScript(v8::Local<v8::Context> context)
	:context_(context->GetIsolate(),context)
{

	// 创建一个新的上下文对象
	//Persistent<Context> context = Context::New();
	// 进入上一步创建的上下文，用于编译执行 helloworld 
	//Context::Scope context_scope(context);
	//v8::V8::InitializeICU();
	//isolate = v8::Isolate::GetCurrent();
	//isolate->Enter();
	//handle_scope = new HandleScope(isolate);

	//Local<Context> ctx = Context::New(isolate);
}

LxMyJavaScript::~LxMyJavaScript()
{
	context_.Reset();
}


//static const char* ToCString(const v8::String::Utf8Value& value) {
//	return *value ? *value : "";
//}

int LxMyJavaScript::ScriptDoString(const char* _script, IxObject* _sender)
{

	if (isolate == NULL || _script == NULL) return -1;

	v8::Isolate::Scope isolate_scope(isolate);

	// Create a stack-allocated handle scope.
	v8::HandleScope handle_scope(isolate);


	if (PtrMyJavaScript == NULL) {
		v8::Local<v8::Context> context = Context::New(isolate);
		PtrMyJavaScript = new LxMyJavaScript(context);
		LxMyJavaScript::Init(PtrMyJavaScript->context());
	}

	//v8::Local<v8::Context> context=Context::New(isolate);
	v8::Local<v8::Context> ctx = context();

	// Enter the context for compiling and running the hello world script.
	v8::Context::Scope context_scope(ctx);


	//Handle<v8::Object> global = context->Global();
	//MY_SET_METHOD(global, "xlog", MyPrintLine);

	// 使用以下方式注册user对象到全局范围
	//context->Global()->Set(String::New("user"), userObject);
	{
	Local<v8::String> objName =v8::String::NewFromUtf8(isolate, "sender",v8::NewStringType::kNormal).ToLocalChecked();

	Local<ObjectTemplate> t = v8::ObjectTemplate::New(isolate);
	t->SetInternalFieldCount(1);
	Local<Object> obj=t->NewInstance();
	obj->SetInternalField(0, External::New(isolate, _sender));

	ctx->Global()->Set(objName,obj);
	}


	try {
	// Create a string containing the JavaScript source code.
#if(1)	
	v8::Local<v8::String> source =
		v8::String::NewFromUtf8(isolate, _script,
			v8::NewStringType::kNormal)
		.ToLocalChecked();
#else
	v8::Local<v8::String> source =
		v8::String::NewFromUtf8(isolate, "xlog(\"hhhhhhhaaaaaaaa.\");",
			v8::NewStringType::kNormal)
		.ToLocalChecked();
#endif
	
		// Compile the source code.
		v8::Local<v8::Script> script =
			v8::Script::Compile(ctx, source).ToLocalChecked();

		//Persistent<Script> sc1(isolate,script);//这是对的

		// Run the script to get the result.
		script->Run(ctx);
		//v8::Local<v8::Value> result = script->Run(ctx).ToLocalChecked();
	}
	catch (...) {
		GxLOG_ERROR("javascript error\n\n%s\n\n", _script);
	}
	// Convert the result to an UTF8 string and print it.
	//v8::String::Utf8Value utf8(isolate, result);
	//printf("%s\n", *utf8);
	//v8::String::Utf8Value utf8(result);
	//GxLOG_INFO("%s\n", *utf8);

	return 0;
}

//还未测试
int LxMyJavaScript::ScriptDoFile(const char* _fname, IxObject* _sender)
{

	if (isolate == NULL || _fname == NULL) return -1;

	v8::Isolate::Scope isolate_scope(isolate);

	// Create a stack-allocated handle scope.
	v8::HandleScope handle_scope(isolate);

	// Create a new context.
	v8::Local<v8::Context> context = v8::Context::New(isolate);

	// Enter the context for compiling and running the hello world script.
	v8::Context::Scope context_scope(context);

	Local<ObjectTemplate> global = v8::ObjectTemplate::New(isolate);

	Handle<v8::Object> global2 = context->Global();
	
	//注册变量
	{
		v8::Local<v8::String> objName =
			v8::String::NewFromUtf8(isolate, "sender",
				v8::NewStringType::kNormal)
			.ToLocalChecked();

		Local<ObjectTemplate> t = v8::ObjectTemplate::New(isolate);
		t->SetInternalFieldCount(1);
		Local<Object> obj = t->NewInstance();
		obj->SetInternalField(0, External::New(isolate, _sender));

		context->Global()->Set(objName, obj);
	}
	
	Handle<String> source1 = ReadFile(_fname);



	v8::Local<v8::Script> script = v8::Script::Compile(context, source1).ToLocalChecked();

	script->Run();

	return 0;
}

int LxMyJavaScript::ScriptProcAdd(SCRIPT_EX_FUNC _p, const char* _name)
{
	assert(_p && _name);
	//script_ex_func_t ex_func;
	//ex_func.p = _p;
	//memset(ex_func.fmt, 0, 4096);
	//memset(ex_func.ret_fmt, 0, 256);
	//if(fmt) snprintf(ex_func.fmt, 4096, "%s", fmt);
	//if (ret_fmt) snprintf(ex_func.ret_fmt, 256, "%s", ret_fmt);

	cnt_script_ext_func.insert(std::pair<std::string, SCRIPT_EX_FUNC>(_name, _p));
	return 0;
}



void LxMyJavaScript::ScriptProcDel(SCRIPT_EX_FUNC _p)
{
	for (auto it = cnt_script_ext_func.begin(); it != cnt_script_ext_func.end();)
	{
		//script_ex_func_t ex_func=it->second;
		if (it->second == _p) {
			it = cnt_script_ext_func.erase(it);
		}
		else it++;
	}
}

void LxMyJavaScript::Init(Local<Context> ctx)
{
	//context = v8::Context::New(isolate);
	//Handle<v8::Object> global = context->Global();
	//MY_SET_METHOD(global, "xlog", MyPrintLine);

//	Local<Context> ctx = context();
	Handle<v8::Object> global = ctx->Global();
	MY_SET_METHOD(global, "xlog", MyPrintLine);

	MY_SET_METHOD(global, "xobj_attrib_set", GxObjAttribSet);
	MY_SET_METHOD(global, "xobj_attrib_get", GxObjAttribGet);

	MY_SET_METHOD(global, "xobj_timer_create", GxTimerCreate);
	MY_SET_METHOD(global, "xobj_timer_kill", GxTimerKill);
	MY_SET_METHOD(global, "xnet_send", GxSendToClient);

//	MY_SET_METHOD(global, "XByteBuffer", LxByteBufferWriter::Constructor);
	MY_SET_METHOD(global, "xg_proc", GxNormalProc);

}

v8::Local<v8::Context> LxMyJavaScript::context() const
{
	return PersistentToLocal(isolate, context_);
}



#pragma mark ----

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void DoClientRequestByScript(uint16_t _msgId, const char * _lpBuf, XULONG _size, void * arg, IxObject* sender)
{

}


