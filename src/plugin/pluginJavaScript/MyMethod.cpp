
#include "MyWrap.h"
#include "MyMethod.h"

#include <string>
#include <stdio.h>

using namespace  std;

std::map<std::string, gx_method_t> theNormalProc;

void MyPrintLine(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	
	if (args.Length() < 1) return;

	v8::String::Utf8Value str(args[0]);
	int level = 3;
	if (args.Length() > 1) {
		level = args[1]->Int32Value();
	}
	printf("++[%d]+++++[%s]+++++\n",(int)time(NULL),*str);
	//std::string buf(*str);
	//game_engine->log2(level, "%s", *str);
	//GxLOG_LINE(level, "%s",*str);
}


/*
* JS Function: print(string, ...)
* /a string value to be printed
*/
void Print(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::cout << "Print worked= ";

	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope(args.GetIsolate());
		v8::String::Utf8Value str(args[i]);
		std::string myStr = *(str);
		const char* cstr = myStr.c_str();
		printf("%s", cstr);
	}
	printf("\n", NULL);
}


/*

js

  gx_obj_attrib('23123','hp',1213);

*/
void GxObjAttribSet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set((int)-1);

	if (args.Length() < 3) return;
	if (!args[0]->IsObject())
	{
		GxLOG_ERROR("------第1个参数不是对象-------");
		return;
	}

//	v8::String::Utf8Value strObj(args[0]);
	v8::String::Utf8Value strName(args[1]);
	std::string kName = *strName;

	GxLOG_WARNING("------脚本调用属性[%s]设置-------",kName.c_str());

	Local<Object> self = args[0]->ToObject();
	//void* ptr = args.Holder()->GetAlignedPointerFromInternalField(0);
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();

//	IxObject* obj = (IxObject*)MsObjPtr(*strObj);
//	if (obj == NULL) return;
	IxObject* obj = (IxObject*)wrap->Value();


	if (args[2]->IsString())
	{
		v8::String::Utf8Value strValue(args[2]);
		std::string kValue=*strValue;
		game_engine->AttribSetValueString(obj, kName, kValue);
		goto L1;
		args.GetReturnValue().Set((int)0);
		return;
	}
	else if(args[2]->IsInt32())
	{
		int64_t vz = args[2]->Int32Value();
		game_engine->AttribSetValueNumber(obj, kName, vz);
		goto L1;
	}
	else if (args[2]->IsNumber())
	{
		//MaybeLocal<Number> num = args[2]->ToNumber();
		double vz =  args[2]->NumberValue();
		game_engine->AttribSetValueDouble(obj, kName, vz);
		goto L1;
	}

	//args[2]->IntegerValue();
	
	//TODO 针对基础的一些属性进行转接设定 //FIXME


L1:

#ifdef _DEBUG
	int hp = game_engine->AttribInt32(obj, "hp");
	GxLOG_INFO("hp:%d", hp);
#endif

	args.GetReturnValue().Set((int)0);

}


void GxObjAttribGet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	args.GetReturnValue().Set((int)0);

	if (args.Length() < 2) return;
	if (!args[0]->IsObject())
	{
		GxLOG_ERROR("------第1个参数不是对象-------");
		return;
	}

	v8::String::Utf8Value strName(args[1]);

	std::string kName = *strName; //属性名称
	if (kName.empty()) return;

	Local<Object> self = args[0]->ToObject();
	//void* ptr = args.Holder()->GetAlignedPointerFromInternalField(0);
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();

	//	IxObject* obj = (IxObject*)MsObjPtr(*strObj);
	//	if (obj == NULL) return;
	IxObject* obj = (IxObject*)wrap->Value();

	if (obj == NULL) return;



	int t =game_engine->AttribType(obj, kName.c_str());

	//字符串 数字 浮点数 
	if (t == OAT_STRING)
	{
		string str;
		game_engine->AttribGetValueString(obj, kName, str);
		v8::Local<v8::String> source =
			v8::String::NewFromUtf8(isolate, str.c_str(),
				v8::NewStringType::kNormal)
			.ToLocalChecked();
		args.GetReturnValue().Set<v8::String>(source);
	}

	switch (t)
	{
	case OAT_I8:
	case OAT_I16:
	case OAT_I32:
	case OAT_U8:
	case OAT_U16:
	case OAT_U32:
	case OAT_I64:
	{
		int64_t k64 = 0;
		int k = game_engine->AttribGetValueNumber(obj, kName, k64);
		k = (int)k64;
		args.GetReturnValue().Set((int)k);
		break;
	}
	case OAT_U64:
	case OAT_FLOAT:
	case OAT_DOUBLE:
	{
		double d = 0;
		game_engine->AttribGetValueDouble(obj, kName, d);
		args.GetReturnValue().Set((double)d);
		break;
	}
	default:
		break;
	}


}


/*

Handle<String> js_data = String::New("pt");
Handle<Value> js_data_value = pContext->Global()->Get(js_data);
Handle<Object> js_data_object = Handle<Object>::Cast(js_data_value);
Handle<Value> key = String::New("x");
Handle<Value> objX = js_data_object->Get(key);
*/

void GxObjEventSend(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::String::Utf8Value strObj(args[0]);
	IxObject* obj = (IxObject*)MsObjPtr(*strObj);
	//v8::ArrayBuffer buff(args[1]->Cast());
	//Local<v8::Object> obj(args[1]->ToObject());

}

char* DataArrayBufferView(Local<Value> val) {
//	CHECK(val->IsArrayBufferView());
	Local<ArrayBufferView> ui = val.As<ArrayBufferView>();
	ArrayBuffer::Contents ab_c = ui->Buffer()->GetContents();
	return static_cast<char*>(ab_c.Data()) + ui->ByteOffset();
}


void GxSendToClient(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;

	if (!args[0]->IsObject())
	{
		GxLOG_ERROR("------第1个参数不是对象-------");
		return;
	}


	Local<Object> obj = args[0]->ToObject();
	Local<External> wrap = Local<External>::Cast(obj->GetInternalField(0));
	IxObject* xobj =(IxObject*) wrap->Value();

	if (args[1]->IsArrayBuffer())
	{
		Isolate *isolate = args.GetIsolate();
		Local<ArrayBuffer> arr = args[0].As<ArrayBuffer>();
		//ArrayBuffer::Contents ab_c = arr->GetContents();

		const char* ptr = static_cast<char*>(arr->GetContents().Data());// DataArrayBufferView(args[0]);
		size_t sz = arr->ByteLength();
		
		game_engine->sendToEx(xobj, ptr, sz);

		//Local<Object> obj = args[0]->ToObject();
		//Local<External> wrap = Local<External>::Cast(obj->GetInternalField(0));
		//void* ptr = wrap->Value();
		//v8::String::Utf8Value strValue(args[0]);
		//LxByteBufferWriter* bwrite = static_cast<LxByteBufferWriter*>(ptr);
		//printf("ArrayBuffer: '%s', %zu\n", *strValue, strValue.length());
		//string str;
		//bwrite->m_bbf >> str;
		//printf("[===]\n" );
		args.GetReturnValue().Set((int)0);
		return;
	}else
	args.GetReturnValue().Set((int)-1);
}

void GxSendToClientEx(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	if (args[0]->IsObject()) 
	{
		Local<Object> obj = args[0]->ToObject();
		Local<External> wrap = Local<External>::Cast(obj->GetInternalField(0));
		void* ptr = wrap->Value();

		LxByteBufferWriter* bwrite = static_cast<LxByteBufferWriter*>(ptr);

		string str;

		bwrite->m_bbf >> str;

		printf("[%s]\n", str.c_str());
	}
}

void GxNormalProc(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::String::Utf8Value strName(args[0]);
	std::string procName = *strName;

	//根据名字获得函数指针
	auto it = PtrMyJavaScript->cnt_script_ext_func.find(procName);
	if (it != PtrMyJavaScript->cnt_script_ext_func.end())
	{
		//script_ex_func_t ex_func = it->second;
		//根据配置情况解析参数
		IxScriptArgs myArgs;
		for (int i = 1; i < args.Length(); i++)
		{
			IxScriptArg _arg;
			if (args[i]->IsString())
			{
				_arg.type = SAT_STRING;
				v8::String::Utf8Value strU8(args[i]);
				std::string str = *strU8;
				_arg.write(str.c_str(), str.length());
			}

			if (args[i]->IsNumber())
			{
				_arg.type = SAT_DOUBLE;
				double d = args[i]->NumberValue();
				_arg.write(&d, sizeof(double));
			}

			if (args[i]->IsInt32())
			{
				_arg.type = SAT_INT;
				int k = args[i]->Int32Value();
				_arg.write(&k, sizeof(int));
			}

			myArgs.args.push_back(_arg);
		}

		(it->second)(myArgs);
		
		if (myArgs.returnValue.type == SAT_STRING)
		{
			v8::Local<v8::String> source =
				v8::String::NewFromUtf8(isolate, myArgs.returnValue.content(),
					v8::NewStringType::kNormal)
				.ToLocalChecked();
			args.GetReturnValue().Set<v8::String>(source);
		}
		else if (myArgs.returnValue.type == SAT_DOUBLE)
		{
			double* d = (double*)myArgs.returnValue.content();
			args.GetReturnValue().Set((double)*d);
		}
		else if (myArgs.returnValue.type == SAT_INT)
		{
			int* k=(int*)myArgs.returnValue.content();
			args.GetReturnValue().Set((int)*k);
		}

		//根据返回值写入到内容
		//args.GetReturnValue().Set((int)0);
	}
	else {
		args.GetReturnValue().Set((int)0);
	}
}

void GxTimerCreate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	//谁
	//时间ID
	//时间间隙
	//生存周期
	if (args.Length() < 3) return;
	v8::String::Utf8Value strObj(args[0]);
	IxObject* obj = (IxObject*)MsObjPtr(*strObj);

	int32 id = args[1]->Int32Value();
	int32 interval= args[2]->Int32Value();
	int64_t d = 0;
	if (args.Length() < 3) d = args[3]->IntegerValue();

	if (obj) obj->CreateTimer(id, interval, d);

}

void GxTimerKill(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::String::Utf8Value strObj(args[0]);
	IxObject* obj = (IxObject*)MsObjPtr(*strObj);

	int32 id = args[1]->Int32Value();
	if (obj) obj->KillTimer(id);
}

