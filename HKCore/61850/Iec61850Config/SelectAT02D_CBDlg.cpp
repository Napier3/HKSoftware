// SelectAT02D_CBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "SelectAT02D_CBDlg.h"

//#include "resource.h"



// CSelectAT02D_CBDlg 对话框

IMPLEMENT_DYNAMIC(CSelectAT02D_CBDlg, CDialog)

CSelectAT02D_CBDlg::CSelectAT02D_CBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectAT02D_CBDlg::IDD, pParent)
{
	m_pCurSclStation = NULL;
	m_nMaxFiberNum = 2;
}

CSelectAT02D_CBDlg::~CSelectAT02D_CBDlg()
{
	m_oSMVList.RemoveAll();
	m_oGinList.RemoveAll();
	m_oGoutList.RemoveAll();
}

void CSelectAT02D_CBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOG_MSG, m_stcLogMsg);
	DDX_Control(pDX, IDC_COMBO_MAX_FIBER_NUM, m_cmbMaxFiberNum);
}


BEGIN_MESSAGE_MAP(CSelectAT02D_CBDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSelectAT02D_CBDlg 消息处理程序

int CSelectAT02D_CBDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//获得窗口的创建信息指针
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;

	m_tabPara.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0, 0, 0, 0), this, 1000, CMFCTabCtrl::LOCATION_TOP);

	m_oSMVList.RemoveAll();
	m_oGinList.RemoveAll();
	m_oGoutList.RemoveAll();
	m_oSMV_AT02D_View.m_pCurDatasList = &m_oSMVList;
	m_oGsSubAT02D_View.m_pCurDatasList = &m_oGoutList;
	m_oGsPubAT02D_View.m_pCurDatasList = &m_oGinList;
	m_oSMV_AT02D_View.AttachMsgWnd(this);
	m_oGsSubAT02D_View.AttachMsgWnd(this);
	m_oGsPubAT02D_View.AttachMsgWnd(this);

	if (m_pCurSclStation != NULL)
	{
		m_pCurSclStation->GetAll92Ref(&m_oSMVList);
		m_pCurSclStation->GetAllGinRef(&m_oGinList);
		m_pCurSclStation->GetAllGoutRef(&m_oGoutList);
		m_oSMVList.SetSelectNum(3);
		m_oGinList.SetSelectNum(6);
		m_oGoutList.SetSelectNum(6);
	}

	if (m_oSMV_AT02D_View.Create(IDD_AT02D_CBS_FORM,&m_tabPara))
	{
		m_tabPara.AddTab(&m_oSMV_AT02D_View, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecSMVCfg/*_T("SMV配置")*/);
	}

	if (m_oGsSubAT02D_View.Create(IDD_AT02D_CBS_FORM,&m_tabPara))
	{
		m_tabPara.AddTab(&m_oGsSubAT02D_View, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoSubCfg/*_T("GOOSE订阅配置")*/);
	}

	if (m_oGsPubAT02D_View.Create(IDD_AT02D_CBS_FORM,&m_tabPara))
	{
		m_tabPara.AddTab(&m_oGsPubAT02D_View, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoPubCfg/*_T("GOOSE发布配置")*/);
	}

	return 0;
}

void CSelectAT02D_CBDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!::IsWindow(m_tabPara.m_hWnd))
	{
		return;
	}

	CRect rcClient;
	GetClientRect(&rcClient);
	m_tabPara.MoveWindow(0, 0, rcClient.Width(), rcClient.Height()-70);
}

BOOL CSelectAT02D_CBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_stcLogMsg.SetFont(g_pGlobalFont16);
	UpdateCurSelCB_Num();

	long nMaxIndex = 16;
	CString strName;

	for (int nIndex = 2;nIndex<=nMaxIndex;nIndex++)
	{
		strName.Format(_T("%d光口"),nIndex);
		m_cmbMaxFiberNum.InsertString((nIndex-2),strName);
	}

	m_cmbMaxFiberNum.SetCurSel(6);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSelectAT02D_CBDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CSelectAT02D_CBDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	POS pos_cb = m_oSMVList.GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CSclCtrlSmvIn *pCurSmvIn = NULL;

	while(pos_cb)
	{
		pCurObj = m_oSMVList.GetNext(pos_cb);

		if (pCurObj->GetClassID() != SCLIECCLASSID_CTRL_SMV_IN)
		{
			continue;
		}

		pCurSmvIn = (CSclCtrlSmvIn *)pCurObj;

		if (pCurSmvIn->m_nSelect == 0)
		{
			m_oSMVList.Remove(pCurSmvIn);
		}
	}

	pos_cb = m_oGinList.GetHeadPosition();
	CSclCtrlGsIn *pCurGsIn = NULL;

	while(pos_cb)
	{
		pCurObj = m_oGinList.GetNext(pos_cb);

		if (pCurObj->GetClassID() != SCLIECCLASSID_CTRL_GS_IN)
		{
			continue;
		}

		pCurGsIn = (CSclCtrlGsIn *)pCurObj;

		if (pCurGsIn->m_nSelect == 0)
		{
			m_oGinList.Remove(pCurGsIn);
		}
	}

	pos_cb = m_oGoutList.GetHeadPosition();
	CSclCtrlGsOut *pCurGsOut = NULL;

	while(pos_cb)
	{
		pCurObj = m_oGoutList.GetNext(pos_cb);

		if (pCurObj->GetClassID() != SCLIECCLASSID_CTRL_GS_OUT)
		{
			continue;
		}

		pCurGsOut = (CSclCtrlGsOut *)pCurObj;

		if (pCurGsOut->m_nSelect == 0)
		{
			m_oGoutList.Remove(pCurGsOut);
		}
	}

	m_nMaxFiberNum = m_cmbMaxFiberNum.GetCurSel()+2;
	CDialog::OnOK();
}

void CSelectAT02D_CBDlg::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	UpdateCurSelCB_Num();
}

void CSelectAT02D_CBDlg::UpdateCurSelCB_Num()
{
	long nSmvCBNum = 0,nGinCBNum = 0,nGoutCBNum = 0;
	nSmvCBNum = m_oSMVList.GetCurSelCB_Num();
	nGinCBNum = m_oGinList.GetCurSelCB_Num();
	nGoutCBNum = m_oGoutList.GetCurSelCB_Num();
	CString strLogMsg;
	strLogMsg.Format(_T("SMV控制块需要3组,当前%ld组;GOOSE订阅控制块需要6组,当前%ld组;GOOSE发布控制块需要6组,当前%ld组."),nSmvCBNum,nGoutCBNum,nGinCBNum);
	m_stcLogMsg.SetWindowText(strLogMsg);
}