//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_Item.cpp  CSttFrame_Item


#include "stdafx.h"
#include "SttFrame_Item.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_Item::CSttFrame_Item()
{
	//初始化属性
	m_nMacroUse = 0;
	//初始化成员变量
}

CSttFrame_Item::~CSttFrame_Item()
{
}

long CSttFrame_Item::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIconKey, oNode, m_strIcon);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableStateKey, oNode, m_strEnableState);
	xml_GetAttibuteValue(pXmlKeys->m_strMacro_UseKey, oNode, m_nMacroUse);

	return 0;
}

long CSttFrame_Item::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIconKey, oElement, m_strIcon);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strEnableStateKey, oElement, m_strEnableState);
	xml_SetAttributeValue(pXmlKeys->m_strMacro_UseKey, oElement, m_nMacroUse);

	return 0;
}

long CSttFrame_Item::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIcon);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIcon);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIcon);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
	}
	return 0;
}

void CSttFrame_Item::InitAfterRead()
{
}

BOOL CSttFrame_Item::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttFrame_Item *p = (CSttFrame_Item*)pObj;

	if(m_strIcon != p->m_strIcon)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSttFrame_Item::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttFrame_Item *p = (CSttFrame_Item*)pDest;

	p->m_strIcon = m_strIcon;
	p->m_nWidth = m_nWidth;
	p->m_strEnableState = m_strEnableState;
	p->m_nMacroUse = m_nMacroUse;

	return TRUE;
}

CBaseObject* CSttFrame_Item::Clone()
{
	CSttFrame_Item *p = new CSttFrame_Item();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_Item::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_Item *p = new CSttFrame_Item();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

