#include "stdafx.h"
#include "SttSmartTest_SvrDebug.h"
#include "SttServerNativeConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSmartTest* CSttSmartTest::g_pSttSmartTest = NULL;
long CSttSmartTest::g_nSttSmartTestRef = 0;

CSttSmartTest::CSttSmartTest()
{
  m_bTestCreated = TRUE;
}

CSttSmartTest::~CSttSmartTest()
{
    
}


CSttSmartTest* CSttSmartTest::Create()
{
	g_nSttSmartTestRef++;

	if (g_nSttSmartTestRef == 1)
	{
		g_pSttSmartTest = new CSttSmartTest();
	}

	return g_pSttSmartTest;
}

void CSttSmartTest::Release()
{
	g_nSttSmartTestRef--;

	if (g_nSttSmartTestRef == 0)
	{
		delete g_pSttSmartTest;
		g_pSttSmartTest = NULL;
	}
}

void CSttSmartTest::FreeTestControl()
{
	
}

long CSttSmartTest::UpdateParameter(CDataGroup *pParas)
{
	return 0;
}

CExBaseObject* CSttSmartTest::GetGuideBook()
{
	return NULL;
}

BOOL CSttSmartTest::IsTestCreated()
{
	return FALSE;
}

CString CSttSmartTest::GetProjectName()
{
	return _T("");
}

//界面交互
long CSttSmartTest::OnException(long nError,const CString &strError)
{
    CLogPrint::LogString(XLOGLEVEL_TRACE, strError);

    return 0;
}

long CSttSmartTest::OnConnectSuccess()
{
    // 	if(m_pHarmToolDlg != NULL && m_pHarmToolDlg->IsWindowVisible())
    // 	{
    // 		m_pHarmToolDlg->m_ctrBtnStart.EnableWindow(TRUE);
    // 	}
    return 0;
}

long CSttSmartTest::OnConnectFailed()
{
    return 0;
}

long CSttSmartTest::OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop)
{ 
    return 0;
}

long CSttSmartTest::OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj)
{
    return 0;
}

long CSttSmartTest::OnStopTest(long nType)
{
    return 0;
}

long CSttSmartTest::OnUpdateMeasure(long nData)
{

    return 0;
}

BOOL CSttSmartTest::IsRunning(long nType)
{
    return FALSE;
}

long CSttSmartTest::HideAllTestItemUI(long nData)
{

    return 0;
}

HWND CSttSmartTest::GetFrameHwnd()
{
    return 0;
}


void CSttSmartTest::ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate, BOOL bShow)
{

}

void CSttSmartTest::ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow)
{
}

void CSttSmartTest::LocateItemReport(CExBaseObject *pGbItem)
{
}



void CSttSmartTest::EditItemPara(CExBaseObject *pGbItem)
{

}

long CSttSmartTest::OnTestBegin()
{
    return 0;
}

/*
<ats-cmd name="" id="CreateTest" testor="" >
    <paras name="" id="">
        <data id="test-id" value="" /> 【测试标识】
+测试定义：
        <data id="gbxml-file" value="*.ppxml" /> 【规约模板文件】
        <data name="EngineProgID" id="EngineProgID" value=""/>
        <data id="ppxml-file" value="*.ppxml" /> 【规约模板文件】
        <data id="dvm-file" value="*.xml" />  【点表文件】
        <data id="cmm-cfg-file" value="*.xml" />  【通信地址设置文件】
        <group id="omm-config" >  【通信地址设置】
            ...........................
        </group>
或者：
        <data id="TestDefine" value="" ><![CADATA[   创建测试的定义  ]]></data>
    </paras>
</ats -cmd>
 */
//如果没有传递测试模板参数，则表示打开已有测试记录，否则创建新的测试记录
long CSttSmartTest::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_CreateTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_CreateTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    CString strGbXmlFile, strGuideBookFileType
                                       , strTestProjectName, strPpEngineProgID, strPpTemplateFile
                                       , strDeviceFile, strTestFolder;
    CString strPath;
    BOOL bCreateNew = FALSE;

    strPpEngineProgID = _T("PpEngine");
    strGuideBookFileType = _T("");
    strPath = _P_GetWorkspacePath();
    strPath += strTestFolder;

   pAtsCmd->GetParasDataValueByID(XPARA_ID_Path, strTestFolder);
    bCreateNew =pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strGbXmlFile);
   pAtsCmd->GetParasDataValueByID(XPARA_ID_GBRPTFILE, strTestProjectName);

    if (bCreateNew)
    {
        CString strTempFile;
        strTempFile = _P_GetTemplatePath();
        strTempFile += strGbXmlFile;

    }
    else
    {
        strPath += strTestProjectName;
    }

    //STT_CMD_PARA_CommConfig
    CDataGroup *pCommConfig = (CDataGroup*)pAtsCmd->FindByID(STT_CMD_PARA_CommConfig);

    return 1;
}

long CSttSmartTest::Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_StartTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_StartTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
 
    return 1;
}

long CSttSmartTest::Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_StopTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_StopTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

long CSttSmartTest::Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_CloseTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_CloseTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	
	return 1;
}/*
<ats-cmd name="" id="TestItem" testor="" >
<paras name="" id="">	
<data id="ItemPath" value="" />  【项目的绝对路径】
<data id="ItemIndex" value="" />  【项目的编号】
</paras>
</ats -cmd>
*/
long CSttSmartTest::Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_TestItem(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_TestItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{

	return 1;
}

long CSttSmartTest::Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_TestFrom(pAtsCmd, pSttProtocol);
}
long CSttSmartTest::Ats_TestFrom(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{

	return 1;
}

long CSttSmartTest::Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_TestAllFailedItems(pAtsCmd, pSttProtocol);
}
long CSttSmartTest::Ats_TestAllFailedItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

long CSttSmartTest::Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_GetItemReport(pAtsCmd, pSttProtocol);
}
long CSttSmartTest::Ats_GetItemReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	return 1;
}

long CSttSmartTest::Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_GetReportFile(pAtsCmd, pSttProtocol);
}
long CSttSmartTest::Ats_GetReportFile(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	return 1;
}

long CSttSmartTest::Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_SetItemState(pAtsCmd, pSttProtocol);
}
long CSttSmartTest::Ats_SetItemState(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

long CSttSmartTest::Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_GetSystemState(pAtsCmd, pSttProtocol);
}
long CSttSmartTest::Ats_GetSystemState(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

/*
<ats-cmd name="FinishInputData" id="" testor="" >
    <paras name="" id="">
        <data name="温度" id="Temperature" data-type="float" unit="" value="0" ……/>
        <data name="湿度" id="Humidity" data-type="float" unit="" value="0" ……/>
        <data name="气压" id="AirPressure" data-type="float" unit="" value="0" ……/>
    </paras>
</ats -cmd>
 */
 long CSttSmartTest::Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_FinishInputData(pAtsCmd, pSttProtocol);
 }
 long CSttSmartTest::Ats_FinishInputData(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	 return 0;
 }


 long CSttSmartTest::Ats_GenerateTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_GenerateTemplate(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_GenerateTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	 CSttParas *pParas = pAtsCmd->GetSttParas();
	 return 0;
 }

 long CSttSmartTest::Ats_GenerateItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_GenerateItems(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_GenerateItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	 CSttParas *pParas = pAtsCmd->GetSttParas();
	 return 0;
 }

 long CSttSmartTest::Ats_GenerateMacroTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_GenerateMacroTest(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_GenerateMacroTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	 CSttParas *pParas = pAtsCmd->GetSttParas();
	 return 0;
 }

 long CSttSmartTest::Ats_SetItemPara(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_SetItemPara(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_SetItemPara(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	 CSttParas *pParas = pAtsCmd->GetSttParas();
	 return 0;
 }

long CSttSmartTest::Ats_SetItemPara_SystemConfig(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) 
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_SetItemPara_SystemConfig(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_SetItemPara_SystemConfig(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) 
{
	return 0;
}
 
long CSttSmartTest::Ats_ManualTrigger(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) 
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_ManualTrigger(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_ManualTrigger(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) 
{
	return 0;
}

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
 CGuideBook* CSttSmartTest::GetGuideBook_AtsGen()
 {
	 return 0;
 }
#endif

CItems* CSttSmartTest::GetItems_AtsGen()
{
	return 0;
}

void CSttSmartTest::SetTemplateGenMode(UINT nMode)
{

}

bool stt_process_cmd_liveupdate(CDataGroup *pParas)
{
	return true;
}

bool stt_validate_cmd_liveupdate(CDataGroup *pParas)
{
	return true;
}

 //返回 TestAppEvent、EngineEvent的事件  2020-11-24  lijunqing
long stt_Return_Ats_Event_Ex(CExBaseObject *pTestControl, const CString &strEventType, const CString &strEventID)
{
	return 0;
}

long stt_Return_Ats_EngineEvent(const CString &strDeviceID, const CString &strEventType, const CString &strEventID, CDvmDataset *pDataset)
{
	return 0;
}
