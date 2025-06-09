// AtsMesServerGlobalApi.cpp : 实现文件
//

#include "stdafx.h"
#include "AtsMesTestDefine.h"
#include "../AutoTestGlobalDefine.h"
#include "../../../Module/API/FileApi.h"
#include "../../../System/Module/XAtsSysSvrGlobalDef.h"

CAtsMesTestDefine::CAtsMesTestDefine()
{
	m_pDevices = NULL;
	m_pTestApps = NULL;
}

CAtsMesTestDefine::~CAtsMesTestDefine()
{

}

void CAtsMesTestDefine::FreeAtsTestDefineInterface()
{
	DeleteAll();
	m_pDevices = NULL;
	m_pTestApps = NULL;
}

long CAtsMesTestDefine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strTestMode);
	xml_GetAttibuteValue(pXmlKeys->m_strFolderKey, oNode, m_strFolder);
	xml_GetAttibuteValue(pXmlKeys->m_strReportModeKey, oNode, m_strReportMode);

	return 0;
}

long CAtsMesTestDefine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strTestMode);
	xml_SetAttributeValue(pXmlKeys->m_strFolderKey, oElement, m_strFolder);
	xml_SetAttributeValue(pXmlKeys->m_strReportModeKey, oElement, m_strReportMode);

	return 0;
}

void CAtsMesTestDefine::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->m_strID == AtsRpcTestDef_test_apps)
		{
			m_pTestApps = (CDataGroup*)p;
		}
		else if (p->m_strID == AtsRpcTestDef_devices)
		{
			m_pDevices = (CDataGroup*)p;
		}
		else if (p->m_strID == AtsRpcTestDef_InspectionBases)
		{
			m_pInspectionBases = (CDataGroup*)p;
		}
		else if (p->m_strID == AtsRpcTestDef_Testors)
		{
			m_pTesters = (CDataGroup*)p;
		}
		else if (p->m_strID == AtsRpcTestDef_GlobalDatas)
		{
			m_pGlobalDatas = (CDataGroup*)p;
		}
	}

	if (m_pTestApps == NULL)
	{
		m_pTestApps = new CDataGroup();
		m_pTestApps->m_strName = AtsRpcTestDef_test_apps;
		m_pTestApps->m_strID = AtsRpcTestDef_test_apps;
		AddNewChild(m_pTestApps);
	}

	if (m_pDevices == NULL)
	{
		m_pDevices = new CDataGroup();
		m_pDevices->m_strName = AtsRpcTestDef_devices;
		m_pDevices->m_strID = AtsRpcTestDef_devices;
		AddNewChild(m_pDevices);
	}

	if (m_pInspectionBases == NULL)
	{
		m_pInspectionBases = new CDataGroup();
		m_pInspectionBases->m_strName = AtsRpcTestDef_InspectionBases;
		m_pInspectionBases->m_strID = AtsRpcTestDef_InspectionBases;
		AddNewChild(m_pInspectionBases);
	}

	if (m_pTesters == NULL)
	{
		m_pTesters = new CDataGroup();
		m_pTesters->m_strName = AtsRpcTestDef_Testors;
		m_pTesters->m_strID = AtsRpcTestDef_Testors;
		AddNewChild(m_pTesters);
	}
	
	if (m_pGlobalDatas == NULL)
	{
		m_pGlobalDatas = new CDataGroup();
		m_pGlobalDatas->m_strName = AtsRpcTestDef_GlobalDatas;
		m_pGlobalDatas->m_strID = AtsRpcTestDef_GlobalDatas;
		AddNewChild(m_pGlobalDatas);
	}
}

long CAtsMesTestDefine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataGroup::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFolder);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strReportMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strEngineProgID);
		BinarySerializeCalLen(oBinaryBuffer, m_strPpXmlFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmFile);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strFolder);
		BinarySerializeWrite(oBinaryBuffer, m_strTestMode);
		BinarySerializeWrite(oBinaryBuffer, m_strReportMode);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeWrite(oBinaryBuffer, m_strEngineProgID);
		BinarySerializeWrite(oBinaryBuffer, m_strPpXmlFile);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmFile);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFolder);
		BinarySerializeRead(oBinaryBuffer, m_strTestMode);
		BinarySerializeRead(oBinaryBuffer, m_strReportMode);
		BinarySerializeRead(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeRead(oBinaryBuffer, m_strEngineProgID);
		BinarySerializeRead(oBinaryBuffer, m_strPpXmlFile);
		BinarySerializeRead(oBinaryBuffer, m_strDvmFile);
	}

	return 0;
}

BOOL CAtsMesTestDefine::GetGuideBookFile(CString &strGbFile)
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_GBXMLFILE);
	
	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->m_strValue.GetAt(1) != ':')
	{
		strGbFile = _P_GetTemplatePath();
		strGbFile += pFind->m_strValue;
	}
	else
	{
		strGbFile = pFind->m_strValue;
	}

	return TRUE;
}

BOOL CAtsMesTestDefine::GetEngineProgID(CString &strEngineProgID)
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_EngineProgID_2);

	if (pFind == NULL)
	{
		CExBaseList *pDevice = GetDeviceAttrs(0);

		if (pDevice == NULL)
		{
			return FALSE;
		}

		pFind = (CDvmData*)pDevice->FindByID(XPARA_ID_EngineProgID_2);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	strEngineProgID = pFind->m_strValue;

	return TRUE;
}

//shaolei 2023-11-2
BOOL CAtsMesTestDefine::GetEngineMode(CString &strEngineMode)
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_EngineMode);

	if (pFind == NULL)
	{
		CExBaseList *pDevice = GetDeviceAttrs(0);  //此处实际上只取了第一台设备

		if (pDevice == NULL)
		{
			return FALSE;
		}

		pFind = (CDvmData*)pDevice->FindByID(XPARA_ID_EngineMode);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	strEngineMode = pFind->m_strValue;

	return TRUE;
}

BOOL CAtsMesTestDefine::GetPpxmlFile(CString &strPpxmlFile)
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_PPXMLFILE);

	if (pFind == NULL)
	{
		//暂时不考虑多装置,取第一台设备   shaolei  20210810
		CDataGroup *pDevice = (CDataGroup *)m_pDevices->GetHead();
		pFind = (CDvmData*)pDevice->FindByID(XPARA_ID_PPXMLFILE);

		if (pFind == NULL)
		{
			return FALSE;
		}
	}

	if (pFind->m_strValue.IsEmpty())
	{
		return FALSE;
	}

	if (pFind->m_strValue.GetAt(1) != ':')
	{
		strPpxmlFile = atssys_GetProtocolTemplatePath();
		strPpxmlFile.AppendFormat(_T("%s"), pFind->m_strValue.GetString());
	}
	else
	{
		strPpxmlFile = pFind->m_strValue;
	}

	return TRUE;
}

BOOL CAtsMesTestDefine::GetDvmFile(CString &strDvmFile)
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_DVMFILE);	
	CString strFile;

	if (pFind == NULL)
	{
		//暂时不考虑多装置,取第一台设备   shaolei  20210810
		CDataGroup *pDevice = (CDataGroup *)m_pDevices->GetHead();
		pFind = (CDvmData*)pDevice->FindByID(XPARA_ID_DVMFILE);

		if (pFind == NULL)
		{
			return FALSE;
		}
	}

	if (pFind->m_strValue.GetAt(1) != ':')
	{
		strFile = atssys_GetProtocolDvmPath();
		strFile.AppendFormat(_T("%s"), pFind->m_strValue.GetString());

		if (!IsFileExist(strFile))
		{
			strFile = atssys_GetReportLibraryPath();
			strFile.AppendFormat(_T("%s"), pFind->m_strValue.GetString());
		}

		strDvmFile = strFile;
	}
	else
	{
		strDvmFile = pFind->m_strValue;
	}

	return TRUE;
}

BOOL CAtsMesTestDefine::GetTestType(CString &strTestType)
{	
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_TestType);	

	if (pFind == NULL)
	{
		return FALSE;
	}

	strTestType = pFind->m_strValue;
	return TRUE;
}

BOOL CAtsMesTestDefine::GetDeviceSN(CString &strDeviceSN, long nIndex)  //shaolei 2023-11-3
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_DeviceSN);

	if (pFind == NULL)
	{
		CExBaseList *pDevice = GetDeviceAttrs(nIndex);  

		if (pDevice == NULL)
		{
			return FALSE;
		}

		pFind = (CDvmData*)pDevice->FindByID(XPARA_ID_DeviceSN);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	strDeviceSN = pFind->m_strValue;

	return TRUE;
}

BOOL CAtsMesTestDefine::GetDvmFile(CString &strDvmFile, long nIndex)
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_DVMFILE);
	CString strFile;

	if (pFind == NULL)
	{
		CExBaseList *pDevice = GetDeviceAttrs(nIndex);  

		if (pDevice == NULL)
		{
			return FALSE;
		}

		pFind = (CDvmData*)pDevice->FindByID(XPARA_ID_DVMFILE);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->m_strValue.GetAt(1) != ':')
	{
		strFile = atssys_GetProtocolDvmPath();
		strFile.AppendFormat(_T("%s"), pFind->m_strValue.GetString());

		if (!IsFileExist(strFile))
		{
			strFile = atssys_GetReportLibraryPath();
			strFile.AppendFormat(_T("%s"), pFind->m_strValue.GetString());
		}

		strDvmFile = strFile;
	}
	else
	{
		strDvmFile = pFind->m_strValue;
	}

	return TRUE;
}

BOOL CAtsMesTestDefine::GetPpxmlFile(CString &strPpxmlFile, long nIndex)
{
	CDvmData *pFind = (CDvmData*)FindByID(XPARA_ID_PPXMLFILE);

	if (pFind == NULL)
	{
		CExBaseList *pDevice = GetDeviceAttrs(nIndex);  

		if (pDevice == NULL)
		{
			return FALSE;
		}

		pFind = (CDvmData*)pDevice->FindByID(XPARA_ID_PPXMLFILE);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->m_strValue.GetAt(1) != ':')
	{
		strPpxmlFile = atssys_GetProtocolTemplatePath();
		strPpxmlFile.AppendFormat(_T("%s"), pFind->m_strValue.GetString());
	}
	else
	{
		strPpxmlFile = pFind->m_strValue;
	}

	return TRUE;
}

void CAtsMesTestDefine::InitTestTaskName(const CString &strModel)
{
	
}

void CAtsMesTestDefine::SetTestTaskName(const CString &strTaskName)
{
	m_strID = strTaskName;
	m_strName = strTaskName;
}

/*
<paras>
	<data name="测试台标识" id="TestID" value="测试台SN/"/>
	<data name="测试模板" id="gbxml-file" value="SZNR-TTU.gbexe"/>
	<data name="测试模板" id="gbxml-file_s" value="……………"/> 
*/
void CAtsMesTestDefine::SetTestTmplateFile(const CString &strGbxmlFile, const CString &strEngineProgID, const CString &strPpXmlFile, const CString &strDvmFile)
{
	m_strGbxmlFile = strGbxmlFile;
	m_strEngineProgID = strEngineProgID;
	m_strPpXmlFile = strPpXmlFile;
	m_strDvmFile = strDvmFile;

	AddNewData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, _T(""), strGbxmlFile);
	AddNewData(XPARA_ID_EngineProgID, XPARA_ID_EngineProgID, _T(""), strEngineProgID);
	AddNewData(XPARA_ID_PPXMLFILE, XPARA_ID_PPXMLFILE, _T(""), strPpXmlFile);
	AddNewData(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, _T(""), strDvmFile);
}

/*
<group id="devices">
	<group id="device">
		<data id="SN" value="123456789"/>
		<data id="EngineProgID" value="PpEngine"/>
		<data name="规则文件" id="ppxml-file" value="SZNR-TTU.ppxml"/>
		<data name="规则文件" id="ppxml-file_s" value="…… "/>
		<data id="dvm-file" value="SZNR-TTU.xml"/>
		<data id="dvm-file_s" value="…… "/>
		<data id="remote-ip" value="127.0.0.1"/>
		<data id="remote-port" value="9988"/>
	</group>
	……
</group>*/

//删除IP,IP_2,IP_3,COM_1,COM_2,COM_3  这几个变量通过装置属性传递
CExBaseObject* CAtsMesTestDefine::AddDeviceTest(const CString &strDvmFile, const CString &strBRCode, long nPort 
										   ,long nBaudRate, long nByteSize, long nStopBit, long nParity
										    , long nBinOffset, long nBoutOffset, long nUdc_Power
											, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
											, const CString &strSignPath, const CString &strDevIndex)
{
	//<group id="device">
	CDataGroup *pDeviceTest = new CDataGroup();
	m_pDevices->AddNewChild(pDeviceTest);
	pDeviceTest->m_strName = strDevOnlyCode;
	pDeviceTest->m_strID = strDevOnlyCode;

	pDeviceTest->AddNewData(STT_CMD_PARA_DeviceSN, strDevOnlyCode);
	pDeviceTest->AddNewData(XPARA_ID_DVMFILE, strDvmFile);

	return pDeviceTest;
}

//删除IP,IP_2,IP_3,COM_1,COM_2,COM_3  这几个变量通过装置属性传递
CExBaseObject* CAtsMesTestDefine::AddDeviceTest(const CString &strBRCode, long nPort, long nBaudRate, long nByteSize
										   , long nStopBit, long nParity, long nBinOffset, long nBoutOffset
										   , long nUdc_Power, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
										   , const CString &strSignPath, const CString &strDevIndex)
{
	CDataGroup *pDeviceTest = new CDataGroup();
	m_pDevices->AddNewChild(pDeviceTest);
	pDeviceTest->m_strName = strDevOnlyCode;
	pDeviceTest->m_strID = strDevOnlyCode;

	pDeviceTest->AddNewData(STT_CMD_PARA_DeviceSN, strDevOnlyCode);
	pDeviceTest->AddNewData(XPARA_ID_DVMFILE, m_strDvmFile);

	return pDeviceTest;
}

CExBaseObject* CAtsMesTestDefine::AddDeviceTest(CExBaseObject *pDeviceAttrs)
{
	ASSERT (DTMCLASSID_CDATAGROUP == pDeviceAttrs->GetClassID());

	if (DTMCLASSID_CDATAGROUP == pDeviceAttrs->GetClassID())
	{
		CDataGroup *pDeviceTest = new CDataGroup();
		pDeviceTest->AppendCloneEx(*((CDataGroup*)pDeviceAttrs));
		m_pDevices->AddNewChild(pDeviceTest);
	
		return pDeviceTest;
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("CAtsMesTestDefine::AddDeviceTest : pDeviceAttrs is not CDataGroup"));
		return NULL;
	}
}

CExBaseObject* CAtsMesTestDefine::AddDeviceTest(const CString &strBRCode)
{
	ASSERT (FALSE);
	return NULL;
}

CExBaseObject* CAtsMesTestDefine::AddDeviceTest(const CString &strIP, long nPort)
{
	CDataGroup *pDeviceTest = new CDataGroup();
	m_pDevices->AddNewChild(pDeviceTest);

	pDeviceTest->AddNewData(XPARA_ID_DVMFILE, m_strDvmFile);
	pDeviceTest->AddNewData(XPARA_ID_Remote_ip, strIP);

	CString strPort;
	strPort.Format(_T("%d"), nPort);
	pDeviceTest->AddNewData(XPARA_ID_Remote_port, strPort);

	return pDeviceTest;
}

CExBaseObject* CAtsMesTestDefine::SetDeviceTest(long nIndex, const CString &strIP, long nPort)
{
	CDataGroup *pDeviceTest = (CDataGroup*)GetHead();

	if (pDeviceTest == NULL)
	{
		pDeviceTest = (CDataGroup *)AddDeviceTest(strIP, nPort);
	}
	else
	{
		pDeviceTest->SetDataValue(XPARA_ID_DVMFILE, m_strDvmFile);
		pDeviceTest->SetDataValue(XPARA_ID_Remote_ip, strIP);
		pDeviceTest->SetDataValue(XPARA_ID_Remote_port, nPort);
	}

	return pDeviceTest;
}

CExBaseObject* CAtsMesTestDefine::AddDeviceTest(long nPort, long nBaudRate, long nByteSize, long nStopBit, long nParity, long nBinOffset, long nBoutOffset, long nCOM)
{
	CDataGroup *pDeviceTest = new CDataGroup();
	m_pDevices->AddNewChild(pDeviceTest);

	pDeviceTest->AddNewData(XPARA_ID_DVMFILE, m_strDvmFile);

	return pDeviceTest;
}



/*
<group id="test-apps">
	<group id="test-app">
		<data id="DeviceSN" value="123456789"/>
		<data id="EngineProgID" value="IotVm"/>
		<data id="dvm-file" value="MacroTest.xml"/>
		<data id="remote-ip" value="127.0.0.1"/>
		<data id="remote-port" value="9988"/>
	</group>
	……
</group>
*/
void CAtsMesTestDefine::AddTestApp(const CString &strAppType, const CString &strFactory, const CString &strModel, const CString &strIP, const CString &strSN, const CString &strTime)
{
	CDataGroup *pTestApp = AddNewGroup(strIP, strIP, strAppType);
	
	pTestApp->AddNewData(XPARA_ID_Remote_ip, XPARA_ID_Remote_ip, _T("string"), strIP);
	pTestApp->AddNewData(STT_CMD_PARA_DeviceSN, STT_CMD_PARA_DeviceSN, _T("string"), strSN);

	pTestApp->AddNewData(_T("Factory"), strFactory);
	pTestApp->AddNewData(_T("Model"), strModel);
	pTestApp->AddNewData(_T("Name"), strAppType);
	pTestApp->AddNewData(_T("DateManufac"), strTime);
}

void CAtsMesTestDefine::AddTestApp(CExBaseObject *pData)
{
	ASSERT (DTMCLASSID_CDATAGROUP == pData->GetClassID());

	if (DTMCLASSID_CDATAGROUP == pData->GetClassID())
	{
		CDataGroup *pTestApp = (CDataGroup*)pData->Clone();
		AddNewChild(pTestApp);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("CAtsMesTestDefine::AddTestApp : pData is not CDataGroup"));
	}
}

