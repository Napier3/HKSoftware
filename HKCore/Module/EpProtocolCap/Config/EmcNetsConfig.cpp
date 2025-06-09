//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcNetsConfig.cpp  CEmcNetsConfig


#include "stdafx.h"
#include "EmcNetsConfig.h"

CEmcNetsConfig::CEmcNetsConfig()
{
	//初始化属性
	m_strName = _T("网络端口管理");
	m_strID = _T("EmcNetsConfig");

	//初始化成员变量
}

CEmcNetsConfig::~CEmcNetsConfig()
{
}

long CEmcNetsConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcNetsConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcNetsConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEmcNetsConfig::InitAfterRead()
{
}

BOOL CEmcNetsConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEmcNetsConfig *p = (CEmcNetsConfig*)pObj;

	return TRUE;
}

BOOL CEmcNetsConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEmcNetsConfig *p = (CEmcNetsConfig*)pDest;

	return TRUE;
}

CBaseObject* CEmcNetsConfig::Clone()
{
	CEmcNetsConfig *p = new CEmcNetsConfig();
	Copy(p);
	return p;
}

BOOL CEmcNetsConfig::CanPaste(UINT nClassID)
{
	if (nClassID == EMCCLASSID_CEMCNETCONFIG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEmcNetsConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcNetConfigKey)
	{
		pNew = new CEmcNetConfig();
	}

	return pNew;
}

CExBaseObject* CEmcNetsConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCNETCONFIG)
	{
		pNew = new CEmcNetConfig();
	}

	return pNew;
}
long CEmcNetsConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

long CEmcNetsConfig::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

