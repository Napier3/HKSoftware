//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_StatusBar.cpp  CSttFrame_StatusBar


#include "stdafx.h"
#include "SttFrame_StatusBar.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_StatusBar::CSttFrame_StatusBar()
{
	//初始化属性
	m_nHeight = 0;
	m_nWidth = 0;
	//初始化成员变量
	m_pPanal = NULL;
}

CSttFrame_StatusBar::~CSttFrame_StatusBar()
{
}

long CSttFrame_StatusBar::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIcon_PosKey, oNode, m_strIconPos);
	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_nHeight);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	return 0;
}

long CSttFrame_StatusBar::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIcon_PosKey, oElement, m_strIconPos);
	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_nHeight);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	return 0;
}

long CSttFrame_StatusBar::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIconPos);
		BinarySerializeCalLen(oBinaryBuffer, m_nHeight);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIconPos);
		BinarySerializeRead(oBinaryBuffer, m_nHeight);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIconPos);
		BinarySerializeWrite(oBinaryBuffer, m_nHeight);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
	}
	return 0;
}

void CSttFrame_StatusBar::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CSTTFRAME_PANAL)
		{
			m_pPanal = (CSttFrame_Panal*)p;
		}
	}

	if (m_pPanal == NULL)
	{
		m_pPanal = (CSttFrame_Panal*)AddNewChild(new CSttFrame_Panal());
	}

}

BOOL CSttFrame_StatusBar::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_StatusBar *p = (CSttFrame_StatusBar*)pObj;

	if(m_strIconPos != p->m_strIconPos)
	{
		return FALSE;
	}

	if(m_nHeight != p->m_nHeight)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_StatusBar::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_StatusBar *p = (CSttFrame_StatusBar*)pDest;

	p->m_strIconPos = m_strIconPos;
	p->m_nHeight = m_nHeight;
	p->m_nWidth = m_nWidth;
	return TRUE;
}

CBaseObject* CSttFrame_StatusBar::Clone()
{
	CSttFrame_StatusBar *p = new CSttFrame_StatusBar();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_StatusBar::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_StatusBar *p = new CSttFrame_StatusBar();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_StatusBar::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_PANAL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_StatusBar::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_PanalKey)
	{
		pNew = new CSttFrame_Panal();
	}

	return pNew;
}

CExBaseObject* CSttFrame_StatusBar::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_PANAL)
	{
		pNew = new CSttFrame_Panal();
	}

	return pNew;
}
