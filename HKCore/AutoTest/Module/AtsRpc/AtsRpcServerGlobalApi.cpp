// AtsRpcServerGlobalApi.cpp : 实现文件
//

#include "stdafx.h"
#include "AtsRpcServerGlobalApi.h"
#include "..\AutoTestGlobalDefine.h"
#include "..\..\..\Module\API\FileApi.h"
#include "..\..\..\System\Module\XAtsSysSvrGlobalDef.h"

CAtsRpcTestDefine::CAtsRpcTestDefine()
{
	m_pTemplate = NULL;
	m_pDevices = NULL;
	m_pTestApps = NULL;
}

CAtsRpcTestDefine::~CAtsRpcTestDefine()
{

}

void CAtsRpcTestDefine::FreeAtsTestDefineInterface()
{
	DeleteAll();
	m_pTemplate = NULL;
	m_pDevices = NULL;
	m_pTestApps = NULL;
}

long CAtsRpcTestDefine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmLogicDevice::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strTestMode);
	xml_GetAttibuteValue(pXmlKeys->m_strFolderKey, oNode, m_strFolder);
	xml_GetAttibuteValue(pXmlKeys->m_strReportModeKey, oNode, m_strReportMode);

	return 0;
}

long CAtsRpcTestDefine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmLogicDevice::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strTestMode);
	xml_SetAttributeValue(pXmlKeys->m_strFolderKey, oElement, m_strFolder);
	xml_SetAttributeValue(pXmlKeys->m_strReportModeKey, oElement, m_strReportMode);

	return 0;
}

void CAtsRpcTestDefine::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->m_strID == AtsRpcTestDef_template)
		{
			m_pTemplate = (CDvmDataset*)p;
		}
		else if (p->m_strID == AtsRpcTestDef_test_apps)
		{
			m_pTestApps = (CDvmDataset*)p;
		}
		else if (p->m_strID == AtsRpcTestDef_devices)
		{
			m_pDevices = (CDvmDataset*)p;
		}
	}

// 	ASSERT (m_pTemplate != NULL);
// 	ASSERT (m_pTestApps != NULL);
// 	ASSERT (m_pDevices != NULL);

	if (m_pTemplate == NULL)
	{
		m_pTemplate = new CDvmDataset();
		m_pTemplate->m_strName = AtsRpcTestDef_template;
		m_pTemplate->m_strID = AtsRpcTestDef_template;
		AddNewChild(m_pTemplate);
	}

	if (m_pTestApps == NULL)
	{
		m_pTestApps = new CDvmDataset();
		m_pTestApps->m_strName = AtsRpcTestDef_test_apps;
		m_pTestApps->m_strID = AtsRpcTestDef_test_apps;
		AddNewChild(m_pTestApps);
	}

	if (m_pDevices == NULL)
	{
		m_pDevices = new CDvmDataset();
		m_pDevices->m_strName = AtsRpcTestDef_devices;
		m_pDevices->m_strID = AtsRpcTestDef_devices;
		AddNewChild(m_pDevices);
	}
}

long CAtsRpcTestDefine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDvmLogicDevice::SerializeOwn(oBinaryBuffer);

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

BOOL CAtsRpcTestDefine::GetGuideBookFile(CString &strGbFile)
{
	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_GBXMLFILE);
	
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

BOOL CAtsRpcTestDefine::GetEngineProgID(CString &strEngineProgID)
{
	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_EngineProgID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	strEngineProgID = pFind->m_strValue;

	return TRUE;
}

BOOL CAtsRpcTestDefine::GetPpxmlFile(CString &strPpxmlFile)
{
	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_PPXMLFILE);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->m_strValue.IsEmpty())
	{
		return FALSE;
	}

	if (pFind->m_strValue.GetAt(1) != ':')
	{
		strPpxmlFile = atssys_GetProtocolTemplatePath();
		strPpxmlFile.AppendFormat(_T("%s"), pFind->m_strValue);
	}
	else
	{
		strPpxmlFile = pFind->m_strValue;
	}

	return TRUE;
}

BOOL CAtsRpcTestDefine::GetDvmFile(CString &strDvmFile)
{
	CDvmData *pFind = (CDvmData*)m_pTemplate->FindByID(XPARA_ID_DVMFILE);
	CString strFile;

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->m_strValue.GetAt(1) != ':')
	{
		strFile = atssys_GetProtocolDvmPath();
		strFile.AppendFormat(_T("%s"), pFind->m_strValue);

		if (!IsFileExist(strFile))
		{
			strFile = atssys_GetReportLibraryPath();
			strFile.AppendFormat(_T("%s"), pFind->m_strValue);
		}

		strDvmFile = strFile;
	}
	else
	{
		strDvmFile = pFind->m_strValue;
	}

	return TRUE;
}

void CAtsRpcTestDefine::InitTestTaskName(const CString &strModel)
{
	
}

void CAtsRpcTestDefine::SetTestTaskName(const CString &strTaskName)
{
	m_strID = strTaskName;
	m_strName = strTaskName;
}

/*
<dataset name="template" id="template">
	<data name="gbxml-file" id="gbxml-file" value="SF\\CSC-100.gbxml"/>
	<data name="EngineProgID" id="EngineProgID" value=""/>
	<data name="ppxml-file" id="ppxml-file" value=""/>
	<data name="dvm-file" id="dvm-file" value=""/>
</dataset>
*/
void CAtsRpcTestDefine::SetTestTmplateFile(const CString &strGbxmlFile, const CString &strEngineProgID, const CString &strPpXmlFile, const CString &strDvmFile)
{
	m_strGbxmlFile = strGbxmlFile;
	m_strEngineProgID = strEngineProgID;
	m_strPpXmlFile = strPpXmlFile;
	m_strDvmFile = strDvmFile;

	ASSERT (m_pTemplate != NULL);
	m_pTemplate->AddNewData(XPARA_ID_GBXMLFILE, XPARA_ID_GBXMLFILE, _T(""), strGbxmlFile);
	m_pTemplate->AddNewData(XPARA_ID_EngineProgID, XPARA_ID_EngineProgID, _T(""), strEngineProgID);
	m_pTemplate->AddNewData(XPARA_ID_PPXMLFILE, XPARA_ID_PPXMLFILE, _T(""), strPpXmlFile);
	m_pTemplate->AddNewData(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, _T(""), strDvmFile);
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
CExBaseObject* CAtsRpcTestDefine::AddDeviceTest(const CString &strDvmFile, const CString &strBRCode, long nPort 
										   ,long nBaudRate, long nByteSize, long nStopBit, long nParity
										    , long nBinOffset, long nBoutOffset, long nUdc_Power
											, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
											, const CString &strSignPath, const CString &strDevIndex)
{
	CDvmData *pDeviceTest = new CDvmData();
	m_pDevices->AddNewChild(pDeviceTest);
	pDeviceTest->m_strName = strDevOnlyCode;
	pDeviceTest->m_strID = strDevOnlyCode;

	pDeviceTest->AddValue(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, strDvmFile);
	pDeviceTest->AddValue(AtsRpcTestDef_port, AtsRpcTestDef_port, nPort);
	pDeviceTest->AddValue(AtsRpcTestDef_baud_rate, AtsRpcTestDef_baud_rate, nBaudRate);
	pDeviceTest->AddValue(AtsRpcTestDef_byte_size, AtsRpcTestDef_byte_size, nByteSize);
	pDeviceTest->AddValue(AtsRpcTestDef_stop_bit, AtsRpcTestDef_stop_bit, nStopBit);
	pDeviceTest->AddValue(AtsRpcTestDef_parity, AtsRpcTestDef_parity, nParity);
	pDeviceTest->AddValue(AtsRpcTestDef_bin_offset, AtsRpcTestDef_bin_offset, nBinOffset);
	pDeviceTest->AddValue(AtsRpcTestDef_bout_offset, AtsRpcTestDef_bout_offset, nBoutOffset);
	pDeviceTest->AddValue(AtsRpcTestDef_udc_power, AtsRpcTestDef_udc_power, nUdc_Power);
	pDeviceTest->AddValue(AtsRpcTestDef_TestAppGroup, AtsRpcTestDef_TestAppGroup, nTestAppGroup);
	pDeviceTest->AddValue(AtsRpcTestDef_AcCurrent, AtsRpcTestDef_AcCurrent, nAcCurr);
	pDeviceTest->AddValue(AtsRpcTestDef_DevOnlyCode, AtsRpcTestDef_DevOnlyCode, strDevOnlyCode);
	pDeviceTest->AddValue(AtsRpcTestDef_Sign, AtsRpcTestDef_Sign, strSignPath);
	pDeviceTest->AddValue(AtsRpcTestDef_DevIndex, AtsRpcTestDef_DevIndex, strDevIndex);

	return pDeviceTest;
}

//删除IP,IP_2,IP_3,COM_1,COM_2,COM_3  这几个变量通过装置属性传递
CExBaseObject* CAtsRpcTestDefine::AddDeviceTest(const CString &strBRCode, long nPort, long nBaudRate, long nByteSize
										   , long nStopBit, long nParity, long nBinOffset, long nBoutOffset
										   , long nUdc_Power, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
										   , const CString &strSignPath, const CString &strDevIndex)
{
	CDvmData *pDeviceTest = new CDvmData();
	m_pDevices->AddNewChild(pDeviceTest);
	pDeviceTest->m_strName = strDevOnlyCode;
	pDeviceTest->m_strID = strDevOnlyCode;

	pDeviceTest->AddValue(XPARA_ID_DVMFILE, XPARA_ID_DVMFILE, m_strDvmFile);
	pDeviceTest->AddValue(AtsRpcTestDef_port, AtsRpcTestDef_port, nPort);
	pDeviceTest->AddValue(AtsRpcTestDef_baud_rate, AtsRpcTestDef_baud_rate, nBaudRate);
	pDeviceTest->AddValue(AtsRpcTestDef_byte_size, AtsRpcTestDef_byte_size, nByteSize);
	pDeviceTest->AddValue(AtsRpcTestDef_stop_bit, AtsRpcTestDef_stop_bit, nStopBit);
	pDeviceTest->AddValue(AtsRpcTestDef_parity, AtsRpcTestDef_parity, nParity);
	pDeviceTest->AddValue(AtsRpcTestDef_bin_offset, AtsRpcTestDef_bin_offset, nBinOffset);
	pDeviceTest->AddValue(AtsRpcTestDef_bout_offset, AtsRpcTestDef_bout_offset, nBoutOffset);
	pDeviceTest->AddValue(AtsRpcTestDef_udc_power, AtsRpcTestDef_udc_power, nUdc_Power);
	pDeviceTest->AddValue(AtsRpcTestDef_TestAppGroup, AtsRpcTestDef_TestAppGroup, nTestAppGroup);
	pDeviceTest->AddValue(AtsRpcTestDef_AcCurrent, AtsRpcTestDef_AcCurrent, nAcCurr);
	pDeviceTest->AddValue(AtsRpcTestDef_DevOnlyCode, AtsRpcTestDef_DevOnlyCode, strDevOnlyCode);
	pDeviceTest->AddValue(AtsRpcTestDef_Sign, AtsRpcTestDef_Sign, strSignPath);
	pDeviceTest->AddValue(AtsRpcTestDef_DevIndex, AtsRpcTestDef_DevIndex, strDevIndex);

	return pDeviceTest;
}

CExBaseObject* CAtsRpcTestDefine::AddDeviceTest(CExBaseObject *pDeviceAttrs)
{
	CDvmData *pDeviceTest = new CDvmData();
	m_pDevices->AddNewChild(pDeviceTest);
	pDeviceTest->AppendCloneEx(*((CDvmData*)pDeviceAttrs));
	return pDeviceTest;
}

CExBaseObject* CAtsRpcTestDefine::AddDeviceTest(const CString &strBRCode)
{
	ASSERT (FALSE);
	return NULL;
}

CExBaseObject* CAtsRpcTestDefine::AddDeviceTest(const CString &strIP, long nPort)
{
	CDvmData *pDeviceTest = new CDvmData();
	m_pDevices->AddNewChild(pDeviceTest);

	pDeviceTest->AddValue(XPARA_ID_DVMFILE, m_strDvmFile);
	pDeviceTest->AddValue(AtsRpcTestDef_ip, strIP);
	pDeviceTest->AddValue(AtsRpcTestDef_port, nPort);

	return pDeviceTest;
}

CExBaseObject* CAtsRpcTestDefine::SetDeviceTest(long nIndex, const CString &strIP, long nPort)
{
	CDvmData *pDeviceTest = (CDvmData*)GetHead();

	if (pDeviceTest == NULL)
	{
		pDeviceTest = (CDvmData *)AddDeviceTest(strIP, nPort);
	}
	else
	{
		pDeviceTest->SetValue(XPARA_ID_DVMFILE, m_strDvmFile);
		pDeviceTest->SetValue(AtsRpcTestDef_ip, strIP);
		pDeviceTest->SetValue(AtsRpcTestDef_port, nPort);
	}

	return pDeviceTest;
}

CExBaseObject* CAtsRpcTestDefine::AddDeviceTest(long nPort, long nBaudRate, long nByteSize, long nStopBit, long nParity, long nBinOffset, long nBoutOffset, long nCOM)
{
	CDvmData *pDeviceTest = new CDvmData();
	m_pDevices->AddNewChild(pDeviceTest);

	pDeviceTest->AddValue(XPARA_ID_DVMFILE, m_strDvmFile);
	pDeviceTest->AddValue(AtsRpcTestDef_port, nPort);
	pDeviceTest->AddValue(AtsRpcTestDef_baud_rate, nBaudRate);
	pDeviceTest->AddValue(AtsRpcTestDef_byte_size, nByteSize);
	pDeviceTest->AddValue(AtsRpcTestDef_stop_bit, nStopBit);
	pDeviceTest->AddValue(AtsRpcTestDef_parity, nParity);
	pDeviceTest->AddValue(AtsRpcTestDef_bin_offset, nBinOffset);
	pDeviceTest->AddValue(AtsRpcTestDef_bout_offset, nBoutOffset);

	return pDeviceTest;
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
void CAtsRpcTestDefine::AddTestApp(const CString &strAppType, const CString &strFactory, const CString &strModel, const CString &strIP, const CString &strSN, const CString &strTime)
{
	CDvmData *pTestApp = m_pTemplate->AddNewData(strIP, strIP, strAppType, strIP);
	
	pTestApp->AddValue(_T("Factory"), strFactory);
	pTestApp->AddValue(_T("Model"), strModel);
	pTestApp->AddValue(_T("Name"), strAppType);
	pTestApp->AddValue(_T("SN"), strSN);
	pTestApp->AddValue(_T("DateManufac"), strTime);
}

void CAtsRpcTestDefine::AddTestApp(CExBaseObject *pData)
{
	CDvmData *pTestApp = (CDvmData*)pData->Clone();
	m_pTemplate->AddNewChild(pTestApp);
}

