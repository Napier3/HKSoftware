//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceChBase.cpp  CCapDeviceChBase


#include "stdafx.h"
#include "CapDeviceChBase.h"

CCapDeviceChBase::CCapDeviceChBase()
{
	//��ʼ������
	m_nSelect = 1;
	m_nChType = 0;
	m_nLength = 0;

	//��ʼ����Ա����
	m_pCapRecord = NULL;
}

CCapDeviceChBase::~CCapDeviceChBase()
{
}
