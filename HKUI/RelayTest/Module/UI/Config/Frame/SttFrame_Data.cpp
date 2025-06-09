//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_Data.cpp  CSttFrame_Data


#include "stdafx.h"
#include "SttFrame_Data.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_Data::CSttFrame_Data()
{
	//初始化属性
	m_nWidth = 0;

	//初始化成员变量
}

CSttFrame_Data::~CSttFrame_Data()
{
}

long CSttFrame_Data::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strIconKey, oNode, m_strIcon);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CSttFrame_Data::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strIconKey, oElement, m_strIcon);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CSttFrame_Data::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_strIcon);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
		BinarySerializeRead(oBinaryBuffer, m_strIcon);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
		BinarySerializeWrite(oBinaryBuffer, m_strIcon);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CSttFrame_Data::InitAfterRead()
{
}

BOOL CSttFrame_Data::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttFrame_Data *p = (CSttFrame_Data*)pObj;

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	if(m_strIcon != p->m_strIcon)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_Data::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttFrame_Data *p = (CSttFrame_Data*)pDest;

	p->m_nWidth = m_nWidth;
	p->m_strIcon = m_strIcon;
	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CSttFrame_Data::Clone()
{
	CSttFrame_Data *p = new CSttFrame_Data();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_Data::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_Data *p = new CSttFrame_Data();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

