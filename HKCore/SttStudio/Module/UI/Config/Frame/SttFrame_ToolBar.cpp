//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_ToolBar.cpp  CSttFrame_ToolBar


#include "stdafx.h"
#include "SttFrame_ToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_ToolBar::CSttFrame_ToolBar()
{
	//初始化属性

	//初始化成员变量
}

CSttFrame_ToolBar::~CSttFrame_ToolBar()
{
}

long CSttFrame_ToolBar::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIcon_PosKey, oNode, m_strIconPos);
	return 0;
}

long CSttFrame_ToolBar::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIcon_PosKey, oElement, m_strIconPos);
	return 0;
}

long CSttFrame_ToolBar::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIconPos);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIconPos);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIconPos);
	}
	return 0;
}

void CSttFrame_ToolBar::InitAfterRead()
{
}

BOOL CSttFrame_ToolBar::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_ToolBar *p = (CSttFrame_ToolBar*)pObj;

	if(m_strIconPos != p->m_strIconPos)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrame_ToolBar::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_ToolBar *p = (CSttFrame_ToolBar*)pDest;

	p->m_strIconPos = m_strIconPos;
	return TRUE;
}

CBaseObject* CSttFrame_ToolBar::Clone()
{
	CSttFrame_ToolBar *p = new CSttFrame_ToolBar();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_ToolBar::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_ToolBar *p = new CSttFrame_ToolBar();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_ToolBar::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_PANAL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_ToolBar::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_PanalKey)
	{
		pNew = new CSttFrame_Panal();
	}

	return pNew;
}

CExBaseObject* CSttFrame_ToolBar::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_PANAL)
	{
		pNew = new CSttFrame_Panal();
	}

	return pNew;
}
