#include "stdafx.h"
#include "WzdDlg_IECCfg.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgFile.h"
#include "../StepDlg/ThreadPrgsDlg.h"
#include "MessageDlg.h"

#define IECAUTOBTN_FIRST 20001

IMPLEMENT_DYNAMIC(CWzdDlg_IECCfg, CDialog)

CWzdDlg_IECCfg::CWzdDlg_IECCfg(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdDlg_IECCfg::IDD, pParent)
{
	m_pSelSmvIecfgDataMngrDlg = NULL;
	m_strType = IECCFG_TRANSFORM;
}

CWzdDlg_IECCfg::~CWzdDlg_IECCfg()
{
	m_oIecCfgDatasMngrList.RemoveAll();
	m_oGsSmvChList.RemoveAll();

	if (m_pSelSmvIecfgDataMngrDlg != NULL)
	{
		delete m_pSelSmvIecfgDataMngrDlg;
	}
}

void CWzdDlg_IECCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_IECGSIN, m_btnGsIn);
	DDX_Control(pDX, IDC_BTN_IECGSOUT, m_btnGsOut);
	DDX_Control(pDX, IDC_BTN_IECSETTING, m_btnIECSetting);
	DDX_Control(pDX, IDC_GRID_IECSMVCH, m_gridCh_Smv_Gs);
	DDX_Control(pDX, IDC_GRID_IECSMV, m_gridSmv);
	DDX_Control(pDX, IDC_STATIC_SMV, m_txtSmv);
	DDX_Control(pDX, IDC_STATIC_SMVCH, m_txtSmvCh);
	DDX_Control(pDX, IDC_BTN_IECSMV, m_btnSmv);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
}

void CWzdDlg_IECCfg::OnInitialUpdate()
{
	XUI_InitAdjust();

	m_dlgIECCfg.SetParentWnd(this);
	m_dlgIECCfg.OnInitialUpdate();
	m_dlgIECCfg.ShowWindow(SW_HIDE);

	m_gridSmv.InitGrid();
	m_gridCh_Smv_Gs.InitGrid();

	//20230811 huangliang 显示GOOSE发布
	//m_btnGsOut.EnableWindow(FALSE);
}

void CWzdDlg_IECCfg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_btnSmv, 0, 0, 0.33, 0);
	XUI_AddWnd(&m_btnGsIn, 0.33, 0, 0.33, 0);
	XUI_AddWnd(&m_btnGsOut, 0.66, 0, 0.33, 0);
	XUI_AddWnd(&m_btnIECSetting, 1, 0, 0, 0);
	XUI_AddWnd(&m_btnSave, 1, 0, 0, 0);
	XUI_AddWnd(&m_gridSmv, 0, 0, 1, 0);
	XUI_AddWnd(&m_gridCh_Smv_Gs, 0, 0, 1, 1);
	XUI_AddWnd(&m_txtSmv, 0, 0, 0, 0);
	XUI_AddWnd(&m_txtSmvCh, 0, 0, 0, 0);
	CXUIAdjItem_Area::XUI_OnSize();
}

BOOL CWzdDlg_IECCfg::InitUI(CDataGroup* pDataGroup)
{
	m_pDataCfg = pDataGroup;
	return TRUE;
}

//20230619 huangliang 初始化IED文件的选择，返回上一步时，改变了选择内容，即使相同的Iecc文件也需要重新加载
void CWzdDlg_IECCfg::InitIECFileChoose()
{
	m_strIeccfgFile = _T("");
}
void CWzdDlg_IECCfg::LoadIecfgFile(const CString& strFile)
{
	if (m_strIeccfgFile == strFile)
	{
		return;
	}

	m_strIeccfgFile = strFile;
	m_oIecCfgFileDevice.Open(strFile);
	
	IecCfgDeviceCover();

	m_oIecCfgDatasMngrList.RemoveAll();

	g_theThreadPrgsDlg->ShowMsg(_T("Load:") + strFile);
	CIecCfgDevice *pCIecCfgDevice = m_oIecCfgFileDevice.GetIecCfgDevice();

	POS pos = pCIecCfgDevice->GetHeadPosition();
	while(pos)
	{
		CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)pCIecCfgDevice->GetNext(pos);
		if(pDatas->GetClassID() == SCLIECCLASSID_IED)
		{
			continue;
		}

		m_oIecCfgDatasMngrList.AddTail(pDatas);	
	}

}
void CWzdDlg_IECCfg::IecCfgDeviceCover()
{//覆盖
	//20231023 huangliang 在CIecCfgDevice类中实现，释放前再克隆
	m_oIecCfgFileDevice.GetIecCfgDevice()->CopyFirstGinGoutToAnther();
	//CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
	//CIecCfgGinDatas* pGinDatas = pDatas->GetGinMngr();
	//CIecCfgGoutDatas* pGoutDatas= pDatas->GetGoutMngr();

	//POS posData = NULL;
	//CExBaseObject *p = NULL;

	//POS posDevice = m_oIecCfgFileDevice.GetIecCfgDevice()->GetHeadPosition();	//第一组(IEd不能在第一组)
	////m_oIecCfgFileDevice.GetIecCfgDevice()->GetNext(posDevice);	//20231023 huangliang IEd组,在循环中排序
	//while (posDevice)
	//{
	//	pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetNext(posDevice);
	//	if(pDatas->GetClassID() == SCLIECCLASSID_IED)
	//	{
	//		continue;
	//	}

	//	if(pDatas->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR && pDatas->GetGinMngr() != pGinDatas)
	//	{
	//		pDatas->GetGinMngr()->DeleteAll();
	//		pDatas->SetGinMngr(pGinDatas);	//20231020 huangliang 此处只设置了m_pGinMngr指向，链表中未改变

	//		//20231020 huangliang 改变链表中数据地址
	//		posData = pDatas->GetHeadPosition();
	//		while(posData)
	//		{
	//			p = pDatas->GetNext(posData);
	//			if (p->GetClassID() == CFGCLASSID_CIECCFGDATASGIN)
	//			{
	//				pDatas->Remove(p);
	//				pDatas->InsertBefore(posData, pGinDatas);
	//				break;
	//			}
	//		}			
	//	}
	//	if(pDatas->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR && pDatas->GetGoutMngr() != pGoutDatas)
	//	{
	//		pDatas->GetGoutMngr()->DeleteAll();
	//		pDatas->SetGoutMngr(pGoutDatas);	//20231020 huangliang 此处只设置了m_pGinMngr指向，链表中未改变

	//		//20231020 huangliang 改变链表中数据地址
	//		posData = pDatas->GetHeadPosition();
	//		while(posData)
	//		{
	//			p = pDatas->GetNext(posData);
	//			if (p->GetClassID() == CFGCLASSID_CIECCFGDATASGOUT)
	//			{
	//				pDatas->Remove(p);
	//				pDatas->InsertBefore(posData, pGoutDatas);
	//				break;
	//			}
	//		}
	//	}
	//}
}
void CWzdDlg_IECCfg::ShowIecfgFile()
{
	if (m_pSelSmvIecfgDataMngrDlg != NULL)
	{
		delete m_pSelSmvIecfgDataMngrDlg;
	}

	m_pSelSmvIecfgDataMngrDlg = new CSmvIecfgDataMngrSelDlg();
	m_pSelSmvIecfgDataMngrDlg->Create(this);
	m_pSelSmvIecfgDataMngrDlg->ShowWindow(SW_HIDE);
	m_pSelSmvIecfgDataMngrDlg->AttachDatas(&m_oIecCfgDatasMngrList);
}

void CWzdDlg_IECCfg::SetSclStation(CSclStation* pSclStation)
{
	m_dlgIECCfg.SetSclStation(pSclStation);
}

BOOL CWzdDlg_IECCfg::DoPrev()
{
	if (m_pSelSmvIecfgDataMngrDlg != NULL)
	{
		m_pSelSmvIecfgDataMngrDlg->Exit();
	}

	return TRUE;
}

BOOL CWzdDlg_IECCfg::DoNext()
{
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);

	if (m_pSelSmvIecfgDataMngrDlg != NULL)
	{
		m_pSelSmvIecfgDataMngrDlg->Exit();
	}

	GetParentWnd()->SendMessage(WM_CONNECT_UPDATE, 0, 0);

	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CWzdDlg_IECCfg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_IECCFG_RETURN, &CWzdDlg_IECCfg::OnSettingReturn)
	ON_MESSAGE(WM_IECCFG_CLICKED, &CWzdDlg_IECCfg::OnAutoBtnClicked)
	ON_BN_CLICKED(IDC_BTN_IECSETTING, &CWzdDlg_IECCfg::OnBnClickedBtnIecsetting)
	ON_BN_CLICKED(IDC_BTN_IECGSIN, &CWzdDlg_IECCfg::OnBnClickedBtnIecgsin)
	ON_BN_CLICKED(IDC_BTN_IECGSOUT, &CWzdDlg_IECCfg::OnBnClickedBtnIecgsout)
	ON_BN_CLICKED(IDC_BTN_IECSMV, &CWzdDlg_IECCfg::OnBnClickedBtnIecsmv)
	ON_MESSAGE(WM_IECCFG_UPDATEGS, &CWzdDlg_IECCfg::OnUpdateGs)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CWzdDlg_IECCfg::OnBnClickedBtnSave)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CWzdDlg_IECCfg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);

	//20230620 huangliang 界面变化后，按钮位置大小需要跟随变化
	if (m_pSelSmvIecfgDataMngrDlg != NULL)
	{
		m_pSelSmvIecfgDataMngrDlg->XUI_InitAdjust();
	}

	if(m_btnGsIn.IsHold() || m_btnGsOut.IsHold())
	{
		ChangGooseFaceSize();
	}
}

void CWzdDlg_IECCfg::OnWindowPosChanging()
{
	if (m_pSelSmvIecfgDataMngrDlg == NULL)
	{
		return;
	}

	if(m_pSelSmvIecfgDataMngrDlg->IsWindowVisible())
	{
		CRect rc, rcIn;
		m_btnGsIn.GetWindowRect(rcIn);
		GetWindowRect(rc);
		rc.top = rcIn.bottom + 5;
		m_pSelSmvIecfgDataMngrDlg->MoveWindow(rc);
	}
}

BOOL CWzdDlg_IECCfg::SaveXmlFile()
{
	return m_oIecCfgFileDevice.Save(FALSE);
}

LRESULT CWzdDlg_IECCfg::OnSettingReturn(WPARAM wParam, LPARAM lParam)
{
	ShowOwnWindow(SW_SHOW);
	m_dlgIECCfg.ShowWindow(SW_HIDE);

	//20230630 huangliang 去掉此处清除，改为加载函数中清除
	//m_gridCh_Smv_Gs.ClearDataTypes();
	if(m_gridCh_Smv_Gs.m_tagType == CIECSmvChGrid::MODE_SMV)
	{
		m_gridSmv.UpdateDatas();

		m_oGsSmvChList.RemoveAll();
		CollectAllSmvCh(&m_oGsSmvChList);
		m_gridCh_Smv_Gs.ShowDatas(&m_oGsSmvChList);//20240221 luozibing 根据当前选择项更新Gs表格
	}
	else if(m_gridCh_Smv_Gs.m_tagType == CIECSmvChGrid::MODE_GOOSE_IN)
	{
		//20230630 huangliang 重新加载数据类型
		ReLoadAllGsChDataType();

		SmvGridToGsGrid();

		m_oGsinChList.DeleteAll();
		CollectAllGsCh(&m_oGsinChList);
		m_gridCh_Smv_Gs.ShowDatas(&m_oGsinChList);
	}
	else 
	{
		ReLoadAllGsOutChDataType();

		SmvGridToGsGrid(false);

		m_oGsoutChList.DeleteAll();
		CollectAllGsOutCh(&m_oGsoutChList);
		m_gridCh_Smv_Gs.ShowDatas(&m_oGsoutChList);
	}

	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
	return TRUE;
}
//20230630 huangliang 加载数据类型
void CWzdDlg_IECCfg::ReLoadAllGsChDataType()
{
	m_gridCh_Smv_Gs.ClearDataTypes();

	CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
	CIecCfgGinDatas* pGinDatas = pDatas->GetGinMngr();

	POS posGin = pGinDatas->GetHeadPosition();
	while(posGin)
	{
		CIecCfgGinData* pGinData = (CIecCfgGinData*)pGinDatas->GetNext(posGin);
		if(pGinData->m_nUseFlag != 1)
		{
			continue;
		}

		CIecCfgChsBase* pChs = pGinData->m_pCfgChs;
		m_gridCh_Smv_Gs.AddDataType(pChs);
	}
}
void CWzdDlg_IECCfg::ReLoadAllGsOutChDataType()
{
	m_gridCh_Smv_Gs.ClearOutDataTypes();

	CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
	CIecCfgGoutDatas* pGoutDatas = pDatas->GetGoutMngr();

	POS posGout = pGoutDatas->GetHeadPosition();
	while(posGout)
	{
		CIecCfgGoutData* pGoutData = (CIecCfgGoutData*)pGoutDatas->GetNext(posGout);
		if(pGoutData->m_nUseFlag != 1)
		{
			continue;
		}

		CIecCfgChsBase* pChs = pGoutData->m_pCfgChs;
		m_gridCh_Smv_Gs.AddDataTypeForGsOut(pChs);
	}
}

LRESULT CWzdDlg_IECCfg::OnAutoBtnClicked(WPARAM wParam, LPARAM lParam)
{
	m_btnGsIn.SetHold(false);
	m_btnSmv.SetHold(true);

	if(wParam)
	{
		GsGridToSmvGrid();

		CString strText;
		m_txtSmv.GetWindowText(strText);
		if(strText.Find(":") != -1)
		{
			strText = strText.Mid(0, strText.Find(":") + 1);
		}
		CString strBtn = (char*)lParam;
		m_txtSmv.SetWindowText(strText + strBtn);
		m_txtSmvCh.GetWindowText(strText);
		if(strText.Find(":") != -1)
		{
			strText = strText.Mid(0, strText.Find(":") + 1);
		}
		m_txtSmvCh.SetWindowText(strText + strBtn);

		//wparam是item所带的data
		CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)wParam;
		m_oIecCfgFileDevice.GetIecCfgDevice()->SetCurrDatasMngr(pDatas);
 		m_gridSmv.ShowDatas(pDatas->GetSmvMngr());
		m_gridSmv.SelectRow(1);
		
		m_oGsSmvChList.RemoveAll();
		CollectAllSmvCh(&m_oGsSmvChList);
		m_gridCh_Smv_Gs.ShowDatas(&m_oGsSmvChList);//20240221 luozibing 根据当前选择项更新Gs表格
	}
	else
	{
		ShowSelectDlg(TRUE);
	}

	return TRUE;
}

LRESULT CWzdDlg_IECCfg::OnUpdateGs(WPARAM wParam, LPARAM lParam)
{
	if(m_gridCh_Smv_Gs.m_tagType == CIECSmvChGrid::MODE_GOOSE_IN)
	{
		m_oGsinChList.DeleteAll();
		CollectAllGsCh(&m_oGsinChList);
		m_gridCh_Smv_Gs.ShowDatas(&m_oGsinChList);

		//20230629 huangliang
		ReBindData();
	}
	else if(m_gridCh_Smv_Gs.m_tagType == CIECSmvChGrid::MODE_SMV) //20240221 luozibing 根据当前选择项更新Gs表格
	{
		m_oGsSmvChList.RemoveAll();
		CollectAllSmvCh(&m_oGsSmvChList);
		m_gridCh_Smv_Gs.ShowDatas(&m_oGsSmvChList);
	}
	else 
	{
		m_oGsoutChList.DeleteAll();
		CollectAllGsOutCh(&m_oGsoutChList);
		m_gridCh_Smv_Gs.ShowDatas(&m_oGsoutChList);
	}	
	return TRUE;
}
//20230629 huangliang 需要绑定m_oIecCfgFileDevice.m_pIecCfgDatasMngr->m_pGinMngr->m_oIecCfgGinAppChMaps列表中对象的m_pIecCfgGinCh
void CWzdDlg_IECCfg::ReBindData()
{
	CIecCfgDevice *pIecCfgDevice = m_oIecCfgFileDevice.GetIecCfgDevice();
	CIecCfgDatasMngr *pIecCfgDatasMngr = pIecCfgDevice->GetCurrDatasMngr();
	CIecCfgGinDatas *pIecCfgGinDatas = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgGinAppChMaps *poIecCfgGinAppChMaps = pIecCfgGinDatas->GetIecCfgGinAppChMaps();

	POS pos = poIecCfgGinAppChMaps->GetHeadPosition();
	while(pos)
	{
		CIecCfgGinAppChMap* pGinChMap = (CIecCfgGinAppChMap*)poIecCfgGinAppChMaps->GetNext(pos);
		CString strCh = pGinChMap->m_strID;
		CIecCfgGinCh* pCh = FindGsInChByID(strCh);
		poIecCfgGinAppChMaps->Bind(strCh, pCh);
	}
}

void CWzdDlg_IECCfg::ShowOwnWindow(BOOL bShow)
{
	m_txtSmv.ShowWindow(bShow);
	m_txtSmvCh.ShowWindow(bShow);
	m_btnSmv.ShowWindow(bShow);
	m_btnGsIn.ShowWindow(bShow);
	m_btnGsOut.ShowWindow(bShow);
	m_btnIECSetting.ShowWindow(bShow);
	m_gridCh_Smv_Gs.ShowWindow(bShow);
	m_gridSmv.ShowWindow(bShow);
	m_btnSave.ShowWindow(bShow);
}

void CWzdDlg_IECCfg::OnBnClickedBtnIecsetting()
{
	if(!m_oIecCfgFileDevice.GetIecCfgDevice()->GetCurrDatasMngr())
	{
		MessageDlg::MessageBox("错误", "请至少选中一个配置!", MessageDlg::ERRYES);
		return;
	}

	ShowOwnWindow(SW_HIDE);

	m_oIecCfgFileDevice.m_pIecCfgDatasMngr = m_oIecCfgFileDevice.GetIecCfgDevice()->GetCurrDatasMngr();
	m_dlgIECCfg.SetIECCfgFile(&m_oIecCfgFileDevice);

	if(m_gridCh_Smv_Gs.m_tagType == CIECSmvChGrid::MODE_SMV)
	{
		m_dlgIECCfg.SetTableCfg(0);
	}
	else if(m_gridCh_Smv_Gs.m_tagType == CIECSmvChGrid::MODE_GOOSE_IN)
	{
		m_dlgIECCfg.SetTableCfg(1);
	}
	else 
	{
		m_dlgIECCfg.SetTableCfg(2);
	}

	m_dlgIECCfg.UpdateDatas(TRUE);

	CRect rc;
	GetClientRect(rc);
	m_dlgIECCfg.ShowWindow(SW_SHOW);
	m_dlgIECCfg.MoveWindow(rc);

	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);
}

CIecCfgGinCh* CWzdDlg_IECCfg::FindGsInChByID(const CString& strID)
{
	CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
	CIecCfgGinDatas* pGinDatas = pDatas->GetGinMngr();

	POS posGin = pGinDatas->GetHeadPosition();
	while(posGin)
	{
		CIecCfgGinData* pGinData = (CIecCfgGinData*)pGinDatas->GetNext(posGin);
		if(pGinData->m_nUseFlag != 1)
		{
			continue;
		}

		CIecCfgChsBase* pChs = pGinData->m_pCfgChs;
		POS pos = pChs->GetHeadPosition();
		while (pos)
		{
			CIecCfgGinCh* pCh = (CIecCfgGinCh*)pChs->GetNext(pos);

			if(pCh->m_strAppChID.Find(strID) != -1)
			{
				return pCh;
			}
		}
	}

	return NULL;
}

void CWzdDlg_IECCfg::SmvGridToGsGrid(bool bIn)
{
	if(bIn)
		m_gridCh_Smv_Gs.SetGridType(CIECSmvChGrid::MODE_GOOSE_IN);
	else
		m_gridCh_Smv_Gs.SetGridType(CIECSmvChGrid::MODE_GOOSE_OUT);

	m_gridSmv.ShowWindow(SW_HIDE);
	m_txtSmv.ShowWindow(SW_HIDE);
	m_txtSmvCh.ShowWindow(SW_HIDE);
	m_btnSave.ShowWindow(SW_HIDE);
	m_gridCh_Smv_Gs.HideColumnBorder(1);

	ChangGooseFaceSize();
}
void CWzdDlg_IECCfg::ChangGooseFaceSize()
{
	CRect rc, rcGrid;
	m_btnIECSetting.GetWindowRect(rc);
	ScreenToClient(rc);
	GetClientRect(rcGrid);
	rcGrid.top = rc.bottom + 10;
	m_gridCh_Smv_Gs.MoveWindow(rcGrid);
}

void CWzdDlg_IECCfg::GsGridToSmvGrid()
{
	m_gridCh_Smv_Gs.SetGridType(CIECSmvChGrid::MODE_SMV);

	m_gridSmv.ShowWindow(SW_SHOW);
	m_txtSmv.ShowWindow(SW_SHOW);
	m_txtSmvCh.ShowWindow(SW_SHOW);
	m_btnSave.ShowWindow(SW_SHOW);
	m_gridCh_Smv_Gs.ShowColumnBorder(1);

	CRect rc, rcGrid;
	m_gridSmv.GetWindowRect(rc);
	ScreenToClient(rc);
	GetClientRect(rcGrid);
	rcGrid.top = rc.bottom + 26;
	m_gridCh_Smv_Gs.MoveWindow(rcGrid);
}

void CWzdDlg_IECCfg::CollectAllSmvCh(CExBaseList* pList)
{
	int nRow = m_gridSmv.GetCurrSelRow();
	CString strName = m_gridSmv.GetItemText(nRow,1);
	CIecCfgDatasMngr* pDatas = m_oIecCfgFileDevice.GetIecCfgDevice()->GetCurrDatasMngr();
	POS pos = pDatas->GetSmvMngr()->GetHeadPosition();
	CIecCfg92Ch *pObj = NULL;
	while (pos)
	{
		CIecCfg92Data* pData = (CIecCfg92Data*)pDatas->GetSmvMngr()->GetNext(pos);
		if(pData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
		{
			continue;
		}

		POS posChild = pData->GetHeadPosition();
		while (posChild)
		{
			CIecCfg92Chs* pChs = (CIecCfg92Chs*)pData->GetNext(posChild);
			if(pChs->GetClassID() != CFGCLASSID_CIECCFGCHS92)
			{
				continue;
			}

			//20230626 huangliang 过程层中需过滤被引用的SV
			//pList->Append(pChs);
			POS posData = pChs->GetHeadPosition();
			while (posData)
			{
				pObj = (CIecCfg92Ch*)pChs->GetNext(posData);
				if(pObj == NULL)
					continue;
				if(pObj->m_nIndexExternal == -1)
					continue;
				
				if(pObj->GetClassID() != CFGCLASSID_CIECCFG92CH)
				{
					continue;
				}
				CIecCfg92Data* pParent = (CIecCfg92Data*)pChs->GetParent();//->GetParent();luozibing 20210221
				CString strChName = pParent->m_pSclRef->m_strName;
				if(strChName.Find("--") != -1)
				{
					strChName = strChName.Mid(strChName.Find("--") + 2);
				}

				if(strName == strChName)
				{
				pList->AddTail(pObj);
			}
		}
	}
	}
}

void CWzdDlg_IECCfg::CollectAllGsCh(CExBaseList* pList)
{
	//因为Device下所有的控制块的goose-in理应一致，所以调用第一个，然后覆盖其他的
	CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
	CIecCfgGinDatas* pGinDatas = pDatas->GetGinMngr();
	CIecCfgGinAppChMaps* pChMaps = pGinDatas->GetIecCfgGinAppChMaps();
	POS pos = pChMaps->GetHeadPosition();
	while(pos)
	{
		CIecCfgGinAppChMap* pGinChMap = (CIecCfgGinAppChMap*)pGinDatas->GetNext(pos);
		CIECChMap* pChMap = new CIECChMap;
		pChMap->m_pChMap = pGinChMap;
		pChMap->m_pIedSel = m_oIecCfgFileDevice.GetIecCfgDevice()->m_pSclIed;
		CString strCh = pGinChMap->m_strID;
		CIecCfgGinCh* pCh = FindGsInChByID(strCh);
		pChMap->m_pCh = pCh ? (CIecCfgGinCh*)pCh->Clone() : 0;
		pChMap->m_pCh ? pChMap->m_pCh->SetParent(pCh->GetParent()) : 0;
		m_oGsinChList.AddNewChild(pChMap);
	}

	
}

void CWzdDlg_IECCfg::OnBnClickedBtnIecgsin()
{
	if(!m_oIecCfgFileDevice.GetIecCfgDevice()->GetCurrDatasMngr())
	{
		CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
		m_oIecCfgFileDevice.GetIecCfgDevice()->SetCurrDatasMngr(pDatas);
	}

	//20230628 huangliang 返回上一步后再次进入时，重新加载数据
	ReLoadAllGsChDataType();

	m_btnSmv.SetHold(false);
	m_btnGsIn.SetHold(true);
	m_btnGsOut.SetHold(false);

	if (m_pSelSmvIecfgDataMngrDlg != NULL)
	{
		m_pSelSmvIecfgDataMngrDlg->Exit();
	}

	SmvGridToGsGrid();
 	m_oGsinChList.DeleteAll();
	CollectAllGsCh(&m_oGsinChList);
 	m_gridCh_Smv_Gs.ShowDatas(&m_oGsinChList);
	m_gridCh_Smv_Gs.m_bInitDataTypes = true;
}

CIecCfgGoutCh* CWzdDlg_IECCfg::FindGsOutChByID(const CString& strID)
{
	//因为Device下所有的控制块的goose-out理应一致，所以调用第一个，然后覆盖其他的
	CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
	CIecCfgGoutDatas* pGoutDatas = pDatas->GetGoutMngr();
	POS posGout = pGoutDatas->GetHeadPosition();
	while(posGout)
	{
		CIecCfgGoutData* pGouData = (CIecCfgGoutData*)pGoutDatas->GetNext(posGout);
		if(pGouData->m_nUseFlag != 1)
		{
			continue;
		}

		CIecCfgChsBase* pChs = pGouData->m_pCfgChs;
		POS pos = pChs->GetHeadPosition();
		while (pos)
		{
			CIecCfgGoutCh* pCh = (CIecCfgGoutCh*)pChs->GetNext(pos);
			if(pCh->m_strAppChID.Find(strID) != -1)
			{
				return pCh;
			}
		}
	}
	return NULL;
}
void CWzdDlg_IECCfg::CollectAllGsOutCh(CExBaseList* pList)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(g_strGsChDtID_goose_out_ch_single);
	POS pos = pDataType->GetHeadPosition();
	CDataTypeValue* pDValue = NULL;
	while(pos)
	{
		pDValue = (CDataTypeValue*)pDataType->GetNext(pos);
		if(pDValue->m_strName == _T("---"))
			continue;

		CIECChOutMap* pChMap = new CIECChOutMap;
		pChMap->m_strID = pDValue->m_strID;
		pChMap->m_strName = pDValue->m_strName;
		pChMap->m_pCh = FindGsOutChByID(pDValue->m_strID);
		m_oGsoutChList.AddNewChild(pChMap);
	}
}
void CWzdDlg_IECCfg::OnBnClickedBtnIecgsout()
{
	if(!m_oIecCfgFileDevice.GetIecCfgDevice()->GetCurrDatasMngr())
	{
		CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_oIecCfgFileDevice.GetIecCfgDevice()->GetHead();
		m_oIecCfgFileDevice.GetIecCfgDevice()->SetCurrDatasMngr(pDatas);
	}

	ReLoadAllGsOutChDataType();

	m_btnSmv.SetHold(false);
	m_btnGsIn.SetHold(false);
	m_btnGsOut.SetHold(true);

	if (m_pSelSmvIecfgDataMngrDlg != NULL)
	{
		m_pSelSmvIecfgDataMngrDlg->Exit();
	}

	SmvGridToGsGrid(false);

	m_oGsoutChList.DeleteAll();
	CollectAllGsOutCh(&m_oGsoutChList);
 	m_gridCh_Smv_Gs.ShowDatas(&m_oGsoutChList);
}

void CWzdDlg_IECCfg::OnBnClickedBtnIecsmv()
{
	SendMessage(WM_IECCFG_CLICKED, 0, 0);
}

void CWzdDlg_IECCfg::ShowSelectDlg(BOOL bShow)
{
	if (m_pSelSmvIecfgDataMngrDlg == NULL)
	{
		return;
	}

	if(bShow == SW_HIDE)
	{
		m_pSelSmvIecfgDataMngrDlg->Exit();
		return;
	}


	m_pSelSmvIecfgDataMngrDlg->ShowWindow(SW_SHOW);
	CRect rc, rcIn;
	m_btnGsIn.GetWindowRect(rcIn);
	GetWindowRect(rc);
	rc.top = rcIn.bottom + 5;
	m_pSelSmvIecfgDataMngrDlg->MoveWindow(rc);
}

void CWzdDlg_IECCfg::OnBnClickedBtnSave()
{
	if (m_pSelSmvIecfgDataMngrDlg == NULL)
	{
		return;
	}

	CString strText;
	m_txtSmv.GetWindowText(strText);
	strText = strText.Mid(strText.Find(":") + 1);

	if(MessageDlg::MessageBox("提示", "是否标记为已修改?", MessageDlg::YESANDNO) == IDYES)
	{
		m_pSelSmvIecfgDataMngrDlg->SetBtnType(strText, CIECAutoBtn::CURRENTSAVE);
	}
	else
	{
		m_pSelSmvIecfgDataMngrDlg->SetBtnType(strText, CIECAutoBtn::CURRENT);
	}

	ShowSelectDlg(TRUE);
}

void CWzdDlg_IECCfg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWzdDlgBase::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		if (m_pSelSmvIecfgDataMngrDlg != NULL)
		{
			m_pSelSmvIecfgDataMngrDlg->UpdateBbns();
		}

		ShowSelectDlg(TRUE);
	}
}
