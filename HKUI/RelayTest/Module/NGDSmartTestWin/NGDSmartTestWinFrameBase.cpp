#include <QMessageBox>
#include <QString>
#include <QDateTime>
#include "NGDSmartTestWinFrameBase.h"
#include "..\SttTestAppConfig\SttTestAppCfg.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgDataMngrGlobal.h"
#include "..\SttTestBase\SttMacroXmlKeys.h"
#include "..\Log\LogPrint.h"
#include "..\DataMngr\DataMngrGlobal.h"
#include "..\SttSocket\SttCmdOverTimeMngr.h"
#include "..\SttCmd\SttCmdDefineGlobal.h"
#include "..\SmartCap\61850Cap\CapDevice\CapDevice92.h"
#include "..\..\61850\Module\SCL\SclIecCfgDatas.h"
#include "..\..\61850\Module\IecCfgSclTool\SclToIecCfgTool.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgDataBase.h"
#include "..\..\AutoTest\Module\GuideBook\GbXMLKeys.h"
#include "..\TestMacro\TestMacrosFileMngr.h"
#include "..\TestMacro\TestMacroGlobal.h"
#include "..\..\AutoTest\Module\GuideBook\ScriptText.h"
#include "..\..\AutoTest\Module\GuideBook\GbParaTypeMngr.h"
#include "..\XLanguage\XLanguageGlobal.h"
#include "..\XLanguage\XLanguageMngr.h"
#include "CString_QT.h"

extern CSttTestAppConfigTool g_oSttTestAppConfigTool;
extern CSttTestAppCfg g_oSttTestAppCfg;
NGDSmartTestWinFrameBase *g_NGDSmartTestWin = NULL;
NGDSmartTestWinFrameBase::NGDSmartTestWinFrameBase()
{
	InitResource();
	g_NGDSmartTestWin = this;
	m_bConnected = FALSE;
	m_bLoadSCDFile = FALSE;
	m_SelectCbsChanged = TRUE;
	m_nPage = 0;
	m_pXClientEngine = NULL;
	m_pSmartTestClient = NULL;
	m_pSelectIed = NULL;
	m_pIecCfgGinDatas = NULL;
	m_pIecCfgGinDatas = NULL;
	m_oX61850CapBase.SetDvmDevice(&m_oDvmDevice);
	InitKeyDB();
}

NGDSmartTestWinFrameBase::~NGDSmartTestWinFrameBase()
{
	g_NGDSmartTestWin = NULL;
	ReleaseResource();
	m_oSelectedSclCtrlsRef.RemoveAll();
}

long NGDSmartTestWinFrameBase::OnRtData(CSttParas *pParas)
{
	return 0;
}

void NGDSmartTestWinFrameBase::InitKeyDB()
{
	m_oKeyDB.DeleteAll();
	m_oKeyDB.OpenKeyDbFile(_T("RelayTestKeyDb.xml"), FALSE);
	m_oX61850CapBase.m_pKeyDB = &m_oKeyDB;
}

void NGDSmartTestWinFrameBase::InitGooseInOutData()
{
	ASSERT(m_oIecDatasMngr);
	m_pIecCfgGinDatas = m_oIecDatasMngr.GetGinMngr();
	m_pIecCfgGoutDatas = m_oIecDatasMngr.GetGoutMngr();
}

void NGDSmartTestWinFrameBase::UpdateRecordDevices()
{
	m_oRecordDevice.RemoveAll();
	CCapDeviceBase *pCapDeviceBase = NULL;
	POS pos = m_oX61850CapBase.m_oCapDeviceAll.GetHeadPosition();
	while (pos)
	{
		pCapDeviceBase = (CCapDeviceBase *)m_oX61850CapBase.m_oCapDeviceAll.GetNext(pos);
		if (pCapDeviceBase == NULL)
		{
			continue;
		}
		if (pCapDeviceBase->m_bSelect == TRUE)
		{
			m_oRecordDevice.AddTail(pCapDeviceBase);
			AttachDeviceChMapsBySCL(pCapDeviceBase);
		}
	}
}

void NGDSmartTestWinFrameBase::InitCtrlsByRecordDevs(CCapDeviceMngr *pRecordDevs)
{
	m_oSelectedSclCtrlsRef.RemoveAll();
	CCapDeviceBase *pCapDeviceBase = NULL;
	POS pos = pRecordDevs->GetHeadPosition();
	while (pos)
	{
		pCapDeviceBase = (CCapDeviceBase *)pRecordDevs->GetNext(pos);
		if (pCapDeviceBase != NULL)
		{
			CSclCtrlBase *pSclCtrlBase = m_oSclStation.FindCtrl_GsOutSmvOut(pCapDeviceBase->m_dwAppID, pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92);
			if (pSclCtrlBase == NULL)
			{
				return;
			}
			if (pSclCtrlBase->GetCount() == 0)
			{
				if (!m_oSclStation.OpenSiedFile((CSclIed*)pSclCtrlBase->GetAncestor(SCLIECCLASSID_IED)))
				{
					return ;
				}

				pSclCtrlBase = m_oSclStation.FindCtrl_GsOutSmvOut(pCapDeviceBase->m_dwAppID,pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92);

				if (pSclCtrlBase == NULL)
				{
					return ;
				}

				if (pSclCtrlBase->GetCount() == 0)
				{
					return ;
				}
			}
			if (pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICEGOOSE)
			{
 				AddGsInCtrlsFromGsOutCtrl((CSclCtrlGsOut*)pSclCtrlBase);
			}
			m_oSelectedSclCtrlsRef.AddTail(pSclCtrlBase);
		}
	}
}

void NGDSmartTestWinFrameBase::InitIecCfgs()
{
	m_oIecDatasMngr.InitCfgDataMngr();
	InitCtrlsByRecordDevs(&m_oRecordDevice);
	CSclToIecCfgTool oSclToIecCfgTool;
	oSclToIecCfgTool.AttacthSclFileRead(&m_oSclStation);
	oSclToIecCfgTool.AddToIecCfg_Mix(&m_oSelectedSclCtrlsRef, &m_oIecDatasMngr,FALSE);
	m_SelectCbsChanged = FALSE;
}

void NGDSmartTestWinFrameBase::InitDevMods()
{
	m_oX61850CapBase.InitDvmDevices();
//	m_oX61850CapBase.InitDvmDevices(&m_oIecDatasMngr);
}

BOOL NGDSmartTestWinFrameBase::AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase)
{
	if (pCapDeviceBase == NULL)
	{
		return FALSE;
	}
	CSclCtrlBase *pSclCtrlBase = m_oSclStation.FindCtrl_GsOutSmvOut(pCapDeviceBase->m_dwAppID,pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92);
	if (pSclCtrlBase == NULL)
	{
		return FALSE;
	}

	if (pSclCtrlBase->GetCount() == 0)
	{
		if (!m_oSclStation.OpenSiedFile((CSclIed*)pSclCtrlBase->GetAncestor(SCLIECCLASSID_IED)))
		{
			return FALSE;
		}

		pSclCtrlBase = m_oSclStation.FindCtrl_GsOutSmvOut(pCapDeviceBase->m_dwAppID,pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92);

		if (pSclCtrlBase == NULL)
		{
			return FALSE;
		}

		if (pSclCtrlBase->GetCount() == 0)
		{
			return FALSE;
		}
	}
	pSclCtrlBase->m_nFiberIndex = pCapDeviceBase->m_nFiberIndex;
	CSclToIecCfgTool oSclToIecCfgTool;
	oSclToIecCfgTool.AttacthSclFileRead(&m_oSclStation);
	CIecCfgDataBase* pIecCfgDataBase = oSclToIecCfgTool.AddCfgSmvInGin_By_SclSmvOutGout(pSclCtrlBase, &m_oIecDatasForDetectCbs,TRUE);
	pIecCfgDataBase->m_nFiberIndex = pCapDeviceBase->m_nFiberIndex;
	pIecCfgDataBase->m_nFiber2Index = pCapDeviceBase->m_nFiberIndex;
	CExBaseList oCurrList;
	long nCBIndex = 0;
	nCBIndex = m_oX61850CapBase.m_oCapDeviceAll.GetDeviceCount(pCapDeviceBase->GetClassID()) - 1;
	pIecCfgDataBase->SetAT02D_ChannelID(&oCurrList,nCBIndex);
	oCurrList.RemoveAll();
	pCapDeviceBase->AttachIecCfgData(pIecCfgDataBase);
	return TRUE;
}

void NGDSmartTestWinFrameBase::SendIecDetect(long bEnable)
{
	if (m_pXClientEngine == NULL)
	{
		return;
	}
	CDataGroup oGroup;
	oGroup.AddNewData(_T("Enable"), bEnable);
	m_pXClientEngine->Test_SetParameter(_T("IecDetect"), &oGroup);
}

void NGDSmartTestWinFrameBase::On_IecDetect(CDataGroup *pIecCb)
{
	CCapDeviceBase *pNew = m_oX61850CapBase.m_oCapDeviceAll.AddCapDevice(pIecCb);//此接口里会判断重复的控制块
	AttachDeviceChMapsBySCL(pNew);
}

BOOL NGDSmartTestWinFrameBase::connectTestApp(const CString &strIP,long nPort,const CString &strSoftID /*= STT_SOFT_ID_TEST*/)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, "正在连接测试仪......");
	g_oSttTestAppConfigTool.m_pSttTestMsgViewInterface = this;
	BOOL bRet = g_oSttTestAppConfigTool.Local_ConnectServer(&g_oSttTestAppCfg,strIP,nPort,strSoftID);

	if(bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "测试仪连接成功");

		g_oSttTestAppCfg.SetTestAppIP(strIP);
		g_oSttTestAppCfg.SetTestServerPort(nPort);

		g_oSttTestAppConfigTool.GetSttTestEngineClientData(&m_pXClientEngine);//联机成功后，从Tool中获取Client对象
		m_pXClientEngine->SetTestEventInterface(this);
		m_bConnected = TRUE;
		m_oTimerForHeartBeat.start(1000);
		SendIecDetect(1);
	}
	else
	{
		m_bConnected = FALSE;
		CLogPrint::LogString(XLOGLEVEL_ERROR, "连接测试仪失败，请检查网络链路是否连通，IP地址及端口配置是否正确；然后点击网络连接按钮重新连接");
	}

	return bRet;
}

void NGDSmartTestWinFrameBase::InitResource()
{
	_P_InitSystemPath();
	CMacroXmlKeys::Create();
	CString strAppCfg = "";
	strAppCfg = _P_GetConfigPath();
	strAppCfg += "TestAppConfig.xml";
	g_oSttTestAppCfg.SttOpen(strAppCfg);
	CCfgDataMngrXmlRWKeys::Create();
	CDataMngrXmlRWKeys::Create();
	CSttCmdOverTimeTool::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CGbParaTypeMngr::Create();
	CCfgDataMngrConstGlobal::Create();
	CGbXMLKeys::CreatetGbXMLkeys();
	CScriptTextMngrGlobalPool::Create();
	CTestMacroXmlRWKeys::Create();
	CTestMacrosFileMngr::Create(TRUE);
	CString strTestCfg = "";
	strTestCfg = _P_GetConfigPath();
	strTestCfg += "TestFunction.xml";
	m_oTestFuntions.OpenXmlFile(strTestCfg,CDataMngrXmlRWKeys::g_pXmlKeys);
}

void NGDSmartTestWinFrameBase::ReleaseResource()
{
	CCfgDataMngrXmlRWKeys::Release();
	CMacroXmlKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CSttCmdOverTimeTool::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
	CGbXMLKeys::Release();
	CTestMacrosFileMngr::Release();
	CTestMacroXmlRWKeys::Release();
	CScriptTextMngrGlobalPool::Release();
	CGbParaTypeMngr::Release();
	CXLanguageXmlRWKeys::Release();
	CXLanguageMngr::Release();
	if (m_pXClientEngine)
	{
		delete m_pXClientEngine;
		m_pXClientEngine = NULL;
	}
	if (m_pSmartTestClient)
	{
		m_pSmartTestClient->ExitXSmartTestClient();
		delete m_pSmartTestClient;
		m_pSmartTestClient = NULL;
	}
}

void NGDSmartTestWinFrameBase::InitForEntireyIntervalTest()
{
	m_nTestMode = TestMode_EntireyInterval;

	m_strPage[0] = Process_MainWidget;
	m_strPage[1] = Process_LoadSCD;
	m_strPage[2] = Process_MUDetect;
	m_strPage[3] = Process_GooseDetect;
	m_strPage[4] = Process_GooseInCfg;
	m_strPage[5] = Process_GooseOutCfg;
	m_strPage[6] = Process_ChooseDev;

}

void NGDSmartTestWinFrameBase::InitForProtectorTest()
{
	m_nTestMode = TestMode_Protector;

	m_strPage[0] = Process_MainWidget;
	m_strPage[1] = Process_LoadSCD;
	m_strPage[2] = Process_ChooseDev;
	m_strPage[3] = "";
	m_strPage[4] = "";
	m_strPage[5] = "";
	m_strPage[6] = "";
}

void NGDSmartTestWinFrameBase::InitForCollectExecuteUnitTest()
{
	m_nTestMode = TestMode_CollectExecuteUnit;

	m_strPage[0] = Process_MainWidget;
	m_strPage[1] = Process_LoadSCD;
	m_strPage[2] = Process_MUDetect;
	m_strPage[3] = Process_GooseDetect;
	m_strPage[4] = Process_GooseInCfg;
	m_strPage[5] = Process_GooseOutCfg;
	m_strPage[6] = "";
}

void NGDSmartTestWinFrameBase::ExportDvmModFile(CString strDvmModFilePath)
{
	m_oX61850CapBase.AddDataset_dsRcdStep6U6I();
	m_oX61850CapBase.AddDataset_dsTestFunSelect();
	m_oX61850CapBase.InitDvmDevices();
	if (strDvmModFilePath == _T(""))
	{
		strDvmModFilePath = _P_GetTemplatePath();
		strDvmModFilePath += _T("SttIecRecordDetectDvm.xml");
	}
	m_oX61850CapBase.m_pDvmDevice->SaveXmlFile(strDvmModFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void NGDSmartTestWinFrameBase::ExportIecCfgFile(CString strIecCfgFile)
{
	if (strIecCfgFile == _T(""))
	{
		strIecCfgFile = _P_GetTemplatePath();
		strIecCfgFile += _T("SttIecConfig.ixml");
	}
	m_oIecDatasMngr.SaveAsIecCfgFile(strIecCfgFile, FALSE);
}


void NGDSmartTestWinFrameBase::ReplaceIEDForSmartTest(CSclIed *pIed)
{
	if (pIed == NULL)
	{
		return;
	}
	CSclToIecCfgTool oSclToIecCfgTool;
	oSclToIecCfgTool.AttacthSclFileRead(&m_oSclStation);
	oSclToIecCfgTool.AddToIecCfg(pIed, &m_oIecDatasMngrForProtect);
	CX61850CapBase oX61850CapBase;
	oX61850CapBase.SetDvmDevice(&m_oDvmForProtect);
	oX61850CapBase.InitDvmDevices(&m_oIecDatasMngrForProtect);
 	CString strAEU;
	strAEU = _P_GetTemplatePath();
	strAEU += _T("AEUDevMod.xml");
 	m_oDvmForProtect.SaveXmlFile(strAEU, CDataMngrXmlRWKeys::g_pXmlKeys);
 	m_oGuideBook.Open(m_strSmartTestModFile);
	Gb_SetGbModifiedFlag(&m_oGuideBook,TRUE);
 
 	CDevice *pDevice = m_oGuideBook.GetDevice();
 	CCpus *pCpus = (CCpus *)pDevice->FindByID(_T("AEU"));
 
 	if (pCpus == NULL)
 	{
 		pCpus = (CCpus *)pDevice->GetHead();
 	}
 
  	CCpus oCpus;
  	oCpus.OpenModelFile(strAEU);
  	pCpus->DeleteAll();
  	pCpus->AppendEx(oCpus);
  	oCpus.RemoveAll();

	m_strGbRptFile = _P_GetWorkspacePath();
	//加个时间戳、相对路径；
	QDateTime oCurrentDateTime = QDateTime::currentDateTime();
	int nYear, nMonth, nDay, nTime;
	nTime = oCurrentDateTime.currentMSecsSinceEpoch();
	nYear = oCurrentDateTime.date().year();
	nMonth = oCurrentDateTime.date().month();
	nDay = oCurrentDateTime.date().day();
	m_strGbRptFile += GetSmartTestModFile();
	m_strGbRptFile.AppendFormat(_T("(_%d%d%d%d).gbrpt"), nYear, nMonth, nDay, nTime);

	CString strGBXmlFile = _P_GetWorkspacePath();
	strGBXmlFile += GetSmartTestModFile();
	strGBXmlFile += _T(".gbxml");
	m_oGuideBook.SaveXMLFile(strGBXmlFile);
 	m_oGuideBook.SaveBinaryFile(m_strGbRptFile);
}

void NGDSmartTestWinFrameBase::CreatAutoTest()
{
	if (IsProgramExist(_T("SmartTest.exe")))
	{
		return;
	}
	CString strPath;
	strPath = _P_GetBinPath();
	strPath += _T("SmartTest.exe");

	ExecuteFile(strPath, _T(""), _T("single"));
}

void NGDSmartTestWinFrameBase::OpenGbRptFile(const CString &strFilePath)
{
	if (m_pSmartTestClient == NULL)
	{
		m_pSmartTestClient = new CXSttAtsTestClientImp();
	}

	m_pSmartTestClient->m_pXSmartTestEventInterface = this;

	BOOL bRet = m_pSmartTestClient->InitXSmartTestClient(_T("127.0.0.1"));
	if (bRet)
	{
		m_pSmartTestClient->OpenGbrptFile(strFilePath, SmartTest_Run_Mode_Server);
	}
	else
	{
		QMessageBox::information(NULL, QString("提示"), QString("未能检测到自动测试程序，请确认自动测试已开启并重试"));
	}
}

void NGDSmartTestWinFrameBase::RemoveCapGooseDevice()
{
	CCapDeviceBase *pCapDeviceBase = NULL;
	POS pos = m_oX61850CapBase.m_oCapDeviceAll.GetHeadPosition();
	while (pos)
	{
		pCapDeviceBase = (CCapDeviceBase *)m_oX61850CapBase.m_oCapDeviceAll.GetNext(pos);
		if (pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{
			m_oX61850CapBase.m_oCapDeviceAll.Remove(pCapDeviceBase);
		}
	}
}

void NGDSmartTestWinFrameBase::RemoveCap92Device()
{
	CCapDeviceBase *pCapDeviceBase = NULL;
	POS pos = m_oX61850CapBase.m_oCapDeviceAll.GetHeadPosition();
	while (pos)
	{
		pCapDeviceBase = (CCapDeviceBase *)m_oX61850CapBase.m_oCapDeviceAll.GetNext(pos);
		if (pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92)
		{
			m_oX61850CapBase.m_oCapDeviceAll.Remove(pCapDeviceBase);
		}
	}
}

void NGDSmartTestWinFrameBase::AddGsInCtrlsFromGsOutCtrl(CSclCtrlGsOut  *pSclCtrlGsOut)
{
	POS posGsInCtrl = NULL;
	POS posGsInOld = NULL;
	CSclChGsOut *pSclChGsOut = NULL;
	CSclIed *pSclIed = NULL;
	CSclCtrlsGsOut *pCtrlsGsOut = (CSclCtrlsGsOut*)pSclCtrlGsOut->GetParent();
	pSclIed = (CSclIed*)pCtrlsGsOut->GetParent();
	CSclCtrlsGsIn *pSclCtrlsGsIn = NULL;
	CSclCtrlGsIn *pSclCtrlGsIn = NULL;
	 CSclCtrlGsIn *pSclCtrlGsInOld = NULL;
	BOOL beExist = FALSE;
	CSclChGsIn *pSclChGsIn = NULL;

	if (pSclIed->GetClassID() == SCLIECCLASSID_IED)
	{
		pSclCtrlsGsIn = pSclIed->GetGsIns();
		if (pSclCtrlsGsIn!=NULL)
		{
			posGsInCtrl = pSclCtrlsGsIn->GetHeadPosition();
			while(posGsInCtrl!=NULL)
			{
				pSclCtrlGsIn = (CSclCtrlGsIn*)pSclCtrlsGsIn->GetNext(posGsInCtrl);
				posGsInOld = m_oSelectedSclCtrlsRef.GetHeadPosition();
				beExist = FALSE;
				while(posGsInOld)
				{
					pSclCtrlGsInOld = (CSclCtrlGsIn*)m_oSelectedSclCtrlsRef.GetNext(posGsInOld);
					if (pSclCtrlGsInOld->m_strMac == pSclCtrlGsIn->m_strMac)
					{
						beExist = TRUE;
					}
				}
				if (beExist == FALSE)
				{
					m_oSelectedSclCtrlsRef.AddTail(pSclCtrlGsIn);
				}
			}
		}
	}
}

