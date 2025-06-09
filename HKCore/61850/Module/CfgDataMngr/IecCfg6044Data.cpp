//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData6044.cpp  CIecCfgData6044


#include "stdafx.h"
#include "IecCfg6044Data.h"

CIecCfg6044Data::CIecCfg6044Data()
{
	//初始化属性
	m_dwLDName = 0;
	m_dwLNName = 0;
	m_dwDataSetName = 0;
	m_dwDelayTime = 0;
	m_dwTransSpeed = 0;
	m_dwStateWord = 0;
// 	m_dwINomPh = 1200;
// 	m_dwINomNeutral =100;
// 	m_dwUNomPh = 110;

	//初始化成员变量
	m_strID = _T("IEC60044-8(FT3)");
	m_nCheckSum = 0;
	m_nPolarity = 0;



}

CIecCfg6044Data::~CIecCfg6044Data()
{
}

long CIecCfg6044Data::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgSmvDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLDNameKey, oNode, m_dwLDName);
	xml_GetAttibuteValue(pXmlKeys->m_strLNNameKey, oNode, m_dwLNName);
	xml_GetAttibuteValue(pXmlKeys->m_strDataSetNameKey, oNode, m_dwDataSetName);
	xml_GetAttibuteValue(pXmlKeys->m_strDelayTimeKey, oNode, m_dwDelayTime);
	xml_GetAttibuteValue(pXmlKeys->m_strTransSpeedKey, oNode, m_dwTransSpeed);
	xml_GetAttibuteValue(pXmlKeys->m_strStateWordKey, oNode, m_dwStateWord);
// 	xml_GetAttibuteValue(pXmlKeys->m_strINomPhKey, oNode, m_dwINomPh);
// 	xml_GetAttibuteValue(pXmlKeys->m_strINomNeutralKey, oNode, m_dwINomNeutral);
// 	xml_GetAttibuteValue(pXmlKeys->m_strUNomPhKey, oNode, m_dwUNomPh);

	xml_GetAttibuteValue(pXmlKeys->m_strChecksumKey, oNode, m_nCheckSum);
	xml_GetAttibuteValue(pXmlKeys->m_strPolarityKey, oNode, m_nPolarity);

	m_nCheckSum = GetChecksum();
	m_nPolarity = GetPolarity();

	return 0;
}

long CIecCfg6044Data::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgSmvDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLDNameKey, oElement, m_dwLDName);
	xml_SetAttributeValue(pXmlKeys->m_strLNNameKey, oElement, m_dwLNName);
	xml_SetAttributeValue(pXmlKeys->m_strDataSetNameKey, oElement, m_dwDataSetName);
	xml_SetAttributeValue(pXmlKeys->m_strDelayTimeKey, oElement, m_dwDelayTime);
	xml_SetAttributeValue(pXmlKeys->m_strTransSpeedKey, oElement, m_dwTransSpeed);
	xml_SetAttributeValue(pXmlKeys->m_strStateWordKey, oElement, m_dwStateWord);
// 	xml_SetAttributeValue(pXmlKeys->m_strINomPhKey, oElement, m_dwINomPh);
// 	xml_SetAttributeValue(pXmlKeys->m_strINomNeutralKey, oElement, m_dwINomNeutral);
// 	xml_SetAttributeValue(pXmlKeys->m_strUNomPhKey, oElement, m_dwUNomPh);
	xml_SetAttributeValue(pXmlKeys->m_strChecksumKey, oElement, m_nCheckSum);
	xml_SetAttributeValue(pXmlKeys->m_strPolarityKey, oElement, m_nPolarity);
	return 0;
}

BOOL CIecCfg6044Data::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgSmvDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg6044Data *p = (CIecCfg6044Data*)pObj;

	if(m_dwLDName != p->m_dwLDName)
	{
		return FALSE;
	}

	if(m_dwLNName != p->m_dwLNName)
	{
		return FALSE;
	}

	if(m_dwDataSetName != p->m_dwDataSetName)
	{
		return FALSE;
	}

	if(m_dwDelayTime != p->m_dwDelayTime)
	{
		return FALSE;
	}

	if(m_dwTransSpeed != p->m_dwTransSpeed)
	{
		return FALSE;
	}

	if(m_dwStateWord != p->m_dwStateWord)
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

	return TRUE;
}

BOOL CIecCfg6044Data::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgSmvDataBase::CopyOwn(pDest);

	CIecCfg6044Data *p = (CIecCfg6044Data*)pDest;

	p->m_dwLDName = m_dwLDName;
	p->m_dwLNName = m_dwLNName;
	p->m_dwDataSetName = m_dwDataSetName;
	p->m_dwDelayTime = m_dwDelayTime;
	p->m_dwTransSpeed = m_dwTransSpeed;
	p->m_dwStateWord = m_dwStateWord;
// 	p->m_dwINomPh = m_dwINomPh;
// 	p->m_dwINomNeutral = m_dwINomNeutral;
// 	p->m_dwUNomPh = m_dwUNomPh;
	p->m_nCheckSum = m_nCheckSum;
	p->m_nPolarity = m_nPolarity;
	return TRUE;
}

CBaseObject* CIecCfg6044Data::Clone()
{
	CIecCfg6044Data *p = new CIecCfg6044Data();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg6044Data::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChs6044Key)
	{
		pNew = new CIecCfg6044Chs();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	return CIecCfgSmvDataBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg6044Data::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHS6044);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg6044Chs();
		AddNewChild(m_pCfgChs);
	}

	CIecCfgSmvDataBase::InitAfterRead();
}


#ifdef _PSX_IDE_QT_
BOOL CIecCfg6044Data::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
//		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue;
		m_nFiberIndex = m_nFiberIndex % GetAppFiberCount();

		return TRUE;
	}

	if (nDataID == CFGDATAID_CHCECKSUM)
	{
//		if (vValue.vt == VT_UI4)
		{
			m_nCheckSum = vValue;
		}
// 		else if (vValue.vt == VT_R4)
// 		{
// 			m_nCheckSum = (long)vValue.fltVal;
// 		}

		m_nCheckSum = m_nCheckSum % 2;

		return TRUE;
	}

	if (nDataID == CFGDATAID_POLARITY)
	{
//		if (vValue.vt == VT_UI4)
		{
			m_nPolarity = vValue;
		}
// 		else if (vValue.vt == VT_R4)
// 		{
// 			m_nPolarity = (long)vValue.fltVal;
// 		}

		m_nPolarity = m_nPolarity % 2;

		return TRUE;
	}

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfg6044Data::GetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg6044Data::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
{
	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}

#else
BOOL CIecCfg6044Data::SetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue.ulVal;
		m_nFiberIndex = m_nFiberIndex % GetAppFiberCount();

		return TRUE;
	}

	if (nDataID == CFGDATAID_CHCECKSUM)
	{
		if (vValue.vt == VT_UI4)
		{
			m_nCheckSum = vValue.ulVal;
		}
		else if (vValue.vt == VT_R4)
		{
			m_nCheckSum = (long)vValue.fltVal;
		}

		m_nCheckSum = m_nCheckSum % 2;

		return TRUE;
	}

	if (nDataID == CFGDATAID_POLARITY)
	{
		if (vValue.vt == VT_UI4)
		{
			m_nPolarity = vValue.ulVal;
		}
		else if (vValue.vt == VT_R4)
		{
			m_nPolarity = (long)vValue.fltVal;
		}

		m_nPolarity = m_nPolarity % 2;

		return TRUE;
	}

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfg6044Data::GetCfgDataValue(long nDataID, VARIANT &vValue)
{
	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg6044Data::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
{
	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#endif
