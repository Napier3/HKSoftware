#include "SttMacroParaEditViewTransPlay.h"
#include "../SttTestCntrFrameAPI.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include <QApplication>
#ifdef _PSX_QT_LINUX_
#include"../../../../Module/OSInterface/QT/XGlobalDefine_QT.h"
#endif
#include "../Module/PopupDialog/SttFileMngrTool.h"
#include "../../XLangResource_Native.h"
#include <QFileDialog>

QSttMacroParaEditViewTransPlay* g_pReplayTestMain =NULL;

//数字量模块通道映射第几组
#define DIGITAL_CH_MAP_FRIST_GROUP		0		
#define DIGITAL_CH_MAP_SECOND_GROUP		1

BOOL FindInCStringArry(const CStringArray& strList, const CString & strName)
{
	long nIndex = 0;
	long nCount = strList.GetCount();
	BOOL bFind = FALSE;

	for (nIndex = 0; nIndex < nCount; nIndex++)
	{
		if (strName == strList.GetAt(nIndex))
		{
			return TRUE;
		}
	}

	return FALSE;
}

QSttMacroParaEditViewTransPlay::QSttMacroParaEditViewTransPlay(QWidget *parent)
    :CSttMacroParaEditViewOriginal(parent)
{
	RANGESTATEAXIS_BLOCK_HEIGHT1 = 20;
	RANGESTATEAXIS_BLOCK_HEIGHT2 = 10;
	RANGESTATEAXIS_BLOCK_WIDTHGAP = 15;
	CBigComtradeTransPlay::Create();
	g_pReplayTestMain = this;
	m_pWaveGraphWidget = NULL;
	m_pSttProgDlg = NULL;
	m_bRecoverWave =  false;

	m_pSttOpenComtradeFileThread = NULL;
	m_pSttInsertWaveThread = NULL;

	m_strParaFileTitle = g_sLangTxt_faultreplay;
	m_strParaFilePostfix = tr("project(*.rptxml)");
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("ReplayTest.rptxml");

	m_bReadComtradeFile = false; 
	m_oOutputType.init();


	if (!g_oSystemParas.m_nHasDigital && !g_oSystemParas.m_nHasAnalog)
	{
		g_oSystemParas.m_nHasAnalog = 1;
		// 	 	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前模块只支持模拟量故障回放,强制设置为模拟量输出模式.")*/g_sLangTxt_Native_EnfSetAnalog.GetString());
	}

// 	if (g_oSystemParas.m_nHasAnalog == 0)
// 	{
// 		g_oSystemParas.m_nHasAnalog = 1;
// 	}

	if (g_oSystemParas.m_nHasWeek)
	{
		g_oSystemParas.m_nHasWeek = 0;
// 	  	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前模块只支持模拟量故障回放,强制设置为模拟量输出模式.")*/g_sLangTxt_Native_EnfSetAnalog.GetString());
	}

	g_theBigComtradeTransPlay->SetSystemOutputType(g_oSystemParas.m_nHasAnalog,
		g_oSystemParas.m_nHasDigital, g_oSystemParas.m_nHasWeek);

	m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();
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
		m_pSttProgDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
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
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系

		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GenerateReplayConfigFromTMT(&m_oTmtReplayTest.m_oReplayParas,false);
		Updata_ChMapConfig();
	}

	CString strComtradePlayConfigName;
	strComtradePlayConfigName = m_oTmtReplayTest.m_oReplayParas.m_pszComtradeFilePath;

	if(m_ParaSetWidget)
	{
		m_ParaSetWidget->init(&g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind,this);
	}


	stt_Frame_ClearInfoWidget();
	//打开相应录波文件
	if(IsFileExist( strComtradePlayConfigName))
	{	
		StartProgDlg(g_sLangTxt_parsebar);
		m_strComtradeFilePath = strComtradePlayConfigName;
		m_oTmtReplayTest.m_oReplayParas.m_bInitChMapConfig = FALSE;

#ifdef _PSX_QT_LINUX_
		pthread_create(&m_pSttOpenComtradeFileThread,NULL,SttOpenComtradeFileThread,(LPVOID)this );
#else
		m_pSttOpenComtradeFileThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttOpenComtradeFileThread,(LPVOID)this,0,NULL);
#endif
	}

	CTickCount32 oTick;
	while(TRUE)
	{
		if(m_pSttOpenComtradeFileThread == NULL)
		{
			break;
		}
		oTick.DoEvents(5);
	}

     stt_Frame_ClearInfoWidget();
//	UpdateManualParas();
}

bool QSttMacroParaEditViewTransPlay::PrepStartTest()
{
	g_theBigComtradeTransPlay->CreateSttComtradeSocket();

	if(m_pSttOpenComtradeFileThread && !m_pSttProgDlg->isHidden())//正在解析波形文件
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("当前正在解析波形文件，无法开始测试，请等待解析完成再开始测试！"));
		return false;
	}
	if (!m_bReadComtradeFile)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,g_sLangTxt_starttest2.GetString());
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
			if(!HasFT3ChMap())
			{
				return FALSE;
			}
		}
		if(!VaildDigitalChMaxValue())
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

	if (!g_oSystemParas.m_nHasAnalog)
	{
		g_oSystemParas.m_nHasAnalog = 1;
		m_bSystemParasChanged = TRUE;
	}

	if (g_oSystemParas.m_nHasDigital)
	{
		g_oSystemParas.m_nHasDigital = 0;
		m_bSystemParasChanged = TRUE;
	}

	if (m_bSystemParasChanged)
	{
// 		stt_Frame_TestCtrlFrame()->OnUpdateTestResource(FALSE);
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
	m_oOutputType.nAnalogSel = g_oSystemParas.m_nHasAnalog;
	m_oOutputType.nDigtalSel = g_oSystemParas.m_nHasDigital;
	m_oOutputType.nWeekSel = g_oSystemParas.m_nHasWeek;

}

void QSttMacroParaEditViewTransPlay::OnViewTestStart()
{
	m_ParaSetWidget->startInit();
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();

	if (m_oTmtReplayTest.m_oReplayParas.m_nTripType == COMTRADE_TRIGGRE_TYPE_Manual)
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true);
	}
}

void QSttMacroParaEditViewTransPlay::OnViewTestStop()
{
	m_ParaSetWidget->stopInit();
	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget();
	stt_Frame_StopPowerWidget();

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

	if (m_oTmtReplayTest.m_oReplayParas.m_nTripType == COMTRADE_TRIGGRE_TYPE_Manual)
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger, false);
	}
}

QWidget* QSttMacroParaEditViewTransPlay::GetWaveWidget()
{
	return m_pWaveGraphWidget;
}

void QSttMacroParaEditViewTransPlay::CopyBinaryConfig( BOOL b)
{
	if(b)
	{
		stt_GetBinaryConfig()->m_nBinLogic = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
			stt_GetBinaryConfig()->m_binIn[i] = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[i];
		}
		for (int i=0;i<MAX_ExBINARY_COUNT;i++){

			stt_GetBinaryConfig()->m_binInEx[i] = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binInEx[i];
		}
	}
	else
	{

		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic = stt_GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){

			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[i] = stt_GetBinaryConfig()->m_binIn[i];
		}
		for (int i=0;i<MAX_ExBINARY_COUNT;i++){

			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binInEx[i] = stt_GetBinaryConfig()->m_binInEx[i];
		}
	}
}

void QSttMacroParaEditViewTransPlay::SwitchStateChanged()
{
	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
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
	m_oTmtReplayTest.m_oReplayParas.m_bInitChMapConfig = true;
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

bool QSttMacroParaEditViewTransPlay::HasFT3ChMap()
{
	CStringArray ChNameList;
	ChNameList.Add(_T("Ia1"));
	ChNameList.Add(_T("Ib1"));
	ChNameList.Add(_T("Ic1"));
	ChNameList.Add(_T("Ua1"));
	ChNameList.Add(_T("Ub1"));
	ChNameList.Add(_T("Uc1"));
	ChNameList.Add(_T("Ia2"));
	ChNameList.Add(_T("Ib2"));
	ChNameList.Add(_T("Ic2"));
	ChNameList.Add(_T("Ua2"));
	ChNameList.Add(_T("Ub2"));
	ChNameList.Add(_T("Uc2"));

	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgDatasSMV* pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfg6044CommonCh *pIecCfg6044CommonCh = NULL;
	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	CExBaseObject *pCurObj = NULL;

	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while (pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);
		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCurObj;

			if (pIecCfg6044CommonData->m_nUseFlag == 1)
			{
				POS pos1 = pIecCfg6044CommonData->m_pCfgChs->GetHeadPosition();
				while (pos1)
				{
					pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pIecCfg6044CommonData->m_pCfgChs->GetNext(pos1);
					if (FindInCStringArry(ChNameList, pIecCfg6044CommonCh->m_strAppChID))
					{
						return true;
					}
				}
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_RESULT, _T("IEC配置中FT3发送未映射电压电流通道!"));
	return false;

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

	if(!pReplay->m_oTmtReplayTest.m_oReplayParas.m_bInitChMapConfig)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GenerateReplayConfigFromTMT(&pReplay->m_oTmtReplayTest.m_oReplayParas, FALSE);
	}

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
	if(g_oSttTestResourceMngr.GetCurrModel().Find(_T("PNS330")) >= 0)
	{
	 	CLogPrint::LogString(XLOGLEVEL_TRACE,_T("当前PNS330只支持模拟量故障回放！"));
	 	g_oSystemParas.m_nHasDigital = 0;
	 	g_oSystemParas.m_nHasAnalog = 1;
	 	g_oSystemParas.m_nHasWeek = 0;
	}

	g_theBigComtradeTransPlay->SetSystemOutputType(g_oSystemParas.m_nHasAnalog,
		g_oSystemParas.m_nHasDigital, g_oSystemParas.m_nHasWeek);

	BOOL bOutputTypeChange = FALSE;
	if ((m_oOutputType.nAnalogSel != g_oSystemParas.m_nHasAnalog )||
		(m_oOutputType.nDigtalSel != g_oSystemParas.m_nHasDigital)||
		(m_oOutputType.nWeekSel != g_oSystemParas.m_nHasWeek))
	{
		bOutputTypeChange = TRUE;
	}

	if (bOutputTypeChange)
	{
	Updata_ChMapConfig();
		m_ParaSetWidget->init(&g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind, this);

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

		m_oOutputType.nAnalogSel = g_oSystemParas.m_nHasAnalog;
		m_oOutputType.nDigtalSel = g_oSystemParas.m_nHasDigital;
		m_oOutputType.nWeekSel = g_oSystemParas.m_nHasWeek;
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
	//StartProgDlg(_T("正在生成新的波形,请稍等...."));
	CString strProgTitle;
	strProgTitle = g_sLangTxt_ReplayTest_InsertWaveTip.GetString();
	StartProgDlg(strProgTitle);

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
	//strProgTitle = _T("波形正在复归，请稍等....");
	strProgTitle = g_sLangTxt_ReplayTest_RecoverWaveTip.GetString();
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

	// 	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetAnalogModuleCount() > 0) 
	// 	{
	// 		return true;
	// 	}

	return true;
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

	// 	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetDigitalModuleCount() > 0) 
	// 	{
	// 		return true;
	// 	}

	return true;
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

	// 	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.GetWeekModuleCount() > 0) 
	// 	{
	// 		return true;
	// 	}

	return true;
}


bool QSttMacroParaEditViewTransPlay::isNeedBinaryModule()
{
	if (g_theBigComtradeTransPlay == NULL)
	{
		return false;
	}

	if ((g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind.m_nUseBinaryModuleWidget == 1) &&
		(g_nBoutCount > 0))
	{
		return true;
	}

	return false;
}



int QSttMacroParaEditViewTransPlay::GetFT3MaxCodeValue(int nChannelGroupIndex, CSttModuleChComtradeBind *pCh)
{
	if (!pCh)
	{
		return -1;
	}
	int nMaxCode = -1;

	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgDatasSMV* pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgSmvRates* pIecCfgDatasSMVRates = pIecCfgDatasSMV->GetIecCfgSmvRates();

	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	int nCodeValue = 0;

	CStringArray ChNameList;
	CString strCodeName;

	if (nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
	{
		ChNameList.Add(_T("Ia1"));
		ChNameList.Add(_T("Ib1"));
		ChNameList.Add(_T("Ic1"));
		ChNameList.Add(_T("Ua1"));
		ChNameList.Add(_T("Ub1"));
		ChNameList.Add(_T("Uc1"));
		strCodeName = (pCh->IsModuleType_U()) ? _T("Uabcz") : _T("Iabc");
	}
	else
	{
		ChNameList.Add(_T("Ia2"));
		ChNameList.Add(_T("Ib2"));
		ChNameList.Add(_T("Ic2"));
		ChNameList.Add(_T("Ua2"));
		ChNameList.Add(_T("Ub2"));
		ChNameList.Add(_T("Uc2"));
		strCodeName = (pCh->IsModuleType_U()) ? _T("Up-abcz") : _T("Ip-abc");
	}


	CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate *)pIecCfgDatasSMVRates->FindByID(strCodeName);
	if (!pIecCfgSmvRate)
	{
		return -1;
	}

	CExBaseObject *pCurObj = NULL;

	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while (pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);
		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCurObj;
			if (pIecCfg6044CommonData->m_nUseFlag == 0)
			{
				continue;
			}

			POS pos1 = pIecCfg6044CommonData->m_pCfgChs->GetHeadPosition();
			while (pos1)
			{
				CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pIecCfg6044CommonData->m_pCfgChs->GetNext(pos1);

				if (!FindInCStringArry(ChNameList, pIecCfg6044CommonCh->m_strAppChID))
				{
					continue;
				}
				if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol && (pCh->IsModuleType_U()))
				{
					nCodeValue = pIecCfgSmvRate->m_nCodeValue;//保护码值
					nMaxCode = max(nCodeValue, nMaxCode);
				}
				else if (pCh->IsModuleType_I())
				{
					if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
					{
						nCodeValue = pIecCfgSmvRate->m_nMeasCurrCodeValue;//测量码值
						nMaxCode = max(nCodeValue, nMaxCode);
					}
					else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr || pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrProt)
					{
						nCodeValue = pIecCfgSmvRate->m_nCodeValue;//保护码值
						nMaxCode = max(nCodeValue, nMaxCode);
					}
				}
			}
		}
	}
	return nMaxCode;
}

bool QSttMacroParaEditViewTransPlay::CalDigitalChMaxValue(CSttModuleChComtradeBind *pCh, int nChannelGroupIndex)
{
	if (!pCh || nChannelGroupIndex < 0)
	{
		return false;
	}

	bool bRes = true;
	unsigned long nMaxValue = 0x0000;
	bool bIsUCh = pCh->IsModuleType_U() ? TRUE : FALSE;
	double fMax = pCh->CalcChannelMaxValue();

	CString strRateName, strPrimRate;
	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgDatasSMV *pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgSysParas *pIecCfgSysParas = pIecCfgDatasMngr->GetSysParasMngr();
	CIecCfgSmvRates *pIecCfgDatasSMVRates = pIecCfgDatasSMV->GetIecCfgSmvRates();
	CIecCfgPrimRates *pIecCfgPrimRates = (CIecCfgPrimRates *)pIecCfgSysParas->GetPrimRates();

	// 	if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_61850_92)
	// 	{	
	// 		if(nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
	// 		{	
	// 			strRateName = bIsUCh ? _T("Uabcz") : _T("Iabc");
	// 			strPrimRate = bIsUCh ? _T("U1-abc") : _T("I1-abc");
	// 		}
	// 		else
	// 		{
	// 			strRateName = bIsUCh ? _T("Up-abcz") : _T("Ip-abc");
	// 			strPrimRate = bIsUCh ? _T("U2-abc") : _T("I2-abc");
	// 		}
	// 		//比例因子
	// 		float fRate = pIecCfgDatasSMVRates->GetSmvRate(strRateName);
	// 
	// 		//一次值和二次值关系
	// 		CIecCfgPrimRate *pIecCfgPrimRate = (CIecCfgPrimRate *)pIecCfgPrimRates->FindByID(strPrimRate);
	// 		float fPrimValue = bIsUCh ? pIecCfgPrimRate->m_fPrimValue*1000 : pIecCfgPrimRate->m_fPrimValue;
	// 		float fSecondValue = pIecCfgPrimRate->m_fSecondValue;
	// 
	// 		//最大值
	// 		nMaxValue = fMax*(fPrimValue/fSecondValue)/fRate;
	// 
	// 		//9-2限制四个字节
	// 		unsigned long n92MaxValue = 0x7FFFFFFF;
	// 		if(nMaxValue > n92MaxValue)
	// 		{
	// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前9-2通道【%s】的实际输出值为【%x】,已超出最大输出值【%x】,请重新设置之后开始测试"),pCh->m_strName.GetString(),nMaxValue,n92MaxValue);
	// 			return false;
	// 		}
	// 
	// 	}
	// 	else if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
	if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
	{

		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("wuwuwu---当前格式：FT3"));

		if (nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
		{
			strRateName = bIsUCh ? _T("Uabcz") : _T("Iabc");
		}
		else
		{
			strRateName = bIsUCh ? _T("Up-abcz") : _T("Ip-abc");
		}

		//最小位宽
		int nMinSampLen = 3;
		POS pos = pIecCfgDatasSMV->GetHeadPosition();
		CExBaseObject *pCurObj = NULL;
		CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;

		while (pos)
		{
			pCurObj = pIecCfgDatasSMV->GetNext(pos);
			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
			{
				pIecCfg6044CommonData = (CIecCfg6044CommonData*)pCurObj;
				if (pIecCfg6044CommonData->m_nUseFlag == 1)
				{
					int nSmpDataLen = pIecCfg6044CommonData->m_nSmpDataLen;
					nMinSampLen = min(nSmpDataLen, nMinSampLen);
				}
			}
		}

		long n6044MaxValue = 0;
		switch (nMinSampLen)
		{
		case 1:
			n6044MaxValue = 0x7F;
			break;
		case 2:
			n6044MaxValue = 0x7FFF;
			break;
		default:
			n6044MaxValue = 0x7FFFFF;
			break;
		}

		CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate *)pIecCfgDatasSMVRates->FindByID(strRateName);
		float fRateValue = bIsUCh ? pIecCfgSmvRate->m_fPrimValue * 1000 : pIecCfgSmvRate->m_fPrimValue;//额定值
		int nMaxCodeValue = GetFT3MaxCodeValue(nChannelGroupIndex, pCh);//最大码值
		nMaxValue = fMax * nMaxCodeValue / fRateValue;//最大值

		if (nMaxValue > n6044MaxValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前FT3通道【%s】的实际输出值为【%x】,已超出最大输出值【%x】,请重新设置之后开始测试"), pCh->m_strName.GetString(), nMaxValue, n6044MaxValue);
			return false;
		}

	}
	else if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		if (nChannelGroupIndex == DIGITAL_CH_MAP_FRIST_GROUP)
		{
			strRateName = bIsUCh ? _T("Us-abcz") : _T("I5-abc");
		}
		else
		{
			strRateName = bIsUCh ? _T("Ut-abcz") : _T("I6-abc");
		}
		CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate *)pIecCfgDatasSMVRates->FindByID(strRateName);
		int nCodeValue = pIecCfgSmvRate->m_nCodeValue;//码值
		float fRateValue = bIsUCh ? pIecCfgSmvRate->m_fPrimValue * 1000 : pIecCfgSmvRate->m_fPrimValue;//额定值
		nMaxValue = fMax * nCodeValue / fRateValue;//最大值

		//柔直FT3限制
		int nMinSampLen = 3;
		POS pos = pIecCfgDatasSMV->GetHeadPosition();
		CExBaseObject *pCurObj = NULL;
		CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;

		while (pos)
		{
			pCurObj = pIecCfgDatasSMV->GetNext(pos);
			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
			{
				pIecCfg6044CommonData = (CIecCfg6044CommonData*)pCurObj;
				if (pIecCfg6044CommonData->m_nUseFlag == 1)
				{
					int nSmpDataLen = pIecCfg6044CommonData->m_nSmpDataLen;
					nMinSampLen = min(nSmpDataLen, nMinSampLen);
				}
			}
		}
		long n6044MaxValue = 0;
		switch (nMinSampLen)
		{
		case 1:
			n6044MaxValue = 0x7F;
			break;
		case 2:
			n6044MaxValue = 0x7FFF;
			break;
		default:
			n6044MaxValue = 0x7FFFFF;
			break;
		}

		if (nMaxValue > n6044MaxValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前柔直FT3通道【%s】的实际输出值为【%x】,已超出最大输出值【%x】,请重新设置之后开始测试"), pCh->m_strName.GetString(), nMaxValue, n6044MaxValue);
			return false;
		}
	}

	return bRes;
}

bool QSttMacroParaEditViewTransPlay::VaildDigitalChMaxValue(CSttModuleComtradeBind *pModule)
{
	if (!pModule)
	{
		return false;
	}

	CSttModuleChComtradeBind *pCh = NULL;
	POS pos = pModule->GetHeadPosition();
	int nChIndex = 0;

	while (pos)
	{
		pCh = (CSttModuleChComtradeBind *)pModule->GetNext(pos);
		if (pCh->IsChannelSelected())
		{
			int nGroupIndex = (nChIndex < 6) ? DIGITAL_CH_MAP_FRIST_GROUP : DIGITAL_CH_MAP_SECOND_GROUP;
			if (!CalDigitalChMaxValue(pCh, nGroupIndex))
			{
				return false;
			}
		}
		nChIndex++;
	}
	return true;
}

bool QSttMacroParaEditViewTransPlay::VaildDigitalChMaxValue()
{
	CSttModulesComtradeBind *pModulesComtradeBind = &g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oSttModulesComtradeBind;
	POS pos = pModulesComtradeBind->GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while (pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)pModulesComtradeBind->GetNext(pos);

		if (pModule->IsModuleSelected() && pModule->IsDigitalTypeModule())
		{
			if (!VaildDigitalChMaxValue(pModule))
			{
				return false;
			}
		}
	}

	return true;
}

