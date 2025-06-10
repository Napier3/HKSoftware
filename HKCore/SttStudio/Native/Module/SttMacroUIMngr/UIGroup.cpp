//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIGroup.cpp  UIGroup


#include "stdafx.h"
#include "UIGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CUIGroup::CUIGroup()
{
	//初始化属性

	//初始化成员变量
}

CUIGroup::~CUIGroup()
{
}

long CUIGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CUIGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CUIGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CUIGroup::InitAfterRead()
{
}

BOOL CUIGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIGroup *p = (CUIGroup*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUIGroup *p = (CUIGroup*)pDest;

	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CUIGroup::Clone()
{
	CUIGroup *p = new CUIGroup();
	Copy(p);
	return p;
}

CBaseObject* CUIGroup::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CUIGroup *p = new CUIGroup();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CUIGroup::CanPaste(UINT nClassID)
{
	if (nClassID == UIMNGRCLASSID_MACROUI)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestMacroUIMngrXmlRWKeys *pXmlKeys = (CSttTestMacroUIMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strMacroUIKey)
	{
		pNew = new CMacroUI();
	}

	return pNew;
}

CExBaseObject* CUIGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UIMNGRCLASSID_MACROUI)
	{
		pNew = new CMacroUI();
	}

	return pNew;
}
