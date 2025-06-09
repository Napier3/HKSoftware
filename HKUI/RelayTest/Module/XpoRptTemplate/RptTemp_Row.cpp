//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Row.cpp  CRptTemp_Row


#include "stdafx.h"
#include "RptTemp_Row.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Row::CRptTemp_Row()
{
	//初始化属性
	m_nMergeCol = 0;
	m_pGbItemBase = NULL;
	//初始化成员变量
}

CRptTemp_Row::~CRptTemp_Row()
{
}

long CRptTemp_Row::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strItemPathKey, oNode, m_strItemPath);
	return 0;
}

long CRptTemp_Row::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strItemPathKey, oElement, m_strItemPath);
	return 0;
}

long CRptTemp_Row::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strItemPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strItemPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strItemPath);
	}
	return 0;
}

void CRptTemp_Row::InitAfterRead()
{
}

BOOL CRptTemp_Row::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Row *p = (CRptTemp_Row*)pObj;

	if(m_strItemPath != p->m_strItemPath)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Row::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Row *p = (CRptTemp_Row*)pDest;

	p->m_strItemPath = m_strItemPath;

	return TRUE;
}

CBaseObject* CRptTemp_Row::Clone()
{
	CRptTemp_Row *p = new CRptTemp_Row();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Row::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Row *p = new CRptTemp_Row();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Row::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_CELL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_Row::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_CellKey)
	{
		pNew = new CRptTemp_Cell();
	}

	return pNew;
}

CExBaseObject* CRptTemp_Row::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_CELL)
	{
		pNew = new CRptTemp_Cell();
	}

	return pNew;
}

CRptTemp_Cell* CRptTemp_Row::AddNewCell(const CString &strText)
{
	CRptTemp_Cell* pNewCell = new CRptTemp_Cell();
	pNewCell->m_strText = strText;
	AddNewChild(pNewCell);

	return pNewCell;
}