// D:\WorkAts\Source\AutoTest\Module\WzdDlgApi\StepDlg\WzdBluetoothDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "../../../iSmartTestWzd/iSmartTestWzdDlg.h"
#include "../../../AutoTest/Module/XSttAtsTestClientImp.h"
#include "WzdBluetoothDlg.h"
#include "MessageDlg.h"


// CWzdBluetoothDlg 对话框

IMPLEMENT_DYNAMIC(CWzdBluetoothDlg, CDialog)

CWzdBluetoothDlg::CWzdBluetoothDlg(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzdBluetoothDlg::IDD, pParent)
{
	m_Font = NULL;
	m_bRecvTask = false;
}

CWzdBluetoothDlg::~CWzdBluetoothDlg()
{
	m_BlueDataPross.CloseBlueToothServer();	
	if(m_Font != NULL)
	{
		delete m_Font;
		m_Font = NULL;
	}
}

void CWzdBluetoothDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_txtTitle);
	DDX_Control(pDX, IDC_ICON_MAIN, m_btnIcon);
	DDX_Control(pDX, IDC_MAIN_BOTTOM, m_btnBottom);	

	DDX_Control(pDX, IDC_STATIC_WORD1, m_sWORD1);
	DDX_Control(pDX, IDC_STATIC_WORD2, m_sWORD2);
	DDX_Control(pDX, IDC_STATIC_PIC, m_sPIC);
	DDX_Control(pDX, IDC_STATIC_LINKSTATE, m_sLinkState);

	DDX_Control(pDX, IDD_DATA_SHOW, m_DataShow);

	DDX_Control(pDX, IDC_BTN_PREV, m_btnReturn);
	DDX_Control(pDX, IDC_BTN_RECV, m_btnRecv);
}


BEGIN_MESSAGE_MAP(CWzdBluetoothDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PREV, &CWzdBluetoothDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_RECV, &CWzdBluetoothDlg::OnBnClickedBtnRecv)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_RECV_RPT_DATA, &CWzdBluetoothDlg::OnShowRecv0x92Data)
	ON_MESSAGE(WM_RECV_RPT_CLOSE, &CWzdBluetoothDlg::OnShowRecv0x94Data)
	ON_MESSAGE(WM_START_SEND, &CWzdBluetoothDlg::OnStartSendFileData)
	ON_MESSAGE(WM_END_SEND, &CWzdBluetoothDlg::OnEndSendFileData)
	ON_MESSAGE(WM_STOP_SEND, &CWzdBluetoothDlg::OnStopSendFileData)
	ON_MESSAGE(WM_RECORD_SEND, &CWzdBluetoothDlg::OnRecordSendFileData)
END_MESSAGE_MAP()

// CWzdBluetoothDlg 消息处理程序
void CWzdBluetoothDlg::OnInitialUpdate()
{
	m_BlueDataPross.SetParentWnd(this);

    m_Font = new CFont;
    m_Font->CreateFont(35,18,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,"Arial");
    m_sWORD2.SetFont(m_Font);
	m_sLinkState.SetFont(m_Font);

	XUI_InitAdjust();
	InitBtns();

	m_DataShow.InitGrid();

	m_DlgSendS.Create(CWzdDlgSendState::IDD, NULL);
}

void CWzdBluetoothDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
 	XUI_AddWnd(&m_txtTitle, 0, 0, 1, 0);
 	XUI_AddWnd(&m_btnIcon, 0, 0, 0, 0);
	XUI_AddWnd(&m_btnBottom, 0, 1, 1, 0);

	XUI_AddWnd(&m_sWORD1, 0, 0, 1, 0);
	XUI_AddWnd(&m_sWORD2, 0, 0, 0, 0);

	XUI_AddWnd(&m_sPIC, 1, 0, 0, 0);
	XUI_AddWnd(&m_sLinkState, 1, 0, 0, 0);
	
	XUI_AddWnd(&m_DataShow, 0, 0, 1, 1);

 	XUI_AddWnd(&m_btnReturn, 0.5, 1, 0.1, 0);
 	XUI_AddWnd(&m_btnRecv, 0.5, 1, 0.1, 0);

	CXUIAdjItem_Area::XUI_OnSize();
}
void CWzdBluetoothDlg::InitBtns()
{
	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
 	m_btnIcon.LoadImage(strIcon + "title.jpg", strIcon + "title.jpg", strIcon + "title.jpg", strIcon + "title.jpg");
 	m_btnIcon.SetImgMode(TRUE);

	m_txtTitle.LoadImage(strIcon + "title2.png", strIcon + "title2.png", strIcon + "title2.png", strIcon + "title2.png");
	m_txtTitle.SetImgMode(TRUE);

	m_btnBottom.LoadImage(strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png");
	m_btnBottom.SetImgMode(TRUE);

	strIcon += "blooth.png";
	m_sPIC.LoadImage(strIcon, strIcon, strIcon, strIcon);
	m_sPIC.SetImgMode(TRUE);
}
void CWzdBluetoothDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdBluetoothDlg::InitBluetooth()
{
	//打开蓝牙接口
	KillTimer(SHOWSTATE_TIMER_ID);
	SetTimer(SHOWSTATE_TIMER_ID, 500, NULL);

	if(m_BlueDataPross.m_nBTState == BT_STATE_IDLE)
	{
		m_BlueDataPross.OpenBlueToothServer();		
	}
}

void CWzdBluetoothDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case SHOWSTATE_TIMER_ID:
		if(m_BlueDataPross.m_nBTState == BT_STATE_IDLE)
			m_sLinkState.SetWindowText(_T("空闲"));
		else if(m_BlueDataPross.m_nBTState == BT_STATE_ACCEPTING)
			m_sLinkState.SetWindowText(_T("等待连接"));
		else if(m_BlueDataPross.m_nBTState == BT_STATE_CONNECTING)
			m_sLinkState.SetWindowText(_T("正在连接"));
		else if(m_BlueDataPross.m_nBTState == BT_STATE_CONNECTED)
			m_sLinkState.SetWindowText(_T("已连接"));
		else if(m_BlueDataPross.m_nBTState == BT_STATE_CLOSE)
			m_sLinkState.SetWindowText(_T("已关闭"));
		break;
	}

	__super::OnTimer(nIDEvent);
}

void CWzdBluetoothDlg::OnBnClickedBtnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_BlueDataPross.Answer0x93Data(false);
	g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_EntrySel);	

	m_DataShow.DeleteAllItems();	//清空任务
	m_bRecvTask = false;
}

void CWzdBluetoothDlg::OnBnClickedBtnRecv()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bRecvTask)
	{
		MessageDlg::MessageBox("提示", "尚未收到任务", MessageDlg::YES);
		return ;
	}
	m_BlueDataPross.m_iCheckOver = CHECK_STATE_ING;	//设置为开始检测状态
	m_BlueDataPross.Answer0x93Data(true);
	g_pISmartTestWzdDlg->SetActiveDlg(DLG_STEP_Main);
	g_pISmartTestWzdDlg->InitMainCfg(false);		
}

LRESULT CWzdBluetoothDlg::OnShowRecv0x92Data(WPARAM wPara,LPARAM lPara)//子界面中保存修改按键对应的消息处理函数
{
	//将COrderInfo0x92 转换为CDataGroup
	CDvmDataset *dataG = m_BlueDataPross.m_OrderInfo.CreateDataGroup();

	//存入全局变量中
	g_pISmartTestWzdDlg->SetDataInGlobal(dataG);	

	dataG->DeleteAll();
	delete dataG;

	//显示数据到界面
	m_DataShow.ShowData(&m_BlueDataPross.m_OrderInfo);
	m_bRecvTask = true;
	return 0;
}
LRESULT CWzdBluetoothDlg::OnShowRecv0x94Data(WPARAM wPara,LPARAM lPara)//子界面中保存修改按键对应的消息处理函数
{
	g_pISmartTestWzdDlg->CloseTestClient();
	return 0;
}
LRESULT CWzdBluetoothDlg::OnStartSendFileData(WPARAM wPara,LPARAM lPara)//弹出发送提示界面
{
	int iMaxRange = (int)lPara;
	m_DlgSendS.SetTitle(_T("文件发送"));
	m_DlgSendS.SetMaxRange(iMaxRange);
	return 0;
}
LRESULT CWzdBluetoothDlg::OnRecordSendFileData(WPARAM wPara,LPARAM lPara)
{
	m_DlgSendS.StepIt();
	return 0;
}
LRESULT CWzdBluetoothDlg::OnEndSendFileData(WPARAM wPara,LPARAM lPara)//关闭发送提示界面
{
	m_DlgSendS.Finish();
	return 0;
}
LRESULT CWzdBluetoothDlg::OnStopSendFileData(WPARAM wPara,LPARAM lPara)//关闭发送提示界面
{
	m_DlgSendS.Finish();
	return 0;
}

void CWzdBluetoothDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(SHOWSTATE_TIMER_ID);
	__super::OnClose();
}

void CWzdBluetoothDlg::SetCheckOver(int iState)
{
	m_BlueDataPross.m_iCheckOver = iState;
	//检测完成还需等待人工确认，然后移动端再发送94或98指令，完成导出后自动回复数据
	if(iState == CHECK_STATE_OVER)		
	{
		m_BlueDataPross.ProssRecvFileOrder();
	}
}

//启动、停止蓝牙服务
void CWzdBluetoothDlg::OpenBlueToothServer()
{
	if(m_BlueDataPross.m_nBTState == BT_STATE_IDLE)
	{
		m_BlueDataPross.OpenBlueToothServer();		
	}
}

void CWzdBluetoothDlg::CloseBlueToothServer()
{
	m_BlueDataPross.CloseBlueToothServer();		
}