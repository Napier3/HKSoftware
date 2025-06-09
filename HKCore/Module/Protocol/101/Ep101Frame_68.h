//Ep101Frame_68.h  
#ifndef _Ep101Frame_68_H__
#define _Ep101Frame_68_H__

#include "Ep101FrameBase.h"

/*
*********�ɱ�֡����ʽ
	�����ַ���68H��
	���ȣ�L��
	�����ظ���L��    ---------  ����L���������򡢵�ַ���û����������ֽ���
	�����ַ���68H��
	������C��
	��·��ַ��A��
	��·�û����ݣ��ɱ䳤�ȣ�
	֡У��ͣ�CS��
	�����ַ���16H��
*/

#define EP_101_FRAME_68_POS_LENGTH1  1
#define EP_101_FRAME_68_POS_LENGTH2  2
#define EP_101_FRAME_68_POS_START2   3
#define EP_101_FRAME_68_POS_CONTROL  4
#define EP_101_FRAME_68_POS_LINKADDR     5

class CEp101Frame_68_Head : public CEp101FrameBase
{
public:
	CEp101Frame_68_Head();
	virtual ~CEp101Frame_68_Head();

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


class CEp101Frame_68_Tail : public CEp101FrameBase
{
public:
	CEp101Frame_68_Tail();
	virtual ~CEp101Frame_68_Tail();

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

#endif //_Ep101Frame_68_H__