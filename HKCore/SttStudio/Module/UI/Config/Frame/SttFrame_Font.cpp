//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_Font.cpp  CSttFrame_Font


#include "stdafx.h"
#include "SttFrame_Font.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_Font::CSttFrame_Font()
{
	//初始化属性
	m_nWidth = 0;
	m_nHeigth = 0;
	m_nBold = 0;

	//初始化成员变量
}

CSttFrame_Font::~CSttFrame_Font()
{
}

long CSttFrame_Font::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_nHeigth);
	xml_GetAttibuteValue(pXmlKeys->m_strBoldKey, oNode, m_nBold);
	return 0;
}

long CSttFrame_Font::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_nHeigth);
	xml_SetAttributeValue(pXmlKeys->m_strBoldKey, oElement, m_nBold);
	return 0;
}

long CSttFrame_Font::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_nHeigth);
		BinarySerializeCalLen(oBinaryBuffer, m_nBold);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
		BinarySerializeRead(oBinaryBuffer, m_nHeigth);
		BinarySerializeRead(oBinaryBuffer, m_nBold);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
		BinarySerializeWrite(oBinaryBuffer, m_nHeigth);
		BinarySerializeWrite(oBinaryBuffer, m_nBold);
	}
	return 0;
}

void CSttFrame_Font::InitAfterRead()
{
}

BOOL CSttFrame_Font::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_Font *p = (CSttFrame_Font*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	if(m_nHeigth != p->m_nHeigth)
	{
		return FALSE;
	}

	if(m_nBold != p->m_nBold)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_Font::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_Font *p = (CSttFrame_Font*)pDest;

	p->m_strName = m_strName;
	p->m_nWidth = m_nWidth;
	p->m_nHeigth = m_nHeigth;
	p->m_nBold = m_nBold;
	return TRUE;
}

CBaseObject* CSttFrame_Font::Clone()
{
	CSttFrame_Font *p = new CSttFrame_Font();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_Font::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_Font *p = new CSttFrame_Font();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

