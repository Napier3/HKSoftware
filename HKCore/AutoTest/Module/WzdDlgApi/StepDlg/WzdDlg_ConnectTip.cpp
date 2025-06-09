#include "stdafx.h"
#include "WzdDlg_ConnectTip.h"
#include "WzdMainDlg.h"

CString GetRealFiber(long nIndex)
{
	CString strFiber;
	strFiber.Format("光口%d", nIndex + 1);
	return strFiber;
}

void CConnectSVGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(4);
	SetColumnCount(1);
	SetFixedRowCount(1);
	InitGridTitle();
}

void CConnectSVGrid::InitGridTitle()
{
	CString astrSclIedsGirdTitle[2] = {_T("继保仪输出光口"),_T("继电保护装置接收光口IED描述")};
	const int nSclIedsWidth[2]={200, 300};
	SetColumnCount(2);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, 2);
}

void CConnectSVGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CIecCfg92Data* p92Data = (CIecCfg92Data*)pData;
	if(p92Data->GetClassID() != CFGCLASSID_CIECCFG92DATA)
	{
		return;
	}

	Show_StaticString(p92Data, nRow, 0, GetRealFiber(p92Data->m_nFiberIndex));
	Show_StaticString(p92Data, nRow, 1, p92Data->m_pSclRef->m_strName);
	
	nRow++;
}

void CConnectGsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(4);
	SetColumnCount(1);
	SetFixedRowCount(1);
	InitGridTitle();
}

void CConnectGsGrid::InitGridTitle()
{
	CString astrSclIedsGirdTitle[2] = {_T("继保仪接收光口"),_T("GOOSE输出IED描述")};
	const int nSclIedsWidth[2]={200, 300};
	SetColumnCount(2);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, 2);
}

void CConnectGsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CIecCfgGinData* pGinData = (CIecCfgGinData*)pData;
	Show_StaticString(pGinData, nRow, 0, GetRealFiber(pGinData->m_nFiberIndex));
	CIecCfgDevice* pIecDevice = (CIecCfgDevice*)pGinData->GetParent()->GetParent()->GetParent();
	CString strDesc;
	strDesc.Format("%s-%s", pIecDevice->m_pSclIed->m_strName ,pGinData->m_strIedRefDesc);
	Show_StaticString(pGinData, nRow, 1, strDesc);
	nRow++;
}

IMPLEMENT_DYNAMIC(CWzdDlg_ConnectTip, CDialog)

CWzdDlg_ConnectTip::CWzdDlg_ConnectTip(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdDlg_ConnectTip::IDD, pParent)
{
	m_pIecFileDevice = NULL;
}

CWzdDlg_ConnectTip::~CWzdDlg_ConnectTip()
{
}

void CWzdDlg_ConnectTip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DEVICE, m_txtDevice);
	DDX_Control(pDX, IDC_STATIC_FACTORY, m_txtFactor);
	DDX_Control(pDX, IDC_STATIC_FACTORY2, m_txtFactor2);
	DDX_Control(pDX, IDC_STATIC_IP, m_txtIP);
	DDX_Control(pDX, IDC_STATIC_IP2, m_txtIP2);
	DDX_Control(pDX, IDC_STATIC_CONNECT, m_txtConnect);
	DDX_Control(pDX, IDC_STATIC_SV, m_txtSV);
	DDX_Control(pDX, IDC_STATIC_GOOSE, m_txtGOOSE);
	DDX_Control(pDX, IDC_STATIC_INFO, m_txtInfo);
	DDX_Control(pDX, IDC_BTN_FACTORY_JUMP, m_btnJumpFactory);
	DDX_Control(pDX, IDC_BTN_IP_JUMP, m_btnJumpIP);
	DDX_Control(pDX, IDC_BTN_SV_JUMP, m_btnJumpSV);
	DDX_Control(pDX, IDC_BTN_GS_JUMP, m_btnJumpGs);
	DDX_Control(pDX, IDC_GRID_CONNECTSV, m_gridSV);
	DDX_Control(pDX, IDC_GRID_CONNECTGS, m_gridGs);
}

void CWzdDlg_ConnectTip::OnInitialUpdate()
{
	XUI_InitAdjust();

	CString strInfo = "请根据IP地址，将继电保护测试仪的网口连接到装置相应IP的网口；\n"
		"如果网口被占用，可根据能够使用的装置网口IP设置IP地址，并连接相应的网线。";
	m_txtInfo.SetWindowText(strInfo);

	m_gridGs.InitGrid();
	m_gridSV.InitGrid();

	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/";
	m_btnJumpFactory.LoadImage(strImg + "jump_n.png", strImg + "jump_y.png", strImg + "jump_h.png");
	m_btnJumpFactory.SetImgMode(TRUE);
	m_btnJumpIP.LoadImage(strImg + "jump_n.png", strImg + "jump_y.png", strImg + "jump_h.png");
	m_btnJumpIP.SetImgMode(TRUE);
	m_btnJumpSV.LoadImage(strImg + "jump_n.png", strImg + "jump_y.png", strImg + "jump_h.png");
	m_btnJumpSV.SetImgMode(TRUE);
	m_btnJumpGs.LoadImage(strImg + "jump_n.png", strImg + "jump_y.png", strImg + "jump_h.png");
	m_btnJumpGs.SetImgMode(TRUE);
}

void CWzdDlg_ConnectTip::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_txtGOOSE, 0, 0.5, 0, 0);
	XUI_AddWnd(&m_btnJumpGs, 0, 0.5, 0, 0);
	XUI_AddWnd(&m_gridSV, 0, 0, 1, 0.5);
	XUI_AddWnd(&m_gridGs, 0, 0.5, 1, 0.5);
	XUI_AddWnd(&m_txtInfo, 0, 0, 1, 0);
	CXUIAdjItem_Area::XUI_OnSize();
}

void CWzdDlg_ConnectTip::SetAddress(const CString& strIP)
{
	m_txtIP2.SetWindowText(strIP);
}

void CWzdDlg_ConnectTip::SetFactory(const CString& strFactory)
{
	m_txtFactor2.SetWindowText(strFactory);
}

void CWzdDlg_ConnectTip::UpdateGrid(CExBaseObject* pIecFileDevice)
{
	m_pIecFileDevice = ((CIecCfgFileDevice*)pIecFileDevice)->GetIecCfgDevice();
	
	CExBaseList oList;
	POS pos = m_pIecFileDevice->GetHeadPosition();
	while(pos)
	{
		CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_pIecFileDevice->GetNext(pos);
		if(pDatas->GetClassID() == SCLIECCLASSID_IED)
		{
			continue;
		}

		oList.Append(pDatas->GetSmvMngr());
	}

	m_gridSV.ShowDatas(&oList);
	oList.RemoveAll();

	CIecCfgDatasMngr* pDatas = (CIecCfgDatasMngr*)m_pIecFileDevice->GetHead();
	oList.Append(pDatas->GetGinMngr());
	m_gridGs.ShowDatas(&oList);
	oList.RemoveAll();
}

void CWzdDlg_ConnectTip::SetMd5(const CString& strParameterMd5, const CString& strSettingMd5, const CString& strEnaMd5)
{
	m_strParameterMd5 = strParameterMd5;
	m_strSettingMd5 = strSettingMd5;
	m_strEnaMd5 = strEnaMd5;
}

BOOL CWzdDlg_ConnectTip::DoNext()
{
	CString strFile;
	strFile.Format("%s.iecfg", m_pIecFileDevice->m_pSclIed->m_strID);
	strFile = _P_GetTemplatePath() + strFile;
	m_pIecFileDevice->SaveAsIecCfgFile(strFile);

	CDataGroup* pRoot = new CDataGroup;
	CDataGroup* pDevice = pRoot->AddNewGroup("被测设备信息","DeviceInfor","");
	pDevice->m_strValue = "1";
	CString strFactory, strIP;
	m_txtFactor2.GetWindowText(strFactory);
	m_txtIP2.GetWindowText(strIP);
	CDvmData* pDeviceData = pDevice->AddNewData("Factory", strFactory);
	pDeviceData->m_strName = "生产厂家";
	pDeviceData = pDevice->AddNewData("IP", strIP);
	pDeviceData->m_strName = "IP地址";

	//定值单
	CDataGroup* pSetInfor = pRoot->AddNewGroup("定值单信息","SetInfor","");
	if(!m_strParameterMd5.GetLength())
	{
		pSetInfor->m_strValue = "0";
	}
	else
	{
		pSetInfor->m_strValue = "1";
		pSetInfor->AddNewData("设备参数哈希值", "ParameterMd5", "", m_strParameterMd5);
		pSetInfor->AddNewData("保护压板哈希值", "RelayEnaMd5", "", m_strEnaMd5);
		pSetInfor->AddNewData("设备参数哈希值", "SettingMd5", "", m_strSettingMd5);
	}

	strFile.Format("%s.wzdxml", m_pIecFileDevice->m_pSclIed->m_strID);
	strFile = _P_GetTemplatePath() + strFile;
	pRoot->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	pRoot->DeleteAll();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CWzdDlg_ConnectTip, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_FACTORY_JUMP, &CWzdDlg_ConnectTip::OnBnClickedBtnFactoryJump)
	ON_BN_CLICKED(IDC_BTN_IP_JUMP, &CWzdDlg_ConnectTip::OnBnClickedBtnIpJump)
	ON_BN_CLICKED(IDC_BTN_SV_JUMP, &CWzdDlg_ConnectTip::OnBnClickedBtnSvJump)
	ON_BN_CLICKED(IDC_BTN_GS_JUMP, &CWzdDlg_ConnectTip::OnBnClickedBtnGsJump)
END_MESSAGE_MAP()

void CWzdDlg_ConnectTip::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdDlg_ConnectTip::OnBnClickedBtnFactoryJump()
{
	CString strDlg = DLG_STEP_SenceSel;
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_RETURN, (WPARAM)strDlg.GetString(), 1);
}

void CWzdDlg_ConnectTip::OnBnClickedBtnIpJump()
{
	CString strDlg = DLG_STEP_IEDSel;
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_RETURN, (WPARAM)strDlg.GetString(), 1);
}

void CWzdDlg_ConnectTip::OnBnClickedBtnSvJump()
{
	CString strDlg = DLG_STEP_IECCfg;
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_RETURN, (WPARAM)strDlg.GetString(), 1);
}

void CWzdDlg_ConnectTip::OnBnClickedBtnGsJump()
{
	CString strDlg = DLG_STEP_IECCfg;
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_RETURN, (WPARAM)strDlg.GetString(), 1);
}
