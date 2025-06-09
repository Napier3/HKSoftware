//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcQueryProtocols.cpp  CEmcQueryProtocols


#include "stdafx.h"
#include "EmcQueryProtocols.h"

CEmcQueryProtocols::CEmcQueryProtocols()
{
	//初始化属性
	m_strName = _T("查询分类管理");
	m_strID = _T("EmcQueryProtocols");

	//初始化成员变量
}

CEmcQueryProtocols::~CEmcQueryProtocols()
{
}

long CEmcQueryProtocols::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcQueryProtocols::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcQueryProtocols::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);
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

void CEmcQueryProtocols::InitAfterRead()
{
}

BOOL CEmcQueryProtocols::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseList::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEmcQueryProtocols *p = (CEmcQueryProtocols*)pObj;

	return TRUE;
}

BOOL CEmcQueryProtocols::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);

	CEmcQueryProtocols *p = (CEmcQueryProtocols*)pDest;

	return TRUE;
}

CBaseObject* CEmcQueryProtocols::Clone()
{
	CEmcQueryProtocols *p = new CEmcQueryProtocols();
	Copy(p);
	return p;
}

BOOL CEmcQueryProtocols::CanPaste(UINT nClassID)
{

	return FALSE;
}

CExBaseObject* CEmcQueryProtocols::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strProtocolKey)
	{
		pNew = new CEmcQueryProtocol();
	}

	return pNew;
}

CExBaseObject* CEmcQueryProtocols::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCQUERYPROTOCOL)
	{
		pNew = new CEmcQueryProtocol();
	}

	return pNew;
}
long CEmcQueryProtocols::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEmcQueryProtocols::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

