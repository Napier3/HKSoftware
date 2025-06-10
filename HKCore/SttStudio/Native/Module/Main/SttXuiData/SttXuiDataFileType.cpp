//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataFileType.cpp  CSttXuiDataFileType


#include "stdafx.h"
#include "SttXuiDataFileType.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataFileType::CSttXuiDataFileType()
{
	//初始化属性

	//初始化成员变量
}

CSttXuiDataFileType::~CSttXuiDataFileType()
{
}

long CSttXuiDataFileType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRootKey, oNode, m_strRoot);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CSttXuiDataFileType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRootKey, oElement, m_strRoot);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CSttXuiDataFileType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strRoot);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strRoot);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strRoot);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CSttXuiDataFileType::InitAfterRead()
{
}

BOOL CSttXuiDataFileType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataFileType *p = (CSttXuiDataFileType*)pObj;

	if(m_strRoot != p->m_strRoot)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataFileType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataFileType *p = (CSttXuiDataFileType*)pDest;

	p->m_strRoot = m_strRoot;
	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CSttXuiDataFileType::Clone()
{
	CSttXuiDataFileType *p = new CSttXuiDataFileType();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataFileType::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataFileType *p = new CSttXuiDataFileType();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataFileType::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttXuiDataFileType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSttXuiDataFileType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
