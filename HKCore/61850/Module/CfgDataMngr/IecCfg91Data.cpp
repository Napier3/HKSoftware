//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData91.cpp  CIecCfgData91


#include "stdafx.h"
#include "IecCfg91Data.h"

CIecCfg91Data::CIecCfg91Data()
{
	//初始化属性
	m_nPriority = 4;
	m_dwVersion = 1;
	m_dwAppID = 0;
	m_dwVID = 0x101;
	m_dwDataSet = 0;
	m_nAsduNum = 1;
	m_dwVersion = 1;
	m_dwLNName = 0;
	m_dwLDName = 0;
	m_nUseStateWord = 0;
	m_dwStateWord = 0;
	m_nUseStateDataSet = 0;
// 	m_dwINomPh = 1200;
// 	m_dwINomNeutral =100;
// 	m_dwUNomPh = 110;
	m_dwDelayTime = 0;

	//初始化成员变量
	m_strSrcAddress = _T("00-FF-FF-FF-FF-FF");
	m_strDestAddress = _T("00-FF-FF-FF-FF-FF");
	//初始化成员变量

	m_pStatusDataSet = NULL;
	m_strID = _T("9-1");
}

CIecCfg91Data::~CIecCfg91Data()
{
}

long CIecCfg91Data::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgSmvDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDestAddressKey, oNode, m_strDestAddress);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcAddressKey, oNode, m_strSrcAddress);
	xml_GetAttibuteValue(pXmlKeys->m_strAppIDKey, oNode, m_dwAppID);
	xml_GetAttibuteValue(pXmlKeys->m_strPriorityKey, oNode, m_nPriority);
	xml_GetAttibuteValue(pXmlKeys->m_strVIDKey, oNode, m_dwVID);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_dwVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strDataSetKey, oNode, m_dwDataSet);
	xml_GetAttibuteValue(pXmlKeys->m_strLNNameKey, oNode, m_dwLNName);
	xml_GetAttibuteValue(pXmlKeys->m_strLDNameKey, oNode, m_dwLDName);
	xml_GetAttibuteValue(pXmlKeys->m_strStateWordKey, oNode, m_dwStateWord);
	xml_GetAttibuteValue(pXmlKeys->m_strStateWordKey, oNode, m_nUseStateWord);
	xml_GetAttibuteValue(pXmlKeys->m_strUseStateDataSetKey, oNode, m_nUseStateDataSet);
// 	xml_GetAttibuteValue(pXmlKeys->m_strINomPhKey, oNode, m_dwINomPh);
// 	xml_GetAttibuteValue(pXmlKeys->m_strINomNeutralKey, oNode, m_dwINomNeutral);
// 	xml_GetAttibuteValue(pXmlKeys->m_strUNomPhKey, oNode, m_dwUNomPh);
	xml_GetAttibuteValue(pXmlKeys->m_strDelayTimeKey, oNode, m_dwDelayTime);

#ifndef _PSX_IDE_QT_
	iecfg_GetCfgDataValueMac(m_strDestAddress, m_byteDestAddress);
	iecfg_GetCfgDataValueMac(m_strSrcAddress, m_byteSrcAddresss);
#endif

	return 0;
}

long CIecCfg91Data::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgSmvDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDestAddressKey, oElement, m_strDestAddress);
	xml_SetAttributeValue(pXmlKeys->m_strSrcAddressKey, oElement, m_strSrcAddress);
	xml_SetAttributeValue(pXmlKeys->m_strAppIDKey, oElement, m_dwAppID);
	xml_SetAttributeValue(pXmlKeys->m_strPriorityKey, oElement, m_nPriority);
	xml_SetAttributeValue(pXmlKeys->m_strVIDKey, oElement, m_dwVID);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_dwVersion);
	xml_SetAttributeValue(pXmlKeys->m_strDataSetKey, oElement, m_dwDataSet);
	xml_SetAttributeValue(pXmlKeys->m_strLNNameKey, oElement, m_dwLNName);
	xml_SetAttributeValue(pXmlKeys->m_strLDNameKey, oElement, m_dwLDName);
	xml_SetAttributeValue(pXmlKeys->m_strStateWordKey, oElement, m_dwStateWord);
	xml_SetAttributeValue(pXmlKeys->m_strStateWordKey, oElement, m_nUseStateWord);
	xml_SetAttributeValue(pXmlKeys->m_strUseStateDataSetKey, oElement, m_nUseStateDataSet);
// 	xml_SetAttributeValue(pXmlKeys->m_strINomPhKey, oElement, m_dwINomPh);
// 	xml_SetAttributeValue(pXmlKeys->m_strINomNeutralKey, oElement, m_dwINomNeutral);
// 	xml_SetAttributeValue(pXmlKeys->m_strUNomPhKey, oElement, m_dwUNomPh);
	xml_SetAttributeValue(pXmlKeys->m_strDelayTimeKey, oElement, m_dwDelayTime);

	return 0;
}

BOOL CIecCfg91Data::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgSmvDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg91Data *p = (CIecCfg91Data*)pObj;

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

	if(m_nPriority != p->m_nPriority)
	{
		return FALSE;
	}

	if(m_dwVID != p->m_dwVID)
	{
		return FALSE;
	}

	if(m_dwVersion != p->m_dwVersion)
	{
		return FALSE;
	}

	if(m_dwDataSet != p->m_dwDataSet)
	{
		return FALSE;
	}

	if(m_dwLNName != p->m_dwLNName)
	{
		return FALSE;
	}

	if(m_dwLDName != p->m_dwLDName)
	{
		return FALSE;
	}

	if(m_dwStateWord != p->m_dwStateWord)
	{
		return FALSE;
	}

	if(m_nUseStateWord != p->m_nUseStateWord)
	{
		return FALSE;
	}

	if(m_nUseStateDataSet != p->m_nUseStateDataSet)
	{
		return FALSE;
	}

// 	if(m_dwINomPh != p->m_dwINomPh)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_dwINomNeutral != p->m_dwINomNeutral)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_dwUNomPh != p->m_dwUNomPh)
// 	{
// 		return FALSE;
// 	}

	if(m_dwDelayTime != p->m_dwDelayTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg91Data::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgSmvDataBase::CopyOwn(pDest);

	CIecCfg91Data *p = (CIecCfg91Data*)pDest;

	p->m_strDestAddress = m_strDestAddress;
	p->m_strSrcAddress = m_strSrcAddress;
	p->m_dwAppID = m_dwAppID;
	p->m_nPriority = m_nPriority;
	p->m_dwVID = m_dwVID;
	p->m_dwVersion = m_dwVersion;
	p->m_dwDataSet = m_dwDataSet;
	p->m_dwLNName = m_dwLNName;
	p->m_dwLDName = m_dwLDName;
	p->m_dwStateWord = m_dwStateWord;
	p->m_nUseStateWord = m_nUseStateWord;
	p->m_nUseStateDataSet = m_nUseStateDataSet;
// 	p->m_dwINomPh = m_dwINomPh;
// 	p->m_dwINomNeutral = m_dwINomNeutral;
// 	p->m_dwUNomPh = m_dwUNomPh;
	p->m_dwDelayTime = m_dwDelayTime;

	return TRUE;
}

CBaseObject* CIecCfg91Data::Clone()
{
	CIecCfg91Data *p = new CIecCfg91Data();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg91Data::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfg91StatusDataSetKey)
	{
		m_pStatusDataSet = new CIecCfg91StatusDataSet();
		pNew = m_pStatusDataSet;
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgChs91Key)
	{
		pNew = new CIecCfg91Chs();
	}


	if (pNew != NULL)
	{
		return pNew;
	}

	return CIecCfgSmvDataBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

void CIecCfg91Data::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHS91);
	CIecCfgSmvDataBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFG91STATUSDATASET)
		{
			m_pStatusDataSet = (CIecCfg91StatusDataSet *)p;
			break;
		}
	}

	GetStatusDataSet();


	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg91Chs();
		AddNewChild(m_pCfgChs);
	}

}

CIecCfg91StatusDataSet* CIecCfg91Data::GetStatusDataSet()
{
	if (m_pStatusDataSet == NULL)
	{
		m_pStatusDataSet = new CIecCfg91StatusDataSet();
		m_pStatusDataSet->InitAfterRead();
		AddNewChild(m_pStatusDataSet);
	}

	return m_pStatusDataSet;
}


#ifdef _PSX_IDE_QT_
BOOL CIecCfg91Data::SetCfgDataValue(long nDataID, unsigned long long &vValue)
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

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfg91Data::GetCfgDataValue(long nDataID, unsigned long long &vValue)
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

	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg91Data::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
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

	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#else
BOOL CIecCfg91Data::SetCfgDataValue(long nDataID, VARIANT &vValue)
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

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfg91Data::GetCfgDataValue(long nDataID, VARIANT &vValue)
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

	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg91Data::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
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

	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#endif

