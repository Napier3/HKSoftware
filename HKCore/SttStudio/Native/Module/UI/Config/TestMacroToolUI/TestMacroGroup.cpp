//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroGroup.cpp  CTestMacroGroup


#include "stdafx.h"
#include "TestMacroGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTestMacroGroup::CTestMacroGroup()
{
	//初始化属性

	//初始化成员变量
}

CTestMacroGroup::~CTestMacroGroup()
{
}

long CTestMacroGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPicKey, oNode, m_strPic);
	return 0;
}

long CTestMacroGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPicKey, oElement, m_strPic);
	return 0;
}

long CTestMacroGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTestMacroGroup::InitAfterRead()
{
}

BOOL CTestMacroGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTestMacroGroup *p = (CTestMacroGroup*)pObj;

	if(m_strPic != p->m_strPic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTestMacroGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTestMacroGroup *p = (CTestMacroGroup*)pDest;

	p->m_strPic = m_strPic;
	return TRUE;
}

CBaseObject* CTestMacroGroup::Clone()
{
	CTestMacroGroup *p = new CTestMacroGroup();
	Copy(p);
	return p;
}

CBaseObject* CTestMacroGroup::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTestMacroGroup *p = new CTestMacroGroup();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTestMacroGroup::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CCOMMCMDREF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTESTMACROGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTESTMACROREF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTestMacroGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassDefMngrXmlRWKeys *pXmlKeys = (CClassDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCommcmdRefKey)
	{
		pNew = new CCommcmdRef();
	}
	else if (strClassID == pXmlKeys->m_strCTestMacroGroupKey)
	{
		pNew = new CTestMacroGroup();
	}
	else if (strClassID == pXmlKeys->m_strCTestMacroRefKey)
	{
		pNew = new CTestMacroRef();
	}

	return pNew;
}

CExBaseObject* CTestMacroGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CCOMMCMDREF)
	{
		pNew = new CCommcmdRef();
	}
	else if (nClassID == MNGRCLASSID_CTESTMACROGROUP)
	{
		pNew = new CTestMacroGroup();
	}
	else if (nClassID == MNGRCLASSID_CTESTMACROREF)
	{
		pNew = new CTestMacroRef();
	}

	return pNew;
}
