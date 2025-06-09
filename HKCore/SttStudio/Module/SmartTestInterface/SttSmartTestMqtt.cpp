#include "stdafx.h"
#include "SttSmartTestMqtt.h"
#include "../../../Module/BaseClass/StringSerializeBufferAscii.h"
#include "../SttCmd/GuideBook/SttItems.h"
#include "../../../IotAtsMngr/Module/SttMqttClientEngineConfig.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_Bench.h"
#include "../../../Module/MySqlApp/MySqlBaseApp.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_Items.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_TypeTaskTestItemGen.h"
#include "../../../AutoTest/Module/GuideBook/GuideBook.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_TypeTaskTestItem.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_TypeTaskTestApps.h"
#include "../../../IotAtsMngr/Module/Iot_AtsMngrDB/Iot_TestApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// IMPLEMENT_DYNCREATE(CSttSmartTesMqtt, CWnd)

CSttSmartTestMqtt::CSttSmartTestMqtt()
{
	m_pDevices = NULL;
	InitSmartTestMqtt();
}

CSttSmartTestMqtt::~CSttSmartTestMqtt()
{
	if (m_pDevices != NULL)
	{
		delete m_pDevices;
		m_pDevices = NULL;
	}

	ExitSmartTestMqtt();
}

// void CSttSmartTesMqtt::CreateWnd()
// {
// 	CreateEx(0, AfxRegisterWndClass(0), _T("_Stt_SmartTest_Com_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
// }

void CSttSmartTestMqtt::InitSmartTestMqtt()
{
}

void CSttSmartTestMqtt::ExitSmartTestMqtt()
{

}

//接收网站的MQTT指令，组合成创建测试真正需要的信息，保存成文件，并通过命令行参数，拉起SmartTest
/*
选择哪些测试小项，需要自动测试服务去查询数据库表：iot_type_task_test_item_gen，同时需要根据动态生成的项目，维护表iot_type_task_test_item
创建测试时，先根据配置的测试项目，在模板中进行生成。生成后保存模板，然后创建测试。
*/
long CSttSmartTestMqtt::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttParas *pParas = pAtsCmd->GetSttParas();
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
	BOOL bRet = DownLoadAllFiles(pAtsCmd);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -1;
	}

	CString strGbxmlFile, strItemsSN;
	CExBaseList *pListItems = NULL;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strGbxmlFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_ItemsSN, strItemsSN);
	bRet = GenerateTemplate(strGbxmlFile, strItemsSN, pListItems);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -2;
	}

	//写入任务测试记录表、测试记录子项表
	bRet = DB_InsertTypeTaskTest(pAtsCmd, pListItems);
	delete pListItems;
	pListItems = NULL;

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -3;
	}

	//写入任务-仪器仪表 表
	bRet = DB_InsertTypeTask_TestApps(pAtsCmd);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -4;
	}

	//待处理，保存CreateTest.atscmd。拉起自动测试，并自动开始测试
	bRet = Ats_CreateTest_StartSmartTest(pAtsCmd);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -5;
	}

	return 0;
}

/*
<sys-state name="" id="ItemStateChanged" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
		<data id="ItemIndex" data-type="long" value="2" unit=""/>
		<data id="ItemPath" data-type="string" value="MacroTest1" unit=""/>
		<data id="State" data-type="string" value="TESTING" unit=""/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt::Process_Cmd_SysState_ItemStateChanged(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN, strItemPath, strItemState;
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pSysState->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	pSysState->GetParasDataValueByID(STT_CMD_PARA_State, strItemState);

	return 0;
}

/*
<sys-state name="" id="TestFinished" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
  		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt::Process_Cmd_SysState_TestFinished(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN;

	return 0;
}

/*
<sys-state name="" id="TestStarted" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
  		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt::Process_Cmd_SysState_TestStarted(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN;

	return 0;
}

/*
<sys-state name="" id="TestStoped" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
  		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
	</paras>
</sys-state>
*/
long CSttSmartTestMqtt::Process_Cmd_SysState_TestStoped(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();
	CString strDeviceSN;

	return 0;
}

long CSttSmartTestMqtt::Process_Cmd_SysState_OnReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

long CSttSmartTestMqtt::Process_Cmd_SysState_ExportReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	return 0;
}

long CSttSmartTestMqtt::ReturnSysState_REPLY(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID)
{
	if (pSttProtocol == NULL)
	{
		return 0;
	}

	return pSttProtocol->ReturnSysState_REPLY(pCmmOptrInterface, nCmdExecStatus, pRetData, pszEventID, STT_CMD_SYSSTATE_ATS);
}

long CSttSmartTestMqtt::ReturnSysState_EVENT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID)
{
	if (pSttProtocol == NULL)
	{
		return 0;
	}

	return pSttProtocol->ReturnSysState_EVENT(pCmmOptrInterface, pRetData, pszEventID, STT_CMD_SYSSTATE_ATS);
}

CString CSttSmartTestMqtt::GetItemType(UINT nClassID)
{
	CString strType = Task_Test_Item_Type_Item_Items;
	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		strType = Task_Test_Item_Type_Item_Commcmd;
		break;
	case GBCLASSID_MACROTEST:
		strType = Task_Test_Item_Type_Item_MacroTest;
		break;
	case GBCLASSID_SAFETY:
		strType = Task_Test_Item_Type_Item_Safety;
		break;
	case GBCLASSID_SYSPARAEDIT:
		strType = Task_Test_Item_Type_Item_SysParaEdit;
		break;
	}

	return strType;
}

BOOL CSttSmartTestMqtt::DownLoadAllFiles(CSttAtsCmd *pAtsCmd)
{
	CSttParas *pParas = (CSttParas *)pAtsCmd->GetSttParas();
	//下载被测装置相关的文件
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	BOOL bRet1 = TRUE;

	if (pDevices != NULL)
	{
		bRet1 = DownLoadFiles_Devices(pDevices);
	}

 	CDataGroup *pApps = (CDataGroup *)pParas->FindByID(XPARA_ID_test_apps);
 	BOOL bRet2 = TRUE;
 
 	if (pApps != NULL)
 	{
 		bRet2 = DownLoadFiles_TestApps(pApps);
 	}

	return bRet1 && bRet2;
}

//下载模型文件和规约模板
BOOL CSttSmartTestMqtt::DownLoadFiles_Devices(CDataGroup *pDevices)
{
	if (pDevices == NULL)
	{
		return FALSE;
	}

	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CString strFileDownLoad;

	POS pos = pDevices->GetHeadPosition();
	CString strDvmRoot, strPpRoot;
	strRootPath = _P_GetInstallPath();
	strDvmRoot = strRootPath + _T("e-Protocol\\Library\\");
	strPpRoot = strRootPath + _T("e-Protocol\\Template\\");
	BOOL bReturn = TRUE;

	while (pos != NULL)
	{
		CDataGroup *pDevice = (CDataGroup *)pDevices->GetNext(pos);

		//下载模型文件
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_DVMFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_DVMFILE, strFile);
		BOOL bRet = TRUE;

		strFileDownLoad = strDvmRoot + strFile;
		if (IsFileExist(strFileDownLoad))
		{
			bRet = TRUE;
		}
		else
		{
			if (strFile_s.IsEmpty())
			{
				//模型文件是必须项，若不存在，直接返回下载失败
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("被测设备模型文件【%s】为空，下载失败！"), strFile);
				bRet = FALSE;
			}
			else
			{	

				strUrl = strHttpUrlHead + strFile_s;
				bRet = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
			}
		}

		if (!bRet)
		{
			bReturn = FALSE;
		}

		//下载规约模板文件
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE, strFile);

		strFileDownLoad = strPpRoot + strFile;

		if (IsFileExist(strFileDownLoad))
		{
			bRet = TRUE;
		}
		else
		{
			if (!strFile_s.IsEmpty())
			{
				//规约模板文件不是必须项，若不存在，则跳过下载
				strFileDownLoad = strPpRoot + strFile;
				strUrl = strHttpUrlHead + strFile_s;

				if (IsFileExist(strFileDownLoad))
				{
					bRet = TRUE;
				}
				else
				{
					bRet = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
				}

				if (!bRet)
				{
					bReturn = FALSE;
				}
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("被测设备规约模板文件【%s】为空，下载失败！"), strFile);
			}
		}
	}

	return bReturn;
}

//下载测试功能文件
BOOL CSttSmartTestMqtt::DownLoadFiles_TestApps(CDataGroup *pTestApps)
{
	if (pTestApps == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSmartTestMqtt::GenerateTemplate(const CString &strGbxmlFile, const CString &strItemsSN, CExBaseList *pListItems)
{
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath = strPath + _T("e-Report\\Template\\");
	CString strFile = strPath + strGbxmlFile;
	BOOL bRet = FALSE;

	if (! IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("本地不存在测试模板文件【%s】"), strFile);
		return FALSE;
	}

	//根据测试台SN，查询测试台主键
	CIot_Bench oBench;
	bRet = oBench.QueryBenchBySN(g_pTheMySqlApp, m_strBenchSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到测试台【%s】"), m_strBenchSN);
		return FALSE;
	}

	//根据大项SN，查找大项主键
	CIot_Items oItems;
	bRet = oItems.QueryItemsBySN(g_pTheMySqlApp, strItemsSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到测试大项【%s】"), strItemsSN);
		return FALSE;
	}

	//根据大项Index和测试台Index，查找测试记录子项目生成规则表
	CIot_TypeTaskTestItemGens oItemGens;
	bRet = oItemGens.QueryItemGens(g_pTheMySqlApp, oItems.m_nIndex_Items, oBench.m_nIndex_Bench);

	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("查找测试记录子项生成规则失败！"));
		return FALSE;
	}

	bRet = GenerateTemplate(strFile, &oItemGens, pListItems);

	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("根据子项生成规则，生成测试项目失败！"));
		return FALSE;
	}

	return bRet;
}

//strGbxmlFile：带文件名的绝对路径
BOOL CSttSmartTestMqtt::GenerateTemplate(const CString &strGbxmlFile, CIot_TypeTaskTestItemGens* pItemGens, CExBaseList *pListItems)
{
	if (pItemGens == NULL)
	{
		return FALSE;
	}

	if (pItemGens->GetCount() == 0)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CGuideBook oGuideBook;
	bRet = oGuideBook.OpenXMLFile(strGbxmlFile);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("打开模板文件失败【%s】"), strGbxmlFile);
		return FALSE;
	}

	//CDevice下一级，为测试大项分类，并且只有一个项目分类；
	//测试大项分类下一级，为测试小项分类;
	CDevice *pDevice = oGuideBook.GetDevice();

	if (pDevice == NULL)
	{
		return FALSE;
	}

	//测试大项
	CItems *pItems = (CItems *)pDevice->FindByClassID(GBCLASSID_ITEMS);

	if (pItems == NULL)
	{
		return FALSE;
	}

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pChild = (CItems *)pObj;
		CIot_TypeTaskTestItemGen *pItemGen = (CIot_TypeTaskTestItemGen *)pItemGens->FindByName(pChild->m_strName);

		if (pItemGen == NULL)
		{
			//说明这个测试子项，不是需要测试的
			//此处是将nSelect设置为0，还是直接删掉该子项？
			//待讨论
			pChild->SetItemState(1, 1, 0, TRUE, TRUE, TRUE);
		}
		else
		{
			pChild->SetItemState(1, 1, pItemGen->m_nSelect, TRUE, TRUE, TRUE);

			if (pItemGen->m_nSelect == 1)
			{
				//需要测试的子项，进行参数的更新：因为网站可能进行过编辑
				GenerateTemplate_UpdateParas(pChild, pItemGen);
				//删除已经匹配的生成规则，则剩余的是未匹配的，都是需要添加到模板中的自定义点
				pItemGens->Delete(pItemGen);
			}
		}
	}

	//取第一个子项的分类节点，作为动态生成项目的模板。
	CItems *pTemplateChild = (CItems *)pItems->FindByClassID(GBCLASSID_ITEMS); 
	pos = pItemGens->GetHeadPosition();

	while (pos != NULL)
	{
		CIot_TypeTaskTestItemGen *pItemGen = (CIot_TypeTaskTestItemGen *)pItemGens->GetNext(pos);
		CItems *pNew = (CItems *)pTemplateChild->CloneEx(TRUE, TRUE);
		GenerateTemplate_UpdateParas(pNew, pItemGen);
		pItems->AddNewChild(pNew, TRUE);
	}

	pListItems = pItems;  //返回测试大项
	bRet = oGuideBook.SaveXMLFile(strGbxmlFile);
	pDevice->Remove(pItems);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("保存模板文件失败【%s】"), strGbxmlFile);
		return FALSE;
	}

	return bRet;
}

BOOL CSttSmartTestMqtt::GenerateTemplate_UpdateParas(CItems *pChildItems, CIot_TypeTaskTestItemGen* pItemGen)
{
	BOOL bRet = TRUE;
	pChildItems->m_strName = pItemGen->m_strName;

	//默认测试小项分类中，第一个电气量项目是用来设置仪器仪表的参数的
	CMacroTest *pMacroTest = (CMacroTest *)pChildItems->FindByClassID(GBCLASSID_MACROTEST);

	if (pMacroTest == NULL)
	{
		return FALSE;
	}

	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CMacroTestParaDatas *pFaultParas = pMacroTestPara->GetFaultParaDatas();

	if ( !pItemGen->m_strPara1_Name.IsEmpty()
		&& !pItemGen->m_strPara1_Id.IsEmpty())
	{
		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->AddPara(pItemGen->m_strPara1_Id);
		p->m_strExpression.Format(_T("%s"), pItemGen->m_fPara1_Value);
	}

	if ( !pItemGen->m_strPara2_Name.IsEmpty()
		&& !pItemGen->m_strPara2_Id.IsEmpty())
	{
		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->AddPara(pItemGen->m_strPara2_Id);
		p->m_strExpression.Format(_T("%s"), pItemGen->m_fPara2_Value);
	}

	if ( !pItemGen->m_strPara3_Name.IsEmpty()
		&& !pItemGen->m_strPara3_Id.IsEmpty())
	{
		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->AddPara(pItemGen->m_strPara3_Id);
		p->m_strExpression.Format(_T("%s"), pItemGen->m_fPara3_Value);
	}

	if ( !pItemGen->m_strPara4_Name.IsEmpty()
		&& !pItemGen->m_strPara4_Id.IsEmpty())
	{
		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->AddPara(pItemGen->m_strPara4_Id);
		p->m_strExpression.Format(_T("%s"), pItemGen->m_fPara4_Value);
	}

	return bRet;
}

BOOL CSttSmartTestMqtt::DB_InsertTypeTaskTest(CSttAtsCmd *pAtsCmd, CExBaseList *pListItems)
{
	if (pAtsCmd == NULL)
	{
		return FALSE;
	}

	CString strUserName, strItemsSN, strHumidity, strTempreture;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_USER_NAME, strUserName);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_ItemsSN, strItemsSN);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_Humidity, strHumidity);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_Tempreture, strTempreture);
	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	BOOL bRet = TRUE;

	if (pDevices == NULL)
	{
		return FALSE;
	}

	POS pos = pDevices->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pDevice = (CDataGroup *)pDevices->GetNext(pos);
		//插入委托任务测试记录表
		CIot_TypeTaskTest* pTypeTaskTest = DB_InsertTypeTaskTest(strUserName, strItemsSN, pDevice);

		if (pTypeTaskTest == NULL)
		{
			bRet = FALSE;
			continue;
		}

		//插入任务测试记录子项目表
		if ( ! DB_InsertTypeTaskTest_Item(strHumidity, strTempreture, pTypeTaskTest, pListItems))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

CIot_TypeTaskTest* CSttSmartTestMqtt::DB_InsertTypeTaskTest(const CString &strUserName, const CString &strItemsSN, CDataGroup *pDevice)
{
	if (pDevice == NULL)
	{
		return NULL;
	}

	BOOL bRet = TRUE;
	CString strDeviceSN, strTaskSN;
	pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pDevice->GetDataValue(XPARA_ID_TaskSN, strTaskSN);

	CIot_Bench oBench;
	bRet = oBench.QueryBenchBySN(g_pTheMySqlApp, m_strBenchSN);

	if (!bRet)
	{
		return FALSE;
	}

	CIot_TypeTaskTest* pNew = new CIot_TypeTaskTest();
	pNew->m_strId_User = strUserName;
	pNew->m_strSn_Items = strItemsSN;
	pNew->m_nIndex_Task = CString_To_long(strTaskSN);
	pNew->m_strSn_Sample_Dev = strDeviceSN;
	pNew->m_nIndex_Bench = oBench.m_nIndex_Bench;

	bRet = pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);

	if (!bRet)
	{
		delete pNew;
		return NULL;
	}

	return pNew;
}

BOOL CSttSmartTestMqtt::DB_InsertTypeTaskTest_Item(const CString &strHumidity, const CString &strTempreture, CIot_TypeTaskTest* pTypeTaskTest, CExBaseList *pListItems)
{
	if (pTypeTaskTest == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pListItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CIot_TypeTaskTestItem *pNew = NULL;

	while (pos != NULL)
	{
		pObj = pListItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{
			pNew = new CIot_TypeTaskTestItem();
			pNew->m_strName = pObj->m_strName;   //暂时不处理路径
			pNew->m_strID = pObj->m_strID;
			pNew->m_strType_Item = GetItemType(nClassID);
			pNew->m_strSn_Items = pTypeTaskTest->m_strSn_Items;
			pNew->m_nIndex_Task = pTypeTaskTest->m_nIndex_Task;
			pNew->m_nIndex_Test = pTypeTaskTest->m_nIndex_Test;
			pNew->m_strHumidity = strHumidity;
			pNew->m_strTempreture = strTempreture;

			if (! pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("任务记录子项目【%s】，写入数据库失败！"), pObj->m_strName);
				bRet = FALSE;
			}
			
			delete pNew;
			pNew = NULL;
		}

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItems = (CItems *)pObj;

			if (! DB_InsertTypeTaskTest_Item(strHumidity, strTempreture, pTypeTaskTest, pItems))
			{
				bRet = FALSE;
			}
		}

		if (nClassID == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest *)pObj;

			//电气量项目下有子项目，递归调用
			if (! DB_InsertTypeTaskTest_Item(strHumidity, strTempreture, pTypeTaskTest, pMacroTest))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

BOOL CSttSmartTestMqtt::DB_InsertTypeTask_TestApps(CSttAtsCmd *pAtsCmd)
{
	BOOL bRet = TRUE;

	if (pAtsCmd == NULL)
	{
		return FALSE;
	}

	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	CDataGroup *pTestApps = (CDataGroup *)pParas->FindByID(XPARA_ID_test_apps);

	POS posDev = pDevices->GetHeadPosition();
	CString strTaskSN, strDeviceSN, strTestAppSN;

	while (posDev != NULL)
	{
		strTaskSN.Empty();
		strDeviceSN.Empty();
		CDataGroup *pDevice = (CDataGroup *)pDevices->GetNext(posDev);
		pDevice->GetDataValue(XPARA_ID_TaskSN, strTaskSN);
		pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);   //样品设备序列号

		POS posApp = pTestApps->GetHeadPosition();

		while (posApp != NULL)
		{
			strTestAppSN.Empty();
			CDataGroup *pTestApp = (CDataGroup *)pTestApps->GetNext(posApp);
			pTestApp->GetDataValue(STT_CMD_PARA_DeviceSN, strTestAppSN);   //仪器仪表编号

			CIot_TypeTaskTestApps oTaskTestApps;
			BOOL bRslt = oTaskTestApps.QueryTestApps(g_pTheMySqlApp, strTestAppSN, strDeviceSN, CString_To_long(strTaskSN));

			if (bRslt)
			{
				//说明同样的样品，用同样的测试仪，测试过多次
				continue;
			}

			CIot_TestApp oTestApp;
			bRslt = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strTestAppSN);

			if ( ! bRslt)
			{
				bRet = FALSE;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("仪器仪表总表中，找不到对应的测试仪【%s】"), strTestAppSN);
				continue;
			}

			oTaskTestApps.m_nIndex_Task = CString_To_long(strTaskSN);
			oTaskTestApps.m_nIndex_Testapp = oTestApp.m_nIndex_Testapp;
			oTaskTestApps.m_strSn_Sample_Dev = strDeviceSN;
			oTaskTestApps.m_strSn_Testapp = strTestAppSN;
			oTaskTestApps.m_strName_Testapp = strTestAppSN;  //仪器仪表总表中，没有name字段。暂时用编号处理  待处理

			bRslt = oTaskTestApps.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);

			if (!bRslt)
			{
				bRet = FALSE;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("任务-仪器仪表写入失败【任务ID=%s；仪器编号=%s】"), strTaskSN, strTestAppSN);
			}
		}
	}

	return bRet;
}

BOOL CSttSmartTestMqtt::Ats_CreateTest_StartSmartTest(CSttAtsCmd *pAtsCmd)
{
	if (pAtsCmd == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atscmd\\CreateTest.atscmd");

	SYSTEMTIME oLocalTime;
	::GetLocalTime(&oLocalTime);
	CString strAppend;
	strAppend.Format(_T("%4d_%2d_%2d(%2d_%2d_%2d)_"), oLocalTime.wYear, oLocalTime.wMonth, oLocalTime.wDay
		, oLocalTime.wHour, oLocalTime.wMinute, oLocalTime.wSecond);
	
	strFile = strAppend + strFile;
	bRet = pAtsCmd->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		return FALSE;
	}

	//待处理。拉起自动测试进程（SmartTest.exe）

	return bRet;
}