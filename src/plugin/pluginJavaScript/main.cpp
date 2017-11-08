
#include "GxEngine.h"
#include "plugin.h"
#include "Opcodes.h"

#include "MyWrap.h"
#include "MyEventDelegate.h"

GxEngine* game_engine = NULL;

static const int v8_default_thread_pool_size = 4;

#define IDS_VERSION "javascript v8 & rs 0.15"

/**
引擎装载插件的时候执行
*/
extern "C"
void plugin_init(GxEngine* _engine)
{
	game_engine = _engine;

//	printf("%s\n",game_engine->version());

	LxV8Init();

	MyScriptHelloWorld();
	IxObject* sender = game_engine->GetServer();
	PtrMyJavaScript->ScriptDoString("xlog('[000000000000]');", sender);

	//开始注册自己的回调函数

	//注册有玩家角色进入此服务器时的动作
	//game_engine->addEventListener(EX_CHAR_ENTER, on_player_enter,NULL);
	//game_engine->addNetMsgHandler(NetMsgHandler, (uint16)XCMSG_GM, 0, 0);

	//game_engine->addEventListener(XEID_APP_STARTUP, cbOnAppStartup);
	//game_engine->addEventListener(XEID_APP_SHUTDOWN, cbOnAppShutdown);

	game_engine->ScriptRegister(PtrMyJavaScript);
//	theMyJavaScript.ScriptDoString("");

	game_engine->addObjectEventListener(CLASSTYPE_SCENE, ObjectEventHandler);
	game_engine->addObjectEventListener(CLASSTYPE_PLAYER, ObjectEventHandler);
	game_engine->addObjectEventListener(CLASSTYPE_NPC, ObjectEventHandler);
	game_engine->addObjectEventListener(CLASSTYPE_HELPER, ObjectEventHandler);

	//处理客户端来的消息协议
	/*
	通过读XML配置来决定执行哪个脚本
	*/
	//game_engine->addNetMsgHandler(CxActor::OnCharacterRename, (uint16)XCMSG_CHAR_RENAME2, 0, 0);

}


/**
引擎释放插件的时候执行
*/
extern "C"
void plugin_free()
{
	//释放回调函数
	//game_engine->removeEventListener(EX_CHAR_ENTER, on_player_enter);
	//game_engine->removeNetMsgHandler(NetMsgHandler);
	game_engine->ScriptRegister(NULL);

	if(PtrMyJavaScript) delete PtrMyJavaScript;

	LxV8Free();
}

//所有插件装载完毕后执行
extern "C"
void plugin_loaded()
{
	//LxMyJavaScript::Instance()->Init();
	GxLOG_INFO("%s",IDS_VERSION);
	
}


