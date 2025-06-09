#pragma once

#include "../SmartTestDefineInterface.h"
#include "..\..\..\Module\DataMngr\DvmLogicDevice.h"


#define AtsRpcTestDef_template    _T("template")
#define AtsRpcTestDef_model		_T("model")
#define AtsRpcTestDef_model_sn	_T("model-sn")
#define AtsRpcTestDef_BRCode   _T("br-code")
#define AtsRpcTestDef_ip   _T("ip")
#define AtsRpcTestDef_ip_2   _T("ip_2")
#define AtsRpcTestDef_ip_3  _T("ip_3")
#define AtsRpcTestDef_COM_1   _T("COM_1")
#define AtsRpcTestDef_COM_2   _T("COM_2")
#define AtsRpcTestDef_COM_3  _T("COM_3")
#define AtsRpcTestDef_TestAppGroup _T("TestAppGroup")   //工装编号
#define AtsRpcTestDef_AcCurrent    _T("Ac-Current")
#define AtsRpcTestDef_DevOnlyCode  _T("DevOnlyCode")
#define AtsRpcTestDef_Sign     _T("Sign_File")
#define AtsRpcTestDef_DevIndex _T("DevIndex")

#define AtsRpcTestDef_port   _T("port")
#define AtsRpcTestDef_baud_rate   _T("baud-rate")
#define AtsRpcTestDef_byte_size   _T("byte-size")
#define AtsRpcTestDef_stop_bit   _T("stop-bit")
#define AtsRpcTestDef_parity   _T("parity")

#define AtsRpcTestDef_bin_offset   _T("bin-offset")
#define AtsRpcTestDef_bout_offset   _T("bout-offset")
#define AtsRpcTestDef_udc_power   _T("udc-power")

#define AtsRpcTestDef_DataType_TestApp   _T("test-app")
#define AtsRpcTestDef_DataType_IOApp   _T("io-app")

#define AtsRpcTestDef_rempte_ip   _T("remote-ip")
#define AtsRpcTestDef_rempte_port _T("remote-port")

/*
#define XPARA_ID_GBXMLFILE  _T("gbxml-file")
#define XPARA_ID_XTESTDB_TASKS  _T("xtest-db-task")
#define XPARA_ID_DEVICE_ATTR  _T("device-attr")
#define XPARA_ID_GBRPTFILE  _T("gbrpt-file")
#define XPARA_ID_DVMFILE    _T("dvm-file")
#define XPARA_ID_DVMFILE_DST    _T("dvm-file-dst")
#define XPARA_ID_DVMFILES    _T("dvm-files")
#define XPARA_ID_PPXMLFILE   _T("ppxml-file")
#define XPARA_ID_TscdFile    _T("tscd-file")
#define XPARA_ID_IecfgFile   _T("iecfg-file")
#define XPARA_ID_DvmMapFile  _T("dvmmap-file")
*/
/*
<ldevice name="文件夹名称" id="">
	<dataset name="template" id="template">
		<data name="gbxml-file" id="gbxml-file" value="SF\\CSC-100.gbxml"/>
		<data name="EngineProgID" id="EngineProgID" value=""/>
		<data name="ppxml-file" id="ppxml-file" value=""/>
		<data name="dvm-file" id="dvm-file" value=""/>
	</dataset>
	<dataset name="TestApp" id="TestApp" data-type="" write-mode="0" index="0">
		<data name="电能质量标准源" id="B150601" data-type="" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
			<value name="Factory" id="Factory" data-type="" value="北京博电新力电力仪器股份有限公司"/>
			<value name="Model" id="Model" data-type="" value="PQC600B"/>
			<value name="Name" id="Name" data-type="" value="电能质量标准源"/>
			<value name="SN" id="SN" data-type="" value="B150601"/>
			<value name="DateManufac" id="DateManufac" data-type="" value="2015年6月"/>
		</data>
		<data name="环境监测仪" id="THP1504022078LA" data-type="" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
			<value name="Factory" id="Factory" data-type="" value="佐格微系统有限公司"/>
			<value name="Model" id="Model" data-type="" value="DSR-THPLA"/>
			<value name="Name" id="Name" data-type="" value="环境监测仪"/>
			<value name="SN" id="SN" data-type="" value="THP1504022078LA"/>
			<value name="DateManufac" id="DateManufac" data-type="" value="2015年4月"/>
		</data>
	</dataset>
	<dataset name="devices" id="devices">
		<data name="device" id="device" value="SN" data-type="mgrp">
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
</ldevice>
*/
class CAtsRpcTestDefine : public CDvmLogicDevice, public CAtsTestDefineInterface
{
public:
	CAtsRpcTestDefine();
	virtual ~CAtsRpcTestDefine();

	static CXObjectRefBase*  New()
	{
		return new CAtsRpcTestDefine;
	}

	virtual void InitAfterRead();
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	void FreeAtsTestDefineInterface();

public:
	CDvmDataset *m_pTemplate;

public:
	virtual BOOL GetGuideBookFile(CString &strGbFile);
	virtual BOOL GetEngineProgID(CString &strEngineProgID);
	virtual BOOL GetPpxmlFile(CString &strPpxmlFile);
	virtual BOOL GetDvmFile(CString &strDvmFile);

public:
	virtual void InitTestTaskName(const CString &strModel);
	virtual void SetTestTaskName(const CString &strTaskName);
	virtual void SetTestTmplateFile(const CString &strGbxmlFile, const CString &strEngineProgID, const CString &strPpXmlFile, const CString &strDvmFile);
	virtual CExBaseObject* AddDeviceTest(const CString &strDvmFile, const CString &strBRCode, long nPort, long nBaudRate, long nByteSize, long nStopBit
		, long nParity, long nBinOffset, long nBoutOffset, long nUdc_Power, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
		, const CString &strSignPath, const CString &strDevIndex);
	virtual CExBaseObject* AddDeviceTest(const CString &strBRCode, long nPort, long nBaudRate, long nByteSize, long nStopBit, long nParity, long nBinOffset
		, long nBoutOffset, long nUdc_Power, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode, const CString &strSignPath
		, const CString &strDevIndex);

	virtual CExBaseObject* AddDeviceTest(CExBaseObject *pDeviceAttrs);
	virtual CExBaseObject* AddDeviceTest(const CString &strBRCode);
	virtual CExBaseObject* AddDeviceTest(const CString &strIP, long nPort);
	virtual CExBaseObject* SetDeviceTest(long nIndex, const CString &strIP, long nPort);
	virtual CExBaseObject* AddDeviceTest(long nPort, long nBaudRate, long nByteSize, long nStopBit, long nParity, long nBinOffset, long nBoutOffset, long nCOM);

	virtual void AddTestApp(const CString &strAppType, const CString &strFactory, const CString &strModel, const CString &strIP, const CString &strSN, const CString &strTime);
	virtual void AddTestApp(CExBaseObject *pData);

	void AddApp_TestApp(const CString &strFactory, const CString &strModel, const CString &strIP, const CString &strSN, const CString &strTime)
	{
		AddTestApp(AtsRpcTestDef_DataType_TestApp,strFactory, strModel, strIP, strSN, strTime);
	}

	void AddApp_IOApp(const CString &strFactory, const CString &strModel, const CString &strIP, const CString &strSN, const CString &strTime)	
	{
		AddTestApp(AtsRpcTestDef_DataType_IOApp,strFactory, strModel, strIP, strSN, strTime);
	}
};

