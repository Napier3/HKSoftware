//Ep104Frame_68.h  
#ifndef _Ep104Frame_68_H__
#define _Ep104Frame_68_H__

#include "Ep104FrameBase.h"

/*
*********可变帧长格式
	启动字符（68H）
	长度（L）
	控制域（C）
	链路地址域（A）
	链路用户数据（可变长度）
	帧校验和（CS）
	结束字符（16H）
*/

#define EP_104_FRAME_68_POS_LENGTH  1
#define EP_104_FRAME_68_POS_CONTROL  2
#define EP_104_FRAME_68_POS_LINKADDR     3

class CEp104Frame_68_Head : public CEp104FrameBase
{
public:
	CEp104Frame_68_Head();
	virtual ~CEp104Frame_68_Head();

//属性
public:
	
public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_10;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


class CEp104Frame_68_Tail : public CEp104FrameBase
{
public:
	CEp104Frame_68_Tail();
	virtual ~CEp104Frame_68_Tail();

//属性
public:
	
public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_10;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};

#endif //_Ep104Frame_68_H__