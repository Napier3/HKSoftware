#include "stdafx.h"
#include "TestControlBase.h"
#include "../GuideBook/Script/GbScript_GlobalDefine.h"
#include <math.h>
#include "../../Module/DataMngr/DvmDatasetSort.h"
#include "../GuideBook/GuideBookDefine.h"

#include "../XLanguageResourceAts.h"
#include "../GuideBook/GuideBookTool.h"
#include "../GuideBook/GbUnqualifiedItemTool.h"
#include "../TCtrlCntrConfig.h"
#include "SmartTestBaseApp.h"
#include "../TCtrlCntrWorkSpace.h"
#include "../SmartTestRpcEventApi.h"
#include "../GuideBook/ReportMap/JsonReport/JsonRptFill.h"

#ifndef _PSX_QT_LINUX_
#include "..\..\..\Module\API\MemClean.h"
#include "TestControlWnd_Win.h"
#else
#include "TestControlWnd_Linux.h"
#endif

#ifndef _PSX_QT_LINUX_
#include "../GuideBook/ReportMap/SystemReport/SystemRptFill.h"
#include "../GuideBook/ReportMap/WordReport/WordRptFill.h"
#include "../GuideBook/ReportMap/WPSReport/WPSRptFill.h"
#include "../GuideBook/ReportMap/WPSRptExport.h"
#include "../GuideBook/ReportMap/WordRptExport.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _debug_log_device_ex
#define ENCRYPT_TEST_TIMELONG  600000

#ifdef GUIDEBOOK_DEV_MODE
CStringTokenizer CTestControlBase::m_oStringTokenizer;
#endif

extern CString g_strReportFillProgID;// = REPORTFILL_PROGID_WORD;
BOOL g_bInXTestDbGenReprtState = FALSE;
CAutoCriticSection CTestControlBase::m_oTestCriticSection; //测试执行的互斥量

CDataGroup g_oWordReportExGroup;


//2022-11-2  LIJUNQING  合并单元修改，没考虑详细，恢复
//后续在测试命令中增加选项：结果数据存入dataset
//#define CMD_REPORT_ADD_TO_DATASET

CTestControlBase::CTestControlBase()
{
	m_pMacroTestInterface = NULL;
	m_bSingleTestControl = TRUE;
	m_bCanRunCommCmdFinalResultScript = FALSE;
	//m_pTestProject = NULL;
	m_nCurrProjectIndex = 0;
	m_nCurrTestItemIndex = 0;
	m_nTestItemIndexBkForAllInlegible = -1;
	m_pItemContainer = NULL;
	m_pParentWnd = NULL;

	m_pCurrTestItem = NULL;
	m_pCurrSubTestItem = NULL;

#ifndef GUIDEBOOK_DEV_MODE
	m_pGuideBook = new CGuideBook();
	m_pGuideBook->SetParent(this);
#endif

	m_pReportFill = NULL;

	m_nCommCmdTestTimes = 0;
	m_nMacroTestTimes = 0;
	InitEquation();

	//m_bPpDeviceConnectSucc = 0;
	m_nHasTestItemCount = 0;
	m_nStopTestByError = 0;
	m_nCommCmdCurrDeviceIndex = 0;

	m_oTickCount32.Enter();
	m_nMacroTestReTestTimes = 0;
	m_nBreakItemsLevel = -1;
	m_bSafetyScriptStopByRecord = FALSE;
	m_bExecCommCmdTdelayBefore = TRUE;

	m_pItemsRsltExprScript = NULL;
	m_nItemsRsltExprScriptIndex = 0;
	m_nItemsRsltExprScriptTimerLong = 0;
	m_nItemsRsltExprScriptMaxRead = -1;
	m_nItemsRsltExprScriptTimeIgnore = 0;
	m_pCurrReport = NULL;
	m_pTestProjectRef = NULL;
	m_bUseBinaryOffset = FALSE;
	m_nBinRngBegin = 0;
	m_nBinRngEnd = 65535;

	m_pReportFill = NULL;
	m_bMacroTestFinished = FALSE;
	m_pTCtrlWnd = NULL;
}

void CTestControlBase::InitGuideBook()
{
	m_pItemContainer = (CItemContainer*)m_pGuideBook->GetItemContainer();

	if (m_pGuideBook->m_nIndex != 0)
	{
		return;
	}

	m_pGuideBook->InitGuideBook();
}

void CTestControlBase::CreateTestControlWnd(CTestControlWnd *pWndRef)
{
	if (pWndRef == NULL)
	{
		if (m_pTCtrlWnd != NULL)
		{
			if (GetParent() != NULL && m_bTestControlWndRef == TRUE)
			{
				//子TestControl，已经绑定主TestControl的窗口。此处不能删除主TestControl的窗口
				//shaolei 2024-3-21
				return;
			}

			if(m_pTCtrlWnd != NULL)
			{
				m_pTCtrlWnd->DestroyWindow();
				delete m_pTCtrlWnd;
			}
		}

#ifndef _PSX_QT_LINUX_
		m_pTCtrlWnd = new CTestControlWnd_Win();
#else
		m_pTCtrlWnd = new CTestControlWnd_Linux();
#endif

		m_pTCtrlWnd->CreateTestControlWnd();
		m_pTCtrlWnd->m_pTestControl = this;
		m_bTestControlWndRef = FALSE;
	}
	else
	{
		m_pTCtrlWnd = pWndRef;
		m_bTestControlWndRef = TRUE;
	}
}

long ats_ReadFrom(CExBaseList *pDvmDataObj, const CString &strFile)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.ResetVersion();

	if ( ! oBuffer.OpenFromFile(strFile) )
	{
		return 0;
	}

	oBuffer.SetCharSet(CHAR_SET_ASCII);
	dvm_InitDvmVersion(oBuffer);
	oBuffer.SetReadMode();
	oBuffer.ReadVersion();
	oBuffer.SetVersionFind(g_dwDataMngrCurrVersion);

	try
	{
		pDvmDataObj->Serialize(oBuffer);
	}
	catch (...)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG
            , g_sLangTxt_FileRightError.GetString()/*_T("文件【%s】版本错误！")*/, strFile.GetString());

		return 0;
	}

	return 1;
}

void CTestControlBase::InitEquation()
{
	
}

long CTestControlBase::CreateReportFill(const CString &strRptProgID, BOOL bExportWord)
{
#ifndef _PSX_QT_LINUX_
	//打开报告文件
	CString strWordFile = GetReportFilePath();

	if (!IsFileExist(strWordFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] error!"), strWordFile);
		return 0;
	}

	if (m_pReportFill != NULL)
	{
		return 0;
	}

	if (TCC_IsDebugWithoutReport())
	{	
		m_pReportFill = new CSystemRptFill();
	}
	else
	{
		if (strRptProgID.CompareNoCase(REPORTFILL_PROGID_WORD) == 0)
		{
			if (bExportWord)
			{
				g_theSmartTestBaseApp->CreateApp(CRptFillWordApp::New);
				m_pReportFill = new CWordRptFill();
			}
			else
			{
				g_theSmartTestBaseApp->CreateApp(CRptFillWordApp::New);
				m_pReportFill = new CWordRptFill();
			}
		}
		else if (!strRptProgID.CompareNoCase(REPORTFILL_PROGID_WPS))
		{
			g_theSmartTestBaseApp->CreateApp(CRptFillWPSApp::New);
			m_pReportFill = new CWPSRptFill();
		}
		else if (!strRptProgID.CompareNoCase(REPORTFILL_PROGID_SYSTEM))
		{		
			m_pReportFill = new CSystemRptFill();
			m_pReportFill->SetSysRptShowMaxCount(g_theSmartTestBaseApp->GetSysRptShowMaxCount());
		}
		else
		{	
			m_pReportFill = NULL;
		}
	}

	if (m_pReportFill != NULL)
	{
		m_pReportFill->SetGuideBook(m_pGuideBook);
		m_pReportFill->m_strName = m_strName;
		m_pReportFill->SetFillReport(g_theSmartTestBaseApp->IsFillReport());
	}
#endif

	return 0;
}

CWordRptExportBase* CTestControlBase::CreateRptExport(const CString &strRptProgID)
{
	//shaolei 修改此处  20220718
	//return NULL;
#ifndef _PSX_QT_LINUX_
	CWordRptExportBase* pRptExport = NULL;

	if (strRptProgID == REPORTFILL_PROGID_WPS)
	{
		pRptExport = new CWPSRptExport;
	}
	else
	{
		pRptExport = new CWordRptExport;
	}

	return pRptExport;
#else 
	return NULL;
#endif
}

CTestControlBase::~CTestControlBase()
{
	m_oTCtrlMsgRcv.RemoveAll();
	ReleaseMacroTestInterface();
	GBS_PpReleaseAllDevice();

#ifndef GUIDEBOOK_DEV_MODE
	if(m_pGuideBook != NULL)
	{
		delete m_pGuideBook;
		m_pGuideBook = NULL;
	}
#endif

	if (!m_bTestControlWndRef)
	{
		if(m_pTCtrlWnd != NULL)
		{
			m_pTCtrlWnd->DestroyWindow();
			delete m_pTCtrlWnd;
		}
	}

	m_pTCtrlWnd = NULL;

	if (m_pReportFill != NULL)
	{
		m_pReportFill->Close(1);
		delete m_pReportFill;
		m_pReportFill = NULL;
	}

	m_oDeviceRefs.DeleteAll();
	m_listHdResReqFaildItem.RemoveAll();
}

#ifdef GUIDEBOOK_DEV_MODE
BOOL CTestControlBase::CreateTest(CGuideBook *pGuideBook, BOOL bCreatePpDeviceRefs)
{
	m_pGuideBook = pGuideBook;

	if (bCreatePpDeviceRefs)
	{
		CreatePpDeviceRefs();
	}

	m_pGuideBook->SetParent(this);
	//m_pGuideBook->InitGuideBook();//2019-4-27  lijunqing   修改为测试前再初始化
	m_pItemContainer = (CItemContainer*)m_pGuideBook->GetItemContainer();
	m_pItemContainer->SetGuideBook(pGuideBook);

	return TRUE;
}
#endif

//创建PMTest组件

void CTestControlBase::CreateMacroTestInterface(CTestMacros* pTestMacros, const CString &strMacroID)
{
	if (pTestMacros == NULL)
	{
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("pTestMacros == null"));
	}
	else
	{
       // CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s, %d"), pTestMacros->m_strMacroFile.GetString(), pTestMacros->m_strMacroFile.GetLength());
	}

	CTestMacro *pMacro = (CTestMacro*)pTestMacros->FindByID(strMacroID);
	ASSERT (pMacro != NULL);

	if (pMacro == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TestMacro [%s] not exist in [%s]"), strMacroID.GetString(), pTestMacros->m_strMacroFile.GetString());
		StopTestExtern(_T(""), 0);
		return;
	}

	CString strType = pMacro->m_strType; 
	CreateMacroTestInterface(strType, pTestMacros->m_strProgID, m_pGuideBook->m_strTestMacroFileID, m_pGuideBook->GetTestApps(TRUE));

	if (m_pMacroTestInterface != NULL)
	{
		m_pMacroTestInterface->SetTestMacro(pMacro);   //add by shaolei
	}
}

void CTestControlBase::CreateMacroTestInterface_HdRes()
{
	CreateMacroTestInterface(ID_HD_RES, ID_HD_RES, ID_HD_RES, m_pGuideBook->GetTestApps(TRUE));
}

void CTestControlBase::CreateMacroTestInterface(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	m_pMacroTestInterface = g_theSmartTestBaseApp->GetMacroTest(strType, strProgID, strMacroFile, pTestApps);
	m_pGuideBook->SetgVmProgID(strProgID);

	if (m_pMacroTestInterface != NULL)
	{
		BOOL bTrue = TRUE;

		//2021-1-5  lijunqing  增加简化版本的功能，新创建的时候，配置IP
		if (CTCtrlCntrConfig::IsSimpleTestMode())
		{
			if (m_pMacroTestInterface->IsNewCreate())
			{
				CString strIpXml;
				CTCtrlCntrConfig::GetIP_TestApp(strIpXml);
				m_pMacroTestInterface->SetConfig(strIpXml);
			}
		}

		try
		{
			m_pMacroTestInterface->SetWndMsg((unsigned long)m_pTCtrlWnd->GetSafeHwnd(), WM_ELECTRIC_TEST);
		}
		catch (...)
		{
			bTrue = FALSE;
			TRACE("catch error-----");
		}

		if (bTrue)
		{
			return;
		}
		else
		{
			delete m_pMacroTestInterface;
			m_pMacroTestInterface = NULL;
		}
	}
	else
	{
#ifdef _PSX_QT_LINUX_
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("Create TestMacroTestInterface Failed"));
#else
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, g_sLangTxt_CreatTestCmtFail/*L"创建测试仪通讯组件失败"*/);
#endif
	}
}

void CTestControlBase::CreateMacroTestInterface()
{
	if (m_pMacroTestInterface != NULL)
	{
		return;
	}

	CString strType; 
	CreateMacroTestInterface(strType, m_pGuideBook->m_pTestMacros->m_strProgID, m_pGuideBook->m_strTestMacroFileID, m_pGuideBook->GetTestApps(TRUE));
	//CreateMacroTestInterface(strType, _T("IotVm.TestEngine"), m_pGuideBook->m_strTestMacroFileID, m_pGuideBook->m_strTestAppGroup);
}

void CTestControlBase::ReleaseMacroTestInterface(BOOL bRelease)
{
	if (m_pMacroTestInterface == NULL)
	{
		return;
	}

// 	if (bRelease)
// 	{
// 		m_pMacroTestInterface->Release();
// 	}
	CMacroTestFactory::ReleaseMacroTestEngine();
	m_pMacroTestInterface = NULL;
}

//创建通讯规约引擎对象
void CTestControlBase::CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef)
{
	CString strDeviceID ;

	strDeviceID = m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);

	if (strDeviceID.IsEmpty())
	{
		if (pDevieceRef->m_strID.GetLength() > 0)
		{
			strDeviceID = pDevieceRef->m_strID;
		}
		else
		{
			strDeviceID = GetPathFileNameFromFilePathName(m_pGuideBook->m_strDeviceModelFile);
		}
	}

	pDevieceRef->m_oPpDevice =  (CXProtocolDevice*)pEngine->CreateDevice(pDevieceRef->m_strPpTemplateFile, pDevieceRef->m_strDeviceModelFile, strDeviceID);

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	if (pDevieceRef->m_strEngineMode.IsEmpty() || pDevieceRef->m_strEngineMode == STT_CMD_PARA_EngineMode_COM)
	{
		//COM接口，没有SetSttCmdDataFormat
	}
	else
	{
		if (pDevieceRef->m_oPpDevice != NULL)
		{
			pDevieceRef->m_oPpDevice->SetSttCmdDataFormat(g_theSmartTestBaseApp->GetXmlRwType());
		}
	}
#endif

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("CreatePpEngineDevice:%s"), pDevieceRef->m_strID.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("      TemplateFile:%s"), pDevieceRef->m_strPpTemplateFile.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("      DvmFile:%s"), pDevieceRef->m_strDeviceModelFile.GetString());

	//设置录波文件路径
	SetPpEngineRecordFilePath(pDevieceRef->m_oPpDevice);
}

void CTestControlBase::DeviceCmmConfig(CPpDeviceRef *pPpDeviceRef)
{
    //pPpDeviceRef->SetCommConfig(&m_oCmmConfig);
	pPpDeviceRef->CommConfig();
}

BOOL CTestControlBase::CreatePpEngineDevice(CCommCmd *pCmd)
{
	if (m_oDeviceRefs.IsAllDeviceConnectSucc())
	{
		return TRUE;
	}

	//如果是多引擎，在此修改  李俊庆-20140918
	//shaolei  for debug  暂时写死  20210929
	/*ASSERT(FALSE);*/
/*//2023-8-22  lijunqing 不再使用m_pGuideBook->m_strPpEngineProgID，统一使用pPpDeviceRef->m_strPpEngineProgID
	//如果是打开测试记录文件，则进行初始化设置pPpDeviceRef
	CProtocolEngineInterface *pEngine = g_theSmartTestBaseApp->GetPpEngine(m_pGuideBook->m_strPpEngineProgID);

	if (pEngine == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoPrtcCpnt/ *L"没有注册规约引擎组件"* /);
		return FALSE;
	}
*/

	//@@根据设备的ID【IP地址】，创建通讯设备对象
	//strDeviceID : 设备数据模型的ID【IP地址】
	CPpDeviceRef *pPpDeviceRef = NULL;
	pPpDeviceRef = m_oDeviceRefs.GetPpDeviceRefToConnect();
	ASSERT (pPpDeviceRef != NULL);

	//shaolei  for debug  暂时写死  20210929
	//ASSERT(FALSE);
	CProtocolEngineInterface *pEngine = g_theSmartTestBaseApp->GetPpEngine(pPpDeviceRef->m_strEngineMode, pPpDeviceRef->m_strPpEngineProgID);

	if (pEngine == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoPrtcCpnt/*L"没有注册规约引擎组件"*/);
		return FALSE;
	}

	try
	{
		if (pPpDeviceRef->m_oPpDevice == NULL)
		{
			//李俊庆  20140918
			CreatePpEngineDevice(pEngine, pPpDeviceRef);
		}
	}
	catch (...)
	{
		return FALSE;
	}

	//if (m_oPpDevice == NULL)
	if (pPpDeviceRef->m_oPpDevice == NULL)
	{
		g_theSmartTestBaseApp->ReleasePpEngine(pPpDeviceRef->m_strPpEngineProgID);//(m_pGuideBook->m_strPpEngineProgID);
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CreatPrtcFail/*L"创建规约通讯设备失败"*/);
	}
	else
	{
		try
		{
            pPpDeviceRef->m_oPpDevice->AttachSystemWndMsg((ULONG)m_pTCtrlWnd->GetSafeHwnd(), WM_ENGINE_SYSTEM_MSG);
			CString strTempFilePath = ats_GetBinaryTempFilePath(pCmd);
			::CreateAllDirectories(strTempFilePath);

			try
			{
				pPpDeviceRef->m_oPpDevice->SetRecordPath(strTempFilePath);
			}
			catch (...)
			{

			}

			if (pCmd->IsUseConnect())
			{
				DeviceCmmConfig(pPpDeviceRef);
			}
			//Sleep (5000);
		}
		catch(...)
		{
			if (pPpDeviceRef != NULL)
			{
				if (pPpDeviceRef->m_oPpDevice != NULL)
				{
					pPpDeviceRef->m_oPpDevice = NULL;
					pPpDeviceRef->SetConnectState(FALSE);
				}
			}
			return FALSE;
		}
	}

	return TRUE;
}


//串行化
long CTestControlBase::BinarySerialize(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

void CTestControlBase::InitAllCpus()
{
	CExBaseList oListCpus;
	m_pGuideBook->GetAllCpus(oListCpus);
	POS pos = oListCpus.GetHeadPosition();
	CCpus *pCpus = NULL;

#ifndef _PSX_QT_LINUX_
	CPpDeviceRefs *pPpDeviceRefs = CTCtrlCntrWorkSpace::GetPpDeviceRefs();
	long nIndex = 0;
	CPpDeviceRef *pPpRef = NULL;

	//是否使用同一的模式
	BOOL bUseTotal = m_pGuideBook->m_strDeviceModelFile.GetLength() > 0;

	while (pos != NULL)
	{
		pCpus = (CCpus *)oListCpus.GetNext(pos);

		if (bUseTotal)
		{
			pCpus->m_strPpEngineProgID = m_pGuideBook->m_strPpEngineProgID;
			pCpus->m_strPpTemplateFile = m_pGuideBook->m_strPpTemplateFile;
			pCpus->m_strDeviceModelFile = m_pGuideBook->m_strDeviceModelFile;
		}
		else
		{
			pPpRef = (CPpDeviceRef *)pPpDeviceRefs->GetAtIndex(nIndex);

			if (pPpRef == NULL)
			{
				break;
			}

			pCpus->m_strPpEngineProgID = pPpRef->m_strPpEngineProgID;
			pCpus->m_strPpTemplateFile = pPpRef->m_strPpTemplateFile;
			pCpus->m_strDeviceModelFile = pPpRef->m_strDeviceModelFile;
			nIndex++;
		}
	}
#endif

	oListCpus.RemoveAll();
}

//2023-4-3 lijunqing 通信部分改为SttIot
void CTestControlBase::InitGbCommConfig()
{

#ifndef _PSX_QT_LINUX_
	CPpSttCommConfig *pCommConfig = CTCtrlCntrWorkSpace::GetSttCommConfig(FALSE);

	if (pCommConfig != NULL)
	{
		m_pGuideBook->SetCommConfig(pCommConfig);
	}

	CPpSttCommConfigs *pCommConfigs = CTCtrlCntrWorkSpace::GetSttCommConfigs(FALSE);

	if (pCommConfigs != NULL)
	{
		m_pGuideBook->SetCommConfigs(pCommConfigs);
	}
#endif
}

//初始化，创建TestControl
BOOL CTestControlBase::CreateTest(CDataGroup *pTestApps)
{
	CreateReportFill(g_strReportFillProgID);
	m_strGbBinaryFile = CTCtrlCntrWorkSpace::s_GetNewGuideBookBinaryFileName();
    InitGbBinaryFileName();

	m_pGuideBook->m_strGuideBookFileType = CTCtrlCntrWorkSpace::s_GetReportMapFile();

    //2020-9-13  lijunqing
    //long nRet = m_pGuideBook->OpenXMLFile(CTCtrlCntrWorkSpace::s_GetTemplateFile());
    CString strGbFile;
    strGbFile = CTCtrlCntrWorkSpace::s_GetTemplateFile();
    long nRet = m_pGuideBook->Open(strGbFile);

	//shaolei  创建测试时，只有选择了规约模板文件，才使用选择的文件，否则使用模板中写好的规约模板
	//20210909
	CString strPpTemplateFile = CTCtrlCntrWorkSpace::s_GetPpTemplateFile();
	if (strPpTemplateFile.GetLength() >= 5)
	{
		m_pGuideBook->m_strPpTemplateFile = strPpTemplateFile;
	}
    
	m_pGuideBook->m_strDeviceModelFile = CTCtrlCntrWorkSpace::s_GetPpDeviceFile();
	m_pGuideBook->m_strPpEngineProgID = CTCtrlCntrWorkSpace::s_GetPpEngineProgID();

#ifdef CGuideBook_with_iecfg_file
	//测试仪IEC61850配置文件, 20180829
	m_pGuideBook->CopyIecCfgFile(m_strGbBinaryFile);
#endif

	if(!nRet)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FileOpenFalseS.GetString()/*L"打开文件\"%s\"出错"*/, CTCtrlCntrWorkSpace::s_GetTemplateFile().GetString());
        return 0;
	}

	m_pGuideBook->AdjustByTkIDIndex( CTCtrlCntrWorkSpace::s_GetTkIDIndex()
		, CTCtrlCntrConfig::IsAdjustByTkIDMode_Delete());

	//20140920   多设备通讯相关设置
	InitAllCpus();

	//初始化特性曲线测试项目
	m_pGuideBook->InitMacroCharTestItems();
	//m_pGuideBook->InitGuideBook();	//2019-4-27  lijunqing   修改为测试前再初始化
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	//2023-4-3  lijunqing 初始化通信参数
	InitGbCommConfig();

	//2023-6-17 lijunqing 
	m_pGuideBook->SetTestApps(pTestApps);
	m_pGuideBook->AddMacroFileToTestApps();

	//保存测试记录文件
	m_pGuideBook->SaveBinaryFile(m_strGbBinaryFile, CTCtrlCntrConfig::Get_RWReportFileMode());	

	if (m_pGuideBook->m_strIecfgFile.GetLength() > 5)
	{
		m_pGuideBook->SetIecfgFile(CTCtrlCntrWorkSpace::s_GetIecfgFile());
	}
	
	m_pItemContainer = (CItemContainer*)m_pGuideBook->GetItemContainer();

	//通讯配置文件
	m_pGuideBook->OpenCommConfigFile(_T(""));

	//报告映射关联
	if (m_pReportFill != NULL)
	{
		m_pReportFill->SetGuideBook(m_pGuideBook);
	}

	//打开规约引擎
	//2020-02-08  lijq  注释  打开测试报告查看的时候，提高打开速度
	CreatePpDeviceRefs();

    return 1;
}

void CTestControlBase::CreatePpDeviceRefs()
{
	CExBaseList oListDevice;
	m_pGuideBook->GetDevice(oListDevice);
	POS posDevice = oListDevice.GetHeadPosition();
	CDevice *pDevice = NULL;
	POS posCpus = NULL;
	CExBaseList oListCpus;
    m_oDeviceRefs.DeleteAll();
    BOOL bUseOwn = TRUE;

#ifndef _PSX_QT_LINUX_
    CPpDeviceRefs *pPpDeviceRefs = CTCtrlCntrWorkSpace::GetPpDeviceRefs();
    bUseOwn = (pPpDeviceRefs->GetCount() > 0);
#else
	bUseOwn = FALSE;
#endif

	while (posDevice != NULL)
	{
		pDevice = (CDevice *)oListDevice.GetNext(posDevice);
		pDevice->GetCpusList(oListCpus);

#ifndef _PSX_QT_LINUX_
		if (pPpDeviceRefs->HasInit())
		{
			pPpDeviceRefs->Copy(&m_oDeviceRefs);
			oListCpus.RemoveAll();
			continue;
		}
#endif

		m_oDeviceRefs.CreateAllDevice(oListCpus, m_pGuideBook->m_strPpEngineProgID
			, m_pGuideBook->m_strPpTemplateFile
			, m_pGuideBook->m_strDeviceModelFile
			, m_pGuideBook->m_strEngineMode
			, bUseOwn);

		oListCpus.RemoveAll();
	}

	oListDevice.RemoveAll();

	InitPpDeviceRefsCommConfig();
}

void CTestControlBase::ReleasePpDeviceRefs(BOOL bPpDeviceHasDelete)
{
	if (bPpDeviceHasDelete)
	{
		POS pos = m_oDeviceRefs.GetHeadPosition();

		while (pos != NULL)
		{	
			CPpDeviceRef *pDeviceRef = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);
			pDeviceRef->m_oPpDevice = NULL; //ReleasePpEngine的时候，已经删掉了
		}
	}

	m_oDeviceRefs.DeleteAll();
}

void CTestControlBase::InitPpDeviceRefsCommConfig()
{
	CPpDeviceRef *pRef = NULL;
	POS pos = m_oDeviceRefs.GetHeadPosition();
	CDataGroup *pCommConfig = m_pGuideBook->GetCommConfig(FALSE);

	if (pCommConfig != NULL)
	{
		while (pos != NULL)
		{
			pRef = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);
			pRef->SetCommConfig(pCommConfig);
		}
	}

	CDataGroup *pCommConfigs = m_pGuideBook->GetCommConfigs(FALSE);

	if (pCommConfigs != NULL)
	{
		POS posCfg = pCommConfigs->GetHeadPosition();

		while (pos != NULL && posCfg != NULL)
		{
			pRef = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);
			pCommConfig = (CDataGroup *)pCommConfigs->GetNext(posCfg);
			pRef->SetCommConfig(pCommConfig);
		}
	}
}

void CTestControlBase::InitGbBinaryFileName()
{
	m_strName = GetFileTitleFromFilePath(m_strGbBinaryFile);
	m_strID = m_strName;

	CTCtrlCntrWorkSpace::s_SetLastTestFile(m_strGbBinaryFile);
	m_strGbBinaryFileName = m_strName;
}

void CTestControlBase::SaveFinalXMLReportEx()
{
	SaveFinalXMLReport();

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CTestControlBase *pTestControl = (CTestControlBase *)GetNext(pos);

		pTestControl->SaveFinalXMLReport();
	}
}

void CTestControlBase::SaveFinalXMLReport()
{
	CString strXmlFile;
	strXmlFile = GetGbBinaryFile();
	strXmlFile = ChangeFilePostfix(strXmlFile, _T("xml"));
	m_pGuideBook->SaveFinalXMLReport(strXmlFile);
}

void CTestControlBase::SaveBinaryFile()
{
	if (m_pGuideBook == NULL)
	{
		return;
	}

	m_pGuideBook->SaveBinaryFile(m_strGbBinaryFile, CTCtrlCntrConfig::Get_RWReportFileMode());
}

void CTestControlBase::DeleteTempDirectorys()
{
	if (m_pGuideBook == NULL)
	{
		return;
	}

	if (g_theSmartTestBaseApp->IsSaveRptToDB() || m_pGuideBook->IsSaveRptToDB())
	{
		return;
	}

	if (m_strGbBinaryFile.GetLength() < 10)
	{
		return;
	}

#ifndef _PSX_QT_LINUX_
    CString strTempFilePath = GetItemTempPath();//GetPathFromFilePathName(m_strGbBinaryFile);
	CXFileMngr oXFileMngr;
	oXFileMngr.SetLibraryPath(strTempFilePath);
	POS pos = oXFileMngr.GetHeadPosition();
	CExBaseObject *p = NULL;
	CXFile *pXFile = NULL;
	CString strPostfix;
	CString strSrcFile;
	CExBaseList listDel;

	while (pos != NULL)
	{
		p = oXFileMngr.GetNext(pos);

		if (p->GetClassID() != CLASSID_XFILE)
		{
			continue;
		}

		pXFile = (CXFile *)p;
		pXFile->GetFilePostfix(strPostfix, FALSE);
		strPostfix.MakeLower();

		if (strPostfix == g_strTempGuideBookBinaryPostfix || strPostfix == _T("xml"))
		{
			strSrcFile = pXFile->GetTotalFileName();

			if (strPostfix == _T("xml"))
			{
				CString strGbrpt = ChangeFilePostfix(strSrcFile, g_strGuideBookBinaryPostfix);

				if (IsFileExist(strGbrpt))
				{
					//与gbrpt配套存在的xml，是最终的xml报告，不能删除
					continue;
				}
			}

			X_DeleteFile(strSrcFile);
			listDel.AddTail(pXFile);
		}
	}

	if (listDel.GetCount() == oXFileMngr.GetCount())
	{
		DeleteAllDirectorys(strTempFilePath);
	}

	listDel.RemoveAll();
#endif
}

CString CTestControlBase::GetGbBinaryFileName()
{
	return GetPathFileNameFromFilePathName(m_strGbBinaryFile);
}

void CTestControlBase::ChangeGbBinaryFileName(const CString &strFileName)
{
	m_strGbBinaryFile = strFileName;
	m_pGuideBook->m_strGuideBookFile = strFileName;
	InitGbBinaryFileName();
}

long CTestControlBase::OpenBinaryFile(const CString &strFile, long nRWReportFileMode, BOOL bOnlyReadAttr)
{
	long nRet = m_pGuideBook->OpenBinaryFile(strFile, nRWReportFileMode, bOnlyReadAttr);
	
	return nRet;
}

long CTestControlBase::OpenGbxmlFile(const CString &strFile, BOOL bOnlyReadAttr, const long &nXmlRWType)
{
	if (m_pGuideBook == NULL)
	{
		return -1;
	}

	return m_pGuideBook->OpenXMLFile(strFile, bOnlyReadAttr, nXmlRWType);
}

BOOL CTestControlBase::CreateTest(const CString &strGbBinaryFile, BOOL bFullPath, BOOL bBinaryFile)
{
	if (bBinaryFile)
	{
		//二进制文件：gbrpt
		if (!bFullPath)
		{
			m_strGbBinaryFile = GetGuideBookBinaryFileName(strGbBinaryFile);
		}
		else
		{
			m_strGbBinaryFile = strGbBinaryFile;
		}

		InitGbBinaryFileName();

		if(! OpenBinaryFile(m_strGbBinaryFile, CTCtrlCntrConfig::Get_RWReportFileMode()))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestFileOpenFalseS.GetString()/*L"打开试验文件\"%s\"出错"*/, strGbBinaryFile.GetString());
			return FALSE;
		}
	}
	else
	{
		//xml文件：gbxml
		CString strGbxmlFile = strGbBinaryFile;
		SYSTEMTIME oTime;
		CString strTime;
		::GetLocalTime(&oTime);
		strTime.Format(_T("_(%04d%02d%02d_%02d%02d%02d)"), oTime.wYear, oTime.wMonth, oTime.wDay
			, oTime.wHour, oTime.wMinute, oTime.wSecond);

		//先根据模板文件名称，获取一个BinaryFileName
		CString strBinaryFile = GetFileNameFromFilePath(strGbBinaryFile);
		strBinaryFile = ParseFileName(strBinaryFile);  //去掉后缀
		//给目标报告文件，打上时标
		strBinaryFile += strTime;
		strBinaryFile = ChangeFilePostfix(strBinaryFile, g_strGuideBookBinaryPostfix);
		m_strGbBinaryFile = GetGuideBookBinaryFileName(strBinaryFile);
		InitGbBinaryFileName();

		if (! bFullPath)
		{
			strGbxmlFile = GetGuideBookGbxmlFileName(strGbxmlFile);
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("CreateTest：%s"), strGbxmlFile.GetString());
		if (! OpenGbxmlFile(strGbxmlFile))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestFileOpenFalseS.GetString()/*L"打开试验文件\"%s\"出错"*/, strGbxmlFile.GetString());
			return FALSE;
		}

		if (g_bInXTestDbGenReprtState)
		{
			//拷贝报告模板文件，到目标路径
			CString strDocFile = strGbxmlFile;
			strDocFile = GetFileNameFromFilePath(strDocFile);
			strDocFile = ParseFileName(strDocFile);  //去掉后缀
			//给目标报告文件，打上时标
			strDocFile += strTime;
			strDocFile += g_strDocPostfix;
			strDocFile = GetGuideBookDocRptFileName(strDocFile);
			CString strSrcFile;
			strSrcFile = ChangeFilePostfix(strGbxmlFile, g_strDocFilePostfix);

			if (!::X_CopyFile(strSrcFile, strDocFile))
			{
                CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("拷贝报告模板文件【%s】到WorkSpace目录失败！"), strGbxmlFile.GetString());
				return FALSE;
			}
		}
	}

#ifndef _PSX_QT_LINUX_
    if (m_pGuideBook->m_strIecfgFile.GetLength() > 5)
	{
		m_pGuideBook->SetIecfgFile(CTCtrlCntrWorkSpace::s_GetIecfgFile());
	}
#endif

	InitAfterOpenBinaryFile();

	return TRUE;
}

void CTestControlBase::InitAfterOpenBinaryFile()
{
	m_strName = m_strGbBinaryFileName;
	m_strID = m_strGbBinaryFileName;

	CreateReportFill(g_strReportFillProgID);
	m_pItemContainer = (CItemContainer*)m_pGuideBook->GetItemContainer();

	//通讯配置文件
	m_pGuideBook->OpenCommConfigFile(_T(""));

	//报告映射关联
	if (m_pReportFill != NULL)
	{
		m_pReportFill->SetGuideBook(m_pGuideBook);
	}

	//为了提高打开速度，在报告生成模式下，不打开规约引擎
	if (g_bInXTestDbGenReprtState)
	{//2018-4-3  for 南瑞科技检测中心，故障指示器报告造假
		return;
	}

	//打开规约引擎
	//2020-02-08  lijq  注释  打开测试报告查看的时候，提高打开速度
	CreatePpDeviceRefs();
	m_bUseBinaryOffset = m_pGuideBook->UseBinaryOffset();

	if (m_pGuideBook->IsSaveRptToDB())
	{
		double dSize = file_GetFileSize(m_strGbBinaryFile);
		dSize /= 1048576;
		
		if (dSize < 5)
		{
			return;
		}

#ifndef _PSX_QT_LINUX_
		//CString strTempFilePath = GetItemTempPath();
		//gb_ClearReportDatasByMap(m_pGuideBook, strTempFilePath, g_theSmartTestBaseApp->IsWriteTestTempFile());
		//gb_ClearItemInDbState(m_pGuideBook, strTempFilePath, g_theSmartTestBaseApp->IsWriteTestTempFile());
		ClearItemInDbState();
		Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);
		SaveBinaryFile();
		//mem_EmptyAllSet_CurrApp();
        mem_AdjustTokenPrivilegesForNT();
		mem_EmptyAllSet();
#endif
    }
}


BOOL GB_IsReportFillUseNoRepeat(CReport* pReport)
{
	CGbItemBase *pGbItem = (CGbItemBase*)pReport->GetParent()->GetParent();

	if (pGbItem == NULL)
	{
		return FALSE;
	}

	if (pGbItem->GetClassID() == GBCLASSID_COMMCMD )
	{
		CCmd *pCmd =  ((CCommCmd*)pGbItem)->GetCmd();
		return (pCmd->m_nReportFillUseNoRepeat != 0);
	}

	if (pGbItem->GetClassID() == GBCLASSID_MACROTEST)
	{
		return (((CMacroTest*)pGbItem)->m_nReportFillUseNoRepeat != 0);
	}

	return FALSE;
}

long CTestControlBase::FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
{
	if (GB_IsReportFillUseNoRepeat(pReport))
	{
		nRepeatIndex = 0;
	}

	if (m_pReportFill != NULL)
	{
		m_pReportFill->FillReport(pReport, nRepeatIndex, nInsertDataLinkWhenEligible);
	}

	return 0;
}

void CTestControlBase::AddTCtrlMsgRcvInterface(CTCtrlMsgRcvInterface *pInterface)
{
	ASSERT(pInterface != NULL);
	m_oTCtrlMsgRcv.AddTCtrlMsgRcvInterface(pInterface);
}

CString CTestControlBase::GetReportFilePath(const CString &strExtend)
{
	//打开报告文件
	CString strWordFile;

	strWordFile = m_strGbBinaryFile;
	long nPos = strWordFile.ReverseFind('.');
	strWordFile = strWordFile.Left(nPos);

	if (strExtend.GetLength() > 0)
	{
		strWordFile += strExtend;
	}

	strWordFile += _T(".doc");

	return strWordFile;
}

void CTestControlBase::OpenReportFile(CWnd *pParentWnd, BOOL bFirst)
{
	CreateReportFill(g_strReportFillProgID);

	if (m_pReportFill != NULL)
	{
		m_pReportFill->SetParentWnd(pParentWnd);
	
		//打开报告文件
		CString strWordFile = GetReportFilePath();

		ASSERT (m_pReportFill != NULL);
		if (!m_pReportFill->Open(strWordFile, bFirst))
		{
			//重新填写报告
		}
	}
	
	if (m_pGuideBook->IsGuideBookFirstCreate())
	{
		CReport *pReport = m_pGuideBook->GetReport(-1);
		FillReport(pReport, 0);
		SaveReport();
	}
}


BOOL CTestControlBase::OpenWordReportFile(BOOL bExportWord, const CString &strDocFile)
{
	//	CreateReportFill(REPORTFILL_PROGID_WORD, bExportWord);
	CreateReportFill(CTCtrlCntrConfig::GetReportMode(), bExportWord);

	if (m_pReportFill != NULL)
	{
		m_pReportFill->SetParentWnd(NULL);
	}

	//打开报告文件
	CString strWordFile;

	if (strDocFile.GetLength() == 0)
	{
		strWordFile = GetReportFilePath();
	}
	else
	{
		strWordFile = strDocFile;
	}

	CWordRptFillBase *pReportFill = (CWordRptFillBase*)m_pReportFill;
	ASSERT (pReportFill != NULL);

	if (pReportFill == NULL)
	{
		return FALSE;
	}

	if (!pReportFill->OpenOnly(strWordFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("++++CTestControl::OpenWordReportFile++++Open Failed [%s]"), strWordFile.GetString());
		return FALSE;
	}

	//全局参数填写
	CReport *pReport = m_pGuideBook->GetReport(-1);
	FillReport(pReport, 0);

	return TRUE;
}

BOOL CTestControlBase::OpenWordReportFileOnly(CString &strWordFile)
{
	return FALSE;
}

CString CTestControlBase::GetDeviceReportFile()
{
	CString strFile;
	CDvmDataset *pGlobal = m_pGuideBook->GetGlobalDatas();

	if (pGlobal == NULL)
	{
		return strFile;
	}

	CDvmData *pSN = (CDvmData*)pGlobal->FindByID(_T("SN"));
	CDvmData *pRpt_SN = NULL;

	if (pSN == NULL)
	{
		pSN = (CDvmData*)pGlobal->FindByID(_T("sn"));
	}

	pRpt_SN = (CDvmData*)pGlobal->FindByID(g_strGbGlobalData_ReportSN);

	if (pSN != NULL && pRpt_SN != NULL)
	{
		strFile.Format(_T("%s$%s.doc"), pSN->m_strValue.GetString(), pRpt_SN->m_strValue.GetString());
	}
	else
	{
		if (pSN != NULL)
		{
			strFile.Format(_T("%s.doc"), pSN->m_strValue.GetString());
		}

		if (pRpt_SN != NULL)
		{
			strFile.Format(_T("%s.doc"), pRpt_SN->m_strValue.GetString());
		}
	}

	return strFile;
}

void CTestControlBase::GenerateWordReport(CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd)
{
	m_pReportFill->SetParentWnd(pMsgWnd);
	CExBaseList *pListItems = m_pItemContainer->GetGuideBookAllItems();
	POS pos = pListItems->GetHeadPosition();
	CGbItemBase *pItem = NULL;
	//CString strPath;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)pListItems->GetNext(pos);
		//strPath = pItem->GetNamePathEx(GBCLASSID_GUIDEBOOK, FALSE);
		//CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
		//pMsgWnd->SetWindowText(strPath);
		GenerateWordReport(pItem, &oBuffer);
	}

	m_pReportFill->AdjustReport_FillEmpty();

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GenerateWordReport [%s] finished"), m_strGbBinaryFile.GetString());;
}

void CTestControlBase::CloseReportFill()
{
	if (m_pReportFill == NULL)
	{
		return;
	}

	CWordRptFillBase *pReportFill = (CWordRptFillBase*)m_pReportFill;
	pReportFill->CloseWord();
	delete pReportFill;
/*	CWordRptFill *pWordReportFill = (CWordRptFill*)m_pReportFill;
	pWordReportFill->CloseWord();
	delete pWordReportFill;
*/
	m_pReportFill = NULL;
}

//2019-7-15  打开临时文件：多装置测试模式下，如果数据量很大，导致内存不足，从临时文件获取数据
void CTestControlBase::Test_OpenTempBinaryFile(CGbItemBase *pItem)
{
	if (!m_pGuideBook->IsSaveRptToDB())
	{
		return;
	}

	CString strTempFileName = ats_GetBinaryTempFile(pItem);
	pItem->OpenBinaryTempFile(strTempFileName);
}

void CTestControlBase::OpenAllBinaryTempFiles()
{
	return;
    if (g_theSmartTestBaseApp->IsSaveRptToDB())
	{
		return;
	}

// 	if (m_pTestProject == NULL)
// 	{
// 		return ;
// 	}

// 	if (m_pTestProject->GetTestState() != g_strTesting)
// 	{
// 		return;
// 	}
	if (CTCtrlCntrWorkSpace::s_GetLastTestState() != g_strTesting)
	{
		return;
	}

#ifndef _PSX_QT_LINUX_

	//CString strTempFilePath = GetTestProjectTempFilePath(m_pTestProject);
	CString strTempFilePath = GetItemTempPath();//GetPathFromFilePathName(m_strGbBinaryFile);
	ASSERT(m_pItemContainer != NULL);

	CString strFileFind;// = strTempFilePath + _T("*.") + g_strTempGuideBookBinaryPostfix;
	CFileFind finder;
	strFileFind = strTempFilePath + _T("*.") + g_strTempGuideBookBinaryPostfix;
	BOOL bFlag = finder.FindFile(strFileFind);
	//CExBaseList *pListItems = m_pItemContainer->GetGuideBookAllItems();
	BOOL bRead = FALSE;
	CBinarySerialBuffer oBuffer;

	while(bFlag)
	{
		bFlag = finder.FindNextFile();
		CString strTempFileTitle = finder.GetFileTitle();
		CString strTempFileName = finder.GetFileName();
#ifdef _UNICODE
		long nIndex = _wtol(strTempFileTitle);
#else
		long nIndex = atol(strTempFileTitle);
#endif

		//CGbItemBase* pItem = (CGbItemBase*)pListItems->GetAtIndex(nIndex);
		CGbItemBase* pItem = m_pItemContainer->FindItemByIndex(nIndex);

		if (pItem != NULL)
		{
			pItem->OpenBinaryTempFile(strTempFilePath+strTempFileName);
			GenerateWordReport(pItem, &oBuffer);
			bRead = TRUE;
		}
	}

	if (bRead)
	{
		//CString strGuideBookBinaryFile = GetGuideBookBinaryFileName(m_pTestProject);
		Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);
		m_pGuideBook->SaveBinaryFile(m_strGbBinaryFile, CTCtrlCntrConfig::Get_RWReportFileMode());
		//DeleteAllDirectorys(strTempFilePath);
		DeleteTempDirectorys();
	}

#endif
}

long CTestControlBase::AfterOnUpdateGbItem(CGbItemBase* pGbItem)
{
	UINT nClassID = pGbItem->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		AfterOnUpdateGbItem_CommCmd(pGbItem);
		break;

	default:
		break;
	}

	return 0;
}

long CTestControlBase::AfterOnUpdateGbItem_CommCmd(CGbItemBase* pGbItem)
{
	//重新判断结果，填写报告
	CCommCmd *pCommCmd = (CCommCmd *)pGbItem;
	CReport *pReport = pGbItem->GetReport(-1);

	if (pReport == NULL)
	{
		return 0;
	}

	pCommCmd->AddCommCmdRptTags(pReport->GetValues());
	CString strSyntax;
	m_pCurrReport = pReport;
	pCommCmd->RunResultScript(strSyntax);
	m_pCurrReport = NULL;
	//填写报告
	FillReport(pReport, 0);

	return 0;
}

long CTestControlBase::OnUpdateGbItem(CGbItemBase* pGbItem)
{
	return 0;
}

long CTestControlBase::UpdateGbItem(const CString &strGbxmlFile, CGbItemBase* pGbItemSrc)
{
	CExBaseObject *pFind = Gb_GetItem(m_pGuideBook, pGbItemSrc);

	if (pFind != NULL)
	{
		m_pGuideBook->m_strGbXmlFile = strGbxmlFile;
		pGbItemSrc->Update(pFind);
		AfterOnUpdateGbItem((CGbItemBase*)pFind);
		Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

#ifndef _PSX_QT_LINUX_
		SaveBinaryFile();
#endif
	}

	return 0;
}

void CTestControlBase::ContinueExecutePpEngineCmd(CTestControlBase *pTestControl)
{
	m_nRunProcedureType = ProcedureType_TestItem;
}

//单一项目
long CTestControlBase::TestSingle(CGbItemBase* pGbItem)
{
	InitGuideBook();
    return TestSingle(pGbItem->m_nIndex);

    //经调试发现，即便执行成功，若已经执行结束，m_pCurrTestItem也可能为空指针。
    //shaolei 20201215
   // return (m_pCurrTestItem != NULL);
}

long CTestControlBase::OnTestAllInlegibleItems()
{
#ifndef AUTOTEST_DEMO
	//if (!Encrypt_IsEncrypt(FETUREID_AUTOTEST))
    if (!g_theSmartTestBaseApp->ats_IsRegisterTrue(FALSE, TRUE))
	{
		return 0;
	}
#endif

	if (m_nTestItemIndexBkForAllInlegible < 0)
	{//备份当前测试项目
		m_nTestItemIndexBkForAllInlegible = m_nCurrTestItemIndex;
	}

	if (GetDeviceRefsCount() == 0)
	{//2022-11-2  lijunqing
		CreatePpDeviceRefs();
	}

	m_pItemContainer->ClearFilter();
	m_pItemContainer->RemoveAll();
	CGbUnqualifiedItemTool oGbUnqualifiedItemTool;
	oGbUnqualifiedItemTool.QueryUnqualifiedItems(m_pGuideBook, m_pItemContainer);
	
	TestFirstItem();

	return 0;
}

long CTestControlBase::TestSingle_MdOne(CGbItemBase* pGbItem)
{
	//2019-4-27  lijunqing   修改为测试前再初始化
	InitGuideBook();

#ifndef AUTOTEST_DEMO
   
	
    if (!g_theSmartTestBaseApp->ats_IsRegisterTrue(FALSE, TRUE))
	{
		if (!Gb_IsGbItemClassID(pGbItem->GetClassID()))
		{
			return 0;
		}
	}
#endif

	UINT nClassID = pGbItem->GetClassID();

	if (!(nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_SYSPARAEDIT))
	{
		return 0;
	}

	CSafety *pSafety = (CSafety *)pGbItem;
	pSafety->m_nManyDeviceTestMode = GbMdItemTestMode_ManyTime;
	m_pItemContainer->ClearFilter();
	long nFilter = AddIndexFilter(pGbItem->m_nIndex);
	m_pItemContainer->Query(nFilter, TRUE);

	OnTestItemCount_TCtrlMsg(m_pItemContainer->m_nItemCount);
	//m_oTCtrlMsgRcv.OnTestItemCount(m_pItemContainer->m_nItemCount, this);

	TestFirstItem();

	return 0;
}

long CTestControlBase::TestSingle(long nItemIndex)
{
	//2022-11-7  lijunqing 清除状态
	m_nTestItemIndexBkForAllInlegible = -1; 

	//2019-4-27  lijunqing   修改为测试前再初始化
	InitGuideBook();

	if (GetDeviceRefsCount() == 0)
	{//2022-11-2  lijunqing
		CreatePpDeviceRefs();
	}


	m_pItemContainer->ClearFilter();
	long nFilter = AddIndexFilter(nItemIndex);
	m_pItemContainer->Query(nFilter, TRUE);

	OnTestItemCount_TCtrlMsg(m_pItemContainer->m_nItemCount);
	//m_oTCtrlMsgRcv.OnTestItemCount(m_pItemContainer->m_nItemCount, this);

    //shaolei 20201212  此处还需要根据m_nSelect去确认是否开始测试，因此此处先注释
	//OnTestBegin_TCtrlMsg();20231101
    ////m_oTCtrlMsgRcv.OnTestBegin(this);原先的

    //成功返回1,失败返回0;  shaolei 20201215
    return TestFirstItem();
}

//某个项目到结束
long CTestControlBase::TestFrom(CGbItemBase* pGbItem)
{
	if (pGbItem == NULL)
	{
		return -1;
	}

	InitGuideBook();
	return TestFrom(pGbItem->m_nIndex);
}

void CTestControlBase::TraceItems()
{
	POS pos = m_pItemContainer->GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCountCmd = 0;
	long nCountMacroTest = 0;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)m_pItemContainer->GetNext(pos);
		nClassID = pItem->GetClassID();

		if (nClassID == GBCLASSID_MACROTEST)
		{
			nCountMacroTest++;
		}
		else if (nClassID == GBCLASSID_COMMCMD)
		{
			nCountCmd++;
		}
	}

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,g_sLangTxt_CommunItemD.GetString() /*_T("通讯命令项目个数：%d    电气量项目个数：%d")*/, nCountCmd, nCountMacroTest);
}

long CTestControlBase::QueryFrom(long nItemIndex)
{
	if (nItemIndex < 0)
	{
		nItemIndex = m_nCurrTestItemIndex;
	}

	m_nHasTestItemCount = 0;
	m_pItemContainer->ClearFilter();
	long nIndexFilter = m_pItemContainer->CreateAttrFilter(GbFilterAttrIndex,GbFilterOptrMoreThanEqual,nItemIndex);
	//暂停后继续测试，记录已完成的测试项目的数量
	long nFinishCount = m_pItemContainer->m_nCurrFinishItem;
	m_pItemContainer->Query(nIndexFilter, TRUE);
	m_pItemContainer->m_nCurrFinishItem = nFinishCount;

	OnTestItemCount_TCtrlMsg(m_pItemContainer->m_nItemCount);
    //m_oTCtrlMsgRcv.OnTestItemCount(m_pItemContainer->m_nItemCount, this);

	return 0;
}

//当模板中的测试项目，动态改变后，需要根据操作模式来重新查询项目
long CTestControlBase::QueryFrom_Ex(long nItemIndex)
{
	long nTestMode = m_pItemContainer->GetTestMode();
	switch (nTestMode)
	{
	case TestOptrMode_StartTest:
		nItemIndex = -1;
		return QueryFrom(nItemIndex);
	case TestOptrMode_TestSingle:
		break;
	case TestOptrMode_TestFrom:
		return QueryFrom(nItemIndex);
	default:
		nItemIndex = -1;
		return QueryFrom(nItemIndex);
	}

	return 0;
}

CGbItemBase* CTestControlBase::GetItemByIndex(long nItemIndex)
{
	return Gb_GetItemByIndex(m_pGuideBook, nItemIndex);
}

//shaolei 2023-7-13  
//自动测试存在bug：停止测试后，若被停止的项目是最后一个项目，则实际不会开始测试。查找不到需要测试的项目
void CTestControlBase::ProcessCurrentItemLast()
{
	m_pItemContainer = (CItemContainer*)m_pGuideBook->GetItemContainer();
	CGbItemBase *pTailItem = (CGbItemBase *)m_pItemContainer->GetTail();
	CGbItemBase *pCurrItem = GetItemByIndex(m_nCurrTestItemIndex);
	BOOL bReset = FALSE;

	//当前测试的项目，是最后一个项目。或者是最后一个项目的子项目
	if (pTailItem != NULL && pCurrItem != NULL)
	{
		if (pTailItem == pCurrItem)
		{
			bReset = TRUE;
		}
		else if (pCurrItem->GetParent() == pTailItem)
		{
			bReset = TRUE;
		}
	}

	if (bReset)
	{
		//强制从头开始
		m_pGuideBook->m_nIndex = 0;
		m_nCurrTestItemIndex = 0;
	}
}

long CTestControlBase::TestFrom(long nItemIndex)
{
	if (m_nTestItemIndexBkForAllInlegible > 0)
	{
		m_nCurrTestItemIndex = m_nTestItemIndexBkForAllInlegible;
	}

	//shaolei 2023-7-13  
	//自动测试存在bug：停止测试后，若被停止的项目是最后一个项目，则实际不会开始测试。查找不到需要测试的项目
	ProcessCurrentItemLast();

    //2019-4-27  lijunqing   修改为测试前再初始化
	InitGuideBook();

	if (GetDeviceRefsCount() == 0)
	{//2022-11-2  lijunqing
		CreatePpDeviceRefs();
	}

	QueryFrom(nItemIndex);

	//准备前驱项目
	if (m_nTestItemIndexBkForAllInlegible > 0)
	{
		CGbUnqualifiedItemTool oGbUnqualifiedItemTool;
		oGbUnqualifiedItemTool.Query_BFT_Items(m_pGuideBook, m_pItemContainer);
		m_nTestItemIndexBkForAllInlegible = -1;
	}

#ifndef _PSX_QT_LINUX_
    SHORT nState = ::GetKeyState(VK_CONTROL);

    if ( (nState & 0xFF00) > 0)
	{
		TraceItems();
	}
	else
#endif
	{
		//在TestFirstItem中会发送此消息，故此处注释 
		//shaolei 2021 0805
		//OnTestBegin_TCtrlMsg();20231101
		//m_oTCtrlMsgRcv.OnTestBegin(this);原先的

		TestFirstItem();
	}

	return 0;
}

//两个项目之间
long CTestControlBase::TestBetween(CGbItemBase* pGbItemBegin, CGbItemBase* pItemEnd)
{
	return 0;
}

long CTestControlBase::TestBetween(long nBeginItemIndex, long EndItemIndex)
{
	return 0;
}

void CTestControlBase::TestOverTimerItem()
{
	if (m_pCurrTestItem == NULL)
	{
		return;
	}

	TestItem(m_pCurrTestItem);
}

void CTestControlBase::IsMacroTCtrlException()
{
}

//状态
long CTestControlBase::TestByState(long nTestState)
{
	return 0;
}

long CTestControlBase::TestAllIneligible()
{
	return 0;
}

long CTestControlBase::TestAllNormal()
{
	return 0;
}

//测试控制
long CTestControlBase::FinishTest()
{
	return 0;
}

//隐藏全部测试相关的界面
void CTestControlBase::HideAllTestItemUI()
{
}

void CTestControlBase::DestroyAllTestItemUI()
{
}

long CTestControlBase::StopMacroTestOutput(BOOL bStopDevice)
{
	if (m_pMacroTestInterface == NULL)
	{
		return 0;
	}

	try
	{
		if (g_nLog_TestControl_Msg == 1)
		{
            CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("     -- call StopTest"));
		}

		m_pMacroTestInterface->StopTest();
	}
	catch(...)
	{
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("call StopTest error-----"));
	}
	
	try
	{
		if (bStopDevice)
		{
			m_pMacroTestInterface->StopDevice();
		}
	}
	catch(...)
	{
	}

	return 1;
}

//测试结束或者完成后的处理
void CTestControlBase::OnProjectTestEnded(BOOL bFinish)
{
#ifndef _PSX_QT_LINUX_
	//保存系统测试报告，删除临时文件
	//CString strBinaryFileName = GetGuideBookBinaryFileName(m_pTestProject);
	m_pGuideBook->SaveBinaryFile(m_strGbBinaryFile, CTCtrlCntrConfig::Get_RWReportFileMode());
	CString strTempFilePath = GetPathFromFilePathName(m_strGbBinaryFile);//GetTestProjectTempFilePath(m_pTestProject);
	//DeleteAllDirectorys(strTempFilePath);
	DeleteTempDirectorys();

	//报告保存
	SaveReport();
	ExportRptDataFile(); //先自动导出报告数据文件  2023-9-26  lijunqing
#endif

	//m_pTestProject->SetTestState(g_strTestStop);
	CTCtrlCntrWorkSpace::s_SetLastTestState(g_strTestStop);

#ifndef _PSX_QT_LINUX_
	CTCtrlCntrWorkSpace::g_pWorkSpace->Save();
#endif

	m_pCurrTestItem = NULL;
	m_pCurrSubTestItem = NULL;

	//更新界面显示
	//OnStopTest_TCtrlMsg(bFinish);//此处不用处理子TestControl，因为StopTestExtern已经处理
	m_oTCtrlMsgRcv.OnStopTest(bFinish, this);
}

//自动测试自身停止测试
long CTestControlBase::StopTest(const CString &strMsg)
{
	return StopTestExtern(strMsg);
}

//由于在原StopTestExtern中有互斥锁，与OnElectricMsg中的锁重复，需要删除原锁，改到此函数中增加互斥锁
long CTestControlBase::StopTestByOptr()
{
 #ifndef _PSX_QT_LINUX_
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">>>>>>>>>>>>>>>>>>CTestControlBase::StopTestByOptr()---------------1"));
 	CAutoSimpleLock oLock(m_oCriticSectionGridTest);
 #endif
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">>>>>>>>>>>>>>>>>>CTestControlBase::StopTestByOptr()---------------2"));
	return StopTestExtern(_T(""), TRUE);
}
//外部停止测试：用户停止测试、由于异常停止测试
long CTestControlBase::StopTestExtern(const CString &strMsg, BOOL bExtern)
{
	//m_bIsTestStoped = TRUE;
// #ifndef _PSX_QT_LINUX_
// 	CAutoSimpleLock oLock(m_oCriticSectionGridTest);
// #endif


#ifndef _PSX_QT_LINUX_
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, g_sLangTxt_TestStopS.GetString() /*_T("【%s】测试停止")*/, m_strGbBinaryFileName);
#endif

    BOOL bFinish = FALSE;

	if (m_pTCtrlWnd != NULL)
	{
		m_pTCtrlWnd->StopTest();
	}
	
	HideAllTestItemUI();

#ifndef GUIDEBOOK_DEV_MODE
	//更新测试项目的测试状态，如果测试项目的状态为测试完成状态，则不更新
	//####################
	if (m_pCurrTestItem != NULL)
	{
		//删除最近添加的报告数据对象
		if (bExtern)
		{
			m_pCurrTestItem->DeleteReport(); //2017.05.17
		}

		m_pCurrTestItem->SetState(TEST_STATE_STOPED);  //此处会根据上一次报告的状态，设置项目的状态

		m_oTCtrlMsgRcv.OnCurrItemStateChanged(m_pCurrTestItem);

		if(m_pCurrTestItem->GetState() != TEST_STATE_STOPED)
		{
			//说明在SetState函数中，通过InitStateByReport()函数给测试项设置了状态，此时需要再通知AtsBench此时停止
			//shaolei 2019.06.24
            //2020-11-23  lijunqing  EngineEvent = Protocol Engine
//            if (strMsg.IsEmpty())
//			{
//				atsrpc_OnEngineEvent(this, TEST_STATE_DESC_STOPED);
//			}
//			else
//			{
//				atsrpc_OnEngineEvent(this, strMsg);
//			}
        }

		//停止试验时，修改标记。为下一次跳出循环做准备
		m_pCurrTestItem->m_nBreakLoopState = 0;

		if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			CGbItemBase *pItemParent = (CGbItemBase*)m_pCurrTestItem->GetParent();
			UINT nClassID = pItemParent->GetClassID();

			//父项目，MacroTest、Safety、SysParaEdit
			if ((nClassID == GBCLASSID_MACROTEST) || (nClassID == GBCLASSID_SAFETY) || (nClassID == GBCLASSID_SYSPARAEDIT))
			{
				pItemParent->m_nBreakLoopState = 0;
			}
		}
	}
	else
	{
		//shaolei 20210908  只有主TestControl下，才认定是结束
		//shaolei 2022-12-13 注释掉判断是否是主TestControl。
		//所有的TestControl都应回复TestFinished，回复的报文中通过DeviceIndex进行判断
		//if (GetParent() == NULL)
		{
			//shaolei 20220419   修改atsrpc_IsSmartTestRpc函数
			if (atsrpc_IsSmartTestRpc())
			{
				//COM调用模式下，判断是否所有测试项已经测试结束，只有测试结束，才真正导出报告
				//shaolei  20210918   
				if (Gb_IsItemsTestFinished(m_pGuideBook))
				{
					bFinish = TRUE;
				}
			}
		}
	}
#endif

	StopMacroTestOutput(TRUE);

#ifndef GUIDEBOOK_DEV_MODE
	if (m_pCurrSubTestItem != NULL)
	{
		//删除最近添加的报告数据对象

		if (bExtern)
		{
			m_pCurrSubTestItem->DeleteReport(); //2017.05.17
		}

		m_pCurrSubTestItem->SetState(TEST_STATE_STOPED);
		m_oTCtrlMsgRcv.OnCurrItemStateChanged(m_pCurrSubTestItem);

		if(m_pCurrSubTestItem->GetState() != TEST_STATE_STOPED)
		{
			//说明在SetState函数中，通过InitStateByReport()函数给测试项设置了状态，此时需要再通知AtsBench停止测试
			//shaolei 2019.06.24
            //2020-11-23  lijunqing  EngineEvent = Protocol Engine
//			if (strMsg.IsEmpty())
//			{
//				atsrpc_OnEngineEvent(this, TEST_STATE_DESC_STOPED);
//			}
//			else
//			{
//				atsrpc_OnEngineEvent(this, strMsg);
//			}
		}
	}

	OnProjectTestEnded(bFinish);
#else

#endif

	m_pCurrTestItem = NULL;
	m_pCurrSubTestItem = NULL;
	return 0;
}

//停止当前项目的测试：和资源申请配合，资源申请失败后，自动测试系统继续执行。资源调度系统申请成功
//则发送分配成功消息给自动测试，自动测试停止当前测试的项目，然后从资源分配的项目开始往下继续测试
long CTestControlBase::StopTestCurrItem()
{
	if (m_pTCtrlWnd != NULL)
	{
		m_pTCtrlWnd->StopTest();
	}
	
	HideAllTestItemUI();

#ifndef GUIDEBOOK_DEV_MODE
	//更新测试项目的测试状态，如果测试项目的状态为测试完成状态，则不更新
	//####################
	if (m_pCurrTestItem != NULL)
	{
		//删除最近添加的报告数据对象
		m_pCurrTestItem->DeleteReport(); //2017.05.17
		m_pCurrTestItem->SetState(TEST_STATE_STOPED);  //此处会根据上一次报告的状态，设置项目的状态
		m_oTCtrlMsgRcv.OnCurrItemStateChanged(m_pCurrTestItem);
	}
	else
	{
	}
#endif

	StopMacroTestOutput(TRUE);

#ifndef GUIDEBOOK_DEV_MODE
	if (m_pCurrSubTestItem != NULL)
	{
		//删除最近添加的报告数据对象
		m_pCurrSubTestItem->DeleteReport(); //2017.05.17

		m_pCurrSubTestItem->SetState(TEST_STATE_STOPED);
		m_oTCtrlMsgRcv.OnCurrItemStateChanged(m_pCurrSubTestItem);
	}
#else

#endif

	m_pCurrTestItem = NULL;
	m_pCurrSubTestItem = NULL;
	return 0;
}

long CTestControlBase::UpdateParameter(CDataGroup *pParas)
{
    CString strMacroID;

   if(! pParas->GetDataValue(STT_CMD_PARA_MacroID, strMacroID))
   {
       return -1;
   }

   if(m_pMacroTestInterface == NULL)
   {
       return -1;
   }

   if( strMacroID == _T("ManualTest") || strMacroID == _T("HarmTest") || strMacroID == _T("SequenceManuTest")
	   || strMacroID == _T("MUAccuracyTest") || strMacroID == _T("MUZeroDriftTest")
	   || strMacroID == _T("MUTimingAccurTest") || strMacroID == _T("MUPunctAccurTest") 
	   || strMacroID == _T("LineVolManuTest") || strMacroID == _T("BinaryManuTest")
	   || strMacroID == _T("PowerManuTest") || strMacroID == _T("ImpedanceManuTest")
	   || strMacroID == _T("ImpedManualTest"))
   {
       CDataGroup *pItemParas = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_ItemParas);
       return m_pMacroTestInterface->UpdateParameter(strMacroID, pItemParas);
   }

   return 0;
}

long CTestControlBase::ManualTrigger()
{
    if(m_pMacroTestInterface == NULL)
    {
        return -1;
    }

    return m_pMacroTestInterface->ManualTrigger();
}
//是否正在测试
BOOL CTestControlBase::IsNowTesting()
{
	return (m_pCurrTestItem != NULL);
}

void CTestControlBase::EditItemPara(CExBaseObject *pItem)	
{	
	m_oTCtrlMsgRcv.EditItemPara(pItem);	
}


extern CString g_strSmartTestRunMode;
void CTestControlBase::UpdateMacroCharTest_Finished(CMacroTest *pMacroTest, CReport *pReport, long &nCurrIndex)
{
	CExBaseObject *pParent = (CExBaseObject*)pMacroTest->GetParent();

	if (pParent->GetClassID() != GBCLASSID_MACROCHARITEMS)
	{
		nCurrIndex = -1;
		return;
	}

	CMacroCharItems *pMacroCharItems = (CMacroCharItems*)pParent;

	//计算TestLine。从界面CDlgMacroCharTest抄过来
	pMacroCharItems->UpdateMacroTest(pMacroTest, pReport);
	m_oTCtrlMsgRcv.OnCurrCharItemStateChanged(m_pCurrTestItem, pReport);

	if(g_strSmartTestRunMode == SmartTest_Run_Mode_Server)
	{
		//南瑞windows软件，如果绘制特性曲线图，会导致重复释放软件崩溃。临时用这个标记屏蔽
		return;
	}

	//全部测试完毕，绘制特性曲线图
	pMacroCharItems->WriteCharGraphFile();
	nCurrIndex = pMacroCharItems->GetMacroTestIndex(pMacroTest);
}

void CTestControlBase::UpdateMacroCharTest_Testing(CMacroTest *pMacroTest)
{
	if (pMacroTest == NULL)
	{
		return;
	}

	CExBaseObject *pParent = (CExBaseObject*)pMacroTest->GetParent();

	if (pParent->GetClassID() != GBCLASSID_MACROCHARITEMS)
	{
		return;
	}

	//点的模式：GetReport。搜索线的模式：GetSearchReport();
	CMacroCharItems *pMacroCharItems = (CMacroCharItems*)pParent;
	CValues oValues;
	CString strSearchRpt = m_pMacroTestInterface->GetSearchReport();
	oValues.SetValuesByString(strSearchRpt);

	//计算TestLine。从界面CDlgMacroCharTest抄过来
	pMacroCharItems->UpdateMacroTest(pMacroTest, &oValues);
	m_oTCtrlMsgRcv.OnCurrCharItemStateChanged(pMacroTest, &oValues);
}

BOOL CTestControlBase::IsRepeatTimesFinished(CMacroTest *pMacroTest)
{
	if (pMacroTest->m_nRepeatTimes > 1)
	{
		if (m_nMacroTestTimes >= GetMaxRepeatTimes(pMacroTest->m_nRepeatTimes))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	//没有重复测试的 默认返回结束
	return TRUE;
}

//测试资源如果申请失败，自动测试继续测试，分配成功后，资源管理系统发送分配成功消息给自动测试
//自动测试系统从资源分配成功失败的项目继续执行
BOOL CTestControlBase::ContinueTestByHdResReq()
{
	if (m_listHdResReqFaildItem.GetCount() == 0)
	{//没有资源分配失败的项目
		return 0;
	}

	if (m_pCurrTestItem != NULL)
	{
		StopTestCurrItem();
	}

	m_pCurrTestItem = (CGbItemBase*)m_listHdResReqFaildItem.GetHead();
	m_listHdResReqFaildItem.RemoveHead();
	m_pItemContainer->SetCurrPosByItem(m_pCurrTestItem);
	m_pCurrTestItem->SetState(TEST_STATE_ELIGIBLE);
	TestNextItem();

	return TRUE;
}

//底层功能组件消息处理函数
LRESULT CTestControlBase::OnElectricTestMsg(WPARAM wParam, LPARAM lParam)
{
#ifndef _PSX_QT_LINUX_
	CAutoSimpleLock oLock(m_oCriticSectionGridTest);
#endif
	long nEvent = wParam;


    //2020-11-24  lijunqing 处理异常消息，解决在m_pCurrTestItem==NULL的情况下无法发出事件消息
	if (m_pCurrTestItem == NULL)
	{
		if (ContinueTestByHdResReq())
		{
			return 0;
		}
		else
		{
			OnException_TCtrlMsg(nEvent, g_sLangTxt_CommunIgnored.GetString());
			//m_oTCtrlMsgRcv.OnException(nEvent, g_sLangTxt_CommunIgnored.GetString() /*_T("忽略的电气量测试功能消息......")*/, this);
			//return 0;
		}
	}
    else
    {
		UINT nClassID = m_pCurrTestItem->GetClassID();

		if (nClassID == GBCLASSID_MACROCHARITEMS)
        {
            FinishTestItemMacroCharTest((CMacroCharItems*)m_pCurrTestItem);
            return 0;
        }

		if ((nClassID != GBCLASSID_MACROTEST) && (nClassID != GBCLASSID_HDRESREQUEST))
		{
			if (ContinueTestByHdResReq())
			{
				return 0;
			}
			else
			{
				OnException_TCtrlMsg(nEvent, g_sLangTxt_CommunIgnored.GetString());
				//m_oTCtrlMsgRcv.OnException(nEvent, g_sLangTxt_CommunIgnored.GetString() /*_T("忽略的电气量测试功能消息......")*/, this);
				return 0;
			}
		}
	}

	//当前测试项目为空，可能是自动测试作为19815服务时，转发TestCmd，需要与测试仪联机
	if (m_pCurrTestItem != NULL)
	{
		if (m_pCurrTestItem->GetClassID() != GBCLASSID_HDRESREQUEST)
		{
			return OnElectricTestMsg_MacroTest(wParam, lParam);
		}
		else
		{
			return OnElectricTestMsg_ResReq(wParam, lParam);
		}
	}

	return OnElectricTestMsg_MacroTest(wParam, lParam);
}

LRESULT CTestControlBase::OnElectricTestMsg_ResReq(WPARAM wParam, LPARAM lParam)
{
	long nEvent = wParam;


	switch (nEvent)
	{
	case MTMSG_ConnectSuccess : //0,
		atsrpc_OnTestAppEvent(this, TestAppEvent_ConnectSuccess);
		m_oTCtrlMsgRcv.OnConnectSuccess(this);
		break;

	case MTMSG_ConnectFaild : //1,
		atsrpc_OnTestAppEvent(this, TestAppEvent_ConnectFaild);
		m_oTCtrlMsgRcv.OnException(nEvent, g_sLangTxt_OnlineFail.GetString() /*_T("联机失败")*/, this);
		StopTestExtern();
		break;

	case MTMSG_TestBegin : //3,
		atsrpc_OnTestAppEvent(this, TestAppEvent_TestBegin);

		if(m_pCurrTestItem != NULL)
		{
			m_oTCtrlMsgRcv.OnCurrItemStateChanged(m_pCurrTestItem);
		}
		break;

	case MTMSG_TestFinished : //4,
		atsrpc_OnTestAppEvent(this, TestAppEvent_TestFinished);

		if(m_pCurrTestItem != NULL)
		{
			FinishTestItemHdResReqest((CHdResReqest*)m_pCurrTestItem);
		}

		break;

	case MTMSG_CommError : //5,
		atsrpc_OnTestAppEvent(this, TestAppEvent_CommError);
		m_oTCtrlMsgRcv.OnException(nEvent,g_sLangTxt_ParaDnldFail.GetString() /*_T("------参数下载失败")*/, this);
		StopTestExtern();
		break;

	case MTMSG_Not_Surport : //6,
		//2020-11-24  lijunqing 处理异常消息，解决在m_pCurrTestItem==NULL的情况下无法发出事件消息
		if (m_pCurrTestItem != NULL)
		{
			CHdResReqest *pResReqest = (CHdResReqest*)m_pCurrTestItem;
			CString strMsg;
			strMsg.Format(g_sLangTxt_TestUnsuptFctn.GetString()/*L"------测试仪器底层功能接口不支持测试功能[%s]"*/,  pResReqest->m_strType.GetString());
			m_oTCtrlMsgRcv.OnException(nEvent, strMsg, this);
		}

		StopTestExtern();
		break;

	case MTMSG_TestOverTime :
		atsrpc_OnTestAppEvent(this, TestAppEvent_TestOverTime);
		StopTestExtern();
		break;

	default:
		break;
	}

	return 0;
}

//电气量项目，多装置时，多个TestControl同时测试，因此事件同时触发
LRESULT CTestControlBase::OnElectricTestMsg_MacroTest(WPARAM wParam, LPARAM lParam)
{
	if (g_nLog_TestControl_Msg == 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("CTestControlBase::OnElectricTestMsg(%08X, %08X)"), wParam, lParam);
	}

	DWORD dwBegin = ::GetTickCount();
	long nEvent = wParam;

	switch (nEvent)
	{
    case MTMSG_ConnectSuccess : //0,
		atsrpc_OnTestAppEvent(this, TestAppEvent_ConnectSuccess);
		OnConnectSuccess_TCtrlMsg();
		//m_oTCtrlMsgRcv.OnConnectSuccess(this);
		break;

    case MTMSG_ConnectFaild : //1,
		atsrpc_OnTestAppEvent(this, TestAppEvent_ConnectFaild);
		OnException_TCtrlMsg(nEvent, g_sLangTxt_OnlineFail.GetString());
		//m_oTCtrlMsgRcv.OnException(nEvent, g_sLangTxt_OnlineFail.GetString() /*_T("联机失败")*/, this);

		if (m_pCurrTestItem != NULL)
		{
			//shaolei 2025-3-4 电气量项目联机失败时，当前项目为空，则不触发停止逻辑
			StopTestExtern();
		}
		
		break;

    case MTMSG_ConnectConfig : //2,
        //2020-11-24  lijunqing 处理异常消息，解决在m_pCurrTestItem==NULL的情况下无法发出事件消息
        if (m_pCurrTestItem != NULL)
        {
            TestItemMacroTestChildItem((CMacroTest*)m_pCurrTestItem);
        }
		break;

    case MTMSG_TestBegin : //3,
		atsrpc_OnTestAppEvent(this, TestAppEvent_TestBegin);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_TestStartInf/*_T("------收到电气量测试开始消息【%s】")*/, m_pCurrTestItem->m_strName);
		TestFirstSubItems_MacroTest(TRUE);
        if(m_pCurrTestItem != NULL)
        {
            m_oTCtrlMsgRcv.OnCurrItemStateChanged(m_pCurrTestItem);//待处理。电气量项目的测试开始事件。需确认
            UpdateMacroCharTest_Testing((CMacroTest*)m_pCurrTestItem); //更新特性曲线的过程状态
        }
		break;

    case MTMSG_TestFinished : //4,
		atsrpc_OnTestAppEvent(this, TestAppEvent_TestFinished);

        if(m_pCurrTestItem != NULL)
        {
			//UpdateMacroCharTest_Testing((CMacroTest*)m_pCurrTestItem);  //更新特性曲线的过程状态			
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("收到电气量测试结束消息【%s】"), m_pCurrTestItem->m_strName.GetString());
            FinishTestItemMacroTest((CMacroTest*)m_pCurrTestItem);
        }
		m_nMacroTestReTestTimes = 0;
		break;

    case MTMSG_SearchPointFinished : //5,
		atsrpc_OnTestAppEvent(this, TestAppEvent_SearchPointFinished);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("收到电气量测试结束消息【%s】"), m_pCurrTestItem->m_strName);
        if(m_pCurrTestItem != NULL)
        {
			//此处应当用过程还是结束？
            UpdateMacroCharTest_Testing((CMacroTest*)m_pCurrTestItem);  //更新特性曲线的过程状态
        }
		break;

    case MTMSG_CommError : //5,
		atsrpc_OnTestAppEvent(this, TestAppEvent_CommError);
		OnException_TCtrlMsg(nEvent, g_sLangTxt_ParaDnldFail.GetString());
		//m_oTCtrlMsgRcv.OnException(nEvent,g_sLangTxt_ParaDnldFail.GetString() /*_T("------参数下载失败")*/, this);
		StopTestExtern();
		break;

    case MTMSG_Not_Surport : //6,
        //2020-11-24  lijunqing 处理异常消息，解决在m_pCurrTestItem==NULL的情况下无法发出事件消息
        if (m_pCurrTestItem != NULL)
        {
            CMacroTest *pMacroTest = (CMacroTest*)m_pCurrTestItem;
            CMacroTestPara *pPara = pMacroTest->GetMacroTestPara();
            CString strMsg;
            strMsg.Format(g_sLangTxt_TestUnsuptFctn.GetString()/*L"------测试仪器底层功能接口不支持测试功能[%s]"*/,  pPara->GetMacroID().GetString());
			OnException_TCtrlMsg(nEvent, strMsg);
            //m_oTCtrlMsgRcv.OnException(nEvent, strMsg, this);
        }

		StopTestExtern();
		break;

    case MTMSG_ManualTestBegin : //7,
		break;

    case MTMSG_ManualTestReturn : //8,
		break;

    case MTMSG_ManualTestStop : //9,
		break;

    case MTMSG_ShowCurItem : //10
		break;

    case MTMSG_TestOverTime :
		atsrpc_OnTestAppEvent(this, TestAppEvent_TestOverTime);

        //2020-11-24  lijunqing 处理异常消息，解决在m_pCurrTestItem==NULL的情况下无法发出事件消息
        if (m_pCurrTestItem == NULL)
        {
            StopTestExtern();
            break;
        }

		if (m_pCurrTestItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest*)m_pCurrTestItem;
			CMacroTestPara *pPara = pMacroTest->GetMacroTestPara();
			CString strMsg;
            strMsg.Format(g_sLangTxt_TestOverTimeS.GetString() /*_T("------测试仪器底层测试功能[%s]测试超时, %d ms后重新测试")*/,  pPara->GetMacroID().GetString(), TIMER_TEST_FOR_OVERTIME_LONG);
			OnException_TCtrlMsg(nEvent, strMsg);
			//m_oTCtrlMsgRcv.OnException(nEvent, strMsg, this);

			//如果有子通讯命令，并且是同步启动的命令，则终止测试
			if (m_pCurrSubTestItem != NULL)
			{
				if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
				{
					CCommCmd *pCommCmd = (CCommCmd*)m_pCurrSubTestItem;
					CCmd *pCmd = pCommCmd->GetCmd();

					if (pCmd->IsBeginModeSynchro())
					{
						StopTest();
						break;
					}
				}
			}

			m_nMacroTestReTestTimes++;

			//电气量测试项目，停止装置输出
			StopMacroTestOutput();
			ASSERT (m_pTCtrlWnd != NULL);

			if (m_nMacroTestReTestTimes < GetCmmMaxRetryTimes())
			{
				m_pTCtrlWnd->m_pTestItemRef = m_pCurrTestItem;
				m_pTCtrlWnd->SetTimer(TIMER_TEST_FOR_OVERTIME, TIMER_TEST_FOR_OVERTIME_LONG, NULL);
			}
			else
			{
				m_pCurrTestItem->SetRsltJdg(0);
				UpdateStateAfterFinishTestItem(m_pCurrTestItem);

				//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
				//因此单独执行
				WriteItemTempFile(m_pCurrTestItem);

				m_nMacroTestReTestTimes = 0;
				TestNextItem();				
			}
		}

		break;

    case MTMSG_AppWarning :
    case MTMSG_AppError :
		atsrpc_OnTestAppEvent(this, TestAppEvent_AppError);
		OnElectricTestAppMsg( wParam, lParam);
		break;
	case MTMSG_TestManualStop:
		atsrpc_OnTestAppEvent(this, TestAppEvent_TestStoped);
		OnStopTest_TCtrlMsg(0);
		//m_oTCtrlMsgRcv.OnStopTest(0, this);  //0表示测试停止
		StopTestExtern();
		break;
	case MTMSG_SearchPointReport : //16,
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("+++for debug+++ CTestControlBase::OnElectricTestMsg_MacroTest-->SearchPointReport"));
		if(m_pCurrTestItem != NULL)
		{
			UpdateMacroCharTest_Testing((CMacroTest*)m_pCurrTestItem);  //更新特性曲线的过程状态
		}
		break;
		

	default:
		break;
	}

	DWORD dwEnd = ::GetTickCount();

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("OnElectricTestMsg::TimeLong=%d"), dwEnd - dwBegin);

	return 0;
}

//@@wParam代表装置的编号和索引,  lParam:消息值
//规约组件消息处理函数
LRESULT CTestControlBase::OnCommCommandMsg(WPARAM wParam, LPARAM lParam)
{
#ifndef _PSX_QT_LINUX_
    CAutoSimpleLock oLock(m_oCriticSectionGridTest);
#endif

	if (m_nRunProcedureType == ProcedureType_EngineCmd)
	{
		ContinueExecutePpEngineCmd(this);
		
		return 0;
	}

	m_nCommCmdErrorState = 0;
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("    <<<<<<OnCommCommandMsg(%d, %d)"), wParam, lParam);

	if ( lParam == 1 )
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_CommunOverTime /*L"通讯超时，测试终止！"*/);
		StopTestExtern();
		return 0;
	}

	//释放注册的过程消息

    if (!UnRegisterProcedureMsg(wParam, lParam, m_pTCtrlWnd->GetSafeHwnd()))
	{
		StopTestExtern();
		return 0;
	}

	CCommCmd *pCommCmd = NULL;

	if (m_pCurrSubTestItem != NULL)
	{
		if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			pCommCmd = (CCommCmd*)m_pCurrSubTestItem;
		}
	}
	else
	{
		if (m_pCurrTestItem != NULL)
		{
			if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
			{
				pCommCmd = (CCommCmd*)m_pCurrTestItem;
			}
		}
	}

	if (lParam == engineCommError)
	{
		atsrpc_OnEngineEvent(this, EngineEvent_CommError);
		m_oTCtrlMsgRcv.OnEngineEvent(this, EngineEvent_CommError);
		//2018-11-6  通讯错误测试模式下，不处理错误，当做测试成功来处理
		if (!CTCtrlCntrConfig::Get_EngineUseCommTestMode())
		{
			m_nCommCmdErrorState = 1;

			if (pCommCmd != NULL)
			{
				CCmd *pCmd = pCommCmd->GetCmd();

				if (pCmd->m_nMaxRetrytimes == -1)
				{
					FinishTestItemCommCmd(pCommCmd);
				}
				else
				{
					//if (m_nCommCmdReCommTimes >= pCmd->m_nMaxRetrytimes)
					if (m_nCommCmdReCommTimes >= GetCmmMaxRetryTimes())
					{
						m_nCommCmdReCommTimes = 0;
                        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunTestStop.GetString()/*L"通讯过程中出现错误，测试终止"*/);
						StopTestExtern();
					}
					else
					{
						m_pTCtrlWnd->m_pTestItemRef = pCommCmd;
						m_nCommCmdReCommTimes++;
                        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ReCommunD.GetString()/*L"通讯过程中出现错误，重新通讯第%d次，共%d次"*/, m_nCommCmdReCommTimes, GetCmmMaxRetryTimes());//pCmd->m_nMaxRetrytimes);
						m_pTCtrlWnd->SetTimer(TIMER_RETRY_CMM_CMD, pCmd->GetDelayBeforeRetry(), NULL);
					}
				}
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_CommunFalse.GetString()/* L"通讯过程中出现错误，pCommCmd==NULL"*/);
			}

			return 0;
		}
	}

	atsrpc_OnEngineEvent(this, EngineEvent_CommFinish);

	if (pCommCmd != NULL)
	{
		FinishTestItemCommCmd(pCommCmd);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunFalse.GetString()/*L"通讯过程中出现错误，pCommCmd == NULL"*/);
	}

	return 0;
}

//Safety完成的消息处理函数
LRESULT CTestControlBase::OnSafetyTestFinished(WPARAM wParam, LPARAM lParam)
{
	if (m_bSafetyScriptStopByRecord)
	{
		m_bSafetyScriptStopByRecord = FALSE;
		StopTest();
		return 0;
	}
	CGbItemBase *pItem = (CGbItemBase*)wParam;
//	ASSERT (pItem == m_pCurrTestItem);

	if (lParam == 1)
	{
		FinishTestItemSafety( (CSafety*)pItem );
	}
	else
	{//停止测试
		StopTestExtern(_T(""), TRUE);
	}

	return 0;
}

//系统参数录入完成
LRESULT CTestControlBase::OnSysParaEditTestFinished(WPARAM wParam, LPARAM lParam)
{
	CGbItemBase *pItem = (CGbItemBase*)wParam;
	ASSERT (pItem == m_pCurrTestItem);

	if (lParam == 1)
	{
		FinishTestItemSysParaEdit( (CSysParaEdit *)pItem);
	}
	else
	{//停止测试
		StopTestExtern(_T(""), TRUE);
	}

	return 0;
}

//通讯命令手动录入结果数据
LRESULT CTestControlBase::OnCommCmdMamualTestFinished(WPARAM wParam, LPARAM lParam)
{
	CCommCmd *pCommCmd = NULL;

	if (m_pCurrSubTestItem != NULL)
	{
		pCommCmd = (CCommCmd*)m_pCurrSubTestItem;
	}
	else
	{
		pCommCmd =  (CCommCmd*)m_pCurrTestItem;
	}

	return 0;
}

//手动测试消息处理函数
LRESULT CTestControlBase::OnManualTestMsg(WPARAM wParam, LPARAM lParam)
{
	long nEvent = wParam;

	return 0;
}

//@@wParam代表装置的编号和索引,lParam消息值
CPpDeviceRef* CTestControlBase::FindPpDeviceRef(WPARAM wParam)
{
	//首先获取当前正在连接的Device
	CPpDeviceRef *p = m_oDeviceRefs.GetPpDeviceConnecting();

	if (p != NULL)
	{
		return p;
	}

	return m_oDeviceRefs.FindPpDeviceRef(wParam);
}

CProtocolDeviceInterface* CTestControlBase::FindPpDevice(WPARAM wParam)
{
	CProtocolDeviceInterface* oPpDevice = m_oDeviceRefs.FindByID(wParam);
	return oPpDevice;
}

//此函数中所有测试代码，均是由于四方测试时，SdmEngine发送联机成功消息，SmartTest这边没有正确响应   shaolei 2019.07.30
LRESULT CTestControlBase::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
	//测试代码
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("      CTestControlBase::OnEngineSystemMessage    lParam = %d"), (long)lParam);
	if (m_nRunProcedureType == ProcedureType_EngineCmd)
	{
		//测试代码
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("      CTestControlBase::OnEngineSystemMessage    m_nRunProcedureType == ProcedureType_EngineCmd 函数返回"));
		return 0;
	}

	CPpDeviceRef *pPpDeviceRef = FindPpDeviceRef(wParam);

#ifndef _PSX_QT_LINUX_
	ASSERT (pPpDeviceRef != NULL);
#endif

	if (pPpDeviceRef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("OnEngineSystemMessage Error: FindPpDeviceRef(%d) == NULL"), wParam);
		StopTestExtern();
		return 0;
	}
	
	pPpDeviceRef->SetConnectState(FALSE);

	if (m_pCurrTestItem == NULL)
	{
		HideAllTestItemUI();
		return 0;
	}

	BOOL bCommCmd = FALSE;

	if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		bCommCmd = TRUE;
	}
	else
	{
		if (m_pCurrSubTestItem != NULL)
		{
			if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
			{
				bCommCmd = TRUE;
			}
			else if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_SAFETY)
			{
				if (lParam == engineConnectDeviceSuccessful)
				{
					//m_bPpDeviceConnectSucc = TRUE;
					//pPpDeviceRef->m_bConnected = TRUE;
					pPpDeviceRef->SetConnectState(TRUE);
				}
			}
		}
	}

	if (m_pCurrTestItem != NULL)
	{
		if (m_pCurrTestItem->GetClassID() == GBCLASSID_SAFETY)
		{
			if (lParam == engineConnectDeviceSuccessful)
			{
				//m_bPpDeviceConnectSucc = TRUE;
				//pPpDeviceRef->m_bConnected = TRUE;
				pPpDeviceRef->SetConnectState(TRUE);
			}
		}
	}

	if (!bCommCmd)
	{
		//CLogPrint::LogString(XLOGLEVEL_ERROR, L"OnEngineSystemMessage: not commcmd");
		return 0;
	}

	CCommCmd *pCmmCmd = (CCommCmd*)(m_pTCtrlWnd->m_pTestItemRef);

	if (pCmmCmd == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("OnEngineSystemMessage Error(%d) : m_pTCtrlWnd->m_pTestItemRef== NULL"), wParam);
		return 0;
	}

	CCmd *pCmd = pCmmCmd->GetCmd();
	long nGetCmmMaxRetryTimes = GetCmmMaxRetryTimes();

	switch (lParam)
	{
	case engineConnectDeviceFailed:
		atsrpc_OnEngineEvent(this, EngineEvent_ConnectDeviceFailed);
		m_oTCtrlMsgRcv.OnEngineEvent(this, EngineEvent_ConnectDeviceFailed);
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_TestStop2/*L"连接设备失败，测试终止"*/);
	
		//2018-11-6 李俊庆   通讯错误测试模式
		if (CTCtrlCntrConfig::Get_EngineUseCommTestMode())
		{
			pPpDeviceRef->SetPpDeviceCommError(TRUE);
			SetTestError(_T("通讯错误"));
			pCmmCmd->SetRsltJdg(0);
		}
		else
		{
			StopTestExtern();
			break;
		}

	case engineConnectDeviceSuccessful:
		atsrpc_OnEngineEvent(this, EngineEvent_ConnectDeviceSuccessful);
		m_oTCtrlMsgRcv.OnEngineEvent(this, EngineEvent_ConnectDeviceSuccessful);
		//m_bPpDeviceConnectSucc = TRUE;
		//CLogPrint::LogString(XLOGLEVEL_ERROR, L"连接设备成功");
		//pPpDeviceRef->m_bConnected = TRUE;
		pPpDeviceRef->SetConnectState(TRUE);

		//@@判断是否所有的设备都连接成功，如果连接成功，则进行通讯命令的处理，否则，接着连接下一个通讯命令
		if (m_oDeviceRefs.IsAllDeviceConnectSucc())
		{
			//启动规约引擎判断时钟
#ifdef _use_ppengine_exception
			//20161216：屏蔽规约引擎异常
			m_pTCtrlWnd->SetPpEngineTimer();
#endif

			//连接设备成功，则更新逻辑设备
			UpdateDvmLdeviceID();

            CLogPrint::LogString(XLOGLEVEL_DEBUG,g_sLangTxt_StartCommun /*L"连接设备成功，开始执行通讯命令"*/);
			ExecuteTestItemCommCmd(pCmmCmd);
		}
		else
		{
            CLogPrint::LogString(XLOGLEVEL_DEBUG, g_sLangTxt_ContNextItem/*L"继续连接下一个设备"*/);
			CreatePpEngineDevice(pCmmCmd);
		}

		break;

	case engineCommError:
		atsrpc_OnEngineEvent(this, EngineEvent_CommError);
		m_oTCtrlMsgRcv.OnEngineEvent(this, EngineEvent_CommError);
		//2018-11-6  通讯错误测试模式下，不处理错误，当做测试成功来处理
		if (CTCtrlCntrConfig::Get_EngineUseCommTestMode())
		{
			OnCommCommandMsg(wParam, lParam);
			break;
		}

		if (m_nCommCmdReCommTimes >= nGetCmmMaxRetryTimes && nGetCmmMaxRetryTimes > 0)
		//if (m_nCommCmdReCommTimes >= pCmd->m_nMaxRetrytimes)
		{
			m_nCommCmdReCommTimes = 0;
           
            CTCtrlCntrConfig *pCtrlConfig = g_theSmartTestBaseApp->GetCntrConfig();

			if (SkipStxmlWhenWSetsError(Get_ID_SkipModeWhenWSetsErro(pCtrlConfig->m_strSkipStxmlWhenWSetsError), pCmmCmd))
			{
			}
			else
			{
				StopTestExtern();
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunTestStop.GetString()/*L"通讯过程中出现错误，测试终止"*/);
			}
		}
		else
		{
			m_nCommCmdErrorState = 1;

			if (pCmd->m_nMaxRetrytimes == -1)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestContS.GetString()/*L"【%s】：【%s】忽略通讯过程中出现错误，测试继续"*/, m_strGbBinaryFileName.GetString(), pCmmCmd->m_strName.GetString());
				FinishTestItemCommCmd(pCmmCmd);
				return 0;
			}

			if (nGetCmmMaxRetryTimes == 0)
			{
				StopTestExtern();
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunTestStop.GetString()/*L"通讯过程中出现错误，测试终止"*/);
				return 0;
			}

			m_pTCtrlWnd->m_pTestItemRef = pCmmCmd;
			m_nCommCmdReCommTimes++;
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ReCommunD.GetString()/*L"通讯过程中出现错误，重新通讯第%d次，共%d次"*/, m_nCommCmdReCommTimes, GetCmmMaxRetryTimes());//pCmd->m_nMaxRetrytimes);
			m_pTCtrlWnd->SetTimer(TIMER_RETRY_CMM_CMD, pCmd->GetDelayBeforeRetry(), NULL);
		}

		break;

	case engineException:
		atsrpc_OnEngineEvent(this, EngineEvent_CommError);
		m_oTCtrlMsgRcv.OnEngineEvent(this, EngineEvent_CommError);
		TerminateProgram(g_strPpMmsEngineExeName);
		break;

	default:
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_TestStop3/*L"通讯引擎异常，测试终止"*/);
		StopTestExtern();
		break;
	}
	
	return 0;
}

void CTestControlBase::OnPpEngineExceptionTimer()
{
#ifdef _use_ppengine_exception
	if (m_pGuideBook->m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		if (IsProgramExist(g_strPpMmsEngineExeName))
		{
            if (g_theTCtrlCntrApp->IsPpMmsEngineException())
			{
				TerminateProgram(g_strPpMmsEngineExeName);
			}
			else
			{
				return;
			}
		}
	}
	else if (m_pGuideBook->m_strPpEngineProgID == g_strPpEngineProgID)
	{
		if (IsProgramExist(g_strPpEngineExeName))
		{
			return;
		}
	}
	else
	{
		return;
	}

	CExBaseObject *pCurrTestItem = m_pCurrTestItem;
	m_pTCtrlWnd->KillPpEngineTimer();
	StopTest();

	if (pCurrTestItem == NULL)
	{
		return;
	}

	m_oDeviceRefs.ReleaseAllDevice();
    g_theSmartTestBaseApp->ReleasePpEngine(m_pGuideBook->m_strPpEngineProgID);

	AddBeforeTestItems(pCurrTestItem);

	m_pCurrTestItem = m_pItemContainer->GetCurrItem();
	TestItem(m_pCurrTestItem);
#endif
}

void CTestControlBase::AddBeforeTestItems(CExBaseObject *pCurrTestItem)
{
	CExBaseList listQuery, listBftItem;
	Gb_QueryBftAftItem(m_pGuideBook, pCurrTestItem, listQuery);
	Gb_QueryBftItem(listQuery, listBftItem);
	m_pItemContainer->AddItemsBeforeCurr(listBftItem);

	listQuery.RemoveAll();
	listBftItem.RemoveAll();
}

CItems* CTestControlBase::GetStxmlItemsRoot(CExBaseList *pItem)
{
	CExBaseList *pParent = (CExBaseList*)pItem->GetParent();
	CItems *pItemsFind = NULL;

	while (pParent != NULL)
	{
		if (pParent->FindByID(GBID_BeforeTest_) != NULL && pParent->FindByID(GBID_AfterTest_) != NULL)
		{
			pItemsFind = (CItems*)pParent;
			break;
		}

		pParent = (CExBaseList*)pParent->GetParent();
	}

	return pItemsFind;
}

BOOL CTestControlBase::SkipStxmlWhenWSetsError(long nSkipStxmlWhenWSetsError, CCommCmd *pCommCmd)
{
	if (nSkipStxmlWhenWSetsError == ID_SkipModeWhenWSetsError_None)
	{
		return FALSE;
	}

	if (nSkipStxmlWhenWSetsError == ID_SkipModeWhenWSetsError_Stxml)
	{
		return SkipStxml(pCommCmd);
	}

	if (nSkipStxmlWhenWSetsError == ID_SkipModeWhenWSetsError_ParentItems)
	{
		return SkipItems(pCommCmd);
	}

	if (nSkipStxmlWhenWSetsError == ID_SkipModeWhenWSetsError_Item)
	{
		return SkipItem(pCommCmd);
	}

	return SkipItem(pCommCmd);
}

BOOL CTestControlBase::SkipStxml(CCommCmd *pCommCmd)
{
	//如果不是修改定值，则返回
	if (!pCommCmd->IsWrite())
	{
		return FALSE;
	}

	CString strCmdID = pCommCmd->m_strCommCmdID;
	strCmdID.MakeLower();

	if (strCmdID != _T("writesetting"))
	{
		return FALSE;
	}

	//获取子模板实例化的项目路径
	CItems *pItemsFind = GetStxmlItemsRoot(pCommCmd);
	
	if (pItemsFind == NULL)
	{
		return FALSE;
	}

	SkipItemsAndTest(pItemsFind);

	return TRUE;
}

BOOL CTestControlBase::SkipItems(CCommCmd *pCommCmd)
{
	//获取子模板实例化的项目路径
	CExBaseObject *pParent = (CExBaseObject*)pCommCmd->GetParent();

	while (pParent->GetClassID() != GBCLASSID_ITEMS)
	{
		pParent = (CExBaseObject*)pParent->GetParent();
	}

	CItems *pItemsFind = (CItems*)pParent;

	if (pItemsFind == NULL)
	{
		return FALSE;
	}

	SkipItemsAndTest(pItemsFind);

	return TRUE;
}

BOOL CTestControlBase::SkipItem(CCommCmd *pCommCmd)
{
	pCommCmd->SetState(TEST_STATE_SKIP);

	CGbItemBase *pNext = m_pItemContainer->GetNextItem();
	SkipTestNext(pNext);

	return TRUE;
}

void CTestControlBase::SkipItemsAndTest(CItems *pItems)
{
	Gb_SetItemsAllItemState(pItems, TEST_STATE_SKIP);

	//获取下一个项目对象
	CGbItemBase *pNext = m_pItemContainer->GetNextItem();
	CGbItemBase *pNextFind = NULL;

	while (pNext != NULL)
	{
		if (pNext->HasParent(pItems))
		{
			pNext = m_pItemContainer->GetNextItem();;
		}
		else
		{
			pNextFind = pNext;
			break;
		}
	}

	SkipTestNext(pNextFind);
}

void CTestControlBase::SkipTestNext(CGbItemBase *pNextFind)
{
	if (pNextFind != NULL)
	{
		m_pCurrTestItem = pNextFind;
		TestItem(pNextFind);
	}
	else
	{
		//所有测试已经完成，设置当前测试项目为0
		m_nCurrTestItemIndex = 0;
		m_pCurrTestItem = NULL;

		//整个测试完成，发送测试完成消息
		StopTest();

       
        g_theSmartTestBaseApp->FireTestFinishMessage();
	}
}

BOOL CTestControlBase::BreakItems()
{
	if (m_nBreakItemsLevel < 0)
	{
		return FALSE;
	}

	if (m_pCurrTestItem == NULL)
	{
		return FALSE;
	}

	CItems *pItemsFind = (CItems*)m_pCurrTestItem->GetAncestorByDepth(m_nBreakItemsLevel);

	if (pItemsFind == NULL)
	{
		m_nBreakItemsLevel = -1;
		return FALSE;
	}

	m_nBreakItemsLevel = -1;
	SkipItemsAndTest(pItemsFind);
	return TRUE;
}

//组织容器
long CTestControlBase::AddEnableFilter(long nEnable/* =1 */)
{
	ASSERT(m_pItemContainer != NULL);
	long nEnableFilter = m_pItemContainer->CreateAttrFilter(GbFilterAttrEnable,GbFilterOptrEqual,nEnable);
	
	return nEnableFilter;
}

long CTestControlBase::AddShowFilter(long nShow/* =1 */)
{
	ASSERT(m_pItemContainer != NULL);
	long nShowFilter = m_pItemContainer->CreateAttrFilter(GbFilterAttrShow,GbFilterOptrEqual,nShow);

	return nShowFilter;
}

long CTestControlBase::AddIndexFilter(long nIndex)
{
	ASSERT(m_pItemContainer != NULL);
	long nBeginFilter = m_pItemContainer->CreateAttrFilter(GbFilterAttrIndex,GbFilterOptrEqual,nIndex);

	return nBeginFilter;
}

long CTestControlBase::AddIndexFilter2(long nBeginIndex, long nEndIndex/* =-1 */)
{
	ASSERT(m_pItemContainer != NULL);
	long nBeginFilter = m_pItemContainer->CreateAttrFilter(GbFilterAttrIndex,GbFilterOptrMoreThanEqual,nBeginIndex);
	long nEndFilter = m_pItemContainer->CreateAttrFilter(GbFilterAttrIndex,GbFilterOptrLessThanEqual,nEndIndex);
	long nReturn = m_pItemContainer->CreateFilter(nBeginIndex,GbFilterOptrAnd,nEndFilter);

	return nReturn;
}

long CTestControlBase::AddStateFilter(long nState)
{
	ASSERT(m_pItemContainer != NULL);
	return 0;
}

long CTestControlBase::AddTKidFilter(long nTKid)
{
	ASSERT(m_pItemContainer != NULL);
	return 0;
}

long CTestControlBase::AddEnableShowFilter(long nEnable, long nShow)
{
	ASSERT(m_pItemContainer != NULL);
	return 0;
}

long CTestControlBase::AddEnableShowStateFilter(long nEnable, long nShow, long nState)
{
	ASSERT(m_pItemContainer != NULL);
	return 0;
}

//测试项目
long CTestControlBase::TestFirstItem()
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);
    g_theSmartTestBaseApp->InitPpEngineShowSpyWnd();

	m_nMacroTestTimes = 0;
	InitAfterMacroTestItemsChanged();
	m_nCommCmdTestTimes = 0;
	m_nCommCmdCurrDeviceIndex = 0;

	m_pCurrTestItem = m_pItemContainer->GetFirstItem();

	if (m_pCurrTestItem != NULL)
	{
        //当确认可以测试时，才发送消息  shaolei 20201212
		OnTestBegin_TCtrlMsg();
        //m_oTCtrlMsgRcv.OnTestBegin(this);
		BackRptsBeforeTest(m_pCurrTestItem);
		TestItem(m_pCurrTestItem);
        return 1;
	}
	else
	{
        CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoTestItem.GetString() /*_T("没有需要测试的项目！")*/);
        return 0;
	}
}

BOOL CTestControlBase::IsEncrypt()
{
	if (m_oTickCount32.GetTickCountLong(FALSE) > ENCRYPT_TEST_TIMELONG)
	{
		m_oTickCount32.Enter();

#ifndef AUTOTEST_DEMO
		//if (!Encrypt_IsEncrypt(FETUREID_AUTOTEST))
       
		//if (!Encrypt_IsEncrypt(FETUREID_AUTOTEST))
        if (!g_theSmartTestBaseApp->ats_IsRegisterTrue(FALSE, TRUE))
		{
			StopTestExtern();
			//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("你使用的系统没有授权"));
			return FALSE;
		}
#endif

	}

	return TRUE;
}

long CTestControlBase::TestNextItem()
{
	m_nHasTestItemCount++;

	if (m_nHasTestItemCount > CTCtrlCntrConfig::GetSaveReportGap())
	{
		SaveReport();
		//mem_AdjustTokenPrivilegesForNT();
#ifndef _PSX_QT_LINUX_
        mem_EmptyAllSet();
#endif
        m_nHasTestItemCount = 0;
	}

	//测试下一个项目之前，填写Items的报告结果数据
	if (m_pCurrTestItem != NULL)
	{
		CItems *pItems = (CItems*)m_pCurrTestItem->GetFirstParentItems();
		ASSERT (pItems != NULL);

		if (pItems != NULL)
		{
			FillParentItemsReport(pItems);
		}

		if (Gb_IsItemsTestFinished(m_pGuideBook))
		{
			SetTestEndTime();//m_pGuideBook->SetTestEndTime();
			CReport *pReport = m_pGuideBook->GetReport(-1);
			//此处只需要更新TestEndTime的报告即可。shaolei 20220507
			CReportMap *pMap = m_pGuideBook->GetReportMap();
			CRptData *pRptData = (CRptData *)pMap->FindByID(g_strGbGlobalData_TestEndTime);

			if (m_pReportFill != NULL && pRptData != NULL)
			{
				m_pReportFill->FillReport(pRptData, pReport);
			}
			//FillReport(pReport, 0);

			//所有的测试完成，自动导出xml格式报告数据文件  2019-10-12  lijq
			SaveFinalXMLReport(); 
		}

		//m_dwReserved：用于记录和保存SystemReport的表格，清空
		ClearSysRptFill(m_pCurrTestItem);
	}

	if (m_nStopTestByError == 1)
	{
		m_pCurrTestItem = NULL;
		m_pCurrSubTestItem = NULL;
		return 0;
	}

	if (BreakItems())
	{
		return 0;
	}


	//2026-6-18  lijunqing 为了资源申请部分项目的方便，测试完毕，立即从容器去掉当前项目
	//从而简化项目执行流程的算法
	CGbItemBase *pItem = m_pCurrTestItem;
	CGbItemBase *pNext = m_pItemContainer->GetNextItem();
	m_pItemContainer->RemoveItemTestFinished(pItem);

	if (pNext != NULL)
	{
		//如果下一个项目为非电气量项目，并且当前项目为电气量项目，则停止输出
		if (m_pCurrTestItem != NULL)
		{
			
		}

		if (m_pCurrTestItem != NULL)
		{
			if (m_pCurrTestItem->GetClassID() == GBCLASSID_MACROTEST
				&& pNext->GetClassID() != GBCLASSID_MACROTEST)
			{
				StopMacroTestOutput();
			}
		}

		m_pCurrTestItem = pNext;
		TestItem(pNext);
	}
	else
	{
		//所有测试已经完成，设置当前测试项目为0
		m_nCurrTestItemIndex = 0;
		m_pCurrTestItem = NULL;

		//整个测试完成，发送测试完成消息
		StopTest();

		//shaolei  20210608
		//所有的测试完成，自动导出xml格式报告数据文件  2019-10-12  lijq
		SaveFinalXMLReport();  
       
        g_theSmartTestBaseApp->FireTestFinishMessage();

		//再次关闭所有窗口，销毁所有窗口
		DestroyAllTestItemUI();
	}

	return 0;
}

void CTestControlBase::GotoItem(CGbItemBase *pGotoItem)
{
	m_pItemContainer->GotoItem(pGotoItem);
}

void CTestControlBase::SetTestEndTime()
{
	m_pGuideBook->SetTestEndTime();
}

void CTestControlBase::SetTestError(const CString &strTestError)
{
	m_pGuideBook->SetTestError(strTestError);
	FillGlobalDatasRpt();
}

void CTestControlBase::SetTestTime(CDvmData *pTestBeginTime, CDvmData *pTestEndTime)
{
	m_pGuideBook->SetTestTime(pTestBeginTime, pTestEndTime);
}

BOOL CTestControlBase::HasNextItemNeedTest()	
{	
	BOOL bHas = ! (m_pItemContainer->ReachTailPos() );

	if (bHas)
	{
		return bHas;
	}

	if (m_pCurrSubTestItem != NULL)
	{
		bHas = HasNextSubItem(m_pCurrSubTestItem);
	}

	return bHas;	
}

void CTestControlBase::FillGlobalDatasRpt()
{
	CReport *pReport = m_pGuideBook->GetReport(-1);
	ASSERT (pReport != NULL);
	FillReport(pReport, 0);
}

void CTestControlBase::SetTestItemState(CGbItemBase* pItem, UINT nState)
{
	pItem->SetState(nState);
	//pItem->SetRsltJdg(1);
}

long CTestControlBase::TestItem(CGbItemBase* pItem)
{
	//2019.7.15   DB模式下，清除了项目的相关数据
	//Test_OpenTempBinaryFile(pItem);

// 	if (!IsEncrypt())
// 	{
// 		return 0;
// 	}
	ClearGotoItemEx();

	m_bCanRunCommCmdFinalResultScript = FALSE;
	m_pCurrReport = NULL;
 
	//测试第一个项目，填写全局数据
	BOOL bIsFirst = m_pGuideBook->IsTestFirstItem();

	if (bIsFirst)
	{
		m_pGuideBook->SetTestBeginTime();
		m_pGuideBook->AddReportDatas_GlobalDatas();
		FillGlobalDatasRpt();
	}

	m_nStopTestByError = 0;
	GBS_ClearBreakLoopState(pItem);//pItem->m_nBreakLoopState = 0;

	if(CTCtrlCntrWorkSpace::s_GetLastTestState() != g_strTesting)
	{
		CTCtrlCntrWorkSpace::s_SetLastTestState(g_strTesting);

 #ifndef _PSX_QT_LINUX_
		CTCtrlCntrWorkSpace::g_pWorkSpace->Save();
#endif
	}

	//设置当前测试项目
	m_nCurrTestItemIndex = pItem->GetIndex();

	//设置测试状态
	//pItem->SetState(TEST_STATE_TESTING);
	SetTestItemState(pItem, TEST_STATE_TESTING);

	//山东项目，改为先触发项目状态改变，再执行测试  shaolei 2024-2-29
	//移动到此处
	//触发测试项目状态改变消息
	m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem);

	switch (pItem->GetClassID())
	{
	case GBCLASSID_SAFETY:
		TestItemSafety((CSafety*)pItem);
		m_bElectricTesting = FALSE;
		break;

	case GBCLASSID_MACROCHARITEMS:
		TestItemMacroCharTest((CMacroCharItems*)pItem);
		break;

	case GBCLASSID_MACROTEST:
		TestItemMacroTest((CMacroTest*)pItem);
		break;

	case GBCLASSID_SYSPARAEDIT:
		TestItemSysParaEdit((CSysParaEdit*)pItem);
		m_bElectricTesting = FALSE;
		break;

	case GBCLASSID_COMMCMD:
		TestItemCommCmdEx((CCommCmd*)pItem);
		break;

		//2023-5-13  lijunqing
	case GBCLASSID_HDRESREQUEST:
		TestItemHdResReqest((CHdResReqest*)pItem);
		break;

	default:
		break;
	}

	//山东项目，改为先触发项目状态改变，再执行测试  shaolei 2024-2-29
	//移动到上方
// 	//触发测试项目状态改变消息
// 	m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem);

	return 0;
}

//测试前，对项目的报告进行备份：
//对于重复测试的项目，为了保证每次开始测试，是一个完整的测试周期；
//对于完整周期中间停止测试的，再次开始测试，就应该需要备份报告。例如：5次测试一周期，测到第二次时停止。下一个周期测试前应备份
void CTestControlBase::BackRptsBeforeTest(CGbItemBase *pItem)
{
	if (! CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_nUseSttAtsSvr)
	{
		return;
	}

	long nCurrTestTimes = 1, nRepeatTimes = 1;
	long nRptsCount = pItem->m_pReports->GetCount();

	if (nRptsCount == 0)
	{
		return;
	}

	if (pItem->GetClassID() == GBCLASSID_MACROTEST)
	{
		//电气量项目有自己的重复测试次数
		CMacroTest *pMacroTest = (CMacroTest *)pItem;

		if (pMacroTest->m_nRepeatTimes > 1)
		{
			nRepeatTimes = pMacroTest->m_nRepeatTimes;
		}
		else
		{
			pMacroTest->GetTestTimes(nCurrTestTimes, nRepeatTimes);
		}

		if (nRepeatTimes > 1)
		{
			pItem->ClearReport();
		}
	}
// 	else
// 	{
// 		pItem->GetTestTimes(nCurrTestTimes, nRepeatTimes);
// 	}
}

void CTestControlBase::ChangeReportFileName(const CString &strFileName)
{

}

long CTestControlBase::TestItemSafety(CSafety* pItem)
{
	return 0;
}

void CTestControlBase::GetMacroTestParaDatas(CMacroTestPara* pTestPara, CString &strPataDatas)
{
	strPataDatas = pTestPara->GetParaDatas();
}

//电气量测试输出控制
long CTestControlBase::TestItemMacroTest(CMacroTest* pItem)
{
	//2019-4-28  李俊庆
	//2019-4-28：多装置模式下，主装置TestControl执行测试流程，子装置没有执行测试流程，所以m_pCurrTestItem==NULL
// 	if (m_pCurrTestItem == NULL)
// 	{
// 		m_pCurrTestItem = pItem;
// 	}

	//为解决测试到第二台时卡住的问题，修改为不加是否为空判断，2019.05.07
	m_pCurrTestItem = pItem;

	CTestControlBase*pTestControl =  (CTestControlBase*)tctrl_GetTestControl(pItem);
	ASSERT (pTestControl == this);

	if (pTestControl != this)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TestControl:%s"), pTestControl->GetGbBinaryFileName().GetString());
	}

	if (pItem->m_nRepeatTimes > 1)
	{
		if (m_nMacroTestTimes == 0)
		{
			pItem->ClearReport();
		}

        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, g_sLangTxt_ItemTestTimeD.GetString()/*L"------项目[%s]第%d次测试，共%d次"*/
                                   , pItem->m_strName.GetString(), m_nMacroTestTimes+1, GetMaxRepeatTimes(pItem->m_nRepeatTimes)+1);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, g_sLangTxt_ItemTestTimeD2.GetString()/*L"------项目[%s]第1次测试，共1次"*/, pItem->m_strName.GetString());
	}

	//创建接口
	CreateMacroTestInterface(m_pGuideBook->m_pTestMacros, pItem->GetTestMacroID());

	if (m_pMacroTestInterface == NULL)
	{//创建失败，则终止测试
		StopTestExtern();

		return -1;
	}

	CMacroTest* pMacroTest = pItem;
	CMacroTestPara* pTestPara;
	CString strTestPara;
	CString strMacroID;

	if(m_pMacroTestInterface != NULL)
	{
		try
		{
			m_pMacroTestInterface->SetWndMsg((long)m_pTCtrlWnd->GetSafeHwnd(), WM_ELECTRIC_TEST);
		}
		catch(...)
		{
		}
	}
	else
	{
		return -1;
	}

	pTestPara = pMacroTest->GetMacroTestPara();
	strMacroID = pTestPara->GetMacroID();

	//2019-4-28  李俊庆
	//对于一个开关量测试仪对应多台装置的测试，开出传动测试，需要对开入节点进行切分提取
	//2019-4-28：多装置模式下，如果是每台装置都单独执行
	if (!pItem->IsMdvTestEach())
	{
		GetMacroTestParaDatas(pTestPara, strTestPara);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MdvTestTest:%s---1"), strTestPara);
	}
	else
	{
		CTestControlBase::GetMacroTestParaDatas(pTestPara, strTestPara);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MdvTestTest:%s---2"), strTestPara);
	}

	//控制输出
	DWORD nRet = 	0;

	try
	{
		if (g_nLog_TestControl_Msg == 1)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MacroTest=%s"), strMacroID.GetString());
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), strTestPara.GetString());
		}

		CString strItemPath = pItem->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
		m_pMacroTestInterface->SetItemPath(strItemPath);
        g_theSmartTestBaseApp->InitMacroTestEngineShowSpyWnd();
		nRet = m_pMacroTestInterface->Test(strMacroID,strTestPara); 
	}
	catch(...)
	{
	}

	//如果有子项目，先创建报告，并且获取报告数据
	//CExBaseList *pList = pItem->GetSubGbItems();
	//if (pList->GetCount() > 0)
	CReport *pReport = AddReport(pItem, pItem->m_nRepeatTimes, m_nMacroTestTimes);
	
	//2020-07-25  lijunqing  屏蔽开始前获取报告的操作，直接使用测试参数作为报告数据
	AddMacroTestReport(pItem, strTestPara);  //2017.05.17
	InitFillReport(pItem);
	SetTestItemState(pItem, TEST_STATE_TESTING);
	
	//如果连接成功，测试试验中的项目
	if ( (nRet & 0xF0000000) == 0)
	{
		m_bMacroTestFinished = FALSE;
		if (CanTestFirstSubItems())
		{
			//TestFirstSubItems();
			TestFirstSubItems_MacroTest(FALSE);
		}

		return 0;
	}
	else
	{
		if (m_pCurrTestItem != NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("MacroTest error{%s}={%08X}"), m_pCurrTestItem->m_strName.GetString(), nRet);
		}

		DeleteReport(pItem, pReport);
		StopTest(TEST_STATE_TEST_ERROR);
		return -1;
	}
}

long CTestControlBase::TestItemMacroCharTest(CMacroCharItems* pMacroCharItems)
{
	pMacroCharItems->UpdateMacroTestItems();

    m_pTCtrlWnd->PostMessage(WM_ELECTRIC_TEST, MTMSG_TestFinished, MTMSG_TestFinished);

	return 0;
}

long CTestControlBase::TestItemMacroTestChildItem(CMacroTest* pItem)
{
	TestFirstSubItems();

	return 0;
}

long CTestControlBase::TestItemHdResReqest(CHdResReqest *pItem)
{
	m_pCurrTestItem = pItem;

	CTestControlBase*pTestControl =  (CTestControlBase*)tctrl_GetTestControl(pItem);
	ASSERT (pTestControl == this);

	if (pTestControl != this)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TestControl:%s"), pTestControl->GetGbBinaryFileName().GetString());
	}

	//创建接口
	CreateMacroTestInterface_HdRes();

	if (m_pMacroTestInterface == NULL)
	{//创建失败，则终止测试
		StopTestExtern();

		return -1;
	}

	CHdResReqest* pHdResReqest = pItem;

	if(m_pMacroTestInterface != NULL)
	{
		try
		{
			m_pMacroTestInterface->SetWndMsg((long)m_pTCtrlWnd->GetSafeHwnd(), WM_ELECTRIC_TEST);
		}
		catch(...)
		{
		}
	}
	else
	{
		return -1;
	}

	//控制输出
	DWORD nRet = 	0;

	try
	{
		if (g_nLog_TestControl_Msg == 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MacroTest=%s"), pHdResReqest->m_strType.GetString());
		}

		g_theSmartTestBaseApp->InitMacroTestEngineShowSpyWnd();
		nRet = m_pMacroTestInterface->Test(pHdResReqest->m_strType, pHdResReqest->m_pPara); 
	}
	catch(...)
	{
	}

	//如果有子项目，先创建报告，并且获取报告数据
	//CExBaseList *pList = pItem->GetSubGbItems();
	//if (pList->GetCount() > 0)
	CReport *pReport = AddReport(pItem, -1, -1);

	//AddMacroTestReport(pItem, strTestPara);  //2017.05.17
	//InitFillReport(pItem);
	SetTestItemState(pItem, TEST_STATE_TESTING);

	//如果连接成功，测试试验中的项目
	if ( (nRet & 0xF0000000) == 0)
	{
		m_bMacroTestFinished = FALSE;
		return 0;
	}
	else
	{
		if (m_pCurrTestItem != NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("MacroTest error{%s}={%08X}"), m_pCurrTestItem->m_strName.GetString(), nRet);
		}

		DeleteReport(pItem, pReport);
		StopTest(TEST_STATE_TEST_ERROR);
		return -1;
	}
}

long CTestControlBase::TestItemSysParaEdit(CSysParaEdit* pItem)
{
#ifndef GUIDEBOOK_DEV_MODE
	AddReport(pItem, -1, -1); //2017.05.17
	
	if (pItem->m_strDatasetPath == g_strwSysPara)
	{
		if (pItem->m_nShow == 0)
		{
			long nDatasCount = 0;
			pItem->InitDataList(nDatasCount);
			return FinishTestItemSysParaEdit(pItem);
		}
	}

	return TestItemSysParaEdit_Test(pItem);
#else

	return 0;

#endif
}

long CTestControlBase::TestItemSysParaEdit_Test(CSysParaEdit* pItem)
{
	return 0;
}

long CTestControlBase::ViewSysPara(const CString &strSysParaID, CGbItemBase *pCurrSelItem)
{
	return 0;
}

void CTestControlBase::ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate)
{	
	m_oTCtrlMsgRcv.ShowItemReport(pGbItem, bCreate, TRUE);
}

void CTestControlBase::ShowCharDraw(CExBaseObject *pGbItem)
{
	m_oTCtrlMsgRcv.ShowCharDraw(pGbItem, TRUE);
}

void CTestControlBase::ShowItemRecord(CExBaseObject *pGbItem)
{
#ifndef _PSX_QT_LINUX_
    CGbItemBase *pItem = (CGbItemBase*)pGbItem;
	CValue *pFind = pItem->FindRecordFile();

	if (pFind == NULL)
	{
		return;
	}

	::ShellExecute(NULL, _T("explore"), pFind->m_strValue, NULL, NULL, SW_SHOWNORMAL);
#endif
}

void CTestControlBase::ShowItemReportDsv(CExBaseObject *pGbItem, CReport *pReport)
{
}

BOOL CTestControlBase::ExecuteTestItemCommCmd(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = AddReport(pItem, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17

	if ((m_pItemsRsltExprScript != NULL) && (m_nItemsRsltExprScriptTimeIgnore > 0) )
	{
		m_oItemsRsltExprScriptTimeTick.Enter();
	}
	
	//启动通讯命令前延时
	CString strSyntax;
	pItem->RunInitScriptScript(strSyntax);
	long nDelay = GetDelayBeforeCmd(pItem);

	if (nDelay > 0)
	{
		m_pTCtrlWnd->m_pTestItemRef = pItem;
		m_pTCtrlWnd->SetTestTimer(TIMER_DELAY_BEFORE_CMM_CMD, nDelay);
		//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("通讯前延时 = %d ms"), nDelay);
	}
	else
	{
		//如果不需要延时，则直接开始测试
		ExcuteCommCmdOnDelayBeforeFinish(pItem);
	}

	ExecuteTestItemCommCmd_ViewDlg(pItem);

	return TRUE;
}

BOOL CTestControlBase::ExecuteTestItemCommCmd_ViewDlg(CCommCmd* pItem)
{
	return TRUE;
}

long CTestControlBase::TestItemCommCmdEx(CCommCmd* pItem)
{
	if (Gb_IsGuideBookTemplate(pItem))
	{
#ifndef _PSX_QT_LINUX_
        AfxMessageBox(g_sLangTxt_MdfParaData .GetString() /*_T("调试子模板方式，请手动修改保护装置的参数数据")*/, MB_OK);
#endif
        TestNextItem();
		return TRUE;
	}

	m_nCommCmdReCommTimes = 0;

	if (HasCommCmdEngine(pItem))
	{
		return TestItemCommCmd((CCommCmd*)pItem);
	}
	else
	{
		return StopTestExtern();
//		return TestItemCommCmdMamual((CCommCmd*)pItem);
	}
}

CProtocolDeviceInterface* CTestControlBase::GetDevicePtr(CCommCmd* pItem)
{
	CPpDeviceRef *pPpDeviceRef = NULL;
	return m_oDeviceRefs.Find(pItem->GetCpusIndex(), m_nCommCmdCurrDeviceIndex);
}

CProtocolDeviceInterface* CTestControlBase::GetDevicePtr_0()
{
	CPpDeviceRef *pPpDeviceRef = NULL;
	return m_oDeviceRefs.Find(0, 0);
}

CProtocolDeviceInterface* CTestControlBase::GetDevicePtr()
{
	if (m_pCurrTestItem== NULL)
	{
		//return m_oPpDevice;
		return NULL;
	}

	if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		return GetDevicePtr((CCommCmd*)m_pCurrTestItem);
	}

	if (m_pCurrSubTestItem== NULL)
	{
		//return m_oPpDevice;
		return NULL;
	}

	if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		return GetDevicePtr((CCommCmd*)m_pCurrSubTestItem);
	}
	else if (m_pCurrTestItem->GetClassID() == GBCLASSID_MACROTEST)
	{
		return m_oDeviceRefs.Find(DSID_ALL_DVM, 0);
	}
	else
	{
		return NULL;
	}
}

void CTestControlBase::InitItemsRsltExprScript(CCommCmd* pItem)
{
	CItemsRsltExprScript *pItemsRsltExprScript = pItem->GetItemsRsltExprScript();

	if (m_pItemsRsltExprScript != pItemsRsltExprScript)
	{
		if (m_pItemsRsltExprScript != NULL)
		{
			m_pItemsRsltExprScript->m_dwReserved = 0;
		}
	}

	m_pItemsRsltExprScript = pItemsRsltExprScript;
	m_nItemsRsltExprScriptIndex = 0;

	if (m_pItemsRsltExprScript == NULL)
	{
		m_nItemsRsltExprScriptTimerLong = 0;
		m_nItemsRsltExprScriptMaxRead = -1;
		m_nItemsRsltExprScriptTimeIgnore = 0;
	}
	else
	{
		m_pItemsRsltExprScript->GetItemsRsltExprScriptTime(m_nItemsRsltExprScriptTimerLong, m_nItemsRsltExprScriptTimeIgnore);
		m_nItemsRsltExprScriptMaxRead  = m_pItemsRsltExprScript->m_nMaxReadTimes;
	}
}

//通讯命令测试
long CTestControlBase::CreatemUICommCmdViewDlg(LPVOID pUIViewDlg)
{
	return 0;
}

void CTestControlBase::HideCommCmdAttrDlg()
{
}


long CTestControlBase::TestItemCommCmd(CCommCmd* pItem)
{
	m_pTCtrlWnd->m_pTestItemRef = pItem;
	InitItemsRsltExprScript(pItem);
	InitFillReport(pItem);

	CCmd *pCmd = pItem->GetCmd();
	CString strGbBinaryFileName;

	if (!m_bSingleTestControl)
	{
        strGbBinaryFileName.Format(_T("[%s]"), m_strGbBinaryFileName.GetString());
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		if (pCmd->m_nRepeatTimes > 1)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,g_sLangTxt_CommunTestTimeD.GetString() /*L"----%s通讯命令[%s]第%d次测试，共%d次"*/
                                       , strGbBinaryFileName.GetString(), pItem->m_strName.GetString(), m_nCommCmdTestTimes+1, GetMaxRepeatTimes(pCmd->m_nRepeatTimes)+1);
		}
		else
		{
			if (m_pCurrSubTestItem == pItem)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, g_sLangTxt_CommunCmdS.GetString()/*L"----%s通讯命令[%s]"*/
                                           , strGbBinaryFileName.GetString(), pItem->m_strName.GetString());
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,  g_sLangTxt_CommunCmdItem.GetString()/*L"----------%s通讯命令项目[%s]"*/
                                           , strGbBinaryFileName.GetString(), pItem->m_strName.GetString());
			}
		}
	}

	//设置测试状态
	if (m_pCurrTestItem != pItem)
	{
		pItem->SetState(TEST_STATE_TESTING);
	}
	
	BOOL bWaiteConnect = FALSE;
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr(pItem);

	if (oPpDevice == NULL)
	{
		bWaiteConnect = TRUE;
	}

	//创建规约引擎设备连接，如果创建失败，则终止测试
	
	if (!CreatePpEngineDevice(pItem))
	{
		oPpDevice = GetDevicePtr(pItem);
		bWaiteConnect = TRUE;
		CreatePpEngineDevice(pItem);
	}

	oPpDevice = GetDevicePtr(pItem);

	if (oPpDevice == NULL)
	{//执行第一个测试项目的测试，创建设备之后，等待设备联机成功，再执行此项目的测试
		return 0;
	}

	if (!oPpDevice->IsConnectSuccessful())
	{
		bWaiteConnect = TRUE;
	}

	try
	{
		if (pItem->IsUseConnect())
		{
			if (!bWaiteConnect)
			{
				ExecuteTestItemCommCmd(pItem);
			}
		}
		else
		{
			ExecuteTestItemCommCmd(pItem);
		}
	}
	catch(...)
	{
		return 0;
	}

	if (m_pCurrTestItem != pItem)
	{
		m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem, FALSE);
	}

	return 0;
}

BOOL CTestControlBase::IsItemMacroTest(CGbItemBase* pItem)
{
	if (pItem == NULL)
	{
		return FALSE;
	}

	return (pItem->GetClassID() == GBCLASSID_MACROTEST);
}

//完成测试
long CTestControlBase::FinishTestItem(CGbItemBase* pItem)
{
	long nResult = 0;
	DWORD dwBegin = ::GetTickCount();

	switch (pItem->GetClassID())
	{
	case GBCLASSID_SAFETY:
		nResult = FinishTestItemSafety((CSafety*)pItem);
		break;
	case GBCLASSID_MACROTEST:
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("+++for debug+++CTestControlBase::FinishTestItem  ---%s"), pItem->m_strID.GetString());
		nResult = FinishTestItemMacroTest((CMacroTest*)pItem);
		break;
	case GBCLASSID_SYSPARAEDIT:
		nResult = FinishTestItemSysParaEdit((CSysParaEdit*)pItem);
		break;
	case GBCLASSID_COMMCMD:
		ASSERT (FALSE);
		break;
	default:
		StopTestExtern();
		break;
	}

	return nResult;
	return 0;
}

CString CTestControlBase::GetItemTempPath()
{
	CString strTempFilePath = GetPathFromFilePathName(m_strGbBinaryFile);//GetTestProjectTempFilePath(m_pTestProject);

	if (strTempFilePath.IsEmpty())
	{
		strTempFilePath = _P_GetWorkspacePath();
	}

    if (strTempFilePath.Right(1) == _T("\\") || strTempFilePath.Right(1) == _T("/"))
	{
		strTempFilePath.AppendFormat(_T("%s"), m_strGbBinaryFileName.GetString());
	}
	else
	{
		strTempFilePath.AppendFormat(_T("%s\\"), m_strGbBinaryFileName.GetString());
	}
    
	return strTempFilePath;
}

void CTestControlBase::GetReportFiles(CDataGroup *pDataGroup)
{
	CString strFile = GetGbBinaryFile();
	pDataGroup->AddNewData(XPARA_ID_GBRPTFILE, strFile);
	strFile = ChangeFilePostfix(strFile, g_strDocFilePostfix);
	pDataGroup->AddNewData(XPARA_ID_DOCFILE, strFile);
	strFile = ChangeFilePostfix(strFile, _T("xml"));
	pDataGroup->AddNewData(XPARA_ID_XMLRPTFILE, strFile);

#ifndef _PSX_QT_LINUX_
    pDataGroup->AppendCloneEx(g_oWordReportExGroup);
#endif
}

void CTestControlBase::SetGuideBook(CGuideBook *pGuideBook)
{
    if (m_pGuideBook != NULL)
    {
        delete m_pGuideBook;
    }

    m_pGuideBook = pGuideBook;
    m_pGuideBook->SetParent(this);
}

void CTestControlBase::FreeItemsContainer()
{
    if(m_pItemContainer != NULL)
    {
        delete m_pItemContainer;
        m_pItemContainer = NULL;
    }
}

void CTestControlBase::ResetTestControl()
{
	m_nCurrTestItemIndex = 0;
	//ReleaseMacroTestInterface();
	GBS_PpReleaseAllDevice();
	SaveBinaryFile();
	DeleteTempDirectorys();

#ifndef GUIDEBOOK_DEV_MODE
	if(m_pGuideBook != NULL)
	{
		delete m_pGuideBook;
	}
#endif

	if (!m_bTestControlWndRef)
	{
		if(m_pTCtrlWnd != NULL)
		{
			m_pTCtrlWnd->DestroyWindow();
			delete m_pTCtrlWnd;
		}
	}

	m_pTCtrlWnd = NULL;

	if (m_pReportFill != NULL)
	{
		m_pReportFill->Close(1);
		delete m_pReportFill;
		m_pReportFill = NULL;
	}

	m_oDeviceRefs.DeleteAll();
	DeleteAll();

#ifndef GUIDEBOOK_DEV_MODE
	m_pGuideBook = new CGuideBook;
	m_pGuideBook->m_nIndex = 0;
	m_pGuideBook->InitAfterRead();
	m_pGuideBook->SetParent(this);
#endif
}

void CTestControlBase::AttachItemViewGrid(void *pGrid, BOOL bUpdateGrid)
{

}

void CTestControlBase::EmptyReportDatas(BOOL bUseCfgFlag)
{
	if (bUseCfgFlag)
	{
		CTCtrlCntrConfig *pConfig = g_theSmartTestBaseApp->GetCntrConfig();

		//路径的有效性
		if (pConfig->m_strAutoSaveReportPath.GetLength() < 3)
		{
			return;
		}
	}

	m_pCurrTestItem = NULL;
	m_nCurrTestItemIndex = 0;
	Gb_EmptyReportDatas(m_pGuideBook);

	if (m_pReportFill != NULL)
	{
		m_pReportFill->EmptyReportText();
	}
}

void CTestControlBase::FinishInptuData(CDataGroup *pDataGroup)
{

}

//自动上传测试报告
void CTestControlBase::AutoSaveReportFileName(CWnd *pParentWnd, BOOL bJudgeState)
{
#ifndef _PSX_QT_LINUX_
	if (bJudgeState)
	{
		if (!Gb_IsItemsTestFinished(m_pGuideBook))
		{
			return;
		}
	}


	CTCtrlCntrConfig *pConfig = g_theSmartTestBaseApp->GetCntrConfig();

	//路径的有效性
	if (pConfig->m_strAutoSaveReportPath.GetLength() < 3)
	{
		return;
	}

	if ( m_pGuideBook->m_strAotuSaveReportFileName.GetLength() < 3)
	{
		return;
	}

	//不创建路径，避免网络路径带来的问题
	//CreateAllDirectories(pConfig->m_strAutoSaveReportPath);

	CString strFile;
	CString strSrc = m_strGbBinaryFile;

	strFile = pConfig->m_strAutoSaveReportPath;

	if (strFile.Right(1) != _P_FOLDER_PATH_SEPARATOR_)
	{
		strFile += _P_FOLDER_PATH_SEPARATOR_;
	}

	CString strMsg = g_sLangTxt_ReportExpSucc/*_T("报告导出成功：\r\n")*/;
	strFile.AppendFormat(_T("%s.%s"), m_pGuideBook->m_strAotuSaveReportFileName, g_strGuideBookBinaryPostfix);

	strMsg.AppendFormat(_T("%s\r\n"), strFile);
	::X_CopyFile(strSrc, strFile, TRUE);
	strSrc  = ChangeFilePostfix(strSrc, g_strDocFilePostfix);
	strFile = ChangeFilePostfix(strFile, g_strDocFilePostfix);
	::X_CopyFile(strSrc, strFile, TRUE);
	strMsg.AppendFormat(_T("%s\r\n"), strFile);
	pParentWnd->MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONINFORMATION);
#endif
}

void CTestControlBase::GetItemsCount(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount)
{
	nTotalCount = nEligibleCount = nInlegibleCount = 0;
	if (m_pGuideBook == NULL)
	{
		return ;
	}

	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig == NULL)
	{
		//nTotalCount = m_pItemContainer->m_nItemCount;
		m_pGuideBook->GetItemsCount(nTotalCount, nEligibleCount, nInlegibleCount);
	}

	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strItemsCountMode == SMARTTEST_ITEM_COUNT_MODE_ITEMSTYPE)
	{
		m_pGuideBook->GetItemsCountByItemsType(nTotalCount, nEligibleCount, nInlegibleCount);
	}
	else
	{
		//nTotalCount = m_pItemContainer->m_nItemCount;
		m_pGuideBook->GetItemsCount(nTotalCount, nEligibleCount, nInlegibleCount);
	}
}

void CTestControlBase::UploadRptFiles(CString &strFiles)
{
	CDataGroup oGroup;
	CDataGroup *pGroup = oGroup.AddNewGroup(m_strName, m_strID, _T(""));
	UploadRptFiles(pGroup);
// 	long nTotalItems = 0, nEligibleItems = 0, nInlegibleItems = 0;
// 	GetItemsCount(nTotalItems, nEligibleItems, nInlegibleItems);
// 	pGroup->AddNewData(XPARA_ID_TOTALITEMS, nTotalItems);
// 	pGroup->AddNewData(XPARA_ID_ELIGIBLEITEMS, nEligibleItems);
// 	pGroup->AddNewData(XPARA_ID_INLEGIBLEITEMS, nInlegibleItems);
// 
// 	CString strFile = GetGbBinaryFile();
// 	pGroup->AddNewData(XPARA_ID_GBRPTFILE, strFile);
// 	strFile = ChangeFilePostfix(strFile, g_strDocFilePostfix);
// 	pGroup->AddNewData(XPARA_ID_DOCFILE, strFile);
// 	strFile = ChangeFilePostfix(strFile, _T("xml"));
// 	pGroup->AddNewData(XPARA_ID_XMLRPTFILE, strFile);

	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	oGroup.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strFiles);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
}

void CTestControlBase::UploadRptFiles(CDataGroup *pGroup)
{
	long nTotalItems = 0, nEligibleItems = 0, nInlegibleItems = 0;
	GetItemsCount(nTotalItems, nEligibleItems, nInlegibleItems);
	pGroup->AddNewData(XPARA_ID_TOTALITEMS, nTotalItems);
	pGroup->AddNewData(XPARA_ID_ELIGIBLEITEMS, nEligibleItems);
	pGroup->AddNewData(XPARA_ID_INLEGIBLEITEMS, nInlegibleItems);

	CString strFile = GetGbBinaryFile();
	pGroup->AddNewData(XPARA_ID_GBRPTFILE, strFile);
	strFile = ChangeFilePostfix(strFile, g_strDocFilePostfix);
	pGroup->AddNewData(XPARA_ID_DOCFILE, strFile);
	strFile = ChangeFilePostfix(strFile, _T("xml"));
	pGroup->AddNewData(XPARA_ID_XMLRPTFILE, strFile);
}

void CTestControlBase::SetDeviceSN_AfterTestCreated(const CString &strDeviceSN)
{
	if (strDeviceSN.IsEmpty())
	{
		return;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	CCpus *pCpus = pDevice->GetCpus();

	if (pCpus != NULL)
	{
		pCpus->m_strID = strDeviceSN;
	}

	m_pGuideBook->GBS_SetGlobal_Str(STT_CMD_PARA_DeviceSN, strDeviceSN);
}

BOOL CTestControlBase::WriteItemTempFile(CGbItemBase* pItem)
{
    //lijunqing 2020-9-16  测试仪底层，暂时不考虑临时文件的方式
#ifdef _PSX_QT_LINUX_
    return 1;
#endif

#ifndef GUIDEBOOK_DEV_MODE
	//保存测试项目的临时文件
	CString strTempFilePath = ats_GetBinaryTempFilePath(pItem);
	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, pItem);
	CString strXmlFile = ChangeFilePostfix(strTempFileName, _T("xml"));
	BOOL bIsSaveRptToDB = FALSE;

	if (m_pGuideBook->IsSaveRptToDB())
	{
		bIsSaveRptToDB = TRUE;
	}
	else
	{
        if (g_theSmartTestBaseApp->IsSaveRptToDB())
		{
			bIsSaveRptToDB = TRUE;
		}
	}

	if (bIsSaveRptToDB)
	{
		CGbItemBase *pNew = pItem->CloneForTempFile(strTempFileName);
		pNew->SaveBinaryTempFile(strTempFilePath,strTempFileName);
	
        if (g_theSmartTestBaseApp->IsWriteTestTempFile())
		{
			pNew->SaveXmlTempFile(strTempFilePath,strXmlFile);
		}

		pNew->FreeCloneForTempFile();
		delete pNew;
	}
	else
	{
		pItem->SaveBinaryTempFile(strTempFilePath,strTempFileName);

        if (g_theSmartTestBaseApp->IsWriteTestTempFile())
		{
			pItem->SaveXmlTempFile(strTempFilePath,strXmlFile);
		}
	}

	//2017-8-31 LiJQ  避免多装置多组测试导致内存不足
	if (bIsSaveRptToDB)
	{
// 		CReport *pReport = pItem->GetReport(-1);
// 		pReport->ClearReportDatasByMap(pItem->GetReportMap()
// 			, TRUE, 2);
		pItem->ClearItemInDbState();
		m_oGbItemBaseMapForDB_Mngr.DeleteAll();
	}
#endif

	return TRUE;
}

long CTestControlBase::UpdateStateAfterFinishTestItem(CGbItemBase* pItem, BOOL bNeedFireMsg)
{
	DWORD dwEnd = ::GetTickCount();

	//根据执行判断脚本的返回值设置项目状态
	pItem->InitStateByReport();

	//保存测试项目的临时文件
	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	//因此在此注释掉，在每个更新的位置单独执行
	//WriteItemTempFile(pItem);

	dwEnd = ::GetTickCount();
	dwEnd = ::GetTickCount();

	dwEnd = ::GetTickCount();

	m_nStopTestByError = 0;
    CTCtrlCntrConfig *pConfig = g_theSmartTestBaseApp->GetCntrConfig();
	BOOL bPlayCycle = 0;

	if (pItem->GetState() == TEST_STATE_INLEGIBLE)
	{
		if (m_pCurrTestItem == pItem)
		{

			if (pConfig->IsErrorProcessStop())
			{
				StopTestExtern();
				m_nStopTestByError = 1;
				bPlayCycle = 1;
			}
		}

		if (pItem->GetClassID() == GBCLASSID_MACROTEST)
		{//电气量项目
			AddRecordReport(pItem);
		}
		else if (pItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			if (m_pCurrTestItem != NULL)
			{
				if ( m_pCurrTestItem->GetClassID() == GBCLASSID_MACROTEST)
				{//通讯命令项目，但是作为电气量项目的子项目
					AddRecordReport(pItem);
				}
			}
		}
	}

	if (pConfig->m_nErrPlayMode > 0)
	{
		bPlayCycle = 1;
	}

	BOOL bFireTestItemErrorMsg = FALSE;

	if (m_pCurrTestItem != NULL)
	{
		if (m_pCurrTestItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			CMacroTest* pMacroItem = (CMacroTest*)m_pCurrTestItem;

			if (pMacroItem->m_nRepeatTimes > 1)
			{
				//if (m_nMacroTestTimes == pMacroItem->m_nRepeatTimes-1)
				if (m_nMacroTestTimes >= GetMaxRepeatTimes(pMacroItem->m_nRepeatTimes))
				{
					bFireTestItemErrorMsg = TRUE;
				}
			}
			else
			{
				bFireTestItemErrorMsg = TRUE;
			}
		}
		else
		{
			bFireTestItemErrorMsg = TRUE;
		}
	}
	else
	{
		bFireTestItemErrorMsg = TRUE;
	}

	//对于覆盖的通讯命令来说，测试结果不合格不发送消息
	if (pItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		CCommCmd *pCommCmd = (CCommCmd *)pItem;
		CCmd *pCmd = pCommCmd->GetCmd();
		long nCalMode = pCmd->GetCalMode();

		if (nCalMode == TEST_CALMODE_OVERWRITE)
		{
			bFireTestItemErrorMsg = FALSE;
		}
	}

	if (bFireTestItemErrorMsg && bNeedFireMsg)
	{
        g_theSmartTestBaseApp->FireTestItemErrorMsg(pItem, bPlayCycle);
	}

    //触发测试项目状态改变消息
    m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem);

	return 0;
}

void CTestControlBase::QueryRecord(CGbItemBase* pItem)
{
	if (pItem == NULL)
	{
		return ;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		return;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr(pCommCmd);

	if (oPpDevice == NULL)
	{
		//创建规约引擎设备连接，如果创建失败，则终止测试
		if (!CreatePpEngineDevice(pCommCmd))
		{
			oPpDevice = GetDevicePtr(pCommCmd);
			CreatePpEngineDevice(pCommCmd);
		}

		oPpDevice = GetDevicePtr(pCommCmd);
	}


	if (oPpDevice == NULL)
	{
		return;
	}

	CString strTempFilePath = ats_GetBinaryTempFilePath(pCommCmd);
	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, pCommCmd);
	CreateAllDirectories(strTempFilePath);
	
	CReport *pReport = pCommCmd->GetReport(-1);

	if (pReport == NULL)
	{
		return;
	}

	CString strRcdFile = oPpDevice->QueryRecord(pReport->m_strBeginTime, pReport->m_strEndTime, strTempFileName);

	if (strRcdFile.GetLength() > 0)
	{
		CValue *pValue = (CValue*)pReport->m_pValues->FindByID(g_strRecordResultKey);

		if (pValue != NULL)
		{
			pValue->m_strName = strRcdFile;
		}
		else
		{
			pReport->AddValue(g_strRecordResultKey, strRcdFile);
		}

        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Query Record File %s"), strRcdFile.GetString());
	}
}

void CTestControlBase::AddRecordReport(CGbItemBase* pItem)
{
}

void CTestControlBase::AdjustSafetyComCmdDlgPos()
{
}

CMacroTestInterface* CTestControlBase::CreateMacroTestInterface(const CString &strType, const CString &strProgID)
{
	if (m_pMacroTestInterface != NULL)
	{
		return m_pMacroTestInterface;
	}

	if (m_pGuideBook == NULL)
	{
		return NULL;
	}

	CreateMacroTestInterface(strType, strProgID, m_pGuideBook->m_strTestMacroFileID, m_pGuideBook->GetTestApps(TRUE));

	return m_pMacroTestInterface;
}

void CTestControlBase::GetAllInlegibleTestItems(CExBaseList *pList, CExBaseList *pGbList)
{
	POS pos = pGbList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_ITEMS || nClassID == GBCLASSID_JOBGUIDE)
		{
			GetAllInlegibleTestItems(pList, (CExBaseList*)p);
		}
		else if (nClassID == GBCLASSID_MACROTEST || nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_SAFETY)
		{
			CGbItemBase *pItem = (CGbItemBase*)p;
			long nState = pItem->GetState();
// 			if (nState == TEST_STATE_ELIGIBLEEX)
// 			{
// 				pList->AddTail(p);
// 			}
// 			else 
			if (nState == TEST_STATE_INLEGIBLE)
			{
				pList->AddTail(p);
			}
		}
	}
}

#ifndef _PSX_QT_LINUX_
#endif

void CTestControlBase::FinishTestSubItem_MacroTest(BOOL &bCallMacroStopTestError)
{
	try
	{
		if (m_pMacroTestInterface != NULL)
		{
			//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("     -- call MacroTest.FinishTest"));
			if (!mt_IsVirtualVm())
			{
				if (g_nLog_TestControl_Msg == 1)
				{
                    CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("TestNextSubItem::Set_TIMER_TEST_CTRL_MACROFINISH"));
				}

				if (!m_bMacroTestFinished)
				{
					m_pTCtrlWnd->Set_TIMER_TEST_CTRL_MACROFINISH();
				}
			}
			else
			{
				if (g_nLog_TestControl_Msg == 1)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, _T("TestNextSubItem::Virtual VM"));
				}
			}

			if (g_nLog_TestControl_Msg == 1)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("TestNextSubItem::FinishTest(1)"));
			}

			if (!m_bMacroTestFinished)
			{
				m_pMacroTestInterface->FinishTest(1);
			}
			else
			{
				FinishTestItem(m_pCurrTestItem);
			}
		}
	}
	catch (...)
	{
		bCallMacroStopTestError = TRUE;
	}

	if (bCallMacroStopTestError)
	{
		try
		{
			if (g_nLog_TestControl_Msg == 1)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("     -- call StopTest"));
			}

			m_pMacroTestInterface->StopTest();
            m_pTCtrlWnd->PostMessage(WM_ELECTRIC_TEST, MTMSG_TestFinished, MTMSG_TestFinished);
		}
		catch (...)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("call StopTest error-----"));
		}
	}
}

long CTestControlBase::TestNextSubItem(CGbItemBase* pCurrSubItem)
{
	//m_dwReserved：用于记录和保存SystemReport的表格，清空
	ClearSysRptFill(m_pCurrSubTestItem);

	if (m_nStopTestByError == 1)
	{
		if (g_nLog_TestControl_Msg == 1)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("TestNextSubItem::m_nStopTestByError == 1"));
		}

		m_pCurrTestItem = NULL;
		m_pCurrSubTestItem = NULL;
		return 0;
	}

	ASSERT (m_pCurrSubTestItem != NULL);

	//是否作为实验中的提示信息出现
	long nClassID = m_pCurrTestItem->GetClassID();
	ASSERT (pCurrSubItem == m_pCurrSubTestItem);
	//ASSERT (nClassID == GBCLASSID_MACROTEST);
	BOOL bSubTestFinish = FALSE;

	//如果当前项目处于“m_nBreakLoopState == 1”状态，则结束跳出
	if (GBS_CanBreakLoop(m_pCurrTestItem))//if (m_pCurrTestItem->m_nBreakLoopState == 1)
	{
		bSubTestFinish = TRUE;
		m_pCurrSubTestItem = NULL;
	}
	else if (m_pItemContainer->GetGotoItem() != NULL)
	{
		bSubTestFinish = TRUE;
		m_pCurrSubTestItem = NULL;
	}
	else
	{
		GetNextTestSubItem();

		if (m_pCurrSubTestItem == NULL)
		{
			bSubTestFinish = TRUE;
		}
	}

	//if (GetNextTestSubItem() == NULL)
	BOOL bCallMacroStopTestError = FALSE;

	if (bSubTestFinish)
	{//没有子项目，完成当前测试项目的测试
		switch  (nClassID )
		{
		case GBCLASSID_MACROTEST:
			FinishTestSubItem_MacroTest(bCallMacroStopTestError);
			break;
		case GBCLASSID_SYSPARAEDIT:
			break;

		case GBCLASSID_SAFETY:
			break;

		default:
			FinishTestItem(m_pCurrTestItem);
			break;
		}
	}
	else
	{
		TestItem(m_pCurrSubTestItem);
	}

	return 0;
}

BOOL CTestControlBase::HasNextSubItem(CGbItemBase* pCurrSubItem)
{
	UINT nClassID = m_pCurrTestItem->GetClassID();
	ASSERT (nClassID == GBCLASSID_MACROTEST);

	if (nClassID != GBCLASSID_MACROTEST )
	{
		return FALSE;
	}

	CMacroTest *pMacroTest = (CMacroTest*)m_pCurrTestItem;
	CExBaseList *pList = pMacroTest->GetSubGbItems();

	if (pList->GetCount())
	{
		POS pos = pList->Find(m_pCurrSubTestItem);

		if (pos == NULL)
		{
			return FALSE;
		}

		//下一个项目
		CGbItemBase *pCurrSubTestItem = (CGbItemBase*)pList->GetNext(pos);

		if (pos != NULL)
		{
			pCurrSubTestItem = (CGbItemBase*)pList->GetAt(pos);
		}
		else
		{
			pCurrSubTestItem = NULL;
		}

		return (pCurrSubTestItem != NULL);
	}
	else
	{
		return FALSE;
	}
}

BOOL CTestControlBase::AfterFinishTestItemSafety(CSafety *pSafety)
{
	return TRUE;
}

void CTestControlBase::SaveReport()
{
	if (m_pReportFill == NULL)
	{
		return;
	}

	try
	{
		if (m_pReportFill->GetReportFile().GetLength() > 10)
		{
			m_pReportFill->Save();
		}
		else
		{
			CString strReportFile = GetReportFile();

			if (m_pReportFill != NULL)
			{
				m_pReportFill->SaveAs(strReportFile);
			}
		}
	}
	catch (...)
	{
		
	}

	//m_pGuideBook->SaveBinaryFile(m_strGbBinaryFile);
}

//2023-9-26  lijunqing 导出报告数据文件
void CTestControlBase::ExportRptDataFile()
{
	CString strTemplateFile;
	strTemplateFile = m_pGuideBook->m_strGbXmlFile;
	strTemplateFile = ChangeFilePostfix(strTemplateFile, _T("json"));
	CString strRptFile = m_strGbBinaryFile;

	if (IsFileExist(strTemplateFile))
	{
// 		CString strLocal;
// 		strLocal = _T("D:\\0\\TEST_FOR_JSONFILL.GBXML");
// 		m_pGuideBook->SaveXMLFile(strLocal);
		CJsonRptFill oJsonRptFill;
		oJsonRptFill.OpenRptTemplateFile(strTemplateFile);
		oJsonRptFill.FillRpt(m_pGuideBook);
		strRptFile = ChangeFilePostfix(m_strGbBinaryFile, _T("json"));
		oJsonRptFill.SaveRptFile(strRptFile);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GenerateWordReport [%s] finished"), strRptFile.GetString());;
	}
}

void CTestControlBase::SaveReportOwn()
{
// 	if (m_pReportFill != NULL)
// 	{
// 		m_pReportFill->Save();
// 	}
	SaveReport();

	m_pGuideBook->SaveBinaryFile(m_strGbBinaryFile, CTCtrlCntrConfig::Get_RWReportFileMode());
}

CGbItemBase* CTestControlBase::GetTestItem(CGbItemBase *pGbItem, long nIndex)
{
	return pGbItem;
}

long CTestControlBase::FinishCurrTestItem(CDataGroup *pDataGroup)
{
    if (m_pCurrTestItem == NULL)
    {
        return 0;
    }


    if (m_pCurrTestItem->GetClassID() == GBCLASSID_SAFETY)
    {
        CSafety *pSafety = (CSafety*)m_pCurrTestItem;
        SetVal_ShortDatas_by_DvmDatas(pDataGroup, pSafety->m_pDatas);

// 		if (m_pSafetyDlg != NULL)
// 		{
// 			m_pSafetyDlg->PostMessage(WM_FINISH_INPUTDATA, 0, 0);
// 		}
// 		else
		{
			FinishTestItemSafety(pSafety);
		}

        return 1;
    }

    if (m_pCurrTestItem->GetClassID() == GBCLASSID_SYSPARAEDIT)
    {
        CSysParaEdit *pSysParaEdit = (CSysParaEdit*)m_pCurrTestItem;
        CExBaseList *pList = pSysParaEdit->GetSysParaEditDataObjList();
        Gb_InitValueByDvmDatas(pDataGroup, pList);
        FinishTestItemSysParaEdit(pSysParaEdit);
        return 1;
    }

    return 0;
}

//2021-8-10  lijunqing
void CTestControlBase::SetItemReport(CGbItemBase *pCurrItem, CGbItemBase *pSrcItem)
{
	UINT nClassID = pCurrItem->GetClassID();

	if (nClassID == GBCLASSID_SAFETY)
	{
		FinishTestItemSafety((CSafety*)pCurrItem, (CSafety*)pSrcItem);
		return;
	}

	if (nClassID == GBCLASSID_SYSPARAEDIT)
	{
		FinishTestItemSysParaEdit((CSysParaEdit*)pCurrItem, (CSysParaEdit*)pSrcItem);
		return;
	}

	if (nClassID == GBCLASSID_MACROTEST)
	{
		return;
	}
}

void CTestControlBase::SetItemsReport(CItems *pCurrItems, CItems *pSrcItems)
{
	POS pos = pSrcItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CExBaseObject *pFind = NULL;

	//2021-10-1  lijunqing
	m_pCurrTestItem = NULL;
	m_pCurrSubTestItem = NULL;
	m_pItemContainer->ResetItemContainer();

	while (pos != NULL)
	{
		p = pSrcItems->GetNext(pos);
		nClassID = p->GetClassID();
		pFind = NULL;

		if (nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_SYSPARAEDIT
			|| nClassID == GBCLASSID_MACROTEST)
		{//目前只处理三种
			pFind = pCurrItems->FindByID(p->m_strID);

			if (pFind != NULL)
			{
				SetItemReport((CGbItemBase*)pFind, (CGbItemBase*)p);
			}
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			pFind = pCurrItems->FindByID(p->m_strID);

			if (pFind != NULL)
			{
				SetItemsReport((CItems*)pFind, (CItems*)p);
			}
		}
	}
}


long CTestControlBase::FinishTestItemSafety(CSafety* pItem)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	//添加报告
	CReport *pReport = pItem->GetReport(-1);//AddReport(pItem, -1, -1); //2017.05.17
	pReport->SetReportValues(pItem->m_pDatas);
	pItem->AddQRCodeValues(pReport->m_pValues);

	//2021-8-10  lijunqing
	return FinishTestItemSafety_Process(pItem, pReport);
}

//2021-8-10  lijunqing
long CTestControlBase::FinishTestItemSafety(CSafety* pItem, CSafety *pSrcItem)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	//记录数据
	pItem->m_pDatas->InitDatasValue(pSrcItem->m_pDatas);

	//添加报告
	pItem->m_pReports->InitReports(pSrcItem->m_pReports);

	//2021-8-10  lijunqing
	CReport *pReport = pItem->GetReport(-1);//AddReport(pItem, -1, -1); //2017.05.17
	pItem->AddQRCodeValues(pReport->m_pValues);

	return FinishTestItemSafety_Process(pItem, pReport);
}

//2021-8-10  lijunqing
long CTestControlBase::FinishTestItemSafety_Process(CSafety* pItem, CReport *pReport)
{
	//执行结果判断脚本
	CString strSyntax;
	m_pCurrReport = pReport;
	pItem->RunResultScript(strSyntax);
	m_pCurrReport = NULL;

	//填写报告
	FillReport(pReport, 0);

	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	UpdateStateAfterFinishTestItem(pItem);

	//如果所有的事情都处理完毕，则返回TRUE
	if (!AfterFinishTestItemSafety(pItem))
	{
		//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
		//因此单独执行
		WriteItemTempFile(pItem);
		return 0;
	}

	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	//因此单独执行
	WriteItemTempFile(pItem);

	//作为子项目，测试子项目
	if (pItem->m_bIsSubItem)
	{
		if (m_pCurrSubTestItem == pItem)
		{
			TestNextSubItem(pItem);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_TestStop4.GetString() /*_T("    测试项目时序发生错误，测试停止")*/);
			StopTest();
		}
	}
	else//不作为子项目，测试下一个项目
	{
		TestNextItem();
	}

	return 0;
}

//该函数是将电气量项目中的参数，作为报告数据，添加到报告中
CReport* CTestControlBase::AddMacroTestReport(CMacroTest* pItem, const CString &strItemPara)
{
    CReport *pReport = pItem->GetReport(-1);  //2017.05.24

    //add by shaolei 20220318
    if(strItemPara.Left(1) == _T("<"))
        return pReport;

	if (pReport == NULL)
	{
		pReport = pItem->AddReport(-1, -1);
	}

	//以下是从TestMacro中查找缺省值参数，添加到报告中
	CString strMacroID = pItem->GetTestMacroID();
	CTestMacro *pTestMacro = (CTestMacro *)m_pGuideBook->m_pTestMacros->FindByID(strMacroID);
	ASSERT(pTestMacro != NULL);

	CShortDatas *pFaultParas = pTestMacro->GetFaultParas();
	CShortDatas *pSysParas = pTestMacro->GetSysParas();
	CShortDatas oList, oListEx;
	oList.AppendEx(*pFaultParas, FALSE);
	oList.AppendEx(*pSysParas, FALSE);
	pTestMacro->InitFaultParasEx(oListEx);

	pReport->AppendReportValues(&oList);
	pReport->AppendReportValues(&oListEx);
	oList.RemoveAll(); 
	oListEx.RemoveAll();

	//以下是更新非缺省值，因为strItemPara中只有非缺省值
	CValues pValues;
	pValues.SetValuesByString(strItemPara);
	pReport->UpdateReportValues(&pValues);

	//shaolei 2023-9-1 通过GetReport返回的报告，没有name属性
	ats_InitReportValuesName(pReport, pItem);

	return pReport;
}

CReport* CTestControlBase::AddHdResReqestReport(CHdResReqest* pItem)
{
	CReport *pReport = pItem->GetReport(-1);  //2017.05.24

	if (pReport == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("测试项【%s】没有报告"), pItem->m_strID.GetString());
		pReport = AddReport(pItem, -1, -1);////2017.05.17
	}

	CString bstrReport;

	try
	{
		bstrReport = m_pMacroTestInterface->GetReport();

		if (g_nLog_TestControl_Msg == 1)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("MacroTest.GetReport:"));
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), bstrReport.GetString());
		}
	}
	catch(...)
	{
	}

	CValues pValues;
	pValues.SetValuesByString(bstrReport);
	pReport->SetReportValues(&pValues);

	return pReport;
}

CReport* CTestControlBase::AddMacroTestReport(CMacroTest* pItem)
{
	CReport *pReport = pItem->GetReport(-1);  //2017.05.24
	//AddReport(pItem, pItem->m_nRepeatTimes, m_nMacroTestTimes);////2017.05.17

	if (pReport == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("测试项【%s】没有报告"), pItem->m_strID.GetString());
		pReport = AddReport(pItem, pItem->m_nRepeatTimes, m_nMacroTestTimes);////2017.05.17
	}

	CString bstrReport;
	
	try
	{
		bstrReport = m_pMacroTestInterface->GetReport();

		if (g_nLog_TestControl_Msg == 1)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("MacroTest.GetReport:"));
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), bstrReport.GetString());
		}
	}
	catch(...)
	{
    }

	CValues pValues;
	pValues.SetValuesByString(bstrReport);
	pReport->SetReportValues(&pValues);

	//shaolei 2023-9-1 通过GetReport返回的报告，没有name属性
	ats_InitReportValuesName(pReport, pItem);

	return pReport;
}

void CTestControlBase::AddMacroTestReport(CMacroTest* pItem, CReport *pSrcReport)
{
	CReport *pDestReport = pItem->GetReport(-1); //2017.05.24
	//AddReport(pItem, pItem->m_nRepeatTimes, m_nMacroTestTimes);
	pSrcReport->CopyOwn(pDestReport);
	pDestReport->m_pValues->DeleteAll();
	pDestReport->m_pValues->AppendCloneEx(*pSrcReport->m_pValues);
}

void CTestControlBase::BackMacroTestResults(CReport *pReport)
{
	m_listMacroTestResults.DeleteAll();

	BackMacroTestResult(pReport, g_strTestResultAbsErrorKey);
	BackMacroTestResult(pReport, g_strTestResultRelErrorKey);
	BackMacroTestResult(pReport, g_strTestResultRsltEx1Key);
	BackMacroTestResult(pReport, g_strTestResultRsltEx2Key);
	BackMacroTestResult(pReport, g_strTestResultRsltEx3Key);
	BackMacroTestResult(pReport, g_strTestResultRsltEx4Key);
}

void CTestControlBase::BackMacroTestResult(CReport *pReport, const CString &strValID)
{
	CValue *pValue = NULL;
	pValue = (CValue *)pReport->m_pValues->FindByID(strValID);

	if (pValue != NULL)
	{
		m_listMacroTestResults.AddTail((CExBaseObject*)pValue->Clone());
	}
}

void CTestControlBase::UpdateMacroTestResults(CReport *pReport)
{
	pReport->UpdateReportValues(&m_listMacroTestResults);
	m_listMacroTestResults.DeleteAll();
}

void CTestControlBase::UpdateMacroTestReport(CMacroTest* pItem, CReport *pSrcReport)
{
	CReport *pDestReport = (CReport*)pItem->GetReport(-1);

	if (pDestReport == NULL)
	{
		//ASSERT (FALSE);//2017.05.17   调试时，注释此断言  shaolei  20201023
		pDestReport = AddMacroTestReport(pItem);//2017.05.17
	}

	pDestReport->m_pValues->DeleteAll();
	pDestReport->m_pValues->AppendCloneEx(*pSrcReport->m_pValues);
}

CReport* CTestControlBase::UpdateMacroTestReport(CMacroTest* pItem)
{
	CReport *pReport = (CReport*)pItem->GetReport(-1);

	if (pReport == NULL)
	{
		//ASSERT (FALSE);//2017.05.17   调试debug时注释此断言  shaolei  20201023
		pReport = AddMacroTestReport(pItem);//2017.05.17
	}

	CValues pValues;
	CString bstrReport; 

	try
	{
		bstrReport = m_pMacroTestInterface->GetReport();

		if (g_nLog_TestControl_Msg == 1)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("MacroTest.GetReport:"));
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), bstrReport.GetString());
		}
	}
	catch(...)
	{
	}

	BackMacroTestResults(pReport);

	pValues.SetValuesByString(bstrReport);
	pReport->UpdateReportValues(&pValues);

	UpdateMacroTestResults(pReport);

	//shaolei 2023-9-1 通过GetReport返回的报告，没有name属性
	ats_InitReportValuesName(pReport, pItem);

	//2019-4-27  李俊庆
	//对于一个开关量测试仪对应多台装置的测试，开出传动测试，需要对开入节点进行切分提取
	//最后切分提取主装置的部分
	//2019-4-27：多装置模式下，如果是每台装置都单独执行
	if (!pItem->IsMdvTestEach())
	{
		return pReport;
	}

	if (m_bUseBinaryOffset)
	{
		CGuideBookTool::ExtractBinputsResult(pReport->m_pValues, m_nBinRngBegin, m_nBinRngEnd, m_pGuideBook->m_nBinOffset);
		CString strSyntax;
		pItem->RunResultScript(strSyntax);
		FillReport(pReport, m_nMacroTestTimes);
	}

	return pReport;
}

void CTestControlBase::AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes)
{

}

void CTestControlBase::AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes)
{

}

long CTestControlBase::FinishTestItemMacroTest(CMacroTest* pItem)
{
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("+++for debug+++CTestControlBase::FinishTestItemMacroTest  ---%s"), pItem->m_strID.GetString());
	m_bMacroTestFinished = TRUE;
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	//shaolei  20210520
	//从工具栏点击“停止测试”按钮，在Stt规约下，也会发送StopTest指令，底层会回复TestFinished
	//此时，m_pCurrTestItem已经 == NULL
	if (pItem == NULL)
		return 0;

	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestCotrAbnom.GetString()/*L"------测试仪控制程序发生异常"*/, pItem->m_strName.GetString());
		return 0;
	}

	if (m_pCurrSubTestItem != NULL)
	{
		if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			CCommCmd *pCCommCmd = (CCommCmd*)m_pCurrSubTestItem;

			if (pCCommCmd->IsBeginModeAsynchronous())
			{
				TestItem((CCommCmd*)m_pCurrSubTestItem);
				return 0;
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,  g_sLangTxt_ItemUncmpltS.GetString()/*L"------电气量项目\"%s\"还有子项目没有完成"*/, pItem->m_strName.GetString());
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}

	//执行测试结果操作，针对于不同的测试模式，执行不同的处理运算
	FinishTestItemMacroTest_Only(pItem);

	return 0;
}

long CTestControlBase::FinishTestItemHdResReqest(CHdResReqest* pItem)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	if (pItem == NULL)
		return 0;

	if (pItem->GetClassID() != GBCLASSID_HDRESREQUEST)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestCotrAbnom.GetString()/*L"------测试仪控制程序发生异常"*/, pItem->m_strName.GetString());
		return 0;
	}

	CReport *pReport = (CReport*)pItem->GetReport(-1);

	if (pReport == NULL)
	{
		pReport = AddHdResReqestReport(pItem);//2017.05.17
	}

	CValues pValues;
	CString bstrReport; 

	try
	{
		bstrReport = m_pMacroTestInterface->GetReport();
	}
	catch(...)
	{
	}

	pValues.SetValuesByString(bstrReport);
	pReport->UpdateReportValues(&pValues);
	CString strReqRslt;

	if (pReport->GetReportValueEx(_T("ReqRslt"), strReqRslt))
	{
		if (strReqRslt == _T("1"))
		{
			pItem->SetState(TEST_STATE_ELIGIBLE);
			m_pGuideBook->UpdateTestApps(m_pMacroTestInterface->GetResults());
			TestNextItem();			//请求成功，继续测试
			return 0;
		}
		else
		{	//请求失败，设置为停止测试状态，添加到停止测试列表
			m_listHdResReqFaildItem.AddTail(pItem);
			pItem->SetState(TEST_STATE_STOPED);
			m_pCurrTestItem = m_pItemContainer->GetNextItemForHdResReqFailed();

			if (m_pCurrTestItem == NULL)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Error, not Release for requset[%s]"), pItem->m_strName.GetString());
				StopTest(_T(""));
			}
			else
			{
				TestItem(m_pCurrTestItem);
			}
		}

		return 0;
	}
	
	pItem->SetState(TEST_STATE_STOPED);
	StopTest(_T(""));
	
	return 0;
}

long CTestControlBase::FinishTestItemMacroCharTest(CMacroCharItems* pMacroCharItems)
{
	pMacroCharItems->SetState(TEST_STATE_ELIGIBLE);

	//测试下一个项目
	TestNextItem();

	return 0;
}

//2019-4-27  lijunqing
//在多装置模式下，FinishTestItemMacroTest_Only函数的处理方式，
long CTestControlBase::FinishTestItemMacroTest_Only(CMacroTest* pItem)
{
	if (FinishTestItemMacroTest_IsError(pItem))
	{
		return 0;
	}
	else
	{
		FinishTestItemMacroTest_Report(pItem);
	}

	return FinishTestItemMacroTest_Process(pItem);
}

long CTestControlBase::FinishTestItemMacroTest_IsError(CMacroTest* pItem)
{
	if (pItem == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_EltrcProjectCmplt/*L"     电气量项目完成"*/);
		try
		{
			if (m_pMacroTestInterface != NULL)
			{
				if (g_nLog_TestControl_Msg == 1)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, _T("     -- call StopTest"));
				}

				m_pMacroTestInterface->StopTest();
			}
		}
		catch (...)
		{
            CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("call StopTest error-----"));
		}

		return TRUE;
	}

	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestCotrAbnom2.GetString()/* L"      测试仪控制程序发生异常"*/, pItem->m_strName.GetString());
		return TRUE;
	}

	return FALSE;
}

long CTestControlBase::FinishTestItemMacroTest_Report(CMacroTest* pItem)
{
	//shaolei 2024-1-8注释此处。原因：在外部调用进来的时候，已经做过判断了，不用再重复判断
// 	if (FinishTestItemMacroTest_IsError(pItem))
// 	{
// 		return 0;
// 	}

	DWORD dwBegin = ::GetTickCount();
	//添加报告
	CExBaseList *pList = pItem->GetSubGbItems();
	CReport *pReport = NULL;
	
	//2019-4-27：多装置模式下，如果是每台装置都单独执行
	if (pItem->IsMdvTestEach())
	{//执行自身的函数
		pReport = CTestControlBase::UpdateMacroTestReport(pItem);   //2017.05.17
	}
	else
	{//执行多装置统一处理的函数
		pReport = UpdateMacroTestReport(pItem);   //2017.05.17
	}

	//2019-1-7  在多装置多组的模式下，如果需要提取开入参数，则不执行脚本
	//if (!CGuideBookTool::NeedExtractBinputsResult(pReport->m_pValues))
	if (ats_IsTestControlMode_MDVMGBRP(this) && CGuideBookTool::NeedExtractBinputsResult(pReport->m_pValues))
	{
	}
	else
	{
		//执行结果判断脚本
		CString strSyntax;
		m_pCurrReport = pReport;
		long nCurrTestTimes = 1, nRepeatTimes = 1;

		if (pItem->m_nRepeatTimes > 1)
		{
			nCurrTestTimes = m_nMacroTestTimes+1;  //此时，m_nMacroTestTimes还没有递增。此处需要+1
			nRepeatTimes = pItem->m_nRepeatTimes;
		}
		else
		{
			pItem->GetTestTimes(nCurrTestTimes, nRepeatTimes);
		}

		pItem->RunResultScript(strSyntax, TRUE, nCurrTestTimes, nRepeatTimes);
		m_pCurrReport = NULL;

		//填写报告
		pReport = (CReport*)pItem->GetReport(-1);

		//特性曲线处理，更新搜索线的搜索结果
		long nTimes = m_nMacroTestTimes;
		UpdateMacroCharTest_Finished(pItem, pReport, nTimes);

		FillReport(pReport, m_nMacroTestTimes);
	}

	//处理子TestControl
	//2019-4-27：多装置模式下，如果是每台装置都单独执行
	if (pItem->IsMdvTestEach())
	{//执行自身的函数
		CTestControlBase::AfterUpdateMacroTestReport(pItem, m_nMacroTestTimes);
	}
	else
	{//执行多装置统一处理的函数
		AfterUpdateMacroTestReport(pItem, m_nMacroTestTimes);
	}

	if (m_nStopTestByError == 1)
	{
		//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
		//因此单独执行
		WriteItemTempFile(pItem);
		return 0;
	}

	UpdateStateAfterFinishTestItem(pItem);

	if (pItem->m_nRepeatTimes > 1)
	{
		if (!GBS_CanBreakLoop(pItem))//if (pItem->m_nBreakLoopState != 1)
		{
			if (m_nMacroTestTimes >= GetMaxRepeatTimes(pItem->m_nRepeatTimes))
			{
				CreateCalRpt_SubItems(pItem);//处理子项目的计算报告
				pReport = CreateMtFinalReport(pItem);
				//对于重复测试的电气量，用于保存计算结果的报告，也需要执行结果判断脚本
				pItem->RunRsltExpr_Only(m_nMacroTestTimes + 2, pItem->m_nRepeatTimes);//此时，m_nMacroTestTimes还没有递增。此处需要+2
				FillReport(pReport, pItem->m_nRepeatTimes);

				//处理子TestControl
				//2019-4-27：多装置模式下，如果是每台装置都单独执行
				if (pItem->IsMdvTestEach())
				{
					CTestControlBase::AfterCreateMtFinalReport(pItem, pItem->m_nRepeatTimes);
				}
				else
				{
					AfterCreateMtFinalReport(pItem, pItem->m_nRepeatTimes);
				}

				//重复测试的电气量，生成计算报告后，再次触发项目状态改变，以上送REPORT事件
				//shaolei 2023-4-20
				UpdateStateAfterFinishTestItem(pItem);

				WriteItemTempFile(pItem);
			}
		}
	}

	InitAfterMacroTestItemsChanged();

	return 0;
}

long CTestControlBase::FinishTestItemMacroTest_Process(CMacroTest* pItem)
{
	if (FinishTestItemMacroTest_IsError(pItem))
	{
		return 0;
	}

	if (m_nStopTestByError == 1)
	{
		return 0;
	}

	if (pItem->m_nRepeatTimes > 1)
	{
		if (GBS_CanBreakLoop(pItem))//if (pItem->m_nBreakLoopState == 1)
		{
			pItem->FreeTestParas();
			m_nMacroTestTimes = 0;
			//测试下一个项目
			TestNextItem();
		}
		else
		{
			//if (m_nMacroTestTimes >= pItem->m_nRepeatTimes-1)
			if (m_nMacroTestTimes >= GetMaxRepeatTimes(pItem->m_nRepeatTimes))
			{
				m_nMacroTestTimes = 0;
				pItem->FreeTestParas();
				//测试下一个项目
				TestNextItem();
			}
			else
			{
				m_nMacroTestTimes++;
				TestItem(pItem);
			}
		}
	}
	else
	{
		pItem->FreeTestParas();
		m_nMacroTestTimes = 0;
		//测试下一个项目
		TestNextItem();
	}

	return 0;
}

long CTestControlBase::GetDelayBeforeCmd(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	return pCmd->GetDelayBeforeCmd();
}

long CTestControlBase::GetDelayAfterCmd(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	return pCmd->GetDelayAfterCmd();
}

void CTestControlBase::AddSysParasToTask(CSysParaEdit* pItem)
{

}


long CTestControlBase::FinishTestItemSysParaEdit(CSysParaEdit* pItem)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);
	FinishTestItemSysParaEdit_ProcessReport(pItem);

	//保存到
	AddSysParasToTask(pItem);
	
	TestNextItem();

	return 0;
}

long CTestControlBase::FinishTestItemSysParaEdit(CSysParaEdit* pItem, CSysParaEdit* pSrcItem)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	//添加报告
	pItem->m_pReports->InitReports(pSrcItem->m_pReports);

	//2021-8-10  lijunqing
	CReport *pReport = pItem->GetReport(-1);

	return FinishTestItemSysParaEdit_ProcessReport(pItem, pReport);
}

long CTestControlBase::FinishTestItemSysParaEdit_ProcessReport(CSysParaEdit* pItem)
{
	//添加报告
	CReport *pReport = pItem->GetReport(-1);//AddReport(pItem, -1, -1); ////2017.05.17
	
	//CSysParaEditGroups *pGroups = (CSysParaEditGroups*)pItem->GetSysParaEditGroup();
	CExBaseList *pList = pItem->GetSysParaEditDataObjList();
	//CValues *pValus = pItem->GetReportValues();//->GetReportValues();
	pReport->SetReportValues(pList);

	if (pItem->m_strDatasetPath == g_strwSysPara)
	{
		CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
		pList = pDevice->GetSysParas();
		pReport->AppendReportValues(pList);
	}
	else
	{
		pReport->AppendReportValues(pList);
	}

	return FinishTestItemSysParaEdit_ProcessReport(pItem, pReport);
}

long CTestControlBase::FinishTestItemSysParaEdit_ProcessReport(CSysParaEdit* pItem, CReport *pReport)
{
	//执行结果判断脚本
	CString strSyntax;
	m_pCurrReport = pReport;
	pItem->RunResultScript(strSyntax);
	m_pCurrReport = NULL;


	//如果有语法错误，需要在界面显示

	//填写报告
	FillReport(pReport, 0);

	UpdateStateAfterFinishTestItem(pItem);

	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	//因此单独执行
	WriteItemTempFile(pItem);

	return 0;
}

long CTestControlBase::FinishTestItemCommCmd(CCommCmd* pItem)
{
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("+++for debug+++ CTestControlBase::FinishTestItemCommCmd    ->%s"), pItem->m_strName.GetString());
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	if (pItem == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunFalse2.GetString()/*L"通讯过程中出现错误，Item==NULL"*/);
		return 0;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_NotCommunCmd.GetString()/*L"通讯过程中出现错误，不是通讯命令"*/);
		return 0;
	}

	CCmd *pCmd = pItem->GetCmd();
	BOOL bFinish = FALSE;

	//处理通讯命令的后续项目，例如：投退压板，每次只能投退一个压板
	ContinueTestCommCmd(pItem, bFinish);

	//if (bFinish)
	{
		long nDelay = GetDelayAfterCmd(pItem);

		if (nDelay > 0)
		{
			m_pTCtrlWnd->m_pTestItemRef = pItem;
			m_pTCtrlWnd->SetTimer(TIMER_DELAY_AFTER_CMM_CMD, nDelay, NULL);
		}
		else
		{
			//如果不需要延时，则直接处理结束
			ExcuteCommCmdOnDelayAfterFinish(pItem);
		}
	}

	return 0;
}


//重新填写报告
void CTestControlBase::ReFillReport()
{

}

//调整报告，试验完成后归档调用
void CTestControlBase::AdjustReport(CThreadProgressInterface *pProgress)
{
	m_oTCtrlMsgRcv.OnExportRptEvent(this, SYS_STATE_XEVENT_EVENTID_ExportBegin);

	if (m_pReportFill != NULL)
	{
		m_pReportFill->AdjustReport(pProgress);
	}

	m_oTCtrlMsgRcv.OnExportRptEvent(this, SYS_STATE_XEVENT_EVENTID_ExportFinish);
}

BOOL CTestControlBase::SetItemState(CDataGroup *pParas)
{
	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	CGbItemBase *pItemFind = NULL;
	CString strItemPath, strItemIndex;
	pParas->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath);
	pParas->GetDataValue(STT_CMD_PARA_ItemIndex, strItemIndex);

	if (strItemPath.GetLength() > 0)
	{
		pItemFind = (CGbItemBase*)Gb_GetItem(m_pGuideBook, strItemPath);

		if (pItemFind == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, "GetItem([%s] == NULL", strItemPath.GetString());
		}
	}
	else
	{
		long nItemIndex = CString_To_long(strItemIndex);
		pItemFind = Gb_GetItemByIndex(m_pGuideBook, nItemIndex);

		if (pItemFind == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, "GetItem([%d] == NULL", nItemIndex);
		}
	}

	if (pItemFind == NULL)
	{
		return FALSE;
	}

	long nValue = 1;

	if (pParas->GetDataValue(STT_CMD_PARA_Show, nValue))
	{
		pItemFind->SetShow(nValue);
	}

	if (pParas->GetDataValue(STT_CMD_PARA_Enable, nValue))
	{
		pItemFind->SetEnable(nValue);
	}

	if (pParas->GetDataValue(STT_CMD_PARA_Select, nValue))
	{
		pItemFind->SetSelect(nValue);
		Gb_SetTestItemSelectedState(pItemFind, nValue);
	}

	if (pItemFind->m_nIndex < m_nCurrTestItemIndex
		/*&& nValue == 1*/)
	{
		m_nCurrTestItemIndex = pItemFind->m_nIndex;
	}

	//2024-9-13 注释此处
	//m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItemFind, TRUE);

	return TRUE;
}

void CTestControlBase::OnTestItemCount_TCtrlMsg(long nItemCount)
{
	m_oTCtrlMsgRcv.OnTestItemCount(nItemCount, this);
}

void CTestControlBase::OnTestBegin_TCtrlMsg()
{
	m_oTCtrlMsgRcv.OnTestBegin(this);
}

void CTestControlBase::OnStopTest_TCtrlMsg(long nType)
{
	m_oTCtrlMsgRcv.OnStopTest(nType, this);
}

void CTestControlBase::OnException_TCtrlMsg(long nEvent, const CString &strError)
{
	m_oTCtrlMsgRcv.OnException(nEvent, strError, this);
}

void CTestControlBase::OnConnectSuccess_TCtrlMsg()
{
	m_oTCtrlMsgRcv.OnConnectSuccess(this);
}

void CTestControlBase::AdjustReport_FillEmpty()
{
	m_pReportFill->AdjustReport_FillEmpty();
}

long CTestControlBase::InitFillReport(CGbItemBase* pItem)
{
	if (m_pReportFill == NULL)
	{
		return 0;
	}

	CTestControlBase *pTestControl = (CTestControlBase*)pItem->GetAncestor(GBCLASSID_TESTCONTROL);
	pTestControl->m_pReportFill->InitFillReport(pItem);

	return 0;
}

long CTestControlBase::InitFillReport(CReport* pReport)
{
	if (m_pReportFill == NULL)
	{
		return 0;
	}

	CTestControlBase *pTestControl = (CTestControlBase*)pReport->GetAncestor(GBCLASSID_TESTCONTROL);
	pTestControl->m_pReportFill->InitFillReport(pReport);

	return 0;
}

/*
CCommCmd* ats_CloneCommCmdFromDB(CCommCmd *pCommCmd, CBinarySerialBuffer &oBuffer)
{
	CReports *pReports = pCommCmd->GetReports();
	CReport* pReport = (CReport*)pReports->GetHead();

	if (pReport == NULL)
	{
		return NULL;
	}

	if (pReport->m_pValues->GetCount() > 0)
	{
		return NULL;
	}

	CString strTempFileName = ats_GetBinaryTempFile(pCommCmd);
	CCommCmd *pGbItemForRpt = (CCommCmd*)pCommCmd->OpenBinaryTempFileForRpt(strTempFileName, oBuffer);

	return pGbItemForRpt;
}
*/
CGbItemBase* ats_CloneGbItemFromDB(CGbItemBase *pGbItem)
{
	CGbItemBase *pNewForRptDB = NULL;
	CString strTempFilePath = ats_GetBinaryTempFilePath(pGbItem);
	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, pGbItem);
	pNewForRptDB = pGbItem->CloneForTempFile();
	pNewForRptDB->SetParent(pGbItem->GetParent());
	pNewForRptDB->OpenBinaryTempFile(strTempFileName);
	return pNewForRptDB;
}

//2021-1-2  lijunqing add: BOOL bClone
CGbItemBase* ats_CloneGbItemFromDB(CGbItemBase *pGbItem, CBinarySerialBuffer &oBuffer, BOOL bClone)
{
	CReports *pReports = pGbItem->GetReports();
	CReport* pReport = (CReport*)pReports->GetHead();

	if (pReport == NULL)
	{
		return NULL;
	}

	if (pReport->m_pValues->GetCount() > 0)
	{
		return NULL;
	}

	//2021-1-27  lijunqing 克隆报告时，不删除报告数据，以备后续导出xml或者是excel
	pGbItem->OpenBinaryTempFileReport(oBuffer);

	return NULL;
//	CString strTempFileName = ats_GetBinaryTempFile(pGbItem);
// 	if (bClone)
// 	{//创建克隆对象
// 		CGbItemBase *pGbItemForRpt = (CCommCmd*)pGbItem->OpenBinaryTempFileForRpt(strTempFileName, oBuffer);
// 		return pGbItemForRpt;
// 	}
// 	else
// 	{//打开自身临时报告文件
// 		pGbItem->OpenBinaryTempFile(strTempFileName, oBuffer);
// 		return NULL;
// 	}
}

void CTestControlBase::ClearItemInDbState()
{
	if (m_pGuideBook->IsSaveRptToDB() || g_theSmartTestBaseApp->IsSaveRptToDB())
	{
		CString strTempFilePath = GetItemTempPath();
		gb_ClearItemInDbState(m_pGuideBook, strTempFilePath, g_theSmartTestBaseApp->IsWriteTestTempFile());
	}
}

long CTestControlBase::GenerateWordReport(CGbItemBase* pItem, CBinarySerialBuffer *pBuffer)
{
	if(pItem == NULL)
		return -1;

	if (!pItem->HasReport())
	{
		return -1;
	}

	CGbItemBase *pNewForDb = NULL;

	if (pItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		CCommCmd *pCommCmd = (CCommCmd*)pItem;
		//2021-1-2  lijunqing 不克隆，打开自身临时报告，再释放
		pNewForDb = ats_CloneGbItemFromDB(pCommCmd, *pBuffer, FALSE);
		CExBaseObject *pParent = (CExBaseObject*)pItem->GetParent();

		if (pParent->GetClassID() == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest*)pParent;

			if (pMacroTest->m_nRepeatTimes > 0)
			{
				if (pCommCmd->GetCmd()->m_nRepeatTimes <= 1)
				{
					BOOL bRet = FALSE;

					if (pNewForDb != NULL)
					{
						FillReportRepeatCommCmd(pMacroTest, (CCommCmd*)pNewForDb);
						delete pNewForDb;
					}
					else
					{
						FillReportRepeatCommCmd(pMacroTest, pCommCmd);
					}

					return bRet;
				}
			}
		}
	}
	else
	{
        if (m_pGuideBook->IsSaveRptToDB() || g_theSmartTestBaseApp->IsSaveRptToDB())
		{
			//2021-1-2  lijunqing 不克隆，打开自身临时报告，再释放
			pNewForDb = ats_CloneGbItemFromDB(pItem, *pBuffer, FALSE);
		}
	}

    
	CReports *pReports = pItem->GetReports();

	if (pNewForDb != NULL)
	{
		pReports = pNewForDb->GetReports();
	}

	CReport* pReport = NULL;

	if(m_pReportFill == NULL)
	{
		if (pNewForDb != NULL)
		{
			delete pNewForDb;
		}

		return 0;
	}

	long nCount = pReports->GetCount();
	long nIndex = 0;
	long nPos = 0;
	long nTestIndex = 0;
	long nBeginTestIndex = 0;

	for (nIndex=nCount-1; nIndex>=0; nIndex--)
	{
		pReport = (CReport*)pReports->GetAtIndex(nIndex);
		nPos = pReport->m_strID.ReverseFind('_');

		if (nPos < 0)
		{
			nBeginTestIndex = nIndex;
			break;
		}
		else
		{
			nTestIndex = CString_To_long(pReport->m_strID.Mid(nPos+1));

			if (nTestIndex == 0)
			{
				nBeginTestIndex = nIndex;
				break;
			}
		}
	}

	//for (nIndex=nCount-1; nIndex>=0; nIndex--)
	//处理项目覆盖填写的问题
	for (nIndex=nBeginTestIndex; nIndex < nCount; nIndex++)
	{
		pReport = (CReport*)pReports->GetAtIndex(nIndex);
		pReport->SetParent(pReports);   //shaolei  20210624  此处pReport的parent不对，可能与m_oListItems.AddTail(pObj);有关
		nPos = pReport->m_strID.ReverseFind('_');

		if (nPos < 0)
		{
            FillReportEx(pReport, 0, g_theSmartTestBaseApp->IsInsertDataLinkWhenEligible());
		}
		else
		{
			nTestIndex = CString_To_long(pReport->m_strID.Mid(nPos+1));
            FillReportEx(pReport, nTestIndex, g_theSmartTestBaseApp->IsInsertDataLinkWhenEligible());
		}
	}

	if (pNewForDb != NULL)
	{
		delete pNewForDb;
	}

	return 0;
}

long CTestControlBase::FillReportRepeatCommCmd(CMacroTest *pMacroTest, CCommCmd* pCommCmd)
{
    
	CReports *pReports_CommCmd = pCommCmd->GetReports();
	CReports *pReports_MacroTest = pMacroTest->GetReports();
	CReport* pReport = NULL;
	CReport* pReportFill = NULL;

	long nCount = pReports_MacroTest->GetCount();
	long nIndex = 0;
	long nPos = 0;
	long nTestIndex = 0;
	long nIndex_CommCmd = pReports_CommCmd->GetCount() - 1;

	for (nIndex=nCount-1; nIndex>=0; nIndex--)
	{
		pReport = (CReport*)pReports_MacroTest->GetAtIndex(nIndex);
		pReportFill =  (CReport*)pReports_CommCmd->GetAtIndex(nIndex_CommCmd);
		nIndex_CommCmd--;
		nPos = pReport->m_strID.ReverseFind('_');

		if (nPos < 0)
		{
			if (pReportFill != NULL)
			{
                FillReportEx(pReportFill, 0, g_theSmartTestBaseApp->IsInsertDataLinkWhenEligible());
			}

			break;
		}
		else
		{
			nTestIndex = CString_To_long(pReport->m_strID.Mid(nPos+1));

			if (pReportFill != NULL)
			{
                FillReportEx(pReportFill, nTestIndex, g_theSmartTestBaseApp->IsInsertDataLinkWhenEligible());
			}

			if (nTestIndex == 0)
			{
				break;
			}
		}
	}

	return 0;
}

long CTestControlBase::FillReport(CReport* pReport, long nRepeatIndex)
{
	if (pReport == NULL)
	{
		return 0;
	}

	//if (!TCC_IsDebugWithoutReport())
	{
		if(m_pReportFill != NULL)
		{
            FillReportEx(pReport, nRepeatIndex, g_theSmartTestBaseApp->IsInsertDataLinkWhenEligible());
		}
	}

	return 0;
}

long CTestControlBase::FillParentItemsReport(CGbItemBase *pItems)
{
	if (!Gb_IsItemsTestFinished(pItems))
	{
		return 0;
	}

	pItems->UpdateItemsReport();
	CReport *pReport = pItems->GetReport(-1);

	FillReportEx(pReport, 0, 0);
	CBaseObject *pParent = pItems->GetParent();

	if (pParent == NULL)
	{
		return 0;
	}

	UINT nClassID = pParent->GetClassID();

	if (pParent != NULL)
	{
		//for debug  注释掉GuideBook的报告填写
		//GuideBook 会填写全局数据的部分，每个项目测试结束，在填写父项目报告时，都会填写全局数据部分，因此注释此处
		if (nClassID == GBCLASSID_ITEMS || nClassID == GBCLASSID_DEVICE
			/*|| nClassID == GBCLASSID_GUIDEBOOK*/ || nClassID == GBCLASSID_JOBGUIDE)
		{
			FillParentItemsReport((CItems*)pParent);
		}
	}

	return 0;
}

void CTestControlBase::SetTestItemSelectedState(CGbItemBase *pItem,long nSelect)
{
	if (!(pItem->GetEnable() && pItem->GetShow() ) )
	{
		return;
	}

	if (nSelect == 0)
	{
		nSelect = 1;
	}
	else
	{
		nSelect = 0;
	}

	Gb_SetTestItemSelectedState(pItem, nSelect);

	m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem, FALSE);
}

void CTestControlBase::UpdateDvmLdeviceID()
{
	if (m_pGuideBook->m_strPpEngineProgID != g_strPpEngineProgIDMms)
	{
		return;
	}

	CDvmDevice oDvmDevice;
	CProtocolDeviceInterface* oPoDevice = m_oDeviceRefs.Find(0, 0);
    CString strLdXml = oPoDevice->GetXmlDataLD();

    wchar_t *pbstr = strLdXml.AllocSysString();
    oDvmDevice.SetXml(pbstr, CDataMngrXmlRWKeys::g_pXmlKeys);
    ::SysFreeString(pbstr);

	if (oDvmDevice.GetCount() == 0)
	{
		return;
	}

	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	CCpus *pCpus = pDevice->GetCpus();
	POS pos = pCpus->GetHeadPosition();
	CCpu *pCpu = NULL;
	CString strKey;
	CDvmLogicDevice *pLdevice = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)pCpus->GetNext(pos);
		strKey = GetLdKey(pCpu->m_strID);
		pLdevice = FindByLdKey(&oDvmDevice, strKey);

		if (pLdevice != NULL)
		{
			pCpu->m_strID = pLdevice->m_strID;
			break;
		}
	}
}

//多装置、多组测试功能跳转  2017-11-22
BOOL CTestControlBase::GBS_CanBreakLoop(CGbItemBase *pCurrItem)
{
	return pCurrItem->m_nBreakLoopState == 1;
}

void CTestControlBase::GBS_ClearBreakLoopState(CGbItemBase *pItem)
{
	
}

void CTestControlBase::GBS_GotoItemEx(CGbItemBase *pCurrItem, CGbItemBase *pGotoItem, const CString &strGotoItemPath, long nRslt, long nAndOr)
{
	m_pItemGotoItemEx = pGotoItem;
	m_pItemGotoItemEx_Curr = pCurrItem;
	m_nGotoItemExAndOr = nAndOr;
	m_nGotoItemExRsltState = nRslt;
	m_strGotoItemExPath = strGotoItemPath;

	GBS_GotoItemEx_Go(m_pItemGotoItemEx);
}

void CTestControlBase::GBS_GotoItemEx_Go(CGbItemBase *pItem)
{
	GotoItem(pItem);
}

long CTestControlBase::GetBreakLoopState()
{
	if (m_pCurrSubTestItem != NULL)
	{
		if (m_pCurrSubTestItem->m_nBreakLoopState != 0)
		{
			return 1;
		}
	}

	return m_pCurrTestItem->m_nBreakLoopState;	
}

void CTestControlBase::RcdCmp(const CString &strStdFile, const CString &strTestFile)
{
    CRecorderInterface *pRecord = g_theSmartTestBaseApp->GetRecorder();

	if (pRecord == NULL)
	{
		return;
	}

	pRecord->RcdCmp(strStdFile, strTestFile);

	//获取结果数据
}


void CTestControlBase::RcdAnalyse(const CString &strTestFile)
{
    CRecorderInterface *pRecord = g_theSmartTestBaseApp->GetRecorder();

	if (pRecord == NULL)
	{
		return;
	}

	pRecord->RcdAnalyse(strTestFile);

	//获取结果数据
}

CString CTestControlBase::GetLdKey(const CString &strLdevice)
{
    CTCtrlCntrConfig *pConfig = g_theSmartTestBaseApp->GetCntrConfig();
	CString strKey;

	if (pConfig == NULL)
	{
		return strKey;
	}

	CDataTypes *pDvmTestKeyDataTypes = pConfig->GetDvmTestKeyDataTypes();
	CDataType *pDataType = (CDataType*)pDvmTestKeyDataTypes->FindByID(_T("ldevice-key"));

	if (pDataType == NULL)
	{
		return strKey;
	}

	POS pos = pDataType->GetHeadPosition();
	CDataTypeValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDataTypeValue *)pDataType->GetNext(pos);

		if (strLdevice.Find(p->m_strID) >= 0)
		{
			strKey = p->m_strID;
			break;
		}
	}

	return strKey;
}

CDvmLogicDevice* CTestControlBase::FindByLdKey(CDvmDevice *pDevice, const CString &strKey)
{
	POS pos = pDevice->GetHeadPosition();
	CDvmLogicDevice *p = NULL, *pFind = NULL;

	if (strKey.GetLength() == 0)
	{
		return NULL;
	}

	while (pos != NULL)
	{
		p = (CDvmLogicDevice *)pDevice->GetNext(pos);

		if (p->m_strID.Find(strKey) >= 0)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}


long CTestControlBase::LocateReport(CGbItemBase* pItem, long nIndex)
{
	if(pItem == NULL)
		return -1;

	//CReport* pReport = (CReport*)pItem->GetReports()->GetTail();

	//if (!TCC_IsDebugWithoutReport())
	{
		if(m_pReportFill)
		{
			m_pReportFill->LocateReport(pItem);
		}
	}

	return 0;
}

long CTestControlBase::LocateReport(CGbItemBase* pItem)
{
	m_oTCtrlMsgRcv.LocateItemReport(pItem);

	return 0;
}

void CTestControlBase::PrintReport()
{
	if (m_pReportFill == NULL)
	{
		return;
	}

	//if (!TCC_IsDebugWithoutReport())
	{
		m_pReportFill->PrintReport();
	}
}

void CTestControlBase::ExportPdf()
{
	if (m_pReportFill == NULL)
	{
		return;
	}

	//if (!TCC_IsDebugWithoutReport())
	{
		//m_pReportFill->ExportPdf();
	}
}

void CTestControlBase::ZoomReport(long nPercentage)
{
	if (m_pReportFill == NULL)
	{
		return;
	}

	//if (!TCC_IsDebugWithoutReport())
	{
		m_pReportFill->ZoomReport(nPercentage);
	}
}

long CTestControlBase::GetZoomReport()
{
	if (m_pReportFill == NULL)
	{
		return 100;
	}

	//if (!TCC_IsDebugWithoutReport())
	{
		return m_pReportFill->GetZoomReport();
	}

	return 100;
}

CString CTestControlBase::GetReportFile()
{
	CString strReportFile = m_strGbBinaryFile;//GetReportFileName(m_pTestProject);
	long nPos = strReportFile.ReverseFind('.');
	strReportFile = strReportFile.Left(nPos + 1);
	strReportFile += g_strDocFilePostfix;
	return strReportFile;
}

CString CTestControlBase::GetSysReportFile()
{
	return m_strGbBinaryFile;
//	CString strSysREportFile = m_strGbBinaryFile;//GetGuideBookBinaryFileName(m_pTestProject);
//	return strSysREportFile;
}


//通讯
BOOL CTestControlBase::HasCommCmdEngine(CCommCmd *pItem)
{
	long nCpusIndex = pItem->GetCpusIndex();

	if (nCpusIndex == DSID_ALL_DVM)
	{
		nCpusIndex = m_nCommCmdCurrDeviceIndex;
	}

	CPpDeviceRef *pRef = (CPpDeviceRef*)m_oDeviceRefs.GetAtIndex(nCpusIndex);

	if (pRef == NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE; //(pRef->m_oPpDevice != NULL);
	}
// 	if (m_oPpDevice != NULL)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (m_pGuideBook->m_strPpTemplateFile.GetLength() < 5)
// 	{
// 
// 	}
// 
// 	if (g_strPpEngineProgIDMms == m_pGuideBook->m_strPpEngineProgID)
// 	{
// 		return TRUE;
// 	}
// 	else
// 	{
// 		if (m_pGuideBook->m_strPpTemplateFile.GetLength() < 5)
// 		{
// 			return FALSE;
// 		}
// 		else
// 		{
// 			return TRUE;
// 		}
// 	}
}

//////////////////////////////////////////////////////////////////////////
//通讯命令处理
long CTestControlBase::GetCommCmdCurrDeviceIndex(CCommCmd *pCommCmd)
{
	long nCpusIndex = pCommCmd->GetCpusIndex();

	if (nCpusIndex == DSID_ALL_DVM)
	{
		nCpusIndex = m_nCommCmdCurrDeviceIndex;
	}

	return nCpusIndex;
}

CDataSet* CTestControlBase::GetDataset(CCommCmd *pCommCmd, CString *pStrDatasetPath)
{
	long nCpusIndex = GetCommCmdCurrDeviceIndex(pCommCmd);
	CDataSet *pDataset = pCommCmd->GetDataset(nCpusIndex);

	if (nCpusIndex > 0 && pStrDatasetPath != NULL && pDataset != NULL)
	{
		CExBaseObject *pCpu = (CExBaseObject*)pDataset->GetParent();
        pStrDatasetPath->Format(_T("%s$%s"), pCpu->m_strID.GetString(), pDataset->m_strID.GetString());
	}

	return pDataset;
}

long CTestControlBase::JudgeItemGotoItemEx(CGbItemBase **ppItemGotoItemEx_Curr, CString &strGotoItemExPath, long &nGotoItemLogic)
{
	if (m_pItemGotoItemEx_Curr == NULL || m_pItemGotoItemEx == NULL)
	{
		return 0;
	}

	if (m_strGotoItemExPath.GetLength() > 0)
	{
		strGotoItemExPath = m_strGotoItemExPath;
		*ppItemGotoItemEx_Curr = m_pItemGotoItemEx_Curr;
		nGotoItemLogic = m_nGotoItemExAndOr;
		return 1;
	}
	else
	{
		return 0;
	}

// 	if ( m_nGotoItemExRsltState == m_pItemGotoItemEx_Curr->GetRsltJdg() )
// 	{
// 		return 1;
// 	}
// 	else
// 	{
// 		return 0;
// 	}
}

BOOL CTestControlBase::IsDeviceConnectSucc(CCommCmd *pCommCmd)
{
// 	CCmd *pCmd = pCommCmd->GetCmd();
// 
	if (!pCommCmd->IsUseConnect())
	{
		return TRUE;
	}

	long nCpusIndex = GetCommCmdCurrDeviceIndex(pCommCmd);
	CPpDeviceRef *p = (CPpDeviceRef*)m_oDeviceRefs.GetAtIndex(nCpusIndex);
	ASSERT (p != NULL);

	if (p->IsDeviceConnectSucc())
	{
		return TRUE;
	}

	//链接设备
	DeviceCmmConfig(p);

	return p->IsDeviceConnectSucc();
// 
// 	if (p != NULL)
// 	{
// 		return p->m_bConnected;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
}

/*
<group id="omm-config" >  【通信地址设置】
	<data id="serial" value=""/>【串口】
		<value id="port_number" value="4"/>
		<value id="baud-rate" value="4800"/>
		<value id="byte-size" value="8"/>
		<value id="stop-bit" value="2"/>
		<value id="parity" value="0"/>
		<value id="port_number" value="4"/>
	</data>
	<data id="tcp-server" value=""/>
		<value id="local-ip" value="127.0.0.1"/>
		<value id="local-port" value="2404"/>
	</data>
	<data id="tcp-client" value=""/>
		<value id="local-ip" value="127.0.0.1"/>
		<value id="local-port" value="0"/>
		<value id="remote-ip" value="100.100.102.1"/>
		<value id="remote-port" value="2404"/>
	</data>
	<data id="udp-server" value=""/>
		<value id="local-ip" value="127.0.0.1"/>
		<value id="local-port" value="2404"/>
		<value id="use-broadcast" value="0"/>
		<value id="multicast-ip" value="0.0.0.0"/>
		<value id="multicast-port" value="0"/>
	</data>
	<data id="udp-client" value=""/>
		<value id="local-ip" value="127.0.0.1"/>
		<value id="local-port" value="2404"/>
		<value id="remote-ip" value="100.100.102.1"/>
		<value id="remote-port" value="2404"/>
		<value id="use-broadcast" value="0"/>
		<value id="multicast-ip" value="0.0.0.0"/>
		<value id="multicast-port" value="0"/>
	</data>
</group>
*/
void CTestControlBase::InitCmmConfig(CDataGroup *pCmmConfig)
{
	m_oCmmConfig.DeleteAll();

    if (pCmmConfig != NULL)
    {
        m_oCmmConfig.AppendClone(pCmmConfig);
    }
}

CDataGroup* CTestControlBase::GetCmmConfig()
{
    return &m_oCmmConfig;
}

long CTestControlBase::GetDeviceRefsCount()
{
	return m_oDeviceRefs.GetCount();
}

void CTestControlBase::ReleasePpEngine()
{
	CProtocolEngineFactory::ReleasePpEngine();
	ReleasePpDeviceRefs(TRUE);
}

//执行项目的测试：通讯命令通讯前延时
void CTestControlBase::ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem)
{
	ClearGotoItemEx();

	if (pItem == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_TestItemFalse.GetString() /*_T("    >>>>>>>ExcuteCommCmd:测试项目时序发生错误")*/);
		return;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("    >>>>>>>ExcuteCommCmd：%s"), pItem->m_strName);

	if (m_pCurrTestItem == NULL)
	{
		//CLogPrint::LogString(XLOGLEVEL_ERROR, L"系统测试错误：ExcuteCommCmdOnDelayBeforeFinish");
		return;
	}

	CTestControlBase *pTestContrl = (CTestControlBase*)pItem->GetAncestor(GBCLASSID_TESTCONTROL);
	//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("***************ExcuteCommCmdOnDelayBeforeFinish:[%s][%s] / [%s]"), pTestContrl->m_strName, m_strName, pItem->m_strName);

	CCmd *pCmd = NULL;
	InitFillReport(pItem);

	if (pItem == NULL)
	{
		if (m_pCurrSubTestItem != NULL)
		{
			pItem = (CCommCmd*)m_pCurrSubTestItem;
		}
		else 
		{
			if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
			{
				pItem = (CCommCmd*)m_pCurrTestItem;
			}
		}
	}

	if (pItem == NULL)
	{
		//CLogPrint::LogString(XLOGLEVEL_ERROR, L"系统测试错误：ExcuteCommCmdOnDelayBeforeFinish");
		return;
	}

	pCmd = pItem->GetCmd();
	CString strDatasetPath = pCmd->m_strDatasetPath;
	//CGbCommCmd *pGbCmdCfg = (CGbCommCmd*)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pItem->m_strCommCmdID);  //命令的类型
	//CCpu *pCpu = (CCpu*)pItem->GetCpu(pCmd->m_strDatasetPath);
	CDataSet *pDataset = GetDataset(pItem, &strDatasetPath);   //pItem->GetDataset();
	BOOL bCanTest = TRUE;

// 	if (pGbCmdCfg == NULL)
// 	{
// 		bCanTest = FALSE;
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("通讯命令项目【%s】定义的【%s】错误"), pItem->m_strName, pItem->m_strType);
// 	}

	if (pDataset == NULL)
	{
		if (pCmd->IsEmptyDataset() && pItem->IsWrite() && pItem->IsCmdNeedDataset())
		{
			if (g_nLog_TestControl_Msg)
			{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunParaFalse.GetString() /*_T("    通讯命令项目【%s】定义的参数【%s】错误")*/
                                       , pItem->m_strName.GetString(), pCmd->m_strDatasetPath.GetString());
			}
            
			//bCanTest = FALSE;
		}
		else
		{
			//bCanTest = TRUE;
		}
	}


	if (pItem->IsWrite())
	{
		if (!bCanTest)
		{
			StopTestExtern();
			return;
		}

		if (!pCmd->IsEmptyDataset())
		{
			if (!WriteDatasToEngine(pItem))
			{
				return;
			}
		}
	}
	else if (pItem->IsRead())
	{
		//SaveCmdDatasToLocal(pItem);
	}
	else
	{
		
	}
	
	InitEngineDataInterface(pItem);

	if (! RunProcedure(pItem->m_strCommCmdID, strDatasetPath//pCmd->m_strDatasetPath
        , 0, 0, ProcedureType_TestItem, m_pTCtrlWnd->GetSafeHwnd()) )
	{
		pItem->DeleteReport();  //执行失败，删除最后一次的报告【测试前添加了最后一次报告】
		StopTestExtern();
	}
}

long CTestControlBase::GetMaxRepeatTimes(long nRepeatTimes)
{
   
    CTCtrlCntrConfig *pCtrlConfig = g_theSmartTestBaseApp->GetCntrConfig();

	if (pCtrlConfig->m_nOwnDefRepeatTimes < 1)
	{
		return nRepeatTimes - 1;
	}

	if (nRepeatTimes > pCtrlConfig->m_nOwnDefRepeatTimes)
	{
		return pCtrlConfig->m_nOwnDefRepeatTimes - 1;
	}

	return nRepeatTimes - 1;
}

long CTestControlBase::GetCmmMaxRetryTimes()
{
   
    CTCtrlCntrConfig *pCtrlConfig = g_theSmartTestBaseApp->GetCntrConfig();

	return pCtrlConfig->m_nCmmMaxRetrytimes;
}

long CTestControlBase::GetCmmRetryDelay()
{
   
    CTCtrlCntrConfig *pCtrlConfig = g_theSmartTestBaseApp->GetCntrConfig();

	return pCtrlConfig->m_nCmmRetryDelay;
}

void CTestControlBase::Update_dsSetting_TimeData_s(CDataSet *pDataset)
{
	return;
   
    CTCtrlCntrConfig *pCtrlConfig = g_theSmartTestBaseApp->GetCntrConfig();

// 	if (!pCtrlConfig->m_nUse_dsSetting_TimeTrans)
// 	{
// 		return;
// 	}
// 	
	POS pos = pDataset->GetHeadPosition();
	CDataObj *pData = NULL;
	CString strUnit;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDataset->GetNext(pos);
		strUnit = pData->m_strUnit;
		strUnit.MakeLower();

		if (strUnit == _T("ms"))
		{
#ifdef _UNICODE
			double dValue = _wtof(pData->m_strValue);
#else
            double dValue = atof(pData->m_strValue.GetString());
#endif
			dValue /= 1000;
			pData->m_strValue.Format(_T("%f"), dValue);
		}
	}
}

void CTestControlBase::Update_dsSetting_TimeData_ms(CDvmDataset *pDataset)
{
	return;
   
    CTCtrlCntrConfig *pCtrlConfig = g_theSmartTestBaseApp->GetCntrConfig();

// 	if (!pCtrlConfig->m_nUse_dsSetting_TimeTrans)
// 	{
// 		return;
// 	}

	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strUnit;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);
		strUnit = pData->m_strUnit;
		strUnit.MakeLower();

		if (strUnit == _T("ms"))
		{
#ifdef _UNICODE
			double dValue = _wtof(pData->m_strValue);
#else
            double dValue = atof(pData->m_strValue.GetString());
#endif
			dValue *= 1000;
			pData->m_strValue.Format(_T("%f"), dValue);
		}
	}
}

//2021-10-14  lijunqing
CDvmDataset* CTestControlBase::CreateNewDvmDatasetForCommCmd(CCommCmd* pItem)
{
	CDvmDataset *pNew = pItem->GetNewDvmDataset(GetCommCmdCurrDeviceIndex(pItem));

	return pNew;
}

BOOL CTestControlBase::WriteDatasToEngine(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	CString strDatasetPath;
	CDvmDataset *pDvmDataset = pItem->GetWriteDvmDataset(GetCommCmdCurrDeviceIndex(pItem), &strDatasetPath);

	if (pDvmDataset == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ItemDataUnexistS .GetString() /*_T("项目(%s)通讯引擎设备数据模型()%s不存在")*/
                                   , pItem->m_strName.GetString(), pCmd->m_strDatasetPath.GetString());
		return FALSE;
	}

	pDvmDataset->m_strID = strDatasetPath;

	CProtocolDeviceInterface* oPpDevice = GetDevicePtr(pItem);
	Update_dsSetting_TimeData_ms(pDvmDataset);

	if (oPpDevice == NULL)
	{
		delete pDvmDataset;
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ItemDataUnexist.GetString() /*_T("项目(%s)通讯引擎设备数据模型不存在")*/
                                   , pItem->m_strName.GetString());
		StopTestExtern();
		return FALSE;
	}

	if (g_nLog_TestControl_Msg == 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("FindDataSet：%s"), pCmd->m_strDatasetPath.GetString());
	}

	CProtocolDatasetInterface* oDataset = NULL;
	
	if (strDatasetPath != pCmd->m_strDatasetPath)
	{
		oDataset = oPpDevice->FindDataSet(strDatasetPath);
	}
	else
	{
		oDataset = oPpDevice->FindDataSet(pCmd->m_strDatasetPath);
	}

	if (oDataset == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,  g_sLangTxt_ItemDataUnexist2.GetString() /*_T("项目【%s】通讯引擎设备数据集【%s】不存在")*/
                                   , pItem->m_strName.GetString(), pCmd->m_strDatasetPath.GetString());
		StopTestExtern();
		delete pDvmDataset;
		return FALSE;
	}

	CString strXmlDatas;

	try
	{
		pDvmDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXmlDatas);
		
		//设置定值数据
		//oPpDevice->SetXmlDataEx(pCmd->m_strDatasetPath, strXmlDatas);
		oDataset->SetXmlData(strXmlDatas);
	}
	catch(...)
	{
	}

	CDataSet *pDataset = GetDataset(pItem);   //pItem->GetDataset();
	pDataset->InitValueByDvmDataset(pDvmDataset, FALSE, dvm_dataset_find_mode_name_id());
	Update_dsSetting_TimeData_s(pDataset);

	delete pDvmDataset;
	oDataset->Release();

	return TRUE;
}

long CTestControlBase::SaveCmdDatasToLocal(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();

	//判断数据是否需要保存到本地设备数据模型
	if (!pCmd->IsCmdNeedWriteToLocal())
	{
		return 0;
	}

	CDataSet *pDataset = GetDataset(pItem);   //pItem->GetDataset();

	if (pDataset == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ItemDataUnexist3.GetString() /*_T("项目【%s】设备数据模型【%s】不存在")*/
                                   , pItem->m_strName.GetString(), pCmd->m_strDatasetPath.GetString());
		//return StopTestExtern();
		return 0;
	}

	pDataset->SetDataSetValue(pCmd);
	Update_dsSetting_TimeData_s(pDataset);

	return 0;
}

long CTestControlBase::ReadEngineDatas(CCommCmd* pItem, CDvmDataset *pShortDatas)
{
	ASSERT (pShortDatas != NULL);
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr(pItem);
	CCmd *pCmd = pItem->GetCmd();

	return ReadEngineDatas(oPpDevice, pItem->m_strName, pCmd->m_strDatasetPath, pShortDatas);
}

long CTestControlBase::ReadEngineDatas(CProtocolDeviceInterface* &oPpDevice, const CString &strName
								   , const CString &strDatasetPath, CDvmDataset *pShortDatas)
{
	if (oPpDevice == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_ItemDataUnexist4.GetString() /*_T("项目【%s】通讯引擎设备数据模型不存在")*/
            , strName.GetString());
		return StopTestExtern();
	}

	if (g_nLog_TestControl_Msg == 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("FindDataSet：%s"), strDatasetPath.GetString());
	}

	CProtocolDatasetInterface* oDataset = oPpDevice->FindDataSet(strDatasetPath);

	if (oDataset == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ItemDataUnexist2.GetString() /*_T("项目【%s】通讯引擎设备数据集【%s】不存在")*/
            , strName.GetString(), strDatasetPath.GetString());

		return -1;//StopTestExtern();
	}

#if 1  //2021-10-14  lijunqing 测试模型组功能
	try
	{
        CString strXmlDatas;
		strXmlDatas = oDataset->GetXmlData();
        wchar_t *pstrXmlDatas = strXmlDatas.AllocSysString();

		if (pstrXmlDatas[1] == ':')
		{
			CString strFile;
			strFile = pstrXmlDatas;
			ats_ReadFrom(pShortDatas, strFile);
		}
		else
		{
			CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();
			//shaolei 20211017  
			if (pShortDatas->GetClassID() == DVMCLASSID_CDVMDATASET)
			{
				pShortDatas->SetXml(pstrXmlDatas,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
			}
			else if (pShortDatas->GetClassID() == DVMCLASSID_CDVMDATASETGROUP)
			{
				pShortDatas->SetXml(pstrXmlDatas,CDataMngrXmlRWKeys::CDvmDatasetGroupKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
			}

			CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
		}

        ::SysFreeString(pstrXmlDatas);
	}
	catch(...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("oDataset->GetXmlData : ERROR...."));
	}
#else
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("Test_DsGroup_R.xml");
	pShortDatas->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
#endif

	try 
	{
		oDataset->Release();
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("oDataset->Release : ERROR...."));
	}
	

	return 0;
}

long CTestControlBase::SaveEngineDatasToLocal(CCommCmd* pItem, CDvmDataset *pShortDatas)
{
	ASSERT (pShortDatas != NULL);
	CCmd *pCmd = pItem->GetCmd();

	if (pItem->IsCommCmdNeedWriteRptEx())
	{
		AddCommCmdReportDataEx(pItem, pShortDatas);
	}
	
	//判断数据是否需要保存到本地设备数据模型
	if (!pCmd->IsCmdNeedWriteToLocal())
	{
		return 0;
	}

	CDataSet *pDataset = GetDataset(pItem);   //pItem->GetDataset();

	if (pDataset == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ItemDataUnexist3.GetString() /*_T("项目【%s】设备数据模型【%s】不存在")*/
                                   , pItem->m_strName.GetString(), pCmd->m_strDatasetPath.GetString());
		//return StopTestExtern();
		return 0;
	}

	//获取g_strGbGlobalData_DvmNameIsStd的值
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CDataObj *pDataFind = (CDataObj*)pDevice->m_pSysParas->FindByID(g_strGbGlobalData_DvmNameIsStd);

	if (pDataFind == NULL)
	{
		pDataset->InitValueByDvmDataset(pShortDatas, FALSE, dvm_dataset_find_mode_name_id());
	}
	else
	{
		long nValue = CString_To_long(pDataFind->m_strValue);

		if (nValue > 0)
		{
			pDataset->InitValueByDvmDataset(pShortDatas, FALSE, dvm_dataset_find_mode_name_id());
		}
		else
		{
			pDataset->InitValueByDvmDataset(pShortDatas, FALSE, dvm_dataset_find_mode_name());
		}
	}
	
	return 0;
}

CDataObj* CTestControlBase::GBS_GetDsDataObj(CGbItemBase *pItem, long nDeviceIndex, const char* pszID)
{
	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return 0;
	}

	CString strID ;
	strID = pszID;

	CDataObj *pData = pDevice->FindDataObjByID(strID, nDeviceIndex);

	return pData;
}

double CTestControlBase::GBS_GetDsDataValueEx(CGbItemBase *pItem, long nDeviceIndex, const char* pszID)
{
	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return 0;
	}
	
	CString strID ;
	strID = pszID;
	
	CDataObj *pData = pDevice->FindDataObjByID(strID, nDeviceIndex);
	double dValue = 1;

	if (pData != NULL)
	{
		if (GBCLASSID_DATAOBJ_VALUE == pData->GetClassID())
		{
#ifdef _UNICODE
			dValue = _wtof(((CDataObjValue*)pData)->m_strValue);
#else
            dValue = atof(((CDataObjValue*)pData)->m_strValue.GetString());
#endif
		}
		else if (GBCLASSID_DATAOBJ == pData->GetClassID())
		{
#ifdef _UNICODE
			dValue = _wtof(pData->m_strValue);
#else
            dValue = atof(pData->m_strValue.GetString());
#endif
		}
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "dsData id(%s) not exist", pszID);
	}

	return dValue;
}

BOOL CTestControlBase::ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();

	if (pCmd->m_nRepeatTimes > 1)
	{//重复通讯的次数大于1
		//if (!pCmd->HasRepeatTestFinish(m_nCommCmdTestTimes))
		if (GBS_CanBreakLoop(pItem))//pItem->m_nBreakLoopState == 1)
		{//跳出循环
			pItem->m_nBreakLoopState = 0;  //已经跳出过循环，将标记置回0。为下一次测试做准备。
			CGbItemBase *pItemParent = (CGbItemBase*)pItem->GetParent();
			UINT nClassID = pItemParent->GetClassID();

			//父项目，MacroTest、Safety、SysParaEdit
			if ((nClassID == GBCLASSID_MACROTEST) || (nClassID == GBCLASSID_SAFETY) || (nClassID == GBCLASSID_SYSPARAEDIT))
			{
				pItemParent->m_nBreakLoopState = 0;
			}
		}
		else
		{
			if (m_nCommCmdTestTimes < GetMaxRepeatTimes(pCmd->m_nRepeatTimes))
			{//没有达到通讯次数，继续测试此项目
				m_nCommCmdTestTimes++;
				TestItemCommCmdEx((CCommCmd*)pItem);
				return TRUE;
			}
		}
	}

	m_nCommCmdTestTimes = 0;

	return FALSE;
}

//执行项目的测试：通讯命令完成后延时
void CTestControlBase::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	if (m_pCurrTestItem == NULL)
	{
		HideCommCmdAttrDlg();
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SytmTestFalse/*L"系统测试错误：ExcuteCommCmdOnDelayBeforeFinish"*/);
		return;
	}

	if (pItem == NULL)
	{
		if (m_pCurrSubTestItem != NULL)
		{
			pItem = (CCommCmd*)m_pCurrSubTestItem;
		}
		else 
		{
			if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
			{
				pItem = (CCommCmd*)m_pCurrTestItem;
			}
		}
	}

	if (pItem == NULL)
	{
		HideCommCmdAttrDlg();
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SytmTestFalse/*L"系统测试错误：ExcuteCommCmdOnDelayBeforeFinish"*/);
		return;
	}

	//处理测试项目的试验报告数据
	ProcessFinishCommCmd(pItem);

	//@@如果通讯真实完成，则往下执行，否则，执行当前通讯命令【主要处理一次性针对多装置同时通讯】
	if (pItem->GetCpusIndex() == DSID_ALL_DVM)
	{
		long nPpDeviceCount = m_oDeviceRefs.GetCount();

		if (nPpDeviceCount > 1)
		{//多设备
			if (m_nCommCmdCurrDeviceIndex+1 < nPpDeviceCount)
			{//还有设备没有通讯，则完成设备的通讯
				m_nCommCmdCurrDeviceIndex++;
				TestItemCommCmdEx((CCommCmd*)pItem);
				return;
			}
		}
	}

	m_nCommCmdCurrDeviceIndex = 0;

	//进行重复次数的判断
	//m_nCommCmdTestTimes
	CCmd *pCmd = pItem->GetCmd();

	if (pCmd != NULL)
	{
		//2017-11-19  如果是重复测试的项目，则执行重复测试处理
		if (ExcuteCommCmdOnDelayAfterFinish_Repeat(pItem))
		{
			return;
		}
// 		if (pCmd->m_nRepeatTimes > 1)
// 		{//重复通讯的次数大于1
// 			//if (!pCmd->HasRepeatTestFinish(m_nCommCmdTestTimes))
// 			if (pItem->m_nBreakLoopState == 1)
// 			{//跳出循环
// 
// 			}
// 			else
// 			{
// 				if (m_nCommCmdTestTimes < GetMaxRepeatTimes(pCmd->m_nRepeatTimes))
// 				{//没有达到通讯次数，继续测试此项目
// 					m_nCommCmdTestTimes++;
// 					TestItemCommCmdEx((CCommCmd*)pItem);
// 					return;
// 				}
// 			}
// 		}
	}


	if (m_pItemsRsltExprScript == NULL)
	{
		HideCommCmdAttrDlg();
	}

	BOOL bNeedFireMsg = TRUE;

	if (pCmd->m_nMaxRetrytimes == -1 && m_nCommCmdErrorState == 1)
	{
		bNeedFireMsg = FALSE;
	}

	if ( CanContinueTestByItemsRsltExprScript(pItem))
	{
		bNeedFireMsg = FALSE;
	}

	UpdateStateAfterFinishTestItem(pItem, bNeedFireMsg);

	//如果在结束通讯命令后的处理中，返回TRUE，表示可以继续处理通讯命令
	if (!ProcessAfterCommCmdFinish(pItem))
	{
		//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
		//因此单独执行
		WriteItemTempFile(pItem);

		return;
	}

	//2021-1-3  lijunqing 多装置模式下，如果更新了状态，释放了数据，导致后续的装置不能取到数据
	//因此单独执行
	WriteItemTempFile(pItem);

	if (pItem->m_bIsSubItem)
	{
		if (m_pCurrSubTestItem == NULL)
		{
			TestNextItem();
		}
		else
		{
			TestNextSubItem(pItem);
		}
	}
	else
	{
		TestNextItem();
	}
}

BOOL CTestControlBase::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	//如果没有测试完成
	if (m_pItemsRsltExprScript == NULL)
	{
		return TRUE;
	}

	//测试合格，返回
	if (pCommCmd->GetRsltJdg() == 1)
	{
		return TRUE;
	}

	if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
	{
		//添加多份报告数据，如果是读SOE项目，则不添加多次报告数据
		if (!pCommCmd->IsReadSoe())
		{
			CCmd *pCmd = pCommCmd->GetCmd();
			CReport *pReport = AddReport(pCommCmd, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17
		}

		pCommCmd->SetState(TEST_STATE_TESTING);
		Gb_UpdateGbItemParentTestState(pCommCmd);
		m_pTCtrlWnd->SetTimer(TIMER_DELAY_CMM_CMD_ITEMSEXPR, m_nItemsRsltExprScriptTimerLong, NULL);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//测试子项目，主要为：电气量项目的通讯命令、SysParaEdit
BOOL CTestControlBase::CanTestFirstSubItems()
{
	return TRUE;
}

BOOL CTestControlBase::IsVirtualVm()
{
	return g_strActiveTestMacroProgID == _T("VirtualVm.TestEngine");
	//return m_pGuideBook->m_pTestMacros->m_strProgID == _T("VirtualVm.TestEngine");
}

//电气量测试功能开始测试子项目
long CTestControlBase::TestFirstSubItems_MacroTest(BOOL bFromMtMsg)
{
	if (IsVirtualVm())
	{
		if (bFromMtMsg)
		{
			CExBaseList *pList = m_pCurrTestItem->GetSubGbItems();
			ASSERT (pList != NULL);

			if (pList->GetCount() > 0)
			{
				return TestFirstSubItems();
			}
			else
			{
				BOOL bCallMacroStopTestError = FALSE;
				FinishTestSubItem_MacroTest(bCallMacroStopTestError);
			}
		}
	}
	else
	{
		if (!bFromMtMsg)
		{
			return TestFirstSubItems();
		}
	}

	return 0;
}

long CTestControlBase::TestFirstSubItems()
{
	if (m_pCurrTestItem == NULL)
	{
		return 0;
	}

	UINT nClassID = m_pCurrTestItem->GetClassID();
	
	if ((nClassID == GBCLASSID_MACROTEST ) || (nClassID == GBCLASSID_SAFETY ))
	{
	}
	else
	{
		return 0;
	}

	//CMacroTest *pMacroTest = (CMacroTest*)m_pCurrTestItem;
	CExBaseList *pList = m_pCurrTestItem->GetSubGbItems();
	ASSERT (pList != NULL);

	if (pList->GetCount())
	{
		m_pCurrSubTestItem = (CCommCmd*)pList->GetHead();
		//TestItemCommCmdEx((CCommCmd*)m_pCurrSubTestItem);

		if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			CCommCmd *pCCommCmd = (CCommCmd*)m_pCurrSubTestItem;

			if (pCCommCmd->IsBeginModeSynchro())
			{
				TestItem((CCommCmd*)m_pCurrSubTestItem);
			}
		}
		else
		{
			TestItem((CSafety*)m_pCurrSubTestItem);
		}
		

		return 1;
	}
	else
	{
		return 0;
	}
}

CGbItemBase* CTestControlBase::GetNextTestSubItem()
{
	UINT nClassID = m_pCurrTestItem->GetClassID();
	ASSERT ((nClassID == GBCLASSID_MACROTEST ) || (nClassID == GBCLASSID_SAFETY ));

	if ((nClassID == GBCLASSID_MACROTEST ) || (nClassID == GBCLASSID_SAFETY ))
	{

	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestAbnrm2.GetString()/*L"测试发生异常，试验过程中通讯命令没有对应的项目"*/);
		return NULL;
	}

	CMacroTest *pMacroTest = (CMacroTest*)m_pCurrTestItem;
	CExBaseList *pList = pMacroTest->GetSubGbItems();
	ASSERT (pList != NULL);

	if (pList->GetCount())
	{
		POS pos = pList->Find(m_pCurrSubTestItem);
		ASSERT (pos != NULL);

		if (pos == NULL)
		{
			//m_pCurrSubTestItem = NULL;
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_TestAbnrm3.GetString()/*L"测试发生异常，试验过程中通讯命令没有对应的项目[TestNextSubItems]"*/);
			return NULL;
		}

		//下一个项目
		m_pCurrSubTestItem = (CGbItemBase*)pList->GetNext(pos);

		if (pos != NULL)
		{
			m_pCurrSubTestItem = (CGbItemBase*)pList->GetAt(pos);
		}
		else
		{
			m_pCurrSubTestItem = NULL;
		}

		return m_pCurrSubTestItem;
	}
	else
	{
		return NULL;
	}
}

const BSTR CTestControlBase::g_strDataInterfaceID_CPU = L"pnCpuIndex";
const BSTR CTestControlBase::g_strDataInterfaceID_Group = L"pnGroupIndex";
const BSTR CTestControlBase::g_strDataInterfaceID_Index = L"pnItemIndex";
const BSTR CTestControlBase::g_strDataInterfaceID_Value = L"pnValue";


long CTestControlBase::ContinueTestCommCmd(CCommCmd* pItem, BOOL &bFinish)
{
	bFinish = TRUE;
// 	CCmd *pCmd = pItem->GetCmd();
// 	CGbCommCmd *pGbCmdCfg = (CGbCommCmd*)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pItem->m_strType);  //命令的类型
// 	CCpu *pCpu = (CCpu*)pItem->GetCpu(pCmd->m_strDatasetPath);
// 
// 	if (pItem->m_strType == g_strwSoftswitchs)
// 	{
// 		ProcessFinishCommCmdWriteSoftSwitch(pItem);
// 	}
// 	else if (pItem->m_strCommCmdID == g_strrCtrlWords)
// 	{		
// 		//TestItemCmdReadSets(pItem);
// 	}
// 	else if (pItem->m_strType == g_strwCtrlWords)
// 	{
// 		//TestItemCmdReadSets(pItem);
// 	}
// 	else
// 	{
// 		bFinish = TRUE;
// 	}

	return 0;
}

long CTestControlBase::ProcessFinishCommCmd(CCommCmd* pItem)
{
    CReport *pReport = NULL;
	CCmd *pCmd = pItem->GetCmd();

	if (pItem->IsWrite())
	{//写命令
		ProcessFinishCommCmdWrite(pItem);
	}
	else if (pItem->IsRead())
	{
		ProcessFinishCommCmdRead(pItem);
	}
	else
	{
		ProcessFinishCommCmdNone(pItem);
	}

	if (m_nCommCmdErrorState == 1)
	{
		pItem->SetRsltJdg(0);
	}

	return 0;
}

long CTestControlBase::ProcessFinishCommCmdWrite(CCommCmd* pItem)
{
    

	CReport *pReport = NULL;
	CCmd *pCmd = pItem->GetCmd();

	pReport = pItem->GetReport(-1);//AddReport(pItem, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);////2017.05.17
	//pReport->AddReportValues(pItem->GetCmd());

	CValue *pValue = NULL;
	POS pos = pCmd->GetHeadPosition();
	CValues *pValues = pReport->m_pValues;
	CDataSet *pDataset = GetDataset(pItem);
	CDataObj *pData = NULL;

	if (pDataset != NULL)
	{
		while (pos != NULL)
		{
			pValue = (CValue *)pCmd->GetNext(pos);
			pData = pDataset->FindDataByID(pValue->m_strID);

			if (pData == NULL)
			{
				pData = pDataset->FindDataObjByID_Has(pValue->m_strID);
			}

			if (pData != NULL)
			{
				pValues->AddValue(pValue->m_strID, pData->m_strValue);
			}
			else
			{
				pValues->AddValue(pValue->m_strID, pValue->m_strValue);
			}
		}
	}
	else
	{
		pReport->AddReportValues(pItem->GetCmd());
	}

// 	pItem->AddCommCmdRptTags(pValues);
	ProcessFinishCommCmdAfter(pItem, pReport);

	return 0;
}

long CTestControlBase::ProcessFinishCommCmdRead(CCommCmd* pItem)
{
	//在此处进行判断，如果是读日志，则进行读日志的处理
	if (pItem->IsReadLog())
	{
		return ProcessFinishCommCmdReadLog(pItem);
	}

	CReport *pReport = NULL;
	CCmd *pCmd = pItem->GetCmd();

	CDvmDataset *pDvmDataset = CreateNewDvmDatasetForCommCmd(pItem);

	if (pItem->IsReadLogEx())
	{
		//如果是ReadLog*之类的命令，不读取数据集的数据
	}
	else
	{
		ReadEngineDatas(pItem, pDvmDataset);
	}

// 	CString strFile;
// 	strFile = _P_GetDBPath();
// 	SYSTEMTIME oTime;
// 	::GetLocalTime(&oTime);
// 	strFile.AppendFormat(_T("ReadEngineDatas_fordebug_%2d%2d%2d"), oTime.wHour, oTime.wMinute, oTime.wSecond);
// 	pDvmDataset->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);


	if (pItem->IsCmdRptDataset() )
	{
		ProcessFinishCommCmdReadSOE(pItem, pDvmDataset);
	}
	else
	{
		ProcessFinishCommCmdReadOther(pItem, pDvmDataset);
	}

	delete pDvmDataset;

	return 0;
}

long CTestControlBase::ProcessFinishCommCmdReadLog(CCommCmd* pItem)
{
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr(pItem);
	CCmd *pCmd = pItem->GetCmd();

	if (oPpDevice == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_ItemDataUnexist4.GetString() /*_T("项目【%s】通讯引擎设备数据模型不存在")*/, pItem->m_strName.GetString());
		return StopTestExtern();
	}

	CReport *pReport = GetReport_AddCommCmdReportData(pItem);
	CDvmLogs *pLogs = pReport->m_pLogs;

	try
	{
        CString strXmlDatas;
		strXmlDatas = oPpDevice->GetLogsXml();


        wchar_t *pstrXmlDatas = strXmlDatas.AllocSysString();

		if (pstrXmlDatas[1] == ':')
		{
			CString strFile;
			strFile = pstrXmlDatas;
			ats_ReadFrom(pLogs, strFile);
		}
		else
		{
            pLogs->SetXml(pstrXmlDatas,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
		}

        ::SysFreeString(pstrXmlDatas);
	}
	catch(...)
	{
	}

	ProcessFinishCommCmdAfter(pItem, pReport);

	return 0;
}


long CTestControlBase::ProcessFinishCommCmdReadSOE(CCommCmd* pItem,CDvmDataset *pDataset)
{
    

	if (pItem->IsSortSoe())
	{
		CDvmDatasetSort oDvmDatasetSort;
		oDvmDatasetSort.SortByAttrValue_t(pDataset);
	}

	CReport *pReport = NULL;
	CCmd *pCmd = pItem->GetCmd();
	long nCalMode = pCmd->GetCalMode();

	if (nCalMode == TEST_CALMODE_OVERWRITE)
	{
		if (pCmd->m_nRepeatTimes > 0)
		{
			if (m_nCommCmdTestTimes == 0)
			{
				pReport = AddCommCmdReportDataEx(pItem, pDataset);
			}
			else
			{
				pReport = AddCommCmdReportDataEx_OverWrite(pItem, pDataset);
			}
		}
		else
		{
			pReport = AddCommCmdReportDataEx(pItem, pDataset);
		}
	}
	else
	{
		pReport = AddCommCmdReportDataEx(pItem, pDataset);
	}

	ProcessFinishCommCmdAfter(pItem, pReport);

	return 0;
}

long CTestControlBase::ProcessFinishCommCmdReadOther(CCommCmd* pItem,CDvmDataset *pDataset)
{
	CReport *pReport = NULL;

	//保存数据到本地
	SaveEngineDatasToLocal(pItem, pDataset);

//#ifdef CMD_REPORT_ADD_TO_DATASET	
	//CommCmd添加标记，确认放到dataset还是values对象
	if (pItem->m_nFillRptDataset == 1)
	{
		//合并单元测试的功能。
		//shaolei 20221013 通讯命令的报告，直接添加到Dataset
		pReport = GetReport_AddCommCmdReportData(pItem);
		CCmd *pCmd = pItem->GetCmd();

		//pReport->AddRptDvmDataset(*pDatas);
		pReport->m_pRptDvmDataset->AppendEx(*pDataset);
		pDataset->RemoveAll();
		pReport->m_pRptDvmDataset->m_strName = pCmd->m_strDatasetPath; 
		pReport->m_pRptDvmDataset->m_strID = pCmd->m_strDatasetPath;
	}
//#else
	else
	{
		//添加数据到报告
		CDataSet *pDatasetCurr = GetDataset(pItem);   //pItem->GetDataset();

		if (pDatasetCurr != NULL)
		{
			pReport = AddCommCmdReportData(pItem, pDatasetCurr);
		}
		else
		{
			pReport = AddCommCmdReportData(pItem, pDataset);
		}
	}
//#endif	

	ProcessFinishCommCmdAfter(pItem, pReport);

	return 0;
}

long CTestControlBase::ProcessFinishCommCmdNone(CCommCmd* pItem)
{
    
	CReport *pReport = NULL;
	CCmd *pCmd = pItem->GetCmd();

	pReport = pItem->GetReport(-1);//AddReport(pItem, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17
	CValues * pValues = pReport->m_pValues;
// 	pItem->AddCommCmdRptTags(pValues);

	ProcessFinishCommCmdAfter(pItem, pReport);

	return 0;
}

long CTestControlBase::ProcessFinishCommCmdAfter(CCommCmd* pItem, CReport *pReport)
{
    
	FillCommCmdItemReport(pItem, pReport);

	pItem->InitStateByReport();

     //2020-11-22 lijunqing  避免上送两次测试结束消息
	//m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem, FALSE);

	return 0;
}

long CTestControlBase::ProcessFinishCommCmdMamual(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	

	//pItem->InitStateByReport();
	//m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem, FALSE);

	return 0;
}

void CTestControlBase::AddAnalogErrorDatas(CCommCmd* pItem, CValues * pValues)
{
	CCmd *pCmd = pItem->GetCmd();

	if (!pCmd->IsCmdDataset(DSID_dsAin))
	{
		return;
	}

	CDataSet *pDataset = GetDataset(pItem);   //pItem->GetDataset();

	if (pDataset == NULL)
	{
		return;
	}
	
	POS pos = pDataset->GetHeadPosition();
	CDataObj *pAnalog = NULL;
	CValue * pValue = NULL;

	while (pos != NULL)
	{
		pAnalog = (CDataObj*)pDataset->GetNext(pos);

		if (pAnalog->m_strDataType == g_strAnalogType_Error)
		{
			pValue = pValues->AddNew(pAnalog->m_strID, pAnalog->m_strName, _T("0"));
		}
	}
}

CReport* CTestControlBase::AddCommCmdReportData(CCommCmd* pItem, CDvmDataset *pDatas)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = GetReport_AddCommCmdReportData(pItem);
	CValues * pValues = pReport->m_pValues;
	long nIndex = 0;

// 	if (m_pCurrTestItem == pItem)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_DealCommunRst /*_T("----处理通讯命令【%s】结果")*/, pItem->m_strName);
// 	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DealCommunRst/*_T("--------处理通讯命令【%s】结果")*/, pItem->m_strName);
// 	}

	if (pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CreatRptFail/*L"创建报告对象失败"*/);
		return pReport;
	}

	//添加CommCmd定义的报告数据 
// 	pItem->AddCommCmdRptTags(pValues);

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("处理通讯命令【%s】结果个数【%d】"), pItem->m_strName, pValues->GetCount());

	//添加设备数据模型的数据
	BOOL bAdd = FALSE;

	if (m_pItemsRsltExprScript != NULL)
	{
		CDvmDataset oDataset;
		m_pItemsRsltExprScript->SelectAllDatas(oDataset, pDatas);
		CDvmData *pData = NULL;
		POS pos = oDataset.GetHeadPosition();
		bAdd = (pos != NULL);

		while (pos != NULL)
		{
			pData = (CDvmData*)oDataset.GetNext(pos);
			Gb_AddToRptValues(pData, pValues, TRUE);
		}

		oDataset.RemoveAll();
	}

	if (!bAdd)
	{
		//2021-10-14  lijunqing
		Gb_AddToRptValues(pDatas, pValues);
// 		POS pos = pDatas->GetHeadPosition();
// 		CDvmData *pData = NULL;
// 
// 		while (pos != NULL)
// 		{
// 			pData = (CDvmData*)pDatas->GetNext(pos);
// 			Gb_AddToRptValues(pData, pValues);
// 		}
	}
	
	//如果是遥测，处理误差量
	AddAnalogErrorDatas(pItem, pValues);

	return pReport;
}

CReport* CTestControlBase::GetReport_AddCommCmdReportData(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();

	CReport *pReport = pItem->GetReport(-1);;//AddReport(pItem, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17

	//重复次数与当前测试次数的判断
	if (pReport->IsCalReport() || pReport->IsCalReportEx())
	{
		CReports *pReports = pItem->GetReports();
		long nCount = pReports->GetCount();
		ASSERT (nCount >= 3);
		pReport = (CReport*)pReports->GetAtIndex(nCount - 2);
	}

	return pReport;
}

CReport* CTestControlBase::AddCommCmdReportData(CCommCmd* pItem, CDataSet *pDatas)
{
//#ifdef CMD_REPORT_ADD_TO_DATASET	
	if (pItem->m_nFillRptDataset == 1)
	{
		//shaolei 20221012  新平台的合并单元自动测试功能需要，需要将通讯命令的报告部分，全部放到Dataset中，故修改此处。
		CCmd *pCmd = pItem->GetCmd();
		CReport *pReport = GetReport_AddCommCmdReportData(pItem);
		CValues * pValues = pReport->m_pValues;
		CDvmDataset *pRptDataset = pReport->m_pRptDvmDataset;
		long nIndex = 0;

		if (g_nLog_TestControl_Msg == 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DealCommunRst.GetString() //_T("处理通讯命令【%s】结果")
				, pItem->GetNamePathEx(GBCLASSID_TESTCONTROL, TRUE).GetString());// m_strName);
		}

		if (pRptDataset == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_CreatRptFail);  //L"创建报告对象失败"
			return pReport;
		}

		//添加设备数据模型的数据
		BOOL bAdd = FALSE;

		if (m_pItemsRsltExprScript != NULL)
		{
			CDataSet oDataset;
			m_pItemsRsltExprScript->SelectAllDatas(oDataset, pDatas);
			POS pos = oDataset.GetHeadPosition();
			CDataObj *pData = NULL;
			bAdd = (pos != NULL);

			while (pos != NULL)
			{
				pData = (CDataObj*)oDataset.GetNext(pos);
				Gb_AddToRptDataset(pData, pRptDataset, TRUE);
			}

			oDataset.RemoveAll();
		}

		if (!bAdd)
		{
			Gb_AddToRptDataset(pDatas, pRptDataset);
		}

		//如果是遥测，处理误差量,  遥测误差量的处理不变
		AddAnalogErrorDatas(pItem, pValues);

		return pReport;
	}
	
// #else
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = GetReport_AddCommCmdReportData(pItem);
	CValues * pValues = pReport->m_pValues;
	long nIndex = 0;

	if (g_nLog_TestControl_Msg == 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DealCommunRst.GetString() //_T("处理通讯命令【%s】结果")
                                   , pItem->GetNamePathEx(GBCLASSID_TESTCONTROL, TRUE).GetString());// m_strName);
	}

	if (pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_CreatRptFail);  //L"创建报告对象失败"
		return pReport;
	}

	//添加CommCmd定义的报告数据 
// 	pItem->AddCommCmdRptTags(pValues);

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("处理通讯命令【%s】结果个数【%d】"), pItem->m_strName, pValues->GetCount());

	//添加设备数据模型的数据
	BOOL bAdd = FALSE;

	if (m_pItemsRsltExprScript != NULL)
	{
		CDataSet oDataset;
		m_pItemsRsltExprScript->SelectAllDatas(oDataset, pDatas);
		POS pos = oDataset.GetHeadPosition();
		CDataObj *pData = NULL;
		bAdd = (pos != NULL);

		while (pos != NULL)
		{
			pData = (CDataObj*)oDataset.GetNext(pos);
			Gb_AddToRptValues(pData, pValues, TRUE);
		}

		oDataset.RemoveAll();
	}

	if (!bAdd)
	{
		Gb_AddToRptValues(pDatas, pValues);
	}
	
	//如果是遥测，处理误差量
	AddAnalogErrorDatas(pItem, pValues);

// #endif

	return pReport;
}

CReport* CTestControlBase::AddCommCmdReportDataEx(CCommCmd* pItem, CDvmDataset *pDatas)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = GetReport_AddCommCmdReportData(pItem);
	CValues *pValues = pReport->m_pValues;
	long nIndex = 0;

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DealCommunRst/*_T("处理通讯命令【%s】结果")*/, pItem->m_strName);

	if (pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CreatRptFail/*L"创建报告对象失败"*/);
		return pReport;
	}

	//添加CommCmd定义的报告数据 
// 	pItem->AddCommCmdRptTags(pValues);

	pReport->AddRptDvmDataset(*pDatas);
	pReport->m_pRptDvmDataset->m_strName = pCmd->m_strDatasetPath; //2019-1-4:报告可以填写数据集
	pReport->m_pRptDvmDataset->m_strID = pCmd->m_strDatasetPath;

	return pReport;
}

CReport* CTestControlBase::AddCommCmdReportDataEx_OverWrite(CCommCmd* pItem, CDvmDataset *pDatas)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = pItem->GetReport(-1);

	if (pReport == NULL)
	{
		ASSERT (FALSE);//2017.05.17
		pReport = AddReport(pItem, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17
	}

	CValues *pValues = pReport->m_pValues;
	long nIndex = 0;

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DealCommunRst/*_T("处理通讯命令【%s】结果")*/, pItem->m_strName);

	if (pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CreatRptFail/*L"创建报告对象失败"*/);
		return pReport;
	}

	//添加CommCmd定义的报告数据 
// 	pItem->AddCommCmdRptTags(pValues);

	pReport->AddRptDvmDataset(*pDatas);

	return pReport;
}

LRESULT CTestControlBase::OnElectricTestAppMsg(WPARAM wPara,LPARAM lPara)
{
	if (m_pTCtrlWnd->m_bTIMER_TEST_FOR_APPEXCEPTION)
	{
		return 0;
	}

	m_pTCtrlWnd->m_bTIMER_TEST_FOR_APPEXCEPTION = TRUE;
	m_pTCtrlWnd->m_pTestItemRef = m_pCurrTestItem;
	StopTest();
    
    CTCtrlCntrConfig *pConfig = g_theSmartTestBaseApp->GetCntrConfig();
	long nTimeLong = pConfig->m_nMacroTestAppExceptionTDelay;
	if (nTimeLong < 1)
	{
		nTimeLong = 1;
	}

	if(nTimeLong > 30)
	{
		nTimeLong = 30;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE,       _T(""));
	CLogPrint::LogString(XLOGLEVEL_TRACE,       _T("***********************************************************"));
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_WaitRtest.GetString() /*_T("***********标准源告警，等待%d分钟后重新开始测试************")*/, nTimeLong);
	nTimeLong *= 60;

	m_pTCtrlWnd->SetTimer(TIMER_TEST_FOR_APPEXCEPTION, nTimeLong, NULL);

	return 0;
}

#define _use_xmatch

long CTestControlBase::GetCommCmdItemMaxRepeatTimes(CCommCmd* pItem)
{
	if (pItem->GetParent()->GetClassID() == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest*)pItem->GetParent();

		if (pMacroTest->m_nRepeatTimes > 1)
		{
			return pMacroTest->m_nRepeatTimes;
		}
	}

	CCmd *pCmd = pItem->GetCmd();

	return pCmd->m_nRepeatTimes;
}

long CTestControlBase::GetCommCmdItemReportFillIndex(CCommCmd* pItem)
{
	long nCommCmdTestTimes = m_nCommCmdTestTimes;

	if (m_pCurrSubTestItem == NULL)
	{
		return nCommCmdTestTimes;
	}

	CCmd *pCmd = pItem->GetCmd();

	if (pCmd->m_nRepeatTimes > 0)
	{
		return nCommCmdTestTimes;
	}

	if (pItem->GetParent()->GetClassID() != GBCLASSID_MACROTEST)
	{
		return m_nCommCmdTestTimes;
	}

	CMacroTest *pMacroTest = (CMacroTest*)pItem->GetParent();

	if (pMacroTest->m_nRepeatTimes > 1)
	{
		return m_nMacroTestTimes;
	}
	else
	{
		return m_nCommCmdTestTimes;
	}
}

//如果是标准差计算方式，则只在最后的报告才能执行结果判断脚本
BOOL CTestControlBase::CanRunCommCmdFinalResultScript(CCommCmd* pItem)
{
	return m_bCanRunCommCmdFinalResultScript;

	if (m_pCurrSubTestItem == NULL)
	{
		return TRUE;
	}
	else
	{
		CCmd *pCmd = pItem->GetCmd();

		//通讯命令本身就是标准差的计算方式
		if (pCmd->GetCalMode() == TEST_CALMODE_STDERROR)
		{
			if ((m_pCurrSubTestItem == pItem) && (pItem->GetParent()->GetClassID() == GBCLASSID_MACROTEST) )
			{
				CMacroTest *pMacroTest = (CMacroTest *)pItem->GetParent();

				if (pMacroTest->m_nRepeatTimes > 1)
				{//通讯命令通过
					long nCommCmdTestTimes = GetCommCmdItemReportFillIndex(pItem);//m_nCommCmdTestTimes;

					if (nCommCmdTestTimes >= GetMaxRepeatTimes(pMacroTest->m_nRepeatTimes))
					{//达到通讯次数，添加新的报告数据对象
						return TRUE;
					}
				}
			}

			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

	long nCurrClassID = m_pCurrTestItem->GetClassID();

	if (nCurrClassID == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest*)m_pCurrTestItem;

		if (pMacroTest->m_nRepeatTimes <= 1)
		{
			return FALSE;
		}
		else
		{
			if (pMacroTest->GetCalMode() == TEST_CALMODE_STDERROR)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}
	else if (nCurrClassID == GBCLASSID_COMMCMD)
	{
		CCmd *pCmd = pItem->GetCmd();

		if (pCmd->GetCalMode() == TEST_CALMODE_STDERROR)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CTestControlBase::ContinueTestByItemsRsltExprScript(CCommCmd* pItem)
{
	if (m_pItemsRsltExprScript != NULL)
	{
		if (pItem->GetRsltJdg() == 0)
		{
			m_nItemsRsltExprScriptIndex++;

			if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CTestControlBase::CanContinueTestByItemsRsltExprScript(CCommCmd* pItem)
{
	if (m_pItemsRsltExprScript != NULL)
	{
		if (pItem->GetRsltJdg() == 0)
		{
			if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void CTestControlBase::ClearSysRptFill(CGbItemBase *pItem)
{
	//pItem->m_dwReserved = 0;
}

void CTestControlBase::EditItemPara(CMacroTest *pMacroTest, CShortData  *pData)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);
}

void CTestControlBase::EditItemPara(CCommCmd *pCommCmd, CValue *pValue)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);
}

void CTestControlBase::EditMacroTestPara(CMacroTest *pMacroTest, CShortData  *pData)
{
	pMacroTest->UpdateMacroTestParaData(pData, FALSE, TRUE);
}

void CTestControlBase::EditCommCmdPara(CCommCmd *pCommCmd, CValue *pValue)
{
	CCmd *pCmd = pCommCmd->GetCmd();
	CValue *pFind = (CValue*)pCmd->FindByID(pValue->m_strID);

	if (pFind == pValue)
	{
		return;
	}

	if (pFind != NULL)
	{
		pFind->m_strValue = pValue->m_strValue;
	}
}

long CTestControlBase::SelectAllTestControl(CExBaseList &listTestControl, BOOL bMainFirst)
{
	listTestControl.AddTail(this);

	return listTestControl.GetCount();
}

CReport* CTestControlBase::AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex)
{
	return pItem->AddReport(nRepeatTimes, nTestIndex);
}

void CTestControlBase::DeleteReport(CGbItemBase *pItem, CReport *pReport)
{
	pItem->DeleteReport(pReport);
}

BOOL CTestControlBase::ItemsRsltExprScriptTimeIgnore()
{
	if (m_nItemsRsltExprScriptTimeIgnore <= 0)
	{
		return FALSE;
	}

	return m_oItemsRsltExprScriptTimeTick.GetTickCountLong(FALSE) < m_nItemsRsltExprScriptTimeIgnore;
}

CReport* CTestControlBase::GetReport(CGbItemBase* pItem, long nIndex)
{
	if (m_pCurrReport == NULL)
	{
		return pItem->GetReport(nIndex);
	}
	else
	{
		CGbItemBase* pSelItem = (CGbItemBase*)m_pCurrReport->GetParent()->GetParent();

		if (pSelItem == pItem)
		{
			return m_pCurrReport;
		}
		else
		{
			return pItem->GetReport(nIndex);
		}
	}
}


//填写通讯命令项目的报告数据
void CTestControlBase::FillCommCmdItemReport(CCommCmd* pItem, CReport *pReport)
{
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	CCmd *pCmd = pItem->GetCmd();
	long nRsltJdg = 0;
	CString strSyntax;

	pTestControl->m_bCanRunCommCmdFinalResultScript = FALSE;
	pItem->AddCommCmdRptTags(pReport->GetValues());

	if (m_pReportFill != NULL)
	{
		m_pReportFill->SetCommCmdCpusIndex(GetCommCmdCurrDeviceIndex(pItem));
	}

	if (pCmd->m_nRepeatTimes > 1)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("项目【%s】报告填写第%d次，共%d次"), pItem->m_strName, m_nCommCmdTestTimes+1, GetMaxRepeatTimes(pCmd->m_nRepeatTimes)+1);
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("项目【%s】报告填写"), pItem->m_strName);
	}

	//执行结果判断脚本
	BOOL bNeedRun = TRUE;

	if (m_pItemsRsltExprScript != NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)pItem->GetParent();
		CReport *pRptMacroTest = pMacroTest->GetReport(-1);
		CDevice *pDevice = (CDevice*)pMacroTest->GetAncestor(GBCLASSID_DEVICE);

		if (pItem->IsReadSoe())
		{//读SOE命令，只执行报文验证
			if (ItemsRsltExprScriptTimeIgnore())
			{
				CReport *pReport = pItem->GetReport(-1);

				if (pReport->m_pRptDvmDataset->GetCount() > 0)
				{
					CString strText;
					strText = pItem->GetNamePathEx(GBCLASSID_TESTCONTROL);
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s: Ingnore SOE %d"), strText.GetString(), pReport->m_pRptDvmDataset->GetCount());
					pReport->m_pRptDvmDataset->DeleteAll();
				}
			}
			else
			{
				nRsltJdg = pItem->RunDsvScript();
			}
		}
		else
		{
			//其他项目，先执行表达式判断
			nRsltJdg = m_pItemsRsltExprScript->RunRsltExprScript(pDevice, pReport->m_pValues, pRptMacroTest->m_pValues);

			//再执行结果判断脚本，这样就能够兼容之前的模板
			if (nRsltJdg != 0)
			{
				m_pCurrReport = pReport;
				pItem->RunResultScript(strSyntax);
				m_pCurrReport = NULL;
				nRsltJdg = pItem->m_nRsltJdg;
			}

			bNeedRun = FALSE;
		}

		pItem->SetRsltJdg(nRsltJdg);
	}

	if (bNeedRun)
	{
		m_pCurrReport = pReport;
		pItem->RunResultScript(strSyntax);
		m_pCurrReport = NULL;
	}

	if (m_pItemsRsltExprScript != NULL)
	{
		ASSERT(m_pReportFill != NULL);
		if (m_pReportFill != NULL)
		{
			m_pReportFill->UpdateReport(pReport);
		}
	}

	if (ContinueTestByItemsRsltExprScript(pItem))
	{
		return;
	}

	//获取通讯命令的重复测试次数，考虑通讯命令作为电气量项目的子项目进行测试
	long nCommCmdTestTimes = GetCommCmdItemReportFillIndex(pItem);//m_nCommCmdTestTimes;
	long nCalMode = pCmd->GetCalMode();

	if (nCalMode == TEST_CALMODE_OVERWRITE)
	{
		FillReport(pReport, 0);
	}
	else
	{
		FillReport(pReport, nCommCmdTestTimes);
	}

	if (pCmd != NULL)
	{
		if (pCmd->m_nRepeatTimes > 1)
		{//重复通讯的次数大于1
			//if (pCmd->HasRepeatTestFinish(m_nCommCmdTestTimes))
			if (m_nCommCmdTestTimes >= GetMaxRepeatTimes(pCmd->m_nRepeatTimes))
			{//达到通讯次数，添加新的报告数据对象
				pTestControl->m_bCanRunCommCmdFinalResultScript = TRUE;
				pReport = CreateCmmFinalReport(pItem, pCmd->m_nRepeatTimes);
				nCommCmdTestTimes = pCmd->m_nRepeatTimes;
				FillReport(pReport, nCommCmdTestTimes);
			}
			else
			{//没有达到通讯次数，返回
// #ifdef TCTRLCNTR_USE_WORD
// 				//nCommCmdTestTimes = pCmd->m_nRepeatTimes;
// 				//FillReport(pReport, nCommCmdTestTimes);
// #endif			
			}

			return;
		}
		else
		{
			if ((m_pCurrSubTestItem == pItem) && (pItem->GetParent()->GetClassID() == GBCLASSID_MACROTEST) )
			{
				CMacroTest *pMacroTest = (CMacroTest *)pItem->GetParent();

				if (pMacroTest->m_nRepeatTimes > 1)
				{//通讯命令通过
					if (nCommCmdTestTimes >= GetMaxRepeatTimes(pMacroTest->m_nRepeatTimes))
					{//达到通讯次数，添加新的报告数据对象
						pTestControl->m_bCanRunCommCmdFinalResultScript = TRUE;
						pReport = CreateCmmFinalReport(pItem, pMacroTest->m_nRepeatTimes);
						nCommCmdTestTimes = pMacroTest->m_nRepeatTimes;
						FillReport(pReport, nCommCmdTestTimes);
					}
				}
				
			}
		}
	}


	if (m_pCurrSubTestItem == pItem)
	{//当前项目是项目
		//根据执行判断脚本的返回值设置项目状态
		pItem->InitStateByReport();
	}
}

long CTestControlBase::GbDeleteAllNodeData(const CString &strID)
{
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_CommunUnExist /*L"通讯设备不存在"*/);
		return StopTestExtern();
	}

	CProtocolDatasetInterface* oDataset = NULL;

	try
	{
		oDataset = oPpDevice->FindDataSet(strID);

		if(oDataset != NULL)
		{
			oDataset->DeleteAllDatas();
		}
	}
	catch(...){}

	oDataset->Release();

	return 0;
}

void CTestControlBase::SetBinaryFile(const CString &strFile)
{
	m_strGbBinaryFile = strFile;	
	m_strName = GetFileTitleFromFilePath(strFile);
	m_strID = m_strName;
}


void CTestControlBase::InitEngineDataInterface(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr(pItem);

	if (oPpDevice == NULL)
	{
		return;
	}

	CProtocolParasInterface* oDataInterface = oPpDevice->GetDataInterface();

	if (oDataInterface == NULL)
	{
		return;
	}
	oDataInterface->Reset();

	//写入定值区号参数
	if (pCmd->m_nZoneIndex > 0)
	{
		CString strZoneIndex;
		strZoneIndex.Format(_T("%d"), pCmd->m_nZoneIndex);
		oDataInterface->AddData(_T("Set_Zone_Index"), strZoneIndex);
	}

	if (pCmd->GetCount() == 0)
	{
		oDataInterface->Release();
		return;
	}

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pItem->m_strCommCmdID);

	if (pGbCmd == NULL)
	{
		oDataInterface->Release();
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_CmdFalse.GetString() /*_T("通讯配置文件【%s】不正确，命令【%s】错误")*/
                                   , pGuideBook->m_strCommCmdConfigFile.GetString(), pItem->m_strCommCmdID.GetString());
		return ;
	}

	//通讯命令没有参数
	if (pGbCmd->GetCount() == 0)
	{
		oDataInterface->Release();
		return;
	}

	oDataInterface->Reset();

	POS pos = pCmd->GetHeadPosition();
	CValue *pPara = NULL;
	CGbCommCmdPara *pFind = NULL;
	CString strValue;

	while (pos != NULL)
	{
		pPara = (CValue *)pCmd->GetNext(pos);
		pFind = (CGbCommCmdPara *)pGbCmd->FindByID(pPara->m_strID);

		if (pFind != NULL)
		{
			strValue = pItem->CalValue(pPara);
			oDataInterface->AddData(pPara->m_strID, strValue);
		}
		else
		{
			oDataInterface->AddData(pPara->m_strID, pPara->m_strValue);
		}
	}

	oDataInterface->Release();
}

BOOL CTestControlBase::Out_RunProcedure(const CString &bstrProcedureID, const CString &bstrDatasetPath
					  , WPARAM wParam, LPARAM lParam, UINT nProcedureType)
{
    return RunProcedure(bstrProcedureID, bstrDatasetPath, wParam, lParam, nProcedureType, m_pTCtrlWnd->GetSafeHwnd());
}

//执行过程
BOOL CTestControlBase::RunProcedure(const CString &bstrProcedureID, const CString & bstrDatasetPath
								, WPARAM wParam, LPARAM lParam, UINT nProcedureType, HWND hMsgRcvWnd)
{
	if (g_nLog_TestControl_Msg == 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RunProcedure：%s, %s"), bstrProcedureID.GetString(), bstrDatasetPath.GetString());
	}

	m_nRunProcedureType = nProcedureType;

	//@@获取当前通讯的设备，进行通讯
	CProtocolDeviceInterface* oPpDevice = NULL;
	
	if (m_nRunProcedureType == ProcedureType_EngineCmd)
	{
		CPpDeviceRef *pPpDeviceRef = NULL;
		pPpDeviceRef =  (CPpDeviceRef*)m_oDeviceRefs.GetHead();
		
		if (pPpDeviceRef != NULL)
		{
			oPpDevice = pPpDeviceRef->m_oPpDevice;
		}
	}
	else
	{
		oPpDevice = GetDevicePtr();
	}

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_CommunEngineFalse /*L"    执行通讯过程：通讯引擎错误"*/);
		return FALSE;
	}

	//设置录波路径
#ifdef UNICODE
	if (_wcsicmp(bstrProcedureID, CCommCmd::g_strCmdID_StartRecord) == 0)
#else
    if (stricmp(bstrProcedureID.GetString(), CCommCmd::g_strCmdID_StartRecord.GetString()) == 0)
#endif
	{
		SetPpEngineRecordFilePath(oPpDevice);
	}

	try
	{
		//oPpDevice->RegisterProcedureWndMsg(bstrProcedureID, (ULONG)m_pTCtrlWnd->m_hWnd, WM_COMM_COMMAND);
		oPpDevice->RegisterProcedureWndMsg(bstrProcedureID, (ULONG)hMsgRcvWnd, WM_COMM_COMMAND);
		m_strProcedureID = bstrProcedureID;
		m_strDatasetPath = bstrDatasetPath;
		oPpDevice->RunProcedure(bstrProcedureID, bstrDatasetPath);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_CommunEngineFalse /*L"    执行通讯过程:通讯引擎错误"*/);
	}

	return TRUE;
}


long CTestControlBase::GBS_RcdSetPath(CGbItemBase *pItem, long nAppendItemPath, const CString &strRcdFilePathRoot, long nAppendTestTimeDir)
{
	CString strRcdFilePath;
	strRcdFilePath = GBS_RcdGetPath(pItem, nAppendItemPath, strRcdFilePathRoot, nAppendTestTimeDir);

	::CreateAllDirectories(strRcdFilePath);
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();
	oPpDevice->SetAttrByID(g_strPpEngineRecordFilePathKey, strRcdFilePath);

	CReport *pReport = pItem->GetReport(-1);
	CString strTemp;
	strTemp = _P_GetWorkspacePath();
	strTemp = strRcdFilePath.Mid(strTemp.GetLength());
	pReport->AddValue(g_strPpEngineRecordFilePathKey, strTemp);

	return 0;
}

CString CTestControlBase::GBS_RcdGetPath(CGbItemBase *pItem, long nAppendItemPath, const CString &strRcdFilePathRoot, long nAppendTestTimeDir)
{
	CString strRcdFilePath;
	long nPos = m_strGbBinaryFile.ReverseFind('.');
	strRcdFilePath = m_strGbBinaryFile.Left(nPos);
    strRcdFilePath += _T(_P_FOLDER_PATH_SEPARATOR_);

	if (nAppendItemPath == 1)
	{
        strRcdFilePath.AppendFormat(_T("%s\\"), pItem->m_strName.GetString());
	}
	else if (nAppendItemPath == 2)
	{
		strRcdFilePath.AppendFormat(_T("%d\\"), pItem->m_nIndex);
	}
	else if (nAppendItemPath == 3)
	{
        strRcdFilePath.AppendFormat(_T("%d_%s\\"), pItem->m_nIndex, pItem->m_strName.GetString());
	}

	if (strRcdFilePathRoot.GetLength() > 0)
	{
        strRcdFilePath.AppendFormat(_T("%s\\"), strRcdFilePathRoot.GetString());
	}

	if (nAppendTestTimeDir)
	{
		if (pItem->GetClassID() == GBCLASSID_COMMCMD
			|| pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			strRcdFilePath.AppendFormat(_T("%d\\"), pItem->GetReports()->GetCount());
		}
	}

	return strRcdFilePath;
}

BOOL CTestControlBase::Parse_Item_File_Path(CGbItemBase *pCurrItem, const CString &strEpxr, CString &strRet)
{
	CGbItemBase *pSelItem = NULL;

	if (pCurrItem == NULL)
	{
		return FALSE;
	}
	
	if (!pCurrItem->Parse_Item_File_Path(strEpxr, &pSelItem))
	{
		return FALSE;
	}

	strRet = GBS_RcdGetPath(pSelItem, 2, _T(""), 0);

	return TRUE;
}

BOOL CTestControlBase::Parse_Report_File_Path(CGbItemBase *pCurrItem, CString &strPath)
{
	BOOL bRet = FALSE;

	if (strPath.Find(CGbItemBase::g_strItemPathKey_gbrpt) >= 0)
	{
		bRet = TRUE;
		strPath.Replace(CGbItemBase::g_strItemPathKey_gbrpt, m_strGbBinaryFileName);
	}

	if (strPath.Find(CGbItemBase::g_strItemPathKey_ItemIndex) >= 0)
	{
		bRet = TRUE;
		CString strIndex;
		strIndex.Format(_T("%d"), pCurrItem->m_nIndex);
		strPath.Replace(CGbItemBase::g_strItemPathKey_ItemIndex, strIndex);
	}

	if (strPath.Find(CGbItemBase::g_strItemPathKey_ItemID) >= 0)
	{
		bRet = TRUE;
		strPath.Replace(CGbItemBase::g_strItemPathKey_ItemID, pCurrItem->m_strID);
	}

	if (strPath.Find(CGbItemBase::g_strItemPathKey_ItemName) >= 0)
	{
		bRet = TRUE;
		strPath.Replace(CGbItemBase::g_strItemPathKey_ItemName, pCurrItem->m_strName);
	}

	return bRet;
}

BOOL CTestControlBase::Parse_Report_File_Path(CGbItemBase *pCurrItem, const CString &strEpxr, CString &strRet)
{
#ifndef _PSX_QT_LINUX_
    CString strPath, strRight;
	
	if (!Gb_Parse_Item_File_Path(strEpxr, CGbItemBase::g_strReportFilePathKey, strPath, strRight))
	{
		return FALSE;
	}

	strRet = GetPathFromFilePathName(m_strGbBinaryFile);

	CString strAppend = strPath;

	if (Parse_Report_File_Path(pCurrItem, strAppend))
	{
		if (strRet.Right(1) == '\\')
		{
			strRet.AppendFormat(_T("%s"), strAppend);
		}
		else
		{
			strRet.AppendFormat(_T("\\%s"), strAppend);
		}
	}

	ValidatePath(strRet);

	if (strRight.GetLength() > 0)
	{
		CHAR ch = strRight.GetAt(0);

		if (ch == '\\' || ch == '/')
		{
			strRight = strRight.Mid(1);
		}

		strRet += strRight;
	}

	ValidatePath(strRet);
#endif

	return TRUE;
}
void CTestControlBase::SetPpEngineRecordFilePath(CProtocolDeviceInterface *oPpDevice)
{
    //lijunqing 2020-11-07
    if (oPpDevice == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("Protocol pDevice==NULL"));
        return;
    }

	CString strRcdFilePath;
	strRcdFilePath = GBS_RcdGetRcdDestPath(TRUE);//GetPathFromFilePathName(m_strGbBinaryFile);
	oPpDevice->SetAttrByID(g_strPpEngineRecordFilePathKey, strRcdFilePath);
}

BOOL CTestControlBase::UnRegisterProcedureMsg(WPARAM wParam, LPARAM lParam, HWND hMsgRcvWnd)
{
	//CProtocolDeviceInterface* oPpDevice = GetDevicePtr();
	//CProtocolDeviceInterface* oPpDevice = m_oDeviceRefs.FindByID(wParam);
	CProtocolDeviceInterface* oPpDevice = FindPpDevice(wParam);

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CommunEngineFalse/*L"执行通讯过程:通讯引擎错误"*/);
		return FALSE;
	}

	//oPpDevice->UnRegisterProcedureWndMsg(_bstr_t(m_strProcedureID), (ULONG)m_pTCtrlWnd->m_hWnd, WM_COMM_COMMAND);
	oPpDevice->UnRegisterProcedureWndMsg(m_strProcedureID, (ULONG)hMsgRcvWnd, WM_COMM_COMMAND);

	return TRUE;
}

//最终报告的标识与其他报告的区别：报告表示以"CAL_"开头
//获取最后一个报告数据到前一个"CAL_"的数据之后的数据
//之后按照定义的计算方式进行数据的处理
CReport* CTestControlBase::CreateCmmFinalReport(CCommCmd* pItem, long nRepeatTimes)
{
	CCmd *pCmd = pItem->GetCmd();
	long nCalMode = pCmd->GetCalMode();
	CReport *pReportFinal = NULL;

	if (nCalMode == TEST_CALMODE_NONE)
	{
		pReportFinal = pItem->GetCurrReport();
		return pReportFinal;
	}

	//计算报告数据
	pReportFinal = AddReport(pItem, nRepeatTimes, nRepeatTimes);//2017.05.17
	pReportFinal->SetCalReport();
	CExBaseList oReports;

	//获取需要计算的报告数据对象
	GetCmmReportsForCal(pItem, oReports);

	if (oReports.GetCount() < 2)
	{
		oReports.RemoveAll();
		return pReportFinal;
	}

	pReportFinal->m_pValues->DeleteAll();

	switch (nCalMode)
	{
	case TEST_CALMODE_AVERAGE:
		CmmCalReports_Average(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MAX:
		CmmCalReports_Max(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MIN:
		CmmCalReports_Min(pReportFinal, oReports);
		break;

	case TEST_CALMODE_ERRORMAX:
		CmmCalReports_ErrorMax(pReportFinal, oReports);
		break;

	case TEST_CALMODE_STDERROR:
		CmmCalReports_StdError(pReportFinal, oReports);
		break;

	case TEST_CALMODE_OVERWRITE:
		CmmCalReports_OverWrite(pReportFinal, oReports);
		break;

	default:
		break;
	}

	oReports.RemoveAll();

	//
	if (nCalMode == TEST_CALMODE_STDERROR)
	{
		m_pCurrReport = pReportFinal;
		pItem->RunResultScript();
		m_pCurrReport = NULL;
	}
	else
	{
		InitFinalReportState(pItem, nRepeatTimes);
	}

	return pReportFinal;
}

CReport* CTestControlBase::CreateMtFinalReport(CMacroTest* pItem)
{
	long nCalMode = pItem->GetCalMode();
	CReport *pReportFinal = NULL;

	if (nCalMode == TEST_CALMODE_NONE)
	{
		pReportFinal = pItem->GetCurrReport();
		return pReportFinal;
	}

	CExBaseList oReports;

	//获取需要计算的报告数据对象
	GetMtReportsForCal(pItem, oReports);

	if (oReports.GetCount() < 2)
	{
		oReports.RemoveAll();
		return pReportFinal;
	}

	CGbItemBase *pNewForRptDB = NULL;

    if (m_pGuideBook->IsSaveRptToDB() || g_theSmartTestBaseApp->IsSaveRptToDB())
	{
		oReports.RemoveAll();
		pNewForRptDB = ats_CloneGbItemFromDB(pItem);
		GetMtReportsForCal((CMacroTest*)pNewForRptDB, oReports);
	}

	//计算报告数据
	pReportFinal = AddReport(pItem, pItem->m_nRepeatTimes, pItem->m_nRepeatTimes);//2017.05.17
	pReportFinal->SetCalReport();
	pReportFinal->m_pValues->DeleteAll();

	switch (nCalMode)
	{
	case TEST_CALMODE_AVERAGE:
		CmmCalReports_Average(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MAX:
		CmmCalReports_Max(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MIN:
		CmmCalReports_Min(pReportFinal, oReports);
		break;

	case TEST_CALMODE_ERRORMAX:
		CmmCalReports_ErrorMax(pReportFinal, oReports);
		break;

	case TEST_CALMODE_STDERROR:
		CmmCalReports_StdError(pReportFinal, oReports);
		break;

	default:
		break;
	}

	oReports.RemoveAll();

	if (nCalMode == TEST_CALMODE_STDERROR)
	{
		//pItem->RunResultScript();
	}
	else
	{
		InitFinalReportState(pItem, GetMaxRepeatTimes(pItem->m_nRepeatTimes));
	}

	if (pNewForRptDB != NULL)
	{
		delete pNewForRptDB;
	}

	return pReportFinal;
}

CReport* CTestControlBase::CreateMtFinalReport(CCommCmd* pItem, long nCalMode, long nRepeatTimes)
{
	CReport *pReportFinal = NULL;

	if (nCalMode == TEST_CALMODE_NONE)
	{
		pReportFinal = pItem->GetCurrReport();
		return pReportFinal;
	}

	CExBaseList oReports;

	//获取需要计算的报告数据对象
	GetMtReportsForCal(pItem, oReports);

	if (oReports.GetCount() < 2)
	{
		oReports.RemoveAll();
		return pReportFinal;
	}

	CGbItemBase *pNewForRptDB = NULL;

	if (m_pGuideBook->IsSaveRptToDB() || g_theSmartTestBaseApp->IsSaveRptToDB())
	{
		oReports.RemoveAll();
		pNewForRptDB = ats_CloneGbItemFromDB(pItem);
		GetMtReportsForCal(pNewForRptDB, oReports);
	}

	//计算报告数据
	pReportFinal = AddReport(pItem, nRepeatTimes, nRepeatTimes);//2017.05.17
	pReportFinal->SetCalReport();
	pReportFinal->m_pValues->DeleteAll();

	switch (nCalMode)
	{
	case TEST_CALMODE_AVERAGE:
		CmmCalReports_Average(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MAX:
		CmmCalReports_Max(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MIN:
		CmmCalReports_Min(pReportFinal, oReports);
		break;

	case TEST_CALMODE_ERRORMAX:
		CmmCalReports_ErrorMax(pReportFinal, oReports);
		break;

	case TEST_CALMODE_STDERROR:
		CmmCalReports_StdError(pReportFinal, oReports);
		break;

	default:
		break;
	}

	oReports.RemoveAll();

	if (nCalMode == TEST_CALMODE_STDERROR)
	{
		//pItem->RunResultScript();
	}
	else
	{
		InitFinalReportState(pItem, GetMaxRepeatTimes(nRepeatTimes));
	}

	if (pNewForRptDB != NULL)
	{
		delete pNewForRptDB;
	}

	return pReportFinal;
}

//电气量重复测试时，对于电气量下的子项目，肯定也是重复测试的，因此根据电气量报告的处理方式，计算CAL报告
void CTestControlBase::CreateCalRpt_SubItems(CMacroTest *pMacroTest)
{
	if (pMacroTest->m_oSubGbItems.GetCount() == 0)
	{
		return;
	}

	POS pos = pMacroTest->m_oSubGbItems.GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pMacroTest->m_oSubGbItems.GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_COMMCMD)
		{
			//暂时只处理通讯命令的
			continue;
		}

		CCommCmd *pCommCmd = (CCommCmd *)pObj;
		CReport *pReport = CreateMtFinalReport(pCommCmd, pMacroTest->GetCalMode(), pMacroTest->m_nRepeatTimes);
		//对于重复测试的电气量下的子项目，用于保存计算结果的报告，也需要执行结果判断脚本
		pCommCmd->RunRsltExpr_Only(m_nMacroTestTimes + 2, pMacroTest->m_nRepeatTimes);//此时，m_nMacroTestTimes还没有递增。此处需要+2
		FillReport(pReport, pMacroTest->m_nRepeatTimes);

		//重复测试的电气量下的子项目，生成计算报告后，再次触发项目状态改变，以上送REPORT事件
		UpdateStateAfterFinishTestItem(pCommCmd);
		WriteItemTempFile(pCommCmd);
	}
}

void CTestControlBase::InitFinalReportState(CGbItemBase *pItem, long nRepeatTimes)
{
	CReports *pReports = pItem->GetReports();
	CReport *pReport = NULL;

	long nTotalCount = pReports->GetCount();
	long nBeginIndex = nTotalCount - (nRepeatTimes+1) - 1;

	if (nBeginIndex<0)
	{
		nBeginIndex = 0;
	}

	long nRsltJdg = 1;

	for (; nBeginIndex<nRepeatTimes+1; nBeginIndex++)
	{
		pReport = (CReport *)pReports->GetAtIndex(nBeginIndex);

		if (pReport == NULL)
		{
			continue;
		}

		if (pReport->GetResultJudge() == 0)
		{
			nRsltJdg = 0;
			break;
		}
	}

	//更新状态
	pItem->SetRsltJdg(nRsltJdg);
}

void CTestControlBase::GetCmmReportsForCal(CCommCmd* pItem, CExBaseList &oReports)
{
	CReports *pReports = pItem->GetReports();
	pReports->GetReportsForCal(oReports);
}

void CTestControlBase::GetMtReportsForCal(CGbItemBase* pItem, CExBaseList &oReports)
{
	CReports *pReports = pItem->GetReports();
	CReport *pReport = NULL;
	POS pos = pReports->GetTailPosition();

	while (pos != NULL)
	{
		pReport = (CReport*)pReports->GetPrev(pos);

		if (pReport->IsCalReport())
		{
			break;
		}

		oReports.AddTail(pReport);
	}
}

BOOL CTestControlBase::CanCal(CValue *pValue, CString &bstrID, CString &bstrValue)
{
	bstrID = pValue->m_strID;

	if (g_strTestResultJudgeKey == bstrID)
	{
		return FALSE;
	}

	if (g_strTestResultDescriptKey == bstrID)
	{
		return FALSE;
	}

	bstrValue = pValue->m_strValue;

	if (!IsStringNumber(bstrValue))
	{
		return FALSE;
	}

	return TRUE;
}

void CTestControlBase::CmmCalReports_Average(CReport *pReportFinal, CExBaseList &oReports)
{
	CReport *pReport = NULL;
	CReport *pReportRef = NULL;
	CValue * oValNew = NULL;
	CValue * oValRef = NULL;
	CValue * pValue = NULL;
	POS pos = oReports.GetHeadPosition();
	pReportRef = (CReport*)oReports.GetAt(pos);

	CValues * pValues = pReportRef->m_pValues;
	long nCount = pValues->GetCount();
	long nIndex = 0;
	double dSum = 0;
	long nValCount = 0;
	CString bstrID;
	CString bstrValue;
	CString strValue;
	POS posVal = pValues->GetHeadPosition();

	while (posVal != NULL)
	{
		oValRef = (CValue*)pValues->GetNext(posVal);
		oValNew = (CValue*)oValRef->Clone();
		pReportFinal->m_pValues->AddNewChild(oValNew);
		
		if (!CanCal(oValRef, bstrID, bstrValue))
		{
			continue;
		}

		pos = oReports.GetHeadPosition();
		nValCount = 0;
		dSum = 0;

		while (pos != NULL)
		{
			pReport = (CReport*)oReports.GetNext(pos);
			pValue = pReport->FindReportData(bstrID);

			if (pValue != NULL)
			{
				nValCount++;
				bstrValue = pValue->m_strValue;
#ifdef _UNICODE
                dSum += _wtof(bstrValue.GetString());
#else
                dSum += atof(bstrValue.GetString());
#endif
			}
		}


		if (nValCount >= 2)
		{
			dSum /= nValCount;
		}

		strValue.Format(_T("%f"), dSum);
		oValNew->PutValue(strValue);
	}
}

void CTestControlBase::CmmCalReports_Max(CReport *pReportFinal, CExBaseList &oReports)
{
	CReport *pReport = NULL;
	CReport *pReportRef = NULL;
	CValue * oValNew = NULL;
	CValue * oValRef = NULL;
	CValue * pValue = NULL;
	POS pos = oReports.GetHeadPosition();
	pReportRef = (CReport*)oReports.GetAt(pos);

	CValues * pValues = pReportRef->m_pValues;
	long nCount = pValues->GetCount();
	long nIndex = 0;
	double dMax = 0;
	CString bstrID;
	CString bstrValue;
	CString strValue;
	POS posVal = pValues->GetHeadPosition();

	while (posVal != NULL)
	{
		oValRef = (CValue*)pValues->GetNext(posVal);
		oValNew = (CValue*)oValRef->Clone();
		pReportFinal->m_pValues->AddNewChild(oValNew);

		if (!CanCal(oValRef, bstrID, bstrValue))
		{
			continue;
		}

		pos = oReports.GetHeadPosition();
#ifdef _UNICODE
        dMax = _wtof(oValRef->m_strValue.GetString());
#else
        dMax = atof(oValRef->m_strValue.GetString());
#endif

		while (pos != NULL)
		{
			pReport = (CReport*)oReports.GetNext(pos);
			pValue = pReport->FindReportData(bstrID);

			if (pValue != NULL)
			{
#ifdef _UNICODE
				dMax = max(_wtof(pValue->m_strValue), dMax);
#else
                dMax = max(atof(pValue->m_strValue.GetString()), dMax);
#endif
			}
		}

		strValue.Format(_T("%f"), dMax);
		oValNew->PutValue(strValue);
	}
}

void CTestControlBase::CmmCalReports_Min(CReport *pReportFinal, CExBaseList &oReports)
{
	CReport *pReport = NULL;
	CReport *pReportRef = NULL;
	CValue * oValNew = NULL;
	CValue * oValRef = NULL;
	CValue * pValue = NULL;
	POS pos = oReports.GetHeadPosition();
	pReportRef = (CReport*)oReports.GetAt(pos);

	CValues * pValues = pReportRef->m_pValues;
	long nCount = pValues->GetCount();
	long nIndex = 0;
	double dMin = 0;
	CString bstrID;
	CString bstrValue;
	CString strValue;
	POS posVal = pValues->GetHeadPosition();

	while (posVal != NULL)
	{
		oValRef = (CValue*)pValues->GetNext(posVal);
		oValNew = (CValue*)oValRef->Clone();
		pReportFinal->m_pValues->AddNewChild(oValNew);

		if (!CanCal(oValRef, bstrID, bstrValue))
		{
			continue;
		}

		pos = oReports.GetHeadPosition();
#ifdef _UNICODE
		dMin = _wtof(oValRef->m_strValue);
#else
        dMin = atof(oValRef->m_strValue.GetString());
#endif

		while (pos != NULL)
		{
			pReport = (CReport*)oReports.GetNext(pos);
			pValue = pReport->FindReportData(bstrID);

			if (pValue != NULL)
			{
#ifdef _UNICODE
				dMin = min(_wtof(pValue->m_strValue), dMin);
#else
                dMin = min(atof(pValue->m_strValue.GetString()), dMin);
#endif
			}
		}

		strValue.Format(_T("%f"), dMin);
		oValNew->PutValue(strValue);
	}	
}

CReport* rpt_FindAbsErrorMaxReport(const CString &strValID, CExBaseList &oReports)
{
	CReport *pReport = NULL;
	CReport *pReportRef = NULL;
	CValue * pValue = NULL;
	POS pos = oReports.GetHeadPosition();

	double dMax = 0;
	double dAbsError = 0;

	while (pos != NULL)
	{
		pReport = (CReport*)oReports.GetNext(pos);
		pValue = pReport->FindReportData(strValID);

		if (pValue != NULL)
		{
			dAbsError = CString_To_double(pValue->m_strValue);
			dAbsError = fabs(dAbsError);

			if (dAbsError >= dMax)
			{
				pReportRef = pReport;
				dMax = dAbsError;
			}
		}
	}	

	return pReportRef;
}

void CTestControlBase::CmmCalReports_ErrorMax(CReport *pReportFinal, CExBaseList &oReports)
{
	CReport *pReport = NULL;
	CReport *pReportRef = NULL;
	CValue * pValue = NULL;
	POS pos = oReports.GetHeadPosition();

	pReportRef = rpt_FindAbsErrorMaxReport(g_strCalMode_ErrorValueID, oReports);

	if (pReportRef != NULL)
	{
		pReportFinal->m_pValues->AppendCloneEx(*pReportRef->m_pValues);
	}
	else
	{
		//pReportFinal->SetResultJudge(0);
		CReport *pHeadReport = (CReport*)oReports.GetHead();
		POS posValue = NULL;
		posValue = pHeadReport->m_pValues->GetHeadPosition();

		while (posValue != NULL)
		{
			pValue = (CValue *) pHeadReport->m_pValues->GetNext(posValue);
			CString strValID = pValue->m_strID;
			CString strLeft = strValID.Left(4);

			if (strLeft == g_strAinExand_Abs || strLeft == g_strAinExand_Rel || strLeft == g_strAinExand_Rst)
			{
				continue;
			}

			pReportRef = rpt_FindAbsErrorMaxReport(g_strAinExand_Abs + pValue->m_strID, oReports);
			pReportFinal->m_pValues->AddNewChild((CExBaseObject*)pValue->Clone());

			if (pReportRef != NULL)
			{
				pValue = (CValue *)pReportRef->m_pValues->FindByID(g_strAinExand_Abs + strValID);
				if (pValue != NULL)
				{
					pReportFinal->m_pValues->AddNewChild((CExBaseObject*)pValue->Clone());
				}

				pValue = (CValue*)pReportRef->m_pValues->FindByID(g_strAinExand_Rel + strValID);
				if (pValue != NULL)
				{
					pReportFinal->m_pValues->AddNewChild((CExBaseObject*)pValue->Clone());
				}

				pValue = (CValue*)pReportRef->m_pValues->FindByID(g_strAinExand_Rst + strValID);
				if (pValue != NULL)
				{
					pReportFinal->m_pValues->AddNewChild((CExBaseObject*)pValue->Clone());
				}
			}
		}

	}
}

void CTestControlBase::CmmCalReports_StdError(CReport *pReportFinal, CExBaseList &oReports)
{
	POS pos = oReports.GetHeadPosition();
	CReport *pReportRef = (CReport*)oReports.GetAt(pos);

	pReportFinal->m_pValues->AppendCloneEx(*pReportRef->m_pValues);
}

void CTestControlBase::CmmCalReports_OverWrite(CReport *pReportFinal, CExBaseList &oReports)
{
	
}

// 规约帧录波设置
void CTestControlBase::GBS_RecordPackage(const  char* pszPkgID)
{
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_PrtcEngineFalse/*L"规约引擎设备数据对象错误"*/);
	}
	try
	{
		//oPpDevice->RecordPackage(_bstr_t(pszPkgID));
	}
	catch (...)
	{
		TRACE("catch error-----");
	}

}

void CTestControlBase::GBS_UnRecordPackage(const  char* pszPkgID)
{
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_PrtcEngineFalse /*L"规约引擎设备数据对象错误"*/);
	}
	try
	{
		//oPpDevice->UnRecordPackage(_bstr_t(pszPkgID));
	}
	catch (...)
	{
		TRACE("catch error-----");
	}
}

void CTestControlBase::GBS_GetPackagePcTime(const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail)
{
}

long CTestControlBase::GBS_ReadMacroTestResult()
{
	if (m_pCurrTestItem == NULL)
	{
		return 0;
	}

	if (m_pCurrTestItem->GetClassID() != GBCLASSID_MACROTEST)
	{
		return 0;
	}

	UpdateMacroTestReport((CMacroTest*)m_pCurrTestItem);

	return 0;
}

void CTestControlBase::GBS_DownloadMacroTestPara()
{
	if (m_pMacroTestInterface == NULL)
	{//创建失败，则终止测试
		StopTestExtern();
	}

	if (m_pCurrTestItem == NULL)
	{
		return;
	}

	if (m_pCurrTestItem->GetClassID() != GBCLASSID_MACROTEST)
	{
		return;
	}

	CMacroTest* pMacroTest = (CMacroTest*)m_pCurrTestItem;
	CMacroTestPara* pTestPara;
	CString strTestPara;
	CString strMacroID;

	pTestPara = pMacroTest->GetMacroTestPara();
	strMacroID = pTestPara->GetMacroID();
	strTestPara = pTestPara->GetParaDatas();

	//控制装置输出
	try
	{
		long nRet = m_pMacroTestInterface->Test(strMacroID,strTestPara); 
	}
	catch(...)
	{
	}
}

long CTestControlBase::GBS_PpGetDeviceAttr(const char *pszAttrID, CString &strAttr)
{
	long nResult = 0;
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_PrtcEngineFalse/*L"规约引擎设备数据对象错误"*/);
	}
	try
	{
		CProtocolDataInterface* oData = oPpDevice->FindData(pszAttrID);

		if (oData != NULL)
		{
			strAttr = oData->GetValue();
		}

		oData->Release();
	}
	catch (...)
	{
		nResult = 1;
	}

	return 0;
}

void CTestControlBase::GBS_PpSetDeviceAttr(const char *pszAttrID, CString &strAttr)
{
	long nResult = 0;
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_PrtcEngineFalse /*L"规约引擎设备数据对象错误"*/);
	}
	try
	{
		oPpDevice->SetAttrByID(pszAttrID, strAttr);
	}
	catch (...)
	{
		nResult = 1;
	}
}

long CTestControlBase::GBS_PpRptGetDevieNodeDatas(const char *pszNodePath)
{
	long nResult = 0;
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_PrtcEngineFalse/*L"规约引擎设备数据对象错误"*/);
		return 0;
	}

	if (m_pCurrTestItem == NULL)
	{
		return 0;
	}

	CGbItemBase *pCurrItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = pCurrItem->GetReport(-1);

	if (pReport == NULL)
	{
		return 0;
	}

	try
	{
		//PpEngine::IDeviceNodePtr oNode = NULL;
		CProtocolDatasetInterface* oNode = NULL;

		try
		{
			oNode = oPpDevice->FindDataSet(pszNodePath);
		}
		catch(...){}

		if (oNode != NULL)
		{
			CString strXml = oNode->GetXmlData();
			BSTR bstrXml = strXml.AllocSysString();//oNode.GetXmlData();
			CShortDatas oDatas;
			oDatas.SetXml(bstrXml, CDataMngrXmlRWKeys::CShortDatasKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
			pReport->AddReportEx(&oDatas);
			pReport->AddReport(&oDatas);
			::SysFreeString(bstrXml);
			oNode->Release();
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_PathData.GetString() /*_T("路径：%s：数据个数%d")*/, pszNodePath, oDatas.GetCount());
		}
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_PathFalse.GetString() /*_T("路径错误：%s")*/, pszNodePath);
		}
	}
	catch (...)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_PathFalse.GetString() /*_T("路径错误：%s")*/, pszNodePath);
		nResult = 0;
	}

	return 0;
}


long CTestControlBase::GBS_PpDeleteAllNodeData(const char *pszNodePath)
{
	GbDeleteAllNodeData(CString(pszNodePath));
	return 0;
}

long CTestControlBase::GBS_PpRptGetDeviceAttrs(void)
{
	return 0;
}

long CTestControlBase::GBS_PpGetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, CString &strAttr)
{
	return 0;
}

long CTestControlBase::GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, const char *strValue)
{
	return 0;
}

long CTestControlBase::GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID)
{
	return 0;
}

long CTestControlBase::GBS_PpReleaseDevice(const char *pszDeviceID)
{
	return 0;
}

long CTestControlBase::GBS_PpReleaseAllDevice()
{
	POS pos = m_oDeviceRefs.GetHeadPosition();
	CPpDeviceRef *p = NULL;
	
	while (pos != NULL)
	{
		p = (CPpDeviceRef*)m_oDeviceRefs.GetNext(pos);

		if (p->m_oPpDevice != NULL)
		{
			try
			{
                p->m_oPpDevice->UnLoad();
                p->ReleaseDevice();
				p->SetConnectState(FALSE);
				Sleep(1000);
			}
			catch(...)
			{
			}
		}
		else
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++ for debug  ++++ CTestControlBase::GBS_PpReleaseAllDevice()  %s   ++++  2 "), p->m_strID.GetString());
		}
	}

	return 0;
}


long CTestControlBase::GBS_PpCreateDeviceEx(const char *pszPpFile, const char *pszDeviceFile)
{
	return 0;
}

long CTestControlBase::GBS_PpReleaseDeviceEx()
{
	return 0;
}

void CTestControlBase::GBS_MtExcuteCmd(const char *pszCmd, const char *pCmdPara)
{
	if (m_pMacroTestInterface != NULL)
	{
		try
		{
			m_pMacroTestInterface->ExcuteCmd(CString(pszCmd), CString(pCmdPara));
		}
		catch (...)
		{
			TRACE("catch error-----");
		}
	}
}

void CTestControlBase::GBS_MtRegistPpDataMsg(const char *pszDvmDataPath)
{
	if (m_pMacroTestInterface != NULL)
	{
		CString strDvmDataPath;
		strDvmDataPath = pszDvmDataPath;

		try
		{
			BOOL bSucc = FALSE;
			UINT nHwnd = m_pMacroTestInterface->GetExternMsgRcvWnd();
			UINT nMsgID = m_pMacroTestInterface->GetExternMsgID();
			
			CPpDeviceRef *pRef = NULL;
			POS pos = m_oDeviceRefs.GetHeadPosition();

			while (pos != NULL)
			{
				pRef = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);

				if (pRef->IsDeviceConnectSucc())
				{
					pRef->m_oPpDevice->RegisterDataChangedWndMsg(strDvmDataPath, nHwnd, nMsgID);
					bSucc = TRUE;
				}
			}

			if (!bSucc)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE,  g_sLangTxt_FunctionError.GetString() /*_T("MtRegistPpDataMsg函数调用错误")*/);
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RegistPpDataMsg(%s)"), strDvmDataPath.GetString());
			}
		}
		catch (...)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_TestFctnNo.GetString() /*_T("测试功能组件没有实现GetExternMsgRcvWnd、G方法etExternMsgID")*/);
		}
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,g_sLangTxt_UnCreatFctn .GetString() /*_T("还没有创建测试功能组件！")*/);
	}
}

void CTestControlBase::GBS_MtUnRegistPpDataMsg(const char *pszDvmDataPath)
{
	if (m_pMacroTestInterface != NULL)
	{
		CString strDvmDataPath;
		strDvmDataPath = pszDvmDataPath;

		try
		{
			BOOL bSucc = FALSE;

			CPpDeviceRef *pRef = NULL;
			POS pos = m_oDeviceRefs.GetHeadPosition();

			while (pos != NULL)
			{
				pRef = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);

				if (pRef->IsDeviceConnectSucc())
				{
					pRef->m_oPpDevice->UnRegisterDataChangedWndMsg(strDvmDataPath);
					bSucc = TRUE;
				}
			}

			if (!bSucc)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FunctionError.GetString() /*_T("UnRegisterDataChangedWndMsg函数调用错误")*/);
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("UnRegistPpDataMsg(%s)"), strDvmDataPath.GetString());
			}
		}
		catch (...)
		{
			TRACE("catch error-----");
		}
	}
}

void CTestControlBase::GBS_MtRegistCmdMsg(const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam)
{
	if (m_pMacroTestInterface != NULL)
	{
		CString strCmdID;
		strCmdID = pszCmdID;

		try
		{
			BOOL bSucc = FALSE;
			UINT nHwnd = m_pMacroTestInterface->GetExternMsgRcvWnd();
			UINT nMsgID = m_pMacroTestInterface->GetExternMsgID();

			CPpDeviceRef *pRef = NULL;
			POS pos = m_oDeviceRefs.GetHeadPosition();

			while (pos != NULL)
			{
				pRef = (CPpDeviceRef *)m_oDeviceRefs.GetNext(pos);

				if (pRef->IsDeviceConnectSucc())
				{
					CProtocolParasInterface* oDataInterface = pRef->m_oPpDevice->GetDataInterface();

					if (oDataInterface != NULL)
					{
						CString strText;
						oDataInterface->Reset();
						strText.Format(_T("%d"), nCmdState);
						oDataInterface->AddData(_T("CmdState"), strText);

						strText.Format(_T("%d"), nCmdWParam);
						oDataInterface->AddData(_T("wParam"), strText);

						strText.Format(_T("%d"), nCmdLParam);
						oDataInterface->AddData(_T("lParam"), strText);
						oDataInterface->Release();
					}

					pRef->m_oPpDevice->RegisterDataChangedWndMsg(strCmdID, nHwnd, nMsgID);
					bSucc = TRUE;
				}
			}

			if (!bSucc)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE,g_sLangTxt_FunctionError.GetString() /*_T("MtRegistPpDataMsg函数调用错误")*/);
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RegistPpDataMsg(%s)"), strCmdID.GetString());
			}
		}
		catch (...)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE,  g_sLangTxt_TestFctnNo.GetString() /*_T("测试功能组件没有实现GetExternMsgRcvWnd、G方法etExternMsgID")*/);
		}
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,g_sLangTxt_UnCreatFctn .GetString() /*_T("还没有创建测试功能组件！")*/);
	}
}

void CTestControlBase::GBS_MtUnRegistCmdMsg(const char *pszCmdID)
{
	GBS_MtUnRegistPpDataMsg(pszCmdID);
}

void CTestControlBase::GBS_MtRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax)
{

}

long CTestControlBase::GBS_GetTestIndex(CGbItemBase *pItem)
{
	if (pItem == NULL)
	{
		return -1;
	}

	UINT nClassID = pItem->GetClassID();

	if (nClassID == GBCLASSID_MACROTEST)
	{
		return m_nMacroTestTimes;
	}

	if (nClassID == GBCLASSID_COMMCMD)
	{
		return m_nCommCmdTestTimes;
	}

	return -1;
}

long CTestControlBase::GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara)
{
	return 1;
}

long CTestControlBase::GBS_RcdSetProgID(const char* pszRcdProgID)
{
	return 0;
}

long CTestControlBase::GBS_RcdExit()
{
	return 0;
}

long CTestControlBase::GBS_RcdConfig(const char* pszPara)
{
	return 0;
}

long CTestControlBase::GBS_RcdSelect(const char* pszPara)
{
	return 1;
}

long CTestControlBase::GBS_RcdValidate(const char* pszRsltID)
{
	return 0;
}

long CTestControlBase::GBS_RcdCmpClear()
{
	return 0;
}

long CTestControlBase::GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile)
{
	return 0;
}

CCommCmd* CTestControlBase::GBS_RcdCmp_GetCommCmd()
{
	return NULL;
}

CString CTestControlBase::GBS_RcdGetRcdDestPath(BOOL bIsFullPath)
{
	CString strRcdFilePath;

	return strRcdFilePath;
}

long CTestControlBase::GB_GetFullPath(CGbItemBase *pCurrItem, CString &strFile)
{
	return strFile.GetLength();
}

long CTestControlBase::GBS_RcdCmp_GetFiles(const char* pszStdFile, const char* pszTestFile, CString &strStdFile, CString &strTestFile, CGbItemBase **ppRcdCmpItem)
{
	return 1;
}

long CTestControlBase::GBS_RcdAnalyse_GetFile(const char* pszRcdFile, CString &strRcdFile, CGbItemBase **ppRcdCmpItem)
{
	return 1;
}

long CTestControlBase::GBS_RcdCmp_CopyStdFile(CTestControlBase *pTestControl, CString &strStdSrcFile, CString &strStdDestFile)
{
	return 0;
}

long CTestControlBase::GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir)
{
	return 0;
}


long CTestControlBase::GBS_RcdAnalyse(const char* pszRcdFile)
{
	return 0;
}


void CTestControlBase::Gbs_SetTmTriggerSecond(long nSecond, long nOptr)
{

}

void CTestControlBase::Gbs_SetTmTriggerCountMinute(long nMinute)
{

}

void CTestControlBase::Gbs_EnterTmTrigger()
{

}

void CTestControlBase::Gbs_StartTimerTigger()
{

}

void CTestControlBase::Gbs_StopTimerTrigger()
{

}

long CTestControlBase::GBS_BinRslt(CGbItemBase *pItem, const char *pszParaID, const char *pszRsltID)
{
	CString strParaID, strRsltID, strRefuseID, strUnWantedID;
	strParaID = pszParaID;
	strRsltID = pszRsltID;
	strRefuseID = g_strBinartRsltID_RefuseBinary;
	strUnWantedID = g_strBinartRsltID_UnWantedBinary;
	CReport *pReport = pItem->GetReport(-1);
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return 0;
	}

	CValue *pValuePara = (CValue*)pReport->m_pValues->FindByID(strParaID);
	CValue *pValueRslt = (CValue*)pReport->m_pValues->FindByID(strRsltID);
	CValue *pValueRefuse = (CValue*)pReport->m_pValues->FindByID(strRefuseID);
	CValue *pValueUnwanted = (CValue*)pReport->m_pValues->FindByID(strUnWantedID);

	if (pValuePara == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("参数[%s]不存在"), strParaID.GetString());
		return 0;
	}

	if (pValueRslt == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("参数[%s]不存在"), strRsltID.GetString());
		return 0;
	}

	if (pValueRefuse == NULL)
	{
		pValueRefuse = new CValue;
		pValueRefuse->m_strID = g_strBinartRsltID_RefuseBinary;
		pValueRefuse->m_strName = g_strBinartRsltName_RefuseBinary;
		pReport->m_pValues->AddNewChild(pValueRefuse);
	}

	if (pValueUnwanted == NULL)
	{
		pValueUnwanted = new CValue;
		pValueUnwanted->m_strID = g_strBinartRsltID_UnWantedBinary;
		pValueUnwanted->m_strName = g_strBinartRsltName_UnWantedBinary;
		pReport->m_pValues->AddNewChild(pValueUnwanted);
	}

	if (g_nLog_TestControl_Msg)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开入结果比较：【下传参数：%s】【上送结果：%s】【拒动节点：%s】【误动节点：%s】")
                                   , pValuePara->m_strValue.GetString(), pValueRslt->m_strValue.GetString(), pValueRefuse->m_strValue.GetString(), pValueUnwanted->m_strValue.GetString());
	}

	return CGuideBookTool::BinRslt(strParaID, pValuePara->m_strValue, pValueRslt->m_strValue, pValueRefuse->m_strValue, pValueUnwanted->m_strValue);
}


long CTestControlBase::GBS_BinStateRslt(CGbItemBase *pItem, const char *pszParaID, const char *pszRsltID)
{
	CString strParaID, strRsltID, strRefuseID, strUnWantedID;
	strParaID = pszParaID;
	strRsltID = pszRsltID;
	strRefuseID = g_strBinartRsltID_RefuseBinary;
	strUnWantedID = g_strBinartRsltID_UnWantedBinary;
	CReport *pReport = pItem->GetReport(-1);
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return 0;
	}

	CValue *pValuePara = (CValue*)pReport->m_pValues->FindByID(strParaID);
	CValue *pValueRslt = (CValue*)pReport->m_pValues->FindByID(strRsltID);
	CValue *pValueRefuse = (CValue*)pReport->m_pValues->FindByID(strRefuseID);
	CValue *pValueUnwanted = (CValue*)pReport->m_pValues->FindByID(strUnWantedID);

	if (pValuePara == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("参数[%s]不存在"), strParaID.GetString());
		return 0;
	}

	if (pValueRslt == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("参数[%s]不存在"), strRsltID.GetString());
		return 0;
	}

	if (pValueRefuse == NULL)
	{
		pValueRefuse = new CValue;
		pValueRefuse->m_strID = g_strBinartRsltID_RefuseBinary;
		pValueRefuse->m_strName = g_strBinartRsltName_RefuseBinary;
		pReport->m_pValues->AddNewChild(pValueRefuse);
		pReport->m_pValues->BringToHead(pValueRefuse);
	}

	if (pValueUnwanted == NULL)
	{
		pValueUnwanted = new CValue;
		pValueUnwanted->m_strID = g_strBinartRsltID_UnWantedBinary;
		pValueUnwanted->m_strName = g_strBinartRsltName_UnWantedBinary;
		pReport->m_pValues->AddNewChild(pValueUnwanted);
		pReport->m_pValues->BringToHead(pValueUnwanted);
	}

	long nRet = CGuideBookTool::BinStateRslt(strParaID, pValuePara->m_strValue, pValueRslt->m_strValue, pValueRefuse->m_strValue, pValueUnwanted->m_strValue);

	if (g_nLog_TestControl_Msg)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开入结果比较：【下传参数：%s】【上送结果：%s】【拒动节点：%s】【误动节点：%s】")
                                   , pValuePara->m_strValue.GetString(), pValueRslt->m_strValue.GetString(), pValueRefuse->m_strValue.GetString(), pValueUnwanted->m_strValue.GetString());
	}

	return nRet;
}


long CTestControlBase::GBS_BinChngCntRslt(CGbItemBase *pItem, const char *pszBinChngData, const char *pszRsltID)
{
	CString strBinChngData, strRsltID;
	strBinChngData = pszBinChngData;
	strRsltID = pszRsltID;
	CReport *pReport = pItem->GetReport(-1);
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return 0;
	}

	CValue *pValueRslt = (CValue*)pReport->m_pValues->FindByID(strRsltID);

	if (pValueRslt == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("参数[%s]不存在"), strRsltID.GetString());
		return 0;
	}

	if (g_nLog_TestControl_Msg)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开入结果比较：【%s】【%s】"), strBinChngData.GetString(), pValueRslt->m_strValue.GetString());
	}

	return CGuideBookTool::BinChngCntRslt(g_strBinaryParaID_BinputsResult, strBinChngData, pValueRslt->m_strValue);
}


void 	CTestControlBase::GBS_AddDataErrorToRpt(CGbItemBase *pItem, const char* pszDataID, long nValue)
{
	CString strID;
	strID = pszDataID;
// 	CString strErrDataID;
// 	strErrDataID.Format(_T("%s%s"), g_strDataResultJudgePrevKey, strID);
	CReport *pReport = pItem->GetReport(-1);
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return;
	}

	Gb_AddDataErrorToRpt_Rslt(pReport->m_pValues, strID, nValue);
}

double CTestControlBase::GBS_GetItemParaValueEx(CGbItemBase *pItem, const char* pszValID)
{
	//如果保存到本地数据库，则打开之前的项目进行判断
    if (g_theSmartTestBaseApp->IsSaveRptToDB() || m_pGuideBook->IsSaveRptToDB())
	{
		return m_oGbItemBaseMapForDB_Mngr.GetItemParaValueEx(pItem, pszValID);
	}
	else
	{
		return pItem->GetItemParaValue(pszValID);
	}
}

CReport* CTestControlBase::GBS_GetReport(CGbItemBase* pItem, long nIndex)
{
	//如果保存到本地数据库，则打开之前的项目进行判断
    if (g_theSmartTestBaseApp->IsSaveRptToDB() || m_pGuideBook->IsSaveRptToDB())
	{
		return m_oGbItemBaseMapForDB_Mngr.GetReport(pItem, nIndex);
	}
	else
	{
		return GetReport(pItem, nIndex);
	}
}

void CTestControlBase::GBS_OffsetTestDataByGbrptIndex(CGbItemBase *pItem, const CString &strRsltDataID)
{
	ASSERT (pItem != NULL);
	ASSERT (pItem->GetClassID() == GBCLASSID_MACROTEST);
	long nDeviceIndex = tctrl_GetTestControlIndex(this);
	CString strSrcDataID;
	TCHAR chIndex;
	long nLen = strRsltDataID.GetLength();
	chIndex = strRsltDataID.GetAt(nLen-1);
	long nDestIndex = chIndex - 'A';
	ASSERT(0 <= nDestIndex && nDestIndex <= 8);

	if (nDestIndex == nDeviceIndex)
	{
		return;
	}

	chIndex += nDeviceIndex;
	strSrcDataID = strRsltDataID;
	strSrcDataID.SetAt(nLen - 1, chIndex);
	CReport *pReport = pItem->GetReport(-1);
	ASSERT (pReport != NULL);

	CValue *pValSrc = (CValue*)pReport->m_pValues->FindByID(strSrcDataID);
	CValue *pValDest = (CValue*)pReport->m_pValues->FindByID(strRsltDataID);
	ASSERT (pValSrc != NULL && pValDest != NULL);
	CString strValSrc = pValSrc->m_strValue;
	CString strValDest = pValDest->m_strValue;
	pValSrc->m_strValue = strValDest;
	pValDest->m_strValue = strValSrc;
}	

//////////////////////////////////////////////////////////////////////////
//
BOOL ats_IsTestControlManyReport(CTestControlBase *pTestControl)
{
	if (pTestControl == NULL)
	{
		return FALSE;
	}

	if (pTestControl->GetTestControlMode() == TESTCONTROLMODE_MGBRPT)
	{
		return TRUE;
	}

	CTestControlBase *pParent = (CTestControlBase*)pTestControl->GetParent();

	if (pParent == NULL)
	{
		return FALSE;
	}

	if (pParent->GetTestControlMode() == TESTCONTROLMODE_MGBRPT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL ats_IsTestControlManyDevice(CTestControlBase *pTestControl)
{
	if (pTestControl == NULL)
	{
		return FALSE;
	}

	if (pTestControl->GetTestControlMode() == TESTCONTROLMODE_MDGBRPT)
	{
		return TRUE;
	}

	CTestControlBase *pParent = (CTestControlBase*)pTestControl->GetParent();

	if (pParent == NULL)
	{
		return FALSE;
	}

	if (pParent->GetTestControlMode() == TESTCONTROLMODE_MDGBRPT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL ats_IsTestControlSdvMpp(CTestControlBase *pTestControl)
{
	if (pTestControl == NULL)
	{
		return FALSE;
	}

	if (pTestControl->GetTestControlMode() == TESTCONTROLMODE_SDVMPP)
	{
		return TRUE;
	}

	CTestControlBase *pParent = (CTestControlBase*)pTestControl->GetParent();

	if (pParent == NULL)
	{
		return FALSE;
	}

	if (pParent->GetTestControlMode() == TESTCONTROLMODE_SDVMPP)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL ats_IsTestControlMode_NORMAL(CTestControlBase *pTestControl)
{
	return (TESTCONTROLMODE_NORMAL == pTestControl->GetTestControlMode());
}

BOOL ats_IsTestControlMode_MGBRPT(CTestControlBase *pTestControl)
{
	return (TESTCONTROLMODE_MGBRPT == pTestControl->GetTestControlMode());
}

BOOL ats_IsTestControlMode_MDGBRPT(CTestControlBase *pTestControl)
{
	return (TESTCONTROLMODE_MDGBRPT == pTestControl->GetTestControlMode());
}

BOOL ats_IsTestControlMode_MDVMGBRP(CTestControlBase *pTestControl)
{
	return (TESTCONTROLMODE_MDVMGRP== pTestControl->GetTestControlMode());
}

BOOL ats_IsTestControlMode_SDVMPP(CTestControlBase *pTestControl)
{
	return (TESTCONTROLMODE_SDVMPP == pTestControl->GetTestControlMode());
}

////2021-2-23  lijunqing : 
// CTestControlBase* tctrl_GetTestControl(CExBaseObject *pItem)
// {
// 	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
// 	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
// 
// 	return pTestControl;
// }


long tctrl_GetTestControlIndex(CTestControlBase *pTestControl)
{
	CTestControlBase *pParent = (CTestControlBase*)pTestControl->GetParent();
	long nDeviceIndex = 0;

	if (pParent == NULL)
	{
		nDeviceIndex = 0;
	}
	else
	{
		nDeviceIndex = pParent->FindTestControlIndex(pTestControl) + 1;
	}

	return nDeviceIndex;
}

//2021-2-26  lijunqing
// #ifndef GUIDEBOOK_DEV_MODE
// CString Gb_GetItemTempFilePath(CGbItemBase* pItem)
// {
// 	CString strTempFilePath = ats_GetBinaryTempFilePath(pItem);
// 	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, pItem);
// 	return strTempFileName;
// }
// #endif

 BOOL ats_IsGuideBook_DeviceSN(CGuideBook *pGuideBook, const CString &strDeviceSN)
 {
	CString strSN = pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);

	return strSN == strDeviceSN;
 }

//2021-8-5  lijunqing
CGuideBook* ats_FindGuideBookByDeviceSN(CTestControlBase *pMainTestControl, const CString &strDeviceSN)
{
	if (ats_IsTestControlMode_NORMAL(pMainTestControl) || ats_IsTestControlSdvMpp(pMainTestControl))
	{//单装置，直接返回
		return pMainTestControl->m_pGuideBook;
	}

	if (ats_IsTestControlMode_MDVMGBRP(pMainTestControl) || ats_IsTestControlManyDevice(pMainTestControl))
	{
		if (ats_IsGuideBook_DeviceSN(pMainTestControl->m_pGuideBook, strDeviceSN))
		{
			return pMainTestControl->m_pGuideBook;
		}

		POS pos = pMainTestControl->GetHeadPosition();
		CTestControlBase *p = NULL;

		while (pos != NULL)
		{
			p = (CTestControlBase *)pMainTestControl->GetNext(pos);

			if (ats_IsGuideBook_DeviceSN(p->m_pGuideBook, strDeviceSN))
			{
				return p->m_pGuideBook;
			}
		}
	}


	return pMainTestControl->m_pGuideBook;
}

void ats_InitReportValuesName(CReport *pReport, CMacroTest *pMacroTest)
{
	//LINUX下，提高速度，不在初始化名称。2024-1-8
#ifdef _PSX_QT_LINUX_
	return;
#endif

	CGuideBook *pGuideBook = (CGuideBook *)pMacroTest->GetAncestor(GBCLASSID_GUIDEBOOK);
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CString strMacroID = pMacroTestPara->GetMacroID();
	CTestMacro *pTestMacro = (CTestMacro *)pGuideBook->m_pTestMacros->FindByID(strMacroID);

	if (pTestMacro == NULL)
	{
		return;
	}

	POS pos = pReport->m_pValues->GetHeadPosition();

	while (pos != NULL)
	{
		CValue *pValue = (CValue *)pReport->m_pValues->GetNext(pos);

		if (pValue->m_strID == g_strTestResultJudgeKey)
		{
			if (pValue->m_strName.IsEmpty())
			{
				pValue->m_strName = g_strTestResultJudgeNameKey;
			}

			continue;
		}

		if (pValue->m_strID == g_strTestResultDescriptKey)
		{
			if (pValue->m_strName.IsEmpty())
			{
				pValue->m_strName = g_strTestResultDescriptNameKey;
			}

			continue;
		}

		if (pValue->m_strID == g_strTestResultTimeKey)
		{
			if (pValue->m_strName.IsEmpty())
			{
				pValue->m_strName = _T("结果时间");
			}

			continue;
		}

		CShortData *pData = pTestMacro->FindDataByID(pValue->m_strID);

		if (pData != NULL)
		{
			if (pValue->m_strName.IsEmpty())
			{
				if (pData->m_strName.IsEmpty())
				{
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TestMacro.xml中，参数【%s】未配置name属性！"), pData->m_strID.GetString());
				}
				else
				{
					pValue->m_strName = pTestMacro->GetParaNamePath(pData);//pData->m_strName;
				}
			}
		}
		else
		{
			//找不到，考虑从结果判断表达式中查找。
			CXExprNode *pNode = (CXExprNode *)pMacroTest->GetRsltExpr();

			//结果判断里面，只有名称
			if (pNode != NULL)
			{
				ats_InitReportValuesName(pValue, pNode);
			}
		}
	}
}	

void ats_InitReportValuesName(CValue *pValue, CXExprNode *pNode)
{
	if (pNode == NULL || pValue == NULL)
	{
		return;
	}

	CString strName;
	pNode->GetValueName(pValue->m_strID, strName);

	if ( !strName.IsEmpty())
	{
		pValue->m_strName = strName;
	}
}
