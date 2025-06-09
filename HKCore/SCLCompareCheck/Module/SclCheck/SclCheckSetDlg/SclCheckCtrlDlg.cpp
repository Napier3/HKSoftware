// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "SCLCompareCheckDev.h"
#include "SclCheckCtrlDlg.h"
#include "..\..\SclCheckDataMngr\SclCheckObjectsSet.h"

// CSclCheckCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CSclCheckCtrlDlg, CDialog)

CSclCheckCtrlDlg::CSclCheckCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSclCheckCtrlDlg::IDD, pParent)
{
	m_cxMIn =  m_cyMin = 0;
	m_pCheckObjectsData = NULL;
}

CSclCheckCtrlDlg::~CSclCheckCtrlDlg()
{
}

void CSclCheckCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSclCheckCtrlDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(SCLCHECK_VIEW_CHOOSEALL, &CSclCheckCtrlDlg::OnChooseAllItems)
	ON_COMMAND(SCLCHECK_VIEW_CHOOSENULL, &CSclCheckCtrlDlg::OnChooseNullItems)
	ON_COMMAND(SCLCHECK_VIEW_CHOOSEINVERT, &CSclCheckCtrlDlg::OnChooseInvertItems)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CSclCheckCtrlDlg::ShowGridDatas(CExBaseList *pDatas )
{
	if (pDatas == NULL)
	{
		m_oSclCheckSettingDlgGrid.SetRowCount(1);
		m_oSclCheckSettingDlgGrid.Invalidate(FALSE);
		return ;
	}
	m_oSclCheckSettingDlgGrid.AttachDatas(pDatas);

	m_oSclCheckSettingDlgGrid.InitGridTitle();

	m_oSclCheckSettingDlgGrid.ShowDatas(pDatas);
	m_oSclCheckSettingDlgGrid.SelectRow(1);
}

int CSclCheckCtrlDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_cxMIn = lpCreateStruct->cx;
	m_cyMin = lpCreateStruct->cy;
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

BOOL CSclCheckCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rcGrid;
	GetClientRect(&rcGrid);

	rcGrid.top = 5;
	rcGrid.left = 5;
	rcGrid.right -= 5;
	rcGrid.bottom -= 5;

	m_oSclCheckSettingDlgGrid.Create(rcGrid, this, IDC_GRID_VIRLOOP_DLG_CTRL);
	m_oSclCheckSettingDlgGrid.SetFont(g_pGlobalFont);
	m_oSclCheckSettingDlgGrid.InitGrid();

	ShowGridDatas(m_pCheckObjectsData);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSclCheckCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!::IsWindow(m_oSclCheckSettingDlgGrid.m_hWnd))
	{
		return;
	}

	if (cx < m_cxMIn)
	{
		cx = m_cxMIn;
	}

	if (cy < m_cyMin)
	{
		cy = m_cyMin;
	}

	long nHeight = 0;
	CRect rc(IECCFG_CTRL_GAP, IECCFG_CTRL_GAP, cx - 2*IECCFG_CTRL_GAP, cy - nHeight - 2*IECCFG_CTRL_GAP);
	m_oSclCheckSettingDlgGrid.MoveWindow(rc);
}

void CSclCheckCtrlDlg::OnChooseAllItems()
{
	ASSERT(m_pCheckObjectsData != NULL);
	POS pos01 = m_pCheckObjectsData->GetHeadPosition();
	CExBaseList *pExBaseList = NULL;

	while(pos01 != NULL)
	{
		pExBaseList = (CExBaseList *)m_pCheckObjectsData->GetNext(pos01);

		if (pExBaseList->GetClassID() == SCLCLASSID_SCHEMACCHECKOBJECT)
		{
			((CSchemaCheckObject*)pExBaseList)->m_nChoose = 1;
		}
		else if (pExBaseList->GetClassID() == SCLCLASSID_CCHECKOBJECT)
		{
			((CCheckObject*)pExBaseList)->m_nChoose = 1;
		}
		else if (pExBaseList->GetClassID() == SCLCLASSID_ADDTEMPLATESELEMENT)
		{
			((CAddTempsElement*)pExBaseList)->m_nChoose = 1;
		}
	}

	ShowGridDatas(m_pCheckObjectsData);
}

void CSclCheckCtrlDlg::OnChooseNullItems()
{
	ASSERT(m_pCheckObjectsData != NULL);
	POS pos01 = m_pCheckObjectsData->GetHeadPosition();
	CExBaseList *pExBaseList = NULL;

	while(pos01 != NULL)
	{
		pExBaseList = (CExBaseList *)m_pCheckObjectsData->GetNext(pos01);

		if (pExBaseList->GetClassID() == SCLCLASSID_SCHEMACCHECKOBJECT)
		{
			((CSchemaCheckObject*)pExBaseList)->m_nChoose = 0;
		}
		else if (pExBaseList->GetClassID() == SCLCLASSID_CCHECKOBJECT)
		{
			((CCheckObject*)pExBaseList)->m_nChoose = 0;
		}
		else if (pExBaseList->GetClassID() == SCLCLASSID_ADDTEMPLATESELEMENT)
		{
			((CAddTempsElement*)pExBaseList)->m_nChoose = 0;
		}
	}

	ShowGridDatas(m_pCheckObjectsData);
}

void CSclCheckCtrlDlg::OnChooseInvertItems()
{
	ASSERT(m_pCheckObjectsData != NULL);
	POS pos01 = m_pCheckObjectsData->GetHeadPosition();
	CExBaseList *pExBaseList = NULL;

	while(pos01 != NULL)
	{
		pExBaseList = (CExBaseList *)m_pCheckObjectsData->GetNext(pos01);

		if (pExBaseList->GetClassID() == SCLCLASSID_SCHEMACCHECKOBJECT)
		{
			if (((CSchemaCheckObject*)pExBaseList)->m_nChoose)
			{
				((CSchemaCheckObject*)pExBaseList)->m_nChoose = 0;
			}
			else
			{
				((CSchemaCheckObject*)pExBaseList)->m_nChoose = 1;
			}
		}
		else if (pExBaseList->GetClassID() == SCLCLASSID_CCHECKOBJECT)
		{
			if (((CCheckObject*)pExBaseList)->m_nChoose)
			{
				((CCheckObject*)pExBaseList)->m_nChoose = 0;
			}
			else
			{
				((CCheckObject*)pExBaseList)->m_nChoose = 1;
			}
		}
		else if (pExBaseList->GetClassID() == SCLCLASSID_ADDTEMPLATESELEMENT)
		{
			if (((CAddTempsElement*)pExBaseList)->m_nChoose)
			{
				((CAddTempsElement*)pExBaseList)->m_nChoose = 0;
			}
			else
			{
				((CAddTempsElement*)pExBaseList)->m_nChoose = 1;
			}
		}
	}

	ShowGridDatas(m_pCheckObjectsData);
}

void CSclCheckCtrlDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
//	CPoint point;
	CRect rect;
	GetWindowRect(rect);

	point.x -= rect.left;
	point.y -= rect.top;

	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();

	SetFocus();

	menu.AppendMenu(MF_STRING,SCLCHECK_VIEW_CHOOSEALL,_T("全部选中"));
	menu.AppendMenu(MF_STRING,SCLCHECK_VIEW_CHOOSENULL,_T("全部取消"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING,SCLCHECK_VIEW_CHOOSEINVERT,_T("反向选中"));

	if (menu.GetMenuItemCount() > 0)
	{
		//CUIWndThread::Attach_Wnd_WM_COMMAND(this);
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y, this);
		//资源回收
		//CUIWndThread::Attach_Wnd_WM_COMMAND(NULL);
		HMENU hmenu=menu.Detach();			
		menu.DestroyMenu();	
	}
}
