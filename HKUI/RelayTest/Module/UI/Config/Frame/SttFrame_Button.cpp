//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_Button.cpp  CSttFrame_Button


#include "stdafx.h"
#include "SttFrame_Button.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_Button::CSttFrame_Button()
{
	//初始化属性
	m_nWidth = 0;

	//初始化成员变量
}

CSttFrame_Button::~CSttFrame_Button()
{
}

long CSttFrame_Button::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIconKey, oNode, m_strIcon);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableStateKey, oNode, m_strEnableState);
	return 0;
}

long CSttFrame_Button::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIconKey, oElement, m_strIcon);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strEnableStateKey, oElement, m_strEnableState);
	return 0;
}

long CSttFrame_Button::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttFrame_Button::InitAfterRead()
{
}

BOOL CSttFrame_Button::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttFrame_Button *p = (CSttFrame_Button*)pObj;

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

BOOL CSttFrame_Button::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttFrame_Button *p = (CSttFrame_Button*)pDest;

	p->m_strIcon = m_strIcon;
	p->m_nWidth = m_nWidth;
	p->m_strEnableState = m_strEnableState;
	return TRUE;
}

CBaseObject* CSttFrame_Button::Clone()
{
	CSttFrame_Button *p = new CSttFrame_Button();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_Button::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_Button *p = new CSttFrame_Button();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

