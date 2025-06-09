#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "QOutPutDebugDlg.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../../XLangResource_Native.h"


QOutPutDebug::QOutPutDebug(QWidget* parent) :QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_bHasClosed = FALSE;
	m_IsConnected = FALSE;
	m_pUIParaSet = NULL;
	m_pParaSetSttTestResource = NULL;
	m_pAllVLayout = NULL;
	m_pGrideLayout = NULL;
	m_pButtonLayout = NULL;
	m_ptnStartOutPut = NULL;
	m_ptnStopOutput = NULL;
	m_pbtnClose = NULL;
	m_nTimerID = 0;

	InitUI();
	InitConnection();

	m_IsConnected = OnConnectTestApp();
	 m_nTimerID = startTimer(Time_HeartbeatTimeGap); //定时器启动
	
}

QOutPutDebug::~QOutPutDebug()
{
	if(m_pParaSetSttTestResource != NULL)
	{
   delete m_pParaSetSttTestResource;
	}

	if(m_pUIParaSet != NULL)
	{
   delete m_pUIParaSet;
}
}

void QOutPutDebug::InitUI()
{
	
	m_pAllVLayout = new QVBoxLayout(this);
	m_pGrideLayout = new QHBoxLayout(this);
	m_pButtonLayout = new QHBoxLayout(this);
	m_ptnStartOutPut = new QPushButton(this);
	m_ptnStopOutput = new QPushButton(this);
	m_pbtnClose = new QPushButton(this);
	m_pUIParaSet = new QBasicTestParaSet();

    InitUIGrid();

    CString strTitle;
    this->resize(900, 400);
    // this->setFixedWidth(900);
    // this->setFixedHeight(400);
    strTitle = /* _T("输出调试") */ g_sLangTxt_Native_DebugOutput;
	this->setWindowTitle(strTitle);
    CString strbutton1 = /* _T("开始输出") */ g_sLangTxt_Native_StartOutput;
    m_ptnStartOutPut->setText(strbutton1);
    m_ptnStartOutPut->adjustSize();
    CString strbutton2 = /* _T("停止输出") */ g_sLangTxt_Native_StopOutput;
    m_ptnStopOutput->setText(strbutton2);
	m_ptnStopOutput->adjustSize();
	m_ptnStopOutput->setEnabled(false);
    CString strbutton3 = /* _T("关闭") */ g_sLangTxt_Close;
    m_pbtnClose->setText(strbutton3);
	m_pbtnClose->adjustSize();

    m_pGrideLayout->addWidget(m_pUIParaSet);
    m_pButtonLayout->addWidget(m_ptnStartOutPut);
	m_pButtonLayout->addWidget(m_ptnStopOutput);
    m_pButtonLayout->addStretch(1);
	m_pButtonLayout->addWidget(m_pbtnClose);
	m_pAllVLayout->addLayout(m_pGrideLayout);
	m_pAllVLayout->addLayout(m_pButtonLayout);
    this->setLayout(m_pAllVLayout);
}

void QOutPutDebug::InitConnection()
{
	connect(m_pbtnClose,SIGNAL(clicked()), this, SLOT(slot_CloseClicked()));
	connect(m_ptnStartOutPut,SIGNAL(clicked()), this, SLOT(slot_StartOutput()));
	connect(m_ptnStopOutput,SIGNAL(clicked()), this, SLOT(slot_StopOutput()));
    connect(m_pUIParaSet,SIGNAL(sig_updataParas()),this,SLOT(slot_Paraschanged()));  
}

void QOutPutDebug::InitUIGrid()
{ 
if(m_pParaSetSttTestResource == NULL)
{
    m_pParaSetSttTestResource = new CSttTestResource_Sync();
}

	CSttChMaps oChMaps;

	if (g_oSttTestResourceMngr.OpenChMapsFile(&oChMaps,m_pParaSetSttTestResource))
	{
		m_pParaSetSttTestResource->CreateSoftResourceByChMaps(&oChMaps);
	}
	else
	{
		m_pParaSetSttTestResource->CreateSoftResource(); //软件资源初始化
	}

	CString StrParaFile = _P_GetDBPath();
	StrParaFile.append("atsgen/Manual_Paras.xml");
	CDataGroup oDataGroup;
	BOOL nbet = oDataGroup.OpenXmlFile(StrParaFile,CDataMngrXmlRWKeys::g_pXmlKeys);

	if(oDataGroup.GetCount() == 0)
	{
        return;
	}
	if(!nbet)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/* _T("打开文件(%s)失败.") */ g_sLangTxt_Native_OpenFail.GetString(),StrParaFile.GetString());
		return;
	}

     m_pUIParaSet->initUI(m_pParaSetSttTestResource);
	 CSttDataGroupSerializeRead oRead(&oDataGroup);
	 stt_xml_serialize(&m_oManualTest.m_oManuParas,
		 &oRead,m_pParaSetSttTestResource->GetVolRsNum(),m_pParaSetSttTestResource->GetVCurRsNum());//序列化数据
     m_pUIParaSet->setPropertyOfParaSet(P_Common, m_pParaSetSttTestResource,
		m_oManualTest.m_oManuParas.m_uiVOL, m_oManualTest.m_oManuParas.m_uiCUR, false); //初始化数据

}
BOOL QOutPutDebug::OnConnectTestApp()
{
	g_oSttTestAppCfg.SttOpen(g_oSttTestAppCfg.GetOldCfgFile());//zhouhj 20211005 修改IP地址后,重新读取IP地址等信息
	CString strIP = g_oSttTestAppCfg.GetTestAppIP();
	long nPort = g_oSttTestAppCfg.GetTestServerPort();
	return OnConnectTestApp(strIP,nPort);
}

BOOL QOutPutDebug::OnConnectTestApp(const CString &strIP, long nPort)
{
	if(!IsTestAppExist(strIP))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/* _T("与当前测试仪建立连接失败(%s).") */ g_sLangTxt_Native_ConnectFail.GetString(),strIP.GetString());
		return FALSE;
	}
	else
	{
		return connectTestApp(strIP,nPort,STT_SOFT_ID_TEST);
	}
}

BOOL QOutPutDebug::IsTestAppExist(const CString &strIP)
{
	char pszIP[20];
	CString_to_char(strIP,pszIP);
	return xping(pszIP);
}

void QOutPutDebug::slot_CloseClicked()
{
	killTimer(m_nTimerID);
    DisConnectCmd();
	FreeXClientEngine();
	m_bHasClosed = TRUE;
	close();
}
void QOutPutDebug::slot_StartOutput()
{
  	if(!m_IsConnected)
  	{
		if (!OnConnectTestApp())
		{
            CLogPrint::LogString(XLOGLEVEL_ERROR,/* "与测试仪断开连接，请检查网络链路是否连通，IP地址及端口配置是否正确；重新连接" */g_sLangTxt_Native_Disconnect.GetString());
			return;
		}

		m_IsConnected = TRUE;
  	}

  	m_ptnStartOutPut->setEnabled(false);
  	m_ptnStopOutput->setEnabled(true);
  	SendDebugOutputCmd(); 

}
void QOutPutDebug::slot_StopOutput()
{
	if(!m_IsConnected)
	{
		if (!OnConnectTestApp())
		{
            CLogPrint::LogString(XLOGLEVEL_ERROR,/* "与测试仪断开连接，请检查网络链路是否连通，IP地址及端口配置是否正确；重新连接" */ g_sLangTxt_Native_Disconnect.GetString());
			return;
		}

		m_IsConnected = TRUE;
	}

    m_ptnStopOutput->setEnabled(false);
	m_ptnStartOutPut->setEnabled(true);
	StopDebugOutputCmd();
}


void QOutPutDebug::slot_Paraschanged()
{
	if(!m_IsConnected)
	{
		if (!OnConnectTestApp())
		{
            CLogPrint::LogString(XLOGLEVEL_ERROR, /* "与测试仪断开连接，请检查网络链路是否连通，IP地址及端口配置是否正确；重新连接" */g_sLangTxt_Native_Disconnect.GetString());
			return;
		}

		m_IsConnected = TRUE;
	}

	SendUpdateParaCmd();
}

long QOutPutDebug::SendDebugOutputCmd()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	InitTestCmdFromParas(oSttCmd, STT_CMD_TYPE_TEST_StartTest);
//	GenerateTestCmdFromDeBugOutputParas(oSttCmd);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,/* "测试仪连接中断，请先与测试仪建立连接。" */ g_sLangTxt_Native_TestrDisconn.GetString());
	}

	return nRet;
}

long QOutPutDebug::StopDebugOutputCmd()
{
	long nRet = 0;

 	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
 	{
 		CSttTestCmd oSttCmd;
 		oSttCmd.m_strID = STT_CMD_TYPE_TEST_StopTest; 
 		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
 	}
	else
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,/* "测试仪连接中断，请先与测试仪建立连接。" */ g_sLangTxt_Native_TestrDisconn.GetString());
	}
 
 	return nRet;
}

long QOutPutDebug::SendUpdateParaCmd()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	InitTestCmdFromParas(oSttCmd, STT_CMD_TYPE_TEST_UpdateParameter);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,/* "测试仪连接中断，请先与测试仪建立连接。" */ g_sLangTxt_Native_TestrDisconn.GetString());
	}

	return nRet;
}

long QOutPutDebug::DisConnectCmd()
{
	long nRet = 0;

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		CSttTestCmd oSttCmd;
		oSttCmd.m_strID = STT_CMD_TYPE_TEST_CloseDevice;
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	
	return nRet;
}

void  QOutPutDebug::InitTestCmdFromParas(CSttTestCmd &oSttTestCmd, const CString &strCmdID)
{
	oSttTestCmd.m_strID = strCmdID;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(FALSE,FALSE);
	pMacro->m_strID = STT_MACRO_ID_ManualTest;
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase* pMacroSerializeBase = oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);

	//序列化参数
	ASSERT(m_pParaSetSttTestResource);
    stt_xml_serialize(&m_oManualTest,pMacroSerializeBase,m_pParaSetSttTestResource->GetVolRsNum(),m_pParaSetSttTestResource->GetVCurRsNum());
	pMacro->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(pMacro);
}

void QOutPutDebug::timerEvent(QTimerEvent * event)
{
	if (m_bHasClosed)
	{
		return;
	}

	if (!m_IsConnected)
	{
		return;
	}

	if(event->timerId() == m_nTimerID)
	{  
		m_pXClientEngine->m_pSttClientSocket->SendHeartbeatCmd();
	} 
}
