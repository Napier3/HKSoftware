//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataText.cpp  CSttXuiDataText


#include "stdafx.h"
#include "SttXuiDataText.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataText::CSttXuiDataText()
{
	//初始化属性
	m_nX = 0;
	m_nY = 0;
	m_nCx = 0;
	m_nCy = 0;

	//初始化成员变量
}

CSttXuiDataText::~CSttXuiDataText()
{
}

long CSttXuiDataText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);
	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_nX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_nY);
	xml_GetAttibuteValue(pXmlKeys->m_strCxKey, oNode, m_nCx);
	xml_GetAttibuteValue(pXmlKeys->m_strCyKey, oNode, m_nCy);
	xml_GetAttibuteValue(pXmlKeys->m_strFontKey, oNode, m_strFont);
	xml_GetAttibuteValue(pXmlKeys->m_strPicKey, oNode, m_strPic);
	return 0;
}

long CSttXuiDataText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);
	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_nX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_nY);
	xml_SetAttributeValue(pXmlKeys->m_strCxKey, oElement, m_nCx);
	xml_SetAttributeValue(pXmlKeys->m_strCyKey, oElement, m_nCy);
	xml_SetAttributeValue(pXmlKeys->m_strFontKey, oElement, m_strFont);
	xml_SetAttributeValue(pXmlKeys->m_strPicKey, oElement, m_strPic);
	return 0;
}

long CSttXuiDataText::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
		BinarySerializeCalLen(oBinaryBuffer, m_nX);
		BinarySerializeCalLen(oBinaryBuffer, m_nY);
		BinarySerializeCalLen(oBinaryBuffer, m_nCx);
		BinarySerializeCalLen(oBinaryBuffer, m_nCy);
		BinarySerializeCalLen(oBinaryBuffer, m_strFont);
		BinarySerializeCalLen(oBinaryBuffer, m_strPic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strText);
		BinarySerializeRead(oBinaryBuffer, m_nX);
		BinarySerializeRead(oBinaryBuffer, m_nY);
		BinarySerializeRead(oBinaryBuffer, m_nCx);
		BinarySerializeRead(oBinaryBuffer, m_nCy);
		BinarySerializeRead(oBinaryBuffer, m_strFont);
		BinarySerializeRead(oBinaryBuffer, m_strPic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strText);
		BinarySerializeWrite(oBinaryBuffer, m_nX);
		BinarySerializeWrite(oBinaryBuffer, m_nY);
		BinarySerializeWrite(oBinaryBuffer, m_nCx);
		BinarySerializeWrite(oBinaryBuffer, m_nCy);
		BinarySerializeWrite(oBinaryBuffer, m_strFont);
		BinarySerializeWrite(oBinaryBuffer, m_strPic);
	}
	return 0;
}

void CSttXuiDataText::InitAfterRead()
{
}

BOOL CSttXuiDataText::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataText *p = (CSttXuiDataText*)pObj;

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	if(m_nX != p->m_nX)
	{
		return FALSE;
	}

	if(m_nY != p->m_nY)
	{
		return FALSE;
	}

	if(m_nCx != p->m_nCx)
	{
		return FALSE;
	}

	if(m_nCy != p->m_nCy)
	{
		return FALSE;
	}

	if(m_strFont != p->m_strFont)
	{
		return FALSE;
	}

	if(m_strPic != p->m_strPic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataText::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataText *p = (CSttXuiDataText*)pDest;

	p->m_strText = m_strText;
	p->m_nX = m_nX;
	p->m_nY = m_nY;
	p->m_nCx = m_nCx;
	p->m_nCy = m_nCy;
	p->m_strFont = m_strFont;
	p->m_strPic = m_strPic;
	return TRUE;
}

CBaseObject* CSttXuiDataText::Clone()
{
	CSttXuiDataText *p = new CSttXuiDataText();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataText::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataText *p = new CSttXuiDataText();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataText::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttXuiDataText::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSttXuiDataText::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
