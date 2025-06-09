//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataBtnsGroup.cpp  CSttXuiDataBtnsGroup


#include "stdafx.h"
#include "SttXuiDataBtnsGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataBtnsGroup::CSttXuiDataBtnsGroup()
{
	//初始化属性
	m_nX = 0;
	m_nY = 0;
	m_nCx = 0;
	m_nCy = 0;
	m_nInset = 0;

	//初始化成员变量
}

CSttXuiDataBtnsGroup::~CSttXuiDataBtnsGroup()
{
}

long CSttXuiDataBtnsGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_nX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_nY);
	xml_GetAttibuteValue(pXmlKeys->m_strCxKey, oNode, m_nCx);
	xml_GetAttibuteValue(pXmlKeys->m_strCyKey, oNode, m_nCy);
	xml_GetAttibuteValue(pXmlKeys->m_strInsetKey, oNode, m_nInset);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strFromKey, oNode, m_strFrom);
	xml_GetAttibuteValue(pXmlKeys->m_strFontKey, oNode, m_strFont);
	return 0;
}

long CSttXuiDataBtnsGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_nX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_nY);
	xml_SetAttributeValue(pXmlKeys->m_strCxKey, oElement, m_nCx);
	xml_SetAttributeValue(pXmlKeys->m_strCyKey, oElement, m_nCy);
	xml_SetAttributeValue(pXmlKeys->m_strInsetKey, oElement, m_nInset);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strFromKey, oElement, m_strFrom);
	xml_SetAttributeValue(pXmlKeys->m_strFontKey, oElement, m_strFont);
	return 0;
}

long CSttXuiDataBtnsGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nX);
		BinarySerializeCalLen(oBinaryBuffer, m_nY);
		BinarySerializeCalLen(oBinaryBuffer, m_nCx);
		BinarySerializeCalLen(oBinaryBuffer, m_nCy);
		BinarySerializeCalLen(oBinaryBuffer, m_nInset);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strFrom);
		BinarySerializeCalLen(oBinaryBuffer, m_strFont);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nX);
		BinarySerializeRead(oBinaryBuffer, m_nY);
		BinarySerializeRead(oBinaryBuffer, m_nCx);
		BinarySerializeRead(oBinaryBuffer, m_nCy);
		BinarySerializeRead(oBinaryBuffer, m_nInset);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strFrom);
		BinarySerializeRead(oBinaryBuffer, m_strFont);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nX);
		BinarySerializeWrite(oBinaryBuffer, m_nY);
		BinarySerializeWrite(oBinaryBuffer, m_nCx);
		BinarySerializeWrite(oBinaryBuffer, m_nCy);
		BinarySerializeWrite(oBinaryBuffer, m_nInset);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strFrom);
		BinarySerializeWrite(oBinaryBuffer, m_strFont);
	}
	return 0;
}

void CSttXuiDataBtnsGroup::InitAfterRead()
{
}

BOOL CSttXuiDataBtnsGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataBtnsGroup *p = (CSttXuiDataBtnsGroup*)pObj;

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

	if(m_nInset != p->m_nInset)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strFrom != p->m_strFrom)
	{
		return FALSE;
	}

	if(m_strFont != p->m_strFont)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataBtnsGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataBtnsGroup *p = (CSttXuiDataBtnsGroup*)pDest;

	p->m_nX = m_nX;
	p->m_nY = m_nY;
	p->m_nCx = m_nCx;
	p->m_nCy = m_nCy;
	p->m_nInset = m_nInset;
	p->m_strType = m_strType;
	p->m_strFrom = m_strFrom;
	p->m_strFont = m_strFont;
	return TRUE;
}

CBaseObject* CSttXuiDataBtnsGroup::Clone()
{
	CSttXuiDataBtnsGroup *p = new CSttXuiDataBtnsGroup();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataBtnsGroup::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataBtnsGroup *p = new CSttXuiDataBtnsGroup();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataBtnsGroup::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTXUIDATABUTTON)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttXuiDataBtnsGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttXuiDataButtonKey)
	{
		pNew = new CSttXuiDataButton();
	}

	return pNew;
}

CExBaseObject* CSttXuiDataBtnsGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTXUIDATABUTTON)
	{
		pNew = new CSttXuiDataButton();
	}

	return pNew;
}
