//Ep101Frame_10.h  
#ifndef _Ep101Frame_10_H__
#define _Ep101Frame_10_H__

#include "Ep101FrameBase.h"

/*
******固定帧长格式
	启动字符（10H）
	控制域（C）
	链路地址域（A）
	帧校验和（CS）
	结束字符（16H）
*/


class CEp101Frame_10 : public CEp101FrameBase
{
public:
	CEp101Frame_10(void);
	~CEp101Frame_10(void);
	
#define EP_101_FRAME_10_POS_CONTROL  1
#define EP_101_FRAME_10_POS_LINKADDR     2
#define EP_101_FRAME_10_POS_SUM_CHK      3
#define EP_101_FRAME_10_POS_END      4
#define EP_101_FRAME_10_LENGTH       5

// 属性
public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_10;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_Ep101Frame_10_H__