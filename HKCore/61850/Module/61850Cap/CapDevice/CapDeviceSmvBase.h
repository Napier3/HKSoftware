//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceSmvBase.h  CCapDeviceSmvBase

#pragma once

#include "CapDeviceBase.h"
#include "CapDeviceSmvCh.h"

class CCapDeviceSmvBase : public CCapDeviceBase
{
public:
	CCapDeviceSmvBase();
	virtual ~CCapDeviceSmvBase();


	long  m_nSampleRate;
	long  m_nAsduNum;

//���غ���
public:

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceSmvCh();	}

};

