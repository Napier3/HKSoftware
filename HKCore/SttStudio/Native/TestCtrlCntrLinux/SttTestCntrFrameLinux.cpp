#include "SttTestCntrFrameLinux.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "../../Module/API/StringConvertApi.h"
#include "../Module/SttTestCtrl/SttTestAppBase.h"
#include "../../Module/SmartCap/XSmartCapMngr.h"
#include "../Module/SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Module/LiveUpdate/SttLiveUpdateDef.h"
#include "../Module/Engine/SttTestEngineClientData.h"
#include "../Module/Engine/SttPowerTestEngineBase.h"
#include "../Module/LiveUpdate/SttLiveUpdateShell.h"
#include "../Module/UI/Module/SttAuxIPSetDlg/SttAuxIPSetDlg.h"
#include "../Module/SttSystemConfig/SttSystemConfig.h"
#include "../Module/RecordTest/UI/SttIecRecordCbWidget.h"
#include "../Module/UI/Module/PopupDialog/SttPopupOpenDialog.h"
#include "../Module/HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../Module/API/StringConvert/String_Gbk_To_Utf8.h"
#include "../Module/XLangResource_Native.h"
#include "../Module/UI/Module/CommConfigurationDlg/DevComm/QSttCommCfgDeviceWidget.h"
#include "../Module/UI/Module/CommConfigurationDlg/CommCfg/QSttCommCfgMainDlg.h"
#include "../Module/UI/Module/CommConfigurationDlg/DevComm/QSttCommCfgDeviceDlg.h"

#ifdef _USE_SoftKeyBoard_	
#include "../Module/UI/SoftKeyboard/SoftKeyBoard.h"
#endif


#ifdef _PSX_QT_LINUX_
#include "../Module/API/NetworkInterface.h"
#include "../../Module/Socket/XPing.h"
#include "../Module/UI/SttEventFilter/SttEventFilter.h"

extern QSttEventFilter *g_pSttEventFilter;
#endif

#include "../../Module/OSInterface/QT/XMessageBox.h"

//2022-12-02 �޸Ĺ���ID���������еĶ�Ҫ���룬Ч�ʵ��£����Դ�ͷ�ļ���ȥ�������κ���Ҫ�����ĵط����а���
#include "../Module/UI/SttTestCntrCmdDefine.h"

//2023-2-21  lijunqing
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdAi/GbWzdAiTool.h"
#include "../Module/UI/Module/CommonCtrl_QT/QSttProgDlg.h"

//2023-3-6  lijunqing  ����װ��IP��ַ
#include "../Module/UI/Controls/NetworkConfig/qnetworkconfigwidget.h"

extern QSttProgDlg *g_pSttGlobalProgDlg;


QSttTestCntrFrameLinux::QSttTestCntrFrameLinux(QWidget *parent) :
    QSttTestCntrFrameBase(parent)
{
// 	if (m_pSttGbTreeView != NULL)//zhouhj 20220326 ��Ϊ��m_pSttGbTreeView��Ӧ����new��֮������,�˴��ö���Ϊ��
// 	{
// 		connect(this,SIGNAL(sig_OnItemStateChanged(CExBaseObject *)),m_pSttGbTreeView,SLOT(slot_ItemStateChanged(CExBaseObject *)));
// 		connect(this,SIGNAL(sig_ShowItems_TreeView(CExBaseList *)),m_pSttGbTreeView,SLOT(slot_ShowItems(CExBaseList *)));
// 	}
	m_pToolBar = NULL;
	m_pMenuWidget = NULL;

	m_pEngineClientWidget = NULL;   //2023-2-20  lijunqing

    //2023-03-01  lijunqing : ���ȴ�������������ڼ�����ʾ��Ϣ
    //�����ͼһֱ����
    m_pOutputWidget = new QSttOutPutWidget(this);
    m_pOutputWidget->hide();

}

QSttTestCntrFrameLinux::~QSttTestCntrFrameLinux()
{
	if (m_pEngineClientWidget != NULL)
	{//2023-2-20  lijunqing
		delete m_pEngineClientWidget;
		m_pEngineClientWidget = NULL;
	}
}


BOOL QSttTestCntrFrameLinux::CreateEngineClientWidget()
{
	if (m_pEngineClientWidget != NULL)
	{
		return FALSE;
	}

	CString strDevMode;
	//strDevMode = g_oSttSystemConfig.GetDevModel();

	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	strDevMode = pCurDevice->m_strModel;

	QPpSttIotEngineClientWidgetMain *pMainWidget  = NULL;

	if (strDevMode == _T("PNS331") || strDevMode.Find(_T("PTU200L")) >= 0)
	{
		pMainWidget = new QSttCommCfgDeviceWidget();
	}
	else
	{
		pMainWidget = new QPpSttIotEngineClientWidgetMain();
	}


	m_pEngineClientWidget = pMainWidget;
	pMainWidget->setParent(this);
	pMainWidget->hide();
	pMainWidget->setGeometry(m_rcWorkArea);

// 	if (g_pTheSttTestApp->m_pDvmDevice != NULL)
// 	{
// 		m_pEngineClientWidget->ShowDvmDevice( g_pTheSttTestApp->m_pDvmDevice );
// 		m_pEngineClientWidget->NewPpSttIotDeviceClient(&g_pTheSttTestApp->m_oCommConfig, g_pTheSttTestApp->m_pDvmDevice);
// 	}	

	connect(m_pEngineClientWidget,  SIGNAL(sig_OnConfigDevice(CDataGroup *)), this, SLOT(slot_OnConfigDevice(CDataGroup *)));
	return TRUE;
}

void QSttTestCntrFrameLinux::InitUI()
{
	resize(m_pSttFrameConfig->m_nWidth,m_pSttFrameConfig->m_nHeight);
	this->setFixedHeight(m_pSttFrameConfig->m_nHeight);
	this->setFixedWidth(m_pSttFrameConfig->m_nWidth);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	
// #ifndef _PSX_QT_LINUX_
// 	this->move(0, 0);
// #endif//2024-2-26 zhouyangyongע�ͣ���ͬ�ֱ����¶�����ΪĬ�Ͼ�����ʾ

	QSttTestCntrFrameBase::InitUI();

	CSttFrame_ToolBar *pToolBarParas = m_pSttFrameConfig->GetToolBar();
	CSttFrame_StatusBar *pStatusBarParas = m_pSttFrameConfig->GetStatusBar();
	CSttFrame_ResultBar *pResultBarParas = m_pSttFrameConfig->GetResultBar();

	m_pToolBar = new QSttBarBase(pToolBarParas, m_oDataBtnsMngr,m_gFont,this);
	m_pToolBar->setGeometry(0,0,pToolBarParas->m_nWidth,pToolBarParas->m_nHeight);

	m_pStatusBar = new QSttBarBase(pStatusBarParas, m_oDataBtnsMngr,m_gFont,this);

	if (pResultBarParas != NULL)
	{
		m_pResultBarUI = new QSttBarBase(pResultBarParas, m_oDataBtnsMngr,m_gFont,this);
		m_pResultBarUI->m_bDrawFrame = FALSE;
		m_pResultBarUI->setGeometry(0,m_pSttFrameConfig->m_nHeight - pResultBarParas->m_nHeight - pStatusBarParas->m_nHeight,pResultBarParas->m_nWidth,pResultBarParas->m_nHeight);
		m_pStatusBar->setGeometry(0,m_pSttFrameConfig->m_nHeight - pStatusBarParas->m_nHeight,pStatusBarParas->m_nWidth,pStatusBarParas->m_nHeight);
		m_pResultWidget = m_pResultBarUI->FindResultPanel();
	}
	else
	{
		m_pStatusBar->setGeometry(0,m_pSttFrameConfig->m_nHeight - pStatusBarParas->m_nHeight,pStatusBarParas->m_nWidth,pStatusBarParas->m_nHeight);
	}

	UpdateButtonsStateByID();

	//��Ŀ�б���ͼ
	CSttFrame_GbTree *pTree = m_pSttFrameConfig->GetGbTree();
	m_pSttGbTreeView = new QSttGuideBookTreeWidget(NULL, pTree, this);
	m_pSttGbTreeView->hide();

	g_theTestCntrFrame = this;
	CalRectArea();

	//��Ϣ��ͼһֱ����
	InitInfoWidget(this);
	m_pInfoWidget->hide();

	InitFAParasSetDialog(this);
	m_pSttFaParasSetDialog->hide();

	InitIecRecordMain();

	InitRemoteCtrl();

	//��ʼ����ɣ��ټ��ر�����ͼ
    //m_pSttReportViewHtml = new QSttReportViewHtml(this);
    //m_pSttReportViewHtml->hide();
    //m_pSttReportViewHtml->OpenHtmlFile(STT_REPORT_HEAD_HTML_FILE);   //�򿪱���ͷ�ļ�

}

void QSttTestCntrFrameLinux::UpdateButtonsStateByID()
{
	//��ʼ����ʱ�������ֶ�������ť sf 20220222
	UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
	//�մ򿪵�ʱ�򣬿�ʼ���Բ�ʹ��
	UpdateButtonStateByID(STT_CNTR_CMD_StartTest,false,true);

	//ϵͳ����ҳ�棬δ��ѡ�����֡���Ӧ���ء�IEC���á���ť sf 20220317
	if ((!g_oSystemParas.HasDigitalInOrOut())&&(g_pTheSttTestApp->m_pTestMacroUI != NULL))//20220528zhouhj ��δѡ����,��IEC����ʱ,����IEC����
	{
		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,false,false);
	}
// 	else
// 	{
// 		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,true,true);
// 	}

	AdjustToolBarButtons();
}

void QSttTestCntrFrameLinux::CalRectArea()
{
	CSttFrame_GbTree *pGbTree = m_pSttFrameConfig->GetGbTree();

	CSttFrame_ToolBar *pToolBarParas = m_pSttFrameConfig->GetToolBar();
	CSttFrame_StatusBar *pStatusBarParas = m_pSttFrameConfig->GetStatusBar();
	CSttFrame_ResultBar *pResultBarParas = m_pSttFrameConfig->GetResultBar();
	int nHeight = m_pSttFrameConfig->m_nHeight - pStatusBarParas->m_nHeight - pToolBarParas->m_nHeight - 2*SttFrame_Interval;

	if ((m_pResultBarUI != NULL)&&(pResultBarParas != NULL))
	{
		nHeight = m_pSttFrameConfig->m_nHeight - pToolBarParas->m_nHeight - pStatusBarParas->m_nHeight
			- pResultBarParas->m_nHeight - 2*SttFrame_Interval;
	} 

	if (m_pSttGbTreeView == NULL || m_pSttGbTreeView->isVisible() == false)
	{
		m_rcWorkArea = QRect(0, pToolBarParas->m_nHeight + SttFrame_Interval, m_pSttFrameConfig->m_nWidth,nHeight);
	}
	else
	{
		CSttFrame_Size *pSize = pGbTree->GetSize();

		m_rcGbItemsArea = QRect(0,pToolBarParas->m_nHeight + SttFrame_Interval,pSize->m_nWidth,nHeight);
		m_rcWorkArea = QRect(pSize->m_nWidth, pToolBarParas->m_nHeight + SttFrame_Interval, m_pSttFrameConfig->m_nWidth - pSize->m_nWidth - SttFrame_Interval, nHeight);

		if (m_pSttGbTreeView != NULL)
		{
			m_pSttGbTreeView->setGeometry(m_rcGbItemsArea);
		}
	}

	if (m_pActiveWidget != NULL)
	{
		m_pActiveWidget->setGeometry(m_rcWorkArea);
	}
}

void QSttTestCntrFrameLinux::UpdateToolButtons_FloatPanel()
{
	if (m_pToolBar == NULL)
	{
		return;
	}

	QSttFloatPanel *pSttFloatPanel = (QSttFloatPanel*)m_pToolBar->FindFloatPanel();

	if (pSttFloatPanel == NULL)
	{
		return;
	}

	pSttFloatPanel->UpdateCurrShowButton();
}

void QSttTestCntrFrameLinux::UpdateButtonStateByID( const CString &strID,bool bState,bool bShow )
{
	if ((m_pManualTriggerBtn != NULL)&&(m_pManualTriggerBtn->m_strID == strID))
	{
		QSttToolButtonBase *pButtonUI = (QSttToolButtonBase*)m_pManualTriggerBtn->m_dwItemData;

		if (pButtonUI != NULL)
		{
			pButtonUI->m_bShow = bShow;
			pButtonUI->setEnabled(bState);
			pButtonUI->setVisible(bShow);
		}
		return;
	}

	if (m_pToolBar != NULL)
	{
		for(int i = 0; i<m_pToolBar->m_plistPanel.size();i++)
		{
			QSttPanelBase* pPanel = m_pToolBar->m_plistPanel.at(i);
			for (int j = 0;j < pPanel->m_listCtrls.size(); j++)
			{
				QSttToolButtonBase* pButton = pPanel->m_listCtrls.at(j);
				if (pButton->m_pCfgData->m_strID == strID)
				{
					pButton->setDisabled(!bState);
//					pButton->ShowBtn(bShow);
					pButton->m_bShow = bShow;
					break;
				}
			}
		}
	}

	if (m_pMenuWidget != NULL)
	{
		for(int i = 0; i < m_pMenuWidget->m_Btnlist.size(); i++)
		{
			QSttItemButton *pButton = m_pMenuWidget->m_Btnlist.at(i);
			if (pButton->m_pItem->m_strID == strID)
			{
				pButton->setDisabled(bState);
				pButton->setVisible(bShow);
				break;
			}
		}
	}
}

void QSttTestCntrFrameLinux::UpdateEnableState(const CString &strState)
{
	if (m_pToolBar != NULL)
	{
		m_pToolBar->UpdateEnableState(strState);
	}
}

void QSttTestCntrFrameLinux::InitSttIecRecord()
{
	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	CSttTestAppCfg* pSttTestAppCfg = pNative->m_oSttAtsClient.GetSttTestAppCfg();
	g_pTheSttTestApp->InitKeyDB();//20230302 zhouhj ��̽�����ʱ,���KeyDBδ��ʼ��,��Ҫ���г�ʼ��
	g_pTheSttTestApp->InitSttIecRecord(pSttTestAppCfg);
}

//zhouhj 20230606 ��Ϊʹ��InitAfterCreateSttMacroPara����
// void QSttTestCntrFrameLinux::InitSttCap_MUTerminal()
// {
// 	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();
// 
// 	if(strIDMacroUI == STT_ORG_MACRO_MUTimingAccurTest
// 		|| strIDMacroUI == STT_ORG_MACRO_MUPunctAccurTest)
// 	{
// 		InitSttIecRecord();
// 		g_bSmartCap_RecordNow = FALSE;//������ӽ���ʱ,ֹͣ���Ľ���
// 		CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();
// 
// 		if (pXSttCap_61850 != NULL)
// 		{
// 			pXSttCap_61850->MUTimeTestRlt_AddDataset();
// 		}
// 	}
// }

BOOL QSttTestCntrFrameLinux::IsMenuWidget(QWidget *pWidget)
{
	if (m_pMenuWidget == NULL)
	{
		return FALSE;
	}

	return (m_pMenuWidget == pWidget);
}

void QSttTestCntrFrameLinux::AdjustToolBarButtons()
{
	m_pToolBar->AdjustPanels();
}

void QSttTestCntrFrameLinux::AdjustStatusBarButtons()
{
	m_pStatusBar->AdjustPanels();
}

void QSttTestCntrFrameLinux::Before_OnCmd()
{
	if (m_pMenuWidget != NULL)
	{
#ifdef _PSX_QT_LINUX_
		if (g_pSttEventFilter != NULL)
		{
			g_pSttEventFilter->m_pWidgetForHide = NULL;
		}
#endif
		m_pMenuWidget->close();
		delete m_pMenuWidget;
		m_pMenuWidget = NULL;
	}
}

void QSttTestCntrFrameLinux::OnCmd_Menu()
{
	if (m_pMenuWidget != NULL)
	{
#ifdef _PSX_QT_LINUX_
		if (g_pSttEventFilter != NULL)
		{
			g_pSttEventFilter->m_pWidgetForHide = NULL;
		}
#endif

		BOOL bHasHidden = m_pMenuWidget->isHidden();
		slot_CloseMenu();

		if (!bHasHidden)
		{
			return;
		}
	}
//	else
	{
		CSttFrame_Menus *pMenusParas = m_pSttFrameConfig->GetMenus();

		if (pMenusParas == NULL)
		{
			return;
		}

		if (pMenusParas->m_nUse == 0)
		{
			CSttFrame_ToolBar *pToolBarParas = m_pSttFrameConfig->GetToolBar();
			CString strState;
			if (IsTestStarted())
			{
				strState = STT_TEST_STATE_TESTTING;
			}
			else
				strState = STT_TEST_STATE_TEST_STOPED;

#ifdef _PSX_QT_LINUX_
			m_pMenuWidget = new QSttMenuWidget(pMenusParas,strState,m_gFont,this);
#else
			m_pMenuWidget = new QSttMenuWidget(pMenusParas,strState,m_gFont,NULL);
#endif
			m_pMenuWidget->m_strHideButton.append(STT_CNTR_CMD_IECConfig);

// 			if (!m_bSelMacroShow)
// 			{
// 				m_pMenuWidget->m_strHideButton.append(STT_CNTR_CMD_AddMacro);
// 			}

			// sy ���������ļ��е����Կ����Ƿ���ʾѡ����
			if (m_nSelMacroShow == 0)
			{
				m_pMenuWidget->m_strHideButton.append(STT_CNTR_CMD_AddMacro);
			}

			CSttMacroTestUI_TestMacroUI *pTestMacroUI = m_pTestCtrlCntrBase->GetCurrTestMacroUI();

			if ((pTestMacroUI == NULL) || (!pTestMacroUI->HasCharLib()))
			{
				m_pMenuWidget->m_strHideButton.append(STT_CNTR_CMD_CharDrawView);
			}

			m_pMenuWidget->Init();

			if (pToolBarParas != NULL)
			{
				//zhouhj 2024.4.25 ֮ǰ��ģʽ�����⣬�ڶ��İ�ϵͳ���޷�ʶ��
#ifdef USE_IN_Astra_LINUX
				m_pMenuWidget->move(0, pToolBarParas->m_nHeight);
#else
				m_pMenuWidget->move(pos().x(),pos().y() + pToolBarParas->m_nHeight);
#endif
// 				CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("x=%d,y=%d,m_nHeight=%ld"),pos().x()
// 					,pos().y(),pToolBarParas->m_nHeight);
// 				QDesktopWidget* desktopWidget = QApplication::desktop();
// 				QRect screenRect = desktopWidget->screenGeometry();
// 				int cx = screenRect.width();
// 				int cy = screenRect.height();
// 				int Menu_X = (cx - (m_pSttFrameConfig->m_nWidth)*g_dUIShowCoef)/2;
// 				int Menu_Y = (cy - (m_pSttFrameConfig->m_nHeight)*g_dUIShowCoef)/2;
// 				m_pMenuWidget->move(Menu_X, Menu_Y+pToolBarParas->m_nHeight);//2024-3-4 zhouyangyong��������к󣬲˵��ĵ���λ��Ҳ��֮����
			}

			m_pMenuWidget->show();

#ifdef _PSX_QT_LINUX_
			if (g_pSttEventFilter != NULL)
			{
				g_pSttEventFilter->m_pWidgetForHide = m_pMenuWidget;
			}
#endif
		}
	}
}

void QSttTestCntrFrameLinux::slot_CloseMenu()
{
	if (m_pMenuWidget == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_

	if (g_pSttEventFilter != NULL)
	{
		g_pSttEventFilter->m_pWidgetForHide = NULL;
	}
#endif
	m_pMenuWidget->close();
	delete m_pMenuWidget;
	m_pMenuWidget = NULL;
}

void QSttTestCntrFrameLinux::OnCmd_StartTest()
{
	if (m_bIsRunningStartStopCmd)
	{
		return;
	}

	m_bIsRunningStartStopCmd = TRUE;
	QSttTestCntrFrameBase::OnCmd_StartTest();
	m_bIsRunningStartStopCmd = FALSE;
}

void QSttTestCntrFrameLinux::OnCmd_ULiveupdate()
{
	QStringList astrPostfix;
	CString strFolderPath;

	if (!Global_GetUsbRootFolderPath(strFolderPath))
	{
        CXMessageBox::information(this,tr("����"),/*tr("δʶ��U��,����U�̽�������.")*/
			g_sLangTxt_Native_UnrecognizedUSB);
		return;
	}

	astrPostfix<<"*.zip"/*<<"*.rar"*/;
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	CString strFilePath;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}

	if (!m_oDataBtnsMngr.IsCharging())
	{
        CXMessageBox::information(this,tr("����"),/*tr("���ó���߽�������.")*/g_sLangTxt_Native_ChargingUpgrade);
		
		if(!m_oDataBtnsMngr.IsCharging())
		{
		return;
	}
	}

	if (g_pSttGlobalProgDlg != NULL)
	{
		g_pSttGlobalProgDlg->SetText(/*_T("��������������,���Ժ�...")*/g_sLangTxt_Native_OfflineUpgrade,/*_T("����������")*/g_sLangTxt_Native_UpgradeProgressBar);
		g_pSttGlobalProgDlg->Start(0,100,50);
		CTickCount32 oTickCount;
		oTickCount.DoEvents(20);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,/*_T("׼����������(%s).")*/
		g_sLangTxt_Native_PreparationUpgrade.GetString(),strFilePath.GetString());

#ifdef _PSX_QT_LINUX_
	CString strVerRemoteRelPath,strFileName;
	strFileName = GetFileNameFromFilePath(strFilePath);
	strVerRemoteRelPath = QString("%1%2").arg(LIVEUPDATE_PATH_TEMP).arg(strFileName);

	CString strArgv;
	strArgv.Format(_T("%s=%s;"), STT_CMD_PARA_LIVEUPDATE_VERFILE, strVerRemoteRelPath.GetString());
	CString strVerUnzipPath,strVerTempPath;
	strVerUnzipPath = STTNATIVE_PATH_ROOT;
	strVerUnzipPath += LIVEUPDATE_PATH_UNZIP;
	strVerTempPath = STTNATIVE_PATH_ROOT;
	strVerTempPath += LIVEUPDATE_PATH_TEMP;
	CreateAllDirectories(strVerUnzipPath);
	CreateAllDirectories(strVerTempPath);

	QTextCodec *pOldTextCodec = NULL;
    InitLocalCodec_BeforeReadWrite(strFilePath,&pOldTextCodec);
	QFile::copy(strFilePath, STTNATIVE_PATH_ROOT + strVerRemoteRelPath);
	ResetLocalCodec(pOldTextCodec);

	theLiveUpdate.Init();
	theLiveUpdate.TestAppUpdate_OffLine(strArgv);
	CTickCount32 oTickCount;
	oTickCount.DoEvents(500);
// 	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
// 	CSttTestAppCfg* pSttTestAppCfg = pNative->m_oSttAtsClient.GetSttTestAppCfg();
// 
// 	CString strCloudIP;
// 	strCloudIP = pSttTestAppCfg->GetCloudIP();
// 
// 	xping(strCloudIP);
// 
// 	if (!g_oSttTestAppConfigTool.ConnectServer(pSttTestAppCfg, pSttTestAppCfg->GetTestAppIP(), STT_PORT_LOCAL_UPDATE))
// 	{
// 		g_pSttGlobalProgDlg->Stop();
// 		CLogPrint::LogString(XLOGLEVEL_RESULT,/*_T("���Ӱ汾���³���ʧ��.")*/g_sLangTxt_Native_VersionUpdateFailed.GetString());
// 		return;
// 	}

	system("pkill -9 SttTestMainCore");
	system("pkill -9 SttTestServer_PNS330");
	system("pkill -9 SttNativeMain");
#endif

//    if (!theLiveUpdate.IsProcessExist())
//    {
//        theLiveUpdate.Init();
//        theLiveUpdate.TestAppUpdate();
//    }
//
//#ifdef _PSX_QT_LINUX_
//    stt_net_dhcp();
//
//    CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
//    CSttTestAppCfg* pSttTestAppCfg = pNative->m_oSttAtsClient.GetSttTestAppCfg();
//
//    CString strCloudIP;
//    strCloudIP = pSttTestAppCfg->GetCloudIP();
//
//    xping(strCloudIP);
//
//    if (!g_oSttTestAppConfigTool.ConnectServer(pSttTestAppCfg, pSttTestAppCfg->GetTestAppIP(), STT_PORT_LOCAL_UPDATE))
//    {
//        g_pSttGlobalProgDlg->Stop();
//        CLogPrint::LogString(XLOGLEVEL_RESULT,/*_T("���Ӱ汾���³���ʧ��.")*/g_sLangTxt_Native_VersionUpdateFailed.GetString());
//        return;
//    }
//
//    CString strVerUnzipPath,strVerTempPath;
//    strVerUnzipPath = STTNATIVE_PATH_ROOT;
//    strVerUnzipPath += LIVEUPDATE_PATH_UNZIP;
//    strVerTempPath = STTNATIVE_PATH_ROOT;
//    strVerTempPath += LIVEUPDATE_PATH_TEMP;
//    CreateAllDirectories(strVerUnzipPath);
//    CreateAllDirectories(strVerTempPath);
//
//    QString strVerRemoteRelPath,strFileName;
//    strFileName = GetFileNameFromFilePath(strFilePath);
//    strVerRemoteRelPath = QString("%1%2").arg(LIVEUPDATE_PATH_TEMP).arg(strFileName);
//
//    CSttSystemCmd oCmdLocal;
//    oCmdLocal.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;
//
//    CSttParas oParas;
//    oParas.m_strID = UPDATEPARAS_TYPE_LOCAL;
//    oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERFILE,strVerRemoteRelPath);
//    oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH,LIVEUPDATE_PATH_UNZIP);
//    oCmdLocal.AddNewChild(&oParas);
//
//    g_oSttTestAppConfigTool.m_pClientEngine->SetTestEventInterface((CTestEventBaseInterface*)m_pResultWidget);
//
//    long nLenSend = g_oSttTestAppConfigTool.m_pClientEngine->m_pSttClientSocket->SendCmd(&oCmdLocal);
//    oCmdLocal.RemoveAll();
//    if (nLenSend<=0)
//    {
//        g_pSttGlobalProgDlg->Stop();
//        CLogPrint::LogString(XLOGLEVEL_RESULT,/*_T("���Ͱ汾��������ʧ��.")*/g_sLangTxt_Native_CommandFailed);
//        return;
//    }
//    else
//    {
//        QFile::copy(strFilePath, STTNATIVE_PATH_ROOT + strVerRemoteRelPath);
//
//        CSttSystemCmd oCmd;
//        oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;
//
//        CSttParas oParas;
//        oParas.m_strID = UPDATEPARAS_TYPE_FILE;
//
//        oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_FILEOVER,_T("1"));
//        oCmd.AddNewChild(&oParas);
//        CTickCount32 oUpdateTickCount;
//        CLogPrint::LogString(XLOGLEVEL_RESULT,_T("׼��������������."));
//        oUpdateTickCount.DoEvents(50);
//
//        nLenSend = g_oSttTestAppConfigTool.m_pClientEngine->m_pSttClientSocket->SendCmd(&oCmd);
//        oCmd.RemoveAll();
//
//        if (nLenSend<=0)
//        {
//            g_pSttGlobalProgDlg->Stop();
//            CLogPrint::LogString(XLOGLEVEL_RESULT,/*_T("���Ұ汾������ʧ��.")*/g_sLangTxt_Native_LookupFailed);
//            return;
//        }
//        else
//        {
//            hide();
//            oUpdateTickCount.DoEvents(50);
//            CLogPrint::LogFormatString(XLOGLEVEL_RESULT,/*_T("��������(SttLiveUpdate)�����ɹ�,��ʼ׼������.")*/
//                g_sLangTxt_Native_LiveUpdate.GetString());
//            oUpdateTickCount.DoEvents(50);
//            system("pkill -9 SttTestMainCore");
//            system("pkill -9 SttTestServer_PNS330");
//            system("pkill -9 SttNativeMain");
//        }
//    }
//#endif
}

void QSttTestCntrFrameLinux::OnCmd_Liveupdate()
{
// 	CString strSavePath,strTestDirPath;
// 	CString strUtf8SavePath;
// 	unsigned char *pgbkPath = NULL,*putf8Path = NULL;
// 	int nUtf8Lenth = 0;
// 	strSavePath = _P_GetLibraryPath();
// 	strSavePath += _T("����.xml");
// 
// //  	if (g_oSttTestResourceMngr.m_oChMaps.SaveChMapsFile(strSavePath))
// //  	{
// //  		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("�洢�����ļ��ɹ�(GBKͨ��ӳ��)(%s)."),strSavePath.GetString());
// //  	}
// //  	else
// 	{
// 		CString_to_char(strSavePath,(char**)&pgbkPath);
// 		gbk_to_utf8_r(pgbkPath,strlen((char*)pgbkPath),&putf8Path,&nUtf8Lenth,0);
// 		strUtf8SavePath = (const char *)putf8Path;
// 
// 		if (g_oSttTestResourceMngr.m_oChMaps.SaveChMapsFile(strUtf8SavePath))
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("�洢�����ļ��ɹ�(UTF8ͨ��ӳ��)(%s)."),strUtf8SavePath.GetString());
// 		} 
// 		else
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("�洢�����ļ�ʧ��(UTF8ͨ��ӳ��)(nUtf8Lenth=%d;%s,%s)."),nUtf8Lenth,putf8Path,strUtf8SavePath.GetString());
// 		}
// 
// 		delete pgbkPath;
// 		pgbkPath = NULL;
// 
// 		if (putf8Path != NULL)
// 		{
// 			delete putf8Path;
// 			putf8Path = NULL;
// 		}
// 	}
// 
// 	strTestDirPath = _P_GetLibraryPath();
// 	strTestDirPath += _T("����/");
// 	CreateAllDirectories(strTestDirPath);
// 	nUtf8Lenth = 0;
// 	CString_to_char(strTestDirPath,(char**)&pgbkPath);
// 	gbk_to_utf8_r(pgbkPath,strlen((char*)pgbkPath),&putf8Path,&nUtf8Lenth,0);
// 	strUtf8SavePath = (const char *)putf8Path;
// 	CreateAllDirectories(strUtf8SavePath);
// 	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("����UTF8�����ļ���(nUtf8Lenth=%d;%s,%s)."),nUtf8Lenth,putf8Path,strUtf8SavePath.GetString());
// 
// 	delete pgbkPath;
// 
// 	if (putf8Path != NULL)
// 	{
// 		delete putf8Path;
// 	}
	
 	if (!m_oDataBtnsMngr.IsCharging())
 	{
        CXMessageBox::information(this,tr("����"),/*tr("���ó���߽�������.")*/g_sLangTxt_Native_Upgradation);

 		if(!m_oDataBtnsMngr.IsCharging())
		{
			return;
		}
 	}

	CString strMsg;
	strMsg =/* "�������,��������,�Ƿ���£�"*/g_sLangTxt_Native_UpdateSoftware;
	int result = CXMessageBox::information(this,/* tr("��ʾ")*/g_sLangTxt_Message, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result != QMessageBox::Yes)
	{
		return;
	}

	if (g_pSttGlobalProgDlg != NULL)
	{
		g_pSttGlobalProgDlg->SetText(/*_T("��������������,���Ժ�...")*/g_sLangTxt_Native_OnlineUpgrade.GetString(),/*_T("����������")*/g_sLangTxt_Native_UpgradeProgressBar.GetString());
		g_pSttGlobalProgDlg->Start(0,100,50);
		CTickCount32 oTickCount;
		oTickCount.DoEvents(20);
	}

	if (!theLiveUpdate.IsProcessExist())
	{
		theLiveUpdate.Init();
		theLiveUpdate.TestAppUpdate();
	}

#ifdef _PSX_QT_LINUX_
    CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
    CSttTestAppCfg* pSttTestAppCfg = pNative->m_oSttAtsClient.GetSttTestAppCfg();

	stt_net_dhcp();
	CString strCloudIP;
	strCloudIP = pSttTestAppCfg->GetCloudIP();

	if (!xping(strCloudIP))
	{
		if (g_pSttGlobalProgDlg)
		{
			g_pSttGlobalProgDlg->Stop();
		}
		CLogPrint::LogString(XLOGLEVEL_RESULT,/*_T("��ƽ̨IPδpingͨ,�������������Ƿ�����.")*/g_sLangTxt_Native_NetworkConnectionFailed.GetString());
		return;
	}

	if (!g_oSttTestAppConfigTool.ConnectServer(pSttTestAppCfg, pSttTestAppCfg->GetTestAppIP(), STT_PORT_LOCAL_UPDATE))
	{
		if (g_pSttGlobalProgDlg)
		{
			g_pSttGlobalProgDlg->Stop();
		}
		CLogPrint::LogString(XLOGLEVEL_RESULT,/*_T("���Ӱ汾���³���ʧ��.")*/g_sLangTxt_Native_VersionUpdateFailed.GetString());
		return;
	}

	CSttSystemCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_SYSTEM_LiveUpdate;

	CSttParas  *pParas = new CSttParas;
	pParas->m_strID = UPDATEPARAS_TYPE_REMOTE;

	//m_oVerUpdateCfgMngr.Open();
	//CVerUpdateCfgYun* pCfgYun = m_oVerUpdateCfgMngr.GetCfgYun();
	pParas->AddNewData(STT_CMD_PARA_LIVEUPDATE_IPCLOUD,"");
	pParas->AddNewData(STT_CMD_PARA_LIVEUPDATE_PORTCLOUD,"");	
	pParas->AddNewData(STT_CMD_PARA_LIVEUPDATE_FTPPORTCLOUD,"");
	//oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_SYSINDEX,"50");	//ϵͳ����
	//oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERID,m_pAts_Version->m_strID);				//�汾��
	//oParas.AddNewData(STT_CMD_PARA_LIVEUPDATE_VERINDEX,"194");	//�汾����
	pParas->AddNewData(STT_CMD_PARA_LIVEUPDATE_UNZIPPATH,LIVEUPDATE_PATH_UNZIP);
	oCmd.AddNewChild(pParas);

	g_oSttTestAppConfigTool.m_pClientEngine->SetTestEventInterface((CTestEventBaseInterface*)m_pResultWidget);
	CTickCount32 oUpdateTickCount;
	CLogPrint::LogString(XLOGLEVEL_RESULT,_T("׼��������������."));
	oUpdateTickCount.DoEvents(50);

	long nLenSend = g_oSttTestAppConfigTool.m_pClientEngine->m_pSttClientSocket->SendCmd(&oCmd);

	if (nLenSend<=0)
	{
		if (g_pSttGlobalProgDlg)
		{
			g_pSttGlobalProgDlg->Stop();
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("���Ͱ汾��������ʧ��.")*/g_sLangTxt_Native_CommandFailed.GetString());
	}
    else
    {
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("��������ͳɹ�,��ʼ����....."));
		oUpdateTickCount.DoEvents(50);
        system("pkill -9 SttTestMainCore");
        system("pkill -9 SttTestServer_PNS330");
		system("pkill -9 SttNativeMain");
 //	 	system("pkill -9 TestCtrlCntrLinux");

    }
  #endif
}

void QSttTestCntrFrameLinux::OnCmd_AuxIPSet()
{
	QSttAuxIPSetDlg oAuxIPSetDlg;
	oAuxIPSetDlg.setWindowModality(Qt::WindowModal);
	CSttDevConfig *pDevConfig = g_oSttSystemConfig.GetSttDevConfig();
	oAuxIPSetDlg.InitParas(pDevConfig->m_strAuxIP);

	if (oAuxIPSetDlg.exec() != QDialog::Accepted)
		return;

	pDevConfig->m_strAuxIP = oAuxIPSetDlg.GetCurrIP();
	g_oSttSystemConfig.SaveSystemConfig();
}

void QSttTestCntrFrameLinux::OnCmd_RemoteCtrl()
{
	SetActiveWidget(m_pRemoteCtrlWidget, ActiveWidgetType_Other);
}

void QSttTestCntrFrameLinux::OnCmd_PpIotEngineClientDlg()
{
	CString strDevMode;
	strDevMode = g_oSttSystemConfig.GetDevModel();
	g_pTheSttTestApp->IinitGbWzdAiTool();

	if (m_pEngineClientWidget == NULL)
	{
		CreateEngineClientWidget();
	}

	QSttCommCfgDeviceDlg oSttComDlg(m_pEngineClientWidget,this);
	//oSttComDlg.setParent(this);
	//=====================
#ifdef _USE_SoftKeyBoard_	
	QSoftKeyBoard::AttachObj(&oSttComDlg, Keyboard::NUMBER);
#endif
	oSttComDlg.exec();
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	// 	if (strDevMode == "PNS331")
	// 	{
	// 		
	// 	}
	// 	else
	// 	{
	// 		QPpSttIotEngineClientWidgetMain oMainWidget(this);
	// 		oMainWidget.UpdateTitleAndSize(CString("װ��ͨѶ"),800, 630);
	// #ifdef _USE_SoftKeyBoard_	
	// 		QSoftKeyBoard::AttachObj(&oMainWidget, Keyboard::NUMBER);
	// #endif
	// 		//m_pEngineClientWidget = pMainWidget;
	// 		//pMainWidget->setParent(this);
	// 		//pMainWidget->hide();
	// 		//pMainWidget->setGeometry(m_rcWorkArea);
	// 
	// 		if (g_pTheSttTestApp->m_pDvmDevice != NULL)
	// 		{
	// 			oMainWidget.ShowDvmDevice( g_pTheSttTestApp->m_pDvmDevice );
	// 			oMainWidget.NewPpSttIotDeviceClient(&g_pTheSttTestApp->m_oCommConfig, g_pTheSttTestApp->m_pDvmDevice);
	// 		}	
	// 
	// 		oMainWidget.exec();
	// 
	// #ifdef _USE_SoftKeyBoard_
	// 		QSoftKeyBoard::ReAttachObj();
	// #endif
	// 	}
}

void QSttTestCntrFrameLinux::OnCmd_StopTest()
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return;
	}

	if (m_bIsRunningStartStopCmd)
	{
		return;
	}

	m_bIsRunningStartStopCmd = TRUE;
	EnableStartStopButton(FALSE);

	if (!m_pTestCtrlCntrBase->StopTest())
	{
#ifdef _PSX_QT_LINUX_
		CString strTitile,strMsg;
		strTitile = g_sLangTxt_Message/*"��ʾ"*/;
		strMsg = g_sLangTxt_Native_StopTestSendFail/*"ֹͣ���������·�ʧ��."*/;
		CXMessageBox::information(this, strTitile, strMsg);
#endif
//		EnableStartStopButton(TRUE);
		//��������ֹͣ���Դ���
		OnTestStoped();
	}

	m_bIsRunningStartStopCmd = FALSE;
}

void QSttTestCntrFrameLinux::OnCmd_IecCap()
{
	m_pSttIecRecordMainWidget->SetIecCapWriteFile(false);
	InitSttIecRecord();
	CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

	if (pXSttCap_61850 == NULL)
	{
		return;
	}

	if ((pXSttCap_61850->m_oCapDeviceAll.GetCount() == 0)&&(g_bSmartCap_RecordNow))//20220610 ��һ�ν����ʱ,���ÿ���¼��,�ڽ�����ӽ���ʱ,����¼��
	{
		g_bSmartCap_RecordNow = 0;
	}

	OnCmd_IecCap_Prepare();//zhouhj2023.9.2
	SetActiveWidget(m_pSttIecRecordMainWidget, ActiveWidgetType_Other);

	long nPkgDetectType = -1;
	if (g_oSystemParas.m_nIecFormatMeas != STT_IEC_FORMAT_61850_92)
	{
		//20240821 suyang ���뱨��̽��ʱ����ϵͳ������ѡ�����������FT3
		nPkgDetectType = 3;
	}

	if ((g_pTheSttTestApp->m_pTestMacroUI != NULL)&&(g_theSttIecRecordMainWidget != NULL))
	{
		g_theSttIecRecordMainWidget->InitIecRecordCbWidget(g_pTheSttTestApp->m_pTestMacroUI->m_strID,/*-1*/nPkgDetectType);
	}

	if(g_theSttIecRecordMainWidget != NULL)
	{
		//g_pTheSttTestApp->m_pTestMacroUI ��Ϊ�յģ�������Ϊ�˴���������뱨��̽��ʱ�ܸ��¹�ѡ״̬
		if (g_oSystemParas.m_nIecFormatMeas != STT_IEC_FORMAT_61850_92)
		{
			g_theSttIecRecordMainWidget->UpdateIecDetectType(nPkgDetectType);
		}
	}
}

void QSttTestCntrFrameLinux::OnCmd_IecCapWriteFile()
{
	OnCmd_IecCap();
	m_pSttIecRecordMainWidget->SetIecCapWriteFile(true);
}

void QSttTestCntrFrameLinux::OnCmd_IecCapDebugHead()
{
	OnCmd_IecCap();
	m_pSttIecRecordMainWidget->SetIecCapWriteFile(true);
	CXCapPkgBufferMngrInterface::XSmartCapDebugHead();
}


void QSttTestCntrFrameLinux::OnCmd_AddMacro(BOOL bUseNameID)
{
	QSttTestCntrFrameBase::OnCmd_AddMacro(FALSE);
}

void QSttTestCntrFrameLinux::OnCmd_PpIotEngineClient()
{
	//2023-03-01 lijunqing Ϊ����߳��������ٶȣ���ͨ����صģ���ͨ�Ž����ʱ����������ʼ��
	g_pTheSttTestApp->IinitGbWzdAiTool();

	CreateEngineClientWidget();

	SetActiveWidget(m_pEngineClientWidget, ActiveWidgetType_Other);

	g_theGbWzdAiTool->SetSttGuideBook((CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook());
}

void QSttTestCntrFrameLinux::OnCmd_NetworkConfig()
{
	QNetworkConfigWidget dlg(this);
	dlg.InitUI();
	dlg.slot_ScanClicked();
	dlg.exec();
}

void QSttTestCntrFrameLinux::OnCmd_OpenTest()
{
	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = _P_GetWorkspacePath();
	astrPostfix<<"*.gbrpt";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		oOpenDlg.resize(850,500);
		oOpenDlg.setFixedHeight(500);
	}

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	CString strFilePath;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}

    BOOL bRet = OpenTest(strFilePath, "");

// 	if ( !bRet)
// 	{
// 		m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
// 		//ɾ��֮ǰ��tab
// 		if (m_pMacroEditView != NULL)
// 		{
// 			QWidget *pMacroEditWidget = NULL;
// 			long nTabIndex = 0;
// 			pMacroEditWidget = GetMacroEditWidget();
// 			nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
// 			m_tabTestViews->removeTab(nTabIndex);
// 		}
// 
// 		SetActiveWidget(NULL);
// 		g_pTheSttTestApp->SetCurrTestMacroUI(NULL);
// 		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
// 		return;
// 	}



// 	CString strFile = OpenTestDlg();
// 
// 	if (strFile.GetLength() < 5)
// 	{
// 		return;
// 	}
// 
// 	if (m_pCmdWzdDsEditWidget != NULL)
// 	{
// 		//���´�������ʱ�������в�������
// 		m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
// 		m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
// 		DeleteCmdWzdDsEditWidget();
// 	}
// 
// 	ClearSmartGenWzd();
// 	m_pSttGbTreeView->show();
// 
// 	//2023-9-4 �ȴ�wzdxml�ļ�����ֹģ���Ǵӱ�ĵط����������ġ���Ϊ����ģ��ʱ�����޸�wzdxml�е�ģ���ļ�·����
// 	CString strWzdxml = ChangeFilePostfix(strFile, GbSmartGenWzd_File_Postfix);
// 	g_theGbSmartGenWzd->OpenSmartGenWzdFile(strWzdxml);
// 
// 	BOOL bRet = OpenTest(strFile, g_theGbSmartGenWzd->m_strDvmFile);
// 
// 	if ( !bRet)
// 	{
// 		m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
// 		//ɾ��֮ǰ��tab
// 		if (m_pMacroEditView != NULL)
// 		{
// 			QWidget *pMacroEditWidget = NULL;
// 			long nTabIndex = 0;
// 			pMacroEditWidget = GetMacroEditWidget();
// 			nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
// 			m_tabTestViews->removeTab(nTabIndex);
// 		}
// 
// 		SetActiveWidget(NULL);
// 		g_pTheSttTestApp->SetCurrTestMacroUI(NULL);
// 		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
// 		return;
// 	}
// 
// 	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
// 	pGuideBook->AddTimeSettingCoef(g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms);  //��ģ��ʱ��ҲҪ����ʱ�䶨ֵ����ϵ��
// 	//��ģ���������ص�ͨѶ����
// 	CreateEngineClientWidget();
// 
// 	//ң�����ӳ��
// 	InitAinDataMap(pGuideBook->m_pAinDataMapCfg);
// 
// 	//��ģ����ʼ��������Ͳ˵�
// 	UpdateToolButtons_AfterAddMacro();
// 	SelectActionByID(STT_CNTR_CMD_TemplateView, TRUE);
// 	SelectActionByID(STT_CNTR_CMD_VectorDrawView, TRUE);
// 	SelectActionByID(STT_CNTR_CMD_InfoView, TRUE);
// 
// 	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(m_pSttGbTreeView->m_pCurrSelRootNode->m_strstxmlFile);
// 
// 	if (pTestMacroUI == NULL)
// 	{
// 		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
// 		return;
// 	}
// 
// 	//��������
// 	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
// 	{
// 		ShowCharLib();
// 	}
// 	else
// 	{
// 		HideCharLib();
// 	}
// 
// 	ExpandRootNode();
// 	CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
}

void QSttTestCntrFrameLinux::InitIecCapTest(bool bActiveIecCap, bool bStartDetect,bool bShowMenuBtns)
{
	QSttTestCntrFrameBase::InitIecCapTest(bActiveIecCap, bStartDetect,bShowMenuBtns);

	if (bActiveIecCap)
	{
		InitToolBtnFocusPos(STT_CNTR_CMD_IecCap);
	}
/*
	UpdateButtonStateByID(STT_CNTR_CMD_Menu,false);
	UpdateButtonStateByID(STT_CNTR_CMD_AddMacro,false,false);
	UpdateButtonStateByID(STT_CNTR_CMD_TemplateView,false,false);
	UpdateButtonStateByID(STT_CNTR_CMD_ItemList,false,false);
	UpdateButtonStateByID(STT_CNTR_CMD_ReportView,false,false);
	UpdateButtonStateByID(STT_CNTR_CMD_ChRsMaps,false,false);
	AdjustToolBarButtons();
	OnCmd_IecCap();

	if (m_pSttIecRecordMainWidget != NULL)
	{
		m_pSttIecRecordMainWidget->StartDetect();
	}*/
}

void QSttTestCntrFrameLinux::InitRemoteCtrlTest(bool bActiveRemoteCtrl, bool bStart,bool bShowMenuBtns)
{
	QSttTestCntrFrameBase::InitRemoteCtrlTest(bActiveRemoteCtrl, bStart,bShowMenuBtns);

	if (bActiveRemoteCtrl)
	{
		InitToolBtnFocusPos(STT_ORG_MACRO_RemoteCtrlTest);
	}
}

long QSttTestCntrFrameLinux::OnItemStateChanged(CExBaseObject *pItem)
{
	//m_pSttGbTreeView->SetCurTestItem(pItem);
	((CSttItemBase *)pItem)->UpdateParentState();
	emit sig_OnItemStateChanged(pItem);
	QSttTestCntrFrameBase::OnItemStateChanged(pItem);
	return 0;
}

long QSttTestCntrFrameLinux::OnTestFinished()
{
	QSttTestCntrFrameBase::OnTestFinished();
	return 0;
}

long QSttTestCntrFrameLinux::OnTestStarted()
{
	QSttTestCntrFrameBase::OnTestStarted();
	return 0;
}

long QSttTestCntrFrameLinux::OnTestStoped()
{
	QSttTestCntrFrameBase::OnTestStoped();
	return 0;
}

void QSttTestCntrFrameLinux::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
{
	QSttTestCntrFrameBase::OnSearchPointReport(strMacroID,pSearchResults);
}


long QSttTestCntrFrameLinux::OnTestCreated()
{
	return 0;
}

void QSttTestCntrFrameLinux::OnReport(CExBaseObject *pItem) 
{
	CSttItemBase *pSttItem = (CSttItemBase*)pItem;
	CSttReports *pSttReports = pSttItem->GetSttReports();

	if (pSttReports == NULL)
	{
		return;
	}

	CSttReport *pReport = (CSttReport*)pSttReports->GetTail();

	if (pReport == NULL)
	{
		return;
	}

	//��ҳ������ʾ�������ݣ������ֶ�ģ��
	m_pMacroEditView->ShowReport(pReport->m_pValues);

	FillReport(pItem);

	if (m_pCharLibWidget != NULL)
	{
		m_pCharLibWidget->AddTestResultPoint(pReport->m_pValues);

 		CExBaseObject *pParent = (CExBaseObject*)pSttItem->GetParent();
 		//CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(pSttItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
 		UINT nClassID = pParent->GetClassID();
 
 		if (nClassID == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
 		{
 			CSttMacroCharItems *pCharItems = (CSttMacroCharItems *)pParent;

  			CString strBase64;
			CSttCharacteristic* pSttChar = (CSttCharacteristic*)pCharItems->FindByClassID(STTGBXMLCLASSID_CSTTCHARACTERISTIC);

			if (pSttChar != NULL)
			{
				//m_pSttCharacterDrawPng->GetSearchingPng(NULL, strBase64);
				CString strCharactPath,strParentItemsPath;
				strParentItemsPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
				strCharactPath = strParentItemsPath + _T("Img");
				emit sig_FillReportImg(strCharactPath.GetString());
				//m_pSttReportViewHtml->FillReportImg("", strCharactPath, strBase64);//zhouhj 20230213 ���ڲ���ͼƬ
			}
 		}
	}
}


//void QSttTestCntrFramBase::on_btnSetDatas_clicked()
//{
//	CString strFile;
//	strFile = _P_GetDBPath();
//	strFile += _T("paras/");
//	strFile += _T("ZeroTest.sttjs");

//	CFile oFile;
//	oFile.Open(strFile, CFile::modeRead);
//	long nLen = oFile.GetLength();
//	char *pszBuffer = new char [nLen + 1];
//	oFile.Read(pszBuffer, nLen);
//	pszBuffer[nLen] = 0;
//	CString strDataset = pszBuffer;

//	m_pParaEdit->SetDatas(strDataset);

//	delete pszBuffer;

//}

void QSttTestCntrFrameLinux::FillReport(CExBaseObject *pItem)
{
	CSttItemBase *pSttItem = (CSttItemBase*)pItem;
	CSttReports *pSttReports = pSttItem->GetSttReports();

	if (pSttReports == NULL)
	{
		return;
	}

	CSttReport *pReport = (CSttReport*)pSttReports->GetTail();

	if (pReport == NULL)
	{
		return;
	}

// 	CString strTmpPath;
// 	strTmpPath = _P_GetBinPath();
// 	strTmpPath += "report.xml";
// 	pReport->SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	CString strMacroID;
	strMacroID = _T("");

	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pItem;
		strMacroID = pSttMacroTest->m_strMacroID;
	}

	UpdateResultWidget(pReport,pSttItem->m_strName,strMacroID);//���½����ʾ����
	FillReport_OnlyHtmlRpt(pItem);
}

void QSttTestCntrFrameLinux::FillReport_OnlyHtmlRpt(CExBaseObject *pItem)
{
    //if (m_pSttReportViewHtml == NULL)
    //{
    //	return;
    //}

	CString strMacroID;
	CSttItemBase *pSttItem = (CSttItemBase*)pItem;
	CSttReports *pSttReports = pSttItem->GetSttReports();
	CString strItemID;

	if (pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pItem;
		strMacroID = pSttMacroTest->m_strMacroID;
	}
	strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	if (pSttReports == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("��ǰ������(%s)�²�������������.")*/g_sLangTxt_Native_ExcludingReportData.GetString(),strItemID.GetString());
		return;
	}

	CSttReport *pReport = (CSttReport*)pSttReports->GetTail();

	if (pReport == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("��ǰ������(%s)�°����ı�������Ϊ��.")*/g_sLangTxt_Native_ReportDataEmpty.GetString(),strItemID.GetString());
		return;
	}

	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	pNative->UpdateReportValuesByMacroTestDataType(pReport,strMacroID);//���ݱ����е����ݶ�������������ж�,���¶�Ӧ���ݵ�ֵ
//	pReport->SaveXmlFile(_T("D://111.xml"),CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	//��д����
	CString strParentItemsPath, strState,strBeforeTestString;
	strBeforeTestString.Format(_T("$%s$"),STT_ITEMS_ID_BEFORETEST);
	CExBaseObject *pParent = (CExBaseObject*)pItem->GetParent();
	strParentItemsPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	strItemID = pItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	strState = Gb_GetTestStateByID(pSttItem->m_nState);

	// 	if (strItemID.Find(strBeforeTestString.GetString())>0)//���Ա�����Ŀǰδ�в���ǰ׼�����ݵĸ���,�ʲ���ǰ׼���ӽڵ��µ����ݲ�����zhouhj20220326
	// 	{
	// 		return;
	// 	}

	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		if (strItemID.Find(_T("ReadSoeRlts")) >= 0)
		{
			((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->AddShowSoeReports(pReport->m_pRptDvmDataset);
		}
		else if (strItemID.Find(_T("ReadCount")) >= 0)
		{
			((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->UpdateDinCount(pReport->m_pValues,pReport->m_pRptDvmDataset,strItemID);
		}
	}
	if (!ModifyReport(pReport,strItemID))
	{
		return;
	}

	char *pszReport = NULL;
	pReport->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
	//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����·��(%s)."),strItemID.GetString());//zhouhj 20220317 �˴����Ӵ�ӡ��Ϣ.��ֹjs�ű��г�����ʱ,�������ݴ�ӡ��Ϣ�޷�����

	strState = _T("NORMAL");//20240205 suyang ��䱨��ʱ���Ͳ��ԣ�ǿ��ת��
	if(g_pTheSttTestApp->IsTestMacro_CurrVolChAsItem())
	{
        //m_pSttReportViewHtml->FillReportData("Table", strItemID, strState, pszReport);
	}
	else
	{
        //m_pSttReportViewHtml->FillReportData(strParentItemsPath, strItemID, strState, pszReport);

		if ((pReport->m_pRptDvmDataset != NULL)
			&&(pReport->m_pRptDvmDataset->GetCount()>0))//���ݼ����ݲ�Ϊ��ʱ,������ݼ�����
		{
            //m_pSttReportViewHtml->FillReportDataset(strParentItemsPath, strItemID, pReport->m_pRptDvmDataset);

// 			CString strTmp;
// 			strTmp = _P_GetBinPath();
// 			strTmp += _T("dsFillReportDataset.xml");
// 			pReport->m_pRptDvmDataset->SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�洢dsFillReportDataset���ݼ�(%s)���."),strTmp.GetString());
//			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("�������ݼ����(%s)(%s)."),strParentItemsPath.GetString(),strItemID.GetString());
		}
	}

	delete pszReport;
}


BOOL QSttTestCntrFrameLinux::ModifyReport( CSttReport *pReport,const CString &strItemID)
{
	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{	
		CSttMacroParaEditViewOriginal* pOriginalView  = ((CSttMacroParaEditViewOriginal*)m_pMacroEditView);
        //return pOriginalView->GetDatas_Reports(pReport,strItemID);
	}
	return TRUE;
}

void QSttTestCntrFrameLinux::UpdateRptHtml()
{
	QSttTestCntrFrameBase::UpdateRptHtml();

	if (!g_pTheSttTestApp->IsTestMacro_CurrVolChAsItem())
	{
		return;
	}

	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();

	if (strIDMacroUI.IsEmpty() || (strIDMacroUI == STT_MACRO_ID_StateTest))//״̬����,ģ������ʱ,���ٸ��±���,Ϊ��������ӦЧ��
	{
		return;
	}

	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	CExBaseList *pItems = (CExBaseList*)pNative->FindRootItemsByID(strIDMacroUI);

	if (pItems == NULL)
	{
		return;
	}

	CExBaseObject *pCurrObj = NULL;
	POS pos = pItems->GetHeadPosition();

	while(pos)
	{
		pCurrObj = pItems->GetNext(pos);

		if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			FillReport_OnlyHtmlRpt(pCurrObj);
		}
	}
}

void QSttTestCntrFrameLinux::FillReport()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return;
	}

	//������������
// 	FillReport_ForState();
// 	return;

	FillReports((CExBaseList*)m_pTestCtrlCntrBase->GetGuideBook());
}

void QSttTestCntrFrameLinux::FillReports(CExBaseList *pItems)
{
	if (pItems == NULL)
	{
		return;
	}

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pItems->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case STTGBXMLCLASSID_CSTTDEVICE:
		case STTGBXMLCLASSID_CSTTITEMS:
			FillReports((CExBaseList*)p);
			break;

		case STTGBXMLCLASSID_CSTTCOMMCMD:
		case STTGBXMLCLASSID_CSTTMACROTEST:
		case STTGBXMLCLASSID_CSTTSAFETY:
		case STTGBXMLCLASSID_CSTTSYSPARAEDIT:
			FillReport(p);
			break;
		}
	}
}

void QSttTestCntrFrameLinux::FillReport_ForState()
{
    //if (m_pSttReportViewHtml == NULL)
    //{
    //	return;
    //}

	CSttReports oSttReports;
	CString strFile;
	strFile = stt_ui_GetDebugFile("Debug_TestFillReport.xml");
	oSttReports.OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttReport *pReport = (CSttReport*)oSttReports.GetTail();

	if (pReport == NULL)
	{
		return;
	}

	char *pszReport = NULL;
	pReport->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
//	m_pSttReportViewHtml->FillReportData("Table", "StateTest$StateTest", "NORMAL", pszReport);

	delete pszReport;
}


void QSttTestCntrFrameLinux::paintEvent(QPaintEvent *event)
{
	if (SttFrame_Vert_Gap == 0)
	{
		return;
	}

	QPainter p(this);
	p.setPen(QColor(128, 128, 128)); //���û��ʼ���ɫ
	p.drawRect(m_rcWorkArea.left(), m_rcWorkArea.top(), m_rcWorkArea.width()-1, m_rcWorkArea.height()-1); //���Ʊ߿�
}

void QSttTestCntrFrameLinux::UpDateUdcVal()
{
#ifdef _PSX_QT_LINUX_
	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	
	if (pNative == NULL)
	{
		return;
	}
	
	CEventResult oCurrEventResult = pNative->m_oSttAtsClient.m_oCurrEventResult;

	if (oCurrEventResult.m_nUdc == 0)
	{
		if (g_oSystemParas.m_fAuxDC_Vol != 0)
		{
			g_oSystemParas.m_fAuxDC_Vol = 0;
		}
	}

#endif
}
