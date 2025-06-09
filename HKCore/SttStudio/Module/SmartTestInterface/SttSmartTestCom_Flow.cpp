#include "stdafx.h"
#include "SttSmartTestCom_Flow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSttSmartTestCom_Flow, CWnd)

CSttSmartTestCom_Flow::CSttSmartTestCom_Flow()
{

}

CSttSmartTestCom_Flow::~CSttSmartTestCom_Flow()
{

}

/*
<ats-cmd name="" id="CreateTest" testor="" >
    <paras name="" id="">
        <data id="test-id" value="" /> �����Ա�ʶ��
+���Զ��壺
        <data id="gbxml-file" value="*.ppxml" /> ����Լģ���ļ���
        <data name="EngineProgID" id="EngineProgID" value=""/>
        <data id="ppxml-file" value="*.ppxml" /> ����Լģ���ļ���
        <data id="dvm-file" value="*.xml" />  ������ļ���
        <data id="cmm-cfg-file" value="*.xml" />  ��ͨ�ŵ�ַ�����ļ���
        <group id="omm-config" >  ��ͨ�ŵ�ַ���á�
            ...........................
        </group>
���ߣ�
        <data id="TestDefine" value="" ><![CADATA[   �������ԵĶ���  ]]></data>
    </paras>
</ats -cmd>
*/

/*
<ats-cmd name="" id="CreateTest" testor="">
	<paras>
		<data name="����ģ��" id="gbxml-file" value="SZNR-TTU.gbexe"/>
		<data name="����ģ��" id="gbxml-file_s" value="����������"/>    //e-Report/Template
		�����²��ּ����ϰ汾���ݸ�ʽ��
		<data name="" id="DeviceID" data-type="" value="SZNR-TTU"/>
		<data name="�����ļ�" id="ppxml-file" value="SZNR-TTU.ppxml"/>
		<data name="ģ���ļ�" id="dvm-file" value="SZNR-TTU.xml"/>
		<data name="�����¼�ļ�" id="gbrpt-file" value="SZNR-TTU202012131427"/>
		<data name="����װ������" id="EngineProgID" value="PpEngine"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
		�����²���Ϊ���������豸�Լ������豸��Ϣ��
		<group id="devices">
			<group id="device">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="PpEngine"/>
				<data name="�����ļ�" id="ppxml-file" value="SZNR-TTU.ppxml"/>
				<data name="�����ļ�" id="ppxml-file_s" value="���� "/>  //e-Protocol/Template
				<data id="dvm-file" value="SZNR-TTU.xml"/>
				<data id="dvm-file_s" value="���� "/>   //e-Protocol/Library;[�̶���·�����������ԡ��༭ģ�嶼�����·����]
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			����
		</group>
		<group id="test-apps">
			<group id="test-app">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="IotVm"/>
				<data id="dvm-file" value="MacroTest.xml"/>
				<data id="dvm-file_s" value="���� "/>   //�����ǲ���Ҫ���
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			����
		</group>
	</paras>
</ats-cmd>
*/
//���û�д��ݲ���ģ����������ʾ�����в��Լ�¼�����򴴽��µĲ��Լ�¼
long CSttSmartTestCom_Flow::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	//�ȵ��û���Ĵ������ԣ�������������
	return CSttSmartTestCom::Ats_CreateTest(oAtsCmdDrv, pSttProtocol);
// 	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
// 
// 	CSttParas *pParas = pAtsCmd->GetSttParas();
// 	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
// 
// 	//pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);
// 	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
// 
// 	if (pDevices != NULL)
// 	{
// 		m_pDevices = (CDataGroup *)pDevices->CloneEx(TRUE, TRUE);
// 
// 		if (m_strDeviceSN.IsEmpty() && m_pDevices != NULL)
// 		{
// 			CDataGroup *pFirstDevice = (CDataGroup *)m_pDevices->GetHead();
// 			pFirstDevice->GetDataValue(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
// 		}
// 	}
// 
// 	CSttSysState oSysState;
// 	CSttParas *pParasReturn = oSysState.GetSttParas();
// 	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
// 
// 	ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 
// 	if (m_pXSmartTestClient == NULL)
// 	{
// 		InitSmartTestCom();
// 	}
// 
// 	if (m_pXSmartTestClient == NULL)
// 	{
// 		ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 		return -1;
// 	}
// 
// 	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("���ڴ������ԣ����Ժ󡭡�"));
// 	
// 	//2021-8-4  lijunqing   
// 	m_pXSmartTestClient->AddEventSink(_T("SmartTestService.TestEventSink"), m_strDeviceSN);
// 
//     long nRet = m_pXSmartTestClient->CreateTest(pParas);
// 
// 	if (nRet != SMART_TEST_COM_EXEC_SUCC)
// 	{
// 		ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 		return -1;
// 	}
// 	else
// 	{
// 		//�����ɹ�����Ҫ����gbrpt-file
// // 		CString strGbrptFile;  //��λ�ȡ��
// // 		pParasReturn->AddNewData(XPARA_ID_GBRPTFILE, strGbrptFile);
// 		ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 	}
// 
// 	return nRet;
}

long CSttSmartTestCom_Flow::Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	CString strDeviceSN;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_ConfigTest);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench);
		return -1;
	}

	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pTestApps = (CDataGroup *)pParas->FindByID(XPARA_ID_test_apps);
	CString  strTestApps;

	if (pTestApps != NULL)
	{
		POS pos = pTestApps->GetHeadPosition();
		pTestApps->m_strDataType = XPARA_ID_test_apps;
		CDataGroup *pTestApp = NULL;

		while (pos != NULL)
		{
			pTestApp = (CDataGroup *)pTestApps->GetNext(pos);
			pTestApp->m_strDataType = XPARA_ID_test_app;
		}

		pTestApps->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strTestApps);
	}

	long nRet = m_pXSmartTestClient->ConfigTest(strDeviceSN, strTestApps);

	if ( nRet < 0)
	{
		pParasReturn->m_strTextParasID.Empty();
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench);
		return -1;
	}
	else
	{

		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench);
	}

	return 0;
}