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

//������վ��MQTTָ���ϳɴ�������������Ҫ����Ϣ��������ļ�����ͨ�������в���������SmartTest
/*
ѡ����Щ����С���Ҫ�Զ����Է���ȥ��ѯ���ݿ��iot_type_task_test_item_gen��ͬʱ��Ҫ���ݶ�̬���ɵ���Ŀ��ά����iot_type_task_test_item
��������ʱ���ȸ������õĲ�����Ŀ����ģ���н������ɡ����ɺ󱣴�ģ�壬Ȼ�󴴽����ԡ�
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

	//д��������Լ�¼�����Լ�¼�����
	bRet = DB_InsertTypeTaskTest(pAtsCmd, pListItems);
	delete pListItems;
	pListItems = NULL;

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -3;
	}

	//д������-�����Ǳ� ��
	bRet = DB_InsertTypeTask_TestApps(pAtsCmd);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -4;
	}

	//����������CreateTest.atscmd�������Զ����ԣ����Զ���ʼ����
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
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
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
  		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
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
  		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
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
  		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
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
	//���ر���װ����ص��ļ�
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

//����ģ���ļ��͹�Լģ��
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

		//����ģ���ļ�
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
				//ģ���ļ��Ǳ�����������ڣ�ֱ�ӷ�������ʧ��
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����豸ģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
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

		//���ع�Լģ���ļ�
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
				//��Լģ���ļ����Ǳ�����������ڣ�����������
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
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����豸��Լģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
			}
		}
	}

	return bReturn;
}

//���ز��Թ����ļ�
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("���ز����ڲ���ģ���ļ���%s��"), strFile);
		return FALSE;
	}

	//���ݲ���̨SN����ѯ����̨����
	CIot_Bench oBench;
	bRet = oBench.QueryBenchBySN(g_pTheMySqlApp, m_strBenchSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�Ҳ�������̨��%s��"), m_strBenchSN);
		return FALSE;
	}

	//���ݴ���SN�����Ҵ�������
	CIot_Items oItems;
	bRet = oItems.QueryItemsBySN(g_pTheMySqlApp, strItemsSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�Ҳ������Դ��%s��"), strItemsSN);
		return FALSE;
	}

	//���ݴ���Index�Ͳ���̨Index�����Ҳ��Լ�¼����Ŀ���ɹ����
	CIot_TypeTaskTestItemGens oItemGens;
	bRet = oItemGens.QueryItemGens(g_pTheMySqlApp, oItems.m_nIndex_Items, oBench.m_nIndex_Bench);

	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("���Ҳ��Լ�¼�������ɹ���ʧ�ܣ�"));
		return FALSE;
	}

	bRet = GenerateTemplate(strFile, &oItemGens, pListItems);

	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("�����������ɹ������ɲ�����Ŀʧ�ܣ�"));
		return FALSE;
	}

	return bRet;
}

//strGbxmlFile�����ļ����ľ���·��
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��ģ���ļ�ʧ�ܡ�%s��"), strGbxmlFile);
		return FALSE;
	}

	//CDevice��һ����Ϊ���Դ�����࣬����ֻ��һ����Ŀ���ࣻ
	//���Դ��������һ����Ϊ����С�����;
	CDevice *pDevice = oGuideBook.GetDevice();

	if (pDevice == NULL)
	{
		return FALSE;
	}

	//���Դ���
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
			//˵������������������Ҫ���Ե�
			//�˴��ǽ�nSelect����Ϊ0������ֱ��ɾ�������
			//������
			pChild->SetItemState(1, 1, 0, TRUE, TRUE, TRUE);
		}
		else
		{
			pChild->SetItemState(1, 1, pItemGen->m_nSelect, TRUE, TRUE, TRUE);

			if (pItemGen->m_nSelect == 1)
			{
				//��Ҫ���Ե�������в����ĸ��£���Ϊ��վ���ܽ��й��༭
				GenerateTemplate_UpdateParas(pChild, pItemGen);
				//ɾ���Ѿ�ƥ������ɹ�����ʣ�����δƥ��ģ�������Ҫ��ӵ�ģ���е��Զ����
				pItemGens->Delete(pItemGen);
			}
		}
	}

	//ȡ��һ������ķ���ڵ㣬��Ϊ��̬������Ŀ��ģ�塣
	CItems *pTemplateChild = (CItems *)pItems->FindByClassID(GBCLASSID_ITEMS); 
	pos = pItemGens->GetHeadPosition();

	while (pos != NULL)
	{
		CIot_TypeTaskTestItemGen *pItemGen = (CIot_TypeTaskTestItemGen *)pItemGens->GetNext(pos);
		CItems *pNew = (CItems *)pTemplateChild->CloneEx(TRUE, TRUE);
		GenerateTemplate_UpdateParas(pNew, pItemGen);
		pItems->AddNewChild(pNew, TRUE);
	}

	pListItems = pItems;  //���ز��Դ���
	bRet = oGuideBook.SaveXMLFile(strGbxmlFile);
	pDevice->Remove(pItems);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ģ���ļ�ʧ�ܡ�%s��"), strGbxmlFile);
		return FALSE;
	}

	return bRet;
}

BOOL CSttSmartTestMqtt::GenerateTemplate_UpdateParas(CItems *pChildItems, CIot_TypeTaskTestItemGen* pItemGen)
{
	BOOL bRet = TRUE;
	pChildItems->m_strName = pItemGen->m_strName;

	//Ĭ�ϲ���С������У���һ����������Ŀ���������������Ǳ�Ĳ�����
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
		//����ί��������Լ�¼��
		CIot_TypeTaskTest* pTypeTaskTest = DB_InsertTypeTaskTest(strUserName, strItemsSN, pDevice);

		if (pTypeTaskTest == NULL)
		{
			bRet = FALSE;
			continue;
		}

		//����������Լ�¼����Ŀ��
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
			pNew->m_strName = pObj->m_strName;   //��ʱ������·��
			pNew->m_strID = pObj->m_strID;
			pNew->m_strType_Item = GetItemType(nClassID);
			pNew->m_strSn_Items = pTypeTaskTest->m_strSn_Items;
			pNew->m_nIndex_Task = pTypeTaskTest->m_nIndex_Task;
			pNew->m_nIndex_Test = pTypeTaskTest->m_nIndex_Test;
			pNew->m_strHumidity = strHumidity;
			pNew->m_strTempreture = strTempreture;

			if (! pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����¼����Ŀ��%s����д�����ݿ�ʧ�ܣ�"), pObj->m_strName);
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

			//��������Ŀ��������Ŀ���ݹ����
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
		pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);   //��Ʒ�豸���к�

		POS posApp = pTestApps->GetHeadPosition();

		while (posApp != NULL)
		{
			strTestAppSN.Empty();
			CDataGroup *pTestApp = (CDataGroup *)pTestApps->GetNext(posApp);
			pTestApp->GetDataValue(STT_CMD_PARA_DeviceSN, strTestAppSN);   //�����Ǳ���

			CIot_TypeTaskTestApps oTaskTestApps;
			BOOL bRslt = oTaskTestApps.QueryTestApps(g_pTheMySqlApp, strTestAppSN, strDeviceSN, CString_To_long(strTaskSN));

			if (bRslt)
			{
				//˵��ͬ������Ʒ����ͬ���Ĳ����ǣ����Թ����
				continue;
			}

			CIot_TestApp oTestApp;
			bRslt = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strTestAppSN);

			if ( ! bRslt)
			{
				bRet = FALSE;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����Ǳ��ܱ��У��Ҳ�����Ӧ�Ĳ����ǡ�%s��"), strTestAppSN);
				continue;
			}

			oTaskTestApps.m_nIndex_Task = CString_To_long(strTaskSN);
			oTaskTestApps.m_nIndex_Testapp = oTestApp.m_nIndex_Testapp;
			oTaskTestApps.m_strSn_Sample_Dev = strDeviceSN;
			oTaskTestApps.m_strSn_Testapp = strTestAppSN;
			oTaskTestApps.m_strName_Testapp = strTestAppSN;  //�����Ǳ��ܱ��У�û��name�ֶΡ���ʱ�ñ�Ŵ���  ������

			bRslt = oTaskTestApps.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);

			if (!bRslt)
			{
				bRet = FALSE;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����-�����Ǳ�д��ʧ�ܡ�����ID=%s���������=%s��"), strTaskSN, strTestAppSN);
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

	//�����������Զ����Խ��̣�SmartTest.exe��

	return bRet;
}