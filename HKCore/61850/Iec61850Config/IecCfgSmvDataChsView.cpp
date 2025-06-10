// IecCfgSmvDataChsView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgSmvDataChsView.h"

#include "..\..\Module\XLanguage\XLangWndAdjust.h"//20161013


// CIecCfgSmvDataChsView

IMPLEMENT_DYNCREATE(CIecCfgSmvDataChsView, CFormView)

CIecCfgSmvDataChsView::CIecCfgSmvDataChsView()
	: CIecCfgDataChsViewBase(CIecCfgSmvDataChsView::IDD)
	, m_bUseMapCur(TRUE)
	, m_bUseMapVol(TRUE)
	, m_nUITypeSelIndex(2)
	, m_bIntelligent(FALSE)
{
	m_nGridTop = 30;
}

CIecCfgSmvDataChsView::~CIecCfgSmvDataChsView()
{
	if (m_pIecCfgDataChsGrid != NULL)
	{
		delete m_pIecCfgDataChsGrid;
		m_pIecCfgDataChsGrid = NULL;
	}
}

void CIecCfgSmvDataChsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_UISEL_I, m_nUITypeSelIndex);
	DDX_Check(pDX, IDC_CHECK_USENAME, m_bIntelligent);
	DDX_Control(pDX, IDC_RADIO_UISEL_I, m_radIecUiselI);
	DDX_Control(pDX, IDC_RADIO_UISEL_U, m_radIecUiselU);    //20161013
	DDX_Control(pDX, IDC_RADIO_UISEL_ALL, m_radIecUiselAll);  //20161013
	DDX_Control(pDX, IDC_CHECK_USENAME, m_cheIecUseName);
	DDX_Control(pDX, IDC_BTN_SET_ABC, m_butIecSetABC);
	DDX_Control(pDX, IDC_BTN_SET_PABC, m_butIecSetPABC);
	DDX_Control(pDX, IDC_BTN_SET_SABC, m_butIecSetSABC);
	DDX_Control(pDX, IDC_BTN_SET_TABC, m_butIecSetTABC);
	DDX_Control(pDX, IDC_BTN_SET_ABC5, m_butIecSetABC5);
	DDX_Control(pDX, IDC_BTN_SET_ABC6, m_butIecSetABC6);
	DDX_Control(pDX, IDC_BTN_SET_0, m_butIecSet0);
	DDX_Control(pDX, IDC_BTN_SET_CHECK, m_btnSetCheck);
}
	//DDX_Check(pDX, IDC_CHECK_I, m_bUseMapCur);
	//DDX_Check(pDX, IDC_CHECK_U, m_bUseMapVol);

BEGIN_MESSAGE_MAP(CIecCfgSmvDataChsView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_SET_ABC, &CIecCfgSmvDataChsView::OnBnClickedBtnSetAbc)
	ON_BN_CLICKED(IDC_BTN_SET_PABC, &CIecCfgSmvDataChsView::OnBnClickedBtnSetPabc)
	ON_BN_CLICKED(IDC_BTN_SET_SABC, &CIecCfgSmvDataChsView::OnBnClickedBtnSetSabc)
	ON_BN_CLICKED(IDC_BTN_SET_TABC, &CIecCfgSmvDataChsView::OnBnClickedBtnSetTabc)
	ON_BN_CLICKED(IDC_BTN_SET_ABC5, &CIecCfgSmvDataChsView::OnBnClickedBtnSetabc5)
	ON_BN_CLICKED(IDC_BTN_SET_ABC6, &CIecCfgSmvDataChsView::OnBnClickedBtnSetabc6)
	ON_BN_CLICKED(IDC_BTN_SET_0, &CIecCfgSmvDataChsView::OnBnClickedBtnSet0)
	ON_BN_CLICKED(IDC_RADIO_UISEL_I, &CIecCfgSmvDataChsView::OnBnClickedRadioUiselI)
	ON_BN_CLICKED(IDC_RADIO_UISEL_U, &CIecCfgSmvDataChsView::OnBnClickedRadioUiselU)
	ON_BN_CLICKED(IDC_RADIO_UISEL_ALL, &CIecCfgSmvDataChsView::OnBnClickedRadioUiselAll)
	ON_BN_CLICKED(IDC_CHECK_USENAME, &CIecCfgSmvDataChsView::OnBnClickedCheckUsename)
	ON_BN_CLICKED(IDC_BTN_SET_CHECK, &CIecCfgSmvDataChsView::OnBnClickedBtnSetCheck)
END_MESSAGE_MAP()


// CIecCfgSmvDataChsView 诊断

#ifdef _DEBUG
void CIecCfgSmvDataChsView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgSmvDataChsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgSmvDataChsView 消息处理程序

void CIecCfgSmvDataChsView::CreateChsGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CIecCfgDatasSMV *pDatasSmv = iecfg_GetIecCfgDatasSMV(m_pIecCfgFile);

	CRect rcGrid;
	GetClientRect(&rcGrid);
	rcGrid.left = 5;
	rcGrid.right -= 5;
	rcGrid.top = m_nGridTop;
	rcGrid.bottom -=  5;

	FreeGrid(rcGrid);

	if (pDatasSmv->IsSmvType92())
	{
		m_pIecCfgDataChsGrid = new CIecCfgSmvData92ChsGrid();
		m_pIecCfgDataChsGrid->SetViewChsPath(CIecCfgTool::IsViewChsPath());
	}
	else if (pDatasSmv->IsSmvType91())
	{
		m_pIecCfgDataChsGrid = new CIecCfgSmvData91ChsGrid();
	}
	else if (pDatasSmv->IsSmvType6044())
	{
		m_pIecCfgDataChsGrid = new CIecCfgSmvData6044ChsGrid();
	}
	else if (pDatasSmv->IsSmvType6044Common())
	{
		m_pIecCfgDataChsGrid = new CIecCfgSmvData6044CommonChsGrid();
	}
	else
	{
		ASSERT(FALSE);
	}

	m_pIecCfgDataChsGrid->Create(rcGrid, this, IDC_GRID_IECCFG_DATACHS_BASE);
	m_pIecCfgDataChsGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataChsGrid->InitGrid();
}
void CIecCfgSmvDataChsView::xlang_InitAndAdjust()   //2016.10.13
{
	if (xlang_IsCurrXLanguageChinese())   //2016.10.13
	{
		return;    //2016.10.13
	}

	m_radIecUiselI.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_radUiselI);//2016.10.13
	m_radIecUiselU.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_radIecUiselU);//2016.10.13
	m_radIecUiselAll.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_radIecUiselAll);//2016.10.13
	m_cheIecUseName.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_cheUseName);//2016.10.13
	m_butIecSetABC.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC);//2016.10.13
	m_butIecSetPABC.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSetPABC);//2016.10.13
	m_butIecSetSABC.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSetSABC);//2016.10.13
	m_butIecSetTABC.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSetTABC);//2016.10.13
	m_butIecSetABC5.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC5);//zhouhj20210924
	m_butIecSetABC6.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC6);//zhouhj20210924
	m_butIecSet0.SetLanguageID(CXLanguageResourceIec_61850Cfg::g_sLid_butSet0);//2016.10.13

	CXLangWndAdjMngr oWndAdjMngr;//2016.10.13
	oWndAdjMngr.RegisterCols();//2016.10.13   注册（添加）一个列集合对象（即行的概念）
	oWndAdjMngr.RegisterXCol(&m_radIecUiselI);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_radIecUiselU);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_radIecUiselAll);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_cheIecUseName);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_butIecSetABC);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_butIecSetPABC);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_butIecSetSABC);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_butIecSetTABC);//2016.10.13
	oWndAdjMngr.RegisterXCol(&m_butIecSetABC5);//zhouhj20210924
	oWndAdjMngr.RegisterXCol(&m_butIecSetABC6);//zhouhj20210924
	oWndAdjMngr.RegisterXCol(&m_butIecSet0);//2016.10.13

	oWndAdjMngr.Adjust(this, TRUE);//2016.10.13

}

void CIecCfgSmvDataChsView::OnInitialUpdate()
{
	CIecCfgDataChsViewBase::OnInitialUpdate();

	//CreateGrid();

	xlang_InitAndAdjust(); //2016.10.13
}

void CIecCfgSmvDataChsView::OnSize(UINT nType, int cx, int cy)
{
	CIecCfgDataChsViewBase::OnSize(nType, cx, cy);

	AdjustSize(cx, cy);
}

BOOL CIecCfgSmvDataChsView::CanSetSelectChs(CExBaseList &oListDatas)
{
	long nCount = oListDatas.GetCount();

	if (nCount< 3)
	{
		return FALSE;
	}

	if (nCount % 3 == 0)
	{
		return TRUE;
	}

	if (nCount % 4 == 0)
	{
		return TRUE;
	}

	return FALSE;
}

void CIecCfgSmvDataChsView::ShowIecCfgDataChs(CIecCfgDataBase *pIecCfgData)
{
	CIecCfgDataChsViewBase::ShowIecCfgDataChs(pIecCfgData);

	if (pIecCfgData == NULL)
	{
		return;
	}

	CIecCfg92Data* pSmvData92 = (CIecCfg92Data*)m_pIecCfgData;

	if (pSmvData92->IsAllChSetTest())
	{
		m_btnSetCheck.SetWindowText(_T("不投检修"));
	} 
	else
	{
		m_btnSetCheck.SetWindowText(_T("投检修"));
	}

	CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data *)pIecCfgData->GetAncestor(CFGCLASSID_CIECCFG92DATA);

	if (pIecCfg92Data != NULL)
	{
		m_radIecUiselI.ShowWindow(TRUE);
		m_radIecUiselU.ShowWindow(TRUE);
		m_radIecUiselAll.ShowWindow(TRUE);
		m_cheIecUseName.ShowWindow(TRUE);
		m_butIecSetABC.ShowWindow(TRUE);
		m_butIecSetPABC.ShowWindow(TRUE);
		m_butIecSetSABC.ShowWindow(TRUE);
		m_butIecSetTABC.ShowWindow(TRUE);
		m_butIecSetABC5.ShowWindow(TRUE);
		m_butIecSetABC6.ShowWindow(TRUE);
		m_butIecSet0.ShowWindow(TRUE);
		m_btnSetCheck.ShowWindow(TRUE);
	} 
	else
	{
		m_radIecUiselI.ShowWindow(FALSE);
		m_radIecUiselU.ShowWindow(FALSE);
		m_radIecUiselAll.ShowWindow(FALSE);
		m_cheIecUseName.ShowWindow(FALSE);
		m_butIecSetABC.ShowWindow(FALSE);
		m_butIecSetPABC.ShowWindow(FALSE);
		m_butIecSetSABC.ShowWindow(FALSE);
		m_butIecSetTABC.ShowWindow(FALSE);
		m_butIecSetABC5.ShowWindow(FALSE);
		m_butIecSetABC6.ShowWindow(FALSE);
		m_butIecSet0.ShowWindow(FALSE);
		m_btnSetCheck.ShowWindow(FALSE);
	}
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSetAbc()
{
	UpdateData(TRUE);
	ASSERT (m_pIecCfgData != NULL);

	if (m_bUseMapVol && m_bUseMapCur)
	{
		((CIecCfgSmvDataBase*)m_pIecCfgData)->SetAbc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
	}
	else
	{
		CExBaseList oListDatas;
		m_pIecCfgDataChsGrid->GetAllSelectDatas(&oListDatas);

		if (CanSetSelectChs(oListDatas))
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetAbc(oListDatas, m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}
		else
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetAbc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}

		oListDatas.RemoveAll();
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSetPabc()
{
	UpdateData(TRUE);
	ASSERT (m_pIecCfgData != NULL);

	if (m_bUseMapVol && m_bUseMapCur)
	{
		((CIecCfgSmvDataBase*)m_pIecCfgData)->SetPabc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
	}
	else
	{
		CExBaseList oListDatas;
		m_pIecCfgDataChsGrid->GetAllSelectDatas(&oListDatas);

		if (CanSetSelectChs(oListDatas))
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetPabc(oListDatas, m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}
		else
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetPabc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}

		oListDatas.RemoveAll();
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSetSabc()
{
	UpdateData(TRUE);
	ASSERT (m_pIecCfgData != NULL);

	if (m_bUseMapVol && m_bUseMapCur)
	{
		((CIecCfgSmvDataBase*)m_pIecCfgData)->SetSabc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
	}
	else
	{
		CExBaseList oListDatas;
		m_pIecCfgDataChsGrid->GetAllSelectDatas(&oListDatas);

		if (CanSetSelectChs(oListDatas))
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetSabc(oListDatas, m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}
		else
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetSabc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}

		oListDatas.RemoveAll();
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSetTabc()
{
	UpdateData(TRUE);
	ASSERT (m_pIecCfgData != NULL);

	if (m_bUseMapVol && m_bUseMapCur)
	{
		((CIecCfgSmvDataBase*)m_pIecCfgData)->SetTabc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
	}
	else
	{
		CExBaseList oListDatas;
		m_pIecCfgDataChsGrid->GetAllSelectDatas(&oListDatas);

		if (CanSetSelectChs(oListDatas))
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetTabc(oListDatas, m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}
		else
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->SetTabc(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}

		oListDatas.RemoveAll();
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSetabc5()
{
	UpdateData(TRUE);
	ASSERT (m_pIecCfgData != NULL);

	if (m_bUseMapVol && m_bUseMapCur)
	{
		((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc5(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
	}
	else
	{
		CExBaseList oListDatas;
		m_pIecCfgDataChsGrid->GetAllSelectDatas(&oListDatas);

		if (CanSetSelectChs(oListDatas))
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc5(oListDatas, m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}
		else
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc5(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}

		oListDatas.RemoveAll();
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSetabc6()
{
	UpdateData(TRUE);
	ASSERT (m_pIecCfgData != NULL);

	if (m_bUseMapVol && m_bUseMapCur)
	{
		((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc6(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
	}
	else
	{
		CExBaseList oListDatas;
		m_pIecCfgDataChsGrid->GetAllSelectDatas(&oListDatas);

		if (CanSetSelectChs(oListDatas))
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc6(oListDatas, m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}
		else
		{
			((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc6(m_bUseMapVol, m_bUseMapCur, m_bIntelligent);
		}

		oListDatas.RemoveAll();
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSet0()
{
	UpdateData(TRUE);
	ASSERT (m_pIecCfgData != NULL);
	((CIecCfgSmvDataBase*)m_pIecCfgData)->Set0(m_bUseMapVol, m_bUseMapCur);
	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIecCfgSmvDataChsView::OnBnClickedRadioUiselI()
{
	m_bUseMapCur = TRUE;
	m_bUseMapVol = FALSE;
}

void CIecCfgSmvDataChsView::OnBnClickedRadioUiselU()
{
	m_bUseMapCur = FALSE;
	m_bUseMapVol = TRUE;
}

void CIecCfgSmvDataChsView::OnBnClickedRadioUiselAll()
{
	m_bUseMapCur = TRUE;
	m_bUseMapVol = TRUE;
}

void CIecCfgSmvDataChsView::OnBnClickedCheckUsename()
{
	UpdateData(TRUE);
}

void CIecCfgSmvDataChsView::OnBnClickedBtnSetCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	ASSERT (m_pIecCfgData != NULL);

	if (m_pIecCfgData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
	{
		return;
	}

	CIecCfg92Data* pSmvData92 = (CIecCfg92Data*)m_pIecCfgData;

	if (pSmvData92->IsAllChSetTest())
	{
		pSmvData92->SetChsQualityValue(0x00);
		m_btnSetCheck.SetWindowText(_T("投检修"));
	} 
	else
	{
		pSmvData92->SetChsQualityValue(0x0800);
		m_btnSetCheck.SetWindowText(_T("不投检修"));
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}
