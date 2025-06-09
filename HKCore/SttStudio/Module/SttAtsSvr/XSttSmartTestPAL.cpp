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
	<group name="������Ϣ" id="TaskInfo" data-type="" value="">
		<group name="���������Ϣ" id="BasicInfo" data-type="" value="">
			<data name="��������" id="TestType" data-type="" default-value="" value="��ʽ����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ʒ�ͺ�" id="SampleModel" data-type="" default-value="" value="CQSJ" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ʒ����" id="SampleName" data-type="" default-value="" value="�����·���װ��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="ί�е�λ����" id="ClientName" data-type="" default-value="" value="ί�пƼ����޹�˾" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="ί�е�λ��ַ" id="ClientAddress" data-type="" default-value="" value="8��A��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="���쵥λ����" id="ManufactorName" data-type="" default-value="" value="����Ƽ����޹�˾" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="���쵥λ��ַ" id="ManufactorAddress" data-type="" default-value="" value="8��B��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ʒ����" id="SampleCnt" data-type="" default-value="" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="����" id="MainInspection" data-type="" default-value="" value="����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="���" id="Checker" data-type="" default-value="" value="����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="У��" id="Proofreader" data-type="" default-value="" value="����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="����ģ���ļ�" id="DocFile" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).doc" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="����ģ���ļ�" id="TemplateFile" data-type="" default-value="" value="D:\Program Files\EPOTO\e-Report\Template\PowerSky.gbxml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="�����������" id="InspectionBases" data-type="" value="">
			<data name="��������" id="Name" data-type="" default-value="" value="Q/GDW 12021-2019�����豸�������ڵ��豸��������Э��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��������" id="Name" data-type="" default-value="" value="PAL/BZ 12020-2020�����豸������΢����������ͨ��Э��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��������" id="Name" data-type="" default-value="" value="PAL/BZ 12021-2020�����豸�������ڵ��豸��������Э��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
	<group name="��Ʒ��Ϣ" id="SampleInfo" data-type="" value="">
		<group name="��Ʒ�б�" id="SampleDevices" data-type="" value="">
			<group name="��Ʒ1" id="SampleDevice1" data-type="" value="">
				<data name="�豸���к�" id="DeviceSN" data-type="" default-value="" value="1234512345" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207-3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="��Ʒ2" id="SampleDevice2" data-type="" value="">
				<data name="�豸���к�" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110010" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207-1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="��Ʒ3" id="SampleDevice3" data-type="" value="">
				<data name="�豸���к�" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110011" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207-2" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
		<data name="��Ʒ��Ƭ" id="SamplePic" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).png" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<group name="�����" id="RatedParameter" data-type="" value="">
			<data name="����" id="Power" data-type="float" default-value="" value="100" unit="W" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="����" id="Weight" data-type="float" default-value="" value="1.23" unit="kg" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
	<group name="��������Ϣ" id="TestAppInfo" data-type="" value="">
		<group name="�������б�" id="TestApps" data-type="" value="">
			<group name="������1" id="TestApp1" data-type="" value="">
				<data name="����������" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�������ͺ�" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�����Ǳ��" id="TestAppSN" data-type="" default-value="" value="77778888" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ч��" id="ValidityTime" data-type="" default-value="" value="2023-7-20" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ӳ���汾��" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="������2" id="TestApp2" data-type="" value="">
				<data name="����������" id="TestAppName" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�������ͺ�" id="TestAppModel" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�����Ǳ��" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0004" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ч��" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ӳ���汾��" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
			<group name="������3" id="TestApp3" data-type="" value="">
				<data name="����������" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�������ͺ�" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�����Ǳ��" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0002" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ч��" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="��Ӳ���汾��" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
	</group>
	<group name="������Ϣ" id="TestInfo" data-type="" value="">
		<group name="�¶Ȳ���" id="TempTest" data-type="" value="">
			<group name="�¶�-55��" id="TempSet_55" data-type="macrotest" value="">
				<data name="��Ŀ·��" id="ItemPath" data-type="" default-value="" value="TempSet_55$55" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="����" id="Result" data-type="" default-value="" value="�ϸ�" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�����ļ�" id="ReportFile" data-type="" default-value="" value="D:\Program Files\EPOTO\IotAtsMngr\Workspace\Report\1234512345\2023_ 7_20(14_ 4_30)_Report.json" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
		<group name="ʪ�Ȳ���" id="HumiTest" data-type="" value="">
			<group name="ʪ��-30%RH" id="HumiSet_30" data-type="macrotest" value="">
				<data name="��Ŀ·��" id="ItemPath" data-type="" default-value="" value="HumiSet_30$30" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="����" id="Result" data-type="" default-value="" value="�ϸ�" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="�����ļ�" id="ReportFile" data-type="" default-value="" value="D:\Program Files\EPOTO\IotAtsMngr\Workspace\Report\1234512345\2023_ 7_20(14_ 4_30)_Report.json" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
	</group>
</paras>
*/
//�������棬��һ�������Ʒ������һ��word���档�����Ʒ�����Ӧ��ͬ�Ĳ�����Ŀ��ÿ����Ŀ���и��Եı����ļ�
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

	//������Ϣ�Ǳ�Ҫ��Ϣ
	if (pTaskInfo == NULL)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -2;
	}

	//���������Ϣ����Ҫ��Ϣ
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

	//������Ϣ�Ǳ�Ҫ��Ϣ
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

//������Ϣ��������Ŀ+���Ա���
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
	CDataGroup *pItems = NULL;   //���Դ���

	while (pos != NULL)
	{
		pItems = (CDataGroup *)pTestInfo->GetNext(pos);

		POS pos2 = pItems->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDataGroup *pRpt = (CDataGroup *)pItems->GetNext(pos2);  //����С��
			Pre_Ats_ExportReport_SingleRpt(pGuideBook, pRpt);
		}
	}

	return 0;
}

/*
<group name="������Ϣ" id="TaskInfo" data-type="" value="">
	<group name="���������Ϣ" id="BasicInfo" data-type="" value="">
		<data name="��������" id="TestType" data-type="" default-value="" value="��ʽ����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="��Ʒ�ͺ�" id="SampleModel" data-type="" default-value="" value="CQSJ" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="��Ʒ����" id="SampleName" data-type="" default-value="" value="�����·���װ��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="ί�е�λ����" id="ClientName" data-type="" default-value="" value="ί�пƼ����޹�˾" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="ί�е�λ��ַ" id="ClientAddress" data-type="" default-value="" value="8��A��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="���쵥λ����" id="ManufactorName" data-type="" default-value="" value="����Ƽ����޹�˾" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="���쵥λ��ַ" id="ManufactorAddress" data-type="" default-value="" value="8��B��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="��Ʒ����" id="SampleCnt" data-type="" default-value="" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="����" id="MainInspection" data-type="" default-value="" value="����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="���" id="Checker" data-type="" default-value="" value="����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="У��" id="Proofreader" data-type="" default-value="" value="����" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="����ģ���ļ�" id="DocFile" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).doc" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="����ģ���ļ�" id="TemplateFile" data-type="" default-value="" value="D:\Program Files\EPOTO\e-Report\Template\PowerSky.gbxml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</group>
	<group name="�����������" id="InspectionBases" data-type="" value="">
		<data name="��������" id="Name" data-type="" default-value="" value="Q/GDW 12021-2019�����豸�������ڵ��豸��������Э��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="��������" id="Name" data-type="" default-value="" value="PAL/BZ 12020-2020�����豸������΢����������ͨ��Э��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="��������" id="Name" data-type="" default-value="" value="PAL/BZ 12021-2020�����豸�������ڵ��豸��������Э��" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</group>
</group>
*/
//����������Ϣ
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

	//���������Ϣ����Ϊȫ�����ݴ���
	if (pBasicInfo != NULL)
	{
		pGuideBook->SetGlobalDatas_GlobalDatas(pBasicInfo);
	}

	CDataGroup *pInspectionBases = (CDataGroup *)pTaskInfo->FindByID(XPARA_ID_InspectionBases);
	
	//����������ݣ��ϲ���һ����������
	if (pInspectionBases != NULL)
	{
		pGuideBook->SetGlobalDatas_InspectionBases_Ex(pInspectionBases);
	}

	return 0;
}

/*
<group name="��Ʒ��Ϣ" id="SampleInfo" data-type="" value="">
	<group name="��Ʒ�б�" id="SampleDevices" data-type="" value="">
		<group name="��Ʒ1" id="SampleDevice1" data-type="" value="">
			<data name="�豸���к�" id="DeviceSN" data-type="" default-value="" value="1234512345" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207-3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="��Ʒ2" id="SampleDevice2" data-type="" value="">
			<data name="�豸���к�" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110010" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207-1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="��Ʒ3" id="SampleDevice3" data-type="" value="">
			<data name="�豸���к�" id="DeviceSN" data-type="" default-value="" value="CQSJ2022110011" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ʒ���" id="SampleSN" data-type="" default-value="" value="GJK20220207-2" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
	<data name="��Ʒ��Ƭ" id="SamplePic" data-type="" default-value="" value="d:\Program Files\EPOTO\IotAtsMngr\Workspace\XXX._(2023 721_1520 3).png" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<group name="�����" id="RatedParameter" data-type="" value="">
		<data name="����" id="Power" data-type="float" default-value="" value="100" unit="W" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="����" id="Weight" data-type="float" default-value="" value="1.23" unit="kg" min="" max="" format="" index="0" time="0" change="0" step="" />
	</group>
</group>
*/
//������Ʒ��Ϣ
//��Ʒ��Ϣ��Ŀǰֻ��һ������ƷͼƬ
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
		//��ƷͼƬ���ŵ�ȫ�����ݡ�ͬʱ������ID���������file���ؼ��֣�����д����ʱ������ΪͼƬ����
		pGuideBook->m_pGlobalDatas->AddNew2(_T("��ƷͼƬ"), _T("SamplePic_file"), _T("")
			, _T("string"), pSamplePic->m_strValue, _T(""), FALSE);

		CString strFile;
		strFile = pSamplePic->m_strID + _T("_file");  //����ͼƬ�ļ����̶���׺
		pGuideBook->AddReportData(strFile, pSamplePic->m_strValue);
	}

	return 0;
}

/*
<group name="��������Ϣ" id="TestAppInfo" data-type="" value="">
	<group name="�������б�" id="TestApps" data-type="" value="">
		<group name="������1" id="TestApp1" data-type="" value="">
			<data name="����������" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="�������ͺ�" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="�����Ǳ��" id="TestAppSN" data-type="" default-value="" value="77778888" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ч��" id="ValidityTime" data-type="" default-value="" value="2023-7-20" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ӳ���汾��" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="������2" id="TestApp2" data-type="" value="">
			<data name="����������" id="TestAppName" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="�������ͺ�" id="TestAppModel" data-type="" default-value="" value="SU1200C" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="�����Ǳ��" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0004" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ч��" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ӳ���汾��" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="������3" id="TestApp3" data-type="" value="">
			<data name="����������" id="TestAppName" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="�������ͺ�" id="TestAppModel" data-type="" default-value="" value="C-70/1000" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="�����Ǳ��" id="TestAppSN" data-type="" default-value="" value="PAL/P-HJ.0002" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ч��" id="ValidityTime" data-type="" default-value="" value="2023-9-6" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="��Ӳ���汾��" id="Version" data-type="" default-value="" value="/" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</group>
</group>
*/
//����������Ϣ
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

	//�����ݹ����Ĳ����Ƕ��壬ÿһ��������ת��һ��CDvmData����ŵ�oTestApp����
	//�����ǵĶ���ÿ�����������磺DeviceSN��remote-ip�ȣ���Ϊһ��CDvmValue��š�
	//��ҪExpandData.xml�ж���Ĳ����ǣ���(CDataGroup *)p�ж���Ĳ���һ��
	CDvmDataset oTestApp;
	POS pos = pTestApps->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pTestApp = (CDataGroup *)pTestApps->GetNext(pos);  //ÿһ��group����Ӧһ��������
		CDvmData *pNew = new CDvmData();
		oTestApp.AddNewChild(pNew);

		POS pos2 = pTestApp->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDvmData *pData = (CDvmData *)pTestApp->GetNext(pos2);  //ÿһ��data����Ӧ�����ǵ�һ������
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
