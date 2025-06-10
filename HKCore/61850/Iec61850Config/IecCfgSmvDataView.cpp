// IecCfgSmvDataView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgSmvDataView.h"
#include "IecCfgSmvDataChsView.h"
#include "CommonFT3ParasSetDlg.h"

#include "..\Module\UI\DlgSmvRate.h"
#include "..\..\Module\XLanguage\XLangWndAdjust.h"//20161013

#define SMV_RATE_FT3_500HZ                                    0
#define SMV_RATE_FT3_4000HZ                                   1
#define SMV_RATE_FT3_5000HZ                                   2
#define SMV_RATE_FT3_8000HZ                                   3
#define SMV_RATE_FT3_10000HZ                                  4
#define SMV_RATE_FT3_50000HZ                                  5
#define SMV_RATE_FT3_100000HZ                                 6

#define BAUD_RATE_FT3_2_5MBPS                                 0
#define BAUD_RATE_FT3_5MBPS                                   1
#define BAUD_RATE_FT3_10MBPS                                  2
#define BAUD_RATE_FT3_20MBPS                                  3



// CIecCfgSmvDataView

IMPLEMENT_DYNCREATE(CIecCfgSmvDataView, CFormView)

CIecCfgSmvDataView::CIecCfgSmvDataView()
	: CIecCfgDataViewBase(CIecCfgSmvDataView::IDD)
	, m_strSmpRate(_T(""))
	, m_bNoQuality(FALSE)
{
	m_bSelDataset = FALSE;
	m_bSelSecurity = FALSE;
	m_bSelSmpRate = FALSE;
	m_bSelRefrTm = FALSE;
	m_nGridTop = 30;
	//m_pChsView = NULL;
}

CIecCfgSmvDataView::~CIecCfgSmvDataView()
{
	
}

void CIecCfgSmvDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SMV_TYPE, m_cmbIecCfgSmvType);
	DDX_Text(pDX, IDC_EDIT_SMAP_RATE, m_strSmpRate);
	DDX_Control(pDX, IDC_COMBO_ASDU, m_cmbAsdu);
	DDX_Check(pDX, IDC_CHECK_QUALITY, m_bNoQuality);
	DDX_Check(pDX, IDC_CHECK_DATASET, m_bSelDataset);
	DDX_Check(pDX, IDC_CHECK_SECURITY, m_bSelSecurity);
	DDX_Check(pDX, IDC_CHECK_SMPRATE, m_bSelSmpRate);
	DDX_Check(pDX, IDC_CHECK_REFRTM, m_bSelRefrTm);
	//	DDX_Control(pDX, IDC_STATIC_MesType, m_STATIC_MesType);
	DDX_Control(pDX, IDC_STATIC_MESTYPE, m_staIecMesType);
	DDX_Control(pDX, IDC_STATIC_SAMPLERATE, m_staIecSampleRate);
	DDX_Control(pDX, IDC_EDIT_SMAP_RATE, m_ediIecSmapRate);
	DDX_Control(pDX, IDC_STATIC_ASDU, m_staIecASDU);
	DDX_Control(pDX, IDC_CHECK_QUALITY, m_cheIecQuality);
	DDX_Control(pDX, IDC_SMV_RATE, m_butIecSMVRate);
	DDX_Control(pDX, IDC_CHECK_DATASET, m_btnDataset);
	DDX_Control(pDX, IDC_STATIC_SMP_RATE_FT3, m_stcSmpRateFT3);
	DDX_Control(pDX, IDC_COMBO_SMP_RATE_FT3, m_cmbSmpRateFT3);
	DDX_Control(pDX, IDC_STATIC_BAUDRATE_FT3, m_stcBaudRateFT3);
	DDX_Control(pDX, IDC_COMBO_BAUD_RATE_FT3, m_cmbBaudRateFT3);
}

BEGIN_MESSAGE_MAP(CIecCfgSmvDataView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_ADD, &CIecCfgDataViewBase::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_DELETE, &CIecCfgDataViewBase::OnBnClickedBtnDelete)
// 	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_DELETEALL, &CIecCfgDataViewBase::OnBnClickedBtnDeleteAll)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_MOVEUP, &CIecCfgDataViewBase::OnBnClickedBtnMoveUp)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_MOVEDOWN, &CIecCfgDataViewBase::OnBnClickedBtnMoveDown)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_COPY, &CIecCfgDataViewBase::OnBnClickedBtnCopy)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_PASTE, &CIecCfgDataViewBase::OnBnClickedBtnPaste)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_EXPORTTO, &CIecCfgDataViewBase::OnBnClickedBtnExportTo)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_INCREASE, &CIecCfgDataViewBase::OnBnClickedBtnIncrease)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_DECREASE, &CIecCfgDataViewBase::OnBnClickedBtnDecrease)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_SELALL, &CIecCfgDataViewBase::OnBnClickedBtnSelAll)
	ON_CBN_SELCHANGE(IDC_COMBO_SMV_TYPE, &CIecCfgSmvDataView::OnCbnSelchangeComboSmvType)
	ON_EN_KILLFOCUS(IDC_EDIT_SMAP_RATE, &CIecCfgSmvDataView::OnEnKillfocusEditSmapRate)
	ON_CBN_SELCHANGE(IDC_COMBO_ASDU, &CIecCfgSmvDataView::OnCbnSelchangeComboAsdu)
	ON_BN_CLICKED(IDC_SMV_RATE, &CIecCfgSmvDataView::OnBnClickedSmvRate)
	ON_BN_CLICKED(IDC_CHECK_QUALITY, &CIecCfgSmvDataView::OnBnClickedCheckQuality)
	ON_BN_CLICKED(IDC_CHECK_DATASET, &CIecCfgSmvDataView::OnBnClickedCheckDataset)
	ON_BN_CLICKED(IDC_CHECK_SECURITY, &CIecCfgSmvDataView::OnBnClickedCheckSecurity)
	ON_BN_CLICKED(IDC_CHECK_SMPRATE, &CIecCfgSmvDataView::OnBnClickedCheckSmpRate)
	ON_BN_CLICKED(IDC_CHECK_REFRTM, &CIecCfgSmvDataView::OnBnClickedCheckRefrTm)
//	ON_STN_CLICKED(IDC_STATIC_MesType, &CIecCfgSmvDataView::OnStnClickedStaticMestype)
//	ON_STN_CLICKED(IDC_STATIC_MESTIPE, &CIecCfgSmvDataView::OnStnClickedStaticMestipe)
	ON_STN_CLICKED(IDC_STATIC_SAMPLERATE, &CIecCfgSmvDataView::OnStnClickedStaticSamplerate)
	ON_STN_CLICKED(IDC_STATIC_MESTYPE, &CIecCfgSmvDataView::OnStnClickedStaticMestype)
	ON_EN_CHANGE(IDC_EDIT_SMAP_RATE, &CIecCfgSmvDataView::OnEnChangeEditSmapRate)
	ON_STN_CLICKED(IDC_STATIC_ASDU, &CIecCfgSmvDataView::OnStnClickedStaticAsdu)
	ON_CBN_SELCHANGE(IDC_COMBO_SMP_RATE_FT3, &CIecCfgSmvDataView::OnCbnSelchangeComboSmpRateFt3)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD_RATE_FT3, &CIecCfgSmvDataView::OnCbnSelchangeComboBaudRateFt3)
END_MESSAGE_MAP()


// CIecCfgSmvDataView 诊断

#ifdef _DEBUG
void CIecCfgSmvDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgSmvDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgSmvDataView 消息处理程序
// 
// void CIecCfgSmvDataView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
// {
// 	CIecCfgFile *pFile = (CIecCfgFile*)lHint;
// 
// }

void CIecCfgSmvDataView::CreateIecCfgDataGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	long nCfgType = IEC_CFG_DEVICE_USE_TYPE_NORMAL;
	ASSERT (m_pIecCfgFile->m_pIecCfgDatasMngr != NULL);
	CIecCfgDevice *pIecCfgDevice = (CIecCfgDevice*)m_pIecCfgFile->m_pIecCfgDatasMngr->GetAncestor(CFGCLASSID_CIECCFGDEVICE);

	if (pIecCfgDevice != NULL)
	{
		nCfgType = pIecCfgDevice->m_nType;
	}

	CIecCfgDatasSMV *pDatasSmv = iecfg_GetIecCfgDatasSMV(m_pIecCfgFile);

	CRect rcGrid;
	GetClientRect(&rcGrid);

	rcGrid.left = 5;
	rcGrid.right -= 5;
	rcGrid.top = m_nGridTop;
	rcGrid.bottom = rcGrid.bottom - 10 - IDC_BTN_IECCFG_DATA_OPTR_HEIGHT;

	if (m_pIecCfgDataGrid != NULL)
	{
		m_pIecCfgDataGrid->GetWindowRect(&rcGrid);
		ScreenToClient(&rcGrid);
		m_pIecCfgDataGrid->DestroyWindow();
		delete m_pIecCfgDataGrid;
		m_pIecCfgDataGrid = NULL;
	}
	
	if (pDatasSmv->IsSmvType92())
	{
		m_pIecCfgDataGrid = new CIecCfgSmvData92Grid(nCfgType);
	}
	else if (pDatasSmv->IsSmvType91())
	{
		m_pIecCfgDataGrid = new CIecCfgSmvData91Grid();
	}
	else if (pDatasSmv->IsSmvType6044())
	{
		m_pIecCfgDataGrid = new CIecCfgSmvData6044Grid();
	}
	else if (pDatasSmv->IsSmvType6044Common())
	{
		m_pIecCfgDataGrid = new CIecCfgSmvData6044CommonGrid();
	}
	else
	{
		ASSERT(FALSE);
	}

	m_pIecCfgDataGrid->Create(rcGrid, this, IDC_GRID_IECCFG_DATA_BASE);
	m_pIecCfgDataGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataGrid->InitGrid();
	m_pIecCfgDataGrid->AttachDataViewOptrInterface(this);
}


void CIecCfgSmvDataView::xlang_InitAndAdjust()   //2016.10.13
{
	if (xlang_IsCurrXLanguageChinese())   //2016.10.13
	{
		return;    //2016.10.13
	}

	m_staIecMesType.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_staMesType);//2016.10.13
//	m_staIecSampleRate.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_staSampleRate);//2016.10.13
	m_staIecASDU.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_staASDU);//2016.10.13
	m_cheIecQuality.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_cheQuality);//2016.10.13
	m_butIecSMVRate.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSMVRate);//2016.10.13

	CXLangWndAdjMngr oWndAdjMngr;//2016.10.13
	oWndAdjMngr.RegisterCols();//2016.10.13   注册（添加）一个列集合对象（即行的概念）
	oWndAdjMngr.RegisterXCol(&m_staIecMesType);//2016.10.13
	oWndAdjMngr.RegisterCol();  //2016.10.13 未定义语言
	oWndAdjMngr.RegisterWnd(&m_cmbIecCfgSmvType);//2016.10.13 未定义语言
//	oWndAdjMngr.RegisterXCol(&m_staIecSampleRate);//2016.10.13
	oWndAdjMngr.RegisterCol();  //2016.10.13 未定义语言
	oWndAdjMngr.RegisterWnd(&m_ediIecSmapRate);//2016.10.13 未定义语言
	oWndAdjMngr.RegisterXCol(&m_staIecASDU);//2016.10.13
	oWndAdjMngr.RegisterCol();   //2016.10.13 未定义语言
	oWndAdjMngr.RegisterWnd(&m_cmbAsdu);//2016.10.13 未定义语言
	oWndAdjMngr.RegisterXCol(&m_cheIecQuality);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_butIecSMVRate);//2016.10.13

	oWndAdjMngr.Adjust(this, TRUE);//2016.10.13

}



void CIecCfgSmvDataView::OnInitialUpdate()
{
	CIecCfgDataViewBase::OnInitialUpdate();

	m_cmbIecCfgSmvType.InitIt();
	m_cmbAsdu.InitNumbers(1, 8);//目前硬件支持到8

	m_cmbSmpRateFT3.Clear();
	m_cmbSmpRateFT3.AddString(_T("500Hz"));
	m_cmbSmpRateFT3.AddString(_T("4000Hz"));
	m_cmbSmpRateFT3.AddString(_T("5000Hz"));
	m_cmbSmpRateFT3.AddString(_T("8000Hz"));
	m_cmbSmpRateFT3.AddString(_T("10000Hz"));
	m_cmbSmpRateFT3.AddString(_T("50000Hz"));
	m_cmbSmpRateFT3.AddString(_T("100000Hz"));

	m_cmbBaudRateFT3.Clear();
	m_cmbBaudRateFT3.AddString(_T("2.5Mbps"));
	m_cmbBaudRateFT3.AddString(_T("5Mbps"));
	m_cmbBaudRateFT3.AddString(_T("10Mbps"));
	m_cmbBaudRateFT3.AddString(_T("20Mbps"));

	CRect rc;
	GetClientRect(&rc);

	xlang_InitAndAdjust(); //2016.10.13

// 	CreateIecCfgDataGrid();
	CreateAllButtons(rc.Width(), rc.Height());

	CRect rcSmpRate92;
	m_staIecSampleRate.GetWindowRect(rcSmpRate92);
	ScreenToClient(rcSmpRate92);
	m_stcSmpRateFT3.GetWindowRect(m_rcSmpRateFT3_Stc);
	ScreenToClient(m_rcSmpRateFT3_Stc);
	long nLenth = m_rcSmpRateFT3_Stc.left - rcSmpRate92.left;
	m_rcSmpRateFT3_Stc.left -= nLenth;
	m_rcSmpRateFT3_Stc.right -= nLenth;

	m_cmbSmpRateFT3.GetWindowRect(m_rcSmpRateFT3_Cmb);
	ScreenToClient(m_rcSmpRateFT3_Cmb);
	m_rcSmpRateFT3_Cmb.left -= nLenth;
	m_rcSmpRateFT3_Cmb.right -= nLenth;

	m_stcBaudRateFT3.GetWindowRect(m_rcBaudRateFT3_Stc);
	ScreenToClient(m_rcBaudRateFT3_Stc);
	m_rcBaudRateFT3_Stc.left -= nLenth;
	m_rcBaudRateFT3_Stc.right -= nLenth;

	m_cmbBaudRateFT3.GetWindowRect(m_rcBaudRateFT3_Cmb);
	ScreenToClient(m_rcBaudRateFT3_Cmb);
	m_rcBaudRateFT3_Cmb.left -= nLenth;
	m_rcBaudRateFT3_Cmb.right -= nLenth;
}

void CIecCfgSmvDataView::OnSize(UINT nType, int cx, int cy)
{
	CIecCfgDataViewBase::OnSize(nType, cx, cy);

	AdjustSize(cx, cy);

	if (::IsWindow(m_stcSmpRateFT3.m_hWnd))
	{
		m_stcSmpRateFT3.MoveWindow(m_rcSmpRateFT3_Stc);
	}

	if (::IsWindow(m_cmbSmpRateFT3.m_hWnd))
	{
		m_cmbSmpRateFT3.MoveWindow(m_rcSmpRateFT3_Cmb);
	}

	if (::IsWindow(m_stcBaudRateFT3.m_hWnd))
	{
		m_stcBaudRateFT3.MoveWindow(m_rcBaudRateFT3_Stc);
	}

	if (::IsWindow(m_cmbBaudRateFT3.m_hWnd))
	{
		m_cmbBaudRateFT3.MoveWindow(m_rcBaudRateFT3_Cmb);
	}
}


void CIecCfgSmvDataView::ShowIecCfgData()
{
	CIecCfgDataViewBase::ShowIecCfgData();

	//显示其他参数
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;//m_pIecCfgFile->m_pIecCfgDatasMngr->GetSmvMngr();

	long nSmv = pIecCfgDatasSMV->GetSmvType();
	m_cmbIecCfgSmvType.SetSmvType(nSmv);
	
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();

	iecfg_ValidateMiMax(pSmvCommon->m_fFNom, 10, 500000);
	iecfg_ValidateMiMax(pSmvCommon->m_nSampleRate, 500, 1000000);

	m_strSmpRate.Format(_T("%d"), pSmvCommon->m_nSampleRate);
	m_cmbAsdu.SelNumber(pSmvCommon->m_nAsduNum);
	m_bNoQuality = pSmvCommon->m_bNoQuality;

	CIecCfgDataBase* pIecCfgData = pIecCfgDatasSMV->GetFirstIecCfgDataBase();

	if ((pIecCfgData != NULL)&&(pIecCfgData->GetClassID() == CFGCLASSID_CIECCFG92DATA))
	{
		CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pIecCfgData;
		m_bSelDataset = pIecCfg92Data->m_nUseDataSet;
		m_bSelSecurity = pIecCfg92Data->m_nUseEncrupt;
		m_bSelSmpRate = pIecCfg92Data->m_nUseSampRate;
		m_bSelRefrTm = pIecCfg92Data->m_nUseRefreshTime;
	}

	UpdateData(FALSE);
	UpdateSMV_UI(m_cmbIecCfgSmvType.GetSmvType());
}

CIecCfgDatasBase* CIecCfgSmvDataView::GetIecCfgDatas()
{
	if (m_pIecCfgFile == NULL)
	{
		return NULL;
	}

	ASSERT (m_pIecCfgFile->m_pIecCfgDatasMngr != NULL);

	if (m_pIecCfgFile->m_pIecCfgDatasMngr == NULL)
	{
		return NULL;
	}

	CIecCfgDatasBase *pIecCfgDatas = NULL;
	pIecCfgDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetSmvMngr();

	return pIecCfgDatas;
}

CIecCfgDataSmvCommon* CIecCfgSmvDataView::GetIecCfgDataSmvCommon()
{
	if (m_pIecCfgDatas == NULL)
	{
		return NULL;
	}

	CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();
	
	return pSmvCommon;
}

void CIecCfgSmvDataView::OnCbnSelchangeComboSmvType()
{
	ASSERT (m_pIecCfgDatas != NULL);

	if (m_pIecCfgDatas == NULL)
	{
		return ;
	}

	CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
	UINT nSmvType = m_cmbIecCfgSmvType.GetSmvType();

	if (nSmvType == pIecCfgDatasSMV->GetSmvType())
	{
		return;
	}

//	m_pIecCfgDataGrid->SetRowCount(1);
	pIecCfgDatasSMV->SetSmvType(nSmvType);
	m_pChsView->CreateChsGrid();
	CreateIecCfgDataGrid();
	ShowIecCfgData();
	UpdateSMV_UI(nSmvType);

	if (m_pIecCfgDataGrid != NULL && m_pChsView != NULL)
	{
		m_pIecCfgDataGrid->AttachRefChsGrid(m_pChsView->m_pIecCfgDataChsGrid);
	}
}

void CIecCfgSmvDataView::UpdateSMV_UI(long nSmvType)
{
	if (nSmvType == SMVTYPE_6044_COMMON)
	{
		m_stcSmpRateFT3.ShowWindow(TRUE);
		m_cmbSmpRateFT3.ShowWindow(TRUE);
		m_stcBaudRateFT3.ShowWindow(TRUE);
		m_cmbBaudRateFT3.ShowWindow(TRUE);
		m_staIecSampleRate.ShowWindow(FALSE);
		m_ediIecSmapRate.ShowWindow(FALSE);
		m_staIecASDU.ShowWindow(FALSE);
		m_cmbAsdu.ShowWindow(FALSE);
		(CButton *)GetDlgItem(IDC_CHECK_DATASET)->ShowWindow(FALSE);
		(CButton *)GetDlgItem(IDC_CHECK_SECURITY)->ShowWindow(FALSE);
		(CButton *)GetDlgItem(IDC_CHECK_SMPRATE)->ShowWindow(FALSE);
		(CButton *)GetDlgItem(IDC_CHECK_REFRTM)->ShowWindow(FALSE);
		(CButton *)GetDlgItem(IDC_CHECK_QUALITY)->ShowWindow(FALSE);

		SetSmpRateFT3_UI();
		SetBautRateFT3_UI();
	}
	else
	{
		m_stcSmpRateFT3.ShowWindow(FALSE);
		m_cmbSmpRateFT3.ShowWindow(FALSE);
		m_stcBaudRateFT3.ShowWindow(FALSE);
		m_cmbBaudRateFT3.ShowWindow(FALSE);
		m_staIecSampleRate.ShowWindow(TRUE);
		m_ediIecSmapRate.ShowWindow(TRUE);
		m_staIecASDU.ShowWindow(TRUE);
		m_cmbAsdu.ShowWindow(TRUE);
		(CButton *)GetDlgItem(IDC_CHECK_DATASET)->ShowWindow(TRUE);
		(CButton *)GetDlgItem(IDC_CHECK_SECURITY)->ShowWindow(TRUE);
		(CButton *)GetDlgItem(IDC_CHECK_SMPRATE)->ShowWindow(TRUE);
		(CButton *)GetDlgItem(IDC_CHECK_REFRTM)->ShowWindow(TRUE);
		(CButton *)GetDlgItem(IDC_CHECK_QUALITY)->ShowWindow(TRUE);
	}
}

void CIecCfgSmvDataView::SetSmpRateFT3_UI()
{
	if (m_pIecCfgDatas == NULL)
	{
		return;
	}

	CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();

	if (pSmvCommon->m_nSampleRate == 500)
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_500HZ);
	}
	else if (pSmvCommon->m_nSampleRate == 4000)
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_4000HZ);
	}
	else if (pSmvCommon->m_nSampleRate == 5000)
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_5000HZ);
	}
	else if (pSmvCommon->m_nSampleRate == 8000)
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_8000HZ);
	}
	else if (pSmvCommon->m_nSampleRate == 10000)
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_10000HZ);
	}
	else if (pSmvCommon->m_nSampleRate == 50000)
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_50000HZ);
	}
	else if (pSmvCommon->m_nSampleRate == 100000)
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_100000HZ);
	}
	else
	{
		m_cmbSmpRateFT3.SetCurSel(SMV_RATE_FT3_4000HZ);
	}
}

void CIecCfgSmvDataView::GetSmpRateFT3_UI()
{
	if (m_pIecCfgDatas != NULL)
	{
		long nCurSel = m_cmbSmpRateFT3.GetCurSel();
		CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
		CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();

		if (nCurSel == SMV_RATE_FT3_500HZ)
		{
			pSmvCommon->m_nSampleRate = 500;
		}
		else if (nCurSel == SMV_RATE_FT3_4000HZ)
		{
			pSmvCommon->m_nSampleRate = 4000;
		}
		else if (nCurSel == SMV_RATE_FT3_5000HZ)
		{
			pSmvCommon->m_nSampleRate = 5000;
		}
		else if (nCurSel == SMV_RATE_FT3_8000HZ)
		{
			pSmvCommon->m_nSampleRate = 8000;
		}
		else if (nCurSel == SMV_RATE_FT3_10000HZ)
		{
			pSmvCommon->m_nSampleRate = 10000;
		}
		else if (nCurSel == SMV_RATE_FT3_50000HZ)
		{
			pSmvCommon->m_nSampleRate = 50000;
		}
		else if (nCurSel == SMV_RATE_FT3_100000HZ)
		{
			pSmvCommon->m_nSampleRate = 100000;
		}
		else
			pSmvCommon->m_nSampleRate = 4000;
	}
}

void CIecCfgSmvDataView::SetBautRateFT3_UI()
{
	if (m_pIecCfgDatas == NULL)
	{
		return;
	}

	CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();

	if ((pSmvCommon->m_nBaudRate<BAUD_RATE_FT3_2_5MBPS)||(pSmvCommon->m_nBaudRate>BAUD_RATE_FT3_20MBPS))
	{
		pSmvCommon->m_nBaudRate = BAUD_RATE_FT3_2_5MBPS;
	}

	m_cmbBaudRateFT3.SetCurSel(pSmvCommon->m_nBaudRate);
}

void CIecCfgSmvDataView::GetBautRateFT3_UI()
{
	if (m_pIecCfgDatas != NULL)
	{
		CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
		CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();
		pSmvCommon->m_nBaudRate = m_cmbBaudRateFT3.GetCurSel();
	}
}

void CIecCfgSmvDataView::OnEnKillfocusEditSmapRate()
{
	UpdateData(TRUE);

	CIecCfgDataSmvCommon *pSmvCommon = GetIecCfgDataSmvCommon();
	
	long nValue = CString_To_long(m_strSmpRate);

	if (iecfg_IsValidateMiMax(nValue, 500, 1000000))
	{
		pSmvCommon->m_nSampleRate = nValue;
	}
	else
	{
		nValue = pSmvCommon->m_nSampleRate;
	}
	
	m_strSmpRate.Format(_T("%d"), nValue);
	UpdateData(FALSE);
}

void CIecCfgSmvDataView::OnCbnSelchangeComboAsdu()
{
	CIecCfgDataSmvCommon *pSmvCommon = GetIecCfgDataSmvCommon();

	if (pSmvCommon == NULL)
	{
		return;
	}

	m_cmbAsdu.GetNumber(pSmvCommon->m_nAsduNum);
}

void CIecCfgSmvDataView::OnBnClickedSmvRate()
{
	CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
	CIecCfgSmvRates *pSmvRates = NULL;
	pSmvRates = pIecCfgDatasSMV->GetIecCfgSmvRates();
	pSmvRates->TransSmvRateID();

	if (pIecCfgDatasSMV->GetSmvType() == SMVTYPE_6044_COMMON)
	{
		CIecCfgDataSmvCommon *pSmvCommon = GetIecCfgDataSmvCommon();

		if (pSmvCommon == NULL)
		{
			return;
		}

		CCommonFT3ParasSetDlg oCommonFT3SetDlg;
		oCommonFT3SetDlg.InitParas(pSmvCommon);

		if (oCommonFT3SetDlg.DoModal() != IDOK)
		{
			return;
		}

		oCommonFT3SetDlg.GetCommonDataValues(pSmvCommon);
	} 
	else
	{
		CDlgSmvRate dlg;
		dlg.InitIecCfgSmvRates(pSmvRates);

		if (dlg.DoModal() != IDOK)
		{
			return;
		}

		pSmvRates = dlg.GetIecCfgSmvRates();

		if (dlg.m_bEditAll)
		{
			CIecCfgTool::SetIecCfgSmvRates(pSmvRates, NULL);
		}
		else
		{
			CIecCfgTool::SetIecCfgSmvRates(pSmvRates, m_pIecCfgFile);
		}
	}
}

void CIecCfgSmvDataView::OnBnClickedCheckQuality()
{
	UpdateData(TRUE);

	CIecCfgDataSmvCommon *pSmvCommon = GetIecCfgDataSmvCommon();
	pSmvCommon->m_bNoQuality = m_bNoQuality;
	CIecCfgTool::SetIecCfgSmvCommon(pSmvCommon, m_pIecCfgFile);

	UpdateData(FALSE);
}

void CIecCfgSmvDataView::OnBnClickedCheckDataset()
{
	UpdateData(TRUE);
	UpdateOptionalDatas();
	UpdateData(FALSE);
}

void CIecCfgSmvDataView::OnBnClickedCheckSecurity()
{
	UpdateData(TRUE);
	UpdateOptionalDatas();
	UpdateData(FALSE);
}

void CIecCfgSmvDataView::OnBnClickedCheckSmpRate()
{
	UpdateData(TRUE);
	UpdateOptionalDatas();
	UpdateData(FALSE);
}

void CIecCfgSmvDataView::OnBnClickedCheckRefrTm()
{
	UpdateData(TRUE);
	UpdateOptionalDatas();
	UpdateData(FALSE);
}


void CIecCfgSmvDataView::UpdateOptionalDatas()
{
	if (m_pIecCfgDatas != NULL)
	{
		CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatas;
		CExBaseObject *pCurObj = NULL;
		CIecCfg92Data *pIecCfg92Data = NULL;
		POS pos = m_pIecCfgDatas->GetHeadPosition();

		while(pos)
		{
			pCurObj = m_pIecCfgDatas->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92DATA)
			{
				pIecCfg92Data = (CIecCfg92Data *)pCurObj;
				pIecCfg92Data->m_nUseDataSet = m_bSelDataset;
				pIecCfg92Data->m_nUseEncrupt = m_bSelSecurity;
				pIecCfg92Data->m_nUseSampRate = m_bSelSmpRate;
				pIecCfg92Data->m_nUseRefreshTime = m_bSelRefrTm;
			}
		}

		iecfg_SetModified(m_pIecCfgDatas);
	}
}



void CIecCfgSmvDataView::OnStnClickedStaticSamplerate()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CIecCfgSmvDataView::OnStnClickedStaticMestype()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CIecCfgSmvDataView::OnEnChangeEditSmapRate()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CIecCfgDataViewBase::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CIecCfgSmvDataView::OnStnClickedStaticAsdu()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CIecCfgSmvDataView::OnCbnSelchangeComboSmpRateFt3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetSmpRateFT3_UI();
}

void CIecCfgSmvDataView::OnCbnSelchangeComboBaudRateFt3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetBautRateFT3_UI();
}
