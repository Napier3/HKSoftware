//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecFiberConfig.h  CIecFiberConfig

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

class CIecFiberCh : public CExBaseObject
{
public:
	CIecFiberCh();
	virtual ~CIecFiberCh();
	
	long m_nIndex;
	long m_nState;   //״̬��������ʹ�á�����ʹ��
	long m_nUseCount;   //ʹ�ü�����
};

class CIecFiberConfig : public CExBaseList
{
public:
	CIecFiberConfig();
	virtual ~CIecFiberConfig();


//���غ���
public:
	void InitFiberConfig(long nFiberCount);
	void InitFt3Config(long nFiberCount);
	void InitFiberConfig(long nAppType, long nAppVersion);
	
	
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

 
