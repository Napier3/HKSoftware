//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbBaseObject.h  CSmDbBaseObject

#pragma once

#include "SmFileDBGlobal.h"
#include "..\ShareMem\ShareMemServerEx.h"
#include "..\ShareMem\ShareMemClientEx.h"


class CSmDbBaseObject : public CBaseObject
{
public:
	CSmDbBaseObject();
	virtual ~CSmDbBaseObject();


//���غ���
public:
	virtual long SmRead(CShareMemClientEx &oSm)	{	SmReadOwn(oSm);	SmReadChildren(oSm);	InitAfterRead();	return 0;	}
	virtual long SmReadOwn(CShareMemClientEx &oSm)	{	return 0;	}
	virtual long SmReadChildren(CShareMemClientEx &oSm)	{	return 0;	}

	virtual long SmWrite(CShareMemClientEx &oSm)	{	SmWriteOwn(oSm);	SmWriteChildren(oSm);	return 0;	}
	virtual long SmWriteOwn(CShareMemClientEx &oSm)	{	return 0;	}
	virtual long SmWriteChildren(CShareMemClientEx &oSm)	{	return 0;	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

