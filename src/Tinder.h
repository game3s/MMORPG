
#ifndef Tinder_h__
#define Tinder_h__

#include <iostream>
#include <sstream>
#include <list>
#include <stdint.h>
#include <stdarg.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <algorithm>
#include <stddef.h>     /* offsetof */


typedef unsigned long ULONG;

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

enum XATTR_TYPE
{
	OAT_I8,
	OAT_I16,
	OAT_I32,  //	OAT_INT,  //含BOOL
	OAT_I64,

	OAT_FLOAT,
	OAT_DOUBLE,

	OAT_U8,
	OAT_U16,
	OAT_U32,
	OAT_U64,

	//块数据
	OAT_STRING,
	OAT_BLOB,

	//容器
	OAT_VECTOR,
	OAT_MAP,

};


class IxEventDelegate
{
public:
	std::string name;

	IxEventDelegate() {};
	virtual ~IxEventDelegate() {};

	virtual void OnCreate(IxObject * sender) {};							//创建的时候初始化
	virtual void OnDestory(IxObject * sender) {};							//销毁的时候

	virtual void OnActive(IxObject * sender) {};							//进入活动 后
	virtual void OnDeactive(IxObject * sender) {};							//进入不活跃状态

	virtual void OnPause(IxObject * sender) {};								//暂停
	virtual void OnResume(IxObject * sender) {};							//重新继续
	virtual void OnDie(IxObject * sender) {};								//死亡
	virtual void OnBrith(IxObject * sender) {};								//出生

	virtual void OnSetPosition(IxObject * sender) {};						//改变位置后 包括方向改变 以及停止

	virtual void OnCombatBefore(IxObject * sender) {};						//进入战斗后
	virtual void OnCombatAfter(IxObject * sender) {};						//离开战斗

	virtual void OnSkillBefore(IxObject * sender, uint32_t) {};				//使用技能前
	virtual void OnSkillAfter(IxObject * sender, uint32_t) {};				//使用技能后

	virtual void OnDamage(IxObject * sender, uint32_t) {};					//受到伤害
	virtual void OnIdle(IxObject * sender) {};								//进入待机状态

	virtual void OnAttribChanged(IxObject * sender, const char* kname) {};	//属性改变
	virtual void OnCollision(IxObject * sender, IxObject* target) {};		//发生碰撞

	virtual void OnChildInc(IxObject * sender, IxObject* child) {};			//子增加
	virtual void OnChildDec(IxObject * sender, IxObject* child) {};			//子减少
	virtual void OnRemoveFromParent(IxObject * sender, IxObject* parent) {};

	virtual void OnTimer(IxObject * sender, int _nId, uint32 _diff) {};		//定时器
	virtual void OnCustomerEvent(IxObject * sender, int nEvent, uint64 p0 = 0, int64 p1 = 0, const void* arg = NULL) {};

	virtual void OnFrameBefore(IxObject * sender) {};	//逻辑帧开始 在场景刷新开始的时候最前调用
	virtual void OnFrameAfter(IxObject * sender) {};	//逻辑帧结束 在场景刷新结束的时候调用

														/**
														执行协议命令
														@return 非零的值 后续将不再执行其他命令解析
														*/
	virtual int OnExecuteCmdline(IxObject * sender, const void* _lpBuf, size_t _size, void* arg)
	{
		return 0;
	};

};

class IxObject
{
public:

	int				ClassID;			//未知 角色 场景 NPC 怪物 物品
	int			    subType;			//标记类型

	int64_t			tag;				//场景内唯一标识

	int				state;				//状态
	int				flags;				//标记
	int				flags2;				//标记

	float		position[3];			//位置 x,y,z
	float		orientation[3];		//方向 x,y,z


	int tile_x, tile_y;					//在虚拟地图那个瓦片上

	int32_t			move_flags;			//移动标记 0停止 
	int32_t			collision_flags;	//碰撞标记
	float			move_speed;			//移动速度


										//基础属性

	uint32_t		exp;
	uint32_t		coin;				//硬币

	uint32_t		hp;					//生命值
										//	uint32_t		hp_max;				//生命最大值 放到逻辑层

	uint32_t		mp;					//蓝值
										//	uint32_t		mp_max;				//蓝值最大 放到逻辑层

	int32_t			atk;				//攻击力
	int32_t			dmg;				//防守

	uint32_t		level;				//级别
	int8_t			camp;				//阵营
	int8_t			career;				//职业

	int8_t			m_active;
	int8_t			m_death;			//标记是否死亡
	int8_t			m_pause;			//标记是否暂停

	int8_t			m_visible;			//是否可见
	int8_t			m_moveable;			//是否可以移动
	int8_t			m_physics;			//是否参加物理 碰撞
	int8_t			m_combat;			//是否战斗单元

	time_t			ti_brith;			//出生时间
	time_t			ti_death;			//死亡时间
	int16_t			ti_relive;			//重生秒数 0 死不了 -1 不重生


	float			m_pursue_r;			//追击半径
	float			m_attack_r;			//攻击半径

	float			m_body[8];	//体型尺寸 用这个来进行碰撞检测

	IxObject*		parent;
//	IxScene*		scn;				//所在的场景

	std::string		name;				//名字
	std::string     script;				//脚本

public:
	virtual bool init() { return true; }
	virtual void clear() {};


	//子 添加 删除 查找
	virtual IxObject* NewChild() { return NULL; };
	virtual void RemoveChild(IxObject*) {};

	virtual void RemoveChildAll() {};
	virtual void ChildAppend(IxObject*) {};

	virtual IxObject* FirstChildByName(const char* _name) { return NULL; };
	virtual IxObject* NextChildByName(const char* _name, IxObject* _start) { return NULL; }
	virtual IxObject* FirstChildByTag(uint64_t _tag) { return NULL; }
	virtual IxObject* NextChildByTag(uint64_t _tag, IxObject* _start) { return NULL; }

	//	virtual IxObject* FirstChildByTag32(uint32_t _tag_prefix) { return NULL; }
	//	IxObject* createChild() { return NULL; }
	//	IxObject* createChildWithInitFromString(std::string strObj) { return NULL; }
	//	virtual IxObject* GetChildAt(size_t idx) { return NULL; };

	//返回子的个数
	virtual size_t GetChildSize() { return 0; };

	//从父亲身上移除
	virtual void RemoveFromParent() {};

	//////////////////////////////////////////////////////////////////////////
#pragma mark ----------------------------

	//事件代理
	virtual void AddEventDelegate(IxEventDelegate* _delegate, int _order = 0) {};
	virtual IxEventDelegate* FindEventDelegateByName(std::string name) { return NULL; }; //返回相等字符串的一个 所以不要相同
	virtual void RemoveEventDelegate(IxEventDelegate* _delegate) {};
	//virtual void EnumEventDelegate(std::vector<IxEventDelegate*>& result) {}
	virtual void RemoveAllEventDelegate() {};

	//////////////////////////////////////////////////////////////////////////

	virtual void Dispatch(int nEvent, uint64 p0 = 0, int64 p1 = 0, const void* arg = NULL) {};
	virtual void OnEvent(int nEvent, uint64 p0 = 0, int64 p1 = 0, const void* arg = NULL) {};

	//////////////////////////////////////////////////////////////////////////

	/**创建定时器 触发器
	@param idx 定时器编号
	@param interval 定时器间隔 毫秒单位
	@param duration 持续多少毫秒 >0 就会自动删除
	*/
	virtual void CreateTimer(int idx, uint32 interval, int duration = -1) {};
	virtual void KillTimer(int idx) {};

	//////////////////////////////////////////////////////////////////////////

	//获得接口的指针
	virtual void* GetPtr(const char* _iName) { return this; };
	inline bool IsClass(int val) { return ClassID == val; }


	//////////////////////////////////////////////////////////////////////////
								 
	virtual void MsgPushBack(const void* _lpBuf, size_t _size, void* arg) { };


public: 
	//2017-05-21 对象属性相关的

		//属性名称支持 :: 进行分割

		/**
		设置对象属性中的元素值
		@param kname 名称 如果父是Vector容器将被忽略
		@param _type 元素类型
		@param v 将要设置值的指针
		@param vsz 将要设置值的数据长度
		@param _parent 挂载在哪个父节点上 如果这个未空就为根节点
		@param _force 如果这个参数为 true  如果此属性不存在就创建
		*/
	virtual void* AttribSet(const char* kname, int _type, const char* v, size_t vsz, void* _parent = NULL, bool _force = true) { return NULL; };
	virtual void* AttribGet(const char* kname, int& _type, void* _parent = NULL) { return NULL; };
	virtual void* AttribGetValue(const char* kname, void* _parent = NULL) { return NULL; };

	virtual bool  AttribRemove(const char* kname, void* _parent = NULL) { return true; };
	virtual void  AttribRemoveAll() {};


	virtual const char* AttribString(const char* kname, void* _parent = NULL) { return NULL; };
	virtual int AttribString(const char* kname, const char* _value,size_t _len,void* _parent = NULL, bool _force = true) { return 1; };

	/**
	* @fn	virtual bool IxObject::AttribIsExist(const char* kname, void* _parent = NULL)
	*
	* @brief	Attribute is exist.
	*
	* @author	Im
	* @date	2017/10/30
	*
	* @param	kname		   	The kname.
	* @param [in,out]	_parent	(Optional) If non-null, the parent.
	*
	* @return	true if it succeeds, false if it fails.
	*/
	virtual bool  AttribIsExist(const char* kname, void* _parent = NULL) { return false; };

	/**
	创建属性树 支持 :: 分割
	*/
	virtual void* AttribMap(const char* kname, void* _parent = NULL, bool _force = true) { return NULL; };


};




#endif // Tinder_h__

