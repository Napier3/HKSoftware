//Ep104Frame_68.h  
#ifndef _Ep104Frame_68_H__
#define _Ep104Frame_68_H__

#include "Ep104FrameBase.h"

/*
*********�ɱ�֡����ʽ
	�����ַ���68H��
	���ȣ�L��
	������C��
	��·��ַ��A��
	��·�û����ݣ��ɱ䳤�ȣ�
	֡У��ͣ�CS��
	�����ַ���16H��
*/

#define EP_104_FRAME_68_POS_LENGTH  1
#define EP_104_FRAME_68_POS_CONTROL  2
#define EP_104_FRAME_68_POS_LINKADDR     3

class CEp104Frame_68_Head : public CEp104FrameBase
{
public:
	CEp104Frame_68_Head();
	virtual ~CEp104Frame_68_Head();

//����
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

//����
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