//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataTab.cpp  CSttXuiDataTab


#include "stdafx.h"
#include "SttXuiDataTab.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataTab::CSttXuiDataTab()
{
	//初始化属性

	//初始化成员变量
}

CSttXuiDataTab::~CSttXuiDataTab()
{
}

long CSttXuiDataTab::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFontKey, oNode, m_strFont);
	return 0;
}

long CSttXuiDataTab::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFontKey, oElement, m_strFont);
	return 0;
}

long CSttXuiDataTab::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFont);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFont);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFont);
	}
	return 0;
}

void CSttXuiDataTab::InitAfterRead()
{
}

BOOL CSttXuiDataTab::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataTab *p = (CSttXuiDataTab*)pObj;

	if(m_strFont != p->m_strFont)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataTab::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataTab *p = (CSttXuiDataTab*)pDest;

	p->m_strFont = m_strFont;
	return TRUE;
}

CBaseObject* CSttXuiDataTab::Clone()
{
	CSttXuiDataTab *p = new CSttXuiDataTab();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataTab::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataTab *p = new CSttXuiDataTab();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataTab::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTXUIDATATEXT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATABTNSGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATAFILEMNGRGRID)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttXuiDataTab::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttXuiDataTextKey)
	{
		pNew = new CSttXuiDataText();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataTestBtnsGroupKey)
	{
		pNew = new CSttXuiDataTestBtnsGroup();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataBtnsGroupKey)
	{
		pNew = new CSttXuiDataBtnsGroup();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataFileMngrGridKey)
	{
		pNew = new CSttXuiDataFileMngrGrid();
	}

	return pNew;
}

CExBaseObject* CSttXuiDataTab::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTXUIDATATEXT)
	{
		pNew = new CSttXuiDataText();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
	{
		pNew = new CSttXuiDataTestBtnsGroup();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATABTNSGROUP)
	{
		pNew = new CSttXuiDataBtnsGroup();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATAFILEMNGRGRID)
	{
		pNew = new CSttXuiDataFileMngrGrid();
	}

	return pNew;
}
