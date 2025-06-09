//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcDeviceModelFile.cpp  CEmcDeviceModelFile


#include "stdafx.h"
#include "EmcDeviceModelFile.h"

CEmcDeviceModelFile::CEmcDeviceModelFile()
{
	//初始化属性

	//初始化成员变量
	m_strName = _T("点表文件");
}

CEmcDeviceModelFile::~CEmcDeviceModelFile()
{
}

long CEmcDeviceModelFile::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	 
	return 0;
}

long CEmcDeviceModelFile::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CEmcDeviceModelFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);


	return 0;
}

void CEmcDeviceModelFile::InitAfterRead()
{
}

BOOL CEmcDeviceModelFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEmcDeviceModelFile *p = (CEmcDeviceModelFile*)pObj;



	return TRUE;
}

BOOL CEmcDeviceModelFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEmcDeviceModelFile *p = (CEmcDeviceModelFile*)pDest;


	return TRUE;
}

CBaseObject* CEmcDeviceModelFile::Clone()
{
	CEmcDeviceModelFile *p = new CEmcDeviceModelFile();
	Copy(p);
	return p;
}

long CEmcDeviceModelFile::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);

	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);

	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 0;
}

long CEmcDeviceModelFile::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 150);
	pListCtrl->InsertColumn(2, _T("点表文件"));
	pListCtrl->SetColumnWidth(2, 150);

	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

