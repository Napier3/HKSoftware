//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StCfgDataWndBase.cpp  CStCfgDataWndBase


#include "stdafx.h"
#include "StCfgDataWndBase.h"

CStCfgDataWndBase::CStCfgDataWndBase()
{
	//初始化属性
	m_pCfgData = NULL;  //对应的配置数据对象
	m_pCfgDataWnd = NULL; 				 //配置窗体指针  具体的窗体引用

	//初始化成员变量
	m_szOrigin.cx = 0;
	m_szOrigin.cy = 0;

	m_dwCfgDataWndState = CFGDATAWND_STATE_MAX;
	m_pCfgDataParentWnd = NULL;
	m_bHasTitleButtons = TRUE;
	m_yPos = 0;
}

CStCfgDataWndBase::~CStCfgDataWndBase()
{
}


BOOL CStCfgDataWndBase::UICreate(CWnd *pParentWnd)
{
	UICreateOwn(pParentWnd);
	UICreateChildren(pParentWnd);
	return TRUE;
}


BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{//
	CDWordArray *padwCtrl = (CDWordArray*)lParam;
	padwCtrl->Add((DWORD)hwnd);
	return TRUE;
}

BOOL CStCfgDataWndBase::UICreateOwn(CWnd *pParentWnd)
{
	ASSERT (m_pCfgDataWnd != NULL);
	m_pCfgDataParentWnd = pParentWnd;

	CRect rcDataWnd;
	m_pCfgDataWnd->GetWindowRect(&rcDataWnd);

	m_szOrigin.cx = rcDataWnd.Width();
	m_szOrigin.cy = rcDataWnd.Height();   //原始大小
	
	if (!m_bHasTitleButtons)
	{
		return TRUE;
	}

	m_szMin.cx = m_szOrigin.cx;
	m_szMin.cy = STCFGDATAWND_TITLEBAR_CTRL_HEIGHT + ::GetSystemMetrics(SM_CYBORDER) * 2 + STCFGDATAWND_TITLEBAR_GAP;
	
	m_szOrigin.cy += m_szMin.cy;

	//遍历全部控件
	BOOL b = EnumChildWindows(m_pCfgDataWnd->m_hWnd, EnumChildProc, (LPARAM)&m_adwCtrls);

	long nCount = m_adwCtrls.GetCount();
	long nIndex = 0;
	long nOffset = STCFGDATAWND_TITLEBAR_GAP * 2 + STCFGDATAWND_TITLEBAR_CTRL_HEIGHT;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		HWND hWnd = (HWND)m_adwCtrls.GetAt(nIndex);

		if (::IsWindow(hWnd))
		{
			CRect rc;
			::GetWindowRect(hWnd, &rc);
			m_pCfgDataWnd->ScreenToClient(&rc);
			rc.top += nOffset;
			rc.bottom += nOffset;
			::MoveWindow(hWnd, rc.left, rc.top, rc.Width(), rc.Height(), TRUE);
		}
	}

	long nWidth = rcDataWnd.Width();

	long nLeft = STCFGDATAWND_TITLEBAR_GAP;
	long nRight = 0;
	CRect rcCtrl;
	rcCtrl.top = 2;
	rcCtrl.bottom = rcCtrl.top + STCFGDATAWND_TITLEBAR_CTRL_HEIGHT;

	long nWidthInfor = nWidth - STCFGDATAWND_TITLEBAR_WIDTH * 3 - STCFGDATAWND_TITLEBAR_GAP * 6 - ::GetSystemMetrics(SM_CXBORDER) * 2;
	rcCtrl.left = STCFGDATAWND_TITLEBAR_GAP;
	rcCtrl.right = rcCtrl.left + nWidthInfor;
	DWORD dwStyle = ES_LEFT | ES_READONLY | WS_VISIBLE | WS_BORDER;
 	m_edtInfor.Create(dwStyle, CRect(rcCtrl.left, rcCtrl.top, rcCtrl.right, rcCtrl.bottom + 2),m_pCfgDataWnd, ID_CFGDATA_BTN_INFOR);

	rcCtrl.left = rcCtrl.right + STCFGDATAWND_TITLEBAR_GAP;
	rcCtrl.right = rcCtrl.left + STCFGDATAWND_TITLEBAR_WIDTH;
	m_btnMin.Create(NULL,WS_VISIBLE | BS_BITMAP | BS_OWNERDRAW,rcCtrl,m_pCfgDataWnd,ID_CFGDATA_BTN_MIN);

	rcCtrl.left = rcCtrl.right + STCFGDATAWND_TITLEBAR_GAP;
	rcCtrl.right = rcCtrl.left + STCFGDATAWND_TITLEBAR_WIDTH;
	m_btnMax.Create(NULL,WS_VISIBLE | BS_BITMAP | BS_OWNERDRAW,rcCtrl,m_pCfgDataWnd,ID_CFGDATA_BTN_MAX);

	rcCtrl.left = rcCtrl.right + STCFGDATAWND_TITLEBAR_GAP;
	rcCtrl.right = rcCtrl.left + STCFGDATAWND_TITLEBAR_WIDTH;
	m_btnClose.Create(NULL,WS_VISIBLE | BS_BITMAP | BS_OWNERDRAW,rcCtrl,m_pCfgDataWnd,ID_CFGDATA_BTN_CLOSE);

	m_edtInfor.SetFont(&g_oGlobalFont);

	return TRUE;
}


void  CStCfgDataWndBase::ShowStCfgData(CStCfgDataBase *pCfgData)
{
	ShowStCfgDataOwn(pCfgData);
	ShowStCfgDataChildren(pCfgData);
}

void  CStCfgDataWndBase::SaveStCfgData()
{
	SaveStCfgDataOwn();
	SaveStCfgDataChildren();
}

void CStCfgDataWndBase::ShowTitle()
{
	if (!m_bHasTitleButtons)
	{
		return;
	}

	CString strTitle = GetTitle();
	m_edtInfor.SetWindowText(strTitle);
}

CSize CStCfgDataWndBase::GetDataWndSize()
{
	if (m_pCfgDataWnd == NULL)
	{
		return CSize(0, 0);
	}

	if (!m_bHasTitleButtons)
	{
		return m_szOrigin;
	}


	if (m_dwCfgDataWndState == CFGDATAWND_STATE_MIN)
	{
		CSize sz = m_szMin;
		sz.cy += ::GetSystemMetrics(SM_CXBORDER) * 2 + STCFGDATAWND_TITLEBAR_GAP * 2;
		return sz;
	}
	else
	{
		return m_szOrigin;
	}
}

void CStCfgDataWndBase::SetDataWndPos(long &nLeft, long &nTop)
{
	m_yPos = nTop;
	CSize sz = GetDataWndSize();
	m_pCfgDataWnd->MoveWindow(nLeft, nTop, sz.cx, sz.cy, TRUE);
	nTop += sz.cy;
}

void CStCfgDataWndBase::MoveDataWndPos(long &nLeft, long &nTop)
{
	SetDataWndPos(nLeft, nTop);
}

void CStCfgDataWndBase::ShowCfgDataWnd()	
{	
	if (m_pCfgDataWnd != NULL) 
	{	
		m_pCfgDataWnd->ShowWindow(SW_SHOW);
	}

	ShowTitle();
}

void CStCfgDataWndBase::HideCfgDataWnd()	
{	
	if (m_pCfgDataWnd != NULL) 
	{	
		m_pCfgDataWnd->ShowWindow(SW_HIDE);	
	}	
}


BOOL CStCfgDataWndBase::InitMinBtnBitmaps(UINT nIDBitmapResource,UINT nIDBitmapResourceSel,UINT nIDBitmapResourceFocus,UINT nIDBitmapResourceDisabled)
{
	return m_btnMin.LoadBitmaps(nIDBitmapResource, nIDBitmapResource, nIDBitmapResourceFocus, nIDBitmapResourceDisabled);
}

BOOL CStCfgDataWndBase::InitMaxBtnBitmaps(UINT nIDBitmapResource,UINT nIDBitmapResourceSel,UINT nIDBitmapResourceFocus,UINT nIDBitmapResourceDisabled)
{
	return m_btnMax.LoadBitmaps(nIDBitmapResource, nIDBitmapResource, nIDBitmapResourceFocus, nIDBitmapResourceDisabled);
}

BOOL CStCfgDataWndBase::InitCloseBtnBitmaps(UINT nIDBitmapResource,UINT nIDBitmapResourceSel,UINT nIDBitmapResourceFocus,UINT nIDBitmapResourceDisabled)
{
	return m_btnClose.LoadBitmaps(nIDBitmapResource, nIDBitmapResource, nIDBitmapResourceFocus, nIDBitmapResourceDisabled);
}

void CStCfgDataWndBase::PostDataWndMsg(UINT nMsg, WPARAM wPara, LPARAM lPara)
{
// 	CWnd *pParent = CWnd::GetParent();
	ASSERT (m_pCfgDataParentWnd != NULL);
	ASSERT (::IsWindow(m_pCfgDataParentWnd->m_hWnd));

	if (m_pCfgDataParentWnd != NULL)
	{
		m_pCfgDataParentWnd->PostMessage(nMsg, wPara, lPara);
	}
}


void CStCfgDataWndBase::_OnClose()
{
	UINT nDown = ::GetKeyState(VK_SHIFT) & 0x80 ;
	nDown += ::GetKeyState(VK_CONTROL) & 0x80;
	nDown += ::GetKeyState(VK_MENU) & 0x80;

	if (nDown == 384)
	{
		if (m_pCfgData != NULL)
		{
			SaveStCfgData();
			m_pCfgData->SaveCfgDefaultConfigFile();
			return;
		}
	}

	PostDataWndMsg(WM_CFGDATAWND_DELETE, (WPARAM)this, (LPARAM)this);
}

void CStCfgDataWndBase::_OnMin()
{
	if (m_dwCfgDataWndState == CFGDATAWND_STATE_MIN)
	{
		return;
	}

	m_dwCfgDataWndState = CFGDATAWND_STATE_MIN;
	PostDataWndMsg(WM_CFGDATAWNDS_CHANGED, (WPARAM)this, (LPARAM)this);
// 	CRect rcWnd;
// 	GetWindowRect(rcWnd);
// 	ScreenToClient(&rcWnd);
// 
// 	MoveWindow(nLeft, nTop, sz.cx, sz.cy, TRUE);
// 	nTop += sz.cy;
// 	
// 
// 	theApp.m_pConfigView->PostMessage(WM_CFGDATAWND_DELETE, (WPARAM)this, (LPARAM)this);
}

void CStCfgDataWndBase::_OnMax()
{
	if (m_dwCfgDataWndState == CFGDATAWND_STATE_MAX)
	{
		return;
	}

	m_dwCfgDataWndState = CFGDATAWND_STATE_MAX;
	PostDataWndMsg(WM_CFGDATAWNDS_CHANGED, (WPARAM)this, (LPARAM)this);
}


void CStCfgDataWndBase::AdjustCfgDataWndCtrls()
{
	
}

void CStCfgDataWndBase::SetCfgDataValue(long nDataID, float dValue)
{
	PostDataWndMsg(WM_CFGDATAWND_SETCFGDATAVALUE, (WPARAM)nDataID, (LPARAM)dValue);
}

