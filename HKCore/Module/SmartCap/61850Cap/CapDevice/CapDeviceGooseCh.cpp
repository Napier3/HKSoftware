//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceGooseCh.cpp  CCapDeviceGooseCh


#include "stdafx.h"
#include "CapDeviceGooseCh.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDataGooseChBase.h"

CCapDeviceGooseCh::CCapDeviceGooseCh()
{
	//初始化属性
	m_nChType = CAPDEVICE_CHTYPE_B;

	//初始化成员变量
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
	case 0x83://单点
		strDataType = g_strGooseChType_Single;
		break;
	case 0x84://双点

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
	case 0x85://枚举
		strDataType = g_strGooseChType_Integer;
		break;
	case 0x86://UINT
		strDataType = g_strGooseChType_UInteger;
		break;
	case 0x91://时间
		strDataType = g_strGooseChType_Time;
		break;
	case 0x87://浮点
		strDataType = g_strGooseChType_Float;
		break;
	case 0xA2://结构体
		strDataType = g_strGooseChType_Struct;
		break;
	default:
		strDataType = g_strGooseChType_Single;
		break;
	}

	return strDataType;
}