//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptDataAlsDefsMngr.cpp  CRptDataAlsDefsMngr


#include "stdafx.h"
#include "RptDataAlsDefsMngr.h"

CRptDataAlsDefsMngr::CRptDataAlsDefsMngr()
{
	//初始化属性

	//初始化成员变量
}

CRptDataAlsDefsMngr::~CRptDataAlsDefsMngr()
{
	m_listAllItem.RemoveAll();
}

void CRptDataAlsDefsMngr::FreeRptDataAlsDefsMngr()
{
	DeleteAll();
	m_listAllItem.RemoveAll();
}

long CRptDataAlsDefsMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptDataAlsDefsMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptDataAlsDefsMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptDataAlsDefsMngr::InitAfterRead()
{
	GetAllDataAlsDef(m_listAllItem);
}

BOOL CRptDataAlsDefsMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptDataAlsDefsMngr *p = (CRptDataAlsDefsMngr*)pObj;

	return TRUE;
}

BOOL CRptDataAlsDefsMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptDataAlsDefsMngr *p = (CRptDataAlsDefsMngr*)pDest;

	return TRUE;
}

CBaseObject* CRptDataAlsDefsMngr::Clone()
{
	CRptDataAlsDefsMngr *p = new CRptDataAlsDefsMngr();
	Copy(p);
	return p;
}

BOOL CRptDataAlsDefsMngr::CanPaste(UINT nClassID)
{
	if (nClassID == RPTALSCLASSID_CRPTDATAALSDEFS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptDataAlsDefsMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRptAnalysisXmlRWKeys *pXmlKeys = (CRptAnalysisXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptDataAlsDefsKey)
	{
		pNew = new CRptDataAlsDefs();
	}

	return pNew;
}

CExBaseObject* CRptDataAlsDefsMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RPTALSCLASSID_CRPTDATAALSDEFS)
	{
		pNew = new CRptDataAlsDefs();
	}

	return pNew;
}

long CRptDataAlsDefsMngr::GetAllDataAlsDef(CExBaseList &listDataDef)
{
	POS pos = GetHeadPosition();
	CRptDataAlsDefs *pDefs = NULL;

	while (pos != NULL)
	{
		pDefs  = (CRptDataAlsDefs *)GetNext(pos);
		listDataDef.Append(pDefs);
	}

	return listDataDef.GetCount();
}

