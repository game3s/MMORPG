
#include "MyWrap.h"

using namespace v8;


std::map<uint16_t, std::string> theMsgWorkerCnt;

void MsgWorkerConfigLoadFromXmlFile(std::string fname)
{

}

//LxByteBufferWriter::LxByteBufferWriter()
//{
//	strObjPtr = "LxByteBufferWriter";
////	strObjPtr=MsObjPtr(this);
////	m_bbf.clear();
////	m_bbf.resize(4096);
//}

LxByteBufferWriter::~LxByteBufferWriter()
{
	printf("=======\n[%s]========\n", __FUNCTION__);
}


void LxByteBufferWriter::Constructor(const FunctionCallbackInfo<v8::Value>& args)
{
	//Locker lock;
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope handle_scope(isolate);
	//Handle<ObjectTemplate> t = v8::ObjectTemplate::New();
	Local<ObjectTemplate> t = v8::ObjectTemplate::New(isolate);

	//The JavaScript point object only has 1 C++ object
	t->SetInternalFieldCount(1);

	// Create x and y members with starting values of 0
	//t->Set(String::New("x"), Number::New(0));
	//t->SetAccessor(String::New("x"),
	//	(AccessorGetterCallback)GetPointX,
	//	(AccessorSetterCallback)SetPointX);

	////t->Set(String::New("y"), Number::New(0));
	//t->SetAccessor(String::New("y"),
	//	(AccessorGetterCallback)GetPointY,
	//	(AccessorSetterCallback)SetPointY);

	// Create a mul(number) function that scales the point
//	v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate,writeStringCallback);
//	t->Set(String::NewFromUtf8(isolate,"write_string"), FunctionTemplate::New());
//	LxMyJavaScript::MY_SET_METHOD(t, "write_string", writeStringCallback);

	//Handle<FunctionTemplate> obj = FunctionTemplate::New(isolate);
	t->Set(String::NewFromUtf8(isolate,"write_string"), FunctionTemplate::New(isolate, writeStringCallback));


	// for use in the if statement
	LxByteBufferWriter *p = NULL;
	Local<Object> obj;

		/**
		* Wrap a point object
		*/
	
	//std::string s = MsObjPtr(p);
	//Local<String> pstr= v8::String::NewFromUtf8(isolate, s.c_str(), v8::NewStringType::kNormal).ToLocalChecked();

	obj = t->NewInstance();

	p = new LxByteBufferWriter(isolate,obj);

	obj->SetInternalField(0, External::New(isolate,p));
	//obj->SetInternalField(0, pstr);
	// Return this newly created object
	args.GetReturnValue().Set(obj);

}


#if(0)
void LxByteBufferWriter::writeStringCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	LxByteBufferWriter* bwrite;

	void* ptr = args.Holder()->GetAlignedPointerFromInternalField(0);

	//bwrite=std::remove_reference<LxByteBufferWriter*>(ptr);

	bwrite = static_cast<LxByteBufferWriter*>(ptr);
	//LxByteBufferWriter* bwrite = (LxByteBufferWriter*)(ptr);

	//ASSIGN_OR_RETURN_UNWRAP(&bwrite,args.Holder());

	v8::String::Utf8Value strObj(args[0]);
	std::string s = *strObj;
	
	bwrite->m_bbf.append((const uint8*)s.c_str(),s.length());
	
}
#endif

/*
Local<Object> self = info.Holder();
Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
void* ptr = wrap->Value();
static_cast<Point*>(ptr)->y_ = value->Int32Value();
*/

void LxByteBufferWriter::writeStringCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	LxByteBufferWriter* bwrite;
	Local<Object> self = args.Holder();
	//void* ptr = args.Holder()->GetAlignedPointerFromInternalField(0);
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();
	//bwrite=std::remove_reference<LxByteBufferWriter*>(ptr);

	bwrite = static_cast<LxByteBufferWriter*>(ptr);
	//LxByteBufferWriter* bwrite = (LxByteBufferWriter*)(ptr);

	//ASSIGN_OR_RETURN_UNWRAP(&bwrite,args.Holder());

	v8::String::Utf8Value strObj(args[0]);
	std::string s = *strObj;

	bwrite->m_bbf.append((const uint8*)s.c_str(), s.length());

}



v8::Local<v8::Value> LxByteBufferWriter::LocalValue(Isolate* isolate)
{
	v8::HandleScope handle_scope(isolate);
	Handle<ObjectTemplate> t = v8::ObjectTemplate::New(isolate);
	t->SetInternalFieldCount(1);

	Local<Object> obj = t->NewInstance();

	LxByteBufferWriter *p = new LxByteBufferWriter(isolate, obj);
	p->object()->SetInternalField(0, External::New(isolate, p));

	p->persistent().SetWeak(p, [](const v8::WeakCallbackInfo<LxByteBufferWriter>& data)
	{
		LxByteBufferWriter* _p = data.GetParameter();
		_p->persistent().Reset();
		delete _p;
	}, WeakCallbackType::kParameter);

	return p->object();
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////



void LxScriptSender::Constructor(const FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope handle_scope(isolate);
	Handle<ObjectTemplate> t = v8::ObjectTemplate::New(isolate);

	t->SetInternalFieldCount(1);




}


/*
void TCPWrap::SetKeepAlive(const FunctionCallbackInfo<Value>& args) {
	TCPWrap* wrap;
	ASSIGN_OR_RETURN_UNWRAP(&wrap,
		args.Holder(),
		args.GetReturnValue().Set(UV_EBADF));
	int enable = args[0]->Int32Value();
	unsigned int delay = args[1]->Uint32Value();
	int err = uv_tcp_keepalive(&wrap->handle_, enable, delay);
	args.GetReturnValue().Set(err);
}
*/

