// EpCapDatasListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "EpCapDatasListCtrlEx.h"
#include "..\MemBuffer\BinaryTextConvert.h"
#include "..\Protocol\101\EpGlobalDefine_101.h"

#include "Config\MonitorCapConfig.h"
// CEpCapDatasListCtrlEx


IMPLEMENT_DYNAMIC(CEpCapDatasListCtrlEx, CListCtrl)

CEpCapDatasListCtrlEx::CEpCapDatasListCtrlEx()
{
}

CEpCapDatasListCtrlEx::~CEpCapDatasListCtrlEx()
{
	
}


BEGIN_MESSAGE_MAP(CEpCapDatasListCtrlEx, CListCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CEpCapDatasListCtrlEx 消息处理程序


int CEpCapDatasListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

// 	// TODO:  在此添加您专用的创建代码
// 	this->ModifyStyle(NULL, LVS_OWNERDRAWFIXED);

	return 0;
}


BOOL CEpCapDatasListCtrlEx::CreateWatch(CRect rc, CWnd *pParent)
{
	CRect rectDummy;
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT;

	BOOL bRet = Create(dwStyle, rc, pParent, ID_EPCAP_DATA_LISTCTRL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	if (bRet)
	{
		InsertColumn(0, _T("条目号"), LVCFMT_LEFT, 50);
		InsertColumn(1, _T("名称"), LVCFMT_LEFT, 100);
		InsertColumn(2, _T("数据"), LVCFMT_LEFT, 60);
		InsertColumn(3, _T("时间"), LVCFMT_LEFT, 120);
	}

	return bRet;
}

void CEpCapDatasListCtrlEx::ShowResults(CEpDeviceDatas *pDeviceDatas, long nProtocol)
{
	DeleteAllItems();

	if (pDeviceDatas == NULL)
	{
		return;
	}

	POS pos = pDeviceDatas->GetHeadPosition();
	CEpY4Data *pData = NULL;
	long nIndex = 0;
	long nDataType = pDeviceDatas->m_nDeviceDataType;

	while (pos != NULL)
	{
		pData = pDeviceDatas->GetNext(pos);
		InsertItem(nIndex, NULL, 0);
		ShowResult(pData, nIndex, nDataType, nProtocol);
		nIndex++;
	}
}

void CEpCapDatasListCtrlEx::AddResults(CEpDeviceDatas *pDeviceDatas, long nProtocol)
{
	
}

void CEpCapDatasListCtrlEx::ShowResult(CEpY4Data *pDeviceData, long nIndex, long nDataType, long nProtocol)
{
	CString strText;

	strText.Format(_T("%d"), pDeviceData->m_nDataAddr);
	SetItemText(nIndex, 0, strText);

	CExBaseObject *pData = Ep_GetEdcmData(nProtocol, nDataType, pDeviceData->m_nDataAddr);
	if (pData != NULL)
	{
		strText = pData->m_strName;
	}
	else
	{
		strText = _T("---");
	}

	SetItemText(nIndex, 1, strText);

	strText = Ep_GetCapDataText(pDeviceData, nDataType);
	SetItemText(nIndex, 2, strText);

	if (pDeviceData->m_tm.n64Time > 0)
	{
		Ep_EPTIME64_To_String(pDeviceData->m_tm, strText);
		SetItemText(nIndex, 3, strText);
	}
}


