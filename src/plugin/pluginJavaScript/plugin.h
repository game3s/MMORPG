
#ifndef pluginGM_h__
#define pluginGM_h__

#include "GxEngine.h"
#include "GameStruct.h"
#include "Opcodes.h"

#include "include/v8.h"

#include <string>
#include <assert.h>
#include <map>

using namespace v8;


template <class TypeName>
inline v8::Local<TypeName> StrongPersistentToLocal(
	const v8::Persistent<TypeName>& persistent) {
	return *reinterpret_cast<v8::Local<TypeName>*>(
		const_cast<v8::Persistent<TypeName>*>(&persistent));
}

template <class TypeName>
inline v8::Local<TypeName> WeakPersistentToLocal(
	v8::Isolate* isolate,
	const v8::Persistent<TypeName>& persistent) {
	return v8::Local<TypeName>::New(isolate, persistent);
}



template <class TypeName>
inline v8::Local<TypeName> PersistentToLocal(
	v8::Isolate* isolate,
	const v8::Persistent<TypeName>& persistent) {
	if (persistent.IsWeak()) {
		return WeakPersistentToLocal(isolate, persistent);
	}
	else {
		return StrongPersistentToLocal(persistent);
	}
}



class LxMyJavaScript: public IxScript
{
public:
	//static LxMyJavaScript* Instance();
	std::map<std::string, SCRIPT_EX_FUNC> cnt_script_ext_func;

public:
	LxMyJavaScript(v8::Local<v8::Context> context);
	virtual ~LxMyJavaScript();


	virtual int ScriptDoString(const char* _script, IxObject* _sender);


	virtual int ScriptDoFile(const char* _fname, IxObject* _sender);

	//向脚本系统注册 删除 方法

	/**
	 * @fn	virtual int LxMyJavaScript::ScriptProcAdd(void* _p, const char* _name, const char* fmt)
	 *
	 * @brief	向脚本系统注册一个函数
	 *
	 * @author	Im
	 * @date	2017/10/10
	 *
	 * @param [in]	_p   	函数指针.
	 * @param [in]		  	_name	函数名称.
	 * @param [in]		  	fmt  	参数列表 和 printf 一样
	 * @param [in]			ret_fmt 返回值的数据类型 int[%d] string[%s]   
	 *
	 * @return	0成功. <0 错误
	 */
	virtual int  ScriptProcAdd(SCRIPT_EX_FUNC _p, const char* _name);

	/**
	 * @fn	virtual void LxMyJavaScript::ScriptProcDel(void* _p)
	 *
	 * @brief	Script proc delete
	 *
	 * @author	Im
	 * @date	2017/10/10
	 *
	 * @param [in,out]	_p	If non-null, the p.
	 */
	virtual void ScriptProcDel(SCRIPT_EX_FUNC _p);

public:
	static void Init(Local<Context> ctx);

	static inline void MY_SET_METHOD(v8::Local<v8::Object> recv,
		const char* name,
		v8::FunctionCallback callback) 
	{
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		v8::HandleScope handle_scope(isolate);
		v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate,
			callback);
		v8::Local<v8::Function> fn = t->GetFunction();
		v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, name);
		fn->SetName(fn_name);
		recv->Set(fn_name, fn);
	}


	//inline Local<Context> context() const {
	//	return PersistentToLocal(context_.ge, context_);
	//}

	inline Local<Context> context() const;

public:
	//v8
	//v8::Local<v8::Context> context;
	Persistent<Context> context_;
};

void LxV8Init();
void LxV8Free();

void MyScriptHelloWorld();

std::string MsObjPtr(void* p);
void* MsObjPtr(const char* strAddr);


void AddStringToArguments(std::string str, Handle<Value>* argList, unsigned int argPos);
void AddNumberToArguments(double num, Handle<Value>* argList, unsigned int argPos);
void AddIntToArguments(int num, Handle<Value>* argList, unsigned int argPos);
void AddInt64ToArguments(int64 num, Handle<Value>* argList, unsigned int argPos);

Handle<v8::Value> CallJSFunction(Handle<v8::Object> global, std::string funcName, Handle<Value>* argList, unsigned int argCount);


void MyScriptRegister(const char* name,
	v8::FunctionCallback callback);

extern LxMyJavaScript* PtrMyJavaScript;
extern v8::Isolate* isolate;

#define CHECK_EQ(a, b) CHECK((a) == (b))
#define CHECK_GE(a, b) CHECK((a) >= (b))
#define CHECK_GT(a, b) CHECK((a) > (b))
#define CHECK_LE(a, b) CHECK((a) <= (b))
#define CHECK_LT(a, b) CHECK((a) < (b))
#define CHECK_NE(a, b) CHECK((a) != (b))

#define ASSIGN_OR_RETURN_UNWRAP(ptr, obj, ...)                                \
  do {                                                                        \
    *ptr =                                                                    \
        Unwrap<typename std::remove_reference<decltype(**ptr)>::type>(obj);  \
    if (*ptr == nullptr)                                                      \
      return __VA_ARGS__;                                                     \
  } while (0)


template <typename TypeName>
TypeName* Unwrap(v8::Local<v8::Object> object) {
//	CHECK_EQ(false, object.IsEmpty());
//	CHECK_GT(object->InternalFieldCount(), 0);
	void* pointer = object->GetAlignedPointerFromInternalField(0);
	return static_cast<TypeName*>(pointer);
}


/**
脚本响应客户端来的协议请求
*/
void DoClientRequestByScript(uint16_t _msgId, const char * _lpBuf, XULONG _size, void * arg, IxObject* sender);


#endif // pluginTask_h__