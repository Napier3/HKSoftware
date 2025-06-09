//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceGooseCh.cpp  CCapDeviceGooseCh


#include "stdafx.h"
#include "CapDeviceGooseCh.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDataGooseChBase.h"

CCapDeviceGooseCh::CCapDeviceGooseCh()
{
	//��ʼ������
	m_nChType = CAPDEVICE_CHTYPE_B;

	//��ʼ����Ա����
}

CCapDeviceGooseCh::~CCapDeviceGooseCh()
{
}

void CCapDeviceGooseCh::InitChannel(CIecCfgDataChBase *pIecCfgDataCh)
{
	ASSERT(pIecCfgDataCh != NULL);

	if(pIecCfgDataCh == NULL)
	{
		return;
	}

	CCapDeviceChBase::InitChannel(pIecCfgDataCh);
	CIecCfgDataGooseChBase* pGooseCh = (CIecCfgDataGooseChBase*)pIecCfgDataCh;

	m_strChTypeName = pGooseCh->m_strDataTypeName;
}

void CCapDeviceGooseCh::InitChannel(CDvmData *pChData)
{
	InitChTypeName();
	CCapDeviceChBase::InitChannel(pChData);
}

void CCapDeviceGooseCh::InitChannelAttrs(CDvmData *pChData)
{
	pChData->m_strDataType = m_strChTypeName;
}

void CCapDeviceGooseCh::UpdateChTypeAndLength(WORD wChType,WORD wLength)
{
	if ((m_nChType != wChType)||(m_nLength!= wLength))
	{
		m_nLength = wLength;
		m_nChType = wChType;
		m_strChTypeName = st_GetGooseChType(wChType,wLength);

		if (m_pRefDvmData != NULL)
		{
			CDvmData *pData = (CDvmData *)m_pRefDvmData;
			pData->m_strDataType = m_strChTypeName;
		}
	}
}

CString CCapDeviceGooseCh::GetIecCfgChDataType()
{
	CString strDataType;
	strDataType = g_strGooseChType_Single;
	switch (m_nChType)
	{
	case 0x83://����
		strDataType = g_strGooseChType_Single;
		break;
	case 0x84://˫��

		if (m_nLength == 2)
		{
			strDataType = g_strGooseChType_Double;
		}
		else if (m_nLength == 3)
		{
			strDataType = g_strGooseChType_Quality;
		}
		else
		{
			strDataType = g_strGooseChType_String;
		}
		break;
	case 0x85://ö��
		strDataType = g_strGooseChType_Integer;
		break;
	case 0x86://UINT
		strDataType = g_strGooseChType_UInteger;
		break;
	case 0x91://ʱ��
		strDataType = g_strGooseChType_Time;
		break;
	case 0x87://����
		strDataType = g_strGooseChType_Float;
		break;
	case 0xA2://�ṹ��
		strDataType = g_strGooseChType_Struct;
		break;
	default:
		strDataType = g_strGooseChType_Single;
		break;
	}

	return strDataType;
}