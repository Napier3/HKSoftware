#pragma once

#include "ProtocolEngineInterface.h"
#include "../../../Module/Interface/ProtocolEngineInterface.h"
#include "../../../AutoTest/Module/PpEngineCreateMngr.h"


class CPpeParas : public CProtocolParasInterface
{
public:
	CPpeParas();
	virtual ~CPpeParas();

	virtual long Reset();
	virtual long AddData(const CString &bstrID, const CString &bstrValue);

	PpEngine::CPoDataInterface m_oDataInterface;
};

class CPpeValue : public CProtocolValueInterface
{
public:
	CPpeValue();
	virtual ~CPpeValue();

	virtual CString GetName();
	virtual void SetName(CString propVal);
	virtual CString GetID();
	virtual void SetID(CString propVal);
	virtual CString GetDataType();
	virtual void SetDataType(CString propVal);
	virtual CString GetValue();
	virtual void SetValue(CString propVal);
	virtual CString GetUnit();
	virtual void SetUnit(CString propVal);

	PpEngine::IValuePtr m_oValue;
};

class CPpeData : public CProtocolDataInterface
{
public:
	CPpeData();
	virtual ~CPpeData();

	virtual long GetCount();
	virtual CProtocolValueInterface* GetItem(long nIndex);
	virtual long RegisterDataChangedWndMsg(unsigned long hWnd, unsigned long nWMsgID);
	virtual long UnRegisterDataChangedWndMsg();
	virtual CString GetName();
	virtual void SetName(CString propVal);
	virtual CString GetID();
	virtual void SetID(CString propVal);
	virtual CString GetDataType();
	virtual void SetDataType(CString propVal);
	virtual CString GetValue();
	virtual void SetValue(CString propVal);
	virtual CString GetUnit();
	virtual void SetUnit(CString propVal);
	virtual CString GetMinValue();
	virtual void SetMinValue(CString propVal);
	virtual CString GetMaxValue();
	virtual void SetMaxValue(CString propVal);

	PpEngine::IDataPtr m_oData;
};


class CPpeDataset : public CProtocolDatasetInterface
{
public:
	CPpeDataset();
	virtual ~CPpeDataset();

	virtual long GetCount();
	virtual CProtocolDataInterface* GetItem(long nIndex);
	virtual CProtocolDataInterface* FindDataByID(const CString &strDataID);
	virtual CProtocolDataInterface* FindDataByName(const CString &strName);
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &strXmlData);
	virtual long DeleteAllDatas();

	PpEngine::IDataSetPtr m_oDataset;
};

class CPpeLogicDevice : public CProtocolLogicDeviceInterface
{
public:
	CPpeLogicDevice();
	virtual ~CPpeLogicDevice();

	virtual long GetCount();
	virtual CProtocolDatasetInterface* GetItem(long nIndex);
	virtual CProtocolDatasetInterface* FindDataSet(const CString &strDatasetPath);
	virtual CProtocolDataInterface* FindData(const CString &strPath);
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &strXmlData);

	PpEngine::ILogicDevicePtr m_oLogicDevice;
};

class CPpeDevice : public CProtocolDeviceInterface
{
public:
	CPpeDevice();
	virtual ~CPpeDevice();

	virtual void InitCommConfig(CDataGroup *pCommConfig);
	virtual long CommConfig(const CString &strCmmConfig);
	virtual long IsConnectSuccessful();
	virtual long GetCount();
	virtual CProtocolLogicDeviceInterface* GetItem(long nIndex);
	virtual CProtocolDatasetInterface* FindDataSet(const CString &strDataSetName);
	virtual CProtocolDataInterface* FindData(const CString &strPath);
	virtual long RunProcedure(const CString &strProcedureID, const CString &strDatasetPath);
	virtual long RunProcedureEx(const CString &strProcedureScript);
	virtual long AttachSystemWndMsg(unsigned long hWnd, unsigned long nMsgID);
	virtual long RegisterProcedureWndMsg(const CString &strProcedureID, unsigned long hWnd, unsigned long nMsgID);
	virtual long UnRegisterProcedureWndMsg(const CString &strProcedureID, unsigned long hWnd, unsigned long nMsgID);
	virtual long RegisterDataChangedWndMsg(const CString &strDataPath, unsigned long hWnd, unsigned long nWMsgID);
	virtual long UnRegisterDataChangedWndMsg(const CString &strDataPath);
	virtual long UnLoad();
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &bstrXmlData);
	virtual CString GetXmlDataEx(const CString &strDatasetPath);
	virtual CString SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData);
	virtual CProtocolParasInterface* GetDataInterface();
	virtual long ConnectDevice();
	virtual CString GetAttrByID(const CString &strAttrID);
	virtual long SetAttrByID(const CString &strAttrID, const CString &strValue);
	virtual long SaveDvmFile(const CString &strDvmFile);
	virtual long SetCommConfig(const CString &strCommConfig);
	virtual CString GetCommConfig(const CString &strCommConfig);
	virtual CString GetXmlDataLD();
	virtual CString GetLogsXml();	
	virtual CString QueryRecord(const CString &strBeginTime, const CString &strEndTime, const CString &strRcdFileName);
	virtual long SetRecordPath(const CString &strRcdPath);

public:
	PpEngine::IDevicePtr m_oPpDevice;

};

class CPpeEngine : public CProtocolEngineInterface
{
public:
	CPpeEngine();
	virtual ~CPpeEngine(void);

	virtual CString GetVersion();
	virtual CProtocolDeviceInterface* CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);
	virtual long GetCount();
	virtual CProtocolDeviceInterface* GetItem(long nIndex);
	virtual long ShowSpyWnd(long nShow);
	virtual long ReleaseDevice(const CString &strDeviceID);
	virtual long ReleaseAllDevice();
	virtual long CreateProject(const CString &strProjectFile);
	virtual long SetProtocolParse(long nStopFlag);
	virtual long ConfigEngine(const CString &strDvmFile);
	virtual long AttatchLogWnd(unsigned long hWnd);
	//2023-3-16 lijunqing
	virtual CProtocolDeviceInterface* CreateDevice(CPpSttCommConfig *pCommConfig);

public:
	PpEngine::IPpEnginePtr m_oEngine;
};

class CPpeEngineCreator : public CProtocolEngineCreatorInterface
{
public:
	CPpeEngineCreator();
	virtual ~CPpeEngineCreator();

protected:
	//支持多规约功能，即传统规约和61850MMS规约兼容  2016-8-15
	CPpEngineCreateMngr m_oPpEngineCreateMngr;

public:
	virtual CProtocolEngineInterface* GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID);
	virtual void ReleasePpEngine(const CString &strProgID);
	virtual void ReleasePpEngine();
	virtual void StopProtocolParseForReadSoe(BOOL bStop);
	virtual BOOL HasPpEngine();
	virtual void InitPpEngineShowSpyWnd();
	virtual long ConfigEngine();
	virtual long AttatchLogWnd(unsigned long hWnd);
};

