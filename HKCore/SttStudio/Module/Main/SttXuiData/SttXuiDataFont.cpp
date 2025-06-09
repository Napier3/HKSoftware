//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataFont.cpp  CSttXuiDataFont


#include "stdafx.h"
#include "SttXuiDataFont.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataFont::CSttXuiDataFont()
{
	//初始化属性
	m_nSize = 0;

	//初始化成员变量
}

CSttXuiDataFont::~CSttXuiDataFont()
{
}

long CSttXuiDataFont::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCr_BackKey, oNode, m_strCr_Back);
	xml_GetAttibuteValue(pXmlKeys->m_strCr_TextKey, oNode, m_strCr_Text);
	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_nSize);
	return 0;
}

long CSttXuiDataFont::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCr_BackKey, oElement, m_strCr_Back);
	xml_SetAttributeValue(pXmlKeys->m_strCr_TextKey, oElement, m_strCr_Text);
	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_nSize);
	return 0;
}

long CSttXuiDataFont::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCr_Back);
		BinarySerializeCalLen(oBinaryBuffer, m_strCr_Text);
		BinarySerializeCalLen(oBinaryBuffer, m_nSize);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCr_Back);
		BinarySerializeRead(oBinaryBuffer, m_strCr_Text);
		BinarySerializeRead(oBinaryBuffer, m_nSize);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCr_Back);
		BinarySerializeWrite(oBinaryBuffer, m_strCr_Text);
		BinarySerializeWrite(oBinaryBuffer, m_nSize);
	}
	return 0;
}

void CSttXuiDataFont::InitAfterRead()
{
}

BOOL CSttXuiDataFont::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataFont *p = (CSttXuiDataFont*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strCr_Back != p->m_strCr_Back)
	{
		return FALSE;
	}

	if(m_strCr_Text != p->m_strCr_Text)
	{
		return FALSE;
	}

	if(m_nSize != p->m_nSize)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataFont::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataFont *p = (CSttXuiDataFont*)pDest;

	p->m_strID = m_strID;
	p->m_strCr_Back = m_strCr_Back;
	p->m_strCr_Text = m_strCr_Text;
	p->m_nSize = m_nSize;
	return TRUE;
}

CBaseObject* CSttXuiDataFont::Clone()
{
	CSttXuiDataFont *p = new CSttXuiDataFont();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataFont::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataFont *p = new CSttXuiDataFont();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataFont::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttXuiDataFont::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSttXuiDataFont::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
