#include "stdafx.h"
#include "SttSmartTestCom.h"
#include "../../../Module/BaseClass/StringSerializeBufferAscii.h"
#include "../SttCmd/GuideBook/SttItems.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSttSmartTestCom, CWnd)

CSttSmartTestCom::CSttSmartTestCom()
{
	m_pGuideBook = NULL;
	InitSmartTestCom();
}

CSttSmartTestCom::~CSttSmartTestCom()
{
	if (m_pGuideBook != NULL)
	{
		delete m_pGuideBook;
		m_pGuideBook = NULL;
	}

	ExitSmartTestCom();
}

void CSttSmartTestCom::InitSmartTestCom()
{
	if (m_pXSmartTestClient == NULL)
	{
		m_pXSmartTestClient = new CXSmartTestClient();
		m_pXSmartTestClient->InitXSmartTestClient();
	}
}

void CSttSmartTestCom::ExitSmartTestCom()
{
	if (m_pXSmartTestClient != NULL)
	{
		m_pXSmartTestClient->ExitXSmartTestClient();
		delete m_pXSmartTestClient;
		m_pXSmartTestClient = NULL;
	}
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
long CSttSmartTestCom::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

	CSttParas *pParas = pAtsCmd->GetSttParas();
	pParas->CopyEx(m_pXSmartTestClient->GetAtsTestDefine(), TRUE, TRUE);

	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_Test_ID, m_strTestID);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceID, m_strDeviceID);

	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("AtsCreateTestDefine.xml");
	pParas->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("正在创建测试，请稍后……"));
	
    long nRet = m_pXSmartTestClient->CreateTest(m_strTestID, m_strDeviceID);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	//创建成功 在OnTestCreated中返回事件

// 	else
// 	{
// 		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
// 	}

	return nRet;
}

long CSttSmartTestCom::Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

    long nRet = m_pXSmartTestClient->BeginTest(m_strDeviceID);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

    long nRet = m_pXSmartTestClient->StopTest(m_strDeviceID);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

    long nRet = m_pXSmartTestClient->CloseTest(m_strDeviceID);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
}
/*
<ats-cmd name="" id="TestItem" testor="" >
<paras name="" id="">	
<data id="ItemPath" value="" />  【项目的绝对路径】
<data id="ItemIndex" value="" />  【项目的编号】
</paras>
</ats -cmd>
*/
long CSttSmartTestCom::Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

	CString strItemPath;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);

    long nRet = m_pXSmartTestClient->TestPoint(m_strDeviceID, strItemPath);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

	CString strDeviceID, strItemPath;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);

	long nRet = m_pXSmartTestClient->TestBelow(m_strDeviceID, strItemPath);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

	CString strDeviceID;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceID, strDeviceID);

	long nRet = m_pXSmartTestClient->TestAllInlegibleItems(m_strDeviceID);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

	//暂不实现
    return 0;
}

long CSttSmartTestCom::Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

	//暂不实现
    return 0;
}

long CSttSmartTestCom::Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

	//暂不实现
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
 long CSttSmartTestCom::Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	if (m_pXSmartTestClient == NULL)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		return -1;
	}

    CSttParas *pParas = pAtsCmd->GetSttParas();
	CString strDeviceID;
	CDvmData *pDeviceID = (CDvmData*)pParas->FindByID(STT_CMD_PARA_DeviceID);

	if (pDeviceID != NULL)
	{
		strDeviceID = pDeviceID->m_strValue;
	}

	CStringSerializeBufferAscii oReportBuffer;
	oReportBuffer.SetBufferLength(256000);
	oReportBuffer.AllocBuffer(0);

	//此处确保paras下只有一个group
	CDataGroup *pGroup = (CDataGroup *)pParas->FindByClassID(DTMCLASSID_CDATAGROUP);
	POS pos = pGroup->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pGroup->GetNext(pos);
		oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
	}

	CString strReport;
	strReport = oReportBuffer.GetBuffer();

	long nRet = m_pXSmartTestClient->FinishInputData(strDeviceID, strReport);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
 }

 /*
 <ats-cmd name="" id="SetItemState" testor="" >
     <paras name="" id="">
         <data id="ItemPath" value="" />  【项目的绝对路径】
         <data id="ItemIndex" value="" />  【项目的编号】
         <data id="Select" value="1" />
         <data id="Enable" value="1" />
         <data id="Show" value="1" />
     </paras>
 </ats -cmd>e
 */
 long CSttSmartTestCom::Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	 if (m_pXSmartTestClient == NULL)
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		 return -1;
	 }

	 long nSelect, nEnable, nShow;
	 nShow = nSelect = nEnable = 1;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_Select, nSelect);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_Show, nShow);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_Enable, nEnable);

	 CString strItemPath;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	 long nState = TEST_STATE_ELIGIBLE;  //合格

    long nRet = m_pXSmartTestClient->SetItemStateEx(strItemPath, nSelect, nEnable, nShow, nState);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	}
	else
	{
		pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	}

	return nRet;
 }

 long CSttSmartTestCom::Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	return 0;
 }
 
 long CSttSmartTestCom::Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	 if (m_pXSmartTestClient == NULL)
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		 return -1;
	 }

	 CString strDeviceID;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceID, strDeviceID);

	 long nRet = m_pXSmartTestClient->ExportRpt(strDeviceID);

	 if (nRet != SMART_TEST_COM_EXEC_SUCC)
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	 }
	 else
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	 }

	 return nRet;
 }
 
 long CSttSmartTestCom::Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	 if (m_pXSmartTestClient == NULL)
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		 return -1;
	 }

	 CString strItemPath, strDeviceID;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceID, strDeviceID);

	 CSttParas *pParas = pAtsCmd->GetSttParas();
	 CSttItems *pItems = (CSttItems *)pParas->FindByClassID(STTGBXMLCLASSID_CSTTITEMS);
	 CString  strReports;
	 
	 if (pItems != NULL)
	 {
		 pItems->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strReports);
	 }

	 long nRet = m_pXSmartTestClient->SetReports(strDeviceID, strItemPath, strReports);

	 if (nRet != SMART_TEST_COM_EXEC_SUCC)
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	 }
	 else
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	 }

	 return nRet;
 }
 
 long CSttSmartTestCom::Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceID, m_strDeviceID);

	 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_ACK, &oSysState);

	 if (m_pXSmartTestClient == NULL)
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
		 return -1;
	 }

	 CString strItemPath, strDeviceID;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceID, strDeviceID);

	 CString strItems = m_pXSmartTestClient->QueryItems(strDeviceID, strItemPath);

	 if (strItems.IsEmpty())
	 {
		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_FAILURE, &oSysState);
	 }
	 else
	 {
		 BSTR bstrText = strItems.AllocSysString();
		 CSttItems *pItems = new CSttItems();
		 pItems->SetXml(bstrText,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		 SysFreeString(bstrText);
		 pParasReturn->AddNewData(STT_CMD_PARA_Test_ID, m_strTestID);
		 pParasReturn->AddNewData(STT_CMD_PARA_ItemPath, strItemPath);

		 pParasReturn->AddNewChild(pItems);
		 //此处还需要添加data-types节点

		 pSttProtocol->ReturnSysState(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oSysState);
	 }

	 return 0;
 }

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long CSttSmartTestCom::OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState)
{
     return 0;
}

long CSttSmartTestCom::OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
     return 0;
}

long CSttSmartTestCom::OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
     return 0;
}

long CSttSmartTestCom::OnExportRptFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
     return 0;
}

long CSttSmartTestCom::OnTestAppEvent(const CString& strDeviceID, const CString& strEvent)
{
     return 0;
}

long CSttSmartTestCom::OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent)
{
     return 0;
}

long CSttSmartTestCom::OnTestCreated(const CString& strDeviceID)
{
	if (m_pXSmartTestClient == NULL)
	{
		return -1;
	}

	CString strGuideBook;
	strGuideBook = m_pXSmartTestClient->GetGuideBook(strDeviceID);

	if (m_pGuideBook == NULL)
	{
		m_pGuideBook = new CSttGuideBook;
	}
	else
	{
		m_pGuideBook->DeleteAll();
	}

	BSTR bstrText = strGuideBook.AllocSysString();
	m_pGuideBook->SetXml(bstrText,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	SysFreeString(bstrText);

     return 0;
}

long CSttSmartTestCom::OnOpenGbrptFileFailed(const CString& strDeviceID)
{
     return 0;
}