//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDevice92.h  CCapDevice92

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

class CCapDevice92 : public CCapDeviceSmvBase
{
public:
	CCapDevice92();
	virtual ~CCapDevice92();


	CString m_strSVID;
	long m_nConfRev;
	long m_nSmpSynch;
	
//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE92;};

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

};

