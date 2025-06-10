// SclFileCtrlView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SclFileCtrlView.h"
#include "..\Module\IecCfgSclTool\SclToIecCfgTool.h"
#include "..\Module\SCL\SclGsInCtrlsToDinWzdTools.h"
#include "SclFileFrame.h"
#include "SclFileTreeView.h"

#include "..\..\Module\XLanguage\XLangWndAdjust.h"//20161013
#include "TestEngine.h"
// CSclFileCtrlView

IMPLEMENT_DYNCREATE(CSclFileCtrlView, CFormView)

CSclFileCtrlView::CSclFileCtrlView()
	: CFormView(CSclFileCtrlView::IDD)
{
	m_cxMIn =  m_cyMin = 0;
	m_nOldSclDatasClassID = 0;
	m_pCurrSelSclCtrls = NULL;
	m_pSclFileTreeView = NULL;
}

CSclFileCtrlView::~CSclFileCtrlView()
{
}

void CSclFileCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADDTO, m_btnAddTo);
	DDX_Control(pDX, IDC_COMBO_IECCFG_FILE, m_cmbIecCfgFile);
	DDX_Control(pDX, IDC_COMBO_IECCFG_TYPE, m_cmbIecCfgType);
	DDX_Control(pDX, IDC_BTN_OVERRITE, m_btnOverwrite);
	DDX_Control(pDX, IDC_BTN_COMPARE, m_btnCompare);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btnExport);
	//	DDX_Control(pDX, IDC_CHECK_ALL, m_btnAllSel);
	DDX_Control(pDX, IDC_BTN_ONE_KEY_CFG, m_btnOneKeyCfg);
}

BEGIN_MESSAGE_MAP(CSclFileCtrlView, CFormView)
	ON_MESSAGE(WM_SCLIECCFGCTRL_SELECTED, OnSclIecCfgCtrlSelected)
	ON_MESSAGE(WM_SCLIECCFGCTRLS_SELECTED, OnSclIecCfgCtrlsSelected)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_ADDTO, &CSclFileCtrlView::OnBnClickedBtnAddto)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_OVERRITE, &CSclFileCtrlView::OnBnClickedBtnOverrite)
	ON_BN_CLICKED(IDC_BTN_COMPARE, &CSclFileCtrlView::OnBnClickedBtnCompare)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CSclFileCtrlView::OnBnClickedBtnExport)
//	ON_BN_CLICKED(IDC_CHECK_ALL, &CSclFileCtrlView::OnBnClickedCheckAll)
	ON_CBN_SELCHANGE(IDC_COMBO_IECCFG_FILE, &CSclFileCtrlView::OnCbnSelchangeComboIeccfgFile)
	ON_CBN_SELCHANGE(IDC_COMBO_IECCFG_TYPE, &CSclFileCtrlView::OnCbnSelchangeComboIeccfgType)
	ON_BN_CLICKED(IDC_BTN_ONE_KEY_CFG, &CSclFileCtrlView::OnBnClickedBtnOneKeyCfg)
END_MESSAGE_MAP()


// CSclFileCtrlView 诊断

#ifdef _DEBUG
void CSclFileCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSclFileCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSclFileCtrlView 消息处理程序


LRESULT CSclFileCtrlView::OnSclIecCfgCtrlSelected(WPARAM wParam, LPARAM lParam)
{
	CSclCtrlBase *pSclCtrlBase = (CSclCtrlBase*)wParam;

	if (pSclCtrlBase == NULL)
	{
		return 0;
	}

	if (m_pSclFileTreeView == NULL)
	{
		return 0;
	}

	CSclFileTreeView *pSclFileTreeView = (CSclFileTreeView*)m_pSclFileTreeView;
	pSclFileTreeView->UpdateSclCtrl(pSclCtrlBase);
	return 0;
}

LRESULT CSclFileCtrlView::OnSclIecCfgCtrlsSelected(WPARAM wParam, LPARAM lParam)
{
	m_pCurrSelSclCtrls = (CSclCtrls*)wParam;

	if (m_pCurrSelSclCtrls == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("当前选择的控制块为空."));
		return 0;
	}

	theApp.m_pCurrSelSclIed = (CSclIed*)m_pCurrSelSclCtrls->GetParent();

	ShowGridDatas(m_pCurrSelSclCtrls);
	InitComboBoxIecCfgType(m_pCurrSelSclCtrls);

	return 0;
}

void CSclFileCtrlView::ShowGridDatas(CExBaseList *pDatas)
{
	if (pDatas == NULL)
	{
		m_oSclIecCfgCtrlGrid.SetRowCount(1);
		m_oSclIecCfgCtrlGrid.Invalidate(FALSE);
		m_pChsView->ShowDatas(NULL);
		return ;
	}

	//ASSERT (m_pSclFile != NULL);
	m_oSclIecCfgCtrlGrid.AttachDatas(pDatas);//&pSclFileFrame->m_oSclStation);
	m_oSclIecCfgCtrlGrid.InitGridTitle();
	CSclCtrls *pSclCtrls = (CSclCtrls*)pDatas;

	if (!pSclCtrls->IsRead())
	{
		m_oSclIecCfgCtrlGrid.SetRowCount(1);
		return ;
	}

	m_oSclIecCfgCtrlGrid.AttachDataViewOptrInterface(m_pChsView);
	m_oSclIecCfgCtrlGrid.ShowDatas(pDatas);
	m_oSclIecCfgCtrlGrid.SelectRow(1);

	CExBaseList *pSelCtrl = (CExBaseList*)pDatas->GetHead();
	m_pChsView->ShowDatas(pSelCtrl);

	POS pos = pDatas->GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;
	long nTotalCount = 0, nRefTotalCount = 0;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase*)pDatas->GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if (nClassID == SCLIECCLASSID_CTRL_GS_OUT || nClassID == SCLIECCLASSID_CTRL_SMV_OUT)
		{
			break;
		}

		if (nClassID == SCLIECCLASSID_CTRL_SMV_IN)
		{
			nRefTotalCount += ((CSclCtrlSmvIn*)pSclCtrl)->m_nChnRefCount;
		}
		else
		{
			nRefTotalCount += ((CSclCtrlGsIn*)pSclCtrl)->m_nChnRefCount;
		}

		nTotalCount += pSclCtrl->m_nChnCount;
	}

	if (nTotalCount > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("内部连线总通道数：%d； 实际输出控制块总通道数：%d"), nTotalCount, nRefTotalCount);
	}
}

void CSclFileCtrlView::InitComboBoxIecCfgType(CExBaseList *pDatas)
{
	if (pDatas == NULL)
	{
		m_cmbIecCfgType.ResetContent();
		return;
	}

	UINT nClassID = pDatas->GetClassID();

	if ((nClassID == SCLIECCLASSID_CTRLS_GS_IN)&&(g_nEngineDispMode == _DISP_MODE_NORMAL))
	{
		m_btnExport.ShowWindow(SW_SHOW);
	}
	else
	{
		m_btnExport.ShowWindow(SW_HIDE);
	}

	if ( (nClassID == SCLIECCLASSID_CTRLS_SMV_OUT || nClassID == SCLIECCLASSID_CTRLS_SMV_IN)
		 && (m_nOldSclDatasClassID == SCLIECCLASSID_CTRLS_SMV_OUT || m_nOldSclDatasClassID == SCLIECCLASSID_CTRLS_SMV_IN) )
	{
		return;
	}

	if ( (nClassID == SCLIECCLASSID_CTRLS_GS_OUT || nClassID == SCLIECCLASSID_CTRLS_GS_IN)
		&& (m_nOldSclDatasClassID == SCLIECCLASSID_CTRLS_GS_OUT || m_nOldSclDatasClassID == SCLIECCLASSID_CTRLS_GS_IN) )
	{
		return;
	}

	m_nOldSclDatasClassID = nClassID;
	long nIndex = 0;
	m_cmbIecCfgType.ResetContent();

	if ( nClassID == SCLIECCLASSID_CTRLS_SMV_OUT || nClassID == SCLIECCLASSID_CTRLS_SMV_IN)
	{
		nIndex = m_cmbIecCfgType.AddString(CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecSMVCfg/*_T("SMV配置")*/);
		m_cmbIecCfgType.SetItemData(nIndex, CFGCLASSID_CIECCFGDATASSMV);
		m_cmbIecCfgType.SetCurSel(0);
	}
	else if ( nClassID == SCLIECCLASSID_CTRLS_GS_OUT || nClassID == SCLIECCLASSID_CTRLS_GS_IN)
	{
		nIndex = m_cmbIecCfgType.AddString(_T("GOOSE订阅"));
		m_cmbIecCfgType.SetItemData(nIndex, CFGCLASSID_CIECCFGDATASGIN);

		nIndex = m_cmbIecCfgType.AddString(_T("GOOSE发布"));
		m_cmbIecCfgType.SetItemData(nIndex, CFGCLASSID_CIECCFGDATASGOUT);

		if ( nClassID == SCLIECCLASSID_CTRLS_GS_OUT)
		{
			m_cmbIecCfgType.SetCurSel(1);
		} 
		else
		{
			m_cmbIecCfgType.SetCurSel(0);
		}
	}

	
}
void CSclFileCtrlView::xlang_InitAndAdjust()   //2016.10.13
{
	if (xlang_IsCurrXLanguageChinese())   //2016.10.13
	{
		return;    //2016.10.13
	}

//	m_btnAllSel.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnAllSel);//2016.10.13
	m_btnAddTo.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnAddTo);//2016.10.13
	m_btnOverwrite.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnOverwrite);//2016.10.13
	m_btnCompare.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnCompare);//2016.10.13
	m_btnExport.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_btnExport);//2016.10.13

	CXLangWndAdjMngr oWndAdjMngr;//2016.10.13
	oWndAdjMngr.RegisterCols();//2016.10.13   注册（添加）一个列集合对象（即行的概念）
//	oWndAdjMngr.RegisterXCol(&m_btnAllSel);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_btnAddTo);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_btnOverwrite);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_btnCompare);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_btnExport);//2016.10.13

	oWndAdjMngr.Adjust(this, TRUE);//2016.10.13

}

void CSclFileCtrlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CRect rcGrid;
	GetClientRect(&rcGrid);

	rcGrid.top = 5;
	rcGrid.left = 5;
	rcGrid.right -= 5;
	rcGrid.bottom -= 5;

	m_oSclIecCfgCtrlGrid.Create(rcGrid, this, IDC_GRID_SCLIECCFG_CTRL);
	m_oSclIecCfgCtrlGrid.SetFont(g_pGlobalFont11);
	m_oSclIecCfgCtrlGrid.InitGrid();

	xlang_InitAndAdjust(); //2016.10.13   【此句放在下列窗口调整之前】

	m_btnAddTo.GetWindowRect(&m_rcCtrlsOrigin[0]);
	m_cmbIecCfgFile.GetWindowRect(&m_rcCtrlsOrigin[1]);
	m_cmbIecCfgType.GetWindowRect(&m_rcCtrlsOrigin[2]);
	m_btnOverwrite.GetWindowRect(&m_rcCtrlsOrigin[3]);
	m_btnCompare.GetWindowRect(&m_rcCtrlsOrigin[4]);
	m_btnExport.GetWindowRect(&m_rcCtrlsOrigin[5]);
	m_btnOneKeyCfg.GetWindowRect(&m_rcCtrlsOrigin[6]);
	
	ScreenToClient(&m_rcCtrlsOrigin[0]);
	ScreenToClient(&m_rcCtrlsOrigin[1]);
	ScreenToClient(&m_rcCtrlsOrigin[2]);
	ScreenToClient(&m_rcCtrlsOrigin[3]);
	ScreenToClient(&m_rcCtrlsOrigin[4]);
	ScreenToClient(&m_rcCtrlsOrigin[5]);
	ScreenToClient(&m_rcCtrlsOrigin[6]);
	UpdateIecCfgFilesComboBox();

	if ((g_nEngineDispMode == _DISP_MODE_PN466))
	{
		m_btnAddTo.SetWindowText(_T("导入"));
		m_cmbIecCfgFile.ShowWindow(SW_HIDE);
	}
	else
	{
		m_cmbIecCfgFile.ShowWindow(SW_SHOW);
	}

	m_oSclIecCfgCtrlGrid.m_pMsgRcvWnd = this;
}

void CSclFileCtrlView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_oSclIecCfgCtrlGrid.m_hWnd))
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

	long nHeight = m_rcCtrlsOrigin[0].Height();
	CRect rc(IECCFG_CTRL_GAP, IECCFG_CTRL_GAP, cx - 2*IECCFG_CTRL_GAP, cy - nHeight - 2*IECCFG_CTRL_GAP);
	m_oSclIecCfgCtrlGrid.MoveWindow(rc);

	rc = m_rcCtrlsOrigin[0];
	rc.bottom = cy - IECCFG_CTRL_GAP;
	rc.top = rc.bottom - nHeight;
	m_btnAddTo.CButton::MoveWindow(&rc);

	rc.left = m_rcCtrlsOrigin[6].left;
	rc.right = m_rcCtrlsOrigin[6].right;
	m_btnOneKeyCfg.CButton::MoveWindow(rc, TRUE);

	rc.left = m_rcCtrlsOrigin[3].left;
	rc.right = m_rcCtrlsOrigin[3].right;
	m_btnOverwrite.CButton::MoveWindow(rc);

	rc.left = m_rcCtrlsOrigin[4].left;
	rc.right = m_rcCtrlsOrigin[4].right;
	m_btnCompare.CButton::MoveWindow(rc);
	
	rc.left = m_rcCtrlsOrigin[5].left;
	rc.right = m_rcCtrlsOrigin[5].right;
	m_btnExport.CButton::MoveWindow(rc);

	rc.bottom = rc.top + 200;
	rc.left = m_rcCtrlsOrigin[1].left;
	rc.right = m_rcCtrlsOrigin[1].right;
	m_cmbIecCfgFile.MoveWindow(rc);

	rc.left = m_rcCtrlsOrigin[2].left;
	rc.right = m_rcCtrlsOrigin[2].right;
	m_cmbIecCfgType.MoveWindow(rc);


}

void CSclFileCtrlView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pSclFile = (CSclFile*)lHint;
}


BOOL CSclFileCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::PreCreateWindow(cs);
}

int CSclFileCtrlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_cxMIn = lpCreateStruct->cx;
	m_cyMin = lpCreateStruct->cy;

	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CSclFileCtrlView::UpdateIecCfgFilesComboBox()
{
	CIecCfgFiles *pIecCfgFiles = CIecCfgTool::GetIecCfgFiles();
	long nCurrSel = m_cmbIecCfgFile.GetCurSel();

	if (nCurrSel == CB_ERR)
	{
		nCurrSel = 0;
	}

	m_cmbIecCfgFile.ResetContent();

	if (pIecCfgFiles->GetCount() == 0)
	{
		return;
	}

	long nIndex = m_cmbIecCfgFile.AddString(_T("所有打开配置文件"));
	m_cmbIecCfgFile.SetItemDataPtr(nIndex, NULL);

	pIecCfgFiles->InsertChildreComboBox(&m_cmbIecCfgFile);

	if (nCurrSel >= m_cmbIecCfgFile.GetCount())
	{
		nCurrSel = m_cmbIecCfgFile.GetCount() - 1;
	}

	m_cmbIecCfgFile.SetCurSel(nCurrSel);
}

CExBaseObject* CSclFileCtrlView::GetDestIecCfgFile()
{
	if (m_cmbIecCfgFile.GetCount() == 0)
	{
		return NULL;
	}

	long nCurrSel = m_cmbIecCfgFile.GetCurSel();

	if (nCurrSel == CB_ERR)
	{
		return NULL;
	}

	return (CExBaseObject*)m_cmbIecCfgFile.GetItemDataPtr(nCurrSel);
}

UINT CSclFileCtrlView::GetDestIecCfgDataClassID()
{
	long nIndex = m_cmbIecCfgType.GetCurSel();
	return m_cmbIecCfgType.GetItemData(nIndex);
}

void GetRepeatSclCtrlsLogString(CExBaseList &oRepeatListRef,CString &strMsg)
{
	CString strSmv = _T(""),strGin = _T(""),strGout = _T("");
	POS pos = oRepeatListRef.GetHeadPosition();
	CSclCtrlBase *pSclCtrlBase = NULL;
	strMsg = _T("是否覆盖如下控制块？");

	while(pos)
	{
		pSclCtrlBase = (CSclCtrlBase *)oRepeatListRef.GetNext(pos);

		if ((pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)||(pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN))
		{
			strSmv.AppendFormat(_T("0x%04X;"),pSclCtrlBase->GetAppID());
		}
		else if (pSclCtrlBase->m_dwItemData == 0)//用于测试仪Goose订阅
		{
			strGin.AppendFormat(_T("0x%04X;"),pSclCtrlBase->GetAppID());
		}
		else//用于测试仪Goose发布
		{
			strGout.AppendFormat(_T("0x%04X;"),pSclCtrlBase->GetAppID());		 
		}
	}

	if (!strSmv.IsEmpty())
	{
		strMsg.AppendFormat(_T("采样值(AppID=%s)"),strSmv);
	}

	if (!strGin.IsEmpty())
	{
		strMsg.AppendFormat(_T("GOOSE订阅(AppID=%s)"),strGin);
	}

	if (!strGout.IsEmpty())
	{
		strMsg.AppendFormat(_T("GOOSE发布(AppID=%s)"),strGout);
	}
}

void CSclFileCtrlView::OnBnClickedBtnAddto()
{
	CIecCfgFiles *pIecCfgFiles = CIecCfgTool::GetIecCfgFiles();

	if (pIecCfgFiles->GetCount() == 0)
	{
		MessageBox(_T("没有打开IEC测试仪配置文件"), _T("提示"), MB_OK | MB_ICONWARNING);
		return;

	}

	CSclFileTreeView *pSclFileTreeView = (CSclFileTreeView*)m_pSclFileTreeView;
	ASSERT(pSclFileTreeView);

// 	CExBaseList oListSclDatas;
// 	m_pCurrSelSclCtrls->GetAllSelectedDatas(oListSclDatas);

	if (pSclFileTreeView->m_oSelectedSclCtrls.GetCount() == 0)
	{
		MessageBox(_T("没有选中的控制块对象"), _T("提示"), MB_OK | MB_ICONWARNING);
		return;
	}

	CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
	CSclToIecCfgTool oSclToIecCfgTool;
	oSclToIecCfgTool.AttacthSclFileRead(&pSclFileFrame->m_oSclStation);
	CExBaseObject *pSelIecCfgFile = GetDestIecCfgFile();
//	UINT nClassID = GetDestIecCfgDataClassID();

// 	if (pSelIecCfgFile == NULL)//在添加到ixml的情况下,增加AppID是否重复的判断
// 	{
// 		oSclToIecCfgTool.ValidCtrls_Repeat(pIecCfgFiles,&pSclFileTreeView->m_oSelectedSclCtrls);
// 	}
// 
// 	if (pSclFileTreeView->m_oSelectedSclCtrls.GetCount() == 0)
// 	{
// 		MessageBox(_T("没有有效的选中控制块对象."), _T("提示"), MB_OK | MB_ICONWARNING);
// 		return;
// 	}

	if (pSelIecCfgFile == NULL)
	{
		CIecCfgFiles *pFiles = CIecCfgTool::GetIecCfgFiles();
		CExBaseList oRepeatListRef;
		BOOL bHasRepeatCtrls = oSclToIecCfgTool.HasRepeatCtrls(&pSclFileTreeView->m_oSelectedSclCtrls,pFiles,oRepeatListRef);

		if (bHasRepeatCtrls)
		{
			CString strMsg;
			GetRepeatSclCtrlsLogString(oRepeatListRef,strMsg);

			UINT nRet = MessageBox(strMsg.GetString(), _T("提示"), MB_YESNO | MB_ICONQUESTION);

			if (nRet == IDYES)
			{
				oSclToIecCfgTool.DeleteAllRepeatCtrls(pFiles,oRepeatListRef);
			}
		}

		oRepeatListRef.RemoveAll();
		oSclToIecCfgTool.AddToIecCfg_Mix(&pSclFileTreeView->m_oSelectedSclCtrls, pFiles);
	}
	else
	{
		ASSERT (pSelIecCfgFile->GetClassID() == IFTCLASSID_CIECCFGFILE);
		oSclToIecCfgTool.AddToIecCfg_Mix(&pSclFileTreeView->m_oSelectedSclCtrls, (CIecCfgFile*)pSelIecCfgFile);
	}

//	oSclToIecCfgTool.AddToIecCfg_Mix(&pSclFileTreeView->m_oSelectedSclCtrls, pSelIecCfgFile);
	pSclFileTreeView->m_oSelectedSclCtrls.RemoveAll();

	if (m_pCurrSelSclCtrls != NULL)
	{
		m_pCurrSelSclCtrls->SetSelectAll(FALSE);
		m_oSclIecCfgCtrlGrid.UpdateCheck();
	}

	pSclFileTreeView->ShowGridDatas();
}

void CSclFileCtrlView::OnBnClickedBtnOverrite()
{
	MessageBox(_T("功能开发中......"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
}

void CSclFileCtrlView::OnBnClickedBtnCompare()
{
	MessageBox(_T("功能开发中......"), _T("提示"), MB_OK | MB_ICONEXCLAMATION);
}

void CSclFileCtrlView::OnBnClickedBtnExport()
{
	if (m_pCurrSelSclCtrls == NULL)
	{
		return;
	}

	if (m_pCurrSelSclCtrls->GetClassID() != SCLIECCLASSID_CTRLS_GS_IN)
	{
		return;
	}

	CString strFile;
	strFile = wzd_GetWzdFilePath();

	if (!PopupSaveAsFileDialog(this, strFile, _T("遥信测试向导数据文件|*.xml||"), _T("xml")))
	{
		return;
	}

	CSclGsInCtrlsToDinWzdTools oSclGsInCtrlsToDinWzdTools;
	oSclGsInCtrlsToDinWzdTools.ExportDinWzdFile(strFile, (CSclCtrlsGsIn*)m_pCurrSelSclCtrls);

}
// 
// void CSclFileCtrlView::OnBnClickedCheckAll()
// {
// 	POS pos = m_pCurrSelSclCtrls->GetHeadPosition();
// 	CSclCtrlBase *pSclCtrl = NULL;
// 	long nSelect = m_btnAllSel.GetCheck();
// 
// 	while (pos != NULL)
// 	{
// 		pSclCtrl = (CSclCtrlBase*)m_pCurrSelSclCtrls->GetNext(pos);
// 		pSclCtrl->m_nSelect = nSelect;
// 	}
// 
// 	m_oSclIecCfgCtrlGrid.UpdateCheck();
// }

void CSclFileCtrlView::OnCbnSelchangeComboIeccfgFile()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CSclFileCtrlView::OnCbnSelchangeComboIeccfgType()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CSclFileCtrlView::OnBnClickedBtnOneKeyCfg()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pCurrSelSclCtrls == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的IED为空,请重新选择."));
		return;
	}

	CSclIed *pSclIED = (CSclIed*)m_pCurrSelSclCtrls->GetParent();

	if (pSclIED == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的IED为空,请重新选择."));
		return;
	}

	CSclCtrlsSmvOut *pSmvOutCtrls = pSclIED->GetSmvOuts();
	CSclCtrlsSmvIn *pSmvInCtrls = pSclIED->GetSmvIns();
	CSclCtrlsGsIn *pGsInCtrls = pSclIED->GetGsIns();
	CSclCtrlsGsOut *pGsOutCtrls = pSclIED->GetGsOuts();
	CSclFileTreeView *pSclFileTreeView = (CSclFileTreeView*)m_pSclFileTreeView;
	BOOL bIsAllSelected = FALSE;

	if (pSclIED->IsAllCtrlsSelected())
	{
		bIsAllSelected = TRUE;
	}

	if (pSmvOutCtrls != NULL)
	{
		pSmvOutCtrls->SetSelectAll(!bIsAllSelected);
		pSclFileTreeView->AddGridCtrls(pSmvOutCtrls);//   m_oSelectedSclCtrls.Append(pSmvOutCtrls);
	}

	if (pSmvInCtrls != NULL)
	{
		pSmvInCtrls->SetSelectAll(!bIsAllSelected);
		pSclFileTreeView->AddGridCtrls(pSmvInCtrls);
	}

	if (pGsInCtrls != NULL)
	{
		pGsInCtrls->SetSelectAll(!bIsAllSelected);
		pGsInCtrls->SetAllItemData(1);//用于测试仪Goose发布
		pSclFileTreeView->AddGridCtrls(pGsInCtrls);
	}

	if (pGsOutCtrls != NULL)
	{
		pGsOutCtrls->SetSelectAll(!bIsAllSelected);
		pGsOutCtrls->SetAllItemData(0);//用于测试仪Goose订阅
		pSclFileTreeView->AddGridCtrls(pGsOutCtrls);
	}

	m_oSclIecCfgCtrlGrid.UpdateCheck();
	pSclFileTreeView->ShowGridDatas();
}
