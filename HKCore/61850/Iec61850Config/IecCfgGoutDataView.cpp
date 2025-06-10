// IecCfgGoutDataView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgGoutDataView.h"
#include "IecCfgGoutDataChsView.h"

// CIecCfgGoutDataView

IMPLEMENT_DYNCREATE(CIecCfgGoutDataView, CFormView)

CIecCfgGoutDataView::CIecCfgGoutDataView()
	: CIecCfgDataViewBase(CIecCfgGoutDataView::IDD)
{
	m_nGridTop = 2;
}

CIecCfgGoutDataView::~CIecCfgGoutDataView()
{
}

void CIecCfgGoutDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIecCfgGoutDataView, CFormView)
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
END_MESSAGE_MAP()


// CIecCfgGoutDataView 诊断

#ifdef _DEBUG
void CIecCfgGoutDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgGoutDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgGoutDataView 消息处理程序
// 
// void CIecCfgGoutDataView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
// {
// 	// TODO: 在此添加专用代码和/或调用基类
// }

void CIecCfgGoutDataView::OnInitialUpdate()
{
	CIecCfgDataViewBase::OnInitialUpdate();

	CRect rc;
	GetClientRect(&rc);

// 	CreateIecCfgDataGrid();
	CreateAllButtons(rc.Width(), rc.Height());
}


void CIecCfgGoutDataView::CreateIecCfgDataGrid()
{
	if (m_pIecCfgDataGrid != NULL)
	{
		return;
	}

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

	m_pIecCfgDataGrid = new CIecCfgGoutDataGrid(nCfgType);

	CRect rc;
	GetClientRect(&rc);

	rc.left = 5;
	rc.right -= 5;
	rc.top = m_nGridTop;
	rc.bottom = rc.bottom - 5;
	m_pIecCfgDataGrid->Create(rc, this, IDC_GRID_IECCFG_DATA_BASE);
	m_pIecCfgDataGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataGrid->InitGrid();
	m_pIecCfgDataGrid->AttachDataViewOptrInterface(this);
}

void CIecCfgGoutDataView::OnSize(UINT nType, int cx, int cy)
{
	CIecCfgDataViewBase::OnSize(nType, cx, cy);

	AdjustSize(cx, cy);
}



CIecCfgDatasBase* CIecCfgGoutDataView::GetIecCfgDatas()
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
	pIecCfgDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetGoutMngr();

	return pIecCfgDatas;
}

