
#ifndef MyScript_h__
#define MyScript_h__


#include "GxEngine.h"
#include "GameStruct.h"
#include "Opcodes.h"

#include "plugin.h"

#include "include/v8.h"

#include <map>
#include <vector>

using namespace v8;

typedef struct gx_method_s
{
	void* p;
	std::string name;
	std::vector<int> arg_fmt;
	int result_type;

}gx_method_t;

extern std::map<std::string, gx_method_t> theNormalProc;

void MyPrintLine(const v8::FunctionCallbackInfo<v8::Value>& args);
void Print(const v8::FunctionCallbackInfo<v8::Value>& args);

/**
设置对象的属性值
*/
void GxObjAttribSet(const v8::FunctionCallbackInfo<v8::Value>& args);

/**
获得对象属性值
@return 如果属性不存在返回 0
        字符串 双精度 数字
*/
void GxObjAttribGet(const v8::FunctionCallbackInfo<v8::Value>& args);

/**
触发事件
*/
void GxObjEventSend(const v8::FunctionCallbackInfo<v8::Value>& args);


/**
发送数据给客户端
*/
void GxSendToClient(const v8::FunctionCallbackInfo<v8::Value>& args);

/**
普通函数
*/
void GxNormalProc(const v8::FunctionCallbackInfo<v8::Value>& args);

/**
创建 删除 定时器
*/
void GxTimerCreate(const v8::FunctionCallbackInfo<v8::Value>& args);
void GxTimerKill(const v8::FunctionCallbackInfo<v8::Value>& args);

/*
把C++的对象作为javascript的内置对象
*/
class MyScriptEngine
{
public:
	//向脚本系统提供日志打印函数
	//static void MyPrintLine(const v8::FunctionCallbackInfo<v8::Value>& args);
};


#endif // MyScript_h__