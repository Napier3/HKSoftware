#include "stdafx.h"
#include "TCtrlMsgRcvInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTCtrlMsgRcvInterface::CTCtrlMsgRcvInterface()
{
	m_pTCtrlMsgRcvWnd = NULL;
}

CTCtrlMsgRcvInterface::~CTCtrlMsgRcvInterface()
{

}
// void CTCtrlMsgRcvInterface::LogString(long nLevel, const CString &strMsg)
// {
// }

long CTCtrlMsgRcvInterface::OnTestBegin(CExBaseObject *pTestControl)
{
	return 0;
}

// void CTCtrlMsgRcvInterface::LogFormatString(long nLevel, const wchar_t *strFormat, ...)
// {
// #ifndef _PSX_QT_LINUX_
//     wchar_t strDest[1024];
// 	memset(strDest, 0, sizeof(wchar_t)*1024);
// 	*strDest = 0;
// 
// 	va_list argList;
// 	va_start( argList, strFormat );
// 	vswprintf_s( strDest, 1020, strFormat, argList );
// 	va_end( argList );
// 
// #ifdef _UNICODE
// 	LogString(nLevel, strDest);
// #else
// 	CString strMsg;
// 	strMsg = strDest;
// 	LogString(nLevel, strMsg);
// #endif
// 
// #endif
// }


CTCtrlMsgRcvInterfaceMngr::CTCtrlMsgRcvInterfaceMngr()
{

}

CTCtrlMsgRcvInterfaceMngr::~CTCtrlMsgRcvInterfaceMngr()
{

}

void CTCtrlMsgRcvInterfaceMngr::AddTCtrlMsgRcvInterface(CTCtrlMsgRcvInterface *p)
{
	//避免重复添加，因为可能在多个地方调用添加函数
	if (Find(p) == NULL)
	{
		AddTail(p);
	}
}

long CTCtrlMsgRcvInterfaceMngr::OnException(long nError, const CString &strError, CExBaseObject *pTestControl)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnException(nError, strError, pTestControl);
	}

	return 0;
}

long CTCtrlMsgRcvInterfaceMngr::OnConnectSuccess(CExBaseObject *pTestControl)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnConnectSuccess(pTestControl);
	}

	return 0;
}

long CTCtrlMsgRcvInterfaceMngr::OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnCurrItemStateChanged(pItem, bBringToTop);
	}

	return 0;
}

long CTCtrlMsgRcvInterfaceMngr::OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnCurrCharItemStateChanged(pItem, pObj);
	}

	return 0;
}

long CTCtrlMsgRcvInterfaceMngr::OnStopTest(long nType, CExBaseObject *pTestControl)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnStopTest(nType, pTestControl);
	}

	return 0;
}


long CTCtrlMsgRcvInterfaceMngr::OnUpdateMeasure(long nData, CExBaseObject *pTestControl)   //直流测试
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnUpdateMeasure(nData, pTestControl);
	}

	return 0;
}

BOOL CTCtrlMsgRcvInterfaceMngr::IsRunning(long nType, CExBaseObject *pTestControl)         //手动工作是否正在输出
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->IsRunning(nType, pTestControl);
	}

	return 0;
}

long CTCtrlMsgRcvInterfaceMngr::HideAllTestItemUI(long nData, CExBaseObject *pTestControl) //关闭手动工具
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->HideAllTestItemUI(nData, pTestControl);
	}

	return 0;
}

HWND CTCtrlMsgRcvInterfaceMngr::GetFrameHwnd()
{
	return 0;
}

void CTCtrlMsgRcvInterfaceMngr::ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate, BOOL bShow)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->ShowItemReport(pGbItem, bCreate, bShow);
	}
}

void CTCtrlMsgRcvInterfaceMngr::ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->ShowCharDraw(pGbItem, bShow);
	}
}

void CTCtrlMsgRcvInterfaceMngr::EditItemPara(CExBaseObject *pGbItem)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->EditItemPara(pGbItem);
	}
}

void CTCtrlMsgRcvInterfaceMngr::LocateItemReport(CExBaseObject *pGbItem)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->LocateItemReport(pGbItem);
	}
}

long CTCtrlMsgRcvInterfaceMngr::OnTestBegin(CExBaseObject *pTestControl)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnTestBegin(pTestControl);
	}

	return 0;
}

void CTCtrlMsgRcvInterfaceMngr::OnTestItemCount(long nCount, CExBaseObject *pTestControl)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnTestItemCount(nCount, pTestControl);
	}
}

void CTCtrlMsgRcvInterfaceMngr::OnExportRptEvent(CExBaseObject *pTestControl, const CString &strEventID)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->OnExportRptEvent(pTestControl, strEventID);
	}
}


void CTCtrlMsgRcvInterfaceMngr::InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->InsertItem(pParentItem, pSubItem);
	}
}

void CTCtrlMsgRcvInterfaceMngr::DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DeleteItem(pParentItem, pSubItem);
	}
}

void CTCtrlMsgRcvInterfaceMngr::InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	POS pos = GetHeadPosition();
	CTCtrlMsgRcvInterface *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->InsertItemEx(pParentItem, pSubItem);
	}
}

