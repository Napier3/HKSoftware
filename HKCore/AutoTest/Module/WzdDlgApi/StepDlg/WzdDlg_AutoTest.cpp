// WzdDlg_AutoTest.cpp : 实现文件
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "WzdDlg_AutoTest.h"
#include "WzdMainDlg.h"
//#include "ExBaseList.h"
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "..\..\..\iSmartTestWzd\iSmartTestWzdDlg.h"

// WzdDlg_AutoTest 对话框

IMPLEMENT_DYNAMIC(CWzdDlg_AutoTest, CDialog)

CWzdDlg_AutoTest::CWzdDlg_AutoTest(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzdDlg_AutoTest::IDD, pParent)
{
	m_pFrame = NULL;
	m_pGlobalDataList = NULL;
	m_pDeviceDataList = NULL;
	m_nAutoTestState = AUTOTEST_NULL;
	m_mapStateIcon.clear();
	m_nTestResultState = 1;
	m_nPreTestItemState = 1;
	m_pCurTestItem = NULL;
	m_pInputDlg = NULL;
	m_bIsStarTimer = false;
	m_nState_BlueTooth = NetState_Ethernet;
}

CWzdDlg_AutoTest::~CWzdDlg_AutoTest()
{
	//m_pGlobalDataList = NULL;
	//m_pDeviceDataList = NULL;
	//m_TestStepDataList.RemoveAll();
	if(m_bIsStarTimer)
	{
		KillTimer(TimeEvent_State);
	}
	
}

void CWzdDlg_AutoTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINE_STATIC, m_LineStatic);
	DDX_Control(pDX, IDC_TEST_STATIC1, m_TestStatic1);
	DDX_Control(pDX, IDC_TEST_STATIC2, m_TestStatic2);
	DDX_Control(pDX, IDC_COMM_STATIC1, m_CommStatic1);
	DDX_Control(pDX, IDC_COMM_STATIC2, m_CommStatic2);
	DDX_Control(pDX, IDC_OUTPUT_STATIC1, m_OutputStatic1);
	DDX_Control(pDX, IDC_OUTPUT_STATIC2, m_OutputStatic2);
	DDX_Control(pDX, IDC_TCP_STATIC1, m_TcpStatic1);
	DDX_Control(pDX, IDC_TCP_STATIC2, m_TcpStatic2);
	DDX_Control(pDX, IDC_TOOTH_STATIC1, m_ToothStatic1);
	DDX_Control(pDX, IDC_TOOTH_STATIC2, m_ToothStatic2);
	DDX_Control(pDX, IDC_DEVICE_INFO_STATIC, m_DeviceInfoStatic);
	DDX_Control(pDX, IDC_LOG_LIST, m_ctrlLogListBox);
	DDX_Control(pDX, IDC_CUTSOM_WINDOW, m_ctrlBtnCutsomWin);
	DDX_Control(pDX, IDC_STAR_BUTTON, m_ctrlBtnStarTest);
	DDX_Control(pDX, IDC_STOP_BUTTON, m_ctrlBtnStopTest);
	DDX_Control(pDX, IDC_FINISH_BUTTON, m_ctrlBtnFinishTest);
	DDX_Control(pDX, IDC_SET_BUTTON, m_ctrlBtnSet);
	DDX_Control(pDX, IDC_BOOTH_BUTTON, m_ctrlBtnBooth);
	DDX_Control(pDX, IDC_PEO_AUTO_CONFIRM_CHECK, m_ctrlBtnPerConfirm);
	DDX_Control(pDX, IDC_TEST_ITEM_AUTO_CHECK, m_ctrlBtnTestResultAuto);
}

BEGIN_MESSAGE_MAP(CWzdDlg_AutoTest, CDialog)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_STAR_BUTTON, &CWzdDlg_AutoTest::OnBnClickedStarButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CWzdDlg_AutoTest::OnBnClickedStopButton)
	ON_BN_CLICKED(IDC_FINISH_BUTTON, &CWzdDlg_AutoTest::OnBnClickedFinishButton)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CWzdDlg_AutoTest::OnBnClickedSetButton)
	ON_BN_CLICKED(IDC_PEO_AUTO_CONFIRM_CHECK, &CWzdDlg_AutoTest::OnBnClickedPeoAutoConfirmCheck)
	ON_BN_CLICKED(IDC_TEST_ITEM_AUTO_CHECK, &CWzdDlg_AutoTest::OnBnClickedTestItemAutoCheck)
	ON_MESSAGE(WM_TEST_STEP_CHANG, &CWzdDlg_AutoTest::OnTestStepChange)
	ON_MESSAGE(WM_TEST_STATE_CHANGE, &CWzdDlg_AutoTest::OnItemStateChanged)

	ON_MESSAGE(WM_TEST_STATE_STAR, &CWzdDlg_AutoTest::OnTestStarted)
	ON_MESSAGE(WM_TEST_STATE_STOP, &CWzdDlg_AutoTest::OnTestStoped)
	ON_MESSAGE(WM_TEST_STATE_FINISH, &CWzdDlg_AutoTest::OnTestFinished)
	ON_MESSAGE(WM_TEST_STATE_CREATE, &CWzdDlg_AutoTest::OnTestCreated)
	ON_MESSAGE(WM_TEST_STATE_REPORT, &CWzdDlg_AutoTest::OnReport)
	ON_MESSAGE(WM_TEST_STATE_BOOTH, &CWzdDlg_AutoTest::OnSetNetState)
	ON_MESSAGE(WM_TEST_ONINPUTDATA, &CWzdDlg_AutoTest::OnInputData)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BOOTH_BUTTON, &CWzdDlg_AutoTest::OnBnClickedBoothButton)
	ON_COMMAND(ID_LOG_DELETE, &CWzdDlg_AutoTest::OnLogDelete)
	ON_COMMAND(ID_LOG_CLEAR, &CWzdDlg_AutoTest::OnLogClear)
END_MESSAGE_MAP()


// WzdDlg_AutoTest 消息处理程序
void CWzdDlg_AutoTest::OnInitialUpdate()
{
	m_dlgTestStep.Create(CWzd_TestStepDlg::IDD,&m_Spliter);
	m_dlgTestStep.SetDlgCtrlID(m_Spliter.IdFromRowCol(0,0));
	m_dlgTestStep.XUI_InitAdjust();
	m_dlgTestStep.ShowWindow(SW_NORMAL);

	m_dlgCheckItem.Create(CWzd_CheckItemDlg::IDD,&m_Spliter);
	m_dlgCheckItem.SetDlgCtrlID(m_Spliter.IdFromRowCol(0,1));
	m_dlgCheckItem.XUI_InitAdjust();
	m_dlgCheckItem.ShowWindow(SW_NORMAL);

	m_dlgFailItem.Create(CWzd_FailItemDlg::IDD,&m_Spliter);
	m_dlgFailItem.SetDlgCtrlID(m_Spliter.IdFromRowCol(1,0));
	m_dlgFailItem.XUI_InitAdjust();
	m_dlgFailItem.ShowWindow(SW_NORMAL);

	m_dlgCheckResult.Create(CWzd_CheckResultDlg::IDD,&m_Spliter);
	m_dlgCheckResult.SetDlgCtrlID(m_Spliter.IdFromRowCol(1,1));
	m_dlgCheckResult.XUI_InitAdjust();
	m_dlgCheckResult.ShowWindow(SW_NORMAL);

	initWholeState();
	initButton();
	SetAutoTestState(m_nAutoTestState);

//	CString strImg1 = strImg+ "star.png";
//	HBITMAP IcImage1 = (HBITMAP)LoadImage(NULL, strImg1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//	m_ctrlBtnStarTest.SetBitmap(IcImage1);

	XUI_InitAdjust();
	CRect cRect;
	GetDlgItem(IDC_CUTSOM_WINDOW)->GetWindowRect(&cRect);
	ScreenToClient(&cRect);

	m_pFrame->MoveWindow(&cRect);
	m_pFrame->ShowWindow(SW_SHOW);
	m_Spliter.MoveWindow(0,0,cRect.Width(),cRect.Height());

	m_Spliter.SetRowInfo(0,cRect.Height()/2, 50);
	m_Spliter.SetRowInfo(1,cRect.Height()/2, 50);
	m_Spliter.SetColumnInfo(0,cRect.Width()/2, 200);
	m_Spliter.SetColumnInfo(1,cRect.Width()/2, 200);

	m_Spliter.RecalcLayout();

	m_Spliter.ShowWindow(SW_SHOW);
}

BOOL CWzdDlg_AutoTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	//XUI_InitAdjust();
	return TRUE;
}

void CWzdDlg_AutoTest::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	//具体移动
	XUI_AddWnd(&m_LineStatic, 0, 0, 1, 0);
	XUI_AddWnd(&m_DeviceInfoStatic, 0, 0, 1, 0);
	XUI_AddWnd(&m_ctrlLogListBox, 0, 1, 1, 0);
	XUI_AddWnd(&m_ctrlBtnCutsomWin, 0, 0, 1, 1);

	XUI_AddWnd(&m_TestStatic1, 1, 0, 0, 0);
	XUI_AddWnd(&m_TestStatic2, 1, 0, 0, 0);
	XUI_AddWnd(&m_CommStatic1, 1, 0, 0, 0);
	XUI_AddWnd(&m_CommStatic2, 1, 0, 0, 0);
	XUI_AddWnd(&m_OutputStatic1, 1, 0, 0, 0);
	XUI_AddWnd(&m_OutputStatic2, 1, 0, 0, 0);
	XUI_AddWnd(&m_TcpStatic1, 1, 0, 0, 0);
	XUI_AddWnd(&m_TcpStatic2, 1, 0, 0, 0);
	XUI_AddWnd(&m_ToothStatic1, 1, 0, 0, 0);
	XUI_AddWnd(&m_ToothStatic2, 1, 0, 0, 0);

	//XUI_AddWnd(m_pFrame, 0, 0, 1, 1);
	//XUI_AddWnd(&m_Spliter, 0, 0, 1, 1);
	XUI_AddWnd(&m_dlgTestStep, 0, 0, 1, 1);
	XUI_AddWnd(&m_dlgCheckItem, 0, 0, 1, 1);
	XUI_AddWnd(&m_dlgFailItem, 0, 0, 1, 1);
	XUI_AddWnd(&m_dlgCheckResult, 0, 0, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

int CWzdDlg_AutoTest::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWzdDlgBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pFrame = new CFrameWnd();
	m_pFrame->Create(NULL,"",WS_CHILD,CRect(0,0,1,1),this);
	m_pFrame->ShowWindow(SW_SHOW);
	m_pFrame->MoveWindow(0,0,300,350);
	m_pFrame->ModifyStyleEx(WS_EX_CLIENTEDGE,0,SWP_DRAWFRAME);

	m_Spliter.CreateStatic(m_pFrame,2,2,WS_CHILD | WS_VISIBLE);
	SetWindowLong(m_Spliter, GWL_EXSTYLE, GetWindowLong(m_Spliter, GWL_EXSTYLE) & ~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME));
	m_Spliter.setSplitterGap(10,10);
	m_Spliter.setBorder(0,0);

	return 0;
}

BOOL CWzdDlg_AutoTest::DoNext()
{

	return TRUE;
}


///////////////////////////////
void CWzdDlg_AutoTest::InitDeviceInfo()
{
	if(m_pGlobalDataList == NULL)
	{
		return;
	}
	CExBaseList lstDatas;
	//m_pGlobalDataList->SelectChildrenByClassIDEx(lstDatas,GBCLASSID_DATAOBJ);
	m_pGlobalDataList->SelectChildrenByClassID(lstDatas,DVMCLASSID_CDVMDATA);
	int nSize = lstDatas.GetCount();
	if(nSize <= 0)
	{
		lstDatas.RemoveAll();
		return;
	}

	CString strDeviceInfo = "装置信息        ";
	CDvmData* pbdzData = (CDvmData*)lstDatas.FindByID("bdz");
	strDeviceInfo += "变电站名称：";
	if(pbdzData)  strDeviceInfo += pbdzData->m_strValue;
	strDeviceInfo += "       ";

	CDvmData* psbmcData = (CDvmData*)lstDatas.FindByID("sbmc");
	strDeviceInfo += "间隔/主变名称：";
	if(psbmcData)  strDeviceInfo += psbmcData->m_strValue;
	strDeviceInfo += "       ";

	CDvmData* psbxhData = (CDvmData*)lstDatas.FindByID("sbxh");
	strDeviceInfo += "装置型号：";
	if(psbxhData)  strDeviceInfo += psbxhData->m_strValue;
	strDeviceInfo += "       ";

	CDvmData* piedinfoData = (CDvmData*)lstDatas.FindByID("iedinfo");
	strDeviceInfo += "保护套别：";
	if(piedinfoData) strDeviceInfo += piedinfoData->m_strValue;
	strDeviceInfo += "       ";

	CDvmData* pgzfzrData = (CDvmData*)lstDatas.FindByID("gzfzr");
	strDeviceInfo += "检验人：";
	if(pgzfzrData)  strDeviceInfo += pgzfzrData->m_strValue;
	strDeviceInfo += "       ";

	CDvmData* pjyrqData = (CDvmData*)lstDatas.FindByID("jyrq");
	strDeviceInfo += "检验日期：";
	if(pjyrqData)  strDeviceInfo += pjyrqData->m_strValue;

	m_DeviceInfoStatic.SetWindowText(strDeviceInfo);

	/////Test
	/*CString strTimeLog = "";
	CTime cTime; 
	cTime = CTime::GetCurrentTime();
	CString strTime = cTime.Format("%Y-%m-%d-%H-%M");
	strTimeLog += strTime;
	CLogPrint::LogString(XLOGLEVEL_WARNING,strTimeLog);*/
}

void CWzdDlg_AutoTest::initWholeState()
{
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/test/";

	CString strImg1 = strImg+ "green.ico";
	HICON IcImage1 = (HICON)LoadImage(NULL, strImg1, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	m_mapStateIcon[0] = IcImage1;

	CString strImg2 = strImg+ "gray.ico";
	HICON IcImage2 = (HICON)LoadImage(NULL,strImg2,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	m_mapStateIcon[1] = IcImage2;

	CString strImg3 = strImg+ "red.ico";
	HICON IcImage3 = (HICON)LoadImage(NULL,strImg3,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	m_mapStateIcon[2] = IcImage3;

	CString strImg4 = strImg+ "yellow.ico";
	HICON IcImage4 = (HICON)LoadImage(NULL,strImg4,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	m_mapStateIcon[3] = IcImage4;
	
	m_TestStatic1.SetIcon(IcImage4);
	m_CommStatic1.SetIcon(IcImage2);
	m_OutputStatic1.SetIcon(IcImage2);
	m_TcpStatic1.SetIcon(IcImage1);
	m_ToothStatic1.SetIcon(IcImage3);
}

void CWzdDlg_AutoTest::initButton()
{
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/test/";

	m_ctrlBtnStarTest.LoadImage(strImg+ "star.jpg",strImg+ "star_h.jpg",strImg+ "star_h.jpg",strImg+ "star_f.jpg");
	m_ctrlBtnStarTest.SetImgMode(TRUE);

	m_ctrlBtnStopTest.LoadImage(strImg+ "stop.jpg",strImg+ "stop_h.jpg",strImg+ "stop_h.jpg",strImg+ "stop_f.jpg");
	m_ctrlBtnStopTest.SetImgMode(TRUE);

	m_ctrlBtnFinishTest.LoadImage(strImg+ "finish.jpg",strImg+ "finish_h.jpg",strImg+ "finish_h.jpg",strImg+ "finish_f.jpg");
	m_ctrlBtnFinishTest.SetImgMode(TRUE);

	m_ctrlBtnSet.LoadImage(strImg+ "set.jpg",strImg+ "set_h.jpg",strImg+ "set_h.jpg",strImg+ "set_f.jpg");
	m_ctrlBtnSet.SetImgMode(TRUE);

	m_ctrlBtnBooth.LoadImage(strImg+ "booth.jpg",strImg+ "booth_h.jpg",strImg+ "booth_h.jpg",strImg+ "booth_f.jpg");
	m_ctrlBtnBooth.SetImgMode(TRUE);

	m_ctrlBtnPerConfirm.SetCheck(m_nPreTestItemState);
	m_ctrlBtnTestResultAuto.SetCheck(m_nTestResultState);
}

void CWzdDlg_AutoTest::EnableBtnBooth()
{
	if (m_nState_BlueTooth == NetState_BlueTooth)
	{
		//已经是蓝牙启用状态，则直接禁用按钮
		m_ctrlBtnBooth.EnableWindow(false);
		return;
	}

	if (m_nAutoTestState == AUTOTEST_NULL)//进入到当前页面，但是状态是初始态，表示创建测试或打开测试记录失败，没有收到TestCreated事件
	{
		m_ctrlBtnBooth.EnableWindow(false);
	}
	else if(m_nAutoTestState == AUTOTEST_CREATE)
	{
		m_ctrlBtnBooth.EnableWindow(true);
	}
	else if(m_nAutoTestState == AUTOTEST_STOP)
	{
		m_ctrlBtnBooth.EnableWindow(true);
	}
	else if(m_nAutoTestState == AUTOTEST_START)
	{
		m_ctrlBtnBooth.EnableWindow(false);
	}
	else if(m_nAutoTestState == AUTOTEST_FINISH)
	{
		m_ctrlBtnBooth.EnableWindow(true);
	}
	else if(m_nAutoTestState == AUTOTEST_CLOSE)
	{
		m_ctrlBtnBooth.EnableWindow(false);
	}
}

void CWzdDlg_AutoTest::UpdateText(CStatic *pStatic)
{
	pStatic->UpdateData(FALSE);
	CRect staticRect;
	pStatic->GetWindowRect(&staticRect);     //获取控件的坐标  
	//InvalidateRect(&staticRect); 
	//CRect rc;
	//GetWindowRect(rc);
	ScreenToClient(staticRect);
	InvalidateRect(staticRect,TRUE);
	//UpdateWindow();
}

void CWzdDlg_AutoTest::StarTimer()
{
	SetTimer(TimeEvent_State,1000,NULL);
	m_bIsStarTimer = true;
}

void CWzdDlg_AutoTest::EndTimer()
{
	KillTimer(TimeEvent_State);
	m_bIsStarTimer = false;
}

void CWzdDlg_AutoTest::ClearResult()
{
	m_dlgCheckResult.ClearResult();
}

void CWzdDlg_AutoTest::setDataInfo(CDvmDataset* pGlobalDatas,CDevice* pDeviceDatas)
{
	if(pGlobalDatas != NULL)
	{
		m_pGlobalDataList = pGlobalDatas;
	}

	if(pDeviceDatas != NULL)
	{
		pDeviceDatas->SelectChildrenByClassID(m_TestStepDataList,GBCLASSID_ITEMS);
		m_pDeviceDataList = pDeviceDatas;
	}


	InitDeviceInfo();
	m_dlgTestStep.InitCheckStepInfo(m_TestStepDataList);
	//默认设置选中指导书第一步， 测试项也显示第一步的子节点
	POS posHead  = m_TestStepDataList.GetHeadPosition();
	CItems *pStepItem = (CItems*)GetNext(posHead);

	m_dlgCheckItem.InitCheckItemInfo(pStepItem);
	m_dlgFailItem.InitFailItemInfo();
	m_dlgCheckResult.InitCheckResultInfo();
}

LRESULT CWzdDlg_AutoTest::OnItemStateChanged(WPARAM wP,LPARAM lP)
{
	CGbItemBase *pItem = NULL;
	pItem = reinterpret_cast<CItems*>((void*)wP);
	if(pItem == NULL)
	{
		return 0;
	}

	UINT nClassID = pItem->GetClassID();
	//1、CItems，父节点是CDevice为一级结点，父节点是CItems为二级结点
	//2、CMacroTest。如果是测试中，则置为“测试仪器输出中”。如果是其它状态，则置为“测试仪器停止输出”；
	//3、CCommCmd。如果是测试中，则置为“保护装置通讯中”。如果是其它状态，则置为“保护装置停止通讯”；
	CGbItemBase *pParent = NULL;
	long nState = pItem->GetState();

	if(nState == TEST_STATE_TESTING)
	{
		//记录当前测试的项目，检验项目人工确认时需要
		m_pCurTestItem = pItem;
	}
	else if (nState == TEST_STATE_ELIGIBLE
		|| nState == TEST_STATE_INLEGIBLE
		|| nState == TEST_STATE_ELIGIBLEEX)
	{
		//当前项目测试完成了，置空
		m_pCurTestItem = NULL;
	}

	switch (nClassID)
	{
	case GBCLASSID_ITEMS:
		pParent = (CGbItemBase*)pItem->GetParent();
		//更新作业指导书
		if(pParent->GetClassID() == GBCLASSID_DEVICE)
		{
			m_dlgTestStep.UpdateCheckStepState(pItem);
		}//更新 检查项目
		else if(pParent->GetClassID() == GBCLASSID_ITEMS)
		{
			m_dlgCheckItem.UpdateCheckItemState(pItem);
			if(nState == TEST_STATE_INLEGIBLE)
			{
				m_dlgFailItem.UpdateFailItemInfo(pItem);
			}
		}
		break;
	case GBCLASSID_COMMCMD:
		if(nState == TEST_STATE_TESTING)
		{
			//加载图标
			m_CommStatic1.SetIcon(m_mapStateIcon[0]);
			m_CommStatic2.SetWindowText(_T("保护装置通讯中"));
			SetCurrentLog(_T("保护装置通讯中"));
		}
		else
		{
			m_CommStatic1.SetIcon(m_mapStateIcon[1]);
			m_CommStatic2.SetWindowText(_T("保护装置停止通讯"));
			SetCurrentLog(_T("保护装置停止通讯"));
		}

		UpdateText(&m_CommStatic2);
		break;
	case GBCLASSID_MACROTEST:
		if(nState == TEST_STATE_TESTING)
		{
			//加载图标
			m_OutputStatic1.SetIcon(m_mapStateIcon[0]);
			m_OutputStatic2.SetWindowText(_T("测试仪器输出中"));
			SetCurrentLog(_T("测试仪器输出中"));
		}
		else
		{
			m_OutputStatic1.SetIcon(m_mapStateIcon[1]);
			m_OutputStatic2.SetWindowText(_T("测试仪器停止输出"));
			SetCurrentLog(_T("测试仪器停止输出"));
		}
		UpdateText(&m_OutputStatic2);
		break;
	default:
		break;
	}
	return 0;
}

void CWzdDlg_AutoTest::SetAutoTestState(int nState)
{
	m_nAutoTestState = nState;
	if (m_nAutoTestState == AUTOTEST_NULL)//进入到当前页面，但是状态是初始态，表示创建测试或打开测试记录失败，没有收到TestCreated事件
	{
		m_ctrlBtnStarTest.EnableWindow(false);
		m_ctrlBtnStopTest.EnableWindow(false);
		m_ctrlBtnFinishTest.EnableWindow(false);
		m_ctrlBtnSet.EnableWindow(false);
	}
	else if(m_nAutoTestState == AUTOTEST_CREATE)
	{
		m_ctrlBtnStarTest.EnableWindow(true);
		m_ctrlBtnStopTest.EnableWindow(false);
		m_ctrlBtnFinishTest.EnableWindow(true);
		m_ctrlBtnSet.EnableWindow(true);
		//m_ctrlBtnBooth.EnableWindow(true);
	}
	else if(m_nAutoTestState == AUTOTEST_STOP)
	{
		m_ctrlBtnStarTest.EnableWindow(true);
		m_ctrlBtnStopTest.EnableWindow(false);
		m_ctrlBtnFinishTest.EnableWindow(true);
		m_ctrlBtnSet.EnableWindow(true);
		//m_ctrlBtnBooth.EnableWindow(true);
	}
	else if(m_nAutoTestState == AUTOTEST_START)
	{
		m_ctrlBtnStarTest.EnableWindow(false);
		m_ctrlBtnStopTest.EnableWindow(true);
		m_ctrlBtnFinishTest.EnableWindow(false);
		m_ctrlBtnSet.EnableWindow(false);
	}
	else if(m_nAutoTestState == AUTOTEST_FINISH)
	{
		m_ctrlBtnStarTest.EnableWindow(true);
		m_ctrlBtnStopTest.EnableWindow(false);
		m_ctrlBtnFinishTest.EnableWindow(true);
		m_ctrlBtnSet.EnableWindow(true);
		//m_ctrlBtnBooth.EnableWindow(true);
	}
	else if(m_nAutoTestState == AUTOTEST_CLOSE)
	{
		m_ctrlBtnStarTest.EnableWindow(false);
		m_ctrlBtnStopTest.EnableWindow(false);
		m_ctrlBtnFinishTest.EnableWindow(false);
		m_ctrlBtnSet.EnableWindow(false);
	}

	EnableBtnBooth();
}

void CWzdDlg_AutoTest::SetCurrentLog(CString strText,int nFlag)
{
	CString strInfo = "";
	CTime tmValue = CTime::GetCurrentTime();
	strInfo = tmValue.Format(_T("%Y-%m-%d %H:%M:%S"));
	strInfo += "      ";
	strInfo += strText;

	long nCount = m_ctrlLogListBox.GetCount();
	if(nFlag == -1 || nFlag == Log_Type_NULL)
	{
		m_ctrlLogListBox.InsertString(nCount,strInfo,RGB(0,0,0));
	}
	else if(nFlag == Log_Type_Error)
	{
		m_ctrlLogListBox.InsertString(nCount,strInfo,RGB(255,0,0));
	}
	else if(nFlag == Log_Type_Other)
	{
		m_ctrlLogListBox.InsertString(nCount,strInfo,RGB(0,0,0));
	}
	
	m_ctrlLogListBox.SetTopIndex(nCount-1);
}

LRESULT CWzdDlg_AutoTest::OnSetNetState(WPARAM wP,LPARAM lP)
{
	int nState = -1;
	nState = (int)wP;
	m_nState_BlueTooth = nState;

	switch (nState)
	{
	case NetState_BlueTooth:
		//TUDO：蓝牙已启用，以太网已禁用
		m_ToothStatic1.SetIcon(m_mapStateIcon[0]);
		m_ToothStatic2.SetWindowText(_T("蓝牙已启用"));

		m_TcpStatic1.SetIcon(m_mapStateIcon[2]);
		m_TcpStatic2.SetWindowText(_T("以太网已禁用"));
		SetCurrentLog(_T("蓝牙已启用,以太网已禁用"));
		//m_ctrlBtnBooth.EnableWindow(false);
		break;
	case NetState_Ethernet:
		//TUDO：蓝牙已禁用，以太网已启用
		m_ToothStatic1.SetIcon(m_mapStateIcon[2]);
		m_ToothStatic2.SetWindowText(_T("蓝牙已禁用"));

		m_TcpStatic1.SetIcon(m_mapStateIcon[0]);
		m_TcpStatic2.SetWindowText(_T("以太网已启用"));
		SetCurrentLog(_T("蓝牙已禁用,以太网已启用"));
		//m_ctrlBtnBooth.EnableWindow(true);
		break;
	}

	EnableBtnBooth(); //更新蓝牙按钮的状态
	UpdateText(&m_ToothStatic2);
	UpdateText(&m_TcpStatic2);
	return 0;
}

LRESULT CWzdDlg_AutoTest::OnInputData(WPARAM wP,LPARAM lP)
{
	CExBaseList *pSttParas = (CExBaseList *)wP;
	CExBaseList *pSttMsgs = (CExBaseList *)lP;

	//dlg对象的内存释放已经写在了dlg的onok中,外部不再需要管理此内存指针
	m_pInputDlg = new InputDataDlg;
	BOOL bRet = m_pInputDlg->Create(InputDataDlg::IDD, GetDesktopWindow());
	m_pInputDlg->InitDlg(pSttParas, pSttMsgs, m_pCurTestItem);
	m_pInputDlg->ShowWindow(SW_SHOW);

	CRect rc, rcDlg;
	GetClientRect(rc);
	m_pInputDlg->GetWindowRect(rcDlg);
	ScreenToClient(rcDlg);

	long nX = rc.Width() / 2;
	long nY = rc.Height() / 2;
	nX = nX - rcDlg.Width() / 2;
	nY = nY - rcDlg.Height() / 2;
	::SetWindowPos(m_pInputDlg->m_hWnd, HWND_TOPMOST, nX, nY, 0, 0, SWP_NOSIZE);

	return 0;
}

LRESULT CWzdDlg_AutoTest::OnTestFinished(WPARAM wP,LPARAM lP)
{
	//测试完成，修改测试状态。开始测试按钮，结束测试按钮，配置测试参数按钮都enable为true
	SetAutoTestState(AUTOTEST_FINISH);
	m_TestStatic1.SetIcon(m_mapStateIcon[1]);
	m_TestStatic2.SetWindowText(_T("检验项目结束测试"));
	UpdateText(&m_TestStatic2);
	SetCurrentLog("检验项目结束测试");
	if(m_bIsStarTimer)
	{
		EndTimer();
	}
	return 0;
}

LRESULT CWzdDlg_AutoTest::OnTestStoped(WPARAM wP,LPARAM lP)
{
	//测试停止，修改测试状态。开始测试按钮，结束测试按钮，配置测试参数按钮都enable为true
	SetAutoTestState(AUTOTEST_STOP);
	m_TestStatic1.SetIcon(m_mapStateIcon[2]);
	m_TestStatic2.SetWindowText(_T("检验项目停止测试"));
	UpdateText(&m_TestStatic2);
	SetCurrentLog(_T("检验项目停止测试"));
	if(m_bIsStarTimer)
	{
		EndTimer();
	}
	return 0;
}

void CWzdDlg_AutoTest::OnTestAppEvent(const CString& strEvent)
{
	//测试仪事件，暂缓处理
}

void CWzdDlg_AutoTest::OnEngineEvent(const CString& strEvent)
{
	//保护装置事件，暂缓处理
}

LRESULT CWzdDlg_AutoTest::OnTestCreated(WPARAM wP,LPARAM lP)
{
	//测试创建成功。修改测试状态。开始测试按钮，结束测试按钮，配置测试参数按钮都enable为true
	SetAutoTestState(AUTOTEST_CREATE);
	SetCurrentLog(_T("创建自动测试"));
	return 0;
}

void CWzdDlg_AutoTest::OnOpenGbrptFileFailed()
{
	//测试记录打开失败，暂缓处理
}

void CWzdDlg_AutoTest::OnTestProcess(CExBaseList* pSttParas)
{
	//测试进度事件，暂缓处理
}

void CWzdDlg_AutoTest::OnReTestFinished(CExBaseList* pSttParas)
{
	//重测结束，暂缓处理
}

void CWzdDlg_AutoTest::ClearInputDlg()
{
	//destroy和delete已经在dlg中执行了,此处只需要置空
	m_pInputDlg = NULL;
}

LRESULT CWzdDlg_AutoTest::OnTestStarted(WPARAM wP,LPARAM lP)
{
	//测试开始。修改测试状态。停止测试按钮enable为true。开始测试、结束测试、测试参数编辑按钮enable为false
	SetAutoTestState(AUTOTEST_START);
	m_TestStatic1.SetIcon(m_mapStateIcon[0]);
	m_TestStatic2.SetWindowText(_T("检验项目开始测试"));
	UpdateText(&m_TestStatic2);
	SetCurrentLog(_T("检验项目开始测试"));
	if(!m_bIsStarTimer)
	{
		StarTimer();
	}
	return 0;
}

// void CWzdDlg_AutoTest::OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs)
// {
// 	//提示人工确认信息弹窗，启动定时器等
// 	if(m_pInputDlg)
// 	{
// 		delete m_pInputDlg;
// 		m_pInputDlg = NULL;
// 	}
// 
// 	m_pInputDlg = new InputDataDlg;
// 	m_pInputDlg->Create(InputDataDlg::IDD, this);
// 	m_pInputDlg->InitDlg(pSttParas, pSttMsgs, m_pCurTestItem);
// 	m_pInputDlg->ShowWindow(SW_SHOW);
// 
// 	CRect rc;
// 	m_pInputDlg->GetWindowRect(rc);
// 	ScreenToClient(rc);
// 	::SetWindowPos(m_pInputDlg->m_hWnd, HWND_TOPMOST, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOSIZE);
// }

//报告接口，处理报告数据显示
LRESULT CWzdDlg_AutoTest::OnReport(WPARAM wP,LPARAM lP)
{
	CGbItemBase *pItem = NULL;
	pItem = reinterpret_cast<CItems*>((void*)wP);
	if(pItem == NULL)
	{
		return 0;
	}

	UINT nClassID = pItem->GetClassID();
	if(nClassID != GBCLASSID_SAFETY)
	{
		return 0;
	}

	if (pItem->m_strID != ID_CONSTANT_ITEM_RPTVIEW)
	{
		return 0;
	}

	//不自动更新 不刷新结果
	if(m_nTestResultState == Auto_TestResult_N)
	{
		return 0;
	}
	CReports *pReports = NULL;
	pReports = pItem->GetReports();
	if(pReports == NULL)
	{
		return 0;
	}

	m_dlgCheckResult.SetCheckResultInfo(pReports);
	return 0;
	
}
////////////////////////
void CWzdDlg_AutoTest::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);

	if(GetDlgItem(IDC_CUTSOM_WINDOW)->GetSafeHwnd() == NULL || m_pFrame == NULL)
	{
		return;
	}
	
	CRect cRect;
	GetDlgItem(IDC_CUTSOM_WINDOW)->GetWindowRect(&cRect);
	ScreenToClient(&cRect);

	m_pFrame->MoveWindow(&cRect);
	m_Spliter.MoveWindow(0,0,cRect.Width(),cRect.Height());

	m_Spliter.SetRowInfo(0,cRect.Height()/2, 200);
	m_Spliter.SetRowInfo(1,cRect.Height()/2, 200);
	m_Spliter.SetColumnInfo(0,cRect.Width()/2, 300);
	m_Spliter.SetColumnInfo(1,cRect.Width()/2, 300 );
	m_Spliter.RecalcLayout();
}

void CWzdDlg_AutoTest::OnBnClickedStarButton()
{
	// TODO: 在此添加控件通知处理程序代码
	g_pWzdMainDlg->TestClientStartTest();
	/*if(!m_bIsStarTimer)
	{
		StarTimer();
	}
	*/
}

void CWzdDlg_AutoTest::OnBnClickedStopButton()
{
	// TODO: 在此添加控件通知处理程序代码
	g_pWzdMainDlg->TestClientStopTest();
	/*if(m_bIsStarTimer)
	{
		EndTimer();
	}*/
}

void CWzdDlg_AutoTest::OnBnClickedFinishButton()
{
	// TODO: 在此添加控件通知处理程序代码
	g_pWzdMainDlg->CloseTestClient();
	/*if(m_bIsStarTimer)
	{
		EndTimer();
	}*/
}

//系统参数配置
void CWzdDlg_AutoTest::OnBnClickedSetButton()
{
	//先弹窗
	CWzd_ConfigSetDlg dlgConfigSet;
	CDevice *pDevice = g_pWzdMainDlg->m_oGuideBook.GetDevice();
	CSysParas *pSysParas = pDevice->m_pSysParas;   //需要在弹窗中显示的参数列表，每一个参数是一个CDataObj对象；
	dlgConfigSet.SetGridData(pSysParas);
	if(dlgConfigSet.DoModal() == IDOK)
	{
		CString strTestParas = dlgConfigSet.GetTestParas();
		//发送指令
		g_pWzdMainDlg->SetTestParas(_T(""), strTestParas);
	}
}

void CWzdDlg_AutoTest::OnBnClickedBoothButton()
{
	// TODO: 在此添加控件通知处理程序代码

	//m_ToothStatic1.SetIcon(m_mapStateIcon[0]);
	//m_ToothStatic2.SetWindowText(_T(""));
	//UpdateText(&m_ToothStatic1);

	CString strTitle, strText;
	strText = _T("根据网安要求，将开启蓝牙服务，请确保已拔出网线");
	strTitle = _T("警告");
	long nRet = ::MessageBox(NULL, strText,  strTitle, MB_OKCANCEL | MB_ICONQUESTION);
	if (nRet == IDCANCEL)
	{
		return;
	}

	//禁用网卡
	g_pISmartTestWzdDlg->SetNetCardState(FALSE);

	g_pISmartTestWzdDlg->SetWzdMode(Wzd_Mode_BlueToothTask);
	g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_Bluetooth);
	g_pISmartTestWzdDlg->InitBluetooth();

}

void CWzdDlg_AutoTest::OnBnClickedPeoAutoConfirmCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nPreTestItemState = m_ctrlBtnPerConfirm.GetCheck();
	if(m_nPreTestItemState == Pre_TestItem_Confirm_N)
	{
		//TUDO：若InputDataDlg对话框已经弹出，需要关闭计时器
		if(m_pInputDlg)
		{
			m_pInputDlg->KillTimer();
		}
	}
	else if(m_nPreTestItemState == Pre_TestItem_Confirm_Y)
	{
		//TUDO：若InputDataDlg对话框已经弹出，需要启动计时器
		if(m_pInputDlg)
		{
			m_pInputDlg->StartTimer();
		}
	}
}

void CWzdDlg_AutoTest::OnBnClickedTestItemAutoCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nTestResultState = m_ctrlBtnTestResultAuto.GetCheck();
}

LRESULT CWzdDlg_AutoTest::OnTestStepChange(WPARAM wP,LPARAM lP)
{
	CItems* pStep = NULL;
	pStep = reinterpret_cast<CItems*>((void*)wP);
	if(pStep == NULL)
	{
		return 0;
	}
	m_dlgCheckItem.UpdateCheckItemInfo(pStep);
	return 0;
}

LRESULT CWzdDlg_AutoTest::OnFindFailItem(WPARAM wP,LPARAM lP)
{
	CItems* pStep = NULL;
	CItems*pTestItem = NULL;
	pStep = reinterpret_cast<CItems*>((void*)wP);
	pTestItem = reinterpret_cast<CItems*>((void*)lP);
	if(pStep == NULL || pTestItem == NULL)
	{
		return 0;
	}
	m_dlgCheckItem.UpdateCheckItemInfo(pStep);
	//更新 检查项目的选中项  TODO
	m_dlgCheckItem.SetSelectRow(pTestItem);
	return 0;
}

HBRUSH CWzdDlg_AutoTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWzdDlgBase::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何属性
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
		HBRUSH aBrush;
		aBrush = CreateSolidBrush(RGB(255, 255, 255));
		hbr = aBrush;
		break;
	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT);   
		pDC->SetTextColor(RGB(0,0,0));   
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CWzdDlg_AutoTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGbItemBase* pStepItems = NULL;
	if(nIDEvent == TimeEvent_State)
	{
		pStepItems = m_dlgTestStep.UpdateCheckStepState2();
		if(pStepItems)
		{
			m_dlgCheckItem.UpdateCheckItemInfo((CItems*)pStepItems);
		}
		m_dlgCheckItem.UpdateCheckItemState2();	
	}

	CWzdDlgBase::OnTimer(nIDEvent);
}

void CWzdDlg_AutoTest::OnLogDelete()
{
	int nSelItem = m_ctrlLogListBox.GetCurSel();
	int nCount = m_ctrlLogListBox.GetCount();
	if(nSelItem < 0 || nSelItem >= nCount)
	{
		return;
	}
	m_ctrlLogListBox.DeleteString(nSelItem);
}

void CWzdDlg_AutoTest::OnLogClear()
{
	int nCount = m_ctrlLogListBox.GetCount();
	for(int i = nCount;i >= 0 ;i--)
	{
		m_ctrlLogListBox.DeleteString(i);
	}
	
}