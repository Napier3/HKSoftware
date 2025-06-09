#pragma once

#include "ProtocolEngineInterface.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngine.h"


class CPpsttParas : public CProtocolParasInterface
{
public:
	CPpsttParas();
	virtual ~CPpsttParas();

	virtual long Reset();
	virtual long AddData(const CString &bstrID, const CString &bstrValue);

	CPxiDataInterface *m_pDataInterface;
};

class CPpsttValue : public CProtocolValueInterface
{
public:
	CPpsttValue();
	virtual ~CPpsttValue();

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

    CPxiValue *m_pValue;
};

class CPpsttData : public CProtocolDataInterface
{
public:
	CPpsttData();
	virtual ~CPpsttData();

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

    CPxiData *m_pData;
};


class CPpsttDataset : public CProtocolDatasetInterface
{
public:
	CPpsttDataset();
	virtual ~CPpsttDataset();

	virtual long GetCount();
	virtual CProtocolDataInterface* GetItem(long nIndex);
	virtual CProtocolDataInterface* FindDataByID(const CString &strDataID);
	virtual CProtocolDataInterface* FindDataByName(const CString &strName);
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &strXmlData);
	virtual long DeleteAllDatas();

    CPxiDataSet *m_pDataset;
};

class CPpsttLogicDevice : public CProtocolLogicDeviceInterface
{
public:
	CPpsttLogicDevice();
	virtual ~CPpsttLogicDevice();

	virtual long GetCount();
	virtual CProtocolDatasetInterface* GetItem(long nIndex);
	virtual CProtocolDatasetInterface* FindDataSet(const CString &strDatasetPath);
	virtual CProtocolDataInterface* FindData(const CString &strPath);
	virtual CString GetXmlData();
	virtual long SetXmlData(const CString &strXmlData);

    CPxiLogicDevice *m_pLogicDevice;
};

class CPpsttDevice : public CProtocolDeviceInterface
{
public:
	CPpsttDevice();
	virtual ~CPpsttDevice();

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

    CPxiDevice *m_pPxiDevice;
};

class CPpsttEngine : public CProtocolEngineInterface
{
public:
	CPpsttEngine();
	virtual ~CPpsttEngine(void);

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
};

/*  shaolei 移动到PpsttEngineCreator.h中  20220813
class CPpsttEngineCreator : public CProtocolEngineCreatorInterface
{
public:
	CPpsttEngineCreator();
	virtual ~CPpsttEngineCreator();

public:
	virtual CProtocolEngineInterface* GetProtocolEngine(const CString &strPpEngineProgID);
	virtual void ReleasePpEngine(const CString &strProgID);
	virtual void ReleasePpEngine();
	virtual void StopProtocolParseForReadSoe(BOOL bStop);
	virtual BOOL HasPpEngine();
	virtual void InitPpEngineShowSpyWnd();
    virtual long ConfigEngine();
};
*/
