//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapConfig.cpp  CEpCapConfig


#include "stdafx.h"
#include "EpCapConfig.h"

CEpCapConfig::CEpCapConfig()
{
	//初始化属性

	//初始化成员变量
}

CEpCapConfig::~CEpCapConfig()
{
}

long CEpCapConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEpCapConfig::InitAfterRead()
{
}

BOOL CEpCapConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapConfig *p = (CEpCapConfig*)pObj;

	return TRUE;
}

BOOL CEpCapConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapConfig *p = (CEpCapConfig*)pDest;

	return TRUE;
}

CBaseObject* CEpCapConfig::Clone()
{
	CEpCapConfig *p = new CEpCapConfig();
	Copy(p);
	return p;
}

long CEpCapConfig::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEpCapConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CEpCapConfig::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETCONFIG)
	{
		return TRUE;
	}

	if (nClassID == ECCLASSID_CEPCAPSERIALCONFIG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetConfigKey)
	{
		pNew = new CEpCapNetConfig();
	}
	else if (strClassID == pXmlKeys->m_strCEpCapSerialConfigKey)
	{
		pNew = new CEpCapSerialConfig();
	}

	return pNew;
}

CExBaseObject* CEpCapConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETCONFIG)
	{
		pNew = new CEpCapNetConfig();
	}
	else if (nClassID == ECCLASSID_CEPCAPSERIALCONFIG)
	{
		pNew = new CEpCapSerialConfig();
	}

	return pNew;
}
