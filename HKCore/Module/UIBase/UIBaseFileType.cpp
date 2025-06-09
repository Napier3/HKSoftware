//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseFileType.cpp  CUIBaseFileType


#include "stdafx.h"
#include "UIBaseFileType.h"

CUIBaseFileType::CUIBaseFileType()
{
	//初始化属性

	//初始化成员变量
}

CUIBaseFileType::~CUIBaseFileType()
{
}

long CUIBaseFileType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strExeKey, oNode, m_strExe);
	xml_GetAttibuteValue(pXmlKeys->m_strRunModeKey, oNode, m_strRunMode);

	return 0;
}

long CUIBaseFileType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strExeKey, oElement, m_strExe);
	xml_SetAttributeValue(pXmlKeys->m_strRunModeKey, oElement, m_strRunMode);

	return 0;
}

long CUIBaseFileType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strExe);
		BinarySerializeCalLen(oBinaryBuffer, m_strRunMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strExe);
		BinarySerializeWrite(oBinaryBuffer,m_strRunMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strExe);
		BinarySerializeRead(oBinaryBuffer, m_strRunMode);
	}

	return 0;
}

void CUIBaseFileType::InitAfterRead()
{
}

BOOL CUIBaseFileType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIBaseFileType *p = (CUIBaseFileType*)pObj;

	return TRUE;
}

BOOL CUIBaseFileType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUIBaseFileType *p = (CUIBaseFileType*)pDest;

	return TRUE;
}

CBaseObject* CUIBaseFileType::Clone()
{
	CUIBaseFileType *p = new CUIBaseFileType();
	Copy(p);
	return p;
}


CExBaseObject* CUIBaseFileType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCUIBaseFileTypePostfixKey)
	{
		pNew = new CUIBaseFileTypePostfix();
	}

	return pNew;
}

CExBaseObject* CUIBaseFileType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == UICLASSID_CUIBASEFILETYPEPOSTFIX)
	{
		pNew = new CUIBaseFileTypePostfix();
	}

	return pNew;
}


void CUIBaseFileType::InitXFileType(CXFileType *pXFileType)
{
	POS pos = GetHeadPosition();
	CUIBaseFileTypePostfix *pPostfix = NULL;

	while(pos != NULL)
	{
		pPostfix = (CUIBaseFileTypePostfix *)GetNext(pos);
		pXFileType->AddNewPostfix(pPostfix->m_strName, pPostfix->m_strID);
	}
}


