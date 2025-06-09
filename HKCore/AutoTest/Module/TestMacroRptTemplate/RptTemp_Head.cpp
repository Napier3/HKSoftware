//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Head.cpp  CRptTemp_Head


#include "stdafx.h"
#include "RptTemp_Head.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Head::CRptTemp_Head()
{
	//初始化属性
	m_nMergeCol = 0;
    m_fHeadHeight = 0.0;
    m_fColWidth = 0.0;
	//初始化成员变量
}

CRptTemp_Head::~CRptTemp_Head()
{
}

long CRptTemp_Head::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strHeadHeightKey, oNode, m_fHeadHeight);
    xml_GetAttibuteValue(pXmlKeys->m_strColWidthKey, oNode, m_fColWidth);

	return 0;
}

long CRptTemp_Head::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strHeadHeightKey, oElement, m_fHeadHeight);
    xml_SetAttributeValue(pXmlKeys->m_strColWidthKey, oElement, m_fColWidth);

	return 0;
}

long CRptTemp_Head::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
        BinarySerializeCalLen(oBinaryBuffer, m_fHeadHeight);
        BinarySerializeCalLen(oBinaryBuffer, m_fColWidth);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
        BinarySerializeRead(oBinaryBuffer, m_fHeadHeight);
        BinarySerializeRead(oBinaryBuffer, m_fColWidth);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
        BinarySerializeWrite(oBinaryBuffer, m_fHeadHeight);
        BinarySerializeWrite(oBinaryBuffer, m_fColWidth);
	}
	return 0;
}

void CRptTemp_Head::InitAfterRead()
{
}

BOOL CRptTemp_Head::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Head *p = (CRptTemp_Head*)pObj;	

    if(m_fHeadHeight != p->m_fHeadHeight)
    {
        return FALSE;
    }

    if(m_fColWidth != p->m_fColWidth)
    {
        return FALSE;
    }

	return TRUE;
}

BOOL CRptTemp_Head::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Head *p = (CRptTemp_Head*)pDest;

    p->m_fHeadHeight = m_fHeadHeight;
    p->m_fColWidth = m_fColWidth;

	return TRUE;
}

CBaseObject* CRptTemp_Head::Clone()
{
	CRptTemp_Head *p = new CRptTemp_Head();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Head::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Head *p = new CRptTemp_Head();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Head::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_CELL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_Head::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_CellKey)
	{
		pNew = new CRptTemp_Cell();
	}

	return pNew;
}

CExBaseObject* CRptTemp_Head::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_CELL)
	{
		pNew = new CRptTemp_Cell();
	}

	return pNew;
}
