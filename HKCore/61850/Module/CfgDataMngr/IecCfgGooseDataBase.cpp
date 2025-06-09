//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgGooseDataBase.cpp  CIecCfgGooseDataBase


#include "stdafx.h"
#include "IecCfgGooseDataBase.h"

CIecCfgGooseDataBase::CIecCfgGooseDataBase()
{
	//初始化属性
	m_dwVLandPriority = 6;
	m_bTest = 0;
	m_nT0 = 5000;
	m_nT1 = 2;
	m_nT2 = 0;
	m_nT3 = 0;
	m_nTGroup = 0;
	m_strTQuality = _T("0A");
	m_strSrcAddress = _T("00-FF-FF-FF-FF-FF");
	m_strDestAddress = _T("00-FF-FF-FF-FF-FF");
	m_dwAppID = 0x1001;
	m_dwVLandID = 0x101;
	m_dwVersion = 1;
	m_bNdsCom = 0;
	m_nLiveTime = 10000;

	//初始化成员变量
}

CIecCfgGooseDataBase::~CIecCfgGooseDataBase()
{
}

long CIecCfgGooseDataBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDestAddressKey, oNode, m_strDestAddress);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcAddressKey, oNode, m_strSrcAddress);
	xml_GetAttibuteValue(pXmlKeys->m_strAppIDKey, oNode, m_dwAppID);
	xml_GetAttibuteValue(pXmlKeys->m_strPriorityKey, oNode, m_dwVLandPriority);
	xml_GetAttibuteValue(pXmlKeys->m_strVIDKey, oNode, m_dwVLandID);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_dwVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strGooseIdKey, oNode, m_strGooseId);
	xml_GetAttibuteValue(pXmlKeys->m_strDataSetKey, oNode, m_strDataSet);
	xml_GetAttibuteValue(pXmlKeys->m_strDataSetDescKey, oNode, m_strDataSetDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strgocbRefKey, oNode, m_strgocbRef);
	xml_GetAttibuteValue(pXmlKeys->m_strgocbIEDKey, oNode, m_strgocbIED);
	xml_GetAttibuteValue(pXmlKeys->m_strTestKey, oNode, m_bTest);
	xml_GetAttibuteValue(pXmlKeys->m_strT0Key, oNode, m_nT0);
	xml_GetAttibuteValue(pXmlKeys->m_strT1Key, oNode, m_nT1);
	xml_GetAttibuteValue(pXmlKeys->m_strT2Key, oNode, m_nT2);
	xml_GetAttibuteValue(pXmlKeys->m_strT3Key, oNode, m_nT3);
	xml_GetAttibuteValue(pXmlKeys->m_strTGKey, oNode, m_nTGroup);
	xml_GetAttibuteValue(pXmlKeys->m_strTQKey, oNode, m_strTQuality);
	xml_GetAttibuteValue(pXmlKeys->m_strNdsComKey, oNode, m_bNdsCom);
	xml_GetAttibuteValue(pXmlKeys->m_strLiveTimeKey, oNode, m_nLiveTime);

	//T3=2T2=4T1
	m_nT3 = 4 * m_nT1;
	m_nT2 = 2 * m_nT1;

#ifndef _PSX_IDE_QT_
	iecfg_GetCfgDataValueMac(m_strDestAddress, m_byteDestAddress);
	iecfg_GetCfgDataValueMac(m_strSrcAddress, m_byteSrcAddresss);
#endif

	return 0;
}

long CIecCfgGooseDataBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDestAddressKey, oElement, m_strDestAddress);
	xml_SetAttributeValue(pXmlKeys->m_strSrcAddressKey, oElement, m_strSrcAddress);
	xml_SetAttributeValue(pXmlKeys->m_strAppIDKey, oElement, m_dwAppID);
	xml_SetAttributeValue(pXmlKeys->m_strPriorityKey, oElement, m_dwVLandPriority);
	xml_SetAttributeValue(pXmlKeys->m_strVIDKey, oElement, m_dwVLandID);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_dwVersion);
	xml_SetAttributeValue(pXmlKeys->m_strGooseIdKey, oElement, m_strGooseId);
	xml_SetAttributeValue(pXmlKeys->m_strDataSetKey, oElement, m_strDataSet);
	xml_SetAttributeValue(pXmlKeys->m_strDataSetDescKey, oElement, m_strDataSetDesc);
	xml_SetAttributeValue(pXmlKeys->m_strgocbRefKey, oElement, m_strgocbRef);
	xml_SetAttributeValue(pXmlKeys->m_strgocbIEDKey, oElement, m_strgocbIED);
	xml_SetAttributeValue(pXmlKeys->m_strTestKey, oElement, m_bTest);
	xml_SetAttributeValue(pXmlKeys->m_strT0Key, oElement, m_nT0);
	xml_SetAttributeValue(pXmlKeys->m_strT1Key, oElement, m_nT1);
	xml_SetAttributeValue(pXmlKeys->m_strT2Key, oElement, m_nT2);
	xml_SetAttributeValue(pXmlKeys->m_strT3Key, oElement, m_nT3);
	xml_SetAttributeValue(pXmlKeys->m_strTGKey, oElement, m_nTGroup);
	xml_SetAttributeValue(pXmlKeys->m_strTQKey, oElement, m_strTQuality);
	xml_SetAttributeValue(pXmlKeys->m_strNdsComKey, oElement, m_bNdsCom);
	xml_SetAttributeValue(pXmlKeys->m_strLiveTimeKey, oElement, m_nLiveTime);

	return 0;
}

BOOL CIecCfgGooseDataBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgGooseDataBase *p = (CIecCfgGooseDataBase*)pObj;

	if(m_strDestAddress != p->m_strDestAddress)
	{
		return FALSE;
	}

	if(m_strSrcAddress != p->m_strSrcAddress)
	{
		return FALSE;
	}

	if(m_dwAppID != p->m_dwAppID)
	{
		return FALSE;
	}

	if(m_dwVLandPriority != p->m_dwVLandPriority)
	{
		return FALSE;
	}

	if(m_dwVLandID != p->m_dwVLandID)
	{
		return FALSE;
	}

	if(m_dwVersion != p->m_dwVersion)
	{
		return FALSE;
	}

	if(m_strGooseId != p->m_strGooseId)
	{
		return FALSE;
	}

	if(m_strDataSet != p->m_strDataSet)
	{
		return FALSE;
	}

	if(m_strDataSetDesc != p->m_strDataSetDesc)
	{
		return FALSE;
	}

	if(m_strgocbRef != p->m_strgocbRef)
	{
		return FALSE;
	}

	if(m_strgocbIED != p->m_strgocbIED)
	{
		return FALSE;
	}

	if(m_bTest != p->m_bTest)
	{
		return FALSE;
	}

	if(m_nT0 != p->m_nT0)
	{
		return FALSE;
	}

	if(m_nT1 != p->m_nT1)
	{
		return FALSE;
	}

	if(m_nT2 != p->m_nT2)
	{
		return FALSE;
	}

	if(m_nT3 != p->m_nT3)
	{
		return FALSE;
	}

	if(m_nTGroup != p->m_nTGroup)
	{
		return FALSE;
	}

	if(m_strTQuality != p->m_strTQuality)
	{
		return FALSE;
	}

	if(m_bNdsCom != p->m_bNdsCom)
	{
		return FALSE;
	}

	if(m_nLiveTime != p->m_nLiveTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgGooseDataBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataBase::CopyOwn(pDest);

	CIecCfgGooseDataBase *p = (CIecCfgGooseDataBase*)pDest;

	p->m_strDestAddress = m_strDestAddress;
	p->m_strSrcAddress = m_strSrcAddress;
	p->m_dwAppID = m_dwAppID;
	p->m_dwVLandPriority = m_dwVLandPriority;
	p->m_dwVLandID = m_dwVLandID;
	p->m_dwVersion = m_dwVersion;
	p->m_strGooseId = m_strGooseId;
	p->m_strDataSet = m_strDataSet;
	p->m_strDataSetDesc = m_strDataSetDesc;
	p->m_strgocbRef = m_strgocbRef;
	p->m_strgocbIED = m_strgocbIED;
	p->m_bTest = m_bTest;
	p->m_nT0 = m_nT0;
	p->m_nT1 = m_nT1;
	p->m_nT2 = m_nT2;
	p->m_nT3 = m_nT3;
	p->m_nTGroup = m_nTGroup;
	p->m_strTQuality = m_strTQuality;
	p->m_bNdsCom = m_bNdsCom;
	p->m_nLiveTime = m_nLiveTime;
	return TRUE;
}

void CIecCfgGooseDataBase::InitAfterRead()
{
	//SetChannelNum(STGOOSE_CHANNEL_NUM);
}

long CIecCfgGooseDataBase::GetIndex()
{
	CExBaseList *pList = (CExBaseList*)m_pParent;
	return pList->FindIndex(this);
}

void CIecCfgGooseDataBase::SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex)
{
}

BOOL CIecCfgGooseDataBase::OpenCfgDefaultConfigFile()
{
	return CIecCfgDataBase::OpenCfgDefaultConfigFile();
}

#ifdef _PSX_IDE_QT_
BOOL CIecCfgGooseDataBase::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_SetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_SetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
//		ASSERT (vValue.vt == VT_UI4);
		m_dwAppID = vValue;
		return TRUE;
	}

	return CIecCfgDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfgGooseDataBase::GetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
//		vValue.vt = VT_UI4;
		vValue = m_dwAppID;
		return TRUE;
	}

	return CIecCfgDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfgGooseDataBase::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
{
	unsigned long long vCurr;

	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vCurr);
		return (vCurr == vValue);
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vCurr);
		return (vCurr == vValue);
	}

	if (nDataID == CFGDATAID_APPID)
	{
//		ASSERT (vValue.vt == VT_UI4);
		return (vValue == m_dwAppID);
	}

	return CIecCfgDataBase::IsEqualCfgDataValue(nDataID, vValue);
}

#else
BOOL CIecCfgGooseDataBase::SetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_SetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_SetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
		ASSERT (vValue.vt == VT_UI4);
		m_dwAppID = vValue.ulVal;
		return TRUE;
	}

	return CIecCfgDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfgGooseDataBase::GetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
		vValue.vt = VT_UI4;
		vValue.ulVal = m_dwAppID;
		return TRUE;
	}

	return CIecCfgDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfgGooseDataBase::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
{
	VARIANT vCurr;

	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vCurr);
		return (vCurr.ullVal == vValue.ullVal);
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vCurr);
		return (vCurr.ullVal == vValue.ullVal);
	}

	if (nDataID == CFGDATAID_APPID)
	{
		ASSERT (vValue.vt == VT_UI4);
		return (vValue.ulVal == m_dwAppID);
	}

	return CIecCfgDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#endif