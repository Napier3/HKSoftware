#include "QSttCapIotEngineFrameBase.h"
#include "..\SttCmd\SttCmdDefineGlobal.h"
#include "..\..\61850\Module\SCL\SclFileMngr\SclFileMngrGlobal.h"
#include "..\..\61850\Module\61850ClientConfig\61850ClientCfgMngrGlobal.h"
#include "..\XLanguage\XLanguageMngr.h"
#include "..\TestMacro\TestMacroGlobal.h"
#include "..\..\AutoTest\Module\TestMacroRptTemplate\TestMacroRptTemplateGlobal.h"
#include "..\SttSystemConfig\SttSystemConfigGlobal.h"
#include "..\Controls\SafetyMsgCfg\SttSafetyMsgCfgGlobal.h"
#include "..\Config\MacroTestUI\SttMacroTestUI_TestMacroUIDB.h"
#include "..\SttSocket\SttCmdOverTimeMngr.h"
#include "..\KeyDb\KeyDbGlobal.h"
#include "..\..\61850\Module\GlobalDataMngr\IecGlobalDataMngrGlobal.h"
#include "..\..\61850\Module\GlobalDataMngr\IecGlobalDataMngr.h"
#include "..\FilterText\FilterTextGlobal.h"
#include "..\..\Protocol\Module\Engine\DeviceModel\DeviceModelXmlKeys.h"
#include "..\..\AutoTest\Module\Characteristic\CharacteristicGlobal.h"
#include "..\SmartCap\XSttCap_61850.h"
#include "..\SmartCap\61850Cap\ProtocolBase\Stt\SttRcdMemBufferMngr.h"
#include "..\SttTest\Common\tmt_adjust_sys_para_trans.h"
#include "..\..\61850\Module\XLanguageResourcePp_Mms.h"
#include "..\XMinidmp\XMinidmp.h"
#include "..\SmartCap\XSmartCapMngr.h"
#include "..\SttRcdBufferRcvMsg.h"
#include "..\SmartCap\SmartCapCtrl.h"
#include "..\..\IotAtsMngr\Module\PxEngineServer\IotPxEngineServer.h"
#include "..\Engine\PpEngineServerBase\SttPpEngineServer.h"
#include "..\ReplayTest\BigComtradeTransPlay.h"
#include "PpSttCapEngineServer.h"


CSttRcdBufferRcvMsg *g_pSttRcdSndRingBuf;
QSttCapIotEngineFrameBase *g_pSttCapIotEngineBase = NULL;
QSttCapIotEngineFrameBase::QSttCapIotEngineFrameBase(QWidget *parent)
: QMainWindow(parent)
{
	m_pXSttCap_61850 = NULL;
	m_pCapDevice92 = NULL;
	m_bConnected = FALSE;
	g_pSttCapIotEngineBase = this;
	connect(this, SIGNAL(sig_ClearPkgStc()), this, SLOT(slot_ClearPkgStc()));
	connect(this, SIGNAL(sig_StartClearPkgStc(int)), this, SLOT(slot_StartClearPkgStc(int)));
	connect(&m_oTimerClearPkgStc,SIGNAL(timeout()),this,SLOT(slot_ClearPkgStc()), Qt::QueuedConnection);
}
 
QSttCapIotEngineFrameBase::~QSttCapIotEngineFrameBase()
{
	if (g_theSmartCapCtrl)
	{
		ExitSttIecRecord();
	}
}

void QSttCapIotEngineFrameBase::InitTestApp(CXLanguageResourceBase *pLanguage/*=NULL*/)
{
	_P_InitSystemPath();
#ifndef _PSX_QT_LINUX_
	RunCrashHandler();
#endif

	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(pLanguage, TRUE);

	CXLanguageMngr::xlang_AddXLanguageRerouce(new CXLanguageResourcePp_Mms(), TRUE);

#ifndef NOT_USE_XLANGUAGE
	((CSttAdjSysParaDataTypes*)g_pSttAdjSysParaDataTypes)->InitAdjSysParaDataTypes();
#endif

	CFilterTextXmlRWKeys::Create();
	CIecGlobalDataMngrXmlRWKeys::Create();
	CIecGlobalDataMngr::Create();
	CSttSystemConfigXmlRWKeys::Create();
	CMacroXmlKeys::Create();
	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CTestDataTypeMngrConstGlobal::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CCfgDataMngrConstGlobal::Create();
	CDeviceModelXmlKeys::Create();
	CSttMacroTestUI_TestMacroUIDB::Create();
	CSttCmdOverTimeTool::Create();
	CSclFileMngrXmlRWKeys::Create();

	CCharacteristicXmlRWKeys::Create();
	CKeyDbXmlRWKeys::Create();
	CTestMacroXmlRWKeys::Create();
	CSttSafetyMsgCfgXmlRWKeys::Create();
	C61850ClientCfgMngrXmlRWKeys::Create();
	CTestMacroRptTemplateXmlRWKeys::Create();

#ifdef _use_g_theIotEngineApp_
	g_theIotEngineApp = new CPpSttIotEngineClientApp();
	g_theIotEngineApp->InitPpSttIotEngineClientApp();
#endif
}

void QSttCapIotEngineFrameBase::ExitTestApp()
{
	CTestMacroRptTemplateXmlRWKeys::Release();
	C61850ClientCfgMngrXmlRWKeys::Release();
	CSttSafetyMsgCfgXmlRWKeys::Release();
	CTestMacroXmlRWKeys::Release();
	CSclFileMngrXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CTestDataTypeMngrConstGlobal::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CMacroXmlKeys::Release();
	CDeviceModelXmlKeys::Release();
	CSttMacroTestUI_TestMacroUIDB::Release();
	CSttSystemConfigXmlRWKeys::Release();

	CXLanguageMngr::Release();
	CXLanguageXmlRWKeys::Release();
	CSttCmdOverTimeTool::Release();
	CKeyDbXmlRWKeys::Release();
	CCharacteristicXmlRWKeys::Release();
	CIecGlobalDataMngr::Release();
	CFilterTextXmlRWKeys::Release();
	CIecGlobalDataMngrXmlRWKeys::Release();

	if (g_theSmartCapCtrl != NULL)
	{
		ExitSttIecRecord();
	}

#ifdef _use_g_theIotEngineApp_

	if (g_theIotEngineApp)
	{
		g_theIotEngineApp->ExitPpSttIotEngineClientApp();
		delete g_theIotEngineApp;
		g_theIotEngineApp = NULL;
	}
#endif

}

void QSttCapIotEngineFrameBase::InitSttIecRecord(CSttTestAppCfg* pSttTestAppCfg)
{
	if (g_theSmartCapCtrl != NULL)
	{
		return;
	}

	CXSmartCapMngr::Create();

#ifdef _XSmartCap_use_SttRcdSocket_
	//使用动态分配的内存  2022-6-21  lijunqing
	CSttRcdMemBufferMngr *pSttRcdMemBufferMngr = new CSttRcdMemBufferMngr();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->CreateSttCap_61850(pSttTestAppCfg, pSttRcdMemBufferMngr);
	pXSttCap_61850->m_bUseSttTestEngineClientData = FALSE;
	g_pSttRcdSndRingBuf = pXSttCap_61850;
#else

	//2022-4-7  lijunqing 创建共性内存Server
	CRingMemBuf *pRingMemBuf = NULL;
#ifdef _PSX_QT_LINUX_
	CRingMemBufShm *pRingMemBufShm = new CRingMemBufShm();
	pRingMemBufShm->ShmCreateClient();
	pRingMemBuf = pRingMemBufShm;
#else
	CRingMemBufShmDebug *pRingMemBufShm = new CRingMemBufShmDebug();
	pRingMemBufShm->ShmCreateServer();
	pRingMemBufShm->ShmCreateClient();
	pRingMemBuf = pRingMemBufShm;
#endif

	CSttLocalRcdMemBufferMngrLinux *pNewRcdMemBufferMngr = new CSttLocalRcdMemBufferMngrLinux();
	pNewRcdMemBufferMngr->SetRingMemBuf(pRingMemBuf);
	pNewRcdMemBufferMngr->ResetBuffer();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->CreateSttCap_61850(pSttTestAppCfg, pNewRcdMemBufferMngr);
	pXSttCap_61850->m_bUseSttTestEngineClientData = FALSE;
	g_pSttRcdSndRingBuf = pRingMemBuf;

#endif

	CSmartCapCtrl::Create();
	g_theSmartCapCtrl->m_pXSttCap_61850 = pXSttCap_61850;
	g_theSmartCapCtrl->BeginSmartCapThread();
	pXSttCap_61850->m_pKeyDB = &m_oKeyDB;

}

void QSttCapIotEngineFrameBase::ExitSttIecRecord()
{
	CXSmartCapMngr::Release();
	CSmartCapCtrl::Release();
}

void QSttCapIotEngineFrameBase::InitKeyDB()
{
	m_oKeyDB.DeleteAll();
	m_oKeyDB.OpenKeyDbFile(_T("RelayTestKeyDb.xml"), TRUE);
}

void QSttCapIotEngineFrameBase::CreatSever()
{
	CString strIP = g_oSttTestAppCfg.GetLocalIP();
	CIotPxEngineServer::Create();
	CSttPpEngineServer::Create(const_cast<char*>(strIP.GetString()), 19821);
	CIotPxEngineServer::RegisterFactory(new CPpSttCapEngineServer);//创建服务端
}

void QSttCapIotEngineFrameBase::ExitServer()
{
	CSttPpEngineServer::Release();
	CIotPxEngineServer::Release();	
}

BOOL QSttCapIotEngineFrameBase::BeginIecRecord()
{
	long nSmpRate = 4000;

	InitKeyDB();
	InitSttIecRecord(&g_oSttTestAppCfg);
	m_pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	m_pXSttCap_61850->Reset();//清空设备
	g_oCapAnalysisConfig.m_nShowPrimaryValue = 0;

	CIecCfgDatasSmvIn *pIecCfgDatasSmvIn = m_oIecDatasMngr.GetSmvInMngr();
	CIecCfg92InData *pIecCfg92InData = (CIecCfg92InData*)pIecCfgDatasSmvIn->FindByClassID(CFGCLASSID_CIECCFG92INPUTDATA);
	if (pIecCfg92InData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("配置文件出错，请检查配置"));
	}
	else
	{
		m_pXSttCap_61850->AddCapDevice(pIecCfg92InData);//将Iec配置文件里的92In控制块关联上(CapDevice92)
		m_pCapDevice92 = (CCapDevice92*)g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.FindByClassID(CPDCLASSID_DEVICE92);
		m_pCapDevice92->m_bSelect = 1;
		m_pCapDevice92->m_strID = "dsSV1";
		m_pCapDevice92->m_dwAppID = pIecCfg92InData->m_dwAppID;
	}

	m_pXSttCap_61850->SetDvmDevice(&m_oDvmDevice);//将设备数据模型关联上


	g_theXSmartCapMngr->InitDvmDevice(m_pCapDevice92);
	m_pXSttCap_61850->RecordDevice(m_pCapDevice92);//将设备92添加到需要录波
	g_theXSmartCapMngr->IecAnalysis_AddDatasets();
	g_theXSmartCapMngr->m_pX61850Cap->BeginRecord();
	CIecCfgSysParas *pIecSysParas = m_oIecDatasMngr.GetSysParasMngr();
	m_pXSttCap_61850->SetPT_CT_Rates(pIecSysParas->GetPrimRatesIn());//更新变比
	m_pXSttCap_61850->UpdateCapDevicesRecordSmvChRates();//根据通道类型及CT、PT变比等更新系数
	m_pXSttCap_61850->InitCapDeviceRecordMngr_SmpRate(nSmpRate);
	g_theXSmartCapMngr->m_pX61850Cap->Init_SV_Channels();
	m_pXSttCap_61850->UpdateUI_Paras(TRUE);//将数据集中设置的加量的6U6I更新到结构体中

	g_bSmartCap_RecordNow = TRUE;//解析报文之前将是否录波设为真
	if (m_bConnected == FALSE)//连接录波通道前先进行判断，自动测试通过脚本启动sever的模式可能会在传第一帧报文的时候就启动连接录波
	{
		m_bConnected = m_pXSttCap_61850->CreateSttRcdSocket();//创建录波通道
	}
	if(m_bConnected)
	{
		m_pXSttCap_61850->CreateCapTrhead();//创建抓取报文的线程
		g_oCapAnalysisConfig.m_bMU_Test = true;
		g_oCapAnalysisConfig.m_bAnalysisData_DelayTime = true;//延时计算
		g_oCapAnalysisConfig.m_bAnalysisData_PhaseDelt = true;//角差计算
		g_oCapAnalysisConfig.m_bAnalysisData_Complex = true;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

void QSttCapIotEngineFrameBase::ExitIecRecord()
{
	
}

void QSttCapIotEngineFrameBase::SttOpen()
{
	CString strAppCfg = "";
	strAppCfg = _P_GetConfigPath();
	strAppCfg += "TestAppConfig.xml";
	g_oSttTestAppCfg.SttOpen(strAppCfg);
}

void QSttCapIotEngineFrameBase::InitIecCfg()
{
	CString strIecCfgFile = "";
	strIecCfgFile = _P_GetConfigPath();
	strIecCfgFile += "SttIecConfig.ixml";
	m_oIecDatasMngr.OpenIecCfgFile(strIecCfgFile);//读取Iec配置
}

void QSttCapIotEngineFrameBase::InitDevMods()
{
	CString strDvmFile = "";
	strDvmFile += _P_GetLibraryPath();
	strDvmFile += _T("SttIecRecordDetectDvm007.xml");
	bool bOpen = false;
	bOpen = m_oDvmDevice.OpenXmlFile(strDvmFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	if (bOpen)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("打开设备模型文件成功"));
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("打开设备模型文件失败"));
	}
}

void QSttCapIotEngineFrameBase::StartClearPkgStc(int nDelayTime)
{
	emit sig_StartClearPkgStc(nDelayTime);
}

void QSttCapIotEngineFrameBase::slot_ClearPkgStc()
{
	if (m_pCapDevice92)
	{
		m_pCapDevice92->ClearAnalysisResultErrors();
	}
	m_oTimerClearPkgStc.stop();
}

void QSttCapIotEngineFrameBase::slot_StartClearPkgStc(int nDelayTime)
{
	m_oTimerClearPkgStc.start(nDelayTime);
}
