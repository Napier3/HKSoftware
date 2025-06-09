#include "stdafx.h"
#include "IECCfgDlg.h"
#include "IECCfgExDlg.h"
#include "IECCfgAddDlg.h"
#include "../StepCtrl/61850/IECCfgSmv92DataGrid.h"
#include "../StepCtrl/61850/IECCfgSmv92ChsGrid.h"
#include "../StepCtrl/61850/IECCfgGinDataGrid.h"
#include "../StepCtrl/61850/IECCfgGinChsGrid.h"
#include "../StepCtrl/61850/IECCfgGoutChsGrid.h"
#include "../StepCtrl/61850/IECCfgGoutDataGrid.h"
#include "../StepCtrl/61850/IECCfgOtherSettingGrid.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgTool.h"
#include "../../../../61850/Module/IecCfgSclTool/SclToIecCfgTool.h"
#include "MessageDlg.h"

IMPLEMENT_DYNAMIC(CIeccfgDeviceConfigDlg, CDialog)

CIeccfgDeviceConfigDlg::CIeccfgDeviceConfigDlg(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CIeccfgDeviceConfigDlg::IDD, pParent)
{
	Create(IDD, pParent);
	m_pIecCfgFile = NULL;
	m_pIecCfgDataGrid = NULL;
	m_pIecCfgDataChsGrid = NULL;
	m_pLastSelIecCfgData = NULL;
	m_pIecCfgData = NULL;
}

CIeccfgDeviceConfigDlg::~CIeccfgDeviceConfigDlg()
{
}

void CIeccfgDeviceConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SMV, m_txtSmv);
	DDX_Control(pDX, IDC_CBB_SMV, m_cbbSmv);
	DDX_Control(pDX, IDC_BTN_EXSETTING, m_btnExSetting);
	DDX_Control(pDX, IDC_BTN_IECADD, m_btnIECAdd);
	DDX_Control(pDX, IDC_BTN_IECDEL, m_btnIECDel);
	DDX_Control(pDX, IDC_CBB_SETTINGCFG, m_cbbSettingCfg);
	DDX_Control(pDX, IDC_TAB_CFG, m_tabCfg);
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
	DDX_Control(pDX, IDC_BTN_RETURN, m_btnReturn);
	DDX_Control(pDX, IDC_CB_ALL, m_btnAll);
	DDX_Control(pDX, IDC_CB_VOLT, m_btnVolt);
	DDX_Control(pDX, IDC_CB_CUR, m_btnCur);
}

void CIeccfgDeviceConfigDlg::OnInitialUpdate()
{
	XUI_InitAdjust();

	m_tabCfg.InsertItem(0, _T("SMV配置"));
	m_tabCfg.InsertItem(1, _T("GOOSE订阅配置"));
	m_tabCfg.InsertItem(2, _T("GOOSE发布配置"));
	m_tabCfg.InsertItem(3, _T("系统参数配置"));
	m_tabCfg.SetCurSel(0);

	m_tabSetting.InsertItem(0, _T("通道设置"));
	m_tabSetting.InsertItem(1, _T("其他设置"));
	m_tabSetting.SetCurSel(0);

	m_cbbSmv.InitIt();
	m_cbbSmv.SetSmvType(SMVTYPE_92);
	m_cbbSettingCfg.AddString(_T("配置为0"));
	m_cbbSettingCfg.AddString(_T("配置为abc1"));
	m_cbbSettingCfg.AddString(_T("配置为abc2"));
	m_cbbSettingCfg.AddString(_T("配置为abc3"));
	m_cbbSettingCfg.AddString(_T("配置为abc4"));
	m_cbbSettingCfg.AddString(_T("配置为abc5"));
	m_cbbSettingCfg.AddString(_T("配置为abc6"));
	m_cbbSettingCfg.SetCurSel(0);

	m_dlgIECSys.Create(CIECSysDlg::IDD, this);
	m_dlgIECSys.OnInitialUpdate();
	m_dlgIECSys.ShowWindow(SW_HIDE);

	m_btnVolt.SetCheck(TRUE);
}

void CIeccfgDeviceConfigDlg::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if(pGridCtrl->GetGridClassID() == "CIECCfgSmv92DataGrid"
		|| pGridCtrl->GetGridClassID() == "CIECCfgGoutDataGrid"
		|| pGridCtrl->GetGridClassID() == "CIECCfgGinDataGrid")
	{
		//20230828 huangliang 始终取第一列中对象
		nCol = 1;
		if (nRow <= 0 || nCol <= 0)
		{
			return;
		}

		PEXBASECELLDATA pVellData = (EXBASECELLDATA*)pGridCtrl->GetItemData(nRow, nCol);
		if (pVellData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  表格没有关联数据对象"), nRow, nCol);
			return;
		}

		ASSERT (pVellData->pObj != NULL);

		CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;

		if (pIecCfgData == NULL)
		{
			return;
		}

		if (m_pLastSelIecCfgData == pIecCfgData)
		{
			return;
		}

		m_pLastSelIecCfgData = pIecCfgData;
		ShowIECCfgChs();
	}
}

void CIeccfgDeviceConfigDlg::OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if(pGridCtrl->GetGridClassID() == "CIECCfgGoutDataGrid"
		|| pGridCtrl->GetGridClassID() == "CIECCfgGinDataGrid"
		|| pGridCtrl->GetGridClassID() == "CIECCfgSmv92DataGrid")
	{
		if (nCol == 1)
		{
			ShowIECCfgChs();
		}
	}
}

void CIeccfgDeviceConfigDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(IDC_STATIC_SMV, 0, 0, 0, 0);
	XUI_AddWnd(IDC_CBB_SMV, 0, 0, 0, 0);
	XUI_AddWnd(IDC_BTN_EXSETTING, 0, 0, 0, 0);
	XUI_AddWnd(IDC_BTN_IECADD, 1, 0, 0, 0);
	XUI_AddWnd(IDC_BTN_IECDEL, 1, 0, 0, 0);
	XUI_AddWnd(IDC_BTN_RETURN, 1, 0, 0, 0);
	XUI_AddWnd(IDC_GRID_IECCTRL, 0, 0, 1, 0);
	XUI_AddWnd(IDC_CBB_SETTINGCFG, 1, 0, 0, 0);
	XUI_AddWnd(IDC_CB_ALL, 1, 0, 0, 0);
	XUI_AddWnd(IDC_CB_VOLT, 1, 0, 0, 0);
	XUI_AddWnd(IDC_CB_CUR, 1, 0, 0, 0);
	XUI_AddWnd(IDC_GRID_IECCHS, 0, 0, 1, 0);
	XUI_AddWnd(IDC_TAB_CFG, 0, 0, 1, 0);
	XUI_AddWnd(IDC_TAB_SETTING, 0, 0, 1, 0);
	CXUIAdjItem_Area::XUI_OnSize();
}

void CIeccfgDeviceConfigDlg::CreateSMVDataGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CIecCfgDatasSMV *pDatasSmv = iecfg_GetIecCfgDatasSMV(m_pIecCfgFile);

	CRect rcGrid = GetDataGridRect();

	ClearDataGrid();

	if (pDatasSmv->IsSmvType92())
	{
		m_pIecCfgDataGrid = new CIECCfgSmv92DataGrid(IEC_CFG_DEVICE_USE_TYPE_ISmartTest);
	}
	else
	{
		ASSERT(FALSE);
	}

	m_pIecCfgDataGrid->Create(rcGrid, this, IDC_GRID_IECCTRL);
	m_pIecCfgDataGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataGrid->InitGrid();
	m_pIecCfgDataGrid->AttachDataViewOptrInterface(this);
} 

void CIeccfgDeviceConfigDlg::CreateSMVChsGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CIecCfgDatasSMV *pDatasSmv = iecfg_GetIecCfgDatasSMV(m_pIecCfgFile);

	CRect rcGrid = GetChsGridRect();

	ClearChsGrid();

	if (pDatasSmv->IsSmvType92())
	{
		m_pIecCfgDataChsGrid = new CIECCfgSmv92ChsGrid();
		m_pIecCfgDataChsGrid->SetViewChsPath(CIecCfgTool::IsViewChsPath());
	}
	else
	{
		ASSERT(FALSE);
	}

	m_pIecCfgDataChsGrid->Create(rcGrid, this, IDC_GRID_IECCHS);
	m_pIecCfgDataChsGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataChsGrid->InitGrid();
}

void CIeccfgDeviceConfigDlg::ShowIECCfgData()
{
	CIecCfgDatasBase* pIecCfgDatas = GetIecCfgDatas(m_tabCfg.GetCurSel());

	if (pIecCfgDatas == NULL)
	{
		return;
	}

	if (m_pIecCfgDataGrid == NULL
		|| m_pIecCfgDataChsGrid == NULL)
	{
		return;
	}

	//显示数据到表格，并选中第一个数据
	m_pIecCfgDataGrid->ShowDatas(pIecCfgDatas);
	m_pIecCfgDataGrid->SelectRow(1);

	//获取第一个配置数据对象，记录为最后一个选中的对象
	m_pLastSelIecCfgData = pIecCfgDatas->GetIecCfgData(0);
	m_pIecCfgData = m_pLastSelIecCfgData;

	ShowIECCfgChs();
}

void CIeccfgDeviceConfigDlg::ShowIECCfgChs()
{
	if (m_pLastSelIecCfgData == NULL)
	{
		m_pIecCfgDataChsGrid->ShowDatas(NULL);
	}
	else
	{
		m_pIecCfgDataChsGrid->SetEditable(m_pLastSelIecCfgData->m_nUseFlag);

		if (m_pLastSelIecCfgData->m_nUseFlag)
		{
			m_pIecCfgDataChsGrid->SetTextColor(RGB(0,0,0));
		} 
		else
		{
			m_pIecCfgDataChsGrid->SetTextColor(RGB(128,128,128));
		}

		if(m_pIecCfgDataChsGrid->GetGridClassID() == "CIECCfgOtherSettingGrid")
		{
			((CIECCfgOtherSettingGrid*)m_pIecCfgDataChsGrid)->ShowData(m_pLastSelIecCfgData);
		}
		else
		{
			m_pIecCfgDataChsGrid->ShowDatas(m_pLastSelIecCfgData->m_pCfgChs);
		}
	}
}

void CIeccfgDeviceConfigDlg::UpdateSMVDatas(BOOL bInit)
{
	if(bInit)
	{
		CreateSMVDataGrid();
	}
	CreateSMVChsGrid();
}

void CIeccfgDeviceConfigDlg::CreateGOOSEINDataGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CRect rcGrid = GetDataGridRect();

	ClearDataGrid();

	m_pIecCfgDataGrid = new CIECCfgGinDataGrid(IEC_CFG_DEVICE_USE_TYPE_ISmartTest);

	m_pIecCfgDataGrid->Create(rcGrid, this, IDC_GRID_IECCTRL);
	m_pIecCfgDataGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataGrid->InitGrid();
	m_pIecCfgDataGrid->AttachDataViewOptrInterface(this);
}

void CIeccfgDeviceConfigDlg::CreateGOOSEINChsGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CRect rcGrid = GetChsGridRect();

	ClearChsGrid();

	m_pIecCfgDataChsGrid = new CIECCfgGinChsGrid();
	m_pIecCfgDataChsGrid->SetViewChsPath(1);

	m_pIecCfgDataChsGrid->Create(rcGrid, this, IDC_GRID_IECCHS);
	m_pIecCfgDataChsGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataChsGrid->InitGrid();
}

void CIeccfgDeviceConfigDlg::UpdateGOOSEINDatas(BOOL bInit)
{
	if(bInit)
	{
		CreateGOOSEINDataGrid();
	}
	CreateGOOSEINChsGrid();
}

void CIeccfgDeviceConfigDlg::UpdateDatas(BOOL bInit)
{
	if(m_tabCfg.GetCurSel() == 3)
	{
		//获得当前数据视图对应的数据管理对象
		CIecCfgSysParas* pParas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetSysParasMngr();
		m_dlgIECSys.ShowWindow(SW_SHOW);
		CRect rc = GetSysRect();
		m_dlgIECSys.MoveWindow(rc);
		ShowCtrls(FALSE);
		m_dlgIECSys.UpdateDatas(m_pIecCfgFile);
		m_dlgIECSys.UpdateData(FALSE);
	}
	else
	{
		ShowCtrls(TRUE);
		m_dlgIECSys.ShowWindow(SW_HIDE);
		if(m_tabCfg.GetCurSel() == 0)
		{
			UpdateSMVDatas(bInit);
		}
		else if(m_tabCfg.GetCurSel() == 1)
		{
			m_btnExSetting.ShowWindow(SW_HIDE);
			m_cbbSmv.ShowWindow(SW_HIDE);
			m_cbbSettingCfg.ShowWindow(SW_HIDE);
			m_btnVolt.ShowWindow(SW_HIDE);
			m_btnCur.ShowWindow(SW_HIDE);
			m_btnAll.ShowWindow(SW_HIDE);
			UpdateGOOSEINDatas(bInit);
		}
		else if(m_tabCfg.GetCurSel() == 2)
		{
			m_btnExSetting.ShowWindow(SW_HIDE);
			m_cbbSmv.ShowWindow(SW_HIDE);
			m_cbbSettingCfg.ShowWindow(SW_HIDE);
			m_btnVolt.ShowWindow(SW_HIDE);
			m_btnCur.ShowWindow(SW_HIDE);
			m_btnAll.ShowWindow(SW_HIDE);
			UpdateGOOSEOUTDatas(bInit);
		}

		m_pIecCfgDataGrid->AttachRefChsGrid(m_pIecCfgDataChsGrid);
		m_pIecCfgDataChsGrid->AttachRefDataGrid(m_pIecCfgDataGrid);

		m_pIecCfgDataChsGrid->SetRowsHeight(20);

		if(bInit)
		{
			ShowIECCfgData();
			m_tabSetting.SetCurSel(0);
		}
		else
		{
			ShowIECCfgChs();
		}
	}
}

void CIeccfgDeviceConfigDlg::MoveWindow(LPCRECT lpRect, BOOL bRepaint /* = TRUE */)
{
	CDialog::MoveWindow(lpRect, bRepaint);

	CRect rc = GetDataGridRect();
	m_pIecCfgDataGrid->MoveWindow(rc);
	rc = GetChsGridRect();
	m_pIecCfgDataChsGrid->MoveWindow(rc);
}

void CIeccfgDeviceConfigDlg::ShowOtherSetting()
{
	if (m_pLastSelIecCfgData == NULL)
	{
		return;
	}

	CRect rcGrid = GetChsGridRect();

	ClearChsGrid();

	CIECCfgOtherSettingGrid* pIecCfgDataChsGrid = new CIECCfgOtherSettingGrid;

	pIecCfgDataChsGrid->SetViewChsPath(1);

	pIecCfgDataChsGrid->Create(rcGrid, this, IDC_GRID_IECCHS);
	pIecCfgDataChsGrid->SetFont(g_pGlobalFont11);
	pIecCfgDataChsGrid->InitGrid();
	pIecCfgDataChsGrid->SetRowsHeight(20);
	pIecCfgDataChsGrid->ShowData(m_pLastSelIecCfgData);
	m_pIecCfgDataChsGrid = pIecCfgDataChsGrid;
	m_pIecCfgDataChsGrid->AttachRefDataGrid(m_pIecCfgDataGrid);
	m_pIecCfgDataGrid->AttachRefChsGrid(m_pIecCfgDataChsGrid);
}

void CIeccfgDeviceConfigDlg::SetSclStation(CSclStation* pSclStation)
{
	m_pSclStation = pSclStation;
}

void CIeccfgDeviceConfigDlg::CreateGOOSEOUTDataGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	
	CRect rcGrid = GetDataGridRect();

	ClearDataGrid();

	m_pIecCfgDataGrid = new CIECCfgGoutDataGrid(IEC_CFG_DEVICE_USE_TYPE_ISmartTest );

	m_pIecCfgDataGrid->Create(rcGrid, this, IDC_GRID_IECCTRL);
	m_pIecCfgDataGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataGrid->InitGrid();
	m_pIecCfgDataGrid->AttachDataViewOptrInterface(this);
}

void CIeccfgDeviceConfigDlg::CreateGOOSEOUTChsGrid()
{
	if (m_pIecCfgFile == NULL)
	{
		return;
	}

	CRect rcGrid = GetChsGridRect();

	ClearChsGrid();

	m_pIecCfgDataChsGrid = new CIECCfgGoutDataChsGrid();
	m_pIecCfgDataChsGrid->SetViewChsPath(CIecCfgTool::IsViewChsPath());

	m_pIecCfgDataChsGrid->Create(rcGrid, this, IDC_GRID_IECCHS);
	m_pIecCfgDataChsGrid->SetFont(g_pGlobalFont11);
	m_pIecCfgDataChsGrid->InitGrid();
}

void CIeccfgDeviceConfigDlg::UpdateGOOSEOUTDatas(BOOL bInit)
{
	if(bInit)
	{
		CreateGOOSEOUTDataGrid();
	}
	CreateGOOSEOUTChsGrid();
}


void CIeccfgDeviceConfigDlg::SetIECCfgFile(CIecCfgFile* pIecCfg)
{
	m_pIecCfgFile = pIecCfg;
}

CIecCfgDatasBase* CIeccfgDeviceConfigDlg::GetIecCfgDatas(long nIndex)
{
	CIecCfgDatasBase *pIecCfgDatas = NULL;
	switch(nIndex)
	{
	case 0:
		pIecCfgDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetSmvMngr();
		break;
	case 1:	
		pIecCfgDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetGinMngr();
		break;
	case 2: 
		pIecCfgDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetGoutMngr();
		break;
	default:
		break;
	}

	return pIecCfgDatas;
}

CRect CIeccfgDeviceConfigDlg::GetDataGridRect()
{
	CRect rcTemp;
	m_btnIECDel.GetWindowRect(rcTemp);
	ScreenToClient(rcTemp);
	long nTop = rcTemp.bottom;
	m_cbbSettingCfg.GetWindowRect(rcTemp);
	ScreenToClient(rcTemp);
	long nBottom = rcTemp.top;
	CRect rcGrid;
	GetClientRect(&rcGrid);
	rcGrid.left = 5;
	rcGrid.right = rcTemp.right - 5;
	rcGrid.top = nTop + 5;
	rcGrid.bottom = nBottom - 5;
	return rcGrid;
}

CRect CIeccfgDeviceConfigDlg::GetChsGridRect()
{
	CRect rcTemp;
	m_cbbSettingCfg.GetWindowRect(rcTemp);
	ScreenToClient(rcTemp);
	long nTop = rcTemp.bottom;
	CRect rcGrid;
	GetClientRect(&rcGrid);
	rcGrid.left = 5;
	rcGrid.right = rcTemp.right - 5;
	rcGrid.top = nTop + 5;
	rcGrid.bottom -=  5;
	return rcGrid;
}

CRect CIeccfgDeviceConfigDlg::GetSysRect()
{
	CRect rcTemp;
	m_tabCfg.GetWindowRect(rcTemp);
	ScreenToClient(rcTemp);
	long nTop = rcTemp.bottom;
	CRect rcGrid;
	GetClientRect(&rcGrid);
	rcGrid.left = 5;
	rcGrid.right -= 5;
	rcGrid.top = nTop + 5;
	rcGrid.bottom -=  5;
	return rcGrid;
}

void CIeccfgDeviceConfigDlg::ClearDataGrid()
{
	if (m_pIecCfgDataGrid != NULL)
	{
		m_pIecCfgDataGrid->DestroyWindow();
		delete m_pIecCfgDataGrid;
		m_pIecCfgDataGrid = NULL;
	}
}

void CIeccfgDeviceConfigDlg::ClearChsGrid()
{
	if (m_pIecCfgDataChsGrid != NULL)
	{
		m_pIecCfgDataChsGrid->DestroyWindow();
		delete m_pIecCfgDataChsGrid;
		m_pIecCfgDataChsGrid = NULL;
	}
};

void CIeccfgDeviceConfigDlg::ShowCtrls(BOOL bShow)
{
	m_txtSmv.ShowWindow(bShow);
	m_cbbSmv.ShowWindow(bShow);
	m_btnExSetting.ShowWindow(bShow);
	m_btnIECAdd.ShowWindow(bShow);
	m_btnIECDel.ShowWindow(bShow);
	m_btnVolt.ShowWindow(bShow);
	m_btnCur.ShowWindow(bShow);
	m_btnAll.ShowWindow(bShow);
	m_cbbSettingCfg.ShowWindow(bShow);
	m_tabSetting.ShowWindow(bShow);
	if(m_pIecCfgDataGrid)
	{
		m_pIecCfgDataGrid->ShowWindow(bShow);
	}
	if(m_pIecCfgDataChsGrid)
	{
		m_pIecCfgDataChsGrid->ShowWindow(bShow);
	}
}

void CIeccfgDeviceConfigDlg::DeleteCtrlByAPPID(CIecCfgDatasBase* pDatas, long dwAppID)
{
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{
		CIecCfgDataBase* pData = (CIecCfgDataBase*)pDatas->GetNext(pos);
		if(pData->GetClassID() == CFGCLASSID_CIECCFG92DATA)
		{
			if(((CIecCfg92Data*)pData)->m_dwAppID == dwAppID)
			{
				pDatas->DeleteCfgData(pData);
				return;
			}
		}
		else if (pData->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			if(((CIecCfgGinData*)pData)->m_dwAppID == dwAppID)
			{
				pDatas->DeleteCfgData(pData);
				return;
			}
		}
		else if (pData->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			if(((CIecCfgGoutData*)pData)->m_dwAppID == dwAppID)
			{
				pDatas->DeleteCfgData(pData);
				return;
			}
		}
	}
}

BOOL CIeccfgDeviceConfigDlg::CheckAppIDExisted(CSclCtrlBase* pScl)
{
	CIecCfgGinDatas  *pIecCfgGinDatas  = m_pIecCfgFile->m_pIecCfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV  *pIecCfgDatasSMV  = m_pIecCfgFile->m_pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetGoutMngr();

	//GOOSE发送控制块默认配置到GOOSE订阅配置页面
	//GOOSE接收控制块默认配置到GOOSE发布配置页面
	CIecCfgDataBase* pTemp = NULL;
	if(pScl->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN)
	{
		CSclCtrlSmvIn* pTempScl = (CSclCtrlSmvIn*)pScl;
		POS pos = pIecCfgDatasSMV->GetHeadPosition();
		while (pos)
		{
			CIecCfg92Data* pData = (CIecCfg92Data*)pIecCfgDatasSMV->GetNext(pos);
			if(pData->m_dwAppID == pTempScl->m_dwAppID)
			{
				return FALSE;
			}
		}
	}
	else if (pScl->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
	{
		
		CSclCtrlGsIn* pTempScl = (CSclCtrlGsIn*)pScl;
		POS pos = pIecCfgGinDatas->GetHeadPosition();
		while (pos)
		{
			CIecCfgGinData* pData = (CIecCfgGinData*)pIecCfgGinDatas->GetNext(pos);
			if(pData->m_dwAppID == pTempScl->m_dwAppID)
			{
				return FALSE;
			}
		}
	}
	else if (pScl->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)
	{
		CSclCtrlGsOut* pTempScl = (CSclCtrlGsOut*)pScl;
		POS pos = pIecCfgGoutDatas->GetHeadPosition();
		while (pos)
		{
			CIecCfgGoutData* pData = (CIecCfgGoutData*)pIecCfgGoutDatas->GetNext(pos);
			if(pData->m_dwAppID == pTempScl->m_dwAppID)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CIeccfgDeviceConfigDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CFG, &CIeccfgDeviceConfigDlg::OnTcnSelchangeTabCfg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETTING, &CIeccfgDeviceConfigDlg::OnTcnSelchangeTabSetting)
	ON_CBN_SELCHANGE(IDC_CBB_SETTINGCFG, &CIeccfgDeviceConfigDlg::OnCbnSelchangeCbbSettingcfg)
	ON_BN_CLICKED(IDC_BTN_EXSETTING, &CIeccfgDeviceConfigDlg::OnBnClickedBtnExsetting)
	ON_BN_CLICKED(IDC_BTN_IECADD, &CIeccfgDeviceConfigDlg::OnBnClickedBtnIecadd)
	ON_BN_CLICKED(IDC_BTN_IECDEL, &CIeccfgDeviceConfigDlg::OnBnClickedBtnIecdel)
	ON_MESSAGE(WM_GIN_CH_APPID_CHANGED, &CIeccfgDeviceConfigDlg::OnGinChAppIDChanged)
	ON_BN_CLICKED(IDC_BTN_RETURN, &CIeccfgDeviceConfigDlg::OnBnClickedBtnReturn)
	ON_BN_CLICKED(IDC_CB_ALL, &CIeccfgDeviceConfigDlg::OnBnClickedCbAll)
END_MESSAGE_MAP()

void CIeccfgDeviceConfigDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CIeccfgDeviceConfigDlg::OnTcnSelchangeTabCfg(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(m_pIecCfgFile)
	{
		UpdateDatas(TRUE);
	}

	*pResult = 0;
}

void CIeccfgDeviceConfigDlg::OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(m_tabSetting.GetCurSel())
	{
		ShowOtherSetting();
	}
	else
	{
		UpdateDatas();
	}
	*pResult = 0;
}

void CIeccfgDeviceConfigDlg::OnCbnSelchangeCbbSettingcfg()
{
	long m_bUseMapVol = 0, m_bUseMapCur = 0;
	long nIndex = m_cbbSettingCfg.GetCurSel();

	if(m_btnAll.GetCheck())
	{
		m_bUseMapVol = m_bUseMapCur = 1;
	}
	else
	{
		if(m_btnVolt.GetCheck())
		{
			m_bUseMapVol = 1;
			m_bUseMapCur = 0;
		}
		else
		{
			m_bUseMapVol = 0;
			m_bUseMapCur = 1;
		}
	}

	UpdateData(TRUE);

	switch(nIndex)
	{
	case 0: ((CIecCfgSmvDataBase*)m_pIecCfgData)->Set0(m_bUseMapVol, m_bUseMapCur); break;
	case 1: ((CIecCfgSmvDataBase*)m_pIecCfgData)->SetAbc(m_bUseMapVol, m_bUseMapCur, TRUE); break;
	case 2: ((CIecCfgSmvDataBase*)m_pIecCfgData)->SetPabc(m_bUseMapVol, m_bUseMapCur, TRUE); break;
	case 3: ((CIecCfgSmvDataBase*)m_pIecCfgData)->SetSabc(m_bUseMapVol, m_bUseMapCur, TRUE); break;
	case 4: ((CIecCfgSmvDataBase*)m_pIecCfgData)->SetTabc(m_bUseMapVol, m_bUseMapCur, TRUE); break;
	case 5: ((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc5(m_bUseMapVol, m_bUseMapCur, TRUE); break;
	case 6: ((CIecCfgSmvDataBase*)m_pIecCfgData)->Setabc6(m_bUseMapVol, m_bUseMapCur, TRUE); break;
	default:
		break;
	}

	m_pIecCfgDataChsGrid->UpdateDatas();
}

void CIeccfgDeviceConfigDlg::OnBnClickedBtnExsetting()
{
	CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)GetIecCfgDatas(m_tabCfg.GetCurSel());
	CIECCfgExDlg dlg;
	dlg.SetIecCfg(pIecCfgDatasSMV);
	if (dlg.DoModal() == IDOK)
	{
		CIecCfgTool::SetIecCfgSmvRates(dlg.GetIecCfg(), m_pIecCfgFile);
	}
	
	dlg.ClearClone();
}

void CIeccfgDeviceConfigDlg::OnBnClickedBtnIecadd()
{
	CIECCfgAddDlg dlg;
	dlg.Init(m_pSclStation);
	CExBaseList* pList = new CExBaseList;
	dlg.Attach(pList);
	long nRes = dlg.DoModal();
	if(nRes == IDOK)
	{
		CSclToIecCfgTool oSclToIecCfgTool;
		oSclToIecCfgTool.AttacthSclFileRead(m_pSclStation);
		POS pos = pList->GetHeadPosition();
		CString strErr;
		while (pos)
		{
			CSclCtrlsSmvIn oSclSmvIn;
			CSclCtrlsGsIn oSclGsIn;
			CSclCtrlsGsOut oSclGsOut;

			CSclCtrlBase* pScl = (CSclCtrlBase*)pList->GetNext(pos);
					
			CString strText;
			if(pScl->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN)
			{
				if(!CheckAppIDExisted(pScl))
				{
					strText.Format("重复SMV控制块(%s)\n", pScl->m_strMac);
					strErr += strText;
					continue;
				}

				oSclSmvIn.AddTail(pScl);
			}
			else if (pScl->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
			{
				if(!CheckAppIDExisted(pScl))
				{
					strText.Format("重复GOOSEOUT控制块(%s)\n", pScl->m_strMac);
					strErr += strText;
					continue;
				}

				oSclGsOut.AddTail(pScl);
			}
			else if (pScl->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)
			{
				if(!CheckAppIDExisted(pScl))
				{
					strText.Format("重复GOOSEIN控制块(%s)\n", pScl->m_strMac);
					strErr += strText;
					continue;
				}

				oSclGsIn.AddTail(pScl);
			}

			oSclToIecCfgTool.AddToIecCfg(&oSclSmvIn, &oSclGsOut, &oSclGsIn, m_pIecCfgFile->m_pIecCfgDatasMngr);
		}

		CIecCfgDatasBase* pIecCfgDatas = GetIecCfgDatas(m_tabCfg.GetCurSel());
		m_pIecCfgDataGrid->ShowDatas(pIecCfgDatas);
		m_pIecCfgDataGrid->SelectRow(1);

		if(strErr.GetLength())
		{
			MessageDlg::MessageBox("提示", strErr, MessageDlg::YES);
		}
	}
}

void CIeccfgDeviceConfigDlg::OnBnClickedBtnIecdel()
{
	if (m_pLastSelIecCfgData == NULL)
	{
		return;
	}

	CExBaseList oListItems;
	m_pIecCfgDataGrid->GetCurrSelDatas(oListItems, 1);

	if (oListItems.GetCount() == 0)
	{
		return;
	}

	CIecCfgDatasBase* pIecCfgDatas = GetIecCfgDatas(m_tabCfg.GetCurSel());
	if ((m_pIecCfgDataGrid->GetRowCount() - 1) == oListItems.GetCount())
	{
		MessageDlg::MessageBox("提示", "至少保留一个配置数据对象", MessageDlg::YES);
		oListItems.RemoveAll();
		return;
	}

	POS pos = oListItems.GetHeadPosition();
	while(pos)
	{
		CIecCfgDataBase* pData = (CIecCfgDataBase*)oListItems.GetNext(pos);
		long dwAppID = 0;
		if(pData->GetClassID() == CFGCLASSID_CIECCFG92DATA)
		{
			dwAppID = ((CIecCfg92Data*)pData)->m_dwAppID;
		}
		else if (pData->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			dwAppID = ((CIecCfgGinData*)pData)->m_dwAppID;
		}
		else if (pData->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			dwAppID = ((CIecCfgGoutData*)pData)->m_dwAppID;
		}

		DeleteCtrlByAPPID(pIecCfgDatas, dwAppID);
	}

	oListItems.RemoveAll();
	m_pIecCfgDataGrid->ShowDatas(pIecCfgDatas);
	m_pLastSelIecCfgData = m_pIecCfgData = (CIecCfgDataBase*)pIecCfgDatas->GetHead();
	m_pIecCfgDataChsGrid->ShowDatas(m_pLastSelIecCfgData->m_pCfgChs);
}

LRESULT CIeccfgDeviceConfigDlg::OnGinChAppIDChanged(WPARAM wParam, LPARAM lParam)
{
	CIecCfgGinDatas* m_pGinDatas = (CIecCfgGinDatas *)m_pIecCfgData->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
	m_pGinDatas->InitGinAppChMaps();
	return 0;
}

void CIeccfgDeviceConfigDlg::OnBnClickedBtnReturn()
{
	GetParentWnd()->SendMessage(WM_IECCFG_RETURN, 0, 0);
}

void CIeccfgDeviceConfigDlg::OnBnClickedCbAll()
{
	if(m_btnAll.GetCheck())
	{
		m_btnCur.EnableWindow(FALSE);
		m_btnVolt.EnableWindow(FALSE);
	}
	else
	{
		m_btnCur.EnableWindow(TRUE);
		m_btnVolt.EnableWindow(TRUE);	
	}
}
