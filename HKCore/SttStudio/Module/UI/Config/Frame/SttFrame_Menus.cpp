//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_Menus.cpp  CSttFrame_Menus


#include "stdafx.h"
#include "SttFrame_Menus.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_Menus::CSttFrame_Menus()
{
	//初始化属性
	m_nUse = 0;

	//初始化成员变量
}

CSttFrame_Menus::~CSttFrame_Menus()
{
}

long CSttFrame_Menus::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_nUse);
	return 0;
}

long CSttFrame_Menus::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUseKey, oElement, m_nUse);
	return 0;
}

long CSttFrame_Menus::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nUse);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nUse);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nUse);
	}
	return 0;
}

void CSttFrame_Menus::InitAfterRead()
{
}

BOOL CSttFrame_Menus::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_Menus *p = (CSttFrame_Menus*)pObj;

	if(m_nUse != p->m_nUse)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_Menus::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_Menus *p = (CSttFrame_Menus*)pDest;

	p->m_nUse = m_nUse;
	return TRUE;
}

CBaseObject* CSttFrame_Menus::Clone()
{
	CSttFrame_Menus *p = new CSttFrame_Menus();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_Menus::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_Menus *p = new CSttFrame_Menus();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_Menus::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_MENU)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_Menus::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_MenuKey)
	{
		pNew = new CSttFrame_Menu();
	}

	return pNew;
}

CExBaseObject* CSttFrame_Menus::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_MENU)
	{
		pNew = new CSttFrame_Menu();
	}

	return pNew;
}
