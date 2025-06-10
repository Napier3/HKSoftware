//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroRef.cpp  CTestMacroRef


#include "stdafx.h"
#include "TestMacroRef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTestMacroRef::CTestMacroRef()
{
	//初始化属性

	//初始化成员变量
}

CTestMacroRef::~CTestMacroRef()
{
}

long CTestMacroRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPicKey, oNode, m_strPic);
	return 0;
}

long CTestMacroRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPicKey, oElement, m_strPic);
	return 0;
}

long CTestMacroRef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPic);
	}
	return 0;
}

void CTestMacroRef::InitAfterRead()
{
}

BOOL CTestMacroRef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTestMacroRef *p = (CTestMacroRef*)pObj;

	if(m_strPic != p->m_strPic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTestMacroRef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTestMacroRef *p = (CTestMacroRef*)pDest;

	p->m_strPic = m_strPic;
	return TRUE;
}

CBaseObject* CTestMacroRef::Clone()
{
	CTestMacroRef *p = new CTestMacroRef();
	Copy(p);
	return p;
}

CBaseObject* CTestMacroRef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTestMacroRef *p = new CTestMacroRef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTestMacroRef::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTestMacroRef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTestMacroRef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
