//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbBaseList.h  CSmDbBaseList

#pragma once

#include "SmDbBaseObject.h"
#include "..\BaseClass\BaseList.h"

class CSmDbBaseList : public CBaseList
{
public:
	CSmDbBaseList();
	virtual ~CSmDbBaseList();


//���غ���
public:
	virtual long SmReadChildren(CShareMemClientEx &oSm);
	virtual long SmWriteChildren(CShareMemClientEx &oSm);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

