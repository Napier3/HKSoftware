//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_Size.cpp  CSttFrame_Size


#include "stdafx.h"
#include "SttFrame_Size.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_Size::CSttFrame_Size()
{
	//初始化属性
	m_nWidth = 0;
	m_nHeight = 0;

	//初始化成员变量
}

CSttFrame_Size::~CSttFrame_Size()
{
}

long CSttFrame_Size::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_nHeight);
	return 0;
}

long CSttFrame_Size::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_nHeight);
	return 0;
}

long CSttFrame_Size::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_nHeight);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
		BinarySerializeRead(oBinaryBuffer, m_nHeight);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
		BinarySerializeWrite(oBinaryBuffer, m_nHeight);
	}
	return 0;
}

void CSttFrame_Size::InitAfterRead()
{
}

BOOL CSttFrame_Size::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_Size *p = (CSttFrame_Size*)pObj;

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	if(m_nHeight != p->m_nHeight)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_Size::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_Size *p = (CSttFrame_Size*)pDest;

	p->m_nWidth = m_nWidth;
	p->m_nHeight = m_nHeight;
	return TRUE;
}

CBaseObject* CSttFrame_Size::Clone()
{
	CSttFrame_Size *p = new CSttFrame_Size();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_Size::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_Size *p = new CSttFrame_Size();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

