#include "stdafx.h"
#include "IotVmAppBase.h"
#include "../../Module/DataMngr/DvmDataset.h"
#include "../../SttStudio/Module/SttCmd/SttParas.h"
#include "SttMqttClientEngineConfig.h"

#include "../../Module/TestMacro/TestMacroInterface.h"
#include "..\..\Module\TestMacro\TestMacrosFileMngr.h"

CIotVmAppBase *g_theIotVmApp = NULL;

CIotVmAppBase::CIotVmAppBase()
{
	g_theIotVmApp = this;
}

CIotVmAppBase::~CIotVmAppBase()
{
	RemoveAll();
}

void CIotVmAppBase::InitIotVmBase()
{
	CDataMngrXmlRWKeys::Create();
	CTestMacroXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CCfgDataMngrConstGlobal::Create();
	CSttCmdDefineXmlRWKeys::Create();

	CString strFile = _P_GetConfigPath();
	strFile += _T("SttMqttClientEngineCfg.xml");
	CSttMqttClientEngineConfig::Create(strFile);

	CTestMacrosFileMngr::Create(TRUE);
	TM_CreateTestMacros();
}

void CIotVmAppBase::ExitIotVmBase()
{
	CSttMqttClientEngineConfig::Release();

	CSttCmdDefineXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CTestMacroXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	TM_ReleaseTestMacros();
	CTestMacrosFileMngr::Release();
}

/*********************
<dataset>
	<data id=”TestSN” value=”$$$$$$$$”/>
	<data id=”SN” value=”$$$$$$$$”/>
	<data id=”devCode” value=123456123456”/>
	<data id=”devType” value=”0”/>
	<data id=”MacroFile” value=”##/TestMacro.xml”/>
</dataset>
*********************/
/*********************
<group id="test-app">
	<data id="DeviceSN" name="" value="YRQ010101"/>
	<data id="EngineProgID" name="" value="IotVm.TestEngine"/>
	<data id="dvm-file" name="" value="SensorTestMacro.xml"/>
	<data id="dvm-file_s" name="" value="/profile/upload/2021/07/31/3de40090da2d47cc9737158ce5e66bde.xml"/>
	<data id="remote-ip" name="" value="192.168.134.112"/>
	<data id="remote-port" name="" value="2049"/>
</group>
********************/

/*********************
g_theAtsNewTestTool->m_pTestApp;传递的数据集//一个data表示一个测试仪
<dataset>
	<data id="" name="" value="">      
		<value id="DeviceSN" name="" value="YRQ010101"/>
		<value id="EngineProgID" name="" value="IotVm.TestEngine"/>
		<value id="dvm-file" name="" value="SensorTestMacro.xml"/>
		<value id="dvm-file_s" name="" value="/profile/upload/2021/07/31/3de40090da2d47cc9737158ce5e66bde.xml"/>
		<value id="remote-ip" name="" value="192.168.134.112"/>
		<value id="remote-port" name="" value="2049"/>
		<value id="MacroFile" name="" value="D:\Program Files\EPOTO\e-Report\Config\SensorTest\SensorTestMacro.xml"/>
	</data>
</dataset>
*********************/
CIotTestCtrlBase *CIotVmAppBase::CreateIotTestCtrl(const CString &strConfig)
{
	CExBaseList *pDatas = CreateConfigDatas(strConfig);

	if (pDatas == NULL)
	{
		return NULL;
	}

	CString strMacroFile, strDeviceSN, strEngineProgID, strRemoteIP, strProtocolID;
	long nRemotePort = 8998;
	long nDeviceType = 0;
	//stt_GetDataValueByID(pDatas, _T("SN"), strSN);
	//stt_GetDataValueByID(pDatas, _T("MacroFile"), strMacroFile);
	//stt_GetDataValueByID(pDatas, STT_CMD_PARA_DeviceSN, strDeviceSN);
	//stt_GetDataValueByID(pDatas, _T("devType"), nDeviceType);
	CExBaseObject *pTestApp = pDatas->GetHead();

	if (pTestApp->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CDvmData *pData = (CDvmData *)pTestApp;
		pData->GetChildValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
		pData->GetChildValueByID(STT_CMD_PARA_MacroFile, strMacroFile);
		pData->GetChildValueByID(STT_CMD_PARA_EngineProgID, strEngineProgID);
		pData->GetChildValueByID(XPARA_ID_Remote_ip, strRemoteIP);
		pData->GetChildValueByID(XPARA_ID_Remote_port, nRemotePort);
		pData->GetChildValueByID(STT_CMD_PARA_ProtocolID, strProtocolID);
	}
	else if (pTestApp->GetClassID() == DTMCLASSID_CSHORTDATA)
	{
		//可以暂时不考虑是CShortData的
		CShortData *pData = (CShortData *)pTestApp;
	}

	CIotTestCtrlBase *pTestCtrl = NULL;

	if (strDeviceSN.IsEmpty())
	{//电力测试仪
		pTestCtrl = new CIotTestCtrlBase;
	}
	else
	{//物联测试仪
		pTestCtrl = new CIotTestCtrl;
		((CIotTestCtrl *)pTestCtrl)->SetIotDevice(strDeviceSN,nDeviceType);
	}

	pTestCtrl->m_pTestMacros = TM_GetTestMacros(strMacroFile);
	pTestCtrl->m_strID = strDeviceSN;
	pTestCtrl->m_strMacroFile = strMacroFile;
	pTestCtrl->m_strEngineProgID = strEngineProgID;
	pTestCtrl->m_strRemoteIP = strRemoteIP;
	pTestCtrl->m_nRemotePort = nRemotePort;
	pTestCtrl->m_strProtocolID = strProtocolID;
	AddNewChild(pTestCtrl);

	return pTestCtrl;
}

CExBaseList* CIotVmAppBase::CreateConfigDatas(const CString &strConfig)
{
	CExBaseList *pDatas = NULL;

	if (strConfig.Find(_T("<dataset")) >= 0)
	{
		pDatas = new CDvmDataset();
	}
	else if (strConfig.Find(_T("<group")) >= 0)
	{
		pDatas = new CDataGroup();
	}


	if (pDatas != NULL)
	{
		BSTR bstrText = strConfig.AllocSysString();
		pDatas->SetXml(bstrText,CDataMngrXmlRWKeys::g_pXmlKeys);
		SysFreeString(bstrText);
	}

	return pDatas;
}


CIotTestCtrlBase* CIotVmAppBase::OnNewTestApp(const CString &strTestAppSN,const CString &strTestMacrosFile)
{
	ASSERT(!strTestAppSN.IsEmpty());
	ASSERT(!strTestMacrosFile.IsEmpty());

	CString strTempFile = strTestMacrosFile;
	CIotTestCtrlBase *pTestCtrl = new CIotTestCtrlBase;
	pTestCtrl->m_strID = strTestAppSN;

	pTestCtrl->m_pTestMacros = TM_GetTestMacros(strTempFile);
	pTestCtrl->SubcribeMqttTopic(0);

	return pTestCtrl;
}

CIotTestCtrlBase* CIotVmAppBase::OnNewIotTestApp(const CString &strTestAppSN,const CString &strTestMacrosFile
								,const CString &strDeviceSN,long nDeviceType)
{
	ASSERT(!strTestAppSN.IsEmpty());
	ASSERT(!strDeviceSN.IsEmpty());
	ASSERT(!strTestMacrosFile.IsEmpty());

	CString strTempFile = strTestMacrosFile;
	CIotTestCtrl *pTestCtrl = new CIotTestCtrl;
	pTestCtrl->m_strID = strTestAppSN;

	pTestCtrl->m_pTestMacros = TM_GetTestMacros(strTempFile);
	pTestCtrl->SetIotDevice(strDeviceSN,nDeviceType);

	pTestCtrl->SubcribeMqttTopic(0);

	return pTestCtrl;
}
