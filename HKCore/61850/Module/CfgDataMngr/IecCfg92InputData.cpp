//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData92.cpp  CIecCfgData92


#include "stdafx.h"
#include "IecCfg92InputData.h"
#include "IecCfg92ChIn.h"
#include "IecCfg92ChsIn.h"

CIecCfg92InputData::CIecCfg92InputData()
{

}

CIecCfg92InputData::~CIecCfg92InputData()
{
}

long CIecCfg92InputData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CIecCfgSmvDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSVIDKey, oNode, m_strSVID);


	return 0;
}
long CIecCfg92InputData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CIecCfgSmvDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

//	xml_SetAttributeValue(pXmlKeys->m_strSVIDKey, oElement, m_strSVID);

	return 0;
}

BOOL CIecCfg92InputData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg92InputData *p = (CIecCfg92InputData*)pObj;

	if(m_strSVID != p->m_strSVID)
	{
		return FALSE;
	}

	if(m_nSyn != p->m_nSyn)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg92InputData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataBase::CopyOwn(pDest);

	CIecCfg92InputData *p = (CIecCfg92InputData*)pDest;

	p->m_strSVID = m_strSVID;


	return TRUE;
}

CBaseObject* CIecCfg92InputData::Clone()
{
	CIecCfg92InputData *p = new CIecCfg92InputData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg92InputData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChs92InKey)
	{
		pNew = new CIecCfg92ChsIn();
		
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	return pNew;//CIecCfgSmvDataBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg92InputData::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHS92IN);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg92ChsIn();//  CIecCfg92InputData
		AddNewChild(m_pCfgChs);
	}

	CIecCfgDataBase::InitAfterRead();
}


void CIecCfg92InputData::GetQualityList(CIecCfg92ChQualityList *pList)
{
	ASSERT (pList != NULL);
	ASSERT (m_pCfgChs != NULL);

	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfg92ChIn *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg92ChIn *)m_pCfgChs->GetNext(pos);

		if (pCh->GetClassID() == CFGCLASSID_CIECCFG92CHIN)
		{
			CIecCfg92ChQuality *pNew = new CIecCfg92ChQuality();
			pNew->SetQualityRef(&pCh->m_nQuality);
			pList->AddTail(pNew);
		}
	}

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg92ChsIn();
		AddNewChild(m_pCfgChs);
	}
}

#ifdef _PSX_IDE_QT_
BOOL CIecCfg92InputData::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	return CIecCfgDataBase::SetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg92InputData::GetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	return CIecCfgDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg92InputData::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
{
	unsigned long long vCurr;
	return CIecCfgDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#else
BOOL CIecCfg92InputData::SetCfgDataValue(long nDataID, VARIANT &vValue)
{
	return CIecCfgDataBase::SetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg92InputData::GetCfgDataValue(long nDataID, VARIANT &vValue)
{
	return CIecCfgDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg92InputData::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
{
	VARIANT vCurr;
	return CIecCfgDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#endif

BOOL CIecCfg92InputData::OpenCfgDefaultConfigFile()
{
	CString strFile;
	CIecCfgDataBase::GetCfgDefaultConfigFile(strFile);

	BOOL b = OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	if (!b)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("config file [%s] is not exist"), strFile.GetString());
		InitAfterRead();
		SetChannelNum(12);
	}

	return b;
}
