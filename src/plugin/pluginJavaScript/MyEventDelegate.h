#ifndef ObjScript_h__
#define ObjScript_h__


#include "GxEngine.h"
#include "GameStruct.h"
#include "Opcodes.h"

#include "plugin.h"

class LxScriptEventDelegate : public IxEventDelegate
{
public:
	Persistent<Context> context_;

/*
	v8::MaybeLocal<Script> v_script;
	//v8::Isolate::Scope v_scope;
	v8::MaybeLocal<v8::String> v_source;
	v8::Context::Scope v_scope;
*/
	inline Local<Context> context() const;

//	v8::MaybeLocal<Script> v_script;

	LxScriptEventDelegate(v8::Local<v8::Context> ctx, std::string txtScript);
	~LxScriptEventDelegate();

	virtual void OnCreate(IxObject * sender) override;

	virtual void OnTimer(IxObject * sender, int _nId, uint32 _diff) override;

};

int ObjectEventHandler(IxObject* _sender, int _nEvent, uint64_t _p0, int64_t _p1, const void* arg);


/**
提供给脚本使用的
*/
class LxObject
{
public:
	IxObject* real;

};

/*

支持的数据类型 字符串 int(4) int8(1) int16(2) int64(8) float(4) 

*/





#endif // pluginTask_h__