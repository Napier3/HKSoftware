// AtsRpcServerGlobalApi.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartTestDefineInterface.h"
#include "../../Module/DataMngr/DvmData.h"//zhouhj 20210819 解决编译问题


CAtsTestDefineInterface::CAtsTestDefineInterface()
{
	m_pDevices = NULL;
	m_pTestApps = NULL;
	m_pInspectionBases = NULL;
	m_pTesters = NULL;
	m_pGlobalDatas = NULL;
}

CAtsTestDefineInterface::~CAtsTestDefineInterface()
{

}

void CAtsTestDefineInterface::FreeAtsTestDefineInterface()
{
	m_pDevices = NULL;
	m_pTestApps = NULL;
}

void CAtsTestDefineInterface::SetTestMode_gbrpt()
{
	m_strTestMode = _T("gbrpt");
}

void CAtsTestDefineInterface::SetTestMode_gbmdmrpt()
{
	m_strTestMode = _T("gbmdmrpt");
}

void CAtsTestDefineInterface::SetReportMode_WPS()
{
	m_strReportMode = REPORTFILL_PROGID_WPS;
}

void CAtsTestDefineInterface::SetReportMode_WORD()
{
	m_strReportMode = REPORTFILL_PROGID_WORD;
}

void CAtsTestDefineInterface::SetReportMode_SYSTEM()
{
	m_strReportMode = REPORTFILL_PROGID_SYSTEM;
}

void CAtsTestDefineInterface::SetReportMode_NONE()
{
	m_strReportMode = REPORTFILL_PROGID_NONE;
}

CString CAtsTestDefineInterface::GetDeviceAttrByID(long nIndex, const CString &strAttrID)
{
	if (m_pDevices == NULL)
	{
		return _T("");
	}

	CExBaseList *pDevice = (CExBaseList*)m_pDevices->GetAtIndex(nIndex);

	if (pDevice == NULL)
	{
		return _T("");
	}

	CExBaseObject *pData = pDevice->FindByID(strAttrID);

	if (pData == NULL)
	{
		return _T("");
	}

	return ((CDvmData*)pData)->m_strValue;
}

CExBaseList* CAtsTestDefineInterface::GetDeviceAttrs(long nIndex)
{
	if (m_pDevices == NULL)
	{
		return NULL;
	}

	return (CExBaseList*)m_pDevices->GetAtIndex(nIndex);
}

BOOL CAtsTestDefineInterface::GetGuideBookFile(CString &strGbFile)
{
	ASSERT (FALSE);
// 	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_GBXMLFILE);
// 	
// 	if (pFind == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (pFind->m_strValue.GetAt(1) != ':')
// 	{
// 		strGbFile = _P_GetTemplatePath();
// 		strGbFile += pFind->m_strValue;
// 	}
// 	else
// 	{
// 		strGbFile = pFind->m_strValue;
// 	}

	return TRUE;
}

BOOL CAtsTestDefineInterface::GetEngineProgID(CString &strEngineProgID)
{
	ASSERT (FALSE);
// 	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_EngineProgID);
// 
// 	if (pFind == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	strEngineProgID = pFind->m_strValue;

	return TRUE;
}

BOOL CAtsTestDefineInterface::GetEngineMode(CString &strEngineMode)
{
	return FALSE;
}

BOOL CAtsTestDefineInterface::GetPpxmlFile(CString &strPpxmlFile)
{
	ASSERT (FALSE);
// 	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_PPXMLFILE);
// 
// 	if (pFind == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (pFind->m_strValue.IsEmpty())
// 	{
// 		return FALSE;
// 	}
// 
// 	if (pFind->m_strValue.GetAt(1) != ':')
// 	{
// 		strPpxmlFile = atssys_GetProtocolTemplatePath();
// 		strPpxmlFile.AppendFormat(_T("%s"), pFind->m_strValue);
// 	}
// 	else
// 	{
// 		strPpxmlFile = pFind->m_strValue;
// 	}

	return TRUE;
}

BOOL CAtsTestDefineInterface::GetDvmFile(CString &strDvmFile)
{
	ASSERT (FALSE);
// 	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_DVMFILE);
// 	CString strFile;
// 
// 	if (pFind == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (pFind->m_strValue.GetAt(1) != ':')
// 	{
// 		strFile = atssys_GetProtocolDvmPath();
// 		strFile.AppendFormat(_T("%s"), pFind->m_strValue);
// 
// 		if (!IsFileExist(strFile))
// 		{
// 			strFile = atssys_GetReportLibraryPath();
// 			strFile.AppendFormat(_T("%s"), pFind->m_strValue);
// 		}
// 
// 		strDvmFile = strFile;
// 	}
// 	else
// 	{
// 		strDvmFile = pFind->m_strValue;
// 	}

	return TRUE;
}

BOOL CAtsTestDefineInterface::GetTestType(CString &strTestType)
{
	return FALSE;
}

BOOL CAtsTestDefineInterface::GetDeviceSN(CString &strDeviceSN, long nIndex)  //shaolei 2023-11-3
{
	return FALSE;
}

BOOL CAtsTestDefineInterface::GetDvmFile(CString &strDvmFile, long nIndex)
{
	return FALSE;
}

BOOL CAtsTestDefineInterface::GetPpxmlFile(CString &strPpxmlFile, long nIndex)
{
	return FALSE;
}

void CAtsTestDefineInterface::InitTestTaskName(const CString &strModel)
{
	
}

void CAtsTestDefineInterface::SetTestTaskName(const CString &strTaskName)
{
	m_strTaskName = strTaskName;
}

/*
<dataset name="template" id="template">
	<data name="gbxml-file" id="gbxml-file" value="SF\\CSC-100.gbxml"/>
	<data name="EngineProgID" id="EngineProgID" value=""/>
	<data name="ppxml-file" id="ppxml-file" value=""/>
	<data name="dvm-file" id="dvm-file" value=""/>
</dataset>
*/
void CAtsTestDefineInterface::SetTestTmplateFile(const CString &strGbxmlFile, const CString &strEngineProgID, const CString &strPpXmlFile, const CString &strDvmFile)
{
	m_strGbxmlFile = strGbxmlFile;
	m_strEngineProgID = strEngineProgID;
	m_strPpXmlFile = strPpXmlFile;
	m_strDvmFile = strDvmFile;

	ASSERT (FALSE);
// 	ASSERT (m_pTemplate != NULL);
// 	m_pTemplate->AddNewData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, _T(""), strGbxmlFile);
// 	m_pTemplate->AddNewData(XPARA_ID_EngineProgID, XPARA_ID_EngineProgID, _T(""), strEngineProgID);
// 	m_pTemplate->AddNewData(XPARA_ID_PPXMLFILE, XPARA_ID_PPXMLFILE, _T(""), strPpXmlFile);
// 	m_pTemplate->AddNewData(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, _T(""), strDvmFile);
}

/*
<dataset>
	<data name="device" id="device" value="">
		<value name="dvm-file" id="dvm-file" value="SF\\CSC-100.xml"/>
		<value name="model" id="model" value="CSC-200"/>
		<value name="br-code" id="br-code" value=""/>
		<value name="ip" id="ip" value="192.168.1.160"/>
		<value name="port" id="port" value="3"/>
		<value name="baud-rate" id="baud-rate" value="9600"/>
		<value name="byte-size" id="baud-rate" value="8"/>
		<value name="stop-bit" id="stop-bit" value="1"/>
		<value name="parity" id="parity" value="0"/>
	</data>
</dataset>
*/

//删除IP,IP_2,IP_3,COM_1,COM_2,COM_3  这几个变量通过装置属性传递
CExBaseObject* CAtsTestDefineInterface::AddDeviceTest(const CString &strDvmFile, const CString &strBRCode, long nPort 
										   ,long nBaudRate, long nByteSize, long nStopBit, long nParity
										    , long nBinOffset, long nBoutOffset, long nUdc_Power
											, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
											, const CString &strSignPath, const CString &strDevIndex)
{
	ASSERT (FALSE);
	return NULL;
// 	CDvmData *pDeviceTest = new CDvmData();
// 	m_pDevices->AddNewChild(pDeviceTest);
// 	pDeviceTest->m_strName = strDevOnlyCode;
// 	pDeviceTest->m_strID = strDevOnlyCode;
// 
// 	pDeviceTest->AddValue(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, strDvmFile);
// 	pDeviceTest->AddValue(AtsRpcTestDef_port, AtsRpcTestDef_port, nPort);
// 	pDeviceTest->AddValue(AtsRpcTestDef_baud_rate, AtsRpcTestDef_baud_rate, nBaudRate);
// 	pDeviceTest->AddValue(AtsRpcTestDef_byte_size, AtsRpcTestDef_byte_size, nByteSize);
// 	pDeviceTest->AddValue(AtsRpcTestDef_stop_bit, AtsRpcTestDef_stop_bit, nStopBit);
// 	pDeviceTest->AddValue(AtsRpcTestDef_parity, AtsRpcTestDef_parity, nParity);
// 	pDeviceTest->AddValue(AtsRpcTestDef_bin_offset, AtsRpcTestDef_bin_offset, nBinOffset);
// 	pDeviceTest->AddValue(AtsRpcTestDef_bout_offset, AtsRpcTestDef_bout_offset, nBoutOffset);
// 	pDeviceTest->AddValue(AtsRpcTestDef_udc_power, AtsRpcTestDef_udc_power, nUdc_Power);
// 	pDeviceTest->AddValue(AtsRpcTestDef_TestAppGroup, AtsRpcTestDef_TestAppGroup, nTestAppGroup);
// 	pDeviceTest->AddValue(AtsRpcTestDef_AcCurrent, AtsRpcTestDef_AcCurrent, nAcCurr);
// 	pDeviceTest->AddValue(AtsRpcTestDef_DevOnlyCode, AtsRpcTestDef_DevOnlyCode, strDevOnlyCode);
// 	pDeviceTest->AddValue(AtsRpcTestDef_Sign, AtsRpcTestDef_Sign, strSignPath);
// 	pDeviceTest->AddValue(AtsRpcTestDef_DevIndex, AtsRpcTestDef_DevIndex, strDevIndex);
// 
// 	return pDeviceTest;
}

//删除IP,IP_2,IP_3,COM_1,COM_2,COM_3  这几个变量通过装置属性传递
CExBaseObject* CAtsTestDefineInterface::AddDeviceTest(const CString &strBRCode, long nPort, long nBaudRate, long nByteSize
										   , long nStopBit, long nParity, long nBinOffset, long nBoutOffset
										   , long nUdc_Power, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
										   , const CString &strSignPath, const CString &strDevIndex)
{
	ASSERT (FALSE);
	return NULL;
// 	CDvmData *pDeviceTest = new CDvmData();
// 	m_pDevices->AddNewChild(pDeviceTest);
// 	pDeviceTest->m_strName = strDevOnlyCode;
// 	pDeviceTest->m_strID = strDevOnlyCode;
// 
// 	pDeviceTest->AddValue(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, m_strDvmFile);
// 	pDeviceTest->AddValue(AtsRpcTestDef_port, AtsRpcTestDef_port, nPort);
// 	pDeviceTest->AddValue(AtsRpcTestDef_baud_rate, AtsRpcTestDef_baud_rate, nBaudRate);
// 	pDeviceTest->AddValue(AtsRpcTestDef_byte_size, AtsRpcTestDef_byte_size, nByteSize);
// 	pDeviceTest->AddValue(AtsRpcTestDef_stop_bit, AtsRpcTestDef_stop_bit, nStopBit);
// 	pDeviceTest->AddValue(AtsRpcTestDef_parity, AtsRpcTestDef_parity, nParity);
// 	pDeviceTest->AddValue(AtsRpcTestDef_bin_offset, AtsRpcTestDef_bin_offset, nBinOffset);
// 	pDeviceTest->AddValue(AtsRpcTestDef_bout_offset, AtsRpcTestDef_bout_offset, nBoutOffset);
// 	pDeviceTest->AddValue(AtsRpcTestDef_udc_power, AtsRpcTestDef_udc_power, nUdc_Power);
// 	pDeviceTest->AddValue(AtsRpcTestDef_TestAppGroup, AtsRpcTestDef_TestAppGroup, nTestAppGroup);
// 	pDeviceTest->AddValue(AtsRpcTestDef_AcCurrent, AtsRpcTestDef_AcCurrent, nAcCurr);
// 	pDeviceTest->AddValue(AtsRpcTestDef_DevOnlyCode, AtsRpcTestDef_DevOnlyCode, strDevOnlyCode);
// 	pDeviceTest->AddValue(AtsRpcTestDef_Sign, AtsRpcTestDef_Sign, strSignPath);
// 	pDeviceTest->AddValue(AtsRpcTestDef_DevIndex, AtsRpcTestDef_DevIndex, strDevIndex);
// 
// 	return pDeviceTest;
}

CExBaseObject* CAtsTestDefineInterface::AddDeviceTest(CExBaseObject *pDeviceAttrs)
{
// 	CDvmData *pDeviceTest = new CDvmData();
// 	m_pDevices->AddNewChild(pDeviceTest);
// 	pDeviceTest->AppendCloneEx(*pDeviceAttrs);
// 	return pDeviceTest;
	ASSERT (FALSE);
	return NULL;
}

CExBaseObject* CAtsTestDefineInterface::AddDeviceTest(const CString &strBRCode)
{
	ASSERT (FALSE);
	return NULL;
}

CExBaseObject* CAtsTestDefineInterface::AddDeviceTest(const CString &strIP, long nPort)
{
	ASSERT (FALSE);
	return NULL;
// 	CDvmData *pDeviceTest = new CDvmData();
// 	m_pDevices->AddNewChild(pDeviceTest);
// 
// 	pDeviceTest->AddValue(XPARA_ID_DVMFILE, m_strDvmFile);
// 	pDeviceTest->AddValue(AtsRpcTestDef_ip, strIP);
// 	pDeviceTest->AddValue(AtsRpcTestDef_port, nPort);
// 
// 	return pDeviceTest;
}

CExBaseObject* CAtsTestDefineInterface::SetDeviceTest(long nIndex, const CString &strIP, long nPort)
{
	ASSERT (FALSE);
	return NULL;
// 	CDvmData *pDeviceTest = (CDvmData*)GetHead();
// 
// 	if (pDeviceTest == NULL)
// 	{
// 		pDeviceTest = AddDeviceTest(strIP, nPort);
// 	}
// 	else
// 	{
// 		pDeviceTest->SetValue(XPARA_ID_DVMFILE, m_strDvmFile);
// 		pDeviceTest->SetValue(AtsRpcTestDef_ip, strIP);
// 		pDeviceTest->SetValue(AtsRpcTestDef_port, nPort);
// 	}
// 
// 	return pDeviceTest;
}

CExBaseObject* CAtsTestDefineInterface::AddDeviceTest(long nPort, long nBaudRate, long nByteSize, long nStopBit, long nParity, long nBinOffset, long nBoutOffset, long nCOM)
{
	ASSERT (FALSE);
	return NULL;
// 	CDvmData *pDeviceTest = new CDvmData();
// 	m_pDevices->AddNewChild(pDeviceTest);
// 
// 	pDeviceTest->AddValue(XPARA_ID_DVMFILE, m_strDvmFile);
// 	pDeviceTest->AddValue(AtsRpcTestDef_port, nPort);
// 	pDeviceTest->AddValue(AtsRpcTestDef_baud_rate, nBaudRate);
// 	pDeviceTest->AddValue(AtsRpcTestDef_byte_size, nByteSize);
// 	pDeviceTest->AddValue(AtsRpcTestDef_stop_bit, nStopBit);
// 	pDeviceTest->AddValue(AtsRpcTestDef_parity, nParity);
// 	pDeviceTest->AddValue(AtsRpcTestDef_bin_offset, nBinOffset);
// 	pDeviceTest->AddValue(AtsRpcTestDef_bout_offset, nBoutOffset);
// 
// 	return pDeviceTest;
}



/*
<data name="电能质量标准源" id="B150601" data-type="" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
	<value name="Factory" id="Factory" data-type="" value="北京博电新力电力仪器股份有限公司"/>
	<value name="Model" id="Model" data-type="" value="PQC600B"/>
	<value name="Name" id="Name" data-type="" value="电能质量标准源"/>
	<value name="SN" id="SN" data-type="" value="B150601"/>
	<value name="DateManufac" id="DateManufac" data-type="" value="2015年6月"/>
</data>
*/
void CAtsTestDefineInterface::AddTestApp(const CString &strAppType, const CString &strFactory, const CString &strModel, const CString &strIP, const CString &strSN, const CString &strTime)
{
	ASSERT (FALSE);
// 	CDvmData *pTestApp = m_pTemplate->AddNewData(strIP, strIP, strAppType, strIP);
// 	
// 	pTestApp->AddValue(_T("Factory"), strFactory);
// 	pTestApp->AddValue(_T("Model"), strModel);
// 	pTestApp->AddValue(_T("Name"), strAppType);
// 	pTestApp->AddValue(_T("SN"), strSN);
// 	pTestApp->AddValue(_T("DateManufac"), strTime);
}

void CAtsTestDefineInterface::AddTestApp(CExBaseObject *pData)
{
	ASSERT (FALSE);
// 	CDvmData *pTestApp = (CDvmData*)pData->Clone();
// 	m_pTemplate->AddNewChild(pTestApp);
}

