// IecCfgGinDataView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgGinDataView.h"
#include "IecCfgGinDataChsView.h"

// CIecCfgGinDataView

IMPLEMENT_DYNCREATE(CIecCfgGinDataView, CFormView)

CIecCfgGinDataView::CIecCfgGinDataView()
	: CIecCfgDataViewBase(CIecCfgGinDataView::IDD)
{
	m_nGridTop = 2;
// 	m_pChsView = NULL;
// 	m_pIecCfgFile = NULL;
}

CIecCfgGinDataView::~CIecCfgGinDataView()
{
}

void CIecCfgGinDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIecCfgGinDataView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_ADD, &CIecCfgGinDataView::OnBnClickedBtnAddEx)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_DELETE, &CIecCfgGinDataView::OnBnClickedBtnDeleteEx)
// 	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_DELETEALL, &CIecCfgDataViewBase::OnBnClickedBtnDeleteAll)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_MOVEUP, &CIecCfgDataViewBase::OnBnClickedBtnMoveUp)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_MOVEDOWN, &CIecCfgDataViewBase::OnBnClickedBtnMoveDown)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_COPY, &CIecCfgDataViewBase::OnBnClickedBtnCopy)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_PASTE, &CIecCfgGinDataView::OnBnClickedBtnPasteEx)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_EXPORTTO, &CIecCfgDataViewBase::OnBnClickedBtnExportTo)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_INCREASE, &CIecCfgDataViewBase::OnBnClickedBtnIncrease)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_DECREASE, &CIecCfgDataViewBase::OnBnClickedBtnDecrease)
	ON_BN_CLICKED(IDC_BTN_IECCFG_DATA_OPTR_SELALL, &CIecCfgDataViewBase::OnBnClickedBtnSelAll)
END_MESSAGE_MAP()


// CIecCfgGinDataView 诊断

#ifdef _DEBUG
void CIecCfgGinDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgGinDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgGinDataView 消息处理程序
// 
// void CIecCfgGinDataView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
// {
// 	// TODO: 在此添加专用代码和/或调用基类
// }

void CIecCfgGinDataView::OnInitialUpdate()
{
	CIecCfgDataViewBase::OnInitialUpdate();

	CRect rc;
	GetClientRect(&rc);

// 	CreateIecCfgDataGrid();
	CreateAllButtons(rc.Width(), rc.Height());
}


void CIecCfgGinDataView::CreateIecCfgDataGrid()
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

	m_pIecCfgDataGrid = new CIecCfgGinDataGrid(nCfgType);

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

void CIecCfgGinDataView::OnSize(UINT nType, int cx, int cy)
{
	CIecCfgDataViewBase::OnSize(nType, cx, cy);

	AdjustSize(cx, cy);
}


CIecCfgDatasBase* CIecCfgGinDataView::GetIecCfgDatas()
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
	pIecCfgDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetGinMngr();

	return pIecCfgDatas;
}

void CIecCfgGinDataView::OnBnClickedBtnAddEx()
{
	CIecCfgDataViewBase::OnBnClickedBtnAdd();

	UpdateAppMaps();
}

void CIecCfgGinDataView::OnBnClickedBtnDeleteEx()
{
	CIecCfgDataViewBase::OnBnClickedBtnDelete();

	UpdateAppMaps();
}

void CIecCfgGinDataView::OnBnClickedBtnPasteEx()
{
	CIecCfgDataViewBase::OnBnClickedBtnPaste();

	UpdateAppMaps();
}
void CIecCfgGinDataView::UpdateAppMaps()
{
	CIecCfgDatasBase *pIecCfgDatas = NULL;
	pIecCfgDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetGinMngr();
	((CIecCfgGinDatas*)pIecCfgDatas)->InitGinAppChMaps();
	((CIecCfgGinDataChsView*)m_pChsView)->ShowIecCfgGinAppMaps();;
}

