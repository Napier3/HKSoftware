#include "StdAfx.h"
#include "AtsSvr_TemplateServiceBase.h"
#include "../../../../Module/XFileHttpClient/XFileHttpClient.h"

/*
<sys-state name="" id="QueryItems" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="1|2|3|4" unit=""/>
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data name="" id="ItemPath" data-type="" value="Device$ManulTest"/>
		<items name="" id="" tkid="65535" select="1">
			������������
			<safety name="������ʾ" id="Safety" tkid="65535" select="0">
				<msg type="1"><![CDATA[					����ʾ�˹����в�������Ϣ��					]]></msg>
				<datas name="" id="">
					<data name="���վ����" id="Test1" data-type="" unit="" value="220KV����վ" format="" remark="" default="220KV����վ" reserved="1" time="0"/>
					<data name="��������" id="Test2" data-type="" unit="" value="1������" format="" remark="" default="1������" reserved="1" time="0"/>
					<data name="���ر��" id="Test3" data-type="" unit="" value="110" format="" remark="" default="110" reserved="1" time="0"/>
					<data name="data1" id="data1" data-type="combobox" unit="" value="eligible" format="Eligible" remark="" default="eligible" reserved="1" time="0" />
					<data name="data2" id="data2" data-type="combobox" unit="" value="right" format="Right" remark="" default="" reserved="1" time="0" />
				</datas>
			</safety>
������������
		</items>
		<data-types name="" id="">
			<data-type name="�ϸ�/���ϸ�" id="Eligible">
				<value name="�ϸ�" id="eligible" index="1"/>
				<value name="���ϸ�" id="inlegible" index="2"/>
			</data-type>
			<data-type name="��ȷ/����ȷ" id="Right">
				<value name="��ȷ" id="right" index="1"/>
				<value name="����ȷ" id="wrong" index="2"/>
			</data-type>
			������������
		</data-types>
	</paras>
</sys-state>
*/
///////////////////////////////////////////////////////////////////////////
//CAtsSvr_TemplateItemsObj
CAtsSvr_TemplateItemsObj::CAtsSvr_TemplateItemsObj()
{
	m_pItems = NULL;
	m_pDataTypes = NULL;
}

CAtsSvr_TemplateItemsObj::~CAtsSvr_TemplateItemsObj()
{
	if (m_pItems != NULL)
	{
		delete m_pItems;
	}

	if (m_pDataTypes != NULL)
	{
		delete m_pDataTypes;
	}
}

//////////////////////////////////////////////////////////////////////////
//CAtsSvr_TemplateObject
CAtsSvr_TemplateObject::CAtsSvr_TemplateObject()
{
	m_pGuideBook = NULL;
}

CAtsSvr_TemplateObject::~CAtsSvr_TemplateObject()
{
	if (m_pGuideBook != NULL)
	{
		delete m_pGuideBook;
		m_pGuideBook = NULL;
	}
}

CAtsSvr_TemplateItemsObj* CAtsSvr_TemplateObject::QueryItems(const CString &strGbFile, const CString &strGbFile_s, const CString &strItemsPath)
{
	CAtsSvr_TemplateItemsObj *pFind = (CAtsSvr_TemplateItemsObj*)FindByID(strItemsPath);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CAtsSvr_TemplateItemsObj();
	pFind->m_strID = strItemsPath;

	if (m_pGuideBook == NULL)
	{
		m_pGuideBook = OpenGuideBook(strGbFile, strGbFile_s);
	}

	if (m_pGuideBook == NULL)
	{
		return NULL;
	}
	
	if (! QueryItems(m_pGuideBook, strItemsPath, pFind))
	{
		delete pFind;
		return NULL;
	}

	AddNewChild(pFind);
	
	return pFind;
}

CGuideBook* CAtsSvr_TemplateObject::OpenGuideBook(const CString &strGbFile, const CString &strGbFile_s)
{
	CString strPath;
	strPath = atssys_GetReportTemplatePath();
	strPath += strGbFile;

	if (!::IsFileExist(strPath))
	{
		return NULL;
	}

	CGuideBook *pGuideBook = new CGuideBook();
	pGuideBook->Open(strPath);
	return pGuideBook;
}

BOOL CAtsSvr_TemplateObject::QueryItems(CGuideBook *pGuideBook, const CString &strItemsPath, CAtsSvr_TemplateItemsObj *pItems)
{
	CGbItemBase *pFind =  (CGbItemBase*)Gb_GetItem(pGuideBook, strItemsPath);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->GetClassID() != GBCLASSID_ITEMS)
	{
		return FALSE;
	}

	//2023-9-11  ��� ����ʱ��ֻ������Ҫ��Ϣ�����ڸ�MES���������ⲿϵͳ��ȥ��script��report-map�ȶ���
	g_nGbCopyItemForMes = 1;
	pItems->m_pItems = (CItems*)pFind->Clone();
	g_nGbCopyItemForMes = 0;

	pItems->m_pDataTypes = new CDataTypes();
	QueryItems_DataTypes(pItems->m_pItems, pItems->m_pDataTypes);

	return TRUE;
}

void CAtsSvr_TemplateObject::QueryItems_DataTypes(CItems *pItems, CDataTypes *pDataTypes)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pItems->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_SAFETY)
		{
			QueryItems_DataTypes((CSafety*)p, pDataTypes);
		}
		else if (p->GetClassID() == GBCLASSID_ITEMS)
		{
			QueryItems_DataTypes((CItems*)p, pDataTypes);
		}
	}
}

void CAtsSvr_TemplateObject::QueryItems_DataTypes(CSafety *pSafety, CDataTypes *pDestDataTypes)
{
	CShortDatas *pDatas = pSafety->m_pDatas;
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;
	CDataTypes *pComboTypes = CGbDataTypeMngr::g_pGbDataTypeMngr->GetSafetyComboDataTypes();
	CDataType *pDataType = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);

		if (pData->m_strDataTypeID == g_strGbDataTypeCombobox)
		{
			pDataType = (CDataType *)pComboTypes->FindByID(pData->m_strFormat);

			if (pDataType != NULL)
			{
				if (pDestDataTypes->FindByID(pDataType->m_strID) == NULL)
				{
					pDestDataTypes->AddNewChild((CDataType*)pDataType->Clone());
				}
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//CAtsSvr_TemplateServiceBase
CAtsSvr_TemplateServiceBase *g_pAtsSvr_TemplateService = NULL;

CAtsSvr_TemplateServiceBase::CAtsSvr_TemplateServiceBase(void)
{
	g_pAtsSvr_TemplateService = this;
}

CAtsSvr_TemplateServiceBase::~CAtsSvr_TemplateServiceBase(void)
{

}


CAtsSvr_TemplateItemsObj* CAtsSvr_TemplateServiceBase::QueryItems(const CString &strGbFile, const CString &strGbFile_s, const CString &strItemsPath)
{
	CAtsSvr_TemplateObject *pFind = (CAtsSvr_TemplateObject*)FindByID(strGbFile);

	if (pFind == NULL)
	{
		pFind = new CAtsSvr_TemplateObject();
		pFind->m_strID = strGbFile;
		AddNewChild(pFind);
	}

	return pFind->QueryItems(strGbFile, strGbFile_s, strItemsPath);
}

#if 0
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	long nRet = -1;
	char* pszCmdID = NULL;
	CString_to_char(pAtsCmd->m_strID, &pszCmdID);

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	oSysState.m_strToSN = pAtsCmd->m_strFromSN;

	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_UploadTemplate)
	{
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
		nRet = Process_Cmd_Ats_UploadTemplate(pAtsCmd);
	}
	else if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_ImportTaskInfo)
	{
		//2023-6-6���������µ��޸ģ�����������Ϣ������վ����д�⡣�Զ����Է��񲻴����ָ?
		delete pszCmdID;
		return 0;
		//pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
		//return Process_Cmd_Ats_ImportTaskInfo(pAtsCmd);
	}
	else if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_ImportSampleInfo)
	{
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
		return Process_Cmd_Ats_ImportSampleInfo(pAtsCmd);
	}
	else if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_ExportReport)
	{
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
		return Process_Cmd_Ats_ExportReport(pAtsCmd, pSttProtocol);
	}
	else if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_CreateTask)
	{
		//��ʱ���ø�ָ��
		delete pszCmdID;
		return 0;
	}
	else
	{
		delete pszCmdID;
		return 0;
	}

	if (nRet == 0)
	{
		//�ɹ�
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
	}
	else
	{
		//ʧ��
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
	}

	delete pszCmdID;
	return nRet;
}

//cxa��������Ҫ���Ӵ���ExportReport�¼�
long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState*)oSysStateDrv.GetXObjectRef();

	if (pSysState->m_strID == SYS_STATE_EVENT_OnTestAppEvent)
	{
		return Process_Cmd_SysState_TestAppEvent(pSysState);   //�����ǵ��¼�
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnEngineEvent)  
	{
		return Process_Cmd_SysState_EngineEvent(pSysState);   //�豸���¼�
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnRTDATA)
	{
		return Process_Cmd_SysState_RTDATA(pSysState);   //�豸|�����ǵ�ʵʱ����
	}

	return 0;
}

/*
����ģ�壺
1������ģ���ļ���
2�����ؽ���ģ���ļ����������еĴ��д���ݿ��iot_template_items����
3��ÿһ���������һ��Сģ�塰��ģ����$������.gbxml�������浽����Template·���£�
4������ÿ�������С�д���ݿ��iot_template_item����
*/
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_UploadTemplate(CSttAtsCmd *pAtsCmd)
{
	//strFileDownLoad�����غ󷵻صı���ȫ·�������ļ�����
	CString strFileDownLoad, strFileName;
	BOOL bRet = DownLoadFile_Template(pAtsCmd, strFileDownLoad);

	if (!bRet)
	{
		return -1;
	}

	//����ģ���ļ��������������д���
	CGuideBook *pGuideBook = new CGuideBook();
	CExBaseList oListItems;
	bRet = OpenGbxmlFile(strFileDownLoad, &oListItems, pGuideBook);

	if (!bRet)
	{
		oListItems.RemoveAll();
		delete pGuideBook;
		return -2;
	}

	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strFileName);

	//�������д��Ϊÿһ�������һ��gbxmlСģ��
	bRet = SaveGbxmlFile_Items(strFileName, pGuideBook, &oListItems);

	if (!bRet)
	{
		oListItems.RemoveAll();
		delete pGuideBook;
		return -3;
	}

	//���ݴ�����Ϣ��д�����ݿ⣺ģ����Ŀ�����+ģ����Ŀ���������
	bRet = DB_InsertTemplateItems(strFileName, &oListItems);

	if (!bRet)
	{
		oListItems.RemoveAll();
		delete pGuideBook;
		return -4;
	}

	//��Ŀ�����ܱ�
	bRet = DB_Insert_IotItems(&oListItems);

	if (!bRet)
	{
		oListItems.RemoveAll();
		delete pGuideBook;
		return -5;
	}

	//����������Ҫ�����ļ���Ϊ��ģ���ļ���$gen.xml����xml�ļ�
	//��Ҫ��Iot_Template���������ֶΡ�
	//�������ļ���ά����iot_item_gen
	//20230609������ȷ��Ҫ��

	oListItems.RemoveAll();
	delete pGuideBook;
	return 0;
}

/*
<!--����������Ϣ����������Ϣ�ļ���Word�������ļ����н�������ȡ�������Ϣ�󣬷������½ṹ-->
<group id="TaskInfo" name="������Ϣ">
	<group id="BasicInfo" name="���������Ϣ">
		<data id="TestType" name="��������" value="��ʽ����"/>
		<data id="SampleSN" name="��Ʒ���" value="GJK20220207"/>
		<data id="SampleModel" name="��Ʒ�ͺ�" value="CQSJ"/>
		<data id="SampleName" name="��Ʒ����" value="�����·���װ��"/>
		<data id="ClientName" name="ί�е�λ����" value="�Ƽ����޹�˾"/>
		<data id="ClientAddress" name="ί�е�λ��ַ" value="8��A��"/>
		<data id="ManufactorName" name="���쵥λ����" value="�Ƽ����޹�˾"/>
		<data id="ManufactorAddress" name="���쵥λ��ַ" value="8��A��"/>
		<!--�������У������Ϣȱʧʱ��value�������-->
	</group>
	<group id="InspectionBases" name="�����������">
		<data id="InspectionBasis1" name="��������1" value="Q/GDW 12021-2019�����豸�������ڵ��豸��������Э��"/>
		<data id="Name" name="��������" value="PAL/BZ 12020-2020�����豸������΢����������ͨ��Э��"/>
		<data id="Name" name="��������" value="PAL/BZ 12021-2020�����豸�������ڵ��豸��������Э��"/>
		<!--��߶��ٸ��������ݣ����ж��ٸ�data-->
	</group>
</group>
*/
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_ImportTaskInfo(CSttAtsCmd *pAtsCmd)
{
	//strFileDownLoad�����غ󷵻صı���ȫ·�������ļ�����
	CString strFileDownLoad, strName_User;
	BOOL bRet = DownLoadFile_TaskInfo(pAtsCmd, strFileDownLoad);

	if (!bRet)
	{
		return -1;
	}

	//�����������ļ�������������Ϣgroup
	CDataGroup *pTaskInfo = NULL;
	pTaskInfo = ParseFile_TaskInfo(strFileDownLoad);

	if (pTaskInfo == NULL)
	{
		return -2;
	}

	//���������Ϣ��������Ϊ��
	CDataGroup *pBasicInfo = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_BASICINFO);

	if (pBasicInfo == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("������Ϣ������ȱ�����������Ϣ"));
		return -3;
	}

	CString strTaskFileName, strTaskFile_s;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE, strTaskFileName);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE_S, strTaskFile_s);

	CString strTaskSN;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TaskSN, strTaskSN);
	CIot_TypeTask* pIotTypeTask = NULL;

	long nUser_ID = CString_To_long(pAtsCmd->m_strFromSN);  //��Ҫ�������л�ȡ

	if (!strTaskSN.IsEmpty())
	{
		//������Ϣ������ε��롣
		//���·���ָ���У�TaskSN��Ϊ��ʱ����˵���Ƕ��ε��롣��Ҫ���Ѵ�����ί���������Ϣ���и���
		pIotTypeTask = DB_UpdateTypeTask(CString_To_long(strTaskSN), pBasicInfo, strTaskFileName, strTaskFile_s);
	}
	else
	{
		//���û����У���ѯ�û�����
		bRet = QueryUserByUserID(nUser_ID, strName_User);

		if (!bRet)
		{
			return -4;
		}

		//д���ݿ��iot_type_task���½�ί������
		pIotTypeTask = DB_InsertTypeTask(pBasicInfo, strTaskFileName, strTaskFile_s, strName_User);
	}

	if (pIotTypeTask == NULL)
	{
		return -5;
	}

	//����������Ϣ������Ϊ�ա���Ϊ��ʱ�����سɹ�
	CDataGroup *pInspectionBases = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_InspectionBases);

	//д���ݿ��iot_type_task_standard
	bRet = DB_InsertTypeTask_Standard(pIotTypeTask->m_nIndex_Task, pInspectionBases);
	
	if (!bRet)
	{
		return -6;
	}

	return 0;
}

/*
//2023-6-6
//�������µ���ƣ��Զ����Է��񽫲��ٽ�����Ʒ��Ϣ�ļ�
//��վ�����ļ��󣬽���ص���Ϣд�����ݿ���Զ����Է�������ݿ������ȡ������͵�����������ģ���ļ�


<!--������Ʒ�б�����Ʒ��Ϣ�ļ���Excel�ļ����н�������ȡ��Ʒ����Ϣ�󣬷������½ṹ-->
<group id="SampleInfo" name="��Ʒ��Ϣ">
	<group id="SampleDevices" name="��Ʒ�б�">
		<group id="SampleDevice1" name="��Ʒ1">
			<data id="DeviceSN" name="�豸���к�" value="CQSJ2022110010"/>
			<data id="SampleSN" name="��Ʒ���" value="GJK20220207-1"/>
			<!--�����Ʒ��Ϣ�ļ���û�и���Ϣ���򷵻صĽṹ�в�Ҫ������SmapleSN���ֶ�-->
		</group>
		<group id="SampleDevice2" name="��Ʒ2">
			<data id="DeviceSN" name="�豸���к�" value="CQSJ2022110011"/>
			<data id="SampleSN" name="��Ʒ���" value="GJK20220207-2"/>
		</group>
		<!--��߶��ٸ���Ʒ�豸�����ж��ٸ�group-->
	</group>
	<group id="RatedParameter" name="�����">
		<data id="Power" name="����" value="100" data-type="float" unit="W"/>
		<data id="Weight" name="����" value="1.23" data-type="float" unit="kg"/>
		<!--��߶��ٸ�����������ж��ٸ�data���������id��name��value��data-type��unit���ԣ�����excel�ļ��������-->
	</group>
	<group id="DevDvm" name="������">
		<data id="RealTimeWindSpeed" name="ʵʱ����" value="23.2" data-type="unsigned int" unit="m/s"/>
		<data id="RealTimeWindDir" name="ʵʱ����" value="1.23" data-type="unsigned int" unit="��"/>
		<!--��߶��ٸ������������ж��ٸ�data���������id��name��value��data-type��unit���ԣ�����excel�ļ��������-->
	</group>
</group>
*/
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_ImportSampleInfo(CSttAtsCmd *pAtsCmd)
{
	/*
	//strFileDownLoad�����غ󷵻صı���ȫ·�������ļ�����
	CString strFileDownLoad;
	BOOL bRet = DownLoadFile_SampleInfo(pAtsCmd, strFileDownLoad);

	if (!bRet)
	{
		return -1;
	}

	//������Ʒ�б��ļ���������Ʒ��Ϣgroup
	CDataGroup *pSampleInfo = NULL;
	pSampleInfo = ParseFile_SampleInfo(strFileDownLoad);

	if (pSampleInfo == NULL)
	{
		return -2;
	}

	CDataGroup *pSampleDevices = (CDataGroup *)pSampleInfo->FindByID(XPARA_ID_SampleDevices);
	CString strTaskSN;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TaskSN, strTaskSN);

	if (pSampleDevices == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("��Ʒ��Ϣ������ȱ����Ʒ�б���Ϣ"));
		//��ȱ����Ʒ�б���Ϣʱ�������Ƕ����ϴ���������Ʒ�Ķ����
		//��һ���ϴ�ʱ������û�ж��������Ҫ�����ϴ�
	}
	else
	{
		//д���ݿ⣺������Ʒ��iot_type_task_dev
		bRet = DB_InsertTypeTask_Devs(CString_To_long(strTaskSN), pSampleDevices);

		if (!bRet)
		{
			return -3;
		}
	}

	//�����д�����ݿ�
	CDataGroup *pRatedParameter = (CDataGroup *)pSampleInfo->FindByID(XPARA_ID_RatedParameter);
	bRet = DB_InsertTypeTask_RatedParameter(CString_To_long(strTaskSN), pRatedParameter);

	if (!bRet)
	{
		return -4;
	}

	//������д�����ݿ�
	CDataGroup *pDevDvm = (CDataGroup *)pSampleInfo->FindByID(XPARA_ID_DevDvm);
	bRet = DB_InsertTypeTask_DevDvm(CString_To_long(strTaskSN), pDevDvm);

	if (!bRet)
	{
		return -5;
	}

	//����ģ���ļ�
	CString strDvmFile = GenerateDevDvm(strTaskSN, pRatedParameter, pDevDvm);  //�����ļ���
	CString strFile_s;

	//ͨ��HTTP�ϴ����ɵ�ģ���ļ�
	bRet = UploadFile_DvmDevice(strDvmFile, strFile_s);

	if (!bRet)
	{
		return -6;
	}

	bRet = DB_InsertDeviceModel(strDvmFile, strFile_s);

	if (!bRet)
	{
		return -7;
	}
	*/

	CString strTaskSN;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TaskSN, strTaskSN);
	long nTaskIndex = CString_To_long(strTaskSN);

	//��ѯ����������
	CIot_TypeTaskDevParases oParases;
	BOOL bRet = oParases.QueryTypeTaskDevParases(g_pTheMySqlApp, nTaskIndex);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��ѯ����������ʧ�ܡ�%s��"), strTaskSN);
		return -1;
	}

	//��ѯ�����������
	CIot_TypeTaskDevModels oModels;
	bRet = oModels.QueryTypeTaskDevModels(g_pTheMySqlApp, nTaskIndex);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��ѯ�����������ʧ�ܡ�%s��"), strTaskSN);
		return -2;
	}

	//����ģ���ļ�
	CString strDvmFile = GenerateDevDvm(strTaskSN, &oParases, &oModels);  //�����ļ���
	CString strFile_s;

	//ͨ��HTTP�ϴ����ɵ�ģ���ļ�
	bRet = UploadFile_DvmDevice(strDvmFile, strFile_s);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ģ���ļ��ϴ�ʧ�ܡ�%s   %s��"), strTaskSN, strDvmFile);
		return -3;
	}

	bRet = DB_InsertDeviceModel(strDvmFile, strFile_s);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ģ���ļ�д���ݿ�ʧ�ܡ�%s   %s��"), strTaskSN, strDvmFile);
		return -4;
	}

	return 0;
}

/*
�������棬���ɲ��Լ�¼�����������ί�����񵼳����档
���Թ��������������ID�����Ҹ�������������в��Լ�¼����������Ϊ���ձ��������������Լ�¼�ı��档
����ʹ�õ�ģ�壺iot_type_task��ġ�name_template����ģ���ļ���Ψһ����
�ڵ��������ʱ����Ҫ���¼���ģ�塣
*/
//��������
//cxa�������������񣬲�ѯ������صļ�¼��ģ�塢�����ˡ��������ݵ���Ϣ��Ӧ������������Ҫ��������Ϣ����ƴ�ӳ�xml�ĵ����ĵ��ṹ����������ɱ��غ�����SmartTest���е���
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_ExportReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	BOOL bRet = TRUE;
	CString strTaskSN, strSampleSN, strTemplateName;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TaskSN, strTaskSN);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_SampleSN, strSampleSN);

	//��ѯί����������������������ձ���Ĳ��Լ�¼
	CIot_TypeTaskTests oTaskTests;
	bRet = oTaskTests.QueryAllTaskTests_FinalRpt(g_pTheMySqlApp, CString_To_long(strTaskSN));

	if (!bRet || oTaskTests.GetCount() == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��ѯ������Լ�¼ʧ�ܣ���%s��"), strTaskSN);
		return -1;
	}

	//��ѯ�������ȡ�����õĲ���ģ��
	CIot_TypeTask oTypeTask;
	bRet = oTypeTask.QueryTypeTaskByIndex(g_pTheMySqlApp, CString_To_long(strTaskSN));

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ѯί�������ʧ�ܣ�[%s]"), strTaskSN);
		return -2;
	}

	strTemplateName = oTypeTask.m_strName_Template;  //ģ���ļ���
	CString strTemplateFilePath;
	bRet = DownLoadFile_Template_RptFile(strTemplateName, strTemplateFilePath);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���ر���ģ��ʧ�ܣ�[%s]"), strTemplateName);
		return -3;
	}

	//�Ƚ�word����ģ�壬������WorkSpace·����
	CString strDestFile;
	strDestFile = GetFileNameFromFilePath(strTemplateFilePath);
	strDestFile = ChangeFilePostfix(strDestFile, _T(""));  //ȥ����׺
	SYSTEMTIME oTime;
	::GetLocalTime(&oTime);
	//��Ŀ�걨���ļ�������ʱ��
	strDestFile.AppendFormat(_T("_(%4d%2d%2d_%2d%2d%2d).doc"), oTime.wYear, oTime.wMonth, oTime.wDay
		, oTime.wHour, oTime.wMinute, oTime.wSecond);
	CString strPath;
	strPath = _P_GetWorkspacePath(_T(""));
	strDestFile = strPath + strDestFile;

	if (!::X_CopyFile(strTemplateFilePath, strDestFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��������ģ���ļ���%s����WorkSpaceĿ¼ʧ�ܣ�"), strTemplateFilePath);
		return FALSE;
	}

	//������gbrpt-file��δ���
	//20230609��ί������û��gbrpt�ļ���ÿ����¼���ø��Ե�gbrpt�ļ�������word��word����ģ���Ǹ�ȫ��ģ�壩��
	bRet = Export_Report(pAtsCmd, pSttProtocol, strDestFile, &oTaskTests);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����%s����������ʧ�ܣ�"), strTaskSN);
		return -4;
	}

	//��������������ļ������ݡ������ˡ�����ˡ�У���˵���Ϣ

	//�����ɹ����ϴ�word���档
	CString strRptFile_s, strGbrptFile, strGbrptFile_s;
	bRet = UploadFile_RptFile(strDestFile, strRptFile_s);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����%s���ϴ������ļ���%s��ʧ�ܣ�"), strTaskSN, strDestFile);
		return -5;
	}

	//�����ɹ��󣬸���ί�������
	strDestFile = GetFileNameFromFilePath(strDestFile);
	oTypeTask.m_strDoc_File = strDestFile;
	oTypeTask.m_strDoc_File_S = strRptFile_s;
	//������
	//20230609���������û�и��ֶ�
	//oTypeTask.m_strGbrpt_File = strGbrptFile;
	//oTypeTask.m_strGbrpt_File_S = strGbrptFile_s;
	bRet = oTypeTask.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����%s���������ݿ�ʧ�ܣ�"), strTaskSN);
		return -6;
	}

	//����ExportFinish�¼�
	char* pszCmdID = NULL;
	CString_to_char(pAtsCmd->m_strID, &pszCmdID);
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_EventID, SYS_STATE_XEVENT_EVENTID_ExportFinish);
	pParasReturn->AddNewData(XPARA_ID_TaskSN, strTaskSN);
	pParasReturn->AddNewData(XPARA_ID_SampleSN, strSampleSN);
	pParasReturn->AddNewData(XPARA_ID_DOCFILE, strDestFile);
	pParasReturn->AddNewData(XPARA_ID_DOCRPTFILE_S, strRptFile_s);
	pParasReturn->AddNewData(XPARA_ID_GBXMLFILE, strGbrptFile);
	pParasReturn->AddNewData(XPARA_ID_GBXMLFILE_S, strGbrptFile_s);
	pSttProtocol->ReturnSysState_EVENT((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
	delete pszCmdID;

	return 0;
}

/*
<sys-state name="" id="TestAppEvent" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data id="EventID" data-type="string" value="TestBegin" unit=""/>
		<data id="DeviceSN" data-type="long" value="0" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>
*/
//�����ǵ��¼�����ʱֻ����
//1�������ɹ���ConnectSuccess
//2������ʧ�ܣ�ConnectFailed
//3������ͨѶ����ͬ����ʧ�ܣ���CommError
long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState_TestAppEvent(CSttSysState *pSysState)
{
	CString strDeviceSN, strEventID;
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pSysState->GetParasDataValueByID(SYS_STATE_XEVENT_EVENTID, strEventID);

	BOOL bRet = FALSE;
	CIot_TestApp oTestApp;
	bRet = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�Ҳ��������ǡ�%s��"), strDeviceSN);
		return -1;
	}

	if (strEventID == SYS_STATE_XEVENT_EVENTID_ConnectSuccess)
	{
		oTestApp.m_nConnect_State = DEV_CONNECT_STATE_ON;
		bRet = oTestApp.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else if (strEventID == SYS_STATE_XEVENT_EVENTID_ConnectFailed
		|| strEventID == SYS_STATE_XEVENT_EVENTID_CommError)
	{
		oTestApp.m_nConnect_State = DEV_CONNECT_STATE_OFF;
		bRet = oTestApp.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��֧�ֵĲ����ǲ����¼����͡�%s��"), strEventID);
		return 0;
	}

	if ( !bRet)
	{
		return -2;
	}

	return 0;
}

/*
<sys-state name="" id="EngineEvent" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data id="EventID" data-type="string" value="CommFinish" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>
*/
//�豸���¼�����ʱֻ����
//1�������ɹ���ConnectDeviceSuccessful
//2������ʧ�ܣ�ConnectDeviceFailed
//3��ͨѶ����ͬ����ʧ�ܣ���CommError
long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState_EngineEvent(CSttSysState *pSysState)
{
	CString strDeviceSN, strEventID;
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pSysState->GetParasDataValueByID(SYS_STATE_XEVENT_EVENTID, strEventID);
	BOOL bRet = FALSE;
	CIot_TypeTaskDev oDev;
	bRet = oDev.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�Ҳ�����Ʒ�豸��%s��"), strDeviceSN);
		return -1;
	}

	if (strEventID == SYS_STATE_XEVENT_EVENTID_ConnectDeviceSuccessful)
	{
		oDev.m_nConnect_State = DEV_CONNECT_STATE_ON;
		bRet = oDev.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else if (strEventID == SYS_STATE_XEVENT_EVENTID_ConnectDeviceFailed
		|| strEventID == SYS_STATE_XEVENT_EVENTID_CommError)
	{
		oDev.m_nConnect_State = DEV_CONNECT_STATE_OFF;
		bRet = oDev.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��֧�ֵ��豸�����¼����͡�%s��"), strEventID);
		return 0;
	}

	if ( !bRet)
	{
		return -2;
	}

	return 0;
}

/*
<sys-state name="" id="OnRTDATA" mater-host="" ret-type="RTDATA" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="װ�����к�|�����Ǳ���" id="DeviceSN" data-type="string" value="CQSJ2022110010"/>
		<data name="�Ƿ�澯" id="is_warning" data-type="long" value="0"/>
		<group name="" id="" data-type="" value="">
			<data name="�����¶�" id="Tempreture" data-type="float" value="25.3"/>
			<data name="����ʪ��" id="Humidity" data-type="float" value="50.1"/>
		</group>
	</paras>
</sys-state>
*/
//ʵʱ���ݣ��豸�Ͳ����ǹ���
long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState_RTDATA(CSttSysState *pSysState)
{
	CString strDeviceSN, strEventID;
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	BOOL bRet = FALSE;
	CIot_TestApp oTestApp;
	bRet = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (bRet)
	{
		return Process_Cmd_SysState_RTDATA_TestApp(pSysState, &oTestApp);
	}

	CIot_TypeTaskDev oDev;
	bRet = oDev.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (bRet)
	{
		return Process_Cmd_SysState_RTDATA_Dev(pSysState, &oDev);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�Ҳ�����Ʒ�豸�������Ǳ�%s��"), strDeviceSN);
	return -1;
}

long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState_RTDATA_TestApp(CSttSysState *pSysState, CIot_TestApp *pTestApp)
{
	if (pSysState == NULL || pTestApp == NULL)
	{
		return -1;
	}

	//������
	return 0;
}

long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState_RTDATA_Dev(CSttSysState *pSysState, CIot_TypeTaskDev *pDev)
{
	if (pSysState == NULL || pDev == NULL)
	{
		return -1;
	}

	//������
	return 0;
}

//strTemplateDocFile�����غ�ı���ģ�壬���ؾ���·��
BOOL CAtsSvr_TemplateServiceBase::Export_Report(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol, const CString &strDocRptFile, CIot_TypeTaskTests *pListTaskTests)
{
	if (pAtsCmd == NULL || pSttProtocol == NULL)
	{
		return FALSE;
	}

	if (!IsFileExist(strDocRptFile))
	{
		return FALSE;
	}

	if (pListTaskTests->GetCount() == 0)
	{
		return FALSE;
	}

	CString strTaskSN, strSampleSN;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TaskSN, strTaskSN);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_SampleSN, strSampleSN);
	char* pszCmdID = NULL;
	CString_to_char(pAtsCmd->m_strID, &pszCmdID);

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	//����ExportBegin�¼�
	pParasReturn->AddNewData(STT_CMD_PARA_EventID, SYS_STATE_XEVENT_EVENTID_ExportBegin);
	pParasReturn->AddNewData(XPARA_ID_TaskSN, strTaskSN);
	pParasReturn->AddNewData(XPARA_ID_SampleSN, strSampleSN);
	pSttProtocol->ReturnSysState_EVENT((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);

	BOOL bRet = TRUE;
	POS pos = pListTaskTests->GetHeadPosition();
	long nIndex = 0;
	long nTotalCount = pListTaskTests->GetCount();
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		CIot_TypeTaskTest *pTaskTest = (CIot_TypeTaskTest *)pListTaskTests->GetNext(pos);
		pParasReturn->DeleteAll();
		nIndex++;
		
		bSucc = Export_Report(strDocRptFile, pTaskTest);

		if (bSucc)
		{
			oSysState.Set_ExecStatus_Success();
		}
		else
		{
			bRet = FALSE;
			oSysState.Set_ExecStatus_Failure();
		}
	
		pParasReturn->AddNewData(STT_CMD_PARA_EventID, SYS_STATE_XEVENT_EVENTID_ExportProcess);
		pParasReturn->AddNewData(XPARA_ID_TaskSN, strTaskSN);
		pParasReturn->AddNewData(XPARA_ID_TaskTestSN, pTaskTest->m_nIndex_Test);
		pParasReturn->AddNewData(XPARA_ID_SampleSN, strSampleSN);
		pParasReturn->AddNewData(XPARA_ID_TOTALCUOUNT, nTotalCount);
		pParasReturn->AddNewData(XPARA_ID_CURRENTINDEX, nIndex);
		pSttProtocol->ReturnSysState_EVENT((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
	}

	//���������еĲ��Լ�¼�������󣬹ر�word�ĵ�

	delete pszCmdID;
	return bRet;
}

BOOL CAtsSvr_TemplateServiceBase::Export_Report(const CString &strDocRptFile, CIot_TypeTaskTest *pTaskTest)
{
	//��������ʱ���Ƿ���Ҫ��ÿ�����Լ�¼���ԵĲ��Ե�ģ�塣
	//����Ҫ������Ҫ��iot_type_task_test���У���һ���ֶΣ���¼�����õ�ģ�塣
	//�����õ�ģ�壬�Ǹ��ݲ��Ե�����ã���̬����˲�����Ŀ�ġ�
	//���ģ�屣��ʱ��Ӧ������ʱ�꣬��ֹ���ǡ�
	//ÿ�����Լ�¼���ԵĲ��Ե�ģ�壬�Ƿ����ϴ���

	//20230609��ÿ�����Լ�¼��ʵ��ģ�壬��ʱ���ϴ�
	//��������ʱ��ƴ��һ���µı��ģ����һ���ļ���ͨ�������������µ�SmartTestʵ�������б��浼����
	BOOL bRet = TRUE;

	return TRUE;
}

//��������ʱ�����ر���ģ���ļ�
//strFileNameΪ����ģ���ļ��������磺�����·���װ��.gbxml
BOOL CAtsSvr_TemplateServiceBase::DownLoadFile_Template_RptFile(const CString &strFileName, CString &strFileDownLoad)
{
	BOOL bRet = TRUE;
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	strRootPath = _P_GetInstallPath();
	strRootPath += _T("e-Report\\Template\\");
	CString strRptFile;
	strRptFile = ChangeFilePostfix(strFileName, _T("doc"));

	strFileDownLoad = strRootPath + strRptFile;   //���ص����ص�·��

	if (IsFileExist(strFileDownLoad))
	{
		return TRUE;
	}

	//��ѯģ�����ȡ����ģ���ļ��������ص�ַ
	CIot_Template oTemplate;
	bRet = oTemplate.QureyTemplateByName(g_pTheMySqlApp, strFileName);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��ѯ����ģ���ʧ�ܡ�%s��"), strFileName);
		return bRet;
	}

	//doc_file = PAL_PCS-931.doc|55485f01c9894147828f04ccea25ceb5.doc
	//svr_relate_path = /profile/upload/2021/09/01
	long nPos = oTemplate.m_strDoc_File.Find(_T("|"));

	if (nPos < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��ѯ����ģ���ȡ����ģ���ļ���ʧ�ܡ�%s��"), oTemplate.m_strDoc_File);
		return FALSE;
	}

	strFile_s = oTemplate.m_strSvr_Relate_Path + _T("/");
	strFile_s += oTemplate.m_strDoc_File.Mid(nPos + 1);
	strUrl = strHttpUrlHead + strFile_s;

	return CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
}

BOOL CAtsSvr_TemplateServiceBase::DownLoadFile_Template(CSttAtsCmd *pAtsCmd, CString &strFileDownLoad)
{
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CSttParas *pParas = (CSttParas *)pAtsCmd->GetSttParas();
	strRootPath = _P_GetInstallPath();
	strRootPath += _T("e-Report\\Template\\");

	//���ز���ģ���ļ�
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE_S, strFile_s);

	if (strFile_s.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ģ���ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
		return FALSE;
	}
	
	strFileDownLoad = strRootPath + strFile;
	strUrl = strHttpUrlHead + strFile_s;

	if (IsFileExist(strFileDownLoad))
	{
		return TRUE;
	}
	
	return CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
}

BOOL CAtsSvr_TemplateServiceBase::DownLoadFile_TaskInfo(CSttAtsCmd *pAtsCmd, CString &strFileDownLoad)
{
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CSttParas *pParas = (CSttParas *)pAtsCmd->GetSttParas();
	strRootPath = _P_GetLibraryPath();
	strRootPath += _T("TaskInfo\\");
	CreateAllDirectories(strRootPath);

	//���ز���ģ���ļ�
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE_S, strFile_s);

	if (strFile_s.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("������Ϣ�ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
		return FALSE;
	}

	strFileDownLoad = strRootPath + strFile;
	strUrl = strHttpUrlHead + strFile_s;

	if (IsFileExist(strFileDownLoad))
	{
		return TRUE;
	}

	return CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
}

BOOL CAtsSvr_TemplateServiceBase::DownLoadFile_SampleInfo(CSttAtsCmd *pAtsCmd, CString &strFileDownLoad)
{
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CSttParas *pParas = (CSttParas *)pAtsCmd->GetSttParas();
	strRootPath = _P_GetLibraryPath();
	strRootPath += _T("SampleInfo\\");
	CreateAllDirectories(strRootPath);

	//���ز���ģ���ļ�
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DVMFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DVMFILE_S, strFile_s);

	if (strFile_s.IsEmpty())
	{
		//����ģ���ļ��Ǳ�����������ڣ�ֱ�ӷ�������ʧ��
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��Ʒ��Ϣ�ļ���%s��Ϊ�գ�����ʧ�ܣ�"), strFile);
		return FALSE;
	}

	strFileDownLoad = strRootPath + strFile;
	strUrl = strHttpUrlHead + strFile_s;

	if (IsFileExist(strFileDownLoad))
	{
		return TRUE;
	}

	return CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
}

//strLocalFilePathΪ���ļ����ľ���·��
BOOL CAtsSvr_TemplateServiceBase::UploadFile(const CString &strLocalFilePath, CString &strFile_s)
{
	CString strUrl, strHttpUrlHead;
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	strUrl = strHttpUrlHead + _T("/file/upload");
	std::string strLastRpt, strFileNameRpt, strUrlRpt;
	strLastRpt = "";

	BOOL bRet = CXFileHttpClient::UploadFile(strUrl, strLocalFilePath);
	CXFileHttpClient::ParseURLReport(strLastRpt, strFileNameRpt, strUrlRpt);
	strFile_s = strFileNameRpt.c_str();

	return bRet;
}

BOOL CAtsSvr_TemplateServiceBase::UploadFile_DvmDevice(const CString &strFile, CString &strFile_s)
{
	CString strLocalPath;
	strLocalPath = _P_GetInstallPath();
	strLocalPath += _T("e-Protocol\\Library\\");  //ģ���ļ�ͳһ�����e-Protocol/Library��Ŀ¼
	strLocalPath += strFile;

	if (!IsFileExist(strLocalPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("���ϴ���ģ���ļ���%s�������ڣ��ϴ�ʧ�ܣ�"), strFile);
		return FALSE;
	}

	return UploadFile(strLocalPath, strFile_s);
}

//strFile�Ǿ���·��
BOOL CAtsSvr_TemplateServiceBase::UploadFile_RptFile(const CString &strFile, CString &strFile_s)
{
	return UploadFile(strFile, strFile_s);
}

BOOL CAtsSvr_TemplateServiceBase::OpenGbxmlFile(const CString &strFilePath, CExBaseList *pItemsList, CGuideBook *pGuideBook)
{
	BOOL bRet = pGuideBook->Open(strFilePath);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ģ���ļ���%s������ʧ�ܣ�"), strFilePath);
		return bRet;
	}

	//��ɸѡ�����еĲ��Դ���ŵ���ʱ������
	CDevice *pDevice = pGuideBook->GetDevice();
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = NULL;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			//���Դ����ӦΪCDevice�ڵ��µĵ�һ��CItems
			continue;
		}

		pItemsList->AddTail(pObj);
		pDevice->Remove(pObj);   //ͬʱ�Ƴ�����������ÿ�������һ��Сģ��
	}

	return bRet;
}

//Ϊÿһ�����Դ������һ������ģ��
BOOL CAtsSvr_TemplateServiceBase::SaveGbxmlFile_Items(const CString &strFileName, CGuideBook *pGuideBook, CExBaseList *pListItems)
{
	BOOL bRet = TRUE;
	CString strGbxmlFile, strPath;
	strGbxmlFile = _P_GetInstallPath();
	strGbxmlFile += _T("e-Report\\Template\\");

	CString strFile = strFileName;
	long nPos = strFileName.Find(g_strGbFilePostfix);

	if (nPos > 0)
	{
		//��ȡ��ģ����ļ�����������׺
		strFile = strFileName.Left(nPos);
	}

	CDevice *pDevice = pGuideBook->GetDevice();
	POS pos = pListItems->GetHeadPosition();

	while (pos != NULL)
	{
		CItems *pItems = (CItems *)pListItems->GetNext(pos);
		pDevice->AddTail(pItems);  //��ǰ�Ѿ��Ƴ������д����Ӵ��ģ���С���ʱ��ģ��ֻ��һ������

		strPath = strGbxmlFile;
		strPath += strFile;
		strPath += _T("$");
		strPath += pItems->m_strName;
		strPath += g_strGbFilePostfix;  //��ģ���ļ���$������.gbxml

		if (!pGuideBook->SaveXMLFile(strPath))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("���Դ��%s����ģ���ļ���%s������ʧ�ܣ�"), pItems->m_strName, strPath);
			bRet = FALSE;
		}

		//������Ƴ��ѱ���Ĵ���Ա������һ������
		pDevice->Remove(pItems);
	}

	return bRet;
}

CDataGroup* CAtsSvr_TemplateServiceBase::ParseFile_TaskInfo(const CString &strTaskInfoFile)
{
	if (!IsFileExist(strTaskInfoFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("������Ϣ�ļ���%s������ʧ�ܣ�"), strTaskInfoFile);
		return NULL;
	}

	//return m_oTaskInfoParser.Parse(strTaskInfoFile);
	return NULL;
}

CDataGroup* CAtsSvr_TemplateServiceBase::ParseFile_SampleInfo(const CString &strSampleInfoFile)
{
	if (!IsFileExist(strSampleInfoFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��Ʒ��Ϣ�ļ���%s������ʧ�ܣ�"), strSampleInfoFile);
		return NULL;
	}

	//return m_oSampleInfoParser.Parse(strTaskInfoFile);
	return NULL;
}

/*
<device-model>
	<dataset name="dsDeviceAttr" id="dsDeviceAttr">
		<data name="ҵ��������ʱ����" id="PkgUpTmInterval" value="6000"></data>
	</dataset>
	<ldevice name="�¶ȴ�����" id="WD" index="0">
		<dataset name="dsAin" id="dsAin">
			<data name="�����¶�" id="temp" value=""/>
			<data name="�豸�¶�" id="equipTemp" value=""/>
		</dataset>
	</ldevice>
</device-model>
*/
//��Ʒ������������ģ���ļ�
CString CAtsSvr_TemplateServiceBase::GenerateDevDvm(const CString &strTaskSN, CDataGroup *pRatedParameter, CDataGroup *pDevDvm)
{
	CString strFileName, strPath;
	strFileName = strTaskSN + _T(".xml");
	strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol\\Library\\");  //ģ���ļ�ͳһ�����e-Protocol/Library��Ŀ¼
	strPath += strFileName;

	CDvmDevice *pDvmDevice = new CDvmDevice();
	
	if (pRatedParameter != NULL)
	{
		CDvmDataset *pDevAttr = new CDvmDataset();
		pDevAttr->m_strName = _T("װ������");
		pDevAttr->m_strID = _T("dsDeviceAttr");

		pDvmDevice->AddNewChild(pDevAttr);
		pDevAttr->AppendEx(*pRatedParameter);
		pRatedParameter->RemoveAll();
	}

	if (pDevDvm != NULL)
	{
		CDvmLogicDevice *pLogicDev = new CDvmLogicDevice();
		pLogicDev->m_strName = strTaskSN;
		pLogicDev->m_strID = strTaskSN;
		pDvmDevice->AddNewChild(pLogicDev);

		CDvmDataset *pdsAin = new CDvmDataset();
		pdsAin->m_strName = _T("�������ݼ�");
		pdsAin->m_strID = _T("dsAin");

		pLogicDev->AddNewChild(pdsAin);
		pdsAin->AppendEx(*pDevDvm);
		pDevDvm->RemoveAll();
	}

	pDvmDevice->SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	delete pDvmDevice;
	return strFileName;
}

CString CAtsSvr_TemplateServiceBase::GenerateDevDvm(const CString &strTaskSN, CIot_TypeTaskDevParases *pRatedParas, CIot_TypeTaskDevModels *pDevDvm)
{
	CString strFileName, strPath;
	strFileName = strTaskSN + _T(".xml");
	strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol\\Library\\");  //ģ���ļ�ͳһ�����e-Protocol/Library��Ŀ¼
	strPath += strFileName;

	CDvmDevice *pDvmDevice = new CDvmDevice();

	if (pRatedParas != NULL)
	{
		CDvmDataset *pDevAttr = new CDvmDataset();
		pDevAttr->m_strName = _T("װ������");
		pDevAttr->m_strID = _T("dsDeviceAttr");

		pDvmDevice->AddNewChild(pDevAttr);
		POS pos = pRatedParas->GetHeadPosition();

		while (pos != NULL)
		{
			CIot_TypeTaskDevParas *pPara = (CIot_TypeTaskDevParas *)pRatedParas->GetNext(pos);
			CDvmData *pData = new CDvmData();
			pData->m_strName = pPara->m_strName;
			pData->m_strID = pPara->m_strID;
			pData->m_strDataType = pPara->m_strData_Type;
			pData->m_strValue = pPara->m_strValue;

			pDevAttr->AddNewChild(pData);
		}
	}

	if (pDevDvm != NULL)
	{
		CDvmLogicDevice *pLogicDev = new CDvmLogicDevice();
		pLogicDev->m_strName = strTaskSN;
		pLogicDev->m_strID = strTaskSN;
		pDvmDevice->AddNewChild(pLogicDev);

		CDvmDataset *pdsAin = new CDvmDataset();
		pdsAin->m_strName = _T("�������ݼ�");
		pdsAin->m_strID = _T("dsAin");

		pLogicDev->AddNewChild(pdsAin);
		POS pos = pDevDvm->GetHeadPosition();

		while (pos != NULL)
		{
			CIot_TypeTaskDevModel *pDevModel = (CIot_TypeTaskDevModel *)pDevDvm->GetNext(pos);
			CDvmData *pData = new CDvmData();
			pData->m_strName = pDevModel->m_strName;
			pData->m_strID = pDevModel->m_strID;
			pData->m_strDataType = pDevModel->m_strData_Type;
			pData->m_strValue = pDevModel->m_strValue;

			pdsAin->AddNewChild(pData);
		}
	}

	pDvmDevice->SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	delete pDvmDevice;
	return strFileName;
}

//�����û�ID����ѯ�û���
BOOL CAtsSvr_TemplateServiceBase::QueryUserByUserID(long nUser_ID, CString &strName_User)
{
	CSys_User oUser;
	return oUser.QueryUserByUserID(g_pTheMySqlApp, nUser_ID, strName_User);
}

BOOL CAtsSvr_TemplateServiceBase::DB_InsertTemplateItems(const CString &strFileName, CExBaseList *pListItems)
{
	//�ȸ���ģ���ļ�����strFileName������ѯiot_template����ȡģ���index_template
	BOOL bRet = TRUE;
 	CIot_Template oTemplate;
 	bRet = oTemplate.QureyTemplateByName(g_pTheMySqlApp, strFileName);

	if (!bRet)
	{
		return bRet;
	}

	POS pos = pListItems->GetHeadPosition();

	while (pos != NULL)
	{
		CItems *pItems = (CItems *)pListItems->GetNext(pos);
		//ģ������Ĵ��д�����ݿ��iot_template_items
		CIot_TemplateItems *pIotItems = DB_InsertTemplateItems_Items(oTemplate.m_nIndex_Template, pItems); 

		if (pIotItems == NULL)
		{
			bRet = FALSE;
			continue;
		}

		POS posItems = pItems->GetHeadPosition();

		while (posItems != NULL)
		{
			CExBaseObject *pItem = pItems->GetNext(posItems);

			if (pItem->GetClassID() != GBCLASSID_ITEMS)
			{
				//����С��ǲ��Դ����µ�һ������ڵ�
				//ģ����Ŀ����-�����iot_template_item��
				continue;
			}

			//���������С�д�����ݿ��iot_template_item
			CIot_TemplateItem *pIotItem = DB_InsertTemplateItems_Item(oTemplate.m_nIndex_Template, pIotItems->m_nIndex_Items, (CItems *)pItem); 

	 		if (pIotItem == NULL)
	 		{
	 			bRet = FALSE;
	 			continue;
	 		}

			delete pIotItem;
		}

		delete pIotItems;
	}

	return bRet;
}

//ģ������Ĵ��д�����ݿ��iot_template_items
CIot_TemplateItems* CAtsSvr_TemplateServiceBase::DB_InsertTemplateItems_Items(long nIndex_Template, CExBaseList *pItems)
{
	CIot_TemplateItems *pNew = new CIot_TemplateItems();

	pNew->m_strName = pItems->m_strName;
	pNew->m_strID = pItems->m_strID;
	pNew->m_nIndex_Template = nIndex_Template;

	CString strID = pItems->m_strID;
	strID.MakeLower();

	if (strID.Find(_T("manual")) >= 0)
	{
		pNew->m_strType = TEMPLATE_ITEMS_TYPE_MANUAL;
	}
	else
	{
		pNew->m_strType = TEMPLATE_ITEMS_TYPE_ATS;
	}

	BOOL bRet = pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);

	if (bRet)
	{
		return pNew;
	}

	delete pNew;
	return NULL;
}

//ģ�������С�д�����ݿ��iot_template_item
CIot_TemplateItem* CAtsSvr_TemplateServiceBase::DB_InsertTemplateItems_Item(long nIndex_Template, long nIndex_Items, CExBaseList *pItem)
{
	CIot_TemplateItem *pNew = new CIot_TemplateItem();

	pNew->m_strName = pItem->m_strName;
	pNew->m_strID = pItem->m_strID;
	pNew->m_nIndex_Items = nIndex_Items;
	pNew->m_nIndex_Template = nIndex_Template;

	BOOL bRet = pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);

	if (bRet)
	{
		return pNew;
	}

	delete pNew;
	return NULL;
}

//������
BOOL CAtsSvr_TemplateServiceBase::DB_Insert_IotItems(CExBaseList *pListItems)
{
	BOOL bRet = TRUE;

	return bRet;
}

/*
<group id="BasicInfo" name="���������Ϣ">
	<data id="TestType" name="��������" value="��ʽ����"/>
	<data id="SampleSN" name="��Ʒ���" value="GJK20220207"/>
	<data id="SampleModel" name="��Ʒ�ͺ�" value="CQSJ"/>
	<data id="SampleName" name="��Ʒ����" value="�����·���װ��"/>
	<data id="ClientName" name="ί�е�λ����" value="�Ƽ����޹�˾"/>
	<data id="ClientAddress" name="ί�е�λ��ַ" value="8��A��"/>
	<data id="ManufactorName" name="���쵥λ����" value="�Ƽ����޹�˾"/>
	<data id="ManufactorAddress" name="���쵥λ��ַ" value="8��A��"/>
	<!--�������У������Ϣȱʧʱ��value�������-->
</group>
*/
//д���ݿ��iot_type_task���½�ί������
CIot_TypeTask* CAtsSvr_TemplateServiceBase::DB_InsertTypeTask(CDataGroup *pTaskBasicInfo, const CString &strTaskFileName, const CString &strTaskFile_s, const CString &strID_User)
{
	if(pTaskBasicInfo == NULL)
	{
		return NULL;
	}

	CIot_TypeTask* pNew = new CIot_TypeTask();
	pNew->m_strTask_File = strTaskFileName;
	pNew->m_strTask_File_S = strTaskFile_s;
	pNew->m_strId_User = strID_User;

	pTaskBasicInfo->GetDataValue(XPARA_ID_TestType, pNew->m_strInspection_Type);
	pTaskBasicInfo->GetDataValue(XPARA_ID_SampleSN, pNew->m_strSn_Sample);
	pTaskBasicInfo->GetDataValue(XPARA_ID_SampleModel, pNew->m_strModel_Sample);
	pTaskBasicInfo->GetDataValue(XPARA_ID_SampleName, pNew->m_strName_Sample);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ClientName, pNew->m_strName_Client);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ClientAddress, pNew->m_strAddress_Client);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ManufactorName, pNew->m_strName_Manufactor);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ManufactorAddress, pNew->m_strAddress_Manufactor);

	BOOL bRet = pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);

	if (bRet)
	{
		return pNew;
	}

	delete pNew;
	return NULL;
}

//д���ݿ��iot_type_task���������������ţ�����ί������
CIot_TypeTask* CAtsSvr_TemplateServiceBase::DB_UpdateTypeTask(long nIndex_TypeTask, CDataGroup *pTaskBasicInfo, const CString &strTaskFileName
	, const CString &strTaskFile_s)
{
	if (pTaskBasicInfo == NULL)
	{
		return NULL;
	}

	CIot_TypeTask* pNew = new CIot_TypeTask();
	BOOL bRet = pNew->QueryTypeTaskByIndex(g_pTheMySqlApp, nIndex_TypeTask);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ѯί�������ʧ�ܣ�[%d]"), nIndex_TypeTask);
		delete pNew;
		return NULL;
	}

	pNew->m_strTask_File = strTaskFileName;
	pNew->m_strTask_File_S = strTaskFile_s;
	pTaskBasicInfo->GetDataValue(XPARA_ID_TestType, pNew->m_strInspection_Type);
	pTaskBasicInfo->GetDataValue(XPARA_ID_SampleSN, pNew->m_strSn_Sample);
	pTaskBasicInfo->GetDataValue(XPARA_ID_SampleModel, pNew->m_strModel_Sample);
	pTaskBasicInfo->GetDataValue(XPARA_ID_SampleName, pNew->m_strName_Sample);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ClientName, pNew->m_strName_Client);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ClientAddress, pNew->m_strAddress_Client);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ManufactorName, pNew->m_strName_Manufactor);
	pTaskBasicInfo->GetDataValue(XPARA_ID_ManufactorAddress, pNew->m_strAddress_Manufactor);

	bRet = pNew->DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	if (bRet)
	{
		return pNew;
	}

	delete pNew;
	return NULL;
}

/*
<group id="InspectionBases" name="�����������">
	<data id="InspectionBasis1" name="��������1" value="Q/GDW 12021-2019�����豸�������ڵ��豸��������Э��"/>
	<data id="Name" name="��������" value="PAL/BZ 12020-2020�����豸������΢����������ͨ��Э��"/>
	<data id="Name" name="��������" value="PAL/BZ 12021-2020�����豸�������ڵ��豸��������Э��"/>
	<!--��߶��ٸ��������ݣ����ж��ٸ�data-->
</group>
*/
//д���ݿ��iot_type_task_standard
BOOL CAtsSvr_TemplateServiceBase::DB_InsertTypeTask_Standard(long nIndex_TypeTask, CDataGroup *pInspectionBases)
{
	//�������ݣ�����Ϊ��
	if(pInspectionBases == NULL)
	{
		return TRUE;
	}

	BOOL bRet = TRUE;
	CIot_TypeTaskStandard *pNew = new CIot_TypeTaskStandard();
	pNew->m_nIndex_Task = nIndex_TypeTask;

	POS pos = pInspectionBases->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pInspectionBases->GetNext(pos);

		//�˴���ʱ������ȥά���������ݵ��ܱ�iot_test_standard����
		//��Ϊ��������ʱ�����������Ǵ��������н�����ã������Ǵ��ܱ���ѡ��
		pNew->m_strStandard_Name = pData->m_strValue;
		::GetLocalTime(&pNew->m_tmCreate_Time);
		pNew->m_nId = 0;

		if ( !pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��������д�����ݿ�ʧ�ܣ�[%s]"), pData->m_strValue);
			bRet = FALSE;
		}
	}

	return bRet;
}

/*
<group id="SampleDevices" name="��Ʒ�б�">
	<group id="SampleDevice1" name="��Ʒ1">
		<data id="DeviceSN" name="�豸���к�" value="CQSJ2022110010"/>
		<data id="SampleSN" name="��Ʒ���" value="GJK20220207-1"/>
		<!--�����Ʒ��Ϣ�ļ���û�и���Ϣ���򷵻صĽṹ�в�Ҫ������SmapleSN���ֶ�-->
	</group>
	<group id="SampleDevice2" name="��Ʒ2">
		<data id="DeviceSN" name="�豸���к�" value="CQSJ2022110011"/>
		<data id="SampleSN" name="��Ʒ���" value="GJK20220207-2"/>
	</group>
	<!--��߶��ٸ���Ʒ�豸�����ж��ٸ�group-->
</group>
*/
//д���ݿ⣺������Ʒ��iot_type_task_dev
BOOL CAtsSvr_TemplateServiceBase::DB_InsertTypeTask_Devs(long nIndex_TypeTask, CDataGroup *pSampleDevices)
{
	if (pSampleDevices == NULL)
	{
		return FALSE;
	}

	if (pSampleDevices->GetCount() == 0)
	{
		return FALSE;
	}

	//1����ѯί�������iot_type_task����ȡ��Ʒ��ţ�������Ʒ����
	BOOL bRet = TRUE;
	CIot_TypeTask* pTypeTask = new CIot_TypeTask();
	bRet = pTypeTask->UpdateSampleCnt(g_pTheMySqlApp, nIndex_TypeTask, pSampleDevices->GetCount());

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����ί����������Ʒ����ʧ�ܣ�[%d]"), nIndex_TypeTask);
		delete pTypeTask;
		return NULL;
	}

	//2����Ʒ��Ϣ�У���û��SampleSN�ֶΣ�����Ҫ����ί���������Ʒ��ţ��Զ����£�SampleSN-1��SampleSN-2����
	POS pos = pSampleDevices->GetHeadPosition();
	long nIndex = 0;
	CString strDeviceSN, strSampleSN;

	while (pos != NULL)
	{
		CDataGroup *pSampleDevice = (CDataGroup *)pSampleDevices->GetNext(pos);
		pSampleDevice->GetDataValue(XPARA_ID_SampleSN, strSampleSN);
		pSampleDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);
		nIndex++;

		if (strDeviceSN.IsEmpty())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ί��������Ʒ��%s�����豸���к�Ϊ�գ�"), strSampleSN);
			bRet = FALSE;
			continue;
		}

		if (strSampleSN.IsEmpty())
		{
			//�Զ����
			strSampleSN.Format(_T("%s-%d"), pTypeTask->m_strSn_Sample, nIndex);
		}

		CIot_TypeTaskDev oTypeTaskDev;
		oTypeTaskDev.m_nIndex_Task = pTypeTask->m_nIndex_Task;
		oTypeTaskDev.m_strSn_Sample_Dev = strDeviceSN;   //��Ʒ�豸���к�
		oTypeTaskDev.m_strNumber_Sample_Dev = strSampleSN;   //��Ʒ���

		if ( !oTypeTaskDev.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ί��������Ʒ��%s����д�����ݿ�ʧ�ܣ�"), strSampleSN);
			bRet = FALSE;
		}
	}

	delete pTypeTask;
	return bRet;
}
 
/*
<group id="RatedParameter" name="�����">
	<data id="Power" name="����" value="100" data-type="float" unit="W"/>
	<data id="Weight" name="����" value="1.23" data-type="float" unit="kg"/>
	<!--��߶��ٸ�����������ж��ٸ�data���������id��name��value��data-type��unit���ԣ�����excel�ļ��������-->
</group>
*/
//�����д�����ݿ�  iot_type_task_dev_paras
BOOL CAtsSvr_TemplateServiceBase::DB_InsertTypeTask_RatedParameter(long nIndex_TypeTask, CDataGroup *pRatedParameter)
{
	if (pRatedParameter == NULL)
	{
		//��Ʒ�����������Ϊ��
		return TRUE;
	}

	BOOL bRet = TRUE;
	POS pos = pRatedParameter->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pRatedParameter->GetNext(pos);
		CIot_TypeTaskDevParas oDevPara;
		oDevPara.m_nIndex_Task = nIndex_TypeTask;
		
		if ( !oDevPara.WriteToDB(g_pTheMySqlApp, pData) )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ί������������%s����д�����ݿ�ʧ�ܣ�"), pData->m_strName);
			bRet = FALSE;
			continue;
		}
	}

	return bRet;
}

/*
<group id="DevDvm" name="������">
	<data id="RealTimeWindSpeed" name="ʵʱ����" value="23.2" data-type="unsigned int" unit="m/s"/>
	<data id="RealTimeWindDir" name="ʵʱ����" value="1.23" data-type="unsigned int" unit="��"/>
	<!--��߶��ٸ������������ж��ٸ�data���������id��name��value��data-type��unit���ԣ�����excel�ļ��������-->
</group>
*/
//������д�����ݿ�  iot_type_task_dev_model
BOOL CAtsSvr_TemplateServiceBase::DB_InsertTypeTask_DevDvm(long nIndex_TypeTask, CDataGroup *pDevDvm)
{
	//������������Ϊ��
	if (pDevDvm == NULL)
	{
		return FALSE;
	}

	if (pDevDvm->GetCount() == 0)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pDevDvm->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pDevDvm->GetNext(pos);
		CIot_TypeTaskDevModel oDevModel;
		oDevModel.m_nIndex_Task = nIndex_TypeTask;

		if ( !oDevModel.WriteToDB(g_pTheMySqlApp, pData) )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ί�������������%s����д�����ݿ�ʧ�ܣ�"), pData->m_strName);
			bRet = FALSE;
			continue;
		}
	}

	return bRet;
}

BOOL CAtsSvr_TemplateServiceBase::DB_InsertDeviceModel(const CString &strFile, const CString &strFile_s)
{
	CIot_DeviceModel oDeviceModel;
	//�������ԣ���ʱ������Ϊ0��
	oDeviceModel.m_nIndex_Device_Classify = 0;
	oDeviceModel.m_nIndex_Device_Type = 0;
	oDeviceModel.m_nIndex_Factory = 0;
	oDeviceModel.m_nIndex_Model_Dir = 0;

	oDeviceModel.m_strFile_Name = strFile;
	oDeviceModel.m_strPath_Protocol_File = strFile_s;

	//ģ���ļ����ļ�������������ID�����ģ���˲��ò�ѯ�Ƿ��ظ���ֱ�Ӵ������
	return oDeviceModel.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);
}
#endif
