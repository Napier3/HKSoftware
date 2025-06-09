//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcQueryProtocol.cpp  CEmcQueryProtocol


#include "stdafx.h"
#include "EmcQueryProtocol.h"

CEmcQueryProtocol::CEmcQueryProtocol()
{
	//初始化属性

	//初始化成员变量
	m_strName = _T("规约查询对象");
}

CEmcQueryProtocol::~CEmcQueryProtocol()
{
}

long CEmcQueryProtocol::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcQueryProtocol::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcQueryProtocol::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CEmcQueryProtocol::InitAfterRead()
{
}

BOOL CEmcQueryProtocol::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEmcQueryProtocol *p = (CEmcQueryProtocol*)pObj;

	return TRUE;
}

BOOL CEmcQueryProtocol::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEmcQueryProtocol *p = (CEmcQueryProtocol*)pDest;

	return TRUE;
}

CBaseObject* CEmcQueryProtocol::Clone()
{
	CEmcQueryProtocol *p = new CEmcQueryProtocol();
	Copy(p);
	return p;
}

BOOL CEmcQueryProtocol::CanPaste(UINT nClassID)
{

	return FALSE;
}

CExBaseObject* CEmcQueryProtocol::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcQueryAddrDirKey)
	{
		pNew = new CEmcQueryAddrDir();
	}

	return pNew;
}

CExBaseObject* CEmcQueryProtocol::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCQUERYADDRDIR)
	{
		pNew = new CEmcQueryAddrDir();
	}

	return pNew;
}
long CEmcQueryProtocol::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 160);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 120);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEmcQueryProtocol::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

