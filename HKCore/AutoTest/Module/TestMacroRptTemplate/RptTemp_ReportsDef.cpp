//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ReportsDef.cpp  CRptTemp_ReportsDef


#include "stdafx.h"
#include "RptTemp_ReportsDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ReportsDef::CRptTemp_ReportsDef()
{
	//初始化属性

	//初始化成员变量
	m_pRpeortDef = NULL;
}

CRptTemp_ReportsDef::~CRptTemp_ReportsDef()
{
}

long CRptTemp_ReportsDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strData_PathKey, oNode, m_strData_Path);
	return 0;
}

long CRptTemp_ReportsDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;
	//xml_SetAttributeValue(pXmlKeys->m_strData_PathKey, oElement, m_strData_Path);

	return 0;
}

long CRptTemp_ReportsDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Path);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strData_Path);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strData_Path);
	}
	return 0;
}

void CRptTemp_ReportsDef::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
		{
			m_pRpeortDef = (CRptTemp_ReportDef*)p;
		}
	}

	if (m_pRpeortDef == NULL)
	{
		m_pRpeortDef = (CRptTemp_ReportDef*)AddNewChild(new CRptTemp_ReportDef());
	}

}

BOOL CRptTemp_ReportsDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_ReportsDef *p = (CRptTemp_ReportsDef*)pObj;

	if(m_strData_Path != p->m_strData_Path)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_ReportsDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_ReportsDef *p = (CRptTemp_ReportsDef*)pDest;
	p->m_strData_Path = m_strData_Path;

	return TRUE;
}

CBaseObject* CRptTemp_ReportsDef::Clone()
{
	CRptTemp_ReportsDef *p = new CRptTemp_ReportsDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ReportsDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ReportsDef *p = new CRptTemp_ReportsDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_ReportsDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_VALUEDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_ReportsDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ReportDefKey)
	{
		pNew = new CRptTemp_ReportDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ValueDefKey)
	{
		pNew = new CRptTemp_ValueDef();
	}

	return pNew;
}

CExBaseObject* CRptTemp_ReportsDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
	{
		pNew = new CRptTemp_ReportDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_VALUEDEF)
	{
		pNew = new CRptTemp_ValueDef();
	}

	return pNew;
}
