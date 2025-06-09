#pragma once

#include "SttBaseInterface.h"
#include "PpSttCommConfig.h"

#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

static const CString g_strSttEngine_MMS = _T("MmsEngine");
static const CString g_strSttEngine_PXI = _T("PpEngine");
static const CString g_strSttEngine_IOT = _T("PpSttIotEngine");
static const CString g_strSttEngine_MQTT = _T("PpSttMqttEngine");

#define WM_ENGINE_SYSTEM_MSG           (WM_USER + 1116)
#define	WM_COMM_COMMAND		(WM_USER+1117)
#define WM_ENGINE_EVENT_MSG           (WM_USER + 1118)

class CProtocolParasInterface : public CSttBaseInterface
{
public:
	CProtocolParasInterface(){}
	virtual ~CProtocolParasInterface(){}

	virtual long Reset() = 0;
	virtual long AddData(const CString &bstrID, const CString &bstrValue) = 0;
	virtual long AddData(const CString &bstrID, long nValue){	return 0;	}
};

class CProtocolValueInterface : public CSttBaseInterface
{
public:
	CProtocolValueInterface(){}
	virtual ~CProtocolValueInterface(){}

	virtual CString GetName() = 0;
	virtual void SetName(CString propVal) = 0;
	virtual CString GetID() = 0;
	virtual void SetID(CString propVal) = 0;
	virtual CString GetDataType() = 0;
	virtual void SetDataType(CString propVal) = 0;
	virtual CString GetValue() = 0;
	virtual void SetValue(CString propVal) = 0;
	virtual CString GetUnit() = 0;
	virtual void SetUnit(CString propVal) = 0;
};

class CProtocolDataInterface : public CSttBaseInterface
{
public:
	CProtocolDataInterface(){};
	virtual ~CProtocolDataInterface(){};

	virtual long GetCount() = 0;
	virtual CProtocolValueInterface* GetItem(long nIndex) = 0;
	virtual long RegisterDataChangedWndMsg(PSX_OBJ_ADDR hWnd, unsigned long nWMsgID) = 0;
	virtual long UnRegisterDataChangedWndMsg() = 0;
	virtual CString GetName() = 0;
	virtual void SetName(CString propVal) = 0;
	virtual CString GetID() = 0;
	virtual void SetID(CString propVal) = 0;
	virtual CString GetDataType() = 0;
	virtual void SetDataType(CString propVal) = 0;
	virtual CString GetValue() = 0;
	virtual void SetValue(CString propVal) = 0;
	virtual CString GetUnit() = 0;
	virtual void SetUnit(CString propVal) = 0;
	virtual CString GetMinValue() = 0;
	virtual void SetMinValue(CString propVal) = 0;
	virtual CString GetMaxValue() = 0;
	virtual void SetMaxValue(CString propVal) = 0;
};


class CProtocolDatasetInterface : public CSttBaseInterface
{
public:
	CProtocolDatasetInterface(){}
	virtual ~CProtocolDatasetInterface(){}

	virtual long GetCount() = 0;
	virtual CProtocolDataInterface* GetItem(long nIndex) = 0;
	virtual CProtocolDataInterface* FindDataByID(const CString &strDataID) = 0;
	virtual CProtocolDataInterface* FindDataByName(const CString &strName) = 0;
	virtual CString GetXmlData() = 0;
	virtual long SetXmlData(const CString &strXmlData) = 0;
	virtual long DeleteAllDatas() = 0;
};

class CProtocolLogicDeviceInterface : public CSttBaseInterface
{
public:
	CProtocolLogicDeviceInterface(){}
	virtual ~CProtocolLogicDeviceInterface(){}

	virtual long GetCount() = 0;
	virtual CProtocolDatasetInterface* GetItem(long nIndex) = 0;
	virtual CProtocolDatasetInterface* FindDataSet(const CString &strDatasetPath) = 0;
	virtual CProtocolDataInterface* FindData(const CString &strPath) = 0;
	virtual CString GetXmlData() = 0;
	virtual long SetXmlData(const CString &strXmlData) = 0;
};

class CProtocolDeviceInterface : public CSttBaseInterface
{
public:
	CProtocolDeviceInterface(){}
	virtual ~CProtocolDeviceInterface()	{}

	virtual void InitCommConfig(CDataGroup *pCommConfig) = 0;
	virtual long CommConfig(const CString &strCmmConfig) = 0;
	virtual long IsConnectSuccessful() = 0;
	virtual long GetCount() = 0;
	virtual CProtocolLogicDeviceInterface* GetItem(long nIndex) = 0;
	virtual CProtocolDatasetInterface* FindDataSet(const CString &strDataSetName) = 0;
	virtual CProtocolDataInterface* FindData(const CString &strPath) = 0;
	virtual long RunProcedure(const CString &strProcedureID, const CString &strDatasetPath) = 0;
	virtual long RunProcedureEx(const CString &strProcedureScript) = 0;
	virtual long AttachSystemWndMsg(PSX_OBJ_ADDR hWnd, unsigned long nMsgID) = 0;
	virtual long RegisterProcedureWndMsg(const CString &strProcedureID, PSX_OBJ_ADDR hWnd, unsigned long nMsgID) = 0;
	virtual long UnRegisterProcedureWndMsg(const CString &strProcedureID, PSX_OBJ_ADDR hWnd, unsigned long nMsgID) = 0;
	virtual long RegisterDataChangedWndMsg(const CString &strDataPath, PSX_OBJ_ADDR hWnd, unsigned long nWMsgID) = 0;
	virtual long UnRegisterDataChangedWndMsg(const CString &strDataPath) = 0;
	virtual long UnLoad() = 0;
	virtual CString GetXmlData() = 0;
	virtual long SetXmlData(const CString &bstrXmlData) = 0;
	virtual CString GetXmlDataEx(const CString &strDatasetPath) = 0;
	virtual CString SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData) = 0;
	virtual CProtocolParasInterface* GetDataInterface() = 0;
	virtual long ConnectDevice() = 0;
	virtual CString GetAttrByID(const CString &strAttrID) = 0;
	virtual long SetAttrByID(const CString &strAttrID, const CString &strValue) = 0;
	virtual long SaveDvmFile(const CString &strDvmFile) = 0;
	virtual long SetCommConfig(const CString &strCommConfig) = 0;
	virtual CString GetCommConfig(const CString &strCommConfig) = 0;
	virtual CString GetXmlDataLD() = 0;
	virtual CString GetLogsXml() = 0;	
	virtual CString QueryRecord(const CString &strBeginTime, const CString &strEndTime, const CString &strRcdFileName) = 0;
	virtual long SetRecordPath(const CString &strRcdPath) = 0;

};

class CProtocolEngineInterface : public CSttBaseInterface
{
public:
	CProtocolEngineInterface(){};
	virtual ~CProtocolEngineInterface(void){};

	virtual CString GetVersion() = 0;
	virtual CProtocolDeviceInterface* CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID) = 0;
	virtual long GetCount() = 0;
	virtual CProtocolDeviceInterface* GetItem(long nIndex) = 0;
	virtual long ShowSpyWnd(long nShow) = 0;
	virtual long ReleaseDevice(const CString &strDeviceID) = 0;
	virtual long ReleaseAllDevice() = 0;
	virtual long CreateProject(const CString &strProjectFile) = 0;
	virtual long SetProtocolParse(long nStopFlag) = 0;
	virtual long ConfigEngine(const CString &strDvmFile) = 0;
	virtual long AttatchLogWnd(PSX_OBJ_ADDR hWnd) = 0;

	//2023-3-16 lijunqing
	virtual CProtocolDeviceInterface* CreateDevice(CPpSttCommConfig *pCommConfig) = 0;
};


class CProtocolEngineCreatorInterface : public CSttBaseInterface
{
public:
	CProtocolEngineCreatorInterface()
	{
		m_hLogWnd = NULL;
	};

	virtual ~CProtocolEngineCreatorInterface(void){};

	virtual CProtocolEngineInterface* GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID) = 0;
	virtual void ReleasePpEngine(const CString &strProgID) = 0;
	virtual void ReleasePpEngine() = 0;
	virtual void StopProtocolParseForReadSoe(BOOL bStop) = 0;
	virtual BOOL HasPpEngine() = 0;
	virtual void InitPpEngineShowSpyWnd() = 0;
	virtual long ConfigEngine() = 0;

public:
	unsigned long m_hLogWnd;

};
