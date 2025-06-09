#include "stdafx.h"
#include "XSttSmartTestPAL.h"
#include "../Engine/SttNativeTestEngine.h"
#include "../SttCmd/GuideBook/SttCmdGuideBookTransTool.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXSmartTestPAL* CXSmartTestPAL::g_pXSttSmartTestPAL = NULL;
long CXSmartTestPAL::g_nXSttSmartTestPALRef = 0;
extern CSttGuideBookGenServer g_oSttGuideBookGenServer; 

CXSmartTestPAL::CXSmartTestPAL()
{
	CString strSysPath;
	strSysPath = _P_GetInstallPath();
	strSysPath += _T("STT/");
	g_oSttGuideBookGenServer.InitGbGenSysPath(strSysPath);  //2022-3-29  lijunqing SmartTest
	CSttMacroTestUI_TestMacroUIDB::Create(strSysPath);
	CGbItemsGenRuleDefMngrXmlRWKeys::Create();
}

CXSmartTestPAL::~CXSmartTestPAL()
{
	CGbItemsGenRuleDefMngrXmlRWKeys::Release();
	CSttMacroTestUI_TestMacroUIDB::Release();
}

CXSmartTestPAL* CXSmartTestPAL::Create()
{
	g_nXSttSmartTestPALRef++;

	if (g_nXSttSmartTestPALRef == 1)
	{
		g_pXSttSmartTestPAL = new CXSmartTestPAL();
		g_theSttSmartTest = g_pXSttSmartTestPAL;
	}

	return g_pXSttSmartTestPAL;
}

void CXSmartTestPAL::Release()
{
	g_nXSttSmartTestPALRef--;

	if (g_nXSttSmartTestPALRef == 0)
	{
		delete g_pXSttSmartTestPAL;
		g_pXSttSmartTestPAL = NULL;
		g_theSttSmartTest = NULL;
	}
}

long CXSmartTestPAL::Pre_Ats_ExportReport(CSttAtsCmd *pAtsCmd)
{
	return CSttSmartTest::Pre_Ats_ExportReport(pAtsCmd);
}

long CXSmartTestPAL::Pre_Ats_ExportReport_single(CSttAtsCmd *pAtsCmd)
{
	return -1;
}

long CXSmartTestPAL::Pre_Ats_ExportReport_docs(CSttAtsCmd *pAtsCmd)
{
	return -1;
}

/*
<paras name="" id="">
	<group name="任务信息" id="TaskInfo" data-type="" value="">
		<group name="任务基本信息" id="BasicInfo" data-type="" value="">
			<data name="检验类型" id="TestType" data-type="" default-value="" value="型式检验" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="样品型号" id="SampleModel" data-type="" default-value="" value="CQSJ" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="样品名称" id="SampleName" data-type="" default-value="" value="输电线路监测装置" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="委托单位名称" id="ClientName" data-type="" default-value="" value="委托科技有限公司" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="委托单位地址" id="ClientAddress" data-type="" default-value="" value="8号A栋" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="制造单位名称" id="ManufactorName" data-type="" default-value="" value="制造科技有限公司" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="制造单位地址" id="ManufactorAddress" data-type="" default-value="" value="8号B栋" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="样品数量" id="SampleCnt" data-type="" default-value="" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="主检" id="MainInspection" data-type="" default-value="" value="张三" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="审核" id="Checker" data-type="" default-value="" value="李四" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="校对" id="Proofreader" data-type="" default-value="" value="王五" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="报告模板文件" id="DocFile" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).doc" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="测试模板文件" id="TemplateFile" data-type="" default-value="" value="D:\Program Files\EPOTO\e-Report\Template\PowerSky.gbxml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="任务检验依据" id="InspectionBases" data-type="" value="">
			<data name="依据名称" id="Name" data-type="" default-value="" value="Q/GDW 12021-2019输变电设备物联网节点设备无线组网协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="依据名称" id="Name" data-type="" default-value="" value="PAL/BZ 12020-2020输变电设备物联网微功率无线网通信协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="依据名称" id="Name" data-type="" default-value="" value="PAL/BZ 12021-2020输变电设备物联网节点设备无线组网协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
	<group name="样品信息" id="SampleInfo" data-type="" value="">
		<group name="样品列表" id="SampleDevices" data-type="" value="">
			<group name="样品1" id="SampleDevice1" data-type="" value="">
				<data name="设备序列号" id="DeviceSN" data-type="" default-value="" value="1234512345" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207-3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="样品2" id="SampleDevice2" data-type="" value="">
				<data name="设备序列号" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110010" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207-1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="样品3" id="SampleDevice3" data-type="" value="">
				<data name="设备序列号" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110011" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207-2" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
		<data name="样品照片" id="SamplePic" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).png" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<group name="额定参数" id="RatedParameter" data-type="" value="">
			<data name="功率" id="Power" data-type="float" default-value="" value="100" unit="W" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="重量" id="Weight" data-type="float" default-value="" value="1.23" unit="kg" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
	<group name="测试仪信息" id="TestAppInfo" data-type="" value="">
		<group name="测试仪列表" id="TestApps" data-type="" value="">
			<group name="测试仪1" id="TestApp1" data-type="" value="">
				<data name="测试仪名称" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="测试仪型号" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="测试仪编号" id="TestAppSN" data-type="" default-value="" value="77778888" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="有效期" id="ValidityTime" data-type="" default-value="" value="2023-7-20" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="软硬件版本号" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="测试仪2" id="TestApp2" data-type="" value="">
				<data name="测试仪名称" id="TestAppName" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="测试仪型号" id="TestAppModel" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="测试仪编号" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0004" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="有效期" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="软硬件版本号" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="测试仪3" id="TestApp3" data-type="" value="">
				<data name="测试仪名称" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="测试仪型号" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="测试仪编号" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0002" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="有效期" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="软硬件版本号" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
	</group>
	<group name="测试信息" id="TestInfo" data-type="" value="">
		<group name="温度测试" id="TempTest" data-type="" value="">
			<group name="温度-55度" id="TempSet_55" data-type="macrotest" value="">
				<data name="项目路径" id="ItemPath" data-type="" default-value="" value="TempSet_55$55" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="结论" id="Result" data-type="" default-value="" value="合格" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="报告文件" id="ReportFile" data-type="" default-value="" value="D:\Program Files\EPOTO\IotAtsMngr\Workspace\Report\1234512345\2023_ 7_20(14_ 4_30)_Report.json" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
		<group name="湿度测试" id="HumiTest" data-type="" value="">
			<group name="湿度-30%RH" id="HumiSet_30" data-type="macrotest" value="">
				<data name="项目路径" id="ItemPath" data-type="" default-value="" value="HumiSet_30$30" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="结论" id="Result" data-type="" default-value="" value="合格" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="报告文件" id="ReportFile" data-type="" default-value="" value="D:\Program Files\EPOTO\IotAtsMngr\Workspace\Report\1234512345\2023_ 7_20(14_ 4_30)_Report.json" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
	</group>
</paras>
*/
//导出报告，是一个大的样品，导出一份word报告。大的样品，会对应不同的测试项目，每个项目都有各自的报告文件
long CXSmartTestPAL::Pre_Ats_ExportReport_gbrpts(CSttAtsCmd *pAtsCmd)
{
	if (m_pTestControl == NULL)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -1;
	}

	CDataGroup *pTaskInfo = (CDataGroup*)pAtsCmd->FindInParasByID(XPARA_Val_Export_Para_TaskInfo);
	CDataGroup *pTestInfo = (CDataGroup*)pAtsCmd->FindInParasByID(XPARA_Val_Export_Para_TestInfo);
	CDataGroup *pSampleInfo = (CDataGroup*)pAtsCmd->FindInParasByID(XPARA_Val_Export_Para_SampleInfo);
	CDataGroup *pTestAppInfo = (CDataGroup*)pAtsCmd->FindInParasByID(XPARA_Val_Export_Para_TestAppInfo);

	//任务信息是必要信息
	if (pTaskInfo == NULL)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -2;
	}

	//任务基本信息，必要信息
	CDataGroup *pBasicInfo = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_BASICINFO);

	if (pBasicInfo == NULL)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -3;
	}

	CString strGbXmlFile, strDeviceSN;
	pBasicInfo->GetDataValue(XPARA_ID_GBXMLFILE, strGbXmlFile);
	pBasicInfo->GetDataValue(XPARA_ID_SampleSN, strDeviceSN);

	g_bInXTestDbGenReprtState = TRUE;

	if (! m_pTestControl->CreateTest(strGbXmlFile, 1, FALSE))
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		g_bInXTestDbGenReprtState = FALSE;
		return -3;
	}

	g_bInXTestDbGenReprtState = FALSE;

	//测试信息是必要信息
	if (pTestInfo == NULL)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -4;
	}

	m_pTestControl->m_pGuideBook->GBS_SetGlobal_Str(DATAID_DEVICESN, strDeviceSN);
	Pre_Ats_ExportReport_TestInfo(m_pTestControl, pTestInfo);
	Pre_Ats_ExportReport_TaskInfo(m_pTestControl, pTaskInfo);
	Pre_Ats_ExportReport_SampleInfo(m_pTestControl, pSampleInfo);
	Pre_Ats_ExportReport_TestAppInfo(m_pTestControl, pTestAppInfo);

	Gb_SetGbModifiedFlag(m_pTestControl->m_pGuideBook, TRUE);
	m_pTestControl->SaveBinaryFile();

	//for debug
	//m_pTestControl->m_pGuideBook->SaveXMLFile(_T("D:\\0\\SENSORTEST.GBXML"));
	return 0;
}

//测试信息：测试项目+测试报告
long CXSmartTestPAL::Pre_Ats_ExportReport_TestInfo(CTestControlBase *pTestControl, CDataGroup *pTestInfo)
{
	if (pTestInfo == NULL)
	{
		return -1;
	}

	if (pTestInfo->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return -2;
	}

	CGuideBook *pGuideBook = pTestControl->m_pGuideBook;
	POS pos = pTestInfo->GetHeadPosition();
	CDataGroup *pItems = NULL;   //测试大项

	while (pos != NULL)
	{
		pItems = (CDataGroup *)pTestInfo->GetNext(pos);

		POS pos2 = pItems->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDataGroup *pRpt = (CDataGroup *)pItems->GetNext(pos2);  //测试小项
			Pre_Ats_ExportReport_SingleRpt(pGuideBook, pRpt);
		}
	}

	return 0;
}

/*
<group name="任务信息" id="TaskInfo" data-type="" value="">
	<group name="任务基本信息" id="BasicInfo" data-type="" value="">
		<data name="检验类型" id="TestType" data-type="" default-value="" value="型式检验" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="样品型号" id="SampleModel" data-type="" default-value="" value="CQSJ" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="样品名称" id="SampleName" data-type="" default-value="" value="输电线路监测装置" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="委托单位名称" id="ClientName" data-type="" default-value="" value="委托科技有限公司" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="委托单位地址" id="ClientAddress" data-type="" default-value="" value="8号A栋" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="制造单位名称" id="ManufactorName" data-type="" default-value="" value="制造科技有限公司" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="制造单位地址" id="ManufactorAddress" data-type="" default-value="" value="8号B栋" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="样品数量" id="SampleCnt" data-type="" default-value="" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="主检" id="MainInspection" data-type="" default-value="" value="张三" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="审核" id="Checker" data-type="" default-value="" value="李四" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="校对" id="Proofreader" data-type="" default-value="" value="王五" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="报告模板文件" id="DocFile" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).doc" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="测试模板文件" id="TemplateFile" data-type="" default-value="" value="D:\Program Files\EPOTO\e-Report\Template\PowerSky.gbxml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</group>
	<group name="任务检验依据" id="InspectionBases" data-type="" value="">
		<data name="依据名称" id="Name" data-type="" default-value="" value="Q/GDW 12021-2019输变电设备物联网节点设备无线组网协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="依据名称" id="Name" data-type="" default-value="" value="PAL/BZ 12020-2020输变电设备物联网微功率无线网通信协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="依据名称" id="Name" data-type="" default-value="" value="PAL/BZ 12021-2020输变电设备物联网节点设备无线组网协议" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</group>
</group>
*/
//测试任务信息
long CXSmartTestPAL::Pre_Ats_ExportReport_TaskInfo(CTestControlBase *pTestControl, CDataGroup *pTaskInfo)
{
	if (pTaskInfo == NULL)
	{
		return -1;
	}

	if (pTaskInfo->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return -2;
	}

	CGuideBook *pGuideBook = pTestControl->m_pGuideBook;
	CDataGroup *pBasicInfo = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_BASICINFO);

	//任务基本信息，作为全局数据处理
	if (pBasicInfo != NULL)
	{
		pGuideBook->SetGlobalDatas_GlobalDatas(pBasicInfo);
	}

	CDataGroup *pInspectionBases = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_InspectionBases);
	
	//任务检验依据，合并成一个报告数据
	if (pInspectionBases != NULL)
	{
		pGuideBook->SetGlobalDatas_InspectionBases_Ex(pInspectionBases);
	}

	return 0;
}

/*
<group name="样品信息" id="SampleInfo" data-type="" value="">
	<group name="样品列表" id="SampleDevices" data-type="" value="">
		<group name="样品1" id="SampleDevice1" data-type="" value="">
			<data name="设备序列号" id="DeviceSN" data-type="" default-value="" value="1234512345" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207-3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="样品2" id="SampleDevice2" data-type="" value="">
			<data name="设备序列号" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110010" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207-1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="样品3" id="SampleDevice3" data-type="" value="">
			<data name="设备序列号" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110011" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="样品编号" id="SampleSN" data-type="" default-value="" value="GJK20220207-2" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
	<data name="样品照片" id="SamplePic" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).png" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<group name="额定参数" id="RatedParameter" data-type="" value="">
		<data name="功率" id="Power" data-type="float" default-value="" value="100" unit="W" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="重量" id="Weight" data-type="float" default-value="" value="1.23" unit="kg" min="" max="" format="" index="0" time="0" change="0" step="" />
	</group>
</group>
*/
//测试样品信息
//样品信息，目前只放一个：样品图片
long CXSmartTestPAL::Pre_Ats_ExportReport_SampleInfo(CTestControlBase *pTestControl, CDataGroup *pSampleInfo)
{
	if (pSampleInfo == NULL)
	{
		return -1;
	}

	if (pSampleInfo->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return -2;
	}

	CGuideBook *pGuideBook = pTestControl->m_pGuideBook;
	CDvmData *pSamplePic = (CDvmData *)pSampleInfo->FindByID(XPARA_ID_SamplePic);

	if (pSamplePic != NULL)
	{
		//样品图片，放到全局数据。同时，数据ID必须包含“file”关键字，在填写报告时才能作为图片处理
		pGuideBook->m_pGlobalDatas->AddNew2(_T("样品图片"), _T("SamplePic_file"), _T("")
			, _T("string"), pSamplePic->m_strValue, _T(""), FALSE);

		CString strFile;
		strFile = pSamplePic->m_strID + _T("_file");  //对于图片文件，固定后缀
		pGuideBook->AddReportData(strFile, pSamplePic->m_strValue);
	}

	return 0;
}

/*
<group name="测试仪信息" id="TestAppInfo" data-type="" value="">
	<group name="测试仪列表" id="TestApps" data-type="" value="">
		<group name="测试仪1" id="TestApp1" data-type="" value="">
			<data name="测试仪名称" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="测试仪型号" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="测试仪编号" id="TestAppSN" data-type="" default-value="" value="77778888" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="有效期" id="ValidityTime" data-type="" default-value="" value="2023-7-20" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="软硬件版本号" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="测试仪2" id="TestApp2" data-type="" value="">
			<data name="测试仪名称" id="TestAppName" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="测试仪型号" id="TestAppModel" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="测试仪编号" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0004" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="有效期" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="软硬件版本号" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="测试仪3" id="TestApp3" data-type="" value="">
			<data name="测试仪名称" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="测试仪型号" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="测试仪编号" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0002" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="有效期" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="软硬件版本号" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
</group>
*/
//测试仪器信息
long CXSmartTestPAL::Pre_Ats_ExportReport_TestAppInfo(CTestControlBase *pTestControl, CDataGroup *pTestAppInfo)
{
	if (pTestAppInfo == NULL)
	{
		return -1;
	}

	if (pTestAppInfo->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return -2;
	}

	CGuideBook *pGuideBook = pTestControl->m_pGuideBook;
	CDataGroup *pTestApps = (CDataGroup *)pTestAppInfo->FindByID(XPARA_ID_TestApps);

	//将传递过来的测试仪定义，每一个测试仪转成一个CDvmData。存放到oTestApp对象
	//测试仪的定义每个参数，例如：DeviceSN、remote-ip等，作为一个CDvmValue存放。
	//需要ExpandData.xml中定义的测试仪，与(CDataGroup *)p中定义的参数一致
	CDvmDataset oTestApp;
	POS pos = pTestApps->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pTestApp = (CDataGroup *)pTestApps->GetNext(pos);  //每一个group，对应一个测试仪
		CDvmData *pNew = new CDvmData();
		oTestApp.AddNewChild(pNew);

		POS pos2 = pTestApp->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDvmData *pData = (CDvmData *)pTestApp->GetNext(pos2);  //每一个data，对应测试仪的一个属性
			pNew->AddValue(pData->m_strName, pData->m_strID, pData->m_strValue);
		}
	}

	pGuideBook->SetGlobalDatas_TestApp(&oTestApp);
	return 0;
}

long CXSmartTestPAL::Pre_Ats_ExportReport_SingleRpt(CGuideBook *pGuideBook, CDataGroup *pRpt)
{
	CString strItemPath, strRptFile;
	pRpt->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath);
	pRpt->GetDataValue(XPARA_Val_Export_Para_ReportFile, strRptFile);

	CGbItemBase *pGbItem = (CGbItemBase*)Gb_GetItem(pGuideBook, strItemPath);

	if (pGbItem == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("item-path [%s] error"), strItemPath.GetString());
		return -1;
	}

	CSttSysState oSysState;
	FILE *pFile = fopen(strRptFile.GetString(), "r");

	if (pFile == NULL)
	{
		return -1;
	}

	char pBuff[4];
	fread(pBuff, 1, 2, pFile);
	fclose(pFile);

	if (pBuff[0] == '<')
	{
		oSysState.OpenXmlFile(strRptFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys, _PUGI_XML_TYPE_);
	}
	else
	{
		oSysState.OpenXmlFile(strRptFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
	}

	CSttParas *pParas = oSysState.GetSttParas();
	CSttReports *pSttReports = pParas->GetSttReports();
	CReports *pReports = pGbItem->GetReports();
	pGbItem->m_nEnable = 1;
	Gb_SetGbModifiedFlag(pGbItem, TRUE);

	CItemContainer *pContainer = (CItemContainer *)m_pTestControl->m_pItemContainer;
	pContainer->m_oListItems.AddTail(pGbItem);

	CSttCmdGuideBookTransTool oTool;
	pReports->DeleteAll();
	oTool.ReverseTrans(pReports, pSttReports);
	
	return 0;
}
