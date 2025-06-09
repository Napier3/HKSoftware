//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgPrimRates.cpp  CIecCfgPrimRates


#include "stdafx.h"
#include "IecCfgPrimRates.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecCfgPrimRates::CIecCfgPrimRates()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgPrimRates::~CIecCfgPrimRates()
{
}

long CIecCfgPrimRates::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgPrimRates::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgPrimRates::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CIecCfgPrimRates::InitAfterRead()
{
}

BOOL CIecCfgPrimRates::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgPrimRates *p = (CIecCfgPrimRates*)pObj;

	return TRUE;
}

BOOL CIecCfgPrimRates::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgPrimRates *p = (CIecCfgPrimRates*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgPrimRates::Clone()
{
	CIecCfgPrimRates *p = new CIecCfgPrimRates();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgPrimRates::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecCfgPrimRates *p = new CIecCfgPrimRates();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecCfgPrimRates::CanPaste(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFGPRIMRATE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecCfgPrimRates::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgPrimRateKey)
	{
		pNew = new CIecCfgPrimRate();
	}

	return pNew;
}

CExBaseObject* CIecCfgPrimRates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGPRIMRATE)
	{
		pNew = new CIecCfgPrimRate();
	}

	return pNew;
}

void CIecCfgPrimRates::InitCommon(long nCT_RateNum,long nPT_RateNum)
{
	CString strID;
	CIecCfgPrimRate *pPrimRate = NULL;
	int nIndex = 0;

	for (nIndex = 0;nIndex<nPT_RateNum;nIndex++)
	{
		strID.Format(_T("U%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate*)FindByID(strID);

		if (pPrimRate == NULL)
		{
			pPrimRate = new CIecCfgPrimRate;
			pPrimRate->m_strID = strID;
			pPrimRate->m_strName = strID;
			pPrimRate->m_fPrimValue = 220;
			pPrimRate->m_fSecondValue = 100;
			AddNewChild(pPrimRate);
		}
	}

	for (nIndex = nPT_RateNum;nIndex<m_nCount;nIndex++)
	{
		strID.Format(_T("U%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate*)FindByID(strID);

		if (pPrimRate != NULL)
		{
			Delete(pPrimRate);
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	for (nIndex = 0;nIndex<nCT_RateNum;nIndex++)
	{
		strID.Format(_T("I%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate*)FindByID(strID);

		if (pPrimRate == NULL)
		{
			pPrimRate = new CIecCfgPrimRate;
			pPrimRate->m_strID = strID;
			pPrimRate->m_strName = strID;
			pPrimRate->m_fPrimValue = 1000;
			pPrimRate->m_fSecondValue = 1;
			AddNewChild(pPrimRate);
		}
	}

	for (nIndex = nCT_RateNum;nIndex<m_nCount;nIndex++)
	{
		strID.Format(_T("I%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate*)FindByID(strID);

		if (pPrimRate != NULL)
		{
			Delete(pPrimRate);
		}
	}
}
