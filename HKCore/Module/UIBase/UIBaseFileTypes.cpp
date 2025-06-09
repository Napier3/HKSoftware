//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseFileTypes.cpp  CUIBaseFileTypes


#include "stdafx.h"
#include "UIBaseFileTypes.h"


CUIBaseFileTypes::CUIBaseFileTypes()
{
	//初始化属性

	//初始化成员变量
	m_bOnllySearchMainTypeFile = 1;
	m_strRootName = _T("文件类型管理");
}

CUIBaseFileTypes::~CUIBaseFileTypes()
{
}

long CUIBaseFileTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRootPathKey, oNode, m_strRootPath);
	xml_GetAttibuteValue(pXmlKeys->m_strRootNameKey, oNode, m_strRootName);
	xml_GetAttibuteValue(pXmlKeys->m_strOnlySearchMainTypeFileKey, oNode, m_bOnllySearchMainTypeFile);
	
	return 0;
}

long CUIBaseFileTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRootPathKey, oElement, m_strRootPath);
	xml_SetAttributeValue(pXmlKeys->m_strRootNameKey, oElement, m_strRootName);
	xml_SetAttributeValue(pXmlKeys->m_strOnlySearchMainTypeFileKey, oElement, m_bOnllySearchMainTypeFile);

	return 0;
}

long CUIBaseFileTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strRootPath);
		BinarySerializeCalLen(oBinaryBuffer, m_strRootName);
		BinarySerializeCalLen(oBinaryBuffer, m_bOnllySearchMainTypeFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_bOnllySearchMainTypeFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_bOnllySearchMainTypeFile);
	}

	return 0;
}

void CUIBaseFileTypes::InitAfterRead()
{
}

BOOL CUIBaseFileTypes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIBaseFileTypes *p = (CUIBaseFileTypes*)pObj;

	return TRUE;
}

BOOL CUIBaseFileTypes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIBaseFileTypes *p = (CUIBaseFileTypes*)pDest;
	p->m_strRootPath = m_strRootPath;
	p->m_strRootName = m_strRootName;
	p->m_bOnllySearchMainTypeFile = m_bOnllySearchMainTypeFile;

	return TRUE;
}

CBaseObject* CUIBaseFileTypes::Clone()
{
	CUIBaseFileTypes *p = new CUIBaseFileTypes();
	Copy(p);
	return p;
}

BOOL CUIBaseFileTypes::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIBASEFILETYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIBaseFileTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIBaseFileTypeKey)
	{
		pNew = new CUIBaseFileType();
	}

	return pNew;
}

CExBaseObject* CUIBaseFileTypes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIBASEFILETYPE)
	{
		pNew = new CUIBaseFileType();
	}

	return pNew;
}

CString CUIBaseFileTypes::GetRootPath()
{
	return _P_GetFullPath(m_strRootPath);
}

CString CUIBaseFileTypes::GetRootName()
{
	return m_strRootName;
}

void CUIBaseFileTypes::InitXFileTypes(CXFileTypes *pXFileTypes)
{
	POS pos = GetHeadPosition();
	CUIBaseFileType *pType = NULL;
	CXFileType *pXFileType = NULL;

	while(pos != NULL)
	{
		pType = (CUIBaseFileType *)GetNext(pos);
		pXFileType = pXFileTypes->AddFileType(pType->m_strName, pType->m_strID, pType->m_strExe, pType->m_strRunMode);
		pType->InitXFileType(pXFileType);
	}
}

