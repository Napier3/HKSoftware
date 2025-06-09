//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_ReportView.cpp  CSttFrame_ReportView


#include "stdafx.h"
#include "SttFrame_ReportView.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttFrame_ReportView::CSttFrame_ReportView()
{
	//初始化属性

	//初始化成员变量
	m_pFont = NULL;
}

CSttFrame_ReportView::~CSttFrame_ReportView()
{
}

long CSttFrame_ReportView::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_ReportView::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_ReportView::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CSttFrame_ReportView::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
		{
			m_pFont = (CSttFrame_Font*)p;
		}
	}

	if (m_pFont == NULL)
	{
		m_pFont = (CSttFrame_Font*)AddNewChild(new CSttFrame_Font());
	}

}

BOOL CSttFrame_ReportView::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_ReportView *p = (CSttFrame_ReportView*)pObj;

	return TRUE;
}

BOOL CSttFrame_ReportView::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_ReportView *p = (CSttFrame_ReportView*)pDest;

	return TRUE;
}

CBaseObject* CSttFrame_ReportView::Clone()
{
	CSttFrame_ReportView *p = new CSttFrame_ReportView();
	Copy(p);
	return p;
}

CBaseObject* CSttFrame_ReportView::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_ReportView *p = new CSttFrame_ReportView();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_ReportView::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_ReportView::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_FontKey)
	{
		pNew = new CSttFrame_Font();
	}

	return pNew;
}

CExBaseObject* CSttFrame_ReportView::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
	{
		pNew = new CSttFrame_Font();
	}

	return pNew;
}
