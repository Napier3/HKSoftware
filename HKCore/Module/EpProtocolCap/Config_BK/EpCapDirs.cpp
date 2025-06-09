//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDirs.cpp  CEpCapDirs


#include "stdafx.h"
#include "EpCapDirs.h"

CEpCapDirs::CEpCapDirs()
{
	//初始化属性

	//初始化成员变量
}

CEpCapDirs::~CEpCapDirs()
{
}

long CEpCapDirs::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapDirs::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapDirs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEpCapDirs::InitAfterRead()
{
}

BOOL CEpCapDirs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapDirs *p = (CEpCapDirs*)pObj;

	return TRUE;
}

BOOL CEpCapDirs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapDirs *p = (CEpCapDirs*)pDest;

	return TRUE;
}

CBaseObject* CEpCapDirs::Clone()
{
	CEpCapDirs *p = new CEpCapDirs();
	Copy(p);
	return p;
}

long CEpCapDirs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEpCapDirs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CEpCapDirs::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPDIR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapDirs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapDirKey)
	{
		pNew = new CEpCapDir();
	}

	return pNew;
}

CExBaseObject* CEpCapDirs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPDIR)
	{
		pNew = new CEpCapDir();
	}

	return pNew;
}
