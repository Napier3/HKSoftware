//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbBuffer.h  CSmDbBuffer

#pragma once

#include "SmFileDBGlobal.h"



class CSmDbBuffer : public CExBaseObject
{
public:
	CSmDbBuffer();
	virtual ~CSmDbBuffer();


//���غ���
public:
	virtual UINT GetClassID() {    return SMDBCLASSID_CSMDBBUFFER;   }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

