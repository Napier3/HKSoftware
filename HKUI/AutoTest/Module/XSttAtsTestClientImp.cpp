#include "stdafx.h"

#include "XSttAtsTestClientImp.h"
#include "../../SttStudio/Module/SttTestSysGlobalPara.h"
#include "../../Module/DataMngr/DataMngrTrans.h"

// #include "../SttTestResourceMngr/SttTestResourceMngr.h"
// 
// #include "../../../Module/SmartCap/SmartCapCtrl.h"

CXSttAtsTestClientImp::CXSttAtsTestClientImp()
{
	m_pSttGuideBook = new CSttGuideBook();
	m_oSttAtsClient.m_pAtsEventRcv = this;
	m_pXSmartTestEventInterface = NULL;
	CSttCmdOverTimeTool::Create();
	CCfgDataMngrXmlRWKeys::Create();
}

CXSttAtsTestClientImp::~CXSttAtsTestClientImp()
{
	m_oSttAtsClient.FreeXClientEngine();
	CSttCmdOverTimeTool::Release();
	CCfgDataMngrXmlRWKeys::Release();

	if (m_pSttGuideBook != NULL)
	{
		delete m_pSttGuideBook;
		m_pSttGuideBook = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//
BOOL CXSttAtsTestClientImp::InitXSmartTestClient(const CString &strTestAppIP)
{
	m_oSttAtsClient.ConnectAtsTestServer(strTestAppIP);

	return m_oSttAtsClient.IsConnectSuccess();
}

void CXSttAtsTestClientImp::ExitXSmartTestClient()
{
	m_oSttAtsClient.FreeXClientEngine();
}

long CXSttAtsTestClientImp::CreateTest(CExBaseList *pSttParas)
{
	return m_oSttAtsClient.Ats_CreateTest(pSttParas);
}

long CXSttAtsTestClientImp::CreateTest(const CString &strTestDefine)
{	
	
	return 0;	
}

long CXSttAtsTestClientImp::BeginTest(const CString &strDeviceID)
{
	return m_oSttAtsClient.Ats_StartTest(NULL, NULL);
}

long CXSttAtsTestClientImp::StopTest(const CString &strDeviceID)
{
	return m_oSttAtsClient.Ats_StopTest();
}


long CXSttAtsTestClientImp::Retest(const CString &strDeviceID, const CString &strCommConfig)
{
	return 0;
}


long CXSttAtsTestClientImp::ExportRpt(const CString &strDeviceID)
{
	return m_oSttAtsClient.Ats_ExportRpt(strDeviceID);
}


long CXSttAtsTestClientImp::CloseTest(const CString &strDeviceID)
{
	return m_oSttAtsClient.Ats_CloseTest();
}


long CXSttAtsTestClientImp::ViewItemRpt(const CString &strDeviceID, long nItemIndex)
{

	return 0;
}


long CXSttAtsTestClientImp::TestAllInlegibleItems(const CString &strDeviceID)
{
	return m_oSttAtsClient.Ats_TestAllFailedItems();
}


long CXSttAtsTestClientImp::TestPoint(const CString &strDeviceID, const CString &strItemPath)
{
	return m_oSttAtsClient.Ats_TestItem(strItemPath);
}


long CXSttAtsTestClientImp::TestBelow(const CString &strDeviceID, const CString &strItemPath)
{
	return m_oSttAtsClient.Ats_TestFrom(strItemPath);
}


long CXSttAtsTestClientImp::OpenGbrptFile(const CString &strFilePath, const CString &strSmartTestRunMode, long nDeviceIndex)
{
	return m_oSttAtsClient.Ats_OpenGbrptFile(strFilePath, "", strSmartTestRunMode);
}

CString CXSttAtsTestClientImp::GetAllTestItems(const CString &strDeviceID)
{
	return _T("");
}

CString CXSttAtsTestClientImp::GetTestItemReports(const CString &strDeviceID)
{
	return _T("");
}

long CXSttAtsTestClientImp::SetAppVisible(long nVisible)
{

	return 0;
}

/*
<datas name="" id="">
	<data name="温度" id="TEMP" data-type="" unit="" value="112" format="" remark="" default="" reserved="0" time="0" />
	……
</datas>
*/
long CXSttAtsTestClientImp::FinishInputData(const CString& strDeviceID, const CString& strReports)
{
	CShortDatas oDatas;
	BSTR bstrXml = strReports.AllocSysString();
	oDatas.SetXml(bstrXml,CDataMngrXmlRWKeys::CShortDatasKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
	::SysFreeString(bstrXml);

	CDataGroup oGroup;
	ShortDatas_to_DvmDatas(&oDatas, &oGroup);

	return m_oSttAtsClient.Ats_FinishInputData(&oGroup, NULL);
}


long CXSttAtsTestClientImp::SetItemStateEx(const CString& strItemPath, long nSelect, long nEnable, long nShow, long nState)
{

	return 0;
}


long CXSttAtsTestClientImp::AddEventSink(const CString &strEventSinkProgID, const CString& strDeviceID)
{

	return 0;
}


long CXSttAtsTestClientImp::RemoveEventSink(const CString &strEventSinkProgID, const CString& strDeviceID)
{

	return 0;
}


long CXSttAtsTestClientImp::ClearReport(const CString &strDeviceID)
{

	return 0;
}

long CXSttAtsTestClientImp::GetReports(const CString &strDeviceID, const CString &strItemPath, CExBaseList *pRetSttReports)
{
	CSttItemBase *pItem = stt_gb_find_itembase(m_pSttGuideBook, strItemPath);

	if (pItem == NULL)
	{
		return 0;
	}

	CSttReports *pReports = pItem->GetSttReports();

	if (pReports != NULL)
	{
		pRetSttReports->AppendCloneEx2(*pReports);
	}

	return 0;
}

long CXSttAtsTestClientImp::GetReports(const CString &strDeviceID, const CString &strItemPath, char **ppszReports)
{

	return 0;
}


long CXSttAtsTestClientImp::SetReports(const CString &strDeviceID, const CString &strItemPath, const CString &strReports)
{

	return 0;
}


long CXSttAtsTestClientImp::QueryItems(const CString &strDeviceID, const CString &strItemPath, char **ppszItems)
{

	return 0;
}


long CXSttAtsTestClientImp::ConfigTest(const CString &strDeviceID, const CString &strConfig)
{

	return 0;
}


long CXSttAtsTestClientImp::QueryAtsFile(const CString &strDeviceID, const CString &strConfig)
{
	return m_oSttAtsClient.Ats_QueryAtsFile();
}


CString CXSttAtsTestClientImp::GetDataset(const CString &strDatasetPath)
{
	return _T("");
}

long CXSttAtsTestClientImp::SetDataset(const CString &strDatasetPath, const CString &strDataset)
{

	return 0;
}


long CXSttAtsTestClientImp::RunProcedure(const CString &strProcedureID, const CString &strParas)
{

	return 0;
}


long CXSttAtsTestClientImp::SetItemState(const CString &strParas)
{
	return 0;
}

long CXSttAtsTestClientImp::SetItemState(CExBaseList *pSttParas)
{
	return m_oSttAtsClient.Ats_SetItemState(pSttParas);
}

void CXSttAtsTestClientImp::SetItemState_ForDebug()
{
	if (m_pSttGuideBook->GetCount() <=0 )
	{
		return;
	}

	CSttDevice *pDevice = m_pSttGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	CSttParas oParas;
	long nIndex = 0;
	POS pos = pDevice->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	CString strItemPath, strSel;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}
		
		CSttItems *pItems = (CSttItems *)pObj;
		stt_gb_get_itempath_id(pItems, strItemPath);

		if (nIndex % 2 == 0)
		{
			strSel= _T("1");
		}
		else
		{
			strSel = _T("0");
		}

		oParas.AddNewData(_T("DeviceSN"), "");
		oParas.AddNewData(_T("ItemPath"), strItemPath);
		oParas.AddNewData(_T("Select"),  strSel);
		oParas.AddNewData(_T("Enable"),  _T("1"));
		oParas.AddNewData(_T("Show"),  _T("1"));

		SetItemState(&oParas);
		nIndex++;
		oParas.DeleteAll();
	}
		/*
	//组装xml 调用com组件
	CSttParas* pParas = new CSttParas;
	pParas->AddNewData(_T("DeviceSN"), "");
	pParas->AddNewData(_T("ItemPath"), strItemPath);
	pParas->AddNewData(_T("Select"),  cstrSel);
	pParas->AddNewData(_T("Enable"),  _T("1"));
	pParas->AddNewData(_T("Show"),  _T("1"));

	//调用com组件
	CString bstrXml;
	pParas->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, bstrXml);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("SetItemState =[%s]"), strItemPath);
	m_pSmartTestClient->SetItemState(bstrXml);

	*/
}

long CXSttAtsTestClientImp::GetGuideBook(const CString &strDeviceID, char **ppszGuideBookUft8)
{

	return 0;
}



long CXSttAtsTestClientImp::GetReportFiles(const CString &strDeviceID, CString &strFile)
{

	return 0;
}



long CXSttAtsTestClientImp::GetTotalItemsCount(const CString &strDeviceID, long &nCount)
{

	return 0;
}


long CXSttAtsTestClientImp::QueryTestParas(const CString &strDeviceID, CString &strTestParas)
{

	return 0;
}

//strTestParas结构如下
/*
<group name="" id="Paras">
		<data name="参数1" id="Para1" value="0.25" />
		<data name="参数2" id="Para2" value="0.25999999" />
		<data name="参数3" id="Para3" value="0.75" />
		……
</group>
*/
long CXSttAtsTestClientImp::SetTestParas(const CString &strDeviceID, CString &strTestParas)
{
	//注意，此处new。后面再发送指令时可以直接Append。随着oAtsCmd一起释放
	CDataGroup *pTestParas = new CDataGroup();
	BSTR bstrXml = strTestParas.AllocSysString();
	pTestParas->SetXml(bstrXml,CDataMngrXmlRWKeys::g_pXmlKeys);
	::SysFreeString(bstrXml);
	pTestParas->m_strID = _T("Paras");
	return m_oSttAtsClient.Ats_SetTestParas(strDeviceID, pTestParas);
}


long CXSttAtsTestClientImp::AdjustMainWnd(LONG hMainParent, LONG hLogParent)
{
	return m_oSttAtsClient.Ats_AdjustMainWnd(hMainParent, hLogParent);
}


long CXSttAtsTestClientImp::AttatchLogWnd(unsigned long hWnd)
{

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
void CXSttAtsTestClientImp::SttOpen(const CString &strTestAppCfgFile)
{
	m_oSttAtsClient.SttOpen(strTestAppCfgFile);
}


long CXSttAtsTestClientImp::OnUpdateSyncTime(CDataGroup *pRtSyncTime)
{	
	//m_pXSmartTestEventInterface->OnUpdateSyncTime(pRtSyncTime);
	return 0;
}

long CXSttAtsTestClientImp::OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	CSttItemBase *pItem = stt_gb_find_itembase(m_pSttGuideBook, strItemID);

	if (pItem == NULL)
	{
		return 1;
	}

	pItem->m_nState = nState;
	CString strState = Gb_GetTestStateByID(nState);
	long nSelect = 1, nTemp =0;

	if (pParas->GetDataValue(STT_CMD_PARA_Select, nTemp))
	{
		nSelect = nTemp;
		pItem->m_nSelect = nSelect;
	}
	
	m_pXSmartTestEventInterface->OnItemStateChanged(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState, nSelect);
	return 1;
}

long CXSttAtsTestClientImp::OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	m_pXSmartTestEventInterface->OnTestFinished(strTestID, nDeviceIndex, nReportIndex);

	return 0;
}

long CXSttAtsTestClientImp::OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	m_pXSmartTestEventInterface->OnTestStarted(strTestID, nDeviceIndex, nReportIndex);
	return 0;
}

long CXSttAtsTestClientImp::OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	m_pXSmartTestEventInterface->OnTestStoped(strTestID, nDeviceIndex, nReportIndex);
	return 0;
}

long CXSttAtsTestClientImp::OnTestCreated(const CString &strTestID, CSttParas *pParas)
{
	CSttGuideBook *pSttGuideBook = pParas->GetGuideBook();

	if (pSttGuideBook != NULL)
	{
		if (pSttGuideBook->GetCount() > 0)
		{//有模板数据
			m_pSttGuideBook->ClearGuideBook();
			m_pSttGuideBook->AppendEx(*pSttGuideBook);
			pSttGuideBook->RemoveAll();
		}
	}

	m_pXSmartTestEventInterface->AttachGuideBook(m_pSttGuideBook);
	m_pXSmartTestEventInterface->OnTestCreated(strTestID);
	return 0;
}

long CXSttAtsTestClientImp::OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas)
{
	m_pXSmartTestEventInterface->OnEngineEvent(strTestID, nDeviceIndex, strEvent);
	return 0;
}

long CXSttAtsTestClientImp::OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs) 
{
	m_pXSmartTestEventInterface->OnInputData(pParas, pMsgs);

	return 0;
}

long CXSttAtsTestClientImp::OnExportRptEvent(CSttParas *pParas) 
{
	CString strDeviceSN = _T(""),strEvent = _T(""),strGbRptFile = _T(""),strDocFile = _T(""),strXmlFile = _T("");
	long nDeviceIndex = 0, nReportIndex = 0;

	pParas->GetDataValue(STT_CMD_PARA_DeviceSN,strDeviceSN);
	pParas->GetDataValue(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
	pParas->GetDataValue(STT_CMD_PARA_EventID,strEvent);
	pParas->GetDataValue(STT_CMD_PARA_ReportIndex,nReportIndex);
	pParas->GetDataValue(XPARA_ID_GBRPTFILE,strGbRptFile);
	pParas->GetDataValue(XPARA_ID_DOCFILE,strDocFile);
	pParas->GetDataValue(XPARA_ID_XMLRPTFILE,strXmlFile);

	m_pXSmartTestEventInterface->OnExportRptEvent(strDeviceSN, strEvent, nDeviceIndex, nReportIndex,strGbRptFile,strDocFile,strXmlFile);//20230201 zhouhj 自动测试Paras新增Xml路径

	return 0;
}

long CXSttAtsTestClientImp::OnReTestFinished(CSttParas *pParas)
{
	m_pXSmartTestEventInterface->OnReTestFinished(pParas);

	return 0;
}

long CXSttAtsTestClientImp::OnTestProcess(CSttParas *pParas)
{
	m_pXSmartTestEventInterface->OnTestProcess(pParas);
	return 0;
}

void CXSttAtsTestClientImp::OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("收到项目【%s】报告事件"), strItemID);
	CSttParas *pSttParas = (CSttParas*)pParas;
	CSttReports *pSttReports = pSttParas->GetSttReports(FALSE);
	CSttItemBase *pItem = stt_gb_find_itembase(m_pSttGuideBook, strItemID);

	if (pItem == NULL)
	{
		return;
	}

	if (pSttReports == NULL)
	{
		return;
	}

	pItem->SetReports(pSttReports);
	//m_pXSmartTestEventInterface->OnReport(pItem);
}

void CXSttAtsTestClientImp::ConnectAtsServer()
{
	m_oSttAtsClient.ConnectAtsTestServer();
}

BOOL CXSttAtsTestClientImp::StartTest(CDataGroup *pCurrentUIParas, long nTestMode)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return FALSE;
	}
	
	return m_oSttAtsClient.Ats_StartTest(NULL, NULL, NULL, NULL, TRUE, NULL, _T(""), nTestMode);
}

BOOL CXSttAtsTestClientImp::StopTest()
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
		return FALSE;
	}

	return m_oSttAtsClient.Ats_StopTest();
}

//2022-3-29  lijunqing
//成功返回3
long CXSttAtsTestClientImp::TestItem(const CString &strItemPath)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
	return 0;
	}

	return m_oSttAtsClient.Ats_TestItem(strItemPath);
}

long CXSttAtsTestClientImp::TestFrom(const CString &strItemPath)
{
	if (! m_oSttAtsClient.ConnectAtsTestServer())
	{
	return 0;
	}

	return m_oSttAtsClient.Ats_TestFrom(strItemPath);
}


void CXSttAtsTestClientImp::FillReport(CSttReports *pSttReports)
{
	
}

CExBaseList* CXSttAtsTestClientImp::GetReports()
{

	return NULL;
}

//yzj 2022-2-20 没有使用引用,在执行完成后会析构oInfoList导致野指针崩溃
void CXSttAtsTestClientImp::GetEventInfo(CExBaseList& oInfoList)
{
	m_oSttAtsClient.GetEventInfo(oInfoList);
}

bool CXSttAtsTestClientImp::IsTestStarted()
{
	if(m_oSttAtsClient.m_pXClientEngine == NULL)
	{
		return false;
	}

	return m_oSttAtsClient.m_pXClientEngine->m_bTestStarted;
}

bool CXSttAtsTestClientImp::IsTestAppConnect()
{
	return m_oSttAtsClient.m_bTestAppConnect;
}

void CXSttAtsTestClientImp::CloseTest()
{
	m_oSttAtsClient.Ats_CloseTest();
}

//CreateTest指令的REPLY，返回了gbrptfile的全路径
void CXSttAtsTestClientImp::On_Ats_CreateTest(CSttSysState *pSysState)
{
	CSttParas *pParas = pSysState->GetSttParas();
	CString strGbrptFile;
	pParas->GetDataValue(XPARA_ID_GBRPTFILE, strGbrptFile);

	m_pXSmartTestEventInterface->On_Ats_CreateTest(strGbrptFile);
}

void CXSttAtsTestClientImp::On_Ats_AdjustMainWnd(CSttSysState *pSysState)
{
	CSttParas *pParas = pSysState->GetSttParas();
	LONG nMainWnd = 0;
	pParas->GetDataValue(XPARA_ID_MainWnd, nMainWnd);

	m_pXSmartTestEventInterface->On_Ats_AdjustMainWnd(nMainWnd);
}

long CXSttAtsTestClientImp::OnConnectStateChanged(bool bState)
{
	long nRet = 0;

// 	if (!bState)
// 	{
// 		nRet = //m_pXSmartTestEventInterface->OnTestStoped();//如果Socket断链了,主动将界面返回到停止测试状态
// 	}

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
void stt_Start_SmartTest()
{
	if (IsProgramExist(_T("SmartTest.exe")))
	{
		return;
	}

	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Report/Bin/");
	strPath += _T("SmartTest.exe");

	ExecuteFile(strPath, _T(""), _T("single"));
}

