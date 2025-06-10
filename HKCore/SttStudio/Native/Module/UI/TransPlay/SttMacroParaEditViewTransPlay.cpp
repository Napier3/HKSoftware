#include "SttMacroParaEditViewTransPlay.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include <QApplication>
#ifdef _PSX_QT_LINUX_
#include"../../Module/OSInterface/QT/XGlobalDefine_QT.h"
#endif
#include "../Module/PopupDialog/SttFileMngrTool.h"
#include "../../XLangResource_Native.h"

QSttMacroParaEditViewTransPlay* g_pReplayTestMain =NULL;

QSttMacroParaEditViewTransPlay::QSttMacroParaEditViewTransPlay(QWidget *parent, Qt::WindowFlags flags)
	:CSttMacroParaEditViewOriginal(parent,flags)
{
	RANGESTATEAXIS_BLOCK_HEIGHT1 = 20;
	RANGESTATEAXIS_BLOCK_HEIGHT2 = 10;
	RANGESTATEAXIS_BLOCK_WIDTHGAP = 15;
	CBigComtradeTransPlay::Create();
	g_pReplayTestMain = this;
	m_pWaveGraphWidget = NULL;
	m_pSttProgDlg = NULL;
	m_bRecoverWave =  false;

	m_strParaFileTitle = g_sLangTxt_faultreplay;
	m_strParaFilePostfix = tr("project(*.rptxml)");
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("ReplayTest.rptxml");

	m_bReadComtradeFile = false;
	m_pSttOpenComtradeFileThread = NULL;
	m_pSttInsertWaveThread = NULL;

	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	g_theTestCntrFrame->InitTestResource();
	OpenTestTestMngrFile(m_strDefaultParaFile);
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.GenerateReplayConfigFromTMT(&m_oTmtReplayTest.m_oReplayParas,false);
	Updata_ChMapConfig();
	initUI();

	SwitchStateChanged();

	m_ParaSetWidget->InitSttReplayTriggerWidget();
	m_ParaSetWidget->InitSttReplayWaveEditWidget();

	m_oProgTimer.start(500);
	initConnections();
	initData();
}

QSttMacroParaEditViewTransPlay::~QSttMacroParaEditViewTransPlay()
{
	if (m_pSttProgDlg != NULL)
	{
		delete m_pSttProgDlg;
		m_pSttProgDlg = NULL;
	}

	CBigComtradeTransPlay::Release();
}

void QSttMacroParaEditViewTransPlay::StartProgDlg(const CString &strTitle)
{
	if (m_pSttProgDlg == NULL)
	{
		m_pSttProgDlg = new QSttProgDlg(NULL);
		m_pSttProgDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
		m_pSttProgDlg->initUI(g_sLangTxt_downloaddata);
		m_pSttProgDlg->setModal(false);
 		 m_pSttProgDlg->move((this->width() - m_pSttProgDlg->width())/2,
 			 (this->height() - m_pSttProgDlg->height())/2);
	}

	m_pSttProgDlg->setWindowTitle(strTitle);
	m_pSttProgDlg->Start();
	m_pSttProgDlg->show();
	setEnabled(false);
}

void QSttMacroParaEditViewTransPlay::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewTransPlay::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(&m_oTmtReplayTest, &oRead);
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GenerateReplayConfigFromTMT(&m_oTmtReplayTest.m_oReplayParas,false);
		Updata_ChMapConfig();

	}

	g_theTestCntrFrame->ClearInfoWidget();
//	UpdateManualParas();
}

bool QSttMacroParaEditViewTransPlay::PrepStartTest()
{
	if(m_pSttOpenComtradeFileThread && !m_pSttProgDlg->isHidden())//正在解析波形文件
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("当前正在解析波形文件，无法开始测试，请等待解析完成再开始测试！"));
		return false;
	}
	if (!m_bReadComtradeFile)
	{
        CLogPrint::LogString(XLOGLEVEL_RESULT,g_sLangTxt_ReplayStarttest.GetString());
		return false;
	}

	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetTotalChs_SelectedModule()<=0)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,g_sLangTxt_playback.GetString());
		return false;
	}

	if(isNeedDigitalModule())
	{
		if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8 || g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
		{
			if(!g_theBigComtradeTransPlay->m_oComtradePlayConfig.HasFT3ChMap())
			{
				return FALSE;
			}
		}
		if(!g_theBigComtradeTransPlay->m_oComtradePlayConfig.VaildDigitalChMaxValue())
		{
			return FALSE;
		}
	}
	if(isNeedAnalogModule())
	{
	double fUMax,fIMax;
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetReplayChMaxValue(fUMax,fIMax,REPLAY_MODULE_TYPE_ANALOG);

	CString strMsg;

	double fAC_CurMax = g_oLocalSysPara.m_fAC_CurMax  * SQRT2;
	double fAC_VolMax = g_oLocalSysPara.m_fAC_VolMax  * SQRT2;

	if (fUMax>fAC_VolMax)
	{
		strMsg = g_sLangTxt_outputvoltage.arg(fUMax).arg(fAC_VolMax);
	//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电压通道回放的最大电压值(%lf),大于测试仪最大输出电压(%f)."),fUMax,g_oLocalSysPara.m_fAC_VolMax);
		CLogPrint::LogString(XLOGLEVEL_RESULT,strMsg);
		return false;
	}

	if (fIMax>fAC_CurMax)
	{
		strMsg = g_sLangTxt_outputcurrent.arg(fIMax).arg(fAC_CurMax);
	//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电流通道回放的最大电流值(%lf),大于测试仪最大输出电流(%f)."),fIMax,g_oLocalSysPara.m_fAC_CurMax);
		CLogPrint::LogString(XLOGLEVEL_RESULT,strMsg);
		return false;
	}
	}
	if(isNeedWeekModule())
	{
		if(!g_theBigComtradeTransPlay->m_oComtradePlayConfig.VaildWeekChMaxValue())
		{
			return FALSE;
		}
	}

	//防止editFinish事件未触发
	UpdateEditData();

	//开始测试下发参数之前将回放缓存准备好
	//CString strProgTitle;
	//strProgTitle = _T("波形数据下发进度条");
	StartProgDlg(g_sLangTxt_deliverybar);
	g_theBigComtradeTransPlay->OnStartTest();

// 	m_bSystemParasChanged = FALSE;

	//可使用数字量 2024--6-19 wuxinyi 保证故障回放输出，暂时放出
// 	if (!g_oSystemParas.m_nHasAnalog)
// 	{
// 		g_oSystemParas.m_nHasAnalog = 1;
// 		m_bSystemParasChanged = TRUE;
// 	}
// 
// 	if (g_oSystemParas.m_nHasDigital)
// 	{
// 		g_oSystemParas.m_nHasDigital = 0;
// 		m_bSystemParasChanged = TRUE;
// 	}

	if (m_bSystemParasChanged)
	{
		g_theTestCntrFrame->OnUpdateTestResource(FALSE);
	}

	return true;
}

void QSttMacroParaEditViewTransPlay::initUI()
{
	m_ParaSetWidget = new CSttReplayParaSetWidget(&g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind,this);

	m_pWaveGraphWidget = new QWaveGraphWidget();
	m_pWaveGraphWidget->setObjectName(QString::fromUtf8("QWaveGraphWidget"));
	m_ParaSetWidget->AddTabWidget(m_pWaveGraphWidget,g_sLangTxt_Faultcurve);

	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->addWidget(m_ParaSetWidget);
	setLayout(m_pMainLayout);	
	connect(&m_oProgTimer,SIGNAL(timeout()),this,SLOT(slot_Timer()));
}

void QSttMacroParaEditViewTransPlay::initConnections()
{
	connect(this,SIGNAL(sig_UpdateOpenComtradeFile(int)),this,SLOT(slot_UpdateOpenComtradeFile(int)),Qt::BlockingQueuedConnection);
}

void QSttMacroParaEditViewTransPlay::initData()
{
}

void QSttMacroParaEditViewTransPlay::OnViewTestStart()
{
	m_ParaSetWidget->startInit();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();

	if (m_oTmtReplayTest.m_oReplayParas.m_nTripType == COMTRADE_TRIGGRE_TYPE_Manual)
	{
		g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true);
	}
}

void QSttMacroParaEditViewTransPlay::OnViewTestStop()
{
	m_ParaSetWidget->stopInit();
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();

	if(g_theBigComtradeTransPlay->m_pSttComtradeFileReadThread != NULL)
	{
		g_theBigComtradeTransPlay->OnStopTest();
	}

	if (m_pSttProgDlg != NULL)
	{
		if (!m_pSttProgDlg->isHidden())
		{
			m_pSttProgDlg->Stop();
		}
	}
}

void QSttMacroParaEditViewTransPlay::CopyBinaryConfig( BOOL b)
{
	if(b)
	{
		g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i] = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[i];
		}
		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i] = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binInEx[i];
		}
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic = g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[i] = g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i];
		}
		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binInEx[i] = g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i];
		}
	}
}

void QSttMacroParaEditViewTransPlay::SwitchStateChanged()
{
	CopyBinaryConfig(TRUE);
	g_theTestCntrFrame->UpdateToolButtons();
}

void QSttMacroParaEditViewTransPlay::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
													 long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_ReplayTest *pTmtReplayTest = (tmt_ReplayTest *)pParas;

	if (/*m_bReadComtradeFile&&*/(stt_xml_serialize_is_write(pMacroParas)||stt_xml_serialize_is_register(pMacroParas)))
	{
		long nSampleFreq = (long)g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_dInsertFreq;
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GenerateReplayTestParas(((tmt_ReplayTest*)pParas)->m_oReplayParas,nSampleFreq);
	}

	stt_xml_serialize(&pTmtReplayTest->m_oReplayParas, pMacroParas, g_oSystemParas.m_nHasAnalog, g_oSystemParas.m_nHasDigital, g_oSystemParas.m_nHasWeek);
}

void QSttMacroParaEditViewTransPlay::OpenComtradeFile()
{
	CString strFileName;

	strFileName = g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_Comtrade);

#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
	// 	strPath = _P_GetLibraryPath();
	// 	strFileName = strPath+"Comtrade";
	astrPostfix<<"*.cfg";		
	QSttPopupOpenDialog oOpenDlg(strFileName,astrPostfix,this);
	oOpenDlg.InitUI();

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	if (!oOpenDlg.GetFilePath(strFileName))
	{
		return;
	}
	
// 	QTextCodec *pOldTextCodec = NULL;//不应该在此处增加处理
// 	InitLocalCodec_BeforeReadWrite(strFileName,&pOldTextCodec);//将编码变为utf-8
#else
	strFileName = QFileDialog::getOpenFileName(this,g_sLangTxt_Open,
		_P_GetBinPath(),g_sLangTxt_cfgFile);
#endif

	if (strFileName.IsEmpty())
	{
		return;
	}

	m_strComtradeFilePath = strFileName;
#ifdef _PSX_QT_LINUX_
    pthread_create(&m_pSttOpenComtradeFileThread,NULL,SttOpenComtradeFileThread,(LPVOID)this );
#else
	m_pSttOpenComtradeFileThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttOpenComtradeFileThread,(LPVOID)this,0,NULL);
#endif
	CString strProgTitle;
	//strProgTitle = _T("波形文件解析进度条");
	StartProgDlg(g_sLangTxt_parsebar);
//	OpenComtradeFile(strFileName,TRUE);

#ifdef _PSX_QT_LINUX_
	CTickCount32 oTick;
	while(TRUE)
	{
		if(m_pSttOpenComtradeFileThread == NULL)
		{
			break;
		}
		oTick.DoEvents(5);
	}
//	ResetLocalCodec(pOldTextCodec);
	system("sync");//20220616 写文件后需要同步
#endif


}

// BOOL QSttMacroParaEditViewTransPlay::OpenComtradeFile(const CString &strComtradeFile,BOOL bInitDefault)
// {
// 	StartProgDlg();
// 
// 	m_strComtradeFilePath = strComtradeFile;
// #ifdef _PSX_QT_LINUX_
// 	pthread_create(&m_pSttOpenComtradeFileThread,NULL,SttOpenComtradeFileThread,(LPVOID)this );
// #else
// 	m_pSttOpenComtradeFileThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttOpenComtradeFileThread,(LPVOID)this,0,NULL);
// #endif	
// 	return TRUE;
// }

#ifdef _PSX_QT_LINUX_
void* QSttMacroParaEditViewTransPlay::SttOpenComtradeFileThread(LPVOID pParam)
#else
UINT QSttMacroParaEditViewTransPlay::SttOpenComtradeFileThread(LPVOID pParam)
#endif
{
	QSttMacroParaEditViewTransPlay *pReplay = (QSttMacroParaEditViewTransPlay*)pParam;

	bool bInitDefault = true;
	if(pReplay->m_bRecoverWave)
	{
		bInitDefault = false;
	}
	int bRet = g_theBigComtradeTransPlay->OnOpenComtradeFile(pReplay->m_strComtradeFilePath,bInitDefault);
	emit pReplay->sig_UpdateOpenComtradeFile(bRet);
	pReplay->m_pSttOpenComtradeFileThread = NULL;
	pReplay->m_bRecoverWave = false;
//	pReplay->UpdateComtradeFile(bRet);
	// 	CTickCount32 oTickCount;
	// 	oTickCount.DoEvents(100);
#ifndef _PSX_QT_LINUX_
	return 0;
#endif
}

void QSttMacroParaEditViewTransPlay::slot_UpdateOpenComtradeFile(int bRet)
{
	setEnabled(true);
	m_pSttProgDlg->Stop();
 	CString strMsg;

 	if (bRet)
 	{//解析文件成功，刷新界面
		strMsg = g_sLangTxt_recordfile  + m_strComtradeFilePath +g_sLangTxt_Win;
		CLogPrint::LogString(XLOGLEVEL_RESULT,strMsg);
// 		m_strComtradeFilePath = strComtradeFile;
 		m_bReadComtradeFile = true; 
 		m_ParaSetWidget->InitModuleChList();
 		m_ParaSetWidget->InitSttReplayTriggerWidget();
		m_ParaSetWidget->InitSttReplayWaveEditWidget();
		m_ParaSetWidget->InitBinaryModuleChList();

 		m_ParaSetWidget->initTabPage();
 
 		//重新计算最大值，并刷新所有模块
 		g_theBigComtradeTransPlay->m_oComtradePlayConfig.CalcReplayChMaxValue();
		m_ParaSetWidget->UpdateUIMax();
		m_pWaveGraphWidget->InitWaveGraph();
		CreateWaveGraphByComtrade();
 	}
	else
	{
		strMsg = g_sLangTxt_recordfile  + m_strComtradeFilePath + g_sLangTxt_Lose;
		CLogPrint::LogString(XLOGLEVEL_RESULT,strMsg);
	}
}

void QSttMacroParaEditViewTransPlay::slot_ModuleChChanged(int nModuleIndex,int nChIndex)
{
	m_ParaSetWidget->UpdateUIMax();
	emit sig_UpdateDrawWaveGraph();
	//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("slot_ModuleChChanged(nModuleIndex=%d,nChIndex=%d)"),nModuleIndex,nChIndex);
}

void QSttMacroParaEditViewTransPlay::slot_ModuleChRangeChanged()
{
	CreateWaveGraphByComtrade();
}

void QSttMacroParaEditViewTransPlay::CreateWaveGraphByComtrade()
{
	if (m_pWaveGraphWidget == NULL)
	{
		return;
	}

	disconnect(this, SIGNAL(sig_UpdateDrawWaveGraph()), m_pWaveGraphWidget, SLOT(slot_UpdateDrawWaveGraph()));
	disconnect(m_pWaveGraphWidget, SIGNAL(sig_UpdateTwoCursorTimeValues(double,double)), m_ParaSetWidget, SLOT(slot_UpdateTwoCursorTimeValues(double,double)));
	m_pWaveGraphWidget->CreateRecordDrawByComtrade();
	connect(this, SIGNAL(sig_UpdateDrawWaveGraph()), m_pWaveGraphWidget, SLOT(slot_UpdateDrawWaveGraph()),Qt::QueuedConnection);
	connect(m_pWaveGraphWidget, SIGNAL(sig_UpdateTwoCursorTimeValues(double,double)),m_ParaSetWidget, SLOT(slot_UpdateTwoCursorTimeValues(double,double)),Qt::QueuedConnection);
	m_pWaveGraphWidget->SendUpdateTwoCursorTimeValues(FALSE);
}

void QSttMacroParaEditViewTransPlay::UpdateEditData()
{
	m_ParaSetWidget->UpdateEditData();
}

void QSttMacroParaEditViewTransPlay::Updata_ChMapConfig()
{
	if (!g_oSttTestResourceMngr.HasLoadDevice())
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_hardwarefile .GetString());
		return;
	}

	long nTotalModuleIndex = 1;

	CSttModulesComtradeBind *pSttModulesComtradeBind = &g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind;
	pSttModulesComtradeBind->InitBySttAdjDevice(&g_oSttTestResourceMngr.m_oCurrDevice);

	if (m_bReadComtradeFile)
	{
		g_theBigComtradeTransPlay->m_oBigComtradeFileRead.InitChMapConfig();
	}
}

void QSttMacroParaEditViewTransPlay::UpdateTestResource(BOOL bCreateChMaps)
{
	//g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.InitAllMoudleCount();//初始化模块数量

	Updata_ChMapConfig();
	m_ParaSetWidget->init(&g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind,this);

	if (m_bReadComtradeFile && IsFileExist(m_strComtradeFilePath))//如果已经加载了波形文件
	{
		g_theBigComtradeTransPlay->m_oBigComtradeFileRead.BeginGenerateComtradeBuf();

		m_ParaSetWidget->InitModuleChList();
		m_ParaSetWidget->InitSttReplayTriggerWidget();
		m_ParaSetWidget->InitSttReplayWaveEditWidget();
		m_ParaSetWidget->initTabPage();
		m_ParaSetWidget->UpdateUIMax();

		//重新计算最大值，并刷新所有模块
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.CalcReplayChMaxValue();
		m_pWaveGraphWidget->InitWaveGraph();
		CreateWaveGraphByComtrade();
	}
}

void QSttMacroParaEditViewTransPlay::slot_Timer()
{
	if ((g_theBigComtradeTransPlay->m_pSttComtradeFileReadThread == NULL)&&(m_pSttOpenComtradeFileThread == NULL)
		&&(m_pSttProgDlg != NULL)&&(m_pSttInsertWaveThread == NULL))
	{
		if (!m_pSttProgDlg->isHidden())
		{
			m_pSttProgDlg->Stop();
			setEnabled(true);
		}
	}
}

void QSttMacroParaEditViewTransPlay::StartInsertWaveThread()
{
#ifdef _PSX_QT_LINUX_
	pthread_create(&m_pSttInsertWaveThread,NULL,SttInsertWaveThread,(LPVOID)this );
#else
	m_pSttInsertWaveThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttInsertWaveThread,(LPVOID)this,0,NULL);
#endif
	StartProgDlg(_T("正在生成新的波形,请稍等...."));
}

#ifdef _PSX_QT_LINUX_
void* QSttMacroParaEditViewTransPlay::SttInsertWaveThread(LPVOID pParam)
#else
UINT QSttMacroParaEditViewTransPlay::SttInsertWaveThread( LPVOID pParam )
#endif
{
	QSttMacroParaEditViewTransPlay *pReplay = (QSttMacroParaEditViewTransPlay*)pParam;

	int nType = pReplay->m_ParaSetWidget->GetWaveEditType();

	if(nType == REPLAYTEST_INSERT_TYPE_RAW)
	{
		long nCycNum = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nCycleIndex;
		//时间
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_nInsertWaveType == INSERT_WAVE_TYPE_TIME)
		{
			double dBegin = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin;
			double dEnd = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd;

			g_theBigComtradeTransPlay->m_oBigComtradeFileRead.InsertCyclePointsByRelTime(dBegin, dEnd,dEnd, nCycNum);//插入原始波形

		}
		else//点号
		{
			long nBegin = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nBeginPoint;
			long nEnd = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nEndPoint;
			g_theBigComtradeTransPlay->m_oBigComtradeFileRead.InsertCyclePointsByPoint(nBegin, nEnd,nEnd, nCycNum);
		}
	}
	else if(nType == REPLAYTEST_INSERT_TYPE_NORMAL)
	{
		double dVal = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fVoltage;
		double dCur = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fCurrent;
		double dOutTime = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_dOutputTime;
		double RatioV = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[1]/g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[0];
		double RatioI = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[1]/g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[0];

		g_theBigComtradeTransPlay->m_oBigComtradeFileRead.InsertNormalCyclePoints(dVal * RatioV,dCur* RatioI,dOutTime);//插入常态波形
	}
	pReplay->m_pSttInsertWaveThread = NULL;

#ifndef _PSX_QT_LINUX_
	return 0;
#endif
}

void QSttMacroParaEditViewTransPlay::ReCoveryWave()
{
	m_bRecoverWave = true;
#ifdef _PSX_QT_LINUX_
	pthread_create(&m_pSttOpenComtradeFileThread,NULL,SttOpenComtradeFileThread,(LPVOID)this );
#else
	m_pSttOpenComtradeFileThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttOpenComtradeFileThread,(LPVOID)this,0,NULL);
#endif
	CString strProgTitle;
	strProgTitle = _T("波形正在复归，请稍等....");
	StartProgDlg(strProgTitle);
}

bool QSttMacroParaEditViewTransPlay::isNeedAnalogModule()
{
	if (!g_oSystemParas.m_nHasAnalog)
	{
		return false;
	}

	if (g_theBigComtradeTransPlay == NULL)
	{
		return false;
	}

	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetAnalogModuleCount() > 0) 
	{
		return true;
	}

	return false;
}

bool QSttMacroParaEditViewTransPlay::isNeedDigitalModule()
{
	if (!g_oSystemParas.m_nHasDigital)
	{
		return false;
	}

	if (g_theBigComtradeTransPlay == NULL)
	{
		return false;
	}

	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetDigitalModuleCount() > 0) 
	{
		return true;
	}

	return false;
}


bool QSttMacroParaEditViewTransPlay::isNeedWeekModule()
{
	if (!g_oSystemParas.m_nHasWeek)
	{
		return false;
	}

	if (g_theBigComtradeTransPlay == NULL)
	{
		return false;
	}

	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetWeekModuleCount() > 0) 
	{
		return true;
	}

	return false;
}


bool QSttMacroParaEditViewTransPlay::isNeedBinaryModule()
{
	if (g_theBigComtradeTransPlay == NULL)
	{
		return false;
	}

	if ((g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.m_nUseBinaryModuleWidget == 1)&&
		(g_nBoutCount > 0)) 
	{
		return true;
	}

	return false;
}



