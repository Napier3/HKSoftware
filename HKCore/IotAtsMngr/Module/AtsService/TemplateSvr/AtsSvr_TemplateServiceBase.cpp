#include "StdAfx.h"
#include "AtsSvr_TemplateServiceBase.h"
#include "../../../../Module/XFileHttpClient/XFileHttpClient.h"

/*
<sys-state name="" id="QueryItems" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="1|2|3|4" unit=""/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data name="" id="ItemPath" data-type="" value="Device$ManulTest"/>
		<items name="" id="" tkid="65535" select="1">
			。。。。。。
			<safety name="接线提示" id="Safety" tkid="65535" select="0">
				<msg type="1"><![CDATA[					【提示人工进行操作的信息】					]]></msg>
				<datas name="" id="">
					<data name="变电站名称" id="Test1" data-type="" unit="" value="220KV晨阳站" format="" remark="" default="220KV晨阳站" reserved="1" time="0"/>
					<data name="主变名称" id="Test2" data-type="" unit="" value="1号主变" format="" remark="" default="1号主变" reserved="1" time="0"/>
					<data name="开关编号" id="Test3" data-type="" unit="" value="110" format="" remark="" default="110" reserved="1" time="0"/>
					<data name="data1" id="data1" data-type="combobox" unit="" value="eligible" format="Eligible" remark="" default="eligible" reserved="1" time="0" />
					<data name="data2" id="data2" data-type="combobox" unit="" value="right" format="Right" remark="" default="" reserved="1" time="0" />
				</datas>
			</safety>
。。。。。。
		</items>
		<data-types name="" id="">
			<data-type name="合格/不合格" id="Eligible">
				<value name="合格" id="eligible" index="1"/>
				<value name="不合格" id="inlegible" index="2"/>
			</data-type>
			<data-type name="正确/不正确" id="Right">
				<value name="正确" id="right" index="1"/>
				<value name="不正确" id="wrong" index="2"/>
			</data-type>
			。。。。。。
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

	//2023-9-11  李俊庆 拷贝时，只拷贝必要信息，用于给MES或者其他外部系统，去掉script、report-map等对象
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
		//2023-6-6：按照最新的修改，导入任务信息，由网站解析写库。自动测试服务不处理该指?
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
		//暂时不用该指令
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
		//成功
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
	}
	else
	{
		//失败
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, pszCmdID, STT_CMD_SYSSTATE_ATS);
	}

	delete pszCmdID;
	return nRet;
}

//cxa待处理。需要增加处理ExportReport事件
long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState*)oSysStateDrv.GetXObjectRef();

	if (pSysState->m_strID == SYS_STATE_EVENT_OnTestAppEvent)
	{
		return Process_Cmd_SysState_TestAppEvent(pSysState);   //测试仪的事件
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnEngineEvent)  
	{
		return Process_Cmd_SysState_EngineEvent(pSysState);   //设备的事件
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnRTDATA)
	{
		return Process_Cmd_SysState_RTDATA(pSysState);   //设备|测试仪的实时数据
	}

	return 0;
}

/*
新增模板：
1、下载模板文件；
2、加载解析模板文件，解析其中的大项，写数据库表“iot_template_items”；
3、每一个大项，都存一个小模板“大模板名$大项名.gbxml”，保存到本地Template路径下；
4、解析每个大项的小项，写数据库表“iot_template_item”后。
*/
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_UploadTemplate(CSttAtsCmd *pAtsCmd)
{
	//strFileDownLoad，下载后返回的本地全路径（带文件名）
	CString strFileDownLoad, strFileName;
	BOOL bRet = DownLoadFile_Template(pAtsCmd, strFileDownLoad);

	if (!bRet)
	{
		return -1;
	}

	//解析模板文件，并解析出所有大项
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

	//遍历所有大项，为每一个大项保存一个gbxml小模板
	bRet = SaveGbxmlFile_Items(strFileName, pGuideBook, &oListItems);

	if (!bRet)
	{
		oListItems.RemoveAll();
		delete pGuideBook;
		return -3;
	}

	//根据大项信息，写入数据库：模板项目分类表+模板项目分类子项表
	bRet = DB_InsertTemplateItems(strFileName, &oListItems);

	if (!bRet)
	{
		oListItems.RemoveAll();
		delete pGuideBook;
		return -4;
	}

	//项目分类总表
	bRet = DB_Insert_IotItems(&oListItems);

	if (!bRet)
	{
		oListItems.RemoveAll();
		delete pGuideBook;
		return -5;
	}

	//待处理：还需要下载文件名为“模板文件名$gen.xml”的xml文件
	//需要在Iot_Template表中增加字段。
	//解析该文件后，维护表iot_item_gen
	//20230609：讨论确定要加

	oListItems.RemoveAll();
	delete pGuideBook;
	return 0;
}

/*
<!--导入任务信息，从任务信息文件（Word任务书文件）中解析，获取任务的信息后，返回如下结构-->
<group id="TaskInfo" name="任务信息">
	<group id="BasicInfo" name="任务基本信息">
		<data id="TestType" name="检验类型" value="型式检验"/>
		<data id="SampleSN" name="样品编号" value="GJK20220207"/>
		<data id="SampleModel" name="样品型号" value="CQSJ"/>
		<data id="SampleName" name="样品名称" value="输电线路监测装置"/>
		<data id="ClientName" name="委托单位名称" value="科技有限公司"/>
		<data id="ClientAddress" name="委托单位地址" value="8号A栋"/>
		<data id="ManufactorName" name="制造单位名称" value="科技有限公司"/>
		<data id="ManufactorAddress" name="制造单位地址" value="8号A栋"/>
		<!--任务书中，相关信息缺失时，value属性填空-->
	</group>
	<group id="InspectionBases" name="任务检验依据">
		<data id="InspectionBasis1" name="检验依据1" value="Q/GDW 12021-2019输变电设备物联网节点设备无线组网协议"/>
		<data id="Name" name="依据名称" value="PAL/BZ 12020-2020输变电设备物联网微功率无线网通信协议"/>
		<data id="Name" name="依据名称" value="PAL/BZ 12021-2020输变电设备物联网节点设备无线组网协议"/>
		<!--这边多少个检验依据，就有多少个data-->
	</group>
</group>
*/
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_ImportTaskInfo(CSttAtsCmd *pAtsCmd)
{
	//strFileDownLoad，下载后返回的本地全路径（带文件名）
	CString strFileDownLoad, strName_User;
	BOOL bRet = DownLoadFile_TaskInfo(pAtsCmd, strFileDownLoad);

	if (!bRet)
	{
		return -1;
	}

	//解析任务书文件，返回任务信息group
	CDataGroup *pTaskInfo = NULL;
	pTaskInfo = ParseFile_TaskInfo(strFileDownLoad);

	if (pTaskInfo == NULL)
	{
		return -2;
	}

	//任务基本信息。不允许为空
	CDataGroup *pBasicInfo = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_BASICINFO);

	if (pBasicInfo == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("任务信息解析，缺少任务基本信息"));
		return -3;
	}

	CString strTaskFileName, strTaskFile_s;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE, strTaskFileName);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE_S, strTaskFile_s);

	CString strTaskSN;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TaskSN, strTaskSN);
	CIot_TypeTask* pIotTypeTask = NULL;

	long nUser_ID = CString_To_long(pAtsCmd->m_strFromSN);  //需要从主题中获取

	if (!strTaskSN.IsEmpty())
	{
		//任务信息允许二次导入。
		//当下发的指令中，TaskSN不为空时，则说明是二次导入。需要对已创建的委托任务的信息进行更新
		pIotTypeTask = DB_UpdateTypeTask(CString_To_long(strTaskSN), pBasicInfo, strTaskFileName, strTaskFile_s);
	}
	else
	{
		//从用户表中，查询用户名称
		bRet = QueryUserByUserID(nUser_ID, strName_User);

		if (!bRet)
		{
			return -4;
		}

		//写数据库表iot_type_task，新建委托任务
		pIotTypeTask = DB_InsertTypeTask(pBasicInfo, strTaskFileName, strTaskFile_s, strName_User);
	}

	if (pIotTypeTask == NULL)
	{
		return -5;
	}

	//检验依据信息，允许为空。当为空时，返回成功
	CDataGroup *pInspectionBases = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_InspectionBases);

	//写数据库表iot_type_task_standard
	bRet = DB_InsertTypeTask_Standard(pIotTypeTask->m_nIndex_Task, pInspectionBases);
	
	if (!bRet)
	{
		return -6;
	}

	return 0;
}

/*
//2023-6-6
//根据最新的设计，自动测试服务将不再解析样品信息文件
//网站解析文件后，将相关的信息写入数据库表，自动测试服务从数据库表中拉取额定参数和点表参数，生成模型文件


<!--导入样品列表，从样品信息文件（Excel文件）中解析，获取样品的信息后，返回如下结构-->
<group id="SampleInfo" name="样品信息">
	<group id="SampleDevices" name="样品列表">
		<group id="SampleDevice1" name="样品1">
			<data id="DeviceSN" name="设备序列号" value="CQSJ2022110010"/>
			<data id="SampleSN" name="样品编号" value="GJK20220207-1"/>
			<!--如果样品信息文件中没有该信息，则返回的结构中不要包含“SmapleSN”字段-->
		</group>
		<group id="SampleDevice2" name="样品2">
			<data id="DeviceSN" name="设备序列号" value="CQSJ2022110011"/>
			<data id="SampleSN" name="样品编号" value="GJK20220207-2"/>
		</group>
		<!--这边多少个样品设备，就有多少个group-->
	</group>
	<group id="RatedParameter" name="额定参数">
		<data id="Power" name="功率" value="100" data-type="float" unit="W"/>
		<data id="Weight" name="重量" value="1.23" data-type="float" unit="kg"/>
		<!--这边多少个额定参数，就有多少个data。额定参数的id、name、value、data-type、unit属性，均从excel文件解析获得-->
	</group>
	<group id="DevDvm" name="点表参数">
		<data id="RealTimeWindSpeed" name="实时风速" value="23.2" data-type="unsigned int" unit="m/s"/>
		<data id="RealTimeWindDir" name="实时风向" value="1.23" data-type="unsigned int" unit="度"/>
		<!--这边多少个点表参数，就有多少个data。额定参数的id、name、value、data-type、unit属性，均从excel文件解析获得-->
	</group>
</group>
*/
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_ImportSampleInfo(CSttAtsCmd *pAtsCmd)
{
	/*
	//strFileDownLoad，下载后返回的本地全路径（带文件名）
	CString strFileDownLoad;
	BOOL bRet = DownLoadFile_SampleInfo(pAtsCmd, strFileDownLoad);

	if (!bRet)
	{
		return -1;
	}

	//解析样品列表文件，返回样品信息group
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
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("样品信息解析，缺少样品列表信息"));
		//当缺少样品列表信息时，可能是二次上传，更新样品的额定参数
		//第一次上传时，可能没有额定参数，需要二次上传
	}
	else
	{
		//写数据库：任务样品表iot_type_task_dev
		bRet = DB_InsertTypeTask_Devs(CString_To_long(strTaskSN), pSampleDevices);

		if (!bRet)
		{
			return -3;
		}
	}

	//额定参数写入数据库
	CDataGroup *pRatedParameter = (CDataGroup *)pSampleInfo->FindByID(XPARA_ID_RatedParameter);
	bRet = DB_InsertTypeTask_RatedParameter(CString_To_long(strTaskSN), pRatedParameter);

	if (!bRet)
	{
		return -4;
	}

	//点表参数写入数据库
	CDataGroup *pDevDvm = (CDataGroup *)pSampleInfo->FindByID(XPARA_ID_DevDvm);
	bRet = DB_InsertTypeTask_DevDvm(CString_To_long(strTaskSN), pDevDvm);

	if (!bRet)
	{
		return -5;
	}

	//生成模型文件
	CString strDvmFile = GenerateDevDvm(strTaskSN, pRatedParameter, pDevDvm);  //返回文件名
	CString strFile_s;

	//通过HTTP上传生成的模型文件
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

	//查询任务额定参数表
	CIot_TypeTaskDevParases oParases;
	BOOL bRet = oParases.QueryTypeTaskDevParases(g_pTheMySqlApp, nTaskIndex);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("查询任务额定参数表失败【%s】"), strTaskSN);
		return -1;
	}

	//查询任务点表参数表
	CIot_TypeTaskDevModels oModels;
	bRet = oModels.QueryTypeTaskDevModels(g_pTheMySqlApp, nTaskIndex);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("查询任务点表参数表失败【%s】"), strTaskSN);
		return -2;
	}

	//生成模型文件
	CString strDvmFile = GenerateDevDvm(strTaskSN, &oParases, &oModels);  //返回文件名
	CString strFile_s;

	//通过HTTP上传生成的模型文件
	bRet = UploadFile_DvmDevice(strDvmFile, strFile_s);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("任务模型文件上传失败【%s   %s】"), strTaskSN, strDvmFile);
		return -3;
	}

	bRet = DB_InsertDeviceModel(strDvmFile, strFile_s);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("任务模型文件写数据库失败【%s   %s】"), strTaskSN, strDvmFile);
		return -4;
	}

	return 0;
}

/*
导出报告，生成测试记录。可以是针对委托任务导出报告。
测试管理机，根据任务ID，查找该任务关联的所有测试记录，导出设置为最终报告的所有任务测试记录的报告。
任务使用的模板：iot_type_task表的“name_template”（模板文件名唯一）。
在导出报告的时候，需要重新加载模板。
*/
//导出报告
//cxa待处理。根据任务，查询任务相关的记录、模板、检验人、检验依据等信息（应包括报告中需要的所有信息）。拼接成xml文档（文档结构待定），存成本地后，拉起SmartTest进行导出
long CAtsSvr_TemplateServiceBase::Process_Cmd_Ats_ExportReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	BOOL bRet = TRUE;
	CString strTaskSN, strSampleSN, strTemplateName;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TaskSN, strTaskSN);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_SampleSN, strSampleSN);

	//查询委托任务关联的所有设置最终报告的测试记录
	CIot_TypeTaskTests oTaskTests;
	bRet = oTaskTests.QueryAllTaskTests_FinalRpt(g_pTheMySqlApp, CString_To_long(strTaskSN));

	if (!bRet || oTaskTests.GetCount() == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("查询任务测试记录失败！【%s】"), strTaskSN);
		return -1;
	}

	//查询任务表，获取任务用的测试模板
	CIot_TypeTask oTypeTask;
	bRet = oTypeTask.QueryTypeTaskByIndex(g_pTheMySqlApp, CString_To_long(strTaskSN));

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("查询委托任务表失败！[%s]"), strTaskSN);
		return -2;
	}

	strTemplateName = oTypeTask.m_strName_Template;  //模板文件名
	CString strTemplateFilePath;
	bRet = DownLoadFile_Template_RptFile(strTemplateName, strTemplateFilePath);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("下载报告模板失败！[%s]"), strTemplateName);
		return -3;
	}

	//先将word报告模板，拷贝到WorkSpace路径下
	CString strDestFile;
	strDestFile = GetFileNameFromFilePath(strTemplateFilePath);
	strDestFile = ChangeFilePostfix(strDestFile, _T(""));  //去掉后缀
	SYSTEMTIME oTime;
	::GetLocalTime(&oTime);
	//给目标报告文件，打上时标
	strDestFile.AppendFormat(_T("_(%4d%2d%2d_%2d%2d%2d).doc"), oTime.wYear, oTime.wMonth, oTime.wDay
		, oTime.wHour, oTime.wMinute, oTime.wSecond);
	CString strPath;
	strPath = _P_GetWorkspacePath(_T(""));
	strDestFile = strPath + strDestFile;

	if (!::X_CopyFile(strTemplateFilePath, strDestFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("拷贝报告模板文件【%s】到WorkSpace目录失败！"), strTemplateFilePath);
		return FALSE;
	}

	//待处理：gbrpt-file如何处理？
	//20230609：委托任务，没有gbrpt文件。每个记录，用各自的gbrpt文件，导出word（word报告模板是个全量模板）。
	bRet = Export_Report(pAtsCmd, pSttProtocol, strDestFile, &oTaskTests);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("任务【%s】导出报告失败！"), strTaskSN);
		return -4;
	}

	//待处理，处理任务的检验依据、检验人、审核人、校对人等信息

	//导出成功后，上传word报告。
	CString strRptFile_s, strGbrptFile, strGbrptFile_s;
	bRet = UploadFile_RptFile(strDestFile, strRptFile_s);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("任务【%s】上传报告文件【%s】失败！"), strTaskSN, strDestFile);
		return -5;
	}

	//导出成功后，更新委托任务表
	strDestFile = GetFileNameFromFilePath(strDestFile);
	oTypeTask.m_strDoc_File = strDestFile;
	oTypeTask.m_strDoc_File_S = strRptFile_s;
	//待处理
	//20230609：任务表中没有该字段
	//oTypeTask.m_strGbrpt_File = strGbrptFile;
	//oTypeTask.m_strGbrpt_File_S = strGbrptFile_s;
	bRet = oTypeTask.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("任务【%s】更新数据库失败！"), strTaskSN);
		return -6;
	}

	//发送ExportFinish事件
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
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="EventID" data-type="string" value="TestBegin" unit=""/>
		<data id="DeviceSN" data-type="long" value="0" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>
*/
//测试仪的事件，暂时只处理：
//1、联机成功：ConnectSuccess
//2、联机失败：ConnectFailed
//3、联机通讯错误（同联机失败）：CommError
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到测试仪【%s】"), strDeviceSN);
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("不支持的测试仪测试事件类型【%s】"), strEventID);
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
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="EventID" data-type="string" value="CommFinish" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>
*/
//设备的事件，暂时只处理：
//1、联机成功：ConnectDeviceSuccessful
//2、联机失败：ConnectDeviceFailed
//3、通讯错误（同联机失败）：CommError
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到样品设备【%s】"), strDeviceSN);
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("不支持的设备测试事件类型【%s】"), strEventID);
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
		<data name="装置序列号|仪器仪表编号" id="DeviceSN" data-type="string" value="CQSJ2022110010"/>
		<data name="是否告警" id="is_warning" data-type="long" value="0"/>
		<group name="" id="" data-type="" value="">
			<data name="传感温度" id="Tempreture" data-type="float" value="25.3"/>
			<data name="传感湿度" id="Humidity" data-type="float" value="50.1"/>
		</group>
	</paras>
</sys-state>
*/
//实时数据，设备和测试仪公用
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

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到样品设备或仪器仪表【%s】"), strDeviceSN);
	return -1;
}

long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState_RTDATA_TestApp(CSttSysState *pSysState, CIot_TestApp *pTestApp)
{
	if (pSysState == NULL || pTestApp == NULL)
	{
		return -1;
	}

	//待处理
	return 0;
}

long CAtsSvr_TemplateServiceBase::Process_Cmd_SysState_RTDATA_Dev(CSttSysState *pSysState, CIot_TypeTaskDev *pDev)
{
	if (pSysState == NULL || pDev == NULL)
	{
		return -1;
	}

	//待处理
	return 0;
}

//strTemplateDocFile：下载后的报告模板，本地绝对路径
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
	//发送ExportBegin事件
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

	//待处理：所有的测试记录都导出后，关闭word文档

	delete pszCmdID;
	return bRet;
}

BOOL CAtsSvr_TemplateServiceBase::Export_Report(const CString &strDocRptFile, CIot_TypeTaskTest *pTaskTest)
{
	//导出报告时，是否需要打开每个测试记录各自的测试的模板。
	//若需要，则需要在iot_type_task_test表中，加一个字段，记录测试用的模板。
	//测试用的模板，是根据测试点的设置，动态添加了测试项目的。
	//因此模板保存时，应当打上时标，防止覆盖。
	//每个测试记录各自的测试的模板，是否考虑上传？

	//20230609：每个测试记录的实际模板，暂时不上传
	//导出报告时，拼接一个新的报文，存成一个文件，通过命令行拉起新的SmartTest实例，进行报告导出。
	BOOL bRet = TRUE;

	return TRUE;
}

//导出报告时，下载报告模板文件
//strFileName为测试模板文件名，例如：输电线路监测装置.gbxml
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

	strFileDownLoad = strRootPath + strRptFile;   //下载到本地的路径

	if (IsFileExist(strFileDownLoad))
	{
		return TRUE;
	}

	//查询模板表，获取报告模板文件名及下载地址
	CIot_Template oTemplate;
	bRet = oTemplate.QureyTemplateByName(g_pTheMySqlApp, strFileName);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("查询测试模板表失败【%s】"), strFileName);
		return bRet;
	}

	//doc_file = PAL_PCS-931.doc|55485f01c9894147828f04ccea25ceb5.doc
	//svr_relate_path = /profile/upload/2021/09/01
	long nPos = oTemplate.m_strDoc_File.Find(_T("|"));

	if (nPos < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("查询测试模板获取报告模板文件名失败【%s】"), oTemplate.m_strDoc_File);
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

	//下载测试模板文件
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE_S, strFile_s);

	if (strFile_s.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试模板文件【%s】为空，下载失败！"), strFile);
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

	//下载测试模板文件
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_TASKFILE_S, strFile_s);

	if (strFile_s.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("任务信息文件【%s】为空，下载失败！"), strFile);
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

	//下载测试模板文件
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DVMFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DVMFILE_S, strFile_s);

	if (strFile_s.IsEmpty())
	{
		//测试模板文件是必须项，若不存在，直接返回下载失败
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("样品信息文件【%s】为空，下载失败！"), strFile);
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

//strLocalFilePath为带文件名的绝对路径
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
	strLocalPath += _T("e-Protocol\\Library\\");  //模型文件统一存放在e-Protocol/Library根目录
	strLocalPath += strFile;

	if (!IsFileExist(strLocalPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("待上传的模型文件【%s】不存在，上传失败！"), strFile);
		return FALSE;
	}

	return UploadFile(strLocalPath, strFile_s);
}

//strFile是绝对路径
BOOL CAtsSvr_TemplateServiceBase::UploadFile_RptFile(const CString &strFile, CString &strFile_s)
{
	return UploadFile(strFile, strFile_s);
}

BOOL CAtsSvr_TemplateServiceBase::OpenGbxmlFile(const CString &strFilePath, CExBaseList *pItemsList, CGuideBook *pGuideBook)
{
	BOOL bRet = pGuideBook->Open(strFilePath);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试模板文件【%s】，打开失败！"), strFilePath);
		return bRet;
	}

	//先筛选出所有的测试大项，放到临时链表中
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
			//测试大项，对应为CDevice节点下的第一级CItems
			continue;
		}

		pItemsList->AddTail(pObj);
		pDevice->Remove(pObj);   //同时移除大项，方便后面每个大项保存一个小模板
	}

	return bRet;
}

//为每一个测试大项，保存一个测试模板
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
		//获取大模板的文件名，不带后缀
		strFile = strFileName.Left(nPos);
	}

	CDevice *pDevice = pGuideBook->GetDevice();
	POS pos = pListItems->GetHeadPosition();

	while (pos != NULL)
	{
		CItems *pItems = (CItems *)pListItems->GetNext(pos);
		pDevice->AddTail(pItems);  //此前已经移除了所有大项，添加大项到模板中。此时，模板只有一个大项

		strPath = strGbxmlFile;
		strPath += strFile;
		strPath += _T("$");
		strPath += pItems->m_strName;
		strPath += g_strGbFilePostfix;  //大模板文件名$大项名.gbxml

		if (!pGuideBook->SaveXMLFile(strPath))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试大项【%s】的模板文件【%s】保存失败！"), pItems->m_strName, strPath);
			bRet = FALSE;
		}

		//保存后，移除已保存的大项，以便添加下一个大项
		pDevice->Remove(pItems);
	}

	return bRet;
}

CDataGroup* CAtsSvr_TemplateServiceBase::ParseFile_TaskInfo(const CString &strTaskInfoFile)
{
	if (!IsFileExist(strTaskInfoFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("任务信息文件【%s】解析失败！"), strTaskInfoFile);
		return NULL;
	}

	//return m_oTaskInfoParser.Parse(strTaskInfoFile);
	return NULL;
}

CDataGroup* CAtsSvr_TemplateServiceBase::ParseFile_SampleInfo(const CString &strSampleInfoFile)
{
	if (!IsFileExist(strSampleInfoFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("样品信息文件【%s】解析失败！"), strSampleInfoFile);
		return NULL;
	}

	//return m_oSampleInfoParser.Parse(strTaskInfoFile);
	return NULL;
}

/*
<device-model>
	<dataset name="dsDeviceAttr" id="dsDeviceAttr">
		<data name="业务报文上送时间间隔" id="PkgUpTmInterval" value="6000"></data>
	</dataset>
	<ldevice name="温度传感器" id="WD" index="0">
		<dataset name="dsAin" id="dsAin">
			<data name="环境温度" id="temp" value=""/>
			<data name="设备温度" id="equipTemp" value=""/>
		</dataset>
	</ldevice>
</device-model>
*/
//样品点表参数，保存模型文件
CString CAtsSvr_TemplateServiceBase::GenerateDevDvm(const CString &strTaskSN, CDataGroup *pRatedParameter, CDataGroup *pDevDvm)
{
	CString strFileName, strPath;
	strFileName = strTaskSN + _T(".xml");
	strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol\\Library\\");  //模型文件统一存放在e-Protocol/Library根目录
	strPath += strFileName;

	CDvmDevice *pDvmDevice = new CDvmDevice();
	
	if (pRatedParameter != NULL)
	{
		CDvmDataset *pDevAttr = new CDvmDataset();
		pDevAttr->m_strName = _T("装置属性");
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
		pdsAin->m_strName = _T("测量数据集");
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
	strPath += _T("e-Protocol\\Library\\");  //模型文件统一存放在e-Protocol/Library根目录
	strPath += strFileName;

	CDvmDevice *pDvmDevice = new CDvmDevice();

	if (pRatedParas != NULL)
	{
		CDvmDataset *pDevAttr = new CDvmDataset();
		pDevAttr->m_strName = _T("装置属性");
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
		pdsAin->m_strName = _T("测量数据集");
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

//根据用户ID，查询用户名
BOOL CAtsSvr_TemplateServiceBase::QueryUserByUserID(long nUser_ID, CString &strName_User)
{
	CSys_User oUser;
	return oUser.QueryUserByUserID(g_pTheMySqlApp, nUser_ID, strName_User);
}

BOOL CAtsSvr_TemplateServiceBase::DB_InsertTemplateItems(const CString &strFileName, CExBaseList *pListItems)
{
	//先根据模板文件名（strFileName），查询iot_template表，获取模板的index_template
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
		//模板关联的大项，写入数据库表iot_template_items
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
				//测试小项，是测试大项下第一级分类节点
				//模板项目分类-子项表（iot_template_item）
				continue;
			}

			//大项关联的小项，写入数据库表iot_template_item
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

//模板关联的大项，写入数据库表iot_template_items
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

//模板关联的小项，写入数据库表iot_template_item
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

//待处理
BOOL CAtsSvr_TemplateServiceBase::DB_Insert_IotItems(CExBaseList *pListItems)
{
	BOOL bRet = TRUE;

	return bRet;
}

/*
<group id="BasicInfo" name="任务基本信息">
	<data id="TestType" name="检验类型" value="型式检验"/>
	<data id="SampleSN" name="样品编号" value="GJK20220207"/>
	<data id="SampleModel" name="样品型号" value="CQSJ"/>
	<data id="SampleName" name="样品名称" value="输电线路监测装置"/>
	<data id="ClientName" name="委托单位名称" value="科技有限公司"/>
	<data id="ClientAddress" name="委托单位地址" value="8号A栋"/>
	<data id="ManufactorName" name="制造单位名称" value="科技有限公司"/>
	<data id="ManufactorAddress" name="制造单位地址" value="8号A栋"/>
	<!--任务书中，相关信息缺失时，value属性填空-->
</group>
*/
//写数据库表iot_type_task，新建委托任务
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

//写数据库表iot_type_task，根据任务索引号，更新委托任务
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("查询委托任务表失败！[%d]"), nIndex_TypeTask);
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
<group id="InspectionBases" name="任务检验依据">
	<data id="InspectionBasis1" name="检验依据1" value="Q/GDW 12021-2019输变电设备物联网节点设备无线组网协议"/>
	<data id="Name" name="依据名称" value="PAL/BZ 12020-2020输变电设备物联网微功率无线网通信协议"/>
	<data id="Name" name="依据名称" value="PAL/BZ 12021-2020输变电设备物联网节点设备无线组网协议"/>
	<!--这边多少个检验依据，就有多少个data-->
</group>
*/
//写数据库表iot_type_task_standard
BOOL CAtsSvr_TemplateServiceBase::DB_InsertTypeTask_Standard(long nIndex_TypeTask, CDataGroup *pInspectionBases)
{
	//检验依据，允许为空
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

		//此处暂时不考虑去维护检验依据的总表（iot_test_standard）。
		//因为创建任务时，检验依据是从任务书中解析获得，而不是从总表中选择。
		pNew->m_strStandard_Name = pData->m_strValue;
		::GetLocalTime(&pNew->m_tmCreate_Time);
		pNew->m_nId = 0;

		if ( !pNew->DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("检验依据写入数据库失败！[%s]"), pData->m_strValue);
			bRet = FALSE;
		}
	}

	return bRet;
}

/*
<group id="SampleDevices" name="样品列表">
	<group id="SampleDevice1" name="样品1">
		<data id="DeviceSN" name="设备序列号" value="CQSJ2022110010"/>
		<data id="SampleSN" name="样品编号" value="GJK20220207-1"/>
		<!--如果样品信息文件中没有该信息，则返回的结构中不要包含“SmapleSN”字段-->
	</group>
	<group id="SampleDevice2" name="样品2">
		<data id="DeviceSN" name="设备序列号" value="CQSJ2022110011"/>
		<data id="SampleSN" name="样品编号" value="GJK20220207-2"/>
	</group>
	<!--这边多少个样品设备，就有多少个group-->
</group>
*/
//写数据库：任务样品表iot_type_task_dev
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

	//1、查询委托任务表iot_type_task，获取样品编号，更新样品数量
	BOOL bRet = TRUE;
	CIot_TypeTask* pTypeTask = new CIot_TypeTask();
	bRet = pTypeTask->UpdateSampleCnt(g_pTheMySqlApp, nIndex_TypeTask, pSampleDevices->GetCount());

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("更新委托任务表的样品数量失败！[%d]"), nIndex_TypeTask);
		delete pTypeTask;
		return NULL;
	}

	//2、样品信息中，若没有SampleSN字段，则需要根据委托任务的样品编号，自动更新：SampleSN-1，SampleSN-2……
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
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("委托任务样品【%s】的设备序列号为空！"), strSampleSN);
			bRet = FALSE;
			continue;
		}

		if (strSampleSN.IsEmpty())
		{
			//自动编号
			strSampleSN.Format(_T("%s-%d"), pTypeTask->m_strSn_Sample, nIndex);
		}

		CIot_TypeTaskDev oTypeTaskDev;
		oTypeTaskDev.m_nIndex_Task = pTypeTask->m_nIndex_Task;
		oTypeTaskDev.m_strSn_Sample_Dev = strDeviceSN;   //样品设备序列号
		oTypeTaskDev.m_strNumber_Sample_Dev = strSampleSN;   //样品编号

		if ( !oTypeTaskDev.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("委托任务样品【%s】，写入数据库失败！"), strSampleSN);
			bRet = FALSE;
		}
	}

	delete pTypeTask;
	return bRet;
}
 
/*
<group id="RatedParameter" name="额定参数">
	<data id="Power" name="功率" value="100" data-type="float" unit="W"/>
	<data id="Weight" name="重量" value="1.23" data-type="float" unit="kg"/>
	<!--这边多少个额定参数，就有多少个data。额定参数的id、name、value、data-type、unit属性，均从excel文件解析获得-->
</group>
*/
//额定参数写入数据库  iot_type_task_dev_paras
BOOL CAtsSvr_TemplateServiceBase::DB_InsertTypeTask_RatedParameter(long nIndex_TypeTask, CDataGroup *pRatedParameter)
{
	if (pRatedParameter == NULL)
	{
		//样品额定参数，允许为空
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
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("委托任务额定参数【%s】，写入数据库失败！"), pData->m_strName);
			bRet = FALSE;
			continue;
		}
	}

	return bRet;
}

/*
<group id="DevDvm" name="点表参数">
	<data id="RealTimeWindSpeed" name="实时风速" value="23.2" data-type="unsigned int" unit="m/s"/>
	<data id="RealTimeWindDir" name="实时风向" value="1.23" data-type="unsigned int" unit="度"/>
	<!--这边多少个点表参数，就有多少个data。额定参数的id、name、value、data-type、unit属性，均从excel文件解析获得-->
</group>
*/
//点表参数写入数据库  iot_type_task_dev_model
BOOL CAtsSvr_TemplateServiceBase::DB_InsertTypeTask_DevDvm(long nIndex_TypeTask, CDataGroup *pDevDvm)
{
	//点表参数不允许为空
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
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("委托任务点表参数【%s】，写入数据库失败！"), pData->m_strName);
			bRet = FALSE;
			continue;
		}
	}

	return bRet;
}

BOOL CAtsSvr_TemplateServiceBase::DB_InsertDeviceModel(const CString &strFile, const CString &strFile_s)
{
	CIot_DeviceModel oDeviceModel;
	//以下属性，暂时都设置为0。
	oDeviceModel.m_nIndex_Device_Classify = 0;
	oDeviceModel.m_nIndex_Device_Type = 0;
	oDeviceModel.m_nIndex_Factory = 0;
	oDeviceModel.m_nIndex_Model_Dir = 0;

	oDeviceModel.m_strFile_Name = strFile;
	oDeviceModel.m_strPath_Protocol_File = strFile_s;

	//模型文件的文件名，是以任务ID命名的，因此不用查询是否重复，直接存入库中
	return oDeviceModel.DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);
}
#endif
