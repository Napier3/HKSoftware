#include "PpSttIotEngineClientWidgetMain.h"

#include <QMessageBox>

#include "../../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../../Module/API/GlobalConfigApi.h"

extern CPpSttIotEngineClientApp *g_theIotEngineApp;

class CPpSttIotDeviceClientMain : public CPpSttIotDeviceClient
{
public:
    CPpSttIotDeviceClientMain()
    {
    }
    virtual ~CPpSttIotDeviceClientMain()
    {
        m_oEngineMsgWnd.DestroyWindow();
    }

public:
    QPpSttIotEngineClientWidgetWnd m_oEngineMsgWnd;

};

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineClientWidgetMain
QPpSttIotEngineClientWidgetMain::QPpSttIotEngineClientWidgetMain(QWidget *parent) :
    QPpSttIotEngineClientWidget(parent)
{
    this->setWindowFlags(Qt::Dialog);
	m_pPpSttIotEngineClientInterface = NULL;
    connect(this, SIGNAL(sig_NewDevice()), this, SLOT(slot_NewDevice()), Qt::QueuedConnection);
	//connect(&m_oInitCmdTimer,SIGNAL(timeout()),this,SLOT(slot_InitCmdTimer()));
}

QPpSttIotEngineClientWidgetMain::~QPpSttIotEngineClientWidgetMain()
{

}

void QPpSttIotEngineClientWidgetMain::slot_NewDevice()
{
#ifdef _SttIotEngineClientWidgetMain_
    PopNewDeviceDlg();
#endif
}

void QPpSttIotEngineClientWidgetMain::NewPpSttIotDeviceClient(CPpSttCommConfig *pCommConfig, CDvmDevice *pDvmDevice)
{
	QPpSttIotEngineClientWidget::NewPpSttIotDeviceClient(pCommConfig, pDvmDevice);
	CPpSttIotDeviceClientMain *pNewDevice = NULL;

	//2023-1-28  lijunqing 只考虑单装置模式 如果装置没有创建，则创建
	if (m_pPpDeviceClient == NULL)
	{
		pNewDevice = new CPpSttIotDeviceClientMain();
		g_theIotEngineApp->CreateDevice(pNewDevice, (PSX_OBJ_ADDR)&pNewDevice->m_oEngineMsgWnd);
		pNewDevice->m_oEngineMsgWnd.m_pMainWidget = this;
		pNewDevice->m_oEngineMsgWnd.m_pIotDevice = pNewDevice;
		m_pPpDeviceClient = pNewDevice;
	}
	else
	{
		pNewDevice = (CPpSttIotDeviceClientMain *)m_pPpDeviceClient;
	}

	m_pPpDeviceClient->InitDvmDevice(pDvmDevice);
	//每次新建测试，都重新连接装置  2023-12-27   因为装置可能重新换过了
	m_pPpDeviceClient->m_pPpDevice->m_bIsSvrDeviceConnectSucc = FALSE;  
	pNewDevice->m_strDeviceID = pCommConfig->Get_DeviceSN();
	pNewDevice->InitCommConfig(pCommConfig);

	if (pNewDevice->IsConnectSuccessful())
	{
		return;
	}

	pNewDevice->ConnectDevice();
	//zhouhj 2024.3.14 如果是传统规约平台,连接成功后,主动调用初始化命令
//	if (pNewDevice->ConnectDevice()&&(m_pPpDeviceClient->m_oCommConfig.Is_PpEngine()))
//	{
//		//m_oInitCmdTimer.start(2000);
//	}
}

void QPpSttIotEngineClientWidgetMain::slot_InitCmdTimer()
{
	//m_oInitCmdTimer.stop();
	Initialize_Cmd();
}

void QPpSttIotEngineClientWidgetMain::OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam)
{
	QPpSttIotEngineClientWidget::OnCommCommandMsg(pIotDevice, wParam, lParam);

	if (m_pPpSttIotEngineClientInterface != NULL)
	{
		m_pPpSttIotEngineClientInterface->OnCommCommandMsg(wParam,lParam);
	}
}

void QPpSttIotEngineClientWidgetMain::OnEngineSystemMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam)
{
	QPpSttIotEngineClientWidget::OnEngineSystemMessage(pIotDevice, wParam, lParam);

	if (m_pPpSttIotEngineClientInterface != NULL)
	{
		m_pPpSttIotEngineClientInterface->OnEngineSystemMessage(wParam,lParam);
	}
}

void QPpSttIotEngineClientWidgetMain::UpdateTitleAndSize(const CString &strTitle,long nWidth,long nHeight)
{
	setWindowTitle(strTitle);
	resize(nWidth,nHeight);
}


QPpSttIotEngineClientWidgetMain *g_theEngineClientWidgetMain= NULL;

QPpSttIotEngineClientWidgetMain* CreateEngineClientWidgetMain()
{
    if (g_theEngineClientWidgetMain != NULL)
    {
        return g_theEngineClientWidgetMain;
    }

    g_theEngineClientWidgetMain = new QPpSttIotEngineClientWidgetMain();
    g_theEngineClientWidgetMain->show();
    g_theEngineClientWidgetMain->emit_sig_NewDevice();
    return g_theEngineClientWidgetMain;
}

void ReleaseEngineClientWidgetMain()
{
    if (g_theEngineClientWidgetMain == NULL)
    {
        return;
    }

    delete g_theEngineClientWidgetMain;
    g_theEngineClientWidgetMain = NULL;
}
