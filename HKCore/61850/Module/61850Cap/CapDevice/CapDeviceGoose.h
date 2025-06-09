//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceGoose.h  CCapDeviceGoose

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"
#include "CapDeviceGooseCh.h"

class CCapDeviceGoose : public CCapDeviceBase
{
public:
	CCapDeviceGoose();
	virtual ~CCapDeviceGoose();

	long  m_dwVID;
	long  m_dwVersion;
	CString  m_strGooseId;
	CString  m_strDataSet;
	CString  m_strDataSetDesc;
	CString  m_strgocbRef;
	CString  m_strgocbIED;
	long  m_nTest;
	long  m_dwTimeAllowToAlive;
	long m_dwStNum;
	long m_dwSqNum;
	long m_dwNdsCom;
	double m_dTime;
	
//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICEGOOSE;};

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceGooseCh();	}

};

