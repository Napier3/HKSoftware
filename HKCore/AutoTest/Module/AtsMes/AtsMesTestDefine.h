#pragma once

#include "../SmartTestDefineInterface.h"

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../SttStudio/Module/SttCmd/SttCmdDefineGlobal.h"

/*
<ats-cmd name="" id="CreateTest" testor="">
	<paras>
		<data name="测试台标识" id="TestID" value="测试台SN/"/>
		<data name="测试模板" id="gbxml-file" value="SZNR-TTU.gbexe"/>
		<data name="测试模板" id="gbxml-file_s" value="……………"/> 
		
		[以下部分兼容老版本数据格式]
		<data name="" id="DeviceID" data-type="" value="SZNR-TTU"/>
		<data name="规则文件" id="ppxml-file" value="SZNR-TTU.ppxml"/>
		<data name="模型文件" id="dvm-file" value="SZNR-TTU.xml"/>
		<data name="报告记录文件" id="gbrpt-file" value="SZNR-TTU202012131427"/>
		<data name="被测装置引擎" id="EngineProgID" value="PpEngine"/>
		<group name="" id="comm-config" data-type="" value="">
		<data name="" id="tcp-client" data-type="" value="">
			<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
			<value name="" id="local-port" data-type="" value="20183"/>
			<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
			<value name="" id="remote-port" data-type="" value="2404"/>
		</data>
		</group>
	
		[以下部分为物联测试设备以及被测设备信息]
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
		</group>
		<group id="test-apps">
			<group id="test-app">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="IotVm"/>
				<data id="dvm-file" value="MacroTest.xml"/>
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			……
		</group>
	</paras>
</ats-cmd>
*/
class CAtsMesTestDefine : public CDataGroup, public CAtsTestDefineInterface
{
public:
	CAtsMesTestDefine();
	virtual ~CAtsMesTestDefine();

	static CXObjectRefBase*  New()
	{
		return new CAtsMesTestDefine;
	}

	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttParasKey();     }
	virtual void InitAfterRead();
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	void FreeAtsTestDefineInterface();

public:
	virtual BOOL GetGuideBookFile(CString &strGbFile);
	virtual BOOL GetEngineProgID(CString &strEngineProgID);
	virtual BOOL GetEngineMode(CString &strEngineMode);  //shaolei 2023-11-2
	virtual BOOL GetPpxmlFile(CString &strPpxmlFile);
	virtual BOOL GetDvmFile(CString &strDvmFile);
	virtual BOOL GetTestType(CString &strTestType);
	virtual BOOL GetDeviceSN(CString &strDeviceSN, long nIndex);  //shaolei 2023-11-3
	virtual BOOL GetDvmFile(CString &strDvmFile, long nIndex);
	virtual BOOL GetPpxmlFile(CString &strPpxmlFile, long nIndex);

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

};
