#include "stdafx.h"
#include "WzdMainDlg.h"
#include "WzdDlg_DvmMap.h"
#include "../StepCtrl/DlgDvmDatasetMap.h"
#include "../StepCtrl/DvmMapSelDatasetDlg.h"
#include "../../../../Module/API/GloblaDrawFunctions.h"
#include "MessageDlg.h"

CWzdDlg_DvmMap* g_DvmMapDlg = NULL;

IMPLEMENT_DYNAMIC(CWzdDlg_DvmMap, CDialog)

CWzdDlg_DvmMap::CWzdDlg_DvmMap(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdDlg_DvmMap::IDD, pParent)
{
	g_DvmMapDlg = this;
	m_pGbDvmReplaceTool = NULL;
	m_pCurDatasetMap = NULL;
	m_bIsReplacing = FALSE;
	m_strInfo = "          站控层信息配置: 将选择的继电保护装置的模型文件与测试标准模型文件进行映射替换，"
		"\n配置结果标识数据集数据映射成功率。\n"
		"          界面操作： "
		"\n          1、双击选择行，可显示和修改对应数据集配置；"
		"\n          2、右击选择行，可删除和新增配置数据集；";
}

CWzdDlg_DvmMap::~CWzdDlg_DvmMap()
{
	if(m_pGbDvmReplaceTool)
	{
		delete m_pGbDvmReplaceTool;
		m_pGbDvmReplaceTool = NULL;
	}
}

void CWzdDlg_DvmMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_MAP, m_gridMap);
	DDX_Control(pDX, IDC_DVMMAP_STATIC, m_txtTitle);
	DDX_Control(pDX, IDC_DVMMAP_TIP, m_txtTip);
}

void CWzdDlg_DvmMap::OnInitialUpdate()
{
	XUI_InitAdjust();
	m_oDvmCmpTool.OpenKeyDataTypesFile(_T("DvmTestKeyDataTypes.xml"));
	m_gridMap.InitGrid();

	m_txtTip.SetWindowText(m_strInfo);
}

// void CWzdDlg_DvmMap::SetMaxRange(long nMaxRange)
// {
// 	m_nStepCurrIndex = 0;
// 	m_nMaxRange = nMaxRange;
// }
// 
// void CWzdDlg_DvmMap::ResetProcess()
// {
// 
// }
// 
// void CWzdDlg_DvmMap::StepIt()
// {
// 	m_nStepCurrIndex++;
// 
// 	if (m_nStepCurrIndex >= m_nMaxRange)
// 	{
// 
// 	}
// }
// 
// void CWzdDlg_DvmMap::Finish(DWORD dwParam)
// {
// 	//模型替换结束，切换到导入定值单的视图
// 	m_bIsReplacing = FALSE;
// }
// 
// void CWzdDlg_DvmMap::StartTimer(long nTimerLong)
// {
// 
// }
// 
// void CWzdDlg_DvmMap::ShowMsg(const CString &strMsg)
// {
// 	CLogPrint::LogString(XLOGLEVEL_INFOR, strMsg);
// }

void CWzdDlg_DvmMap::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_gridMap, 0, 0, 1, 1);
	XUI_AddWnd(&m_txtTitle, 0, 0, 1, 0);
	XUI_AddWnd(&m_txtTip, 0, 1, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

BOOL CWzdDlg_DvmMap::DoNext()
{
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);
 	//初始化替换的对象
	CDevice *pDevice = g_pWzdMainDlg->m_oGuideBook.GetDevice();
	if(!pDevice)
	{
		MessageDlg::MessageBox("错误", "检测到错误的模型文件,请确认后重新进入配置!", MessageDlg::ERRYES);
		PostMessage(WM_QUIT,0,0);
		return FALSE;
	}
	CCpus *pCpus = pDevice->GetCpus();   //即模板中的device-model节点

	if(m_pGbDvmReplaceTool)
	{
		delete m_pGbDvmReplaceTool;
		m_pGbDvmReplaceTool = NULL;
	}
	m_pGbDvmReplaceTool = new CGbDvmReplaceTool;
	m_pGbDvmReplaceTool->BuildRepalce(pDevice, pCpus);

	//根据选择的数据集初始化替换数据对象
	CDvmDeviceMap *pDvmDeviceMap = &m_oDvmCmpTool.m_oDvmDeviceMap;
	pDvmDeviceMap->InitAfterRead();
	POS pos = pDvmDeviceMap->m_listDatasetMap.GetHeadPosition();
	CDvmDatasetMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmDatasetMap *) pDvmDeviceMap->m_listDatasetMap.GetNext(pos);
		m_pGbDvmReplaceTool->AddDatasetMap(pMap);
	}

	//打开数据模型文件，替换掉相关的数据集
	pCpus->DvmReplaceByMap(pDvmDeviceMap);

	//执行替换
	g_theThreadPrgsDlg->SetTitle(_T("数据模型替换"));
	m_pGbDvmReplaceTool->m_pGbDvmReplaceEvent = this;
	m_pGbDvmReplaceTool->CreateGbDvmReplaceThread(g_theThreadPrgsDlg);

	return TRUE;
}

void CWzdDlg_DvmMap::ReplaceFinished()
{
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);

	//20230608 huangliang 因打开pdf时报错，故将SendMessage改为PostMessage
	//GetParentWnd()->SendMessage(WM_DVMMAP_DONEXT, 0, 0);
	GetParentWnd()->PostMessage(WM_DVMMAP_DONEXT, 0, 0);
}

void CWzdDlg_DvmMap::CmpDeviceFile(const CString& strFile)
{
	g_theThreadPrgsDlg->SetTitle(_T("装置模型智能匹配"));
	m_oDvmCmpTool.m_pPrgsInterface = g_theThreadPrgsDlg;
	m_strDestFile = strFile;
	m_oDvmCmpTool.CmpDeviceFile(m_strStandFile, m_strDestFile);
	CDvmLDeviceMap* pDevice = (CDvmLDeviceMap*)m_oDvmCmpTool.m_oDvmDeviceMap.GetHead();
	m_gridMap.ShowDatas(pDevice);
}

void CWzdDlg_DvmMap::UpdateDvmTitle(const CString& strText)
{
	m_txtTitle.SetWindowText(strText);
}

void CWzdDlg_DvmMap::UpdateStandFile(const CString& strFile)
{
	m_strStandFile = strFile;
}

BEGIN_MESSAGE_MAP(CWzdDlg_DvmMap, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_DVMMAP_CREATEDATAMAP_STAND, &CWzdDlg_DvmMap::OnCreateDatasetMap_Stand)
	ON_COMMAND(ID_DVMMAP_CREATEDATAMAP_DEST, &CWzdDlg_DvmMap::OnCreateDatasetMap_Dest)
	ON_COMMAND(ID_DVMMAP_DELETEDATAMAP_STAND, &CWzdDlg_DvmMap::OnDeleteDatasetMap_Stand)
	ON_COMMAND(ID_DVMMAP_DELETEDATAMAP_DEST, &CWzdDlg_DvmMap::OnDeleteDatasetMap_Dest)
	ON_MESSAGE(WM_OPEN_DVMCMP_DATASET, &CWzdDlg_DvmMap::OnOpenDvmCmpDataset)
	ON_MESSAGE(WM_DVMREPLACE_FINISH, &CWzdDlg_DvmMap::OnReplaceFinish)
	ON_MESSAGE(WM_DVMMAP_MENU, &CWzdDlg_DvmMap::OnMenuMessage)
END_MESSAGE_MAP()

void CWzdDlg_DvmMap::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdDlg_DvmMap::OnCreateDatasetMap_Stand()
{
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);

	CDvmMap_SelDatasetDlg dlg;
	dlg.m_pDatasetMap = (CDvmDatasetMap*)m_pCurDatasetMap;
	dlg.m_pDvmDevice = (CDvmDevice *)m_oDvmCmpTool.m_oDvmDeviceMap.m_pMap;

	if (dlg.DoModal() != IDOK)
	{
		GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
		GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);

		return;
	}

	CDvmDatasetMap *pDatasetMap = m_gridMap.AddDatasetMap(dlg.m_pDvmDataset, TRUE);
	pDatasetMap->AddNullDvmMap_Stand();
	m_oDvmCmpTool.CmpDvmDataset(pDatasetMap, FALSE);
	pDatasetMap->CountErrMapCount();
	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pDatasetMap->m_dwItemData;
	if (pProp != NULL)
	{
		pProp->SetNameEx(pDatasetMap);
	}
	dvmmap_SetDvmMapModifiedFlag(pDatasetMap);
	m_gridMap.UpdateDatas();

	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
}

void CWzdDlg_DvmMap::OnCreateDatasetMap_Dest()
{

}

void CWzdDlg_DvmMap::OnDeleteDatasetMap_Stand()
{
	CDvmDatasetMap *pDatasetMap = m_pCurDatasetMap;

	if (pDatasetMap == NULL)
	{
		return;
	}

	long nIndex = 0;
	CDvmLDeviceMap *pLdeviceMap = (CDvmLDeviceMap*)pDatasetMap->GetParent();
	dvmmap_SetDvmMapModifiedFlag(pDatasetMap);
	pLdeviceMap->Delete(pDatasetMap);
	m_gridMap.UpdateDatas();
}

void CWzdDlg_DvmMap::OnDeleteDatasetMap_Dest()
{

}

HRESULT CWzdDlg_DvmMap::OnOpenDvmCmpDataset(WPARAM wParam, LPARAM lParam)
{
	CDvmDatasetMap *pDvmCmp = (CDvmDatasetMap*)wParam;

	if (pDvmCmp->m_pMap == NULL || pDvmCmp->m_pStand == NULL)
	{
		return 0;
	}

	CDlgDvmDatasetMap oDlg;
	CString strTitle;
	strTitle.Format(_T("数据集映射【%s-%s】"), pDvmCmp->m_strName, pDvmCmp->m_strID);
	oDlg.m_strTitle = strTitle;
	oDlg.m_pDvmCmpObj = pDvmCmp;

	if (oDlg.DoModal() != IDOK)
	{
		return 0;
	}

	//保存

	return 0;
}

LRESULT CWzdDlg_DvmMap::OnMenuMessage(WPARAM wParam, LPARAM lParam)
{
	long nX = wParam;
	long nY = lParam;
	long nRow = m_gridMap.GetCurrSelRow();
	CExBaseObject *pSelObj = (CExBaseObject*)m_gridMap.GetItemData(nRow, 0);

	if (pSelObj == NULL)
	{
		return FALSE;
	}

	if (pSelObj->GetClassID() != DMPCLASSID_CDVMDATASETMAP)
	{
		return FALSE;
	}

	m_pCurDatasetMap = (CDvmDatasetMap*)pSelObj;

	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING,ID_DVMMAP_CREATEDATAMAP_STAND,_T("创建数据集映射"));

	if (m_pCurDatasetMap->m_pMap != NULL)
	{
		menu.AppendMenu(MF_STRING,ID_DVMMAP_DELETEDATAMAP_STAND,_T("删除数据集映射"));
	}

	CRect rc;
	m_gridMap.GetClientRect(rc);
	m_gridMap.ClientToScreen(rc);
	menu.TrackPopupMenu(TPM_LEFTALIGN,rc.left + nX, rc.top + nY, this);	

	return TRUE;
}

LRESULT CWzdDlg_DvmMap::OnReplaceFinish(WPARAM wParam, LPARAM lParam)
{
	return 0;
}