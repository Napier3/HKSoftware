// SclFileTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SclFileTreeView.h"
#include "SclFileFrame.h"

#include "..\..\Module\XLanguage\XLangWndAdjust.h"//20161013

#define SCL_FILE_READ_TIMER_ID    2036
// CSclFileTreeView

IMPLEMENT_DYNCREATE(CSclFileTreeView, CFormView)

CSclFileTreeView::CSclFileTreeView()
	: CFormView(CSclFileTreeView::IDD)
{
// 	m_pDlgSclReadProgress = NULL;
	m_pSclFileCtrlView = NULL;
	m_nBtnHeight = 23;
	m_pSclFileRead = NULL;
}

CSclFileTreeView::~CSclFileTreeView()
{
	m_oSelectedSclCtrls.RemoveAll();
	FreeSclFileRead();
}

void CSclFileTreeView::ShowSelectIED(const CString &strIedId)
{
//	m_treeSclIecCfg.SetCurrIedID(strIedId);
	m_treeSclIecCfg.AttachMsgRcvWnd(m_pSclFileCtrlView);
	m_treeSclIecCfg.ShowSelectIED(strIedId);
	//CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
	//m_treeSclIecCfg.ShowIecfgSclIeds(&pSclFileFrame->m_oSclStation);
	theApp.m_pCurrSelSclIed = m_treeSclIecCfg.GetCurrSelIed();
}

void CSclFileTreeView::UpdateSclCtrl(CSclCtrlBase *pSclCtrlBase)
{
	if (pSclCtrlBase->m_nSelect)
	{
		m_oSelectedSclCtrls.AddTail(pSclCtrlBase);
	} 
	else
	{
		m_oSelectedSclCtrls.Remove(pSclCtrlBase);
	}

	ShowGridDatas();
}

void CSclFileTreeView::ShowGridDatas()
{
	m_oIecCfgCtrlsGrid.ShowDatas(&m_oSelectedSclCtrls);
}

void CSclFileTreeView::AddGridCtrls(CSclCtrls *pSclCtrls)
{
	CSclCtrlBase *pObj = NULL;
	POS pos = pSclCtrls->GetHeadPosition();
	CString strTmp;

	while(pos)
	{
		pObj = (CSclCtrlBase*)pSclCtrls->GetNext(pos);

		if (m_oSelectedSclCtrls.Find(pObj) == NULL)
		{
			m_oSelectedSclCtrls.AddTail(pObj);
		} 
		else if (pObj->m_nSelect == 1)
		{
			strTmp.Format(_T("0x%04X"),pObj->GetAppID());
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前控制块(%s)已添加."),strTmp.GetString());
		}
		else if (pObj->m_nSelect == 0)
		{
			m_oSelectedSclCtrls.Remove(pObj);
		}
	}
}

CSclFileRead* CSclFileTreeView::GetSclFileRead()
{
	if (m_pSclFileRead == NULL)
	{
		m_pSclFileRead = new CSclFileRead();
	}

	CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
	pSclFileFrame->m_pSclFileRead = m_pSclFileRead;
	return m_pSclFileRead;
}

void CSclFileTreeView::FreeSclFileRead()
{
	if (m_pSclFileRead != NULL)
	{
		delete m_pSclFileRead;
		m_pSclFileRead = NULL;
	}
}

void CSclFileTreeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeSclIecCfg);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_cmbFilter);
	DDX_Control(pDX, IDC_BTN_FILTER, m_btnFilter);
	DDX_Control(pDX, IDC_CUSTOM_IECCFG_CTRLS_GRID, m_oIecCfgCtrlsGrid);
}

BEGIN_MESSAGE_MAP(CSclFileTreeView, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_SCLFILE_READ_FINISH, OnSclReadFinish)
	ON_BN_CLICKED(IDC_BTN_FILTER, &CSclFileTreeView::OnBnClickedBtnFilter)
END_MESSAGE_MAP()


// CSclFileTreeView 诊断

#ifdef _DEBUG
void CSclFileTreeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSclFileTreeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSclFileTreeView 消息处理程序

void CSclFileTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CSclFile *pSclFile = (CSclFile*)lHint;

	if (pSclFile != NULL)
	{
		m_pSclFile = pSclFile;
		SetTimer(SCL_FILE_READ_TIMER_ID, 50, NULL);
	}
}


void CSclFileTreeView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);

// 	if (!::IsWindow(m_treeSclIecCfg.m_hWnd))
// 	{
// 		return;
// 	}
// 
// 	if (cx < 160)
// 	{
// 		cx = 160;
// 	}
// 
// 	if (cy < 100)
// 	{
// 		cy = 100;
// 	}
// 
// 	long nHigh = cy - IECCFG_CTRL_GAP * 4;
// 	float fTreeCoef = 0.6f;
// 	long nTreeBottom = fTreeCoef*nHigh + IECCFG_CTRL_GAP;
// 	long nGridBottom = nHigh +m_nBtnHeight + 3*IECCFG_CTRL_GAP;
// 	CRect rc;
// 
// 	rc.left = IECCFG_CTRL_GAP;
// 	rc.top = IECCFG_CTRL_GAP;
// 	rc.right = cx - IECCFG_CTRL_GAP;
// 	rc.bottom = nTreeBottom;
// 	m_treeSclIecCfg.MoveWindow(rc);
// 
// 	rc.top = rc.bottom + IECCFG_CTRL_GAP;
// 	rc.bottom = rc.top + m_nBtnHeight;
// 	rc.left = rc.right - 60;
// 	m_btnFilter.CButton::MoveWindow(rc);
// 
// 	rc.right = rc.left - IECCFG_CTRL_GAP;
// 	rc.left = IECCFG_CTRL_GAP;
// 	rc.bottom = rc.top + 200;
// 	m_cmbFilter.MoveWindow(rc);
// 
// 	rc.left = IECCFG_CTRL_GAP;
// 	rc.top = rc.bottom + IECCFG_CTRL_GAP;
// 	rc.right = cx - IECCFG_CTRL_GAP;
// 	rc.bottom = nGridBottom;
// 	m_oIecCfgCtrlsGrid.MoveWindow(rc);
}
void CSclFileTreeView::xlang_InitAndAdjust()   //2016.10.14
{
	if (xlang_IsCurrXLanguageChinese())   //2016.10.14
	{
		return;    //2016.10.14
	}

	m_btnFilter.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnFilter);//2016.10.14

	CXLangWndAdjMngr oWndAdjMngr;//2016.10.14
	oWndAdjMngr.RegisterCols();//2016.10.14   注册（添加）一个列集合对象（即行的概念）
	oWndAdjMngr.RegisterXCol(&m_btnFilter);//2016.10.14

	oWndAdjMngr.Adjust(this, TRUE);//2016.10.14

}

void CSclFileTreeView::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);

	CXUIAdjItem_Wnd *pWnd = NULL;
	pWnd = XUI_AddWnd(IDC_TREE1,0,0,1.0f, 0.6f);
	pWnd = XUI_AddWnd(IDC_COMBO_FILTER,0,0.6f,1.0f, 0);
	pWnd = XUI_AddWnd(IDC_BTN_FILTER,1.0f,0.6f,0.0f, 0);
	pWnd = XUI_AddWnd(IDC_CUSTOM_IECCFG_CTRLS_GRID,	0,0.6,1.0f, 0.4f);

	CXUIAdjItem_Area::XUI_OnSize();
}

void CSclFileTreeView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CRect rc;
	m_btnFilter.GetWindowRect(&rc);
	m_nBtnHeight = rc.Height();

	xlang_InitAndAdjust(); //2016.10.14   【此句放在下列窗口调整之前】

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SclFilterText.xml");
	m_oFilterTextMngr.OpenXmlFile(strFile);
	m_cmbFilter.SetAddEmptyString(TRUE);
	m_cmbFilter.InitFilterText(&m_oFilterTextMngr);
	m_treeSclIecCfg.SetIDB_SclData(IDB_BITMAP_SCLDATA);

	m_oIecCfgCtrlsGrid.InitGrid();
//	m_oIecCfgCtrlsGrid.AttachDataViewOptrInterface(this);
//	m_oIecCfgCtrlsGrid.SetEditable(FALSE);
	m_oIecCfgCtrlsGrid.ShowDatas(&m_oSelectedSclCtrls);
	XUI_InitAdjust();
}

void CSclFileTreeView::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);

	m_treeSclIecCfg.AttachMsgRcvWnd(m_pSclFileCtrlView);
	GetSclFileRead();
	CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
	m_pSclFileRead->ReadSclFile(m_pSclFile->m_strID, this, &pSclFileFrame->m_oSclStation);
	CFormView::OnTimer(nIDEvent);
}


LRESULT CSclFileTreeView::OnSclReadFinish(WPARAM wParam, LPARAM lParam)
{
	if (SCLFILE_READ_FINISH == lParam)
	{
// 		m_pDlgSclReadProgress->ShowWindow(SW_HIDE);
// 		delete m_pDlgSclReadProgress;
// 		m_pDlgSclReadProgress = NULL;
		CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;

		if (CIecCfgTool::LinkGout())
		{
			pSclFileFrame->m_oSclStation.InitGoutCh_VirtualTerminals();
		}

#ifdef SCL_USE_MMS_STRING_
		pSclFileFrame->m_oSclStation.SaveStationFile();
#else
		pSclFileFrame->m_oSclStation.SaveStationFile();
		FreeSclFileRead();
#endif
	}
	else if (SCLFILE_READ_SHOW == lParam)
	{
		CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
		m_treeSclIecCfg.ShowIecfgSclIeds(&pSclFileFrame->m_oSclStation);
// 		CRect rcClient;
// 		GetWindowRect(&rcClient);
// 		CRect rcDlg;
// 		//m_pDlgSclReadProgress->GetWindowRect(&rcDlg);
// 		long nWidth = rcDlg.Width();
// 		long nHeight = rcDlg.Height();
// 
// 		rcDlg.right = rcClient.right;
// 		rcDlg.bottom = rcClient.bottom;
// 		rcDlg.left = rcDlg.right - nWidth;
// 		rcDlg.top = rcDlg.bottom - nHeight;
// 		//m_pDlgSclReadProgress->MoveWindow(rcDlg);
	}
	else if (SCLFILE_READ_DELCTRLS == lParam)
	{
		CSclCtrls *pCtrls = (CSclCtrls*)wParam;
		CSclIed *pIed = (CSclIed*)pCtrls->GetParent();
		m_treeSclIecCfg.DeleteItem((HTREEITEM)pCtrls->m_dwItemData);
		pIed->DeleteCtrls(pCtrls);
	}

	return 0;
}

void CSclFileTreeView::OnBnClickedBtnFilter()
{
	CString strFilterText;

	if (!m_cmbFilter.GetFilterText(strFilterText))
	{
		return;
	}

	m_treeSclIecCfg.Filter(strFilterText);
}
