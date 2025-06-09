//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CommcmdRef.cpp  CCommcmdRef


#include "stdafx.h"
#include "CommcmdRef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCommcmdRef::CCommcmdRef()
{
	//初始化属性

	//初始化成员变量
}

CCommcmdRef::~CCommcmdRef()
{
}

long CCommcmdRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPicKey, oNode, m_strPic);
	xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CCommcmdRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPicKey, oElement, m_strPic);
	xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CCommcmdRef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPic);
		BinarySerializeCalLen(oBinaryBuffer, m_strFormat);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPic);
		BinarySerializeRead(oBinaryBuffer, m_strFormat);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPic);
		BinarySerializeWrite(oBinaryBuffer, m_strFormat);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CCommcmdRef::InitAfterRead()
{
}

BOOL CCommcmdRef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCommcmdRef *p = (CCommcmdRef*)pObj;

	if(m_strPic != p->m_strPic)
	{
		return FALSE;
	}

	if(m_strFormat != p->m_strFormat)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCommcmdRef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCommcmdRef *p = (CCommcmdRef*)pDest;

	p->m_strPic = m_strPic;
	p->m_strFormat = m_strFormat;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CCommcmdRef::Clone()
{
	CCommcmdRef *p = new CCommcmdRef();
	Copy(p);
	return p;
}

CBaseObject* CCommcmdRef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCommcmdRef *p = new CCommcmdRef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCommcmdRef::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CCommcmdRef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CCommcmdRef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
