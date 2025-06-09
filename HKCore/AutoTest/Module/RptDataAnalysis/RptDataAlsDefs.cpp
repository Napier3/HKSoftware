//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptDataAlsDefs.cpp  CRptDataAlsDefs


#include "stdafx.h"
#include "RptDataAlsDefs.h"

CRptDataAlsDefs::CRptDataAlsDefs()
{
	//初始化属性

	//初始化成员变量
}

CRptDataAlsDefs::~CRptDataAlsDefs()
{
}

long CRptDataAlsDefs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptDataAlsDefs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptDataAlsDefs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CRptDataAlsDefs::InitAfterRead()
{
}

BOOL CRptDataAlsDefs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptDataAlsDefs *p = (CRptDataAlsDefs*)pObj;

	return TRUE;
}

BOOL CRptDataAlsDefs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptDataAlsDefs *p = (CRptDataAlsDefs*)pDest;

	return TRUE;
}

CBaseObject* CRptDataAlsDefs::Clone()
{
	CRptDataAlsDefs *p = new CRptDataAlsDefs();
	Copy(p);
	return p;
}

BOOL CRptDataAlsDefs::CanPaste(UINT nClassID)
{
	if (nClassID == RPTALSCLASSID_CRPTDATAALSDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptDataAlsDefs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptDataAlsDefKey)
	{
		pNew = new CRptDataAlsDef();
	}

	return pNew;
}

CExBaseObject* CRptDataAlsDefs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RPTALSCLASSID_CRPTDATAALSDEF)
	{
		pNew = new CRptDataAlsDef();
	}

	return pNew;
}
