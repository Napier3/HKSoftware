//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_RpeortDef.cpp  CRptTemp_RpeortDef


#include "stdafx.h"
#include "RptTemp_RpeortDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ReportDef::CRptTemp_ReportDef()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CRptTemp_ReportDef::~CRptTemp_ReportDef()
{
}

long CRptTemp_ReportDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CRptTemp_ReportDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

long CRptTemp_ReportDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
	}
	return 0;
}

void CRptTemp_ReportDef::InitAfterRead()
{
}

BOOL CRptTemp_ReportDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_ReportDef *p = (CRptTemp_ReportDef*)pObj;

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_ReportDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_ReportDef *p = (CRptTemp_ReportDef*)pDest;

	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CRptTemp_ReportDef::Clone()
{
	CRptTemp_ReportDef *p = new CRptTemp_ReportDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ReportDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ReportDef *p = new CRptTemp_ReportDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_ReportDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_VALUEDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_ReportDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ValueDefKey)
	{
		pNew = new CRptTemp_ValueDef();
	}

	return pNew;
}

CExBaseObject* CRptTemp_ReportDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_VALUEDEF)
	{
		pNew = new CRptTemp_ValueDef();
	}

	return pNew;
}
