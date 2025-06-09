//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgPrimRates.cpp  CIecCfgPrimRatesIn


#include "stdafx.h"
#include "IecCfgPrimRatesIn.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecCfgPrimRatesIn::CIecCfgPrimRatesIn()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgPrimRatesIn::~CIecCfgPrimRatesIn()
{
}

long CIecCfgPrimRatesIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgPrimRatesIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgPrimRatesIn::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecCfgPrimRatesIn::InitAfterRead()
{
}

BOOL CIecCfgPrimRatesIn::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgPrimRatesIn *p = (CIecCfgPrimRatesIn*)pObj;

	return TRUE;
}

BOOL CIecCfgPrimRatesIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgPrimRatesIn *p = (CIecCfgPrimRatesIn*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgPrimRatesIn::Clone()
{
	CIecCfgPrimRatesIn *p = new CIecCfgPrimRatesIn();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgPrimRatesIn::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecCfgPrimRatesIn *p = new CIecCfgPrimRatesIn();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecCfgPrimRatesIn::CanPaste(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFGPRIMRATE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecCfgPrimRatesIn::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgPrimRateKey)
	{
		pNew = new CIecCfgPrimRate();
	}

	return pNew;
}

CExBaseObject* CIecCfgPrimRatesIn::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGPRIMRATE)
	{
		pNew = new CIecCfgPrimRate();
	}

	return pNew;
}

