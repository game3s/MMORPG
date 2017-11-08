#ifndef pluginExt_h__
#define pluginExt_h__


#include <stdint.h>
#include <map>
#include <string>
#include <vector>

typedef unsigned char uchar;

typedef std::vector<uchar> CxDataBuffer;

#include "plugin.h"

/*

脚本文件 每一个都压入内存对象池中
如果要重新装载，需要执行一个命令清空所有装载的部分

*/

extern std::map<uint16_t, std::string> theMsgWorkerCnt;

void MsgWorkerConfigLoadFromXmlFile(std::string fname);



/**

*/
class LxScriptSender
{
public:


public:
	//LxScriptSender(IxObject* obj);

	static void Constructor(const FunctionCallbackInfo<v8::Value>& args);

	//static void SetKeepAlive(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
	IxObject* obj_;
};




class LxByteBufferWriter
{
public:
	std::string strObjPtr;

	ByteBuffer m_bbf;

private:
	v8::Persistent<v8::Object> persistent_handle_;
	v8::Isolate* isolate_;

public:
	LxByteBufferWriter(v8::Isolate* isolate, v8::Local<v8::Object> obj)
		:isolate_(isolate)
		, persistent_handle_(isolate, obj)
	{};

	virtual ~LxByteBufferWriter();


	inline v8::Local<v8::Object> object() {
		return PersistentToLocal(isolate_, persistent_handle_);
	}

	inline v8::Persistent<v8::Object>& persistent() {
		return persistent_handle_;
	}

public:

	static void Constructor(const FunctionCallbackInfo<v8::Value>& args);

	//static void writeI8Callback(Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info);
	//static void writeStringCallback(Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info);

	static void writeStringCallback(const v8::FunctionCallbackInfo<v8::Value>& args);

	static Local<v8::Value> LocalValue(Isolate* isolate);

};


#endif // pluginExt_h__
