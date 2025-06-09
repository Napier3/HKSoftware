// UICommCmdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UICommCmdDlg.h"
#include "../TestControl/TestControlWnd.h"
#include "../TestControl/TestControl.h"
#include "../../../Module/api/GloblaDrawFunctions.h"

#include "CommCmdGrid_Analogs.h"
// CUICommCmdDlg 对话框

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CUICommCmdDlg, CDialog)

CUICommCmdDlg::CUICommCmdDlg(CWnd* pParent /*=NULL*/)
//: CDialog(CUICommCmdDlg::IDD, pParent)
{
	m_lfFont = InitLogFont();
#ifdef UNICODE
	lstrcpy(m_lfFont.lfFaceName,_T("Tahoma"));
#else
	strcpy(m_lfFont.lfFaceName, _T("Tahoma"));
#endif // UNICODE

	m_lfFont.lfHeight = 16;
	m_lfFont.lfWeight = 0;
	m_font.CreateFontIndirect(&m_lfFont);
	m_lfFont.lfHeight = 14;
	m_fontRsltCtrl.CreateFontIndirect(&m_lfFont);
	m_pGridCmdDatas = NULL;
}

CUICommCmdDlg::~CUICommCmdDlg()
{
	m_listNodeDatas.RemoveAll();
	m_setCpu.RemoveAll();

	if (m_pGridCmdDatas != NULL)
	{
		m_pGridCmdDatas->DestroyWindow();
		delete m_pGridCmdDatas;
		m_pGridCmdDatas = NULL;
	}
}

void CUICommCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUICommCmdDlg, CDialog)
	ON_BN_CLICKED(IDC_SYSEDIT_BTN_OK, &CUICommCmdDlg::OnBnClickedOk)
	ON_MESSAGE(WM_GRID_END_EDIT,  &CUICommCmdDlg::OnEndEdit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_SYSEDIT_TAB_PARASEL_0, &CUICommCmdDlg::OnSelchangeTab1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CUICommCmdDlg 消息处理程序

void CUICommCmdDlg::OnBnClickedOk()
{
	ShowWindow(SW_HIDE);

	//发送消息给TestControl，测试完成，填写报告
	if(m_pWndMsgRcv)
	{
		m_pWndMsgRcv->PostMessage(WM_COMMCMD_TEST_FINISHED, (WPARAM)m_pTestItemCommCmd, 1);
	}
}


void CUICommCmdDlg::OnCancel()
{
}

void CUICommCmdDlg::OnOK()
{
}

void CUICommCmdDlg::OnClose()
{
	//停止测试
	ASSERT (m_pWndMsgRcv != NULL);
	if(m_pWndMsgRcv)
	{
		m_pWndMsgRcv->PostMessage(WM_COMMCMD_TEST_FINISHED, (WPARAM)m_pTestItemCommCmd, 0);
	}

	ShowWindow(SW_HIDE);
}

BOOL CUICommCmdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitMacroRect();

	MoveWindow(&rectWin);
	CenterWindow();

	DWORD dwStyle = BS_PUSHBUTTON;
	m_btnNext.Create(/*g_strTestBtnOK_Next*/g_sLangTxt_NextStep,dwStyle,rectBtnNext,this,IDC_SYSEDIT_BTN_OK);
	m_btnNext.SetFont(&m_font);
	m_btnNext.MoveWindow(&rectBtnNext);
	m_btnNext.ShowWindow(SW_SHOW);

	m_tabParaSel.Create(dwStyle,rectTab,this,IDC_SYSEDIT_TAB_PARASEL_0);
	m_tabParaSel.SetFont(&m_font);
	m_tabParaSel.MoveWindow(&rectTab);
	m_tabParaSel.ShowWindow(SW_SHOW);

	return TRUE;
}

void CUICommCmdDlg::CreateCommCmdGrid()
{
	if (m_pGridCmdDatas != NULL)
	{
		delete m_pGridCmdDatas;
		m_pGridCmdDatas = NULL;
	}

// 	if (m_strType == g_strRAnalog)
// 	{
// 		m_pGridCmdDatas = new CCommCmdGrid_Analogs();
// 	}

	if (m_pGridCmdDatas == NULL)
	{
		return;
	}
		
	m_pGridCmdDatas->Create(rectGrid, this, IDC_SYSEDIT_RELAYSETGRID);
	m_pGridCmdDatas->SetFont(&m_font);
	m_pGridCmdDatas->MoveWindow(&rectGrid);
	m_pGridCmdDatas->ShowWindow(SW_SHOW);
	m_pGridCmdDatas->InitGrid();
}

void CUICommCmdDlg::InitTestItem(CCommCmd* pTestItemCommCmd, CTestControlWnd *pWndMsgRcv)
{
	m_listNodeDatas.RemoveAll();
	m_setCpu.RemoveAll();

	m_pWndMsgRcv = pWndMsgRcv;
	ASSERT (pTestItemCommCmd != NULL);

	if (pTestItemCommCmd == NULL)
	{
		return;
	}

	SetWindowText(pTestItemCommCmd->GetName());
	m_pTestItemCommCmd = pTestItemCommCmd;
	m_strType = pTestItemCommCmd->GetCommCmdID();
	m_pCurDevice = (CDevice*)pTestItemCommCmd->GetAncestor(GBCLASSID_DEVICE);
	ASSERT(m_pCurDevice != NULL);
	CreateCommCmdGrid();
	m_tabParaSel.DeleteAllItems();
	InitTabandCpu();

	if (m_pWndMsgRcv->m_pTestControl->HasNextItemNeedTest())
	{
		m_btnNext.SetWindowText(/*g_strTestBtnOK_Next*/g_sLangTxt_NextStep);
	}
	else
	{
		m_btnNext.SetWindowText(/*g_strTestBtnOK_Finish*/g_sLangTxt_Finish);
	}

	ShowWindow(SW_SHOW);
}

void CUICommCmdDlg::FinishTestCmmCmdItem()
{
	
}

void CUICommCmdDlg::FinishTestItem()
{
	FinishTestCmmCmdItem();
	m_btnNext.EnableWindow(TRUE);
}

LRESULT CUICommCmdDlg::OnEndEdit(WPARAM wParam, LPARAM lParam)
{
	long nCol,nRow;
	nCol = lParam & 0x0FFFF;
	nRow = (lParam>>16) & 0x0FFFF;

	m_pGridCmdDatas->SaveValue(nRow, nCol);

	return 0;
}


void CUICommCmdDlg::InitTabandCpu()
{
	CCpus* pCpus = m_pCurDevice->GetCpus();
	CCpu* pCpu = NULL;
	long nIndex = 0;
	POS pos = NULL;

	m_listNodeDatas.RemoveAll();
	m_setCpu.RemoveAll();

	CCmd *pCmd = m_pTestItemCommCmd->GetCmd();
	pCpu = (CCpu*)pCpus->FindByID(pCmd->m_strDatasetPath);

	if (pCpu != NULL)
	{
		m_setCpu.AddTail(pCpu);
	}
	else
	{
		pos = pCpus->GetHeadPosition();

		while (pos != NULL)
		{
			pCpu = (CCpu*)pCpus->GetNext(pos);
			m_setCpu.AddTail(pCpu);
		}
	}

	CString strType = m_pTestItemCommCmd->m_strCommCmdID;

	pos = m_setCpu.GetHeadPosition();

	while (pos != NULL)
	{
		pCpu = (CCpu*)m_setCpu.GetNext(pos);

// 		if (strType == g_strRAnalog)
// 		{
// 			m_listNodeDatas.Append(pCpu->m_pAnalogs);
// 		}
	}

	//初始化Tab页
	nIndex = 0;
	pos = m_setCpu.GetHeadPosition();

	while (pos != NULL)
	{
		pCpu = (CCpu*)m_setCpu.GetNext(pos);
		m_tabParaSel.InsertItem(nIndex, pCpu->m_strName, nIndex);
		nIndex++;
	}

	if(m_tabParaSel.GetItemCount()>0)
	{
		m_tabParaSel.SetCurSel(0);
	}

	ChangeCurCpu( (CCpu*)m_setCpu.GetHead());
}

void CUICommCmdDlg::ChangeCurCpu(CCpu* pChangeCpu)
{
	m_pCurCpu = pChangeCpu;
	CCpus* pCpus = m_pCurDevice->GetCpus();

	if (m_pGridCmdDatas != NULL)
	{
		m_pGridCmdDatas->InitVariables(m_pCurCpu);
	}
}

void CUICommCmdDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SetFocus();

	int iCurSel = m_tabParaSel.GetCurSel();
	CCpu* pCpu;
	pCpu = (CCpu*)m_setCpu.GetAtIndex(iCurSel);

	if(pCpu != NULL)
	{
		ChangeCurCpu(pCpu);
	}

	*pResult = 0;
}

//初始化RECT
void CUICommCmdDlg::InitMacroRect()
{
	rectWin.top = SYSEDIT_WIN_TOP;
	rectWin.bottom = SYSEDIT_WIN_BOTTOM;
	rectWin.left = SYSEDIT_WIN_LEFT;
	rectWin.right= SYSEDIT_WIN_RIGHT;

	rectTab.top = SYSEDIT_Tab_TOP;
	rectTab.bottom = SYSEDIT_Tab_BOTTOM;
	rectTab.left = SYSEDIT_Tab_LEFT;
	rectTab.right= SYSEDIT_Tab_RIGHT;

	rectGrid.top = SYSEDIT_Grid_TOP;
	rectGrid.bottom = SYSEDIT_Grid_BOTTOM;
	rectGrid.left = SYSEDIT_Grid_LEFT;
	rectGrid.right= SYSEDIT_Grid_RIGHT;

	rectBtnNext.top = SYSEDIT_BTN_NEXT_TOP;
	rectBtnNext.bottom = SYSEDIT_BTN_NEXT_BOTTOM;
	rectBtnNext.left = SYSEDIT_BTN_NEXT_LEFT;
	rectBtnNext.right= SYSEDIT_BTN_NEXT_RIGHT;
}

