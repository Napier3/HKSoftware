//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDevice91.h  CCapDevice91

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

class CCapDevice91 : public CCapDeviceSmvBase
{
public:
	CCapDevice91();
	virtual ~CCapDevice91();


//	long  m_nPriority;
	DWORD  m_dwVID;
	DWORD  m_dwVersion;
	DWORD  m_dwDataSet;
	DWORD  m_dwLNName;
	DWORD  m_dwLDName;

	DWORD  m_dwINomPh;
	DWORD  m_dwUNomPh;
	DWORD  m_dwINomNeutral;
	DWORD  m_dwDelayTime;
	
	DWORD  m_dwStateWord;
	DWORD  m_dwSmpCnt;
	
//���غ���
public:
	//��������
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE91;};

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

